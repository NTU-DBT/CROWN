# `tools/run_measurements.py` — block usage map

[Source](../../../../tools/run_measurements.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `423ee4fd161f99723242a097621a62d6f65154777265bd1f97aaa0bf8454281d`. 415 lines partitioned into 27 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–25](../../../../tools/run_measurements.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 26–27](../../../../tools/run_measurements.py#L26) | Callable definition: def require(value, message): | calls ValueError; guard def require(value, message): · [reviewed contract](#b0002) |
| [B0003 · 28–29](../../../../tools/run_measurements.py#L28) | Explanatory comments or spacing. |  |
| [B0004 · 30–31](../../../../tools/run_measurements.py#L30) | Callable definition: def digest(path): | calls sha256, read_bytes, hexdigest; returns hashlib.sha256(path.read_bytes()).hexdigest() · [reviewed contract](#b0004) |
| [B0005 · 32–33](../../../../tools/run_measurements.py#L32) | Explanatory comments or spacing. |  |
| [B0006 · 34–42](../../../../tools/run_measurements.py#L34) | Callable definition: def measurement_tools(): | calls in, which, require, Path; guard require(found is not None, 'missing measurement launcher: ' + name); returns result; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 43–44](../../../../tools/run_measurements.py#L43) | Explanatory comments or spacing. |  |
| [B0008 · 45–55](../../../../tools/run_measurements.py#L45) | Callable definition: def distribution(values): | calls require, all, isinstance, sorted; guard require(all(isinstance(x, int) and not isinstance(x, bool) and x &gt;= 0 for x in values), 'invalid no…; returns {'samples': len(values), 'minimum': min(values) if values else None, 'maximum': max(values) if valu…; 3 loop sites · [reviewed contract](#b0008) |
| [B0009 · 56–57](../../../../tools/run_measurements.py#L56) | Explanatory comments or spacing. |  |
| [B0010 · 58–82](../../../../tools/run_measurements.py#L58) | Callable definition: def environment(): | calls Path, exists, read_text, splitlines; returns {'platform': platform.platform(), 'uname': list(platform.uname()), 'python': sys.version,; 5 loop sites · [reviewed contract](#b0010) |
| [B0011 · 83–85](../../../../tools/run_measurements.py#L83) | Module statements. | source comment (unverified): # Hashes bind current bytes; filesystem freshness checks are not cryptographic build lineage. · [reviewed contract](#b0011) |
| [B0012 · 86–168](../../../../tools/run_measurements.py#L86) | Callable definition: def build_provenance(source_root, build, crown, collector, extra_binaries=()): | calls require, is_file, loads, read_text; guard require(crown.parent == build and collector.parent == build, 'controlled measurements require binar…; returns {'build_directory': str(build), 'files': files, 'link_commands': links, 'compiled_units': compiled,; 14 loop sites · [reviewed contract](#b0012) |
| [B0013 · 169–171](../../../../tools/run_measurements.py#L169) | declares types or opens a type body. |  · [reviewed contract](#b0013) |
| [B0014 · 172–175](../../../../tools/run_measurements.py#L172) | Callable definition: def __init__(self, output, cpu, timeout, byte_limit): | calls measurement_tools · [reviewed contract](#b0014) |
| [B0015 · 176–177](../../../../tools/run_measurements.py#L176) | Module statements. | source comment (unverified): # Raw-output bytes are checked after the child exits; sink files are outside this grant. · [reviewed contract](#b0015) |
| [B0016 · 178–222](../../../../tools/run_measurements.py#L178) | Callable definition: def invoke(self, label, arguments): | calls require, len, list, map; guard require(len(self.commands) &lt; 10000, 'experiment command count grant exceeded'); returns json.loads(out.read_text()), record; 1 loop sites; source comment (unverified): # The lightweight time process forks the target after exec. Its target · [reviewed contract](#b0016) |
| [B0017 · 223–223](../../../../tools/run_measurements.py#L223) | Explanatory comments or spacing. |  |
| [B0018 · 224–225](../../../../tools/run_measurements.py#L224) | Callable definition: def save_commands(self): | calls write_text, dumps · [reviewed contract](#b0018) |
| [B0019 · 226–227](../../../../tools/run_measurements.py#L226) | Explanatory comments or spacing. |  |
| [B0020 · 228–238](../../../../tools/run_measurements.py#L228) | Callable definition: def indexed_options(): | calls dict, zip; returns {'schema_version': 2,; 1 loop sites; source comment (unverified): # Explicit measured configuration, equal to the verified finite native · [reviewed contract](#b0020) |
| [B0021 · 239–240](../../../../tools/run_measurements.py#L239) | Explanatory comments or spacing. |  |
| [B0022 · 241–259](../../../../tools/run_measurements.py#L241) | Callable definition: def summarize(reports): | calls setdefault, len, distribution, sum; returns {'runs': len(reports), 'update_latency_ns': distribution(\[event\['event_active_ns'\] for event in eve…; 18 loop sites · [reviewed contract](#b0022) |
| [B0023 · 260–261](../../../../tools/run_measurements.py#L260) | Explanatory comments or spacing. |  |
| [B0024 · 262–393](../../../../tools/run_measurements.py#L262) | Callable definition: def run(args): | calls resolve, require, startswith, hasattr; guard require(sys.platform.startswith('linux') and hasattr(os, 'wait4'), 'controlled runner requires Linu…; 25 loop sites; source comment (unverified): # Raw reports are immutable files; materialize one repetition group for · [reviewed contract](#b0024) |
| [B0025 · 394–395](../../../../tools/run_measurements.py#L394) | Explanatory comments or spacing. |  |
| [B0026 · 396–409](../../../../tools/run_measurements.py#L396) | Callable definition: def main(): | calls ArgumentParser, add_argument, run, parse_args · [reviewed contract](#b0026) |
| [B0027 · 410–415](../../../../tools/run_measurements.py#L410) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0027) |

## B0001

[Lines 1–25](../../../../tools/run_measurements.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define Linux controlled-run harness with build/source checks and target-versus-launcher resource accounting. |
| inputs / outputs | Imports standard library/trusted verifier, disables bytecode writing, and exposes guarded CLI for explicit source/build/binaries/pack/output. |
| invariants | Import alone does not run measurements. Raw records use schema v2; requests/experiment packets remain separately versioned. GNU time measures target RSS; wait4 RSS is launcher scope. |
| ownership | Module owns definitions/imports; packet/report objects and child processes are outside native query-account ownership. |
| failure | Import failures precede guarded main; missing measurement tools, stale provenance and child failures use their scoped errors. |
| cost | Fixed import/setup; measurement_tools hashes executable bytes when called; full process/file work starts only through run(). |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [schemas/workload-measurement-v2.schema.json](../../../../schemas/workload-measurement-v2.schema.json), [schemas/measurement-experiment-v1.schema.json](../../../../schemas/measurement-experiment-v1.schema.json), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py) |

## B0002

[Lines 26–27](../../../../tools/run_measurements.py#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value, message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a false caller-supplied condition in this tool. |
| inputs / outputs | Truth-tested value and diagnostic text in; None on truth, ValueError on false. |
| invariants | Explicit conditional raise remains active under Python -O; this is a local assertion of the stated predicate, not native/proof validation. |
| ownership | Borrows condition/message; exception retains message until released. |
| failure | Raises ValueError at the caller check before subsequent operations; does not catch or undo earlier IO. |
| cost | O(truth conversion) plus exception construction only on failure; arbitrary user-defined __bool__ is outside these primitive callers. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/measurement.md](../../../measurement.md), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py), [tests/integration/measurement_build_provenance.py](../../../../tests/integration/measurement_build_provenance.py), [schemas/workload-measurement-v1.schema.json](../../../../schemas/workload-measurement-v1.schema.json), [schemas/measurement-experiment-v1.schema.json](../../../../schemas/measurement-experiment-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 30–31](../../../../tools/run_measurements.py#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def digest(path):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute SHA256 for an entire file as raw bytes. |
| inputs / outputs | Path-like input; lowercase SHA256 hex output; file content read completely. |
| invariants | Digest binds exact bytes supplied, including line endings and literal spelling; it does not attest semantic correctness or build lineage. |
| ownership | Owns full read_bytes temporary and hash/hex result; filesystem source unchanged. |
| failure | IO/OOM/type failure propagates before a digest result. |
| cost | O(file bytes) read+hash with full file-sized temporary. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/measurement.md](../../../measurement.md), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py), [tests/integration/measurement_build_provenance.py](../../../../tests/integration/measurement_build_provenance.py), [schemas/workload-measurement-v1.schema.json](../../../../schemas/workload-measurement-v1.schema.json), [schemas/measurement-experiment-v1.schema.json](../../../../schemas/measurement-experiment-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0006

[Lines 34–42](../../../../tools/run_measurements.py#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def measurement_tools():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve and hash the external time and taskset launchers. |
| inputs / outputs | No args; returns resolved paths and SHA-256 values for both executables. |
| invariants | Both commands are required even without CPU affinity. Hash pins file bytes but does not probe GNU time option compatibility. |
| ownership | Owns returned mapping; executable files are read only. |
| failure | Missing executable raises ValueError; file/hash failures propagate. |
| cost | Two PATH lookups and full executable reads/hashes per call. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py), [docs/measurement.md](../../../measurement.md), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0008

[Lines 45–55](../../../../tools/run_measurements.py#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def distribution(values):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute finite nearest-rank latency/byte summary and logarithmic histogram. |
| inputs / outputs | Iterable of nonnegative strict int samples in; count/min/max/p50/p95/p99/mean/stdev/bins dict out. |
| invariants | Rejects bool/negative/nonint; empty values produce explicit None statistics. Mean/stdev use floating point; bins use bit_length, not exact dense-frequency histogram. |
| ownership | Owns sorted sample list and Counter/output lists; sample scalars immutable. |
| failure | ValueError on unadmitted samples; statistics/float/overflow/OOM errors propagate. |
| cost | O(N log N) sort, O(N) retained list and histogram; several passes, statistics conversions can lose precision for huge ints. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/measurement.md](../../../measurement.md), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py), [tests/integration/measurement_build_provenance.py](../../../../tests/integration/measurement_build_provenance.py), [schemas/workload-measurement-v1.schema.json](../../../../schemas/workload-measurement-v1.schema.json), [schemas/measurement-experiment-v1.schema.json](../../../../schemas/measurement-experiment-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0010

[Lines 58–82](../../../../tools/run_measurements.py#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def environment():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record host metadata, launcher pins and target/launcher RSS scope. |
| inputs / outputs | No args; returns platform/Python/affinity/procfs data plus time/taskset hashes and RSS source description. |
| invariants | Frequency/cache remain observed, not controlled. GNU-time target maximum and outer wait4 launcher maximum have distinct fields. Governor OSError alone becomes None. |
| ownership | Owns procfs text and returned dict; system inputs read-only. |
| failure | Missing launcher and non-governor metadata/affinity/hash errors propagate. |
| cost | Reads/scans procfs/governors and hashes both launcher executables; outside native interval. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [schemas/workload-measurement-v2.schema.json](../../../../schemas/workload-measurement-v2.schema.json), [docs/measurement.md](../../../measurement.md) |

## B0011

[Lines 83–85](../../../../tools/run_measurements.py#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L85:sha256:8ae74c183eec50c296f7a25a185a16254436548742e1e084714de240cf1bef38
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent Python helper boundary: Hashes bind current bytes; filesystem freshness checks are not cryptographic build lineage. |
| inputs / outputs | Explanatory source text only; no checked observation is produced. |
| invariants | The note does not execute validation or establish the described result. Its neighboring callable contract defines the actual behavior. |
| ownership | No runtime owner or state is introduced by this comment. |
| failure | No Python runtime failure branch in comment text. |
| cost | No execution from this note; the described helper work is charged at that helper. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/measurement.md](../../../measurement.md), [docs/code_review.md](../../../code_review.md) |

## B0012

[Lines 86–168](../../../../tools/run_measurements.py#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def build_provenance(source_root, build, crown, collector, extra_binaries=()):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind actual binaries, objects, source dependencies and raw report schema with timestamp freshness checks. |
| inputs / outputs | Source/build and binaries in; detailed provenance graph out. |
| invariants | Requires colocated binaries and actual link/compile/dependency records. Hashes bind bytes; timestamps are not cryptographic lineage; dynamic libraries are not archived. Harness source list now pins raw schema v2. |
| ownership | Owns parsed commands, dependency lists and hashes; performs no build/source write. |
| failure | Missing/stale prerequisites raise ValueError; file/parse/compiler/Git errors propagate. Compiler/Git subprocesses are bounded at 30 seconds. |
| cost | Traverses build dependencies and hashes files; compiler/Git metadata commands run separately. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [schemas/workload-measurement-v2.schema.json](../../../../schemas/workload-measurement-v2.schema.json), [schemas/measurement-experiment-v1.schema.json](../../../../schemas/measurement-experiment-v1.schema.json), [tests/integration/measurement_build_provenance.py](../../../../tests/integration/measurement_build_provenance.py) |

## B0013

[Lines 169–171](../../../../tools/run_measurements.py#L169); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Experiment:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own command ledger, launch pins, fresh output and cumulative stdout/stderr grant. |
| inputs / outputs | Construct with output/CPU/timeout/byte limit; invoke records launch argv, target/launcher resources and streams. |
| invariants | Target RSS comes from GNU time sidecar; wait4 RSS is launcher_maxrss. CPU scope includes owned launch chain. Byte grant checks stdout+stderr after exit and excludes sidecar/sinks/packet. |
| ownership | Retains tool pins, scalar grants and ledger; per-call children/streams/resource records have invocation scope. |
| failure | Constructor may fail while resolving/hashing tools; invoke checks process/resource outcomes and is not a general transaction. |
| cost | Fixed state plus executable hashes; each invocation adds time and optional taskset process launch and command metadata. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [schemas/workload-measurement-v2.schema.json](../../../../schemas/workload-measurement-v2.schema.json), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py) |

## B0014

[Lines 172–175](../../../../tools/run_measurements.py#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def __init__(self, output, cpu, timeout, byte_limit):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize command state and pin required external launchers. |
| inputs / outputs | Output Path/CPU/timeout/byte cap in; initializes counters, command list and tool paths/hashes. |
| invariants | Creates no directory/process. time and taskset must both be discoverable even when CPU is None. |
| ownership | Retains passed values and owns fresh ledger/tool mappings. |
| failure | Launcher/hash errors propagate; caller may already have created output directory. |
| cost | Fixed initialization plus PATH lookup and full reads/hashes of two executables. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py) |

## B0015

[Lines 176–177](../../../../tools/run_measurements.py#L176); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L176-L177:sha256:f998844e37a34230c63d6698f15d1ba3dbf558f655881f79e6d5397b16260402
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent Python helper boundary: Raw-output bytes are checked after the child exits; sink files are outside this grant. |
| inputs / outputs | Explanatory source text only; no checked observation is produced. |
| invariants | The note does not execute validation or establish the described result. Its neighboring callable contract defines the actual behavior. |
| ownership | No runtime owner or state is introduced by this comment. |
| failure | No Python runtime failure branch in comment text. |
| cost | No execution from this note; the described helper work is charged at that helper. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/measurement.md](../../../measurement.md), [docs/code_review.md](../../../code_review.md) |

## B0016

[Lines 178–222](../../../../tools/run_measurements.py#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def invoke(self, label, arguments):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one child through the external resource/affinity launch chain and retain target RSS separately from launcher RSS. |
| inputs / outputs | Label/target argv in; JSON stdout and command record with actual launch argv, sidecar hash, wait4 RSS/CPU and stream hashes out. |
| invariants | GNU time writes target %M; optional taskset applies affinity without Python preexec_fn. wait4 polls at 2ms; timeout kills/reaps process group. Record is saved before timeout/cap/exit/RSS checks. Byte cap is post-child. |
| ownership | Owns stream handles, child chain, sidecar and ledger record; packet files persist. |
| failure | Timeout can yield empty/missing sidecar and None RSS before TimeoutError. Success requires a nonnegative numeric target RSS. Nonzero/stderr/cap/parse/IO errors propagate; no generic interrupt cleanup promise. |
| cost | Adds launcher processes, polling, resource-file IO, hashing, JSON parse and full ledger rewrite. Sidecar/sink bytes are outside stdout/stderr grant. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [schemas/workload-measurement-v2.schema.json](../../../../schemas/workload-measurement-v2.schema.json), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py), [docs/measurement.md](../../../measurement.md) |

## B0018

[Lines 224–225](../../../../tools/run_measurements.py#L224); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def save_commands(self):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rewrite the complete command journal after an invocation. |
| inputs / outputs | Captured output directory and command list in; overwrites commands.json pretty JSON. |
| invariants | Write is sequential, non-atomic and not fsynced; it does not certify command success. |
| ownership | Borrows ledger; owns complete serialized text; filesystem keeps output. |
| failure | IO/JSON/OOM failures propagate and may leave partial ledger; no catch/retry. |
| cost | O(cumulative command-metadata bytes) serialization/write per call, so total journal rewriting can grow quadratically in command count. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/measurement.md](../../../measurement.md), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py), [tests/integration/measurement_build_provenance.py](../../../../tests/integration/measurement_build_provenance.py), [schemas/workload-measurement-v1.schema.json](../../../../schemas/workload-measurement-v1.schema.json), [schemas/measurement-experiment-v1.schema.json](../../../../schemas/measurement-experiment-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0020

[Lines 228–238](../../../../tools/run_measurements.py#L228); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def indexed_options():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the explicit finite indexed-backend physical/storage work grants used in this experiment. |
| inputs / outputs | No args; fresh nested schema_version2 options dict out. |
| invariants | Nine component slots and five operation work counters are local measured configuration, not implicit changed engine defaults or paper asymptotic constants. |
| ownership | Owns fresh nested dicts/limit maps; literal strings/scalars shared immutable. |
| failure | Allocation/OOM failure propagates; no native validation until compile/lower. |
| cost | Fixed-size dictionary/list/zip/comprehension allocations; no table scan or process. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/measurement.md](../../../measurement.md), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py), [tests/integration/measurement_build_provenance.py](../../../../tests/integration/measurement_build_provenance.py), [schemas/workload-measurement-v1.schema.json](../../../../schemas/workload-measurement-v1.schema.json), [schemas/measurement-experiment-v1.schema.json](../../../../schemas/measurement-experiment-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0022

[Lines 241–259](../../../../tools/run_measurements.py#L241); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def summarize(reports):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Aggregate retained measured event/output samples by phase and accounting scope. |
| inputs / outputs | Measured report sequence in; distributions, phase sums, output-row total and accounting note out. |
| invariants | Caller excludes warmups. Native prepare includes internal delta work; optional operator metrics overlap and must not be summed across layers. Query cumulative peak is not per-event incremental/RSS. |
| ownership | Owns flattened event-reference list, multiple temporary sample lists/distributions and phase dict; report rows remain borrowed. |
| failure | Missing/malformed report fields or distribution/type/OOM errors propagate. |
| cost | Several full event/output-call traversals and independent sorts per metric; retains O(events+calls) sample references/values while constructing summary. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/measurement.md](../../../measurement.md), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py), [tests/integration/measurement_build_provenance.py](../../../../tests/integration/measurement_build_provenance.py), [schemas/workload-measurement-v1.schema.json](../../../../schemas/workload-measurement-v1.schema.json), [schemas/measurement-experiment-v1.schema.json](../../../../schemas/measurement-experiment-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0024

[Lines 262–393](../../../../tools/run_measurements.py#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run(args):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight and measure selected workload cases with target/launcher resource separation. |
| inputs / outputs | Parsed source/pack/build/binary/output and finite experiment grants in; experiment/commands/raw reports/requests/sinks/summaries out. |
| invariants | Validates deterministic pack and build before trials; each configuration passes independent verification before warmup/measurement. Raw records are v2, request stays v1. Report path strings are retained and one repetition group is loaded for each summary. |
| ownership | Owns manifests/oracles/bound inputs/plans/preflight records and packet; report files stay on disk, temporary summary DOMs belong to one group. |
| failure | Failures in trial block save failed status then rethrow; setup failures may create no packet; sequential writes have no rollback. |
| cost | Full pack/oracle and build scans, helper/collector children, sinks and summary rereads. Path retention avoids keeping all parsed report DTOs; GNU time/taskset and sidecars add external IO, not engine update work. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [schemas/workload-measurement-v2.schema.json](../../../../schemas/workload-measurement-v2.schema.json), [schemas/measurement-experiment-v1.schema.json](../../../../schemas/measurement-experiment-v1.schema.json), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py) |

```text
def save(): (output / 'experiment.json').write_text(json.dumps(packet, indent=2) + '\n')
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Persist the current B03 experiment status without hiding earlier raw artifacts. |
| inputs / outputs | Captured packet/output in; overwrites experiment.json. |
| invariants | Status running/failed/complete is a DTO; completed validation records supply evidence, flag alone grants no native authority. |
| ownership | Owns serialization temporary; packet borrowed, persisted file retained. |
| failure | Write/JSON/OOM errors propagate including during failure handling; no atomic rename or fsync. |
| cost | O(entire cumulative packet bytes) rewrite after progress, potentially repeated large graph serialization. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/measurement.md](../../../measurement.md), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py), [tests/integration/measurement_build_provenance.py](../../../../tests/integration/measurement_build_provenance.py), [schemas/workload-measurement-v1.schema.json](../../../../schemas/workload-measurement-v1.schema.json), [schemas/measurement-experiment-v1.schema.json](../../../../schemas/measurement-experiment-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0026

[Lines 396–409](../../../../tools/run_measurements.py#L396); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse the explicit controlled-measurement CLI and dispatch run. |
| inputs / outputs | Required source/build/crown/collector/output Paths plus case/backend/mode/repetition/codec/sink/observation/grant options in. |
| invariants | argparse enumerates supported labels; run applies numeric/context limits and all correctness gates. --help is handled before native runs. |
| ownership | Owns parser and args, then run owns packet/IO lifetime. |
| failure | Argparse SystemExit for usage; operational errors reach script wrapper. |
| cost | Fixed parser/argument work followed by full run cost, not a hot runtime hook. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/measurement.md](../../../measurement.md), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py), [tests/integration/measurement_build_provenance.py](../../../../tests/integration/measurement_build_provenance.py), [schemas/workload-measurement-v1.schema.json](../../../../schemas/workload-measurement-v1.schema.json), [schemas/measurement-experiment-v1.schema.json](../../../../schemas/measurement-experiment-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0027

[Lines 410–415](../../../../tools/run_measurements.py#L410); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == '__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the B03 controlled measurement runner only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | Catches Exception, prints B03 diagnostic and exits1; does not catch SystemExit/KeyboardInterrupt or remove retained artifacts. |
| cost | Fixed guard/error presentation plus run; no hidden native work outside main. |
| Design | [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/measurement.md](../../../measurement.md), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [tests/integration/measurement_harness.py](../../../../tests/integration/measurement_harness.py), [tests/integration/measurement_build_provenance.py](../../../../tests/integration/measurement_build_provenance.py), [schemas/workload-measurement-v1.schema.json](../../../../schemas/workload-measurement-v1.schema.json), [schemas/measurement-experiment-v1.schema.json](../../../../schemas/measurement-experiment-v1.schema.json), [docs/code_review.md](../../../code_review.md) |
