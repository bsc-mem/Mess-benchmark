# Mess benchmark: SiFive HiFive Unmateched 

This repository is tuned and modified to generate bandwidth--latency curves on SiFive HiFive Unmateched board [[1]](https://www.sifive.com/boards/hifive-unmatched). 




## System configuration and Prerequisites

- Linux Server 
- Slurm batch processing support 
- PAPI 6.0.0
- gcc 10.3.0
- openmpi 
- Python 3.12.1 with following packages: matplotlib, toml, Pyarrow, and seaborn. 




## How to run the Mess benchmark 

```
# Fisrt, we modifeid the "config/HiFive.toml" file to represent SiFive HiFive Unmateched CPU. 
# Then: 
./runner.sh 
```


## To generate bandwidth--latency curves

```
# after all the submitted job by runner.sh finished, execute the script below:
./generateFigure.sh 
```



## Notes

- RISC-V processors are in the early stages of development and often lack support for uncore performance monitoring units (PMUs). To enable a RISC-V-compatible version of Mess, we implement a STREAM-like bandwidth estimation methodology, where bandwidth is computed as the total volume of data transferred, measured from the application's perspective, divided by the execution time. 



## Refrences

[[1]](https://www.sifive.com/boards/hifive-unmatched ) [https://www.sifive.com/boards/hifive-unmatched](https://www.sifive.com/boards/hifive-unmatched ) 
