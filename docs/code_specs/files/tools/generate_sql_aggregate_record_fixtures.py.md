# `tools/generate_sql_aggregate_record_fixtures.py` — block usage map

[Source](../../../../tools/generate_sql_aggregate_record_fixtures.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `fc5f77b61d4ef881102734b0fc54030bb2bc5d9849feb909746eebd5965c05fb`. 69 lines partitioned into 11 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../tools/generate_sql_aggregate_record_fixtures.py#L1) | Imports dependencies; declares types or opens a type body. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 15–17](../../../../tools/generate_sql_aggregate_record_fixtures.py#L15) | Callable definition: def word(value, width=8): | calls to_bytes; returns value.to_bytes(width, "little") · [reviewed contract](#b0002) |
| [B0003 · 18–19](../../../../tools/generate_sql_aggregate_record_fixtures.py#L18) | Explanatory comments or spacing. |  |
| [B0004 · 20–25](../../../../tools/generate_sql_aggregate_record_fixtures.py#L20) | Callable definition: def frame(kind, ordinal, payload): | calls word, len, sha256, hexdigest; returns prefix + hashlib.sha256(prefix).hexdigest().encode("ascii") + body · [reviewed contract](#b0004) |
| [B0005 · 26–27](../../../../tools/generate_sql_aggregate_record_fixtures.py#L26) | Explanatory comments or spacing. |  |
| [B0006 · 28–31](../../../../tools/generate_sql_aggregate_record_fixtures.py#L28) | Callable definition: def text(value): | calls encode, word, len; returns b"\x01\x01" + word(len(data)) + data · [reviewed contract](#b0006) |
| [B0007 · 32–33](../../../../tools/generate_sql_aggregate_record_fixtures.py#L32) | Explanatory comments or spacing. |  |
| [B0008 · 34–36](../../../../tools/generate_sql_aggregate_record_fixtures.py#L34) | Callable definition: def integer(value): | calls pack; returns b"\x01\x00" + struct.pack("&lt;q", value) · [reviewed contract](#b0008) |
| [B0009 · 37–38](../../../../tools/generate_sql_aggregate_record_fixtures.py#L37) | Explanatory comments or spacing. |  |
| [B0010 · 39–62](../../../../tools/generate_sql_aggregate_record_fixtures.py#L39) | Callable definition: def fixtures(): | calls frame, word, date, text; returns {"wal-header": header, "input": command, "commit": commit, "reject": reject, · [reviewed contract](#b0010) |
| [B0011 · 63–69](../../../../tools/generate_sql_aggregate_record_fixtures.py#L63) | declares values/defaults or compile-time conditions. | 1 loop sites · [reviewed contract](#b0011) |

## B0001

[Lines 1–14](../../../../tools/generate_sql_aggregate_record_fixtures.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:1d7966663547e844b786120039cf1ce729a9e6f217b03a28946e0b9d323148a4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for generate_sql_aggregate_record_fixtures.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tools/generate_sql_aggregate_record_fixtures.py](../../../../tools/generate_sql_aggregate_record_fixtures.py), [docs/aggregates.md](../../../aggregates.md), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 15–17](../../../../tools/generate_sql_aggregate_record_fixtures.py#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def word(value, width=8):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an unsigned fixed-width integer in little-endian order. |
| inputs / outputs | Declaration: \`def word(value, width=8):\`. Inputs/outputs: Encode an unsigned fixed-width integer in little-endian order. |
| invariants | Uses Python int.to_bytes and returns a new bytes value; invalid width/value raises Python's own conversion exception. |
| ownership | Returns a new immutable bytes sequence. |
| failure | Uses only Python standard-library conversion/hash/date operations; Python conversion, indexing or struct errors propagate. |
| cost | One integer-to-bytes conversion at requested width. |
| Design | [tools/generate_sql_aggregate_record_fixtures.py](../../../../tools/generate_sql_aggregate_record_fixtures.py), [docs/sql_aggregate_records.md § Wire contract](../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../sql_aggregate_records.md) |

## B0004

[Lines 20–25](../../../../tools/generate_sql_aggregate_record_fixtures.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def frame(kind, ordinal, payload):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble one exact R2 frame prefix/body and bind their byte lengths and SHA256 digests. |
| inputs / outputs | Declaration: \`def frame(kind, ordinal, payload):\`. Inputs/outputs: Assemble one exact R2 frame prefix/body and bind their byte lengths and SHA256 digests. |
| invariants | Returns new immutable bytes; integer/hash/sequence logic here is an independent local wire oracle, not production admission. |
| ownership | Returns newly concatenated immutable frame bytes. |
| failure | Uses only Python standard-library conversion/hash/date operations; Python conversion, indexing or struct errors propagate. |
| cost | Concatenates one frame from fixed prefix/body pieces and computes two SHA256 digests. |
| Design | [tools/generate_sql_aggregate_record_fixtures.py](../../../../tools/generate_sql_aggregate_record_fixtures.py), [docs/sql_aggregate_records.md § Wire contract](../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../sql_aggregate_records.md) |

## B0006

[Lines 28–31](../../../../tools/generate_sql_aggregate_record_fixtures.py#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def text(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a present UTF8 TEXT scalar with its byte length. |
| inputs / outputs | Declaration: \`def text(value):\`. Inputs/outputs: Encode a present UTF8 TEXT scalar with its byte length. |
| invariants | UTF8 encoding owns new bytes and length is UTF8 byte count, not Python character count. |
| ownership | Returns UTF8 bytes newly allocated from the string argument. |
| failure | Uses only Python standard-library conversion/hash/date operations; Python conversion, indexing or struct errors propagate. |
| cost | UTF8-encodes one supplied string. |
| Design | [tools/generate_sql_aggregate_record_fixtures.py](../../../../tools/generate_sql_aggregate_record_fixtures.py), [docs/sql_aggregate_records.md § Wire contract](../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../sql_aggregate_records.md) |

## B0008

[Lines 34–36](../../../../tools/generate_sql_aggregate_record_fixtures.py#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def integer(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a present signed int64 scalar as little-endian two's-complement bits. |
| inputs / outputs | Declaration: \`def integer(value):\`. Inputs/outputs: Encode a present signed int64 scalar as little-endian two's-complement bits. |
| invariants | struct.pack('&lt;q') owns the signed int64 representation; values outside int64 raise struct.error. |
| ownership | Returns packed immutable bytes. |
| failure | Uses only Python standard-library conversion/hash/date operations; Python conversion, indexing or struct errors propagate. |
| cost | Packs one signed 64-bit integer. |
| Design | [tools/generate_sql_aggregate_record_fixtures.py](../../../../tools/generate_sql_aggregate_record_fixtures.py), [docs/sql_aggregate_records.md § Wire contract](../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../sql_aggregate_records.md) |

## B0010

[Lines 39–62](../../../../tools/generate_sql_aggregate_record_fixtures.py#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def fixtures():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct seven independent full-byte transport goldens for headers, input, decisions, and group epochs. |
| inputs / outputs | Declaration: \`def fixtures():\`. Inputs/outputs: Construct seven independent full-byte transport goldens for headers, input, decisions, and group epochs. |
| invariants | Returns seven immutable bytes fixtures built without C++ bindings; the output covers one value per kind plus the empty group epoch, not exhaustive validation. |
| ownership | Returns a new dict whose values are independent immutable bytes objects. |
| failure | Uses only Python standard-library conversion/hash/date operations; Python conversion, indexing or struct errors propagate. |
| cost | Constructs seven small fixture byte strings and hashes their framed bodies. |
| Design | [tools/generate_sql_aggregate_record_fixtures.py](../../../../tools/generate_sql_aggregate_record_fixtures.py), [docs/sql_aggregate_records.md § Wire contract](../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Inspection and verification](../../../sql_aggregate_records.md) |

## B0011

[Lines 63–69](../../../../tools/generate_sql_aggregate_record_fixtures.py#L63); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write the independent R2 record-golden dictionary as named ASCII hex fixtures when this generator is executed as a script. |
| inputs / outputs | Read destination from sys.argv\[1\], create that directory, call fixtures(), then write each name.hex as lowercase hex plus newline. Existing same-named files are replaced; unrelated files are not removed. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The caller chooses the persistent destination through argv\[1\]. This guarded block creates its directory and writes same-named hex files there; it leaves unrelated files alone. These Python/filesystem objects create no native query account or publication authority. |
| failure | Missing argv, fixture encoding, directory creation or file-write errors propagate. Writes are per file, so a later failure can leave an already written prefix; this is not native transactional publication. |
| cost | One directory creation attempt plus one hex allocation and file write per fixture; work/temporary Python memory scale with all generated byte lengths and filesystem costs. |
| Design | [tools/generate_sql_aggregate_record_fixtures.py](../../../../tools/generate_sql_aggregate_record_fixtures.py), [docs/sql_aggregate_records.md](../../../sql_aggregate_records.md), [docs/development.md](../../../development.md) |
