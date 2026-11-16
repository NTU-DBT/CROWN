#!/usr/bin/env python3
"""Render static scientific PNG/PDF figures from exact experimental tables."""
from collections import defaultdict
import argparse
import csv
from fractions import Fraction
import hashlib
import json
import os
from pathlib import Path
import re
import statistics
import sys

sys.dont_write_bytecode = True


def require(condition, message):
    if not condition:
        raise ValueError(message)


def digest(path):
    with path.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def csv_rows(path):
    with path.open(newline='') as stream:
        return list(csv.DictReader(stream))


def run(args):
    source, output = args.input.resolve(), args.output.resolve()
    require(not output.exists(), 'figure output must be new')
    manifest = json.loads((source/'artifact-manifest.json').read_text())
    for name in ('per_repetition_metrics.csv', 'report-index.json'):
        require(digest(source/name) == manifest['files'][name], 'plot input hash differs: '+name)
    rows = csv_rows(source/'per_repetition_metrics.csv')
    require(rows, 'no metric rows to plot')
    scopes = json.loads((source/'report-index.json').read_text())['scopes']
    output.mkdir(parents=True)
    os.environ.setdefault('MPLCONFIGDIR', str(output/'.matplotlib'))
    import matplotlib
    matplotlib.use('Agg')
    import matplotlib.pyplot as plt
    from plot_adversarial_scalability import figure, PANELS, SENTINEL_PANELS, CHURN
    artifacts = []; reused = []
    # Reuse the reviewed B05 plot API and its complete selected-family appendix.
    if (source/'b05-rows.csv').exists():
        for name in ('b05-rows.csv', 'b05-probes.csv'):
            require(digest(source/name) == manifest['files'][name], 'B05 plot input hash differs')
        b05 = csv_rows(source/'b05-rows.csv'); probes = csv_rows(source/'b05-probes.csv')
        for row in b05:
            row['_x'], row['_scale'] = float(row['axis_value']), int(row['scale'])
            for metric, _ in PANELS:
                row['_'+metric] = float(row[metric]) if row[metric] else None
        for row in probes:
            row['_x'], row['_scale'] = int(row['completed_cycles']), int(row['scale'])
            for metric, _ in SENTINEL_PANELS:
                row['_'+metric] = float(row[metric]) if row[metric] else None
        for family in sorted({row['family'] for row in b05}):
            selected = [row for row in b05 if row['family'] == family]
            figure(selected, '_x', selected[0]['axis'].replace('_', ' '), PANELS,
                   'B05 selected family: '+family, output, 'b05-'+family, artifacts)
            if family in CHURN:
                maximum = max(row['_scale'] for row in selected)
                sentinel = [row for row in probes if row['family'] == family and row['_scale'] == maximum and row['phase'] == 'sentinel_probe']
                if sentinel:
                    figure(sentinel, '_x', 'Completed churn cycles', SENTINEL_PANELS,
                           family+': fixed-live-state sentinel probes', output, 'b05-'+family+'-sentinels', artifacts)
        import plot_adversarial_scalability as b05_plotter
        reused.append({'path': str(Path(b05_plotter.__file__).resolve()), 'sha256': digest(Path(b05_plotter.__file__))})
    metrics = {
        'planning': ('native_prepare_and_epoch_release_ns_per_input', 'event_active_ns_per_input', 'query_peak_requested_bytes', 'process_maxrss_KiB'),
        'operational': ('loop_ns_per_input', 'epochs.apply_ns_p95', 'query_current_requested_bytes', 'process_maxrss_KiB'),
        'matched': ('loop_ns_per_input', 'epochs.apply_ns_p95', 'query_current_requested_bytes', 'process_maxrss_KiB'),
        'search': ('algorithm_ns', 'process_wall_ns', 'retained_candidates', 'process_maxrss_KiB'),
        'specialization': ('loop_ns_per_input', 'execution_prepare_ns', 'query_current_requested_bytes', 'process_maxrss_KiB'),
    }
    x_labels = {'planning': 'Held-out trace', 'operational': 'Input width',
                'matched': 'Input width', 'search': 'Work grant (categorical)',
                'specialization': 'Case'}
    metric_labels = {'native_prepare_and_epoch_release_ns_per_input': 'Native prepare + epoch release',
                     'event_active_ns_per_input': 'Active event work', 'query_peak_requested_bytes': 'Peak query account',
                     'process_maxrss_KiB': 'Peak process RSS', 'loop_ns_per_input': 'Owner loop',
                     'epochs.apply_ns_p95': 'Apply latency (p95)', 'query_current_requested_bytes': 'Current query account',
                     'algorithm_ns': 'Algorithm time', 'process_wall_ns': 'Process wall time',
                     'retained_candidates': 'Retained candidates', 'execution_prepare_ns': 'Receiving freeze + execution preparation'}
    facets = sorted({(row['study'], row['facet']) for row in rows if row['study'] != 'b05'})
    for study, facet in facets:
        selected = [row for row in rows if row['study'] == study and row['facet'] == facet]
        xs = sorted({row['x'] for row in selected}, key=lambda x: (0, int(x)) if x.isdigit() else (1, x))
        positions = {x: number for number, x in enumerate(xs)}
        qualifier = '' if scopes[study]['full_source_scope'] else ' (selected subset)'
        fig, axes = plt.subplots(2, 2, figsize=(12, 8)); fig.suptitle(study+': '+facet+qualifier)
        used = []
        for axis, metric in zip(axes.flat, metrics[study]):
            values = [row for row in selected if row['metric'] == metric]
            unit = next((row['unit'] for row in values), 'unavailable')
            for series in sorted({row['series'] for row in selected}):
                points, medians, lows, highs = [], [], [], []
                for x in xs:
                    cells = [row for row in values if row['series'] == series and row['x'] == x and row['availability'] == 'available']
                    if not cells:
                        continue
                    samples = [Fraction(int(row['numerator']), int(row['denominator'])) for row in cells]
                    median = statistics.median(samples); points.append(positions[x]); medians.append(float(median))
                    lows.append(float(median-min(samples))); highs.append(float(max(samples)-median)); used.extend(row['row_id'] for row in cells)
                if points:
                    axis.errorbar(points, medians, yerr=[lows, highs], marker='o', capsize=3, label=series)
                else:
                    axis.plot([], [], label=series+' (unavailable)')
            ticks = [x.removeprefix('evaluation_').replace('_', ' ') if study == 'planning' else x for x in xs]
            axis.set_xticks(list(positions.values()), ticks, rotation=20, ha='right')
            axis.set_xlabel(x_labels[study]); axis.set_ylabel(metric_labels[metric]+'\n'+unit); axis.grid(alpha=0.25)
        handles, labels = axes.flat[0].get_legend_handles_labels()
        columns = min(4, max(1, len(labels)))
        legend_rows = (len(labels)+columns-1)//columns
        fig.legend(handles, labels, loc='lower center', bbox_to_anchor=(0.5, 0.04), ncol=columns, fontsize=7)
        fig.text(0.5, 0.01, 'Median and observed min/max across measured process repetitions; no confidence interval. Missing is unavailable; zero stays zero. Search includes bounded attempts; exact stops remain in tables.', ha='center', fontsize=7)
        fig.tight_layout(rect=(0, 0.13+0.025*legend_rows, 1, 0.94))
        slug = re.sub(r'[^A-Za-z0-9_.-]+', '_', facet)[:80]+'-'+hashlib.sha256(facet.encode()).hexdigest()[:8]
        for extension in ('png', 'pdf'):
            path = output/(study+'-'+slug+'.'+extension)
            fig.savefig(path, dpi=160, bbox_inches='tight', metadata={'Creator': 'source-pinned experimental report'})
            artifacts.append({'path': path.name, 'sha256': digest(path), 'bytes': path.stat().st_size,
                              'study': study, 'facet': facet, 'row_ids': sorted(set(used))})
        plt.close(fig)
    metadata = {'schema_version': 1, 'kind': 'experimental_report_figures_v1', 'figures': artifacts,
                'input_manifest_sha256': digest(source/'artifact-manifest.json'), 'metric_table_sha256': digest(source/'per_repetition_metrics.csv'),
                'plotter_sha256': digest(Path(__file__)), 'reused_plotters': reused, 'matplotlib_version': matplotlib.__version__,
                'backend': matplotlib.get_backend(), 'font_family': matplotlib.rcParams['font.family'],
                'freetype_version': matplotlib.ft2font.__freetype_version__,
                'interval': 'observed min/max across repetitions, not confidence intervals',
                'limits': 'Plot values are display floats; exact rational values/raw hashes remain in report tables. No cross-platform figure-byte or benchmark claim.'}
    (output/'manifest.json').write_text(json.dumps(metadata, indent=2)+'\n')
    lines = ['# Static experimental figures', '', 'Observed medians and min/max; exact values and raw links remain in the report tables.', '']
    for artifact in artifacts:
        if artifact['path'].endswith('.png'):
            stem = artifact['path'][:-4]
            lines += ['## '+stem, '', '[PDF]('+stem+'.pdf)', '', '![]('+artifact['path']+')', '']
    (output/'index.md').write_text('\n'.join(lines))
    print('Wrote '+str(len(artifacts))+' standalone PNG/PDF files: '+str(output))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--input', type=Path, required=True); parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    try:
        run(args)
    except Exception as error:
        print('Experimental plots failed: '+str(error), file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
