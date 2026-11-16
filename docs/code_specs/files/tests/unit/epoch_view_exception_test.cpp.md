# `tests/unit/epoch_view_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/epoch_view_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c2750499977c02487faabc61536583eaa798db5623337e7a18aac469478a76c2`. 1070 lines partitioned into 99 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–26](../../../../../tests/unit/epoch_view_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // This executable owns a persistent global-new injector so factory and next · [reviewed contract](#b0001) |
| [B0002 · 27–34](../../../../../tests/unit/epoch_view_exception_test.cpp#L27) | Callable definition: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes) | calls std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 35–41](../../../../../tests/unit/epoch_view_exception_test.cpp#L35) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0003) |
| [B0004 · 42–43](../../../../../tests/unit/epoch_view_exception_test.cpp#L42) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 44–44](../../../../../tests/unit/epoch_view_exception_test.cpp#L44) | Callable definition: void* operator new(std::size_t bytes) | calls malloc_new; returns malloc_new(bytes); growth new · [reviewed contract](#b0005) |
| [B0006 · 45–45](../../../../../tests/unit/epoch_view_exception_test.cpp#L45) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 46–46](../../../../../tests/unit/epoch_view_exception_test.cpp#L46) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0007) |
| [B0008 · 47–47](../../../../../tests/unit/epoch_view_exception_test.cpp#L47) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0008) |
| [B0009 · 48–48](../../../../../tests/unit/epoch_view_exception_test.cpp#L48) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0009) |
| [B0010 · 49–49](../../../../../tests/unit/epoch_view_exception_test.cpp#L49) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0010) |
| [B0011 · 50–63](../../../../../tests/unit/epoch_view_exception_test.cpp#L50) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;SupportRuntime::PendingEpoch&gt;); · [reviewed contract](#b0011) |
| [B0012 · 64–66](../../../../../tests/unit/epoch_view_exception_test.cpp#L64) | Callable definition: void check(bool condition, std::string_view message) | calls std::runtime_error, std::string; guard void check(bool condition, std::string_view message) { · [reviewed contract](#b0012) |
| [B0013 · 67–67](../../../../../tests/unit/epoch_view_exception_test.cpp#L67) | Explanatory comments or spacing. |  |
| [B0014 · 68–77](../../../../../tests/unit/epoch_view_exception_test.cpp#L68) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls check, code, std::runtime_error, std::string; guard check(failure.code() == code, "unexpected epoch-view error code"); · [reviewed contract](#b0014) |
| [B0015 · 78–78](../../../../../tests/unit/epoch_view_exception_test.cpp#L78) | Explanatory comments or spacing. |  |
| [B0016 · 79–79](../../../../../tests/unit/epoch_view_exception_test.cpp#L79) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0016) |
| [B0017 · 80–80](../../../../../tests/unit/epoch_view_exception_test.cpp#L80) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0017) |
| [B0018 · 81–83](../../../../../tests/unit/epoch_view_exception_test.cpp#L81) | Callable definition: Row a_row(std::int64_t x, std::int64_t y, std::string witness) | calls n, s, std::move; returns {n(x), n(y), s(std::move(witness))} · [reviewed contract](#b0018) |
| [B0019 · 84–86](../../../../../tests/unit/epoch_view_exception_test.cpp#L84) | Callable definition: Row b_row(std::int64_t x, std::int64_t y, std::string witness) | calls n, s, std::move; returns {n(x), n(y), s(std::move(witness))} · [reviewed contract](#b0019) |
| [B0020 · 87–89](../../../../../tests/unit/epoch_view_exception_test.cpp#L87) | Callable definition: Row c_row(std::int64_t x, std::int64_t z, std::string witness) | calls n, s, std::move; returns {n(x), n(z), s(std::move(witness))} · [reviewed contract](#b0020) |
| [B0021 · 90–90](../../../../../tests/unit/epoch_view_exception_test.cpp#L90) | Explanatory comments or spacing. |  |
| [B0022 · 91–91](../../../../../tests/unit/epoch_view_exception_test.cpp#L91) | Callable definition: const Row& inserted_a() | calls a_row; returns value · [reviewed contract](#b0022) |
| [B0023 · 92–92](../../../../../tests/unit/epoch_view_exception_test.cpp#L92) | Callable definition: const Row& inserted_b() | calls b_row; returns value · [reviewed contract](#b0023) |
| [B0024 · 93–93](../../../../../tests/unit/epoch_view_exception_test.cpp#L93) | Callable definition: const Row& inserted_c() | calls c_row; returns value · [reviewed contract](#b0024) |
| [B0025 · 94–94](../../../../../tests/unit/epoch_view_exception_test.cpp#L94) | Callable definition: const Row& erased_b() | calls b_row; returns value · [reviewed contract](#b0025) |
| [B0026 · 95–95](../../../../../tests/unit/epoch_view_exception_test.cpp#L95) | Callable definition: const Row& later_a() | calls a_row; returns value · [reviewed contract](#b0026) |
| [B0027 · 96–96](../../../../../tests/unit/epoch_view_exception_test.cpp#L96) | Callable definition: const Row& later_b() | calls b_row; returns value · [reviewed contract](#b0027) |
| [B0028 · 97–103](../../../../../tests/unit/epoch_view_exception_test.cpp#L97) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0028) |
| [B0029 · 104–124](../../../../../tests/unit/epoch_view_exception_test.cpp#L104) | Callable definition: PhysicalPlan make_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree); source comment (unverified): // C shares A's hidden witness and contributes to the query, but lies outside · [reviewed contract](#b0029) |
| [B0030 · 125–125](../../../../../tests/unit/epoch_view_exception_test.cpp#L125) | Explanatory comments or spacing. |  |
| [B0031 · 126–130](../../../../../tests/unit/epoch_view_exception_test.cpp#L126) | Callable definition: SupportOptions support_options() | calls ; returns result · [reviewed contract](#b0031) |
| [B0032 · 131–131](../../../../../tests/unit/epoch_view_exception_test.cpp#L131) | Explanatory comments or spacing. |  |
| [B0033 · 132–136](../../../../../tests/unit/epoch_view_exception_test.cpp#L132) | Callable definition: PhysicalRuntimeOptions physical_options() | calls support_options; returns result · [reviewed contract](#b0033) |
| [B0034 · 137–137](../../../../../tests/unit/epoch_view_exception_test.cpp#L137) | Explanatory comments or spacing. |  |
| [B0035 · 138–142](../../../../../tests/unit/epoch_view_exception_test.cpp#L138) | Callable definition: const std::vector&lt;Row&gt;& a_rows() | calls a_row; returns value · [reviewed contract](#b0035) |
| [B0036 · 143–147](../../../../../tests/unit/epoch_view_exception_test.cpp#L143) | Callable definition: const std::vector&lt;Row&gt;& b_rows() | calls b_row; returns value · [reviewed contract](#b0036) |
| [B0037 · 148–152](../../../../../tests/unit/epoch_view_exception_test.cpp#L148) | Callable definition: const std::vector&lt;Row&gt;& c_rows() | calls c_row; returns value · [reviewed contract](#b0037) |
| [B0038 · 153–156](../../../../../tests/unit/epoch_view_exception_test.cpp#L153) | Callable definition: const std::vector&lt;Row&gt;& base_results() | calls n; returns value · [reviewed contract](#b0038) |
| [B0039 · 157–161](../../../../../tests/unit/epoch_view_exception_test.cpp#L157) | Callable definition: const std::vector&lt;Row&gt;& inserted_results() | calls n; returns value · [reviewed contract](#b0039) |
| [B0040 · 162–165](../../../../../tests/unit/epoch_view_exception_test.cpp#L162) | Callable definition: const std::vector&lt;Row&gt;& erased_results() | calls n; returns value · [reviewed contract](#b0040) |
| [B0041 · 166–169](../../../../../tests/unit/epoch_view_exception_test.cpp#L166) | Callable definition: const std::vector&lt;Row&gt;& x_one_results() | calls n; returns value · [reviewed contract](#b0041) |
| [B0042 · 170–170](../../../../../tests/unit/epoch_view_exception_test.cpp#L170) | Explanatory comments or spacing. |  |
| [B0043 · 171–183](../../../../../tests/unit/epoch_view_exception_test.cpp#L171) | Callable definition: SupportRuntime make_support(const PhysicalPlan& plan) | calls support_options, a_rows, apply, b_rows; guard check(runtime.sequence() == sequence - 1 && runtime.has_answer(), "support epoch-view fixture did n…; returns runtime; growth insert; 3 loop sites · [reviewed contract](#b0043) |
| [B0044 · 184–184](../../../../../tests/unit/epoch_view_exception_test.cpp#L184) | Explanatory comments or spacing. |  |
| [B0045 · 185–197](../../../../../tests/unit/epoch_view_exception_test.cpp#L185) | Callable definition: PhysicalRuntime make_physical(const PhysicalPlan& plan) | calls physical_options, a_rows, apply, b_rows; guard check(runtime.sequence() == sequence - 1 && runtime.has_answer(), "physical epoch-view fixture did …; returns runtime; growth insert; 3 loop sites · [reviewed contract](#b0045) |
| [B0046 · 198–198](../../../../../tests/unit/epoch_view_exception_test.cpp#L198) | Explanatory comments or spacing. |  |
| [B0047 · 199–203](../../../../../tests/unit/epoch_view_exception_test.cpp#L199) | Callable definition: io::Json row_image(const Row& row) | calls io::Json::array, push_back, io::write_scalar; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0047) |
| [B0048 · 204–204](../../../../../tests/unit/epoch_view_exception_test.cpp#L204) | Explanatory comments or spacing. |  |
| [B0049 · 205–208](../../../../../tests/unit/epoch_view_exception_test.cpp#L205) | Callable definition: io::Json support_snapshot_image(const SupportSnapshot& snapshot, const auto& plan) | calls io::write_support_snapshot; returns {{@ , snapshot.sequence}, {@ , snapshot.has_answer}, · [reviewed contract](#b0049) |
| [B0050 · 209–209](../../../../../tests/unit/epoch_view_exception_test.cpp#L209) | Explanatory comments or spacing. |  |
| [B0051 · 210–212](../../../../../tests/unit/epoch_view_exception_test.cpp#L210) | Callable definition: io::Json state_image(const SupportRuntime& runtime) | calls support_snapshot_image, snapshot, plan; returns support_snapshot_image(runtime.snapshot(), runtime.plan()) · [reviewed contract](#b0051) |
| [B0052 · 213–213](../../../../../tests/unit/epoch_view_exception_test.cpp#L213) | Explanatory comments or spacing. |  |
| [B0053 · 214–231](../../../../../tests/unit/epoch_view_exception_test.cpp#L214) | Callable definition: io::Json physical_snapshot_image(const PhysicalSnapshot& snapshot, const auto& plan) | calls io::Json::array, push_back, row_image, std::move; returns {{@ , snapshot.sequence}, {@ , std::move(physical)},; growth push_back; 4 loop sites · [reviewed contract](#b0053) |
| [B0054 · 232–232](../../../../../tests/unit/epoch_view_exception_test.cpp#L232) | Explanatory comments or spacing. |  |
| [B0055 · 233–249](../../../../../tests/unit/epoch_view_exception_test.cpp#L233) | Callable definition: io::Json state_image(const PhysicalRuntime& runtime) | calls snapshot, physical_snapshot_image, plan, io::Json::array; guard check(handle.has_value(), "physical epoch-view row lost its public source handle");; returns result; growth push_back; 2 loop sites · [reviewed contract](#b0055) |
| [B0056 · 250–250](../../../../../tests/unit/epoch_view_exception_test.cpp#L250) | Explanatory comments or spacing. |  |
| [B0057 · 251–253](../../../../../tests/unit/epoch_view_exception_test.cpp#L251) | Callable definition: io::Json pending_image(const SupportRuntime::PendingEpoch& pending, const PhysicalPlan& plan) | calls support_snapshot_image, snapshot; returns support_snapshot_image(pending.snapshot(), plan) · [reviewed contract](#b0057) |
| [B0058 · 254–254](../../../../../tests/unit/epoch_view_exception_test.cpp#L254) | Explanatory comments or spacing. |  |
| [B0059 · 255–264](../../../../../tests/unit/epoch_view_exception_test.cpp#L255) | Callable definition: io::Json pending_image(const PhysicalRuntime::PendingUpdate& pending, const PhysicalPlan& plan) | calls physical_snapshot_image, snapshot, preview, row_image; returns result · [reviewed contract](#b0059) |
| [B0060 · 265–265](../../../../../tests/unit/epoch_view_exception_test.cpp#L265) | Explanatory comments or spacing. |  |
| [B0061 · 266–274](../../../../../tests/unit/epoch_view_exception_test.cpp#L266) | Callable definition: void sort_rows(std::vector&lt;Row&gt;& rows) | calls std::sort, begin, end, size; returns lx &lt; rx; std::get&lt;std::int64_t&gt;(left\[1\]) &lt; std::get&lt;std::int64_t&gt;(right\[1\]) · [reviewed contract](#b0061) |
| [B0062 · 275–275](../../../../../tests/unit/epoch_view_exception_test.cpp#L275) | Explanatory comments or spacing. |  |
| [B0063 · 276–287](../../../../../tests/unit/epoch_view_exception_test.cpp#L276) | Callable definition: std::vector&lt;Row&gt; drain(Cursor& cursor) | calls next, push_back, crown::storage::export_row, values; guard check(cursor.state() == ResultCursorState::exhausted && !cursor.active(),; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0063) |
| [B0064 · 288–288](../../../../../tests/unit/epoch_view_exception_test.cpp#L288) | Explanatory comments or spacing. |  |
| [B0065 · 289–292](../../../../../tests/unit/epoch_view_exception_test.cpp#L289) | Callable definition: std::vector&lt;Row&gt; drain(SupportRuntime::EpochView& view, ResultCursorOptions options = {}) | calls results; returns drain(cursor) · [reviewed contract](#b0065) |
| [B0066 · 293–293](../../../../../tests/unit/epoch_view_exception_test.cpp#L293) | Explanatory comments or spacing. |  |
| [B0067 · 294–348](../../../../../tests/unit/epoch_view_exception_test.cpp#L294) | Callable definition: void check_support_view_factory_sweep(const PhysicalPlan& plan, SnapshotSide side, bool erase) | calls make_support, state_image, begin_epoch, sequence; guard check(pending.stage(NodeId{2}, erased_b()), "support delete view-factory fixture was a no-op");; growth insert; 1 loop sites · [reviewed contract](#b0067) |
| [B0068 · 349–349](../../../../../tests/unit/epoch_view_exception_test.cpp#L349) | Explanatory comments or spacing. |  |
| [B0069 · 350–387](../../../../../tests/unit/epoch_view_exception_test.cpp#L350) | Callable definition: void check_physical_view_factory_sweep(const PhysicalPlan& plan, SnapshotSide side) | calls make_physical, state_image, prepare, sequence; guard check(failures &gt; 0, "physical view factory sweep missed its allocation failures");; growth insert; 1 loop sites · [reviewed contract](#b0069) |
| [B0070 · 388–388](../../../../../tests/unit/epoch_view_exception_test.cpp#L388) | Explanatory comments or spacing. |  |
| [B0071 · 389–433](../../../../../tests/unit/epoch_view_exception_test.cpp#L389) | Callable definition: void check_completion_factory_sweep(const PhysicalPlan& plan, bool physical) | calls emplace, make_physical, current_view, make_support; guard check(failures &gt; 0, "completions factory sweep missed its allocation failures");; returns coordinator-&gt;current_view(); support-&gt;current_view(); growth emplace; 1 loop sites · [reviewed contract](#b0071) |
| [B0072 · 434–434](../../../../../tests/unit/epoch_view_exception_test.cpp#L434) | Explanatory comments or spacing. |  |
| [B0073 · 435–454](../../../../../tests/unit/epoch_view_exception_test.cpp#L435) | Callable definition: void check_completion_validation(const PhysicalPlan& plan) | calls make_support, state_image, current_view, expect_error; guard check(drain(hidden_restriction) == std::vector&lt;Row&gt;{{n(1), n(10)}}, · [reviewed contract](#b0073) |
| [B0074 · 455–455](../../../../../tests/unit/epoch_view_exception_test.cpp#L455) | Explanatory comments or spacing. |  |
| [B0075 · 456–476](../../../../../tests/unit/epoch_view_exception_test.cpp#L456) | Callable definition: void check_completions_filter_paths(const PhysicalPlan& plan) | calls make_support, current_view, completions, n; guard check(drain(partial) == x_one_results(), "partial visible binding did not filter the live root buck… · [reviewed contract](#b0075) |
| [B0076 · 477–477](../../../../../tests/unit/epoch_view_exception_test.cpp#L477) | Explanatory comments or spacing. |  |
| [B0077 · 478–507](../../../../../tests/unit/epoch_view_exception_test.cpp#L478) | Callable definition: void check_rollback_aborts_linked_cursors_noalloc(const PhysicalPlan& plan) | calls make_support, begin_epoch, sequence, check; guard check(pending.stage(NodeId{1}, inserted_a()) && pending.stage(NodeId{2}, inserted_b()) &&; growth insert · [reviewed contract](#b0077) |
| [B0078 · 508–508](../../../../../tests/unit/epoch_view_exception_test.cpp#L508) | Explanatory comments or spacing. |  |
| [B0079 · 509–554](../../../../../tests/unit/epoch_view_exception_test.cpp#L509) | Callable definition: void check_commit_preserves_views_noalloc(const PhysicalPlan& plan) | calls make_support, sequence, begin_epoch, check; guard check(pending.stage(NodeId{1}, inserted_a()) && pending.stage(NodeId{2}, inserted_b()) &&; growth emplace, insert, push_back · [reviewed contract](#b0079) |
| [B0080 · 555–555](../../../../../tests/unit/epoch_view_exception_test.cpp#L555) | Explanatory comments or spacing. |  |
| [B0081 · 556–588](../../../../../tests/unit/epoch_view_exception_test.cpp#L556) | Callable definition: void check_pending_move_cleanup_noalloc(const PhysicalPlan& plan) | calls make_support, emplace, begin_epoch, sequence; guard check(destination-&gt;stage(NodeId{1}, inserted_a()), "move destination did not stage");; growth emplace, insert · [reviewed contract](#b0081) |
| [B0082 · 589–589](../../../../../tests/unit/epoch_view_exception_test.cpp#L589) | Explanatory comments or spacing. |  |
| [B0083 · 590–617](../../../../../tests/unit/epoch_view_exception_test.cpp#L590) | Callable definition: void check_pending_destruction_noalloc(const PhysicalPlan& plan) | calls make_support, emplace, begin_epoch, sequence; guard check(pending-&gt;stage(NodeId{1}, inserted_a()), "destruction fixture did not stage");; growth emplace, insert · [reviewed contract](#b0083) |
| [B0084 · 618–618](../../../../../tests/unit/epoch_view_exception_test.cpp#L618) | Explanatory comments or spacing. |  |
| [B0085 · 619–710](../../../../../tests/unit/epoch_view_exception_test.cpp#L619) | Callable definition: void check_physical_pending_lifecycle_noalloc(const PhysicalPlan& plan) | calls make_physical, prepare, sequence, inserted_a; guard check(saved && first.active() && second.active(), "physical pending fixture did not start its curso…; returns abandoned-&gt;view(SnapshotSide::after); growth emplace, insert, push_back · [reviewed contract](#b0085) |
| [B0086 · 711–711](../../../../../tests/unit/epoch_view_exception_test.cpp#L711) | Explanatory comments or spacing. |  |
| [B0087 · 712–771](../../../../../tests/unit/epoch_view_exception_test.cpp#L712) | Callable definition: void check_next_fault_sweep(const PhysicalPlan& plan, bool erase, SnapshotSide side, bool later) | calls base_results, erased_results, inserted_results, make_support; guard check(pending.stage(NodeId{2}, erased_b()), "delete next-fault fixture was a no-op");; growth insert; 1 loop sites · [reviewed contract](#b0087) |
| [B0088 · 772–772](../../../../../tests/unit/epoch_view_exception_test.cpp#L772) | Explanatory comments or spacing. |  |
| [B0089 · 773–817](../../../../../tests/unit/epoch_view_exception_test.cpp#L773) | Callable definition: void check_current_view_next_lease(const PhysicalPlan& plan, bool later) | calls make_support, state_image, current_view, completions; guard check(cursor.next().has_value() && cursor.next().has_value(), "later current-view fault prefix was …; growth insert; 1 loop sites · [reviewed contract](#b0089) |
| [B0090 · 818–818](../../../../../tests/unit/epoch_view_exception_test.cpp#L818) | Explanatory comments or spacing. |  |
| [B0091 · 819–876](../../../../../tests/unit/epoch_view_exception_test.cpp#L819) | Callable definition: void check_facade_destruction_stability(const PhysicalPlan& plan) | calls make_support, begin_epoch, sequence, check; guard check(pending.stage(NodeId{1}, inserted_a()) && pending.stage(NodeId{2}, inserted_b()) &&; growth emplace, insert, push_back · [reviewed contract](#b0091) |
| [B0092 · 877–877](../../../../../tests/unit/epoch_view_exception_test.cpp#L877) | Explanatory comments or spacing. |  |
| [B0093 · 878–882](../../../../../tests/unit/epoch_view_exception_test.cpp#L878) | Callable definition: std::vector&lt;Row&gt; reference_rows(const storage::ReferenceTable& table) | calls snapshot, push_back, crown::storage::export_row, values; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0093) |
| [B0094 · 883–883](../../../../../tests/unit/epoch_view_exception_test.cpp#L883) | Explanatory comments or spacing. |  |
| [B0095 · 884–974](../../../../../tests/unit/epoch_view_exception_test.cpp#L884) | Callable definition: void check_reference_journal_owned_cursor_lifecycle() | calls tuple, n, s, crown::storage::export_row; guard check(reference_rows(table) == std::vector&lt;Row&gt;{crown::storage::export_row(row1.values()), crown::s…; growth emplace, insert; 2 loop sites; source comment (unverified): // An ordinary cursor cannot advance while a journal owns the table. The · [reviewed contract](#b0095) |
| [B0096 · 975–975](../../../../../tests/unit/epoch_view_exception_test.cpp#L975) | Explanatory comments or spacing. |  |
| [B0097 · 976–1033](../../../../../tests/unit/epoch_view_exception_test.cpp#L976) | Callable definition: void check_reference_journal_cursor_fault_sweep() | calls tuple, n, s, insert; guard check(journal.insert(row3).inserted, "journal cursor fault fixture insert was a no-op");; growth emplace, insert; 1 loop sites; source comment (unverified): // Cleanup runs while persistent fail-zero is active. · [reviewed contract](#b0097) |
| [B0098 · 1034–1036](../../../../../tests/unit/epoch_view_exception_test.cpp#L1034) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0098) |
| [B0099 · 1037–1070](../../../../../tests/unit/epoch_view_exception_test.cpp#L1037) | Callable definition: int main() | calls make_plan, check_support_view_factory_sweep, check_physical_view_factory_sweep, check_completion_factory_sweep; returns 1 · [reviewed contract](#b0099) |

## B0001

[Lines 1–26](../../../../../tests/unit/epoch_view_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L26:sha256:c144c59f136895f74212341b803d04f55ee8502419a33c1b63766845143ab709
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare epoch_view_exception_test.cpp: include "crown/api/error.hpp", "crown/io/support.hpp", "crown/planner/lower.hpp", "crown/runtime/physical.hpp", "crown/storage/reference.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 27–34](../../../../../tests/unit/epoch_view_exception_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count one thread-local allocation-failure position and return malloc-backed storage for an admitted ordinary new call. |
| inputs / outputs | Requested byte count and fail_after enter; one selected failure throws std::bad_alloc, otherwise a non-null malloc result exits. |
| invariants | The position is checked before malloc; positive values decrement once, zero fails without calling malloc, and zero-byte requests ask malloc for one byte. |
| ownership | Successful replacement requests are backed by std::malloc and released by the matching replacement delete. The seam owns only thread-local fail_after; returned storage is caller-owned until its matching delete. |
| failure | A selected fail_after position throws std::bad_alloc at the replaced ordinary global new/new\[\] boundary; a real malloc null also throws. Raw malloc/realloc calls and operating-system calls are outside. Aligned and nothrow allocation overloads are not replaced. MemoryAccount allocations that pass account admission and reach ordinary ::operator new can be intercepted, but this suite does not lower memory_limit_bytes or inject MemoryFailure from an account limit. |
| cost | One fail-index branch and, for an admitted call, one malloc attempt. The index counts intercepted C++ allocation calls, not requested bytes, account charge, RSS, or CPU time. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0003

[Lines 35–41](../../../../../tests/unit/epoch_view_exception_test.cpp#L35); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm or disable the executable-local global-new failure point for one fixture scope. |
| inputs / outputs | Optional signed step enters construction; destruction sets fail_after to -1; forbid_allocations() changes it to zero. |
| invariants | Copy and assignment are deleted; a scope resets to disabled rather than restoring an enclosing value, so it is not a nesting stack. |
| ownership | Borrows only the thread-local fail_after scalar and owns no runtime or allocated product. |
| failure | Constructor/destructor and forbid_allocations are noexcept by their bodies; the guard does not interpose direct malloc or syscalls. |
| cost | Constant scalar bookkeeping; no allocation-count or byte counter is maintained. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0004

[Lines 42–43](../../../../../tests/unit/epoch_view_exception_test.cpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L43:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in epoch_view_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 44–44](../../../../../tests/unit/epoch_view_exception_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch scalar ordinary new through malloc_new. |
| inputs / outputs | A size enters and malloc-backed storage or std::bad_alloc exits. |
| invariants | Scalar and array calls share the same thread-local failure position; their matching delete overloads free the result. |
| ownership | Successful storage is returned to the C++ caller and released through the matching replacement delete. |
| failure | Only calls dispatched through this ordinary global overload are injected; raw malloc, aligned/nothrow forms, account-limit denial and syscalls are not separate injected faults. |
| cost | One seam call plus one malloc attempt if admitted. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0006

[Lines 45–45](../../../../../tests/unit/epoch_view_exception_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch array ordinary new\[\] through malloc_new. |
| inputs / outputs | A size enters and malloc-backed storage or std::bad_alloc exits. |
| invariants | Scalar and array calls share the same thread-local failure position; their matching delete overloads free the result. |
| ownership | Successful storage is returned to the C++ caller and released through the matching replacement delete. |
| failure | Only calls dispatched through this ordinary global overload are injected; raw malloc, aligned/nothrow forms, account-limit denial and syscalls are not separate injected faults. |
| cost | One seam call plus one malloc attempt if admitted. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0007

[Lines 46–46](../../../../../tests/unit/epoch_view_exception_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the replacement scalar unsized delete family. |
| inputs / outputs | A pointer from the matching scalar allocation form enters; no value is returned. |
| invariants | The body calls std::free on the supplied pointer and does not change fail_after. |
| ownership | The pointer is borrowed for this call and released here; it must belong to compatible malloc-backed replacement storage. |
| failure | No fault is injected by delete; the replacement covers ordinary scalar/array forms, not arbitrary external storage. |
| cost | One std::free call; no allocation request. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0008

[Lines 47–47](../../../../../tests/unit/epoch_view_exception_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the replacement array unsized delete family. |
| inputs / outputs | A pointer from the matching array allocation form enters; no value is returned. |
| invariants | The body calls std::free on the supplied pointer and does not change fail_after. |
| ownership | The pointer is borrowed for this call and released here; it must belong to compatible malloc-backed replacement storage. |
| failure | No fault is injected by delete; the replacement covers ordinary scalar/array forms, not arbitrary external storage. |
| cost | One std::free call; no allocation request. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0009

[Lines 48–48](../../../../../tests/unit/epoch_view_exception_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the replacement scalar sized delete family. |
| inputs / outputs | A pointer from the matching scalar allocation form enters; no value is returned. |
| invariants | The body calls std::free on the supplied pointer and does not change fail_after. |
| ownership | The pointer is borrowed for this call and released here; it must belong to compatible malloc-backed replacement storage. |
| failure | No fault is injected by delete; the replacement covers ordinary scalar/array forms, not arbitrary external storage. |
| cost | One std::free call; no allocation request. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0010

[Lines 49–49](../../../../../tests/unit/epoch_view_exception_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the replacement array sized delete family. |
| inputs / outputs | A pointer from the matching array allocation form enters; no value is returned. |
| invariants | The body calls std::free on the supplied pointer and does not change fail_after. |
| ownership | The pointer is borrowed for this call and released here; it must belong to compatible malloc-backed replacement storage. |
| failure | No fault is injected by delete; the replacement covers ordinary scalar/array forms, not arbitrary external storage. |
| cost | One std::free call; no allocation request. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0011

[Lines 50–63](../../../../../tests/unit/epoch_view_exception_test.cpp#L50); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L63:sha256:c0989a83e13cb215bfe049ca90acbbb94af06c122fa0531772ac2677a663d928
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare epoch_view_exception_test.cpp: bind local aliases/name imports; require 6 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 64–66](../../../../../tests/unit/epoch_view_exception_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed fixture predicate into a named runtime_error. |
| inputs / outputs | A bool and borrowed string_view enter; true returns, false constructs and throws runtime_error. |
| invariants | The helper does not catch product exceptions or retry the checked operation. |
| ownership | Inputs are borrowed only for the call; returned fixture values own their scalar/string/vector contents unless the function explicitly returns a const reference to function-static storage. |
| failure | Ordinary value construction can propagate allocation or validation errors; these fixture helpers add no catch or product-error translation. |
| cost | Constructs only the fixed small rows, strings, schema, or plan named by the fixture; this is not a performance, byte-limit, or CPU-time claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0014

[Lines 68–77](../../../../../tests/unit/epoch_view_exception_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one crown::api::Error with an exact code from an action. |
| inputs / outputs | A forwarded action and expected string_view code enter; matching Error returns normally. |
| invariants | A nonmatching Error is a failed check; no Error becomes runtime_error; only crown::api::Error is accepted. |
| ownership | Inputs are borrowed only for the call; returned fixture values own their scalar/string/vector contents unless the function explicitly returns a const reference to function-static storage. |
| failure | Ordinary value construction can propagate allocation or validation errors; these fixture helpers add no catch or product-error translation. |
| cost | Constructs only the fixed small rows, strings, schema, or plan named by the fixture; this is not a performance, byte-limit, or CPU-time claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0016

[Lines 79–79](../../../../../tests/unit/epoch_view_exception_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap one int64 fixture value in the public scalar Value variant. |
| inputs / outputs | An int64 enters and a Value containing the same integer exits. |
| invariants | No conversion, retention, or view into the argument is introduced. |
| ownership | Inputs are borrowed only for the call; returned fixture values own their scalar/string/vector contents unless the function explicitly returns a const reference to function-static storage. |
| failure | Ordinary value construction can propagate allocation or validation errors; these fixture helpers add no catch or product-error translation. |
| cost | Constructs only the fixed small rows, strings, schema, or plan named by the fixture; this is not a performance, byte-limit, or CPU-time claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0017

[Lines 80–80](../../../../../tests/unit/epoch_view_exception_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap one owning string fixture value in Value. |
| inputs / outputs | An owning std::string enters by value and a string alternative in Value exits. |
| invariants | The returned variant owns the string value; no input view escapes. |
| ownership | Inputs are borrowed only for the call; returned fixture values own their scalar/string/vector contents unless the function explicitly returns a const reference to function-static storage. |
| failure | Ordinary value construction can propagate allocation or validation errors; these fixture helpers add no catch or product-error translation. |
| cost | Constructs only the fixed small rows, strings, schema, or plan named by the fixture; this is not a performance, byte-limit, or CPU-time claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0018

[Lines 81–83](../../../../../tests/unit/epoch_view_exception_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row a_row(std::int64_t x, std::int64_t y, std::string witness) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one A-relation row with x, y and witness fields. |
| inputs / outputs | Two int64s and a string enter by value; an owning three-scalar Row exits. |
| invariants | The witness is moved into the returned scalar and field order matches the A descriptor. |
| ownership | Inputs are borrowed only for the call; returned fixture values own their scalar/string/vector contents unless the function explicitly returns a const reference to function-static storage. |
| failure | Ordinary value construction can propagate allocation or validation errors; these fixture helpers add no catch or product-error translation. |
| cost | Constructs only the fixed small rows, strings, schema, or plan named by the fixture; this is not a performance, byte-limit, or CPU-time claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0019

[Lines 84–86](../../../../../tests/unit/epoch_view_exception_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row b_row(std::int64_t x, std::int64_t y, std::string witness) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one B-relation row with x, y and witness fields. |
| inputs / outputs | Two int64s and a string enter by value; an owning three-scalar Row exits. |
| invariants | The witness is moved into the returned scalar and field order matches the B descriptor. |
| ownership | Inputs are borrowed only for the call; returned fixture values own their scalar/string/vector contents unless the function explicitly returns a const reference to function-static storage. |
| failure | Ordinary value construction can propagate allocation or validation errors; these fixture helpers add no catch or product-error translation. |
| cost | Constructs only the fixed small rows, strings, schema, or plan named by the fixture; this is not a performance, byte-limit, or CPU-time claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0020

[Lines 87–89](../../../../../tests/unit/epoch_view_exception_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row c_row(std::int64_t x, std::int64_t z, std::string witness) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one C-relation row with x, z and witness fields. |
| inputs / outputs | Two int64s and a string enter by value; an owning three-scalar Row exits. |
| invariants | The second integer is z; row fields match the C descriptor and the witness is moved. |
| ownership | Inputs are borrowed only for the call; returned fixture values own their scalar/string/vector contents unless the function explicitly returns a const reference to function-static storage. |
| failure | Ordinary value construction can propagate allocation or validation errors; these fixture helpers add no catch or product-error translation. |
| cost | Constructs only the fixed small rows, strings, schema, or plan named by the fixture; this is not a performance, byte-limit, or CPU-time claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0022

[Lines 91–91](../../../../../tests/unit/epoch_view_exception_test.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row& inserted_a() { static const Row value = a_row(3, 30, "a-3"); return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the static A insert row (3,30,"a-3"). |
| inputs / outputs | No input; const Row& to the fixture row exits. |
| invariants | The values match the physical A layout and the staged insert oracle. |
| ownership | Each returned reference borrows a function-static const Row or vector&lt;Row&gt; that owns the fixture values for process lifetime; callers must not treat the reference as a temporary or mutate it. |
| failure | The first static initialization can propagate an allocation failure; the helper catches nothing and does not fault-inject itself. |
| cost | Fixed process-lifetime fixture construction on first use, then a reference return; no runtime CPU or memory bound is measured. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0023

[Lines 92–92](../../../../../tests/unit/epoch_view_exception_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row& inserted_b() { static const Row value = b_row(3, 30, "b-3"); return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the static B insert row (3,30,"b-3"). |
| inputs / outputs | No input; const Row& to the fixture row exits. |
| invariants | The values match the physical B layout and pair with inserted_a in the insertion fixtures. |
| ownership | Each returned reference borrows a function-static const Row or vector&lt;Row&gt; that owns the fixture values for process lifetime; callers must not treat the reference as a temporary or mutate it. |
| failure | The first static initialization can propagate an allocation failure; the helper catches nothing and does not fault-inject itself. |
| cost | Fixed process-lifetime fixture construction on first use, then a reference return; no runtime CPU or memory bound is measured. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0024

[Lines 93–93](../../../../../tests/unit/epoch_view_exception_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row& inserted_c() { static const Row value = c_row(3, 9, "a-3"); return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the static C insert row (3,9,"a-3"). |
| inputs / outputs | No input; const Row& to the fixture row exits. |
| invariants | The witness equals A inserted_a witness; the row is on the C branch. |
| ownership | Each returned reference borrows a function-static const Row or vector&lt;Row&gt; that owns the fixture values for process lifetime; callers must not treat the reference as a temporary or mutate it. |
| failure | The first static initialization can propagate an allocation failure; the helper catches nothing and does not fault-inject itself. |
| cost | Fixed process-lifetime fixture construction on first use, then a reference return; no runtime CPU or memory bound is measured. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0025

[Lines 94–94](../../../../../tests/unit/epoch_view_exception_test.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row& erased_b() { static const Row value = b_row(1, 10, "b-10"); return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the static B erase row (1,10,"b-10"). |
| inputs / outputs | No input; const Row& to the fixture row exits. |
| invariants | It is present in the initialized B relation and its removal changes visible results. |
| ownership | Each returned reference borrows a function-static const Row or vector&lt;Row&gt; that owns the fixture values for process lifetime; callers must not treat the reference as a temporary or mutate it. |
| failure | The first static initialization can propagate an allocation failure; the helper catches nothing and does not fault-inject itself. |
| cost | Fixed process-lifetime fixture construction on first use, then a reference return; no runtime CPU or memory bound is measured. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0026

[Lines 95–95](../../../../../tests/unit/epoch_view_exception_test.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row& later_a() { static const Row value = a_row(4, 40, "a-4"); return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a later A row used to prove staging can resume after a view failure or release. |
| inputs / outputs | No input; const Row& to the fixture row exits. |
| invariants | It is distinct from the baseline and earlier insert row; callers borrow it only for the API call. |
| ownership | Each returned reference borrows a function-static const Row or vector&lt;Row&gt; that owns the fixture values for process lifetime; callers must not treat the reference as a temporary or mutate it. |
| failure | The first static initialization can propagate an allocation failure; the helper catches nothing and does not fault-inject itself. |
| cost | Fixed process-lifetime fixture construction on first use, then a reference return; no runtime CPU or memory bound is measured. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0027

[Lines 96–96](../../../../../tests/unit/epoch_view_exception_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row& later_b() { static const Row value = b_row(1, 11, "b-11"); return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a later B row used to prove staging can resume after an erase view failure. |
| inputs / outputs | No input; const Row& to the fixture row exits. |
| invariants | It is distinct from erased_b and the initial B rows; callers borrow it only for the API call. |
| ownership | Each returned reference borrows a function-static const Row or vector&lt;Row&gt; that owns the fixture values for process lifetime; callers must not treat the reference as a temporary or mutate it. |
| failure | The first static initialization can propagate an allocation failure; the helper catches nothing and does not fault-inject itself. |
| cost | Fixed process-lifetime fixture construction on first use, then a reference return; no runtime CPU or memory bound is measured. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0028

[Lines 97–103](../../../../../tests/unit/epoch_view_exception_test.cpp#L97); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L97-L103:sha256:75c210e48e03f5f6b648a0a86f94a88a11c6a39674e70de9b266fd58dc224713
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare epoch_view_exception_test.cpp: declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md) |

## B0029

[Lines 104–124](../../../../../tests/unit/epoch_view_exception_test.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the fixed A/B/C query and FreeConnex tree used by view and pending-update fixtures. |
| inputs / outputs | No input; local catalog/query/tree values enter lower_tree and an owning PhysicalPlan exits. |
| invariants | A and B produce visible x,y rows; C shares A hidden witness and is outside the root C* subtree. Node and variable IDs are the fixture constants used by the later stages. |
| ownership | Inputs are borrowed only for the call; returned fixture values own their scalar/string/vector contents unless the function explicitly returns a const reference to function-static storage. |
| failure | Ordinary value construction can propagate allocation or validation errors; these fixture helpers add no catch or product-error translation. |
| cost | Constructs only the fixed small rows, strings, schema, or plan named by the fixture; this is not a performance, byte-limit, or CPU-time claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0031

[Lines 126–130](../../../../../tests/unit/epoch_view_exception_test.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportOptions support_options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable support transition capture while leaving other SupportOptions defaults intact. |
| inputs / outputs | No input; a SupportOptions value with capture_transitions=true exits. |
| invariants | Default work and memory limits are retained; this helper does not set a fault or a byte cap. |
| ownership | Inputs are borrowed only for the call; returned fixture values own their scalar/string/vector contents unless the function explicitly returns a const reference to function-static storage. |
| failure | Ordinary value construction can propagate allocation or validation errors; these fixture helpers add no catch or product-error translation. |
| cost | Constructs only the fixed small rows, strings, schema, or plan named by the fixture; this is not a performance, byte-limit, or CPU-time claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0033

[Lines 132–136](../../../../../tests/unit/epoch_view_exception_test.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntimeOptions physical_options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build physical options by embedding the support options fixture. |
| inputs / outputs | No input; PhysicalRuntimeOptions exits with support.capture_transitions=true. |
| invariants | Other physical and support settings retain their declared defaults. |
| ownership | Inputs are borrowed only for the call; returned fixture values own their scalar/string/vector contents unless the function explicitly returns a const reference to function-static storage. |
| failure | Ordinary value construction can propagate allocation or validation errors; these fixture helpers add no catch or product-error translation. |
| cost | Constructs only the fixed small rows, strings, schema, or plan named by the fixture; this is not a performance, byte-limit, or CPU-time claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0035

[Lines 138–142](../../../../../tests/unit/epoch_view_exception_test.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<Row>& a_rows() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the four A source rows used to initialize SupportRuntime and PhysicalRuntime. |
| inputs / outputs | No input; const vector&lt;Row&gt;& with x,y,witness values exits. |
| invariants | Rows are ordered as the deterministic fixture sequence; every value conforms to A. |
| ownership | The function-static const vector owns every Row and scalar; returned const references remain valid for process lifetime. |
| failure | First static construction may propagate allocation failure; no fault scope is installed inside these accessors. |
| cost | One fixed small vector is constructed on first use and reused; this is fixture cardinality, not a CPU or byte guarantee. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md) |

## B0036

[Lines 143–147](../../../../../tests/unit/epoch_view_exception_test.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<Row>& b_rows() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the four B source rows used to initialize SupportRuntime and PhysicalRuntime. |
| inputs / outputs | No input; const vector&lt;Row&gt;& with x,y,witness values exits. |
| invariants | Rows are ordered as the deterministic fixture sequence; every value conforms to B. |
| ownership | The function-static const vector owns every Row and scalar; returned const references remain valid for process lifetime. |
| failure | First static construction may propagate allocation failure; no fault scope is installed inside these accessors. |
| cost | One fixed small vector is constructed on first use and reused; this is fixture cardinality, not a CPU or byte guarantee. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md) |

## B0037

[Lines 148–152](../../../../../tests/unit/epoch_view_exception_test.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<Row>& c_rows() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the four C source rows used to initialize SupportRuntime and PhysicalRuntime. |
| inputs / outputs | No input; const vector&lt;Row&gt;& with x,z,witness values exits. |
| invariants | Witness values match the A records joined by C in the fixed plan. |
| ownership | The function-static const vector owns every Row and scalar; returned const references remain valid for process lifetime. |
| failure | First static construction may propagate allocation failure; no fault scope is installed inside these accessors. |
| cost | One fixed small vector is constructed on first use and reused; this is fixture cardinality, not a CPU or byte guarantee. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md) |

## B0038

[Lines 153–156](../../../../../tests/unit/epoch_view_exception_test.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<Row>& base_results() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the expected committed visible rows before the epoch insert or erase. |
| inputs / outputs | No input; const vector&lt;Row&gt;& of four core x,y rows exits. |
| invariants | These are exact expected rows for both support and physical fixture baselines. |
| ownership | The function-static const vector owns every Row and scalar; returned const references remain valid for process lifetime. |
| failure | First static construction may propagate allocation failure; no fault scope is installed inside these accessors. |
| cost | One fixed small vector is constructed on first use and reused; this is fixture cardinality, not a CPU or byte guarantee. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md) |

## B0039

[Lines 157–161](../../../../../tests/unit/epoch_view_exception_test.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<Row>& inserted_results() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the expected visible rows after the three-table insert epoch. |
| inputs / outputs | No input; const vector&lt;Row&gt;& of five core x,y rows exits. |
| invariants | The new (3,30) row is included once; output is compared after row sorting. |
| ownership | The function-static const vector owns every Row and scalar; returned const references remain valid for process lifetime. |
| failure | First static construction may propagate allocation failure; no fault scope is installed inside these accessors. |
| cost | One fixed small vector is constructed on first use and reused; this is fixture cardinality, not a CPU or byte guarantee. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md) |

## B0040

[Lines 162–165](../../../../../tests/unit/epoch_view_exception_test.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<Row>& erased_results() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the expected visible rows after erasing B(1,10). |
| inputs / outputs | No input; const vector&lt;Row&gt;& of three core x,y rows exits. |
| invariants | Only the (1,10) result disappears from the baseline. |
| ownership | The function-static const vector owns every Row and scalar; returned const references remain valid for process lifetime. |
| failure | First static construction may propagate allocation failure; no fault scope is installed inside these accessors. |
| cost | One fixed small vector is constructed on first use and reused; this is fixture cardinality, not a CPU or byte guarantee. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md) |

## B0041

[Lines 166–169](../../../../../tests/unit/epoch_view_exception_test.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<Row>& x_one_results() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the expected rows for the visible binding x=1. |
| inputs / outputs | No input; const vector&lt;Row&gt;& of three core x,y rows exits. |
| invariants | The values are exactly the visible baseline subset selected by x=1. |
| ownership | The function-static const vector owns every Row and scalar; returned const references remain valid for process lifetime. |
| failure | First static construction may propagate allocation failure; no fault scope is installed inside these accessors. |
| cost | One fixed small vector is constructed on first use and reused; this is fixture cardinality, not a CPU or byte guarantee. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md) |

## B0043

[Lines 171–183](../../../../../tests/unit/epoch_view_exception_test.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime make_support(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct and validate the initialized logical SupportRuntime fixture. |
| inputs / outputs | A PhysicalPlan is borrowed; the helper inserts all four rows from A, B and C at contiguous sequences, checks sequence/answer/invariants, and returns a SupportRuntime by value. |
| invariants | The three native node IDs match the plan; returned owner is committed and ready at sequence 12. |
| ownership | The local plan is borrowed during runtime construction; returned runtime owns its implementation/state and original memory account. |
| failure | Runtime, update, or fixture checks can throw; there is no local catch or injected failure during setup. |
| cost | Initializes twelve small native rows and validates the resulting state; no time or bytes bound is asserted. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/runtime_support.md § Input contract](../../../../runtime_support.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md) |

## B0045

[Lines 185–197](../../../../../tests/unit/epoch_view_exception_test.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime make_physical(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct and validate the initialized PhysicalRuntime fixture. |
| inputs / outputs | A PhysicalPlan is borrowed; the helper inserts all four source rows for each of A, B and C at contiguous sequences and returns a PhysicalRuntime by value. |
| invariants | Table IDs correspond to A/B/C; returned runtime has sequence 12, an answer, and valid physical/logical state. |
| ownership | The plan is borrowed during construction; returned facade owns source, derivation and delegated logical runtime state under its account. |
| failure | Construction, physical apply, and checks can propagate errors; this setup is unarmed by the helper. |
| cost | Builds twelve source rows and their alias/support effects; no CPU, allocator-byte, or system-resource bound is inferred. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md) |

## B0047

[Lines 199–203](../../../../../tests/unit/epoch_view_exception_test.cpp#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json row_image(const Row& row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one Row to a JSON array of serialized scalar values. |
| inputs / outputs | A Row is borrowed; one JSON array with one scalar image per field exits. |
| invariants | Field order and scalar value are preserved; the source Row is not modified. |
| ownership | Inputs are borrowed while encoded; the returned JSON tree owns its scalar, string, array and object values. No reference into a runtime or snapshot escapes. |
| failure | Serialization or JSON allocation errors propagate; these oracles catch no product exception and make no fault injection unless their caller scopes one around the call. |
| cost | Visits the fixed fixture rows/records and constructs a diagnostic JSON value. Encoding cost is separate from runtime work metrics and is not a CPU or byte cap. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md) |

## B0049

[Lines 205–208](../../../../../tests/unit/epoch_view_exception_test.cpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json support_snapshot_image(const SupportSnapshot& snapshot, const auto& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize sequence, answer flag and support state from one SupportSnapshot. |
| inputs / outputs | Snapshot and plan are borrowed; JSON object containing sequence, answer and write_support_snapshot output exits. |
| invariants | The helper adds no owner normalization; output is a detached image for equality oracles. |
| ownership | Inputs are borrowed while encoded; the returned JSON tree owns its scalar, string, array and object values. No reference into a runtime or snapshot escapes. |
| failure | Serialization or JSON allocation errors propagate; these oracles catch no product exception and make no fault injection unless their caller scopes one around the call. |
| cost | Visits the fixed fixture rows/records and constructs a diagnostic JSON value. Encoding cost is separate from runtime work metrics and is not a CPU or byte cap. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md) |

## B0051

[Lines 210–212](../../../../../tests/unit/epoch_view_exception_test.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json state_image(const SupportRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture one committed SupportRuntime state image. |
| inputs / outputs | Runtime is borrowed; snapshot() and plan() feed support_snapshot_image, which returns owned JSON. |
| invariants | The runtime snapshot requires readable committed state; the image includes sequence and support state. |
| ownership | Inputs are borrowed while encoded; the returned JSON tree owns its scalar, string, array and object values. No reference into a runtime or snapshot escapes. |
| failure | Serialization or JSON allocation errors propagate; these oracles catch no product exception and make no fault injection unless their caller scopes one around the call. |
| cost | Visits the fixed fixture rows/records and constructs a diagnostic JSON value. Encoding cost is separate from runtime work metrics and is not a CPU or byte cap. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md) |

## B0053

[Lines 214–231](../../../../../tests/unit/epoch_view_exception_test.cpp#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json physical_snapshot_image(const PhysicalSnapshot& snapshot, const auto& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize physical source tables, derivation counts and support from one PhysicalSnapshot. |
| inputs / outputs | Snapshot and plan are borrowed; JSON object with sequence, physical rows, derivations and support exits. |
| invariants | Accounted tuple values are exported while the snapshot lives; each output row is copied into JSON. |
| ownership | Inputs are borrowed while encoded; the returned JSON tree owns its scalar, string, array and object values. No reference into a runtime or snapshot escapes. |
| failure | Serialization or JSON allocation errors propagate; these oracles catch no product exception and make no fault injection unless their caller scopes one around the call. |
| cost | Visits the fixed fixture rows/records and constructs a diagnostic JSON value. Encoding cost is separate from runtime work metrics and is not a CPU or byte cap. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md) |

## B0055

[Lines 233–249](../../../../../tests/unit/epoch_view_exception_test.cpp#L233); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json state_image(const PhysicalRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture PhysicalRuntime state and verify every snapshot source row still resolves through its public handle. |
| inputs / outputs | A PhysicalRuntime is borrowed; snapshot and plan are serialized, then source handles are looked up and appended to an owning JSON image. |
| invariants | Every snapshot source row must have a find_source handle and get_source must resolve the same values; output records owner/relation/tuple IDs. |
| ownership | The snapshot and returned accounted tuples are local owners; exported Rows and JSON own copied values, while the runtime is borrowed. |
| failure | A missing or mismatched handle throws runtime_error; snapshot and JSON allocation failures propagate. |
| cost | Visits all fixed source rows and emits one handle image per row; this is a test oracle, not a physical work/CPU measurement. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md) |

## B0057

[Lines 251–253](../../../../../tests/unit/epoch_view_exception_test.cpp#L251); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json pending_image(const SupportRuntime::PendingEpoch& pending, const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the tentative logical snapshot exposed by one pending SupportRuntime epoch. |
| inputs / outputs | Pending token and plan are borrowed; its snapshot value is converted to an owning support JSON image. |
| invariants | This is a diagnostic copy of the current staged prefix; it does not publish or commit the pending state. |
| ownership | Inputs are borrowed while encoded; the returned JSON tree owns its scalar, string, array and object values. No reference into a runtime or snapshot escapes. |
| failure | Serialization or JSON allocation errors propagate; these oracles catch no product exception and make no fault injection unless their caller scopes one around the call. |
| cost | Visits the fixed fixture rows/records and constructs a diagnostic JSON value. Encoding cost is separate from runtime work metrics and is not a CPU or byte cap. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md) |

## B0059

[Lines 255–264](../../../../../tests/unit/epoch_view_exception_test.cpp#L255); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json pending_image(const PhysicalRuntime::PendingUpdate& pending, const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the PhysicalRuntime pending snapshot and its held source update. |
| inputs / outputs | Pending token and plan are borrowed; physical snapshot JSON optionally receives the pending source handle and exported source values. |
| invariants | The preview source is read only while the pending token lives; the returned JSON owns row/scalar images. |
| ownership | Inputs are borrowed while encoded; the returned JSON tree owns its scalar, string, array and object values. No reference into a runtime or snapshot escapes. |
| failure | Serialization or JSON allocation errors propagate; these oracles catch no product exception and make no fault injection unless their caller scopes one around the call. |
| cost | Visits the fixed fixture rows/records and constructs a diagnostic JSON value. Encoding cost is separate from runtime work metrics and is not a CPU or byte cap. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md) |

## B0061

[Lines 266–274](../../../../../tests/unit/epoch_view_exception_test.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sort_rows(std::vector<Row>& rows) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sort an owning row vector by the fixture x field and then y when present. |
| inputs / outputs | A mutable vector&lt;Row&gt; enters and is reordered in place; no separate vector exits. |
| invariants | Rows compare the first int64 field and then second int64 when both rows have at least two fields; fixture rows are compatible. |
| ownership | The vector and all Row values are caller-owned and mutated in place. |
| failure | Invalid variant or malformed fixture row use can propagate standard exceptions; no catch or injected fault is present. |
| cost | std::sort over the supplied fixture result count; comparator work is not converted to a CPU-time claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md) |

## B0063

[Lines 276–287](../../../../../tests/unit/epoch_view_exception_test.cpp#L276); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Row> drain(Cursor& cursor) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a support ResultCursor into an owning sorted vector of public Rows. |
| inputs / outputs | A cursor is borrowed; repeated next() results are exported to Row and appended until null; a sorted vector exits. |
| invariants | The cursor must end exhausted and inactive; each exported Row is an owning copy and remains independent of later cursor release. |
| ownership | The cursor token remains caller-owned; each returned storage::Tuple owns its payload until exported, and the returned vector owns Row values. |
| failure | Cursor next, row export, vector growth or assertion can throw; a next failure closes the cursor according to the API and propagates. |
| cost | Visits exactly the rows returned by the selected cursor plus one terminal next; only fixed fixture result counts are used, not a delay bound. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md § Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md) |

## B0065

[Lines 289–292](../../../../../tests/unit/epoch_view_exception_test.cpp#L289); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Row> drain(SupportRuntime::EpochView& view, ResultCursorOptions options = {}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open and drain one projected result cursor from an EpochView. |
| inputs / outputs | A mutable view is borrowed with optional cursor settings; results(options) is drained and an owning sorted Row vector exits. |
| invariants | The created cursor is local and releases its group reference on exhaustion; the view itself remains open until its caller closes it. |
| ownership | The view belongs to its caller; returned Rows own copied values independently of the view/cursor. |
| failure | Cursor construction/next/export errors propagate; this wrapper does not retry or translate them. |
| cost | One cursor startup, selected row traversal and terminal next over a small fixture; no time or abstract-work cap is asserted here. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md), [docs/result_cursors.md § Traversal and output rows](../../../../result_cursors.md) |

## B0067

[Lines 294–348](../../../../../tests/unit/epoch_view_exception_test.cpp#L294); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_support_view_factory_sweep(const PhysicalPlan& plan, SnapshotSide side, bool erase) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep SupportRuntime pending before/after view construction for insert and erase prefixes. |
| inputs / outputs | Plan, snapshot side and erase flag enter; each fresh runtime captures committed and tentative images, then pending.view(side) runs under one selected fault point. |
| invariants | Each bad_alloc must leave the pending epoch active and tentative image unchanged; a retry view drains to the exact before/after result oracle, closes, permits another stage, and rollback restores the committed image. First successful factory also leaves the pending prefix unchanged. |
| ownership | Each loop iteration owns its fresh runtime and pending token; snapshots/JSON are detached oracle values. A failed factory leaves the same active token/view available for the explicit same-owner retry within that iteration. |
| failure | The scoped fault catches only std::bad_alloc from replaced ordinary global new/new\[\]. It checks pending state after failure and retries the factory on that same owner. The seam does not force MemoryAccount limit errors, raw malloc/realloc failures, aligned/nothrow allocation failures or syscalls. |
| cost | At most 256 selected C++ new fault positions per call, stopping at the first successful factory; every point rebuilds the small fixture. The index is not a byte/CPU/work limit and this is not a benchmark. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/epoch_views.md § Work limits and scope](../../../../epoch_views.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0069

[Lines 350–387](../../../../../tests/unit/epoch_view_exception_test.cpp#L350); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_physical_view_factory_sweep(const PhysicalPlan& plan, SnapshotSide side) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep before/after view creation delegated by a PhysicalRuntime pending source insertion. |
| inputs / outputs | Plan and side enter; each fresh physical owner prepares one source-row insert, captures its pending image, and constructs/closes pending.view(side) under a selected fault point. |
| invariants | A failed factory preserves the source/logical pending image and active token; same-token retry returns the clean visible prefix, then rollback restores committed source handles/state. Successful construction likewise does not publish the physical update. |
| ownership | Each iteration owns the physical pending source and delegated logical token; snapshots/JSON own their copies. The view shares the pending logical owner. |
| failure | Only bad_alloc through ordinary global new/new\[\] is injected. Physical/account limit failures, raw malloc, system calls and other overloads are not swept; failure leaves token for same-token retry. |
| cost | At most 256 fault positions, with each iteration rebuilding the small physical fixture; no byte, CPU or physical work bound is measured. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/epoch_views.md § Work limits and scope](../../../../epoch_views.md) |

## B0071

[Lines 389–433](../../../../../tests/unit/epoch_view_exception_test.cpp#L389); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_completion_factory_sweep(const PhysicalPlan& plan, bool physical) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep completion-cursor factory allocation failures for committed SupportRuntime and PhysicalRuntime views. |
| inputs / outputs | Plan and runtime selector enter; each fresh owner creates a committed view, then completions(x=1, root C*) is opened under one fault point. |
| invariants | Factory bad_alloc leaves the shared view valid and read lease held; a new cursor on that same view drains exactly x_one_results, then close releases the unchanged runtime. The successful cursor factory also leaves view/runtime state unchanged. |
| ownership | Each loop owns one fresh runtime, view and cursor; the view group retains logical runtime state until close, while output Rows are owning values. |
| failure | The scoped injection is ordinary global new/new\[\] only; no account-cap denial, raw malloc/realloc, aligned/nothrow failure or syscall is forced. Retry is a fresh cursor factory on the same view, not a fresh runtime inside the trial. |
| cost | At most 256 selected factory fault positions for each runtime flavor; each point rebuilds the tiny initialized owner. No CPU/byte performance claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md), [docs/epoch_views.md § Work limits and scope](../../../../epoch_views.md), [docs/result_cursors.md § Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Read lease and runtime lifetime](../../../../result_cursors.md) |

## B0073

[Lines 435–454](../../../../../tests/unit/epoch_view_exception_test.cpp#L435); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_completion_validation(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check invalid binding and fragment errors plus hidden-variable filtering on a committed support view. |
| inputs / outputs | Plan enters; a fresh SupportRuntime and current view exercise wrong type, duplicate-conflict, out-of-range variable and invalid roots, then drain hidden-bound and full-result cursors. |
| invariants | Each invalid input expects its specific Error code; hidden witness binding restricts output but is not projected; current and full C* results equal their fixture vectors and view close restores readiness. |
| ownership | Runtime and view are local owners; fixed assignments are temporary owning inputs; drained Rows own their values. |
| failure | Unexpected error code, missing error, result mismatch, or construction/allocation error propagates; no allocation failure sweep is active. |
| cost | A fixed set of eight validation/read cases over the tiny plan; no cursor-work, CPU, or byte bound is inferred. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md), [docs/epoch_views.md § Work limits and scope](../../../../epoch_views.md), [docs/result_cursors.md § Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md) |

## B0075

[Lines 456–476](../../../../../tests/unit/epoch_view_exception_test.cpp#L456); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_completions_filter_paths(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise filtered completion scans and exact primary lookups using selected cursor metrics. |
| inputs / outputs | Plan enters; committed view opens x=1 and x=1,y=11 completion cursors and drains their rows. |
| invariants | Partial binding must record binding checks/rejections and a lookup path; full binding must record direct lookups; the view remains valid and closing it restores ready state. |
| ownership | View/cursors are local; drained Rows own values and cursor metrics are borrowed only while cursor handles remain alive. |
| failure | Metric or row assertions throw runtime_error; no fault injector is armed and no resource-limit failure is forced. |
| cost | Two cursor traversals over the fixed tiny plan. Metrics identify selected abstract operations; they do not establish CPU time, bytes, or delay. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md), [docs/epoch_views.md § Work limits and scope](../../../../epoch_views.md), [docs/result_cursors.md § Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md) |

## B0077

[Lines 478–507](../../../../../tests/unit/epoch_view_exception_test.cpp#L478); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_rollback_aborts_linked_cursors_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require pending rollback to abort linked views/cursors without intercepted global new calls. |
| inputs / outputs | Plan enters; one pending insert stages three rows, copied after-view handles open two cursors, and the first cursor yields an owning tuple before rollback. |
| invariants | Under fail_after=0 rollback closes the token, invalidates both views, marks cursors failed/inactive, releases the writer lease, and leaves the saved Tuple readable; a new token at the same sequence can stage and roll back. |
| ownership | Pending token owns transaction; view copies and cursors share its group; saved storage::Tuple owns its returned row. The later token is a fresh token on the same runtime, not a retry of the closed pending token. |
| failure | The zero fail point rejects only ordinary global new/new\[\] calls during rollback. Direct malloc/syscalls are not intercepted, so “noalloc” means no intercepted C++ new call in this scope. |
| cost | One staged three-row prefix, two cursors and one new-token retry; no latency or allocator-byte accounting. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md) |

## B0079

[Lines 509–554](../../../../../tests/unit/epoch_view_exception_test.cpp#L509); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_commit_preserves_views_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check committed before/after views and active cursors survive a no-intercepted-new commit. |
| inputs / outputs | Plan enters; pending insert stages three rows, both side views and cursors yield saved tuples, and commit returns SupportEpoch while fail_after=0. |
| invariants | Commit publishes exactly one sequence, makes after view non-tentative, preserves fixed before/after cursor results and saved tuple values, and keeps runtime busy until the last copied view closes; a later update then succeeds. |
| ownership | The returned SupportEpoch owns output journal; copied views/cursors retain their shared group/read lease; saved result Tuples own values. The later update is a subsequent input after lease release, not retry of the committed batch. |
| failure | The fail-zero scope rejects intercepted ordinary new/new\[\] during commit; source asserts the operation completes. Raw malloc/syscalls and other new overloads are outside this check. |
| cost | Three staged rows, two output streams and one later update on the fixed fixture; no CPU or byte limit is measured. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/result_cursors.md § Read lease and runtime lifetime](../../../../result_cursors.md) |

## B0081

[Lines 556–588](../../../../../tests/unit/epoch_view_exception_test.cpp#L556); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_pending_move_cleanup_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check move assignment of a pending token aborts its old destination group and transfers source ownership without intercepted new. |
| inputs / outputs | Plan enters; two SupportRuntimes each stage an insert; destination has an open after-view/cursor, then move assignment replaces it while fail_after=0. |
| invariants | Destination old view/cursor become invalid/failed, its old runtime becomes ready, source runtime stays busy under the transferred token, and the transferred prefix can be read then rolled back. |
| ownership | Two runtimes own separate state/accounts; token move transfers its source Data; old view/cursor references retain only their terminal state until closed. |
| failure | Move assignment/rollback must complete without ordinary intercepted new/new\[\]; direct malloc/syscalls are not covered by the fail-zero check. |
| cost | Two fixture runtimes, one cursor invalidation, a retry view and rollback; no CPU or allocator-byte claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md) |

## B0083

[Lines 590–617](../../../../../tests/unit/epoch_view_exception_test.cpp#L590); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_pending_destruction_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check destruction of an active pending token aborts its group and linked cursors under fail_after=0. |
| inputs / outputs | Plan enters; one pending insert stages, opens a view with two cursors, and saves one result tuple; optional token reset runs under fail_after=0. |
| invariants | Destruction invalidates view and both cursors, closes the runtime writer lease, and leaves the saved tuple readable; caller then closes the invalid view handle. |
| ownership | Optional owns the pending token; view/cursors share its group; the saved Tuple owns its payload beyond token destruction. |
| failure | The no-allocation assertion covers only replaced ordinary global new/new\[\] calls in the destructor scope; no direct malloc/syscall interception. |
| cost | One small staged prefix, two cursor registrations and one token teardown; no general allocator or latency bound. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md) |

## B0085

[Lines 619–710](../../../../../tests/unit/epoch_view_exception_test.cpp#L619); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_physical_pending_lifecycle_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise PhysicalRuntime pending rollback, commit, token move assignment and destruction with delegated views/cursors. |
| inputs / outputs | Plan enters; physical owner prepares one source insert, opens copied delegated views and cursors, rolls back; a second pending input commits with a live cursor; separate owners then test move replacement and destructor abort. |
| invariants | Rollback aborts cursor authority and preserves a saved Tuple; a later same-sequence input can be prepared. Commit under fail_after=0 preserves delegated view/cursor until close. Move replacement aborts old destination token; destruction aborts source-linked views and restores ready state. |
| ownership | Physical pending token owns source journal, undo and delegated logical PendingEpoch; views/cursors retain the logical group, and returned Tuples own values. Follow-up prepares are new pending tokens, not retries of closed commits. |
| failure | Fail-zero scopes require rollback/commit/move/destructor to complete without calls through replaced ordinary new/new\[\]. Account limit denial, direct malloc and syscalls are not injected. |
| cost | Several fixed-size physical owners, source updates and cursor lifecycles; cost is fixture orchestration, not bytes, CPU or measured physical work. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0087

[Lines 712–771](../../../../../tests/unit/epoch_view_exception_test.cpp#L712); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_next_fault_sweep(const PhysicalPlan& plan, bool erase, SnapshotSide side, bool later) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep next() allocation failures for pending before/after result cursors across insert/erase and early/later prefixes. |
| inputs / outputs | Plan, operation, view side and later flag enter; each fresh SupportRuntime stages the selected prefix, constructs a view/cursor, optionally emits two rows, then calls next() under one selected fault point. |
| invariants | On failure the cursor closes but view/pending image and sequence remain unchanged; earlier owning rows survive later failures; same-view retry drains the exact before/after oracle, then close/rollback releases the lease. The first successful next returns a row while view remains held. |
| ownership | Each attempt owns a fresh fixture runtime and pending token/view; a saved storage::Tuple owns its row. After next() failure the failed cursor closes, while the same live view and pending token remain available for a new cursor factory. |
| failure | Only the selected ordinary global new/new\[\] position during cursor.next() is forced to bad_alloc. The cursor must become failed/inactive; the view and pending token remain live; later next() on the failed cursor is invalid_cursor. Raw malloc/realloc, aligned/nothrow overloads, account-limit denial and syscalls are outside. |
| cost | At most 192 selected next-call fault positions per case, stopping at first successful next; each point rebuilds a tiny runtime and cursor. No work/CPU/byte bound is asserted. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md), [docs/epoch_views.md § Work limits and scope](../../../../epoch_views.md), [docs/result_cursors.md § Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md) |

## B0089

[Lines 773–817](../../../../../tests/unit/epoch_view_exception_test.cpp#L773); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_current_view_next_lease(const PhysicalPlan& plan, bool later) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep failed next() calls on committed current-view completions while a peer cursor shares the read lease. |
| inputs / outputs | Plan and later-prefix flag enter; each fresh committed runtime captures state, creates current view plus x=1 completions and peer result cursors, then faults one next() call. |
| invariants | A failed primary cursor becomes inactive/failed while peer/view remain valid; updates still return runtime_busy; a new completions cursor on the same view drains x_one_results and closing peer/view restores unchanged state. |
| ownership | Each attempt owns a fresh SupportRuntime, committed view and two cursors. Returned Tuple rows own values; failed cursor state is independent from the peer cursor and shared view group. |
| failure | Only ordinary global new/new\[\] during one completions cursor next() is faulted. A failure closes that cursor but leaves peer and view active; the same view can create a replacement cursor. The suite does not force account cap, direct malloc/realloc, aligned/nothrow allocation, or syscall failures. |
| cost | At most 192 fault positions per prefix mode, stopping at first successful next; each iteration rebuilds fixed support state. Metrics assert emitted-row count only, not CPU time/bytes/delay. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md), [docs/epoch_views.md § Work limits and scope](../../../../epoch_views.md), [docs/result_cursors.md § Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Read lease and runtime lifetime](../../../../result_cursors.md) |

## B0091

[Lines 819–876](../../../../../tests/unit/epoch_view_exception_test.cpp#L819); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_facade_destruction_stability(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check committed and aborted SupportRuntime/PhysicalRuntime delegated views across facade/token scope exit. |
| inputs / outputs | Plan enters; committed support and physical pending views emit one Tuple before commit and drain remaining rows after their facade scopes end; an aborted support view is also retained across rollback and facade destruction. |
| invariants | Committed views/cursors remain valid after facade destruction and return the complete expected owning row set; rollback invalidates view/cursor but saved Tuple remains readable. No syscall or allocation fault is armed. |
| ownership | Optional view/cursor and saved Tuple outlive local runtime/token facades; committed view group retains logical runtime state; physical view retains delegated logical support, not physical source facade ownership. |
| failure | Mismatch throws runtime_error; owner/cursor construction and iteration failures propagate; no exception is translated. |
| cost | Three fixed lifecycle cases and a few rows; no memory-retention byte total, CPU limit or durability claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/result_cursors.md § Read lease and runtime lifetime](../../../../result_cursors.md) |

## B0093

[Lines 878–882](../../../../../tests/unit/epoch_view_exception_test.cpp#L878); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Row> reference_rows(const storage::ReferenceTable& table) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the current rows of a ReferenceTable snapshot into ordinary owning Row values. |
| inputs / outputs | A ReferenceTable is borrowed; snapshot tuples are traversed and export_row copies each into an owning vector&lt;Row&gt;. |
| invariants | Output values preserve table snapshot order; the returned vector has no table borrow. |
| ownership | Table is borrowed for traversal; returned Rows own scalar/string values. |
| failure | Snapshot/export/vector allocation or table errors propagate; there is no fault scope in this helper. |
| cost | Visits each row in the small reference-table fixture and exports it; no byte/CPU bound. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md § Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md § Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md § Scope boundary](../../../../storage_journal.md) |

## B0095

[Lines 884–974](../../../../../tests/unit/epoch_view_exception_test.cpp#L884); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_reference_journal_owned_cursor_lifecycle() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check owner-only ReferenceTable journal cursors across tentative insert, commit, other journals, mutation and rollback. |
| inputs / outputs | No external input; builds a two-row table/index, opens an exclusive journal, inserts rows, and compares live/bucket handles and later committed row snapshots. |
| invariants | Ordinary cursors/reads are busy during journal; owner live/bucket cursors observe tentative values and survive commit; an unrelated empty journal blocks a committed owner cursor until rollback; same-journal real mutation and rollback invalidate prior cursors. The final cursor reset is followed by a same-journal insert, but source permits that insert while a cursor is still open, so the assertion does not establish that destruction released a registration. |
| ownership | Table owns ReferenceTable State and rows; Journal owns its transaction/state and also retains its shared reader token; Cursor has unique cursor metadata, a weak table-state reference, and a shared reader token. Cursor returns owner-scoped TupleHandle IDs while next_entry references are borrowed. In this fixture, row snapshots and expected vectors are copied values. |
| failure | Expected storage_busy/invalid_cursor errors are checked; the only fail-zero action is cursor destruction and checks only ordinary global new/new\[\]. The later insert is not fault-scoped and succeeds even if an owner cursor remains open, so the source diagnostic overstates a causal registration-release oracle; raw malloc/syscalls and a memory-account cap are outside. |
| cost | A fixed two-index/four-row journal sequence plus one no-allocation cursor teardown; no timing or byte budget. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md § Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md § Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md § Scope boundary](../../../../storage_journal.md), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md) |

## B0097

[Lines 976–1033](../../../../../tests/unit/epoch_view_exception_test.cpp#L976); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_reference_journal_cursor_fault_sweep() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ReferenceTable Journal::live cursor-factory allocation failures and verify rollback/handles. |
| inputs / outputs | No external input; up to 48 fresh two-row tables open a journal, insert a tentative third row, and call journal.live() under one selected fail point. |
| invariants | Factory bad_alloc leaves the journal active and retryable on the same table/journal; retry cursor reads a row then rollback restores exact rows/handles. First successful factory has its first next() checked while fail_after=0, then cursor destruction and rollback restore baseline; this is a factory sweep plus a no-intercepted-new first-read check, not an injected next sweep. |
| ownership | Each iteration owns table, journal and cursor; TupleHandles are value IDs; table rows are table-owned, and reference_rows produces owning Row copies. |
| failure | The injector reaches ordinary global new/new\[\] only; raw malloc, aligned/nothrow forms, account-limit failure and syscalls are not tested. A failed factory does not close the enclosing journal. |
| cost | At most 48 selected cursor-factory fault points before first success over a two-row table. The first-read check is fail-zero; no CPU or allocation-byte bound is inferred. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md § Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md § Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md § Scope boundary](../../../../storage_journal.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0098

[Lines 1034–1036](../../../../../tests/unit/epoch_view_exception_test.cpp#L1034); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1034-L1036:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in epoch_view_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md) |

## B0099

[Lines 1037–1070](../../../../../tests/unit/epoch_view_exception_test.cpp#L1037); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Orchestrate every epoch-view factory, completion, rollback/commit lifecycle, next sweep and ReferenceTable journal cursor case. |
| inputs / outputs | No external input; constructs the fixed PhysicalPlan, invokes the listed support/physical/ReferenceTable helpers, and returns zero only if each check completes. |
| invariants | The main catch resets fail_after, prints std::exception diagnostics and returns one; its final success print is source text, not evidence this executable ran during review. |
| ownership | All fixture owners are local; helpers create owning snapshots/JSON/Rows and owner-scoped runtime tokens/views/cursors as described in their cards. |
| failure | Exceptions reach the main catch; no failure is translated into a claim about an executed test. No syscall fault injector is present. |
| cost | Runs bounded helper loops at their stated source caps over fixed small fixtures; no benchmark, CPU-time, byte-limit, or theorem claim. |
| Design | [tests/unit/epoch_view_exception_test.cpp](../../../../../tests/unit/epoch_view_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/epoch_views.md § What an epoch view represents](../../../../epoch_views.md), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/epoch_views.md § Projected completions](../../../../epoch_views.md), [docs/epoch_views.md § Work limits and scope](../../../../epoch_views.md), [docs/result_cursors.md § Traversal and output rows](../../../../result_cursors.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [docs/storage_journal.md § Purpose and API](../../../../storage_journal.md), [docs/storage_journal.md § Exclusive mutation and tentative reads](../../../../storage_journal.md), [docs/storage_journal.md § Scope boundary](../../../../storage_journal.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md) |
