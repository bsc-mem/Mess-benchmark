#!/bin/bash
#SBATCH --job-name="acmTest"
#SBATCH -D .
#SBATCH --output=output_%j.out
#SBATCH --error=output_%j.err 
#SBATCH --account=bsc18
#SBATCH --qos=gp_bsccs
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4   
#SBATCH --cpus-per-task=1      
#SBATCH --time=00:20:00


# below code block is for the MareNostrum 5 in Barcelona Supercomputer Center (BSC). It will load all the necessary modules to run the experiment.
# if you use other servers please make sure the system has gcc and g++ installed. 
# if you use other servers please make sure the system has python3 with matplotlib and toml paclage installed.
# module purge
# module load bsc/1.0
# module load intel/2023.2.0
# module load impi/2021.9.0
# module load oneapi/2023.2.0
# module load mkl/2023.2.0

# module load hdf5 python/3.12.1 
# module load cmake/3.29.2



export LC_ALL="en_US.UTF-8"

# currently it only generate two curves. 100% and 0% read worklaod. change the step to generate more curves. (make sure input tracefiles are available.)
RWRATIO_MIN=0
RWRATIO_MAX=100
RWRATIO_STEP=50



SMOOTH_SAVGOL_WINDOW_LENGTH=0
SMOOTH_SAVGOL_POLYORDER=3




# uncomment below line to remove previously simulated points. 
rm -r measurment_*

# Define an array of constant values (these are different delays to put in the trace file to configure bandwidth.)
constant_values=(2 5 10 15 20 22 25 27 30 32 35 37 40 42 45 50 75 200 400 1000)


for ((rd_percentage=RWRATIO_MIN; rd_percentage<=RWRATIO_MAX; rd_percentage+=RWRATIO_STEP)); do

	
	for constant_value in "${constant_values[@]}"
	do
	            
		export rd_percentage

		echo "*********** Iteration: rd_percentage=${rd_percentage} pause=${constant_value} "


		mkdir measurment_${rd_percentage}_${constant_value}
		cd measurment_${rd_percentage}_${constant_value}


		# Set the input and output file names
		input_file="../traceInput/measurment_${rd_percentage}_0/dramsim3.trace"
		output_file="dramsim3.trace"

		# Use awk to process the file
		# multiply the 3rd column by the constant value (this will add delay to the trace file, which will be used to configure the bandwidth)
		awk -v const="$constant_value" '{
			$3 = $3 * const
			print $0
		}' "$input_file" > "$output_file"



		cp ../submit.batch ./
		
		# option 1
		# for SLRUM (supercomputer)
		# sbatch submit.batch
		
		# option 2
		# for single node
		bash submit.batch

	

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
# echo "start processing data..."


# PROCESSING_DIR="${ROOT_DIR}/processing/"
# ${PROCESSING_DIR}/main.py ${OUTPUT_DIR}




