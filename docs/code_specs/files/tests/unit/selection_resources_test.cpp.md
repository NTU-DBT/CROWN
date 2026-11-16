# `tests/unit/selection_resources_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_resources_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `577424404a278a00a5d239bf24f0a683a8bf9dd5a2f73e469b16223ce0ddf155`. 125 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/unit/selection_resources_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 8–8](../../../../../tests/unit/selection_resources_test.cpp#L8) | Type/record definition: struct Dimension |  · [reviewed contract](#b0002) |
| [B0003 · 9–16](../../../../../tests/unit/selection_resources_test.cpp#L9) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 17–20](../../../../../tests/unit/selection_resources_test.cpp#L17) | Callable definition: void same_choice(const ps::Selection& a, const ps::Selection& b) | calls check, selected_index, selected, structural_key; guard check(a.selected_index() == b.selected_index() && a.selected().structural_key() == b.selected().str… · [reviewed contract](#b0004) |
| [B0005 · 21–21](../../../../../tests/unit/selection_resources_test.cpp#L21) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |
| [B0006 · 22–125](../../../../../tests/unit/selection_resources_test.cpp#L22) | Callable definition: int main() | calls budget, begin_delegate, check, end_delegate; guard check(delegated.*dimension.cap == UINT64_MAX - 20, "C05 P+(L-U) narrowed or wrapped");; returns 1; 8 loop sites; source comment (unverified): // This private arithmetic fixture tests the aggregate transport equation; · [reviewed contract](#b0006) |

## B0001

[Lines 1–7](../../../../../tests/unit/selection_resources_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:f64152a91edcc77034596d6a31428d24c4533d74232d841e371ff3e3b4fea450
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_resources_test.cpp: include "selection_fixture.hpp", "selection_detail.hpp", &lt;array&gt;, &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_resources_test.cpp](../../../../../tests/unit/selection_resources_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–8](../../../../../tests/unit/selection_resources_test.cpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Dimension { std::uint64_t pr::Usage::*used; std::uint64_t pr::Limits::*cap; };

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name each used/cap pair for a resource dimension. |
| inputs / outputs | Stores two pointer-to-member selectors: one for Usage and one for Limits. It has no label or counter values. |
| invariants | The record is test notation only; it does not execute accounting. |
| ownership | Plain scalar value has no retained owner. |
| failure | No failure path beyond caller input. |
| cost | Two pointer-to-member values are stored; this helper performs no accounting. |
| Design | [tests/unit/selection_resources_test.cpp](../../../../../tests/unit/selection_resources_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0003

[Lines 9–16](../../../../../tests/unit/selection_resources_test.cpp#L9); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L16:sha256:ae4e69599b7bb00467d9b65ae4b67326dd8c7f9fa3907dd816438b5ea600e6a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_resources_test.cpp: declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/selection_resources_test.cpp](../../../../../tests/unit/selection_resources_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 17–20](../../../../../tests/unit/selection_resources_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void same_choice(const ps::Selection& a, const ps::Selection& b) {
  check(a.selected_index() == b.selected_index() && a.selected().structural_key() == b.selected().structural_key() &&
      a.plan().physical_sha256() == b.plan().physical_sha256(), "C05 resource grant changed successful choice");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require both selections to choose the same candidate and compiled plan. |
| inputs / outputs | Compares selected index, candidate key/digest, and plan digest from two Selection results. |
| invariants | Equality is checked across choice and executable artifact, not cache counters or owner identity. |
| ownership | Both Selection handles are borrowed for comparison and retain their plans. |
| failure | Mismatch throws the local test assertion. |
| cost | Compares selected index, full structural-key strings and physical SHA strings; structural-key equality may inspect bytes proportional to their common prefix/length. |
| Design | [tests/unit/selection_resources_test.cpp](../../../../../tests/unit/selection_resources_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0005

[Lines 21–21](../../../../../tests/unit/selection_resources_test.cpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L21:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_resources_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/selection_resources_test.cpp](../../../../../tests/unit/selection_resources_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 22–125](../../../../../tests/unit/selection_resources_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() { try {
  using namespace c05_test;
  // This private arithmetic fixture tests the aggregate transport equation;
  // it does not manufacture Evidence or claim an actual UINT64_MAX census.
  pr::Limits limits; pr::Usage preparation, total, returned;
  for (const auto& dimension : dimensions) {
    limits.*dimension.cap = UINT64_MAX;
    preparation.*dimension.used = UINT64_MAX - 40;
    total.*dimension.used = UINT64_MAX - 20;
    returned.*dimension.used = UINT64_MAX - 33;
  }
  preparation.active_nanoseconds = 9; total.active_nanoseconds = 9; returned.active_nanoseconds = 9;
  sd::Budget budget(limits, total); const auto delegated = budget.begin_delegate(preparation);
  for (const auto& dimension : dimensions)
    check(delegated.*dimension.cap == UINT64_MAX - 20, "C05 P+(L-U) narrowed or wrapped");
  budget.end_delegate(returned, preparation);
  for (const auto& dimension : dimensions)
    check(budget.usage.*dimension.used == UINT64_MAX - 13, "C05 V-P counted preparation twice");
  check(budget.usage.active_nanoseconds == 9 && !budget.running, "C05 untimed budget measured new time");
  bool overflow = false;
  try { budget.work(14); } catch (const sd::Failure& failure) { overflow = failure.resource == ps::Resource::work; }
  check(overflow && budget.usage.work == UINT64_MAX - 13, "C05 failed addition mutated or wrapped");
  sd::Budget wide(pr::Limits{});
  check(sd::decimal_compare("18446744073709551616", "18446744073709551615", wide) > 0 &&
      sd::decimal_compare("340282366920938463463374607431768211456", "18446744073709551616", wide) > 0 &&
      sd::decimal_compare("340282366920938463463374607431768211456", "340282366920938463463374607431768211456", wide) == 0,
      "C05 canonical comparison narrowed wide exact scores");

  const auto f = c02_test::fixture(); const auto snapshot = c02_test::candidates(f);
  const auto plan = planner::lower_tree(f.catalog, f.query, snapshot.candidate(0)->tree());
  auto owner = runtime::PhysicalRuntime::initialize(plan, f.database); heat(owner, f);
  const auto facts = capture(snapshot, owner).inputs(); const ps::Source source = ps::DirectCQ{};
  auto both = request(ps::Policy::committed_input_native_depth); both.constraint = ps::TupleIndexSlotLimit{"31"};
  const auto baseline = complete(ps::select(snapshot, source, both, facts));
  depth_oracle(assessment(baseline, pr::Policy::committed_input_native_depth));
  slot_oracle(assessment(baseline, pr::Policy::tuple_index_slots));
  check(baseline.assessments().size() == 2 && baseline.usage().active_nanoseconds == 0 &&
      baseline.preparation_timing() == ps::PreparationTiming::unmeasured, "C05 complete untimed dual assessment");
  for (const auto& dimension : dimensions) {
    std::uint64_t incremental = facts.preparation_usage().*dimension.used;
    for (const auto& item : baseline.assessments()) {
      check(item.result.usage().*dimension.used >= facts.preparation_usage().*dimension.used,
          "C05 component lost preparation accounting");
      incremental += item.result.usage().*dimension.used - facts.preparation_usage().*dimension.used;
      check(item.result.request().limits.*dimension.cap <= both.limits.aggregate.*dimension.cap,
          "C05 component received a fresh full grant");
    }
    check(baseline.usage().*dimension.used >= incremental, "C05 missing component incremental work");
    const auto used = baseline.usage().*dimension.used;
    if (!used) continue;
    auto exact = both; exact.limits.aggregate.*dimension.cap = used;
    const auto passed = complete(ps::select(snapshot, source, exact, facts)); same_choice(baseline, passed);
    check(passed.usage().*dimension.used == used, "C05 exact cap changed accounting");
    --(exact.limits.aggregate.*dimension.cap);
    const auto failed = ps::select(snapshot, source, exact, facts);
    check(!failed.selection && failed.stop == ps::Stop::resource_limit, "C05 one-under aggregate cap fell back/published");
    same_choice(baseline, complete(ps::select(snapshot, source, both, facts)));
  }
  for (const auto which : {0U, 1U}) {
    auto small = both;
    if (which == 0) small.limits.aggregate.candidates = snapshot.candidate_count() - 1;
    else small.limits.aggregate.score_bits = 1;
    const auto attempt = ps::select(snapshot, source, small, facts);
    check(!attempt.selection && attempt.stop == ps::Stop::resource_limit, "C05 candidate/bit stop activated fallback");
  }
  // First DirectCQ construction has no pre-existing identity DOM. Its known
  // source and newly created public identity/compiled payload remain capped.
  const auto height = request(ps::Policy::height_only);
  const auto direct = complete(ps::select(snapshot, source, height));
  for (const auto dimension : {dimensions[3], dimensions[4], dimensions[5]}) {
    auto exact = height; exact.limits.aggregate.*dimension.cap = direct.usage().*dimension.used;
    same_choice(direct, complete(ps::select(snapshot, source, exact)));
    --(exact.limits.aggregate.*dimension.cap);
    const auto stopped = ps::select(snapshot, source, exact);
    check(!stopped.selection && stopped.stop == ps::Stop::resource_limit, "C05 first DirectCQ payload/native cap ignored");
  }
  constexpr std::string_view maximum = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084095";
  auto cap = both; cap.constraint = ps::TupleIndexSlotLimit{std::string(maximum)};
  const auto wide_cap = complete(ps::select(snapshot, source, cap, facts));
  check(c02_test::shape(wide_cap.selected().tree()) == 1, "C05 512-bit cap narrowed");
  for (const auto& invalid : std::vector<std::string>{"", "00", "+1", "-1", " 1", "1 ", "1.0", std::string(maximum.substr(0, maximum.size() - 1)) + "6", std::string(156, '9')}) {
    cap.constraint = ps::TupleIndexSlotLimit{invalid};
    check(ps::select(snapshot, source, cap, facts).stop == ps::Stop::invalid_request, "C05 noncanonical/out-of-domain cap accepted");
  }
  auto timed = both; timed.limits.aggregate.active_time = std::chrono::hours(1);
  const auto timed_asof = complete(ps::select(snapshot, source, timed, facts)); same_choice(baseline, timed_asof);
  check(timed_asof.preparation_timing() == ps::PreparationTiming::unmeasured && timed_asof.usage().active_nanoseconds > 0,
      "C05 retrospectively measured old capture");
  const auto timed_current = complete(rs::select_current(snapshot, source, owner, timed));
  check(timed_current.selection().preparation_timing() == ps::PreparationTiming::measured &&
      timed_current.capture().inputs().preparation_usage().active_nanoseconds > 0 &&
      timed_current.selection().usage().active_nanoseconds >= timed_current.capture().inputs().preparation_usage().active_nanoseconds,
      "C05 current timing lost preparation");
  auto exhausted_time = height;
  exhausted_time.limits.aggregate.active_time = std::chrono::nanoseconds(timed_current.capture().inputs().preparation_usage().active_nanoseconds);
  const auto exhausted = ps::select(snapshot, source, exhausted_time, timed_current.capture().inputs());
  check(!exhausted.selection && exhausted.stop == ps::Stop::resource_limit && exhausted.resource == ps::Resource::active_time &&
      exhausted.usage == timed_current.capture().inputs().preparation_usage(), "C05 carried exact time ceiling was reset");
  exhausted_time.limits.aggregate.active_time = std::chrono::nanoseconds(0);
  check(ps::select(snapshot, source, exhausted_time).resource == ps::Resource::active_time, "C05 zero time cap ignored");
  exhausted_time.limits.aggregate.active_time = std::chrono::nanoseconds(-1);
  check(ps::select(snapshot, source, exhausted_time).stop == ps::Stop::invalid_request, "C05 negative time accepted");
  std::cout << "C05 aggregate exact/one-under, first-source admission, finite native work and optional timing contracts passed\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check every resource dimension, large score text, and timing behavior with real selection. |
| inputs / outputs | Exercises exact and one-under ceilings for each exercised nonzero-usage dimension among eight domains, DirectCQ admission limits, 512-bit score text and invalid strings, then as-of/current timing. |
| invariants | Each dimension is independently admitted; resource stop cannot fall back or publish a partial plan; timing includes preparation only when measured; slot counts never become allocator bytes. |
| ownership | Real results retain immutable candidate/evidence/plan handles; budget requests and copied source text are local. |
| failure | One-under, invalid decimal, negative time, and zero-time cases return explicit stops; retries compare against the full result. |
| cost | The cap loop skips dimensions whose measured use is zero, so it does not guarantee eight real exact/one-under boundary pairs; it also checks DirectCQ admission, nine invalid score texts and finite time cases. Work/bytes are logical counters, not elapsed CPU. |
| Design | [tests/unit/selection_resources_test.cpp](../../../../../tests/unit/selection_resources_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |
