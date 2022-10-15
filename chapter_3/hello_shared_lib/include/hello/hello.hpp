#pragma once

#include "hello/export_hello.hpp"
#include <string>

namespace hello {
// example class that is explicitly exported into a dll.
class CH3_HELLO_SHARED_EXPORT Hello {
private:
  const std::string name_;

public:
  explicit Hello(std::string name) : name_(std::move(name)) {}
  void greet() const;
};
}
