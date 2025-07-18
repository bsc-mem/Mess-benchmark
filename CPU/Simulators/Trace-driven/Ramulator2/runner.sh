#!/bin/bash

module load anaconda
source activate gem5
export CC=clang
export CXX=clang++


export LC_ALL="en_US.UTF-8"

RWRATIO_MIN=0
RWRATIO_MAX=100
RWRATIO_STEP=2
# PAUSES="0 2 4 5 6 7 9 10 15 20 25 30 35 40 45 65 200"
# 2000
# PAUSES="100 120 140 160 200 300 70 80 90 0 1 2 3 4 5 6 7 8 9 10 15 20 25 30 35 40 45 50 55 65"

# rm -r measurment_100_0

# PAUSES="0 5 10 15 20 25 30 35 40 45 50 55 60 65 70 80 90 100 110 120 130 140 150 160 170 180 190 200 210 220 240 260 280 300"

# new
# PAUSES="2000 1000 0 5 10 15 20 25 30 35 40 45 50 55 60 65 70 80 90 100 110 120 130 140 150 160 170 180 190 200 210 220 240 260 280 300 340 380 450 550 600 700 800 900"


# PAUSES="2000 1000 0 5 10 15 20 25 30 35 40 45 50 55 60 65 70 80 90 100 120 140 160 180 200 220 260 300 340 380 450 550 600 700 800 900"
# PAUSES="0 5 10 15 20 25 30 35 40 45 50 55 60 65 70 80 90 100 120 140 160 180 200"

# 1500 2000 3000
# PAUSES="0 3 5 10 15 20 25 30 35 40 45 50 55 60 65 70 80 90 100 120 140 160 180 200 220 260 300 340 380 450 550 600 700 800 900 1000"

# PAUSES="3000 5000 10000 20000"

# 2000
SMOOTH_SAVGOL_WINDOW_LENGTH=0
SMOOTH_SAVGOL_POLYORDER=3


# cd ./src/stream_mpi/
# make
# cd ../../


# exit 0
#rm -r measurment_*

# Define an array of constant values
constant_values=(0 2 5 10 15 20 22 25 27 30 32 35 37 40 42 45 50 75 200 400 1000 5000 20000 50000 100000)

# constant_values=(100000)


for ((rd_percentage=RWRATIO_MIN; rd_percentage<=RWRATIO_MAX; rd_percentage+=RWRATIO_STEP)); do
#     for pause in ${PAUSES}; do


	# to avoid submitting too much jobs to slurm (comment )
	jobsWAitingInTheQueue=$(squeue | wc -l)
	while [ $jobsWAitingInTheQueue -gt 300 ]
	do
		sleep 200
		jobsWAitingInTheQueue=$(squeue | wc -l)
		echo 'waiting for the queues...'
	done
	
	for constant_value in "${constant_values[@]}"
	do
	            
		export rd_percentage=${rd_percentage}
		export constant_value=${constant_value}

		# export pause=0

		echo "*********** Iteration: rd_percentage=${rd_percentage} pause=${constant_value} "


		mkdir measurment_${rd_percentage}_${constant_value}
		cd measurment_${rd_percentage}_${constant_value}





		# cp ../traceInput/measurment_${rd_percentage}_0/dramsim3.trace ./

		# Set the input and output file names
		input_file="../traceInput/measurment_${rd_percentage}_0/ramulator.trace"
		output_file="ramulator.trace"

		# Use awk to process the file
		# multiply the 3rd column by the constant value
		awk -v const="$constant_value" '{
			$1 = $1 * const
			print $0
		}' "$input_file" > "$output_file"



		cp ../submit.batch ./
		cp ../config.cfg ./

		# if you want to use batch system of supercomputer
		sbatch submit.batch

		# # if you want to run it on a single server
		# sh submit.batch

		# cp ../sb.cfg ./

		# sed -i "s/rd_percentage/${rd_percentage}/g" sb.cfg 
		# sed -i "s/pause/${pause}/g" sb.cfg 

		# # cp ../src/ptr_chase/ptr_chase ./
		# # cp ../src/ptr_chase/array.dat ./

		# cp ../submit.batch ./

		# sbatch submit.batch
		# to avoid submitting too much jobs to slurm


		# cannot run more than one ramulator job at the same time !!!
		# jobsWAitingInTheQueue=$(squeue | wc -l)
		# while [ $jobsWAitingInTheQueue -gt 1 ]
		# do
		# 	sleep 1
		# 	jobsWAitingInTheQueue=$(squeue | wc -l)
		# 	# echo 'waiting for the queues...'
		# done

		cd ../

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

