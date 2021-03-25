#ifndef STIMULUS_ABSTRACT_SAMPLE_CREATOR_H
#define STIMULUS_ABSTRACT_SAMPLE_CREATOR_H
#include <stimulus/operators/operator.h>

template <typename T, typename R>
class AbstractSampleCreator : public Operator<R> {
 protected:
  T object_;
  Dataset dataset_;

 public:
  AbstractSampleCreator(T object, Dataset dataset)
      : Operator<R>(), object_(object), dataset_(dataset) {}
};
#endif  // STIMULUS_ABSTRACT_SAMPLE_CREATOR_H
