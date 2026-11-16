#!/usr/bin/env python3
"""Root-only schema, literal-map, transport, and mutation checks. Never imports engine code."""
import argparse
import collections
import copy
import datetime
import decimal
import json
import importlib.metadata
import pathlib
import re
import jsonschema


def pairs(values):
    out = {}
    for key, value in values:
        assert key not in out, ("duplicate JSON key", key)
        out[key] = value
    return out


def read(path):
    return json.loads(path.read_text(encoding="utf-8"), object_pairs_hook=pairs,
                      parse_constant=lambda value: (_ for _ in ()).throw(AssertionError(value)))


def item_count(value):
    if isinstance(value, dict):
        return 1 + sum(item_count(v) for v in value.values())
    if isinstance(value, list):
        return 1 + sum(item_count(v) for v in value)
    return 1


def scalar(value):
    tag, raw = value["type"], value["value"]
    if tag == "string":
        assert value["encoding"] == "hex_bytes" and re.fullmatch(r"(?:[0-9a-f]{2})*", raw)
        return bytes.fromhex(raw)
    assert value["encoding"] == "native_canonical"
    if tag == "int64":
        assert type(raw) is int and -(2**63) <= raw < 2**63
        return raw
    if tag == "bool":
        assert type(raw) is bool
        return raw
    if tag == "date":
        parsed = datetime.date.fromisoformat(raw)
        assert parsed.isoformat() == raw
        return parsed
    assert tag == "decimal"
    parsed = decimal.Decimal(raw)
    canonical = format(parsed, "f")
    if "." in canonical:
        canonical = canonical.rstrip("0").rstrip(".")
    if parsed == 0:
        canonical = "0"
    assert canonical == raw and parsed.is_finite()
    digits = raw.lstrip("-").replace(".", "").lstrip("0") or "0"
    assert len(digits) <= 38
    if "." in raw:
        assert len(raw.split(".")[1]) <= 38
    return parsed


def native_row(value):
    return tuple(scalar(v) for v in value)


def distribution(actual, counts, visited, k):
    assert actual["completion"] == "exact"
    assert actual["visited"] == visited
    assert actual["ndv"] == {"value": len(counts), "reason": None}
    histogram = collections.Counter(counts.values())
    assert actual["histogram"] == [{"multiplicity": n, "positive_keys": keys} for n, keys in sorted(histogram.items())]
    ranked = sorted(counts.items(), key=lambda item: (-item[1], item[0]))[:k]
    assert [(native_row(row["key"]), row["multiplicity"]) for row in actual["top_k"]] == ranked
    assert actual["unknown_reason"] is None


def literal(report, supported):
    physical = {(1, 7, 10), (1, 7, 11), (2, 7, 20), (3, 8, 30)}
    native = collections.Counter((x, y) for x, y, unused in physical)
    source = collections.Counter((y,) for x, y, unused in physical)
    survivors = {key for key in native if key[1] in supported}
    survivor_y = collections.Counter((key[1],) for key in survivors)
    parent = {(): len(survivors)} if survivors else {}
    visible = {key: 1 for key in survivors}
    reverse = collections.Counter((key[1],) for key in native)
    state = report["c01"]["state"]
    assert state["availability"] == "available"
    value = state["value"]
    components = value["components"]
    assert len(components) == value["requested_components"] == 8
    cards = [4, 1, 3, 3, len(survivors), len(parent), len(visible), 2]
    for component, cardinality in zip(components, cards, strict=True):
        assert component["cardinality"] == {"value": cardinality, "reason": None}
    for index, counts, visits in [(0, source, 4), (2, native, 3), (4, survivor_y, len(survivors)),
                                  (5, parent, len(parent)), (6, visible, len(visible)), (7, reverse, 2)]:
        distribution(components[index]["distribution"], counts, visits, value["limits"]["heavy_keys"])
    for index in (1, 3):
        assert components[index]["distribution"] is None
        assert components[index]["distribution_absence_reason"] == "not_requested"
    for index in (5, 6):
        assert sum(x["multiplicity"] * x["positive_keys"] for x in components[index]["distribution"]["histogram"]) == len(survivors)


RATIOS = ("input_share", "events_per_input", "crossing_fraction", "adapter_selectivity")


def semantics(report):
    boundary, mode, observation, c01 = (report[k] for k in ("boundary", "mode", "o07", "c01"))
    assert mode["requested"]["o07"] == observation["options"]
    if observation["options"]["mode"] == "off":
        assert observation["recorded_owner"] is None and observation["counts_status"] == "disabled"
        assert observation["attempts"] is observation["commits"] is observation["aborts"] is None
    else:
        assert observation["recorded_owner"] == boundary["owner"]
    current = observation["current_configuration"]
    if current:
        assert current["owner"] == boundary["owner"] and current["requested"] == mode["requested"]
        for key in ("resolved_mode", "resolved_completion", "live_maintenance", "view"):
            assert current[key] == mode[key]
    for summary in (observation["current"], observation["last"]):
        if summary:
            for metric in summary["metrics"]:
                known = metric["availability"] == "available" and not metric["saturated"]
                assert (metric["fact"]["value"] is not None) == known
                if metric["saturated"]:
                    assert metric["raw_status"] == "lower_bound" and metric["fact"]["reason"] == "saturated"
    state, workload = c01["state"], c01["workload"]
    if boundary["presence"] == "released":
        assert workload["stamp"] is workload["pending"] is workload["value"] is state["value"] is None
        assert workload["availability"] == state["availability"] == "runtime_released"
        assert c01["options_scope"] == "retained_last_configuration_runtime_released"
    else:
        assert workload["stamp"]["owner"] == boundary["owner"]
        assert workload["stamp"]["committed_epoch"] == boundary["committed_sequence"]
        assert workload["pending"] == boundary["pending"]
        if state["value"]:
            assert state["value"]["owner"] == boundary["owner"] and state["value"]["sequence"] == boundary["committed_sequence"]
            assert (state["availability"] == "pending_private_state") == boundary["pending"]
            for dimension in ("work", "rows", "distinct_keys", "accounted_bytes"):
                assert state["value"]["usage"][dimension] <= state["value"]["limits"][dimension]
            for component in state["value"]["components"]:
                d = component["distribution"]
                if d and d["completion"] != "exact":
                    assert d["ndv"]["value"] is d["histogram"] is d["top_k"] is None
                elif d:
                    assert sum(row["positive_keys"] for row in d["histogram"]) == d["ndv"]["value"]
                    multiplicities = [row["multiplicity"] for row in d["histogram"]]
                    assert multiplicities == sorted(set(multiplicities))
                    assert len(d["top_k"]) == min(d["ndv"]["value"], state["value"]["limits"]["heavy_keys"])
                    ordering = [(-key["multiplicity"], native_row(key["key"])) for key in d["top_k"]]
                    assert ordering == sorted(ordering)
                    for key in d["top_k"]:
                        native_row(key["key"])
        if not state["requested"]:
            assert state["value"] is None and state["availability"] == "not_requested"
    if c01["options"]["mode"] == "off":
        assert workload["value"] is None
    value = workload["value"]
    if value:
        assert c01["options"]["offset"] < c01["options"]["period"]
        assert len(value["cells"]) <= c01["options"]["max_cells"]
        memory = value["memory"]
        assert memory["retained_payload_bytes"] == sum(memory[key] for key in ("descriptors_bytes", "routes_bytes", "committed_bytes", "attempt_bytes", "previous_bytes"))
        assert value["modes"]["requested_mode"] == mode["requested"]["mode"]
        assert value["modes"]["requested_completion"] == mode["requested"]["completion"]
        for key in ("resolved_mode", "resolved_completion", "live_maintenance", "view"):
            assert value["modes"][key] == mode[key]
        for i, record in enumerate(value["cells"]):
            assert record["id"] == i
            raw = record["observations"]
            descriptor = record["descriptor"]
            population = "unequal_support_event_after_values" if descriptor["kind"] == "support" else (
                "generalized_pre_probe_presence" if descriptor["role"] == "generalized_probe" else (
                    "directed_child_event_degrees" if descriptor["kind"] == "degree" else (
                        "adapter_route_visits" if descriptor["kind"] == "occurrence" else "committed_input_census")))
            assert raw["population"] == population
            clipped = raw["saturated"] or value["metadata"]["saturated"]
            assert raw["numeric_status"] == ("lower_bound" if clipped else "exact")
            if clipped:
                for ratio in RATIOS:
                    assert record[ratio]["numerator"] is record[ratio]["denominator"] is None
                    assert record[ratio]["availability"] == "unavailable"
            else:
                assert sum(raw["bins"]) == raw["count"]
                if raw["count"] == 0:
                    assert raw["minimum"]["value"] is raw["maximum"]["value"] is None
            for key in RATIOS:
                ratio = record[key]
                assert (ratio["numerator"] is not None) == (ratio["availability"] in ("exact", "sampled"))
        if value["metadata"]["saturated"] or any(x["observations"]["saturated"] for x in value["cells"]):
            assert workload["availability"] == "lower_bound"
    comparison = report["comparison"]
    if comparison:
        assert comparison["actual_owner"] == boundary["owner"] and comparison["actual_sequence"] == boundary["committed_sequence"]
        if boundary["presence"] == "released":
            assert comparison["data"] is None
        elif comparison["previous_owner"] != boundary["owner"]:
            assert comparison["data"] == "foreign_owner"
    if report["session"]:
        assert report["session"]["committed_sequence"] == boundary["committed_sequence"]


def find_cell(report, role, operation="insert", node=None):
    records = report["c01"]["workload"]["value"]["cells"]
    found = [r for r in records if r["descriptor"]["initiating_table"] == 1
             and r["descriptor"]["operation"] == operation and r["descriptor"]["role"] == role
             and r["descriptor"]["node"] == node]
    assert len(found) == 1
    return found[0]


def main():
    args = argparse.ArgumentParser()
    args.add_argument("--schema", type=pathlib.Path, required=True)
    args.add_argument("--fixtures", type=pathlib.Path, required=True)
    args.add_argument("--legacy-baseline", type=pathlib.Path, required=True)
    args.add_argument("--legacy-schema", type=pathlib.Path, required=True)
    args.add_argument("--testing", action="store_true")
    options = args.parse_args()
    schema = read(options.schema)
    jsonschema.Draft202012Validator.check_schema(schema)
    validator = jsonschema.Draft202012Validator(schema, format_checker=jsonschema.FormatChecker())
    legacy = jsonschema.Draft202012Validator(read(options.legacy_schema))
    cases = {}
    for path in sorted(options.fixtures.glob("*.json")):
        document = read(path)
        if path.name.startswith("legacy-"):
            legacy.validate(document)
            assert path.read_bytes() == (options.legacy_baseline / path.name).read_bytes(), ("changed v2 bytes", path.name)
        else:
            validator.validate(document)
            semantics(document)
            human = path.with_suffix(".txt").read_text(encoding="utf-8")
            assert human.startswith("CROWN statistics report v3\n") and human.endswith("\n")
            assert human[human.index("{"):].rstrip("\n") == path.read_text(encoding="utf-8")
            cases[path.stem] = document
    expected = set("off-metadata off-state success noop erased sampled truncated state-exhausted state-zero mode-before mode-after mode-noop reset reconfigured pending prepared unread aborted stale within-lag rebuilt moved session-live session-private session-stopped session-released window-private window-committed hidden-e scalars generalized-events".split())
    if options.testing:
        expected.add("saturated")
    assert set(cases) == expected, (set(cases) - expected, expected - set(cases))
    for label in ("off-state", "unread", "aborted", "stale", "within-lag", "rebuilt", "moved", "session-live", "session-stopped"):
        literal(cases[label], {7})
    for label in ("success", "noop", "sampled", "truncated", "mode-before", "mode-after", "mode-noop", "reset", "reconfigured"):
        literal(cases[label], {7, 8})
    literal(cases["erased"], {8})
    literal(cases["window-committed"], set())
    for label in ("pending", "prepared", "session-private", "window-private"):
        assert cases[label]["boundary"]["pending"] is True and cases[label]["c01"]["state"]["value"]["components"] == []
    assert cases["window-private"]["boundary"]["delta_state"] == "ready"
    assert cases["unread"]["boundary"]["delta_state"] == "committed_output" and not cases["unread"]["boundary"]["pending"]
    root = find_cell(cases["noop"], "input")["observations"]
    assert (root["inputs"], root["changed"], root["noop"], root["complete_detail_inputs"]) == (2, 1, 1, 2)
    ratio = find_cell(cases["noop"], "parent_support", node=0)["events_per_input"]
    assert (ratio["numerator"], ratio["denominator"], ratio["denominator_scope"]) == (1, 2, "complete_detail_sample_physical_stratum")
    event = find_cell(cases["erased"], "parent_support", "erase", 0)["observations"]
    assert (event["count"], event["sum"], event["changes"], event["bins"][1], event["bins"][2]) == (2, 3, 2, 1, 1)
    assert cases["erased"]["c01"]["state"]["value"]["components"][5]["distribution"]["histogram"] == [{"multiplicity": 1, "positive_keys": 1}]
    sampled = cases["sampled"]["c01"]["workload"]
    assert sampled["availability"] == "sampled" and sampled["value"]["metadata"]["selected"] == 1 and sampled["value"]["metadata"]["committed"] == 2
    ratio = find_cell(cases["sampled"], "parent_support", node=0)["events_per_input"]
    assert ratio["availability"] == "sampled" and (ratio["numerator"], ratio["denominator"]) == (1, 1)
    truncated = cases["truncated"]["c01"]["workload"]
    assert truncated["availability"] == "incomplete" and truncated["value"]["metadata"]["committed_truncated"] == 1
    for cell in truncated["value"]["cells"]:
        if cell["descriptor"]["kind"] != "physical":
            assert cell["observations"]["count"] == cell["observations"]["changes"] == cell["observations"]["visited"] == 0
    partial = cases["state-exhausted"]["c01"]["state"]["value"]["components"]
    assert partial[0]["distribution"]["ndv"]["value"] == 2 and partial[2]["distribution"]["ndv"]["value"] is None
    assert cases["state-zero"]["c01"]["state"]["availability"] == "budget_exhausted"
    for label, key in (("mode-after", "workload_segment"), ("reset", "workload_reset"), ("reconfigured", "workload_configuration")):
        comparison = cases[label]["comparison"]
        assert comparison["data"] == "current" and comparison[key] == "changed"
    assert cases["mode-noop"]["comparison"]["workload_segment"] == "same"
    assert cases["mode-after"]["o07"]["last"]["begin_configuration"]["resolved_mode"] == "delta"
    assert cases["mode-after"]["o07"]["current_configuration"]["resolved_mode"] == "maintenance"
    assert cases["mode-after"]["c01"]["workload"]["value"]["previous"]["modes"]["resolved_mode"] == "delta"
    assert cases["mode-before"]["o07"]["current_declared_labels"]["run_hex"] == "72756e00ff"
    assert cases["stale"]["comparison"]["data"] == "stale" and cases["within-lag"]["comparison"]["data"] == "within_lag"
    assert cases["rebuilt"]["comparison"]["data"] == "foreign_owner" and cases["rebuilt"]["c01"]["options"]["mode"] == "off"
    assert cases["session-released"]["c01"]["options"]["mode"] == "counters" and cases["session-released"]["comparison"]["data"] is None
    hidden = cases["hidden-e"]["c01"]["state"]["value"]["components"]
    assert hidden[0]["availability"] == "not_applicable" and hidden[0]["cardinality"]["value"] is hidden[0]["distribution"] is None
    assert [hidden[i]["cardinality"]["value"] for i in (1, 2)] == [2, 1]
    mixed = cases["scalars"]["c01"]["state"]["value"]["components"]
    rows = {( -(2**63), True, datetime.date(1, 1, 1), decimal.Decimal(1), bytes.fromhex("6100ff80")): 1,
            (2**63-1, False, datetime.date(9999, 12, 31), decimal.Decimal("-0.0001"), bytes.fromhex("c3a9")): 1}
    distribution(mixed[0]["distribution"], rows, 2, 16)
    distribution(mixed[1]["distribution"], {(row[4], row[0], row[4]): 1 for row in rows}, 2, 16)
    distribution(mixed[2]["distribution"], {(): 2}, 2, 16)
    distribution(mixed[3]["distribution"], rows, 2, 16)
    assert mixed[1]["selection"]["projection_fields"] == [4, 0, 4] and mixed[2]["selection"]["projection_fields"] == []
    probes = [cell["observations"] for cell in cases["generalized-events"]["c01"]["workload"]["value"]["cells"]
              if cell["descriptor"]["role"] == "generalized_probe"]
    children, probe_values = [set(), set()], []
    for x, y, tag in [(1, 7, 0), (1, 7, 1)]:
        for child in range(2):
            if (child == 0 or tag == 1) and (x, y) not in children[child]:
                probe_values.append(int((x, y) in children[0] | children[1]))
                children[child].add((x, y))
    assert probe_values == [0, 1]
    assert sum(cell["count"] for cell in probes) == len(probe_values)
    assert sum(cell["bins"][0] for cell in probes) == probe_values.count(0) and sum(cell["bins"][1] for cell in probes) == probe_values.count(1)
    assert item_count(cases["off-state"]) == int((options.fixtures / "export-items.txt").read_text())
    if options.testing:
        literal(cases["saturated"], {7})
        assert cases["saturated"]["comparison"]["workload_configuration"] == "saturated"
    mutations = 0

    def reject(original, change):
        nonlocal mutations
        changed = copy.deepcopy(original)
        change(changed)
        try:
            validator.validate(changed)
            semantics(changed)
        except (jsonschema.ValidationError, AssertionError):
            mutations += 1
            return
        raise AssertionError("mutated report escaped schema/semantic checks")

    reject(cases["off-state"], lambda x: x.update(extra=True))
    reject(cases["off-state"], lambda x: x["capabilities"].update(global_cost_optimality=True))
    reject(cases["off-state"], lambda x: x["c01"]["state"]["value"]["components"][0].update(exact=True))
    reject(cases["off-state"], lambda x: x["boundary"].update(owner=x["boundary"]["owner"]+1))
    reject(cases["off-state"], lambda x: x["mode"]["requested"]["o07"].update(mode="counters"))
    reject(cases["state-exhausted"], lambda x: x["c01"]["state"]["value"]["components"][2]["distribution"].update(histogram=[]))
    reject(cases["state-exhausted"], lambda x: x["c01"]["state"]["value"]["components"][2]["distribution"]["ndv"].update(value=0,reason=None))
    reject(cases["scalars"], lambda x: x["c01"]["state"]["value"]["components"][0]["distribution"]["top_k"][0]["key"][4].update(value="ff0"))
    reject(cases["scalars"], lambda x: x["c01"]["state"]["value"]["components"][0]["distribution"]["top_k"][0]["key"][4].update(encoding="utf8"))
    reject(cases["scalars"], lambda x: x["c01"]["state"]["value"]["components"][0]["distribution"]["top_k"][0]["key"][2].update(value="0000-01-01"))
    reject(cases["scalars"], lambda x: x["c01"]["state"]["value"]["components"][0]["distribution"]["top_k"][0]["key"][3].update(value="1.00"))
    reject(cases["scalars"], lambda x: x["c01"]["state"]["value"]["components"][0]["distribution"]["top_k"][0]["key"][1].update(value=None))
    reject(cases["noop"], lambda x: find_cell(x,"parent_support",node=0)["events_per_input"].update(denominator=None))
    reject(cases["pending"], lambda x: x["boundary"].update(pending=False))
    reject(cases["session-released"], lambda x: x["c01"]["workload"].update(stamp={}))
    if options.testing:
        reject(cases["saturated"], lambda x: x["c01"]["workload"].update(availability="exact"))
        reject(cases["saturated"], lambda x: x["c01"]["workload"]["value"]["cells"][0]["events_per_input"].update(availability="exact",numerator=1,denominator=1,reason=None))
    print(json.dumps({"status":"pass","reports":len(cases),"legacy_byte_comparisons":2,"mutations_rejected":mutations,"testing":options.testing,
                      "jsonschema_version":importlib.metadata.version("jsonschema")},sort_keys=True))


if __name__ == "__main__":
    main()
