"""Check the real clean-source closure without a full release build."""
import argparse
import hashlib
import importlib.util
import io
import json
from pathlib import Path
import subprocess
import sys
import tempfile

sys.dont_write_bytecode = True
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('source', type=Path)
parser.add_argument('--install-inputs-only', action='store_true')
arguments = parser.parse_args()
root = arguments.source.resolve()
spec = importlib.util.spec_from_file_location('clean_source', root / 'tools/verify_clean_build.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)

# These are the current explicit documentation inputs to CrownInstall.cmake.
INSTALL_INPUTS = ('docs/cli.md', 'docs/sql_aggregate_input.md')
CURRENT_PLAN = 'Refactor.md'
HISTORICAL_PLAN = 'benchmarks/legacy/basis/Refactor-v52.md'


def require_install_inputs(source):
    """Reject a snapshot missing a current required install document."""
    for name in INSTALL_INPUTS:
        assert (source / name).is_file(), name


def check_install_fixture():
    """Exercise the actual copier and missing-input guard without native work."""
    with tempfile.TemporaryDirectory(prefix='crown-install-inputs-') as temporary:
        base = Path(temporary)
        repository = base / 'repository'; repository.mkdir()
        snapshot = base / 'snapshot'; snapshot.mkdir()
        for directory in module.SOURCE_DIRECTORIES:
            (repository / directory).mkdir(parents=True, exist_ok=True)
        for name in (*module.SOURCE_FILES, *INSTALL_INPUTS, CURRENT_PLAN, HISTORICAL_PLAN):
            path = repository / name; path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text('synthetic input: ' + name + '\n')
        legacy = {HISTORICAL_PLAN: hashlib.sha256((repository / HISTORICAL_PLAN).read_bytes()).hexdigest()}
        (repository / 'benchmarks/legacy/manifest.json').write_text(json.dumps({'source_sha256_local': legacy}) + '\n')
        module.copy_snapshot(repository, snapshot, io.StringIO())
        require_install_inputs(snapshot)
        # Current requirements are explicit; historical evidence retains its exact pin.
        for name in (*INSTALL_INPUTS, CURRENT_PLAN, HISTORICAL_PLAN):
            assert (snapshot / name).read_bytes() == (repository / name).read_bytes(), name
        (snapshot / 'docs/sql_aggregate_input.md').unlink()
        try:
            require_install_inputs(snapshot)
        except AssertionError as error:
            assert str(error) == 'docs/sql_aggregate_input.md'
        else:
            raise AssertionError('missing install document was accepted')


check_install_fixture()
if arguments.install_inputs_only:
    print('Clean-source inputs: both install docs and current/historical plans preserved; missing aggregate doc rejected; no native commands')
    raise SystemExit(0)

with tempfile.TemporaryDirectory(prefix='crown-snapshot-preflight-') as temporary:
    source = Path(temporary) / 'source'; source.mkdir()
    module.copy_snapshot(root, source, io.StringIO())
    assert not (source / 'build').exists() and not (source / '.git').exists()
    for required in ('examples/reoptimization/main.cpp', 'examples/workload-measurement/main.cpp',
                     *INSTALL_INPUTS, 'benchmarks/legacy/manifest.json', 'docs/source_baselines.md', 'Refactor.md',
                     'README.md', '.gitignore', 'docs/experimental_report.md', 'docs/releases/r1.md'):
        assert (source / required).is_file(), required
    manifest = json.loads((source / 'benchmarks/legacy/manifest.json').read_text())
    assert all((source / name).read_bytes() == (root / name).read_bytes() for name in manifest['source_sha256_local'])
    commands = [
        ['cmake', '-S', str(source), '-B', str(source / 'build'), '-DBUILD_TESTING=ON'],
        [sys.executable, str(source / 'tools/verify_workloads.py'), '--source', str(source), '--static-only'],
        [sys.executable, str(source / 'tools/generate_ranking_evaluation.py'), '--check', str(source / 'benchmarks/ranking')],
        [sys.executable, str(source / 'tools/verify_imported_workloads.py'), '--source', str(source)],
    ]
    for command in commands:
        result = subprocess.run(command, capture_output=True, text=True, timeout=90)
        assert result.returncode == 0, (command, result.stdout[-2000:], result.stderr[-2000:])
print('Clean-source closure: real configure, examples/install inputs, 122 pinned baseline files, workload/import/ranking manifests')
