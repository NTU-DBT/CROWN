#!/usr/bin/env python3
"""Exercise real R2 CLI processes/files against independent DuckDB snapshots.

The helper persists an actual public-API Input/Commit before releasing its locks.
These are deterministic durable-boundary fixtures; native EIO/process-cut sweeps
have their own tests. AVG uses exact SQL SUM/COUNT and the existing Fraction rule.
"""
import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import tempfile

import duckdb  # Required, no install or fallback.
from fractions import Fraction
from aggregate_sql_oracle import numeric
from sql_aggregate_runtime_oracle import session_epoch


def invoke(binary, *arguments, code=0):
    result = subprocess.run([str(binary), "aggregate", *map(str, arguments)],
                            capture_output=True, text=True, timeout=180)
    assert result.returncode == code, (arguments, result.returncode, result.stdout, result.stderr)
    if code:
        assert not result.stdout and json.loads(result.stderr)["error"]["code"]
        return json.loads(result.stderr)
    return json.loads(result.stdout)


def edit(values, before, after):
    return {"table": "r", "source_schema_version": 1, "values": list(values),
            "before": before, "after": after}


def fingerprint(root, sink):
    return {str(path): hashlib.sha256(path.read_bytes()).hexdigest()
            for path in sorted(set(root.parent.glob(root.name + "*")) | {sink}) if path.is_file()}


def sql_groups(connection, state):
    connection.execute("DELETE FROM r")
    rows = [row for row, weight in state.items() for _ in range(weight)]
    if rows:
        connection.executemany("INSERT INTO r VALUES (?,?)", rows)
    result = {}
    for g, all_count, count, total in connection.execute(
            "SELECT g,COUNT(*),COUNT(x),SUM(x) FROM r GROUP BY g").fetchall():
        result[json.dumps([g])] = [g, all_count, count,
                                  numeric(total) if total is not None else None,
                                  numeric(Fraction(total, count), 2) if count else None]
    return result


def snapshot(binary, root, sink, recovery, expected):
    result = invoke(binary, "snapshot", root, sink, *recovery)
    assert [column["kind"] for column in result["columns"]] == ["string", "int64", "int64", "decimal", "decimal"]
    actual = {json.dumps(group["key"]): group["values"] for group in result["groups"]}
    assert actual == expected, (actual, expected)


def sink_epochs(sink, expected, initial=None):
    data = sink.read_bytes()
    offset = 0
    frames = []
    while offset < len(data):
        assert data[offset:offset+8] == b"CROWNAG2" and len(data)-offset >= 148
        size = 148 + struct.unpack_from("<Q", data, offset+12)[0]
        frame = data[offset:offset+size]
        assert len(frame) == size
        assert frame[20:84] == hashlib.sha256(frame[148:]).hexdigest().encode()
        assert frame[84:148] == hashlib.sha256(frame[:84]).hexdigest().encode()
        frames.append(frame)
        offset += size
    assert frames[0][148] == 4 and len(frames)-1 == len(expected)
    materialized = dict(initial or {})
    for sequence, (frame, reference) in enumerate(zip(frames[1:], expected), 1):
        epoch = session_epoch(frame.hex())
        assert epoch["sequence"] == sequence
        for change in epoch["output"]:
            key = json.dumps(change["key"])
            assert materialized.get(key) == change["before"]
            if change["after"] is None:
                del materialized[key]
            else:
                materialized[key] = change["after"]
        assert materialized == reference, (sequence, materialized, reference)


def physical_options():
    return {"schema_version": 2,
            "policy": {"arithmetic": "exact-nonnull-v1", "planner": "crown-tree-v1",
                       "optimization": "structural-height-v1", "cost_model": "no-cost-v1"},
            "limits": {"work": 1000000, "identity_work": 1000000},
            "indexed_storage": {
                "algorithm": "indexed_chained_v1", "traversal": "insertion_first_live_key_v1",
                "component_scope": "per_table_including_undo", "work_scope": "operation_aggregate",
                "limits": dict(zip(("rows", "indices", "keys", "memberships", "nodes", "directory_slots",
                                    "arena_slots", "arena_pins", "journal_entries"),
                                   (4096, 64, 32768, 65536, 131072, 524288, 8192, 32768, 8192))),
                "work": {key: 1000000000 for key in ("structural_steps", "scalar_fields", "scalar_bytes",
                                                      "pointer_slots", "link_actions")}}}


def profile(binary, helper, directory, indexed):
    directory.mkdir()
    root, sink, source = (directory / name for name in ("query.root", "groups.sink", "input.jsonl"))
    catalog = directory / "catalog.json"
    sql = directory / "query.sql"
    catalog.write_text(json.dumps({"schema_version": 1, "catalog": {"version": 1, "tables": [
        {"name": "r", "columns": [{"name": "g", "type": "string", "nullable": True},
                                   {"name": "x", "type": "int64", "nullable": True}]}]}}))
    sql.write_text("SELECT g,COUNT(*),COUNT(x),SUM(x),AVG(x) FROM r GROUP BY g")
    creation = ["--average-scale", "2", "--count-limit", "5"]
    recovery = []
    if indexed:
        options = directory / "physical.json"
        options.write_text(json.dumps(physical_options()))
        creation += ["--physical-options", options]
        recovery = ["--rebuild-indexed-work", "100000000"]
    created = invoke(binary, "create", sql, catalog, root, sink, *creation)
    assert created["logged"] == created["committed"] == 0
    assert created["storage_backend"] == ("indexed_chained_v1" if indexed else "reference_ordered_v1")
    a, empty, b, null = ("a", 2), ("a", None), ("b", 4), (None, -3)
    commands = [
        ([edit(a, 0, 2)], None),
        ([edit(a, 2, 0), edit(empty, 0, 3), edit(b, 0, 1)], None),
        ([edit(b, 1, 2), edit(b, 2, 3)], None),
        ([], None),
        ([edit(b, 99, 0)], "weight_mismatch"),
        ([edit(b, 3, 0)], None),
        ([edit(("overflow", (1 << 63)-1), 0, 6)], "aggregate_overflow"),
        ([edit(null, 0, 1)], None),
        ([edit(empty, 3, 0)], None),
        ([edit(("cancel", 8), 0, 2), edit(("cancel", 8), 2, 0)], None),
        ([edit(("large", 1), 0, 6)], "aggregate_overflow")]
    records = [{"schema_version": 1, "binding_sha256": created["binding_sha256"],
                "sequence": i, "replacements": edits,
                "source_position": {"source": "cli-source", "offset": i}}
               for i, (edits, _) in enumerate(commands, 1)]
    lines = [json.dumps(record, separators=(",", ":")) + ("\r\n" if i % 2 else "\n")
             for i, record in enumerate(records)]
    source.write_bytes("".join(lines).encode())
    connection = duckdb.connect(":memory:")
    connection.execute("CREATE TABLE r(g VARCHAR,x BIGINT)")
    state = Counter()
    expected_commits = []
    for sequence, (edits, reject) in enumerate(commands, 1):
        if sequence in (1, 2):
            mode = "--leave-log" if sequence == 1 else "--leave-output"
            seeded = subprocess.run([str(helper), mode, str(root), str(sink), str(source),
                                     *(["indexed"] if indexed else [])], capture_output=True, text=True, timeout=180)
            assert seeded.returncode == 0, seeded.stderr
            pending = invoke(binary, "status", root, sink, *recovery)
            assert pending["logged"] == sequence and pending["logged_reader"]["records"] == sequence
            assert pending["pending"] == (sequence == 1) and pending["output_pending"] == (sequence == 2)
            zero = invoke(binary, "run", root, sink, source, "--commands", 0, *recovery)
            assert zero["processed"] == 0 and zero["pending"] == (sequence == 1)
            if sequence == 2:
                result = zero
                assert zero["delivered"] == 2
            else:
                result = invoke(binary, "run", root, sink, source, "--commands", 1, *recovery)
        elif sequence == 3:
            # A failed report follows the durable decision. Retry must resume W,
            # never re-log that command or append a duplicate sink epoch.
            invoke(binary, "run", root, sink, source, "--commands", 1, "--max-bytes", 2, *recovery, code=2)
            result = invoke(binary, "run", root, sink, source, "--commands", 0, *recovery)
        else:
            result = invoke(binary, "run", root, sink, source, "--commands", 1, *recovery)
        assert result["logged"] == result["disposed"] == sequence
        if reject:
            assert result["last_reject"] == {"sequence": sequence, "reason": reject}
        else:
            for replacement in edits:
                row = tuple(replacement["values"])
                assert state[row] == replacement["before"]
                state[row] = replacement["after"]
            expected_commits.append(sql_groups(connection, state))
        expected = sql_groups(connection, state)
        assert result["committed"] == result["delivered"] == len(expected_commits)
        snapshot(binary, root, sink, recovery, expected)
        sink_epochs(sink, expected_commits)
        if sequence in (5, 9):
            generation = invoke(binary, "checkpoint", root, sink, *recovery)["generation"]
            assert generation in (2, 3)
            snapshot(binary, root, sink, recovery, expected)
    assert invoke(binary, "run", root, sink, source, *recovery)["processed"] == 0
    stable = fingerprint(root, sink)
    # Invalid or incomplete *transport* is rejected before log, never recorded as
    # a semantic native Reject. A fresh reader retries from the durable origin.
    original = source.read_bytes()
    for tail in (b"\n", b'{"schema_version":1}\n', json.dumps(dict(records[-1], sequence=12, binding_sha256="f"*64)).encode()+b"\n"):
        source.write_bytes(original+tail)
        invoke(binary, "run", root, sink, source, *recovery, code=2)
        assert fingerprint(root, sink) == stable
    source.write_bytes(original[:-1])
    invoke(binary, "run", root, sink, source, *recovery, code=2)
    assert fingerprint(root, sink) == stable
    source.write_bytes(original[:-1]+b" "+b"{}\n")
    failure = invoke(binary, "run", root, sink, source, *recovery, code=2)
    assert failure["error"]["code"] == "invalid_input_progress"
    assert fingerprint(root, sink) == stable
    source.write_bytes(original)
    invoke(binary, "status", root, sink, "--query-id", "f"*32, *recovery, code=2)
    invoke(binary, "status", root, sink, "--unknown", 1, *recovery, code=2)
    assert fingerprint(root, sink) == stable
    if indexed:
        failure = invoke(binary, "status", root, sink, "--rebuild-indexed-work", 0, code=2)
        assert failure["error"]["code"] == "storage_work_limit"
        assert fingerprint(root, sink) == stable
        assert invoke(binary, "status", root, sink, *recovery)["logged"] == len(commands)
    # Observation commands are recovery operations. Refuse repair explicitly,
    # then allow the actual complete validation barrier to repair both tails.
    generation = invoke(binary, "status", root, sink, *recovery)["generation"]
    wal = Path(str(root)+f".g{generation:016x}.wal")
    wal.write_bytes(wal.read_bytes()+b"CRO")
    sink.write_bytes(sink.read_bytes()+b"CROWN")
    torn = fingerprint(root, sink)
    invoke(binary, "status", root, sink, "--repair-tail", "no", *recovery, code=2)
    assert fingerprint(root, sink) == torn
    invoke(binary, "status", root, sink, *recovery)
    assert fingerprint(root, sink) == stable
    sink_epochs(sink, expected_commits)
    # SUM of a constant INT uses the admitted signed-bigint result domain.
    # Keep count within bigint while the exact SUM exceeds it, without expanding
    # billions of rows. Main commands 7/11 above test count-limit rejection.
    sum_overflow(binary, directory/"sum-overflow", indexed, connection)
    connection.close()
    return {"indexed": indexed, "commands": len(commands), "commits": len(expected_commits),
            "semantic_rejects": 3, "pending_input_resume": True, "pending_output_resume": True}


def sum_overflow(binary, directory, indexed, connection):
    directory.mkdir()
    sql, catalog, source, root, sink = (directory/name for name in
                                      ("query.sql", "catalog.json", "input.jsonl", "query.root", "sink"))
    sql.write_text("SELECT COUNT(*),SUM(CAST(2 AS INT)) FROM r")
    catalog.write_text(json.dumps({"schema_version": 1, "catalog": {"version": 1, "tables": [
        {"name": "r", "columns": [{"name": "x", "type": "int64"}]}]}}))
    creation, recovery = [], []
    if indexed:
        physical = directory/"physical.json"
        physical.write_text(json.dumps(physical_options()))
        creation = ["--physical-options", physical]
        recovery = ["--rebuild-indexed-work", "100000000"]
    created = invoke(binary, "create", sql, catalog, root, sink, *creation)
    weight = (1 << 62)
    exact_sum = connection.execute("SELECT CAST(? AS DECIMAL(38,0))*2", [weight]).fetchone()[0]
    assert exact_sum > (1 << 63)-1 and weight <= (1 << 63)-1
    commands = [{"schema_version": 1, "binding_sha256": created["binding_sha256"],
                 "sequence": sequence, "replacements": [edit([1], 0, after)]}
                for sequence, after in ((1, weight), (2, 1))]
    source.write_text("\n".join(json.dumps(command) for command in commands))
    rejected = invoke(binary, "run", root, sink, source, "--commands", 1, *recovery)
    assert rejected["last_reject"] == {"sequence": 1, "reason": "aggregate_overflow"}
    assert rejected["committed"] == rejected["delivered"] == 0
    assert invoke(binary, "snapshot", root, sink, *recovery)["groups"][0]["values"] == [0, None]
    invoke(binary, "checkpoint", root, sink, *recovery)
    committed = invoke(binary, "run", root, sink, source, *recovery)
    assert committed["logged"] == committed["disposed"] == 2
    assert committed["committed"] == committed["delivered"] == 1
    assert invoke(binary, "snapshot", root, sink, *recovery)["groups"][0]["values"] == [1, 2]
    sink_epochs(sink, [{"[]": [1, 2]}], {"[]": [0, None]})
    # A consumed unterminated final record is terminal for this CLI source.
    # Adding a terminator afterward leaves the saved offset before that LF.
    stable = fingerprint(root, sink)
    original = source.read_bytes()
    following = dict(commands[-1], sequence=3, replacements=[edit([1], 1, 2)])
    source.write_bytes(original+b"\n"+json.dumps(following).encode()+b"\n")
    refused = invoke(binary, "run", root, sink, source, *recovery, code=2)
    assert refused["error"]["code"] == "invalid_input_progress"
    assert fingerprint(root, sink) == stable
    source.write_bytes(original)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--binary", required=True, type=Path)
    parser.add_argument("--helper", required=True, type=Path)
    args = parser.parse_args()
    with tempfile.TemporaryDirectory(prefix="crown-r2-cli-") as directory:
        results = [profile(args.binary, args.helper, Path(directory)/name, indexed)
                   for name, indexed in (("reference", False), ("indexed", True))]
    print(json.dumps({"status": "pass", "engine": "DuckDB "+duckdb.__version__, "profiles": results}))


if __name__ == "__main__":
    main()
