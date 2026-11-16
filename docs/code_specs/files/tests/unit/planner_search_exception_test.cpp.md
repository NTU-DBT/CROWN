# `tests/unit/planner_search_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/planner_search_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `2592f858f317bda7c9928780bbd0e4099abfa420ef82fb810c5f3debccae66a7`. 611 lines partitioned into 71 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–30](../../../../../tests/unit/planner_search_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Faults direct ordinary/nothrow scalar/array new via malloc-backed replacements. · [reviewed contract](#b0001) |
| [B0002 · 31–39](../../../../../tests/unit/planner_search_exception_test.cpp#L31) | Callable definition: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes) | calls std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 40–40](../../../../../tests/unit/planner_search_exception_test.cpp#L40) | Explanatory comments or spacing. |  |
| [B0004 · 41–47](../../../../../tests/unit/planner_search_exception_test.cpp#L41) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0004) |
| [B0005 · 48–49](../../../../../tests/unit/planner_search_exception_test.cpp#L48) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 50–50](../../../../../tests/unit/planner_search_exception_test.cpp#L50) | Callable definition: void* operator new(std::size_t bytes) | calls malloc_new; returns malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 51–51](../../../../../tests/unit/planner_search_exception_test.cpp#L51) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns malloc_new(bytes); growth new · [reviewed contract](#b0007) |
| [B0008 · 52–60](../../../../../tests/unit/planner_search_exception_test.cpp#L52) | Callable definition: void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept | calls malloc_new; returns malloc_new(bytes); nullptr; growth new; source comment (unverified): // malloc_new leaves fail_after at zero after an injected failure, so an · [reviewed contract](#b0008) |
| [B0009 · 61–67](../../../../../tests/unit/planner_search_exception_test.cpp#L61) | Callable definition: void* operator new\[\](std::size_t bytes, const std::nothrow_t&) noexcept | calls ; returns malloc_new(bytes); nullptr; growth new · [reviewed contract](#b0009) |
| [B0010 · 68–68](../../../../../tests/unit/planner_search_exception_test.cpp#L68) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0010) |
| [B0011 · 69–69](../../../../../tests/unit/planner_search_exception_test.cpp#L69) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0011) |
| [B0012 · 70–70](../../../../../tests/unit/planner_search_exception_test.cpp#L70) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0012) |
| [B0013 · 71–71](../../../../../tests/unit/planner_search_exception_test.cpp#L71) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0013) |
| [B0014 · 72–72](../../../../../tests/unit/planner_search_exception_test.cpp#L72) | Callable definition: void operator delete(void* pointer, const std::nothrow_t&) noexcept | calls std::free · [reviewed contract](#b0014) |
| [B0015 · 73–73](../../../../../tests/unit/planner_search_exception_test.cpp#L73) | Callable definition: void operator delete\[\](void* pointer, const std::nothrow_t&) noexcept | calls  · [reviewed contract](#b0015) |
| [B0016 · 74–80](../../../../../tests/unit/planner_search_exception_test.cpp#L74) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_destructible_v&lt;planner::OracleResult&gt;); · [reviewed contract](#b0016) |
| [B0017 · 81–83](../../../../../tests/unit/planner_search_exception_test.cpp#L81) | Callable definition: void check(bool condition, const char* message) | calls std::runtime_error; guard void check(bool condition, const char* message) { · [reviewed contract](#b0017) |
| [B0018 · 84–84](../../../../../tests/unit/planner_search_exception_test.cpp#L84) | Explanatory comments or spacing. |  |
| [B0019 · 85–88](../../../../../tests/unit/planner_search_exception_test.cpp#L85) | Type/record definition: struct Fixture |  · [reviewed contract](#b0019) |
| [B0020 · 89–89](../../../../../tests/unit/planner_search_exception_test.cpp#L89) | Explanatory comments or spacing. |  |
| [B0021 · 90–116](../../../../../tests/unit/planner_search_exception_test.cpp#L90) | Callable definition: Fixture fixture_for(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& scopes, const std::vector&lt;std::size_t&gt;& head) | calls insert, begin, end, reserve; returns fixture; growth emplace_back, insert, push_back, reserve; 5 loop sites · [reviewed contract](#b0021) |
| [B0022 · 117–117](../../../../../tests/unit/planner_search_exception_test.cpp#L117) | Explanatory comments or spacing. |  |
| [B0023 · 118–129](../../../../../tests/unit/planner_search_exception_test.cpp#L118) | Callable definition: bool same_constraint(const Constraint& left, const Constraint& right) | calls index; returns false; a-&gt;name == b.name && a-&gt;columns == b.columns && a-&gt;status == b.status · [reviewed contract](#b0023) |
| [B0024 · 130–130](../../../../../tests/unit/planner_search_exception_test.cpp#L130) | Explanatory comments or spacing. |  |
| [B0025 · 131–161](../../../../../tests/unit/planner_search_exception_test.cpp#L131) | Callable definition: bool same_catalog(const Catalog& left, const Catalog& right) | calls size, same_constraint; returns false; false; 5 loop sites · [reviewed contract](#b0025) |
| [B0026 · 162–162](../../../../../tests/unit/planner_search_exception_test.cpp#L162) | Explanatory comments or spacing. |  |
| [B0027 · 163–170](../../../../../tests/unit/planner_search_exception_test.cpp#L163) | Callable definition: bool same_term(const Term& left, const Term& right) | calls index; returns false; *variable == std::get&lt;VariableId&gt;(right) · [reviewed contract](#b0027) |
| [B0028 · 171–171](../../../../../tests/unit/planner_search_exception_test.cpp#L171) | Explanatory comments or spacing. |  |
| [B0029 · 172–189](../../../../../tests/unit/planner_search_exception_test.cpp#L172) | Callable definition: bool same_query(const Query& left, const Query& right) | calls size, same_term; returns false; false; 4 loop sites · [reviewed contract](#b0029) |
| [B0030 · 190–190](../../../../../tests/unit/planner_search_exception_test.cpp#L190) | Explanatory comments or spacing. |  |
| [B0031 · 191–195](../../../../../tests/unit/planner_search_exception_test.cpp#L191) | Callable definition: void check_unchanged(const Fixture& fixture, const Catalog& catalog_before, const Query& query_before) | calls check, same_catalog, same_query; guard check(same_catalog(fixture.catalog, catalog_before), "planner changed the input catalog"); · [reviewed contract](#b0031) |
| [B0032 · 196–196](../../../../../tests/unit/planner_search_exception_test.cpp#L196) | Explanatory comments or spacing. |  |
| [B0033 · 197–209](../../../../../tests/unit/planner_search_exception_test.cpp#L197) | Callable definition: bool same_tree(const FreeConnexTree& left, const FreeConnexTree& right) | calls size; returns false; false; 1 loop sites · [reviewed contract](#b0033) |
| [B0034 · 210–210](../../../../../tests/unit/planner_search_exception_test.cpp#L210) | Explanatory comments or spacing. |  |
| [B0035 · 211–224](../../../../../tests/unit/planner_search_exception_test.cpp#L211) | Callable definition: bool same_certificate(const planner::HeightCertificate& left, const planner::HeightCertificate& right) | calls has_value, size, same_tree; returns false; false; 1 loop sites · [reviewed contract](#b0035) |
| [B0036 · 225–225](../../../../../tests/unit/planner_search_exception_test.cpp#L225) | Explanatory comments or spacing. |  |
| [B0037 · 226–228](../../../../../tests/unit/planner_search_exception_test.cpp#L226) | Callable definition: planner::HeightCertificate certificate_for(const planner::OracleResult& result) | calls ; returns {result.algorithm, result.minimum_height, result.tree, result.lower_bounds} · [reviewed contract](#b0037) |
| [B0038 · 229–229](../../../../../tests/unit/planner_search_exception_test.cpp#L229) | Explanatory comments or spacing. |  |
| [B0039 · 230–236](../../../../../tests/unit/planner_search_exception_test.cpp#L230) | Callable definition: void check_no_partial_result(const planner::OracleResult& result) | calls check, empty; guard check(result.status == planner::OracleStatus::resource_limit, · [reviewed contract](#b0039) |
| [B0040 · 237–237](../../../../../tests/unit/planner_search_exception_test.cpp#L237) | Explanatory comments or spacing. |  |
| [B0041 · 238–250](../../../../../tests/unit/planner_search_exception_test.cpp#L238) | Callable definition: void check_native_occurrences_once(const Query& query, const FreeConnexTree& tree) | calls check, has_value, push_back, std::sort; guard check(node.occurrence.has_value(), "native witness node omitted its occurrence");; growth push_back; 2 loop sites · [reviewed contract](#b0041) |
| [B0042 · 251–251](../../../../../tests/unit/planner_search_exception_test.cpp#L251) | Explanatory comments or spacing. |  |
| [B0043 · 252–269](../../../../../tests/unit/planner_search_exception_test.cpp#L252) | Callable definition: void check_successful_oracle(const Fixture& fixture, const planner::OracleResult& result, std::size_t expected_height, std::strin… | calls check, has_value, empty, planner::validate_tree; guard check(result.status == planner::OracleStatus::proven_minimum, · [reviewed contract](#b0043) |
| [B0044 · 270–273](../../../../../tests/unit/planner_search_exception_test.cpp#L270) | Explanatory comments or spacing. | source comment (unverified): // Return 1 for success, 0 for an honest resource stop, and -1 for a malformed · [reviewed contract](#b0044) |
| [B0045 · 274–280](../../../../../tests/unit/planner_search_exception_test.cpp#L274) | Callable definition: int classify_oracle(const planner::OracleResult& result) | calls empty; returns 1; 0; source comment (unverified): // Return 1 for success, 0 for an honest resource stop, and -1 for a malformed · [reviewed contract](#b0045) |
| [B0046 · 281–281](../../../../../tests/unit/planner_search_exception_test.cpp#L281) | Explanatory comments or spacing. |  |
| [B0047 · 282–286](../../../../../tests/unit/planner_search_exception_test.cpp#L282) | Callable definition: int classify_report(const planner::CertificateReport& report) | calls ; returns 1; 0 · [reviewed contract](#b0047) |
| [B0048 · 287–290](../../../../../tests/unit/planner_search_exception_test.cpp#L287) | Explanatory comments or spacing. | source comment (unverified): // The observed successful path determines the complete sweep length. Point N · [reviewed contract](#b0048) |
| [B0049 · 291–359](../../../../../tests/unit/planner_search_exception_test.cpp#L291) | Callable definition: template &lt;class Invoke, class Classify, class CheckSuccess, class CheckImmutable&gt; void sweep_persistent_allocations(std::string_v… | calls invoke, check, max, classify; guard check(successful_allocations &gt; 0, "planner sweep calibration observed no allocations");; growth emplace; 1 loop sites; source comment (unverified): // The observed successful path determines the complete sweep length. Point N · [reviewed contract](#b0049) |
| [B0050 · 360–360](../../../../../tests/unit/planner_search_exception_test.cpp#L360) | Explanatory comments or spacing. |  |
| [B0051 · 361–364](../../../../../tests/unit/planner_search_exception_test.cpp#L361) | Callable definition: void check_successful_report(const planner::CertificateReport& report) | calls check; guard check(report.valid && !report.resource_limit && report.work &gt; 0, · [reviewed contract](#b0051) |
| [B0052 · 365–365](../../../../../tests/unit/planner_search_exception_test.cpp#L365) | Explanatory comments or spacing. |  |
| [B0053 · 366–378](../../../../../tests/unit/planner_search_exception_test.cpp#L366) | Callable definition: void hierarchy_sweep(const Fixture& fixture) | calls planner::minimum_tree, check_successful_oracle, check, sweep_persistent_allocations; guard check(result.statistics.hierarchy_hits &gt; 0,; returns planner::minimum_tree(fixture.catalog, fixture.query) · [reviewed contract](#b0053) |
| [B0054 · 379–379](../../../../../tests/unit/planner_search_exception_test.cpp#L379) | Explanatory comments or spacing. |  |
| [B0055 · 380–393](../../../../../tests/unit/planner_search_exception_test.cpp#L380) | Callable definition: void connected_symmetry_sweep(const Fixture& fixture) | calls planner::minimum_tree, check_successful_oracle, check, sweep_persistent_allocations; guard check(result.statistics.symmetry_skips &gt; 0,; returns planner::minimum_tree(fixture.catalog, fixture.query) · [reviewed contract](#b0055) |
| [B0056 · 394–394](../../../../../tests/unit/planner_search_exception_test.cpp#L394) | Explanatory comments or spacing. |  |
| [B0057 · 395–412](../../../../../tests/unit/planner_search_exception_test.cpp#L395) | Callable definition: void disconnected_components_sweep(const Fixture& fixture) | calls planner::minimum_tree, check_successful_oracle, check, std::any_of; guard check(result.statistics.component_splits &gt; 0,; returns planner::minimum_tree(fixture.catalog, fixture.query); node.kind == NodeKind::native && node.scope.… · [reviewed contract](#b0057) |
| [B0058 · 413–413](../../../../../tests/unit/planner_search_exception_test.cpp#L413) | Explanatory comments or spacing. |  |
| [B0059 · 414–431](../../../../../tests/unit/planner_search_exception_test.cpp#L414) | Callable definition: void certificate_replay_sweep(const Fixture& fixture, const planner::HeightCertificate& certificate, std::string_view label) | calls planner::verify_height_certificate, check_successful_report, sweep_persistent_allocations, check_unchanged; guard check(same_certificate(certificate, certificate_before),; returns planner::verify_height_certificate(fixture.catalog, fixture.query, certificate) · [reviewed contract](#b0059) |
| [B0060 · 432–432](../../../../../tests/unit/planner_search_exception_test.cpp#L432) | Explanatory comments or spacing. |  |
| [B0061 · 433–454](../../../../../tests/unit/planner_search_exception_test.cpp#L433) | Callable definition: void zero_limits_never_publish_partial_proofs(const Fixture& fixture, const planner::HeightCertificate& certificate) | calls planner::minimum_tree, check_no_partial_result, planner::verify_height_certificate, check; guard check(replay.resource_limit && !replay.valid,; 1 loop sites · [reviewed contract](#b0061) |
| [B0062 · 455–455](../../../../../tests/unit/planner_search_exception_test.cpp#L455) | Explanatory comments or spacing. |  |
| [B0063 · 456–459](../../../../../tests/unit/planner_search_exception_test.cpp#L456) | Callable definition: Fixture residual_seven() | calls fixture_for; returns fixture_for({{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5}, {5}, {0, 6}}, · [reviewed contract](#b0063) |
| [B0064 · 460–460](../../../../../tests/unit/planner_search_exception_test.cpp#L460) | Explanatory comments or spacing. |  |
| [B0065 · 461–523](../../../../../tests/unit/planner_search_exception_test.cpp#L461) | Callable definition: void certificate_replay_resource_limit_is_distinct() | calls residual_seven, planner::minimum_tree, check, reset; guard check(complete.status == planner::OracleStatus::proven_minimum &&; 2 loop sites · [reviewed contract](#b0065) |
| [B0066 · 524–524](../../../../../tests/unit/planner_search_exception_test.cpp#L524) | Explanatory comments or spacing. |  |
| [B0067 · 525–553](../../../../../tests/unit/planner_search_exception_test.cpp#L525) | Callable definition: void typed_result_and_report_cleanup_is_allocation_free(const Fixture& fixture) | calls planner::minimum_tree, check, certificate_for, planner::verify_height_certificate; guard check(result.status == planner::OracleStatus::proven_minimum && result.tree && · [reviewed contract](#b0067) |
| [B0068 · 554–554](../../../../../tests/unit/planner_search_exception_test.cpp#L554) | Explanatory comments or spacing. |  |
| [B0069 · 555–599](../../../../../tests/unit/planner_search_exception_test.cpp#L555) | Callable definition: void run() | calls fixture_for, hierarchy_sweep, connected_symmetry_sweep, disconnected_components_sweep; guard check(v2_certificate.lower_bounds.size() &gt; 1,; returns planner::testing::minimum_tree_baseline(connected.catalog, connected.query); source comment (unverified): // Nested incidence classes exercise generalized-node construction and its · [reviewed contract](#b0069) |
| [B0070 · 600–601](../../../../../tests/unit/planner_search_exception_test.cpp#L600) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0070) |
| [B0071 · 602–611](../../../../../tests/unit/planner_search_exception_test.cpp#L602) | Callable definition: int main() | calls run, what; returns 0; 1 · [reviewed contract](#b0071) |

## B0001

[Lines 1–30](../../../../../tests/unit/planner_search_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L30:sha256:b7315e560157e03a7a7f258c206245f39fd0bdd48ea3e6b30b937bc1ed6161cc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_search_exception_test.cpp: include "crown/planner/oracle.hpp", "crown/planner/search.hpp", "crown/planner/verify.hpp", "planner_probe.hpp", &lt;algorithm&gt;, &lt;chrono&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;variant&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 31–39](../../../../../tests/unit/planner_search_exception_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0004

[Lines 41–47](../../../../../tests/unit/planner_search_exception_test.cpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm one exact failure point, or enter with failures disarmed. |
| inputs / outputs | Optional point defaults to -1; returns no value. |
| invariants | Writes thread-local fail_after; destructor resets to -1; forbid_allocations sets it to zero. |
| ownership | Owns no planner state. |
| failure | No custom exception path. |
| cost | One TLS write per state change. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0005

[Lines 48–49](../../../../../tests/unit/planner_search_exception_test.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L49:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in planner_search_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 50–50](../../../../../tests/unit/planner_search_exception_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0007

[Lines 51–51](../../../../../tests/unit/planner_search_exception_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0008

[Lines 52–60](../../../../../tests/unit/planner_search_exception_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0009

[Lines 61–67](../../../../../tests/unit/planner_search_exception_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0010

[Lines 68–68](../../../../../tests/unit/planner_search_exception_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0011

[Lines 69–69](../../../../../tests/unit/planner_search_exception_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0012

[Lines 70–70](../../../../../tests/unit/planner_search_exception_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0013

[Lines 71–71](../../../../../tests/unit/planner_search_exception_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0014

[Lines 72–72](../../../../../tests/unit/planner_search_exception_test.cpp#L72); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0015

[Lines 73–73](../../../../../tests/unit/planner_search_exception_test.cpp#L73); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0016

[Lines 74–80](../../../../../tests/unit/planner_search_exception_test.cpp#L74); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L80:sha256:ea8f58590ac7e426e5eab66a806de68b78a7522e5f1823e2e7c5bf943b9e32b1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_search_exception_test.cpp: bind local aliases/name imports; require 2 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 81–83](../../../../../tests/unit/planner_search_exception_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const char* message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one test predicate with its C-string diagnostic. |
| inputs / outputs | Takes condition and borrowed message; returns for true. |
| invariants | Does not catch CROWN or standard exceptions. |
| ownership | Retains neither argument. |
| failure | False throws std::runtime_error. |
| cost | One branch. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0019

[Lines 85–88](../../../../../tests/unit/planner_search_exception_test.cpp#L85); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle one planner fixture catalog and query. |
| inputs / outputs | Aggregate owns Catalog and Query values. |
| invariants | Populated by fixture_for using integer scopes/head. |
| ownership | Owns fixture metadata. |
| failure | No custom failure translation. |
| cost | Plain data. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0021

[Lines 90–116](../../../../../tests/unit/planner_search_exception_test.cpp#L90); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp) |

## B0023

[Lines 118–129](../../../../../tests/unit/planner_search_exception_test.cpp#L118); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0025

[Lines 131–161](../../../../../tests/unit/planner_search_exception_test.cpp#L131); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0027

[Lines 163–170](../../../../../tests/unit/planner_search_exception_test.cpp#L163); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0029

[Lines 172–189](../../../../../tests/unit/planner_search_exception_test.cpp#L172); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0031

[Lines 191–195](../../../../../tests/unit/planner_search_exception_test.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_unchanged(const Fixture& fixture, const Catalog& catalog_before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that planner invocation did not mutate caller-owned fixture inputs. |
| inputs / outputs | Takes fixture and pre-call Catalog/Query by const reference; returns void. |
| invariants | Uses the test comparators over the specifically compared catalog/query fields. |
| ownership | All arguments borrowed. |
| failure | Mismatch throws runtime_error through check. |
| cost | Two whole fixture comparisons. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0033

[Lines 197–209](../../../../../tests/unit/planner_search_exception_test.cpp#L197); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0035

[Lines 211–224](../../../../../tests/unit/planner_search_exception_test.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_certificate(const planner::HeightCertificate& left,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the certificate data retained by baseline and resumed exact search. |
| inputs / outputs | Takes borrowed certificates; returns equality. |
| invariants | Checks algorithm, height, tree presence/content, lower-bound count and each occurrence/generalized/connex/bound field. |
| ownership | Inputs borrowed; no artifact is retained. |
| failure | No exception translation. |
| cost | Scans certificate vectors and tree nodes. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0037

[Lines 226–228](../../../../../tests/unit/planner_search_exception_test.cpp#L226); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::HeightCertificate certificate_for(const planner::OracleResult& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy OracleResult’s certificate fields into a HeightCertificate value. |
| inputs / outputs | Takes result by const reference; returns copied certificate. |
| invariants | Performs no validation. |
| ownership | Returned tree/bounds own copied storage. |
| failure | Copy allocation exceptions propagate. |
| cost | Copies the finite proof payload. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0039

[Lines 230–236](../../../../../tests/unit/planner_search_exception_test.cpp#L230); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_no_partial_result(const planner::OracleResult& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require stateless exact search to publish no partial result on resource_limit. |
| inputs / outputs | Takes OracleResult by const reference; returns after assertions. |
| invariants | Requires resource_limit and no minimum height, tree, lower bounds or verified-certificate flag. |
| ownership | Result borrowed. |
| failure | Any leaked partial field throws runtime_error. |
| cost | Fixed status/optional/vector checks. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md § Authority and policies](../../../../planner_continuations.md) |

## B0041

[Lines 238–250](../../../../../tests/unit/planner_search_exception_test.cpp#L238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_native_occurrences_once(const Query& query, const FreeConnexTree& tree) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one native witness node for each query atom occurrence. |
| inputs / outputs | Takes borrowed Query and FreeConnexTree; returns after assertion. |
| invariants | Collects only native node occurrence IDs, sorts them, and compares exactly with \[0, atom_count). |
| ownership | Inputs borrowed; temporary vector local. |
| failure | Missing, repeated or absent occurrence fails through check. |
| cost | Scans tree nodes and sorts the observed finite IDs. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [docs/planner_proofs.md § Independent tree verification (P02)](../../../../planner_proofs.md) |

## B0043

[Lines 252–269](../../../../../tests/unit/planner_search_exception_test.cpp#L252); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_successful_oracle(const Fixture& fixture, const planner::OracleResult& result,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a successful minimum_tree result against expected height, witness, native occurrences and independent replay. |
| inputs / outputs | Takes fixture/result by reference, expected height and algorithm tag; returns void. |
| invariants | Requires proven_minimum, tree/height, verified nonempty lower bounds, valid tree at same height, all native occurrences once, and valid non-resource-limited certificate replay. |
| ownership | Fixture/result borrowed; certificate/replay values are local. |
| failure | Any mismatch fails through check. |
| cost | Tree validation and one full independent certificate replay for the finite fixture. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md § Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md § Independent tree verification (P02)](../../../../planner_proofs.md) |

## B0044

[Lines 270–273](../../../../../tests/unit/planner_search_exception_test.cpp#L270); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L270-L273:sha256:2438e266efe71e790adbf65248334a942184c0ab6e230002b3039542a68d1b4f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Return 1 for success, 0 for an honest resource stop, and -1 for a malformed result. The classifier is also used under persistent failure and must not allocate. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0045

[Lines 274–280](../../../../../tests/unit/planner_search_exception_test.cpp#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int classify_oracle(const planner::OracleResult& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify a stateless OracleResult for the sweep. |
| inputs / outputs | Takes result by const reference; returns 1 success, 0 honest resource stop, -1 malformed. |
| invariants | Success is proven_minimum; resource_limit is accepted only with no partial proof/result fields. |
| ownership | Input borrowed. |
| failure | No throws or diagnostic construction in the classifier. |
| cost | Fixed field checks. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0047

[Lines 282–286](../../../../../tests/unit/planner_search_exception_test.cpp#L282); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int classify_report(const planner::CertificateReport& report) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify a CertificateReport for the replay sweep. |
| inputs / outputs | Takes report by const reference; returns 1 valid, 0 invalid resource stop, -1 malformed. |
| invariants | Accepts only valid&&!resource_limit or !valid&&resource_limit. |
| ownership | Input borrowed. |
| failure | No custom exception path. |
| cost | Two boolean checks. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0048

[Lines 287–290](../../../../../tests/unit/planner_search_exception_test.cpp#L287); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L287-L290:sha256:a119642c2b742d1a47785acb675efc22b7dccf9a2f70741f3c84a4ef7b8208a5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: The observed successful path determines the complete sweep length. Point N lets all N observed allocations succeed, so it is the first un-faulted run; there is no arbitrary test-only cap on the failure positions. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0049

[Lines 291–359](../../../../../tests/unit/planner_search_exception_test.cpp#L291); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Invoke, class Classify, class CheckSuccess, class CheckImmutable>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep stateless planner calls at every observed direct-new replacement failure index. |
| inputs / outputs | Generic callable/califier/success/input-check closures in; returns after exact failure positions and fresh recovery. |
| invariants | A clean invocation calibrates N direct replacement calls; indices &lt;N must throw bad_alloc or return honest resource_limit, preserve inputs and expose no partial proof; N must succeed. Recovery invokes the same request anew after disarming, not a retained owner. |
| ownership | Closures are passed by value; per-attempt optional Result is local and cleared on resource stop. |
| failure | Bad_alloc is caught only around invoke/classify; malformed output or missed index fails through check. |
| cost | Invokes along the successful stateless path N times at fault positions plus calibration and fresh recovery; count excludes bytes and any allocation outside direct replaced new forms. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md) |

## B0051

[Lines 361–364](../../../../../tests/unit/planner_search_exception_test.cpp#L361); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_successful_report(const planner::CertificateReport& report) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a completed independent certificate report with positive work. |
| inputs / outputs | Takes report by const reference; returns void. |
| invariants | Requires valid, not resource-limited, work &gt; 0. |
| ownership | Report borrowed. |
| failure | Mismatch throws runtime_error. |
| cost | Constant field checks. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp) |

## B0053

[Lines 366–378](../../../../../tests/unit/planner_search_exception_test.cpp#L366); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void hierarchy_sweep(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault-sweep hierarchical exact search and assert the hierarchy shortcut was visited. |
| inputs / outputs | Takes fixture by reference; returns after stateless sweep. |
| invariants | Uses minimum_tree; successful result has v2 exact height 1 and hierarchy_hits &gt; 0; inputs compared before/after. |
| ownership | Fixture borrowed. |
| failure | Sweep or oracle mismatch fails. |
| cost | Complete fault sweep based on measured direct replacement calls. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md § Authority and policies](../../../../planner_continuations.md) |

## B0055

[Lines 380–393](../../../../../tests/unit/planner_search_exception_test.cpp#L380); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void connected_symmetry_sweep(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault-sweep connected duplicate-scope exact search and symmetry pruning. |
| inputs / outputs | Takes fixture by reference; returns after sweep. |
| invariants | Clean v2 result has height 2, positive symmetry_skips and search states; input catalog/query are unchanged. |
| ownership | Fixture borrowed. |
| failure | Mismatches fail through check. |
| cost | One full stateless calibration and per-request fault sweep. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp) |

## B0057

[Lines 395–412](../../../../../tests/unit/planner_search_exception_test.cpp#L395); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void disconnected_components_sweep(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault-sweep disconnected components with a nullary occurrence. |
| inputs / outputs | Takes fixture by reference; returns after sweep. |
| invariants | Clean v2 result has height 2, component_splits&gt;0 and a nullary native witness node; A04/P02 checks also run. |
| ownership | Fixture borrowed. |
| failure | Any assertion/sweep failure propagates. |
| cost | Full calibration and fault positions from measured new calls. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_proofs.md § Independent tree verification (P02)](../../../../planner_proofs.md) |

## B0059

[Lines 414–431](../../../../../tests/unit/planner_search_exception_test.cpp#L414); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void certificate_replay_sweep(const Fixture& fixture,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault-sweep independent replay of a caller-supplied height certificate. |
| inputs / outputs | Takes fixture/proof by reference and label; returns after stateless replay sweep. |
| invariants | Successful CertificateReport valid and not resource-limited; every retry checks catalog, query and proof unchanged. |
| ownership | Inputs borrowed. |
| failure | Bad allocation may escape invoke and is caught in generic sweep; malformed report fails. |
| cost | Calibrates and repeats one full certificate replay for every observed direct new fault position. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md § Authority and policies](../../../../planner_continuations.md) |

## B0061

[Lines 433–454](../../../../../tests/unit/planner_search_exception_test.cpp#L433); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void zero_limits_never_publish_partial_proofs(const Fixture& fixture,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that zero work, zero time, and zero recursion ceilings return no partial oracle/replay authority. |
| inputs / outputs | Takes fixture/proof by reference; returns after six constrained calls. |
| invariants | Each minimum_tree result must be resource_limit with empty proof fields; each verifier report must be resource-limited and invalid; caller inputs stay equal. |
| ownership | Inputs borrowed; result/report values local. |
| failure | Unexpected proof publication or input change throws runtime_error. |
| cost | Three pairs of stateless API calls; time zero is a deterministic limit, not a timing measurement. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md) |

## B0063

[Lines 456–459](../../../../../tests/unit/planner_search_exception_test.cpp#L456); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture residual_seven() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the seven-occurrence residual fixture used to separate producer and replay budgets. |
| inputs / outputs | Takes no arguments; returns Fixture. |
| invariants | Scopes/head are fixed to indices 0..6; query is finite int64 metadata only. |
| ownership | Returned fixture owns Catalog/Query. |
| failure | Construction allocation failures propagate. |
| cost | Builds seven table/atom definitions. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |

## B0065

[Lines 461–523](../../../../../tests/unit/planner_search_exception_test.cpp#L461); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void certificate_replay_resource_limit_is_distinct() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Force strict ExactSearch to finish production but stop at zero replay work, then raise the replay ceiling and resume. |
| inputs / outputs | Takes no arguments; creates fixture, limits and owner; returns after authority assertions. |
| invariants | Uses producer work/time unbounded and replay work 0; bounded loops request quantum 4096 and have a five-million iteration guard; requires total_work after producer completion and before replay attempt, no authority, then same owner accepts replay limit 10,000,000 and completes height 3. |
| ownership | Owner retains copied fixture input; fixture remains local; optimum is a copied typed handle. |
| failure | Unexpected stop/failed result, missed budget phase or missing final optimum throws. |
| cost | May issue up to five million advance calls per phase; this is an iteration ceiling, not CPU-time bound. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md) |

## B0067

[Lines 525–553](../../../../../tests/unit/planner_search_exception_test.cpp#L525); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_result_and_report_cleanup_is_allocation_free(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move and reset completed OracleResult and CertificateReport values under fail-after zero. |
| inputs / outputs | Takes fixture by reference; returns after cleanup assertion. |
| invariants | Creates clean stateless result and independently valid report before arming; checks direct replacement counter remains zero across moves/resets. |
| ownership | Fixture borrowed; optionals locally own moved result/report. |
| failure | Any replacement-new request fails the assertion; no all-allocator guarantee. |
| cost | Moves/resets four optionals under one fault scope; deallocation cost is not bounded. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp) |

## B0069

[Lines 555–599](../../../../../tests/unit/planner_search_exception_test.cpp#L555); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run stateless search/replay, strict resource stop and typed-cleanup scenarios. |
| inputs / outputs | No arguments; constructs exact fixtures/certificates and calls scenario helpers. |
| invariants | Nested, connected duplicate-scope and disconnected fixtures have distinct expected proof properties; v1 baseline portion is conditional on CROWN_PLANNER_TESTING. |
| ownership | Fixture and proof values remain local. |
| failure | Any scenario failure propagates to main. |
| cost | Finite fixtures; fault-sweep size follows measured replacement calls. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md § Authority and policies](../../../../planner_continuations.md) |

## B0070

[Lines 600–601](../../../../../tests/unit/planner_search_exception_test.cpp#L600); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L600-L601:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in planner_search_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0071

[Lines 602–611](../../../../../tests/unit/planner_search_exception_test.cpp#L602); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the stateless exception scenarios as executable entry point. |
| inputs / outputs | Takes process argc/argv implicitly; returns 0 after run or 1 on std::exception. |
| invariants | Catches standard exceptions and prints diagnostic; no assertion that this executable was run is made here. |
| ownership | No owner escapes run scope. |
| failure | Exception is rendered to stderr and return code 1. |
| cost | Calls run once. |
| Design | [tests/unit/planner_search_exception_test.cpp](../../../../../tests/unit/planner_search_exception_test.cpp) |
