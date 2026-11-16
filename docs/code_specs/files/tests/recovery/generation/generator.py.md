# `tests/recovery/generation/generator.py` — block usage map

[Source](../../../../../../tests/recovery/generation/generator.py) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `ee81bd516e4353ab9fb2fe1189056e8dba7f66d8c7c711f19f797eb4fd4dd986`. 82 lines partitioned into 3 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../../code_review.md), [docs/reference_fuzz.md](../../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../../tests/recovery/generation/generator.py#L1) | Imports dependencies; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 21–46](../../../../../../tests/recovery/generation/generator.py#L21) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): # The fixed 20-byte envelope prefix precedes this 128-byte payload. · [reviewed contract](#b0002) |
| [B0003 · 47–82](../../../../../../tests/recovery/generation/generator.py#L47) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |

## B0001

[Lines 1–20](../../../../../../tests/recovery/generation/generator.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
COMMAND_SEQUENCE = 13
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize fixed CROWNGR1 v1 golden-record constants and output directory. |
| inputs / outputs | Binds OUT to the generator’s own directory and fixed magic/version/flags/query/generation/checkpoint/hash/sequence values. |
| invariants | The module is an eager generator with no main guard; output files are written only in B0003, under OUT rather than cwd. |
| ownership | Module globals own the constants; OUT is a Path and does not own an open file. |
| failure | Hash/path/import errors abort module initialization; no file output or catch in this span. |
| cost | Module imports, source-relative path setup, fixed constants and one SHA-256 of the literal checkpoint payload. |
| Design | [tests/recovery/generation/generator.py](../../../../../../tests/recovery/generation/generator.py), [tests/recovery/generation/manifest.json](../../../../../../tests/recovery/generation/manifest.json), tests/recovery/generation/generator.py:1-20 |

## B0002

[Lines 21–46](../../../../../../tests/recovery/generation/generator.py#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
assert len(record) == 212
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble and length-check the fixed CROWNGR1 v1 payload, protected prefix, and record in memory. |
| inputs / outputs | Packs fixed u16/u64 fields into payload/prefix, computes SHA256 checksum text, and asserts payload/prefix/record lengths 128/148/212. |
| invariants | This constructs one literal golden record. With Python assertions enabled, its local length checks run; they do not validate the native decoder. |
| ownership | Bytes remain in module globals until the output block; no file handle exists here. |
| failure | Packing/hash/allocation errors propagate; a length mismatch raises AssertionError when Python assertions are enabled. No fixture output is written here. |
| cost | Fixed-size concatenation and hashing of one 148-byte prefix. |
| Design | [tests/recovery/generation/generator.py](../../../../../../tests/recovery/generation/generator.py), [tests/recovery/generation/manifest.json](../../../../../../tests/recovery/generation/manifest.json), tests/recovery/generation/generator.py:21-46 |

## B0003

[Lines 47–82](../../../../../../tests/recovery/generation/generator.py#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
print(f"record_sha256={manifest['record_sha256']}")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the CROWNGR1 v1 offset manifest, overwrite the adjacent golden hex/manifest files, and print digests. |
| inputs / outputs | Creates field/manifest dictionaries from the fixed record, writes root.hex then manifest.json under OUT, and prints byte lengths and hashes. |
| invariants | Writes are sequential and not staged atomically; importing the module executes them, and each fixed target is truncated/replaced. |
| ownership | The output directory belongs to the test fixture; record/manifest objects and their text encodings are temporary Python-owned values. |
| failure | Serialization/write/stdout errors propagate; if the second write fails, root.hex may already have been replaced and the old manifest may remain. |
| cost | Serializes one small record and manifest; two fixed-file writes and four digest/size print calls. |
| Design | [tests/recovery/generation/generator.py](../../../../../../tests/recovery/generation/generator.py), [tests/recovery/generation/manifest.json](../../../../../../tests/recovery/generation/manifest.json), tests/recovery/generation/generator.py:47-82 |
