#!/usr/bin/env python3
"""Independent consistency checks for the literal C01 fixture packet.

This uses only JSON rows/maps and the Python standard library. It has no
connection to CROWN runtime state, production collectors, or O07 metrics.
"""

from collections import Counter
from decimal import Decimal
import json
from pathlib import Path


PACKET = Path(__file__).with_name("fixtures.json")


def require(condition, message):
    if not condition:
        raise AssertionError(message)


def scalar_key(value):
    if isinstance(value, dict):
        if set(value) == {"bytes_hex"}:
            return (1, bytes.fromhex(value["bytes_hex"]))
        if set(value) == {"decimal"}:
            return (4, Decimal(value["decimal"]))
        if set(value) == {"decimal_input"}:
            # Input spellings are only used for equality checks after parsing.
            return (4, Decimal(value["decimal_input"]))
        raise AssertionError(f"unrecognized tagged scalar: {value!r}")
    if isinstance(value, bool):
        return (2, value)
    if isinstance(value, int):
        return (0, value)
    if isinstance(value, str):
        return (1, value.encode("utf-8"))
    raise AssertionError(f"unsupported fixture scalar: {value!r}")


def row_key(row):
    return tuple(scalar_key(value) for value in row)


def native_key_order(key):
    return tuple(scalar_key(value) for value in key)


def projection(row, layout, fields):
    positions = [layout.index(field) for field in fields]
    return [row[position] for position in positions]


def projection_key(row, layout, fields):
    return row_key(projection(row, layout, fields))


def literal_bins(values, value_name, count_name):
    counts = Counter(values)
    return [
        {value_name: value, count_name: counts[value]}
        for value in sorted(counts)
    ]


def check_population(population, label):
    rows = population["rows"]
    layout = population["layout"]
    keys = [row_key(row) for row in rows]
    require(len(keys) == len(set(keys)), f"{label}: population rows are not a set")
    require(population["cardinality"] == len(rows), f"{label}: cardinality mismatch")
    for projection_spec in population["ordered_projection_ndv"]:
        fields = projection_spec["fields"]
        ndv = len({projection_key(row, layout, fields) for row in rows})
        require(ndv == projection_spec["ndv"], f"{label}: NDV mismatch for {fields!r}")

    if "derivations" in population:
        derivations = population["derivations"]
        derived_keys = [row_key(item["tuple"]) for item in derivations]
        require(len(derived_keys) == len(set(derived_keys)), f"{label}: duplicate derivation key")
        require(set(derived_keys) == set(keys), f"{label}: derivation keys differ from native rows")
        require(all(item["count"] > 0 for item in derivations), f"{label}: nonpositive derivation")


def check_support_map(item, survivor, label):
    entries = item["key_multiplicities"]
    keys = [row_key(entry["key"]) for entry in entries]
    require(len(keys) == len(set(keys)), f"{label}: duplicate support key")
    require(all(entry["multiplicity"] > 0 for entry in entries), f"{label}: stored zero/nonpositive key")
    counts = [entry["multiplicity"] for entry in entries]
    layout = survivor["layout"]
    fields = item["projection_fields"]
    expected_map = Counter(projection_key(row, layout, fields) for row in survivor["rows"])
    provided_map = {row_key(entry["key"]): entry["multiplicity"] for entry in entries}
    require(provided_map == expected_map, f"{label}: support keys/counts do not group S rows")
    expected_bins = literal_bins(counts, "multiplicity", "key_count")
    summary = item["summary"]
    require(summary["positive_key_count"] == len(entries), f"{label}: positive-key count mismatch")
    require(summary["sum_multiplicities"] == sum(counts), f"{label}: support sum mismatch")
    require(summary["bins"] == expected_bins, f"{label}: support histogram mismatch")
    require(sum(counts) == survivor["cardinality"], f"{label}: P/E sum differs from S cardinality")

    top = item.get("top_k")
    if top is not None:
        ordered = sorted(entries, key=lambda entry: (-entry["multiplicity"], native_key_order(entry["key"])))
        expected = [
            {"key": entry["key"], "count": entry["multiplicity"]}
            for entry in ordered[: top["k"]]
        ]
        require(top["entries"] == expected, f"{label}: deterministic top-K mismatch")


def check_index(index, label, source_population=None):
    entries = index["key_degrees"]
    keys = [row_key(entry["key"]) for entry in entries]
    require(len(keys) == len(set(keys)), f"{label}: duplicate index key")
    require(all(entry["degree"] > 0 for entry in entries), f"{label}: empty bucket stored")
    degrees = [entry["degree"] for entry in entries]
    if source_population is not None:
        expected_degrees = Counter(
            projection_key(row, source_population["layout"], index["key_fields"])
            for row in source_population["rows"]
        )
        provided_degrees = {
            row_key(entry["key"]): entry["degree"] for entry in entries
        }
        require(provided_degrees == expected_degrees, f"{label}: bucket degrees do not group source rows")
    summary = index["summary"]
    require(summary["positive_key_count"] == len(entries), f"{label}: index NDV mismatch")
    require(summary["sum_degrees"] == sum(degrees), f"{label}: index degree sum mismatch")
    require(summary["bins"] == literal_bins(degrees, "degree", "key_count"), f"{label}: index histogram mismatch")
    top = index.get("top_k")
    if top is not None:
        ordered = sorted(entries, key=lambda entry: (-entry["degree"], native_key_order(entry["key"])))
        expected = [{"key": entry["key"], "degree": entry["degree"]} for entry in ordered[: top["k"]]]
        require(top["entries"] == expected, f"{label}: deterministic index top-K mismatch")


def check_common_state(state, label):
    sources = {}
    for table in state.get("source_tables", []):
        check_population(table["population"], f"{label}/{table['id']}/source")
        sources[table["id"]] = table["population"]
    for native in state.get("native_populations", []):
        check_population(native["population"], f"{label}/{native['id']}/native")
    survivors = state.get("survivor_populations", [])
    survivor_by_id = {}
    for survivor in survivors:
        check_population(survivor["population"], f"{label}/{survivor['id']}/S")
        survivor_by_id[survivor["id"].split(":", 1)[-1]] = survivor["population"]
    for item in state.get("P", []) + state.get("E", []):
        scope = item["id"].split(":", 1)[-1]
        require(scope in survivor_by_id, f"{label}/{item['id']}: missing S population")
        check_support_map(item, survivor_by_id[scope], f"{label}/{item['id']}")
    for index in state.get("existing_indexes", []):
        owner = index["id"].split(".", 1)[0]
        check_index(index, f"{label}/{index['id']}", sources.get(owner))


def check_single_state(state, label):
    for name in ("source", "native", "S"):
        check_population(state[name], f"{label}/{name}")
    check_support_map(state["P"], state["S"], f"{label}/P")
    check_support_map(state["E"], state["S"], f"{label}/E")


def check_packet(packet):
    checked = 0
    for fixture in packet["fixtures"]:
        fixture_id = fixture["id"]
        if fixture_id == "native_r_root_s_child":
            for state in fixture["states"]:
                check_common_state(state, f"{fixture_id}/{state['label']}")
                checked += 1
            require(fixture["post_baseline_inputs"]["touched_degree_histogram"]["event_count"] == 2,
                    f"{fixture_id}: touched event denominator")
            require(fixture["post_baseline_inputs"]["support_count_changes"]["P:R-root"]["changes"] == 3,
                    f"{fixture_id}: P change denominator")
            require(fixture["post_baseline_inputs"]["support_count_changes"]["E:R-root"]["changes"] == 3,
                    f"{fixture_id}: E change denominator")
        elif fixture_id == "physical_projection_derivations":
            for state in fixture["states"]:
                check_single_state(state, f"{fixture_id}/{state['label']}")
                checked += 1
            require(fixture["post_baseline_inputs"]["committed_physical_input_count"] == 6,
                    f"{fixture_id}: physical denominator")
            require(fixture["post_baseline_inputs"]["no_op_source_memberships"] == 2,
                    f"{fixture_id}: no-op count")
            require(fixture["states"][-1]["native"]["cardinality"] == 0,
                    f"{fixture_id}: last derivation must remove native tuple")
        elif fixture_id == "empty_and_nullary_projections":
            for case in fixture["cases"]:
                check_single_state(case, f"{fixture_id}/{case['label']}")
                checked += 1
        elif fixture_id == "binary_heavy_tie_and_decimal_equality":
            for state in fixture["states"]:
                check_common_state(state, f"{fixture_id}/{state['label']}")
                checked += 1
            weighting = fixture["index_event_weighting_control"]
            parent_population = {
                "layout": ["k", "id"],
                "rows": weighting["parent_source_rows"],
            }
            check_index(weighting["existing_index"], f"{fixture_id}/weighting/index", parent_population)
            require(weighting["touched_degree_event_values"] == [1,1,1,1,1,1,1,1,2],
                    f"{fixture_id}: weighting trace degrees")
            require(weighting["touched_degree_histogram"]["event_count"] == 9,
                    f"{fixture_id}: weighting event count")
            require(weighting["touched_degree_histogram"]["sum_degrees"] == 10,
                    f"{fixture_id}: weighting event degree sum")
            final_s = {"layout": ["k", "id"], "rows": weighting["final_survivor_rows"],
                       "cardinality": weighting["final_S_cardinality"]}
            check_support_map(weighting["final_P"], final_s, f"{fixture_id}/weighting/P")
            check_support_map(weighting["final_E"], final_s, f"{fixture_id}/weighting/E")
            checked += 1
        else:
            raise AssertionError(f"unrecognized fixture {fixture_id!r}")

    require(packet["lower_only_capture"]["physical_input_denominator"] == "unavailable",
            "lower-only physical denominator must remain unavailable")
    require(packet["lower_only_capture"]["unavailable_must_not_be_encoded_as_zero"] is True,
            "lower-only unavailable state must not be represented as zero")
    return checked


def main():
    packet = json.loads(PACKET.read_text(encoding="utf-8"))
    count = check_packet(packet)
    print(f"C01 literal fixture reference: PASS ({count} scopes checked)")


if __name__ == "__main__":
    main()
