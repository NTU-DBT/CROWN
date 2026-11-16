# `src/planner/recognize.cpp` — block usage map

[Source](../../../../../src/planner/recognize.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Run GYO reduction for body and augmented-head hypergraphs; distinguish free-connex, acyclic non-free-connex and cyclic cases.

Snapshot SHA-256: `b2de595f8e3e186b892202e4cc9322990eb8f4458256472ebd5a47d7e7ce5045`. 122 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [planner](../../../subsystem_contracts.md#planner). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/planner/recognize.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–10](../../../../../src/planner/recognize.cpp#L10) | Type/record definition: struct Limit |  · [reviewed contract](#b0002) |
| [B0003 · 11–12](../../../../../src/planner/recognize.cpp#L11) | Explanatory comments or spacing. | source comment (unverified): // Selected reduction/containment steps only; validation and container work · [reviewed contract](#b0003) |
| [B0004 · 13–20](../../../../../src/planner/recognize.cpp#L13) | Type/record definition: struct Budget | source comment (unverified): // Selected reduction/containment steps only; validation and container work · [reviewed contract](#b0004) |
| [B0005 · 21–30](../../../../../src/planner/recognize.cpp#L21) | Callable definition: bool contains(const Scope& larger, const Scope& smaller, Budget& budget) | calls begin, end, charge; returns false; true; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 31–32](../../../../../src/planner/recognize.cpp#L31) | Explanatory comments or spacing. | source comment (unverified): // Restart the ordered passes after each deletion to keep the witness stable. · [reviewed contract](#b0006) |
| [B0007 · 33–85](../../../../../src/planner/recognize.cpp#L33) | Callable definition: GyoResult reduce(const std::vector&lt;Scope&gt;& scopes, Budget& budget) | calls size, charge, push_back, empty; returns result; growth push_back; 10 loop sites; source comment (unverified): // Restart the ordered passes after each deletion to keep the witness stable. · [reviewed contract](#b0007) |
| [B0008 · 86–87](../../../../../src/planner/recognize.cpp#L86) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0008) |
| [B0009 · 88–92](../../../../../src/planner/recognize.cpp#L88) | Callable definition: GyoResult gyo_reduce(const std::vector&lt;Scope&gt;& scopes) | calls reduce, Error; returns reduce(scopes,budget) · [reviewed contract](#b0009) |
| [B0010 · 93–93](../../../../../src/planner/recognize.cpp#L93) | Explanatory comments or spacing. |  |
| [B0011 · 94–98](../../../../../src/planner/recognize.cpp#L94) | Callable definition: StructuralAnalysis analyze(const Catalog& catalog, const Query& query) | calls analyze_bounded, Error, std::move; returns std::move(*run.analysis) · [reviewed contract](#b0011) |
| [B0012 · 99–99](../../../../../src/planner/recognize.cpp#L99) | Explanatory comments or spacing. |  |
| [B0013 · 100–121](../../../../../src/planner/recognize.cpp#L100) | Callable definition: RecognitionRun analyze_bounded(const Catalog& catalog, const Query& query, RecognitionLimits limits) | calls validate, charge, insert, push_back; returns {StructuralAnalysis{classification,std::move(body),std::move(augmented)},budget.work}; {std::nullop…; growth insert, push_back; 3 loop sites; source comment (unverified): // Recognition only: this edge never enters a runtime plan or database. · [reviewed contract](#b0013) |
| [B0014 · 122–122](../../../../../src/planner/recognize.cpp#L122) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner · [reviewed contract](#b0014) |

## B0001

[Lines 1–9](../../../../../src/planner/recognize.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:6c6e2ee06fc59284adace54d0784d3626c0ef13c9db414af126fe377a3d6c98f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | make #include "crown/planner/recognize.hpp", #include "crown/api/error.hpp", #include &lt;limits&gt;, #include &lt;map&gt;, #include &lt;utility&gt; available to src/planner/recognize.cpp; open crown::planner and anonymous helper namespace. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/recognize.cpp](../../../../../src/planner/recognize.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0002

[Lines 10–10](../../../../../src/planner/recognize.cpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Limit {};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Signal selected GYO work exhaustion without inventing a query class. |
| inputs / outputs | Empty internal exception payload. |
| invariants | Only recognition wrappers translate this sentinel; it does not represent allocation or invalid input. |
| ownership | Value-only sentinel; no witness or source borrow. |
| failure | Thrown before a disallowed increment; outer temporary state is discarded. |
| cost | No owned text/container payload; exception runtime overhead applies only on exhaustion. |
| Design | [docs/planner_proofs.md](../../../../planner_proofs.md), [Refactor.md §4](../../../../../Refactor.md), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp) |

## B0003

[Lines 11–12](../../../../../src/planner/recognize.cpp#L11); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L12:sha256:7c2d026c93791f1d3f6cb6a0c0319e5f303b5b5c5261b112eb46e2d1ebfcd4aa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Budget: Selected reduction/containment steps only; validation and container work retain their own costs. Exhaustion publishes no partial classification. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Budget; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Budget come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/recognize.cpp](../../../../../src/planner/recognize.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0004

[Lines 13–20](../../../../../src/planner/recognize.cpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Budget {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count admitted GYO checkpoints against optional finite allowance and uint64 capacity. |
| inputs / outputs | RecognitionLimits plus initially zero work; charge increments once or throws Limit. |
| invariants | A rejected charge does not increment. No finite option still retains overflow rejection. |
| ownership | Owns scalar limits/work for the synchronous recognition call. |
| failure | Limit is translated separately from propagated allocation/input errors. |
| cost | Fixed counter work; metadata validation, copying, allocator and ordered-container costs remain separate. |
| Design | [docs/planner_proofs.md](../../../../planner_proofs.md), [Refactor.md §4](../../../../../Refactor.md), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp) |

## B0005

[Lines 21–30](../../../../../src/planner/recognize.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool contains(const Scope& larger,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test ordered scope inclusion with a checkpoint for each merge-loop iteration. |
| inputs / outputs | Two sorted variable sets and shared Budget to bool. |
| invariants | Visits larger elements until every smaller element matches or inclusion becomes impossible; empty smaller succeeds without a loop charge. |
| ownership | Borrows scopes; mutates only the caller-owned budget. |
| failure | Limit aborts the whole recognition attempt without a partial class. |
| cost | Merge visits up to both scope lengths, not a constant-time set inclusion; no container allocation. |
| Design | [docs/planner_proofs.md](../../../../planner_proofs.md), [Refactor.md §4](../../../../../Refactor.md), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp) |

## B0006

[Lines 31–32](../../../../../src/planner/recognize.cpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L32:sha256:8483e86c25dfe181d2597d7a28650cff39b1516d2de0dfb690911ba6b500f595
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for reduce: Restart the ordered passes after each deletion to keep the witness stable. These scope copies are compiler scratch, not mutable-input elimination. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies reduce; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for reduce come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/recognize.cpp](../../../../../src/planner/recognize.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0007

[Lines 33–85](../../../../../src/planner/recognize.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GyoResult reduce(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a deterministic GYO elimination witness or frozen residual core. |
| inputs / outputs | Copies original indexed scopes, then removes empty edges, private variables or contained edges in ordered passes. |
| invariants | One deletion restarts the passes. Original edge IDs survive scope shrink/erase, including duplicate scopes; source query is unchanged. |
| ownership | Owns copied residual scopes, count-map nodes and witness entries; no runtime table is removed. |
| failure | Limit or allocation failure discards temporary reduction; no partially accepted result is published. |
| cost | Repeated whole-incidence scans, ordered count maps, edge-pair containment merge walks and vector erasure shifts; witness/set/vector growth allocates. |
| Design | [docs/planner_proofs.md](../../../../planner_proofs.md), [Refactor.md §4](../../../../../Refactor.md), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp) |

## B0008

[Lines 86–87](../../../../../src/planner/recognize.cpp#L86); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L86-L87:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the lexical scope identified by the source span. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/recognize.cpp](../../../../../src/planner/recognize.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0009

[Lines 88–92](../../../../../src/planner/recognize.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GyoResult gyo_reduce(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose unconfigured-limit scope reduction with typed counter-exhaustion presentation. |
| inputs / outputs | Scope vector to complete witness/core; no catalog/query validation is implied. |
| invariants | Variable IDs are opaque scope keys here; nullopt removes only the configured finite cap. |
| ownership | Borrows input while reduce constructs independent output. |
| failure | Limit becomes resource_limit Error; allocation exceptions propagate. |
| cost | Full deterministic reduction and owning copies; not a resumable continuation. |
| Design | [docs/planner_proofs.md](../../../../planner_proofs.md), [Refactor.md §4](../../../../../Refactor.md), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp) |

## B0011

[Lines 94–98](../../../../../src/planner/recognize.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StructuralAnalysis analyze(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the blocking unlimited-option query classification adapter. |
| inputs / outputs | Catalog/query to owned body/augmented GYO analyses and class. |
| invariants | Delegates the same bounded implementation with no configured finite work cap; does not compute height. |
| ownership | Returns the owned successful analysis by move. |
| failure | Absent analysis from counter exhaustion becomes resource_limit Error; input/allocation failures propagate. |
| cost | Full input validation and both reductions; final move does not rerun classification. |
| Design | [docs/planner_proofs.md](../../../../planner_proofs.md), [Refactor.md §4](../../../../../Refactor.md), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp) |

## B0013

[Lines 100–121](../../../../../src/planner/recognize.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RecognitionRun analyze_bounded(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify body and body-plus-output scope without trusting an augmented result alone. |
| inputs / outputs | Validated catalog/query and selected-step limit to optional complete StructuralAnalysis plus consumed work. |
| invariants | Body cyclicity takes precedence even when the synthetic output edge makes the augmentation acyclic. Head is deduplicated metadata, never a runtime input. |
| ownership | Owns scope/witness/core scratch; successful output owns both reductions independently of inputs. |
| failure | Limit returns no analysis and exact admitted checkpoint count; initial validation and allocation errors propagate rather than becoming a partial class. |
| cost | Input validation occurs outside the counter, followed by term/head scans and two copying/repeated-scan reductions under one shared work counter. |
| Design | [docs/planner_proofs.md](../../../../planner_proofs.md), [Refactor.md §4](../../../../../Refactor.md), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp), [P1 arXiv:2301.04003v2 §3.2 free-connex definition](https://arxiv.org/pdf/2301.04003v2) |

## B0014

[Lines 122–122](../../../../../src/planner/recognize.cpp#L122); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L122-L122:sha256:acb95521e5c8cc117a4f60f87ae076d39f48ab1ff02f31d3b8a4ada933fd3da0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/recognize.cpp](../../../../../src/planner/recognize.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |
