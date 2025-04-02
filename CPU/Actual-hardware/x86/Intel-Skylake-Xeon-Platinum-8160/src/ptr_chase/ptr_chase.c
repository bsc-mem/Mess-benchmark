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

#ifndef ARRAY_ELEMS
#pragma message "ARRAY_ELEMS not defined. Using the default value."
#define ARRAY_ELEMS 524288
#endif

#ifndef ITERS
#pragma message "ITERS not defined. Using the default value."
#define ITERS 5000
#endif

struct line{
    struct line *next;
    int pad[14];
};

struct line *array;

int main(int argc, char *argv[]) {
    int r;
    long unsigned int array_bytes = ARRAY_ELEMS * sizeof(struct line); // get the size of the array in bytes (num of elements of the size of the struct)
    printf("%d\n", sizeof(struct line *));
    r = posix_memalign((void **)&array, 64, array_bytes); // allocate a space in mem to receive the amount of information calculated
                                                          // aligned to 64
    if (r != 0) {
        printf("Allocation of array failed, return code is %d\n",r);
        exit(1);
    }
    FILE *f = fopen("array.dat","r");
    if (f == NULL) {
        printf("Random walk file cannot be located.\n");
        free(array);
        exit(1);
    }
    r = fread(array,sizeof(*array),ARRAY_ELEMS,f); // from the file f, reads #ARRAY_ELEMS of the size of a line
                                                   // size of line = size of each array element (which is in fact a cache line being read, 64 bytes)
    if (r != ARRAY_ELEMS) {
        printf("Reading of the array from file failed, return code is %d\n",r);
        free(array);
        exit(1);
    }
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
    free(array);
    printf("Done walking!\n");
    return 0;
}
