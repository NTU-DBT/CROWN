# `src/io/residual.cpp` — block usage map

[Source](../../../../../src/io/residual.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `d53ad91e68a3de8be07f62d9f19a7c0d738f742b8065c102527f679d9afe7b6d`. 387 lines partitioned into 42 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/io/residual.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases. | returns #Value · [reviewed contract](#b0001) |
| [B0002 · 11–17](../../../../../src/io/residual.cpp#L11) | Callable definition: const char* name(ResidualMode value) noexcept | calls RESIDUAL_ENUM_CASE; returns @ · [reviewed contract](#b0002) |
| [B0003 · 18–28](../../../../../src/io/residual.cpp#L18) | Callable definition: const char* name(ResidualOrigin value) noexcept | calls RESIDUAL_ENUM_CASE; returns @ · [reviewed contract](#b0003) |
| [B0004 · 29–49](../../../../../src/io/residual.cpp#L29) | Callable definition: const char* name(ResidualPhase value) noexcept | calls RESIDUAL_ENUM_CASE; returns @ · [reviewed contract](#b0004) |
| [B0005 · 50–59](../../../../../src/io/residual.cpp#L50) | Callable definition: const char* name(ResidualResult value) noexcept | calls RESIDUAL_ENUM_CASE; returns @ · [reviewed contract](#b0005) |
| [B0006 · 60–68](../../../../../src/io/residual.cpp#L60) | Callable definition: const char* name(ResidualProofStatus value) noexcept | calls RESIDUAL_ENUM_CASE; returns @ · [reviewed contract](#b0006) |
| [B0007 · 69–90](../../../../../src/io/residual.cpp#L69) | Callable definition: const char* name(ResidualStopReason value) noexcept | calls RESIDUAL_ENUM_CASE; returns @ · [reviewed contract](#b0007) |
| [B0008 · 91–98](../../../../../src/io/residual.cpp#L91) | Callable definition: const char* name(ResidualTerminal value) noexcept | calls RESIDUAL_ENUM_CASE; returns @ · [reviewed contract](#b0008) |
| [B0009 · 99–106](../../../../../src/io/residual.cpp#L99) | Callable definition: const char* name(EarCondition value) noexcept | calls RESIDUAL_ENUM_CASE; returns @ · [reviewed contract](#b0009) |
| [B0010 · 107–122](../../../../../src/io/residual.cpp#L107) | Callable definition: const char* name(SearchPhase value) noexcept | calls RESIDUAL_ENUM_CASE; returns @ · [reviewed contract](#b0010) |
| [B0011 · 123–141](../../../../../src/io/residual.cpp#L123) | Callable definition: const char* name(StopReason value) noexcept | calls RESIDUAL_ENUM_CASE; returns @ · [reviewed contract](#b0011) |
| [B0012 · 142–150](../../../../../src/io/residual.cpp#L142) | Callable definition: const char* name(ResultKind value) noexcept | calls RESIDUAL_ENUM_CASE; returns @ · [reviewed contract](#b0012) |
| [B0013 · 151–157](../../../../../src/io/residual.cpp#L151) | Callable definition: const char* name(BoundEvidence value) noexcept | calls RESIDUAL_ENUM_CASE; returns @ · [reviewed contract](#b0013) |
| [B0014 · 158–159](../../../../../src/io/residual.cpp#L158) | Member/declaration region. |  · [reviewed contract](#b0014) |
| [B0015 · 160–164](../../../../../src/io/residual.cpp#L160) | Callable definition: Json index_set(const VariableSet& values) | calls Json::array, push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 165–169](../../../../../src/io/residual.cpp#L165) | Callable definition: Json index_list(const std::vector&lt;std::size_t&gt;& values) | calls Json::array, push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 170–172](../../../../../src/io/residual.cpp#L170) | Callable definition: Json optional_index(const std::optional&lt;std::size_t&gt;& value) | calls Json; returns value ? Json(*value) : Json(nullptr) · [reviewed contract](#b0017) |
| [B0018 · 173–175](../../../../../src/io/residual.cpp#L173) | Callable definition: Json optional_variable(const std::optional&lt;VariableId&gt;& value) | calls Json; returns value ? Json(value-&gt;value) : Json(nullptr) · [reviewed contract](#b0018) |
| [B0019 · 176–183](../../../../../src/io/residual.cpp#L176) | Callable definition: Json counters(const WorkCounters& value) | calls ; returns {{@ , value.attempted}, · [reviewed contract](#b0019) |
| [B0020 · 184–187](../../../../../src/io/residual.cpp#L184) | Callable definition: Json phase_limit(const PhaseCeiling& value) | calls Json, count; returns {{@ , value.work ? Json(*value.work) : Json(nullptr)}, · [reviewed contract](#b0020) |
| [B0021 · 188–190](../../../../../src/io/residual.cpp#L188) | Callable definition: Json depth_limit(const std::optional&lt;std::size_t&gt;& value) | calls Json; returns value ? Json(*value) : Json(nullptr) · [reviewed contract](#b0021) |
| [B0022 · 191–204](../../../../../src/io/residual.cpp#L191) | Callable definition: Json statistics(const ResidualStatistics& value) | calls ; returns {{@ , value.hierarchy_tests}, · [reviewed contract](#b0022) |
| [B0023 · 205–219](../../../../../src/io/residual.cpp#L205) | Callable definition: Json exact_statistics(const SearchStatistics& value) | calls ; returns {{@ , value.work}, · [reviewed contract](#b0023) |
| [B0024 · 220–221](../../../../../src/io/residual.cpp#L220) | Explanatory comments or spacing. | source comment (unverified): // Compatibility path builds/validates a full binding Document/DOM before · [reviewed contract](#b0024) |
| [B0025 · 222–224](../../../../../src/io/residual.cpp#L222) | Callable definition: Json query_payload(const Catalog& catalog, const Query& query) | calls detail::query_binding, at; returns detail::query_binding(catalog, query).at(@ ); source comment (unverified): // Compatibility path builds/validates a full binding Document/DOM before · [reviewed contract](#b0025) |
| [B0026 · 225–227](../../../../../src/io/residual.cpp#L225) | Callable definition: Json ear_anchor(const EarAnchor& value) | calls name; returns {{@ , value.occurrence}, {@ , name(value.condition)}} · [reviewed contract](#b0026) |
| [B0027 · 228–235](../../../../../src/io/residual.cpp#L228) | Callable definition: Json ear(const EarRecord& value) | calls Json::array, push_back, ear_anchor, index_set; returns {{@ , value.occurrence},; growth push_back; 1 loop sites · [reviewed contract](#b0027) |
| [B0028 · 236–251](../../../../../src/io/residual.cpp#L236) | Callable definition: Json layer(const ResidualLayer& value) | calls Json::array, push_back, ear, index_list; returns {{@ , index_list(value.members)},; growth push_back; 2 loop sites · [reviewed contract](#b0028) |
| [B0029 · 252–266](../../../../../src/io/residual.cpp#L252) | Callable definition: Json trace_view(const ResidualTrace& value) | calls record, Json::array, push_back, optional_index; returns {{@ , index_list(view.original_occurrences)},; growth push_back; 3 loop sites · [reviewed contract](#b0029) |
| [B0030 · 267–267](../../../../../src/io/residual.cpp#L267) | Explanatory comments or spacing. | source comment (unverified): // The immutable handle certifies this frozen trace only, not tree height. · [reviewed contract](#b0030) |
| [B0031 · 268–288](../../../../../src/io/residual.cpp#L268) | Callable definition: Json trace_document(const ResidualTrace& value) | calls valid, Error, record, Json::array; returns {{@ , 1},; growth push_back; 2 loop sites; source comment (unverified): // The immutable handle certifies this frozen trace only, not tree height. · [reviewed contract](#b0031) |
| [B0032 · 289–289](../../../../../src/io/residual.cpp#L289) | Explanatory comments or spacing. | source comment (unverified): // A typed checked upper remains upper-only; exact original proof is separate. · [reviewed contract](#b0032) |
| [B0033 · 290–304](../../../../../src/io/residual.cpp#L290) | Callable definition: Json candidate_document(const ResidualCandidate& value) | calls valid, Error, catalog, query; returns {{@ , 1},; source comment (unverified): // A typed checked upper remains upper-only; exact original proof is separate. · [reviewed contract](#b0033) |
| [B0034 · 305–320](../../../../../src/io/residual.cpp#L305) | Callable definition: Json exact_diagnostic(const SearchProgress& value, bool original_scope) | calls name, optional_index, counters, exact_statistics; returns {{@ , original_scope}, · [reviewed contract](#b0034) |
| [B0035 · 321–329](../../../../../src/io/residual.cpp#L321) | Callable definition: Json residual_limits(const ResidualLimits& value) | calls phase_limit, depth_limit, Json; returns {{@ , phase_limit(value.residual)}, · [reviewed contract](#b0035) |
| [B0036 · 330–331](../../../../../src/io/residual.cpp#L330) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0036) |
| [B0037 · 332–334](../../../../../src/io/residual.cpp#L332) | Callable definition: Json write_residual_trace(const planner::ResidualTrace& value) | calls trace_document; returns trace_document(value) · [reviewed contract](#b0037) |
| [B0038 · 335–335](../../../../../src/io/residual.cpp#L335) | Explanatory comments or spacing. |  |
| [B0039 · 336–338](../../../../../src/io/residual.cpp#L336) | Callable definition: Json write_residual_candidate(const planner::ResidualCandidate& value) | calls candidate_document; returns candidate_document(value) · [reviewed contract](#b0039) |
| [B0040 · 339–341](../../../../../src/io/residual.cpp#L339) | Explanatory comments or spacing. | source comment (unverified): // Exclusive diagnostic export: no advance/replay, but ordinary allocating DOM · [reviewed contract](#b0040) |
| [B0041 · 342–386](../../../../../src/io/residual.cpp#L342) | Callable definition: Json write_residual_progress(const planner::ResidualSearch& owner) | calls catalog, query, options, progress; returns {{@ , 1},; source comment (unverified): // Exclusive diagnostic export: no advance/replay, but ordinary allocating DOM · [reviewed contract](#b0041) |
| [B0042 · 387–387](../../../../../src/io/residual.cpp#L387) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0042) |

## B0001

[Lines 1–10](../../../../../src/io/residual.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#define RESIDUAL_ENUM_CASE(Type, Value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define local descriptive residual enum spellings. |
| inputs / outputs | Macro expands one case to the exact enumerator name for finite name overloads; private planner lookup imported above. |
| invariants | Macro is undefined after use. Unknown enum values deliberately return unknown; formatting does not validate/upgrade trace, candidate or proof authority. |
| ownership | No storage; returned spellings are static literals. |
| failure | No runtime macro failure; enclosing noexcept enum writers have unknown fallback. |
| cost | Preprocessor substitution/static literals, no runtime owner or allocation. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0002

[Lines 11–17](../../../../../src/io/residual.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResidualMode value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive ResidualMode without inferring authority. |
| inputs / outputs | Declared cases map to candidates_with_exact_repair, require_exact_original; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | noexcept; returns unknown for unsupported value. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0003

[Lines 18–28](../../../../../src/io/residual.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResidualOrigin value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive ResidualOrigin without inferring authority. |
| inputs / outputs | Declared cases map to hierarchy_seed, native_leaf, generalized_leaf, generalized_graft, exact_repair, exact_original; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | noexcept; returns unknown for unsupported value. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0004

[Lines 29–49](../../../../../src/io/residual.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResidualPhase value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive ResidualPhase without inferring authority. |
| inputs / outputs | Declared cases map to admitted, scopes, recognize, eligibility, delete_ears, seal_layer, trace_replay, seed, restore, validate_candidate, repair, exact_original, complete, failed, cancelled, moved_from; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | noexcept; returns unknown for unsupported value. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0005

[Lines 50–59](../../../../../src/io/residual.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResidualResult value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive ResidualResult without inferring authority. |
| inputs / outputs | Declared cases map to unfinished, checked_candidate, verified_optimum, verified_infeasible, failed; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | noexcept; returns unknown for unsupported value. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0006

[Lines 60–68](../../../../../src/io/residual.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResidualProofStatus value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive ResidualProofStatus without inferring authority. |
| inputs / outputs | Declared cases map to none, trace_verified, checked_upper_only, exact_original_verified; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | noexcept; returns unknown for unsupported value. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0007

[Lines 69–90](../../../../../src/io/residual.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResidualStopReason value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive ResidualStopReason without inferring authority. |
| inputs / outputs | Declared cases map to none, quantum_work, quantum_time, total_work, total_time, depth_limit, record_limit, cell_limit, exact_limit, allocation_failure, counter_overflow, invalid_quantum, invalid_trace, internal_failure, complete, cancelled, moved_from; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | noexcept; returns unknown for unsupported value. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0008

[Lines 91–98](../../../../../src/io/residual.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResidualTerminal value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive ResidualTerminal without inferring authority. |
| inputs / outputs | Declared cases map to empty_body, hierarchical, stalled; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | noexcept; returns unknown for unsupported value. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0009

[Lines 99–106](../../../../../src/io/residual.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(EarCondition value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive EarCondition without inferring authority. |
| inputs / outputs | Declared cases map to first, second, both; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | noexcept; returns unknown for unsupported value. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0010

[Lines 107–122](../../../../../src/io/residual.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(SearchPhase value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive SearchPhase without inferring authority. |
| inputs / outputs | Declared cases map to admitted, preprocess, search, build_incumbent, validate_incumbent, export_proof, replay, complete, failed, cancelled, moved_from; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | noexcept; returns unknown for unsupported value. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0011

[Lines 123–141](../../../../../src/io/residual.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(StopReason value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive StopReason without inferring authority. |
| inputs / outputs | Declared cases map to none, quantum_work, quantum_time, total_work, total_time, depth_limit, allocation_failure, counter_overflow, invalid_quantum, invalid_certificate, internal_failure, complete, cancelled, moved_from; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | noexcept; returns unknown for unsupported value. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0012

[Lines 142–150](../../../../../src/io/residual.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResultKind value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive ResultKind without inferring authority. |
| inputs / outputs | Declared cases map to unfinished, verified_optimum, verified_infeasible, failed; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | noexcept; returns unknown for unsupported value. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0013

[Lines 151–157](../../../../../src/io/residual.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(BoundEvidence value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive BoundEvidence without inferring authority. |
| inputs / outputs | Declared cases map to universal, independently_checked; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | noexcept; returns unknown for unsupported value. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0014

[Lines 158–159](../../../../../src/io/residual.cpp#L158); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L158-L159:sha256:d1f6f19063e85fd4af527ede9df78b5a031bfb14bb18ea521bdda024fdf1f462
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ends the local preprocessor definition of RESIDUAL_ENUM_CASE; subsequent translation-unit code cannot use that macro expansion. |
| inputs / outputs | No runtime values are exchanged; a preprocessor macro is removed for later source text in this translation unit. |
| invariants | The macro expansion is available only before this directive; later code must use ordinary declarations or a fresh definition. |
| ownership | No runtime state. |
| failure | No runtime error. Preprocessing/compilation can fail if later tokens depended on the removed macro. |
| cost | Preprocessing only. |
| Design | [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/code_specs/files/src/io/residual.cpp.md](residual.cpp.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0015

[Lines 160–164](../../../../../src/io/residual.cpp#L160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json index_set(const VariableSet& values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize a residual ordered variable-ID set JSON array. |
| inputs / outputs | Copies VariableSet elements as .value integers in existing order into a new Json array. |
| invariants | No sorting, renumbering or validity proof is introduced; typed artifact supplied identity. |
| ownership | Returned Json owns array values independently of borrowed input. |
| failure | DOM allocation errors propagate; existing vendored cleanup repair applies during partial destruction. |
| cost | O(entries), ordinary DOM array capacity/element ownership; no search-work debit. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0016

[Lines 165–169](../../../../../src/io/residual.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json index_list(const std::vector<std::size_t>& values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize a residual ordered occurrence/index list JSON array. |
| inputs / outputs | Copies size_t entries unchanged in existing order into a new Json array. |
| invariants | No sorting, renumbering or validity proof is introduced; typed artifact supplied identity. |
| ownership | Returned Json owns array values independently of borrowed input. |
| failure | DOM allocation errors propagate; existing vendored cleanup repair applies during partial destruction. |
| cost | O(entries), ordinary DOM array capacity/element ownership; no search-work debit. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0017

[Lines 170–172](../../../../../src/io/residual.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json optional_index(const std::optional<std::size_t>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode optional residual size_t index. |
| inputs / outputs | Present value becomes integer (VariableId.value); absence becomes null. |
| invariants | Present zero remains zero. Null does not claim zero bound or a native SQL NULL. |
| ownership | Returned Json owns scalar value. |
| failure | Standard Json construction failures propagate without producer mutation. |
| cost | Fixed Json scalar creation; no traversal or producer work charge. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0018

[Lines 173–175](../../../../../src/io/residual.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json optional_variable(const std::optional<VariableId>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode optional residual VariableId. |
| inputs / outputs | Present value becomes integer (VariableId.value); absence becomes null. |
| invariants | Present zero remains zero. Null does not claim zero bound or a native SQL NULL. |
| ownership | Returned Json owns scalar value. |
| failure | Standard Json construction failures propagate without producer mutation. |
| cost | Fixed Json scalar creation; no traversal or producer work charge. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0019

[Lines 176–183](../../../../../src/io/residual.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json counters(const WorkCounters& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize one recorded continuation work/depth/time summary. |
| inputs / outputs | Copies attempted/committed transitions/allocation failures/active time/current and peak depth. |
| invariants | These are recorded phase facts, not additive equivalent work units or new elapsed measurement; no clock read. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed object fields with ordinary DOM allocations. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md), [docs/residual_candidates.md §Work and resource accounting](../../../../residual_candidates.md) |

## B0020

[Lines 184–187](../../../../../src/io/residual.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json phase_limit(const PhaseCeiling& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize captured optional phase work/time ceilings. |
| inputs / outputs | work optional and active_time.count() become integers or null. |
| invariants | Ceilings describe owner configuration, not spent work; absent and zero remain distinct. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed object fields/optional scalar creation. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md), [docs/residual_candidates.md §Work and resource accounting](../../../../residual_candidates.md) |

## B0021

[Lines 188–190](../../../../../src/io/residual.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json depth_limit(const std::optional<std::size_t>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode optional residual logical depth ceiling. |
| inputs / outputs | Present value becomes integer (VariableId.value); absence becomes null. |
| invariants | Present zero remains zero. Null does not claim zero bound or a native SQL NULL. |
| ownership | Returned Json owns scalar value. |
| failure | Standard Json construction failures propagate without producer mutation. |
| cost | Fixed Json scalar creation; no traversal or producer work charge. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0022

[Lines 191–204](../../../../../src/io/residual.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json statistics(const ResidualStatistics& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize the residual algorithm recorded statistics. |
| inputs / outputs | Copies hierarchy/round/eligibility/deletion/restoration/draft/graft/repair/original-search/publication/admission counters. |
| invariants | Construction provenance and earlier activity are preserved separately; counts do not prove minimum height or a successful reconstruction. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed DOM fields, no algorithm scan/recognition or work/time charge. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md), [docs/residual_candidates.md §Work and resource accounting](../../../../residual_candidates.md) |

## B0023

[Lines 205–219](../../../../../src/io/residual.cpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json exact_statistics(const SearchStatistics& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize delegated exact-search recorded structural counters. |
| inputs / outputs | Copies work/states/partitions/candidates/cache/certificate/hierarchy/component/symmetry/pruning fields. |
| invariants | Delegated exact scope can be seed/repair rather than original; original lower authority is carried separately, not inferred from these numbers. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed DOM fields; no exact search/replay advancement. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md), [docs/residual_candidates.md §Work and resource accounting](../../../../residual_candidates.md) |

## B0024

[Lines 220–221](../../../../../src/io/residual.cpp#L220); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L220-L221:sha256:d5214e857fb04d332bb9ff269dfcc7b346d072e236ebf2268a0f51cab18b4f33
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Compatibility path builds/validates a full binding Document/DOM before copying out its query subtree; that cost is outside residual work quanta. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/residual.cpp lines 218-223; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/code_specs/files/src/io/residual.cpp.md](residual.cpp.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0025

[Lines 222–224](../../../../../src/io/residual.cpp#L222); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json query_payload(const Catalog& catalog, const Query& query)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract a terminal dense query payload through the existing full binding serializer. |
| inputs / outputs | Builds detail::query_binding(catalog,query), selects its query member and returns an owning Json copy. |
| invariants | This helper also copies Catalog/Query into a Document, builds empty database slots and validates/serializes full binding before extracting query. It does not prove terminal query equivalent to original. |
| ownership | Returned Json owns selected query; complete temporary binding/Document is released afterward. |
| failure | Binding validation/domain/DOM allocation errors propagate; local vendored JSON bad_alloc cleanup repair remains required. |
| cost | O(full catalog/query validation + binding DOM + query subtree copy), with temporary full Document/DOM overlap; no independent output byte/item cap. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0026

[Lines 225–227](../../../../../src/io/residual.cpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json ear_anchor(const EarAnchor& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize one frozen ear-anchor condition label. |
| inputs / outputs | Writes original anchor occurrence and EarCondition spelling. |
| invariants | Condition bits describe retained reduction support, not reconstruction validity, an original lower bound or minimum-height proof. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed DOM fields/static enum spelling. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md), [docs/residual_candidates.md §Frozen reduction](../../../../residual_candidates.md) |

## B0027

[Lines 228–235](../../../../../src/io/residual.cpp#L228); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json ear(const EarRecord& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize one frozen ear and its anchor list. |
| inputs / outputs | Copies original occurrence/shared/unique variable sets and all recorded anchors. |
| invariants | Writes already checked trace facts without replaying eligibility or selecting a new anchor. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | O(stored sets+anchors), ordinary DOM arrays/objects. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0028

[Lines 236–251](../../../../../src/io/residual.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json layer(const ResidualLayer& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize one complete frozen residual reduction layer. |
| inputs / outputs | Writes members/variables/head/unique, ears/deletion anchor order, remaining members and residual head. |
| invariants | Preserves original IDs and recorded order. Stalled/reduced shapes remain diagnostic; no rounds-plus-one height claim is generated. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | O(layer sets+ears/anchors+deletions), ordinary nested DOM ownership. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0029

[Lines 252–266](../../../../../src/io/residual.cpp#L252); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json trace_view(const ResidualTrace& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize the explicit dense terminal-view mapping. |
| inputs / outputs | Copies ascending original occurrences/variables, optional original-to-local maps and terminal query payload. |
| invariants | Dense query IDs are separate from original binding; table IDs still address original catalog. Terminal proof cannot silently certify original query. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | O(mapping widths) plus query_payload full binding validation/copy/DOM cost. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0030

[Lines 267–267](../../../../../src/io/residual.cpp#L267); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L267-L267:sha256:0f3de77bec3b4fe0ca817cfeb43aa378f51026d149434a2e6c296804dedc75c7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: The immutable handle certifies this frozen trace only, not tree height. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/residual.cpp lines 265-269; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/code_specs/files/src/io/residual.cpp.md](residual.cpp.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0031

[Lines 268–288](../../../../../src/io/residual.cpp#L268); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json trace_document(const ResidualTrace& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a genuine immutable replayed trace as a version1 diagnostic DOM. |
| inputs / outputs | Requires valid ResidualTrace, writes original binding/scopes/layers/terminal mapping and trace_verified=true. |
| invariants | The typed handle grants frozen trace authority only; JSON flag is descriptive and cannot manufacture a trace/tree/minimum proof. No re-replay occurs here. |
| ownership | Returned Json owns copied diagnostic content; immutable trace/source owners are borrowed during export. |
| failure | Moved-from trace throws invalid_residual_handle; delegated binding/DOM errors propagate using existing JSON cleanup repair. |
| cost | O(retained trace metadata + full original/terminal binding serialization), ordinary overlapping DOMs; outside advance quanta with no final export byte/item cap. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md), [docs/residual_candidates.md §Work and resource accounting](../../../../residual_candidates.md) |

## B0032

[Lines 289–289](../../../../../src/io/residual.cpp#L289); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L289-L289:sha256:a619cc8344ecefa27599884aa7b93f2ef00b9539c50239438624f7df288c105a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: A typed checked upper remains upper-only; exact original proof is separate. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/residual.cpp lines 287-291; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/code_specs/files/src/io/residual.cpp.md](residual.cpp.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0033

[Lines 290–304](../../../../../src/io/residual.cpp#L290); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json candidate_document(const ResidualCandidate& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an original-query checked upper candidate with honest proof status. |
| inputs / outputs | Requires valid ResidualCandidate; writes original binding, checked_upper_only/valid_upper_bound, height/origin, named tree and certificate=null. |
| invariants | Candidate is a typed P02 upper witness; origin describes last construction step, not exactness. No original minimum or infeasibility proof is synthesized. |
| ownership | Returned DOM owns its copy; original candidate/catalog/query/tree remain immutable. |
| failure | Moved-from handle/delegated catalog-tree validation/allocation failures propagate; no owner advancement. |
| cost | Full binding Document/DOM copy+validation and write_tree metadata validation/name sets/DOM, O(tree fields+metadata with ordered name comparisons). |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0034

[Lines 305–320](../../../../../src/io/residual.cpp#L305); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json exact_diagnostic(const SearchProgress& value, bool original_scope)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize exact-search diagnostics with explicit original-versus-induced scope. |
| inputs / outputs | Writes scope_original, phase/stop/result/height interval/evidence/completion, producer/replay/structural counters and revision. |
| invariants | Induced residual/repair proof cannot raise original lower bound. Progress fields are descriptive, not an editable verified handle. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed progress objects/fields, no exact traversal or clock. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md), [docs/residual_candidates.md §Work and resource accounting](../../../../residual_candidates.md) |

## B0035

[Lines 321–329](../../../../../src/io/residual.cpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json residual_limits(const ResidualLimits& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize residual and delegated-exact configured ceilings. |
| inputs / outputs | Writes residual phase/depth/record/cell limits and separate exact producer/replay/depth limits. |
| invariants | Logical record/cell/work counters do not impose an encoded DOM/allocator byte ceiling; owner admission/diagnostic serialization are separate costs. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed nested DOM fields/optionals. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md), [docs/residual_candidates.md §Work and resource accounting](../../../../residual_candidates.md) |

## B0036

[Lines 330–331](../../../../../src/io/residual.cpp#L330); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L330-L331:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/code_specs/files/src/io/residual.cpp.md](residual.cpp.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0037

[Lines 332–334](../../../../../src/io/residual.cpp#L332); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_residual_trace(const planner::ResidualTrace& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose immutable trace diagnostic serialization. |
| inputs / outputs | Delegates write_residual_trace to trace_document. |
| invariants | Only typed ResidualTrace enters; returned Json flags cannot bypass trace replay admission. |
| ownership | Returns owning ordinary Json DOM independent of handle lifetime. |
| failure | Handle/validation/allocation errors propagate with no partial public DOM. |
| cost | Fixed forwarding plus full trace/binding allocating export, outside search quanta. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0039

[Lines 336–338](../../../../../src/io/residual.cpp#L336); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_residual_candidate(const planner::ResidualCandidate& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose immutable checked upper candidate diagnostic serialization. |
| inputs / outputs | Delegates to candidate_document. |
| invariants | Typed candidate guarantees checked upper only; no overload accepts an editable tree/progress struct as that authority. |
| ownership | Caller owns returned ordinary DOM. |
| failure | Moved-from/delegated validation/allocation errors propagate without changing candidate/search. |
| cost | Fixed forwarding plus binding/tree allocating export. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0040

[Lines 339–341](../../../../../src/io/residual.cpp#L339); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L339-L341:sha256:293e6eb49dee6661d15716742dcfa46b9f52dbff0e6632a4266fdc1256c4239a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Exclusive diagnostic export: no advance/replay, but ordinary allocating DOM construction and nested copies have no final byte/item cap in this API. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/residual.cpp lines 337-343; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/code_specs/files/src/io/residual.cpp.md](residual.cpp.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0041

[Lines 342–386](../../../../../src/io/residual.cpp#L342); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_residual_progress(const planner::ResidualSearch& owner)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one exclusive ResidualSearch owner snapshot with distinct authority scopes. |
| inputs / outputs | Reads actual catalog/query/options/progress/trace/candidate/original optimum/infeasibility; rejects impossible simultaneous proofs; includes certificate only from original typed verified result. |
| invariants | Caller prevents interleaved advance/cancel/move. Trace verified, checked upper, induced exact diagnostics and original proof remain distinct. Export never runs residual reduction/exact search/replay or grants global cost/durability authority. |
| ownership | Returned Json owns diagnostic copy; local typed handles retain immutable source while building it. |
| failure | Owner invalidity/contradictory proofs/delegated validation/DOM allocation errors return no public result. Existing vendored JSON cleanup repair handles allocation failure; no local catch is added. |
| cost | Repeated full original/terminal binding copies/validation, trace/candidate/tree and optional verified certificate DOMs; O(all exported metadata and delegated validation), ordinary capacity/temporary overlap outside quanta. No final byte/item cap. |
| Design | [include/crown/io/residual.hpp](../../../../../include/crown/io/residual.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md), [docs/residual_candidates.md §Work and resource accounting](../../../../residual_candidates.md), [src/io/search.cpp](../../../../../src/io/search.cpp) |

## B0042

[Lines 387–387](../../../../../src/io/residual.cpp#L387); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L387-L387:sha256:a992a30ac7c9748c33994a213cb5eed12f62a6204d01f8b49f69db451a145039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/residual.cpp](../../../../../src/io/residual.cpp), [docs/code_specs/files/src/io/residual.cpp.md](residual.cpp.md), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
