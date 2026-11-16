# `tests/integration/installed_cost_calibration.py` — block usage map

[Source](../../../../../tests/integration/installed_cost_calibration.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `1f46473f0c1c0100f12f205fb7970e3fd9aab6ae4a117c47aec863f3001123a7`. 33 lines partitioned into 5 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../tests/integration/installed_cost_calibration.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 6–7](../../../../../tests/integration/installed_cost_calibration.py#L6) | Callable definition: def require(value,message): | calls RuntimeError; guard def require(value,message): · [reviewed contract](#b0002) |
| [B0003 · 8–11](../../../../../tests/integration/installed_cost_calibration.py#L8) | Callable definition: def run(command): | calls str, require; guard require(result.returncode==0,f'{command}: {result.stderr\[-2500:\]} {result.stdout\[-2500:\]}'); returns result; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 12–30](../../../../../tests/integration/installed_cost_calibration.py#L12) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, Path; guard require((prefix/'share/crown/schemas/cost-calibration-v1.schema.json').is_file(),'calibration schem…; returns 0; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 31–33](../../../../../tests/integration/installed_cost_calibration.py#L31) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |

## B0001

[Lines 1–5](../../../../../tests/integration/installed_cost_calibration.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:da469058d98fdf186d40519f72858350ab149406ed6e7126eedcfa7fbfa3de62
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for installed_cost_calibration.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/installed_cost_calibration.py](../../../../../tests/integration/installed_cost_calibration.py), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 6–7](../../../../../tests/integration/installed_cost_calibration.py#L6); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value,message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an installed-calibration acceptance mismatch. |
| inputs / outputs | Truth-tests value, returning None or raising RuntimeError with message. |
| invariants | The explicit if remains enabled under optimized Python; it asserts only the supplied condition. |
| ownership | Borrows operands and leaves installed files and result objects untouched. |
| failure | False value raises RuntimeError; errors in truth conversion are not translated. |
| cost | One truth conversion, apart from caller-built diagnostic text. |
| Design | [tests/integration/installed_cost_calibration.py](../../../../../tests/integration/installed_cost_calibration.py), [docs/measurement.md](../../../../measurement.md), [tests/integration/cost_calibration.py](../../../../../tests/integration/cost_calibration.py) |

## B0003

[Lines 8–11](../../../../../tests/integration/installed_cost_calibration.py#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run(command):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one SDK install/build/acceptance subprocess and retain its captured result. |
| inputs / outputs | Stringifies command entries; capture_output/text with timeout 240; requires zero exit and returns CompletedProcess. |
| invariants | A successful child may still write stderr; failure diagnostics include only suffixes of both captured channels. |
| ownership | Owns the temporary argument list and subprocess communication buffers; caller receives the result, while subprocess.run waits and closes its pipes. |
| failure | Nonzero exit raises RuntimeError; timeout, launch and text-decoding errors propagate unchanged. |
| cost | One potentially install/build-heavy child and full text buffering; timeout applies per call, not to the whole main workflow. |
| Design | [tests/integration/installed_cost_calibration.py](../../../../../tests/integration/installed_cost_calibration.py), [docs/measurement.md](../../../../measurement.md), [tests/integration/cost_calibration.py](../../../../../tests/integration/cost_calibration.py) |

## B0004

[Lines 12–30](../../../../../tests/integration/installed_cost_calibration.py#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the relocated installed calibration example and delegate SQL/oracle report acceptance to cost_calibration.py. |
| inputs / outputs | Parses source/build/compiler/sanitize; installs into a temporary stage, renames it to a prefix containing spaces, copies the installed example, configures/builds it and invokes the integration driver. Returns 0. |
| invariants | Requires one package config and one native compilation unit, C++23, no source/build header paths and no testing/reference link archive; confirms installed schema. Sanitizer flags are added only for recognized truthy spellings. |
| ownership | Copies installed example files into a private tree and owns the temporary SDK/build artifacts through TemporaryDirectory, which cleans up even on exceptions; source/build inputs are read by commands, not edited by Python. |
| failure | Argparse exits on malformed args; explicit checks raise RuntimeError, child/file/JSON errors propagate to the broad entrypoint Exception handler and exit 1. A failed install/build may have partial private files until context cleanup. |
| cost | Runs install, configure, -j2 build and a full calibration integration child; recursively searches package config and reads compiler/link metadata. This is real subprocess/build/SQL work, not a small conversion. |
| Design | [tests/integration/installed_cost_calibration.py](../../../../../tests/integration/installed_cost_calibration.py), [docs/measurement.md](../../../../measurement.md), [tests/integration/cost_calibration.py](../../../../../tests/integration/cost_calibration.py) |

## B0005

[Lines 31–33](../../../../../tests/integration/installed_cost_calibration.py#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__=='__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Build the relocated installed calibration example and delegate SQL/oracle report acceptance to cost_calibration.py. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Pass the delegated return value to Python SystemExit; main controls that explicit exit status. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only Exception to stdout, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/installed_cost_calibration.py](../../../../../tests/integration/installed_cost_calibration.py), [docs/development.md](../../../../development.md), [docs/measurement.md](../../../../measurement.md), [tests/integration/cost_calibration.py](../../../../../tests/integration/cost_calibration.py) |
