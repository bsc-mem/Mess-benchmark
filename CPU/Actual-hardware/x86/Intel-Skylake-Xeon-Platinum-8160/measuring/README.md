# Obtaining bandwidth--latency curves with Mess

The end result of Mess tool is a family of bandwidth-latency curves for a given memory system. A single curve corresponds to a given read-write ratio of memory traffic and shows the dependency of memory access latency from the current memory bandwidth.

The overal process of obtaining these curves is straight-forward. This page describes the process of gathering the raw performance measurements used to generate the curves.

### Performance counter sampling for memory bandwidth and memory access latency

We use STREAM benchmark to generate desired level of memory traffic. While STREAM executes, we measure the achieved bandwidth and the latency of a memory access. These two measurements give us a memory access latency during the measured memory traffic intensity. Repeating these measurements for a range of memory bandwidths gives us a single bandwidth-latency curve for selected read-write ratio. Finally, we repeat the whole process for all desired read-write ratios and, thus, obtain the family of bandwidth-lantecy curves for the particular memory system.

The simple version of this main loop looks as follows:
```
# Get a family of BwLat curves
for rw_ratio in RW_RATIOS do
    # Get a single BwLat curve
    for pause in PAUSES do
        # Get a point on a single BwLat curve
        launch_stream rw_ratio pause
        measure_bw
        measure_lat
        terminate_stream
    done
done
```


MeStress measures system-wide memory bandwith and supports various tools for that purpose: Likwid and V-Tune.

The real version of the loop is more complex due to several peculiarities that we will explain in the following text.

### #1 Bandwidth is unstable shortly after launching STREAM
PICTURE

The image shows the bandwidth vs time for various STREAM configurations and executions. We notice the instability of bandwidth at the beginning of execution. Also, the time to stabilize is not constant. Our simplest solution is to empirically select a time interval that covers almost all cases. The cases where this interval is not long enough are handled in post-processing.

The length of this interval is configured by SLEEP_STREAM_STABILIZE constant.

### #2 Bandwidth may randomly destabilize during STREAM execution

PICTURE

The image shows that the bandwidth can be unstable even after the initial interval. To overcome this issue, we measure bandwidth and latency several times and filter potentially bad measurements in post-processing.

Number of bandwidth and latency measurements can be configured separately.

### #3 Bandwidth stabilizes around different values during different executions of STREAM using the same run configuration

PICTURE

The image shows bandwidth evolution during different executions of equally configured STREAM benchmark. Therefore, we run stream several times and find an average.

The resulting loop for measuring all the Bw-Lat curves is as follows:

```
for rw_ratio in RW_RATIOS do
    for pause in PAUSES do
        for point_repeat in 1..N_REPEATS do
            launch_stream rw_ratio pause

            sleep ${SLEEP_STREAM_STABILIZE}

            for i in 1..bandwidth_measurement_repeats do
                measure_bw
            done

            sleep ${SLEEP_POST_BW_MEAS}

            for i in 1..latency_measurement_repeats do
                measure_lat
            done
            cd -

            terminate_stream
            sleep ${SLEEP_POST_STREAM_KILL}
            check_threads
        done
    done
done
```
