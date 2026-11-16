# `tests/integration/clean_source_snapshot.py` — block usage map

[Source](../../../../../tests/integration/clean_source_snapshot.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `615f2b0a277e473026687ac272d481a6edc86b4807832b84fe6ce0c7b466989f`. 85 lines partitioned into 5 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–27](../../../../../tests/integration/clean_source_snapshot.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): # These are the current explicit documentation inputs to CrownInstall.cmake. · [reviewed contract](#b0001) |
| [B0002 · 28–31](../../../../../tests/integration/clean_source_snapshot.py#L28) | Callable definition: def require_install_inputs(source): | calls assert, is_file; guard assert (source / name).is_file(), name; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 32–33](../../../../../tests/integration/clean_source_snapshot.py#L32) | Explanatory comments or spacing. |  |
| [B0004 · 34–58](../../../../../tests/integration/clean_source_snapshot.py#L34) | Callable definition: def check_install_fixture(): | calls TemporaryDirectory, Path, mkdir, in; guard assert (snapshot / name).read_bytes() == (repository / name).read_bytes(), name; 3 loop sites; source comment (unverified): # Current requirements are explicit; historical evidence retains its exact pin. · [reviewed contract](#b0004) |
| [B0005 · 59–85](../../../../../tests/integration/clean_source_snapshot.py#L59) | declares callable signatures; declares values/defaults or compile-time conditions. | guard assert (source / required).is_file(), required; 3 loop sites · [reviewed contract](#b0005) |

## B0001

[Lines 1–27](../../../../../tests/integration/clean_source_snapshot.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L27:sha256:414d3fb3e5793e5e281647e042b63484352fc860f2f0f93af390bc07055af0ed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse clean-source preflight scope and load the actual copier. |
| inputs / outputs | Source argument and optional --install-inputs-only produce an imported verify_clean_build module and current install/current-plan/historical-plan path constants. |
| invariants | Disable bytecode writes before local imports. Flags and definitions run at module import; the install-only branch is later and must precede CMake commands. |
| ownership | Python owns parsed paths/module and constant tuples. |
| failure | Argument/import/path failures propagate; this scaffold itself performs no native command. |
| cost | Module/path setup and import work, without recursive copying here. |
| Design | [tests/integration/clean_source_snapshot.py](../../../../../tests/integration/clean_source_snapshot.py), [tools/verify_clean_build.py](../../../../../tools/verify_clean_build.py), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [docs/native_build.md](../../../../native_build.md) |

## B0002

[Lines 28–31](../../../../../tests/integration/clean_source_snapshot.py#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L31:sha256:47c4fea7b8eb783e056aa6f59426a1a6a836777f14785595380f65479413edeb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require both current SDK install documents in a source snapshot. |
| inputs / outputs | Snapshot root in; assert each INSTALL_INPUTS member is a regular file. |
| invariants | A regular file test is closure evidence, not byte equivalence or native correctness. Run Python with assertions enabled. |
| ownership | Borrow path, retain no state. |
| failure | Missing document raises AssertionError with its path. |
| cost | Two filesystem file-status checks. |
| Design | [tests/integration/clean_source_snapshot.py](../../../../../tests/integration/clean_source_snapshot.py), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake) |

## B0004

[Lines 34–58](../../../../../tests/integration/clean_source_snapshot.py#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L58:sha256:ba3eb6b47b9a7cbcc36dab2f5215786d45fe15cdcbf9e49844ae99759cf830e6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise actual snapshot copying and a missing-install-document negative. |
| inputs / outputs | Create synthetic repositories for the actual six root files and eleven directory constants, with both install docs and distinct current/archived plans; call copy_snapshot, compare four selected leaf bytes, remove the aggregate install doc and require rejection. |
| invariants | Synthetic files are copier test inputs, not native proof or changed historical evidence. The repository/docs directory is created before its leaves, and snapshot/docs is initially absent because SOURCE_FILES contains root-only leaves; the one docs copytree therefore has no collision. This fixture does not pretend to exercise all R1 required docs. |
| ownership | TemporaryDirectory owns source/snapshot and cleans both on exit. |
| failure | Copy/I/O/hash/assert failures propagate; only the intentionally missing-doc assertion is caught and checked. |
| cost | Copy finite synthetic tree, hash archived bytes and compare four selected members; no CMake/native execution. |
| Design | [tests/integration/clean_source_snapshot.py](../../../../../tests/integration/clean_source_snapshot.py), [tools/verify_clean_build.py](../../../../../tools/verify_clean_build.py), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake) |

## B0005

[Lines 59–85](../../../../../tests/integration/clean_source_snapshot.py#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
print('Clean-source closure: real configure, examples/install inputs, 122 pinned baseline files, workload/import/ranking manifests')
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the registered clean-source preflight in a temporary copy of the repository. |
| inputs / outputs | Parse source and optional --install-inputs-only. The synthetic copier control always runs; that flag exits before CMake. Default real-copy mode additionally requires README.md, .gitignore, docs/experimental_report.md and docs/releases/r1.md, then configures and runs three static Python verifiers. |
| invariants | Module executes on import, with assertions-enabled Python required. Install-only checks stay separate from default full source/docs closure; current and archived plans retain distinct byte/provenance contracts. This is configure/static preflight, not a full release build or packaging acceptance. |
| ownership | TemporaryDirectory attempts cleanup during normal or exceptional unwinding; Python owns copied paths and captured child output. |
| failure | Import/copy/I/O failures and subprocess timeouts propagate. A nonzero configure/verifier result fails through a Python assertion when assertions are enabled; the subprocess call itself uses check=False. |
| cost | Copies the full filtered source/docs inventory and checks the expanded required-path list, then runs one CMake configure plus three Python commands, each with a90-second timeout. Actual copied bytes, captured output and host tools govern cost. |
| Design | [tests/integration/clean_source_snapshot.py](../../../../../tests/integration/clean_source_snapshot.py), [tools/verify_clean_build.py](../../../../../tools/verify_clean_build.py), CMakeLists.txt:962, [docs/native_build.md](../../../../native_build.md), tests/integration/clean_source_snapshot.py:1-84 |
