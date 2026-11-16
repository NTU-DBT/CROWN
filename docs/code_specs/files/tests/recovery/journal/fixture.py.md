# `tests/recovery/journal/fixture.py` — block usage map

[Source](../../../../../../tests/recovery/journal/fixture.py) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `18be33429872e201b91d60908ebb13b70f40754a41eebdc35321cb249ad51c31`. 352 lines partitioned into 39 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../../code_review.md), [docs/reference_fuzz.md](../../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–26](../../../../../../tests/recovery/journal/fixture.py#L1) | Imports dependencies; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 27–28](../../../../../../tests/recovery/journal/fixture.py#L27) | Callable definition: def u8(value: int) -&gt; bytes: | calls pack; returns struct.pack("&lt;B", value) · [reviewed contract](#b0002) |
| [B0003 · 29–30](../../../../../../tests/recovery/journal/fixture.py#L29) | Explanatory comments or spacing. |  |
| [B0004 · 31–32](../../../../../../tests/recovery/journal/fixture.py#L31) | Callable definition: def u16(value: int) -&gt; bytes: | calls pack; returns struct.pack("&lt;H", value) · [reviewed contract](#b0004) |
| [B0005 · 33–34](../../../../../../tests/recovery/journal/fixture.py#L33) | Explanatory comments or spacing. |  |
| [B0006 · 35–36](../../../../../../tests/recovery/journal/fixture.py#L35) | Callable definition: def u32(value: int) -&gt; bytes: | calls pack; returns struct.pack("&lt;I", value) · [reviewed contract](#b0006) |
| [B0007 · 37–38](../../../../../../tests/recovery/journal/fixture.py#L37) | Explanatory comments or spacing. |  |
| [B0008 · 39–40](../../../../../../tests/recovery/journal/fixture.py#L39) | Callable definition: def u64(value: int) -&gt; bytes: | calls pack; returns struct.pack("&lt;Q", value) · [reviewed contract](#b0008) |
| [B0009 · 41–42](../../../../../../tests/recovery/journal/fixture.py#L41) | Explanatory comments or spacing. |  |
| [B0010 · 43–44](../../../../../../tests/recovery/journal/fixture.py#L43) | Callable definition: def i64_bits(value: int) -&gt; bytes: | calls pack; returns struct.pack("&lt;Q", value & ((1 &lt;&lt; 64) - 1)) · [reviewed contract](#b0010) |
| [B0011 · 45–46](../../../../../../tests/recovery/journal/fixture.py#L45) | Explanatory comments or spacing. |  |
| [B0012 · 47–48](../../../../../../tests/recovery/journal/fixture.py#L47) | Callable definition: def body_prefix(kind: int, ordinal: int) -&gt; bytes: | calls u8, u64; returns u8(kind) + u64(ordinal) · [reviewed contract](#b0012) |
| [B0013 · 49–50](../../../../../../tests/recovery/journal/fixture.py#L49) | Explanatory comments or spacing. |  |
| [B0014 · 51–63](../../../../../../tests/recovery/journal/fixture.py#L51) | Callable definition: def frame(body: bytes) -&gt; bytes: | calls sha256, hexdigest, encode, u16; returns prefix + prefix_checksum + body; source comment (unverified): # flags · [reviewed contract](#b0014) |
| [B0015 · 64–65](../../../../../../tests/recovery/journal/fixture.py#L64) | Explanatory comments or spacing. |  |
| [B0016 · 66–67](../../../../../../tests/recovery/journal/fixture.py#L66) | Callable definition: def row(cells: list\[tuple\[int, bytes\]\]) -&gt; bytes: | calls u64, len, join; returns u64(len(cells)) + b"".join(tagged for _, tagged in cells); 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 68–69](../../../../../../tests/recovery/journal/fixture.py#L68) | Explanatory comments or spacing. |  |
| [B0018 · 70–71](../../../../../../tests/recovery/journal/fixture.py#L70) | Callable definition: def int64_cell(value: int) -&gt; tuple\[int, bytes\]: | calls u8, i64_bits; returns 0, u8(0) + i64_bits(value) · [reviewed contract](#b0018) |
| [B0019 · 72–73](../../../../../../tests/recovery/journal/fixture.py#L72) | Explanatory comments or spacing. |  |
| [B0020 · 74–75](../../../../../../tests/recovery/journal/fixture.py#L74) | Callable definition: def raw_cell(value: bytes) -&gt; tuple\[int, bytes\]: | calls u8, u64, len; returns 1, u8(1) + u64(len(value)) + value · [reviewed contract](#b0020) |
| [B0021 · 76–77](../../../../../../tests/recovery/journal/fixture.py#L76) | Explanatory comments or spacing. |  |
| [B0022 · 78–79](../../../../../../tests/recovery/journal/fixture.py#L78) | Callable definition: def bool_cell(value: bool) -&gt; tuple\[int, bytes\]: | calls u8; returns 2, u8(2) + u8(1 if value else 0) · [reviewed contract](#b0022) |
| [B0023 · 80–81](../../../../../../tests/recovery/journal/fixture.py#L80) | Explanatory comments or spacing. |  |
| [B0024 · 82–83](../../../../../../tests/recovery/journal/fixture.py#L82) | Callable definition: def epoch_day_cell(days: int) -&gt; tuple\[int, bytes\]: | calls u8, u32; returns 3, u8(3) + u32(days & 0xFFFFFFFF) · [reviewed contract](#b0024) |
| [B0025 · 84–85](../../../../../../tests/recovery/journal/fixture.py#L84) | Explanatory comments or spacing. |  |
| [B0026 · 86–90](../../../../../../tests/recovery/journal/fixture.py#L86) | Callable definition: def decimal_cell(text: str) -&gt; tuple\[int, bytes\]: | calls encode, len, ValueError, u8; returns 4, u8(4) + u8(len(encoded)) + encoded · [reviewed contract](#b0026) |
| [B0027 · 91–92](../../../../../../tests/recovery/journal/fixture.py#L91) | Explanatory comments or spacing. |  |
| [B0028 · 93–99](../../../../../../tests/recovery/journal/fixture.py#L93) | Callable definition: def source(present: bool, name: str = "", offset: int = 0) -&gt; bytes: | calls u8, encode, ValueError, u64; returns u8(0); u8(1) + u64(len(encoded)) + encoded + u64(offset) · [reviewed contract](#b0028) |
| [B0029 · 100–101](../../../../../../tests/recovery/journal/fixture.py#L100) | Explanatory comments or spacing. |  |
| [B0030 · 102–119](../../../../../../tests/recovery/journal/fixture.py#L102) | Callable definition: def reader_progress( | calls u8, u64, len, join; returns u8(0); (; 1 loop sites · [reviewed contract](#b0030) |
| [B0031 · 120–121](../../../../../../tests/recovery/journal/fixture.py#L120) | Explanatory comments or spacing. |  |
| [B0032 · 122–137](../../../../../../tests/recovery/journal/fixture.py#L122) | Callable definition: def input_body( | calls body_prefix, u8, u64; returns ( · [reviewed contract](#b0032) |
| [B0033 · 138–139](../../../../../../tests/recovery/journal/fixture.py#L138) | Explanatory comments or spacing. |  |
| [B0034 · 140–148](../../../../../../tests/recovery/journal/fixture.py#L140) | Callable definition: def named_row() -&gt; bytes: | calls int64_cell, raw_cell, bool_cell, epoch_day_cell; returns row(cells); source comment (unverified): # 1970-01-01 · [reviewed contract](#b0034) |
| [B0035 · 149–150](../../../../../../tests/recovery/journal/fixture.py#L149) | Explanatory comments or spacing. |  |
| [B0036 · 151–257](../../../../../../tests/recovery/journal/fixture.py#L151) | Callable definition: def build_frames() -&gt; tuple\[dict\[str, tuple\[bytes, bytes\]\], bytes\]: | calls encode, ValueError, len, any; returns frames, physical_body; growth insert; 3 loop sites; source comment (unverified): # generation · [reviewed contract](#b0036) |
| [B0037 · 258–259](../../../../../../tests/recovery/journal/fixture.py#L258) | Explanatory comments or spacing. |  |
| [B0038 · 260–348](../../../../../../tests/recovery/journal/fixture.py#L260) | Callable definition: def main() -&gt; None: | calls mkdir, build_frames, items, hex; 2 loop sites · [reviewed contract](#b0038) |
| [B0039 · 349–352](../../../../../../tests/recovery/journal/fixture.py#L349) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0039) |

## B0001

[Lines 1–26](../../../../../../tests/recovery/journal/fixture.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
"7dc08dba65898efde205ca8008e3b4b102e79c13f7fcdee0b52af9edfe3c9779"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read and parse the neighboring WAL format specification at fixture-module import time. |
| inputs / outputs | Sets HERE/OUTPUT/SPEC_PATH, reads all format.json bytes into SPEC_BYTES, decodes UTF-8, and json.loads into SPEC. |
| invariants | The specification path is anchored beside this script; the import read precedes the separately guarded fixture writer and does not invoke it. |
| ownership | The module retains SPEC_BYTES and the parsed SPEC object for its later frame-generation functions. |
| failure | Missing/inaccessible file, Unicode, or JSON errors propagate during import; no partial fixture output is produced in this block. |
| cost | One complete read and JSON parse of the adjacent format.json; memory retains both original bytes and parsed object. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [tests/recovery/journal/fixture-manifest.json](../../../../../../tests/recovery/journal/fixture-manifest.json), tests/recovery/journal/fixture.py:1-26 |

## B0002

[Lines 27–28](../../../../../../tests/recovery/journal/fixture.py#L27); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0004

[Lines 31–32](../../../../../../tests/recovery/journal/fixture.py#L31); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0006

[Lines 35–36](../../../../../../tests/recovery/journal/fixture.py#L35); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0008

[Lines 39–40](../../../../../../tests/recovery/journal/fixture.py#L39); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0010

[Lines 43–44](../../../../../../tests/recovery/journal/fixture.py#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def i64_bits(value: int) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the low 64 bits of a signed/arbitrary Python integer. |
| inputs / outputs | Masks value modulo 2^64 and packs the resulting unsigned word into eight little-endian bytes. |
| invariants | Values outside signed int64 are deliberately truncated rather than rejected; caller chooses the intended signed fixture domain. |
| ownership | Builds masked integer and new immutable bytes without changing caller input. |
| failure | Non-integer bitwise operations or packing errors propagate. |
| cost | Bitwise masking depends on integer limb count; output is fixed eight bytes. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0012

[Lines 47–48](../../../../../../tests/recovery/journal/fixture.py#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def body_prefix(kind: int, ordinal: int) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start a journal body with its kind byte and record ordinal. |
| inputs / outputs | Returns u8(kind) concatenated with u64(ordinal), exactly nine bytes. |
| invariants | Widths are checked by packers; whether kind/ordinal is valid in a WAL stream is not checked here. |
| ownership | Owns concatenated result; no frame, cursor or input buffer is mutated. |
| failure | struct range/type errors propagate from either packer. |
| cost | Two fixed-width encodings and a nine-byte concatenation. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0014

[Lines 51–63](../../../../../../tests/recovery/journal/fixture.py#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def frame(body: bytes) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Protect an independently assembled journal body with maintained WAL framing. |
| inputs / outputs | Uses SPEC magic/version, reserved 0, body length, body SHA text and prefix 84 SHA text; returns complete 148-byte header plus body. |
| invariants | The first prefix must be exactly 84 bytes; spec semantics/body validity are not inferred from its checksum. |
| ownership | Creates digest/prefix/result bytes while borrowing immutable body and loaded global SPEC. |
| failure | Unexpected prefix size raises ValueError; spec lookup/ASCII/packing errors propagate. |
| cost | Hashes all body bytes and the fixed prefix, then copies them into a complete frame; storage scales with body length. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0016

[Lines 66–67](../../../../../../tests/recovery/journal/fixture.py#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def row(cells: list[tuple[int, bytes]]) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble a row from already tagged scalar encodings. |
| inputs / outputs | Prefixes the number of cell tuples and joins each tuple’s second element into one bytes result. |
| invariants | The integer tag in each pair is ignored; callers must keep it consistent with the supplied tagged bytes. |
| ownership | Creates a new joined row; input list/pairs and immutable scalar byte strings are read only. |
| failure | Malformed pair unpacking, non-byte join input or length packing errors propagate. |
| cost | Visits every cell and copies the total tagged payload plus an eight-byte count. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0018

[Lines 70–71](../../../../../../tests/recovery/journal/fixture.py#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def int64_cell(value: int) -> tuple[int, bytes]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a native int64 fixture scalar. |
| inputs / outputs | Returns tag 0 plus bytes containing tag 0 and the low 64 two’s-complement bits of value. |
| invariants | The helper inherits modular masking from i64_bits and does not enforce a signed-domain bound. |
| ownership | New tuple/bytes own their encoding; input integer is unchanged. |
| failure | Bitwise/type/packing errors propagate. |
| cost | Fixed nine-byte wire payload plus arbitrary-integer mask cost. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0020

[Lines 74–75](../../../../../../tests/recovery/journal/fixture.py#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def raw_cell(value: bytes) -> tuple[int, bytes]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a native raw-byte scalar, including embedded NUL/non-UTF-8 bytes. |
| inputs / outputs | Returns tag 1 and tag 1/u64-length/value bytes. |
| invariants | Payload is opaque; no SQL TEXT UTF-8 or no-NUL rule is imposed by this native fixture helper. |
| ownership | Copies borrowed immutable value bytes into a new encoding and returns a new tuple. |
| failure | Non-byte concatenation or length packing errors propagate. |
| cost | Linear copy in raw byte length plus fixed tag/length work. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0022

[Lines 78–79](../../../../../../tests/recovery/journal/fixture.py#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def bool_cell(value: bool) -> tuple[int, bytes]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a native Boolean fixture scalar from Python truthiness. |
| inputs / outputs | Returns tag 2 and a tag byte followed by 0 or 1. |
| invariants | It truth-tests value rather than requiring type(value) is bool. |
| ownership | Returns new fixed bytes/tuple; caller value is not modified. |
| failure | Errors in a custom truth conversion propagate; ordinary packing is fixed-domain. |
| cost | One truth conversion and two-byte wire output. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0024

[Lines 82–83](../../../../../../tests/recovery/journal/fixture.py#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def epoch_day_cell(days: int) -> tuple[int, bytes]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode signed epoch-day bits for a native date fixture. |
| inputs / outputs | Returns tag 3 with low 32 bits of days serialized as u32 little endian. |
| invariants | Masking does not validate the Gregorian/date range; negative days are represented by their two’s-complement bits. |
| ownership | Builds a masked integer and new tuple/bytes. |
| failure | Non-integer bitwise or packing errors propagate. |
| cost | Five-byte output; mask work depends on Python integer size. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0026

[Lines 86–90](../../../../../../tests/recovery/journal/fixture.py#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def decimal_cell(text: str) -> tuple[int, bytes]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode supplied decimal fixture spelling without normalizing it. |
| inputs / outputs | ASCII-encodes text and returns tag 4/u8-length/data with the numeric tag alongside. |
| invariants | Only ASCII and one-byte length are enforced; canonical decimal grammar/precision are a codec-test responsibility. |
| ownership | Owns encoded bytes; original text is read only. |
| failure | Non-ASCII raises UnicodeEncodeError; length&gt;255 raises ValueError. |
| cost | Scans/encodes/copies the complete text; fixed-length check follows encoding. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0028

[Lines 93–99](../../../../../../tests/recovery/journal/fixture.py#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def source(present: bool, name: str = "", offset: int = 0) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode optional journal input source-position metadata. |
| inputs / outputs | False present returns flag 0; true requires nonempty UTF-8 name without NUL and emits flag 1/u64 name length/name/u64 offset. |
| invariants | Absent metadata ignores name/offset. Offset monotonicity and source history are not validated. |
| ownership | Returns fresh bytes and owns the UTF-8 name copy; caller string is unchanged. |
| failure | Invalid name raises ValueError, invalid UTF-8 encoding UnicodeEncodeError, and invalid offset/range struct.error. |
| cost | Present form scans/encodes/copies the source name; absent form is one byte. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0030

[Lines 102–119](../../../../../../tests/recovery/journal/fixture.py#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def reader_progress(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode optional stream decoder progress, including CSV header state. |
| inputs / outputs | Present form writes byte/record counters, truth-normalized header_read, permutation count and each u64 field; absent form is flag 0. |
| invariants | Permutation validity and relationships between counters are not checked; caller supplies a coherent fixture. |
| ownership | Joins fresh encodings and borrows the permutation sequence; retains no mutable caller structure. |
| failure | Range/type failures in counters or permutation entries propagate from struct.pack. |
| cost | Linear in permutation length with fixed-width words; absent form is constant. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0032

[Lines 122–137](../../../../../../tests/recovery/journal/fixture.py#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def input_body(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Join an Input body envelope with already encoded command/source/reader payloads. |
| inputs / outputs | Writes kind 1/ordinal, item tag, command sequence, payload and both optional-metadata byte strings. |
| invariants | Only numeric widths are checked; this helper does not validate command ordering or inspect payload schemas. |
| ownership | Returns new bytes copying all supplied encoded components; no caller buffer is mutated. |
| failure | Numeric packing or incompatible byte-concatenation errors propagate. |
| cost | Linear in combined payload/source/reader byte lengths plus fixed envelope. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0034

[Lines 140–148](../../../../../../tests/recovery/journal/fixture.py#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def named_row() -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the five-type hostile native row used by the physical Input golden. |
| inputs / outputs | Returns encoded INT64_MIN, raw A/NUL/0xff, true, epoch-day 0 and decimal -123.45. |
| invariants | This is native raw scalar coverage, not a SQL nullable row or a parser-generated fixture. |
| ownership | Creates independent cell encodings/list and joined row; uses no external mutable state. |
| failure | Underlying pack/encoding errors propagate; constants are chosen within their widths. |
| cost | Fixed fixture payload with five encodings and one row join. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0036

[Lines 151–257](../../../../../../tests/recovery/journal/fixture.py#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def build_frames() -> tuple[dict[str, tuple[bytes, bytes]], bytes]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently construct seven maintained WAL golden bodies and complete frames. |
| inputs / outputs | Checks loaded SPEC magic/version/policy width/range; returns name→(body,frame) for header, physical input/commit/checkpoint and three window inputs, plus physical body. |
| invariants | Commit binds the physical body SHA; header has 26 policy words. The fixed EXPECTED_INPUT_BODY_SHA256 check occurs later in main, not here. |
| ownership | New dict/bytes contain immutable body/frame values; returned physical body shares the same immutable object also stored in the dict. Loaded SPEC is read only. |
| failure | Wrong magic/version/policy shape/range raises ValueError; missing spec keys and packing errors propagate. |
| cost | Constructs/copies/hashes every fixture frame, including the rich row; size follows spec policy and fixed fixture payloads. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0038

[Lines 260–348](../../../../../../tests/recovery/journal/fixture.py#L260); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write independent maintained WAL hex fixtures and a provenance/layout manifest. |
| inputs / outputs | Builds frames, overwrites each .hex, verifies the fixed original input-body digest, writes fixture-manifest.json and prints hashes/lengths. |
| invariants | The fixed digest must match; output hex writes happen before that check, so a later failure does not roll back earlier files. |
| ownership | Owns frame/manifest data and reads its own source for provenance; writes directly into OUTPUT, without a temporary transaction or rollback. |
| failure | ValueError, file/encoding and JSON/packing errors propagate to process failure; no top-level catch translates them. |
| cost | Multiple whole-body/frame/prefix/source/spec hash passes, hex expansion, JSON materialization and file writes dominate the fixed corpus. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0039

[Lines 349–352](../../../../../../tests/recovery/journal/fixture.py#L349); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Write independent maintained WAL hex fixtures and a provenance/layout manifest. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | No presentation catch is added here: main/fixture failures and SystemExit propagate through the interpreter. This block supplies no extra retry or rollback. Delegated main writes frame files and then a manifest; a later write failure can leave already completed files. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. |
| Design | [tests/recovery/journal/fixture.py](../../../../../../tests/recovery/journal/fixture.py), [docs/development.md](../../../../../development.md), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |
