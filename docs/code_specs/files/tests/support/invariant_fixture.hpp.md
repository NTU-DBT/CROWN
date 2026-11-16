# `tests/support/invariant_fixture.hpp` — block usage map

[Source](../../../../../tests/support/invariant_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `018274e9dab5508b6bc135b8ca6dea47d99506c0698665cb8ae279608271f7c7`. 99 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/support/invariant_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 15–15](../../../../../tests/support/invariant_fixture.hpp#L15) | Type/record definition: enum class Kind |  · [reviewed contract](#b0002) |
| [B0003 · 16–17](../../../../../tests/support/invariant_fixture.hpp#L16) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // All runtime alternatives delete copy and transfer concrete ownership on move. · [reviewed contract](#b0003) |
| [B0004 · 18–31](../../../../../tests/support/invariant_fixture.hpp#L18) | Callable definition: inline c02_test::Fixture fixture(unsigned flavor) | calls c02_test::fixture, std::string, Date::parse, Decimal::parse; returns f · [reviewed contract](#b0004) |
| [B0005 · 32–44](../../../../../tests/support/invariant_fixture.hpp#L32) | Callable definition: inline Owner make(const PhysicalPlan& plan,const Database& database,Kind kind,std::uint64_t cap=allowance) | calls owner, inputs, size, adapt_input; returns owner; PhysicalRuntime::initialize(plan,database,options); growth insert; 2 loop sites · [reviewed contract](#b0005) |
| [B0006 · 45–45](../../../../../tests/support/invariant_fixture.hpp#L45) | Callable definition: inline resource::MemoryAccount account(const Owner& owner) | calls std::visit, plan; returns std::visit(\[\](const auto& value){return value.plan().account() · [reviewed contract](#b0006) |
| [B0007 · 46–46](../../../../../tests/support/invariant_fixture.hpp#L46) | Callable definition: inline InvariantReport inspect(const Owner& owner,InspectionOptions limits={}) | calls std::visit, inspect_invariants; returns std::visit(\[&\](const auto& value){return value.inspect_invariants(limits) · [reviewed contract](#b0007) |
| [B0008 · 47–47](../../../../../tests/support/invariant_fixture.hpp#L47) | Callable definition: inline void check_invariants(const Owner& owner) | calls std::visit · [reviewed contract](#b0008) |
| [B0009 · 48–55](../../../../../tests/support/invariant_fixture.hpp#L48) | Callable definition: inline SupportRuntime& support(Owner& owner) | calls std::visit, constexpr, RuntimeTestProbe::support, RuntimeTestProbe::physical; returns std::visit(\[\](auto& value)-&gt;SupportRuntime& {; value · [reviewed contract](#b0009) |
| [B0010 · 56–56](../../../../../tests/support/invariant_fixture.hpp#L56) | Explanatory comments or spacing. | source comment (unverified): // key is an ordinary deep-owned Row; this value has no automatic restore action. · [reviewed contract](#b0010) |
| [B0011 · 57–57](../../../../../tests/support/invariant_fixture.hpp#L57) | Type/record definition: struct Corruption | source comment (unverified): // key is an ordinary deep-owned Row; this value has no automatic restore action. · [reviewed contract](#b0011) |
| [B0012 · 58–59](../../../../../tests/support/invariant_fixture.hpp#L58) | Explanatory comments or spacing. | source comment (unverified): // Canonical/key exports can allocate. The returned key copy follows the intentional · [reviewed contract](#b0012) |
| [B0013 · 60–70](../../../../../tests/support/invariant_fixture.hpp#L60) | Callable definition: inline Corruption corrupt(Owner& owner) | calls support, canonical_state, empty, c02_test::check; guard c02_test::check(chosen!=nullptr,"invariant fixture has no corruptible nonempty key");; returns {node,chosen-&gt;values,previous}; 3 loop sites; source comment (unverified): // Canonical/key exports can allocate. The returned key copy follows the intentional · [reviewed contract](#b0013) |
| [B0014 · 71–73](../../../../../tests/support/invariant_fixture.hpp#L71) | Callable definition: inline void restore(Owner& owner,const Corruption& corruption) | calls RuntimeTestProbe::set_satisfied, support · [reviewed contract](#b0014) |
| [B0015 · 74–82](../../../../../tests/support/invariant_fixture.hpp#L74) | Callable definition: template&lt;class Function&gt; void each(Function function) | calls fixture, c02_test::candidates, candidate_count, planner::lower_tree; 4 loop sites · [reviewed contract](#b0015) |
| [B0016 · 83–84](../../../../../tests/support/invariant_fixture.hpp#L83) | Explanatory comments or spacing. | source comment (unverified): // Explicit test IO: default ofstream flags are not checked here; corpus validation · [reviewed contract](#b0016) |
| [B0017 · 85–98](../../../../../tests/support/invariant_fixture.hpp#L85) | Callable definition: inline void export_reports(const std::filesystem::path& directory) | calls std::filesystem::create_directories, each, make, std::to_string; guard restore(owner,corruption);c02_test::check(inspect(owner).valid(),"fixture export failed to restore …; source comment (unverified): // Explicit test IO: default ofstream flags are not checked here; corpus validation · [reviewed contract](#b0017) |
| [B0018 · 99–99](../../../../../tests/support/invariant_fixture.hpp#L99) | Closes surrounding scope/type. | source comment (unverified): // namespace s05_inspection · [reviewed contract](#b0018) |

## B0001

[Lines 1–14](../../../../../tests/support/invariant_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr std::uint64_t allowance=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the default native query cap for the invariant diagnostic matrix. |
| inputs / outputs | allowance is64MiB; make accepts an explicit smaller cap for exact/one-under account tests. |
| invariants | This byte cap is distinct from finite indexed component/work limits, ordinary caller export allocations and process memory. |
| ownership | Inline constant, no account/control created until make. |
| failure | No intrinsic failure; actual account cap enforced by runtime storage ownership. |
| cost | Compile-time scalar, no instrumentation. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–15](../../../../../tests/support/invariant_fixture.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Kind {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate the three actual owner layers exercised by invariant tests. |
| inputs / outputs | support/physical/delta select logical-kernel, physical coordinator or Delta initialization. |
| invariants | Internal matrix supplies valid enum values; make's final branch handles Delta and does not separately validate arbitrary casts. |
| ownership | Inline tag owns no runtime. |
| failure | No own failure path; actual constructors can reject. |
| cost | Fixed enum value. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 16–17](../../../../../tests/support/invariant_fixture.hpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Owner=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own exactly one move-only actual runtime layer in a test-dispatch variant. |
| inputs / outputs | Variant alternatives are SupportRuntime, PhysicalRuntime and DeltaRuntime. |
| invariants | Each alternative deletes copy and supplies noexcept move; variant cannot copy runtime state. Moving transfers concrete runtime owner, and existing references remain tied to its actual implementation lifetime, not the moved-from variant. |
| ownership | Variant exclusively retains selected runtime handle/account/state; no ordinary snapshot clone or shared query-row copy. |
| failure | Construction may fail in actual owner admission; normal moves transfer owners without a new engine/account. Replacing variant can release the previous whole runtime graph. |
| cost | Fixed discriminant/owner move plus real teardown on replacement, not cloning rows; final destruction cost scales with retained state. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 18–31](../../../../../tests/support/invariant_fixture.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline c02_test::Fixture fixture(unsigned flavor)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build independent scalar/long-text populations for diagnostic ownership tests. |
| inputs / outputs | Flavor0 uses int64 R/S/T witness. Flavor1 changes x to a4096-byte string plus embedded NUL-tail and two S/T y values. Flavor2 is one string/bool/date/38-digit exact Decimal relation/atom. |
| invariants | Each ordinary catalog/query/database agrees on types; no UTF-8/text serializer requirement is imposed on native embedded NUL data. Expected optimum family is asserted later by actual c02 candidates (h2/count3 or flavor2 h1/count1). |
| ownership | Returns owning ordinary Fixture; strings/Decimal coefficients/Relation rows are copied into independent payload, not borrowed/shared native keys. |
| failure | Date/Decimal parsing or ordinary allocations can throw during setup; no fallback fixture or typed admission authority is created. |
| cost | Real long-string/Decimal/vector/set construction and copies. Native runtime/inspection allocation is not measured until actual owner and Scope windows later. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 32–44](../../../../../tests/support/invariant_fixture.hpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Owner make(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an actual owner layer under an explicit native byte allowance for diagnostics. |
| inputs / outputs | Sets support memory cap/transitions=false. Support starts empty and applies each accepted compiler adapt_input occurrence row as a logical set update; Physical uses initialize(plan,database); Delta initializes in delta mode with same physical options. |
| invariants | Support branch is logical replay, not physical source/derivation/FK coordination; duplicate logical keys follow set semantics. Normalized input adaptation remains production compiled behavior. Each public runtime import establishes its real query account, rather than using fixture DTOs as native owners. |
| ownership | Returns move-only Owner; native state/accounts own imported bytes. Support branch temporarily exports adapted tuple values into ordinary Row before native apply; input ordinary database/plan are borrowed or copied by actual constructors as defined. |
| failure | Build/adaptation/row/domain/account/work/update/allocation failures propagate; partial local runtime releases through RAII. Logical updates already applied to that unpublished local owner are not a public multi-input transaction. |
| cost | Real native program/storage/account setup and full row import/maintenance. Support additionally scans occurrences/base rows and adapts/exports each accepted row; no blanket fixed/no-allocation setup. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 45–45](../../../../../tests/support/invariant_fixture.hpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline resource::MemoryAccount account(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the actual chosen runtime's original account for diagnostic funding/lifetime checks. |
| inputs / outputs | Visits Owner and copies value.plan().account(). |
| invariants | This is one actual runtime account/ceiling, not compiler fixture memory or a replacement unlimited allowance. |
| ownership | Returned owning handle keeps account control readable after owner close; it does not retain all runtime rows itself. |
| failure | Moved/invalid owner access can reject; no handler/fallback. |
| cost | Fixed variant/member/shared-account access, no ledger scan or new account. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 46–46](../../../../../tests/support/invariant_fixture.hpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline InvariantReport inspect(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture the chosen actual owner's independent bounded invariant report. |
| inputs / outputs | Visits owner and returns value.inspect_invariants(limits). |
| invariants | Real inspector owns complete/partial diagnostics and original-account allocations; missing/partial facts are not considered valid. No canonical DTO is substituted for the actual owner. |
| ownership | Report owns funded issues/compact keys and numeric census independently; owner is borrowed synchronously. |
| failure | Bounded stops yield complete=false per inspector; actual allocation/account/native faults follow production semantics. No wrapper catch/retry. |
| cost | Full owner-specific expected-state recomputation/snapshots/regrouping and copied-key/report storage, not fixed variant dispatch alone. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 47–47](../../../../../tests/support/invariant_fixture.hpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void check_invariants(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the actual chosen owner's fail-fast invariant checker. |
| inputs / outputs | Visits owner and calls check_invariants(). |
| invariants | This is independent recomputation, not checking a cached report flag or skipped diagnostic when no issues. |
| ownership | Borrows stable actual owner; temporary expected sets/snapshots remain private under original account. |
| failure | Invariant/native/resource/account/allocation failures propagate; wrapper adds no catch or repair. |
| cost | Full owner-specific row/index/metadata recomputation and scratch allocation plus fixed variant dispatch. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 48–55](../../../../../tests/support/invariant_fixture.hpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline SupportRuntime& support(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual logical kernel regardless of selected test owner layer. |
| inputs / outputs | For Support returns itself; Physical uses RuntimeTestProbe::support; Delta unwraps Physical then Support. |
| invariants | Testing target/macro is required by runtime_probe. It does not clone owner state or create another native query/account. |
| ownership | Reference borrows Owner implementation; keep variant/runtime alive and do not replace it while using the reference. |
| failure | Invalid owner access propagates; no allocation/fallback or generic recovery. |
| cost | Fixed type/variant dispatch and nested references on success; no row/metadata export. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 56–56](../../../../../tests/support/invariant_fixture.hpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L56:sha256:006b23ec39a9964de75cff48ecf3b4840eb2fd634edf2e9197f70a51fa9f2424
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: key is an ordinary deep-owned Row; this value has no automatic restore action. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 57–57](../../../../../tests/support/invariant_fixture.hpp#L57); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Corruption {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the key and old counter needed to restore one intentional diagnostic corruption. |
| inputs / outputs | Contains NodeId, ordinary Row key and previous size_t satisfied count. |
| invariants | No automatic destructor restoration/transaction is provided. Ordinary Row copy deep-copies nested string/Decimal payload; this is not a borrowed pointer into canonical snapshot or shared native capture key. |
| ownership | Aggregate owns independent ordinary key bytes; copies can allocate, moves transfer Row ownership. It stores no runtime reference so restore requires the same actual owner explicitly. |
| failure | Key copying/allocation can fail; previously successful counter mutation is not rolled back by this value type. |
| cost | Inline IDs/count plus real Row/scalar byte storage; key copying costs fields/text, not O(1). |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 58–59](../../../../../tests/support/invariant_fixture.hpp#L58); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L59:sha256:50520ed55d7329f5fa71e56ed289097b61b766242303df310c212306bab6446e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Canonical/key exports can allocate. The returned key copy follows the intentional counter mutation, so this test helper does not promise exception rollback. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 60–70](../../../../../tests/support/invariant_fixture.hpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Corruption corrupt(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one localized satisfied-count inconsistency in actual native support state. |
| inputs / outputs | Captures canonical state, picks first nonempty record but prefers the last visited string-bearing record, requires a choice, sets satisfied to current+1 via actual probe, then returns copied key/node/previous value. |
| invariants | Known fixture counts fit size_t increment. Only one metadata field is deliberately invalidated; no legal source update/propagation/proof change is claimed. Return-key copying occurs after mutation, so this test helper does not promise a strong exception guarantee if that ordinary copy fails. |
| ownership | chosen pointer borrows local canonical DTO only during call; returned Corruption deep-copies ordinary Row before DTO dies. Native owner retains actual row state; previous count is inline. |
| failure | Canonical export/probe/key copy can throw; caller performs explicit restore after successful return, or discards local test owner on fixture failure. No hidden rollback/new handler. |
| cost | Full canonical snapshot/ordinary row/text copies and scan, then keyed probe with possible funded operation/key construction, then another returned key copy; intentionally not allocation-free. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 71–73](../../../../../tests/support/invariant_fixture.hpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void restore(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly restore the one saved test-corrupted satisfied count. |
| inputs / outputs | Resolves actual Support kernel and invokes set_satisfied(node,key,previous), discarding exchanged value. |
| invariants | Requires same still-live owner/key and no intervening record replacement; restores only this field, not an arbitrary corruption transaction or source/history proof. |
| ownership | Borrows independent Corruption key and actual runtime for synchronous lookup; no returned owner. |
| failure | Readiness/missing-key/native work/account/key construction failure propagates; no automatic retry/recovery. |
| cost | Probe's actual indexed operation/key copy/lookup cost plus fixed exchange; no complete invariant recomputation until caller requests it. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 74–82](../../../../../tests/support/invariant_fixture.hpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Function> void each(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive the complete42-case fixture matrix with actual proof/lowering and caller-owned operations. |
| inputs / outputs | For flavors0/1 builds h2/count3 actual family, flavor2 h1/count1; for reference/indexed backend and each actual candidate shape lowers plan, then calls Function for support/physical/delta with plan/database. |
| invariants | Total (3+3+1)*2*3=42. Function must not retain borrowed plan/database references beyond their loop lifetime. No case is silently sampled/truncated or labeled proved without actual c02 candidates. |
| ownership | Function is copied by value (actual callers use lightweight captured lambdas), each plan/fixture owns its data during calls; callbacks create/own runtimes as needed. |
| failure | Proof/lowering/callback/allocation errors propagate and abort matrix; no handler or test skip. |
| cost | Actual search/enumeration,14 plan lowerings and42 callback invocations; callback diagnostic/IO/native allocation costs are additional, not hidden constant dispatch. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 83–84](../../../../../tests/support/invariant_fixture.hpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L84:sha256:7a348813f9825ee3bde2e4f9e03a12cecdccb68abcd7c38493cb46bb6c4fc4c4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Explicit test IO: default ofstream flags are not checked here; corpus validation must detect missing/truncated files. Production runtime code does not use this path. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 85–98](../../../../../tests/support/invariant_fixture.hpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void export_reports(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export healthy/corrupt/limited diagnostic examples for every matrix case without changing library behavior. |
| inputs / outputs | Creates directory, then each case constructs actual owner and writes healthy, corrupt, zero-work, zero-issue and half-healthy-work partial JSON reports under deterministic names, restores corruption and asserts valid. |
| invariants | Expected210 phase files over42cases; healthy report is also captured separately to choose partial limit. This helper is only explicit test export. ofstream default state is not checked and exceptions are not enabled, so helper alone does not guarantee every write/close reached disk. |
| ownership | Owners/reports/keys use actual native and ordinary owners as documented; io export builds ordinary caller JSON/text outside query account. Callback borrows loop plan/database synchronously. |
| failure | Filesystem create, inspection/export/allocation/probe/check errors propagate. Stream write failure can remain a stream flag; external corpus checking must detect missing/truncated files. Restoration is explicit, not automatic on an exception. |
| cost | 42 real owner builds, multiple full inspections per phase, ordinary JSON serialization/file IO and keyed corruption/restore; no native timing/space acceptance or hidden production instrumentation. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 99–99](../../../../../tests/support/invariant_fixture.hpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L99:sha256:873a7fc564598aff6e8db88dc8f7d8f990db8586487b53aa4b2cf70d8044d749
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in invariant_fixture.hpp: namespace s05_inspection. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/code_review.md](../../../../code_review.md) |
