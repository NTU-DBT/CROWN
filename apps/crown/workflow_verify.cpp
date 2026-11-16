#include "workflow_verify.hpp"
#include "crown/api/error.hpp"
#include "crown/io/document.hpp"
#include "crown/runtime/session.hpp"
#include "evaluator.hpp"
#include <algorithm>
#include <fstream>
#include <iterator>
#include <set>
#include <sstream>

namespace {
using namespace crown;
struct Budget {
  std::uint64_t remaining,consumed=0;
  void charge(std::uint64_t amount) {
    if(amount>remaining)throw Error("resource_limit","reference verification work limit exceeded");
    remaining-=amount;consumed+=amount;
  }
};
std::uint64_t product(std::uint64_t a,std::uint64_t b,std::uint64_t limit) {
  if(a && b>limit/a)throw Error("resource_limit","reference verification estimate exceeds its limit");
  return a*b;
}
std::uint64_t row_bytes(const Row& row) {
  std::uint64_t bytes=128+row.size()*sizeof(Value);
  for(const auto& value:row)if(const auto* text=std::get_if<std::string>(&value))bytes+=text->size()+1;
  return bytes;
}
Relation oracle(const PhysicalPlan& plan,const Database& physical,Budget& work,std::uint64_t bytes_limit) {
  const auto& normalized=*plan.normalized();Database logical;logical.tables.resize(normalized.core_catalog.tables.size());
  std::uint64_t stored=0,largest=64;
  for(const auto& table:physical.tables)for(const auto& row:table) {
    const auto bytes=row_bytes(row);if(bytes>bytes_limit-stored)throw Error("resource_limit","reference source state exceeds byte estimate");stored+=bytes;
    for(const auto& value:row)if(const auto* text=std::get_if<std::string>(&value))largest=std::max(largest,static_cast<std::uint64_t>(text->size()));
  }
  for(const auto& output:normalized.outputs)if(const auto* constant=std::get_if<frontend::ConstantOutput>(&output.value))
    if(const auto* text=std::get_if<std::string>(&constant->value))largest=std::max(largest,static_cast<std::uint64_t>(text->size()));
  if(!normalized.core.contradiction)for(const auto& adapter:normalized.adapters) {
    const auto table=normalized.core.atoms.at(adapter.occurrence.value).table;
    for(const auto& source:physical.tables.at(adapter.base.value)) {
      work.charge(1+source.size());auto row=frontend::adapt_row(normalized,adapter.occurrence,source);if(!row)continue;
      const auto bytes=row_bytes(*row);if(bytes>bytes_limit-stored)throw Error("resource_limit","reference adapter state exceeds byte estimate");stored+=bytes;
      logical.tables.at(table.value).insert(std::move(*row));
    }
  }
  std::uint64_t prefix=1,peak=1;
  if(!normalized.core.contradiction)for(const auto& atom:normalized.core.atoms) {
    prefix=product(prefix,logical.tables.at(atom.table.value).size(),work.remaining);
    const auto width=1+normalized.core.variables.size()+atom.terms.size();
    work.charge(product(prefix,width,work.remaining));peak=std::max(peak,prefix);
  }
  const auto fields=1+normalized.core.variables.size()+normalized.outputs.size();
  const auto per_assignment=product(fields,sizeof(Value)+largest+128,bytes_limit);
  const auto transient=product(product(peak,per_assignment,bytes_limit),4,bytes_limit);
  if(transient>bytes_limit-stored)throw Error("resource_limit","reference assignment/output state exceeds byte estimate");
  // Relational joins/projection are independent; SQL adapters/mapping are shared.
  // Native support, cursors and delta production do not compute this result.
  return frontend::map_sql_result(normalized,reference::evaluate(normalized.core_catalog,normalized.core,logical));
}
Relation snapshot(runtime::QuerySession& owner) {
  Relation rows;const auto state=owner.snapshot();
  for(const auto& row:state.rows)if(!rows.insert(storage::export_row(row.values())).second)throw Error("trace_mismatch","native current result contains a duplicate");
  return rows;
}
using Signed=std::set<std::pair<SetOperation,Row>>;
Signed difference(const Relation& before,const Relation& after) {
  Signed result;
  for(const auto& row:after)if(!before.contains(row))result.emplace(SetOperation::insert,row);
  for(const auto& row:before)if(!after.contains(row))result.emplace(SetOperation::erase,row);
  return result;
}
}
std::string crown::cli::verify_workflow_trace(const PhysicalPlan& plan,const std::string& path,
    io::InputOptions input_options,std::optional<std::uint64_t> memory,std::uint64_t work_limit,
    std::uint64_t bytes_limit,std::uint64_t event_limit,std::size_t output_limit) {
  if(!plan.normalized())throw Error("unsupported_verifier","verify-trace requires a compiled SQL workflow");
  constexpr std::size_t input_limit=8U*1024U*1024U;
  std::ifstream file(path,std::ios::binary);if(!file)throw Error("io_error","cannot open verification input");
  std::string text;char block[8192];
  while(file) {
    file.read(block,sizeof(block));const auto count=static_cast<std::size_t>(file.gcount());
    if(count>input_limit-text.size())throw Error("resource_limit","verify-trace input exceeds8MiB");
    text.append(block,count);
  }
  if(file.bad())throw Error("io_error","cannot read verification input");
  runtime::SessionOptions options;options.input=input_options;
  if(memory)options.delta.physical.support.memory_limit_bytes=*memory;
  auto owner=runtime::QuerySession::create(plan,std::make_unique<std::istringstream>(text),options);
  std::istringstream definition_input(text);io::EventReader reader(definition_input,plan.source_catalog(),input_options);
  Database physical;physical.tables.resize(plan.source_catalog().tables.size());Budget work{work_limit};
  auto previous=oracle(plan,physical,work,bytes_limit);
  if(snapshot(*owner)!=previous)throw Error("trace_mismatch","initial native state differs from relational recomputation");
  owner->start();std::uint64_t records=0;
  while(const auto* event=reader.peek()) {
    if(records==event_limit)throw Error("resource_limit","verify-trace exceeds --verify-events");
    auto& table=physical.tables.at(event->update.table.value);
    auto row=storage::export_row(event->update.values);
    if(event->update.operation==SetOperation::insert)table.insert(std::move(row));
    else table.erase(row);
    auto expected=oracle(plan,physical,work,bytes_limit);const auto delta=difference(previous,expected);
    if(owner->begin_next_result()!=runtime::SessionBegin::pending)throw Error("trace_mismatch","native input ended before the reference stream");
    while(owner->step()!=runtime::DeltaStep::prepared){}owner->commit();Signed actual;
    while(auto row=owner->next_output())if(!actual.emplace(row->operation,storage::export_row(row->tuple.values())).second)
      throw Error("trace_mismatch","native delta contains a duplicate signed row");
    // Reference acceptance follows the completed native epoch and raw output collection.
    reader.acknowledge();++records;
    const auto accepted=reader.progress().export_value();const auto progress=owner->progress();
    if(actual!=delta || snapshot(*owner)!=expected || progress.sequence!=accepted.sequence ||
        progress.source_positions!=accepted.source_positions)
      throw Error("trace_mismatch","native state, raw signed delta or accepted source position differs from relational recomputation");
    previous=std::move(expected);
  }
  if(owner->begin_next_result()!=runtime::SessionBegin::end)throw Error("trace_mismatch","native stream has additional input");
  const io::Json result{{"schema_version",1},{"trace_verified",true},{"records",records},
    {"source_positions",owner->progress().source_positions},{"physical_sha256",plan.physical_sha256()},
    {"verifier","relational_reference_with_validated_sql_adapters"},{"reference_estimated_work",work.consumed},
    {"reference_estimated_bytes_limit",bytes_limit},{"input_bytes",text.size()}};
  auto encoded=result.dump();if(encoded.size()>output_limit)throw Error("output_limit","verification report exceeds --max-bytes");
  return encoded;
}
