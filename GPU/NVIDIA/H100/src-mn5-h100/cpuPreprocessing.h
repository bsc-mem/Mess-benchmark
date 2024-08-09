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

#ifndef CPUPREPROCESSING_H
#define CPUPREPROCESSING_H

#include <iostream>
#include <fstream>

#include "common.h"

using namespace std;


void createWorkloadGeneratorArray(STREAM_TYPE* a, STREAM_TYPE* b) {
    
    // initialize the arrays
    for (uint64_t i = 0; i < STREAM_ARRAY_SIZE; i++) {
        a[i] = 0.0;
        b[i] = 2.0;
    }
}

#ifdef __x86__
void testPtrChaseCPUPower(struct line *array, uint64_t number_of_instructions) {
    
    clock_t beginTime,endTime;

    uint64_t i; 
    i = number_of_instructions/PTR_CHASE_LOOP_SIZE; // number of iterations 
    // cout << "i = " << i << endl;
    struct line *start; // rbx is fixed as the beginning of the array, what changes is the offset inside the array, given by rax
    start = array;
    struct line *next; // rax is the next element to be read inside the array
    next = array[0].next;                  // it starts with the 64 bit information contained in the first position of the array
                                            // the 64 bit information is an offset
                                            // the assembly code copies to rax the value contained at the array position (relative)0 + 64-bit offset
                                            // then in the next step it accesses 0 + the new offset to repeat the copy.
                                            // It is being forced to perform jumps inside the array

    // cout << "number_of_instructions = " << number_of_instructions << endl;
    // cout << "PTR_CHASE_LOOP_SIZE = " << PTR_CHASE_LOOP_SIZE << endl;
    // cout << "i = " << i << endl;
    // cout << "start = " << start << endl;
    // cout << "next = " << array->next << endl;
    beginTime = clock();
    // register uint64_t next asm("x2");
    // x2 is the next element to be read inside the array
    // it starts with the 64 bit information contained in the first position of the array (second line of assembly)
    // the 64 bit information is an offset
    // the assembly code copies to x2 the value contained at the array position (relative)0 + 64-bit offset
    // then in the next step it accesses 0 + the new offset to repeat the copy.
    // It is being forced to perform jumps inside the array

    // each line in loopCPU.h: "add %3, %1, %2; ld %2, 0(%3);"
    // which means 
    // add %3, %1, %2; add	RT, RA, RB -> RT = RA + RB
    // ld %2, 0(%3); -> ld	RT, Disp(RA) -> Load Doubleword (64 bits) from effective address formed by RA+Disp into RT
    __asm__ __volatile__ (
        "start_loop:"
        #include "loopCPU.h"
        "dec %0;\n\t"
        "jnz start_loop;\n\t"
        :
        : "r" (i), "r" (start), "r" (next)
        : 
    );
    
    endTime = clock();

    cout << ((double)(endTime - beginTime)/ CLOCKS_PER_SEC) << " seconds time elapsed" << endl;
    cout << "latency from execution time: " << (((1000000000)*(double)(endTime - beginTime)/ CLOCKS_PER_SEC)/((number_of_instructions))) << "ns" << endl;

}
#endif

#ifdef __POWERPC__
void testPtrChaseCPUPower(struct line *array, uint64_t number_of_instructions) {
    register uint64_t i;
    register struct line *start; // x1 is fixed as the beginning of the array, what changes is the offset inside the array, given by x2
    register struct line *next; // rax is the next element to be read inside the array
    register uint64_t tmp=0;
    clock_t beginTime,endTime;

    i=number_of_instructions/PTR_CHASE_LOOP_SIZE; // number of iterations
    cout << "iterations = " << i << endl;
    start = array;
    next = 0;

    cout << "i = " << i << endl;
    cout << "start = " << start << endl;
    // cout << "next = " << array->next << endl;

    

    beginTime = clock();


    // perform pointer chase on the array
    // for (uint64_t j = 0; j < i; j++) {
    //     next = start->next;
    //     start = next;
    //     cout << "start = " << start << endl;
    // }

    // register uint64_t next asm("x2");
    // x2 is the next element to be read inside the array
    // it starts with the 64 bit information contained in the first position of the array (second line of assembly)
    // the 64 bit information is an offset
    // the assembly code copies to x2 the value contained at the array position (relative)0 + 64-bit offset
    // then in the next step it accesses 0 + the new offset to repeat the copy.
    // It is being forced to perform jumps inside the array

    // each line in loopCPU.h: "add %3, %1, %2; ld %2, 0(%3);"
    // which means 
    // add %3, %1, %2; add	RT, RA, RB -> RT = RA + RB
    // ld %2, 0(%3); -> ld	RT, Disp(RA) -> Load Doubleword (64 bits) from effective address formed by RA+Disp into RT
    asm __volatile__ (
        "start_loop:"
        #include "loopCPU.h"
        "ai %0, %0, -0x01;"
        "cmpli 0, 1, %0, 0;"
        "bne start_loop;"
        :
        : "r" (i), "r" (start), "r" (next), "r" (tmp)
        : 
    );
    
    endTime = clock();

    cout << ((double)(endTime - beginTime)/ CLOCKS_PER_SEC) << " seconds time elapsed" << endl;
    cout << "latency from execution time: " << (((1000000000)*(double)(endTime - beginTime)/ CLOCKS_PER_SEC)/((number_of_instructions))) << "ns" << endl;

}
#endif


void validate(int input, int reference) {
    if (input != reference) {
        cout << "Error: " << input << " != " << reference << endl;
        exit(1);
    }
}

struct line* createPointerChaseArray(uint64_t array_bytes, string filename) {
    // pointer chase array
    struct line *array; 

    int valid = cudaMallocHost((void**)&array, array_bytes);
    if(valid != 0) {
        cout << "Error: " << valid << endl;
        return NULL;
    }
    // number of elelemtns in the array
    uint64_t num_elements = array_bytes / CACHE_LINE;
    cout << "num_elements = " << num_elements << endl;

    ifstream inputFile (filename);

    if (!inputFile.is_open()) {
        printf("Random walk file cannot be located.\n");
        free(array);
        exit(1);
    }

    // generating input of pointer chasing...
    // insert next entry of line from the file.
    for (uint64_t i = 0; i < num_elements; ++i)
    {
        uint64_t tmp;
        inputFile >> tmp;
        array[i].next = (struct line *) tmp;
    }

    return array;
}



// Function to parse command line arguments
void parseCommandLineArguments(int argc, char** argv, size_t& array_bytes, const char*& filename, uint64_t& rd_percentage, uint64_t& pause, uint64_t& number_of_instructions) {
    int opt;
    while ((opt = getopt(argc, argv, ":s:f:r:p:i:")) != -1) {
        // printf("opt = %c\n", opt);
        // cout << "optarg = " << optarg << "\n";
        switch (opt) {
            case 's':
                array_bytes = atoi(optarg);
                break;
            case 'i':
                number_of_instructions = atoi(optarg);
                break; 
            case 'f':
                filename = optarg;
                break;
            case 'r':
                rd_percentage = atoi(optarg);
                cout << "rd_percentage value is: " << rd_percentage << endl;
                if (rd_percentage > 100 || rd_percentage % 2 == 1) {
                    printf("ERROR: RD ratio has to be an even number between 0 and 100.\n");
                    exit(-1);
                }
                break;
            case 'p':
                pause = atoi(optarg);
                cout << "pause value is: " << pause << endl;
                break;
            default:
                printf("Invalid option - default \n");
                printf("usage: %s -s <array_size> -f <filename> -r <rd_percentage> -p <pause> -i <number_of_instructions> \n", argv[0]);
                exit(-1);
        }
    }

    if (optind < argc || argc != 11) {
        printf("Invalid option\n");
        printf("usage: %s -s <array_size> -f <filename> -r <rd_percentage> -p <pause> -i <number_of_instructions> \n", argv[0]);
        exit(-1);
    }
}

void busyWait(uint64_t wait_cycles) {
    for (uint64_t i = 0; i < wait_cycles; i++) {
        asm volatile("nop");
    }
}


void printGPUInfo() {
    cout << "Node's GPUs configuration!" << endl;
    int deviceCount;

    cudaGetDeviceCount(&deviceCount);
    std::cout << "Number of GPUs: " << deviceCount << std::endl;

    for (int i = 0; i < deviceCount; i++) {
        cudaDeviceProp deviceProp;
        cudaGetDeviceProperties(&deviceProp, i);
        std::cout << "GPU " << i << " Information:" << std::endl;
        std::cout << "  Name: " << deviceProp.name << std::endl;
        std::cout << "  Total Global Memory: " << deviceProp.totalGlobalMem << " bytes" << std::endl;
        std::cout << "  Memory Clock Rate: " << deviceProp.memoryClockRate << " kHz" << std::endl;
        std::cout << "  Memory Bus Width: " << deviceProp.memoryBusWidth << " bits" << std::endl;
        std::cout << "  Compute Capability: " << deviceProp.major << "." << deviceProp.minor << std::endl;
        printf("  Detected Compute SM %d.%d hardware with %d multi-processors (SMT)\n", deviceProp.major, deviceProp.minor, deviceProp.multiProcessorCount);
        std::cout << "  Number of Warps per SM: " << deviceProp.warpSize << std::endl;
        std::cout << "  Size of each Warp: " << deviceProp.maxThreadsPerMultiProcessor / deviceProp.warpSize << std::endl;
        cout << "  Does support concurrent kernels: " << deviceProp.concurrentKernels << endl;
        std::cout << std::endl << std::endl << std::endl;
    }
}

#endif // CPUPREPROCESSING_H
