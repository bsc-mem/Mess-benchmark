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
#define ARRAY_ELEMS 5000
#endif

// size: 64 Bytes
struct line{
    struct line *next; // 8 Bytes
    int pad[14]; // 14*4 (sizeof int on cascade lake): 56 Bytes
};

struct line *array;
int seq[ARRAY_ELEMS-1];
int res[ARRAY_ELEMS];


//Taken from: http://stackoverflow.com/questions/6127503/shuffle-array-in-c
/* Arrange the ARRAY_ELEMS elements of ARRAY in random order.
   Only effective if ARRAY_ELEMS is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
void shuffle(int *array, size_t n) {
    printf("RAND_MAX = %d\n", RAND_MAX);
    srand(0);
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void walk_generator(){
    int j;
    // Init the position array
    for(j = 1; j < ARRAY_ELEMS; j++){
        seq[j - 1] = j;
    }

    // regular shuffle: only works for smaller arrays, for optane we need to change
    shuffle(seq, ARRAY_ELEMS - 1);

    // this loop below removes all the possible loops inside the array
    // that is, positions on the array that point to themselves
    res[0] = seq[0];
    int n = res[0];
    for(j = 0; j < ARRAY_ELEMS - 1; j++){
        res[n] = seq[j];
        n = res[n];
    }

    // 
    for(j = 0; j < ARRAY_ELEMS; j++){
        array[j].next = (struct line *) (long) (res[j] * 64); // multiply for 64 to be 64-byte aligned accesses 
    }
}

int main(int argc, char *argv[]) {
    int r;
    long unsigned int array_bytes = ARRAY_ELEMS * sizeof(struct line);
    r = posix_memalign((void **)&array, 64, array_bytes);
    if (r != 0) {
      printf("Allocation of array failed, return code is %d\n",r);
      exit(1);
    }
    printf("Generating random walk file.\n");
    walk_generator();
    FILE *f = fopen("array.dat", "w");
    if (f == NULL) {
        printf("File cannot be open");
    }
    fwrite(array, sizeof(*array), ARRAY_ELEMS, f);
    fclose(f);
    free(array);
    printf("Random walk file generated.\n");
    return 0;
}

