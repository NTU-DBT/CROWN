# `tests/unit/initialization_scale_test.cpp` — block usage map

[Source](../../../../../tests/unit/initialization_scale_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `9368c20cee9de37fd6d30c8ac34d89f3874f480a0b364189f2d6826278ebdb4f`. 318 lines partitioned into 24 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/unit/initialization_scale_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 14–16](../../../../../tests/unit/initialization_scale_test.cpp#L14) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../tests/unit/initialization_scale_test.cpp#L17) | Explanatory comments or spacing. |  |
| [B0004 · 18–18](../../../../../tests/unit/initialization_scale_test.cpp#L18) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0004) |
| [B0005 · 19–19](../../../../../tests/unit/initialization_scale_test.cpp#L19) | Explanatory comments or spacing. |  |
| [B0006 · 20–43](../../../../../tests/unit/initialization_scale_test.cpp#L20) | Callable definition: PhysicalPlan disconnected_product_plan(std::size_t arity) | calls push_back, std::to_string, std::move, planner::lower_tree; returns planner::lower_tree(catalog, query, tree); growth push_back; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 44–44](../../../../../tests/unit/initialization_scale_test.cpp#L44) | Explanatory comments or spacing. |  |
| [B0008 · 45–53](../../../../../tests/unit/initialization_scale_test.cpp#L45) | Callable definition: Database product_database(std::size_t arity, std::size_t width) | calls resize, insert, n; returns database; growth insert, resize; 2 loop sites · [reviewed contract](#b0008) |
| [B0009 · 54–54](../../../../../tests/unit/initialization_scale_test.cpp#L54) | Explanatory comments or spacing. |  |
| [B0010 · 55–59](../../../../../tests/unit/initialization_scale_test.cpp#L55) | Callable definition: std::size_t relation_rows(const std::vector&lt;Relation&gt;& relations) | calls size; returns result; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 60–60](../../../../../tests/unit/initialization_scale_test.cpp#L60) | Explanatory comments or spacing. |  |
| [B0012 · 61–65](../../../../../tests/unit/initialization_scale_test.cpp#L61) | Callable definition: std::size_t count_keys(const std::vector&lt;std::vector&lt;CanonicalCount&gt;&gt;& counts) | calls size; returns result; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 66–66](../../../../../tests/unit/initialization_scale_test.cpp#L66) | Explanatory comments or spacing. |  |
| [B0014 · 67–142](../../../../../tests/unit/initialization_scale_test.cpp#L67) | Callable definition: void check_canonical_reconciliation(const DeltaRuntime& runtime, const InvariantReport& report, const std::string& method) | calls canonical_state, storage_statistics, check, has_value; guard check(state.live.has_value(), method + ": initialized delta state has no L");; 5 loop sites · [reviewed contract](#b0014) |
| [B0015 · 143–143](../../../../../tests/unit/initialization_scale_test.cpp#L143) | Explanatory comments or spacing. |  |
| [B0016 · 144–196](../../../../../tests/unit/initialization_scale_test.cpp#L144) | Callable definition: std::size_t check_linear_state_and_print(const DeltaRuntime& runtime, std::size_t width, const std::string& method) | calls inspect_invariants, check, valid, check_canonical_reconciliation; guard check(report.complete && report.valid(),; returns total_record_count; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 197–197](../../../../../tests/unit/initialization_scale_test.cpp#L197) | Explanatory comments or spacing. |  |
| [B0018 · 198–201](../../../../../tests/unit/initialization_scale_test.cpp#L198) | Type/record definition: struct RecordCounts |  · [reviewed contract](#b0018) |
| [B0019 · 202–202](../../../../../tests/unit/initialization_scale_test.cpp#L202) | Explanatory comments or spacing. |  |
| [B0020 · 203–234](../../../../../tests/unit/initialization_scale_test.cpp#L203) | Callable definition: RecordCounts compare_initialization_methods_at_scale(std::size_t width) | calls disconnected_product_plan, product_database, DeltaRuntime::initialize, initialization_metrics; guard check(direct_metrics.replay_inputs == 0 && direct_metrics.replay_events == 0 &&; returns {direct_records, replay_records} · [reviewed contract](#b0020) |
| [B0021 · 235–235](../../../../../tests/unit/initialization_scale_test.cpp#L235) | Explanatory comments or spacing. |  |
| [B0022 · 236–300](../../../../../tests/unit/initialization_scale_test.cpp#L236) | Callable definition: void churn_rebuild_separates_live_rows_pins_and_arena_high_water() | calls disconnected_product_plan, product_database, PhysicalRuntime::initialize, sequence; guard check(epoch.input.source.has_value(),; growth insert, push_back; 4 loop sites · [reviewed contract](#b0022) |
| [B0023 · 301–303](../../../../../tests/unit/initialization_scale_test.cpp#L301) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0023) |
| [B0024 · 304–318](../../../../../tests/unit/initialization_scale_test.cpp#L304) | Callable definition: int main() | calls push_back, compare_initialization_methods_at_scale, check, back; guard check(matrix.back().direct &lt;= 8 * matrix\[1\].direct &&; returns 0; 1; growth push_back; 1 loop sites · [reviewed contract](#b0024) |

## B0001

[Lines 1–13](../../../../../tests/unit/initialization_scale_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:fe1a3b3249485a4d23c50fc4fcc64f3e08e6cfbc3bfcf8292cdd15edeb394fcc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare initialization_scale_test.cpp: include "crown/planner/lower.hpp", "crown/runtime/delta.hpp", &lt;cstdint&gt;, &lt;iostream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/initialization_scale_test.cpp](../../../../../tests/unit/initialization_scale_test.cpp), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–16](../../../../../tests/unit/initialization_scale_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the initialization scale test’s local assertion gate. |
| inputs / outputs | A bool and diagnostic string enter; no value is returned. |
| invariants | Only false takes the local failure branch. |
| ownership | The message is borrowed during the call; no runtime state is retained. |
| failure | False throws std::runtime_error with the supplied message. |
| cost | One condition branch; exception construction is on failure. |
| Design | [tests/unit/initialization_scale_test.cpp § L14-L16](../../../../../tests/unit/initialization_scale_test.cpp) |

## B0004

[Lines 18–18](../../../../../tests/unit/initialization_scale_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one signed integer fixture value to Value. |
| inputs / outputs | One std::int64_t enters; one Value is returned. |
| invariants | No additional range or type policy is checked here. |
| ownership | The scalar is returned by value. |
| failure | No test-local failure path is present. |
| cost | One scalar conversion. |
| Design | [tests/unit/initialization_scale_test.cpp § L18-L18](../../../../../tests/unit/initialization_scale_test.cpp) |

## B0006

[Lines 20–43](../../../../../tests/unit/initialization_scale_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan disconnected_product_plan(std::size_t arity)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a disconnected generalized plan with one one-column int64 table and query variable per arity position. |
| inputs / outputs | Arity enters; matching variables, atoms, head fields, catalog tables, child IDs, and native nodes are generated and passed to lower_tree. |
| invariants | The generated variable/table IDs follow the loop index and the generalized root lists every child; no arity precondition is checked locally. |
| ownership | All intermediate containers are local fixture values; the returned PhysicalPlan owns the lowered representation. |
| failure | No test-local error category or recovery is asserted; lowering failures propagate. |
| cost | Construction visits each arity position and invokes lowering once; this is fixture setup cost, not query-runtime complexity. |
| Design | [tests/unit/initialization_scale_test.cpp § L20-L43](../../../../../tests/unit/initialization_scale_test.cpp) |

## B0008

[Lines 45–53](../../../../../tests/unit/initialization_scale_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database product_database(std::size_t arity
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Populate every disconnected product table with the same finite integer range. |
| inputs / outputs | Arity and width enter; returns a Database with arity tables, each receiving values 0 through width-1 as one-column rows. |
| invariants | Each table receives one row per loop index; set insertion semantics apply to the test Relation type. |
| ownership | The returned Database owns the tables and rows. |
| failure | No test-local failure branch is asserted; allocation failures propagate. |
| cost | Attempts arity×width inserts, exactly as the two nested loops specify; no runtime bound is inferred. |
| Design | [tests/unit/initialization_scale_test.cpp § L45-L53](../../../../../tests/unit/initialization_scale_test.cpp) |

## B0010

[Lines 55–59](../../../../../tests/unit/initialization_scale_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t relation_rows(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sum row counts across a vector of Relations for reconciliation assertions. |
| inputs / outputs | A borrowed vector of Relations enters; its summed size is returned as std::size_t. |
| invariants | Only each relation’s size contributes; row contents are not inspected. |
| ownership | The vector and relations are borrowed; only a scalar total is returned. |
| failure | No explicit overflow check or failure policy is present in this helper. |
| cost | One addition per relation entry. |
| Design | [tests/unit/initialization_scale_test.cpp § L55-L59](../../../../../tests/unit/initialization_scale_test.cpp) |

## B0012

[Lines 61–65](../../../../../tests/unit/initialization_scale_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t count_keys(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sum the key counts across canonical derivation-count relations. |
| inputs / outputs | A borrowed vector of CanonicalCount vectors enters; summed relation sizes return as std::size_t. |
| invariants | Only vector lengths contribute; key values and canonical counts are not compared here. |
| ownership | Input is borrowed and result is a scalar. |
| failure | No explicit overflow check or local failure path is present. |
| cost | One addition per relation entry. |
| Design | [tests/unit/initialization_scale_test.cpp § L61-L65](../../../../../tests/unit/initialization_scale_test.cpp) |

## B0014

[Lines 67–142](../../../../../tests/unit/initialization_scale_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_canonical_reconciliation(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare reported initialization counts with the runtime’s exposed canonical and storage snapshots. |
| inputs / outputs | A borrowed DeltaRuntime, InvariantReport, and method label enter; the helper queries canonical_state() and storage_statistics(). |
| invariants | Checks live-state presence; source/support live-records, derivation keys, source rows; native/generalized records, survivors, parent/visible keys, child flags; factor rows; parent/child bucket counts and their row totals. |
| ownership | Runtime/report/method are borrowed; returned state/statistics snapshots are local values. |
| failure | Each mismatch throws via check() as std::runtime_error; no runtime error category is expected. |
| cost | Traverses the canonical support nodes/records and live factor/bucket collections shown in the loops; cost follows those retained fixture records. |
| Design | [tests/unit/initialization_scale_test.cpp § L67-L142](../../../../../tests/unit/initialization_scale_test.cpp) |

## B0016

[Lines 144–196](../../../../../tests/unit/initialization_scale_test.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t check_linear_state_and_print(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect one initialized fixed-query state, reconcile selected record counters, and return the combined retained-record count. |
| inputs / outputs | A borrowed DeltaRuntime, width, and method label enter; report checks and a std::size_t total are returned. |
| invariants | Requires a complete valid invariant report; for its caller’s arity/width checks source rows equal arity×width, derivation/native records do not exceed that input count, the first support node is generalized with one fully populated child-flag record, and the selected five record categories total at most 32×(1+width). |
| ownership | Runtime is borrowed; canonical/storage snapshots and report are local; only the total scalar escapes. |
| failure | Any failed bound or reconciliation uses check() and throws std::runtime_error; this records finite assertions, not a theorem for all queries or widths. |
| cost | Calls inspection and reconciliation, scans report counters/nodes, and prints selected metrics; actual callers use arity 2 and widths 2, 16, and 64. |
| Design | [tests/unit/initialization_scale_test.cpp § L144-L196](../../../../../tests/unit/initialization_scale_test.cpp) |

## B0018

[Lines 198–201](../../../../../tests/unit/initialization_scale_test.cpp#L198); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RecordCounts {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the direct and insertion-replay record totals returned by one scale comparison. |
| inputs / outputs | Two std::size_t data members, direct and replay, are declared; no methods or behavior are defined. |
| invariants | The type itself imposes no relation between the two counts. |
| ownership | It contains scalar counts by value and owns no runtime state. |
| failure | No failure behavior is defined by this aggregate. |
| cost | Fixed two-member record; no dynamic storage is declared. |
| Design | [tests/unit/initialization_scale_test.cpp § L198-L201](../../../../../tests/unit/initialization_scale_test.cpp) |

## B0020

[Lines 203–234](../../../../../tests/unit/initialization_scale_test.cpp#L203); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RecordCounts compare_initialization_methods_at_scale(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare direct and insertion-replay initialization of the same disconnected-product snapshot. |
| inputs / outputs | Width enters; the helper builds an arity-2 plan/database and initializes two DeltaRuntime owners with delta mode, returning their check_linear_state_and_print totals. |
| invariants | Direct replay metrics must all be zero; insertion replay inputs/events/work must be positive. Owners must differ, while canonical states must compare equal. |
| ownership | Each DeltaRuntime owns its initialized state; the plan/database/options are local fixture values. |
| failure | Failed assertions throw through check(); initialization failures propagate. No specific product error code is asserted. |
| cost | Creates two initialized runtimes over two width-sized tables and inspects both; caller uses only the finite widths 2,16,64. |
| Design | [tests/unit/initialization_scale_test.cpp § L203-L234](../../../../../tests/unit/initialization_scale_test.cpp) |

## B0022

[Lines 236–300](../../../../../tests/unit/initialization_scale_test.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void churn_rebuild_separates_live_rows_pins_and_arena_high_water()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise delete/reinsert churn while distinguishing live source rows, retained caller pins, arena slots, and rebuilt-owner storage. |
| inputs / outputs | A fixed arity-2, width-16 database initializes PhysicalRuntime; each source row is erased with its retained Pin saved, then reinserted and a rebuilt runtime is created. |
| invariants | After erase live source records are zero while retained records are positive; after reinsertion live records are 32 and slots exceed live records; clearing pins drops retained records to zero without changing membership or slots. Rebuild changes owner, preserves sequence/canonical state/live count, and has fewer slots than the old owner. |
| ownership | Runtime owns arena state; \`erased_source_pins\` owns retained tuple pins until clear(); rebuilt owns a distinct state after return. |
| failure | Any counter or identity mismatch fails through check() with std::runtime_error; no product failure code is asserted. |
| cost | Initializes one arity-2, width-16 state, performs 32 erases and 32 inserts, reads four storage_statistics snapshots, rebuilds once and compares the two canonical states. These finite operations do not bound arbitrary churn. |
| Design | [tests/unit/initialization_scale_test.cpp § L236-L300](../../../../../tests/unit/initialization_scale_test.cpp) |

## B0023

[Lines 301–303](../../../../../tests/unit/initialization_scale_test.cpp#L301); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L301-L303:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in initialization_scale_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/initialization_scale_test.cpp](../../../../../tests/unit/initialization_scale_test.cpp), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 304–318](../../../../../tests/unit/initialization_scale_test.cpp#L304); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run direct/replay scale comparisons at widths 2, 16, and 64, then the churn/rebuild fixture. |
| inputs / outputs | No inputs enter; success returns 0 and a caught std::exception prints and returns 1. |
| invariants | The final asserted ratio is only that the width-64 direct and replay totals are each no more than eight times their width-16 totals; no other widths are covered by this comparison. |
| ownership | Matrix and runtimes are local to main or each called function. |
| failure | The harness catches std::exception; no product error code is asserted here. |
| cost | Runs three explicit width cases and one fixed churn case; this finite matrix is not a general scaling proof. |
| Design | [tests/unit/initialization_scale_test.cpp § L304-L318](../../../../../tests/unit/initialization_scale_test.cpp) |
