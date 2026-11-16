# `src/io/query_explain.cpp` — block usage map

[Source](../../../../../src/io/query_explain.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `f01abfb2b394fc982b8bfb4dbaf68a58ffe9443760b6bd6e3d56e69c6da1d595`. 185 lines partitioned into 51 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/io/query_explain.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 9–27](../../../../../src/io/query_explain.cpp#L9) | Callable definition: void utf8(std::string_view text) | calls size, Error; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 28–32](../../../../../src/io/query_explain.cpp#L28) | declares types or opens a type body. | source comment (unverified): // Private text buffer: encoded length is capped, allocator capacity is separate. · [reviewed contract](#b0003) |
| [B0004 · 33–33](../../../../../src/io/query_explain.cpp#L33) | Callable definition: explicit Writer(std::size_t bytes):limit(bytes) | calls limit · [reviewed contract](#b0004) |
| [B0005 · 34–37](../../../../../src/io/query_explain.cpp#L34) | Callable definition: void raw(std::string_view value) | calls size, Error, append · [reviewed contract](#b0005) |
| [B0006 · 38–49](../../../../../src/io/query_explain.cpp#L38) | Callable definition: void quote(std::string_view value,bool dot=false) | calls size, Error, utf8, raw; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 50–54](../../../../../src/io/query_explain.cpp#L50) | Callable definition: template&lt;class Integer&gt; void number(Integer value) | calls std::to_chars, Error, raw · [reviewed contract](#b0007) |
| [B0008 · 55–55](../../../../../src/io/query_explain.cpp#L55) | Callable definition: void boolean(bool value) | calls raw · [reviewed contract](#b0008) |
| [B0009 · 56–56](../../../../../src/io/query_explain.cpp#L56) | Callable definition: void null() | calls raw · [reviewed contract](#b0009) |
| [B0010 · 57–57](../../../../../src/io/query_explain.cpp#L57) | Callable definition: template&lt;class T&gt; void optional(const std::optional&lt;T&gt;& value) | calls number, null · [reviewed contract](#b0010) |
| [B0011 · 58–60](../../../../../src/io/query_explain.cpp#L58) | Callable definition: template&lt;class Range,class Fn&gt; void array(const Range& values,Fn fn) | calls raw, fn; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 61–68](../../../../../src/io/query_explain.cpp#L61) | Type/record definition: struct Object |  · [reviewed contract](#b0012) |
| [B0013 · 69–69](../../../../../src/io/query_explain.cpp#L69) | Callable definition: template&lt;class Fn&gt; void object(Fn fn) | calls raw, fn · [reviewed contract](#b0013) |
| [B0014 · 70–70](../../../../../src/io/query_explain.cpp#L70) | Callable definition: template&lt;class Range&gt; void ids(const Range& values) | calls array, number · [reviewed contract](#b0014) |
| [B0015 · 71–71](../../../../../src/io/query_explain.cpp#L71) | Closes surrounding scope/type. |  · [reviewed contract](#b0015) |
| [B0016 · 72–72](../../../../../src/io/query_explain.cpp#L72) | Callable definition: const char* name(QueryExplainSource v) | calls Error; returns @; @ · [reviewed contract](#b0016) |
| [B0017 · 73–73](../../../../../src/io/query_explain.cpp#L73) | Callable definition: const char* name(QueryHeightStatus v) | calls Error; returns @; @ · [reviewed contract](#b0017) |
| [B0018 · 74–74](../../../../../src/io/query_explain.cpp#L74) | Callable definition: const char* name(SearchPolicy v) | calls Error; returns @; @ · [reviewed contract](#b0018) |
| [B0019 · 75–75](../../../../../src/io/query_explain.cpp#L75) | Callable definition: const char* name(NodeKind v) | calls Error; returns @; @ · [reviewed contract](#b0019) |
| [B0020 · 76–76](../../../../../src/io/query_explain.cpp#L76) | Callable definition: const char* name(BoundEvidence v) | calls Error; returns @; @ · [reviewed contract](#b0020) |
| [B0021 · 77–77](../../../../../src/io/query_explain.cpp#L77) | Callable definition: const char* name(ResultKind v) | calls Error; returns @; @ · [reviewed contract](#b0021) |
| [B0022 · 78–78](../../../../../src/io/query_explain.cpp#L78) | Callable definition: const char* name(SearchPhase v) | calls Error; returns @; @ · [reviewed contract](#b0022) |
| [B0023 · 79–79](../../../../../src/io/query_explain.cpp#L79) | Callable definition: const char* name(ReplayPhase v) | calls Error; returns @; @ · [reviewed contract](#b0023) |
| [B0024 · 80–80](../../../../../src/io/query_explain.cpp#L80) | Callable definition: const char* name(StopReason v) | calls Error; returns @; @ · [reviewed contract](#b0024) |
| [B0025 · 81–92](../../../../../src/io/query_explain.cpp#L81) | Callable definition: void scalar(Writer& w,const Value& value) | calls object, text, type_name, type_of · [reviewed contract](#b0025) |
| [B0026 · 93–99](../../../../../src/io/query_explain.cpp#L93) | Callable definition: void term(Writer& w,const Term& value) | calls object, text, number, field · [reviewed contract](#b0026) |
| [B0027 · 100–100](../../../../../src/io/query_explain.cpp#L100) | Callable definition: void statistics(Writer& w,const SearchStatistics& s) | calls object, number · [reviewed contract](#b0027) |
| [B0028 · 101–101](../../../../../src/io/query_explain.cpp#L101) | Explanatory comments or spacing. |  |
| [B0029 · 102–102](../../../../../src/io/query_explain.cpp#L102) | Callable definition: void decimal(Writer& w,const std::optional&lt;DecimalSpec&gt;& d) | calls null, object, number · [reviewed contract](#b0029) |
| [B0030 · 103–112](../../../../../src/io/query_explain.cpp#L103) | Callable definition: void catalog(Writer& w,const Catalog& c) | calls object, number, field, array · [reviewed contract](#b0030) |
| [B0031 · 113–117](../../../../../src/io/query_explain.cpp#L113) | Callable definition: void query(Writer& w,const Query& q) | calls object, boolean, field, array · [reviewed contract](#b0031) |
| [B0032 · 118–118](../../../../../src/io/query_explain.cpp#L118) | Explanatory comments or spacing. | source comment (unverified): // Diagnostic text preserves the original binding; it cannot create that authority. · [reviewed contract](#b0032) |
| [B0033 · 119–119](../../../../../src/io/query_explain.cpp#L119) | Callable definition: void binding(Writer& w,const SearchBinding& b) | calls object, field, catalog, query; source comment (unverified): // Diagnostic text preserves the original binding; it cannot create that authority. · [reviewed contract](#b0033) |
| [B0034 · 120–124](../../../../../src/io/query_explain.cpp#L120) | Callable definition: void tree(Writer& w,const FreeConnexTree& t) | calls object, field, number, null · [reviewed contract](#b0034) |
| [B0035 · 125–127](../../../../../src/io/query_explain.cpp#L125) | Callable definition: void counters(Writer& w,const WorkCounters& c) | calls object, number, boolean · [reviewed contract](#b0035) |
| [B0036 · 128–128](../../../../../src/io/query_explain.cpp#L128) | Callable definition: void phase_limit(Writer& w,const PhaseCeiling& p) | calls object, field, optional, number · [reviewed contract](#b0036) |
| [B0037 · 129–136](../../../../../src/io/query_explain.cpp#L129) | Callable definition: void search(Writer& w,const QueryExplanation& e) | calls search_progress, null, object, text · [reviewed contract](#b0037) |
| [B0038 · 137–141](../../../../../src/io/query_explain.cpp#L137) | Callable definition: void replay(Writer& w,const QueryExplanation& e) | calls replay_progress, null, object, text · [reviewed contract](#b0038) |
| [B0039 · 142–143](../../../../../src/io/query_explain.cpp#L142) | Explanatory comments or spacing. | source comment (unverified): // Observed upper, published checked witness and independently proved minimum · [reviewed contract](#b0039) |
| [B0040 · 144–149](../../../../../src/io/query_explain.cpp#L144) | Callable definition: void height(Writer& w,const QueryExplanation& e) | calls object, text, name, height_status; source comment (unverified): // Observed upper, published checked witness and independently proved minimum · [reviewed contract](#b0040) |
| [B0041 · 150–150](../../../../../src/io/query_explain.cpp#L150) | Callable definition: void witness(Writer& w,const QueryExplanation& e) | calls null, object, text, number · [reviewed contract](#b0041) |
| [B0042 · 151–154](../../../../../src/io/query_explain.cpp#L151) | Callable definition: void certificate(Writer& w,const QueryExplanation& e) | calls null, object, text, field · [reviewed contract](#b0042) |
| [B0043 · 155–165](../../../../../src/io/query_explain.cpp#L155) | Callable definition: void report(Writer& w,const QueryExplanation& e) | calls object, text, number, name · [reviewed contract](#b0043) |
| [B0044 · 166–166](../../../../../src/io/query_explain.cpp#L166) | Explanatory comments or spacing. | source comment (unverified): // A bound alone is insufficient: both tree transports require this typed owner. · [reviewed contract](#b0044) |
| [B0045 · 167–167](../../../../../src/io/query_explain.cpp#L167) | Callable definition: const ValidatedIncumbent& need_witness(const QueryExplanation& e) | calls witness, Error; returns *e.witness(); source comment (unverified): // A bound alone is insufficient: both tree transports require this typed owner. · [reviewed contract](#b0045) |
| [B0046 · 168–168](../../../../../src/io/query_explain.cpp#L168) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0046) |
| [B0047 · 169–169](../../../../../src/io/query_explain.cpp#L169) | Callable definition: std::string write_query_explain_json(const QueryExplanation& e,QueryExplainTextLimits limits) | calls w, report, std::move; returns std::move(w.out) · [reviewed contract](#b0047) |
| [B0048 · 170–170](../../../../../src/io/query_explain.cpp#L170) | Callable definition: std::string write_query_explain_tree_json(const QueryExplanation& e,QueryExplainTextLimits limits) | calls need_witness, w, object, text; returns std::move(w.out) · [reviewed contract](#b0048) |
| [B0049 · 171–180](../../../../../src/io/query_explain.cpp#L171) | Callable definition: std::string write_query_explain_text(const QueryExplanation& e,QueryExplainTextLimits limits) | calls w, raw, name, source; returns std::move(w.out) · [reviewed contract](#b0049) |
| [B0050 · 181–184](../../../../../src/io/query_explain.cpp#L181) | Callable definition: std::string write_query_explain_dot(const QueryExplanation& e,QueryExplainTextLimits limits) | calls need_witness, tree, w, raw; returns std::move(w.out); 2 loop sites · [reviewed contract](#b0050) |
| [B0051 · 185–185](../../../../../src/io/query_explain.cpp#L185) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0051) |

## B0001

[Lines 1–8](../../../../../src/io/query_explain.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using namespace planner;using namespace observability;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind query transport helpers to typed planner/report declarations. |
| inputs / outputs | Private namespace imports resolve SearchBinding, evidence/status/progress and query-tree types from public IO header. |
| invariants | Compile-time name lookup only; no admission, owner, runtime dispatch or mutable state. |
| ownership | No independent storage or ownership. |
| failure | Mismatched declarations fail compilation, not runtime recovery. |
| cost | No runtime cost or allocation. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0002

[Lines 9–27](../../../../../src/io/query_explain.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void utf8(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate strict UTF-8 for query report string transport. |
| inputs / outputs | Scans borrowed bytes; rejects malformed leaders/continuations, truncation, overlong encodings, surrogates and values above U+10FFFF. |
| invariants | ASCII controls may pass here because quote escapes them; native metadata bytes are neither mutated nor normalized. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | text_encoding at first malformed sequence; native binding/proof remains unchanged. |
| cost | O(input bytes), fixed local state and no successful heap allocation. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0003

[Lines 28–32](../../../../../src/io/query_explain.cpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Writer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a private streaming query/search UTF-8 transport buffer. |
| inputs / outputs | Writer holds ordinary output string and encoded-byte ceiling for JSON/text/tree/DOT. |
| invariants | Successful raw keeps out.size() &lt;= limit. Ceiling is final encoded length, not capture/proof storage, string spare capacity, total allocator use or CPU work. |
| ownership | Local Writer uniquely owns output until public function moves complete string to caller. |
| failure | Any encoding/byte/allocation error discards only local partial output; no catch or producer rollback needed. |
| cost | Amortized std::string growth/copy and emitted bytes, no DOM or producer work instrumentation. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0004

[Lines 33–33](../../../../../src/io/query_explain.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Writer(std::size_t bytes):limit(bytes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize an empty query writer with caller ceiling. |
| inputs / outputs | Stores size_t limit; output string starts empty. |
| invariants | Zero ceiling is admitted and rejects nonempty artifact later; no hidden reserve/account. |
| ownership | Constructs local output owner only. |
| failure | No explicit validation failure in construction. |
| cost | Fixed scalar/default-string initialization. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0005

[Lines 34–37](../../../../../src/io/query_explain.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void raw(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and append one already encoded output span. |
| inputs / outputs | Subtraction-based remaining-length check precedes out.append. |
| invariants | Overflow-safe size invariant out.size()&lt;=limit; cap counts bytes only. Earlier private writes are not public partial text. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | resource_limit before oversized append; std::bad_alloc/length errors from string propagate. |
| cost | O(span bytes), possible string capacity growth/relocation. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0006

[Lines 38–49](../../../../../src/io/query_explain.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void quote(std::string_view value,bool dot=false)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Quote strict UTF-8 for JSON or DOT label transport. |
| inputs / outputs | Prechecks raw length, validates UTF-8, escapes quotes/backslashes/control bytes; DOT control escape gets an extra slash. |
| invariants | raw checks actual expansion after the cheap initial length test. No Unicode normalization or replacement of unencodable native values. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | UTF-8 scan plus O(input/encoded bytes) escaping and output growth. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0007

[Lines 50–54](../../../../../src/io/query_explain.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Integer> void number(Integer value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Format one integral fact using locale-free exact decimal text. |
| inputs / outputs | to_chars writes into fixed 32-byte local buffer, checks result, then appends its digits. |
| invariants | Admitted numeric types fit fixed buffer; no floating/stream/locale conversion. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | explain_encoding on unexpected conversion error; byte/allocation errors propagate. |
| cost | Bounded integer formatting plus output append; no formatting heap buffer. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0008

[Lines 55–55](../../../../../src/io/query_explain.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boolean(bool value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit an exact Boolean JSON token. |
| inputs / outputs | Appends true or false. |
| invariants | Boolean remains distinct from numeric 0/1. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Fixed token work plus output growth. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0009

[Lines 56–56](../../../../../src/io/query_explain.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void null()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit explicit absent/unknown JSON metadata. |
| inputs / outputs | Appends null. |
| invariants | Unknown report bound is not silently zero and does not introduce native SQL NULL. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Fixed token work plus output growth. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0010

[Lines 57–57](../../../../../src/io/query_explain.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void optional(const std::optional<T>& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit one optional integral bound/fact. |
| inputs / outputs | Present value becomes number, absence becomes null. |
| invariants | Present zero remains zero; no inferred proof bound on absence. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Fixed branch plus numeric/null output. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0011

[Lines 58–60](../../../../../src/io/query_explain.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range,class Fn> void array(const Range& values,Fn fn)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stream an ordered range as one JSON array. |
| inputs / outputs | Invokes synchronous element encoder once per item with explicit commas/brackets. |
| invariants | Preserves order/repeats; callback emits one valid value; no array copy, sorting or semantic admission. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | O(range count + callback/encoded bytes), only output growth is owned. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0012

[Lines 61–68](../../../../../src/io/query_explain.cpp#L61); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Object
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a stack borrowing JSON object field writer. |
| inputs / outputs | Tracks first field; quotes keys and delegates typed value callbacks. |
| invariants | Callers supply fixed unique keys; no key-dedup map or DOM. Object lifetime is inside its parent Writer callback. |
| ownership | Object holds only Writer& and Boolean; no separate buffer or report owner. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Fixed state; each field costs key bytes plus delegated value/output work. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0013

[Lines 69–69](../../../../../src/io/query_explain.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Fn> void object(Fn fn)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stream a callback-built JSON object. |
| inputs / outputs | Writes braces and passes a fresh Object to synchronous callback. |
| invariants | No public artifact until entire enclosing encoder returns; callback failures leave local partial buffer. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Fixed braces/state plus callback cost. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0014

[Lines 70–70](../../../../../src/io/query_explain.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range> void ids(const Range& values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode ordered native ID fields. |
| inputs / outputs | Maps each item.value to a numeric array element. |
| invariants | Does not renumber or validate IDs; typed binding/witness already supplies admitted identity. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | O(ID count + digit bytes), no temporary vector. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0015

[Lines 71–71](../../../../../src/io/query_explain.cpp#L71); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L71-L71:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [docs/code_specs/files/src/io/query_explain.cpp.md](query_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0016

[Lines 72–72](../../../../../src/io/query_explain.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(QueryExplainSource v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell QueryExplainSource without losing typed query-report states. |
| inputs / outputs | Declared enum alternatives map to static literals: exact_search, certificate_replay, checked_upper, verified_optimum, verified_infeasible, checked_certificate. |
| invariants | No fallback rewrites unknown/unfinished/failed into verified proof or a successful stop reason. |
| ownership | Returns static literal pointer; retains no report or runtime. |
| failure | Unknown enum throws query_explain_enum; does not modify capture. |
| cost | Finite switch, no successful allocation or producer access. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0017

[Lines 73–73](../../../../../src/io/query_explain.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(QueryHeightStatus v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell QueryHeightStatus without losing typed query-report states. |
| inputs / outputs | Declared enum alternatives map to static literals: unknown, owner_checked_upper_unpublished, checked_upper, verified_optimum, verified_infeasible. |
| invariants | No fallback rewrites unknown/unfinished/failed into verified proof or a successful stop reason. |
| ownership | Returns static literal pointer; retains no report or runtime. |
| failure | Unknown enum throws query_explain_enum; does not modify capture. |
| cost | Finite switch, no successful allocation or producer access. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0018

[Lines 74–74](../../../../../src/io/query_explain.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(SearchPolicy v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell SearchPolicy without losing typed query-report states. |
| inputs / outputs | Declared enum alternatives map to static literals: strict, best_found. |
| invariants | No fallback rewrites unknown/unfinished/failed into verified proof or a successful stop reason. |
| ownership | Returns static literal pointer; retains no report or runtime. |
| failure | Unknown enum throws query_explain_enum; does not modify capture. |
| cost | Finite switch, no successful allocation or producer access. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0019

[Lines 75–75](../../../../../src/io/query_explain.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(NodeKind v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell NodeKind without losing typed query-report states. |
| inputs / outputs | Declared enum alternatives map to static literals: native, generalized. |
| invariants | No fallback rewrites unknown/unfinished/failed into verified proof or a successful stop reason. |
| ownership | Returns static literal pointer; retains no report or runtime. |
| failure | Unknown enum throws query_explain_enum; does not modify capture. |
| cost | Finite switch, no successful allocation or producer access. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0020

[Lines 76–76](../../../../../src/io/query_explain.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(BoundEvidence v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell BoundEvidence without losing typed query-report states. |
| inputs / outputs | Declared enum alternatives map to static literals: universal, independently_checked. |
| invariants | No fallback rewrites unknown/unfinished/failed into verified proof or a successful stop reason. |
| ownership | Returns static literal pointer; retains no report or runtime. |
| failure | Unknown enum throws query_explain_enum; does not modify capture. |
| cost | Finite switch, no successful allocation or producer access. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0021

[Lines 77–77](../../../../../src/io/query_explain.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResultKind v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell ResultKind without losing typed query-report states. |
| inputs / outputs | Declared enum alternatives map to static literals: unfinished, verified_optimum, verified_infeasible, failed. |
| invariants | No fallback rewrites unknown/unfinished/failed into verified proof or a successful stop reason. |
| ownership | Returns static literal pointer; retains no report or runtime. |
| failure | Unknown enum throws query_explain_enum; does not modify capture. |
| cost | Finite switch, no successful allocation or producer access. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0022

[Lines 78–78](../../../../../src/io/query_explain.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(SearchPhase v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell SearchPhase without losing typed query-report states. |
| inputs / outputs | Declared enum alternatives map to static literals: admitted, preprocess, search, build_incumbent, validate_incumbent, export_proof, replay, complete, failed, cancelled, moved_from. |
| invariants | No fallback rewrites unknown/unfinished/failed into verified proof or a successful stop reason. |
| ownership | Returns static literal pointer; retains no report or runtime. |
| failure | Unknown enum throws query_explain_enum; does not modify capture. |
| cost | Finite switch, no successful allocation or producer access. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0023

[Lines 79–79](../../../../../src/io/query_explain.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ReplayPhase v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell ReplayPhase without losing typed query-report states. |
| inputs / outputs | Declared enum alternatives map to static literals: admitted, dispatch, validate_upper, build_scopes, classify_scope_orbits, index_claims, order_claims, prove_claim, match_root, complete, failed, cancelled, moved_from. |
| invariants | No fallback rewrites unknown/unfinished/failed into verified proof or a successful stop reason. |
| ownership | Returns static literal pointer; retains no report or runtime. |
| failure | Unknown enum throws query_explain_enum; does not modify capture. |
| cost | Finite switch, no successful allocation or producer access. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0024

[Lines 80–80](../../../../../src/io/query_explain.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(StopReason v)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell StopReason without losing typed query-report states. |
| inputs / outputs | Declared enum alternatives map to static literals: none, quantum_work, quantum_time, total_work, total_time, depth_limit, allocation_failure, counter_overflow, invalid_quantum, invalid_certificate, internal_failure, complete, cancelled, moved_from. |
| invariants | No fallback rewrites unknown/unfinished/failed into verified proof or a successful stop reason. |
| ownership | Returns static literal pointer; retains no report or runtime. |
| failure | Unknown enum throws query_explain_enum; does not modify capture. |
| cost | Finite switch, no successful allocation or producer access. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0025

[Lines 81–92](../../../../../src/io/query_explain.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar(Writer& w,const Value& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an exact typed native constant from the original query. |
| inputs / outputs | Writes type plus integer/Boolean/UTF-8 string or quoted canonical date/decimal spelling. |
| invariants | No float approximation/type coercion; arbitrary invalid UTF-8 rejects export only, not native binding ownership. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | O(scalar/output bytes); date/owning Decimal::to_string can allocate temporaries. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0026

[Lines 93–99](../../../../../src/io/query_explain.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void term(Writer& w,const Term& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one original core term without rewriting it. |
| inputs / outputs | Variable emits ID; owning constant delegates scalar; ignored column emits its kind. |
| invariants | Preserves variant distinction from the typed SearchBinding; no substitution, projection or inference. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Fixed variant branch plus scalar/text output cost. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0027

[Lines 100–100](../../../../../src/io/query_explain.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void statistics(Writer& w,const SearchStatistics& s)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode producer-recorded structural search counters. |
| inputs / outputs | Writes work/states/partitions/candidates/cache/certificate/hierarchy/component/symmetry/pruning fields. |
| invariants | These are recorded producer observations; work aliases producer attempted and certificate_work aliases replay attempted, not independent additive phases. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Fixed field count plus digits; does not rerun recognition or search. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0029

[Lines 102–102](../../../../../src/io/query_explain.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void decimal(Writer& w,const std::optional<DecimalSpec>& d)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an optional decimal schema typemod. |
| inputs / outputs | Absent is null; present writes precision and scale. |
| invariants | Retains exact admitted metadata, no numeric coercion or value formatting. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Fixed fields/digits. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0030

[Lines 103–112](../../../../../src/io/query_explain.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void catalog(Writer& w,const Catalog& c)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode complete original catalog metadata in query binding. |
| inputs / outputs | Writes ordered tables/columns/typemods/collation, UNIQUE/FK status/ordered IDs, statistics and key hints. |
| invariants | Catalog estimates are original input metadata, not captured runtime statistics or optimizer results. Typed binding admitted enums/layouts; serializer creates no validity authority. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | O(catalog descriptors/name/hint/ID bytes + encoded output), no DOM/deep catalog copy during formatting. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md) |

## B0031

[Lines 113–117](../../../../../src/io/query_explain.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void query(Writer& w,const Query& q)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode exact original CQ variables, atoms, head and contradiction flag. |
| inputs / outputs | Preserves ordered names/types/occurrence tables/terms and head aliases/variables. |
| invariants | A nonempty contradiction-marked original query retains structural query-family scope; do not replace it with P08 executable constant-false operator height zero. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | O(query/term/head metadata and scalar/output bytes), no recognizer or normalization. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0032

[Lines 118–118](../../../../../src/io/query_explain.cpp#L118); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L118:sha256:ac4325b526cf99f72d82f4d30ed7258a3965936eb964085c48608a436f9c369b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Diagnostic text preserves the original binding; it cannot create that authority. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/query_explain.cpp lines 116-120; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [docs/code_specs/files/src/io/query_explain.cpp.md](query_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0033

[Lines 119–119](../../../../../src/io/query_explain.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void binding(Writer& w,const SearchBinding& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode original typed SearchBinding catalog and query. |
| inputs / outputs | Writes two complete nested native metadata objects from binding getters. |
| invariants | Export is diagnostic, not a SearchBinding importer; JSON contents/digests cannot mint proof ownership. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | O(full catalog/query/scalar/output bytes), no copy of the typed binding graph. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0034

[Lines 120–124](../../../../../src/io/query_explain.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void tree(Writer& w,const FreeConnexTree& t)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a genuine original witness tree and its retained claim fields. |
| inputs / outputs | Writes optional root/claimed connex/height and ordered node label/kind/scope/children/occurrence/separator. |
| invariants | Claim fields are preserved, not independently checked here. Public witness exporters reach this only through a typed published incumbent. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | O(tree nodes + stored ID/label bytes + output), no tree validation or C* rescan. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0035

[Lines 125–127](../../../../../src/io/query_explain.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void counters(Writer& w,const WorkCounters& c)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one recorded continuation phase work/time counter set. |
| inputs / outputs | Writes attempted, committed transitions, allocation failures, active nanoseconds/cap flag and depth maxima. |
| invariants | attempted and committed transitions have distinct accounting. active_nanoseconds==UINT64_MAX means at cap and may be capped, not proven exact elapsed time. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Fixed numeric/Boolean fields; no clock read or work charging. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0036

[Lines 128–128](../../../../../src/io/query_explain.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void phase_limit(Writer& w,const PhaseCeiling& p)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode optional phase work and active-time ceilings. |
| inputs / outputs | Writes work optional and duration.count() if active_time exists, otherwise null. |
| invariants | Ceilings are captured configuration, not elapsed observations; omitted ceiling is not zero. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Fixed optionals/digits, no clock or limit change. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0037

[Lines 129–136](../../../../../src/io/query_explain.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void search(Writer& w,const QueryExplanation& e)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode captured exact-search progress without advancing it. |
| inputs / outputs | Absent search is null; present writes policy/phase/recorded last stop/result, observed height interval, completion/revision, producer/replay counters, structural observations and captured limits. |
| invariants | Factory pairs policy/limits with search progress. Owner recorded last_stop excludes nonmutating zero-quantum returns. Observed upper/progress completion cannot manufacture a typed optimum or publish hidden witness. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Fixed progress/limit fields plus formatting bytes; no search, replay, recognizer or clock. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0038

[Lines 137–141](../../../../../src/io/query_explain.cpp#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void replay(Writer& w,const QueryExplanation& e)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode captured independent certificate-replay progress. |
| inputs / outputs | Absent replay is null; present writes phase/last stop/complete/valid/checked claims/revision/work and captured limits. |
| invariants | Unchecked input claim details stay hidden until a checked handle exists. Factory pairs replay limits; zero-quantum nonmutating return is not rewritten into recorded owner history. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Fixed progress/limit fields plus output; no proof traversal. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0039

[Lines 142–143](../../../../../src/io/query_explain.cpp#L142); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L142-L143:sha256:8e96b080f4630524c51f82250987f975079f86f4e4eb724fd4a873cb4ed9bc10
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Observed upper, published checked witness and independently proved minimum are distinct. An unpublished strict-search upper cannot authorize tree export. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/query_explain.cpp lines 140-145; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [docs/code_specs/files/src/io/query_explain.cpp.md](query_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0040

[Lines 144–149](../../../../../src/io/query_explain.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void height(Writer& w,const QueryExplanation& e)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose height bounds while distinguishing typed proof from observed upper. |
| inputs / outputs | Writes QueryHeightStatus/lower/upper/evidence labels, minimum/infeasibility proof flags and witness exportability. |
| invariants | Without typed minimum/infeasibility, lower remains universal empty/nonempty CQ bound. An owner-observed upper may lack a published witness; no fake tree export is enabled. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | Fixed metadata/optional owning-handle access plus output; no new proof check. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0041

[Lines 150–150](../../../../../src/io/query_explain.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void witness(Writer& w,const QueryExplanation& e)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an optional published typed checked upper witness. |
| inputs / outputs | No witness is null; present writes exact-original-binding authority label, height and tree. |
| invariants | Checked upper is not itself a minimum. No observed-but-unpublished producer candidate becomes an exportable tree. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | O(witness nodes/IDs/labels + encoded bytes). |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0042

[Lines 151–154](../../../../../src/io/query_explain.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void certificate(Writer& w,const QueryExplanation& e)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode only a typed independently checked original certificate. |
| inputs / outputs | No checked certificate emits null; present writes algorithm/optional minimum/tree and ordered lower-bound claim fields. |
| invariants | QueryExplanation exposes certificates from verified optimum/infeasibility/checked handles, not raw unfinished replay input. Diagnostic certificate text is not a verification shortcut. |
| ownership | Borrows immutable source/report metadata synchronously; only local result/output state changes. Does not advance a producer, runtime, cursor, journal or work allowance. |
| failure | Access, binding, encoding, resource or allocation errors propagate. Local RAII releases partial result/output; no producer or committed runtime state is rolled back or published. |
| cost | O(certificate entries/occurrence lists/witness tree bytes + output), no replay work. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0043

[Lines 155–165](../../../../../src/io/query_explain.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void report(Writer& w,const QueryExplanation& e)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose the complete version1 query/search diagnostic artifact. |
| inputs / outputs | Writes source/accounting, exact binding, height/progress/witness/certificate and explicit absent recognition/cost/runtime/durable scopes. |
| invariants | Factory-produced owning QueryExplanation supplies authority. Recorded producer/replay phases remain distinct; catalog estimates are metadata. Constant-operator and global-cost/runtime guarantees are outside original structural proof domain. |
| ownership | Borrows owning immutable QueryExplanation and builds private ordinary output only. |
| failure | Any getter/enum/UTF-8/byte/allocation error unwinds local output without affecting the captured proof/producer. |
| cost | O(binding + exported witness/certificate metadata + output bytes), including any repeated tree content; no producer advancement, recognition or total memory cap. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Encodings and schemas](../../../../observability.md), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0044

[Lines 166–166](../../../../../src/io/query_explain.cpp#L166); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L166-L166:sha256:dfde80f4ecae22fb87dfc54f5093a1e113d61f4882bd7b2c586245fbf6da8190
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: A bound alone is insufficient: both tree transports require this typed owner. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/query_explain.cpp lines 164-168; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [docs/code_specs/files/src/io/query_explain.cpp.md](query_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0045

[Lines 167–167](../../../../../src/io/query_explain.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ValidatedIncumbent& need_witness(const QueryExplanation& e)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a genuinely published typed witness before any tree/DOT export. |
| inputs / outputs | Returns const ValidatedIncumbent& or throws query_explain_no_witness. |
| invariants | A numeric upper interval or raw certificate input is insufficient; strict unfinished producer can therefore report upper without exportable tree. |
| ownership | Borrowed witness reference remains inside QueryExplanation; caller retains report through encoding. |
| failure | query_explain_no_witness on absent published witness; invalid report getter faults propagate. |
| cost | Fixed optional/getter checks, no successful allocation. |
| Design | [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0046

[Lines 168–168](../../../../../src/io/query_explain.cpp#L168); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L168-L168:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [docs/code_specs/files/src/io/query_explain.cpp.md](query_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0047

[Lines 169–169](../../../../../src/io/query_explain.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_query_explain_json(const QueryExplanation& e,QueryExplainTextLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one complete owning query/search JSON string. |
| inputs / outputs | Builds capped Writer, renders report and moves out only completed output. |
| invariants | No public partial text, no imported proof authority and no producer/runtime mutation. |
| ownership | Returned std::string outlives capture/producer; no borrowed report pointer escapes. |
| failure | Getter/encoding/byte/allocation errors discard local partial output and propagate. |
| cost | Full report traversal + amortized ordinary string growth; final move transfers owned bytes. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp) |

## B0048

[Lines 170–170](../../../../../src/io/query_explain.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_query_explain_tree_json(const QueryExplanation& e,QueryExplainTextLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a complete typed original witness JSON artifact. |
| inputs / outputs | Checks need_witness first, then writes version1 authority/height, exact binding and tree. |
| invariants | Hidden/unpublished upper cannot pass; JSON tree remains diagnostic and does not become a new typed incumbent. |
| ownership | Returned string owns bytes independently of report/evidence. |
| failure | No-witness failure occurs before writer construction; later getter/encoding/byte/allocation failure returns no partial artifact. |
| cost | O(binding + witness metadata/output bytes), ordinary string growth. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0049

[Lines 171–180](../../../../../src/io/query_explain.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_query_explain_text(const QueryExplanation& e,QueryExplainTextLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish human query/search progress and original proof context. |
| inputs / outputs | Prints status/bounds, recorded phase/limits/counters, witness/proof presence, exact binding and explicit absent runtime/cost guarantees. |
| invariants | Nonempty contradiction metadata retains P06 universal lower1, separate from P08 constant_false operator0. Strict observed upper may be unpublished; source/cost/runtime completion is never inferred. |
| ownership | Final text owns its bytes; typed report stays borrowed during call. |
| failure | Access/enum/UTF-8/byte/allocation failures return no partial text and do not alter search/replay. |
| cost | O(binding/scalar/recorded progress/output bytes), no producer advance/clock/recognizer; ordinary output and scalar formatting may allocate. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0050

[Lines 181–184](../../../../../src/io/query_explain.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_query_explain_dot(const QueryExplanation& e,QueryExplainTextLimits limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish DOT only for the genuine published original witness. |
| inputs / outputs | Checks witness, writes original height caption, node labels/shapes and every stored child edge. |
| invariants | Admitted typed tree guarantees valid IDs/kinds. This is not a selected physical operator or proof importer; no witness is fabricated from an upper bound. |
| ownership | Returned DOT owns bytes independently of report; witness/tree references are synchronous. |
| failure | Missing witness rejects first; later access/text/byte/allocation errors discard only private output. |
| cost | O(nodes + child edges + escaped label/output bytes), one ordinary growing output string, no graph clone. |
| Design | [docs/observability.md §Encodings and schemas](../../../../observability.md), [include/crown/observability/query_explain.hpp](../../../../../include/crown/observability/query_explain.hpp), [include/crown/io/query_explain.hpp](../../../../../include/crown/io/query_explain.hpp), [docs/observability.md §Height, cost, and proof scope](../../../../observability.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0051

[Lines 185–185](../../../../../src/io/query_explain.cpp#L185); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L185:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/query_explain.cpp](../../../../../src/io/query_explain.cpp), [docs/code_specs/files/src/io/query_explain.cpp.md](query_explain.cpp.md), [docs/observability.md](../../../../observability.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
