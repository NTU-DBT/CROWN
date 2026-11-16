#include "crown/runtime/statistics.hpp"
#include "crown/api/error.hpp"
#include "crown/storage/accounted_projection.hpp"
#include "crown/storage/accounted_table.hpp"
#include <array>
#include <map>
#include <stdexcept>
#include <iostream>
using namespace crown;
using namespace crown::storage;
namespace stats=crown::runtime::statistics;
void check(bool b){if(!b)throw std::runtime_error("C01 proposal assertion failed");}
template<class F> void error(F f){try{f();}catch(const Error&){return;}throw std::runtime_error("expected native error");}

// Standalone native captures must bind the supplied DTO to the actual index,
// including equal descriptors recreated across the legacy/native token boundary.
void accounted_index_metadata(bool indexed) {
  const auto account=resource::MemoryAccount::create(64*1024*1024);
  const LayoutContext context{17,std::string(4096,'b')};
  TupleLayout layout{LayoutId{20},{{ScalarType::int64},{ScalarType::int64}},context};
  TupleLayout key{LayoutId{21},{{ScalarType::int64}},context};
  TupleLayout pair{LayoutId{22},{{ScalarType::int64},{ScalarType::int64}},context};
  const auto native_layout=AccountedLayout::freeze(account,layout);
  const auto native_key=AccountedLayout::freeze(account,key);
  const auto native_pair=AccountedLayout::freeze(account,pair);
  auto table=indexed?AccountedStorageTable{RelationId{20},native_layout,
      IndexedLimits{32,8,64,128,256,1024,64,64,128}}:
      AccountedStorageTable{RelationId{20},native_layout};
  constexpr IndexWork generous{1000000,1000000,1000000,1000000,1000000};
  auto build=AccountedIndexWork::create(account,generous);
  const std::array first{FieldId{0}};
  const std::array both{FieldId{0},FieldId{1}};
  const auto id=table.add_index(AccountedProjection::freeze(native_layout,native_key,first),build.get());
  const auto pair_id=table.add_index(AccountedProjection::freeze(native_layout,native_pair,both),build.get());
  static_cast<void>(table.insert(native_layout.tuple(Row{std::int64_t{1},std::int64_t{7}}),build.get()));
  static_cast<void>(table.insert(native_layout.tuple(Row{std::int64_t{2},std::int64_t{7}}),build.get()));
  const auto revision=table.revision();
  const auto capture=[&](IndexId index,const Projection& metadata,stats::Budget& budget,
      std::optional<IndexWork> limit={}) {
    auto work=AccountedIndexWork::create(account,limit.value_or(generous));
    return stats::index(table,index,metadata,budget,work.get());
  };
  const auto reject=[&](IndexId index,const Projection& metadata) {
    stats::Budget budget;bool rejected=false;
    try{static_cast<void>(capture(index,metadata,budget));}
    catch(const Error& failure){rejected=failure.code()=="invalid_statistics_request";}
    if(!rejected)throw std::runtime_error("accounted index accepted mismatched metadata");
    check(table.size()==2 && table.revision()==revision);
  };

  // Actual field0 keys are 1/2; labeling them field1 would falsely claim NDV 2
  // for a column whose only value is 7. Equal width cannot establish identity.
  reject(id,Projection{layout,key,{FieldId{1}}});
  TupleLayout foreign{LayoutId{99},{{ScalarType::int64},{ScalarType::int64}},context};
  reject(id,Projection{foreign,key,{FieldId{0}}});
  TupleLayout changed_source{LayoutId{20},{{ScalarType::int64,{},VariableId{8}},{ScalarType::int64}},context};
  reject(id,Projection{changed_source,key,{FieldId{0}}});
  TupleLayout changed_target{LayoutId{21},{{ScalarType::int64,{},VariableId{8}}},context};
  reject(id,Projection{layout,changed_target,{FieldId{0}}});
  TupleLayout changed_origin{LayoutId{21},{{ScalarType::int64}},context,LayoutOrigin{TableId{3},4}};
  reject(id,Projection{layout,changed_origin,{FieldId{0}}});
  const LayoutContext other_context{17,std::string(4096,'c')};
  TupleLayout other_source{LayoutId{20},{{ScalarType::int64},{ScalarType::int64}},other_context};
  TupleLayout other_target{LayoutId{21},{{ScalarType::int64}},other_context};
  reject(id,Projection{other_source,other_target,{FieldId{0}}});
  reject(pair_id,Projection{layout,pair,{FieldId{1},FieldId{0}}});

  // Legacy layout construction and native freeze intentionally create distinct
  // tokens. Full descriptor equivalence must still admit this correct recipe.
  TupleLayout recreated_layout{LayoutId{20},{{ScalarType::int64},{ScalarType::int64}},context};
  TupleLayout recreated_key{LayoutId{21},{{ScalarType::int64}},context};
  Projection correct{recreated_layout,recreated_key,{FieldId{0}}};
  check(!native_layout.same_token(recreated_layout));
  stats::Budget healthy;const auto exact=capture(id,correct,healthy);
  check(exact.distribution.completion==stats::Completion::exact && exact.distribution.ndv==2 &&
      exact.source_layout.same_token(native_layout) && exact.projection->same_token(table.projection(id,build.get())));
  const std::map<Row,std::uint64_t> expected{{Row{std::int64_t{1}},1},{Row{std::int64_t{2}},1}};
  for(const auto& value:*exact.distribution.heavy_keys)check(expected.at(value.key)==value.count);

  // Metadata comparison shares the finite statistics budget. An exhausted read
  // retains authentic metadata and publishes no prefix exact facts.
  stats::Limits binding_short;binding_short.work=context.binding.size()-1;
  stats::Budget binding_budget{binding_short};
  check(!capture(id,correct,binding_budget).distribution.ndv);
  stats::Limits exact_work;exact_work.work=healthy.usage().work;
  stats::Budget admitted{exact_work};check(capture(id,correct,admitted).distribution.ndv==2);
  --exact_work.work;stats::Budget denied{exact_work};
  check(!capture(id,correct,denied).distribution.ndv);
  stats::Limits exact_bytes;exact_bytes.accounted_bytes=healthy.usage().accounted_bytes;
  stats::Budget bytes_ok{exact_bytes};check(capture(id,correct,bytes_ok).distribution.ndv==2);
  --exact_bytes.accounted_bytes;stats::Budget bytes_short{exact_bytes};
  check(!capture(id,correct,bytes_short).distribution.ndv);
  stats::Limits none;none.work=0;stats::Budget zero{none};
  const auto incomplete=capture(id,Projection{layout,key,{FieldId{1}}},zero);
  check(!incomplete.distribution.ndv && !incomplete.distribution.heavy_keys &&
      incomplete.distribution.histogram.empty() && incomplete.projection->fields()[0]==FieldId{0});

  if(indexed) {
    // The real index definition lookup and scan consume this same grant.
    auto work=AccountedIndexWork::create(account,generous);stats::Budget budget;
    check(stats::index(table,id,correct,budget,work.get()).distribution.ndv==2);
    const auto left=work.get()->remaining();
    IndexWork spent{generous.structural_steps-left.structural_steps,
        generous.scalar_fields-left.scalar_fields,generous.scalar_bytes-left.scalar_bytes,
        generous.pointer_slots-left.pointer_slots,generous.link_actions-left.link_actions};
    stats::Budget tight;check(capture(id,correct,tight,spent).distribution.ndv==2);
    check(spent.structural_steps>0);--spent.structural_steps;stats::Budget short_storage;
    check(!capture(id,correct,short_storage,spent).distribution.ndv);
    auto empty=AccountedIndexWork::create(account,{});bool exhausted=false;
    try{stats::Budget b;static_cast<void>(stats::index(table,id,correct,b,empty.get()));}
    catch(const IndexFailure& failure){exhausted=failure.code()=="storage_work_limit";}
    check(exhausted);
  }
  check(table.size()==2 && table.revision()==revision);table.check_invariants();
}

int main(){
  TupleLayout layout{LayoutId{1},{{ScalarType::int64},{ScalarType::int64}}};
  TupleLayout key_layout{LayoutId{2},{{ScalarType::int64}}};
  TupleLayout empty_layout{LayoutId{3},{}};
  Projection y{layout,key_layout,{FieldId{1}}}, x{layout,key_layout,{FieldId{0}}}, empty{layout,empty_layout,{}};
  ReferenceTable table{RelationId{1},layout};
  const std::vector<Row> rows{{std::int64_t{1},std::int64_t{7}},{std::int64_t{2},std::int64_t{7}},{std::int64_t{3},std::int64_t{8}}};
  for(auto r:rows)static_cast<void>(table.insert(layout.tuple(r)));
  const auto id=table.add_index(y);
  // 1: literal cardinality, projection NDV and exact support-style grouping.
  stats::Budget b; auto cy=stats::projection(table,y,b); auto cx=stats::projection(table,x,b);
  check(cy.cardinality==3 && cy.distribution.ndv==2 && cx.distribution.ndv==3);
  check(cy.distribution.histogram==std::vector<std::pair<std::uint64_t,std::uint64_t>>{{1,1},{2,1}});
  // 2: independent positional reference grouping, without production projection.
  std::map<Row,std::uint64_t> reference;
  for(const auto& r:rows)++reference[Row{r[1]}];
  stats::Budget bi; auto ci=stats::index(table,id,bi);
  check(ci.distribution.ndv==reference.size());
  for(const auto& h:*ci.distribution.heavy_keys)check(reference.at(h.key)==h.count);
  check(ci.distribution.heavy_keys->front().key==Row{std::int64_t{7}});
  // 3: empty projection has one key for nonempty population.
  stats::Budget be; check(stats::projection(table,empty,be).distribution.ndv==1);
  // 4: exact empty population has zero NDV and known empty top-K.
  ReferenceTable blank{RelationId{2},layout}; stats::Budget bb;
  auto cb=stats::projection(blank,empty,bb); check(cb.distribution.ndv==0 && cb.distribution.heavy_keys->empty());
  // 5: row exhaustion after a prefix never publishes NDV/top-K/histogram.
  stats::Limits limited;limited.rows=1;stats::Budget br{limited};auto cr=stats::projection(table,y,br);
  check(cr.distribution.visited==1 && !cr.distribution.ndv && !cr.distribution.heavy_keys && cr.distribution.histogram.empty());
  // 6: exactly consumed work repeats exactly; one less is unknown.
  stats::Limits exact; exact.work=bi.usage().work;stats::Budget bx{exact};check(stats::index(table,id,bx).distribution.ndv==2);
  --exact.work;stats::Budget short_work{exact};check(!stats::index(table,id,short_work).distribution.ndv);
  stats::Limits final_bytes;final_bytes.accounted_bytes=bi.usage().accounted_bytes-1;stats::Budget bf{final_bytes};auto cf=stats::index(table,id,bf);
  check(cf.distribution.visited==2 && !cf.distribution.ndv && !cf.distribution.heavy_keys && cf.distribution.histogram.empty());
  check(bi.usage().max_row_capacity>=1 && bi.usage().max_histogram_capacity>=2 && bi.usage().max_heavy_capacity>=2);
  // 7: shared budget is not renewed per component.
  limited.rows=3;stats::Budget shared{limited};check(stats::projection(table,y,shared).distribution.ndv==2);
  check(!stats::projection(table,x,shared).distribution.ndv);
  // 8: no-op leaves cursor valid; real mutation invalidates before iterator use.
  auto cursor=table.index_keys(id);static_cast<void>(table.insert(layout.tuple(rows[0])));check(cursor.next()->degree==2);
  static_cast<void>(table.insert(layout.tuple({std::int64_t{4},std::int64_t{9}})));error([&]{static_cast<void>(cursor.next());});
  // 9: journal admission rejects cursor reads and captures, even without mutation.
  auto cursor2=table.index_keys(id);{auto journal=table.journal();error([&]{static_cast<void>(cursor2.next());});error([&]{stats::Budget t;static_cast<void>(stats::index(table,id,t));});}
  // 10: owning results survive table clear and preserve their source stamp.
  const auto stamp=ci.stamp;table.clear();check(ci.stamp.revision==stamp.revision && ci.distribution.heavy_keys->front().count==2);
  // 11: key/byte/width limits fail explicitly, keeping cardinality exact.
  for(int kind=0;kind<3;++kind){stats::Limits l;if(kind==0)l.distinct_keys=0;if(kind==1)l.accounted_bytes=0;if(kind==2)l.projection_width=0;stats::Budget z{l};
    ReferenceTable one{RelationId{4},layout};static_cast<void>(one.insert(layout.tuple(rows[0])));auto c=stats::projection(one,y,z);check(c.cardinality==1&&!c.distribution.ndv);}
  // 12: native binary strings including NUL/high bytes and canonical Decimal.
  TupleLayout mixed{LayoutId{5},{{ScalarType::string},{ScalarType::decimal}}};
  Projection identity{mixed,mixed,{FieldId{0},FieldId{1}}}; ReferenceTable strings{RelationId{5},mixed};
  static_cast<void>(strings.insert(mixed.tuple({std::string("a\0z",3),Decimal::parse("1.00")})));
  static_cast<void>(strings.insert(mixed.tuple({std::string("a\0z",3),Decimal::parse("1")})));
  static_cast<void>(strings.insert(mixed.tuple({std::string(1,static_cast<char>(255)),Decimal::parse("1")})));
  stats::Budget bs;auto cs=stats::projection(strings,identity,bs);check(cs.distribution.ndv==2);
  check(cs.distribution.heavy_keys->front().key[0]==Value{std::string("a\0z",3)});
  TupleLayout repeated_layout{LayoutId{7},{{ScalarType::decimal},{ScalarType::string},{ScalarType::decimal}}};
  Projection repeated{mixed,repeated_layout,{FieldId{1},FieldId{0},FieldId{1}}};stats::Budget repeated_budget;
  auto repeated_capture=stats::projection(strings,repeated,repeated_budget);check(repeated_capture.distribution.ndv==2);
  const auto& repeated_key=repeated_capture.distribution.heavy_keys->front().key;
  check(repeated_key[0]==Value{Decimal::parse("1")} && repeated_key[0]==repeated_key[2] && repeated_key[1]==Value{std::string("a\0z",3)});
  // 13: wide native string comparisons consume byte work (not one comparison).
  TupleLayout sl{LayoutId{6},{{ScalarType::string}}};Projection sp{sl,sl,{FieldId{0}}};ReferenceTable st{RelationId{6},sl};
  static_cast<void>(st.insert(sl.tuple({std::string(4096,'x')})));
  static_cast<void>(st.insert(sl.tuple({std::string(4095,'x')+"y"})));
  stats::Limits wl;wl.work=9000;stats::Budget wb{wl};check(!stats::projection(st,sp,wb).distribution.ndv);
  // 14: dropped index / destroyed owner / moved-from cursor all reject safely.
  auto dead=st.index_keys(st.add_index(sp)); ReferenceTable moved=std::move(st);moved.clear();error([&]{static_cast<void>(dead.next());});
  auto drop_id=moved.add_index(sp);auto dropped=moved.index_keys(drop_id);static_cast<void>(moved.drop_index(drop_id));error([&]{static_cast<void>(dropped.next());});
  auto orphan=[](){ReferenceTable t{RelationId{9},TupleLayout{LayoutId{9},{}}};auto p=Projection{t.layout(),t.layout(),{}};return t.index_keys(t.add_index(p));}();error([&]{static_cast<void>(orphan.next());});
  auto original=blank.index_keys(blank.add_index(empty));auto transferred=std::move(original);error([&]{static_cast<void>(original.next());});check(!transferred.next());
  accounted_index_metadata(false);accounted_index_metadata(true);
  std::cout<<"16 C01 proposal test groups passed\n";
}
