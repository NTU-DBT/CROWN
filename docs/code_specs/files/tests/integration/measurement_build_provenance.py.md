# `tests/integration/measurement_build_provenance.py` — block usage map

[Source](../../../../../tests/integration/measurement_build_provenance.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `fdbaccf2627d33a445c559caf472983b8546e4c343728a1a2ec9c1e95b78507f`. 84 lines partitioned into 4 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/integration/measurement_build_provenance.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | growth insert · [reviewed contract](#b0001) |
| [B0002 · 15–17](../../../../../tests/integration/measurement_build_provenance.py#L15) | Callable definition: def run(command, directory=None): | calls  · [reviewed contract](#b0002) |
| [B0003 · 18–53](../../../../../tests/integration/measurement_build_provenance.py#L18) | declares callable signatures; declares values/defaults or compile-time conditions. | returns 0; value() · [reviewed contract](#b0003) |
| [B0004 · 54–84](../../../../../tests/integration/measurement_build_provenance.py#L54) | declares callable signatures; declares values/defaults or compile-time conditions. | returns 1; 2; 1 loop sites; source comment (unverified): # Execute an actual recorded compiler command without rebuilding its archive. · [reviewed contract](#b0004) |

## B0001

[Lines 1–14](../../../../../tests/integration/measurement_build_provenance.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
from run_measurements import build_provenance
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up the import-time environment and source/compiler inputs for the B03 stale-build fixture. |
| inputs / outputs | Reads source root from sys.argv\[1\], sets sys.dont_write_bytecode, prepends its tools directory to sys.path and imports build_provenance. The following configuration block reads the compiler from sys.argv\[2\]. |
| invariants | This module body runs when imported; it changes only this Python process’s import/cache settings in this span and has no native CROWN account or output yet. |
| ownership | Python owns argv, sys.path and interpreter settings; the imported helper module remains in sys.modules for this process. |
| failure | Missing argv, path-resolution and import failures propagate before fixture execution; no local recovery. |
| cost | Path resolution, import-path insertion and module loading/setup; no explicit subprocess/build call occurs in this span. |
| Design | [tests/integration/measurement_build_provenance.py](../../../../../tests/integration/measurement_build_provenance.py), [tools/run_measurements.py](../../../../../tools/run_measurements.py), CMakeLists.txt:964, tests/integration/measurement_build_provenance.py:1-14 |

## B0002

[Lines 15–17](../../../../../tests/integration/measurement_build_provenance.py#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run(command, directory=None):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute one command used by the stale-build provenance fixture. |
| inputs / outputs | Accepts subprocess-compatible command and optional cwd; captures text stdout/stderr with a 90-second timeout and returns None. The surrounding module, not this helper alone, creates and repeatedly rebuilds a miniature project. |
| invariants | Asserts returncode==0 with command and both channels as diagnostic; python -O disables this status assertion, so the helper then accepts nonzero exits. |
| ownership | The argument sequence is borrowed and no CompletedProcess escapes; subprocess.run waits and owns/closes communication pipes. The enclosing module owns its TemporaryDirectory via with. |
| failure | TimeoutExpired, launch/cwd OSError and text-decoding errors propagate; a nonzero child raises AssertionError only when assertions are enabled. |
| cost | One real configure/build/compiler subprocess, complete channel buffering and optional cwd lookup; the per-call timeout does not bound the full module workflow. |
| Design | [tests/integration/measurement_build_provenance.py](../../../../../tests/integration/measurement_build_provenance.py), [docs/measurement.md](../../../../measurement.md), [tools/run_measurements.py](../../../../../tools/run_measurements.py) |

## B0003

[Lines 18–53](../../../../../tests/integration/measurement_build_provenance.py#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
else: raise AssertionError('stale build was accepted: ' + reason)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create and configure the temporary miniature CMake project used by the stale-link provenance fixture. |
| inputs / outputs | Inside a TemporaryDirectory, creates source/build trees and writes a minimal library, two executables, and CMakeLists; configures using the compiler argument; defines local build/provenance/rejection helpers for the next block. |
| invariants | This is unguarded module-level code: importing the script creates/configures this synthetic project too. The source tree is limited to the named provenance scenarios; this span does not build CROWN or certify arbitrary project build provenance. |
| ownership | The with-scope owns temporary files and removes them on return or exception; child-command failures propagate from the local run helper. |
| failure | File-writing, CMake configure, and helper-definition errors propagate; no local catch recovers or preserves the temporary project. |
| cost | Writes a handful of small files and runs one CMake configure; later block B0004 performs the repeated builds and mutations. |
| Design | [tests/integration/measurement_build_provenance.py](../../../../../tests/integration/measurement_build_provenance.py), [tools/run_measurements.py](../../../../../tools/run_measurements.py), CMakeLists.txt:964, tests/integration/measurement_build_provenance.py:18-53 |

## B0004

[Lines 54–84](../../../../../tests/integration/measurement_build_provenance.py#L54); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
print('Build provenance: actual stale library, one stale executable, stale archive member, changed compiler/link flags rejected; rebuilt closure accepted')
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise stale library/executable/archive and compiler-command cases against the temporary provenance project. |
| inputs / outputs | Calls the local make/provenance helpers, edits the synthetic library, rebuilds selected targets, alters/runs a compile command from compile_commands.json, checks expected rejection reasons, and prints a bounded summary. |
| invariants | This is unguarded module-level code: importing the script runs the builds and mutations too. All checks concern this temporary minimal project, the supplied compiler, and the enumerated cases; they do not establish arbitrary build provenance or measurement validity. |
| ownership | The enclosing TemporaryDirectory removes the synthetic project; no persistent artifact ledger is written. |
| failure | I/O, timeout and unexpected exception failures propagate. Python assertions check child return codes and expected rejection text when enabled; no retry follows a failed check. |
| cost | Several CMake builds, one direct compiler command and file mutations. run() applies 90-second child timeouts; no whole-process CPU/RSS or hard completion bound is established. |
| Design | [tests/integration/measurement_build_provenance.py](../../../../../tests/integration/measurement_build_provenance.py), [tools/run_measurements.py](../../../../../tools/run_measurements.py), CMakeLists.txt:964, tests/integration/measurement_build_provenance.py:54-84 |
