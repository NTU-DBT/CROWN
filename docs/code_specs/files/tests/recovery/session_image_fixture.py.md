# `tests/recovery/session_image_fixture.py` — block usage map

[Source](../../../../../tests/recovery/session_image_fixture.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `dd8d15e66cf358767a10327831e1780e78df77d353f6f648a3427836af38e3d2`. 152 lines partitioned into 25 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/recovery/session_image_fixture.py#L1) | Imports dependencies; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 18–19](../../../../../tests/recovery/session_image_fixture.py#L18) | Callable definition: def u8(value: int) -&gt; bytes: | calls pack; returns struct.pack("&lt;B", value) · [reviewed contract](#b0002) |
| [B0003 · 20–21](../../../../../tests/recovery/session_image_fixture.py#L20) | Explanatory comments or spacing. |  |
| [B0004 · 22–23](../../../../../tests/recovery/session_image_fixture.py#L22) | Callable definition: def u16(value: int) -&gt; bytes: | calls pack; returns struct.pack("&lt;H", value) · [reviewed contract](#b0004) |
| [B0005 · 24–25](../../../../../tests/recovery/session_image_fixture.py#L24) | Explanatory comments or spacing. |  |
| [B0006 · 26–27](../../../../../tests/recovery/session_image_fixture.py#L26) | Callable definition: def u32(value: int) -&gt; bytes: | calls pack; returns struct.pack("&lt;I", value) · [reviewed contract](#b0006) |
| [B0007 · 28–29](../../../../../tests/recovery/session_image_fixture.py#L28) | Explanatory comments or spacing. |  |
| [B0008 · 30–31](../../../../../tests/recovery/session_image_fixture.py#L30) | Callable definition: def u64(value: int) -&gt; bytes: | calls pack; returns struct.pack("&lt;Q", value) · [reviewed contract](#b0008) |
| [B0009 · 32–33](../../../../../tests/recovery/session_image_fixture.py#L32) | Explanatory comments or spacing. |  |
| [B0010 · 34–35](../../../../../tests/recovery/session_image_fixture.py#L34) | Callable definition: def optional_u64(value: int \| None) -&gt; bytes: | calls u8, u64; returns u8(value is not None) + (u64(value) if value is not None else b"") · [reviewed contract](#b0010) |
| [B0011 · 36–37](../../../../../tests/recovery/session_image_fixture.py#L36) | Explanatory comments or spacing. |  |
| [B0012 · 38–39](../../../../../tests/recovery/session_image_fixture.py#L38) | Callable definition: def text_u64(value: bytes) -&gt; bytes: | calls u64, len; returns u64(len(value)) + value · [reviewed contract](#b0012) |
| [B0013 · 40–41](../../../../../tests/recovery/session_image_fixture.py#L40) | Explanatory comments or spacing. |  |
| [B0014 · 42–43](../../../../../tests/recovery/session_image_fixture.py#L42) | Callable definition: def scalar(tag: int, payload: bytes = b"") -&gt; bytes: | calls u8; returns u8(tag) + payload · [reviewed contract](#b0014) |
| [B0015 · 44–45](../../../../../tests/recovery/session_image_fixture.py#L44) | Explanatory comments or spacing. |  |
| [B0016 · 46–47](../../../../../tests/recovery/session_image_fixture.py#L46) | Callable definition: def row(values: list\[bytes\]) -&gt; bytes: | calls u64, len, join; returns u64(len(values)) + b"".join(values) · [reviewed contract](#b0016) |
| [B0017 · 48–49](../../../../../tests/recovery/session_image_fixture.py#L48) | Explanatory comments or spacing. |  |
| [B0018 · 50–54](../../../../../tests/recovery/session_image_fixture.py#L50) | Callable definition: def frame(magic: bytes, payload: bytes) -&gt; bytes: | calls len, u16, u64, sha256; returns header + payload · [reviewed contract](#b0018) |
| [B0019 · 55–72](../../../../../tests/recovery/session_image_fixture.py#L55) | declares values/defaults or compile-time conditions. | source comment (unverified): # runtime/checkpoint_policy.hpp field order. Optional values are represented · [reviewed contract](#b0019) |
| [B0020 · 73–97](../../../../../tests/recovery/session_image_fixture.py#L73) | Callable definition: def runtime_image() -&gt; bytes: | calls scalar, u64, text_u64, u8; returns frame(b"CROWNRI1", bytes(payload)); 1 loop sites; source comment (unverified): # Exact native scalar tags from recovery/binary_detail.hpp: · [reviewed contract](#b0020) |
| [B0021 · 98–99](../../../../../tests/recovery/session_image_fixture.py#L98) | Explanatory comments or spacing. |  |
| [B0022 · 100–138](../../../../../tests/recovery/session_image_fixture.py#L100) | Callable definition: def session_image(inner: bytes) -&gt; bytes: | calls bytearray, u32, u8, u64; returns frame(b"CROWNSI1", bytes(body)); growth insert; 1 loop sites; source comment (unverified): # native SessionCheckpoint version · [reviewed contract](#b0022) |
| [B0023 · 139–140](../../../../../tests/recovery/session_image_fixture.py#L139) | Explanatory comments or spacing. |  |
| [B0024 · 141–148](../../../../../tests/recovery/session_image_fixture.py#L141) | Callable definition: def main() -&gt; None: | calls runtime_image, session_image, Path, with_name · [reviewed contract](#b0024) |
| [B0025 · 149–152](../../../../../tests/recovery/session_image_fixture.py#L149) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0025) |

## B0001

[Lines 1–17](../../../../../tests/recovery/session_image_fixture.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:c801ff36eb64eab332dcf06a97268823b6a27e27dcb417d765d094d8e98344dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for session_image_fixture.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–19](../../../../../tests/recovery/session_image_fixture.py#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def u8(value: int) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one unsigned 8-bit little-endian fixture word. |
| inputs / outputs | Returns 1 new byte(s) for an integer/indexable value in 0..2^8-1. |
| invariants | No masking or semantic tag validation occurs; range is enforced by struct.pack. |
| ownership | Input integer is borrowed/immutable; returned bytes own their encoding. |
| failure | Out-of-range or non-indexable input raises struct.error/TypeError; no file is touched. |
| cost | Fixed 1-byte output; integer conversion/range checking depends on operand representation. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0004

[Lines 22–23](../../../../../tests/recovery/session_image_fixture.py#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def u16(value: int) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one unsigned 16-bit little-endian fixture word. |
| inputs / outputs | Returns 2 new byte(s) for an integer/indexable value in 0..2^16-1. |
| invariants | No masking or semantic tag validation occurs; range is enforced by struct.pack. |
| ownership | Input integer is borrowed/immutable; returned bytes own their encoding. |
| failure | Out-of-range or non-indexable input raises struct.error/TypeError; no file is touched. |
| cost | Fixed 2-byte output; integer conversion/range checking depends on operand representation. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0006

[Lines 26–27](../../../../../tests/recovery/session_image_fixture.py#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def u32(value: int) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one unsigned 32-bit little-endian fixture word. |
| inputs / outputs | Returns 4 new byte(s) for an integer/indexable value in 0..2^32-1. |
| invariants | No masking or semantic tag validation occurs; range is enforced by struct.pack. |
| ownership | Input integer is borrowed/immutable; returned bytes own their encoding. |
| failure | Out-of-range or non-indexable input raises struct.error/TypeError; no file is touched. |
| cost | Fixed 4-byte output; integer conversion/range checking depends on operand representation. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0008

[Lines 30–31](../../../../../tests/recovery/session_image_fixture.py#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def u64(value: int) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one unsigned 64-bit little-endian fixture word. |
| inputs / outputs | Returns 8 new byte(s) for an integer/indexable value in 0..2^64-1. |
| invariants | No masking or semantic tag validation occurs; range is enforced by struct.pack. |
| ownership | Input integer is borrowed/immutable; returned bytes own their encoding. |
| failure | Out-of-range or non-indexable input raises struct.error/TypeError; no file is touched. |
| cost | Fixed 8-byte output; integer conversion/range checking depends on operand representation. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0010

[Lines 34–35](../../../../../tests/recovery/session_image_fixture.py#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def optional_u64(value: int | None) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a nullable fixture counter with a separate presence byte. |
| inputs / outputs | None emits flag 0 only; any other value emits flag 1 plus u64 value. |
| invariants | Uses identity with None rather than truthiness, so zero is a present value. It is not the policy tuple’s absent-value-zero-word convention. |
| ownership | Returns new bytes; caller scalar is unchanged. |
| failure | Non-indexable/out-of-range present values propagate packing errors. |
| cost | One-byte absent or nine-byte present output plus integer conversion. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0012

[Lines 38–39](../../../../../tests/recovery/session_image_fixture.py#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def text_u64(value: bytes) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prefix opaque fixture bytes by their unsigned 64-bit byte length. |
| inputs / outputs | Returns u64(len(value)) followed by the exact value bytes, including NUL/non-UTF-8. |
| invariants | No text decoding or string-domain validation occurs. |
| ownership | Copies borrowed bytes into a new independent encoding. |
| failure | Non-bytes concatenation or excessive length errors propagate. |
| cost | Linear payload copy plus fixed length word. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0014

[Lines 42–43](../../../../../tests/recovery/session_image_fixture.py#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def scalar(tag: int, payload: bytes = b"") -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Join a fixture scalar tag to an already encoded payload. |
| inputs / outputs | Returns u8(tag)+payload; empty payload is allowed by the assembler. |
| invariants | Tag range is only u8; tag/payload compatibility and scalar canonicality are deliberately caller responsibilities. |
| ownership | New bytes copy the immutable payload; caller state is unchanged. |
| failure | Tag packing and payload type errors propagate. |
| cost | Linear in payload length plus one byte. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0016

[Lines 46–47](../../../../../tests/recovery/session_image_fixture.py#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def row(values: list[bytes]) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble a native row from independently encoded scalar byte strings. |
| inputs / outputs | Returns u64 scalar count plus the joined value encodings, including count 0 for an empty row. |
| invariants | It does not decode or compare scalar tags; each list element must already be a complete encoding. |
| ownership | Owns the joined row; input list and bytes are borrowed. |
| failure | Join/type or count packing errors propagate. |
| cost | Visits every element and copies the complete scalar payload. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0018

[Lines 50–54](../../../../../tests/recovery/session_image_fixture.py#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def frame(magic: bytes, payload: bytes) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Frame a runtime/session payload with its version 1 length and body digest. |
| inputs / outputs | Returns magic 8/u16 version 1/u16 flags 0/u64 length/64-byte SHA text followed by payload. |
| invariants | assert requires magic length 8 and header 84; this image format has no separate prefix checksum, unlike WAL frames. Assertions disappear under -O. |
| ownership | Creates header/digest/result bytes and borrows payload. |
| failure | Enabled assertion, numeric packing or buffer errors propagate. |
| cost | Hashes/copies all payload bytes plus fixed 84-byte header construction. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0019

[Lines 55–72](../../../../../tests/recovery/session_image_fixture.py#L55); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
assert len(DEFAULT_DELTA_POLICY) == 26
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the literal delta-policy fixture length during module initialization. |
| inputs / outputs | Asserts len(DEFAULT_DELTA_POLICY)==26 before the separately guarded session-image writer is called. |
| invariants | The fixed module-load length assertion runs when Python assertions are enabled. It does not encode or validate a native checkpoint. |
| ownership | The tuple/list constant and assertion live in the Python process; no file is opened by this span. |
| failure | A changed length raises AssertionError when assertions are enabled; no local catch. |
| cost | One fixed-length comparison. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [tests/recovery/session-image-v1.hex](../../../../../tests/recovery/session-image-v1.hex), tests/recovery/session_image_fixture.py:55-72 |

## B0020

[Lines 73–97](../../../../../tests/recovery/session_image_fixture.py#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def runtime_image() -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a codec-only native runtime golden with all scalar tags and empty-row/table cases. |
| inputs / outputs | Builds synthetic hashes/catalog 7/epoch 99/default 26-word policy, table 0 rich and empty rows, table 1 empty, framed as CROWNRI1. |
| invariants | Binding is synthetic codec data, not an admitted Program; raw scalar bytes include NUL/0xff. |
| ownership | Uses a private bytearray and new scalar/row bytes; freezes the payload into independent frame bytes. |
| failure | Constant packing/framing errors propagate; the function writes no fixture file. |
| cost | Fixed fixture assembly with repeated bytearray extension, payload hashing and final copy. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0022

[Lines 100–138](../../../../../tests/recovery/session_image_fixture.py#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def session_image(inner: bytes) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap an arbitrary inner native image in the specified stopped typed-session golden. |
| inputs / outputs | Writes version/control/options/default limits, accepted progress 99 with alpha/z offsets, absent window and length-prefixed inner bytes, then CROWNSI1 framing. |
| invariants | No inner validation occurs; constants declare stopped typed_physical source alternative 2 and independent captured options. |
| ownership | Copies inner bytes into a private bytearray/result; no caller object or native runtime is retained. |
| failure | Packing/framing/type errors propagate; no file is changed here. |
| cost | Linear in inner image size plus fixed session envelope/options, including full body hash/copies. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0024

[Lines 141–148](../../../../../tests/recovery/session_image_fixture.py#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Overwrite the independent session-image hex golden and report its component hashes. |
| inputs / outputs | Builds inner and outer images, writes session-image-v1.hex alongside this module and prints sizes/SHA/path. |
| invariants | Uses Python struct/hashlib only and synthetic codec bindings; no native-state acceptance is asserted by file creation. |
| ownership | Owns both images and directly writes the output Path; no transactional temp file or rollback is used. |
| failure | File/encoding/packing/assertion errors propagate to process failure. |
| cost | Builds/hashes both images, expands outer bytes to hex and writes the full fixture. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [docs/session-journal.md](../../../../session-journal.md) |

## B0025

[Lines 149–152](../../../../../tests/recovery/session_image_fixture.py#L149); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Overwrite the independent session-image hex golden and report its component hashes. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | No presentation catch is added here: main/fixture failures and SystemExit propagate through the interpreter. This block supplies no extra retry or rollback. Delegated main replaces its persistent golden; the wrapper does not roll that file back on failure. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. |
| Design | [tests/recovery/session_image_fixture.py](../../../../../tests/recovery/session_image_fixture.py), [docs/development.md](../../../../development.md), [src/runtime/checkpoint_policy.hpp](../../../../../src/runtime/checkpoint_policy.hpp), [docs/session-journal.md](../../../../session-journal.md) |
