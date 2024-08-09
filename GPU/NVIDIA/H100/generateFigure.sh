#!/bin/bash

module load intel mkl python/3.12.1
module load cuda/12.2
module load papi/7.1.0



# TODO: add this to config file
export POWER_ISA=1

# TODO add toml to current python package
./create_runner_config.sh ./configs/mn5-gpu-h100.toml
. ./config.sh
PTRCHASE_ARRAY_SIZE=$((${PTRCHASE_ARRAY_SIZE}))
echo $PTRCHASE_ARRAY_SIZE
# set variables for latency measurment
export PTRCHASE_NUM_INSTRUCTIONS=${PTRCHASE_NUM_INSTRUCTIONS}
# export PTRCHASE_NUM_ITERATIONS=${PTRCHASE_NUM_ITERATIONS}
export PTRCHASE_ARRAY_SIZE=${PTRCHASE_ARRAY_SIZE}
export CACHE_LINE=${CACHE_LINE}
export LAT_MEAS_REPS=${LAT_MEAS_REPS}
export LAT_TOOL=${LAT_TOOL}
export PTRCHASE_CORE=${PTRCHASE_CORE}
export LAT_TOOL_PATH=${LAT_TOOL_PATH}
export LAT_TOOL_COUNTERS=${LAT_TOOL_COUNTERS}
export BW_TOOL=${BW_TOOL}


###########################
# Setting the working dir #
###########################

# Setting working dir, output dir, and compiling the benchmarks according to the
# configuration file
export ROOT_DIR="$(pwd)"
export TARGE_DIR="src-mn5-h100"

# TODO: add this to config file at the end
export OUTPUT_DIR="${ROOT_DIR}/${TARGE_DIR}/measuring/"
export OUTPUT_DIR_BW="${OUTPUT_DIR}/bw"
export OUTPUT_DIR_LAT="${OUTPUT_DIR}/lat"
export OUTPUT_DIR_LOG="${OUTPUT_DIR}/log"

mkdir -p ${OUTPUT_DIR_BW}
mkdir -p ${OUTPUT_DIR_LAT}
mkdir -p ${OUTPUT_DIR_LOG}


# set the path to generate ptr_chase file
export PTRCHASE_DIR="${ROOT_DIR}/tools/ptr_chase_gen/"


# copy the config file to output directory
cd ${ROOT_DIR}
cp ./config.sh ${OUTPUT_DIR}


cd ${ROOT_DIR}/${TARGE_DIR}

PROCESSING_DIR="${ROOT_DIR}/${TARGE_DIR}/processing/"
${PROCESSING_DIR}/main.py ${OUTPUT_DIR}



