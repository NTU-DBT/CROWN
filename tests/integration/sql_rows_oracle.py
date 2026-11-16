#!/usr/bin/env python3
"""Independent SQL recomputation for small expanded W05 bags.

DuckDB is required for the registered test. Explicit --engine postgres starts
one private UTF8/C cluster, using supplied binaries, and always stops it. No
production library links either engine. Native and SQL outputs are compared as
typed compressed bags; Python does no join, predicate, or DISTINCT evaluation.
"""
import argparse
from collections import Counter
import csv
import datetime
from decimal import Decimal
from io import StringIO
import json
from pathlib import Path
import random
import re
import shutil
import subprocess
import tempfile

SEED = 0xC705B46
KIND = {"INTEGER": 1, "BIGINT": 2, "VARCHAR": 3, "BOOLEAN": 4, "DATE": 5,
        "integer": 1, "bigint": 2, "text": 3, "boolean": 4, "date": 5, "numeric": 6}


def key(value):
    return json.dumps(value, sort_keys=True, ensure_ascii=False, separators=(",", ":"))


def canonical(value):
    if isinstance(value, Decimal):
        text = format(value, "f")
        if "." in text:
            text = text.rstrip("0").rstrip(".")
        return {"decimal": "0" if value == 0 else text}
    if isinstance(value, datetime.date):
        return {"date": value.isoformat()}
    return value


def type_info(name):
    decimal = re.fullmatch(r"(?:DECIMAL|numeric)\((\d+),\s*(\d+)\)", name)
    return {"kind": 6, "decimal": [int(decimal[1]), int(decimal[2])]} if decimal else {
        "kind": KIND[name], "decimal": None}


def parameter(value):
    if isinstance(value, dict):
        return Decimal(value["decimal"]) if "decimal" in value else datetime.date.fromisoformat(value["date"])
    return value


def column(name, kind, decimal=None):
    result = {"name": name, "type": "bool" if kind == "boolean" else kind, "nullable": True}
    if decimal is not None:
        result["decimal"] = {"precision": 38, "scale": decimal}
    return result


def catalog(scale=2):
    columns = [column("x", "int64"), column("y", "int64"), column("s", "string"),
               column("b", "boolean"), column("d", "date"), column("n", "decimal", scale)]
    return {"version": 1, "tables": [{"name": name, "columns": columns} for name in ("r", "t")]}


def inputs(scale=2, generic=False):
    number = "1.25" if scale == 2 else "1" if scale == 0 else "0.00000000000000000000000000000000000001"
    wide = "99999999999999999999999999999999999999" if generic or scale == 0 else number
    return [[None] * 6, [0, 0, "", False, {"date": "1970-01-01"}, {"decimal": "0"}],
            [1, 1, "a", True, {"date": "2024-02-29"}, {"decimal": number}],
            [1, 2, "b", None, None, {"decimal": number}],
            [2, 1, "A'\\é😀", False, {"date": "2000-01-01"}, {"decimal": wide}],
            [None, 1, "a", True, None, None],
            [1, 1, "A", True, {"date": "2024-02-29"}, {"decimal": number}],
            [1, 1, "é", True, {"date": "2024-02-29"}, {"decimal": number}],
            [1, 1, "e\u0301", True, {"date": "2024-02-29"}, {"decimal": number}]]


def updates(pool):
    rng = random.Random(SEED)
    state = [{}, {}]
    result = []
    for table in range(2):
        for index, row in enumerate(pool):
            after = index % 3 + 1
            result.append({"table": table, "values": row, "before": 0, "after": after})
            state[table][key(row)] = after
    for _ in range(12):
        table = rng.randrange(2)
        row = rng.choice(pool)
        before = state[table].get(key(row), 0)
        after = rng.randrange(4)
        result.append({"table": table, "values": row, "before": before, "after": after})
        state[table][key(row)] = after
    return result


def cases(engine):
    result = []
    def add(sql, scale=2, generic=False, parameters=None, parameter_columns=None):
        item = {"id": f"rows-{len(result):03d}", "sql": sql, "catalog": catalog(None if generic else scale),
                "updates": updates(inputs(scale, generic))}
        if parameters is not None:
            item.update(parameters=parameters, parameter_columns=parameter_columns)
        result.append(item)
    for output in ("x", "s", "b", "d", "n", "x,x,NULL::text", "x = y,b IS UNKNOWN", "x,y,s,b,d,n"):
        add(f"SELECT {output} FROM r")
        add(f"SELECT DISTINCT {output} FROM r")
    for predicate in ("x=y", "x<>y", "x<y", "x>=y", "s=''", "NOT b", "b IS NOT TRUE",
                      "x IS NULL", "x=1", "(x=1 OR x IS NULL) AND b IS NOT FALSE", "x=NULL",
                      "x IS NULL AND x IS NOT NULL", "x=y AND y=1", "x=x", "x=1 AND x=2"):
        add(f"SELECT x,s,b FROM r WHERE {predicate}")
    for sql in ("SELECT r.x,r.s,t.s FROM r JOIN t ON r.x=t.x",
                "SELECT DISTINCT r.x,r.s,t.s FROM r JOIN t ON r.x=t.x",
                "SELECT r.s FROM r JOIN t ON r.x=t.x",
                "SELECT x,r.s,t.s FROM r JOIN t USING (x)",
                "SELECT x FROM r NATURAL JOIN t",
                "SELECT a.x,a.s FROM r a JOIN r b ON a.x=b.x",
                "SELECT a.x,a.s FROM r a JOIN r b ON a.x=b.x WHERE a.y=1 AND b.s='b'",
                "SELECT r.x,t.x FROM r CROSS JOIN t",
                "SELECT 1 FROM r WHERE x=y",
                "SELECT EXISTS(SELECT x FROM r WHERE x IS NULL)",
                "SELECT EXISTS(SELECT r.x FROM r JOIN t ON r.x=t.x WHERE r.b IS TRUE)",
                "SELECT NULL::bigint, TRUE, DATE '2024-02-29', 'x'::text",
                "SELECT 1 WHERE FALSE"):
        add(sql)
    for scale in (0, 38):
        add("SELECT n FROM r", scale)
        add("SELECT r.n FROM r JOIN t ON r.n=t.n", scale)
        add("SELECT DISTINCT n FROM r", scale)
    for kind, value in (("int64", 1), ("int64", None), ("string", "a"), ("string", None), ("boolean", False)):
        name = {"int64": "bigint", "string": "text", "boolean": "boolean"}[kind]
        field = {"int64": "x", "string": "s", "boolean": "b"}[kind]
        add(f"SELECT {field}, $1::{name} FROM r WHERE {field}=$1", parameters=[value],
            parameter_columns=[column("p", kind)])
    if engine == "postgres":
        for sql in ("SELECT NULL", "SELECT NULL,NULL FROM r", "SELECT DISTINCT NULL FROM r"):
            add(sql)
        for sql in ("SELECT n FROM r", "SELECT DISTINCT n FROM r", "SELECT r.n FROM r JOIN t ON r.n=t.n"):
            add(sql, 38, generic=True)
    return result


def type_sql(col, engine):
    kind = col["type"]
    if kind == "decimal":
        spec = col.get("decimal")
        return f"DECIMAL(38,{spec['scale']})" if spec else "NUMERIC"
    if kind == "string":
        return 'TEXT COLLATE "C"' if engine == "postgres" else "VARCHAR"
    return {"int64": "BIGINT", "bool": "BOOLEAN", "date": "DATE"}[kind]


def ddl(case, engine):
    return [f"CREATE TABLE {table['name']} (" + ",".join(
        f"{col['name']} {type_sql(col, engine)}" for col in table["columns"]) + ")"
        for table in case["catalog"]["tables"]]


def states(case):
    state = [{}, {}]
    yield [[], []]
    for update in case["updates"]:
        table, row = update["table"], update["values"]
        before = state[table].get(key(row), (row, 0))[1]
        assert before == update["before"]
        state[table][key(row)] = (row, update["after"])
        yield [[row for row, weight in source.values() for _ in range(weight)] for source in state]


def duckdb_trace(case):
    import duckdb  # Required: no install, skip, or fallback.
    connection = duckdb.connect(":memory:")
    try:
        assert connection.execute("SELECT current_setting('default_collation')").fetchone() == ("",)
        for statement in ddl(case, "duckdb"):
            connection.execute(statement)
        trace, types = [], None
        for state in states(case):
            for table, rows in zip(case["catalog"]["tables"], state):
                connection.execute(f"DELETE FROM {table['name']}")
                if rows:
                    connection.executemany(f"INSERT INTO {table['name']} VALUES (?,?,?,?,?,?)",
                                           [[parameter(value) for value in row] for row in rows])
            query = connection.execute(case["sql"], [parameter(value) for value in case.get("parameters", [])])
            types = [type_info(str(col[1])) for col in query.description]
            trace.append(Counter(key([canonical(value) for value in row]) for row in query.fetchall()))
        return types, trace
    finally:
        connection.close()


def literal(value):
    if value is None:
        return "NULL"
    if type(value) is bool:
        return "TRUE" if value else "FALSE"
    if type(value) is int:
        return str(value)
    if isinstance(value, dict):
        tag = "date" if "date" in value else "decimal"
        return "'" + value[tag] + "'::" + ("DATE" if tag == "date" else "NUMERIC")
    return "'" + value.replace("'", "''") + "'"


def pg_value(value, kind):
    if value is None:
        return None
    if kind in (1, 2):
        return int(value)
    if kind == 4:
        assert value in ("true", "false")
        return value == "true"
    if kind == 5:
        return {"date": value}
    if kind == 6:
        return canonical(Decimal(value))
    return value


class Postgres:
    def __init__(self, binaries):
        self.bin = Path(binaries).resolve()
        self.root = Path(tempfile.mkdtemp(prefix="crown-w05-pg-"))
        self.data, self.socket = self.root / "data", self.root / "socket"
        self.socket.mkdir(mode=0o700)

    def run(self, command, **options):
        result = subprocess.run(command, text=True, capture_output=True, timeout=60, **options)
        if result.returncode:
            raise RuntimeError(f"{Path(command[0]).name} exited {result.returncode}: {result.stderr}")
        return result.stdout

    def start(self):
        share = self.bin.parents[3] / "share/postgresql/16"
        self.run([str(self.bin / "initdb"), "-D", str(self.data), "-L", str(share), "--encoding=UTF8",
                  "--no-locale", "--username=w05oracle", "--auth-local=trust", "--auth-host=reject", "--no-instructions"])
        with (self.data / "postgresql.conf").open("a") as out:
            out.write(f"\nlisten_addresses=''\nunix_socket_directories='{self.socket}'\nport=55441\n"
                      "shared_buffers='16MB'\nmax_connections=10\nfsync=off\nstandard_conforming_strings=on\n")
        self.run([str(self.bin / "pg_ctl"), "-D", str(self.data), "-l", str(self.root / "server.log"), "-w", "-t", "20", "start"])
        settings = json.loads(self.sql("SELECT json_build_array(current_setting('server_encoding'),"
                                      "(SELECT datcollate FROM pg_database WHERE datname=current_database()),current_setting('listen_addresses'),"
                                      "current_setting('standard_conforming_strings'));\n"))
        assert settings == ["UTF8", "C", "", "on"]

    def sql(self, text, csv_output=False):
        formatting = ["--csv"] if csv_output else ["--no-align", "--tuples-only"]
        return self.run([str(self.bin / "psql"), "--no-psqlrc", *formatting, "--quiet",
                         "--set=ON_ERROR_STOP=1", "--host", str(self.socket), "--port", "55441",
                         "--username", "w05oracle", "--dbname", "postgres"], input=text)

    def trace(self, case):
        sql = case["sql"]
        parameters = case.get("parameters", [])
        # Fixture SQL uses placeholders only as expressions, never in quotes.
        sql = re.sub(r"\$(\d+)", lambda match: literal(parameters[int(match[1]) - 1]), sql)
        self.sql(";\n".join(["DROP TABLE IF EXISTS r,t", *ddl(case, "postgres")]) + ";\n")
        # Describe the complete SQL result independently of native arity. A
        # shorter alias list would let a native dropped-column bug escape.
        description = list(csv.reader(StringIO(self.sql(sql + "\n\\gdesc\n", csv_output=True))))
        assert description[0] == ["Column", "Type"]
        actual_types = [type_info(item[1]) for item in description[1:]]
        names = [f"c{i}" for i in range(len(actual_types))]
        source = f"({sql}) AS q(" + ",".join(names) + ")"
        script = []
        fields = ",".join(f"{name}::text" for name in names)
        for index, state in enumerate(states(case)):
            script.append("TRUNCATE r,t")
            for table, rows in zip(case["catalog"]["tables"], state):
                if rows:
                    script.append(f"INSERT INTO {table['name']} VALUES " + ",".join(
                        "(" + ",".join(literal(value) for value in row) + ")" for row in rows))
            script.append(f"SELECT json_build_object('snapshot',{index},'rows',"
                          f"COALESCE(json_agg(json_build_array({fields})),'[]'::json)) FROM {source}")
        observed = [json.loads(line) for line in self.sql(";\n".join(script) + ";\n").splitlines()]
        assert [item["snapshot"] for item in observed] == list(range(len(observed)))
        return actual_types, [Counter(key([pg_value(value, info["kind"]) for value, info in zip(row, actual_types)])
                                     for row in item["rows"]) for item in observed]

    def close(self):
        # A timed-out start can still have created a server; probe its own data
        # directory rather than assuming started=False means no server exists.
        if (self.data / "postmaster.pid").exists():
            self.run([str(self.bin / "pg_ctl"), "-D", str(self.data), "-m", "immediate", "-w", "-t", "20", "stop"])
        assert not (self.data / "postmaster.pid").exists()
        assert not list(self.socket.glob(".s.PGSQL.*"))
        # Preserve this private directory if shutdown fails, for inspection.
        shutil.rmtree(self.root)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--driver", required=True)
    parser.add_argument("--engine", choices=("duckdb", "postgres"), default="duckdb")
    parser.add_argument("--postgres-bin")
    args = parser.parse_args()
    suite = cases(args.engine)
    requests = [dict(case, id=f"{case['id']}/{backend}", indexed=backend) for case in suite for backend in (False, True)]
    run = subprocess.run([args.driver], input="\n".join(json.dumps(item) for item in requests) + "\n",
                         text=True, capture_output=True, timeout=600)
    assert run.returncode == 0, ("native driver", run.stderr, len(run.stdout.splitlines()))
    native = [json.loads(line) for line in run.stdout.splitlines()]
    assert len(native) == len(requests)
    postgres = Postgres(args.postgres_bin) if args.engine == "postgres" and args.postgres_bin else None
    assert args.engine != "postgres" or postgres, "--postgres-bin is required; no engine fallback"
    snapshots = 0
    try:
        if postgres:
            postgres.start()
        for index, case in enumerate(suite):
            types = [{"kind": item["kind"], "decimal": item["decimal"]} for item in native[2 * index]["types"]]
            engine_types, expected = postgres.trace(case) if postgres else duckdb_trace(case)
            assert types == engine_types, (case["id"], "SQL type mismatch", types, engine_types)
            for backend in (0, 1):
                observed = native[2 * index + backend]
                assert len(observed["trace"]) == len(expected)
                assert [{"kind": item["kind"], "decimal": item["decimal"]} for item in observed["types"]] == engine_types
                for sequence, (actual, reference) in enumerate(zip(observed["trace"], expected)):
                    assert actual["sequence"] == sequence
                    assert all(type(item["weight"]) is int and item["weight"] > 0 for item in actual["rows"])
                    compressed = {key(item["values"]): item["weight"] for item in actual["rows"]}
                    assert len(compressed) == len(actual["rows"]), "native output was not compressed"
                    assert compressed == dict(reference), (case["id"], backend, sequence, case["sql"], compressed, reference)
                    snapshots += 1
        version = postgres.sql("SHOW server_version;\n").strip() if postgres else __import__("duckdb").__version__
    finally:
        if postgres:
            postgres.close()
    print(json.dumps({"engine": args.engine, "version": version, "seed": SEED,
                      "cases": len(suite), "native_cases": len(requests), "compared_snapshots": snapshots,
                      "expanded_small_bags": True, "private_postgres_stopped": bool(postgres)}))


if __name__ == "__main__":
    main()
