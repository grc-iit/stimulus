//
// Created by hdevarajan on 3/25/21.
//

#ifndef STIMULUS_HDF5_SAMPLE_CREATOR_OP_H
#define STIMULUS_HDF5_SAMPLE_CREATOR_OP_H

#include <stimulus/common/datastructure.h>
#include <stimulus/operators/sample_creator/hdf5_sample_creator.h>
#include <tensorflow/core/framework/op_kernel.h>

#include "hdf5_io_op.h"

using namespace tensorflow;

class HDF5SampleCreatorOp : public OpKernel{
 public:
  explicit HDF5SampleCreatorOp(OpKernelConstruction* context) : OpKernel(context) {}

  void Compute(OpKernelContext* context) override {
    // Grab the input tensor
    auto buffer = context->input(0).flat<int>().data();
    auto size = context->input(1).flat<size_t>().data();
    auto type = context->input(2).flat<int>().data();
    auto name = context->input(3).flat<int>();
    auto field_name = context->input(4).flat<int>();
    auto label_name = context->input(5).flat<int>();
    auto boundary_type = context->input(6).flat<int>().data();
    Dataset dataset;
    if(*type == 0) {
      dataset.type_=DatasetType::HDF5;
    }
    dataset.name_=std::string((char*)name.data());
    dataset.field_name=std::string((char*)field_name.data());
    dataset.label_name=std::string((char*)label_name.data());
    if(*boundary_type == 0) {
      dataset.boundary_type_=BoundaryType::FIXED;
    } else if(*boundary_type == 1) {
      dataset.boundary_type_=BoundaryType::VARIABLE;
    }
    Data d;
    d.buffer_ = (void*)buffer;
    d.size_ = *size;

    auto sample_creator = HDF5SampleCreator(d,dataset);
    Data ret = sample_creator.execute().value();

    TensorShape shape;
    shape.AddDim(ret.size_);
    // Create an output tensor
    Tensor* output_tensor = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(0, shape,
                                                     &output_tensor));
    auto output_flat = output_tensor->flat<int>();
    memcpy(output_flat.data(), ret.buffer_, ret.size_);
  }
};
;

#endif  // STIMULUS_HDF5_SAMPLE_CREATOR_OP_H
