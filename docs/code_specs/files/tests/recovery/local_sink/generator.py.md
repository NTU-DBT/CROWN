# `tests/recovery/local_sink/generator.py` — block usage map

[Source](../../../../../../tests/recovery/local_sink/generator.py) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `e5dddb76fda621f7ae231cba7f2d009fc3444b729f59d3fc7c4e5f023c31be30`. 206 lines partitioned into 13 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../../code_review.md), [docs/reference_fuzz.md](../../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../../tests/recovery/local_sink/generator.py#L1) | Imports dependencies; declares types or opens a type body; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 17–18](../../../../../../tests/recovery/local_sink/generator.py#L17) | Callable definition: def sha256(data): | calls hexdigest; returns hashlib.sha256(data).hexdigest() · [reviewed contract](#b0002) |
| [B0003 · 19–20](../../../../../../tests/recovery/local_sink/generator.py#L19) | Explanatory comments or spacing. |  |
| [B0004 · 21–22](../../../../../../tests/recovery/local_sink/generator.py#L21) | Callable definition: def span(start, length): | calls ; returns {"offset": start, "length": length, "end_exclusive": start + length} · [reviewed contract](#b0004) |
| [B0005 · 23–24](../../../../../../tests/recovery/local_sink/generator.py#L23) | Explanatory comments or spacing. |  |
| [B0006 · 25–49](../../../../../../tests/recovery/local_sink/generator.py#L25) | Callable definition: def encode_scalar(kind, value): | calls pack, encode, len, date; returns wire, {"kind": kind, "tag": tag, "wire_length": len(wire)} · [reviewed contract](#b0006) |
| [B0007 · 50–51](../../../../../../tests/recovery/local_sink/generator.py#L50) | Explanatory comments or spacing. |  |
| [B0008 · 52–70](../../../../../../tests/recovery/local_sink/generator.py#L52) | Callable definition: def encode_row(operation, values): | calls pack, len, encode_scalar, span; returns encoded, {; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 71–100](../../../../../../tests/recovery/local_sink/generator.py#L71) | declares values/defaults or compile-time conditions. | growth insert; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 101–134](../../../../../../tests/recovery/local_sink/generator.py#L101) | declares types or opens a type body; declares values/defaults or compile-time conditions. | 3 loop sites · [reviewed contract](#b0010) |
| [B0011 · 135–151](../../../../../../tests/recovery/local_sink/generator.py#L135) | declares values/defaults or compile-time conditions. | 3 loop sites · [reviewed contract](#b0011) |
| [B0012 · 152–187](../../../../../../tests/recovery/local_sink/generator.py#L152) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0012) |
| [B0013 · 188–206](../../../../../../tests/recovery/local_sink/generator.py#L188) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |

## B0001

[Lines 1–16](../../../../../../tests/recovery/local_sink/generator.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FLAGS = 0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the eager CROWNSK1 fixture output root and fixed envelope constants. |
| inputs / outputs | Sets OUT to this script’s directory and binds CROWNSK1 magic, version 1 and zero flags. |
| invariants | The module executes the following fixture assembly/write blocks on import; output location is independent of cwd. |
| ownership | Module globals own constants and output Path only. |
| failure | Import/path setup errors propagate; this block does not write files. |
| cost | Module imports, source-relative path resolution and fixed envelope constants. |
| Design | [tests/recovery/local_sink/generator.py](../../../../../../tests/recovery/local_sink/generator.py), [tests/recovery/local_sink/manifest.json](../../../../../../tests/recovery/local_sink/manifest.json), tests/recovery/local_sink/generator.py:1-16 |

## B0002

[Lines 17–18](../../../../../../tests/recovery/local_sink/generator.py#L17); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/recovery/local_sink/generator.py](../../../../../../tests/recovery/local_sink/generator.py), [docs/local-sink.md](../../../../../local-sink.md), [tests/recovery/local_sink/manifest.json](../../../../../../tests/recovery/local_sink/manifest.json) |

## B0004

[Lines 21–22](../../../../../../tests/recovery/local_sink/generator.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def span(start, length):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe an offset/length interval in a fixture manifest. |
| inputs / outputs | Returns a new dict with offset, length and end_exclusive=offset+length. |
| invariants | Callers supply numeric fixture offsets; no nonnegative/range/overlap validation occurs. |
| ownership | The dict is new; offset/length values are retained by reference rather than deep-copied. |
| failure | Invalid addition/type operations propagate; no wire or file is changed. |
| cost | One Python addition and fixed dict creation; large-integer addition depends on operand bit lengths. |
| Design | [tests/recovery/local_sink/generator.py](../../../../../../tests/recovery/local_sink/generator.py), [docs/local-sink.md](../../../../../local-sink.md), [tests/recovery/local_sink/manifest.json](../../../../../../tests/recovery/local_sink/manifest.json) |

## B0006

[Lines 25–49](../../../../../../tests/recovery/local_sink/generator.py#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def encode_scalar(kind, value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one of five native sink scalar kinds and describe its tag/length. |
| inputs / outputs | int64 uses signed q, string UTF-8/u64 length, bool truth byte, date signed days from 1970, decimal ASCII/u8 length; returns wire and new metadata. |
| invariants | Decimal grammar is not normalized; native strings may contain NUL. Unknown kinds reject and decimal payload must fit 255 bytes. |
| ownership | Creates independent encoded bytes/metadata; value is borrowed. Module-level generator code uses these results to write goldens when executed/imported. |
| failure | Unknown kind/long decimal raises ValueError; encoding/date arithmetic/struct range/type errors propagate. |
| cost | Strings/decimals scan and copy their full text; dates/numerics use fixed-width output plus conversion cost. |
| Design | [tests/recovery/local_sink/generator.py](../../../../../../tests/recovery/local_sink/generator.py), [docs/local-sink.md](../../../../../local-sink.md), [tests/recovery/local_sink/manifest.json](../../../../../../tests/recovery/local_sink/manifest.json) |

## B0008

[Lines 52–70](../../../../../../tests/recovery/local_sink/generator.py#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def encode_row(operation, values):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a signed sink row and record scalar-relative layout spans. |
| inputs / outputs | Writes operation byte, arity and encoded values; returns complete row bytes and metadata including SHA and a scalar metadata list. |
| invariants | Operation is width-checked but not restricted to insert/erase here; scalar offsets start at 9 and advance by encoded lengths. |
| ownership | Owns new parts/list/dict graph; later module-level dict(metadata) is shallow and mutates shared scalar metadata while converting spans. |
| failure | Scalar encoding, operation range, byte join or hashing errors propagate; no file is written by this function. |
| cost | Traverses/encodes all scalars, joins complete row and hashes it; memory is row bytes plus metadata per cell. |
| Design | [tests/recovery/local_sink/generator.py](../../../../../../tests/recovery/local_sink/generator.py), [docs/local-sink.md](../../../../../local-sink.md), [tests/recovery/local_sink/manifest.json](../../../../../../tests/recovery/local_sink/manifest.json) |

## B0009

[Lines 71–100](../../../../../../tests/recovery/local_sink/generator.py#L71); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
raise AssertionError("fixture row sort order changed")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode two fixed typed sink rows and sort them into the CROWNSK1 fixture order. |
| inputs / outputs | Calls encode_row for one insert and one erase using fixed int64/string/bool/date/decimal values, sorts by encoded bytes, and asserts the expected insert/erase order. |
| invariants | This is one deterministic two-row fixture; it does not prove general row ordering or native sink behavior. |
| ownership | Encoded row bytes and metadata dictionaries are module-owned temporaries retained for later blocks. |
| failure | Scalar encoding/assertion/allocation errors propagate; no output file is touched yet. |
| cost | Encodes two rows and sorts two byte strings. |
| Design | [tests/recovery/local_sink/generator.py](../../../../../../tests/recovery/local_sink/generator.py), [tests/recovery/local_sink/manifest.json](../../../../../../tests/recovery/local_sink/manifest.json), tests/recovery/local_sink/generator.py:71-100 |

## B0010

[Lines 101–134](../../../../../../tests/recovery/local_sink/generator.py#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
cursor += len(value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble the fixed CROWNSK1 epoch body/header and verify their declared lengths. |
| inputs / outputs | Builds fixed body fields, concatenates sorted row bytes, hashes body and header prefix, and checks prefix/header lengths before deriving record offsets. |
| invariants | Length assertions are local to this one golden record; they do not validate the native frame decoder or durable append path. |
| ownership | The body/header/record bytes stay in Python module variables for manifest/write stages. |
| failure | Packing/hash/assertion failures propagate; no file is written in this region. |
| cost | Fixed two-row frame concatenation and hashes; scratch retains body/header/record bytes. |
| Design | [tests/recovery/local_sink/generator.py](../../../../../../tests/recovery/local_sink/generator.py), [tests/recovery/local_sink/manifest.json](../../../../../../tests/recovery/local_sink/manifest.json), tests/recovery/local_sink/generator.py:101-134 |

## B0011

[Lines 135–151](../../../../../../tests/recovery/local_sink/generator.py#L135); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
raise AssertionError("row boundaries do not end at record boundary")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute row/scalar byte-span metadata and require the fixture cursor to end at the record boundary. |
| inputs / outputs | Walks two encoded rows and their scalar spans, fills row_metadata, and asserts the final cursor equals record length. |
| invariants | Offsets describe only the fixed generated record; this loop does not parse arbitrary sink input. |
| ownership | Metadata lists/dicts are retained for the manifest block and own their Python values. |
| failure | Span helper/assertion/allocation failures propagate with whatever in-memory metadata was already built. |
| cost | Linear in the two rows and their finite scalar fields. |
| Design | [tests/recovery/local_sink/generator.py](../../../../../../tests/recovery/local_sink/generator.py), [tests/recovery/local_sink/manifest.json](../../../../../../tests/recovery/local_sink/manifest.json), tests/recovery/local_sink/generator.py:135-151 |

## B0012

[Lines 152–187](../../../../../../tests/recovery/local_sink/generator.py#L152); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
"body": len(body),
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the CROWNSK1 manifest object from the fixed header/body/row-span values. |
| inputs / outputs | Builds one nested JSON-compatible dictionary describing constants, offsets, lengths and hashes; no file write occurs until B0013. |
| invariants | The manifest describes this fixture’s bytes and helper-generated spans only; it is not an acceptance result. |
| ownership | The module owns the manifest and references retained data until serialization. |
| failure | Dictionary allocation/hash lookup errors propagate; there is no recovery or destination mutation in this block. |
| cost | Constructs one finite nested manifest proportional to two rows and their scalar spans. |
| Design | [tests/recovery/local_sink/generator.py](../../../../../../tests/recovery/local_sink/generator.py), [tests/recovery/local_sink/manifest.json](../../../../../../tests/recovery/local_sink/manifest.json), tests/recovery/local_sink/generator.py:152-187 |

## B0013

[Lines 188–206](../../../../../../tests/recovery/local_sink/generator.py#L188); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
print("record SHA256:", sha256(record))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Overwrite the adjacent CROWNSK1 epoch hex and manifest files and print fixture sizes/hashes. |
| inputs / outputs | Writes epoch.hex then manifest.json under OUT, followed by fixed size/hash prints. |
| invariants | No main guard or atomic replacement exists; importing this generator replaces these files in its own directory. |
| ownership | Test fixture directory owns the files; Python owns serialized text/temporary encodings. |
| failure | Serialization/write/print errors propagate; a manifest failure can leave the already-written epoch file updated. |
| cost | Two small fixed-file writes and six summary prints. |
| Design | [tests/recovery/local_sink/generator.py](../../../../../../tests/recovery/local_sink/generator.py), [tests/recovery/local_sink/manifest.json](../../../../../../tests/recovery/local_sink/manifest.json), tests/recovery/local_sink/generator.py:188-206 |
