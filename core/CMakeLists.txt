set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines -std=c++20 -fno-exceptions -L$ENV{TENSORFLOW_PATH}/lib")
include_directories($ENV{TENSORFLOW_PATH}/include)

include_directories(include)
include_directories(src)
set(STIMULUS_PUBLIC_INCLUDE include/stimulus/stimulus.h)
set(STIMULUS_PRIVATE_INCLUDE
        src/stimulus/operators/io_operator/abstract_io_operator.h
        include/stimulus/operators/io_operator/hdf5_io_operator.h
        src/stimulus/operators/sample_converter/abstract_sample_converter.h
        include/stimulus/operators/sample_converter/hdf5_sample_converter.h
        src/stimulus/operators/sample_creator/abstract_sample_creator.h
        include/stimulus/operators/sample_creator/hdf5_sample_creator.h
        include/stimulus/common/datastructure.h
        include/stimulus/common/enumeration.h src/stimulus/operators/operator.h include/stimulus/common/singleton.h)
set(STIMULUS_SRC src/stimulus/stimulus.cpp
        src/stimulus/operators/io_operator/hdf5_io_operator.cpp
        src/stimulus/operators/sample_converter/hdf5_sample_converter.cpp
        src/stimulus/operators/sample_creator/hdf5_sample_creator.cpp)

FIND_PACKAGE(HDF5)
include_directories(${HDF5_INCLUDE_DIRS})

FIND_PACKAGE(MPI)
include_directories(${MPI_C_INCLUDE_DIRS})

add_library(stimulus SHARED ${STIMULUS_SRC} ${STIMULUS_PUBLIC_INCLUDE} ${STIMULUS_PRIVATE_INCLUDE})
target_link_libraries(stimulus ${HDF5_LIBRARIES})
target_link_libraries(stimulus ${MPI_C_LIBRARIES})