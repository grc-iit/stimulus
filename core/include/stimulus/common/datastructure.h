#ifndef STIMULUS_DATASTRUCTURE_H
#define STIMULUS_DATASTRUCTURE_H

#include <cstdint>
#include <string>
#include <unordered_map>

#include "enumeration.h"

typedef std::unordered_map<uint32_t, std::pair<uint32_t, uint32_t>> SampleBounderiesType;

struct Dataset {
public:
    DatasetType type_;
    std::string name_;
    std::string field_name;
    std::string label_name;
    BoundaryType boundary_type_;
    SampleBounderiesType sample_boundaries_;

    Dataset() : type_(DatasetType::HDF5),
                name_(), field_name(),
                label_name(),
                boundary_type_(BoundaryType::FIXED),
                sample_boundaries_() {}
};

struct Data {
 public:
  void* buffer_;
  size_t size_;
  Data():buffer_(),size_(0){}
};

#endif //STIMULUS_DATASTRUCTURE_H
