#!/usr/bin/env python3
"""Replay a tiny genuine report bundle; no native executable is launched."""
import argparse
import csv
from fractions import Fraction
import gzip
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tarfile
import tempfile

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]


def require(condition, message):
    if not condition:
        raise ValueError(message)


def digest(path):
    with path.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def tree_hashes(directory):
    return {str(path.relative_to(directory)): digest(path) for path in directory.rglob('*') if path.is_file()}


def unpack_fixture(fixture, destination):
    if fixture.is_dir():
        shutil.copytree(fixture, destination)
        return
    destination.mkdir()
    with tarfile.open(fixture, 'r:*') as archive:
        members = archive.getmembers()
        require(len(members) <= 20000 and sum(member.size for member in members) <= 256*1024**2, 'fixture archive grant exceeded')
        require(all(not Path(member.name).is_absolute() and '..' not in Path(member.name).parts and
                    (member.isfile() or member.isdir()) for member in members), 'unsafe fixture archive')
        archive.extractall(destination, filter='data')


def corrupt_search_metadata(bundle, kind):
    """Keep the byte envelope consistent while contradicting actual raw output."""
    catalog = json.loads((bundle/'input-catalog.json').read_text())
    index = json.loads((bundle/'evidence-index.json').read_text())
    source = str(Path(catalog['inputs']['search'])/'experiment.json')
    old = index['files'][index['original_paths'][source]]
    packet = json.loads(gzip.decompress((bundle/old['path']).read_bytes()))
    selected = catalog['selection'].get('search')
    row = next(row for row in packet['runs'] if not row['warmup'] and
               (not selected or '|'.join((row['case'], row['method'], str(row['work_limit']))) in selected))
    if kind == 'timing':
        field = next(name for name, value in row['timings'].items() if type(value) is int)
        row['timings'][field] += 1
    else:
        row['retained_candidates'] += 1
    data = json.dumps(packet, sort_keys=True).encode(); key = hashlib.sha256(data).hexdigest()
    payload = gzip.compress(data, compresslevel=6, mtime=0); member = 'evidence/'+key+'.gz'
    (bundle/member).write_bytes(payload)
    index['files'][key] = {'path': member, 'original_bytes': len(data), 'compressed_bytes': len(payload),
                           'compressed_sha256': hashlib.sha256(payload).hexdigest()}
    index['original_paths'][source] = key
    (bundle/'evidence-index.json').write_text(json.dumps(index, sort_keys=True))
    manifest = json.loads((bundle/'artifact-manifest.json').read_text())
    manifest['files'][member] = digest(bundle/member)
    manifest['files']['evidence-index.json'] = digest(bundle/'evidence-index.json')
    (bundle/'artifact-manifest.json').write_text(json.dumps(manifest, sort_keys=True))


def run(args):
    temporary = None
    if args.output:
        directory = args.output.resolve(); directory.mkdir(parents=True, exist_ok=False)
    else:
        temporary = tempfile.TemporaryDirectory(prefix='crown-report-integration-'); directory = Path(temporary.name)
    fixture = directory/'portable fixture with spaces'; unpack_fixture(args.bundle.resolve(), fixture)
    commands = []; builder = ROOT/'tools/build_experimental_report.py'

    def invoke(label, arguments, success=True, env=None):
        child = subprocess.run(list(map(str, arguments)), capture_output=True, text=True, timeout=300,
                               env=dict(os.environ, PYTHONDONTWRITEBYTECODE='1', **(env or {})), cwd=directory)
        (directory/(label+'.stdout')).write_text(child.stdout); (directory/(label+'.stderr')).write_text(child.stderr)
        commands.append({'label': label, 'arguments': list(map(str, arguments)), 'exit_code': child.returncode})
        (directory/'commands.json').write_text(json.dumps(commands, indent=2)+'\n')
        require((child.returncode == 0) is success, label+': '+child.stderr[-3000:])
        if success:
            require(not child.stderr, label+': unexpected successful diagnostic')
        return child

    output = directory/'replayed report'
    invoke('replay-genuine', [sys.executable, builder, '--replay', fixture, '--output', output,
                            '--expected-manifest-sha256', digest(fixture/'artifact-manifest.json')])
    index = json.loads((output/'report-index.json').read_text())
    require(index['status'] == 'complete_report_data' and index['B06_accepted'] is False and
            set(index['scopes']) >= {'b05', 'planning', 'operational', 'matched', 'search'}, 'missing study or overstated acceptance')
    with (output/'per_repetition_metrics.csv').open() as stream:
        rows = list(csv.DictReader(stream))
    require(rows and any(row['availability'] == 'unavailable' for row in rows), 'missing metrics were silently zero-filled')
    expected_metrics = {'b05': 'native_prepare_commit_ns_per_input', 'planning': 'native_prepare_and_epoch_release_ns_per_input',
                        'operational': 'loop_ns_per_input', 'matched': 'loop_ns_per_input', 'search': 'algorithm_ns'}
    checked = []
    for study, metric in expected_metrics.items():
        row = next(row for row in rows if row['study'] == study and row['metric'] == metric and row['availability'] == 'available')
        raw_bytes = gzip.decompress((output/row['raw_path']).read_bytes())
        require(hashlib.sha256(raw_bytes).hexdigest() == row['raw_sha256'], 'per-row raw linkage differs')
        raw = json.loads(raw_bytes)
        if study in ('b05', 'planning'):
            numerator = sum(epoch['native_prepare_commit_ns']+(epoch['epoch_release_ns'] if study == 'planning' else 0) for epoch in raw['epochs'])
            expected = Fraction(numerator, len(raw['epochs']))
        elif study in ('operational', 'matched'):
            owner = next(value for value in raw['passes'] if value['warmup'] is False)
            last = owner['epochs'][-1]; physical = last.get('physical_input_end', last['sequence'])
            expected = Fraction(owner['loop_wall_ns'], physical)
        else:
            expected = Fraction(raw['timings']['algorithm_ns'])
        require(Fraction(int(row['numerator']), int(row['denominator'])) == expected, study+': independently recomputed metric differs')
        checked.append({'study': study, 'metric': metric, 'raw_sha256': row['raw_sha256']})

    original = json.loads((fixture/'evidence-index.json').read_text()); replayed = json.loads((output/'evidence-index.json').read_text())
    for key, entry in replayed['files'].items():
        require(key in original['files'], 'replay introduced an unknown raw evidence payload')
    for study in expected_metrics:
        row = next(row for row in rows if row['study'] == study and row['metric'] == 'process_maxrss_KiB')
        value = int(gzip.decompress((output/row['raw_path']).read_bytes()))
        require(row['json_pointer'] == '' and row['raw_original_path'].endswith('.resources') and
                Fraction(int(row['numerator']), int(row['denominator'])) == value, 'RSS row does not point to its actual GNU-time resource value')
    wall = next(row for row in rows if row['study'] == 'search' and row['metric'] == 'process_wall_ns')
    packet = json.loads(gzip.decompress((output/wall['raw_path']).read_bytes()))
    pointer = wall['json_pointer'].split('/')
    require(pointer[1] == 'runs' and pointer[3] == 'wall_ns' and
            Fraction(int(wall['numerator']), int(wall['denominator'])) == packet['runs'][int(pointer[2])]['wall_ns'], 'outer process wall clock points to the wrong raw source')
    second = directory/'standalone replay'
    invoke('included-standalone-tools', [sys.executable, output/'report-tools/build_experimental_report.py',
                                        '--replay', output, '--output', second])
    for name in ('per_repetition_metrics.csv', 'summary_metrics.csv', 'decisions_and_stops.csv'):
        require((output/name).read_bytes() == (second/name).read_bytes(), 'portable standalone replay changed '+name)
    repeated = json.loads((second/'evidence-index.json').read_text())
    require({key: value['compressed_sha256'] for key, value in replayed['files'].items()} ==
            {key: value['compressed_sha256'] for key, value in repeated['files'].items()}, 'same-runtime gzip serialization is not deterministic')

    changed = directory/'corrupted fixture'; shutil.copytree(fixture, changed)
    member = next(iter(original['files'].values()))['path']; data = bytearray((changed/member).read_bytes()); data[len(data)//2] ^= 1
    (changed/member).write_bytes(data)
    invoke('reject-corruption', [sys.executable, builder, '--replay', changed, '--output', directory/'corrupted-output'], False)
    require(not (directory/'corrupted-output/artifact-manifest.json').exists(), 'corrupted evidence received a complete manifest')
    missing = directory/'missing fixture'; shutil.copytree(fixture, missing); (missing/member).unlink()
    invoke('reject-missing-no-private-fallback', [sys.executable, builder, '--replay', missing, '--output', directory/'missing-output'], False)
    invoke('reject-wrong-published-manifest', [sys.executable, builder, '--replay', fixture, '--output', directory/'wrong-manifest',
                                              '--expected-manifest-sha256', '0'*64], False)
    invoke('reject-finite-grant', [sys.executable, builder, '--replay', fixture, '--output', directory/'tiny-grant', '--max-evidence-bytes', '1'], False)
    for kind in ('timing', 'count'):
        altered = directory/('inconsistent '+kind); shutil.copytree(fixture, altered); corrupt_search_metadata(altered, kind)
        rejection = invoke('reject-metadata-raw-'+kind, [sys.executable, builder, '--replay', altered, '--output', directory/('bad-'+kind)], False)
        require('search metadata/raw timing, count or status differs' in rejection.stderr, 'metadata corruption failed for an unrelated reason')
    before = tree_hashes(output)
    invoke('reject-existing-output', [sys.executable, builder, '--replay', fixture, '--output', output], False)
    require(tree_hashes(output) == before, 'rejected reuse changed prior accepted report')

    plot_status = 'not_requested'
    if args.plots:
        figures = directory/'actual figures'
        env = {'MPLCONFIGDIR': str(directory/'new plot cache')}
        if args.plot_pythonpath:
            env['PYTHONPATH'] = str(args.plot_pythonpath.resolve())+os.pathsep+os.environ.get('PYTHONPATH', '')
        invoke('actual-standard-plots', [sys.executable, output/'report-tools/plot_experimental_report.py', '--input', output, '--output', figures], env=env)
        plotted = json.loads((figures/'manifest.json').read_text()); require(plotted['backend'].lower() == 'agg' and plotted['figures'], 'no actual scientific plots')
        for artifact in plotted['figures']:
            path = figures/artifact['path']; require(digest(path) == artifact['sha256'], 'plot artifact hash differs')
            require(path.read_bytes().startswith(b'\x89PNG\r\n\x1a\n' if path.suffix == '.png' else b'%PDF-'), 'invalid standalone plot format')
        plot_status = 'PASS_'+str(len(plotted['figures']))+'_PNG_PDF_files'
    receipt = {'status': 'PASS_genuine_offline_report_replay', 'independent_metric_checks': checked,
               'portable_members': len(replayed['files']), 'plot_status': plot_status,
               'native_build_timing_invocations': [], 'scope': 'Report arithmetic/byte links/portable replay/negative controls; not a fresh benchmark or B06 acceptance.'}
    (directory/'receiving.json').write_text(json.dumps(receipt, indent=2)+'\n')
    print('Experimental report: all five genuine studies, exact arithmetic, deterministic gzip, standalone relocation and corruption/missing/grant/reuse controls passed; plots='+plot_status)
    if temporary:
        temporary.cleanup()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('bundle', type=Path); parser.add_argument('--output', type=Path)
    parser.add_argument('--plots', action='store_true'); parser.add_argument('--plot-pythonpath', type=Path)
    run(parser.parse_args())


if __name__ == '__main__':
    main()
