# `src/io/inspection.cpp` — block usage map

[Source](../../../../../src/io/inspection.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `f904fd77243f1786cd6406dda0dc655225175474e2dd0c1291e3a5799e437f3d`. 161 lines partitioned into 23 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../src/io/inspection.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body. | source comment (unverified): // The ceiling bounds encoded length; ordinary string capacity may be larger. · [reviewed contract](#b0001) |
| [B0002 · 16–18](../../../../../src/io/inspection.cpp#L16) | Callable definition: void room(std::size_t count) const | calls size, Error · [reviewed contract](#b0002) |
| [B0003 · 19–19](../../../../../src/io/inspection.cpp#L19) | Callable definition: void raw(std::string_view value) | calls room, size, append · [reviewed contract](#b0003) |
| [B0004 · 20–23](../../../../../src/io/inspection.cpp#L20) | Callable definition: void number(std::uint64_t value) | calls std::to_chars, raw, std::string_view · [reviewed contract](#b0004) |
| [B0005 · 24–27](../../../../../src/io/inspection.cpp#L24) | Callable definition: void signed_number(std::int64_t value) | calls std::to_chars, raw, std::string_view · [reviewed contract](#b0005) |
| [B0006 · 28–28](../../../../../src/io/inspection.cpp#L28) | Callable definition: void boolean(bool value) | calls raw · [reviewed contract](#b0006) |
| [B0007 · 29–49](../../../../../src/io/inspection.cpp#L29) | Callable definition: void text(std::string_view value) | calls room, size, Error, ingest_detail::require_utf8; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 50–54](../../../../../src/io/inspection.cpp#L50) | Callable definition: template&lt;class Range,class Function&gt; void array(const Range& values,Function function) | calls raw, function; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 55–64](../../../../../src/io/inspection.cpp#L55) | Callable definition: void row(const Row& values) | calls array, std::visit, constexpr, signed_number · [reviewed contract](#b0009) |
| [B0010 · 65–65](../../../../../src/io/inspection.cpp#L65) | Callable definition: void rows(const Relation& values) | calls array, row · [reviewed contract](#b0010) |
| [B0011 · 66–68](../../../../../src/io/inspection.cpp#L66) | Callable definition: void counts(const std::vector&lt;CanonicalCount&gt;& values) | calls array, raw, row, number · [reviewed contract](#b0011) |
| [B0012 · 69–86](../../../../../src/io/inspection.cpp#L69) | Callable definition: void support(const CanonicalSupportState& state) | calls raw, text, number, boolean · [reviewed contract](#b0012) |
| [B0013 · 87–91](../../../../../src/io/inspection.cpp#L87) | Callable definition: void physical(const CanonicalPhysicalState& state) | calls raw, support, number, array · [reviewed contract](#b0013) |
| [B0014 · 92–95](../../../../../src/io/inspection.cpp#L92) | Callable definition: void buckets(const std::vector&lt;CanonicalBucket&gt;& values) | calls array, raw, row, number · [reviewed contract](#b0014) |
| [B0015 · 96–103](../../../../../src/io/inspection.cpp#L96) | Callable definition: void live(const CanonicalLiveState& state) | calls raw, number, array, rows · [reviewed contract](#b0015) |
| [B0016 · 104–104](../../../../../src/io/inspection.cpp#L104) | Closes surrounding scope/type. |  · [reviewed contract](#b0016) |
| [B0017 · 105–114](../../../../../src/io/inspection.cpp#L105) | Callable definition: std::string_view code(InvariantCode value) | calls CROWN_CASE, Error; returns #name · [reviewed contract](#b0017) |
| [B0018 · 115–124](../../../../../src/io/inspection.cpp#L115) | Callable definition: std::string_view component(InvariantComponent value) | calls CROWN_CASE, Error; returns #name · [reviewed contract](#b0018) |
| [B0019 · 125–125](../../../../../src/io/inspection.cpp#L125) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0019) |
| [B0020 · 126–128](../../../../../src/io/inspection.cpp#L126) | Callable definition: std::string write_runtime_state(const CanonicalPhysicalState& state,std::size_t limit) | calls raw, physical, std::move; returns std::move(out.output) · [reviewed contract](#b0020) |
| [B0021 · 129–133](../../../../../src/io/inspection.cpp#L129) | Callable definition: std::string write_runtime_state(const CanonicalDeltaState& state,std::size_t limit) | calls raw, physical, boolean, live; returns std::move(out.output) · [reviewed contract](#b0021) |
| [B0022 · 134–160](../../../../../src/io/inspection.cpp#L134) | Callable definition: std::string write_invariant_report(const InvariantReport& report,std::size_t limit) | calls raw, boolean, valid, number; returns std::move(out.output) · [reviewed contract](#b0022) |
| [B0023 · 161–161](../../../../../src/io/inspection.cpp#L161) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0023) |

## B0001

[Lines 1–15](../../../../../src/io/inspection.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/io/inspection.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode bounded runtime diagnostic JSON directly into ordinary caller-owned text. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
struct Writer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep a private direct encoder and its explicit encoded-byte ceiling. |
| inputs / outputs | Writer is aggregate-initialized with empty output and caller limit; members append only through checked paths. |
| invariants | Encoded length is capped; std::string capacity/allocator framing is not included in that ceiling. Report fields remain diagnostic DTO values. |
| ownership | Owns std::string output; implicit copying would deep-copy text and can allocate, while moving transfers its buffer. |
| failure | Partial output stays local when bounds/UTF8/enum/allocation fail; no runtime state is mutated. |
| cost | O(encoded bytes) writes plus traversal/validation, with ordinary string growth and potentially overlapping old/new capacity. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
std::string output;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the complete encoded diagnostic accumulated so far. |
| inputs / outputs | Mutable ordinary string grows through raw(); public writer moves it out on success. |
| invariants | Logical size is bounded by limit; capacity can exceed logical length. |
| ownership | Independent ordinary byte ownership; no MemoryAccount funding or shared runtime row ownership. |
| failure | append/growth can throw before a full string is returned; local destruction discards partial output. |
| cost | Storage O(encoded length/capacity); copy O(length), final buffer release follows ordinary allocator cost. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
std::size_t limit;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the maximum number of encoded output bytes accepted by the caller. |
| inputs / outputs | size_t input copied into Writer; room checks it before each append. |
| invariants | This bounds output length, not runtime-state cardinality, elapsed scan work or allocated capacity. |
| ownership | Inline scalar, no retention of caller state. |
| failure | Reading/storing limit cannot fail; room emits the resource failure. |
| cost | O(1) storage/access. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–18](../../../../../src/io/inspection.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void room(std::size_t count) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check append capacity using subtraction that cannot underflow. |
| inputs / outputs | Requested count in; return only when output.size()+count fits caller limit. |
| invariants | First rejects existing size&gt;limit before evaluating limit-size; output is unchanged. |
| ownership | Reads Writer state only; retains no input. |
| failure | Throws resource_limit Error before append; diagnostic/exception construction may allocate. |
| cost | O(1) integer comparisons, no success-path allocation. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 19–19](../../../../../src/io/inspection.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void raw(std::string_view value) { room(value.size()); output.append(value); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append an already encoded fragment after the byte guard. |
| inputs / outputs | Borrowed string_view in; bytes copied into output. |
| invariants | raw assumes caller supplied JSON punctuation/numeric/previously escaped data; it does not validate arbitrary UTF8 or JSON syntax. |
| ownership | Output owns copied fragment; input is borrowed through append. |
| failure | room can throw before copy; string append can allocate/fail; public wrapper never exposes partial output. |
| cost | O(fragment bytes) plus amortized string growth; a reallocation can copy the existing prefix. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 20–23](../../../../../src/io/inspection.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void number(std::uint64_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a unsigned64-bit integer without temporary owning numeric text. |
| inputs / outputs | Integer in; to_chars fills a32-byte stack buffer then raw appends its decimal digits. |
| invariants | The fixed buffer exceeds the largest admitted64-bit decimal spelling; no locale-dependent formatting. |
| ownership | Temporary bytes are stack-owned until raw copies them into output. |
| failure | raw byte/OOM failure propagates; no integer overflow or recovery handler. |
| cost | At most20 digit/sign bytes converted and appended, O(1) stack space; output growth can allocate. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 24–27](../../../../../src/io/inspection.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void signed_number(std::int64_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a signed64-bit integer without temporary owning numeric text. |
| inputs / outputs | Integer in; to_chars fills a32-byte stack buffer then raw appends its decimal digits. |
| invariants | The fixed buffer exceeds the largest admitted64-bit decimal spelling; no locale-dependent formatting. |
| ownership | Temporary bytes are stack-owned until raw copies them into output. |
| failure | raw byte/OOM failure propagates; no integer overflow or recovery handler. |
| cost | At most20 digit/sign bytes converted and appended, O(1) stack space; output growth can allocate. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 28–28](../../../../../src/io/inspection.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boolean(bool value) { raw(value?"true":"false"); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write a Boolean JSON literal. |
| inputs / outputs | bool in; appends true/false through raw. |
| invariants | Fixed JSON spellings, subject to the same output ceiling. |
| ownership | Borrows static literal and copies it into owned output. |
| failure | raw bound/allocation failure propagates. |
| cost | O(1) fragment work; buffer growth may allocate. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 29–49](../../../../../src/io/inspection.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void text(std::string_view value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and escape UTF8 text into bounded JSON string syntax. |
| inputs / outputs | Borrowed bytes in; appends opening quote, escaped content and closing quote. |
| invariants | Initial lower-bound length guard is followed by UTF8 validation; each escape append rechecks actual encoded length. Control bytes use standard escapes or six-byte unicode forms. |
| ownership | Input is borrowed; one ordinary output string is grown; no DOM or whole escaped-string shadow. |
| failure | resource_limit may occur before or during escaping; UTF8 Error before first quote; OOM while appending; no partial public return. |
| cost | O(input bytes+encoded bytes), up to6 bytes per escaped control byte; O(1) local scratch besides output capacity. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
for (const char character : value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Escape each validated UTF8 byte into legal JSON string content. |
| inputs / outputs | Iterates value after complete require_utf8; appends standard escapes, six-byte control escape or original byte. |
| invariants | Non-ASCII byte sequences pass through exactly after validation; raw rechecks byte budget for every fragment. |
| ownership | One local char and fixed hex/control arrays; output owns appended bytes. |
| failure | Output limit/allocation can fail mid-string, which stays private to enclosing public writer. |
| cost | O(input bytes+encoded bytes), with per-byte raw guards and ordinary output growth. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 50–54](../../../../../src/io/inspection.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Range,class Function> void array(const Range& values,Function function) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Traverse a range once and let a callback emit each element. |
| inputs / outputs | Borrowed range and synchronous callback in; bracket/comma syntax appended, callbacks may recurse into Writer. |
| invariants | Preserves iteration order and invokes callback once per element; this does not canonicalize or sort a DTO. |
| ownership | No element copies or new backing container; callback captures obey caller lifetimes. |
| failure | Callback/raw failures propagate, discarding the local public writer output. |
| cost | O(element count)+sum callback work/encoded bytes; no per-element container allocation beyond output/callees. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 55–64](../../../../../src/io/inspection.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void row(const Row& values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a row of ordinary owning scalar alternatives. |
| inputs / outputs | Row in; emits int64/string/bool or tagged date/decimal JSON in existing order. |
| invariants | Valid Value alternatives required; string passes UTF8/escaping; date/decimal use canonical to_string then text. |
| ownership | Input row borrowed. Date/decimal formatting creates temporary ordinary strings; output owns copied encoded bytes. |
| failure | Valueless variant can throw bad_variant_access; formatting/UTF8/byte/OOM failures propagate; no state publication. |
| cost | O(fields+text/decimal/encoded bytes), date/decimal temporary text can allocate; no claimed allocation-free row serialization. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
array(values,[&](const auto& value) { std::visit([&](const auto& cell) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Visit one scalar alternative and invoke its exact direct encoder. |
| inputs / outputs | Nested synchronous row-array/std::visit callbacks receive Value/cell by const reference. |
| invariants | int64/string/bool branches encode directly; date/decimal branch produces tagged canonical text; invalid valueless variant is not silently replaced. |
| ownership | Callbacks borrow Writer/Row; formatting strings are temporary owning ordinary text. |
| failure | Variant/format/UTF8/byte/OOM errors propagate to enclosing local writer. |
| cost | O(scalar bytes), plus date/decimal temporary formatting and output allocation; no row graph clone. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 65–65](../../../../../src/io/inspection.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rows(const Relation& values) { array(values,[&](const auto& value) { row(value); }); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an ordinary relation as ordered rows. |
| inputs / outputs | Relation in; emits array with row() for each existing row; no sorting/deduplication. |
| invariants | Canonical ordering must be supplied by the diagnostic producer. |
| ownership | Relation borrowed; output independently owns bytes. |
| failure | row/raw failures propagate. |
| cost | O(rows+fields+scalar/encoded bytes); output growth and scalar formatting can allocate. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 66–68](../../../../../src/io/inspection.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void counts(const std::vector<CanonicalCount>& values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode projection-key/count diagnostics. |
| inputs / outputs | CanonicalCount vector in; emits each key row and unsigned count. |
| invariants | Counts and key ordering are reported as supplied; serialization does not rederive support invariants. |
| ownership | Borrows vector/keys, owns only output text. |
| failure | row/number/raw failure propagates. |
| cost | O(entries+key fields/bytes+encoded bytes). |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 69–86](../../../../../src/io/inspection.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void support(const CanonicalSupportState& state) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the complete provided canonical support snapshot. |
| inputs / outputs | CanonicalSupportState in; writes binding fields, sequence, nodes, records, child flags, survivors, parent and optional visible counts. |
| invariants | Only native/generalized node kinds admitted; has_answer, binding and counts are DTO reports rather than a fresh invariant or authority check. |
| ownership | Snapshot graph borrowed; encoded text owns copies of names/row values. No live support state is retained or mutated. |
| failure | Unknown node kind throws invalid_document; nested UTF8/encoding/OOM failures propagate. |
| cost | Full traversal of supplied nodes/records/flags/relations/keys and scalar bytes; no hidden runtime rescan or sort, ordinary output can allocate. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
array(state.nodes,[&](const auto& node) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one support node and all of its recorded state components. |
| inputs / outputs | Node callback emits kind/records/child flags/survivors/parent/visible counts. |
| invariants | Unknown node.kind rejects before record serialization; no satisfaction/count invariants are recalculated. |
| ownership | Borrows node and captures Writer; output copies values into ordinary string. |
| failure | Node enum/nested serialization failures propagate. |
| cost | Visits all node records/memberships/keys/flags with repeated scalar encoding; no extra live engine scan. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 87–91](../../../../../src/io/inspection.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void physical(const CanonicalPhysicalState& state) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the provided physical support/source/derivation snapshot. |
| inputs / outputs | CanonicalPhysicalState in; emits support, sequence, sources and derivation counts. |
| invariants | Caller snapshot is already canonical if desired; encoder does not verify source-versus-derived consistency. |
| ownership | All rows/maps are borrowed diagnostic values; independent output owns bytes. |
| failure | Nested serializer/byte/UTF8/OOM errors propagate without runtime mutation. |
| cost | O(total supplied support/source/derivation cells+bytes), including repeated values present in the DTO. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 92–95](../../../../../src/io/inspection.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void buckets(const std::vector<CanonicalBucket>& values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode live-factor index buckets with both key counts and member rows. |
| inputs / outputs | CanonicalBucket vector in; emits key, count and rows for each bucket. |
| invariants | No recomputation of count/member consistency or ordering. |
| ownership | Borrowed keys/rows, independently owned encoded output. |
| failure | Nested encoding/resource errors propagate. |
| cost | Visits every bucket, key and member row; repeated rows across buckets are encoded repeatedly. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 96–103](../../../../../src/io/inspection.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void live(const CanonicalLiveState& state) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode live delta-factor diagnostics and their stated aggregate counts. |
| inputs / outputs | CanonicalLiveState in; emits sequence/totals and factor rows/parent/child buckets. |
| invariants | Totals are reported without recomputing them from factors; this is diagnostic serialization. |
| ownership | Borrows complete DTO; output owns only bytes. |
| failure | Nested encoding/resource errors propagate. |
| cost | O(all factors, memberships, rows, fields and encoded scalar bytes); no live engine scan here. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 104–104](../../../../../src/io/inspection.cpp#L104); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L104-L104:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing helper type at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [docs/code_specs/files/src/io/inspection.cpp.md](inspection.cpp.md), [docs/observability.md](../../../../observability.md), [docs/physical_runtime.md](../../../../physical_runtime.md) |

## B0017

[Lines 105–114](../../../../../src/io/inspection.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view code(InvariantCode value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map InvariantCode into its stable diagnostic spelling. |
| inputs / outputs | Enum in; string_view of static spelling out. |
| invariants | Only declared enum values are accepted; labels do not certify an invariant check. |
| ownership | Returned view borrows static literal storage and retains no report/runtime owner. |
| failure | Unknown enum throws invalid_document Error; no catch. |
| cost | Fixed switch O(1), no success-path text allocation. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 115–124](../../../../../src/io/inspection.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view component(InvariantComponent value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map InvariantComponent into its stable diagnostic spelling. |
| inputs / outputs | Enum in; string_view of static spelling out. |
| invariants | Only declared enum values are accepted; labels do not certify an invariant check. |
| ownership | Returned view borrows static literal storage and retains no report/runtime owner. |
| failure | Unknown enum throws invalid_document Error; no catch. |
| cost | Fixed switch O(1), no success-path text allocation. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 125–125](../../../../../src/io/inspection.cpp#L125); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L125-L125:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [docs/code_specs/files/src/io/inspection.cpp.md](inspection.cpp.md), [docs/observability.md](../../../../observability.md), [docs/physical_runtime.md](../../../../physical_runtime.md) |

## B0020

[Lines 126–128](../../../../../src/io/inspection.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_runtime_state(const CanonicalPhysicalState& state,std::size_t limit) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a complete bounded physical diagnostic text artifact. |
| inputs / outputs | Borrowed canonical state and output-byte ceiling in; owning JSON-syntax std::string out. |
| invariants | Public return occurs only after closing syntax is written; fields/flags supplied by DTO are not checked runtime proof/native authority. |
| ownership | Local Writer owns partial output, moves completed buffer to caller; input backing remains caller-owned. |
| failure | Bounds, UTF8, invalid enum/scalar or ordinary OOM propagates; partial local text is discarded. |
| cost | Full physical DTO traversal and scalar-byte escaping; delta additionally visits optional live factor DTO; output string allocation outside hot update work. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 129–133](../../../../../src/io/inspection.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_runtime_state(const CanonicalDeltaState& state,std::size_t limit) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a complete bounded delta diagnostic text artifact. |
| inputs / outputs | Borrowed canonical state and output-byte ceiling in; owning JSON-syntax std::string out. |
| invariants | Public return occurs only after closing syntax is written; fields/flags supplied by DTO are not checked runtime proof/native authority. |
| ownership | Local Writer owns partial output, moves completed buffer to caller; input backing remains caller-owned. |
| failure | Bounds, UTF8, invalid enum/scalar or ordinary OOM propagates; partial local text is discarded. |
| cost | Full delta DTO traversal and scalar-byte escaping; delta additionally visits optional live factor DTO; output string allocation outside hot update work. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 134–160](../../../../../src/io/inspection.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string write_invariant_report(const InvariantReport& report,std::size_t limit) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an existing invariant report without rerunning the invariant inspector. |
| inputs / outputs | InvariantReport plus encoded-byte limit in; complete owned diagnostic text out. |
| invariants | valid() reads complete/issues; serialized complete/valid/work are current report facts, not a new proof. Optional IDs/expected/actual appear only when present. |
| ownership | Report borrowed; each native issue key is exported to an ordinary temporary Row before encoding, so its scalar payload is deep-copied. |
| failure | Enum/key-export/UTF8/byte/allocation failure propagates before public return; no report mutation. |
| cost | Fixed statistics fields plus all issues/key cells/bytes; explicit export_row allocates ordinary rows/strings, then scalar encoding and output growth add cost. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
const auto stat=[&](std::string_view name,std::uint64_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit each named invariant statistic with correct comma placement. |
| inputs / outputs | Synchronous lambda accepts static name and uint64_t; mutates first/out locals only. |
| invariants | Statistics macro expands to fixed names; no live measurement is performed. |
| ownership | References borrow stack Writer/first until the enclosing serializer returns. |
| failure | Writer failures propagate into the local incomplete artifact. |
| cost | O(1) work per named scalar field plus name/digits copied into output. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

```text
out.raw("},\"issues\":"); out.array(report.issues,[&](const auto& issue) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize each issue including optional context and an explicit owning key export. |
| inputs / outputs | Borrows one issue in out.array callback; emits code/component and available fields. |
| invariants | Key may be a native AccountedRow; export_row is a deliberate caller DTO boundary, not a borrowed constant-time conversion. |
| ownership | Callback borrows report/out; temporary ordinary Row owns exported cell/string bytes for the row call. |
| failure | Key export and writer failure abort the enclosing serializer without changing report. |
| cost | O(issue key fields+bytes) extra export allocation and a second pass for encoding. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 161–161](../../../../../src/io/inspection.cpp#L161); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L161-L161:sha256:a992a30ac7c9748c33994a213cb5eed12f62a6204d01f8b49f69db451a145039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [docs/code_specs/files/src/io/inspection.cpp.md](inspection.cpp.md), [docs/observability.md](../../../../observability.md), [docs/physical_runtime.md](../../../../physical_runtime.md) |
