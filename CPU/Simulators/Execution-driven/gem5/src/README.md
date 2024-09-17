# Mess benchmark for gem5 memory systems

This is Mess benchmark source code modified slightly to run on simulators. In simulators, we can measure latency from simulation trace, and therefore there is no need to execute pointer-chase. Additionally, original Mess benchmark is based on MPI. However, in simulation environment, we use Mess version with OpenMP. 


