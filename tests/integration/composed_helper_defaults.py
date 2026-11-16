#!/usr/bin/env python3
"""Check standalone composed-checker paths using synthetic transport data.

The fixture exercises closed JSON shape and checker invocation only. Its text
fields are not a native certificate and grant no planner authority.
"""
import argparse
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile


def query_fixture():
    """Supply the checker's structural-negative query transport branch."""
    columns = [{"name": name, "type": "int64", "nullable": False,
                "collation": "binary", "decimal": None} for name in ("x", "y")]
    catalog = {"version": 1, "tables": [
        {"name": name, "source_schema_version": 1, "columns": columns,
         "constraints": [], "statistics": {"row_count": None, "distinct_counts": []},
         "key_hints": []} for name in ("A", "B", "C")]}
    query = {"contradiction": True,
             "variables": [{"name": name, "type": "int64"} for name in ("x", "y", "z")],
             "atoms": [{"occurrence": name, "table": table,
                        "terms": [{"kind": "variable", "variable": variable} for variable in terms]}
                       for table, name, terms in ((0, "a", (0, 1)), (1, "b", (1, 2)), (2, "c", (0, 2)))],
             "head": [{"variable": i, "alias": name} for i, name in enumerate(("x", "y", "z"))]}
    report = {"format": "crown_query_explain", "version": 1,
              "source": "verified_infeasible", "accounting": "continuation_v1",
              "binding": {"catalog": catalog, "query": query},
              "height": {"status": "verified_infeasible", "lower": None, "upper": None,
                         "lower_evidence": "typed_independent_proof", "upper_evidence": "none",
                         "minimum_proven": False, "infeasible_proven": True,
                         "witness_exportable": False},
              "search": None, "replay": None, "witness": None,
              "certificate": {"authority": "typed_independently_checked_original_binding",
                              "algorithm": "synthetic_transport_fixture", "minimum_height": None,
                              "tree": None, "lower_bounds": []},
              "recognized_class": {"status": "not_collected", "diagnostic_work": 0,
                                   "reason": "capture_does_not_run_recognizer_or_reclassify_producer_statistics"},
              "cost": {"status": "not_run", "estimates": None, "statistics": "not_collected",
                       "catalog_estimates": "original_input_metadata_only", "candidate_family_exhaustion": None},
              "active_time_semantics": "producer_recorded_active_time_excludes_pause; UINT64_MAX_may_be_capped_not_exact",
              "proof_scope": "original_structural_height_only; no_cost_optimum_runtime_or_durable_guarantee",
              "structural_domain": "original_CQ_atom_head_tree_family; contradiction_metadata_preserved; excludes_P08_constant_false_operator_shortcut",
              "counter_scopes": "producer_and_replay_attempted_are_separate_phases; structural.work_aliases_producer.attempted; structural.certificate_work_aliases_replay.attempted; transitions_not_additive_work"}
    return {"schema_version": 2, "artifact": "crown_explain", "kind": "query",
            "query_explanation": report}


def check(source):
    """Run defaults and both wrapper path forms from an unrelated directory."""
    checker = source / "tools/support/check_composed_reports.py"
    with tempfile.TemporaryDirectory(prefix="crown-composed-defaults-") as temporary:
        work = Path(temporary)
        corpus = work / "corpus"
        corpus.mkdir()
        (corpus / "structural-negative.query.json").write_text(json.dumps(query_fixture()), encoding="utf-8")
        for options in ([], ["--schema-dir", str(source / "schemas"), "--repo-root", str(source)],
                        ["--schema-dir", "schemas", "--repo-root", str(source)]):
            result = subprocess.run([sys.executable, str(checker), str(corpus), *options], cwd=work,
                                    env={**os.environ, "PYTHONDONTWRITEBYTECODE": "1"},
                                    text=True, capture_output=True, timeout=30)
            assert result.returncode == 0, (options, result.stdout, result.stderr)
            assert result.stdout.strip() == "PASS closed V2 schemas and native semantic sidecars: 1"
    print("PASS composed helper defaults and explicit absolute/relative schema paths")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path)
    check(parser.parse_args().source.resolve())
