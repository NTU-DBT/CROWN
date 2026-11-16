"""Reject real stale links and archives before controlled measurement."""
import json
from pathlib import Path
import shlex
import subprocess
import sys
import tempfile

sys.dont_write_bytecode = True
root = Path(sys.argv[1]).resolve()
sys.path.insert(0, str(root / 'tools'))
from run_measurements import build_provenance


def run(command, directory=None):
    result = subprocess.run(command, cwd=directory, text=True, capture_output=True, timeout=90)
    assert result.returncode == 0, (command, result.stdout, result.stderr)


with tempfile.TemporaryDirectory(prefix='crown-provenance-') as temporary:
    source = Path(temporary) / 'source'; build = Path(temporary) / 'build'
    (source / 'examples/workload-measurement').mkdir(parents=True)
    (source / 'src').mkdir()
    library = source / 'src/core.cpp'; library.write_text('int value() { return 0; }\n')
    main = 'int value(); int main() { return value(); }\n'
    (source / 'main.cpp').write_text(main)
    (source / 'examples/workload-measurement/main.cpp').write_text(main)
    (source / 'CMakeLists.txt').write_text('''cmake_minimum_required(VERSION 3.25)
project(provenance_fixture LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_library(crown_core STATIC src/core.cpp)
add_executable(crown main.cpp)
add_executable(crown_measure_workload examples/workload-measurement/main.cpp)
target_link_libraries(crown PRIVATE crown_core)
target_link_libraries(crown_measure_workload PRIVATE crown_core)
''')
    configure = ['cmake', '-S', str(source), '-B', str(build), '-DCMAKE_CXX_COMPILER:FILEPATH=' + sys.argv[2]]
    run(configure)

    def make(*targets):
        command = ['cmake', '--build', str(build), '--parallel', '2']
        if targets: command += ['--target', *targets]
        run(command)

    def provenance():
        return build_provenance(root, build, build / 'crown', build / 'crown_measure_workload')

    def rejected(reason):
        try: provenance()
        except ValueError as error:
            assert reason in str(error), str(error)
        else: raise AssertionError('stale build was accepted: ' + reason)

    make()
    initial = provenance()
    assert len(initial['compiled_units']) == 3
    library.write_text('int value() { return 1; }\n')
    make('crown_core')
    rejected('relink before measurement')
    make('crown')
    rejected('relink before measurement')
    make('crown_measure_workload')
    provenance()

    # Execute an actual recorded compiler command without rebuilding its archive.
    library.write_text('int value() { return 2; }\n')
    commands = json.loads((build / 'compile_commands.json').read_text())
    member = next(entry for entry in commands if Path(entry['file']) == library)
    run(shlex.split(member['command']), member['directory'])
    rejected('newer than its archive')
    make()
    provenance()

    with (source / 'CMakeLists.txt').open('a') as output:
        output.write('target_compile_definitions(crown_core PRIVATE PROVENANCE_NEW_FLAGS=1)\n')
    run(configure)
    rejected('compiler flags changed')
    make()
    provenance()
    run([*configure, '-DCMAKE_EXE_LINKER_FLAGS=-Wl,--as-needed'])
    rejected('link command changed')
    make()
    provenance()
print('Build provenance: actual stale library, one stale executable, stale archive member, changed compiler/link flags rejected; rebuilt closure accepted')
