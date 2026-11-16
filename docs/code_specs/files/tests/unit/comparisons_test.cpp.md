# `tests/unit/comparisons_test.cpp` — block usage map

[Source](../../../../../tests/unit/comparisons_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `43f596b120def7467a1d024f4673ba3776ec04c5c6f344fa2504819b6b2fa6b0`. 255 lines partitioned into 25 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/unit/comparisons_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 18–21](../../../../../tests/unit/comparisons_test.cpp#L18) | Callable definition: void check(bool condition, const char* message) | calls std::runtime_error; guard void check(bool condition, const char* message) { · [reviewed contract](#b0002) |
| [B0003 · 22–30](../../../../../tests/unit/comparisons_test.cpp#L22) | Callable definition: template&lt;class Function&gt; void refusal(Function action, std::string_view code = {}) | calls action, check, empty, code; guard catch (const Error& e) { failed = true; check(code.empty() \|\| e.code() == code, "wrong refusal cate… · [reviewed contract](#b0003) |
| [B0004 · 31–33](../../../../../tests/unit/comparisons_test.cpp#L31) | Callable definition: Row ints(std::initializer_list&lt;std::int64_t&gt; input) | calls emplace_back; returns out; growth emplace_back; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 34–39](../../../../../tests/unit/comparisons_test.cpp#L34) | Callable definition: template&lt;class Range&gt; Relation rows(const Range& input) | calls check, insert, storage::export_row, values; guard check(out.insert(storage::export_row(tuple.values())).second, "duplicate output escaped");; returns out; growth insert; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 40–40](../../../../../tests/unit/comparisons_test.cpp#L40) | Type/record definition: struct Fixture |  · [reviewed contract](#b0006) |
| [B0007 · 41–54](../../../../../tests/unit/comparisons_test.cpp#L41) | Callable definition: Fixture path(std::vector&lt;std::size_t&gt; head = {0}, bool self_join = false) | calls push_back, std::to_string, size; returns f; growth push_back; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 55–57](../../../../../tests/unit/comparisons_test.cpp#L55) | Callable definition: PhysicalPlan lower(const Fixture& f, bool indexed) | calls planner::lower_tree, s04_runtime::options; returns planner::lower_tree(f.catalog,f.query,f.tree,indexed?s04_runtime::options():PhysicalOptions{}) · [reviewed contract](#b0008) |
| [B0009 · 58–60](../../../../../tests/unit/comparisons_test.cpp#L58) | Callable definition: pc::Predicate predicate(pc::Operator operation = pc::Operator::less) | calls ; returns {VariableId{0},operation,VariableId{2}} · [reviewed contract](#b0009) |
| [B0010 · 61–62](../../../../../tests/unit/comparisons_test.cpp#L61) | Explanatory comments or spacing. | source comment (unverified): // This slow definition uses original full-state joins with ALL variables in · [reviewed contract](#b0010) |
| [B0011 · 63–88](../../../../../tests/unit/comparisons_test.cpp#L63) | Callable definition: Relation expected(const Fixture& f, const Database& database, std::span&lt;const pc::Predicate&gt; predicates) | calls clear, size, push_back, std::to_string; returns assignment.at(id-&gt;value); std::get&lt;Value&gt;(operand); growth insert, push_back; 4 loop sites; source comment (unverified): // This slow definition uses original full-state joins with ALL variables in · [reviewed contract](#b0011) |
| [B0012 · 89–94](../../../../../tests/unit/comparisons_test.cpp#L89) | declares types or opens a type body. |  · [reviewed contract](#b0012) |
| [B0013 · 95–98](../../../../../tests/unit/comparisons_test.cpp#L95) | Callable definition: Trial(Fixture f, std::vector&lt;pc::Predicate&gt; p, bool indexed, rt::Options options = {}) :original(std::move(f)),predicates(std::mo… | calls original, std::move, predicates, selected · [reviewed contract](#b0013) |
| [B0014 · 99–108](../../../../../tests/unit/comparisons_test.cpp#L99) | Callable definition: void verify() | calls check, ready, sequence, source_snapshot; guard check(owner.ready(),"comparison owner stayed busy"); · [reviewed contract](#b0014) |
| [B0015 · 109–121](../../../../../tests/unit/comparisons_test.cpp#L109) | Callable definition: rt::Epoch apply(std::size_t table, SetOperation operation, Row values) | calls expected, database, sequence, std::move; guard check(rows(epoch.added)==added && rows(epoch.removed)==removed,"endpoint delta differs");; returns epoch · [reviewed contract](#b0015) |
| [B0016 · 122–122](../../../../../tests/unit/comparisons_test.cpp#L122) | Closes surrounding scope/type. |  · [reviewed contract](#b0016) |
| [B0017 · 123–134](../../../../../tests/unit/comparisons_test.cpp#L123) | Callable definition: void admission() | calls path, lower, predicate, pc::admit; guard check(plan.predicates().front().operation==pc::Operator::less,"admission retained mutable caller pr… · [reviewed contract](#b0017) |
| [B0018 · 135–159](../../../../../tests/unit/comparisons_test.cpp#L135) | Callable definition: void semantics(bool indexed) | calls random, t, path, predicate; guard check(!event.metrics.recomputed,"unused source caused unnecessary recomputation");; growth insert; 2 loop sites · [reviewed contract](#b0018) |
| [B0019 · 160–180](../../../../../tests/unit/comparisons_test.cpp#L160) | Callable definition: void typed(bool indexed) | calls t, front, apply, one; growth insert; 5 loop sites · [reviewed contract](#b0019) |
| [B0020 · 181–191](../../../../../tests/unit/comparisons_test.cpp#L181) | Callable definition: void constants(bool indexed) | calls t, check, has_answer, apply; guard check(t.owner.has_answer()==truth,"constant comparison initial result differs");; growth insert; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 192–215](../../../../../tests/unit/comparisons_test.cpp#L192) | Callable definition: void constraints_and_limits(bool indexed) | calls path, push_back, constrained, predicate; growth insert, push_back; 1 loop sites; source comment (unverified): // Empty joins fit this one cumulative producer allowance; the after-state · [reviewed contract](#b0021) |
| [B0022 · 216–240](../../../../../tests/unit/comparisons_test.cpp#L216) | Callable definition: void allocation_cuts(bool indexed, bool deletion) | calls path, predicate, apply, ints; guard check(allocations&gt;0,"allocation cut control observed no allocations");; returns t; PhysicalSetUpdate{t.owner.sequence()+1,TableId{deletion?1U:0U},deletion?SetOperation::erase:SetO…; growth insert, make_unique; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 241–247](../../../../../tests/unit/comparisons_test.cpp#L241) | Callable definition: void retained() | calls t, path, predicate, apply; guard check(rows(snapshot.rows)==Relation{ints({1})},"owning comparison snapshot did not survive runtime …; returns t.owner.snapshot(); growth insert · [reviewed contract](#b0023) |
| [B0024 · 248–248](../../../../../tests/unit/comparisons_test.cpp#L248) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0024) |
| [B0025 · 249–255](../../../../../tests/unit/comparisons_test.cpp#L249) | Callable definition: int main() | calls admission, retained, semantics, typed; returns 0; 1; 1 loop sites · [reviewed contract](#b0025) |

## B0001

[Lines 1–17](../../../../../tests/unit/comparisons_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:7f0be8169616e10f1e14b9eeeaca9f42693550fd122a1010e05688c24edc7522
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the real comparison owner, equality admission and independent A04/failure support. |
| inputs / outputs | Header declarations, local aliases and the successful-check counter. |
| invariants | Production comparison implementation is linked, while allocation injection and A04 are test-only dependencies. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Compile-time declarations and fixed counter storage. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0002

[Lines 18–21](../../../../../tests/unit/comparisons_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L21:sha256:a595360a7bac6b7cb2bed8c74d9ee189e9b9c287073c55ee0599b6d03d9e4684
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce a test condition independently of NDEBUG. |
| inputs / outputs | Boolean and static message become one counted success or a runtime_error. |
| invariants | A false check terminates the test through its process boundary; production state is untouched. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | One branch and counter increment; exception construction only on failure. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0003

[Lines 22–30](../../../../../tests/unit/comparisons_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L30:sha256:dc8f24af7d62ed68ef1b1eb3b0a11a7165b48128647ee198f743c61081e1a042
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify an operation refuses with the expected diagnostic domain. |
| inputs / outputs | A callable and optional code are run once; recognized native/resource failures must occur. |
| invariants | A code expectation cannot silently accept another native category. This helper belongs only to tests and is not a runtime retry policy. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | One invocation plus diagnostic comparisons and assertion work. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0004

[Lines 31–33](../../../../../tests/unit/comparisons_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L33:sha256:12ca1398ac5475d22a1b466f52fc534b8ceca0c2f45004cfb38adff3366afa84
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct exact integer source rows for fixtures. |
| inputs / outputs | An initializer list of int64 values becomes an owning ordinary Row. |
| invariants | No floating conversion or comparison runtime helper supplies values. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Linear in row width with ordinary vector allocation. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0005

[Lines 34–39](../../../../../tests/unit/comparisons_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L39:sha256:d09bc7d565e7cbe391722b51085f54a82e45c0bdd302905833a12762aec0a53d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export and check distinct native endpoint/snapshot tuples. |
| inputs / outputs | A tuple range becomes an ordinary reference Relation; duplicate insertion fails the test. |
| invariants | Returned DTO rows are separate from native ownership; every input must appear exactly once. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Full output scalar export plus ordered set insertion and payload copies. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0006

[Lines 40–40](../../../../../tests/unit/comparisons_test.cpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L40:sha256:8be265d7845074be89e5d7b4d7b9fe24f4739be76340081d2e5ce2b79523b631
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the original catalog, equality query and proposed tree as test data. |
| inputs / outputs | Fixture fields hold caller/compiler DTOs. |
| invariants | A fixture is not a checked plan or minimum-height certificate. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Storage follows fixture metadata at construction. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0007

[Lines 41–54](../../../../../tests/unit/comparisons_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L54:sha256:d2a01aa4a748ca580dd5862033b3742dd711ab5c2d07dec1c8480ee7a0df31ed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a two-atom equality path with optional physical self-join. |
| inputs / outputs | Ordered head variable IDs and alias mode produce R(x,y),S(y,z) or two R aliases and an unused source. |
| invariants | Both atoms retain full scopes and separate occurrence IDs. Root children occupy TreeNode.children, and claimed separators stay absent. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Fixed small metadata construction plus head-width string/vector work. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0008

[Lines 55–57](../../../../../tests/unit/comparisons_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L57:sha256:b846ab10d5e2fd400bfa841cb18aadec0fee8ba96b9491a7950972bf34e7b894
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the original fixture under an explicit backend. |
| inputs / outputs | Original DTOs and indexed flag produce a genuinely checked PhysicalPlan. |
| invariants | Reference and finite indexed options use the same original query/tree; comparison admission comes later. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Existing cold validation, lowering, identity and metadata allocation costs. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0009

[Lines 58–60](../../../../../tests/unit/comparisons_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L60:sha256:b2676c7213e3a9ddbf34236e2bc5f7e9fe0d052d711c11e6167d4d0d858c09e1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the standard cross-occurrence comparison fixture. |
| inputs / outputs | One selected operator produces x op z. |
| invariants | The predicate remains a separate comparison DTO; y remains the equality separator. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Fixed inline descriptor construction. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0010

[Lines 61–62](../../../../../tests/unit/comparisons_test.cpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L62:sha256:e5f8eab2a95b3d1fa581630297df86b02759c94ace6f6341f4508e7221b4ca9b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the independent oracle ordering requirement. |
| inputs / outputs | The adjacent note explains why A04 must expose all variables before comparison filtering. |
| invariants | Filtering already projected outputs could lose hidden comparands or witnesses; the note asserts no native execution result. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | No executable work. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0011

[Lines 63–88](../../../../../tests/unit/comparisons_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L88:sha256:df7accc16713711629181236468357c7247f23808a0ecd0478863e1630ca5d14
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the original full-state CQ and comparison conjunction before projection. |
| inputs / outputs | Original catalog/query/database and predicate DTOs produce an exact ordinary answer set. |
| invariants | A04 gets a head containing all variable IDs. Test-side Value ordering applies the six relations, then the original ordered/repeated head is projected and deduplicated. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Full original join evaluation plus predicate tests, head copies and ordered distinct insertion; deliberately slow oracle work. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0012

[Lines 89–94](../../../../../tests/unit/comparisons_test.cpp#L89); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L94:sha256:2ab57e177cd82413560885ab92297a4df1791bd57eaaecc5e5b8b03f9431c0f5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own independent original metadata, selected plan, native runtime and reference session. |
| inputs / outputs | Trial groups each comparison predicate set with its own native and A04 owners. |
| invariants | Native retained state is not shared with the reference database or other Trials. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Storage includes both full test models and one finite native owner. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0013

[Lines 95–98](../../../../../tests/unit/comparisons_test.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L95-L98:sha256:5b6895e3b01326ecff2137074382be509885a105527aaf59ec6af8c20f17e7a2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a comparison trial from genuine original lowering. |
| inputs / outputs | Fixture, predicates, backend and optional runtime options create empty native and original reference owners, then verify them. |
| invariants | The copied original/predicates survive separately from immutable admission and runtime binding. Initial constant answers are checked immediately. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Cold original lowering/admission/import plus initial native construction and full oracle verification. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0014

[Lines 99–108](../../../../../tests/unit/comparisons_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L108:sha256:1f01ec1fb51a71586acae24c75acceaa32242956004c9eac414b9173d441db4c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one committed epoch against the original predicate-aware definition. |
| inputs / outputs | Native source/snapshot/sequence/existence are compared to the reference database and expected(). |
| invariants | The owner must be ready; full source state, comparison result and sequence must agree. Source exports and expected recomputation are test-only materializations. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Full source/output export and A04 join/filter work, not a maintenance benchmark. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0015

[Lines 109–121](../../../../../tests/unit/comparisons_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L109-L121:sha256:ddecc76a321350cc004c3cc0e39083e7d14d5b4d2d13d09559513aafaf85dc7a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact added/removed sets for one original physical update. |
| inputs / outputs | The reference update and native update are applied once; sorted set differences define expected endpoint deltas. |
| invariants | Hidden witness changes retract an output only when final projected membership changes. Physical membership flags and every post-state are verified independently. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Two full predicate-aware reference evaluations, endpoint set differences and one native update/verification. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0016

[Lines 122–122](../../../../../tests/unit/comparisons_test.cpp#L122); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L122-L122:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the Trial helper type. |
| inputs / outputs | The scope terminator ends its fields and methods. |
| invariants | This line creates no mutation, recovery or runtime proof. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | No executable work. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0017

[Lines 123–134](../../../../../tests/unit/comparisons_test.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L123-L134:sha256:f4452d4820b3674642138eb705b1b6e2e9930157bb6a7cebd30a418e9764c8a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise typed admission, immutable copies and equality-route exclusion. |
| inputs / outputs | Valid and malformed predicates, a zero work grant and explicitly quoted R/S SQL drive admission checks. |
| invariants | The original physical identity is unchanged. Unknown variables, heterotypes and invalid enum values refuse; SQL must classify cross-relation residuals as unsupported rather than pass equality admission. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Finite cold construction and negative admission calls only. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0018

[Lines 135–159](../../../../../tests/unit/comparisons_test.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L159:sha256:d5b83aa9fd38a1a4febdb43eda7ae2bb18269b8af04c8aafb0ef7840f31cd777
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify all six operators, self-join fanout and hidden last witnesses through updates. |
| inputs / outputs | Seeded insert/erase traces, repeated heads, unused sources and Boolean self-alias cases are checked on either backend. |
| invariants | Every prefix and endpoint delta matches A04 filtering before projection; duplicate/unused events skip unnecessary recomputation, and only last matching witnesses retract membership. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Hundreds of small native/oracle updates plus full snapshot/export checks; no throughput claim. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0019

[Lines 160–180](../../../../../tests/unit/comparisons_test.cpp#L160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L160-L180:sha256:bdc3a7488bac418aec09a50728e1ed6e7a774ac0fbcd05efa06e5f4f2415b80a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test exact typed relation and constant comparisons at value boundaries. |
| inputs / outputs | Int64 extrema, NUL/UTF8 strings, Boolean, finite date endpoints and large exact decimals are inserted and deleted for every operator. |
| invariants | Both operands have the declared same ScalarType. Decimal comparisons never convert to floating point, and constant conjunctions participate before projection. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Cartesian value-pair fixtures times six operators and two directions; finite original/reference/native comparisons. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0020

[Lines 181–191](../../../../../tests/unit/comparisons_test.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L181-L191:sha256:ae563c56e358367e44d23cad0323e1c15126e2dd1c6f59e506791ffd20d85976
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check no-FROM true/false comparisons and contradictory direct-CQ plans. |
| inputs / outputs | Constant predicates and a contradictory path start empty and receive source events. |
| invariants | A true nullary result is one empty tuple; false/contradiction emits none. A constant-false plan may retain original variable metadata while requiring an empty tree. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Small fixed cold owners, updates and oracle checks. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0021

[Lines 192–215](../../../../../tests/unit/comparisons_test.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L192-L215:sha256:58e1ffa5074c37287623f49d0e2229f3421badb5b32dd769998790dae406d783
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check full-source constraints and finite comparison/snapshot/producer limits. |
| inputs / outputs | Enforced FK/UNIQUE updates, a one-row retained-result cap and zero work/snapshot-row grants and a cumulative producer scan exhausted after source preparation exercise refusal. |
| invariants | Refused source or answer preparation preserves source/result sequence. A subsequent valid event at the same sequence succeeds; diagnostic snapshot failure leaves the owner ready. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Small full-source validations and deliberately bounded result/export attempts. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0022

[Lines 216–240](../../../../../tests/unit/comparisons_test.cpp#L216); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L216-L240:sha256:33464523867e274783abfa6c21fb21bb4e70221395adc9f60eeef73932756d09
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep persistent allocation denial across real comparison insertion/deletion. |
| inputs / outputs | A counted successful control determines every allocation prefix; each denied operation is followed by unchanged-state verification and retry on the same owner/sequence. |
| invariants | Both backends and both delta directions are covered. Every cut authenticates s04_alloc::triggered before unchanged-state checking. The global-new seam stays test-only and persists through rollback; old reference state advances only after a successful retry. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | One successful control and one reconstructed fixture/denial/retry per observed allocation, including native source preparation and comparison materialization. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0023

[Lines 241–247](../../../../../tests/unit/comparisons_test.cpp#L241); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L241-L247:sha256:ad861f99210a85c189ec55ec2efedf0f99e09963f002b6da3654daa09e462d4c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check owning output survival and independent query state. |
| inputs / outputs | A snapshot outlives its Trial; two comparison predicates own independent runtimes. |
| invariants | Output payload is native/accounted after runtime teardown, and updates to one owner cannot change another reference or native state. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | One retained snapshot and a few finite independent-owner updates. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0024

[Lines 248–248](../../../../../tests/unit/comparisons_test.cpp#L248); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L248-L248:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private test namespace. |
| inputs / outputs | Namespace scope terminates before the test entry point. |
| invariants | No state change or new validation occurs. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | No executable work. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |

## B0025

[Lines 249–255](../../../../../tests/unit/comparisons_test.cpp#L249); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L249-L255:sha256:d237535a710ba034459a863627c233f3c3e1c913367a32a575c8449bafc36210
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all comparison correctness and atomic-refusal tests. |
| inputs / outputs | The process executes admission/ownership and both-backend semantic/type/constant/constraint/allocation suites, then reports the successful check count. |
| invariants | Any escaping standard exception returns a failing exit code. The printed count is produced only by actual execution, not by this source contract. |
| ownership | Test-owned ordinary fixtures/reference DTOs surround independently funded native owners. Temporary views stay within their tuples/owners; exports are explicit test copies. |
| failure | Allocation, native and assertion failures propagate to the helper or process boundary described above. No production recovery or retry machinery is installed by this test block. |
| cost | Sum of the finite suites; the process-level catch formats one failure and is not a production exception layer. |
| Design | [tests/unit/comparisons_test.cpp](../../../../../tests/unit/comparisons_test.cpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [include/crown/runtime/comparisons.hpp](../../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../../comparisons.md) |
