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
#define CACHE_LINE 64
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
    if (r != 0) {
        printf("Allocation of array failed, return code is %d\n",r);
        exit(1);
    }

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

    // cout << "iterations are:" << ITERS << endl;
    // cout << "array elements are:" << ARRAY_ELEMS << endl;
    cout << "array_bytes: " << array_bytes << endl; 

    // if we do not need the information for tlb and etc we can just execute counter=0 (instructions and cycles)
    for (int counter = 0; counter < 2; ++counter)
    {
        
        setPerfCounters();
        initializeProfiling(counter);
        startProfiling();

        register int i asm("ecx") = ITERS;
        register struct line *start asm("rbx"); // rbx is fixed as the beginning of the array, what changes is the offset inside the array, given by rax
        start = array;
        register struct line *next asm("rax"); // rax is the next element to be read inside the array
        next = array[0].next;                  // it starts with the 64 bit information contained in the first position of the array
                                               // the 64 bit information is an offset
                                               // the assembly code copies to rax the value contained at the array position (relative)0 + 64-bit offset
                                               // then in the next step it accesses 0 + the new offset to repeat the copy.
                                               // It is being forced to perform jumps inside the array
        __asm__ __volatile__ (
            "start_loop:"
            #include "loop.h"
            "dec %ecx;"
            "jnz start_loop;"
        );

        endProfiling();
        readProfiling(counter);
    }
    readExecutionTime();

    free(array);
    printf("Done walking!\n");
    return 0;
}
