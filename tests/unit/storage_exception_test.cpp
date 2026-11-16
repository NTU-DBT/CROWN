#include "crown/storage/reference.hpp"
#include "crown/api/error.hpp"
#include <cstdlib>
#include <functional>
#include <iostream>
#include <new>
#include <stdexcept>

// This test binary fails one intercepted scalar/array global-new attempt.
// Aligned/nothrow overloads are not independently replaced; direct libc and
// exception-ABI allocation are outside the count.
namespace {
thread_local std::ptrdiff_t fail_after=-1;
[[gnu::noinline]] void* allocate(std::size_t bytes) {
  if (fail_after>=0 && fail_after--==0) throw std::bad_alloc{};
  if (auto* result=std::malloc(bytes==0 ? 1 : bytes)) return result;
  throw std::bad_alloc{};
}
}
void* operator new(std::size_t bytes) { return allocate(bytes); }
void* operator new[](std::size_t bytes) { return allocate(bytes); }
void operator delete(void* pointer) noexcept { std::free(pointer); }
void operator delete[](void* pointer) noexcept { std::free(pointer); }
void operator delete(void* pointer,std::size_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer,std::size_t) noexcept { std::free(pointer); }

namespace {
using namespace crown;
using namespace crown::storage;
void check(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); }
Value n(std::int64_t value) { return value; }
Value text(std::string value) { return value; }
TupleLayout source() { return {LayoutId{1},{{ScalarType::int64},{ScalarType::string},{ScalarType::int64}}}; }
void initialize(ReferenceTable& table,const TupleLayout& layout) {
  for (const auto& fields : std::vector<std::vector<FieldId>>{{{0}},{{1},{2}}, {}})
    static_cast<void>(table.add_index({layout,projected_layout(LayoutId{10+table.indices().size()},layout,fields),fields}));
  for (std::int64_t i=0;i<12;++i) static_cast<void>(table.insert(layout.tuple({n(i%3),text(std::string(180,'a')+std::to_string(i)),n(i)})));
}
void expect_rows(const ReferenceTable& table,const std::vector<Tuple>& before) {
  const auto after=table.snapshot(); check(after.size()==before.size(),"allocation failure changed primary size");
  for (std::size_t i=0;i<before.size();++i) check(after[i]==before[i],"allocation failure changed owned tuple values/layouts");
  table.check_invariants();
}
std::size_t insertion_failures() {
  std::size_t failures=0;
  for (std::ptrdiff_t step=0;step<512;++step) {
    const auto layout=source(); ReferenceTable table{RelationId{1},layout}; initialize(table,layout);
    const auto before=table.snapshot(); const auto revision=table.revision(); auto cursor=table.live();
    const auto candidate=layout.tuple({n(1),text(std::string(180,'z')),n(99)});
    bool failed=false; std::optional<InsertResult> result;
    fail_after=step;
    try { result=table.insert(candidate); } catch (const std::bad_alloc&) { failed=true; }
    fail_after=-1;
    if (failed) {
      ++failures; expect_rows(table,before);
      check(table.revision()==revision && !table.find(candidate) && cursor.next().has_value(),"failed insertion published an ID/revision/cursor change");
      const auto retry=table.insert(candidate);
      check(retry.handle.tuple.value==13,"failed insertion consumed a tuple ID");
    } else {
      check(result && result->inserted && table.size()==before.size()+1,"insertion did not eventually commit");
      table.check_invariants(); return failures;
    }
  }
  throw std::runtime_error("insertion fault sweep did not reach success");
}
std::size_t index_failures() {
  std::size_t failures=0;
  for (std::ptrdiff_t step=0;step<512;++step) {
    const auto layout=source(); ReferenceTable table{RelationId{1},layout}; initialize(table,layout);
    const std::vector<FieldId> fields{{1},{0},{1}};
    const Projection projection{layout,projected_layout(LayoutId{99},layout,fields),fields};
    const auto before=table.snapshot(); const auto indices=table.indices(); const auto revision=table.revision(); auto cursor=table.live();
    bool failed=false; std::optional<IndexId> result;
    fail_after=step;
    try { result=table.add_index(projection); } catch (const std::bad_alloc&) { failed=true; }
    fail_after=-1;
    if (failed) {
      ++failures; expect_rows(table,before);
      check(table.indices()==indices && table.revision()==revision && cursor.next().has_value(),"failed index build published a partial definition/bucket");
      check(table.add_index(projection).value==4,"failed index build consumed an index ID");
    } else {
      check(result && result->value==4,"index build did not eventually commit"); table.check_invariants(); return failures;
    }
  }
  throw std::runtime_error("index fault sweep did not reach success");
}
std::size_t deletion_failures() {
  std::size_t failures=0;
  for (std::ptrdiff_t step=0;step<512;++step) {
    const auto layout=source(); ReferenceTable table{RelationId{1},layout}; initialize(table,layout);
    const auto nullary=table.indices().back(); const auto key=table.projection(nullary).target().tuple({});
    const auto before=table.snapshot(); const auto revision=table.revision(); auto cursor=table.live();
    bool failed=false; std::size_t removed=0;
    fail_after=step;
    try { removed=table.erase_key(nullary,key); } catch (const std::bad_alloc&) { failed=true; }
    fail_after=-1;
    if (failed) {
      ++failures; expect_rows(table,before);
      check(table.revision()==revision && cursor.next().has_value(),"failed key deletion partially removed records");
    } else {
      check(removed==before.size() && table.size()==0,"nullary key deletion did not remove all live records");
      for (const auto index : table.indices()) check(table.key_count(index)==0,"key deletion retained an empty bucket");
      table.check_invariants(); return failures;
    }
  }
  throw std::runtime_error("deletion fault sweep did not reach success");
}
std::size_t tuple_assignment_failures() {
  std::size_t failures=0;
  for (std::ptrdiff_t step=0;step<64;++step) {
    const TupleLayout left{LayoutId{1},{{ScalarType::int64},{ScalarType::string}}},right{LayoutId{2},{{ScalarType::string},{ScalarType::int64}}};
    auto target=left.tuple({n(7),text(std::string(180,'a'))}); const auto old=target;
    const auto input=right.tuple({text(std::string(180,'b')),n(9)}); bool failed=false;
    fail_after=step;
    try { target=input; } catch (const std::bad_alloc&) { failed=true; }
    fail_after=-1;
    if (failed) { ++failures; check(target==old,"failed tuple copy assignment broke validated layout/value identity"); }
    else { check(target==input,"tuple copy assignment did not eventually commit"); return failures; }
  }
  throw std::runtime_error("tuple assignment fault sweep did not reach success");
}
}  // namespace
int main() {
  try {
    const auto insert=insertion_failures(),index=index_failures(),erase=deletion_failures(),assign=tuple_assignment_failures();
    check(insert>0 && index>0 && erase>0 && assign>0,"allocation fault sweep did not exercise failure paths");
    std::cout << "allocation rollback points: insert=" << insert << " index=" << index << " erase_key=" << erase << " tuple_assign=" << assign << '\n';
  } catch (const std::exception& failure) { fail_after=-1; std::cerr << failure.what() << '\n'; return 1; }
}
