# `tests/unit/window_test.cpp` — block usage map

[Source](../../../../../tests/unit/window_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `0122d2073251765bcc4c8d0597150aa082327205b165296a476c2556353c47e8`. 1075 lines partitioned into 95 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–30](../../../../../tests/unit/window_test.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 31–33](../../../../../tests/unit/window_test.cpp#L31) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 34–34](../../../../../tests/unit/window_test.cpp#L34) | Explanatory comments or spacing. |  |
| [B0004 · 35–46](../../../../../tests/unit/window_test.cpp#L35) | Callable definition: template &lt;class Action&gt; void expect_code(Action&& action, std::string_view code, const std::string& label) | calls check, code, std::string, std::runtime_error; guard check(failure.code() == code, · [reviewed contract](#b0004) |
| [B0005 · 47–47](../../../../../tests/unit/window_test.cpp#L47) | Explanatory comments or spacing. |  |
| [B0006 · 48–55](../../../../../tests/unit/window_test.cpp#L48) | Callable definition: template &lt;class Action&gt; void run_case(const std::string& label, Action&& action) | calls std::runtime_error, what · [reviewed contract](#b0006) |
| [B0007 · 56–56](../../../../../tests/unit/window_test.cpp#L56) | Explanatory comments or spacing. |  |
| [B0008 · 57–57](../../../../../tests/unit/window_test.cpp#L57) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0008) |
| [B0009 · 58–58](../../../../../tests/unit/window_test.cpp#L58) | Explanatory comments or spacing. |  |
| [B0010 · 59–67](../../../../../tests/unit/window_test.cpp#L59) | Callable definition: PhysicalPlan unary_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0010) |
| [B0011 · 68–68](../../../../../tests/unit/window_test.cpp#L68) | Explanatory comments or spacing. |  |
| [B0012 · 69–81](../../../../../tests/unit/window_test.cpp#L69) | Callable definition: PhysicalPlan projected_pair_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0012) |
| [B0013 · 82–82](../../../../../tests/unit/window_test.cpp#L82) | Explanatory comments or spacing. |  |
| [B0014 · 83–100](../../../../../tests/unit/window_test.cpp#L83) | Callable definition: PhysicalPlan self_join_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0014) |
| [B0015 · 101–101](../../../../../tests/unit/window_test.cpp#L101) | Explanatory comments or spacing. |  |
| [B0016 · 102–116](../../../../../tests/unit/window_test.cpp#L102) | Callable definition: PhysicalPlan two_relation_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0016) |
| [B0017 · 117–117](../../../../../tests/unit/window_test.cpp#L117) | Explanatory comments or spacing. |  |
| [B0018 · 118–134](../../../../../tests/unit/window_test.cpp#L118) | Callable definition: PhysicalPlan exists_plan() | calls frontend::bind_sql, std::runtime_error, frontend::normalize_sql, std::move; returns planner::lower_normalized(program, tree) · [reviewed contract](#b0018) |
| [B0019 · 135–135](../../../../../tests/unit/window_test.cpp#L135) | Explanatory comments or spacing. |  |
| [B0020 · 136–138](../../../../../tests/unit/window_test.cpp#L136) | Callable definition: io::SourcePosition source_position(std::uint64_t offset) | calls ; returns io::SourcePosition{@ , offset} · [reviewed contract](#b0020) |
| [B0021 · 139–139](../../../../../tests/unit/window_test.cpp#L139) | Explanatory comments or spacing. |  |
| [B0022 · 140–147](../../../../../tests/unit/window_test.cpp#L140) | Callable definition: io::WindowCommand insert_command(std::uint64_t sequence, std::uint64_t label, TableId table, Row values, std::uint64_t timestamp,… | calls std::move, source_position; returns {sequence, io::WindowInsert{label, table, std::move(values), timestamp}, · [reviewed contract](#b0022) |
| [B0023 · 148–148](../../../../../tests/unit/window_test.cpp#L148) | Explanatory comments or spacing. |  |
| [B0024 · 149–155](../../../../../tests/unit/window_test.cpp#L149) | Callable definition: io::WindowCommand withdraw_command(std::uint64_t sequence, std::uint64_t label, std::optional&lt;std::uint64_t&gt; offset = {}) | calls source_position; returns {sequence, io::WindowWithdraw{label}, · [reviewed contract](#b0024) |
| [B0025 · 156–156](../../../../../tests/unit/window_test.cpp#L156) | Explanatory comments or spacing. |  |
| [B0026 · 157–163](../../../../../tests/unit/window_test.cpp#L157) | Callable definition: io::WindowCommand watermark_command(std::uint64_t sequence, std::uint64_t watermark, std::optional&lt;std::uint64_t&gt; offset = {}) | calls source_position; returns {sequence, io::AdvanceWatermark{watermark}, · [reviewed contract](#b0026) |
| [B0027 · 164–164](../../../../../tests/unit/window_test.cpp#L164) | Explanatory comments or spacing. |  |
| [B0028 · 165–172](../../../../../tests/unit/window_test.cpp#L165) | Callable definition: WindowOptions window_options(std::vector&lt;TableId&gt; tables, std::uint64_t width, WindowFifoPolicy fifo = WindowFifoPolicy::global) | calls std::move; returns result · [reviewed contract](#b0028) |
| [B0029 · 173–173](../../../../../tests/unit/window_test.cpp#L173) | Explanatory comments or spacing. |  |
| [B0030 · 174–181](../../../../../tests/unit/window_test.cpp#L174) | Type/record definition: struct ModelLabel |  · [reviewed contract](#b0030) |
| [B0031 · 182–182](../../../../../tests/unit/window_test.cpp#L182) | Explanatory comments or spacing. |  |
| [B0032 · 183–189](../../../../../tests/unit/window_test.cpp#L183) | Type/record definition: struct ModelActive |  · [reviewed contract](#b0032) |
| [B0033 · 190–190](../../../../../tests/unit/window_test.cpp#L190) | Explanatory comments or spacing. |  |
| [B0034 · 191–201](../../../../../tests/unit/window_test.cpp#L191) | Type/record definition: struct Oracle |  · [reviewed contract](#b0034) |
| [B0035 · 202–202](../../../../../tests/unit/window_test.cpp#L202) | Explanatory comments or spacing. |  |
| [B0036 · 203–206](../../../../../tests/unit/window_test.cpp#L203) | Type/record definition: struct PlannedStep |  · [reviewed contract](#b0036) |
| [B0037 · 207–207](../../../../../tests/unit/window_test.cpp#L207) | Explanatory comments or spacing. |  |
| [B0038 · 208–213](../../../../../tests/unit/window_test.cpp#L208) | Callable definition: std::size_t count_labels(const Oracle& oracle, TableId table, const Row& row) | calls std::count_if, begin, end; returns static_cast&lt;std::size_t&gt;(std::count_if(oracle.labels.begin(), oracle.labels.end(),; label.table == … · [reviewed contract](#b0038) |
| [B0039 · 214–214](../../../../../tests/unit/window_test.cpp#L214) | Explanatory comments or spacing. |  |
| [B0040 · 215–221](../../../../../tests/unit/window_test.cpp#L215) | Callable definition: std::uint64_t count_id_for(const Oracle& oracle, TableId table, const Row& row) | calls std::find_if, begin, end; returns label.table == table && label.values == row; found == oracle.labels.end() ? 0 : found-&gt;count_id · [reviewed contract](#b0040) |
| [B0041 · 222–222](../../../../../tests/unit/window_test.cpp#L222) | Explanatory comments or spacing. |  |
| [B0042 · 223–230](../../../../../tests/unit/window_test.cpp#L223) | Callable definition: void add_physical(Oracle& oracle, TableId table, SetOperation operation, const Row& row, std::optional&lt;PhysicalSetUpdate&gt;& update) | calls emplace, at, insert, erase; growth emplace, insert · [reviewed contract](#b0042) |
| [B0043 · 231–231](../../../../../tests/unit/window_test.cpp#L231) | Explanatory comments or spacing. |  |
| [B0044 · 232–239](../../../../../tests/unit/window_test.cpp#L232) | Callable definition: void complete_command(Oracle& oracle, const io::WindowCommand& command) | calls  · [reviewed contract](#b0044) |
| [B0045 · 240–240](../../../../../tests/unit/window_test.cpp#L240) | Explanatory comments or spacing. |  |
| [B0046 · 241–360](../../../../../tests/unit/window_test.cpp#L241) | Callable definition: std::vector&lt;PlannedStep&gt; plan_independently( const Oracle& before, const io::WindowCommand& command) | calls count_labels, count_id_for, add_physical, push_back; returns result; label.id == id; growth emplace_back, insert, push_back; 5 loop sites; source comment (unverified): // Compare the entire timestamp-selected order against the insertion-list · [reviewed contract](#b0046) |
| [B0047 · 361–361](../../../../../tests/unit/window_test.cpp#L361) | Explanatory comments or spacing. |  |
| [B0048 · 362–372](../../../../../tests/unit/window_test.cpp#L362) | Callable definition: WindowProgress expected_progress(const Oracle& oracle) | calls ; returns result · [reviewed contract](#b0048) |
| [B0049 · 373–373](../../../../../tests/unit/window_test.cpp#L373) | Explanatory comments or spacing. |  |
| [B0050 · 374–433](../../../../../tests/unit/window_test.cpp#L374) | Callable definition: void compare_canonical(QuerySession& session, const Oracle& oracle, const std::string& label) | calls window_state, check, has_value, push_back; guard check(actual.has_value(), label + ": session omitted canonical window state");; growth emplace, emplace_back, push_back; 4 loop sites · [reviewed contract](#b0050) |
| [B0051 · 434–434](../../../../../tests/unit/window_test.cpp#L434) | Explanatory comments or spacing. |  |
| [B0052 · 435–446](../../../../../tests/unit/window_test.cpp#L435) | Callable definition: std::set&lt;SignedKey&gt; collect_output(QuerySession& session, const std::string& label) | calls next_output, check, emplace, crown::storage::export_row; guard check(record-&gt;ordinal == ++ordinal,; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0052) |
| [B0053 · 447–447](../../../../../tests/unit/window_test.cpp#L447) | Explanatory comments or spacing. |  |
| [B0054 · 448–453](../../../../../tests/unit/window_test.cpp#L448) | Callable definition: std::set&lt;SignedKey&gt; reference_delta(const CommittedReferenceEpoch& epoch) | calls emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0054) |
| [B0055 · 454–454](../../../../../tests/unit/window_test.cpp#L454) | Explanatory comments or spacing. |  |
| [B0056 · 455–460](../../../../../tests/unit/window_test.cpp#L455) | Callable definition: Query exists_source_query() | calls ; returns Query{{{@ , ScalarType::int64}},; source comment (unverified): // This physical R(x) query yields one nullary row for nonempty R. The SQL · [reviewed contract](#b0056) |
| [B0057 · 461–461](../../../../../tests/unit/window_test.cpp#L461) | Explanatory comments or spacing. |  |
| [B0058 · 462–464](../../../../../tests/unit/window_test.cpp#L462) | Callable definition: Query independent_query(const PhysicalPlan& plan, bool sql_exists_wrapper) | calls exists_source_query, query; returns sql_exists_wrapper ? exists_source_query() : plan.query() · [reviewed contract](#b0058) |
| [B0059 · 465–465](../../../../../tests/unit/window_test.cpp#L465) | Explanatory comments or spacing. |  |
| [B0060 · 466–468](../../../../../tests/unit/window_test.cpp#L466) | Callable definition: Relation sql_exists_rows(const Relation& nullary_answer) | calls empty; returns Relation{Row{Value{!nullary_answer.empty()}}} · [reviewed contract](#b0060) |
| [B0061 · 469–469](../../../../../tests/unit/window_test.cpp#L469) | Explanatory comments or spacing. |  |
| [B0062 · 470–478](../../../../../tests/unit/window_test.cpp#L470) | Callable definition: std::set&lt;SignedKey&gt; signed_difference(const Relation& before, const Relation& after) | calls contains, emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0062) |
| [B0063 · 479–479](../../../../../tests/unit/window_test.cpp#L479) | Explanatory comments or spacing. |  |
| [B0064 · 480–510](../../../../../tests/unit/window_test.cpp#L480) | Callable definition: void compare_snapshot(QuerySession& session, const PhysicalPlan& plan, const reference::Session& reference_session, const Oracle&… | calls snapshot, check, layout, same_token; guard check(tuple.layout().same_token(snapshot.layout),; growth insert; 1 loop sites · [reviewed contract](#b0064) |
| [B0065 · 511–519](../../../../../tests/unit/window_test.cpp#L511) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0065) |
| [B0066 · 520–539](../../../../../tests/unit/window_test.cpp#L520) | Callable definition: Harness(PhysicalPlan value, WindowOptions windows, Database initial = {}, bool wrap_sql_exists = false) : plan(std::move(value)),… | calls plan, std::move, options, sql_exists_wrapper; growth make_unique, resize · [reviewed contract](#b0066) |
| [B0067 · 540–540](../../../../../tests/unit/window_test.cpp#L540) | Explanatory comments or spacing. |  |
| [B0068 · 541–549](../../../../../tests/unit/window_test.cpp#L541) | Callable definition: void enqueue(const std::vector&lt;io::WindowCommand&gt;& commands) | calls reserve, size, emplace_back, batch; guard check(session-&gt;enqueue(batch) == io::Admission::accepted,; growth emplace_back, reserve; 1 loop sites · [reviewed contract](#b0068) |
| [B0069 · 550–550](../../../../../tests/unit/window_test.cpp#L550) | Explanatory comments or spacing. |  |
| [B0070 · 551–608](../../../../../tests/unit/window_test.cpp#L551) | Callable definition: void commit_step(const io::WindowCommand& command, const PlannedStep& planned, bool check_output_barrier, const std::string& labe… | calls workload_statistics, at, contains, check; guard check(session-&gt;status().pending_command_sequence == command.sequence,; growth insert; 1 loop sites · [reviewed contract](#b0070) |
| [B0071 · 609–609](../../../../../tests/unit/window_test.cpp#L609) | Explanatory comments or spacing. |  |
| [B0072 · 610–635](../../../../../tests/unit/window_test.cpp#L610) | Callable definition: void process(const io::WindowCommand& command, bool check_output_barrier = false) | calls plan_independently, check, empty, begin_next_result; guard check(!steps.empty(), "list oracle returned an empty command expansion");; 1 loop sites · [reviewed contract](#b0072) |
| [B0073 · 636–637](../../../../../tests/unit/window_test.cpp#L636) | Closes surrounding scope/type. |  · [reviewed contract](#b0073) |
| [B0074 · 638–647](../../../../../tests/unit/window_test.cpp#L638) | Callable definition: void finish_and_check_eof(Harness& harness) | calls check, status, begin_next_result, finish_input; guard check(harness.session-&gt;status().queue && · [reviewed contract](#b0074) |
| [B0075 · 648–648](../../../../../tests/unit/window_test.cpp#L648) | Explanatory comments or spacing. |  |
| [B0076 · 649–668](../../../../../tests/unit/window_test.cpp#L649) | Callable definition: void projected_duplicates_and_watermark_prefixes() | calls harness, projected_pair_plan, window_options, insert_command; guard check(harness.oracle.physical_sequence == 6 &&; 1 loop sites; source comment (unverified): // No deadline has reached the boundary. · [reviewed contract](#b0076) |
| [B0077 · 669–669](../../../../../tests/unit/window_test.cpp#L669) | Explanatory comments or spacing. |  |
| [B0078 · 670–703](../../../../../tests/unit/window_test.cpp#L670) | Callable definition: void nonmonotone_times_and_alias_loop_expirations() | calls harness, unary_plan, window_options, insert_command; guard check(harness.oracle.labels.size() == 2,; 2 loop sites · [reviewed contract](#b0078) |
| [B0079 · 704–704](../../../../../tests/unit/window_test.cpp#L704) | Explanatory comments or spacing. |  |
| [B0080 · 705–784](../../../../../tests/unit/window_test.cpp#L705) | Callable definition: void global_and_relation_fifo_contracts() | calls harness, two_relation_plan, window_options, insert_command; guard check(*harness.session-&gt;window_state() == before,; 1 loop sites · [reviewed contract](#b0080) |
| [B0081 · 785–785](../../../../../tests/unit/window_test.cpp#L785) | Explanatory comments or spacing. |  |
| [B0082 · 786–815](../../../../../tests/unit/window_test.cpp#L786) | Callable definition: void rejected_head_preserves_committed_prefix(const PhysicalPlan& plan, WindowOptions options, std::vector&lt;io::WindowCommand&gt; com… | calls harness, std::move, enqueue, start; guard check(canonical_after == canonical_before,; 1 loop sites · [reviewed contract](#b0082) |
| [B0083 · 816–816](../../../../../tests/unit/window_test.cpp#L816) | Explanatory comments or spacing. |  |
| [B0084 · 817–884](../../../../../tests/unit/window_test.cpp#L817) | Callable definition: void strict_time_labels_watermarks_and_overflow() | calls unary_plan, window_options, rejected_head_preserves_committed_prefix, watermark_command; guard check(harness.oracle.labels.size() == 1 &&; 1 loop sites · [reviewed contract](#b0084) |
| [B0085 · 885–885](../../../../../tests/unit/window_test.cpp#L885) | Explanatory comments or spacing. |  |
| [B0086 · 886–929](../../../../../tests/unit/window_test.cpp#L886) | Callable definition: void invalid_window_options_and_managed_initial_state() | calls unary_plan, expect_code, QuerySession::create_windowed, window_options; guard check(allowed.session-&gt;snapshot().rows.empty(),; growth insert, resize · [reviewed contract](#b0086) |
| [B0087 · 930–930](../../../../../tests/unit/window_test.cpp#L930) | Explanatory comments or spacing. |  |
| [B0088 · 931–951](../../../../../tests/unit/window_test.cpp#L931) | Callable definition: void boolean_exists_counts_and_empty_delta_barriers() | calls harness, exists_plan, window_options, snapshot; guard check(initial.rows.size() == 1 &&; 1 loop sites · [reviewed contract](#b0088) |
| [B0089 · 952–952](../../../../../tests/unit/window_test.cpp#L952) | Explanatory comments or spacing. |  |
| [B0090 · 953–1042](../../../../../tests/unit/window_test.cpp#L953) | Callable definition: void pause_drain_and_stop_keep_only_committed_watermark_steps() | calls harness, unary_plan, window_options, insert_command; guard check(watermark_steps.size() == 3,; 1 loop sites · [reviewed contract](#b0090) |
| [B0091 · 1043–1043](../../../../../tests/unit/window_test.cpp#L1043) | Explanatory comments or spacing. |  |
| [B0092 · 1044–1059](../../../../../tests/unit/window_test.cpp#L1044) | Callable definition: void run() | calls run_case · [reviewed contract](#b0092) |
| [B0093 · 1060–1061](../../../../../tests/unit/window_test.cpp#L1060) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0093) |
| [B0094 · 1062–1074](../../../../../tests/unit/window_test.cpp#L1062) | Callable definition: int main() | calls run, statistics_acceptance::print, what; returns 1; 0 · [reviewed contract](#b0094) |
| [B0095 · 1075–1075](../../../../../tests/unit/window_test.cpp#L1075) | Explanatory comments or spacing. |  |

## B0001

[Lines 1–30](../../../../../tests/unit/window_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L30:sha256:084f05201028c19e710cc26b6be6f996bf84272da77736e95589a4c4393ada4c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare window_test.cpp: include "crown/api/error.hpp", "crown/frontend/bind.hpp", "crown/frontend/normalize.hpp", "crown/planner/lower.hpp", "crown/runtime/session.hpp", "evaluator.hpp", "statistics_acceptance.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;map&gt;, &lt;memory&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;utility&gt;, &lt;variant&gt;, &lt;vector&gt;; bind local aliases/name imports; select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 31–33](../../../../../tests/unit/window_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a test failure when a window-fixture condition is false. |
| inputs / outputs | Takes condition and borrowed diagnostic string; returns void. |
| invariants | Does not catch errors from session/runtime operations. |
| ownership | Message is used during the call. |
| failure | False throws std::runtime_error. |
| cost | One branch. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0004

[Lines 35–46](../../../../../tests/unit/window_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
void expect_code(Action&& action, std::string_view code,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to raise crown::Error with the expected code. |
| inputs / outputs | Forwards an action and borrows code/label; returns on exact match. |
| invariants | Catches only crown::Error; wrong code or no error fails; other exceptions propagate. |
| ownership | Callable and text borrowed during invocation. |
| failure | Mismatch throws std::runtime_error. |
| cost | Invokes action once. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0006

[Lines 48–55](../../../../../tests/unit/window_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
void run_case(const std::string& label, Action&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one named window fixture and prefix any std::exception diagnostic with its case label. |
| inputs / outputs | Takes label and action; returns void. |
| invariants | Wraps only std::exception; does not claim to catch non-standard exceptions. |
| ownership | Label/action borrowed for the call. |
| failure | Rethrows a new std::runtime_error with the original message appended. |
| cost | One action invocation and possible string construction. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0008

[Lines 57–57](../../../../../tests/unit/window_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an int64 query fixture Value. |
| inputs / outputs | Takes signed integer; returns Value by value. |
| invariants | Preserves the integer. |
| ownership | No external state retained. |
| failure | Variant construction errors propagate. |
| cost | Scalar conversion. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0010

[Lines 59–67](../../../../../tests/unit/window_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan unary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a unary native plan over one int64 table. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | One atom and one output variable x; used to exercise labels, watermark and boundary behavior. |
| ownership | Returned plan owns catalog/query/tree metadata. |
| failure | Lowering failures propagate. |
| cost | Builds and lowers one fixed plan. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0012

[Lines 69–81](../../../../../tests/unit/window_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan projected_pair_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a physical two-column table query projected to key. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | The payload remains part of full physical-row identity while SQL answer exposes only key. |
| ownership | Returned plan owns metadata. |
| failure | Lowering failures propagate. |
| cost | One fixed plan lowering. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0014

[Lines 83–100](../../../../../tests/unit/window_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan self_join_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a self-join plan over two occurrences of one edge table. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Two aliases share middle variable y; ordered head x,z,y preserves an alias-loop case. |
| ownership | Plan owns metadata. |
| failure | Lowering failures propagate. |
| cost | One fixed plan lowering. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0016

[Lines 102–116](../../../../../tests/unit/window_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan two_relation_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a disconnected product over two unary relations. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Nullary generalized root combines independent x and y factors. |
| ownership | Plan owns metadata. |
| failure | Lowering failures propagate. |
| cost | One fixed plan lowering. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0018

[Lines 118–134](../../../../../tests/unit/window_test.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan exists_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind and normalize a SQL EXISTS query over flags, then lower its one source atom. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | The SQL output is Boolean false/true; underlying core source answer is nullary truth. |
| ownership | Catalog/query/tree/program temporaries local; plan owns lowered metadata. |
| failure | Binding/normalization diagnostics become runtime_error; lowering errors propagate. |
| cost | One fixed SQL bind/normalize/lower pipeline. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp) |

## B0020

[Lines 136–138](../../../../../tests/unit/window_test.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::SourcePosition source_position(std::uint64_t offset) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a source-position value for one synthetic feed. |
| inputs / outputs | Takes byte offset; returns SourcePosition by value. |
| invariants | Source name is fixed as window-feed. |
| ownership | Returned string owns its value. |
| failure | Allocation errors propagate. |
| cost | One small value construction. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp) |

## B0022

[Lines 140–147](../../../../../tests/unit/window_test.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::WindowCommand insert_command(std::uint64_t sequence, std::uint64_t label,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a typed insertion command with optional feed offset. |
| inputs / outputs | Takes sequence, label, table, row, timestamp and optional offset; returns WindowCommand. |
| invariants | Moves row into WindowInsert; present offset maps to window-feed SourcePosition. |
| ownership | Returned command owns row and strings. |
| failure | Allocation/variant errors propagate. |
| cost | One command object and optional source position. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0024

[Lines 149–155](../../../../../tests/unit/window_test.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::WindowCommand withdraw_command(std::uint64_t sequence,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a typed label-withdrawal command. |
| inputs / outputs | Takes sequence, label and optional offset; returns WindowCommand. |
| invariants | No physical table/row is supplied; controller resolves label identity. |
| ownership | Returned command owns its DTO fields. |
| failure | Allocation errors propagate. |
| cost | One small command object. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0026

[Lines 157–163](../../../../../tests/unit/window_test.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::WindowCommand watermark_command(std::uint64_t sequence,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a typed watermark-advance command. |
| inputs / outputs | Takes sequence, watermark and optional offset; returns WindowCommand. |
| invariants | Watermark is uint64 adapter time, separate from SQL timestamps and external source offset. |
| ownership | Returned command owns its DTO fields. |
| failure | Allocation errors propagate. |
| cost | One small command object. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0028

[Lines 165–172](../../../../../tests/unit/window_test.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowOptions window_options(std::vector<TableId> tables, std::uint64_t width,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build WindowOptions for an explicit managed-table set, width and FIFO policy. |
| inputs / outputs | Takes table vector by value plus width/policy; returns options. |
| invariants | Defaults FIFO to global; all resource limits remain their type defaults. |
| ownership | Returned options own managed-table vector. |
| failure | No validation here; create_windowed performs admission checks. |
| cost | Moves the vector and copies scalar settings. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [docs/batches_windows.md § Window policy and full-row identity](../../../../batches_windows.md) |

## B0030

[Lines 174–181](../../../../../tests/unit/window_test.cpp#L174); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ModelLabel {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Model one active window label. |
| inputs / outputs | Stores external label, table, full row, event timestamp, deadline and count ID. |
| invariants | Full physical row identity includes unused columns; equal rows share count identity. |
| ownership | Owns copied Row values. |
| failure | Plain fixture record. |
| cost | Value record; row width is fixture-controlled. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0032

[Lines 183–189](../../../../../tests/unit/window_test.cpp#L183); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ModelActive {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Model one multi-step watermark expansion. |
| inputs / outputs | Stores command sequence, target watermark, expiration label order and completed/total steps. |
| invariants | Separates active watermark progress from accepted external command and physical sequence. |
| ownership | Owns expiration label vector. |
| failure | Plain fixture record. |
| cost | Storage proportional to expirations in the one test command. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0034

[Lines 191–201](../../../../../tests/unit/window_test.cpp#L191); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Oracle {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the list-based independent window oracle state. |
| inputs / outputs | Contains WindowOptions, physical Database, insertion-ordered labels, command/physical/watermark/high-label progress, optional active command and source progress. |
| invariants | Labels form a simple model separate from controller indexes; count IDs identify first live label for each full row. |
| ownership | Owns copied model/database state. |
| failure | No runtime behavior; fixture checks fail through callers. |
| cost | Model copies and scans finite test labels. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0036

[Lines 203–206](../../../../../tests/unit/window_test.cpp#L203); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PlannedStep {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair one prospective controller substep with its post-step oracle state. |
| inputs / outputs | Contains optional PhysicalSetUpdate and Oracle by value. |
| invariants | A watermark expands into one entry per expiring label; metadata-only commands have no physical update. |
| ownership | Owns copied oracle snapshot. |
| failure | Plain planning record. |
| cost | Copies finite oracle state per modeled step. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0038

[Lines 208–213](../../../../../tests/unit/window_test.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t count_labels(const Oracle& oracle, TableId table, const Row& row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count current labels matching a table and full Row. |
| inputs / outputs | Takes Oracle by const reference, table and Row; returns size_t. |
| invariants | Counts label multiplicity, not query-projected duplicates. |
| ownership | Oracle/row borrowed. |
| failure | No custom error handling. |
| cost | Linear scan of live labels. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0040

[Lines 215–221](../../../../../tests/unit/window_test.cpp#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t count_id_for(const Oracle& oracle, TableId table, const Row& row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the stable first-label count identity for one full physical row. |
| inputs / outputs | Takes Oracle/table/row by const reference; returns count ID or zero. |
| invariants | Returns the original surviving count ID when another duplicate label exists. |
| ownership | Inputs borrowed. |
| failure | No custom error handling. |
| cost | Linear scan until match. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0042

[Lines 223–230](../../../../../tests/unit/window_test.cpp#L223); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void add_physical(Oracle& oracle, TableId table, SetOperation operation,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one modeled physical set transition and increment physical sequence. |
| inputs / outputs | Takes Oracle, operation/table/row and optional update output; returns void. |
| invariants | Increments sequence for each actual physical step; relation update uses set insert/erase. |
| ownership | Oracle mutated; row borrowed/copied into update. |
| failure | Invalid table access or allocation failure propagates. |
| cost | One set operation and optional update copy. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0044

[Lines 232–239](../../../../../tests/unit/window_test.cpp#L232); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void complete_command(Oracle& oracle, const io::WindowCommand& command) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance the modeled external command acknowledgement and source offset. |
| inputs / outputs | Takes Oracle/command by const reference; returns void. |
| invariants | Command sequence and optional source position advance together only at modeled completion. |
| ownership | Oracle mutated; command borrowed. |
| failure | No custom validation beyond model assignment. |
| cost | Constant number of scalar/map operations. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0046

[Lines 241–360](../../../../../tests/unit/window_test.cpp#L241); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<PlannedStep> plan_independently(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expand one insert, FIFO withdrawal or watermark into independent list-oracle steps. |
| inputs / outputs | Takes prior Oracle and typed WindowCommand by const reference; returns vector&lt;PlannedStep&gt;. |
| invariants | Insertion adds label and physical insert only at count 0→1; withdrawal requires policy FIFO and erases physical row only at 1→0; watermark sorts due labels by deadline,label, prechecks whole FIFO order, then models each label removal and final command acknowledgement. |
| ownership | Input borrowed; result owns copied post-step Oracles/rows. |
| failure | Unknown label/FIFO/order makes this oracle throw; runtime rejection tests bypass it for rejected heads. It does not inject failures. |
| cost | Scans labels/counts, sorts due labels and copies state for each finite step. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [docs/batches_windows.md § Window policy and full-row identity](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0048

[Lines 362–372](../../../../../tests/unit/window_test.cpp#L362); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowProgress expected_progress(const Oracle& oracle) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert oracle state to expected public WindowProgress. |
| inputs / outputs | Takes Oracle by const reference; returns progress value. |
| invariants | Active command fields are present only during an incomplete watermark. |
| ownership | Oracle borrowed; result owns scalars. |
| failure | No custom failure handling. |
| cost | Constant-size projection. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0050

[Lines 374–433](../../../../../tests/unit/window_test.cpp#L374); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_canonical(QuerySession& session, const Oracle& oracle,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare full exposed canonical window state to independently reconstructed label/count/FIFO/index state. |
| inputs / outputs | Takes QuerySession, Oracle and label; returns void. |
| invariants | Rebuilds expected counts from labels, sorts deadline/label pairs, compares label list, global/per-table FIFO, command/physical/watermark/high-label progress, active expansion and public label/distinct counts. |
| ownership | Session/Oracle borrowed; expected vectors/maps local copies. |
| failure | Any field mismatch fails; canonical_state itself may allocate and export full rows. |
| cost | Full scan of live model and public state; not a constant-work assertion. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0052

[Lines 435–446](../../../../../tests/unit/window_test.cpp#L435); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> collect_output(QuerySession& session,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain committed signed output into a unique operation/Row set. |
| inputs / outputs | Takes QuerySession by reference and label; returns owning set. |
| invariants | Checks ordinals start at one and are contiguous; exports tuple values before retaining them. |
| ownership | Session cursor borrowed; returned rows copied and own values. |
| failure | Duplicate result or ordinal mismatch fails. |
| cost | Consumes all pending output rows. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0054

[Lines 448–453](../../../../../tests/unit/window_test.cpp#L448); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> reference_delta(const CommittedReferenceEpoch& epoch) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a committed reference epoch’s added/removed relations to signed rows. |
| inputs / outputs | Takes epoch by const reference; returns set of SignedKey. |
| invariants | Added rows become inserts; removed rows become erases. |
| ownership | Epoch borrowed; set copies rows. |
| failure | Allocation failures propagate. |
| cost | Visits both finite delta relations. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0056

[Lines 455–460](../../../../../tests/unit/window_test.cpp#L455); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Query exists_source_query() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the physical unary query used under SQL EXISTS. |
| inputs / outputs | No args; returns Query. |
| invariants | One source atom R(x), empty core head; SQL wrapper later maps nullary truth to scalar Boolean. |
| ownership | Returned query owns names/terms. |
| failure | No custom failure handling. |
| cost | Small fixed query construction. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0058

[Lines 462–464](../../../../../tests/unit/window_test.cpp#L462); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Query independent_query(const PhysicalPlan& plan, bool sql_exists_wrapper) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select physical-source query for ordinary versus wrapped EXISTS oracle evaluation. |
| inputs / outputs | Takes plan by const reference and wrapper flag; returns Query copy. |
| invariants | Uses the physical R(x) query for EXISTS truth, otherwise the plan’s core query. |
| ownership | Plan borrowed; result owns query copy. |
| failure | Copy/allocation errors propagate. |
| cost | Copies one fixed query. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0060

[Lines 466–468](../../../../../tests/unit/window_test.cpp#L466); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation sql_exists_rows(const Relation& nullary_answer) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map a nullary reference answer to one scalar Boolean row. |
| inputs / outputs | Takes Relation by const reference; returns singleton Relation. |
| invariants | Nonempty core truth maps to true; empty maps to false. |
| ownership | Input borrowed; result owns Boolean value. |
| failure | Allocation errors propagate. |
| cost | One Boolean row construction. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0062

[Lines 470–478](../../../../../tests/unit/window_test.cpp#L470); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> signed_difference(const Relation& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the signed set difference between two relations. |
| inputs / outputs | Takes before/after relations by const reference; returns operation/row set. |
| invariants | After-only rows insert; before-only rows erase; shared rows omitted. |
| ownership | Inputs borrowed; result copies rows. |
| failure | Allocation failures propagate. |
| cost | Scans both finite relations. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0064

[Lines 480–510](../../../../../tests/unit/window_test.cpp#L480); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_snapshot(QuerySession& session, const PhysicalPlan& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare QuerySession snapshots with independent label-derived evaluation and reference Session state. |
| inputs / outputs | Takes session, plan, reference session and Oracle by reference plus label/wrapper flag; returns void. |
| invariants | Checks tuple layout identity and uniqueness, A04-style independent physical evaluation, reference answer, SQL EXISTS mapping, snapshot/source progress and window prefix. |
| ownership | Runtime/oracle/reference state borrowed; evaluated relations and copied observed rows local. |
| failure | Any row/layout/progress mismatch fails. |
| cost | Materializes both reference answers and copies a full snapshot. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md) |

## B0065

[Lines 511–519](../../../../../tests/unit/window_test.cpp#L511); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L511-L519:sha256:b5f8bad560dd3623d2c753af3710635b82495f451124eac9c853bf1a45c6e850
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare window_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0066

[Lines 520–539](../../../../../tests/unit/window_test.cpp#L520); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Harness(PhysicalPlan value, WindowOptions windows,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a windowed QuerySession, an independent reference Session and list Oracle. |
| inputs / outputs | Takes plan/options/initial DB by value and wrapper flag; returns initialized Harness. |
| invariants | Resizes empty initial tables; optionally enables statistics acceptance under macro; windowed managed tables are supplied explicitly. |
| ownership | Owns plan, options, session owner, reference session and moved Oracle database. |
| failure | Invalid options/initial managed rows or session construction errors propagate. |
| cost | Builds two finite runtimes plus initial database copies. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/batches_windows.md § Window policy and full-row identity](../../../../batches_windows.md) |

## B0068

[Lines 541–549](../../../../../tests/unit/window_test.cpp#L541); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void enqueue(const std::vector<io::WindowCommand>& commands) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer a typed vector of window commands to the session queue. |
| inputs / outputs | Takes command vector by const reference; returns void. |
| invariants | Successful accepted batch must be empty after ownership transfer. |
| ownership | Commands borrowed to build batch then batch owns moved input items. |
| failure | Rejected/full batch or failed ownership transfer fails. |
| cost | Copies command DTOs into one batch. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp) |

## B0070

[Lines 551–608](../../../../../tests/unit/window_test.cpp#L551); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void commit_step(const io::WindowCommand& command,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive one prepared physical or metadata-only window step through commit and compare references. |
| inputs / outputs | Takes command, PlannedStep and label by reference plus barrier flag; returns void. |
| invariants | Physical update reaches prepared, commits, then reference epoch applies; metadata barrier prepares/commits without physical sequence; only after step commit does model/source progress advance; drains exact output and compares snapshots/canonical state. Optional statistics calls are macro-gated. |
| ownership | Harness owns session/reference/Oracle; planned update borrowed and passed to both engines. |
| failure | Runtime/reference/output mismatch fails; no allocation-failure injection. |
| cost | Runs session steps to prepared, one commit, full snapshot/canonical/reference comparisons. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0072

[Lines 610–635](../../../../../tests/unit/window_test.cpp#L610); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void process(const io::WindowCommand& command, bool check_output_barrier = false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begin one queued command and commit each independently planned watermark substep at the same queue head. |
| inputs / outputs | Takes command and optional output-barrier flag; returns void. |
| invariants | Requires begin pending; intermediate watermark steps leave external source progress/queue head unacknowledged; resumes same command sequence. |
| ownership | Harness owns all session state; input command borrowed. |
| failure | Unexpected begin/sequence/queue state fails. |
| cost | Performs one session begin plus all finite planned substeps and per-step checks. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0073

[Lines 636–637](../../../../../tests/unit/window_test.cpp#L636); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L636-L637:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in window_test.cpp: struct Harness. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0074

[Lines 638–647](../../../../../tests/unit/window_test.cpp#L638); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish_and_check_eof(Harness& harness) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the accepted typed queue to drain and distinguish open would-block from closed end. |
| inputs / outputs | Takes Harness by reference; returns void. |
| invariants | Acknowledged queue count zero; open empty is would_block; after finish_input it is end. |
| ownership | Harness borrowed. |
| failure | Unexpected session status fails. |
| cost | Two status reads/transitions. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0076

[Lines 649–668](../../../../../tests/unit/window_test.cpp#L649); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void projected_duplicates_and_watermark_prefixes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise projected duplicate labels, payload identity, exact deadlines and multi-step watermark acknowledgement. |
| inputs / outputs | No args; runs six inserts/watermarks on key projection. |
| invariants | Two identical full rows emit physical insert once and expire erase once; distinct payload row is distinct input; watermark 10 starts count-only then physical steps; command and physical sequences remain separate; output barrier is checked. |
| ownership | Local Harness owns runtime/model/reference state. |
| failure | Output, canonical state, sequence or boundary mismatch fails. |
| cost | Four inserts and three watermark commands with full per-step A04/list comparisons. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0078

[Lines 670–703](../../../../../tests/unit/window_test.cpp#L670); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nonmonotone_times_and_alias_loop_expirations() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise decreasing event timestamps before watermark and full expiration of self-join loop/alias rows. |
| inputs / outputs | No args; runs unary and self-join scopes. |
| invariants | Timestamp insertion order is not expiry order; with width 5, watermark labels eventually expire; duplicate physical edge labels collapse to set insert/erase transitions. |
| ownership | Each Harness local. |
| failure | Reference, count or output mismatch fails. |
| cost | Three unary commands and seven self-join commands. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0080

[Lines 705–784](../../../../../tests/unit/window_test.cpp#L705); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void global_and_relation_fifo_contracts() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare global versus per-relation withdrawal and expiration FIFO policies. |
| inputs / outputs | No args; executes four finite Harness cases. |
| invariants | Global policy rejects later due label when older label blocks and rejects explicit non-head withdrawal; per-relation expires eligible relation B and allows oldest A label within its relation. |
| ownership | Each Harness local; command vectors own DTOs. |
| failure | Exact window_fifo_violation and sticky input_failed codes checked on rejected heads. |
| cost | Four small two-relation traces with snapshots and barriers. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [docs/batches_windows.md § Window policy and full-row identity](../../../../batches_windows.md) |

## B0082

[Lines 786–815](../../../../../tests/unit/window_test.cpp#L786); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rejected_head_preserves_committed_prefix(const PhysicalPlan& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a rejected queued head leaves committed physical/window/source prefix unchanged. |
| inputs / outputs | Takes plan/options/commands by value, prefix count/code/label; returns void. |
| invariants | After committing prefix, rejection preserves full canonical window state, snapshot row count/sequence, progress, sticky queued head and no pending command; next retry reports input_failed. |
| ownership | Local Harness owns all state; expected prefix snapshot copied. |
| failure | Unexpected code or prefix mutation fails. |
| cost | Processes prefix and compares a full current snapshot plus canonical state. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0084

[Lines 817–884](../../../../../tests/unit/window_test.cpp#L817); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void strict_time_labels_watermarks_and_overflow() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise strict late/decreasing/overflow/label validation plus exact watermark boundary acceptance. |
| inputs / outputs | No args; invokes rejected-head helper for seven invalid commands, then two legal traces. |
| invariants | Covers late insertion, decreasing watermark, deadline overflow, duplicate/zero/reused labels, unknown withdrawal; event at completed watermark is allowed and expires at deadline; timestamp order may differ from label FIFO order. |
| ownership | Local Harnesses and vectors own values. |
| failure | Requires named invalid codes and unchanged committed prefix; wrong behavior fails. |
| cost | Seven rejected command fixtures plus two accepted finite traces. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [docs/batches_windows.md § Window policy and full-row identity](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0086

[Lines 886–929](../../../../../tests/unit/window_test.cpp#L886); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void invalid_window_options_and_managed_initial_state() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check create_windowed option admission and managed versus static initial data. |
| inputs / outputs | No args; returns void. |
| invariants | Rejects empty managed set, zero width, unknown and duplicate managed tables; permits populated un-managed static relation; rejects managed initial rows. |
| ownership | Plans/databases are local values. |
| failure | Checks invalid_window_options and invalid_window_initial_state codes. |
| cost | Several constructor admission attempts and one allowed initial snapshot. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0088

[Lines 931–951](../../../../../tests/unit/window_test.cpp#L931); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boolean_exists_counts_and_empty_delta_barriers() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise SQL EXISTS Boolean output with duplicate labels and empty-delta metadata barriers. |
| inputs / outputs | No args; returns void. |
| invariants | Empty source exposes false row; duplicate same physical row has one 0→1 and one final 1→0 transition; no-op count/watermark steps still commit explicit metadata barriers. |
| ownership | Harness owns SQL/core/reference state. |
| failure | Output, canonical label count and physical sequence mismatch fails. |
| cost | Two inserts and two watermarks with A04/reference comparisons. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0090

[Lines 953–1042](../../../../../tests/unit/window_test.cpp#L953); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void pause_drain_and_stop_keep_only_committed_watermark_steps() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify pause, one-step drains and stop preserve only committed prefix of a three-label watermark. |
| inputs / outputs | No args; returns void. |
| invariants | Each drain commits only one physical expiry and leaves queue/source command unacknowledged; stop after private third prepare leaves two committed removals, prior completed watermark and active scalar step counts; dropped session does not invalidate owned snapshot. |
| ownership | Harness owns session/runtime; committed snapshot owns copied rows. |
| failure | Any prefix/progress/snapshot mismatch fails; no fault injection. |
| cost | Three seeds, three watermark steps (last private), two drains, stop and drop. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0092

[Lines 1044–1059](../../../../../tests/unit/window_test.cpp#L1044); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the seven named window scenario groups. |
| inputs / outputs | No args; returns after run_case calls. |
| invariants | Invokes projection/deadline, nonmonotone time, FIFO, validation, initial state, EXISTS and pause/drain/stop cases. |
| ownership | Each case constructs local Harness. |
| failure | run_case prefixes std::exception; unhandled exceptions escape to main. |
| cost | Fixed finite fixture suite. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp) |

## B0093

[Lines 1060–1061](../../../../../tests/unit/window_test.cpp#L1060); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1060-L1061:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in window_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0094

[Lines 1062–1074](../../../../../tests/unit/window_test.cpp#L1062); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run window acceptance fixtures and report pass/failure. |
| inputs / outputs | No args; returns 0 on completion or 1 after caught std::exception. |
| invariants | Statistics print is conditional on CROWN_STATISTICS_ACCEPTANCE; packet review does not claim executable run. |
| ownership | Fixtures own local state. |
| failure | Caught std::exception text prints to stderr. |
| cost | Finite seven-scenario suite. |
| Design | [tests/unit/window_test.cpp](../../../../../tests/unit/window_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md) |
