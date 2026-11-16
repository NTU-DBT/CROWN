# `tests/recovery/retirement/generator.py` — block usage map

[Source](../../../../../../tests/recovery/retirement/generator.py) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c519bb6cfe70610d0610597091c37022a8d9b64f278ac2860bcd6f8d369ab0a5`. 146 lines partitioned into 10 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../../code_review.md), [docs/reference_fuzz.md](../../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../../tests/recovery/retirement/generator.py#L1) | Imports dependencies; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 21–22](../../../../../../tests/recovery/retirement/generator.py#L21) | Callable definition: def sha256(data): | calls hexdigest; returns hashlib.sha256(data).hexdigest() · [reviewed contract](#b0002) |
| [B0003 · 23–24](../../../../../../tests/recovery/retirement/generator.py#L23) | Explanatory comments or spacing. |  |
| [B0004 · 25–26](../../../../../../tests/recovery/retirement/generator.py#L25) | Callable definition: def span(offset, length): | calls ; returns {"offset": offset, "length": length, "end_exclusive": offset + length} · [reviewed contract](#b0004) |
| [B0005 · 27–33](../../../../../../tests/recovery/retirement/generator.py#L27) | declares values/defaults or compile-time conditions. | source comment (unverified): # 8-byte magic + u16 version + u16 flags + u64 body length · [reviewed contract](#b0005) |
| [B0006 · 34–42](../../../../../../tests/recovery/retirement/generator.py#L34) | Callable definition: def add(name, data, value, encoding): | calls append, span, len · [reviewed contract](#b0006) |
| [B0007 · 43–78](../../../../../../tests/recovery/retirement/generator.py#L43) | declares types or opens a type body; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): # Old selected root (128 bytes). · [reviewed contract](#b0007) |
| [B0008 · 79–93](../../../../../../tests/recovery/retirement/generator.py#L79) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0008) |
| [B0009 · 94–129](../../../../../../tests/recovery/retirement/generator.py#L94) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |
| [B0010 · 130–146](../../../../../../tests/recovery/retirement/generator.py#L130) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |

## B0001

[Lines 1–20](../../../../../../tests/recovery/retirement/generator.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
65536, 67108864,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the eager CROWNRT1 v1 fixture policy, envelope constants and output directory. |
| inputs / outputs | Sets OUT beside the module and binds the literal CROWNRT1 magic, version 1, zero flags and DEFAULT_POLICY words. Query/sink IDs and hashes are assigned in B0007. |
| invariants | This generator runs its following assembly/write blocks at import; all output paths are rooted at OUT. |
| ownership | Module globals own fixed constants and mutable field/manifest assembly state. |
| failure | Import/setup errors propagate; no file writes in this span. |
| cost | Module imports, source-relative path resolution and a fixed policy list. |
| Design | [tests/recovery/retirement/generator.py](../../../../../../tests/recovery/retirement/generator.py), [tests/recovery/retirement/manifest.json](../../../../../../tests/recovery/retirement/manifest.json), tests/recovery/retirement/generator.py:1-20 |

## B0002

[Lines 21–22](../../../../../../tests/recovery/retirement/generator.py#L21); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/recovery/retirement/generator.py](../../../../../../tests/recovery/retirement/generator.py), [docs/reoptimization.md](../../../../../reoptimization.md), [tests/recovery/retirement/intent.hex](../../../../../../tests/recovery/retirement/intent.hex) |

## B0004

[Lines 25–26](../../../../../../tests/recovery/retirement/generator.py#L25); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/recovery/retirement/generator.py](../../../../../../tests/recovery/retirement/generator.py), [docs/reoptimization.md](../../../../../reoptimization.md), [tests/recovery/retirement/intent.hex](../../../../../../tests/recovery/retirement/intent.hex) |

## B0005

[Lines 27–33](../../../../../../tests/recovery/retirement/generator.py#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L33:sha256:b6c27bd1ad6c2d07bf0b2aaf0d9f3e1f4c73b44126cb4ad5ec4f0849f029b4aa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the independent retirement-frame builder: empty field/part containers and offset 20 for magic/version/flags/body-length. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/recovery/retirement/generator.py](../../../../../../tests/recovery/retirement/generator.py), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 34–42](../../../../../../tests/recovery/retirement/generator.py#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def add(name, data, value, encoding):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append a named byte field to the module’s retirement-intent assembly and manifest layout. |
| inputs / outputs | Mutates global body_parts, fields and cursor: appends data, records current span/value/encoding under name, then advances cursor by len(data). |
| invariants | Caller provides correct wire/value correspondence and unique names; duplicate name overwrites metadata while bytes still append. |
| ownership | Retains data and value references in global collections; no deep copy is made. Module execution later joins/writes these globals. |
| failure | Length/addition/type or allocation errors propagate; a failure can leave partially updated global assembly. |
| cost | Amortized list/dict insertion plus fixed metadata creation and Python cursor addition; payload bytes are not copied until final join. |
| Design | [tests/recovery/retirement/generator.py](../../../../../../tests/recovery/retirement/generator.py), [docs/reoptimization.md](../../../../../reoptimization.md), [tests/recovery/retirement/intent.hex](../../../../../../tests/recovery/retirement/intent.hex) |

## B0007

[Lines 43–78](../../../../../../tests/recovery/retirement/generator.py#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
raise AssertionError("sink header section must be 496 bytes")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble fixed root and sink-header fields for the CROWNRT1 v1 history-retirement intent fixture. |
| inputs / outputs | Uses literal IDs/sequences/hashes and add() to append named spans/values; loops over DEFAULT_POLICY and checks fixed root/header section lengths. |
| invariants | The values are synthetic fixture constants, not a selected live generation or a proof that retirement is safe. |
| ownership | Module-level byte parts, field-offset map, and cursor are retained for the intent body and manifest. |
| failure | Pack/hash/assertion errors propagate; the block writes no files. |
| cost | One fixed number of header fields plus a finite policy loop. |
| Design | [tests/recovery/retirement/generator.py](../../../../../../tests/recovery/retirement/generator.py), [tests/recovery/retirement/manifest.json](../../../../../../tests/recovery/retirement/manifest.json), tests/recovery/retirement/generator.py:43-78 |

## B0008

[Lines 79–93](../../../../../../tests/recovery/retirement/generator.py#L79); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
raise AssertionError("retirement intent record must be 724 bytes")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish the fixed CROWNRT1 v1 acknowledgement body, protected prefix, checksum, and record-length checks. |
| inputs / outputs | Appends acknowledged generation/sequence, concatenates body, builds prefix/checksum/record, and asserts declared fixture lengths. |
| invariants | The serialized values are one independent intent fixture; they are not read from a live root or WAL. |
| ownership | Record/body byte strings remain module-owned for the manifest/write stage. |
| failure | Length, packing, hash, or allocation failures propagate; no file is written here. |
| cost | Fixed-size concatenations and one checksum. |
| Design | [tests/recovery/retirement/generator.py](../../../../../../tests/recovery/retirement/generator.py), [tests/recovery/retirement/manifest.json](../../../../../../tests/recovery/retirement/manifest.json), tests/recovery/retirement/generator.py:79-93 |

## B0009

[Lines 94–129](../../../../../../tests/recovery/retirement/generator.py#L94); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
"covers": span(0, 660),
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the CROWNRT1 v1 manifest from the fixed field layout and record values. |
| inputs / outputs | Creates a JSON-compatible nested manifest describing literal values, offsets, lengths and record/body hashes. |
| invariants | The manifest is coupled to the fixed bytes built earlier; it does not imply native parser/recovery acceptance. |
| ownership | The manifest dictionary and earlier record values remain in module globals for the write stage. |
| failure | Python allocation/encoding-value errors propagate; no external mutation in this block. |
| cost | Builds one finite metadata object. |
| Design | [tests/recovery/retirement/generator.py](../../../../../../tests/recovery/retirement/generator.py), [tests/recovery/retirement/manifest.json](../../../../../../tests/recovery/retirement/manifest.json), tests/recovery/retirement/generator.py:94-129 |

## B0010

[Lines 130–146](../../../../../../tests/recovery/retirement/generator.py#L130); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
print("record SHA256:", sha256(record))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Overwrite the adjacent CROWNRT1 intent hex/manifest files and print record hashes. |
| inputs / outputs | Writes intent.hex then manifest.json under OUT and prints body/prefix/record sizes and SHA256 values. |
| invariants | Importing the module performs these writes; fixed targets are truncated/replaced without staging or rollback. |
| ownership | The test fixture directory owns persistent outputs; serialization buffers are temporary Python values. |
| failure | JSON/text/file errors propagate; if manifest writing fails, intent.hex may already have been replaced. |
| cost | Two fixed-file writes and six summary prints. |
| Design | [tests/recovery/retirement/generator.py](../../../../../../tests/recovery/retirement/generator.py), [tests/recovery/retirement/manifest.json](../../../../../../tests/recovery/retirement/manifest.json), tests/recovery/retirement/generator.py:130-146 |
