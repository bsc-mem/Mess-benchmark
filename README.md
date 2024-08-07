# Mess benchmark


Below figure illustrates the workflow employed by Mess to create bandwidth--latency curves. Mess reads an input configuration file, specifying system setups like the number of sockets, CPU model, and memory technology. Additionally, it includes details about the profiling tools used to read hardware counters (e.g. Perf, PAPI, and Likwid) and lists the hardware counters. This configuration file also defines the experiments to be executed, specifying ranges of read/write ratios, memory stress level, and the number of times each experiment is repeated. For this study, we conducted each experiment three times to enhance the reliability of our measurements. 

<table>
  <tr>
    <td align="center">
      <img src="./workflow.png" alt="Alt text" title="Title" width="800" />
      <div><em>Figure 1: Caption describing the figure.</em></div>
    </td>
  </tr>
</table>

Afterward, the workflow establishes a list of experimental points and iterates through them until all points have been executed. For each experiment, initially, we setup the experiment configuration, setting parameters such as read/write ratio and memory stress level. These settings are utilized by the traffic generator to stress main memory. For hugh stress level, the memory traffic generator reaches to the highest issue rate of the load and store operations, thereby creating the highest significant pressure on the memory system. Typically (unless over-saturation exists in the platform, this is the point of the maximum measured bandwidth and latency.

However, when the srress level is low, the memory traffic generator spends practically all the time issuing nop instructions, generating negligible memory traffic. In this case, the main memory remains unloaded and unloaded latency can be measured. After setting up the experiment, the workflow runs the memory traffic generator on all the cores in each socket except core 0 to stress the main memory with the configured workload.

Subsequently, we allow a specific duration for memory bandwidth utilization to stabilize. This duration is determined empirically and is crucial for the CPU to reach a high-performance state (e.g., maximum voltage/frequency settings) and achieve stability. Afterwards, we run the pointer-chase benchmark on core 0 while the traffic generator is running on the rest of the cores. Then, we measure latency and bandwidth for this experimental point by utilizing available hardware counters. Measuring the latency of the actual hardware requires profiling overheads such as secondary TLB hits and the cycles consumed during page walking to exclude OS-dependent overheads. To measure bandwidth, we employ uncore counters that count the number of CAS commands issued by the memory controller. Each measurement contributes to a single point of a single curve. To generate the complete curve, this process is iterated for all points with the same read/write ratio, followed by a repetition for other curves with varying read/write ratios. Following this procedure, we replicate the entire set of experiments to enhance the reliability of our findings as many times as specified in the configuration file.

Afterward, when all the points are measured (i.e., check finish is positive), we proceed to the post-processing phase. As each experimental point is repeated at least three times, we can compute the mean and standard deviations. Subsequently, any outliers deviating more than three times from the standard deviations away from the mean are removed. The remaining experiments are merged through an averaging process.

Following this, to mitigate the noise resulting from experiment variability on the actual systems, we utilize the Savitzky–Golay filter (savgol_filter function from the Python scipy.signal library). This filter, a commonly used digital signal processing technique, performs linear smoothing over a sliding window of data points (in this case, bandwidth–latency measurement points). Specifically, the filter utilizes a least squares polynomial fitting method to estimate the underlying trend in the data. It then substitutes each data point in the window with the corresponding value derived from the polynomial fit, resulting in a smoothed output signal. The Savitzky–Golay filter is preferred due to its efficiency in noise reduction while preserving crucial curve features like peak shapes and edges.

Finally, after collecting all bandwidth–latency measurements, filtered and smoothed, we construct complete curves by utilizing the plot function within the Python matplotlib module.
