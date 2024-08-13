# Mess benchmark: Intel Skylake Xeon Platinum 8160

This repository is tuned and modified to generate bandwidth--latency curves on MareNostrum 4 supercomputer located in Barcelona Supercomputing Center[[1]](https://www.bsc.es/supportkc/docs/MareNostrum4/intro/). 




## System configuration and Prerequisites

- SUSE Linux Enterprise Server 12 SP2.
- Slurm batch processing support.
- Intel VTune 2017.4.
- Intel compiler 2023.
- OneAPI 2023. 
- Python 3.12.1 with following packages: matplotlib, toml, Pyarrow, and seaborn. 
 



## How to run the Mess benchmark 

```
# Fisrt, we modifeid the "config/mn4_DDR4-2666.toml" file to represent MareNostrum 4. 
# Then: 
./runner.sh 
```


## To generate bandwidth--latency curves

```
# after all the submitted job by runner.sh finished, execute the script below:
./generateFigure.sh 
```



## Notes

- Ensure that you have access to uncore counters. This means that either you have root access privilage (this is not our case in supercomputers) or the system is configured such that perf_event_paranoid is -1. We can check the status of perf_event_paranoid at /proc/sys/kernel/perf_event_paranoid. We can also configure it with the command below: 

```
echo -1 > /proc/sys/kernel/perf_event_paranoid
```



## Refrences

[[1]](https://www.bsc.es/supportkc/docs/MareNostrum4/intro/ ) [https://www.bsc.es/supportkc/docs/MareNostrum4/intro/](https://www.bsc.es/supportkc/docs/MareNostrum4/intro/ ) 
