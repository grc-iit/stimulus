#ifndef STIMULUS_HDF5_IO_OP_H
#define STIMULUS_HDF5_IO_OP_H

#include <stimulus/common/datastructure.h>
#include <tensorflow/core/framework/op_kernel.h>
#include <stimulus/operators/io_operator/hdf5_io_operator.h>

#include "hdf5_io_op.h"

using namespace tensorflow;

static std::string toString(const Eigen::MatrixXd& mat){
  std::stringstream ss;
  ss << mat;
  return ss.str();
}

class HDF5IOOp : public OpKernel{
 public:
  explicit HDF5IOOp(OpKernelConstruction* context) : OpKernel(context) {}

  void Compute(OpKernelContext* context) override {
    // Grab the input tensor
    auto type = context->input(0).flat<int>().data();
    auto name = context->input(1).flat<int>();
    auto field_name = context->input(2).flat<int>();
    auto label_name = context->input(3).flat<int>();
    auto boundary_type = context->input(4).flat<int>().data();
    auto transfer_size= context->input(6).flat<size_t>().data();
    auto element_index= context->input(7).flat<size_t>().data();
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
    auto io_operator = HDF5IOOperator(dataset, *transfer_size, *element_index);
    Data d = io_operator.execute();

    TensorShape shape;
    shape.AddDim(d.size_);
    // Create an output tensor
    Tensor* output_tensor = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(0, shape,
                                                     &output_tensor));
    auto output_flat = output_tensor->flat<int>();
    memcpy(output_flat.data(), d.buffer_, d.size_);
  }
};

#endif  // STIMULUS_HDF5_IO_OP_H
