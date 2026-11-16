# `tests/unit/ranking_result_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/ranking_result_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `40a888d8b68911caeb6671b58bc78abe353cc02acef0a0fe3354140912d178e2`. 223 lines partitioned into 24 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/unit/ranking_result_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 17–17](../../../../../tests/unit/ranking_result_memory_test.cpp#L17) | Type/record definition: enum class Kind |  · [reviewed contract](#b0002) |
| [B0003 · 18–18](../../../../../tests/unit/ranking_result_memory_test.cpp#L18) | Type/record definition: enum class Phase |  · [reviewed contract](#b0003) |
| [B0004 · 19–19](../../../../../tests/unit/ranking_result_memory_test.cpp#L19) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 20–20](../../../../../tests/unit/ranking_result_memory_test.cpp#L20) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message) {if(!value)throw std::runtime_error(std::string(mes… · [reviewed contract](#b0005) |
| [B0006 · 21–24](../../../../../tests/unit/ranking_result_memory_test.cpp#L21) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(value.allocations==1 && value.requested_bytes==resource::MemoryAccount::control_bytes(),"rank… · [reviewed contract](#b0006) |
| [B0007 · 25–30](../../../../../tests/unit/ranking_result_memory_test.cpp#L25) | Callable definition: resource::MemoryAccount account(const Owner& owner) | calls std::visit, constexpr, get_deleter, plan; returns std::visit(\[\](const auto& value){; value.get_deleter().account() · [reviewed contract](#b0007) |
| [B0008 · 31–37](../../../../../tests/unit/ranking_result_memory_test.cpp#L31) | Callable definition: template&lt;class Plan&gt; Owner make_owner(Plan plan,const Database& database,Kind kind,std::uint64_t cap) | calls PhysicalRuntime::initialize, std::move, DeltaRuntime::initialize, QuerySession::create_typed; returns PhysicalRuntime::initialize(std::move(plan),database,physical); DeltaRuntime::initialize(std::move(… · [reviewed contract](#b0008) |
| [B0009 · 38–38](../../../../../tests/unit/ranking_result_memory_test.cpp#L38) | Type/record definition: struct Facts |  · [reviewed contract](#b0009) |
| [B0010 · 39–42](../../../../../tests/unit/ranking_result_memory_test.cpp#L39) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 43–64](../../../../../tests/unit/ranking_result_memory_test.cpp#L43) | Callable definition: Fixture(const c02_test::Fixture& f,const planner::CandidateSnapshot& c,bool indexed,Kind kind,Phase phase, bool enabled,pr::Polic… | calls owner, make_owner, planner::lower_tree, candidate; guard check(value-&gt;enqueue(input)==io::Admission::accepted,"ranking result input rejected");value-&gt;start(…; growth insert · [reviewed contract](#b0011) |
| [B0012 · 65–65](../../../../../tests/unit/ranking_result_memory_test.cpp#L65) | Callable definition: resource::MemoryAccount account() const | calls ; returns ::account(owner) · [reviewed contract](#b0012) |
| [B0013 · 66–72](../../../../../tests/unit/ranking_result_memory_test.cpp#L66) | Callable definition: pr::Attempt rank() const | calls std::visit, constexpr, rr::rank_current; returns std::visit(\[&\](const auto& value){; rr::rank_current(candidates,*value,request) · [reviewed contract](#b0013) |
| [B0014 · 73–78](../../../../../tests/unit/ranking_result_memory_test.cpp#L73) | Callable definition: void stable() const | calls std::visit, constexpr, check, status; guard if constexpr(std::is_same_v&lt;std::decay_t&lt;decltype(value)&gt;,QuerySession::Owner&gt;)check(value-&gt;status(… · [reviewed contract](#b0014) |
| [B0015 · 79–79](../../../../../tests/unit/ranking_result_memory_test.cpp#L79) | Closes surrounding scope/type. |  · [reviewed contract](#b0015) |
| [B0016 · 80–80](../../../../../tests/unit/ranking_result_memory_test.cpp#L80) | Callable definition: pr::Result accepted(pr::Attempt attempt) | calls check, has_value; guard pr::Result accepted(pr::Attempt attempt) {check(attempt.stop==pr::Stop::complete && attempt.result.…; returns *attempt.result · [reviewed contract](#b0016) |
| [B0017 · 81–105](../../../../../tests/unit/ranking_result_memory_test.cpp#L81) | Callable definition: void verify(const pr::Result& result,Facts facts,const resource::MemoryAccount& account) | calls check, scores, size, get_allocator; guard check(result.scores().size()==3 && result.scores().get_allocator()==rd::score_allocator&lt;pr::Candida…; 4 loop sites · [reviewed contract](#b0017) |
| [B0018 · 106–115](../../../../../tests/unit/ranking_result_memory_test.cpp#L106) | Callable definition: template&lt;class Make&gt; void requests_and_lifetime(Make make) | calls make, fixture, account, statistics; guard check(calls&gt;0 && calls==after.successful_allocations-before.successful_allocations,"ranking result/… · [reviewed contract](#b0018) |
| [B0019 · 116–130](../../../../../tests/unit/ranking_result_memory_test.cpp#L116) | Callable definition: template&lt;class Make&gt; std::size_t persistent(Make make) | calls make, account, accepted, rank; guard check(expected&gt;0 && expected&lt;4096,"native ranking fault calibration is outside test bound");; returns expected; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 131–150](../../../../../tests/unit/ranking_result_memory_test.cpp#L131) | Callable definition: template&lt;class Make&gt; std::pair&lt;std::uint64_t,std::size_t&gt; caps(Make make) | calls make, account, reserve, statistics; guard check(peak&gt;0 && pins&gt;0,"ranking did not exceed earlier setup peak");; returns {peak,pins}; growth push_back, reserve; 3 loop sites · [reviewed contract](#b0020) |
| [B0021 · 151–162](../../../../../tests/unit/ranking_result_memory_test.cpp#L151) | Callable definition: void native_runtime_input(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates,bool indexed,Kind kind) | calls CompiledProgram::standalone, planner::lower_tree, candidate, tree; guard const auto target=account(*owner);check(calls&gt;0 && calls==target.statistics().successful_allocation… · [reviewed contract](#b0021) |
| [B0022 · 163–198](../../../../../tests/unit/ranking_result_memory_test.cpp#L163) | Callable definition: void native_runtime_operation_grant(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates) | calls s04_runtime::options, CompiledProgram::standalone, planner::lower_tree, candidate; guard {const auto copy=CompiledProgram::freeze(target,limited,&exact);check(exact.remaining()==storage::I…; 2 loop sites; source comment (unverified): // Starting the one outer runtime operation consumes a structural step before · [reviewed contract](#b0022) |
| [B0023 · 199–199](../../../../../tests/unit/ranking_result_memory_test.cpp#L199) | Closes surrounding scope/type. |  · [reviewed contract](#b0023) |
| [B0024 · 200–223](../../../../../tests/unit/ranking_result_memory_test.cpp#L200) | Callable definition: int main() | calls c02_test::fixture, c02_test::candidates, native_runtime_operation_grant, native_runtime_input; returns Fixture(f,candidates,indexed,kind,Phase::ready,true,policy,cap); Fixture(f,candidates,indexed,Kind:…; 6 loop sites · [reviewed contract](#b0024) |

## B0001

[Lines 1–16](../../../../../tests/unit/ranking_result_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:18792f49e672b6795f3d311e77e1902ab352251b50112d8f90ddc9bd2442b953
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_result_memory_test.cpp: include "ranking_fixture.hpp", "indexed_runtime_fixture.hpp", "crown/runtime/ranking_evidence.hpp", "ranking_detail.hpp", "index_allocation.hpp", &lt;iostream&gt;, &lt;optional&gt;, &lt;variant&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 17–17](../../../../../tests/unit/ranking_result_memory_test.cpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Kind {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select which actual runtime owner supplies ranking evidence. |
| inputs / outputs | The enum value \`physical, delta and session\` is stored in Facts and used by Fixture setup/verification. |
| invariants | The declaration is only a scenario selector; it carries no ranking evidence or owner state. |
| ownership | An enum value is copied as fixture metadata; Fixture owns the mutable owner and result handles. |
| failure | The declaration performs no setup; owner/session initialization and ranking can fail in their own paths. |
| cost | No allocator or loop is introduced by this type; its selected phase affects later fixture/rank work. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [docs/ranking.md](../../../../ranking.md) |

## B0003

[Lines 18–18](../../../../../tests/unit/ranking_result_memory_test.cpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Phase {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select session-boundary state used by runtime ranking evidence. |
| inputs / outputs | The enum value \`ready, pending, stopped and dropped\` is stored in Facts and used by Fixture setup/verification. |
| invariants | The declaration is only a scenario selector; it carries no ranking evidence or owner state. |
| ownership | An enum value is copied as fixture metadata; Fixture owns the mutable owner and result handles. |
| failure | The declaration performs no setup; owner/session initialization and ranking can fail in their own paths. |
| cost | No allocator or loop is introduced by this type; its selected phase affects later fixture/rank work. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [docs/ranking.md](../../../../ranking.md) |

## B0004

[Lines 19–19](../../../../../tests/unit/ranking_result_memory_test.cpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L19:sha256:f341b03c7d3e42c23b3d3fb749c8b09481b4a3de6a9e7ea41102e085a3e9d7cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_result_memory_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 20–20](../../../../../tests/unit/ranking_result_memory_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed ranking-result memory assertion into a test exception. |
| inputs / outputs | True returns; false converts the borrowed message to std::string and throws runtime_error. |
| invariants | Error text is created only inside the false branch; passing checks do not eagerly construct exception text. |
| ownership | Borrows message during the call; a thrown runtime_error owns its text. |
| failure | Failure construction may allocate and is caught only at main's outer test boundary. |
| cost | One branch per check; string/error work happens only on a failed assertion. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0006

[Lines 21–24](../../../../../tests/unit/ranking_result_memory_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that no ranking result/evidence storage remains after the final handle release. |
| inputs / outputs | Runs account.check_invariants() and then compares current allocations/requested bytes with the single account control block. |
| invariants | The account controller remains alive; result/control/text/score allocations are expected to be gone. |
| ownership | Borrows the account; it retains no query allocation. |
| failure | The invariant or equality check can throw; this diagnostic is called by the test, not used as an operational ranking primitive. |
| cost | check_invariants walks tracked live blocks; statistics() is a counter snapshot. statistics_for also walks live blocks but is not used by this helper. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0007

[Lines 25–30](../../../../../tests/unit/ranking_result_memory_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount account(const Owner& owner)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the existing query account through a physical, delta or session owner variant. |
| inputs / outputs | Physical/Delta return plan().account(); QuerySession::Owner returns its deleter account. |
| invariants | The function references the runtime's original account and never creates a ranking-local refill. |
| ownership | Returns a copied account handle; Owner remains owned by caller Fixture. |
| failure | A valueless/moved-from owner would fail its visit/access; no fallback account is created. |
| cost | One variant visit and shared account-handle copy; no statistics scan. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0008

[Lines 31–37](../../../../../tests/unit/ranking_result_memory_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Plan> Owner make_owner(Plan plan,const Database& database,Kind kind,std::uint64_t cap)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a capped runtime/session from either a physical or compiled plan for ranking tests. |
| inputs / outputs | Moves Plan into PhysicalRuntime, maintenance DeltaRuntime or typed QuerySession; physical support cap is set and transition capture is disabled. |
| invariants | All owner choices share the same input plan/database semantics; native admission uses the same caller-supplied cap and configured storage work grant. |
| ownership | Returned Owner owns its runtime facade/session deleter and receiving query account; the source plan/database are not retained as mutable owners by this helper. |
| failure | Runtime/session initialization can allocate, reject input or exhaust storage work; errors propagate to the test caller. |
| cost | Initializes a full runtime and database state; time/storage depends on plan backend and database shape, not merely the Kind branch. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0009

[Lines 38–38](../../../../../tests/unit/ranking_result_memory_test.cpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Facts {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the policy, session phase and workload-counter mode used to rank and verify one fixture. |
| inputs / outputs | Three value fields provide ranking Policy, Phase and whether workload capture is enabled. |
| invariants | verify uses these values to predict evidence availability/fallback; Facts itself is not runtime evidence. |
| ownership | Plain fixture metadata; it owns no account, string or result backing. |
| failure | No separate setup path is defined; downstream Fixture construction and rank calls can fail. |
| cost | Scalar fields copied into/out of Fixture; no allocation is performed by this data shape. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md) |

## B0010

[Lines 39–42](../../../../../tests/unit/ranking_result_memory_test.cpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L42:sha256:a4eef3c01293526433373889114cd9e6f6a57a466f6212a432bd0b3332138b1c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_result_memory_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 43–64](../../../../../tests/unit/ranking_result_memory_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture(const c02_test::Fixture& f,const planner::CandidateSnapshot& c,bool indexed,Kind kind,Phase phase,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a ranking case with a chosen backend, owner kind, session phase, evidence mode, score policy and memory cap. |
| inputs / outputs | Lowers candidate zero, constructs one runtime owner, stores Facts, configures workload counters/off, and inserts sequence-one input; session phases may stage sequence-two erase, stop or drop. |
| invariants | Only the pending session phase leaves an uncommitted second event; committed sequence stays one. The indexed option changes only physical planning/backend options. |
| ownership | Owns the runtime/session owner and Facts; borrows the candidate snapshot for ranking and keeps no Result until a helper retains one. |
| failure | Lowering, runtime initialization, workload setup, enqueue/begin/drain and input publication can allocate or report errors; constructor completion is not assumed infallible. |
| cost | Constructs a plan and owner, configures one workload mode, applies one input and may stage a second session event; costs depend on backend and phase. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 65–65](../../../../../tests/unit/ranking_result_memory_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount account() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the account of the Fixture's current owner for result and allocation checks. |
| inputs / outputs | Calls the shared account visitor on the stored Owner variant. |
| invariants | The account handle is the same receiving account used by rank_current; no additional allowance is created. |
| ownership | Fixture retains the runtime/session owner; caller receives an account reference handle. |
| failure | Owner access can fail for invalid moved-from state; no exception is translated here. |
| cost | One variant visit and MemoryAccount handle copy; no live-block inventory walk. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0013

[Lines 66–72](../../../../../tests/unit/ranking_result_memory_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
pr::Attempt rank() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke current-owner runtime ranking with the Fixture's requested score policy. |
| inputs / outputs | Builds Request from Facts, forces height-only fallback, and visits PhysicalRuntime, DeltaRuntime or QuerySession to call rank_current. |
| invariants | The runtime entry captures fresh owner evidence for evidence-based policies; height-only uses the actual owner's account without source-fact capture. |
| ownership | Borrows candidate snapshot and owner for the synchronous call; returned Attempt owns an optional shared Result handle. |
| failure | rank_current is noexcept and reports allocation, evidence, limit or internal stops in Attempt. |
| cost | One runtime dispatch plus policy-dependent capture/ranking; candidate loops, score buffers and modeled plans vary with policy/backend. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [docs/ranking.md](../../../../ranking.md) |

## B0014

[Lines 73–78](../../../../../tests/unit/ranking_result_memory_test.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stable() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert ranking did not commit or advance the runtime/session owner. |
| inputs / outputs | Physical and delta sequence, or session committed_sequence, must remain one. |
| invariants | Pending phase may have private uncommitted input while the committed epoch check still remains one. |
| ownership | Borrows Fixture owner and retains nothing. |
| failure | A mismatch throws through check; the helper does not repair or rollback owner state. |
| cost | One variant visit and scalar committed-sequence/status read. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0015

[Lines 79–79](../../../../../tests/unit/ranking_result_memory_test.cpp#L79); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L79:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ranking_result_memory_test.cpp: struct Fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 80–80](../../../../../tests/unit/ranking_result_memory_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
pr::Result accepted(pr::Attempt attempt)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require complete runtime ranking and return a retained Result handle. |
| inputs / outputs | A complete Attempt with Result returns a copy; an incomplete Attempt triggers check and a test exception. |
| invariants | Result is an immutable shared handle, so the local Attempt can be destroyed after return. |
| ownership | The returned handle shares immutable account-backed ResultData. ResultData retains a CandidateSnapshot handle and optional evidence; each CandidateScore carries a copied MinimumHeightCandidate handle that pins immutable candidate payloads. Score structural_key text and score arrays are separate account-allocated storage. The result does not own the mutable runtime facade. |
| failure | A stop or missing result builds the failure message only in the failed check path; rank_current diagnostics are not erased by this helper. |
| cost | One stop/optional check and shared-handle copy; failure-text work occurs only when rejected. |
| Design | [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/ranking.md](../../../../ranking.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp) |

## B0017

[Lines 81–105](../../../../../tests/unit/ranking_result_memory_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(const pr::Result& result,Facts facts,const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check score vectors and their allocator identity against the supplied account, plus captured evidence, nested text and optional modeled-plan facts. |
| inputs / outputs | Three scores and their text/vector allocators, policy fallback, optional evidence, height/key, modeled-plan presence/account and depth fields are checked against Facts and account. |
| invariants | Height-only has no evidence; evidence policies retain a capture. Pending/dropped make required depth/memory unavailable as encoded by Facts; disabled workload affects depth availability but not slot evidence. Score allocator equality checks text/vector allocators against the supplied account. result.account() and modeled-plan assertions compare live current MemoryUsage totals (and modeled-plan validity), not account owner IDs. |
| ownership | Borrows Result/account/Facts; Result holds candidate and optional evidence handles, while score fields use OwnerAllocator tied to the original query account. |
| failure | Any mismatch throws via check; getters return const references scoped to the Result handle. |
| cost | Walks exactly the retained three scores and their nested depth/table/population/slot arrays; statistics() samples cached counters, not statistics_for's linked-block scan. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0018

[Lines 106–115](../../../../../tests/unit/ranking_result_memory_test.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> void requests_and_lifetime(Make make)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count one rank request's covered C++ new calls and verify shared Result lifetime beyond its owner fixture. |
| inputs / outputs | A factory builds Fixture; one rank runs in s04_alloc::Scope, then accepted Result and a copy are kept while Fixture is destroyed. |
| invariants | Covered allocation attempts must match the account successful-allocation delta; both Result handles remain valid after fixture destruction and final release leaves only control storage. |
| ownership | Result and copy share immutable account-backed data; the Fixture owns mutable runtime/session and is reset before the handles are released. |
| failure | Native ranking stops are converted by accepted to a test exception; RAII scopes and result handles release on unwinding. |
| cost | One data-dependent rank plus score verification. Scope counts C++ operator-new attempts only; account bytes are requested bytes, not total heap, RSS or CPU. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0019

[Lines 116–130](../../../../../tests/unit/ranking_result_memory_test.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> std::size_t persistent(Make make)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault every dynamically measured C++ new position during repeated ranking and verify all-or-none results plus retry. |
| inputs / outputs | Retains a baseline Result; measures a second rank call (required 1..4095 covered calls), then loops point 0 through expected, retrying after each injected failure. |
| invariants | Before each call current account bytes are recorded; preterminal failures must yield allocation_failure with no result and restore current bytes, retry must complete, and terminal point must match successful-allocation counters while the baseline Result and committed owner stay valid. |
| ownership | The Fixture owns runtime and one baseline handle; each returned attempt/result is temporary except during verification. |
| failure | Ranking returns stop diagnostics; the test throws if calibration exceeds its guard or if any failure leaks storage/partial winner. |
| cost | For dynamic N&lt;4096, the helper makes one retained baseline rank and one successful counted calibration rank on the same Fixture, then N+1 injected ranks and N unscoped retries on that fixture: 2N+3 rank calls total. Each of the N failure positions is retried; the terminal position succeeds. check_invariants scans live blocks once per position; fixture setup occurs once before these calls. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0020

[Lines 131–150](../../../../../tests/unit/ranking_result_memory_test.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> std::pair<std::uint64_t,std::size_t> caps(Make make)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find a retained ranking-result peak and test exact versus one-byte-under account caps. |
| inputs / outputs | Keeps successful Results until peak_requested_bytes rises, records peak/pin count, then ranks under exact peak and peak-1 caps with the same retained result count. |
| invariants | Exact cap must permit a result; one-under must fail without increasing current bytes while an older result remains valid; dropping one held handle permits retry without enlarging the original cap. |
| ownership | The default-allocator vector is test-side pin storage; each Result's scores/evidence/data remain charged to the account until its last handle drops. |
| failure | No peak rise within 2048 attempts is a test error; expected under-cap allocation failure is checked in Attempt. |
| cost | The discovery phase uses D&lt;=2048 rank calls until the first peak rise. Exact-cap and one-under fixtures each pin results and make one probe; the under-cap fixture then drops one pin and retries, for D+2*pins+3 explicit rank calls, excluding each fixture’s owner/input setup. peak_requested_bytes is query-account requested-byte high water, not all heap, RSS or CPU. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0021

[Lines 151–162](../../../../../tests/unit/ranking_result_memory_test.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_runtime_input(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates,bool indexed,Kind kind)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a standalone compiled plan is admitted into the selected runtime's own account. |
| inputs / outputs | Builds a CompiledProgram source, snapshots its source account, counts replacement-new calls around make_owner, checks destination successful allocations match those calls while source allocation counters stay unchanged, then compares physical plan identity. |
| invariants | The new runtime/session uses the source plan identity but has a distinct receiving account; destroying it returns that account to controller-only state. |
| ownership | The local source plan owns its original compiler account; optional Owner owns a separate runtime account and is reset before the final assertion. |
| failure | Runtime factory/admission can fail; the test expects successful construction for this chosen grant and does not claim every constructor is infallible. |
| cost | One plan lowering/standalone compile and one runtime initialization; the C++ shim measures covered operator-new calls, not direct C allocation, RSS or CPU. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 163–198](../../../../../tests/unit/ranking_result_memory_test.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_runtime_operation_grant(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calibrate indexed work for native compiled-plan admission, then check exhausted and insufficient grants for runtime initialization. |
| inputs / outputs | Builds source, limited and early CompiledPrograms; two freezes calibrate one exact admission grant. It then attempts physical, delta and session construction under the exactly exhausted grant and under {1,0,0,0,0}; all six constructions are expected to report storage_work_limit. |
| invariants | The exact grant is fully consumed by the calibrated freeze. The first three rejected constructions preserve the limited compiler account’s current bytes and successful-allocation count; all six must report storage_work_limit. The latter three diagnostic checks do not separately snapshot the early compiler account. |
| ownership | Probe/target accounts and CompiledProgram handles are local RAII values; temporary frozen copies release before controller_only checks. |
| failure | Freeze/runtime creation may throw storage_work_limit or other errors; the test catches only the expected Error code in the rejection loops and lets unexpected failures surface. |
| cost | Builds three CompiledPrograms, performs two calibration freezes, then makes exactly six runtime-construction attempts (three owner kinds under each grant). Each may traverse native plan metadata under IndexWork counters. This measures indexed work grants, not global C++ allocations or CPU time. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0023

[Lines 199–199](../../../../../tests/unit/ranking_result_memory_test.cpp#L199); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L199-L199:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ranking_result_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 200–223](../../../../../tests/unit/ranking_result_memory_test.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose the runtime ranking memory matrix across backend, owner, policy, session phase and workload-capture mode. |
| inputs / outputs | Build one candidate family, test native work-grant behavior, then for two backends × three owners run native-plan admission and three score policies; pending/stopped/dropped session phases and disabled-counter depth/slot policies add more cases. |
| invariants | The main path only registers the intended checks; its printed completion sentence is not execution evidence. Dynamic fault counts and pin peaks remain per-fixture observations. |
| ownership | Candidate fixture lives through each loop; factories create separate owner accounts and Results are dropped at each helper boundary unless deliberately retained. |
| failure | Any assertion or unexpected exception is printed and returns status 1; rank_current stops are checked by the helper paths. |
| cost | Runs 40 lifetime/persistent profiles (18 ready + 18 nonready session + 4 disabled-counter), of which 18 ready profiles also run caps; adds 6 native-source owner initializations and one work-grant helper with 2 freezes plus 6 expected grant refusals. Each persistent helper includes setup, calibration, injected failures and retries; exact allocations and account peaks are dynamic. |
| Design | [tests/unit/ranking_result_memory_test.cpp](../../../../../tests/unit/ranking_result_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |
