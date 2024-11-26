# Mess benchmark: Fujitsu A64FX



This repository is tuned and modified to generate bandwidth--latency curves on CTE-ARM cluster of MareNostrum 4 supercomputer located in Barcelona Supercomputing Center[[1]](https://www.bsc.es/supportkc/docs/CTE-ARM/intro). 



## System configuration and Prerequisites

- gcc
- Python 3 with following packages: matplotlib, toml, Pyarrow, and seaborn. 
- openMPI (or fuji compiler of fugaku)
 



## How to run the Mess benchmark 

```sh
# Fisrt, we modifeid the "config/A64FX.toml" file to represent MareNostrum 4. 
# Then: 
./runner.sh 
```


## To generate bandwidth--latency curves

```sh
# after all the submitted job by runner.sh finished, execute the script below:
./generateFigure.sh 
```






## Notes

- Ensure that you have access to uncore counters. This means that either you have root access privilage (this is not our case in supercomputers) or the system is configured such that perf_event_paranoid is -1. We can check the status of perf_event_paranoid at /proc/sys/kernel/perf_event_paranoid. We can also configure it with the command below: 

```sh
echo -1 > /proc/sys/kernel/perf_event_paranoid
```
- In this experiments we had sbatch command to submit jobs. If you have access to only one server you need to change sbatch command in `runner.sh` file with sh command. Additionally, at the end of the `submit_main.job` file, you need to make sure you terminate the pricesses that you have started for previous point. To do so, you can use the following command:
```sh
# Terminate stream execution 
sleep 2s
pkill stream_mpi.x
sleep 2s
```

- Before starting a new set of experiments remember to uncomment rm commands in `runner.sh` file to remove the results of the previous experiments. 

## Refrences

[[1]](https://www.bsc.es/supportkc/docs/CTE-ARM/intro ) [https://www.bsc.es/supportkc/docs/CTE-ARM/intro](https://www.bsc.es/supportkc/docs/CTE-ARM/intro ) 



