//
// Created by hdevarajan on 3/25/21.
//

#ifndef STIMULUS_HDF5_SAMPLE_CREATOR_H
#define STIMULUS_HDF5_SAMPLE_CREATOR_H

#include <stdio.h>
#include <stimulus/common/datastructure.h>

#include <coroutine>
#include <cstring>
#include <future>

#include "stimulus/operators/sample_creator/abstract_sample_creator.h"

using namespace std;

struct Generator {
  struct Promise;

  // compiler looks for promise_type
  using promise_type = Promise;
  coroutine_handle<Promise> coro;
  Generator(coroutine_handle<Promise> h) : coro(h) {}

  ~Generator() {
    if (coro) coro.destroy();
  }
  // get current value of coroutine
  Data value() { return coro.promise().val; }

  // advance coroutine past suspension
  bool next() {
    coro.resume();
    return !coro.done();
  }
  struct Promise {
    // current value of suspended coroutine
    Data val;

    // called by compiler first thing to get coroutine result
    Generator get_return_object() {
      return Generator{coroutine_handle<Promise>::from_promise(*this)};
    }
    // called by compiler first time co_yield occurs
    suspend_always initial_suspend() { return {}; }

    // required for co_yield
    suspend_always yield_value(Data x) {
      val = x;
      return {};
    }
    // required for co_yield
    suspend_always return_value(Data x) {
      val = x;
      return {};
    }
    // called by compiler for coroutine without return
    suspend_never return_void() { return {}; }

    // called by compiler last thing to await final result
    // coroutine cannot be resumed after this is called
    suspend_always final_suspend() { return {}; }
  };
};

class HDF5SampleCreator : public AbstractSampleCreator<Data, Generator> {
 public:
  HDF5SampleCreator(Data object, Dataset dataset)
      : AbstractSampleCreator<Data, Generator>(object, dataset) {}
  Generator execute() override;
};

#endif  // STIMULUS_HDF5_SAMPLE_CREATOR_H
