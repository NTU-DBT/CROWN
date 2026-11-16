#pragma once

#include "crown/recovery/sql_aggregate_descriptor.hpp"
#include "crown/resource/ownership.hpp"

namespace crown::recovery::sql_aggregate {
// Concrete Linux regular files for CROWNAG2. One owner holds an advisory flock;
// the containing namespace and other writers must cooperate. See
// docs/sql_aggregate_files.md for the separate native-replay/repair barrier.
enum class FileStage : std::uint8_t {
  path,open_directory,entropy,create_temporary,open_file,stat_file,lock_file,
  read_data,write_data,sync_file,link_file,unlink_temporary,sync_directory,
  truncate_tail,close_file,close_directory,state
};
enum class FileFault : std::uint8_t { io,limit,path,not_regular,busy,changed,truncated,state };
enum class FileOutcome : std::uint8_t { unchanged,unknown,durable };
// Fixed failure metadata requires no allocation. An unknown outcome may have
// reached disk; an append/repair I/O failure requires a fresh owner, even if
// fsync succeeded and only the following stat failed.
class FileFailure final : public std::exception {
 public:
  FileFailure(FileFault fault,FileStage stage,FileOutcome outcome,int error=0,bool cleanup=false) noexcept
      : fault_(fault),stage_(stage),outcome_(outcome),error_(error),cleanup_(cleanup) {}
  [[nodiscard]] FileFault fault() const noexcept { return fault_; }
  [[nodiscard]] FileStage stage() const noexcept { return stage_; }
  [[nodiscard]] FileOutcome outcome() const noexcept { return outcome_; }
  [[nodiscard]] int native_error() const noexcept { return error_; }
  [[nodiscard]] bool temporary_cleanup_failed() const noexcept { return cleanup_; }
  [[nodiscard]] const char* what() const noexcept override { return "R2 file operation failed"; }
 private:
  FileFault fault_; FileStage stage_; FileOutcome outcome_; int error_; bool cleanup_;
};
struct FileLimits {
  ScanLimits scan;
  std::size_t path_bytes=4095,chunk_bytes=1024*1024;
  std::uint64_t operations=1'000'000;
};
// Operations counts attempts routed through the bounded dispatcher; best-effort
// raw close is outside it. Work charges explicit codec/prefix/chain/comparison
// checkpoints. Failed inspect/WAL feed returns no codec work; earlier prefix or
// successful sink-inspect charges remain if later admission fails. Cold metadata
// copying, native replay and wall-clock CPU are outside this logical counter.
struct FileStatistics { std::uint64_t operations=0,work=0; };
struct WalFileState {
  WalState wal; // Confirmed transport frontiers, not native replay authority.
  FileStatistics statistics; // Charged file work; wal.work is codec-only.
  bool torn_tail=false;
};

// No retained command copy: append borrows an immutable pre-funded Frame for
// the call. Validation and a fixed cursor candidate precede the first I/O;
// only fsync plus final stat publishes that candidate. Failed I/O poisons getters.
class WalFile {
  struct Data;
 public:
  [[nodiscard]] static WalFile create(const resource::MemoryAccount&,std::string_view,
      const Descriptor&,const WalHeader&,FileLimits={});
  [[nodiscard]] static WalFile open(const resource::MemoryAccount&,std::string_view,
      const Descriptor&,const WalHeader&,FileLimits={});
  ~WalFile();
  WalFile(const WalFile&)=delete; WalFile& operator=(const WalFile&)=delete;
  WalFile(WalFile&&) noexcept; WalFile& operator=(WalFile&&)=delete;
  [[nodiscard]] WalFileState state() const;
  [[nodiscard]] bool requires_reopen() const noexcept;
  void append(const Frame&) &;
  // Lower transport primitive only. The session must first validate the entire
  // selected root, native replay, sink coverage and both EOF/stamps. Removes
  // only a validated incomplete suffix; a complete pending Input is retained.
  void repair_tail() &;
  void close() &; // Destruction closes best effort; close reports errors once.
 private:
  friend class Session;
  // Only the receiving session factory may visit frames before the whole scan
  // returns. Its effects stay private through later corruption/EOF/sync failure.
  using ReplayVisitor=void(*)(std::string_view,const Inspected&,const WalState&,void*);
  static WalFile open_replay(const resource::MemoryAccount&,std::string_view,
      const Descriptor&,const WalHeader&,FileLimits,ReplayVisitor,void*);
  explicit WalFile(resource::AccountedUnique<Data>) noexcept;
  [[nodiscard]] Data& data() const;
  void validate() &; // Receiving Session's final stamp/EOF barrier, no repair.
  resource::AccountedUnique<Data> data_;
};

// A chained fingerprint of a complete sink prefix, not the raw file SHA256.
// Generation/input_sequence=0 on a header-only prefix mean "no output epoch";
// physical_sequence is then the header's explicitly declared base_sequence.
struct SinkPrefix {
  std::uint64_t generation=0,input_sequence=0,physical_sequence=0,bytes=0;
  Hash content_sha256{};
  bool operator==(const SinkPrefix&) const = default;
};
struct SinkFileState {
  SinkHeader header;
  SinkPrefix prefix;
  std::uint64_t records=0;
  FileStatistics statistics;
  bool torn_tail=false;
};
// Only a healthy, untorn actual SinkFile mints this evidence. Copies preserve
// an observation; they retain no file lock and cannot replace current-owner
// checks by a coordinator. Editable checkpoint/root DTOs cannot construct one.
class SinkReceipt {
 public:
  SinkReceipt(const SinkReceipt&)=default;
  SinkReceipt& operator=(const SinkReceipt&)=delete;
  [[nodiscard]] const SinkHeader& header() const & noexcept { return header_; }
  const SinkHeader& header() const && = delete;
  [[nodiscard]] const SinkPrefix& prefix() const & noexcept { return prefix_; }
  const SinkPrefix& prefix() const && = delete;
 private:
  friend class SinkFile;
  SinkReceipt(const SinkHeader& header,const SinkPrefix& prefix) noexcept : header_(header),prefix_(prefix) {}
  const SinkHeader header_;
  const SinkPrefix prefix_;
};

// One bounded offset/fingerprint entry per complete epoch; no retained output
// payload queue. Epoch ordinal is absolute C, including a sink starting at C>0.
// I strictly increases across epochs (Reject can skip I); generation never falls.
class SinkFile {
  struct Data;
 public:
  [[nodiscard]] static SinkFile create(const resource::MemoryAccount&,std::string_view,
      const Descriptor&,const SinkHeader&,FileLimits={});
  [[nodiscard]] static SinkFile open(const resource::MemoryAccount&,std::string_view,
      const Descriptor&,const SinkHeader&,FileLimits={});
  ~SinkFile();
  SinkFile(const SinkFile&)=delete; SinkFile& operator=(const SinkFile&)=delete;
  SinkFile(SinkFile&&) noexcept; SinkFile& operator=(SinkFile&&)=delete;
  [[nodiscard]] SinkFileState state() const;
  [[nodiscard]] SinkPrefix prefix(std::uint64_t physical_sequence) const;
  [[nodiscard]] SinkReceipt receipt() const;
  [[nodiscard]] bool requires_reopen() const noexcept;
  // True means one newly synced epoch. False means every encoded byte already
  // matches the actual recorded epoch; hash metadata alone never accepts a retry.
  bool append(const Frame&) &;
  void verify(const Frame&) &; // Existing prefix only; permitted through a torn suffix.
  void repair_tail() &; // Same whole-session validation precondition as WalFile.
  void close() &;
 private:
  friend class Session;
  explicit SinkFile(resource::AccountedUnique<Data>) noexcept;
  [[nodiscard]] Data& data() const;
  void validate() &;
  bool accept(const Frame&,bool verify_only);
  resource::AccountedUnique<Data> data_;
};
} // namespace crown::recovery::sql_aggregate
