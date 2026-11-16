# `src/runtime/inspection_detail.hpp` — block usage map

[Source](../../../../../src/runtime/inspection_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `d5075fadcaa4a35868394177232507b6bdf8920bbb0080dcfef71b89a17cd47d`. 63 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/runtime/inspection_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–11](../../../../../src/runtime/inspection_detail.hpp#L9) | Callable definition: inline AccountedRowSet inspection_rows(const resource::MemoryAccount& account) | calls AccountedRowSet; returns AccountedRowSet(account,resource::MemoryPurpose::scratch,invariant_attribution) · [reviewed contract](#b0002) |
| [B0003 · 12–14](../../../../../src/runtime/inspection_detail.hpp#L12) | Callable definition: template&lt;class T&gt; AccountedRowMap&lt;T&gt; inspection_counts(const resource::MemoryAccount& account) | calls ; returns AccountedRowMap&lt;T&gt;(account,resource::MemoryPurpose::scratch,invariant_attribution) · [reviewed contract](#b0003) |
| [B0004 · 15–15](../../../../../src/runtime/inspection_detail.hpp#L15) | Type/record definition: struct InspectionStop |  · [reviewed contract](#b0004) |
| [B0005 · 16–21](../../../../../src/runtime/inspection_detail.hpp#L16) | declares types or opens a type body. | source comment (unverified): // Own diagnostic prefixes and their original account; nested merges may stop partway · [reviewed contract](#b0005) |
| [B0006 · 22–23](../../../../../src/runtime/inspection_detail.hpp#L22) | Callable definition: InspectionContext(InspectionOptions limits,const resource::MemoryAccount& memory) :options(limits),account(memory),report(memory) | calls options, account, report · [reviewed contract](#b0006) |
| [B0007 · 24–25](../../../../../src/runtime/inspection_detail.hpp#L24) | Callable definition: InspectionContext(InspectionOptions limits,InvariantReport prefix) :options(limits),account(prefix.issues.get_allocator().account… | calls options, account, get_allocator, report · [reviewed contract](#b0007) |
| [B0008 · 26–26](../../../../../src/runtime/inspection_detail.hpp#L26) | Callable definition: \[\[nodiscard\]\] InvariantKey key(storage::RowView values) const | calls InvariantKey::copy_of; returns InvariantKey::copy_of(account,values); growth copy_of · [reviewed contract](#b0008) |
| [B0009 · 27–34](../../../../../src/runtime/inspection_detail.hpp#L27) | Callable definition: void charge(std::uint64_t amount=1) | calls max · [reviewed contract](#b0009) |
| [B0010 · 35–38](../../../../../src/runtime/inspection_detail.hpp#L35) | Callable definition: void add(InvariantIssue issue) | calls size, push_back, std::move; growth push_back · [reviewed contract](#b0010) |
| [B0011 · 39–39](../../../../../src/runtime/inspection_detail.hpp#L39) | Explanatory comments or spacing. | source comment (unverified): // Callers provide prefixes already within both ceilings before subtracting. · [reviewed contract](#b0011) |
| [B0012 · 40–43](../../../../../src/runtime/inspection_detail.hpp#L40) | Callable definition: \[\[nodiscard\]\] InspectionOptions remaining() const noexcept | calls size; returns {options.work_limit?std::optional&lt;std::uint64_t&gt;{*options.work_limit-report.work}:std::nullopt,; source comment (unverified): // Callers provide prefixes already within both ceilings before subtracting. · [reviewed contract](#b0012) |
| [B0013 · 44–61](../../../../../src/runtime/inspection_detail.hpp#L44) | Callable definition: void merge(InvariantReport child) | calls charge, add, std::move, max; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 62–63](../../../../../src/runtime/inspection_detail.hpp#L62) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::detail · [reviewed contract](#b0014) |

## B0001

[Lines 1–8](../../../../../src/runtime/inspection_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:b5c5b3223b96a0d695df5509f3165b698f03691d4ceb53c67c69afadf7d050a3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/inspection_detail.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/runtime/inspection.hpp"\`, \`"accounted_ordered_rows.hpp"\`, \`&lt;limits&gt;\`, \`&lt;utility&gt;\` for compilation; opens namespace \`crown::runtime::detail\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 9–11](../../../../../src/runtime/inspection_detail.hpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline AccountedRowSet inspection_rows(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty expected-row set with invariant diagnostic attribution. |
| inputs / outputs | Returns AccountedRowSet(account,scratch,invariant_attribution) for independent inspection regrouping. |
| invariants | It binds the existing query allowance and does not validate contents, reserve all rows or create an index of live runtime state. |
| ownership | Returned set owns subsequently inserted compact rows/nodes; its allocator retains the supplied account. |
| failure | Empty setup introduces no manual handler; later inserts/clones may fail under the original account. |
| cost | Fixed empty container/allocator setup; later ordered insertion and key-byte costs belong to the population loop. |
| Design | [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 12–14](../../../../../src/runtime/inspection_detail.hpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> AccountedRowMap<T> inspection_counts(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty expected-count map under the invariant scratch owner. |
| inputs / outputs | Returns an AccountedRowMap&lt;T&gt; funded by the supplied account and capture:15 attribution. |
| invariants | Expected counts are independent diagnostic reconstruction, not shared mutable engine indexes or authority to commit. |
| ownership | The map later owns copied keys and values; borrowed lookup keys remain caller-owned. |
| failure | No new catch or account fallback; later node/key allocation or T construction can propagate. |
| cost | Fixed empty map/allocator setup; insertion/comparison and T costs depend on later usage. |
| Design | [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 15–15](../../../../../src/runtime/inspection_detail.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InspectionStop {};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Signal bounded inspection incompleteness without allocating a diagnostic string. |
| inputs / outputs | Empty private exception is thrown after setting report.complete=false for work, issue or census overflow. |
| invariants | Only the enclosing inspection boundary converts it to a partial incomplete report; it never represents a valid invariant proof or engine rollback. |
| ownership | No payload or retained owner; partial report still owns any copied issues. |
| failure | Always used for the named limit stop; allocation errors are separate and propagate. |
| cost | Fixed sentinel construction/exception propagation, not a row traversal; unwinding releases actual diagnostic scratch. |
| Design | [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 16–21](../../../../../src/runtime/inspection_detail.hpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InspectionContext {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose one diagnostic allowance, original account and owning partial invariant report. |
| inputs / outputs | options is the caller ceiling, account funds expected-state/key/report storage, report holds work/complete/issues/census. New and prefixed constructors support layered inspection. |
| invariants | Callers supply prefixes whose work and issue counts fit options before remaining() is used. A partial/overflow stop marks complete=false; validity cannot be inferred from an empty partial issue list. |
| ownership | Account and report retain native owners; it stores no mutable runtime pointer. Issue/key copies can allocate and returned views need their owner retained. |
| failure | InspectionStop marks bounded incompleteness; bad_alloc/MemoryFailure remain real allocation failures handled by the public inspector contract, not swallowed here. |
| cost | Context setup is fixed; actual expected sets, full database clones, key bytes, issue-vector growth and layered merges are explicit costs of inspection. |
| Design | [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 22–23](../../../../../src/runtime/inspection_detail.hpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  InspectionContext(InspectionOptions limits,const resource::MemoryAccount& memory)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start an empty invariant report bound to the existing query account. |
| inputs / outputs | Copies limits/account handles and constructs InvariantReport(memory). |
| invariants | No inspection or new allowance is performed; report starts complete with zero usage and empty issues. |
| ownership | Report allocator retains the original account for any later issue/key allocation. |
| failure | No explicit handler; empty owner construction does not hide subsequent allocation failures. |
| cost | Fixed scalar/handle/empty allocator setup without a row scan. |
| Design | [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 24–25](../../../../../src/runtime/inspection_detail.hpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  InspectionContext(InspectionOptions limits,InvariantReport prefix)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Continue layered inspection by adopting an existing owning diagnostic prefix. |
| inputs / outputs | Takes prefix by value, derives account from its issues allocator and moves prefix into report. |
| invariants | Caller preserves compatible limits and used&lt;=ceiling before requesting remaining allowance. This constructor does not clamp or independently validate an arbitrary edited prefix. |
| ownership | Moving transfers its issue/key owners. Passing an lvalue first copies the report and can fund deep issues/keys on the source account. |
| failure | Any by-value copy failure precedes construction; no prefix repair, catch or budget reset. |
| cost | Move path uses scalar/handle/container ownership transfer; lvalue import can cost O(issues plus owned key bytes). |
| Design | [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 26–26](../../../../../src/runtime/inspection_detail.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] InvariantKey key(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a stable diagnostic key that outlives the inspected cursor/row. |
| inputs / outputs | Deep-copies the supplied RowView with InvariantKey::copy_of(account,values). |
| invariants | The result owns immutable compact values; it is not a borrowed row, cursor pin or data-freshness witness. |
| ownership | Original query account funds the key block; input values need remain valid only until copying completes. |
| failure | Memory/overflow/allocation failures propagate before any issue append; no truncation fallback. |
| cost | Visits/copies projected fields and variable text bytes plus actual compact block/control overhead; not a free view operation. |
| Design | [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 27–34](../../../../../src/runtime/inspection_detail.hpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void charge(std::uint64_t amount=1)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit cumulative abstract inspection work before the corresponding diagnostic work. |
| inputs / outputs | Checks uint64 addition and optional remaining ceiling, then increments report.work only on success. |
| invariants | Denial preserves the already-spent counter and marks report incomplete. Unlimited optional work still cannot overflow uint64. |
| ownership | Only local report counters mutate; no query grant is replaced or runtime data changed. |
| failure | Throws InspectionStop after complete=false; no error string or broad catch. |
| cost | Fixed checked arithmetic, independent of the amount of allocator/CPU work modeled by the caller. |
| Design | [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 35–38](../../../../../src/runtime/inspection_detail.hpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void add(InvariantIssue issue)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one owning invariant issue within the issue ceiling. |
| inputs / outputs | Takes an already prepared issue, checks report.issues.size()&gt;=issue_limit, then moves it into the funded vector. |
| invariants | An over-limit append marks incomplete and retains the prior issue prefix. Preparing by-value issue/key may have cost work before this check. |
| ownership | Vector retains the moved issue/key graph under its account; local rejected issue releases through RAII. |
| failure | Ceiling throws InspectionStop; vector/funded key allocation failure propagates separately. |
| cost | Fixed cap check plus amortized vector growth/moves; by-value copying and key construction may allocate proportional to issue payload. |
| Design | [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 39–39](../../../../../src/runtime/inspection_detail.hpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L39:sha256:5534072724912ee08fdf66eb73d0ad95a4ee7a4a62756b609c844975ef9e833d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`\[\[nodiscard\]\] InspectionOptions remaining() const noexcept\`: Callers provide prefixes already within both ceilings before subtracting. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/inspection_detail.hpp:L40; use that declaration for the actual input/output shape. |
| invariants | The source note states: Callers provide prefixes already within both ceilings before subtracting. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0012

[Lines 40–43](../../../../../src/runtime/inspection_detail.hpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] InspectionOptions remaining()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pass the unspent outer inspection limits to a nested layer. |
| inputs / outputs | Subtracts report.work from present work_limit and issues.size() from issue_limit, retaining absent work bound as nullopt. |
| invariants | Requires the existing prefix to fit both original limits; this unsigned subtraction is not clamped for arbitrary edited prefixes. Normal callers stop immediately on InspectionStop. |
| ownership | Returns inline options only; no new account, row owner or allowance is created. |
| failure | Declared noexcept under the caller prefix invariant; no recovery or dynamic validation. |
| cost | Two fixed arithmetic subtractions and optional construction. |
| Design | [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 44–61](../../../../../src/runtime/inspection_detail.hpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void merge(InvariantReport child)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine a nested partial invariant report without claiming atomic diagnostic publication. |
| inputs / outputs | Charges child.work, ANDs completeness, moves each child issue through add(), then checked-adds all 16 census fields. |
| invariants | May stop after part of the diagnostic merge; each denial/overflow sets complete=false so the prefix is never a valid proof. Callers keep child usage within remaining outer limits and use compatible original-account owners. |
| ownership | Child is owned by value and its copied/moved keys remain funded; lvalue call may deep-copy first. No engine data is merged. |
| failure | Work/issue/census overflow throws InspectionStop; actual issue allocation errors propagate. This intentionally preserves useful prior issues rather than rolling back a diagnostic prefix. |
| cost | O(child issues) moves plus 16 fixed census checks and possible vector growth; deep lvalue copies/key payload and existing child inspections are separate real costs. |
| Design | [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
    const auto sum=[&](std::size_t& target,std::size_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent census addition from silently wrapping host-sized inspection counts. |
| inputs / outputs | Checks value&lt;=SIZE_MAX-target before incrementing each selected report.statistics field. |
| invariants | Earlier merged census fields/issues may already have changed; overflow always marks the report incomplete. |
| ownership | Captures the local diagnostic report only; no live storage owner is touched. |
| failure | Throws InspectionStop on overflow with no dynamic message. |
| cost | One fixed subtraction/comparison/add per census field. |
| Design | [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [tests/unit/runtime_inspection_test.cpp](../../../../../tests/unit/runtime_inspection_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 62–63](../../../../../src/runtime/inspection_detail.hpp#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L63:sha256:f79cabcac75b0816074faad638b67262ffe6b32c06065ad63cecb17182f14b77
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/inspection_detail.hpp: closes \`struct InspectionContext\`, \`namespace crown::runtime::detail\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace crown::runtime::detail Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
