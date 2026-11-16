# `tools/plot_adversarial_scalability.py` — block usage map

[Source](../../../../tools/plot_adversarial_scalability.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `ae3d915fcef92a40f1fd8c32389e4bf46120695a15bf7ea666ef259e6499e84a`. 206 lines partitioned into 12 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../tools/plot_adversarial_scalability.py#L1) | Imports dependencies. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 18–42](../../../../tools/plot_adversarial_scalability.py#L18) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0002) |
| [B0003 · 43–44](../../../../tools/plot_adversarial_scalability.py#L43) | Callable definition: def digest(path: Path) -&gt; str: | calls sha256, read_bytes, hexdigest; returns hashlib.sha256(path.read_bytes()).hexdigest() · [reviewed contract](#b0003) |
| [B0004 · 45–46](../../../../tools/plot_adversarial_scalability.py#L45) | Explanatory comments or spacing. |  |
| [B0005 · 47–55](../../../../tools/plot_adversarial_scalability.py#L47) | Callable definition: def read_csv(path: Path, required: list\[str\], allow_empty: bool = False) -&gt; list\[dict\]: | calls stat, open, DictReader, SystemExit; returns \[\]; list(reader) · [reviewed contract](#b0005) |
| [B0006 · 56–57](../../../../tools/plot_adversarial_scalability.py#L56) | Explanatory comments or spacing. |  |
| [B0007 · 58–105](../../../../tools/plot_adversarial_scalability.py#L58) | Callable definition: def draw(ax, records: list\[dict\], x_field: str, metric: str, ylabel: str, | calls sorted, float, items, len; 7 loop sites · [reviewed contract](#b0007) |
| [B0008 · 106–107](../../../../tools/plot_adversarial_scalability.py#L106) | Explanatory comments or spacing. |  |
| [B0009 · 108–143](../../../../tools/plot_adversarial_scalability.py#L108) | Callable definition: def figure(records: list\[dict\], x_field: str, xlabel: str, panels: tuple, | calls sorted, by_key, len, get; 5 loop sites; source comment (unverified): # One legend leaves the measured curves visible in every panel. · [reviewed contract](#b0009) |
| [B0010 · 144–145](../../../../tools/plot_adversarial_scalability.py#L144) | Explanatory comments or spacing. |  |
| [B0011 · 146–202](../../../../tools/plot_adversarial_scalability.py#L146) | Callable definition: def main() -&gt; None: | calls ArgumentParser, add_argument, parse_args, Path; 13 loop sites · [reviewed contract](#b0011) |
| [B0012 · 203–206](../../../../tools/plot_adversarial_scalability.py#L203) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0012) |

## B0001

[Lines 1–17](../../../../tools/plot_adversarial_scalability.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
matplotlib.use("Agg")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select Matplotlib’s noninteractive backend before importing pyplot. |
| inputs / outputs | Sets Agg backend for this process. |
| invariants | Reporting only; measurement/native execution does not import this plotter. |
| ownership | Matplotlib owns process-global plotting backend state. |
| failure | Backend/package import failures propagate. |
| cost | One backend selection and import. |
| Design | [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0002

[Lines 18–42](../../../../tools/plot_adversarial_scalability.py#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ROW_COLUMNS = """family scale axis axis_value backend mode repetition events changed_events output_rows
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the required per-run CSV fields used for family figures. |
| inputs / outputs | Module-level column-name literal is split once at import into the list required by read_csv(). |
| invariants | Does not derive or fill observations; base figures select metrics separately. |
| ownership | Module owns a mutable list of column-name strings. |
| failure | Missing columns fail in read_csv. |
| cost | One import-time split and fixed list storage; no per-event engine work. |
| Design | [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

```text
PROBE_COLUMNS = """family scale backend mode repetition sequence phase completed_cycles
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the required probe CSV fields for sentinel figures. |
| inputs / outputs | Module-level column-name literal is split once at import into the list required by read_csv(). |
| invariants | An empty zero-byte probes file is separately permitted; nonempty files still need this complete header. |
| ownership | Module owns a mutable list of column-name strings. |
| failure | Missing header/columns fail in read_csv. |
| cost | One import-time split and fixed list storage; no per-event engine work. |
| Design | [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

```text
PANELS = (
    ("native_ns_per_event", "Native prepare/commit (ns/event)")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select six base metrics for each family figure. |
| inputs / outputs | Fixed metric/axis-label pairs: native time/event, max current query bytes, max source slots, support visits/event, cumulative query peak and target process RSS. |
| invariants | Missing values remain missing; the panel set does not equate query-account bytes, arena slots or process RSS. |
| ownership | Immutable module tuple. |
| failure | An absent CSV column fails before plotting; blank cells remain unavailable. |
| cost | Fixed six-pair storage. |
| Design | [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

```text
SENTINEL_PANELS = (
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select five metrics for sentinel probe figures. |
| inputs / outputs | Fixed pairs are query current bytes, source slots, support slots, cursor work and active event time. |
| invariants | Uses only \`sentinel_probe\` rows selected at the largest scale for each present churn family; it does not fill missing probes. |
| ownership | Immutable module tuple. |
| failure | Missing required columns or family sentinels raise SystemExit in main(). |
| cost | Fixed five-pair storage. |
| Design | [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

```text
CHURN = {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the six churn families eligible for sentinel probe figures. |
| inputs / outputs | Fixed family set used to intersect analyzer families and validate selected maximum-scale sentinel rows. |
| invariants | Absent churn families produce no sentinel figure; a present family without its required maximum-scale sentinels fails. |
| ownership | Module owns a mutable Python set of six fixed family-name strings. |
| failure | Missing required probes are rejected by main(). |
| cost | Fixed six-name storage. |
| Design | [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [tools/generate_adversarial_workloads.py](../../../../tools/generate_adversarial_workloads.py), [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0003

[Lines 43–44](../../../../tools/plot_adversarial_scalability.py#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def digest(path: Path) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash input CSVs and rendered figures for the plot manifest. |
| inputs / outputs | Path in; SHA-256 string out. |
| invariants | Hash binds bytes only. |
| ownership | File bytes are not retained after read_bytes returns. |
| failure | Read/hash errors propagate. |
| cost | Reads whole file into memory and hashes it. |
| Design | [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0005

[Lines 47–55](../../../../tools/plot_adversarial_scalability.py#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def read_csv(path: Path, required: list[str], allow_empty: bool = False) -> list[dict]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read CSV rows and require named columns, with an explicit zero-byte allowance for probes. |
| inputs / outputs | Path/required columns/allow_empty in; list of row dicts out. |
| invariants | Only zero-byte input is treated as empty when allowed; missing header/columns raise SystemExit. A header-only file returns no rows. |
| ownership | Returned list owns parsed strings/dicts; source file unchanged. |
| failure | Missing header/columns use SystemExit; I/O/CSV failures propagate. |
| cost | Materializes all rows in memory. |
| Design | [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0007

[Lines 58–105](../../../../tools/plot_adversarial_scalability.py#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def draw(ax, records: list[dict], x_field: str, metric: str, ylabel: str,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Draw one metric with repetition medians, observed min/max and missing-series notes. |
| inputs / outputs | Axes, converted rows, metric/x labels and style map in; axes mutated. |
| invariants | Missing/absent values are not zero. X is log2 only when positive range max/min is at least 16; y stays linear. Bars are observed min–max, not confidence intervals. |
| ownership | Borrows rows/styles and mutates axes only. |
| failure | Malformed numeric data and Matplotlib/allocation errors propagate. |
| cost | Scans rows by series/x, computes median/extrema, adds artists/text. |
| Design | [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0009

[Lines 108–143](../../../../tools/plot_adversarial_scalability.py#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def figure(records: list[dict], x_field: str, xlabel: str, panels: tuple,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render one family/sentinel figure with a shared legend and record PNG/PDF hashes. |
| inputs / outputs | Rows, labels, panels, output/stem and mutable artifact list in; saves two files and appends metadata. |
| invariants | Six base panels put one shared legend below plots; five sentinel panels use the sixth axes for the legend. Ranges remain observed repetition min–max. |
| ownership | Matplotlib owns temporary figure state; caller owns output directory and manifest list. |
| failure | Render/save/hash failures propagate; a partial figure set can remain. |
| cost | Creates axes/styles, draws panels, saves/hashes PNG and PDF, closes figure. |
| Design | [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0011

[Lines 146–202](../../../../tools/plot_adversarial_scalability.py#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert analyzer CSVs into family and churn-sentinel figures and a pinned manifest. |
| inputs / outputs | Requires input with rows.csv/probes.csv and a new output path. |
| invariants | Rows must be nonempty; zero-byte probes allowed. Each present churn family needs sentinel records at its maximum selected scale. Manifest binds CSVs, plotter/version/backend and figures; it does not schema-validate every analyzer field. |
| ownership | Owns row lists, numeric conversions, family groups and output metadata. |
| failure | Missing input/columns/sentinels or existing output raises SystemExit; parse/render/write failures propagate. Post-mkdir failure can leave partial files. |
| cost | Loads both CSVs, groups rows, renders two files per family plus sentinel figures, and writes manifest. No native process. |
| Design | [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [tools/analyze_adversarial_scalability.py](../../../../tools/analyze_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |

## B0012

[Lines 203–206](../../../../tools/plot_adversarial_scalability.py#L203); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run plot CLI only on direct execution. |
| inputs / outputs | Guard delegates to main(). |
| invariants | Import selects Agg/loads pyplot but reads no CSV or creates output. |
| ownership | Process owns Matplotlib state; main owns files. |
| failure | Unhandled errors use normal Python traceback/exit. |
| cost | One guard/call. |
| Design | [tools/plot_adversarial_scalability.py](../../../../tools/plot_adversarial_scalability.py), [docs/adversarial_scalability.md](../../../adversarial_scalability.md), Refactor.md:1393-1395 |
