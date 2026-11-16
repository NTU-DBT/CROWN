# `tests/unit/planner_continuation_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/planner_continuation_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d5394f2b5892dbb4fa461ef5644075b22ad8790e5a71da9e6c6c17648d0ea417`. 1029 lines partitioned into 87 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–27](../../../../../tests/unit/planner_continuation_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Faults direct ordinary/nothrow scalar/array new via malloc-backed replacements. · [reviewed contract](#b0001) |
| [B0002 · 28–36](../../../../../tests/unit/planner_continuation_exception_test.cpp#L28) | Callable definition: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes) | calls std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 37–37](../../../../../tests/unit/planner_continuation_exception_test.cpp#L37) | Explanatory comments or spacing. |  |
| [B0004 · 38–43](../../../../../tests/unit/planner_continuation_exception_test.cpp#L38) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0004) |
| [B0005 · 44–45](../../../../../tests/unit/planner_continuation_exception_test.cpp#L44) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 46–46](../../../../../tests/unit/planner_continuation_exception_test.cpp#L46) | Callable definition: void* operator new(std::size_t bytes) | calls malloc_new; returns malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 47–47](../../../../../tests/unit/planner_continuation_exception_test.cpp#L47) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns malloc_new(bytes); growth new · [reviewed contract](#b0007) |
| [B0008 · 48–51](../../../../../tests/unit/planner_continuation_exception_test.cpp#L48) | Callable definition: void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept | calls malloc_new; returns malloc_new(bytes); nullptr; growth new · [reviewed contract](#b0008) |
| [B0009 · 52–55](../../../../../tests/unit/planner_continuation_exception_test.cpp#L52) | Callable definition: void* operator new\[\](std::size_t bytes, const std::nothrow_t&) noexcept | calls ; returns malloc_new(bytes); nullptr; growth new · [reviewed contract](#b0009) |
| [B0010 · 56–56](../../../../../tests/unit/planner_continuation_exception_test.cpp#L56) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0010) |
| [B0011 · 57–57](../../../../../tests/unit/planner_continuation_exception_test.cpp#L57) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0011) |
| [B0012 · 58–58](../../../../../tests/unit/planner_continuation_exception_test.cpp#L58) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0012) |
| [B0013 · 59–59](../../../../../tests/unit/planner_continuation_exception_test.cpp#L59) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0013) |
| [B0014 · 60–60](../../../../../tests/unit/planner_continuation_exception_test.cpp#L60) | Callable definition: void operator delete(void* pointer, const std::nothrow_t&) noexcept | calls std::free · [reviewed contract](#b0014) |
| [B0015 · 61–61](../../../../../tests/unit/planner_continuation_exception_test.cpp#L61) | Callable definition: void operator delete\[\](void* pointer, const std::nothrow_t&) noexcept | calls  · [reviewed contract](#b0015) |
| [B0016 · 62–74](../../../../../tests/unit/planner_continuation_exception_test.cpp#L62) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_destructible_v&lt;ExactSearch&gt;); · [reviewed contract](#b0016) |
| [B0017 · 75–77](../../../../../tests/unit/planner_continuation_exception_test.cpp#L75) | Callable definition: void check(bool condition, const char* message) | calls std::runtime_error; guard void check(bool condition, const char* message) { · [reviewed contract](#b0017) |
| [B0018 · 78–78](../../../../../tests/unit/planner_continuation_exception_test.cpp#L78) | Explanatory comments or spacing. |  |
| [B0019 · 79–82](../../../../../tests/unit/planner_continuation_exception_test.cpp#L79) | Type/record definition: struct Fixture |  · [reviewed contract](#b0019) |
| [B0020 · 83–83](../../../../../tests/unit/planner_continuation_exception_test.cpp#L83) | Explanatory comments or spacing. |  |
| [B0021 · 84–109](../../../../../tests/unit/planner_continuation_exception_test.cpp#L84) | Callable definition: Fixture fixture_for(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& scopes, const std::vector&lt;std::size_t&gt;& head) | calls insert, begin, end, reserve; returns fixture; growth emplace_back, insert, push_back, reserve; 5 loop sites · [reviewed contract](#b0021) |
| [B0022 · 110–110](../../../../../tests/unit/planner_continuation_exception_test.cpp#L110) | Explanatory comments or spacing. |  |
| [B0023 · 111–122](../../../../../tests/unit/planner_continuation_exception_test.cpp#L111) | Callable definition: bool same_constraint(const Constraint& left, const Constraint& right) | calls index; returns false; a-&gt;name == b.name && a-&gt;columns == b.columns && a-&gt;status == b.status · [reviewed contract](#b0023) |
| [B0024 · 123–123](../../../../../tests/unit/planner_continuation_exception_test.cpp#L123) | Explanatory comments or spacing. |  |
| [B0025 · 124–154](../../../../../tests/unit/planner_continuation_exception_test.cpp#L124) | Callable definition: bool same_catalog(const Catalog& left, const Catalog& right) | calls size, same_constraint; returns false; false; 5 loop sites · [reviewed contract](#b0025) |
| [B0026 · 155–155](../../../../../tests/unit/planner_continuation_exception_test.cpp#L155) | Explanatory comments or spacing. |  |
| [B0027 · 156–163](../../../../../tests/unit/planner_continuation_exception_test.cpp#L156) | Callable definition: bool same_term(const Term& left, const Term& right) | calls index; returns false; *variable == std::get&lt;VariableId&gt;(right) · [reviewed contract](#b0027) |
| [B0028 · 164–164](../../../../../tests/unit/planner_continuation_exception_test.cpp#L164) | Explanatory comments or spacing. |  |
| [B0029 · 165–182](../../../../../tests/unit/planner_continuation_exception_test.cpp#L165) | Callable definition: bool same_query(const Query& left, const Query& right) | calls size, same_term; returns false; false; 4 loop sites · [reviewed contract](#b0029) |
| [B0030 · 183–183](../../../../../tests/unit/planner_continuation_exception_test.cpp#L183) | Explanatory comments or spacing. |  |
| [B0031 · 184–196](../../../../../tests/unit/planner_continuation_exception_test.cpp#L184) | Callable definition: bool same_tree(const FreeConnexTree& left, const FreeConnexTree& right) | calls size; returns false; false; 1 loop sites · [reviewed contract](#b0031) |
| [B0032 · 197–197](../../../../../tests/unit/planner_continuation_exception_test.cpp#L197) | Explanatory comments or spacing. |  |
| [B0033 · 198–210](../../../../../tests/unit/planner_continuation_exception_test.cpp#L198) | Callable definition: bool same_certificate(const HeightCertificate& left, const HeightCertificate& right) | calls has_value, size, same_tree; returns false; false; 1 loop sites · [reviewed contract](#b0033) |
| [B0034 · 211–211](../../../../../tests/unit/planner_continuation_exception_test.cpp#L211) | Explanatory comments or spacing. |  |
| [B0035 · 212–219](../../../../../tests/unit/planner_continuation_exception_test.cpp#L212) | Callable definition: bool same_statistics(const SearchStatistics& a, const SearchStatistics& b) | calls ; returns a.work == b.work && a.states == b.states && a.partitions == b.partitions && · [reviewed contract](#b0035) |
| [B0036 · 220–220](../../../../../tests/unit/planner_continuation_exception_test.cpp#L220) | Explanatory comments or spacing. |  |
| [B0037 · 221–230](../../../../../tests/unit/planner_continuation_exception_test.cpp#L221) | Callable definition: bool same_statistics_shape(const SearchStatistics& a, const SearchStatistics& b) | calls ; returns a.states == b.states && a.partitions == b.partitions &&; source comment (unverified): // P06 fills these compatibility fields from attempted counters, which must · [reviewed contract](#b0037) |
| [B0038 · 231–231](../../../../../tests/unit/planner_continuation_exception_test.cpp#L231) | Explanatory comments or spacing. |  |
| [B0039 · 232–244](../../../../../tests/unit/planner_continuation_exception_test.cpp#L232) | Callable definition: bool same_search_shape(const SearchProgress& a, const SearchProgress& b) | calls same_statistics_shape; returns a.phase == b.phase && a.result == b.result && a.heights == b.heights &&; source comment (unverified): // Attempted/failed counts, active time and last_stop legitimately change · [reviewed contract](#b0039) |
| [B0040 · 245–245](../../../../../tests/unit/planner_continuation_exception_test.cpp#L245) | Explanatory comments or spacing. |  |
| [B0041 · 246–252](../../../../../tests/unit/planner_continuation_exception_test.cpp#L246) | Callable definition: bool same_search_progress(const SearchProgress& a, const SearchProgress& b) | calls same_statistics; returns a.phase == b.phase && a.last_stop == b.last_stop && a.result == b.result && · [reviewed contract](#b0041) |
| [B0042 · 253–253](../../../../../tests/unit/planner_continuation_exception_test.cpp#L253) | Explanatory comments or spacing. |  |
| [B0043 · 254–261](../../../../../tests/unit/planner_continuation_exception_test.cpp#L254) | Callable definition: bool same_replay_shape(const ReplayProgress& a, const ReplayProgress& b) | calls ; returns a.phase == b.phase && a.complete == b.complete && a.valid == b.valid &&; source comment (unverified): // Repeated OOM retries advance only attempted/failure diagnostics. · [reviewed contract](#b0043) |
| [B0044 · 262–262](../../../../../tests/unit/planner_continuation_exception_test.cpp#L262) | Explanatory comments or spacing. |  |
| [B0045 · 263–267](../../../../../tests/unit/planner_continuation_exception_test.cpp#L263) | Callable definition: bool same_replay_progress(const ReplayProgress& a, const ReplayProgress& b) | calls ; returns a.phase == b.phase && a.last_stop == b.last_stop && a.complete == b.complete && · [reviewed contract](#b0045) |
| [B0046 · 268–268](../../../../../tests/unit/planner_continuation_exception_test.cpp#L268) | Explanatory comments or spacing. |  |
| [B0047 · 269–271](../../../../../tests/unit/planner_continuation_exception_test.cpp#L269) | Callable definition: std::uint64_t attempted_total(const SearchProgress& p) | calls ; returns p.producer.attempted + p.replay.attempted · [reviewed contract](#b0047) |
| [B0048 · 272–274](../../../../../tests/unit/planner_continuation_exception_test.cpp#L272) | Callable definition: std::uint64_t committed_total(const SearchProgress& p) | calls ; returns p.producer.committed_transitions + p.replay.committed_transitions · [reviewed contract](#b0048) |
| [B0049 · 275–277](../../../../../tests/unit/planner_continuation_exception_test.cpp#L275) | Callable definition: std::uint64_t failures_total(const SearchProgress& p) | calls ; returns p.producer.allocation_failures + p.replay.allocation_failures · [reviewed contract](#b0049) |
| [B0050 · 278–278](../../../../../tests/unit/planner_continuation_exception_test.cpp#L278) | Explanatory comments or spacing. |  |
| [B0051 · 279–281](../../../../../tests/unit/planner_continuation_exception_test.cpp#L279) | Callable definition: HeightCertificate certificate_for(const OracleResult& result) | calls ; returns {result.algorithm, result.minimum_height, result.tree, result.lower_bounds} · [reviewed contract](#b0051) |
| [B0052 · 282–282](../../../../../tests/unit/planner_continuation_exception_test.cpp#L282) | Explanatory comments or spacing. |  |
| [B0053 · 283–287](../../../../../tests/unit/planner_continuation_exception_test.cpp#L283) | Callable definition: SearchOptions best_found_options() | calls ; returns options · [reviewed contract](#b0053) |
| [B0054 · 288–290](../../../../../tests/unit/planner_continuation_exception_test.cpp#L288) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0054) |
| [B0055 · 291–295](../../../../../tests/unit/planner_continuation_exception_test.cpp#L291) | Type/record definition: struct ReplacementPoint |  · [reviewed contract](#b0055) |
| [B0056 · 296–296](../../../../../tests/unit/planner_continuation_exception_test.cpp#L296) | Explanatory comments or spacing. |  |
| [B0057 · 297–303](../../../../../tests/unit/planner_continuation_exception_test.cpp#L297) | Type/record definition: struct ExactBaseline |  · [reviewed contract](#b0057) |
| [B0058 · 304–304](../../../../../tests/unit/planner_continuation_exception_test.cpp#L304) | Explanatory comments or spacing. |  |
| [B0059 · 305–343](../../../../../tests/unit/planner_continuation_exception_test.cpp#L305) | Callable definition: ExactBaseline calibrate_exact(const Fixture& fixture) | calls ExactSearch::create, best_found_options, incumbent, advance; guard check(advanced.stopped_for == StopReason::quantum_work,; returns result; growth push_back; 1 loop sites; source comment (unverified): // Admission precedes calibration, so the count measures advance only. · [reviewed contract](#b0059) |
| [B0060 · 344–344](../../../../../tests/unit/planner_continuation_exception_test.cpp#L344) | Explanatory comments or spacing. |  |
| [B0061 · 345–367](../../../../../tests/unit/planner_continuation_exception_test.cpp#L345) | Callable definition: void check_exact_final(const ExactSearch& owner, const ExactBaseline& baseline) | calls progress, check, optimum, infeasibility; guard check(progress.phase == SearchPhase::complete && progress.proof_complete, · [reviewed contract](#b0061) |
| [B0062 · 368–368](../../../../../tests/unit/planner_continuation_exception_test.cpp#L368) | Explanatory comments or spacing. |  |
| [B0063 · 369–374](../../../../../tests/unit/planner_continuation_exception_test.cpp#L369) | Callable definition: bool same_incumbent(const std::optional&lt;ValidatedIncumbent&gt;& a, const std::optional&lt;ValidatedIncumbent&gt;& b) | calls has_value, valid, height, same_tree; returns false; !a \|\| (a-&gt;valid() && b-&gt;valid() && a-&gt;height() == b-&gt;height() && · [reviewed contract](#b0063) |
| [B0064 · 375–375](../../../../../tests/unit/planner_continuation_exception_test.cpp#L375) | Explanatory comments or spacing. |  |
| [B0065 · 376–561](../../../../../tests/unit/planner_continuation_exception_test.cpp#L376) | Callable definition: void exact_oom_sweep(const Fixture& fixture, const ExactBaseline& baseline, const char* label, bool require_replacement) | calls check, empty, ExactSearch::create, best_found_options; guard check(!require_replacement \|\| !baseline.replacements.empty(),; growth emplace; 1 loop sites; source comment (unverified): // Owner creation and all input copies happen before persistent failure. · [reviewed contract](#b0065) |
| [B0066 · 562–562](../../../../../tests/unit/planner_continuation_exception_test.cpp#L562) | Explanatory comments or spacing. |  |
| [B0067 · 563–583](../../../../../tests/unit/planner_continuation_exception_test.cpp#L563) | Callable definition: void check_replay_final(const CertificateReplay& owner, const HeightCertificate& expected) | calls progress, check, size, checked; guard check(progress.phase == ReplayPhase::complete && progress.complete && progress.valid && · [reviewed contract](#b0067) |
| [B0068 · 584–584](../../../../../tests/unit/planner_continuation_exception_test.cpp#L584) | Explanatory comments or spacing. |  |
| [B0069 · 585–589](../../../../../tests/unit/planner_continuation_exception_test.cpp#L585) | Type/record definition: struct ReplayBaseline |  · [reviewed contract](#b0069) |
| [B0070 · 590–590](../../../../../tests/unit/planner_continuation_exception_test.cpp#L590) | Explanatory comments or spacing. |  |
| [B0071 · 591–615](../../../../../tests/unit/planner_continuation_exception_test.cpp#L591) | Callable definition: ReplayBaseline calibrate_replay(const Fixture& fixture, const HeightCertificate& certificate) | calls CertificateReplay::create, advance, progress, check; guard check(advanced.stopped_for == StopReason::quantum_work,; returns result; 1 loop sites; source comment (unverified): // Certificate and owner admission are prepared before measuring advance. · [reviewed contract](#b0071) |
| [B0072 · 616–616](../../../../../tests/unit/planner_continuation_exception_test.cpp#L616) | Explanatory comments or spacing. |  |
| [B0073 · 617–779](../../../../../tests/unit/planner_continuation_exception_test.cpp#L617) | Callable definition: void replay_oom_sweep(const Fixture& fixture, const HeightCertificate& certificate, const ReplayBaseline& baseline, const char* l… | calls check, size, CertificateReplay::create, fault; guard check(certificate.lower_bounds.size() &gt; 1,; 1 loop sites · [reviewed contract](#b0073) |
| [B0074 · 780–780](../../../../../tests/unit/planner_continuation_exception_test.cpp#L780) | Explanatory comments or spacing. |  |
| [B0075 · 781–811](../../../../../tests/unit/planner_continuation_exception_test.cpp#L781) | Callable definition: void search_nonallocating_lifecycle(const Fixture& fixture) | calls ExactSearch::create, best_found_options, advance, emplace; guard check(valid && observed == 0,; growth emplace · [reviewed contract](#b0075) |
| [B0076 · 812–812](../../../../../tests/unit/planner_continuation_exception_test.cpp#L812) | Explanatory comments or spacing. |  |
| [B0077 · 813–843](../../../../../tests/unit/planner_continuation_exception_test.cpp#L813) | Callable definition: void replay_nonallocating_lifecycle(const Fixture& fixture, const HeightCertificate& certificate) | calls CertificateReplay::create, advance, emplace, std::move; guard check(valid && observed == 0,; growth emplace · [reviewed contract](#b0077) |
| [B0078 · 844–844](../../../../../tests/unit/planner_continuation_exception_test.cpp#L844) | Explanatory comments or spacing. |  |
| [B0079 · 845–894](../../../../../tests/unit/planner_continuation_exception_test.cpp#L845) | Callable definition: void exact_handle_copies_are_nonallocating(const Fixture& fixture, bool infeasible) | calls ExactSearch::create, best_found_options, advance, check; guard check(done.stopped_for == StopReason::complete, "handle-copy search fixture did not finish"); · [reviewed contract](#b0079) |
| [B0080 · 895–895](../../../../../tests/unit/planner_continuation_exception_test.cpp#L895) | Explanatory comments or spacing. |  |
| [B0081 · 896–932](../../../../../tests/unit/planner_continuation_exception_test.cpp#L896) | Callable definition: void replay_handle_copies_are_nonallocating(const Fixture& fixture, const HeightCertificate& certificate) | calls CertificateReplay::create, advance, check, checked; guard check(done.stopped_for == StopReason::complete, "handle-copy replay fixture did not finish"); · [reviewed contract](#b0081) |
| [B0082 · 933–933](../../../../../tests/unit/planner_continuation_exception_test.cpp#L933) | Explanatory comments or spacing. |  |
| [B0083 · 934–941](../../../../../tests/unit/planner_continuation_exception_test.cpp#L934) | Callable definition: void validate_baseline_certificate(const Fixture& fixture, const HeightCertificate& certificate, const char* expected_algorithm) | calls check, verify_height_certificate; guard check(certificate.algorithm == expected_algorithm, · [reviewed contract](#b0083) |
| [B0084 · 942–942](../../../../../tests/unit/planner_continuation_exception_test.cpp#L942) | Explanatory comments or spacing. |  |
| [B0085 · 943–1016](../../../../../tests/unit/planner_continuation_exception_test.cpp#L943) | Callable definition: void run() | calls fixture_for, planner::minimum_tree, check, calibrate_exact; guard check(hierarchy_before.status == OracleStatus::proven_minimum &&; source comment (unverified): // Construct standalone proof inputs through the strict baseline APIs before · [reviewed contract](#b0085) |
| [B0086 · 1017–1018](../../../../../tests/unit/planner_continuation_exception_test.cpp#L1017) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0086) |
| [B0087 · 1019–1029](../../../../../tests/unit/planner_continuation_exception_test.cpp#L1019) | Callable definition: int main() | calls run, what; returns 0; 1 · [reviewed contract](#b0087) |

## B0001

[Lines 1–27](../../../../../tests/unit/planner_continuation_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L27:sha256:95fa9b93ed0e6fc2d8a4d2522ccdcdd326160a9ba36daf1926b42047f9182096
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_continuation_exception_test.cpp: include "crown/planner/search.hpp", "crown/planner/verify.hpp", "planner_probe.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;variant&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 28–36](../../../../../tests/unit/planner_continuation_exception_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back the test replacement new forms and inject a selected fail-after point. |
| inputs / outputs | Takes a byte count; returns malloc storage or throws std::bad_alloc. |
| invariants | Increments the thread-local call counter before testing the fault point; point zero throws before the backing malloc, and real malloc failure also throws. |
| ownership | Returns raw storage to the matching test delete forms; it owns no planner state. |
| failure | A selected direct call throws before malloc; a failed malloc throws; fail_after remains zero after injected failure. |
| cost | One counter update, fault check, and one malloc attempt when admitted. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0004

[Lines 38–43](../../../../../tests/unit/planner_continuation_exception_test.cpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm one exact failure index for a lexical scope. |
| inputs / outputs | Takes an index and returns no value. |
| invariants | Writes the thread-local fail_after; destruction always resets it to -1 rather than restoring a nested prior value. |
| ownership | Owns no storage or planner facade. |
| failure | No custom exception path; destructor disarms the seam. |
| cost | One TLS write on entry and exit. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0005

[Lines 44–45](../../../../../tests/unit/planner_continuation_exception_test.cpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L45:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in planner_continuation_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 46–46](../../../../../tests/unit/planner_continuation_exception_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the directly replaced ordinary scalar throwing new form. |
| inputs / outputs | Takes requested bytes; returns malloc_new storage. |
| invariants | Routes this form through the counter/fail-after seam. |
| ownership | Caller owns the returned allocation. |
| failure | Propagates std::bad_alloc from injected or real malloc failure. |
| cost | One intercepted request and backing malloc when not faulted. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0007

[Lines 47–47](../../../../../tests/unit/planner_continuation_exception_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the directly replaced ordinary array throwing new form. |
| inputs / outputs | Takes requested bytes; returns malloc_new storage. |
| invariants | Uses the same seam as scalar ordinary new. |
| ownership | Caller owns the returned allocation. |
| failure | Propagates std::bad_alloc. |
| cost | One intercepted request and backing malloc when not faulted. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0008

[Lines 48–51](../../../../../tests/unit/planner_continuation_exception_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the directly defined nothrow scalar new form. |
| inputs / outputs | Takes bytes and std::nothrow_t; returns storage or null. |
| invariants | Calls malloc_new and catches std::bad_alloc to return nullptr. |
| ownership | Caller owns nonnull returned storage. |
| failure | Injected or real bad_alloc is converted to null at this direct nothrow overload. |
| cost | One intercepted request; no exception escapes this overload. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0009

[Lines 52–55](../../../../../tests/unit/planner_continuation_exception_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes, const std::nothrow_t&) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the directly defined nothrow array new form. |
| inputs / outputs | Takes bytes and std::nothrow_t; returns storage or null. |
| invariants | Calls malloc_new and converts std::bad_alloc to nullptr. |
| ownership | Caller owns nonnull returned storage. |
| failure | bad_alloc is caught only here and returned as null. |
| cost | One intercepted request. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0010

[Lines 56–56](../../../../../tests/unit/planner_continuation_exception_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release scalar new storage from this executable’s replacements. |
| inputs / outputs | Takes a raw pointer; returns void. |
| invariants | Calls std::free, including for null as permitted by the C library. |
| ownership | Releases the allocation; it does not own planner objects. |
| failure | Declared noexcept; no CROWN translation. |
| cost | One free call. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0011

[Lines 57–57](../../../../../tests/unit/planner_continuation_exception_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release array new storage from this executable’s replacements. |
| inputs / outputs | Takes a raw pointer; returns void. |
| invariants | Calls std::free. |
| ownership | Releases the allocation. |
| failure | Declared noexcept. |
| cost | One free call. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0012

[Lines 58–58](../../../../../tests/unit/planner_continuation_exception_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized scalar-new storage. |
| inputs / outputs | Takes pointer and size; returns void. |
| invariants | Ignores size and calls std::free. |
| ownership | Releases the allocation. |
| failure | Declared noexcept. |
| cost | One free call. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0013

[Lines 59–59](../../../../../tests/unit/planner_continuation_exception_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized array-new storage. |
| inputs / outputs | Takes pointer and size; returns void. |
| invariants | Ignores size and calls std::free. |
| ownership | Releases the allocation. |
| failure | Declared noexcept. |
| cost | One free call. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0014

[Lines 60–60](../../../../../tests/unit/planner_continuation_exception_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release scalar nothrow-new storage. |
| inputs / outputs | Takes pointer and nothrow tag; returns void. |
| invariants | Ignores tag and calls std::free. |
| ownership | Releases the allocation. |
| failure | Declared noexcept. |
| cost | One free call. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0015

[Lines 61–61](../../../../../tests/unit/planner_continuation_exception_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release array nothrow-new storage. |
| inputs / outputs | Takes pointer and nothrow tag; returns void. |
| invariants | Ignores tag and calls std::free. |
| ownership | Releases the allocation. |
| failure | Declared noexcept. |
| cost | One free call. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0016

[Lines 62–74](../../../../../tests/unit/planner_continuation_exception_test.cpp#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L74:sha256:5014969e9377078527a46fe9d4ab68490c2cf8c572f288dfbb96910471bbcba6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_continuation_exception_test.cpp: bind local aliases/name imports; require 7 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 75–77](../../../../../tests/unit/planner_continuation_exception_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const char* message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one test predicate with its C-string message. |
| inputs / outputs | Takes condition and borrowed message; returns normally if true. |
| invariants | Does not catch or translate other exceptions. |
| ownership | Retains neither argument. |
| failure | False throws std::runtime_error. |
| cost | One conditional branch. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0019

[Lines 79–82](../../../../../tests/unit/planner_continuation_exception_test.cpp#L79); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle one fixture catalog and query. |
| inputs / outputs | Aggregate owns one Catalog and one Query value. |
| invariants | Fields are populated by fixture_for. |
| ownership | Owns copied/moved fixture metadata. |
| failure | No custom failure handling. |
| cost | Plain test data; construction cost is paid by fixture_for. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0021

[Lines 84–109](../../../../../tests/unit/planner_continuation_exception_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture fixture_for(const std::vector<std::vector<std::size_t>>& scopes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an integer-variable CQ fixture from atom scopes and head indices. |
| inputs / outputs | Takes borrowed vectors of zero-based scope/head indices; returns Catalog and Query by value. |
| invariants | Creates int64 columns/variables, one table and atom per scope, and head aliases in supplied order; this test helper’s inputs use contiguous indices from zero. |
| ownership | Returned fixture owns all generated strings, catalog and query values. |
| failure | Bounds/allocations propagate from vector::at and containers. |
| cost | Scans all scopes/head entries and constructs the corresponding fixture metadata. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp) |

## B0023

[Lines 111–122](../../../../../tests/unit/planner_continuation_exception_test.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_constraint(const Constraint& left, const Constraint& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare either supported constraint variant field by field. |
| inputs / outputs | Takes two borrowed Constraint variants; returns equality. |
| invariants | Rejects differing variant indices; compares all declared fields of UniqueConstraint or ForeignKeyConstraint. |
| ownership | Inputs remain borrowed. |
| failure | Unexpected third variant is treated as foreign-key arm by this test helper. |
| cost | Compares the selected variant’s name/columns/status and FK target fields. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0025

[Lines 124–154](../../../../../tests/unit/planner_continuation_exception_test.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_catalog(const Catalog& left, const Catalog& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the catalog metadata observed around admission and retry. |
| inputs / outputs | Takes two borrowed Catalogs; returns equality. |
| invariants | Checks catalog/table counts, schema/name/column metadata, constraint fields, row-count and distinct-count sizes/entries, and key hints. It does not compare every possible future Catalog field. |
| ownership | Inputs borrowed; no copies retained. |
| failure | No exception translation; indexed access/container failures propagate. |
| cost | Visits compared tables, columns, constraints, statistic entries and hints. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0027

[Lines 156–163](../../../../../tests/unit/planner_continuation_exception_test.cpp#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_term(const Term& left, const Term& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare variable and literal Term variants. |
| inputs / outputs | Takes two borrowed Terms; returns equality. |
| invariants | Requires equal variant index; compares VariableId or Value; other same-index terms are accepted as equal. |
| ownership | Inputs borrowed. |
| failure | No custom failure handling. |
| cost | Variant check and one selected value comparison. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0029

[Lines 165–182](../../../../../tests/unit/planner_continuation_exception_test.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_query(const Query& left, const Query& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the query fields used to detect caller-input mutation. |
| inputs / outputs | Takes two borrowed Queries; returns equality. |
| invariants | Checks contradiction, vector sizes, variable name/type, atom occurrence/table/terms, and head variable/alias; delegates term comparison. |
| ownership | Inputs borrowed. |
| failure | No exception translation. |
| cost | Visits the compared query vectors. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0031

[Lines 184–196](../../../../../tests/unit/planner_continuation_exception_test.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_tree(const FreeConnexTree& left, const FreeConnexTree& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two FreeConnexTree witness values. |
| inputs / outputs | Takes borrowed trees; returns equality. |
| invariants | Checks root/claimed metadata and node id, kind, scope, children, occurrence and separator fields. |
| ownership | Inputs borrowed. |
| failure | No custom failure handling. |
| cost | Visits node vectors and their compared fields. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0033

[Lines 198–210](../../../../../tests/unit/planner_continuation_exception_test.cpp#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_certificate(const HeightCertificate& left, const HeightCertificate& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the certificate data retained by baseline and resumed exact search. |
| inputs / outputs | Takes borrowed certificates; returns equality. |
| invariants | Checks algorithm, height, tree presence/content, lower-bound count and each occurrence/generalized/connex/bound field. |
| ownership | Inputs borrowed; no artifact is retained. |
| failure | No exception translation. |
| cost | Scans certificate vectors and tree nodes. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0035

[Lines 212–219](../../../../../tests/unit/planner_continuation_exception_test.cpp#L212); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_statistics(const SearchStatistics& a, const SearchStatistics& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every structural SearchStatistics counter except compatibility work totals. |
| inputs / outputs | Takes two borrowed statistics values; returns equality. |
| invariants | Checks work, states, partitions, candidates, cache, certificate, hierarchy, singleton, empty-body, split, symmetry and bound counters. |
| ownership | Inputs borrowed. |
| failure | No custom failure handling. |
| cost | Fixed sequence of scalar comparisons. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0037

[Lines 221–230](../../../../../tests/unit/planner_continuation_exception_test.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_statistics_shape(const SearchStatistics& a, const SearchStatistics& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare semantic search shape while ignoring retry diagnostics. |
| inputs / outputs | Takes borrowed SearchStatistics values; returns equality. |
| invariants | Checks structural counters but excludes work and certificate_work compatibility totals; caller separately checks monotone attempt/failure counts. |
| ownership | Inputs borrowed. |
| failure | No custom failure handling. |
| cost | Fixed scalar comparisons. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0039

[Lines 232–244](../../../../../tests/unit/planner_continuation_exception_test.cpp#L232); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_search_shape(const SearchProgress& a, const SearchProgress& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact-search semantic cursor and committed-work shape across OOM retries. |
| inputs / outputs | Takes borrowed SearchProgress values; returns equality. |
| invariants | Checks phase/result/heights/completion, committed transitions/depths, structural shape and limit revision; intentionally excludes stop reason, attempts, failures and active time. |
| ownership | Progress snapshots are local values; no owner retained. |
| failure | No custom failure handling. |
| cost | Compares fixed progress fields and structural counters. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md) |

## B0041

[Lines 246–252](../../../../../tests/unit/planner_continuation_exception_test.cpp#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_search_progress(const SearchProgress& a, const SearchProgress& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare complete SearchProgress snapshots. |
| inputs / outputs | Takes borrowed progress values; returns equality. |
| invariants | Includes last stop, producer/replay counters and all listed structural statistics plus limit revision. |
| ownership | Snapshots borrowed. |
| failure | No custom failure handling. |
| cost | Fixed scalar/record comparison. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0043

[Lines 254–261](../../../../../tests/unit/planner_continuation_exception_test.cpp#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_replay_shape(const ReplayProgress& a, const ReplayProgress& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare replay phase/claim and committed-work shape across retries. |
| inputs / outputs | Takes borrowed ReplayProgress values; returns equality. |
| invariants | Checks phase/completion/validity/claim count, committed depth/work and revision; retry totals and stop reason are checked separately. |
| ownership | Snapshots borrowed. |
| failure | No custom failure handling. |
| cost | Fixed field comparisons. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0045

[Lines 263–267](../../../../../tests/unit/planner_continuation_exception_test.cpp#L263); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_replay_progress(const ReplayProgress& a, const ReplayProgress& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare full certificate replay progress snapshots. |
| inputs / outputs | Takes borrowed ReplayProgress values; returns equality. |
| invariants | Includes stop reason and full work counters in addition to claim/phase fields. |
| ownership | Snapshots borrowed. |
| failure | No custom failure handling. |
| cost | Fixed field comparison. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0047

[Lines 269–271](../../../../../tests/unit/planner_continuation_exception_test.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t attempted_total(const SearchProgress& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sum producer and replay attempted transition diagnostics. |
| inputs / outputs | Takes borrowed SearchProgress; returns uint64 sum. |
| invariants | Uses direct unsigned addition; the test does not use this helper to establish overflow behavior. |
| ownership | No retained ownership. |
| failure | No explicit overflow check. |
| cost | Two reads and one addition. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0048

[Lines 272–274](../../../../../tests/unit/planner_continuation_exception_test.cpp#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t committed_total(const SearchProgress& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sum producer and replay committed-transition counts. |
| inputs / outputs | Takes borrowed SearchProgress; returns uint64 sum. |
| invariants | Uses direct unsigned addition; current calibrated fixture values are compared. |
| ownership | No retained ownership. |
| failure | No explicit overflow check. |
| cost | Two reads and one addition. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0049

[Lines 275–277](../../../../../tests/unit/planner_continuation_exception_test.cpp#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t failures_total(const SearchProgress& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sum producer and replay allocation-failure counters. |
| inputs / outputs | Takes borrowed SearchProgress; returns uint64 sum. |
| invariants | The terms are runtime diagnostics; the injected seam here reaches directly defined scalar/array new replacements only. |
| ownership | No retained ownership. |
| failure | No explicit overflow check. |
| cost | Two reads and one addition. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0051

[Lines 279–281](../../../../../tests/unit/planner_continuation_exception_test.cpp#L279); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
HeightCertificate certificate_for(const OracleResult& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a completed OracleResult’s certificate fields into a HeightCertificate. |
| inputs / outputs | Takes borrowed result; returns certificate by value. |
| invariants | Copies algorithm, height, optional tree and lower-bound claims without validating them. |
| ownership | Returned certificate owns its copied fields. |
| failure | Allocation/copy failures propagate. |
| cost | Copies the finite certificate payload. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0053

[Lines 283–287](../../../../../tests/unit/planner_continuation_exception_test.cpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchOptions best_found_options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select best_found policy for owned exact-search fixture owners. |
| inputs / outputs | Takes no arguments; returns default SearchOptions with policy set. |
| invariants | Other defaults remain as defined by SearchOptions. |
| ownership | Returns options by value. |
| failure | No custom failure path. |
| cost | Constant-size option construction. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp) |

## B0054

[Lines 288–290](../../../../../tests/unit/planner_continuation_exception_test.cpp#L288); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L288-L290:sha256:923aa14be2e8f94d7a5eea3f1e5549510cfd3933406b645289d169f6066683bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_continuation_exception_test.cpp: declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0055

[Lines 291–295](../../../../../tests/unit/planner_continuation_exception_test.cpp#L291); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReplacementPoint {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one calibrated incumbent-replacement fault position. |
| inputs / outputs | Aggregate stores replacement allocation offset, old height and old tree. |
| invariants | Populated when the calibrated incumbent becomes strictly better. |
| ownership | The stored tree is an owned value. |
| failure | Copy/allocation failures propagate during calibration. |
| cost | Plain test record. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0057

[Lines 297–303](../../../../../tests/unit/planner_continuation_exception_test.cpp#L297); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ExactBaseline {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the uninterrupted exact-search calibration used as retry oracle. |
| inputs / outputs | Aggregate stores final progress/certificate, replacement points, advance allocation count and infeasible flag. |
| invariants | Certificate is captured from a typed final authority; count measures advance calls after admission. |
| ownership | Owns copied progress, certificate and replacement vector. |
| failure | No custom failure translation. |
| cost | Plain result bundle; payload size follows fixture proof. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0059

[Lines 305–343](../../../../../tests/unit/planner_continuation_exception_test.cpp#L305); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExactBaseline calibrate_exact(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calibrate a complete ExactSearch one transition grant at a time. |
| inputs / outputs | Takes borrowed fixture; returns progress/certificate/replacement offsets and direct-new call count. |
| invariants | Creates owner before resetting call counter; each advance gets quantum 1; checks only expected quantum stop until complete and requires typed optimum/infeasible authority. |
| ownership | Owner is local; baseline copies final proof and incumbent-replacement tree snapshots. |
| failure | Unexpected stop/final type fails through check; bad_alloc propagates outside the injected sweep. |
| cost | Runs until completion; counter includes calls reaching this executable’s four directly defined new replacements during advance only. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md § Authority and policies](../../../../planner_continuations.md) |

## B0061

[Lines 345–367](../../../../../tests/unit/planner_continuation_exception_test.cpp#L345); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_exact_final(const ExactSearch& owner, const ExactBaseline& baseline) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check resumed ExactSearch authority against uninterrupted calibration. |
| inputs / outputs | Takes borrowed owner and baseline; returns after exact progress/artifact assertions. |
| invariants | Requires complete independent proof and correctly typed optimum or infeasibility with identical certificate. |
| ownership | Owner remains caller-owned; optional handles are local owning copies. |
| failure | Mismatch throws runtime_error. |
| cost | Reads progress and typed artifact, then compares finite certificate fields. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md § Authority and policies](../../../../planner_continuations.md) |

## B0063

[Lines 369–374](../../../../../tests/unit/planner_continuation_exception_test.cpp#L369); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_incumbent(const std::optional<ValidatedIncumbent>& a,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare optional previously validated incumbent handles. |
| inputs / outputs | Takes two borrowed optionals; returns equality of presence, validity, height and tree. |
| invariants | Absent handles compare equal; present handles must both be valid. |
| ownership | Handles are immutable owning values copied from the facade. |
| failure | No custom failure path. |
| cost | Constant number of handle/value comparisons. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0065

[Lines 376–561](../../../../../tests/unit/planner_continuation_exception_test.cpp#L376); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exact_oom_sweep(const Fixture& fixture, const ExactBaseline& baseline,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep every calibrated direct-new fault point in ExactSearch advance and same-owner retry. |
| inputs / outputs | Takes fixture, uninterrupted baseline, label and whether an improvement must be faulted; returns after all checks. |
| invariants | Creates each owner before faulting; point N succeeds; earlier points must return allocation_failure without final authority, keep committed semantic shape and any old incumbent, increment attempt/failure diagnostics on repeated retry, make zero quantum no-op, and preserve inputs. The historical \`replacement_failure_here\` index is the first intercepted new request in the quantum-one advance whose clean calibration published a better incumbent; it does not pinpoint the replacement allocation itself. After disarming, that same faulted owner must finish with baseline authority; each point is a fresh owner, while retry within a point is the same owner. |
| ownership | Fixture is borrowed; each loop owns one ExactSearch; progress and handles are local value snapshots. |
| failure | Bad allocation escaping the owner, partial authority, changed input, lost incumbent, or failed same-owner resume throws runtime_error. |
| cost | For N measured advance new calls, tries N fault indices plus point N; the count excludes owner admission and does not measure bytes, direct malloc/system failures, MemoryAccount denial or all process allocation. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md) |

## B0067

[Lines 563–583](../../../../../tests/unit/planner_continuation_exception_test.cpp#L563); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_replay_final(const CertificateReplay& owner, const HeightCertificate& expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the completed CertificateReplay artifact after resumption. |
| inputs / outputs | Takes owner and expected certificate by reference; returns after typed authority comparison. |
| invariants | Requires all lower-bound claims checked and exact checked certificate, then exactly optimum or infeasibility artifact according to presence of tree. |
| ownership | Owner and expected proof are borrowed; copied typed handles are local. |
| failure | Mismatch throws runtime_error. |
| cost | Reads one full progress/artifact and compares its finite payload. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md § Authority and policies](../../../../planner_continuations.md) |

## B0069

[Lines 585–589](../../../../../tests/unit/planner_continuation_exception_test.cpp#L585); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReplayBaseline {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold uninterrupted certificate-replay calibration data. |
| inputs / outputs | Aggregate stores final ReplayProgress, direct-new count and whether ordering phase was observed. |
| invariants | Count is accumulated only around advance calls after proof and owner admission. |
| ownership | Progress is copied; no replay owner retained. |
| failure | No custom failure path. |
| cost | Plain calibration record. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |

## B0071

[Lines 591–615](../../../../../tests/unit/planner_continuation_exception_test.cpp#L591); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReplayBaseline calibrate_replay(const Fixture& fixture, const HeightCertificate& certificate) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calibrate a CertificateReplay owner with one-transition grants. |
| inputs / outputs | Takes borrowed fixture and proof; returns final progress and call count. |
| invariants | Owner/proof admission precedes measured advances; every lower claim is checked; requires order-claims phase and completed checked authority. |
| ownership | Owner local; returned progress is a value snapshot. |
| failure | Unexpected stop or missing authority throws runtime_error. |
| cost | Runs until complete; count records direct replacement new requests during advance, not admission. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md § Grants and retained state](../../../../planner_continuations.md) |

## B0073

[Lines 617–779](../../../../../tests/unit/planner_continuation_exception_test.cpp#L617); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void replay_oom_sweep(const Fixture& fixture, const HeightCertificate& certificate,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault-sweep every measured CertificateReplay advance request and resume the same faulted owner. |
| inputs / outputs | Takes fixture, immutable certificate, baseline and label; returns after indexed, dependency and final-publication fault observations. |
| invariants | Each iteration constructs owner before fault; pre-N points require allocation_failure, no published CheckedCertificate, stable committed/claim shape and retry-only attempt/failure increments; zero quantum/no-allocation facade copies and moves preserve state; after disarm same owner completes against proof. Caller fixture/proof remain equal. |
| ownership | Each loop owns a replay facade; input certificate and fixture borrowed; binding/checked handles and progress snapshots are local copies. |
| failure | Unexpected authority, state/input mutation, missed phase injection, or failure to resume throws runtime_error. |
| cost | Sweeps calibrated advance replacement calls plus point N; does not count admission or prove all allocators, malloc/system/account fault behavior. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md) |

## B0075

[Lines 781–811](../../../../../tests/unit/planner_continuation_exception_test.cpp#L781); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void search_nonallocating_lifecycle(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check ExactSearch facade progress, zero quantum, moves, binding copies, cancel and destruction under fail-after zero. |
| inputs / outputs | Takes fixture by reference; returns after assertions. |
| invariants | Owner is admitted and advanced before fault is armed; guarded actions preserve progress except terminal cancel phase. |
| ownership | Optional owner and binding copies are local owning handles; fixture borrowed. |
| failure | Any guarded direct new request or mismatched progress fails the test. |
| cost | A few facade calls under one armed scope; allocator exclusion is only the replacement-new seam. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0077

[Lines 813–843](../../../../../tests/unit/planner_continuation_exception_test.cpp#L813); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void replay_nonallocating_lifecycle(const Fixture& fixture, const HeightCertificate& certificate) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check CertificateReplay facade progress, zero quantum, moves, binding copies, cancel and destruction under fail-after zero. |
| inputs / outputs | Takes fixture and proof by reference; returns after assertions. |
| invariants | Owner admitted/advanced before arming; zero quantum and move snapshots preserve replay progress; cancel changes phase to cancelled. |
| ownership | Fixture/proof borrowed; owner/handles local. |
| failure | Any intercepted request or state mismatch fails. |
| cost | Finite facade lifecycle actions; no byte or global allocator claim. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0079

[Lines 845–894](../../../../../tests/unit/planner_continuation_exception_test.cpp#L845); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exact_handle_copies_are_nonallocating(const Fixture& fixture, bool infeasible) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check copies of completed ExactSearch artifact handles under fail-after zero. |
| inputs / outputs | Takes fixture and expected infeasible flag; returns after checking handles. |
| invariants | Completes owner before arming; verifies mutually exclusive optimum/infeasibility presence and copies whichever incumbent/typed artifact exists. |
| ownership | Artifact and binding handles are immutable owning copies. |
| failure | Unexpected artifact type, invalid copy or intercepted request fails. |
| cost | Copies a bounded fixture artifact set under direct replacement-new fault. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md § Authority and policies](../../../../planner_continuations.md) |

## B0081

[Lines 896–932](../../../../../tests/unit/planner_continuation_exception_test.cpp#L896); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void replay_handle_copies_are_nonallocating(const Fixture& fixture,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check copies of a completed checked-certificate handle and typed result under fail-after zero. |
| inputs / outputs | Takes fixture and proof by reference; returns after checking matching optimum/infeasible copy. |
| invariants | Completes replay first; typed choice follows whether the input certificate has a tree. |
| ownership | Proof and fixture borrowed; checked/binding/typed handles are owned values. |
| failure | Missing/wrong typed artifact or intercepted request fails. |
| cost | Copies finite proof and bindings under direct replacement-new fault. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0083

[Lines 934–941](../../../../../tests/unit/planner_continuation_exception_test.cpp#L934); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_baseline_certificate(const Fixture& fixture, const HeightCertificate& certificate,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently replay a baseline certificate before using it as the OOM oracle. |
| inputs / outputs | Takes fixture/proof by reference and expected algorithm string; returns after valid report. |
| invariants | Requires exact algorithm tag and strict replay valid without resource stop. |
| ownership | Fixture/proof borrowed; report local. |
| failure | Unexpected tag or invalid/incomplete report throws runtime_error. |
| cost | Runs one complete independent certificate replay over this fixture. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md § Authority and policies](../../../../planner_continuations.md) |

## B0085

[Lines 943–1016](../../../../../tests/unit/planner_continuation_exception_test.cpp#L943); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive hierarchical, connected, infeasible, v1/v2 replay and handle-copy fault scenarios. |
| inputs / outputs | Takes no arguments; creates three finite fixtures and invokes scenario helpers. |
| invariants | Checks strict stateless baselines before owned continuations; connected fixture requires a better incumbent; v1 replay is conditional on CROWN_PLANNER_TESTING. |
| ownership | All fixtures, certificates and owners are local values. |
| failure | Any scenario assertion/error propagates to main. |
| cost | Runs multiple finite sweeps proportional to measured replacement-new calls; no wall-clock guarantee. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md § Authority and policies](../../../../planner_continuations.md) |

## B0086

[Lines 1017–1018](../../../../../tests/unit/planner_continuation_exception_test.cpp#L1017); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1017-L1018:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in planner_continuation_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0087

[Lines 1019–1029](../../../../../tests/unit/planner_continuation_exception_test.cpp#L1019); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the continuation fault scenarios as the executable entry point. |
| inputs / outputs | Takes process argc/argv implicitly; returns 0 on run completion or 1 on caught std::exception. |
| invariants | Catches std::exception, disarms fail_after, and reports the error; success text is printed only if run returns. |
| ownership | No session-long object beyond run-local scope. |
| failure | Exception produces stderr and nonzero return. |
| cost | Calls run once; this source review does not assert that the executable was run. |
| Design | [tests/unit/planner_continuation_exception_test.cpp](../../../../../tests/unit/planner_continuation_exception_test.cpp) |
