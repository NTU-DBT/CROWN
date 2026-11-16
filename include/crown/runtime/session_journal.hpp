#pragma once
#include "crown/runtime/session_checkpoint.hpp"
#include "crown/recovery/session_file.hpp"
#include "crown/recovery/journal_file.hpp"
namespace crown::runtime {
struct SessionJournalOptions {
  std::array<char,32> query_id{};
  std::uint64_t generation=1;
  SessionCheckpointLimits native;
  recovery::CheckpointFileLimits checkpoint;
  recovery::journal::FileLimits file;
};
enum class SessionJournalFault : std::uint8_t {state,checkpoint,recovery_required,tail,continuation,transition};
class SessionJournalFailure final:public std::exception {
 public:
  explicit SessionJournalFailure(SessionJournalFault fault) noexcept:fault_(fault) {}
  [[nodiscard]] SessionJournalFault fault() const noexcept {return fault_;}
  [[nodiscard]] const char* what() const noexcept override {return "session journal operation rejected";}
 private:
  SessionJournalFault fault_;
};
struct SessionJournalRecoveryOptions {
  SessionJournalOptions journal;
  BuildOptions build;
  std::optional<std::uint64_t> memory_limit_bytes;
  // Codec inspection/materialization work across this reconstruction. Engine
  // and source validation retain their own native limits in journal.native.
  std::uint64_t decode_work=512*1024*1024;
  std::uint64_t source_work=256*1024*1024;
  std::size_t output_rows=65536,output_bytes=64*1024*1024;
  std::optional<std::uint64_t> outputs_after_physical_sequence;
  bool repair_torn_tail=true;
  // False: caller supplies the stream at the first unread byte after the last
  // complete logged input (including a cached uncommitted row). True: seek a
  // caller-owned seekable source from origin to the recovered decoder counter.
  bool seek_source_from_origin=false;
};
struct RecoveredResult {
  // Native tuple copies share payload; legacy tuple copies can clone/allocate.
  // Exact value identity excludes ordinal and does not assert durable delivery.
  std::array<char,32> query_id{};
  std::uint64_t generation=0,physical_sequence=0;
  SignedResult value;
  // Exact semantic identity; spool ordinal and reconstruction iteration order
  // are deliberately excluded. Typed tuple equality has no digest collision.
  [[nodiscard]] bool same_identity(const RecoveredResult& other) const {
    return query_id==other.query_id && generation==other.generation && physical_sequence==other.physical_sequence &&
        value.operation==other.value.operation && value.tuple.values()==other.value.tuple.values();
  }
};
// Records/work/reader/pending fields describe the reconstruction handoff.
// Output fields describe the currently retained replay buffer. Live source
// progress and journal_state remain separate from this recovery report.
struct SessionJournalRecoveryStatus {
  std::uint64_t records=0,decode_work=0,source_work=0,reader_bytes=0,reader_records=0;
  std::size_t output_remaining=0,output_bytes=0;
  std::optional<std::uint64_t> pending_input_sequence;
};
// Fixed metadata about the last confirmed durable prefix. After an I/O failure
// this is a lower bound; recovery_required forbids further session publication.
struct SessionJournalState {
  bool enabled=false,recovery_required=false;
  std::uint64_t records=0,physical_sequence=0,command_sequence=0,next_substep=0;
  std::optional<std::uint64_t> pending_input;
};
} // namespace crown::runtime
