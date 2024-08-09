#!/bin/bash

module purge
module load bsc/1.0
module load intel/2023.2.0
module load impi/2021.9.0
module load oneapi/2023.2.0
module load mkl/2023.2.0

module load hdf5 python/3.12.1 
module load cmake/3.29.2

#module load intel 
#module load HDF5 PYTHON/2.7.3  SCONS/2.3.0 # for Nord 2
#module load gcc/4.8.2 gcc/4.9.1
#module load gcc/7.2.0
# # for Nord 4
# module load mkl python/2.7.18 
# module load intel/2021.4.0 impi/2021.4.0 
# module load scons/2.3.0
# module load hdf5/1.10.8

export LC_ALL="en_US.UTF-8"

# currently it only generate two curves. 100% and 0% read worklaod. change the step to generate more curves. (make sure input tracefiles are available.)
RWRATIO_MIN=0
RWRATIO_MAX=100
RWRATIO_STEP=100



SMOOTH_SAVGOL_WINDOW_LENGTH=0
SMOOTH_SAVGOL_POLYORDER=3


# cd ./src/stream_mpi/
# make
# cd ../../


# uncomment below line to remove previously simulated points. 
# rm -r measurment_*

# Define an array of constant values (these are different delays to put in the trace file to configure bandwidth.)
constant_values=(2 5 10 15 20 22 25 27 30 32 35 37 40 42 45 50 75 200 400 1000)


for ((rd_percentage=RWRATIO_MIN; rd_percentage<=RWRATIO_MAX; rd_percentage+=RWRATIO_STEP)); do

	
	for constant_value in "${constant_values[@]}"
	do
	            
		export rd_percentage
		# export pause=0

		echo "*********** Iteration: rd_percentage=${rd_percentage} pause=${constant_value} "


		mkdir measurment_${rd_percentage}_${constant_value}
		cd measurment_${rd_percentage}_${constant_value}


		# Set the input and output file names
		input_file="../traceInput/measurment_${rd_percentage}_0/dramsim3.trace"
		output_file="dramsim3.trace"

		# Use awk to process the file
		# multiply the 3rd column by the constant value
		awk -v const="$constant_value" '{
			$3 = $3 * const
			print $0
		}' "$input_file" > "$output_file"



		cp ../submit.batch ./
		sbatch submit.batch

	

		cd ../

	done 





    # to avoid submitting too much jobs to slurm
    jobsWAitingInTheQueue=$(squeue | wc -l)
    while [ $jobsWAitingInTheQueue -gt 200 ]
    do
        sleep 300
        jobsWAitingInTheQueue=$(squeue | wc -l)
        echo 'waiting for the queues...'
	done


done


export ROOT_DIR="$(pwd)"
export ATE="$(date +"%d-%m-%Y-%H_%M_%S")"
export OUTPUT_DIR="${ROOT_DIR}/measuring/"



###################
# Post-processing #
###################
echo "start processing data..."


# PROCESSING_DIR="${ROOT_DIR}/processing/"
# ${PROCESSING_DIR}/main.py ${OUTPUT_DIR}











