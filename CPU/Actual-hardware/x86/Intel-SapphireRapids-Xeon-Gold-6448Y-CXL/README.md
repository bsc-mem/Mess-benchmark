# Mess benchmark: Intel Sapphire Rapids Xeon Gold 6448Y with CXL


This repository is tuned and modified to generate CXL bandwidth--latency curves on a dual-socket intel server with two Intel Sapphire Rapids Xeon Gold 6448Y CPUs. A CXL memory expander device is connected to socket 0 and configured as CPU-less numa node (numa memory node 2).



## System configuration and Prerequisites

- Linux (tested version 5.14.0).
- Intel PCM (tested with 202307 Release; https://github.com/intel/pcm/releases/tag/202307).
- Intel compiler (tested with gcc 11.4.1).
- numactl
- Python 3 with following packages: matplotlib, toml, Pyarrow, and seaborn. 
 


## How to run the Mess benchmark 
Fisrt, we modifeid the `config/sapphireRapids_CXL.toml` file to represent your system. Then: 

```
sudo ./runner.sh 
```


## To generate bandwidth--latency curves
After the `runner.sh` script is finished, execute the script below:

``` 
./generateFigure.sh 
```


## Notes

- Ensure that you have access to uncore counters. Ensure that the system is configured such that perf_event_paranoid is -1. We can check the status of perf_event_paranoid at /proc/sys/kernel/perf_event_paranoid. We can also configure it with the command below: 

```
echo -1 > /proc/sys/kernel/perf_event_paranoid

```

- In this experiment, to read hardware counters related to CXL, we use Intel PCM. To work properly we needed to run the workflow (runner.sh) as sudo  
```
sudo ./runner.sh 
```
