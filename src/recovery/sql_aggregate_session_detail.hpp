#pragma once

#include "crown/recovery/sql_aggregate_session.hpp"
#include "generation_detail.hpp"
#include <type_traits>

namespace crown::recovery::sql_aggregate {
namespace session_detail {
void require(bool,SessionFault=SessionFault::state);
[[nodiscard]] std::optional<RejectReason> semantic(std::string_view) noexcept;
[[nodiscard]] GenerationDeliveryAnchor anchor(const SinkReceipt&);
}
// Private ownership order closes head/spool and file locks before native/root
// teardown, with the receiving account retained through every member destructor.
struct Session::Data {
  // Retain only bounds needed by operations/replay. Caller-owned cold binder
  // parameters never become ordinary-heap state hidden inside this owner.
  struct LiveLimits {
    CheckpointLimits checkpoint;
    runtime::sql_rows::SourceSnapshotLimits capture;
    FileLimits wal,sink;
    std::uint64_t history_generations,replay_commands,replay_codec_work;
  };
  static_assert(std::is_trivially_copyable_v<LiveLimits>);
  struct Head {
    DecodedInput input;
    io::InputPositions::Prepared position;
  };
  struct Prepared {
    std::optional<runtime::SqlAggregateRuntime::PreparedBatch> token;
    std::optional<RejectReason> rejected;
  };
  resource::MemoryAccount account;
  LiveLimits limits;
  ::crown::recovery::detail::GenerationOwner root;
  Descriptor descriptor;
  runtime::SqlAggregateRuntime native;
  io::AccountedInputProgress progress;
  std::optional<ReaderPosition> reader;
  std::optional<WalFile> wal;
  std::optional<SinkFile> sink;
  std::optional<Head> head;
  std::optional<Frame> spool;
  ReplayStatistics replayed{};
  bool poisoned=false;

  Data(const resource::MemoryAccount&,const SessionLimits&,::crown::recovery::detail::GenerationOwner,
      Descriptor,runtime::SqlAggregateRuntime,io::AccountedInputProgress,std::optional<ReaderPosition>);
  void ready() const;
  [[nodiscard]] Head own(DecodedInput);
  [[nodiscard]] Prepared prepare();
  [[nodiscard]] Frame epoch(const runtime::sql_aggregate::Epoch&,bool replay);
  void publish(Prepared&,std::optional<Frame>);
  [[nodiscard]] Limits codec_limits(bool output) const;
  void charge_codec(std::uint64_t);
  void observe(const runtime::sql_aggregate::Epoch&);
};
} // namespace crown::recovery::sql_aggregate
