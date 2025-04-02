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

# define _XOPEN_SOURCE 600

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <float.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>
# include <mpi.h>
# include "utils.h"

/*-----------------------------------------------------------------------
 * The benchmark is based on the modified STREAM benchmark
 * (original STREAM benchmark: http://www.cs.virginia.edu/stream/).
 * Contrary to the original STREAM benchmark, it contains only the Copy kernel
 * while the specific kernel functions for different RD ratios are coded
 * in x86 assembly, using AVX instructions and non-temporal stores
 * (defined in utils.c file).
 * Also, the content of the arrays at the end is not checked.
 * We kept most of the comments from the original STREAM code.
 *
 * INSTRUCTIONS:
 *
 *	1) Benchmark requires different amounts of memory to run on different
 *     systems, depending on both the system cache size(s) and the
 *     granularity of the system timer.
 *     You should adjust the value of 'STREAM_ARRAY_SIZE' (below)
 *     to meet *both* of the following criteria:
 *       (a) Each array must be at least 4 times the size of the
 *           available cache memory. In practice, the minimum array size
 *           is about 3.8 times the cache size.
 *           Example 1: One Xeon E3 with 8 MB L3 cache
 *               STREAM_ARRAY_SIZE should be >= 4 million, giving
 *               an array size of 30.5 MB and a total memory requirement
 *               of 91.5 MB.
 *           Example 2: Two Xeon E5's with 20 MB L3 cache each (using OpenMP)
 *               STREAM_ARRAY_SIZE should be >= 20 million, giving
 *               an array size of 153 MB and a total memory requirement
 *               of 458 MB.
 *       (b) The size should be large enough so that the 'timing calibration'
 *           output by the program is at least 20 clock-ticks.
 *           Example: most versions of Windows have a 10 millisecond timer
 *               granularity.  20 "ticks" at 10 ms/tic is 200 milliseconds.
 *               If the chip is capable of 10 GB/s, it moves 2 GB in 200 msec.
 *               This means the each array must be at least 1 GB, or 128M elements.
 *
 *      Version 5.10 increases the default array size from 2 million
 *          elements to 10 million elements in response to the increasing
 *          size of L3 caches.  The new default size is large enough for caches
 *          up to 20 MB.
 *      Version 5.10 changes the loop index variables from "register int"
 *          to "ssize_t", which allows array indices >2^32 (4 billion)
 *          on properly configured 64-bit systems.  Additional compiler options
 *          (such as "-mcmodel=medium") may be required for large memory runs.
 *
 *      Array size can be set at compile time without modifying the source
 *          code for the (many) compilers that support preprocessor definitions
 *          on the compile line.  E.g.,
 *                icc -O -DSTREAM_ARRAY_SIZE=100000000 stream_mpi.c -o stream_mpi.100M
 *          will override the default size of 80M with a new size of 100M elements
 *          per array.
 */

#ifndef STREAM_ARRAY_SIZE
#   define STREAM_ARRAY_SIZE	80000000
#endif

# define HLINE "-------------------------------------------------------------\n"

# ifndef MIN
    # define MIN(x,y) ((x)<(y)?(x):(y))
# endif
# ifndef MAX
    # define MAX(x,y) ((x)>(y)?(x):(y))
# endif

#ifndef STREAM_TYPE
    #define STREAM_TYPE double
#endif

// Some compilers require an extra keyword to recognize the "restrict" qualifier.
double * __restrict a, * __restrict b;
ssize_t array_elements, array_bytes, array_alignment;

char *usage = "[-r <read_ratio>] [-p <pause>]\n";

void (*STREAM_copy_rw)(double *a_array, double *b_array,
                         ssize_t *array_size, int *pause) = NULL;

#ifdef _OPENMP
    extern int omp_get_num_threads();
#endif

int main(int argc, char *argv[])
{
    int BytesPerWord, k, rd_percentage = 50, opt;
    ssize_t j;
    int rc, numranks, myrank, pause = 0;

    /* --- SETUP --- call MPI_Init() before anything else! --- */
    rc = MPI_Init(NULL, NULL);
    if (rc != MPI_SUCCESS)
    {
        printf("ERROR: MPI Initialization failed with return code %d\n",rc);
        exit(1);
    }

    // if either of these fail there is something really screwed up!
    MPI_Comm_size(MPI_COMM_WORLD, &numranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    // Command line parsing
    while (( opt = getopt(argc, argv, ":r:p:")) != -1)
    {
        switch(opt)
        {
            case 'r':
                rd_percentage = atoi(optarg);
                if (rd_percentage < 0 || rd_percentage > 100 || rd_percentage % 2 == 1)
                {
                    if (myrank == 0)
                        printf("ERROR: RD ratio has to be even number between 50 and 100.\n");
                    MPI_Finalize();
                    exit(-1);
                }
                break;
            case 'p':
                pause = atoi(optarg);
                if (pause < 0)
                {
                    if (myrank == 0)
                        printf("ERROR: Pause has to be a non-negative number.\n");
                    MPI_Finalize();
                    exit(-1);
                }
                break;
            default:
                if (myrank == 0)
                    print_usage(argv, usage);
                MPI_Finalize();
                exit(-1);
        }
    }

    if (optind < argc || argc != 5)
    {
        if (myrank == 0)
            print_usage(argv, usage);
        MPI_Finalize();
        exit(-1);
    }

    // End of command line partsing

    // Assigning the right asm function based on the RD ratio
    switch(rd_percentage)
    {
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
    array_elements = STREAM_ARRAY_SIZE / numranks;              // don't worry about rounding vs truncation
    array_alignment = 64;                                       // Can be modified -- provides partial support for adjusting relative alignment

    // Dynamically allocate the three arrays using "posix_memalign()"
    array_bytes = array_elements * sizeof(STREAM_TYPE);
    k = posix_memalign((void **)&a, array_alignment, array_bytes);
    if (k != 0)
    {
        printf("Rank %d: Allocation of array a failed, return code is %d\n",myrank,k);
        MPI_Abort(MPI_COMM_WORLD, 2);
        exit(1);
    }
    k = posix_memalign((void **)&b, array_alignment, array_bytes);
    if (k != 0)
    {
        printf("Rank %d: Allocation of array b failed, return code is %d\n",myrank,k);
        MPI_Abort(MPI_COMM_WORLD, 2);
        exit(1);
    }

    // Initial informational printouts -- rank 0 handles all the output
    if (myrank == 0)
    {
        printf(HLINE);
        printf("$ Memory bandwidth load kernel $\n");
        printf(HLINE);
        BytesPerWord = sizeof(STREAM_TYPE);
        printf("This system uses %d bytes per array element.\n",
        BytesPerWord);

        printf(HLINE);
        #ifdef N
            printf("*****  WARNING: ******\n");
            printf("      It appears that you set the preprocessor variable N when compiling this code.\n");
            printf("      This version of the code uses the preprocesor variable STREAM_ARRAY_SIZE to control the array size\n");
            printf("      Reverting to default value of STREAM_ARRAY_SIZE=%llu\n",(unsigned long long) STREAM_ARRAY_SIZE);
            printf("*****  WARNING: ******\n");
        #endif

        printf("Total Aggregate Array size = %llu (elements)\n" , (unsigned long long) STREAM_ARRAY_SIZE);
        printf("Total Aggregate Memory per array = %.1f MiB (= %.1f GiB).\n",
          BytesPerWord * ( (double) STREAM_ARRAY_SIZE / 1024.0/1024.0),
          BytesPerWord * ( (double) STREAM_ARRAY_SIZE / 1024.0/1024.0/1024.0));
        printf("Total Aggregate memory required = %.1f MiB (= %.1f GiB).\n",
          (2.0 * BytesPerWord) * ( (double) STREAM_ARRAY_SIZE / 1024.0/1024.),
          (2.0 * BytesPerWord) * ( (double) STREAM_ARRAY_SIZE / 1024.0/1024./1024.));
        printf("Data is distributed across %d MPI ranks\n",numranks);
        printf("   Array size per MPI rank = %llu (elements)\n" , (unsigned long long) array_elements);
        printf("   Memory per array per MPI rank = %.1f MiB (= %.1f GiB).\n",
          BytesPerWord * ( (double) array_elements / 1024.0/1024.0),
          BytesPerWord * ( (double) array_elements / 1024.0/1024.0/1024.0));
        printf("   Total memory per MPI rank = %.1f MiB (= %.1f GiB).\n",
          (2.0 * BytesPerWord) * ( (double) array_elements / 1024.0/1024.),
          (2.0 * BytesPerWord) * ( (double) array_elements / 1024.0/1024./1024.));

        printf(HLINE);
        printf("The kernel will be executed indefinitely.\n");

        #ifdef _OPENMP
            printf(HLINE);
            #pragma omp parallel
            {
                #pragma omp master
                {
                    k = omp_get_num_threads();
                    printf ("Number of Threads requested for each MPI rank = %i\n",k);
                }
            }
        #endif

        #ifdef _OPENMP
            k = 0;
            #pragma omp parallel
            #pragma omp atomic
                k++;
                printf ("Number of Threads counted for rank 0 = %i\n",k);
        #endif

    }

    /* --- SETUP --- initialize arrays --- */

#ifdef _OPENMP
    #pragma omp parallel for
#endif
    for (j=0; j<array_elements; j++)
    {
        a[j] = 1.0;
        b[j] = 2.0;
    }

    /*	--- MAIN LOOP --- repeat indefinitely --- */

    while (1)
    {
        // kernel : Copy
#ifdef _OPENMP
        #pragma omp parallel
#endif
        {
            STREAM_copy_rw(a, b, &array_elements, &pause);
        }
    }


    free(a);
    free(b);

    MPI_Finalize();
    return(0);
}

