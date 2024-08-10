#!/bin/bash

module load gcc/7.2.0 #gcc/4.7.0 #gcc/4.9.1 #gcc/5.1.0 #gcc/7.2.0 


RWRATIO_MIN=0
RWRATIO_MAX=100
RWRATIO_STEP=2
PAUSES="0 5 10 15 20 25 30 35 40 45 50 55 60 65 70 80 90 100 120 140 160 180 200 220 260 300 340 380 450 550 600 700 800 900 1000 1500 2000 3000 5000 10000"
SMOOTH_SAVGOL_WINDOW_LENGTH=11
SMOOTH_SAVGOL_POLYORDER=3



cd ./src/stream_mpi/
make
cd ../../

# remove previous measurments
rm -r measurment_*



for ((rd_percentage=RWRATIO_MIN; rd_percentage<=RWRATIO_MAX; rd_percentage+=RWRATIO_STEP)); do
    for pause in ${PAUSES}; do
        
       	# to avoid submitting too much jobs to slurm
	    jobsWAitingInTheQueue=$(squeue | wc -l)
	    while [ $jobsWAitingInTheQueue -gt 200 ]
	    do
	        sleep 200
	        jobsWAitingInTheQueue=$(squeue | wc -l)
	        echo 'waiting for the queues...'
		done

		export rd_percentage=100
		export pause=0

		echo "*********** Iteration: rd_percentage=${rd_percentage} pause=${pause} "


		mkdir measurment_${rd_percentage}_${pause}
		cd measurment_${rd_percentage}_${pause}
		cp ../sb.cfg ./

		sed -i "s/rd_percentage/${rd_percentage}/g" sb.cfg 
		sed -i "s/pause/${pause}/g" sb.cfg 

		# code to run pointer-chase to valdiate unloaded latency
		# cp ../src/ptr_chase/ptr_chase ./
		# cp ../src/ptr_chase/array.dat ./

		cp ../submit.batch ./

		sbatch submit.batch

		cd ../

    done




    # to avoid submitting too much jobs to slurm
    # jobsWAitingInTheQueue=$(squeue | wc -l)
    # while [ $jobsWAitingInTheQueue -gt 200 ]
    # do
    #     sleep 200
    #     jobsWAitingInTheQueue=$(squeue | wc -l)
    #     echo 'waiting for the queues...'
	# done


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
