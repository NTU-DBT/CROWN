# `tests/integration/sql_aggregate_checkpoint_wire.py` — block usage map

[Source](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `5f383feff337ca63a5fb0438d0fcb8c2e536659f0e3e3f3849058f439927a9e3`. 77 lines partitioned into 15 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L1) | Imports dependencies; declares aliases; declares types or opens a type body. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 17–18](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L17) | Callable definition: def word(value): | calls pack; returns struct.pack("&lt;Q", value) · [reviewed contract](#b0002) |
| [B0003 · 19–20](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L19) | Explanatory comments or spacing. |  |
| [B0004 · 21–22](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L21) | Callable definition: def integer(value): | calls pack; returns b"\x01\x00" + struct.pack("&lt;q", value) · [reviewed contract](#b0004) |
| [B0005 · 23–24](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L23) | Explanatory comments or spacing. |  |
| [B0006 · 25–27](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L25) | Callable definition: def text(value): | calls encode, word, len; returns b"\x01\x01" + word(len(data)) + data · [reviewed contract](#b0006) |
| [B0007 · 28–29](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L28) | Explanatory comments or spacing. |  |
| [B0008 · 30–32](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L30) | Callable definition: def date(value): | calls fromisoformat, pack; returns b"\x01\x03" + struct.pack("&lt;i", days) · [reviewed contract](#b0008) |
| [B0009 · 33–34](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L33) | Explanatory comments or spacing. |  |
| [B0010 · 35–37](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L35) | Callable definition: def decimal(value): | calls encode, bytes, len; returns b"\x01\x04" + bytes(\[len(data)\]) + data · [reviewed contract](#b0010) |
| [B0011 · 38–39](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L38) | Explanatory comments or spacing. |  |
| [B0012 · 40–57](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L40) | Callable definition: def expected(descriptor): | calls sha256, hexdigest, encode, word; returns prefix + hashlib.sha256(prefix).hexdigest().encode("ascii") + body; 2 loop sites; source comment (unverified): # Numeric TableId, then exact nullable row-wire order. Weight is not a key. · [reviewed contract](#b0012) |
| [B0013 · 58–59](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L58) | Explanatory comments or spacing. |  |
| [B0014 · 60–73](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L60) | Callable definition: def main(): | calls RuntimeError, ArgumentParser, add_argument, parse_args · [reviewed contract](#b0014) |
| [B0015 · 74–77](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L74) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |

## B0001

[Lines 1–16](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:dc3f58fbf7c054b3367697c44b0866ca82e7ac9ecd1cab7ab431618fd0fb8998
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for sql_aggregate_checkpoint_wire.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/sql_aggregate_checkpoint_wire.py](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 17–18](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def word(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one unsigned little-endian 64-bit wire word. |
| inputs / outputs | Python integer in; exactly eight \`struct.pack\` bytes out. |
| invariants | Fixture values are within uint64 and byte order is explicit; this helper does not call the native codec. |
| ownership | Returns a new immutable bytes value. |
| failure | struct range/type failures propagate. |
| cost | Constant eight-byte work. |
| Design | [tests/integration/sql_aggregate_checkpoint_wire.py](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md) |

## B0004

[Lines 21–22](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def integer(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a present signed int64 scalar using the declared checkpoint scalar tag. |
| inputs / outputs | Signed integer in; presence/type tag plus eight little-endian signed bytes out. |
| invariants | The representation is independently spelled out and agrees with the fixture’s declared SQL type. |
| ownership | Returns owned bytes. |
| failure | struct range errors propagate. |
| cost | Constant ten-byte encoding. |
| Design | [tests/integration/sql_aggregate_checkpoint_wire.py](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md) |

## B0006

[Lines 25–27](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def text(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a present UTF8 TEXT fixture cell with length prefix. |
| inputs / outputs | Python str in; tag, word byte length and UTF8 bytes out. |
| invariants | Length counts encoded bytes, not Unicode code points; fixed test text is canonical. |
| ownership | Returns an owned concatenated bytes object. |
| failure | UTF8 encode errors propagate. |
| cost | O(encoded text length) plus concatenation. |
| Design | [tests/integration/sql_aggregate_checkpoint_wire.py](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md) |

## B0008

[Lines 30–32](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def date(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a canonical date as signed days from the Unix epoch. |
| inputs / outputs | ISO date string in; tag and signed little-endian int32 day count out. |
| invariants | Uses \`datetime.date\` calendar rules and explicit 1970-01-01 epoch, independent of native serializer. |
| ownership | Returns immutable bytes. |
| failure | Malformed dates/range/packing errors propagate. |
| cost | Constant date parse/arithmetic. |
| Design | [tests/integration/sql_aggregate_checkpoint_wire.py](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md) |

## B0010

[Lines 35–37](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def decimal(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode canonical fixed decimal ASCII representation in this fixture. |
| inputs / outputs | Decimal text in; tag, one-byte encoded length and ASCII bytes out. |
| invariants | Fixture precision/scale/ASCII spelling is exact; this helper does not parse or authorize arbitrary decimal policies. |
| ownership | Returns immutable bytes. |
| failure | Non-ASCII or unsupported length fails during encode/bytes construction. |
| cost | O(decimal spelling length). |
| Design | [tests/integration/sql_aggregate_checkpoint_wire.py](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md) |

## B0012

[Lines 40–57](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def expected(descriptor):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently reconstruct the exact expected CROWNAC2 bytes for the emitted fixed fixture. |
| inputs / outputs | Opaque descriptor bytes in; computes expected metadata/source positions/tables/nullable rows/weights, body digest and prefix digest, returning complete frame. |
| invariants | Hard-coded fixture metadata/rows and Python stdlib encoders define the expected wire without importing native decoder logic; row sort uses complete row-wire bytes; descriptor identity hashes its exact bytes. |
| ownership | All intermediate and returned Python bytes are ordinary temporary owners. |
| failure | Python packing/hash errors propagate; exact mismatch is detected by main. |
| cost | Builds complete body plus hashes through several linear byte concatenations; bounded fixed fixture only. |
| Design | [tests/integration/sql_aggregate_checkpoint_wire.py](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py), [docs/sql_aggregate_checkpoint.md §Wire contract](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_checkpoint.md §Verification boundaries](../../../../sql_aggregate_checkpoint.md) |

## B0014

[Lines 60–73](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the native fixture emitter and compare its entire checkpoint file to independent Python reconstruction. |
| inputs / outputs | Requires assertions enabled, driver path; launches one temporary subprocess, reads descriptor/checkpoint bytes and checks exact byte equality. |
| invariants | TemporaryDirectory owns fixture files; descriptor is hashed opaquely and no wire bytes are treated as sink/fsync evidence. |
| ownership | Captured subprocess output and file bytes live in the Python scope; directory is removed on exit. |
| failure | Nonzero native exit or any byte mismatch fails assertion; subprocess timeout is 300 seconds. |
| cost | One native fixture execution plus complete Python frame reconstruction and exact-byte comparison. |
| Design | [tests/integration/sql_aggregate_checkpoint_wire.py](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py), [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/sql_aggregate_checkpoint.md §Verification boundaries](../../../../sql_aggregate_checkpoint.md) |

## B0015

[Lines 74–77](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py#L74); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Run the native fixture emitter and compare its entire checkpoint file to independent Python reconstruction. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | No presentation catch is added here: main/fixture failures and SystemExit propagate through the interpreter. This block supplies no extra retry or rollback. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. |
| Design | [tests/integration/sql_aggregate_checkpoint_wire.py](../../../../../tests/integration/sql_aggregate_checkpoint_wire.py), [docs/development.md](../../../../development.md), [tests/unit/sql_aggregate_checkpoint_test.cpp](../../../../../tests/unit/sql_aggregate_checkpoint_test.cpp), [docs/sql_aggregate_checkpoint.md §Verification boundaries](../../../../sql_aggregate_checkpoint.md) |
