#!/bin/bash

module load intel mkl python/3.12.1
module load cuda/12.2
module load papi/7.1.0





# TODO: add this to config file
export POWER_ISA=0
export x86_ISA=1

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


# clear output directories
cd ${OUTPUT_DIR_LOG}
# rm -f *
# rm -f .*
# cd ${OUTPUT_DIR_BW}
# rm -f *
# rm -f .*
# cd ${OUTPUT_DIR_LAT}
# rm -f *
# rm -f .*
# rm -f * ../../output/*
# rm -f .* ../../output/*


# copy the config file to output directory
cd ${ROOT_DIR}
cp ./config.sh ${OUTPUT_DIR}

# compiling pointer chase benchmark
cd ${PTRCHASE_DIR}
# echo "*********** Compiling and run arraygen to generate ptrChase file ..."
# make clean && make
# echo "*********** Ptr_chase compiled successfully."
# echo "*********** Test to make sure ptr chase works fine ..."
# ./ptr_chase


# exit 0


cd ${ROOT_DIR}/${TARGE_DIR}

#  compiler GPU code. 
make clean
make


# export rd_percentage=100
# export pause=0

# sbatch submit.bash




cd ${ROOT_DIR}

# run the bandwidth--latency curves.

for ((point_rep=1; point_rep<=${POINT_REPS}; point_rep+=1)); do

    for ((rd_percentage=RWRATIO_MIN; rd_percentage<=RWRATIO_MAX; rd_percentage+=RWRATIO_STEP)); do

        for pause in ${PAUSES}; do

                export rd_percentage 
                export pause 
                echo "*********** Iteration: rd_percentage=${rd_percentage} pause=${pause} rep=${point_rep}"
                sbatch submit.bash

        done


        # to avoid submitting too much jobs to slurm
        jobsWAitingInTheQueue=$(squeue | wc -l)
        while [ $jobsWAitingInTheQueue -gt 250 ]
        do
                sleep 150
                echo 'waiting for the free node...'
                jobsWAitingInTheQueue=$(squeue | wc -l)
        done


    done
done



