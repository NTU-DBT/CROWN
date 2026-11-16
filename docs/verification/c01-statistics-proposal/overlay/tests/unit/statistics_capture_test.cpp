#include "crown/runtime/statistics.hpp"
#include "crown/api/error.hpp"
#include <map>
#include <stdexcept>
#include <iostream>
using namespace crown;
using namespace crown::storage;
namespace stats=crown::runtime::statistics;
void check(bool b){if(!b)throw std::runtime_error("C01 proposal assertion failed");}
template<class F> void error(F f){try{f();}catch(const Error&){return;}throw std::runtime_error("expected native error");}
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
  std::cout<<"14 C01 proposal test groups passed\n";
}
