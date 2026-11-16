#!/usr/bin/env python3
"""Assemble an inspectable release candidate; packaging does not grant acceptance."""
from pathlib import Path
import argparse
import gzip
import hashlib
import json
import re
import shutil
import subprocess
import sys
import tarfile

SOURCE_ROOT_FILES = ('.gitignore', 'CMakeLists.txt', 'CMakePresets.json',
                     'dependencies.lock.json', 'README.md', 'Refactor.md')
SOURCE_DIRECTORIES = ('include', 'src', 'apps', 'tools', 'examples', 'cmake',
                      'tests', 'schemas', 'benchmarks', 'third_party', 'docs')
IGNORED = {'__pycache__', '.git', '.aws', '.codex'}


def require(value, message):
    if not value:
        raise ValueError(message)


def sha(path):
    digest = hashlib.sha256()
    with path.open('rb') as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b''):
            digest.update(chunk)
    return digest.hexdigest()


def positive(value):
    number = int(value)
    require(number > 0, 'grant must be positive')
    return number


def regular_files(directory):
    """Use regular local files only; do not follow source/evidence symlinks."""
    require(directory.is_dir(), f'missing input directory: {directory}')
    result = []
    for path in sorted(directory.rglob('*')):
        relative = path.relative_to(directory)
        if any(part in IGNORED for part in relative.parts) or path.suffix == '.pyc':
            continue
        require(not path.is_symlink(), f'symlink input: {path}')
        if path.is_file():
            result.append(path)
    require(result, f'empty input directory: {directory}')
    return result


def arguments():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('source', 'build-dir', 'report', 'figures', 'evidence', 'output'):
        parser.add_argument('--' + name, type=Path, required=True)
    parser.add_argument('--profile', choices=('R1', 'R2'), default='R1')
    parser.add_argument('--max-total-bytes', type=positive, default=2 * 1024**3)
    parser.add_argument('--max-files', type=positive, default=50000)
    return parser.parse_args()


def main():
    args = arguments()
    source, build = args.source.resolve(), args.build_dir.resolve()
    output = args.output.resolve()
    require(not output.exists(), f'output already exists: {output}')
    require(output.parent.is_dir(), 'output parent must exist')
    require(not output.is_relative_to(source / 'docs') and
            not any(output.is_relative_to(source / name) for name in SOURCE_DIRECTORIES),
            'output must be outside maintained source directories')
    roles = {name: (getattr(args, name).resolve(), regular_files(getattr(args, name).resolve()))
             for name in ('report', 'figures', 'evidence')}
    require(all(not output.is_relative_to(directory) for directory, _ in roles.values()),
            'output must be outside its evidence inputs')
    if args.profile == 'R2':
        for name in ('docs/releases/r2.md', 'docs/r2_compatibility.md', 'docs/r2_migration.md',
                     'docs/sql_rows_session.md', 'docs/sql_aggregate_session.md'):
            require((source / name).is_file(), 'missing R2 guide: ' + name)
        require((roles['report'][0] / 'r2-report.md').is_file(), 'missing R2 report entry: r2-report.md')
    version_text = (source / 'include/crown/version.hpp').read_text()
    version_match = re.search(r'version\s*=\s*"([0-9]+\.[0-9]+\.[0-9]+)"', version_text)
    api_match = re.search(r'public_api_version\s*=\s*([0-9]+)', version_text)
    require(version_match and api_match, 'public version/API declarations missing')
    version, api = version_match[1], int(api_match[1])
    require(re.search(r'project\(crown_next\s+VERSION\s+' + re.escape(version) + r'\s',
                      (source / 'CMakeLists.txt').read_text()), 'CMake/public versions differ')
    cache = {}
    for line in (build / 'CMakeCache.txt').read_text().splitlines():
        if ':' in line and '=' in line and not line.startswith(('#', '//')):
            key, value = line.split('=', 1)
            cache[key.split(':', 1)[0]] = value
    require(cache.get('CMAKE_HOME_DIRECTORY') and
            Path(cache['CMAKE_HOME_DIRECTORY']).resolve() == source,
            'build belongs to another source directory')
    source_files = {source / name for name in SOURCE_ROOT_FILES}
    for name in SOURCE_DIRECTORIES:
        source_files.update(regular_files(source / name))
    legacy = json.loads((source / 'benchmarks/legacy/manifest.json').read_text())
    for name, expected in legacy['source_sha256_local'].items():
        relative = Path(name)
        require(not relative.is_absolute() and '..' not in relative.parts, 'invalid baseline source path')
        path = source / relative
        require(path.is_file() and not path.is_symlink() and sha(path) == expected,
                f'baseline source pin differs: {name}')
        source_files.add(path)
    source_files.update(source.glob('*.pdf'))
    require(all(path.is_file() and not path.is_symlink() for path in source_files),
            'source inventory contains a missing or symlink file')
    known_inputs = [*source_files, *(path for _, paths in roles.values() for path in paths)]
    require(len(known_inputs) + 1 <= args.max_files, 'file grant exceeded')
    require(sum(path.stat().st_size for path in known_inputs) <= args.max_total_bytes,
            'payload byte grant exceeded')

    output.mkdir()
    name = f'crown-next-{version}-{args.profile.lower()}'
    stage = output / name
    stage.mkdir()
    commands = []

    def run(command):
        index = len(commands)
        with (output / f'{index}.stdout').open('xb') as stdout, (output / f'{index}.stderr').open('xb') as stderr:
            result = subprocess.run([str(item) for item in command], stdout=stdout, stderr=stderr)
        commands.append({'arguments': [str(item) for item in command], 'exit_code': result.returncode,
                         'stdout': f'{index}.stdout', 'stderr': f'{index}.stderr'})
        (output / 'commands.json').write_text(json.dumps(commands, indent=2) + '\n')
        require(result.returncode == 0, f'command failed; see {index}.stderr')

    run(['cmake', '--install', build, '--prefix', stage / 'sdk'])
    run([stage / 'sdk/bin/crown', '--version'])
    expected_version = f'CROWN Next {version} (C++23; exact set semantics; native API {api})\n'
    require((output / '1.stdout').read_text() == expected_version, 'installed CLI version/API differs')
    payload = []
    originals = []
    total_bytes = 0

    def record(path):
        nonlocal total_bytes
        size = path.stat().st_size
        require(len(payload) < args.max_files, 'file grant exceeded')
        require(size <= args.max_total_bytes - total_bytes, 'payload byte grant exceeded')
        total_bytes += size
        payload.append({'path': str(path.relative_to(stage)), 'bytes': size, 'sha256': sha(path)})

    def copy(original, relative):
        before = sha(original)
        require(len(payload) < args.max_files, 'file grant exceeded')
        require(original.stat().st_size <= args.max_total_bytes - total_bytes, 'payload byte grant exceeded')
        target = stage / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(original, target)
        target.chmod(0o755 if original.stat().st_mode & 0o111 else 0o644)
        require(sha(target) == before == sha(original), f'input changed during copy: {original}')
        originals.append((original, before))
        record(target)

    for path in regular_files(stage / 'sdk'):
        record(path)
    require(not list((stage / 'sdk').rglob('*testing*.a')) and
            not list((stage / 'sdk').rglob('libcrown_reference.a')), 'private test ABI installed')
    for path in sorted(source_files):
        copy(path, Path('source') / path.relative_to(source))
    for role, (directory, paths) in roles.items():
        for path in paths:
            copy(path, Path(role) / path.relative_to(directory))
    profile_scope = ('R1 covers the documented free-connex equality set fragment. Other installed\n'
                     'libraries and opt-in interfaces retain their separate acceptance boundaries.')
    guide_links = ('[R1 methods and scope](source/docs/releases/r1.md)\n'
                   'and [CLI](source/docs/cli.md)')
    report_entry = 'report/report.md'
    if args.profile == 'R2':
        profile_scope = ('R2 covers the admitted exact SQL bag and COUNT/SUM/AVG workflows, with their\n'
                         'declared NULL, numeric, batch and bounded local recovery contracts. Use the\n'
                         'public CROWN::sql_rows_recovery and CROWN::sql_aggregate_recovery SDK targets.\n'
                         'The installed CLI retains its exact-set identity and defaults. Other SQL and\n'
                         'separately gated extensions retain their own admission and evidence boundaries.')
        guide_links = ('[R2 methods and scope](source/docs/releases/r2.md),\n'
                       '[compatibility](source/docs/r2_compatibility.md), [migration](source/docs/r2_migration.md),\n'
                       '[durable SQL rows](source/docs/sql_rows_session.md),\n'
                       '[durable SQL aggregates](source/docs/sql_aggregate_session.md)\n'
                       'and [CLI](source/docs/cli.md)')
        report_entry = 'report/r2-report.md'
    readme = stage / 'README.md'
    readme.write_text(f'''# CROWN Next {version}: {args.profile} candidate

This archive is unqualified until its source, validation and advertised scope
receive a separate release decision. Packaging files does not prove their claims.
{profile_scope}

Use `sdk/bin/crown --help`. For a public C++ consumer, set `CMAKE_PREFIX_PATH`
to the relocated `sdk` directory and use `find_package(Crown {version} CONFIG REQUIRED)`.
Read [quickstart](source/docs/quickstart.md), {guide_links}. Build a new source tree with:

    cmake -S source -B new-build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF
    cmake --build new-build --parallel 2

[Report]({report_entry}), [figures](figures/index.md) and `evidence/` retain
their explicit qualification. Historical build-evidence links in exact source
documents refer to the original repository lineage; they are not a fallback
path for the portable report. Source and SDK are separate roots. Native binary
compatibility depends on the recorded compiler/OS/runtime ABI; this archive does
not bundle system libraries. Existing rights and dependency notices are retained.
''')
    record(readme)
    require(all(sha(path) == expected for path, expected in originals), 'input closure changed')
    payload.sort(key=lambda row: row['path'])
    manifest = {
        'schema_version': 1, 'kind': 'crown_release_candidate_v1', 'profile': args.profile,
        'version': version, 'public_api_version': api, 'status': 'candidate_unqualified',
        'release_accepted': False,
        'build': {'configuration': cache.get('CMAKE_BUILD_TYPE', ''),
                  'sanitizers': cache.get('CROWN_SANITIZERS', 'OFF'),
                  'compiler': cache.get('CMAKE_CXX_COMPILER', '')},
        'files': payload,
        'limits': {'files': args.max_files, 'total_bytes': args.max_total_bytes},
        'payload_files': len(payload), 'payload_bytes': total_bytes,
        'scope': {'evidence': 'Explicit unqualified input directories; byte presence is not lineage or acceptance.',
                  'grants': 'Regular payload bytes/files only; installer staging, metadata, archive and process resources are separate.',
                  'runtime': 'No changes to query execution, semantics, defaults or query memory accounts.',
                  'source': 'Complete maintained tree plus exact baseline-manifest source pins; root build/VCS/account directories excluded.'},
    }
    (stage / 'release-manifest.json').write_text(json.dumps(manifest, sort_keys=True, indent=2) + '\n')
    checksums = [(row['path'], row['sha256']) for row in payload]
    checksums.append(('release-manifest.json', sha(stage / 'release-manifest.json')))
    (stage / 'CHECKSUMS.sha256').write_text(''.join(f'{digest}  {path}\n' for path, digest in sorted(checksums)))
    archive = output / (name + '.tar.gz')
    with archive.open('xb') as raw:
        with gzip.GzipFile(filename='', fileobj=raw, mode='wb', mtime=0, compresslevel=6) as compressed:
            with tarfile.open(fileobj=compressed, mode='w|', format=tarfile.USTAR_FORMAT) as tar:
                for path in regular_files(stage):
                    info = tarfile.TarInfo(name + '/' + str(path.relative_to(stage)))
                    info.size = path.stat().st_size
                    info.mode = 0o755 if path.stat().st_mode & 0o111 else 0o644
                    with path.open('rb') as stream:
                        tar.addfile(info, stream)
    result = {'status': 'candidate_unqualified', 'archive': archive.name,
              'archive_sha256': sha(archive), 'archive_bytes': archive.stat().st_size,
              'payload_files': len(payload), 'payload_bytes': total_bytes,
              'release_manifest_sha256': sha(stage / 'release-manifest.json')}
    (output / 'candidate.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result))


if __name__ == '__main__':
    try:
        main()
    except (ValueError, OSError, subprocess.SubprocessError) as error:
        print(str(error), file=sys.stderr)
        raise SystemExit(1)
