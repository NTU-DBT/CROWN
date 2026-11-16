#pragma once
// Version-1 journal records and prefix validation. Filesystem durability and
// native query admission are separate from this bounded codec.
#include "crown/recovery/image.hpp"
#include "crown/io/input_view.hpp"

namespace crown::recovery::journal {
using Fault=ImageFault;
class Failure final:public std::exception {
 public:
  explicit Failure(Fault fault) noexcept:fault_(fault) {}
  [[nodiscard]] Fault fault() const noexcept {return fault_;}
  [[nodiscard]] const char* what() const noexcept override {return "journal record rejected";}
 private:
  Fault fault_;
};
enum class Kind:std::uint8_t {header,input,commit,checkpoint};
enum class InputKind:std::uint8_t {stream,physical,window};
enum class CommitKind:std::uint8_t {physical,metadata};
struct Limits {
  ImageLimits record{16*1024*1024,64*1024*1024,0,1,1024,1024*1024};
  std::uint64_t source_bytes=1024;
};
struct Header {
  std::array<char,32> query_id{};
  std::uint64_t generation=1;
  ImageBinding binding;
  std::array<char,64> checkpoint_sha256{};
  std::uint64_t physical_sequence=0,command_sequence=0;
  InputKind input_kind=InputKind::physical;
  bool operator==(const Header&) const=default;
};
struct ReaderAdvanceView {
  std::uint64_t bytes=0,records=0;
  bool header_read=false;
  std::span<const std::uint64_t> csv_fields;
};
struct InputView {
  io::InputItemView item;
  std::optional<ReaderAdvanceView> reader;
};
struct Commit {
  std::uint64_t input_ordinal=0;
  std::array<char,64> input_sha256{};
  CommitKind kind=CommitKind::physical;
  std::uint64_t physical_sequence=0,command_sequence=0,substep=0;
  bool completes_input=true;
  bool operator==(const Commit&) const=default;
};
struct Checkpoint {
  std::uint64_t physical_sequence=0,command_sequence=0;
  std::array<char,64> checkpoint_sha256{};
  bool operator==(const Checkpoint&) const=default;
};
using PayloadView=std::variant<Header,InputView,Commit,Checkpoint>;
struct InputMetadata {
  bool window=false;
  std::uint8_t window_kind=0;
  std::uint64_t sequence=0,table=0,label=0,timestamp=0,watermark=0,fields=0;
  SetOperation operation=SetOperation::insert;
  bool source_present=false;
  std::uint64_t source_size=0,source_offset=0;
  bool reader_present=false,header_read=false;
  std::uint64_t reader_bytes=0,reader_records=0,csv_fields=0;
};
struct Inspected {
  Kind kind=Kind::header;
  std::uint64_t ordinal=0;
  Header header;
  InputMetadata input;
  Commit commit;
  Checkpoint checkpoint;
  std::array<char,64> body_sha256{};
  ImageStatistics statistics;
};
struct Encoded {ImageVector<char> bytes;ImageStatistics statistics;};
struct Decoded {
  // Owns native row/source/CSV payload; returned input views borrow this owner.
  // View construction checks shape; actual query/source admission remains later.
  Inspected info;
  storage::AccountedRow row;
  ImageVector<char> source;
  ImageVector<std::uint64_t> csv_fields;
  [[nodiscard]] std::string_view source_name() const & noexcept {return {source.data(),source.size()};}
  std::string_view source_name() const &&=delete;
  // Borrows this decoded owner's native row/source/CSV storage. Native query
  // admission still validates program/schema/source policy. Retain this owner
  // through consumption; temporary owners cannot produce a dangling view.
  [[nodiscard]] InputView input_view() const &;
  InputView input_view() const &&=delete;
};
// Encode allocates one final buffer after full preflight. Decode retains only
// receiving-account values; inspect allocates nothing. Byte work includes both
// checksum visits, structural passes and CSV-permutation comparisons.
[[nodiscard]] Encoded encode(const resource::MemoryAccount&,std::uint64_t ordinal,const PayloadView&,Limits={});
[[nodiscard]] Inspected inspect(std::string_view,Limits={});
[[nodiscard]] Decoded decode(const resource::MemoryAccount&,std::string_view,Limits={});
struct ScanLimits {
  Limits record;
  std::uint64_t bytes=256*1024*1024,work=512*1024*1024,records=1'000'000;
};
struct PendingView {
  std::uint64_t ordinal=0,next_substep=0;
  InputMetadata input;
  std::array<char,64> input_sha256{};
  std::string_view frame;
};
struct Scanned {
  Header header;
  std::uint64_t records=0,work=0,physical_sequence=0,command_sequence=0;
  std::optional<std::uint64_t> reader_bytes;
  std::size_t consumed=0,last_commit_end=0,last_command_end=0,last_checkpoint_end=0;
  bool torn_tail=false;
  std::optional<PendingView> pending;
};
// Validates a framed prefix without allocation. Pending frame bytes borrow the
// immutable caller input. This is not native program/schema admission or a
// durable-state decision; a complete record with bad checksum always rejects.
[[nodiscard]] Scanned scan(std::string_view,ScanLimits={},const Header* expected=nullptr);
// One validation owns its cumulative limits and continuation state. Scanned
// snapshots are descriptive and cannot mint another work/record allowance.
// Pending frame views still borrow caller bytes. File repair/flush and native
// query admission remain separate from this allocation-free validator.
class Cursor {
  // Failed feed keeps stored state/work; repeated validation still costs CPU.
  // Moves consume this continuation without copying the borrowed frame bytes.
 public:
  explicit Cursor(ScanLimits={},const Header* expected=nullptr);
  Cursor(const Cursor&)=delete;
  Cursor& operator=(const Cursor&)=delete;
  Cursor(Cursor&&) noexcept;
  Cursor& operator=(Cursor&&) noexcept;
  [[nodiscard]] Scanned feed(std::string_view full_frame) &;
  [[nodiscard]] Scanned finish_tail(std::string_view incomplete_tail) &;
  [[nodiscard]] Scanned state() const noexcept {return state_;}
 private:
  ScanLimits limits_;
  std::optional<Header> expected_;
  Scanned state_;
  bool active_=true;
};
inline constexpr std::size_t frame_prefix_size=84,frame_header_size=148;
} // namespace crown::recovery::journal
