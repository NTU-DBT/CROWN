# `include/crown/planner/recognize.hpp` — block usage map

[Source](../../../../../../include/crown/planner/recognize.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Run GYO reduction for body and augmented-head hypergraphs; distinguish free-connex, acyclic non-free-connex and cyclic cases.

Snapshot SHA-256: `f3372210133bee6ca6fa82dfcec40264648a50b4954e02ba3101fef4ce28b856`. 36 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [planner](../../../../subsystem_contracts.md#planner). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/tree_plans.md](../../../../../tree_plans.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../../include/crown/planner/recognize.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 10–10](../../../../../../include/crown/planner/recognize.hpp#L10) | Type/record definition: enum class ReductionKind |  · [reviewed contract](#b0002) |
| [B0003 · 11–16](../../../../../../include/crown/planner/recognize.hpp#L11) | Type/record definition: struct ReductionStep |  · [reviewed contract](#b0003) |
| [B0004 · 17–17](../../../../../../include/crown/planner/recognize.hpp#L17) | Type/record definition: struct ResidualEdge |  · [reviewed contract](#b0004) |
| [B0005 · 18–22](../../../../../../include/crown/planner/recognize.hpp#L18) | Type/record definition: struct GyoResult |  · [reviewed contract](#b0005) |
| [B0006 · 23–23](../../../../../../include/crown/planner/recognize.hpp#L23) | Type/record definition: enum class QueryClass |  · [reviewed contract](#b0006) |
| [B0007 · 24–24](../../../../../../include/crown/planner/recognize.hpp#L24) | Type/record definition: struct StructuralAnalysis |  · [reviewed contract](#b0007) |
| [B0008 · 25–25](../../../../../../include/crown/planner/recognize.hpp#L25) | Explanatory comments or spacing. | source comment (unverified): // Caps explicit recognition checkpoints after catalog/query validation; it is not a byte or elapsed-time limit. · [reviewed contract](#b0008) |
| [B0009 · 26–26](../../../../../../include/crown/planner/recognize.hpp#L26) | Type/record definition: struct RecognitionLimits | source comment (unverified): // Caps explicit recognition checkpoints after catalog/query validation; it is not a byte or elapsed-time limit. · [reviewed contract](#b0009) |
| [B0010 · 27–30](../../../../../../include/crown/planner/recognize.hpp#L27) | Type/record definition: struct RecognitionRun | source comment (unverified): // Absent on resource exhaustion. · [reviewed contract](#b0010) |
| [B0011 · 31–36](../../../../../../include/crown/planner/recognize.hpp#L31) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Scope reduction never removes occurrences from the actual query IR. · [reviewed contract](#b0011) |

## B0001

[Lines 1–9](../../../../../../include/crown/planner/recognize.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Scope = std::set<VariableId>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the ordered unique-variable set used for one query occurrence scope. |
| inputs / outputs | A Scope value contains VariableId entries and is passed to the GYO reducer. |
| invariants | The set orders IDs and stores each ID at most once; the alias does not change the query IR. |
| ownership | The alias owns nothing; each instantiated std::set owns its nodes. |
| failure | The alias declaration cannot fail; constructing or growing a set may allocate. |
| cost | The alias has no runtime cost; Scope construction and set operations follow std::set costs. |
| Design | [include/crown/planner/recognize.hpp §Scope](../../../../../../include/crown/planner/recognize.hpp), [src/planner/recognize.cpp §GYO scope reduction](../../../../../../src/planner/recognize.cpp), [docs/planner_proofs.md §Structural foundation and remaining proof obligations](../../../../../planner_proofs.md) |

## B0002

[Lines 10–10](../../../../../../include/crown/planner/recognize.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ReductionKind {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the three GYO deletion rules recorded in a reduction witness. |
| inputs / outputs | Distinguishes deleting an empty edge, a contained edge, or a variable private to one current edge. |
| invariants | The tag does not prove a supplied step is legal; legality depends on current scopes. |
| ownership | Value-sized enum; no query or edge ownership. |
| failure | Any representable enumerator is storable; replay establishes validity. |
| cost | Constant-size storage and comparison. |
| Design | [include/crown/planner/recognize.hpp](../../../../../../include/crown/planner/recognize.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/planner/recognize.cpp](../../../../../../src/planner/recognize.cpp), [src/frontend/admission.cpp](../../../../../../src/frontend/admission.cpp) |

## B0003

[Lines 11–16](../../../../../../include/crown/planner/recognize.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReductionStep {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one replayable GYO deletion against original occurrence-edge identity. |
| inputs / outputs | Stores rule kind, original edge index, optional containment anchor, and optional private variable. |
| invariants | Empty-edge has neither optional; private-variable has only variable; contained-edge has only anchor. Aggregate construction does not enforce these shapes. |
| ownership | Owns scalar IDs/enum/optionals; no scope reference. |
| failure | Malformed combinations require replay rejection. |
| cost | Fixed-size copy; no dynamic allocation. |
| Design | [include/crown/planner/recognize.hpp](../../../../../../include/crown/planner/recognize.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/planner/recognize.cpp](../../../../../../src/planner/recognize.cpp), [src/frontend/admission.cpp](../../../../../../src/frontend/admission.cpp) |

## B0004

[Lines 17–17](../../../../../../include/crown/planner/recognize.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResidualEdge {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one unreduced edge in a failed core without renumbering occurrences. |
| inputs / outputs | Pairs original edge index with current reduced Scope. |
| invariants | Duplicate source scopes remain distinct through original edge IDs. |
| ownership | Owns the reduced set and index after input scopes expire. |
| failure | No constructor checks edge index against a particular input. |
| cost | Scope copy scales with members and allocates set nodes. |
| Design | [include/crown/planner/recognize.hpp](../../../../../../include/crown/planner/recognize.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/planner/recognize.cpp](../../../../../../src/planner/recognize.cpp), [src/frontend/admission.cpp](../../../../../../src/frontend/admission.cpp) |

## B0005

[Lines 18–22](../../../../../../include/crown/planner/recognize.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GyoResult {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a completed reduction witness or the residual edges that blocked reduction. |
| inputs / outputs | acyclic reports whether all edges reduced; witness is the applied prefix; failed_core is residual. |
| invariants | Success has no failed core; failure retains unreduced original IDs. This is hypergraph evidence, not a plan witness. |
| ownership | Owns vectors and every residual scope. |
| failure | Does not cross-check acyclic, witness and core fields. |
| cost | Storage/copy scales with witness and residual scopes. |
| Design | [include/crown/planner/recognize.hpp](../../../../../../include/crown/planner/recognize.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/planner/recognize.cpp](../../../../../../src/planner/recognize.cpp), [src/frontend/admission.cpp](../../../../../../src/frontend/admission.cpp) |

## B0006

[Lines 23–23](../../../../../../include/crown/planner/recognize.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class QueryClass {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the body/head structural outcomes of query recognition. |
| inputs / outputs | Distinguishes free-connex, acyclic-but-not-free-connex, and cyclic body. |
| invariants | A cyclic body remains cyclic even when its head-augmented hypergraph reduces; body acyclicity is checked first. |
| ownership | Value-sized tag. |
| failure | Does not perform classification and has no resource-stop case. |
| cost | Constant-size value. |
| Design | [include/crown/planner/recognize.hpp](../../../../../../include/crown/planner/recognize.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/planner/recognize.cpp](../../../../../../src/planner/recognize.cpp), [src/frontend/admission.cpp](../../../../../../src/frontend/admission.cpp) |

## B0007

[Lines 24–24](../../../../../../include/crown/planner/recognize.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StructuralAnalysis {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep body and head-augmented GYO results with the derived query class. |
| inputs / outputs | Carries QueryClass and GyoResult for atom scopes and those scopes plus one unique head-variable set. |
| invariants | Synthetic head edge is recognition-only, never query IR/physical database/runtime tree; repeated output positions collapse in the set. |
| ownership | Owns both reduction results and nested scope payloads. |
| failure | Aggregate does not verify class/result consistency. |
| cost | Move transfers nested state; copy follows all witnesses/cores. |
| Design | [include/crown/planner/recognize.hpp](../../../../../../include/crown/planner/recognize.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/planner/recognize.cpp](../../../../../../src/planner/recognize.cpp), [src/frontend/admission.cpp](../../../../../../src/frontend/admission.cpp) |

## B0008

[Lines 25–25](../../../../../../include/crown/planner/recognize.hpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L25:sha256:6ab451d076b2511b0682d1e34c9875af4017586e7acb91b02b97e611834d4eed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for RecognitionLimits: Caps explicit recognition checkpoints after catalog/query validation; it is not a byte or elapsed-time limit. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies RecognitionLimits; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for RecognitionLimits come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/recognize.hpp](../../../../../../include/crown/planner/recognize.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0009

[Lines 26–26](../../../../../../include/crown/planner/recognize.hpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RecognitionLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the explicit work-checkpoint ceiling for bounded structural recognition. |
| inputs / outputs | Optional uint64 work_limit defaults to one million; disengaged means no work ceiling. |
| invariants | Counts selected charges only. analyze_bounded validates catalog/query before charging; not elapsed-time or allocator-byte cap. |
| ownership | Owns optional numeric limit only. |
| failure | Zero permits validation but no charged recognition step; unsigned limit cannot be negative. |
| cost | Constant-size copy. |
| Design | [include/crown/planner/recognize.hpp](../../../../../../include/crown/planner/recognize.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/planner/recognize.cpp](../../../../../../src/planner/recognize.cpp), [src/frontend/admission.cpp](../../../../../../src/frontend/admission.cpp) |

## B0010

[Lines 27–30](../../../../../../include/crown/planner/recognize.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RecognitionRun {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent bounded recognition without inventing a class after resource exhaustion. |
| inputs / outputs | analysis holds both GYO results only on success; work is accepted selected charges. |
| invariants | Absent analysis means resource stop, distinct from cyclic/non-free-connex; work is not total CPU/memory. |
| ownership | Owns optional analysis and nested payloads. |
| failure | Aggregate does not enforce stop cause; analyze_bounded supplies protocol. |
| cost | Successful result construction/copy may allocate by witness/core size. |
| Design | [include/crown/planner/recognize.hpp](../../../../../../include/crown/planner/recognize.hpp), [docs/planner_proofs.md](../../../../../planner_proofs.md), [src/planner/recognize.cpp](../../../../../../src/planner/recognize.cpp), [src/frontend/admission.cpp](../../../../../../src/frontend/admission.cpp) |

## B0011

[Lines 31–36](../../../../../../include/crown/planner/recognize.hpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] GyoResult gyo_reduce(const std::vector<Scope>& scopes);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose unbounded GYO reduction and bounded whole-query structural classification. |
| inputs / outputs | Scopes or a Catalog/Query in; GyoResult, StructuralAnalysis, or RecognitionRun with work used out. |
| invariants | Bounded exhaustion returns no partial analysis; classification checks the body and the body augmented by the head set. |
| ownership | Inputs are borrowed synchronously; returned witnesses and failed cores own their vectors. |
| failure | Input validation can throw. GYO counter exhaustion becomes resource_limit in the blocking APIs; bounded analysis returns an empty optional. |
| cost | Reduction visits and ordered container work are counted selectively; the limit is not a byte or elapsed-time cap. |
| Design | [src/planner/recognize.cpp §analyze_bounded](../../../../../../src/planner/recognize.cpp), [docs/planner_proofs.md §Structural foundation and remaining proof obligations](../../../../../planner_proofs.md), [include/crown/planner/recognize.hpp §RecognitionRun](../../../../../../include/crown/planner/recognize.hpp) |
