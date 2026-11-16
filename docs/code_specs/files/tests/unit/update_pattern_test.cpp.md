# `tests/unit/update_pattern_test.cpp` — block usage map

[Source](../../../../../tests/unit/update_pattern_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `7ab39c37d8e87da6a38e3caec42fd5cab723d51cdab49a30ffea465c5f501011`. 276 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/update_pattern_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Build genuine P02/P07 handles; fixture expectations never create authority. · [reviewed contract](#b0001) |
| [B0002 · 15–19](../../../../../tests/unit/update_pattern_test.cpp#L15) | Callable definition: CompiledProgram compile(const c02_test::Fixture& fixture, const planner::CandidateSnapshot& candidates) | calls CompiledProgram::standalone, planner::lower_tree, candidate, tree; returns CompiledProgram::standalone(planner::lower_tree(; source comment (unverified): // Build genuine P02/P07 handles; fixture expectations never create authority. · [reviewed contract](#b0002) |
| [B0003 · 20–20](../../../../../tests/unit/update_pattern_test.cpp#L20) | Explanatory comments or spacing. |  |
| [B0004 · 21–26](../../../../../tests/unit/update_pattern_test.cpp#L21) | Callable definition: template&lt;class Function&gt; void rejects(Function function, ip::Fault expected) | calls function, fault, check; guard check(rejected, "declaration accepted an invalid shape or insufficient grant"); · [reviewed contract](#b0004) |
| [B0005 · 27–29](../../../../../tests/unit/update_pattern_test.cpp#L27) | Explanatory comments or spacing. | source comment (unverified): // Capture canonical table order and explicit group membership without merging · [reviewed contract](#b0005) |
| [B0006 · 30–89](../../../../../tests/unit/update_pattern_test.cpp#L30) | Callable definition: void declaration_contract(const CompiledProgram& source) | calls resource::MemoryAccount::create, statistics, ip::Declaration::capture, check; guard check(declaration.matches(source) && declaration.constrained(),; growth copy_of; 1 loop sites; source comment (unverified): // Capture canonical table order and explicit group membership without merging · [reviewed contract](#b0006) |
| [B0007 · 90–92](../../../../../tests/unit/update_pattern_test.cpp#L90) | Explanatory comments or spacing. | source comment (unverified): // An independently known three-member family separates a joint FIFO promise · [reviewed contract](#b0007) |
| [B0008 · 93–157](../../../../../tests/unit/update_pattern_test.cpp#L93) | Callable definition: void height_two_contract(const c02_test::Fixture& fixture, const planner::CandidateSnapshot& candidates, const CompiledProgram& s… | calls resource::MemoryAccount::create, ip::Declaration::capture, candidate_count, pp::analyse; guard check(result.stop == planner::ranking::Stop::complete && result.analysis.has_value(),; returns count; 2 loop sites; source comment (unverified): // An independently known three-member family separates a joint FIFO promise · [reviewed contract](#b0008) |
| [B0009 · 158–161](../../../../../tests/unit/update_pattern_test.cpp#L158) | Explanatory comments or spacing. | source comment (unverified): // Arbitrary height-one maintenance needs only bounded occurrence fanout; · [reviewed contract](#b0009) |
| [B0010 · 162–189](../../../../../tests/unit/update_pattern_test.cpp#L162) | Callable definition: void transfer_contract() | calls resource::MemoryAccount::create, push_back, c02_test::candidates, code; guard check(rejected, "nullable direct CQ bypassed the existing compiler admission");; growth push_back; 1 loop sites; source comment (unverified): // Arbitrary height-one maintenance needs only bounded occurrence fanout; · [reviewed contract](#b0010) |
| [B0011 · 190–192](../../../../../tests/unit/update_pattern_test.cpp#L190) | Explanatory comments or spacing. | source comment (unverified): // The general mixed-pattern characterization remains open. Use a genuine · [reviewed contract](#b0011) |
| [B0012 · 193–225](../../../../../tests/unit/update_pattern_test.cpp#L193) | Callable definition: void taller_contract() | calls pattern_test::height_three_fixture, pattern_test::height_three_family, candidate, CompiledProgram::standalone; guard check(result.stop == planner::ranking::Stop::complete &&; returns edge.basis==pp::EdgeBasis::subtree_insertion_only; growth insert, push_back; 3 loop sites; source comment (unverified): // The general mixed-pattern characterization remains open. Use a genuine · [reviewed contract](#b0012) |
| [B0013 · 226–228](../../../../../tests/unit/update_pattern_test.cpp#L226) | Explanatory comments or spacing. | source comment (unverified): // Constant routes need no maintained join. SQL all-insertion and arbitrary · [reviewed contract](#b0013) |
| [B0014 · 229–258](../../../../../tests/unit/update_pattern_test.cpp#L229) | Callable definition: void route_contract() | calls resource::MemoryAccount::create, c02_test::candidates, compile, ip::Declaration::capture; guard check(result.stop == planner::ranking::Stop::complete &&; 1 loop sites; source comment (unverified): // Constant routes need no maintained join. SQL all-insertion and arbitrary · [reviewed contract](#b0014) |
| [B0015 · 259–261](../../../../../tests/unit/update_pattern_test.cpp#L259) | Closes surrounding scope/type. |  · [reviewed contract](#b0015) |
| [B0016 · 262–276](../../../../../tests/unit/update_pattern_test.cpp#L262) | Callable definition: int main() | calls c02_test::fixture, c02_test::candidates, compile, declaration_contract; returns 1 · [reviewed contract](#b0016) |

## B0001

[Lines 1–14](../../../../../tests/unit/update_pattern_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:dae2be3f56f5ba9852b81a83ceef06af868f85f9c5e086c20d68f2302f03a633
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import genuine ranking fixture, declaration/analyzer APIs, error binding helpers, and test output support. |
| inputs / outputs | Include the shared typed height-three fixture, declaration/analyzer API, binding helpers and test output support. |
| invariants | The shared helper runs actual exact proof/P07 admission; fixture expectations and includes themselves supply no checked authority. |
| ownership | Test objects own their ordinary harness state; runtime declarations are created in explicit test accounts. |
| failure | No behavior beyond include/namespace setup. |
| cost | Compile-time only. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0002

[Lines 15–19](../../../../../tests/unit/update_pattern_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L19:sha256:d5f9425eb7b005e952ab335508f6e535a0eda6e402c9664b94a638cb7c513c52
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile a real fixture candidate into a standalone CompiledProgram through P07 tree lowering. |
| inputs / outputs | Fixture and CandidateSnapshot enter; returns CompiledProgram from fixture catalog/query and candidate zero tree. |
| invariants | Candidate authority comes from the real P02/P07 fixture path; expectations do not synthesize a valid tree. |
| ownership | Returned standalone program owns its compiled metadata under its own account. |
| failure | Candidate absence or lowering errors fail the test through existing checks/exceptions. |
| cost | One native lowering for the fixture tree. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0004

[Lines 21–26](../../../../../tests/unit/update_pattern_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L26:sha256:21c6439dc61819f22deb8e46f4c0d34a075396d376666f3b661f43f492e3bd22
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that a declaration operation rejects the expected Fault. |
| inputs / outputs | Runs a callable, catches only ip::Failure, compares its fault with expected, then uses c02_test::check. |
| invariants | The helper checks the specified rejection category; it does not swallow unrelated exceptions. |
| ownership | Callable’s captures remain under the enclosing test’s owners. |
| failure | Fails the test if no Failure or wrong Fault is observed. |
| cost | One operation invocation plus exception-path check. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0005

[Lines 27–29](../../../../../tests/unit/update_pattern_test.cpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L29:sha256:26e4fc9c355cbd1b4da7e7786f37be7bfa0a026ea9b571edd85f0a109294eed8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe declaration tests for canonical order, explicit scopes, logical grants, account cleanup, import shape, and export. |
| inputs / outputs | The next test receives a real CompiledProgram fixture. |
| invariants | Scope IDs remain distinct raw values; logical limits and actual allocator caps are exercised separately. |
| ownership | Each tested declaration is funded by an explicit MemoryAccount and released before final statistics checks. |
| failure | Tests expect invalid shape/limits to reject without retained partial storage. |
| cost | Test intent only; no runtime claim. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0006

[Lines 30–89](../../../../../tests/unit/update_pattern_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L89:sha256:96d34ace21235820f6d19a67228202ee968f93e048011c8bdbd8d1885416c0be
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise capture/import/copy/export behavior and logical/account failures for TableRule declarations. |
| inputs / outputs | Builds unsorted three-table rules including insertion-only and UINT64_MAX scope; verifies canonical lookup, exact Usage replay, each one-below grant, DTO round-trip, foreign/malformed hashes, duplicate/unknown tables, receiving-account copy, empty declaration, teardown, and tiny-account denial. |
| invariants | Assertions establish tested declaration behavior only; hash-valid import is not source authority; logical caps do not bypass account cap; failed construction leaves current account storage unchanged. |
| ownership | Uses explicit account statistics to verify original and receiving allocations are released; Record export uses caller vector. |
| failure | Expected Faults are checked by \`rejects\`; tiny account must produce MemoryFailure and retain only its controller allocation. |
| cost | O(R log R) capture with small fixture R; test-only repeated account/statistics snapshots. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0007

[Lines 90–92](../../../../../tests/unit/update_pattern_test.cpp#L90); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L90-L92:sha256:8ffdf04ade5283b618194ca2aa21b39607add0e74dbb8d636a8fa2b03db48f98
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the finite three-member family tests that distinguish joint FIFO, separate scopes, child insertion, and all-insertion. |
| inputs / outputs | The next test receives the genuine fixture, P02/P07 candidate snapshot, and compiled source. |
| invariants | Test compares only retained candidates in this known family; it is not a proof over all CQs/families. |
| ownership | Candidate/source/declaration owners are those returned by fixture/compiler; analysis edges use test receiving account. |
| failure | Unexpected incomplete analysis or sufficient-case count fails the test. |
| cost | Bounded finite-family test intent; no exhaustive-family claim. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0008

[Lines 93–157](../../../../../tests/unit/update_pattern_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L93-L157:sha256:7eadc332fe5b4d43459f98858fcc9e935292327447ba78410d2b00f98913a641
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check native height-two sufficient cases, binding refusal, aggregate limits, and no-partial-result behavior on genuine candidates. |
| inputs / outputs | Uses real snapshot; tests all members under joint ID 17, distinct IDs 17/18/19, child insertion-only, all insertion-only, exact analysis grant, one-below work stop, foreign source and same-shaped foreign candidate. A direct raw report constructor must remain unknown/not_checked, keep edges empty, and add no account allocation. |
| invariants | Only expected local sufficient conditions are asserted; separate per-table IDs are never promoted to joint scope; full typed source/candidate comparison rejects a foreign candidate. All-insertion now reports checked_monotone_source; the existing mixed height-two cases report checked_typed_cq. Original candidate/declaration handles and exact grant controls remain. |
| ownership | Analyses run in an 8 MiB receiving account and retain candidate/declaration handles without fabricating their authority. |
| failure | Failed grant must return work_limit and no Analysis; foreign bindings must return binding_mismatch. |
| cost | Finite family iteration and bounded analyzer work; not total CPU/delay proof. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0009

[Lines 158–161](../../../../../tests/unit/update_pattern_test.cpp#L158); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L158-L161:sha256:5c87e1323df1ea645337a31770834e032d61ee7c2477875af14e5ef5a29ddcf6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain why arbitrary height-one source mapping permits projection and aliases while compiler nullable refusal remains separate. |
| inputs / outputs | Source comment only; adjacent fixtures check bounded occurrence transfer. |
| invariants | This note does not assert physical-to-logical FIFO through projection or aliases. |
| ownership | Fixtures are built through the real P02/P07 candidate path, then compiled/lowered normally. |
| failure | Unsupported source transfer must remain unknown; compiler rejection is expected for nullable direct CQ. |
| cost | No executable work from the comment; fixture construction/search has its own cost. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0010

[Lines 162–189](../../../../../tests/unit/update_pattern_test.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L162-L189:sha256:cf1cd0681d0ada3bb3a71acc5e8ce8fac2c32e665a01d140ac203caefe4ba438
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check arbitrary height-one source-event transfer and the unchanged nullable direct-CQ compiler boundary. |
| inputs / outputs | For five variants, creates one-table fixture, changes second term/nullability/self-join, obtains genuine candidates, compiles, captures an empty declaration, and analyzes. |
| invariants | Variables/repeats/constants, ignored columns and same-source aliases all admit the height-one event case. Nullable direct input still fails before a pattern candidate exists; no general FIFO transfer is inferred. |
| ownership | Each declaration uses the explicit receiving account; candidate handles retain genuine checked catalog/query/tree/proof owners, while the source owns its actual native compiled program. |
| failure | Unexpected compiler acceptance of nullable input or unexpected sufficient case fails via check. |
| cost | Five finite fixture variants with real proof/provider/lowering; no runtime benchmark or exhaustive source-language check. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0011

[Lines 190–192](../../../../../tests/unit/update_pattern_test.cpp#L190); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L190-L192:sha256:2c345d7ed8205ce5393a3c4ef3edff5ac3b959c13aa14a92b47218fa80c30205
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document that the mixed-pattern general characterization remains open and the following test retains only a genuine height-three witness. |
| inputs / outputs | The next test runs exact search to height three and retains its first candidate only. |
| invariants | A finite prefix is not presented as exhaustion of all native trees; height-two analyzer cases do not justify deeper claims. |
| ownership | No storage effect in this comment. |
| failure | Search failure is asserted by the test. |
| cost | Test intent only. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0012

[Lines 193–225](../../../../../tests/unit/update_pattern_test.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L193-L225:sha256:6b1f137e37baa18b4c48b424e45343cebfb6c184f4d51a1e4a1c862a8f438a7e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a genuine minimum-height-three mixed refusal, all-insertion success and proved monotone-subtree success. |
| inputs / outputs | Use the shared seven-atom schema and one genuine P07 candidate; compare all-FIFO unknown, all-source insertion-only and one arbitrary first-native branch with insertion-only descendants. |
| invariants | The exact original minimum is three. Only a retained prefix is used; no family-exhaustion or minimum-maintenance claim. The taller mixed case must retain a subtree_insertion_only edge basis. |
| ownership | The fixture/candidate/proof/program and declarations own their usual data; analysis scratch/edges use the explicit original receiving account. |
| failure | Requires completed exact proof and one candidate; stop or wrong case fails test. |
| cost | One finite exact search/provider prefix and three explicit analyses. No per-update production work or timing benchmark. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0013

[Lines 226–228](../../../../../tests/unit/update_pattern_test.cpp#L226); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L226-L228:sha256:ca0fef276b44e8a3ae6c7c944c3a616eb4dc873afe7927614c08fdbd885f0084
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document constant routes and the separately justified SQL monotone/height-one event cases. |
| inputs / outputs | Next block compiles contradictory/constant routes and a normalized SQL source. |
| invariants | Source-event transfer grants no FIFO lifetime premise or structural authority. |
| ownership | All program/candidate handles follow existing compiler and account ownership. |
| failure | Failed SQL bind/normalize or wrong transfer classification fails the test. |
| cost | Prose has no runtime cost; adjacent tests own compile/proof/analysis work. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0014

[Lines 229–258](../../../../../tests/unit/update_pattern_test.cpp#L229); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L229-L258:sha256:3bfd36650186f27a96b9f6007ffd8efad3f69d6b0594dc3dc3966f0272c3f798
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check constant-route sufficiency plus SQL all-insertion and arbitrary height-one event transfer. |
| inputs / outputs | Analyze constant empty/unit routes, then an admitted normalized unary query under physical insertion-only and empty declarations. |
| invariants | Constants report not_required; SQL insertion-only reports checked_monotone_source and arbitrary height-one reports checked_event_mapping. No checked_typed_cq/FIFO transfer is substituted. |
| ownership | Uses explicit account for declaration; program/candidate owners are returned by compiler/planner APIs. |
| failure | Binding, normalization, candidate creation, or unexpected sufficient case fails. |
| cost | Finite native proof/compilation and explicit analyses; no public CPU/delay claim. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0015

[Lines 259–261](../../../../../tests/unit/update_pattern_test.cpp#L259); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L259-L261:sha256:0fc5d8ec7d53a9193325663dc0e7cbfbd83e87df77e1c966b6657fe657840e0d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the test’s anonymous namespace. |
| inputs / outputs | No inputs/outputs. |
| invariants | No runtime behavior. |
| ownership | No ownership effect. |
| failure | No failure path. |
| cost | No runtime cost. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0016

[Lines 262–276](../../../../../tests/unit/update_pattern_test.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L262-L276:sha256:d498ee4c59a7fa943ce66444633d45563efd696c22bf74414fd662104f301b67
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the declaration and conditional-analysis fixture contracts from main. |
| inputs / outputs | Creates genuine base fixture/candidates/source; calls declaration, height-two, transfer, taller, and route contracts; prints success or catches std::exception and returns failure. |
| invariants | The printed success means these finite unit fixtures passed; it does not mean V51 implementation acceptance, runtime enforcement, or exhaustive characterization. |
| ownership | Test-local handles release on normal/exceptional scope exit; test process owns the output streams. |
| failure | Returns 1 and reports exception text if any contract fails. |
| cost | Executes the finite suites in sequence; native test invocation is separate from this card audit. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |
