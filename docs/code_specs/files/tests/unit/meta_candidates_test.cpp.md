# `tests/unit/meta_candidates_test.cpp` — block usage map

[Source](../../../../../tests/unit/meta_candidates_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `9f5791fd36e8bb1c5dad17735b67c4a926c7944cefd8e9ed2c4aa08b9650f994`. 235 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/meta_candidates_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 21–21](../../../../../tests/unit/meta_candidates_test.cpp#L21) | Callable definition: void require(bool value,const std::string& message) | calls std::runtime_error; guard void require(bool value,const std::string& message) { if (!value) throw std::runtime_error(message)… · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../tests/unit/meta_candidates_test.cpp#L22) | Type/record definition: struct Fixture |  · [reviewed contract](#b0003) |
| [B0004 · 23–41](../../../../../tests/unit/meta_candidates_test.cpp#L23) | Callable definition: Fixture fixture(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& edges, const std::vector&lt;std::size_t&gt;& head = {}) | calls emplace, size, push_back, std::to_string; returns f; growth emplace, emplace_back, push_back; 6 loop sites · [reviewed contract](#b0004) |
| [B0005 · 42–47](../../../../../tests/unit/meta_candidates_test.cpp#L42) | Callable definition: VerifiedOptimum prove(const Fixture& f) | calls ExactSearch::create, advance, require, optimum; guard require(done.progress.result == ResultKind::verified_optimum && exact.optimum(),"independent origin…; returns *exact.optimum() · [reviewed contract](#b0005) |
| [B0006 · 48–55](../../../../../tests/unit/meta_candidates_test.cpp#L48) | Callable definition: void finish(CandidateProvider& owner) | calls advance, require, std::runtime_error; guard require(stop == CandidateStop::candidate_ready \|\| stop == CandidateStop::quantum_work,"unexpected m…; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 56–67](../../../../../tests/unit/meta_candidates_test.cpp#L56) | Callable definition: std::set&lt;std::string&gt; signatures(const Fixture& f,const CandidateSnapshot& snapshot,std::size_t height) | calls candidate_count, candidate, require, has_value; guard const auto c = snapshot.candidate(i); require(c.has_value(),"published mapped candidate missing");; returns result; growth insert; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 68–73](../../../../../tests/unit/meta_candidates_test.cpp#L68) | Callable definition: void complete(const meta::PreparedMetaCandidates& prepared) | calls require; guard require(prepared.report.construction_stop == meta::Stop::complete && prepared.report.ordinary_exhau… · [reviewed contract](#b0008) |
| [B0009 · 74–92](../../../../../tests/unit/meta_candidates_test.cpp#L74) | Callable definition: void reference_case(const Fixture& f,const std::string& label) | calls prove, io::write_verified_optimum, meta::prepare_meta_candidates, complete; guard require(!prepared.report.all_ordinary_roots_materialized &&; growth insert; 2 loop sites · [reviewed contract](#b0009) |
| [B0010 · 93–95](../../../../../tests/unit/meta_candidates_test.cpp#L93) | Explanatory comments or spacing. | source comment (unverified): // Independent hierarchical set partitions, not inverse contractions or a join · [reviewed contract](#b0010) |
| [B0011 · 96–125](../../../../../tests/unit/meta_candidates_test.cpp#L96) | Callable definition: std::vector&lt;FreeConnexTree&gt; hierarchies(const std::vector&lt;std::size_t&gt;& leaves) | calls size, push_back, self, pop_back; returns {{NodeId{0},{{@ ,NodeKind::native,{VariableId{0}},{},leaves\[0\],{}}},{},{}}}; result; growth push_back; 5 loop sites; source comment (unverified): // Independent hierarchical set partitions, not inverse contractions or a join · [reviewed contract](#b0011) |
| [B0012 · 126–139](../../../../../tests/unit/meta_candidates_test.cpp#L126) | Callable definition: void four_leaf_fiber() | calls fixture, prove, require, height; guard require(proof.height() == 1,"four-leaf literal lower/upper control");; growth insert; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 140–195](../../../../../tests/unit/meta_candidates_test.cpp#L140) | Callable definition: void grants_and_status() | calls fixture, prove, meta::prepare_meta_candidates, complete; guard auto full = meta::prepare_meta_candidates(proof); complete(full); require(full.provider.has_value()…; 2 loop sites · [reviewed contract](#b0013) |
| [B0014 · 196–219](../../../../../tests/unit/meta_candidates_test.cpp#L196) | Callable definition: void selection_and_domains() | calls fixture, prove, meta::prepare_meta_candidates, complete; guard auto prepared = meta::prepare_meta_candidates(proof); complete(prepared); require(prepared.provider…; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 220–220](../../../../../tests/unit/meta_candidates_test.cpp#L220) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0015) |
| [B0016 · 221–235](../../../../../tests/unit/meta_candidates_test.cpp#L221) | Callable definition: int main() | calls reference_case, fixture, std::to_string, size; returns 1; 2 loop sites · [reviewed contract](#b0016) |

## B0001

[Lines 1–20](../../../../../tests/unit/meta_candidates_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:2e035b885e4d99cf94b3c263460e65165c1375d4805b7f7e8d82596cf64ddea5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide test-only imports, standard-library declarations, and the namespace for finite meta-candidate checks. |
| inputs / outputs | Includes expose the adapter, selection, I/O, exact-search, and reference-oracle types used by later blocks. |
| invariants | This scaffolding does not add a production API or claim exhaustive coverage of query space. |
| ownership | Preprocessor and namespace scaffolding retains no runtime query or candidate state. |
| failure | Missing declarations or incompatible APIs fail at compilation. |
| cost | Compilation cost only; no planner or update work occurs here. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp) |

## B0002

[Lines 21–21](../../../../../tests/unit/meta_candidates_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L21:sha256:07fe3c20695da699a5db55ea851f684e833b334b9e807680be5354b781e253fd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed test predicate into a diagnostic exception. |
| inputs / outputs | require accepts a boolean and message; successful checks return normally. |
| invariants | Only a false predicate takes the failure branch. |
| ownership | The message is passed by const reference; the helper stores no state. |
| failure | A failed check throws the test's runtime error with the supplied diagnostic. |
| cost | One predicate branch and exception construction only on failure. |
| Design | [tests/unit/meta_candidates_test.cpp](../../../../../tests/unit/meta_candidates_test.cpp) |

## B0003

[Lines 22–22](../../../../../tests/unit/meta_candidates_test.cpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:246d49180ec13ace5da6a94ef5aa6b366fc2329840f73eaede649aaa9d3b0474
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group the catalog and query fixture consumed by the independent small-instance checks. |
| inputs / outputs | Fixture carries the validated catalog/query values built by fixture(). |
| invariants | The fixture is test data; it is not a production CandidateProvider or a proof object. |
| ownership | The aggregate owns its value members for the duration of the test call. |
| failure | Invalid fixture metadata is rejected by the constructor helper or validation path. |
| cost | Value construction and storage proportional to the finite fixture description. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0004

[Lines 23–41](../../../../../tests/unit/meta_candidates_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L41:sha256:6b1cbd1b2a5f5ee61e6754edfcc4fd2af963704bd9720905b030a09ccfa259e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a compact query fixture from edge-variable lists and an optional head. |
| inputs / outputs | Each edge description becomes a table/atom incidence; optional head indexes select query head variables, then metadata validation runs. |
| invariants | Table IDs, variable IDs, atom ordering, aliases, and head membership are derived from this fixture input; validation is required before use. |
| ownership | The returned Fixture owns the catalog and query values; temporary construction data ends with the call. |
| failure | Malformed incidence/head metadata fails through validation or a test assertion. |
| cost | Work and storage scale with the explicitly listed edges and incidences; this is test setup, not a production complexity bound. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0005

[Lines 42–47](../../../../../tests/unit/meta_candidates_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L47:sha256:06905a0926d598393d0f807d7a9d2319e1cdf75b22cd73d1c0ddaa02063fd5d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain the baseline VerifiedOptimum used by each finite comparison. |
| inputs / outputs | ExactSearch is created for the fixture, advanced with a 50,000,000-work budget, and its verified optimum is required and returned. |
| invariants | The adapter receives the exact-search proof object rather than manufacturing or modifying an optimum. |
| ownership | The returned proof value is owned by the caller; ExactSearch is local to the helper. |
| failure | Creation, search, or a missing verified optimum fails the finite test. |
| cost | The explicit search budget bounds the test's selected work accounting for this fixture; it is not a total CPU/time guarantee. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0006

[Lines 48–55](../../../../../tests/unit/meta_candidates_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L55:sha256:ed1075981c9ac347294092d9b957729ab847e1da09dde2a9d52766ac17ab218b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume a finite-proposal provider until its terminal state for status checks. |
| inputs / outputs | The helper advances in quanta up to 10,000 iterations, accepting candidate-ready and quantum-work results, and requires exhaustion. |
| invariants | Only the provider's reported terminal exhaustion satisfies this helper; reaching the loop cap does not. |
| ownership | CandidateProvider remains caller-owned by reference and retains its own provider state. |
| failure | Unexpected advance status or failure to exhaust within the iteration cap fails the test. |
| cost | At most 10,000 calls with the stated one-million selected-work grant per call; no machine-time bound follows. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0007

[Lines 56–67](../../../../../tests/unit/meta_candidates_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L67:sha256:9f754cdbd1210e8b4b66d10ee40f07a015270821ad0a5414dd26acf7b1201328
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract and validate normalized signatures from a finite candidate snapshot. |
| inputs / outputs | For every snapshot tree, check its bound catalog/query, validity, and requested height, then record its reference normal-form signature and supplied-proposal provenance. |
| invariants | Duplicate normalized signatures collapse in the returned set; each admitted tree is checked against the same fixture and height. |
| ownership | The helper takes fixture/snapshot by const reference and returns an owning set of signature strings. |
| failure | Any invalid, misbound, wrong-height, or incorrectly sourced candidate fails through require. |
| cost | Visits the snapshot candidates and their represented nodes, plus set/signature construction; the test does not establish an asymptotic production bound. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp) |

## B0008

[Lines 68–73](../../../../../tests/unit/meta_candidates_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L73:sha256:612413ad55843210b6eba9bf28f4bb12350c97fee054571038c0dbfd52a04589
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert all ordinary and mapped-family completion flags for a prepared finite fixture. |
| inputs / outputs | Reads prepared construction, ordinary enumeration, mapping, mapped-input-fiber, and normalized-minimum-family status. |
| invariants | Completion requires every checked status and no heuristic marker; each flag is a separate condition. |
| ownership | The helper borrows the prepared result and retains no state. |
| failure | Any incomplete or heuristic state fails the test rather than being treated as full coverage. |
| cost | A fixed set of status reads; it does not perform additional enumeration. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0009

[Lines 74–92](../../../../../tests/unit/meta_candidates_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L92:sha256:ca64e216d02972bb37d0d4c48704330eacb3b242c080f0e38518ac93826b428a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare adapter output on one small fixture with an independent normalized-minimum reference set. |
| inputs / outputs | Runs prove(), writes the original proof, prepares the canonical meta adapter, consumes its provider, and compares normalized signatures to the independently traversed reference plan set at the proved height. |
| invariants | The family-complete flag is checked only after provider consumption; the independent oracle must itself report exhausted and not resource-limited; proof serialization remains unchanged across candidates. |
| ownership | Prepared provider and proof serialization are local test values; the exact proof passed to preparation remains the baseline. |
| failure | Any noncanonical-mode mismatch, missing provider, incomplete oracle, signature difference, or changed proof bytes fails the case. |
| cost | Finite enumeration over this fixture and its reference set; neither this case nor the 12-case matrix proves all-input completeness or a P3 delay theorem. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp) |

## B0010

[Lines 93–95](../../../../../tests/unit/meta_candidates_test.cpp#L93); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L93-L95:sha256:99834eea75f61a6b01a0ad8c1b721a2fa3f885341b732b8a07499f7699059d39
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the independence and restricted scope of the equal-scope hierarchy oracle. |
| inputs / outputs | The comment distinguishes hierarchical set partitions from inverse contractions and ordinary join-tree traversal, and records why identical scopes satisfy P02 at height one. |
| invariants | This rationale is local to the equal-scope fixture used below; it does not claim the generator covers every arbitrary query or every admissible decomposition. |
| ownership | Comment only; it owns no data or runtime behavior. |
| failure | No runtime failure path; an overbroad reading would exceed the evidence described by the tests. |
| cost | No executable work. |
| Design | [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/unit/meta_candidates_test.cpp](../../../../../tests/unit/meta_candidates_test.cpp) |

## B0011

[Lines 96–125](../../../../../tests/unit/meta_candidates_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L96-L125:sha256:496969dc80ef6ec19dd2debe16a265da33cafba8dbb750df27c53f18be05e0cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate all recursive hierarchical set partitions for the supplied finite leaf labels. |
| inputs / outputs | Recursively choose a set partition of the leaves and combine the recursively generated child hierarchies into FreeConnexTree values. |
| invariants | The generator is a test oracle for hierarchical shapes, not an inverse-contraction traversal; its intended use here is four leaves with identical scopes. |
| ownership | Returns an owning vector of trees; recursive child and partition values are temporary. |
| failure | Invalid/empty recursion cases or construction failures surface through the test's checks/allocation behavior. |
| cost | The number of generated structures grows combinatorially; the exercised four-leaf case has 26 recursive hierarchies (hierarchical set partitions) and is not a production budget claim. |
| Design | [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/unit/meta_candidates_test.cpp](../../../../../tests/unit/meta_candidates_test.cpp) |

## B0012

[Lines 126–139](../../../../../tests/unit/meta_candidates_test.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L126-L139:sha256:9d90eddf2f695d9ec4b39e911eb1d856ee66159c13f56f779928b93fff1b6a97
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the adapter's four-equal-scope fiber against all 26 independent hierarchical shapes. |
| inputs / outputs | Builds the four-leaf equal-scope fixture, independently generates hierarchical set partitions, checks every shape's P02 validity and height one, then compares normalized signatures with the consumed adapter family. |
| invariants | The result is a finite cross-check for four identical scopes and the exact fixture's proof; it does not establish completeness for arbitrary scopes or leaf counts. |
| ownership | All fixture, shape, proof, and provider values are local to the test. |
| failure | Any P02, height, exhaustion, or signature mismatch fails the test. |
| cost | Enumerates the 26 generated shapes and the corresponding adapter/reference output for this case only. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/candidate_set.hpp](../../../../../tests/reference/candidate_set.hpp), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp) |

## B0013

[Lines 140–195](../../../../../tests/unit/meta_candidates_test.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L140-L195:sha256:4aab8541c299a52fff2c32bd3c69be1247a40def92e9a282181c8f10d3f04cdf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise mapping grants, stopped states, rooted-output mode, and resumable candidate admission. |
| inputs / outputs | Builds an unlimited baseline for three equal scopes, replays exact observed work/cell/fragment/output/depth grants, tests each mapping stop at zero and one-short, tests ordinary output truncation, all-roots mode, and candidate-cap stop/resume. |
| invariants | A stopped or truncated invocation is expected to remain incomplete; a consumed provider cannot upgrade incomplete upstream ordinary coverage; resumed admission only completes after the provider reports family exhaustion. |
| ownership | Providers, prepared values, and finite grant copies are owned by this test helper; observed counters are copied as explicit grants. |
| failure | Unexpected stop reason, counter overrun, falsely complete status, or candidate outside the expected set fails the test. |
| cost | The matrix is bounded to one three-leaf shape and five named mapping limits with zero/one-short grants plus selected output/admission cases; it is not exhaustive over all inputs or all budget values. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0014

[Lines 196–219](../../../../../tests/unit/meta_candidates_test.cpp#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L196-L219:sha256:cf3a999ba89a04451985f6869588c97c7cb5e392d3f304d412a812f016afdedf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify existing C02/C05 selection behavior, plan-cache use, EXPLAIN reporting, provider ownership, and degenerate domains. |
| inputs / outputs | Uses a fully consumed finite provider with height_only and require_exhausted_family policies, checks PlanCache read/write and EXPLAIN JSON scope, moves the provider, then checks empty-body and nullary-occurrence inputs retain the ordinary proof but expose no meta provider. |
| invariants | The tests reuse existing policy interfaces; reported finite-proposal family scope and global_cost_complete=false are distinct, and moving the provider affects whether remaining prepared state can report exhaustion. |
| ownership | Fixture/proof/prepared/provider values are locally owned and moved explicitly where checked; cache is local test state. |
| failure | Policy, status, JSON, provider-move, or degenerate-domain mismatch fails the test. |
| cost | Finite policy and degenerate-input cases only; no independent performance, global-cost, or all-domain theorem is established. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0015

[Lines 220–220](../../../../../tests/unit/meta_candidates_test.cpp#L220); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L220-L220:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous test namespace. |
| inputs / outputs | Ends the namespace containing the test-only fixture and helper definitions. |
| invariants | No declaration is exported by this delimiter. |
| ownership | No runtime ownership or state. |
| failure | A delimiter error is a compile-time failure. |
| cost | No runtime cost. |
| Design | [tests/unit/meta_candidates_test.cpp](../../../../../tests/unit/meta_candidates_test.cpp) |

## B0016

[Lines 221–235](../../../../../tests/unit/meta_candidates_test.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L221-L235:sha256:2a71756ddcfd9650f29b3adb196e0f2d65c87eada7b5f8fde68c29a632656ffa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the fixed finite adapter, oracle, status, policy, and domain cases. |
| inputs / outputs | Executes 12 reference_case fixtures (chain and disconnected scopes with four heads each, plus equal, nested, nonhead-separator, and alias cases), then the four-leaf fiber, grant/status matrix, and policy/domain checks. |
| invariants | The 12 cases and targeted 26-shape oracle are concrete regression evidence only; successful test return does not prove all-input family completeness or global cost optimality. |
| ownership | Each helper owns its local test values; main returns a process status. |
| failure | Any helper assertion/exception makes the executable fail. |
| cost | Finite cases of explicitly listed sizes; costs include exact search and enumerations in those fixtures only. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp) |
