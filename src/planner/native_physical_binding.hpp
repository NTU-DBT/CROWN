#pragma once

#include "crown/ir/program.hpp"
#include "crown/ir/digest.hpp"
#include <charconv>

namespace crown::planner::native_binding_detail {
// Exact nlohmann default object order/UTF-8 spelling for physical v1/v2.
// Dynamic buffer capacity uses the supplied receiving account/owner;
// replan_into may use a different account from the immutable basis.
class Writer {
  using String=std::basic_string<char,std::char_traits<char>,resource::MemoryAllocator<char>>;
 public:
  String output;
  Writer(const resource::MemoryAccount& account,resource::MemoryAttribution owner)
      :output(resource::MemoryAllocator<char>(account,resource::MemoryPurpose::scratch,owner)) {}
  static void require(bool valid) {if(!valid)throw storage::IndexFailure(storage::IndexFault::contract);}
  void raw(std::string_view value) {output.append(value);}
  // JSON compatibility check, not P02 validity: native planner byte strings
  // can be broader than this strict UTF-8 digest/transport boundary.
  static void utf8(std::string_view value) {
    for(std::size_t i=0;i<value.size();) {
      const auto first=static_cast<unsigned char>(value[i++]);if(first<0x80)continue;
      unsigned continuation=0;std::uint32_t code=0,minimum=0;
      if(first>=0xc2 && first<=0xdf){continuation=1;code=first&0x1fU;minimum=0x80;}
      else if(first>=0xe0 && first<=0xef){continuation=2;code=first&0x0fU;minimum=0x800;}
      else if(first>=0xf0 && first<=0xf4){continuation=3;code=first&0x07U;minimum=0x10000;}
      else require(false);
      require(continuation<=value.size()-i);
      while(continuation--) {const auto next=static_cast<unsigned char>(value[i++]);require((next&0xc0U)==0x80U);code=(code<<6U)|(next&0x3fU);}
      require(code>=minimum && code<=0x10ffff && (code<0xd800 || code>0xdfff));
    }
  }
  // Validate before writing a quote. Later allocation failure may leave
  // a private prefix; the caller publishes only a completed digest.
  void text(std::string_view value) {
    utf8(value);raw("\"");constexpr std::string_view hex="0123456789abcdef";
    for(const auto c:value) {
      const auto byte=static_cast<unsigned char>(c);
      switch(byte) {
        case '"':raw("\\\"");break;case '\\':raw("\\\\");break;
        case '\b':raw("\\b");break;case '\f':raw("\\f");break;case '\n':raw("\\n");break;
        case '\r':raw("\\r");break;case '\t':raw("\\t");break;
        default:if(byte<32){const char escaped[]={'\\','u','0','0',hex[byte>>4U],hex[byte&15U]};raw({escaped,6});}
          else raw({&c,1});
      }
    }
    raw("\"");
  }
  void number(std::uint64_t value) {
    std::array<char,32> bytes{};const auto encoded=std::to_chars(bytes.data(),bytes.data()+bytes.size(),value);
    require(encoded.ec==std::errc{});raw({bytes.data(),static_cast<std::size_t>(encoded.ptr-bytes.data())});
  }
  void limit(const std::optional<std::uint64_t>& value) {if(value)number(*value);else raw("null");}
  template<class Range,class Function> void array(const Range& values,Function emit) {
    raw("[");bool first=true;for(const auto& value:values){if(!first)raw(",");first=false;emit(value);}raw("]");
  }
};

// Keep default JSON object key order/spelling exactly. The legacy v1
// digest omits explicit options; indexed v2 includes this whole object.
inline void options(Writer& out,const program::PhysicalOptions& options) {
  out.raw("{");
  if(options.indexed_storage) {
    const auto& spec=*options.indexed_storage;const auto& cap=spec.per_table;const auto& work=spec.per_operation;
    out.raw("\"indexed_storage\":{\"algorithm\":\"indexed_chained_v1\",\"component_scope\":\"per_table_including_undo\",\"limits\":{\"arena_pins\":");out.number(cap.arena_pins);
    out.raw(",\"arena_slots\":");out.number(cap.arena_slots);out.raw(",\"directory_slots\":");out.number(cap.directory_slots);
    out.raw(",\"indices\":");out.number(cap.indices);out.raw(",\"journal_entries\":");out.number(cap.journal_entries);
    out.raw(",\"keys\":");out.number(cap.keys);out.raw(",\"memberships\":");out.number(cap.memberships);
    out.raw(",\"nodes\":");out.number(cap.nodes);out.raw(",\"rows\":");out.number(cap.rows);
    out.raw("},\"traversal\":\"insertion_first_live_key_v1\",\"work\":{\"link_actions\":");out.number(work.link_actions);
    out.raw(",\"pointer_slots\":");out.number(work.pointer_slots);out.raw(",\"scalar_bytes\":");out.number(work.scalar_bytes);
    out.raw(",\"scalar_fields\":");out.number(work.scalar_fields);out.raw(",\"structural_steps\":");out.number(work.structural_steps);
    out.raw("},\"work_scope\":\"operation_aggregate\"},");
  }
  out.raw("\"limits\":{\"identity_work\":");out.limit(options.limits.identity.work_limit);
  out.raw(",\"work\":");out.limit(options.limits.work_limit);out.raw("},\"policy\":{\"arithmetic\":");out.text(options.policy.arithmetic);
  out.raw(",\"cost_model\":");out.text(options.policy.cost_model);out.raw(",\"optimization\":");out.text(options.policy.optimization);
  out.raw(",\"planner\":");out.text(options.policy.planner);out.raw("},\"schema_version\":");out.number(options.indexed_storage?2:1);out.raw("}");
}
// Caller supplies a P02-checked candidate. These range/kind checks are
// not a second full tree validator; exact display IDs/claims stay bound.
inline void tree(Writer& out,const program::FreeConnexTree& tree,const program::Catalog& catalog,const program::Query& query) {
  const auto node=[&](NodeId id){Writer::require(id.value<tree.nodes.size());out.text(tree.nodes[id.value].id);};
  const auto scope=[&](const auto& values){out.array(values,[&](VariableId id){Writer::require(id.value<query.variables.size());out.text(query.variables[id.value].name);});};
  out.raw("{\"catalog_version\":");out.number(catalog.version);
  if(tree.claimed_connex){out.raw(",\"connex\":");out.array(*tree.claimed_connex,node);}
  if(tree.claimed_native_height){out.raw(",\"native_height\":");out.number(*tree.claimed_native_height);}
  out.raw(",\"nodes\":");out.array(tree.nodes,[&](const auto& value){
    out.raw("{\"children\":");out.array(value.children,node);out.raw(",\"id\":");out.text(value.id);
    out.raw(",\"kind\":");Writer::require(value.kind==NodeKind::native || value.kind==NodeKind::generalized);
    out.text(value.kind==NodeKind::native?"native":"generalized");
    if(value.kind==NodeKind::native){Writer::require(value.occurrence && *value.occurrence<query.atoms.size());out.raw(",\"occurrence\":");out.text(query.atoms[*value.occurrence].occurrence);}
    else Writer::require(!value.occurrence);
    out.raw(",\"scope\":");scope(value.scope);if(value.claimed_separator){out.raw(",\"separator\":");scope(*value.claimed_separator);}out.raw("}");
  });
  out.raw(",\"root\":");if(tree.root)node(*tree.root);else out.raw("null");out.raw(",\"schema_version\":1,\"semantics\":\"set\"}");
}
// Build full accounted bytes, then hash; this is not streaming/constant
// space. Exact source admission belongs to NativeLowering before this call.
inline std::array<char,64> digest(const CompiledProgram& basis,const program::FreeConnexTree& candidate,
    resource::MemoryAttribution owner,const resource::MemoryAccount& account) {
  Writer out(account,owner);const auto& identity=basis.identity();const auto indexed=bool(basis.options().indexed_storage);
  out.raw("{\"domain\":\"crown-physical-plan\",\"lowerer\":");out.text(indexed?"crown-lower-v2":"crown-lower-v1");
  out.raw(",\"occurrence_order\":");out.array(identity.occurrence_order,[&](std::size_t i){out.number(i);});
  if(indexed){out.raw(",\"options\":");options(out,basis.options());}
  out.raw(",\"plan_cache_sha256\":");out.text(identity.plan_cache_sha256);
  out.raw(",\"source_sha256\":");out.text(basis.physical_source_sha256());
  out.raw(",\"tree\":");tree(out,candidate,basis.catalog(),basis.query());
  out.raw(",\"variable_order\":");out.array(identity.variable_order,[&](std::size_t i){out.number(i);});
  out.raw(",\"version\":");out.number(indexed?2:1);out.raw("}");return sha256_fixed(out.output);
}
} // namespace crown::planner::native_binding_detail
