#ifndef MY_PROMISE_WEAKMM_H
#define MY_PROMISE_WEAKMM_H

#include <atomic>
#include <optional>
#include <exception>
#include <stdexcept>
#include <thread>
#include <utility>

namespace mpcs 
{

  enum class State : uint8_t { empty, val, exc };

  template<typename T>
  struct SharedState 
  {
    std::atomic<State>      state{State::empty};
    std::optional<T>        value;      
    std::exception_ptr      exception;
  };

  template<typename T>
  class MyFuture;

  template<typename T>
  class MyPromise 
  {
  public:
    MyPromise()
      : sharedState(std::make_shared<SharedState<T>>())
    {}

    // set a value: 1) construct it, 2) release‐store the new state
    void set_value(const T& v) 
    {
      sharedState->value.emplace(v);
      sharedState->state.store(State::val, std::memory_order_release);
    }

    void set_value(T&& v) 
    {
      sharedState->value.emplace(std::move(v));
      sharedState->state.store(State::val, std::memory_order_release);
    }

    void set_exception(std::exception_ptr e) 
    {
      sharedState->exception = e;
      sharedState->state.store(State::exc,
                               std::memory_order_release);
    }

    MyFuture<T> get_future() 
    {
      return MyFuture<T>(sharedState);
    }

  private:
    std::shared_ptr<SharedState<T>> sharedState;
  };

  template<typename T>
  class MyFuture 
  {
  public:
    MyFuture(const MyFuture&) = delete;
    MyFuture(MyFuture&&) = default;

    // Blocks by spinning + yielding; as soon as
    // state!=empty (acquire‐load), we know the
    // preceding write to value/exception happened
    T get() 
    {
      State s;
      while ((s = sharedState->state.load(std::memory_order_acquire)) == State::empty)
      {
        std::this_thread::yield();
      }

      if (s == State::val) 
      {
        return std::move(*sharedState->value);
      } 
      else if (s == State::exc) 
      {
        std::rethrow_exception(sharedState->exception);
      } 
      else 
      {
        throw std::runtime_error("MyFuture in invalid state");
      }
    }

  private:
    friend class MyPromise<T>;
    explicit MyFuture(std::shared_ptr<SharedState<T>> const& ss)
      : sharedState(ss)
    {}

    std::shared_ptr<SharedState<T>> sharedState;
  };

}

#endif