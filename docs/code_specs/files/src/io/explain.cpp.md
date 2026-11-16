# `src/io/explain.cpp` — block usage map

[Source](../../../../../src/io/explain.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `0305c0c73bcdea56e7a81ce8045b69f609c22f6d9fd133c5b04d4ed3fff7f1de`. 602 lines partitioned into 87 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../src/io/explain.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 15–33](../../../../../src/io/explain.cpp#L15) | Callable definition: void utf8(std::string_view text) | calls size, Error; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 34–38](../../../../../src/io/explain.cpp#L34) | declares types or opens a type body. | source comment (unverified): // Private streaming text: the cap bounds encoded length, not string capacity · [reviewed contract](#b0003) |
| [B0004 · 39–39](../../../../../src/io/explain.cpp#L39) | Callable definition: explicit Writer(std::size_t bytes):limit(bytes) | calls limit · [reviewed contract](#b0004) |
| [B0005 · 40–40](../../../../../src/io/explain.cpp#L40) | Callable definition: std::size_t remaining() const noexcept | calls size; returns limit-out.size() · [reviewed contract](#b0005) |
| [B0006 · 41–44](../../../../../src/io/explain.cpp#L41) | Callable definition: void raw(std::string_view value) | calls size, Error, append · [reviewed contract](#b0006) |
| [B0007 · 45–45](../../../../../src/io/explain.cpp#L45) | Explanatory comments or spacing. | source comment (unverified): // UTF-8 is a transport rule; raw checks also admit each escaping expansion. · [reviewed contract](#b0007) |
| [B0008 · 46–57](../../../../../src/io/explain.cpp#L46) | Callable definition: void quote(std::string_view value,bool dot=false) | calls size, remaining, Error, utf8; 1 loop sites; source comment (unverified): // UTF-8 is a transport rule; raw checks also admit each escaping expansion. · [reviewed contract](#b0008) |
| [B0009 · 58–62](../../../../../src/io/explain.cpp#L58) | Callable definition: template&lt;class Integer&gt; void number(Integer value) | calls std::to_chars, Error, raw · [reviewed contract](#b0009) |
| [B0010 · 63–63](../../../../../src/io/explain.cpp#L63) | Callable definition: void boolean(bool value) | calls raw · [reviewed contract](#b0010) |
| [B0011 · 64–64](../../../../../src/io/explain.cpp#L64) | Callable definition: void null() | calls raw · [reviewed contract](#b0011) |
| [B0012 · 65–65](../../../../../src/io/explain.cpp#L65) | Callable definition: template&lt;class T&gt; void optional(const std::optional&lt;T&gt;& value) | calls number, null · [reviewed contract](#b0012) |
| [B0013 · 66–68](../../../../../src/io/explain.cpp#L66) | Callable definition: template&lt;class Range,class Fn&gt; void array(const Range& values,Fn fn) | calls raw, fn; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 69–76](../../../../../src/io/explain.cpp#L69) | Type/record definition: struct Object |  · [reviewed contract](#b0014) |
| [B0015 · 77–77](../../../../../src/io/explain.cpp#L77) | Callable definition: template&lt;class Fn&gt; void object(Fn fn) | calls raw, fn · [reviewed contract](#b0015) |
| [B0016 · 78–78](../../../../../src/io/explain.cpp#L78) | Callable definition: template&lt;class Range&gt; void ids(const Range& values) | calls array, number · [reviewed contract](#b0016) |
| [B0017 · 79–80](../../../../../src/io/explain.cpp#L79) | controls preprocessing. | returns #Item · [reviewed contract](#b0017) |
| [B0018 · 81–84](../../../../../src/io/explain.cpp#L81) | Callable definition: const char* name(PhysicalRoute value) | calls CASE, Error · [reviewed contract](#b0018) |
| [B0019 · 85–88](../../../../../src/io/explain.cpp#L85) | Callable definition: const char* name(NodeKind value) | calls CASE, Error · [reviewed contract](#b0019) |
| [B0020 · 89–89](../../../../../src/io/explain.cpp#L89) | Callable definition: const char* name(DeltaMode value) | calls CASE, Error · [reviewed contract](#b0020) |
| [B0021 · 90–90](../../../../../src/io/explain.cpp#L90) | Callable definition: const char* name(LiveMaintenance value) | calls CASE, Error · [reviewed contract](#b0021) |
| [B0022 · 91–91](../../../../../src/io/explain.cpp#L91) | Callable definition: const char* name(DeltaCompletion value) | calls CASE, Error · [reviewed contract](#b0022) |
| [B0023 · 92–92](../../../../../src/io/explain.cpp#L92) | Callable definition: const char* name(ResultView value) | calls CASE, Error · [reviewed contract](#b0023) |
| [B0024 · 93–93](../../../../../src/io/explain.cpp#L93) | Callable definition: const char* name(PropagationOrder value) | calls CASE, Error · [reviewed contract](#b0024) |
| [B0025 · 94–94](../../../../../src/io/explain.cpp#L94) | Callable definition: const char* name(ObservationMode value) | calls CASE, Error · [reviewed contract](#b0025) |
| [B0026 · 95–98](../../../../../src/io/explain.cpp#L95) | Callable definition: const char* name(DeltaState value) | calls CASE, Error · [reviewed contract](#b0026) |
| [B0027 · 99–99](../../../../../src/io/explain.cpp#L99) | Callable definition: const char* name(ObservationLayer value) | calls CASE, Error · [reviewed contract](#b0027) |
| [B0028 · 100–100](../../../../../src/io/explain.cpp#L100) | Callable definition: const char* name(ObservationOutcome value) | calls CASE, Error · [reviewed contract](#b0028) |
| [B0029 · 101–101](../../../../../src/io/explain.cpp#L101) | Callable definition: const char* name(MetricAvailability value) | calls CASE, Error · [reviewed contract](#b0029) |
| [B0030 · 102–102](../../../../../src/io/explain.cpp#L102) | Callable definition: const char* name(MetricKind value) | calls CASE, Error · [reviewed contract](#b0030) |
| [B0031 · 103–106](../../../../../src/io/explain.cpp#L103) | Callable definition: const char* name(TraceDisposition value) | calls CASE, Error · [reviewed contract](#b0031) |
| [B0032 · 107–107](../../../../../src/io/explain.cpp#L107) | Callable definition: const char* name(planner::CandidateSource value) | calls CASE, Error · [reviewed contract](#b0032) |
| [B0033 · 108–114](../../../../../src/io/explain.cpp#L108) | Callable definition: const char* name(planner::CandidateFamily value) | calls Error; returns @; @ · [reviewed contract](#b0033) |
| [B0034 · 115–121](../../../../../src/io/explain.cpp#L115) | Callable definition: const char* exhaustion_scope(planner::CandidateFamily value) | calls Error; returns @; @ · [reviewed contract](#b0034) |
| [B0035 · 122–122](../../../../../src/io/explain.cpp#L122) | Callable definition: const char* name(observability::RuntimePresence v) | calls CASE, Error · [reviewed contract](#b0035) |
| [B0036 · 123–123](../../../../../src/io/explain.cpp#L123) | Callable definition: const char* name(observability::ExplanationKind v) | calls CASE, Error · [reviewed contract](#b0036) |
| [B0037 · 124–124](../../../../../src/io/explain.cpp#L124) | Callable definition: const char* name(observability::GaugeAvailability v) | calls CASE, Error · [reviewed contract](#b0037) |
| [B0038 · 125–125](../../../../../src/io/explain.cpp#L125) | Callable definition: const char* name(SessionState v) | calls CASE, Error · [reviewed contract](#b0038) |
| [B0039 · 126–126](../../../../../src/io/explain.cpp#L126) | Callable definition: const char* name(SessionPhase v) | calls CASE, Error · [reviewed contract](#b0039) |
| [B0040 · 127–127](../../../../../src/io/explain.cpp#L127) | Callable definition: const char* name(SessionInputKind v) | calls CASE, Error · [reviewed contract](#b0040) |
| [B0041 · 128–128](../../../../../src/io/explain.cpp#L128) | Callable definition: const char* name(InitializationRoute v) | calls CASE, Error · [reviewed contract](#b0041) |
| [B0042 · 129–129](../../../../../src/io/explain.cpp#L129) | Callable definition: const char* name(BuildMethod v) | calls CASE, Error · [reviewed contract](#b0042) |
| [B0043 · 130–130](../../../../../src/io/explain.cpp#L130) | Callable definition: const char* name(io::InputFormat v) | calls CASE, Error · [reviewed contract](#b0043) |
| [B0044 · 131–131](../../../../../src/io/explain.cpp#L131) | Callable definition: const char* name(ResultCursorState v) | calls CASE, Error · [reviewed contract](#b0044) |
| [B0045 · 132–132](../../../../../src/io/explain.cpp#L132) | Callable definition: const char* name(CursorObservationSource v) | calls CASE, Error · [reviewed contract](#b0045) |
| [B0046 · 133–133](../../../../../src/io/explain.cpp#L133) | Callable definition: const char* name(CursorTerminalReason v) | calls CASE, Error · [reviewed contract](#b0046) |
| [B0047 · 134–134](../../../../../src/io/explain.cpp#L134) | Callable definition: const char* name(TraceKind v) | calls CASE, Error · [reviewed contract](#b0047) |
| [B0048 · 135–135](../../../../../src/io/explain.cpp#L135) | Member/declaration region. |  · [reviewed contract](#b0048) |
| [B0049 · 136–139](../../../../../src/io/explain.cpp#L136) | Callable definition: const char* height_status(const PlanExplanation& report) | calls ; returns @; report.height_status()==observability::HeightStatus::verified_original_minimum?@ :@ · [reviewed contract](#b0049) |
| [B0050 · 140–151](../../../../../src/io/explain.cpp#L140) | Callable definition: void scalar(Writer& w,const Value& value) | calls object, text, type_name, type_of · [reviewed contract](#b0050) |
| [B0051 · 152–156](../../../../../src/io/explain.cpp#L152) | Callable definition: void scalar(Writer& w,const storage::ScalarView& value) | calls object, text, field, quote · [reviewed contract](#b0051) |
| [B0052 · 157–163](../../../../../src/io/explain.cpp#L157) | Callable definition: template&lt;class TermView&gt; void term(Writer& w,const TermView& value) | calls object, text, number, field · [reviewed contract](#b0052) |
| [B0053 · 164–192](../../../../../src/io/explain.cpp#L164) | Callable definition: template&lt;class TreeView,class Validation=planner::ValidationReport&gt; void tree(Writer& w,const TreeView& value,const Validation* v… | calls resize, size, at, object; growth resize; 1 loop sites; source comment (unverified): // Diagnostic scratch is linear in the admitted tree size. Do not scan C* · [reviewed contract](#b0053) |
| [B0054 · 193–193](../../../../../src/io/explain.cpp#L193) | Explanatory comments or spacing. | source comment (unverified): // Export the supplied profile verbatim; this is no independent bound checker. · [reviewed contract](#b0054) |
| [B0055 · 194–203](../../../../../src/io/explain.cpp#L194) | Callable definition: void profile(Writer& w,const DeltaRuntimeProfile& p) | calls object, text, boolean; source comment (unverified): // Export the supplied profile verbatim; this is no independent bound checker. · [reviewed contract](#b0055) |
| [B0056 · 204–237](../../../../../src/io/explain.cpp#L204) | Callable definition: void mode(Writer& w,const observability::ModeDescriptor& m) | calls object, text, presence, options; source comment (unverified): // Frozen v2 capability text is not the current sink or ledger status. · [reviewed contract](#b0056) |
| [B0057 · 238–258](../../../../../src/io/explain.cpp#L238) | Callable definition: \[\[maybe_unused\]\] void requested_options(Writer& w,const DeltaOptions& opts) | calls object, text, name, field · [reviewed contract](#b0057) |
| [B0058 · 259–269](../../../../../src/io/explain.cpp#L259) | Callable definition: template&lt;class Configuration&gt; void configuration(Writer& w,const Configuration& c) | calls object, number, format_version, support_owner · [reviewed contract](#b0058) |
| [B0059 · 270–270](../../../../../src/io/explain.cpp#L270) | Callable definition: bool mode_bound(const ObservationSummary& s) | calls has_value; returns s.configuration.has_value() · [reviewed contract](#b0059) |
| [B0060 · 271–274](../../../../../src/io/explain.cpp#L271) | Callable definition: void historical_mode(Writer& w,Writer::Object& o,const ObservationSummary& s) | calls text, field, configuration, null · [reviewed contract](#b0060) |
| [B0061 · 275–277](../../../../../src/io/explain.cpp#L275) | Callable definition: void current_configuration(Writer& w,const ObservationSnapshot& s) | calls configuration, null · [reviewed contract](#b0061) |
| [B0062 · 278–294](../../../../../src/io/explain.cpp#L278) | Callable definition: void summary(Writer& w,const std::optional&lt;ObservationSummary&gt;& value) | calls null, object, number, text; source comment (unverified): // An unavailable metric can retain a stale internal payload. It is not · [reviewed contract](#b0062) |
| [B0063 · 295–299](../../../../../src/io/explain.cpp#L295) | Callable definition: void causal_record(Writer& w,const TraceRecord& r) | calls object, text, name, number · [reviewed contract](#b0063) |
| [B0064 · 300–300](../../../../../src/io/explain.cpp#L300) | Explanatory comments or spacing. |  |
| [B0065 · 301–333](../../../../../src/io/explain.cpp#L301) | Callable definition: void observations(Writer& w,const PlanExplanation& report) | calls object, text, observation, boolean · [reviewed contract](#b0065) |
| [B0066 · 334–362](../../../../../src/io/explain.cpp#L334) | Callable definition: template&lt;class PlanView&gt; void query(Writer& w,const PlanView& plan) | calls object, boolean, field, array · [reviewed contract](#b0066) |
| [B0067 · 363–363](../../../../../src/io/explain.cpp#L363) | Explanatory comments or spacing. |  |
| [B0068 · 364–392](../../../../../src/io/explain.cpp#L364) | Callable definition: void session_status(Writer& w,const PlanExplanation& e) | calls null, observation, object, text · [reviewed contract](#b0068) |
| [B0069 · 393–393](../../../../../src/io/explain.cpp#L393) | Explanatory comments or spacing. |  |
| [B0070 · 394–471](../../../../../src/io/explain.cpp#L394) | Callable definition: void json(Writer& w,const PlanExplanation& e) | calls plan, object, number, text; source comment (unverified): // Historical v2 constants; current component acceptance lives in the ledger. · [reviewed contract](#b0070) |
| [B0071 · 472–484](../../../../../src/io/explain.cpp#L472) | Callable definition: void human_metrics(Writer& w,const char* label,const std::optional&lt;ObservationSummary&gt;& summary_value) | calls raw, number, name, mode_bound; 1 loop sites · [reviewed contract](#b0071) |
| [B0072 · 485–485](../../../../../src/io/explain.cpp#L485) | Explanatory comments or spacing. |  |
| [B0073 · 486–492](../../../../../src/io/explain.cpp#L486) | Callable definition: void human_declared(Writer& w,std::string_view label,const std::shared_ptr&lt;const DeclaredBenchmarkContext&gt;& value) | calls raw, labels, quote, field · [reviewed contract](#b0073) |
| [B0074 · 493–499](../../../../../src/io/explain.cpp#L493) | Callable definition: void human_output(Writer& w,std::string_view label,const std::optional&lt;ObservationSummary&gt;& s) | calls human_declared, raw, boolean, flag · [reviewed contract](#b0074) |
| [B0075 · 500–527](../../../../../src/io/explain.cpp#L500) | Callable definition: void human_integrated(Writer& w,const PlanExplanation& e) | calls raw, name, mode, presence; 1 loop sites · [reviewed contract](#b0075) |
| [B0076 · 528–529](../../../../../src/io/explain.cpp#L528) | Closes surrounding scope/type. |  · [reviewed contract](#b0076) |
| [B0077 · 530–530](../../../../../src/io/explain.cpp#L530) | Callable definition: std::string write_explain_json(const PlanExplanation& report,ExplainTextLimits limits) | calls w, json, std::move; returns std::move(w.out) · [reviewed contract](#b0077) |
| [B0078 · 531–575](../../../../../src/io/explain.cpp#L531) | Callable definition: std::string write_explain_text(const PlanExplanation& report,ExplainTextLimits limits) | calls w, plan, raw, physical_sha256; returns std::move(w.out); 4 loop sites · [reviewed contract](#b0078) |
| [B0079 · 576–577](../../../../../src/io/explain.cpp#L576) | Explanatory comments or spacing. | source comment (unverified): // Caption/label buffers overlap the result; each length cap is not a total · [reviewed contract](#b0079) |
| [B0080 · 578–595](../../../../../src/io/explain.cpp#L578) | Callable definition: std::string write_explain_dot(const PlanExplanation& report,ExplainTextLimits limits) | calls w, plan, raw, caption; returns std::move(w.out); 2 loop sites; source comment (unverified): // Caption/label buffers overlap the result; each length cap is not a total · [reviewed contract](#b0080) |
| [B0081 · 596–596](../../../../../src/io/explain.cpp#L596) | Explanatory comments or spacing. |  |
| [B0082 · 597–597](../../../../../src/io/explain.cpp#L597) | Callable definition: std::string write_explain_tree_json(const PlanExplanation& e,ExplainTextLimits limits) | calls w, object, number, text; returns std::move(w.out) · [reviewed contract](#b0082) |
| [B0083 · 598–598](../../../../../src/io/explain.cpp#L598) | Callable definition: std::string write_explain_json(const observability::QueryExplanation& e,ExplainTextLimits limits) | calls w, object, number, text; returns std::move(w.out) · [reviewed contract](#b0083) |
| [B0084 · 599–599](../../../../../src/io/explain.cpp#L599) | Callable definition: std::string write_explain_text(const observability::QueryExplanation& e,ExplainTextLimits limits) | calls w, raw, write_query_explain_text, remaining; returns std::move(w.out) · [reviewed contract](#b0084) |
| [B0085 · 600–600](../../../../../src/io/explain.cpp#L600) | Callable definition: std::string write_explain_dot(const observability::QueryExplanation& e,ExplainTextLimits limits) | calls write_query_explain_dot; returns write_query_explain_dot(e,{limits.bytes}) · [reviewed contract](#b0085) |
| [B0086 · 601–601](../../../../../src/io/explain.cpp#L601) | Callable definition: std::string write_explain_tree_json(const observability::QueryExplanation& e,ExplainTextLimits limits) | calls w, object, number, text; returns std::move(w.out) · [reviewed contract](#b0086) |
| [B0087 · 602–602](../../../../../src/io/explain.cpp#L602) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0087) |

## B0001

[Lines 1–14](../../../../../src/io/explain.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using observability::PlanExplanation;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind this private implementation to the typed plan report and runtime names. |
| inputs / outputs | Public IO headers and local using declarations make report, ID, runtime and delegated encoder types available. |
| invariants | The aliases change lookup only; mutable runtime state is neither created nor admitted here. Anonymous-namespace helpers stay translation-unit private. |
| ownership | No storage or ownership is introduced by includes/using declarations. |
| failure | Compilation rejects unavailable or mismatched declarations; there is no runtime error path. |
| cost | Compile-time dependency/name binding only; no runtime calls, allocation or handlers. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0002

[Lines 15–33](../../../../../src/io/explain.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void utf8(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate strict UTF-8 before emitting an EXPLAIN string. |
| inputs / outputs | Borrowed bytes in; success returns without rewriting them. ASCII, including controls later escaped by quote, is accepted. |
| invariants | Rejects invalid leaders/continuations, truncated sequences, overlong forms, surrogate code points and values above U+10FFFF; this is export validation, not native admission or Unicode normalization. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | Throws text_encoding at the first malformed sequence; native bytes and runtime state remain untouched. |
| cost | O(input bytes), fixed local state and no successful heap allocation. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0003

[Lines 34–38](../../../../../src/io/explain.cpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Writer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one private streaming EXPLAIN buffer and its encoded-byte ceiling. |
| inputs / outputs | Public encoder supplies a byte limit; methods append a complete JSON/text/DOT artifact or throw before return. |
| invariants | out.size() never exceeds limit after a successful raw append. The cap counts encoded length, not string capacity, report storage, temporary labels or total process allocation. |
| ownership | Writer uniquely owns its ordinary std::string; references to report values remain borrowed. Each public encoder owns its Writer until moving the finished string out. |
| failure | Any append/encoding failure leaves only local partial output, released by RAII; no public partial result or catch is required. |
| cost | Amortized growing std::string allocation/copy proportional to emitted bytes; no DOM, query account or update-path instrumentation. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0004

[Lines 39–39](../../../../../src/io/explain.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Writer(std::size_t bytes):limit(bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize an empty writer with the caller byte ceiling. |
| inputs / outputs | A size_t ceiling is stored; out remains an empty owning string. |
| invariants | Zero is a valid ceiling and will reject nonempty output at raw. No eager reserve or hidden extra grant is created. |
| ownership | Constructs the local buffer owner; retains no report pointer. |
| failure | No explicit error path; later writes enforce the cap. |
| cost | Fixed scalar initialization; string implementation may use inline empty storage. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0005

[Lines 40–40](../../../../../src/io/explain.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t remaining() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the remaining encoded-byte budget to nested encoders. |
| inputs / outputs | Returns limit minus current output length. |
| invariants | Successful raw writes preserve out.size() &lt;= limit, so subtraction cannot underflow; it is not remaining allocator memory. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | noexcept; relies on the private writer length invariant. |
| cost | Fixed arithmetic without allocation. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0006

[Lines 41–44](../../../../../src/io/explain.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void raw(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and append one already encoded byte span. |
| inputs / outputs | Borrowed bytes are copied into out after the remaining-length check. |
| invariants | Subtraction-based admission avoids addition overflow; successful size stays within the ceiling. Earlier local appends are not undone on failure. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | resource_limit precedes an over-limit append; std::string allocation failure propagates. Buffer stays private. |
| cost | O(span bytes) plus possible string capacity growth/copy; checks are fixed work. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0007

[Lines 45–45](../../../../../src/io/explain.cpp#L45); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L45:sha256:3d9078701f311571c0696568a25af8f12e5742fb4160abac8ccb673c44784cf6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: UTF-8 is a transport rule; raw checks also admit each escaping expansion. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/explain.cpp lines 43-47; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/code_specs/files/src/io/explain.cpp.md](explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0008

[Lines 46–57](../../../../../src/io/explain.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void quote(std::string_view value,bool dot=false)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Quote a valid UTF-8 string for JSON or a DOT label. |
| inputs / outputs | Borrowed value and optional dot-control escaping flag produce one quoted string. |
| invariants | Prechecks raw input length, validates UTF-8, escapes quote/backslash and control bytes; DOT controls receive an extra slash. Exact escaping growth still passes raw admission per piece. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | Malformed UTF-8 or encoded-byte exhaustion throws with possibly partial local text; caller publishes no result. |
| cost | UTF-8 pass plus bytewise escape pass, O(input + encoded bytes); output growth can allocate. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0009

[Lines 58–62](../../../../../src/io/explain.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Integer> void number(Integer value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one integer using locale-independent decimal digits. |
| inputs / outputs | Integral value becomes a raw numeric token through a fixed 32-byte local buffer. |
| invariants | No stream, locale or floating conversion; to_chars success is required before appending the token. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | Unexpected to_chars error becomes explain_encoding; byte/allocation failure propagates from raw. |
| cost | Bounded integer conversion and digit append; no numeric formatting heap buffer. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0010

[Lines 63–63](../../../../../src/io/explain.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boolean(bool value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit a JSON Boolean token. |
| inputs / outputs | bool maps exactly to true or false. |
| invariants | Boolean values are not encoded as integer 0/1. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed token append and possible output growth. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0011

[Lines 64–64](../../../../../src/io/explain.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void null()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit an explicit JSON null token. |
| inputs / outputs | Appends null at the current value position. |
| invariants | Callers decide absence/unavailability; this does not create a native SQL NULL. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed token append and possible output growth. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0012

[Lines 65–65](../../../../../src/io/explain.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void optional(const std::optional<T>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an optional numeric fact. |
| inputs / outputs | Engaged value is a number; disengaged value is null. |
| invariants | Present zero remains a numeric zero; absence is not guessed from its payload. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed branch plus bounded number/null encoding. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0013

[Lines 66–68](../../../../../src/io/explain.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range,class Fn> void array(const Range& values,Fn fn)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stream an ordered range as a JSON array. |
| inputs / outputs | Borrows an iterable range and synchronous element encoder; preserves its iteration order. |
| invariants | One comma separates successive values; callback must encode exactly one valid value. No element buffering or sorting is performed. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | Range access/callback/append failures propagate from private partial output; no catch or source mutation. |
| cost | O(element count + callback/encoded-byte cost); only output growth is owned. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0014

[Lines 69–76](../../../../../src/io/explain.cpp#L69); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Object
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a borrowing JSON-object field writer. |
| inputs / outputs | Object borrows its Writer and tracks whether a comma is needed; typed wrappers delegate one field value. |
| invariants | Keys are quoted but not deduplicated; callers supply fixed unique keys and callbacks that emit one value. The first flag belongs only to this object. |
| ownership | Stack Object holds only Writer& and a Boolean; it owns no report or separate buffer. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed state per object; each field costs key escaping plus its value encoder and output growth. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0015

[Lines 77–77](../../../../../src/io/explain.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Fn> void object(Fn fn)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stream a callback-built JSON object. |
| inputs / outputs | Synchronous callback receives a fresh Object between braces. |
| invariants | Callback lifetime is nested within Writer; no DOM or publication before closing brace. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed brace/state work plus callback cost and output growth. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0016

[Lines 78–78](../../../../../src/io/explain.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range> void ids(const Range& values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an ordered native ID range. |
| inputs / outputs | Each element.value becomes one numeric array element. |
| invariants | Preserves field/node/variable order; it neither validates nor renumbers admitted IDs. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(ID count + digit bytes), no temporary ID vector. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0017

[Lines 79–80](../../../../../src/io/explain.cpp#L79); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#define CASE(Type,Item)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the local enum-to-literal switch shorthand. |
| inputs / outputs | Each CASE expands to one case label and returns the enumerator spelling as static text. |
| invariants | Only used by the name overloads below and undefined immediately afterward; this is spelling, not a default/saturation or validation policy. |
| ownership | Returned spellings have static literal lifetime; macro owns no state. |
| failure | No macro-level error handling; enclosing switches reject unsupported enumerators. |
| cost | Preprocessor substitution only; no runtime storage or dispatch layer. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0018

[Lines 81–84](../../../../../src/io/explain.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(PhysicalRoute value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell PhysicalRoute in this report format. |
| inputs / outputs | An admitted PhysicalRoute returns one static literal: tree, constant_true, constant_false. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0019

[Lines 85–88](../../../../../src/io/explain.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(NodeKind value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell NodeKind in this report format. |
| inputs / outputs | An admitted NodeKind returns one static literal: native, generalized. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0020

[Lines 89–89](../../../../../src/io/explain.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(DeltaMode value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell DeltaMode in this report format. |
| inputs / outputs | An admitted DeltaMode returns one static literal: maintenance, delta. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0021

[Lines 90–90](../../../../../src/io/explain.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(LiveMaintenance value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell LiveMaintenance in this report format. |
| inputs / outputs | An admitted LiveMaintenance returns one static literal: on_output, incremental, eager. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0022

[Lines 91–91](../../../../../src/io/explain.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(DeltaCompletion value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell DeltaCompletion in this report format. |
| inputs / outputs | An admitted DeltaCompletion returns one static literal: automatic, ordered_replay, anchored, root_first. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0023

[Lines 92–92](../../../../../src/io/explain.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResultView value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell ResultView in this report format. |
| inputs / outputs | An admitted ResultView returns one static literal: core, sql. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0024

[Lines 93–93](../../../../../src/io/explain.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(PropagationOrder value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell PropagationOrder in this report format. |
| inputs / outputs | An admitted PropagationOrder returns one static literal: fifo, lifo. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0025

[Lines 94–94](../../../../../src/io/explain.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ObservationMode value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell ObservationMode in this report format. |
| inputs / outputs | An admitted ObservationMode returns one static literal: off, counters, timed, trace. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0026

[Lines 95–98](../../../../../src/io/explain.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(DeltaState value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell DeltaState in this report format. |
| inputs / outputs | An admitted DeltaState returns one static literal: ready, pending_delta, paused, draining, epoch_prepared, committed_output, committed, aborted. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0027

[Lines 99–99](../../../../../src/io/explain.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ObservationLayer value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell ObservationLayer in this report format. |
| inputs / outputs | An admitted ObservationLayer returns one static literal: support, physical, delta. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0028

[Lines 100–100](../../../../../src/io/explain.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ObservationOutcome value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell ObservationOutcome in this report format. |
| inputs / outputs | An admitted ObservationOutcome returns one static literal: pending, committed, aborted. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0029

[Lines 101–101](../../../../../src/io/explain.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(MetricAvailability value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell MetricAvailability in this report format. |
| inputs / outputs | An admitted MetricAvailability returns one static literal: unavailable, disabled, available. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0030

[Lines 102–102](../../../../../src/io/explain.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(MetricKind value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell MetricKind in this report format. |
| inputs / outputs | An admitted MetricKind returns one static literal: counter, high_water, timing. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0031

[Lines 103–106](../../../../../src/io/explain.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(TraceDisposition value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell TraceDisposition in this report format. |
| inputs / outputs | An admitted TraceDisposition returns one static literal: disabled, not_sampled, pending, committed, aborted, released. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0032

[Lines 107–107](../../../../../src/io/explain.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(planner::CandidateSource value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell planner::CandidateSource in this report format. |
| inputs / outputs | An admitted CandidateSource returns exact_witness, residual_seed, normal_form or supplied_proposal; unknown values reject. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0033

[Lines 108–114](../../../../../src/io/explain.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L108-L114:sha256:1be2be147646fba7af460bcc17a7bb128c375f653a93a6ce3ac30cea0afe9891
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render a supported typed family name or its precise exhaustion scope. |
| inputs / outputs | Actual CandidateFamily in; stable report literal out. |
| invariants | finite_proposals_v1 remains explicitly limited to supplied input; old family spelling remains unchanged. |
| ownership | Static literal borrow only. |
| failure | Unknown family throws explain_enum before complete output publication. |
| cost | Fixed switch; enclosing report serialization retains its own length/allocation costs. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [Refactor.md](../../../../../Refactor.md) |

## B0034

[Lines 115–121](../../../../../src/io/explain.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L115-L121:sha256:4adec509d6028b01afab330fa574a4d242977cf68ea3a220fcf9d6084612271f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render a supported typed family name or its precise exhaustion scope. |
| inputs / outputs | Actual CandidateFamily in; stable report literal out. |
| invariants | finite_proposals_v1 remains explicitly limited to supplied input; old family spelling remains unchanged. |
| ownership | Static literal borrow only. |
| failure | Unknown family throws explain_enum before complete output publication. |
| cost | Fixed switch; enclosing report serialization retains its own length/allocation costs. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [Refactor.md](../../../../../Refactor.md) |

## B0035

[Lines 122–122](../../../../../src/io/explain.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(observability::RuntimePresence v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell observability::RuntimePresence in this report format. |
| inputs / outputs | An admitted observability::RuntimePresence returns one static literal: compile_only, live, stopped_retained, released. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0036

[Lines 123–123](../../../../../src/io/explain.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(observability::ExplanationKind v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell observability::ExplanationKind in this report format. |
| inputs / outputs | An admitted observability::ExplanationKind returns one static literal: physical, runtime, session. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0037

[Lines 124–124](../../../../../src/io/explain.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(observability::GaugeAvailability v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell observability::GaugeAvailability in this report format. |
| inputs / outputs | An admitted observability::GaugeAvailability returns one static literal: available, compile_only, pending_private_state, runtime_released. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0038

[Lines 125–125](../../../../../src/io/explain.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(SessionState v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell SessionState in this report format. |
| inputs / outputs | An admitted SessionState returns one static literal: created, running, paused, stopped, dropped. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0039

[Lines 126–126](../../../../../src/io/explain.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(SessionPhase v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell SessionPhase in this report format. |
| inputs / outputs | An admitted SessionPhase returns one static literal: ready, pending, paused_pending, draining, prepared, output. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0040

[Lines 127–127](../../../../../src/io/explain.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(SessionInputKind v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell SessionInputKind in this report format. |
| inputs / outputs | An admitted SessionInputKind returns one static literal: owned_stream, typed_physical, typed_window. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0041

[Lines 128–128](../../../../../src/io/explain.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(InitializationRoute v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell InitializationRoute in this report format. |
| inputs / outputs | An admitted InitializationRoute returns one static literal: empty_constructor, initialized_database, rebuilt_snapshot. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0042

[Lines 129–129](../../../../../src/io/explain.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(BuildMethod v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell BuildMethod in this report format. |
| inputs / outputs | An admitted BuildMethod returns one static literal: direct, insertion_replay. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0043

[Lines 130–130](../../../../../src/io/explain.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(io::InputFormat v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell io::InputFormat in this report format. |
| inputs / outputs | An admitted io::InputFormat returns one static literal: jsonl, binary, csv, legacy_signed, legacy_relations, legacy_insert_only, legacy_flags, legacy_timestamp_flags. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0044

[Lines 131–131](../../../../../src/io/explain.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResultCursorState v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell ResultCursorState in this report format. |
| inputs / outputs | An admitted ResultCursorState returns one static literal: active, exhausted, cancelled, failed. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0045

[Lines 132–132](../../../../../src/io/explain.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(CursorObservationSource v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell CursorObservationSource in this report format. |
| inputs / outputs | An admitted CursorObservationSource returns one static literal: committed_results, epoch_visible, epoch_witnesses, epoch_keys, epoch_bucket. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0046

[Lines 133–133](../../../../../src/io/explain.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(CursorTerminalReason v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell CursorTerminalReason in this report format. |
| inputs / outputs | An admitted CursorTerminalReason returns one static literal: not_recorded, none, exhausted, explicit_cancel, destruction, move_replacement, invalidated, startup_failure, next_failure. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0047

[Lines 134–134](../../../../../src/io/explain.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(TraceKind v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell TraceKind in this report format. |
| inputs / outputs | An admitted TraceKind returns one static literal: begin, source_change, alias, native_event, child_enqueued, child_applied, journal, reverse_visit, core_result, mapped_record, prepared, drain, commit, abort, transferred, discarded, serialization_attempt, serialization_success, serialization_failure, sink_attempt, sink_success, sink_failure, acknowledged. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw explain_enum; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0048

[Lines 135–135](../../../../../src/io/explain.cpp#L135); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L135:sha256:4bccd635a3ec24b2916b35de7843c068b5e66ab93e75680a9a36dbdae735397f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ends the local preprocessor definition of CASE; subsequent translation-unit code cannot use that macro expansion. |
| inputs / outputs | No runtime values are exchanged; a preprocessor macro is removed for later source text in this translation unit. |
| invariants | The macro expansion is available only before this directive; later code must use ordinary declarations or a fresh definition. |
| ownership | No runtime state. |
| failure | No runtime error. Preprocessing/compilation can fail if later tokens depended on the removed macro. |
| cost | Preprocessing only. |
| Design | [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/code_specs/files/src/io/explain.cpp.md](explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0049

[Lines 136–139](../../../../../src/io/explain.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* height_status(const PlanExplanation& report)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the height-evidence label already admitted by PlanExplanation. |
| inputs / outputs | Report HeightStatus yields checked_constant_operator, verified_original_minimum or checked_upper. |
| invariants | A constant-false executable operator is distinguished from an original CQ minimum; fallback is valid only because factory-produced reports carry declared statuses. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | Moved-from/invalid report access propagates invalid_explanation; this function creates no proof or validation report. |
| cost | Fixed handle/status access with no successful allocation. |
| Design | [docs/observability.md §Height, cost, and proof scope](../../../../observability.md) |

## B0050

[Lines 140–151](../../../../../src/io/explain.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar(Writer& w,const Value& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one owning native scalar with its type tag. |
| inputs / outputs | Value alternative becomes {type,value}; int64 is a JSON integer, bool a Boolean, string UTF-8 text, date/decimal a quoted canonical spelling. |
| invariants | Date/decimal spelling and type are retained; string bytes must satisfy this export transport even though native storage accepts arbitrary bytes. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | String encoding/byte/format/allocation failure aborts only the private export; the original scalar remains unchanged. |
| cost | O(encoded scalar bytes); date/decimal to_string may allocate a temporary before output growth. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0051

[Lines 152–156](../../../../../src/io/explain.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar(Writer& w,const storage::ScalarView& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a borrowed native scalar without first copying a string payload. |
| inputs / outputs | ScalarView string_view writes type=string directly; other alternatives export an owning inline/native value and reuse scalar(Value). |
| invariants | Borrowed string bytes need only survive this synchronous call; ordinary scalars are not assigned SQL nullability. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(scalar spelling/output bytes); strings avoid an owning payload copy. InlineDecimal takes export_scalar render/Decimal::parse and then Decimal::to_string, so bounded coefficient/spelling temporaries and output can allocate. |
| Design | [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0052

[Lines 157–163](../../../../../src/io/explain.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class TermView> void term(Writer& w,const TermView& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one admitted query term. |
| inputs / outputs | Variable emits its ID, constant delegates typed scalar, and ignored column emits only its kind. |
| invariants | Discriminates the TermView alternatives without re-binding, rewriting or looking up a table row. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed variant dispatch plus scalar/encoded-byte cost for constants. |
| Design | [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0053

[Lines 164–192](../../../../../src/io/explain.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class TreeView,class Validation=planner::ValidationReport> void tree(Writer& w,const TreeView& value,const Validation* validation=nullptr)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a selected or proof-witness tree and optional validation facts. |
| inputs / outputs | Tree node order supplies numeric IDs; optional Validation supplies separators and maximal-connex membership. Absent validation emits null facts. |
| invariants | Builds one membership bit-vector, then visits each node once; native IDs and validation arrays must correspond to the admitted tree. It does not establish tree validity. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | Scratch allocation, invalid validation IDs (.at), encoding and byte failures propagate; source/report and proof handles are unchanged. |
| cost | O(nodes + maximal_connex + total scope/children/separator IDs + output bytes); O(nodes) diagnostic bit scratch before writing. vector bounds/allocations are separate from encoded-byte cap. |
| Design | [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0054

[Lines 193–193](../../../../../src/io/explain.cpp#L193); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L193-L193:sha256:a7e0b5ec9404f06cc28ac2960f64e76ac4fd1ac3a199cf424bc551ef0370cc7a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Export the supplied profile verbatim; this is no independent bound checker. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/explain.cpp lines 177-181; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/code_specs/files/src/io/explain.cpp.md](explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0055

[Lines 194–203](../../../../../src/io/explain.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void profile(Writer& w,const DeltaRuntimeProfile& p)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the supplied DeltaRuntimeProfile guarantee prose. |
| inputs / outputs | Writes semantics, class, arithmetic, backend, phase bounds, startup flag, costs, assumptions and output-accounting strings. |
| invariants | Forwards actual profile fields; does not recompute selected backend or certify the bounds. The known producer backend-default finding is owned by the Delta review. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed field count plus total prose bytes and output growth. |
| Design | [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md) |

## B0056

[Lines 204–237](../../../../../src/io/explain.cpp#L204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void mode(Writer& w,const observability::ModeDescriptor& m)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode current/retained owner configuration independently of historical attempts. |
| inputs / outputs | ModeDescriptor yields presence/scope/plan facts; compile-only has null runtime, otherwise writes requested options, resolved profile, owner/state and limits. |
| invariants | Factory assures options/profile appear together. Historical metric configuration lives in each summary. durable_delivery and other legacy capability prose are frozen v2 fields, not live sink or repository acceptance facts. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed metadata/limit fields plus profile/prose bytes; no engine-table scan or fresh measurement. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/observability/explain.hpp](../../../../../include/crown/observability/explain.hpp) |

## B0057

[Lines 238–258](../../../../../src/io/explain.cpp#L238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[maybe_unused]] void requested_options(Writer& w,const DeltaOptions& opts)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the requested DeltaOptions nested inside an immutable begin configuration. |
| inputs / outputs | Writes mode/completion/view/live maintenance, optional work limits, spool quotas and nested support/observation options. |
| invariants | Only a nondefault legacy support.memory_limit_bytes is emitted; absence preserves v2 wire compatibility. Requested options must not be relabeled as resolved execution. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed option field count and numeric/text output; no runtime calls or new grant. |
| Design | [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0058

[Lines 259–269](../../../../../src/io/explain.cpp#L259); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Configuration> void configuration(Writer& w,const Configuration& c)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an immutable observation configuration identity. |
| inputs / outputs | Configuration supplies format, owner/generation, resolved modes, query factor count and captured requested options. |
| invariants | Identity is process-local owner/generation; a saturated generation is not unique. Guarantee prose is explicitly not copied from the current runtime profile. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed metadata plus requested-options formatting. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0059

[Lines 270–270](../../../../../src/io/explain.cpp#L270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool mode_bound(const ObservationSummary& s)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether one attempt retained its begin configuration. |
| inputs / outputs | Returns configuration.has_value(). |
| invariants | Recorded configuration, rather than current owner options, determines historical binding. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | No explicit failure path; reads the provided summary only. |
| cost | Fixed optional-presence check with no allocation. |
| Design | [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0060

[Lines 271–274](../../../../../src/io/explain.cpp#L271); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void historical_mode(Writer& w,Writer::Object& o,const ObservationSummary& s)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose exact begin binding or explicit not-recorded history. |
| inputs / outputs | Writes mode_binding and a captured configuration object or null. |
| invariants | Never reconstructs missing history from current mode; does not mutate the summary. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed binding fields plus captured configuration formatting. |
| Design | [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0061

[Lines 275–277](../../../../../src/io/explain.cpp#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void current_configuration(Writer& w,const ObservationSnapshot& s)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode current observation configuration if retained. |
| inputs / outputs | Snapshot configuration becomes its object, otherwise null. |
| invariants | Current configuration is a separate field from per-attempt begin configuration. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed presence branch plus configuration output. |
| Design | [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0062

[Lines 278–294](../../../../../src/io/explain.cpp#L278); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void summary(Writer& w,const std::optional<ObservationSummary>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one optional attempt summary while suppressing unavailable numeric payloads. |
| inputs / outputs | Absent summary is null; present summary includes attempt/sequence/layer/outcome, begin binding, and one value entry per registry descriptor. |
| invariants | Only available metrics export numeric value and saturation flag; disabled/unavailable stale internal payloads become null. Available saturated values remain explicitly saturated. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(registry descriptors + captured configuration/output bytes); no counter recomputation or clocks. |
| Design | [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0063

[Lines 295–299](../../../../../src/io/explain.cpp#L295); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void causal_record(Writer& w,const TraceRecord& r)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one sampled numeric causal-trace record. |
| inputs / outputs | Writes kind, event/cause/prefix/before/after, and optional node/occurrence/role/tuple IDs. |
| invariants | observation_no_id maps to null; numeric IDs do not pin source rows or assert a complete committed history. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed fields per record plus digits. |
| Design | [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0065

[Lines 301–333](../../../../../src/io/explain.cpp#L301); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void observations(Writer& w,const PlanExplanation& report)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode observation availability, registry, summaries, lifetime counts and retained trace. |
| inputs / outputs | Plan report may have no observation, disabled observation or a retained enabled snapshot; each state remains distinguishable. |
| invariants | Mandatory accounting stays declared active; aborted summaries are attempted work. Trace records are sampled/truncated numeric captures, not durable history or row owners. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(registry + current/last metric entries + retained trace + output bytes); no live sampling, cursor advance or table scan. |
| Design | [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0066

[Lines 334–362](../../../../../src/io/explain.cpp#L334); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class PlanView> void query(Writer& w,const PlanView& plan)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the admitted typed query and optional normalized SQL mapping. |
| inputs / outputs | Writes ordered variables, atoms/table names/terms, head and, if present, SQL source, bound parameters and output metadata/constants. |
| invariants | Uses actual plan catalog/query/normalization; IDs, output order, nullable flags and decimal typemods are descriptive. This is not a SQL compiler or a digest/proof import authority. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | Bounds/variant/encoding/byte/allocation errors propagate; private output is not published. Plan/normalized owners are not modified. |
| cost | O(query metadata, term/scalar bytes, parameter/output arrays and encoded bytes); date/decimal formatting may allocate. |
| Design | [include/crown/runtime/program.hpp](../../../../../include/crown/runtime/program.hpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0068

[Lines 364–392](../../../../../src/io/explain.cpp#L364); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void session_status(Writer& w,const PlanExplanation& e)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode captured owning-session lifecycle and queue/window occupancy. |
| inputs / outputs | Absent status emits null; present status emits phases/sequences/work/output, input flags, queue/window facts and availability. Optional pattern status exports actual physical/source binding, origin/through counters, insertion policy, fresh/restored provenance and fixed violation. |
| invariants | Uses actual session metadata; absent live queue/window with retained construction context means released, otherwise not applicable. No supplied plan/hash join fabricates session identity. No new maintenance bound is asserted; restored history is explicitly trusted checkpoint metadata, and undeclared reports omit the optional object. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed captured scalar/optional fields plus output bytes; no queue traversal, window transition or source peek. |
| Design | [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0070

[Lines 394–471](../../../../../src/io/explain.cpp#L394); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void json(Writer& w,const PlanExplanation& e)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose the complete closed v2 plan/runtime/session JSON artifact. |
| inputs / outputs | Factory-produced PlanExplanation yields identities, query/tree/height evidence, physical descriptors, modes, observations, session/cursor/gauges and frozen capability fields. |
| invariants | Digests navigate but do not authorize proof/import. Typed original evidence stays distinct from checked constant operators and finite candidate families. Legacy cost/open_gates constants describe v2, not current repository completion. Candidate family name and exhaustion scope come from the actual typed snapshot; source comes from selected-candidate provenance. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | Any nested getter, bounds, format, byte or allocation failure propagates. The local buffer is discarded; source report, engine state and proof handles remain unchanged. |
| cost | Traverses admitted query/tree/index/evidence/registry/trace arrays; O(their size + emitted bytes), with O(tree nodes) scratch and nested encoders materializing temporary strings within remaining byte length. |
| Design | [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0071

[Lines 472–484](../../../../../src/io/explain.cpp#L472); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void human_metrics(Writer& w,const char* label,const std::optional<ObservationSummary>& summary_value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render one optional attempt and its metrics in human text. |
| inputs / outputs | No summary prints nothing; present summary prints sequence/outcome, exact-or-missing historical binding and registry values with units/accounting. |
| invariants | Unavailable/disabled metrics print their availability, not stale payloads; available saturated values are labeled. Registry prose is descriptive instrumentation scope. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(registry + historical configuration + text bytes); no timing measurement. |
| Design | [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0073

[Lines 486–492](../../../../../src/io/explain.cpp#L486); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void human_declared(Writer& w,std::string_view label,const std::shared_ptr<const DeclaredBenchmarkContext>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render optional caller-declared benchmark labels. |
| inputs / outputs | Prints unmeasured provenance and run/input/codec/sink labels or explicit absence. |
| invariants | Labels are caller declarations, not measured system identity or authenticated delivery. Optional empty string remains a present label. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed label count plus UTF-8/escape/output bytes. |
| Design | [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0074

[Lines 493–499](../../../../../src/io/explain.cpp#L493); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void human_output(Writer& w,std::string_view label,const std::optional<ObservationSummary>& s)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render one captured attempt output disposition. |
| inputs / outputs | Absent attempt prints nothing; present attempt prints declarations and recorded output-action flags or not-recorded. |
| invariants | Flags describe observed publication/serialization/sink/release actions, not durable receipt authority; no callback or delivery is invoked. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed flag count plus optional declared-label bytes. |
| Design | [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0075

[Lines 500–527](../../../../../src/io/explain.cpp#L500); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void human_integrated(Writer& w,const PlanExplanation& e)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render integrated captured construction/session/cursor/gauge facts. |
| inputs / outputs | Writes presence, actual initialization/input/limits, begin-bound output dispositions, latest cursor metrics and committed gauges when available. Window FIFO text preserves exact names for both label and physical lifetime policies. |
| invariants | Latest cursor is not an update/lifetime total. Nested context/gauge exports use captured owners. Final memory/recovery capability prose is frozen legacy v2 and not a current release or sink-status assertion. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(cursor registry + nested captured arrays/prose/output bytes); nested JSON creates temporary strings bounded by remaining encoded length, not aggregate allocation. |
| Design | [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0076

[Lines 528–529](../../../../../src/io/explain.cpp#L528); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L528-L529:sha256:804f89fc0ec98c9824183e795d3edd19e930f7bc471f9012aa3d503be2f8974b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing implementation scope at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/code_specs/files/src/io/explain.cpp.md](explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0077

[Lines 530–530](../../../../../src/io/explain.cpp#L530); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_explain_json(const PlanExplanation& report,ExplainTextLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one complete owning v2 JSON string. |
| inputs / outputs | Builds a local byte-capped Writer, composes json(report), then moves out the finished string. |
| invariants | No partial return and no runtime update on failure; cap is encoded size only. |
| ownership | Returned std::string owns its bytes independently of the borrowed report and native runtime. |
| failure | Propagates report/encoding/resource/allocation errors; local RAII discards partial text. |
| cost | Full json composition cost plus ordinary string growth; final string move avoids a deliberate deep copy. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0078

[Lines 531–575](../../../../../src/io/explain.cpp#L531); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_explain_text(const PlanExplanation& report,ExplainTextLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a human-readable v2 plan/runtime/session explanation. |
| inputs / outputs | Prints actual typed query/tree/index/height context, current and historical observation facts, trace and integrated metadata under one byte ceiling. |
| invariants | Checked upper/minimum/constant-operator authority stays explicit. Frozen unavailable cost/recovery/open prose is retained v2 compatibility; ledger and current owner APIs supply project/sink completion. Supplied batches print finite-proposals-v1 with retained count/completion and no global-cost completeness. |
| ownership | Returned string owns all text; borrowed immutable report data is needed only through the call. |
| failure | Report access, string encoding, byte exhaustion and allocation errors propagate before any returned text. |
| cost | O(all displayed metadata/trace/registry + encoded bytes), with repeated query/proof rendering and nested temporary strings; no update-path instrumentation. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0079

[Lines 576–577](../../../../../src/io/explain.cpp#L576); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L576-L577:sha256:8e5011da60ea36015fe67e55d0c975d37cb9d5890995c9f4ae23bdf414e94612
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Caption/label buffers overlap the result; each length cap is not a total allocator-memory cap. DOT remains an explicit diagnostic operation. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/explain.cpp lines 535-540; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/code_specs/files/src/io/explain.cpp.md](explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0080

[Lines 578–595](../../../../../src/io/explain.cpp#L578); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_explain_dot(const PlanExplanation& report,ExplainTextLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish DOT for the selected admitted physical tree. |
| inputs / outputs | Emits height/status caption, native/generalized node shapes, connex styling and separator-labeled edges; empty node set has a constant route marker. |
| invariants | Selected tree/height is diagnostic, not an imported certificate. Node/edge label scratch and caption each have a byte ceiling; their concurrent memory is not the single final-output cap. |
| ownership | Final DOT string owns its text; each local label/caption is released after quoting. |
| failure | Invalid report IDs/UTF-8, byte limits or allocation fail only this private export. |
| cost | O(nodes + edges + scope/separator IDs + output bytes); temporary label/caption strings and final output can allocate. |
| Design | [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0082

[Lines 597–597](../../../../../src/io/explain.cpp#L597); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_explain_tree_json(const PlanExplanation& e,ExplainTextLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the selected-tree-only v2 JSON artifact. |
| inputs / outputs | Writes schema/kind/scope/native height and admitted tree with its validation facts. |
| invariants | Constant-false operator scope remains explicit; no original-query minimum or proof authority is synthesized. |
| ownership | Moves the complete local string to the caller; report remains borrowed. |
| failure | Report/bounds/encoding/byte/allocation failures propagate without partial return. |
| cost | O(tree nodes/IDs + encoded bytes), O(nodes) connex membership scratch. |
| Design | [schemas/explain-tree-v2.schema.json](../../../../../schemas/explain-tree-v2.schema.json), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0083

[Lines 598–598](../../../../../src/io/explain.cpp#L598); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_explain_json(const observability::QueryExplanation& e,ExplainTextLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap the separate typed query/search JSON in the v2 envelope. |
| inputs / outputs | QueryExplanation is delegated with the remaining outer byte budget. |
| invariants | Nested query report retains its own search/evidence scope; outer identity is kind=query and not a physical-plan import. |
| ownership | Returned envelope owns bytes; temporary nested encoding is local and borrows the typed query report. |
| failure | Nested encoder/access/byte/allocation errors propagate before public return. |
| cost | Nested query-encoder cost plus copying its temporary string into the outer output; both buffers can coexist. |
| Design | [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0084

[Lines 599–599](../../../../../src/io/explain.cpp#L599); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_explain_text(const observability::QueryExplanation& e,ExplainTextLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prefix and publish the separate query/search human format. |
| inputs / outputs | Writes the v2 query/search heading, then delegates the remaining budget to query text encoding. |
| invariants | Prefix bytes consume the same final encoded-length allowance; preserves query/search authority distinctions. |
| ownership | Returned text owns bytes independently of the query report. |
| failure | Nested encoder/byte/allocation errors propagate; no partial return. |
| cost | Nested text encoder plus temporary/final string copying and growth. |
| Design | [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0085

[Lines 600–600](../../../../../src/io/explain.cpp#L600); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_explain_dot(const observability::QueryExplanation& e,ExplainTextLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate query/search DOT export without adding an envelope. |
| inputs / outputs | Forwards QueryExplanation and exactly limits.bytes to write_query_explain_dot. |
| invariants | The query-specific encoder decides whether a witness is available; this wrapper supplies no invented physical tree. |
| ownership | Returns the delegated owning string; retains no additional report ownership. |
| failure | Propagates delegated query-explanation/witness/resource/encoding errors unchanged. |
| cost | Fixed forwarding overhead plus delegated witness/DOT formatting. |
| Design | [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0086

[Lines 601–601](../../../../../src/io/explain.cpp#L601); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_explain_tree_json(const observability::QueryExplanation& e,ExplainTextLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap a typed query witness export in the v2 tree envelope. |
| inputs / outputs | Writes schema/artifact/kind=query and delegates witness JSON under the remaining budget. |
| invariants | Missing witness is governed by the query encoder; wrapper cannot fabricate one from status or digest. |
| ownership | Final envelope owns bytes; query/evidence is borrowed for synchronous encoding. |
| failure | Delegated missing-witness, byte/encoding/allocation errors propagate; local partial text is discarded. |
| cost | Nested witness rendering plus temporary/final buffer overlap and copy. |
| Design | [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0087

[Lines 602–602](../../../../../src/io/explain.cpp#L602); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L602-L602:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/explain.cpp](../../../../../src/io/explain.cpp), [docs/code_specs/files/src/io/explain.cpp.md](explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |
