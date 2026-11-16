#include "crown/api/error.hpp"
#include "crown/frontend/adapter.hpp"
#include "crown/io/binding.hpp"
#include "crown/io/identity.hpp"
#include "crown/io/normalization.hpp"
#include "crown/ir/digest.hpp"
#include "evaluator.hpp"

#include <functional>
#include <iostream>
#include <stdexcept>

namespace {
using namespace crown;
using namespace crown::frontend;
using io::Json;
Value n(std::int64_t value) { return value; }
Value text(std::string value) { return value; }
void check(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); }
void error(const std::function<void()>& work,std::string_view code) {
  try { work(); } catch (const Error& failure) { check(failure.code()==code,"unexpected error: "+failure.code()+"; expected "+std::string(code)); return; }
  throw std::runtime_error("expected error: "+std::string(code));
}
Catalog catalog() { return {3,{{"r",{{"a",ScalarType::int64},{"b",ScalarType::int64},{"tag",ScalarType::string}}},
    {"s",{{"a",ScalarType::int64},{"c",ScalarType::int64}}},{"zero",{}}}}; }
NormalizedSql program(std::string_view sql,const BindOptions& types={},const NormalizeOptions& values={}) {
  auto bound=bind_sql(sql,catalog(),types);
  if (const auto* failure=std::get_if<BindingDiagnostic>(&bound)) throw std::runtime_error(failure->diagnostic.code);
  auto result=normalize_sql(std::get<BoundSql>(bound),values);
  if (const auto* failure=std::get_if<BindingDiagnostic>(&result)) throw std::runtime_error(failure->diagnostic.code);
  return std::get<NormalizedSql>(std::move(result));
}
Relation snapshot(const AdapterState& state) {
  return map_sql_result(state.query(),reference::evaluate(state.query().core_catalog,state.query().core,state.logical()));
}
void digest_vectors() {
  check(sha256("")=="e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855","SHA-256 empty vector");
  check(sha256("abc")=="ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad","SHA-256 abc vector");
  check(sha256("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq")=="248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1","SHA-256 two-block padding vector");
  check(sha256(std::string(1000000,'a'))=="cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0","SHA-256 million-a vector");
}
void program_roundtrip_and_rejection() {
  const auto original=program("SELECT DISTINCT l.a,q.c,l.a AS again,7 AS fixed FROM r l JOIN s q ON l.a=q.a WHERE l.b>0");
  const auto encoded=io::write_sql_normalization(original);
  const auto restored=io::read_sql_normalization(encoded.dump());
  check(io::write_sql_normalization(restored).dump()==encoded.dump(),"full normalized round trip is byte-deterministic");
  const auto binding=io::write_sql_binding(original.binding);
  check(io::write_sql_binding(io::read_sql_binding(binding.dump())).dump()==binding.dump(),"binding round trip retains all typed/source fields");
  Database data{{Relation{{n(1),n(2),text("x")},{n(1),n(3),text("y")}},Relation{{n(1),n(10)}},Relation{}}};
  AdapterState before(original,data),after(restored,data);
  check(snapshot(before)==Relation{{n(1),n(10),n(1),n(7)}} && snapshot(before)==snapshot(after),"round trip preserves independently expected SQL rows");
  const std::vector<PhysicalSetUpdate> updates{{1,TableId{0},SetOperation::erase,{n(1),n(2),text("x")}},
      {2,TableId{0},SetOperation::erase,{n(1),n(3),text("y")}}};
  for (const auto& update : updates) {
    static_cast<void>(before.apply(update)); static_cast<void>(after.apply(update));
    check(snapshot(before)==snapshot(after) && before.supports()==after.supports(),"round trip preserves support-counted deletion semantics");
  }
  check(snapshot(after).empty(),"last support disappears after round trip");
  const auto reject=[&](const std::function<void(Json&)>& change) {
    auto tampered=encoded; change(tampered);
    error([&] { static_cast<void>(io::read_sql_normalization(tampered.dump())); },"invalid_document");
  };
  reject([](Json& x) { x["unknown_mandatory"]=true; });
  reject([](Json& x) { x["core"]["query"]["atoms"][0]["terms"][0]["var"]="missing"; });
  reject([](Json& x) { x["adapters"][0]["program"][0]=999999; });
  reject([](Json& x) { x["adapters"][0]["predicates"]=Json::array(); });
  reject([](Json& x) { x["adapters"][0]["future_field"]=1; });
  reject([](Json& x) { x["base_routes"][0]=Json::array(); });
  reject([](Json& x) { x["outputs"][0]["column"]=1.0; });
  reject([](Json& x) { x["binding"]["expressions"][0]["occurrence"]=999999; });
  reject([](Json& x) { x["binding"]["source"]="SELECT DISTINCT a FROM r"; });
  reject([](Json& x) { x["work"]=x["work"].get<double>(); });
  auto wrong_version=encoded; wrong_version["schema_version"]=999;
  error([&] { static_cast<void>(io::read_sql_normalization(wrong_version.dump())); },"unsupported_version");
  io::ProgramReadLimits no_binding; no_binding.binding.work_limit=0;
  error([&] { static_cast<void>(io::read_sql_normalization(encoded.dump(),no_binding)); },"resource_limit");
  io::ProgramReadLimits no_normalization; no_normalization.normalization.work_limit=0;
  error([&] { static_cast<void>(io::read_sql_normalization(encoded.dump(),no_normalization)); },"resource_limit");
  error([&] { static_cast<void>(io::read_sql_normalization("{\"schema_version\":1,\"schema_version\":1}")); },"invalid_document");

  BindOptions types; types.parameters={{"p",ScalarType::int64,true}}; NormalizeOptions values; values.parameters={std::nullopt};
  const auto exists=program("SELECT EXISTS(SELECT NULL FROM r WHERE a=$1) AS \"雪\"",types,values);
  const auto exists_copy=io::read_sql_normalization(io::write_sql_normalization(exists).dump());
  AdapterState wrapped(exists_copy,data);
  check(snapshot(wrapped)==Relation{{Value{false}}},"NULL parameter, ignored inner target and Unicode EXISTS label survive round trip");
  const auto false_result=io::write_sql_normalization(BindingDiagnostic{"normalization",{"unsupported_semantics","bag",{},{},{},{}}});
  error([&] { static_cast<void>(io::read_sql_normalization(false_result.dump())); },"invalid_document");
}
void version_migration() {
  Document old;
  old.catalog={1,{{"r",{{"a",ScalarType::int64},{"tag",ScalarType::string}}}}};
  old.query={{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0},IgnoredColumn{}}}},{{VariableId{0},"x"}},false};
  old.initial.tables={Relation{{n(1),text("a")},{n(1),text("b")}}};
  old.updates={{1,TableId{0},SetOperation::erase,{n(1),text("a")}}, {2,TableId{0},SetOperation::insert,{n(2),text("c")}}};
  const auto bytes=io::write_document(old).dump();
  for (const auto version : {1U,2U,3U}) {
    const auto upgraded=io::read_document(io::write_document(io::upgrade_document(old,version)).dump());
    check(upgraded.schema_version==version,"explicit CQ target version retained");
    reference::Session baseline(old.catalog,old.query,old.initial),migrated(upgraded.catalog,upgraded.query,upgraded.initial);
    check(baseline.snapshot()==migrated.snapshot(),"CQ migration preserves initial projection supports");
    for (const auto& update : old.updates) check(baseline.apply(update).current==migrated.apply(update).current,"CQ migration preserves every physical event");
  }
  check(io::write_document(old).dump()==bytes,"migration does not mutate source or change default writer behavior");
  const auto latest=io::upgrade_document(old,3);
  error([&] { static_cast<void>(io::upgrade_document(latest,2)); },"unsupported_version");
  error([&] { static_cast<void>(io::upgrade_document(old,4)); },"unsupported_version");
}
void direct_identities() {
  const Catalog source{3,{{"r",{{"a",ScalarType::int64},{"b",ScalarType::int64}}}, {"s",{{"a",ScalarType::int64},{"b",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64},{"z",ScalarType::int64}},
      {{"left",TableId{0},{VariableId{0},VariableId{1}}},{"right",TableId{1},{VariableId{1},VariableId{2}}}},
      {{VariableId{0},"a"},{VariableId{2},"b"},{VariableId{0},"again"}},false};
  const Query reordered{{{"last",ScalarType::int64},{"first",ScalarType::int64},{"middle",ScalarType::int64}},
      {{"second_alias",TableId{1},{VariableId{2},VariableId{0}}},{"first_alias",TableId{0},{VariableId{1},VariableId{2}}}},
      {{VariableId{1},"a"},{VariableId{0},"b"},{VariableId{1},"again"}},false};
  const auto identity=io::query_identity(source,query),renamed=io::query_identity(source,reordered);
  check(identity.canonical==renamed.canonical && identity.semantic_sha256==renamed.semantic_sha256 && identity.plan_cache_sha256==renamed.plan_cache_sha256,
      "CQ atom reordering and variable/alias alpha-renaming canonicalize equally");
  check(renamed.occurrence_order==std::vector<std::size_t>{1,0} && renamed.variable_order==std::vector<std::size_t>{1,2,0},"canonical IDs retain explicit inverse maps");
  auto output=query; output.head[0].alias="renamed"; const auto labels=io::query_identity(source,output);
  check(labels.semantic_sha256==identity.semantic_sha256 && labels.output_contract_sha256!=identity.output_contract_sha256 && labels.plan_cache_sha256!=identity.plan_cache_sha256,"output label changes result contract/cache but not relational identity");
  std::swap(output.head[0],output.head[1]); check(io::query_identity(source,output).semantic_sha256!=identity.semantic_sha256,"ordered output changes semantic identity");
  auto stats=source; stats.tables[0].statistics.row_count=99; const auto cost=io::query_identity(stats,query);
  check(cost.semantic_sha256==identity.semantic_sha256 && cost.cost_inputs_sha256!=identity.cost_inputs_sha256 && cost.plan_cache_sha256!=identity.plan_cache_sha256,"statistics invalidate cost decisions without changing semantics");
  auto schema=source; schema.tables[0].source_schema_version=2;
  check(io::query_identity(schema,query).semantic_sha256!=identity.semantic_sha256,"source schema versions invalidate semantics");
  auto policy=io::CachePolicy{}; policy.planner="crown-tree-v2";
  check(io::query_identity(source,query,policy).plan_cache_sha256!=identity.plan_cache_sha256,"planner version invalidates cache");
  policy.arithmetic="float"; error([&] { static_cast<void>(io::query_identity(source,query,policy)); },"invalid_policy");
  io::IdentityLimits zero; zero.work_limit=0;
  error([&] { static_cast<void>(io::query_identity(source,query,{},zero)); },"resource_limit");
  auto extra=query; extra.atoms.push_back({"contained_mutable",TableId{1},{VariableId{0},IgnoredColumn{}}});
  check(io::query_identity(source,extra).semantic_sha256!=identity.semantic_sha256,"contained mutable atoms never disappear from identity");
  auto false_query=query; false_query.contradiction=true;
  check(io::query_identity(source,false_query).semantic_sha256!=identity.semantic_sha256,"constant contradiction participates in identity");
  check(io::query_identity({1,{}},{}).semantic_sha256.size()==64,"empty conjunction canonicalizes without a special variable cap");
}
void sql_identities() {
  const auto left=program("SELECT DISTINCT l.a,q.c,l.a AS again FROM r l JOIN s q ON l.a=q.a WHERE l.b>0 AND l.tag<>'skip'");
  const auto right=program("SELECT DISTINCT x.a,y.c,x.a AS again FROM s y JOIN r x ON y.a=x.a WHERE x.tag<>'skip' AND 0<x.b");
  const auto a=io::query_identity(left),b=io::query_identity(right);
  check(a.canonical==b.canonical && a.plan_cache_sha256==b.plan_cache_sha256,"SQL FROM/predicate order and textual aliases preserve canonical equivalence");
  const auto cycle=program("SELECT EXISTS(SELECT * FROM r a,r b,r c,r d WHERE a.b=b.a AND b.b=c.a AND c.b=d.a AND d.b=a.a)");
  const auto permuted=program("SELECT EXISTS(SELECT NULL FROM r z,r x,r w,r y WHERE w.b=y.a AND x.b=w.a AND z.b=x.a AND y.b=z.a)");
  check(io::query_identity(cycle).canonical==io::query_identity(permuted).canonical,"symmetric self-join occurrences canonicalize by complete colored permutations");
  BindOptions types; types.parameters={{"p",ScalarType::int64}};
  NormalizeOptions one; one.parameters={n(1)}; NormalizeOptions two; two.parameters={n(2)};
  const auto first=program("SELECT DISTINCT a FROM r WHERE a=$1",types,one),second=program("SELECT DISTINCT a FROM r WHERE a=$1",types,two);
  check(io::query_identity(first).semantic_sha256!=io::query_identity(second).semantic_sha256,"concrete parameter specialization belongs to semantic identity");
  const auto changed=program("SELECT DISTINCT l.a,q.c,l.a AS again FROM r l JOIN s q ON l.a=q.a WHERE l.b>1 AND l.tag<>'skip'");
  check(io::query_identity(changed).semantic_sha256!=a.semantic_sha256,"local predicates belong to semantic identity");
}
}  // namespace
int main() {
  try {
    digest_vectors(); program_roundtrip_and_rejection(); version_migration(); direct_identities(); sql_identities();
    std::cout << "schema replay, migration and canonical identity checks passed\n";
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
