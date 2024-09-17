#!/bin/bash

module purge
module load bsc/1.0
module load intel/2023.2.0
module load impi/2021.9.0
module load oneapi/2023.2.0
module load mkl/2023.2.0

module load hdf5 python/3.12.1



. ./config.sh


#############
# Functions #
#############

# Prints the current iteration for progress tracking
print_iteration() {
    echo "*********** Iteration: rd_percentage=${rd_percentage} pause=${pause} point_rep=${point_rep}"
}

# Launches stream benchmark with desired read-percentage and pause
launch_stream() {
    echo "Launching stream..."
    # Launch stream and redirect stdout and stderr to a log file
    export STREAM_LOG_FILE=${OUTPUT_DIR_LOG}/stream_${rd_percentage}_${pause}.log
    #numactl -C1 mpirun -n 1 ../src/stream_mpi/bin/stream_mpi.x -r ${ratio} -p ${pause} >/dev/null &
    numactl -C${STREAM_CORE_LIST} ${STREAM_NUMACTL_ADDITIONAL_ARGS} mpirun -n ${STREAM_CORE_COUNT} ${STREAM_DIR}/stream_mpi.x -r ${rd_percentage} -p ${pause} >>${STREAM_LOG_FILE} 2>&1 &
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
            { ${BW_TOOL_PATH} -f -c ${BW_TOOL_CORES} -O -g ${BW_TOOL_COUNTERS} -S ${BW_TOOL_SAMPLE_TIME} ; } >>${BW_TOOL_OUTPUT_FILE} 2>&1
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

# Continuously gets the frequency at the PTRCHASE_CORE
measure_frequency() {
    while true
    do
        # print information regarding the PTRCHASE_CORE and also its subsequent core
        # to have information about ptr_chase and stream frequency
        cat /proc/cpuinfo | grep "processor.*\b[$PTRCHASE_CORE+1]\b" -A10 | grep "MHz" | awk -F: '{ print $2 }' >> ${STREAM_LOG_FILE} 2>&1
        sleep 2
    done
}

# Use selected tool to measure performance of pointer chasing benchmark and store them in a file
# These measurements are used in post-processing to calculate memory access latency
measure_latency() {
    echo "Measuring latency..."
    LAT_TOOL_OUTPUT_FILE=${OUTPUT_DIR_LAT}/lat_${LAT_TOOL}_${rd_percentage}_${pause}.txt

    # call measure_frequency in the background to monitor the frequency during ptr_chase
    echo "Getting frequency information..."
    measure_frequency &
    export GET_FREQ_PID=$!

    case ${LAT_TOOL} in
        "perf")
          if ${PTRCHASE_WARMUP}; then
            # warmup and then run ptr_chase
            numactl -C${PTRCHASE_CORE} ${PTRCHASE_NUMACTL_ADDITIONAL_ARGS} ${LAT_TOOL_PATH} stat -e ${LAT_TOOL_COUNTERS} ./ptr_chase 1 >> ${LAT_TOOL_OUTPUT_FILE} 2>&1
            numactl -C${PTRCHASE_CORE} ${PTRCHASE_NUMACTL_ADDITIONAL_ARGS} ${LAT_TOOL_PATH} stat -e ${LAT_TOOL_COUNTERS} ./ptr_chase 2 >> ${LAT_TOOL_OUTPUT_FILE} 2>&1
          else
            # without warming up
            numactl -C${PTRCHASE_CORE} ${PTRCHASE_NUMACTL_ADDITIONAL_ARGS} ${LAT_TOOL_PATH} stat -e ${LAT_TOOL_COUNTERS} ./ptr_chase 2 >> ${LAT_TOOL_OUTPUT_FILE} 2>&1
          fi
            ;;
        "CUSTOM")
            #{ ${LAT_TOOL_CUSTOM_CMD} ; } >>${LAT_TOOL_OUTPUT_FILE} 2>&1
            time numactl -C${PTRCHASE_CORE} ${PTRCHASE_NUMACTL_ADDITIONAL_ARGS} ./ptr_chase >> ${LAT_TOOL_OUTPUT_FILE} 2>&1
            ;;
        *)
            echo "  ERROR: ${LAT_TOOL} not supported as a latency measurement tool."
    esac

    kill $GET_FREQ_PID >/dev/null 2>&1
    echo "  Latency measured."
}

# Terminates stream
# Checks if correct stream configuration is running
terminate_stream() {
    #First check if correct stream process is still executing
    stream_cmd=$(ps -p ${STREAM_PID} -o command)
    if [[ "${stream_cmd}" == *"-r ${rd_percentage} -p ${pause}"* ]]; then
        #OK: stream with correct parameters is still running. We can terminate it
        echo "  Terminating stream."
        kill -SIGKILL ${STREAM_PID}
        wait ${STREAM_PID} 2>>${STREAM_LOG_FILE}
    else
        # TODO: what if there is a running instance of stream from a previous iteration?
        echo "  WARNING: Stream execution finished prematurelly for rd_percentage=${rd_percentage} pause=${pause}."
        echo "  WARNING: The measurements might be inprecisse."
    fi
}

# Checks if cpu load is low
# The purpose is to identify situations where another "heavy" process may run in parallel with this tool.
# Such situations may result in inprecisse measurements.
check_cpu_load() {
    # Taken from https://stackoverflow.com/questions/9229333/how-to-get-overall-cpu-usage-e-g-57-on-linux#comment33209786_9229692
    CPU_USAGE=$(top -b -n2 -p 1 | fgrep "Cpu(s)" | tail -1 | awk -F'id,' -v prefix="$prefix" '{ split($1, vs, ","); v=vs[length(vs)]; sub("%", "", v); printf "%s%.1f%%\n", prefix, 100 - v }')
    echo "Current CPU usage: ${CPU_USAGE}"
}

###########################
# Setting the working dir #
###########################

# Setting working dir, output dir, and compiling the benchmarks according to the
# configuration file
ROOT_DIR="$(pwd)"
DATE="$(date +"%d-%m-%Y-%H_%M_%S")"
OUTPUT="${NAME}_${MEM_TYPE}_${DRAM_FREQ}_${DATE}/"
OUTPUT_DIR="${ROOT_DIR}/measuring/"

OUTPUT_DIR_BW="${OUTPUT_DIR}/bw"
OUTPUT_DIR_LAT="${OUTPUT_DIR}/lat"
OUTPUT_DIR_LOG="${OUTPUT_DIR}/log"
mkdir -p ${OUTPUT_DIR_BW}
mkdir -p ${OUTPUT_DIR_LAT}
mkdir -p ${OUTPUT_DIR_LOG}

STREAM_DIR="${ROOT_DIR}/src/stream_mpi/"
PTRCHASE_DIR="${ROOT_DIR}/src/ptr_chase/"

echo "*********** Working dir set. Compiling Stream..."
cd ${STREAM_DIR}
export STREAM_ARRAY_SIZE=${STREAM_ARRAY_SIZE}

# mpicc="$(module list | grep "mpich-x86_64")"
# if [[ "$mpicc" != *mpich* ]]; then
#   module="$(module avail | grep "mpich-x86_64" | awk -F\  {'print $1'})"
#   echo "Loading module $module"
#   module load $module
# fi

#make clean && make
echo "*********** Stream compiled successfully. Compiling Ptr_chase..."

cd ${PTRCHASE_DIR}
export PTRCHASE_NUM_INSTRUCTIONS=${PTRCHASE_NUM_INSTRUCTIONS}
export PTRCHASE_NUM_ITERATIONS=${PTRCHASE_NUM_ITERATIONS}
export PTRCHASE_ARRAY_SIZE=${PTRCHASE_ARRAY_SIZE}

if [[ "${MEM_TYPE}" == *"MemMode"* ]]; then
  if [[ "${PTRCHASE_TARGET_LEVEL}" == *"optane"* ]]; then
    export PTRCHASE_CACHE_LINE_SIZE=256
    export PTRCHASE_FILE_SIZE="LARGE_PTR_CHASE"
  else
    export PTRCHASE_CACHE_LINE_SIZE=64
    export PTRCHASE_FILE_SIZE="SMALL_PTR_CHASE"
  fi
else
  export PTRCHASE_CACHE_LINE_SIZE=64
  export PTRCHASE_FILE_SIZE="SMALL_PTR_CHASE"
fi

#make clean && make
if [[ "${MEM_TYPE}" == *"MemMode"* ]]; then
  numactl -C 0 ./ptr_chase 2
fi

echo "*********** Ptr_chase compiled successfully."
echo "*********** Starting StressMe..."

cd ${ROOT_DIR}
# mv ./config.sh ${OUTPUT_DIR}

# if [ "$(cat /proc/sys/kernel/perf_event_paranoid)" != 0 ]; then
#   "$(sudo /opt/admin/event_paranoid_zero.sh)"
# fi

#############
# Main loop #
#############
for ((rd_percentage=RWRATIO_MIN; rd_percentage<=RWRATIO_MAX; rd_percentage+=RWRATIO_STEP)); do
    for pause in ${PAUSES}; do
        for ((point_rep=1; point_rep<=${POINT_REPS}; point_rep+=1)); do
            print_iteration

            # check that system load is low
            check_cpu_load

            # mess with everything left on any cache level so far
            # to make sure there is nothing left from previous executions
            #stress-ng --brk 2 --stack 2 --bigheap 2 -t 10

            launch_stream

            # Wait for bandwidth to stabilize
            sleep ${TIME_STREAM_STABILIZE}

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
            terminate_stream
            sleep ${TIME_AFTER_STREAM_TERMINATION}

            echo "*********** Done executing iteration."

        done

    done
done


###################
# Post-processing #
###################
PROCESSING_DIR="${ROOT_DIR}/processing"
${PROCESSING_DIR}/main.py ${OUTPUT_DIR}


