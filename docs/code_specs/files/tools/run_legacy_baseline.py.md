# `tools/run_legacy_baseline.py` — block usage map

[Source](../../../../tools/run_legacy_baseline.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `f07a5e6783523ac8dc12395d0774cd2f1287e6e85333d2d4d5b3f3ec603b31ec`. 161 lines partitioned into 13 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../tools/run_legacy_baseline.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 24–25](../../../../tools/run_legacy_baseline.py#L24) | Callable definition: def sha256_file(path: Path) -&gt; str: | calls sha256, read_bytes, hexdigest; returns hashlib.sha256(path.read_bytes()).hexdigest() · [reviewed contract](#b0002) |
| [B0003 · 26–27](../../../../tools/run_legacy_baseline.py#L26) | Explanatory comments or spacing. |  |
| [B0004 · 28–59](../../../../tools/run_legacy_baseline.py#L28) | Callable definition: def detect_environment(): | calls run, splitlines, strip, platform; returns { · [reviewed contract](#b0004) |
| [B0005 · 60–61](../../../../tools/run_legacy_baseline.py#L60) | Explanatory comments or spacing. |  |
| [B0006 · 62–69](../../../../tools/run_legacy_baseline.py#L62) | Callable definition: def parse_pom_properties(pom_path: Path): | calls read_text, finditer, groups; returns props; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 70–71](../../../../tools/run_legacy_baseline.py#L70) | Explanatory comments or spacing. |  |
| [B0008 · 72–105](../../../../tools/run_legacy_baseline.py#L72) | Callable definition: def attempt_legacy_build(root_dir: Path, timeout: int = 120): | calls is_file, str, now, run; returns {"status": "missing_pom", "error": f"pom.xml not found at {pom_path}"}; {; source comment (unverified): # Parse key error signatures · [reviewed contract](#b0008) |
| [B0009 · 106–107](../../../../tools/run_legacy_baseline.py#L106) | Explanatory comments or spacing. |  |
| [B0010 · 108–120](../../../../tools/run_legacy_baseline.py#L108) | Callable definition: def inspect_legacy_manifest(manifest_path: Path): | calls is_file, loads, read_text, get; returns {"status": "manifest_not_found"}; {; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 121–122](../../../../tools/run_legacy_baseline.py#L121) | Explanatory comments or spacing. |  |
| [B0012 · 123–157](../../../../tools/run_legacy_baseline.py#L123) | Callable definition: def main(): | calls ArgumentParser, runner, add_argument, Path · [reviewed contract](#b0012) |
| [B0013 · 158–161](../../../../tools/run_legacy_baseline.py#L158) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |

## B0001

[Lines 1–23](../../../../tools/run_legacy_baseline.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the draft legacy environment/build diagnostic and import its standard-library dependencies. |
| inputs / outputs | Module load creates definitions and sets sys.dont_write_bytecode; main is entered only by the script guard. |
| invariants | The docstring describes intended B01 work; this module does not authenticate pinned source/toolchain versions or execute baseline queries. Some imports and sha256_file are unused by main. |
| ownership | Python owns module state; no native query owner or toolchain process is created by these declarations. |
| failure | Import/runtime initialization errors propagate. |
| cost | Ordinary Python imports and fixed declarations; subsequent external commands have separate costs. |
| Design | [tools/run_legacy_baseline.py](../../../../tools/run_legacy_baseline.py), [Refactor.md](../../../../Refactor.md) |

## B0002

[Lines 24–25](../../../../tools/run_legacy_baseline.py#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sha256_file(path: Path) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a SHA256 digest for one supplied file; the current runner never calls this helper. |
| inputs / outputs | Path in; lowercase digest string out. |
| invariants | Reads actual file bytes but compares no expected pin, so its presence does not establish a source audit. |
| ownership | Owns one full Python bytes copy and digest result. |
| failure | Read/allocation errors propagate. |
| cost | O(file bytes) time and full-file Python storage, with no explicit file-size cap. |
| Design | [tools/run_legacy_baseline.py](../../../../tools/run_legacy_baseline.py), [Refactor.md](../../../../Refactor.md) |

## B0004

[Lines 28–59](../../../../tools/run_legacy_baseline.py#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def detect_environment():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect host metadata and first-line Java/javac/Maven version observations. |
| inputs / outputs | Current PATH/JAVA_HOME and host platform in; nullable command-version fields and platform strings out. |
| invariants | FileNotFoundError is treated as an absent optional tool. Versions are observed, not compared against required pins; command exit status is not validated. |
| ownership | subprocess.run owns captured output; returned strings are ordinary Python report data. |
| failure | Missing tools return null; other launch errors or empty java output can propagate, including the unguarded first-line access. |
| cost | Three captured subprocesses without timeouts plus platform observations; output/time are not bounded by this helper. |
| Design | [tools/run_legacy_baseline.py](../../../../tools/run_legacy_baseline.py), [Refactor.md](../../../../Refactor.md) |

## B0006

[Lines 62–69](../../../../tools/run_legacy_baseline.py#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def parse_pom_properties(pom_path: Path):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract five selected version-property spellings from raw POM text using a regular expression. |
| inputs / outputs | UTF-8 POM path in; matching Flink/Java/Scala/log4j values out. |
| invariants | This is not XML/dependency resolution, inheritance/substitution or comparison with an expected dependency lock. Repeated selected tags overwrite prior values. |
| ownership | Owns full decoded text, regex captures and a small dictionary. |
| failure | Missing/unreadable/non-UTF8 input propagates unless the caller skipped the call for a missing file. |
| cost | Whole text read and regex scan/captures; no admitted byte/work cap or general XML complexity guarantee. |
| Design | [tools/run_legacy_baseline.py](../../../../tools/run_legacy_baseline.py), [Refactor.md](../../../../Refactor.md) |

## B0008

[Lines 72–105](../../../../tools/run_legacy_baseline.py#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def attempt_legacy_build(root_dir: Path, timeout: int = 120):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Optionally invoke Maven clean compile on the legacy subdirectory and summarize its returned diagnostic. |
| inputs / outputs | Root and timeout in; missing-POM, success, build_failed, timeout or generic error dictionary out. |
| invariants | Maven clean can remove legacy target outputs and Maven can resolve dependencies. The helper does not check A02 provenance/license disposition, pin an environment or compare query results; failure-signature strings are heuristics. |
| ownership | Owns captured stdout/stderr and returns only tails on normal exit; the external build controls its target/dependency artifacts. |
| failure | Timeout yields a summary without the full partial log; a broad Exception catch converts other failures to status/error text. Descendant process cleanup is not separately implemented. |
| cost | One potentially costly external build with a subprocess timeout and fully captured output; no native runtime/update performance evidence. |
| Design | [tools/run_legacy_baseline.py](../../../../tools/run_legacy_baseline.py), [Refactor.md](../../../../Refactor.md) |

## B0010

[Lines 108–120](../../../../tools/run_legacy_baseline.py#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def inspect_legacy_manifest(manifest_path: Path):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Summarize selected manifest dictionary fields if a JSON file exists. |
| inputs / outputs | Manifest path in; title/counts/query labels or manifest_not_found out. |
| invariants | Uses get defaults without schema or source-pin validation; missing/mismatched fields can produce empty or null summaries. |
| ownership | Owns full JSON text/DOM and copied summary data. |
| failure | Missing file has an explicit status; invalid JSON or unexpected field types propagate. |
| cost | Full-file JSON parse and linear query-label traversal, without explicit byte/item bounds. |
| Design | [tools/run_legacy_baseline.py](../../../../tools/run_legacy_baseline.py), [Refactor.md](../../../../Refactor.md) |

## B0012

[Lines 123–157](../../../../tools/run_legacy_baseline.py#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate the draft B01 host/POM/manifest diagnostic and optionally attach a legacy compile result. |
| inputs / outputs | CLI source/output/try-build/timeout arguments in; JSON report and console status out. |
| invariants | Writing a report is not a successful baseline build or query/correctness comparison. Existing output is overwritten; this is not an immutable evidence-packet writer. It does not satisfy Refactor B01/A02 acceptance. |
| ownership | Python owns report data; optional Maven owns build side effects; the caller chooses the destination. |
| failure | Argument/read/write errors propagate. A reported failed build does not make this main return nonzero. |
| cost | Environment probes, optional Maven build and JSON serialization; no benchmark execution or timing comparison. |
| Design | [tools/run_legacy_baseline.py](../../../../tools/run_legacy_baseline.py), [Refactor.md](../../../../Refactor.md) |

## B0013

[Lines 158–161](../../../../tools/run_legacy_baseline.py#L158); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the diagnostic CLI only when this file is executed as a script. |
| inputs / outputs | Module name predicate in; main invocation or no dispatch out. |
| invariants | Import still sets dont_write_bytecode, but does not invoke the CLI. |
| ownership | No new owner beyond main. |
| failure | main failures propagate to Python process status. |
| cost | One predicate/dispatch; main supplies all real costs. |
| Design | [tools/run_legacy_baseline.py](../../../../tools/run_legacy_baseline.py), [Refactor.md](../../../../Refactor.md) |
