## Memory access latency benchmark (pointer-chase)

The benchmark is used to measure access latency of different levels of memory hierarchy, for a randomized memory access pattern (so the effect of the prefetcher is negligible).
The load file size determines at which level of memory hierarchy the load file resides and which memory hierarchy level is tested.

The benchmark is implemented as a pointer-chasing code with load instructions in x86 assembly.
Execution time or number of CPU cycles of the benchmark execution can be measured using tools such as **perf**, **LIKWID**, etc. In our experiments, we also measured page walks and secondary DTLB penalties, so we can subtract them from the total CPU cycles count and get more precise results. Finally, we divide this result with the number of load instructions and, thus, get per-load average access latency of a certain memory hierarchy level.

### Compiling and running the benchmark

Installation requires a **C** compiler. We tested the code with **gcc** (higher than 4.9.1) and **Intel** compiler.

The compiler and compiler flags can be set in Makefile file using `CC` and `CFLAGS` variables.
Also, the size(s) of load file(s) can be set in the `sizes` list (in kB). It can be a single size, or several sizes. For example, to set the load file size of 512MB, define the variable as `sizes = [524288]`.
Finally, number of load instructions is defined in with `ins` variable.

To compile benchmark, run make command.
It will:
- Compile load file generator binary.
- Create the load file by executing the generator. The load file contains randomized access pattern used by the pointer-chasing code.
- Produce the pointer-chasing binary.
The example output of the make process is as follows:
```
awk '{for(i=0; i<1000; i++)print}' loop_template.h > loop.h
gcc -O0 -DARRAY_ELEMS=16777216 -DITERS=5000 -o ptr_chase ptr_chase.c
gcc -O3 -DARRAY_ELEMS=16777216 -o arraygen arraygen.c
./arraygen
Generating random walk file.
RAND_MAX = 2147483647
Random walk file generated.
```

### Example of the benchmark execution and measurement with perf

For example, we used the benchmark as follows:
```
time numactl -C 0 -m 0 perf stat -e cycles:u,instructions:u,r1008:u,r2008:u ./ptr_chase
```
This way, we execute the benchmark on CPU core0 and measure cycles, instructions, hits in the secondary DTLB and page walks.
From the total number of cycles we subtract page walks and secondary DTLB penalties, 9 cycles on our platform (measured using TLB kernel of LMBench benchmark), divide this result with number of instructions (5M),
and this way we get only the latency of the random memory read access, without the cycles needed for address translation.
