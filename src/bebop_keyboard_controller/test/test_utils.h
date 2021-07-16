#ifndef TEST_UTILS_H
#define TEST_UTILS_H
#include <functional>
class CallbackMock {
public:
  std::size_t numberOfCalls() { return this->number_of_calls_; }
  
  std::function<void(void)> operator()() {
    return std::bind(&CallbackMock::slot, this);
  }

private:
  void slot() {
    number_of_calls_++;
  };
  std::size_t number_of_calls_{};
};

#endif
