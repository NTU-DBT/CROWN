#pragma once

#include "crown/recovery/sql_aggregate_records.hpp"

namespace crown::recovery::sql_aggregate {
namespace detail { class DescriptorFactory; }
struct DescriptorLimits {
  ImageLimits image;
  std::uint64_t cbor_items = 1000000;
  std::size_t cbor_depth = 128;
};
// Cold receiving limits, separate from the stored operational runtime policy.
// The binder/lowerer work counters must be finite. Their ordinary compiler/DOM
// workspace is separate from account-owned retained metadata and runtime state.
struct AdmissionLimits {
  DescriptorLimits descriptor;
  frontend::SqlAggregateBindOptions binding;
  PhysicalLimits lowering;
};
struct InspectedDescriptor {
  std::string_view binding_image, recipe; // Borrow the exact supplied frame.
  Hash sha256; // Whole-frame identity used by a separately selected root.
  ImageStatistics statistics;
};

// Immutable genuine compiler/native metadata and original operational policy.
// Sharing retains their receiving account. No DTO constructor/import path exists;
// file selection, durable output and source-row recovery are separate boundaries.
class Descriptor {
  struct Data;
 public:
  Descriptor() noexcept = default;
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
  [[nodiscard]] const frontend::SqlAggregateProgram& program() const &;
  const frontend::SqlAggregateProgram& program() const && = delete;
  [[nodiscard]] const CompiledProgram& native_program() const &;
  const CompiledProgram& native_program() const && = delete;
  [[nodiscard]] const runtime::weighted::Binding& native_binding() const &;
  const runtime::weighted::Binding& native_binding() const && = delete;
  [[nodiscard]] const runtime::sql_aggregate::Options& options() const &;
  const runtime::sql_aggregate::Options& options() const && = delete;
  [[nodiscard]] const Hash& sha256() const &;
  const Hash& sha256() const && = delete;
  [[nodiscard]] std::string_view bytes() const &;
  std::string_view bytes() const && = delete;
 private:
  friend class detail::DescriptorFactory;
  explicit Descriptor(std::shared_ptr<const Data> data) noexcept : data_(std::move(data)) {}
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
struct Admitted {
  Descriptor descriptor;
  runtime::SqlAggregateRuntime runtime; // Genuine empty/static state at C0.
  ImageStatistics statistics; // Codec byte visits only; compiler grants are separate.
};
// Both factories require capture_changes=true and preserve all supplied normal
// arithmetic/work/backend policies. Finite producer limits within the host caps
// bound actual construction; otherwise one finite host check precedes it. Neither
// path rewrites original limits or claims minimum height. No mutable native owner
// is created from an imported DTO.
[[nodiscard]] Admitted admit_into(const resource::MemoryAccount&,
    frontend::SqlAggregateProgram,const FreeConnexTree&,const PhysicalOptions&,
    runtime::sql_aggregate::Options,const AdmissionLimits& = {});
// Inspect is allocation-free bounded wire/CBOR validation. Rebind additionally
// authenticates original SQL/catalog/typed parameters/AVG through real factories,
// and compares complete binding/recipe/native identity bytes before returning.
[[nodiscard]] InspectedDescriptor inspect_descriptor(std::string_view,DescriptorLimits = {});
[[nodiscard]] Admitted rebind_into(const resource::MemoryAccount&,std::string_view,
    const AdmissionLimits& = {});
} // namespace crown::recovery::sql_aggregate
