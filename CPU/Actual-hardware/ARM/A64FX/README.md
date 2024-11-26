# Mess benchmark: Amazon Graviton 3

TODO: redo for a64fx

This repository is tuned and modified to generate bandwidth--latency curves on Amazon AWS with 64-core Graviron 3.




## System configuration and Prerequisites

- Ubuntu 20.04.5 LTS.
- Python 3 with following packages: matplotlib, toml, Pyarrow, and seaborn. 
- spack.  
 



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




