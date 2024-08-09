#!/bin/bash
#SBATCH --job-name="acmTest"
#SBATCH -D .
#SBATCH --output=output/output_%j.out
#SBATCH --error=output/output_%j.err 
#SBATCH --account=bsc18
#SBATCH --qos=acc_bsccs
#SBATCH --nodes=1
#SBATCH --gres=gpu:4
#SBATCH --exclusive
#SBATCH --constraint=perfparanoid
#SBATCH --time=00:10:00
#SBATCH --nodelist=as01r2b30


module load intel mkl python/3.12.1
module load cuda/12.2
module load papi/7.1.0

PAPI_HOME=/apps/ACC/PAPI/7.1.0/


LAT_TOOL_OUTPUT_FILE=${OUTPUT_DIR_LAT}/lat_${LAT_TOOL}_${rd_percentage}_${pause}.txt 
BW_TOOL_OUTPUT_FILE=${OUTPUT_DIR_BW}/bw_${BW_TOOL}_${rd_percentage}_${pause}.txt

./main -s ${PTRCHASE_ARRAY_SIZE} -f ${PTRCHASE_DIR}/array.dat -r ${rd_percentage} -p ${pause} -i ${PTRCHASE_NUM_INSTRUCTIONS} >> ${LAT_TOOL_OUTPUT_FILE} 2>&1

cp ${LAT_TOOL_OUTPUT_FILE} ${BW_TOOL_OUTPUT_FILE} 


