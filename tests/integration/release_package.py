#!/usr/bin/env python3
"""Verify an extracted candidate archive and its relocated public SQL consumer."""
import argparse
from contextlib import nullcontext
import hashlib
import json
import re
from pathlib import Path, PurePosixPath
import shutil
import sqlite3
import subprocess
import sys
import tarfile
import tempfile

sys.dont_write_bytecode = True


def archive_root(profile):
    return 'crown-next-0.1.0-' + profile.lower()


def require(value, message):
    if not value:
        raise RuntimeError(message)


def digest(path):
    result = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            result.update(block)
    return result.hexdigest()


def canonical(value):
    return json.dumps(value, sort_keys=True, ensure_ascii=False, separators=(',', ':'))


class Runner:
    def __init__(self, base):
        self.base, self.records = base, []

    def run(self, arguments, success=True):
        command = list(map(str, arguments))
        child = subprocess.run(command, capture_output=True, text=True, timeout=900)
        number = str(len(self.records))
        out, err = self.base / (number + '.stdout'), self.base / (number + '.stderr')
        out.write_text(child.stdout); err.write_text(child.stderr)
        self.records.append({'arguments': command, 'exit_code': child.returncode,
                             'stdout': out.name, 'stderr': err.name,
                             'stdout_sha256': digest(out), 'stderr_sha256': digest(err)})
        (self.base / 'commands.json').write_text(json.dumps(self.records, indent=2) + '\n')
        require((child.returncode == 0) == success,
                'unexpected command status: ' + canonical(command) + '\n' + child.stderr[-2500:])
        return child.stdout


def inspect_archive(archive, destination, source, build, compiler, sanitize, profile='R1'):
    root = archive_root(profile)
    with archive.open('rb') as stream:
        header = stream.read(10)
    require(header[:3] == b'\x1f\x8b\x08' and len(header) == 10 and
            header[3] & 8 == 0 and header[4:8] == bytes(4), 'noncanonical gzip header')
    destination.mkdir()
    hashes = {}
    with tarfile.open(archive, 'r:gz') as bundle:
        for member in bundle:
            parts = PurePosixPath(member.name).parts
            require(member.isfile() and len(parts) > 1 and parts[0] == root and
                    not member.name.startswith('/') and '..' not in parts and '.' not in parts,
                    'archive contains nonregular or escaping member')
            relative = '/'.join(parts[1:])
            require(relative not in hashes and member.name == root + '/' + relative,
                    'duplicate or noncanonical archive path')
            require(member.uid == member.gid == member.mtime == 0 and
                    member.uname == member.gname == '' and member.mode in (0o644, 0o755),
                    'noncanonical tar ownership/time/mode')
            target = destination / relative
            target.parent.mkdir(parents=True, exist_ok=True)
            with bundle.extractfile(member) as incoming, target.open('xb') as output:
                shutil.copyfileobj(incoming, output, 1024 * 1024)
            target.chmod(member.mode)
            require(target.stat().st_size == member.size, 'truncated archive member')
            hashes[relative] = {'bytes': member.size, 'sha256': digest(target)}
    manifest = json.loads((destination / 'release-manifest.json').read_text())
    require(type(manifest['schema_version']) is int and type(manifest['public_api_version']) is int and
            manifest['schema_version'] == 1 and manifest['kind'] == 'crown_release_candidate_v1' and
            manifest['profile'] == profile and manifest['version'] == '0.1.0' and
            manifest['public_api_version'] == 1 and manifest['status'] == 'candidate_unqualified' and
            manifest['release_accepted'] is False, 'packaging inferred release acceptance or changed version')
    require(Path(manifest['build']['compiler']).resolve() == Path(compiler).resolve(),
            'candidate compiler differs from actual build')
    enabled = lambda value: value.upper() in ('ON', 'TRUE', 'YES', '1')
    configuration = next(line.split('=', 1)[1] for line in (build / 'CMakeCache.txt').read_text().splitlines()
                         if line.startswith('CMAKE_BUILD_TYPE:STRING='))
    require(enabled(manifest['build']['sanitizers']) == enabled(sanitize) and
            manifest['build']['configuration'] == configuration, 'candidate build configuration differs')
    require(all(type(manifest['limits'][name]) is int and manifest['limits'][name] > 0
                for name in ('files', 'total_bytes')), 'candidate limits are not positive integer grants')
    indexed = {}
    for row in manifest['files']:
        require(row['path'] not in indexed and type(row['bytes']) is int and row['bytes'] >= 0,
                'duplicate or invalid payload manifest row')
        indexed[row['path']] = {'bytes': row['bytes'], 'sha256': row['sha256']}
    payloads = {name: row for name, row in hashes.items()
                if name not in ('release-manifest.json', 'CHECKSUMS.sha256')}
    require(indexed == payloads, 'payload manifest does not match every actual archive member')
    checksums = ''.join(hashes[name]['sha256'] + '  ' + name + '\n'
                        for name in sorted(hashes) if name != 'CHECKSUMS.sha256')
    require((destination / 'CHECKSUMS.sha256').read_text() == checksums, 'CHECKSUMS differs from archive bytes')
    for directory in ('include', 'src', 'apps', 'tools', 'examples', 'cmake', 'tests',
                      'schemas', 'docs', 'benchmarks', 'third_party'):
        for path in (source / directory).rglob('*'):
            if path.is_file() and '__pycache__' not in path.parts and path.suffix != '.pyc':
                name = 'source/' + path.relative_to(source).as_posix()
                require(name in hashes and hashes[name]['sha256'] == digest(path),
                        'complete maintained source/fixture preimage missing: ' + name)
    for name in ('CMakeLists.txt', 'CMakePresets.json', 'dependencies.lock.json', 'README.md', 'Refactor.md'):
        require(hashes['source/' + name]['sha256'] == digest(source / name), 'source build metadata differs')
    baselines = json.loads((source / 'benchmarks/legacy/manifest.json').read_text())['source_sha256_local']
    require(all(hashes['source/' + name]['sha256'] == expected for name, expected in baselines.items()),
            'pinned baseline source prerequisite missing or changed')
    forbidden = {'.git', '.aws', '.codex', 'build', 'cache', '__pycache__'}
    require(not any(name.startswith('source/') and name.split('/')[1] in forbidden for name in hashes),
            'private/cache/build root copied into source archive')
    readme = (destination / 'README.md').read_text()
    require(readme.startswith('# CROWN Next 0.1.0: ' + profile + ' candidate\n'),
            'candidate README profile differs from archive/manifest')
    for target in re.findall(r'\[[^\]]+\]\(([^)]+)\)', readme):
        require((destination / target).is_file(), 'candidate README link is missing: ' + target)
    if profile == 'R2':
        require('report/r2-report.md' in readme and 'source/docs/releases/r2.md' in readme and
                'CLI retains its exact-set identity and defaults' in readme,
                'R2 README lost native SDK scope or stable CLI boundary')
        targets = next((destination / 'sdk').rglob('CrownTargets.cmake')).read_text()
        require(all(name in targets for name in ('CROWN::sql_rows_recovery', 'CROWN::sql_aggregate_recovery')),
                'R2 public SQL recovery targets missing from installed SDK')
    return manifest, hashes


def sqlite_prefixes(sql, events):
    database = sqlite3.connect(':memory:')
    database.execute('CREATE TABLE r(a INTEGER,b INTEGER,PRIMARY KEY(a,b))')
    database.execute('CREATE TABLE s(b INTEGER,c INTEGER,PRIMARY KEY(b,c))')
    snapshots = []
    for operation, table, values in events:
        columns = ('a', 'b') if table == 'r' else ('b', 'c')
        statement = 'INSERT OR IGNORE INTO ' + table + ' VALUES(?,?)' if operation == '+' else \
                    'DELETE FROM ' + table + ' WHERE ' + columns[0] + '=? AND ' + columns[1] + '=?'
        database.execute(statement, values)
        snapshots.append(sorted(list(row) for row in database.execute(sql)))
    database.close()
    return snapshots


def installed_consumer(base, package, source, build, compiler, sanitize, runner):
    sdk = package / 'sdk'
    require(runner.run([sdk / 'bin/crown', '--version']) ==
            'CROWN Next 0.1.0 (C++23; exact set semantics; native API 1)\n', 'SDK CLI version/API differs')
    require(not list(sdk.rglob('*testing*.a')) and not list(sdk.rglob('libcrown_reference.a')),
            'private test/reference archive installed')
    configs = list(sdk.rglob('CrownConfig.cmake'))
    require(len(configs) == 1, 'extracted SDK package configuration is ambiguous')
    outside, consumer = base / 'outside-source', base / 'outside-build'
    shutil.copytree(sdk / 'share/crown/examples/native-workflow', outside)
    arguments = ['cmake', '-S', outside, '-B', consumer, '-DCMAKE_BUILD_TYPE=Release',
                 '-DCMAKE_CXX_COMPILER=' + compiler, '-DCrown_DIR=' + str(configs[0].parent),
                 '-DCMAKE_FIND_USE_PACKAGE_REGISTRY=OFF', '-DCMAKE_FIND_USE_SYSTEM_PACKAGE_REGISTRY=OFF']
    if sanitize.upper() in ('ON', 'TRUE', 'YES', '1'):
        arguments.append('-DCMAKE_CXX_FLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer')
    runner.run(arguments); runner.run(['cmake', '--build', consumer, '--parallel', '2'])
    units = json.loads((consumer / 'compile_commands.json').read_text())
    require(len(units) == 1 and all(flag in units[0]['command'] for flag in
            ('-std=c++23', '-Wall', '-Wextra', '-Wpedantic', '-Wconversion', '-Wsign-conversion', '-Werror')),
            'public consumer lost strict C++23 build')
    link = (consumer / 'CMakeFiles/crown_native_workflow.dir/link.txt').read_text()
    for forbidden in (source / 'include', source / 'third_party', build,
                      package / 'source/include', package / 'source/third_party'):
        require(str(forbidden) not in units[0]['command'] + link, 'consumer used producer/source closure')
    require('libcrown_reference' not in link and '_testing' not in link, 'consumer linked private test ABI')
    catalog = {'schema_version': 1, 'catalog': {'version': 1, 'tables': [
        {'name': table, 'source_schema_version': 1, 'constraints': [], 'key_hints': [],
         'statistics': {'distinct_counts': []},
         'columns': [{'name': column, 'type': 'int64', 'nullable': False} for column in columns]}
        for table, columns in [('r', ('a', 'b')), ('s', ('b', 'c'))]]}}
    catalog_path, sql_path, input_path = base / 'catalog.json', base / 'unseen.sql', base / 'input.jsonl'
    catalog_path.write_text(canonical(catalog) + '\n')
    catalog_hash = hashlib.sha256(canonical(json.loads(runner.run(
        [sdk / 'bin/crown', 'canonicalize-catalog', catalog_path]))).encode()).hexdigest()
    sql = 'SELECT DISTINCT s.c,r.a,r.b,43 AS token FROM r JOIN s ON r.b=s.b WHERE r.a>=0 AND s.c<>19'
    sql_path.write_text(sql + '\n')
    events = [('+', 'r', [4, 11]), ('+', 's', [11, 71]), ('+', 's', [11, 72]),
              ('+', 'r', [-1, 11]), ('+', 's', [11, 19]), ('+', 'r', [9, 31]),
              ('+', 's', [31, 93]), ('+', 'r', [4, 11]), ('-', 's', [11, 71]),
              ('-', 's', [77, 77]), ('-', 'r', [-1, 11]), ('-', 's', [31, 93]), ('+', 's', [31, 94])]
    input_path.write_text(''.join(canonical({'schema_version': 1, 'catalog_sha256': catalog_hash,
        'catalog_version': 1, 'source_schema_version': 1, 'sequence': number, 'table': table,
        'operation': 'insert' if operation == '+' else 'delete', 'values': values,
        'source_position': {'source': 'release-feed', 'offset': number * 7}}) + '\n'
        for number, (operation, table, values) in enumerate(events, 1)))
    for number, expected in enumerate(sqlite_prefixes(sql, events), 1):
        mode = 'run' if number == 1 else 'restore'
        actual = json.loads(runner.run([consumer / 'crown_native_workflow', mode, sql_path,
            catalog_path, input_path, base / 'state.root', base / 'results.sink', '1']))
        require(actual['public_api_version'] == 1 and actual['sequence'] == actual['verified_output_sequence'] == number and
                actual['source_positions'] == {'release-feed': number * 7} and sorted(actual['rows']) == expected,
                'extracted SDK unseen SQL/SQLite state, progress or recovery differs')
    return len(events)


def main():
    parser = argparse.ArgumentParser()
    for name in ('source', 'build', 'compiler', 'sanitize'):
        parser.add_argument(name)
    parser.add_argument('artifacts', nargs='?')
    args = parser.parse_args()
    source, build = Path(args.source).resolve(), Path(args.build).resolve()
    if args.artifacts:
        base = Path(args.artifacts).resolve(); base.mkdir(parents=True, exist_ok=False)
        context = nullcontext(base)
    else:
        context = tempfile.TemporaryDirectory(prefix='crown-release-package-')
    with context as temporary:
        base = Path(temporary); runner = Runner(base)
        roles = {}
        for role, original in [('report', 'docs/experimental_report.md'),
                               ('figures', 'docs/component_evaluation.md'), ('evidence', 'tests/workflow/manifest.json')]:
            directory = base / role; directory.mkdir(); roles[role] = directory
            shutil.copyfile(source / original, directory / Path(original).name)
        # Small documentation fixtures exercise portable entry paths, not report qualification.
        shutil.copyfile(source / 'docs/experimental_report.md', roles['report'] / 'report.md')
        shutil.copyfile(source / 'docs/experimental_report.md', roles['report'] / 'r2-report.md')
        shutil.copyfile(source / 'docs/component_evaluation.md', roles['figures'] / 'index.md')
        command = [sys.executable, source / 'tools/package_release.py', '--source', source,
                   '--build-dir', build, '--report', roles['report'], '--figures', roles['figures'],
                   '--evidence', roles['evidence']]
        occupied = base / 'occupied'; occupied.mkdir(); (occupied / 'marker').write_text('preserve\n')
        runner.run(command + ['--output', occupied], False)
        require(sorted(p.name for p in occupied.iterdir()) == ['marker'] and
                (occupied / 'marker').read_text() == 'preserve\n', 'existing output was modified')
        missing = base / 'missing-role-output'
        runner.run(command + ['--report', base / 'missing', '--output', missing], False)
        require(not missing.exists(), 'missing role created output before rejection')
        linked = base / 'linked-evidence'; linked.mkdir()
        (linked / 'source-link').symlink_to(source / 'README.md')
        denied_link = base / 'symlink-output'
        runner.run(command + ['--evidence', linked, '--output', denied_link], False)
        require(not denied_link.exists(), 'symlink input created output before rejection')
        alias = roles['evidence'] / '..' / 'evidence' / 'nested-output'
        original_names = sorted(path.name for path in roles['evidence'].iterdir())
        runner.run(command + ['--output', alias], False)
        require(sorted(path.name for path in roles['evidence'].iterdir()) == original_names,
                'aliased output wrote into a packaged input tree')
        runner.run(command + ['--output', base / 'unknown', '--unknown-release-option'], False)
        unknown_profile = base / 'unknown-profile'
        runner.run(command + ['--profile', 'R3', '--output', unknown_profile], False)
        require(not unknown_profile.exists(), 'unknown profile created output before rejection')
        r2_report = base / 'report-without-r2-entry'; r2_report.mkdir()
        shutil.copyfile(source / 'docs/experimental_report.md', r2_report / 'report.md')
        missing_r2 = base / 'missing-r2-entry-output'
        runner.run(command + ['--profile', 'R2', '--report', r2_report, '--output', missing_r2], False)
        require(not missing_r2.exists(), 'missing R2 entry created output before rejection')
        for option in ('--max-files', '--max-total-bytes'):
            denied = base / option[2:]
            runner.run(command + ['--output', denied, option, '1'], False)
            require(not (denied / (archive_root('R1') + '.tar.gz')).exists(), 'denied grant produced candidate archive')
        output = base / 'candidate'
        runner.run(command + ['--output', output])
        archive = output / (archive_root('R1') + '.tar.gz')
        package = base / 'extracted relocated SDK'
        manifest, hashes = inspect_archive(archive, package, source, build, args.compiler, args.sanitize)
        for role, directory in roles.items():
            for original in directory.iterdir():
                require(hashes[role + '/' + original.name]['sha256'] == digest(original), 'input subset bytes changed')
        prefixes = installed_consumer(base, package, source, build, args.compiler, args.sanitize, runner)
        explicit_r1 = base / 'candidate-explicit-r1'
        runner.run(command + ['--profile', 'R1', '--output', explicit_r1])
        explicit_archive = explicit_r1 / (archive_root('R1') + '.tar.gz')
        require(digest(explicit_archive) == digest(archive), 'default and explicit R1 archive bytes differ')
        r2_output = base / 'candidate-r2'
        runner.run(command + ['--profile', 'R2', '--output', r2_output])
        r2_archive = r2_output / (archive_root('R2') + '.tar.gz')
        r2_base = base / 'r2-receiving'; r2_base.mkdir()
        r2_package = r2_base / 'extracted relocated SDK'
        r2_manifest, r2_hashes = inspect_archive(r2_archive, r2_package, source, build,
                                               args.compiler, args.sanitize, 'R2')
        for role, directory in roles.items():
            for original in directory.iterdir():
                require(r2_hashes[role + '/' + original.name]['sha256'] == digest(original),
                        'R2 input subset bytes changed')
        r2_prefixes = installed_consumer(r2_base, r2_package, source, build,
                                         args.compiler, args.sanitize, runner)
        receipt = {'status': 'PASS_independent_release_archive_install_SQLite_receiving',
                   'archive_sha256': digest(archive), 'payload_files': len(manifest['files']),
                   'independent_SQLite_prefixes': prefixes, 'release_accepted': False,
                   'default_explicit_R1_archive_equal': True,
                   'R2': {'archive_sha256': digest(r2_archive), 'payload_files': len(r2_manifest['files']),
                          'independent_set_SQLite_prefixes': r2_prefixes, 'release_accepted': False,
                          'scope': 'R2 package layout/manifest/exports and retained R1 set workflow only; independent SQL bag/aggregate qualification is separate.'},
                   'fixture_scope': 'Packaging-only documentation/fixture subsets; no synthetic performance data or full-report qualification.'}
        (base / 'receiving.json').write_text(json.dumps(receipt, indent=2) + '\n')
        print(canonical(receipt))
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except Exception as error:
        print('Release package verification failed: ' + str(error), file=sys.stderr)
        raise SystemExit(1)
