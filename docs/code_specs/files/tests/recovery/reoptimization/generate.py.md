# `tests/recovery/reoptimization/generate.py` — block usage map

[Source](../../../../../../tests/recovery/reoptimization/generate.py) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `6233535e190ea078e86a9eff5222be6c1f8ec5a5d3e83d6d1c1fb16106979cad`. 47 lines partitioned into 7 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../../code_review.md), [docs/reference_fuzz.md](../../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../tests/recovery/reoptimization/generate.py#L1) | Imports dependencies; declares aliases; declares types or opens a type body. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 9–10](../../../../../../tests/recovery/reoptimization/generate.py#L9) | Callable definition: def digest(value): | calls sha256, hexdigest, encode; returns hashlib.sha256(value).hexdigest().encode("ascii") · [reviewed contract](#b0002) |
| [B0003 · 11–12](../../../../../../tests/recovery/reoptimization/generate.py#L11) | Explanatory comments or spacing. |  |
| [B0004 · 13–29](../../../../../../tests/recovery/reoptimization/generate.py#L13) | Callable definition: def packet(seed): | calls len, sha256, hexdigest, unpack_from; returns result; source comment (unverified): # query, generation/floor, checkpoint hash, two frontiers · [reviewed contract](#b0004) |
| [B0005 · 30–31](../../../../../../tests/recovery/reoptimization/generate.py#L30) | Explanatory comments or spacing. |  |
| [B0006 · 32–43](../../../../../../tests/recovery/reoptimization/generate.py#L32) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, Path · [reviewed contract](#b0006) |
| [B0007 · 44–47](../../../../../../tests/recovery/reoptimization/generate.py#L44) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |

## B0001

[Lines 1–8](../../../../../../tests/recovery/reoptimization/generate.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:05ff070244ae0179a3c3999e055ade72615bf1dc2671233bae3b745a5cb05295
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for generate.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/recovery/reoptimization/generate.py](../../../../../../tests/recovery/reoptimization/generate.py), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 9–10](../../../../../../tests/recovery/reoptimization/generate.py#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def digest(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the ASCII-byte SHA-256 field used by the descriptor golden. |
| inputs / outputs | Returns 64 lowercase ASCII bytes for the complete supplied byte buffer. |
| invariants | This binary helper differs from hexdigest str helpers; no descriptor validation is implied. |
| ownership | Owns newly encoded digest bytes and only borrows the input buffer. |
| failure | hashlib/ASCII buffer errors propagate. |
| cost | Linear in input bytes plus fixed 64-byte hex encoding. |
| Design | [tests/recovery/reoptimization/generate.py](../../../../../../tests/recovery/reoptimization/generate.py), [docs/reoptimization.md](../../../../../reoptimization.md), [tests/recovery/retirement/intent.hex](../../../../../../tests/recovery/retirement/intent.hex) |

## B0004

[Lines 13–29](../../../../../../tests/recovery/reoptimization/generate.py#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def packet(seed):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the independent CROWNPL1 fixture from a pinned retirement intent. |
| inputs / outputs | Validates the 724-byte seed/hash/layout, extracts root/sink/binding spans, constructs a target binding and fake compiler artifact, returns a 1529-byte descriptor. |
| invariants | assert pins the exact seed, command frontier 13 and final size; artifact is golden-test-only, not an admitted native compiler program. Assertions can be disabled by -O. |
| ownership | Byte slices and concatenations create new immutable data; seed remains unchanged. |
| failure | Enabled assertion, struct unpack and buffer/type errors propagate; no files are changed. |
| cost | Slices fixed seed spans, assembles full body and hashes seed/target/descriptor; output size is fixed for this fixture. |
| Design | [tests/recovery/reoptimization/generate.py](../../../../../../tests/recovery/reoptimization/generate.py), [docs/reoptimization.md](../../../../../reoptimization.md), [tests/recovery/retirement/intent.hex](../../../../../../tests/recovery/retirement/intent.hex) |

## B0006

[Lines 32–43](../../../../../../tests/recovery/reoptimization/generate.py#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the independent descriptor golden or explicitly replace it with --write. |
| inputs / outputs | argparse reads --write, loads retirement/intent.hex, computes packet, then compares descriptor-v1.hex or overwrites it and prints PASS. |
| invariants | Default mode is comparison only; --write opts into replacement. Equality is an assert and therefore absent under -O. |
| ownership | Owns read/decoded/generated bytes and local Paths; no native child or temporary directory is created. |
| failure | argparse usage exits 2; read/hex errors and enabled assertions propagate; writes are direct with no rollback. |
| cost | Whole seed/golden reads, hex decoding/encoding, packet hashes and optional file overwrite; no native codec is invoked. |
| Design | [tests/recovery/reoptimization/generate.py](../../../../../../tests/recovery/reoptimization/generate.py), [docs/reoptimization.md](../../../../../reoptimization.md), [tests/recovery/retirement/intent.hex](../../../../../../tests/recovery/retirement/intent.hex) |

## B0007

[Lines 44–47](../../../../../../tests/recovery/reoptimization/generate.py#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Check the independent descriptor golden or explicitly replace it with --write. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | No presentation catch is added here: main/fixture failures and SystemExit propagate through the interpreter. This block supplies no extra retry or rollback. Delegated main replaces its golden only with --write; the wrapper adds no atomic replacement or rollback guarantee. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. |
| Design | [tests/recovery/reoptimization/generate.py](../../../../../../tests/recovery/reoptimization/generate.py), [docs/development.md](../../../../../development.md), [docs/reoptimization.md](../../../../../reoptimization.md), [tests/recovery/retirement/intent.hex](../../../../../../tests/recovery/retirement/intent.hex) |
