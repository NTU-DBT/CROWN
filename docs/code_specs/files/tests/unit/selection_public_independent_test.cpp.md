# `tests/unit/selection_public_independent_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_public_independent_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `b544fe54a41d19994ae403bb1239a645ba0af1993ee8014856f429149d9cbc40`. 370 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/selection_public_independent_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_default_constructible_v&lt;s::Selection&gt;); · [reviewed contract](#b0001) |
| [B0002 · 16–87](../../../../../tests/unit/selection_public_independent_test.cpp#L16) | Callable definition: void height_and_complete_constraints(const BooleanFixture& f) | calls s::select, height, complete, check; guard check(only_height.selected().structural_key() == f.label_by_key.begin()-&gt;first &&; growth insert; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 88–88](../../../../../tests/unit/selection_public_independent_test.cpp#L88) | Explanatory comments or spacing. |  |
| [B0004 · 89–121](../../../../../tests/unit/selection_public_independent_test.cpp#L89) | Callable definition: void family_ties_and_history(const BooleanFixture& f) | calls r::PhysicalRuntime::initialize, lower, at, configure_workload_statistics; guard check(tied_result.selected().structural_key() == std::min(f.by_label.at("generalized_x").structural…; 2 loop sites · [reviewed contract](#b0004) |
| [B0005 · 122–122](../../../../../tests/unit/selection_public_independent_test.cpp#L122) | Explanatory comments or spacing. |  |
| [B0006 · 123–175](../../../../../tests/unit/selection_public_independent_test.cpp#L123) | Callable definition: void unavailable_and_early_rejection(const BooleanFixture& f) | calls r::PhysicalRuntime::initialize, lower, at, s::PlanCache::create; guard check(required.stop == s::Stop::evidence_unavailable && !required.selection && cache.statistics() =…; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 176–176](../../../../../tests/unit/selection_public_independent_test.cpp#L176) | Explanatory comments or spacing. |  |
| [B0008 · 177–217](../../../../../tests/unit/selection_public_independent_test.cpp#L177) | Callable definition: void physical_current(const BooleanFixture& f) | calls r::PhysicalRuntime::initialize, lower, at, hot; guard check(label(f,result.selection()) == "generalized_x" && result.capture().inputs().identity().owner … · [reviewed contract](#b0008) |
| [B0009 · 218–218](../../../../../tests/unit/selection_public_independent_test.cpp#L218) | Explanatory comments or spacing. |  |
| [B0010 · 219–260](../../../../../tests/unit/selection_public_independent_test.cpp#L219) | Callable definition: void delta_session_lifecycle(const BooleanFixture& f) | calls lower, at, r::DeltaRuntime::initialize, configure_workload_statistics; guard check(emitted.remaining() == 1, "literal Boolean deletion did not retain one output");; growth insert · [reviewed contract](#b0010) |
| [B0011 · 261–261](../../../../../tests/unit/selection_public_independent_test.cpp#L261) | Explanatory comments or spacing. |  |
| [B0012 · 262–300](../../../../../tests/unit/selection_public_independent_test.cpp#L262) | Callable definition: void aliases_and_unused() | calls frontend::bind_sql, check, frontend::normalize_sql, std::move; guard check(std::holds_alternative&lt;frontend::BoundSql&gt;(bound),"alias SQL binding failed");; 3 loop sites · [reviewed contract](#b0012) |
| [B0013 · 301–301](../../../../../tests/unit/selection_public_independent_test.cpp#L301) | Explanatory comments or spacing. |  |
| [B0014 · 302–354](../../../../../tests/unit/selection_public_independent_test.cpp#L302) | Callable definition: void decimal_repeat_and_zero() | calls Decimal::parse, candidates, r::PhysicalRuntime::initialize, lower; guard check(selected.assessments().size() == 1 &&; growth emplace_back, push_back; 3 loop sites · [reviewed contract](#b0014) |
| [B0015 · 355–356](../../../../../tests/unit/selection_public_independent_test.cpp#L355) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0015) |
| [B0016 · 357–370](../../../../../tests/unit/selection_public_independent_test.cpp#L357) | Callable definition: int main(int argc,char** argv) | calls check, boolean_fixture, height_and_complete_constraints, family_ties_and_history; guard check(argc == 2,"usage: selection_public_independent_test REPOSITORY_ROOT");; returns 1 · [reviewed contract](#b0016) |

## B0001

[Lines 1–15](../../../../../tests/unit/selection_public_independent_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:2010738e25e876902d105d361c17ee7b20088516d3b58e7f705bfc8feedb14d0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_public_independent_test.cpp: include "selection_independent_fixture.hpp", &lt;iostream&gt;, &lt;limits&gt;; bind local aliases/name imports; require 7 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–87](../../../../../tests/unit/selection_public_independent_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void height_and_complete_constraints(const BooleanFixture& f) {
  const s::Source source{s::DirectCQ{}};
  const auto structural = s::select(f.all, source, height());
  const auto& only_height = complete(structural);
  check(only_height.selected().structural_key() == f.label_by_key.begin()->first &&
        only_height.selected().original_proof().height() == 2 && only_height.selected().height() == 2,
        "pure height did not retain the original typed optimum and full-key choice");
  check(only_height.evidence_use() == s::EvidenceUse::absent && !only_height.evidence() &&
        only_height.preparation_timing() == s::PreparationTiming::absent &&
        only_height.plan().guarantee().height_status == "valid_upper_bound",
        "pure structural selection invented current evidence or promoted low-level plan authority");
  const auto no_candidate = s::select(f.empty, source, height());
  check(no_candidate.stop == s::Stop::no_candidates && !no_candidate.selection, "empty actual snapshot selected a plan");
  auto moved = f.all;
  const auto retained = std::move(moved);
  check(retained.valid() && !moved.valid(), "snapshot move fixture failed");
  const auto invalid = s::select(moved, source, height());
  check(invalid.stop == s::Stop::invalid_handle && !invalid.selection, "invalid typed handle bypassed admission");

  auto owner = r::PhysicalRuntime::initialize(lower(f.by_label.at("native_s")), f.initial);
  hot(owner, f);
  const auto observed = capture_checked(f.all, owner);
  const auto before = owner.canonical_state();
  const auto workload = owner.workload_statistics();
  const auto initial_depth = s::select(f.all, source, depth(), observed.inputs());
  check(label(f, complete(initial_depth)) == "generalized_x", "unconstrained hot-R selection chose another shape");
  literal_depth(f, assessment(*initial_depth.selection, s::AssessmentPurpose::primary));
  const auto initial_slots = s::select(f.all, source, slots(), observed.inputs());
  check(label(f, complete(initial_slots)) == "native_s", "slot policy did not choose Q24");
  literal_slots(f, assessment(*initial_slots.selection, s::AssessmentPurpose::primary));

  for (const auto* cap : {"23", "24", "31", "32"}) {
    auto request = depth();
    request.constraint = s::TupleIndexSlotLimit{cap};
    const auto attempt = s::select(f.all, source, request, observed.inputs());
    if (std::string(cap) == "23") {
      check(attempt.stop == s::Stop::constraint_unsatisfied && !attempt.selection &&
            attempt.retained == 3 && attempt.constraint_evaluated == 3 && attempt.primary_evaluated == 0,
            "cap23 published a winner or skipped a constraint candidate");
      continue;
    }
    const auto& result = complete(attempt);
    check(attempt.constraint_evaluated == 3 && attempt.primary_evaluated == 3 &&
          result.assessments().size() == 2 && result.decisions().size() == 3,
          "dual policy did not assess the whole retained family twice");
    literal_slots(f, assessment(result, s::AssessmentPurpose::slot_constraint));
    const auto& primary = assessment(result, s::AssessmentPurpose::primary);
    literal_depth(f, primary);
    const bool all_fit = std::string(cap) == "32";
    check(label(f, result) == (all_fit ? "generalized_x" : "native_s"), "literal slot-cap C05 winner differs");
    check(f.label_by_key.at(primary.selected().structural_key()) == "generalized_x",
          "constraint rewrote C02's complete depth assessment winner");
    check(all_fit || result.selected_index() != primary.selected_index(), "C05 conflated constrained and assessment winners");
    std::set<std::size_t> seen;
    for (const auto& decision : result.decisions()) {
      check(seen.insert(decision.candidate_index).second, "duplicate candidate eligibility row");
      const auto member = f.all.candidate(decision.candidate_index);
      check(member.has_value(), "eligibility names absent candidate");
      const bool fits = all_fit || f.label_by_key.at(member->structural_key()) == "native_s";
      check(decision.eligibility == (fits ? s::Eligibility::within_slot_limit : s::Eligibility::above_slot_limit),
            "literal candidate eligibility differs from Q24/32/32");
    }
    auto initialized = r::PhysicalRuntime::initialize(result.plan(), f.initial);
    check(answers(initialized) == Relation{Row{}}, "selected artifact initialization changed Boolean output");
    static_cast<void>(initialized.apply({1, TableId{1}, SetOperation::erase, *f.initial.tables[1].begin()}));
    check(answers(initialized).empty(), "selected artifact retained a deleted sole witness");
    static_cast<void>(initialized.apply({2, TableId{1}, SetOperation::insert, *f.initial.tables[1].begin()}));
    check(answers(initialized) == Relation{Row{}}, "selected artifact did not restore literal output");
  }
  check(owner.canonical_state() == before && same_workload(workload, owner.workload_statistics()),
        "selection changed its actual evidence owner's data or census");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check complete constraints before primary ranking across a retained family. |
| inputs / outputs | Uses the three-member Boolean fixture, heats/captures owner evidence, and selects under exact slot caps 23,24,31,32. |
| invariants | Cap23 evaluates three constraints then exits before primary ranking; other caps evaluate all three constraints and all three primary scores; selected artifact is exercised by a witness update. |
| ownership | Fixture holds immutable family/evidence; runtime owner is mutated only to create evidence and execute the chosen plan. |
| failure | Mandatory slot limit never falls back around unsatisfied constraints; invalid/unsatisfied calls publish no result. |
| cost | Finite hot trace (90 R, 5 S, 5 T update attempts) and four three-candidate requests; no unbounded family search. |
| Design | [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0004

[Lines 89–121](../../../../../tests/unit/selection_public_independent_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void family_ties_and_history(const BooleanFixture& f) {
  const s::Source source{s::DirectCQ{}};
  auto owner = r::PhysicalRuntime::initialize(lower(f.by_label.at("native_s")), f.initial);
  owner.configure_workload_statistics(counters());
  for (std::size_t i = 0; i < 3; ++i) noop(owner, i, *f.initial.tables[i].begin(), 1);
  const auto equal = capture_checked(f.all, owner);
  const auto tied = s::select(f.all, source, depth(), equal.inputs());
  const auto& tied_result = complete(tied);
  check(tied_result.selected().structural_key() == std::min(f.by_label.at("generalized_x").structural_key(),
        f.by_label.at("generalized_y").structural_key()), "depth tie ignored full structural key");
  for (const auto& score : assessment(tied_result,s::AssessmentPurpose::primary).scores())
    check(score.numerator == (f.label_by_key.at(caller_text(score.structural_key)) == "native_s" ? "5" : "4") &&
          score.denominator == "3", "equal-weight literal assessment differs");
  const auto prefix = s::select(f.partial, source, depth(), equal.inputs());
  check(complete(prefix).snapshot().candidate_count() == 1 && !prefix.selection->snapshot().family_exhausted(),
        "retained prefix acquired family completeness");
  auto exhaustive = depth();
  exhaustive.family = s::FamilyPolicy::require_exhausted_family;
  const auto rejected = s::select(f.partial, source, exhaustive, equal.inputs());
  check(rejected.stop == s::Stop::incomplete_family && !rejected.selection && rejected.primary_evaluated == 0,
        "required family exhaustion silently advanced or scored a prefix");
  owner.reset_workload_statistics();
  noop(owner, 0, *f.initial.tables[0].begin(), 5);
  noop(owner, 1, *f.initial.tables[1].begin(), 5);
  noop(owner, 2, *f.initial.tables[2].begin(), 90);
  const auto hot_t = capture_checked(f.all, owner);
  const auto reversed = s::select(f.all, source, depth(), hot_t.inputs());
  check(label(f,complete(reversed)) == "generalized_y", "hot-T literal winner did not reverse");
  literal_depth(f,assessment(*reversed.selection,s::AssessmentPurpose::primary),false);
  check(tied_result.evidence()->denominator() == 3 && tied_result.evidence()->identity().epoch == 3 &&
        tied_result.evidence_use() == s::EvidenceUse::as_of,
        "old as-of result changed after reset and updates");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve tied family members and keep historical Evidence as-of across reset. |
| inputs / outputs | Compares three equal-denominator candidates, a retained one-member prefix, incomplete required-exhaustion request, then reset and a different hot-table trace. |
| invariants | Tie break uses full structural key; retained-prefix result does not claim family exhaustion; old Evidence remains unchanged after reset. |
| ownership | Snapshots/proofs/Evidence are immutable handles; current owner is changed separately. |
| failure | Required family exhaustion rejects the retained prefix; after reset and updates, the earlier Result continues to expose its unchanged as-of Evidence. This helper does not revalidate currentness. |
| cost | Three-candidate comparisons and finite hot updates; no provider is advanced by selection. |
| Design | [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0006

[Lines 123–175](../../../../../tests/unit/selection_public_independent_test.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unavailable_and_early_rejection(const BooleanFixture& f) {
  const s::Source source{s::DirectCQ{}};
  auto owner = r::PhysicalRuntime::initialize(lower(f.by_label.at("native_s")), f.initial);
  auto cache = s::PlanCache::create();
  const auto untouched = cache.statistics();
  const auto off = capture_checked(f.all, owner);
  const auto required = s::select(f.all, source, depth(), off.inputs(), &cache, s::CacheUse::read_write);
  check(required.stop == s::Stop::evidence_unavailable && !required.selection && cache.statistics() == untouched,
        "required disabled census fell back or touched cache");
  s::Request fallback;
  const auto allowed = s::select(f.all, source, fallback, off.inputs());
  check(complete(allowed).effective_policy() == rank::Policy::height_only &&
        has(allowed.selection->fallback_reasons(),rank::Reason::disabled), "configured disabled-census fallback lost reason");
  auto constrained = fallback;
  constrained.constraint = s::TupleIndexSlotLimit{"24"};
  const auto exact_sources = s::select(f.all, source, constrained, off.inputs());
  check(label(f,complete(exact_sources)) == "native_s" && exact_sources.selection->effective_policy() == rank::Policy::height_only,
        "valid source constraint could not coexist with disabled-depth fallback");
  capture::CaptureOptions no_sources;
  no_sources.state_limits.accounted_bytes = 0;
  const auto unavailable = capture_checked(f.all,owner,no_sources);
  const auto mandatory = s::select(f.all,source,constrained,unavailable.inputs(),&cache,s::CacheUse::read_write);
  check(mandatory.stop == s::Stop::evidence_unavailable && !mandatory.selection &&
        has(mandatory.reasons,rank::Reason::source_budget_exhausted) && cache.statistics() == untouched,
        "mandatory slot cap was bypassed by unavailable-source fallback");
  auto pending = owner.prepare({1,TableId{1},SetOperation::erase,*f.initial.tables[1].begin()});
  for (const auto bytes : {std::uint64_t{0}, std::numeric_limits<std::uint64_t>::max()}) {
    auto request = fallback;
    request.constraint = s::AllocatorByteLimit{bytes,s::BytePrediction::peak_allocation};
    const auto rejected = current::select_current(f.all,source,owner,request,{},&cache,s::CacheUse::read_write);
    check(rejected.stop == s::Stop::unsupported_memory_prediction && rejected.stage == s::Stage::admission &&
          !rejected.selection && rejected.preparation_timing == s::PreparationTiming::absent &&
          cache.statistics() == untouched, "allocator-byte request reached capture/cache or was converted to slots");
  }
  auto model = fallback;
  model.policy = s::Policy::maintenance_cost;
  const auto unsupported = current::select_current(f.all,source,owner,model,{},&cache,s::CacheUse::read_write);
  check(unsupported.stop == s::Stop::unsupported_model && unsupported.stage == s::Stage::admission &&
        !unsupported.selection && unsupported.preparation_timing == s::PreparationTiming::absent &&
        cache.statistics() == untouched, "unsupported model crossed the pending capture boundary");
  pending.rollback();
  for (const auto* cap : {"", "00", "+1", "-1", " 1", "1.0"}) {
    auto request = height();request.constraint = s::TupleIndexSlotLimit{cap};
    const auto rejected = s::select(f.all,source,request,off.inputs(),&cache,s::CacheUse::read_write);
    check(rejected.stop == s::Stop::invalid_request && !rejected.selection && cache.statistics() == untouched,
          "noncanonical slot cap was accepted or mutated cache");
  }
  auto changed = f.document.catalog;++changed.version;
  const auto foreign = candidates(changed,f.document.query);
  const auto mismatched = s::select(foreign,source,fallback,off.inputs(),&cache,s::CacheUse::read_write);
  check(mismatched.stop == s::Stop::binding_mismatch && !mismatched.selection && cache.statistics() == untouched,
        "foreign proof binding took fallback or reused cache");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check unavailable evidence and reject unsupported requests before capture/cache work. |
| inputs / outputs | Tests disabled-census fallback/require with available source cardinalities, then capture with state_limits.accounted_bytes=0, pending-owner allocator-byte requests, unsupported maintenance model, invalid slot text and foreign proof version. |
| invariants | With disabled depth but available source counts, height fallback can still honor a mandatory slot cap. When source capture is unavailable under the zero-byte budget, the mandatory cap returns evidence_unavailable; unsupported model and pending-owner admission remain separate stops. |
| ownership | Selection inputs are caller handles; pending state stays in owner until rolled back. |
| failure | Every invalid/unavailable case asserts a specific stop and no partial cache admission. |
| cost | Finite rejection matrix; it measures results/counters, not CPU or allocator peak. |
| Design | [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0008

[Lines 177–217](../../../../../tests/unit/selection_public_independent_test.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void physical_current(const BooleanFixture& f) {
  const s::Source source{s::DirectCQ{}};
  auto owner = r::PhysicalRuntime::initialize(lower(f.by_label.at("native_s")),f.initial);
  hot(owner,f);
  const auto first = current::select_current(f.all,source,owner,depth());
  const auto& result = complete(first);
  check(label(f,result.selection()) == "generalized_x" && result.capture().inputs().identity().owner == owner.owner().value &&
        result.capture().inputs().identity().epoch == 100 && result.capture().captured().has_value(),
        "current result is not tied to actual Physical owner/epoch");
  const auto before = owner.canonical_state();
  auto pending = owner.prepare({101,TableId{1},SetOperation::erase,*f.initial.tables[1].begin()});
  const auto excluded = current::select_current(f.all,source,owner,height());
  check(excluded.stop == s::Stop::boundary_unavailable && !excluded.selection && has(excluded.reasons,rank::Reason::pending),
        "height policy bypassed pending actual-owner exclusion");
  pending.rollback();
  check(owner.canonical_state() == before, "pending/rollback changed actual committed state");
  check(capture::revalidate(result.capture(),owner).boundary == 0, "rollback staled unchanged committed epoch");
  noop(owner,0,*f.initial.tables[0].begin(),1);
  check(has(capture::revalidate(result.capture(),owner).boundary,rank::Reason::stale), "no-op commit did not stale old current capture");
  const auto next = current::select_current(f.all,source,owner,depth());
  check(complete(next).capture().inputs().identity().epoch == 101 && result.capture().inputs().identity().epoch == 100,
        "fresh capture reused/mutated the old epoch");
  auto rebuilt = owner.rebuilt();
  check(rebuilt.snapshot().physical.tables == owner.snapshot().physical.tables &&
        has(capture::revalidate(result.capture(),rebuilt).boundary,rank::Reason::foreign_owner),
        "equal rebuilt data inherited old owner identity");
  auto moved = std::move(owner);
  const auto moved_now = current::select_current(f.all,source,moved,depth());
  check(complete(moved_now).capture().inputs().identity().owner == result.capture().inputs().identity().owner,
        "move changed actual owner identity");
  moved.reset_workload_statistics();
  auto cap = s::Request{};cap.constraint = s::TupleIndexSlotLimit{"24"};
  const auto reset = current::select_current(f.all,source,moved,cap);
  check(label(f,complete(reset).selection()) == "native_s" &&
        reset.selection->selection().effective_policy() == rank::Policy::height_only &&
        has(reset.selection->selection().fallback_reasons(),rank::Reason::empty_census),
        "reset destroyed exact sources or borrowed the old depth census");
  const auto historical = s::select(f.all,source,depth(),result.capture().inputs());
  check(label(f,complete(historical)) == "generalized_x" && historical.selection->evidence_use() == s::EvidenceUse::as_of,
        "pure historical selection claimed currentness or lost retained facts");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track physical currentness over rollback, no-op commit, reset, move, and rebuild. |
| inputs / outputs | Captures at sequence 100, tests pending rejection/rollback, no-op epoch 101, recapture, different owner, moved runtime, reset, and historical select. |
| invariants | Pending blocks current selection; rollback can keep prior capture current; commit/reset/rebuild alter boundary identity; moved handle retains owner identity. |
| ownership | CurrentSelection retains its RuntimeEvidence; old Selection remains usable as-of and does not pin owner state as current. |
| failure | Pending current selection returns a boundary reason; old captures report stale or foreign_owner only through revalidation after commit/rebuild, while historical selection remains valid as-of. This helper does not request selection from a released owner. |
| cost | Sequential physical owner boundary operations with a capture at each asserted boundary. |
| Design | [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0010

[Lines 219–260](../../../../../tests/unit/selection_public_independent_test.cpp#L219); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void delta_session_lifecycle(const BooleanFixture& f) {
  const auto plan = lower(f.by_label.at("native_s"));
  const s::Source source{s::DirectCQ{}};
  auto owner = r::DeltaRuntime::initialize(plan,f.initial);
  owner.configure_workload_statistics(counters());
  auto emitted = owner.apply({1,TableId{1},SetOperation::erase,*f.initial.tables[1].begin()});
  check(emitted.remaining() == 1, "literal Boolean deletion did not retain one output");
  const auto unread = current::select_current(f.all,source,owner,height());
  check(complete(unread).capture().inputs().identity().epoch == 1 && emitted.remaining() == 1,
        "current selection drained committed unread output");
  emitted.discard();
  auto pending = owner.begin({2,TableId{1},SetOperation::insert,*f.initial.tables[1].begin()});
  const auto rejected = current::select_current(f.all,source,owner,height());
  check(rejected.stop == s::Stop::boundary_unavailable && !rejected.selection, "private Delta work was treated as committed");
  pending.rollback();
  static_cast<void>(owner.set_mode(r::DeltaMode::maintenance));
  const auto rotated = current::select_current(f.all,source,owner,s::Request{});
  check(complete(rotated).capture().inputs().identity().epoch == 1 &&
        rotated.selection->capture().inputs().identity().modes.delta_owner &&
        rotated.selection->selection().effective_policy() == rank::Policy::height_only &&
        has(rotated.selection->selection().fallback_reasons(),rank::Reason::empty_census),
        "mode change borrowed an old census or changed committed epoch");

  auto session = r::QuerySession::create_typed(plan,f.initial);
  session->configure_workload_statistics(counters());
  auto request = height();request.constraint = s::TupleIndexSlotLimit{"24"};
  const auto live = current::select_current(f.all,source,*session,request);
  check(label(f,complete(live).selection()) == "native_s" && live.selection->capture().session_context().has_value(),
        "session selection omitted its actual guarded context");
  session->start();session->stop();
  const auto stopped = current::select_current(f.all,source,*session,request);
  check(complete(stopped).capture().session_context()->status().state == r::SessionState::stopped,
        "stopped session lost still-owned committed facts");
  session->drop();
  const auto released = current::select_current(f.all,source,*session,height());
  check(released.stop == s::Stop::boundary_unavailable && !released.selection && has(released.reasons,rank::Reason::released),
        "released session took a current height fallback");
  check(live.selection->capture().session_context()->status().state == r::SessionState::created &&
        live.selection->capture().captured().has_value(), "drop changed prior owning current result");
  auto restored = r::PhysicalRuntime::initialize(live.selection->selection().plan(),f.initial);
  check(answers(restored) == Relation{Row{}}, "plan retained after session drop is unusable");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check Delta cursor and QuerySession lifecycle without confusing selection with epoch draining. |
| inputs / outputs | Applies a Delta epoch and leaves cursor output, checks current selection before/after pending and mode changes, then starts/stops/drops a QuerySession. |
| invariants | Selection does not drain the Delta cursor; session stop can retain runtime/currentness while drop releases it; old selected plan remains usable. |
| ownership | Session owns runtime while live; captured RuntimeEvidence is separate and immutable; cursor is explicitly local. |
| failure | Pending/current-after-drop paths reject; old result remains available but cannot refresh a released owner. |
| cost | One delta update/cursor and one session lifecycle with a small number of current captures. |
| Design | [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0012

[Lines 262–300](../../../../../tests/unit/selection_public_independent_test.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void aliases_and_unused() {
  const Catalog catalog{7,{{"unused",{{"value",ScalarType::int64}}},
      {"r",{{"x",ScalarType::int64},{"flag",ScalarType::int64},{"payload",ScalarType::string}}}}};
  auto bound = frontend::bind_sql("SELECT DISTINCT a.x FROM r a JOIN r b ON a.x=b.x WHERE a.flag=1",catalog);
  check(std::holds_alternative<frontend::BoundSql>(bound),"alias SQL binding failed");
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(bound));
  check(std::holds_alternative<frontend::NormalizedSql>(normalized),"alias SQL normalization failed");
  const auto program = std::get<frontend::NormalizedSql>(std::move(normalized));
  const auto set = candidates(program.core_catalog,program.core);
  const auto basis = p::lower_normalized(program,set.candidate(0)->tree());
  const s::Source source{s::PhysicalBasis{basis}};
  Database initial{{Relation{Row{std::int64_t{99}}},Relation{
      Row{std::int64_t{1},std::int64_t{1},std::string("a")},Row{std::int64_t{2},std::int64_t{0},std::string("b")}}}};
  auto owner = r::PhysicalRuntime::initialize(basis,initial);
  owner.configure_workload_statistics(counters());
  noop(owner,1,*initial.tables[1].begin(),3);
  for (unsigned i = 0;i < 2;++i)
    static_cast<void>(owner.apply({owner.sequence()+1,TableId{1},SetOperation::erase,
        {std::int64_t{3},std::int64_t{1},std::string("absent")}}));
  noop(owner,0,*initial.tables[0].begin(),2);
  const auto result = current::select_current(set,source,owner,depth());
  const auto& selected = complete(result).selection();
  for (const auto& score : assessment(selected,s::AssessmentPurpose::primary).scores()) {
    check(score.numerator == "10" && score.denominator == "7" && score.height == 1 && score.depths.size() == 2,
          "physical aliases or unused source changed literal10/7");
    for (const auto& item : score.depths) check(item.table == TableId{1} && item.depth == 1,"alias route lost physical table ID");
  }
  check(result.selection->capture().inputs().weights().size() == 2 && result.selection->capture().inputs().denominator() == 7,
        "unused physical source disappeared from the committed denominator");
  auto initialized = r::PhysicalRuntime::initialize(selected.plan(),initial);
  check(answers(initialized) == Relation{Row{std::int64_t{1}}},"selected normalized plan changed literal filtered alias output");
  const auto memory = current::select_current(set,source,owner,slots());
  check(complete(memory).capture().inputs().sources().size() == 1 &&
        memory.selection->capture().inputs().sources()[0].table == TableId{1} &&
        memory.selection->capture().inputs().sources()[0].rows == 2,
        "slot source used filtered membership or scanned unused physical input");
  const auto mismatch = s::select(set,s::Source{s::DirectCQ{}},s::Request{},result.selection->capture().inputs());
  check(mismatch.stop == s::Stop::binding_mismatch && !mismatch.selection,"normalized evidence was transplanted to a core-only source");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check alias multiplicity, unused-table denominator, and source-specific statistics. |
| inputs / outputs | Builds normalized self-join with aliases plus unused table, applies seven no-op/update attempts, and compares depth/slot behavior. |
| invariants | Aliases share a base table’s input count but each occurrence contributes depth; unused source tables remain in denominator; core-only source is rejected for normalized evidence. |
| ownership | Normalized source and actual owner live through capture; Selection retains source binding, not owner mutability. |
| failure | Wrong source or incomplete slot/depth facts stop explicitly; no filtered-answer count substitutes for source cardinality. |
| cost | Seven finite update attempts and candidate-limited selections; unused-table census still participates in denominators. |
| Design | [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0014

[Lines 302–354](../../../../../tests/unit/selection_public_independent_test.cpp#L302); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void decimal_repeat_and_zero() {
  const auto value = Decimal::parse("12345678901234567890123456789012345678");
  const auto predicate = Decimal::parse("87654321098765432109876543210987654321");
  const Catalog catalog{1,{{"decimal_rows",{{"x",ScalarType::decimal},{"filter",ScalarType::decimal}}}}};
  const Query query{{{"x",ScalarType::decimal}},{{"r",TableId{0},{VariableId{0},Value{predicate}}}},
      {{VariableId{0},"first"},{VariableId{0},"again"}},false};
  const auto set = candidates(catalog,query);
  Database initial{{Relation{Row{value,predicate},Row{value,Decimal::parse("0")}}}};
  auto owner = r::PhysicalRuntime::initialize(lower(*set.candidate(0)),initial);
  auto request = slots();request.constraint = s::TupleIndexSlotLimit{"13"};
  const auto result = current::select_current(set,s::Source{s::DirectCQ{}},owner,request);
  const auto& selected = complete(result).selection();
  check(selected.assessments().size() == 1 &&
        assessment(selected,s::AssessmentPurpose::primary_and_constraint).scores()[0].slots == "13",
        "Decimal/repeated projection changed literalQ13 or duplicated its assessment");
  auto initialized = r::PhysicalRuntime::initialize(selected.plan(),initial);
  check(answers(initialized) == Relation{Row{value,value}},"selected Decimal repeated head changed literal output");
  bool unequal = false;
  const auto exported_plan = PhysicalPlan::from_compiled(selected.plan());
  try {static_cast<void>(exported_plan.result_layout().tuple(Row{value,predicate}));}
  catch (const Error& error) {unequal = error.code() == "invalid_tuple";}
  check(unequal,"selected repeated layout lost its equality check");
  request.constraint = s::TupleIndexSlotLimit{"12"};
  const auto short_cap = current::select_current(set,s::Source{s::DirectCQ{}},owner,request);
  check(short_cap.stop == s::Stop::constraint_unsatisfied && !short_cap.selection,"Q13 fit a cap12");
  for (const bool nullary : {false,true}) {
    Catalog one{1,{{"T",{{"x",ScalarType::int64}}}}};Query q;
    if (!nullary) q.variables = {{"x",ScalarType::int64}};
    Atom atom{"t",TableId{0},{}};
    if (nullary) atom.terms.emplace_back(IgnoredColumn{});else atom.terms.emplace_back(VariableId{0});
    q.atoms.push_back(std::move(atom));
    const auto family = candidates(one,q);
    const auto plan = lower(*family.candidate(0));
    for (const bool empty : {false,true}) {
      Database db{{empty ? Relation{} : Relation{Row{std::int64_t{1}},Row{std::int64_t{2}},Row{std::int64_t{3}}}}};
      auto actual = r::PhysicalRuntime::initialize(plan,db);
      const auto attempt = current::select_current(family,s::Source{s::DirectCQ{}},actual,slots());
      const auto& score = assessment(complete(attempt).selection(),s::AssessmentPurpose::primary).scores()[0];
      check(score.slots == (empty ? "0" : (nullary ? "4" : "14")),"literal unary/nullary/empty Q differs");
      check(actual.has_answer() == !empty,"selection changed empty/nullary Boolean result");
    }
  }
  for (const bool contradiction : {false,true}) {
    Catalog no_tables;Query q;q.contradiction = contradiction;
    const auto family = candidates(no_tables,q);
    auto actual = r::PhysicalRuntime::initialize(lower(*family.candidate(0)),Database{});
    auto zero = slots();zero.constraint = s::TupleIndexSlotLimit{"0"};
    const auto result_zero = current::select_current(family,s::Source{s::DirectCQ{}},actual,zero);
    check(complete(result_zero).selection().selected().height() == 0 &&
          assessment(result_zero.selection->selection(),s::AssessmentPurpose::primary_and_constraint).scores()[0].slots == "0" &&
          actual.has_answer() == !contradiction,"zero-node constant route lost exact zero proxy or semantics");
  }
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check Decimal slot accounting, repeated outputs, and zero-node routes. |
| inputs / outputs | Exercises 38-digit Decimal repeated projection with exact Q13/Q12 caps, unary/nullary empty/nonempty shapes, and true/false contradictions. |
| invariants | Repeated output fields count repeated tuple slots. Empty-source cardinality is Q0 for both unary and nullary fixtures; nonempty unary and nullary fixtures produce Q14 and Q4 respectively. Zero-node contradiction routes preserve their Boolean result. |
| ownership | Queries/plans are local immutable values; selection result retains its candidate and compiled artifact. |
| failure | Q12 rejects while Q13 passes; empty/nonempty cases are separate; no unsupported allocator byte inference. |
| cost | Finite shape matrix and cap comparisons; counts vary by projected slots, not output-row scan volume. |
| Design | [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0015

[Lines 355–356](../../../../../tests/unit/selection_public_independent_test.cpp#L355); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L355-L356:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_public_independent_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 357–370](../../../../../tests/unit/selection_public_independent_test.cpp#L357); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
  try {
    check(argc == 2,"usage: selection_public_independent_test REPOSITORY_ROOT");
    const auto fixture = boolean_fixture(argv[1]);
    height_and_complete_constraints(fixture);
    family_ties_and_history(fixture);
    unavailable_and_early_rejection(fixture);
    physical_current(fixture);
    delta_session_lifecycle(fixture);
    aliases_and_unused();
    decimal_repeat_and_zero();
    std::cout << "C05 independent public groups=7 depth=195/105/190 slots=24/32/32 caps=23/24/31/32 alias=10/7 decimal=13 zero=0\n";
  } catch (const std::exception& error) {std::cerr << error.what() << '\n';return 1;}
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the seven independent public selection behavior groups. |
| inputs / outputs | Requires a fixture path and calls constraints, family/history, unavailable, physical current, Delta/session, alias, and Decimal/empty cases. |
| invariants | Groups use independent literals and check exact outcomes; the executable source is reviewed, not executed in this packet. |
| ownership | Fixture and group locals release independently. |
| failure | Input/preparation/assertion failures return a failed process. |
| cost | Seven groups over small candidate families with the stated finite update and cap loops. |
| Design | [tests/unit/selection_public_independent_test.cpp](../../../../../tests/unit/selection_public_independent_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |
