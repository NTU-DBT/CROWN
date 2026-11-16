# `include/crown/io/input_view.hpp` — block usage map

[Source](../../../../../../include/crown/io/input_view.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `ee97a0e1dbbd143ffbd88dee5d809c4cae671ded09f8d1fcf58440b8ed64542a`. 39 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../../include/crown/io/input_view.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 11–16](../../../../../../include/crown/io/input_view.hpp#L11) | Type/record definition: struct SourcePositionView |  · [reviewed contract](#b0002) |
| [B0003 · 17–21](../../../../../../include/crown/io/input_view.hpp#L17) | Type/record definition: struct InputEventView |  · [reviewed contract](#b0003) |
| [B0004 · 22–22](../../../../../../include/crown/io/input_view.hpp#L22) | Type/record definition: struct WindowWithdraw |  · [reviewed contract](#b0004) |
| [B0005 · 23–23](../../../../../../include/crown/io/input_view.hpp#L23) | Type/record definition: struct AdvanceWatermark |  · [reviewed contract](#b0005) |
| [B0006 · 24–29](../../../../../../include/crown/io/input_view.hpp#L24) | Type/record definition: struct WindowInsertView |  · [reviewed contract](#b0006) |
| [B0007 · 30–37](../../../../../../include/crown/io/input_view.hpp#L30) | Type/record definition: struct WindowCommandView | source comment (unverified): // monostate preserves a malformed external variant until head validation; · [reviewed contract](#b0007) |
| [B0008 · 38–39](../../../../../../include/crown/io/input_view.hpp#L38) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0008) |

## B0001

[Lines 1–10](../../../../../../include/crown/io/input_view.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the io input_view public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0002

[Lines 11–16](../../../../../../include/crown/io/input_view.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourcePositionView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one source name with its fixed offset. |
| inputs / outputs | Nonowning string_view and uint64 offset; equality compares values. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::string_view source;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The borrowed upstream source-name bytes. |
| inputs / outputs | Stores/exposes the borrowed upstream source-name bytes. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::uint64_t offset=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The fixed upstream offset value. |
| inputs / outputs | Stores/exposes the fixed upstream offset value. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
bool operator==(const SourcePositionView&)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exact borrowed source-name/offset value equality. |
| inputs / outputs | Stores/exposes exact borrowed source-name/offset value equality. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
bool operator==(const SourcePosition&) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Value comparison to the ordinary owning source position. |
| inputs / outputs | Stores/exposes value comparison to the ordinary owning source position. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0003

[Lines 17–21](../../../../../../include/crown/io/input_view.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputEventView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one physical event without an ordinary row copy. |
| inputs / outputs | PhysicalUpdateView plus optional borrowed SourcePositionView. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
runtime::PhysicalUpdateView update;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The sequence/table/op/tuple-values view. |
| inputs / outputs | Stores/exposes the sequence/table/op/tuple-values view. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::optional<SourcePositionView> source_position;
  [[nodiscard]] static InputEventView borrow(const InputEvent&) noexcept;

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional borrowed upstream name/offset. |
| inputs / outputs | Stores/exposes the optional borrowed upstream name/offset. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
static InputEventView borrow(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact ordinary external physical event. |
| inputs / outputs | Borrows its Row through PhysicalUpdateView::borrow and its optional source-name text. |
| invariants | No validation, acceptance or native ownership import occurs; the original event must remain valid. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Declared noexcept; no string or row construction. |
| cost | Fixed view/optional construction, no payload traversal/allocation. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0004

[Lines 22–22](../../../../../../include/crown/io/input_view.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowWithdraw {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one window label to withdraw. |
| inputs / outputs | Inline label only; actual label existence/policy is checked by window admission. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0005

[Lines 23–23](../../../../../../include/crown/io/input_view.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AdvanceWatermark {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one requested operational event-time watermark. |
| inputs / outputs | Inline watermark; expansion/monotonicity is checked by the window/session owner. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0006

[Lines 24–29](../../../../../../include/crown/io/input_view.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowInsertView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one operational-window insertion row. |
| inputs / outputs | Label/table/tuple view/event timestamp; no SQL timestamp conversion. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::uint64_t label=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The insertion label value. |
| inputs / outputs | Stores/exposes the insertion label value. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
TableId table{0};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The physical source table ID. |
| inputs / outputs | Stores/exposes the physical source table ID. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
storage::TupleValuesView values;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The full row view, potentially sharing an already retained tuple payload. |
| inputs / outputs | Stores/exposes the full row view, potentially sharing an already retained tuple payload. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::uint64_t timestamp=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The independent adapter event-time value. |
| inputs / outputs | Stores/exposes the independent adapter event-time value. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0007

[Lines 30–37](../../../../../../include/crown/io/input_view.hpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowCommandView {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | View one ordered external window command. |
| inputs / outputs | Sequence, monostate/insert/withdraw/watermark payload and optional borrowed upstream position. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::uint64_t sequence=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The requested window command sequence. |
| inputs / outputs | Stores/exposes the requested window command sequence. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::variant<std::monostate,WindowInsertView,WindowWithdraw,AdvanceWatermark> command;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The exact payload; monostate preserves malformed/valueless external commands until head validation. |
| inputs / outputs | Stores/exposes the exact payload; monostate preserves malformed/valueless external commands until head validation. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
std::optional<SourcePositionView> source_position;
  [[nodiscard]] static WindowCommandView borrow(const WindowCommand&) noexcept;

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional borrowed upstream position. |
| inputs / outputs | Stores/exposes the optional borrowed upstream position. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

```text
static WindowCommandView borrow(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an external command without normalizing away malformed state. |
| inputs / outputs | Copies fixed payload fields/views when active; leaves monostate if no recognized active alternative. |
| invariants | No invalid command is silently replaced by a valid watermark or insertion; validation occurs at the owned source head. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Declared noexcept; scalar/view assignments do not allocate ordinary rows/text. |
| cost | Fixed alternative checks and view construction, no payload copy. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |

## B0008

[Lines 38–39](../../../../../../include/crown/io/input_view.hpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using InputItemView=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the physical/window head-view union. |
| inputs / outputs | InputEventView or WindowCommandView, used synchronously by native source/session adapters. |
| invariants | Mutable data alone never authorizes source acceptance, native plan execution, proof, output acknowledgment or durable publication. |
| ownership | Explicit borrow factories keep no caller Row/source-string owner. A directly supplied TupleValuesView may already retain an immutable tuple payload, but its string/source subviews still need that backing to survive. Native admission imports independent owned state before returning. |
| failure | Declaration only; source head validation handles mode/envelope errors. |
| cost | Fixed variant descriptor with actual existing tuple-handle copy/release costs. |
| Design | [include/crown/io/input_view.hpp](../../../../../../include/crown/io/input_view.hpp), [src/io/input_view.cpp](../../../../../../src/io/input_view.cpp), [src/io/batch.cpp](../../../../../../src/io/batch.cpp), [docs/batches_windows.md](../../../../../batches_windows.md) |
