# `tests/recovery/journal/partial-metadata-fixture.py` — block usage map

[Source](../../../../../../tests/recovery/journal/partial-metadata-fixture.py) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `1c16507722dbe1053e464bf1fcb0301eb8209e7f508a772fd2280d0036e6cd7b`. 206 lines partitioned into 14 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../../code_review.md), [docs/reference_fuzz.md](../../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–34](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L1) | Imports dependencies; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 35–42](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L35) | declares values/defaults or compile-time conditions. | source comment (unverified): # The 26 policy words from the maintained format.json default_policy. · [reviewed contract](#b0002) |
| [B0003 · 43–44](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L43) | Callable definition: def u8(value: int) -&gt; bytes: | calls pack; returns struct.pack("&lt;B", value) · [reviewed contract](#b0003) |
| [B0004 · 45–46](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L45) | Explanatory comments or spacing. |  |
| [B0005 · 47–48](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L47) | Callable definition: def u16(value: int) -&gt; bytes: | calls pack; returns struct.pack("&lt;H", value) · [reviewed contract](#b0005) |
| [B0006 · 49–50](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L49) | Explanatory comments or spacing. |  |
| [B0007 · 51–52](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L51) | Callable definition: def u64(value: int) -&gt; bytes: | calls pack; returns struct.pack("&lt;Q", value) · [reviewed contract](#b0007) |
| [B0008 · 53–54](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L53) | Explanatory comments or spacing. |  |
| [B0009 · 55–56](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L55) | Callable definition: def digest_hex(data: bytes) -&gt; str: | calls sha256, hexdigest; returns hashlib.sha256(data).hexdigest() · [reviewed contract](#b0009) |
| [B0010 · 57–58](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L57) | Explanatory comments or spacing. |  |
| [B0011 · 59–71](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L59) | Callable definition: def make_frame(kind: int, ordinal: int, payload: bytes) -&gt; tuple\[bytes, str, str\]: | calls u8, u64, u16, len; returns frame, digest_hex(body), digest_hex(frame) · [reviewed contract](#b0011) |
| [B0012 · 72–73](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L72) | Explanatory comments or spacing. |  |
| [B0013 · 74–202](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L74) | Callable definition: def main() -&gt; None: | calls len, fromhex, read_text, strip; 5 loop sites; source comment (unverified): # Confirm the golden header payload matches byte-for-byte apart from the · [reviewed contract](#b0013) |
| [B0014 · 203–206](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L203) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0014) |

## B0001

[Lines 1–34](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L34:sha256:ddd0206c692fc91e6e5799efcdbf8a78147ef77d2aaaf4c183bfd43b0ecc94be
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for partial-metadata-fixture.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/recovery/journal/partial-metadata-fixture.py](../../../../../../tests/recovery/journal/partial-metadata-fixture.py), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 35–42](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L42:sha256:27f291fb842424fccad8a953f0579a06e876fd4e31423b10468e9657df5edf86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for partial-metadata-fixture.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/recovery/journal/partial-metadata-fixture.py](../../../../../../tests/recovery/journal/partial-metadata-fixture.py), [docs/session-journal.md](../../../../../session-journal.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 43–44](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L43); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/recovery/journal/partial-metadata-fixture.py](../../../../../../tests/recovery/journal/partial-metadata-fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0005

[Lines 47–48](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L47); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/recovery/journal/partial-metadata-fixture.py](../../../../../../tests/recovery/journal/partial-metadata-fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0007

[Lines 51–52](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L51); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/recovery/journal/partial-metadata-fixture.py](../../../../../../tests/recovery/journal/partial-metadata-fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0009

[Lines 55–56](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def digest_hex(data: bytes) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute a lowercase SHA-256 text fingerprint for fixture bytes. |
| inputs / outputs | Accepts a bytes-like buffer and returns a fresh 64-character hexadecimal string. |
| invariants | Hashes the supplied bytes exactly; it does not validate framing or confer receipt/native authority. |
| ownership | Reads the borrowed buffer synchronously and returns independent digest text. |
| failure | hashlib buffer/type errors propagate; this helper performs no I/O. |
| cost | Linear hashing over the entire buffer plus fixed-size digest rendering. |
| Design | [tests/recovery/journal/partial-metadata-fixture.py](../../../../../../tests/recovery/journal/partial-metadata-fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0011

[Lines 59–71](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def make_frame(kind: int, ordinal: int, payload: bytes) -> tuple[bytes, str, str]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one independently framed partial-window WAL record. |
| inputs / outputs | Combines kind/ordinal/payload, hashes body/prefix/frame and returns frame bytes plus body and frame hex digests. |
| invariants | assert checks 84-byte prefix and 148+body total; these assertions disappear under python -O. Kind/stream transition semantics are supplied by caller. |
| ownership | Creates new bytes/digest strings and borrows the immutable payload. |
| failure | Packing failures propagate; length assertions raise AssertionError when enabled. |
| cost | Hashes/copies complete payload/body/frame several times; cost is linear in their lengths. |
| Design | [tests/recovery/journal/partial-metadata-fixture.py](../../../../../../tests/recovery/journal/partial-metadata-fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0013

[Lines 74–202](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write a corrected window continuation stream with a nonfinal metadata-only substep. |
| inputs / outputs | Reads golden header, builds header at C2/I5, Input 6, metadata substep preserving C2/I5 and final physical C3/I6; writes hex and manifest. |
| invariants | Assertions check 26 policy words, exact 467-byte header payload, golden equality except base/input-kind fields and record lengths; assertions are disabled by -O. |
| ownership | Mutates a private bytearray copy of golden payload; owns frame/manifest lists and directly overwrites two output files. |
| failure | Read/hex/packing errors propagate; enabled assertions fail before or after some fixture preparation/writes; no rollback is supplied. |
| cost | Reads/hashes golden/spec/source bytes, assembles and hashes four frames, joins/hex-expands the stream and serializes the manifest. |
| Design | [tests/recovery/journal/partial-metadata-fixture.py](../../../../../../tests/recovery/journal/partial-metadata-fixture.py), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |

## B0014

[Lines 203–206](../../../../../../tests/recovery/journal/partial-metadata-fixture.py#L203); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Write a corrected window continuation stream with a nonfinal metadata-only substep. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | No presentation catch is added here: main/fixture failures and SystemExit propagate through the interpreter. This block supplies no extra retry or rollback. Delegated main writes the stream and then its manifest; those two file writes are not one atomic update. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. |
| Design | [tests/recovery/journal/partial-metadata-fixture.py](../../../../../../tests/recovery/journal/partial-metadata-fixture.py), [docs/development.md](../../../../../development.md), [tests/recovery/journal/format.json](../../../../../../tests/recovery/journal/format.json), [docs/journal-files.md](../../../../../journal-files.md) |
