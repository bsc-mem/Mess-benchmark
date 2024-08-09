#!/bin/bash
#SBATCH --job-name="bw-latency"
#SBATCH -D .
#SBATCH --output=output/output_%j.out
#SBATCH --error=output/output_%j.err 
#SBATCH --nodes=1
#SBATCH --time=2:00:00
#SBATCH --exclusive
#SBATCH --constraint=perfparanoid
#SBATCH --reservation=smt-disable


module load gcc/9.2.0
module load python/3.9.0 # it has toml
module load openmpi/4.1.2
module load bsc
module load likwid
module load lmbench

# . ./config.sh

numactl --hardware

export OMPI_MCA_btl=^openib



lscpu


perf list


#############
# Functions #
#############

# Prints the current iteration for progress tracking
print_iteration() {
    echo "*********** Iteration: rd_percentage=${rd_percentage} pause=${pause} point_rep=${point_rep}"
}




# Use selected tool to measure performance of pointer chasing benchmark and store them in a file
# These measurements are used in post-processing to calculate memory access latency
measure_latency() {
    echo "Measuring latency..."
    LAT_TOOL_OUTPUT_FILE=${OUTPUT_DIR_LAT}/lat_${LAT_TOOL}_${rd_percentage}_${pause}.txt
    case ${LAT_TOOL} in
        "perf")
            #numactl -C${PTRCHASE_CORE} ${PTRCHASE_NUMACTL_ADDITIONAL_ARGS} ${LAT_TOOL_PATH} stat -e ${LAT_TOOL_COUNTERS} ./ptr_chase >> ${LAT_TOOL_OUTPUT_FILE} 2>&1
            # numactl -C${PTRCHASE_CORE} ${PTRCHASE_NUMACTL_ADDITIONAL_ARGS} ${LAT_TOOL_PATH} stat -e ${LAT_TOOL_COUNTERS} ./ptr_chase 
            numactl -C${PTRCHASE_CORE} ${PTRCHASE_NUMACTL_ADDITIONAL_ARGS} ./ptr_chase >> ${LAT_TOOL_OUTPUT_FILE} 2>&1
            ;;
        "CUSTOM")
            { ${LAT_TOOL_CUSTOM_CMD} ; } >>${LAT_TOOL_OUTPUT_FILE} 2>&1
            ;;
        *)
            echo "  ERROR: ${LAT_TOOL} not supported as a latency measurement tool."
    esac
    echo "  Latency measured."
}


# Launches stream benchmark with desired read-percentage and pause
launch_stream() {
    echo "Launching stream..."
    # Launch stream and redirect stdout and stderr to a log file
    export STREAM_LOG_FILE=${OUTPUT_DIR_LOG}/stream_${rd_percentage}_${pause}.log
    #numactl -C1 mpirun -n 1 ../src/stream_mpi/bin/stream_mpi.x -r ${ratio} -p ${pause} >/dev/null &
    taskset -c ${STREAM_CORE_LIST} mpirun -n ${STREAM_CORE_COUNT} ${STREAM_DIR}/stream_mpi.x -r ${rd_percentage} -p ${pause} >>${STREAM_LOG_FILE} 2>&1 &
    # mpirun -n 20 ${STREAM_DIR}/stream_mpi.x -r ${rd_percentage} -p ${pause} >>${STREAM_LOG_FILE} 2>&1 &
    
    # Save the PID for later termination
    export STREAM_PID=$!
    echo "  Stream launched."
}

# Use selected tool to sample uncore counters (memory controller) and store them in a file
# These measurements are used in post-processing to calculate memory bandwidth
measure_bandwidth() {
    echo "Measuring bandwidth..."
    BW_TOOL_OUTPUT_FILE=${OUTPUT_DIR_BW}/bw_${BW_TOOL}_${rd_percentage}_${pause}.txt
    case ${BW_TOOL} in
        "likwid")
            # numactl -C${PTRCHASE_CORE} ${PTRCHASE_NUMACTL_ADDITIONAL_ARGS} ${LAT_TOOL_PATH} stat -e ${LAT_TOOL_COUNTERS} ./ptr_chase
            # perf stat -v -e ${BW_TOOL_COUNTERS} sleep 5
            # { ${BW_TOOL_PATH} -c 0 -g MEM -S ${BW_TOOL_SAMPLE_TIME} ; } >>${BW_TOOL_OUTPUT_FILE} 2>&1
            { ${BW_TOOL_PATH} -f -O -g ${BW_TOOL_COUNTERS} -S ${BW_TOOL_SAMPLE_TIME} ; } >>${BW_TOOL_OUTPUT_FILE} 2>&1
            # { ${BW_TOOL_PATH} -f -c ${BW_TOOL_CORES} -O -g ${BW_TOOL_COUNTERS} -S ${BW_TOOL_SAMPLE_TIME} ; } >>${BW_TOOL_OUTPUT_FILE} 2>&1
            ;;
        "perf")
            { taskset -c 0 ${BW_TOOL_PATH} stat -a -e ${BW_TOOL_COUNTERS} sleep ${BW_TOOL_SAMPLE_TIME} ;} >>${BW_TOOL_OUTPUT_FILE} 2>&1
            ;;
        "vtune")
            # TODO: Make the following command fully configurable
            # TODO: Does Vtune support sampling mode similar to stetoscope mode in likwid? (this avoids using sleep)
            { ${BW_TOOL_PATH} -collect-with runsa -quiet -knob event-config=UNC_M_CAS_COUNT.ALL -- numactl -C 0 sleep ${BW_TOOL_SAMPLE_TIME} ; } >>${BW_TOOL_OUTPUT_FILE} 2>&1
            ;;
        "CUSTOM")
            { ${BW_TOOL_CUSTOM_CMD} ; } >>${BW_TOOL_OUTPUT_FILE} 2>&1
            ;;
        *)
            echo "  ERROR: ${BW_TOOL} not supported as a bandwidth measurement tool."
    esac
    echo "  Bandwidth measured."
}


# Checks if cpu load is low
# The purpose is to identify situations where another "heavy" process may run in parallel with this tool.
# Such situations may result in inprecisse measurements.
check_cpu_load() {
    # Taken from https://stackoverflow.com/questions/9229333/how-to-get-overall-cpu-usage-e-g-57-on-linux#comment33209786_9229692
    CPU_USAGE=$(top -b -n2 -p 1 | fgrep "Cpu(s)" | tail -1 | awk -F'id,' -v prefix="$prefix" '{ split($1, vs, ","); v=vs[length(vs)]; sub("%", "", v); printf "%s%.1f%%\n", prefix, 100 - v }')
    echo "Current CPU usage: ${CPU_USAGE}"
}



# check that system load is low
# check_cpu_load

launch_stream

# Wait for bandwidth to stabilize (10 seconds are good 10 times repeat. identical results.)

sleep ${TIME_STREAM_STABILIZE}





print_iteration




# Measure performance counters needed to calculate memory bandwidth
# Repeat measurements configured number of times
for ((bw_meas_rep=1; bw_meas_rep<=${BW_MEAS_REPS}; bw_meas_rep+=1)); do
    measure_bandwidth
done

sleep ${TIME_AFTER_BW_MEAS}


# Measure performance counters needed to calculate memory access latency
# Repeat measurements configured number of times
cd ${PTRCHASE_DIR}
for ((lat_meas_rep=1; lat_meas_rep<=${LAT_MEAS_REPS}; lat_meas_rep+=1)); do
    measure_latency
done
cd ${ROOT_DIR}

# Terminate stream execution
# terminate_stream
# sleep ${TIME_AFTER_STREAM_TERMINATION}


echo "*********** Done executing iteration."




