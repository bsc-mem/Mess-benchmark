

# Mess Benchmark Tutorial (MICRO 2025)

This folder provides a detailed, step-by-step guide for running the **Mess benchmark**. It is designed to help users understand the benchmark’s workflow, configuration, and output in detail.  

The repository has been tuned and adapted to generate **bandwidth–latency curves** on general-purpose nodes of the **MareNostrum 5** supercomputer, located at the [Barcelona Supercomputing Center (BSC)](https://www.bsc.es/marenostrum/marenostrum-5) [[1]](https://www.bsc.es/marenostrum/marenostrum-5), [[2]](https://www.bsc.es/supportkc/docs/MareNostrum5/overview).

The target system is a **dual-socket** node. Each socket hosts an **Intel Sapphire Rapids Xeon Platinum 8480** CPU with **56 cores** and **8 channels of DDR5-4800** memory.
 




## System configuration and Prerequisites

- Linux (tested Red Hat Enterprise Linux 9.2).
- Slurm batch processing support.
- Intel compiler (tested with icc 2021.10.0).
- OneAPI (tested with 2023.2.0 version). 
- Python 3.12.1 with following packages: matplotlib, toml, Pyarrow, and seaborn. 
 

## Introduction to workflow of Mess benchmark (runner.sh)


Below figure illustrates the workflow employed by Mess to create bandwidth--latency curves. 

<table>
  <tr>
    <td align="center">
      <img src="../../../../workflow.png" alt="Alt text" title="Title" width="800" />
      <div><em>Figure 1: Mess Workflow to generate bandwidth--latency curves .</em></div>
    </td>
  </tr>
</table>



1. Mess **reads** an input configuration file, specifying system setups like the number of sockets, CPU model, and memory technology. Additionally, it includes details about the profiling tools used to read hardware counters (e.g. Perf, PAPI, and Likwid) and lists the hardware counters. This configuration file also defines the experiments to be executed, specifying ranges of read/write ratios, memory stress level, and the number of times each experiment is repeated. In the config folder we have a more detailed documentation on config files. Afterward, the workflow establishes a list of experimental points and iterates through them until all points have been executed.


**Note:** Make sure the configuration file is set up correctly.

- **stream-core-list:** List of thread IDs that will run the traffic generator.  
  If multithreading is enabled, include only **thread 0** of each core.  
  All threads of **core 0** of each socket must remain unused.  

- **Increasing system pressure:**  
  To apply more pressure on the memory system, you can occupy all threads except those belonging to **core 0** of each socket.  
  This configuration may increase memory stress, but in typical Mess use cases, we use **one thread per core**.

- **stream-core-count:** Number of cores across all sockets, **excluding core 0** from each socket  
  (e.g., `total number of cores – number of sockets`).

- **rwratio-min**, **rwratio-max**, **rwratio-step:** Define the ratio of load to store memory instructions.  
  For example, a value of **100** means all memory instructions are loads (no stores).

- **stream-pauses:** List defining the number of NOP instructions per memory instruction (load or store).  
  To obtain a complete curve, use a wide range of pause values.  
  More pause values provide more data points but increase the total runtime.

- **point-reps:** Each experiment point should be repeated **at least three times** to ensure reliability.  
  Some runs may fail, so repetition is important for stability.

- **time-stream-stabilize:** Defines the stabilization (warm-up) time before each measurement begins.  
  This ensures the system reaches steady-state behavior.

- **bw-tool:** Determines the method used to measure **bandwidth**.  
  (Details are explained later.)

- **lat-tool:** Determines the method used to measure **latency**.  
  (Details are explained later.)

- **smooth-savgol-polyorder**, **smooth-savgol-window-length:** Parameters for the smoothing function.  
  (Explained later in detail.)

- **ptrchase-num-instructions:** Number of instructions executed by the pointer-chase benchmark.  
  This value must be sufficiently large to ensure stable latency results.

- **ptrchase-num-iterations:** Recommended value: **5000**.  
  Lower values can increase **L1i TLB misses**, while higher values add loop overhead.

- **ptrchase-array-size:** Dataset size for the pointer-chase benchmark.  
  It should be at least **4× larger than the LLC**.  
  Avoid excessively large arrays, as they can introduce TLB overhead.  
  The goal is to approximate **0% cache hit** and **100% TLB hit** conditions — we never reach this perfectly, but we aim to get as close as possible.



2. For each experiment, initially, we **setup** the experiment configuration, setting parameters such as read/write ratio and memory stress level. These settings are utilized by the traffic generator to stress main memory. For hugh stress level, the memory traffic generator reaches to the highest issue rate of the load and store operations, thereby creating the highest significant pressure on the memory system. Typically (unless over-saturation exists in the platform, this is the point of the maximum measured bandwidth and latency. However, when the srress level is low, the memory traffic generator spends practically all the time issuing nop instructions, generating negligible memory traffic. In this case, the main memory remains unloaded and unloaded latency can be measured. 

3. After setting up the experiment, the workflow **runs** the memory traffic generator on all the cores in each socket except core 0 to stress the main memory with the configured workload.

4. Subsequently, we allow a specific duration for memory bandwidth utilization to **stabilize**. This duration is determined empirically and is crucial for the CPU to reach a high-performance state (e.g., maximum voltage/frequency settings) and achieve stability. 

5. Afterwards, we run the pointer-chase benchmark on core 0 while the traffic generator is running on the rest of the cores. Then, we **measure latency and bandwidth** for this experimental point by utilizing available hardware counters. Measuring the latency of the actual hardware requires profiling overheads such as secondary TLB hits and the cycles consumed during page walking to exclude OS-dependent overheads. To measure bandwidth, we employ uncore counters that count the number of CAS commands issued by the memory controller. Each measurement contributes to a single point of a single curve. To generate the complete curve, this process is iterated for all points with the same read/write ratio, followed by a repetition for other curves with varying read/write ratios. Following this procedure, we replicate the entire set of experiments to enhance the reliability of our findings as many times as specified in the configuration file.

6. Afterward, when all the points are measured (i.e., **check finish** is positive), we proceed to the post-processing phase. As each experimental point is repeated at least three times, we can compute the mean and standard deviations. 

7. Subsequently, any **outliers** deviating more than three times from the standard deviations away from the mean are removed. The remaining experiments are merged through an averaging process.

8. Following this, to mitigate the noise resulting from experiment variability on the actual systems, we utilize the **Savitzky–Golay filter** (savgol_filter function from the Python scipy.signal library). This filter, a commonly used digital signal processing technique, performs linear smoothing over a sliding window of data points (in this case, bandwidth–latency measurement points). Specifically, the filter utilizes a least squares polynomial fitting method to estimate the underlying trend in the data. It then substitutes each data point in the window with the corresponding value derived from the polynomial fit, resulting in a smoothed output signal. The Savitzky–Golay filter is preferred due to its efficiency in noise reduction while preserving crucial curve features like peak shapes and edges.

9. Finally, after collecting all bandwidth–latency measurements, filtered and smoothed, we construct complete curves by utilizing the plot function within the Python matplotlib module.




## How to run the Mess benchmark 

```
# Fisrt, we modifeid the "config.sh" file to represent MareNostrum 5. 
# Then run the Mess benchmark and generate bandwidth--latency curves : 
./runner.sh 
```

## To generate bandwidth--latency curves
After the `runner.sh` script is finished, execute the script below:

``` 
./generateFigure.sh 
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
