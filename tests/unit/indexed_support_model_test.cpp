#include "indexed_runtime_fixture.hpp"
#include "crown/runtime/support.hpp"
#include "crown/io/support.hpp"
#include "crown/io/tree.hpp"
#include "crown/planner/lower.hpp"
#include "crown/frontend/adapter.hpp"
#include "evaluator.hpp"
#include "native_input.hpp"
#include <algorithm>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <set>
#include <stdexcept>
#include <tuple>

namespace {
using namespace crown;
using namespace crown::runtime;
using Assignment=std::map<VariableId,Value>;
using Assignments=std::set<Assignment>;
using Counts=std::map<Row,std::uint64_t>;
using Membership=std::tuple<NodeId,SupportRole,Row>;
using Members=std::map<Membership,SupportHandle>;
using Change=std::tuple<NodeId,SupportRole,Row,SetOperation>;
void check(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); }
std::string read(const std::filesystem::path& path) {
  std::ifstream stream(path); check(bool(stream),"cannot open "+path.string());
  return {std::istreambuf_iterator<char>{stream},std::istreambuf_iterator<char>{}};
}
Row row(const io::Json& values) { Row result; for (const auto& value : values) result.push_back(io::read_scalar(value)); return result; }
VariableSet intersection(const auto& a,const auto& b) {
  VariableSet result; std::set_intersection(a.begin(),a.end(),b.begin(),b.end(),std::inserter(result,result.end())); return result;
}
Assignment assignment(const Row& row,const auto& scope) {
  check(row.size()==scope.size(),"oracle scope width mismatch"); Assignment result; auto value=row.begin();
  for (const auto variable : scope) result.emplace(variable,*value++);
  return result;
}
Row project(const Assignment& value,const auto& scope) {
  Row result; for (const auto variable : scope) result.push_back(value.at(variable)); return result;
}
Assignments join(const Assignments& left,const Assignments& right) {
  Assignments result;
  for (const auto& a : left) for (const auto& b : right) {
    auto combined=a; bool compatible=true;
    for (const auto& [variable,value] : b) {
      const auto [entry,inserted]=combined.emplace(variable,value);
      if (!inserted && entry->second!=value) { compatible=false; break; }
    }
    if (compatible) result.insert(std::move(combined));
  }
  return result;
}
struct ExpectedNode {
  Relation records,survivors;
  Counts parent;
  std::optional<Counts> visible;
  std::map<Row,std::vector<bool>> children;
};
struct Oracle { std::vector<ExpectedNode> nodes; Relation answers; };
Oracle recompute(const auto& plan,const std::vector<Relation>& inputs) {
  const auto& query=reference::input::query(plan.query()); const auto& tree=plan.tree(); Oracle result;
  if (query.contradiction) return result;
  if (query.atoms.empty()) { result.answers.insert(Row{}); return result; }
  result.nodes.resize(tree.nodes.size());
  std::vector<std::optional<NodeId>> parents(tree.nodes.size()); std::vector<NodeId> order{*tree.root};
  for (std::size_t i=0;i<order.size();++i) for (const auto child : tree.nodes[order[i].value].children) { parents[child.value]=order[i]; order.push_back(child); }
  VariableSet head; for (const auto& output : query.head) head.insert(output.variable);
  std::vector<bool> connex(tree.nodes.size()); connex[tree.root->value]=true;
  for (const auto id : order) if (parents[id.value]) {
    const auto separator=intersection(tree.nodes[id.value].scope,tree.nodes[parents[id.value]->value].scope);
    connex[id.value]=connex[parents[id.value]->value] && std::includes(head.begin(),head.end(),separator.begin(),separator.end());
  }
  std::vector<Assignments> subtrees(tree.nodes.size());
  for (auto position=order.rbegin();position!=order.rend();++position) {
    const auto id=*position; const auto& node=tree.nodes[id.value]; auto& expected=result.nodes[id.value];
    Assignments values;
    if (node.kind==NodeKind::native) for (const auto& tuple : inputs[id.value]) values.insert(assignment(tuple,node.scope));
    else values.insert(Assignment{});
    for (const auto child : node.children) values=join(values,subtrees[child.value]);
    subtrees[id.value]=std::move(values);
    for (const auto& value : subtrees[id.value]) expected.survivors.insert(project(value,node.scope));
    const auto separator=parents[id.value] ? intersection(node.scope,tree.nodes[parents[id.value]->value].scope) : VariableSet{};
    if (connex[id.value]) expected.visible.emplace();
    for (const auto& tuple : expected.survivors) {
      const auto values_by_id=assignment(tuple,node.scope);
      ++expected.parent[project(values_by_id,separator)];
      if (expected.visible) ++(*expected.visible)[project(values_by_id,intersection(node.scope,head))];
    }
    if (node.kind==NodeKind::native) expected.records=inputs[id.value];
    else for (const auto child : node.children) for (const auto& [key,count] : result.nodes[child.value].parent) { static_cast<void>(count); expected.records.insert(key); }
    for (const auto& tuple : expected.records) {
      std::vector<bool> flags; const auto values_by_id=assignment(tuple,node.scope);
      for (const auto child : node.children) flags.push_back(result.nodes[child.value].parent.contains(project(values_by_id,intersection(node.scope,tree.nodes[child.value].scope))));
      expected.children.emplace(tuple,std::move(flags));
    }
  }
  // An independent ordinary CQ over one relation per logical occurrence also
  // checks final answers, without production projections or support helpers.
  Catalog catalog; Query expanded=query; expanded.atoms.clear(); Database database;
  for (std::size_t a=0;a<query.atoms.size();++a) {
    const auto found=std::find_if(tree.nodes.begin(),tree.nodes.end(),[&](const auto& node) { return node.occurrence==a; });
    check(found!=tree.nodes.end(),"oracle lost occurrence"); const auto id=static_cast<std::size_t>(found-tree.nodes.begin());
    Table table{"logical_"+std::to_string(a),{}}; Atom atom{query.atoms[a].occurrence,TableId{a},{}};
    atom.terms.reserve(found->scope.size());
    for (const auto variable : found->scope) {
      table.columns.push_back({query.variables[variable.value].name,query.variables[variable.value].type});
      atom.terms.emplace_back(std::in_place_type<VariableId>,variable);
    }
    catalog.tables.push_back(std::move(table)); expanded.atoms.push_back(std::move(atom)); database.tables.push_back(inputs[id]);
  }
  result.answers=reference::evaluate(catalog,expanded,database); return result;
}
Counts counts(const std::vector<ProjectionKeySnapshot>& keys) {
  Counts result; for (const auto& key : keys) check(result.emplace(crown::storage::export_row(key.key.values()),key.support.value).second,"duplicate runtime projection key"); return result;
}
Members members(const SupportRuntime& runtime,const SupportSnapshot& snapshot) {
  Members result;
  const auto add=[&](NodeId node,SupportRole role,const Row& values,SupportHandle handle) {
    check(result.emplace(Membership{node,role,values},handle).second,"duplicate runtime membership");
    const auto owned=runtime.get(handle); check(owned && owned->values()==values,"public stable handle resolves incorrectly");
  };
  for (const auto& node : snapshot.nodes) {
    for (const auto& record : node.records) add(node.node,SupportRole::records,crown::storage::export_row(record.tuple.values()),record.handle);
    for (const auto& tuple : node.survivors) add(node.node,SupportRole::survivors,crown::storage::export_row(tuple.values()),*runtime.find(node.node,SupportRole::survivors,crown::storage::export_row(tuple.values())));
    for (const auto& key : node.parent_keys) add(node.node,SupportRole::parent_support,crown::storage::export_row(key.key.values()),key.handle);
    if (node.visible_keys) for (const auto& key : *node.visible_keys) add(node.node,SupportRole::visible,crown::storage::export_row(key.key.values()),key.handle);
  }
  return result;
}
void compare(const SupportRuntime& runtime,const std::vector<Relation>& inputs) {
  runtime.check_invariants(); const auto actual=runtime.snapshot(); const auto expected=recompute(runtime.plan(),inputs);
  check(actual.has_answer==!expected.answers.empty(),"root answer presence differs from A04");
  check(actual.nodes.size()==expected.nodes.size(),"node count mismatch");
  VariableSet head; for (const auto& field : runtime.plan().query().head) head.insert(field.variable);
  Assignments visible{Assignment{}};
  for (const auto& node : actual.nodes) {
    const auto& wanted=expected.nodes[node.node.value]; Relation records,survivors;
    for (const auto& record : node.records) {
      records.insert(crown::storage::export_row(record.tuple.values())); const auto& flags=wanted.children.at(crown::storage::export_row(record.tuple.values()));
      check(record.child_present==flags && record.satisfied.value==static_cast<std::size_t>(std::count(flags.begin(),flags.end(),true)),"stored child presence/count mismatch");
      check(record.survives==wanted.survivors.contains(crown::storage::export_row(record.tuple.values())),"record survivor bit mismatch");
    }
    for (const auto& tuple : node.survivors) survivors.insert(crown::storage::export_row(tuple.values()));
    check(records==wanted.records && survivors==wanted.survivors,"local records/survivors differ from full subtree joins");
    check(counts(node.parent_keys)==wanted.parent,"P support count differs from unique local survivors");
    check(node.visible_keys.has_value()==wanted.visible.has_value(),"C* membership differs from independent traversal");
    if (wanted.visible) {
      check(counts(*node.visible_keys)==*wanted.visible,"E support count differs from visible subtree projection");
      Assignments local; const auto scope=intersection(runtime.plan().tree().nodes[node.node.value].scope,head);
      for (const auto& key : *node.visible_keys) local.insert(assignment(crown::storage::export_row(key.key.values()),scope));
      visible=join(visible,local);
    }
  }
  Relation answers;
  if (!runtime.plan().query().contradiction) for (const auto& value : visible) {
    Row tuple; for (const auto& field : runtime.plan().query().head) tuple.push_back(value.at(field.variable)); answers.insert(std::move(tuple));
  }
  check(answers==expected.answers,"maintained E join differs from full A04 answers");
}
struct ReferenceValueState {
  bool member=false;
  std::optional<SatisfiedChildCount> satisfied;
  std::vector<bool> child_present;
  std::optional<ProjectionSupportCount> support;
};
template<class Left,class Right>bool same_state(const Left& a,const Right& b) {
  return a.member==b.member && a.satisfied==b.satisfied && std::ranges::equal(a.child_present,b.child_present) && a.support==b.support;
}
struct AuditValue { SupportHandle handle; ReferenceValueState state; };
using AuditState=std::map<Membership,AuditValue>;
AuditState audit_state(const SupportSnapshot& snapshot,const Members& handles) {
  AuditState result;
  const auto add=[&](NodeId node,SupportRole role,const Row& values,ReferenceValueState state) {
    const Membership key{node,role,values}; check(result.emplace(key,AuditValue{handles.at(key),std::move(state)}).second,"duplicate audit state");
  };
  for (const auto& node : snapshot.nodes) {
    for (const auto& record : node.records) add(node.node,SupportRole::records,crown::storage::export_row(record.tuple.values()),{true,record.satisfied,record.child_present,{}});
    for (const auto& tuple : node.survivors) add(node.node,SupportRole::survivors,crown::storage::export_row(tuple.values()),{true,{}, {},{}});
    for (const auto& key : node.parent_keys) add(node.node,SupportRole::parent_support,crown::storage::export_row(key.key.values()),{true,{}, {},key.support});
    if (node.visible_keys) for (const auto& key : *node.visible_keys) add(node.node,SupportRole::visible,crown::storage::export_row(key.key.values()),{true,{}, {},key.support});
  }
  return result;
}
void audit_journal(const SupportRuntime& runtime,const SupportEpoch& epoch,AuditState before,const AuditState& after) {
  const auto& journal=*epoch.journal; std::uint64_t metadata=0,saved_flags=0;
  for (std::size_t i=0;i<journal.records.size();++i) {
    const auto& record=journal.records[i]; const Membership key{record.handle.node,record.handle.role,storage::export_row(record.tuple().values())};
    check(record.ordinal==i+1 && record.cause>0 && record.cause<=epoch.metrics.events_applied,"journal record has an invalid ordinal/cause");
    const auto found=before.find(key);
    check(record.before.member==(found!=before.end()),"journal before membership differs from independent replay");
    if (found!=before.end()) check(found->second.handle==record.handle && same_state(found->second.state,record.before),"journal before metadata/identity differs from independent replay");
    const auto shape=[&](const SupportValueState& value) {
      if (!value.member) { check(!value.satisfied && value.child_present.empty() && !value.support,"absent journal value contains metadata"); return; }
      if (record.handle.role==SupportRole::records) {
        check(value.satisfied && !value.support && value.child_present.size()==runtime.plan().nodes()[record.handle.node.value].children.size(),"record journal shape differs from compiled children");
        check(value.satisfied->value==static_cast<std::size_t>(std::count(value.child_present.begin(),value.child_present.end(),true)),"journal child flags/count disagree");
      } else if (record.handle.role==SupportRole::survivors) check(!value.satisfied && value.child_present.empty() && !value.support,"survivor journal contains counter metadata");
      else check(!value.satisfied && value.child_present.empty() && value.support && value.support->value>0,"projection journal lacks a positive exact support");
    };
    shape(record.before); shape(record.after);
    if (record.handle.role!=SupportRole::survivors) ++metadata;
    if (record.handle.role==SupportRole::records && record.before.member && record.after.member) saved_flags+=static_cast<std::uint64_t>(record.before.child_present.size());
    if (record.after.member) before.insert_or_assign(key,AuditValue{record.handle,ReferenceValueState{record.after.member,record.after.satisfied,
        {record.after.child_present.begin(),record.after.child_present.end()},record.after.support}});
    else if (found!=before.end()) before.erase(found);
  }
  check(before.size()==after.size(),"journal replay final cardinality differs from the subtree oracle state");
  for (const auto& [key,value] : after) {
    const auto found=before.find(key); check(found!=before.end() && found->second.handle==value.handle && same_state(found->second.state,value.state),"journal replay final metadata differs from the subtree oracle state");
  }
  check(epoch.metrics.metadata_changes==metadata && epoch.metrics.saved_child_flags==saved_flags,"metadata/undo-flag accounting differs from journal changes");
  if (!runtime.options().capture_transitions) { check(journal.events.empty(),"disabled trace captured payloads"); return; }
  check(journal.events.size()==epoch.metrics.events_applied,"captured causal events omit an applied event");
  std::vector<const PropagationEvent*> order(journal.events.size(),nullptr);
  std::map<std::uint64_t,std::vector<const PropagationEvent*>> caused;
  for (std::size_t i=0;i<journal.events.size();++i) {
    const auto& event=journal.events[i];
    check(event.id==i+1 && event.sequence==epoch.sequence && event.applied_ordinal>0 && event.applied_ordinal<=order.size(),"event IDs/sequence/application order invalid");
    auto& slot=order[static_cast<std::size_t>(event.applied_ordinal-1)]; check(slot==nullptr,"event applied twice"); slot=&event;
    check(event.id==1 ? event.cause==0 : event.cause>0 && event.cause<event.id,"event cause does not precede its enqueue");
    check(event.before!=event.after && event.operation==(event.after?SetOperation::insert:SetOperation::erase),"event polarity disagrees with before/after membership");
    caused[event.cause].push_back(&event);
  }
  std::deque<std::uint64_t> queue; std::uint64_t peak=0;
  for (std::size_t i=0;i<order.size();++i) {
    const auto* event=order[i]; check(event!=nullptr,"scheduler skipped an event");
    if (i==0) check(event->id==1 && event->kind==SupportEventKind::native_update,"scheduler did not begin with the native event");
    else {
      check(!queue.empty(),"event applied without being enqueued by its cause");
      const auto next=runtime.options().order==PropagationOrder::fifo?queue.front():queue.back();
      check(next==event->id,"captured application order violates the selected FIFO/LIFO discipline");
      if (runtime.options().order==PropagationOrder::fifo) queue.pop_front(); else queue.pop_back();
    }
    for (const auto* child : caused[event->id]) { queue.push_back(child->id); peak=std::max(peak,static_cast<std::uint64_t>(queue.size())); }
  }
  check(queue.empty() && epoch.metrics.queue_peak==peak,"queue peak/drain accounting differs from causal replay");
}
SupportEpoch update(SupportRuntime& runtime,std::vector<Relation>& inputs,NodeId node,SetOperation operation,Row values) {
  const auto before=runtime.snapshot(); const auto old=members(runtime,before); bool changed=false;
  if (operation==SetOperation::insert) changed=inputs[node.value].insert(values).second;
  else changed=inputs[node.value].erase(values)!=0;
  const auto effect=runtime.apply({runtime.sequence()+1,node,operation,std::move(values)});
  check(effect.native_changed==changed,"native set/no-op result differs"); compare(runtime,inputs);
  const auto after=runtime.snapshot(); const auto current=members(runtime,after); std::set<Change> expected,actual;
  for (const auto& [key,handle] : old) {
    const auto found=current.find(key);
    if (found==current.end()) { const auto& [n,r,v]=key; expected.emplace(n,r,v,SetOperation::erase); check(!runtime.get(handle),"removed stable handle remained live"); }
    else check(found->second==handle,"unchanged membership lost its stable ID during commit");
  }
  for (const auto& [key,handle] : current) if (!old.contains(key)) { static_cast<void>(handle); const auto& [n,r,v]=key; expected.emplace(n,r,v,SetOperation::insert); }
  std::uint64_t survivor=0,parent=0,visible=0,child=0,created=0,reclaimed=0;
  for (const auto& change : expected) {
    const auto& [n,role,values,operation]=change; static_cast<void>(values);
    if (role==SupportRole::survivors) ++survivor;
    if (role==SupportRole::parent_support) { ++parent; if (runtime.plan().nodes()[n.value].parent) ++child; }
    if (role==SupportRole::visible) ++visible;
    if (role==SupportRole::records && runtime.plan().nodes()[n.value].kind==NodeKind::generalized) { if (operation==SetOperation::insert) ++created; else ++reclaimed; }
  }
  for (const auto& event : effect.transitions) {
    const auto key=Membership{event.handle.node,event.handle.role,crown::storage::export_row(event.tuple.values())};
    const auto& handle=event.operation==SetOperation::insert ? current.at(key) : old.at(key);
    check(event.handle==handle,"membership transition has the wrong stable identity");
    check(actual.emplace(event.handle.node,event.handle.role,crown::storage::export_row(event.tuple.values()),event.operation).second,"duplicate membership transition");
  }
  check(actual==expected,"internal events are not exact local membership zero crossings");
  check(effect.metrics.survivor_transitions==survivor && effect.metrics.parent_key_transitions==parent && effect.metrics.visible_key_transitions==visible &&
      effect.metrics.child_key_events==child && effect.metrics.candidates_created==created && effect.metrics.candidates_reclaimed==reclaimed,"event accounting differs from independently observed crossings");
  check(effect.metrics.copied_rows==0 && effect.metrics.copied_index_memberships==0 && effect.metrics.copied_metadata_entries==0 &&
      effect.metrics.copied_child_flags==0,"runtime copied whole state instead of journaling affected records");
  if (!changed) check(effect.metrics.work==0 && effect.transitions.empty() && !effect.journal,"no-op journaled or propagated state");
  else {
    check(effect.journal && effect.journal->sequence==effect.sequence && effect.metrics.journal_records==effect.journal->records.size(),"affected record journal omitted changes");
    check(effect.metrics.storage_changes==expected.size(),"storage journal count differs from independent membership crossings");
    check(effect.metrics.events_enqueued==1+child && effect.metrics.events_applied==1+child,"scheduler did not apply every logical event exactly once");
    audit_journal(runtime,effect,audit_state(before,old),audit_state(after,current));
  }
  return effect;
}
Value sample(ScalarType type,std::uint64_t value) {
  switch (type) {
    case ScalarType::int64: return static_cast<std::int64_t>(value);
    case ScalarType::string: return std::string(value==0 ? "a" : value==1 ? "b" : "é");
    case ScalarType::boolean: return value%2==0;
    case ScalarType::date: return Date::parse(value==0 ? "1969-12-31" : value==1 ? "2000-02-29" : "2024-02-29");
    case ScalarType::decimal: return Decimal::parse(value==0 ? "0" : value==1 ? "-1.25" : "1.25");
  }
  throw std::runtime_error("unknown sample scalar");
}
void manual(const std::filesystem::path& root) {
  const auto manifest=io::Json::parse(read(root/"tests/runtime/support/manifest.json")); std::size_t events=0;
  for (const auto& fixture : manifest.at("cases")) {
    const auto document=io::read_document(read(root/fixture.at("query").get<std::string>()));
    const auto tree=io::read_tree(read(root/fixture.at("tree").get<std::string>()),document.catalog,document.query);
    const auto plan=s04_runtime::lower_tree(document.catalog,document.query,tree); SupportOptions options; options.capture_transitions=true;
    SupportRuntime runtime(plan,options); std::vector<Relation> inputs(tree.nodes.size());
    std::map<std::string,NodeId> nodes; for (std::size_t i=0;i<tree.nodes.size();++i) nodes.emplace(tree.nodes[i].id,NodeId{i});
    for (const auto& event : fixture.at("events")) {
      const auto effect=update(runtime,inputs,nodes.at(event.at("node").get<std::string>()),event.at("operation")=="insert" ? SetOperation::insert : SetOperation::erase,row(event.at("values")));
      const auto& expected=event.at("expected"); const auto snapshot=runtime.snapshot();
      check(effect.sequence==event.at("sequence").get<std::uint64_t>() && effect.native_changed==expected.at("native_changed") && snapshot.has_answer==expected.at("has_answer"),"manual event outcome differs");
      for (const auto& [name,wanted] : expected.at("nodes").items()) {
        const auto& node=snapshot.nodes[nodes.at(name).value];
        check(node.records.size()==wanted.at("records").get<std::size_t>() && node.survivors.size()==wanted.at("survivors").get<std::size_t>(),"manual local state cardinality differs");
        const auto expected_keys=[&](const io::Json& values) { Counts result; for (const auto& key : values) result.emplace(row(key.at("key")),key.at("support").get<std::uint64_t>()); return result; };
        check(counts(node.parent_keys)==expected_keys(wanted.at("parent_keys")),"manual P counts differ");
        check(node.visible_keys.has_value()!=wanted.at("visible_keys").is_null(),"manual C* visibility differs");
        if (node.visible_keys) check(counts(*node.visible_keys)==expected_keys(wanted.at("visible_keys")),"manual E counts differ");
      }
      ++events;
    }
  }
  std::cout << events << " manual logical support events passed\n";
}
void randomized(const std::filesystem::path& root) {
  const auto manifest=io::Json::parse(read(root/"tests/structural/lowering/manifest.json")); std::size_t events=0,families=0;
  for (const auto& fixture : manifest.at("cases")) {
    if (!fixture.at("expected").at("valid").get<bool>()) continue;
    const auto document=io::read_document(read(root/fixture.at("query").get<std::string>()));
    const auto tree=io::read_tree(read(root/fixture.at("tree").get<std::string>()),document.catalog,document.query);
    const auto plan=s04_runtime::lower_tree(document.catalog,document.query,tree); ++families;
    for (std::uint64_t seed=1;seed<=2;++seed) {
      std::mt19937_64 random(seed*0x9e3779b97f4a7c15ULL); SupportOptions options; options.capture_transitions=true; options.work_limit.reset();
      SupportRuntime fifo(plan,options); options.order=PropagationOrder::lifo; SupportRuntime lifo(plan,options);
      std::vector<Relation> inputs(tree.nodes.size()),other(tree.nodes.size()); std::vector<NodeId> natives;
      for (const auto& node : plan.nodes()) if (node.kind==NodeKind::native) natives.push_back(node.id);
      compare(fifo,inputs); compare(lifo,other);
      if (natives.empty()) continue;
      for (std::size_t step=0;step<40;++step) {
        const auto id=natives[static_cast<std::size_t>(random()%natives.size())]; const auto operation=random()%100<60 ? SetOperation::insert : SetOperation::erase;
        Row values; const auto coherent=random()%3;
        for (const auto variable : tree.nodes[id.value].scope) values.push_back(sample(document.query.variables[variable.value].type,random()%4==0 ? random()%3 : coherent));
        if (!inputs[id.value].empty() && random()%2==0) { auto found=inputs[id.value].begin(); std::advance(found,static_cast<std::ptrdiff_t>(random()%inputs[id.value].size())); values=*found; }
        static_cast<void>(update(fifo,inputs,id,operation,values)); static_cast<void>(update(lifo,other,id,operation,values)); ++events;
      }
      for (const auto id : natives) while (!inputs[id.value].empty()) {
        const auto values=*inputs[id.value].begin(); static_cast<void>(update(fifo,inputs,id,SetOperation::erase,values)); static_cast<void>(update(lifo,other,id,SetOperation::erase,values)); ++events;
      }
      check(!fifo.has_answer() && !lifo.has_answer(),"complete cleanup retained answer truth");
    }
  }
  std::cout << families << " structural families, two schedules and " << events << " generated/cleanup updates passed\n";
}
void reverse_lookup_and_deep_queue() {
  Catalog catalog{1,{{"r",{{"a",ScalarType::string},{"b",ScalarType::string}}},{"s",{{"b",ScalarType::string}}}}};
  Query query{{{"a",ScalarType::string},{"b",ScalarType::string}},{{"r",TableId{0},{VariableId{0},VariableId{1}}},{"s",TableId{1},{VariableId{1}}}},{{VariableId{0},"a"}},false};
  FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},{"s",NodeKind::native,{VariableId{1}},{},1,{}}},{},{}};
  SupportOptions options; options.work_limit.reset(); SupportRuntime runtime(s04_runtime::lower_tree(catalog,query,tree),options);
  for (std::size_t i=0;i<32;++i) static_cast<void>(runtime.apply({runtime.sequence()+1,NodeId{0},SetOperation::insert,{Value{std::to_string(i)},Value{std::to_string(i)}}}));
  const auto effect=runtime.apply({runtime.sequence()+1,NodeId{1},SetOperation::insert,{Value{std::string("7")}}});
  check(effect.metrics.native_record_visits==2 && effect.metrics.copied_rows==0 && runtime.snapshot().nodes[0].survivors.size()==1,"child support scanned or copied unrelated native records");
  check(effect.journal && std::count_if(effect.journal->records.begin(),effect.journal->records.end(),[](const JournalRecord& value) {
    return value.handle.node==NodeId{0} && value.handle.role==SupportRole::records;
  })==1,"journal retained unrelated parent records");
  runtime.check_invariants();
  Catalog deep; Query cq; cq.variables={{"x",ScalarType::int64}}; cq.head={{VariableId{0},"x"}}; FreeConnexTree chain; chain.root=NodeId{0}; constexpr std::size_t length=128;
  for (std::size_t i=0;i<length;++i) {
    const auto name="r"+std::to_string(i); deep.tables.push_back({name,{{"x",ScalarType::int64}}}); cq.atoms.push_back({name,TableId{i},{VariableId{0}}});
    chain.nodes.push_back({name,NodeKind::native,{VariableId{0}},{},i,{}}); if (i>0) chain.nodes[i-1].children.push_back(NodeId{i});
  }
  SupportRuntime cascade(s04_runtime::lower_tree(deep,cq,chain),options);
  for (std::size_t i=0;i<length-1;++i) static_cast<void>(cascade.apply({cascade.sequence()+1,NodeId{i},SetOperation::insert,{Value{std::int64_t{7}}}}));
  const auto appeared=cascade.apply({cascade.sequence()+1,NodeId{length-1},SetOperation::insert,{Value{std::int64_t{7}}}});
  check(appeared.metrics.survivor_transitions==length && appeared.metrics.child_key_events==length-1 && cascade.has_answer(),"deep iterative insertion propagation stopped early");
  const auto vanished=cascade.apply({cascade.sequence()+1,NodeId{length-1},SetOperation::erase,{Value{std::int64_t{7}}}});
  check(vanished.metrics.survivor_transitions==length && !cascade.has_answer(),"deep iterative deletion propagation stopped early"); cascade.check_invariants();
}
void physical_derivations_bridge() {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64},{"payload",ScalarType::string}}}}};
  const auto bound=frontend::bind_sql("SELECT DISTINCT x FROM r",catalog); check(std::holds_alternative<frontend::BoundSql>(bound),"bridge SQL binding failed");
  const auto normalized=frontend::normalize_sql(std::get<frontend::BoundSql>(bound)); check(std::holds_alternative<frontend::NormalizedSql>(normalized),"bridge normalization failed");
  auto program=std::get<frontend::NormalizedSql>(normalized); const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  const auto plan=s04_runtime::lower_normalized(program,tree); SupportOptions options; options.capture_transitions=true; SupportRuntime runtime(plan,options);
  Database empty; empty.tables.resize(1); frontend::AdapterState adapter(program,empty);
  const Query direct{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0},IgnoredColumn{}}}},{{VariableId{0},"x"}},false}; reference::Session oracle(catalog,direct,empty);
  std::optional<SupportHandle> visible;
  const std::vector<std::pair<SetOperation,Row>> events{{SetOperation::insert,{Value{std::int64_t{7}},Value{std::string("a")}}},
      {SetOperation::insert,{Value{std::int64_t{7}},Value{std::string("b")}}},{SetOperation::erase,{Value{std::int64_t{7}},Value{std::string("a")}}},
      {SetOperation::erase,{Value{std::int64_t{7}},Value{std::string("b")}}}};
  for (std::size_t i=0;i<events.size();++i) {
    const PhysicalSetUpdate input{static_cast<std::uint64_t>(i+1),TableId{0},events[i].first,events[i].second}; const auto adapted=adapter.apply(input); const auto expected=oracle.apply(input);
    for (const auto& occurrence : adapted.occurrences) for (const auto operation : {SetOperation::insert,SetOperation::erase}) {
      const auto& values=operation==SetOperation::insert ? occurrence.delta.added : occurrence.delta.removed;
      for (const auto& value : values) {
        const auto& port=plan.inputs()[occurrence.occurrence.value]; const auto tuple=port.projection.apply(port.projection.source().tuple(value));
        static_cast<void>(runtime.apply({runtime.sequence()+1,port.node,operation,crown::storage::export_row(tuple.values())}));
      }
    }
    const auto snapshot=runtime.snapshot(); Relation actual; for (const auto& key : *snapshot.nodes[0].visible_keys) actual.insert(crown::storage::export_row(key.key.values()));
    check(actual==expected.current,"multiple physical derivations lost projected support");
    if (i<3) {
      const auto handle=runtime.find(NodeId{0},SupportRole::visible,{Value{std::int64_t{7}}}); check(handle.has_value(),"live physical derivation lost E key");
      if (visible) check(handle==visible,"nonzero physical derivation change replaced stable E assignment"); else visible=handle;
      check(snapshot.nodes[0].visible_keys->at(0).support.value==1,"E count conflated physical derivations with logical survivors");
    } else check(!runtime.get(*visible) && !runtime.has_answer(),"last physical derivation did not delete its logical assignment");
    runtime.check_invariants();
  }
}
}  // namespace
int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: crown_support_model_test REPOSITORY"); manual(argv[1]); randomized(argv[1]); reverse_lookup_and_deep_queue(); physical_derivations_bridge();
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
