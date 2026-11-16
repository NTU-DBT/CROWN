#!/usr/bin/env python3
"""Validate actual typed P07 reports and strict schema/authority mutations."""
import copy
import json
from pathlib import Path
import subprocess
import sys
import warnings

with warnings.catch_warnings():
    warnings.simplefilter("ignore", DeprecationWarning)
    from jsonschema import Draft202012Validator, RefResolver

# This script executes its producer and checks at import time; do not import as a library.
if len(sys.argv) not in (3, 4):
    raise SystemExit("usage: verify_candidate_reports.py FIXTURE_EXECUTABLE REPOSITORY_ROOT [PROPOSAL_FIXTURE]")
root = Path(sys.argv[2]).resolve()
schema_dir = root / "schemas"
schemas = {p.name: json.loads(p.read_text()) for p in schema_dir.glob("*.schema.json")}
store = {}
for name, schema in schemas.items():
    store[(schema_dir / name).as_uri()] = schema
    if "$id" in schema:
        store[schema["$id"]] = schema

def local_file(uri):
    if uri not in store:
        raise RuntimeError("schema reference outside local set: " + uri)
    return store[uri]

def deny_network(uri):
    raise RuntimeError("schema resolver attempted network access: " + uri)

schema_path = schema_dir / "candidate-report-v1.schema.json"
schema = schemas[schema_path.name]
Draft202012Validator.check_schema(schema)
resolver = RefResolver(schema_path.as_uri(), schema, store=store,
                       handlers={"file": local_file, "http": deny_network, "https": deny_network})
validator = Draft202012Validator(schema, resolver=resolver)
emitted = subprocess.run([str(Path(sys.argv[1]).resolve()), "--emit"],
                         capture_output=True, text=True, timeout=180, check=False)
if emitted.returncode != 0 or emitted.stderr:
    raise RuntimeError("native candidate report fixtures failed: " + emitted.stderr)
records = json.loads(emitted.stdout)
assert isinstance(records, list) and records
names = set()
versions = set()
artifacts = set()
for record in records:
    assert set(record) == {"name", "schema", "document"}
    assert isinstance(record["name"], str) and record["name"] not in names
    names.add(record["name"])
    assert record["schema"] == schema_path.name
    document = record["document"]
    validator.validate(document)
    versions.add(document["query_binding"]["schema_version"])
    artifacts.add(document["artifact"])
    proof = document["original_proof"]["certificate"]
    assert document["original_proof"]["scope"] == "original_query"
    assert proof["query_binding"] == document["query_binding"]
    if document["artifact"] == "minimum_height_candidate":
        assert document["checked_upper"]["height"] == proof["minimum_height"]
        assert document["checked_upper"]["proof_status"] == "checked_upper_only"
    elif document["artifact"] == "candidate_progress":
        assert document["verified_original_height"] == proof["minimum_height"]
    else:
        assert document["candidate_count"] == len(document["prefix"])
        assert all(c["original_proof"] == document["original_proof"] for c in document["prefix"])
assert versions == {1, 2, 3}
assert artifacts == {"minimum_height_candidate", "candidate_progress", "candidate_snapshot"}

def pick(artifact, **fields):
    return next(r["document"] for r in records if r["document"]["artifact"] == artifact
                and all(r["document"].get(k) == v for k, v in fields.items()))

candidate = pick("minimum_height_candidate")
progress = pick("candidate_progress", family_exhausted=False)
snapshot = pick("candidate_snapshot", family_exhausted=True)
mutations = []

def reject(base, path, value):
    mutant = copy.deepcopy(base)
    target = mutant
    for key in path[:-1]:
        target = target[key]
    target[path[-1]] = value
    mutations.append(("/".join(map(str, path)), mutant))

for base in (candidate, progress, snapshot):
    reject(base, ["unexpected"], True)
    reject(base, ["context", "unexpected"], True)
    reject(base, ["original_proof", "unexpected"], True)
    reject(base, ["original_proof", "certificate", "unexpected"], True)
    reject(base, ["original_proof", "scope"], "residual_query")
    reject(base, ["original_proof", "certificate", "minimum_height"], None)
    reject(base, ["original_proof", "certificate", "tree"], None)
    reject(base, ["context", "cost_model"], "globally_cost_optimal")
    reject(base, ["family"], "all_possible_tree_shapes")
    reject(base, ["optimization_scope"], "global_cost")
reject(candidate, ["checked_upper", "proof_status"], "verified_optimum")
reject(candidate, ["checked_upper", "height"], -1)
reject(candidate, ["checked_upper", "tree", "unexpected"], 1)
reject(candidate, ["provenance", "source"], "residual_seed")
reject(candidate, ["provenance", "unexpected"], 1)
reject(candidate, ["structural_key"], 17)
reject(candidate, ["height_relationship"], "cost_optimal")
reject(progress, ["family_exhausted"], True)
reject(progress, ["work", "attempted"], -1)
reject(progress, ["work", "unexpected"], 1)
reject(progress, ["statistics", "unexpected"], 1)
reject(progress, ["limits", "enumeration", "unexpected"], 1)
reject(progress, ["limits", "records"], -1)
reject(progress, ["verified_original_height"], None)
reject(progress, ["report_role"], "proof")
reject(snapshot, ["prefix", 0, "unexpected"], 1)
reject(snapshot, ["candidate_count"], -1)
reject(snapshot, ["exhaustion_scope"], "all_trees")
residual = next(r["document"] for r in records if r["name"] == "residual_distinct")
cached = next(r["document"] for r in records if r["name"] == "cached_residual_distinct")
assert residual["provenance"]["source"] == "residual_seed"
assert residual["provenance"] == cached["provenance"]
assert residual["provenance"]["residual_trace"]["audit_scope"] == "frozen_residual_trace_only"
assert any(r["document"].get("stop_reason") == "record_limit" for r in records)
assert any(r["document"].get("stop_reason") == "allocation_failure" for r in records)
assert any(r["document"].get("phase") == "failed" for r in records)
reject(candidate, ["structural_key"], "")
reject(residual, ["provenance", "residual_last_step"], None)
reject(residual, ["provenance", "residual_trace"], None)
reject(residual, ["provenance", "residual_trace", "audit_scope"], "original_query_exact")
reject(residual, ["provenance", "source"], "normal_form")
failed = pick("candidate_progress", phase="failed")
reject(failed, ["family_exhausted"], True)
for label, mutant in mutations:
    if validator.is_valid(mutant):
        raise AssertionError("schema accepted mutation: " + label)

# The second native producer isolates finite-batch provenance, including both
# EXPLAIN families. Validate actual documents before changing one field at a time.
proposal_count = proposal_mutations = 0
if len(sys.argv) == 4:
    output = subprocess.run([str(Path(sys.argv[3]).resolve()), "--emit"],
                            capture_output=True, text=True, timeout=180, check=False)
    if output.returncode != 0 or output.stderr:
        raise RuntimeError("native proposal reports failed: " + output.stderr)
    explain_name = "explain-report-v2.schema.json"
    explain_schema = schemas[explain_name]
    Draft202012Validator.check_schema(explain_schema)
    explain_validator = Draft202012Validator(explain_schema, resolver=RefResolver(
        (schema_dir / explain_name).as_uri(), explain_schema, store=store,
        handlers={"file": local_file, "http": deny_network, "https": deny_network}))
    validators = {schema_path.name: validator, explain_name: explain_validator}
    proposals = json.loads(output.stdout)
    expected = {"finite_progress", "finite_snapshot", "finite_candidate", "finite_explain", "normal_explain"}
    assert len(proposals) == len(expected) and {r["name"] for r in proposals} == expected
    by_name = {}
    for record in proposals:
        assert set(record) == {"name", "schema", "document"}
        chosen_validator = validators[record["schema"]]
        chosen_validator.validate(record["document"])
        by_name[record["name"]] = (record["document"], chosen_validator)
    proposal_count = len(proposals)

    def reject_proposal(name, path, value):
        global proposal_mutations
        base, chosen_validator = by_name[name]
        mutant = copy.deepcopy(base)
        target = mutant
        for key in path[:-1]:
            target = target[key]
        target[path[-1]] = value
        if chosen_validator.is_valid(mutant):
            raise AssertionError("schema accepted proposal mutation: " + name + "/" + "/".join(map(str, path)))
        proposal_mutations += 1

    normal = "exact-seed/residual-seed/normal-form-v1"
    finite = "finite-proposals-v1"
    old_scope = "admitted_seeds_and_normal_form_v1_only"
    new_scope = "supplied_finite_proposals_v1_only"
    reject_proposal("finite_candidate", ["family"], normal)
    reject_proposal("finite_candidate", ["provenance", "source"], "normal_form")
    for name in ("finite_progress", "finite_snapshot"):
        reject_proposal(name, ["exhaustion_scope"], old_scope)
        reject_proposal(name, ["family"], normal)
    reject_proposal("finite_snapshot", ["prefix", 0, "family"], normal)
    reject_proposal("finite_snapshot", ["prefix", 0, "provenance", "source"], "exact_witness")
    for name, wrong_scope, wrong_source in (("finite_explain", old_scope, "normal_form"),
                                           ("normal_explain", new_scope, "supplied_proposal")):
        reject_proposal(name, ["candidate_family", "exhaustion_scope"], wrong_scope)
        reject_proposal(name, ["selected_candidate", "source"], wrong_source)
    reject_proposal("finite_explain", ["candidate_family", "family"], normal)
    reject_proposal("normal_explain", ["candidate_family", "family"], finite)

print(f"schema_valid_reports={len(records)} strict_mutations_rejected={len(mutations)} "
      f"proposal_reports={proposal_count} proposal_mutations_rejected={proposal_mutations} "
      "CQ_versions=1,2,3 original_proof=separate typed_upper=yes")
