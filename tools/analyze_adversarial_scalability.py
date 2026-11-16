#!/usr/bin/env python3
"""Trace B05 tables to B03 raw records; keep timings, bytes, slots and work apart.

Checks relevant receipt/result/storage invariants, not every JSON-schema field.
Reported repetition ranges are empirical min/max, never confidence intervals.
"""
from __future__ import annotations

import argparse
import collections
import csv
import hashlib
import json
from pathlib import Path
import statistics

METRICS = ('support.native_record_visits', 'support.reverse_index_records_visited',
           'support.child_key_probes', 'physical.constraint_rows', 'physical.aliases_visited',
           'physical.native_crossings', 'delta.work', 'delta.replay_results_work', 'delta.replay_preparation_work')


def require(value, message):
    if not value:
        raise ValueError(message)


def digest(path):
    with path.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def read(path):
    return json.loads(path.read_text())


def checked(path, expected, pins):
    """Read a pinned JSON record once and retain its exact provenance."""
    require(digest(path) == expected, 'input fingerprint mismatch: ' + str(path))
    pins[str(path)] = expected
    return read(path)


def extent(values):
    """Summarize repeated observations without a probabilistic interpretation."""
    return {'minimum': min(values), 'median': statistics.median(values), 'maximum': max(values)}


def write_csv(path, rows):
    with path.open('x', newline='') as stream:
        if rows:
            writer = csv.DictWriter(stream, fieldnames=list(rows[0]))
            writer.writeheader()
            writer.writerows(rows)


def analyze(packet, output):
    """Reconcile completed case packets and write fresh derived artifacts."""
    root = read(packet / 'experiment.json')
    require(root['kind'] == 'b05_parameterized_native_stress' and root['status'] == 'complete', 'B05 batch is incomplete')
    expected = {(f, s) for f in root['configuration']['families'] for s in root['configuration']['scales']}
    require({(r['family'], r['scale']) for r in root['cases']} == expected and len(root['cases']) == len(expected), 'parameter coverage mismatch')
    pins = {str(packet / 'experiment.json'): digest(packet / 'experiment.json')}
    rows, phases, counters, probes, availability = [], [], [], [], []
    for case in root['cases']:
        require(case['exit_code'] == 0, 'failed B05 child')
        directory = packet / case['directory']
        require(digest(directory / 'child.log') == case['log_sha256'], 'child log changed')
        manifest = checked(directory / 'workload/manifest.json', case['pack_manifest_sha256'], pins)
        axes = checked(directory / 'workload/axes.json', case['axes_sha256'], pins)['cases'][0]
        native_dir = directory / 'native'
        native = checked(native_dir / 'experiment.json', case['native_experiment_sha256'], pins)
        require(native['status'] == 'complete' and native['correctness_gate'] == 'passed_all_configurations_before_warmup_or_measurement', 'missing native correctness gate')
        commands = checked(native_dir / 'commands.json', native['commands_sha256'], pins)
        workload = manifest['workloads'][0]
        oracle = checked(directory / 'workload' / workload['oracle']['path'], workload['oracle']['sha256'], pins)
        require(len(oracle['epochs']) == len(axes['live_source_rows']) == axes['events'], 'oracle/live horizon mismatch')
        require(native['configuration']['repetitions'] == root['configuration']['repetitions'], 'repetition configuration changed')
        wanted_labels = {axes['case_id'] + '/' + b + '/' + m for b in root['configuration']['backends'] for m in root['configuration']['modes']}
        require({v['label'] for v in native['verification']} == wanted_labels, 'backend/mode coverage mismatch')
        require(len(native['runs']) == len(wanted_labels) * (native['configuration']['repetitions'] + native['configuration']['warmups']), 'missing retained run')
        require(max(v['command'] for v in native['verification']) < min(r['command'] for r in native['runs']), 'measurement preceded preflight')
        for entry in native['runs']:
            raw = native_dir / entry['raw_report']
            report = checked(raw, entry['raw_report_sha256'], pins)
            command = commands[entry['command']]
            require(command['exit_code'] == 0 and not command['timed_out'] and command['stdout_sha256'] == entry['raw_report_sha256'], 'raw command linkage failed')
            require(command.get('resource_usage_sha256') is not None, 'older inherited-wait4 RSS is not eligible for B05 memory curves')
            resources = native_dir / command['resource_usage']
            require(digest(resources) == command['resource_usage_sha256'], 'target resource record changed')
            pins[str(resources)] = command['resource_usage_sha256']
            require(int(resources.read_text()) == command['process_maxrss_KiB'] == entry['process_maxrss_KiB'], 'target RSS linkage differs')
            require(report['schema_version'] == 2 and report['kind'] == 'native_workload_measurement', 'expected arena-aware raw record v2')
            require(report['binding_sha256'] == entry['collector_binding_sha256'], 'raw binding differs')
            require(entry['label'] in wanted_labels and report['request']['label'] == entry['label'], 'raw label differs')
            _, backend, mode = entry['label'].rsplit('/', 2)
            require((report['backend'], report['output_mode']) == (backend, mode), 'raw backend/mode differs')
            epochs = report['epochs']
            require(len(epochs) == report['records'] == axes['events'], 'raw event horizon differs')
            for event, desired, live in zip(epochs, oracle['epochs'], axes['live_source_rows'], strict=True):
                require(event['sequence'] == desired['sequence'] and event['phase'] == desired['phase'], 'epoch/oracle identity differs')
                count = len(desired['signed_delta']) if report['output_mode'] == 'delta' else len(desired['current_rows']) if report['output_mode'] == 'snapshot' else 0
                require(event['output_rows'] == count, 'measured output demand differs')
                require(sum(c['returned_row'] for c in event['output_calls']) == count, 'returned-row census differs')
                require(len(event['output_calls']) == (count + 1 if report['output_mode'] != 'maintenance' else 0), 'termination-call census differs')
                require(event['storage']['source']['live_records'] == live, 'native source live population differs')
                for arena in ('source', 'support'):
                    state = event['storage'][arena]
                    require(all(type(v) is int and v >= 0 for v in state.values()), 'invalid arena count')
                    require(state['slots'] == sum(state[k] for k in ('live_records', 'retained_records', 'free_slots', 'exhausted_slots')), 'arena slot partition differs')
            require(sum(e['output_rows'] for e in epochs) == report['output_rows'] == report['sink']['calls'], 'total output/sink demand differs')
            if entry['warmup']:
                continue
            common = {'family': case['family'], 'scale': case['scale'], 'axis': axes['axis'],
                'axis_value': axes['axis_value'], 'backend': report['backend'], 'mode': report['output_mode'],
                'repetition': entry['repetition']}
            count = len(epochs)
            total = lambda name: sum(e[name] for e in epochs)
            visits = [e['operator_metrics']['support.native_record_visits'] for e in epochs]
            valid_visits = all(v['availability'] == 'available' and not v['saturated'] for v in visits)
            plan = checked(native_dir / (case['family'] + '-' + report['backend'] + '.compiled.json'), report['artifact_sha256'], pins)
            row = dict(common, events=count, changed_events=sum(e['physical_changed'] for e in oracle['epochs']),
                output_rows=report['output_rows'], maximum_result_rows=axes['maximum_result_rows'],
                arity=axes.get('arity'), atoms=axes.get('atoms'),
                checked_native_height=plan['height_certificate']['minimum_height'],
                native_ns_total=total('native_prepare_commit_ns'), native_ns_per_event=total('native_prepare_commit_ns') / count,
                active_ns_total=total('event_active_ns'), active_ns_per_event=total('event_active_ns') / count,
                output_next_ns_total=total('output_next_ns'),
                output_next_ns_per_output=total('output_next_ns') / report['output_rows'] if report['output_rows'] else None,
                encoding_ns_total=total('encoding_ns'), sink_ns_total=total('sink_write_wait_ns'), diagnostics_ns_total=total('diagnostics_ns'),
                query_current_max=max(e['memory']['current_requested_bytes'] for e in epochs),
                query_payload_max=max(e['memory']['current_payload_bytes'] for e in epochs),
                query_current_final=report['memory_final']['current_requested_bytes'],
                query_peak_requested=report['memory_final']['peak_requested_bytes'],
                process_maxrss_KiB=entry['process_maxrss_KiB'],
                source_slots_max=max(e['storage']['source']['slots'] for e in epochs),
                support_slots_max=max(e['storage']['support']['slots'] for e in epochs),
                support_native_visits_per_event=sum(v['value'] for v in visits) / count if valid_visits else None,
                raw_report=str(raw), raw_sha256=entry['raw_report_sha256'])
            rows.append(row)
            by_phase = collections.defaultdict(list)
            completed_cycles = 0
            for event in epochs:
                by_phase[event['phase']].append(event)
                completed_cycles += event['phase'] == 'churn_delete'
                if event['phase'] in ('sentinel_probe', 'empty_probe'):
                    probes.append(dict(common, sequence=event['sequence'], phase=event['phase'], completed_cycles=completed_cycles,
                        source_live_rows=event['storage']['source']['live_records'],
                        source_slots=event['storage']['source']['slots'], support_slots=event['storage']['support']['slots'],
                        query_current_requested_bytes=event['memory']['current_requested_bytes'],
                        cursor_work=sum(event['cursor_work'].values()), output_next_ns=event['output_next_ns'],
                        event_active_ns=event['event_active_ns'], raw_report=str(raw), raw_sha256=entry['raw_report_sha256']))
            for phase, values in by_phase.items():
                phases.append(dict(common, phase=phase, events=len(values),
                    native_ns_total=sum(e['native_prepare_commit_ns'] for e in values),
                    native_ns_max=max(e['native_prepare_commit_ns'] for e in values),
                    active_ns_total=sum(e['event_active_ns'] for e in values),
                    output_rows=sum(e['output_rows'] for e in values),
                    cursor_work=sum(sum(e['cursor_work'].values()) for e in values),
                    query_current_min=min(e['memory']['current_requested_bytes'] for e in values),
                    query_current_max=max(e['memory']['current_requested_bytes'] for e in values)))
                for name in METRICS:
                    cells = [e['operator_metrics'][name] for e in values if name in e['operator_metrics']]
                    available = [c['value'] for c in cells if c['availability'] == 'available' and not c['saturated']]
                    counters.append(dict(common, phase=phase, metric=name, unit=cells[0]['unit'] if cells else None,
                        available_samples=len(available), unavailable_samples=len(values) - len(available),
                        saturated_samples=sum(c['saturated'] for c in cells),
                        sum_available_values=sum(available), minimum=min(available) if available else None,
                        maximum=max(available) if available else None,
                        includes=cells[0]['includes'] if cells else None))
            for name in epochs[0]['operator_metrics']:
                cells = [e['operator_metrics'][name] for e in epochs]
                availability.append(dict(common, metric=name,
                    available=sum(c['availability'] == 'available' for c in cells),
                    disabled=sum(c['availability'] == 'disabled' for c in cells),
                    unavailable=sum(c['availability'] == 'unavailable' for c in cells),
                    saturated=sum(c['saturated'] for c in cells)))
    output.mkdir(parents=True, exist_ok=False)
    for name, values in [('rows', rows), ('phases', phases), ('counters', counters), ('probes', probes), ('availability', availability)]:
        write_csv(output / (name + '.csv'), values)
    grouped = collections.defaultdict(list)
    for row in rows:
        grouped[(row['family'], row['axis_value'], row['backend'], row['mode'])].append(row)
    groups = []
    for (family, axis_value, backend, mode), values in sorted(grouped.items()):
        groups.append(dict(family=family, axis_value=axis_value, backend=backend, mode=mode, repetitions=len(values),
            native_ns_per_event=extent([v['native_ns_per_event'] for v in values]),
            query_current_max=extent([v['query_current_max'] for v in values]),
            source_slots_max=extent([v['source_slots_max'] for v in values]),
            output_rows=extent([v['output_rows'] for v in values])))
    summary = {'status': 'raw_refs_and_result_storage_counts_checked', 'groups': groups,
        'measured_runs': len(rows), 'parameter_points': len(root['cases']), 'raw_input_pins': pins,
        'scope': 'Per-run means include charged loading; output and diagnostics remain separate. Counter layers overlap and are never summed into a synthetic total. Arena slots are populations, not visits. RSS includes caller records/report buffers. Repetition ranges are observed min/max, not confidence intervals.',
        'acceptance': 'Root must examine and explain actual trends; completing or hashing a packet does not accept B05.'}
    (output / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    lines = ['# B05 measured points', '', summary['scope'], '', summary['acceptance'], '',
        '| Family | Size | Backend | Mode | Runs | Native ns/event median [min,max] | Max query bytes median | Source slots median |',
        '| --- | ---: | --- | --- | ---: | ---: | ---: | ---: |']
    for group in groups:
        t = group['native_ns_per_event']
        lines.append(f'| {group["family"]} | {group["axis_value"]} | {group["backend"]} | {group["mode"]} | {group["repetitions"]} | {t["median"]:.1f} [{t["minimum"]:.1f},{t["maximum"]:.1f}] | {group["query_current_max"]["median"]:g} | {group["source_slots_max"]["median"]:g} |')
    (output / 'report.md').write_text('\n'.join(lines) + '\n')
    artifacts = {p.name: digest(p) for p in output.iterdir() if p.is_file()}
    (output / 'artifact-manifest.json').write_text(json.dumps({'files': artifacts,
        'analyzer_sha256': digest(Path(__file__)), 'input_experiment_sha256': digest(packet / 'experiment.json')}, indent=2) + '\n')
    return dict(measured_runs=len(rows), parameter_points=len(root['cases']), derived_groups=len(groups))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--packet', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    print(analyze(args.packet.resolve(), args.output.resolve()))


if __name__ == '__main__':
    main()
