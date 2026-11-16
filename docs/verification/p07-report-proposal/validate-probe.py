#!/usr/bin/env python3
"""Validate actual excluded report output and targeted strict-schema mutations."""
import copy
import json
from pathlib import Path
import sys
import warnings

with warnings.catch_warnings():
    warnings.simplefilter("ignore", DeprecationWarning)
    from jsonschema import Draft202012Validator, RefResolver

schema_path = Path(__file__).with_name("candidate-report-v1.schema.json").resolve()
schema = json.loads(schema_path.read_text())
Draft202012Validator.check_schema(schema)
validator = Draft202012Validator(schema, resolver=RefResolver(schema_path.as_uri(), schema))
records = json.loads(Path(sys.argv[1]).read_text())
for record in records:
    validator.validate(record["document"])

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
for label, mutant in mutations:
    if validator.is_valid(mutant):
        raise AssertionError("schema accepted mutation: " + label)
print(f"schema_valid_reports={len(records)} strict_mutations_rejected={len(mutations)} "
      "CQ_versions=1,2,3 proposal_only P07=not_started")
