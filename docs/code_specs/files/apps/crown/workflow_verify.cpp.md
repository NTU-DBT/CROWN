# `apps/crown/workflow_verify.cpp` — block usage map

[Source](../../../../../apps/crown/workflow_verify.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `2f892894f16d37752ccb40da54265a249c5bdc68756336c544c895ff801bc57d`. 121 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../apps/crown/workflow_verify.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 14–20](../../../../../apps/crown/workflow_verify.cpp#L14) | Type/record definition: struct Budget |  · [reviewed contract](#b0002) |
| [B0003 · 21–24](../../../../../apps/crown/workflow_verify.cpp#L21) | Callable definition: std::uint64_t product(std::uint64_t a,std::uint64_t b,std::uint64_t limit) | calls Error; returns a*b · [reviewed contract](#b0003) |
| [B0004 · 25–29](../../../../../apps/crown/workflow_verify.cpp#L25) | Callable definition: std::uint64_t row_bytes(const Row& row) | calls size; returns bytes; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 30–60](../../../../../apps/crown/workflow_verify.cpp#L30) | Callable definition: Relation oracle(const PhysicalPlan& plan,const Database& physical,Budget& work,std::uint64_t bytes_limit) | calls normalized, resize, size, row_bytes; returns frontend::map_sql_result(normalized,reference::evaluate(normalized.core_catalog,normalized.core,log…; growth insert, resize; 7 loop sites; source comment (unverified): // Relational joins/projection are independent; SQL adapters/mapping are shared. · [reviewed contract](#b0005) |
| [B0006 · 61–65](../../../../../apps/crown/workflow_verify.cpp#L61) | Callable definition: Relation snapshot(runtime::QuerySession& owner) | calls insert, storage::export_row, values, Error; returns rows; growth insert; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 66–66](../../../../../apps/crown/workflow_verify.cpp#L66) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 67–72](../../../../../apps/crown/workflow_verify.cpp#L67) | Callable definition: Signed difference(const Relation& before,const Relation& after) | calls contains, emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0008) |
| [B0009 · 73–73](../../../../../apps/crown/workflow_verify.cpp#L73) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |
| [B0010 · 74–121](../../../../../apps/crown/workflow_verify.cpp#L74) | Callable definition: std::string crown::cli::verify_workflow_trace(const PhysicalPlan& plan,const std::string& path, io::InputOptions input_options,st… | calls normalized, Error, file, read; returns encoded; growth emplace, insert, make_unique, resize; 4 loop sites; source comment (unverified): // Reference acceptance follows the completed native epoch and raw output collection. · [reviewed contract](#b0010) |

## B0001

[Lines 1–13](../../../../../apps/crown/workflow_verify.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using namespace crown;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind verification helper to actual typed native and relational reference APIs. |
| inputs / outputs | Private namespace alias and includes resolve physical/session/scalar/reference types. |
| invariants | Compile-time names do not certify source, structural optimum or native correctness. |
| ownership | No owner introduced. |
| failure | Declaration only. |
| cost | No runtime cost. |
| Design | [apps/crown/workflow_verify.hpp](../../../../../apps/crown/workflow_verify.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0002

[Lines 14–20](../../../../../apps/crown/workflow_verify.cpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Budget
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track the diagnostic reference work estimate. |
| inputs / outputs | charge rejects amount&gt;remaining, otherwise moves amount to consumed. |
| invariants | Tracks named modeled verification actions, not every CPU comparison/allocation or native engine work; remaining+consumed stays original granted total. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | resource_limit before modeled overrun; no automatic native/source rollback. |
| cost | Fixed arithmetic per charge. |
| Design | [apps/crown/workflow_verify.hpp](../../../../../apps/crown/workflow_verify.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0003

[Lines 21–24](../../../../../apps/crown/workflow_verify.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t product(std::uint64_t a,std::uint64_t b,std::uint64_t limit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound multiplicative reference work/byte estimates before multiplication. |
| inputs / outputs | If a nonzero and b&gt;limit/a rejects; else returns exact a*b. |
| invariants | Zero product is safe; callers choose work or estimated bytes domain. Not actual allocator request measurement. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Fixed checked arithmetic. |
| Design | [apps/crown/workflow_verify.hpp](../../../../../apps/crown/workflow_verify.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0004

[Lines 25–29](../../../../../apps/crown/workflow_verify.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t row_bytes(const Row& row)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Estimate ordinary reference row memory. |
| inputs / outputs | Counts128 fixed bytes, Value descriptors and actual string lengths+terminator. |
| invariants | This model excludes full container/capacity/allocator/Decimal/workspace overhead; current private CLI row/input caps keep component arithmetic finite. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | O(row width), no formatting or row copy. |
| Design | [apps/crown/workflow_verify.hpp](../../../../../apps/crown/workflow_verify.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0005

[Lines 30–60](../../../../../apps/crown/workflow_verify.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation oracle(const PhysicalPlan& plan,const Database& physical,Budget& work,std::uint64_t bytes_limit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute complete small SQL-set result with independent relational join evaluation. |
| inputs / outputs | Builds logical relations via validated shared SQL adapters, charges modeled source/adapter/prefix-product/workspace estimates, then reference::evaluate plus shared SQL mapping. |
| invariants | Joins/projection use reference evaluator, not native support/cursors/deltas. Parser/adapters/output mapping are shared, so this is not an independent mature SQL-engine oracle for them. |
| ownership | Returns owning ordinary Relation; logical/reference scratch and physical input remain tool-owned. |
| failure | Estimate/domain/allocation/reference errors fail diagnostic before report; no durable workflow files are involved. |
| cost | Full source/adapter scans, product-size joins/sets and mapped output plus conservative estimates; ordinary state outside native query account. |
| Design | [apps/crown/workflow_verify.hpp](../../../../../apps/crown/workflow_verify.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/cli.md §Limits and verification](../../../../cli.md), [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_support.md](../../../../sql_support.md) |

## B0006

[Lines 61–65](../../../../../apps/crown/workflow_verify.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation snapshot(runtime::QuerySession& owner)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one native session snapshot to an ordinary comparison set. |
| inputs / outputs | Obtains owning native snapshot, exports each tuple Row and rejects duplicate current rows. |
| invariants | This explicit reference-side copy is outside native maintenance; snapshot query grant and ordinary exported rows have distinct owners. |
| ownership | Returned Relation owns ordinary rows after native snapshot release. |
| failure | Native budget/lease/output/allocation or duplicate mismatch rejects diagnostic. |
| cost | Full result traversal/native snapshot plus O(rows/scalar bytes) export and ordered-set insertion/comparisons. |
| Design | [apps/crown/workflow_verify.hpp](../../../../../apps/crown/workflow_verify.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/cli.md §Limits and verification](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0007

[Lines 66–66](../../../../../apps/crown/workflow_verify.cpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Signed=std::set<std::pair<SetOperation,Row>>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define exact signed set-delta comparison storage. |
| inputs / outputs | Ordered pairs retain operation and full owning Row; opposite signs remain distinct. |
| invariants | This is a small diagnostic set, not a native output spool, bag multiplicity or W06 net-batch algebra. |
| ownership | Each Signed value owns ordinary comparison rows. |
| failure | No runtime declaration failure. |
| cost | Type declaration only; actual rows allocate on insertion. |
| Design | [apps/crown/workflow_verify.hpp](../../../../../apps/crown/workflow_verify.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0008

[Lines 67–72](../../../../../apps/crown/workflow_verify.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Signed difference(const Relation& before,const Relation& after)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive expected exact signed set delta between two complete results. |
| inputs / outputs | After-before rows emit insert, before-after emit erase. |
| invariants | Preserves raw signs and full tuple identity, without cancelling opposite signs or inventing bag counts. |
| ownership | Returned Signed owns copies independent of both Relations. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | O(before+after) ordered membership comparisons plus changed-row copies/allocations. |
| Design | [apps/crown/workflow_verify.hpp](../../../../../apps/crown/workflow_verify.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/cli.md §Limits and verification](../../../../cli.md) |

## B0009

[Lines 73–73](../../../../../apps/crown/workflow_verify.cpp#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L73:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in workflow_verify.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [apps/crown/workflow_verify.cpp](../../../../../apps/crown/workflow_verify.cpp), [docs/quickstart.md](../../../../quickstart.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 74–121](../../../../../apps/crown/workflow_verify.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string crown::cli::verify_workflow_trace(const PhysicalPlan& plan,const std::string& path,
    io::InputOptions input_options,std::optional<std::uint64_t> memory,std::uint64_t work_limit,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every native set epoch against bounded modeled relational recomputation. |
| inputs / outputs | Reads≤8MiB input, creates separate native session and reference reader/state, verifies initial result, then per event expected signed difference versus raw native output/current snapshot/accepted positions; requires both EOF. |
| invariants | No durable restart proof or performance measurement. Native memory cap, modeled reference work/bytes, event cap and final report bytes are separate; reference adapter/mapping semantics are shared. |
| ownership | All owners local; native session derives configured grant, reference/input/report DTO storage stays outside it. |
| failure | Input/estimate/native/mismatch/output/OOM errors return no successful verification report; no maintained durable root/sink is created. |
| cost | Two input reader buffers plus full reference source/results/sets/native snapshot/delta exports per epoch, with joins and modeled product estimates; report dump created before final length check. |
| Design | [apps/crown/workflow_verify.hpp](../../../../../apps/crown/workflow_verify.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/cli.md §Limits and verification](../../../../cli.md) |

```text
while(const auto* event=reader.peek()) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare raw signed native epoch and source acceptance after each input. |
| inputs / outputs | Reference physical set changes/recomputation/difference precede native begin/step/commit/output; duplicate signed rows reject; compares result and both source directories before next event. |
| invariants | Reference and native own separate source state but share SQL adapters/mapping; both EOF checked after loop. No durable file or performance claim. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Input/usage/resource/encoding/native/I/O failures propagate to the appropriate process dispatcher. An operation may already have committed durable effects before report/diagnostic failure; absence of stdout proves no rollback. |
| cost | Per epoch full reference join/result/source copies plus actual native epoch/output/snapshot and ordered-set comparisons. |
| Design | [apps/crown/workflow_verify.hpp](../../../../../apps/crown/workflow_verify.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/cli.md §Limits and verification](../../../../cli.md) |
