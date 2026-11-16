# `tests/unit/ingest_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/ingest_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `89cbef27a4f2b65030e647e927971cf6f5c7c29e20f01c89b7f1a65c0eeff915`. 954 lines partitioned into 92 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–27](../../../../../tests/unit/ingest_exception_test.cpp#L1) | Imports dependencies. | growth new · [reviewed contract](#b0001) |
| [B0002 · 28–39](../../../../../tests/unit/ingest_exception_test.cpp#L28) | declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // This standalone executable replaces the ordinary throwing scalar and · [reviewed contract](#b0002) |
| [B0003 · 40–50](../../../../../tests/unit/ingest_exception_test.cpp#L40) | Callable definition: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes) | calls std::max, std::malloc; returns result; growth malloc · [reviewed contract](#b0003) |
| [B0004 · 51–51](../../../../../tests/unit/ingest_exception_test.cpp#L51) | Explanatory comments or spacing. |  |
| [B0005 · 52–58](../../../../../tests/unit/ingest_exception_test.cpp#L52) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0005) |
| [B0006 · 59–60](../../../../../tests/unit/ingest_exception_test.cpp#L59) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0006) |
| [B0007 · 61–61](../../../../../tests/unit/ingest_exception_test.cpp#L61) | Callable definition: void* operator new(std::size_t bytes) | calls malloc_new; returns malloc_new(bytes); growth new · [reviewed contract](#b0007) |
| [B0008 · 62–62](../../../../../tests/unit/ingest_exception_test.cpp#L62) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns malloc_new(bytes); growth new · [reviewed contract](#b0008) |
| [B0009 · 63–63](../../../../../tests/unit/ingest_exception_test.cpp#L63) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0009) |
| [B0010 · 64–64](../../../../../tests/unit/ingest_exception_test.cpp#L64) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0010) |
| [B0011 · 65–65](../../../../../tests/unit/ingest_exception_test.cpp#L65) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0011) |
| [B0012 · 66–66](../../../../../tests/unit/ingest_exception_test.cpp#L66) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0012) |
| [B0013 · 67–80](../../../../../tests/unit/ingest_exception_test.cpp#L67) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;io::EventReader&gt;); · [reviewed contract](#b0013) |
| [B0014 · 81–83](../../../../../tests/unit/ingest_exception_test.cpp#L81) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0014) |
| [B0015 · 84–84](../../../../../tests/unit/ingest_exception_test.cpp#L84) | Explanatory comments or spacing. |  |
| [B0016 · 85–95](../../../../../tests/unit/ingest_exception_test.cpp#L85) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls check, code, std::string, std::runtime_error; guard check(failure.code() == code, · [reviewed contract](#b0016) |
| [B0017 · 96–96](../../../../../tests/unit/ingest_exception_test.cpp#L96) | Explanatory comments or spacing. |  |
| [B0018 · 97–99](../../../../../tests/unit/ingest_exception_test.cpp#L97) | Callable definition: Catalog make_catalog() | calls ; returns {53, {{@ , {{@ , ScalarType::int64}, {@ , ScalarType::string}}, 4}}} · [reviewed contract](#b0018) |
| [B0019 · 100–100](../../../../../tests/unit/ingest_exception_test.cpp#L100) | Explanatory comments or spacing. |  |
| [B0020 · 101–103](../../../../../tests/unit/ingest_exception_test.cpp#L101) | Callable definition: Row row(std::int64_t x, std::string label) | calls std::move; returns {x, std::move(label)} · [reviewed contract](#b0020) |
| [B0021 · 104–104](../../../../../tests/unit/ingest_exception_test.cpp#L104) | Explanatory comments or spacing. |  |
| [B0022 · 105–109](../../../../../tests/unit/ingest_exception_test.cpp#L105) | Callable definition: InputEvent event(std::uint64_t sequence, std::int64_t x, std::string label, std::optional&lt;io::SourcePosition&gt; position = std::nul… | calls row, std::move; returns {{sequence, TableId{0}, SetOperation::insert, row(x, std::move(label))},; growth insert · [reviewed contract](#b0022) |
| [B0023 · 110–110](../../../../../tests/unit/ingest_exception_test.cpp#L110) | Explanatory comments or spacing. |  |
| [B0024 · 111–117](../../../../../tests/unit/ingest_exception_test.cpp#L111) | Callable definition: bool same_event(const auto& left, const InputEvent& right) | calls ; returns left.update.sequence == right.update.sequence && · [reviewed contract](#b0024) |
| [B0025 · 118–130](../../../../../tests/unit/ingest_exception_test.cpp#L118) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0025) |
| [B0026 · 131–140](../../../../../tests/unit/ingest_exception_test.cpp#L131) | Callable definition: Fixture() | calls emplace; growth emplace · [reviewed contract](#b0026) |
| [B0027 · 141–141](../../../../../tests/unit/ingest_exception_test.cpp#L141) | Explanatory comments or spacing. |  |
| [B0028 · 142–146](../../../../../tests/unit/ingest_exception_test.cpp#L142) | Callable definition: std::string_view bytes(InputFormat format) const | calls ; returns json; binary · [reviewed contract](#b0028) |
| [B0029 · 147–147](../../../../../tests/unit/ingest_exception_test.cpp#L147) | Explanatory comments or spacing. |  |
| [B0030 · 148–152](../../../../../tests/unit/ingest_exception_test.cpp#L148) | Callable definition: InputOptions options(InputFormat format) const | calls ; returns json_options; binary_options · [reviewed contract](#b0030) |
| [B0031 · 153–153](../../../../../tests/unit/ingest_exception_test.cpp#L153) | Explanatory comments or spacing. |  |
| [B0032 · 154–158](../../../../../tests/unit/ingest_exception_test.cpp#L154) | Callable definition: InputEvent expected(InputFormat format) const | calls event, std::string, size; returns input; event(1, 7, @ , · [reviewed contract](#b0032) |
| [B0033 · 159–159](../../../../../tests/unit/ingest_exception_test.cpp#L159) | Explanatory comments or spacing. |  |
| [B0034 · 160–164](../../../../../tests/unit/ingest_exception_test.cpp#L160) | Callable definition: std::uint64_t expected_bytes_read(InputFormat format) const | calls size; returns json.size(); binary.size() · [reviewed contract](#b0034) |
| [B0035 · 165–166](../../../../../tests/unit/ingest_exception_test.cpp#L165) | Closes surrounding scope/type. |  · [reviewed contract](#b0035) |
| [B0036 · 167–174](../../../../../tests/unit/ingest_exception_test.cpp#L167) | Callable definition: std::unique_ptr&lt;io::EventReader&gt; make_reader(const Fixture& fixture, InputFormat format, std::istringstream& stream, InputProgres… | calls options, std::move; returns std::make_unique&lt;io::EventReader&gt;(stream, fixture.catalog,; growth make_unique · [reviewed contract](#b0036) |
| [B0037 · 175–175](../../../../../tests/unit/ingest_exception_test.cpp#L175) | Explanatory comments or spacing. |  |
| [B0038 · 176–189](../../../../../tests/unit/ingest_exception_test.cpp#L176) | Callable definition: void check_fresh_recreated_event(const Fixture& fixture, InputFormat format) | calls std::string, bytes, make_reader, peek; guard check(decoded && same_event(*decoded, fixture.expected(format)), · [reviewed contract](#b0038) |
| [B0039 · 190–190](../../../../../tests/unit/ingest_exception_test.cpp#L190) | Explanatory comments or spacing. |  |
| [B0040 · 191–197](../../../../../tests/unit/ingest_exception_test.cpp#L191) | Callable definition: std::string edge_line(const Catalog& catalog, std::uint64_t sequence, std::int64_t x, std::int64_t z, std::optional&lt;io::SourcePos… | calls std::move, io::write_input_json; returns io::write_input_json(input, catalog) + @; growth insert · [reviewed contract](#b0040) |
| [B0041 · 198–198](../../../../../tests/unit/ingest_exception_test.cpp#L198) | Explanatory comments or spacing. |  |
| [B0042 · 199–234](../../../../../tests/unit/ingest_exception_test.cpp#L199) | Callable definition: std::size_t sweep_reader_construction(const Fixture& fixture, InputFormat format) | calls std::string, bytes, options, fault; guard check(failures &gt; 0, "reader construction sweep observed no injected ordinary-new failure point");; returns failures; growth emplace; 1 loop sites; source comment (unverified): // Construction does not consume the borrowed stream. A fresh reader on · [reviewed contract](#b0042) |
| [B0043 · 235–235](../../../../../tests/unit/ingest_exception_test.cpp#L235) | Explanatory comments or spacing. |  |
| [B0044 · 236–284](../../../../../tests/unit/ingest_exception_test.cpp#L236) | Callable definition: std::size_t sweep_reader_peek(const Fixture& fixture, InputFormat format) | calls std::string, bytes, make_reader, fault; guard check(reader-&gt;failed(), "parser/progress-preparation OOM was not sticky");; returns failures; 1 loop sites · [reviewed contract](#b0044) |
| [B0045 · 285–285](../../../../../tests/unit/ingest_exception_test.cpp#L285) | Explanatory comments or spacing. |  |
| [B0046 · 286–342](../../../../../tests/unit/ingest_exception_test.cpp#L286) | Callable definition: void acknowledgement_and_lifetime_are_noalloc(const Fixture& fixture) | calls std::string, bytes, make_reader, check; guard check(reader-&gt;peek() != nullptr, "new-source acknowledgement fixture did not decode");; growth emplace; 1 loop sites; source comment (unverified): // A fresh source takes the prepared map-node path. · [reviewed contract](#b0046) |
| [B0047 · 343–343](../../../../../tests/unit/ingest_exception_test.cpp#L343) | Explanatory comments or spacing. |  |
| [B0048 · 344–430](../../../../../tests/unit/ingest_exception_test.cpp#L344) | Callable definition: void sweep_catalog_digest_and_codecs(const Fixture& fixture) | calls fault, io::input_catalog_sha256, check, forbid_allocations; guard check(digest_failures &gt; 0,; returns io::write_input_json(fixture.input, fixture.catalog); io::write_input_binary(fixture.input, fixture…; 2 loop sites · [reviewed contract](#b0048) |
| [B0049 · 431–431](../../../../../tests/unit/ingest_exception_test.cpp#L431) | Explanatory comments or spacing. |  |
| [B0050 · 432–442](../../../../../tests/unit/ingest_exception_test.cpp#L432) | Callable definition: PhysicalPlan make_root_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0050) |
| [B0051 · 443–443](../../../../../tests/unit/ingest_exception_test.cpp#L443) | Explanatory comments or spacing. |  |
| [B0052 · 444–457](../../../../../tests/unit/ingest_exception_test.cpp#L444) | Callable definition: PhysicalPlan make_self_join_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0052) |
| [B0053 · 458–458](../../../../../tests/unit/ingest_exception_test.cpp#L458) | Explanatory comments or spacing. |  |
| [B0054 · 459–470](../../../../../tests/unit/ingest_exception_test.cpp#L459) | Callable definition: io::Json normalized_owners(io::Json value) | calls is_object, contains, items, self; returns value; 2 loop sites · [reviewed contract](#b0054) |
| [B0055 · 471–471](../../../../../tests/unit/ingest_exception_test.cpp#L471) | Explanatory comments or spacing. |  |
| [B0056 · 472–478](../../../../../tests/unit/ingest_exception_test.cpp#L472) | Type/record definition: struct RuntimeImage |  · [reviewed contract](#b0056) |
| [B0057 · 479–479](../../../../../tests/unit/ingest_exception_test.cpp#L479) | Explanatory comments or spacing. |  |
| [B0058 · 480–489](../../../../../tests/unit/ingest_exception_test.cpp#L480) | Callable definition: RuntimeImage image(const PhysicalRuntime& runtime) | calls snapshot, has_answer, normalized_owners, io::write_support_snapshot; returns result · [reviewed contract](#b0058) |
| [B0059 · 490–490](../../../../../tests/unit/ingest_exception_test.cpp#L490) | Explanatory comments or spacing. |  |
| [B0060 · 491–500](../../../../../tests/unit/ingest_exception_test.cpp#L491) | Callable definition: RuntimeImage image(const DeltaRuntime& runtime) | calls snapshot, has_answer, normalized_owners, io::write_support_snapshot; returns result · [reviewed contract](#b0060) |
| [B0061 · 501–501](../../../../../tests/unit/ingest_exception_test.cpp#L501) | Explanatory comments or spacing. |  |
| [B0062 · 502–506](../../../../../tests/unit/ingest_exception_test.cpp#L502) | Callable definition: io::InputProgress progress_at(std::uint64_t sequence) | calls ; returns progress · [reviewed contract](#b0062) |
| [B0063 · 507–507](../../../../../tests/unit/ingest_exception_test.cpp#L507) | Explanatory comments or spacing. |  |
| [B0064 · 508–513](../../../../../tests/unit/ingest_exception_test.cpp#L508) | Callable definition: std::string line(const Catalog& catalog, std::uint64_t sequence, std::int64_t x, std::string label, std::optional&lt;io::SourcePosit… | calls io::write_input_json, event, std::move; returns io::write_input_json(event(sequence, x, std::move(label), std::move(position)), · [reviewed contract](#b0064) |
| [B0065 · 514–514](../../../../../tests/unit/ingest_exception_test.cpp#L514) | Explanatory comments or spacing. |  |
| [B0066 · 515–519](../../../../../tests/unit/ingest_exception_test.cpp#L515) | Callable definition: std::string root_line(const PhysicalPlan& plan, std::uint64_t sequence, std::int64_t x, std::string label, std::uint64_t offset) | calls line, catalog, std::move; returns line(plan.catalog(), sequence, x, std::move(label), · [reviewed contract](#b0066) |
| [B0067 · 520–527](../../../../../tests/unit/ingest_exception_test.cpp#L520) | declares types or opens a type body. |  · [reviewed contract](#b0067) |
| [B0068 · 528–534](../../../../../tests/unit/ingest_exception_test.cpp#L528) | Callable definition: explicit HeldSourcePin(PhysicalEpoch committed) : epoch(std::move(committed)) | calls epoch, std::move, check, has_value; guard check(epoch.input.source.has_value(), "committed seed did not retain its source row"); · [reviewed contract](#b0068) |
| [B0069 · 535–535](../../../../../tests/unit/ingest_exception_test.cpp#L535) | Explanatory comments or spacing. |  |
| [B0070 · 536–543](../../../../../tests/unit/ingest_exception_test.cpp#L536) | Callable definition: void check_unchanged() const | calls check, handle, tuple, values; guard check(epoch.input.source && epoch.input.source-&gt;handle == handle && · [reviewed contract](#b0070) |
| [B0071 · 544–545](../../../../../tests/unit/ingest_exception_test.cpp#L544) | Closes surrounding scope/type. |  · [reviewed contract](#b0071) |
| [B0072 · 546–617](../../../../../tests/unit/ingest_exception_test.cpp#L546) | Callable definition: std::size_t sweep_ordered_physical_apply(const PhysicalPlan& plan) | calls catalog, root_line, clean, apply; guard check(expected.sequence == 2 && expected.physical\[0\].size() == 2,; returns failures; growth emplace, insert; 1 loop sites · [reviewed contract](#b0072) |
| [B0073 · 618–618](../../../../../tests/unit/ingest_exception_test.cpp#L618) | Explanatory comments or spacing. |  |
| [B0074 · 619–658](../../../../../tests/unit/ingest_exception_test.cpp#L619) | Callable definition: void sparse_replay_does_not_copy_the_existing_database(const PhysicalPlan& plan) | calls runtime, apply, sequence, row; guard check(replay.peek() != nullptr, "sparse replay fixture did not decode its event");; growth insert; 1 loop sites; source comment (unverified): // Stay below the arena's geometric slot-capacity boundary so the check · [reviewed contract](#b0074) |
| [B0075 · 659–659](../../../../../tests/unit/ingest_exception_test.cpp#L659) | Explanatory comments or spacing. |  |
| [B0076 · 660–669](../../../../../tests/unit/ingest_exception_test.cpp#L660) | Callable definition: DeltaOptions ordered_delta_options(std::size_t spool_rows = 65536, std::size_t spool_bytes = 64 * 1024 * 1024) | calls ; returns options · [reviewed contract](#b0076) |
| [B0077 · 670–670](../../../../../tests/unit/ingest_exception_test.cpp#L670) | Explanatory comments or spacing. |  |
| [B0078 · 671–677](../../../../../tests/unit/ingest_exception_test.cpp#L671) | Callable definition: std::vector&lt;std::tuple&lt;std::uint64_t, SetOperation, Row&gt;&gt; drain_delta( DeltaRuntime::Epoch& epoch) | calls next, emplace_back, crown::storage::export_row, values; returns result; growth emplace_back; 1 loop sites · [reviewed contract](#b0078) |
| [B0079 · 678–678](../../../../../tests/unit/ingest_exception_test.cpp#L678) | Explanatory comments or spacing. |  |
| [B0080 · 679–682](../../../../../tests/unit/ingest_exception_test.cpp#L679) | Type/record definition: struct DeltaCleanImage |  · [reviewed contract](#b0080) |
| [B0081 · 683–683](../../../../../tests/unit/ingest_exception_test.cpp#L683) | Explanatory comments or spacing. |  |
| [B0082 · 684–698](../../../../../tests/unit/ingest_exception_test.cpp#L684) | Callable definition: DeltaCleanImage clean_delta_single_event(const PhysicalPlan& plan, const std::string& encoded, std::uint64_t starting_sequence) | calls runtime, ordered_delta_options, set_mode, stream; guard check(output.has_value(), "clean delta replay did not return an epoch");; returns result · [reviewed contract](#b0082) |
| [B0083 · 699–699](../../../../../tests/unit/ingest_exception_test.cpp#L699) | Explanatory comments or spacing. |  |
| [B0084 · 700–760](../../../../../tests/unit/ingest_exception_test.cpp#L700) | Callable definition: std::size_t sweep_ordered_delta_apply(const PhysicalPlan& plan) | calls catalog, root_line, clean_delta_single_event, check; guard check(expected.runtime.sequence == 1 && expected.runtime.physical\[0\].size() == 1,; returns failures; growth emplace; 1 loop sites · [reviewed contract](#b0084) |
| [B0085 · 761–761](../../../../../tests/unit/ingest_exception_test.cpp#L761) | Explanatory comments or spacing. |  |
| [B0086 · 762–835](../../../../../tests/unit/ingest_exception_test.cpp#L762) | Callable definition: void parser_oom_precedes_engine_and_late_truncation_is_sticky() | calls make_root_plan, catalog, root_line, runtime; guard check(first && runtime.sequence() == 1 && replay.progress().sequence == 1,; growth emplace; 1 loop sites; source comment (unverified): // The reader consumed some or all of record two. Recovery is explicit: · [reviewed contract](#b0086) |
| [B0087 · 836–836](../../../../../tests/unit/ingest_exception_test.cpp#L836) | Explanatory comments or spacing. |  |
| [B0088 · 837–889](../../../../../tests/unit/ingest_exception_test.cpp#L837) | Callable definition: void late_truncated_binary_and_output_busy_keep_progress() | calls make_root_plan, catalog, io::write_input_binary, event; guard check(committed && physical.sequence() == 1 && broken.progress().sequence == 1, · [reviewed contract](#b0088) |
| [B0089 · 890–890](../../../../../tests/unit/ingest_exception_test.cpp#L890) | Explanatory comments or spacing. |  |
| [B0090 · 891–921](../../../../../tests/unit/ingest_exception_test.cpp#L891) | Callable definition: void alias_fanout_quota_rollback_retains_cached_input() | calls make_self_join_plan, catalog, ordered_delta_options, runtime; guard check(cached && cached-&gt;update.sequence == 3,; growth insert; source comment (unverified): // Seed both aliases in maintenance mode, then start ordered output mode. · [reviewed contract](#b0090) |
| [B0091 · 922–924](../../../../../tests/unit/ingest_exception_test.cpp#L922) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0091) |
| [B0092 · 925–954](../../../../../tests/unit/ingest_exception_test.cpp#L925) | Callable definition: int main() | calls sweep_reader_construction, sweep_reader_peek, acknowledgement_and_lifetime_are_noalloc, sweep_catalog_digest_and_codecs; returns 1 · [reviewed contract](#b0092) |

## B0001

[Lines 1–27](../../../../../tests/unit/ingest_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L27:sha256:13b7bc4af0f6f0c421744957ddfd9571e85ec342cd0e8342a015714c99f9c364
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ingest_exception_test.cpp: include "crown/api/error.hpp", "crown/io/catalog.hpp", "crown/io/ingest.hpp", "crown/io/support.hpp", "crown/planner/lower.hpp", "crown/runtime/delta.hpp", "crown/runtime/physical.hpp", "crown/runtime/replay.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;tuple&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 28–39](../../../../../tests/unit/ingest_exception_test.cpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L39:sha256:49b285d7acda34c07f9124a520c24160818d817fa05a3eba9685bae6b42996e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ingest_exception_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 40–50](../../../../../tests/unit/ingest_exception_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the test-local ordinary throwing allocation replacement backing used by scalar and array new. |
| inputs / outputs | Requested byte count in; records largest/count/total requests, checks thread-local fail_after, then returns malloc storage. |
| invariants | A zero-byte request calls malloc(1) but the recorded request remains zero; failure is checked before the backing malloc call. |
| ownership | Returned storage is released by this file’s matching free-based delete replacements; direct malloc users are outside the counter. |
| failure | Throws std::bad_alloc when fail_after is zero or the backing malloc returns null; fail_after is request-count based, not byte based. |
| cost | Updates three thread-local counters and makes one malloc call; counters observe only calls through this replacement. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md §Budgets and diagnostic command](../../../../ingestion.md) |

## B0005

[Lines 52–58](../../../../../tests/unit/ingest_exception_test.cpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm and reset the test’s thread-local fail-after setting. |
| inputs / outputs | Optional allocation-point index in; constructor sets fail_after and forbid_allocations sets it to zero. |
| invariants | Destruction always resets fail_after to -1; this is not a nesting stack and does not restore a prior value. |
| ownership | The scope owns no allocation or runtime; it controls thread-local state only. |
| failure | It injects only when a request reaches directly defined ordinary throwing scalar/array operator new; no dedicated aligned/nothrow replacements exist, and indirect delegation is not asserted coverage. |
| cost | Constant-time scalar assignment; no allocator census is performed. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md §Budgets and diagnostic command](../../../../ingestion.md) |

## B0006

[Lines 59–60](../../../../../tests/unit/ingest_exception_test.cpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L60:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ingest_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 61–61](../../../../../tests/unit/ingest_exception_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp) |

## B0008

[Lines 62–62](../../../../../tests/unit/ingest_exception_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp) |

## B0009

[Lines 63–63](../../../../../tests/unit/ingest_exception_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp) |

## B0010

[Lines 64–64](../../../../../tests/unit/ingest_exception_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp) |

## B0011

[Lines 65–65](../../../../../tests/unit/ingest_exception_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp) |

## B0012

[Lines 66–66](../../../../../tests/unit/ingest_exception_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp) |

## B0013

[Lines 67–80](../../../../../tests/unit/ingest_exception_test.cpp#L67); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L80:sha256:36eae0051fbe8d92d11cc8c92857f7269593835882072e82e6cfa5e55443bc99
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ingest_exception_test.cpp: bind local aliases/name imports; require 4 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 81–83](../../../../../tests/unit/ingest_exception_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp) |

## B0016

[Lines 85–95](../../../../../tests/unit/ingest_exception_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one action to throw crown::api::Error with the requested code. |
| inputs / outputs | Forwards action and compares failure.code(); returns on match. |
| invariants | Catches only Error; bad_alloc and other exceptions propagate; wrong code fails through check. |
| ownership | Action/code view are borrowed; helper retains no session. |
| failure | No matching Error or wrong code throws test runtime_error. |
| cost | One action call and exact code comparison. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0018

[Lines 97–99](../../../../../tests/unit/ingest_exception_test.cpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog make_catalog() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the small source catalog shared by codec and runtime replay fixtures. |
| inputs / outputs | No arguments; returns catalog version 53 with R(x:int64,label:string), source version 4. |
| invariants | Fixture event rows are full two-column physical rows and table id 0. |
| ownership | The returned catalog owns its names/schema values. |
| failure | Catalog construction allocation errors propagate. |
| cost | Builds fixed one-table metadata. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md), [docs/ingestion.md §CSV and explicit legacy profiles](../../../../ingestion.md) |

## B0020

[Lines 101–103](../../../../../tests/unit/ingest_exception_test.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row row(std::int64_t x, std::string label) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one two-column physical Row from an integer and moved string. |
| inputs / outputs | Takes x and label; returns a value-owned Row in catalog column order. |
| invariants | No schema validation occurs in this helper; callers use the fixed R catalog. |
| ownership | The returned row owns its string value. |
| failure | Row/string allocation errors propagate. |
| cost | Creates two scalar values. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp) |

## B0022

[Lines 105–109](../../../../../tests/unit/ingest_exception_test.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputEvent event(std::uint64_t sequence, std::int64_t x, std::string label,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an insert InputEvent with optional source-position metadata. |
| inputs / outputs | Takes sequence, x, label and optional SourcePosition; returns update for table 0. |
| invariants | Operation is always insert and values are in the fixed catalog order. |
| ownership | The returned event owns its Row and optional source string. |
| failure | Construction/allocation errors propagate. |
| cost | Fixed row/event construction. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md), [docs/ingestion.md §CSV and explicit legacy profiles](../../../../ingestion.md) |

## B0024

[Lines 111–117](../../../../../tests/unit/ingest_exception_test.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_event(const auto& left, const InputEvent& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare an EventReader view with the owning fixture InputEvent field by field. |
| inputs / outputs | Borrowed decoded view and expected event in; Boolean equality result out. |
| invariants | Compares sequence, table, operation, row values and optional source position; it does not acknowledge input. |
| ownership | Both inputs are borrowed for the call and no view is retained. |
| failure | No exception translation; comparison allocation behavior is not fault-injected here. |
| cost | Compares a fixed number of event fields and row values. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md) |

## B0025

[Lines 118–130](../../../../../tests/unit/ingest_exception_test.cpp#L118); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L130:sha256:e9215aea7b7910089e76e28ab7d840dbe3b130fc6ac6b1460896cf11c5654b05
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ingest_exception_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 131–140](../../../../../tests/unit/ingest_exception_test.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Fixture() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the JSONL, binary and CSV event fixture plus initial source progress/options. |
| inputs / outputs | No arguments; populates a catalog, one event, encoded bytes, CSV text and per-format InputOptions. |
| invariants | Initial accepted sequence is zero with old-source offset 3; new event carries source-A offset 100, while CSV expected position includes the header bytes. |
| ownership | Fixture owns all strings, catalog, input event, progress and option values used by later readers. |
| failure | Encoding or storage allocation errors propagate from member initialization/construction. |
| cost | Writes one JSON and one binary event and prepares one short CSV record. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md), [docs/ingestion.md §CSV and explicit legacy profiles](../../../../ingestion.md), [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp) |

## B0028

[Lines 142–146](../../../../../tests/unit/ingest_exception_test.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::string_view bytes(InputFormat format) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a borrowed encoded byte view selected by the requested input format. |
| inputs / outputs | InputFormat in; string_view into Fixture JSON, binary or CSV storage out. |
| invariants | The helper is used only with JSONL, binary and CSV enum values in this executable. |
| ownership | The view remains valid only while the Fixture and selected string remain alive and unchanged. |
| failure | No validation for unsupported enum values; the final branch returns the CSV view. |
| cost | Constant-time format branch; no bytes are copied. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0030

[Lines 148–152](../../../../../tests/unit/ingest_exception_test.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  InputOptions options(InputFormat format) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the format-specific InputOptions value for a reader fixture. |
| inputs / outputs | InputFormat in; JSON defaults, binary format, or CSV table/delimiter/source/byte-origin options out by value. |
| invariants | Only the selected format settings differ; unrelated options remain defaults. |
| ownership | Returned option strings/maps are copied and owned by the caller. |
| failure | Copy allocation errors propagate. |
| cost | Copies a bounded options value. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0032

[Lines 154–158](../../../../../tests/unit/ingest_exception_test.cpp#L154); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  InputEvent expected(InputFormat format) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the expected owning event for each fixture codec. |
| inputs / outputs | InputFormat in; original JSON/binary event or CSV event with source-A offset after the header out. |
| invariants | CSV source offset is byte origin 100 plus the exact header record length; JSONL/binary preserve the event’s encoded position. |
| ownership | Returns a separate InputEvent value; strings/rows are owned by it. |
| failure | Copies may allocate; no injected retry is performed in this helper. |
| cost | One format branch plus bounded value copy. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md), [docs/ingestion.md §CSV and explicit legacy profiles](../../../../ingestion.md) |

## B0034

[Lines 160–164](../../../../../tests/unit/ingest_exception_test.cpp#L160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::uint64_t expected_bytes_read(InputFormat format) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the raw fixture byte count expected after one complete decoded record. |
| inputs / outputs | InputFormat in; JSON, binary or whole CSV fixture byte length out. |
| invariants | CSV count includes its header and record framing; the value is compared with EventReader bytes_read, not accepted progress. |
| ownership | Returns a scalar; it borrows no fixture after return. |
| failure | No format validation beyond the helper’s final CSV branch. |
| cost | Constant-time size read. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md) |

## B0035

[Lines 165–166](../../../../../tests/unit/ingest_exception_test.cpp#L165); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L165-L166:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ingest_exception_test.cpp: struct Fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0036

[Lines 167–174](../../../../../tests/unit/ingest_exception_test.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::unique_ptr<io::EventReader> make_reader(const Fixture& fixture,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an EventReader using the fixture’s borrowed stream and per-format configuration. |
| inputs / outputs | Fixture/format, lvalue istringstream and InputProgress in; unique_ptr&lt;EventReader&gt; out. |
| invariants | Reader borrows the supplied stream, copies/retains catalog options and starts from the supplied accepted progress. |
| ownership | Caller must keep stream alive longer than the returned reader; the unique_ptr owns only the EventReader facade/state. |
| failure | Construction errors propagate; reader construction does not itself consume an event record. |
| cost | Creates one reader and copies bounded options/progress. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp) |

## B0038

[Lines 176–189](../../../../../tests/unit/ingest_exception_test.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_fresh_recreated_event(const Fixture& fixture, InputFormat format) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Demonstrate explicit reader recreation after a failed reader or constructor attempt. |
| inputs / outputs | Fixture/format in; creates a fresh stream and reader, peeks the expected event, then explicitly acknowledges it. |
| invariants | Progress is unchanged by peek and advances to sequence 1 plus the format-specific source-A offset only after acknowledge. |
| ownership | The local stream outlives its reader; decoded view is borrowed until acknowledgement, which releases the cached record. |
| failure | Any mismatch throws the local test failure; this does not resume a consumed/poisoned reader instance. |
| cost | One fresh reader construction, decode, compare and acknowledge. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md) |

## B0040

[Lines 191–197](../../../../../tests/unit/ingest_exception_test.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string edge_line(const Catalog& catalog, std::uint64_t sequence,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a self-join edge update as one JSONL physical event. |
| inputs / outputs | Catalog, sequence, x/z and optional SourcePosition in; encoded JSON line with trailing newline out. |
| invariants | Table id is zero and operation is insert; event values are full physical edge columns. |
| ownership | Returned string owns encoded bytes; moved event fields do not escape separately. |
| failure | JSON writer/validation errors propagate. |
| cost | One record serialization. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md), [docs/ingestion.md §CSV and explicit legacy profiles](../../../../ingestion.md) |

## B0042

[Lines 199–234](../../../../../tests/unit/ingest_exception_test.cpp#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep_reader_construction(const Fixture& fixture, InputFormat format) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary-new failure points while constructing EventReader for JSONL, binary and CSV. |
| inputs / outputs | Fixture/format in; failure-point count out after construction sweep succeeds. |
| invariants | Only EventReader construction is inside FaultScope; on bad_alloc the borrowed stream is not consumed and a distinct fresh stream/reader explicitly decodes and accepts the same bytes. |
| ownership | Each point owns its stream/schema/options/progress; reader is local to the attempted construction and never owns the stream. |
| failure | Observed constructor bad_allocs are retried by recreation; other exceptions fail the test; maximum is 2048 points. |
| cost | Up to 2048 reader constructions per format; this is not a time bound or all-allocator failure sweep. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md) |

## B0044

[Lines 236–284](../../../../../tests/unit/ingest_exception_test.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep_reader_peek(const Fixture& fixture, InputFormat format) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary-new failures during one EventReader peek and separate sticky parser/progress failure from success. |
| inputs / outputs | Fixture/format in; failure-point count out after one full deterministic sweep reaches a nonfailing point. |
| invariants | Failed peek marks the reader sticky, leaves accepted progress and records_read at their prior values, may consume all raw bytes, and requires a fresh reader; successful peek caches one stable view until explicit acknowledgement. |
| ownership | Reader borrows the loop-local stream; decoded pointer is reader-owned and invalidated by acknowledge/move/destruction. |
| failure | A failed reader’s later peek must report input_failed; same reader is not retryable. Ack is attempted under fail-after zero and accepted position must then advance. |
| cost | Up to 4096 deterministic failure points per format, including failures after full-record byte consumption; not a broad allocator census. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md) |

## B0046

[Lines 286–342](../../../../../tests/unit/ingest_exception_test.cpp#L286); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void acknowledgement_and_lifetime_are_noalloc(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check acknowledgement, move assignment and reader destruction while intercepted ordinary new is forced to fail. |
| inputs / outputs | Fixture in; runs new-source and existing-source progress cases for all three formats, then moves/destroys cached readers under fail-after zero. |
| invariants | A new source-position node is prepared before acknowledgement; an existing source uses its saved iterator; move/destruction must retain/release cached reader state without requesting intercepted ordinary new. |
| ownership | The stream remains caller-owned; moved reader owns its cached event/progress, and destruction releases that owned state. |
| failure | Any request through the direct ordinary-new replacements throws and fails the test; direct malloc/account/system paths are not denied by this scope. |
| cost | Six format/source acknowledgement checks plus fixed move/assignment/destruction operations. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp) |

## B0048

[Lines 344–430](../../../../../tests/unit/ingest_exception_test.cpp#L344); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sweep_catalog_digest_and_codecs(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep codec/catalog writer allocations, compare deterministic bytes, and enforce a short record budget before a payload-sized ordinary-new request. |
| inputs / outputs | Fixture in; digest and JSON/binary writer fault points are swept, with tight-budget 32 KiB payload cases checked separately. |
| invariants | Clean digest/encoded JSON/binary bytes are stable across intercepted ordinary-new failures; tight record_bytes=128 must reject while largest directly intercepted ordinary-new request stays below 4096. |
| ownership | Writer outputs and digest strings are caller-owned; fixture inputs are retained independently. |
| failure | Bad allocation is expected under persistent fail-after for writers and at selected sweep points; tight budget must raise resource_limit, not an injected allocation error. |
| cost | Up to 2048 points per digest/writer sweep; byte-size bound counts only requested bytes routed through this file’s ordinary-new replacements. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md), [docs/ingestion.md §CSV and explicit legacy profiles](../../../../ingestion.md), [docs/ingestion.md §Budgets and diagnostic command](../../../../ingestion.md) |

## B0050

[Lines 432–442](../../../../../tests/unit/ingest_exception_test.cpp#L432); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_root_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the one-table R(x,label) plan used by ordered replay and parser-failure sweeps. |
| inputs / outputs | No arguments; returns a PhysicalPlan projecting x and label from physical table R. |
| invariants | The plan catalog matches Fixture catalog version/schema and preserves full source rows. |
| ownership | Returns an owned PhysicalPlan; no runtime or reader is created here. |
| failure | Planner lowering errors propagate. |
| cost | Builds one fixed native source node and lowers it. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0052

[Lines 444–457](../../../../../tests/unit/ingest_exception_test.cpp#L444); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_self_join_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a self-join edge plan for alias-fanout and output-busy replay cases. |
| inputs / outputs | No arguments; returns E(x,z) joined with E(z,y), projecting x,z,y. |
| invariants | Both occurrences use one physical table and share z; seed and fanout events operate on set rows. |
| ownership | Returns a value-owned plan; runtime epochs own later source/output state. |
| failure | Planner validation/lowering errors propagate. |
| cost | Builds two fixed occurrences and lowers one small join tree. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0054

[Lines 459–470](../../../../../tests/unit/ingest_exception_test.cpp#L459); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json normalized_owners(io::Json value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize owner identifiers recursively in a serialized support image for state comparison. |
| inputs / outputs | JSON value by value in; JSON value with every object member named owner set to zero out. |
| invariants | All non-owner keys, values, arrays and object structure are preserved by the recursive mutation. |
| ownership | Input is copied into the parameter and returned JSON owns its tree. |
| failure | JSON allocation errors propagate; malformed JSON values are preserved unless they contain owner fields. |
| cost | Visits every JSON object/array member once. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp) |

## B0056

[Lines 472–478](../../../../../tests/unit/ingest_exception_test.cpp#L472); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RuntimeImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the comparable runtime image used to compare committed physical/delta state across retries. |
| inputs / outputs | Stores sequence, answer flag, physical relation vector and normalized support JSON; default equality compares fields. |
| invariants | Owner identifiers are normalized before populating support; the image does not include transient output ownership or input progress. |
| ownership | Relations and JSON are value-owned snapshots, independent of the runtime after construction. |
| failure | Snapshot/serialization/copy failures propagate to the caller. |
| cost | Storage scales with the captured physical relation and support snapshot. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp) |

## B0058

[Lines 480–489](../../../../../tests/unit/ingest_exception_test.cpp#L480); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RuntimeImage image(const PhysicalRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a committed PhysicalRuntime into RuntimeImage for rollback/retry comparisons. |
| inputs / outputs | PhysicalRuntime reference in; sequence, has_answer, physical tables and normalized serialized support out. |
| invariants | The snapshot is observational; it does not mutate the runtime or include replay progress. |
| ownership | Returned image owns copied row relations and support JSON; runtime is borrowed. |
| failure | Snapshot, serialization or allocation errors propagate. |
| cost | Work/output are proportional to retained physical and support state. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/delta_runtime.md §One physical input](../../../../delta_runtime.md), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp) |

## B0060

[Lines 491–500](../../../../../tests/unit/ingest_exception_test.cpp#L491); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RuntimeImage image(const DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a committed DeltaRuntime into the same normalized RuntimeImage shape. |
| inputs / outputs | DeltaRuntime reference in; sequence, answer, physical tables and serialized support out. |
| invariants | Transient Epoch output is not part of this image; the caller separately drains/compares output where required. |
| ownership | Returned image is an owning copy; runtime is borrowed. |
| failure | Snapshot/serialization failures propagate. |
| cost | Work/output scale with captured physical/support state. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md §One physical input](../../../../delta_runtime.md), [docs/delta_runtime.md §Output, mapping and ownership](../../../../delta_runtime.md), [docs/delta_runtime.md §Modes and bounded spool](../../../../delta_runtime.md), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp) |

## B0062

[Lines 502–506](../../../../../tests/unit/ingest_exception_test.cpp#L502); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::InputProgress progress_at(std::uint64_t sequence) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create accepted input progress with only a sequence value for replay starting points. |
| inputs / outputs | Sequence integer in; InputProgress with empty source-position map and that sequence out. |
| invariants | No source offset is fabricated; later replay positions are added by EventReader acknowledgement. |
| ownership | Returns an owning value with no borrowed fields. |
| failure | No test-specific failure translation. |
| cost | Scalar initialization. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0064

[Lines 508–513](../../../../../tests/unit/ingest_exception_test.cpp#L508); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string line(const Catalog& catalog, std::uint64_t sequence, std::int64_t x,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize an insert row as JSONL with optional source-position metadata. |
| inputs / outputs | Catalog, sequence, x/label and optional position in; owned JSON line with newline out. |
| invariants | Table id is zero, operation is insert and all physical source columns are serialized. |
| ownership | Returned bytes are owned by the string; moved label/position are stored in the local event then encoded. |
| failure | Writer validation/allocation failures propagate. |
| cost | One record encoding. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md), [docs/ingestion.md §CSV and explicit legacy profiles](../../../../ingestion.md) |

## B0066

[Lines 515–519](../../../../../tests/unit/ingest_exception_test.cpp#L515); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string root_line(const PhysicalPlan& plan, std::uint64_t sequence,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one ordered replay input with source id replay-source and an explicit byte offset. |
| inputs / outputs | Plan, sequence, x/label and offset in; JSONL line bound to plan.catalog out. |
| invariants | Event source position is replay-source/offset; row is complete and sequence is supplied by caller. |
| ownership | Returned string owns encoded bytes. |
| failure | JSON writer errors propagate. |
| cost | One record serialization. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/ingestion.md §Version-1 JSONL event](../../../../ingestion.md), [docs/ingestion.md §Version-1 binary frame](../../../../ingestion.md), [docs/ingestion.md §CSV and explicit legacy profiles](../../../../ingestion.md), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0067

[Lines 520–527](../../../../../tests/unit/ingest_exception_test.cpp#L520); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L520-L527:sha256:ae03473bbf095d7c79a5059c91f8cef682fcf57210f25f03467db9ee9f4a2600
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ingest_exception_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0068

[Lines 528–534](../../../../../tests/unit/ingest_exception_test.cpp#L528); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  explicit HeldSourcePin(PhysicalEpoch committed) : epoch(std::move(committed)) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain and fingerprint a committed source-row pin from a PhysicalEpoch. |
| inputs / outputs | Committed epoch by value in; moves it into the member and captures source tuple/arena handles, exported row and normalized support journal. |
| invariants | Construction requires a retained source; the saved handles and journal are comparison baselines, not database copies. |
| ownership | The HeldSourcePin owns the PhysicalEpoch and therefore its retained source/support journals; copied Row/JSON are independent values. |
| failure | Missing source or serialization/allocation failure fails the test through check or propagates. |
| cost | Copies one retained row and serializes its support epoch. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/delta_runtime.md §One physical input](../../../../delta_runtime.md), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp) |

## B0070

[Lines 536–543](../../../../../tests/unit/ingest_exception_test.cpp#L536); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void check_unchanged() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert a retained seed source row and older support journal remain unchanged during replay attempts. |
| inputs / outputs | No arguments; reads the HeldSourcePin-owned epoch and compares handles, tuple values and normalized journal JSON. |
| invariants | Checks exact tuple/arena handle identity plus values and journal content; does not substitute for the full RuntimeImage comparison. |
| ownership | Reads its own retained epoch and saved copies; no runtime is borrowed. |
| failure | Any difference throws the test failure; serialization errors propagate. |
| cost | Compares one row and traverses/serializes the retained support journal. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/delta_runtime.md §One physical input](../../../../delta_runtime.md), [include/crown/io/support.hpp](../../../../../include/crown/io/support.hpp) |

## B0071

[Lines 544–545](../../../../../tests/unit/ingest_exception_test.cpp#L544); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L544-L545:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ingest_exception_test.cpp: struct HeldSourcePin. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0072

[Lines 546–617](../../../../../tests/unit/ingest_exception_test.cpp#L546); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep_ordered_physical_apply(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary-new failures through OrderedReplay applying one cached event to a PhysicalRuntime. |
| inputs / outputs | Plan in; each point creates a seed runtime/pin, reader with progress 1, cached sequence-2 event, then applies under FaultScope; returns failure count at first successful point. |
| invariants | On bad_alloc, committed sequence/progress, cached-view identity, healthy reader, RuntimeImage and held source/journal pin remain unchanged; retry uses the same replay and runtime owner and must match a clean two-event image. |
| ownership | Reader borrows the local stream; HeldSourcePin owns the old epoch; replay owns reader state; successful PhysicalEpoch is local output. |
| failure | Only intercepted ordinary-new requests are fail-after injected; direct malloc/realloc/system/account denials are outside the seam. Non-allocation errors fail the test. |
| cost | Up to 8192 full runtime setups/retries; no CPU-time or all-allocator bound is asserted. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/delta_runtime.md §One physical input](../../../../delta_runtime.md) |

## B0074

[Lines 619–658](../../../../../tests/unit/ingest_exception_test.cpp#L619); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sparse_replay_does_not_copy_the_existing_database(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound directly intercepted ordinary-new request bytes for one sparse replay step after seeding 900 rows. |
| inputs / outputs | Physical plan in; seeds 900 existing rows, constructs one new JSON event, then records replacement-new request bytes/count/largest around apply_next. |
| invariants | Seed count stays below the arena geometric slot-capacity boundary; sequence/progress advance once and snapshot contains 901 rows; the asserted byte bound is total requests through this file’s ordinary-new replacements below 900*sizeof(Row). |
| ownership | Runtime owns source state; reader borrows the local stream; output and snapshots are value/owner objects scoped to the helper. |
| failure | Replay errors propagate; the bound does not cover direct malloc/realloc/system calls, custom MemoryAccount paths, or possible indirect nothrow delegation. |
| cost | Performs 900 seed applies plus one replay and a full snapshot/invariant check; it is not a time or process-heap claim. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/delta_runtime.md §One physical input](../../../../delta_runtime.md), [docs/ingestion.md §Budgets and diagnostic command](../../../../ingestion.md) |

## B0076

[Lines 660–669](../../../../../tests/unit/ingest_exception_test.cpp#L660); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions ordered_delta_options(std::size_t spool_rows = 65536,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build ordered delta replay options with maintenance-mode setup and bounded output spool limits. |
| inputs / outputs | Optional spool row/byte limits in; DeltaOptions out with completion ordered_replay and live maintenance on_output. |
| invariants | Requested mode starts maintenance; callers explicitly switch to delta when output is needed. |
| ownership | Returns an owning options value. |
| failure | Invalid option combinations are rejected later by DeltaRuntime construction/use. |
| cost | Fixed scalar option initialization. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md §One physical input](../../../../delta_runtime.md), [docs/delta_runtime.md §Output, mapping and ownership](../../../../delta_runtime.md), [docs/delta_runtime.md §Modes and bounded spool](../../../../delta_runtime.md) |

## B0078

[Lines 671–677](../../../../../tests/unit/ingest_exception_test.cpp#L671); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::tuple<std::uint64_t, SetOperation, Row>> drain_delta(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain all remaining rows from a committed DeltaRuntime Epoch into an owning comparison vector. |
| inputs / outputs | Epoch reference in; vector of ordinal, operation and exported Row values out. |
| invariants | Preserves returned order and one-based epoch ordinals; tuple values are copied before the owning record is destroyed. |
| ownership | Vector rows own their values independently of the epoch/runtime. |
| failure | Vector/export allocation errors propagate. |
| cost | Visits each remaining output record once; cost is output-sensitive. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md §One physical input](../../../../delta_runtime.md), [docs/delta_runtime.md §Output, mapping and ownership](../../../../delta_runtime.md), [docs/delta_runtime.md §Modes and bounded spool](../../../../delta_runtime.md) |

## B0080

[Lines 679–682](../../../../../tests/unit/ingest_exception_test.cpp#L679); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaCleanImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle the clean delta replay state image and fully drained ordered output. |
| inputs / outputs | Contains RuntimeImage plus vector of ordinal/operation/Row triples; equality is not customized. |
| invariants | State and output are separate comparison dimensions; normalized owner IDs are only in RuntimeImage support JSON. |
| ownership | Both fields own copied values and do not depend on the DeltaRuntime or Epoch. |
| failure | Member construction/copy errors propagate. |
| cost | Storage is proportional to state image and all emitted rows. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md §Output, mapping and ownership](../../../../delta_runtime.md) |

## B0082

[Lines 684–698](../../../../../tests/unit/ingest_exception_test.cpp#L684); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaCleanImage clean_delta_single_event(const PhysicalPlan& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce the clean same-implementation reference image/output for one ordered delta event. |
| inputs / outputs | Plan, encoded event and starting sequence in; creates DeltaRuntime, sets delta mode, applies one reader event, drains output and captures image. |
| invariants | The comparator is an un-faulted run of the same runtime/replay code, not an independent A04 evaluator. |
| ownership | Local runtime owns live state; reader borrows the local stream; returned DeltaCleanImage owns output and snapshot copies. |
| failure | Construction, apply, drain or image errors propagate. |
| cost | Processes one event and all its result rows; output/snapshot cost depends on fixture state. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md §One physical input](../../../../delta_runtime.md), [docs/delta_runtime.md §Output, mapping and ownership](../../../../delta_runtime.md), [docs/delta_runtime.md §Modes and bounded spool](../../../../delta_runtime.md) |

## B0084

[Lines 700–760](../../../../../tests/unit/ingest_exception_test.cpp#L700); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep_ordered_delta_apply(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary-new failures through one ordered DeltaRuntime replay and verify same-owner cached-event retry. |
| inputs / outputs | Plan in; encodes sequence-1 event, computes clean same-implementation image, then repeats fresh runtime/replay apply under fail-after; returns failure count on first success. |
| invariants | Each bad_alloc leaves runtime sequence/image and replay progress at zero, reader healthy and cached view identical; retry on the same runtime/replay must match the clean output vector and normalized state. |
| ownership | Reader borrows each point’s stream; returned Epoch owns output until drained; RuntimeImage/DeltaCleanImage are value copies. |
| failure | Only requests through ordinary throwing scalar/array new replacements are injected; direct malloc/realloc/system/account denials and unknown indirect delegation are not covered. |
| cost | Up to 16384 full setup/apply/retry points; no CPU-time guarantee. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md §One physical input](../../../../delta_runtime.md), [docs/delta_runtime.md §Output, mapping and ownership](../../../../delta_runtime.md), [docs/delta_runtime.md §Modes and bounded spool](../../../../delta_runtime.md) |

## B0086

[Lines 762–835](../../../../../tests/unit/ingest_exception_test.cpp#L762); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void parser_oom_precedes_engine_and_late_truncation_is_sticky() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish parser allocation failure from engine apply failure after one accepted ordered record. |
| inputs / outputs | Two JSONL events in one stream; first commits, then fail-after sweeps the second apply and returns after observing parser-failure points and a clean point. |
| invariants | Sticky reader failure leaves runtime/progress at sequence 1 and requires a newly constructed reader over the unaccepted second record; engine bad_alloc leaves the decoded view cached and retries it on the same replay/runtime owner. |
| ownership | Original reader borrows its stream; explicit parser recovery uses a fresh stream/replay seeded with accepted sequence/source offset; engine retry retains the original reader. |
| failure | Injected ordinary-new failures only; parser and engine paths have distinct recovery behavior and other exception types propagate. |
| cost | At most 4096 deterministic failure points, each rebuilding runtime and replay; no time bound. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md) |

## B0088

[Lines 837–889](../../../../../tests/unit/ingest_exception_test.cpp#L837); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void late_truncated_binary_and_output_busy_keep_progress() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check sticky rejection of a truncated later binary frame and retry of a cached event after delta output blocks input. |
| inputs / outputs | Plan and two binary frames in; first commits, truncated second must fail; separate self-join stream holds sequence-2 output while sequence 3 is cached, then drains and retries it. |
| invariants | Malformed reader preserves prior sequence/physical row and becomes failed; runtime_busy leaves healthy cached event/progress unchanged; draining committed output releases input admission but never rewinds sequence 2. |
| ownership | Readers borrow local streams; held DeltaRuntime Epoch owns the outstanding output lease; drained records are copied by drain_delta. |
| failure | Expects invalid_document for truncation and runtime_busy for active output; retry occurs only after the held epoch is drained. |
| cost | Decodes two frames and processes three self-join events; output work is fixture-dependent. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [docs/delta_runtime.md §Output, mapping and ownership](../../../../delta_runtime.md) |

## B0090

[Lines 891–921](../../../../../tests/unit/ingest_exception_test.cpp#L891); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void alias_fanout_quota_rollback_retains_cached_input() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify an output spool row-quota rejection preserves the cached alias-fanout event and old delta state. |
| inputs / outputs | Seeds two edge rows in maintenance mode, switches to delta, then replays a third self-join edge with zero spool-row limit. |
| invariants | resource_limit is a logical quota path, not a bad_alloc injection; runtime stays sequence 2/ready with identical image, replay progress stays at 2, and cached event pointer/reader health remain unchanged. |
| ownership | Reader borrows the event stream; runtime owns seed state; no committed output Epoch is returned on quota failure. |
| failure | Quota failure is expected and leaves the same cached event available; no allocation-fault retry is performed. |
| cost | Two seed applications, one bounded failing update, image and invariant checks. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md §One physical input](../../../../delta_runtime.md), [docs/delta_runtime.md §Output, mapping and ownership](../../../../delta_runtime.md), [docs/delta_runtime.md §Modes and bounded spool](../../../../delta_runtime.md) |

## B0091

[Lines 922–924](../../../../../tests/unit/ingest_exception_test.cpp#L922); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L922-L924:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ingest_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0092

[Lines 925–954](../../../../../tests/unit/ingest_exception_test.cpp#L925); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the reader, codec, physical replay, delta replay and quota fixtures and report their observed fault-point counts. |
| inputs / outputs | No explicit arguments are used; constructs Fixture and plans, calls every named sweep/check, then prints counters. |
| invariants | The executable defines only the ordinary throwing scalar/array replacement seam; invoking main is not evidence in this review packet. |
| ownership | Objects are local to main/helpers; EventReader borrows each local stream and runtime/epoch owners follow their own RAII lifetimes. |
| failure | Any test exception is printed and returns 1; the code does not catch every non-standard exception. |
| cost | Runs bounded loops up to 2048/4096/8192/16384 points plus finite fixtures; no runtime or CPU timing claim. |
| Design | [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/ingestion.md §Reader acceptance and engine replay](../../../../ingestion.md), [docs/ingestion.md §Budgets and diagnostic command](../../../../ingestion.md) |
