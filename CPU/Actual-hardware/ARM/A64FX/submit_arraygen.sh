#!/bin/bash
#PJM -N bw-latency
#PJM -o output/output_%j.out 
#PJM -e output/output_%j.err 
#PJM -L "rscgrp=large"
#PJM -L node=1
#PJM -L elapse=0:30:00

module load fuji

module list
module avail


pwd


cd src/ptr_chase


./arraygen






