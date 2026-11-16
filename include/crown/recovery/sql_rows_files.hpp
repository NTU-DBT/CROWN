#pragma once

#include "crown/recovery/sql_rows_descriptor.hpp"
#include "crown/recovery/sql_aggregate_files.hpp"
#include "crown/resource/ownership.hpp"

namespace crown::recovery::sql_rows {
// The existing R2 byte/file limits and fixed transport observations are shared.
// They describe regular files only; row-program admission and replay stay typed.
using sql_aggregate::FileStage;
using sql_aggregate::FileFault;
using sql_aggregate::FileOutcome;
using sql_aggregate::FileFailure;
using sql_aggregate::FileLimits;
using sql_aggregate::FileStatistics;
using sql_aggregate::WalFileState;

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

// Prefixes describe actual synced bytes; only the typed owner mints receipts.
using sql_aggregate::SinkPrefix;
using sql_aggregate::SinkFileState;
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
} // namespace crown::recovery::sql_rows
