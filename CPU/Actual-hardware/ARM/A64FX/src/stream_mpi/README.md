## Memory bandwidth load benchmark

The benchmark generates the traffic towards main memory, with two runtime parameters:

 - specific amount of RD requests (between 50\% and 100\% of reads in the total traffic, with a step of 2\%)
 - a pause that inject delays (by executing *nops*) between memory requests and thus lowers the generated bandwidth

The benchmark is based on the modified STREAM \[[1][]\] benchmark.
It uses MPI library and optional OpenMP directives.
These are notable differences from the original STREAM benchmark:

 - It contains only the Copy kernel while the specific kernel functions for different RD ratios are coded in x86 assembly, using AVX instructions and non-temporal stores (defined in **utils.c** file and explained in detail below).
 - The content of the arrays at the end is not checked.
 - Any type of timing is removed as it is not needed.
 - Benchmark runs indefinitely instead of using NTIMES macro to define number of iterations.

Apart from the runtime parameters, the main code located in the **stream_mpi.c** file contains array size parameter (default at 80,000,000).
This parameter can be set in the code, or through compiler flags (-D) during the compilation.

\[1\] *John D. McCalpin. 1991-2007. STREAM: Sustainable Memory Bandwidth in High Performance Computers. Technical
Report. University of Virginia. http://www.cs.virginia.edu/stream/*

[1]: http://www.cs.virginia.edu/stream/ "Original STREAM benchmark developed by John D. McCalpin"

### Compiling the code

In order to compile the code, set the desired compiler and its flags in the Makefile.
We tested the code with **gcc** compiler in combination with **OpenMPI** library, and with **Intel** compiler together with and **Intel MPI** library.
Optionally, array size parameter can be set as compiler flags `-DSTREAM_ARRAY_SIZE=...`.

Compile the code by running `make`.

### Running the benchmark

Here is the example of running the benchmark with 16 MPI processes, with 64\% of RD traffic and a pause of 1000.

```
mpirun -n 16 ./bin/stream_mpi.x -r 64 -p 1000
```
The **-r** parameter is the required RD ratio in the total traffic (from 50 to 100, with a step of 2), while the **-p** parameter is the introduced pause. For the maximum bandwidth, set this parameter to 0.

The example above displays the following output:

```
-------------------------------------------------------------
$ Memory bandwidth load kernel $
-------------------------------------------------------------
This system uses 8 bytes per array element.
-------------------------------------------------------------
Total Aggregate Array size = 80000000 (elements)
Total Aggregate Memory per array = 610.4 MiB (= 0.6 GiB).
Total Aggregate memory required = 1220.7 MiB (= 1.2 GiB).
Data is distributed across 16 MPI ranks
   Array size per MPI rank = 5000000 (elements)
   Memory per array per MPI rank = 38.1 MiB (= 0.0 GiB).
   Total memory per MPI rank = 76.3 MiB (= 0.1 GiB).
-------------------------------------------------------------
The kernel will be executed indefinitely.
```

For the best precision, memory bandwidth can be measured using uncore counters (with tools such as **perf**, **LIKWID**, etc.), which we used to get bandwidth-latency dependencies in PROFET model.


### Implementation details
#### Copy kernel
Copy kernel is a function written in assembler that performs loads and stores from/to two independent arrays stored in memory and thus generates memory traffic with a desired ratio of memory reads and writes. There are specific kernels written for each RD percentage and they are all located in **utils.c** file. Each kernel consists of 100 vector move instructions. The ratio between load and store instructions depends on the kernel's RD percentage. For example, kernel ```STREAM_copy_60```, which corresponds to RD percentage of 60, contains 60 vector load and 40 vector store instructions.

The assembly code is currently written following AT&T syntax (used by GNU tools). For curious readers, there is more info on AT&T syntax ([Wikibooks](https://en.wikibooks.org/wiki/X86_Assembly/GNU_assembly_syntax)) and main differences between AT&T and Intel syntax ([Wikipedia](https://en.wikipedia.org/wiki/X86_assembly_language#Syntax)). Here we provide a short summary:

- first operand is the source and the second operand is destination
- adressing uses the following format:
    - ```$200``` - immediate value 200
    - ```%r10``` - register r10
    - ```32(%r10,%rbx,8)``` memory address calculated as ```%r10 + %rbx*8 + 32```. General format is ```displacement(base_register, index_register, scale_factor)```, which translates to ```base_register + index_register * scale_factor + displacement```. In our case, scale factor is 8 because the arrays consist of double-precission floating point numbers, which have size of 8B.

Loads are performed using instruction [```vmovupd```](https://www.felixcloutier.com/x86/movupd) that loads 256b (32B) from given memory address to vector register ```%ymm0```.
Stores using instruction [```vmovntpd```](https://www.felixcloutier.com/x86/movntpd) that stores 256b (32B) from register ```%ymm1``` to a given memory address, using non-temporal hint to bypass the cache ([More info on non-temporal memory instructions, Section 6.1](https://lwn.net/Articles/255364/)].

Blocks of load and store instructions are interleaved with a call to function ```nop``` implemented in file ***nop.c***. This function takes the number of ```nop``` instructions to execute as an argument ```pause``` passed through register ```rdi```. Note: pay attention to the difference between the function ```nop``` and nop instruction.
