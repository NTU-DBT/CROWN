# `tests/unit/residual_test.cpp` — block usage map

[Source](../../../../../tests/unit/residual_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `fa4d63a1457f1aa8ccdc019d003b74ff13fb63f7ec07bb20d264b02abc1e46e9`. 1088 lines partitioned into 83 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–26](../../../../../tests/unit/residual_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 27–29](../../../../../tests/unit/residual_test.cpp#L27) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 30–30](../../../../../tests/unit/residual_test.cpp#L30) | Explanatory comments or spacing. |  |
| [B0004 · 31–31](../../../../../tests/unit/residual_test.cpp#L31) | Type/record definition: struct VariableRef |  · [reviewed contract](#b0004) |
| [B0005 · 32–32](../../../../../tests/unit/residual_test.cpp#L32) | Type/record definition: struct Ignored |  · [reviewed contract](#b0005) |
| [B0006 · 33–34](../../../../../tests/unit/residual_test.cpp#L33) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 35–35](../../../../../tests/unit/residual_test.cpp#L35) | Type/record definition: struct Fixture |  · [reviewed contract](#b0007) |
| [B0008 · 36–36](../../../../../tests/unit/residual_test.cpp#L36) | Explanatory comments or spacing. |  |
| [B0009 · 37–37](../../../../../tests/unit/residual_test.cpp#L37) | Callable definition: Slot v(std::size_t value) | calls ; returns VariableRef{value} · [reviewed contract](#b0009) |
| [B0010 · 38–38](../../../../../tests/unit/residual_test.cpp#L38) | Callable definition: Slot c(std::int64_t value) | calls ; returns value · [reviewed contract](#b0010) |
| [B0011 · 39–39](../../../../../tests/unit/residual_test.cpp#L39) | Callable definition: Slot ignored() | calls ; returns Ignored{} · [reviewed contract](#b0011) |
| [B0012 · 40–40](../../../../../tests/unit/residual_test.cpp#L40) | Explanatory comments or spacing. |  |
| [B0013 · 41–104](../../../../../tests/unit/residual_test.cpp#L41) | Callable definition: Fixture fixture_for(const std::vector&lt;Occurrence&gt;& occurrences, const std::vector&lt;std::size_t&gt;& head, std::vector&lt;std::size_t&gt; ta… | calls empty, resize, size, check; guard check(table_groups.size() == occurrences.size(), "test fixture table-group count differs from atom …; returns fixture; growth emplace, emplace_back, insert, push_back, reserve, resize; 10 loop sites · [reviewed contract](#b0013) |
| [B0014 · 105–105](../../../../../tests/unit/residual_test.cpp#L105) | Explanatory comments or spacing. |  |
| [B0015 · 106–118](../../../../../tests/unit/residual_test.cpp#L106) | Callable definition: Fixture scoped_fixture(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& scopes, const std::vector&lt;std::size_t&gt;& head, bool contradict… | calls reserve, size, push_back, v; returns fixture_for(occurrences, head, {}, contradiction); growth push_back, reserve; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 119–119](../../../../../tests/unit/residual_test.cpp#L119) | Explanatory comments or spacing. |  |
| [B0017 · 120–123](../../../../../tests/unit/residual_test.cpp#L120) | Callable definition: std::vector&lt;std::vector&lt;std::size_t&gt;&gt; seven_scopes() | calls ; returns {{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5}, {5}, {0, 6}}; source comment (unverified): // Q(x,y,w): R(x,y,z,r), S(x,y,z,s), L(r), V(s), T(y,b), B(b), E(x,w). · [reviewed contract](#b0017) |
| [B0018 · 124–124](../../../../../tests/unit/residual_test.cpp#L124) | Explanatory comments or spacing. |  |
| [B0019 · 125–129](../../../../../tests/unit/residual_test.cpp#L125) | Callable definition: std::vector&lt;std::vector&lt;std::size_t&gt;&gt; nine_scopes() | calls ; returns {{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5, 6},; source comment (unverified): // The nine-atom analytical variant adds U(y,a,c) and C(c). · [reviewed contract](#b0019) |
| [B0020 · 130–130](../../../../../tests/unit/residual_test.cpp#L130) | Explanatory comments or spacing. |  |
| [B0021 · 131–145](../../../../../tests/unit/residual_test.cpp#L131) | Callable definition: bool same_term(const Term& left, const Term& right) | calls index; returns false; *variable == std::get&lt;VariableId&gt;(right) · [reviewed contract](#b0021) |
| [B0022 · 146–146](../../../../../tests/unit/residual_test.cpp#L146) | Explanatory comments or spacing. |  |
| [B0023 · 147–163](../../../../../tests/unit/residual_test.cpp#L147) | Callable definition: bool same_query(const Query& left, const Query& right) | calls size, same_term; returns false; false; 4 loop sites · [reviewed contract](#b0023) |
| [B0024 · 164–164](../../../../../tests/unit/residual_test.cpp#L164) | Explanatory comments or spacing. |  |
| [B0025 · 165–178](../../../../../tests/unit/residual_test.cpp#L165) | Callable definition: bool same_catalog_boundary(const Catalog& left, const Catalog& right) | calls size; returns false; false; 2 loop sites · [reviewed contract](#b0025) |
| [B0026 · 179–179](../../../../../tests/unit/residual_test.cpp#L179) | Explanatory comments or spacing. |  |
| [B0027 · 180–187](../../../../../tests/unit/residual_test.cpp#L180) | Callable definition: bool same_anchors(const std::vector&lt;planner::EarAnchor&gt;& left, const std::vector&lt;planner::EarAnchor&gt;& right) | calls size; returns false; false; 1 loop sites · [reviewed contract](#b0027) |
| [B0028 · 188–188](../../../../../tests/unit/residual_test.cpp#L188) | Explanatory comments or spacing. |  |
| [B0029 · 189–196](../../../../../tests/unit/residual_test.cpp#L189) | Callable definition: bool same_deletions(const std::vector&lt;planner::EarDeletion&gt;& left, const std::vector&lt;planner::EarDeletion&gt;& right) | calls size; returns false; false; 1 loop sites · [reviewed contract](#b0029) |
| [B0030 · 197–197](../../../../../tests/unit/residual_test.cpp#L197) | Explanatory comments or spacing. |  |
| [B0031 · 198–230](../../../../../tests/unit/residual_test.cpp#L198) | Callable definition: void require_same_trace(const planner::ResidualTraceRecord& actual, const planner::ResidualTraceRecord& expected, const std::stri… | calls check, size, same_anchors, same_deletions; guard check(actual.version == expected.version, context + ": trace version differs from the literal repla…; 2 loop sites · [reviewed contract](#b0031) |
| [B0032 · 231–231](../../../../../tests/unit/residual_test.cpp#L231) | Explanatory comments or spacing. |  |
| [B0033 · 232–239](../../../../../tests/unit/residual_test.cpp#L232) | Callable definition: bool same_statistics(const planner::ResidualStatistics& a, const planner::ResidualStatistics& b) | calls ; returns a.hierarchy_tests == b.hierarchy_tests && a.rounds == b.rounds && · [reviewed contract](#b0033) |
| [B0034 · 240–240](../../../../../tests/unit/residual_test.cpp#L240) | Explanatory comments or spacing. |  |
| [B0035 · 241–248](../../../../../tests/unit/residual_test.cpp#L241) | Callable definition: bool same_search_statistics(const planner::SearchStatistics& a, const planner::SearchStatistics& b) | calls ; returns a.work == b.work && a.states == b.states && a.partitions == b.partitions && · [reviewed contract](#b0035) |
| [B0036 · 249–249](../../../../../tests/unit/residual_test.cpp#L249) | Explanatory comments or spacing. |  |
| [B0037 · 250–255](../../../../../tests/unit/residual_test.cpp#L250) | Callable definition: bool same_search_progress(const planner::SearchProgress& a, const planner::SearchProgress& b) | calls same_search_statistics; returns a.phase == b.phase && a.last_stop == b.last_stop && a.result == b.result && · [reviewed contract](#b0037) |
| [B0038 · 256–256](../../../../../tests/unit/residual_test.cpp#L256) | Explanatory comments or spacing. |  |
| [B0039 · 257–264](../../../../../tests/unit/residual_test.cpp#L257) | Callable definition: bool same_progress(const planner::ResidualProgress& a, const planner::ResidualProgress& b) | calls same_statistics, same_search_progress; returns a.phase == b.phase && a.result == b.result && a.proof_status == b.proof_status && · [reviewed contract](#b0039) |
| [B0040 · 265–265](../../../../../tests/unit/residual_test.cpp#L265) | Explanatory comments or spacing. |  |
| [B0041 · 266–291](../../../../../tests/unit/residual_test.cpp#L266) | Callable definition: void check_monotone(const planner::ResidualProgress& before, const planner::ResidualProgress& after, const std::string& context) | calls check; guard check(after.work.attempted &gt;= before.work.attempted && · [reviewed contract](#b0041) |
| [B0042 · 292–292](../../../../../tests/unit/residual_test.cpp#L292) | Explanatory comments or spacing. |  |
| [B0043 · 293–293](../../../../../tests/unit/residual_test.cpp#L293) | Type/record definition: enum class Slicing |  · [reviewed contract](#b0043) |
| [B0044 · 294–294](../../../../../tests/unit/residual_test.cpp#L294) | Explanatory comments or spacing. |  |
| [B0045 · 295–306](../../../../../tests/unit/residual_test.cpp#L295) | Callable definition: planner::ResidualOptions options_for(planner::ResidualMode mode = planner::ResidualMode::candidates_with_exact_repair) | calls ; returns options · [reviewed contract](#b0045) |
| [B0046 · 307–307](../../../../../tests/unit/residual_test.cpp#L307) | Explanatory comments or spacing. |  |
| [B0047 · 308–313](../../../../../tests/unit/residual_test.cpp#L308) | Callable definition: planner::WorkQuantum quantum_for(Slicing slicing, std::size_t step) | calls size; returns {1, {}}; {grants\[step % grants.size()\], {}} · [reviewed contract](#b0047) |
| [B0048 · 314–314](../../../../../tests/unit/residual_test.cpp#L314) | Explanatory comments or spacing. |  |
| [B0049 · 315–325](../../../../../tests/unit/residual_test.cpp#L315) | Type/record definition: struct CompletedRun |  · [reviewed contract](#b0049) |
| [B0050 · 326–329](../../../../../tests/unit/residual_test.cpp#L326) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0050) |
| [B0051 · 330–379](../../../../../tests/unit/residual_test.cpp#L330) | Callable definition: CompletedRun run_to_completion(const Fixture& fixture, planner::ResidualMode mode, Slicing slicing, planner::ResidualOptions opti… | calls options_for, planner::ResidualSearch::create, progress, advance; guard check(!owner.exact_original() && !owner.infeasibility(),; returns result; growth insert; 1 loop sites · [reviewed contract](#b0051) |
| [B0052 · 380–380](../../../../../tests/unit/residual_test.cpp#L380) | Explanatory comments or spacing. |  |
| [B0053 · 381–391](../../../../../tests/unit/residual_test.cpp#L381) | Callable definition: planner::ResidualTrace trace_only(const Fixture& fixture) | calls planner::ResidualSearch::create, options_for, advance, check; guard check(advanced.progress.result != planner::ResidualResult::failed,; returns *trace; 1 loop sites · [reviewed contract](#b0053) |
| [B0054 · 392–392](../../../../../tests/unit/residual_test.cpp#L392) | Explanatory comments or spacing. |  |
| [B0055 · 393–407](../../../../../tests/unit/residual_test.cpp#L393) | Callable definition: void audit_trace(const Fixture& fixture, const std::string& context) | calls trace_only, check, valid, reference::frozen_residual_trace; guard check(trace.valid(), context + ": published trace handle is invalid"); · [reviewed contract](#b0055) |
| [B0056 · 408–408](../../../../../tests/unit/residual_test.cpp#L408) | Explanatory comments or spacing. |  |
| [B0057 · 409–423](../../../../../tests/unit/residual_test.cpp#L409) | Callable definition: void audit_trace_handle(const Fixture& fixture, const planner::ResidualTrace& trace, const std::string& context) | calls check, valid, reference::frozen_residual_trace, require_same_trace; guard check(trace.valid(), context + ": published trace handle is invalid"); · [reviewed contract](#b0057) |
| [B0058 · 424–424](../../../../../tests/unit/residual_test.cpp#L424) | Explanatory comments or spacing. |  |
| [B0059 · 425–444](../../../../../tests/unit/residual_test.cpp#L425) | Callable definition: void check_valid_candidate(const Fixture& fixture, const planner::ResidualCandidate& candidate, const std::string& context) | calls check, valid, same_query, query; guard check(candidate.valid(), context + ": invalid candidate handle");; growth push_back; 2 loop sites · [reviewed contract](#b0059) |
| [B0060 · 445–445](../../../../../tests/unit/residual_test.cpp#L445) | Explanatory comments or spacing. |  |
| [B0061 · 446–526](../../../../../tests/unit/residual_test.cpp#L446) | Callable definition: void small_p03_and_trace_family() | calls scopes, push_back, scoped_fixture, run_to_completion; guard check(candidate_run.trace && candidate_run.progress.trace_verified,; growth push_back; 6 loop sites · [reviewed contract](#b0061) |
| [B0062 · 527–527](../../../../../tests/unit/residual_test.cpp#L527) | Explanatory comments or spacing. |  |
| [B0063 · 528–589](../../../../../tests/unit/residual_test.cpp#L528) | Callable definition: void named_semantic_cases() | calls audit_trace, scoped_fixture, fixture_for, v; guard check(same_query(terms_trace.query(), terms.query), "typed-term fixture lost its original query bin…; returns ear.occurrence == 1; ear.occurrence == 1; growth push_back; 2 loop sites; source comment (unverified): // Removing C and A changes U so E becomes an ear only in the next frozen · [reviewed contract](#b0063) |
| [B0064 · 590–590](../../../../../tests/unit/residual_test.cpp#L590) | Explanatory comments or spacing. |  |
| [B0065 · 591–646](../../../../../tests/unit/residual_test.cpp#L591) | Callable definition: void verify_counterexamples_and_authority() | calls scoped_fixture, seven_scopes, nine_scopes, run_to_completion; guard check(final_progress.result == planner::ResidualResult::verified_optimum &&; 1 loop sites · [reviewed contract](#b0065) |
| [B0066 · 647–647](../../../../../tests/unit/residual_test.cpp#L647) | Explanatory comments or spacing. |  |
| [B0067 · 648–651](../../../../../tests/unit/residual_test.cpp#L648) | Callable definition: Fixture wrong_anchor_fixture() | calls scoped_fixture; returns scoped_fixture({{0, 1}, {0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4}, {0, 5}}, {0, 5}); source comment (unverified): // R(x,a), A(x,a,b), B(x,b,c), C(x,c,d), U(x,d), E(x,w); head {x,w}. · [reviewed contract](#b0067) |
| [B0068 · 652–652](../../../../../tests/unit/residual_test.cpp#L652) | Explanatory comments or spacing. |  |
| [B0069 · 653–656](../../../../../tests/unit/residual_test.cpp#L653) | Callable definition: Fixture generalized_augmentation_fixture() | calls scoped_fixture; returns scoped_fixture({{0, 1, 2}, {0, 1, 3}, {2}, {3}, {0, 4}}, {0, 4}); source comment (unverified): // P(a,z,x), R(a,z,y), L(x), U(y), S(a,c); head {a,c}. · [reviewed contract](#b0069) |
| [B0070 · 657–657](../../../../../tests/unit/residual_test.cpp#L657) | Explanatory comments or spacing. |  |
| [B0071 · 658–743](../../../../../tests/unit/residual_test.cpp#L658) | Callable definition: void candidate_reconstruction_and_ownership() | calls generalized_augmentation_fixture, run_to_completion, options_for, check; guard check(candidate_run.progress.result == planner::ResidualResult::checked_candidate &&; 2 loop sites · [reviewed contract](#b0071) |
| [B0072 · 744–744](../../../../../tests/unit/residual_test.cpp#L744) | Explanatory comments or spacing. |  |
| [B0073 · 745–815](../../../../../tests/unit/residual_test.cpp#L745) | Callable definition: void residual_ceiling_extensions_resume() | calls generalized_augmentation_fixture, run_to_completion, options_for, check; guard check(baseline.candidate && baseline.trace, "resource-resume baseline lacks a candidate or trace");; 2 loop sites · [reviewed contract](#b0073) |
| [B0074 · 816–816](../../../../../tests/unit/residual_test.cpp#L816) | Explanatory comments or spacing. |  |
| [B0075 · 817–933](../../../../../tests/unit/residual_test.cpp#L817) | Callable definition: void slicing_zero_quantum_and_limit_resume() | calls generalized_augmentation_fixture, run_to_completion, options_for, check; guard check(unsliced.candidate && unit.candidate && varied.candidate,; growth insert; 3 loop sites; source comment (unverified): // A shared zero replay grant would stop the induced seed first. Calibrate · [reviewed contract](#b0075) |
| [B0076 · 934–934](../../../../../tests/unit/residual_test.cpp#L934) | Explanatory comments or spacing. |  |
| [B0077 · 935–937](../../../../../tests/unit/residual_test.cpp#L935) | Callable definition: planner::ResidualTraceRecord get_good_mutation_target(const Fixture& fixture) | calls trace_only, record; returns trace_only(fixture).record() · [reviewed contract](#b0077) |
| [B0078 · 938–938](../../../../../tests/unit/residual_test.cpp#L938) | Explanatory comments or spacing. |  |
| [B0079 · 939–1030](../../../../../tests/unit/residual_test.cpp#L939) | Callable definition: void rejected_mutations() | calls scoped_fixture, seven_scopes, get_good_mutation_target, planner::verify_residual_trace; guard check(!report.valid && !report.resource_limit && report.rule != planner::ResidualTraceRule::none,; growth push_back; 1 loop sites · [reviewed contract](#b0079) |
| [B0080 · 1031–1031](../../../../../tests/unit/residual_test.cpp#L1031) | Explanatory comments or spacing. |  |
| [B0081 · 1032–1069](../../../../../tests/unit/residual_test.cpp#L1032) | Callable definition: void exact_inner_reason_and_fallback_handle() | calls scoped_fixture, options_for, planner::ResidualSearch::create, advance; guard check(advanced.stopped_for == planner::ResidualStopReason::exact_limit &&; 2 loop sites · [reviewed contract](#b0081) |
| [B0082 · 1070–1072](../../../../../tests/unit/residual_test.cpp#L1070) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0082) |
| [B0083 · 1073–1088](../../../../../tests/unit/residual_test.cpp#L1073) | Callable definition: int main() | calls small_p03_and_trace_family, named_semantic_cases, verify_counterexamples_and_authority, candidate_reconstruction_and_ownership; returns 1 · [reviewed contract](#b0083) |

## B0001

[Lines 1–26](../../../../../tests/unit/residual_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L26:sha256:c12c8ff136592ae59fa2970239a0e9e3c17a4773a0f542d3ea79811920a58db9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare residual_test.cpp: include "crown/planner/residual.hpp", "crown/planner/verify.hpp", "residual_oracle.hpp", "tree_oracle.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;chrono&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;map&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;tuple&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;variant&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 27–29](../../../../../tests/unit/residual_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a test assertion with a diagnostic string. |
| inputs / outputs | Inputs and return are those in \`void check(bool condition, const std::string& message)\`; body-specific behavior: Fail a test assertion with a diagnostic string. |
| invariants | check throws std::runtime_error on false; it is a test oracle. |
| ownership | Inputs are borrowed or values for the call as declared; the helper retains no result after return, except explicitly mutated output-reference arguments. |
| failure | False predicate throws std::runtime_error with the supplied message. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0004

[Lines 31–31](../../../../../tests/unit/residual_test.cpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct VariableRef { std::size_t value; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe a named variable reference in one synthetic occurrence. |
| inputs / outputs | Inputs and return are those in \`struct VariableRef\`; body-specific behavior: Describe a named variable reference in one synthetic occurrence. |
| invariants | VariableRef stores one synthetic variable name/index used as an alternative in the Slot variant; it is fixture notation, not a planner VariableId. |
| ownership | Owns only the variable index scalar. |
| failure | Plain test data declaration; no custom error handling. |
| cost | Plain fixture data; no runtime work. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0005

[Lines 32–32](../../../../../tests/unit/residual_test.cpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Ignored {};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe an ignored source column distinct from a variable or constant. |
| inputs / outputs | Inputs and return are those in \`struct Ignored\`; body-specific behavior: Describe an ignored source column distinct from a variable or constant. |
| invariants | Ignored positions remain present in source arity but do not bind a query variable. |
| ownership | No external object is owned. |
| failure | Plain test data declaration; no custom error handling. |
| cost | Plain fixture data; no runtime work. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0006

[Lines 33–34](../../../../../tests/unit/residual_test.cpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L34:sha256:5ad3ff97491aad0965a38cddb8fd6c5b7d5caf1b7ed9aa719d12588b075a2ec9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare residual_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 35–35](../../../../../tests/unit/residual_test.cpp#L35); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture { Catalog catalog; Query query; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one generated Catalog and Query fixture. |
| inputs / outputs | Inputs and return are those in \`struct Fixture\`; body-specific behavior: Own one generated Catalog and Query fixture. |
| invariants | Fixture owns values; this declaration performs no validation or planner call. |
| ownership | Owns Catalog and Query fixture values. |
| failure | Plain test data declaration; no custom error handling. |
| cost | Plain fixture data; no runtime work. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0009

[Lines 37–37](../../../../../tests/unit/residual_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Slot v(std::size_t value) { return VariableRef{value}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a variable Slot. |
| inputs / outputs | Inputs and return are those in \`Slot v(std::size_t value)\`; body-specific behavior: Construct a variable Slot. |
| invariants | Value is carried by value and assigned the variable alternative. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0010

[Lines 38–38](../../../../../tests/unit/residual_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Slot c(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an int64 constant Slot. |
| inputs / outputs | Inputs and return are those in \`Slot c(std::int64_t value)\`; body-specific behavior: Construct an int64 constant Slot. |
| invariants | Constant uses int64 scalar type in generated catalog/query. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0011

[Lines 39–39](../../../../../tests/unit/residual_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Slot ignored() { return Ignored{}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the ignored-column Slot. |
| inputs / outputs | Inputs and return are those in \`Slot ignored()\`; body-specific behavior: Construct the ignored-column Slot. |
| invariants | IgnoredColumn is not the same as a constant or variable. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0013

[Lines 41–104](../../../../../tests/unit/residual_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture fixture_for(const std::vector<Occurrence>& occurrences,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build query/catalog metadata from occurrence slots, ordered head, optional table sharing and contradiction flag. |
| inputs / outputs | Inputs and return are those in \`Fixture fixture_for(const std::vector&lt;Occurrence&gt;& occurrences, const std::vector&lt;std::size_t&gt;& head, std::vector&lt;std::size_t&gt; table_groups = {}, bool contradiction = false)\`; body-specific behavior: Build query/catalog metadata from occurrence slots, ordered head, optional table sharing and contradiction flag. |
| invariants | Repeated logical table groups share table IDs while occurrences remain distinct; output aliases follow head order. |
| ownership | Inputs are borrowed; returned Fixture owns all generated table/query vectors and values. |
| failure | Mismatched group count or variable lookup fails through check/map::at; container allocation can throw. |
| cost | Builds a finite variable/occurrence/table fixture; table and occurrence vectors scale with this supplied test input. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0015

[Lines 106–118](../../../../../tests/unit/residual_test.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture scoped_fixture(const std::vector<std::vector<std::size_t>>& scopes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert variable-only scopes and head into an owned Fixture. |
| inputs / outputs | Inputs and return are those in \`Fixture scoped_fixture(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& scopes, const std::vector&lt;std::size_t&gt;& head, bool contradiction = false)\`; body-specific behavior: Convert variable-only scopes and head into an owned Fixture. |
| invariants | Each listed scope is a distinct atom; the head is passed explicitly. |
| ownership | Scopes/head are borrowed; returned Fixture owns generated values. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Copies each scope into occurrence slots, then calls fixture_for; finite fixture construction. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0017

[Lines 120–123](../../../../../tests/unit/residual_test.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::vector<std::size_t>> seven_scopes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the seven-atom counterexample scopes used by the finite exactness fixture. |
| inputs / outputs | Inputs and return are those in \`std::vector&lt;std::vector&lt;std::size_t&gt;&gt; seven_scopes()\`; body-specific behavior: Return the seven-atom counterexample scopes used by the finite exactness fixture. |
| invariants | The seven-scope query has a known original-query minimum-three counterexample fixture, not a general theorem. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0019

[Lines 125–129](../../../../../tests/unit/residual_test.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::vector<std::size_t>> nine_scopes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the nine-atom analytical variant by adding two linked occurrences. |
| inputs / outputs | Inputs and return are those in \`std::vector&lt;std::vector&lt;std::size_t&gt;&gt; nine_scopes()\`; body-specific behavior: Return the nine-atom analytical variant by adding two linked occurrences. |
| invariants | The extra U/C chain only defines a finite analytical query instance. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0021

[Lines 131–145](../../../../../tests/unit/residual_test.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_term(const Term& left, const Term& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare Term variant and payload equality. |
| inputs / outputs | Inputs and return are those in \`bool same_term(const Term& left, const Term& right)\`; body-specific behavior: Compare Term variant and payload equality. |
| invariants | Variant index and corresponding scalar value both participate in equality. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares variant/value pairs. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0023

[Lines 147–163](../../../../../tests/unit/residual_test.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_query(const Query& left, const Query& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare complete query variables, occurrences, terms, ordered aliases and contradiction. |
| inputs / outputs | Inputs and return are those in \`bool same_query(const Query& left, const Query& right)\`; body-specific behavior: Compare complete query variables, occurrences, terms, ordered aliases and contradiction. |
| invariants | Equality covers listed query structure, not runtime results. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Scans variables, atoms, terms and ordered head. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0025

[Lines 165–178](../../../../../tests/unit/residual_test.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_catalog_boundary(const Catalog& left, const Catalog& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare catalog boundary fields relevant to generated table semantics. |
| inputs / outputs | Inputs and return are those in \`bool same_catalog_boundary(const Catalog& left, const Catalog& right)\`; body-specific behavior: Compare catalog boundary fields relevant to generated table semantics. |
| invariants | Catalog comparison is a fixture boundary check, not full arbitrary catalog identity. |
| ownership | Catalogs are borrowed; no data is retained. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Scans catalog tables/columns in the fixture boundary comparator. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0027

[Lines 180–187](../../../../../tests/unit/residual_test.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_anchors(const std::vector<planner::EarAnchor>& left,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare frozen reduction anchor records. |
| inputs / outputs | Inputs and return are those in \`bool same_anchors(const std::vector&lt;planner::EarAnchor&gt;& left, const std::vector&lt;planner::EarAnchor&gt;& right)\`; body-specific behavior: Compare frozen reduction anchor records. |
| invariants | Anchor vector order/value is compared as expected test data. |
| ownership | Anchor vectors are borrowed; no data is retained. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Scans anchor vectors. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0029

[Lines 189–196](../../../../../tests/unit/residual_test.cpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_deletions(const std::vector<planner::EarDeletion>& left,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare frozen reduction deletion records. |
| inputs / outputs | Inputs and return are those in \`bool same_deletions(const std::vector&lt;planner::EarDeletion&gt;& left, const std::vector&lt;planner::EarDeletion&gt;& right)\`; body-specific behavior: Compare frozen reduction deletion records. |
| invariants | Deletion vector order/value is compared as expected test data. |
| ownership | Deletion vectors are borrowed; no data is retained. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Scans deletion vectors. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0031

[Lines 198–230](../../../../../tests/unit/residual_test.cpp#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require_same_trace(const planner::ResidualTraceRecord& actual,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one actual trace record to equal the independently frozen expected record with context in diagnostics. |
| inputs / outputs | Inputs and return are those in \`void require_same_trace(const planner::ResidualTraceRecord& actual, const planner::ResidualTraceRecord& expected, const std::string& context)\`; body-specific behavior: Require one actual trace record to equal the independently frozen expected record with context in diagnostics. |
| invariants | Mismatch throws with record context; equality comes from frozen oracle fixture. |
| ownership | Inputs are borrowed or values for the call as declared; the helper retains no result after return, except explicitly mutated output-reference arguments. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Compares one finite record and nested scope vectors. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0033

[Lines 232–239](../../../../../tests/unit/residual_test.cpp#L232); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_statistics(const planner::ResidualStatistics& a, const planner::ResidualStatistics& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exposed residual statistics. |
| inputs / outputs | Inputs and return are those in \`bool same_statistics(const planner::ResidualStatistics& a, const planner::ResidualStatistics& b)\`; body-specific behavior: Compare exposed residual statistics. |
| invariants | Only exposed statistics are compared. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0035

[Lines 241–248](../../../../../tests/unit/residual_test.cpp#L241); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_search_statistics(const planner::SearchStatistics& a, const planner::SearchStatistics& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact-search statistics. |
| inputs / outputs | Inputs and return are those in \`bool same_search_statistics(const planner::SearchStatistics& a, const planner::SearchStatistics& b)\`; body-specific behavior: Compare exact-search statistics. |
| invariants | Only selected exact-search progress fields are compared. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0037

[Lines 250–255](../../../../../tests/unit/residual_test.cpp#L250); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_search_progress(const planner::SearchProgress& a, const planner::SearchProgress& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact-search progress fields used by slicing checks. |
| inputs / outputs | Inputs and return are those in \`bool same_search_progress(const planner::SearchProgress& a, const planner::SearchProgress& b)\`; body-specific behavior: Compare exact-search progress fields used by slicing checks. |
| invariants | Counts/scope and terminal fields are selected by body; no time limit proof. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0039

[Lines 257–264](../../../../../tests/unit/residual_test.cpp#L257); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_progress(const planner::ResidualProgress& a, const planner::ResidualProgress& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare residual owner progress fields. |
| inputs / outputs | Inputs and return are those in \`bool same_progress(const planner::ResidualProgress& a, const planner::ResidualProgress& b)\`; body-specific behavior: Compare residual owner progress fields. |
| invariants | Progress equality is fixture consistency, not a general state-machine proof. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0041

[Lines 266–291](../../../../../tests/unit/residual_test.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_monotone(const planner::ResidualProgress& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check selected public monotonic counters and phase transitions. |
| inputs / outputs | Inputs and return are those in \`void check_monotone(const planner::ResidualProgress& before, const planner::ResidualProgress& after, const std::string& context)\`; body-specific behavior: Check selected public monotonic counters and phase transitions. |
| invariants | Every covered counter is nondecreasing across the compared observations; no wall-clock bound. |
| ownership | Inputs are borrowed or values for the call as declared; the helper retains no result after return, except explicitly mutated output-reference arguments. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Scans selected counters and stage fields. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0043

[Lines 293–293](../../../../../tests/unit/residual_test.cpp#L293); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Slicing { unsliced, unit, varied };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name whole-trace versus stepwise fixture execution. |
| inputs / outputs | Inputs and return are those in \`enum class Slicing\`; body-specific behavior: Name whole-trace versus stepwise fixture execution. |
| invariants | Slicing mode only selects grant shape. |
| ownership | Plain local fixture value type; its declared value members own their containers/scalars and it retains no runtime borrow. |
| failure | Plain test data declaration; no custom error handling. |
| cost | Plain fixture data; no runtime work. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0045

[Lines 295–306](../../../../../tests/unit/residual_test.cpp#L295); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::ResidualOptions options_for(planner::ResidualMode mode = planner::ResidualMode::candidates_with_exact_repair) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build residual options with explicit mode and bounded defaults. |
| inputs / outputs | Inputs and return are those in \`planner::ResidualOptions options_for(planner::ResidualMode mode = planner::ResidualMode::candidates_with_exact_repair)\`; body-specific behavior: Build residual options with explicit mode and bounded defaults. |
| invariants | Candidate mode is not exact original-query authority by itself. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0047

[Lines 308–313](../../../../../tests/unit/residual_test.cpp#L308); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::WorkQuantum quantum_for(Slicing slicing, std::size_t step) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose bounded work quanta for whole, small, or alternating slicing. |
| inputs / outputs | Inputs and return are those in \`planner::WorkQuantum quantum_for(Slicing slicing, std::size_t step)\`; body-specific behavior: Choose bounded work quanta for whole, small, or alternating slicing. |
| invariants | Step parameter produces explicit small/alternating grants; grant count is not CPU time. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0049

[Lines 315–325](../../../../../tests/unit/residual_test.cpp#L315); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CompletedRun {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold final trace/candidate/proof and public progress for one completed run. |
| inputs / outputs | Inputs and return are those in \`struct CompletedRun\`; body-specific behavior: Hold final trace/candidate/proof and public progress for one completed run. |
| invariants | CompletedRun owns immutable returned values/handles and progress snapshot. |
| ownership | Owns copied returned trace/candidate optionals and a progress snapshot. |
| failure | Plain test data declaration; no custom error handling. |
| cost | Plain fixture data; no runtime work. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0050

[Lines 326–329](../../../../../tests/unit/residual_test.cpp#L326); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L326-L329:sha256:c3f919103cfe8352a82604f1b5eef0f5d2e333d184d33145f8c262d53b0a6aa4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare residual_test.cpp: declare helper function signatures without invoking them. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. Function prototypes declare the shown reference/helper API; invocation and any default-argument evaluation occur at the caller. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |

## B0051

[Lines 330–379](../../../../../tests/unit/residual_test.cpp#L330); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompletedRun run_to_completion(const Fixture& fixture, planner::ResidualMode mode, Slicing slicing,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one owner by selected work slices to a terminal state and return its handles. |
| inputs / outputs | Inputs and return are those in \`CompletedRun run_to_completion(const Fixture& fixture, planner::ResidualMode mode, Slicing slicing, planner::ResidualOptions options = {})\`; body-specific behavior: Advance one owner by selected work slices to a terminal state and return its handles. |
| invariants | Loop termination is checked against public step statuses and configured finite ceiling. |
| ownership | Fixture is borrowed; ResidualSearch owner is local, and returned trace/candidate/proof values own their public data. |
| failure | Planner statuses are asserted to reach completion; planner errors or fixture mismatch propagate as test failure. |
| cost | Runs finite planner advances according to chosen slicing; not a wall-clock guarantee. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0053

[Lines 381–391](../../../../../tests/unit/residual_test.cpp#L381); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::ResidualTrace trace_only(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain only a trace through the public trace verification path. |
| inputs / outputs | Inputs and return are those in \`planner::ResidualTrace trace_only(const Fixture& fixture)\`; body-specific behavior: Obtain only a trace through the public trace verification path. |
| invariants | Trace-only creation returns a frozen trace consistent with its input fixture; it does not establish exact original-query height. |
| ownership | Fixture is borrowed; returned trace value owns its immutable record. |
| failure | Trace creation or verification failures propagate; a valid trace alone is not an optimum claim. |
| cost | Constructs/validates a finite trace. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0055

[Lines 393–407](../../../../../tests/unit/residual_test.cpp#L393); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void audit_trace(const Fixture& fixture, const std::string& context) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check generated trace against the independent frozen-round oracle. |
| inputs / outputs | Inputs and return are those in \`void audit_trace(const Fixture& fixture, const std::string& context)\`; body-specific behavior: Check generated trace against the independent frozen-round oracle. |
| invariants | Trace certificate demonstrates trace consistency only. |
| ownership | Fixture is borrowed; verifier result is local. |
| failure | Mismatch throws through check; verifier/resource errors are checked explicitly. |
| cost | Replays one finite trace via independent verifier. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0057

[Lines 409–423](../../../../../tests/unit/residual_test.cpp#L409); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void audit_trace_handle(const Fixture& fixture, const planner::ResidualTrace& trace,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a retained trace handle against the independent trace oracle. |
| inputs / outputs | Inputs and return are those in \`void audit_trace_handle(const Fixture& fixture, const planner::ResidualTrace& trace, const std::string& context)\`; body-specific behavior: Check a retained trace handle against the independent trace oracle. |
| invariants | Handle survives independently of the local verifier owner; it does not include mutable worker state. |
| ownership | Fixture and trace are borrowed; verifier result is local. |
| failure | Mismatch throws through check; verifier/resource errors are checked explicitly. |
| cost | Replays a retained trace via independent verifier. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0059

[Lines 425–444](../../../../../tests/unit/residual_test.cpp#L425); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_valid_candidate(const Fixture& fixture, const planner::ResidualCandidate& candidate,
                           const std::string& context) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate one candidate against original fixture query semantics and independent exact/reference authority. |
| inputs / outputs | Inputs and return are those in \`void check_valid_candidate(const Fixture& fixture, const planner::ResidualCandidate& candidate, const std::string& context)\`; body-specific behavior: Validate one candidate against original fixture query semantics and independent exact/reference authority. |
| invariants | Candidate correctness is checked through original query/evaluator and exact verifier, not inferred from residual minimum. |
| ownership | Fixture/candidate are borrowed during validation; no reference is stored. |
| failure | Invalid candidate report fails through check; does not claim to enumerate every invalid candidate. |
| cost | Runs candidate validation and exact reference checks on this fixture. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0061

[Lines 446–526](../../../../../tests/unit/residual_test.cpp#L446); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void small_p03_and_trace_family() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare 225 small 3-atom cases against frozen trace and finite P03/P06 oracles. |
| inputs / outputs | Inputs and return are those in \`void small_p03_and_trace_family()\`; body-specific behavior: Compare 225 small 3-atom cases against frozen trace and finite P03/P06 oracles. |
| invariants | 225 finite generated scope/head cases; P03 oracle range and P06 search are restricted to those small fixtures. |
| ownership | All generated fixtures, planners, handles and oracle values are local; frozen trace and P03/P06 oracle code is independent test support. |
| failure | Any independent trace/P03/P06 disagreement throws; P03/P06 finite-domain limits are those implemented by the oracle. |
| cost | 225 finite generated cases across fixture choices; no broad benchmark or universal complexity conclusion. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0063

[Lines 528–589](../../../../../tests/unit/residual_test.cpp#L528); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void named_semantic_cases() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise named edge cases: nullary, disconnected, repeated scopes/head, constants, ignored columns, contradictions and delayed/stalled reduction. |
| inputs / outputs | Inputs and return are those in \`void named_semantic_cases()\`; body-specific behavior: Exercise named edge cases: nullary, disconnected, repeated scopes/head, constants, ignored columns, contradictions and delayed/stalled reduction. |
| invariants | Named cases are finite semantic edge fixtures, including one 70-variable/occurrence case; no universal scaling guarantee. |
| ownership | Each fixture/search/result is local; returned handles stay within the test call. |
| failure | Named semantic mismatch throws; planner/resource errors propagate. |
| cost | Finite list of named cases, including one 70-variable/occurrence input; no asymptotic guarantee. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0065

[Lines 591–646](../../../../../tests/unit/residual_test.cpp#L591); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify_counterexamples_and_authority() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check seven/nine-atom counterexamples where one frozen reduction round is insufficient and exact original search remains authority. |
| inputs / outputs | Inputs and return are those in \`void verify_counterexamples_and_authority()\`; body-specific behavior: Check seven/nine-atom counterexamples where one frozen reduction round is insufficient and exact original search remains authority. |
| invariants | Exact original search establishes the checked original fixture result; frozen one-round output alone is insufficient. |
| ownership | Fixtures and public handles are local; exact search is a retained local owner. |
| failure | Exact original-search mismatch or false authority fails; frozen-round trace is not treated as exact proof. |
| cost | Runs the seven/nine-atom finite exact counterexamples; exact search may explore its configured bounded state space. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0067

[Lines 648–651](../../../../../tests/unit/residual_test.cpp#L648); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture wrong_anchor_fixture() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a fixture with a deliberately wrong anchor. |
| inputs / outputs | Inputs and return are those in \`Fixture wrong_anchor_fixture()\`; body-specific behavior: Build a fixture with a deliberately wrong anchor. |
| invariants | Purpose is to reject wrong candidate reconstruction evidence, not to compare random arbitrary anchors. |
| ownership | Returns a fully owning fixture value. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0069

[Lines 653–656](../../../../../tests/unit/residual_test.cpp#L653); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture generalized_augmentation_fixture() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the generalized augmentation counterexample fixture. |
| inputs / outputs | Inputs and return are those in \`Fixture generalized_augmentation_fixture()\`; body-specific behavior: Build the generalized augmentation counterexample fixture. |
| invariants | Purpose is to exercise generalized-root augmentation through the concrete nine-atom shape. |
| ownership | Returns a fully owning fixture value. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0071

[Lines 658–743](../../../../../tests/unit/residual_test.cpp#L658); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void candidate_reconstruction_and_ownership() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check candidate construction, original occurrence coverage, saved anchor restoration and owned handles after owner cancellation/destruction. |
| inputs / outputs | Inputs and return are those in \`void candidate_reconstruction_and_ownership()\`; body-specific behavior: Check candidate construction, original occurrence coverage, saved anchor restoration and owned handles after owner cancellation/destruction. |
| invariants | Published handle values are copied/owned; cancelling search discards private work but does not invalidate the saved handle. |
| ownership | Fixture and reference oracles are local; candidate handles own exported artifacts beyond owner cancellation/destruction. |
| failure | Candidate reconstruction/handle mismatch or API error fails; cancellation is not a retry on that owner. |
| cost | Finite reconstruction/ownership fixtures and exact checks; no timing claim. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0073

[Lines 745–815](../../../../../tests/unit/residual_test.cpp#L745); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void residual_ceiling_extensions_resume() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extend selected ceilings and resume the same retained owner to terminal results. |
| inputs / outputs | Inputs and return are those in \`void residual_ceiling_extensions_resume()\`; body-specific behavior: Extend selected ceilings and resume the same retained owner to terminal results. |
| invariants | Only configured ceilings are raised; resource-accounting records are not CPU benchmarks. |
| ownership | Fixture and continuation owners are local; result handles are copied values. |
| failure | Unreached completion/raised ceiling mismatch fails; the same retained owner is resumed. |
| cost | Finite limit extensions; step counts and resource ceilings are logical work, not CPU measurements. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0075

[Lines 817–933](../../../../../tests/unit/residual_test.cpp#L817); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void slicing_zero_quantum_and_limit_resume() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare whole, one-step and alternating slices; verify zero-quanta inertness and same-owner exact replay after ceiling raise. |
| inputs / outputs | Inputs and return are those in \`void slicing_zero_quantum_and_limit_resume()\`; body-specific behavior: Compare whole, one-step and alternating slices; verify zero-quanta inertness and same-owner exact replay after ceiling raise. |
| invariants | Zero grant leaves public progress inert; exact replay continuation remains on the same owner after a limit change. |
| ownership | Each run owns its planner state; result handles are values and progress snapshots are copied. |
| failure | Non-inert zero grant, wrong pause state, or incorrect resumed result fails; same owner continues exact replay. |
| cost | Multiple finite slices per run; zero quantum is checked through public progress equality. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0077

[Lines 935–937](../../../../../tests/unit/residual_test.cpp#L935); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::ResidualTraceRecord get_good_mutation_target(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a trace record chosen for mutation/rejection tests. |
| inputs / outputs | Inputs and return are those in \`planner::ResidualTraceRecord get_good_mutation_target(const Fixture& fixture)\`; body-specific behavior: Return a trace record chosen for mutation/rejection tests. |
| invariants | Mutation target is copied from a known-good trace produced for this fixture. |
| ownership | Fixture is borrowed; returned ResidualTraceRecord owns its copied public fields. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0079

[Lines 939–1030](../../../../../tests/unit/residual_test.cpp#L939); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rejected_mutations() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mutate candidate/trace/certificate-like fields and require public verifier/reconstructor rejection. |
| inputs / outputs | Inputs and return are those in \`void rejected_mutations()\`; body-specific behavior: Mutate candidate/trace/certificate-like fields and require public verifier/reconstructor rejection. |
| invariants | Each mutation targets a claimed exported semantic field; rejection is a validator result, not proof all corruptions are covered. |
| ownership | Mutable trace/candidate copies are local; source fixture remains borrowed and unchanged. |
| failure | Mutated invalid artifact accepted, or valid one rejected, fails through check; only enumerated mutations are covered. |
| cost | Finite mutation table and validation calls. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0081

[Lines 1032–1069](../../../../../tests/unit/residual_test.cpp#L1032); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exact_inner_reason_and_fallback_handle() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Show exact inner P06 stop reason, then raise the relevant limit and use a retained fallback handle to resume. |
| inputs / outputs | Inputs and return are those in \`void exact_inner_reason_and_fallback_handle()\`; body-specific behavior: Show exact inner P06 stop reason, then raise the relevant limit and use a retained fallback handle to resume. |
| invariants | Fallback handle represents a retained exact-search continuation; limit raise resumes this owner, not a new search. |
| ownership | All exact search owners and fallback handles are local; no owner escapes. |
| failure | Expected exact-stop reason and subsequent retained continuation are asserted; unrelated runtime errors propagate. |
| cost | One bounded exact-search continuation fixture. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |

## B0082

[Lines 1070–1072](../../../../../tests/unit/residual_test.cpp#L1070); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1070-L1072:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in residual_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |

## B0083

[Lines 1073–1088](../../../../../tests/unit/residual_test.cpp#L1073); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run residual planner semantic/oracle and continuation fixtures; return conventional process status. |
| inputs / outputs | Inputs and return are those in \`int main()\`; body-specific behavior: Run residual planner semantic/oracle and continuation fixtures; return conventional process status. |
| invariants | The driver assembles finite cases and reports exceptions; no run is claimed by this documentation. |
| ownership | All fixture objects are local to main and called test groups. |
| failure | Catches std::exception, prints it and returns 1; execution is not asserted here. |
| cost | Invokes the finite semantic suite; no run is claimed. |
| Design | [tests/unit/residual_test.cpp](../../../../../tests/unit/residual_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [tests/reference/residual_oracle.hpp](../../../../../tests/reference/residual_oracle.hpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/residual_candidates.md § Reconstruction and its soundness boundary](../../../../residual_candidates.md), [docs/planner_proofs.md § Complete normal-form family (P03)](../../../../planner_proofs.md) |
