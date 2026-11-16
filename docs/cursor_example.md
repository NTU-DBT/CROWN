# Read one committed result with the installed API

This complete C++23 program builds a checked one-table plan, inserts one row,
reads its committed result, exhausts the cursor and deletes the input. The
returned owning row remains readable after that deletion. It uses no query class.

```cpp
#include <crown/planner/lower.hpp>
#include <crown/planner/oracle.hpp>
#include <crown/runtime/physical.hpp>
#include <crown/storage/tuple_values.hpp>
#include <cstdint>

int main() {
  using namespace crown;
  const Catalog catalog{1, {{"reading", {{"id", ScalarType::int64}}}}};
  const Query query{{{"id", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}}}, {{VariableId{0}, "id"}}, false};
  const auto minimum = planner::minimum_tree(catalog, query);
  if (minimum.status != planner::OracleStatus::proven_minimum || !minimum.tree) return 1;
  const auto plan = planner::lower_tree(catalog, query, *minimum.tree);
  runtime::PhysicalRuntime runtime(plan);
  const Row input{Value{std::int64_t{7}}};
  static_cast<void>(runtime.apply({1, TableId{0}, SetOperation::insert, input}));

  auto cursor = runtime.results();
  auto row = cursor.next();
  if (!row || storage::export_row(row->values()) != input) return 1;
  if (cursor.next() || !runtime.ready()) return 1;
  // On early stop, call cursor.cancel() instead of waiting for exhaustion.

  static_cast<void>(runtime.apply({2, TableId{0}, SetOperation::erase, input}));
  return storage::export_row(row->values()) == input && !runtime.has_answer() ? 0 : 1;
}
```

Save the block as `main.cpp` in a new directory with this `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.25)
project(crown_cursor_example LANGUAGES CXX)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(Crown 0.1 CONFIG REQUIRED)
add_executable(cursor_example main.cpp)
target_link_libraries(cursor_example PRIVATE CROWN::runtime)
```

Configure with `cmake -S . -B build -DCMAKE_PREFIX_PATH=PREFIX`, build with
`cmake --build build`, and run `build/cursor_example`. Success returns zero.

`results()` requires a readable committed runtime and acquires a read lease.
Each `next()` can perform indexed work and allocate its owning output; the example
also explicitly exports a host-side row for comparison. No zero-allocation or
constant wall-time claim follows. A throwing read closes the cursor's lease;
ordinary scope destruction releases it on early exit. Retain an owning tuple if
its values are needed later; a borrowed view alone does not retain that tuple.
See the [full cursor contract](result_cursors.md) and [model/guarantees](guarantees.md).
