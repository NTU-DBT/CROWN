# `tools/verify_clean_build.py` — block usage map

[Source](../../../../tools/verify_clean_build.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `9bcb810dc3fbf43aabbe3fdf54efa161a542abb15051a84ba95aede88bbff8e0`. 247 lines partitioned into 18 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–36](../../../../tools/verify_clean_build.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 37–41](../../../../tools/verify_clean_build.py#L37) | declares types or opens a type body. |  · [reviewed contract](#b0002) |
| [B0003 · 42–49](../../../../tools/verify_clean_build.py#L42) | Callable definition: def positive_int(value: str) -&gt; int: | calls int, ArgumentTypeError; returns number · [reviewed contract](#b0003) |
| [B0004 · 50–51](../../../../tools/verify_clean_build.py#L50) | Explanatory comments or spacing. |  |
| [B0005 · 52–73](../../../../tools/verify_clean_build.py#L52) | Callable definition: def parse_args(argv: list\[str\] \| None = None) -&gt; argparse.Namespace: | calls ArgumentParser, add_argument, configuration, jobs; returns parser.parse_args(argv) · [reviewed contract](#b0005) |
| [B0006 · 74–75](../../../../tools/verify_clean_build.py#L74) | Explanatory comments or spacing. |  |
| [B0007 · 76–81](../../../../tools/verify_clean_build.py#L76) | Callable definition: def ignore_snapshot_entries(_directory: str, names: list\[str\]) -&gt; set\[str\]: | calls endswith; returns {; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 82–84](../../../../tools/verify_clean_build.py#L82) | Module statements. | source comment (unverified): # Copy only the explicit source inventory and legacy files, excluding build/cache basenames. · [reviewed contract](#b0008) |
| [B0009 · 85–114](../../../../tools/verify_clean_build.py#L85) | Callable definition: def copy_snapshot(repository: Path, source: Path, log: TextIO) -&gt; None: | calls copy_file, Path, is_absolute, VerificationError; 3 loop sites; source comment (unverified): # B02 checks these exact pinned baseline inputs, not whole legacy projects. · [reviewed contract](#b0009) |
| [B0010 · 115–116](../../../../tools/verify_clean_build.py#L115) | Explanatory comments or spacing. |  |
| [B0011 · 117–122](../../../../tools/verify_clean_build.py#L117) | Callable definition: def output_text(value: str \| bytes \| None) -&gt; str: | calls isinstance, decode; returns ""; value.decode("utf-8", errors="replace") · [reviewed contract](#b0011) |
| [B0012 · 123–124](../../../../tools/verify_clean_build.py#L123) | Explanatory comments or spacing. |  |
| [B0013 · 125–167](../../../../tools/verify_clean_build.py#L125) | Callable definition: def run_command(command: list\[str\], log: TextIO) -&gt; str: | calls write, join, flush, monotonic; returns output · [reviewed contract](#b0013) |
| [B0014 · 168–169](../../../../tools/verify_clean_build.py#L168) | Explanatory comments or spacing. |  |
| [B0015 · 170–172](../../../../tools/verify_clean_build.py#L170) | Callable definition: def test_count(ctest_output: str) -&gt; int \| None: | calls search, of, int, group; returns int(match.group(1)) if match else None · [reviewed contract](#b0015) |
| [B0016 · 173–174](../../../../tools/verify_clean_build.py#L173) | Explanatory comments or spacing. |  |
| [B0017 · 175–243](../../../../tools/verify_clean_build.py#L175) | Callable definition: def main(argv: list\[str\] \| None = None) -&gt; int: | calls parse_args, Path, resolve, expanduser; returns 1; 0 · [reviewed contract](#b0017) |
| [B0018 · 244–247](../../../../tools/verify_clean_build.py#L244) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0018) |

## B0001

[Lines 1–36](../../../../tools/verify_clean_build.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define a source-copy configure/build/CTest runner with a persistent human-readable log. |
| inputs / outputs | Imports stdlib, six explicit root metadata files, eleven selected source/docs trees, basename exclusions and a900-second command timeout; guarded main. |
| invariants | Copies the selected source inventory, now including the full filtered docs tree and root README/.gitignore. Importing the module does not call main; actual build/test execution requires its guarded entry point. |
| ownership | Owns constants/imports; main owns temporary source/build tree and log; copy_snapshot is separately exercised by registered integration fixture. |
| failure | Import failure visible; operational errors represented by VerificationError/ordinary IO and reported by main. |
| cost | Fixed module setup; actual source copying/build/process work deferred to main. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
SOURCE_FILES = (
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the six root metadata files required by clean source and R1 packaging workflows. |
| inputs / outputs | Root-only .gitignore, CMakeLists.txt, CMakePresets.json, dependencies.lock.json, README.md and current Refactor.md; copy_snapshot copies them before directory trees. |
| invariants | No docs leaf appears here: full docs is copied once through SOURCE_DIRECTORIES, avoiding a precreated snapshot/docs destination. Historical baseline plan bytes remain separately copied through their pinned archive path. This is not all tracked Git files or a cryptographic freeze. |
| ownership | Owns immutable tuples/scalars or mutable set of immutable strings. |
| failure | Import allocation failure; missing copied inputs fail later. |
| cost | Fixed registry allocation, no recursive filesystem IO in these assignments. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
SOURCE_DIRECTORIES = (
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare eleven source, fixture, dependency, example, benchmark and complete documentation trees for the clean copy. |
| inputs / outputs | include, src, apps, tests, tools, schemas, third_party, cmake, examples, benchmarks and docs are copied by copy_snapshot with the existing recursive basename exclusions. |
| invariants | The docs tree includes the packaging/report/release guides and generated inspection files. SOURCE_FILES contains only root leaves, so docs is not precreated by that loop. Selection plus exclusions is an explicit local snapshot contract, not all Git tracked files or a cryptographic freeze. |
| ownership | Owns immutable tuples/scalars or mutable set of immutable strings. |
| failure | Import allocation failure; missing copied inputs fail later. |
| cost | Fixed registry allocation, no recursive filesystem IO in these assignments. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
IGNORED_NAMES = {"__pycache__", ".git", "build"}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare IGNORED_NAMES for clean-copy verification. |
| inputs / outputs | Basename exclusions __pycache__, .git and build; pyc excluded separately. Read by copy/command helpers. |
| invariants | This is an explicit local snapshot contract, not all Git tracked files or cryptographic source freeze. |
| ownership | Owns immutable tuples/scalars or mutable set of immutable strings. |
| failure | Import allocation failure; missing copied inputs fail later. |
| cost | Fixed registry allocation, no recursive filesystem IO in these assignments. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
COMMAND_TIMEOUT_SECONDS = 900
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare COMMAND_TIMEOUT_SECONDS for clean-copy verification. |
| inputs / outputs | 900-second per-command subprocess timeout. Read by copy/command helpers. |
| invariants | This is an explicit local snapshot contract, not all Git tracked files or cryptographic source freeze. |
| ownership | Owns immutable tuples/scalars or mutable set of immutable strings. |
| failure | Import allocation failure; missing copied inputs fail later. |
| cost | Fixed registry allocation, no recursive filesystem IO in these assignments. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 37–41](../../../../tools/verify_clean_build.py#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class VerificationError(RuntimeError):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify a clean-copy verification failure while retaining contextual causes. |
| inputs / outputs | RuntimeError subclass; constructed by copy/command helpers and caught by main Exception branch. |
| invariants | No automatic cleanup or error suppression in type itself. |
| ownership | Owns diagnostic/cause references as normal exception. |
| failure | Thrown at failing phase; main reports failure after cleanup attempt. |
| cost | Fixed class import setup; exception traceback/message allocated on failure. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0003

[Lines 42–49](../../../../tools/verify_clean_build.py#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def positive_int(value: str) -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a strictly positive integer argparse option. |
| inputs / outputs | CLI string in; positive Python int out. |
| invariants | Rejects nonnumeric/≤0; no upper bound beyond caller/system resources. |
| ownership | Owns parsed integer; input borrowed. |
| failure | ValueError is translated to chained argparse.ArgumentTypeError; nonpositive explicit ArgumentTypeError. |
| cost | O(input digits) int parse and big-integer storage. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0005

[Lines 52–73](../../../../tools/verify_clean_build.py#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse clean-build configuration, parallelism and persistent log destination. |
| inputs / outputs | Optional argv list in; argparse Namespace out, default Release/parallel2/log build/verification/clean-source.log. |
| invariants | Debug/Release only, positive parallel count; does not run configure/build or validate log contents yet. |
| ownership | Owns parser/namespace/Path and option text. |
| failure | Argparse SystemExit on usage; custom positive-int errors rendered by argparse. |
| cost | O(arguments) parsing and fixed option setup. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0007

[Lines 76–81](../../../../tools/verify_clean_build.py#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def ignore_snapshot_entries(_directory: str, names: list[str]) -> set[str]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply recursive copytree basename/bytecode exclusions. |
| inputs / outputs | Directory string and entry names in; set of ignored names out. |
| invariants | Excludes fixed ignored basenames and .pyc; does not follow Git ignore/tracked inventory. |
| ownership | Owns returned set of name references; source entries borrowed. |
| failure | String/type/OOM errors propagate. |
| cost | O(entries) filtering and set storage per directory. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0008

[Lines 82–84](../../../../tools/verify_clean_build.py#L82); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L84:sha256:e9896175a4dab16a68769c544531c695bac032bfd4a19073dc3f3b542ebbe651
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent Python helper boundary: Copy only the explicit source inventory and legacy files, excluding build/cache basenames. |
| inputs / outputs | Explanatory source text only; no checked observation is produced. |
| invariants | The note does not execute validation or establish the described result. Its neighboring callable contract defines the actual behavior. |
| ownership | No runtime owner or state is introduced by this comment. |
| failure | No Python runtime failure branch in comment text. |
| cost | No execution from this note; the described helper work is charged at that helper. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/code_review.md](../../../code_review.md) |

## B0009

[Lines 85–114](../../../../tools/verify_clean_build.py#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def copy_snapshot(repository: Path, source: Path, log: TextIO) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy six root metadata files, eleven selected trees including full filtered docs, and the exact required legacy-manifest paths into a private source tree. |
| inputs / outputs | Repository/source Paths and writable log in; writes the current root/source/docs inventory plus legacy source_sha256_local members and copy-log entries. |
| invariants | Directory destinations must be fresh for copytree. Root-only SOURCE_FILES leaves do not create source/docs, so its single tree copy has no leaf/tree collision. Basename exclusions remain unchanged. Copies selected baseline members, not whole historical projects; live-source changes can still make this non-atomic/noncryptographic. |
| ownership | Filesystem owns byte copies; helper owns parsed legacy manifest and path/log temporaries; repository unchanged. |
| failure | Missing/unsafe inputs raise VerificationError; an existing directory destination or copy2/copytree/JSON/log IO failure propagates. main owns cleanup; this helper introduces no retry or rollback framework. |
| cost | O(total selected bytes plus directory entries), now including the complete filtered docs tree, with copy2 metadata work and full legacy-manifest parsing. Duplicate legacy leaves may be overwritten by copy_file as before. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

```text
def copy_file(name: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one required repository-relative file into the snapshot and record it. |
| inputs / outputs | Relative path in; captured repository/source/log mutated by mkdir/copy2/log write. |
| invariants | Rejects absolute/.. paths and requires original is_file; fixed metadata paths are trusted local provenance, not a hostile symlink containment proof. |
| ownership | Owns target file bytes on filesystem; Path temporaries, source bytes unchanged. |
| failure | VerificationError for invalid/missing path; IO/copy/log failures propagate. |
| cost | O(file bytes) copy2 plus parent creation/metadata copy and log text. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0011

[Lines 117–122](../../../../tools/verify_clean_build.py#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def output_text(value: str | bytes | None) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize captured process output for a replacement-safe log. |
| inputs / outputs | None/bytes/str-like value in; empty/UTF8(errors=replace)/str(value) out. |
| invariants | Replacement decoding preserves printable diagnostics, not exact raw output byte identity. |
| ownership | Owns decoded/converted string, or reuses existing str. |
| failure | Custom str/OOM errors propagate; bytes decode uses replacement. |
| cost | O(output bytes) decode/copy for bytes; fixed None branch. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0013

[Lines 125–167](../../../../tools/verify_clean_build.py#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run_command(command: list[str], log: TextIO) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Log and execute one configure/build/test command with captured output and900s timeout. |
| inputs / outputs | Argument list and writable log in; merged stdout/stderr text out on success. |
| invariants | Uses shell-free subprocess, check=True, UTF8 replacement decode and full PIPE capture; no output-byte cap. Logs before call and successful/failed/timeout output after. |
| ownership | Owns complete captured text and command/log strings; caller owns log handle and temporary tree. |
| failure | TimeoutExpired/CalledProcessError output preserved then chained VerificationError; spawn/IO/log errors propagate without generic translation. |
| cost | Native/build child work plus full captured output buffering/serialization; timeout bounds elapsed child attempt, not compiler memory or log size. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0015

[Lines 170–172](../../../../tools/verify_clean_build.py#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def test_count(ctest_output: str) -> int | None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract CTest's reported total test count if present. |
| inputs / outputs | CTest text in; integer N from tests failed out of N, or None. |
| invariants | No fixed expected test count and no pass/fail inference; run_command separately enforces zero exit. |
| ownership | Borrows text; regex match/int result temporary. |
| failure | No match is ordinary None; parse/OOM errors propagate. |
| cost | O(output characters) regex search, O(digits) int parse. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0017

[Lines 175–243](../../../../tools/verify_clean_build.py#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main(argv: list[str] | None = None) -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build/test a temporary copied source and retain one persistent pass/fail log. |
| inputs / outputs | Optional argv in; copies root metadata, full filtered docs and all selected source/fixture trees, configures/builds CMake, runs CTest and returns0/1 after logging/cleanup. |
| invariants | Log opened w replaces prior log; source/build under mkdtemp. finally calls rmtree(ignore_errors=True), then records actual removed status; cleanup success not guaranteed. No native jobs were run in this review packet. |
| ownership | Owns temporary tree/log/process captures; temporary tree deletion attempted after normal/Exception/interrupt path. Persistent log retained. |
| failure | Catches Exception into failure, finally attempts cleanup, appends PASS/FAIL then returns; BaseException still triggers finally but bypasses result. Final log errors may escape. |
| cost | Copies the expanded selected source/docs inventory, then actual configure/build/full CTest with per-command900-second limits and uncapped captures. Recursive cleanup visits the temporary tree; this is explicit offline work, not query-runtime cost. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0018

[Lines 244–247](../../../../tools/verify_clean_build.py#L244); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the clean-copy native verification runner only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | SystemExit(main code); main handles Exception/logging as specified, no extra retry/cleanup in guard. |
| cost | Constant guard then full clean build/test work if invoked; not invoked during review. |
| Design | [tools/verify_clean_build.py](../../../../tools/verify_clean_build.py), [docs/native_build.md](../../../native_build.md), [tests/integration/clean_source_snapshot.py](../../../../tests/integration/clean_source_snapshot.py), [benchmarks/legacy/manifest.json](../../../../benchmarks/legacy/manifest.json), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |
