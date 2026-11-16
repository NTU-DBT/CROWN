#pragma once

#include "crown/recovery/sql_aggregate_descriptor.hpp"
#include "crown/recovery/generation.hpp"
#include "crown/io/input_progress.hpp"

namespace crown::recovery::sql_aggregate {
namespace detail { struct CheckpointAccess; }
struct CheckpointMetadata {
  Binding binding;
  std::uint64_t generation = 0, physical_sequence = 0, command_sequence = 0;
  GenerationDeliveryAnchor delivery;
  bool operator==(const CheckpointMetadata&) const = default;
};
struct CheckpointLimits {
  ImageLimits image{128ULL*1024*1024,1024ULL*1024*1024,4096,65536,1024,1024*1024};
  std::uint64_t sources = 4096, source_bytes = 4096;
};
struct InspectedCheckpoint {
  CheckpointMetadata metadata;
  std::optional<ReaderPosition> reader;
  std::uint64_t sources = 0, rows = 0, max_fields = 0;
  Hash sha256;
  ImageStatistics statistics;
};
// Immutable account-owned wire data. Neither this image nor its delivery DTO is
// a file lock, sink receipt or root-selection capability. The durable owner must
// capture only at W=I,D=C and bind this metadata to actual selected files.
class Checkpoint {
 public:
  Checkpoint(const Checkpoint&) = delete;
  Checkpoint& operator=(const Checkpoint&) = delete;
  Checkpoint(Checkpoint&&) noexcept = default;
  Checkpoint& operator=(Checkpoint&&) noexcept = default;
  [[nodiscard]] std::string_view bytes() const & noexcept { return {bytes_.data(),bytes_.size()}; }
  std::string_view bytes() const && = delete;
  [[nodiscard]] const InspectedCheckpoint& info() const & noexcept { return info_; }
  const InspectedCheckpoint& info() const && = delete;
 private:
  friend struct detail::CheckpointAccess;
  Checkpoint(ImageVector<char> bytes,InspectedCheckpoint info) noexcept : bytes_(std::move(bytes)),info_(std::move(info)) {}
  ImageVector<char> bytes_;
  InspectedCheckpoint info_;
};
struct RestoredCheckpoint {
  runtime::SqlAggregateRuntime runtime;
  io::AccountedInputProgress progress; // I, independently of native C after Reject.
  std::optional<ReaderPosition> reader;
  CheckpointMetadata metadata;
  ImageStatistics statistics; // Cumulative codec work; cold build has separate grants.
  runtime::sql_aggregate::RebuildMetrics build;
};
// Snapshot fields are untrusted data. Encode checks full binding/schema/domain
// and canonicalizes unique physical row keys; final source constraints/arithmetic
// are revalidated by genuine cold restoration. Keep all borrows stable during the
// call. No group/join/native-state mirror is serialized or retained on updates.
[[nodiscard]] Checkpoint encode_checkpoint(const resource::MemoryAccount&,const Descriptor&,
    const runtime::sql_aggregate::SourceSnapshot&,const CheckpointMetadata&,
    const io::AccountedInputProgress&,std::optional<ReaderPosition> = {},CheckpointLimits = {});
// Validate complete hashes, framing, source names and typed canonical physical
// rows without allocating. Descriptor is genuine; metadata remains descriptive.
[[nodiscard]] InspectedCheckpoint inspect_checkpoint(const Descriptor&,std::string_view,CheckpointLimits = {});
// Match the expected metadata before any receiving allocation, then materialize
// complete rows and call the real whole-image factory once at C. Temporary decode
// rows die before return; all returned state belongs to the receiving account.
[[nodiscard]] RestoredCheckpoint restore_checkpoint_into(const resource::MemoryAccount&,const Descriptor&,
    std::string_view,const CheckpointMetadata&,const runtime::sql_aggregate::RebuildLimits&,CheckpointLimits = {});
} // namespace crown::recovery::sql_aggregate
