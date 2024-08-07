# Mess benchmark
Mess benchmark describes the memory system performance with a family of bandwidth--latency curves. The benchmark covers the full range of the memory traffic intensity, from the unloaded to fully-saturated memory system. It also considers numerous compositions of read and write operations. The Mess benchmark is designed for holistic and detailed memory system characterization, and it is easily adaptive to different target platforms. The current benchmark release covers all major CPU and GPU ISAs: x86, ARM, Power, RISC-V, and NVIDIA’s Parallel Thread Execution (PTX).


## Citation

Please cite the following paper if you find this benchmark useful:

P. Esmaili-Dokht, F. Sgherzi, V. S. Girelli, I. Boixaderas, M. Carmin, A. Momeni, A. Armejach, E. Mercadal, G. Llort, P. Radojkovic, M. Moreto, J. Gimenez, X. Martorell, E. Ayguade, J. Labarta, E. Confalonieri, R. Dubey, and J. Adlard, “A mess of memory system benchmarking, simulation and application profiling,” 2024. [Online]. Available: https://arxiv.org/abs/2405.10170

---To be appear in MICRO 2024

## Repository structure

The general structure of this repository is depicted below. Mess benchmark is developed for wide range of platforms, from actual hardware to simulators, from CPUs to GPUs, and from x86 to RISC-V CPUs. To use Mess benchmark to evaluate each platform, the user may adopt the Mess version that is more similar to their target platform. 



```
Mess-benchmark
├── Actual-hardware
│   ├── CPU
│   │   ├── x86 
│   │   ├── ARM 
│   │   ├── IBM power 
│   │   └── RISC-V
│   └── GPU
│       └── NVIDIA PTX 
└── Simulators
    ├── Execution-driven
    │   ├── gem5 
    │   └── ZSim 
    └── Trace-driven
        ├── Ramulator2 
        ├── DRAMsim3 
        └── Ramulator 
```


Below we show the structure and the main files for Mess benchmark in x86 CPU directory. We picked x86 CPU as an example and other platforms follow similar structure. 

```
x86
└── Actual-hardware
    ├── config
    │   ├── mn4_DDR4-2666.toml 
    ├── measuring
    │   ├── bw 
    │   ├── lat 
    │   ├── log 
    │   ├── output 
    ├── processing
    ├── src
    ├── runner.sh
    └── submit_main.job
```

 - mn4_DDR4_2666.toml: exists in the config folder, which describes the system under the study and all the experimental setups. 

 - measuring/bw: the folder contains all the raw bandwidith measurements for each individial experimental points (i.e., each point on bandwidth--latency curves).

 - measuring/lat: the folder contains all the raw latency measurements for each individial experimental points (i.e., each point on bandwidth--latency curves).

 - measuring/log: the folder contains all the logs for each individial experimental points (i.e., each point on bandwidth--latency curves).

 - measuring/output: This folder contains the final bandwidth--latency curves and the .csv files that contains detailed information for each bandwidth--latency point on the curves. 

 - processing: This folder contains all the python codes to parse raw measurements and generate final bandwidth--latency curves and .csv file. 

 - src: This folder contains pointer-chase and workload generator benchmark. 

 - runner.sh: The main script that run the workflow. It execute the full workflow from reading the config file to generating final bandwidth--latency curves. 

 - submit_main.job: This is the script that is used by "runner.sh" and measures one experimental data point (one point on bandwidth--latency curves). 


## Workflow (runner.sh)

Below figure illustrates the workflow employed by Mess to create bandwidth--latency curves. 


1. Mess **reads** an input configuration file, specifying system setups like the number of sockets, CPU model, and memory technology. Additionally, it includes details about the profiling tools used to read hardware counters (e.g. Perf, PAPI, and Likwid) and lists the hardware counters. This configuration file also defines the experiments to be executed, specifying ranges of read/write ratios, memory stress level, and the number of times each experiment is repeated. In the config folder we have a more detailed documentation on config files. Afterward, the workflow establishes a list of experimental points and iterates through them until all points have been executed.

<table>
  <tr>
    <td align="center">
      <img src="./workflow.png" alt="Alt text" title="Title" width="800" />
      <div><em>Figure 1: Mess Workflow to generate bandwidth--latency curves .</em></div>
    </td>
  </tr>
</table>

2. For each experiment, initially, we **setup** the experiment configuration, setting parameters such as read/write ratio and memory stress level. These settings are utilized by the traffic generator to stress main memory. For hugh stress level, the memory traffic generator reaches to the highest issue rate of the load and store operations, thereby creating the highest significant pressure on the memory system. Typically (unless over-saturation exists in the platform, this is the point of the maximum measured bandwidth and latency. However, when the srress level is low, the memory traffic generator spends practically all the time issuing nop instructions, generating negligible memory traffic. In this case, the main memory remains unloaded and unloaded latency can be measured. 

3. After setting up the experiment, the workflow **runs** the memory traffic generator on all the cores in each socket except core 0 to stress the main memory with the configured workload.

4. Subsequently, we allow a specific duration for memory bandwidth utilization to **stabilize**. This duration is determined empirically and is crucial for the CPU to reach a high-performance state (e.g., maximum voltage/frequency settings) and achieve stability. 

5. Afterwards, we run the pointer-chase benchmark on core 0 while the traffic generator is running on the rest of the cores. Then, we **measure latency and bandwidth** for this experimental point by utilizing available hardware counters. Measuring the latency of the actual hardware requires profiling overheads such as secondary TLB hits and the cycles consumed during page walking to exclude OS-dependent overheads. To measure bandwidth, we employ uncore counters that count the number of CAS commands issued by the memory controller. Each measurement contributes to a single point of a single curve. To generate the complete curve, this process is iterated for all points with the same read/write ratio, followed by a repetition for other curves with varying read/write ratios. Following this procedure, we replicate the entire set of experiments to enhance the reliability of our findings as many times as specified in the configuration file.

6. Afterward, when all the points are measured (i.e., **check finish** is positive), we proceed to the post-processing phase. As each experimental point is repeated at least three times, we can compute the mean and standard deviations. 

7. Subsequently, any **outliers** deviating more than three times from the standard deviations away from the mean are removed. The remaining experiments are merged through an averaging process.

8. Following this, to mitigate the noise resulting from experiment variability on the actual systems, we utilize the **Savitzky–Golay filter** (savgol_filter function from the Python scipy.signal library). This filter, a commonly used digital signal processing technique, performs linear smoothing over a sliding window of data points (in this case, bandwidth–latency measurement points). Specifically, the filter utilizes a least squares polynomial fitting method to estimate the underlying trend in the data. It then substitutes each data point in the window with the corresponding value derived from the polynomial fit, resulting in a smoothed output signal. The Savitzky–Golay filter is preferred due to its efficiency in noise reduction while preserving crucial curve features like peak shapes and edges.

9. Finally, after collecting all bandwidth–latency measurements, filtered and smoothed, we construct complete curves by utilizing the plot function within the Python matplotlib module.
