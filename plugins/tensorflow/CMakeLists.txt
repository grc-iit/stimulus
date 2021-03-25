include_directories($ENV{TENSORFLOW_PATH}/include)
include_directories(${CMAKE_SOURCE_DIR}/include)
FIND_PACKAGE(HDF5)
include_directories(${HDF5_INCLUDE_DIRS})
FIND_PACKAGE(MPI)
include_directories(${MPI_C_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_BINARY_DIR}/core -fcoroutines  -std=c++20 -fno-exceptions")
set(TENSORFLOW_OPERATOR_SRC hdf5_io_op.h hdf5_io_op.cpp hdf5_sample_creator_op.cpp hdf5_sample_creator_op.h)
add_library(stimulus_tf_op SHARED ${TENSORFLOW_OPERATOR_SRC})
target_link_libraries(stimulus_tf_op -lstimulus)
target_link_libraries(stimulus_tf_op ${HDF5_LIBRARIES})
target_link_libraries(stimulus_tf_op ${MPI_C_LIBRARIES})


