#!/bin/bash
#COBALT -n 128 -A datascience -t 3:00:00 -q default --jobname=dlio_candel --attrs mcdram=cache:numa=quad

export MPICH_MAX_THREAD_SAFETY=multiple
CURRENT_DIR=`pwd`
DLIO_ROOT=`dirname $CURRENT_DIR`
source ./setup_tf2.3.sh
export PYTHONPATH=$DLIO_ROOT:$PYTHONPATH

NNODES=$COBALT_JOBSIZE
RANKS_PER_NODE=4
NRANKS=$((COBALT_JOBSIZE*RANKS_PER_NODE))
NUM_CORES=64
THREADS_PER_CORE=2
NUM_THREADS=$((NUM_CORES*THREADS_PER_CORE))
PROCESS_DISTANCE=$((NUM_THREADS/RANKS_PER_NODE))

DARSHAN_PRELOAD=/soft/perftools/darshan/darshan-3.1.8/lib/libdarshan.so

DATA_DIR=/projects/datascience/dhari/stimulus/evaluation/1

THREADS_USED=$1

OPTS=(-f hdf5_opt -fa shared -nf 1 -sf 1000 -rl 1048576 -bs 64 -e 10 -tr ${THREADS_USED} -tc ${THREADS_USED} -df ${DATA_DIR} -gd 0 -k 1)

echo "aprun -n $NRANKS -N $RANKS_PER_NODE -j $THREADS_PER_CORE -cc depth -e OMP_NUM_THREADS=$PROCESS_DISTANCE -d $PROCESS_DISTANCE ${OPTS[@]}"

aprun -n $NRANKS -N $RANKS_PER_NODE -j $THREADS_PER_CORE -cc depth -e OMP_NUM_THREADS=$PROCESS_DISTANCE -d $PROCESS_DISTANCE \
-e DXT_ENABLE_IO_TRACE=1 -e LD_PRELOAD=$DARSHAN_PRELOAD \
python ${DLIO_ROOT}/src/dlio_benchmark.py ${OPTS[@]}

