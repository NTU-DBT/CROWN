# `tests/integration/experimental_report.py` — block usage map

[Source](../../../../../tests/integration/experimental_report.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `dac285c6c3e52ad284bd134c024636b3376b3b6135e4ab64ada43b65dd30a579`. 194 lines partitioned into 15 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/integration/experimental_report.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 21–23](../../../../../tests/integration/experimental_report.py#L21) | Callable definition: def require(condition, message): | calls ValueError; guard def require(condition, message): · [reviewed contract](#b0002) |
| [B0003 · 24–25](../../../../../tests/integration/experimental_report.py#L24) | Explanatory comments or spacing. |  |
| [B0004 · 26–28](../../../../../tests/integration/experimental_report.py#L26) | Callable definition: def digest(path): | calls open, file_digest, hexdigest; returns hashlib.file_digest(stream, 'sha256').hexdigest() · [reviewed contract](#b0004) |
| [B0005 · 29–30](../../../../../tests/integration/experimental_report.py#L29) | Explanatory comments or spacing. |  |
| [B0006 · 31–32](../../../../../tests/integration/experimental_report.py#L31) | Callable definition: def tree_hashes(directory): | calls str, relative_to, digest, rglob; returns {str(path.relative_to(directory)): digest(path) for path in directory.rglob('*') if path.is_file()}; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 33–34](../../../../../tests/integration/experimental_report.py#L33) | Explanatory comments or spacing. |  |
| [B0008 · 35–45](../../../../../tests/integration/experimental_report.py#L35) | Callable definition: def unpack_fixture(fixture, destination): | calls is_dir, copytree, mkdir, open; guard require(len(members) &lt;= 20000 and sum(member.size for member in members) &lt;= 256*1024**2, 'fixture a…; returns destination.mkdir(); 2 loop sites · [reviewed contract](#b0008) |
| [B0009 · 46–47](../../../../../tests/integration/experimental_report.py#L46) | Explanatory comments or spacing. |  |
| [B0010 · 48–73](../../../../../tests/integration/experimental_report.py#L48) | Callable definition: def corrupt_search_metadata(bundle, kind): | calls loads, read_text, str, Path; 3 loop sites · [reviewed contract](#b0010) |
| [B0011 · 74–75](../../../../../tests/integration/experimental_report.py#L74) | Explanatory comments or spacing. |  |
| [B0012 · 76–183](../../../../../tests/integration/experimental_report.py#L76) | Callable definition: def run(args): | calls resolve, mkdir, TemporaryDirectory, Path; guard require((child.returncode == 0) is success, label+': '+child.stderr\[-3000:\]); returns child; growth new; 15 loop sites · [reviewed contract](#b0012) |
| [B0013 · 184–185](../../../../../tests/integration/experimental_report.py#L184) | Explanatory comments or spacing. |  |
| [B0014 · 186–190](../../../../../tests/integration/experimental_report.py#L186) | Callable definition: def main(): | calls ArgumentParser, add_argument, run, parse_args · [reviewed contract](#b0014) |
| [B0015 · 191–194](../../../../../tests/integration/experimental_report.py#L191) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |

## B0001

[Lines 1–20](../../../../../tests/integration/experimental_report.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:4a4c33d99aea6ead2f86c5e4b2a83f4bc0b92b821033cb7625ccc68cd18f310c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare an offline genuine-evidence report regression. |
| inputs / outputs | Imports standard file/archive/process/CSV/exact-arithmetic helpers and resolves the current repository tool root. |
| invariants | Import invokes no native executable, compiler or measurement. The fixture must supply genuine study bytes rather than generated timing values. |
| ownership | All later artifacts belong to an explicit new or temporary test directory. |
| failure | Import errors fail the regression. |
| cost | Cold test setup, with no controlled performance attribution. |
| Design | [docs/experimental_report.md](../../../../experimental_report.md), [tests/integration/experimental_report.py](../../../../../tests/integration/experimental_report.py) |

## B0002

[Lines 21–23](../../../../../tests/integration/experimental_report.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L23:sha256:771470ca6047ea7b84814e6cc23c2357b927e95ad29ed2fbd7b34f2969c68de4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep regression failures active in optimized Python execution. |
| inputs / outputs | A false condition raises ValueError with its violated obligation. |
| invariants | No assertions-only correctness authority is used. |
| ownership | Borrows inputs; owns a possible failure exception. |
| failure | Failure stops the regression and preserves explicit-output artifacts. |
| cost | Constant local branch. |
| Design | [tests/integration/experimental_report.py](../../../../../tests/integration/experimental_report.py) |

## B0004

[Lines 26–28](../../../../../tests/integration/experimental_report.py#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L28:sha256:1d0332a1d9055bae62af270d2a7698f8118c50a5215446e50040d3fecc7408f8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash actual test files for publication, plot and preservation checks. |
| inputs / outputs | A readable file path produces a streaming SHA256. |
| invariants | Checks use actual file bytes rather than names or successful exit flags. |
| ownership | Owns the scoped input handle; no file mutation. |
| failure | File/hash errors fail the test. |
| cost | Linear bytes with bounded hash state. |
| Design | [tests/integration/experimental_report.py](../../../../../tests/integration/experimental_report.py) |

## B0006

[Lines 31–32](../../../../../tests/integration/experimental_report.py#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L32:sha256:8d49059a02eaf3a172545c1f2f2f554cafd672b8a40ad850cbd531462a0c3879
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture every file byte pin under a report before a rejected reuse attempt. |
| inputs / outputs | A directory becomes relative-path to SHA256 mapping. |
| invariants | After the expected failure, exact mapping equality checks both content and path preservation. |
| ownership | Owns a small test inventory; accepted report files remain unchanged. |
| failure | Unreadable/racing files fail instead of weakening the comparison. |
| cost | One traversal and hash pass over the selected tiny report bytes. |
| Design | [tests/integration/experimental_report.py](../../../../../tests/integration/experimental_report.py), [docs/experimental_report.md](../../../../experimental_report.md) |

## B0008

[Lines 35–45](../../../../../tests/integration/experimental_report.py#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L45:sha256:ef65e86f5f97a2de62fd90794e38fce832021dfcb4b6d448b05efd8ed0a3eeaf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage a genuine portable fixture in a relocated path with spaces. |
| inputs / outputs | A directory copies read-only inputs, or a tar archive extracts into a new destination under finite member/decompressed-byte limits. |
| invariants | Archive admission rejects absolute/parent paths, links and special members; Python data extraction filtering is also applied. The file-backed archive path is bounded to 20,000 members and 256 MiB decoded content. |
| ownership | Owns only the new fixture copy/extraction; original accepted bundle stays immutable. |
| failure | Existing destinations, invalid archives, exceeded grants or unsafe members fail. |
| cost | Copy/extract work scales with genuine fixture bytes; no full historical multi-GB bundle is needed for default development. |
| Design | [docs/experimental_report.md](../../../../experimental_report.md) |

## B0010

[Lines 48–73](../../../../../tests/integration/experimental_report.py#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L73:sha256:f389dd955a82feecc97d0e9fbc60926d2944e2719c9432b0acf6f2c484dfba10
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a semantic source/metadata discrepancy that cannot be dismissed as a broken checksum. |
| inputs / outputs | A fresh copied bundle and timing/count selector modify one selected measured search record, then consistently rebind gzip/index/manifest byte hashes. |
| invariants | Actual raw search stdout remains unchanged. The later rejection must name metadata/raw timing/count/status disagreement, proving the reader joins copied metadata to actual reports. |
| ownership | Owns only a deliberately invalid fixture copy; accepted original evidence and source studies stay untouched. |
| failure | Missing search/run fields or fixture I/O errors fail the setup; a different rejection reason fails the regression. |
| cost | Offline parse/recompress of one small study manifest plus index updates. |
| Design | [tools/build_experimental_report.py](../../../../../tools/build_experimental_report.py), [tests/integration/experimental_report.py](../../../../../tests/integration/experimental_report.py) |

## B0012

[Lines 76–183](../../../../../tests/integration/experimental_report.py#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L76-L183:sha256:77245ed0e08dee9ac43a708169573623fa173b4cc0ef6c1694e69c501f96f562
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise portable genuine replay, exact arithmetic, provenance and failure controls end to end. |
| inputs / outputs | A genuine five-study bundle and optional plot dependency produce logged Python subprocesses, fresh relocated reports, independent raw recomputations and a bounded receiving receipt. |
| invariants | All subprocesses are report/plot Python tools, never native benchmarks. One metric per study is recomputed independently from decoded original bytes; every RSS row points to actual resource text and search wall to its experiment record. Included standalone tools reproduce all three CSVs. Same-runtime gzip determinism, corruption/missing/no-private-fallback, wrong published root, finite grant, semantic timing/count mismatch and reuse preservation are checked. Optional plots validate actual Agg PNG/PDF bytes. Report success remains distinct from B06 acceptance. |
| ownership | Owns a new/temporary test tree and copied deliberately invalid fixtures; accepted input bundle is read-only. Temporary directories clean up on success; explicit output retains commands/stdout/stderr/receiving for review. |
| failure | Wrong exit status, diagnostics, byte/arithmetic/pointer disagreement, unexpected mutation or invalid plots fail immediately. Child Python commands have finite 300-second timeouts; failures are not silently retried. |
| cost | Offline test cost scales with repeated tiny evidence copies/replays and optional rendering. It verifies report mechanisms, not all historical result semantics or a new cross-machine benchmark. |
| Design | [docs/experimental_report.md](../../../../experimental_report.md), [tools/build_experimental_report.py](../../../../../tools/build_experimental_report.py), [tools/plot_experimental_report.py](../../../../../tools/plot_experimental_report.py), [Refactor.md §11.11 B06](../../../../../Refactor.md) |

## B0014

[Lines 186–190](../../../../../tests/integration/experimental_report.py#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L186-L190:sha256:0d0c4479d53260853aa022c23adacfbb360998e41b1260821e9a93be03dfb6b1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose explicit genuine-fixture and optional-plot integration arguments. |
| inputs / outputs | Bundle path, optional new output and plot dependency path call the complete offline regression. |
| invariants | No implicit old workspace path, installed artifact mutation or native executable argument exists. |
| ownership | Owns argparse values; run owns test artifacts. |
| failure | Uncaught regression errors retain a failing process status for CTest/manual invocation. |
| cost | Cold CLI work only. |
| Design | [docs/experimental_report.md](../../../../experimental_report.md) |

## B0015

[Lines 191–194](../../../../../tests/integration/experimental_report.py#L191); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L191-L194:sha256:239f34ccf0a25c3afeefe82507f70b0ffbbcbf03dd6930292ca35d6b41937a29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the integration only for direct execution. |
| inputs / outputs | Module-name guard calls main. |
| invariants | Import does not copy fixtures or execute subprocesses. |
| ownership | Only module globals are live before dispatch. |
| failure | Normal exceptions produce a nonzero regression process. |
| cost | Constant dispatch. |
| Design | [tests/integration/experimental_report.py](../../../../../tests/integration/experimental_report.py) |
