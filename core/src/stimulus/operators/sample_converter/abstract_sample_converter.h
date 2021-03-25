//
// Created by hdevarajan on 3/25/21.
//

#ifndef STIMULUS_ABSTRACT_SAMPLE_CONVERTER_H
#define STIMULUS_ABSTRACT_SAMPLE_CONVERTER_H
#include <stimulus/operators/operator.h>

template <typename T, typename R>
class AbstractSampleConverter : public Operator<R> {
 protected:
  T object_;
  tensorflow::OpKernelContext* context_;

 public:
  AbstractSampleConverter(T object, tensorflow::OpKernelContext context)
      : Operator<R>(), object_(object), context_(context) {}
};
#endif  // STIMULUS_ABSTRACT_SAMPLE_CONVERTER_H
