# Mess benchmark for x86 CPUs 

While the kernels for all x86 platforms are identical, the workflow for each platform is slightly different for the following reason:

- Different platform support different hardware counter monitoring tools. For example, Intel VTune and PCM only support Intel platform.

- Even with the same hardware counter monitoring tool, different runtime and sysadmin can provide or limit different access level to the hardware counter. For example, a system with SLRUM is different from a system with PJM batch submission support.  

- Different version of profiling tools installed on each platform, print the measured hardware counters in different format. Therefore, the parsers in different systems may be slightly different.  



