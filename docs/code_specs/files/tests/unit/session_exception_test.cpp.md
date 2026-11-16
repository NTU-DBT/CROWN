# `tests/unit/session_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/session_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `fc84e4f63464c521af14aa9c729f32e637001f7006c2177499836e99b83b66a0`. 1163 lines partitioned into 93 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–34](../../../../../tests/unit/session_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // This executable replaces ordinary throwing scalar and array global new so · [reviewed contract](#b0001) |
| [B0002 · 35–43](../../../../../tests/unit/session_exception_test.cpp#L35) | Callable definition: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes) | calls std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 44–44](../../../../../tests/unit/session_exception_test.cpp#L44) | Explanatory comments or spacing. |  |
| [B0004 · 45–51](../../../../../tests/unit/session_exception_test.cpp#L45) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0004) |
| [B0005 · 52–53](../../../../../tests/unit/session_exception_test.cpp#L52) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 54–54](../../../../../tests/unit/session_exception_test.cpp#L54) | Callable definition: void* operator new(std::size_t bytes) | calls malloc_new; returns malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 55–55](../../../../../tests/unit/session_exception_test.cpp#L55) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns malloc_new(bytes); growth new · [reviewed contract](#b0007) |
| [B0008 · 56–56](../../../../../tests/unit/session_exception_test.cpp#L56) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0008) |
| [B0009 · 57–57](../../../../../tests/unit/session_exception_test.cpp#L57) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0009) |
| [B0010 · 58–58](../../../../../tests/unit/session_exception_test.cpp#L58) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0010) |
| [B0011 · 59–59](../../../../../tests/unit/session_exception_test.cpp#L59) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0011) |
| [B0012 · 60–66](../../../../../tests/unit/session_exception_test.cpp#L60) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_destructible_v&lt;QuerySession&gt;); · [reviewed contract](#b0012) |
| [B0013 · 67–69](../../../../../tests/unit/session_exception_test.cpp#L67) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0013) |
| [B0014 · 70–70](../../../../../tests/unit/session_exception_test.cpp#L70) | Explanatory comments or spacing. |  |
| [B0015 · 71–81](../../../../../tests/unit/session_exception_test.cpp#L71) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls check, code, std::string, std::runtime_error; guard check(failure.code() == code, · [reviewed contract](#b0015) |
| [B0016 · 82–82](../../../../../tests/unit/session_exception_test.cpp#L82) | Explanatory comments or spacing. |  |
| [B0017 · 83–90](../../../../../tests/unit/session_exception_test.cpp#L83) | Callable definition: template &lt;class Action&gt; auto run_phase(std::string_view label, Action&& action) -&gt; decltype(action()) | calls action, std::runtime_error, std::string, what; returns std::forward&lt;Action&gt;(action)() · [reviewed contract](#b0017) |
| [B0018 · 91–91](../../../../../tests/unit/session_exception_test.cpp#L91) | Explanatory comments or spacing. |  |
| [B0019 · 92–92](../../../../../tests/unit/session_exception_test.cpp#L92) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0019) |
| [B0020 · 93–93](../../../../../tests/unit/session_exception_test.cpp#L93) | Explanatory comments or spacing. |  |
| [B0021 · 94–102](../../../../../tests/unit/session_exception_test.cpp#L94) | Callable definition: PhysicalPlan make_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0021) |
| [B0022 · 103–103](../../../../../tests/unit/session_exception_test.cpp#L103) | Explanatory comments or spacing. |  |
| [B0023 · 104–117](../../../../../tests/unit/session_exception_test.cpp#L104) | Callable definition: PhysicalPlan make_alias_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0023) |
| [B0024 · 118–118](../../../../../tests/unit/session_exception_test.cpp#L118) | Explanatory comments or spacing. |  |
| [B0025 · 119–124](../../../../../tests/unit/session_exception_test.cpp#L119) | Callable definition: io::InputEvent event(std::uint64_t sequence, SetOperation operation, std::int64_t value, std::string source, std::uint64_t offset) | calls n, std::move; returns {{sequence, TableId{0}, operation, {n(value)}}, · [reviewed contract](#b0025) |
| [B0026 · 125–125](../../../../../tests/unit/session_exception_test.cpp#L125) | Explanatory comments or spacing. |  |
| [B0027 · 126–128](../../../../../tests/unit/session_exception_test.cpp#L126) | Callable definition: std::string encode(const PhysicalPlan& plan, const io::InputEvent& input) | calls io::write_input_json, catalog; returns io::write_input_json(input, plan.catalog()) + @ · [reviewed contract](#b0027) |
| [B0028 · 129–129](../../../../../tests/unit/session_exception_test.cpp#L129) | Explanatory comments or spacing. |  |
| [B0029 · 130–134](../../../../../tests/unit/session_exception_test.cpp#L130) | Callable definition: std::string stream_bytes(const PhysicalPlan& plan) | calls encode, event; returns encode(plan, event(1, SetOperation::insert, 7, @ , 10)) +; growth insert · [reviewed contract](#b0029) |
| [B0030 · 135–135](../../../../../tests/unit/session_exception_test.cpp#L135) | Explanatory comments or spacing. |  |
| [B0031 · 136–148](../../../../../tests/unit/session_exception_test.cpp#L136) | Type/record definition: class OwnedStream final : public std::istringstream |  · [reviewed contract](#b0031) |
| [B0032 · 149–149](../../../../../tests/unit/session_exception_test.cpp#L149) | Explanatory comments or spacing. |  |
| [B0033 · 150–157](../../../../../tests/unit/session_exception_test.cpp#L150) | Callable definition: QuerySession::Owner make_session( PhysicalPlan plan, std::string bytes, SessionOptions options = {}, bool* stream_destroyed = nul… | calls std::move, QuerySession::create; returns QuerySession::create(std::move(plan), std::move(input),; growth make_unique · [reviewed contract](#b0033) |
| [B0034 · 158–158](../../../../../tests/unit/session_exception_test.cpp#L158) | Explanatory comments or spacing. |  |
| [B0035 · 159–164](../../../../../tests/unit/session_exception_test.cpp#L159) | Type/record definition: struct OutputImage |  · [reviewed contract](#b0035) |
| [B0036 · 165–165](../../../../../tests/unit/session_exception_test.cpp#L165) | Explanatory comments or spacing. |  |
| [B0037 · 166–171](../../../../../tests/unit/session_exception_test.cpp#L166) | Type/record definition: struct SnapshotImage |  · [reviewed contract](#b0037) |
| [B0038 · 172–172](../../../../../tests/unit/session_exception_test.cpp#L172) | Explanatory comments or spacing. |  |
| [B0039 · 173–180](../../../../../tests/unit/session_exception_test.cpp#L173) | Callable definition: SnapshotImage image(const SessionSnapshot& snapshot) | calls reserve, size, push_back, crown::storage::export_row; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0039) |
| [B0040 · 181–181](../../../../../tests/unit/session_exception_test.cpp#L181) | Explanatory comments or spacing. |  |
| [B0041 · 182–184](../../../../../tests/unit/session_exception_test.cpp#L182) | Callable definition: SnapshotImage image(const QuerySession& session) | calls snapshot; returns image(session.snapshot()) · [reviewed contract](#b0041) |
| [B0042 · 185–185](../../../../../tests/unit/session_exception_test.cpp#L185) | Explanatory comments or spacing. |  |
| [B0043 · 186–192](../../../../../tests/unit/session_exception_test.cpp#L186) | Callable definition: std::vector&lt;OutputImage&gt; take_all_output(QuerySession& session) | calls next_output, push_back, crown::storage::export_row, values; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0043) |
| [B0044 · 193–193](../../../../../tests/unit/session_exception_test.cpp#L193) | Explanatory comments or spacing. |  |
| [B0045 · 194–199](../../../../../tests/unit/session_exception_test.cpp#L194) | Callable definition: void drive_to_prepared(QuerySession& session) | calls step; 1 loop sites · [reviewed contract](#b0045) |
| [B0046 · 200–200](../../../../../tests/unit/session_exception_test.cpp#L200) | Explanatory comments or spacing. |  |
| [B0047 · 201–204](../../../../../tests/unit/session_exception_test.cpp#L201) | Callable definition: void accept_current(QuerySession& session) | calls drive_to_prepared, commit · [reviewed contract](#b0047) |
| [B0048 · 205–205](../../../../../tests/unit/session_exception_test.cpp#L205) | Explanatory comments or spacing. |  |
| [B0049 · 206–209](../../../../../tests/unit/session_exception_test.cpp#L206) | Type/record definition: struct CleanRun |  · [reviewed contract](#b0049) |
| [B0050 · 210–210](../../../../../tests/unit/session_exception_test.cpp#L210) | Explanatory comments or spacing. |  |
| [B0051 · 211–225](../../../../../tests/unit/session_exception_test.cpp#L211) | Callable definition: CleanRun run_clean(PhysicalPlan plan, std::string bytes) | calls make_session, std::move, start, begin_next; guard check(session-&gt;status().end_of_input && !session-&gt;begin_next() &&; returns result; growth insert; 1 loop sites · [reviewed contract](#b0051) |
| [B0052 · 226–226](../../../../../tests/unit/session_exception_test.cpp#L226) | Explanatory comments or spacing. |  |
| [B0053 · 227–232](../../../../../tests/unit/session_exception_test.cpp#L227) | Callable definition: io::InputProgress first_progress() | calls emplace; returns result; growth emplace · [reviewed contract](#b0053) |
| [B0054 · 233–233](../../../../../tests/unit/session_exception_test.cpp#L233) | Explanatory comments or spacing. |  |
| [B0055 · 234–239](../../../../../tests/unit/session_exception_test.cpp#L234) | Callable definition: io::InputProgress second_progress() | calls first_progress, at; returns result · [reviewed contract](#b0055) |
| [B0056 · 240–240](../../../../../tests/unit/session_exception_test.cpp#L240) | Explanatory comments or spacing. |  |
| [B0057 · 241–246](../../../../../tests/unit/session_exception_test.cpp#L241) | Callable definition: io::InputProgress full_progress() | calls second_progress, emplace; returns result; growth emplace · [reviewed contract](#b0057) |
| [B0058 · 247–247](../../../../../tests/unit/session_exception_test.cpp#L247) | Explanatory comments or spacing. |  |
| [B0059 · 248–250](../../../../../tests/unit/session_exception_test.cpp#L248) | Callable definition: SnapshotImage first_snapshot() | calls first_progress, n; returns {1, first_progress(), {{n(7)}}} · [reviewed contract](#b0059) |
| [B0060 · 251–251](../../../../../tests/unit/session_exception_test.cpp#L251) | Explanatory comments or spacing. |  |
| [B0061 · 252–254](../../../../../tests/unit/session_exception_test.cpp#L252) | Callable definition: SnapshotImage second_snapshot() | calls second_progress, n; returns {2, second_progress(), {{n(7)}, {n(8)}}} · [reviewed contract](#b0061) |
| [B0062 · 255–255](../../../../../tests/unit/session_exception_test.cpp#L255) | Explanatory comments or spacing. |  |
| [B0063 · 256–258](../../../../../tests/unit/session_exception_test.cpp#L256) | Callable definition: SnapshotImage final_snapshot() | calls full_progress, n; returns {3, full_progress(), {{n(8)}}} · [reviewed contract](#b0063) |
| [B0064 · 259–259](../../../../../tests/unit/session_exception_test.cpp#L259) | Explanatory comments or spacing. |  |
| [B0065 · 260–269](../../../../../tests/unit/session_exception_test.cpp#L260) | Callable definition: void setup_first_commit(QuerySession& session) | calls start, check, begin_next, accept_current; guard check(session.begin_next(), "session did not admit its first input");; growth insert · [reviewed contract](#b0065) |
| [B0066 · 270–270](../../../../../tests/unit/session_exception_test.cpp#L270) | Explanatory comments or spacing. |  |
| [B0067 · 271–318](../../../../../tests/unit/session_exception_test.cpp#L271) | Callable definition: void reader_close_moves_only_accepted_progress_without_allocation() | calls make_plan, encode, event, emplace; guard check(cached && cached-&gt;update.sequence == 1 &&; growth emplace, insert · [reviewed contract](#b0067) |
| [B0068 · 319–319](../../../../../tests/unit/session_exception_test.cpp#L319) | Explanatory comments or spacing. |  |
| [B0069 · 320–328](../../../../../tests/unit/session_exception_test.cpp#L320) | Callable definition: void retry_second_input(QuerySession& session, const CleanRun& clean) | calls check, begin_next, accept_current, take_all_output; guard check(session.begin_next(), "cached second input was lost after engine OOM"); · [reviewed contract](#b0069) |
| [B0070 · 329–329](../../../../../tests/unit/session_exception_test.cpp#L329) | Explanatory comments or spacing. |  |
| [B0071 · 330–378](../../../../../tests/unit/session_exception_test.cpp#L330) | Callable definition: std::size_t sweep_create_failures(const std::string& bytes) | calls make_plan, fault, QuerySession::create, std::move; guard check(destroyed,; returns failures; growth make_unique; 1 loop sites · [reviewed contract](#b0071) |
| [B0072 · 379–379](../../../../../tests/unit/session_exception_test.cpp#L379) | Explanatory comments or spacing. |  |
| [B0073 · 380–438](../../../../../tests/unit/session_exception_test.cpp#L380) | Callable definition: std::size_t sweep_begin_next_failures(const std::string& bytes, const CleanRun& clean) | calls make_session, make_plan, setup_first_commit, fault; guard check(status.committed_sequence == 1 &&; returns failures; 1 loop sites · [reviewed contract](#b0073) |
| [B0074 · 439–439](../../../../../tests/unit/session_exception_test.cpp#L439) | Explanatory comments or spacing. |  |
| [B0075 · 440–490](../../../../../tests/unit/session_exception_test.cpp#L440) | Callable definition: std::size_t sweep_retaining_step_failures(const std::string& bytes, const CleanRun& clean) | calls make_session, make_plan, setup_first_commit, check; guard check(session-&gt;begin_next(), "step sweep did not begin its second input");; returns failures; 1 loop sites · [reviewed contract](#b0075) |
| [B0076 · 491–491](../../../../../tests/unit/session_exception_test.cpp#L491) | Explanatory comments or spacing. |  |
| [B0077 · 492–550](../../../../../tests/unit/session_exception_test.cpp#L492) | Callable definition: std::size_t sweep_snapshot_failures(const std::string& bytes, const CleanRun& clean) | calls make_session, make_plan, setup_first_commit, check; guard check(session-&gt;begin_next(), "snapshot sweep did not begin its second input");; returns failures; growth emplace; 1 loop sites; source comment (unverified): // Keep one output unread so the snapshot path is exercised while a · [reviewed contract](#b0077) |
| [B0078 · 551–551](../../../../../tests/unit/session_exception_test.cpp#L551) | Explanatory comments or spacing. |  |
| [B0079 · 552–640](../../../../../tests/unit/session_exception_test.cpp#L552) | Callable definition: void commit_output_and_cleanup_are_allocation_free(const std::string& first_bytes, const std::string& second_bytes) | calls make_session, make_plan, start, check; guard check(session-&gt;begin_next(), "new-source guarded fixture did not begin");; growth insert; source comment (unverified): // Reading the last row must destroy the output epoch and release the · [reviewed contract](#b0079) |
| [B0080 · 641–641](../../../../../tests/unit/session_exception_test.cpp#L641) | Explanatory comments or spacing. |  |
| [B0081 · 642–714](../../../../../tests/unit/session_exception_test.cpp#L642) | Callable definition: void paused_drain_and_start_drain() | calls encode, make_plan, event, make_session; guard check(session-&gt;begin_next(), "drain fixture did not begin");; growth insert; source comment (unverified): // Exercise output-spool quota failure after the event has been decoded. · [reviewed contract](#b0081) |
| [B0082 · 715–715](../../../../../tests/unit/session_exception_test.cpp#L715) | Explanatory comments or spacing. |  |
| [B0083 · 716–776](../../../../../tests/unit/session_exception_test.cpp#L716) | Callable definition: void late_alias_quota_failure_retries_without_a_committed_prefix() | calls make_alias_plan, n, encode, make_alias_event; guard check(session-&gt;begin_next(), "alias quota fixture did not begin its seed");; returns io::InputEvent{{sequence, TableId{0}, SetOperation::insert,; row.values() == Row{n(1), n(2)}; growth emplace, insert · [reviewed contract](#b0083) |
| [B0084 · 777–777](../../../../../tests/unit/session_exception_test.cpp#L777) | Explanatory comments or spacing. |  |
| [B0085 · 778–829](../../../../../tests/unit/session_exception_test.cpp#L778) | Callable definition: std::size_t sweep_start_drain_failures(const std::string& bytes) | calls make_session, make_plan, setup_first_commit, check; guard check(session-&gt;begin_next(), "start_drain sweep did not begin its second event");; returns failures; 1 loop sites · [reviewed contract](#b0085) |
| [B0086 · 830–830](../../../../../tests/unit/session_exception_test.cpp#L830) | Explanatory comments or spacing. |  |
| [B0087 · 831–920](../../../../../tests/unit/session_exception_test.cpp#L831) | Callable definition: void stop_and_drop_abort_private_prefixes(const std::string& bytes) | calls make_session, make_plan, start, check; guard check(session-&gt;begin_next(), "unread-output stop fixture did not begin");; 4 loop sites · [reviewed contract](#b0087) |
| [B0088 · 921–921](../../../../../tests/unit/session_exception_test.cpp#L921) | Explanatory comments or spacing. |  |
| [B0089 · 922–950](../../../../../tests/unit/session_exception_test.cpp#L922) | Callable definition: void snapshot_rows_and_committed_output_outlive_session() | calls make_plan, encode, event, make_session; guard check(session-&gt;begin_next(), "snapshot lifetime fixture did not begin");; growth insert · [reviewed contract](#b0089) |
| [B0090 · 951–951](../../../../../tests/unit/session_exception_test.cpp#L951) | Explanatory comments or spacing. |  |
| [B0091 · 952–1094](../../../../../tests/unit/session_exception_test.cpp#L952) | Callable definition: void lifecycle_errors_and_guards() | calls encode, make_plan, event, make_session; guard check(session-&gt;status().state == SessionState::created,; returns traits_type::eof(); traits_type::to_int_type(bytes\[position\]); growth insert, make_unique; 1 loop sites · [reviewed contract](#b0091) |
| [B0092 · 1095–1097](../../../../../tests/unit/session_exception_test.cpp#L1095) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0092) |
| [B0093 · 1098–1163](../../../../../tests/unit/session_exception_test.cpp#L1098) | Callable definition: int main() | calls make_plan, stream_bytes, encode, event; guard check(clean.final_snapshot == final_snapshot() &&; returns run_clean(make_plan(), bytes); sweep_create_failures(bytes); growth insert · [reviewed contract](#b0093) |

## B0001

[Lines 1–34](../../../../../tests/unit/session_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L34:sha256:7f84296f65a6a1350af692b5036e71f209583dd0251e1d3cd266b049fb71b982
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_exception_test.cpp: include "crown/api/error.hpp", "crown/io/ingest.hpp", "crown/planner/lower.hpp", "crown/runtime/physical.hpp", "crown/runtime/session.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;thread&gt;, &lt;tuple&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 35–43](../../../../../tests/unit/session_exception_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count an intercepted ordinary-new request, apply the thread-local fail-after fault point, and obtain backing storage from malloc. |
| inputs / outputs | Accepts byte count; increments allocation_count, throws at fail_after zero, decrements positive thresholds, maps zero bytes to one for malloc, and returns pointer or throws bad_alloc. |
| invariants | The injected failure occurs before malloc; a real malloc null also becomes bad_alloc. allocation_count is increment-only and is not an assertion oracle. This directly backs ordinary throwing scalar/array new only. |
| ownership | Owns no heap result; returned raw storage is released by matching delete replacements. |
| failure | Injected and real malloc failures both throw std::bad_alloc; direct malloc callers are not intercepted. No dedicated aligned/nothrow replacement is defined; indirect library delegation is not asserted coverage. |
| cost | One counter increment/threshold branch plus one malloc for admitted requests; not bytes, MemoryAccount denials, RSS, or syscalls. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0004

[Lines 45–51](../../../../../tests/unit/session_exception_test.cpp#L45); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm or reset the thread-local fail-after seam for one lexical scope. |
| inputs / outputs | Optional point sets fail_after on construction; forbid_allocations sets it to zero; destructor resets it to -1. |
| invariants | The scope is not a nesting stack and does not reset allocation_count. |
| ownership | Owns no allocated resource; mutates thread-local scalars on the current thread. |
| failure | No exception is thrown by the noexcept operations; overlapping/nested scopes are not modeled. |
| cost | Constant scalar assignments; observes only calls that reach the replaced ordinary-new symbols. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0005

[Lines 52–53](../../../../../tests/unit/session_exception_test.cpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L53:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 54–54](../../../../../tests/unit/session_exception_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary scalar throwing global new through malloc_new. |
| inputs / outputs | Takes requested byte count; returns malloc_new result or throws bad_alloc. |
| invariants | This is the directly defined scalar throwing overload; no aligned/nothrow replacement is defined here. |
| ownership | Returned storage is paired with the test executable delete overloads. |
| failure | Propagates malloc_new bad_alloc; direct malloc and system calls are outside injection. |
| cost | One seam call; any indirect delegation from another library form is not asserted as coverage. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0007

[Lines 55–55](../../../../../tests/unit/session_exception_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary array throwing global new through malloc_new. |
| inputs / outputs | Takes requested byte count; returns malloc_new result or throws bad_alloc. |
| invariants | This is the directly defined array throwing overload; no aligned/nothrow replacement is defined here. |
| ownership | Returned storage is paired with array delete overloads. |
| failure | Propagates malloc_new bad_alloc; direct malloc and system calls are outside injection. |
| cost | One seam call; indirect library delegation is not asserted coverage. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0008

[Lines 56–56](../../../../../tests/unit/session_exception_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free scalar storage returned by the replacement allocation function. |
| inputs / outputs | Accepts raw pointer; returns void. |
| invariants | Calls std::free and is noexcept. |
| ownership | Caller transfers matching allocation storage; this function retains nothing. |
| failure | No error reporting; valid pointer/deallocation pairing is assumed. |
| cost | One free operation; not fault-injected. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0009

[Lines 57–57](../../../../../tests/unit/session_exception_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free array storage returned by the replacement allocation function. |
| inputs / outputs | Accepts raw pointer; returns void. |
| invariants | Calls std::free and is noexcept. |
| ownership | Caller transfers matching array allocation storage; retains nothing. |
| failure | No error reporting; valid pointer pairing is assumed. |
| cost | One free operation; not fault-injected. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0010

[Lines 58–58](../../../../../tests/unit/session_exception_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized scalar delete for replacement scalar allocations. |
| inputs / outputs | Accepts pointer and ignored size; returns void. |
| invariants | Calls std::free and is noexcept; size does not affect release. |
| ownership | Storage ownership is transferred to delete; no state is retained. |
| failure | No error reporting. |
| cost | One free operation; not fault-injected. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0011

[Lines 59–59](../../../../../tests/unit/session_exception_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized array delete for replacement array allocations. |
| inputs / outputs | Accepts pointer and ignored size; returns void. |
| invariants | Calls std::free and is noexcept; size does not affect release. |
| ownership | Storage ownership is transferred to delete; no state is retained. |
| failure | No error reporting. |
| cost | One free operation; not fault-injected. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0012

[Lines 60–66](../../../../../tests/unit/session_exception_test.cpp#L60); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L66:sha256:8b28c7985a28e23d57289a2c6b7140ad9ca93b886ee45d283d0263995beca077
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_exception_test.cpp: bind local aliases/name imports; require 1 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 67–69](../../../../../tests/unit/session_exception_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one exception-test assertion with a borrowed diagnostic. |
| inputs / outputs | Takes predicate and message; returns for true or throws std::runtime_error for false. |
| invariants | Catches and translates no product error. |
| ownership | Arguments are borrowed for the call; no test object is retained. |
| failure | False condition throws; message construction can allocate. |
| cost | One branch. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0015

[Lines 71–81](../../../../../tests/unit/session_exception_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
void expect_error(Action&& action, std::string_view code) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one action to throw crown::api::Error with the requested code. |
| inputs / outputs | Forwards action and compares failure.code(); returns on match. |
| invariants | Catches only Error; bad_alloc and other exceptions propagate; wrong code fails through check. |
| ownership | Action/code view are borrowed; helper retains no session. |
| failure | No matching Error or wrong code throws test runtime_error. |
| cost | One action call and exact code comparison. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0017

[Lines 83–90](../../../../../tests/unit/session_exception_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
auto run_phase(std::string_view label, Action&& action) -> decltype(action()) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one labeled phase and wrap std::exception with phase context. |
| inputs / outputs | Takes borrowed label and forwarded action; returns action result. |
| invariants | Catches std::exception only; non-standard exceptions propagate. |
| ownership | Action executes in caller-owned context; return follows action type. |
| failure | Wrapped diagnostic construction can throw; original exception is not preserved as nested exception. |
| cost | One action invocation and catch-path label formatting. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0019

[Lines 92–92](../../../../../tests/unit/session_exception_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an int64 Value for exception fixtures. |
| inputs / outputs | Takes integer and returns Value by value. |
| invariants | Preserves the supplied value. |
| ownership | Owns only the scalar value. |
| failure | No error translation. |
| cost | Constant fixture conversion. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0021

[Lines 94–102](../../../../../tests/unit/session_exception_test.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the unary R(x) plan used by session exception sweeps. |
| inputs / outputs | No arguments; returns PhysicalPlan over catalog R(x). |
| invariants | One native atom projects x; catalog/query/tree agree. |
| ownership | Returned plan owns metadata; input/session are separate. |
| failure | Lowering errors propagate. |
| cost | One fixed fixture lowering. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0023

[Lines 104–117](../../../../../tests/unit/session_exception_test.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_alias_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a two-alias self-join plan producing two result rows for the retry quota fixture. |
| inputs / outputs | No arguments; returns PhysicalPlan over E(x,z) with forward/reverse aliases. |
| invariants | The generalized intersection joins aliases; cross input order enables two distinct projected pairs. |
| ownership | Returned plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed fixture lowering. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0025

[Lines 119–124](../../../../../tests/unit/session_exception_test.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::InputEvent event(std::uint64_t sequence, SetOperation operation,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one sequenced physical input event with source name and offset. |
| inputs / outputs | Accepts values and moves source string into optional SourcePosition; returns InputEvent. |
| invariants | The event carries one int64 row and caller-supplied sequence/operation. |
| ownership | Returned event owns row and source name. |
| failure | No validation occurs here; later encoder/reader handles validity. |
| cost | Plain fixture construction. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0027

[Lines 126–128](../../../../../tests/unit/session_exception_test.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string encode(const PhysicalPlan& plan, const io::InputEvent& input) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one physical event as a JSONL line. |
| inputs / outputs | Takes plan/input references; returns write_input_json output plus newline. |
| invariants | Encoding uses plan catalog and preserves supplied event bytes/position semantically. |
| ownership | Inputs are borrowed; returned string owns encoded bytes. |
| failure | Encoder/allocation errors propagate. |
| cost | One event encoding. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0029

[Lines 130–134](../../../../../tests/unit/session_exception_test.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string stream_bytes(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the fixed three-event JSONL stream used by clean and failure runs. |
| inputs / outputs | Takes plan; returns owned text for insert 7 at source-A-long:10, insert 8 at :20, erase 7 at source-B-long:50. |
| invariants | Sequence numbers are 1,2,3; exact values/positions bind expected progress. |
| ownership | Returned string owns bytes. |
| failure | Encoder/allocation errors propagate. |
| cost | Serializes three finite records. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0031

[Lines 136–148](../../../../../tests/unit/session_exception_test.cpp#L136); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class OwnedStream final : public std::istringstream {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark destruction of an owned istringstream in transfer/cleanup tests. |
| inputs / outputs | Constructs from bytes and borrowed marker; destructor sets marker true. |
| invariants | The marker is updated exactly when stream object is destroyed. |
| ownership | Owns bytes; borrows marker which must outlive stream. |
| failure | No custom exception handling; destructor satisfies stream destructor contract. |
| cost | One stream fixture. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0033

[Lines 150–157](../../../../../tests/unit/session_exception_test.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner make_session(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a QuerySession owning an OwnedStream and optional destruction marker. |
| inputs / outputs | Takes plan, bytes, options and optional marker pointer; returns QuerySession::Owner. |
| invariants | Input stream is transferred to QuerySession::create; optional marker is borrowed. |
| ownership | Owner holds session; session owns input stream and runtime. |
| failure | Factory failures propagate; on transferred-stream construction failure the tests assert destruction. |
| cost | Creates stream and session; cost is fixture initialization, not a runtime benchmark. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0035

[Lines 159–164](../../../../../tests/unit/session_exception_test.cpp#L159); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OutputImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store an owned projection of one returned SignedResult for clean-run comparison. |
| inputs / outputs | Fields hold ordinal, operation and Row values. |
| invariants | Image equality compares the visible signed output values, not borrowed tuple references. |
| ownership | Row is copied/owned by OutputImage. |
| failure | No custom failure path. |
| cost | Plain value object. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0037

[Lines 166–171](../../../../../tests/unit/session_exception_test.cpp#L166); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SnapshotImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store an owned projection of committed snapshot sequence, progress, and rows. |
| inputs / outputs | Fields are populated by image helpers. |
| invariants | Image comparison checks committed rows/progress after the source snapshot object may expire. |
| ownership | Owns its InputProgress and row values. |
| failure | Copy/allocation errors propagate. |
| cost | Copies fixture-sized snapshot content. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0039

[Lines 173–180](../../../../../tests/unit/session_exception_test.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SnapshotImage image(const SessionSnapshot& snapshot) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a SessionSnapshot into comparable owning sequence/progress/row values. |
| inputs / outputs | Takes snapshot by const reference; returns SnapshotImage. |
| invariants | Exports every tuple’s values; no SessionRows reference escapes. |
| ownership | Snapshot is borrowed during conversion; returned rows/progress are owned copies. |
| failure | Export/allocation errors propagate. |
| cost | Linear in snapshot row count and row width. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0041

[Lines 182–184](../../../../../tests/unit/session_exception_test.cpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SnapshotImage image(const QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain a session snapshot and convert it to an owned image. |
| inputs / outputs | Takes const session reference; returns SnapshotImage. |
| invariants | Delegates to QuerySession::snapshot then image(SessionSnapshot). |
| ownership | Temporary snapshot owns rows through conversion; returned image owns exported values. |
| failure | Session snapshot and conversion errors propagate. |
| cost | Creates a snapshot and copies fixture rows/progress. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0043

[Lines 186–192](../../../../../tests/unit/session_exception_test.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<OutputImage> take_all_output(QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain all current public output into owned OutputImage values. |
| inputs / outputs | Takes mutable session; returns vector in next_output order. |
| invariants | Each image copies ordinal/op/row; empty optional terminates the drain. |
| ownership | SignedResult is returned by value; vector images own row copies after session/output destruction. |
| failure | API/export/vector allocation errors propagate. |
| cost | Reads all retained output rows and copies each row. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0045

[Lines 194–199](../../../../../tests/unit/session_exception_test.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void drive_to_prepared(QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive a session from pending to prepared with a finite progress guard. |
| inputs / outputs | Takes mutable session; returns when status.phase is prepared. |
| invariants | Counts step calls and fails if count reaches its guard; it is not a wall-time bound. |
| ownership | Session retains pending token privately. |
| failure | Session errors propagate; test guard throws runtime_error. |
| cost | Bounded call loop up to fixture guard. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0047

[Lines 201–204](../../../../../tests/unit/session_exception_test.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void accept_current(QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit the current prepared event in one helper. |
| inputs / outputs | Takes mutable session; calls commit and returns void. |
| invariants | Assumes the caller established a prepared phase; it does not validate setup separately. |
| ownership | Session owns its token and publishes through its API. |
| failure | Commit errors propagate. |
| cost | One public API call. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0049

[Lines 206–209](../../../../../tests/unit/session_exception_test.cpp#L206); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CleanRun {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle clean-run outputs and final snapshot image for differential retry comparison. |
| inputs / outputs | Fields own vector&lt;OutputImage&gt; and SnapshotImage. |
| invariants | The clean result is a separate session run used only as comparator. |
| ownership | Owns copies; no session or stream is retained. |
| failure | Copy/allocation errors propagate. |
| cost | Plain comparison value. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0051

[Lines 211–225](../../../../../tests/unit/session_exception_test.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CleanRun run_clean(PhysicalPlan plan, std::string bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all three physical events in a separate clean session and capture outputs/snapshots. |
| inputs / outputs | Takes plan and JSONL bytes by value; returns CleanRun. |
| invariants | Each input is begun, stepped, committed and drained; final state has sequence 3, source offsets 20 and 50. |
| ownership | Clean session owns its stream/runtime; CleanRun copies all output and snapshot data. |
| failure | API/encoding/allocation failures propagate. |
| cost | Runs three finite epochs as a reference comparison; it is not a second same-owner retry. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0053

[Lines 227–232](../../../../../tests/unit/session_exception_test.cpp#L227); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::InputProgress first_progress() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return expected accepted progress after the first committed input. |
| inputs / outputs | No arguments; returns sequence 1 and source-A-long offset 10. |
| invariants | Expected map is independent copied fixture data. |
| ownership | Returned map owns source-name key and scalar offset. |
| failure | Allocation errors propagate. |
| cost | Small fixed progress value. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0055

[Lines 234–239](../../../../../tests/unit/session_exception_test.cpp#L234); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::InputProgress second_progress() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return expected progress after the second committed input. |
| inputs / outputs | No arguments; returns sequence 2 and source-A-long offset 20. |
| invariants | Does not include the later source-B-long event. |
| ownership | Returned progress owns its map. |
| failure | Allocation errors propagate. |
| cost | Small fixed progress value. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0057

[Lines 241–246](../../../../../tests/unit/session_exception_test.cpp#L241); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::InputProgress full_progress() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return expected final progress after all three committed inputs. |
| inputs / outputs | No arguments; returns sequence 3 and source positions A:20 and B:50. |
| invariants | Sequence and both source offsets match the JSONL fixture. |
| ownership | Returned progress owns its map. |
| failure | Allocation errors propagate. |
| cost | Small fixed progress value. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0059

[Lines 248–250](../../../../../tests/unit/session_exception_test.cpp#L248); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SnapshotImage first_snapshot() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the expected snapshot image after event one. |
| inputs / outputs | No arguments; returns sequence 1, first_progress, and row 7. |
| invariants | It records the expected committed prefix, not private input state. |
| ownership | Returned image owns progress/rows. |
| failure | Allocation errors propagate. |
| cost | Small fixed fixture value. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0061

[Lines 252–254](../../../../../tests/unit/session_exception_test.cpp#L252); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SnapshotImage second_snapshot() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the expected snapshot image after event two. |
| inputs / outputs | No arguments; returns sequence 2, second_progress, and rows 7 and 8. |
| invariants | Rows are the set result after two inserts. |
| ownership | Returned image owns values. |
| failure | Allocation errors propagate. |
| cost | Small fixture value. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0063

[Lines 256–258](../../../../../tests/unit/session_exception_test.cpp#L256); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SnapshotImage final_snapshot() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the expected snapshot after insert 7, insert 8, and erase 7. |
| inputs / outputs | No arguments; returns sequence 3, full_progress, and row 8. |
| invariants | Represents committed final state and all accepted source positions. |
| ownership | Returned image owns values. |
| failure | Allocation errors propagate. |
| cost | Small fixture value. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp) |

## B0065

[Lines 260–269](../../../../../tests/unit/session_exception_test.cpp#L260); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void setup_first_commit(QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit the first event before arming a later failure sweep. |
| inputs / outputs | Takes mutable session; starts it, begins event 1, steps to prepared, commits, and drains its output. |
| invariants | Failure injections in callers therefore target the second event or later operation; prior committed prefix is stable. |
| ownership | Session owns input/runtime; drained output images are temporary. |
| failure | Setup/API errors propagate. |
| cost | One fixture epoch before fault arming. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0067

[Lines 271–318](../../../../../tests/unit/session_exception_test.cpp#L271); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reader_close_moves_only_accepted_progress_without_allocation() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify EventReader::close moves only accepted progress and releases decoder ownership without a replacement-new request in the guarded close path. |
| inputs / outputs | Constructs reader over borrowed OwnedStream, peeks an unacknowledged event, then guards close/acknowledge/second close with fail_after zero. |
| invariants | Peek caches source new-source-long:10 while accepted progress remains old-source-long:3; close exports only accepted progress; acknowledge after close is no-op; stream survives reader object lifetime. The guard observes the ordinary-new replacement seam only. |
| ownership | Reader borrows stream; reader close moves its progress and drops decoder/cache; stream owner outlives the reader until its own destruction. |
| failure | Reader errors after close must be invalid_input_reader; any intercepted ordinary-new request throws bad_alloc. Direct malloc/system/account-denial paths are not injected; no aligned/nothrow replacements are defined and delegation is not asserted coverage. |
| cost | Checks one borrowed reader and close path; no general no-allocation claim. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp) |

## B0069

[Lines 320–328](../../../../../tests/unit/session_exception_test.cpp#L320); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retry_second_input(QuerySession& session, const CleanRun& clean) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retry event two on the same live session owner and compare it with the separate clean run. |
| inputs / outputs | Takes mutable session and borrowed CleanRun; begins cached event 2, drains to prepared, commits, then compares output/snapshot. |
| invariants | The failure/abort path must preserve old state so this same QuerySession can accept the cached decoded input; clean is only an independent expected-value run. |
| ownership | Session retains its stream/runtime; CleanRun owns expected row images. |
| failure | API/output mismatch fails by runtime_error; session errors propagate. |
| cost | One retry event and row comparisons. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0071

[Lines 330–378](../../../../../tests/unit/session_exception_test.cpp#L330); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep_create_failures(const std::string& bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary-new fail-after points around QuerySession construction, using a fresh plan/stream per attempt. |
| inputs / outputs | Takes encoded bytes; constructs fresh owner at each point and returns count of caught bad_alloc attempts. |
| invariants | On failure the transferred stream must be destroyed; first success starts created/ready at seq0 with empty progress/snapshot; max 8192 points. This is fresh-construction behavior, not same-owner retry. |
| ownership | Each attempt owns a new stream/session transfer; success owner is reset before return. |
| failure | Catches bad_alloc at factory; test assertion fails if no failure point or guard exhaustion. The seam counts calls reaching ordinary throwing scalar/array new; direct allocator/syscall/account denial is not covered. |
| cost | Up to 8192 fresh construction attempts; instrumentation is request-based, not byte/RSS accounting. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0073

[Lines 380–438](../../../../../tests/unit/session_exception_test.cpp#L380); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep_begin_next_failures(const std::string& bytes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep begin_next fault points after event one and separate sticky parser failures from retryable engine-begin failures. |
| inputs / outputs | Takes bytes and clean comparator; each point creates fresh owner, commits first event, and arms around begin_next for event two. |
| invariants | Parser bad_alloc makes input_failed sticky and later begin returns input_failed; engine-begin bad_alloc leaves seq1/progress/snapshot stable and same owner retries cached event through retry_second_input; first success publishes expected event. |
| ownership | Each sweep attempt owns its own session; retry remains on that attempt’s live owner; clean run is separate comparator. |
| failure | Catches bad_alloc only in armed region; unexpected errors propagate. Seam covers ordinary-new replacements only, not direct malloc/system/account denial; no dedicated aligned/nothrow replacements and no delegation claim. |
| cost | At most 8192 fresh setup+begin attempts; allocation counter counts intercepted requests, not bytes or time. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0075

[Lines 440–490](../../../../../tests/unit/session_exception_test.cpp#L440); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep_retaining_step_failures(const std::string& bytes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep retaining step/preparation ordinary-new failures after event two begins. |
| inputs / outputs | Takes bytes and clean comparator; for each point creates fresh session, commits event1, arms during drive_to_prepared(event2), returns number of failed points. |
| invariants | On bad_alloc, private token is aborted, session returns ready/running with committed seq1 and old snapshot/progress; same owner retries cached event2; first success commits exact clean output/snapshot. |
| ownership | Each attempt owns a session; failed attempt retains cached input for retry on that same owner; clean comparator is separate. |
| failure | Catches bad_alloc in armed step region; errors/assertion failures propagate. Direct malloc/system/account-limit failures are outside seam; aligned/nothrow indirect delegation is not asserted coverage. |
| cost | Bounded to 16384 fresh attempts and step calls; no CPU-time or total heap bound. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0077

[Lines 492–550](../../../../../tests/unit/session_exception_test.cpp#L492); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep_snapshot_failures(const std::string& bytes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep snapshot-copy failures while one committed output row remains unread. |
| inputs / outputs | Takes bytes and clean comparator; each attempt commits three events, consumes prior outputs, leaves event3 output unread, and arms around snapshot(). |
| invariants | A failed snapshot leaves committed sequence3, full progress/rows, and unread output unchanged; successful copy also leaves output unread; row quota failure does not alter session/output. |
| ownership | Session owns live runtime and output epoch; copied SessionSnapshot owns its rows; comparator owns expected images. |
| failure | Catches bad_alloc only around snapshot copy; expected resource_limit/output_pending codes are checked. Seam is ordinary-new only and does not inject allocator syscalls or MemoryAccount denials. |
| cost | Up to 8192 full fixture setups and one snapshot each; row copying is fixture-sized, not timing evidence. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0079

[Lines 552–640](../../../../../tests/unit/session_exception_test.cpp#L552); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void commit_output_and_cleanup_are_allocation_free(const std::string& first_bytes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard commit, output retrieval and selected stop/drop cleanup against calls through replaced ordinary new, while checking committed values and output-lease release. |
| inputs / outputs | Takes two JSONL prefixes; guards commit/next_output/stop in one fresh-source case, drop/reset, and commit/next_output for an existing-source case; a third case guards empty-output commit. |
| invariants | The seam fails any request reaching replaced ordinary throwing scalar/array new during guarded expressions; assertion checks source progress, committed snapshots, output values, and ability to admit next event after output exhaustion. It does not cover all allocation APIs. |
| ownership | Returned SignedResult owns row values beyond session drop; session owns output Epoch until exhausted/discarded; snapshots own/shared-own committed rows. |
| failure | Any seam request throws bad_alloc; mismatches throw runtime_error. Direct malloc/system/account denial is not injected; no dedicated aligned/nothrow replacement or delegation guarantee. |
| cost | A few guarded API sequences plus fixture setup/output reads outside some guarded scopes; not a global no-allocation proof. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0081

[Lines 642–714](../../../../../tests/unit/session_exception_test.cpp#L642); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void paused_drain_and_start_drain() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check pause, start_drain and drain semantics under zero output quota and retry a quota-failed cached event. |
| inputs / outputs | No arguments; runs two zero-spool sessions, first paused then drained, second quota-fails after decode then retries. |
| invariants | Paused drain commits only current event while admission remains paused; start_drain disables retention; quota failure does not acknowledge or parser-poison; same owner retries cached event and commits snapshot/progress. |
| ownership | Each session owns input/runtime; snapshots are copied row values. |
| failure | Checks resource_limit and lifecycle state; unexpected errors propagate. This is quota failure, not malloc/ordinary-new fault injection. |
| cost | Two bounded one-event session fixtures; no durable sink or WAL is enabled. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md) |

## B0083

[Lines 716–776](../../../../../tests/unit/session_exception_test.cpp#L716); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void late_alias_quota_failure_retries_without_a_committed_prefix() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Force an alias join to exceed spool row quota, then retry the entire cached event with output retention disabled. |
| inputs / outputs | No arguments; creates a two-event self-join and row limit1; event2 generates two answer rows. |
| invariants | Quota error leaves prior seq1/progress/snapshot unchanged and no partial output prefix; retry uses same session owner/cache, commits seq2 and both expected rows. |
| ownership | Session owns stream/runtime; snapshot row collection owns its rows. |
| failure | Only resource_limit is accepted for quota failure; other errors propagate. This is a logical output-quota seam, not allocation-fault or MemoryAccount denial. |
| cost | Two physical events and two join outputs; fixture checks cardinality/content, not timing. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0085

[Lines 778–829](../../../../../tests/unit/session_exception_test.cpp#L778); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep_start_drain_failures(const std::string& bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary-new fail-after points around start_drain plus drain for a pending second event. |
| inputs / outputs | Takes bytes; each attempt creates a fresh session with event1 committed and event2 partially stepped, then arms around start_drain/drain. |
| invariants | Failure retains committed seq1, progress and snapshot, leaves decoded event retryable on same owner; retry commits seq2 with no retained output; max 8192 points. |
| ownership | Per-attempt session owns stream/runtime; cached event remains owned by its reader/engine state. |
| failure | Catches bad_alloc in guarded region only; API/assertion failures propagate. Direct malloc/system/account denial is outside seam; no dedicated aligned/nothrow replacements or delegation claim. |
| cost | At most 8192 fresh setups plus retry for failed points; no time bound. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0087

[Lines 831–920](../../../../../tests/unit/session_exception_test.cpp#L831); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stop_and_drop_abort_private_prefixes(const std::string& bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check stop/drop discard unread output or abort private prefixes while preserving only committed state/progress. |
| inputs / outputs | Takes bytes; tests unread-output stop and stop/drop at zero or one private step, with guards around selected cleanup operations. |
| invariants | Stop retains committed snapshot/progress but clears unread output and destroys owned input; private event is not acknowledged; drop leaves status tombstone and rejects progress/snapshot; guarded seam checks only ordinary-new requests. |
| ownership | Session retains facade after stop/drop; stream destruction marker records input release; caller-held values own their content. |
| failure | Expected terminal errors are checked; guarded ordinary-new request becomes bad_alloc. Direct allocator/system/account paths are not faulted. |
| cost | Finite cleanup matrix over two private prefixes and one unread output case. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0089

[Lines 922–950](../../../../../tests/unit/session_exception_test.cpp#L922); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void snapshot_rows_and_committed_output_outlive_session() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a held SessionSnapshot and returned SignedResult retain their row values after session drop. |
| inputs / outputs | No arguments; commits fixture row, copies snapshot and output, drops owner, then inspects held values. |
| invariants | Snapshot contains row 7 and sequence/progress; output contains owned tuple row 7 after runtime destruction. |
| ownership | Snapshot and SignedResult are returned owning values; they do not borrow session storage for their row values. |
| failure | Session/snapshot/output errors propagate; assertion mismatch fails test. |
| cost | One row and one output lease fixture; no sink or durability path. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md) |

## B0091

[Lines 952–1094](../../../../../tests/unit/session_exception_test.cpp#L952); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lifecycle_errors_and_guards() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check lifecycle error precedence, creator-thread ownership, and stream reentrancy against exact error codes. |
| inputs / outputs | No arguments; creates sessions across states, worker-thread call, and custom/reentrant paths. |
| invariants | Wrong-thread rejection precedes mutable state; busy reentry is detected; created/paused/stopped/dropped API errors match the session contract. |
| ownership | Each Owner controls session lifetime; worker and callback borrow only during bounded call; no concurrent session ownership is transferred. |
| failure | Expected crown::api::Error codes are required; check reports mismatches. |
| cost | Finite state/error matrix plus one thread and one stream callback; no synchronization/performance claim. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md) |

## B0092

[Lines 1095–1097](../../../../../tests/unit/session_exception_test.cpp#L1095); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1095-L1097:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0093

[Lines 1098–1163](../../../../../tests/unit/session_exception_test.cpp#L1098); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run clean comparison, allocation-failure sweeps, quota/retry and lifecycle fixtures. |
| inputs / outputs | Receives process arguments implicitly; constructs fixture bytes, invokes selected tests and prints counters. |
| invariants | Failure scopes arm only around specific APIs; helper names mentioning allocation do not broaden the seam; no journal, recovery, local sink or R2 nullable aggregate is exercised. |
| ownership | All test/session objects remain scoped to main and called routines. |
| failure | Catches std::exception, resets fail_after, prints diagnostic and returns1; otherwise prints success and returns0. |
| cost | Runs finite fault-point loops with per-sweep caps; no build/test result is asserted by this contract review. |
| Design | [tests/unit/session_exception_test.cpp](../../../../../tests/unit/session_exception_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md) |
