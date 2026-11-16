# `src/io/checkpoint_detail.hpp` — block usage map

[Source](../../../../../src/io/checkpoint_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `a5bc5301a8d7cb65672487d5082e1c2893bbd3bf5d7dedd1012aa93c90c56835`. 64 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/io/checkpoint_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–11](../../../../../src/io/checkpoint_detail.hpp#L9) | Callable definition: inline void require(bool value,recovery::ImageFault fault=recovery::ImageFault::corrupt) | calls recovery::ImageFailure; guard inline void require(bool value,recovery::ImageFault fault=recovery::ImageFault::corrupt) { · [reviewed contract](#b0002) |
| [B0003 · 12–34](../../../../../src/io/checkpoint_detail.hpp#L12) | Type/record definition: struct Budget | guard require(used&lt;=limits.work && value&lt;=limits.work-used,recovery::ImageFault::work);used+=value;; 2 loop sites · [reviewed contract](#b0003) |
| [B0004 · 35–38](../../../../../src/io/checkpoint_detail.hpp#L35) | Explanatory comments or spacing. | source comment (unverified): // Conservative replay source-validation units, charged before scalar text, · [reviewed contract](#b0004) |
| [B0005 · 39–59](../../../../../src/io/checkpoint_detail.hpp#L39) | Callable definition: inline void replay_input(Budget& budget,const InputItemView& item,const InputLimits& limits,const InputPositions& positions) | calls require, size, charge, multiple; guard require(positions.size()&lt;=budget.limits.positions && positions.size()&lt;=limits.sources,recovery::Ima…; returns value.source_position; growth insert; 1 loop sites; source comment (unverified): // Conservative replay source-validation units, charged before scalar text, · [reviewed contract](#b0005) |
| [B0006 · 60–63](../../../../../src/io/checkpoint_detail.hpp#L60) | Callable definition: inline std::array&lt;char,64&gt; hash(std::string_view value) | calls require, size, std::copy, begin; guard require(value.size()==64,recovery::ImageFault::binding);std::array&lt;char,64&gt; result{};; returns result · [reviewed contract](#b0006) |
| [B0007 · 64–64](../../../../../src/io/checkpoint_detail.hpp#L64) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io::checkpoint_detail · [reviewed contract](#b0007) |

## B0001

[Lines 1–8](../../../../../src/io/checkpoint_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share finite checkpoint source-work accounting and replay precharges without rescanning the full accepted directory per row. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 9–11](../../../../../src/io/checkpoint_detail.hpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void require(bool value,recovery::ImageFault fault=recovery::ImageFault::corrupt) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a local checkpoint/source condition with a fixed typed failure. |
| inputs / outputs | Boolean and optional ImageFault(default corrupt) in; returns on true, otherwise throws ImageFailure. |
| invariants | Typed failure preserves work/limit/binding/corrupt category rather than constructing generic runtime diagnostics. |
| ownership | Inline error payload/static what text; no caller backing retained or native publication. |
| failure | No dynamic message concatenation, but throwing/unwinding has normal C++ ABI exception-storage cost; no catch here. |
| cost | O(1) successful guard; exceptional unwind costs depend on caller-owned partial objects. |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 12–34](../../../../../src/io/checkpoint_detail.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Budget {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track a cumulative finite source-validation budget for one admitted checkpoint/replay operation. |
| inputs / outputs | SourceStateLimits copied inline with used=0; charge/positions/options mutate local used counter. |
| invariants | Charges guard used&lt;=limit and amount&lt;=limit-used before addition. These are engineering work units, not measured instructions or a paper theorem; DTO limits grant no native/durable authority. |
| ownership | Owns fixed limits/counter; borrows progress/options only during traversal; no vector/map allocation. |
| failure | Typed ImageFailure on budget/domain guard; UTF8 helper can throw contextual Error. Counters retain successful earlier charges if later validation fails. |
| cost | Fixed counter storage; positions scans directory/names, options scans token map/names; repeat failed calls still consume CPU even when budget object is discarded. |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
SourceStateLimits limits;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the source admission work/component ceilings into the local tracker. |
| inputs / outputs | SourceStateLimits contains work, positions and csv_fields; no ownership of actual sources. |
| invariants | Only relevant helper checks enforce each ceiling; options() merely charges its described work. |
| ownership | Inline limits value. |
| failure | Copy has no failure or allocation. |
| cost | O(1). |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
std::uint64_t used=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count successfully precharged source work without wrapping. |
| inputs / outputs | uint64_t used starts0 and increases only after checked charge. |
| invariants | Failure does not roll back prior successful charges in this Budget object; callers own operation retry lifetime. |
| ownership | Inline scalar, no resource owner. |
| failure | Increment happens only after require accepts subtraction-safe bound. |
| cost | O(1) counter access/update. |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
void charge(std::uint64_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve finite cumulative source-work units before the associated scan/copy. |
| inputs / outputs | Requested uint64_t units in; updates used or throws ImageFault::work. |
| invariants | Short-circuit used&lt;=limits.work prevents subtraction underflow; successful addition cannot exceed ceiling/wrap. |
| ownership | Only mutates local Budget scalar, no runtime/source acceptance. |
| failure | Failed charge leaves used unchanged for that charge; prior charges remain. |
| cost | O(1), no dynamic diagnostic text/allocation on success. |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
void positions(const AccountedInputProgress& progress,const InputLimits& input) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and charge the entire accepted source-position directory at a checkpoint barrier. |
| inputs / outputs | AccountedInputProgress plus InputLimits in; bounds source count and charges one baseline, one per entry and every source-name byte. |
| invariants | Each name must be nonempty, within source_bytes, NUL-free and UTF8; offsets are read but not revalidated as monotone history. No directory clone or acceptance here. |
| ownership | Progress/map/name backing borrowed; iterator traversal does not allocate source nodes. |
| failure | Count violation limit; budget violation work; name shape corrupt through require; UTF8 retains its actual Error category. Partial local used counter remains on failure. |
| cost | O(N+source bytes) scans including NUL+UTF8; charged units1+N+sum name bytes, not exact instruction/scan count. |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
void options(const AccountedInputOptions::Values& options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Account the stored options traversal/copy dimensions used in checkpoint admission. |
| inputs / outputs | AccountedInputOptions::Values in; charges1+relation-token count+all token-name bytes+optional source/null-token bytes. |
| invariants | Does not itself validate format/options semantics or resolve relation table IDs; actual owner admission/fingerprint checks remain necessary. |
| ownership | Options/token names borrowed; no ordinary shadow map/string created. |
| failure | Budget exhaustion throws typed work failure after prior successful charges; no mutations outside Budget. |
| cost | O(token entries) iteration and O(1) size reads per owned text; charge includes text bytes even though this helper does not scan each character. |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 35–38](../../../../../src/io/checkpoint_detail.hpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L38:sha256:b739194ecba726dc617d560ce20415064a90f8fcb8c017689eecadf80a6adf2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Conservative replay source-validation units, charged before scalar text, identifier validation/copy and bounded red-black source-directory searches. Accepted progress was validated at checkpoint admission; never rescan its complete map for every replayed row. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/checkpoint_detail.hpp lines 33-40; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [docs/code_specs/files/src/io/checkpoint_detail.hpp.md](checkpoint_detail.hpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0005

[Lines 39–59](../../../../../src/io/checkpoint_detail.hpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void replay_input(Budget& budget,const InputItemView& item,const InputLimits& limits,const InputPositions& positions) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Precharge conservative incremental source replay validation without rewalking all accepted positions. |
| inputs / outputs | Budget/item/input limits/accepted InputPositions in; charges row fields/text/decimal and a source-name/tree-depth envelope, checking relevant count ceilings. |
| invariants | Accepted positions already fully admitted. Does not itself validate row types/UTF8/sequence/order; callers run native validators and owner ordering afterward. InputItemView variant must be a valid physical or window alternative. |
| ownership | Borrows values/source/map; no copied row, map or source text; TupleValuesView assignment can retain an existing immutable tuple owner only. |
| failure | Checked multiply/budget overflow throws work; row/source/count limit throws limit; invalid variant can propagate bad_variant_access. No source/runtime publication. |
| cost | Charges1+8 per row field+4 per string byte+82 per decimal; optional source adds L*(12+8*bit_width(N)), with O(log N) contains only at configured position ceiling. Actual row iteration O(F), source-name lookup byte comparisons as needed. |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
const auto multiple=[&](std::uint64_t count,std::uint64_t width){require(width==0 || count<=UINT64_MAX/width,recovery::ImageFault::work);budget.charge(count*width);};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard multiplication before reserving conservative replay units. |
| inputs / outputs | count/width passed to synchronous lambda; requires count&lt;=UINT64_MAX/width unless width0, then charges product. |
| invariants | No multiplication wrap; budget.charge additionally bounds cumulative used. |
| ownership | Captures local Budget by reference; no backing retained beyond call. |
| failure | Overflow or cumulative exhaustion throws ImageFault::work before product charge. |
| cost | O(1) arithmetic, no dynamic storage. |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
if(row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Precharge only row-bearing physical events or window insertions. |
| inputs / outputs | Row-bearing item contributes borrowed TupleValuesView; each field charges8 plus text/decimal conservative addenda. |
| invariants | Noninsert window commands skip row work; field count checked before iteration. Does not inspect accepted directory for every cell. |
| ownership | Borrowed/retained existing view; no new native or ordinary row allocation. |
| failure | Column cap/work/accessor failures abort before caller validation/acceptance. |
| cost | Actual O(fields) iteration plus scalar getter/inline decimal work; text charge reads size only, later validator/copy performs text scans. |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
if(position) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve source-name validation/copy/search work and enforce admission of a new source at capacity. |
| inputs / outputs | Optional SourcePositionView in; source length bound and computed red-black search envelope charged. |
| invariants | At positions.size()==budget.limits.positions requires name already present. Separate input.sources count check and later source owner enforce their own new-source bound; offset order checked later. |
| ownership | Borrows map and source-name bytes; lookup creates no key. |
| failure | Length/count/work failures are typed; accepted directory and progress unchanged. |
| cost | O(1) size/bit-width arithmetic plus O(log N) lexicographic contains at capacity; no O(N) map scan. |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 60–63](../../../../../src/io/checkpoint_detail.hpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::array<char,64> hash(std::string_view value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a fixed-size64-byte catalog hash label into inline checkpoint storage. |
| inputs / outputs | string_view in; array&lt;char,64&gt; out after exact length check. |
| invariants | Checks length only, not hex alphabet, actual hash recomputation or catalog binding. Caller compares to authoritative computed catalog digest separately. |
| ownership | Copies64 bytes; result owns inline array and retains no source string. |
| failure | Wrong length throws ImageFault::binding; no dynamic message. |
| cost | O(64) fixed copy/stack storage, no payload allocation on success. |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/ingest_text.cpp](../../../../../src/io/ingest_text.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 64–64](../../../../../src/io/checkpoint_detail.hpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L64:sha256:5ddf9cb284bc183ed9739feb2a8f838bdc51677ce642e7973e0fcd051c6125d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io::checkpoint_detail at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [docs/code_specs/files/src/io/checkpoint_detail.hpp.md](checkpoint_detail.hpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |
