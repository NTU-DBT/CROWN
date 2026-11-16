#include "crown/runtime/program.hpp"
#include "crown/io/batch.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <array>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>

using namespace crown;
using namespace crown::runtime;
static_assert(sizeof(storage::TupleLayout)==sizeof(storage::AccountedLayout));
static_assert(sizeof(storage::Projection)==sizeof(storage::AccountedProjection));
namespace {
void check(bool value,std::string_view message) {if(!value)throw std::runtime_error(std::string(message));}
PhysicalPlan source_plan(bool indexed,bool sql) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::string},{"y",ScalarType::int64}}},
      {"unused",{{"flag",ScalarType::boolean}}}}};
  if(!sql) {
    const Query query{{{"x",ScalarType::string},{"y",ScalarType::int64}},
        {{"r",TableId{0},{VariableId{0},VariableId{1}}}},{{VariableId{0},"x"},{VariableId{1},"y"}},false};
    const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{},0,{}}},{},{}};
    return planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
  }
  frontend::BindOptions bind;bind.parameters={{"minimum",ScalarType::int64}};
  auto bound=frontend::bind_sql("SELECT DISTINCT item.x AS first, item.y AS second, item.x AS repeated, 'marker' AS extra FROM r AS item WHERE item.y >= $1 AND NOT (item.x = 'blocked')",catalog,bind);
  check(std::holds_alternative<frontend::BoundSql>(bound),"SQL metadata fixture did not bind");
  frontend::NormalizeOptions options;options.parameters={Value{std::int64_t{5}}};
  auto result=frontend::normalize_sql(std::get<frontend::BoundSql>(bound),options);
  check(std::holds_alternative<frontend::NormalizedSql>(result),"SQL metadata fixture did not normalize");
  auto normalized=std::move(std::get<frontend::NormalizedSql>(result));
  check(normalized.core.atoms.size()==1,"SQL fixture did not produce one native factor");
  VariableSet scope;for(const auto& term:normalized.core.atoms[0].terms)
    if(const auto* variable=std::get_if<VariableId>(&term))scope.insert(*variable);
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,scope,{},0,{}}},{},{}};
  return planner::lower_normalized(normalized,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
io::Json copied(program::JsonView value) {
  using K=program::JsonKind;
  switch(value.kind()) {
    case K::null:return nullptr;
    case K::boolean:return value.boolean();
    case K::integer:return value.integer();
    case K::unsigned_integer:return value.unsigned_integer();
    case K::number:return value.number();
    case K::string:return std::string(value.text());
    case K::array: {auto result=io::Json::array();for(std::size_t i=0;i<value.size();++i)result.push_back(copied(value.at(i)));return result;}
    case K::object: {auto result=io::Json::object();for(std::size_t i=0;i<value.size();++i)result[std::string(value.key(i))]=copied(value.member(i));return result;}
  }
  throw std::runtime_error("unknown native JSON kind");
}
std::vector<const storage::Projection*> projections(const PhysicalPlan& plan) {
  std::vector<const storage::Projection*> result;
  for(const auto& index:plan.indexes())result.push_back(&index.projection);
  for(const auto& input:plan.inputs())result.push_back(&input.projection);
  for(const auto& node:plan.nodes()) {result.push_back(&node.parent_key);if(node.visible_projection)result.push_back(&*node.visible_projection);}
  for(const auto& edge:plan.edges())result.push_back(&edge.parent_key);
  for(const auto& step:plan.enumeration().steps)if(step.parent_key)result.push_back(&*step.parent_key);
  return result;
}
std::vector<const storage::AccountedProjection*> projections(const CompiledProgram& plan) {
  std::vector<const storage::AccountedProjection*> result;
  for(const auto& index:plan.indexes())result.push_back(&index.projection);
  for(const auto& input:plan.inputs())result.push_back(&input.projection);
  for(const auto& node:plan.nodes()) {result.push_back(&node.parent_key);if(node.visible_projection)result.push_back(&*node.visible_projection);}
  for(const auto& edge:plan.edges())result.push_back(&edge.parent_key);
  for(const auto& step:plan.enumeration().steps)if(step.parent_key)result.push_back(&*step.parent_key);
  return result;
}
void complete_copy(bool indexed,bool sql) {
  auto account=resource::MemoryAccount::create(8*1024*1024);CompiledProgram native;
  storage::AccountedIndexWork grant;io::Json identity;std::string physical_hash,sql_text,catalog_name;
  std::vector<bool> aliases;std::vector<Row> rows{{std::string("allowed"),std::int64_t{6}},
      {std::string("blocked"),std::int64_t{6}},{std::string("allowed"),std::int64_t{4}}};
  auto binary=std::string(8192,'z');binary.append("\0\xff",2);rows.push_back({binary,std::int64_t{9}});
  std::vector<std::optional<Row>> expected;
  {
    const auto source=source_plan(indexed,sql);identity=source.identity().canonical;physical_hash=source.physical_sha256();
    catalog_name=source.catalog().tables.at(0).name;
    if(sql)sql_text=source.normalized()->binding.source;
    const auto original=projections(source);
    for(const auto* a:original)for(const auto* b:original)aliases.push_back(a->same_token(*b));
    for(const auto& row:rows) {const auto tuple=source.adapt_input(OccurrenceId{0},row);expected.push_back(tuple?std::optional<Row>(crown::storage::export_row(tuple->values())):std::nullopt);}
    if(indexed)grant=storage::AccountedIndexWork::create(account,source.options().indexed_storage->per_operation);
    native=CompiledProgram::freeze(account,source,grant.get());
  }
  check(native.physical_sha256()==physical_hash && copied(native.identity().canonical)==identity,"native identity did not survive source destruction");
  check(native.catalog().tables.at(0).name==catalog_name && native.query().atoms.size()==1 && native.validation().valid,
      "native model metadata was not copied");
  if(sql)check(native.normalized()->binding.source==sql_text && native.normalized()->parameters.at(0).has_value(),"SQL source/parameters were not retained");
  check(native.sources().size()==2 && native.sources()[1].layout.fields().size()==1 &&
      native.sources()[1].layout.fields()[0].type==ScalarType::boolean &&
      native.sources()[1].layout.origin()->table==TableId{1} &&
      native.sources()[1].layout.context().binding==physical_hash+":source",
      "unused source layout did not retain native fields, origin and context");
  check(native.sql_result_layout().fields().size()==(sql?4:2),"native SQL output layout has wrong arity");
  {
    const std::array variables{VariableId{0},VariableId{0}};
    const auto scope=native.scope_layout(LayoutId{native.layouts().size()+1},variables,":test-fragment",grant.get());
    check(scope.fields().size()==2 && scope.context().binding==physical_hash+":test-fragment" &&
        scope.validation_issue(Row{std::string("left"),std::string("right")}).problem==storage::TupleProblem::repeated_variable,
        "native fragment layout lost its repeated-variable constraint");
  }
  const auto current=projections(native);std::size_t position=0;
  for(const auto* a:current)for(const auto* b:current)check(a->same_token(*b)==aliases.at(position++),"native projection alias graph changed");
  check(position==aliases.size(),"native projection inventory changed");
  for(std::size_t i=0;i<rows.size();++i) {
    const std::array values{storage::borrow_scalar(rows[i][0]),storage::borrow_scalar(rows[i][1])};
    const auto tuple=native.adapt_input(OccurrenceId{0},storage::RowView::borrow(values),grant.get());
    check(tuple.has_value()==expected[i].has_value(),"native adapter filtering differs from legacy reference");
    if(tuple)check(tuple->values()==*expected[i],"native adapter values differ from legacy reference");
  }
  const auto bytes_before=account.statistics().current;
  std::optional<storage::TupleLayout> readable_layout;
  std::optional<storage::Projection> readable_projection;
  bool same_layout=false,same_projection=false,allocated=false;
  {
    s04_alloc::Scope fault(0);
    readable_layout.emplace(native.inputs().at(0).projection.source().descriptor());
    readable_projection.emplace(native.inputs().at(0).projection.descriptor());
    same_layout=readable_layout->same_token(native.inputs().at(0).projection.source());
    same_projection=readable_projection->same_token(native.inputs().at(0).projection);
    allocated=s04_alloc::calls!=0 || s04_alloc::triggered;
  }
  check(!allocated && same_layout && same_projection && account.statistics().current==bytes_before,
      "readable native descriptor allocated a mirror or changed canonical token");
  std::optional<storage::AccountedPlanStorage> tables;
  tables.emplace(native.make_storage(grant.get()));
  for(const auto& relation:native.relations())check(tables->table(relation.id).layout().same_token(relation.layout),"new mutable table lost canonical layout token");
  native={};tables->check_invariants(grant.get());
  tables.emplace(storage::AccountedPlanStorage(tables->binding(),grant.get()));
  {
    const auto source=readable_layout->tuple({std::string("allowed"),std::int64_t{6}});
    const auto result=readable_projection->apply(source);
    check(result.values()==Row{std::string("allowed"),std::int64_t{6}},"native-backed descriptor lost fields/context after program destruction");
  }
  tables.reset();readable_layout.reset();readable_projection.reset();grant={};account.check_invariants();
  check(account.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes(),
      "last native-readable descriptor or binding did not release its accounted backing");
  std::cout<<(indexed?"indexed":"reference")<<(sql?" SQL":" core")<<" native full metadata/identity/alias/adapter/source lifetime passed\n";
}
void failure_cleanup(bool indexed) {
  const auto source=source_plan(indexed,true);std::size_t positions=0;
  for(std::ptrdiff_t fail=0;fail<4000;++fail) {
    auto account=resource::MemoryAccount::create(8*1024*1024);storage::AccountedIndexWork grant;
    if(indexed)grant=storage::AccountedIndexWork::create(account,source.options().indexed_storage->per_operation);
    const auto before=account.statistics().current;bool failed=false,triggered=false;
    {
      s04_alloc::Scope fault(fail);
      try {auto value=CompiledProgram::freeze(account,source,grant.get());}
      catch(const std::bad_alloc&) {failed=true;}
      triggered=s04_alloc::triggered;
    }
    account.check_invariants();check(account.statistics().current==before,"failed native program construction leaked a metadata body or binding");
    if(!triggered) {check(!failed,"untriggered program construction failed");break;}
    check(failed,"allocation fault did not escape native program construction");++positions;
    {auto retry=CompiledProgram::freeze(account,source,grant.get());check(retry.validation().valid,"native program retry invalid");}
    check(account.statistics().current==before,"native metadata retry retained allocations");
    if(fail==3999)throw std::runtime_error("native constructor fault sweep did not finish");
  }
  std::cout<<(indexed?"indexed":"reference")<<" native full program constructor fault positions="<<positions<<"; exact cleanup and retry passed\n";
}
void native_catalog_io(bool sql) {
  auto account=resource::MemoryAccount::create(8*1024*1024);
  io::CatalogSource retained;
  const io::InputEvent event{{1,TableId{0},SetOperation::insert,
    {std::string("allowed"),std::int64_t{6}}},io::SourcePosition{"input",17}};
  std::string fingerprint,json,binary;
  {
    const auto source=source_plan(false,sql);
    fingerprint=io::input_catalog_sha256(source.source_catalog());
    json=io::write_input_json(event,source.source_catalog());
    binary=io::write_input_binary(event,source.source_catalog());
    auto native=CompiledProgram::freeze(account,source);
    const auto before=account.statistics().current;bool allocated=false;
    {
      s04_alloc::Scope fault(0);retained=native.source_catalog_owner();
      allocated=s04_alloc::calls!=0 || s04_alloc::triggered;
    }
    check(!allocated && account.statistics().current==before,
      "catalog alias allocated a mirror or another native control");
  }
  {
    const auto& catalog=*std::get<std::shared_ptr<const program::Catalog>>(retained);
    check(io::input_catalog_sha256(catalog)==fingerprint && io::write_input_json(event,catalog)==json &&
      io::write_input_binary(event,catalog)==binary,"native wire binding differs after compiler/program destruction");
    for(const auto format:{io::InputFormat::jsonl,io::InputFormat::binary,io::InputFormat::csv}) {
      io::InputOptions options;options.format=format;
      if(format==io::InputFormat::csv)options.table=TableId{0};
      std::istringstream stream(format==io::InputFormat::jsonl?json+"\n":
        format==io::InputFormat::binary?binary:"x,y\nallowed,6\n");
      io::EventReader reader(stream,retained,options);
      check(std::holds_alternative<std::shared_ptr<const program::Catalog>>(reader.catalog()),
        "native reader materialized an owning compiler catalog");
      const auto* decoded=reader.peek();
      check(decoded && decoded->update.sequence==1 && decoded->update.table==TableId{0} &&
        decoded->update.operation==SetOperation::insert && decoded->update.values==event.update.values,
        "native reader changed the physical row or operation");
      if(format!=io::InputFormat::csv)check(decoded->source_position==event.source_position,"native wire position changed");
      reader.acknowledge();check(!reader.peek(),"native reader fabricated another event");
      check(reader.close().sequence==1,"native reader lost accepted progress");
    }
    io::TypedQueue queue(retained,io::QueueMode::physical);
    io::TransportBatch batch({event});check(queue.enqueue(batch)==io::Admission::accepted,"native queue rejected a valid batch");
    const auto* item=queue.peek();check(item && std::get<io::InputEventView>(*item).update.values==event.update.values,
      "native queue changed the validated source row");
    queue.acknowledge();check(queue.empty() && queue.close().sequence==1,"native queue lost accepted progress");
  }
  retained=Catalog{};account.check_invariants();
  check(account.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes(),
    "closed native readers/queue retained the program or catalog alias");
  std::cout<<(sql?"SQL":"core")<<" native catalog alias/wire/readers/queue lifetime passed\n";
}
void direct_layout_lifetime() {
  auto account=resource::MemoryAccount::create(1024*1024);
  const auto before=account.statistics().current;
  {
    std::optional<storage::AccountedLayout> layout;
    {
      const std::array fields{storage::Field{ScalarType::string,{},VariableId{0}},
          storage::Field{ScalarType::string,{},VariableId{0}}};
      const std::string binding("native\0\xff",8);
      layout.emplace(storage::AccountedLayout::make(account,LayoutId{71},fields,{9,binding},storage::LayoutOrigin{TableId{3},4}));
    }
    const std::string expected("native\0\xff",8);
    check(layout->context().binding==expected && layout->origin()==storage::LayoutOrigin{TableId{3},4},
        "direct native layout borrowed caller context or origin");
    const auto descriptor=layout->descriptor();layout.reset();
    descriptor.validate({std::string("same"),std::string("same")});
    bool rejected=false;
    try {descriptor.validate({std::string("same"),std::string("different")});}
    catch(const Error& failure) {rejected=failure.code()=="invalid_tuple";}
    check(rejected,"native-backed readable descriptor lost repeated-variable validation");
    const auto retained=account.statistics().current;
    const auto invalid=[&](std::span<const storage::Field> fields,storage::LayoutContextView context,
        std::optional<storage::LayoutOrigin> origin={}) {
      bool failed=false;
      try {static_cast<void>(storage::AccountedLayout::make(account,LayoutId{72},fields,context,origin));}
      catch(const storage::TupleValidationFailure& failure) {failed=failure.issue().problem==storage::TupleProblem::invalid_layout;}
      check(failed && account.statistics().current==retained,"invalid native layout did not reject and release partial storage");
    };
    const std::array wrong_kind{storage::Field{static_cast<ScalarType>(99)}};
    invalid(wrong_kind,{1,{}});
    const std::array wrong_domain{storage::Field{ScalarType::decimal,DecimalSpec{39,0}}};
    invalid(wrong_domain,{1,{}});
    const std::array wrong_variable{storage::Field{ScalarType::string,{},VariableId{0}},storage::Field{ScalarType::int64,{},VariableId{0}}};
    invalid(wrong_variable,{1,{}});invalid({}, {0,{}});invalid({}, {1,{}},storage::LayoutOrigin{TableId{0},0});
    const auto empty=storage::AccountedLayout::make(account,LayoutId{73},{});
    check(empty.fields().empty() && empty.context().binding.empty() && empty.validation_issue(Row{}).ok(),"empty native layout invalid");
  }
  account.check_invariants();check(account.statistics().current==before,"direct native layout retained storage after its last descriptor");
}
}
int main() {
  try {direct_layout_lifetime();native_catalog_io(false);native_catalog_io(true);for(bool indexed:{false,true}) {complete_copy(indexed,false);complete_copy(indexed,true);failure_cleanup(indexed);}return 0;}
  catch(const std::exception& failure) {std::cerr<<failure.what()<<'\n';return 1;}
}
