#ifndef STIMULUS_HDF5_IO_OPERATOR_H
#define STIMULUS_HDF5_IO_OPERATOR_H

#include <hdf5.h>

#include "stimulus/operators/io_operator/abstract_io_operator.h"

class HDF5IOOperator : public AbstractIOOperator<Data> {
 public:
  HDF5IOOperator(Dataset dataset, size_t transfer_size, size_t element_index)
      : AbstractIOOperator(dataset, transfer_size, element_index) {}
  Data execute() override;
};

#endif  // STIMULUS_HDF5_IO_OPERATOR_H
