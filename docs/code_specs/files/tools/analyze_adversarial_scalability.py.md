# `tools/analyze_adversarial_scalability.py` — block usage map

[Source](../../../../tools/analyze_adversarial_scalability.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `ececa3fcd94c255b5aa622212f71dfd1b0f9e72ce5da9e66047ee5a34e613bf4`. 217 lines partitioned into 17 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../tools/analyze_adversarial_scalability.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 22–24](../../../../tools/analyze_adversarial_scalability.py#L22) | Callable definition: def require(value, message): | calls ValueError; guard def require(value, message): · [reviewed contract](#b0002) |
| [B0003 · 25–26](../../../../tools/analyze_adversarial_scalability.py#L25) | Explanatory comments or spacing. |  |
| [B0004 · 27–29](../../../../tools/analyze_adversarial_scalability.py#L27) | Callable definition: def digest(path): | calls open, file_digest, hexdigest; returns hashlib.file_digest(stream, 'sha256').hexdigest() · [reviewed contract](#b0004) |
| [B0005 · 30–31](../../../../tools/analyze_adversarial_scalability.py#L30) | Explanatory comments or spacing. |  |
| [B0006 · 32–33](../../../../tools/analyze_adversarial_scalability.py#L32) | Callable definition: def read(path): | calls loads, read_text; returns json.loads(path.read_text()) · [reviewed contract](#b0006) |
| [B0007 · 34–35](../../../../tools/analyze_adversarial_scalability.py#L34) | Explanatory comments or spacing. |  |
| [B0008 · 36–40](../../../../tools/analyze_adversarial_scalability.py#L36) | Callable definition: def checked(path, expected, pins): | calls require, digest, str, read; guard require(digest(path) == expected, 'input fingerprint mismatch: ' + str(path)); returns read(path) · [reviewed contract](#b0008) |
| [B0009 · 41–42](../../../../tools/analyze_adversarial_scalability.py#L41) | Explanatory comments or spacing. |  |
| [B0010 · 43–45](../../../../tools/analyze_adversarial_scalability.py#L43) | Callable definition: def extent(values): | calls min, median, max; returns {'minimum': min(values), 'median': statistics.median(values), 'maximum': max(values)} · [reviewed contract](#b0010) |
| [B0011 · 46–47](../../../../tools/analyze_adversarial_scalability.py#L46) | Explanatory comments or spacing. |  |
| [B0012 · 48–53](../../../../tools/analyze_adversarial_scalability.py#L48) | Callable definition: def write_csv(path, rows): | calls open, DictWriter, list, writeheader · [reviewed contract](#b0012) |
| [B0013 · 54–55](../../../../tools/analyze_adversarial_scalability.py#L54) | Explanatory comments or spacing. |  |
| [B0014 · 56–205](../../../../tools/analyze_adversarial_scalability.py#L56) | Callable definition: def analyze(packet, output): | calls read, require, len, str; guard require(root\['kind'\] == 'b05_parameterized_native_stress' and root\['status'\] == 'complete', 'B05 ba…; returns dict(measured_runs=len(rows), parameter_points=len(root\['cases'\]), derived_groups=len(groups)); 54 loop sites · [reviewed contract](#b0014) |
| [B0015 · 206–207](../../../../tools/analyze_adversarial_scalability.py#L206) | Explanatory comments or spacing. |  |
| [B0016 · 208–213](../../../../tools/analyze_adversarial_scalability.py#L208) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, print · [reviewed contract](#b0016) |
| [B0017 · 214–217](../../../../tools/analyze_adversarial_scalability.py#L214) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0017) |

## B0001

[Lines 1–21](../../../../tools/analyze_adversarial_scalability.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
METRICS = (
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select nine exported metric names for the counters table, including mandatory work exposed through observation. |
| inputs / outputs | Fixed metric tuple used while grouping epoch samples. |
| invariants | Layers overlap; units/availability/saturation/includes stay attached and are not summed as synthetic work. |
| ownership | Immutable module tuple. |
| failure | Absent values stay unavailable. |
| cost | Fixed constant storage. |
| Design | [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0002

[Lines 22–24](../../../../tools/analyze_adversarial_scalability.py#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value, message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise ValueError when a receipt predicate is false. |
| inputs / outputs | Predicate/message in; None on truth, ValueError otherwise. |
| invariants | Fail-fast; does not repair input. |
| ownership | Borrows arguments for call. |
| failure | False predicate raises ValueError. |
| cost | One truth test. |
| Design | [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0004

[Lines 27–29](../../../../tools/analyze_adversarial_scalability.py#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def digest(path):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash one exact packet artifact. |
| inputs / outputs | Path in; SHA-256 string out. |
| invariants | Hash binds bytes; caller checks semantics. |
| ownership | File handle scoped to call. |
| failure | File/read errors propagate. |
| cost | Streams full file. |
| Design | [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0006

[Lines 32–33](../../../../tools/analyze_adversarial_scalability.py#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def read(path):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse one JSON artifact. |
| inputs / outputs | Path in; owning decoded object out. |
| invariants | No schema check in this helper. |
| ownership | Returned DOM owns decoded data. |
| failure | File/Unicode/JSON errors propagate. |
| cost | Reads/materializes full file. |
| Design | [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0008

[Lines 36–40](../../../../tools/analyze_adversarial_scalability.py#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def checked(path, expected, pins):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require exact artifact digest and record the input pin. |
| inputs / outputs | Path/expected digest/mutable pin map in; parsed JSON out. |
| invariants | Hash binds bytes and caller checks role. Inputs must remain stable between the hash read and JSON read; this helper does not provide an atomic filesystem snapshot. |
| ownership | Mutates caller pin map; returns owning DOM. |
| failure | Mismatch raises ValueError; I/O/JSON errors propagate. |
| cost | Hashes then rereads/parses full file. |
| Design | [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0010

[Lines 43–45](../../../../tools/analyze_adversarial_scalability.py#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def extent(values):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Summarize repetitions by observed minimum, median and maximum. |
| inputs / outputs | Nonempty numeric list in; three-value dict out. |
| invariants | Empirical range only; not a confidence interval. |
| ownership | Returns scalars. |
| failure | Empty input fails at min/max; analyzer supplies populated groups. |
| cost | Computes median/extrema over values. |
| Design | [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0012

[Lines 48–53](../../../../tools/analyze_adversarial_scalability.py#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def write_csv(path, rows):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a derived CSV at a new file path. |
| inputs / outputs | Path/row list in; CSV artifact out. |
| invariants | Exclusive create; empty rows produce zero-byte file with no header, which is allowed for probes. |
| ownership | Borrows rows; filesystem owns file. |
| failure | Existing path/CSV/I/O errors propagate; a write failure may leave partial file. |
| cost | Writes header if nonempty, then all rows. |
| Design | [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0014

[Lines 56–205](../../../../tools/analyze_adversarial_scalability.py#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def analyze(packet, output):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile completed B05/B03 packets, raw-v2 frames, checked plan and target-RSS sidecars; write derived tables. |
| inputs / outputs | Packet dir and new output dir in; rows/phases/counters/probes/availability CSVs, summary, Markdown and artifact manifest out. |
| invariants | Checks point coverage, B03 gate, labels/config, byte pins, backend/mode from label, exact plan hash, output/termination/sink census, source population and arena slot partitions. Target RSS must match hashed sidecar, command and run row; inherited-wait4-only RSS is rejected. Selected checks only, not full schema validation; probes may be empty. |
| ownership | Loads raw reports sequentially and retains derived rows/pins; temporary references can overlap consecutive report DOMs without retaining all reports. Does not write input files. Caller must keep input bytes stable across separate hash/parse reads; no atomic filesystem snapshot is provided. |
| failure | Mismatch raises ValueError; missing keys/type/JSON/IO/CSV errors propagate. Later writes can leave partial output. |
| cost | Hashes/parses packets and scans all retained epochs/calls, including warmups for checks; derives measured-only tables, groups outputs and writes files. No native child or acceptance decision. |
| Design | [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [tools/run_adversarial_scalability.py](../../../../tools/run_adversarial_scalability.py), [tools/run_measurements.py](../../../../tools/run_measurements.py), [tools/verify_workloads.py](../../../../tools/verify_workloads.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0016

[Lines 208–213](../../../../tools/analyze_adversarial_scalability.py#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose analysis with required packet/output paths. |
| inputs / outputs | Resolves --packet/--output and prints analyze() summary. |
| invariants | Requires completed packet and fresh output; does not run measurements. |
| ownership | Args/result are process-local. |
| failure | Argparse/analyze failures propagate. |
| cost | Parse, delegate, print small result. |
| Design | [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0017

[Lines 214–217](../../../../tools/analyze_adversarial_scalability.py#L214); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == '__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run analyzer CLI only on direct execution. |
| inputs / outputs | Guard delegates to main(). |
| invariants | Import defines helpers without reading packet. |
| ownership | Process owns streams; analyze() owns files. |
| failure | Unhandled errors use normal traceback/exit. |
| cost | One guard/call. |
| Design | [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |
