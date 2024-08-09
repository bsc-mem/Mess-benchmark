#!/bin/bash 
#PJM -N bw-latency
#PJM -o output/output_%j.out 
#PJM -e output/output_%j.err 
#PJM -L "rscgrp=large"
#PJM -L node=1
#PJM -L elapse=0:30:00
#PJM --mpi "proc=45,max-proc-per-node=45"

module purge

module load fuji
module load likwid


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
export STREAM_DIR_BW="${ROOT_DIR}/src/stream_mpi_bw/"
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
    BW_TOOL_COUNTERS="r0017,r0018"
    perf stat -e ${BW_TOOL_COUNTERS} -d -d -d numactl -C${STREAM_CORE_LIST} ${STREAM_NUMACTL_ADDITIONAL_ARGS} mpirun -n ${STREAM_CORE_COUNT} timeout 30s ${STREAM_DIR}/stream_mpi.x -r ${rd_percentage} -p ${pause} >> ${STREAM_LOG_FILE} 2>&1
    

    # Save the PID for later termination

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
            { numactl -C${BW_TOOL_CORES} ${BW_TOOL_PATH} stat -a -e ${BW_TOOL_COUNTERS} sleep ${BW_TOOL_SAMPLE_TIME} ;} >>${BW_TOOL_OUTPUT_FILE} 2>&1
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




echo "Measuring bandwidth..."
export BW_TOOL_OUTPUT_FILE=${OUTPUT_DIR_BW}/bw_${BW_TOOL}_${rd_percentage}_${pause}.txt   



{ numactl -C${STREAM_CORE_LIST} ${STREAM_NUMACTL_ADDITIONAL_ARGS} mpirun -n ${STREAM_CORE_COUNT} ${STREAM_DIR_BW}/stream_mpi.x -r ${rd_percentage} -p ${pause} -f ${BW_TOOL_OUTPUT_FILE}; }









