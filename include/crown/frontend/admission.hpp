#pragma once

#include "crown/frontend/normalize.hpp"
#include "crown/planner/recognize.hpp"

namespace crown::frontend {
enum class AdmissionStatus { admitted, syntax_error, semantic_error, unsupported_semantics, cyclic_body, non_free_connex, resource_limit };
enum class AdmissionRoute { free_connex, constant_empty };
struct AdmissionOptions {
  BindOptions binding;
  std::vector<SqlValue> parameters;
  NormalizeLimits normalization;
  planner::RecognitionLimits recognition;
};
struct AdmissionLimits {
  BindLimits binding;
  NormalizeLimits normalization;
  planner::RecognitionLimits recognition;
};
struct AdmissionWork {
  std::optional<std::uint64_t> binding;
  std::optional<std::uint64_t> normalization;
  std::optional<std::uint64_t> recognition;
};
struct AdmissionResult {
  AdmissionStatus status = AdmissionStatus::semantic_error;
  std::string phase;
  std::optional<SqlDiagnostic> diagnostic;
  std::optional<NormalizedSql> program;
  std::optional<planner::StructuralAnalysis> structure;
  std::optional<AdmissionRoute> route;
  AdmissionLimits limits;
  AdmissionWork work;
};
// Frontend + structural admission only: this does not lower a physical plan,
// certify a minimum height, or start a maintained runtime.
[[nodiscard]] AdmissionResult admit_sql(std::string_view source, const Catalog& catalog, const AdmissionOptions& options = {});
// Owns a producer/reader-validated program. Legacy v1 is grounded to v2 first.
[[nodiscard]] AdmissionResult admit_normalized(NormalizedSql program, planner::RecognitionLimits limits = {}, NormalizeLimits grounding_limits = {});
[[nodiscard]] std::string admission_status_name(AdmissionStatus status);
}  // namespace crown::frontend
