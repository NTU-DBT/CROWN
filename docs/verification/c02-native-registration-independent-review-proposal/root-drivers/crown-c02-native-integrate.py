#!/usr/bin/env python3
"""Root-only guarded, reversible application of a frozen C02 publication map."""
import csv
import datetime
import hashlib
import json
from pathlib import Path
import re
import shutil
import sys

ROOT = Path('/home/userroot/Codex/CROWN')
PACKAGE = ROOT/'docs/verification/c02-native-registration-proposal'
REVIEW = ROOT/'docs/verification/c02-native-registration-independent-review-proposal'
OUT = ROOT/'build/verification/c02-native-integration-start.json'
BACKUP = ROOT/'build/verification/c02-native-preintegration-backup'
SEAL = ROOT/'docs/verification/statistics-sources.sha256'
SEAL_ID = '95eda9c8b4b6e631a9b85bc0d1c84315c1577aa0dbcb84801d570c9217ce070e'
REFACTOR_ID = 'bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce'


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def label(path):
    return path.relative_to(ROOT).as_posix()


def manifest(path, expected=None, count=None):
    if expected is not None and sha(path) != expected:
        raise RuntimeError('manifest FILE changed: '+str(path))
    pins = {label(path): sha(path)}
    entries = {}
    for line in path.read_text().splitlines():
        match = re.fullmatch(r'([0-9a-f]{64})  (.+)', line)
        if not match or match[2] in entries:
            raise RuntimeError('invalid or duplicate manifest row: '+str(path))
        target = Path(match[2])
        if not target.is_absolute():
            target = ROOT/target
        if sha(target) != match[1]:
            raise RuntimeError('manifest entry changed: '+str(target))
        entries[match[2]] = match[1]
        pins[str(target)] = match[1]
    if count is not None and len(entries) != count:
        raise RuntimeError('manifest entry count: '+str(path))
    return pins, entries


def main():
    if len(sys.argv) != 3:
        raise RuntimeError('expected author and independent review PACKAGE_SHA256SUMS identities')
    if OUT.exists() or BACKUP.exists():
        raise RuntimeError('preserve existing native C02 integration attempt')
    package_pins, _ = manifest(PACKAGE/'PACKAGE_SHA256SUMS', sys.argv[1])
    review_pins, _ = manifest(REVIEW/'PACKAGE_SHA256SUMS', sys.argv[2])
    input_pins, _ = manifest(PACKAGE/'INPUT_SHA256SUMS')
    source_pins, sources = manifest(PACKAGE/'source-files.sha256', count=38)
    preedit_pins, preedits = manifest(PACKAGE/'pre-edit.sha256', count=7)
    accepted = {}
    for name in ['producer-strict-root-attempt-2', 'independent-strict-root-attempt-2',
                 'json-cleanup-root-attempt-2', 'independent-sanitize-root-attempt-1',
                 'producer-sanitize-root-attempt-1']:
        path = ROOT/('build/verification/c02-'+name+'.json')
        value = json.loads(path.read_text())
        if value.get('status') != 'passed' or value.get('source_stable') is not True or value.get('errors'):
            raise RuntimeError('precursor not accepted: '+str(path))
        accepted[label(path)] = sha(path)
    for name in ['statistics-matrix-evidence-audit.json', 'statistics-source-evidence-audit.json']:
        path = ROOT/'build/verification'/name
        if json.loads(path.read_text()).get('accepted') is not True:
            raise RuntimeError('C01 gate not accepted: '+str(path))
        accepted[label(path)] = sha(path)
    command_audit = ROOT/'build/verification/c02-coherent-strict-command-audit.json'
    if json.loads(command_audit.read_text()).get('status') != 'passed':
        raise RuntimeError('coherent command audit not passed')
    accepted[label(command_audit)] = sha(command_audit)
    previous = json.loads((ROOT/'build/verification/statistics-execution-freeze.json').read_text())
    historical = dict(previous['historical_manifest_file_hashes'])
    historical['C01'] = {'path': label(SEAL), 'sha256': SEAL_ID}
    if len(historical) != 11:
        raise RuntimeError('expected eleven preserved historical manifest FILE identities')
    for item in historical.values():
        if sha(ROOT/item['path']) != item['sha256']:
            raise RuntimeError('historical manifest FILE changed')
    if sha(ROOT/'Refactor.md') != REFACTOR_ID:
        raise RuntimeError('original Refactor.md changed')
    mappings = list(csv.DictReader((PACKAGE/'source-map.tsv').read_text().splitlines(), delimiter='\t'))
    plan = []
    destinations = set()
    mapped_sources = set()
    for item in mappings:
        rel = item['native_destination']
        if Path(rel).is_absolute() or '..' in Path(rel).parts or Path(rel).as_posix() != rel:
            raise RuntimeError('noncanonical native destination')
        source = ROOT/item['overlay_file']
        destination = ROOT/rel
        if rel in destinations or item['overlay_file'] in mapped_sources:
            raise RuntimeError('duplicate native source/destination')
        destinations.add(rel)
        mapped_sources.add(item['overlay_file'])
        if not source.resolve().is_relative_to((PACKAGE/'overlay').resolve()):
            raise RuntimeError('source outside frozen overlay')
        if not destination.resolve().is_relative_to(ROOT) or destination.is_symlink():
            raise RuntimeError('unsafe native destination')
        if rel in ['Refactor.md', 'docs/task_ledger.md', 'docs/handoff.md'] or rel.startswith(('docs/verification/', '.git/', '.agents/', '.codex/', '.aws/')):
            raise RuntimeError('forbidden native destination: '+rel)
        if rel.split('/')[0] not in ['include', 'src', 'tests', 'tools', 'schemas', 'docs', 'CMakeLists.txt', 'README.md', 'dependencies.lock.json', 'third_party']:
            raise RuntimeError('unreviewed destination root: '+rel)
        if rel.startswith('third_party/') and not rel.startswith('third_party/nlohmann/'):
            raise RuntimeError('unreviewed vendor destination: '+rel)
        plan.append({'source': label(source), 'destination': rel,
                     'before': sha(destination) if destination.exists() else None,
                     'after': sha(source), 'origin': item['origin'], 'change': item['change']})
    if len(plan) != 38 or mapped_sources != set(sources):
        raise RuntimeError('map does not equal the frozen native source manifest')
    if {label(p) for p in (PACKAGE/'overlay').rglob('*') if p.is_file()} != mapped_sources:
        raise RuntimeError('overlay has unmapped files')
    before_paths = {item['destination'] for item in plan if item['before'] is not None}
    if len(before_paths) != 7 or len(plan)-len(before_paths) != 31 or set(preedits) != before_paths:
        raise RuntimeError('reviewed seven-overwrite/thirty-one-new destination shape changed')
    for item in plan:
        if item['before'] is not None and preedits[item['destination']] != item['before']:
            raise RuntimeError('pre-edit map mismatch')
    # This is the one complete CURRENT 733-entry check, after every other gate
    # and immediately before backing up and applying the reviewed native batch.
    baseline_pins, _ = manifest(SEAL, SEAL_ID, 733)
    BACKUP.mkdir()
    for item in plan:
        if item['before'] is not None:
            saved = BACKUP/item['destination']
            saved.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(ROOT/item['destination'], saved)
            if sha(saved) != item['before']:
                raise RuntimeError('backup changed')
    shutil.copy2(SEAL, BACKUP/'C01-current-source-seal.sha256')
    record = {'card': 'C02', 'phase': 'guarded_native_integration_started',
              'recorded_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
              'registration_manifest_sha256': sys.argv[1], 'independent_review_manifest_sha256': sys.argv[2],
              'accepted_precursor_summaries': accepted, 'baseline_source_entry_count': 733,
              'baseline_entry_pins': baseline_pins, 'historical_manifest_file_hashes': historical,
              'publication_pins': package_pins, 'review_pins': review_pins, 'input_pins': input_pins,
              'source_pins': source_pins, 'preedit_pins': preedit_pins, 'refactor_sha256': REFACTOR_ID, 'mappings': plan,
              'applied': False, 'runner': str(Path(__file__)), 'runner_sha256': sha(Path(__file__))}
    OUT.write_text(json.dumps(record, indent=2)+'\n')
    changed = []
    try:
        for item in plan:
            destination = ROOT/item['destination']
            destination.parent.mkdir(parents=True, exist_ok=True)
            changed.append(item)
            destination.write_bytes((ROOT/item['source']).read_bytes())
            if sha(destination) != item['after']:
                raise RuntimeError('native application mismatch')
        for item in historical.values():
            if sha(ROOT/item['path']) != item['sha256']:
                raise RuntimeError('historical manifest FILE changed during application')
        if sha(ROOT/'Refactor.md') != REFACTOR_ID:
            raise RuntimeError('Refactor changed during application')
    except Exception as error:
        for item in reversed(changed):
            destination = ROOT/item['destination']
            if item['before'] is None:
                destination.unlink(missing_ok=True)
            else:
                destination.write_bytes((BACKUP/item['destination']).read_bytes())
        record['phase'] = 'failed_native_application_restored'
        record['error'] = repr(error)
        OUT.write_text(json.dumps(record, indent=2)+'\n')
        raise
    record['applied'] = True
    record['completed_utc'] = datetime.datetime.now(datetime.timezone.utc).isoformat()
    OUT.write_text(json.dumps(record, indent=2)+'\n')
    old = sum(item['before'] is not None for item in plan)
    print(f'applied {len(plan)} mapped C02 native files; backed up{old}; preserved11 historical seal FILE identities', flush=True)
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
