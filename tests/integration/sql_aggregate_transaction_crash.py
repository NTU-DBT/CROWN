#!/usr/bin/env python3
"""Run actual persistence cuts, then decode the real healthy sink tapes.

The native matrix compares every repaired tape byte and every known physical
weight, snapshot/frontier and next update. This independent decoder checks the
typed payloads and identities of each baseline/probe tape with Python integers.
It does not expand the INT64_MAX-sized bag or infer host power-loss behavior.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import tempfile

from sql_aggregate_runtime_oracle import session_epoch

MAX = 2**63-1


def frames(encoded):
    data = bytes.fromhex(encoded)
    result, at = [], 0
    while at < len(data):
        assert len(data)-at >= 148
        size = 148+struct.unpack_from("<Q", data, at+12)[0]
        frame = data[at:at+size]
        assert len(frame) == size and frame[:8] == b"CROWNAG2"
        assert struct.unpack_from("<HH", frame, 8) == (1, 0)
        assert frame[20:84] == hashlib.sha256(frame[148:]).hexdigest().encode()
        assert frame[84:148] == hashlib.sha256(frame[:84]).hexdigest().encode()
        result.append(frame); at += size
    assert at == len(data) and result
    header = result[0]
    assert header[148] == 4 and struct.unpack_from("<Q", header, 149)[0] == 0
    assert header[157:189] == b"1"*32
    assert header[253:285] == b"2"*32 and len(header) == 293
    assert struct.unpack_from("<Q", header, 285)[0] == 0
    return [session_epoch(frame.hex()) for frame in result[1:]]


def row(kind):
    if kind == "small":
        return ["next", 2, 2, 1, {"decimal": "1"}, {"decimal": "0.5"}]
    probe = kind == "probe"
    return [None if kind == "seed" else "next", MAX-1 if kind == "mixed" else MAX,
            MAX-1 if probe else MAX-2, int(probe),
            {"decimal": "1" if probe else "0"}, {"decimal": "0"}]


def change(key, before, after):
    return {"key": [7, key], "before": before, "after": after}


def check_tape(case, probe):
    decoded = frames(case["probe_sink_hex" if probe else "sink_hex"])
    action = case["action"]
    expected = [([change(None, None, row("seed"))], 1, 1),
                ([change(None, row("seed"), None), change("next", None, row("mixed"))], 2, 2)]
    if action == 6:
        expected.append(([change("next", row("mixed"), None)], 5, 3))
    if probe:
        before, after = (None, row("small")) if action == 6 else (row("mixed"), row("probe"))
        generation = 3 if action in (5, 6) else 2
        expected.append(([change("next", before, after)], case["command"]+1, generation))
    assert len(decoded) == len(expected)
    for sequence, (actual, (output, command, generation)) in enumerate(zip(decoded, expected), 1):
        assert actual["sequence"] == sequence and actual["command"] == command
        assert actual["generation"] == generation and actual["changed"] and actual["group_changed"]
        # JSON text equality preserves bool/int and decimal/int distinctions.
        assert json.dumps(actual["output"], sort_keys=True) == json.dumps(output, sort_keys=True)


def main():
    assert __debug__, "assertions must remain enabled"
    parser = argparse.ArgumentParser()
    parser.add_argument("--driver", required=True)
    parser.add_argument("--output-root", required=True)
    args = parser.parse_args()
    root = Path(args.output_root); root.mkdir(parents=True, exist_ok=True)
    destination = Path(tempfile.mkdtemp(prefix="run-", dir=root))/"actual-sink-tapes.json"
    run = subprocess.run([args.driver, str(destination)], capture_output=True, text=True, timeout=1500)
    assert run.returncode == 0, (run.returncode, run.stdout, run.stderr, str(destination))
    cases = json.loads(destination.read_text())
    assert len(cases) == 14 and {(c["indexed"], c["action"]) for c in cases} == {
        (indexed, action) for indexed in (False, True) for action in range(7)}
    for case in cases:
        assert case["syscall_EIO_cuts"] > 0 and case["process_cuts"] > 0
        check_tape(case, False); check_tape(case, True)
    print(json.dumps({"status": "pass", "cases": 14,
                      "syscall_EIO_cuts": sum(c["syscall_EIO_cuts"] for c in cases),
                      "real_process_cuts": sum(c["process_cuts"] for c in cases),
                      "independently_decoded_tapes": 28, "exact_count_boundary": MAX,
                      "artifact": str(destination), "artifact_sha256": hashlib.sha256(destination.read_bytes()).hexdigest(),
                      "host_power_loss_claim": False}))


if __name__ == "__main__":
    main()
