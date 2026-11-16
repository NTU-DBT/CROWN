# `tests/unit/sql_aggregate_checkpoint_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4fda848dd0cff176366834b47b2c77c031a97845bc18a9d53e90438f072dbe81`. 166 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 20–20](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L20) | Callable definition: Cell number(std::int64_t value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0002) |
| [B0003 · 21–21](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L21) | Callable definition: Cell text(std::string_view value) | calls ; returns storage::ScalarView{value} · [reviewed contract](#b0003) |
| [B0004 · 22–25](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L22) | Callable definition: frontend::SqlAggregateProgram bind(std::string_view sql,const Catalog& catalog) | calls frontend::bind_sql_aggregate, assert, std::move; guard auto result=frontend::bind_sql_aggregate(sql,catalog);assert(std::holds_alternative&lt;frontend::SqlAg…; returns std::get&lt;frontend::SqlAggregateProgram&gt;(std::move(result)) · [reviewed contract](#b0004) |
| [B0005 · 26–33](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L26) | Callable definition: ar::Admitted admit(const resource::MemoryAccount& account,const frontend::SqlAggregateProgram& program,bool indexed) | calls source_program, contradiction, export_core, planner::minimum_tree; guard const auto core=program.source_program().export_core();const auto chosen=planner::minimum_tree(core…; returns ar::admit_into(account,program,tree,indexed?s04_runtime::options():PhysicalOptions{},options) · [reviewed contract](#b0005) |
| [B0006 · 34–39](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L34) | Callable definition: runtime::sql_aggregate::RebuildLimits limits(bool indexed) | calls ; returns result · [reviewed contract](#b0006) |
| [B0007 · 40–44](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L40) | Callable definition: ar::CheckpointMetadata metadata(const ar::Descriptor& descriptor,std::uint64_t c,std::uint64_t i) | calls fill, sha256; returns value · [reviewed contract](#b0007) |
| [B0008 · 45–47](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L45) | Callable definition: void position(io::AccountedInputProgress& progress,std::string_view name,std::uint64_t offset) | calls prepare, publish · [reviewed contract](#b0008) |
| [B0009 · 48–50](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L48) | Callable definition: Groups groups(const runtime::SqlAggregateRuntime& runtime) | calls snapshot, assert, emplace, export_values; guard Groups values;for(const auto& group:runtime.snapshot().groups)assert(values.emplace(group.key.expor…; returns values; growth emplace; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 51–53](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L51) | Callable definition: template&lt;class Action&gt; void wire_rejected(Action action) | calls deny, action, assert; guard bool rejected=false;{s04_alloc::Scope deny(0);try{action();}catch(const recovery::ImageFailure&){re… · [reviewed contract](#b0010) |
| [B0011 · 54–56](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L54) | Callable definition: template&lt;class Action&gt; void refused(Action action) | calls action, assert; guard bool rejected=false;try{action();}catch(const std::exception&){rejected=true;}assert(rejected); · [reviewed contract](#b0011) |
| [B0012 · 57–66](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L57) | Callable definition: void receiving_caps(const ar::Descriptor& descriptor,std::string_view wire,const ar::CheckpointMetadata& expected,bool indexed) | calls resource::MemoryAccount::create, ar::restore_checkpoint_into, limits, statistics; guard assert(account.statistics().current.allocations==1);} · [reviewed contract](#b0012) |
| [B0013 · 67–110](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L67) | Callable definition: void round_trip(bool indexed) | calls bind, resource::MemoryAccount::create, admit, number; guard auto source=live.runtime.source_snapshot();assert(source.source.rows.size()==9 && groups(live.runti…; growth push_back; 3 loop sites · [reviewed contract](#b0013) |
| [B0014 · 111–122](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L111) | Callable definition: void terminal_and_empty() | calls bind, resource::MemoryAccount::create, admit, progress; guard auto restored=ar::restore_checkpoint_into(account,live.descriptor,zero.bytes(),zero.info().metadata… · [reviewed contract](#b0014) |
| [B0015 · 123–124](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L123) | Explanatory comments or spacing. | source comment (unverified): // Well-typed mutable image rows still require the actual source constraints and · [reviewed contract](#b0015) |
| [B0016 · 125–144](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L125) | Callable definition: void semantic_rows() | calls push_back, bind, resource::MemoryAccount::create, admit; guard assert(failed && receiver.statistics().current.allocations==1 && live.runtime.sequence()==0);receiv…; growth copy_of, push_back; 1 loop sites; source comment (unverified): // Well-typed mutable image rows still require the actual source constraints and · [reviewed contract](#b0016) |
| [B0017 · 145–146](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L145) | Explanatory comments or spacing. | source comment (unverified): // Emit a known complete physical image. Python reconstructs every wire byte · [reviewed contract](#b0017) |
| [B0018 · 147–161](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L147) | Callable definition: void emit(const char* directory) | calls bind, resource::MemoryAccount::create, admit, number; guard std::ofstream out(std::filesystem::path(directory)/name,std::ios::binary);out.write(bytes.data(),st…; 1 loop sites; source comment (unverified): // Emit a known complete physical image. Python reconstructs every wire byte · [reviewed contract](#b0018) |
| [B0019 · 162–162](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L162) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0019) |
| [B0020 · 163–166](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L163) | Callable definition: int main(int argc,char** argv) | calls assert, round_trip, terminal_and_empty, semantic_rows; guard assert(argc==1 \|\| argc==2);for(const bool indexed:{false,true})round_trip(indexed);terminal_and_emp…; 1 loop sites · [reviewed contract](#b0020) |

## B0001

[Lines 1–19](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:d01db6bf568fb5de945c6023794d29cffbcc04299cb68cc29e66c17e8e8345d6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare sql_aggregate_checkpoint_test.cpp: include "crown/recovery/sql_aggregate_checkpoint.hpp", "crown/api/error.hpp", "crown/io/document.hpp", "crown/ir/digest.hpp", "crown/planner/oracle.hpp", "indexed_runtime_fixture.hpp", "index_allocation.hpp", &lt;cassert&gt;, &lt;filesystem&gt;, &lt;fstream&gt;, &lt;iostream&gt;, &lt;map&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 20–20](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cell number(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one typed integer cell for physical fixture rows. |
| inputs / outputs | Signed int64 in; storage ScalarView alternative inside nullable Cell out. |
| invariants | The helper only creates a test input value; declared SQL type checks occur in the actual descriptor codec/factory. |
| ownership | Value owns no row or account; it is copied by fixture row constructors. |
| failure | No local validation beyond C++ conversion. |
| cost | Constant scalar construction. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp) |

## B0003

[Lines 21–21](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Cell text(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a borrowed TEXT view cell for fixture rows. |
| inputs / outputs | string_view in; nullable Cell containing the string view out. |
| invariants | The fixture source string must outlive the owning Tuple copy/encode operation; codec validates UTF8/domain separately. |
| ownership | The Cell borrows caller text until Tuple::copy_of in the fixture copies it. |
| failure | No local validation; actual type/domain errors propagate from binding/codec. |
| cost | Constant view construction; payload copy occurs in explicit Tuple factory. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md) |

## B0004

[Lines 22–25](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::SqlAggregateProgram bind(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind fixture SQL against its declared catalog using the real SQL aggregate binder. |
| inputs / outputs | Original SQL and Catalog in; asserted genuine SqlAggregateProgram out. |
| invariants | A rejected binding aborts the fixture via assert; expected program is produced by production binder rather than a hand-built DTO. |
| ownership | Returns the program’s owning binder result to caller. |
| failure | Unexpected binding result fails the test assertion; binder failures are not caught. |
| cost | Cold fixture parsing/binding workspace; outside checkpoint codec counters. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [include/crown/frontend/sql_aggregate.hpp](../../../../../include/crown/frontend/sql_aggregate.hpp) |

## B0005

[Lines 26–33](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ar::Admitted admit(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a test-only authentic C0 descriptor/runtime with optional indexed physical backend. |
| inputs / outputs | Account, genuine SQL program and backend selector in; Admitted descriptor/runtime out. |
| invariants | Test computes a planner tree for the program, then uses \`admit_into\` and \`capture_changes=true\`; it does not test arbitrary nonminimum-tree proof. |
| ownership | Admitted owners are funded by the supplied Account and stay live with caller. |
| failure | Planner/binder/runtime/account failures fail the test directly. |
| cost | Cold compile/lower/admit in a 64 MiB test account; not production update work. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [docs/sql_aggregate_checkpoint.md §Verification boundaries](../../../../sql_aggregate_checkpoint.md) |

## B0006

[Lines 34–39](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
runtime::sql_aggregate::RebuildLimits limits(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply generous independent cold-build caps to checkpoint restoration tests. |
| inputs / outputs | Indexed/backend selector in; RebuildLimits for source/native/group and optional indexed work out. |
| invariants | These are receiving build grants, not encoded checkpoint policy or image codec limits. |
| ownership | Returns a value policy; no allocation/ownership. |
| failure | No local failure; cap rejection belongs to rebuild. |
| cost | Constant value construction; actual work occurs in factory. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../sql_aggregate_checkpoint.md) |

## B0007

[Lines 40–44](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ar::CheckpointMetadata metadata(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a synthetic checkpoint identity/frontier DTO for fixture operations. |
| inputs / outputs | Descriptor plus C/I in; metadata binding hash, generation and descriptive delivery anchor out. |
| invariants | The anchor bytes/ID are deterministic fixture values, not an actual sink receipt; C and I may diverge and anchor sequence follows C. |
| ownership | Fixed value passed by reference to encode/restore. |
| failure | The codec rejects impossible combinations; helper itself does not verify a sink. |
| cost | Constant fixed metadata setup. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/sql_aggregate_checkpoint.md §State and authority](../../../../sql_aggregate_checkpoint.md) |

## B0008

[Lines 45–47](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void position(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert one named source offset into AccountedInputProgress using its prepare/publish contract. |
| inputs / outputs | Progress, name view and offset in; progress owns one published node on success. |
| invariants | The map’s ordered names make canonical serialization order; this helper does not assert upstream monotonic offset policy. |
| ownership | Name is copied into the map node/account ownership during prepare/publish; caller may release its view after success. |
| failure | Allocation/publish failures fail the test and propagate. |
| cost | One accounted map-node insertion and name copy. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md) |

## B0009

[Lines 48–50](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Groups groups(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize an actual runtime snapshot to an owning map for exact pre/post-rebuild comparison. |
| inputs / outputs | Runtime snapshot in; ordered full-key to aggregate-row map out, asserting unique exported group keys. |
| invariants | Uses the complete nullable Row key, not rendered SQL output names; duplicate keys fail the assertion. |
| ownership | Exported rows and map own fixture values independently of runtime handles. |
| failure | Snapshot/export/allocation errors propagate; duplicate key assertion fails the test. |
| cost | O(number of groups) traversal plus test-only owning exports/map nodes. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/sql_aggregate_checkpoint.md §Verification boundaries](../../../../sql_aggregate_checkpoint.md) |

## B0010

[Lines 51–53](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void wire_rejected(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that a malformed wire operation fails specifically with ImageFailure and makes no covered C++ allocation. |
| inputs / outputs | Action in; runs inside \`s04_alloc::Scope deny(0)\` and asserts ImageFailure plus zero intercepted C++ new calls. |
| invariants | Only the scoped test allocator seam is covered; this does not establish global malloc, syscall or every allocator-family denial. |
| ownership | The temporary scope controls test instrumentation; caller owns action captures. |
| failure | Missing rejection, another exception carrier or intercepted allocation fails the test. |
| cost | One action and counter checks; failure-path parser work until rejection. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/sql_aggregate_checkpoint.md §Verification boundaries](../../../../sql_aggregate_checkpoint.md) |

## B0011

[Lines 54–56](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void refused(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert an operation is rejected by any standard exception in a broad test-only negative control. |
| inputs / outputs | Action in; boolean rejection assertion out. |
| invariants | This helper intentionally does not constrain the exact exception type; use wire_rejected or semantic_rows for exact carriers. |
| ownership | No output ownership; action controls captures. |
| failure | No exception or non-std exception fails/escapes the assertion path. |
| cost | One invocation and exception catch. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/sql_aggregate_checkpoint.md §Verification boundaries](../../../../sql_aggregate_checkpoint.md) |

## B0012

[Lines 57–66](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void receiving_caps(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure one receiver-account restoration peak and test exact-grant success plus one-byte-under rejection. |
| inputs / outputs | Descriptor, wire, expected metadata and indexed flag in; asserts exact MemoryAccount requested-byte grant behavior. |
| invariants | Peak/current refer to account-requested bytes; C++ global allocations are separate. One-under must fail with resource limit and leave only account controller allocation. |
| ownership | Each local receiving account owns successful restored runtime until scope exit; failed partial owners unwind before current-count assertion. |
| failure | Exact grant must succeed; one-byte-under must raise MemoryFailure(limit); any mismatch fails the test. |
| cost | Three cold restores at a baseline-measured exact grant and one-byte-under; traverses full image/factory each time. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../sql_aggregate_checkpoint.md) |

## B0013

[Lines 67–110](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void round_trip(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise complete encode, inspect, restore and next-epoch equivalence for one physical backend. |
| inputs / outputs | Indexed selector chooses backend; fixture binds nullable join/group/aggregate SQL, inserts matched, null-key, filtered and unused rows, then encodes/restores. |
| invariants | Checks complete physical rows (including filtered and unused), nullable cells/keys, weights, C/I divergence, reader and progress; row permutation is canonical; duplicate row identity rejects; wrong expected metadata and exact/one-under work/shape caps reject; restored next diff/groups equal source runtime. |
| ownership | Sender, Checkpoint frame and receiver have distinct lifetimes/accounts; restored data does not depend on input string after decoding. |
| failure | Asserts specific wire/account errors; genuine factories validate output state and both owner invariant checks run. |
| cost | Repeated bounded cold encode/inspect/restore against both indexed and ordered backend; scratch/sender/receiver live according to lexical scopes. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [src/recovery/sql_aggregate_checkpoint.cpp](../../../../../src/recovery/sql_aggregate_checkpoint.cpp), [docs/sql_aggregate_checkpoint.md §Verification boundaries](../../../../sql_aggregate_checkpoint.md) |

## B0014

[Lines 111–122](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void terminal_and_empty(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cover C0/static-empty state, split command progress, terminal C and cold-build grant failure. |
| inputs / outputs | COUNT(*) descriptor, C0 empty physical image and C=UINT64_MAX image in; restored runtime/frontiers out. |
| invariants | Empty physical rows preserve authentic static root multiplicity one; UINT64_MAX is terminal without wrap; next sequence-zero prepare rejects; zero group-work cap fails and leaves account current unchanged. |
| ownership | One account holds producer and restored test state until function exit; wire is borrowed only during each restore. |
| failure | Uses broad rejection for terminal-next and insufficient build grant; actual account-current assertion detects retained partial receiver state. |
| cost | Two successful cold restorations (C0 and UINT64_MAX), plus a third restore rejected by zero group-work. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/sql_aggregate_checkpoint.md §Verification boundaries](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Limits and cost](../../../../sql_aggregate_checkpoint.md) |

## B0015

[Lines 123–124](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L123); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L123-L124:sha256:4147cc5a22034a576cc40e247eb9fa20b46bdaba1dc841cbcd69f7c662cde3b9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Well-typed mutable image rows still require the actual source constraints and aggregate arithmetic. Rejection leaves the fresh receiving owner unpublished. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 125–144](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void semantic_rows(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove an editable but well-typed complete image is revalidated by the genuine cold source/group factory. |
| inputs / outputs | Runs count-overflow, duplicate-unique-weight and missing-FK cases; encodes each public SourceSnapshot then restores into a fresh receiver. |
| invariants | Requires exact actual error codes (\`aggregate_overflow\`, \`unique_violation\`, \`foreign_key_violation\`); failed receiver publishes no runtime and returns to controller-only requested allocations. |
| ownership | Each producer and receiver is separately account-owned; failed restore’s partial temporaries unwind while the source runtime remains at sequence zero. |
| failure | Exact production Error codes are checked; any missing/translated/wrong rejection fails. |
| cost | Three small cold encodes and rebuild validations; no synthetic native-state mirror. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/sql_aggregate_checkpoint.md §State and authority](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Verification boundaries](../../../../sql_aggregate_checkpoint.md) |

## B0017

[Lines 145–146](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L145); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L145-L146:sha256:95642037b014ec7298f85b09b0bb6f9ee92662e1c04456e0f0835589c9da10fc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Emit a known complete physical image. Python reconstructs every wire byte independently using only this declared fixture and SHA256(descriptor bytes). |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 147–161](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void emit(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write a deterministic complete descriptor/checkpoint fixture for independent Python wire reconstruction. |
| inputs / outputs | Output directory in; constructs real typed physical rows/progress/reader, encodes image, writes descriptor.bin and checkpoint.bin bytes. |
| invariants | Fixture values specify typed scalars and canonical row ordering independently in Python; filesystem output is temporary test transport, not sink durability. |
| ownership | Runtime/image own account bytes while file writes borrow them; files are scoped by Python TemporaryDirectory. |
| failure | Directory/file open/write/assert errors fail the native fixture; no catch or rollback contract is claimed. |
| cost | Cold bind/admit/one batch/encode and two sequential binary file writes. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [tests/integration/sql_aggregate_checkpoint_wire.py](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py), [docs/sql_aggregate_checkpoint.md §Verification boundaries](../../../../sql_aggregate_checkpoint.md) |

## B0019

[Lines 162–162](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L162); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L162-L162:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_checkpoint_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 163–166](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run both backend checkpoint controls and optional independent-wire fixture emission. |
| inputs / outputs | No arguments or one output-directory argument; invokes round_trip for ordered/indexed, terminal_and_empty, semantic_rows and optional emit. |
| invariants | Native assertions must remain active; emitted data is for byte-for-byte independent Python verification. |
| ownership | Local test objects release at function exit; no production sink/account authority escapes. |
| failure | Any assertion, factory, filesystem or output failure yields nonzero process result. |
| cost | Executes finite unit cases; integration oracle is separately registered. |
| Design | [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/sql_aggregate_checkpoint.md §Verification boundaries](../../../../sql_aggregate_checkpoint.md) |
