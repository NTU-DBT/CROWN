# `src/io/input_view.cpp` — block usage map

[Source](../../../../../src/io/input_view.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `2232817cabf469e1d524819a1835a5dbd49a092005b7c611d29030c466498588`. 121 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/io/input_view.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 11–14](../../../../../src/io/input_view.cpp#L11) | Callable definition: std::optional&lt;SourcePositionView&gt; borrow_position(const std::optional&lt;SourcePosition&gt;& source) noexcept | calls ; returns {}; SourcePositionView{source-&gt;source,source-&gt;offset} · [reviewed contract](#b0002) |
| [B0003 · 15–15](../../../../../src/io/input_view.cpp#L15) | Closes surrounding scope/type. |  · [reviewed contract](#b0003) |
| [B0004 · 16–16](../../../../../src/io/input_view.cpp#L16) | Callable definition: bool SourcePositionView::operator==(const SourcePosition& other) const | returns source==other.source && offset==other.offset · [reviewed contract](#b0004) |
| [B0005 · 17–19](../../../../../src/io/input_view.cpp#L17) | Callable definition: InputEventView InputEventView::borrow(const InputEvent& source) noexcept | calls runtime::PhysicalUpdateView::borrow, borrow_position; returns {runtime::PhysicalUpdateView::borrow(source.update),borrow_position(source.source_position)} · [reviewed contract](#b0005) |
| [B0006 · 20–27](../../../../../src/io/input_view.cpp#L20) | Callable definition: WindowCommandView WindowCommandView::borrow(const WindowCommand& source) noexcept | calls borrow_position, storage::TupleValuesView::borrow; returns result; growth insert · [reviewed contract](#b0006) |
| [B0007 · 28–29](../../../../../src/io/input_view.cpp#L28) | declares namespace scope. |  · [reviewed contract](#b0007) |
| [B0008 · 30–32](../../../../../src/io/input_view.cpp#L30) | Callable definition: void require(bool condition,std::string_view code,std::string_view message) | calls Error, std::string; guard void require(bool condition,std::string_view code,std::string_view message) { · [reviewed contract](#b0008) |
| [B0009 · 33–52](../../../../../src/io/input_view.cpp#L33) | Callable definition: template&lt;class CatalogView&gt; RowIssue issue_for(const CatalogView& catalog,TableId table,storage::TupleValuesView values) | calls size, legacy_row, valueless_by_exception, storage::type_of; returns issue; issue; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 53–64](../../../../../src/io/input_view.cpp#L53) | Callable definition: template&lt;class CatalogView&gt; void reject_row(const CatalogView& catalog,TableId table,RowIssue issue) | calls Error, std::string, std::terminate · [reviewed contract](#b0010) |
| [B0011 · 65–71](../../../../../src/io/input_view.cpp#L65) | Callable definition: void position(const std::optional&lt;SourcePositionView&gt;& source,const InputLimits& limits) | calls require, size, empty, find; guard require(source-&gt;source.size()&lt;=limits.source_bytes,"resource_limit","input source identifier exceed… · [reviewed contract](#b0011) |
| [B0012 · 72–90](../../../../../src/io/input_view.cpp#L72) | Callable definition: void payload(storage::TupleValuesView values,const InputLimits& limits,bool window) | calls size, ingest_detail::require_utf8, render, require; guard require(bytes&lt;=limits.field_bytes,"resource_limit",window?"window input scalar field exceeds its by…; 1 loop sites; source comment (unverified): // Typed payload units differ from wire length; preserve the established UTF-8 error order. · [reviewed contract](#b0012) |
| [B0013 · 91–100](../../../../../src/io/input_view.cpp#L91) | Callable definition: template&lt;class CatalogView&gt; void event(const InputEventView& value,const CatalogView& catalog,const InputLimits& limits,RowIssue … | calls require, size, reject_row, payload; guard require(value.update.table.value&lt;catalog.tables.size(),"unknown_table","physical input table ID is …; growth insert · [reviewed contract](#b0013) |
| [B0014 · 101–112](../../../../../src/io/input_view.cpp#L101) | Callable definition: template&lt;class CatalogView&gt; void command(const WindowCommandView& value,const CatalogView& catalog,const InputLimits& limits,RowI… | calls require, valueless_by_exception, size, reject_row; guard require(!value.command.valueless_by_exception() && !std::holds_alternative&lt;std::monostate&gt;(value.co…; growth insert · [reviewed contract](#b0014) |
| [B0015 · 113–113](../../../../../src/io/input_view.cpp#L113) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0015) |
| [B0016 · 114–114](../../../../../src/io/input_view.cpp#L114) | Callable definition: RowIssue row_issue(const Catalog& catalog,TableId table,storage::TupleValuesView values) | calls issue_for; returns issue_for(catalog,table,values) · [reviewed contract](#b0016) |
| [B0017 · 115–115](../../../../../src/io/input_view.cpp#L115) | Callable definition: RowIssue row_issue(const program::Catalog& catalog,TableId table,storage::TupleValuesView values) | calls issue_for; returns issue_for(catalog,table,values) · [reviewed contract](#b0017) |
| [B0018 · 116–116](../../../../../src/io/input_view.cpp#L116) | Callable definition: void validate(const InputEventView& value,const Catalog& catalog,const InputLimits& limits,RowIssue issue) | calls event · [reviewed contract](#b0018) |
| [B0019 · 117–117](../../../../../src/io/input_view.cpp#L117) | Callable definition: void validate(const InputEventView& value,const program::Catalog& catalog,const InputLimits& limits,RowIssue issue) | calls event · [reviewed contract](#b0019) |
| [B0020 · 118–118](../../../../../src/io/input_view.cpp#L118) | Callable definition: void validate(const WindowCommandView& value,const Catalog& catalog,const InputLimits& limits,RowIssue issue) | calls command · [reviewed contract](#b0020) |
| [B0021 · 119–119](../../../../../src/io/input_view.cpp#L119) | Callable definition: void validate(const WindowCommandView& value,const program::Catalog& catalog,const InputLimits& limits,RowIssue issue) | calls command · [reviewed contract](#b0021) |
| [B0022 · 120–121](../../../../../src/io/input_view.cpp#L120) | Closes surrounding scope/type. | source comment (unverified): // namespace input_detail · [reviewed contract](#b0022) |

## B0001

[Lines 1–10](../../../../../src/io/input_view.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/io/input_view.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt external owning input DTOs into views and enforce native row/envelope limits without a JSON round trip. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 11–14](../../../../../src/io/input_view.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<SourcePositionView> borrow_position(const std::optional<SourcePosition>& source) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow optional source-position metadata from an owning DTO. |
| inputs / outputs | Absent optional maps to absent; present source yields source string_view and copied offset. |
| invariants | Keep original SourcePosition/string alive and unmodified while the view is used. |
| ownership | No text ownership is retained by SourcePositionView. |
| failure | noexcept; it performs no text validation. |
| cost | O(1), no source-byte copy/allocation. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 15–15](../../../../../src/io/input_view.cpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L15:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the enclosing implementation scope at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [docs/code_specs/files/src/io/input_view.cpp.md](input_view.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0004

[Lines 16–16](../../../../../src/io/input_view.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SourcePositionView::operator==(const SourcePosition& other) const {return source==other.source && offset==other.offset;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a source-position view with an owning value. |
| inputs / outputs | Reads source bytes and offset, returns exact equality. |
| invariants | Comparison is byte-exact, without UTF8/name validity or ordering checks. |
| ownership | Both source backings borrowed; no retained owner. |
| failure | Caller provides live string_view backing; no intentional error translation. |
| cost | O(source bytes compared), O(1) extra space. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 17–19](../../../../../src/io/input_view.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputEventView InputEventView::borrow(const InputEvent& source) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the physical update and source metadata of an InputEvent. |
| inputs / outputs | Returns InputEventView of copied scalar envelope plus borrowed row/source backing. |
| invariants | Borrowing does not validate malformed rows, sequence or operations and does not extend DTO lifetime. |
| ownership | Both values and source name borrow source; no deep row/string copy. |
| failure | noexcept; later validators own rejection. |
| cost | O(1) view construction, no allocation. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 20–27](../../../../../src/io/input_view.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowCommandView WindowCommandView::borrow(const WindowCommand& source) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve the external window command variant while borrowing insertion values. |
| inputs / outputs | Copies sequence/source metadata; recognized insert/withdraw/watermark become corresponding view alternatives. |
| invariants | Unrecognized/valueless external command remains default monostate and is rejected at head validation, rather than silently becoming a valid command. |
| ownership | Insertion values and source text borrow original DTO; scalar withdraw/watermark payload is copied inline. |
| failure | noexcept; no semantic validation/allocation in this adapter. |
| cost | O(1) alternative tests and view/scalar copies. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 28–29](../../../../../src/io/input_view.cpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L29:sha256:01b645de87a0d2c56e0c6aaa2e09b2b8017fdb46a187e8260ff8efdacb82373f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Opens the internal input_detail namespace and a nested anonymous helper scope for view validation and row-issue checks. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [docs/code_specs/files/src/io/input_view.cpp.md](input_view.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0008

[Lines 30–32](../../../../../src/io/input_view.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool condition,std::string_view code,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the public contextual input error only when a guard fails. |
| inputs / outputs | Boolean plus borrowed diagnostic code/message in; returns on true or throws Error owning strings. |
| invariants | Does not catch native account/OOM or convert unrelated exception types. |
| ownership | Successful guard retains no input; rejected diagnostics copy ordinary text. |
| failure | Error/string construction and exception unwind may allocate; no success-path owner mutation. |
| cost | O(1) true guard; rejection O(code+message bytes) construction plus exception cost. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 33–52](../../../../../src/io/input_view.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> RowIssue issue_for(const CatalogView& catalog,TableId table,storage::TupleValuesView values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify schema/decimal-domain issues before retaining or consuming typed row payload. |
| inputs / outputs | Stable catalog/table and TupleValuesView in; first RowIssue out, including original arity and offending field. |
| invariants | Checks table before indexing, arity before cells; checks valueless legacy scalar before scalar access; only decimal-decorated fields use decimal domain checks. |
| ownership | Borrows catalog/row backing; no copied row/text or formatted diagnostic is retained. |
| failure | Returns issue for admitted problem kinds; invalid borrowed backing is caller misuse and accessor-level errors are not caught. |
| cost | O(arity) field inspection, bounded inline decimal-parts work per decimal; no row/text allocation on normal classification. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
for(std::size_t field=0;field<values.size();++field) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop row schema classification at its first offending scalar/domain. |
| inputs / outputs | Iterates borrowed cells after table/arity checks and updates issue.field. |
| invariants | Legacy valueless scalar checked before scalar conversion; scalar type checked before std::get&lt;InlineDecimal&gt;. Matching schema decimal spec required. |
| ownership | No row retention/clone; decimal parts view borrows fixed inline scalar representation during check. |
| failure | Returns RowIssue instead of formatted Error for known rejection, but accessor-level problems still propagate. |
| cost | One O(fields) pass; successful primitive cells allocate no owned payload. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 53–64](../../../../../src/io/input_view.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> void reject_row(const CatalogView& catalog,TableId table,RowIssue issue) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct a precise public row diagnostic from deferred minimal metadata. |
| inputs / outputs | Matching catalog/table/RowIssue in; none returns, other cases throw their established Error code/message. |
| invariants | type/decimal_domain require field/table from the same valid classification; the enum is internal, not trusted arbitrary caller evidence. |
| ownership | Borrows catalog; rejection copies the affected column name into an ordinary diagnostic. |
| failure | Errors are intentionally not caught; unknown RowProblem terminates as an internal contract violation. |
| cost | O(1) dispatch plus O(column-name bytes) for contextual errors and exception construction. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 65–71](../../../../../src/io/input_view.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void position(const std::optional<SourcePositionView>& source,const InputLimits& limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate optional source identity bytes before retaining accepted source progress. |
| inputs / outputs | Optional borrowed SourcePositionView plus InputLimits in; no output/mutation. |
| invariants | Length guard precedes nonempty/NUL check and UTF8 validation. Offset monotonicity and distinct-source counts belong to source owners. |
| ownership | Source text remains borrowed, never copied here. |
| failure | resource_limit or invalid_source_position/UTF8 Error on rejection; no local handler. |
| cost | O(source length) NUL and UTF8 scans; absent source O(1). |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 72–90](../../../../../src/io/input_view.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void payload(storage::TupleValuesView values,const InputLimits& limits,bool window) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure and validate typed scalar payload using the documented transport accounting model. |
| inputs / outputs | TupleValuesView, limits and window flag in; checks every field and accumulated record units; no mutation/result. |
| invariants | int64/bool contribute one unit and bypass field_bytes; date contributes10; decimal contributes canonical rendered bytes; string contributes its byte length. Size arithmetic is overflow-guarded. |
| ownership | Borrows scalar text; decimal rendering uses a fixed local array; no owned row/DOM is built. |
| failure | Field/record overflow or malformed UTF8 throws contextual Error. Window text validates UTF8 before field/total checks; physical text validates after them; preserve that precedence. |
| cost | O(fields+text bytes) scans and bounded decimal rendering, O(1) stack scratch; this is typed payload accounting, not exact encoded JSON/binary length. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
for(const auto scalar:values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the typed payload accounting model to each scalar without encoding a transport frame. |
| inputs / outputs | Visits all row values; adds1/int64/bool, text length,10/date or rendered decimal length to total. |
| invariants | Scalar field/total limits preserve window-versus-physical UTF8 error precedence; arithmetic guards precede addition. |
| ownership | Borrows text; fixed decimal char array only; no owning scalar copies. |
| failure | Public Error on bounds/UTF8; native view accessor errors remain uncaught. |
| cost | O(fields+text validation bytes), constant local scratch. Units differ from actual JSON/binary encoded bytes. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 91–100](../../../../../src/io/input_view.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> void event(const InputEventView& value,const CatalogView& catalog,const InputLimits& limits,RowIssue issue) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply physical-event envelope, schema, payload and source validation in fixed error order. |
| inputs / outputs | View/schema/limits plus matching RowIssue in; success returns void without advancing input progress. |
| invariants | Table range, positive sequence, set operation and column cap precede deferred row error, payload/table-name byte checks, then source identity. No contiguous-sequence proof here. |
| ownership | All backing borrowed; accepts no ownership/publication on success. |
| failure | Rejects through public Error; native/OOM failures are not swallowed or made sticky here. |
| cost | O(row fields+payload/source bytes) after O(1) envelope checks; row_issue may already have incurred its separate field scan. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 101–112](../../../../../src/io/input_view.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class CatalogView> void command(const WindowCommandView& value,const CatalogView& catalog,const InputLimits& limits,RowIssue issue) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply window-envelope and insertion-row validation without executing window semantics. |
| inputs / outputs | WindowCommandView/schema/limits/matching RowIssue in; success leaves runtime and progress unchanged. |
| invariants | Requires payload variant and positive sequence; only insert checks table/schema/payload, all commands check source. Label/timestamp/watermark semantics remain Controller gates. |
| ownership | Borrows inputs; withdraw/watermark inline data are only read. |
| failure | Contextual Error on malformed command/insert/source; no handler or rollback is needed because no state is published. |
| cost | Insert O(fields+payload/source bytes); noninsert O(source bytes); no row/DOM allocation on success. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
if(const auto* insert=std::get_if<WindowInsertView>(&value.command)) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate insertion-only window schema/payload constraints before source metadata. |
| inputs / outputs | WindowInsertView alternative in; checks table range, column cap, deferred row issue, payload and table-name bytes. |
| invariants | Withdraw/watermark bypass insertion schema validation; Controller owns their semantic legality. |
| ownership | Catalog/values borrowed; no allocated window label or runtime row. |
| failure | Any guard/row/UTF8 Error propagates without mutation. |
| cost | O(insert fields+payload bytes) scans; no total window-label/directory scan here. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 113–113](../../../../../src/io/input_view.cpp#L113); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L113-L113:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [docs/code_specs/files/src/io/input_view.cpp.md](input_view.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0016

[Lines 114–114](../../../../../src/io/input_view.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RowIssue row_issue(const Catalog& catalog,TableId table,storage::TupleValuesView values){return issue_for(catalog,table,values);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch ordinary catalog classification validation to the shared typed-view rules. |
| inputs / outputs | Returns RowIssue from table/values. |
| invariants | No independent catalog admission, sequence acceptance or offset publication occurs in this thin overload. |
| ownership | References borrow actual catalog/values. A passed TupleValuesView may retain an already-owned immutable tuple payload; no deep clone is made. |
| failure | No local catch. Preserve callee validation precedence and caller-owned backing lifetime. |
| cost | Shared classification O(fields); physical/window validation scans payload/source bytes as applicable, with fixed decimal scratch. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 115–115](../../../../../src/io/input_view.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RowIssue row_issue(const program::Catalog& catalog,TableId table,storage::TupleValuesView values){return issue_for(catalog,table,values);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch immutable program catalog classification validation to the shared typed-view rules. |
| inputs / outputs | Returns RowIssue from table/values. |
| invariants | No independent catalog admission, sequence acceptance or offset publication occurs in this thin overload. |
| ownership | References borrow actual catalog/values. A passed TupleValuesView may retain an already-owned immutable tuple payload; no deep clone is made. |
| failure | No local catch. Preserve callee validation precedence and caller-owned backing lifetime. |
| cost | Shared classification O(fields); physical/window validation scans payload/source bytes as applicable, with fixed decimal scratch. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 116–116](../../../../../src/io/input_view.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate(const InputEventView& value,const Catalog& catalog,const InputLimits& limits,RowIssue issue){event(value,catalog,limits,issue);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch ordinary catalog physical validation to the shared typed-view rules. |
| inputs / outputs | Returns void after envelope/payload/source checks, or propagates Error using the supplied matching RowIssue. |
| invariants | No independent catalog admission, sequence acceptance or offset publication occurs in this thin overload. |
| ownership | References borrow actual catalog/values. A passed TupleValuesView may retain an already-owned immutable tuple payload; no deep clone is made. |
| failure | No local catch. Preserve callee validation precedence and caller-owned backing lifetime. |
| cost | Shared classification O(fields); physical/window validation scans payload/source bytes as applicable, with fixed decimal scratch. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 117–117](../../../../../src/io/input_view.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate(const InputEventView& value,const program::Catalog& catalog,const InputLimits& limits,RowIssue issue){event(value,catalog,limits,issue);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch immutable program catalog physical validation to the shared typed-view rules. |
| inputs / outputs | Returns void after envelope/payload/source checks, or propagates Error using the supplied matching RowIssue. |
| invariants | No independent catalog admission, sequence acceptance or offset publication occurs in this thin overload. |
| ownership | References borrow actual catalog/values. A passed TupleValuesView may retain an already-owned immutable tuple payload; no deep clone is made. |
| failure | No local catch. Preserve callee validation precedence and caller-owned backing lifetime. |
| cost | Shared classification O(fields); physical/window validation scans payload/source bytes as applicable, with fixed decimal scratch. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 118–118](../../../../../src/io/input_view.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate(const WindowCommandView& value,const Catalog& catalog,const InputLimits& limits,RowIssue issue){command(value,catalog,limits,issue);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch ordinary catalog window validation to the shared typed-view rules. |
| inputs / outputs | Returns void after envelope/payload/source checks, or propagates Error using the supplied matching RowIssue. |
| invariants | No independent catalog admission, sequence acceptance or offset publication occurs in this thin overload. |
| ownership | References borrow actual catalog/values. A passed TupleValuesView may retain an already-owned immutable tuple payload; no deep clone is made. |
| failure | No local catch. Preserve callee validation precedence and caller-owned backing lifetime. |
| cost | Shared classification O(fields); physical/window validation scans payload/source bytes as applicable, with fixed decimal scratch. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 119–119](../../../../../src/io/input_view.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate(const WindowCommandView& value,const program::Catalog& catalog,const InputLimits& limits,RowIssue issue){command(value,catalog,limits,issue);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch immutable program catalog window validation to the shared typed-view rules. |
| inputs / outputs | Returns void after envelope/payload/source checks, or propagates Error using the supplied matching RowIssue. |
| invariants | No independent catalog admission, sequence acceptance or offset publication occurs in this thin overload. |
| ownership | References borrow actual catalog/values. A passed TupleValuesView may retain an already-owned immutable tuple payload; no deep clone is made. |
| failure | No local catch. Preserve callee validation precedence and caller-owned backing lifetime. |
| cost | Shared classification O(fields); physical/window validation scans payload/source bytes as applicable, with fixed decimal scratch. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [include/crown/io/input_view.hpp](../../../../../include/crown/io/input_view.hpp), [src/io/input_native.hpp](../../../../../src/io/input_native.hpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [include/crown/storage/tuple_values.hpp](../../../../../include/crown/storage/tuple_values.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 120–121](../../../../../src/io/input_view.cpp#L120); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L120-L121:sha256:f465f7cc6c13481b8f2cd898938d94c1b15e207817b287e9279de8eb499c3cc5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the private input_detail helper and its enclosing crown::io namespace after input view validation functions. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/io/input_view.cpp](../../../../../src/io/input_view.cpp), [docs/code_specs/files/src/io/input_view.cpp.md](input_view.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |
