This folder contains scripts for post-processing of performance counters data.
Currently implemented features:
- parsing output of profiling tools
- detecting anomalies in performance counter readings
- recovering from above-mentioned anomalies
- filtering data and smoothing of curves
- plotting

We use pandas DataFrames as a data format for intermediate and final results to:
- benefit from robust mechanisms for data processing and plotting
- enable easier extending of features
