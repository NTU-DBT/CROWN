# `tests/unit/prepared_epoch_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/prepared_epoch_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `ce7c7f12496978a714519137c419c3a155c1cafd46f310489d6b142cdd67d423`. 704 lines partitioned into 97 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–27](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // This executable owns the allocation fault injector so every prepared-epoch · [reviewed contract](#b0001) |
| [B0002 · 28–35](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L28) | Callable definition: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes) | calls std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 36–42](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L36) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0003) |
| [B0004 · 43–44](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L43) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 45–45](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L45) | Callable definition: void* operator new(std::size_t bytes) | calls malloc_new; returns malloc_new(bytes); growth new · [reviewed contract](#b0005) |
| [B0006 · 46–46](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L46) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 47–47](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L47) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0007) |
| [B0008 · 48–48](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L48) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0008) |
| [B0009 · 49–49](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L49) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0009) |
| [B0010 · 50–50](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L50) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0010) |
| [B0011 · 51–59](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L51) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;SupportEpoch&gt;); · [reviewed contract](#b0011) |
| [B0012 · 60–62](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L60) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0012) |
| [B0013 · 63–63](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L63) | Explanatory comments or spacing. |  |
| [B0014 · 64–64](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L64) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0014) |
| [B0015 · 65–65](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L65) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0015) |
| [B0016 · 66–66](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L66) | Explanatory comments or spacing. |  |
| [B0017 · 67–70](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L67) | Callable definition: const Row& a_y1() | calls n, s; returns value · [reviewed contract](#b0017) |
| [B0018 · 71–74](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L71) | Callable definition: const Row& b_y1() | calls n, s; returns value · [reviewed contract](#b0018) |
| [B0019 · 75–78](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L75) | Callable definition: const Row& a_y2_first() | calls n, s; returns value · [reviewed contract](#b0019) |
| [B0020 · 79–82](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L79) | Callable definition: const Row& a_y2_second() | calls n, s; returns value · [reviewed contract](#b0020) |
| [B0021 · 83–86](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L83) | Callable definition: const Row& b_y2() | calls n, s; returns value · [reviewed contract](#b0021) |
| [B0022 · 87–87](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L87) | Explanatory comments or spacing. |  |
| [B0023 · 88–104](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L88) | Callable definition: PhysicalPlan make_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0023) |
| [B0024 · 105–105](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L105) | Explanatory comments or spacing. |  |
| [B0025 · 106–110](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L106) | Callable definition: SupportOptions options() | calls ; returns result · [reviewed contract](#b0025) |
| [B0026 · 111–111](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L111) | Explanatory comments or spacing. |  |
| [B0027 · 112–112](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L112) | Type/record definition: enum class Direction | growth insert · [reviewed contract](#b0027) |
| [B0028 · 113–113](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L113) | Explanatory comments or spacing. |  |
| [B0029 · 114–117](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L114) | Type/record definition: struct StageInput |  · [reviewed contract](#b0029) |
| [B0030 · 118–118](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L118) | Explanatory comments or spacing. |  |
| [B0031 · 119–125](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L119) | Callable definition: std::array&lt;StageInput, 3&gt; stages(Direction direction) | calls a_y2_first, b_y2, a_y2_second; returns {{{NodeId{1}, first}, {NodeId{2}, second}, {NodeId{1}, third}}} · [reviewed contract](#b0031) |
| [B0032 · 126–126](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L126) | Explanatory comments or spacing. |  |
| [B0033 · 127–129](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L127) | Callable definition: SetOperation operation(Direction direction) | calls ; returns direction == Direction::insert ? SetOperation::insert : SetOperation::erase; growth insert · [reviewed contract](#b0033) |
| [B0034 · 130–130](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L130) | Explanatory comments or spacing. |  |
| [B0035 · 131–142](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L131) | Callable definition: io::Json normalized_owners(io::Json value) | calls is_object, contains, items, self; returns value; 2 loop sites · [reviewed contract](#b0035) |
| [B0036 · 143–143](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L143) | Explanatory comments or spacing. |  |
| [B0037 · 144–147](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L144) | Callable definition: io::Json normalized_snapshot(const SupportRuntime& runtime, const PhysicalPlan& plan) | calls check, ready, normalized_owners, io::write_support_snapshot; guard check(runtime.ready(), "cannot serialize a support snapshot while an epoch is open");; returns normalized_owners(io::write_support_snapshot(runtime.snapshot(), plan)) · [reviewed contract](#b0037) |
| [B0038 · 148–148](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L148) | Explanatory comments or spacing. |  |
| [B0039 · 149–151](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L149) | Callable definition: io::Json normalized_epoch(const SupportEpoch& epoch) | calls normalized_owners, io::write_support_epoch; returns normalized_owners(io::write_support_epoch(epoch)) · [reviewed contract](#b0039) |
| [B0040 · 152–152](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L152) | Explanatory comments or spacing. |  |
| [B0041 · 153–163](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L153) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls check, code, std::string, std::runtime_error; guard check(failure.code() == code, "unexpected error code: expected " + std::string(code) + · [reviewed contract](#b0041) |
| [B0042 · 164–164](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L164) | Explanatory comments or spacing. |  |
| [B0043 · 165–173](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L165) | Callable definition: template &lt;class Action&gt; void expect_any_error(Action&& action, const std::string& message) | calls std::runtime_error · [reviewed contract](#b0043) |
| [B0044 · 174–174](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L174) | Explanatory comments or spacing. |  |
| [B0045 · 175–181](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L175) | Type/record definition: struct JournalValue | returns layout.same_token(other.layout) && values == other.values · [reviewed contract](#b0045) |
| [B0046 · 182–182](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L182) | Explanatory comments or spacing. |  |
| [B0047 · 183–189](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L183) | Callable definition: std::vector&lt;JournalValue&gt; retained_values(const std::shared_ptr&lt;const SupportJournal&gt;& journal) | calls check, reserve, size, push_back; guard check(journal != nullptr, "committed epoch omitted its retained journal");; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0047) |
| [B0048 · 190–193](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L190) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0048) |
| [B0049 · 194–198](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L194) | Callable definition: void remember_journal(JournalImages& images, const SupportEpoch& epoch) | calls check, empty, emplace_back, retained_values; guard check(epoch.journal != nullptr && !epoch.journal-&gt;records.empty(),; growth emplace_back · [reviewed contract](#b0049) |
| [B0050 · 199–199](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L199) | Explanatory comments or spacing. |  |
| [B0051 · 200–205](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L200) | Callable definition: void check_journals(const JournalImages& images, const std::string& context) | calls check, retained_values; guard check(retained_values(journal) == expected,; 1 loop sites · [reviewed contract](#b0051) |
| [B0052 · 206–206](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L206) | Explanatory comments or spacing. |  |
| [B0053 · 207–229](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L207) | Callable definition: JournalImages initialize(SupportRuntime& runtime, Direction target) | calls apply, a_y1, check, ready; guard check(first.native_changed && runtime.ready(), "first baseline update did not commit");; returns images; growth insert; 1 loop sites · [reviewed contract](#b0053) |
| [B0054 · 230–230](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L230) | Explanatory comments or spacing. |  |
| [B0055 · 231–238](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L231) | Callable definition: SupportEpoch run_batch(SupportRuntime& runtime, Direction direction) | calls begin_epoch, sequence, operation, stages; guard check(pending.stage(item.node, item.values), "prepared epoch stage unexpectedly reported no change"…; returns epoch; 1 loop sites · [reviewed contract](#b0055) |
| [B0056 · 239–239](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L239) | Explanatory comments or spacing. |  |
| [B0057 · 240–244](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L240) | Type/record definition: struct PublicHandle |  · [reviewed contract](#b0057) |
| [B0058 · 245–245](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L245) | Explanatory comments or spacing. |  |
| [B0059 · 246–267](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L246) | Callable definition: std::vector&lt;PublicHandle&gt; public_handles(const SupportRuntime& runtime) | calls snapshot, get, check, layout; guard check(found && found-&gt;layout().same_token(value.layout()) && found-&gt;values() == value.values(),; returns result; growth push_back; 5 loop sites · [reviewed contract](#b0059) |
| [B0060 · 268–268](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L268) | Explanatory comments or spacing. |  |
| [B0061 · 269–272](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L269) | Type/record definition: struct RootCounterHandles |  · [reviewed contract](#b0061) |
| [B0062 · 273–273](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L273) | Explanatory comments or spacing. |  |
| [B0063 · 274–279](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L274) | Callable definition: RootCounterHandles root_counter_handles(const SupportRuntime& runtime) | calls find, n, check; guard check(parent && visible, "root P/E keys were absent before the prepared epoch");; returns {*parent, *visible} · [reviewed contract](#b0063) |
| [B0064 · 280–280](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L280) | Explanatory comments or spacing. |  |
| [B0065 · 281–287](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L281) | Callable definition: const ProjectionKeySnapshot* projection_key(const std::vector&lt;ProjectionKeySnapshot&gt;& keys, const Row& values) | calls std::find_if, begin, end, values; returns key.key.values() == values; found == keys.end() ? nullptr : &*found · [reviewed contract](#b0065) |
| [B0066 · 288–288](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L288) | Explanatory comments or spacing. |  |
| [B0067 · 289–298](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L289) | Callable definition: void check_count(const SupportSnapshot& snapshot, NodeId node, SupportRole role, const Row& values, std::uint64_t expected, const… | calls at, check, projection_key; guard check(keys != nullptr, context + ": requested projection is absent"); · [reviewed contract](#b0067) |
| [B0068 · 299–299](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L299) | Explanatory comments or spacing. |  |
| [B0069 · 300–354](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L300) | Callable definition: void check_batch_result(const SupportRuntime& runtime, const SupportEpoch& epoch, Direction direction, RootCounterHandles stable_… | calls snapshot, find, n, check; guard check(root_p && root_e && *root_p == stable_counters.parent && *root_e == stable_counters.visible,; growth insert, push_back; 2 loop sites · [reviewed contract](#b0069) |
| [B0070 · 355–355](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L355) | Explanatory comments or spacing. |  |
| [B0071 · 356–359](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L356) | Type/record definition: struct ExpectedResult |  · [reviewed contract](#b0071) |
| [B0072 · 360–360](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L360) | Explanatory comments or spacing. |  |
| [B0073 · 361–370](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L361) | Callable definition: ExpectedResult clean_result(const PhysicalPlan& plan, Direction direction) | calls options, initialize, root_counter_handles, run_batch; returns {normalized_snapshot(runtime, plan), normalized_epoch(epoch)} · [reviewed contract](#b0073) |
| [B0074 · 371–371](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L371) | Explanatory comments or spacing. |  |
| [B0075 · 372–381](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L372) | Callable definition: void check_rollback_statistics(const storage::ArenaStatistics& before, const storage::ArenaStatistics& after, const std::string& … | calls check; guard check(before.live_records == after.live_records &&; source comment (unverified): // Free slots and generations may grow as tentative slots are retired. · [reviewed contract](#b0075) |
| [B0076 · 382–382](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L382) | Explanatory comments or spacing. |  |
| [B0077 · 383–383](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L383) | Type/record definition: enum class Phase : std::size_t |  · [reviewed contract](#b0077) |
| [B0078 · 384–384](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L384) | Explanatory comments or spacing. |  |
| [B0079 · 385–388](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L385) | Type/record definition: struct SweepCounts |  · [reviewed contract](#b0079) |
| [B0080 · 389–389](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L389) | Explanatory comments or spacing. |  |
| [B0081 · 390–486](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L390) | Callable definition: SweepCounts sweep(const PhysicalPlan& plan, Direction direction) | calls clean_result, stages, operation, options; guard check((phase == Phase::begin) == !token_existed_on_failure,; returns counts; growth emplace; 1 loop sites; source comment (unverified): // Keep allocation failure armed through token cleanup. · [reviewed contract](#b0081) |
| [B0082 · 487–487](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L487) | Explanatory comments or spacing. |  |
| [B0083 · 488–523](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L488) | Callable definition: void check_busy_readers(const PhysicalPlan& plan) | calls options, initialize, normalized_snapshot, sequence; guard check(old_handle.has_value(), "busy-reader fixture has no existing native handle");; growth insert · [reviewed contract](#b0083) |
| [B0084 · 524–524](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L524) | Explanatory comments or spacing. |  |
| [B0085 · 525–544](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L525) | Callable definition: void check_invalid_stage_aborts(const PhysicalPlan& plan) | calls options, initialize, normalized_snapshot, public_handles; guard check(pending.stage(NodeId{1}, a_y2_first()), "valid prefix stage was a no-op");; growth insert · [reviewed contract](#b0085) |
| [B0086 · 545–545](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L545) | Explanatory comments or spacing. |  |
| [B0087 · 546–567](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L546) | Callable definition: void check_destructor_cancellation_is_noalloc(const PhysicalPlan& plan) | calls options, initialize, normalized_snapshot, sequence; guard check(pending.stage(NodeId{1}, a_y2_first()), "destructor-cancellation stage was a no-op");; growth insert; source comment (unverified): // Constructing the token and staging may allocate; arm failure only · [reviewed contract](#b0087) |
| [B0088 · 568–568](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L568) | Explanatory comments or spacing. |  |
| [B0089 · 569–604](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L569) | Callable definition: void check_move_assignment_is_noalloc(const PhysicalPlan& plan) | calls options, initialize, normalized_snapshot, sequence; guard check(destination.stage(NodeId{1}, a_y2_first()) && source.stage(NodeId{1}, a_y2_first()),; growth insert · [reviewed contract](#b0089) |
| [B0090 · 605–605](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L605) | Explanatory comments or spacing. |  |
| [B0091 · 606–624](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L606) | Callable definition: void check_active_token_survives_runtime_move(const PhysicalPlan& plan) | calls options, initialize, normalized_snapshot, sequence; guard check(pending.stage(NodeId{1}, a_y2_first()), "runtime-move fixture stage was a no-op");; growth insert · [reviewed contract](#b0091) |
| [B0092 · 625–625](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L625) | Explanatory comments or spacing. |  |
| [B0093 · 626–642](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L626) | Callable definition: void check_token_retains_runtime_after_facade_destruction(const PhysicalPlan& plan) | calls options, initialize, emplace, begin_epoch; guard check(pending-&gt;stage(NodeId{1}, a_y2_first()), "destroyed-facade fixture stage was a no-op");; growth emplace, insert · [reviewed contract](#b0093) |
| [B0094 · 643–643](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L643) | Explanatory comments or spacing. |  |
| [B0095 · 644–667](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L644) | Callable definition: void check_commit_is_noalloc_and_returns_by_move(const PhysicalPlan& plan) | calls options, initialize, root_counter_handles, sequence; guard check(pending.stage(item.node, item.values), "no-allocation commit fixture stage was a no-op");; growth emplace, insert; 1 loop sites · [reviewed contract](#b0095) |
| [B0096 · 668–670](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L668) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0096) |
| [B0097 · 671–704](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L671) | Callable definition: int main() | calls make_plan, check_busy_readers, check_invalid_stage_aborts, check_destructor_cancellation_is_noalloc; guard check(insertion.failed_phase\[static_cast&lt;std::size_t&gt;(Phase::begin)\] &gt; 0 &&; returns 1; growth insert · [reviewed contract](#b0097) |

## B0001

[Lines 1–27](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L27:sha256:8b28e8e93f3f33fb4acdf961c9e666d79567687ec186aec2987a8b634042d10f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare prepared_epoch_exception_test.cpp: include "crown/api/error.hpp", "crown/io/document.hpp", "crown/io/support.hpp", "crown/planner/lower.hpp", "crown/runtime/support.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 28–35](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0003

[Lines 36–42](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L36); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm, disarm or forbid calls through the prepared-epoch executable’s ordinary global-new seam. |
| inputs / outputs | Optional signed step enters construction; destructor disables injection; forbid_allocations() sets fail_after to zero. |
| invariants | Copy/assignment are deleted; destruction resets to disabled, not a previous nested value. |
| ownership | Borrows only thread-local fail_after and owns no runtime/token state. |
| failure | Noexcept scalar state changes; it does not inject raw malloc, account-cap denials, or syscalls. |
| cost | Constant scalar bookkeeping; there is no allocation counter or byte accounting. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0004

[Lines 43–44](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L44:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in prepared_epoch_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 45–45](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch scalar ordinary new through malloc_new. |
| inputs / outputs | A size enters and malloc-backed storage or std::bad_alloc exits. |
| invariants | Scalar and array calls share fail_after; matching delete forms release returned storage. |
| ownership | Successful allocation transfers the malloc pointer to the C++ allocation caller. |
| failure | Only this ordinary global overload is faulted; raw malloc, aligned/nothrow overloads, account-limit denial, and syscalls are not injected. |
| cost | One seam call plus one malloc attempt when admitted. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0006

[Lines 46–46](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch array ordinary new\[\] through malloc_new. |
| inputs / outputs | A size enters and malloc-backed storage or std::bad_alloc exits. |
| invariants | Scalar and array calls share fail_after; matching delete forms release returned storage. |
| ownership | Successful allocation transfers the malloc pointer to the C++ allocation caller. |
| failure | Only this ordinary global overload is faulted; raw malloc, aligned/nothrow overloads, account-limit denial, and syscalls are not injected. |
| cost | One seam call plus one malloc attempt when admitted. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0007

[Lines 47–47](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the replacement scalar unsized delete family. |
| inputs / outputs | A pointer from the matching scalar allocation form enters; no value is returned. |
| invariants | The body calls std::free on the supplied pointer and leaves fail_after unchanged. |
| ownership | Pointer is borrowed for the call and freed here if it is compatible malloc-backed replacement storage. |
| failure | Delete is noexcept and does not inject; no direct malloc/systemcall behavior is measured. |
| cost | One std::free call and no allocation request. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0008

[Lines 48–48](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the replacement array unsized delete family. |
| inputs / outputs | A pointer from the matching array allocation form enters; no value is returned. |
| invariants | The body calls std::free on the supplied pointer and leaves fail_after unchanged. |
| ownership | Pointer is borrowed for the call and freed here if it is compatible malloc-backed replacement storage. |
| failure | Delete is noexcept and does not inject; no direct malloc/systemcall behavior is measured. |
| cost | One std::free call and no allocation request. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0009

[Lines 49–49](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the replacement scalar sized delete family. |
| inputs / outputs | A pointer from the matching scalar allocation form enters; no value is returned. |
| invariants | The body calls std::free on the supplied pointer and leaves fail_after unchanged. |
| ownership | Pointer is borrowed for the call and freed here if it is compatible malloc-backed replacement storage. |
| failure | Delete is noexcept and does not inject; no direct malloc/systemcall behavior is measured. |
| cost | One std::free call and no allocation request. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0010

[Lines 50–50](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the replacement array sized delete family. |
| inputs / outputs | A pointer from the matching array allocation form enters; no value is returned. |
| invariants | The body calls std::free on the supplied pointer and leaves fail_after unchanged. |
| ownership | Pointer is borrowed for the call and freed here if it is compatible malloc-backed replacement storage. |
| failure | Delete is noexcept and does not inject; no direct malloc/systemcall behavior is measured. |
| cost | One std::free call and no allocation request. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0011

[Lines 51–59](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L59:sha256:ced7a140dcf47adfc4ff0cd18036ef8103fac4ed93d02cbb8a1a0369d4eb496b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare prepared_epoch_exception_test.cpp: bind local aliases/name imports; require 3 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 60–62](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a false fixture condition into a named runtime_error. |
| inputs / outputs | A bool and const std::string& enter; true returns and false throws runtime_error with a copied diagnostic. |
| invariants | The input message is borrowed during the call; this helper catches no action exceptions. |
| ownership | Inputs are borrowed during fixture construction; returned schema/plan/rows own their values unless an accessor explicitly returns a const reference to static storage. |
| failure | Standard value construction, plan lowering or test assertions may throw; fixture helpers do not catch product errors or translate allocation failures. |
| cost | Constructs the fixed two-relation/tiny-row oracle named by the helper; no measured CPU time, allocator bytes or performance bound. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0014

[Lines 64–64](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap one int64 fixture value in Value. |
| inputs / outputs | An int64 enters and the equal integer Value exits. |
| invariants | The result is a value alternative without a borrowed reference. |
| ownership | Inputs are borrowed during fixture construction; returned schema/plan/rows own their values unless an accessor explicitly returns a const reference to static storage. |
| failure | Standard value construction, plan lowering or test assertions may throw; fixture helpers do not catch product errors or translate allocation failures. |
| cost | Constructs the fixed two-relation/tiny-row oracle named by the helper; no measured CPU time, allocator bytes or performance bound. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0015

[Lines 65–65](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap one owning string fixture value in Value. |
| inputs / outputs | A std::string enters by value and a Value string alternative exits. |
| invariants | The returned variant owns the string contents. |
| ownership | Inputs are borrowed during fixture construction; returned schema/plan/rows own their values unless an accessor explicitly returns a const reference to static storage. |
| failure | Standard value construction, plan lowering or test assertions may throw; fixture helpers do not catch product errors or translate allocation failures. |
| cost | Constructs the fixed two-relation/tiny-row oracle named by the helper; no measured CPU time, allocator bytes or performance bound. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0017

[Lines 67–70](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row& a_y1() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the static A row for y=1. |
| inputs / outputs | No input; const Row& to (10,1,"a-y1") exits. |
| invariants | Field order is x,y,witness and layout matches A. |
| ownership | Each returned reference borrows a function-static const Row containing its own scalar/string values for process lifetime. |
| failure | First static initialization can propagate ordinary allocation failure; the accessor has no local catch or injected fault. |
| cost | One fixed small row is initialized on first use and reused; no CPU or byte bound is claimed. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0018

[Lines 71–74](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row& b_y1() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the static B row for y=1. |
| inputs / outputs | No input; const Row& to (10,1,"b-y1") exits. |
| invariants | Field order is x,y,witness and layout matches B. |
| ownership | Each returned reference borrows a function-static const Row containing its own scalar/string values for process lifetime. |
| failure | First static initialization can propagate ordinary allocation failure; the accessor has no local catch or injected fault. |
| cost | One fixed small row is initialized on first use and reused; no CPU or byte bound is claimed. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0019

[Lines 75–78](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row& a_y2_first() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the first static A witness row for y=2. |
| inputs / outputs | No input; const Row& to (10,2,"a-y2-first") exits. |
| invariants | The string distinguishes this A row from the later same-key witness. |
| ownership | Each returned reference borrows a function-static const Row containing its own scalar/string values for process lifetime. |
| failure | First static initialization can propagate ordinary allocation failure; the accessor has no local catch or injected fault. |
| cost | One fixed small row is initialized on first use and reused; no CPU or byte bound is claimed. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0020

[Lines 79–82](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row& a_y2_second() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the second static A witness row for y=2. |
| inputs / outputs | No input; const Row& to (10,2,"a-y2-second") exits. |
| invariants | It shares x,y with a_y2_first but is a distinct full row. |
| ownership | Each returned reference borrows a function-static const Row containing its own scalar/string values for process lifetime. |
| failure | First static initialization can propagate ordinary allocation failure; the accessor has no local catch or injected fault. |
| cost | One fixed small row is initialized on first use and reused; no CPU or byte bound is claimed. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0021

[Lines 83–86](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row& b_y2() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the static B row paired with the y=2 A rows. |
| inputs / outputs | No input; const Row& to (10,2,"b-y2") exits. |
| invariants | This B row joins both A rows on x,y. |
| ownership | Each returned reference borrows a function-static const Row containing its own scalar/string values for process lifetime. |
| failure | First static initialization can propagate ordinary allocation failure; the accessor has no local catch or injected fault. |
| cost | One fixed small row is initialized on first use and reused; no CPU or byte bound is claimed. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0023

[Lines 88–104](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the fixed A/B join tree used for prepared epoch insert/erase fixtures. |
| inputs / outputs | No input; local two-table Catalog, Query and FreeConnexTree enter lower_tree; a PhysicalPlan exits. |
| invariants | The two native relations share x,y and the public core head is x; row values below conform to the two descriptors. |
| ownership | Inputs are borrowed during fixture construction; returned schema/plan/rows own their values unless an accessor explicitly returns a const reference to static storage. |
| failure | Standard value construction, plan lowering or test assertions may throw; fixture helpers do not catch product errors or translate allocation failures. |
| cost | Constructs the fixed two-relation/tiny-row oracle named by the helper; no measured CPU time, allocator bytes or performance bound. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0025

[Lines 106–110](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportOptions options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable support transition capture while retaining default support limits. |
| inputs / outputs | No input; SupportOptions with capture_transitions=true exits. |
| invariants | This helper does not set memory/work limits or a fault point. |
| ownership | Inputs are borrowed during fixture construction; returned schema/plan/rows own their values unless an accessor explicitly returns a const reference to static storage. |
| failure | Standard value construction, plan lowering or test assertions may throw; fixture helpers do not catch product errors or translate allocation failures. |
| cost | Constructs the fixed two-relation/tiny-row oracle named by the helper; no measured CPU time, allocator bytes or performance bound. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0027

[Lines 112–112](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L112); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Direction { insert, erase };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name whether the three-stage epoch fixture inserts or erases its rows. |
| inputs / outputs | No input; enum Direction has insert and erase alternatives. |
| invariants | Direction selects one operation for the whole prepared epoch; stages() uses the same row inputs for either polarity. |
| ownership | Value enum with no dynamic ownership. |
| failure | No runtime failure path in the enum declaration. |
| cost | Constant-size enum storage. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md) |

## B0029

[Lines 114–117](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L114); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StageInput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair one native SupportRuntime node with an owning Row for each prepared stage. |
| inputs / outputs | NodeId and Row members are value-initialized/provided; StageInput owns its row value. |
| invariants | The node selects A or B in the fixed plan and values retain the complete scope expected by that native node. |
| ownership | Row owns its scalar and string values; no input view is stored. |
| failure | Row construction/copy can allocate and propagate; no catch is present. |
| cost | One NodeId plus the small owned row payload. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0031

[Lines 119–125](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<StageInput, 3> stages(Direction direction) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return three ordered native stage inputs for either insert or erase direction. |
| inputs / outputs | Direction is accepted but ignored; returns an owning array of A(y2 first), B(y2), A(y2 second) StageInput values. |
| invariants | Order is significant: three stages share x=10,y=2, with two distinct A witnesses; operation() supplies polarity separately. |
| ownership | Returned array owns each Row; source static rows are copied for the value-returning array. |
| failure | Row/string copies can propagate allocation failure; no fault point is installed here. |
| cost | Copies a fixed three-element array of small stage rows; no CPU/byte bound. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md) |

## B0033

[Lines 127–129](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SetOperation operation(Direction direction) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map a batch direction to its logical set operation. |
| inputs / outputs | Direction::insert or Direction::erase enters; matching SetOperation exits. |
| invariants | Only the two enum alternatives are present. |
| ownership | Inputs are borrowed during fixture construction; returned schema/plan/rows own their values unless an accessor explicitly returns a const reference to static storage. |
| failure | Standard value construction, plan lowering or test assertions may throw; fixture helpers do not catch product errors or translate allocation failures. |
| cost | Constructs the fixed two-relation/tiny-row oracle named by the helper; no measured CPU time, allocator bytes or performance bound. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0035

[Lines 131–142](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json normalized_owners(io::Json value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace every serialized owner identifier in a copied JSON tree with zero. |
| inputs / outputs | A JSON value enters by value; recursive object/array traversal mutates and returns that value. |
| invariants | Only object members named owner are normalized; all other keys, arrays and scalar values remain unchanged. |
| ownership | The input JSON value is passed by value; returned or mutated JSON owns its object/array/scalar storage and keeps no runtime borrow. |
| failure | JSON construction, traversal, or serialization allocation failures propagate; no runtime error is swallowed. |
| cost | Visits the small fixed snapshot/event image and copies JSON values; serialization and copies are outside SupportMetrics work and no CPU/byte bound is inferred. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [docs/prepared_epochs.md § Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0037

[Lines 144–147](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json normalized_snapshot(const SupportRuntime& runtime, const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one ready committed support snapshot with owner identifiers normalized. |
| inputs / outputs | SupportRuntime and plan are borrowed; normalized JSON from write_support_snapshot(runtime.snapshot(), plan) exits. |
| invariants | The runtime must be ready before snapshot; it is a diagnostic/canonical image and does not commit or mutate state. |
| ownership | The input JSON value is passed by value; returned or mutated JSON owns its object/array/scalar storage and keeps no runtime borrow. |
| failure | JSON construction, traversal, or serialization allocation failures propagate; no runtime error is swallowed. |
| cost | Visits the small fixed snapshot/event image and copies JSON values; serialization and copies are outside SupportMetrics work and no CPU/byte bound is inferred. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [docs/prepared_epochs.md § Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0039

[Lines 149–151](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json normalized_epoch(const SupportEpoch& epoch) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a committed SupportEpoch and normalize owner IDs in its image. |
| inputs / outputs | SupportEpoch is borrowed; JSON from write_support_epoch is normalized and returned by value. |
| invariants | Sequence, event/journal fields and other diagnostic values are preserved while owner IDs are zeroed. |
| ownership | The input JSON value is passed by value; returned or mutated JSON owns its object/array/scalar storage and keeps no runtime borrow. |
| failure | JSON construction, traversal, or serialization allocation failures propagate; no runtime error is swallowed. |
| cost | Visits the small fixed snapshot/event image and copies JSON values; serialization and copies are outside SupportMetrics work and no CPU/byte bound is inferred. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [docs/prepared_epochs.md § Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0041

[Lines 153–163](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void expect_error(Action&& action, std::string_view code) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to throw crown::api::Error with one exact code. |
| inputs / outputs | Forwarded action and expected code enter; matching error returns normally. |
| invariants | A wrong code fails through check; normal action completion throws the expected-error runtime_error. |
| ownership | Action and diagnostic strings are borrowed for the call; no runtime, token or output object is retained. |
| failure | Only crown::api::Error is treated as an expected product error. Wrong code or missing error throws runtime_error; other exception types propagate. |
| cost | One action invocation and exception-code comparison; no retry or resource measurement. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0043

[Lines 165–173](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void expect_any_error(Action&& action, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to throw any crown::api::Error while preserving a caller diagnostic. |
| inputs / outputs | Forwarded action and const diagnostic string reference enter; any Error returns normally. |
| invariants | A different exception type is not accepted; normal completion throws runtime_error with the diagnostic. |
| ownership | Action and diagnostic strings are borrowed for the call; no runtime, token or output object is retained. |
| failure | Only crown::api::Error is treated as an expected product error. Wrong code or missing error throws runtime_error; other exception types propagate. |
| cost | One action invocation and exception-code comparison; no retry or resource measurement. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0045

[Lines 175–181](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L175); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct JournalValue {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a retained journal layout token and detached Row image for cross-epoch equality checks. |
| inputs / outputs | AccountedLayout plus Row are value members; equality requires same layout token and equal row values. |
| invariants | The copied layout retains layout identity; Row owns exported scalar/string values; no SupportJournal record reference is stored. |
| ownership | The value is owned by the containing vector; AccountedLayout copy shares its immutable token/control as defined by the layout API. |
| failure | Row/layout copies or equality may propagate errors; no exception is caught. |
| cost | Copies one small layout handle and row image; storage scales with saved journal rows but is not reported as query-account bytes by this oracle. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md) |

## B0047

[Lines 183–189](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<JournalValue> retained_values(const std::shared_ptr<const SupportJournal>& journal) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture every retained SupportJournal tuple as a copied layout/value image. |
| inputs / outputs | A shared_ptr&lt;const SupportJournal&gt; is borrowed; returns a vector of JournalValue images, reserving and exporting each retained record tuple. |
| invariants | A non-null journal is required; returned images preserve record order and values, detached from journal record references. |
| ownership | The shared journal remains caller-owned; each AccountedLayout copy retains its token and each exported Row owns values. |
| failure | Null journal fails check; reserve/export/copy allocation errors propagate. |
| cost | Visits all journal records and copies each row once into a vector; no byte/time limit or support-work accounting claim. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md) |

## B0048

[Lines 190–193](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L190); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L190-L193:sha256:2423c4126b84a4a8186057645b3838473265784ca3c8eab94caee2eac44cad47
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare prepared_epoch_exception_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/code_review.md](../../../../code_review.md) |

## B0049

[Lines 194–198](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void remember_journal(JournalImages& images, const SupportEpoch& epoch) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep a shared journal pin and detached expected values from one committed setup epoch. |
| inputs / outputs | JournalImages vector and SupportEpoch are borrowed; requires nonempty epoch journal, captures retained_values, and appends the shared journal plus image. |
| invariants | Caller-held shared_ptr deliberately prolongs journal-pinned affected tuples; expected row image is copied independently for later equality. |
| ownership | Vector owns shared_ptr and copied JournalValue rows; epoch argument is borrowed only during capture. |
| failure | Missing/empty journal fails check; vector/copy errors propagate. |
| cost | Captures the affected records in one setup epoch; retained history cost is intentionally separate from runtime work metrics. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp) |

## B0051

[Lines 200–205](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_journals(const JournalImages& images, const std::string& context) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Re-read each retained journal pin and compare it with the detached expected image. |
| inputs / outputs | JournalImages and a borrowed context string enter; no result value, throws on mismatch. |
| invariants | Every retained journal pointer must remain non-null and current record values/layout tokens must equal its saved image. |
| ownership | Shared pointers keep journals alive for the call; expected images own their Rows. |
| failure | A differing retained value throws runtime_error; journal access/copy failures propagate. |
| cost | Scans each saved journal record and copies values for comparison; no byte or CPU budget is asserted. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp) |

## B0053

[Lines 207–229](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
JournalImages initialize(SupportRuntime& runtime, Direction target) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize a SupportRuntime baseline and retain its committed affected-row journals. |
| inputs / outputs | Runtime reference and Direction enter; commits sequence 1 A(y1), sequence 2 B(y1), and for erase target commits one three-row insert epoch; returns JournalImages. |
| invariants | Each real setup update must change state and close ready; retained journal images stay equal after later mutations; runtime invariant check finishes setup. |
| ownership | Runtime is borrowed and remains caller-owned; returned JournalImages own shared journal pins plus copied expected images. |
| failure | Any check/runtime/storage/allocation error propagates; this helper does not install the allocation fault scope. |
| cost | Two fixed single-row commits plus either no third commit or one three-stage commit; not a work/CPU/byte bound. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md) |

## B0055

[Lines 231–238](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportEpoch run_batch(SupportRuntime& runtime, Direction direction) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute and return one complete three-stage insert or erase epoch on the supplied SupportRuntime. |
| inputs / outputs | Runtime reference and Direction enter; begin_epoch at sequence+1 stages the three ordered inputs and returns committed SupportEpoch. |
| invariants | Every stage must report a membership change; commit closes token and returns runtime to ready. |
| ownership | Runtime remains caller-owned; token owns its transaction until commit; returned SupportEpoch owns moved output/journal. |
| failure | Stage, commit, allocation or assertion failures propagate; no local catch/retry. |
| cost | Exactly three small stages plus their drained propagation; operation work is measured separately in SupportMetrics. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Batch event and resource accounting](../../../../prepared_epochs.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/runtime_support.md § Update metrics](../../../../runtime_support.md) |

## B0057

[Lines 240–244](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L240); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PublicHandle {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair a public SupportHandle with the owning tuple payload resolved for it. |
| inputs / outputs | SupportHandle and storage::Tuple are value members; default equality compares both. |
| invariants | The handle remains owner/node/role/tuple identity; Tuple carries the resolved value payload rather than a borrowed table row. |
| ownership | Tuple shares/retains its accounted immutable payload; handle is a value ID. |
| failure | Tuple copy/equality can fail only through underlying value operations; no catch. |
| cost | One handle plus an owning tuple handle/control reference; payload may be shared, not duplicated. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md) |

## B0059

[Lines 246–267](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<PublicHandle> public_handles(const SupportRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture all public handles and owning tuple values represented by a SupportSnapshot. |
| inputs / outputs | SupportRuntime is borrowed; snapshot records, survivors, parent keys and optional visible keys are resolved through find/get and returned as a vector&lt;PublicHandle&gt;. |
| invariants | Every represented snapshot row/key must map to a public handle and runtime.get must resolve the same layout token and values. |
| ownership | Snapshot is a local owning copy; the output vector retains Tuple payload owners and value handle IDs, not snapshot references. |
| failure | Missing/mismatched handle throws runtime_error; snapshot/vector/tuple allocation errors propagate. |
| cost | Visits all fixed snapshot records, survivors and key entries and retains one tuple reference for each; no byte or CPU limit. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md) |

## B0061

[Lines 269–272](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L269); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RootCounterHandles {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the two root projection handles whose support counts are checked across the batch. |
| inputs / outputs | Parent-support and visible-root handles are value members of RootCounterHandles. |
| invariants | Fields represent the empty root parent key and visible key x=10 respectively; both are expected to exist in initialized fixture. |
| ownership | Handle IDs are copied values scoped to their SupportOwnerId; no tuple payload is owned here. |
| failure | No throw in the aggregate itself; finding/validation occurs in root_counter_handles. |
| cost | Two small value identifiers. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md) |

## B0063

[Lines 274–279](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RootCounterHandles root_counter_handles(const SupportRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve and return the root parent-support and visible-key handles. |
| inputs / outputs | Committed SupportRuntime is borrowed; find() for root parent_support and visible x=10 returns RootCounterHandles. |
| invariants | Both handles must exist before the prepared epoch; they are later compared for identity stability. |
| ownership | Runtime owns the tables; returned SupportHandle IDs are value copies, not row pins. |
| failure | Missing root keys throw runtime_error; read/API errors propagate. |
| cost | Two exact lookups in the fixed root snapshot. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md) |

## B0065

[Lines 281–287](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L281); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ProjectionKeySnapshot* projection_key(const std::vector<ProjectionKeySnapshot>& keys,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find a ProjectionKeySnapshot by exact owning key values and return its borrowed address. |
| inputs / outputs | Key vector and Row are borrowed; pointer to first equal key entry or null exits. |
| invariants | Returned pointer is valid only while the input vector remains alive and unmodified; search does not copy or retain a key. |
| ownership | Vector owns entries and key tuples; returned pointer is a non-owning element address. |
| failure | Invalid vector/index access is not translated; value comparison errors propagate. |
| cost | Linear scan over the supplied small projection-key vector; no CPU/latency guarantee. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md) |

## B0067

[Lines 289–298](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L289); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_count(const SupportSnapshot& snapshot, NodeId node, SupportRole role,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert one projection support counter in a SupportSnapshot. |
| inputs / outputs | Snapshot, node, role, key Row, expected integer and borrowed context enter; no result, throws on mismatch. |
| invariants | Selects parent_keys or present visible_keys by role; the matching key must exist and have exactly the expected count. |
| ownership | Snapshot/Row/context are borrowed for the call; no reference escapes. |
| failure | Absent projection or mismatched counter throws runtime_error; vector::at and comparisons may propagate. |
| cost | One node access and a linear lookup over its selected projection vector. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md) |

## B0069

[Lines 300–354](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L300); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_batch_result(const SupportRuntime& runtime, const SupportEpoch& epoch,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the committed batch snapshot, stable root handles, counts, retained journal and event-causality oracle. |
| inputs / outputs | Runtime, returned SupportEpoch, Direction and prior root handles enter; snapshots and event vectors are inspected; no output value. |
| invariants | Root parent/visible handles remain stable; expected counts and root records differ by operation; epoch sequence/answer/journal match runtime; events have unique IDs, valid causal links and a one-based applied-ordinal permutation. |
| ownership | Runtime owns tables; SupportEpoch owns its moved journal/output; copied vectors of IDs/ordinals are local, while snapshot is an owning diagnostic value. |
| failure | Any failed exact field/count/causality check throws runtime_error; runtime reads/allocation errors propagate. |
| cost | Copies one small snapshot and scans its fixed support events, records, counters and projection entries. Event/work metrics are not CPU time or bytes. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § Batch event and resource accounting](../../../../prepared_epochs.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/runtime_support.md § Update metrics](../../../../runtime_support.md), [docs/runtime_support.md § Handles and snapshots](../../../../runtime_support.md) |

## B0071

[Lines 356–359](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L356); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ExpectedResult {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store detached normalized snapshot and epoch JSON as one clean expected result. |
| inputs / outputs | Two JSON values are members; default construction/copy/move semantics own their content. |
| invariants | Snapshot and event images are compared independently; owner IDs have been normalized by their producer. |
| ownership | Both JSON trees own their values; they do not borrow runtime or journal state. |
| failure | JSON construction/copy allocation failures propagate; no catch. |
| cost | Storage scales with the small serialized setup and batch journal images; no account byte measurement. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp), [docs/prepared_epochs.md § Batch event and resource accounting](../../../../prepared_epochs.md) |

## B0073

[Lines 361–370](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L361); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExpectedResult clean_result(const PhysicalPlan& plan, Direction direction) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an independent clean committed oracle for one insertion or deletion batch. |
| inputs / outputs | Plan and Direction enter; fresh SupportRuntime is initialized, stable counters captured, run_batch and check_batch_result execute; owning ExpectedResult JSON exits. |
| invariants | Oracle uses the same deterministic stage fixture on a fresh owner and runs invariants before return; no caller runtime is changed. |
| ownership | Fresh runtime is local; returned JSON trees own normalized snapshot/epoch values; temporary journal pins release with local objects. |
| failure | Setup/batch/errors propagate; no fault injector or retry loop is installed here. |
| cost | Fresh baseline setup plus one three-stage batch and serialization; oracle workload is fixture-only, not a CPU/byte guarantee. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § Batch event and resource accounting](../../../../prepared_epochs.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/runtime_support.md § Update metrics](../../../../runtime_support.md), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp) |

## B0075

[Lines 372–381](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L372); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_rollback_statistics(const storage::ArenaStatistics& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare rollback arena statistics without claiming exact slot or allocator-byte restoration. |
| inputs / outputs | Before/after ArenaStatistics and borrowed context enter; no value exits. |
| invariants | Live records, retained records and pins must be equal; slots may stay at or grow beyond the earlier high-water value. Free slots and generations may grow after retiring tentative rows. |
| ownership | Statistics and context are borrowed value inputs; helper owns no arena or allocation. |
| failure | A violation throws runtime_error; no translation. |
| cost | Compares four scalar facts; explicitly not an exact capacity, byte, RSS or CPU measure. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/storage/accounted_arena.hpp](../../../../../include/crown/storage/accounted_arena.hpp), [docs/storage_journal.md § Scope boundary](../../../../storage_journal.md), [docs/query_memory.md § Reports and evidence](../../../../query_memory.md) |

## B0077

[Lines 383–383](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L383); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Phase : std::size_t { begin = 0, first_stage = 1, second_stage = 2, third_stage = 3, commit = 4 };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name begin, first/second/third stage, and commit positions in the allocation sweep. |
| inputs / outputs | Phase enum values map to positions 0 through 4 in the failure histogram. |
| invariants | Phase tracks the operation active when std::bad_alloc propagates; it is not a runtime status or error-code enum. |
| ownership | Value enum with no dynamic ownership. |
| failure | No runtime failure path in the enum declaration. |
| cost | Constant-size enum storage. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0079

[Lines 385–388](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L385); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SweepCounts {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count allocation sweep failures overall and separately at each epoch phase. |
| inputs / outputs | One total and five-element phase-count array are value-initialized; sweep increments them and returns counts. |
| invariants | Array positions correspond exactly to Phase underlying values; totals are counts of injected failures, not bytes or allocation requests. |
| ownership | Returned value owns only scalar counters. |
| failure | Indexing beyond declared phase set is checked by callers with std::array::at. |
| cost | Fixed five counters, independent of number of fail points. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0081

[Lines 390–486](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L390); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SweepCounts sweep(const PhysicalPlan& plan, Direction direction) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep allocation-failure positions across begin, three stage calls and commit for an insertion or deletion batch. |
| inputs / outputs | Plan and Direction enter; fresh clean expected JSON is built, then up to 8192 fail points each create/initialize a new runtime and fault one selected ordinary global-new position through begin/stage/commit. |
| invariants | On begin failure no token exists; on stage failure the entire token must auto-close/rollback; fail_after remains zero through token cleanup. Committed sequence/answer/snapshot/handles/root IDs and prior journal pins equal pre-state, then the same runtime retries the full batch at the same sequence and matches the clean oracle. First success must match oracle; caller separately requires failures at begin and all three stages and zero commit failures. |
| ownership | Each loop owns one runtime and an optional move-only PendingEpoch; prior shared journal pins and copied images remain caller-owned. After failure, cleanup and a same-owner full-batch retry occur before the next fresh trial. |
| failure | Only std::bad_alloc at replaced ordinary global new/new\[\] is injected. Account admission can precede the C++ new cut but no MemoryAccount cap denial is synthesized; raw malloc, aligned/nothrow overloads and syscalls are outside. Operation errors other than caught bad_alloc propagate. |
| cost | At most 8192 selected C++ new positions per direction, stopping at first successful full batch; each position rebuilds the tiny baseline and verifies several snapshot/event oracles. Not a performance, bytes, or CPU bound. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Batch event and resource accounting](../../../../prepared_epochs.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/runtime_support.md § Update metrics](../../../../runtime_support.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0083

[Lines 488–523](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L488); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_busy_readers(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a live pending token keeps committed reads busy and explicit rollback preserves unpublished state. |
| inputs / outputs | Plan enters; initialized runtime begins the next epoch and stages one row; preview/snapshot expose tentative sequence, while public state reads and invariant calls are expected to return runtime_busy. |
| invariants | Committed sequence and snapshot remain unchanged during staging; rollback closes token without consuming sequence, restores ready state, preserves snapshot, and later commit on the closed token is invalid_epoch. |
| ownership | Runtime owns state; PendingEpoch owns the private transaction; pending snapshot is an owning diagnostic value, preview is borrowed only while token is active. |
| failure | expect_error checks exact busy/invalid_epoch codes; other allocation/runtime errors propagate. No allocation fault is injected. |
| cost | One stage, one snapshot and a fixed set of busy guards on a small runtime; no memory or CPU measurement. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0085

[Lines 525–544](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L525); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_invalid_stage_aborts(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an invalid native node after a successful prefix stage to abort the entire pending epoch. |
| inputs / outputs | Plan enters; initialized owner and saved snapshot/handles/stats/journals are captured; pending token stages a valid A row then calls stage with an out-of-range node. |
| invariants | Any crown::api::Error is accepted for invalid node; token closes, runtime is ready at old sequence, snapshot/handles/stats and retained journals match pre-state, and closed commit is invalid_epoch. |
| ownership | Runtime and earlier journal pins remain caller-owned; pending token owns undo until it auto-rolls back; detached before snapshot/handles own expected values. |
| failure | Invalid stage exception is caught by expect_any_error; expected cleanup and later assertion failures propagate. This is semantic validation failure, not injected bad_alloc. |
| cost | One valid prefix stage and one invalid stage with exact state/journal checks; no bytes/CPU limit. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/storage_journal.md § Scope boundary](../../../../storage_journal.md) |

## B0087

[Lines 546–567](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L546); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_destructor_cancellation_is_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require pending-token destructor cancellation to undo a staged row while ordinary global new is forbidden. |
| inputs / outputs | Plan enters; initialized runtime snapshots state/journals; token construction and one stage occur with injection disabled, then fail_after=0 is set immediately before token scope exit. |
| invariants | Destructor restores ready state, committed sequence/snapshot/journal images and runtime invariants without an intercepted new/new\[\] call. |
| ownership | Runtime and retained journal pins outlive the scoped token; token destructor owns rollback of its private transaction. |
| failure | Fail-zero covers replaced ordinary global new/new\[\] only; direct malloc/syscalls/account-limit denial are outside. This is not an all-allocation or whole-process claim. |
| cost | One staged row and token teardown plus detached state checks; no CPU/byte metric. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0089

[Lines 569–604](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L569); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_move_assignment_is_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check no-intercepted-new move assignment rolls back a destination token and transfers a source token. |
| inputs / outputs | Plan enters; two initialized runtimes retain independent journals/snapshots and open/stage one token each; destination=move(source), then destination rollback, under fail_after=0. |
| invariants | Source token becomes inactive; both runtimes return ready without publishing either sequence; snapshots and saved journal pins remain unchanged; destination commit on closed token is invalid_epoch. |
| ownership | Two runtimes own distinct accounts/state; move assignment destroys destination transaction then transfers source token; output images and journal references remain separate owning oracles. |
| failure | Fail-zero rejects calls through replaced ordinary new/new\[\] during move/rollback only; raw malloc/syscalls and account cap failures are not injected. |
| cost | Two small runtimes and one token transfer/rollback; no bytes, CPU or performance result. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md) |

## B0091

[Lines 606–624](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L606); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_active_token_survives_runtime_move(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove an active PendingEpoch remains attached when its SupportRuntime facade is moved. |
| inputs / outputs | Plan enters; initialized facade opens/stages token, then facade move-constructs a new SupportRuntime; the same token rolls back against moved owner. |
| invariants | Token stays active and moved owner stays busy at old sequence until rollback; rollback restores ready state, old snapshot, retained journals and invariants. |
| ownership | Pending token and moved facade share/transfer the runtime implementation; the moved-from facade is not reused. |
| failure | Errors/assertions propagate; no allocation fault is injected. |
| cost | One facade move, one staged row, rollback and state comparisons; no CPU or byte bound. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0093

[Lines 626–642](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L626); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_token_retains_runtime_after_facade_destruction(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove a pending token retains enough runtime ownership to roll back after its facade is destroyed. |
| inputs / outputs | Plan enters; runtime initializes, then a token is emplaced outside the runtime scope and stages one row; after facade destruction rollback runs under fail_after=0. |
| invariants | Token becomes inactive after rollback; commit on closed token reports invalid_epoch. The test does not read the destroyed facade. |
| ownership | Optional owns the move-only token, which retains shared runtime implementation; the local journal pin vector is released before token rollback. |
| failure | Fail-zero covers ordinary global new/new\[\] during rollback only; raw malloc, account-cap failure and syscalls are not checked. |
| cost | One owner setup, one staged row and rollback after facade scope; no memory/CPU bound. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0095

[Lines 644–667](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L644); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_commit_is_noalloc_and_returns_by_move(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require successful prepared-epoch commit to return output by move while ordinary global new is forbidden. |
| inputs / outputs | Plan enters; one initialized runtime captures journal/root-handle oracles, opens token, stages the three insert rows, then emplaces commit output under fail_after=0. |
| invariants | Commit returns owning SupportEpoch, closes token, restores ready state, advances exactly one sequence, satisfies batch/event checks, preserves retained journals, and rejects a second commit as invalid_epoch. |
| ownership | Runtime owns committed state; returned SupportEpoch owns moved transition/journal data; retained setup pins remain held in caller vector. |
| failure | Fail-zero covers ordinary replaced global new/new\[\] during commit only. Other allocators/syscalls are not instrumented; source expects commit’s no-throw publication path. |
| cost | Three staged rows and one commit/output transfer with state/journal checks; no CPU/byte performance guarantee. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Batch event and resource accounting](../../../../prepared_epochs.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/runtime_support.md § Update metrics](../../../../runtime_support.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0096

[Lines 668–670](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L668); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L668-L670:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in prepared_epoch_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/code_review.md](../../../../code_review.md) |

## B0097

[Lines 671–704](../../../../../tests/unit/prepared_epoch_exception_test.cpp#L671); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Orchestrate token lifecycle checks and insertion/deletion allocation sweeps, then assert phase coverage and allocation-free commit. |
| inputs / outputs | No external input; builds one plan, runs busy/invalid/destructor/move/lifetime/commit fixtures, then calls sweep for insert and erase and checks returned phase histograms. |
| invariants | Both sweeps must record failure at begin and all three stage positions; commit phase failure count must be zero. Catch resets fail_after and returns one; final print is not evidence the executable ran in review. |
| ownership | All runtimes, tokens, journal pins and clean-result JSON are local to helper scopes; no external state is retained. |
| failure | Main catches std::exception and prints a diagnostic; no syscall injector or execution claim is part of this source review. |
| cost | Two sweeps each stop at first success within 8192 fault positions plus fixed lifecycle cases; not a CPU, memory-byte or throughput benchmark. |
| Design | [tests/unit/prepared_epoch_exception_test.cpp](../../../../../tests/unit/prepared_epoch_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Batch event and resource accounting](../../../../prepared_epochs.md), [docs/runtime_support.md § Atomicity and accounting](../../../../runtime_support.md), [docs/runtime_support.md § Update metrics](../../../../runtime_support.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |
