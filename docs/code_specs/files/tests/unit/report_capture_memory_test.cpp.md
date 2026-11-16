# `tests/unit/report_capture_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/report_capture_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `77c148affde0f7c8330b94f86f191957bf89db97122f66c1946f335bc9b9a07d`. 217 lines partitioned into 31 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/unit/report_capture_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 18–18](../../../../../tests/unit/report_capture_memory_test.cpp#L18) | Type/record definition: enum class Kind |  · [reviewed contract](#b0002) |
| [B0003 · 19–19](../../../../../tests/unit/report_capture_memory_test.cpp#L19) | Type/record definition: enum class Phase |  · [reviewed contract](#b0003) |
| [B0004 · 20–21](../../../../../tests/unit/report_capture_memory_test.cpp#L20) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 22–22](../../../../../tests/unit/report_capture_memory_test.cpp#L22) | Callable definition: void check(bool ok,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool ok,std::string_view message){if(!ok)throw std::runtime_error(std::string(message));} · [reviewed contract](#b0005) |
| [B0006 · 23–26](../../../../../tests/unit/report_capture_memory_test.cpp#L23) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(value.allocations==1 && value.requested_bytes==resource::MemoryAccount::control_bytes(),"reta… · [reviewed contract](#b0006) |
| [B0007 · 27–36](../../../../../tests/unit/report_capture_memory_test.cpp#L27) | Callable definition: PhysicalPlan plan(bool indexed) | calls planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{}) · [reviewed contract](#b0007) |
| [B0008 · 37–40](../../../../../tests/unit/report_capture_memory_test.cpp#L37) | Callable definition: DeltaOptions options(std::uint64_t cap) | calls ; returns result · [reviewed contract](#b0008) |
| [B0009 · 41–41](../../../../../tests/unit/report_capture_memory_test.cpp#L41) | Callable definition: ws::Options enabled() | calls ; returns result · [reviewed contract](#b0009) |
| [B0010 · 42–42](../../../../../tests/unit/report_capture_memory_test.cpp#L42) | Type/record definition: struct Facts |  · [reviewed contract](#b0010) |
| [B0011 · 43–68](../../../../../tests/unit/report_capture_memory_test.cpp#L43) | Callable definition: void verify(const Value& value,Facts facts) | calls std::visit, constexpr, check, owner; guard if constexpr(std::is_same_v&lt;T,obs::ModeDescriptor&gt;)check(report.owner()==facts.owner && report.sequ… · [reviewed contract](#b0011) |
| [B0012 · 69–72](../../../../../tests/unit/report_capture_memory_test.cpp#L69) | declares types or opens a type body. |  · [reviewed contract](#b0012) |
| [B0013 · 73–77](../../../../../tests/unit/report_capture_memory_test.cpp#L73) | Callable definition: RuntimeFixture(bool indexed,Kind k,std::uint64_t cap):runtime(DeltaRuntime::initialize(plan(indexed),owner_fixture::database(),op… | calls runtime, DeltaRuntime::initialize, plan, owner_fixture::database; growth insert · [reviewed contract](#b0013) |
| [B0014 · 78–78](../../../../../tests/unit/report_capture_memory_test.cpp#L78) | Callable definition: resource::MemoryAccount account() const | calls plan; returns runtime.plan().account() · [reviewed contract](#b0014) |
| [B0015 · 79–79](../../../../../tests/unit/report_capture_memory_test.cpp#L79) | Callable definition: Facts facts() const | calls owner; returns {runtime.owner().value,kind,Phase::ready} · [reviewed contract](#b0015) |
| [B0016 · 80–92](../../../../../tests/unit/report_capture_memory_test.cpp#L80) | Callable definition: Value capture() const | calls obs::ModeDescriptor::capture, capture_observation_trace, capture_state_gauges, obs::PlanExplanation::create; returns obs::ModeDescriptor::capture(runtime); runtime.capture_observation_trace() · [reviewed contract](#b0016) |
| [B0017 · 93–93](../../../../../tests/unit/report_capture_memory_test.cpp#L93) | Callable definition: void stable() const | calls check, sequence, state; guard void stable() const {check(runtime.sequence()==1 && runtime.state()==DeltaState::ready,"report read… · [reviewed contract](#b0017) |
| [B0018 · 94–99](../../../../../tests/unit/report_capture_memory_test.cpp#L94) | declares types or opens a type body. |  · [reviewed contract](#b0018) |
| [B0019 · 100–110](../../../../../tests/unit/report_capture_memory_test.cpp#L100) | Callable definition: SessionFixture(bool indexed,Kind k,Phase p,std::uint64_t cap):kind(k),phase(p) | calls kind, phase, options, QuerySession::create_typed; guard check(session-&gt;enqueue(input)==io::Admission::accepted,"session report fixture input rejected");ses…; growth insert · [reviewed contract](#b0019) |
| [B0020 · 111–111](../../../../../tests/unit/report_capture_memory_test.cpp#L111) | Callable definition: resource::MemoryAccount account() const | calls get_deleter; returns session.get_deleter().account() · [reviewed contract](#b0020) |
| [B0021 · 112–112](../../../../../tests/unit/report_capture_memory_test.cpp#L112) | Callable definition: Facts facts() const | calls report_metadata, owner; returns {session-&gt;report_metadata().owner().value,kind,phase} · [reviewed contract](#b0021) |
| [B0022 · 113–117](../../../../../tests/unit/report_capture_memory_test.cpp#L113) | Callable definition: Value capture() const | calls capture_statistics_context, obs::StatisticsExplanation::capture, obs::PlanExplanation::capture; returns session-&gt;capture_statistics_context(request.state,request.state_limits); obs::StatisticsExplanation… · [reviewed contract](#b0022) |
| [B0023 · 118–118](../../../../../tests/unit/report_capture_memory_test.cpp#L118) | Callable definition: void stable() const | calls check, status; guard void stable() const {check(session-&gt;status().committed_sequence==1,"report read accepted private se… · [reviewed contract](#b0023) |
| [B0024 · 119–120](../../../../../tests/unit/report_capture_memory_test.cpp#L119) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0024) |
| [B0025 · 121–123](../../../../../tests/unit/report_capture_memory_test.cpp#L121) | Callable definition: Owners owners(const resource::MemoryAccount& account) | calls size, statistics_for; returns result; 1 loop sites · [reviewed contract](#b0025) |
| [B0026 · 124–145](../../../../../tests/unit/report_capture_memory_test.cpp#L124) | Callable definition: template&lt;class Make&gt; void requests_and_lifetime(Make make) | calls make, fixture, account, facts; guard check(calls&gt;0 && calls==after.successful_allocations-before.successful_allocations && retained==aft…; returns owned_after\[id\].allocations-owned_before\[id\].allocations; 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 146–161](../../../../../tests/unit/report_capture_memory_test.cpp#L146) | Callable definition: template&lt;class Make&gt; std::size_t persistent(Make make) | calls make, account, facts, capture; guard check(expected&gt;0 && expected&lt;2048,"invalid report fault-sweep request count");; returns failures; 1 loop sites · [reviewed contract](#b0027) |
| [B0028 · 162–182](../../../../../tests/unit/report_capture_memory_test.cpp#L162) | Callable definition: template&lt;class Make&gt; std::pair&lt;std::uint64_t,std::size_t&gt; caps(Make make) | calls make, account, reserve, statistics; guard check(peak&gt;0 && pins&gt;0,"report cap fixture never exceeded its earlier setup peak");; returns {peak,pins}; growth push_back, reserve; 3 loop sites · [reviewed contract](#b0028) |
| [B0029 · 183–199](../../../../../tests/unit/report_capture_memory_test.cpp#L183) | Callable definition: void native_cross_account_values(bool indexed) | calls a, b, capture_observation_trace, capture_state_gauges; guard check(io::write_committed_state_gauges_json(source_gauges)==io::write_committed_state_gauges_json(a…; 2 loop sites · [reviewed contract](#b0029) |
| [B0030 · 200–200](../../../../../tests/unit/report_capture_memory_test.cpp#L200) | Closes surrounding scope/type. |  · [reviewed contract](#b0030) |
| [B0031 · 201–217](../../../../../tests/unit/report_capture_memory_test.cpp#L201) | Callable definition: int main() | calls RuntimeFixture, requests_and_lifetime, persistent, caps; returns RuntimeFixture(indexed,kind,cap); SessionFixture(indexed,kind,phase,cap); 4 loop sites · [reviewed contract](#b0031) |

## B0001

[Lines 1–17](../../../../../tests/unit/report_capture_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:eb80e82b31ae36e463de87fdfda45e0038830d0aee76ab3cd60a1da6665308b3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare report_capture_memory_test.cpp: include "owner_statistics_fixture.hpp", "indexed_runtime_fixture.hpp", "crown/observability/statistics_explain.hpp", "crown/io/cursor_observation.hpp", "index_allocation.hpp", &lt;array&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;variant&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–18](../../../../../tests/unit/report_capture_memory_test.cpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Kind
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the report products selected by the two fixture capture dispatchers. |
| inputs / outputs | A Kind chooses one report value in RuntimeFixture or SessionFixture; context is session-only and compiled is the explicit compile-only PlanExplanation route. |
| invariants | The Value alternatives align with the runtime switch and Session conditional dispatcher. The runtime loop omits context; the Session loop selects plan, context and statistics. |
| ownership | The enum is scalar fixture state. The fixture owns its runtime/session; the caller owns the returned Value. |
| failure | The enum declaration cannot fail. RuntimeFixture::capture throws for context/unrecognized kinds; SessionFixture::capture falls through to PlanExplanation for kinds other than context/statistics. |
| cost | One enum value; its meaningful cost is the 7-by-2 runtime and 3-by-4-by-2 session matrix in main. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/observability.md §Native retained report ownership](../../../../observability.md) |

## B0003

[Lines 19–19](../../../../../tests/unit/report_capture_memory_test.cpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Phase
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the session lifecycle boundary used by retained report checks. |
| inputs / outputs | Select ready, pending, stopped, or dropped state when constructing a SessionFixture. |
| invariants | Pending means the second erase batch has begun but is not drained; stopped keeps the runtime; dropped releases runtime tables while metadata remains. |
| ownership | A Phase is a copied test enum; the owning SessionFixture retains the QuerySession. |
| failure | The constructor's queue/session assertions throw if the requested lifecycle cannot be established. |
| cost | Scalar selection; each of the four phases is exercised for three report kinds on both backends. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0004

[Lines 20–21](../../../../../tests/unit/report_capture_memory_test.cpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L21:sha256:0272586f8dca24da6bed64082a6ff490e9a28e1c722469e8d9bc76fcc7ba2fda
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare report_capture_memory_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 22–22](../../../../../tests/unit/report_capture_memory_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool ok,std::string_view message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed test predicate into an exception reported by main. |
| inputs / outputs | Accept a boolean and borrowed message text; return normally when true and throw std::runtime_error when false. |
| invariants | It does not inspect or mutate the product under test. |
| ownership | The string_view borrows its call-site message; the exception owns its failure text only on the failing path. |
| failure | A false predicate propagates to main's std::exception handler and becomes a nonzero test result. |
| cost | One branch per assertion and one exception-string construction only on failure; this helper adds no production behavior. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp) |

## B0006

[Lines 23–26](../../../../../tests/unit/report_capture_memory_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the final report/runtime release to leave only the account controller. |
| inputs / outputs | Read account invariants and current usage, then compare allocations and requested bytes with the single control block. |
| invariants | This checks retained account storage after the fixture and every held report value have been reset. |
| ownership | The account handle borrows the shared control; the helper retains no allocation. |
| failure | Invariant or usage mismatch throws through check; this is a test oracle, not a cleanup routine. |
| cost | check_invariants checks controller totals and traverses the linked payload-allocation list. At a passing controller-only boundary that list is empty; the controller is counted separately, not scanned as one list entry. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0007

[Lines 27–36](../../../../../tests/unit/report_capture_memory_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the fixed two-node R/S report plan, optionally using indexed storage. |
| inputs / outputs | Lower a typed Catalog, Query, and FreeConnexTree; indexed selects s04_runtime::options and false uses default PhysicalOptions. |
| invariants | The fixture includes two active source occurrences and one unused catalog table; the returned plan is selected by the test, not a proof of general plan behavior. |
| ownership | All compiler DTOs are local during lowering; the returned PhysicalPlan owns its plan data. |
| failure | Lowering may throw for malformed or unsupported input; the fixture uses fixed valid values. |
| cost | Catalog/query/tree lowering and selected backend descriptor construction; mutable row/index state is initialized later by the runtime. This helper performs no report capture. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [tests/unit/owner_statistics_fixture.hpp](../../../../../tests/unit/owner_statistics_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0008

[Lines 37–40](../../../../../tests/unit/report_capture_memory_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions options(std::uint64_t cap)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the memory and observation options shared by report runtime fixtures. |
| inputs / outputs | Accept a byte cap; choose maintenance mode, disable transition capture, and configure trace sampling with capacity 4096, rate 1, offset 0, timings off. |
| invariants | The cap is the account's real requested-byte limit, while the observation record capacity is a separate fixed fixture setting. |
| ownership | The returned options value owns no runtime state; the fixture's plan account is created later. |
| failure | No local failure path; account admission can reject an undersized cap when the runtime is created. |
| cost | Constructs a small value with no loop; it does not allocate a 64 MiB buffer. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0009

[Lines 41–41](../../../../../tests/unit/report_capture_memory_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ws::Options enabled()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request workload counters for the combined/statistics report cases. |
| inputs / outputs | Return workload::Options with mode counters. |
| invariants | The fixture enables it only for combined and statistics runtime captures and for non-plan session captures. |
| ownership | The returned options object is a value; the runtime/session owns its configured collector. |
| failure | No local failure path. |
| cost | Scalar option construction; collection/capture cost occurs in the owning runtime, not here. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0010

[Lines 42–42](../../../../../tests/unit/report_capture_memory_test.cpp#L42); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Facts
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the expected owner, report kind, and lifecycle phase into assertions. |
| inputs / outputs | Stores one numeric owner ID, Kind, and Phase with no references or outputs. |
| invariants | Facts describe a captured boundary; they do not imply the capture owns a mutable runtime. |
| ownership | Owns only scalar enum/integer fields. |
| failure | No local failure path. |
| cost | Fixed-size aggregate copied by value; no account or report allocation. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/observability.md §Native retained report ownership](../../../../observability.md) |

## B0011

[Lines 43–68](../../../../../tests/unit/report_capture_memory_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(const Value& value,Facts facts)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check report owner/sequence, retained arrays, committed boundary, and dropped-state visibility. |
| inputs / outputs | Visit ModeDescriptor, trace, gauges, CombinedCapture, PlanExplanation, StatisticsExplanation, or SessionStatisticsContext and compare against Facts. |
| invariants | Owner checks use Facts.owner, not numeric owner 1. Trace checks support_owner and nonempty records without asserting a trace sequence. Other branches check their stated sequence/committed boundary at 1; gauges check two nodes/three bases. Compiled PlanExplanation uses owner 0/compile_only. Session branches check combined/pending/dropped visibility only where explicitly asserted. |
| ownership | The Value is borrowed for the assertion. Report handles and captured native arrays retain their own account-fenced values. |
| failure | A mismatch throws through check; visiting monostate fails explicitly. |
| cost | One std::visit plus fixed metadata comparisons; it reads sizes/empty flags rather than scanning tuple payloads. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md), [docs/observability.md §Native retained report ownership](../../../../observability.md), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp) |

## B0012

[Lines 69–72](../../../../../tests/unit/report_capture_memory_test.cpp#L69); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L72:sha256:0541fba3d3c7093abcbfbf2813b9957b240ff31340c113ff3a3b9ba3ee12bec7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare report_capture_memory_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 73–77](../../../../../tests/unit/report_capture_memory_test.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RuntimeFixture(bool indexed,Kind k,std::uint64_t cap):runtime(DeltaRuntime::initialize(plan(indexed),owner_fixture::database(),options(cap))),kind(k) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one ready DeltaRuntime and the requested report state. |
| inputs / outputs | Initialize the fixed plan/database with cap; prepare and commit one insert to S(y=8), discard the epoch token, and configure workload counters only for combined/statistics. |
| invariants | The runtime is at sequence 1 and ready before capture. The optional indexed mode comes from the fixture selector. |
| ownership | The fixture owns DeltaRuntime; request state is derived from that runtime's actual plan. |
| failure | Initialization, update preparation/commit, or account admission may throw before a report case starts. |
| cost | Each construction performs plan/runtime initialization and one small update on the two-node fixture; it is setup work repeated per case, not report allocation cost. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [tests/unit/owner_statistics_fixture.hpp](../../../../../tests/unit/owner_statistics_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp) |

## B0014

[Lines 78–78](../../../../../tests/unit/report_capture_memory_test.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount account() const{return runtime.plan().account();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the ready runtime's original query account to its memory assertions. |
| inputs / outputs | Return the account handle obtained from runtime.plan().account(). |
| invariants | The account is the original admitted plan grant used by report captures. |
| ownership | Returns a shared account handle; it does not copy the runtime or report. |
| failure | Requires a live fixture runtime and plan. |
| cost | Accessor work plus a shared-control handle copy; no query-memory scan. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp) |

## B0015

[Lines 79–79](../../../../../tests/unit/report_capture_memory_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Facts facts() const{return {runtime.owner().value,kind,Phase::ready};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze expected metadata for the ready runtime capture. |
| inputs / outputs | Return the runtime owner ID with the fixture's Kind and ready phase. |
| invariants | The sequence assertion is kept in stable(); Facts intentionally carries only owner/kind/phase. |
| ownership | Returns scalar facts, not a retained report. |
| failure | Requires a live initialized runtime. |
| cost | Fixed number of metadata reads and scalar copies. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/observability.md §Native retained report ownership](../../../../observability.md) |

## B0016

[Lines 80–92](../../../../../tests/unit/report_capture_memory_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value capture() const {
    switch(kind) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch a report request to the selected native DeltaRuntime API. |
| inputs / outputs | Return ModeDescriptor, native trace, gauges, compile-only PlanExplanation, CombinedCapture, runtime PlanExplanation, or StatisticsExplanation for the configured Kind. |
| invariants | context is deliberately rejected here; all runtime captures in this test use the real runtime plan/account. |
| ownership | The returned handle/value retains copied facts under the original query account; it owns no mutable DeltaRuntime. |
| failure | Ordinary capture failures such as bad_alloc propagate to the caller; this helper does not translate them to CaptureAttempt. |
| cost | Work depends on the kind: a trace copies retained numeric records, gauges enumerate nodes/bases, and combined/explanation captures allocate object controls plus requested child arrays. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0017

[Lines 93–93](../../../../../tests/unit/report_capture_memory_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stable() const {check(runtime.sequence()==1 && runtime.state()==DeltaState::ready,"report read changed accepted runtime state");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert report reads did not advance or mutate the accepted DeltaRuntime. |
| inputs / outputs | Read sequence and state after capture and require sequence 1/ready. |
| invariants | The assertion proves this fixture boundary only; it is not a general concurrency guarantee. |
| ownership | Borrows the fixture runtime and retains nothing. |
| failure | A mismatch throws through check. |
| cost | Two scalar metadata reads; no row traversal or allocation on success. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp) |

## B0018

[Lines 94–99](../../../../../tests/unit/report_capture_memory_test.cpp#L94); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L99:sha256:0a8c9cd989a8fedcc305ff135cd5e6b872172366572b73d42608bb12ccd1811b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare report_capture_memory_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 100–110](../../../../../tests/unit/report_capture_memory_test.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionFixture(bool indexed,Kind k,Phase p,std::uint64_t cap):kind(k),phase(p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a QuerySession at the selected report lifecycle boundary. |
| inputs / outputs | Create the typed session/account, configure workload counters except for plan, enqueue/start/drain one insert to S(y=8); pending adds an undrained erase, stopped calls stop, and dropped calls drop. |
| invariants | The session's committed sequence remains 1. Pending work is private; stopped retains runtime state; dropped preserves report metadata but releases runtime state. |
| ownership | The fixture owns QuerySession through its custom Owner deleter; the plan/request are derived from that session. |
| failure | Admission, begin, fixture setup, or lifecycle assertions can throw before capture. |
| cost | Setup processes one committed event and at most one begun pending event per fixture; stop/drop adds lifecycle work and is repeated across phase/kind cases. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0020

[Lines 111–111](../../../../../tests/unit/report_capture_memory_test.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount account() const{return session.get_deleter().account();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the account retained by the QuerySession owner deleter. |
| inputs / outputs | Return the custom deleter's account handle. |
| invariants | The handle identifies the same original session grant used for report controls and captured children. |
| ownership | Returns a shared MemoryAccount value; it does not retain the QuerySession owner itself. |
| failure | Requires a constructed session owner. |
| cost | Accessor/handle copy only; account statistics are read separately by callers. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0021

[Lines 112–112](../../../../../tests/unit/report_capture_memory_test.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Facts facts() const{return {session->report_metadata().owner().value,kind,phase};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze the session owner ID and requested lifecycle for report assertions. |
| inputs / outputs | Read report metadata owner and return it with Kind/Phase. |
| invariants | Facts are compared with copied report metadata; they do not assert that the report retains the live session. |
| ownership | Returns scalar metadata without keeping the session. |
| failure | Requires the session owner and retained report metadata to exist, including after drop. |
| cost | Metadata accessor reads and scalar copies; no gauge or trace scan. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/observability.md §Native retained report ownership](../../../../observability.md) |

## B0022

[Lines 113–117](../../../../../tests/unit/report_capture_memory_test.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value capture() const {
    if(kind==Kind::context)return session->capture_statistics_context(request.state,request.state_limits);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route session capture to context, statistics, or plan explanation. |
| inputs / outputs | Context calls capture_statistics_context; statistics calls StatisticsExplanation::capture; remaining supported session Kind uses PlanExplanation::capture. |
| invariants | A context is session-only. Pending/stopped/dropped visibility comes from QuerySession capture rules, not a caller-supplied runtime. |
| ownership | Returned native report/context retains its own immutable plan and facts under the session's original account. |
| failure | Ordinary capture exceptions, including allocation failure, propagate; no status wrapper is added here. |
| cost | Trace capture is bounded by configured capacity; gauge arrays scale with plan nodes/bases; statistics additionally captures requested state/workload summaries. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/observability/explain.cpp](../../../../../src/observability/explain.cpp), [src/observability/statistics_explain.cpp](../../../../../src/observability/statistics_explain.cpp), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0023

[Lines 118–118](../../../../../tests/unit/report_capture_memory_test.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stable() const {check(session->status().committed_sequence==1,"report read accepted private session input");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert captured reports did not accept a new committed session epoch. |
| inputs / outputs | Read SessionStatus and require committed_sequence 1. |
| invariants | A pending second event may exist; it is not considered committed by this check. |
| ownership | Borrows QuerySession and retains no status value. |
| failure | A mismatch throws through check. |
| cost | One session metadata read; no census, trace copy, or row iteration. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0024

[Lines 119–120](../../../../../tests/unit/report_capture_memory_test.cpp#L119); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L119-L120:sha256:f7ffa841c424721b89a81c67c096b5f7d4c3abdeb8a99d9846f407e239546db5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare report_capture_memory_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0025

[Lines 121–123](../../../../../tests/unit/report_capture_memory_test.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Owners owners(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot the nine report capture-attribution rows used by report reconciliation. |
| inputs / outputs | Call statistics_for for capture owner indices 0 through 8 and return each current MemoryUsage. |
| invariants | The numeric indices are test-local MemoryAttribution categories, distinct from Facts.owner runtime owner IDs and not an owner identity. The range includes session context, trace, gauge arrays, combined, mode, plan, statistics, and the remaining capture attribution. |
| ownership | The returned array owns only copied counters; the account remains borrowed. |
| failure | An invalid attribution/account would fail in MemoryAccount; the fixture uses valid capture IDs. |
| cost | Nine statistics_for calls each scan the account's linked allocation blocks, so work is O(9A), where A is the current block count; the loop itself has nine iterations. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0026

[Lines 124–145](../../../../../tests/unit/report_capture_memory_test.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> void requests_and_lifetime(Make make)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile one successful report capture, its retained owner bytes, copy behavior, and final release. |
| inputs / outputs | Construct a fixture, record account totals and nine attribution scans, capture under s04_alloc::Scope, compare intercepted new attempts with successful account allocations/current bytes, inspect kind-specific owner blocks, copy the returned Value, then release fixture/handles and require controller-only usage. |
| invariants | The tracker counts replaced C++ allocation overload attempts, while MemoryAccount reports successful account requests and requested bytes. Native trace and gauge copies expect 1 and 2 covered new attempts; shared report/evidence handles expect 0. |
| ownership | The output keeps immutable native facts alive after the runtime/session fixture closes; final aliases release their original-account blocks. |
| failure | Count/attribution mismatches fail check(). Copy uses a counting Scope and must match its 0/1/2 request expectation; teardown uses Scope(0), so unexpected covered new there fails directly. |
| cost | One capture plus one copy; each before/after owners() call performs 9 linked-list scans (18 scans total), then a 9-element delta sum. Capture requests vary by report kind; the function does not claim all captures are allocation-free. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md), [docs/observability.md §Native retained report ownership](../../../../observability.md) |

## B0027

[Lines 146–161](../../../../../tests/unit/report_capture_memory_test.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> std::size_t persistent(Make make)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault every intercepted report-capture allocation position while preserving old reports and runtime state. |
| inputs / outputs | Calibrate N new attempts, then run points 0..N; each injected bad_alloc checks no partial output/current-byte change, retries capture, verifies the old and new values, checks stability, and validates account invariants. |
| invariants | N is measured per fixture and guarded by N&lt;2048. Capture throws bad_alloc on the injected report path; this is not a no-throw capture API. |
| ownership | The original held report remains alive during the sweep; failed graph allocations are expected to roll back and the retry result is released each iteration. |
| failure | A predicate or unexpected exception escapes to main; expected bad_alloc is caught at the capture call. |
| cost | Two initial captures retain the old value and calibrate N. The sweep then makes N+1 capture attempts plus N healthy retries; each iteration also checks account invariants over current linked blocks. Failed attempts can stop partway, and the total includes setup/capture size/outstanding blocks. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md), [docs/observability.md §Native retained report ownership](../../../../observability.md) |

## B0028

[Lines 162–182](../../../../../tests/unit/report_capture_memory_test.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> std::pair<std::uint64_t,std::size_t> caps(Make make)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure retained-report peak growth and test exact/one-byte-under account limits. |
| inputs / outputs | Retain captures until a later capture raises peak_requested_bytes (up to 2048); create fresh accounts capped at peak and peak-1, pin the calibrated number of reports, then capture once more. |
| invariants | Exact cap must permit capture; one-under must throw MemoryFailure(limit) without changing current retained bytes; dropping one pin permits retry under the unchanged cap. |
| ownership | The vector holds native reports across captures and runtime fixture lifetime; each report charges the original query account. |
| failure | The one-under failure is required and classified by MemoryFault::limit; unexpected admission behavior throws. |
| cost | Calibration can perform up to 2048 captures; each cap case retains pins reports and performs one boundary capture, with a further retry only after release. The account peak is measured, not treated as RSS or logical bytes. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0029

[Lines 183–199](../../../../../tests/unit/report_capture_memory_test.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_cross_account_values(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check trace/gauge value assignment across query accounts under every source-array copy failure position. |
| inputs / outputs | Build two runtimes, capture source and old trace/gauges, compare native gauge JSON with the committed-state DTO, then inject failures during trace (1 request) and gauge (2 requests) assignment and retry. |
| invariants | On failure both accounts' current usage and destination metadata remain old; on success assignment adopts source ownership. This covers assignment semantics, not every report API or all allocator calls. |
| ownership | Source values remain tied to account A; destination old values to account B; retained arrays move/copy with value ownership. |
| failure | Injected bad_alloc is caught and followed by an unfaulted retry; a mismatch throws. |
| cost | For each backend, the test runs two trace fault positions and three gauge positions; assignment copies O(records) or O(nodes+bases) arrays, and gauge JSON comparison traverses the small DTO. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md) |

## B0030

[Lines 200–200](../../../../../tests/unit/report_capture_memory_test.cpp#L200); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L200-L200:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in report_capture_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0031

[Lines 201–217](../../../../../tests/unit/report_capture_memory_test.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the source-level report capture matrix and failure reporting boundary. |
| inputs / outputs | For reference/indexed modes, run seven runtime kinds, four session phases by three session kinds, then cross-account trace/gauge assignment; catch std::exception and return 1 on a failed assertion. |
| invariants | This source encodes 14 runtime fixture combinations and 24 session fixture combinations (38 total); cap sweeps occur for all 14 runtime combinations and only the eight session statistics combinations, 22 cap sweeps total. |
| ownership | Fixtures, snapshots, and immutable report values own their distinct lifetimes; numeric report captures retain copied plan/facts, not the mutable runtime/session. |
| failure | Any uncaught fixture, capture, or assertion exception is printed and returns 1. |
| cost | The executable performs repeated setup/capture/fault/cap work for the explicit matrix; runtime and indexed cases repeat separately. CTest registers it as report_capture_memory with timeout 300; this packet did not execute it. |
| Design | [tests/unit/report_capture_memory_test.cpp](../../../../../tests/unit/report_capture_memory_test.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [docs/memory_accounts.md §Native retained trace, gauge and report graphs](../../../../memory_accounts.md), [docs/observability.md §Native retained report ownership](../../../../observability.md) |
