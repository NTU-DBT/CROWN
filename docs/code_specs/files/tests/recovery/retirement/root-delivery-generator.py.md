# `tests/recovery/retirement/root-delivery-generator.py` — block usage map

[Source](../../../../../../tests/recovery/retirement/root-delivery-generator.py) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `5e56fd2d10c141c148ccbd5fcb6796c475af71625abcd76f97314e30acbef989`. 115 lines partitioned into 11 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../../code_review.md), [docs/reference_fuzz.md](../../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L1) | Imports dependencies; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 16–17](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L16) | Callable definition: def sha256(data): | calls hexdigest; returns hashlib.sha256(data).hexdigest() · [reviewed contract](#b0002) |
| [B0003 · 18–19](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L18) | Explanatory comments or spacing. |  |
| [B0004 · 20–21](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L20) | Callable definition: def span(offset, length): | calls ; returns {"offset": offset, "length": length, "end_exclusive": offset + length} · [reviewed contract](#b0004) |
| [B0005 · 22–23](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L22) | Explanatory comments or spacing. |  |
| [B0006 · 24–25](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L24) | Callable definition: def u16(value): | calls pack; returns struct.pack("&lt;H", value) · [reviewed contract](#b0006) |
| [B0007 · 26–27](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L26) | Explanatory comments or spacing. |  |
| [B0008 · 28–29](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L28) | Callable definition: def u64(value): | calls pack; returns struct.pack("&lt;Q", value) · [reviewed contract](#b0008) |
| [B0009 · 30–64](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L30) | declares values/defaults or compile-time conditions. | source comment (unverified): # Original 128-byte selected-root payload. · [reviewed contract](#b0009) |
| [B0010 · 65–82](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L65) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 83–115](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L83) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |

## B0001

[Lines 1–15](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FLAGS = 0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the eager CROWNGR1 v2 delivery-anchor fixture constants and output path. |
| inputs / outputs | Sets OUT beside the script and binds CROWNGR1 magic, version 2 and zero flags. IDs, hashes and sequence inputs are assembled in B0009. |
| invariants | No main guard: later top-level blocks assemble and write the fixture during import; paths remain anchored beside the script. |
| ownership | Module owns literal constants and assembled byte/manifest objects. |
| failure | Import/setup errors propagate; this block itself has no output file mutation. |
| cost | Module imports, source-relative path resolution and fixed envelope constants. |
| Design | [tests/recovery/retirement/root-delivery-generator.py](../../../../../../tests/recovery/retirement/root-delivery-generator.py), [tests/recovery/retirement/root-delivery-manifest.json](../../../../../../tests/recovery/retirement/root-delivery-manifest.json), tests/recovery/retirement/root-delivery-generator.py:1-15 |

## B0002

[Lines 16–17](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sha256(data):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute a lowercase SHA-256 text fingerprint for fixture bytes. |
| inputs / outputs | Accepts a bytes-like buffer and returns a fresh 64-character hexadecimal string. |
| invariants | Hashes the supplied bytes exactly; it does not validate framing or confer receipt/native authority. |
| ownership | Reads the borrowed buffer synchronously and returns independent digest text. |
| failure | hashlib buffer/type errors propagate; this helper performs no I/O. |
| cost | Linear hashing over the entire buffer plus fixed-size digest rendering. |
| Design | [tests/recovery/retirement/root-delivery-generator.py](../../../../../../tests/recovery/retirement/root-delivery-generator.py), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/local-sink.md](../../../../../local-sink.md) |

## B0004

[Lines 20–21](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def span(offset, length):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe an offset/length interval in a fixture manifest. |
| inputs / outputs | Returns a new dict with offset, length and end_exclusive=offset+length. |
| invariants | Callers supply numeric fixture offsets; no nonnegative/range/overlap validation occurs. |
| ownership | The dict is new; offset/length values are retained by reference rather than deep-copied. |
| failure | Invalid addition/type operations propagate; no wire or file is changed. |
| cost | One Python addition and fixed dict creation; large-integer addition depends on operand bit lengths. |
| Design | [tests/recovery/retirement/root-delivery-generator.py](../../../../../../tests/recovery/retirement/root-delivery-generator.py), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/local-sink.md](../../../../../local-sink.md) |

## B0006

[Lines 24–25](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def u16(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one unsigned 16-bit little-endian fixture word. |
| inputs / outputs | Returns 2 new byte(s) for an integer/indexable value in 0..2^16-1. |
| invariants | No masking or semantic tag validation occurs; range is enforced by struct.pack. |
| ownership | Input integer is borrowed/immutable; returned bytes own their encoding. |
| failure | Out-of-range or non-indexable input raises struct.error/TypeError; no file is touched. |
| cost | Fixed 2-byte output; integer conversion/range checking depends on operand representation. |
| Design | [tests/recovery/retirement/root-delivery-generator.py](../../../../../../tests/recovery/retirement/root-delivery-generator.py), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/local-sink.md](../../../../../local-sink.md) |

## B0008

[Lines 28–29](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def u64(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one unsigned 64-bit little-endian fixture word. |
| inputs / outputs | Returns 8 new byte(s) for an integer/indexable value in 0..2^64-1. |
| invariants | No masking or semantic tag validation occurs; range is enforced by struct.pack. |
| ownership | Input integer is borrowed/immutable; returned bytes own their encoding. |
| failure | Out-of-range or non-indexable input raises struct.error/TypeError; no file is touched. |
| cost | Fixed 8-byte output; integer conversion/range checking depends on operand representation. |
| Design | [tests/recovery/retirement/root-delivery-generator.py](../../../../../../tests/recovery/retirement/root-delivery-generator.py), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/local-sink.md](../../../../../local-sink.md) |

## B0009

[Lines 30–64](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L30); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
raise AssertionError("version-2 root record must be 324 bytes")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble the fixed CROWNGR1 v2 delivery-anchor body/prefix/checksum/record and assert lengths. |
| inputs / outputs | Uses literal query/sink IDs and sequence/length/hash values, packs fields, and checks body, covered-prefix and record sizes. |
| invariants | This is a synthetic version-2 root record only; it is not published by a generation owner or accepted by native recovery in this script. |
| ownership | Body, prefix and record bytes remain module-owned for later field-map/manifest stages. |
| failure | Packing/hash/assertion errors propagate; no file is written here. |
| cost | Fixed-size concatenation and checksum. |
| Design | [tests/recovery/retirement/root-delivery-generator.py](../../../../../../tests/recovery/retirement/root-delivery-generator.py), [tests/recovery/retirement/root-delivery-manifest.json](../../../../../../tests/recovery/retirement/root-delivery-manifest.json), tests/recovery/retirement/root-delivery-generator.py:30-64 |

## B0010

[Lines 65–82](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L65); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
"checksum": {"span": span(260, 64), "value": checksum.decode("ascii"), "encoding": "ASCII64 lowercase SHA256", "covers": span(0, 260)},
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the CROWNGR1 v2 byte-offset/field metadata for the fixed delivery-root record. |
| inputs / outputs | Creates the fields map from span() results and literal manifest values for the previously assembled body/record. |
| invariants | Offsets describe one synthetic record and do not attest to selected-root recovery or sink durability. |
| ownership | The nested map is retained in process for JSON serialization in B0011. |
| failure | Mapping/serialization-value allocation errors propagate; no output file is touched here. |
| cost | Finite metadata assembly proportional to the fixed field count. |
| Design | [tests/recovery/retirement/root-delivery-generator.py](../../../../../../tests/recovery/retirement/root-delivery-generator.py), [tests/recovery/retirement/root-delivery-manifest.json](../../../../../../tests/recovery/retirement/root-delivery-manifest.json), tests/recovery/retirement/root-delivery-generator.py:65-82 |

## B0011

[Lines 83–115](../../../../../../tests/recovery/retirement/root-delivery-generator.py#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
print("record SHA256:", sha256(record))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Overwrite the adjacent CROWNGR1 v2 root hex/manifest files and print fixed record summaries. |
| inputs / outputs | Writes root-delivery.hex then root-delivery-manifest.json under OUT and prints sizes and hashes. |
| invariants | Importing this module executes the writes; there is no atomic pair update or rollback if the second write fails. |
| ownership | The test fixture directory owns the files; Python owns serialization buffers and manifest state. |
| failure | Serialization/write/stdout errors propagate; the first file may already be replaced when a later step fails. |
| cost | Two fixed-file writes and six summary prints. |
| Design | [tests/recovery/retirement/root-delivery-generator.py](../../../../../../tests/recovery/retirement/root-delivery-generator.py), [tests/recovery/retirement/root-delivery-manifest.json](../../../../../../tests/recovery/retirement/root-delivery-manifest.json), tests/recovery/retirement/root-delivery-generator.py:83-115 |
