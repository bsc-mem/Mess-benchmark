#!/bin/bash


# spack load likwid
# spack load lmbench
# spack load numactl





./create_runner_config.sh config/graviton3.toml 

. ./config.sh



PTRCHASE_ARRAY_SIZE=$((${PTRCHASE_ARRAY_SIZE}))


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
export PTRCHASE_DIR="${ROOT_DIR}/src/ptr_chase/"

echo "*********** Working dir set. Compiling Stream..."
cd ${STREAM_DIR}

# make clean && make
echo "*********** Stream compiled successfully. Compiling Ptr_chase..."



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




cd ${ROOT_DIR}


# for ((point_rep=1; point_rep<=${POINT_REPS}; point_rep+=1)); do
#     for ((rd_percentage=RWRATIO_MIN; rd_percentage<=RWRATIO_MAX; rd_percentage+=RWRATIO_STEP)); do
#         for pause in ${PAUSES}; do

#                 export rd_percentage
#                 export pause
                
#                 echo "*********** Iteration: rd_percentage=${rd_percentage} pause=${pause} rep=${point_rep}"

#                 sbatch submit_main.job.bash

#                 # to avoid submitting too much jobs to slurm
#                 jobsWAitingInTheQueue=$(squeue | wc -l)
#                 while [ $jobsWAitingInTheQueue -gt 25 ]
#                 do
#                     sleep 150
#                     echo 'waiting for the free node...'
#                     jobsWAitingInTheQueue=$(squeue | wc -l)
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
