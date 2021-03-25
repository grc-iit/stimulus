#include "hdf5_io_op.h"

REGISTER_KERNEL_BUILDER(Name("HDF5IOOp").Device(DEVICE_CPU), HDF5IOOp);
