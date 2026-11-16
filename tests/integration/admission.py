#!/usr/bin/env python3
"""Check SQL support, independent structural families and admission evidence."""
from __future__ import annotations

import itertools
import json
import subprocess
import sys
import tempfile
from pathlib import Path

from binding import decode_scalar, read_json, rows_key
from normalization import run_adapters, invoke_core_oracle, map_outputs, run_sqlite


def require(value: bool, message: str) -> None:
    if not value:
        raise RuntimeError(message)


def invoke(executable: str, arguments: list[str], code: int) -> dict:
    process = subprocess.run([executable, *arguments], capture_output=True, text=True, timeout=30)
    require(process.returncode == code, f"{arguments[0]} exit {process.returncode}, expected {code}: {process.stderr}")
    require(not (process.stderr if code in (0, 1) else process.stdout), f"{arguments[0]} wrong output channel")
    return json.loads(process.stdout if code in (0, 1) else process.stderr)


def replay(scopes: list[set[str]], reduction: dict) -> None:
    remaining = {index: set(scope) for index, scope in enumerate(scopes)}
    for step in reduction["witness"]:
        edge = step["edge"]
        require(edge in remaining, "GYO witness uses removed edge")
        if step["kind"] == "remove_private_variable":
            variable = step["variable"]
            require(variable in remaining[edge] and sum(variable in scope for scope in remaining.values()) == 1, "GYO private-variable step invalid")
            remaining[edge].remove(variable)
        elif step["kind"] == "remove_contained_edge":
            anchor = step["anchor"]
            require(anchor != edge and anchor in remaining and remaining[edge] <= remaining[anchor], "GYO containment step invalid")
            del remaining[edge]
        else:
            require(step["kind"] == "remove_empty_edge" and not remaining[edge], "GYO empty-edge step invalid")
            del remaining[edge]
    actual = {edge["edge"]: set(edge["scope"]) for edge in reduction["failed_core"]}
    require(actual == remaining and reduction["acyclic"] == (not remaining), "GYO residual/status mismatch")


def validate(result: dict, expected: str) -> None:
    require(set(result) == {"schema_version", "admission_scope", "admission_status", "phase", "execution_status", "route", "diagnostic", "program", "structure", "work", "limits"}, "admission envelope fields differ")
    require(result["admission_status"] == expected, f"status {result['admission_status']}, expected {expected}: {result['diagnostic']}")
    require(result["schema_version"] == 1 and result["admission_scope"] == "frontend_and_structure" and result["execution_status"] == "not_lowered", "admission exceeded its declared scope")
    if expected == "admitted":
        require(result["phase"] == "complete" and result["diagnostic"] is None and result["route"] is not None, "admitted result incomplete")
    else:
        require(result["route"] is None and isinstance(result["diagnostic"], dict), "rejection incorrectly has a route")
    program, structure = result["program"], result["structure"]
    if program is not None:
        require(program["schema_version"] == 2 and program["admission_status"] == "not_checked", "component normalization contract changed")
        count = len(program["binding"]["occurrences"])
        require(len(program["core"]["query"]["atoms"]) == len(program["core"]["catalog"]["tables"]) == len(program["adapters"]) == count, "mutable occurrence disappeared or phantom head table appeared")
    if structure is not None:
        require(program is not None and structure["height_status"] == "not_checked", "structural analysis claims a height")
        query = program["core"]["query"]
        scopes = [{term["var"] for term in atom["terms"] if "var" in term} for atom in query["atoms"]]
        head = {output["var"] for output in query["head"]}
        require(structure["synthetic_head_edge"] == len(scopes), "wrong synthetic head index")
        replay(scopes, structure["body"])
        replay([*scopes, head], structure["augmented"])
        actual = "cyclic" if not structure["body"]["acyclic"] else "free_connex" if structure["augmented"]["acyclic"] else "acyclic_non_free_connex"
        require(structure["query_class"] == actual, "wrong completed shape class")
        if result["route"] == "free_connex":
            require(actual == "free_connex" and not query["contradiction"], "native route has wrong shape")
        if result["route"] == "constant_empty":
            require(query["contradiction"], "constant-empty route lacks a contradiction")
    if expected == "resource_limit":
        require(structure is None and result["diagnostic"]["code"] == "resource_limit", "resource stop leaked a partial class")


def join_tree_exists(scopes: list[set[int]]) -> bool:
    """Literal spanning trees + running intersection; no GYO reduction."""
    count = len(scopes)
    if count < 2:
        return True
    pairs = list(itertools.combinations(range(count), 2))
    variables = set().union(*scopes)
    for edges in itertools.combinations(pairs, count - 1):
        adjacent = [[] for _ in scopes]
        for left, right in edges:
            adjacent[left].append(right)
            adjacent[right].append(left)

        def reach(allowed: set[int]) -> bool:
            if not allowed:
                return True
            pending = [min(allowed)]
            seen = set(pending)
            for node in pending:
                for child in adjacent[node]:
                    if child in allowed and child not in seen:
                        seen.add(child)
                        pending.append(child)
            return seen == allowed

        if reach(set(range(count))) and all(reach({i for i, scope in enumerate(scopes) if variable in scope}) for variable in variables):
            return True
    return False


def generated_families(executable: str, temporary: Path) -> int:
    bodies = [[], [set()], [{0}], [{0, 1}], [{0, 1}, {1, 2}], [{0, 1}, {1, 2}, {2, 3}],
              [{0, 1}, {1, 2}, {0, 2}], [{0, 1}, {1, 2}, {2, 3}, {3, 0}],
              [{0, 1}, {0, 2}, {0, 3}], [{0, 1, 2}, {1, 2, 3}, {2, 3, 4}],
              [{0, 1, 2}, {1, 2}, {1, 2}], [{0, 1}, {1}, {2, 3}],
              [set(), {0, 1}, {1, 2}], [{0}, {1}, {2}], [{0, 1}, {0, 1}, {0, 1}],
              [{0, 1, 2, 3}, {1, 2}, {1}, {2, 3}]]
    count = 0
    for scopes in bodies:
        variables = sorted(set().union(*scopes)) if scopes else []
        heads = {(), tuple(variables), tuple(variables[::2])}
        if variables:
            heads.add((variables[0], variables[-1]))
        for head in sorted(heads):
            tables, references, conditions = [], {}, []
            for edge, scope in enumerate(scopes):
                columns = []
                for column, variable in enumerate(sorted(scope)):
                    columns.append({"name": f"c{column}", "type": "int64"})
                    reference = f"a{edge}.c{column}"
                    if variable in references:
                        conditions.append(f"{reference}={references[variable]}")
                    else:
                        references[variable] = reference
                tables.append({"name": f"g_{edge}", "columns": columns})
            body = (" FROM " + ",".join(f"g_{i} a{i}" for i in range(len(scopes)))) if scopes else ""
            where = " WHERE " + " AND ".join(conditions) if conditions else ""
            sql = ("SELECT DISTINCT " + ",".join(references[v] for v in head) + body + where if head
                   else "SELECT EXISTS(SELECT 1" + body + where + ")")
            (temporary / "query.sql").write_text(sql, encoding="utf-8")
            (temporary / "catalog.json").write_text(json.dumps({"schema_version": 1, "catalog": {"version": 1, "tables": tables}}), encoding="utf-8")
            expected = "cyclic_body" if not join_tree_exists(scopes) else "admitted" if join_tree_exists([*scopes, set(head)]) else "non_free_connex"
            result = invoke(executable, ["admit-sql", str(temporary / "query.sql"), str(temporary / "catalog.json")], 0 if expected == "admitted" else 1)
            validate(result, expected)
            count += 1
    return count


def main() -> None:
    require(len(sys.argv) == 3, "usage: admission.py EXECUTABLE SOURCE_ROOT")
    executable, root = sys.argv[1], Path(sys.argv[2]).resolve()
    base = root / "tests/frontend/admission"
    manifest = read_json(base / "manifest.json")
    schema = read_json(base / manifest["catalog"])
    data = read_json(base / manifest["data"])
    features, statuses = set(), set()
    sqlite_count = row_count = 0
    with tempfile.TemporaryDirectory(prefix="crown-admission-") as directory:
        temporary = Path(directory)
        for case in manifest["cases"]:
            arguments = ["admit-sql", str(base / case["sql"]), str(base / manifest["catalog"])]
            options = read_json(base / case["options"]) if "options" in case else {}
            if "options" in case:
                arguments.append(str(base / case["options"]))
            result = invoke(executable, arguments, 0 if case["status"] == "admitted" else 1)
            validate(result, case["status"])
            features.update(case["features"])
            statuses.add(result["admission_status"])
            if "code" in case:
                require(result["diagnostic"]["code"] == case["code"], f"{case['name']}: wrong reason {result['diagnostic']}")
            if "phase" in case:
                require(result["phase"] == case["phase"], f"{case['name']}: wrong phase")
            if "route" in case:
                require(result["route"] == case["route"], f"{case['name']}: wrong route")
            if case["name"] == "ambiguous_unicode":
                source = (base / case["sql"]).read_text(encoding="utf-8")
                point = source.index(", y") + 2
                require(result["diagnostic"]["byte_offset"] == len(source[:point].encode("utf-8")) and result["diagnostic"]["character_position"] == point + 1, "Unicode diagnostic coordinates changed")
            if result["program"] is not None:
                path = temporary / "program.json"
                path.write_text(json.dumps(result["program"], ensure_ascii=False), encoding="utf-8")
                budget = result["limits"]["recognition"]["work_limit"]
                imported = invoke(executable, ["admit-normalized", str(path), "unlimited" if budget is None else str(budget)], 0 if case["status"] == "admitted" else 1)
                validate(imported, case["status"])
                require(imported["structure"] == result["structure"], "source and artifact admission disagree")
            if "rows" not in case:
                continue
            program = result["program"]
            parameters = [decode_scalar(value) for value in options.get("parameter_values", [])]
            adapted = run_adapters(program, data, parameters, case["name"])
            rows = map_outputs(program, invoke_core_oracle(executable, program["core"], adapted, case["name"]), case["name"])
            expected = [[decode_scalar(value) for value in row] for row in case["rows"]]
            require(rows_key([tuple(row) for row in rows]) == rows_key([tuple(row) for row in expected]), f"{case['name']}: normalized SQL rows differ from manual expectation")
            row_count += 1
            if case.get("sqlite"):
                source = (base / case["sql"]).read_text(encoding="utf-8")
                oracle, _ = run_sqlite(case, source, schema, data, parameters, program["binding"], program, case["name"])
                require(rows_key([tuple(row) for row in oracle]) == rows_key([tuple(row) for row in expected]), f"{case['name']}: SQLite and manual rows disagree")
                sqlite_count += 1
        generated = generated_families(executable, temporary)
        for name, arguments, code in [
            ("usage", ["admit-sql"], "usage"),
            ("missing_sql", ["admit-sql", str(temporary / "absent.sql"), str(base / "catalog.json")], "io_error"),
        ]:
            require(invoke(executable, arguments, 2)["error"]["code"] == code, f"{name}: wrong CLI diagnostic")
        for config, code in [({"schema_version": 2}, "unsupported_version"), ({"schema_version": 1, "extra": 1}, "invalid_document"), ({"schema_version": 1, "limits": {"recognition": {"work_limit": 0.5}}}, "invalid_document")]:
            (temporary / "options.json").write_text(json.dumps(config), encoding="utf-8")
            require(invoke(executable, ["admit-sql", str(base / "cases/singleton.sql"), str(base / "catalog.json"), str(temporary / "options.json")], 2)["error"]["code"] == code, "invalid options accepted")
        for frozen in ("normalized-v1.json", "normalized-v1-fixed-head.json"):
            path = root / "tests/frontend/schema" / frozen
            validate(invoke(executable, ["admit-normalized", str(path)], 0), "admitted")
            upgraded = invoke(executable, ["upgrade-normalized", str(path), "2"], 0)
            require(upgraded["schema_version"] == 2, "explicit normalized upgrade failed")
            (temporary / "program.json").write_text(json.dumps(upgraded), encoding="utf-8")
            require(invoke(executable, ["upgrade-normalized", str(temporary / "program.json"), "1"], 2)["error"]["code"] == "unsupported_version", "normalized downgrade accepted")
        (temporary / "program.json").write_text('{"schema_version":999}', encoding="utf-8")
        require(invoke(executable, ["admit-normalized", str(temporary / "program.json")], 2)["error"]["code"] in ("unsupported_version", "invalid_document"), "malformed artifact received admission")
    require(features == set(manifest["required_features"]), "support matrix feature coverage incomplete")
    require(statuses == {"admitted", "syntax_error", "semantic_error", "unsupported_semantics", "cyclic_body", "non_free_connex", "resource_limit"}, "admission categories not all exercised")
    print(f"{len(manifest['cases'])} SQL admission cases, {len(features)} feature groups, {generated} independent join-tree families, {row_count} manual row checks and {sqlite_count} SQLite checks passed")


if __name__ == "__main__":
    try:
        main()
    except (RuntimeError, ValueError, OSError, subprocess.TimeoutExpired) as error:
        print(f"admission fixture failure: {error}", file=sys.stderr)
        raise SystemExit(1)
