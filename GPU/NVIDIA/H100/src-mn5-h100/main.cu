/*
 * Copyright (c) 2024, Barcelona Supercomputing Center
 * Contact: pouya.esmaili    [at] bsc [dot] es
 *          petar.radojkovic [at] bsc [dot] es
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 *     * Neither the name of the copyright holder nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <iostream>
#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include <papi.h>

#include "gpuKernels.cuh"
#include "cpuPreprocessing.h"

using namespace std;
#include <chrono>

#define NUM_EVENTS 4

void handle_error(char *where, int rc)
{
    char *str = PAPI_strerror(rc);
    fprintf(stderr, "%s error %d: %s\n", where, rc, str);
    exit(1);
}

uint64_t device_sync = 0;

int main(int argc, char **argv)
{

    /*          PAPI section           */
    // TODO add ifdef PAPI to generalize the code.
    const char *EventName[] = {"cuda:::fbpa__dram_read_bytes.sum.per_second:device=0", "cuda:::fbpa__dram_write_bytes.sum.per_second:device=0", "cuda:::fbpa__dram_read_bytes.sum:device=0", "cuda:::fbpa__dram_write_bytes.sum:device=0"};

    /* Initialize the PAPI library */
    int events[NUM_EVENTS];
    long long values[NUM_EVENTS];
    int retval;
    int EventSet = PAPI_NULL;
    
    validate(PAPI_library_init(PAPI_VER_CURRENT), PAPI_VER_CURRENT);

    /* convert PAPI native events to PAPI code */
    for (uint64_t i = 0; i < NUM_EVENTS; i++) 
    {
        validate(PAPI_event_name_to_code(EventName[i], &events[i]), PAPI_OK);
    }

    validate(PAPI_create_eventset(&EventSet), PAPI_OK);
    validate(PAPI_add_events(EventSet, events, NUM_EVENTS), PAPI_OK);

    const char *filename;            // ptr chase file address
    uint64_t array_bytes_ptrChase;   // size of the ptr chase array in bytes
    uint64_t number_of_instructions; // number of instructions to be executed by pointer chase kernel

    // create two array for our workload generator
    STREAM_TYPE *stream_a; // for reads
    STREAM_TYPE *stream_b; // for writes
    // create two array for our workload generator (GPU side)
    STREAM_TYPE *d_stream_a;  // for reads
    STREAM_TYPE *d_stream_b;  // for writes
    uint64_t rd_percentage, pause; // workload generator inputs to determine r/w ratio and intensity of the workload

    // parse command line arguments and initialize variables
    parseCommandLineArguments(argc, argv, array_bytes_ptrChase, filename, rd_percentage, pause, number_of_instructions);


    cout << "array_bytes_ptrChase: " << array_bytes_ptrChase << endl;
    // create a pointer chase array (each elelemnt is one cacheline)
    struct line *ptrChaceArray = createPointerChaseArray(array_bytes_ptrChase, filename);
    // testPtrChaseCPUPower(ptrChaceArray, number_of_instructions);
    
    struct line *d_ptrChaceArray;

    // copy the pointer chase array for the GPU
    validate(cudaMalloc((void **)&d_ptrChaceArray, array_bytes_ptrChase), 0);

    // create workload generator arrays for read (stream_a) and write (stream_b)
    uint64_t workloadGeneratorArraySize = STREAM_ARRAY_SIZE * sizeof(STREAM_TYPE);
    validate(cudaMallocHost((void **)&stream_a, workloadGeneratorArraySize), 0);
    validate(cudaMallocHost((void **)&stream_b, workloadGeneratorArraySize), 0);

    createWorkloadGeneratorArray(stream_a, stream_b);

    // copy the workload generator arrays for the GPU
    validate(cudaMalloc((void **)&d_stream_a, workloadGeneratorArraySize), 0);
    validate(cudaMalloc((void **)&d_stream_b, workloadGeneratorArraySize), 0);

    // set the kernel function for the workload generator based on the read/write ratio
    setKernelFunction(rd_percentage);
    
    // print GPUs info
    // printGPUInfo(); 

    // chose GPU number zero for our experiments
    // Later we can exploit multiple GPUs to fisnish all the Mess experimental points faster.
    cudaSetDevice(0); 

    // get the range of stream priorities for this device
    int priority_high, priority_low;
    cudaDeviceGetStreamPriorityRange(&priority_low, &priority_high);

    // create streams with highest and lowest available priorities
    cudaStream_t streamPtrChase, streamWorkloadGenerator;
    cudaEvent_t startEvent, stopEvent;

    // create two streams with highest and lowest priorities
    // Create two streams and two events for our two kernels (ptrChase and workload generator)
    cudaStreamCreateWithPriority(&streamPtrChase, cudaStreamNonBlocking, priority_high);         // stream1: ptrChase
    cudaStreamCreateWithPriority(&streamWorkloadGenerator, cudaStreamNonBlocking, priority_low); // stream2: workload generator
    // check priority_low -> priority_high + 1 
    cudaEventCreate(&startEvent);
    cudaEventCreate(&stopEvent);

    // copy the pointer chase array to the GPU
    cudaMemcpyAsync(d_ptrChaceArray, ptrChaceArray, array_bytes_ptrChase, cudaMemcpyHostToDevice, streamPtrChase);
    // copy the workload generator arrays to the GPU
    cudaMemcpyAsync(d_stream_a, stream_a, workloadGeneratorArraySize, cudaMemcpyHostToDevice, streamWorkloadGenerator);
    cudaMemcpyAsync(d_stream_b, stream_b, workloadGeneratorArraySize, cudaMemcpyHostToDevice, streamWorkloadGenerator);

    // wait for the data movement to finish
    cudaStreamSynchronize(streamPtrChase); 
    cudaStreamSynchronize(streamWorkloadGenerator); 

    cudaDeviceProp deviceProp;
    cudaGetDeviceProperties(&deviceProp, 0); // get the property of the first GPU
    uint64_t NumberOfBlocksWG = deviceProp.multiProcessorCount-1;
    
    // reset papi counters
    PAPI_reset(EventSet);
    // start the PAPI counters (because of some reason in MN5 we cannot instrument with PAPI while some curves are running)
    retval = PAPI_start(EventSet); 
    if (retval != PAPI_OK)
        fprintf(stderr, "PAPI_start failed\n");

    auto start_bw = std::chrono::system_clock::now();
    // launch the kernels
    // 1. workload generator kernel
    STREAM_copy_rw<<<NumberOfBlocksWG, 1024, 0, streamWorkloadGenerator>>>(d_stream_a, d_stream_b, workloadGeneratorArraySize, pause);
    validate(cudaGetLastError(), cudaSuccess);
    sleep(20);
    

    // start the timer
    // cudaEventRecord(startEvent, 0);
    // reset papi counters
    PAPI_reset(EventSet);
    // start the PAPI counters
    // retval = PAPI_start(EventSet); 
    // if (retval != PAPI_OK)
    //     fprintf(stderr, "PAPI_start failed\n");

    auto start = std::chrono::system_clock::now();


    // 2. ptrChase kernel (1 thread and 1 block)
    pointerChase<<<1, 1, 0, streamPtrChase>>>(d_ptrChaceArray, array_bytes_ptrChase, number_of_instructions);
    validate(cudaGetLastError(), cudaSuccess);

    // wait for the kernels to finish
    cudaStreamSynchronize(streamPtrChase);
    // if(device_sync)
    //     cudaStreamSynchronize(streamWorkloadGenerator);

    

    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;

    // this is more accurate
    std::cout << "latency time elapsed: " << elapsed.count() << " ns" << '\n';
    cout << "average access latency: " << elapsed.count() / number_of_instructions << " ns" << endl;

    elapsed = end - start_bw;
    std::cout << "BW time elapsed: " << elapsed.count() << " ns" << '\n';
    // this way of timing is not accurate for our case. 
    // float elapsedTime;
    // cudaEventElapsedTime(&elapsedTime, startEvent, stopEvent);

    // print the time
    // cout << "Time: " << elapsedTime << " ms" << endl;
    // cout << "average access latency " << 1000000 * (elapsedTime / number_of_instructions) << " ns" << endl; 

    // check PAPI stop and read the counters 
    retval = PAPI_stop(EventSet, NULL);
    if (retval != PAPI_OK)
        fprintf(stderr, "PAPI_read failed\n");

    retval = PAPI_read(EventSet, values);
    if (retval != PAPI_OK)
        fprintf(stderr, "PAPI_read failed\n");

    for (uint64_t i = 0; i < NUM_EVENTS; i++)
        printf("%12lld \t\t --> %s \n", values[i], EventName[i]);

    cudaMemcpyAsync(stream_a, d_stream_a, STREAM_ARRAY_SIZE * sizeof(STREAM_TYPE), cudaMemcpyDeviceToHost, streamWorkloadGenerator);
    cudaMemcpyAsync(stream_b, d_stream_b, STREAM_ARRAY_SIZE * sizeof(STREAM_TYPE), cudaMemcpyDeviceToHost, streamWorkloadGenerator);

    cudaStreamSynchronize(streamPtrChase);
    cudaStreamSynchronize(streamWorkloadGenerator);

    cout << "stream_a[0]: " << stream_a[0] << endl;
    cout << "stream_b[0]: " << stream_b[0] << endl;

    cudaStreamDestroy(streamPtrChase);
    cudaStreamDestroy(streamWorkloadGenerator);

    cudaEventDestroy(startEvent);
    cudaEventDestroy(stopEvent);

    return 0;
}