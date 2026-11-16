# `tests/unit/invariant_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/invariant_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d5da9be615b02f74e08b1b67003cca2473e68a1f7593e6bef6fd17b5746e93f6`. 100 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/unit/invariant_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 10–10](../../../../../tests/unit/invariant_memory_test.cpp#L10) | Callable definition: void check(bool value,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool value,std::string_view message){if(!value)throw std::runtime_error(std::string(mess… · [reviewed contract](#b0002) |
| [B0003 · 11–15](../../../../../tests/unit/invariant_memory_test.cpp#L11) | Callable definition: void verify(const InvariantReport& report,const resource::MemoryAccount& account) | calls statistics, check, get_allocator, account; guard check(report.issues.get_allocator().account().statistics().owner==id,"invariant report issues lost …; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 16–19](../../../../../tests/unit/invariant_memory_test.cpp#L16) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(now.allocations==1 && now.requested_bytes==resource::MemoryAccount::control_bytes(),"invarian… · [reviewed contract](#b0004) |
| [B0005 · 20–42](../../../../../tests/unit/invariant_memory_test.cpp#L20) | Callable definition: template&lt;class Make&gt; void lifetime(Make make) | calls owner, make, account, statistics; guard check(healthy-&gt;valid() && calls&gt;0 && calls==memory.statistics().successful_allocations-before.succe… · [reviewed contract](#b0005) |
| [B0006 · 43–63](../../../../../tests/unit/invariant_memory_test.cpp#L43) | Callable definition: template&lt;class Make&gt; std::size_t faults(Make make) | calls make, corrupt, account, inspect; guard check(expected&gt;0 && expected&lt;8192,"invariant allocation calibration exceeds finite fixture bound");; returns expected; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 64–87](../../../../../tests/unit/invariant_memory_test.cpp#L64) | Callable definition: template&lt;class Make&gt; void limits(Make make,bool byte_caps) | calls make, corrupt, inspect, account; guard check(result.complete==exact && !result.valid(),"invariant exact/one-under work limit changed compl…; growth push_back, reserve; 4 loop sites · [reviewed contract](#b0007) |
| [B0008 · 88–88](../../../../../tests/unit/invariant_memory_test.cpp#L88) | Closes surrounding scope/type. |  · [reviewed contract](#b0008) |
| [B0009 · 89–100](../../../../../tests/unit/invariant_memory_test.cpp#L89) | Callable definition: int main(int argc,char** argv) | calls std::string_view, export_reports, check, each; guard check(argc==1,"unknown invariant memory test argument");std::size_t cases=0;; returns 0; make(plan,database,kind,cap) · [reviewed contract](#b0009) |

## B0001

[Lines 1–9](../../../../../tests/unit/invariant_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:b24ba16fab78bc27bd3a74f51f79bc32e4c80ce2b35893320e839addf7f6c909
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare invariant_memory_test.cpp: include "invariant_fixture.hpp", "index_allocation.hpp", &lt;iostream&gt;, &lt;optional&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 10–10](../../../../../tests/unit/invariant_memory_test.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,std::string_view message){if(!value)throw std::runtime_error(std::string(message));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a failure-only assertion helper for invariant memory checks. |
| inputs / outputs | Input: bool and string_view. |
| invariants | Converts message to std::string only on false. |
| ownership | No state retained. |
| failure | False throws runtime_error. |
| cost | Single predicate branch. |
| Design | [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp) |

## B0003

[Lines 11–15](../../../../../tests/unit/invariant_memory_test.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(const InvariantReport& report,const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check report issue-array and each issue-key account identity against an expected account. |
| inputs / outputs | Inputs: InvariantReport and MemoryAccount. Output: void. |
| invariants | Compares account owner ids for issues allocator and each issue key. It does not compare purpose/attribution ids, bytes, or every nested payload address. |
| ownership | Report and issue keys remain borrowed for the traversal. |
| failure | First mismatch throws runtime_error. |
| cost | One allocator identity read plus a linear walk over issues. |
| Design | [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0004

[Lines 16–19](../../../../../tests/unit/invariant_memory_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert all account-funded inspection report storage is released. |
| inputs / outputs | Input: MemoryAccount reference. |
| invariants | Checks account invariants and one remaining control allocation with exactly control_bytes requested. |
| ownership | Caller keeps controller alive; no report is retained by helper. |
| failure | Mismatch throws runtime_error. |
| cost | Fixed account-statistics reads. |
| Design | [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/invariant_memory.md](../../../../invariant_memory.md) |

## B0005

[Lines 20–42](../../../../../tests/unit/invariant_memory_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> void lifetime(Make make) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare healthy, corrupted, copied, and retained invariant reports across runtime lifetime. |
| inputs / outputs | Input: fixture factory Make(cap). Runs Support/Physical/Delta kinds from invariant fixture with default 64 MiB allowance. |
| invariants | Healthy inspect and fail-fast check_invariants each require scoped global-new calls equal account successful-allocation delta and current usage return to baseline after temporary report release. Corruption inspect must be complete, invalid, one issue with exact key; report copy must use accounted new requests. After explicit restore, held/copy report serialize identically even after runtime owner destruction; report issues and keys retain original account. Owner reset and report move/release occur inside fail-after-zero scopes, but those destruction scopes do not read calls or triggered; the final controller-only check verifies account release, not an explicit zero-request count. |
| ownership | Report issue vector/key payloads are account-funded; copy deep-copies issue/key storage under same account, move transfers, held report keeps the controller alive. write_invariant_report returns ordinary export string outside the scoped count. |
| failure | Unexpected allocation mismatch, wrong localized issue, invalid restored state, changed retained export, or retained scratch fails. |
| cost | Runs healthy and corrupted full inspections, full check, one report copy and explicit serialization. C++ new parity is only for the scoped report operations, not JSON export or fixture corruption setup. |
| Design | [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/invariant_memory.md](../../../../invariant_memory.md) |

## B0006

[Lines 43–63](../../../../../tests/unit/invariant_memory_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> std::size_t faults(Make make) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calibrate and sweep each intercepted allocation in invariant inspection and report copy. |
| inputs / outputs | Input: fixture factory. Corrupts one record, holds an initial report/export, and measures operator-new count for one inspection as expected. |
| invariants | Expected must be between 1 and 8,191. Every point below expected must bad_alloc with calls==point+1; expected point succeeds with exactly expected calls and complete report. Releasing result restores account current usage. A separately calibrated copy is faulted at every position; source report/export and current bytes remain unchanged. Explicit restore must produce valid inspection. |
| ownership | Held report/key remains account-owned throughout; each failed temporary report/copy unwinds. Export strings are standard caller values and not inside a scope count except source equality is checked afterward. |
| failure | Only std::bad_alloc marks injected failure; mismatch or a different count fails. Calibration is measured in this fixture at runtime, not assumed from a prior run. |
| cost | One calibration inspection + expected+1 positions + one copy calibration + all copy positions, each with report serialization checks; operator-new positions are not a byte/CPU bound. |
| Design | [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [docs/invariant_memory.md](../../../../invariant_memory.md) |

## B0007

[Lines 64–87](../../../../../tests/unit/invariant_memory_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> void limits(Make make,bool byte_caps) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test work/issue completeness boundaries and optional account-byte caps with retained reports. |
| inputs / outputs | Inputs: fixture factory and byte_caps flag. First corrupts one record, compares full work/issue limits with exact and one-under; if byte_caps true, hoards reports to measure a real peak and repeats the same report count at exact/peak-1 caps. |
| invariants | Exact work/issue cases must be complete (but invalid due to corruption); one-under is incomplete and invalid; zero issue limit returns no issues. Byte case keeps pins reports alive, requires exact admission vs one-under bad_alloc without current-byte leak, then releases one pinned report and successfully inspects under unchanged cap. byte_caps only enabled for shape 0 by main. |
| ownership | Retained report handles pin accounted issue/key arrays; std::vector&lt;InvariantReport&gt;::reserve and writer exports are ordinary fixture allocations outside account. No refill or new allowance on retry. |
| failure | No expected work/issue exception: stopped report fields are asserted. Byte boundary catches bad_alloc only; cap remains unchanged. |
| cost | Work units and issue count are logical limits; byte case measures account requested-byte peak under fixed repeated-report count, not CPU/RSS or allocator overhead. |
| Design | [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/invariant_memory.md](../../../../invariant_memory.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 88–88](../../../../../tests/unit/invariant_memory_test.cpp#L88); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L88-L88:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in invariant_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 89–100](../../../../../tests/unit/invariant_memory_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the invariant allocation matrix or export fixture reports. |
| inputs / outputs | Inputs: optional --export-directory DIR; otherwise no args. No-argument path iterates fixture flavor/backend/shape/runtime-kind combinations and calls lifetime, faults and limits; expected total is 42. |
| invariants | Fixture each provides three flavors, 7 total shapes (3+3+1), two backends and three kinds, hence 42 cases. Export mode calls fixture export and returns before the 42-case assertion. Catches std::exception, reports failure and returns 1. |
| ownership | Exported files and outer vectors/streams are caller/test resources; runtime reports retain account-owned issue data only for their scopes. |
| failure | Unknown arguments or a changed matrix/assertion produce nonzero status. |
| cost | 42 finite fixture cases; each has a bounded measured allocation sweep and only shape 0 runs the account-byte hoarding cap branch. This packet did not execute main. |
| Design | [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [tests/support/invariant_fixture.hpp](../../../../../tests/support/invariant_fixture.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/invariant_memory.md](../../../../invariant_memory.md) |
