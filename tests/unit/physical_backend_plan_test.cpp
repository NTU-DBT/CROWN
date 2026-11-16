#include "crown/io/physical.hpp"
#include "crown/io/tree.hpp"
#include "crown/ir/digest.hpp"
#include "crown/frontend/bind.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/storage/plan.hpp"
#include "crown/storage/physical.hpp"

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <stdexcept>

using namespace crown;
namespace {
void check(bool value,const char* message) { if (!value) throw std::runtime_error(message); }
template<class F> void error(F&& operation) {
  try { operation(); } catch (const Error&) { return; }
  throw std::runtime_error("expected backend/physical rejection");
}
std::string read(const std::filesystem::path& path) {
  std::ifstream input(path);check(bool(input),"fixture unavailable");
  return {std::istreambuf_iterator<char>(input),std::istreambuf_iterator<char>()};
}
PhysicalOptions indexed_options() {
  PhysicalOptions options;storage::IndexedBackendSpec spec;
  spec.per_table={64,64,4096,8192,16384,65536,256,1024,128};
  spec.per_operation={1'000'000'000,1'000'000'000,1'000'000'000,1'000'000'000,1'000'000'000};
  options.indexed_storage=spec;return options;
}
Value sample(ScalarType type,std::size_t variation) {
  switch (type) {
    case ScalarType::int64:return std::int64_t{9'007'199'254'740'992LL+static_cast<std::int64_t>(variation)};
    case ScalarType::string:{ auto text=std::string(128,static_cast<char>('a'+variation));text.push_back(char{0});return text; }
    case ScalarType::boolean:return variation%2==0;
    case ScalarType::date:return Date::parse(variation%2==0 ? "0001-01-01" : "9999-12-31");
    case ScalarType::decimal:return Decimal::parse("0");
  }
  throw std::runtime_error("unsupported sample type");
}
void reference_binding(const PhysicalPlan& plan) {
  const auto& identity=plan.identity();
  const io::Json expected{{"domain","crown-physical-plan"},{"version",1},{"lowerer","crown-lower-v1"},
      {"source_sha256",sha256(io::write_physical_source(plan.catalog(),plan.query(),plan.normalized()).dump())},
      {"plan_cache_sha256",identity.plan_cache_sha256},{"occurrence_order",identity.occurrence_order},
      {"variable_order",identity.variable_order},{"tree",io::write_tree(plan.tree(),plan.catalog(),plan.query())}};
  check(plan.physical_sha256()==sha256(expected.dump()),"reference v1 physical binding changed");
  const auto value=io::write_physical(plan);check(value.at("schema_version")==1 &&
      value.at("lowerer")=="crown-lower-v1" && !value.at("options").contains("indexed_storage"),
      "reference artifact emitted new-format fields");
}
void accounted_binding(const PhysicalPlan& plan) {
  using namespace storage;
  auto account=resource::MemoryAccount::create(1U<<26);
  const IndexWork cap=plan.options().indexed_storage ? plan.options().indexed_storage->per_operation :
      IndexWork{1'000'000'000,1'000'000'000,1'000'000'000,1'000'000'000,1'000'000'000};
  IndexWorkAllowance work(cap,true),oracle_work(cap);
  AccountedPlanStorage stored(account,plan,&work);PlanStorage oracle(plan,&oracle_work);
  check(stored.physical_identity()==plan.physical_sha256() && stored.route()==plan.route() &&
      stored.backend()==oracle.backend() && stored.relation_count()==plan.relations().size() &&
      stored.index_count()==plan.indexes().size() && stored.layouts().size()==plan.layouts().size(),
      "accounted storage binding changed the actual compiled plan");
  std::vector<std::vector<TupleHandle>> handles(plan.relations().size());
  for(const auto& relation:plan.relations()) {
    auto& table=stored.table(relation.id);auto& expected=oracle.table(relation.id);
    check(table.layout().same_token(stored.layout(relation.layout.id())) &&
        stored.relation(relation.id).role==relation.role && stored.relation(relation.id).node==relation.node &&
        stored.relation(relation.id).base==relation.base &&
        std::equal(table.layout().fields().begin(),table.layout().fields().end(),relation.layout.fields().begin(),relation.layout.fields().end()),
        "accounted compiled relation lost layout fields,aliases or role binding");
    for(std::size_t variation=0;variation<3;++variation) {
      Row row;for(const auto& field:relation.layout.fields())row.push_back(sample(field.type,variation));
      const auto actual=table.insert(table.layout().tuple(row),&work);
      const auto original=expected.insert(relation.layout.tuple(row),&oracle_work);
      check(actual.inserted==original.inserted && actual.handle.tuple==original.handle.tuple,
          "accounted compiled relation differs from independent legacy values/IDs");
      if(actual.inserted)handles[relation.id.value].push_back(actual.handle);
    }
    auto cursor=table.live(&work);auto reference=expected.live(&oracle_work);
    while(const auto entry=cursor.next_entry(&work)) {
      const auto other=reference.next_entry(&oracle_work);check(other.has_value(),"accounted relation has extra rows");
      const auto comparison=table.layout().tuple(other->tuple.values());
      check(entry->handle.tuple==other->handle.tuple && entry->tuple.values()==comparison.values(),
          "accounted native cursor changed exact scalar values/order");
    }
    check(!reference.next(&oracle_work),"accounted relation lost a row");
  }
  for(const auto& requirement:plan.indexes()) {
    auto& table=stored.table(requirement.relation);auto& expected=oracle.table(requirement.relation);
    const auto id=stored.index(requirement.id),reference_id=oracle.index(requirement.id);
    const auto& projection=stored.projection(requirement.id);
    check(table.projection(id,&work).same_token(projection) &&
        projection.source().same_token(stored.layout(requirement.projection.source().id())) &&
        projection.target().same_token(stored.layout(requirement.projection.target().id())),
        "accounted compiled index lost its frozen source/target/program token");
    const auto keys=table.keys(id,&work);const auto original=expected.keys(reference_id,&oracle_work);
    check(keys.size()==original.size(),"accounted compiled index changed key cardinality");
    for(std::size_t i=0;i<keys.size();++i) {
      const auto comparison=projection.target().tuple(original[i].values());
      check(keys[i].values()==comparison.values(),"accounted compiled index changed exact key values/order");
      const auto members=table.bucket(id,keys[i],&work);const auto reference=expected.bucket(reference_id,original[i],&oracle_work);
      check(members.size()==reference.size(),"accounted compiled bucket changed degree");
      for(std::size_t j=0;j<members.size();++j)check(members[j].tuple==reference[j].tuple,"accounted compiled bucket changed member IDs/order");
    }
  }
  stored.check_invariants(&work);
  for(const auto& relation:plan.relations())if(handles[relation.id.value].size()>1)
    check(stored.table(relation.id).erase(handles[relation.id.value][0],&work),"accounted plan sparse setup failed");
  IndexWorkAllowance copy_work(cap,true);auto copy=stored.snapshot_copy(&copy_work);copy.check_invariants(&copy_work);
  for(const auto& relation:plan.relations()) {
    const auto& original=stored.table(relation.id);const auto& duplicate=copy.table(relation.id);
    check(original.owner()!=duplicate.owner() && duplicate.layout().same_token(original.layout()),
        "accounted plan copy reused owner or lost frozen token");
    auto cursor=original.live(&work);
    while(const auto entry=cursor.next_entry(&work)) {
      const auto found=duplicate.find(entry->tuple,&copy_work);
      check(found && found->tuple==entry->handle.tuple,"accounted plan copy renumbered sparse IDs");
    }
  }
  check(copy.memory_statistics().shared_metadata.attribution==stored.memory_statistics().shared_metadata.attribution,
      "accounted plan copy duplicated the immutable metadata owner");
}
void populate_and_copy(const PhysicalPlan& plan) {
  auto work=storage::IndexWorkAllowance(plan.options().indexed_storage->per_operation);
  storage::PlanStorage stored(plan,&work);check(stored.backend()==storage::StorageBackend::indexed_chained_v1,
      "new plan storage silently selected reference");
  error([&] { storage::ReferencePlanStorage wrong(plan); });
  error([&] { storage::PlanStorage missing(plan); });
  std::vector<std::vector<TupleHandle>> handles(plan.relations().size());
  for (const auto& relation : plan.relations()) {
    auto& table=stored.table(relation.id);check(table.backend()==stored.backend() && table.layout().same_token(relation.layout),
        "relation backend/layout differs from compiled plan");
    std::set<Row> expected;
    for (std::size_t variation=0;variation<3;++variation) {
      Row values;for (const auto& field : relation.layout.fields()) values.push_back(sample(field.type,variation));
      const bool fresh=expected.insert(values).second;const auto result=table.insert(relation.layout.tuple(std::move(values)),&work);
      check(result.inserted==fresh,"actual table failed typed set insertion");if (fresh) handles[relation.id.value].push_back(result.handle);
    }
    std::set<Row> actual;for (const auto& tuple : table.snapshot(&work)) actual.insert(crown::storage::export_row(tuple.values()));
    check(actual==expected,"actual relation rows differ from input set");
  }
  for (const auto& requirement : plan.indexes()) {
    auto& table=stored.table(requirement.relation);const auto index=stored.index(requirement.id);
    check(table.projection(index,&work).same_token(requirement.projection),"index is not the compiled projection");
    std::map<Row,std::vector<TupleId>> expected;
    auto rows=table.live(&work);
    while (const auto entry=rows.next_entry(&work)) {
      Row key;for (auto field : requirement.projection.fields()) key.push_back(crown::storage::export_row(entry->tuple.values())[field.value]);
      expected[std::move(key)].push_back(entry->handle.tuple);
    }
    check(table.key_count(index,&work)==expected.size(),"compiled index lost a distinct key");
    for (const auto& [key,ids] : expected) {
      const auto probe=requirement.projection.target().tuple(key);std::vector<TupleId> actual;
      auto bucket=table.bucket_cursor(index,probe,&work);while (const auto entry=bucket.next_entry(&work)) actual.push_back(entry->handle.tuple);
      check(actual==ids,"compiled index changed member identity/order");
    }
  }
  stored.check_invariants(&work);
  // Create sparse identities before copying, including reused arena metadata.
  for (const auto& relation : plan.relations()) if (handles[relation.id.value].size()>1)
    check(stored.table(relation.id).erase(handles[relation.id.value][0],&work),"sparse copy setup failed");
  auto copy_work=storage::IndexWorkAllowance(plan.options().indexed_storage->per_operation);
  auto copy=stored.snapshot_copy(&copy_work);copy.check_invariants(&copy_work);stored.check_invariants(&work);
  for (const auto& relation : plan.relations()) {
    auto& original=stored.table(relation.id);auto& duplicate=copy.table(relation.id);
    check(original.owner()!=duplicate.owner() && original.snapshot(&work)==duplicate.snapshot(&copy_work),
        "plan copy lost fresh owners or live row order");
    auto cursor=original.live(&work);
    while (const auto entry=cursor.next_entry(&work)) {
      const auto handle=duplicate.find(entry->tuple,&copy_work);
      check(handle && handle->tuple==entry->handle.tuple,"plan copy renumbered a sparse live row");
      error([&] { static_cast<void>(duplicate.get(entry->handle,&copy_work)); });
    }
  }
  error([&] { static_cast<void>(stored.table(RelationId{plan.relations().size()})); });
  error([&] { static_cast<void>(stored.index(IndexRequirementId{plan.indexes().size()})); });
}
void binding_edges(const Catalog& catalog,const Query& query,const FreeConnexTree& tree) {
  const auto options=indexed_options();const auto plan=planner::lower_tree(catalog,query,tree,options);const auto encoded=io::write_physical(plan);
  const std::array<std::size_t storage::IndexedLimits::*,9> components{&storage::IndexedLimits::rows,&storage::IndexedLimits::indices,
      &storage::IndexedLimits::keys,&storage::IndexedLimits::memberships,&storage::IndexedLimits::nodes,&storage::IndexedLimits::directory_slots,
      &storage::IndexedLimits::arena_slots,&storage::IndexedLimits::arena_pins,&storage::IndexedLimits::journal_entries};
  const std::array<std::uint64_t storage::IndexWork::*,5> domains{&storage::IndexWork::structural_steps,&storage::IndexWork::scalar_fields,
      &storage::IndexWork::scalar_bytes,&storage::IndexWork::pointer_slots,&storage::IndexWork::link_actions};
  for (auto member : components) {
    auto changed=options;++(changed.indexed_storage->per_table.*member);
    const auto revised=planner::lower_tree(catalog,query,tree,changed);check(revised.physical_sha256()!=plan.physical_sha256(),"component limit omitted from physical binding");
    auto corrupt=encoded;corrupt["options"]=io::write_physical_options(changed);error([&] { static_cast<void>(io::read_physical(corrupt.dump())); });
  }
  for (auto member : domains) {
    auto changed=options;++(changed.indexed_storage->per_operation.*member);
    const auto revised=planner::lower_tree(catalog,query,tree,changed);check(revised.physical_sha256()!=plan.physical_sha256(),"work domain omitted from physical binding");
    auto corrupt=encoded;corrupt["options"]=io::write_physical_options(changed);error([&] { static_cast<void>(io::read_physical(corrupt.dump())); });
  }
  for (const auto key : {"algorithm","traversal","component_scope","work_scope"}) {
    auto corrupt=encoded;corrupt["options"]["indexed_storage"][key]="unsupported";
    error([&] { static_cast<void>(io::read_physical(corrupt.dump())); });
  }
  auto wrong=encoded;wrong["guarantee"]["storage_backend"]="reference_ordered_v1";error([&] { static_cast<void>(io::read_physical(wrong.dump())); });
  wrong=encoded;wrong["schema_version"]=1;wrong["lowerer"]="crown-lower-v1";error([&] { static_cast<void>(io::read_physical(wrong.dump())); });
  io::PhysicalReadLimits host;host.lowering.work_limit=0;error([&] { static_cast<void>(io::read_physical(encoded.dump(),host)); });
  auto excess=options.indexed_storage->per_operation;++excess.structural_steps;auto too_large=storage::IndexWorkAllowance(excess);
  error([&] { storage::PlanStorage bad(plan,&too_large); });
  auto zero=storage::IndexWorkAllowance(storage::IndexWork{});error([&] { storage::PlanStorage bad(plan,&zero); });
  if (!plan.indexes().empty()) {
    auto insufficient=options;insufficient.indexed_storage->per_table.indices=0;
    const auto limited=planner::lower_tree(catalog,query,tree,insufficient);auto work=storage::IndexWorkAllowance(insufficient.indexed_storage->per_operation);
    error([&] { storage::PlanStorage bad(limited,&work); });
  }
}
void normalized_backend() {
  const Catalog catalog{23,{{"r",{{"x",ScalarType::int64},{"y",ScalarType::int64},{"flag",ScalarType::boolean}}}}};
  const auto bound=frontend::bind_sql("SELECT DISTINCT l.x,l.y,q.y AS z,l.x AS again "
      "FROM r l JOIN r q ON l.y=q.x WHERE l.flag IS TRUE",catalog);
  check(std::holds_alternative<frontend::BoundSql>(bound),"normalized backend fixture did not bind");
  auto normalized=frontend::normalize_sql(std::get<frontend::BoundSql>(bound));
  check(std::holds_alternative<frontend::NormalizedSql>(normalized),"normalized backend fixture did not normalize");
  const auto& program=std::get<frontend::NormalizedSql>(normalized);
  const FreeConnexTree tree{NodeId{0},{{"join-key",NodeKind::generalized,{VariableId{1}},{NodeId{1},NodeId{2}},{},{}},
      {"left",NodeKind::native,{VariableId{0},VariableId{1}},{},0,{}},
      {"right",NodeKind::native,{VariableId{1},VariableId{2}},{},1,{}}},{},{}};
  const auto reference=planner::lower_normalized(program,tree);reference_binding(reference);
  accounted_binding(reference);
  const auto indexed=planner::lower_normalized(program,tree,indexed_options());
  check(indexed.normalized() && indexed.normalized()->schema_version==2 && indexed.source_catalog().version==23 &&
      indexed.source_catalog().tables.size()==1 && indexed.query().atoms.size()==2,
      "indexed normalized plan lost physical source or aliases");
  check(indexed.identity().plan_cache_sha256==reference.identity().plan_cache_sha256 &&
      indexed.physical_sha256()!=reference.physical_sha256(),"normalized backend semantic/physical identity boundary changed");
  const auto encoded=io::write_physical(indexed);
  check(encoded.at("source").at("kind")=="normalized_sql" && encoded.at("schema_version")==2,
      "normalized indexed artifact has the wrong source/version");
  const auto replay=io::read_physical(encoded.dump());
  check(io::write_physical(replay).dump()==encoded.dump(),"normalized indexed artifact does not replay exactly");
  const auto accepted=replay.adapt_input(OccurrenceId{0},Row{std::int64_t{7},std::int64_t{9},true});
  check(accepted && accepted->values()==Row{std::int64_t{7},std::int64_t{9}} &&
      !replay.adapt_input(OccurrenceId{0},Row{std::int64_t{7},std::int64_t{9},false}),
      "indexed normalized source lost its occurrence-local filter or column projection");
  std::vector<storage::Tuple> assignments;
  for (const auto& step : replay.enumeration().steps) {
    const auto& layout=replay.relations().at(step.relation.value).layout;Row values;
    for (const auto& field : layout.fields()) {
      check(field.variable.has_value() && field.variable->value<3,"normalized assignment has an unexpected slot");
      values.emplace_back(std::in_place_type<std::int64_t>,field.variable->value==0 ? 7 : field.variable->value==1 ? 9 : 11);
    }
    assignments.push_back(layout.tuple(std::move(values)));
  }
  check(replay.assemble_result(assignments).values()==Row{std::int64_t{7},std::int64_t{9},std::int64_t{11},std::int64_t{7}},
      "indexed normalized result lost output order or its repeated head slot");
  populate_and_copy(replay);
  accounted_binding(replay);
}
}  // namespace
int main(int argc,char** argv) {
  check(argc==2,"expected source root");const std::filesystem::path root=argv[1];
  const auto manifest=io::Json::parse(read(root/"tests/structural/lowering/manifest.json"));std::size_t cases=0;bool edges=false;
  for (const auto& item : manifest.at("cases")) {
    if (!item.at("expected").at("valid").get<bool>()) continue;
    const auto document=io::read_document(read(root/item.at("query").get<std::string>()));
    const auto tree=io::read_tree(read(root/item.at("tree").get<std::string>()),document.catalog,document.query);
    const auto original=planner::lower_tree(document.catalog,document.query,tree);reference_binding(original);
    accounted_binding(original);
    const auto options=indexed_options();const auto plan=planner::lower_tree(document.catalog,document.query,tree,options);
    check(plan.guarantee().storage_backend=="indexed_chained_v1" && plan.physical_sha256()!=original.physical_sha256() &&
        plan.identity().plan_cache_sha256==original.identity().plan_cache_sha256,"backend binding changed semantic identity or omitted physical identity");
    for (const auto& layout : plan.layouts()) check(layout.context()==storage::LayoutContext{plan.catalog().version,plan.physical_sha256()},"layout token context omitted backend binding");
    const auto encoded=io::write_physical(plan);check(encoded.at("schema_version")==2 && encoded.at("lowerer")=="crown-lower-v2","indexed artifact mislabeled as reference v1");
    const auto replayed=io::read_physical(encoded.dump());check(io::write_physical(replayed).dump()==encoded.dump(),"complete indexed artifact did not replay exactly");
    populate_and_copy(plan);if (!edges && !plan.indexes().empty()) { binding_edges(document.catalog,document.query,tree);edges=true; }++cases;
    accounted_binding(replayed);
  }
  check(cases>=10 && edges,"fixture coverage unexpectedly narrowed");
  normalized_backend();
  std::cout << "S05 accounted actual compiled plans: reference/indexed layouts,exact scalar rows,index tokens,buckets and sparse copies passed\n";
  std::cout << "Backend-aware physical plan: " << cases << " valid fixture shapes, exact v1 binding, full v2 replay,14 bound limits, actual indexed relation/index storage and sparse copy passed\n";
}
