#include "crown/io/inspection.hpp"

#include "crown/api/error.hpp"
#include "ingest_text.hpp"
#include <charconv>
#include <limits>
#include <type_traits>

namespace crown::io {
namespace {
using namespace runtime;
struct Writer {
  // The ceiling bounds encoded length; ordinary string capacity may be larger.
  std::string output;
  std::size_t limit;
  void room(std::size_t count) const {
    if (output.size()>limit || count>limit-output.size()) throw Error("resource_limit","runtime diagnostic encoded byte limit exceeded");
  }
  void raw(std::string_view value) { room(value.size()); output.append(value); }
  void number(std::uint64_t value) {
    char buffer[32]; const auto end=std::to_chars(buffer,buffer+sizeof(buffer),value).ptr;
    raw(std::string_view(buffer,static_cast<std::size_t>(end-buffer)));
  }
  void signed_number(std::int64_t value) {
    char buffer[32]; const auto end=std::to_chars(buffer,buffer+sizeof(buffer),value).ptr;
    raw(std::string_view(buffer,static_cast<std::size_t>(end-buffer)));
  }
  void boolean(bool value) { raw(value?"true":"false"); }
  void text(std::string_view value) {
    room(2); if (value.size()>limit-output.size()-2) throw Error("resource_limit","runtime diagnostic string exceeds encoded byte limit");
    ingest_detail::require_utf8(value); raw("\"");
    constexpr char hex[]="0123456789abcdef";
    for (const char character : value) {
      const auto byte=static_cast<unsigned char>(character);
      switch (byte) {
        case '"': raw("\\\""); break;
        case '\\': raw("\\\\"); break;
        case '\b': raw("\\b"); break;
        case '\f': raw("\\f"); break;
        case '\n': raw("\\n"); break;
        case '\r': raw("\\r"); break;
        case '\t': raw("\\t"); break;
        default:
          if (byte<32) { const char encoded[]={'\\','u','0','0',hex[byte>>4],hex[byte&15]}; raw(std::string_view(encoded,6)); }
          else raw(std::string_view(&character,1));
      }
    }
    raw("\"");
  }
  template<class Range,class Function> void array(const Range& values,Function function) {
    raw("["); bool first=true;
    for (const auto& value : values) { if (!first) raw(","); first=false; function(value); }
    raw("]");
  }
  void row(const Row& values) {
    array(values,[&](const auto& value) { std::visit([&](const auto& cell) {
      using T=std::decay_t<decltype(cell)>;
      if constexpr (std::is_same_v<T,std::int64_t>) signed_number(cell);
      else if constexpr (std::is_same_v<T,std::string>) text(cell);
      else if constexpr (std::is_same_v<T,bool>) boolean(cell);
      else if constexpr (std::is_same_v<T,Date>) { raw("{\"date\":"); text(cell.to_string()); raw("}"); }
      else { raw("{\"decimal\":"); text(cell.to_string()); raw("}"); }
    },value); });
  }
  void rows(const Relation& values) { array(values,[&](const auto& value) { row(value); }); }
  void counts(const std::vector<CanonicalCount>& values) {
    array(values,[&](const auto& value) { raw("{\"key\":"); row(value.key); raw(",\"count\":"); number(value.count); raw("}"); });
  }
  void support(const CanonicalSupportState& state) {
    raw("{\"physical_sha256\":"); text(state.physical_sha256); raw(",\"catalog_version\":"); number(state.catalog_version);
    raw(",\"arithmetic\":"); text(state.arithmetic); raw(",\"sequence\":"); number(state.sequence);
    raw(",\"has_answer\":"); boolean(state.has_answer); raw(",\"nodes\":");
    array(state.nodes,[&](const auto& node) {
      raw("{\"node\":"); number(node.node.value); raw(",\"kind\":");
      if (node.kind==NodeKind::native) text("native");
      else if (node.kind==NodeKind::generalized) text("generalized");
      else throw Error("invalid_document","unknown diagnostic node kind");
      raw(",\"records\":"); array(node.records,[&](const auto& record) {
        raw("{\"values\":"); row(record.values); raw(",\"satisfied\":"); number(record.satisfied);
        raw(",\"child_present\":"); array(record.child_present,[&](bool value) { boolean(value); });
        raw(",\"survives\":"); boolean(record.survives); raw("}");
      });
      raw(",\"survivors\":"); rows(node.survivors); raw(",\"parent\":"); counts(node.parent);
      raw(",\"visible\":"); if (node.visible) counts(*node.visible); else raw("null"); raw("}");
    }); raw("}");
  }
  void physical(const CanonicalPhysicalState& state) {
    raw("{\"support\":"); support(state.support); raw(",\"sequence\":"); number(state.sequence);
    raw(",\"sources\":"); array(state.sources,[&](const auto& value) { rows(value); });
    raw(",\"derivations\":"); array(state.derivations,[&](const auto& value) { counts(value); }); raw("}");
  }
  void buckets(const std::vector<CanonicalBucket>& values) {
    array(values,[&](const auto& value) { raw("{\"key\":"); row(value.key); raw(",\"count\":"); number(value.count);
      raw(",\"rows\":"); rows(value.rows); raw("}"); });
  }
  void live(const CanonicalLiveState& state) {
    raw("{\"sequence\":"); number(state.sequence); raw(",\"rows\":"); number(state.rows);
    raw(",\"parent_rows\":"); number(state.parent_rows); raw(",\"child_rows\":"); number(state.child_rows);
    raw(",\"factors\":"); array(state.factors,[&](const auto& factor) {
      raw("{\"node\":"); number(factor.node.value); raw(",\"rows\":"); rows(factor.rows);
      raw(",\"parents\":"); buckets(factor.parents); raw(",\"children\":"); buckets(factor.children); raw("}");
    }); raw("}");
  }
};
std::string_view code(InvariantCode value) {
  switch (value) {
#define CROWN_CASE(name) case InvariantCode::name: return #name
    CROWN_CASE(missing_record); CROWN_CASE(unexpected_record); CROWN_CASE(missing_metadata); CROWN_CASE(orphan_metadata);
    CROWN_CASE(child_presence); CROWN_CASE(satisfied_count); CROWN_CASE(support_count); CROWN_CASE(derivation_count);
    CROWN_CASE(membership); CROWN_CASE(sequence); CROWN_CASE(storage); CROWN_CASE(invalid_source); CROWN_CASE(aggregate_count);
#undef CROWN_CASE
  }
  throw Error("invalid_document","unknown runtime diagnostic issue code");
}
std::string_view component(InvariantComponent value) {
  switch (value) {
#define CROWN_CASE(name) case InvariantComponent::name: return #name
    CROWN_CASE(source); CROWN_CASE(derivation); CROWN_CASE(record); CROWN_CASE(survivor); CROWN_CASE(parent);
    CROWN_CASE(visible); CROWN_CASE(sequence); CROWN_CASE(storage); CROWN_CASE(live_factor);
    CROWN_CASE(live_parent); CROWN_CASE(live_child); CROWN_CASE(live_totals);
#undef CROWN_CASE
  }
  throw Error("invalid_document","unknown runtime diagnostic component");
}
}  // namespace
std::string write_runtime_state(const CanonicalPhysicalState& state,std::size_t limit) {
  Writer out{{},limit}; out.raw("{\"schema_version\":1,\"kind\":\"physical\",\"state\":"); out.physical(state); out.raw("}"); return std::move(out.output);
}
std::string write_runtime_state(const CanonicalDeltaState& state,std::size_t limit) {
  Writer out{{},limit}; out.raw("{\"schema_version\":1,\"kind\":\"delta\",\"state\":{\"physical\":"); out.physical(state.physical);
  out.raw(",\"delta_maintained\":"); out.boolean(state.delta_maintained); out.raw(",\"sql_view\":"); out.boolean(state.sql_view);
  out.raw(",\"live\":"); if (state.live) out.live(*state.live); else out.raw("null"); out.raw("}}"); return std::move(out.output);
}
std::string write_invariant_report(const InvariantReport& report,std::size_t limit) {
  Writer out{{},limit}; out.raw("{\"schema_version\":1,\"kind\":\"inspection\",\"complete\":"); out.boolean(report.complete);
  out.raw(",\"valid\":"); out.boolean(report.valid()); out.raw(",\"work\":"); out.number(report.work);
  out.raw(",\"statistics\":{"); bool first=true;
  const auto stat=[&](std::string_view name,std::uint64_t value) {
    if (!first) out.raw(",");
    first=false; out.text(name); out.raw(":"); out.number(value);
  };
#define CROWN_STAT(name) stat(#name,report.statistics.name)
  CROWN_STAT(source_rows); CROWN_STAT(derivation_keys); CROWN_STAT(native_records); CROWN_STAT(generalized_records);
  CROWN_STAT(survivors); CROWN_STAT(parent_keys); CROWN_STAT(visible_keys); CROWN_STAT(child_flags);
  CROWN_STAT(source_storage_records); CROWN_STAT(support_storage_records); CROWN_STAT(index_memberships);
  CROWN_STAT(live_rows); CROWN_STAT(live_parent_rows); CROWN_STAT(live_child_rows);
  CROWN_STAT(live_parent_buckets); CROWN_STAT(live_child_buckets);
#undef CROWN_STAT
  out.raw("},\"issues\":"); out.array(report.issues,[&](const auto& issue) {
    out.raw("{\"code\":"); out.text(code(issue.code)); out.raw(",\"component\":"); out.text(component(issue.component));
    if (issue.table) { out.raw(",\"table\":"); out.number(issue.table->value); }
    if (issue.occurrence) { out.raw(",\"occurrence\":"); out.number(issue.occurrence->value); }
    if (issue.node) { out.raw(",\"node\":"); out.number(issue.node->value); }
    if (issue.child_slot) { out.raw(",\"child_slot\":"); out.number(*issue.child_slot); }
    out.raw(",\"key\":"); out.row(storage::export_row(issue.key.view()));
    if (issue.expected) { out.raw(",\"expected\":"); out.number(*issue.expected); }
    if (issue.actual) { out.raw(",\"actual\":"); out.number(*issue.actual); }
    out.raw("}");
  }); out.raw("}"); return std::move(out.output);
}
}  // namespace crown::io
