# `tests/unit/candidate_proposals_test.cpp` — block usage map

[Source](../../../../../tests/unit/candidate_proposals_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4d16d94cb3761441a9ec30f050f7b67c5f430b488502ee9a5ef4a46b79cb3197`. 317 lines partitioned into 35 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../tests/unit/candidate_proposals_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Deny only the new proposal-owner allocation, once; all other cases allocate · [reviewed contract](#b0001) |
| [B0002 · 24–28](../../../../../tests/unit/candidate_proposals_test.cpp#L24) | Callable definition: void* allocate(std::size_t bytes) | calls std::malloc; returns value; growth allocate, malloc · [reviewed contract](#b0002) |
| [B0003 · 29–29](../../../../../tests/unit/candidate_proposals_test.cpp#L29) | Closes surrounding scope/type. |  · [reviewed contract](#b0003) |
| [B0004 · 30–30](../../../../../tests/unit/candidate_proposals_test.cpp#L30) | Callable definition: void* operator new(std::size_t bytes) | calls allocation_probe::allocate; returns allocation_probe::allocate(bytes); growth allocate, new · [reviewed contract](#b0004) |
| [B0005 · 31–31](../../../../../tests/unit/candidate_proposals_test.cpp#L31) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns allocation_probe::allocate(bytes); growth allocate, new · [reviewed contract](#b0005) |
| [B0006 · 32–32](../../../../../tests/unit/candidate_proposals_test.cpp#L32) | Callable definition: void operator delete(void* value) noexcept | calls std::free · [reviewed contract](#b0006) |
| [B0007 · 33–33](../../../../../tests/unit/candidate_proposals_test.cpp#L33) | Callable definition: void operator delete\[\](void* value) noexcept | calls  · [reviewed contract](#b0007) |
| [B0008 · 34–34](../../../../../tests/unit/candidate_proposals_test.cpp#L34) | Callable definition: void operator delete(void* value, std::size_t) noexcept | calls std::free · [reviewed contract](#b0008) |
| [B0009 · 35–35](../../../../../tests/unit/candidate_proposals_test.cpp#L35) | Callable definition: void operator delete\[\](void* value, std::size_t) noexcept | calls  · [reviewed contract](#b0009) |
| [B0010 · 36–42](../../../../../tests/unit/candidate_proposals_test.cpp#L36) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 43–43](../../../../../tests/unit/candidate_proposals_test.cpp#L43) | Callable definition: void check(bool value, const char* message) | calls std::runtime_error; guard void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); } · [reviewed contract](#b0011) |
| [B0012 · 44–46](../../../../../tests/unit/candidate_proposals_test.cpp#L44) | Explanatory comments or spacing. | source comment (unverified): // Literal Boolean R(x),S(x,y),T(y) witnesses. Their supplied P06 optimum is · [reviewed contract](#b0012) |
| [B0013 · 47–51](../../../../../tests/unit/candidate_proposals_test.cpp#L47) | Callable definition: FreeConnexTree native_tree() | calls ; returns {NodeId{0}, {{@ , NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}, NodeId{2}}, 1, {}},; source comment (unverified): // Literal Boolean R(x),S(x,y),T(y) witnesses. Their supplied P06 optimum is · [reviewed contract](#b0013) |
| [B0014 · 52–57](../../../../../tests/unit/candidate_proposals_test.cpp#L52) | Callable definition: FreeConnexTree x_tree() | calls ; returns {NodeId{0}, {{@ , NodeKind::generalized, {VariableId{0}}, {NodeId{1}, NodeId{2}}, {}, {}}, · [reviewed contract](#b0014) |
| [B0015 · 58–63](../../../../../tests/unit/candidate_proposals_test.cpp#L58) | Callable definition: FreeConnexTree y_tree() | calls ; returns {NodeId{0}, {{@ , NodeKind::generalized, {VariableId{1}}, {NodeId{1}, NodeId{2}}, {}, {}}, · [reviewed contract](#b0015) |
| [B0016 · 64–68](../../../../../tests/unit/candidate_proposals_test.cpp#L64) | Callable definition: FreeConnexTree taller_tree() | calls ; returns {NodeId{0}, {{@ , NodeKind::native, {VariableId{0}}, {NodeId{1}}, 0, {}}, · [reviewed contract](#b0016) |
| [B0017 · 69–69](../../../../../tests/unit/candidate_proposals_test.cpp#L69) | Callable definition: std::vector&lt;FreeConnexTree&gt; minima() | calls x_tree, native_tree, y_tree; returns {x_tree(), native_tree(), y_tree()} · [reviewed contract](#b0017) |
| [B0018 · 70–75](../../../../../tests/unit/candidate_proposals_test.cpp#L70) | Callable definition: std::vector&lt;FreeConnexTree&gt; mixed_batch() | calls native_tree, push_back, x_tree, std::reverse; returns {std::move(invalid), taller_tree(), x_tree(), std::move(duplicate), native_tree(), y_tree()}; growth push_back; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 76–78](../../../../../tests/unit/candidate_proposals_test.cpp#L76) | Explanatory comments or spacing. | source comment (unverified): // Fail boundedly on a stalled fixture. A yielded prefix is never accepted as · [reviewed contract](#b0019) |
| [B0020 · 79–87](../../../../../tests/unit/candidate_proposals_test.cpp#L79) | Callable definition: void finish(CandidateProvider& owner, std::uint64_t quantum = 10000) | calls advance, check, std::runtime_error; guard check(stopped == CandidateStop::candidate_ready \|\| stopped == CandidateStop::quantum_work,; 1 loop sites; source comment (unverified): // Fail boundedly on a stalled fixture. A yielded prefix is never accepted as · [reviewed contract](#b0020) |
| [B0021 · 88–92](../../../../../tests/unit/candidate_proposals_test.cpp#L88) | Callable definition: MinimumHeightCandidate at(const CandidateSnapshot& snapshot, std::size_t index) | calls candidate, check, has_value; guard check(candidate.has_value(), "snapshot omitted a published proposal");; returns *candidate · [reviewed contract](#b0021) |
| [B0022 · 93–97](../../../../../tests/unit/candidate_proposals_test.cpp#L93) | Callable definition: std::vector&lt;std::string&gt; keys(const CandidateSnapshot& snapshot) | calls candidate_count, push_back, at, structural_key; returns out; growth push_back; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 98–102](../../../../../tests/unit/candidate_proposals_test.cpp#L98) | Callable definition: CandidateSnapshot admitted(const VerifiedOptimum& proof, std::vector&lt;FreeConnexTree&gt; trees, std::uint64_t quantum = 10000) | calls CandidateProvider::from_proposals, std::move, finish, snapshot; returns owner.snapshot() · [reviewed contract](#b0023) |
| [B0024 · 103–107](../../../../../tests/unit/candidate_proposals_test.cpp#L103) | Callable definition: template&lt;class Operation&gt; void rejects_binding(Operation operation) | calls operation, check, code, std::runtime_error; guard catch (const Error& error) { check(error.code() == "candidate_binding", "wrong cross-family rejecti… · [reviewed contract](#b0024) |
| [B0025 · 108–108](../../../../../tests/unit/candidate_proposals_test.cpp#L108) | Explanatory comments or spacing. |  |
| [B0026 · 109–140](../../../../../tests/unit/candidate_proposals_test.cpp#L109) | Callable definition: void empty_and_admission(const c02_test::Fixture& fixture, const VerifiedOptimum& proof) | calls CandidateProvider::from_proposals, check, progress, candidate_count; guard check(empty.progress().family == finite && !empty.progress().family_exhausted && empty.candidate_co…; 2 loop sites · [reviewed contract](#b0026) |
| [B0027 · 141–143](../../../../../tests/unit/candidate_proposals_test.cpp#L141) | Explanatory comments or spacing. | source comment (unverified): // Raising a grant must preserve consumed work and old handles, then resume · [reviewed contract](#b0027) |
| [B0028 · 144–152](../../../../../tests/unit/candidate_proposals_test.cpp#L144) | Callable definition: void resume(CandidateProvider& owner, CandidateLimits limits, const std::vector&lt;std::string&gt;& expected) | calls progress, check, raise_limits, finish; guard check(!before.family_exhausted && owner.raise_limits(limits) == LimitChange::applied, "proposal gra…; source comment (unverified): // Raising a grant must preserve consumed work and old handles, then resume · [reviewed contract](#b0028) |
| [B0029 · 153–207](../../../../../tests/unit/candidate_proposals_test.cpp#L153) | Callable definition: void stops_and_retry(const VerifiedOptimum& proof) | calls keys, admitted, minima, CandidateProvider::from_proposals; guard check(inert.advance({0, {}}).stopped_for == CandidateStop::quantum_work && · [reviewed contract](#b0029) |
| [B0030 · 208–208](../../../../../tests/unit/candidate_proposals_test.cpp#L208) | Explanatory comments or spacing. |  |
| [B0031 · 209–289](../../../../../tests/unit/candidate_proposals_test.cpp#L209) | Callable definition: void ranking_cache_and_reports(const CandidateSnapshot& exact, io::Json* reports) | calls original_proof, candidate_count, push_back, at; guard check(keys(supplied) == keys(exact) && supplied.family_exhausted() && exact.family_exhausted(),; growth push_back; 1 loop sites; source comment (unverified): // Identical raw trees/order/completion isolate the family dimension of the · [reviewed contract](#b0031) |
| [B0032 · 290–290](../../../../../tests/unit/candidate_proposals_test.cpp#L290) | Explanatory comments or spacing. |  |
| [B0033 · 291–301](../../../../../tests/unit/candidate_proposals_test.cpp#L291) | Callable definition: void retained_lifetime() | calls c02_test::fixture, c02_test::candidates, admitted, original_proof; guard check(held.family() == finite && held.candidate_count() == 2 && held.original_proof().valid() &&; returns admitted(exact.original_proof(), {x_tree(), native_tree()}); source comment (unverified): // All source/proof/provider locals die before the returned snapshot is used. · [reviewed contract](#b0033) |
| [B0034 · 302–303](../../../../../tests/unit/candidate_proposals_test.cpp#L302) | Closes surrounding scope/type. |  · [reviewed contract](#b0034) |
| [B0035 · 304–317](../../../../../tests/unit/candidate_proposals_test.cpp#L304) | Callable definition: int main(int argc, char** argv) | calls std::string_view, check, io::Json::array, c02_test::fixture; guard check(argc == 1 \|\| emit, "usage: candidate_proposals_test \[--emit\]");; returns 1 · [reviewed contract](#b0035) |

## B0001

[Lines 1–23](../../../../../tests/unit/candidate_proposals_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L23:sha256:0b98b0a9965e63396bad0ddb98af9904f81dfd27783d85ed03c0fdc6cf8142ec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare dependencies and process-local one-shot allocation probe. |
| inputs / outputs | Typed planner/selection/report fixture APIs and standard allocation types become available. |
| invariants | The flag is used by this single-threaded test process only. |
| ownership | Includes create no runtime owner; flag has process storage. |
| failure | Compilation diagnoses missing declarations. |
| cost | Compile-time imports plus one scalar flag; no production instrumentation. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0002

[Lines 24–28](../../../../../tests/unit/candidate_proposals_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L28:sha256:894aea35d71b27bcb0b0afcc0f050b9614fb4853152b9d54a55322e016285d6e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject one allocation failure at the new proposal-owner boundary. |
| inputs / outputs | Byte request and one-shot flag in; malloc-owned storage out. |
| invariants | Clear the denial flag before throwing; assertions and cleanup must still allocate. |
| ownership | Caller/operator delete frees successful storage. |
| failure | The requested cut throws bad_alloc; malloc exhaustion also throws. |
| cost | One malloc or one immediate throw; process-local test probe only. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0003

[Lines 29–29](../../../../../tests/unit/candidate_proposals_test.cpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L29:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the preceding test helper namespace. |
| inputs / outputs | No input or result. |
| invariants | Helpers retain translation-unit scope; this delimiter adds no behavior. |
| ownership | Creates no ownership. |
| failure | Cannot fail independently. |
| cost | No runtime work. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0004

[Lines 30–30](../../../../../tests/unit/candidate_proposals_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L30:sha256:c39abbf733920e3184e4aff0efbfff6217fd69138ed850833de6f41a38a500c2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route test allocations through the one-shot failure probe. |
| inputs / outputs | Byte count in; malloc-backed storage out. |
| invariants | Both ordinary and array new use the same reset-before-throw probe. |
| ownership | Matching delete frees successful storage. |
| failure | bad_alloc from the probe propagates. |
| cost | One call to the test allocation helper; process-local only. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0005

[Lines 31–31](../../../../../tests/unit/candidate_proposals_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L31:sha256:3f9783e06e15790e43476627c8baa89d89bdde9cdd996ab76dbac2c5444807e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route test allocations through the one-shot failure probe. |
| inputs / outputs | Byte count in; malloc-backed storage out. |
| invariants | Both ordinary and array new use the same reset-before-throw probe. |
| ownership | Matching delete frees successful storage. |
| failure | bad_alloc from the probe propagates. |
| cost | One call to the test allocation helper; process-local only. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0006

[Lines 32–32](../../../../../tests/unit/candidate_proposals_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L32:sha256:f3c9baac6c0a7f8584026aa2bf26666aa800c36992328910d20b8b27292f4a28
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release malloc-backed storage used by the test allocator. |
| inputs / outputs | Ordinary/array and sized delete pointer in; no result. |
| invariants | Free exactly the successful malloc result; null is permitted. |
| ownership | Consumes this storage; owns no engine state. |
| failure | noexcept free performs no diagnostic allocation. |
| cost | One C-library free; allocator cost is separate from logical provider work. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0007

[Lines 33–33](../../../../../tests/unit/candidate_proposals_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L33:sha256:5f4d811db81d56376c5fa880544e0a09e4f87b0594d8c96868f5ded525a129d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release malloc-backed storage used by the test allocator. |
| inputs / outputs | Ordinary/array and sized delete pointer in; no result. |
| invariants | Free exactly the successful malloc result; null is permitted. |
| ownership | Consumes this storage; owns no engine state. |
| failure | noexcept free performs no diagnostic allocation. |
| cost | One C-library free; allocator cost is separate from logical provider work. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0008

[Lines 34–34](../../../../../tests/unit/candidate_proposals_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L34:sha256:114a1fa4dc06af569385e38cdb9978c06745d4fa555c768f8b0f885d40f7887a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release malloc-backed storage used by the test allocator. |
| inputs / outputs | Ordinary/array and sized delete pointer in; no result. |
| invariants | Free exactly the successful malloc result; null is permitted. |
| ownership | Consumes this storage; owns no engine state. |
| failure | noexcept free performs no diagnostic allocation. |
| cost | One C-library free; allocator cost is separate from logical provider work. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0009

[Lines 35–35](../../../../../tests/unit/candidate_proposals_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L35:sha256:bda4fbb3ce3999f5dbfdfb6c52be347a2601355fed85b3907ea6ff358ce8f072
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release malloc-backed storage used by the test allocator. |
| inputs / outputs | Ordinary/array and sized delete pointer in; no result. |
| invariants | Free exactly the successful malloc result; null is permitted. |
| ownership | Consumes this storage; owns no engine state. |
| failure | noexcept free performs no diagnostic allocation. |
| cost | One C-library free; allocator cost is separate from logical provider work. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0010

[Lines 36–42](../../../../../tests/unit/candidate_proposals_test.cpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L42:sha256:40ab048f12af3ef445d5e2d22857c43756ed6d603ca26825a29c74856a0d7c2d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name test-local APIs and finite-family constant. |
| inputs / outputs | Planner and selection aliases in; local shorthand out. |
| invariants | The family constant identifies only supplied finite proposals. |
| ownership | Aliases and constexpr value own no payload. |
| failure | Compile-time declaration errors only. |
| cost | No runtime traversal or allocation. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0011

[Lines 43–43](../../../../../tests/unit/candidate_proposals_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L43:sha256:f395e8cd23a700a3d5398f556f3cb4d35433fe0f8e3d56141ef475440be016f5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep every proposal regression assertion active in Release. |
| inputs / outputs | Boolean and literal diagnostic in; return only on true. |
| invariants | NDEBUG does not disable this helper. |
| ownership | Borrows diagnostic; owns no retained engine state. |
| failure | False throws runtime_error and fails this test process. |
| cost | Constant predicate check; diagnostic allocation occurs on failure. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0012

[Lines 44–46](../../../../../tests/unit/candidate_proposals_test.cpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L46:sha256:4eefc265d76826ab83cd15bd0926a15d53aa5fd46ffce52265ba6c60c800705d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent literal fixture or bounded regression contract. |
| inputs / outputs | Human reader uses the neighboring callable and the stated boundary. |
| invariants | Comments grant no checked authority or formal correctness proof. |
| ownership | No executable owner or lifetime. |
| failure | No runtime failure. |
| cost | No runtime work. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0013

[Lines 47–51](../../../../../tests/unit/candidate_proposals_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L51:sha256:c13e68675327323c54e1c4aac79fafd57039e8673b09f8d52eaac014ee2d4085
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a literal native minimum-height upper control. |
| inputs / outputs | No input; R(x),S(x,y),T(y) with S as root out. |
| invariants | Occurrence indices and scopes are fixed independently of the provider. |
| ownership | Returns an owning mutable draft. |
| failure | Ordinary construction allocation can fail. |
| cost | Fixed small vector/set construction outside advance grants. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0014

[Lines 52–57](../../../../../tests/unit/candidate_proposals_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L57:sha256:1a99af63a141eb77d52cc37e4794c7af0eba57efe6aa0e593fd8ff7ace550212
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a literal generalized x-root alternative. |
| inputs / outputs | No input; generalized{x} with correctly guarded R and S branches out. |
| invariants | All original occurrences occur once; the supplied proof supplies the lower bound. |
| ownership | Returns an owning draft. |
| failure | Ordinary construction allocation can fail. |
| cost | Fixed four-node test construction. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0015

[Lines 58–63](../../../../../tests/unit/candidate_proposals_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L63:sha256:59ee155e4f01f142aab92495372c37597e798dddda5c526e716bc99be2cde22c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the symmetric generalized y-root alternative. |
| inputs / outputs | No input; generalized{y} with T and S branches out. |
| invariants | Occurrence IDs differ from display names; native height must be checked separately. |
| ownership | Returns an owning draft. |
| failure | Ordinary construction allocation can fail. |
| cost | Fixed four-node test construction. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0016

[Lines 64–68](../../../../../tests/unit/candidate_proposals_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L68:sha256:758be547364bbf153f6a06410ca2ab1e1d1c4602f9d3307805ce12080f81277b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a valid tree filtered only by the proved-height gate. |
| inputs / outputs | No input; R-S-T native chain out. |
| invariants | P02 must accept this height3 control while genuine proof height is2. |
| ownership | Returns an owning draft. |
| failure | Construction allocation can fail. |
| cost | Fixed three-node test construction. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0017

[Lines 69–69](../../../../../tests/unit/candidate_proposals_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L69:sha256:1fbaf1f563dd584ef1ebe48360a9a6e29b008bb249c3074bd0ce6ed8ab51c396
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble three independently written minimum-height proposals. |
| inputs / outputs | No input; ordered x/native/y drafts out. |
| invariants | Does not manufacture a checked candidate or original proof. |
| ownership | Owns returned trees. |
| failure | Construction allocation can fail. |
| cost | Fixed small fixture cost, outside provider grants. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0018

[Lines 70–75](../../../../../tests/unit/candidate_proposals_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L75:sha256:0356ff6dad76a579462e1eca9a4031c826c303434ff686efb399c114dbe415a6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise distinct rejection, height and dedup gates in input order. |
| inputs / outputs | Literal trees in; invalid, taller, x, renamed/reordered duplicate, native, y out. |
| invariants | Display IDs and child order must not change full structural identity. |
| ownership | Returned vector owns all drafts. |
| failure | Fixture construction allocation can fail. |
| cost | Fixed fixture construction; includes one child-order reversal per duplicate node. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0019

[Lines 76–78](../../../../../tests/unit/candidate_proposals_test.cpp#L76); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L76-L78:sha256:47645b4f0d80927672b0551e89bf48e109ae74708cfbb30740f7d80a304f918d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent literal fixture or bounded regression contract. |
| inputs / outputs | Human reader uses the neighboring callable and the stated boundary. |
| invariants | Comments grant no checked authority or formal correctness proof. |
| ownership | No executable owner or lifetime. |
| failure | No runtime failure. |
| cost | No runtime work. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0020

[Lines 79–87](../../../../../tests/unit/candidate_proposals_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L87:sha256:1cba80c00583dfdce1d0b573b996e0474470a9d696720cca3ada6bb24c43af57
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive a finite provider to actual exhaustion with a bounded fixture loop. |
| inputs / outputs | Exclusive owner and quantum in; returns only at exhausted. |
| invariants | candidate_ready and quantum_work are intermediate; neither proves family completion. |
| ownership | Mutates only the passed provider. |
| failure | Unexpected stop or 100000 iterations fails the fixture. |
| cost | At most100000 advance calls; no benchmark or production deadline claim. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0021

[Lines 88–92](../../../../../tests/unit/candidate_proposals_test.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L88-L92:sha256:19de624ba23da1594ab6ad47d90ef93e7a59fa64395601c91ee34e3d39b3999b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require and own one published candidate from a snapshot. |
| inputs / outputs | Snapshot and index in; copied candidate handle out. |
| invariants | Missing publication is a test failure. |
| ownership | Handle shares immutable payload; no borrowed vector element escapes. |
| failure | Missing index throws through check. |
| cost | Constant indexed lookup and shared-owner copy. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0022

[Lines 93–97](../../../../../tests/unit/candidate_proposals_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L93-L97:sha256:73af159a8765672abe132799cd0fd42a6c513264fb1392c282b4b6437207ec25
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe the ordered full structural identities of a retained prefix. |
| inputs / outputs | Snapshot in; owning key-byte copies out. |
| invariants | Use full bytes rather than display labels or digests. |
| ownership | Returned vector owns copies; snapshot remains unchanged. |
| failure | Missing candidate or allocation fails the fixture. |
| cost | Linear in candidate count plus copied key widths. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0023

[Lines 98–102](../../../../../tests/unit/candidate_proposals_test.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L98-L102:sha256:1f8d71c0a9191a321f1953dde9a95297a629437edce5b1d32099c4c8077e1504
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create and fully consume one unchecked finite proposal batch. |
| inputs / outputs | Genuine original proof, owning drafts and quantum in; owning completed snapshot out. |
| invariants | All authority is supplied by the original proof and real admission gates. |
| ownership | Provider owns drafts; returned snapshot outlives provider. |
| failure | Unexpected stops, bounded-loop failure or admission allocation propagate. |
| cost | Cold fixture construction plus budgeted advance and allocating snapshot copy. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0024

[Lines 103–107](../../../../../tests/unit/candidate_proposals_test.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L107:sha256:b23f9bcb55484ef6a246960089720dde5e15ae33b7523139730a1b7ac068fa52
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact rejection of unsupported cross-family reuse. |
| inputs / outputs | Operation in; returns only after candidate_binding. |
| invariants | Another error code does not satisfy the negative control. |
| ownership | Borrows operation for one call. |
| failure | Accepted operation or wrong error fails the test. |
| cost | One cold cache/factory call and exception inspection. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0026

[Lines 109–140](../../../../../tests/unit/candidate_proposals_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L109-L140:sha256:5c0c5d41f12f12cab7c06ba79ecf69d5bc4ba2a060fdf090341c8ed87a75cfbc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check batch-only exhaustion and independent validation/height/dedup ordering. |
| inputs / outputs | Real fixture and original proof in; assertions over published artifacts. |
| invariants | Empty input adds no seed; six drafts yield exactly three distinct minima at positions2,4,5; sliced grants preserve results. |
| ownership | Local providers and immutable snapshots own their state. |
| failure | Unexpected count, provenance, binding, proof or gate result fails the test. |
| cost | Finite small batch twice, one single-step run; full proof/report serialization is outside grants. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0027

[Lines 141–143](../../../../../tests/unit/candidate_proposals_test.cpp#L141); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L141-L143:sha256:6d8acb25cc057ea860db19b924eda5b485264505a2468a157274655ad91a93e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent literal fixture or bounded regression contract. |
| inputs / outputs | Human reader uses the neighboring callable and the stated boundary. |
| invariants | Comments grant no checked authority or formal correctness proof. |
| ownership | No executable owner or lifetime. |
| failure | No runtime failure. |
| cost | No runtime work. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0028

[Lines 144–152](../../../../../tests/unit/candidate_proposals_test.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L144-L152:sha256:d18de8800786195f8ca2665665997f615d41620354079842a5524528dc3f44d0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check monotone resource extension without cursor or consumed-work reset. |
| inputs / outputs | Stopped owner, larger limits and expected full keys in; complete owner out. |
| invariants | Old work/content/count survive raising limits; exhaustion requires all expected proposals. |
| ownership | Mutates same exclusive owner; expected keys borrowed. |
| failure | Rejected extension, changed counters or results fail the test. |
| cost | Constant progress snapshots followed by finite batch completion/key copies. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0029

[Lines 153–207](../../../../../tests/unit/candidate_proposals_test.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L153-L207:sha256:6d3e1c3e2fe06972746904a8cbf80364bd03d313b4c4d214e6692d663b6afef2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check grant boundaries, saved drafts, cancellation and allocation retry. |
| inputs / outputs | Real original proof in; assertions over independently stopped owners. |
| invariants | Zero grants are inert; work/record/cell/candidate caps resume the same input; one denied first-owner allocation loses no proposal. |
| ownership | Older handles/snapshots must survive continuation and cancel; unpublished inputs release. |
| failure | Any unexpected stop, counter, retry, family policy or lifetime fails this test. |
| cost | Several fixed small runs plus one deliberate allocation denial; no exhaustive fault-sweep claim. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0031

[Lines 209–289](../../../../../tests/unit/candidate_proposals_test.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L209-L289:sha256:e228d72386fec5e3709e6dfa5c739cc96b89b487f65cd48dd9754a80c7a70100
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check finite-family identity through ranking, selection, caches and both report formats. |
| inputs / outputs | Complete original family and optional report sink in; assertions and five actual reports out. |
| invariants | Identical raw trees isolate the family cache key; original CandidateCache rejects finite batches; EXPLAIN family/source cannot disagree. |
| ownership | Local selection/cache/report owners retain immutable inputs; optional sink owns emitted JSON. |
| failure | Wrong cache hit, selection, report or explain_family result fails the test; serialization allocation propagates. |
| cost | Cold small-family ranking/cache passes and full JSON/text serialization; no runtime update overhead or global cost claim. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0033

[Lines 291–301](../../../../../tests/unit/candidate_proposals_test.cpp#L291); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L291-L301:sha256:69e509790fbc86a9812b850137c4920630d9eacc8c4e99c3f1650a59f64cfb8c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a finite snapshot owns all source/proof/tree dependencies. |
| inputs / outputs | No input; assertions after producing locals have died. |
| invariants | Using and serializing the snapshot must not borrow destroyed provider or batch storage. |
| ownership | Only the returned snapshot survives its producing scope. |
| failure | Lost binding/tree/proof data or serialization failure fails the test. |
| cost | One fixed batch and full snapshot serialization. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0034

[Lines 302–303](../../../../../tests/unit/candidate_proposals_test.cpp#L302); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L302-L303:sha256:938de74be97bf3aba7872a61ba0e42084008c81e8a202a612134c755aaf7fa06
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the preceding test helper namespace. |
| inputs / outputs | No input or result. |
| invariants | Helpers retain translation-unit scope; this delimiter adds no behavior. |
| ownership | Creates no ownership. |
| failure | Cannot fail independently. |
| cost | No runtime work. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0035

[Lines 304–317](../../../../../tests/unit/candidate_proposals_test.cpp#L304); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L304-L317:sha256:8a7b286c2466f77018aab1ea5bc78449f3a9d89aee67304895570645334c60f1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run proposal regressions and optionally emit actual typed schema fixtures. |
| inputs / outputs | Optional --emit argument in; success status and summary or JSON array out. |
| invariants | All checks run in both modes; emitted data comes from real typed artifacts. |
| ownership | Process-local fixture owners clean up normally. |
| failure | Top-level exception prints one diagnostic and returns1; invalid arguments fail. |
| cost | Finite regression driver; no production execution hook. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |
