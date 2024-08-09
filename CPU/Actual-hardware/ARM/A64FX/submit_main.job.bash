#!/bin/bash 
#PJM -N bw-latency
#PJM -o output/output_%j.out 
#PJM -e output/output_%j.err 
#PJM -L "rscgrp=large"
#PJM -L node=1
#PJM -L elapse=0:30:00
#PJM --mpi "proc=44,max-proc-per-node=44"

module purge

module load fuji
module load lmbench/3.0-a9
module load likwid/5.2.2


export rd_percentage=`cat rd_percentage.txt`
export pause=`cat pause.txt`


echo $rd_percentage
echo $pause

# Setting working dir, output dir, and compiling the benchmarks according to the
# configuration file
export ROOT_DIR="$(pwd)"
export ATE="$(date +"%d-%m-%Y-%H_%M_%S")"
# OUTPUT="${NAME}_${MEM_TYPE}_${MEM_FREQ}_${DATE}/"
export OUTPUT_DIR="${ROOT_DIR}/measuring/"

export OUTPUT_DIR_BW="${OUTPUT_DIR}/bw"
export OUTPUT_DIR_LAT="${OUTPUT_DIR}/lat"
export OUTPUT_DIR_LOG="${OUTPUT_DIR}/log"



export STREAM_DIR="${ROOT_DIR}/src/stream_mpi/"
export PTRCHASE_DIR="${ROOT_DIR}/src/ptr_chase/"

. ./config.sh



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
            { time numactl -C${PTRCHASE_CORE} ${PTRCHASE_NUMACTL_ADDITIONAL_ARGS} ./ptr_chase ; }>> ${LAT_TOOL_OUTPUT_FILE} 2>&1
            
            #  for measuting bw of pointer chasing
            # { time numactl -C${BW_TOOL_CORES} ${BW_TOOL_PATH} stat -e r0017,r0018 ./ptr_chase ; } >> ${LAT_TOOL_OUTPUT_FILE} 2>&1

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
    numactl -C${STREAM_CORE_LIST} ${STREAM_NUMACTL_ADDITIONAL_ARGS} mpirun -n ${STREAM_CORE_COUNT} ${STREAM_DIR}/stream_mpi.x -r ${rd_percentage} -p ${pause} >> ${STREAM_LOG_FILE} 2>&1 &
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
            # { ${BW_TOOL_PATH} -f -c ${BW_TOOL_CORES} -O -g ${BW_TOOL_COUNTERS} -S ${BW_TOOL_SAMPLE_TIME} ; } >>${BW_TOOL_OUTPUT_FILE} 2>&1
            # { ${BW_TOOL_PATH} -f -c ${BW_TOOL_CORES} -O -g ${BW_TOOL_COUNTERS} -S ${BW_TOOL_SAMPLE_TIME} ; } >>${BW_TOOL_OUTPUT_FILE} 2>&1
            ;;
        "perf")
            { numactl -C${BW_TOOL_CORES} ${BW_TOOL_PATH} stat -e ${BW_TOOL_COUNTERS} sleep ${BW_TOOL_SAMPLE_TIME} ;} >>${BW_TOOL_OUTPUT_FILE} 2>&1
            # { likwid-perfctr -g MEM -S ${BW_TOOL_SAMPLE_TIME} ;} >>${BW_TOOL_OUTPUT_FILE} 2>&1
            # { likwid-perfctr -g MEM numactl -C${STREAM_CORE_LIST} ${STREAM_NUMACTL_ADDITIONAL_ARGS} mpirun -n ${STREAM_CORE_COUNT} $timeout 60 {STREAM_DIR}/stream_mpi.x -r ${rd_percentage} -p ${pause} ;} >>${BW_TOOL_OUTPUT_FILE} 2>&1
            
            # { numactl -C${BW_TOOL_CORES} ${BW_TOOL_PATH} stat -e r0017,r0018 sleep ${BW_TOOL_SAMPLE_TIME} ;} >>${BW_TOOL_OUTPUT_FILE} 2>&1
            # { numactl -C${BW_TOOL_CORES} ${BW_TOOL_PATH} stat -e armv8_pmuv3_0/l2d_cache_refill/,armv8_pmuv3_0/l2d_cache_wb/ sleep ${BW_TOOL_SAMPLE_TIME} ;} >>${BW_TOOL_OUTPUT_FILE} 2>&1
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






# print_iteration




# Measure performance counters needed to calculate memory bandwidth
# Repeat measurements configured number of times
# for ((bw_meas_rep=1; bw_meas_rep<=${BW_MEAS_REPS}; bw_meas_rep+=1)); do
#     measure_bandwidth
# done

# sleep ${TIME_AFTER_BW_MEAS}


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




