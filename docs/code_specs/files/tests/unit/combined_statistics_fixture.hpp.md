# `tests/unit/combined_statistics_fixture.hpp` — block usage map

[Source](../../../../../tests/unit/combined_statistics_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `463882c3ebf771ac651d21f4bf0c25bad8f0598c3e39aa1f68f8573ffa0224e7`. 29 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/unit/combined_statistics_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 10–16](../../../../../tests/unit/combined_statistics_fixture.hpp#L10) | Callable definition: inline void binding(const stats::CombinedCapture& report,std::uint64_t sequence,bool pending=false) | calls check, state, stamp, workload; guard check(report.state().stamp().owner==report.workload().stamp().owner); · [reviewed contract](#b0002) |
| [B0003 · 17–19](../../../../../tests/unit/combined_statistics_fixture.hpp#L17) | Callable definition: inline void facts(const stats::CombinedCapture& report,const Database& db,std::uint64_t sequence) | calls binding, fixture_facts, state · [reviewed contract](#b0003) |
| [B0004 · 20–28](../../../../../tests/unit/combined_statistics_fixture.hpp#L20) | Callable definition: inline void same_workload(const ws::Snapshot& a,const ws::Snapshot& b) | calls check, stamp, metadata, options; guard check(a.stamp().owner==b.stamp().owner && a.stamp().committed_epoch==b.stamp().committed_epoch); · [reviewed contract](#b0004) |
| [B0005 · 29–29](../../../../../tests/unit/combined_statistics_fixture.hpp#L29) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |

## B0001

[Lines 1–9](../../../../../tests/unit/combined_statistics_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:885c7c9250ecadf918428f0081cd32a412a67f515b36e4957ee8a5bc0d3a96b2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare combined_statistics_fixture.hpp: include "owner_statistics_fixture.hpp", "workload_statistics_fixture.hpp", "crown/runtime/combined_statistics.hpp"; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/combined_statistics_fixture.hpp](../../../../../tests/unit/combined_statistics_fixture.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 10–16](../../../../../tests/unit/combined_statistics_fixture.hpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void binding(const stats::CombinedCapture& report,std::uint64_t sequence,bool pending=false){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that the state and workload halves of a CombinedCapture share actual owner, sequence, plan identity, and pending status. |
| inputs / outputs | Borrowed CombinedCapture, expected committed sequence, and optional pending flag enter; assertion-only result exits. |
| invariants | Both halves must name the same SupportOwnerId and physical-plan digest; state sequence and workload committed epoch equal the expected sequence; pending is true in both halves or neither. |
| ownership | Report is borrowed for these reads; no view or owner pointer escapes the helper. |
| failure | Mismatch fails through owner_fixture::check; the helper performs no capture or mutation. |
| cost | Reads immutable accessors and scalar stamps only; no runtime traversal is requested. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/verification/c01-statistics-combined-root-results-2026-11-07.md](../../../../verification/c01-statistics-combined-root-results-2026-11-07.md) |

## B0003

[Lines 17–19](../../../../../tests/unit/combined_statistics_fixture.hpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void facts(const stats::CombinedCapture& report,const Database& db,std::uint64_t sequence){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare combined owner facts against the literal R/S fixture and bind them to one committed sequence. |
| inputs / outputs | Borrowed CombinedCapture, literal Database, and expected sequence enter; assertion-only result exits. |
| invariants | Calls binding with pending=false then the independent fixture_facts oracle; does not treat matching statistics as a query-answer count. |
| ownership | All arguments remain borrowed during comparison; the report owns its capture, while Database rows are read only for expected counts. |
| failure | Binding or fixture mismatch throws the fixture runtime_error; native capture failures occurred before this helper and propagate. |
| cost | Scans the small literal source relations and groups keys in ordered maps; this is oracle work, not the runtime capture budget. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0004

[Lines 20–28](../../../../../tests/unit/combined_statistics_fixture.hpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void same_workload(const ws::Snapshot& a,const ws::Snapshot& b){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a workload snapshot retry or copy to preserve every independently scoped interval and cell field. |
| inputs / outputs | Two borrowed workload Snapshots enter; assertion-only result exits. |
| invariants | Compares owner/epoch/generations/segment, previous interval data, options/modes, metadata, current and prior cells, and pending/history flags; it never equates state freshness with interval identity. |
| ownership | Snapshots own their cell and descriptor values; helper borrows their spans during comparison and retains nothing. |
| failure | A mismatch throws std::runtime_error through owner_fixture::check; no workload mutation is attempted. |
| cost | Linear in current and previous cell counts plus fixed metadata comparisons; no report encoding or runtime work. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0005

[Lines 29–29](../../../../../tests/unit/combined_statistics_fixture.hpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L29:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in combined_statistics_fixture.hpp: namespace combined_fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/combined_statistics_fixture.hpp](../../../../../tests/unit/combined_statistics_fixture.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |
