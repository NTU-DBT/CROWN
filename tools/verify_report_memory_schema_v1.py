#!/usr/bin/env python3
"""Check the additive memory-option schema contract against actual native reports.

The original frozen CLI checker/package is read-only. This successor checks
the two added uint64 fields, exact emitted values and negative schema cases.
All schema resolution is restricted to the supplied local schema directories.
"""
import argparse
import copy
import hashlib
import json
from pathlib import Path
import subprocess
import tempfile

from jsonschema import Draft202012Validator
from referencing import Registry, Resource


# Historical failed revision: the maintained CMake gate invokes v2 instead.
MAXIMUM = (1 << 64) - 1
NAMES = ("explain-report-v2.schema.json", "explain-tree-v2.schema.json",
         "query-explain-v1.schema.json", "query-witness-v1.schema.json")
PATHS = (
    ("observations", "current_configuration", "requested_options", "physical", "support", "memory_limit_bytes"),
    ("run_context", "session", "requested_delta", "memory_limit_bytes"),
)


def read(path):
    return json.loads(path.read_text(encoding="utf-8"))


def deny_remote(uri):
    raise RuntimeError("schema reference outside the local corpus: " + uri)


def validator(directory):
    resources = []
    schemas = {}
    for name in NAMES:
        path = directory / name
        schema = read(path)
        Draft202012Validator.check_schema(schema)
        resource = Resource.from_contents(schema)
        resources.append((path.resolve().as_uri(), resource))
        if "$id" in schema:
            resources.append((schema["$id"], resource))
        schemas[name] = schema
    registry = Registry(retrieve=deny_remote).with_resources(resources)
    return Draft202012Validator(schemas[NAMES[0]], registry=registry), schemas[NAMES[0]]


def memory_fields(value, path=()):
    result = {}
    if isinstance(value, dict):
        for key, item in value.items():
            if key == "memory_limit_bytes":
                result[path + (key,)] = item
            result.update(memory_fields(item, path + (key,)))
    elif isinstance(value, list):
        for index, item in enumerate(value):
            result.update(memory_fields(item, path + (index,)))
    return result


def replace(document, path, value):
    result = copy.deepcopy(document)
    parent = result
    for key in path[:-1]:
        parent = parent[key]
    parent[path[-1]] = value
    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--executable", type=Path, required=True)
    parser.add_argument("--repo-root", type=Path, required=True)
    args = parser.parse_args()
    root = args.repo_root.resolve()
    frozen = root / "tests/observability/cli"
    current, schema = validator(root / "schemas")
    legacy, old_schema = validator(frozen / "schemas")
    checks = 0

    def check(condition, message):
        nonlocal checks
        if not condition:
            raise AssertionError(message)
        checks += 1

    # Review the entire transition: only these two optional properties change.
    expected = copy.deepcopy(old_schema)
    word = {"type": "integer", "minimum": 0, "maximum": MAXIMUM}
    expected["$defs"]["flat_delta"]["properties"]["memory_limit_bytes"] = word
    support = expected["$defs"]["p_requested_options"]["properties"]["physical"]["properties"]["support"]
    support["properties"]["memory_limit_bytes"] = copy.deepcopy(word)
    check(expected == schema, "schema transition changed more than the two reviewed uint64 properties")

    readiness = read(frozen / "readiness.json")
    for name, expected_hash in readiness["files"].items():
        check(hashlib.sha256((frozen / name).read_bytes()).hexdigest() == expected_hash,
              "original frozen package changed: " + name)

    corpus = Path(tempfile.mkdtemp(prefix="crown-report-memory-schema-v1-"))
    print("Native memory-report artifacts: " + str(corpus), flush=True)
    result = subprocess.run([str(args.executable.resolve()), str(corpus)],
                            capture_output=True, text=True, check=False)
    (corpus / "driver.stdout.txt").write_text(result.stdout, encoding="utf-8")
    (corpus / "driver.stderr.txt").write_text(result.stderr, encoding="utf-8")
    check(result.returncode == 0, "native account/report fixture failed: " + result.stderr)
    defaults = read(corpus / "default.json")
    check(current.is_valid(defaults), "default report violates current schema")
    check(legacy.is_valid(defaults), "default report lost frozen CLI schema compatibility")
    check(memory_fields(defaults) == {}, "default limit must retain the original omitted-field contract")

    invalid = (-1, 1 << 64, True, "1048699", 1.25, None, [], {})
    for name, limit in (("limited", 1024 * 1024 + 123), ("maximum", MAXIMUM)):
        document = read(corpus / (name + ".json"))
        check(current.is_valid(document), name + " report violates current schema")
        fields = memory_fields(document)
        check(fields == {path: limit for path in PATHS}, name + " report omitted/misplaced/changed an actual account limit")
        check(all(type(value) is int for value in fields.values()), name + " limit lost its integer representation")
        check(not legacy.is_valid(document), "frozen schema silently accepted an added memory option")
        for path in PATHS:
            for value in invalid:
                check(not current.is_valid(replace(document, path, value)),
                      name + " memory field accepted invalid value " + repr(value))
            check(current.is_valid(replace(document, path, 0)), "schema must preserve the uint64 zero boundary")
    print("PASS memory-option schema v1: checks=" + str(checks) + "; original frozen package unchanged")


if __name__ == "__main__":
    main()
