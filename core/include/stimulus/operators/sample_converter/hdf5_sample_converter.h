//
// Created by hdevarajan on 3/25/21.
//

#ifndef STIMULUS_HDF5_SAMPLE_CONVERTER_H
#define STIMULUS_HDF5_SAMPLE_CONVERTER_H
#include <stimulus/common/datastructure.h>
#include <tensorflow/core/framework/op_kernel.h>

#include "stimulus/operators/sample_converter/abstract_sample_converter.h"
using namespace tensorflow;

class HDF5SampleConverter : public AbstractSampleConverter<Data, Tensor*> {
  Tensor* execute() override;
};

#endif  // STIMULUS_HDF5_SAMPLE_CONVERTER_H
