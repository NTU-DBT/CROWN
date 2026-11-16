"""Exercise actual captured legacy output and corruption/unsupported-mode controls."""
from pathlib import Path
import base64
import hashlib
import json
import subprocess
import sys
import tempfile

sys.dont_write_bytecode = True
root = Path(sys.argv[1]).resolve()
checker = root / 'tools/check_legacy_replay.py'
fixtures = root / 'tests/legacy_baselines'
replays = root / 'benchmarks/legacy/replay'
captures = json.loads((fixtures / 'captures.json').read_text())
for name, row in captures['captures'].items():
    assert hashlib.sha256((root / name).read_bytes()).hexdigest() == row['sha256'], name
cases = [
    ('scala-l3', 'scala-l3-mixed.txt', 'scala-l3.stdout.jsonl'),
    ('cpp-line5cd', 'line5cd-insert-only.txt', 'line5cd.stdout.txt'),
    ('cpp-line5gc-full', 'line5gc-mixed.txt', 'line5gc-full.stdout.txt'),
    ('cpp-line5gc-replacements', 'line5gc-mixed.txt', 'line5gc-replacements.stdout.txt'),
]


def invoke(base, baseline, trace, stdout, label, success, optimized=False):
    """Run the public checker; failed checks must never publish a pass report."""
    output = base / (label + '.json')
    command = [sys.executable] + (['-O'] if optimized else []) + [str(checker), '--baseline', baseline,
        '--trace', str(trace), '--stdout', str(stdout), '--output', str(output)]
    result = subprocess.run(command, capture_output=True, text=True, timeout=20)
    assert (result.returncode == 0) == success, (label, result.stdout, result.stderr[-1600:])
    assert output.is_file() == success, label
    return json.loads(output.read_text()) if success else None


with tempfile.TemporaryDirectory(prefix='crown-legacy-checker-') as temporary:
    base = Path(temporary)
    reports = [invoke(base, kind, replays / trace, fixtures / stdout, kind, True)
               for kind, trace, stdout in cases]
    assert reports[0]['result']['events'] == 22 and reports[0]['result']['signed_records'] == 18
    assert [r['distinct'] for r in reports[1]['result']['milestones']] == [0, 0, 0, 0, 0, 1, 1, 1, 1, 2]
    assert reports[2]['result']['output_records'] == 22
    assert reports[3]['result']['output_records'] == 24 and reports[3]['result']['zero_replacements'] == 8
    assert all(not r['baseline_launched'] and not r['timing_eligible'] for r in reports)

    raw = (fixtures / 'scala-l3.stdout.jsonl').read_text().splitlines()
    event = json.loads(raw[2])
    decoded = base64.b64decode(event['delta_base64']).decode()
    scala_faults = {
        'missing-delta': dict(event, delta_base64=''),
        'duplicate-delta': dict(event, delta_base64=base64.b64encode((decoded + decoded).encode()).decode()),
        'wrong-sign': dict(event, delta_base64=base64.b64encode(decoded.replace('+', '-', 1).encode()).decode()),
        'missing-snapshot': dict(event, rows=[]),
        'duplicate-snapshot': dict(event, rows=event['rows'] * 2),
        'boolean-snapshot': dict(event, rows=[[True, 2, 3, 4]]),
        'wrong-sequence': dict(event, event=4),
        'bad-base64': dict(event, delta_base64='!'),
    }
    for label, changed in scala_faults.items():
        path = base / (label + '.stdout')
        path.write_text('\n'.join(raw[:2] + [json.dumps(changed)] + raw[3:]) + '\n')
        invoke(base, 'scala-l3', replays / 'scala-l3-mixed.txt', path, label, False,
               optimized=label in ('missing-delta', 'duplicate-snapshot'))

    for kind, trace, stdout in cases:
        empty = base / (kind + '-empty.stdout'); empty.write_text('')
        invoke(base, kind, replays / trace, empty, kind + '-empty', False)
    changed = base / 'wrong-count.stdout'
    changed.write_text((fixtures / 'line5cd.stdout.txt').read_text().replace('2.0000', '3.0000'))
    invoke(base, 'cpp-line5cd', replays / 'line5cd-insert-only.txt', changed, 'wrong-count', False, optimized=True)
    changed.write_text((fixtures / 'line5gc-replacements.stdout.txt').read_text().replace(' -> 0.0000', ' -> 1.0000'))
    invoke(base, 'cpp-line5gc-replacements', replays / 'line5gc-mixed.txt', changed, 'lost-removals', False)
    changed.write_text((fixtures / 'line5gc-full.stdout.txt').read_text() + 'unexpected output\n')
    invoke(base, 'cpp-line5gc-full', replays / 'line5gc-mixed.txt', changed, 'extra-output', False)
    for label, kind, trace, stdout, suffix in [
        ('unsupported-delete', 'cpp-line5cd', 'line5cd-insert-only.txt', 'line5cd.stdout.txt', '-|1|2\n'),
        ('duplicate-edge', 'cpp-line5cd', 'line5cd-insert-only.txt', 'line5cd.stdout.txt', '+|1|2\n'),
        ('absent-delete', 'cpp-line5gc-full', 'line5gc-mixed.txt', 'line5gc-full.stdout.txt', '-|999|998\n'),
        ('duplicate-scala-row', 'scala-l3', 'scala-l3-mixed.txt', 'scala-l3.stdout.jsonl', '+,G2,-2,-3\n'),
    ]:
        original = (replays / trace).read_text()
        # Preserve the event count so this control reaches duplicate admission.
        if label == 'duplicate-scala-row': original = '\n'.join(original.splitlines()[:-1]) + '\n'
        bad = base / (label + '.trace'); bad.write_text(original + suffix)
        invoke(base, kind, bad, fixtures / stdout, label, False)
    for kind, trace, stdout in cases[1:]:
        tail = base / (kind + '-unobserved.trace')
        tail.write_text((replays / trace).read_text() + '+|99|100\n')
        invoke(base, kind, tail, fixtures / stdout, kind + '-unobserved', False)
    spelling = base / 'scala-underscore.trace'
    # Python int('0_1') is 1, so join results alone cannot expose this parser gap.
    spelling.write_text((replays / 'scala-l3-mixed.txt').read_text().replace('+,G1,1,2', '+,G1,0_1,2', 1))
    invoke(base, 'scala-l3', spelling, fixtures / 'scala-l3.stdout.jsonl', 'scala-underscore', False)
    existing = base / 'scala-l3.json'
    before = existing.read_bytes()
    result = subprocess.run([sys.executable, str(checker), '--baseline', 'scala-l3', '--trace', str(replays / 'scala-l3-mixed.txt'),
                             '--stdout', str(fixtures / 'scala-l3.stdout.jsonl'), '--output', str(existing)],
                            capture_output=True, text=True, timeout=20)
    assert result.returncode != 0 and existing.read_bytes() == before
print('Legacy replay checker: 4 actual-capture passes; 24 corruption/unsupported-operation/overwrite controls; optimized guards retained')
