/*
 * Copyright (c) 2024, Barcelona Supercomputing Center
 * Contact: mess             [at] bsc [dot] es
 *          pouya.esmaili    [at] bsc [dot] es
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

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cstdint> // include this header for uint64_t
#include <sys/mman.h> // for mmap

#include "perf_helper.h"

using namespace std;

#ifndef ARRAY_ELEMS
#pragma message "ARRAY_ELEMS not defined. Using the default value."
#define ARRAY_ELEMS 524288
#endif

#ifndef ITERS
// #pragma message "ITERS not defined. Using the default value."
#define ITERS 5000
#endif

#ifndef CACHE_LINE
#define CACHE_LINE 128
#endif

struct line{
    struct line *next; // 8 byte
    uint8_t pad[CACHE_LINE-8];
};


struct line *array;


int main(int argc, char *argv[]) {
    int r;
    uint64_t array_bytes=((uint64_t) ARRAY_ELEMS ) * CACHE_LINE; // get the size of the array in bytes (num of elements of the size of the struct)
    r = posix_memalign((void **)&array, CACHE_LINE, array_bytes); // allocate a space in mem to receive the amount of information calculated
                                                          // aligned to cache_line size
    

    // array = (line *) mmap( NULL, array_bytes, PROT_READ | PROT_WRITE, MAP_SHARED| MAP_HUGETLB | MAP_ANONYMOUS, 0, 0 );


    if (array == MAP_FAILED) {
        printf("Allocation of array failed, return code is %d\n",r);
        exit(1);
    }
    // if (r != 0) {
    //     printf("Allocation of array failed, return code is %d\n",r);
    //     exit(1);
    // }

    ifstream inputFile ("array.dat");
    if (!inputFile.is_open()) {
        printf("Random walk file cannot be located.\n");
        free(array);
        exit(1);
    }

    // generating input of pointer chasing...
    // insert next entry of line from the file.
    for (uint64_t i = 0; i < ARRAY_ELEMS; ++i)
    {
        uint64_t tmp;
        inputFile >> tmp;
        array[i].next = (struct line *) tmp;
    }

    uint64_t start_cycles, start_instret, end_cycles, end_instret;

    // int retval;
    // retval=PAPI_library_init(PAPI_VER_CURRENT);
    // if (retval!=PAPI_VER_CURRENT) {
    //         fprintf(stderr,"Error initializing PAPI! %s\n",
    //                 PAPI_strerror(retval));
    //         return 0;
    // }

    // cout << "iterations are:" << ITERS << endl;
    // cout << "array elements are:" << ARRAY_ELEMS << endl;
    // cout << "array_bytes: " << array_bytes << endl; 
    // if we do not need the information for tlb and etc we can just execute counter=0 (instructions and cycles)
    for (int counter = 0; counter < 1; ++counter)
    {
        // __asm__ __volatile__("rdinstret %0" : "=r"(start_instret));
        // __asm__ __volatile__("rdcycle %0"   : "=r"(start_cycles));
        // __asm__ __volatile__("mhpmcounter3 %0"   : "=r"(start_cycles));
        // __asm__ __volatile__("mhpmcounter4 %0"   : "=r"(start_instret));
        // __asm__ __volatile__ ("csrr %0, mhpmcounter3" : "=r"(start_cycles));
        // __asm__ __volatile__ ("csrr %0, mhpmcounter4" : "=r"(start_instret));

        setPerfCounters();
        initializeProfiling(counter);
        startProfiling();

        // register int i asm("x0") = ITERS;
        register uint64_t i;
        register struct line *start; // x1 is fixed as the beginning of the array, what changes is the offset inside the array, given by x2
        register struct line *next; // rax is the next element to be read inside the array
        i=ITERS;
        start = array;
        next = 0; 
        // register uint64_t next asm("x2");
        // x2 is the next element to be read inside the array
        // it starts with the 64 bit information contained in the first position of the array (second line of assembly)
        // the 64 bit information is an offset
        // the assembly code copies to x2 the value contained at the array position (relative)0 + 64-bit offset
        // then in the next step it accesses 0 + the new offset to repeat the copy.
        // It is being forced to perform jumps inside the array

        asm __volatile__ (
            "start_loop:"
            "li x20, 1;" 
            #include "loop.h"
            "sub %0, %0, x20;"
            "bgt %0 , x0, start_loop;"
            :
            : "r" (i), "r" (start), "r" (next)
            : "x20", "x21"
        );

        __asm__ __volatile__("rdcycle %0"   : "=r"(end_cycles));
        __asm__ __volatile__("rdinstret %0" : "=r"(end_instret));
        // __asm__ __volatile__ ("csrr %0, mhpmcounter3" : "=r"(end_cycles));
        // __asm__ __volatile__ ("csrr %0, mhpmcounter4" : "=r"(end_instret));

        uint64_t cycles  = end_cycles  - start_cycles;
        uint64_t instret = end_instret - start_instret;

        cout << "cycles: " << cycles << "  insts: " << instret << endl;
        endProfiling();
        readProfiling(counter);
    }
    readExecutionTime();

    free(array);
    printf("Done walking!\n");
    return 0;
}
