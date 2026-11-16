# `tests/unit/candidates_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/candidates_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `22eaa6a2b6083b06e55dbbc3692f3fe97875e4fd979a386bbab0ebf1692d7f0e`. 1355 lines partitioned into 157 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–29](../../../../../tests/unit/candidates_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // This executable replaces the global allocation family so a failure remains · [reviewed contract](#b0001) |
| [B0002 · 30–38](../../../../../tests/unit/candidates_exception_test.cpp#L30) | Callable definition: \[\[gnu::noinline\]\] void* tracked_malloc_new(std::size_t bytes) | calls std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 39–39](../../../../../tests/unit/candidates_exception_test.cpp#L39) | Explanatory comments or spacing. |  |
| [B0004 · 40–45](../../../../../tests/unit/candidates_exception_test.cpp#L40) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0004) |
| [B0005 · 46–47](../../../../../tests/unit/candidates_exception_test.cpp#L46) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 48–48](../../../../../tests/unit/candidates_exception_test.cpp#L48) | Callable definition: void* operator new(std::size_t bytes) | calls tracked_malloc_new; returns tracked_malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 49–49](../../../../../tests/unit/candidates_exception_test.cpp#L49) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns tracked_malloc_new(bytes); growth new · [reviewed contract](#b0007) |
| [B0008 · 50–53](../../../../../tests/unit/candidates_exception_test.cpp#L50) | Callable definition: void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept | calls tracked_malloc_new; returns tracked_malloc_new(bytes); nullptr; growth new · [reviewed contract](#b0008) |
| [B0009 · 54–57](../../../../../tests/unit/candidates_exception_test.cpp#L54) | Callable definition: void* operator new\[\](std::size_t bytes, const std::nothrow_t&) noexcept | calls ; returns tracked_malloc_new(bytes); nullptr; growth new · [reviewed contract](#b0009) |
| [B0010 · 58–58](../../../../../tests/unit/candidates_exception_test.cpp#L58) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0010) |
| [B0011 · 59–59](../../../../../tests/unit/candidates_exception_test.cpp#L59) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0011) |
| [B0012 · 60–60](../../../../../tests/unit/candidates_exception_test.cpp#L60) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0012) |
| [B0013 · 61–61](../../../../../tests/unit/candidates_exception_test.cpp#L61) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0013) |
| [B0014 · 62–62](../../../../../tests/unit/candidates_exception_test.cpp#L62) | Callable definition: void operator delete(void* pointer, const std::nothrow_t&) noexcept | calls std::free · [reviewed contract](#b0014) |
| [B0015 · 63–63](../../../../../tests/unit/candidates_exception_test.cpp#L63) | Callable definition: void operator delete\[\](void* pointer, const std::nothrow_t&) noexcept | calls  · [reviewed contract](#b0015) |
| [B0016 · 64–73](../../../../../tests/unit/candidates_exception_test.cpp#L64) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_destructible_v&lt;MinimumHeightCandidate&gt;); · [reviewed contract](#b0016) |
| [B0017 · 74–76](../../../../../tests/unit/candidates_exception_test.cpp#L74) | Callable definition: void check(bool condition, const char* message) | calls std::runtime_error; guard void check(bool condition, const char* message) { · [reviewed contract](#b0017) |
| [B0018 · 77–79](../../../../../tests/unit/candidates_exception_test.cpp#L77) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0018) |
| [B0019 · 80–83](../../../../../tests/unit/candidates_exception_test.cpp#L80) | Type/record definition: struct Fixture |  · [reviewed contract](#b0019) |
| [B0020 · 84–84](../../../../../tests/unit/candidates_exception_test.cpp#L84) | Explanatory comments or spacing. |  |
| [B0021 · 85–109](../../../../../tests/unit/candidates_exception_test.cpp#L85) | Callable definition: Fixture scoped_fixture(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& scopes, const std::vector&lt;std::size_t&gt;& head) | calls names, begin, end, insert; returns fixture; growth emplace_back, insert, push_back, reserve; 5 loop sites · [reviewed contract](#b0021) |
| [B0022 · 110–110](../../../../../tests/unit/candidates_exception_test.cpp#L110) | Explanatory comments or spacing. |  |
| [B0023 · 111–117](../../../../../tests/unit/candidates_exception_test.cpp#L111) | Callable definition: VerifiedOptimum prove(const Fixture& fixture) | calls ExactSearch::create, advance, check, optimum; guard check(result.progress.result == ResultKind::verified_optimum && owner.optimum().has_value(),; returns *owner.optimum() · [reviewed contract](#b0023) |
| [B0024 · 118–118](../../../../../tests/unit/candidates_exception_test.cpp#L118) | Explanatory comments or spacing. |  |
| [B0025 · 119–130](../../../../../tests/unit/candidates_exception_test.cpp#L119) | Callable definition: bool same_constraint(const Constraint& left, const Constraint& right) | calls index; returns false; a-&gt;name == b.name && a-&gt;columns == b.columns && a-&gt;status == b.status · [reviewed contract](#b0025) |
| [B0026 · 131–131](../../../../../tests/unit/candidates_exception_test.cpp#L131) | Explanatory comments or spacing. |  |
| [B0027 · 132–162](../../../../../tests/unit/candidates_exception_test.cpp#L132) | Callable definition: bool same_catalog(const Catalog& left, const Catalog& right) | calls size, same_constraint; returns false; false; 5 loop sites · [reviewed contract](#b0027) |
| [B0028 · 163–163](../../../../../tests/unit/candidates_exception_test.cpp#L163) | Explanatory comments or spacing. |  |
| [B0029 · 164–171](../../../../../tests/unit/candidates_exception_test.cpp#L164) | Callable definition: bool same_term(const Term& left, const Term& right) | calls index; returns false; *variable == std::get&lt;VariableId&gt;(right) · [reviewed contract](#b0029) |
| [B0030 · 172–172](../../../../../tests/unit/candidates_exception_test.cpp#L172) | Explanatory comments or spacing. |  |
| [B0031 · 173–191](../../../../../tests/unit/candidates_exception_test.cpp#L173) | Callable definition: bool same_query(const Query& left, const Query& right) | calls size, same_term; returns false; false; 4 loop sites · [reviewed contract](#b0031) |
| [B0032 · 192–192](../../../../../tests/unit/candidates_exception_test.cpp#L192) | Explanatory comments or spacing. |  |
| [B0033 · 193–204](../../../../../tests/unit/candidates_exception_test.cpp#L193) | Callable definition: bool same_tree(const FreeConnexTree& left, const FreeConnexTree& right) | calls size; returns false; false; 1 loop sites · [reviewed contract](#b0033) |
| [B0034 · 205–205](../../../../../tests/unit/candidates_exception_test.cpp#L205) | Explanatory comments or spacing. |  |
| [B0035 · 206–218](../../../../../tests/unit/candidates_exception_test.cpp#L206) | Callable definition: bool same_certificate(const HeightCertificate& left, const HeightCertificate& right) | calls has_value, size, same_tree; returns false; false; 1 loop sites · [reviewed contract](#b0035) |
| [B0036 · 219–219](../../../../../tests/unit/candidates_exception_test.cpp#L219) | Explanatory comments or spacing. |  |
| [B0037 · 220–237](../../../../../tests/unit/candidates_exception_test.cpp#L220) | Callable definition: bool same_layer(const ResidualLayer& a, const ResidualLayer& b) | calls size; returns false; false; 3 loop sites · [reviewed contract](#b0037) |
| [B0038 · 238–238](../../../../../tests/unit/candidates_exception_test.cpp#L238) | Explanatory comments or spacing. |  |
| [B0039 · 239–244](../../../../../tests/unit/candidates_exception_test.cpp#L239) | Callable definition: bool same_residual_view(const ResidualView& a, const ResidualView& b) | calls same_query; returns a.original_occurrences == b.original_occurrences && · [reviewed contract](#b0039) |
| [B0040 · 245–245](../../../../../tests/unit/candidates_exception_test.cpp#L245) | Explanatory comments or spacing. |  |
| [B0041 · 246–254](../../../../../tests/unit/candidates_exception_test.cpp#L246) | Callable definition: bool same_residual_record(const ResidualTraceRecord& a, const ResidualTraceRecord& b) | calls size, same_residual_view, same_layer; returns false; false; 1 loop sites · [reviewed contract](#b0041) |
| [B0042 · 255–255](../../../../../tests/unit/candidates_exception_test.cpp#L255) | Explanatory comments or spacing. |  |
| [B0043 · 256–259](../../../../../tests/unit/candidates_exception_test.cpp#L256) | Callable definition: bool same_residual_trace(const ResidualTrace& a, const ResidualTrace& b) | calls valid, same_catalog, catalog, same_query; returns a.valid() && b.valid() && same_catalog(a.catalog(), b.catalog()) && · [reviewed contract](#b0043) |
| [B0044 · 260–260](../../../../../tests/unit/candidates_exception_test.cpp#L260) | Explanatory comments or spacing. |  |
| [B0045 · 261–265](../../../../../tests/unit/candidates_exception_test.cpp#L261) | Callable definition: bool same_context(const CandidateContext& a, const CandidateContext& b) | calls ; returns a.updates == b.updates && a.arithmetic == b.arithmetic && a.planner == b.planner && · [reviewed contract](#b0045) |
| [B0046 · 266–266](../../../../../tests/unit/candidates_exception_test.cpp#L266) | Explanatory comments or spacing. |  |
| [B0047 · 267–272](../../../../../tests/unit/candidates_exception_test.cpp#L267) | Callable definition: bool same_provenance(const CandidateProvenance& a, const CandidateProvenance& b) | calls has_value, same_residual_trace; returns false; !a.residual_trace \|\| same_residual_trace(*a.residual_trace, *b.residual_trace) · [reviewed contract](#b0047) |
| [B0048 · 273–273](../../../../../tests/unit/candidates_exception_test.cpp#L273) | Explanatory comments or spacing. |  |
| [B0049 · 274–284](../../../../../tests/unit/candidates_exception_test.cpp#L274) | Callable definition: bool same_candidate(const MinimumHeightCandidate& a, const MinimumHeightCandidate& b) | calls valid, same_catalog, catalog, same_query; returns false; a_proof.valid() && b_proof.valid() && · [reviewed contract](#b0049) |
| [B0050 · 285–285](../../../../../tests/unit/candidates_exception_test.cpp#L285) | Explanatory comments or spacing. |  |
| [B0051 · 286–292](../../../../../tests/unit/candidates_exception_test.cpp#L286) | Type/record definition: struct ProofValue |  · [reviewed contract](#b0051) |
| [B0052 · 293–293](../../../../../tests/unit/candidates_exception_test.cpp#L293) | Explanatory comments or spacing. |  |
| [B0053 · 294–297](../../../../../tests/unit/candidates_exception_test.cpp#L294) | Callable definition: ProofValue proof_value(const VerifiedOptimum& proof) | calls binding, catalog, query, certificate; returns {binding.catalog(), binding.query(), proof.certificate(), proof.upper().tree(), proof.height()} · [reviewed contract](#b0053) |
| [B0054 · 298–298](../../../../../tests/unit/candidates_exception_test.cpp#L298) | Explanatory comments or spacing. |  |
| [B0055 · 299–305](../../../../../tests/unit/candidates_exception_test.cpp#L299) | Callable definition: bool same_proof_value(const VerifiedOptimum& proof, const ProofValue& value) | calls valid, height, same_certificate, certificate; returns false; same_catalog(binding.catalog(), value.catalog) && same_query(binding.query(), value.query) · [reviewed contract](#b0055) |
| [B0056 · 306–306](../../../../../tests/unit/candidates_exception_test.cpp#L306) | Explanatory comments or spacing. |  |
| [B0057 · 307–316](../../../../../tests/unit/candidates_exception_test.cpp#L307) | Type/record definition: struct ResidualValue |  · [reviewed contract](#b0057) |
| [B0058 · 317–317](../../../../../tests/unit/candidates_exception_test.cpp#L317) | Explanatory comments or spacing. |  |
| [B0059 · 318–322](../../../../../tests/unit/candidates_exception_test.cpp#L318) | Callable definition: ResidualValue residual_value(const ResidualCandidate& candidate) | calls trace, catalog, query, tree; returns {candidate.catalog(), candidate.query(), candidate.tree(), candidate.height(), candidate.origin(), · [reviewed contract](#b0059) |
| [B0060 · 323–323](../../../../../tests/unit/candidates_exception_test.cpp#L323) | Explanatory comments or spacing. |  |
| [B0061 · 324–331](../../../../../tests/unit/candidates_exception_test.cpp#L324) | Callable definition: bool same_residual_value(const ResidualCandidate& candidate, const ResidualValue& value) | calls valid, height, origin, same_catalog; returns false; same_catalog(trace.catalog(), value.trace_catalog) && · [reviewed contract](#b0061) |
| [B0062 · 332–332](../../../../../tests/unit/candidates_exception_test.cpp#L332) | Explanatory comments or spacing. |  |
| [B0063 · 333–342](../../../../../tests/unit/candidates_exception_test.cpp#L333) | Type/record definition: struct ProvenanceValue |  · [reviewed contract](#b0063) |
| [B0064 · 343–343](../../../../../tests/unit/candidates_exception_test.cpp#L343) | Explanatory comments or spacing. |  |
| [B0065 · 344–353](../../../../../tests/unit/candidates_exception_test.cpp#L344) | Callable definition: ProvenanceValue provenance_value(const CandidateProvenance& provenance) | calls has_value, catalog, query, record; returns value · [reviewed contract](#b0065) |
| [B0066 · 354–354](../../../../../tests/unit/candidates_exception_test.cpp#L354) | Explanatory comments or spacing. |  |
| [B0067 · 355–363](../../../../../tests/unit/candidates_exception_test.cpp#L355) | Callable definition: bool same_provenance_value(const CandidateProvenance& provenance, const ProvenanceValue& value) | calls has_value, same_catalog, catalog, same_query; returns false; true · [reviewed contract](#b0067) |
| [B0068 · 364–364](../../../../../tests/unit/candidates_exception_test.cpp#L364) | Explanatory comments or spacing. |  |
| [B0069 · 365–374](../../../../../tests/unit/candidates_exception_test.cpp#L365) | Type/record definition: struct CandidateValue |  · [reviewed contract](#b0069) |
| [B0070 · 375–375](../../../../../tests/unit/candidates_exception_test.cpp#L375) | Explanatory comments or spacing. |  |
| [B0071 · 376–381](../../../../../tests/unit/candidates_exception_test.cpp#L376) | Callable definition: CandidateValue candidate_value(const MinimumHeightCandidate& candidate) | calls original_proof, catalog, query, tree; returns {candidate.catalog(), candidate.query(), candidate.tree(), candidate.height(), · [reviewed contract](#b0071) |
| [B0072 · 382–382](../../../../../tests/unit/candidates_exception_test.cpp#L382) | Explanatory comments or spacing. |  |
| [B0073 · 383–390](../../../../../tests/unit/candidates_exception_test.cpp#L383) | Callable definition: bool same_candidate_value(const MinimumHeightCandidate& candidate, const CandidateValue& value) | calls valid, height, structural_key, same_catalog; returns false; same_proof_value(candidate.original_proof(), value.proof) · [reviewed contract](#b0073) |
| [B0074 · 391–391](../../../../../tests/unit/candidates_exception_test.cpp#L391) | Explanatory comments or spacing. |  |
| [B0075 · 392–398](../../../../../tests/unit/candidates_exception_test.cpp#L392) | Type/record definition: struct SnapshotValue |  · [reviewed contract](#b0075) |
| [B0076 · 399–399](../../../../../tests/unit/candidates_exception_test.cpp#L399) | Explanatory comments or spacing. |  |
| [B0077 · 400–413](../../../../../tests/unit/candidates_exception_test.cpp#L400) | Callable definition: SnapshotValue snapshot_value(const CandidateSnapshot& snapshot) | calls family_exhausted, family, context, proof_value; guard check(candidate.has_value(), "snapshot value capture lost an indexed candidate");; returns value; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0077) |
| [B0078 · 414–414](../../../../../tests/unit/candidates_exception_test.cpp#L414) | Explanatory comments or spacing. |  |
| [B0079 · 415–425](../../../../../tests/unit/candidates_exception_test.cpp#L415) | Callable definition: bool same_snapshot_value(const CandidateSnapshot& snapshot, const SnapshotValue& value) | calls valid, candidate_count, size, family_exhausted; returns false; false; 1 loop sites · [reviewed contract](#b0079) |
| [B0080 · 426–426](../../../../../tests/unit/candidates_exception_test.cpp#L426) | Explanatory comments or spacing. |  |
| [B0081 · 427–434](../../../../../tests/unit/candidates_exception_test.cpp#L427) | Callable definition: bool same_provider_prefix_value(const CandidateProvider& owner, const SnapshotValue& value) | calls candidate_count, size, candidate, same_candidate_value; returns false; false; 1 loop sites · [reviewed contract](#b0081) |
| [B0082 · 435–435](../../../../../tests/unit/candidates_exception_test.cpp#L435) | Explanatory comments or spacing. |  |
| [B0083 · 436–441](../../../../../tests/unit/candidates_exception_test.cpp#L436) | Callable definition: bool same_stats(const CandidateStatistics& a, const CandidateStatistics& b) | calls ; returns a.proposed == b.proposed && a.rejected == b.rejected && a.taller == b.taller && · [reviewed contract](#b0083) |
| [B0084 · 442–442](../../../../../tests/unit/candidates_exception_test.cpp#L442) | Explanatory comments or spacing. |  |
| [B0085 · 443–446](../../../../../tests/unit/candidates_exception_test.cpp#L443) | Callable definition: bool same_work_except_faults(const WorkCounters& a, const WorkCounters& b) | calls ; returns a.committed_transitions == b.committed_transitions && · [reviewed contract](#b0085) |
| [B0086 · 447–447](../../../../../tests/unit/candidates_exception_test.cpp#L447) | Explanatory comments or spacing. |  |
| [B0087 · 448–454](../../../../../tests/unit/candidates_exception_test.cpp#L448) | Callable definition: bool same_progress_except_faults(const CandidateProgress& a, const CandidateProgress& b) | calls same_work_except_faults, same_stats; returns a.phase == b.phase && a.last_stop == b.last_stop && a.family == b.family && · [reviewed contract](#b0087) |
| [B0088 · 455–455](../../../../../tests/unit/candidates_exception_test.cpp#L455) | Explanatory comments or spacing. |  |
| [B0089 · 456–462](../../../../../tests/unit/candidates_exception_test.cpp#L456) | Callable definition: bool same_pending_progress(const CandidateProgress& a, const CandidateProgress& b) | calls same_work_except_faults, same_stats; returns a.phase == b.phase && a.family == b.family && · [reviewed contract](#b0089) |
| [B0090 · 463–463](../../../../../tests/unit/candidates_exception_test.cpp#L463) | Explanatory comments or spacing. |  |
| [B0091 · 464–472](../../../../../tests/unit/candidates_exception_test.cpp#L464) | Callable definition: bool same_published(const CandidateProvider& owner, const CandidateSnapshot& expected) | calls candidate_count, candidate, same_candidate; returns false; false; 1 loop sites · [reviewed contract](#b0091) |
| [B0092 · 473–473](../../../../../tests/unit/candidates_exception_test.cpp#L473) | Explanatory comments or spacing. |  |
| [B0093 · 474–482](../../../../../tests/unit/candidates_exception_test.cpp#L474) | Callable definition: bool same_published_prefix(const CandidateProvider& owner, const CandidateSnapshot& expected) | calls candidate_count, candidate, same_candidate; returns false; false; 1 loop sites · [reviewed contract](#b0093) |
| [B0094 · 483–483](../../../../../tests/unit/candidates_exception_test.cpp#L483) | Explanatory comments or spacing. |  |
| [B0095 · 484–491](../../../../../tests/unit/candidates_exception_test.cpp#L484) | Type/record definition: struct GeneratorState |  · [reviewed contract](#b0095) |
| [B0096 · 492–492](../../../../../tests/unit/candidates_exception_test.cpp#L492) | Explanatory comments or spacing. |  |
| [B0097 · 493–497](../../../../../tests/unit/candidates_exception_test.cpp#L493) | Callable definition: bool same_generator_stats(const ap::GeneratorStatistics& a, const ap::GeneratorStatistics& b) | calls ; returns a.completed_steps == b.completed_steps && a.topologies_examined == b.topologies_examined && · [reviewed contract](#b0097) |
| [B0098 · 498–498](../../../../../tests/unit/candidates_exception_test.cpp#L498) | Explanatory comments or spacing. |  |
| [B0099 · 499–503](../../../../../tests/unit/candidates_exception_test.cpp#L499) | Callable definition: GeneratorState generator_state(const ap::NormalFormGenerator& generator, const std::shared_ptr&lt;ap::ContentBudget&gt;& budget) | calls statistics, records, cells, current_depth; returns {generator.statistics(), budget-&gt;records(), budget-&gt;cells(), generator.current_depth(), · [reviewed contract](#b0099) |
| [B0100 · 504–504](../../../../../tests/unit/candidates_exception_test.cpp#L504) | Explanatory comments or spacing. |  |
| [B0101 · 505–508](../../../../../tests/unit/candidates_exception_test.cpp#L505) | Callable definition: bool same_generator_state(const GeneratorState& a, const GeneratorState& b) | calls same_generator_stats; returns same_generator_stats(a.stats, b.stats) && a.records == b.records && a.cells == b.cells && · [reviewed contract](#b0101) |
| [B0102 · 509–509](../../../../../tests/unit/candidates_exception_test.cpp#L509) | Explanatory comments or spacing. |  |
| [B0103 · 510–516](../../../../../tests/unit/candidates_exception_test.cpp#L510) | Type/record definition: struct GeneratorRun |  · [reviewed contract](#b0103) |
| [B0104 · 517–517](../../../../../tests/unit/candidates_exception_test.cpp#L517) | Explanatory comments or spacing. |  |
| [B0105 · 518–533](../../../../../tests/unit/candidates_exception_test.cpp#L518) | Callable definition: void append_ready_draft(ap::NormalFormGenerator& generator, const std::shared_ptr&lt;ap::ContentBudget&gt;& budget, std::vector&lt;std::sh… | calls draft, check, size, capacity; guard check(static_cast&lt;bool&gt;(retained), "generator ready event did not expose a retained draft");; growth push_back; 1 loop sites · [reviewed contract](#b0105) |
| [B0106 · 534–534](../../../../../tests/unit/candidates_exception_test.cpp#L534) | Explanatory comments or spacing. |  |
| [B0107 · 535–547](../../../../../tests/unit/candidates_exception_test.cpp#L535) | Callable definition: bool generator_result(ap::NormalFormGenerator& generator, const std::shared_ptr&lt;ap::ContentBudget&gt;& budget, std::vector&lt;std::shar… | calls append_ready_draft, check; guard check(result.event == ap::GeneratorEvent::advanced,; returns false; true · [reviewed contract](#b0107) |
| [B0108 · 548–548](../../../../../tests/unit/candidates_exception_test.cpp#L548) | Explanatory comments or spacing. |  |
| [B0109 · 549–559](../../../../../tests/unit/candidates_exception_test.cpp#L549) | Callable definition: bool drain_generator(ap::NormalFormGenerator& generator, const std::shared_ptr&lt;ap::ContentBudget&gt;& budget, std::vector&lt;std::share… | calls generator_result, step; returns true; false; 1 loop sites · [reviewed contract](#b0109) |
| [B0110 · 560–560](../../../../../tests/unit/candidates_exception_test.cpp#L560) | Explanatory comments or spacing. |  |
| [B0111 · 561–571](../../../../../tests/unit/candidates_exception_test.cpp#L561) | Callable definition: bool same_generator_run(const ap::NormalFormGenerator& generator, const std::shared_ptr&lt;ap::ContentBudget&gt;& budget, const std::ve… | calls size, same_generator_stats, statistics, records; returns false; false; 1 loop sites · [reviewed contract](#b0111) |
| [B0112 · 572–572](../../../../../tests/unit/candidates_exception_test.cpp#L572) | Explanatory comments or spacing. |  |
| [B0113 · 573–592](../../../../../tests/unit/candidates_exception_test.cpp#L573) | Callable definition: GeneratorRun baseline_generator(const std::shared_ptr&lt;const cd::BindingData&gt;& binding) | calls generator, reserve, check, drain_generator; guard check(drain_generator(generator, budget, result.drafts, calls),; returns result; growth make_shared, reserve · [reviewed contract](#b0113) |
| [B0114 · 593–593](../../../../../tests/unit/candidates_exception_test.cpp#L593) | Explanatory comments or spacing. |  |
| [B0115 · 594–636](../../../../../tests/unit/candidates_exception_test.cpp#L594) | Callable definition: void generator_faults(const std::shared_ptr&lt;const cd::BindingData&gt;& binding, const GeneratorRun& expected) | calls check, max, generator, reserve; guard check(expected.allocations &lt;= static_cast&lt;std::size_t&gt;(std::numeric_limits&lt;std::ptrdiff_t&gt;::max()),; growth make_shared, reserve; 3 loop sites · [reviewed contract](#b0115) |
| [B0116 · 637–637](../../../../../tests/unit/candidates_exception_test.cpp#L637) | Explanatory comments or spacing. |  |
| [B0117 · 638–703](../../../../../tests/unit/candidates_exception_test.cpp#L638) | Callable definition: void generator_caps_and_cancel(const std::shared_ptr&lt;const cd::BindingData&gt;& binding, const GeneratorRun& expected) | calls generator, reserve, generator_state, step; guard check(again.event == ap::GeneratorEvent::stopped &&; growth make_shared, reserve; 3 loop sites · [reviewed contract](#b0117) |
| [B0118 · 704–704](../../../../../tests/unit/candidates_exception_test.cpp#L704) | Explanatory comments or spacing. |  |
| [B0119 · 705–713](../../../../../tests/unit/candidates_exception_test.cpp#L705) | Callable definition: void finish_key(ap::StructuralKeyMachine& machine) | calls step, check; guard check(result.event != ap::KeyEvent::stopped,; 1 loop sites · [reviewed contract](#b0119) |
| [B0120 · 714–714](../../../../../tests/unit/candidates_exception_test.cpp#L714) | Explanatory comments or spacing. |  |
| [B0121 · 715–718](../../../../../tests/unit/candidates_exception_test.cpp#L715) | Callable definition: bool same_key_stats(const ap::KeyStatistics& a, const ap::KeyStatistics& b) | calls ; returns a.completed_steps == b.completed_steps && a.completed_nodes == b.completed_nodes && · [reviewed contract](#b0121) |
| [B0122 · 719–719](../../../../../tests/unit/candidates_exception_test.cpp#L719) | Explanatory comments or spacing. |  |
| [B0123 · 720–726](../../../../../tests/unit/candidates_exception_test.cpp#L720) | Type/record definition: struct KeyRun |  · [reviewed contract](#b0123) |
| [B0124 · 727–727](../../../../../tests/unit/candidates_exception_test.cpp#L727) | Explanatory comments or spacing. |  |
| [B0125 · 728–737](../../../../../tests/unit/candidates_exception_test.cpp#L728) | Callable definition: KeyRun baseline_key(const std::shared_ptr&lt;const FreeConnexTree&gt;& tree) | calls machine, finish_key, key, statistics; guard check(result.key && result.allocations != 0,; returns result; growth make_shared · [reviewed contract](#b0125) |
| [B0126 · 738–738](../../../../../tests/unit/candidates_exception_test.cpp#L738) | Explanatory comments or spacing. |  |
| [B0127 · 739–774](../../../../../tests/unit/candidates_exception_test.cpp#L739) | Callable definition: void key_faults(const std::shared_ptr&lt;const FreeConnexTree&gt;& tree, const KeyRun& expected) | calls check, max, machine, fault; guard check(expected.allocations &lt;= static_cast&lt;std::size_t&gt;(std::numeric_limits&lt;std::ptrdiff_t&gt;::max()),; growth make_shared; 2 loop sites · [reviewed contract](#b0127) |
| [B0128 · 775–775](../../../../../tests/unit/candidates_exception_test.cpp#L775) | Explanatory comments or spacing. |  |
| [B0129 · 776–814](../../../../../tests/unit/candidates_exception_test.cpp#L776) | Callable definition: void key_caps_and_cancel(const std::shared_ptr&lt;const FreeConnexTree&gt;& tree, const KeyRun& expected) | calls machine, step, check, current_depth; guard check(zero.event == ap::KeyEvent::stopped && zero.reason == ap::KeyStop::depth_limit &&; growth make_shared; 1 loop sites · [reviewed contract](#b0129) |
| [B0130 · 815–815](../../../../../tests/unit/candidates_exception_test.cpp#L815) | Explanatory comments or spacing. |  |
| [B0131 · 816–825](../../../../../tests/unit/candidates_exception_test.cpp#L816) | Callable definition: CandidateStop drain(CandidateProvider& owner, std::uint64_t quantum = std::numeric_limits&lt;std::uint64_t&gt;::max()) | calls max, advance, std::runtime_error; returns result.stopped_for; 1 loop sites · [reviewed contract](#b0131) |
| [B0132 · 826–826](../../../../../tests/unit/candidates_exception_test.cpp#L826) | Explanatory comments or spacing. |  |
| [B0133 · 827–830](../../../../../tests/unit/candidates_exception_test.cpp#L827) | Type/record definition: struct CandidateRun |  · [reviewed contract](#b0133) |
| [B0134 · 831–831](../../../../../tests/unit/candidates_exception_test.cpp#L831) | Explanatory comments or spacing. |  |
| [B0135 · 832–841](../../../../../tests/unit/candidates_exception_test.cpp#L832) | Callable definition: CandidateRun baseline_provider(CandidateProvider& owner) | calls drain, check, progress; guard check(stop == CandidateStop::exhausted,; returns {owner.progress(), allocations} · [reviewed contract](#b0135) |
| [B0136 · 842–842](../../../../../tests/unit/candidates_exception_test.cpp#L842) | Explanatory comments or spacing. |  |
| [B0137 · 843–850](../../../../../tests/unit/candidates_exception_test.cpp#L843) | Callable definition: void compare_provider(const CandidateProvider& actual, const CandidateRun& expected, const CandidateSnapshot& expected_snapshot) | calls progress, check, same_progress_except_faults, same_published; guard check(same_progress_except_faults(progress, expected.progress), · [reviewed contract](#b0137) |
| [B0138 · 851–851](../../../../../tests/unit/candidates_exception_test.cpp#L851) | Explanatory comments or spacing. |  |
| [B0139 · 852–893](../../../../../tests/unit/candidates_exception_test.cpp#L852) | Callable definition: void provider_faults(const VerifiedOptimum& proof, const CandidateRun& expected, const CandidateSnapshot& expected_snapshot) | calls snapshot_value, check, max, CandidateProvider::create; guard check(expected.allocations &lt;= static_cast&lt;std::size_t&gt;(std::numeric_limits&lt;std::ptrdiff_t&gt;::max()),; 2 loop sites · [reviewed contract](#b0139) |
| [B0140 · 894–894](../../../../../tests/unit/candidates_exception_test.cpp#L894) | Explanatory comments or spacing. |  |
| [B0141 · 895–933](../../../../../tests/unit/candidates_exception_test.cpp#L895) | Callable definition: void factory_admission_faults(const VerifiedOptimum& proof, const CandidateSnapshot& retained_snapshot) | calls proof_value, snapshot_value, CandidateProvider::create, check; guard check(sample.progress().phase == CandidatePhase::exact_seed &&; 2 loop sites · [reviewed contract](#b0141) |
| [B0142 · 934–934](../../../../../tests/unit/candidates_exception_test.cpp#L934) | Explanatory comments or spacing. |  |
| [B0143 · 935–972](../../../../../tests/unit/candidates_exception_test.cpp#L935) | Callable definition: void snapshot_admission_faults(CandidateProvider& owner, const CandidateSnapshot& expected) | calls snapshot_value, snapshot, check, same_snapshot_value; guard check(same_snapshot_value(sample, expected_value),; 2 loop sites · [reviewed contract](#b0143) |
| [B0144 · 973–973](../../../../../tests/unit/candidates_exception_test.cpp#L973) | Explanatory comments or spacing. |  |
| [B0145 · 974–1055](../../../../../tests/unit/candidates_exception_test.cpp#L974) | Callable definition: void provider_caps_and_cancel(const VerifiedOptimum& proof, const CandidateRun& baseline, const CandidateSnapshot& expected_snaps… | calls reset, CandidateProvider::create, drain, check; guard check(stop == expected_stop && !owner.progress().family_exhausted,; returns limits; 1 loop sites · [reviewed contract](#b0145) |
| [B0146 · 1056–1056](../../../../../tests/unit/candidates_exception_test.cpp#L1056) | Explanatory comments or spacing. |  |
| [B0147 · 1057–1158](../../../../../tests/unit/candidates_exception_test.cpp#L1057) | Callable definition: void optional_seed_path_faults(const VerifiedOptimum& proof, const ResidualCandidate& residual, const CandidateSnapshot& prefix) | calls proof_value, residual_value, snapshot_value, CandidateProvider::create; guard check(stop == CandidateStop::exhausted && owner.progress().family_exhausted &&; 5 loop sites; source comment (unverified): // Full factory-admission sweeps include copies/serialization of both optional · [reviewed contract](#b0147) |
| [B0148 · 1159–1159](../../../../../tests/unit/candidates_exception_test.cpp#L1159) | Explanatory comments or spacing. |  |
| [B0149 · 1160–1162](../../../../../tests/unit/candidates_exception_test.cpp#L1160) | Callable definition: CandidateCacheStatistics cache_stats(const CandidateCache& cache) | calls statistics; returns cache.statistics() · [reviewed contract](#b0149) |
| [B0150 · 1163–1163](../../../../../tests/unit/candidates_exception_test.cpp#L1163) | Explanatory comments or spacing. |  |
| [B0151 · 1164–1167](../../../../../tests/unit/candidates_exception_test.cpp#L1164) | Callable definition: bool same_cache_stats(const CandidateCacheStatistics& a, const CandidateCacheStatistics& b) | calls ; returns a.hits == b.hits && a.misses == b.misses && a.insertions == b.insertions && · [reviewed contract](#b0151) |
| [B0152 · 1168–1168](../../../../../tests/unit/candidates_exception_test.cpp#L1168) | Explanatory comments or spacing. |  |
| [B0153 · 1169–1176](../../../../../tests/unit/candidates_exception_test.cpp#L1169) | Callable definition: CandidateSnapshot first_snapshot(const VerifiedOptimum& proof) | calls CandidateProvider::create, check, advance, snapshot; guard check(owner.advance(all_work).stopped_for == CandidateStop::candidate_ready,; returns owner.snapshot() · [reviewed contract](#b0153) |
| [B0154 · 1177–1177](../../../../../tests/unit/candidates_exception_test.cpp#L1177) | Explanatory comments or spacing. |  |
| [B0155 · 1178–1278](../../../../../tests/unit/candidates_exception_test.cpp#L1178) | Callable definition: void cache_install_faults(const VerifiedOptimum& a_proof, const VerifiedOptimum& b_proof, const VerifiedOptimum& c_proof, const C… | calls snapshot_value, CandidateCache::create, check, install; guard check(replacement.install(a_full) == CandidateCacheInstall::inserted &&; returns allocation_count; 2 loop sites; source comment (unverified): // Replacing a matching immutable snapshot cannot allocate; it keeps the old · [reviewed contract](#b0155) |
| [B0156 · 1279–1281](../../../../../tests/unit/candidates_exception_test.cpp#L1279) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0156) |
| [B0157 · 1282–1355](../../../../../tests/unit/candidates_exception_test.cpp#L1282) | Callable definition: int main() | calls scoped_fixture, prove, check, height; guard check(proof.height() == 2, "Boolean fault fixture minimum was not two");; returns 1; growth make_shared, resize; 1 loop sites · [reviewed contract](#b0157) |

## B0001

[Lines 1–29](../../../../../tests/unit/candidates_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L29:sha256:f487f2be4adb75d789564f39c6ac5498e4fafb87f25e01a058ca6139c179a71d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare candidates_exception_test.cpp: include "crown/planner/candidates.hpp", "crown/planner/search.hpp", "crown/planner/verify.hpp", "candidate_key.hpp", "candidate_machine.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;variant&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 30–38](../../../../../tests/unit/candidates_exception_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* tracked_malloc_new(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count each call through the replaced ordinary C++ allocation family, inject the selected failure, and back admitted storage with malloc. |
| inputs / outputs | Requested bytes, thread-local fail_after and allocation_count enter; the count advances, then malloc(bytes or one byte) returns storage or bad_alloc escapes. |
| invariants | A zero fail_after rejects before malloc; a positive value is decremented before malloc; disabled injection leaves fail_after negative; a real malloc null also becomes bad_alloc. |
| ownership | The function borrows only thread-local scalar state. Returned storage belongs to the replacement allocation family and is released by this executable’s matching delete overloads. |
| failure | The configured point injects a C++ allocation failure; the underlying malloc call is not separately faulted. Direct malloc/realloc callers, aligned allocation overloads and operating-system calls are outside this seam. |
| cost | One counter increment and branch plus one malloc attempt for an admitted request; this is a request count, not requested-byte, MemoryAccount, RSS or syscall accounting. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0004

[Lines 40–45](../../../../../tests/unit/candidates_exception_test.cpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scope one thread-local fail-after position around an allocation sweep attempt. |
| inputs / outputs | A signed point sets fail_after at construction; destruction resets it to disabled (-1). |
| invariants | Copy and assignment are deleted; destruction always disables injection rather than restoring an enclosing point. |
| ownership | Owns no allocated product state and borrows only the thread-local fail_after scalar. |
| failure | Construction and destruction are noexcept and do not inject into malloc directly; nested scopes are not a save/restore stack. |
| cost | Constant time and scalar storage. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp) |

## B0005

[Lines 46–47](../../../../../tests/unit/candidates_exception_test.cpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L47:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in candidates_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 48–48](../../../../../tests/unit/candidates_exception_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return tracked_malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route scalar ordinary operator new calls through tracked_malloc_new. |
| inputs / outputs | A byte count enters; malloc-backed storage or std::bad_alloc exits. |
| invariants | Each call is counted before the selected fail point; zero-sized requests are normalized in the common seam. |
| ownership | Storage is freed by this file’s replacement scalar delete. |
| failure | Only calls dispatched through this replaced scalar operator new are injected; raw malloc and syscalls are outside. |
| cost | One seam call and one malloc attempt if admitted; no account-byte inference. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0007

[Lines 49–49](../../../../../tests/unit/candidates_exception_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return tracked_malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route array ordinary operator new\[\] calls through tracked_malloc_new. |
| inputs / outputs | An array byte count enters; malloc-backed storage or std::bad_alloc exits. |
| invariants | Uses the same thread-local position and request counter as scalar new. |
| ownership | Storage is freed by the replacement array delete. |
| failure | The injection is at the C++ new\[\] boundary; it is not a raw malloc or system-call failure sweep. |
| cost | One seam call and one malloc attempt if admitted. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0008

[Lines 50–53](../../../../../tests/unit/candidates_exception_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the nothrow scalar allocation overload on the same tracked C++ new seam. |
| inputs / outputs | A scalar allocation size enters; storage exits on success and nullptr exits when tracked_malloc_new throws bad_alloc. |
| invariants | The wrapper catches only std::bad_alloc; the fail index and allocation count remain those maintained by tracked_malloc_new. |
| ownership | Successful storage is released by the matching nothrow scalar delete overload. |
| failure | Injected or real malloc-backed bad_alloc becomes nullptr by this overload; direct malloc calls remain uninjected. |
| cost | One seam call plus a local try/catch; an admitted request performs one malloc attempt. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0009

[Lines 54–57](../../../../../tests/unit/candidates_exception_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes, const std::nothrow_t&) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the nothrow array allocation overload on the same tracked C++ new\[\] seam. |
| inputs / outputs | An array allocation size enters; storage exits on success and nullptr exits when tracked_malloc_new throws bad_alloc. |
| invariants | Catches only std::bad_alloc and shares the ordinary fail-after index and request counter. |
| ownership | Successful storage is released by the matching nothrow array delete overload. |
| failure | This overload translates the seam’s bad_alloc to nullptr; no raw malloc/syscall injection is added. |
| cost | One seam call plus a local try/catch; one malloc attempt when admitted. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0010

[Lines 58–58](../../../../../tests/unit/candidates_exception_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release scalar unsized storage returned by this executable’s malloc-backed replacement allocation family. |
| inputs / outputs | The pointer supplied by the matching scalar allocation/deallocation form enters; no value is returned. |
| invariants | The noexcept body calls std::free on exactly the supplied pointer; no counter or fault index is changed. |
| ownership | The pointer is borrowed for this call and released here; the caller must pass storage from a compatible malloc-backed replacement allocation. |
| failure | The deallocator is noexcept and does not inject a failure; it does not cover unrelated allocations or system resources. |
| cost | One std::free call and no allocation request. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0011

[Lines 59–59](../../../../../tests/unit/candidates_exception_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release array unsized storage returned by this executable’s malloc-backed replacement allocation family. |
| inputs / outputs | The pointer supplied by the matching array allocation/deallocation form enters; no value is returned. |
| invariants | The noexcept body calls std::free on exactly the supplied pointer; no counter or fault index is changed. |
| ownership | The pointer is borrowed for this call and released here; the caller must pass storage from a compatible malloc-backed replacement allocation. |
| failure | The deallocator is noexcept and does not inject a failure; it does not cover unrelated allocations or system resources. |
| cost | One std::free call and no allocation request. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0012

[Lines 60–60](../../../../../tests/unit/candidates_exception_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release scalar sized storage returned by this executable’s malloc-backed replacement allocation family. |
| inputs / outputs | The pointer supplied by the matching scalar allocation/deallocation form enters; no value is returned. |
| invariants | The noexcept body calls std::free on exactly the supplied pointer; no counter or fault index is changed. |
| ownership | The pointer is borrowed for this call and released here; the caller must pass storage from a compatible malloc-backed replacement allocation. |
| failure | The deallocator is noexcept and does not inject a failure; it does not cover unrelated allocations or system resources. |
| cost | One std::free call and no allocation request. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0013

[Lines 61–61](../../../../../tests/unit/candidates_exception_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release array sized storage returned by this executable’s malloc-backed replacement allocation family. |
| inputs / outputs | The pointer supplied by the matching array allocation/deallocation form enters; no value is returned. |
| invariants | The noexcept body calls std::free on exactly the supplied pointer; no counter or fault index is changed. |
| ownership | The pointer is borrowed for this call and released here; the caller must pass storage from a compatible malloc-backed replacement allocation. |
| failure | The deallocator is noexcept and does not inject a failure; it does not cover unrelated allocations or system resources. |
| cost | One std::free call and no allocation request. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0014

[Lines 62–62](../../../../../tests/unit/candidates_exception_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release scalar nothrow matching storage returned by this executable’s malloc-backed replacement allocation family. |
| inputs / outputs | The pointer supplied by the matching scalar allocation/deallocation form enters; no value is returned. |
| invariants | The noexcept body calls std::free on exactly the supplied pointer; no counter or fault index is changed. |
| ownership | The pointer is borrowed for this call and released here; the caller must pass storage from a compatible malloc-backed replacement allocation. |
| failure | The deallocator is noexcept and does not inject a failure; it does not cover unrelated allocations or system resources. |
| cost | One std::free call and no allocation request. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0015

[Lines 63–63](../../../../../tests/unit/candidates_exception_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release array nothrow matching storage returned by this executable’s malloc-backed replacement allocation family. |
| inputs / outputs | The pointer supplied by the matching array allocation/deallocation form enters; no value is returned. |
| invariants | The noexcept body calls std::free on exactly the supplied pointer; no counter or fault index is changed. |
| ownership | The pointer is borrowed for this call and released here; the caller must pass storage from a compatible malloc-backed replacement allocation. |
| failure | The deallocator is noexcept and does not inject a failure; it does not cover unrelated allocations or system resources. |
| cost | One std::free call and no allocation request. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0016

[Lines 64–73](../../../../../tests/unit/candidates_exception_test.cpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L73:sha256:ed2eb330f5d248896b51f038a145d017f1aacac6c5921f467087af01036b741a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare candidates_exception_test.cpp: bind local aliases/name imports; require 2 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 74–76](../../../../../tests/unit/candidates_exception_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const char* message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a false test predicate into a named test failure. |
| inputs / outputs | A condition and borrowed message enter; true returns normally and false throws std::runtime_error. |
| invariants | Assertions are checked at the call site; this helper does not retry the tested operation or convert product errors. |
| ownership | The message pointer is borrowed through runtime_error construction; no reference is returned. |
| failure | False assertions propagate as std::runtime_error; constructing the exception may itself use the replaced global C++ new seam when active. |
| cost | One branch on success; failure constructs and throws the supplied diagnostic. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp) |

## B0018

[Lines 77–79](../../../../../tests/unit/candidates_exception_test.cpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L79:sha256:929c414dff4a792e963b678afea4332ef2578db62d1e885745396df01f703973
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare candidates_exception_test.cpp: declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 80–83](../../../../../tests/unit/candidates_exception_test.cpp#L80); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group the owned Catalog and Query used to build small candidate-search fixtures. |
| inputs / outputs | Default member construction yields mutable catalog and query values for scoped_fixture; no constructor output is borrowed. |
| invariants | The fixture retains both values until the owning Fixture leaves scope. |
| ownership | Catalog and Query own their standard value containers and strings; no source fixture references escape. |
| failure | Their ordinary value construction may throw allocation exceptions; this type adds no failure translation. |
| cost | Value storage proportional to the fixture catalog/query shape. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp) |

## B0021

[Lines 85–109](../../../../../tests/unit/candidates_exception_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture scoped_fixture(const std::vector<std::vector<std::size_t>>& scopes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a deterministic integer catalog/query whose atom scopes and projected head come from index lists. |
| inputs / outputs | Nested scope index vectors and head indices enter by const reference; a Fixture owning Catalog and Query exits. |
| invariants | Variable names are deduplicated and ordered by std::set; IDs follow that order; each scope creates one int64 table/atom pair and head aliases follow head order. |
| ownership | Input vectors are borrowed only during construction; returned Catalog/Query values own names, columns, atoms, terms and head aliases. |
| failure | Invalid scope/head indices surface through ids.at; container/string allocation failures propagate. No exception is translated here. |
| cost | Builds and stores O(number of distinct names + scope entries + head entries) fixture data, plus ordered-set lookups. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp) |

## B0023

[Lines 111–117](../../../../../tests/unit/candidates_exception_test.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VerifiedOptimum prove(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the original P06 verified optimum used as candidate-test input. |
| inputs / outputs | A fixture is borrowed; ExactSearch::create and one all_work advance produce an owning VerifiedOptimum or a test assertion fails. |
| invariants | The helper requires progress.result == verified_optimum and a present owner.optimum(); candidate enumeration is not the exact-search operation under fault. |
| ownership | The fixture remains borrowed during search; the returned proof handle owns/retains the verified original proof after the local search owner leaves scope. |
| failure | Search or allocation errors propagate; a missing verified optimum throws the helper’s std::runtime_error. This helper does not claim a theorem beyond the returned checked proof. |
| cost | Runs the fixture’s exact-search work to completion under the supplied maximum WorkQuantum; no runtime bound is asserted. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [docs/candidate_alternatives.md § Original proof and checked alternatives](../../../../candidate_alternatives.md) |

## B0025

[Lines 119–130](../../../../../tests/unit/candidates_exception_test.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_constraint(const Constraint& left, const Constraint& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare either UniqueConstraint or ForeignKeyConstraint alternatives without cross-alternative access. |
| inputs / outputs | Two Constraint variants enter; variant-index mismatch returns false, otherwise the active alternative’s name, columns, status, and for a foreign key referenced table/columns are compared. |
| invariants | std::get is used only after matching variant indices; equality includes every field explicitly read by this helper. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0027

[Lines 132–162](../../../../../tests/unit/candidates_exception_test.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_catalog(const Catalog& left, const Catalog& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the catalog fields captured by the candidate failure baseline. |
| inputs / outputs | Two Catalog values enter; version, table counts, table metadata, columns, constraints, statistics/distinct counts and key hints determine the bool. |
| invariants | Table/column/constraint/statistics/key-hint vector lengths are checked before indexed comparison; each declared field and typed constraint is compared. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0029

[Lines 164–171](../../../../../tests/unit/candidates_exception_test.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_term(const Term& left, const Term& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the active Term alternative in a query. |
| inputs / outputs | Two Term variants enter; differing variant indices return false, VariableId and Value alternatives compare their values, and the remaining ignored-column alternative compares equal by kind. |
| invariants | Variant access follows an equal index; no display string or normalized-term conversion is used. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0031

[Lines 173–191](../../../../../tests/unit/candidates_exception_test.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_query(const Query& left, const Query& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare complete query structure used by the candidate state oracle. |
| inputs / outputs | Two Query values enter; contradiction flag and vector sizes, variable names/types, ordered atom occurrence/table/terms, and ordered head variable/alias pairs determine the bool. |
| invariants | Nested Term values use same_term; length checks precede indexed loops and head aliases remain order-sensitive. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0033

[Lines 193–204](../../../../../tests/unit/candidates_exception_test.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_tree(const FreeConnexTree& left, const FreeConnexTree& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the stored FreeConnexTree representation used in retry oracles. |
| inputs / outputs | Two trees enter; root, claimed flags/heights, node count and each node’s id/kind/scope/children/occurrence/claimed separator determine the bool. |
| invariants | Node vector order and each stored child/scope sequence are compared exactly; this is representation equality, not a new P02 validation. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0035

[Lines 206–218](../../../../../tests/unit/candidates_exception_test.cpp#L206); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_certificate(const HeightCertificate& left, const HeightCertificate& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the original height certificate retained by a candidate/proof baseline. |
| inputs / outputs | Two certificates enter; algorithm, minimum height, optional tree presence/content and lower-bound count/fields determine the bool. |
| invariants | Optional trees use same_tree; lower-bound occurrence sets and generalized/connex/bound fields are checked in order. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0037

[Lines 220–237](../../../../../tests/unit/candidates_exception_test.cpp#L220); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_layer(const ResidualLayer& a, const ResidualLayer& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one residual trace layer and its ear/deletion evidence. |
| inputs / outputs | Two layers enter; members, variables, head, unique, ear/deletion counts, remaining and residual head plus each listed ear anchor and deletion determine the bool. |
| invariants | Sizes are checked before indexed loops; anchor occurrence/condition and deletion occurrence/anchor are compared. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0039

[Lines 239–244](../../../../../tests/unit/candidates_exception_test.cpp#L239); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_residual_view(const ResidualView& a, const ResidualView& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare original-to-local residual view mappings and rewritten query. |
| inputs / outputs | Two ResidualView values enter; original occurrence/variable lists, both local maps and same_query on rewritten queries determine the bool. |
| invariants | All four mappings and the full query image are part of equality; no references escape. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0041

[Lines 246–254](../../../../../tests/unit/candidates_exception_test.cpp#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_residual_record(const ResidualTraceRecord& a, const ResidualTraceRecord& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the full captured ResidualTraceRecord used by a retained residual candidate. |
| inputs / outputs | Two records enter; version, scopes, layer count/content, terminal members/head/flag and terminal view determine the bool. |
| invariants | Layer lengths are checked before per-layer comparison; terminal views use same_residual_view. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0043

[Lines 256–259](../../../../../tests/unit/candidates_exception_test.cpp#L256); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_residual_trace(const ResidualTrace& a, const ResidualTrace& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require valid residual trace handles and compare their binding and captured record. |
| inputs / outputs | Two ResidualTrace handles enter; both must be valid, then catalog, query and record equality determine the bool. |
| invariants | Invalid handles return false before access; valid access is restricted to the exact catalog/query/record returned by the trace. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0045

[Lines 261–265](../../../../../tests/unit/candidates_exception_test.cpp#L261); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_context(const CandidateContext& a, const CandidateContext& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all versioned candidate interpretation fields. |
| inputs / outputs | Two CandidateContext values enter; update profile and arithmetic, planner, optimization, cost-model and canonicalization strings determine the bool. |
| invariants | The six namespace fields are compared exactly; no accepted context is treated as a complexity or cost proof. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0047

[Lines 267–272](../../../../../tests/unit/candidates_exception_test.cpp#L267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_provenance(const CandidateProvenance& a, const CandidateProvenance& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare provenance identity and optional residual trace contents. |
| inputs / outputs | Two CandidateProvenance values enter; source/family/sequence/last residual step/trace presence and, when present, full trace equality determine the bool. |
| invariants | Trace access occurs only when both optional-presence flags agree; same_residual_trace supplies the deep comparison. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0049

[Lines 274–284](../../../../../tests/unit/candidates_exception_test.cpp#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_candidate(const MinimumHeightCandidate& a, const MinimumHeightCandidate& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two valid published MinimumHeightCandidate handles and their original proof certificate. |
| inputs / outputs | Two handles enter; validity, binding/query/tree/height/key/context/provenance and the original proof’s validity/certificate determine the bool. |
| invariants | Invalid candidates return false first; the original proof certificate is compared separately and an alternative upper never substitutes for it. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0051

[Lines 286–292](../../../../../tests/unit/candidates_exception_test.cpp#L286); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ProofValue {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a detached original-proof oracle: catalog, query, certificate, original upper tree and minimum height. |
| inputs / outputs | proof_value fills this aggregate from a VerifiedOptimum; the type returns no borrowed output. |
| invariants | The upper field is the proof’s original checked upper, not a candidate alternative; height/certificate remain paired with that proof. |
| ownership | The source handle is borrowed while this owning comparison image is assembled; its Catalog/Query/tree/certificate/string/vector fields are value copies, and no view into the source escapes. |
| failure | Owning value construction/copies and vector reserves may propagate std::bad_alloc; this type has no catch or allocation-failure translation. |
| cost | Copies the selected owned fields and nested sequences once; cost and storage scale with the captured proof/candidate/snapshot size, including copied strings and trace layers. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0053

[Lines 294–297](../../../../../tests/unit/candidates_exception_test.cpp#L294); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ProofValue proof_value(const VerifiedOptimum& proof) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture an owning value image of a VerifiedOptimum for later exact proof-preservation checks. |
| inputs / outputs | A proof handle enters; its binding catalog/query, certificate, original upper tree and height are copied into ProofValue. |
| invariants | The catalog/query come from proof.binding(); the upper tree and certificate are copied independently from the same proof handle. |
| ownership | The input proof/candidate/provenance/snapshot is borrowed for capture; the returned value owns the selected standard containers, strings and trace values. No view into the input escapes. |
| failure | Copying a Catalog, Query, certificate, residual record, tree or string may throw std::bad_alloc; missing/invalid handles are reported by the local check. No product error is translated. |
| cost | Copies the fields and nested entries listed in the result shape; cost and retained bytes grow with those values. No native MemoryAccount or fixed-byte bound is supplied by this helper. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0055

[Lines 299–305](../../../../../tests/unit/candidates_exception_test.cpp#L299); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_proof_value(const VerifiedOptimum& proof, const ProofValue& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a live VerifiedOptimum handle with the copied ProofValue baseline. |
| inputs / outputs | A proof handle and owning baseline enter; validity, height, certificate, upper tree and binding catalog/query determine the bool. |
| invariants | Invalid proof returns false before getters are read; the bound original witness/certificate is checked independently of any candidate upper. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0057

[Lines 307–316](../../../../../tests/unit/candidates_exception_test.cpp#L307); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ResidualValue {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a detached residual-candidate and trace oracle. |
| inputs / outputs | residual_value fills catalog/query/tree/height/origin plus trace record/catalog/query; all fields are copied values. |
| invariants | Candidate image and trace image are kept as separate binding facts for later failure comparisons. |
| ownership | The source handle is borrowed while this owning comparison image is assembled; its Catalog/Query/tree/certificate/string/vector fields are value copies, and no view into the source escapes. |
| failure | Owning value construction/copies and vector reserves may propagate std::bad_alloc; this type has no catch or allocation-failure translation. |
| cost | Copies the selected owned fields and nested sequences once; cost and storage scale with the captured proof/candidate/snapshot size, including copied strings and trace layers. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0059

[Lines 318–322](../../../../../tests/unit/candidates_exception_test.cpp#L318); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualValue residual_value(const ResidualCandidate& candidate) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a ResidualCandidate’s checked tree and complete trace binding/record as detached values. |
| inputs / outputs | A candidate enters; trace() supplies catalog/query/record and the candidate supplies its own catalog/query/tree/height/origin. |
| invariants | The returned image preserves the residual candidate and its trace separately so later comparisons can detect mutation or handle loss. |
| ownership | The input proof/candidate/provenance/snapshot is borrowed for capture; the returned value owns the selected standard containers, strings and trace values. No view into the input escapes. |
| failure | Copying a Catalog, Query, certificate, residual record, tree or string may throw std::bad_alloc; missing/invalid handles are reported by the local check. No product error is translated. |
| cost | Copies the fields and nested entries listed in the result shape; cost and retained bytes grow with those values. No native MemoryAccount or fixed-byte bound is supplied by this helper. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0061

[Lines 324–331](../../../../../tests/unit/candidates_exception_test.cpp#L324); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_residual_value(const ResidualCandidate& candidate, const ResidualValue& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a live residual candidate with its copied catalog/query/tree/trace baseline. |
| inputs / outputs | A ResidualCandidate handle and ResidualValue enter; validity, height, origin, candidate binding/tree and trace binding/record determine the bool. |
| invariants | Invalid candidates return false first; trace catalog/query/record are re-read only from the live handle and compared to the detached baseline. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0063

[Lines 333–342](../../../../../tests/unit/candidates_exception_test.cpp#L333); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ProvenanceValue {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store provenance scalars and an optional copied residual trace for equality after owner operations. |
| inputs / outputs | provenance_value fills source/family/sequence/last-step/presence and the copied trace binding/record when present. |
| invariants | has_trace reflects optional presence; the empty trace fields are ignored only when has_trace is false. |
| ownership | The source handle is borrowed while this owning comparison image is assembled; its Catalog/Query/tree/certificate/string/vector fields are value copies, and no view into the source escapes. |
| failure | Owning value construction/copies and vector reserves may propagate std::bad_alloc; this type has no catch or allocation-failure translation. |
| cost | Copies the selected owned fields and nested sequences once; cost and storage scale with the captured proof/candidate/snapshot size, including copied strings and trace layers. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0065

[Lines 344–353](../../../../../tests/unit/candidates_exception_test.cpp#L344); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ProvenanceValue provenance_value(const CandidateProvenance& provenance) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture CandidateProvenance, materializing residual-trace catalog/query/record only when present. |
| inputs / outputs | A provenance value enters; scalar source/family/sequence/last-step/presence are copied, followed by trace contents when the optional is engaged. |
| invariants | When no trace is present the default empty trace fields are not used by same_provenance_value. |
| ownership | The input proof/candidate/provenance/snapshot is borrowed for capture; the returned value owns the selected standard containers, strings and trace values. No view into the input escapes. |
| failure | Copying a Catalog, Query, certificate, residual record, tree or string may throw std::bad_alloc; missing/invalid handles are reported by the local check. No product error is translated. |
| cost | Copies the fields and nested entries listed in the result shape; cost and retained bytes grow with those values. No native MemoryAccount or fixed-byte bound is supplied by this helper. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0067

[Lines 355–363](../../../../../tests/unit/candidates_exception_test.cpp#L355); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_provenance_value(const CandidateProvenance& provenance, const ProvenanceValue& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare live provenance, including its optional trace, to an owning ProvenanceValue copy. |
| inputs / outputs | CandidateProvenance and ProvenanceValue enter; scalar provenance fields, trace presence and full copied trace contents determine the bool. |
| invariants | No trace fields are read if both sides have no trace; present traces require catalog/query/record equality. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0069

[Lines 365–374](../../../../../tests/unit/candidates_exception_test.cpp#L365); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateValue {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a detached full candidate oracle including the unchanged original proof image. |
| inputs / outputs | candidate_value captures catalog/query/tree/height/key/context/provenance/original proof. |
| invariants | Alternative upper tree and original proof remain distinct fields; exact context/provenance are retained for comparison. |
| ownership | The source handle is borrowed while this owning comparison image is assembled; its Catalog/Query/tree/certificate/string/vector fields are value copies, and no view into the source escapes. |
| failure | Owning value construction/copies and vector reserves may propagate std::bad_alloc; this type has no catch or allocation-failure translation. |
| cost | Copies the selected owned fields and nested sequences once; cost and storage scale with the captured proof/candidate/snapshot size, including copied strings and trace layers. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0071

[Lines 376–381](../../../../../tests/unit/candidates_exception_test.cpp#L376); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateValue candidate_value(const MinimumHeightCandidate& candidate) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture all candidate-owned fields and its original proof into CandidateValue. |
| inputs / outputs | A candidate handle enters; original_proof() is captured first, then catalog/query/tree/height/key/context/provenance and copied proof image exit. |
| invariants | A candidate’s structural upper is separate from the unchanged original proof; the key and provenance are captured for later comparison. |
| ownership | The input proof/candidate/provenance/snapshot is borrowed for capture; the returned value owns the selected standard containers, strings and trace values. No view into the input escapes. |
| failure | Copying a Catalog, Query, certificate, residual record, tree or string may throw std::bad_alloc; missing/invalid handles are reported by the local check. No product error is translated. |
| cost | Copies the fields and nested entries listed in the result shape; cost and retained bytes grow with those values. No native MemoryAccount or fixed-byte bound is supplied by this helper. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0073

[Lines 383–390](../../../../../tests/unit/candidates_exception_test.cpp#L383); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_candidate_value(const MinimumHeightCandidate& candidate, const CandidateValue& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one published candidate with a detached CandidateValue image. |
| inputs / outputs | A MinimumHeightCandidate and CandidateValue enter; validity, height/key, binding, tree, context, provenance and copied original proof determine the bool. |
| invariants | The full proof is checked with same_proof_value after the candidate-owned fields match; diagnostic fields are not treated as authority. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0075

[Lines 392–398](../../../../../tests/unit/candidates_exception_test.cpp#L392); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SnapshotValue {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a detached snapshot oracle with ordered candidate values and actual family completion. |
| inputs / outputs | snapshot_value fills exhaustion/family/context/proof and an ordered vector of copied CandidateValue entries. |
| invariants | Vector size equals the source candidate count at capture; a missing indexed candidate is treated as a test failure. |
| ownership | The source handle is borrowed while this owning comparison image is assembled; its Catalog/Query/tree/certificate/string/vector fields are value copies, and no view into the source escapes. |
| failure | Owning value construction/copies and vector reserves may propagate std::bad_alloc; this type has no catch or allocation-failure translation. |
| cost | Copies the selected owned fields and nested sequences once; cost and storage scale with the captured proof/candidate/snapshot size, including copied strings and trace layers. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0077

[Lines 400–413](../../../../../tests/unit/candidates_exception_test.cpp#L400); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SnapshotValue snapshot_value(const CandidateSnapshot& snapshot) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a CandidateSnapshot’s actual completion state and all ordered candidates as owned values. |
| inputs / outputs | A snapshot handle enters; family/exhaustion/context/proof are copied, then each candidate index is required to produce a value copied into the reserved vector. |
| invariants | The returned candidate vector has source candidate_count length and preserves snapshot order; a missing optional candidate throws the test assertion. |
| ownership | The input proof/candidate/provenance/snapshot is borrowed for capture; the returned value owns the selected standard containers, strings and trace values. No view into the input escapes. |
| failure | Copying a Catalog, Query, certificate, residual record, tree or string may throw std::bad_alloc; missing/invalid handles are reported by the local check. No product error is translated. |
| cost | Copies the fields and nested entries listed in the result shape; cost and retained bytes grow with those values. No native MemoryAccount or fixed-byte bound is supplied by this helper. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0079

[Lines 415–425](../../../../../tests/unit/candidates_exception_test.cpp#L415); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_snapshot_value(const CandidateSnapshot& snapshot, const SnapshotValue& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare an immutable CandidateSnapshot with a deep copied SnapshotValue baseline. |
| inputs / outputs | A snapshot handle and SnapshotValue enter; validity, count, exhaustion, family, context, original proof and each ordered candidate determine the bool. |
| invariants | Count is checked before indexed reads; each candidate optional must be present and match its captured candidate value. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0081

[Lines 427–434](../../../../../tests/unit/candidates_exception_test.cpp#L427); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_provider_prefix_value(const CandidateProvider& owner, const SnapshotValue& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that the live provider’s published candidates match the corresponding copied prefix. |
| inputs / outputs | A CandidateProvider and SnapshotValue enter; provider count must not exceed baseline length and each indexed live candidate must match. |
| invariants | Only the currently published prefix is compared; no exhaustion or unobserved future candidate is inferred. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0083

[Lines 436–441](../../../../../tests/unit/candidates_exception_test.cpp#L436); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_stats(const CandidateStatistics& a, const CandidateStatistics& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all eight candidate publication/statistics counters. |
| inputs / outputs | Two CandidateStatistics values enter; proposed/rejected/taller/duplicates/published/topologies/scope-tuples/cache-seeded determine the bool. |
| invariants | No counter is omitted from this helper’s explicit equality expression. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0085

[Lines 443–446](../../../../../tests/unit/candidates_exception_test.cpp#L443); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_work_except_faults(const WorkCounters& a, const WorkCounters& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare committed work state while intentionally ignoring fault/attempt diagnostics. |
| inputs / outputs | Two WorkCounters values enter; committed_transitions/current_depth/peak_depth determine the bool. |
| invariants | Attempted-work, allocation-failure and time diagnostics are not part of this equality predicate. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0087

[Lines 448–454](../../../../../tests/unit/candidates_exception_test.cpp#L448); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_progress_except_faults(const CandidateProgress& a, const CandidateProgress& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare provider progress while excluding failure-count/time diagnostics captured separately. |
| inputs / outputs | Two CandidateProgress values enter; phase/last stop/family/verified height/exhaustion, selected work, stats, record/cell counts, limit revision and candidate count determine the bool. |
| invariants | same_work_except_faults supplies committed transitions and depth; allocation-failure/attempt/time details are deliberately outside this helper. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0089

[Lines 456–462](../../../../../tests/unit/candidates_exception_test.cpp#L456); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_pending_progress(const CandidateProgress& a, const CandidateProgress& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the provider’s saved pending operation across repeated allocation failures. |
| inputs / outputs | Two CandidateProgress values enter; phase/family/verified height/exhaustion, committed work/depth, statistics, logical counts, limit revision and candidate count determine the bool. |
| invariants | last_stop and the changing fault counter are excluded so the same saved stage can be compared across successive failed attempts. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0091

[Lines 464–472](../../../../../tests/unit/candidates_exception_test.cpp#L464); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_published(const CandidateProvider& owner, const CandidateSnapshot& expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an exact count and ordered candidate-value match between provider and snapshot. |
| inputs / outputs | A provider and expected CandidateSnapshot enter by const reference; each index must be accessible and same_candidate. |
| invariants | Count equality is required before indexed comparison; order and each candidate’s original proof/provenance are preserved. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0093

[Lines 474–482](../../../../../tests/unit/candidates_exception_test.cpp#L474); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_published_prefix(const CandidateProvider& owner, const CandidateSnapshot& expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the provider’s current publication to remain an unchanged prefix of a snapshot. |
| inputs / outputs | A provider and expected CandidateSnapshot enter; provider count may be smaller but not larger; corresponding candidates are compared. |
| invariants | Earlier retained candidates must match in order; the helper permits an incomplete shorter prefix. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0095

[Lines 484–491](../../../../../tests/unit/candidates_exception_test.cpp#L484); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GeneratorState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the resumable generator state fields used by failure/retry equality. |
| inputs / outputs | Captures GeneratorStatistics, logical records/cells, depth, pending shared draft and cancellation state. |
| invariants | The snapshot compares the pending draft handle separately from its full tree value and does not count physical allocation bytes. |
| ownership | The binding/generator/budget/draft vector parameters are borrowed for the call; the baseline owns shared draft handles and copied statistics. The harness does not use MemoryAccount for candidate logical accounting. |
| failure | In the generator fault-sweep functions, explicit FaultScope injects bad_alloc through replaced global C++ new/new\[\] (plus candidate nothrow wrappers); raw malloc and syscall failures are not injected. ContentStop limits are separate logical record/cell stops; helper/type definitions do not arm a fault scope themselves. |
| cost | The fixture has finite loop guards; normal-form enumeration is intentionally potentially exponential. Captured generator records/cells are cumulative logical content, not allocator bytes or a time guarantee. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md § Resource and report boundaries](../../../../candidate_alternatives.md) |

## B0097

[Lines 493–497](../../../../../tests/unit/candidates_exception_test.cpp#L493); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_generator_stats(const ap::GeneratorStatistics& a, const ap::GeneratorStatistics& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the generator’s completed-step, topology, draft and peak-depth counters. |
| inputs / outputs | Two GeneratorStatistics values enter; all six explicit fields determine the bool. |
| invariants | Ready and consumed draft counts are separate and compared independently. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0099

[Lines 499–503](../../../../../tests/unit/candidates_exception_test.cpp#L499); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GeneratorState generator_state(const ap::NormalFormGenerator& generator,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe the current generator state and its associated ContentBudget counters. |
| inputs / outputs | A NormalFormGenerator and shared ContentBudget enter; current statistics/depth/draft/cancelled flag and logical records/cells exit in GeneratorState. |
| invariants | Budget and generator are sampled together at each assertion boundary; shared_ptr keeps the budget alive while the snapshot is formed. |
| ownership | The binding/generator/budget/draft vector parameters are borrowed for the call; the baseline owns shared draft handles and copied statistics. The harness does not use MemoryAccount for candidate logical accounting. |
| failure | In the generator fault-sweep functions, explicit FaultScope injects bad_alloc through replaced global C++ new/new\[\] (plus candidate nothrow wrappers); raw malloc and syscall failures are not injected. ContentStop limits are separate logical record/cell stops; helper/type definitions do not arm a fault scope themselves. |
| cost | The fixture has finite loop guards; normal-form enumeration is intentionally potentially exponential. Captured generator records/cells are cumulative logical content, not allocator bytes or a time guarantee. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md § Resource and report boundaries](../../../../candidate_alternatives.md) |

## B0101

[Lines 505–508](../../../../../tests/unit/candidates_exception_test.cpp#L505); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_generator_state(const GeneratorState& a, const GeneratorState& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the saved normal-form generator state captured around a failed step. |
| inputs / outputs | Two GeneratorState values enter; stats, logical record/cell totals, current depth, pending shared draft identity and cancelled flag determine the bool. |
| invariants | The pending draft pointer is compared for shared ownership identity; deep tree value comparison is performed by same_generator_run. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0103

[Lines 510–516](../../../../../tests/unit/candidates_exception_test.cpp#L510); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GeneratorRun {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the uninterrupted normal-form generator baseline. |
| inputs / outputs | Stores the retained ordered draft shared_ptrs, final GeneratorStatistics, logical records/cells and measured allocation-call count. |
| invariants | Allocation count is sampled only around draining after the output vector’s reserve and generator construction. |
| ownership | The binding/generator/budget/draft vector parameters are borrowed for the call; the baseline owns shared draft handles and copied statistics. The harness does not use MemoryAccount for candidate logical accounting. |
| failure | In the generator fault-sweep functions, explicit FaultScope injects bad_alloc through replaced global C++ new/new\[\] (plus candidate nothrow wrappers); raw malloc and syscall failures are not injected. ContentStop limits are separate logical record/cell stops; helper/type definitions do not arm a fault scope themselves. |
| cost | The fixture has finite loop guards; normal-form enumeration is intentionally potentially exponential. Captured generator records/cells are cumulative logical content, not allocator bytes or a time guarantee. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md § Resource and report boundaries](../../../../candidate_alternatives.md) |

## B0105

[Lines 518–533](../../../../../tests/unit/candidates_exception_test.cpp#L518); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void append_ready_draft(ap::NormalFormGenerator& generator,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acknowledge a ready draft only after preserving a shared handle and checking repeated ready observations. |
| inputs / outputs | Borrows generator, budget and pre-reserved draft vector; appends the ready shared draft, checks the same ready state twice, then consumes once. |
| invariants | Repeated step({}) cannot skip or alter the pending draft; vector capacity must have been reserved before this helper. |
| ownership | The binding/generator/budget/draft vector parameters are borrowed for the call; the baseline owns shared draft handles and copied statistics. The harness does not use MemoryAccount for candidate logical accounting. |
| failure | In the generator fault-sweep functions, explicit FaultScope injects bad_alloc through replaced global C++ new/new\[\] (plus candidate nothrow wrappers); raw malloc and syscall failures are not injected. ContentStop limits are separate logical record/cell stops; helper/type definitions do not arm a fault scope themselves. |
| cost | The fixture has finite loop guards; normal-form enumeration is intentionally potentially exponential. Captured generator records/cells are cumulative logical content, not allocator bytes or a time guarantee. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md § Resource and report boundaries](../../../../candidate_alternatives.md) |

## B0107

[Lines 535–547](../../../../../tests/unit/candidates_exception_test.cpp#L535); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool generator_result(ap::NormalFormGenerator& generator,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate one generator Step into test-harness ready/exhausted/advanced behavior. |
| inputs / outputs | A Step enters; draft_ready is retained/consumed through append_ready_draft, exhausted returns true, advanced returns false, and any other event fails the check. |
| invariants | The harness consumes a draft only after checking the ready observation; unexpected stopped events do not count as normal progress. |
| ownership | The binding/generator/budget/draft vector parameters are borrowed for the call; the baseline owns shared draft handles and copied statistics. The harness does not use MemoryAccount for candidate logical accounting. |
| failure | In the generator fault-sweep functions, explicit FaultScope injects bad_alloc through replaced global C++ new/new\[\] (plus candidate nothrow wrappers); raw malloc and syscall failures are not injected. ContentStop limits are separate logical record/cell stops; helper/type definitions do not arm a fault scope themselves. |
| cost | The fixture has finite loop guards; normal-form enumeration is intentionally potentially exponential. Captured generator records/cells are cumulative logical content, not allocator bytes or a time guarantee. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md § Resource and report boundaries](../../../../candidate_alternatives.md) |

## B0109

[Lines 549–559](../../../../../tests/unit/candidates_exception_test.cpp#L549); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool drain_generator(ap::NormalFormGenerator& generator,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain the generator with an empty UnitContext until actual exhaustion or a finite test guard. |
| inputs / outputs | Generator, shared budget, draft vector and mutable call counter enter; true means the generator reported exhausted within one million steps. |
| invariants | Every call increments the counter and processes one step; hitting the guard returns false rather than claiming exhaustion. |
| ownership | The binding/generator/budget/draft vector parameters are borrowed for the call; the baseline owns shared draft handles and copied statistics. The harness does not use MemoryAccount for candidate logical accounting. |
| failure | In the generator fault-sweep functions, explicit FaultScope injects bad_alloc through replaced global C++ new/new\[\] (plus candidate nothrow wrappers); raw malloc and syscall failures are not injected. ContentStop limits are separate logical record/cell stops; helper/type definitions do not arm a fault scope themselves. |
| cost | The fixture has finite loop guards; normal-form enumeration is intentionally potentially exponential. Captured generator records/cells are cumulative logical content, not allocator bytes or a time guarantee. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md § Resource and report boundaries](../../../../candidate_alternatives.md) |

## B0111

[Lines 561–571](../../../../../tests/unit/candidates_exception_test.cpp#L561); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_generator_run(const ap::NormalFormGenerator& generator,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a completed generator run against the uninterrupted baseline. |
| inputs / outputs | Live generator/budget/draft vector and GeneratorRun baseline enter; draft count, stats, logical totals and each ordered tree value determine the bool. |
| invariants | Every output pointer and tree must be present; same_tree compares content rather than requiring pointer identity. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0113

[Lines 573–592](../../../../../tests/unit/candidates_exception_test.cpp#L573); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GeneratorRun baseline_generator(const std::shared_ptr<const cd::BindingData>& binding) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calibrate the complete ordered normal-form draft result and cumulative logical content for one binding. |
| inputs / outputs | A checked BindingData handle enters; a fresh unlimited ContentBudget and height-2 NormalFormGenerator drain into a vector; GeneratorRun exits. |
| invariants | The output vector reserves 256 before allocation_count is reset; baseline requires finite completion, at least one draft/allocation, and ready==consumed. |
| ownership | The binding/generator/budget/draft vector parameters are borrowed for the call; the baseline owns shared draft handles and copied statistics. The harness does not use MemoryAccount for candidate logical accounting. |
| failure | In the generator fault-sweep functions, explicit FaultScope injects bad_alloc through replaced global C++ new/new\[\] (plus candidate nothrow wrappers); raw malloc and syscall failures are not injected. ContentStop limits are separate logical record/cell stops; helper/type definitions do not arm a fault scope themselves. |
| cost | The fixture has finite loop guards; normal-form enumeration is intentionally potentially exponential. Captured generator records/cells are cumulative logical content, not allocator bytes or a time guarantee. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md § Resource and report boundaries](../../../../candidate_alternatives.md) |

## B0115

[Lines 594–636](../../../../../tests/unit/candidates_exception_test.cpp#L594); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void generator_faults(const std::shared_ptr<const cd::BindingData>& binding,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject every measured generator allocation position, require stable pending retries, then finish the same generator owner. |
| inputs / outputs | Binding and GeneratorRun baseline enter; each trial owns a fresh generator/budget with output capacity reserved, then a fail point is armed during drain. |
| invariants | On bad_alloc it checks the exact point, no pending draft, two still-failing same-owner step retries with unchanged state, then disarms and drains that same owner to identical ordered trees/statistics/logical content. |
| ownership | The binding/generator/budget/draft vector parameters are borrowed for the call; the baseline owns shared draft handles and copied statistics. The harness does not use MemoryAccount for candidate logical accounting. |
| failure | In the generator fault-sweep functions, explicit FaultScope injects bad_alloc through replaced global C++ new/new\[\] (plus candidate nothrow wrappers); raw malloc and syscall failures are not injected. ContentStop limits are separate logical record/cell stops; helper/type definitions do not arm a fault scope themselves. |
| cost | The fixture has finite loop guards; normal-form enumeration is intentionally potentially exponential. Captured generator records/cells are cumulative logical content, not allocator bytes or a time guarantee. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md § Resource and report boundaries](../../../../candidate_alternatives.md) |

## B0117

[Lines 638–703](../../../../../tests/unit/candidates_exception_test.cpp#L638); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void generator_caps_and_cancel(const std::shared_ptr<const cd::BindingData>& binding,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise generator logical content ceilings, saved stops, limit raising, depth grants and cancellation with a retained draft. |
| inputs / outputs | A binding and uninterrupted GeneratorRun enter; zero/one record and zero-cell limits stop, an empty limit extension resumes, and a zero depth grant owns no frame. |
| invariants | Repeated stops preserve the pending stage/counters; after first draft readiness, cancel runs under fail_after=0 and a caller-retained shared draft remains unchanged. |
| ownership | The binding/generator/budget/draft vector parameters are borrowed for the call; the baseline owns shared draft handles and copied statistics. The harness does not use MemoryAccount for candidate logical accounting. |
| failure | In the generator fault-sweep functions, explicit FaultScope injects bad_alloc through replaced global C++ new/new\[\] (plus candidate nothrow wrappers); raw malloc and syscall failures are not injected. ContentStop limits are separate logical record/cell stops; helper/type definitions do not arm a fault scope themselves. |
| cost | The fixture has finite loop guards; normal-form enumeration is intentionally potentially exponential. Captured generator records/cells are cumulative logical content, not allocator bytes or a time guarantee. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/candidate_alternatives.md § Resource and report boundaries](../../../../candidate_alternatives.md) |

## B0119

[Lines 705–713](../../../../../tests/unit/candidates_exception_test.cpp#L705); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish_key(ap::StructuralKeyMachine& machine) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive a structural-key machine to a published token with a finite test guard. |
| inputs / outputs | A mutable StructuralKeyMachine enters; repeated step({256}) calls stop only at key_ready, otherwise unexpected stopped events fail; one million calls is the upper fixture guard. |
| invariants | The helper does not accept a stopped resource result as success; it returns only after the key-ready event. |
| ownership | The input FreeConnexTree shared handle and machine/budget references are borrowed for these calls; KeyRun owns the published shared string token and copied counters. |
| failure | A step allocation exception propagates to the surrounding fault sweep; an unexpected stop or guard exhaustion raises std::runtime_error. |
| cost | At most one million machine steps, with each step receiving logical depth 256; no wall-clock or linear-time claim. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [src/planner/candidate_key.cpp](../../../../../src/planner/candidate_key.cpp), [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [docs/candidate_alternatives.md § Identity, cache and transactions](../../../../candidate_alternatives.md) |

## B0121

[Lines 715–718](../../../../../tests/unit/candidates_exception_test.cpp#L715); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_key_stats(const ap::KeyStatistics& a, const ap::KeyStatistics& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all structural-key-machine progress counters. |
| inputs / outputs | Two KeyStatistics values enter; completed steps/nodes, compared characters and peak depth determine the bool. |
| invariants | No key bytes or content-budget totals are compared here; their owning run oracle checks them separately. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0123

[Lines 720–726](../../../../../tests/unit/candidates_exception_test.cpp#L720); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct KeyRun {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the published structural-key baseline and its logical-content/step counters. |
| inputs / outputs | Stores a shared immutable token, KeyStatistics, ContentBudget records/cells and measured new-call count. |
| invariants | The measured count is reset after machine construction and only spans finish_key; the token remains owned by shared_ptr. |
| ownership | The input FreeConnexTree shared handle and machine/budget references are borrowed for these calls; KeyRun owns the published shared string token and copied counters. |
| failure | FaultScope injects std::bad_alloc only at the replaced C++ new/new\[\] boundary during key stepping; raw malloc/syscalls and MemoryAccount limits are not independently injected. Key content record/cell stops are distinct. |
| cost | The machine has explicit step/depth/content accounting, but encoding/comparison and child-token sorting/copy work can be variable; this harness’s million-step guard is a fixture bound, not a production delay guarantee. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [src/planner/candidate_key.cpp](../../../../../src/planner/candidate_key.cpp), [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [docs/candidate_alternatives.md § Identity, cache and transactions](../../../../candidate_alternatives.md) |

## B0125

[Lines 728–737](../../../../../tests/unit/candidates_exception_test.cpp#L728); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
KeyRun baseline_key(const std::shared_ptr<const FreeConnexTree>& tree) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a structural key and calibrate its token, traversal counters, logical content and C++ allocation calls. |
| inputs / outputs | A shared tree enters; a fresh machine and ContentBudget are built, allocation count is reset, and finish_key must publish a nonempty key. |
| invariants | The tree input is already the checked proof upper in main; the helper checks key publication and a nonzero observed allocation count. |
| ownership | The input FreeConnexTree shared handle and machine/budget references are borrowed for these calls; KeyRun owns the published shared string token and copied counters. |
| failure | FaultScope injects std::bad_alloc only at the replaced C++ new/new\[\] boundary during key stepping; raw malloc/syscalls and MemoryAccount limits are not independently injected. Key content record/cell stops are distinct. |
| cost | The machine has explicit step/depth/content accounting, but encoding/comparison and child-token sorting/copy work can be variable; this harness’s million-step guard is a fixture bound, not a production delay guarantee. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [src/planner/candidate_key.cpp](../../../../../src/planner/candidate_key.cpp), [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [docs/candidate_alternatives.md § Identity, cache and transactions](../../../../candidate_alternatives.md) |

## B0127

[Lines 739–774](../../../../../tests/unit/candidates_exception_test.cpp#L739); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void key_faults(const std::shared_ptr<const FreeConnexTree>& tree, const KeyRun& expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject each baseline key allocation position and prove an unpublished key remains pending until same-owner completion. |
| inputs / outputs | Tree and KeyRun enter; each fresh machine faults during finish_key, records pending stats/content/depth, retries step twice under the same failure point, then completes after disarm. |
| invariants | Every fault must leave key() empty and keep machine stats, logical budget and depth fixed through two retries; recovery publishes exactly the baseline key/counters. |
| ownership | The input FreeConnexTree shared handle and machine/budget references are borrowed for these calls; KeyRun owns the published shared string token and copied counters. |
| failure | FaultScope injects std::bad_alloc only at the replaced C++ new/new\[\] boundary during key stepping; raw malloc/syscalls and MemoryAccount limits are not independently injected. Key content record/cell stops are distinct. |
| cost | The machine has explicit step/depth/content accounting, but encoding/comparison and child-token sorting/copy work can be variable; this harness’s million-step guard is a fixture bound, not a production delay guarantee. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [src/planner/candidate_key.cpp](../../../../../src/planner/candidate_key.cpp), [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [docs/candidate_alternatives.md § Identity, cache and transactions](../../../../candidate_alternatives.md) |

## B0129

[Lines 776–814](../../../../../tests/unit/candidates_exception_test.cpp#L776); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void key_caps_and_cancel(const std::shared_ptr<const FreeConnexTree>& tree, const KeyRun& expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise key depth/cell ceilings, repeated logical stops, limit raising and cancellation after key publication. |
| inputs / outputs | A tree and KeyRun enter; a zero depth grant and zero-cell budget stop, then a cell-limit raise allows finish_key to match the baseline. |
| invariants | Repeated cell stops preserve saved serialization/accounting state; cancel under fail_after=0 leaves the retained published shared key unchanged. |
| ownership | The input FreeConnexTree shared handle and machine/budget references are borrowed for these calls; KeyRun owns the published shared string token and copied counters. |
| failure | FaultScope injects std::bad_alloc only at the replaced C++ new/new\[\] boundary during key stepping; raw malloc/syscalls and MemoryAccount limits are not independently injected. Key content record/cell stops are distinct. |
| cost | The machine has explicit step/depth/content accounting, but encoding/comparison and child-token sorting/copy work can be variable; this harness’s million-step guard is a fixture bound, not a production delay guarantee. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [src/planner/candidate_key.cpp](../../../../../src/planner/candidate_key.cpp), [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [docs/candidate_alternatives.md § Identity, cache and transactions](../../../../candidate_alternatives.md) |

## B0131

[Lines 816–825](../../../../../tests/unit/candidates_exception_test.cpp#L816); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateStop drain(CandidateProvider& owner, std::uint64_t quantum =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain CandidateProvider advances until a non-quantum/non-candidate stop is observed. |
| inputs / outputs | A mutable provider and optional work quantum enter; repeated advance results with candidate_ready/quantum_work are consumed, and the first other CandidateStop exits. |
| invariants | The two million call limit raises a test failure rather than being interpreted as exhaustion; callers distinguish exhausted from resource/failure stops. |
| ownership | Proof/snapshot/residual inputs are borrowed or copied as declared; provider and cache objects remain owned by each local trial. Exported candidate/snapshot handles and detached value images outlive those trials only through their own shared/value ownership. |
| failure | Where a fault scope is present, it targets selected global C++ new/new\[\] requests. Provider advance maps bad_alloc to allocation_failure and retains its pending stage; factory/snapshot/cache admission operations propagate bad_alloc. Accessors/comparators do not arm a fault scope. No direct malloc/syscall or MemoryAccount-limit failure is injected. |
| cost | Provider work is bounded by explicit fixture ceilings and candidate limits, but enumeration, binding admission, serialization, full comparisons and allocation have variable cost. Logical record/cell counters are not allocator bytes. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0133

[Lines 827–830](../../../../../tests/unit/candidates_exception_test.cpp#L827); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateRun {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store CandidateProvider progress and the calibrated global-new call count. |
| inputs / outputs | The provider’s progress value and observed allocation-call count are copied into CandidateRun. |
| invariants | Progress is a value snapshot; its fault counters are excluded only by the explicit comparison helpers. |
| ownership | Proof/snapshot/residual inputs are borrowed or copied as declared; provider and cache objects remain owned by each local trial. Exported candidate/snapshot handles and detached value images outlive those trials only through their own shared/value ownership. |
| failure | Where a fault scope is present, it targets selected global C++ new/new\[\] requests. Provider advance maps bad_alloc to allocation_failure and retains its pending stage; factory/snapshot/cache admission operations propagate bad_alloc. Accessors/comparators do not arm a fault scope. No direct malloc/syscall or MemoryAccount-limit failure is injected. |
| cost | Provider work is bounded by explicit fixture ceilings and candidate limits, but enumeration, binding admission, serialization, full comparisons and allocation have variable cost. Logical record/cell counters are not allocator bytes. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0135

[Lines 832–841](../../../../../tests/unit/candidates_exception_test.cpp#L832); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateRun baseline_provider(CandidateProvider& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calibrate a provider’s complete finite candidate family and final progress. |
| inputs / outputs | A live CandidateProvider enters; allocation count is reset around drain; CandidateRun exits only when exhausted with a nonempty family. |
| invariants | This records a baseline, not a claim that the finite family contains every admissible tree or globally cheapest maintenance plan. |
| ownership | Proof/snapshot/residual inputs are borrowed or copied as declared; provider and cache objects remain owned by each local trial. Exported candidate/snapshot handles and detached value images outlive those trials only through their own shared/value ownership. |
| failure | Where a fault scope is present, it targets selected global C++ new/new\[\] requests. Provider advance maps bad_alloc to allocation_failure and retains its pending stage; factory/snapshot/cache admission operations propagate bad_alloc. Accessors/comparators do not arm a fault scope. No direct malloc/syscall or MemoryAccount-limit failure is injected. |
| cost | Provider work is bounded by explicit fixture ceilings and candidate limits, but enumeration, binding admission, serialization, full comparisons and allocation have variable cost. Logical record/cell counters are not allocator bytes. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0137

[Lines 843–850](../../../../../tests/unit/candidates_exception_test.cpp#L843); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_provider(const CandidateProvider& actual, const CandidateRun& expected,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a recovered provider’s progress and publication against its baseline. |
| inputs / outputs | Actual provider, CandidateRun and expected snapshot enter; selected progress fields and every published candidate determine success. |
| invariants | same_progress_except_faults excludes changing fault diagnostics; same_published requires the exact baseline count and order. |
| ownership | Both operands are borrowed only for the call; the returned bool retains no Catalog, Query, tree, certificate, residual trace or string view. |
| failure | A differing compared field returns false at the first mismatch. This oracle installs no fail point and catches no exception; exceptions from nested comparisons or surrounding checks propagate. |
| cost | Inspects the compared scalar fields and nested vector elements in order, stopping at the first mismatch; it uses structural equality rather than a digest or timing bound. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0139

[Lines 852–893](../../../../../tests/unit/candidates_exception_test.cpp#L852); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void provider_faults(const VerifiedOptimum& proof, const CandidateRun& expected,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject each observed provider allocation point and compare same-owner retries and eventual ordered recovery. |
| inputs / outputs | VerifiedOptimum, baseline progress and frozen snapshot enter; each fault point creates a provider, drains to allocation_failure, retries advance twice while armed, then recovers on that same provider. |
| invariants | Failure is nonterminal and does not publish an out-of-order candidate; earlier prefix, retained proof/snapshot and post-recovery progress/order match the baseline. |
| ownership | Proof/snapshot/residual inputs are borrowed or copied as declared; provider and cache objects remain owned by each local trial. Exported candidate/snapshot handles and detached value images outlive those trials only through their own shared/value ownership. |
| failure | Where a fault scope is present, it targets selected global C++ new/new\[\] requests. Provider advance maps bad_alloc to allocation_failure and retains its pending stage; factory/snapshot/cache admission operations propagate bad_alloc. Accessors/comparators do not arm a fault scope. No direct malloc/syscall or MemoryAccount-limit failure is injected. |
| cost | Provider work is bounded by explicit fixture ceilings and candidate limits, but enumeration, binding admission, serialization, full comparisons and allocation have variable cost. Logical record/cell counters are not allocator bytes. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0141

[Lines 895–933](../../../../../tests/unit/candidates_exception_test.cpp#L895); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void factory_admission_faults(const VerifiedOptimum& proof,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep CandidateProvider factory admission before any provider owner is returned. |
| inputs / outputs | A proof and retained snapshot enter; a calibration create measures calls; each selected create failure is retried by recreating the same request, then a fresh create succeeds. |
| invariants | These retries recreate admission rather than advancing a partially built provider; retained proof and snapshot values are checked unchanged. |
| ownership | Proof/snapshot/residual inputs are borrowed or copied as declared; provider and cache objects remain owned by each local trial. Exported candidate/snapshot handles and detached value images outlive those trials only through their own shared/value ownership. |
| failure | Where a fault scope is present, it targets selected global C++ new/new\[\] requests. Provider advance maps bad_alloc to allocation_failure and retains its pending stage; factory/snapshot/cache admission operations propagate bad_alloc. Accessors/comparators do not arm a fault scope. No direct malloc/syscall or MemoryAccount-limit failure is injected. |
| cost | Provider work is bounded by explicit fixture ceilings and candidate limits, but enumeration, binding admission, serialization, full comparisons and allocation have variable cost. Logical record/cell counters are not allocator bytes. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0143

[Lines 935–972](../../../../../tests/unit/candidates_exception_test.cpp#L935); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void snapshot_admission_faults(CandidateProvider& owner, const CandidateSnapshot& expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep explicit CandidateProvider::snapshot admission while preserving the live provider. |
| inputs / outputs | A drained provider and expected snapshot enter; a sample snapshot calibrates calls; each failed snapshot call is repeated while armed and a fresh call succeeds after disarm. |
| invariants | Failed snapshot admission leaves progress, published prefix and the previously retained snapshot value unchanged. |
| ownership | Proof/snapshot/residual inputs are borrowed or copied as declared; provider and cache objects remain owned by each local trial. Exported candidate/snapshot handles and detached value images outlive those trials only through their own shared/value ownership. |
| failure | Where a fault scope is present, it targets selected global C++ new/new\[\] requests. Provider advance maps bad_alloc to allocation_failure and retains its pending stage; factory/snapshot/cache admission operations propagate bad_alloc. Accessors/comparators do not arm a fault scope. No direct malloc/syscall or MemoryAccount-limit failure is injected. |
| cost | Provider work is bounded by explicit fixture ceilings and candidate limits, but enumeration, binding admission, serialization, full comparisons and allocation have variable cost. Logical record/cell counters are not allocator bytes. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0145

[Lines 974–1055](../../../../../tests/unit/candidates_exception_test.cpp#L974); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void provider_caps_and_cancel(const VerifiedOptimum& proof, const CandidateRun& baseline,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise provider depth/record/cell/candidate caps, limit extensions, pending publication and cancellation. |
| inputs / outputs | Original proof, baseline run and expected snapshot enter; resource caps are raised to exhaustion, a one-candidate cap pauses a pending publication, and cancellation follows one published candidate. |
| invariants | Repeated logical/candidate stops preserve saved state and retained handles; raised limits permit baseline completion; cancel under fail_after=0 keeps proof/candidate/snapshot values valid. |
| ownership | Proof/snapshot/residual inputs are borrowed or copied as declared; provider and cache objects remain owned by each local trial. Exported candidate/snapshot handles and detached value images outlive those trials only through their own shared/value ownership. |
| failure | Where a fault scope is present, it targets selected global C++ new/new\[\] requests. Provider advance maps bad_alloc to allocation_failure and retains its pending stage; factory/snapshot/cache admission operations propagate bad_alloc. Accessors/comparators do not arm a fault scope. No direct malloc/syscall or MemoryAccount-limit failure is injected. |
| cost | Provider work is bounded by explicit fixture ceilings and candidate limits, but enumeration, binding admission, serialization, full comparisons and allocation have variable cost. Logical record/cell counters are not allocator bytes. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0147

[Lines 1057–1158](../../../../../tests/unit/candidates_exception_test.cpp#L1057); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void optional_seed_path_faults(const VerifiedOptimum& proof, const ResidualCandidate& residual,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep optional residual and cached-prefix seeding through provider advance and separate factory admission. |
| inputs / outputs | Original proof, checked residual candidate and exact-proof prefix enter; baseline must publish the exact and distinct residual source candidates while accounting seeded prefix entries. |
| invariants | Each advance allocation fault keeps optional inputs and published prefix unchanged across two armed retries, then same-owner recovery reproduces order/provenance; separate factory sweeps recreate the request and are not advance retries. |
| ownership | Proof/snapshot/residual inputs are borrowed or copied as declared; provider and cache objects remain owned by each local trial. Exported candidate/snapshot handles and detached value images outlive those trials only through their own shared/value ownership. |
| failure | Where a fault scope is present, it targets selected global C++ new/new\[\] requests. Provider advance maps bad_alloc to allocation_failure and retains its pending stage; factory/snapshot/cache admission operations propagate bad_alloc. Accessors/comparators do not arm a fault scope. No direct malloc/syscall or MemoryAccount-limit failure is injected. |
| cost | Provider work is bounded by explicit fixture ceilings and candidate limits, but enumeration, binding admission, serialization, full comparisons and allocation have variable cost. Logical record/cell counters are not allocator bytes. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0149

[Lines 1160–1162](../../../../../tests/unit/candidates_exception_test.cpp#L1160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateCacheStatistics cache_stats(const CandidateCache& cache) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the cache’s current statistics value for comparisons around admission faults. |
| inputs / outputs | A CandidateCache reference enters; the by-value CandidateCacheStatistics snapshot exits. |
| invariants | The returned counters are a momentary value; entries describe current cache contents, while activity counters persist according to the public cache contract. |
| ownership | Proof/snapshot/residual inputs are borrowed or copied as declared; provider and cache objects remain owned by each local trial. Exported candidate/snapshot handles and detached value images outlive those trials only through their own shared/value ownership. |
| failure | CandidateCache::statistics returns its fixed-size value noexcept; this accessor arms no fault scope and translates no failures. |
| cost | Provider work is bounded by explicit fixture ceilings and candidate limits, but enumeration, binding admission, serialization, full comparisons and allocation have variable cost. Logical record/cell counters are not allocator bytes. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0151

[Lines 1164–1167](../../../../../tests/unit/candidates_exception_test.cpp#L1164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_cache_stats(const CandidateCacheStatistics& a, const CandidateCacheStatistics& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare cache hit/miss/insert/replace/evict activity and current entry count. |
| inputs / outputs | Two CandidateCacheStatistics values enter; six counters determine equality. |
| invariants | Entry count is compared separately from cumulative activity; this helper does not inspect cache keys or snapshot payloads. |
| ownership | Proof/snapshot/residual inputs are borrowed or copied as declared; provider and cache objects remain owned by each local trial. Exported candidate/snapshot handles and detached value images outlive those trials only through their own shared/value ownership. |
| failure | Unequal fields return false; this fixed-size comparator arms no fault scope and catches no exception. |
| cost | Provider work is bounded by explicit fixture ceilings and candidate limits, but enumeration, binding admission, serialization, full comparisons and allocation have variable cost. Logical record/cell counters are not allocator bytes. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0153

[Lines 1169–1176](../../../../../tests/unit/candidates_exception_test.cpp#L1169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CandidateSnapshot first_snapshot(const VerifiedOptimum& proof) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the one-candidate exact-proof snapshot used as a cache key fixture. |
| inputs / outputs | A VerifiedOptimum enters; a provider with retained_candidates=1 must publish its exact seed, then an owning snapshot exits. |
| invariants | The returned snapshot contains the exact seed prefix; no family exhaustion is claimed from the one-candidate cap. |
| ownership | Proof/snapshot/residual inputs are borrowed or copied as declared; provider and cache objects remain owned by each local trial. Exported candidate/snapshot handles and detached value images outlive those trials only through their own shared/value ownership. |
| failure | Provider creation/advance/snapshot allocation errors propagate; no fault scope is active in this helper, and the one-candidate cap does not claim exhaustion. |
| cost | Provider work is bounded by explicit fixture ceilings and candidate limits, but enumeration, binding admission, serialization, full comparisons and allocation have variable cost. Logical record/cell counters are not allocator bytes. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0155

[Lines 1178–1278](../../../../../tests/unit/candidates_exception_test.cpp#L1178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cache_install_faults(const VerifiedOptimum& a_proof, const VerifiedOptimum& b_proof,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise allocation-free replacement, failure-atomic new-node admission, immutable snapshot retention and FIFO eviction order. |
| inputs / outputs | Three proofs and four snapshots enter: A full/partial plus distinct B and metadata-distinct C; a capacity-two cache tests replacement and new-node allocation positions. |
| invariants | Matching replacement under fail_after=0 preserves the original FIFO slot; each failed new install leaves old entries/counters intact, and successful retry evicts A while retaining B/C and caller snapshots. |
| ownership | Proof/snapshot/residual inputs are borrowed or copied as declared; provider and cache objects remain owned by each local trial. Exported candidate/snapshot handles and detached value images outlive those trials only through their own shared/value ownership. |
| failure | Where a fault scope is present, it targets selected global C++ new/new\[\] requests. Provider advance maps bad_alloc to allocation_failure and retains its pending stage; factory/snapshot/cache admission operations propagate bad_alloc. Accessors/comparators do not arm a fault scope. No direct malloc/syscall or MemoryAccount-limit failure is injected. |
| cost | Provider work is bounded by explicit fixture ceilings and candidate limits, but enumeration, binding admission, serialization, full comparisons and allocation have variable cost. Logical record/cell counters are not allocator bytes. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0156

[Lines 1279–1281](../../../../../tests/unit/candidates_exception_test.cpp#L1279); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1279-L1281:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in candidates_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0157

[Lines 1282–1355](../../../../../tests/unit/candidates_exception_test.cpp#L1282); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Orchestrate original-proof, generator, key, provider, optional-seed and cache exception fixtures. |
| inputs / outputs | No command-line input is read; deterministic fixtures build P06 proofs, binding data and snapshots; successful execution prints observed-position summaries and returns zero. |
| invariants | The top-level catch disables fail_after before reporting an exception and returns one; all production-style candidate outcomes are asserted by the called helpers. |
| ownership | Local fixture/owner/snapshot values own their data; the static source code makes no external application or durable state writes. |
| failure | Any uncaught std::exception (including fixture assertion or propagated allocation failure) is reported and returns one; this source review makes no claim that the executable was run. |
| cost | Runs finite fixture loops with per-helper ceilings; normal-form enumeration may be exponential and no runtime benchmark follows. |
| Design | [tests/unit/candidates_exception_test.cpp](../../../../../tests/unit/candidates_exception_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |
