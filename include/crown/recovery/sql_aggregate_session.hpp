#pragma once

#include "crown/recovery/sql_aggregate_files.hpp"
#include "crown/recovery/sql_aggregate_checkpoint.hpp"

namespace crown::recovery::sql_aggregate {
struct SessionPaths { std::string_view root,sink; }; // Borrowed only by factories.
struct SessionIdentity { Id query_id{},sink_id{}; };
// Cold binder options can own ordinary parameter DTOs. Factories borrow this
// configuration only for the call; the session retains fixed live limits.
struct SessionLimits {
  AdmissionLimits admission;
  CheckpointLimits checkpoint;
  runtime::sql_rows::SourceSnapshotLimits capture;
  runtime::sql_aggregate::RebuildLimits rebuild;
  FileLimits wal,sink;
  GenerationLimits generation;
  std::uint64_t history_generations=128;
  std::uint64_t replay_commands=65536,replay_codec_work=4ULL*1024*1024*1024;
  bool repair_torn_tail=true;
};
enum class SessionFault : std::uint8_t { state,binding,progress,limit,transition,tail };
class SessionFailure final : public std::exception {
 public:
  explicit SessionFailure(SessionFault fault) noexcept : fault_(fault) {}
  [[nodiscard]] SessionFault fault() const noexcept { return fault_; }
  [[nodiscard]] const char* what() const noexcept override { return "R2 session rejected"; }
 private:
  SessionFault fault_;
};
struct SessionState {
  // W is an Input's command sequence, not its WAL frame ordinal. Reject advances
  // I alone; successful empty/no-op input still advances C and needs a sink epoch.
  std::uint64_t logged=0,disposed=0,committed=0,delivered=0,generation=0;
  bool pending=false,output_pending=false;
};
struct Decision {
  std::uint64_t command_sequence,physical_sequence;
  std::optional<RejectReason> rejected; // No resource/contract-error tag.
};
struct ReplayStatistics {
  std::uint64_t commands=0,codec_work=0;
  // Successful native preparations only; original per-command grants, including
  // disabled caps, remain unchanged. These are not a preemptive CPU allowance.
  std::uint64_t native_work=0,group_work=0;
  storage::IndexWork source_work{};
};

// Synchronous single-writer owner over genuine SQL/native state and actual root,
// WAL and sink locks. One logged head and one canonical committed output spool;
// all calls/borrows must be serialized. See docs/sql_aggregate_session.md.
class Session {
  struct Data;
 public:
  // Normal capture_changes must be explicitly enabled: exact group output is
  // prepared before Commit fsync. Neither factory accepts editable runtime DTOs.
  [[nodiscard]] static Session create_into(const resource::MemoryAccount&,SessionPaths,SessionIdentity,
      frontend::SqlAggregateProgram,const FreeConnexTree&,const PhysicalOptions&,
      runtime::sql_aggregate::Options,const SessionLimits& = {});
  [[nodiscard]] static Session recover_into(const resource::MemoryAccount&,SessionPaths,const Id& query_id,
      const SessionLimits& = {});
  ~Session();
  Session(const Session&)=delete;Session& operator=(const Session&)=delete;
  Session(Session&&) noexcept;Session& operator=(Session&&)=delete;
  [[nodiscard]] bool requires_reopen() const noexcept;
  [[nodiscard]] SessionState state() const;
  [[nodiscard]] GenerationRoot selected_root() const;
  [[nodiscard]] const Descriptor& descriptor() const &;
  const Descriptor& descriptor() const &&=delete;
  [[nodiscard]] const io::AccountedInputProgress& progress() const &;
  const io::AccountedInputProgress& progress() const &&=delete;
  [[nodiscard]] std::optional<ReaderPosition> reader_position() const;
  [[nodiscard]] std::optional<ReaderPosition> logged_reader_position() const;
  [[nodiscard]] std::optional<InputView> pending_input() const &;
  std::optional<InputView> pending_input() const &&=delete;
  [[nodiscard]] std::optional<std::string_view> output() const &;
  std::optional<std::string_view> output() const &&=delete;
  [[nodiscard]] ReplayStatistics replay_statistics() const;
  [[nodiscard]] runtime::sql_aggregate::Snapshot snapshot(runtime::aggregate::SnapshotLimits={}) const;
  [[nodiscard]] std::uint64_t source_weight(TableId,std::span<const runtime::sql_rows::Cell>) const;
  // log owns rows and prepays progress before Input I/O. decide retries only that
  // same head. Resource failure leaves it pending; semantic Reject consumes I.
  void log(const InputView&) &;
  [[nodiscard]] Decision decide() &;
  bool deliver() &; // False if no spool; success confirms actual sink bytes/receipt.
  [[nodiscard]] GenerationRoot checkpoint() &; // Only W=I,D=C, no head/spool.
 private:
  explicit Session(resource::AccountedUnique<Data>) noexcept;
  [[nodiscard]] Data& data() const;
  static void replay(std::string_view,const Inspected&,const WalState&,void*);
  static void validate_files(Data&);
  static GenerationRoot select_checkpoint(Data&,bool initial);
  resource::AccountedUnique<Data> data_;
};
} // namespace crown::recovery::sql_aggregate
