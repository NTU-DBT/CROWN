#pragma once

#include "crown/io/ingest.hpp"
#include <array>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace crown::session_journal_stream_test {

// data/options own bytes; name borrows a literal; progress expectations are ordinary data.
struct Case {
  const char* name;
  io::InputOptions options;
  std::string data;
  std::array<std::uint64_t,2> bytes;
  std::array<std::optional<std::uint64_t>,2> source_offsets;
};

namespace detail {
inline io::InputEvent event(std::uint64_t sequence,std::int64_t x,std::int64_t y,
    std::string source,std::uint64_t offset) {
  io::InputEvent result;
  result.update={sequence,TableId{0},SetOperation::insert,Row{x,y}};
  result.source_position=io::SourcePosition{std::move(source),offset};
  return result;
}

inline void finish(Case& value) {
  value.options.limits.records=2;
  value.options.limits.total_bytes=static_cast<std::uint64_t>(value.data.size());
}
} // namespace detail

// These fixtures assume exactly one physical table e(x,y), with two int64
// columns in that order. Byte checkpoints are cumulative bytes consumed after
// each data event (CSV includes its header). Wire profiles use their explicit
// source offsets; delimited profiles use the configured byte origin, except
// timestamp_flags, which retains its timestamp verbatim.
inline std::vector<Case> cases(const Catalog& catalog) {
  if(catalog.tables.size()!=1 || catalog.tables[0].name!="e" || catalog.tables[0].columns.size()!=2 ||
      catalog.tables[0].columns[0].name!="x" || catalog.tables[0].columns[1].name!="y" ||
      catalog.tables[0].columns[0].type!=ScalarType::int64 || catalog.tables[0].columns[1].type!=ScalarType::int64)
    throw std::invalid_argument("session journal stream fixtures require e(x,y) with int64 columns");

  std::vector<Case> result;
  result.reserve(8);

  Case jsonl{"jsonl",{}, {},{}, {}};
  jsonl.options.format=io::InputFormat::jsonl;
  const auto json_first=io::write_input_json(detail::event(1,1,2,"jsonl-source",10),catalog,jsonl.options.limits);
  const auto json_second=io::write_input_json(detail::event(2,2,3,"jsonl-source",20),catalog,jsonl.options.limits);
  jsonl.data=json_first+"\n"+json_second+"\n";
  jsonl.bytes={static_cast<std::uint64_t>(json_first.size()+1),
      static_cast<std::uint64_t>(json_first.size()+json_second.size()+2)};
  jsonl.source_offsets={10,20};
  detail::finish(jsonl);result.push_back(std::move(jsonl));

  Case binary{"binary",{}, {},{}, {}};
  binary.options.format=io::InputFormat::binary;
  const auto binary_first=io::write_input_binary(detail::event(1,1,2,"binary-source",30),catalog,binary.options.limits);
  const auto binary_second=io::write_input_binary(detail::event(2,2,3,"binary-source",40),catalog,binary.options.limits);
  binary.data=binary_first+binary_second;
  binary.bytes={static_cast<std::uint64_t>(binary_first.size()),
      static_cast<std::uint64_t>(binary_first.size()+binary_second.size())};
  binary.source_offsets={30,40};
  detail::finish(binary);result.push_back(std::move(binary));

  Case csv{"csv",{}, {},{}, {}};
  csv.options.format=io::InputFormat::csv;csv.options.table=TableId{0};csv.options.delimiter=';';
  csv.options.source="csv-source";csv.options.byte_offset=100;
  csv.data="y;x\n2;1\n3;2\n";
  csv.bytes={8,12};csv.source_offsets={104,108};
  detail::finish(csv);result.push_back(std::move(csv));

  Case signed_rows{"legacy_signed",{}, {},{}, {}};
  signed_rows.options.format=io::InputFormat::legacy_signed;signed_rows.options.table=TableId{0};
  signed_rows.options.source="signed-source";signed_rows.options.byte_offset=200;
  signed_rows.data="+,1,2\n+,2,3\n";
  signed_rows.bytes={6,12};signed_rows.source_offsets={200,206};
  detail::finish(signed_rows);result.push_back(std::move(signed_rows));

  Case relations{"legacy_relations",{}, {},{}, {}};
  relations.options.format=io::InputFormat::legacy_relations;
  relations.options.relation_tokens.emplace("E",TableId{0});
  relations.options.source="relation-source";relations.options.byte_offset=300;
  relations.data="+,E,1,2\n+,E,2,3\n";
  relations.bytes={8,16};relations.source_offsets={300,308};
  detail::finish(relations);result.push_back(std::move(relations));

  Case insert_only{"legacy_insert_only",{}, {},{}, {}};
  insert_only.options.format=io::InputFormat::legacy_insert_only;insert_only.options.table=TableId{0};
  insert_only.options.source="insert-only-source";insert_only.options.byte_offset=400;
  insert_only.data="1,2\n2,3\n";
  insert_only.bytes={4,8};insert_only.source_offsets={400,404};
  detail::finish(insert_only);result.push_back(std::move(insert_only));

  Case flags{"legacy_flags",{}, {},{}, {}};
  flags.options.format=io::InputFormat::legacy_flags;flags.options.table=TableId{0};
  flags.options.source="flags-source";flags.options.byte_offset=500;
  flags.data="1,1,2\n1,2,3\n";
  flags.bytes={6,12};flags.source_offsets={500,506};
  detail::finish(flags);result.push_back(std::move(flags));

  Case timestamp_flags{"legacy_timestamp_flags",{}, {},{}, {}};
  timestamp_flags.options.format=io::InputFormat::legacy_timestamp_flags;timestamp_flags.options.table=TableId{0};
  timestamp_flags.options.source="timestamp-source";
  timestamp_flags.data="10,1,1,2\n20,1,2,3\n";
  timestamp_flags.bytes={9,18};timestamp_flags.source_offsets={10,20};
  detail::finish(timestamp_flags);result.push_back(std::move(timestamp_flags));

  return result;
}

} // namespace crown::session_journal_stream_test
