# `tests/unit/selection_pattern_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_pattern_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `2a58ff904f20219c1c995ad304068573c36ed451f6400014c04cec29f24fc73f`. 185 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/unit/selection_pattern_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 14–18](../../../../../tests/unit/selection_pattern_test.cpp#L14) | Callable definition: ps::Selection complete(ps::Attempt attempt) | calls check, has_value; guard check(attempt.stop == ps::Stop::complete && attempt.selection.has_value(),; returns *attempt.selection · [reviewed contract](#b0002) |
| [B0003 · 19–21](../../../../../tests/unit/selection_pattern_test.cpp#L19) | Explanatory comments or spacing. | source comment (unverified): // Prove a decision consequence in the real retained family, then verify exact · [reviewed contract](#b0003) |
| [B0004 · 22–93](../../../../../tests/unit/selection_pattern_test.cpp#L22) | Callable definition: void decision_contract() | calls c02_test::fixture, c02_test::candidates, CompiledProgram::standalone, planner::lower_tree; guard check(baseline.pattern_analyses().empty() && !baseline.request().update_patterns,; 2 loop sites; source comment (unverified): // Prove a decision consequence in the real retained family, then verify exact · [reviewed contract](#b0004) |
| [B0005 · 94–95](../../../../../tests/unit/selection_pattern_test.cpp#L94) | Explanatory comments or spacing. | source comment (unverified): // Persistently deny each covered ordinary/aligned C++ allocation, including · [reviewed contract](#b0005) |
| [B0006 · 96–173](../../../../../tests/unit/selection_pattern_test.cpp#L96) | Callable definition: void allocation_contract() | calls c02_test::fixture, c02_test::candidates, resource::MemoryAccount::create, planner::lower_tree; guard check(healthy.stop == ps::Stop::complete && healthy.selection && positions &gt; 0 && positions &lt; 100'0…; growth allocate; 1 loop sites; source comment (unverified): // Persistently deny each covered ordinary/aligned C++ allocation, including · [reviewed contract](#b0006) |
| [B0007 · 174–176](../../../../../tests/unit/selection_pattern_test.cpp#L174) | Closes surrounding scope/type. |  · [reviewed contract](#b0007) |
| [B0008 · 177–185](../../../../../tests/unit/selection_pattern_test.cpp#L177) | Callable definition: int main() | calls decision_contract, allocation_contract, what; returns 1 · [reviewed contract](#b0008) |

## B0001

[Lines 1–13](../../../../../tests/unit/selection_pattern_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:68ce705d7c7dabd5654c7e263b92d5ff1717ad2b39e3c3bfb694cef01a7eed0f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the real fixture and pure selection API, and enable the existing single-TU test allocator replacement seam. |
| inputs / outputs | Includes index_allocation.hpp in this test executable only; its ordinary/aligned C++ new/delete replacements support scoped persistent allocation denial. Other includes/aliases expose test/API types. |
| invariants | Only this test translation unit owns the replacement operators. Scope enables counting/denial; raw libc malloc calls and C++ exception-runtime storage are outside its denial coverage. No production library includes this seam. |
| ownership | The seam owns thread-local test control fields; every replacement allocation has its matching replacement release. Fixture/caches/native accounts remain explicitly owned by the tests. |
| failure | Missing/incompatible declarations fail compilation. Test scopes can deliberately cause bad_alloc; nested scopes terminate by the existing helper contract. |
| cost | Includes compile declarations and test-only replacement allocator calls. Fault sweeps add test runtime work; production paths and libraries gain no hook. |
| Design | [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md), [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0002

[Lines 14–18](../../../../../tests/unit/selection_pattern_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L18:sha256:ba91a1fbfac5db3026f9448154dc60d49ef219a8661ef98357a78ffed46153a3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an Attempt to contain a complete Selection and return its handle. |
| inputs / outputs | Consumes Selection::Attempt by value; checks complete stop and engaged selection; returns the selected value. |
| invariants | Incomplete attempts fail the test instead of supplying a fabricated result. |
| ownership | Returned Selection retains its immutable owner handles through ordinary value copy. |
| failure | Fails with the supplied test message if stop/result disagree. |
| cost | O(1) wrapper check plus handle copy. |
| Design | [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0003

[Lines 19–21](../../../../../tests/unit/selection_pattern_test.cpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L21:sha256:a4be53158d250c4e5942e1919633e8bb5eeaf18ab98b8ffd5d850e4cb3c19aa0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the end-to-end decision test: real family, changed winner, exact rule/cache binding, and unchanged height authority. |
| inputs / outputs | The next block builds genuine fixture candidates and a PhysicalBasis source. |
| invariants | Default mode must not fabricate an analysis; opt-in conditions remain conditional and must not alter structural proof authority. |
| ownership | Selection and cache results keep their normal owners; declaration rule values are explicitly captured. |
| failure | Each mismatch is reported through the test harness. |
| cost | Finite retained-family test only. |
| Design | [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md), [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0004

[Lines 22–93](../../../../../tests/unit/selection_pattern_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L93:sha256:92f1cbbbe18f6f0bcf107185f1b4a50dc24cb720606d80cc2cb94843a44eddc4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise pure conditional selection, winner filtering, raw scope cache binding, resource refusal, and source-binding rejection. |
| inputs / outputs | Builds real P02/P07 candidates and source; confirms default has no pattern analysis; captures a rule that changes the selected shape; verifies original height proof/source digest and retained context; checks per-candidate eligibility and exact cache hit; proves raw ID changes alter cache key; imposes low work grant and checks no partial selection/cache/account leak; tests empty declaration unsatisfied, DirectCQ unsupported_model, and foreign import binding_mismatch. |
| invariants | Only conditionally eligible candidates can win; selection preserves original height authority. The empty declaration proves no case for this height-two fixture, while other queries can satisfy height-one or constant cases without rules. Distinct raw scope IDs cannot alias. DirectCQ refusal is API admission, not query impossibility. |
| ownership | Fixture/source/candidates use real authority; PlanCache and MemoryAccount statistics are observed around calls; returned results retain normal handles. |
| failure | Any stop/result/cache/binding mismatch fails the unit test; failed aggregate work must leave no selection, cache mutation, or extra live account allocation. |
| cost | Finite fixture with repeated pure selection/cache operations and account statistics; no native runtime enforcement test. |
| Design | [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md), [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0005

[Lines 94–95](../../../../../tests/unit/selection_pattern_test.cpp#L94); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L95:sha256:a68b978284cd954a166fb59f42466064172bd8a0655d8b8d3dc40a5a4cabd60d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the persistent allocation-denial coverage of the following selection control. |
| inputs / outputs | Static note names ordinary/aligned C++ allocation denial, receiving-account pattern vectors/edges and the raw-malloc exclusion. |
| invariants | The comment is usage guidance; allocation_contract and the existing single-TU allocator seam implement the control. It supplies no production monitor or proof. |
| ownership | No storage or owner is introduced by this comment. |
| failure | No runtime failure path in the note; unexpected test outcomes fail in the following function. |
| cost | Source documentation only; no production branch, allocation or instruction. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/files/tests/support/index_allocation.hpp.md](../support/index_allocation.hpp.md) |

## B0006

[Lines 96–173](../../../../../tests/unit/selection_pattern_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L96-L173:sha256:63c4eedc15fb69b5d2d0f66c57c8783801b30f11c70d2b4d616557b3a68f02bb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise actual allocation failure and byte-cap refusal through pattern-aware public selection. |
| inputs / outputs | Build a genuine three-member family, native program and joint-scope declaration under a 1 MiB account. Count a healthy cold-cache call, persistently deny each covered ordinary/aligned C++ new position, require pattern-stage denials and a healthy continuation, then fill the remaining native cap using allocation_bytes(1)-1 framing and require allocation_failure. |
| invariants | Failed attempts return no Selection, preserve cold cache statistics/current account storage, and leave a previously retained analysis valid. Recoverable complete results must preserve the selected candidate. Peak/history counters may change. Coverage concerns scoped C++ new calls, not raw malloc or exception-runtime storage; the cap control separately checks the immutable native account. |
| ownership | Fixture/catalog/search objects keep their original owners. Native source/declaration/results consume the explicit account; each cut owns a fresh cache and private Attempt, with the denial guard alive through select cleanup. A filler MemoryBlock temporarily occupies residual bytes and releases before final current-storage comparison. |
| failure | Unexpected stop/state, missing pattern-stage denial, missing healthy continuation or wrong cap accounting fails the test after leaving the fault scope. No production failure hook or new production exception handler is introduced. |
| cost | Finite test-only O(K times selection work), where K is the measured covered allocation count, plus native-cap fill/release and explicit account/cache observations. No runtime input-update cost or whole-heap coverage claim. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/files/tests/support/index_allocation.hpp.md](../support/index_allocation.hpp.md) |

## B0007

[Lines 174–176](../../../../../tests/unit/selection_pattern_test.cpp#L174); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L175-L176:sha256:938de74be97bf3aba7872a61ba0e42084008c81e8a202a612134c755aaf7fa06
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous namespace after the decision fixture. |
| inputs / outputs | No inputs/outputs. |
| invariants | No runtime behavior. |
| ownership | No ownership effect. |
| failure | No failure path. |
| cost | No runtime cost. |
| Design | [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0008

[Lines 177–185](../../../../../tests/unit/selection_pattern_test.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L177-L185:sha256:17ee21c6b94bf0079021b160f488206a274909dff75d99a63f2e4ea3c2fbe19a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the single conditional selection contract and report its test outcome. |
| inputs / outputs | Run decision_contract and allocation_contract, report counters/outcome, and translate an unexpected test exception to stderr/exit 1. |
| invariants | Success is evidence for this finite selection fixture only; it does not prove a runtime monitor or general P4 theorem. |
| ownership | All local selection/cache handles release at scope exit. |
| failure | Caught standard exceptions yield nonzero test exit. |
| cost | Two finite fixture suites: decision/cache/resource controls and persistent allocation/cap controls. No production execution cost. |
| Design | [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md), [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |
