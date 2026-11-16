# `tests/unit/ranking_evidence_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/ranking_evidence_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `da1e45b2cf6797855d59194b4f04e789050c85742c2438ca4611ea5da48da8a6`. 246 lines partitioned into 26 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 18–18](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L18) | Type/record definition: enum class Phase |  · [reviewed contract](#b0002) |
| [B0003 · 19–21](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L19) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message) { · [reviewed contract](#b0003) |
| [B0004 · 22–26](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L22) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(current.allocations==1 && current.requested_bytes==resource::MemoryAccount::control_bytes(), · [reviewed contract](#b0004) |
| [B0005 · 27–29](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L27) | Callable definition: PhysicalPlan plan(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates,bool indexed) | calls planner::lower_tree, candidate, tree, s04_runtime::options; returns planner::lower_tree(f.catalog,f.query,candidates.candidate(0)-&gt;tree(),indexed?s04_runtime::options(… · [reviewed contract](#b0005) |
| [B0006 · 30–32](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L30) | Callable definition: workload::Options collection(bool enabled) | calls ; returns result · [reviewed contract](#b0006) |
| [B0007 · 33–35](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L33) | Callable definition: PhysicalRuntimeOptions physical_options(std::uint64_t cap) | calls ; returns result · [reviewed contract](#b0007) |
| [B0008 · 36–38](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L36) | Callable definition: DeltaOptions delta_options(std::uint64_t cap) | calls physical_options; returns result · [reviewed contract](#b0008) |
| [B0009 · 39–39](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L39) | Type/record definition: struct Facts |  · [reviewed contract](#b0009) |
| [B0010 · 40–53](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L40) | Type/record definition: struct PhysicalFixture | guard void stable() const {check(runtime.sequence()==1,"evidence capture changed physical epoch");}; returns runtime.plan().account(); {runtime.owner().value,Phase::ready,enabled,wanted,false}; growth insert · [reviewed contract](#b0010) |
| [B0011 · 54–67](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L54) | Type/record definition: struct DeltaFixture | guard void stable() const {check(runtime.sequence()==1 && runtime.state()==DeltaState::ready,"evidence ca…; returns runtime.plan().account(); {runtime.owner().value,Phase::ready,enabled,wanted,false}; growth insert · [reviewed contract](#b0011) |
| [B0012 · 68–88](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L68) | Type/record definition: struct SessionFixture | guard check(session-&gt;enqueue(input)==io::Admission::accepted,"ranking session input rejected");session-&gt;s…; returns session.get_deleter().account(); {session-&gt;report_metadata().owner().value,phase,enabled,wanted,tru…; growth insert · [reviewed contract](#b0012) |
| [B0013 · 89–109](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L89) | Callable definition: void verify(const rr::RuntimeEvidence& evidence,Facts facts,const resource::MemoryAccount& account) | calls inputs, rd::Factory::data, check, identity; guard check(inputs.identity().owner==facts.owner && inputs.identity().epoch==1,"retained ranking owner/ep…; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 110–112](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L110) | Callable definition: rr::RuntimeEvidence accepted(rr::CaptureAttempt attempt) | calls check, has_value; guard check(attempt.stop==pr::Stop::complete && attempt.evidence.has_value(),"ranking memory fixture capt…; returns *attempt.evidence · [reviewed contract](#b0014) |
| [B0015 · 113–113](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L113) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |
| [B0016 · 114–116](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L114) | Callable definition: Owners owners(const resource::MemoryAccount& account) | calls size, statistics_for; returns result; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 117–132](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L117) | Callable definition: template&lt;class Make&gt; void requests_and_lifetime(Make make) | calls make, fixture, account, facts; guard check(calls&gt;0 && calls==after.successful_allocations-before.successful_allocations && retained==aft…; returns owned_after\[i\].allocations-owned_before\[i\].allocations; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 133–147](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L133) | Callable definition: template&lt;class Make&gt; std::size_t persistent(Make make) | calls make, account, facts, accepted; guard check(expected&gt;0 && expected&lt;2048,"invalid ranking fault-sweep request count");std::size_t failures…; returns failures; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 148–171](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L148) | Callable definition: template&lt;class Make&gt; std::pair&lt;std::uint64_t,std::size_t&gt; caps(Make make) | calls make, account, reserve, statistics; guard check(peak&gt;0 && pins&gt;0,"ranking captures never exceeded the earlier setup peak");; returns {peak,pins}; growth push_back, reserve; 3 loop sites · [reviewed contract](#b0019) |
| [B0020 · 172–177](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L172) | Callable definition: template&lt;class Make&gt; void run(Make make,std::string_view label,bool cap_test=true) | calls requests_and_lifetime, persistent, caps · [reviewed contract](#b0020) |
| [B0021 · 178–178](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L178) | Type/record definition: struct BindingFixture |  · [reviewed contract](#b0021) |
| [B0022 · 179–192](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L179) | Callable definition: BindingFixture binding_fixture(bool invalid_utf8=true) | calls std::string, Date::parse, Decimal::parse, std::move; returns {std::move(catalog),std::move(query),std::move(tree)} · [reviewed contract](#b0022) |
| [B0023 · 193–212](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L193) | Callable definition: template&lt;class C,class Q&gt; std::size_t binding_checks(const C& catalog,const Q& query,std::string_view expected,const resource::Me… | calls size, budget, legacy_budget, rd::binding; guard check(std::string_view(*encoded)==expected && legacy==expected && budget.usage.work==legacy_budget.…; returns calls; 1 loop sites · [reviewed contract](#b0023) |
| [B0024 · 213–228](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L213) | Callable definition: void bindings() | calls binding_fixture, planner::frozen_binding_v2::binding_bytes, resource::MemoryAccount::create, binding_checks; guard try{const auto encoded=rd::binding(f.catalog,f.query,budget,bounded);check(std::string_view(encoded…; 1 loop sites · [reviewed contract](#b0024) |
| [B0025 · 229–229](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L229) | Closes surrounding scope/type. |  · [reviewed contract](#b0025) |
| [B0026 · 230–246](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L230) | Callable definition: int main() | calls bindings, c02_test::fixture, c02_test::candidates, run; returns PhysicalFixture(f,candidates,indexed,true,true,cap); DeltaFixture(f,candidates,indexed,true,true,ca…; 3 loop sites · [reviewed contract](#b0026) |

## B0001

[Lines 1–17](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:79caa6f9052144fe4bfa558d5f8a4147dc381988db9442b520a40973cccb9019
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_evidence_memory_test.cpp: include "ranking_fixture.hpp", "indexed_runtime_fixture.hpp", "crown/runtime/ranking_evidence.hpp", "ranking_detail.hpp", "frozen_binding_v2.hpp", "index_allocation.hpp", &lt;array&gt;, &lt;iostream&gt;, &lt;optional&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–18](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Phase {ready,pending,stopped,dropped};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the lifecycle phase used when validating ranking evidence. |
| inputs / outputs | A SessionFixture uses ready, pending, stopped, or dropped; physical and Delta fixtures are always ready. |
| invariants | Pending means a private erase has begun but has not been committed; dropped runtime evidence is released while session metadata remains. |
| ownership | Scalar test enum only. |
| failure | Session construction/check assertions fail if the requested phase cannot be established. |
| cost | Fixed scalar; its phase dimension is repeated in eight session combinations across both backends. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/memory_accounts.md §Native runtime ranking evidence](../../../../memory_accounts.md) |

## B0003

[Lines 19–21](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a test failure when a ranking evidence predicate is false. |
| inputs / outputs | Accept a boolean and borrowed diagnostic text; return on true or throw std::runtime_error on false. |
| invariants | Does not mutate ranking state. |
| ownership | The message view borrows the call-site string; only a failure constructs an exception. |
| failure | A false check propagates to main's std::exception handler. |
| cost | One conditional; diagnostic string work occurs only on failure. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp) |

## B0004

[Lines 22–26](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify final ranking evidence release leaves only the account controller. |
| inputs / outputs | Run account.check_invariants, then require current allocation count 1 and requested bytes equal control_bytes. |
| invariants | Called after fixture and all retained evidence/value aliases are reset. |
| ownership | Borrows account and retains no evidence. |
| failure | Invariant mismatch fails the test; no repair or allowance refill occurs. |
| cost | check_invariants checks controller totals and traverses the linked payload-allocation list. At a passing controller-only boundary that list is empty; the controller is counted separately, not scanned as one list entry. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/memory_accounts.md §Native runtime ranking evidence](../../../../memory_accounts.md) |

## B0005

[Lines 27–29](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates,bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower candidate zero into the selected reference or indexed physical plan. |
| inputs / outputs | Borrow the source fixture and candidate snapshot; return lower_tree using the first candidate tree and indexed fixture options when requested. |
| invariants | The test does not compare all members of the three-candidate family; runtime evidence is bound to this selected compiled plan. |
| ownership | Catalog/query/candidate are borrowed during lowering; returned plan owns its lowered data. |
| failure | Invalid candidate access or plan lowering may throw before evidence checks. |
| cost | Lower the selected tree and backend metadata; initialize mutable runtime indexes later in the fixture constructor. This helper does not enumerate the candidate family. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0006

[Lines 30–32](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
workload::Options collection(bool enabled)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose counter collection or off mode for runtime ranking evidence fixtures. |
| inputs / outputs | Return workload::Options with mode counters when enabled and off otherwise. |
| invariants | Disabled mode is used only in delta optional-fact controls; other matrix fixtures collect counters. |
| ownership | Returns a value; runtime/session owns collector state. |
| failure | No local failure path. |
| cost | One enum selection; capture later scans the actual workload snapshot. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [docs/ranking.md §Runtime evidence allocation ownership](../../../../ranking.md) |

## B0007

[Lines 33–35](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntimeOptions physical_options(std::uint64_t cap)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the query account byte cap for the ranking physical fixture. |
| inputs / outputs | Copy the byte cap into support memory_limit_bytes and turn off transition capture. |
| invariants | The account cap is distinct from ranking logical work/byte budgets. |
| ownership | Options are a value; the runtime created from them owns its account. |
| failure | Runtime initialization may reject an insufficient cap. |
| cost | Small options construction; it does not reserve cap-sized storage. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0008

[Lines 36–38](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions delta_options(std::uint64_t cap)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure maintenance-mode DeltaRuntime with the same physical account limit. |
| inputs / outputs | Build physical options from cap, assign them to DeltaOptions, and select maintenance mode. |
| invariants | The test uses a fixed 64 MiB initial account then measured peak and one-under accounts; no logical refill is configured. |
| ownership | Returned options value has no retained storage. |
| failure | Insufficient account admission can fail during runtime construction. |
| cost | Small value copy; runtime initialization and capture costs occur elsewhere. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0009

[Lines 39–39](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Facts {std::uint64_t owner;Phase phase;bool enabled,wanted,session;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry expected capture identity, phase, collection, source-request, and owner type. |
| inputs / outputs | Store owner ID, Phase, enabled/wanted flags, and whether the evidence came through QuerySession. |
| invariants | These expected facts come from the configured fixture; they do not imply every condition is checked for every branch. |
| ownership | Scalar fields only; no plan or evidence ownership. |
| failure | No local failure path. |
| cost | Fixed-size aggregate copied by value. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [docs/memory_accounts.md §Native runtime ranking evidence](../../../../memory_accounts.md), [docs/ranking.md §Runtime evidence allocation ownership](../../../../ranking.md) |

## B0010

[Lines 40–53](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalFixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one initialized PhysicalRuntime and adapt it to the common capture/lifetime checks. |
| inputs / outputs | Build the selected plan/database under cap, configure workload counters, apply one duplicate insert, expose its account/facts, call rr::capture with source_cardinalities=wanted, and verify sequence remains 1. |
| invariants | The candidate snapshot is held by reference and must outlive the fixture. The inserted row is already present, so the expected committed input is a no-op. |
| ownership | Runtime owns query-account data; candidates are borrowed; returned CaptureAttempt owns evidence only when complete. |
| failure | Initialization/apply can throw; capture itself translates its supported failures to CaptureAttempt. |
| cost | Construction lowers/initializes one plan and applies one small update; capture includes binding, input census, source selection, statistics capture, and retained evidence allocations. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/memory_accounts.md §Native runtime ranking evidence](../../../../memory_accounts.md), [docs/ranking.md §Runtime evidence allocation ownership](../../../../ranking.md) |

## B0011

[Lines 54–67](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L54); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaFixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one committed DeltaRuntime and expose the same capture interface as PhysicalFixture. |
| inputs / outputs | Initialize from candidate zero, configure workload counters, begin/drain/commit/discard one duplicate insert, then call rr::capture and verify sequence 1/ready. |
| invariants | The committed event increments input/noop census without changing stored row membership; candidates remain borrowed. |
| ownership | DeltaRuntime owns its account and state; CaptureAttempt owns the returned evidence graph when complete. |
| failure | Initialization or update processing may throw; capture status is returned in CaptureAttempt. |
| cost | Setup processes one small update; capture work includes binding and census loops plus source/state capture and evidence allocations. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/memory_accounts.md §Native runtime ranking evidence](../../../../memory_accounts.md) |

## B0012

[Lines 68–88](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L68); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionFixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one QuerySession and create the requested ranking evidence lifecycle boundary. |
| inputs / outputs | Configure workload mode; enqueue/start/begin/drain one duplicate insert; for pending, begin an undrained erase; for stopped/drop, invoke the lifecycle method; capture against the actual session. |
| invariants | Committed sequence remains 1. Pending state sets pending reasons; stopped retains runtime; dropped returns released ranking facts plus session context. |
| ownership | QuerySession::Owner custom deleter owns session/account; candidate snapshot is borrowed and outlives the fixture. |
| failure | Queue/start/begin assertions, runtime setup, or lifecycle transitions can fail before capture; capture returns status. |
| cost | Setup processes one committed input and at most one pending input. Stop/drop have lifecycle cost; repeated fixture construction is part of the test matrix. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/memory_accounts.md §Native runtime ranking evidence](../../../../memory_accounts.md) |

## B0013

[Lines 89–109](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(const rr::RuntimeEvidence& evidence,Facts facts,const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check retained evidence identity, source-account allocators, committed input census, optional sources, and phase reasons. |
| inputs / outputs | Read the Evidence input value, compare owner/epoch and allocators for binding/weights/sources/observations, then assert enabled/disabled and wanted/not-captured facts. |
| invariants | For live enabled captures, require three weight entries, denominator 1 and the first entry insert/noop counters equal 1; pending additionally checks its depth reason. Requested nonpending source capture requires three observations/cardinality records with each rows=1. Pending source values are not asserted. Dropped requires released depth/memory reasons and returns after identity/allocator/optional-capture checks. |
| ownership | The evidence and its child Evidence share immutable account-funded storage; account is borrowed for allocator equality. |
| failure | Any mismatch throws through check. It does not normalize missing facts into success. |
| cost | Fixed allocator/identity/size checks and reads of the first weight entry. The requested nonpending source branch loops over three cardinality records; it does not scan all weight payloads. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [docs/memory_accounts.md §Native runtime ranking evidence](../../../../memory_accounts.md), [docs/ranking.md §Runtime evidence allocation ownership](../../../../ranking.md) |

## B0014

[Lines 110–112](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
rr::RuntimeEvidence accepted(rr::CaptureAttempt attempt)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a completed capture and unwrap its immutable evidence handle. |
| inputs / outputs | Accept CaptureAttempt by value; require stop=complete and evidence present, then return the handle. |
| invariants | Partial/failed captures cannot be treated as evidence. |
| ownership | Return a copied shared RuntimeEvidence handle from *attempt.evidence. The by-value attempt is temporary; shared immutable storage remains on its original account. |
| failure | A noncomplete stop or absent value throws through check. |
| cost | One status/presence check and shared-handle copy; no evidence-array copy or new account. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |

## B0015

[Lines 113–113](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L113); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L113-L113:sha256:d0a5ebc64e1a16132295e260cdf601649325658bc01cb251572da5b130da8957
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_evidence_memory_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 114–116](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Owners owners(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the eleven capture-attribution current usages checked by ranking memory tests. |
| inputs / outputs | Call statistics_for for capture owner IDs 0 through 10 and return the copied MemoryUsage rows. |
| invariants | These numeric indices are MemoryAttribution categories, distinct from Facts.owner runtime owner IDs and not an owner identity. The range includes session context, combined, report captures, evidence owner 9, and RuntimeEvidence shared control owner 10. |
| ownership | Returns copied counters; the MemoryAccount is borrowed. |
| failure | Invalid account/attribution fails in the account API. |
| cost | Eleven statistics_for calls each walk the full live allocation list, O(11A) for A outstanding blocks; the fixed loop itself has eleven steps. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/memory_accounts.md §Native runtime ranking evidence](../../../../memory_accounts.md) |

## B0017

[Lines 117–132](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> void requests_and_lifetime(Make make)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile successful ranking capture requests/attributions and retained evidence lifetime. |
| inputs / outputs | Capture under s04_alloc::Scope; compare global-new calls, successful account allocations and current requested bytes; inspect owners 9/10; copy RuntimeEvidence and Evidence handles; close fixture, verify held facts, then release aliases. |
| invariants | The test expects at least two evidence-owner allocations and one RuntimeEvidence control. Ready+enabled+wanted expects exactly five owner-9 allocations: evidence control, binding, weights, sources, and observations. Shared handle copies expect zero covered new calls. |
| ownership | Held RuntimeEvidence/Evidence remain readable after fixture closure and retain original account data until final alias release. |
| failure | Checks fail on mismatched observed requests/attributions or release. The hook counts covered replacement C++ new attempts; replacement delete frees storage but is not counted, and direct malloc/RSS are outside the tracker. |
| cost | One capture and two attribution snapshots, each with 11 full linked-block scans (22 scans total), plus an 11-element delta sum; capture allocation count varies by facts/phase. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/memory_accounts.md §Native runtime ranking evidence](../../../../memory_accounts.md) |

## B0018

[Lines 133–147](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> std::size_t persistent(Make make)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject failure at every measured allocation position in retained ranking evidence capture. |
| inputs / outputs | Keep one old evidence handle, calibrate N covered allocation attempts, then sweep points 0..N; each earlier point requires Stop::allocation_failure/no evidence/current usage unchanged before retry, and the last point requires complete capture. |
| invariants | The public runtime capture is noexcept and translates bad_alloc to allocation_failure in CaptureAttempt; no partial winner is published. N must be below 2048. |
| ownership | The old handle remains alive throughout; failed private evidence is released, and the successful retry/new handle is checked with the original account. |
| failure | Capture status is checked at every point; unexpected exceptions or retained-byte changes fail the test. |
| cost | Two initial captures retain old evidence and calibrate N. Then N+1 fault-position attempts plus N healthy retries run, with account-invariant scans per iteration. Work depends on partial/full capture, census and current allocation blocks. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/memory_accounts.md §Native runtime ranking evidence](../../../../memory_accounts.md) |

## B0019

[Lines 148–171](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> std::pair<std::uint64_t,std::size_t> caps(Make make)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calibrate evidence peak growth and verify exact/one-under original account limits. |
| inputs / outputs | Hold successful evidence until peak bytes grow (at most 2048 captures), then pin the measured number under exact and peak-1 caps; one-under must return allocation_failure without changing current bytes, then release one pin and retry. |
| invariants | Retry uses the same peak-1 limit; it does not mint a new account or increase allowance. Error is a CaptureAttempt status rather than MemoryFailure escaping. |
| ownership | Each held RuntimeEvidence retains arrays and controls charged to the original plan account until released. |
| failure | Any unexpected stop, leak, wrong cap, or released-data mismatch fails check. |
| cost | Calibration performs up to 2048 complete evidence captures; two cap fixtures then pin/release captures and attempt a boundary capture, with retry only on one-under. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/memory_accounts.md §Native runtime ranking evidence](../../../../memory_accounts.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0020

[Lines 172–177](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> void run(Make make,std::string_view label,bool cap_test=true)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply shared request/lifetime and persistent-failure checks, optionally adding cap tests. |
| inputs / outputs | Invoke requests_and_lifetime and persistent for one fixture factory; print failure count and, when enabled, measured peak/pins. |
| invariants | cap_test=false is used by optional source/workload fact controls; these still run capture/lifetime and persistent fault checks. |
| ownership | All fixture/evidence lifetimes are handled by the delegated helpers. |
| failure | Any helper failure propagates to main. |
| cost | Runs one successful lifetime case and the dynamic N-position fault sweep; cap mode adds up to 2048 calibration captures and two cap checks. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [docs/memory_accounts.md §Native runtime ranking evidence](../../../../memory_accounts.md) |

## B0021

[Lines 178–178](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L178); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BindingFixture {Catalog catalog;Query query;FreeConnexTree tree;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the compiler DTO input used for frozen binding bytes. |
| inputs / outputs | Stores one Catalog, Query, and one-node native FreeConnexTree by value. |
| invariants | Its strings/scalars include embedded NUL and invalid UTF-8 only when selected by binding_fixture; this fixture tests binary encoding, not SQL text validity. |
| ownership | Owns the copied compiler DTO graph. |
| failure | Constructing the contained DTO strings/vectors may allocate and propagate ordinary setup failures; this declaration adds no catch or account admission. |
| cost | Cost follows the fixed small DTO and its attribute/name bytes; it is setup for binding checks. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp) |

## B0022

[Lines 179–192](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
BindingFixture binding_fixture(bool invalid_utf8=true)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a catalog/query with binary strings and representative typed constants for binding coverage. |
| inputs / outputs | Create a 163-byte raw name ending in NUL plus either invalid UTF-8 0xff or valid b, with enforced/untrusted constraints, stats, key hints, and int64/string/bool/date/decimal constants; return a one-node tree. |
| invariants | source schema version 13 and catalog version 7 are fixture facts. The invalid-byte case is kept separate from the valid-native compiled-program case. |
| ownership | Returned Catalog/Query/Tree own their strings and nested values. |
| failure | Scalar/date/decimal construction may reject invalid constants; the fixture uses accepted values. |
| cost | Setup copies a fixed 163-byte raw name plus small metadata/DTO vectors; no query account exists until bindings creates one. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp) |

## B0023

[Lines 193–212](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class C,class Q> std::size_t binding_checks(const C& catalog,const Q& query,std::string_view expected,const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare native account-backed evidence binding with legacy encoding, frozen bytes, and persistent allocation behavior. |
| inputs / outputs | Encode once with ordinary Budget and once with account-backed rd::binding, compare bytes and logical work/key/payload counters, verify allocator/account attribution, sweep every covered allocation point with retry, then prove zero payload admission stops before allocation. |
| invariants | Frozen bytes remain version-2 exact; logical binding/payload admission is distinct from actual account requested-byte admission. A zero-payload stop leaves binding-key usage zero. |
| ownership | Native EvidenceText uses the supplied account allocator; each retry uses a fresh Budget and failed text storage must return to baseline. |
| failure | rd::Failure byte_limit is expected before allocation at zero cap; injected std::bad_alloc is expected only at covered positions. |
| cost | One legacy and one initial native encode precede N+1 fault-position attempts plus N healthy retries; a zero-cap refusal follows. Successful encodes traverse catalog/query fields and scalar bytes, while injected attempts can stop partway. Work follows input size and observed allocation count. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [docs/ranking.md §Runtime evidence allocation ownership](../../../../ranking.md) |

## B0024

[Lines 213–228](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void bindings()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise standalone and compiled-plan native binding under exact/one-under memory caps. |
| inputs / outputs | Generate frozen v2 expected bytes and run binding_checks on the binary DTO form. Test exact/one-under account caps for that DTO form only. Separately lower the valid-UTF8 form into CompiledProgram, run binding_checks with its native catalog/query/account, then clear the program. |
| invariants | The first case includes arbitrary binary name bytes; the CompiledProgram case uses valid UTF-8 and is separately lowered. Captured bytes are compared with frozen v2 output. |
| ownership | EvidenceText values are destroyed before controller_only checks a still-live account handle. The compiled form keeps its program/account until native is cleared; native_account then retains only its controller. |
| failure | Wrong cap classification, changed bytes, or leaked account storage throws. |
| cost | Two binding_checks sweeps cover DTO and compiled-native forms. Two additional direct cap encodes test exact/one-under admission on the DTO form; the compiled form has no second cap loop. Program lowering is separate setup work. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/memory_accounts.md §Native runtime ranking evidence](../../../../memory_accounts.md) |

## B0025

[Lines 229–229](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L229); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L229-L229:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ranking_evidence_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 230–246](../../../../../tests/unit/ranking_evidence_memory_test.cpp#L230); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the ranking evidence matrix, optional-fact controls, binding cases, and exception boundary. |
| inputs / outputs | Run binding cases; build one three-table query, exact optimum and exhausted three-candidate family; for reference/indexed backends run Physical, Delta, four session phases, and three optional-fact Delta combinations. |
| invariants | The matrix contains 18 capture fixtures: 2 physical, 2 delta, 8 session, and 6 optional-fact cases. Cap sweeps run for the 12 physical/delta/session fixtures, not the six optional controls. |
| ownership | The candidate snapshot is retained by main and borrowed by each fixture. Captured values own immutable evidence/facts on the runtime account. |
| failure | std::exception from fixtures, captures, or checks is printed and returns 1. |
| cost | Exact search sets producer/replay work caps to 50,000,000 each. Exact search and candidate provider advance in grants of 1,000 work units with a guard of 100,000 iterations each; provider retains its default limits. Eighteen fixture profiles run lifetime/fault sweeps and twelve also run peak/cap checks. This source-only packet executes none. |
| Design | [tests/unit/ranking_evidence_memory_test.cpp](../../../../../tests/unit/ranking_evidence_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [docs/memory_accounts.md §Native runtime ranking evidence](../../../../memory_accounts.md), [docs/ranking.md §Runtime evidence allocation ownership](../../../../ranking.md) |
