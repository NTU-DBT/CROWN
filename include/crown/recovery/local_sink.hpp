#pragma once
#include "crown/recovery/image.hpp"
#include "crown/storage/tuple_values.hpp"
#include <sys/stat.h>

namespace crown::recovery::sink {
struct Header {
  std::array<char,32> query_id{},sink_id{};
  ImageBinding binding;
  std::uint64_t first_generation=1,base_sequence=0,fields=0;
  std::array<char,64> schema_sha256{};
  bool operator==(const Header&) const=default;
};
struct RowView {SetOperation operation=SetOperation::insert;storage::TupleValuesView values;};
struct Row {SetOperation operation=SetOperation::insert;storage::AccountedRow values;};
struct Epoch {std::uint64_t generation=0,sequence=0;ImageVector<Row> rows;};
struct Limits {
  ImageLimits record{64*1024*1024,512*1024*1024,0,65536,1024,1024*1024};
  std::uint64_t bytes=1024*1024*1024,work=4ULL*1024*1024*1024,epochs=1'000'000,operations=1'000'000;
  std::size_t path_bytes=4095,chunk_bytes=1024*1024;
};
enum class Stage :std::uint8_t {path,open_directory,entropy,create_temporary,open_file,stat_file,lock_file,read_data,write_data,sync_file,link_file,unlink_temporary,sync_directory,truncate_tail,close_file,close_directory,state};
enum class Fault :std::uint8_t {io,limit,path,not_regular,busy,changed,truncated,state};
enum class Outcome :std::uint8_t {unchanged,unknown,durable};
enum class HeaderMatch :std::uint8_t {exact,identity};
class Failure final:public std::exception {
 public:
  Failure(Fault fault,Stage stage,Outcome outcome,int error=0,bool cleanup=false) noexcept:fault_(fault),stage_(stage),outcome_(outcome),error_(error),cleanup_(cleanup) {}
  [[nodiscard]] Fault fault() const noexcept{return fault_;}
  [[nodiscard]] Stage stage() const noexcept{return stage_;}
  [[nodiscard]] Outcome outcome() const noexcept{return outcome_;}
  [[nodiscard]] int native_error() const noexcept{return error_;}
  [[nodiscard]] bool temporary_cleanup_failed() const noexcept{return cleanup_;}
  [[nodiscard]] const char* what() const noexcept override{return "local sink file operation failed";}
 private:Fault fault_;Stage stage_;Outcome outcome_;int error_;bool cleanup_;
};
struct State {
  Header header;
  std::uint64_t epochs=0,generation=0,sequence=0,bytes=0,work=0,operations=0,buffer_bytes=0;
  bool torn_tail=false,recovery_required=false;
};
struct Prefix {
  std::uint64_t generation=0,sequence=0,bytes=0;
  std::array<char,64> content_sha256{};
  bool operator==(const Prefix&) const=default;
};
class File;
// Authority for this bound local sink's complete durable prefix. Descriptive
// State/frontiers cannot construct one. Namespace/files must remain trusted.
class Receipt {
  // This fixed capability retains no descriptor, lock, account or row payload.
  // Retirement still verifies actual checkpoint/prefix lineage and trusted files.
 public:
  Receipt(const Receipt& other) noexcept:header_(other.header_),prefix_(other.prefix_) {}
  Receipt& operator=(const Receipt&)=delete;
  [[nodiscard]] Header header() const noexcept{return header_;}
  [[nodiscard]] std::uint64_t generation() const noexcept{return prefix_.generation;}
  [[nodiscard]] std::uint64_t sequence() const noexcept{return prefix_.sequence;}
  [[nodiscard]] std::uint64_t bytes() const noexcept{return prefix_.bytes;}
  [[nodiscard]] std::array<char,64> content_sha256() const noexcept{return prefix_.content_sha256;}
 private:
  friend class File;
  Receipt(const Header& header,const Prefix& prefix) noexcept:header_(header),prefix_(prefix) {}
  const Header header_;const Prefix prefix_;
};
// Each complete epoch is canonicalized by sign and exact typed wire bytes;
// ordinals, layout addresses and producer iteration order are excluded.
class File {
  // Whole-epoch encoding/sorting/byte comparison are explicit funded work.
  // State can report poison; mutation/receipt require a healthy actual owner.
 public:
  [[nodiscard]] static File create(const resource::MemoryAccount&,std::string_view,const Header&,std::span<const ScalarType>,Limits={});
  [[nodiscard]] static File open(const resource::MemoryAccount&,std::string_view,const Header&,std::span<const ScalarType>,Limits={},HeaderMatch=HeaderMatch::exact);
  ~File();File(const File&)=delete;File& operator=(const File&)=delete;
  File(File&&) noexcept;File& operator=(File&&)=delete;
  [[nodiscard]] State state() const;
  [[nodiscard]] Receipt receipt() const;
  // Descriptive fingerprint of an actual admitted complete prefix. A report
  // cannot construct a receipt or authorize native history retirement.
  [[nodiscard]] Prefix prefix(std::uint64_t sequence) const;
  // Returns false only for an exact already-durable epoch. Retry never relies
  // on an ordinal or checksum alone; a changed epoch rejects before mutation.
  [[nodiscard]] bool append(std::uint64_t generation,std::uint64_t sequence,std::span<const RowView>);
  // Compare an existing complete epoch without writing. Available through a
  // valid incomplete tail, so recovery can validate before deciding to repair.
  void verify_epoch(std::uint64_t generation,std::uint64_t sequence,std::span<const RowView>);
  [[nodiscard]] Epoch read_epoch(std::uint64_t sequence);
  void repair_tail();void close();
 private:
  struct Index {std::uint64_t generation=0,offset=0,size=0;std::array<char,64> content_sha256{};};
  File(const resource::MemoryAccount&,const Header&,std::span<const ScalarType>,Limits);
  void ready() const;void consume(std::uint64_t);void refresh();void unchanged_file();
  [[nodiscard]] ImageLimits record_limits() const;
  [[nodiscard]] bool accept_epoch(std::uint64_t,std::uint64_t,std::span<const RowView>,bool verify_only);
  std::int64_t call(Stage,std::size_t=0,int=-1,const char* =nullptr,int=-1,const char* =nullptr,void* =nullptr,std::uint64_t=0,struct stat* =nullptr,bool emergency_cleanup=false);
  std::int64_t checked(Stage,std::size_t=0,int=-1,const char* =nullptr,int=-1,const char* =nullptr,void* =nullptr,std::uint64_t=0,struct stat* =nullptr);
  void transfer(bool,char*,std::size_t,std::uint64_t);bool cleanup_temporary(int,const char*) noexcept;
  resource::MemoryAccount account_;Header header_;Limits limits_;
  ImageVector<ScalarType> schema_;ImageVector<Index> index_;ImageVector<char> scratch_,other_;
  int fd_=-1;struct stat stamp_{};
  std::uint64_t operations_=0,work_=0,bytes_=0;
  std::uint64_t header_bytes_=0;
  std::array<char,64> header_sha256_{};
  Outcome outcome_=Outcome::unchanged;bool poisoned_=false,torn_=false;
};
[[nodiscard]] std::array<char,64> schema_sha256(const resource::MemoryAccount&,std::span<const ScalarType>);
inline constexpr std::size_t frame_prefix_size=84,frame_header_size=148;
} // namespace crown::recovery::sink
