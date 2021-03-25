#include <stimulus/operators/sample_creator/hdf5_sample_creator.h>

Generator HDF5SampleCreator::execute() {
  Data sample;

  switch (dataset_.boundary_type_) {
    case BoundaryType::FIXED: {
      auto sample_size = dataset_.sample_boundaries_[0].first;
      uint32_t size_emitted = 0;
      while (size_emitted < object_.size_) {

        sample.buffer_ = malloc(sample_size);
        sample.size_ = sample_size;
        memcpy(sample.buffer_, (char*)object_.buffer_ + size_emitted, sample_size);
        co_yield sample;
      }
      break;
    }
    case BoundaryType::VARIABLE: {
      break;
    }
  }
  co_return sample;
}
