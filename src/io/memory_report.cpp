#include "crown/io/memory_report.hpp"
#include "crown/api/error.hpp"

namespace crown::io {
namespace {
namespace mm=runtime::memory;
template<class Enum,std::size_t N> const char* name(Enum value,const std::array<const char*,N>& names) {
  const auto i=static_cast<std::size_t>(value);if(i>=N)throw Error("memory_report_encoding","unknown native memory enum");return names[i];
}
const char* layer(mm::Layer v){return name(v,std::array{"support","physical","delta","session"});}
Json usage(resource::MemoryUsage value){return {{"allocations",value.allocations},{"requested_bytes",value.requested_bytes},{"payload_bytes",value.payload_bytes}};}
Json attribution(resource::MemoryAttribution value) {
  static constexpr std::array names{"query","physical_source","support_node","delta_node","storage_table","session","cursor","immutable_metadata","observation","capture","output","recovery","tuple_arena"};
  static_assert(names.size()==static_cast<std::size_t>(resource::MemoryOwnerKind::count));
  return {{"kind",name(value.kind,names)},{"id",value.id}};
}
template<class Statistics> void categories(Json& out,const Statistics& value) {
  static constexpr std::array purposes{"control","table_state","arena_slot","tuple_values","scalar_payload","primary_node","secondary_node","directory","support_metadata","source_counts","delta_state","journal_undo","cursor","observation","capture","immutable_metadata","output_buffer","recovery_log","scratch"};
  static constexpr std::array lifetimes{"active","retained","free_pool"};
  static_assert(purposes.size()==resource::memory_purpose_count && lifetimes.size()==resource::allocation_lifetime_count);
  out["by_purpose"]=Json::object();out["by_lifetime"]=Json::object();
  for(std::size_t i=0;i<purposes.size();++i)out["by_purpose"][purposes[i]]=usage(value.by_purpose[i]);
  for(std::size_t i=0;i<lifetimes.size();++i)out["by_lifetime"][lifetimes[i]]=usage(value.by_lifetime[i]);
}
Json owner(const resource::AttributedMemoryStatistics& value) {
  Json out{{"account",value.account_owner},{"attribution",attribution(value.attribution)},{"current",usage(value.current)}};categories(out,value);return out;
}
Json account(const resource::MemoryStatistics& value) {
  Json out{{"owner",value.owner},{"limit_bytes",value.limit_bytes},{"current",usage(value.current)},
      {"peak_requested_bytes",value.peak_requested_bytes},{"successful_allocations",value.successful_allocations},{"freed_allocations",value.freed_allocations}};
  categories(out,value);return out;
}
Json arena(const storage::ArenaMemoryStatistics& value) {
  const auto& r=value.records;
  return {{"records",{{"slots",r.slots},{"live_records",r.live_records},{"retained_records",r.retained_records},{"pins",r.pins},{"free_slots",r.free_slots},{"exhausted_slots",r.exhausted_slots}}},
      {"owner",owner(value.owner)},{"state_control",usage(value.state_control)},{"directory",usage(value.directory)},
      {"live_slots",usage(value.live_slots)},{"retained_slots",usage(value.retained_slots)},{"free_slots",usage(value.free_slots)},
      {"exhausted_slots",usage(value.exhausted_slots)},{"live_values",usage(value.live_values)},{"retained_values",usage(value.retained_values)},
      {"directory_capacity",value.directory_capacity},{"directory_spare_payload_bytes",value.directory_spare_payload_bytes}};
}
template<class Id> Json optional_id(const std::optional<Id>& value){return value?Json(value->value):Json(nullptr);}
Json table(const mm::Table& value) {
  Json out{{"scope",value.scope==mm::TableScope::support?"support":"physical_source"},{"relation",value.relation.value},
      {"role",name(value.role,std::array{"physical_base","native_records","generalized_candidates","survivors","parent_support","visible"})},
      {"node",optional_id(value.node)},{"base",optional_id(value.base)},{"storage_owner",value.storage_owner.value},
      {"backend",value.backend==storage::StorageBackend::reference_ordered_v1?"reference_ordered_v1":"indexed_chained_v1"},{"live_records",value.live_records}};
  std::visit([&](const auto& memory) {
    out["table_owner"]=owner(memory.table);out["arena"]=arena(memory.arena);out["owned"]=usage(memory.owned);
    if constexpr(requires{memory.live_records;}) {
      out["index_records"]={{"indices",memory.indices},{"keys",memory.secondary_keys},{"live_keys",memory.secondary_keys},{"memberships",memory.memberships},
          {"active_undo_entries",memory.active_undo_entries},{"retained_undo_entries",memory.retained_undo_entries}};
    }else {
      const auto& r=memory.records;
      out["index_records"]={{"indices",r.indices},{"keys",r.keys},{"live_keys",r.live_keys},{"memberships",r.memberships},{"nodes",r.nodes},
          {"directory_slots",r.directory_slots},{"retained_rows",r.retained_rows},{"retained_memberships",r.retained_memberships},
          {"journal_entries",r.journal_entries},{"retained_history_entries",memory.retained_history_entries}};
      out["directories"]=usage(memory.directories);
    }
  },value.memory);return out;
}
Json operation(const mm::Operator& value) {
  return std::visit([](const auto& item) {
    using T=std::remove_cvref_t<decltype(item)>;Json out{{"attribution",attribution(item.attribution)}};
    if constexpr(std::is_same_v<T,mm::SupportNode>) {
      out.update({{"kind","support_node"},{"node",item.node.value},{"records",item.records},{"survivors",item.survivors},{"parent_keys",item.parent_keys},
          {"visible_keys",item.visible_keys?Json(*item.visible_keys):Json(nullptr)},{"child_flags",item.child_flags}});
    }else if constexpr(std::is_same_v<T,mm::Derivations>)out.update({{"kind","derivations"},{"occurrence",item.occurrence.value},{"keys",item.keys}});
    else if constexpr(std::is_same_v<T,mm::DeltaFactor>) {
      out.update({{"kind","delta_factor"},{"node",item.node.value}});out["materialized"]=nullptr;
      if(item.materialized){const auto& c=*item.materialized;out["materialized"]={{"rows",c.rows},{"parent_keys",c.parent_keys},{"parent_rows",c.parent_rows},{"child_keys",c.child_keys},{"child_rows",c.child_rows}};}
    }else out.update({{"kind","coordinator"},{"layer",layer(item.layer)}});
    return out;
  },value);
}
}
Json write_memory_report(const runtime::memory::Report& report) {
  // Export the retained sample into an ordinary DOM; this does not rescan the live account.
  const auto& s=report.snapshot();const auto& u=report.usage();
  Json out{{"format","crown-query-memory"},{"version",runtime::memory::Report::format_version},
      {"allocation_scope","whole_query_account_including_held_generations_and_report_storage"},{"operator_scope","recorded_committed_runtime_only"},
      {"byte_units","requested_upstream_bytes_with_component_headers_and_alignment; payload_bytes_are_requested_payload"},
      {"snapshot",{{"layer",layer(s.layer)},{"availability",name(s.availability,std::array{"committed","pending","released"})},
        {"runtime_owner",s.runtime_owner},{"sequence",s.sequence},{"physical_sha256",std::string(s.physical_sha256.data(),s.physical_sha256.size())},{"account",account(s.account)}}},
      {"usage",{{"work",u.work},{"owners",u.owners},{"tables",u.tables},{"operators",u.operators}}},
      {"owners",Json::array()},{"tables",Json::array()},{"operators",Json::array()}};
  for(const auto& row:report.owners())out["owners"].push_back(owner(row));
  for(const auto& row:report.tables())out["tables"].push_back(table(row));
  for(const auto& row:report.operators())out["operators"].push_back(operation(row));
  return out;
}
} // namespace crown::io
