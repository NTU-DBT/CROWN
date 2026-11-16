#pragma once

#include <stdexcept>
#include <string>
#include <utility>

namespace crown {
class Error : public std::runtime_error {
 public:
  Error(std::string code, const std::string& message)
      : std::runtime_error(message), code_(std::move(code)) {}
  [[nodiscard]] const std::string& code() const noexcept { return code_; }
 private:
  std::string code_;
};
}  // namespace crown
