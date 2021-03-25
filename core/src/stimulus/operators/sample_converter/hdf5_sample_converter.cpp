#include <stimulus/operators/sample_converter/hdf5_sample_converter.h>

Tensor* HDF5SampleConverter::execute() {
  Tensor* output_tensor = NULL;
  TensorShape shape;
  shape.AddDim(object_.size_);
  context_->allocate_output(0, shape, &output_tensor);
  auto output_flat = output_tensor->flat<int32>();
  if (output_flat.size() > 0) {
    memcpy(output_flat.data(), object_.buffer_,object_.size_);
  }
  return output_tensor;
}
