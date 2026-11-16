# `tests/unit/operator_memory_report_test.cpp` — block usage map

[Source](../../../../../tests/unit/operator_memory_report_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `47d25510c1bf8dfe2eff65b126d5832cc39e21380d7c08bf2fc5f84e1b973ca4`. 320 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/unit/operator_memory_report_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 19–19](../../../../../tests/unit/operator_memory_report_test.cpp#L19) | Type/record definition: enum class Kind |  · [reviewed contract](#b0002) |
| [B0003 · 20–20](../../../../../tests/unit/operator_memory_report_test.cpp#L20) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 21–21](../../../../../tests/unit/operator_memory_report_test.cpp#L21) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message){if(!value)throw std::runtime_error(std::string(mess… · [reviewed contract](#b0004) |
| [B0005 · 22–22](../../../../../tests/unit/operator_memory_report_test.cpp#L22) | Callable definition: void sum(resource::MemoryUsage& a,const resource::MemoryUsage& b) | calls  · [reviewed contract](#b0005) |
| [B0006 · 23–28](../../../../../tests/unit/operator_memory_report_test.cpp#L23) | Callable definition: resource::MemoryAccount account(const Owner& owner) | calls std::visit, constexpr, get_deleter, plan; returns std::visit(\[\](const auto& value) {; value.get_deleter().account() · [reviewed contract](#b0006) |
| [B0007 · 29–43](../../../../../tests/unit/operator_memory_report_test.cpp#L29) | Callable definition: Owner make_owner(const PhysicalPlan& plan,const Database& database,Kind kind,std::uint64_t cap,LiveMaintenance live=LiveMaintenan… | calls owner, inputs, size, adapt_input; returns owner; PhysicalRuntime::initialize(plan,database,options); growth insert; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 44–49](../../../../../tests/unit/operator_memory_report_test.cpp#L44) | Callable definition: mm::Attempt capture(const Owner& owner,mm::Limits limits={}) | calls std::visit, constexpr, mm::capture; returns std::visit(\[&\](const auto& value) {; mm::capture(*value,limits) · [reviewed contract](#b0008) |
| [B0009 · 50–53](../../../../../tests/unit/operator_memory_report_test.cpp#L50) | Callable definition: mm::Report accepted(mm::Attempt attempt) | calls std::runtime_error, std::to_string; returns *attempt.report · [reviewed contract](#b0009) |
| [B0010 · 54–80](../../../../../tests/unit/operator_memory_report_test.cpp#L54) | Callable definition: void verify(const mm::Report& report,const resource::MemoryAccount& account) | calls snapshot, check, statistics, owners; guard const auto& snapshot=report.snapshot();check(snapshot.account.owner==account.statistics().owner,"me…; returns row; 6 loop sites · [reviewed contract](#b0010) |
| [B0011 · 81–123](../../../../../tests/unit/operator_memory_report_test.cpp#L81) | Callable definition: void oracle(const mm::Report& report,const Owner& owner) | calls snapshot, check, tables, empty; guard check(report.tables().empty() && report.operators().empty(),"pending/released report exposed commit…; returns state; state.physical.support; 5 loop sites · [reviewed contract](#b0011) |
| [B0012 · 124–127](../../../../../tests/unit/operator_memory_report_test.cpp#L124) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(now.allocations==1 && now.requested_bytes==resource::MemoryAccount::control_bytes(),"memory r… · [reviewed contract](#b0012) |
| [B0013 · 128–137](../../../../../tests/unit/operator_memory_report_test.cpp#L128) | Callable definition: template&lt;class Make&gt; void lifetime(Make make) | calls owner, make, account, statistics; guard check(calls&gt;0 && calls==account.statistics().successful_allocations-before.successful_allocations,"… · [reviewed contract](#b0013) |
| [B0014 · 138–152](../../../../../tests/unit/operator_memory_report_test.cpp#L138) | Callable definition: template&lt;class Make&gt; std::size_t faults(Make make) | calls make, account, accepted, capture; guard check(expected&gt;0 && expected&lt;256,"operator report fault calibration exceeds bound");; returns expected; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 153–183](../../../../../tests/unit/operator_memory_report_test.cpp#L153) | Callable definition: template&lt;class Make&gt; void limits(Make make) | calls make, accepted, capture, usage; guard check(result.stop==expected && !result.report && account.statistics().current==before,"report exact…; growth push_back, reserve; 5 loop sites · [reviewed contract](#b0015) |
| [B0016 · 184–209](../../../../../tests/unit/operator_memory_report_test.cpp#L184) | Callable definition: void phases(const PhysicalPlan& plan,const c02_test::Fixture& f) | calls make_owner, account, accepted, capture; guard const auto value=accepted(capture(owner));check(value.snapshot().availability==mm::Availability::pe…; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 210–230](../../../../../tests/unit/operator_memory_report_test.cpp#L210) | Callable definition: void corruption(const PhysicalPlan& plan,const Database& database) | calls make_owner, accepted, capture, RuntimeTestProbe::set_live_total; guard check(mm::capture(delta).stop==mm::Stop::inconsistent,"memory report certified a corrupted maintain…; 3 loop sites · [reviewed contract](#b0017) |
| [B0018 · 231–255](../../../../../tests/unit/operator_memory_report_test.cpp#L231) | Callable definition: void retained_and_churn(const PhysicalPlan& plan,const c02_test::Fixture& f) | calls make_owner, inputs, adapt_input, begin; guard check(retained&gt;0 && held.snapshot().account.by_lifetime\[static_cast&lt;std::size_t&gt;(resource::Allocati…; returns v.arena.records.retained_records; growth insert; 3 loop sites · [reviewed contract](#b0018) |
| [B0019 · 256–282](../../../../../tests/unit/operator_memory_report_test.cpp#L256) | Callable definition: void wide_and_sql(const c02_test::Fixture& base,const planner::CandidateSnapshot& candidates,bool indexed) | calls std::string, candidate_count, c02_test::shape, candidate; guard check(tree.has_value(),"wide report fixture has no native root");const auto options=indexed?s04_run…; returns make_owner(plan,f.database,Kind::delta,cap,live); make_owner(compiled,f.database,kind,cap); 4 loop sites · [reviewed contract](#b0019) |
| [B0020 · 283–291](../../../../../tests/unit/operator_memory_report_test.cpp#L283) | Callable definition: void inventory_primitive() | calls resource::MemoryAccount::create, allocate, none, check; guard {s04_alloc::Scope none(0);check(account.copy_attributions(owners)==2 && s04_alloc::calls==0,"owner …; growth allocate · [reviewed contract](#b0020) |
| [B0021 · 292–292](../../../../../tests/unit/operator_memory_report_test.cpp#L292) | Closes surrounding scope/type. |  · [reviewed contract](#b0021) |
| [B0022 · 293–320](../../../../../tests/unit/operator_memory_report_test.cpp#L293) | Callable definition: int main(int argc,char** argv) | calls inventory_primitive, c02_test::fixture, c02_test::candidates, std::string_view; guard check(argc==1,"unknown operator memory test argument");; returns 0; make_owner(plan,f.database,kind,cap); 6 loop sites · [reviewed contract](#b0022) |

## B0001

[Lines 1–18](../../../../../tests/unit/operator_memory_report_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:63f485de831fd2577890c738a2fee47ada7c60fb9688a45c1351f4ba6cab2dd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare operator_memory_report_test.cpp: include "ranking_fixture.hpp", "indexed_runtime_fixture.hpp", "crown/runtime/memory_report.hpp", "crown/runtime/session.hpp", "crown/io/memory_report.hpp", "runtime_probe.hpp", "index_allocation.hpp", &lt;filesystem&gt;, &lt;fstream&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;variant&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 19–19](../../../../../tests/unit/operator_memory_report_test.cpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Kind {support,physical,delta,session};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the four runtime owner variants captured by this test. |
| inputs / outputs | Kind has support, physical, delta, and session enumerators; Owner is std::variant&lt;SupportRuntime, PhysicalRuntime, DeltaRuntime, QuerySession::Owner&gt;. |
| invariants | The enum selects which make_owner/capture branch is used; it does not define memory-report Layer or Availability. |
| ownership | Variant owns its selected runtime value; no extra ownership policy is introduced here. |
| failure | No custom failure behavior; variant construction/visitation failures propagate. |
| cost | Fixed enum and variant declaration; selected runtime cost is in callers. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0003

[Lines 20–20](../../../../../tests/unit/operator_memory_report_test.cpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L20:sha256:d5d0e021b9cdc6d8698193bba5c10c88ccfb38ebda103d7167b90c24b4d74cc6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare operator_memory_report_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 21–21](../../../../../tests/unit/operator_memory_report_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message){if(!value)throw std::runtime_error(std::string(message));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the report test's fail-fast assertion boundary. |
| inputs / outputs | Boolean condition and message string_view in; throws std::runtime_error with copied message when false. |
| invariants | Checks only the supplied condition and does not aggregate failures. |
| ownership | Message is borrowed until exception construction; no lasting state. |
| failure | False condition throws std::runtime_error; string allocation errors propagate. |
| cost | One branch; diagnostic creation only on failure. |
| Design | [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0005

[Lines 22–22](../../../../../tests/unit/operator_memory_report_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sum(resource::MemoryUsage& a,const resource::MemoryUsage& b){a.allocations+=b.allocations;a.requested_bytes+=b.requested_bytes;a.payload_bytes+=b.payload_bytes;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add allocation, requested-byte, and payload-byte components into a MemoryUsage total. |
| inputs / outputs | Mutable MemoryUsage a and const MemoryUsage b in; adds b.allocations, b.requested_bytes, and b.payload_bytes to a. |
| invariants | Only those three counters are summed; overflow handling is not added by this helper. |
| ownership | Both arguments are borrowed references; mutation is limited to a. |
| failure | No explicit exception handling; arithmetic follows the unsigned field operations. |
| cost | Three fixed counter additions. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0006

[Lines 23–28](../../../../../tests/unit/operator_memory_report_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount account(const Owner& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the original MemoryAccount associated with a selected runtime Owner. |
| inputs / outputs | Owner variant in; visits SupportRuntime/PhysicalRuntime/DeltaRuntime plan().account(), or QuerySession::Owner get_deleter().account(), and returns a MemoryAccount handle. |
| invariants | The session alternative is distinguished with if constexpr on QuerySession::Owner; returned account is the owner's existing account, not a new grant. |
| ownership | Owner is borrowed for visitation; returned MemoryAccount shares the account control. |
| failure | Invalid/empty runtime access and variant visitation failures propagate. |
| cost | One variant visitation and one account-handle copy. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0007

[Lines 29–43](../../../../../tests/unit/operator_memory_report_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Owner make_owner(const PhysicalPlan& plan,const Database& database,Kind kind,std::uint64_t cap,LiveMaintenance live=LiveMaintenance::on_output) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one selected runtime owner at an explicit cap and seed support, physical, delta, or session state. |
| inputs / outputs | Plan, Database, Kind, cap, and LiveMaintenance in; builds options with memory_limit_bytes=cap and capture_transitions=false, then returns Owner. Support applies adapted input rows; physical/delta use initialize; session uses create_typed. |
| invariants | The cap is an explicit finite requested-byte allowance (default call-site allowance is 64*1024*1024); capture_transitions is disabled. The support branch increments sequence only for successfully adapted input tuples. Other branches use their specified initialization routes. |
| ownership | Returned variant owns its runtime; plan/database inputs are passed to the runtime constructor/initializer and local options die on return. |
| failure | Plan adaptation, account admission, runtime initialization, or session creation errors propagate; no partially built owner is returned. |
| cost | Support branch scans plan.inputs() and database rows and applies one insert per accepted tuple; other branches perform one initialize/create_typed call. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0008

[Lines 44–49](../../../../../tests/unit/operator_memory_report_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
mm::Attempt capture(const Owner& owner,mm::Limits limits={}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch a bounded memory::capture call to the selected runtime owner. |
| inputs / outputs | Owner variant and memory::Limits in; visits the runtime overload, dereferencing QuerySession::Owner for the session alternative; returns mm::Attempt. |
| invariants | The limits are forwarded unchanged; this helper does not require Stop::complete or a report. |
| ownership | Owner is borrowed during capture; Attempt owns any returned Report. |
| failure | The capture overloads are declared noexcept and return Attempt stop status for capture outcomes; this wrapper has no local catch around std::visit. |
| cost | One variant visit and one capture with the supplied selected work/owner/table/operator quotas. Those quotas do not establish a wall-clock bound or count every allocator, comparison or cleanup instruction. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0009

[Lines 50–53](../../../../../tests/unit/operator_memory_report_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
mm::Report accepted(mm::Attempt attempt) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a completed capture with a present Report and return a shared copy of its funded report handle. |
| inputs / outputs | mm::Attempt by value in; requires stop==Stop::complete and report present, then returns the contained mm::Report by value (Report's declared copy shares its funded arrays). |
| invariants | Only complete+present is accepted; report contents are validated by separate helpers. |
| ownership | Attempt is locally owned; return copies the contained Report handle, whose shared Data remains owned by the returned value. |
| failure | Any non-complete stop or absent report throws std::runtime_error including numeric stop value. |
| cost | One status/presence check and one shared Report-handle copy; this does not recapture the arrays. |
| Design | [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0010

[Lines 54–80](../../../../../tests/unit/operator_memory_report_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(const mm::Report& report,const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check report/account identity, funded report vectors, owner partitions, and reported table/arena/operator joins. |
| inputs / outputs | Report and original MemoryAccount in; sums owner current/by_purpose/by_lifetime and verifies the report snapshot, allocator accounts, table/arena owner joins, record counts, and operator attribution joins. |
| invariants | The live account is used for owner identity. Report-vector allocators must have that owner, and sorted unique owner rows must sum to the recorded snapshot.account current/purpose/lifetime totals. Those recorded totals need not equal the later live ledger. Table/arena bindings join to recorded owner rows and their recorded live/retained/free counts; operator attributions must have a recorded owner row. |
| ownership | Report and account are borrowed; local counters/arrays and optional prior attribution hold comparison state. |
| failure | Any mismatch throws std::runtime_error. find() throws if a binding has no allocation partition; std::visit propagates its branch failures. |
| cost | First scans O owner rows and their fixed purpose/lifetime arrays. Each of T tables does two linear owner-row searches and each of P operators does one, so lookup work can be O(O*(T+P)); it is not simply linear in the combined inventory size. Fixed-record comparisons and diagnostics are additional. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0011

[Lines 81–123](../../../../../tests/unit/operator_memory_report_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void oracle(const mm::Report& report,const Owner& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare committed operator inventory to canonical runtime counts, while requiring pending/released captures to omit operator facts. |
| inputs / outputs | Report and Owner in; non-committed availability requires empty tables/operators. For committed non-session owners, reads canonical_state and compares support table/operator counts; for DeltaRuntime also compares optional materialized factor row/key/member counts. |
| invariants | For a visible support table, canonical visible factor must exist. \`parent_rows\`/\`child_rows\` are checked as summed bucket memberships, separately from \`parent_keys\`/\`child_keys\`. QuerySession skips the committed canonical comparison; the function is a selected report oracle, not a complete independent model for all owner types. |
| ownership | Report/Owner are borrowed; canonical state and find_if results are local copies/iterators. |
| failure | Mismatched node/factor/count/availability throws std::runtime_error; variant operations propagate. |
| cost | Scans canonical support nodes and report tables/operators; delta membership checks sum each selected bucket's rows. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0012

[Lines 124–127](../../../../../tests/unit/operator_memory_report_test.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require that only the MemoryAccount control allocation remains after report/runtime storage is released. |
| inputs / outputs | MemoryAccount reference in; checks invariants and requires current.allocations==1 and current.requested_bytes==MemoryAccount::control_bytes(). |
| invariants | The assertion concerns the account's current requested bytes and controller only; it says nothing about process RSS or unrelated allocations. |
| ownership | Account is borrowed and remains alive for the diagnostic. |
| failure | Ledger/check mismatch throws; no cleanup or repair is attempted. |
| cost | One account invariant/statistics diagnostic. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0013

[Lines 128–137](../../../../../tests/unit/operator_memory_report_test.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> void lifetime(Make make) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check report capture allocations and report-copy lifetime against the original runtime account. |
| inputs / outputs | Builds one owner at the 64 MiB allowance, counts one capture, retains and copies its Report, then resets the Owner and verifies/releases both reports inside s04_alloc::Scope(0). The function does not separately assert a zero calls counter for that final scope. |
| invariants | Capture makes positive covered-new calls equal to the account successful-allocation delta. Immediately after capture, its snapshot.account equals the live statistics. Copies remain verifiable against their recorded partitions after owner reset; releasing all runtime/report owners leaves only the controller. These are finite lifetime/account checks. |
| ownership | Optional Owner, Attempt, and Reports explicitly retain/reset the report/account-owned state; account handle outlives runtime/report locals. |
| failure | accepted() rejects incomplete capture and check failures propagate. The final persistent deny-new scope targets covered C++ new attempts; it is not an explicit all-allocator or malloc measurement. |
| cost | One runtime construction, capture, report copy, owner teardown, repeated inventory checks, and final account diagnostic. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0014

[Lines 138–152](../../../../../tests/unit/operator_memory_report_test.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> std::size_t faults(Make make) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure persistent C++ new failure positions during report capture and verify no tentative account bytes are published. |
| inputs / outputs | Constructs one owner and an initial accepted held Report. Counts covered-new calls from a second capture (without separately accepting its status), requires 0&lt;expected&lt;256, then checks points 0 through expected inclusive; returns expected. |
| invariants | Each point before expected must return Stop::allocation_failure with no report, exactly point+1 covered C++ new calls, and unchanged account current usage; a fresh capture succeeds afterward. At expected, capture completes with expected calls. Previously held and new reports remain verifiable. Bound applies to this fixture's C++ new positions, not libc malloc or general report work. |
| ownership | Owner and one accepted Report remain alive across points; each Attempt is local; account snapshot compares before/after. |
| failure | Unexpected Stop/call count or changed usage throws; capture reports its allocation failures through Attempt status. |
| cost | One initial held capture plus one request-count calibration, expected+1 injected capture attempts (at most 256), and one successful retry capture for every expected failing point; report/account verification adds its own scans. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0015

[Lines 153–183](../../../../../tests/unit/operator_memory_report_test.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> void limits(Make make) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact/one-under logical capture limits and finite report-hoarding byte peaks. |
| inputs / outputs | Factory callable in; learns mm::Usage, checks exact and one-under work/owners/tables/operators limits, then holds reports until an observed peak increase within 2048 captures and compares cap=peak versus peak-1. |
| invariants | Each exact logical cap completes; each one-under cap returns its matching Stop and no report without changing account current usage. For hoarding, exact observed account peak is admitted and peak-1 returns allocation_failure without leaking current bytes; held report remains valid and the one-under owner can retry after one held report is removed. The cap peak and 2048 scan are finite fixture observations, not universal maxima. |
| ownership | Each owner/report vector is scoped to its loop; retained Reports intentionally keep report arrays charged to the original account. |
| failure | accepted() rejects incomplete results; explicit checks report wrong Stop/bytes. No rollback of the held report set is promised beyond normal scope destruction. |
| cost | One usage calibration, eight exact/one-under logical cases, then up to 2048 captures to find a growth crossing. Each of two byte-cap routes makes pins held captures plus one probe; the under-cap route removes one held report and captures once more. Inventory and account diagnostics add their own work. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0016

[Lines 184–209](../../../../../tests/unit/operator_memory_report_test.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void phases(const PhysicalPlan& plan,const c02_test::Fixture& f) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect pending, committed, stopped, and released report availability for each of four owner kinds. |
| inputs / outputs | Plan and fixture in; loops Kind::support/physical/delta/session, captures pending owner state, verifies/oracles it, injects zero covered C++ new calls to require allocation_failure without storage change, and for session checks committed-after-stop then released-after-drop. |
| invariants | Pending report availability must be pending and report table/operator facts consistent with selected availability rules; pending capture failure cannot mutate account current. Stopped session capture is committed, dropped session capture is released and still passes selected verification. One operation path per owner kind is exercised. |
| ownership | Owner variant owns each runtime; each prepared update/batch is local and explicitly rolled back/stopped/dropped along its branch. |
| failure | Queue admission, begin, prepare, capture, or assertions may fail and propagate; the zero-allocation report attempt is expected to return a Stop status. |
| cost | Exactly four owner branches, each with one pending capture and one injected report-failure capture; session adds stop/drop captures. |
| Design | [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0017

[Lines 210–230](../../../../../tests/unit/operator_memory_report_test.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void corruption(const PhysicalPlan& plan,const Database& database) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject selected corrupt maintained DeltaRuntime totals/bucket degrees and require memory capture to reject them as inconsistent. |
| inputs / outputs | Plan and Database in; creates delta owner, changes live_factor/live_parent/live_child totals to 999 one at a time, restores each, then changes first nonempty parent/child bucket degree per factor and restores it. |
| invariants | Every modified total or selected bucket must make capture stop inconsistent; after restoring totals/buckets inspect_invariants().valid() and the previously retained good Report remains verifiable. Empty buckets are skipped; this is not exhaustive corruption of every report field. |
| ownership | DeltaRuntime owns maintained state; good Report is retained; old scalar totals and bucket values are saved and restored explicitly. |
| failure | Probe, capture, or check failures propagate; the test does not add an exception guard around the mutations. |
| cost | Three maintained-total mutations, then at most two first-bucket mutations per canonical factor (one parent and one child side), skipping empty sides. Each mutation makes one capture; the test does not iterate every bucket in a nonempty side. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0018

[Lines 231–255](../../../../../tests/unit/operator_memory_report_test.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retained_and_churn(const PhysicalPlan& plan,const c02_test::Fixture& f) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check retained journal bytes and free-pool classification, then compare account current usage after 20 physical duplicate/churn passes. |
| inputs / outputs | Erases one support input and holds its SupportEpoch and captured Report. Resets the epoch inside Scope(0), without separately checking its calls counter, then captures released-slot state. Runs twenty physical insert/duplicate-insert/erase passes with report captures after insert and erase. |
| invariants | Held report must show positive retained_records and retained lifetime bytes. After epoch release, report has zero retained_records, positive free slots, and positive free_pool bytes. For physical churn, account current usage after first pass is baseline and all following passes must equal it. The selected fixture/passes do not prove all workloads stabilize. |
| ownership | The erased SupportEpoch retains deleted-record pins. Reports retain captured numeric inventory arrays and the account, not those runtime row pins: a later report observes zero retained records after epoch reset while the old report remains alive. The separate physical owner retains reusable capacity. |
| failure | Apply, capture and assertion errors propagate. Epoch reset runs under persistent covered-new denial; that scope has no separate calls==0 assertion and is not a malloc/RSS observation. |
| cost | One support erase and two support report captures, followed by exactly twenty passes of three physical updates and two report captures (sixty updates/forty captures). Report verification includes its repeated owner lookups. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0019

[Lines 256–282](../../../../../tests/unit/operator_memory_report_test.cpp#L256); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void wide_and_sql(const c02_test::Fixture& base,const planner::CandidateSnapshot& candidates,bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check wide binary-key delta reports across three live-maintenance modes and a normalized SQL route, including report lifetime/failure/logical limits. |
| inputs / outputs | Base Fixture, CandidateSnapshot and indexed flag in. Builds a 4101-byte x-key fixture and shape-0 plan; initializes Delta owners for on_output/incremental/eager reports and runs lifetime/fault/limit suites. Then binds/normalizes one SQL query, lowers its candidate 0 plan, and uses that real compiled plan for four owner-kind suites. |
| invariants | Wide reports pass verify/oracle and require some materialized factor with parent_rows&gt;parent_keys. SQL binding and normalization must succeed before runtime construction from the SQL-derived plan. The checks exercise selected compiler/runtime/report routes; they do not compare query result rows with an independent SQL engine or cover all candidate shapes. |
| ownership | Fixture copies, plans, Owner values, reports, and candidate snapshot are local; make lambdas construct fresh owners at each requested cap. |
| failure | Missing shape-0 candidate, bind/normalize mismatch, capture failure, or contract check throws; called fault/limit helpers retain their own status handling. |
| cost | Three live-maintenance modes run lifetime/fault/limit suites, then four owner kinds run those suites on one lowered normalized SQL plan; each suite includes bounded report capture/fault loops. |
| Design | [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0020

[Lines 283–291](../../../../../tests/unit/operator_memory_report_test.cpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void inventory_primitive() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that caller-buffer attribution inventory includes controller/block tags and rejects an undersized buffer without allocation. |
| inputs / outputs | Creates a 4096-byte MemoryAccount and one 128-byte scratch MemoryBlock attributed to cursor 99; calls copy_attributions with a two-slot array under zero covered C++ new calls, then with a one-slot span. |
| invariants | Two entries must be returned in expected order: default controller attribution followed by cursor/99. Undersized span must throw MemoryFailure with MemoryFault::contract. Zero-call checks concern the replacement-new hook, while MemoryAccount API documents this diagnostic itself as allocation-free. |
| ownership | MemoryAccount owns controller and block; the caller owns the fixed array and block local. |
| failure | Wrong tags/count throw std::runtime_error; expected short-buffer MemoryFailure is caught and classified. |
| cost | One two-entry attribution scan and one expected short-buffer rejection. |
| Design | [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |

## B0021

[Lines 292–292](../../../../../tests/unit/operator_memory_report_test.cpp#L292); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L292-L292:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in operator_memory_report_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 293–320](../../../../../tests/unit/operator_memory_report_test.cpp#L293); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide default test and optional --export-directory entry modes for operator memory reports. |
| inputs / outputs | Always runs inventory_primitive and constructs Fixture/CandidateSnapshot. Exact argc==3 and --export-directory creates the directory and attempts eight JSON report exports (two backends/four kinds). Otherwise argc must be 1 and the default test matrix runs. |
| invariants | Export filenames are reference-/indexed- plus numeric Kind and .json; normal test loops both backend choices, every candidate_count shape, and four kinds, then runs phases/corruption/retained_and_churn only at shape==0 and wide_and_sql once per backend. Any other argument shape throws. This is source behavior; packet author did not execute it. |
| ownership | The entry owns fixture/candidate and per-loop owners/reports. Export streams target caller-selected names and use normal ofstream truncation for existing files; no transactional export set is retained. |
| failure | Thrown std::exceptions are printed and return 1. Directory, JSON, capture or other thrown failures can leave earlier exports. ofstream exceptions are not enabled and stream state is not checked, so open/write failure may set a stream bit without reaching this catch or a nonzero return. |
| cost | The normal matrix spans candidate_count, two backends and four kinds, plus selected shape-0 and wide/SQL suites. The completed export loop makes eight capture/serialization/stream-output attempts; it does not prove eight successful file writes. |
| Design | [include/crown/io/memory_report.hpp](../../../../../include/crown/io/memory_report.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/memory_report.hpp](../../../../../include/crown/runtime/memory_report.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [tests/unit/operator_memory_report_test.cpp](../../../../../tests/unit/operator_memory_report_test.cpp) |
