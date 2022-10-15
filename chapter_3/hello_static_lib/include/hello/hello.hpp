#pragma once

#include <string>

namespace hello {
// example class that is explicitly exported into a dll.
class Hello {
private:
  const std::string name_;

public:
  explicit Hello(std::string name) : name_(std::move(name)) {}
  void greet() const;
};

} // namespace hello