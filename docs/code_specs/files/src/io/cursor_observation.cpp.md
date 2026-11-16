# `src/io/cursor_observation.cpp` — block usage map

[Source](../../../../../src/io/cursor_observation.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `c6fbc99e3c114c5c75abc531709d5414b152c0cdb2d72ad0045de0874769e283`. 147 lines partitioned into 40 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/io/cursor_observation.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 8–26](../../../../../src/io/cursor_observation.cpp#L8) | Callable definition: void utf8(std::string_view text) | calls size, Error; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 27–31](../../../../../src/io/cursor_observation.cpp#L27) | declares types or opens a type body. | source comment (unverified): // Private JSON text: byte cap limits encoded length, not allocator capacity. · [reviewed contract](#b0003) |
| [B0004 · 32–32](../../../../../src/io/cursor_observation.cpp#L32) | Callable definition: explicit Writer(std::size_t bytes):limit(bytes) | calls limit · [reviewed contract](#b0004) |
| [B0005 · 33–36](../../../../../src/io/cursor_observation.cpp#L33) | Callable definition: void raw(std::string_view value) | calls size, Error, append · [reviewed contract](#b0005) |
| [B0006 · 37–47](../../../../../src/io/cursor_observation.cpp#L37) | Callable definition: void quote(std::string_view value,bool dot=false) | calls utf8, raw; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 48–52](../../../../../src/io/cursor_observation.cpp#L48) | Callable definition: template&lt;class Integer&gt; void number(Integer value) | calls std::to_chars, Error, raw · [reviewed contract](#b0007) |
| [B0008 · 53–53](../../../../../src/io/cursor_observation.cpp#L53) | Callable definition: void boolean(bool value) | calls raw · [reviewed contract](#b0008) |
| [B0009 · 54–54](../../../../../src/io/cursor_observation.cpp#L54) | Callable definition: void null() | calls raw · [reviewed contract](#b0009) |
| [B0010 · 55–55](../../../../../src/io/cursor_observation.cpp#L55) | Callable definition: template&lt;class T&gt; void optional(const std::optional&lt;T&gt;& value) | calls number, null · [reviewed contract](#b0010) |
| [B0011 · 56–58](../../../../../src/io/cursor_observation.cpp#L56) | Callable definition: template&lt;class Range,class Fn&gt; void array(const Range& values,Fn fn) | calls raw, fn; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 59–66](../../../../../src/io/cursor_observation.cpp#L59) | Type/record definition: struct Object |  · [reviewed contract](#b0012) |
| [B0013 · 67–67](../../../../../src/io/cursor_observation.cpp#L67) | Callable definition: template&lt;class Fn&gt; void object(Fn fn) | calls raw, fn · [reviewed contract](#b0013) |
| [B0014 · 68–68](../../../../../src/io/cursor_observation.cpp#L68) | Callable definition: template&lt;class Range&gt; void ids(const Range& values) | calls array, number · [reviewed contract](#b0014) |
| [B0015 · 69–71](../../../../../src/io/cursor_observation.cpp#L69) | Closes surrounding scope/type. | source comment (unverified): // DTO spelling only: unknown enum fallback does not validate owner/state data. · [reviewed contract](#b0015) |
| [B0016 · 72–72](../../../../../src/io/cursor_observation.cpp#L72) | Callable definition: const char* name(ResultCursorState v) | calls ; returns @; @; source comment (unverified): // DTO spelling only: unknown enum fallback does not validate owner/state data. · [reviewed contract](#b0016) |
| [B0017 · 73–73](../../../../../src/io/cursor_observation.cpp#L73) | Callable definition: const char* name(CursorTerminalReason v) | calls ; returns @; @ · [reviewed contract](#b0017) |
| [B0018 · 74–74](../../../../../src/io/cursor_observation.cpp#L74) | Callable definition: const char* name(CursorObservationSource v) | calls ; returns @; @ · [reviewed contract](#b0018) |
| [B0019 · 75–75](../../../../../src/io/cursor_observation.cpp#L75) | Callable definition: const char* name(MetricAvailability v) | calls ; returns @; @ · [reviewed contract](#b0019) |
| [B0020 · 76–76](../../../../../src/io/cursor_observation.cpp#L76) | Callable definition: const char* name(MetricKind v) | calls ; returns @; @ · [reviewed contract](#b0020) |
| [B0021 · 77–77](../../../../../src/io/cursor_observation.cpp#L77) | Callable definition: const char* name(ResultView v) | calls ; returns @; @ · [reviewed contract](#b0021) |
| [B0022 · 78–78](../../../../../src/io/cursor_observation.cpp#L78) | Callable definition: const char* name(SnapshotSide v) | calls ; returns @; @ · [reviewed contract](#b0022) |
| [B0023 · 79–79](../../../../../src/io/cursor_observation.cpp#L79) | Callable definition: const char* name(ObservationMode v) | calls ; returns @; @ · [reviewed contract](#b0023) |
| [B0024 · 80–80](../../../../../src/io/cursor_observation.cpp#L80) | Callable definition: const char* name(DeltaMode v) | calls ; returns @; @ · [reviewed contract](#b0024) |
| [B0025 · 81–81](../../../../../src/io/cursor_observation.cpp#L81) | Callable definition: const char* name(DeltaCompletion v) | calls ; returns @; @ · [reviewed contract](#b0025) |
| [B0026 · 82–82](../../../../../src/io/cursor_observation.cpp#L82) | Callable definition: const char* name(LiveMaintenance v) | calls ; returns @; @ · [reviewed contract](#b0026) |
| [B0027 · 83–83](../../../../../src/io/cursor_observation.cpp#L83) | Callable definition: const char* name(PropagationOrder v) | calls ; returns @; @ · [reviewed contract](#b0027) |
| [B0028 · 84–84](../../../../../src/io/cursor_observation.cpp#L84) | Callable definition: const char* name(NodeKind v) | calls ; returns @; @ · [reviewed contract](#b0028) |
| [B0029 · 85–85](../../../../../src/io/cursor_observation.cpp#L85) | Callable definition: void work(Writer& w,const CursorWork& value) | calls object, number · [reviewed contract](#b0029) |
| [B0030 · 86–97](../../../../../src/io/cursor_observation.cpp#L86) | Callable definition: void delta_options(Writer& w,const DeltaOptions& d) | calls object, text, name, field · [reviewed contract](#b0030) |
| [B0031 · 98–99](../../../../../src/io/cursor_observation.cpp#L98) | Explanatory comments or spacing. | source comment (unverified): // Suppress stale disabled/unavailable payloads rather than exporting a zero. · [reviewed contract](#b0031) |
| [B0032 · 100–103](../../../../../src/io/cursor_observation.cpp#L100) | Callable definition: void metric(Writer& w,const MetricValue& value) | calls object, text, name, field; source comment (unverified): // Suppress stale disabled/unavailable payloads rather than exporting a zero. · [reviewed contract](#b0032) |
| [B0033 · 104–110](../../../../../src/io/cursor_observation.cpp#L104) | Callable definition: void configuration(Writer& w,const std::optional&lt;ObservationConfiguration&gt;& value) | calls null, object, text, number · [reviewed contract](#b0033) |
| [B0034 · 111–112](../../../../../src/io/cursor_observation.cpp#L111) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0034) |
| [B0035 · 113–131](../../../../../src/io/cursor_observation.cpp#L113) | Callable definition: std::string write_cursor_observation_json(const CursorObservation& value,std::size_t max_bytes) | calls w, object, text, number; returns std::move(w.out); source comment (unverified): // Format supplied lifecycle metadata; this does not authenticate DTO consistency. · [reviewed contract](#b0035) |
| [B0036 · 132–132](../../../../../src/io/cursor_observation.cpp#L132) | Explanatory comments or spacing. | source comment (unverified): // Captured arrays are read directly; no fresh engine scan or total-memory proof. · [reviewed contract](#b0036) |
| [B0037 · 133–144](../../../../../src/io/cursor_observation.cpp#L133) | Callable definition: template&lt;class Gauges&gt; std::string gauges_json(const Gauges& value,std::size_t max_bytes) | calls w, object, text, number; returns std::move(w.out); source comment (unverified): // Captured arrays are read directly; no fresh engine scan or total-memory proof. · [reviewed contract](#b0037) |
| [B0038 · 145–145](../../../../../src/io/cursor_observation.cpp#L145) | Callable definition: std::string write_committed_state_gauges_json(const CommittedStateGauges& value,std::size_t max_bytes) | calls gauges_json; returns gauges_json(value,max_bytes) · [reviewed contract](#b0038) |
| [B0039 · 146–146](../../../../../src/io/cursor_observation.cpp#L146) | Callable definition: std::string write_committed_state_gauges_json(const CapturedStateGauges& value,std::size_t max_bytes) | calls gauges_json; returns gauges_json(value,max_bytes) · [reviewed contract](#b0039) |
| [B0040 · 147–147](../../../../../src/io/cursor_observation.cpp#L147) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0040) |

## B0001

[Lines 1–7](../../../../../src/io/cursor_observation.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using namespace runtime;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind cursor/gauge transport to existing runtime descriptor types. |
| inputs / outputs | Private name import resolves public snapshot/metric/option enums and structs. |
| invariants | No runtime registration, validation, account or mutable cursor is created. |
| ownership | No independent storage or owner. |
| failure | Declaration mismatches fail compilation, not runtime recovery. |
| cost | Compile-time name lookup only. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0002

[Lines 8–26](../../../../../src/io/cursor_observation.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void utf8(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate strict UTF-8 for descriptive cursor/gauge text. |
| inputs / outputs | Rejects malformed leaders/continuations, truncation, overlong forms, surrogates and code points above U+10FFFF. |
| invariants | Does not rewrite native input values; later quoting escapes permitted ASCII controls. Error wording retains run-context compatibility. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | text_encoding on first invalid sequence; caller DTO is unchanged. |
| cost | O(input text bytes), fixed inline state and no successful allocation. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0003

[Lines 27–31](../../../../../src/io/cursor_observation.cpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Writer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one private byte-capped cursor/gauge JSON string. |
| inputs / outputs | Local ordinary string and max encoded length are passed through raw/quote/number/array/object helpers. |
| invariants | Successful out.size()&lt;=limit; cap is final encoded bytes, not string capacity, captured arrays, total allocator memory or CPU. |
| ownership | Writer owns only output; input DTO/captured arrays are borrowed synchronously. |
| failure | Encoding/byte/allocation failure discards private output; no partial string or runtime state publication. |
| cost | Amortized string growth/copy proportional to output bytes; no JSON DOM, clocks or cursor instrumentation. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0004

[Lines 32–32](../../../../../src/io/cursor_observation.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Writer(std::size_t bytes):limit(bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize an empty local JSON writer. |
| inputs / outputs | Stores max byte ceiling and default empty string. |
| invariants | Zero cap is a valid request that cannot hold nonempty artifact; no eager reserve or account. |
| ownership | Constructs private ordinary output owner. |
| failure | No explicit error path; writes enforce cap. |
| cost | Fixed initialization. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0005

[Lines 33–36](../../../../../src/io/cursor_observation.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void raw(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and append encoded output bytes safely. |
| inputs / outputs | Checks remaining limit by subtraction before string append. |
| invariants | No size overflow; every encoding fragment uses this gate, but prior UTF-8 scans/array traversal are not CPU-metered by byte cap. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | resource_limit before oversized append; ordinary allocation/length errors propagate. |
| cost | O(span bytes) plus string capacity relocation as needed. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0006

[Lines 37–47](../../../../../src/io/cursor_observation.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void quote(std::string_view value,bool dot=false)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Quote valid UTF-8 JSON text with optional DOT-style control escaping. |
| inputs / outputs | Validates complete text first, then writes escaped quotes/backslashes/control sequences via capped raw. |
| invariants | No initial raw-length shortcut here: validation can scan text before cap rejection. No caller data mutation or schema/authority admission. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | UTF-8 scan + O(input/encoded bytes) escaping, output growth; no full temporary quote buffer. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0007

[Lines 48–52](../../../../../src/io/cursor_observation.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Integer> void number(Integer value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit one exact integral numeric token. |
| inputs / outputs | to_chars uses fixed 32-byte stack storage and appends checked conversion result. |
| invariants | No float/locale/stream coercion; result error becomes explain_encoding. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Bounded integer formatting plus token append, no separate formatting allocation. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0008

[Lines 53–53](../../../../../src/io/cursor_observation.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boolean(bool value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit Boolean metadata exactly. |
| inputs / outputs | Appends true or false. |
| invariants | Does not conflate bool and numeric totals. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed token work plus output growth. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0009

[Lines 54–54](../../../../../src/io/cursor_observation.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void null()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit absent/unavailable metadata explicitly. |
| inputs / outputs | Appends null. |
| invariants | Null does not fabricate zero or admit SQL nullable source data. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed token work plus output growth. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0010

[Lines 55–55](../../../../../src/io/cursor_observation.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void optional(const std::optional<T>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve optional numeric limit presence. |
| inputs / outputs | Present value is number, absent is null. |
| invariants | Zero and absent remain different budget declarations. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed branch plus numeric/null output. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0011

[Lines 56–58](../../../../../src/io/cursor_observation.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range,class Fn> void array(const Range& values,Fn fn)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stream an ordered captured range to JSON. |
| inputs / outputs | Calls synchronous element encoder in order with array delimiters. |
| invariants | No copied range, sorting, cursor advance or snapshot creation; callbacks emit complete values. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | O(range count + callback/output bytes), ordinary final-buffer growth only. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0012

[Lines 59–66](../../../../../src/io/cursor_observation.cpp#L59); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Object
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide borrowing object field emission. |
| inputs / outputs | Tracks first field, quotes keys and delegates numeric/text/Boolean/null values. |
| invariants | Caller provides fixed unique keys; no DOM/key map or authority check. Stack Object holds Writer& only. |
| ownership | Object borrows Writer during synchronous callback; owns no capture. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed state and per-field key/value formatting. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0013

[Lines 67–67](../../../../../src/io/cursor_observation.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Fn> void object(Fn fn)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stream one callback-built JSON object. |
| inputs / outputs | Writes braces and supplies fresh Object. |
| invariants | Any partial object remains private until enclosing public writer returns. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed braces/state plus callback output cost. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0014

[Lines 68–68](../../../../../src/io/cursor_observation.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range> void ids(const Range& values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stream ordered native IDs as numbers. |
| inputs / outputs | Maps item.value through number in a JSON array. |
| invariants | No ID validation/renumbering; caller snapshot supplies meaning. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | O(ID count+digit bytes), no temporary vector. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0015

[Lines 69–71](../../../../../src/io/cursor_observation.cpp#L69); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L71:sha256:644ba7a2283c7772dbb80bd413f7dcdcc82337fa896ad26505885d5a6b0cba66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. Trailing source note states: DTO spelling only: unknown enum fallback does not validate owner/state data. It remains prose guidance, not a certified executable claim. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. Any trailing comment in this block is guidance only and adds no runtime invariant. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/cursor_observation.cpp](../../../../../src/io/cursor_observation.cpp), [docs/code_specs/files/src/io/cursor_observation.cpp.md](cursor_observation.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0016

[Lines 72–72](../../../../../src/io/cursor_observation.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResultCursorState v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive ResultCursorState without inferring authority. |
| inputs / outputs | Declared cases map to active, exhausted, cancelled, failed; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | No explicit throw; unknown fallback can make caller-supplied DTO fail an external closed schema. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0017

[Lines 73–73](../../../../../src/io/cursor_observation.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(CursorTerminalReason v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive CursorTerminalReason without inferring authority. |
| inputs / outputs | Declared cases map to not_recorded, none, exhausted, explicit_cancel, destruction, move_replacement, invalidated, startup_failure, next_failure; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | No explicit throw; unknown fallback can make caller-supplied DTO fail an external closed schema. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0018

[Lines 74–74](../../../../../src/io/cursor_observation.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(CursorObservationSource v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive CursorObservationSource without inferring authority. |
| inputs / outputs | Declared cases map to committed_results, epoch_visible, epoch_witnesses, epoch_keys, epoch_bucket; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | No explicit throw; unknown fallback can make caller-supplied DTO fail an external closed schema. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0019

[Lines 75–75](../../../../../src/io/cursor_observation.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(MetricAvailability v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive MetricAvailability without inferring authority. |
| inputs / outputs | Declared cases map to unavailable, disabled, available; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | No explicit throw; unknown fallback can make caller-supplied DTO fail an external closed schema. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0020

[Lines 76–76](../../../../../src/io/cursor_observation.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(MetricKind v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive MetricKind without inferring authority. |
| inputs / outputs | Declared cases map to counter, high_water, timing; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | No explicit throw; unknown fallback can make caller-supplied DTO fail an external closed schema. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0021

[Lines 77–77](../../../../../src/io/cursor_observation.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResultView v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive ResultView without inferring authority. |
| inputs / outputs | Declared cases map to core, sql; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | No explicit throw; unknown fallback can make caller-supplied DTO fail an external closed schema. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0022

[Lines 78–78](../../../../../src/io/cursor_observation.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(SnapshotSide v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive SnapshotSide without inferring authority. |
| inputs / outputs | Declared cases map to before, after; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | No explicit throw; unknown fallback can make caller-supplied DTO fail an external closed schema. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0023

[Lines 79–79](../../../../../src/io/cursor_observation.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ObservationMode v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive ObservationMode without inferring authority. |
| inputs / outputs | Declared cases map to off, counters, timed, trace; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | No explicit throw; unknown fallback can make caller-supplied DTO fail an external closed schema. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0024

[Lines 80–80](../../../../../src/io/cursor_observation.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(DeltaMode v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive DeltaMode without inferring authority. |
| inputs / outputs | Declared cases map to maintenance, delta; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | No explicit throw; unknown fallback can make caller-supplied DTO fail an external closed schema. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0025

[Lines 81–81](../../../../../src/io/cursor_observation.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(DeltaCompletion v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive DeltaCompletion without inferring authority. |
| inputs / outputs | Declared cases map to automatic, ordered_replay, anchored, root_first; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | No explicit throw; unknown fallback can make caller-supplied DTO fail an external closed schema. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0026

[Lines 82–82](../../../../../src/io/cursor_observation.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(LiveMaintenance v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive LiveMaintenance without inferring authority. |
| inputs / outputs | Declared cases map to on_output, incremental, eager; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | No explicit throw; unknown fallback can make caller-supplied DTO fail an external closed schema. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0027

[Lines 83–83](../../../../../src/io/cursor_observation.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(PropagationOrder v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive PropagationOrder without inferring authority. |
| inputs / outputs | Declared cases map to fifo, lifo; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | No explicit throw; unknown fallback can make caller-supplied DTO fail an external closed schema. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0028

[Lines 84–84](../../../../../src/io/cursor_observation.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(NodeKind v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell descriptive NodeKind without inferring authority. |
| inputs / outputs | Declared cases map to native, generalized; unsupported representation maps to static unknown. |
| invariants | This is a formatter, not enum/schema/owner consistency admission. Unknown cannot be interpreted as a successful checked proof or metric availability. |
| ownership | Returns static literal pointer, no data ownership. |
| failure | No explicit throw; unknown fallback can make caller-supplied DTO fail an external closed schema. |
| cost | Finite switch/static text, no allocation or producer/cursor access. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0029

[Lines 85–85](../../../../../src/io/cursor_observation.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void work(Writer& w,const CursorWork& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one mandatory cursor work phase without recomputing it. |
| inputs / outputs | Writes work/calls/route/descriptor/frame/cursor/lookup/key/equality/output/binding/overlay/fragment/witness counters. |
| invariants | Counters are the existing abstract cursor-action model, not complete scalar CPU, allocation or I/O. Category values/last phase are not blindly additive. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed counter field count plus digits, no cursor execution. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0030

[Lines 86–97](../../../../../src/io/cursor_observation.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void delta_options(Writer& w,const DeltaOptions& d)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode captured requested DeltaOptions in cursor begin configuration. |
| inputs / outputs | Writes requested mode/completion/live/view, distinct work/spool/support/derivation caps, propagation/capture and O07 sampling options. |
| invariants | Nondefault legacy support.memory_limit_bytes emitted conditionally for compatibility; values are declared options, not actual allocated totals or a new grant. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed option fields and output bytes, no runtime reads/work charging. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0031

[Lines 98–99](../../../../../src/io/cursor_observation.cpp#L98); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L98-L99:sha256:3799805db125e9b9e1a10c7d6741954a2bbf1abddb1d558e8d8d70966afe1278
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Suppress stale disabled/unavailable payloads rather than exporting a zero. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/cursor_observation.cpp lines 96-101; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/cursor_observation.cpp](../../../../../src/io/cursor_observation.cpp), [docs/code_specs/files/src/io/cursor_observation.cpp.md](cursor_observation.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0032

[Lines 100–103](../../../../../src/io/cursor_observation.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void metric(Writer& w,const MetricValue& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Suppress unusable metric payload while preserving availability. |
| inputs / outputs | Always writes availability; numeric value/saturated flag only when available, else both null. |
| invariants | Stale disabled/unavailable internal payload is not a plausible total. Available saturated value remains explicitly tagged; serializer does not verify caller consistency. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed fields, no measurement or allocation except output growth. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0033

[Lines 104–110](../../../../../src/io/cursor_observation.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void configuration(Writer& w,const std::optional<ObservationConfiguration>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode optional captured cursor-begin runtime configuration. |
| inputs / outputs | Absent is null; present writes provenance/owner/generation/saturation, resolved mode/completion/query factors and captured requested options. |
| invariants | Begin-bound context is not relabeled with current owner options. This formatter does not authenticate arbitrary public DTO owner/sequence/mode combinations. |
| ownership | Borrows immutable caller/artifact data synchronously; only private result/output ownership changes. Does not accept source input, advance a producer/cursor or alter committed runtime state. |
| failure | Validation/access/encoding/resource/allocation errors propagate; local owned preparation/output is released. No partial public result or committed source progress is published. |
| cost | Fixed metadata plus requested-options formatting. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0034

[Lines 111–112](../../../../../src/io/cursor_observation.cpp#L111); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L112:sha256:b27835c8cf6067be8449b3eda2fad2c90249578dfd3bb7cc01408cadc3b3e4e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. Trailing source note states: Format supplied lifecycle metadata; this does not authenticate DTO consistency. It remains prose guidance, not a certified executable claim. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. Any trailing comment in this block is guidance only and adds no runtime invariant. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/cursor_observation.cpp](../../../../../src/io/cursor_observation.cpp), [docs/code_specs/files/src/io/cursor_observation.cpp.md](cursor_observation.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0035

[Lines 113–131](../../../../../src/io/cursor_observation.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_cursor_observation_json(const CursorObservation& value,std::size_t max_bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one complete descriptive cursor-lifetime JSON artifact. |
| inputs / outputs | Writes version1 owner/sequence, IDs only when telemetry enabled, construction/source/view/side/tentative/state/terminal reason, limits/config/options, registry measurements and mandatory phase work. |
| invariants | Input is a descriptive CursorObservation DTO, not a cursor/proof lease. Per-cursor lifecycle differs from update output spool; last mandatory phase is already included in results/termination/failed and is not additive. No validation of forged cross-field consistency. |
| ownership | Returns owning std::string independent of borrowed DTO; configuration retains its own owner outside encoder. |
| failure | Text/byte/allocation errors return no partial text. Unknown enum fallback is descriptive unknown and may fail external schema; no typed authority is created. |
| cost | O(registry entries + fixed mandatory/config fields + encoded bytes), ordinary private output growth; no clock/cursor/update work. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0036

[Lines 132–132](../../../../../src/io/cursor_observation.cpp#L132); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L132-L132:sha256:4c89264ecd67d1f5aaeb5e1aef2dc51da1c050c9beb91f6a44fb994950b575c8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Captured arrays are read directly; no fresh engine scan or total-memory proof. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/cursor_observation.cpp lines 130-134; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/cursor_observation.cpp](../../../../../src/io/cursor_observation.cpp), [docs/code_specs/files/src/io/cursor_observation.cpp.md](cursor_observation.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0037

[Lines 133–144](../../../../../src/io/cursor_observation.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Gauges> std::string gauges_json(const Gauges& value,std::size_t max_bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Format supplied committed-state gauge metadata without scanning engine rows. |
| inputs / outputs | Writes version1 owner/sequence, base and node arrays, typed S/P/E counts and optional full-result/memory/checkpoint/replay metrics. |
| invariants | Visible factor assignments are per-node E, not full join result count. Supplied DTO/native capture may be caller-editable; encoder does not establish freshness/source/durability/total-memory authority. Unknown metrics remain null via metric(). |
| ownership | Borrows ordinary or native captured arrays synchronously; output owns its complete bytes. |
| failure | Encoding/byte/allocation failure leaves input arrays unchanged; returns no partial text. |
| cost | O(base/node array lengths + output bytes), ordinary string allocation; underlying gauge capture/account arrays happened earlier and are not repeated. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0038

[Lines 145–145](../../../../../src/io/cursor_observation.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_committed_state_gauges_json(const CommittedStateGauges& value,std::size_t max_bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the same gauge JSON format for ordinary CommittedStateGauges DTO. |
| inputs / outputs | Forwards borrowed value and byte ceiling to gauges_json. |
| invariants | Output shape/availability rules are identical; native array ownership/accounting is not exported as a total-memory claim. |
| ownership | Returned string is ordinary caller-owned transport, independent of native/DTO backing. |
| failure | Delegated encoding/resource/allocation errors propagate without mutation. |
| cost | Fixed forwarding plus O(base/node/output bytes) formatting. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0039

[Lines 146–146](../../../../../src/io/cursor_observation.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_committed_state_gauges_json(const CapturedStateGauges& value,std::size_t max_bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the same gauge JSON format for native CapturedStateGauges. |
| inputs / outputs | Forwards borrowed value and byte ceiling to gauges_json. |
| invariants | Output shape/availability rules are identical; native array ownership/accounting is not exported as a total-memory claim. |
| ownership | Returned string is ordinary caller-owned transport, independent of native/DTO backing. |
| failure | Delegated encoding/resource/allocation errors propagate without mutation. |
| cost | Fixed forwarding plus O(base/node/output bytes) formatting. |
| Design | [include/crown/io/cursor_observation.hpp](../../../../../include/crown/io/cursor_observation.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/observability.md §Reports, ownership, and committed gauges](../../../../observability.md) |

## B0040

[Lines 147–147](../../../../../src/io/cursor_observation.cpp#L147); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L147-L147:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/cursor_observation.cpp](../../../../../src/io/cursor_observation.cpp), [docs/code_specs/files/src/io/cursor_observation.cpp.md](cursor_observation.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |
