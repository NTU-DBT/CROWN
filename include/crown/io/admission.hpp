#pragma once

#include "crown/frontend/admission.hpp"
#include "crown/io/document.hpp"

namespace crown::io {
[[nodiscard]] Json write_admission(const frontend::AdmissionResult& result);
// Strict v1 options with optional parameter_types, parameter_values and limits.
[[nodiscard]] frontend::AdmissionOptions read_admission_options(std::string_view text);
}  // namespace crown::io
