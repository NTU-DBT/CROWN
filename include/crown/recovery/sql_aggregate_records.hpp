#pragma once

#include "crown/recovery/image.hpp"
#include "crown/runtime/sql_aggregate.hpp"
#include <variant>

namespace crown::recovery::sql_aggregate {
namespace detail { struct FrameAccess; }
using Hash = std::array<char,64>;
using Id = std::array<char,32>;

// R2 record data only. Binding hashes identify a separately admitted descriptor;
// neither these DTOs nor successful decoding authorize native state or fsync.
struct Binding {
  Id query_id{};
  Hash descriptor_sha256{};
  bool operator==(const Binding&) const = default;
};
struct WalHeader {
  Binding binding;
  std::uint64_t generation = 0;
  Hash checkpoint_sha256{};
  std::uint64_t physical_sequence = 0, command_sequence = 0;
  bool operator==(const WalHeader&) const = default;
};
struct SinkHeader {
  Binding binding;
  Id sink_id{};
  std::uint64_t base_sequence = 0;
  bool operator==(const SinkHeader&) const = default;
};
struct SourcePosition { std::string_view source; std::uint64_t offset; };
// JSONL progress is independent of I/C after rejection. No R1 CSV permutation.
struct ReaderPosition {
  std::uint64_t bytes = 0, records = 0;
  bool operator==(const ReaderPosition&) const = default;
};
struct InputView {
  std::uint64_t command_sequence;
  std::span<const runtime::sql_rows::SourceReplacement> replacements;
  std::optional<SourcePosition> source;
  std::optional<ReaderPosition> reader;
};
struct Commit {
  std::uint64_t input_ordinal = 0;
  Hash input_sha256{};
  std::uint64_t command_sequence = 0, physical_sequence = 0;
  std::uint64_t output_bytes = 0;
  Hash output_sha256{};
  bool operator==(const Commit&) const = default;
};
// Stable explicit semantic allowlist. Resource/contract failures have no tag.
enum class RejectReason : std::uint8_t {
  weight_mismatch, source_overflow, unique_violation, foreign_key_violation,
  aggregate_overflow, annotation_overflow,
  abandoned  // caller-requested durable rejection of a pending head (Session::abandon_pending)
};
struct Reject {
  std::uint64_t input_ordinal = 0;
  Hash input_sha256{};
  std::uint64_t command_sequence = 0, physical_sequence = 0;
  RejectReason reason = RejectReason::weight_mismatch;
  bool operator==(const Reject&) const = default;
};
struct GroupEpochView {
  std::uint64_t generation, input_sequence, physical_sequence;
  Hash input_sha256;
  bool changed, group_changed;
  std::span<const runtime::aggregate::GroupChange> groups;
};
enum class Kind : std::uint8_t { wal_header, input, commit, reject, sink_header, group_epoch };
using PayloadView = std::variant<WalHeader,InputView,Commit,Reject,SinkHeader,GroupEpochView>;
struct Limits {
  ImageLimits record;
  std::uint64_t source_bytes = 4096;
};
struct InputInfo {
  std::uint64_t command_sequence = 0, replacements = 0, cells = 0;
  std::size_t source_begin = 0, source_size = 0;
  std::uint64_t source_offset = 0;
  bool source_present = false;
  std::optional<ReaderPosition> reader;
};
struct GroupInfo {
  std::uint64_t generation = 0, input_sequence = 0, physical_sequence = 0, groups = 0;
  Hash input_sha256{};
  bool changed = false, group_changed = false;
};
struct Inspected {
  Kind kind;
  std::uint64_t ordinal;
  Hash body_sha256;
  ImageStatistics statistics;
  std::variant<WalHeader,InputInfo,Commit,Reject,SinkHeader,GroupInfo> payload;
};

// A move transfers account-owned bytes. Views require a live, unmoved frame;
// immutable bytes avoid a second owned command copy at the coordinator boundary.
class Frame {
 public:
  Frame(const Frame&) = delete;
  Frame& operator=(const Frame&) = delete;
  Frame(Frame&&) noexcept = default;
  Frame& operator=(Frame&&) noexcept = default;
  [[nodiscard]] std::string_view bytes() const & noexcept { return {bytes_.data(),bytes_.size()}; }
  std::string_view bytes() const && = delete;
  [[nodiscard]] const Inspected& info() const & noexcept { return info_; }
  const Inspected& info() const && = delete;
 private:
  friend struct detail::FrameAccess;
  Frame(ImageVector<char> bytes,Inspected info) noexcept : bytes_(std::move(bytes)),info_(std::move(info)) {}
  ImageVector<char> bytes_;
  Inspected info_;
};

// Decoder owns one frame plus two flat arrays; TEXT cells/source names borrow
// that frame. Moves preserve heap addresses; copying/rvalue views are forbidden.
class DecodedInput {
 public:
  DecodedInput(const DecodedInput&) = delete;
  DecodedInput& operator=(const DecodedInput&) = delete;
  DecodedInput(DecodedInput&&) noexcept = default;
  DecodedInput& operator=(DecodedInput&&) noexcept = default;
  [[nodiscard]] InputView view() const &;
  InputView view() const && = delete;
  [[nodiscard]] const Frame& frame() const & noexcept { return frame_; }
  const Frame& frame() const && = delete;
 private:
  friend struct detail::FrameAccess;
  DecodedInput(Frame,ImageVector<runtime::sql_rows::Cell>,ImageVector<runtime::sql_rows::SourceReplacement>) noexcept;
  Frame frame_; // Must outlive every borrowed string and replacement span.
  ImageVector<runtime::sql_rows::Cell> cells_;
  ImageVector<runtime::sql_rows::SourceReplacement> replacements_;
};

// These are bounded transport factories, not durable file/session factories.
// Use a genuine immutable program for nullable SQL type/complete-key validation.
// Encode canonicalizes group keys; inspect validates without allocating. Decode
// validates everything before owning bytes/cells; all retained memory uses the
// supplied account. Work counts byte visits plus bounded sort comparisons.
[[nodiscard]] Frame encode(const resource::MemoryAccount&,const frontend::SqlAggregateProgram&,
    std::uint64_t ordinal,const PayloadView&,Limits = {});
[[nodiscard]] Inspected inspect(const frontend::SqlAggregateProgram&,std::string_view,Limits = {});
[[nodiscard]] DecodedInput decode_input(const resource::MemoryAccount&,
    const frontend::SqlAggregateProgram&,std::string_view,Limits = {});
// Fund the pending command directly, without an encode-then-copy byte buffer.
[[nodiscard]] DecodedInput encode_input(const resource::MemoryAccount&,
    const frontend::SqlAggregateProgram&,std::uint64_t,const InputView&,Limits = {});

struct ScanLimits {
  Limits frame;
  std::uint64_t bytes = 1024ULL*1024*1024, work = 4ULL*1024*1024*1024, records = 1000000;
};
struct PendingInput {
  std::uint64_t ordinal, command_sequence;
  Hash body_sha256;
};
struct WalState {
  WalHeader header;
  std::uint64_t records = 0, bytes = 0, work = 0;
  std::uint64_t logged_sequence = 0, command_sequence = 0, physical_sequence = 0;
  std::uint64_t sink_floor = 0;
  std::optional<PendingInput> pending;
};
// Allocation-free transport validation, not a file lock or native replay owner.
// Feed complete frames in order. Failure preserves the previous validated state;
// files still need independent identity/EOF/tail checks and genuine replay.
class WalCursor {
 public:
  explicit WalCursor(ScanLimits limits = {}) noexcept : limits_(limits) {}
  WalCursor(const WalCursor&) = delete;
  WalCursor& operator=(const WalCursor&) = delete;
  WalCursor(WalCursor&&) noexcept = default;
  WalCursor& operator=(WalCursor&&) noexcept = default;
  [[nodiscard]] Inspected feed(const frontend::SqlAggregateProgram&,std::string_view);
  [[nodiscard]] const WalState& state() const & noexcept { return state_; }
  const WalState& state() const && = delete;
 private:
  friend class WalFile; // Only the concrete file owner can stage spent fixed state.
  ScanLimits limits_;
  WalState state_;
};
inline constexpr std::size_t frame_prefix_size = 84, frame_header_size = 148;
} // namespace crown::recovery::sql_aggregate
