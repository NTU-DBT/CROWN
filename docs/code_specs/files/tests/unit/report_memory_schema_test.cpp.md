# `tests/unit/report_memory_schema_test.cpp` — block usage map

[Source](../../../../../tests/unit/report_memory_schema_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `60645445d901426be61174816bc9a1965b6887d3ccfdf2228468ce9a5f03f968`. 40 lines partitioned into 4 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/unit/report_memory_schema_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 12–28](../../../../../tests/unit/report_memory_schema_test.cpp#L12) | Callable definition: void write_case(const std::filesystem::path& directory,std::string_view name,std::uint64_t limit) | calls runtime::QuerySession::create_typed, planner::lower_tree, report_metadata, plan · [reviewed contract](#b0002) |
| [B0003 · 29–29](../../../../../tests/unit/report_memory_schema_test.cpp#L29) | Closes surrounding scope/type. |  · [reviewed contract](#b0003) |
| [B0004 · 30–40](../../../../../tests/unit/report_memory_schema_test.cpp#L30) | Callable definition: int main(int argc,char** argv) | calls std::runtime_error, std::filesystem::create_directories, write_case, max; returns 0; 1 · [reviewed contract](#b0004) |

## B0001

[Lines 1–11](../../../../../tests/unit/report_memory_schema_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:e6b52f22ddaa2600816bb8aafb33221133571b4a620bc238f5f55b9c18acbfd1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare report_memory_schema_test.cpp: include "crown/api/error.hpp", "crown/io/explain.hpp", "crown/planner/lower.hpp", &lt;filesystem&gt;, &lt;fstream&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/report_memory_schema_test.cpp](../../../../../tests/unit/report_memory_schema_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–28](../../../../../tests/unit/report_memory_schema_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void write_case(const std::filesystem::path& directory,std::string_view name,std::uint64_t limit) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0}}}},{{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  Database database;database.tables={Relation{Row{std::int64_t{7}}}};
  runtime::SessionOptions options;
  options.delta.mode=runtime::DeltaMode::maintenance;
  options.delta.physical.support.memory_limit_bytes=limit;
  options.delta.physical.support.observation.mode=runtime::ObservationMode::counters;
  auto session=runtime::QuerySession::create_typed(planner::lower_tree(catalog,query,tree),database,{},options);
  if(session->report_metadata().plan().account().statistics().limit_bytes!=limit)
    throw std::runtime_error("reported input limit differs from the actual query account");
  const auto report=observability::PlanExplanation::capture(*session);
  std::ofstream output(directory/(std::string(name)+".json"),std::ios::binary);
  output.exceptions(std::ios::badbit|std::ios::failbit);
  output<<io::write_explain_json(report)<<'\n';
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a session with a configured account limit and write its captured report as JSON. |
| inputs / outputs | Receives output directory/name/limit, creates a one-table session, and checks the live account limit before report capture. It then captures PlanExplanation and writes JSON; it does not parse output or inspect an account_limit field. |
| invariants | The live query account limit equals the configured SessionOptions limit before capture; JSON serialization and file writing are exercised, but the emitted memory field/schema is not asserted. |
| ownership | The session, captured explanation and serialized JSON are local; the helper returns no object. The output file retains the serialized values after these locals are destroyed. |
| failure | Session/account setup mismatch throws runtime_error; capture or file-stream failures propagate. No report-schema mismatch is checked. |
| cost | One session creation and account-limit check, one report capture, one JSON serialization, and one file write. |
| Design | [tests/unit/report_memory_schema_test.cpp](../../../../../tests/unit/report_memory_schema_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp) |

## B0003

[Lines 29–29](../../../../../tests/unit/report_memory_schema_test.cpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L29:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in report_memory_schema_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/report_memory_schema_test.cpp](../../../../../tests/unit/report_memory_schema_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 30–40](../../../../../tests/unit/report_memory_schema_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
  try {
    if(argc!=2)throw std::runtime_error("usage: report-memory-schema OUTPUT_DIRECTORY");
    const std::filesystem::path directory=argv[1];std::filesystem::create_directories(directory);
    write_case(directory,"default",crown::runtime::SupportOptions{}.memory_limit_bytes);
    write_case(directory,"limited",1024ULL*1024+123);
    write_case(directory,"maximum",std::numeric_limits<std::uint64_t>::max());
    std::cout<<"Actual query account limits and memory-option report fixtures passed\n";
    return 0;
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate schema cases for default, small finite, and maximal account limits. |
| inputs / outputs | Requires an output-directory argument, creates the directory, and calls write_case three times. |
| invariants | The cases differ only in explicit memory limit; no allocation-size claim follows from the serialized field. |
| ownership | Filesystem paths and sessions are local to main/write_case. |
| failure | Missing argument, directory error, or failed assertion returns a nonzero test result. |
| cost | Three report/session/write cases. |
| Design | [tests/unit/report_memory_schema_test.cpp](../../../../../tests/unit/report_memory_schema_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp) |
