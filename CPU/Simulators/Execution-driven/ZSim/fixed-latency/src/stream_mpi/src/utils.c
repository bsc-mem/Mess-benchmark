/*------------------------------------------------------------------------------
* Copyright (c) 2019, Milan Radulovic
*                     Rommel Sanchez Verdejo
*                     Paul Carpenter
*                     Petar Radojkovic
*                     Bruce Jacob
*                     Eduard Ayguade
*                     Contact: milan.radulovic [at] bsc [dot] es
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
------------------------------------------------------------------------------*/

# include <stdio.h>
# include <unistd.h>
# include "utils.h"

void print_usage(char *argv[], char* usage)
{
    fprintf(stderr,"Usage: %s %s", argv[0], usage);
}

// Notes:
// rdi is source index register
// ymm0 and ymm1 are 256 bit (32 Byte) register
// vmovupd   (%r10,%rbx,8), %ymm0 -> below line:
// means move 32 Byte of data from address 32(%r10,%rbx,8) -> %r10 + %rbx*8 + 32 (each line is a Byte)

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2304(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2336(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2368(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2400(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2432(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2464(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2496(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2528(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2560(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2592(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2624(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2656(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2688(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2720(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2752(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2784(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2816(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2848(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2880(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2912(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2944(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2976(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 3008(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 3040(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 3072(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 3104(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 3136(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 3168(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $400, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2304(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2336(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2368(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2400(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2432(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2464(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2496(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2528(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2560(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2592(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2624(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2656(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2688(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2720(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2752(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2784(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2816(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2848(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2880(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2912(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2944(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2976(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 3008(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 3040(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 3072(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 3104(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $392, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2304(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2336(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2368(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2400(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2432(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2464(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2496(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2528(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2560(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2592(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2624(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2656(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2688(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2720(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2752(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2784(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2816(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2848(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2880(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2912(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2944(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2976(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 3008(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 3040(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $384, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2304(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2336(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2368(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2400(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2432(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2464(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2496(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2528(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2560(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2592(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2624(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2656(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2688(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2720(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2752(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2784(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2816(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2848(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2880(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2912(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2944(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2976(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $376, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2304(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2336(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2368(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2400(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2432(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2464(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2496(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2528(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2560(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2592(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2624(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2656(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2688(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2720(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2752(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2784(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2816(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2848(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2880(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2912(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $368, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2304(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2336(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2368(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2400(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2432(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2464(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2496(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2528(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2560(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2592(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2624(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2656(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2688(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2720(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2752(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2784(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2816(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2848(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $360, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2304(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2336(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2368(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2400(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2432(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2464(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2496(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2528(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2560(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2592(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2624(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2656(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2688(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2720(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2752(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2784(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $352, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2304(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2336(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2368(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2400(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2432(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2464(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2496(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2528(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2560(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2592(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2624(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2656(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2688(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2720(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $344, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2304(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2336(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2368(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2400(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2432(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2464(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2496(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2528(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2560(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2592(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2624(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2656(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $336, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2304(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2336(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2368(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2400(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2432(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2464(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2496(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2528(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2560(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2592(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $328, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2304(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2336(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2368(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2400(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2432(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2464(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2496(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2528(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $320, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovupd   672(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2304(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2336(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2368(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2400(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2432(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2464(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $312, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovupd   672(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "vmovupd   736(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2304(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2336(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2368(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2400(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $304, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovupd   672(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovupd   736(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovupd   800(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2304(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2336(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $296, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovupd   672(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovupd   736(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovupd   800(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovupd   864(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2240(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2272(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $288, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovupd   672(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovupd   736(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovupd   800(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovupd   864(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovupd   928(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2176(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2208(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $280, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovupd   672(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovupd   736(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovupd   800(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovupd   864(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovupd   928(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovupd   992(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2112(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2144(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $272, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovupd   672(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   736(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovupd   800(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   864(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   928(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovupd   992(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovupd   1056(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2048(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2080(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $264, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovupd   672(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   736(%r11,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovupd   800(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   864(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   928(%r11,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovupd   992(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovupd   1056(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   1120(%r11,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1984(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 2016(%r10,%rbx,8);\n"
        "mov       %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $256, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovupd   672(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   736(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovupd   800(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   864(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   928(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovupd   992(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovupd   1056(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   1120(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovupd   1184(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1920(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1952(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $248, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovupd   672(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   736(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovupd   800(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   864(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   928(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovupd   992(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovupd   1056(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   1120(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovupd   1184(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovupd   1248(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1856(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1888(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $240, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovupd   672(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   736(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovupd   800(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   864(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   928(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovupd   992(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovupd   1056(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   1120(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovupd   1184(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovupd   1248(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovupd   1312(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1792(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1824(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $232, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovupd   672(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   736(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovupd   800(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   864(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   928(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovupd   992(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovupd   1056(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   1120(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovupd   1184(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovupd   1248(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovupd   1312(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovupd   1376(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1728(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1760(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $224, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovupd   672(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   736(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovupd   800(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   864(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   928(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovupd   992(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovupd   1056(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   1120(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovupd   1184(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovupd   1248(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovupd   1312(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovupd   1376(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovupd   1440(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1664(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1696(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $216, %rbx;\n"

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

        "vmovntpd  %ymm1, (%r10,%rbx,8);\n"
        "vmovupd   (%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r10,%rbx,8);\n"
        "vmovupd   32(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r10,%rbx,8);\n"
        "vmovupd   64(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 96(%r10,%rbx,8);\n"
        "vmovupd   96(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r10,%rbx,8);\n"
        "vmovupd   128(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r10,%rbx,8);\n"
        "vmovupd   160(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 192(%r10,%rbx,8);\n"
        "vmovupd   192(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r10,%rbx,8);\n"
        "vmovupd   224(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r10,%rbx,8);\n"
        "vmovupd   256(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 288(%r10,%rbx,8);\n"
        "vmovupd   288(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r10,%rbx,8);\n"
        "vmovupd   320(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r10,%rbx,8);\n"
        "vmovupd   352(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 384(%r10,%rbx,8);\n"
        "vmovupd   384(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r10,%rbx,8);\n"
        "vmovupd   416(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r10,%rbx,8);\n"
        "vmovupd   448(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 480(%r10,%rbx,8);\n"
        "vmovupd   480(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r10,%rbx,8);\n"
        "vmovupd   512(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r10,%rbx,8);\n"
        "vmovupd   544(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 576(%r10,%rbx,8);\n"
        "vmovupd   576(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r10,%rbx,8);\n"
        "vmovupd   608(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r10,%rbx,8);\n"
        "vmovupd   640(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 672(%r10,%rbx,8);\n"
        "vmovupd   672(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r10,%rbx,8);\n"
        "vmovupd   704(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r10,%rbx,8);\n"
        "vmovupd   736(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 768(%r10,%rbx,8);\n"
        "vmovupd   768(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r10,%rbx,8);\n"
        "vmovupd   800(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r10,%rbx,8);\n"
        "vmovupd   832(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 864(%r10,%rbx,8);\n"
        "vmovupd   864(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r10,%rbx,8);\n"
        "vmovupd   896(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r10,%rbx,8);\n"
        "vmovupd   928(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 960(%r10,%rbx,8);\n"
        "vmovupd   960(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r10,%rbx,8);\n"
        "vmovupd   992(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r10,%rbx,8);\n"
        "vmovupd   1024(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1056(%r10,%rbx,8);\n"
        "vmovupd   1056(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r10,%rbx,8);\n"
        "vmovupd   1088(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r10,%rbx,8);\n"
        "vmovupd   1120(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1152(%r10,%rbx,8);\n"
        "vmovupd   1152(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1184(%r10,%rbx,8);\n"
        "vmovupd   1184(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r10,%rbx,8);\n"
        "vmovupd   1216(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1248(%r10,%rbx,8);\n"
        "vmovupd   1248(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1280(%r10,%rbx,8);\n"
        "vmovupd   1280(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1312(%r10,%rbx,8);\n"
        "vmovupd   1312(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1344(%r10,%rbx,8);\n"
        "vmovupd   1344(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1376(%r10,%rbx,8);\n"
        "vmovupd   1376(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1408(%r10,%rbx,8);\n"
        "vmovupd   1408(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1440(%r10,%rbx,8);\n"
        "vmovupd   1440(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1472(%r10,%rbx,8);\n"
        "vmovupd   1472(%r11,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1504(%r10,%rbx,8);\n"
        "vmovupd   1504(%r11,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        "vmovntpd  %ymm1, 1536(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1568(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1600(%r10,%rbx,8);\n"
        "vmovntpd  %ymm1, 1632(%r10,%rbx,8);\n"
        "movq      %r15, %rdi;\n"

        "call      nop;\n"

        //-----------------------------------------------

        "add       $208, %rbx;\n"

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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r11,%rbx,8);\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r11,%rbx,8);\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 864(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r11,%rbx,8);\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r11,%rbx,8);\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1056(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r11,%rbx,8);\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1184(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1248(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1280(%r11,%rbx,8);\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1312(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1376(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1408(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1440(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1472(%r11,%rbx,8);\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1504(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1536(%r11,%rbx,8);\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1568(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $200, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r11,%rbx,8);\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r11,%rbx,8);\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 864(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r11,%rbx,8);\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r11,%rbx,8);\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1056(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r11,%rbx,8);\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1184(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1248(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1280(%r11,%rbx,8);\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1312(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1376(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1408(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1440(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1472(%r11,%rbx,8);\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1504(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $208, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r11,%rbx,8);\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r11,%rbx,8);\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 864(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r11,%rbx,8);\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r11,%rbx,8);\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1056(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r11,%rbx,8);\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1184(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1248(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1280(%r11,%rbx,8);\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1312(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1376(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1408(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1440(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $216, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r11,%rbx,8);\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r11,%rbx,8);\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 864(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r11,%rbx,8);\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r11,%rbx,8);\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1056(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r11,%rbx,8);\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1184(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1248(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1280(%r11,%rbx,8);\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1312(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1344(%r11,%rbx,8);\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1376(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $224, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r11,%rbx,8);\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r11,%rbx,8);\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 864(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r11,%rbx,8);\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r11,%rbx,8);\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1056(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r11,%rbx,8);\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1184(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1248(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1280(%r11,%rbx,8);\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1312(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $232, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r11,%rbx,8);\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r11,%rbx,8);\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 864(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r11,%rbx,8);\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r11,%rbx,8);\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1056(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r11,%rbx,8);\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1184(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1216(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1248(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $240, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r11,%rbx,8);\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r11,%rbx,8);\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 864(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r11,%rbx,8);\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r11,%rbx,8);\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1056(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r11,%rbx,8);\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1152(%r11,%rbx,8);\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1184(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $248, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r11,%rbx,8);\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r11,%rbx,8);\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 864(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r11,%rbx,8);\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r11,%rbx,8);\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1056(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1088(%r11,%rbx,8);\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1120(%r11,%rbx,8);\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "mov       %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $256, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r11,%rbx,8);\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r11,%rbx,8);\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 864(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r11,%rbx,8);\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r11,%rbx,8);\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1024(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 1056(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $264, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r11,%rbx,8);\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r11,%rbx,8);\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 864(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r11,%rbx,8);\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 960(%r11,%rbx,8);\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 992(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $272, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r11,%rbx,8);\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r11,%rbx,8);\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 864(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 896(%r11,%rbx,8);\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 928(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $280, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r11,%rbx,8);\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 832(%r11,%rbx,8);\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 864(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $288, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r11,%rbx,8);\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 768(%r11,%rbx,8);\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 800(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2304(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2336(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $296, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 704(%r11,%rbx,8);\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 736(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2336(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2400(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $304, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 640(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 672(%r11,%rbx,8);\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2304(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2336(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2368(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2400(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2464(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $312, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2336(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2400(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 576(%r11,%rbx,8);\n"
        "vmovupd   2432(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2464(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2528(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 608(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $320, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovntpd  %ymm1, 512(%r11,%rbx,8);\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 544(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2336(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2400(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2464(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2496(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2528(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2592(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $328, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2304(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2336(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 448(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2400(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2464(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2528(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 480(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2560(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2592(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2656(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $336, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2336(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2400(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2464(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovntpd  %ymm1, 384(%r11,%rbx,8);\n"
        "vmovupd   2496(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2528(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2592(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2656(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 416(%r11,%rbx,8);\n"
        "vmovupd   2688(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2720(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $344, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2304(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2336(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2368(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2400(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 320(%r11,%rbx,8);\n"
        "vmovupd   2464(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2528(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2592(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2656(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 352(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2688(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2720(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2784(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $352, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "vmovupd   2304(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2336(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2400(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2432(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2464(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2528(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 256(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2592(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2656(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2720(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2784(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2848(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 288(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $360, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2336(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2400(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 192(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2464(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2528(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2592(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2656(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2720(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2784(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 224(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2816(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2848(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2912(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $368, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2304(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2336(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2368(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 128(%r11,%rbx,8);\n"
        "vmovupd   2400(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2464(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2528(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2592(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2656(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2720(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2784(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2848(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 160(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2880(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2912(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2976(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $376, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 64(%r11,%rbx,8);\n"
        "vmovupd   2304(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2336(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2400(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2464(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2528(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2592(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2656(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2720(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2784(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2848(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2912(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2976(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   3040(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 96(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $384, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, (%r11,%rbx,8);\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2304(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2336(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2400(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2464(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2496(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2528(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2592(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2656(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2688(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2720(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2784(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2848(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2880(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2912(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2976(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3040(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   3072(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   3104(%r10,%rbx,8), %ymm0;\n"
        "vmovntpd  %ymm1, 32(%r11,%rbx,8);\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $392, %rbx;\n"
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
        "vmovupd   (%r10,%rbx,8), %ymm0;\n"
        "vmovupd   32(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   64(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   96(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   128(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   160(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   192(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   224(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   256(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   288(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   320(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   352(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   384(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   416(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   448(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   480(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   512(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   544(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   576(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   608(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   640(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   672(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   704(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   736(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   768(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   800(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   832(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   864(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   896(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   928(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   960(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   992(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1024(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1056(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1088(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1120(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1152(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1184(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1216(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1248(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1280(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1312(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1344(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1376(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1408(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1440(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1472(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1504(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1536(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1568(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1600(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1632(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1664(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1696(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1728(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1760(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1792(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1824(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1856(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1888(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   1920(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1952(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   1984(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2016(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2048(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2080(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2112(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2144(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2176(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2208(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2240(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2272(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2304(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2336(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2368(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2400(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2432(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2464(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2496(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2528(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2560(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2592(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2624(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2656(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2688(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2720(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2752(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2784(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2816(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2848(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   2880(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2912(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2944(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   2976(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   3008(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   3040(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        "vmovupd   3072(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   3104(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   3136(%r10,%rbx,8), %ymm0;\n"
        "vmovupd   3168(%r10,%rbx,8), %ymm0;\n"
        "movq      %r15, %rdi;\n"
        "call      nop;\n"
        //-----------------------------------------------
        "add       $400, %rbx;\n"
        "cmp       %r12, %rbx;\n"
        "jb        ..L_100;\n"
    );
}
