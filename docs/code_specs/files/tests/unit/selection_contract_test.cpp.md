# `tests/unit/selection_contract_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_contract_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `df2b17d95c4eaaa3d91fe441bf18ab4536a679c0bb81138c4134c229b4de47fc`. 83 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–4](../../../../../tests/unit/selection_contract_test.cpp#L1) | Imports dependencies. |  · [reviewed contract](#b0001) |
| [B0002 · 5–83](../../../../../tests/unit/selection_contract_test.cpp#L5) | Callable definition: int main() | calls static_assert, plan, c02_test::fixture, c02_test::candidates; guard static_assert(!std::is_default_constructible_v&lt;ps::Selection&gt; && !std::is_default_constructible_v&lt;r…; returns 1; 3 loop sites · [reviewed contract](#b0002) |

## B0001

[Lines 1–4](../../../../../tests/unit/selection_contract_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L4:sha256:0f3e361fcb68d4968bee383413e3bf74972b1e5f5a04981dc7109c1481eac03d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_contract_test.cpp: include "selection_fixture.hpp", &lt;iostream&gt;, &lt;type_traits&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_contract_test.cpp](../../../../../tests/unit/selection_contract_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 5–83](../../../../../tests/unit/selection_contract_test.cpp#L5); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() { try {
  using namespace c05_test;
  static_assert(!std::is_default_constructible_v<ps::Selection> && !std::is_default_constructible_v<rs::CurrentSelection>);
  static_assert(!std::is_constructible_v<rs::CurrentSelection, ps::Selection, rr::RuntimeEvidence>);
  static_assert(std::is_same_v<decltype(std::declval<const ps::Selection&>().plan()), const CompiledProgram&>);
  const auto f = c02_test::fixture(); const auto snapshot = c02_test::candidates(f);
  const auto basis = planner::lower_tree(f.catalog, f.query, snapshot.candidate(0)->tree());
  const ps::Source source = ps::DirectCQ{};
  auto owner = runtime::PhysicalRuntime::initialize(basis, f.database); heat(owner, f);
  const auto state = owner.canonical_state(); const auto facts = capture(snapshot, owner);
  auto depth = request(ps::Policy::committed_input_native_depth);
  const auto pure = complete(ps::select(snapshot, source, depth, facts.inputs()));
  depth_oracle(assessment(pure, pr::Policy::committed_input_native_depth));
  check(c02_test::shape(pure.selected().tree()) == 1 && pure.evidence_use() == ps::EvidenceUse::as_of, "C05 hot R winner/as-of");
  check(pure.usage().active_nanoseconds == 0 && pure.preparation_timing() == ps::PreparationTiming::unmeasured, "C05 default timer read");
  valid_plan(pure, f.database);
  const auto current = complete(rs::select_current(snapshot, source, owner, depth));
  check(current.capture().inputs().identity().owner == owner.owner().value &&
      current.capture().inputs().identity().epoch == owner.sequence(), "C05 actual current boundary missing");
  depth_oracle(assessment(current.selection(), pr::Policy::committed_input_native_depth));
  auto memory = request(ps::Policy::tuple_index_slots);
  const auto m = complete(ps::select(snapshot, source, memory, facts.inputs()));
  slot_oracle(assessment(m, pr::Policy::tuple_index_slots));
  check(c02_test::shape(m.selected().tree()) == 0, "C05 memory winner");
  for (const auto cap : {"23", "24", "31", "32"}) {
    auto constrained = depth; constrained.constraint = ps::TupleIndexSlotLimit{cap};
    const auto attempt = ps::select(snapshot, source, constrained, facts.inputs());
    if (std::string_view(cap) == "23") {
      check(!attempt.selection && attempt.stop == ps::Stop::constraint_unsatisfied && attempt.constraint_evaluated == 3 &&
          attempt.primary_evaluated == 0, "C05 all-retained constraint rejection"); continue;
    }
    const auto selected = complete(attempt);
    check(selected.assessments().size() == 2 && selected.decisions().size() == 3, "C05 two complete assessments missing");
    slot_oracle(assessment(selected, pr::Policy::tuple_index_slots));
    depth_oracle(assessment(selected, pr::Policy::committed_input_native_depth));
    const bool fits_generalized = std::string_view(cap) == "32";
    check(c02_test::shape(selected.selected().tree()) == (fits_generalized ? 1 : 0), "C05 constrained primary winner");
    if (!fits_generalized) check(selected.selected_index() != assessment(selected, pr::Policy::committed_input_native_depth).selected_index(),
        "C05 failed to distinguish filtered winner from C02 assessment winner");
    for (const auto& decision : selected.decisions()) {
      const bool feasible = fits_generalized || c02_test::shape(snapshot.candidate(decision.candidate_index)->tree()) == 0;
      check(decision.eligibility == (feasible ? ps::Eligibility::within_slot_limit : ps::Eligibility::above_slot_limit),
          "C05 incomplete eligibility explanation");
    }
    valid_plan(selected, f.database);
  }
  auto height = request(ps::Policy::height_only); height.constraint = ps::TupleIndexSlotLimit{"31"};
  const auto h = complete(ps::select(snapshot, source, height, facts.inputs()));
  check(h.assessments().size() == 1 && h.effective_policy() == pr::Policy::height_only && c02_test::shape(h.selected().tree()) == 0,
      "C05 height plus mandatory slot constraint");
  auto partial = prefix(snapshot.original_proof());
  const auto p = complete(ps::select(partial, source, depth, facts.inputs()));
  check(p.snapshot().candidate_count() == 1 && !p.snapshot().family_exhausted(), "C05 partial family scope lost");
  depth.family = ps::FamilyPolicy::require_exhausted_family;
  const auto rejected = ps::select(partial, source, depth, facts.inputs());
  check(!rejected.selection && rejected.stop == ps::Stop::incomplete_family, "C05 incomplete family passed strict admission");
  auto unsupported = request(ps::Policy::maintenance_cost);
  check(ps::select(snapshot, source, unsupported).stop == ps::Stop::unsupported_model, "C05 invented C03 policy");
  unsupported.policy = ps::Policy::height_only;
  for (const auto bytes : {std::uint64_t{0}, std::uint64_t{13}, UINT64_MAX}) {
    unsupported.constraint = ps::AllocatorByteLimit{bytes, ps::BytePrediction::peak_allocation};
    check(rs::select_current(snapshot, source, owner, unsupported).stop == ps::Stop::unsupported_memory_prediction,
        "C05 compared allocator bytes with unitless slots");
  }
  unsupported.constraint = std::monostate{}; unsupported.layout = static_cast<ps::LayoutPolicy>(99);
  check(ps::select(snapshot, source, unsupported).stop == ps::Stop::unsupported_layout, "C05 invented layout backend");
  check(owner.canonical_state() == state && pure.snapshot().original_proof().valid(), "C05 selection changed actual owner/proof");
  owner.reset_workload_statistics();
  const auto old = complete(ps::select(snapshot, source, request(ps::Policy::committed_input_native_depth), facts.inputs()));
  depth_oracle(assessment(old, pr::Policy::committed_input_native_depth));
  const auto empty = complete(rs::select_current(snapshot, source, owner));
  check(empty.selection().effective_policy() == pr::Policy::height_only &&
      (empty.selection().fallback_reasons() & pr::reason(pr::Reason::empty_census)), "C05 reset reused old interval");
  heat(owner, f, false);
  const auto mirrored = complete(rs::select_current(snapshot, source, owner));
  depth_oracle(assessment(mirrored.selection(), pr::Policy::committed_input_native_depth), false);
  check(c02_test::shape(mirrored.selection().selected().tree()) == 2, "C05 mirrored hot T winner");
  std::cout << "C05 literal depth/slots, four constraints, typed proof and complete-family contracts passed\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate pure selection policy, cap evaluation order, and result-plan semantics. |
| inputs / outputs | Builds a finite source/family and Evidence, tests height/depth/slot choices, exact caps 23/24/31/32, and then applies the selected plan to check behavior. |
| invariants | At cap23 all three slot constraints are evaluated and primary ranking exits before candidate scoring; at 24/31/32 both complete assessments evaluate all three; primary winner and constrained winner can differ. |
| ownership | Selection owns the proof/family/result; runtime used for execution is separate. |
| failure | Unsatisfied mandatory constraint and resource stops return no Selection; fallback cannot bypass the constraint. |
| cost | Four exact cap requests and a finite three-candidate family; successful plan checks use a delete/reinsert witness update. |
| Design | [tests/unit/selection_contract_test.cpp](../../../../../tests/unit/selection_contract_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |
