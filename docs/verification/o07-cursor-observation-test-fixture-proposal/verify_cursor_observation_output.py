#!/usr/bin/env python3
"""Offline structural checker for output emitted by cursor_observation_test.cpp."""

from __future__ import annotations

import json
import pathlib
import sys


PACKAGE_SHA256 = "5dcd916bda78bbe1bef6047a65b4a1fa7ef6ad405ee54877c8033b818d3b8259"
CURSOR_NAMES = [
    "cursor.startup_ns",
    "cursor.successful_next_ns",
    "cursor.exhausted_next_ns",
    "cursor.failed_next_ns",
    "cursor.cleanup_ns",
    "cursor.successful_calls",
    "cursor.exhausted_calls",
    "cursor.failed_calls",
    "cursor.cancel_calls",
    "cursor.cleanup_calls",
    "cursor.clock_reads",
    "cursor.clock_regressions",
]
CURSOR_SOURCES = {
    "committed_results",
    "epoch_visible",
    "epoch_witnesses",
    "epoch_keys",
    "epoch_bucket",
}
CURSOR_STATES = {"active", "exhausted", "cancelled", "failed"}
TERMINAL_REASONS = {
    "not_recorded",
    "none",
    "exhausted",
    "explicit_cancel",
    "destruction",
    "move_replacement",
    "invalidated",
    "startup_failure",
    "next_failure",
}
AVAILABILITY = {"unavailable", "disabled", "available"}
UNAVAILABLE_GAUGES = {
    "full_result_count",
    "allocated_bytes",
    "live_bytes",
    "checkpoint_bytes",
    "checkpoint_ns",
    "recovery_replay_length",
}


def fail(message: str) -> None:
    raise ValueError(message)


def require(condition: bool, message: str) -> None:
    if not condition:
        fail(message)


def integer(value: object, label: str) -> None:
    require(type(value) is int and value >= 0, f"{label} must be a nonnegative integer")


def check_metric(metric: object, label: str) -> None:
    require(isinstance(metric, dict), f"{label} must be an object")
    availability = metric.get("availability")
    require(availability in AVAILABILITY, f"{label} has an unknown availability")
    value = metric.get("value")
    saturated = metric.get("saturated")
    if availability == "available":
        integer(value, f"{label}.value")
        require(type(saturated) is bool, f"{label}.saturated must be boolean")
    else:
        require(value is None and saturated is None,
                f"{label} must keep disabled/unavailable values explicitly null")


def check_work(work: object, label: str) -> None:
    require(isinstance(work, dict), f"{label} must be an object")
    required = {
        "work", "calls", "route_checks", "descriptor_steps", "frame_initializations",
        "cursor_opens", "cursor_advances", "frame_closes", "tuple_lookups",
        "selected_rows", "bucket_lookups", "key_fields", "equality_checks",
        "output_fields", "rows_emitted", "binding_checks", "binding_rejections",
        "direct_lookups", "overlay_rows", "fragment_steps", "binding_values",
        "witness_probes", "witness_rows", "join_rejections",
    }
    require(required <= work.keys(), f"{label} omits mandatory work fields")
    for key in required:
        integer(work[key], f"{label}.{key}")


def check_cursor(report: object, label: str) -> None:
    require(isinstance(report, dict), f"{label} report must be an object")
    require(report.get("format") == "crown_cursor_observation" and report.get("version") == 1,
            f"{label} has an unknown cursor report format/version")
    require(report.get("scope") == "one_cursor_lifetime_not_delta_output_spooling",
            f"{label} scope is mislabeled")
    integer(report.get("owner"), f"{label}.owner")
    integer(report.get("sequence"), f"{label}.sequence")
    require(report.get("source") in CURSOR_SOURCES, f"{label} has an unknown cursor source")
    require(report.get("view") in {"core", "sql"}, f"{label} has an unknown result view")
    require(report.get("side") in {None, "before", "after"}, f"{label} has an unknown side")
    require(type(report.get("constructed")) is bool, f"{label}.constructed must be boolean")
    require(type(report.get("tentative_at_creation")) is bool,
            f"{label}.tentative_at_creation must be boolean")
    require(report.get("state") in CURSOR_STATES, f"{label} has an unknown cursor state")
    require(report.get("terminal_reason") in TERMINAL_REASONS,
            f"{label} has an unknown terminal reason")
    options = report.get("observation_options")
    require(isinstance(options, dict) and options.get("mode") in {"off", "counters", "timed", "trace"},
            f"{label} omits its observation options")
    metrics = report.get("metrics")
    require(isinstance(metrics, list) and len(metrics) == len(CURSOR_NAMES),
            f"{label} metric registry length differs from cursor v1")
    for expected_id, expected_name in enumerate(CURSOR_NAMES):
        entry = metrics[expected_id]
        require(isinstance(entry, dict), f"{label} metric descriptor is not an object")
        require(entry.get("id") == expected_id and entry.get("name") == expected_name,
                f"{label} metric IDs/names differ from literal cursor v1 registry")
        require(entry.get("unit") == ("nanoseconds" if expected_id < 5 else "count"),
                f"{label}.{expected_name} has the wrong unit")
        require(entry.get("kind") == ("timing" if expected_id < 5 else "counter"),
                f"{label}.{expected_name} has the wrong metric kind")
        require(isinstance(entry.get("scope"), str) and entry["scope"],
                f"{label}.{expected_name} omits its accounting scope")
        check_metric(entry.get("measurement"), f"{label}.{expected_name}")

    if options["mode"] == "off":
        require(report.get("cursor_id") is None and report.get("cursor_id_saturated") is None,
                f"{label} off mode exposes a recorded cursor identity")
        require(report.get("configuration") is None,
                f"{label} off mode exposes a delta configuration")
        require(all(entry["measurement"]["availability"] == "disabled" for entry in metrics),
                f"{label} off mode did not mark every optional metric disabled")
    else:
        integer(report.get("cursor_id"), f"{label}.cursor_id")
        require(type(report.get("cursor_id_saturated")) is bool,
                f"{label}.cursor_id_saturated must be boolean")

    configuration = report.get("configuration")
    if configuration is not None:
        require(isinstance(configuration, dict), f"{label}.configuration must be object or null")
        require(configuration.get("provenance") == "cursor_begin_runtime_configuration",
                f"{label} configuration provenance is mislabeled")
        require(configuration.get("owner") == report["owner"],
                f"{label} configuration owner differs from its cursor owner")
        integer(configuration.get("generation"), f"{label}.configuration.generation")
        require(type(configuration.get("generation_saturated")) is bool,
                f"{label}.configuration.generation_saturated must be boolean")
        require(configuration.get("mode") in {"maintenance", "delta"},
                f"{label} configuration has an unknown mode")
        require(configuration.get("completion") in {"automatic", "ordered_replay", "anchored", "root_first"},
                f"{label} configuration has an unknown completion")
        integer(configuration.get("query_factors"), f"{label}.configuration.query_factors")
        requested = configuration.get("requested_options")
        require(isinstance(requested, dict), f"{label} configuration omitted requested options")
        nested = requested.get("observation")
        require(isinstance(nested, dict) and nested.get("mode") == options["mode"],
                f"{label} configuration lost its requested observation mode")

    mandatory = report.get("mandatory")
    require(isinstance(mandatory, dict), f"{label} omitted mandatory cursor work")
    for key in ("total_work", "max_result_work", "cleanup_frames"):
        integer(mandatory.get(key), f"{label}.mandatory.{key}")
    require(mandatory.get("work_unit") == "existing_abstract_cursor_actions",
            f"{label} mandatory work unit is mislabeled")
    require(mandatory.get("last_scope") ==
            "last_active_call_already_in_results_termination_or_failed_not_additive",
            f"{label} last-call scope is mislabeled")
    for key in ("startup", "results", "termination", "failed", "last"):
        check_work(mandatory.get(key), f"{label}.mandatory.{key}")

    if report["terminal_reason"] == "startup_failure":
        require(report["state"] == "failed" and not report["constructed"],
                f"{label} startup failure was represented as a constructed cursor")
        values = {entry["name"]: entry["measurement"] for entry in metrics}
        require(values["cursor.cleanup_ns"]["availability"] == "unavailable" and
                values["cursor.cleanup_calls"]["availability"] == "unavailable",
                f"{label} startup failure invented a separate cleanup measurement")


def check_gauge(report: object, label: str) -> None:
    require(isinstance(report, dict), f"{label} report must be an object")
    require(report.get("format") == "crown_committed_state_gauges" and report.get("version") == 1,
            f"{label} has an unknown gauge format/version")
    integer(report.get("owner"), f"{label}.owner")
    integer(report.get("sequence"), f"{label}.sequence")
    require(report.get("scope") == "explicit_committed_state_read_available_with_telemetry_off",
            f"{label} gauge scope is mislabeled")
    require(report.get("visible_scope") == "per_node_E_factor_assignments_not_full_join_output_count",
            f"{label} conflates per-node factors with full answer cardinality")
    check_metric(report.get("base_tuples"), f"{label}.base_tuples")
    bases = report.get("bases")
    require(isinstance(bases, list), f"{label}.bases must be a list")
    for index, base in enumerate(bases):
        require(isinstance(base, dict), f"{label}.bases[{index}] must be an object")
        integer(base.get("table"), f"{label}.bases[{index}].table")
        integer(base.get("tuples"), f"{label}.bases[{index}].tuples")
    nodes = report.get("nodes")
    require(isinstance(nodes, list), f"{label}.nodes must be a list")
    for index, node in enumerate(nodes):
        require(isinstance(node, dict), f"{label}.nodes[{index}] must be an object")
        for key in ("node", "records", "survivors", "projected_parent_keys"):
            integer(node.get(key), f"{label}.nodes[{index}].{key}")
        require(node.get("kind") in {"native", "generalized"},
                f"{label}.nodes[{index}] has an unknown node kind")
        check_metric(node.get("visible_factor_assignments"),
                     f"{label}.nodes[{index}].visible_factor_assignments")
    for key in UNAVAILABLE_GAUGES:
        metric = report.get(key)
        check_metric(metric, f"{label}.{key}")
        require(metric["availability"] == "unavailable",
                f"{label}.{key} promoted an unsupported total/memory/durable fact")


def main() -> int:
    if len(sys.argv) != 2:
        print(f"usage: {pathlib.Path(sys.argv[0]).name} RUNTIME_OUTPUT.json", file=sys.stderr)
        return 2
    path = pathlib.Path(sys.argv[1])
    try:
        document = json.loads(path.read_text(encoding="utf-8"))
        require(isinstance(document, dict), "top-level output must be an object")
        require(document.get("format") == "o07_cursor_observation_independent_test",
                "unexpected test output format")
        require(document.get("test_revision") == "o07-cursor-observation-test-fixture-proposal",
                "runtime output is not from the corrected literal fixture revision")
        require(document.get("cursor_package_sha256") == PACKAGE_SHA256,
                "runtime output is not bound to the frozen cursor package")
        integer(document.get("checks"), "checks")
        require(document["checks"] > 0, "test program reported no assertions")
        cursors = document.get("cursor_reports")
        gauges = document.get("gauge_reports")
        require(isinstance(cursors, list) and isinstance(gauges, list),
                "cursor/gauge output collections must be arrays")
        for index, item in enumerate(cursors):
            require(isinstance(item, dict) and isinstance(item.get("case"), str) and item["case"],
                    f"cursor_reports[{index}] is missing its case label")
            check_cursor(item.get("report"), item["case"])
        for index, item in enumerate(gauges):
            require(isinstance(item, dict) and isinstance(item.get("case"), str) and item["case"],
                    f"gauge_reports[{index}] is missing its case label")
            check_gauge(item.get("report"), item["case"])
        require(cursors and gauges, "runtime output lacks actual cursor or gauge snapshots")
    except (OSError, UnicodeError, json.JSONDecodeError, ValueError, KeyError) as error:
        print(f"FAIL: {error}", file=sys.stderr)
        return 1
    print(f"PASS: {document['checks']} C++ checks; {len(cursors)} cursor snapshots; "
          f"{len(gauges)} committed-state gauge snapshots")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
