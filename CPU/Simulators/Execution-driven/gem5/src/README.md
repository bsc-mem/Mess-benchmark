# Mess benchmark for gem5 memory systems

This is Mess benchmark source code modified slightly to run on simulators. In simulators, we can measure latency from simulation trace, and therefore there is no need to execute pointer-chase. 

## System configuration and Prerequisites

- Linux.
- gem5.
- OpenMP.
- gcc 


## How to run the Mess benchmark 

Below, `rd_percentage ` determines the read ratio of the workload. The `pause` value determines intensity of the benchmark and output bandwidth. The lower the `pause` value the higher the bandwidth. 

```
export OMP_NUM_THREADS=64
./build/stream_mpi.x -r rd_percentage -p pause 
```
 



