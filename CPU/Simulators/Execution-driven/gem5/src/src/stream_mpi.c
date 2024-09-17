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


#define _XOPEN_SOURCE 600

#include "utils.h"
#include <float.h>
#include <limits.h>
#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#ifndef STREAM_ARRAY_SIZE
#define STREAM_ARRAY_SIZE 2000000
#endif

#define CORE_NUMBER 16

#define HLINE "-------------------------------------------------------------\n"

#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif

#ifndef STREAM_TYPE
#define STREAM_TYPE double
#endif

// Some compilers require an extra keyword to recognize the "restrict"
// qualifier.
double *__restrict a, *__restrict b;
ssize_t array_elements, array_bytes, array_alignment;

char *usage = "[-r <read_ratio>] [-p <pause>]\n";

void (*STREAM_copy_rw)(double *a_array, double *b_array,
                       unsigned long long *array_size, const int *pause) = NULL;

void roi_begin() {
  // m5_resetstats
  __asm__ __volatile__("mov x0, 0; mov x1, 0; .inst 0XFF000110 | (0x40 << 16);"
                       :
                       :
                       : "x0", "x1");
}

void roi_end() {
  // m5_dumpstats
  __asm__ __volatile__("mov x0, 0; mov x1, 0; .inst 0xFF000110 | (0x41 << 16);"
                       :
                       :
                       : "x0", "x1");

  // m5_exit
  __asm__ __volatile__("mov x0, 0;            .inst 0XFF000110 | (0x21 << 16);"
                       :
                       :
                       : "x0");
}

extern int omp_get_num_threads();

int main(int argc, char *argv[]) {
  int BytesPerWord, k, rd_percentage = 50, opt;
  ssize_t j;
  int rc, numranks, myrank, pause = 0;

  // Command line parsing
  while ((opt = getopt(argc, argv, ":r:p:")) != -1) {
    switch (opt) {
    case 'r':
      rd_percentage = atoi(optarg);
      if (rd_percentage < 0 || rd_percentage > 100 || rd_percentage % 2 == 1) {
        printf("ERROR: RD ratio has to be even number between 0 and 100.\n");
        exit(-1);
      }
      break;
    case 'p':
      pause = atoi(optarg);
      if (pause < 0) {
        printf("ERROR: Pause has to be a non-negative number.\n");
        exit(-1);
      }
      break;
    default:
      print_usage(argv, usage);
      exit(-1);
    }
  }

  // End of command line partsing

  // Assigning the right asm function based on the RD ratio
  switch (rd_percentage) {
  case 0:
    STREAM_copy_rw = &STREAM_copy_0;
    break;
  case 2:
    STREAM_copy_rw = &STREAM_copy_2;
    break;
  case 4:
    STREAM_copy_rw = &STREAM_copy_4;
    break;
  case 6:
    STREAM_copy_rw = &STREAM_copy_6;
    break;
  case 8:
    STREAM_copy_rw = &STREAM_copy_8;
    break;
  case 10:
    STREAM_copy_rw = &STREAM_copy_10;
    break;
  case 12:
    STREAM_copy_rw = &STREAM_copy_12;
    break;
  case 14:
    STREAM_copy_rw = &STREAM_copy_14;
    break;
  case 16:
    STREAM_copy_rw = &STREAM_copy_16;
    break;
  case 18:
    STREAM_copy_rw = &STREAM_copy_18;
    break;
  case 20:
    STREAM_copy_rw = &STREAM_copy_20;
    break;
  case 22:
    STREAM_copy_rw = &STREAM_copy_22;
    break;
  case 24:
    STREAM_copy_rw = &STREAM_copy_24;
    break;
  case 26:
    STREAM_copy_rw = &STREAM_copy_26;
    break;
  case 28:
    STREAM_copy_rw = &STREAM_copy_28;
    break;
  case 30:
    STREAM_copy_rw = &STREAM_copy_30;
    break;
  case 32:
    STREAM_copy_rw = &STREAM_copy_32;
    break;
  case 34:
    STREAM_copy_rw = &STREAM_copy_34;
    break;
  case 36:
    STREAM_copy_rw = &STREAM_copy_36;
    break;
  case 38:
    STREAM_copy_rw = &STREAM_copy_38;
    break;
  case 40:
    STREAM_copy_rw = &STREAM_copy_40;
    break;
  case 42:
    STREAM_copy_rw = &STREAM_copy_42;
    break;
  case 44:
    STREAM_copy_rw = &STREAM_copy_44;
    break;
  case 46:
    STREAM_copy_rw = &STREAM_copy_46;
    break;
  case 48:
    STREAM_copy_rw = &STREAM_copy_48;
    break;
  case 50:
    STREAM_copy_rw = &STREAM_copy_50;
    break;
  case 52:
    STREAM_copy_rw = &STREAM_copy_52;
    break;
  case 54:
    STREAM_copy_rw = &STREAM_copy_54;
    break;
  case 56:
    STREAM_copy_rw = &STREAM_copy_56;
    break;
  case 58:
    STREAM_copy_rw = &STREAM_copy_58;
    break;
  case 60:
    STREAM_copy_rw = &STREAM_copy_60;
    break;
  case 62:
    STREAM_copy_rw = &STREAM_copy_62;
    break;
  case 64:
    STREAM_copy_rw = &STREAM_copy_64;
    break;
  case 66:
    STREAM_copy_rw = &STREAM_copy_66;
    break;
  case 68:
    STREAM_copy_rw = &STREAM_copy_68;
    break;
  case 70:
    STREAM_copy_rw = &STREAM_copy_70;
    break;
  case 72:
    STREAM_copy_rw = &STREAM_copy_72;
    break;
  case 74:
    STREAM_copy_rw = &STREAM_copy_74;
    break;
  case 76:
    STREAM_copy_rw = &STREAM_copy_76;
    break;
  case 78:
    STREAM_copy_rw = &STREAM_copy_78;
    break;
  case 80:
    STREAM_copy_rw = &STREAM_copy_80;
    break;
  case 82:
    STREAM_copy_rw = &STREAM_copy_82;
    break;
  case 84:
    STREAM_copy_rw = &STREAM_copy_84;
    break;
  case 86:
    STREAM_copy_rw = &STREAM_copy_86;
    break;
  case 88:
    STREAM_copy_rw = &STREAM_copy_88;
    break;
  case 90:
    STREAM_copy_rw = &STREAM_copy_90;
    break;
  case 92:
    STREAM_copy_rw = &STREAM_copy_92;
    break;
  case 94:
    STREAM_copy_rw = &STREAM_copy_94;
    break;
  case 96:
    STREAM_copy_rw = &STREAM_copy_96;
    break;
  case 98:
    STREAM_copy_rw = &STREAM_copy_98;
    break;
  case 100:
    STREAM_copy_rw = &STREAM_copy_100;
    break;
  default:
    STREAM_copy_rw = &STREAM_copy_50;
  }

  /* --- distribute requested storage across MPI ranks --- */
  array_elements = STREAM_ARRAY_SIZE; // / numranks;              // don't worry
                                      // about rounding vs truncation
  array_alignment = 64; // Can be modified -- provides partial support for
                        // adjusting relative alignment

  // Dynamically allocate the three arrays using "posix_memalign()"
  array_bytes = CORE_NUMBER * array_elements * sizeof(STREAM_TYPE);
  k = posix_memalign((void **)&a, array_alignment, array_bytes);
  if (k != 0) {
    printf("Allocation of array a failed, return code is %d\n", k);
    exit(1);
  }
  k = posix_memalign((void **)&b, array_alignment, array_bytes);
  if (k != 0) {
    printf("Allocation of array b failed, return code is %d\n", k);
    exit(1);
  }

  printf(HLINE);
#pragma omp parallel
  {
#pragma omp master
    {
      k = omp_get_num_threads();
      printf("Number of Threads requested = %i\n", k);
    }
  }

  /* --- SETUP --- initialize arrays --- */

#pragma omp parallel for
  for (j = 0; j < array_elements * CORE_NUMBER; j++) {
    a[j] = 1.0;
    b[j] = 2.0;
  }

  roi_begin();
#pragma omp parallel for
  for (j = 0; j < CORE_NUMBER; ++j) {
    STREAM_copy_rw(a + (j * array_elements), b + (j * array_elements),
                   &array_elements, &pause);
  }

  roi_end();
  return 0;
}
