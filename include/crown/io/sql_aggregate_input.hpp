#pragma once

#include "crown/recovery/sql_aggregate_records.hpp"
#include <istream>

namespace crown::io {
// Transport admissions from the original stream origin. JSON parsing workspace
// is separate; retained line/command storage uses the supplied receiving account.
struct SqlAggregateJsonlLimits {
  std::size_t record_bytes=1024*1024,field_bytes=1024*1024,source_bytes=4096;
  std::size_t replacements=65536,cells=1000000;
  std::uint64_t bytes=1024ULL*1024*1024,records=1000000;
};

// One validated physical command. Flat cell/text/edit buffers own every borrow;
// moving the owner preserves their heap addresses. No native decision is made.
class SqlAggregateJsonCommand {
  struct Data;
 public:
  ~SqlAggregateJsonCommand();
  SqlAggregateJsonCommand(const SqlAggregateJsonCommand&)=delete;
  SqlAggregateJsonCommand& operator=(const SqlAggregateJsonCommand&)=delete;
  SqlAggregateJsonCommand(SqlAggregateJsonCommand&&) noexcept;
  SqlAggregateJsonCommand& operator=(SqlAggregateJsonCommand&&) noexcept;
  [[nodiscard]] recovery::sql_aggregate::InputView view() const &;
  recovery::sql_aggregate::InputView view() const &&=delete;
 private:
  friend class SqlAggregateJsonlReader;
  explicit SqlAggregateJsonCommand(resource::AccountedUnique<Data>) noexcept;
  resource::AccountedUnique<Data> data_;
};

// The stream must already point at origin.bytes. The schema is a genuine frozen
// program; JSON must bind its complete identity and each physical table version.
// next() owns one command, checks W+1, and records the next unread logical byte.
// Failure latches requires_reopen before consuming input, without catch/retry
// wrappers. Reopen from durable logged W/reader progress, not disposed I alone.
class SqlAggregateJsonlReader {
  struct Data;
 public:
  SqlAggregateJsonlReader(std::istream&,const resource::MemoryAccount&,
      const frontend::SqlAggregateProgram&,std::uint64_t logged=0,
      recovery::sql_aggregate::ReaderPosition origin={},SqlAggregateJsonlLimits={});
  ~SqlAggregateJsonlReader();
  SqlAggregateJsonlReader(const SqlAggregateJsonlReader&)=delete;
  SqlAggregateJsonlReader& operator=(const SqlAggregateJsonlReader&)=delete;
  SqlAggregateJsonlReader(SqlAggregateJsonlReader&&) noexcept;
  SqlAggregateJsonlReader& operator=(SqlAggregateJsonlReader&&) noexcept;
  [[nodiscard]] std::optional<SqlAggregateJsonCommand> next();
  [[nodiscard]] recovery::sql_aggregate::ReaderPosition position() const;
  [[nodiscard]] bool requires_reopen() const noexcept;
 private:
  resource::AccountedUnique<Data> data_;
};
} // namespace crown::io
