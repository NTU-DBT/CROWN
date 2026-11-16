#!/usr/bin/env python3
"""Plot analyzer CSVs for finite B05 adversarial workload experiments."""
from __future__ import annotations

import argparse
import csv
import hashlib
import json
import statistics
from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt


ROW_COLUMNS = """family scale axis axis_value backend mode repetition events changed_events output_rows
native_ns_per_event active_ns_per_event output_next_ns_per_output query_current_max
query_peak_requested process_maxrss_KiB source_slots_max support_slots_max
support_native_visits_per_event raw_report raw_sha256""".split()
PROBE_COLUMNS = """family scale backend mode repetition sequence phase completed_cycles
source_live_rows source_slots support_slots query_current_requested_bytes cursor_work
output_next_ns event_active_ns""".split()
PANELS = (
    ("native_ns_per_event", "Native prepare/commit (ns/event)"),
    ("query_current_max", "Query current requested bytes (max)"),
    ("source_slots_max", "Source slots (max)"),
    ("support_native_visits_per_event", "Support native record visits/event"),
    ("query_peak_requested", "Cumulative query-account peak (bytes)"),
    ("process_maxrss_KiB", "Target process peak RSS (KiB)"),
)
SENTINEL_PANELS = (
    ("query_current_requested_bytes", "Query current requested bytes"),
    ("source_slots", "Source slots"),
    ("support_slots", "Support slots"),
    ("cursor_work", "Cursor work"),
    ("event_active_ns", "Event active time (ns)"),
)
CHURN = {"churn_fresh", "churn_reuse", "churn_projected", "churn_star", "churn_path", "churn_self_join"}


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def read_csv(path: Path, required: list[str], allow_empty: bool = False) -> list[dict]:
    if allow_empty and path.stat().st_size == 0:
        return []
    with path.open(encoding="utf-8-sig", newline="") as stream:
        reader = csv.DictReader(stream)
        if not reader.fieldnames: raise SystemExit(f"{path} has no CSV header")
        missing = set(required) - set(reader.fieldnames)
        if missing: raise SystemExit(f"{path} is missing columns: {', '.join(sorted(missing))}")
        return list(reader)


def draw(ax, records: list[dict], x_field: str, metric: str, ylabel: str,
         xlabel: str, styles: dict) -> None:
    xs = sorted({float(row[x_field]) for row in records})
    any_values = False
    omissions = []
    for (backend, mode), style in styles.items():
        medians, valid_y, lows, highs, valid_x = [], [], [], [], []
        missing = 0
        for x in xs:
            matching = [r for r in records if r["backend"] == backend and r["mode"] == mode
                        and float(r[x_field]) == x]
            values = [r["_" + metric] for r in matching if r["_" + metric] is not None]
            missing += len(matching) - len(values) + (not bool(matching))
            if values:
                median = statistics.median(values)
                medians.append(median)
                valid_y.append(median)
                lows.append(min(values))
                highs.append(max(values))
                valid_x.append(x)
            else:
                medians.append(float("nan"))
        label = f"{backend} / {mode}"
        if missing:
            omissions.append(f"{label}: {missing} missing/absent")
        if valid_x:
            ax.plot(xs, medians, color=style["color"], linestyle=style["line"])
            low = [m - lo for m, lo in zip(valid_y, lows)]
            high = [hi - m for m, hi in zip(valid_y, highs)]
            ax.errorbar(valid_x, valid_y, yerr=[low, high], fmt=style["marker"],
                        linestyle="none", color=style["color"], capsize=3, label=label)
            any_values = True
        else:
            ax.plot([], [], color=style["color"], linestyle=style["line"],
                    marker=style["marker"], label=label + " (unavailable)")
    ax.set_ylabel(ylabel)
    log_x = len(xs) > 1 and xs[0] > 0 and xs[-1] / xs[0] >= 16
    ax.set_xlabel(xlabel + (" (log2 scale)" if log_x else ""))
    if log_x:
        ax.set_xscale("log", base=2)
    if len(xs) <= 12:
        ax.set_xticks(xs)
    ax.grid(True, which="both", alpha=0.25)
    if not any_values:
        ax.text(0.5, 0.5, "No finite values; missing data shown in legend",
                ha="center", va="center", transform=ax.transAxes)
    if omissions:
        ax.text(0.02, 0.98, "\n".join(omissions), va="top", fontsize=6, transform=ax.transAxes)


def figure(records: list[dict], x_field: str, xlabel: str, panels: tuple,
           title: str, output: Path, stem: str, artifacts: list[dict]) -> None:
    pairs = sorted({(r["backend"], r["mode"]) for r in records})
    colors = plt.rcParams["axes.prop_cycle"].by_key()["color"]
    markers = ("o", "s", "^", "D", "v", "P")
    lines = {"maintenance": "-", "snapshot": "--", "delta": ":"}
    styles = {pair: {"color": colors[i % len(colors)], "marker": markers[i % len(markers)],
                     "line": lines.get(pair[1], "-.")} for i, pair in enumerate(pairs)}
    nrows, ncols = (2, 2) if len(panels) == 4 else (3, 2)
    fig, axes = plt.subplots(nrows, ncols, figsize=(12, 8 if nrows == 2 else 10))
    fig.suptitle(title)
    for ax, (metric, ylabel) in zip(axes.flat, panels):
        draw(ax, records, x_field, metric, ylabel, xlabel, styles)
    for ax in list(axes.flat)[len(panels):]:
        ax.set_visible(False)
    fig.text(0.5, 0.015,
             "Points are medians across repetitions; bars are observed min–max, not confidence intervals. "
             "Y axes are linear; zero and negative values are retained.",
             ha="center", fontsize=9)
    # One legend leaves the measured curves visible in every panel.
    handles, labels = axes.flat[0].get_legend_handles_labels()
    if len(panels) != 5:
        fig.legend(handles, labels, loc="lower center", bbox_to_anchor=(0.5, 0.04), ncol=2, fontsize=8)
        bottom = 0.17
    else:
        legend = list(axes.flat)[-1]
        legend.set_visible(True)
        legend.axis("off")
        legend.legend(handles, labels, loc="center", frameon=False, fontsize=9)
        bottom = 0.055
    fig.tight_layout(rect=(0, bottom, 1, 0.94))
    for extension in ("png", "pdf"):
        path = output / f"{stem}.{extension}"
        fig.savefig(path, dpi=160 if extension == "png" else None, bbox_inches="tight")
        artifacts.append({"path": path.name, "bytes": path.stat().st_size, "sha256": digest(path)})
    plt.close(fig)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--input", type=Path, required=True, help="Analyzer directory with rows.csv and probes.csv")
    parser.add_argument("--output", type=Path, required=True, help="New figures directory; must not exist")
    args = parser.parse_args()
    source = Path(__file__).resolve()
    input_dir, output = args.input.expanduser().resolve(), args.output.expanduser().resolve()
    if not input_dir.is_dir(): raise SystemExit(f"input directory does not exist: {input_dir}")
    if output.exists() or output.is_symlink(): raise SystemExit(f"output path already exists: {output}")
    rows_path, probes_path = input_dir / "rows.csv", input_dir / "probes.csv"
    if not rows_path.is_file() or not probes_path.is_file():
        raise SystemExit("input directory must contain rows.csv and probes.csv")
    rows = read_csv(rows_path, ROW_COLUMNS)
    probes = read_csv(probes_path, PROBE_COLUMNS, allow_empty=True)
    if not rows: raise SystemExit("rows.csv contains no measurements")
    for row in rows:
        row["_x"], row["_scale"] = float(row["axis_value"]), int(row["scale"])
        for metric, _ in PANELS:
            row["_" + metric] = float(row[metric]) if row[metric].strip() else None
    for row in probes:
        row["_x"], row["_scale"] = int(row["completed_cycles"]), int(row["scale"])
        for metric, _ in SENTINEL_PANELS:
            row["_" + metric] = float(row[metric]) if row[metric].strip() else None
    families = {}
    for row in rows:
        families.setdefault(row["family"], []).append(row)
    churn = []
    for family in sorted(CHURN & set(families)):
        maximum = max(row["_scale"] for row in families[family])
        selected = [r for r in probes if r["family"] == family and r["_scale"] == maximum
                    and r["phase"] == "sentinel_probe"]
        if not selected: raise SystemExit(f"no sentinel_probe records for {family} at maximum scale {maximum}")
        churn.append((family, maximum, selected))
    output.mkdir(parents=True, exist_ok=False)
    artifacts = []
    for family, data in sorted(families.items()):
        xlabel = data[0]["axis"].replace("_", " ")
        figure(data, "_x", xlabel, PANELS, f"B05 family: {family}",
               output, family.replace("/", "_"), artifacts)
    for family, maximum, data in churn:
        figure(data, "_x", "Completed churn cycles", SENTINEL_PANELS,
               f"{family}: sentinel probes at maximum scale {maximum}; other phases excluded",
               output, f"{family}-sentinel-probes", artifacts)
    manifest = {
        "schema_version": 1, "kind": "b05_adversarial_scalability_plots",
        "inputs": [{"path": p.name, "bytes": p.stat().st_size, "sha256": digest(p)}
                   for p in (rows_path, probes_path)],
        "plotter": {"path": str(source), "bytes": source.stat().st_size,
                    "sha256": digest(source), "matplotlib_version": matplotlib.__version__,
                    "backend": matplotlib.get_backend()},
        "summary": {"families": sorted(families), "row_records": len(rows), "probe_records": len(probes),
                    "interval": "observed min/max across repetitions; not a confidence interval",
                    "x_scale": "log2 when all x are positive and max/min is at least 16; otherwise linear"},
        "figures": artifacts,
    }
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(f"Wrote {len(artifacts)} PNG/PDF files for {len(families)} families to {output}")


if __name__ == "__main__":
    main()
