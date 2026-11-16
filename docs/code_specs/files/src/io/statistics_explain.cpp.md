# `src/io/statistics_explain.cpp` — block usage map

[Source](../../../../../src/io/statistics_explain.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `02528665b49d45aa13661678abdcf6ef7bd6f8c096f53523a086085093c8f554`. 328 lines partitioned into 75 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../src/io/statistics_explain.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Count every JSON value, including containers/null, but exclude field names. · [reviewed contract](#b0001) |
| [B0002 · 19–22](../../../../../src/io/statistics_explain.cpp#L19) | Callable definition: void raw(std::string_view value) | calls size, Error, append · [reviewed contract](#b0002) |
| [B0003 · 23–23](../../../../../src/io/statistics_explain.cpp#L23) | Callable definition: void item() | calls Error · [reviewed contract](#b0003) |
| [B0004 · 24–24](../../../../../src/io/statistics_explain.cpp#L24) | Explanatory comments or spacing. | source comment (unverified): // No item charge here: object keys and string values share escaping. · [reviewed contract](#b0004) |
| [B0005 · 25–34](../../../../../src/io/statistics_explain.cpp#L25) | Callable definition: void quoted(std::string_view value) | calls raw, Error; 1 loop sites; source comment (unverified): // No item charge here: object keys and string values share escaping. · [reviewed contract](#b0005) |
| [B0006 · 35–35](../../../../../src/io/statistics_explain.cpp#L35) | Callable definition: void text(std::string_view value) | calls item, quoted · [reviewed contract](#b0006) |
| [B0007 · 36–40](../../../../../src/io/statistics_explain.cpp#L36) | Callable definition: void bytes(std::string_view value) | calls item, raw; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 41–44](../../../../../src/io/statistics_explain.cpp#L41) | Callable definition: template&lt;class T&gt;void number(T value) | calls item, std::to_chars, Error, raw · [reviewed contract](#b0008) |
| [B0009 · 45–45](../../../../../src/io/statistics_explain.cpp#L45) | Callable definition: void boolean(bool value) | calls item, raw · [reviewed contract](#b0009) |
| [B0010 · 46–46](../../../../../src/io/statistics_explain.cpp#L46) | Callable definition: void null() | calls item, raw · [reviewed contract](#b0010) |
| [B0011 · 47–55](../../../../../src/io/statistics_explain.cpp#L47) | Type/record definition: struct Object |  · [reviewed contract](#b0011) |
| [B0012 · 56–56](../../../../../src/io/statistics_explain.cpp#L56) | Callable definition: template&lt;class F&gt;void object(F fn) | calls item, raw, fn · [reviewed contract](#b0012) |
| [B0013 · 57–57](../../../../../src/io/statistics_explain.cpp#L57) | Callable definition: template&lt;class Range,class F&gt;void array(const Range& values,F fn) | calls item, raw, fn; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 58–58](../../../../../src/io/statistics_explain.cpp#L58) | Callable definition: template&lt;class T&gt;void optional(const std::optional&lt;T&gt;& value) | calls number, null · [reviewed contract](#b0014) |
| [B0015 · 59–59](../../../../../src/io/statistics_explain.cpp#L59) | Closes surrounding scope/type. |  · [reviewed contract](#b0015) |
| [B0016 · 60–60](../../../../../src/io/statistics_explain.cpp#L60) | Callable definition: const char* name(runtime::DeltaMode value) | calls Error; returns @; @ · [reviewed contract](#b0016) |
| [B0017 · 61–61](../../../../../src/io/statistics_explain.cpp#L61) | Callable definition: const char* name(runtime::DeltaCompletion value) | calls Error; returns @; @ · [reviewed contract](#b0017) |
| [B0018 · 62–62](../../../../../src/io/statistics_explain.cpp#L62) | Callable definition: const char* name(runtime::LiveMaintenance value) | calls Error; returns @; @ · [reviewed contract](#b0018) |
| [B0019 · 63–63](../../../../../src/io/statistics_explain.cpp#L63) | Callable definition: const char* name(runtime::ResultView value) | calls Error; returns @; @ · [reviewed contract](#b0019) |
| [B0020 · 64–64](../../../../../src/io/statistics_explain.cpp#L64) | Callable definition: const char* name(runtime::PropagationOrder value) | calls Error; returns @; @ · [reviewed contract](#b0020) |
| [B0021 · 65–65](../../../../../src/io/statistics_explain.cpp#L65) | Callable definition: const char* name(runtime::ObservationMode value) | calls Error; returns @; @ · [reviewed contract](#b0021) |
| [B0022 · 66–66](../../../../../src/io/statistics_explain.cpp#L66) | Callable definition: const char* name(runtime::DeltaState value) | calls Error; returns @; @ · [reviewed contract](#b0022) |
| [B0023 · 67–67](../../../../../src/io/statistics_explain.cpp#L67) | Callable definition: const char* name(runtime::SessionState value) | calls Error; returns @; @ · [reviewed contract](#b0023) |
| [B0024 · 68–68](../../../../../src/io/statistics_explain.cpp#L68) | Callable definition: const char* name(runtime::SessionPhase value) | calls Error; returns @; @ · [reviewed contract](#b0024) |
| [B0025 · 69–69](../../../../../src/io/statistics_explain.cpp#L69) | Callable definition: const char* name(runtime::ObservationOutcome value) | calls Error; returns @; @ · [reviewed contract](#b0025) |
| [B0026 · 70–70](../../../../../src/io/statistics_explain.cpp#L70) | Callable definition: const char* name(runtime::ObservationLayer value) | calls Error; returns @; @ · [reviewed contract](#b0026) |
| [B0027 · 71–71](../../../../../src/io/statistics_explain.cpp#L71) | Callable definition: const char* name(runtime::MetricAvailability value) | calls Error; returns @; @ · [reviewed contract](#b0027) |
| [B0028 · 72–72](../../../../../src/io/statistics_explain.cpp#L72) | Callable definition: const char* name(runtime::TraceDisposition value) | calls Error; returns @; @ · [reviewed contract](#b0028) |
| [B0029 · 73–73](../../../../../src/io/statistics_explain.cpp#L73) | Callable definition: const char* name(runtime::MetricKind value) | calls Error; returns @; @ · [reviewed contract](#b0029) |
| [B0030 · 74–74](../../../../../src/io/statistics_explain.cpp#L74) | Callable definition: const char* name(observability::RuntimePresence value) | calls Error; returns @; @ · [reviewed contract](#b0030) |
| [B0031 · 75–75](../../../../../src/io/statistics_explain.cpp#L75) | Callable definition: const char* name(observability::IntervalComparison value) | calls Error; returns @; @ · [reviewed contract](#b0031) |
| [B0032 · 76–76](../../../../../src/io/statistics_explain.cpp#L76) | Callable definition: const char* name(st::Availability value) | calls Error; returns @; @ · [reviewed contract](#b0032) |
| [B0033 · 77–77](../../../../../src/io/statistics_explain.cpp#L77) | Callable definition: const char* name(st::Freshness value) | calls Error; returns @; @ · [reviewed contract](#b0033) |
| [B0034 · 78–78](../../../../../src/io/statistics_explain.cpp#L78) | Callable definition: const char* name(ws::Mode value) | calls Error; returns @; @ · [reviewed contract](#b0034) |
| [B0035 · 79–79](../../../../../src/io/statistics_explain.cpp#L79) | Callable definition: const char* name(ws::Availability value) | calls Error; returns @; @ · [reviewed contract](#b0035) |
| [B0036 · 80–80](../../../../../src/io/statistics_explain.cpp#L80) | Callable definition: const char* name(ws::Kind value) | calls Error; returns @; @ · [reviewed contract](#b0036) |
| [B0037 · 81–81](../../../../../src/io/statistics_explain.cpp#L81) | Callable definition: const char* name(ws::Operation value) | calls Error; returns @; @; growth insert · [reviewed contract](#b0037) |
| [B0038 · 82–82](../../../../../src/io/statistics_explain.cpp#L82) | Callable definition: const char* name(ws::Role value) | calls Error; returns @; @ · [reviewed contract](#b0038) |
| [B0039 · 83–83](../../../../../src/io/statistics_explain.cpp#L83) | Callable definition: const char* name(ws::InputScope value) | calls Error; returns @; @ · [reviewed contract](#b0039) |
| [B0040 · 84–84](../../../../../src/io/statistics_explain.cpp#L84) | Callable definition: const char* name(ws::DenominatorScope value) | calls Error; returns @; @ · [reviewed contract](#b0040) |
| [B0041 · 85–85](../../../../../src/io/statistics_explain.cpp#L85) | Callable definition: const char* name(SupportRole value) | calls Error; returns @; @ · [reviewed contract](#b0041) |
| [B0042 · 86–86](../../../../../src/io/statistics_explain.cpp#L86) | Callable definition: const char* name(NodeKind value) | calls Error; returns @; @ · [reviewed contract](#b0042) |
| [B0043 · 87–87](../../../../../src/io/statistics_explain.cpp#L87) | Callable definition: const char* name(PhysicalRoute value) | calls Error; returns @; @ · [reviewed contract](#b0043) |
| [B0044 · 88–98](../../../../../src/io/statistics_explain.cpp#L88) | Callable definition: void scalar(Writer& w,const storage::ScalarView& value) | calls object, text, type_name, storage::type_of · [reviewed contract](#b0044) |
| [B0045 · 99–99](../../../../../src/io/statistics_explain.cpp#L99) | Callable definition: void row(Writer& w,const st::CapturedKey& value) | calls array, view, cells, scalar · [reviewed contract](#b0045) |
| [B0046 · 100–102](../../../../../src/io/statistics_explain.cpp#L100) | Callable definition: void fact(Writer& w,std::optional&lt;std::uint64_t&gt; value,std::string_view reason) | calls object, field, optional, null · [reviewed contract](#b0046) |
| [B0047 · 103–106](../../../../../src/io/statistics_explain.cpp#L103) | Callable definition: void observation_options(Writer& w,const ObservationOptions& value) | calls object, text, name, number · [reviewed contract](#b0047) |
| [B0048 · 107–118](../../../../../src/io/statistics_explain.cpp#L107) | Callable definition: void delta_options(Writer& w,const DeltaOptions& value) | calls object, text, name, number · [reviewed contract](#b0048) |
| [B0049 · 119–123](../../../../../src/io/statistics_explain.cpp#L119) | Callable definition: void mode_facts(Writer& w,const ws::ModeFacts& value) | calls object, boolean, text, name · [reviewed contract](#b0049) |
| [B0050 · 124–128](../../../../../src/io/statistics_explain.cpp#L124) | Callable definition: void configuration(Writer& w,const ObservationConfiguration& value) | calls object, number, support_owner, generation · [reviewed contract](#b0050) |
| [B0051 · 129–133](../../../../../src/io/statistics_explain.cpp#L129) | Callable definition: void labels(Writer& w,const std::shared_ptr&lt;const DeclaredBenchmarkContext&gt;& value) | calls null, object, text, field · [reviewed contract](#b0051) |
| [B0052 · 134–147](../../../../../src/io/statistics_explain.cpp#L134) | Callable definition: void observation_summary(Writer& w,const std::optional&lt;ObservationSummary&gt;& value) | calls null, object, number, text · [reviewed contract](#b0052) |
| [B0053 · 148–163](../../../../../src/io/statistics_explain.cpp#L148) | Callable definition: void o07(Writer& w,const Report& report) | calls observation, object, field, observation_options · [reviewed contract](#b0053) |
| [B0054 · 164–167](../../../../../src/io/statistics_explain.cpp#L164) | Callable definition: void limits(Writer& w,const st::Limits& v) | calls object, number · [reviewed contract](#b0054) |
| [B0055 · 168–171](../../../../../src/io/statistics_explain.cpp#L168) | Callable definition: void usage(Writer& w,const st::Usage& v) | calls object, number · [reviewed contract](#b0055) |
| [B0056 · 172–178](../../../../../src/io/statistics_explain.cpp#L172) | Callable definition: void layout(Writer& w,const storage::TupleLayout& v) | calls object, number, id, context · [reviewed contract](#b0056) |
| [B0057 · 179–187](../../../../../src/io/statistics_explain.cpp#L179) | Callable definition: void selection(Writer& w,const st::CapturedSelection& v) | calls object, std::visit, constexpr, text · [reviewed contract](#b0057) |
| [B0058 · 188–196](../../../../../src/io/statistics_explain.cpp#L188) | Callable definition: void distribution(Writer& w,const st::CapturedDistribution& v) | calls object, text, number, field · [reviewed contract](#b0058) |
| [B0059 · 197–197](../../../../../src/io/statistics_explain.cpp#L197) | Explanatory comments or spacing. | source comment (unverified): // Format captured components only; this never scans the live engine tables. · [reviewed contract](#b0059) |
| [B0060 · 198–216](../../../../../src/io/statistics_explain.cpp#L198) | Callable definition: void state(Writer& w,const Report& report) | calls combined, state_requested, name, availability; source comment (unverified): // Format captured components only; this never scans the live engine tables. · [reviewed contract](#b0060) |
| [B0061 · 217–218](../../../../../src/io/statistics_explain.cpp#L217) | Callable definition: void workload_options(Writer& w,const ws::Options& v) | calls object, text, name, number · [reviewed contract](#b0061) |
| [B0062 · 219–223](../../../../../src/io/statistics_explain.cpp#L219) | Callable definition: void stamp(Writer& w,const ws::Stamp& v) | calls object, number, boolean · [reviewed contract](#b0062) |
| [B0063 · 224–230](../../../../../src/io/statistics_explain.cpp#L224) | Callable definition: void metadata(Writer& w,const ws::Metadata& v) | calls object, N, number, text · [reviewed contract](#b0063) |
| [B0064 · 231–237](../../../../../src/io/statistics_explain.cpp#L231) | Callable definition: void descriptor(Writer& w,const ws::Descriptor& v) | calls object, text, name, field · [reviewed contract](#b0064) |
| [B0065 · 238–238](../../../../../src/io/statistics_explain.cpp#L238) | Explanatory comments or spacing. | source comment (unverified): // Keep exact/sample integer ratios; a ratio of clipped lower bounds is unknown. · [reviewed contract](#b0065) |
| [B0066 · 239–246](../../../../../src/io/statistics_explain.cpp#L239) | Callable definition: void fraction(Writer& w,const ws::Fraction& v,bool clipped=false) | calls object, text, name, field; source comment (unverified): // Keep exact/sample integer ratios; a ratio of clipped lower bounds is unknown. · [reviewed contract](#b0066) |
| [B0067 · 247–258](../../../../../src/io/statistics_explain.cpp#L247) | Callable definition: void cell(Writer& w,const ws::Cell& v,const ws::Descriptor& d,bool global_saturation) | calls object, text, boolean, N · [reviewed contract](#b0067) |
| [B0068 · 259–260](../../../../../src/io/statistics_explain.cpp#L259) | Explanatory comments or spacing. | source comment (unverified): // Ratio getters scan captured descriptor/cell arrays: K cells can cost O(K^2) · [reviewed contract](#b0068) |
| [B0069 · 261–288](../../../../../src/io/statistics_explain.cpp#L261) | Callable definition: void workload(Writer& w,const Report& report) | calls combined, object, text, name; source comment (unverified): // Ratio getters scan captured descriptor/cell arrays: K cells can cost O(K^2) · [reviewed contract](#b0069) |
| [B0070 · 289–290](../../../../../src/io/statistics_explain.cpp#L289) | Explanatory comments or spacing. | source comment (unverified): // The factory has bound this owning context to its actual modes/snapshots. · [reviewed contract](#b0070) |
| [B0071 · 291–320](../../../../../src/io/statistics_explain.cpp#L291) | Callable definition: void render(Writer& w,const Report& r) | calls object, number, text, field; source comment (unverified): // The factory has bound this owning context to its actual modes/snapshots. · [reviewed contract](#b0071) |
| [B0072 · 321–321](../../../../../src/io/statistics_explain.cpp#L321) | Closes surrounding scope/type. |  · [reviewed contract](#b0072) |
| [B0073 · 322–322](../../../../../src/io/statistics_explain.cpp#L322) | Callable definition: StatisticsText write_statistics_json(const Report& report,StatisticsTextLimits limits) | calls render, std::move; returns std::move(w.result) · [reviewed contract](#b0073) |
| [B0074 · 323–326](../../../../../src/io/statistics_explain.cpp#L323) | Callable definition: StatisticsText write_statistics_text(const Report& report,StatisticsTextLimits limits) | calls raw, render, std::move; returns std::move(w.result) · [reviewed contract](#b0074) |
| [B0075 · 327–328](../../../../../src/io/statistics_explain.cpp#L327) | Closes surrounding scope/type. |  · [reviewed contract](#b0075) |

## B0001

[Lines 1–18](../../../../../src/io/statistics_explain.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Writer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a private streaming statistics artifact with independent byte and JSON-item ceilings. |
| inputs / outputs | Caller supplies limits; result retains owning text and the count of emitted JSON values. |
| invariants | Every object/array/scalar/null counts one item; field names do not. Successful raw keeps encoded size &lt;= limit.bytes. Limits exclude spare string capacity, allocator overhead and captured-report storage. |
| ownership | Writer uniquely owns result.text and numeric items; borrowed snapshot/report data is not retained by the encoder. |
| failure | Private partial text/item count is discarded on any exception. Publication occurs only after render and optional human suffix finish. |
| cost | Amortized output-string growth/copy plus emitted items/bytes; no JSON DOM or engine-table traversal. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0002

[Lines 19–22](../../../../../src/io/statistics_explain.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void raw(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and append statistics text bytes. |
| inputs / outputs | Copies a span if it fits limit.bytes minus current encoded length. |
| invariants | All previous successful appends preserve current size &lt;= limit; subtraction is safe. Byte limit is independent of item limit. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | Over-limit append throws resource_limit before append; allocation failure propagates without public partial text. |
| cost | O(span bytes) plus possible string growth; fixed admission check. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0003

[Lines 23–23](../../../../../src/io/statistics_explain.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void item()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge one JSON value item before emitting it. |
| inputs / outputs | Increments result.items unless equal to the caller ceiling. |
| invariants | Every value encoder charges once; object keys call quoted directly and cost no item. Equal-limit rejection prevents size_t overflow even at maximum ceiling. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | resource_limit on exhausted item ceiling; earlier local output is discarded by public caller. |
| cost | Fixed comparison/increment, no successful allocation. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0004

[Lines 24–24](../../../../../src/io/statistics_explain.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:c7f4d07c9ae847162b7f484034e1d13d8cc9c3b8b9e4e38ee0b5dbb5d82658db
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: No item charge here: object keys and string values share escaping. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/statistics_explain.cpp lines 22-26; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/code_specs/files/src/io/statistics_explain.cpp.md](statistics_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0005

[Lines 25–34](../../../../../src/io/statistics_explain.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void quoted(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Quote an internal ASCII report token or key. |
| inputs / outputs | Borrowed ASCII text is escaped for quote/backslash and enclosed in quotes. |
| invariants | Rejects controls and bytes above 126; arbitrary native byte strings use bytes instead. This helper intentionally does not charge a value item so keys remain excluded. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | statistics_encoding on non-ASCII/control input; byte/allocation failures propagate with local partial output. |
| cost | O(input + escaped bytes), output-string growth only. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0006

[Lines 35–35](../../../../../src/io/statistics_explain.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void text(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit one ASCII string value and charge one item. |
| inputs / outputs | Charges item(), then quotes the supplied internal token. |
| invariants | Internal text is ASCII; native values/labels must use the hex-byte route where specified. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed item charge plus ASCII escaping/output bytes. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0007

[Lines 36–40](../../../../../src/io/statistics_explain.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void bytes(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit one arbitrary native byte string as lowercase hexadecimal. |
| inputs / outputs | Charges one string item and produces two ASCII hex digits per input byte. |
| invariants | Preserves embedded NUL, invalid UTF-8 and every byte exactly; does not reinterpret or normalize characters. Repeated raw checks avoid unchecked doubled-length arithmetic. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(input bytes), two output digits each plus quotes; output growth may allocate, no full temporary hex buffer. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0008

[Lines 41–44](../../../../../src/io/statistics_explain.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T>void number(T value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit one exact integer token and charge one item. |
| inputs / outputs | Integral value is converted in a fixed 32-byte local buffer using to_chars. |
| invariants | No floating-point conversion or locale; item charge precedes conversion and final append. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | statistics_encoding on unexpected to_chars failure; item/byte/allocation exhaustion propagates before public return. |
| cost | Bounded numeric formatting plus output append; no formatting heap buffer. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0009

[Lines 45–45](../../../../../src/io/statistics_explain.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boolean(bool value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit an exact Boolean statistics value. |
| inputs / outputs | Charges one item and appends true or false. |
| invariants | Does not conflate Boolean with numeric 0/1. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed item/token work plus output growth. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0010

[Lines 46–46](../../../../../src/io/statistics_explain.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void null()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit an explicit absent/unknown statistics value. |
| inputs / outputs | Charges one item and appends null. |
| invariants | Report null denotes missing/unknown facts, not native scalar SQL NULL or an inferred zero. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed item/token work plus output growth. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0011

[Lines 47–55](../../../../../src/io/statistics_explain.cpp#L47); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Object
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide stack-local statistics object field emission. |
| inputs / outputs | Object borrows Writer, tracks comma state and delegates typed field values. |
| invariants | quoted(key) does not debit an item; each field callback emits exactly one counted value. Caller supplies fixed unique keys; no key set or DOM is created. |
| ownership | Object contains Writer& and a Boolean only; nested lambdas execute synchronously. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed object state; per-field key escaping plus value/output cost. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0012

[Lines 56–56](../../../../../src/io/statistics_explain.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F>void object(F fn)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit one counted JSON object. |
| inputs / outputs | Charges one item, writes braces and invokes a synchronous field callback. |
| invariants | Object container counts separately from its values; partial output stays local on callback failure. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed object item/braces plus callback cost. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0013

[Lines 57–57](../../../../../src/io/statistics_explain.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range,class F>void array(const Range& values,F fn)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit one counted ordered JSON array. |
| inputs / outputs | Charges one container item, iterates values and invokes the element callback once each. |
| invariants | Each callback owns its element item charge; range order and repeated entries are preserved without materializing a second vector. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(range count + element encoding/output bytes). |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0014

[Lines 58–58](../../../../../src/io/statistics_explain.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T>void optional(const std::optional<T>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit an optional numeric value without losing present zero. |
| inputs / outputs | Delegates one number if engaged, else one null item. |
| invariants | Exactly one value item charged through the selected branch. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed branch plus bounded integer/null encoding. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0015

[Lines 59–59](../../../../../src/io/statistics_explain.cpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L59:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/code_specs/files/src/io/statistics_explain.cpp.md](statistics_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0016

[Lines 60–60](../../../../../src/io/statistics_explain.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(runtime::DeltaMode value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell runtime::DeltaMode in this report format. |
| inputs / outputs | An admitted runtime::DeltaMode returns one static literal: maintenance, delta. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0017

[Lines 61–61](../../../../../src/io/statistics_explain.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(runtime::DeltaCompletion value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell runtime::DeltaCompletion in this report format. |
| inputs / outputs | An admitted runtime::DeltaCompletion returns one static literal: automatic, ordered_replay, anchored, root_first. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0018

[Lines 62–62](../../../../../src/io/statistics_explain.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(runtime::LiveMaintenance value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell runtime::LiveMaintenance in this report format. |
| inputs / outputs | An admitted runtime::LiveMaintenance returns one static literal: on_output, incremental, eager. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0019

[Lines 63–63](../../../../../src/io/statistics_explain.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(runtime::ResultView value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell runtime::ResultView in this report format. |
| inputs / outputs | An admitted runtime::ResultView returns one static literal: core, sql. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0020

[Lines 64–64](../../../../../src/io/statistics_explain.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(runtime::PropagationOrder value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell runtime::PropagationOrder in this report format. |
| inputs / outputs | An admitted runtime::PropagationOrder returns one static literal: fifo, lifo. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0021

[Lines 65–65](../../../../../src/io/statistics_explain.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(runtime::ObservationMode value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell runtime::ObservationMode in this report format. |
| inputs / outputs | An admitted runtime::ObservationMode returns one static literal: off, counters, timed, trace. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0022

[Lines 66–66](../../../../../src/io/statistics_explain.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(runtime::DeltaState value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell runtime::DeltaState in this report format. |
| inputs / outputs | An admitted runtime::DeltaState returns one static literal: ready, pending_delta, paused, draining, epoch_prepared, committed_output, committed, aborted. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0023

[Lines 67–67](../../../../../src/io/statistics_explain.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(runtime::SessionState value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell runtime::SessionState in this report format. |
| inputs / outputs | An admitted runtime::SessionState returns one static literal: created, running, paused, stopped, dropped. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0024

[Lines 68–68](../../../../../src/io/statistics_explain.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(runtime::SessionPhase value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell runtime::SessionPhase in this report format. |
| inputs / outputs | An admitted runtime::SessionPhase returns one static literal: ready, pending, paused_pending, draining, prepared, output. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0025

[Lines 69–69](../../../../../src/io/statistics_explain.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(runtime::ObservationOutcome value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell runtime::ObservationOutcome in this report format. |
| inputs / outputs | An admitted runtime::ObservationOutcome returns one static literal: pending, committed, aborted. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0026

[Lines 70–70](../../../../../src/io/statistics_explain.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(runtime::ObservationLayer value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell runtime::ObservationLayer in this report format. |
| inputs / outputs | An admitted runtime::ObservationLayer returns one static literal: support, physical, delta. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0027

[Lines 71–71](../../../../../src/io/statistics_explain.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(runtime::MetricAvailability value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell runtime::MetricAvailability in this report format. |
| inputs / outputs | An admitted runtime::MetricAvailability returns one static literal: unavailable, disabled, available. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0028

[Lines 72–72](../../../../../src/io/statistics_explain.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(runtime::TraceDisposition value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell runtime::TraceDisposition in this report format. |
| inputs / outputs | An admitted runtime::TraceDisposition returns one static literal: disabled, not_sampled, pending, committed, aborted, released. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0029

[Lines 73–73](../../../../../src/io/statistics_explain.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(runtime::MetricKind value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell runtime::MetricKind in this report format. |
| inputs / outputs | An admitted runtime::MetricKind returns one static literal: counter, high_water, timing. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0030

[Lines 74–74](../../../../../src/io/statistics_explain.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(observability::RuntimePresence value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell observability::RuntimePresence in this report format. |
| inputs / outputs | An admitted observability::RuntimePresence returns one static literal: compile_only, live, stopped_retained, released. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0031

[Lines 75–75](../../../../../src/io/statistics_explain.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(observability::IntervalComparison value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell observability::IntervalComparison in this report format. |
| inputs / outputs | An admitted observability::IntervalComparison returns one static literal: same, changed, foreign_owner, saturated, unavailable. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0032

[Lines 76–76](../../../../../src/io/statistics_explain.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(st::Availability value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell st::Availability in this report format. |
| inputs / outputs | An admitted st::Availability returns one static literal: available, budget_exhausted, pending_private_state, unavailable, not_applicable. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0033

[Lines 77–77](../../../../../src/io/statistics_explain.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(st::Freshness value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell st::Freshness in this report format. |
| inputs / outputs | An admitted st::Freshness returns one static literal: current, within_lag, stale, foreign_owner, future_sequence, scope_mismatch. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0034

[Lines 78–78](../../../../../src/io/statistics_explain.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ws::Mode value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell ws::Mode in this report format. |
| inputs / outputs | An admitted ws::Mode returns one static literal: off, counters. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0035

[Lines 79–79](../../../../../src/io/statistics_explain.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ws::Availability value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell ws::Availability in this report format. |
| inputs / outputs | An admitted ws::Availability returns one static literal: disabled, unavailable, exact, sampled, incomplete, lower_bound. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0036

[Lines 80–80](../../../../../src/io/statistics_explain.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ws::Kind value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell ws::Kind in this report format. |
| inputs / outputs | An admitted ws::Kind returns one static literal: physical, occurrence, support, degree, logical. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0037

[Lines 81–81](../../../../../src/io/statistics_explain.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ws::Operation value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell ws::Operation in this report format. |
| inputs / outputs | An admitted ws::Operation returns one static literal: insert, erase. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0038

[Lines 82–82](../../../../../src/io/statistics_explain.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ws::Role value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell ws::Role in this report format. |
| inputs / outputs | An admitted ws::Role returns one static literal: input, adapter, derivation, survivor, parent_support, visible_support, native_touched_degree, generalized_probe. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0039

[Lines 83–83](../../../../../src/io/statistics_explain.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ws::InputScope value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell ws::InputScope in this report format. |
| inputs / outputs | An admitted ws::InputScope returns one static literal: physical_table, logical_epoch. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0040

[Lines 84–84](../../../../../src/io/statistics_explain.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ws::DenominatorScope value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell ws::DenominatorScope in this report format. |
| inputs / outputs | An admitted ws::DenominatorScope returns one static literal: unavailable, all_committed_physical_inputs, committed_physical_stratum, complete_detail_sample_physical_stratum, observed_support_count_changes, observed_visited_routes. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0041

[Lines 85–85](../../../../../src/io/statistics_explain.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(SupportRole value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell SupportRole in this report format. |
| inputs / outputs | An admitted SupportRole returns one static literal: records, survivors, parent_support, visible. |
| invariants | The switch spells the current declared alternatives exactly; it does not infer owner state or report availability from another enum. |
| ownership | Borrows no mutable state; returned const char* refers to static string-literal storage. |
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0042

[Lines 86–86](../../../../../src/io/statistics_explain.cpp#L86); `callable`; `contains_scoped_manual_contract`.

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
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0043

[Lines 87–87](../../../../../src/io/statistics_explain.cpp#L87); `callable`; `contains_scoped_manual_contract`.

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
| failure | Unknown enum values throw statistics_encoding; this is an export contract boundary rather than a catch/recovery mechanism. |
| cost | A finite enum switch, no successful allocation, formatting or runtime-state access. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0044

[Lines 88–98](../../../../../src/io/statistics_explain.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar(Writer& w,const storage::ScalarView& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one captured scalar with exact native type and byte-safe spelling. |
| inputs / outputs | String emits lowercase hex bytes; bool/integer are native JSON tokens; decimal renders canonical text into fixed array; date uses canonical to_string. |
| invariants | encoding labels distinguish hex_bytes from native_canonical. The scalar remains non-null and no numeric widening/rounding is performed. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(scalar/output bytes); decimal uses fixed stack text_capacity, date spelling may allocate; final output grows normally. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0045

[Lines 99–99](../../../../../src/io/statistics_explain.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void row(Writer& w,const st::CapturedKey& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one captured projected key in its stored field order. |
| inputs / outputs | Streams each CapturedKey ScalarView from its owning tuple view. |
| invariants | Preserves repeated and zero-width projections; no key comparison, deduplication or engine lookup occurs. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(key width + scalar spelling/output bytes). |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0046

[Lines 100–102](../../../../../src/io/statistics_explain.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fact(Writer& w,std::optional<std::uint64_t> value,std::string_view reason)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair an optional numeric fact with its reason for absence. |
| inputs / outputs | Engaged number writes reason=null; absent number writes value=null and supplied reason. |
| invariants | Exact empty/zero facts remain numeric; unknownness is not silently turned into zero. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed object fields plus reason/digit bytes. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0047

[Lines 103–106](../../../../../src/io/statistics_explain.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void observation_options(Writer& w,const ObservationOptions& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode O07 observation options. |
| inputs / outputs | Writes mode, trace capacity, deterministic period/offset and trace-timing flag. |
| invariants | Describes captured requested configuration only; export reads no clocks and changes no observation mode. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed option fields and output bytes. |
| Design | [docs/observability.md §Observation modes and metric values](../../../../observability.md), [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0048

[Lines 107–118](../../../../../src/io/statistics_explain.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void delta_options(Writer& w,const DeltaOptions& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode captured requested DeltaOptions inside v3 statistics context. |
| inputs / outputs | Writes requested modes, optional work limits, support/derivation/spool quotas and O07 options. |
| invariants | Omits legacy support.memory_limit_bytes only when equal to its default, preserving the admitted report shape; fields describe their distinct work/quota domains. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed field count plus nested observation options, no state scan. |
| Design | [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0049

[Lines 119–123](../../../../../src/io/statistics_explain.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void mode_facts(Writer& w,const ws::ModeFacts& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode workload snapshot requested/resolved mode facts. |
| inputs / outputs | Writes whether owner is Delta and its requested/resolved mode/completion, live maintenance and result view. |
| invariants | Current and previous segment callers pass their own facts; historical intervals are not relabeled using the current owner. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed scalar/enum fields. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md §Transactional workload observations](../../../../statistics.md) |

## B0050

[Lines 124–128](../../../../../src/io/statistics_explain.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void configuration(Writer& w,const ObservationConfiguration& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode begin-bound O07 configuration in statistics output. |
| inputs / outputs | Writes owner/generation/saturation, resolved modes/view/query factors and captured requested options. |
| invariants | Configuration belongs to the captured attempt/current context, not a reconstruction from later settings; saturation remains visible. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed fields plus requested-options formatting. |
| Design | [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0051

[Lines 129–133](../../../../../src/io/statistics_explain.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void labels(Writer& w,const std::shared_ptr<const DeclaredBenchmarkContext>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode optional caller-declared byte labels safely. |
| inputs / outputs | Absent declaration is null; present declaration has explicit unmeasured authority and four optional hex labels. |
| invariants | Labels retain arbitrary bytes and empty-versus-absent distinction; they do not establish measured input/codec/sink identity. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed label count + twice present label bytes/output. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0052

[Lines 134–147](../../../../../src/io/statistics_explain.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void observation_summary(Writer& w,const std::optional<ObservationSummary>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one captured O07 summary with honest numeric availability. |
| inputs / outputs | Absent summary is null; present summary has sequence/layer/outcome, begin configuration, labels and registry metrics. |
| invariants | Raw counters remain tagged disabled/lower_bound/exact. Only available and unsaturated metrics enter the usable fact; unavailable/disabled/saturated facts emit null with reason. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(registry size + captured config/label/output bytes); raw/fact encoding repeats numeric metadata but performs no measurement. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0053

[Lines 148–163](../../../../../src/io/statistics_explain.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void o07(Writer& w,const Report& report)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the O07 portion of the statistics report. |
| inputs / outputs | Writes options, recorded/current owner binding, count status/current/last summaries and retained/dropped trace metadata. |
| invariants | Off observation suppresses lifetime counts. Trace records and cursor details are explicitly outside this export; retaining trace for a report does not cause traversal of record payloads here. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed context fields plus two registry summaries/configurations/labels; trace.size() is metadata access, not trace iteration. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0054

[Lines 164–167](../../../../../src/io/statistics_explain.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void limits(Writer& w,const st::Limits& v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the admitted owner-state scan limits. |
| inputs / outputs | Writes work, row, distinct-key, logical accounted-byte, projection-width and heavy-key ceilings. |
| invariants | Copied limits retain their separate model; not output bytes/items, allocator totals or an update work grant. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed numeric field count. |
| Design | [docs/statistics.md §Requests, budgets, and byte accounting](../../../../statistics.md), [docs/statistics.md §Freshness and lifecycle](../../../../statistics.md) |

## B0055

[Lines 168–171](../../../../../src/io/statistics_explain.cpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void usage(Writer& w,const st::Usage& v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the owner capture actual selected usage. |
| inputs / outputs | Writes charged work/rows/keys/modeled bytes and row/histogram/heavy capacity maxima. |
| invariants | Usage describes the already completed explicit capture; does not charge a scan or claim total allocator memory. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed numeric field count. |
| Design | [docs/statistics.md §Requests, budgets, and byte accounting](../../../../statistics.md), [docs/statistics.md §Freshness and lifecycle](../../../../statistics.md) |

## B0056

[Lines 172–178](../../../../../src/io/statistics_explain.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void layout(Writer& w,const storage::TupleLayout& v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a captured native tuple layout. |
| inputs / outputs | Writes layout ID/context version/binary binding, optional source origin and ordered field type/variable/decimal metadata. |
| invariants | Hex binding preserves arbitrary bytes; absent origin/variable/typemod is null. Layout metadata is descriptive, not import/proof authority. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(layout width + binding/output bytes); no row payload traversal. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0057

[Lines 179–187](../../../../../src/io/statistics_explain.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void selection(Writer& w,const st::CapturedSelection& v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the exact owner-state population and ordered projection request. |
| inputs / outputs | Selection variant emits source/node-role/occurrence/index identity plus fields array or null. |
| invariants | null fields means default/full selection; an empty array means zero-width projection. Repeated field IDs and their order survive. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(projection width + output bytes), fixed variant dispatch. |
| Design | [include/crown/runtime/owner_statistics.hpp](../../../../../include/crown/runtime/owner_statistics.hpp), [docs/statistics.md §Requests, budgets, and byte accounting](../../../../statistics.md), [docs/statistics.md §Freshness and lifecycle](../../../../statistics.md) |

## B0058

[Lines 188–196](../../../../../src/io/statistics_explain.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void distribution(Writer& w,const st::CapturedDistribution& v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an already captured population distribution with completion metadata. |
| inputs / outputs | Writes completion/visited, optional NDV, exact-only histogram, optional top-k keys/counts and unknown reason. |
| invariants | Budget-exhausted histogram is null; optional facts/keys follow captured availability. No partial counts are promoted to an exact population or sorted during export. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(histogram entries + retained heavy keys/width/scalar bytes + output); no engine traversal. |
| Design | [docs/statistics.md §Requests, budgets, and byte accounting](../../../../statistics.md), [docs/statistics.md §Freshness and lifecycle](../../../../statistics.md) |

## B0059

[Lines 197–197](../../../../../src/io/statistics_explain.cpp#L197); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L197-L197:sha256:70de0a4b7d2063147c96f382027172d08cc6aa5356debd4ae22618cbf1554789
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Format captured components only; this never scans the live engine tables. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/statistics_explain.cpp lines 195-199; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/code_specs/files/src/io/statistics_explain.cpp.md](statistics_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0060

[Lines 198–216](../../../../../src/io/statistics_explain.cpp#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void state(Writer& w,const Report& report)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode explicit owner-state selection results or their absence. |
| inputs / outputs | State availability distinguishes released/not requested and captured status; requested live capture writes stamp, limits/usage/components. |
| invariants | Each component retains selection, availability, cardinality/distribution and layout/invalidation facts. Storage invalidation is not committed-data freshness; pending metadata does not expose tentative rows. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | O(captured components + requested projection/layout/distribution/key bytes + output), never a fresh engine-table scan. |
| Design | [docs/statistics.md §Requests, budgets, and byte accounting](../../../../statistics.md), [docs/statistics.md §Freshness and lifecycle](../../../../statistics.md) |

## B0061

[Lines 217–218](../../../../../src/io/statistics_explain.cpp#L217); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void workload_options(Writer& w,const ws::Options& v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode C01 workload collector options. |
| inputs / outputs | Writes mode, maximum cells, period/offset and detail budget. |
| invariants | O07 observation options are separate; this does not enable/disable the collector or perform sampling. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed scalar/enum fields. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md §Transactional workload observations](../../../../statistics.md) |

## B0062

[Lines 219–223](../../../../../src/io/statistics_explain.cpp#L219); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stamp(Writer& w,const ws::Stamp& v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a workload interval stamp and saturation flags. |
| inputs / outputs | Writes owner, committed/start epochs, reset/configuration generations, segment and format version. |
| invariants | All interval identity fields matter; saturated generation flags prevent treating a capped value as unique. Export does not compare against a live owner. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed numeric/Boolean field count. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md §Transactional workload observations](../../../../statistics.md) |

## B0063

[Lines 224–230](../../../../../src/io/statistics_explain.cpp#L224); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void metadata(Writer& w,const ws::Metadata& v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode workload attempt/detail metadata without claiming an uncapped total. |
| inputs / outputs | Writes attempts, commits/aborts, selection/completion/truncation and collection action counts plus protocol flags. |
| invariants | Any saturated metadata labels numeric_status lower_bound; raw counters remain available for diagnosis, not as exact ratios. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed metadata field count, no iteration over events. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md §Transactional workload observations](../../../../statistics.md) |

## B0064

[Lines 231–237](../../../../../src/io/statistics_explain.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void descriptor(Writer& w,const ws::Descriptor& v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one admitted workload descriptor and optional route IDs. |
| inputs / outputs | Writes kind/scope/operation/role, initiating physical table if applicable, node/occurrence/edge/index and event operation. |
| invariants | Logical-epoch scope has null initiating_table; numeric scope is not mistaken for a physical input denominator. IDs describe the snapshot route, not retained row pins. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed variant/optional fields, no descriptor lookup or event scan. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md §Transactional workload observations](../../../../statistics.md) |

## B0065

[Lines 238–238](../../../../../src/io/statistics_explain.cpp#L238); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L238-L238:sha256:2e3d0027cc3d4a86faba94ca18687543eff479a9370679511e2ff931d1cd5d51
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Keep exact/sample integer ratios; a ratio of clipped lower bounds is unknown. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/statistics_explain.cpp lines 236-240; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/code_specs/files/src/io/statistics_explain.cpp.md](statistics_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0066

[Lines 239–246](../../../../../src/io/statistics_explain.cpp#L239); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fraction(Writer& w,const ws::Fraction& v,bool clipped=false)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a usable ratio or explicit unavailable numerator/denominator. |
| inputs / outputs | Exact/sampled Fraction writes integer numerator/denominator; clipping or other availability writes nulls plus a reason. |
| invariants | No division, extrapolation or ratio of lower bounds is emitted. Caller clipping overrides availability to unavailable while retaining denominator scope. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed formatting after the caller computed a Fraction; ratio-computation cost is separate. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md §Transactional workload observations](../../../../statistics.md) |

## B0067

[Lines 247–258](../../../../../src/io/statistics_explain.cpp#L247); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cell(Writer& w,const ws::Cell& v,const ws::Descriptor& d,bool global_saturation)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one workload event-population cell and bounded histogram. |
| inputs / outputs | Writes raw counters, population label, lower-bound status, nonempty unsaturated extrema and all 65 bins. |
| invariants | Support after-values, generalized pre-probe presence, touched degrees, adapter visits and input census remain distinct populations. Global saturation suppresses extrema as well as local saturation. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | A text/enum/output-limit or allocation failure propagates; the caller discards the private partial buffer. This helper adds no catch or rollback layer and publishes no partial artifact. |
| cost | Fixed counters and 65-bin array per cell plus digit/output bytes; no sorting or population traversal. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md §Transactional workload observations](../../../../statistics.md) |

## B0068

[Lines 259–260](../../../../../src/io/statistics_explain.cpp#L259); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L259-L260:sha256:64489a2c021988a6998d34b4208b7d8f15d52efb583cabbec4c542e0c0a691f3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Ratio getters scan captured descriptor/cell arrays: K cells can cost O(K^2) here. This explicit export does no live-state scan or update-path work. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/statistics_explain.cpp lines 257-262; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/code_specs/files/src/io/statistics_explain.cpp.md](statistics_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0069

[Lines 261–288](../../../../../src/io/statistics_explain.cpp#L261); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void workload(Writer& w,const Report& report)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the captured C01 workload snapshot, current ratios and previous raw segment. |
| inputs / outputs | Released/off facts become null; enabled snapshot emits mode/stamp/metadata, descriptor cells and four ratios each, optional prior cells and memory components. |
| invariants | Uses aligned immutable descriptors/cells from factory. Previous segment exports raw observations only. Sampling is deterministic, no extrapolation; arrival rate is null because no clock exists. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | Snapshot/factory alignment is a precondition; enum/item/byte/allocation errors abort the private export. No catch, state mutation or sampling retry is introduced. |
| cost | For K admitted descriptors, current derived-ratio lookup can cost O(K^2): input_share/events and detail_availability scan captured arrays. Cell/bin output costs O(K*65); previous cells add the same raw-width cost. No engine-table access or update-path overhead. |
| Design | [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [docs/statistics.md §Transactional workload observations](../../../../statistics.md), [docs/statistics.md §Requests, budgets, and byte accounting](../../../../statistics.md), [docs/statistics.md §Freshness and lifecycle](../../../../statistics.md) |

## B0070

[Lines 289–290](../../../../../src/io/statistics_explain.cpp#L289); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L289-L290:sha256:fbc32de6c59938d4e7ddadecee5a6fbc8d533dbbabadec1df743bfbf4bb15883
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: The factory has bound this owning context to its actual modes/snapshots. Capability constants describe this v3 export, not repository task acceptance. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/statistics_explain.cpp lines 287-292; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/code_specs/files/src/io/statistics_explain.cpp.md](statistics_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0071

[Lines 291–320](../../../../../src/io/statistics_explain.cpp#L291); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void render(Writer& w,const Report& r)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose the complete closed v3 owner-statistics JSON artifact. |
| inputs / outputs | Factory-produced report supplies actual plan/boundary/modes/session, O07 summaries, requested C01 state/workload and optional comparison. |
| invariants | Factory binding assures live/released mode options/profile exist, checked height is engaged and captured arrays align. Digests and height are descriptive; frozen capability fields add no cost selection, global optimum or repository acceptance status. |
| ownership | Reads borrowed immutable report/descriptor data synchronously; only the local Writer output state changes. No owner, table, work grant or captured report is mutated. |
| failure | Any internal enum/encoding/item/byte/allocation failure propagates before publication; report/owner facts are unchanged. |
| cost | Captured-state formatting plus workload O(K^2) ratios/65-bin cells and output bytes; only string/result growth, no fresh owner table traversal. |
| Design | [schemas/statistics-explain-v3.schema.json](../../../../../schemas/statistics-explain-v3.schema.json), [include/crown/observability/statistics_explain.hpp](../../../../../include/crown/observability/statistics_explain.hpp), [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0072

[Lines 321–321](../../../../../src/io/statistics_explain.cpp#L321); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L321-L321:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing implementation scope at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/code_specs/files/src/io/statistics_explain.cpp.md](statistics_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0073

[Lines 322–322](../../../../../src/io/statistics_explain.cpp#L322); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StatisticsText write_statistics_json(const Report& report,StatisticsTextLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one complete owning statistics JSON artifact and its value count. |
| inputs / outputs | Constructs local Writer, renders the report, then moves result out. |
| invariants | Exactly one independent byte and item budget; item count excludes object keys and includes every JSON value. No partial artifact is returned. |
| ownership | StatisticsText owns its text and item count after report/runtime destruction; no report pointer is retained. |
| failure | Encoding/resource/allocation failure unwinds local storage; no owner mutation or recovery handler is needed. |
| cost | Full render cost and ordinary output-string capacity; final move transfers the completed storage. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0074

[Lines 323–326](../../../../../src/io/statistics_explain.cpp#L323); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StatisticsText write_statistics_text(const Report& report,StatisticsTextLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish human statistics text with the same complete JSON and item count. |
| inputs / outputs | Adds a fixed ASCII introduction, renders v3 JSON, appends newline, then moves result. |
| invariants | Introduction/newline consume byte allowance but no JSON items. The JSON portion preserves exact/unknown/population/type rules and the fixed capability text describes report scope. |
| ownership | Returned StatisticsText owns complete text independently of report and engine. |
| failure | Any prefix/render/suffix byte/item/encoding/allocation failure returns no partial text and leaves captures/owner unchanged. |
| cost | Full render cost plus fixed prefix/suffix append; no separate JSON DOM or full intermediate JSON string. |
| Design | [include/crown/io/statistics_explain.hpp](../../../../../include/crown/io/statistics_explain.hpp), [docs/statistics.md §Export, unknown values and errors](../../../../statistics.md) |

## B0075

[Lines 327–328](../../../../../src/io/statistics_explain.cpp#L327); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L327-L328:sha256:938de74be97bf3aba7872a61ba0e42084008c81e8a202a612134c755aaf7fa06
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing implementation scope at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/statistics_explain.cpp](../../../../../src/io/statistics_explain.cpp), [docs/code_specs/files/src/io/statistics_explain.cpp.md](statistics_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |
