#!/bin/bash

# unzip trace files
cd traceInput
for file in *.zip; do
    unzip "$file"
done
cd ..

# compile DRAMsim3
cd DRAMsim3_mn5
make
cd ..

chmod +x ./DRAMsim3_mn5/build/dramsim3main

################################################## 
# run the experiment (supercomputer)

#sbatch runner.sh

# wait until all jobs are done
while [ $(squeue | wc -l) -gt 1 ]
do
    sleep 300
    echo 'waiting for the queues...'
done

##################################################
# run the experiment (single server)

./runner.sh


##################################################

###################
# Post-processing #
###################
# echo "start processing data..."

python3 main.py .



