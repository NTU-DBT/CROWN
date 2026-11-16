#!/usr/bin/env python3
"""Check the real CLI's final stdout and diagnostic failure boundary on Linux."""
import json
from pathlib import Path
import resource
import subprocess
import sys


def no_core_dump():
    """Keep a regression that aborts from leaving a core file in the workspace."""
    resource.setrlimit(resource.RLIMIT_CORE, (0, 0))


def require(value, message):
    """Fail this process test with the child observation that violated its spec."""
    if not value:
        raise RuntimeError(message)


def main():
    """Exercise small buffered writes and an exception from diagnostic encoding."""
    executable = str(Path(sys.argv[1]).resolve())
    for argument in ('--version', '--help'):
        normal = subprocess.run([executable, argument], capture_output=True,
                                preexec_fn=no_core_dump, timeout=30)
        require(normal.returncode == 0 and normal.stdout and not normal.stderr,
                f'{argument}: unexpected ordinary result {normal}')
        # These short writes can fit in stdout's buffer. Exit must check flush.
        with open('/dev/full', 'wb', buffering=0) as full:
            failed = subprocess.run([executable, argument], stdout=full,
                                    stderr=subprocess.PIPE, preexec_fn=no_core_dump,
                                    timeout=30)
        require(failed.returncode == 2, f'{argument}: {failed}')
        require(json.loads(failed.stderr)['error']['code'] == 'io_error', failed.stderr)
    # A POSIX argument may contain bytes that strict JSON cannot encode. The
    # error formatter then throws from a catch body, past its sibling handlers.
    invalid = subprocess.run([bytes(executable, 'utf-8'), b'\xff', b'unused'],
                             capture_output=True, preexec_fn=no_core_dump, timeout=30)
    require(invalid.returncode == 3 and not invalid.stdout, str(invalid))
    require(json.loads(invalid.stderr)['error']['code'] == 'internal_error', invalid.stderr)
    print('CLI process boundary: normal output, failed flush and diagnostic encoding pass')


if __name__ == '__main__':
    main()
