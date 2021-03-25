# stimulus
Artificial intelligence's popularity has led to its application in several scientific domains. These applications are coupled with traditional scientific simulations by exchanging data. However, there is a lack of efficient infrastructure to enable efficient data exchange between these applications. Hence, there is a need for cohesive integration of scientific data format in AI frameworks. In this work, we present Stimulus: a data management framework for efficiently consuming scientific data into any AI framework. We utilize the tensor infrastructure present in all AI frameworks to build a cohesive solution. Stimulus provides a novel Dataset abstraction to represent structured scientific data efficiently. Additionally, we describe the design and implementation of tensor operators to build an integrated data pipeline for scientific data formats efficiently. The evaluation shows the effectiveness of the framework to accelerate scientific data formats. Specifically, Stimulus can accelerate the scientific data pipeline by 3x for AI applications.

## Dependencies
- gcc-10.2.0 with experimental features.
- tensorflow > 2.3
- hdf5_opt > 1.10

## Install instructions

```bash
export TENSORFLOW_PATH=<path-to-tf-install> # example /home/hdevarajan/anaconda3/lib/python3.8/site-packages/tensorflow/
cd <project_dir>
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=<path-to-dependencies> ../
make -j
make install
```

## Evaluations

All evaluations are based on the [DLIO benchmark](https://github.com/hariharan-devarajan/dlio_benchmark). Check [usage for more details](https://github.com/hariharan-devarajan/dlio_benchmark#usage). Additionally, we perform post processing of logs using [VaniDL](https://github.com/hariharan-devarajan/vanidl/).


### Scientific Format Input Pipeline Evaluations
```bash
# Generate data
DATA_DIR=/projects/datascience/dhari/stimulus/evaluation/1
OPTS=(-f hdf5_opt -fa shared -nf 1 -sf 1024 -df ${DATA_DIR} -rl 1048576 -gd 1 -go 1 -k 1)
python ./dlio_benchmark.py ${OPTS[@]}

# Test Execution: Anatomy of Scientific Format Input Pipeline 
qsub scripts/anatomy.sh

# Test Execution: Performance evaluations for Scientific Format Input Pipeline 
qsub scripts/input_pipeline_performance.sh 1
qsub scripts/input_pipeline_performance.sh 2
qsub scripts/input_pipeline_performance.sh 4
qsub scripts/input_pipeline_performance.sh 8
qsub scripts/input_pipeline_performance.sh 16
qsub scripts/input_pipeline_performance.sh 64
```

### Impact of Data and Processing Decoupling

```bash
# Generate data
DATA_DIR=/projects/datascience/dhari/stimulus/evaluation/2
OPTS=(-f hdf5_opt -fa shared -nf 1 -sf 32768 -df ${DATA_DIR} -rl 8192 -gd 1 -go 1 -k 1)
python ./dlio_benchmark.py ${OPTS[@]}

# Test Execution: Impact of Data and Processing Decoupling
qsub scripts/decoupling.sh 4096
qsub scripts/decoupling.sh 16384
qsub scripts/decoupling.sh 65536
qsub scripts/decoupling.sh 262144
qsub scripts/decoupling.sh 1048576
qsub scripts/decoupling.sh 4194304
qsub scripts/decoupling.sh 16777216
```

### Impact of Overlapping Compute with Input Pipeline

```bash
# Generate data
DATA_DIR=/projects/datascience/dhari/stimulus/evaluation/3
OPTS=(-f hdf5_opt -fa shared -nf 1 -sf 32768 -df ${DATA_DIR} -rl 8192 -gd 1 -go 1 -k 1)
python ./dlio_benchmark.py ${OPTS[@]}

# Test Execution: Impact of Data and Processing Decoupling

qsub scripts/overlap.sh 0
qsub scripts/overlap.sh 0.005
qsub scripts/overlap.sh 0.01
qsub scripts/overlap.sh 0.015
qsub scripts/overlap.sh 0.02
```

### Impact of Read Parallelism

```bash
# Generate data
DATA_DIR=/projects/datascience/dhari/stimulus/evaluation/4
OPTS=(-f hdf5_opt -fa shared -nf 1 -sf 32768 -df ${DATA_DIR} -rl 8192 -gd 1 -go 1 -k 1)
python ./dlio_benchmark.py ${OPTS[@]}

# Test Execution: Impact of Data and Processing Decoupling

qsub scripts/read_parallel.sh 0
qsub scripts/read_parallel.sh 1
qsub scripts/read_parallel.sh 2
qsub scripts/read_parallel.sh 4
qsub scripts/read_parallel.sh 8
qsub scripts/read_parallel.sh 16
qsub scripts/read_parallel.sh 32
```

### Impact of Processing Parallelism

```bash
# Generate data
DATA_DIR=/projects/datascience/dhari/stimulus/evaluation/5
OPTS=(-f hdf5_opt -fa shared -nf 1 -sf 32768 -df ${DATA_DIR} -rl 8192 -gd 1 -go 1 -k 1)
python ./dlio_benchmark.py ${OPTS[@]}

# Test Execution: Impact of Data and Processing Decoupling

qsub scripts/preproc_parallel.sh 0
qsub scripts/preproc_parallel.sh 1
qsub scripts/preproc_parallel.sh 2
qsub scripts/preproc_parallel.sh 4
qsub scripts/preproc_parallel.sh 8
qsub scripts/preproc_parallel.sh 16
qsub scripts/preproc_parallel.sh 32
```

### Impact of Data Prefetching

```bash
# Generate data
DATA_DIR=/projects/datascience/dhari/stimulus/evaluation/6
OPTS=(-f hdf5_opt -fa shared -nf 1 -sf 32768 -df ${DATA_DIR} -rl 8192 -gd 1 -go 1 -k 1)
python ./dlio_benchmark.py ${OPTS[@]}

# Test Execution: Impact of Data and Processing Decoupling

qsub scripts/prefetch.sh 0
qsub scripts/prefetch.sh 26843545.6
qsub scripts/prefetch.sh 53687091.2
qsub scripts/prefetch.sh 80530636.8
qsub scripts/prefetch.sh 107374182.4
qsub scripts/prefetch.sh 134217728
qsub scripts/prefetch.sh 161061273.6
qsub scripts/prefetch.sh 187904819.2
qsub scripts/prefetch.sh 214748364.8
qsub scripts/prefetch.sh 241591910.4
qsub scripts/prefetch.sh 268435456
```

### AI Workload Cosmic Tagger through DLIO
```bash
qsub scripts/cosmic_tagger.sh
```

### AI Workload DFFN through DLIO
```bash
qsub scripts/dffn.sh
```

