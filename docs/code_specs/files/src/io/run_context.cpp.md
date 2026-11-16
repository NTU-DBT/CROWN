# `src/io/run_context.cpp` — block usage map

[Source](../../../../../src/io/run_context.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `87ee55ca851fd0af37185b82ec3fa90b660daa4156d3a0b37be5fe3065fe4054`. 172 lines partitioned into 36 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/io/run_context.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 8–26](../../../../../src/io/run_context.cpp#L8) | Callable definition: void utf8(std::string_view text) | calls size, Error; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 27–30](../../../../../src/io/run_context.cpp#L27) | declares types or opens a type body. | source comment (unverified): // This owns ordinary encoded bytes; the cap excludes capacity and transients. · [reviewed contract](#b0003) |
| [B0004 · 31–31](../../../../../src/io/run_context.cpp#L31) | Callable definition: explicit Writer(std::size_t bytes):limit(bytes) | calls limit · [reviewed contract](#b0004) |
| [B0005 · 32–35](../../../../../src/io/run_context.cpp#L32) | Callable definition: void raw(std::string_view value) | calls size, Error, append · [reviewed contract](#b0005) |
| [B0006 · 36–46](../../../../../src/io/run_context.cpp#L36) | Callable definition: void quote(std::string_view value,bool dot=false) | calls utf8, raw; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 47–51](../../../../../src/io/run_context.cpp#L47) | Callable definition: template&lt;class Integer&gt; void number(Integer value) | calls std::to_chars, Error, raw · [reviewed contract](#b0007) |
| [B0008 · 52–52](../../../../../src/io/run_context.cpp#L52) | Callable definition: void boolean(bool value) | calls raw · [reviewed contract](#b0008) |
| [B0009 · 53–53](../../../../../src/io/run_context.cpp#L53) | Callable definition: void null() | calls raw · [reviewed contract](#b0009) |
| [B0010 · 54–54](../../../../../src/io/run_context.cpp#L54) | Callable definition: template&lt;class T&gt; void optional(const std::optional&lt;T&gt;& value) | calls number, null · [reviewed contract](#b0010) |
| [B0011 · 55–57](../../../../../src/io/run_context.cpp#L55) | Callable definition: template&lt;class Range,class Fn&gt; void array(const Range& values,Fn fn) | calls raw, fn; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 58–65](../../../../../src/io/run_context.cpp#L58) | Type/record definition: struct Object |  · [reviewed contract](#b0012) |
| [B0013 · 66–66](../../../../../src/io/run_context.cpp#L66) | Callable definition: template&lt;class Fn&gt; void object(Fn fn) | calls raw, fn · [reviewed contract](#b0013) |
| [B0014 · 67–67](../../../../../src/io/run_context.cpp#L67) | Callable definition: template&lt;class Range&gt; void ids(const Range& values) | calls array, number · [reviewed contract](#b0014) |
| [B0015 · 68–70](../../../../../src/io/run_context.cpp#L68) | controls preprocessing. | returns #V · [reviewed contract](#b0015) |
| [B0016 · 71–73](../../../../../src/io/run_context.cpp#L71) | Callable definition: const char* name(InitializationRoute v) | calls ENUM_NAME; returns @ · [reviewed contract](#b0016) |
| [B0017 · 74–74](../../../../../src/io/run_context.cpp#L74) | Callable definition: const char* name(BuildMethod v) | calls ENUM_NAME; returns @ · [reviewed contract](#b0017) |
| [B0018 · 75–75](../../../../../src/io/run_context.cpp#L75) | Callable definition: const char* name(SessionInputKind v) | calls ENUM_NAME; returns @ · [reviewed contract](#b0018) |
| [B0019 · 76–76](../../../../../src/io/run_context.cpp#L76) | Callable definition: const char* name(InputFormat v) | calls ENUM_NAME; returns @ · [reviewed contract](#b0019) |
| [B0020 · 77–77](../../../../../src/io/run_context.cpp#L77) | Callable definition: const char* name(DeltaMode v) | calls ENUM_NAME; returns @ · [reviewed contract](#b0020) |
| [B0021 · 78–78](../../../../../src/io/run_context.cpp#L78) | Callable definition: const char* name(DeltaCompletion v) | calls ENUM_NAME; returns @ · [reviewed contract](#b0021) |
| [B0022 · 79–79](../../../../../src/io/run_context.cpp#L79) | Callable definition: const char* name(LiveMaintenance v) | calls ENUM_NAME; returns @ · [reviewed contract](#b0022) |
| [B0023 · 80–80](../../../../../src/io/run_context.cpp#L80) | Callable definition: const char* name(ResultView v) | calls ENUM_NAME; returns @ · [reviewed contract](#b0023) |
| [B0024 · 81–81](../../../../../src/io/run_context.cpp#L81) | Callable definition: const char* name(PropagationOrder v) | calls ENUM_NAME; returns @ · [reviewed contract](#b0024) |
| [B0025 · 82–82](../../../../../src/io/run_context.cpp#L82) | Callable definition: const char* name(ObservationMode v) | calls ENUM_NAME; returns @ · [reviewed contract](#b0025) |
| [B0026 · 83–83](../../../../../src/io/run_context.cpp#L83) | Member/declaration region. |  · [reviewed contract](#b0026) |
| [B0027 · 84–84](../../../../../src/io/run_context.cpp#L84) | Callable definition: template&lt;class Text&gt; void optional_text(Writer& w,const std::optional&lt;Text&gt;& value) | calls quote, null · [reviewed contract](#b0027) |
| [B0028 · 85–89](../../../../../src/io/run_context.cpp#L85) | Callable definition: void initialization(Writer& w,const InitializationContext& c) | calls object, text, name, field · [reviewed contract](#b0028) |
| [B0029 · 90–97](../../../../../src/io/run_context.cpp#L90) | Callable definition: void declared(Writer& w,const std::shared_ptr&lt;const DeclaredBenchmarkContext&gt;& c) | calls null, object, text, labels · [reviewed contract](#b0029) |
| [B0030 · 98–109](../../../../../src/io/run_context.cpp#L98) | Callable definition: void delta_options(Writer& w,const DeltaOptions& d) | calls object, text, name, field · [reviewed contract](#b0030) |
| [B0031 · 110–110](../../../../../src/io/run_context.cpp#L110) | Explanatory comments or spacing. | source comment (unverified): // Actual sessions record admission metadata; this formatter does not authenticate DTOs. · [reviewed contract](#b0031) |
| [B0032 · 111–139](../../../../../src/io/run_context.cpp#L111) | Callable definition: void session(Writer& w,const std::shared_ptr&lt;const SessionRunContext&gt;& c) | calls null, object, text, name; growth insert; source comment (unverified): // Actual sessions record admission metadata; this formatter does not authenticate DTOs. · [reviewed contract](#b0032) |
| [B0033 · 140–156](../../../../../src/io/run_context.cpp#L140) | Callable definition: void attempt(Writer& w,const std::optional&lt;ObservationSummary&gt;& s) | calls null, object, number, text · [reviewed contract](#b0033) |
| [B0034 · 157–158](../../../../../src/io/run_context.cpp#L157) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0034) |
| [B0035 · 159–171](../../../../../src/io/run_context.cpp#L159) | Callable definition: std::string write_run_context_json(const ObservationSnapshot& s,std::size_t max_bytes) | calls w, object, text, number; returns std::move(w.out); source comment (unverified): // Explicit allocating export: visit supplied metadata, not live rows or callbacks. · [reviewed contract](#b0035) |
| [B0036 · 172–172](../../../../../src/io/run_context.cpp#L172) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0036) |

## B0001

[Lines 1–7](../../../../../src/io/run_context.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:00e2fcb3b47ab6cec7de855092f6a163bc5abb413bd487cd5c07158e5baeaecd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/io/run_context.hpp, crown/api/error.hpp, charconv, utility) and opens crown::io scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/run_context.cpp](../../../../../src/io/run_context.cpp), [docs/code_specs/files/src/io/run_context.cpp.md](run_context.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0002

[Lines 8–26](../../../../../src/io/run_context.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void utf8(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate run-context text for strict JSON UTF8 export. |
| inputs / outputs | Accepts ASCII including NUL and valid shortest-form Unicode scalars; rejects bad leaders/continuations, truncation, overlong encodings, surrogates and values beyond Unicode maximum. |
| invariants | Native input bytes are not normalized or rewritten. This is an export constraint on supplied metadata, not native row/source admission. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Throws owning Error diagnostic on invalid UTF8; allocation failure can supersede diagnostic construction. |
| cost | O(input text bytes) validation before escaping/output-byte checks in quote; even a later capped-output failure may have scanned a whole string. No successful validation allocation. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0003

[Lines 27–30](../../../../../src/io/run_context.cpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Writer {
  std::string out;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a private byte-capped run-context output string. |
| inputs / outputs | Ordinary std::string accumulates encoded bytes under size_t limit; nested helpers borrow the same Writer. |
| invariants | The encoded-byte cap is not a query-account, string-capacity, transient-memory or input-validation-work cap. No DOM or stream is retained. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | Output allocation/growth/copies scale with encoded bytes; capacity and old/new buffers can exceed logical output length. No successful native-path instrumentation is added. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0004

[Lines 31–31](../../../../../src/io/run_context.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Writer(std::size_t bytes):limit(bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start a private output writer with its final encoded-byte ceiling. |
| inputs / outputs | Records requested limit and starts empty ordinary string; no eager reserve or input validation. |
| invariants | A zero limit is valid construction but cannot fit the public JSON object. Limit does not count allocator overhead or other retained metadata. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | No custom failure at construction; ordinary library construction behavior applies. |
| cost | Constant initialization; subsequent append may allocate/grow ordinary string. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0005

[Lines 32–35](../../../../../src/io/run_context.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void raw(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append admitted bytes without overflowing the remaining output cap. |
| inputs / outputs | Checks current length and value length by subtraction before std::string::append. |
| invariants | Input is already encoded syntax or validated text fragment; raw itself does not UTF8-check or escape. Failure cannot exceed the logical encoded-byte cap. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(resource_limit) before append when cap exceeded; append allocation/length failures propagate. |
| cost | O(fragment bytes) copy plus possible ordinary string growth/reallocation copying existing prefix; cap does not bound capacity/peak. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0006

[Lines 36–46](../../../../../src/io/run_context.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void quote(std::string_view value,bool dot=false)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Quote supplied text with strict UTF8 and explicit control escaping. |
| inputs / outputs | Validates full input then emits double quotes, escapes quote/backslash and U+0000..001F as Unicode escapes; optional dot flag adds an extra escape backslash for controls. |
| invariants | Public run-context callers use default dot=false; no runtime input is changed. Native-invalid text remains retained but export rejects. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | O(text bytes) UTF8 pass then O(escaped bytes) append; fixed hex/control scratch, ordinary growing output string. Full validation precedes first quoted-byte append. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0007

[Lines 47–51](../../../../../src/io/run_context.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Integer> void number(Integer value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render an integral context value into bounded stack digits. |
| inputs / outputs | std::to_chars writes to 32-byte stack buffer, then raw appends exact produced bytes. |
| invariants | Actual callers use integral limits/counters/IDs within supported 64-bit widths. No locale, floating conversion or owning intermediate number string. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(explain_encoding) on to_chars error; raw/allocation failures propagate. |
| cost | O(number digits) formatting/copy, fixed stack; raw may allocate or hit final byte cap. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0008

[Lines 52–52](../../../../../src/io/run_context.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boolean(bool value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit one Boolean literal. |
| inputs / outputs | Writes true/false through the shared capped raw path. |
| invariants | No semantic validation of the caller DTO flag or evidence authority. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | Fixed literal copy with possible output-string growth. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0009

[Lines 53–53](../../../../../src/io/run_context.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void null()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit explicit absence as JSON null. |
| inputs / outputs | Writes null through raw. |
| invariants | Missing metadata remains absent, without default identity, zero measurement or inferred callback. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | Four output bytes, possible shared output growth. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0010

[Lines 54–54](../../../../../src/io/run_context.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void optional(const std::optional<T>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode optional integral limits with absence preserved. |
| inputs / outputs | Present optional uses number; absent uses null. |
| invariants | Zero is an explicit numeric limit rather than unbounded/unknown. The formatter does not grant or alter that limit. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | Fixed presence branch plus digit output, possible shared string growth. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0011

[Lines 55–57](../../../../../src/io/run_context.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range,class Fn> void array(const Range& values,Fn fn)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a supplied metadata range in its existing order. |
| inputs / outputs | Writes brackets/comma delimiters and calls fn on each const element. |
| invariants | No implicit sorting, validation of cross-field state, producer access or separate element quota; callback owns element spelling/validation. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Callback, raw and allocation failures unwind the private Writer; no partial string is returned. |
| cost | O(element count plus callback formatting/bytes); output string allocations remain ordinary and byte-capped. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0012

[Lines 58–65](../../../../../src/io/run_context.cpp#L58); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Object
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Maintain object field punctuation and typed convenience writes. |
| inputs / outputs | Object borrows Writer, tracks first field, quotes each key then invokes its field callback; text/number/boolean/null delegate to Writer. |
| invariants | Call sites supply fixed distinct keys. Object does not authenticate DTO provenance or rollback individual fields; only the complete private export is published. |
| ownership | Object is stack bookkeeping borrowing its enclosing Writer; field callbacks run synchronously and retain no references. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | Fixed per-field punctuation/key work plus value callback; all bytes grow the shared ordinary output string. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0013

[Lines 66–66](../../../../../src/io/run_context.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Fn> void object(Fn fn)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write a complete object around synchronous field generation. |
| inputs / outputs | Emits opening brace, stack Object state, supplied callback and closing brace. |
| invariants | No independent DOM, output allocation domain, retry or transaction layer; private string can be partial internally on failure. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | Fixed delimiters plus field callback cost; shared output growth only. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0014

[Lines 67–67](../../../../../src/io/run_context.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range> void ids(const Range& values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode typed-ID ranges as numeric arrays. |
| inputs / outputs | Visits each supplied ID and emits its value member through number. |
| invariants | Does not validate IDs against tables/windows or materialize names; order is supplied context order. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | O(ID count plus decimal digit bytes); no ID-vector copy, possible output growth. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0015

[Lines 68–70](../../../../../src/io/run_context.cpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#define ENUM_NAME(T,V) case T::V:return #V
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep local enum spellings identical to their declared enumerator names. |
| inputs / outputs | Macro expands individual switch cases returning static string literals; undefined after name overloads. |
| invariants | Preprocessing convenience only, no dynamic registry, reverse parser or enum validation. Unknown enum values use each overload fallback. |
| ownership | Returned literals have static lifetime; macro has no retained object. |
| failure | No exception or runtime operation at macro definition. |
| cost | Compile-time expansion and constant switch cases, no runtime allocation/state. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0016

[Lines 71–73](../../../../../src/io/run_context.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(InitializationRoute v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell the supplied initialization route enum for diagnostic JSON. |
| inputs / outputs | Returns a static literal for empty_constructor, initialized_database, rebuilt_snapshot; any other representation returns unknown. |
| invariants | Diagnostic spelling only; fallback does not reject a forged/out-of-range DTO or establish that a producer applied the option. |
| ownership | Returned string literal has static lifetime; no borrowed metadata storage. |
| failure | No throwing case; callers quote/copy the literal into their output string. |
| cost | Fixed enum switch and literal pointer return, no scan, text allocation or producer lookup. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0017

[Lines 74–74](../../../../../src/io/run_context.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(BuildMethod v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell the supplied initial build method enum for diagnostic JSON. |
| inputs / outputs | Returns a static literal for direct, insertion_replay; any other representation returns unknown. |
| invariants | Diagnostic spelling only; fallback does not reject a forged/out-of-range DTO or establish that a producer applied the option. |
| ownership | Returned string literal has static lifetime; no borrowed metadata storage. |
| failure | No throwing case; callers quote/copy the literal into their output string. |
| cost | Fixed enum switch and literal pointer return, no scan, text allocation or producer lookup. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0018

[Lines 75–75](../../../../../src/io/run_context.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(SessionInputKind v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell the supplied session input kind enum for diagnostic JSON. |
| inputs / outputs | Returns a static literal for owned_stream, typed_physical, typed_window; any other representation returns unknown. |
| invariants | Diagnostic spelling only; fallback does not reject a forged/out-of-range DTO or establish that a producer applied the option. |
| ownership | Returned string literal has static lifetime; no borrowed metadata storage. |
| failure | No throwing case; callers quote/copy the literal into their output string. |
| cost | Fixed enum switch and literal pointer return, no scan, text allocation or producer lookup. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0019

[Lines 76–76](../../../../../src/io/run_context.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(InputFormat v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell the supplied input wire format enum for diagnostic JSON. |
| inputs / outputs | Returns a static literal for jsonl, binary, csv, legacy_signed, legacy_relations, legacy_insert_only, legacy_flags, legacy_timestamp_flags; any other representation returns unknown. |
| invariants | Diagnostic spelling only; fallback does not reject a forged/out-of-range DTO or establish that a producer applied the option. |
| ownership | Returned string literal has static lifetime; no borrowed metadata storage. |
| failure | No throwing case; callers quote/copy the literal into their output string. |
| cost | Fixed enum switch and literal pointer return, no scan, text allocation or producer lookup. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0020

[Lines 77–77](../../../../../src/io/run_context.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(DeltaMode v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell the supplied delta mode enum for diagnostic JSON. |
| inputs / outputs | Returns a static literal for maintenance, delta; any other representation returns unknown. |
| invariants | Diagnostic spelling only; fallback does not reject a forged/out-of-range DTO or establish that a producer applied the option. |
| ownership | Returned string literal has static lifetime; no borrowed metadata storage. |
| failure | No throwing case; callers quote/copy the literal into their output string. |
| cost | Fixed enum switch and literal pointer return, no scan, text allocation or producer lookup. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0021

[Lines 78–78](../../../../../src/io/run_context.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(DeltaCompletion v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell the supplied delta completion enum for diagnostic JSON. |
| inputs / outputs | Returns a static literal for automatic, ordered_replay, anchored, root_first; any other representation returns unknown. |
| invariants | Diagnostic spelling only; fallback does not reject a forged/out-of-range DTO or establish that a producer applied the option. |
| ownership | Returned string literal has static lifetime; no borrowed metadata storage. |
| failure | No throwing case; callers quote/copy the literal into their output string. |
| cost | Fixed enum switch and literal pointer return, no scan, text allocation or producer lookup. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0022

[Lines 79–79](../../../../../src/io/run_context.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(LiveMaintenance v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell the supplied live-maintenance mode enum for diagnostic JSON. |
| inputs / outputs | Returns a static literal for on_output, incremental, eager; any other representation returns unknown. |
| invariants | Diagnostic spelling only; fallback does not reject a forged/out-of-range DTO or establish that a producer applied the option. |
| ownership | Returned string literal has static lifetime; no borrowed metadata storage. |
| failure | No throwing case; callers quote/copy the literal into their output string. |
| cost | Fixed enum switch and literal pointer return, no scan, text allocation or producer lookup. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0023

[Lines 80–80](../../../../../src/io/run_context.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResultView v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell the supplied result view enum for diagnostic JSON. |
| inputs / outputs | Returns a static literal for core, sql; any other representation returns unknown. |
| invariants | Diagnostic spelling only; fallback does not reject a forged/out-of-range DTO or establish that a producer applied the option. |
| ownership | Returned string literal has static lifetime; no borrowed metadata storage. |
| failure | No throwing case; callers quote/copy the literal into their output string. |
| cost | Fixed enum switch and literal pointer return, no scan, text allocation or producer lookup. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0024

[Lines 81–81](../../../../../src/io/run_context.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(PropagationOrder v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell the supplied support propagation order enum for diagnostic JSON. |
| inputs / outputs | Returns a static literal for fifo, lifo; any other representation returns unknown. |
| invariants | Diagnostic spelling only; fallback does not reject a forged/out-of-range DTO or establish that a producer applied the option. |
| ownership | Returned string literal has static lifetime; no borrowed metadata storage. |
| failure | No throwing case; callers quote/copy the literal into their output string. |
| cost | Fixed enum switch and literal pointer return, no scan, text allocation or producer lookup. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0025

[Lines 82–82](../../../../../src/io/run_context.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ObservationMode v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell the supplied observation mode enum for diagnostic JSON. |
| inputs / outputs | Returns a static literal for off, counters, timed, trace; any other representation returns unknown. |
| invariants | Diagnostic spelling only; fallback does not reject a forged/out-of-range DTO or establish that a producer applied the option. |
| ownership | Returned string literal has static lifetime; no borrowed metadata storage. |
| failure | No throwing case; callers quote/copy the literal into their output string. |
| cost | Fixed enum switch and literal pointer return, no scan, text allocation or producer lookup. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0026

[Lines 83–83](../../../../../src/io/run_context.cpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L83:sha256:40baf18470a5ae0374b9a4c01e0b66457b0c769d48cbe4b8a3a135f5163f8913
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ends the local preprocessor definition of ENUM_NAME; subsequent translation-unit code cannot use that macro expansion. |
| inputs / outputs | No runtime values are exchanged; a preprocessor macro is removed for later source text in this translation unit. |
| invariants | The macro expansion is available only before this directive; later code must use ordinary declarations or a fresh definition. |
| ownership | No runtime state. |
| failure | No runtime error. Preprocessing/compilation can fail if later tokens depended on the removed macro. |
| cost | Preprocessing only. |
| Design | [src/io/run_context.cpp](../../../../../src/io/run_context.cpp), [docs/code_specs/files/src/io/run_context.cpp.md](run_context.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0027

[Lines 84–84](../../../../../src/io/run_context.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Text> void optional_text(Writer& w,const std::optional<Text>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an optional declared label or stored source token. |
| inputs / outputs | Present optional string-like value goes through UTF8 quote; absent emits null. |
| invariants | No inferred identity, callback target inspection or normalization of native bytes. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | O(text/escaped bytes) validation and output copies, no separate owning label copy before quote. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0028

[Lines 85–89](../../../../../src/io/run_context.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void initialization(Writer& w,const InitializationContext& c)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe recorded initialization metadata without replaying construction. |
| inputs / outputs | Emits recorded_successful_construction provenance, route and optional applied build method/work limit. |
| invariants | Empty-constructor route normally has no applied BuildOptions, but this formatter does not validate that relationship in a caller-supplied struct. No build timing or success proof is computed here. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | Fixed fields/digits except output growth, no database scan or build invocation. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/runtime_initialization.md §Distinct construction methods](../../../../runtime_initialization.md) |

## B0029

[Lines 90–97](../../../../../src/io/run_context.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void declared(Writer& w,const std::shared_ptr<const DeclaredBenchmarkContext>& c)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label optional caller benchmark declarations as unmeasured and unauthoritative. |
| inputs / outputs | Null pointer emits null; otherwise emits caller_declared_unmeasured, authority none and run/input-adapter/output-codec/sink optional labels. |
| invariants | Immutable DeclaredBenchmarkContext retains labels but does not inspect callbacks, verify benchmark protocol, cost, completeness, durability or recovery. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | O(total declared label/escaped bytes); borrows shared context without copying label containers, ordinary output allocations. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp) |

## B0030

[Lines 98–109](../../../../../src/io/run_context.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void delta_options(Writer& w,const DeltaOptions& d)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export requested delta/support/observation options without applying them. |
| inputs / outputs | Formats requested mode/completion, maintenance/view, optional work ceilings, spool/physical/support/derivation options and observation settings; memory limit emitted only when it differs from SupportOptions default. |
| invariants | These are supplied requested options, separate from resolved mode/completion. Null limits, explicit zero and default-omitted memory remain distinct; no counters or actual allocation totals are inferred. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | Fixed field/enum/integer formatting and ordinary output growth; no plan/table/trace scan. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0031

[Lines 110–110](../../../../../src/io/run_context.cpp#L110); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L110-L110:sha256:4fd3db7bc6fd25a10d3e722a9c11fe5371b3cbb7e104c61c69ecf7590b710fc3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Actual sessions record admission metadata; this formatter does not authenticate DTOs. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/run_context.cpp lines 108-112; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/run_context.cpp](../../../../../src/io/run_context.cpp), [docs/code_specs/files/src/io/run_context.cpp.md](run_context.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0032

[Lines 111–139](../../../../../src/io/run_context.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void session(Writer& w,const std::shared_ptr<const SessionRunContext>& c)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export one retained session admission context and input configuration. |
| inputs / outputs | Optional shared context yields input kind/wire applicability, exact stored input format/table/delimiter/header/tokens/null/source/offset/limits, queue/window/snapshot settings, initialization and requested/resolved delta configuration. Opt-in update_patterns exports the complete source-bound requested rule set; absent declarations omit the field. |
| invariants | Actual QuerySession records immutable admitted context; a caller-supplied DTO is not authenticated by this formatter. Typed wire format is not applicable. FIFO names distinguish all four policies; an invalid FIFO DTO emits unknown, while invalid csv_operation retains its erase fallback. No admission or historical pattern proof occurs here. Immutable requested rules are not live prefix evidence. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | O(relation-token count plus managed-table IDs plus all label/source/escaped bytes), fixed remaining fields. Borrows account-backed stored options; copies text only into ordinary encoded string. No source records, table rows or trace enumeration. Declared export additionally visits R rules; only explicit serialization allocates output bytes. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0033

[Lines 140–156](../../../../../src/io/run_context.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void attempt(Writer& w,const std::optional<ObservationSummary>& s)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one captured attempt context and observed output lifecycle flags. |
| inputs / outputs | Optional ObservationSummary emits attempt/sequence, captured initialization/declarations/configuration owner+generation/saturation and optional OutputDisposition flags with explicit observed-attempt provenance. |
| invariants | Does not relabel attempt configuration with current settings, infer missing identities, invoke serializer/sink, measure latency or prove durable callback effects. Supplied summary remains a DTO; no cross-field authenticity check. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | Fixed fields plus optional label/initialization text formatting; no metrics array, tuple or trace scan. Ordinary output growth. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp) |

## B0034

[Lines 157–158](../../../../../src/io/run_context.cpp#L157); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L157-L158:sha256:4482cecc598e4c121df76d79d191b84e3a728809d2c4473c3556de17161379e1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. Trailing source note states: Explicit allocating export: visit supplied metadata, not live rows or callbacks. It remains prose guidance, not a certified executable claim. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. Any trailing comment in this block is guidance only and adds no runtime invariant. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/run_context.cpp](../../../../../src/io/run_context.cpp), [docs/code_specs/files/src/io/run_context.cpp.md](run_context.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |

## B0035

[Lines 159–171](../../../../../src/io/run_context.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_run_context_json(const ObservationSnapshot& s,std::size_t max_bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the explicit diagnostic run-context JSON companion. |
| inputs / outputs | ObservationSnapshot and max encoded bytes produce owning JSON text with fixed version-1 scope/disclaimers and current initialization/declarations/session/current+last attempt metadata. |
| invariants | No producer refresh, parsing, callback inspection, measured benchmark or durability/recovery claim. Existing accounted_byte_scope string is a coarse no-total-memory disclaimer, not the precise definition of every modern native account-funded component limit. |
| ownership | Borrows supplied snapshot/context/text synchronously; Writer owns an ordinary std::string outside query MemoryAccount. Only the returned encoded bytes survive; no source/runtime mutation or file I/O. |
| failure | Error(text_encoding/resource_limit/explain_encoding) and ordinary string/allocation failures propagate; private output is discarded. No producer action or partial external output occurs. |
| cost | O(visited metadata ranges plus UTF8/escaping/output bytes); one ordinary growing string, no DOM and no input work quota. Byte cap applies to final logical bytes, not capacity/transients or earlier full UTF8 visits. |
| Design | [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/memory_accounts.md](../../../../memory_accounts.md), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json) |

## B0036

[Lines 172–172](../../../../../src/io/run_context.cpp#L172); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L172-L172:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/run_context.cpp](../../../../../src/io/run_context.cpp), [docs/code_specs/files/src/io/run_context.cpp.md](run_context.cpp.md), [docs/observability.md](../../../../observability.md), [docs/statistics.md](../../../../statistics.md) |
