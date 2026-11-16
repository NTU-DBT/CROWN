#!/usr/bin/env python3
"""Strict logical support diagnostics and independent manual state checks."""
from __future__ import annotations

import copy
import json
import subprocess
import sys
import tempfile
from pathlib import Path


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def key(values: object) -> str:
    return json.dumps(values, sort_keys=True, ensure_ascii=False, separators=(",", ":"))


def memberships(state: dict) -> set[tuple[int, str, str]]:
    result = set()
    for node in state["nodes"]:
        for record in node["records"]:
            result.add((node["id"], "records", key(record["values"])))
        for row in node["survivors"]:
            result.add((node["id"], "survivors", key(row)))
        for role, field in (("parent_support", "parent_keys"), ("visible", "visible_keys")):
            for row in node[field] or []:
                result.add((node["id"], role, key(row["key"])))
    return result


def canonical_state(state: dict) -> dict:
    result = copy.deepcopy(state)
    for node in result["nodes"]:
        for field in ("records", "parent_keys", "visible_keys"):
            for value in node[field] or []:
                value.pop("handle")
    return result


def main() -> None:
    require(len(sys.argv) == 3, "usage: support.py EXECUTABLE REPOSITORY")
    executable = str(Path(sys.argv[1]).resolve())
    root = Path(sys.argv[2]).resolve()
    manifest = json.loads((root / "tests/runtime/support/manifest.json").read_text())
    checks = events = 0

    def invoke(arguments: list[str], code: int = 0, error: str | None = None) -> dict:
        nonlocal checks
        result = subprocess.run([executable, *arguments], capture_output=True, text=True, timeout=60)
        require(result.returncode == code, f"{arguments[0]} exit {result.returncode}: {result.stderr} {result.stdout[:200]}")
        if error:
            require(not result.stdout and json.loads(result.stderr)["error"]["code"] == error, f"wrong trace error: {result.stderr}")
            checks += 1
            return json.loads(result.stderr)
        require(not result.stderr, f"unexpected stderr: {result.stderr}")
        checks += 1
        return json.loads(result.stdout)

    with tempfile.TemporaryDirectory(prefix="crown-support-cli-") as directory:
        plan_path, trace_path = (Path(directory) / name for name in ("plan.json", "trace.json"))
        first_plan = first_trace = None
        for case in manifest["cases"]:
            plan = invoke(["lower-plan", str(root / case["query"]), str(root / case["tree"])])
            plan_path.write_text(json.dumps(plan, ensure_ascii=False))
            trace = {"schema_version": 1, "options": {"capture_transitions": True},
                     "updates": [{name: value for name, value in event.items() if name != "expected"} for event in case["events"]]}
            trace_path.write_text(json.dumps(trace))
            report = invoke(["support-trace", str(plan_path), str(trace_path)])
            require(report["status"] == "complete" and len(report["epochs"]) == len(case["events"]), "trace did not complete")
            require(report["schema_version"] == 2 and report["backend"] == "reference_incremental_journal" and report["update_contract"] == "logical_native_set", "mislabelled runtime contract")
            before = report["initial"]
            handles = {}
            for expected, epoch in zip(case["events"], report["epochs"]):
                effect, state = epoch["effect"], epoch["state"]
                require(state["sequence"] == expected["sequence"] and effect["native_changed"] == expected["expected"]["native_changed"], "logical sequence/no-op mismatch")
                require(state["has_answer"] == expected["expected"]["has_answer"], "root support truth differs from manual expectation")
                nodes = {node["node"]: node for node in state["nodes"]}
                for label, wanted in expected["expected"]["nodes"].items():
                    actual = nodes[label]
                    require(len(actual["records"]) == wanted["records"] and len(actual["survivors"]) == wanted["survivors"], "manual node cardinality mismatch")
                    for field in ("parent_keys", "visible_keys"):
                        if wanted[field] is None:
                            require(actual[field] is None, "hidden node acquired an E relation")
                        else:
                            require(actual[field] is not None and {key(item["key"]): item["support"] for item in actual[field]} ==
                                    {key(item["key"]): item["support"] for item in wanted[field]}, "manual exact projection counts differ")
                old, current = memberships(before), memberships(state)
                transitions = [(event["handle"]["node"], event["handle"]["role"], key(event["values"]), event["operation"]) for event in effect["transitions"]]
                wanted_events = {(*member, "insert") for member in current - old} | {(*member, "erase") for member in old - current}
                require(len(transitions) == len(set(transitions)) and set(transitions) == wanted_events, "local events are not exact membership zero crossings")
                metrics = effect["metrics"]
                for metric in ("copied_rows", "copied_index_memberships", "copied_metadata_entries", "copied_child_flags"):
                    require(metrics[metric] == 0, f"deprecated full-copy metric {metric} was nonzero")
                if effect["native_changed"]:
                    journal = effect["journal"]
                    require(journal is not None and journal["sequence"] == expected["sequence"] and journal["records"], "real update omitted its retained journal")
                    require(metrics["storage_changes"] > 0 and metrics["journal_records"] == len(journal["records"]) > 0,
                            "real update omitted storage or journal-record accounting")
                    require([record["ordinal"] for record in journal["records"]] == list(range(1, len(journal["records"]) + 1)),
                            "journal record ordinals are not contiguous")
                    require(metrics["events_enqueued"] == metrics["events_applied"] == len(journal["events"]),
                            "captured event count differs from enqueue/application accounting")
                    event_ids = {event["id"] for event in journal["events"]}
                    require(event_ids == set(range(1, metrics["events_enqueued"] + 1)), "journal event IDs are not contiguous within the update")
                    require(all(((event["id"] == 1 and event["cause"] == 0) or
                                 (1 <= event["cause"] < event["id"])) and event["sequence"] == expected["sequence"]
                                for event in journal["events"]),
                            "propagation event has an invalid causal parent or sequence")
                    require(sorted(event["applied_ordinal"] for event in journal["events"]) == list(range(1, metrics["events_applied"] + 1)),
                            "applied event ordinals are not a complete permutation")
                    require(all(record["cause"] in event_ids for record in journal["records"]), "journal record refers to a missing causal event")
                    require(all(transition["cause"] in event_ids for transition in effect["transitions"]), "membership transition refers to a missing causal event")
                    require(journal["events"][0]["kind"] == "native_update" and journal["events"][0]["cause"] == 0,
                            "journal does not begin with the native update event")
                else:
                    require(effect["journal"] is None and all(value == 0 for value in metrics.values()) and not transitions,
                            "no-op performed hidden work")
                current_handles = {}
                for node in state["nodes"]:
                    for field in ("parent_keys", "visible_keys"):
                        for item in node[field] or []:
                            identity = (node["id"], field, key(item["key"]))
                            current_handles[identity] = item["handle"]
                            if identity in handles:
                                require(handles[identity] == item["handle"], "positive projection support lost its stable handle")
                handles = current_handles
                before = state
                events += 1
            require(report["final"] == before and not report["final"]["has_answer"], "manual trace cleanup left support")
            trace["options"]["order"] = "lifo"
            trace["options"]["capture_transitions"] = False
            trace_path.write_text(json.dumps(trace))
            alternate = invoke(["support-trace", str(plan_path), str(trace_path)])
            require(alternate["options"]["capture_transitions"] is False and all(
                epoch["effect"]["transitions"] == [] and
                (epoch["effect"]["journal"] is None or epoch["effect"]["journal"]["events"] == [])
                for epoch in alternate["epochs"]), "disabled transition capture retained events")
            for epoch in alternate["epochs"]:
                effect = epoch["effect"]
                if effect["native_changed"]:
                    journal, metrics = effect["journal"], effect["metrics"]
                    require(journal is not None and metrics["journal_records"] == len(journal["records"]) > 0 and
                            metrics["events_enqueued"] == metrics["events_applied"] > 0,
                            "disabled event capture dropped retained journal/accounting")
                    require(all(1 <= record["cause"] <= metrics["events_enqueued"] for record in journal["records"]),
                            "uncaptured journal record has an invalid event cause")
            require([canonical_state(epoch["state"]) for epoch in alternate["epochs"]] == [canonical_state(epoch["state"]) for epoch in report["epochs"]], "FIFO/LIFO canonical states differ")
            if first_plan is None:
                first_plan, first_trace = plan, trace
        require(first_plan is not None and first_trace is not None, "missing support trace corpus")
        plan_path.write_text(json.dumps(first_plan))

        def reject(change: object, code: str) -> None:
            bad = copy.deepcopy(first_trace)
            change(bad)
            trace_path.write_text(json.dumps(bad))
            invoke(["support-trace", str(plan_path), str(trace_path)], 2, code)

        reject(lambda value: value.update(schema_version=2), "unsupported_version")
        reject(lambda value: value["updates"][0].update(sequence=2), "invalid_sequence")
        reject(lambda value: value["updates"][0].update(node="missing"), "invalid_native_update")
        reject(lambda value: value["updates"][0].update(operation="replace"), "invalid_native_update")
        reject(lambda value: value["updates"][0].update(values=[]), "invalid_tuple")
        reject(lambda value: value["options"].update(support_limit=0), "invalid_options")
        reject(lambda value: value["options"].update(order="random"), "invalid_options")
        reject(lambda value: value["options"].update(capture_transitions=1), "invalid_document")
        reject(lambda value: value["options"].update(ignored_future_option=True), "invalid_document")
        trace_path.write_text('{"schema_version":1,"schema_version":1,"updates":[]}')
        invoke(["support-trace", str(plan_path), str(trace_path)], 2, "invalid_document")
        for options, stopped in (({"support_limit": 1}, 5), ({"work_limit": 0}, 1)):
            trace = copy.deepcopy(first_trace)
            trace["options"].update(options)
            trace_path.write_text(json.dumps(trace))
            report = invoke(["support-trace", str(plan_path), str(trace_path)], 1)
            require(report["status"] == "update_rejected" and report["rejected_sequence"] == stopped and len(report["epochs"]) == stopped - 1,
                    "capped update did not stop at its expected boundary")
            prior = report["initial"] if not report["epochs"] else report["epochs"][-1]["state"]
            require(report["final"] == prior and report["final"]["sequence"] == stopped - 1, "rejected update changed the prior diagnostic state")
        for query, tree, truth in (("tests/structural/plans/queries/empty_body.cq.json", "tests/structural/plans/trees/empty_body.tree.json", True),
                                   ("tests/structural/lowering/queries/constant_false.cq.json", "tests/structural/plans/trees/empty_body.tree.json", False)):
            plan = invoke(["lower-plan", str(root / query), str(root / tree)])
            plan_path.write_text(json.dumps(plan))
            trace_path.write_text(json.dumps({"schema_version": 1, "updates": []}))
            report = invoke(["support-trace", str(plan_path), str(trace_path)])
            require(report["final"]["has_answer"] == truth and not report["final"]["nodes"] and not report["epochs"], "constant operator changed its truth/no-port contract")
    print(f"{checks} support CLI checks and {events} manual logical update states PASS")


if __name__ == "__main__":
    try:
        main()
    except (RuntimeError, ValueError, KeyError, OSError, subprocess.TimeoutExpired) as error:
        print(f"support integration failed: {error}", file=sys.stderr)
        raise SystemExit(1)
