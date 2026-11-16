#include "sql_aggregate_session_fixture.hpp"
#include "index_allocation.hpp"
#include <iostream>
#include <type_traits>

namespace {
using namespace crown;
using namespace crown::sql_aggregate_session_test;
using CreateFactory=ar::Session(*)(const resource::MemoryAccount&,ar::SessionPaths,ar::SessionIdentity,
    frontend::SqlAggregateProgram,const FreeConnexTree&,const PhysicalOptions&,runtime::sql_aggregate::Options,const ar::SessionLimits&);
using RecoverFactory=ar::Session(*)(const resource::MemoryAccount&,ar::SessionPaths,const ar::Id&,const ar::SessionLimits&);
static_assert(std::is_same_v<decltype(&ar::Session::create_into),CreateFactory>);
static_assert(std::is_same_v<decltype(&ar::Session::recover_into),RecoverFactory>);
// Real WAL decisions couple nullable physical weights, native groups, source/
// reader progress and actual sink closures. Caller buffers may die after log.
void lifecycle(bool indexed) {
  Fixture f(indexed);std::optional<ar::Session> s;s.emplace(f.create());state(*s,0,0,0,0);
  assert(s->selected_root().plan_sha256 && s->selected_root().delivery);
  std::array<Cell,2> row{Cell{},number(5)};std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,2}};
  std::string source="feed";s->log({1,edits,ar::SourcePosition{source,10},ar::ReaderPosition{10,1}});state(*s,1,0,0,0);
  assert(s->progress().source_positions.empty() && !s->reader_position());source[0]='x';row[1]=number(99);edits[0].after=9;
  assert(s->pending_input()->replacements[0].after==2 && s->pending_input()->source->source=="feed");
  assert(s->logged_reader_position()==(ar::ReaderPosition{10,1}));
  assert(!s->decide().rejected);state(*s,1,1,1,0);const auto output=std::string(*s->output());
  refused([&]{s->log({2,{},{},{}});});s.reset();s.emplace(f.recover());state(*s,1,1,1,0);assert(*s->output()==output);
  row[1]=number(5);assert(s->source_weight(TableId{0},row)==2 && s->progress().source_positions.at("feed")==10);
  assert(s->deliver() && !s->deliver());state(*s,1,1,1,1);
  edits[0].before=9;edits[0].after=0;s->log({2,edits,ar::SourcePosition{"feed",20},ar::ReaderPosition{20,2}});
  assert(s->decide().rejected==ar::RejectReason::weight_mismatch);state(*s,2,2,1,1);assert(!s->output());
  edits[0].before=edits[0].after=2;s->log({3,edits,ar::SourcePosition{"feed",30},ar::ReaderPosition{30,3}});
  assert(!s->decide().rejected && s->output()->size()==ar::frame_header_size+107);assert(s->deliver());state(*s,3,3,2,2);
  const auto root=s->checkpoint();assert(root.generation==2 && root.physical_sequence==2 && root.command_sequence==3);
  const auto header=frames(contents(generation_file(f,2)));assert(header.size()==1);
  const std::array<Cell,2> other{text("other"),number(7)};
  const std::array mixed{runtime::sql_rows::SourceReplacement{TableId{0},row,2,1},runtime::sql_rows::SourceReplacement{TableId{0},other,0,3}};
  assert(!step(*s,mixed).rejected);state(*s,4,4,3,3);s.reset();s.emplace(f.recover());state(*s,4,4,3,3);
  assert(s->source_weight(TableId{0},row)==1 && s->source_weight(TableId{0},other)==3);
  const auto result=s->snapshot();assert(result.groups.size()==2 && s->progress().source_positions.at("feed")==30);
  const auto wal=frames(contents(generation_file(f,2)));const auto input=ar::inspect(s->descriptor().program(),wal[1]);
  assert(input.ordinal==1 && std::get<ar::InputInfo>(input.payload).command_sequence==4);
  const auto sink=frames(contents(f.sink));const auto epoch=ar::inspect(s->descriptor().program(),sink.back());
  assert(epoch.ordinal==3 && std::get<ar::GroupInfo>(epoch.payload).generation==2);
}
// Every supported rejection is produced by the genuine native factory. Resource
// failures have no Reject tag and cannot advance I/C. A valid retry follows each.
void semantic_rejections() {
  for(unsigned mode=0;mode<4;++mode) {
    Catalog catalog=schema();std::string_view sql="SELECT COUNT(*) FROM r";
    if(mode==2)catalog.tables[0].constraints.push_back(UniqueConstraint{"u",{ColumnId{1}},ConstraintStatus::enforced});
    if(mode==3) {
      catalog={1,{{"p",{{"id",ScalarType::int64}}},{"c",{{"pid",ScalarType::int64}}}}};
      catalog.tables[0].constraints.push_back(UniqueConstraint{"p",{ColumnId{0}},ConstraintStatus::enforced});
      catalog.tables[1].constraints.push_back(ForeignKeyConstraint{"f",{ColumnId{0}},TableId{0},{ColumnId{0}},ConstraintStatus::enforced});sql="SELECT COUNT(*) FROM c";
    }
    Fixture f(false,catalog,sql);f.normal.source.native.multiplicity_limit=10;if(mode==1)f.normal.count_limit=3;
    std::optional<ar::Session> owner;owner.emplace(f.create());const std::array<Cell,2> row{text("a"),number(1)};const std::array<Cell,1> child{number(1)};
    const auto cells=mode==3?std::span<const Cell>{child}:std::span<const Cell>{row};
    const std::uint64_t after=mode==0?11:mode==1?4:mode==2?2:1;
    std::array edits{runtime::sql_rows::SourceReplacement{TableId{mode==3?1U:0U},cells,0,after}};
    const auto result=step(*owner,edits);const auto expected=mode==0?ar::RejectReason::source_overflow:mode==1?ar::RejectReason::aggregate_overflow:mode==2?ar::RejectReason::unique_violation:ar::RejectReason::foreign_key_violation;
    assert(result.rejected==expected);state(*owner,1,1,0,0);assert(owner->source_weight(edits[0].source,cells)==0 && !owner->output());
    owner.reset();owner.emplace(f.recover());state(*owner,1,1,0,0);assert(owner->progress().source_positions.empty());
    edits[0].after=0;assert(!step(*owner,edits).rejected);owner.reset();owner.emplace(f.recover());state(*owner,2,2,1,1);
  }
  Catalog join_schema{1,{{"r",{{"id",ScalarType::int64}}},{"s",{{"id",ScalarType::int64}}}}};
  Fixture f(false,join_schema,"SELECT COUNT(*) FROM r JOIN s ON r.id=s.id");std::optional<ar::Session> owner;owner.emplace(f.create());const std::array<Cell,1> row{number(1)};
  std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,1ULL<<63},runtime::sql_rows::SourceReplacement{TableId{1},row,0,2}};
  assert(step(*owner,edits).rejected==ar::RejectReason::annotation_overflow);state(*owner,1,1,0,0);
  owner.reset();owner.emplace(f.recover());state(*owner,1,1,0,0);
  assert(owner->source_weight(TableId{0},row)==0 && owner->source_weight(TableId{1},row)==0);
  edits[0].after=edits[1].after=1;assert(!step(*owner,edits).rejected);owner.reset();owner.emplace(f.recover());state(*owner,2,2,1,1);
}
// Integer guards are reconstructed from original SQL during descriptor rebind.
// A pending cast refusal disposes I/reader progress without C/D; a later signed
// cancellation commits atomically and survives a complete selected checkpoint.
void varying_integer_recovery(bool indexed) {
  Fixture f(indexed, schema(), "SELECT COUNT(*),COUNT((x::integer)::bigint),SUM(x::integer),SUM(x) FROM r WHERE g='visible'");
  constexpr std::uint64_t amount = 4294967299ULL;
  const std::array<Cell, 2> hidden{text("hidden"), number(std::int64_t{INT32_MAX} + 1)};
  const std::array<Cell, 2> bad{text("visible"), number(std::int64_t{INT32_MAX} + 1)};
  const std::array<Cell, 2> positive{text("visible"), number(INT32_MAX)};
  const std::array<Cell, 2> negative{text("visible"), number(-INT32_MAX)};
  const std::array seed{runtime::sql_rows::SourceReplacement{TableId{0}, hidden, 0, 1}};
  const std::array invalid{runtime::sql_rows::SourceReplacement{TableId{0}, bad, 0, 1}};
  {
    auto owner = f.create(); assert(!step(owner, seed).rejected);
    assert(owner.checkpoint().generation == 2);
    owner.log({2, invalid, ar::SourcePosition{"feed", 10}, ar::ReaderPosition{10, 1}});
    state(owner, 2, 1, 1, 1);
  }
  {
    auto owner = f.recover(); state(owner, 2, 1, 1, 1);
    assert(owner.descriptor().program().kernel_program().checked_int32_columns().size() == 1);
    assert(owner.decide().rejected == ar::RejectReason::aggregate_overflow);
    state(owner, 2, 2, 1, 1);
    assert(owner.source_weight(TableId{0}, bad) == 0 && owner.source_weight(TableId{0}, hidden) == 1);
    assert(owner.progress().source_positions.at("feed") == 10 && owner.reader_position() == (ar::ReaderPosition{10, 1}));
  }
  // A checksum-valid false Reject must be recomputed and refused before torn
  // WAL/sink repair. The record alone cannot authorize a cast failure.
  const auto wal_path = generation_file(f, 2), wal = contents(wal_path), sink = contents(f.sink);
  auto records = frames(wal);
  const auto last = ar::inspect(f.program, records.back());
  auto wrong = std::get<ar::Reject>(last.payload); wrong.reason = ar::RejectReason::weight_mismatch;
  const auto encoded = ar::encode(f.account, f.program, last.ordinal, wrong);
  records.back() = encoded.bytes(); const auto corrupt = join(records, records.size()) + "C";
  put(wal_path, corrupt); put(f.sink, sink + "C");
  refused([&] { auto owner = f.recover(); });
  assert(contents(wal_path) == corrupt && contents(f.sink) == sink + "C");
  put(wal_path, wal); put(f.sink, sink);
  const std::array balanced{runtime::sql_rows::SourceReplacement{TableId{0}, positive, 0, amount},
      runtime::sql_rows::SourceReplacement{TableId{0}, negative, 0, amount}};
  {
    auto owner = f.recover(); state(owner, 2, 2, 1, 1);
    assert(!step(owner, balanced).rejected); state(owner, 3, 3, 2, 2);
    const auto snapshot = owner.snapshot(); assert(snapshot.groups.size() == 1);
    const auto values = snapshot.groups[0].values.view();
    assert(values[0] == number(static_cast<std::int64_t>(2 * amount)));
    assert(values[1] == values[0] && values[2] == number(0));
    assert(owner.checkpoint().generation == 3);
  }
  {
    auto owner = f.recover(); state(owner, 3, 3, 2, 2);
    assert(owner.source_weight(TableId{0}, positive) == amount && owner.source_weight(TableId{0}, negative) == amount);
    assert(owner.source_weight(TableId{0}, hidden) == 1);
    const std::array unbalanced{runtime::sql_rows::SourceReplacement{TableId{0}, negative, amount, 0}};
    assert(step(owner, unbalanced).rejected == ar::RejectReason::aggregate_overflow);
    state(owner, 4, 4, 2, 2); assert(owner.checkpoint().generation == 4);
  }
  {
    auto owner = f.recover(); state(owner, 4, 4, 2, 2);
    const std::array erase{runtime::sql_rows::SourceReplacement{TableId{0}, positive, amount, 0},
        runtime::sql_rows::SourceReplacement{TableId{0}, negative, amount, 0}};
    assert(!step(owner, erase).rejected); state(owner, 5, 5, 3, 3);
    const auto snapshot = owner.snapshot(); const auto values = snapshot.groups[0].values.view();
    assert(values[0] == number(0) && values[1] == number(0) && !values[2] && !values[3]);
    assert(frames(contents(f.sink)).size() == 4);
  }
}
// Pending logged input survives a resource failure and cold reopen without a
// second Input record. Source/reader and log ordinals are asserted separately.
void pending_and_progress() {
  Fixture f;std::array<Cell,2> row{Cell{},number(3)};const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,1}};
  {auto s=f.create();s.log({1,edits,ar::SourcePosition{"a",10},ar::ReaderPosition{10,1}});
    bool failed=false;{s04_alloc::Scope deny(0);try{static_cast<void>(s.decide());}catch(const std::bad_alloc&){failed=true;}}
    assert(failed && !s.requires_reopen());state(s,1,0,0,0);assert(s.pending_input() && s.progress().source_positions.empty());}
  auto s=f.recover();state(s,1,0,0,0);assert(s.logged_reader_position()==(ar::ReaderPosition{10,1}));
  assert(!s.decide().rejected && s.deliver());assert(frames(contents(generation_file(f,1))).size()==3);
  for(const auto source:{ar::SourcePosition{"a",10},ar::SourcePosition{"a",9}})refused([&]{s.log({2,{},source,{}});});
  refused([&]{s.log({2,{},{},ar::ReaderPosition{11,3}});});state(s,1,1,1,1);
  s.log({2,{},{},ar::ReaderPosition{11,2}});assert(!s.decide().rejected && s.deliver());state(s,2,2,2,2);
}
// A recorded Reject is evidence to verify, never permission to skip the native
// attempt. False reasons/successful Inputs and false sink values block all repair.
void semantic_corruption() {
  Fixture f;const std::array<Cell,2> row{Cell{},number(4)};
  const std::array edit{runtime::sql_rows::SourceReplacement{TableId{0},row,9,0}};
  {auto s=f.create();s.log({1,edit,ar::SourcePosition{"feed",10},ar::ReaderPosition{10,1}});assert(s.decide().rejected==ar::RejectReason::weight_mismatch);}
  const auto path=generation_file(f,1),wal=contents(path),sink=contents(f.sink);auto parts=frames(wal);
  auto replacement=std::get<ar::Reject>(ar::inspect(f.program,parts[2]).payload);replacement.reason=ar::RejectReason::aggregate_overflow;
  const auto wrong=ar::encode(f.account,f.program,2,replacement);parts[2]=wrong.bytes();put(path,join(parts,parts.size())+"C");put(f.sink,sink+"C");
  const auto corrupted=contents(path);refused([&]{auto s=f.recover();});assert(contents(path)==corrupted && contents(f.sink)==sink+"C");
  put(path,wal);put(f.sink,sink);
  {auto s=f.recover();state(s,1,1,0,0);assert(s.progress().source_positions.at("feed")==10 && s.reader_position()==(ar::ReaderPosition{10,1}));
    const std::array good{runtime::sql_rows::SourceReplacement{TableId{0},row,0,1}};assert(!step(s,good).rejected);}
  const auto complete_wal=contents(path),complete_sink=contents(f.sink);auto sink_parts=frames(complete_sink);
  const auto group=std::get<ar::GroupInfo>(ar::inspect(f.program,sink_parts[1]).payload);
  const std::array<Cell,1> key{Cell{}};const std::array<Cell,3> after{Cell{},number(2),storage::ScalarView{storage::InlineDecimal::parse("4")}};
  const std::array fake{runtime::aggregate::GroupChange{runtime::aggregate::Tuple::copy_of(f.account,key),{},runtime::aggregate::Tuple::copy_of(f.account,after)}};
  const auto false_epoch=ar::encode(f.account,f.program,1,ar::GroupEpochView{group.generation,group.input_sequence,group.physical_sequence,group.input_sha256,group.changed,group.group_changed,fake});
  static_cast<void>(ar::inspect(f.program,false_epoch.bytes()));sink_parts[1]=false_epoch.bytes();put(path,complete_wal+"C");put(f.sink,join(sink_parts,sink_parts.size())+"C");
  const auto false_sink=contents(f.sink);refused([&]{auto s=f.recover();});assert(contents(path)==complete_wal+"C" && contents(f.sink)==false_sink);
  put(path,complete_wal);put(f.sink,complete_sink);parts=frames(complete_wal);
  const auto commit=std::get<ar::Commit>(ar::inspect(f.program,parts[4]).payload);
  const auto false_reject=ar::encode(f.account,f.program,4,ar::Reject{commit.input_ordinal,commit.input_sha256,2,0,ar::RejectReason::weight_mismatch});
  parts[4]=false_reject.bytes();put(path,join(parts,parts.size())+"C");put(f.sink,sink+"C");
  const auto successful_reject=contents(path);refused([&]{auto s=f.recover();});assert(contents(path)==successful_reject && contents(f.sink)==sink+"C");
}
// A later pending Input or Reject also proves the previous output was delivered.
// Removing that actual epoch must fail before a torn WAL/sink can be repaired.
void final_sink_floor() {
  for(bool reject:{false,true}) {
    Fixture f;const std::array<Cell,2> row{Cell{},number(1)};std::array edit{runtime::sql_rows::SourceReplacement{TableId{0},row,0,1}};
    {auto s=f.create();assert(!step(s,edit).rejected);edit[0].before=9;edit[0].after=0;s.log({2,edit,{},{}});if(reject)assert(s.decide().rejected);}
    const auto path=generation_file(f,1),wal=contents(path),sink=contents(f.sink);const auto header=frames(sink)[0];
    put(path,wal+"C");put(f.sink,header+"C");refused([&]{auto s=f.recover();});assert(contents(path)==wal+"C" && contents(f.sink)==header+"C");
    put(path,wal);put(f.sink,sink);{auto s=f.recover();state(s,2,reject?2:1,1,1);if(!reject)assert(s.decide().rejected);}
  }
}
// Recovery owns only one final missing output. A later Input proves prior D=C;
// missing earlier output or a sink ahead of genuine WAL replay is rejected.
void sink_floor_and_repair() {
  Fixture f;const std::array<Cell,2> row{Cell{},number(2)};std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,1}};
  {auto s=f.create();assert(!step(s,edits).rejected);edits[0].before=1;edits[0].after=2;assert(!step(s,edits).rejected);}
  const auto wp=generation_file(f,1),full_wal=contents(wp),full_sink=contents(f.sink);const auto sink=frames(full_sink),wal=frames(full_wal);
  put(f.sink,join(sink,2));{auto s=f.recover();state(s,2,2,2,1);assert(s.output() && s.deliver());}assert(contents(f.sink)==full_sink);
  put(f.sink,sink[0]);put(wp,full_wal+"C");const auto bad=contents(wp);refused([&]{auto s=f.recover();});assert(contents(wp)==bad && contents(f.sink)==sink[0]);
  put(wp,join(wal,3));put(f.sink,full_sink);refused([&]{auto s=f.recover();});assert(contents(f.sink)==full_sink);
  put(wp,full_wal+"C");put(f.sink,full_sink+"C");{auto s=f.recover();state(s,2,2,2,2);}assert(contents(wp)==full_wal && contents(f.sink)==full_sink);
  // A checksum-valid false output identity must fail before either torn suffix
  // is truncated, even though transport parsing alone accepts the Commit.
  auto false_wal=wal;false_wal[2][253]=false_wal[2][253]=='a'?'b':'a';reseal(false_wal[2]);
  put(wp,join(false_wal,false_wal.size())+"C");put(f.sink,full_sink+"C");const auto before_wal=contents(wp),before_sink=contents(f.sink);
  refused([&]{auto s=f.recover();});assert(contents(wp)==before_wal && contents(f.sink)==before_sink);
  put(wp,full_wal+"C");put(f.sink,full_sink+"C");f.limits.repair_torn_tail=false;
  refused([&]{auto s=f.recover();});assert(contents(wp)==full_wal+"C" && contents(f.sink)==full_sink+"C");
}
// Cold-only codec/command bounds are cumulative; original normal policies can
// remain disabled. Root rotation never resets the durable history cap.
void cold_limits_and_history() {
  Fixture f;f.normal.group_work_limit.reset();f.normal.source.native.work_limit.reset();const std::array<Cell,2> row{Cell{},number(1)};
  const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,1}};
  {auto s=f.create();assert(!step(s,edits).rejected);}
  std::uint64_t work=0;{auto s=f.recover();work=s.replay_statistics().codec_work;assert(s.replay_statistics().commands==1 && !s.descriptor().options().group_work_limit && !s.descriptor().options().source.native.work_limit);}
  f.limits.replay_commands=1;f.limits.replay_codec_work=work;{auto s=f.recover();assert(s.replay_statistics().codec_work==work);}
  --f.limits.replay_codec_work;refused([&]{auto s=f.recover();});++f.limits.replay_codec_work;f.limits.replay_commands=0;refused([&]{auto s=f.recover();});
  f.limits.replay_commands=1;f.limits.history_generations=2;
  {auto s=f.recover();assert(s.checkpoint().generation==2);refused([&]{static_cast<void>(s.checkpoint());});assert(!s.requires_reopen());}
  {auto s=f.recover();refused([&]{static_cast<void>(s.checkpoint());});}
}
// Detection of a changed actual selected root invalidates the old owner even
// if the failure occurs before any new root selection was attempted.
void stale_root() {
  Fixture f;auto s=f.create();const auto prior=contents(f.root);put(f.root,prior+"x");refused([&]{static_cast<void>(s.checkpoint());});
  assert(s.requires_reopen());refused([&]{static_cast<void>(s.state());});refused([&]{s.log({1,{},{},{}});});
}
// Complete original filtered/unused rows survive an actual selected checkpoint;
// global-empty output is reconstructed independently of the surviving source bag.
void complete_source() {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64,true}}},{"unused",{{"z",ScalarType::string,true}}}}};
  Fixture f(false,catalog,"SELECT COUNT(*),SUM(x) FROM r WHERE x>0");
  const std::array<Cell,1> filtered{number(-2)},unused{text("retained")};
  const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},filtered,0,3},runtime::sql_rows::SourceReplacement{TableId{1},unused,0,2}};
  {auto s=f.create();assert(s.snapshot().groups.size()==1);assert(!step(s,edits).rejected);assert(s.checkpoint().generation==2);}
  {auto s=f.recover();state(s,1,1,1,1);assert(s.source_weight(TableId{0},filtered)==3 && s.source_weight(TableId{1},unused)==2);
    const auto groups=s.snapshot();assert(groups.groups.size()==1 && groups.groups[0].values.view()[0]==number(0) && !groups.groups[0].values.view()[1]);}
  for(const auto sql:{"SELECT COUNT(*)","SELECT COUNT(*) WHERE FALSE"}) {
    Fixture singleton(false,Catalog{1,{}},sql);
    {auto s=singleton.create();assert(!step(s,{}).rejected);assert(s.checkpoint().generation==2);}
    {auto s=singleton.recover();state(s,1,1,1,1);const auto groups=s.snapshot();assert(groups.groups.size()==1);
      assert(groups.groups[0].values.view()[0]==number(sql==std::string_view{"SELECT COUNT(*)"}?1:0));}
  }
}
// A fresh receiver owns all retained native/schema/output state. Exact observed
// factory peak succeeds; one byte less refuses before either torn suffix repair.
void receiving_account() {
  for(bool pending:{false,true}) {
    Fixture f;const std::array<Cell,2> row{Cell{},number(6)};std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,2}};
    {auto s=f.create();assert(!step(s,edits).rejected);if(pending) {edits[0].before=2;edits[0].after=3;s.log({2,edits,ar::SourcePosition{"feed",10},ar::ReaderPosition{10,1}});}}
    const auto wal=generation_file(f,1),before_wal=contents(wal),before_sink=contents(f.sink);
    const auto open=[&](const resource::MemoryAccount& receiver) {return ar::Session::recover_into(receiver,{f.root,f.sink},f.identity.query_id,f.limits);};
    std::uint64_t peak=0;
    {const auto receiver=resource::MemoryAccount::create(128ULL*1024*1024);const auto baseline=receiver.statistics().current;
      {auto s=open(receiver);assert(s.descriptor().program().account().statistics().owner==receiver.statistics().owner);peak=receiver.statistics().peak_requested_bytes;
        const auto groups=s.snapshot();assert(groups.groups[0].key.account().statistics().owner==receiver.statistics().owner && groups.groups[0].values.account().statistics().owner==receiver.statistics().owner);}
      assert(receiver.statistics().current==baseline);}
    {const auto receiver=resource::MemoryAccount::create(peak);{auto s=open(receiver);assert(s.state().pending==pending);}assert(receiver.statistics().current.allocations==1);}
    put(wal,before_wal+"C");put(f.sink,before_sink+"C");
    {const auto receiver=resource::MemoryAccount::create(peak-1);refused([&]{auto s=open(receiver);});assert(receiver.statistics().current.allocations==1);}
    assert(contents(wal)==before_wal+"C" && contents(f.sink)==before_sink+"C");
    {const auto receiver=resource::MemoryAccount::create(peak);auto s=open(receiver);state(s,pending?2:1,1,1,1);}
    assert(contents(wal)==before_wal && contents(f.sink)==before_sink);
  }
}
// Initial candidates are never auto-cleaned or overwritten. A failed create
// can retain its own earlier unselected files but must select no new root.
void initial_collisions() {
  for(const auto suffix:{".plan",".ckpt",".wal"}) {
    Fixture f;const auto path=generation_file(f,1,suffix);put(path,"preexisting");
    refused([&]{auto s=f.create();});assert(contents(path)=="preexisting" && !std::filesystem::exists(f.root));
  }
}
// Host binder payloads are cold caller DTOs. Session must add no extra copies:
// create ignores them; recover has exactly direct rebind's transient delta.
void host_options() {
  Fixture f;ar::SessionLimits empty,populated;
  populated.admission.binding.source.binding.parameters.push_back(Column{std::string(512,'p'),ScalarType::string,true});
  populated.admission.binding.source.parameters.emplace_back(Value{std::string(1024,'v')});
  std::string descriptor;{auto s=f.create();descriptor=s.descriptor().bytes();}
  const auto create_calls=[&](const ar::SessionLimits& options) {
    Directory directory;const auto root=directory.file("root"),sink=directory.file("sink");
    const auto receiver=resource::MemoryAccount::create(128ULL*1024*1024);s04_alloc::Scope count;
    const auto session=ar::Session::create_into(receiver,{root,sink},f.identity,f.program,f.tree,f.physical,f.normal,options);
    return s04_alloc::calls;
  };
  const auto rebind_calls=[&](const ar::SessionLimits& options) {
    const auto receiver=resource::MemoryAccount::create(128ULL*1024*1024);s04_alloc::Scope count;
    const auto admitted=ar::rebind_into(receiver,descriptor,options.admission);return s04_alloc::calls;
  };
  const auto recover_calls=[&](const ar::SessionLimits& options) {
    const auto receiver=resource::MemoryAccount::create(128ULL*1024*1024);s04_alloc::Scope count;
    const auto session=ar::Session::recover_into(receiver,{f.root,f.sink},f.identity.query_id,options);return s04_alloc::calls;
  };
  // Warm both option profiles and all three genuine factories before observing.
  for(const auto* options:{&empty,&populated}) {static_cast<void>(create_calls(*options));static_cast<void>(rebind_calls(*options));static_cast<void>(recover_calls(*options));}
  const auto ce=create_calls(empty),cp=create_calls(populated),be=rebind_calls(empty),bp=rebind_calls(populated),re=recover_calls(empty),rp=recover_calls(populated);
  std::cout<<"R2 host-option new attempts: create="<<ce<<'/'<<cp<<", direct-rebind="<<be<<'/'<<bp<<", recover="<<re<<'/'<<rp<<'\n'<<std::flush;
  assert(cp==ce && bp>=be && rp>=re && rp-re==bp-be);
  for(bool recover:{false,true}) {
    Directory directory;const auto root=directory.file("root"),sink=directory.file("sink");const auto receiver=resource::MemoryAccount::create(128ULL*1024*1024);
    if(recover) {auto prior=ar::Session::create_into(receiver,{root,sink},f.identity,f.program,f.tree,f.physical,f.normal,empty);}
    std::optional<ar::Session> session;
    {
      auto caller=populated;
      if(recover)session.emplace(ar::Session::recover_into(receiver,{root,sink},f.identity.query_id,caller));
      else session.emplace(ar::Session::create_into(receiver,{root,sink},f.identity,f.program,f.tree,f.physical,f.normal,caller));
      caller.admission={};caller.wal.operations=0;caller.wal.scan.frame.record.bytes=0;caller.sink.scan.frame.record.bytes=0;
      caller.checkpoint.source_bytes=0;caller.capture.rows=0;caller.history_generations=0;
    }
    const std::array<Cell,2> row{Cell{},number(1)};const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,1}};
    session->log({1,edits,ar::SourcePosition{"feed",10},ar::ReaderPosition{10,1}});assert(!session->decide().rejected && session->deliver());
    assert(session->checkpoint().generation==2);state(*session,1,1,1,1);
  }
}
} // namespace
int main() {
  for(bool indexed:{false,true}) { lifecycle(indexed); varying_integer_recovery(indexed); }
  semantic_rejections();pending_and_progress();semantic_corruption();sink_floor_and_repair();final_sink_floor();cold_limits_and_history();stale_root();complete_source();receiving_account();initial_collisions();host_options();
  std::cout<<"R2 session actual W/I/C/D, semantic/native replay, sink floor, root rotation and limits passed\n";
}
