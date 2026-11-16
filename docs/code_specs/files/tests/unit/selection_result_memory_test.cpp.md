# `tests/unit/selection_result_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_result_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `3e81f00266bdc72d0cbd09e4057316b1164926a83455ec7baa08d9ad7cec6f39`. 245 lines partitioned into 27 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/unit/selection_result_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 18–18](../../../../../tests/unit/selection_result_memory_test.cpp#L18) | Type/record definition: enum class Kind |  · [reviewed contract](#b0002) |
| [B0003 · 19–19](../../../../../tests/unit/selection_result_memory_test.cpp#L19) | Type/record definition: enum class SourceKind |  · [reviewed contract](#b0003) |
| [B0004 · 20–20](../../../../../tests/unit/selection_result_memory_test.cpp#L20) | Type/record definition: enum class Case |  · [reviewed contract](#b0004) |
| [B0005 · 21–21](../../../../../tests/unit/selection_result_memory_test.cpp#L21) | Type/record definition: enum class Cache |  · [reviewed contract](#b0005) |
| [B0006 · 22–22](../../../../../tests/unit/selection_result_memory_test.cpp#L22) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 23–23](../../../../../tests/unit/selection_result_memory_test.cpp#L23) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message) {if(!value)throw std::runtime_error(std::string(mes… · [reviewed contract](#b0007) |
| [B0008 · 24–29](../../../../../tests/unit/selection_result_memory_test.cpp#L24) | Callable definition: resource::MemoryAccount account(const Owner& owner) | calls std::visit, constexpr, get_deleter, plan; returns std::visit(\[\](const auto& value) {; value.get_deleter().account() · [reviewed contract](#b0008) |
| [B0009 · 30–36](../../../../../tests/unit/selection_result_memory_test.cpp#L30) | Callable definition: Owner make_owner(const PhysicalPlan& plan,const Database& database,Kind kind,std::uint64_t cap) | calls PhysicalRuntime::initialize, DeltaRuntime::initialize, QuerySession::create_typed; returns PhysicalRuntime::initialize(plan,database,physical); DeltaRuntime::initialize(plan,database,delta) · [reviewed contract](#b0009) |
| [B0010 · 37–41](../../../../../tests/unit/selection_result_memory_test.cpp#L37) | Callable definition: rs::CurrentSelection accepted(rs::Attempt attempt) | calls std::runtime_error, std::to_string; returns *attempt.selection · [reviewed contract](#b0010) |
| [B0011 · 42–47](../../../../../tests/unit/selection_result_memory_test.cpp#L42) | Callable definition: ps::Request request(Case value) | calls ; returns out · [reviewed contract](#b0011) |
| [B0012 · 48–56](../../../../../tests/unit/selection_result_memory_test.cpp#L48) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0012) |
| [B0013 · 57–82](../../../../../tests/unit/selection_result_memory_test.cpp#L57) | Callable definition: Fixture(const c02_test::Fixture& f,const planner::CandidateSnapshot& c,bool indexed,Kind kind, SourceKind source_kind,Case policy… | calls compiler, planner::lower_tree, candidate, tree; guard check(value-&gt;enqueue(input)==io::Admission::accepted,"selection input rejected");value-&gt;start();; returns options; growth insert · [reviewed contract](#b0013) |
| [B0014 · 83–83](../../../../../tests/unit/selection_result_memory_test.cpp#L83) | Callable definition: resource::MemoryAccount account() const | calls ; returns ::account(owner) · [reviewed contract](#b0014) |
| [B0015 · 84–89](../../../../../tests/unit/selection_result_memory_test.cpp#L84) | Callable definition: rs::Attempt run(const ps::Request& r,ps::CacheUse use) | calls std::visit, constexpr, rs::select_current; returns std::visit(\[&\](const auto& value) {; rs::select_current(candidates,source,*value,r,{},&cache,use) · [reviewed contract](#b0015) |
| [B0016 · 90–90](../../../../../tests/unit/selection_result_memory_test.cpp#L90) | Callable definition: rs::Attempt select() | calls run; returns run(wanted,mode==Cache::bypass?ps::CacheUse::bypass:mode==Cache::hit?ps::CacheUse::read_only:ps::Ca… · [reviewed contract](#b0016) |
| [B0017 · 91–96](../../../../../tests/unit/selection_result_memory_test.cpp#L91) | Callable definition: void stable() const | calls std::visit, constexpr, check, status; guard if constexpr(std::is_same_v&lt;std::decay_t&lt;decltype(value)&gt;,QuerySession::Owner&gt;)check(value-&gt;status(… · [reviewed contract](#b0017) |
| [B0018 · 97–97](../../../../../tests/unit/selection_result_memory_test.cpp#L97) | Closes surrounding scope/type. |  · [reviewed contract](#b0018) |
| [B0019 · 98–115](../../../../../tests/unit/selection_result_memory_test.cpp#L98) | Callable definition: void verify(const rs::CurrentSelection& value,const resource::MemoryAccount& account,Case policy) | calls selection, check, account, statistics; guard check(result.account().statistics().owner==account.statistics().owner,"selection replaced the origi…; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 116–119](../../../../../tests/unit/selection_result_memory_test.cpp#L116) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(now.allocations==1 && now.requested_bytes==resource::MemoryAccount::control_bytes(),"selectio… · [reviewed contract](#b0020) |
| [B0021 · 120–129](../../../../../tests/unit/selection_result_memory_test.cpp#L120) | Callable definition: template&lt;class Make&gt; void requests_and_lifetime(Make make,Case policy) | calls make, fixture, account, statistics; guard check(calls&gt;0 && calls==account.statistics().successful_allocations-before.successful_allocations,"… · [reviewed contract](#b0021) |
| [B0022 · 130–148](../../../../../tests/unit/selection_result_memory_test.cpp#L130) | Callable definition: template&lt;class Make&gt; std::size_t persistent(Make make,Case policy) | calls make, select, verify, accepted; guard check(expected&gt;0 && expected&lt;4096,"selection fault calibration exceeded bound");; returns expected; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 149–167](../../../../../tests/unit/selection_result_memory_test.cpp#L149) | Callable definition: template&lt;class Make&gt; std::pair&lt;std::uint64_t,std::size_t&gt; caps(Make make,Case policy) | calls make, account, reserve, statistics; guard check(peak&gt;0 && pins&gt;0,"selection result did not exceed setup high water");; returns {peak,pins}; growth push_back, reserve; 3 loop sites · [reviewed contract](#b0023) |
| [B0024 · 168–199](../../../../../tests/unit/selection_result_memory_test.cpp#L168) | Callable definition: void session_phases(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates,bool indexed) | calls fixture, account, held, accepted; guard check(session.enqueue(next)==io::Admission::accepted && session.begin_next(),"selection phase fixtu…; 2 loop sites · [reviewed contract](#b0024) |
| [B0025 · 200–218](../../../../../tests/unit/selection_result_memory_test.cpp#L200) | Callable definition: void native_input_admission(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates,bool indexed) | calls request, none, ps::select, check; guard check(calls==0 && pure.stop==ps::Stop::invalid_handle && pure.stage==ps::Stage::admission && !pure.…; 1 loop sites · [reviewed contract](#b0025) |
| [B0026 · 219–219](../../../../../tests/unit/selection_result_memory_test.cpp#L219) | Closes surrounding scope/type. |  · [reviewed contract](#b0026) |
| [B0027 · 220–245](../../../../../tests/unit/selection_result_memory_test.cpp#L220) | Callable definition: int main(int argc,char** argv) | calls std::string_view, check, c02_test::fixture, c02_test::candidates; guard check(argc==1 \|\| admission_only,"unknown selection memory test argument");; returns Fixture(f,candidates,indexed,kind,source,policy,cache,cap); Fixture(f,candidates,indexed,kind,sourc…; 6 loop sites · [reviewed contract](#b0027) |

## B0001

[Lines 1–17](../../../../../tests/unit/selection_result_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:324c811dec39bb25e189ed197001a72f63a365d1d098f2842125be179422f67b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_result_memory_test.cpp: include "ranking_fixture.hpp", "indexed_runtime_fixture.hpp", "crown/runtime/selection.hpp", "selection_detail.hpp", "index_allocation.hpp", &lt;iostream&gt;, &lt;optional&gt;, &lt;variant&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–18](../../../../../tests/unit/selection_result_memory_test.cpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Kind {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select which actual runtime owner supplies current selection. |
| inputs / outputs | The enum value \`physical, delta and session\` configures Fixture construction and request/cache branches. |
| invariants | The declaration carries no runtime owner or policy evidence; the selected case is interpreted by request(), Fixture and main. |
| ownership | An enum value is copied as a small fixture selector; owner/result/cache storage lives in Fixture, not in the enum. |
| failure | No validation is performed by the declaration; downstream setup and selection can fail and are checked separately. |
| cost | No loop or allocator is introduced here; matrix work occurs in main and the selected helper. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [docs/selection.md](../../../../selection.md) |

## B0003

[Lines 19–19](../../../../../tests/unit/selection_result_memory_test.cpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SourceKind {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select DirectCQ, PhysicalPlan basis or standalone CompiledProgram selection input. |
| inputs / outputs | The enum value \`direct, compiler and native\` configures Fixture construction and request/cache branches. |
| invariants | The declaration carries no runtime owner or policy evidence; the selected case is interpreted by request(), Fixture and main. |
| ownership | An enum value is copied as a small fixture selector; owner/result/cache storage lives in Fixture, not in the enum. |
| failure | No validation is performed by the declaration; downstream setup and selection can fail and are checked separately. |
| cost | No loop or allocator is introduced here; matrix work occurs in main and the selected helper. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [docs/selection.md](../../../../selection.md) |

## B0004

[Lines 20–20](../../../../../tests/unit/selection_result_memory_test.cpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Case {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the scoring policy or the mandatory depth plus slot-cap request. |
| inputs / outputs | The enum value \`height, depth, slots and constrained depth\` configures Fixture construction and request/cache branches. |
| invariants | The declaration carries no runtime owner or policy evidence; the selected case is interpreted by request(), Fixture and main. |
| ownership | An enum value is copied as a small fixture selector; owner/result/cache storage lives in Fixture, not in the enum. |
| failure | No validation is performed by the declaration; downstream setup and selection can fail and are checked separately. |
| cost | No loop or allocator is introduced here; matrix work occurs in main and the selected helper. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [docs/selection.md](../../../../selection.md) |

## B0005

[Lines 21–21](../../../../../tests/unit/selection_result_memory_test.cpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Cache {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the cache path exercised by the memory and failure fixture. |
| inputs / outputs | The enum value \`bypass, disabled, miss, hit and evict\` configures Fixture construction and request/cache branches. |
| invariants | The declaration carries no runtime owner or policy evidence; the selected case is interpreted by request(), Fixture and main. |
| ownership | An enum value is copied as a small fixture selector; owner/result/cache storage lives in Fixture, not in the enum. |
| failure | No validation is performed by the declaration; downstream setup and selection can fail and are checked separately. |
| cost | No loop or allocator is introduced here; matrix work occurs in main and the selected helper. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [docs/selection.md](../../../../selection.md) |

## B0006

[Lines 22–22](../../../../../tests/unit/selection_result_memory_test.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:f341b03c7d3e42c23b3d3fb749c8b09481b4a3de6a9e7ea41102e085a3e9d7cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_result_memory_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 23–23](../../../../../tests/unit/selection_result_memory_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn one failed selection-memory assertion into a test exception. |
| inputs / outputs | A true condition returns; false constructs std::string from the string_view and throws runtime_error. |
| invariants | The exception-text conversion is inside the false branch, so passing checks do not eagerly build it. |
| ownership | Borrows the message view for the call; the failure exception owns its copied text. |
| failure | A false condition may allocate while constructing the error string/runtime_error and then propagates to main. |
| cost | One branch per assertion; only failure performs string/error construction. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0008

[Lines 24–29](../../../../../tests/unit/selection_result_memory_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount account(const Owner& owner)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract the existing query account from the active physical, delta or session owner variant. |
| inputs / outputs | A valid Owner variant returns a copied MemoryAccount from the plan or session deleter. |
| invariants | It observes the existing owner account and creates no replacement byte allowance. |
| ownership | The returned handle retains the same account control; the input owner remains caller-owned. |
| failure | std::visit requires a valid variant; access to an invalid/empty owner is not converted here. |
| cost | Visits one variant alternative and copies one account handle; statistics() calls elsewhere read scalar counters. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0009

[Lines 30–36](../../../../../tests/unit/selection_result_memory_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Owner make_owner(const PhysicalPlan& plan,const Database& database,Kind kind,std::uint64_t cap)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the selected runtime/session owner with a caller-chosen query memory cap. |
| inputs / outputs | A plan, initial database, Kind and cap create PhysicalRuntime, maintenance-mode DeltaRuntime or typed QuerySession::Owner with transition capture disabled. |
| invariants | All owner variants start from the supplied plan/database and use the requested cap; later checks compare their committed sequence. |
| ownership | The returned Owner variant owns the constructed facade/deleter; plan and database are inputs, and each new owner has its own account. |
| failure | Initialization can allocate, reject a plan/database or exhaust configured native storage work; exceptions propagate to the fixture/test boundary. |
| cost | Creates and initializes a full runtime plus its query-owned storage; cost follows plan/database shape and selected backend, not just the variant switch. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0010

[Lines 37–41](../../../../../tests/unit/selection_result_memory_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
rs::CurrentSelection accepted(rs::Attempt attempt)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a complete current-selection Attempt and retain its result handle for verification. |
| inputs / outputs | A complete Attempt with a selection returns a copied CurrentSelection; other stop/empty cases throw with stop and stage diagnostics. |
| invariants | The result handle shares its immutable backing and survives destruction of the local Attempt. |
| ownership | The by-value Attempt is local; the returned handle owns a shared reference to result data and the original account. |
| failure | On rejection, to_string/string concatenation and runtime_error may allocate; the caller's accepted path is not assumed infallible overall. |
| cost | Checks one stop/optional and copies one shared handle; error formatting occurs only on failure. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 42–47](../../../../../tests/unit/selection_result_memory_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ps::Request request(Case value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map a test case to one selection policy and optional mandatory tuple-slot cap. |
| inputs / outputs | Height maps to height_only, slots to tuple_index_slots and the remaining cases to committed_input_native_depth; constrained_depth adds a long decimal TupleIndexSlotLimit. |
| invariants | The slot-constrained depth request is later checked for both its slot assessment and primary depth result; the cap text remains caller-owned input until selection copies it. |
| ownership | Returns an ordinary Request value; the long std::string cap is owned by that request, not by the query account yet. |
| failure | Constructing/assigning the long std::string can allocate before any selection fault Scope; later admission can reject the cap. |
| cost | Small enum mapping plus a conditional long-string construction for constrained_depth; no fixed allocation count is asserted. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0012

[Lines 48–56](../../../../../tests/unit/selection_result_memory_test.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L56:sha256:6cf87159e9effd29fc0f9d3c8a7ef7adb75dc22e416b946c1a432250a29b9337
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_result_memory_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 57–82](../../../../../tests/unit/selection_result_memory_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture(const c02_test::Fixture& f,const planner::CandidateSnapshot& c,bool indexed,Kind kind,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one selection test scenario across runtime owner, source form, policy and cache mode. |
| inputs / outputs | The independent C02 fixture/candidate snapshot, indexed flag, Kind, SourceKind, Case, Cache and cap construct a lowered compiler plan, owner, source/request, PlanCache and optionally a prior hit/eviction selection. |
| invariants | The compiler plan's cost-model text is length 85 with an embedded NUL at offset 80; setup configures counters and inserts one row before the selection under test. |
| ownership | Owns compiler plan, Owner, source/request, exclusive PlanCache control and optional prior CurrentSelection; candidates is borrowed. Query-funded owner/result/cache-entry graphs use their existing account, while the cache control is separate. |
| failure | Plan lowering, the 80-character and 5-byte string temporaries, runtime setup, session enqueue/drain, cache creation and warm selection are fallible; failures propagate through the test. |
| cost | Initializes a compiler/runtime, creates a separately owned PlanCache control and may create a cache artifact. Session setup enqueues/drains one event; hit/evict modes perform another full selection before measurement. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 83–83](../../../../../tests/unit/selection_result_memory_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount account() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the existing account associated with the Fixture's owner variant. |
| inputs / outputs | The stored Owner is passed to the free account helper, which reads the plan account or session deleter account. |
| invariants | The returned handle shares the owner's account; no allowance is minted by this accessor. |
| ownership | The Fixture owns the owner; the caller receives an additional MemoryAccount reference. |
| failure | Invalid/valueless owner state can make the visitor fail; the accessor adds no error translation. |
| cost | One variant visit and account-handle copy; no block inventory walk. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0015

[Lines 84–89](../../../../../tests/unit/selection_result_memory_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
rs::Attempt run(const ps::Request& r,ps::CacheUse use)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch one selection call to the Fixture's physical, delta or session owner. |
| inputs / outputs | A request and CacheUse are passed with the borrowed candidate snapshot/source and exclusive PlanCache to the corresponding select_current overload. |
| invariants | The same Fixture account and cache are used for each attempt; the function does not update the owner itself. |
| ownership | Inputs are borrowed synchronously; returned Attempt carries an optional shared result handle and diagnostic values. |
| failure | select_current is noexcept at the API boundary and reports stop/stage/resource details in Attempt. |
| cost | One variant dispatch and a full data-dependent current-selection operation; it may capture owner facts, rank candidates, lower and stage cache work. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0016

[Lines 90–90](../../../../../tests/unit/selection_result_memory_test.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
rs::Attempt select()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the Fixture's wanted request with the cache-use mode represented by its test selector. |
| inputs / outputs | bypass uses CacheUse::bypass, hit uses read_only, and disabled/miss/evict use read_write with the Fixture cache. |
| invariants | On this valid Fixture path, every policy including height_only freshly captures runtime/source evidence and checks the boundary before selection; read_only cache lookup does not insert. Other cache behavior is verified by later assertions rather than inferred from this wrapper. |
| ownership | Returns Attempt; Fixture retains owner, source, cache and request throughout the synchronous call. |
| failure | Native stops remain in Attempt; the wrapper does not throw or convert them. |
| cost | One branch selection followed by the \`run\` cost; exact selection allocations are dynamically measured in the caller. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0017

[Lines 91–96](../../../../../tests/unit/selection_result_memory_test.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stable() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert selection did not advance the committed runtime/session epoch. |
| inputs / outputs | The owner variant must still report committed sequence 1 (session status or runtime sequence). |
| invariants | Pending session input is not treated as a committed sequence change; the check reads only committed state. |
| ownership | Borrows Fixture owner for the check and retains nothing. |
| failure | A mismatch throws through check; owner query APIs may themselves report invalid moved-from state. |
| cost | One variant visit and one sequence/status read; no full allocation-ledger scan. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0018

[Lines 97–97](../../../../../tests/unit/selection_result_memory_test.cpp#L97); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L97-L97:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_result_memory_test.cpp: struct Fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 98–115](../../../../../tests/unit/selection_result_memory_test.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(const rs::CurrentSelection& value,const resource::MemoryAccount& account,Case policy)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check retained selection result, capture and nested result storage against the original query account. |
| inputs / outputs | A CurrentSelection, its MemoryAccount and the Case determine expected assessment count, 3 decisions, score count, source/cap/cache text allocator, selected plan and captured epoch assertions. |
| invariants | For constrained depth it expects two assessments; otherwise one. DirectCQ's 85-byte cost model preserves its embedded NUL, slot cap/cache key use the supplied allocator, and plan/capture identities remain tied to the account and epoch. |
| ownership | Borrows the result and account; it does not own exports. Result internals retain immutable account-backed handles. |
| failure | Any failed invariant constructs a check exception; API getters return borrowed const references and require the result handle to stay alive. |
| cost | Traverses each assessment and its three scores plus nested score vectors/strings; statistics() reads cached totals, not statistics_for's live-block scan. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0020

[Lines 116–119](../../../../../tests/unit/selection_result_memory_test.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify all selection-owned allocations have been released after the last result/cache owner is dropped. |
| inputs / outputs | Runs account.check_invariants(), then requires current allocations/bytes to equal the single MemoryAccount control block. |
| invariants | The account controller remains alive for the assertion; no result/cache storage is expected after caller handles leave scope. |
| ownership | Borrows the external account reference and retains no blocks. |
| failure | check_invariants or the equality assertion can report failure; this is a diagnostic helper, not an operational update path. |
| cost | The invariant diagnostic walks outstanding ledger blocks; statistics() then reads counters. This differs from statistics_for, which also scans live blocks when explicitly requested. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0021

[Lines 120–129](../../../../../tests/unit/selection_result_memory_test.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> void requests_and_lifetime(Make make,Case policy)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure one selection's covered C++ new calls, verify all result buffers, then test shared-handle lifetime. |
| inputs / outputs | A fixture factory and Case create an owner; one select runs in s04_alloc::Scope, then accepted result and copy are retained while the Fixture is destroyed. |
| invariants | The test compares covered replacement-new calls with the account's successful-allocation delta, validates the old result after owner destruction, and expects only controller bytes after both result handles release. |
| ownership | Held/copy CurrentSelection handles share immutable result data and its account; fixture owns mutable runtime/cache and is reset before final handle release. |
| failure | Selection stop is converted by accepted to an exception; scoped counters unwind on failure and account/result destructors release their owners. |
| cost | One measured selection plus verification loops. The shim counts covered C++ operator-new attempts, not direct malloc, all heap traffic, RSS or CPU; account statistics are requested-byte counters. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0022

[Lines 130–148](../../../../../tests/unit/selection_result_memory_test.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> std::size_t persistent(Make make,Case policy)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject each calibrated replacement-new failure position and verify retry plus unchanged prior cache/result state. |
| inputs / outputs | A baseline selection determines expected calls (required 1..4095); for each point 0 through expected, a fresh Fixture runs one faulted select and retries below the final successful position. |
| invariants | Before every attempt it snapshots current account bytes/cache stats; injected failures must leave both unchanged and return allocation_failure with no selection, while retry and the terminal success must satisfy verify/stable and retain prior handles. |
| ownership | Each loop iteration owns a Fixture; any previous selection stays a shared handle while retries and full account invariant checks run. |
| failure | Every covered allocation position is expected to fail before the terminal point; allocation failure remains a returned Attempt, and retry may independently fail/throw only through the test's accepted boundary. |
| cost | For dynamic N&lt;4096, one calibration Fixture runs one counted selection, then N+1 fault points each reconstruct a Fixture/owner/cache and run one injected selection; the first N failures each get an unscoped retry and point N is the terminal success. That is 2N+2 explicit target selections, excluding fixture construction/setup (hit/evict setup can warm the cache); check_invariants scans live account blocks once per point. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0023

[Lines 149–167](../../../../../tests/unit/selection_result_memory_test.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> std::pair<std::uint64_t,std::size_t> caps(Make make,Case policy)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Discover a retained-result peak, then check exact and one-byte-under query-account caps and same-cap retry. |
| inputs / outputs | Retains successful selections until the account's peak_requested_bytes rises, records peak and pins, then repeats with cap=peak and peak-1 while pinning the same count. |
| invariants | Exact cap must permit the next result; one-under must return allocation_failure without changing current requested bytes, while a held result stays valid and releasing one pin permits retry at the original cap. |
| ownership | The ordinary std::vector of held CurrentSelection test handles is outside the query account; each result's own shared data remains in the query account until its final alias drops. |
| failure | If no peak rise is observed within 2048 attempts, the helper throws; selection failure at the under-cap point is an Attempt stop checked by the test. |
| cost | The discovery phase uses D&lt;=2048 selections until the first peak rise. Exact-cap and one-under fixtures each retain pins results and make one probe; the under-cap case then drops one pin and retries. This is D+2*pins+3 explicit selections, excluding fixture setup; cap factories use Cache::bypass. peak_requested_bytes is query-account requested-byte high water, not all heap, RSS or CPU. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0024

[Lines 168–199](../../../../../tests/unit/selection_result_memory_test.cpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void session_phases(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates,bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check retained current-selection behavior across stopped, pending and dropped session phases, plus zero-work admission. |
| inputs / outputs | For phases 0..2 it retains a selection, stops the session, stages an uncommitted erase, or drops the owner, then attempts another constrained-depth selection; it separately sets work=0 for each owner kind. |
| invariants | Stopped/live session can return a valid selection; pending/dropped phases must return boundary_unavailable without cache/current-byte changes while the old handle remains usable. Zero-work admission must return resource_limit before a covered C++ new call. |
| ownership | Fixture owns the session/runtime/cache; held CurrentSelection outlives fixture reset and is revalidated before its release. |
| failure | Enqueue/begin, stop/drop, selection or any failed check can reject the scenario; Attempt diagnostics are checked rather than treated as exceptions. |
| cost | Three phase scenarios plus three work-limit owner scenarios per backend; pending setup enqueues and begins one additional event, and account invariants inspect live blocks at controller-only boundaries. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0025

[Lines 200–218](../../../../../tests/unit/selection_result_memory_test.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_input_admission(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates,bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an empty native compiler basis at pure, current-owner and as-of selection admission. |
| inputs / outputs | An empty CompiledProgram becomes PhysicalBasis; pure select and each physical/delta/session current call and prior-capture as-of call are checked for invalid_handle at admission. |
| invariants | Each invalid call must make zero covered C++ new attempts, leave original account bytes/cache statistics unchanged, and preserve the fixture's prior valid selection and committed sequence. |
| ownership | The test Fixture retains owner, cache and prior result; invalid source is a caller-owned empty handle and is not imported into those owners. |
| failure | Selection reports invalid_handle as Attempt data; fixture construction/warm-cache setup can still fail before the measured admission checks. |
| cost | One pure check plus three owner variants, each with current and as-of attempts and account/cache comparisons; counters observe C++ new attempts only. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0026

[Lines 219–219](../../../../../tests/unit/selection_result_memory_test.cpp#L219); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L219-L219:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_result_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0027

[Lines 220–245](../../../../../tests/unit/selection_result_memory_test.cpp#L220); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose the selection result-memory matrix over backend, owner, source, policy, cache and session boundary cases. |
| inputs / outputs | Build one C02 fixture/candidate family; for each reference/indexed backend run native-input admission, session phases, then 3 owners × 3 source forms × 4 cases × 4 cache modes; four mapped case/owner/source/cache combinations also run persistent faults and cap probes. |
| invariants | The optional --admission-only mode still constructs fixtures and performs native-input admission, then skips the larger request/fault/cap matrix; no output line itself proves execution. |
| ownership | Fixture/candidates live in main; each per-case factory creates an independent owner/cache/result lifetime. |
| failure | Unknown arguments, failed helpers or exceptions produce a diagnostic and status 1; native select stop results are checked by each helper. |
| cost | The full main schedules 288 baseline combinations (2 backends × 3 owner kinds × 3 source forms × 4 policies × 4 cache modes), plus 4 mapped persistent-fault and 4 cap profiles per backend (8 of each total). Those caps always use Cache::bypass; persistent profiles cover only their four mapped cache/source/owner/policy combinations, not every matrix mode. Session and native-admission helpers run for both backends. Counts and requested-byte peaks are dynamic; this review did not run the test. |
| Design | [tests/unit/selection_result_memory_test.cpp](../../../../../tests/unit/selection_result_memory_test.cpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |
