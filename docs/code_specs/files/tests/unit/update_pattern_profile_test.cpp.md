# `tests/unit/update_pattern_profile_test.cpp` — block usage map

[Source](../../../../../tests/unit/update_pattern_profile_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `6f24714df4dbb4aff90acdbdfcfd1767a5821dcb7924119f3f8f4b7ed52823fd`. 329 lines partitioned into 26 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–26](../../../../../tests/unit/update_pattern_profile_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Ordinary fixture compilation precedes profile access. The real search/provider · [reviewed contract](#b0001) |
| [B0002 · 27–31](../../../../../tests/unit/update_pattern_profile_test.cpp#L27) | Callable definition: CompiledProgram compile(const c02_test::Fixture& fixture, const planner::CandidateSnapshot& family, bool indexed = false) | calls CompiledProgram::standalone, planner::lower_tree, candidate, tree; returns CompiledProgram::standalone(planner::lower_tree(fixture.catalog, fixture.query,; source comment (unverified): // Ordinary fixture compilation precedes profile access. The real search/provider · [reviewed contract](#b0002) |
| [B0003 · 32–36](../../../../../tests/unit/update_pattern_profile_test.cpp#L32) | Callable definition: ps::Request request(const CompiledProgram& program, std::span&lt;const ip::TableRule&gt; rules) | calls ip::Declaration::capture, account; returns result · [reviewed contract](#b0003) |
| [B0004 · 37–40](../../../../../tests/unit/update_pattern_profile_test.cpp#L37) | Callable definition: SessionOptions monitored(const ps::Request& requested) | calls ; returns result · [reviewed contract](#b0004) |
| [B0005 · 41–41](../../../../../tests/unit/update_pattern_profile_test.cpp#L41) | Callable definition: std::string hash(const std::array&lt;char, 64&gt;& value) | calls data, size; returns {value.data(), value.size()} · [reviewed contract](#b0005) |
| [B0006 · 42–42](../../../../../tests/unit/update_pattern_profile_test.cpp#L42) | Callable definition: std::string_view bytes(const recovery::SessionImage& image) | calls data, size; returns {image.bytes.data(), image.bytes.size()} · [reviewed contract](#b0006) |
| [B0007 · 43–47](../../../../../tests/unit/update_pattern_profile_test.cpp#L43) | Callable definition: void physical(QuerySession& session, PhysicalSetUpdate update) | calls batch, std::move, check, enqueue; guard check(session.enqueue(batch) == io::Admission::accepted && session.begin_next(), "profile input mis… · [reviewed contract](#b0007) |
| [B0008 · 48–50](../../../../../tests/unit/update_pattern_profile_test.cpp#L48) | Explanatory comments or spacing. | source comment (unverified): // These JSON values are test exports for human inspection, outside query · [reviewed contract](#b0008) |
| [B0009 · 51–76](../../../../../tests/unit/update_pattern_profile_test.cpp#L51) | Callable definition: Json describe(const ps::PatternGuarantee& profile, const char* example) | calls analysis, std::string, pp::name, plan; returns result; growth push_back; 2 loop sites; source comment (unverified): // These JSON values are test exports for human inspection, outside query · [reviewed contract](#b0009) |
| [B0010 · 77–90](../../../../../tests/unit/update_pattern_profile_test.cpp#L77) | Callable definition: Json describe(const rs::PatternGuarantee& profile, const char* example) | calls selected, enforcement, stamp, selected_plan_matches_capture; returns result · [reviewed contract](#b0010) |
| [B0011 · 91–93](../../../../../tests/unit/update_pattern_profile_test.cpp#L91) | Explanatory comments or spacing. | source comment (unverified): // The profile must name the selected candidate, native program and exact rules; · [reviewed contract](#b0011) |
| [B0012 · 94–106](../../../../../tests/unit/update_pattern_profile_test.cpp#L94) | Callable definition: ps::PatternGuarantee qualified(const ps::Selection& selected, pp::SufficientCase expected) | calls pattern_guarantee, check, has_value, analysis; guard const auto value = selected.pattern_guarantee(); check(value.has_value(), "proved selection omitted…; returns *value; source comment (unverified): // The profile must name the selected candidate, native program and exact rules; · [reviewed contract](#b0012) |
| [B0013 · 107–107](../../../../../tests/unit/update_pattern_profile_test.cpp#L107) | Explanatory comments or spacing. |  |
| [B0014 · 108–136](../../../../../tests/unit/update_pattern_profile_test.cpp#L108) | Callable definition: void pure_contract(bool indexed, Json& reports) | calls c02_test::fixture, c02_test::candidates, compile, c05_test::complete; guard check(!baseline.pattern_guarantee(), "undeclared selection fabricated a pattern profile");; returns edge.basis != pp::EdgeBasis::unproved; growth push_back · [reviewed contract](#b0014) |
| [B0015 · 137–139](../../../../../tests/unit/update_pattern_profile_test.cpp#L137) | Explanatory comments or spacing. | source comment (unverified): // Constant routes and arbitrary height-one events are positive proved cases, · [reviewed contract](#b0015) |
| [B0016 · 140–175](../../../../../tests/unit/update_pattern_profile_test.cpp#L140) | Callable definition: void simple_routes(Json& reports) | calls c02_test::candidates, compile, c05_test::complete, ps::select; guard check(profile.analysis().transfer == pp::Transfer::not_required, "constant profile invented a sourc…; growth push_back; 1 loop sites; source comment (unverified): // Constant routes and arbitrary height-one events are positive proved cases, · [reviewed contract](#b0016) |
| [B0017 · 176–176](../../../../../tests/unit/update_pattern_profile_test.cpp#L176) | Explanatory comments or spacing. |  |
| [B0018 · 177–192](../../../../../tests/unit/update_pattern_profile_test.cpp#L177) | Callable definition: void taller_contract(Json& reports) | calls pattern_test::height_three_fixture, pattern_test::height_three_family, compile, size; guard check(profile.analysis().height == 3 && std::any_of(profile.analysis().edges.begin(), profile.analy…; returns edge.basis == pp::EdgeBasis::subtree_insertion_only; growth insert, push_back; 2 loop sites · [reviewed contract](#b0018) |
| [B0019 · 193–195](../../../../../tests/unit/update_pattern_profile_test.cpp#L193) | Explanatory comments or spacing. | source comment (unverified): // Profiles own the capture graph and remain as-of values after advancement, · [reviewed contract](#b0019) |
| [B0020 · 196–239](../../../../../tests/unit/update_pattern_profile_test.cpp#L196) | Callable definition: rs::PatternGuarantee live_contract(bool indexed, Json& reports) | calls c02_test::fixture, c02_test::candidates, compile, request; guard check(!plain.pattern_guarantee(), "a monitor without requested analysis fabricated a current profil…; returns latest; growth insert, push_back; source comment (unverified): // Profiles own the capture graph and remain as-of values after advancement, · [reviewed contract](#b0020) |
| [B0021 · 240–242](../../../../../tests/unit/update_pattern_profile_test.cpp#L240) | Explanatory comments or spacing. | source comment (unverified): // Window metadata commands and physical epochs use different progress domains. · [reviewed contract](#b0021) |
| [B0022 · 243–277](../../../../../tests/unit/update_pattern_profile_test.cpp#L243) | Callable definition: void window_contract(bool indexed, Json& reports) | calls c02_test::fixture, c02_test::candidates, compile, request; guard check(selected.analysis().sufficient == pp::SufficientCase::height_two_edges &&; growth push_back; source comment (unverified): // Window metadata commands and physical epochs use different progress domains. · [reviewed contract](#b0022) |
| [B0023 · 278–280](../../../../../tests/unit/update_pattern_profile_test.cpp#L278) | Explanatory comments or spacing. | source comment (unverified): // A real measured replacement is initially a proposed plan, not the installed · [reviewed contract](#b0023) |
| [B0024 · 281–308](../../../../../tests/unit/update_pattern_profile_test.cpp#L281) | Callable definition: void replacement_contract(bool indexed, Json& reports) | calls c02_test::fixture, c02_test::candidates, compile, request; guard check(!proposed.selected_plan_matches_capture() &&; growth push_back; source comment (unverified): // A real measured replacement is initially a proposed plan, not the installed · [reviewed contract](#b0024) |
| [B0025 · 309–310](../../../../../tests/unit/update_pattern_profile_test.cpp#L309) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0025) |
| [B0026 · 311–329](../../../../../tests/unit/update_pattern_profile_test.cpp#L311) | Callable definition: int main(int argc, char** argv) | calls Json::array, simple_routes, taller_contract, pure_contract; guard check(selected.analysis().declaration.matches(selected.plan()) && retained.enforcement().monitored_…; returns 1; 1 loop sites · [reviewed contract](#b0026) |

## B0001

[Lines 1–26](../../../../../tests/unit/update_pattern_profile_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L26:sha256:9e4bef376e085af90785a4444ac74c0ecb0beb01780851bdcc3d26bed7c46a79
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the existing planner/session/restore/durability test fixtures and JSON exporter. |
| inputs / outputs | Include native APIs, real search/provider fixtures and allocation-denial helpers; open test scope and bind short namespace names. |
| invariants | Includes/aliases supply no candidate, runtime or correctness proof. JSON is test instrumentation, not a new production writer. |
| ownership | No query owner is created by declarations. |
| failure | Missing headers/names fail compilation; no runtime fallback. |
| cost | Preprocessing only. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0002

[Lines 27–31](../../../../../tests/unit/update_pattern_profile_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L31:sha256:0f1316cdd545cae2b5e3b2f9dc883c3d251ecd07562b1ef107d1973a9165c3cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile one genuine retained candidate under a requested storage backend. |
| inputs / outputs | Borrow fixture/family, lower candidate0, optionally select indexed storage, return standalone native program. |
| invariants | Search/provider supplies tree authority. The helper is not a minimum-height oracle; constant contradictory bodies require their canonical empty executable tree separately. |
| ownership | Returned program owns its metadata; fixture/family are borrowed during compilation. |
| failure | Compiler/allocation failures propagate to test entry. |
| cost | Query-size-dependent setup, not a measured maintenance benchmark. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0003

[Lines 32–36](../../../../../tests/unit/update_pattern_profile_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L36:sha256:530c3418e4923f948f2791b8f7c39441b568dee2d7c551443fe4edcf7c5feaff
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a height-only request with actual source-bound rules. |
| inputs / outputs | Capture borrowed rule span into program account and return the request. |
| invariants | Rules are assumptions until an actual Session monitors them; capture grants no trace proof. |
| ownership | Declaration retains its funded immutable rule data; input span is not retained. |
| failure | Invalid rules or allocation/resource failures propagate. |
| cost | Existing declaration validation/copy costs depend on rule count; outside allocation-free getter controls. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0004

[Lines 37–40](../../../../../tests/unit/update_pattern_profile_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L40:sha256:773c4c552cc58e52cb0b803c8612973547e7eeb5cbfbe0a99dd02093f2e09aeb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure Session monitoring from the exact requested declaration. |
| inputs / outputs | Copy immutable declaration handle into UpdatePatternOptions within ordinary SessionOptions. |
| invariants | Caller supplies a present declaration; actual Session factory performs source/origin admission. |
| ownership | Shared handle only; actual factory funds its own receiving copy. |
| failure | No new translation boundary; factory errors propagate at its call site. |
| cost | Fixed descriptor construction. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0005

[Lines 41–41](../../../../../tests/unit/update_pattern_profile_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L41:sha256:88c6615abfd5de6d42ee3a1316f7368a82573a5d801df66d307f53041ff36728
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a fixed SHA field into caller-owned text for test JSON. |
| inputs / outputs | Return std::string containing exactly64 stored characters. |
| invariants | Text is a diagnostic, not authentication or import authority. |
| ownership | Ordinary test string owns its copy outside native profile accounting. |
| failure | String allocation failure propagates. |
| cost | Fixed64-byte copy plus ordinary allocation. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0006

[Lines 42–42](../../../../../tests/unit/update_pattern_profile_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L42:sha256:c6169ff871b7de76d38de53114b206987f9a759bcbdd58ff841e90c7279314cd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow encoded Session image bytes for the restore control. |
| inputs / outputs | Return a string_view over the image byte vector. |
| invariants | Caller keeps the image alive and unchanged throughout restore. |
| ownership | Borrow only; no image or row copy. |
| failure | No new failure boundary. |
| cost | O(1), no allocation. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0007

[Lines 43–47](../../../../../tests/unit/update_pattern_profile_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L47:sha256:48634ad617ac695f0c0026f6ab645ff768fbebbba715677d36f072d46be4a088
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit one actual typed physical event through the Session. |
| inputs / outputs | Move PhysicalSetUpdate into a transport batch; require queue/begin success and finish the epoch through the existing fixture. |
| invariants | Native maintenance and result publication really execute; this helper alone is no result oracle or constant-work claim. |
| ownership | Batch/session take event ownership; finish helper drains output. |
| failure | Admission assertion or native semantic/resource failures propagate. |
| cost | Actual event/maintenance/output costs; not the zero-allocation accessor seam. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0008

[Lines 48–50](../../../../../tests/unit/update_pattern_profile_test.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L50:sha256:28460a20431a1ecac5cd148724eb82f216f2e0234d67f7d5b0b14cd3b4c13edd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain that JSON is an explicit test export. |
| inputs / outputs | Source comments or scope delimiter only; adjacent callable cards specify executable behavior. |
| invariants | Prose and delimiters supply no independent proof or enforcement. |
| ownership | No runtime owner. |
| failure | No runtime failure behavior. |
| cost | No executable work. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0009

[Lines 51–76](../../../../../tests/unit/update_pattern_profile_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L76:sha256:d0690b6523c71d11dc54cae0f03a103840cf149078fe7b7a0af14fa13c5ccc2e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a conditional selected-plan profile for human inspection. |
| inputs / outputs | Borrow profile/example label; serialize exact bound/model/proof link, candidate height/key, compiled route/operator height/hash, source rules/transfer and every native edge premise. |
| invariants | Candidate and executable geometry remain separate. This is a caller-owned JSON example, not a structural certificate, live-enforcement claim or production API cost. |
| ownership | Profile retains the native graph; returned ordinary JSON owns explicit copied text/arrays. |
| failure | JSON/string allocation failures propagate, outside denial controls. |
| cost | O(rules+edges+encoded bytes) export plus ordinary allocator costs. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0010

[Lines 77–90](../../../../../tests/unit/update_pattern_profile_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L90:sha256:63c478f1a006e52f3e60ac3a3804bcc66c791fec5de0c9304defae52c1626ab8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an actual captured Session qualification with selected-plan context. |
| inputs / outputs | Extend conditional JSON with as-of owner/stamp, exact plan-match flag, monitor origins/through-counters, source/physical hashes, violation and explicit history trust. |
| invariants | No retrospective-work or future-freshness claim. Matching physical identities is reported separately from shared source premises. |
| ownership | Native profile remains borrowed; returned ordinary JSON owns its diagnostic copies. |
| failure | Export allocations propagate; native getters themselves do not allocate. |
| cost | Conditional export cost plus fixed fields/hash copies. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0011

[Lines 91–93](../../../../../tests/unit/update_pattern_profile_test.cpp#L91); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L93:sha256:7478bc80717c9fd841378eabcc4fa18520efe6fc72f33ff2e985c36c8ce3a809
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain exact selected context and shared ownership checks. |
| inputs / outputs | Source comments or scope delimiter only; adjacent callable cards specify executable behavior. |
| invariants | Prose and delimiters supply no independent proof or enforcement. |
| ownership | No runtime owner. |
| failure | No runtime failure behavior. |
| cost | No executable work. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0012

[Lines 94–106](../../../../../tests/unit/update_pattern_profile_test.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L106:sha256:7195e97ee153a521d8afbbb6f149507d763a6996e3cf269165f5c3497271d4a6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert the actual selected report/program binding and public model. |
| inputs / outputs | Require a profile, expected sufficient tag, matching source declaration, exact candidate key and identical report/program addresses; return the owning profile. |
| invariants | Address checks ensure shared native context rather than cloned payload. Expected tags are test assertions, not authority for constructing a profile. |
| ownership | Returned descriptor shares selected Data and survives original handle release. |
| failure | Assertions throw through the single test entry boundary. |
| cost | Fixed checks plus existing source/hash/key comparisons; no throughput claim. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0014

[Lines 108–136](../../../../../tests/unit/update_pattern_profile_test.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L108-L136:sha256:f0ed1feb16d97b9f4270800cab2ddb65f1a50e0a61624654be6c9af17847362f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise absence/unknown, exact cache rules and a changed compatible-plan decision. |
| inputs / outputs | For each backend, select undeclared and empty-rule cases, then insertion-only/cached and mixed requests; inspect actual selected profile and positive native edges. |
| invariants | Unknown cannot publish a selection/profile. Cache artifacts retain exact rules and chosen context. Mixed conditions change the actual selected index, not just a label. |
| ownership | Fixtures/cache/selections own their metadata; returned profile shares existing owners. |
| failure | Any unexpected compiler/selection/ownership result fails the test. |
| cost | Finite real search/lowering/cache setup and analyses; not a performance benchmark. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0015

[Lines 137–139](../../../../../tests/unit/update_pattern_profile_test.cpp#L137); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L137-L139:sha256:88ac4b7bea5ed4dfae8ce623aec7630ff7f9216a027c04aa7126b3d223570b28
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain positive constant/height-one cases and absent requests. |
| inputs / outputs | Source comments or scope delimiter only; adjacent callable cards specify executable behavior. |
| invariants | Prose and delimiters supply no independent proof or enforcement. |
| ownership | No runtime owner. |
| failure | No runtime failure behavior. |
| cost | No executable work. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0016

[Lines 140–175](../../../../../tests/unit/update_pattern_profile_test.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L140-L175:sha256:d83f8075499ee95817a540cad674d0f69641b47f277c2b1e824d1359c7d3a92b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check constant, projected height-one and contradictory-body profile geometry. |
| inputs / outputs | Use real candidate families and physical source admission; require constant_result/not_required, arbitrary height-one event mapping, and original height2 versus empty executable height0 for a contradictory nonempty body. |
| invariants | No insertion/FIFO rule is invented for height-one. Constant lowering does not replace original structural authority; both geometries are exported explicitly. |
| ownership | Native programs/profiles own their handles; ordinary fixtures are temporary. |
| failure | Proof/search/compiler/assertion failures propagate without skips. |
| cost | Finite fixture/proof construction; profile reads remain constant descriptor work. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0018

[Lines 177–192](../../../../../tests/unit/update_pattern_profile_test.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L177-L192:sha256:e60cbf491eaff5e7581f7e8f4bacaa44e9d507b40c26b7c9bd8ea9863fba1848
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the taller whole-subtree premise in a genuine height-three profile. |
| inputs / outputs | Run exact shared fixture/provider, leave one native root mutable and other rules insertion-only, select and require subtree_edges with an explicit subtree basis. |
| invariants | True subtree means child plus all native descendants. A finite genuine candidate prefix is not family exhaustion or cost optimality. |
| ownership | Fixture/proof/program/declaration/profile own their usual metadata; no new runtime state is introduced. |
| failure | Any missing proof/profile/premise fails the test. |
| cost | Exact setup/analysis work is separate from profile access; no timing claim. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0019

[Lines 193–195](../../../../../tests/unit/update_pattern_profile_test.cpp#L193); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L193-L195:sha256:4655dfebc4a4e4bdb8d7f50007189cd7f4edaf5ac13813ba8c40abf51e59a57b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain captured profile lifetime and allocation-free access. |
| inputs / outputs | Source comments or scope delimiter only; adjacent callable cards specify executable behavior. |
| invariants | Prose and delimiters supply no independent proof or enforcement. |
| ownership | No runtime owner. |
| failure | No runtime failure behavior. |
| cost | No executable work. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0020

[Lines 196–239](../../../../../tests/unit/update_pattern_profile_test.cpp#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L196-L239:sha256:d6bfce2274926f7c830eec8b4a6f27d55e6851e15f2f5e81bdea4a02c48969d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove allocation-free profile access, as-of behavior and retained lifetime. |
| inputs / outputs | For both backends capture real typed Session profiles; deny C++ new from cut0 while reading/copying/moving profiles; advance then reject an erase; require old captures unchanged, rejected current selection absent, and profile valid after owner release. |
| invariants | No native allocation bytes change at accessor seam. A historical clean capture remains historical after a later violation; it is never silently refreshed. |
| ownership | Profile shares capture/selection Data and their native owners after original handles/session are destroyed. |
| failure | Expected semantic Error is narrowly checked; all other failures propagate. Global new denial stays active during getter/copy/destruction scope. |
| cost | Two finite allocation-free controls; actual capture/update/rejection setup remains separately costly. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0021

[Lines 240–242](../../../../../tests/unit/update_pattern_profile_test.cpp#L240); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L240-L242:sha256:1f65b82ecc4b4ab68c452ac4912004f7cfff25a463733a02dc64eb47fab90bc3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain physical/command progress and restored-history trust. |
| inputs / outputs | Source comments or scope delimiter only; adjacent callable cards specify executable behavior. |
| invariants | Prose and delimiters supply no independent proof or enforcement. |
| ownership | No runtime owner. |
| failure | No runtime failure behavior. |
| cost | No executable work. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0022

[Lines 243–277](../../../../../tests/unit/update_pattern_profile_test.cpp#L243); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L243-L277:sha256:d197c52ec7af1d28fa78dfec4434ef2163efb9c2d1a19f353860358d0aba8920
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check FIFO monitor command/physical domains and trusted binary restore. |
| inputs / outputs | Insert duplicate labels, issue a metadata watermark, capture a positive FIFO-leaf profile, restore actual image, then remove a redundant label; compare physical stamp1 with command progress3/4 and preserved old capture. |
| invariants | Restore explicitly reports trusted_restored_checkpoint; metadata-only commands do not advance physical sequence. The source/tree premise comes from actual monitored request and selection. |
| ownership | Session/image/profile owners preserve their own contexts; returned example copies only explicit JSON. |
| failure | Admission, restore, compiler or assertion failures propagate. |
| cost | Finite native/checkpoint/capture work; no claim about all histories or restore cost. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0023

[Lines 278–280](../../../../../tests/unit/update_pattern_profile_test.cpp#L278); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L278-L280:sha256:2d32dd0a871fe2113e0b2590dd029e595a86a5aafc37039c5d4b88b67bda11c7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain proposed versus installed identity during real replacement. |
| inputs / outputs | Source comments or scope delimiter only; adjacent callable cards specify executable behavior. |
| invariants | Prose and delimiters supply no independent proof or enforcement. |
| ownership | No runtime owner. |
| failure | No runtime failure behavior. |
| cost | No executable work. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0024

[Lines 281–308](../../../../../tests/unit/update_pattern_profile_test.cpp#L281); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L281-L308:sha256:aa9028c5315c6de4c5e8cf5af2969e17d009c6570a809411aff3e5240d551d04
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check selected-plan mismatch and later match through real durable replacement. |
| inputs / outputs | Create monitored window and journal/generation, make measured compatible choice, require proposed identity mismatch, actually verify/publish compiled artifact, then recapture and require installed identity match while old profile stays unchanged. |
| invariants | Only fresh capture reflects replacement. The positive support model charges new initialization and never measures old-plan work retrospectively. |
| ownership | Existing directory fixture owns temporary durable files; Session/artifact/captures retain their real native owners. |
| failure | Durable preparation/publication or assertion failure reaches the test entry; no fake receipt or silently accepted failed replacement. |
| cost | Real finite durable replacement and capture work on each backend, outside getter cost controls. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0025

[Lines 309–310](../../../../../tests/unit/update_pattern_profile_test.cpp#L309); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L309-L310:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous test scope. |
| inputs / outputs | Source comments or scope delimiter only; adjacent callable cards specify executable behavior. |
| invariants | Prose and delimiters supply no independent proof or enforcement. |
| ownership | No runtime owner. |
| failure | No runtime failure behavior. |
| cost | No executable work. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |

## B0026

[Lines 311–329](../../../../../tests/unit/update_pattern_profile_test.cpp#L311); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L311-L329:sha256:ea8a82b2b694564a57a4a92c993270dbb2282ce258722b84c10caa412b084f46
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all profile controls and optionally write complete human-readable examples. |
| inputs / outputs | Invoke constant/height-one/taller and both backend pure/live/window/replacement cases; verify surviving returned profile; write profiles.json under the supplied build output directory and print actual count. |
| invariants | Expected current count is17 after root refinement; external recorder execution, not source expectations, establishes a pass. The examples are test exports and do not claim full-suite or universal correctness. |
| ownership | All fixture/profile owners unwind at function exit; ordinary JSON/output stream are caller/test resources. |
| failure | One std::exception boundary prints failure and returns nonzero; no per-operation error framework. |
| cost | Runs the finite listed cases and explicit JSON export; not a production benchmark. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/support/update_pattern_fixture.hpp](../../../../../tests/support/update_pattern_fixture.hpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp) |
