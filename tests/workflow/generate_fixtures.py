#!/usr/bin/env python3
"""Generate independent finite SQL/native-event workflow fixtures using stdlib only."""
from decimal import Decimal
from pathlib import Path
import hashlib
import json

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[1]


def digest(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as f:
        for block in iter(lambda: f.read(1024 * 1024), b""):
            h.update(block)
    return h.hexdigest()


def canonical_decimal(value: Decimal) -> str:
    text = format(value, "f")
    if "." in text:
        text = text.rstrip("0").rstrip(".")
    if text in ("", "-0", "+0"):
        return "0"
    return text


def typed(kind: str, raw):
    if kind == "int64":
        assert isinstance(raw, int) and not isinstance(raw, bool)
        assert -(1 << 63) <= raw < (1 << 63)
        return (kind, raw)
    if kind == "string":
        assert isinstance(raw, str)
        return (kind, raw)
    if kind == "bool":
        assert isinstance(raw, bool)
        return (kind, raw)
    if kind == "date":
        assert isinstance(raw, dict) and set(raw) == {"date"}
        return (kind, raw["date"])
    if kind == "decimal":
        assert isinstance(raw, dict) and set(raw) == {"decimal"}
        return (kind, Decimal(raw["decimal"]))
    raise AssertionError(kind)


def encode_scalar(cell):
    kind, raw = cell
    if kind == "date":
        return {"date": raw}
    if kind == "decimal":
        return {"decimal": canonical_decimal(raw)}
    return raw


def encode_rows(rows):
    return [[encode_scalar(value) for value in row] for row in sorted(rows)]


def oracle_path(db):
    edge = db["edge"]
    return {
        (src, mid, dst)
        for (src, mid) in edge
        for (next_src, dst) in edge
        if mid == next_src
    }


def oracle_projection(db):
    return {(projected_key,) for (projected_key, witness) in db["records"]}


def oracle_exists(db):
    found = any(active == ("bool", True) for (active,) in db["flags"])
    return {(('bool', found),)}


def oracle_product(db):
    return {
        (left_value, right_value)
        for (left_value,) in db["left_rel"]
        for (right_value,) in db["right_rel"]
    }


def oracle_all_scalars(db):
    return {row for row in db["scalar_values"]}


CASES = [
    {
        "name": "full_head_self_join_loop_new_new",
        "description": "Full-head Edge(x,y), Edge(y,z); inserting one loop into empty Edge yields the same new tuple in both aliases and output (x,x,x).",
        "tables": {"edge": [("src", "int64"), ("dst", "int64")]},
        "sql": "SELECT DISTINCT e1.src AS x, e1.dst AS y, e2.dst AS z FROM edge AS e1 JOIN edge AS e2 ON e1.dst = e2.src;\n",
        "oracle": oracle_path,
        "events": [
            ("insert", "edge", [7, 7]),
            ("insert", "edge", [9, 9]),
            ("insert", "edge", [7, 9]),
            ("insert", "edge", [7, 7]),
            ("delete", "edge", [9, 9]),
            ("delete", "edge", [13, 13]),
            ("delete", "edge", [7, 7]),
        ],
    },
    {
        "name": "projected_collision",
        "description": "Two distinct physical records project to one logical key; deleting either witness alone must preserve the answer.",
        "tables": {"records": [("projected_key", "int64"), ("witness", "int64")]},
        "sql": "SELECT DISTINCT r.projected_key FROM records AS r;\n",
        "oracle": oracle_projection,
        "events": [
            ("insert", "records", [5, 1]),
            ("insert", "records", [5, 2]),
            ("delete", "records", [5, 1]),
            ("delete", "records", [5, 2]),
            ("insert", "records", [5, 3]),
            ("delete", "records", [5, 4]),
        ],
    },
    {
        "name": "scalar_exists",
        "description": "Top-level scalar EXISTS over a Boolean filter. Its initial/current result is one Boolean row, false or true.",
        "tables": {"flags": [("active", "bool")]},
        "sql": "SELECT EXISTS (SELECT 1 FROM flags AS f WHERE f.active = TRUE) AS found;\n",
        "oracle": oracle_exists,
        "events": [
            ("insert", "flags", [False]),
            ("insert", "flags", [True]),
            ("insert", "flags", [True]),
            ("delete", "flags", [True]),
            ("delete", "flags", [False]),
        ],
    },
    {
        "name": "disconnected_product",
        "description": "Disconnected two-relation product with ordered events, growth, shrinkage, and empty no-op epochs.",
        "tables": {"left_rel": [("x", "string")], "right_rel": [("y", "string")]},
        "sql": "SELECT DISTINCT l.x, r.y FROM left_rel AS l CROSS JOIN right_rel AS r;\n",
        "oracle": oracle_product,
        "events": [
            ("insert", "left_rel", ["alpha"]),
            ("insert", "right_rel", ["x"]),
            ("insert", "left_rel", ["beta"]),
            ("insert", "right_rel", ["y"]),
            ("delete", "right_rel", ["x"]),
            ("delete", "left_rel", ["alpha"]),
            ("delete", "left_rel", ["alpha"]),
            ("insert", "left_rel", ["gamma"]),
            ("delete", "right_rel", ["y"]),
        ],
    },
    {
        "name": "all_native_scalar_types",
        "description": "Full-head set query covering int64 boundaries, a NUL string, UTF-8 strings, bool, tagged Gregorian dates, and exact tagged decimals; alternate decimal spelling is a typed duplicate.",
        "tables": {
            "scalar_values": [
                ("id", "int64"),
                ("txt", "string"),
                ("truth", "bool"),
                ("event_day", "date"),
                ("amount", "decimal"),
            ]
        },
        "sql": "SELECT DISTINCT v.id, v.txt, v.truth, v.event_day, v.amount FROM scalar_values AS v;\n",
        "oracle": oracle_all_scalars,
        "events": [
            ("insert", "scalar_values", [-(1 << 63), "NUL\x00inside", True, {"date": "2000-02-29"}, {"decimal": "-12.340"}]),
            ("insert", "scalar_values", [(1 << 63) - 1, "café/雪", False, {"date": "2024-02-29"}, {"decimal": "0.00000000000000000000000000000000000001"}]),
            ("insert", "scalar_values", [-(1 << 63), "NUL\x00inside", True, {"date": "2000-02-29"}, {"decimal": "-12.34"}]),
            ("delete", "scalar_values", [(1 << 63) - 1, "café/雪", False, {"date": "2024-02-29"}, {"decimal": "0.00000000000000000000000000000000000001"}]),
            ("delete", "scalar_values", [(1 << 63) - 1, "café/雪", False, {"date": "2024-02-29"}, {"decimal": "0.00000000000000000000000000000000000001"}]),
            ("insert", "scalar_values", [0, "NUL\x00/雪", True, {"date": "1900-02-28"}, {"decimal": "123.45"}]),
            ("delete", "scalar_values", [-(1 << 63), "NUL\x00inside", True, {"date": "2000-02-29"}, {"decimal": "-12.340"}]),
        ],
    },
]


def catalog_for(case):
    tables = []
    for table_name, columns in case["tables"].items():
        encoded_columns = []
        for column_name, kind in columns:
            column = {"name": column_name, "nullable": False, "type": kind}
            if kind == "string":
                column["collation"] = "binary"
            encoded_columns.append(column)
        tables.append({
            "name": table_name,
            "source_schema_version": 1,
            "columns": encoded_columns,
            "constraints": [],
            "statistics": {"distinct_counts": []},
            "key_hints": [],
        })
    return {"schema_version": 1, "catalog": {"version": 1, "tables": tables}}


def build_case(case):
    case_dir = OUT / case["name"]
    case_dir.mkdir(parents=True, exist_ok=True)
    (case_dir / "query.sql").write_text(case["sql"], encoding="utf-8")
    catalog = catalog_for(case)
    (case_dir / "catalog.json").write_text(
        json.dumps(catalog, ensure_ascii=False, indent=2) + "\n", encoding="utf-8"
    )

    column_types = {name: [kind for _, kind in cols] for name, cols in case["tables"].items()}
    physical = {name: set() for name in case["tables"]}
    source = case["name"].replace("_", "-") + "-input"
    event_records = []
    expected_events = []
    before = case["oracle"](physical)
    expected = {
        "schema_version": 1,
        "query": case["name"],
        "oracle_definition": case["description"],
        "initial_current_rows": encode_rows(before),
        "events": [],
    }

    for sequence, (operation, table, raw_values) in enumerate(case["events"], start=1):
        types = column_types[table]
        assert len(types) == len(raw_values)
        row = tuple(typed(kind, value) for kind, value in zip(types, raw_values))
        if operation == "insert":
            physical[table].add(row)
        else:
            assert operation == "delete"
            physical[table].discard(row)
        after = case["oracle"](physical)
        added = after - before
        removed = before - after
        offset = sequence * 100
        record = {
            "schema_version": 1,
            "sequence": sequence,
            "catalog_version": 1,
            "source_schema_version": 1,
            "table": table,
            "operation": operation,
            "source_position": {"source": source, "offset": offset},
            "values": raw_values,
        }
        event_records.append(record)
        delta = ([{"operation": "insert", "values": values} for values in encode_rows(added)]
                 + [{"operation": "delete", "values": values} for values in encode_rows(removed)])
        expected_events.append({
            "sequence": sequence,
            "source_position": {"source": source, "offset": offset},
            "input": {"table": table, "operation": operation, "values": raw_values},
            "current_rows": encode_rows(after),
            "added": encode_rows(added),
            "removed": encode_rows(removed),
            "signed_delta": delta,
        })
        before = after

    event_path = case_dir / "events.template.jsonl"
    event_path.write_text(
        "".join(json.dumps(event, ensure_ascii=False, separators=(",", ":")) + "\n" for event in event_records),
        encoding="utf-8",
    )
    expected["events"] = expected_events
    (case_dir / "expected_oracle.json").write_text(
        json.dumps(expected, ensure_ascii=False, indent=2) + "\n", encoding="utf-8"
    )
    assert [e["sequence"] for e in event_records] == list(range(1, len(event_records) + 1))
    assert all(event_records[i]["source_position"]["offset"] < event_records[i + 1]["source_position"]["offset"]
               for i in range(len(event_records) - 1))
    return {
        "description": case["description"],
        "query": str((case_dir / "query.sql").relative_to(OUT)),
        "catalog": str((case_dir / "catalog.json").relative_to(OUT)),
        "events_template_jsonl": str(event_path.relative_to(OUT)),
        "expected_oracle": str((case_dir / "expected_oracle.json").relative_to(OUT)),
        "event_count": len(event_records),
        "source_id": source,
        "source_offsets": [event["source_position"]["offset"] for event in event_records],
        "empty_delta_sequences": [event["sequence"] for event in expected_events if not event["signed_delta"]],
        "initial_current_rows": expected["initial_current_rows"],
    }

case_manifest = {case["name"]: build_case(case) for case in CASES}
readme = """# Independent O08 workflow fixtures

These five fixtures pair one SQL statement, one standalone catalog, and an ordered physical-event JSONL template with separately generated expected current sets and raw signed set differences. `generate_fixtures.py` uses only Python's standard library; every expected query is a direct finite set comprehension over the current physical table sets.

`events.template.jsonl` contains the logical physical event plus explicit contiguous sequence, catalog/source-schema versions, and strictly increasing source positions. It intentionally omits `catalog_sha256`; a future native runner must compute that binding from the native canonical catalog output and add it to each input record. No native executable was run to derive expected rows or deltas.

The scalar fixture uses JSON strings containing both an escaped NUL and literal UTF-8, JSON booleans, and the native tagged `date` and `decimal` forms. Decimal equality in the independent oracle uses `decimal.Decimal`; output spellings are canonicalized as fixed decimal text.

## Limits

The fixtures and their independent oracles are not a CLI acceptance result. The query admissions, native SQL types, runtime snapshots, local-sink epochs, and recovery behavior have not been built or executed here. Event records need the runner-filled catalog hash before `EventReader` accepts them. Source offsets are logical strictly increasing markers, not byte offsets into the JSONL template. The oracles model finite set semantics and do not prove performance, resource bounds, or durability.
"""
(OUT / "README.md").write_text(readme, encoding="utf-8")

files = {}
for path in sorted(p for p in OUT.rglob("*") if p.is_file() and p.name != "manifest.json"):
    files[str(path.relative_to(OUT))] = digest(path)
spec_sources = ["docs/sql_support.md", "docs/catalog.md", "docs/semantics.md", "docs/scalars.md", "docs/sql_binding.md"]
manifest = {
    "schema_version": 1,
    "title": "O08 independent native CLI workflow fixture packet",
    "generation": "Python standard library only; independent set-comprehension oracles; no CROWN build/test/CLI invocation",
    "event_template_binding": {
        "catalog_sha256": "omitted intentionally; future runner computes it from native canonical catalog output and injects it per event",
        "included_metadata": ["schema_version", "catalog_version", "source_schema_version", "sequence", "source_position"],
    },
    "cases": case_manifest,
    "source_sha256": files,
    "specification_sha256": {name: digest(ROOT / name) for name in spec_sources},
    "limitations": [
        "Fixtures/oracles are independent specifications, not executed CLI acceptance evidence.",
        "Native event binding requires runner injection of catalog_sha256 before EventReader use.",
        "Source positions are explicitly monotone logical offsets and do not encode template byte positions.",
        "Oracles cover finite set results/deltas only, not performance, resource limits, or durability.",
    ],
}
(OUT / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(f"wrote {len(CASES)} workflows; {sum(v['event_count'] for v in case_manifest.values())} events; {len(files)} source-hashed files")
