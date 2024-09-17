# Mess benchmark: Intel Sapphire Rapids Xeon Platinum 8480


This repository is tuned and modified to generate bandwidth--latency curves on general purpose nodes in MareNostrum 5 supercomputer located in Barcelona Supercomputing Center [[1]](https://www.bsc.es/marenostrum/marenostrum-5), [[2]](https://www.bsc.es/supportkc/docs/MareNostrum5/overview). 




## System configuration and Prerequisites

- Linux (tested Red Hat Enterprise Linux 9.2).
- Slurm batch processing support.
- LIKWID (tested with version 5.3.0).
- Intel compiler (tested with icc 2021.10.0).
- OneAPI (tested with 2023.2.0 version). 
- Python 3.12.1 with following packages: matplotlib, toml, Pyarrow, and seaborn. 
 



## How to run the Mess benchmark 

```
# Fisrt, we modifeid the "config.sh" file to represent MareNostrum 5. 
# Then run the Mess benchmark and generate bandwidth--latency curves : 
./runner.sh 
```



## Notes

- Ensure that you have access to uncore counters. This means that either you have root access privilage (this is not our case in supercomputers) or the system is configured such that perf_event_paranoid is -1. We can check the status of perf_event_paranoid at /proc/sys/kernel/perf_event_paranoid. We can also configure it with the command below: 

```
echo -1 > /proc/sys/kernel/perf_event_paranoid

```
- In the start of the workflow (runner.sh), we have `module` commands. These commands load prerequisites for running Mess benchmark on MareNostrum 5 supercomputer[[1]](https://www.bsc.es/marenostrum/marenostrum-5), [[2]](https://www.bsc.es/supportkc/docs/MareNostrum5/overview). If one uses this benchmark on their local server, they need to comment `module` commands and install the prerequisites manually.


## Refrences

[[1]](https://www.bsc.es/marenostrum/marenostrum-5) [https://www.bsc.es/marenostrum/marenostrum-5](https://www.bsc.es/marenostrum/marenostrum-5 ) 

[[2]](https://www.bsc.es/supportkc/docs/MareNostrum5/overview) [https://www.bsc.es/supportkc/docs/MareNostrum5/overview](https://www.bsc.es/supportkc/docs/MareNostrum5/overview ) 
