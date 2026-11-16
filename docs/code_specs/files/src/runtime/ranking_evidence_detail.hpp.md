# `src/runtime/ranking_evidence_detail.hpp` — block usage map

[Source](../../../../../src/runtime/ranking_evidence_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `573bf874c16c5c12dcf1d140a32712eb6c2ec643f9db9eb465f68ab09c5fce57`. 13 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../src/runtime/ranking_evidence_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Private classifier seam for isolated boundary tests. It returns numeric · [reviewed contract](#b0001) |
| [B0002 · 7–11](../../../../../src/runtime/ranking_evidence_detail.hpp#L7) | Type/record definition: struct Census | source comment (unverified): // Private classifier seam for isolated boundary tests. It returns numeric · [reviewed contract](#b0002) |
| [B0003 · 12–13](../../../../../src/runtime/ranking_evidence_detail.hpp#L12) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |

## B0001

[Lines 1–6](../../../../../src/runtime/ranking_evidence_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:3eda7316b678e73a042d30f1e6cc4038a6a9edba416685bb338830625676411e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/ranking_evidence_detail.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/runtime/ranking_evidence.hpp"\`, \`"../planner/ranking_detail.hpp"\` for compilation; opens namespace \`crown::runtime::ranking::detail\`. Source comment: Private classifier seam for isolated boundary tests. It returns numeric observations only and cannot manufacture public actual-owner Evidence. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Private classifier seam for isolated boundary tests. It returns numeric observations only and cannot manufacture public actual-owner Evidence. Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 7–11](../../../../../src/runtime/ranking_evidence_detail.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Census {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent bounded numeric input-census observations without manufacturing actual-owner Evidence authority. |
| inputs / outputs | reasons records unavailable/protocol/saturation facts; total is exact nonsaturated committed physical input denominator when available; weights is one funded InputWeight per source table. Constructor binds evidence allocator to supplied account. |
| invariants | Classifier seam is private/test-only composition. Numeric facts cannot create RuntimeEvidence/actual-owner capture, native-depth or verified-height proof. Disabled/incomplete/overflow states remain explicit reasons. |
| ownership | Owns funded numeric weights only, not runtime rows/cursors. Ordinary vector copies can allocate on the bound account; constructor merely binds an empty allocator. |
| failure | Classifier Budget failures or account allocation propagate to ranking capture boundary; no silent fabricated denominator. |
| cost | Actual classifier scans descriptors/cells and sources, allocates seen/root/weight arrays, and calls input_share per physical root with a full descriptor scan each time. Worst repeated scan is roots*descriptors; no O(1) census claim. |
| Design | [src/runtime/ranking_evidence_detail.hpp](../../../../../src/runtime/ranking_evidence_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 12–13](../../../../../src/runtime/ranking_evidence_detail.hpp#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Census classify_census(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the exact private classifier for isolated boundary tests and internal capture. |
| inputs / outputs | Reads owning workload Snapshot and shared planner ranking Budget, returning numeric Census via the same census implementation. |
| invariants | Checks physical insert/erase roots, completeness/duplicates/saturation and consistent denominators; it does not accept arbitrary numbers as an actual-owner capability. |
| ownership | Snapshot is borrowed; returned numeric arrays are funded on snapshot.plan().account(). Scratch seen/roots arrays expire before return. |
| failure | Work/payload/account exhaustion propagates; reasons preserve semantic unavailability rather than throwing for each unavailable fact. |
| cost | Descriptor/cell/source walks plus one full input_share descriptor scan per root, funded arrays and charged comparisons; no query-row population scan. |
| Design | [src/runtime/ranking_evidence_detail.hpp](../../../../../src/runtime/ranking_evidence_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [docs/code_review.md](../../../../code_review.md) |
