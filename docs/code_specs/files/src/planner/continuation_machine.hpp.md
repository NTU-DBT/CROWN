# `src/planner/continuation_machine.hpp` — block usage map

[Source](../../../../../src/planner/continuation_machine.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims.

Snapshot SHA-256: `fb4109e57e5d2bbfb2695da302a173670b347f609f1f429072458e8d93ada058`. 149 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../src/planner/continuation_machine.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Validated input is copied/moved exactly once at facade admission. Machines · [reviewed contract](#b0001) |
| [B0002 · 14–18](../../../../../src/planner/continuation_machine.hpp#L14) | Type/record definition: struct BindingData | source comment (unverified): // Validated input is copied/moved exactly once at facade admission. Machines · [reviewed contract](#b0002) |
| [B0003 · 19–21](../../../../../src/planner/continuation_machine.hpp#L19) | Explanatory comments or spacing. | source comment (unverified): // Only ValidationMachine constructs checked upper authority. A complete tree · [reviewed contract](#b0003) |
| [B0004 · 22–27](../../../../../src/planner/continuation_machine.hpp#L22) | Type/record definition: struct CheckedUpper | source comment (unverified): // Only ValidationMachine constructs checked upper authority. A complete tree · [reviewed contract](#b0004) |
| [B0005 · 28–32](../../../../../src/planner/continuation_machine.hpp#L28) | Type/record definition: struct CheckedProof |  · [reviewed contract](#b0005) |
| [B0006 · 33–33](../../../../../src/planner/continuation_machine.hpp#L33) | Type/record definition: struct IncumbentData |  · [reviewed contract](#b0006) |
| [B0007 · 34–37](../../../../../src/planner/continuation_machine.hpp#L34) | Type/record definition: struct OptimumData |  · [reviewed contract](#b0007) |
| [B0008 · 38–41](../../../../../src/planner/continuation_machine.hpp#L38) | Type/record definition: struct InfeasibleData |  · [reviewed contract](#b0008) |
| [B0009 · 42–46](../../../../../src/planner/continuation_machine.hpp#L42) | Type/record definition: struct CheckedCertificateData |  · [reviewed contract](#b0009) |
| [B0010 · 47–47](../../../../../src/planner/continuation_machine.hpp#L47) | Explanatory comments or spacing. |  |
| [B0011 · 48–51](../../../../../src/planner/continuation_machine.hpp#L48) | Type/record definition: enum class UnitEvent |  · [reviewed contract](#b0011) |
| [B0012 · 52–55](../../../../../src/planner/continuation_machine.hpp#L52) | Type/record definition: struct UnitResult |  · [reviewed contract](#b0012) |
| [B0013 · 56–61](../../../../../src/planner/continuation_machine.hpp#L56) | Type/record definition: struct UnitContext | returns !depth_ceiling \|\| desired &lt;= *depth_ceiling · [reviewed contract](#b0013) |
| [B0014 · 62–67](../../../../../src/planner/continuation_machine.hpp#L62) | Explanatory comments or spacing. | source comment (unverified): // step performs one saved cursor transition. Constructors allocate only inert · [reviewed contract](#b0014) |
| [B0015 · 68–83](../../../../../src/planner/continuation_machine.hpp#L68) | Type/record definition: class ValidationMachine | source comment (unverified): // step performs one saved cursor transition. Constructors allocate only inert · [reviewed contract](#b0015) |
| [B0016 · 84–90](../../../../../src/planner/continuation_machine.hpp#L84) | declares types or opens a type body. | source comment (unverified): // Producer choices and partition/scoping cursors remain private to exact.cpp. · [reviewed contract](#b0016) |
| [B0017 · 91–111](../../../../../src/planner/continuation_machine.hpp#L91) | Type/record definition: class ProducerMachine | source comment (unverified): // Exclusive producer protocol: retain pending candidates through witness/P02 publication, · [reviewed contract](#b0017) |
| [B0018 · 112–113](../../../../../src/planner/continuation_machine.hpp#L112) | Explanatory comments or spacing. | source comment (unverified): // Own candidate-to-tree copying across retries; returned complete tree ownership still needs · [reviewed contract](#b0018) |
| [B0019 · 114–128](../../../../../src/planner/continuation_machine.hpp#L114) | Type/record definition: class WitnessMachine | source comment (unverified): // Own candidate-to-tree copying across retries; returned complete tree ownership still needs · [reviewed contract](#b0019) |
| [B0020 · 129–130](../../../../../src/planner/continuation_machine.hpp#L129) | Explanatory comments or spacing. | source comment (unverified): // Independent replay publishes an owning CheckedProof only after whole-root success; · [reviewed contract](#b0020) |
| [B0021 · 131–148](../../../../../src/planner/continuation_machine.hpp#L131) | Type/record definition: class ReplayMachine | source comment (unverified): // Independent replay publishes an owning CheckedProof only after whole-root success; · [reviewed contract](#b0021) |
| [B0022 · 149–149](../../../../../src/planner/continuation_machine.hpp#L149) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::continuation_detail · [reviewed contract](#b0022) |

## B0001

[Lines 1–13](../../../../../src/planner/continuation_machine.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:bea24fbb44074de0709386c243c6d0e9cabbdf4fefb1092befecd7bdf87685a9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use #pragma once to suppress repeated header processing within a translation unit. Make #include "crown/planner/search.hpp", #include "crown/planner/verify.hpp", #include &lt;memory&gt;, #include &lt;optional&gt;, #include &lt;string_view&gt; available to src/planner/continuation_machine.hpp; open crown::planner::continuation_detail. Attached note: Validated input is copied/moved exactly once at facade admission. Machines share this immutable ownership, never references into caller-owned inputs. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0002

[Lines 14–18](../../../../../src/planner/continuation_machine.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BindingData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share one owned validated query/catalog snapshot among private continuation machines. |
| inputs / outputs | Catalog, Query and accounting-version tag. |
| invariants | Admission validates before constructing the immutable shared view; this aggregate performs no validation itself. |
| ownership | Owns deep model storage; machines retain shared_ptr&lt;const BindingData&gt; rather than caller borrows. |
| failure | Admission copies/allocations may fail before a machine starts. |
| cost | Copying the aggregate is size-dependent; subsequent shared ownership is not a deep copy. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0003

[Lines 19–21](../../../../../src/planner/continuation_machine.hpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L21:sha256:c264fa0989ab0fbed6e722422a070b6629ad80553e00b80e15d0823ee17e2014
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CheckedUpper: Only ValidationMachine constructs checked upper authority. A complete tree and complete report stay alive without copying either during publication. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CheckedUpper; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CheckedUpper come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0004

[Lines 22–27](../../../../../src/planner/continuation_machine.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CheckedUpper {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain independently checked tree feasibility and its measured native height. |
| inputs / outputs | Shared binding, tree, successful ValidationReport and height. |
| invariants | Only trusted validator publication establishes this private aggregate invariant; a valid upper supplies no lower bound. |
| ownership | Strong immutable owners keep tree/report/binding alive after the validator dies. |
| failure | Authority allocation precedes report.valid publication; no partial public authority on failure. |
| cost | Shared handle assembly avoids another tree/report copy; last-owner destruction remains proportional to retained data. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0005

[Lines 28–32](../../../../../src/planner/continuation_machine.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CheckedProof {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind an independently replayed certificate and its checked upper to original input. |
| inputs / outputs | Shared binding/proof/upper references. |
| invariants | Replay, not aggregate construction or producer intent, establishes proof validity for this binding/version. |
| ownership | Retains immutable proof/tree/report owners. |
| failure | Private callers must publish only after replay completion; incomplete or invalid replay gives no checked evidence. |
| cost | Handle assembly is fixed refcount work; replay/certificate storage are separate size-dependent costs. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0006

[Lines 33–33](../../../../../src/planner/continuation_machine.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IncumbentData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep a feasible upper while minimum-height search may still be incomplete. |
| inputs / outputs | Shared CheckedUpper. |
| invariants | Incumbent means valid feasible tree, not an optimum or maintenance-cost winner. |
| ownership | Retains the upper tree/report/input snapshot. |
| failure | Facade must provide checked non-null authority; this struct adds no runtime validator. |
| cost | Shared handle retention; no deep tree copy on creation. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0007

[Lines 34–37](../../../../../src/planner/continuation_machine.hpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OptimumData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Associate an incumbent with completed original-binding lower evidence. |
| inputs / outputs | Shared incumbent upper and HeightCertificate. |
| invariants | Trusted publication requires compatible upper and independently replayed complete proof; height optimality is structural, not execution-cost optimality. |
| ownership | Owns evidence through shared references, outliving search state. |
| failure | Unfinished proof or mere residual/prefix height must not construct this authority. |
| cost | Handle publication only; proof generation/replay and eventual evidence destruction keep their actual costs. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0008

[Lines 38–41](../../../../../src/planner/continuation_machine.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InfeasibleData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain completed proof that the original admissible family is empty. |
| inputs / outputs | Shared original binding and certificate. |
| invariants | No incumbent, timeout or prefix-only infeasibility establishes this invariant. |
| ownership | Keeps input/proof alive independently of session. |
| failure | Only trusted completed replay can publish it; aggregate construction does not check a proof. |
| cost | Fixed handle storage plus retained certificate/input population. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0009

[Lines 42–46](../../../../../src/planner/continuation_machine.hpp#L42); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CheckedCertificateData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Package replay results without conflating upper, optimum and infeasibility. |
| inputs / outputs | Checked proof and optional optimum/infeasibility authorities. |
| invariants | Consumers inspect which authority exists; a checked certificate view is not automatically an optimum. |
| ownership | Shares all retained evidence; no caller-owned references. |
| failure | Private facade publication must follow the corresponding completed checks. |
| cost | Fixed pointer fields; reachable evidence can be large and last-owner destruction is uncharged teardown. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0011

[Lines 48–51](../../../../../src/planner/continuation_machine.hpp#L48); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class UnitEvent {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name private machine transitions for the facade driver. |
| inputs / outputs | Advanced/candidate/completion/upper/proof/depth-blocked events. |
| invariants | Depth blockage requests allowance without accepting an upper/proof; only matching terminal events carry that authority. |
| ownership | Enum by value. |
| failure | Caller must interpret event with the producing machine, not infer success from any completion label. |
| cost | Fixed event transfer without owning payload. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0012

[Lines 52–55](../../../../../src/planner/continuation_machine.hpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct UnitResult {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return one private transition event and any blocked depth request. |
| inputs / outputs | Defaults advanced/depth0; depth_blocked carries needed depth. |
| invariants | This result does not charge work or active time itself. |
| ownership | Small value result; evidence remains in the machine owner. |
| failure | A blocked transition retains its logical next step for a later admitted call. |
| cost | Fixed event/depth fields, no allocation. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0013

[Lines 56–61](../../../../../src/planner/continuation_machine.hpp#L56); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct UnitContext {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test the admitted simultaneous-frame ceiling before a descent. |
| inputs / outputs | Optional size_t ceiling; permits(desired) accepts equality and nullopt. |
| invariants | Depth is saved-frame nesting, separate from breadth/frontier storage or total memory. |
| ownership | Value-only per-step context; machines do not borrow it after return. |
| failure | A denied ceiling is reported by the caller as depth_blocked before the descent commits. |
| cost | Fixed optional comparison, noexcept and no allocation. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0014

[Lines 62–67](../../../../../src/planner/continuation_machine.hpp#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L67:sha256:ebc6ad6c2fbfea50a5cbb2eab2041477d9a5ff3f8cb5e6a7f951f9d30885e147
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ValidationMachine: step performs one saved cursor transition. Constructors allocate only inert shells; no bulk preprocessing, search, validation or replay is hidden there. Throwing preparation precedes nonthrowing cursor publication. bad_alloc may escape step and leaves the same logical next transition retryable. The facade alone charges work/time; delegated child steps must not double-charge. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ValidationMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ValidationMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0015

[Lines 68–83](../../../../../src/planner/continuation_machine.hpp#L68); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ValidationMachine {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive independent tree-rule verification as retained private cursor state. |
| inputs / outputs | Immutable owned binding/tree in; step, report borrow, checked upper and active-depth read out. |
| invariants | Constructor is inert; steps check all structural rules, accumulate violations, and publish authority only after a complete valid pass. |
| ownership | Unique Impl owns scratch/report and shares input owners; report reference requires machine lifetime. Moved-from objects are destruction/assignment only. |
| failure | Throwing preparation precedes phase/index publication; allocation failure leaves the logical transition retryable. No bulk rollback layer is introduced. |
| cost | Each step has selected cursor work plus actual container/allocator/string costs; final owned-state destruction is outside step accounting. |
| Design | [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [Refactor.md §5.1–5.2](../../../../../Refactor.md) |

## B0016

[Lines 84–90](../../../../../src/planner/continuation_machine.hpp#L84); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L84-L90:sha256:79292defa3a82874accfae3a72d1ef185e8fd695d381e8b8d09959811a4d48d9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward-declare FrozenCandidate in src/planner/continuation_machine.hpp. Attached note: Producer choices and partition/scoping cursors remain private to exact.cpp. Replay shares no producer metadata, hierarchy, symmetry or enumeration code. Exclusive producer protocol: retain pending candidates through witness/P02 publication, then accept the upper and acknowledge. Exported proof needs independent replay. |
| inputs / outputs | A type alias or forward declaration has no runtime inputs or outputs; it gives following declarations a compile-time name. |
| invariants | The alias or incomplete type does not construct an object, validate data, or grant proof authority. |
| ownership | No runtime owner is created; any object lifetime comes from a later complete type and its members. |
| failure | Invalid or inconsistent type declarations fail compilation; no runtime failure is added. |
| cost | Compile-time name and type processing only; no runtime branch or allocation. |
| Design | [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0017

[Lines 91–111](../../../../../src/planner/continuation_machine.hpp#L91); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ProducerMachine {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the exclusive private protocol for resumable exact choice production. |
| inputs / outputs | Constructor retains admitted binding; step exposes candidate/complete/depth events. candidate/completed_proof return shared owners; statistics returns a borrowed reference. |
| invariants | Facade materializes and P02-checks a pending candidate, prepares incumbent ownership, calls accept_upper and only then acknowledges it. The exported certificate still requires independent replay. |
| ownership | Move-only Impl owner; immutable candidate/proof handles can outlive it, while statistics cannot outlive implementation replacement/destruction. |
| failure | Constructor/step allocation may throw for facade retry; depth stops retain pending work. Methods assume non-null admitted binding and a non-moved machine. |
| cost | Construction is inert apart from allocation; total producer work/memory can be exponential. Accessors copy scalars/handles or borrow counters rather than copying search state. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp) |

## B0018

[Lines 112–113](../../../../../src/planner/continuation_machine.hpp#L112); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L112-L113:sha256:a24a4bbc4cc2baab01e4bfd03daeab1ae396aa2ba25cf5c7cec65f332555e871
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for WitnessMachine: Own candidate-to-tree copying across retries; returned complete tree ownership still needs P02 validation before becoming an upper. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies WitnessMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for WitnessMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0019

[Lines 114–128](../../../../../src/planner/continuation_machine.hpp#L114); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class WitnessMachine {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the owned incremental materialization protocol for one frozen producer candidate. |
| inputs / outputs | Constructor retains binding/candidate; step constructs the concrete tree; tree returns an owning handle only after completion. |
| invariants | Copy completion confers no P02 validity. The next facade stage must validate the full tree before upper-bound publication. |
| ownership | Move-only Impl retains the arena-backed candidate; completed tree owners outlive the copier, while internal Choice reads remain borrowed. |
| failure | Inert construction/step can allocate; pending operations preserve retryable copying. Nonempty frame creation is depth-checked; moved-from methods are outside the private protocol. |
| cost | Materialization traverses all exported nodes/scopes/edges and keeps explicit coroutine frames; handle reads do not recopy the tree. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp) |

## B0020

[Lines 129–130](../../../../../src/planner/continuation_machine.hpp#L129); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L129-L130:sha256:fcbb99a1e24fbc678f69261c6350ccadf3815239d8f044a91989b7017034d9e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ReplayMachine: Independent replay publishes an owning CheckedProof only after whole-root success; phase/counters/message are observations. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ReplayMachine; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ReplayMachine come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0021

[Lines 131–148](../../../../../src/planner/continuation_machine.hpp#L131); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ReplayMachine {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the exclusive independent certificate-replay protocol and checked-authority boundary. |
| inputs / outputs | Constructor retains immutable binding/proof; step reconstructs/checks evidence; checked returns an owning CheckedProof only after root success; message returns a borrowed stable diagnostic view. |
| invariants | Upper validation, claim induction and full-root matching precede proof_valid. Resource/depth stops preserve incomplete work and establish neither minimum nor infeasibility. |
| ownership | Move-only Impl owns flat jobs/maps/cache; checked handles outlive it. Scalar accessors observe saved state and message does not allocate an owning string. |
| failure | Construction/step allocation may throw for facade retry; malformed proof returns terminal proof_invalid. Private methods require a live non-moved implementation. |
| cost | Independent exhaustive replay may be exponential and retain large port/claim caches; a delegated step is one metered transition, not a CPU/byte bound. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp) |

## B0022

[Lines 149–149](../../../../../src/planner/continuation_machine.hpp#L149); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L149-L149:sha256:1123fc5908e02d7bbfbdec2c7b0d816c8016869dd57b2906f553a96fa4a43a59
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::continuation_detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |
