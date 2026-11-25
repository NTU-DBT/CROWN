#pragma once

#include "crown/recovery/sql_aggregate_records.hpp"
#include "crown/runtime/sql_rows.hpp"

namespace crown::recovery::sql_rows {
namespace detail { struct FrameAccess; }
// These are transport data only; aliases convey no aggregate/runtime authority.
using Hash = sql_aggregate::Hash;
using Id = sql_aggregate::Id;
using Binding = sql_aggregate::Binding;
using WalHeader = sql_aggregate::WalHeader;
using SinkHeader = sql_aggregate::SinkHeader;
using SourcePosition = sql_aggregate::SourcePosition;
using ReaderPosition = sql_aggregate::ReaderPosition;
using InputView = sql_aggregate::InputView;
using InputInfo = sql_aggregate::InputInfo;
using Commit = sql_aggregate::Commit;
using Limits = sql_aggregate::Limits;
using ScanLimits = sql_aggregate::ScanLimits;
using PendingInput = sql_aggregate::PendingInput;
using WalState = sql_aggregate::WalState;

// Stable plain-row semantic allowlist; resource/contract failures have no tag.
enum class RejectReason : std::uint8_t {
  weight_mismatch, source_overflow, unique_violation, foreign_key_violation,
  annotation_overflow,
  abandoned  // caller-requested durable rejection of a pending head (Session::abandon_pending)
};
struct Reject {
  std::uint64_t input_ordinal = 0;
  Hash input_sha256{};
  std::uint64_t command_sequence = 0, physical_sequence = 0;
  RejectReason reason = RejectReason::weight_mismatch;
  bool operator==(const Reject&) const = default;
};
// Borrow the genuine prepared SQL presentation through encode(). No snapshots,
// mutable row DTO import or second owning nullable-delta vector is required.
struct RowEpochView {
  std::uint64_t generation, input_sequence, physical_sequence;
  Hash input_sha256;
  bool changed;
  const runtime::SqlRowsRuntime::PreparedBatch* output;
};
enum class Kind : std::uint8_t { wal_header, input, commit, reject, sink_header, row_epoch };
using PayloadView = std::variant<WalHeader,InputView,Commit,Reject,SinkHeader,RowEpochView>;
struct RowInfo {
  std::uint64_t generation = 0, input_sequence = 0, physical_sequence = 0, rows = 0;
  Hash input_sha256{};
  bool changed = false, output_changed = false;
};
struct Inspected {
  Kind kind;
  std::uint64_t ordinal;
  Hash body_sha256;
  ImageStatistics statistics;
  std::variant<WalHeader,InputInfo,Commit,Reject,SinkHeader,RowInfo> payload;
};

// Immutable owned record bytes. A frame is neither a durable receipt nor native
// admission authority; every borrow needs the same live, unmoved handle.
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

// One owned frame and two flat view arrays; TEXT and source names borrow the
// frame. Moves preserve backing addresses and copying/rvalue views are denied.
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
  Frame frame_;
  ImageVector<runtime::sql_rows::Cell> cells_;
  ImageVector<runtime::sql_rows::SourceReplacement> replacements_;
};

// Durable codecs require an explicit retain_binding_image=true compilation.
// Genuine program types validate complete nullable input/output schemas. Row
// output uses canonical typed row bytes and nonzero signed uint64 magnitudes;
// DISTINCT changes are unit and EXISTS is a whole Boolean replacement pair.
// encode spends the active token's fixed output allowance across its reads and
// owns one scratch row, packed key bytes and sort metadata under this account.
[[nodiscard]] Frame encode(const resource::MemoryAccount&,const frontend::SqlRowsProgram&,
    std::uint64_t ordinal,const PayloadView&,Limits = {});
[[nodiscard]] Inspected inspect(const frontend::SqlRowsProgram&,std::string_view,Limits = {});
[[nodiscard]] DecodedInput decode_input(const resource::MemoryAccount&,
    const frontend::SqlRowsProgram&,std::string_view,Limits = {});
[[nodiscard]] DecodedInput encode_input(const resource::MemoryAccount&,
    const frontend::SqlRowsProgram&,std::uint64_t,const InputView&,Limits = {});

// Fixed candidate state publishes only after complete validation. Actual file
// identity, sink coverage, genuine replay and tail repair belong to Session.
class WalCursor {
 public:
  explicit WalCursor(ScanLimits limits = {}) noexcept : limits_(limits) {}
  WalCursor(const WalCursor&) = delete;
  WalCursor& operator=(const WalCursor&) = delete;
  WalCursor(WalCursor&&) noexcept = default;
  WalCursor& operator=(WalCursor&&) noexcept = default;
  [[nodiscard]] Inspected feed(const frontend::SqlRowsProgram&,std::string_view);
  [[nodiscard]] const WalState& state() const & noexcept { return state_; }
  const WalState& state() const && = delete;
 private:
  friend class WalFile;
  ScanLimits limits_;
  WalState state_;
};
inline constexpr std::size_t frame_prefix_size = 84, frame_header_size = 148;
} // namespace crown::recovery::sql_rows
