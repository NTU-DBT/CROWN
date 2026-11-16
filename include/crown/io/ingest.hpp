#pragma once

#include "crown/ir/model.hpp"
#include "crown/io/catalog_source.hpp"
#include "crown/io/input_progress.hpp"
#include "crown/io/input_view.hpp"
#include <istream>
#include <map>
#include <memory>
#include <span>
#include <string_view>

namespace crown {class CompiledProgram;}
namespace crown::runtime {class QuerySession;}
namespace crown::io {
class AccountedInputOptions;
struct ReaderCheckpoint;
struct SourceStateLimits;
struct SourcePosition {
  std::string source;
  std::uint64_t offset;
  bool operator==(const SourcePosition&) const = default;
};
struct InputEvent {
  PhysicalSetUpdate update;
  std::optional<SourcePosition> source_position;
};
struct InputProgress {
  std::uint64_t sequence=0;
  std::map<std::string,std::uint64_t> source_positions;
  bool operator==(const InputProgress&) const = default;
};
struct InputLimits {
  // JSON object bytes (LF/CRLF framing excluded), complete binary frame, or
  // complete raw delimited record including its terminator/quoted syntax.
  std::size_t record_bytes=1024*1024;
  // Accepted string/text length. The JSON lexer can temporarily materialize
  // a token up to record_bytes before this narrower acceptance check.
  std::size_t field_bytes=1024*1024;
  std::size_t columns=4096;
  std::size_t source_bytes=1024;
  std::size_t sources=1024;
  std::optional<std::uint64_t> total_bytes=std::nullopt;
  std::optional<std::uint64_t> records=1000000;
  bool operator==(const InputLimits&) const=default;
};
enum class InputFormat { jsonl, binary, csv, legacy_signed, legacy_relations, legacy_insert_only, legacy_flags, legacy_timestamp_flags };
struct InputOptions {
  InputFormat format=InputFormat::jsonl;
  InputLimits limits;
  // CSV and single-relation legacy profiles need an explicit physical table.
  std::optional<TableId> table;
  char delimiter=',';  // A single ASCII separator, excluding quote/CR/LF/NUL.
  bool header=true;  // CSV: all source column names, in any permutation.
  SetOperation csv_operation=SetOperation::insert;
  // legacy_relations: exact input token -> physical table, never an alias.
  std::map<std::string,TableId> relation_tokens;
  // Optional explicit upstream null spelling: reject it, since NULL values
  // have no representation in the current nonnull engine. Never infer one.
  std::optional<std::string> null_token;
  // CSV/legacy profiles can attach the starting byte offset of each record.
  // legacy_timestamp_flags requires this ID and retains its timestamp prefix
  // as the source offset instead of discarding it or treating it as row data.
  std::optional<std::string> source;
  std::uint64_t byte_offset=0;
  // Non-default options for unrelated formats are rejected. Legacy profiles
  // are always headerless; the default header flag applies only to CSV.
};

// Full canonical catalog binding, including source schema versions/policies.
[[nodiscard]] std::string input_catalog_sha256(const Catalog& catalog);
[[nodiscard]] std::string input_catalog_sha256(const program::Catalog& catalog);
// Typed queues share full-row/domain/source validation without serialization.
// Source owners enforce continuity and cumulative byte/record/source-count caps.
void validate_input_event(const InputEvent& event,const Catalog& catalog,InputLimits limits={});
void validate_input_event(const InputEvent& event,const program::Catalog& catalog,InputLimits limits={});
[[nodiscard]] InputEvent read_input_json(std::string_view text,const Catalog& catalog,InputLimits limits={});
[[nodiscard]] InputEvent read_input_json(std::string_view text,const program::Catalog& catalog,InputLimits limits={});
[[nodiscard]] std::string write_input_json(const InputEvent& event,const Catalog& catalog,InputLimits limits={});
[[nodiscard]] std::string write_input_json(const InputEvent& event,const program::Catalog& catalog,InputLimits limits={});
// One independently framed version-1 record. Concatenation forms a stream.
[[nodiscard]] InputEvent read_input_binary(std::string_view bytes,const Catalog& catalog,InputLimits limits={});
[[nodiscard]] InputEvent read_input_binary(std::string_view bytes,const program::Catalog& catalog,InputLimits limits={});
[[nodiscard]] std::string write_input_binary(const InputEvent& event,const Catalog& catalog,InputLimits limits={});
[[nodiscard]] std::string write_input_binary(const InputEvent& event,const program::Catalog& catalog,InputLimits limits={});

// Decoder continuation after the most recently decoded record, including a
// cached unacknowledged record. CSV fields borrow the reader until its next
// operation/move/destruction. This view performs no allocation or acceptance.
struct ReaderPositionView {
  std::uint64_t bytes=0,records=0;
  bool header_read=false;
  std::span<const std::size_t> csv_fields;
};
// Borrows the input stream; retains the supplied catalog owner, one bounded decoded record and
// bounded source progress. Keep the stream alive through this reader.
// peek errors are sticky. Engine rejection can retry the same decoded event.
class EventReader {
 public:
  EventReader(std::istream& input,CatalogSource catalog,InputOptions options={},InputProgress progress={});
  // Execution derives both catalog authority and its finite original grant.
  EventReader(std::istream& input,const CompiledProgram&,InputOptions options={},InputProgress progress={});
  [[nodiscard]] static EventReader with_options(std::istream&,const CompiledProgram&,
      const AccountedInputOptions&,InputProgress progress={});
  // The supplied continuation starts at the next unread byte. Counters and
  // CSV header/permutation state retain their original source origin.
  [[nodiscard]] static EventReader restore_state(std::istream&,const CompiledProgram&,const ReaderCheckpoint&);
  [[nodiscard]] static EventReader restore_state(std::istream&,const CompiledProgram&,const ReaderCheckpoint&,const SourceStateLimits&);
  static void validate_checkpoint_options(const CompiledProgram&,const AccountedInputOptions&,const AccountedInputProgress&);
  [[nodiscard]] ReaderCheckpoint checkpoint_state() const;
  [[nodiscard]] ReaderCheckpoint checkpoint_state(const SourceStateLimits&) const;
  ~EventReader();
  EventReader(const EventReader&)=delete;
  EventReader& operator=(const EventReader&)=delete;
  EventReader(EventReader&&) noexcept;
  EventReader& operator=(EventReader&&) noexcept;
  [[nodiscard]] const InputEventView* peek();
  // Only explicit acceptance advances sequence/positions. Valid acknowledgement
  // links a prepared map node or changes a scalar and never allocates/throws.
  // With no peeked record this is an idempotent no-op, not implicit skipping.
  void acknowledge() noexcept;
  // Moves accepted progress out and releases the cached event/decoder without
  // accepting pending input. Closed peeks/accessors reject; acknowledge stays
  // a no-op, failed is false, and repeated close returns empty progress.
  // Does not own or destroy the borrowed stream.
  [[nodiscard]] AccountedInputProgress close() noexcept;
  [[nodiscard]] bool failed() const noexcept;
  [[nodiscard]] const AccountedInputProgress& progress() const;
  [[nodiscard]] const CatalogSource& catalog() const;
  [[nodiscard]] std::string_view catalog_sha256() const;
  [[nodiscard]] const resource::MemoryAccount& account() const;
  [[nodiscard]] const AccountedInputOptions& native_options() const &;
  const AccountedInputOptions& native_options() const &&=delete;
  [[nodiscard]] bool matches_catalog(const CompiledProgram&) const;
  [[nodiscard]] std::uint64_t bytes_read() const;
  // Fully decoded records, including a peeked record not yet acknowledged.
  [[nodiscard]] std::uint64_t records_read() const;
  [[nodiscard]] ReaderPositionView decoder_position() const &;
  ReaderPositionView decoder_position() const &&=delete;
 private:
  friend class runtime::QuerySession;
  [[nodiscard]] std::uint64_t stage_replay(const InputEventView&,ReaderPositionView,const SourceStateLimits&);
  struct Data;
  EventReader(const resource::MemoryAccount&,std::istream&,CatalogSource,InputOptions,InputProgress,bool admitted);
  EventReader(const resource::MemoryAccount&,std::istream&,CatalogSource,const AccountedInputOptions&,InputProgress,bool admitted);
  EventReader(const resource::MemoryAccount&,std::istream&,CatalogSource,const ReaderCheckpoint&,const SourceStateLimits&,bool admitted);
  static void validate_options(const CatalogSource&,const AccountedInputOptions&,const AccountedInputProgress&);
  resource::AccountedUnique<Data> data_;
};
}  // namespace crown::io
