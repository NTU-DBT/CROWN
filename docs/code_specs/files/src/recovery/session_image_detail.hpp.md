# `src/recovery/session_image_detail.hpp` — block usage map

[Source](../../../../../src/recovery/session_image_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `24cd3330638dba675e8088e4f0163d9eab8b4ae7207115739e19e7456c75777d`. 36 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/recovery/session_image_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Only the native codec can adopt these freshly funded options. No ordinary · [reviewed contract](#b0001) |
| [B0002 · 8–18](../../../../../src/recovery/session_image_detail.hpp#L8) | Type/record definition: struct SessionImageAccess | returns io::AccountedInputOptions(account,std::move(value)); result; source comment (unverified): // Only the native codec can adopt these freshly funded options. No ordinary · [reviewed contract](#b0002) |
| [B0003 · 19–26](../../../../../src/recovery/session_image_detail.hpp#L19) | Type/record definition: struct ValidatedSessionImage | source comment (unverified): // Mutable internal call state, not a capability. Keep validated bytes/limits · [reviewed contract](#b0003) |
| [B0004 · 27–32](../../../../../src/recovery/session_image_detail.hpp#L27) | Type/record definition: struct DecodedSessionImage | source comment (unverified): // Borrows immutable input only during restore. Native source/window rows and · [reviewed contract](#b0004) |
| [B0005 · 33–36](../../../../../src/recovery/session_image_detail.hpp#L33) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::recovery::detail · [reviewed contract](#b0005) |

## B0001

[Lines 1–7](../../../../../src/recovery/session_image_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/recovery/session_image.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the private split between pure image validation and receiving materialization. |
| inputs / outputs | Session image/native checkpoint types and account-funded option access. |
| invariants | No public InputOptions/WindowOptions graph is introduced in binary restore; native codec creates original receiving-account values directly. These are local ownership rules. |
| ownership | No static owner or hidden memory account. |
| failure | No validation occurs merely by including this internal header. |
| cost | Compile-time boundary; actual metadata/native costs remain explicit. |
| Design | [docs/checkpoints.md § Complete binary session API](../../../../checkpoints.md), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/runtime/session.cpp § QuerySession::restore_image](../../../../../src/runtime/session.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0002

[Lines 8–18](../../../../../src/recovery/session_image_detail.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionImageAccess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict adoption of freshly decoded native option structures to the internal codec path. |
| inputs / outputs | Friend access to private AccountedInputOptions and AccountedWindowOptions construction. |
| invariants | The helper is private-header plumbing, not an unforgeable runtime capability. Callers must supply already validated, correctly funded values; subsequent native controllers still admit semantics. |
| ownership | Transfers native option owners without exporting ordinary DTO graphs. |
| failure | Factory failures follow each owning constructor; no file/runtime publication occurs here. |
| cost | No generic conversion framework or second receiving account. |
| Design | [docs/checkpoints.md § Complete binary session API](../../../../checkpoints.md), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/runtime/session.cpp § QuerySession::restore_image](../../../../../src/runtime/session.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

```text
static io::AccountedInputOptions input(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move already receiver-funded input metadata into its immutable native shared owner. |
| inputs / outputs | Explicit account and AccountedInputOptions::Values rvalue in; AccountedInputOptions out. |
| invariants | Actual codec builds Values/map/text with the same account before calling. This helper does not independently check allocator equality or text/schema semantics. |
| ownership | Private constructor allocate_shared funds the control/Values object under account and moves nested nodes/text; no public InputOptions copy. |
| failure | Receiving allocation failure propagates; prior decoded Values remain RAII-owned during unwind. No live session has been installed. |
| cost | One account-funded shared control/value allocation plus member moves; nested map/text allocations already occurred during decoding. |
| Design | [docs/checkpoints.md § Complete binary session API](../../../../checkpoints.md), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/runtime/session.cpp § QuerySession::restore_image](../../../../../src/runtime/session.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/io/input_options.cpp § AccountedInputOptions::AccountedInputOptions](../../../../../src/io/input_options.cpp) |

```text
static runtime::AccountedWindowOptions window(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble native window options around an already funded table-id owner. |
| inputs / outputs | WindowTables by value, width/fifo/labels/bytes/work scalars in. |
| invariants | Codec has checked scalar encodings and funded WindowTables::copy_of; helper neither clones a DTO nor grants native window validity by itself. |
| ownership | Moves managed_tables into result and copies scalar policies; shared table storage retains its original account. |
| failure | Current body performs no throwing allocation/validation; prior table creation can fail before this call. Signature is not declared noexcept. |
| cost | Fixed assignments/shared-owner transfer; no new table buffer allocation in this body. |
| Design | [docs/checkpoints.md § Complete binary session API](../../../../checkpoints.md), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/runtime/session.cpp § QuerySession::restore_image](../../../../../src/runtime/session.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0003

[Lines 19–26](../../../../../src/recovery/session_image_detail.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ValidatedSessionImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one internal validation result and the exact borrowed bytes/limits needed by materialization. |
| inputs / outputs | Byte view, fixed InspectedSessionImage, copied state_limits and envelope limits. |
| invariants | This mutable aggregate has no private constructor/seal. Actual callers obtain it from validate_session_image, keep bytes immutable and do not edit metadata/limits; materialize does not rehash the envelope or inner runtime image. |
| ownership | Owns fixed metadata/limits only; bytes borrows external file/image storage through native restore. |
| failure | Forging/editing it violates the internal call contract; public inspection metadata is not a substitute for this call sequence. |
| cost | Fixed copying; no retained decoded graph or account. |
| Design | [docs/checkpoints.md § Complete binary session API](../../../../checkpoints.md), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/runtime/session.cpp § QuerySession::restore_image](../../../../../src/runtime/session.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0004

[Lines 27–32](../../../../../src/recovery/session_image_detail.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DecodedSessionImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate receiver-owned source/window checkpoint state from a temporary borrowed runtime blob. |
| inputs / outputs | SessionCheckpoint state plus runtime_bytes view. |
| invariants | materialize fills state native metadata and runtime manifest, while runtime_image.bytes remains empty; restore_funded receives runtime_bytes explicitly and performs actual native admission. |
| ownership | Native options/rows/maps own receiver-funded bytes; runtime_bytes aliases the unchanged outer image only until synchronous restore completes. |
| failure | Partial materialization failure destroys owned state; callers retain input buffer through restore. No partly restored session escapes. |
| cost | Owned metadata/row allocations plus one borrowed runtime span, avoiding a duplicate runtime-image buffer. |
| Design | [docs/checkpoints.md § Complete binary session API](../../../../checkpoints.md), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/runtime/session.cpp § QuerySession::restore_image](../../../../../src/runtime/session.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0005

[Lines 33–36](../../../../../src/recovery/session_image_detail.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] ValidatedSessionImage validate_session_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare complete allocation-free envelope and nested-runtime validation before materialization. |
| inputs / outputs | Immutable bytes, native limits and image limits in; internal validation carrier out. |
| invariants | Checks full envelope SHA/structure/metadata, nested runtime inspection and consistency; reserves a conservative second-read work amount. Native program/source/window acceptance still follows. |
| ownership | Output borrows bytes and owns only fixed metadata/limits. |
| failure | ImageFailure before decoded output graph; caller must keep unchanged bytes and exact returned carrier for next phase. |
| cost | Envelope scans/SHA+nested image work+reserved second parse; fixed inspection allocations only (no heap graph). |
| Design | [docs/checkpoints.md § Complete binary session API](../../../../checkpoints.md), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/runtime/session.cpp § QuerySession::restore_image](../../../../../src/runtime/session.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

```text
[[nodiscard]] DecodedSessionImage materialize_session_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare receiving-account assembly using an unchanged prior validation. |
| inputs / outputs | Account and ValidatedSessionImage in; owning native metadata plus borrowed runtime view out. |
| invariants | Trusted internal call order is required: this routine reparses structural payload but does not repeat envelope/inner checksum inspection. Runtime restore separately checks its actual binding/schema/build. |
| ownership | All new native metadata uses supplied account; borrowed runtime bytes live through final restore. |
| failure | Account or pass-two validation failure releases private state. It does not publish a session, mutate input or mint another work/account grant. |
| cost | One materialization pass with metadata/row copying and option-control allocations; no extra whole runtime buffer. |
| Design | [docs/checkpoints.md § Complete binary session API](../../../../checkpoints.md), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/runtime/session.cpp § QuerySession::restore_image](../../../../../src/runtime/session.cpp), [include/crown/io/input_options.hpp](../../../../../include/crown/io/input_options.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |
