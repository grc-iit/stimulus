//
// Created by hdevarajan on 3/25/21.
//

#ifndef STIMULUS_ABSTRACT_IO_OPERATOR_H
#define STIMULUS_ABSTRACT_IO_OPERATOR_H

#include <stimulus/common/datastructure.h>
#include <stimulus/operators/operator.h>

#include <cstddef>

template <typename R>
class AbstractIOOperator : public Operator<R> {
 protected:
  Dataset dataset_;
  size_t transfer_size_;
  size_t element_index_;

 public:
  AbstractIOOperator(Dataset dataset, size_t transfer_size,
                     size_t element_index)
      : Operator<R>(),
        dataset_(dataset),
        transfer_size_(transfer_size),
        element_index_(element_index) {}
};

#endif  // STIMULUS_ABSTRACT_IO_OPERATOR_H
