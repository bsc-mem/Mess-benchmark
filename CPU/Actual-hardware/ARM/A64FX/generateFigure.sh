#!/bin/bash

module purge
module load bsc/1.0
module load intel/2023.2.0
module load impi/2021.9.0
module load oneapi/2023.2.0
module load mkl/2023.2.0

module load hdf5 python/3.12.1

# for compilation of stream it is necessary
# otherwise we get the following error: 
# Catastrophic error: could not set locale "" to allow processing of multibyte characters
export LANG=en_US.utf8
export LC_ALL=en_US.utf8



./create_runner_config.sh config/A64FX.toml 

. ./config.sh

PTRCHASE_ARRAY_SIZE=$((${PTRCHASE_ARRAY_SIZE}))

echo ${PTRCHASE_ARRAY_SIZE}





###########################
# Setting the working dir #
###########################

# Setting working dir, output dir, and compiling the benchmarks according to the
# configuration file
export ROOT_DIR="$(pwd)"
export ATE="$(date +"%d-%m-%Y-%H_%M_%S")"
# OUTPUT="${NAME}_${MEM_TYPE}_${MEM_FREQ}_${DATE}/"
export OUTPUT_DIR="${ROOT_DIR}/measuring/"

export OUTPUT_DIR_BW="${OUTPUT_DIR}/bw"
export OUTPUT_DIR_LAT="${OUTPUT_DIR}/lat"
export OUTPUT_DIR_LOG="${OUTPUT_DIR}/log"
mkdir -p ${OUTPUT_DIR_BW}
mkdir -p ${OUTPUT_DIR_LAT}
mkdir -p ${OUTPUT_DIR_LOG}


export STREAM_DIR="${ROOT_DIR}/src/stream_mpi/"
export STREAM_DIR_BW="${ROOT_DIR}/src/stream_mpi_bw/"
export PTRCHASE_DIR="${ROOT_DIR}/src/ptr_chase/"

echo "*********** Working dir set. Compiling Stream..."
cd ${STREAM_DIR}


# make clean && make
echo "*********** Stream compiled successfully."


echo "*********** Working dir set. Compiling Stream_bw..."
cd ${STREAM_DIR_BW}


# make clean && make
echo "*********** Stream_BW compiled successfully. Compiling Ptr_chase..."


# clear output directories
cd ${OUTPUT_DIR_LOG}
# rm *
# rm .*
# cd ${OUTPUT_DIR_BW}
# rm *
# rm .*
# cd ${OUTPUT_DIR_LAT}
# rm *
# rm .*
# rm ../../output/*


cd ${ROOT_DIR}
cp ./config.sh ${OUTPUT_DIR}



# set variables for bw measurment
export STREAM_CORE_LIST=${STREAM_CORE_LIST} 
export STREAM_NUMACTL_ADDITIONAL_ARGS=${STREAM_NUMACTL_ADDITIONAL_ARGS} 
export STREAM_CORE_COUNT=${STREAM_CORE_COUNT} 
export STREAM_DIR=${STREAM_DIR}
export rd_percentage=${rd_percentage} 
export pause=${pause} 
export STREAM_LOG_FILE=${STREAM_LOG_FILE}
export OUTPUT_DIR_BW=${OUTPUT_DIR_BW}
export BW_TOOL=${BW_TOOL}
export BW_TOOL_PATH=${BW_TOOL_PATH}
export BW_TOOL_CORES=${BW_TOOL_CORES}
export BW_TOOL_COUNTERS=${BW_TOOL_COUNTERS}
export BW_TOOL_SAMPLE_TIME=${BW_TOOL_SAMPLE_TIME} 
export TIME_STREAM_STABILIZE=${TIME_STREAM_STABILIZE}
export TIME_AFTER_BW_MEAS=${TIME_AFTER_BW_MEAS}
export BW_MEAS_REPS=${BW_MEAS_REPS}

# set variables for latency measurment
export PTRCHASE_NUM_INSTRUCTIONS=${PTRCHASE_NUM_INSTRUCTIONS}
export PTRCHASE_NUM_ITERATIONS=${PTRCHASE_NUM_ITERATIONS}
export PTRCHASE_ARRAY_SIZE=${PTRCHASE_ARRAY_SIZE}
export CACHE_LINE=${CACHE_LINE}
export LAT_MEAS_REPS=${LAT_MEAS_REPS}
export LAT_TOOL=${LAT_TOOL}
export PTRCHASE_CORE=${PTRCHASE_CORE}
export LAT_TOOL_PATH=${LAT_TOOL_PATH}
export LAT_TOOL_COUNTERS=${LAT_TOOL_COUNTERS}

export POINT_REPS=${POINT_REPS}





cd ${PTRCHASE_DIR}
# # TODO check about the mpicc module or at least add it to the documentation as a required package
# make clean && make

echo "*********** Ptr_chase compiled successfully."

# generate input array for pointer chasing
# cd ${ROOT_DIR}
# pjsub submit_arraygen.sh

# wait until array is generated...!
# jobsWAitingInTheQueue=$(pjstat | wc -l)
# while [ $jobsWAitingInTheQueue -gt 0 ]
# do
#     sleep 100
#     jobsWAitingInTheQueue=$(pjstat | wc -l)
# done


# echo "arraygen generated the input of pointer chasing benchmark"


#notes of cpu numbers: (lscpu)
# NUMA node4 CPU(s):    12-23
# NUMA node5 CPU(s):    24-35
# NUMA node6 CPU(s):    36-47
# NUMA node7 CPU(s):    48-59

#  from likwid
# Memory read bandwidth [MBytes/s] = 1.0E-06*(L2D_CACHE_REFILL ((r0017)) -(L2D_SWAP_DM (0325) +L2D_CACHE_MIBMCH_PRF (0326) ))*256.0/runtime
# Memory read data volume [GBytes] = 1.0E-09*(L2D_CACHE_REFILL-(L2D_SWAP_DM+L2D_CACHE_MIBMCH_PRF))*256.0
# Memory write bandwidth [MBytes/s] = 1.0E-06*(L2D_CACHE_WB (r0018) )*256.0/runtime
# Memory write data volume [GBytes] = 1.0E-09*(L2D_CACHE_WB)*256.0
# Memory bandwidth [MBytes/s] = 1.0E-06*((L2D_CACHE_REFILL-(L2D_SWAP_DM+L2D_CACHE_MIBMCH_PRF))+L2D_CACHE_WB)*256.0/runtime
# Memory data volume [GBytes] = 1.0E-09*((L2D_CACHE_REFILL-(L2D_SWAP_DM+L2D_CACHE_MIBMCH_PRF))+L2D_CACHE_WB)*256.0




cd ${ROOT_DIR}




# export rd_percentage=100
# export pause=40000




# echo $rd_percentage > rd_percentage.txt
# echo $pause > pause.txt


# pjsub submit_bw.job.bash
# pjsub submit_main.job.bash

# # pjstat --filter "st=RUN"
# # to avoid submitting too much jobs to slurm
# jobsWaitingInTheQueue=$(pjstat | wc -l)
# jobsRunningInTheQueue=$(pjstat --filter "st=RUN" | wc -l)
# while [ $jobsWaitingInTheQueue -gt $jobsRunningInTheQueue ]
# do
#     sleep 10
#     jobsWaitingInTheQueue=$(pjstat | wc -l)
#     jobsRunningInTheQueue=$(pjstat --filter "st=RUN" | wc -l)
# done

# echo 'banwidth measured. start measuring latency'





# echo 'done...'



# for ((point_rep=1; point_rep<=${POINT_REPS}; point_rep+=1)); do
#     for ((rd_percentage=RWRATIO_MIN; rd_percentage<=RWRATIO_MAX; rd_percentage+=RWRATIO_STEP)); do
#         for pause in ${PAUSES}; do

#                 echo $rd_percentage > rd_percentage.txt
#                 echo $pause > pause.txt


#                 pjsub submit_bw.job.bash
#                 pjsub submit_main.job.bash

#                 sleep 20
#                 # pjstat --filter "st=RUN"
#                 # to avoid submitting too much jobs to slurm
#                 jobsWaitingInTheQueue=$(pjstat | wc -l)
#                 jobsRunningInTheQueue=$(pjstat --filter "st=RUN" | wc -l)
#                 while [ $jobsWaitingInTheQueue -gt $jobsRunningInTheQueue ]
#                 do
#                     sleep 20
#                     jobsWaitingInTheQueue=$(pjstat | wc -l)
#                     jobsRunningInTheQueue=$(pjstat --filter "st=RUN" | wc -l)
#                 done

            
#         done

#     done
# done















###################
# Post-processing #
###################
# echo "start processing data..."
PROCESSING_DIR="${ROOT_DIR}/processing/"
${PROCESSING_DIR}/main.py ${OUTPUT_DIR}

# TODO something is not being killed when this process finishes, search for kill
# any process started inside bash script
