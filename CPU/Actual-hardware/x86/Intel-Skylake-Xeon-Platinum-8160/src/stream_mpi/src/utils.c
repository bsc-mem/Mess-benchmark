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

# include <stdio.h>
# include <unistd.h>
# include "utils.h"

void print_usage(char *argv[], char* usage)
{
    fprintf(stderr,"Usage: %s %s", argv[0], usage);
}

// Notes:
// rdi is source index register
// zmm0 and zmm1 are 512 bit (64 Byte) register
// vmovupd 64(%r10,%rbx,8), %zmm0 -> below line:
// means move 64 Byte of data from address 64(%r10,%rbx,8) -> %r10 + %rbx*8 + 64 (each line is a Byte)

void STREAM_copy_0(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_0:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4608(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4672(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4736(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4800(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4864(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4928(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4992(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5056(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5120(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5184(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5248(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5312(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5376(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5440(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5504(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5568(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5632(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5696(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5760(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5824(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5888(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5952(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 6016(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 6080(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 6144(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 6208(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 6272(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 6336(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $800, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_0;\n"

    );

}


void STREAM_copy_2(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_2:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4608(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4672(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4736(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4800(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4864(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4928(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4992(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5056(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5120(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5184(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5248(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5312(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5376(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5440(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5504(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5568(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5632(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5696(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5760(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5824(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5888(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5952(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 6016(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 6080(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 6144(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 6208(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $784, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_2;\n"

    );

}

void STREAM_copy_4(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_4:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4608(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4672(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4736(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4800(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4864(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4928(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4992(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5056(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5120(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5184(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5248(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5312(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5376(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5440(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5504(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5568(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5632(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5696(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5760(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5824(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5888(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5952(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 6016(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 6080(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $768, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_4;\n"

    );

}

void STREAM_copy_6(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_6:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4608(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4672(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4736(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4800(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4864(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4928(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4992(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5056(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5120(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5184(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5248(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5312(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5376(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5440(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5504(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5568(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5632(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5696(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5760(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5824(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5888(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5952(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $752, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_6;\n"

    );

}

void STREAM_copy_8(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_8:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4608(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4672(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4736(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4800(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4864(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4928(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4992(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5056(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5120(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5184(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5248(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5312(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5376(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5440(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5504(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5568(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5632(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5696(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5760(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5824(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $736, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_8;\n"

    );

}

void STREAM_copy_10(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_10:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4608(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4672(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4736(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4800(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4864(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4928(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4992(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5056(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5120(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5184(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5248(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5312(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5376(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5440(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5504(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5568(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5632(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5696(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $720, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_10;\n"

    );

}


void STREAM_copy_12(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_12:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4608(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4672(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4736(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4800(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4864(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4928(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4992(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5056(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5120(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5184(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5248(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5312(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5376(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5440(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5504(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5568(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $704, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_12;\n"

    );

}

void STREAM_copy_14(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_14:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4608(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4672(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4736(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4800(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4864(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4928(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4992(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5056(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5120(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5184(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5248(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5312(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 5376(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5440(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $688, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_14;\n"

    );

}


void STREAM_copy_16(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_16:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4608(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4672(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4736(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4800(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4864(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4928(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4992(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5056(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 5120(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5184(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5248(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5312(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $672, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_16;\n"

    );

}


void STREAM_copy_18(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_18:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4608(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4672(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4736(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4800(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4864(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4928(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4992(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5056(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5120(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5184(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $656, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_18;\n"

    );

}

void STREAM_copy_20(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_20:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4608(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4672(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4736(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4800(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4864(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4928(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4992(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 5056(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $640, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_20;\n"

    );

}


void STREAM_copy_22(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_22:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4608(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4672(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4736(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4800(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4864(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4928(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $624, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_22;\n"

    );

}


void STREAM_copy_24(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_24:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "vmovupd   1472(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4608(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4672(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4736(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4800(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $608, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_24;\n"

    );

}

void STREAM_copy_26(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_26:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd   1472(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd   1536(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd   1600(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4608(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4672(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $592, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_26;\n"

    );

}

void STREAM_copy_28(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_28:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd   1472(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd   1536(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd   1600(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd   1664(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd   1728(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4480(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4544(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $576, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_28;\n"

    );

}


void STREAM_copy_30(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_30:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd   1472(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd   1536(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd   1600(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd   1664(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd   1728(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd   1792(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd   1856(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4352(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4416(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $560, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_30;\n"

    );

}

void STREAM_copy_32(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_32:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd   1472(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd   1536(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd   1600(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd   1664(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd   1728(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd   1792(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd   1856(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd   1920(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd   1984(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4224(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4288(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $544, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_32;\n"

    );

}

void STREAM_copy_34(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_34:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   1472(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd   1536(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd   1600(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd   1664(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   1728(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd   1792(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   1856(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd   1920(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   1984(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd   2048(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd   2112(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4096(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4160(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $528, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_34;\n"

    );

}

void STREAM_copy_36(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_36:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   1472(%r11,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd   1536(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd   1600(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd   1664(%r11,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   1728(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd   1792(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   1856(%r11,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd   1920(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   1984(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd   2048(%r11,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd   2112(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd   2176(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   2240(%r11,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3968(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 4032(%r10,%rbx,8);\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $512, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_36;\n"

    );

}

void STREAM_copy_38(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_38:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   1472(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd   1536(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd   1600(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd   1664(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   1728(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd   1792(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   1856(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd   1920(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   1984(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd   2048(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd   2112(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd   2176(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   2240(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd   2304(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd   2368(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3840(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3904(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $496, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_38;\n"

    );

}

void STREAM_copy_40(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_40:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   1472(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd   1536(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd   1600(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd   1664(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   1728(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd   1792(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   1856(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd   1920(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   1984(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd   2048(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd   2112(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd   2176(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   2240(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd   2304(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd   2368(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd   2432(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd   2496(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3712(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3776(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $480, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_40;\n"

    );

}

void STREAM_copy_42(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_42:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   1472(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd   1536(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd   1600(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd   1664(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   1728(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd   1792(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   1856(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd   1920(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   1984(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd   2048(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd   2112(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd   2176(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   2240(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd   2304(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd   2368(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd   2432(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd   2496(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd   2560(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd   2624(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3584(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3648(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $464, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_42;\n"

    );

}

void STREAM_copy_44(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_44:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   1472(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd   1536(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd   1600(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd   1664(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   1728(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd   1792(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   1856(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd   1920(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   1984(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd   2048(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd   2112(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd   2176(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   2240(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd   2304(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd   2368(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd   2432(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd   2496(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd   2560(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd   2624(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd   2688(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd   2752(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3456(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3520(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $448, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_44;\n"

    );

}

void STREAM_copy_46(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_46:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   1472(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd   1536(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd   1600(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd   1664(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   1728(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd   1792(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   1856(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd   1920(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   1984(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd   2048(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd   2112(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd   2176(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   2240(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd   2304(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd   2368(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd   2432(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd   2496(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd   2560(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd   2624(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd   2688(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd   2752(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd   2816(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd   2880(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3328(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3392(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $432, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_46;\n"

    );

}

void STREAM_copy_48(double *a_array, double *b_array, ssize_t *array_size, int *pause)

{

    register double *a asm("r10");

    a = a_array;

    register double *b asm("r11");

    b = b_array;



    register ssize_t i asm("rbx");

    i = 0;

    register ssize_t n asm("r12");

    n = *array_size;

    register int *p asm("r15");

    p = pause;



    asm (

      "..L_48:\n"

        "vmovupd  %zmm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1152(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   1472(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1536(%r10,%rbx,8);\n"
        "vmovupd   1536(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r10,%rbx,8);\n"
        "vmovupd   1600(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r10,%rbx,8);\n"
        "vmovupd   1664(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   1728(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r10,%rbx,8);\n"
        "vmovupd   1792(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r10,%rbx,8);\n"
        "vmovupd   1856(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 1920(%r10,%rbx,8);\n"
        "vmovupd   1920(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   1984(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r10,%rbx,8);\n"
        "vmovupd   2048(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2112(%r10,%rbx,8);\n"
        "vmovupd   2112(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r10,%rbx,8);\n"
        "vmovupd   2176(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r10,%rbx,8);\n"
        "vmovupd   2240(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2304(%r10,%rbx,8);\n"
        "vmovupd   2304(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2368(%r10,%rbx,8);\n"
        "vmovupd   2368(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r10,%rbx,8);\n"
        "vmovupd   2432(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2496(%r10,%rbx,8);\n"
        "vmovupd   2496(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2560(%r10,%rbx,8);\n"
        "vmovupd   2560(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2624(%r10,%rbx,8);\n"
        "vmovupd   2624(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2688(%r10,%rbx,8);\n"
        "vmovupd   2688(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2752(%r10,%rbx,8);\n"
        "vmovupd   2752(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2816(%r10,%rbx,8);\n"
        "vmovupd   2816(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 2880(%r10,%rbx,8);\n"
        "vmovupd   2880(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2944(%r10,%rbx,8);\n"
        "vmovupd   2944(%r11,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3008(%r10,%rbx,8);\n"
        "vmovupd   3008(%r11,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd  %zmm1, 3072(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3136(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3200(%r10,%rbx,8);\n"
        "vmovupd  %zmm1, 3264(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $416, %rbx;\n"

        "cmp       %r12, %rbx;\n"

        "jb        ..L_48;\n"

    );

}

void STREAM_copy_50(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_50:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r11,%rbx,8);\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1728(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r11,%rbx,8);\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r11,%rbx,8);\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r11,%rbx,8);\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2112(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r11,%rbx,8);\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2304(%r11,%rbx,8);\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2368(%r11,%rbx,8);\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2496(%r11,%rbx,8);\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2560(%r11,%rbx,8);\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2624(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2688(%r11,%rbx,8);\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2752(%r11,%rbx,8);\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2816(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2880(%r11,%rbx,8);\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2944(%r11,%rbx,8);\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3008(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3072(%r11,%rbx,8);\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3136(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $400, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_50;\n"
    );
}

void STREAM_copy_52(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_52:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r11,%rbx,8);\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1728(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r11,%rbx,8);\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r11,%rbx,8);\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r11,%rbx,8);\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2112(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r11,%rbx,8);\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2304(%r11,%rbx,8);\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2368(%r11,%rbx,8);\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2496(%r11,%rbx,8);\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2560(%r11,%rbx,8);\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2624(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2688(%r11,%rbx,8);\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2752(%r11,%rbx,8);\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2816(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2880(%r11,%rbx,8);\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2944(%r11,%rbx,8);\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 3008(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $416, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_52;\n"
    );
}

void STREAM_copy_54(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_54:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r11,%rbx,8);\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1728(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r11,%rbx,8);\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r11,%rbx,8);\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r11,%rbx,8);\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2112(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r11,%rbx,8);\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2304(%r11,%rbx,8);\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2368(%r11,%rbx,8);\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2496(%r11,%rbx,8);\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2560(%r11,%rbx,8);\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2624(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2688(%r11,%rbx,8);\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2752(%r11,%rbx,8);\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2816(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2880(%r11,%rbx,8);\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $432, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_54;\n"
    );
}

void STREAM_copy_56(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_56:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r11,%rbx,8);\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1728(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r11,%rbx,8);\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r11,%rbx,8);\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r11,%rbx,8);\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2112(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r11,%rbx,8);\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2304(%r11,%rbx,8);\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2368(%r11,%rbx,8);\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2496(%r11,%rbx,8);\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2560(%r11,%rbx,8);\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2624(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2688(%r11,%rbx,8);\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2752(%r11,%rbx,8);\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $448, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_56;\n"
    );
}

void STREAM_copy_58(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_58:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r11,%rbx,8);\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1728(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r11,%rbx,8);\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r11,%rbx,8);\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r11,%rbx,8);\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2112(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r11,%rbx,8);\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2304(%r11,%rbx,8);\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2368(%r11,%rbx,8);\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2496(%r11,%rbx,8);\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2560(%r11,%rbx,8);\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2624(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $464, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_58;\n"
    );
}

void STREAM_copy_60(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_60:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r11,%rbx,8);\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1728(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r11,%rbx,8);\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r11,%rbx,8);\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r11,%rbx,8);\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2112(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r11,%rbx,8);\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2304(%r11,%rbx,8);\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2368(%r11,%rbx,8);\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2432(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2496(%r11,%rbx,8);\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $480, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_60;\n"
    );
}

void STREAM_copy_62(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_62:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r11,%rbx,8);\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1728(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r11,%rbx,8);\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r11,%rbx,8);\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r11,%rbx,8);\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2112(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r11,%rbx,8);\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2304(%r11,%rbx,8);\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2368(%r11,%rbx,8);\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $496, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_62;\n"
    );
}

void STREAM_copy_64(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_64:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r11,%rbx,8);\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1728(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r11,%rbx,8);\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r11,%rbx,8);\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r11,%rbx,8);\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2112(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2176(%r11,%rbx,8);\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2240(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $512, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_64;\n"
    );
}

void STREAM_copy_66(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_66:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r11,%rbx,8);\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1728(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r11,%rbx,8);\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r11,%rbx,8);\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r11,%rbx,8);\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2048(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 2112(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $528, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_66;\n"
    );
}

void STREAM_copy_68(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_68:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r11,%rbx,8);\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r11,%rbx,8);\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r11,%rbx,8);\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1728(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r11,%rbx,8);\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1920(%r11,%rbx,8);\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1984(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $544, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_68;\n"
    );
}

void STREAM_copy_70(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_70:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r11,%rbx,8);\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r11,%rbx,8);\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r11,%rbx,8);\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1728(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1792(%r11,%rbx,8);\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1856(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $560, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_70;\n"
    );
}

void STREAM_copy_72(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_72:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r11,%rbx,8);\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r11,%rbx,8);\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1664(%r11,%rbx,8);\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1728(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $576, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_72;\n"
    );
}

void STREAM_copy_74(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_74:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r11,%rbx,8);\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1536(%r11,%rbx,8);\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1600(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4608(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4672(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $592, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_74;\n"
    );
}

void STREAM_copy_76(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_76:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1408(%r11,%rbx,8);\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1472(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4608(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4672(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4736(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4800(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $608, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_76;\n"
    );
}

void STREAM_copy_78(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_78:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1280(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4608(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4672(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4736(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4800(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4864(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4928(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $624, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_78;\n"
    );
}

void STREAM_copy_80(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_80:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4608(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4672(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4736(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4800(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   4864(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4928(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4992(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5056(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1216(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $640, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_80;\n"
    );
}

void STREAM_copy_82(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_82:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd  %zmm1, 1024(%r11,%rbx,8);\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 1088(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4608(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4672(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4736(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4800(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4864(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4928(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4992(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5056(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5120(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5184(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $656, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_82;\n"
    );
}

void STREAM_copy_84(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_84:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4608(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4672(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4736(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 896(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4800(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4864(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4928(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4992(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5056(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 960(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5120(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5184(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5248(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5312(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $672, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_84;\n"
    );
}

void STREAM_copy_86(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_86:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4608(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4672(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4736(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4800(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4864(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4928(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd  %zmm1, 768(%r11,%rbx,8);\n"
        "vmovupd   4992(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5056(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5120(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5184(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5248(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5312(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 832(%r11,%rbx,8);\n"
        "vmovupd   5376(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5440(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $688, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_86;\n"
    );
}

void STREAM_copy_88(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_88:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4608(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4672(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4736(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4800(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4864(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 640(%r11,%rbx,8);\n"
        "vmovupd   4928(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4992(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5056(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5120(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5184(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5248(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5312(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 704(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5376(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5440(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5504(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5568(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $704, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_88;\n"
    );
}

void STREAM_copy_90(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_90:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "vmovupd   4608(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4672(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4736(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4800(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4864(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4928(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4992(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5056(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5120(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 512(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5184(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5248(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5312(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5376(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5440(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5504(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5568(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5632(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5696(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 576(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $720, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_90;\n"
    );
}

void STREAM_copy_92(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_92:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4608(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4672(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4736(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4800(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4864(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 384(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4928(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4992(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5056(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5120(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5184(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5248(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5312(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5376(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5440(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5504(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5568(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5632(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5696(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5760(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5824(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $736, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_92;\n"
    );
}

void STREAM_copy_94(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_94:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4608(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4672(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4736(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 256(%r11,%rbx,8);\n"
        "vmovupd   4800(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4864(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4928(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4992(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5056(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5120(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5184(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5248(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5312(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5376(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5440(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5504(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5568(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5632(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5696(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5760(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5824(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5888(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5952(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $752, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_94;\n"
    );
}

void STREAM_copy_96(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_96:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 128(%r11,%rbx,8);\n"
        "vmovupd   4608(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4672(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4736(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4800(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4864(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4928(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4992(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5056(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5120(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5184(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5248(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5312(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5376(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5440(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5504(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5568(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5632(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5696(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5760(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5824(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5888(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5952(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   6016(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   6080(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 192(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $768, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_96;\n"
    );
}

void STREAM_copy_98(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_98:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, (%r11,%rbx,8);\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4608(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4672(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4736(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4800(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4864(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4928(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4992(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5056(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5120(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5184(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5248(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5312(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5376(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5440(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5504(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5568(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5632(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5696(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5760(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5824(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5888(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5952(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   6016(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   6080(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   6144(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   6208(%r10,%rbx,8), %zmm0;\n"
        "vmovupd  %zmm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $784, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_98;\n"
    );
}

void STREAM_copy_100(double *a_array, double *b_array, ssize_t *array_size, int *pause)
{
    register double *a asm("r10");
    a = a_array;
    register double *b asm("r11");
    b = b_array;

    register ssize_t i asm("rbx");
    i = 0;
    register ssize_t n asm("r12");
    n = *array_size;
    register int *p asm("r15");
    p = pause;

    asm (
      "..L_100:\n"
        "vmovupd   (%r10,%rbx,8), %zmm0;\n"
        "vmovupd   64(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   128(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   192(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   256(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   320(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   448(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   512(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   576(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   640(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   704(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   832(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   896(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   960(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2688(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3072(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3200(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3264(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3328(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3392(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3456(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3520(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3584(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3648(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3712(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3776(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3840(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3904(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   3968(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4032(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4096(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4160(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4224(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4288(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4352(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4416(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4480(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4544(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4608(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4672(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4736(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4800(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4864(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   4928(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   4992(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5056(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5120(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5184(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5248(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5312(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5376(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5440(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5504(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5568(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5632(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5696(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   5760(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5824(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5888(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   5952(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   6016(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   6080(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   6144(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   6208(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   6272(%r10,%rbx,8), %zmm0;\n"
        "vmovupd   6336(%r10,%rbx,8), %zmm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $800, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_100;\n"
    );
}
