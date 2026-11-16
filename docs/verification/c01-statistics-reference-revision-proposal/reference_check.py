#!/usr/bin/env python3
"""Replay the literal C01 fixtures with only sets, Counters, and JSON data.

This checker has no CROWN runtime, collector, or O07 metric dependency. It
compares literal expected maps in fixtures.json against independently replayed
source rows, native derivations, survivor rows, support maps, and index events.
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
        if set(value) in ({"decimal"}, {"decimal_input"}):
            return (4, Decimal(value.get("decimal", value.get("decimal_input"))))
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


def canonical_scalar(value):
    if isinstance(value, dict) and set(value) == {"decimal_input"}:
        number = Decimal(value["decimal_input"])
        text = "0" if number == 0 else format(number.normalize(), "f")
        return {"decimal": text}
    return value


def canonical_row(row):
    return [canonical_scalar(value) for value in row]


def rows_map(rows):
    result = {}
    for row in rows:
        canonical = canonical_row(row)
        key = row_key(canonical)
        require(key not in result, f"duplicate full row in literal set: {row!r}")
        result[key] = canonical
    return result


def same_rows(actual, expected, label):
    actual_map = rows_map(actual)
    expected_map = rows_map(expected)
    require(actual_map.keys() == expected_map.keys(), f"{label}: row-set mismatch")


def projection(row, layout, fields):
    return [row[layout.index(field)] for field in fields]


def projection_key(row, layout, fields):
    return row_key(projection(row, layout, fields))


def derive_projection_counts(rows, layout, fields):
    counts = Counter()
    values = {}
    for row in rows:
        value = projection(row, layout, fields)
        key = row_key(value)
        counts[key] += 1
        values[key] = value
    return counts, values


def literal_bins(values, value_name, count_name):
    counts = Counter(values)
    return [
        {value_name: value, count_name: counts[value]}
        for value in sorted(counts)
    ]


def check_population(population, label):
    rows = population["rows"]
    keys = [row_key(canonical_row(row)) for row in rows]
    require(len(keys) == len(set(keys)), f"{label}: population rows are not a set")
    require(population["cardinality"] == len(rows), f"{label}: cardinality mismatch")
    layout = population["layout"]
    for projection_spec in population["ordered_projection_ndv"]:
        fields = projection_spec["fields"]
        ndv = len({projection_key(row, layout, fields) for row in rows})
        require(ndv == projection_spec["ndv"], f"{label}: NDV mismatch for ordered fields {fields!r}")

    if "derivations" in population:
        derivations = population["derivations"]
        derived = {row_key(item["tuple"]): item["count"] for item in derivations}
        require(len(derived) == len(derivations), f"{label}: duplicate derivation key")
        require(set(derived) == set(keys), f"{label}: derivation keys differ from native rows")
        require(all(count > 0 for count in derived.values()), f"{label}: nonpositive derivation")


def check_native_from_source(native_population, source_rows, source_layout, source_fields, label):
    counts, tuples = derive_projection_counts(source_rows, source_layout, source_fields)
    actual_rows = {row_key(row) for row in native_population["rows"]}
    require(actual_rows == set(tuples), f"{label}: native rows do not equal distinct projected source rows")
    actual_derivations = {
        row_key(item["tuple"]): item["count"]
        for item in native_population["derivations"]
    }
    require(actual_derivations == dict(counts), f"{label}: derivation counts do not group literal source rows")


def check_support_record(item, survivor_rows, layout, label):
    fields = item["projection_fields"]
    expected_counts, key_values = derive_projection_counts(survivor_rows, layout, fields)
    # For P/E, a projection key's support is its number of S tuples.
    entries = item["key_multiplicities"]
    actual_counts = {row_key(entry["key"]): entry["multiplicity"] for entry in entries}
    require(len(actual_counts) == len(entries), f"{label}: duplicate support key")
    require(all(count > 0 for count in actual_counts.values()), f"{label}: nonpositive stored support")
    require(actual_counts == dict(expected_counts), f"{label}: map does not group the literal S rows")

    bins = literal_bins(actual_counts.values(), "multiplicity", "key_count")
    summary = item["summary"]
    require(summary["positive_key_count"] == len(actual_counts), f"{label}: positive-key count mismatch")
    require(summary["sum_multiplicities"] == sum(actual_counts.values()), f"{label}: support sum mismatch")
    require(summary["bins"] == bins, f"{label}: positive support histogram mismatch")
    require(sum(actual_counts.values()) == len(survivor_rows), f"{label}: P/E sum differs from S cardinality")

    top = item.get("top_k")
    if top is not None:
        ordered_keys = sorted(actual_counts, key=lambda key: (-actual_counts[key], key))
        expected_top = [
            {"key": key_values[key], "count": actual_counts[key]}
            for key in ordered_keys[: top["k"]]
        ]
        require(top["entries"] == expected_top, f"{label}: deterministic top-K mismatch")


def check_index(index, source_rows, source_layout, label):
    key_fields = index["key_fields"]
    expected, key_values = derive_projection_counts(source_rows, source_layout, key_fields)
    entries = index["key_degrees"]
    actual = {row_key(entry["key"]): entry["degree"] for entry in entries}
    require(len(actual) == len(entries), f"{label}: duplicate index key")
    require(all(degree > 0 for degree in actual.values()), f"{label}: empty bucket stored")
    require(actual == dict(expected), f"{label}: degree map does not group the literal source rows")
    summary = index["summary"]
    require(summary["positive_key_count"] == len(actual), f"{label}: index NDV mismatch")
    require(summary["sum_degrees"] == sum(actual.values()), f"{label}: index degree sum mismatch")
    require(summary["bins"] == literal_bins(actual.values(), "degree", "key_count"), f"{label}: degree histogram mismatch")
    if "uniform_key_mean" in summary:
        require(summary["uniform_key_mean"] == sum(actual.values()) / len(actual),
                f"{label}: positive-key mean mismatch")
    top = index.get("top_k")
    if top is not None:
        ordered_keys = sorted(actual, key=lambda key: (-actual[key], key))
        expected_top = [
            {"key": key_values[key], "degree": actual[key]}
            for key in ordered_keys[: top["k"]]
        ]
        require(top["entries"] == expected_top, f"{label}: deterministic index top-K mismatch")


def check_common_state(state, label):
    source_by_id = {}
    for table in state.get("source_tables", []):
        pop = table["population"]
        check_population(pop, f"{label}/{table['id']}/source")
        source_by_id[table["id"]] = pop
    for native in state.get("native_populations", []):
        check_population(native["population"], f"{label}/{native['id']}/native")
    survivor_by_id = {}
    for survivor in state.get("survivor_populations", []):
        pop = survivor["population"]
        check_population(pop, f"{label}/{survivor['id']}/S")
        survivor_by_id[survivor["id"].split(":", 1)[-1]] = pop
    for item in state.get("P", []) + state.get("E", []):
        scope = item["id"].split(":", 1)[-1]
        require(scope in survivor_by_id, f"{label}/{item['id']}: missing S population")
        pop = survivor_by_id[scope]
        check_support_record(item, pop["rows"], pop["layout"], f"{label}/{item['id']}")
    for index in state.get("existing_indexes", []):
        owner = index["id"].split(".", 1)[0]
        require(owner in source_by_id, f"{label}/{index['id']}: missing source owner")
        pop = source_by_id[owner]
        check_index(index, pop["rows"], pop["layout"], f"{label}/{index['id']}")


def check_single_state(state, label):
    for name in ("source", "native", "S"):
        check_population(state[name], f"{label}/{name}")
    check_support_record(state["P"], state["S"]["rows"], state["S"]["layout"], f"{label}/P")
    check_support_record(state["E"], state["S"]["rows"], state["S"]["layout"], f"{label}/E")


def support_changes(old_rows, new_rows, layout, support_items):
    """Replay each individual S tuple membership change into each P/E map."""
    old_map = rows_map(old_rows)
    new_map = rows_map(new_rows)
    removed = [old_map[key] for key in old_map.keys() - new_map.keys()]
    added = [new_map[key] for key in new_map.keys() - old_map.keys()]
    removed.sort(key=native_key_order)
    added.sort(key=native_key_order)
    results = {}
    for scope, item in support_items:
        counts, _ = derive_projection_counts(old_rows, layout, item["projection_fields"])
        result = {"changes": 0, "zero_to_positive": 0, "positive_to_zero": 0, "positive_to_positive": 0}
        for row, delta in [(row, 1) for row in added] + [(row, -1) for row in removed]:
            key = projection_key(row, layout, item["projection_fields"])
            before = counts.get(key, 0)
            after = before + delta
            require(after >= 0, "support transition would become negative")
            result["changes"] += 1
            if before == 0 and after > 0:
                result["zero_to_positive"] += 1
            elif before > 0 and after == 0:
                result["positive_to_zero"] += 1
            else:
                result["positive_to_positive"] += 1
            if after:
                counts[key] = after
            else:
                counts.pop(key, None)
        expected_after, _ = derive_projection_counts(new_rows, layout, item["projection_fields"])
        require(counts == expected_after, f"{scope}: replayed support map differs from next S state")
        crossings = result["zero_to_positive"] + result["positive_to_zero"]
        result["crossing_fraction"] = crossings / result["changes"] if result["changes"] else "unknown"
        results[scope] = result
    return results


def add_change_totals(total, changes):
    for scope, item in changes.items():
        target = total.setdefault(scope, {
            "changes": 0, "zero_to_positive": 0,
            "positive_to_zero": 0, "positive_to_positive": 0,
        })
        for field in target:
            target[field] += item[field]


def finish_change_totals(total):
    for item in total.values():
        crossings = item["zero_to_positive"] + item["positive_to_zero"]
        item["crossing_fraction"] = crossings / item["changes"] if item["changes"] else "unknown"
    return total


def compare_change_summaries(expected, actual, label):
    require(expected == actual, f"{label}: support-count changes/crossings mismatch; derived={actual!r}")


def compare_state_rows(state, sources, label):
    expected_tables = {table["id"]: table["population"] for table in state.get("source_tables", [])}
    require(set(expected_tables) == set(sources), f"{label}: source table scopes changed")
    for table_id, population in expected_tables.items():
        same_rows(population["rows"], list(sources[table_id].values()), f"{label}/{table_id} source")


def checked_native_identity(population, rows, label):
    check_native_from_source(population, rows, population["layout"], population["layout"], label)


def state_r_s(fixture, state, source_sets, r_rows, label):
    compare_state_rows(state, source_sets, label)
    r_native = next(item["population"] for item in state["native_populations"] if item["id"] == "R-root-native")
    s_native = next(item["population"] for item in state["native_populations"] if item["id"] == "S-child-native")
    checked_native_identity(r_native, list(source_sets["R"].values()), f"{label}/R native")
    checked_native_identity(s_native, list(source_sets["S"].values()), f"{label}/S native")

    child_keys = {row_key(row) for row in source_sets["S"].values()}
    expected_survivors = [row for row in r_rows if row_key([row[1]]) in child_keys]
    survivor = state["survivor_populations"][0]["population"]
    same_rows(survivor["rows"], expected_survivors, f"{label}/survivor join")
    check_common_state(state, label)
    return expected_survivors


def replay_native_r_s(fixture):
    states = fixture["states"]
    baseline_tables = {table["id"]: table["population"] for table in states[0]["source_tables"]}
    source_sets = {name: rows_map(pop["rows"]) for name, pop in baseline_tables.items()}
    r_rows = list(source_sets["R"].values())
    previous_survivors = state_r_s(fixture, states[0], source_sets, r_rows, "native_r_root_s_child/baseline")
    all_support_changes = {}
    committed = changed_memberships = noops = routes = 0
    touched_degrees = []

    operations = fixture["post_baseline_inputs"]["operations"]
    require(len(states) == len(operations) + 1, "native R/S: expected one state before and after each input")
    for position, operation in enumerate(operations):
        committed += 1
        table = operation["table"]
        row = canonical_row(operation["row"])
        current = source_sets[table]
        key = row_key(row)
        before_cardinality = len(current)
        is_insert = operation["operation"] == "insert"
        changed = (key not in current) if is_insert else (key in current)
        if changed:
            if is_insert:
                current[key] = row
            else:
                del current[key]
            changed_memberships += 1
            routes += 1
            parent_key = operation["parent_key"]
            degree = sum(1 for candidate in r_rows if row_key([candidate[1]]) == row_key(parent_key))
            touched_degrees.append(degree)
        else:
            noops += 1
            degree = None
        after_cardinality = len(current)
        require(operation["source_cardinality"] == f"{before_cardinality}_to_{after_cardinality}",
                f"native R/S input {position}: source cardinality transition mismatch")
        if "touched_parent_degree" in operation:
            require(changed and degree == operation["touched_parent_degree"],
                    f"native R/S input {position}: touched degree did not derive from R rows")
        if "new_survivors" in operation or "removed_survivors" in operation:
            child_keys = {row_key(value) for value in current.values()}
            next_survivors = [row for row in r_rows if row_key([row[1]]) in child_keys]
            before_keys = {row_key(row) for row in previous_survivors}
            after_keys = {row_key(row) for row in next_survivors}
            require(operation.get("new_survivors", 0) == len(after_keys - before_keys),
                    f"native R/S input {position}: new survivor count mismatch")
            require(operation.get("removed_survivors", 0) == len(before_keys - after_keys),
                    f"native R/S input {position}: removed survivor count mismatch")
            support_items = [(item["id"], item) for item in states[position]["P"] + states[position]["E"]]
            add_change_totals(all_support_changes, support_changes(previous_survivors, next_survivors,
                                                                    ["x", "y"], support_items))
            previous_survivors = next_survivors
        else:
            # A child no-op cannot alter the survivor or support maps.
            require(not changed, f"native R/S input {position}: omitted survivor transition on changed input")

        state_r_s(fixture, states[position + 1], source_sets, r_rows,
                  f"native_r_root_s_child/{states[position + 1]['label']}")

    expected = fixture["post_baseline_inputs"]
    require(expected["committed_physical_input_count"] == committed, "native R/S: physical input count not replay-derived")
    require(expected["changed_source_memberships"] == changed_memberships, "native R/S: changed membership count mismatch")
    require(expected["no_op_source_memberships"] == noops, "native R/S: no-op count mismatch")
    require(expected["occurrence_routes_visited_total"] == routes, "native R/S: route count mismatch")
    histogram = expected["touched_degree_histogram"]
    require(histogram["event_count"] == len(touched_degrees), "native R/S: touched event denominator mismatch")
    require(histogram["sum_degrees"] == sum(touched_degrees), "native R/S: touched degree sum mismatch")
    require(histogram["bins"] == literal_bins(touched_degrees, "degree", "event_count"),
            "native R/S: touched degree bins mismatch")
    compare_change_summaries(expected["support_count_changes"], finish_change_totals(all_support_changes),
                             "native R/S")


def state_projection_case(state, source_rows, source_layout, native_fields, label):
    check_single_state(state, label)
    same_rows(state["source"]["rows"], source_rows, f"{label}/source replay")
    check_native_from_source(state["native"], source_rows, source_layout, native_fields, f"{label}/native replay")
    counts, values = derive_projection_counts(source_rows, source_layout, native_fields)
    expected_survivors = [values[key] for key, count in counts.items() if count > 0]
    same_rows(state["S"]["rows"], expected_survivors, f"{label}/S from positive derivations")
    return expected_survivors, counts


def replay_physical_projection(fixture):
    states = fixture["states"]
    source_layout = states[0]["source"]["layout"]
    native_fields = fixture["native_layout"]
    current = rows_map(fixture["initial_source_rows"])
    survivors, derivations = state_projection_case(states[0], list(current.values()), source_layout,
                                                  native_fields, f"{fixture['id']}/{states[0]['label']}")
    input_summary = fixture["post_baseline_inputs"]
    operations = input_summary["operations"]
    require(len(states) == len(operations) + 1, "projection derivation: expected one state before and after each input")
    committed = changed_memberships = noops = routes = crossings = 0
    support_totals = {}

    for position, operation in enumerate(operations):
        committed += 1
        row = canonical_row(operation["row"])
        key = row_key(row)
        is_insert = operation["operation"] == "insert"
        changed = (key not in current) if is_insert else (key in current)
        old_counts, _ = derive_projection_counts(list(current.values()), source_layout, native_fields)
        native_key = projection_key(row, source_layout, native_fields)
        old_count = old_counts.get(native_key, 0)
        if changed:
            if is_insert:
                current[key] = row
            else:
                del current[key]
            changed_memberships += 1
            routes += 1
        else:
            noops += 1
        next_rows = list(current.values())
        new_counts, _ = derive_projection_counts(next_rows, source_layout, native_fields)
        new_count = new_counts.get(native_key, 0)
        derivation_delta = new_count - old_count
        membership_crossing = (old_count == 0) != (new_count == 0)
        require(operation["source_membership_changed"] is changed,
                f"projection input {position}: source membership result mismatch")
        require(operation["occurrence_routes_visited"] == (1 if changed else 0),
                f"projection input {position}: no-op/route result mismatch")
        require(operation["accepted_derivation_delta"] == derivation_delta,
                f"projection input {position}: derivation delta mismatch")
        require(operation["native_membership_crossing"] is membership_crossing,
                f"projection input {position}: native crossing mismatch")
        if "derivation_count_after" in operation:
            require(operation["derivation_count_after"] == new_count,
                    f"projection input {position}: derivation count mismatch")
        old_survivors = survivors
        next_state = states[position + 1]
        survivors, derivations = state_projection_case(next_state, next_rows, source_layout, native_fields,
                                                       f"{fixture['id']}/{next_state['label']}")
        per_step = support_changes(old_survivors, survivors, next_state["S"]["layout"],
                                   [("P", next_state["P"]), ("E", next_state["E"])])
        add_change_totals(support_totals, per_step)
        if membership_crossing:
            crossings += 1

    require(input_summary["committed_physical_input_count"] == committed,
            "projection derivation: physical denominator not replay-derived")
    require(input_summary["changed_source_memberships"] == changed_memberships,
            "projection derivation: changed source count mismatch")
    require(input_summary["no_op_source_memberships"] == noops,
            "projection derivation: no-op count mismatch")
    require(input_summary["occurrence_routes_visited_total"] == routes,
            "projection derivation: route count mismatch")
    require(input_summary["native_tuple_membership_crossings"] == crossings,
            "projection derivation: native membership crossing count mismatch")
    require(not states[-1]["native"]["rows"] and not states[-1]["native"]["derivations"]
            and not states[-1]["S"]["rows"],
            "projection derivation: final source erase must leave no native/S tuple")

    final_step = support_changes(states[-2]["S"]["rows"], states[-1]["S"]["rows"],
                                 states[-1]["S"]["layout"],
                                 [("P", states[-1]["P"]), ("E", states[-1]["E"])])
    aggregate_support = finish_change_totals(support_totals)
    require(aggregate_support == final_step,
            "projection derivation: support transitions occurred before the last derivation erase")
    fields = ("changes", "zero_to_positive", "positive_to_zero", "crossing_fraction")
    expected_last = {
        "P:R-root_support_changes_on_last_erase": {field: final_step["P"][field] for field in fields},
        "E:R-root_support_changes_on_last_erase": {field: final_step["E"][field] for field in fields},
    }
    actual_last = {
        name: {field: value for field, value in item.items() if field in
               ("changes", "zero_to_positive", "positive_to_zero", "crossing_fraction")}
        for name, item in input_summary.items()
        if name.endswith("_support_changes_on_last_erase")
    }
    require(actual_last == expected_last, "projection derivation: final support crossing denominators mismatch")


def replay_decimal_noop(fixture):
    state = next(item for item in fixture["states"] if item["label"] == "canonical_decimal_projection")
    check_common_state(state, f"{fixture['id']}/{state['label']}")
    source_table = state["source_tables"][0]
    source_pop = source_table["population"]
    source_layout = source_pop["layout"]
    original_from_spellings = [canonical_row(item["row"]) for item in fixture["states"][1]["input_spellings"]]
    same_rows(source_pop["rows"], original_from_spellings, "decimal initial spellings after canonical parse")
    current = rows_map(original_from_spellings)
    native = state["native_populations"][0]["population"]
    check_native_from_source(native, list(current.values()), source_layout, ["amount"], "decimal initial derivations")
    survivor = state["survivor_populations"][0]["population"]
    same_rows(survivor["rows"], native["rows"], "decimal S from native projection")

    summary = fixture["states"][1]["post_baseline_inputs"]
    committed = changed = noops = routes = 0
    for position, operation in enumerate(summary["operations"]):
        committed += 1
        before_cardinality = len(current)
        row = canonical_row(operation["row"])
        parsed = canonical_row(operation["parsed_native_row"])
        require(row_key(row) == row_key(parsed), f"decimal input {position}: parsed full row mismatch")
        key = row_key(row)
        present = key in current
        did_change = not present if operation["operation"] == "insert" else present
        before_counts, _ = derive_projection_counts(list(current.values()), source_layout, ["amount"])
        native_key = projection_key(row, source_layout, ["amount"])
        before_derivations = before_counts.get(native_key, 0)
        if did_change:
            changed += 1
            routes += 1
            if operation["operation"] == "insert":
                current[key] = row
            else:
                del current[key]
        else:
            noops += 1
        after_counts, _ = derive_projection_counts(list(current.values()), source_layout, ["amount"])
        derivation_delta = after_counts.get(native_key, 0) - before_derivations
        require(operation["source_membership_changed"] is did_change,
                f"decimal input {position}: equality/no-op result mismatch")
        require(operation["occurrence_routes_visited"] == (1 if did_change else 0),
                f"decimal input {position}: route result mismatch")
        require(operation["native_derivation_delta"] == derivation_delta,
                f"decimal input {position}: derivation delta mismatch")
        cardinality = len(current)
        require(operation["source_cardinality"] == f"{before_cardinality}_to_{cardinality}",
                f"decimal input {position}: source cardinality mismatch")
    require(summary["committed_physical_input_count"] == committed,
            "decimal case: physical denominator not replay-derived")
    require(summary["changed_source_memberships"] == changed, "decimal case: changed count mismatch")
    require(summary["no_op_source_memberships"] == noops, "decimal case: no-op count mismatch")
    require(summary["occurrence_routes_visited_total"] == routes, "decimal case: route count mismatch")
    same_rows(source_pop["rows"], list(current.values()), "decimal source rows after replay")
    check_native_from_source(native, list(current.values()), source_layout, ["amount"], "decimal final derivations")


def replay_weighting_control(control):
    parent_rows = control["parent_source_rows"]
    parent_layout = ["k", "id"]
    check_index(control["existing_index"], parent_rows, parent_layout, "weighting reverse index")
    parent_degrees, _ = derive_projection_counts(parent_rows, parent_layout, ["k"])
    initial_child = control["child_source_initial_rows"]
    child = rows_map(initial_child)
    events = control["applied_child_key_event_trace"]
    snapshots = control["state_snapshots"]
    require(len(snapshots) == len(events) + 1, "weighting trace: expected initial and per-event state maps")

    def check_weighting_snapshot(snapshot, position):
        same_rows(snapshot["child_rows"], list(child.values()), f"weighting state {position}/child")
        child_keys = {row_key([row[0]]) for row in child.values()}
        expected_survivors = [row for row in parent_rows if row_key([row[0]]) in child_keys]
        same_rows(snapshot["survivor_rows"], expected_survivors, f"weighting state {position}/S")
        check_support_record(snapshot["P"], expected_survivors, parent_layout, f"weighting state {position}/P")
        check_support_record(snapshot["E"], expected_survivors, parent_layout, f"weighting state {position}/E")
        return expected_survivors

    previous_survivors = check_weighting_snapshot(snapshots[0], 0)
    degrees = []
    committed = changed = noops = 0
    support_totals = {}
    for position, event in enumerate(events):
        committed += 1
        operation, key_value = event[0], event[1:]
        row = [key_value]
        key = row_key(row)
        is_insert = operation == "+"
        did_change = (key not in child) if is_insert else (key in child)
        if did_change:
            changed += 1
            if is_insert:
                child[key] = row
            else:
                del child[key]
            degree = parent_degrees.get(row_key([key_value]), 0)
            degrees.append(degree)
        else:
            noops += 1
            degree = None
        next_snapshot = snapshots[position + 1]
        next_survivors = check_weighting_snapshot(next_snapshot, position + 1)
        step_changes = support_changes(previous_survivors, next_survivors, parent_layout,
                                       [("P", next_snapshot["P"]), ("E", next_snapshot["E"])])
        add_change_totals(support_totals, step_changes)
        previous_survivors = next_survivors

    counter_expected = control["post_baseline_counters"]
    require(counter_expected["committed_physical_input_count"] == committed,
            "weighting trace: physical denominator not replay-derived")
    require(counter_expected["changed_source_memberships"] == changed,
            "weighting trace: changed membership count mismatch")
    require(counter_expected["no_op_source_memberships"] == noops,
            "weighting trace: no-op count mismatch")
    require(control["touched_degree_event_values"] == degrees,
            "weighting trace: touched degrees were not derived from the parent key map")
    histogram = control["touched_degree_histogram"]
    require(histogram["event_count"] == len(degrees), "weighting trace: event denominator mismatch")
    require(histogram["sum_degrees"] == sum(degrees), "weighting trace: touched degree sum mismatch")
    require(histogram["bins"] == literal_bins(degrees, "degree", "event_count"),
            "weighting trace: touched degree bins mismatch")
    require(histogram["event_weighted_mean"] == sum(degrees) / len(degrees),
            "weighting trace: event-weighted mean mismatch")
    require(control["final_child_source_rows"] == list(child.values()),
            "weighting trace: final child rows mismatch")
    require(control["final_S_cardinality"] == len(previous_survivors),
            "weighting trace: final S cardinality mismatch")
    same_rows(control["final_survivor_rows"], previous_survivors, "weighting final S")
    check_support_record(control["final_P"], previous_survivors, parent_layout, "weighting final P")
    check_support_record(control["final_E"], previous_survivors, parent_layout, "weighting final E")
    compare_change_summaries(control["support_count_changes"], finish_change_totals(support_totals),
                             "weighting trace")


def check_packet(packet):
    scope_count = transition_count = 0
    for fixture in packet["fixtures"]:
        fixture_id = fixture["id"]
        if fixture_id == "native_r_root_s_child":
            replay_native_r_s(fixture)
            scope_count += len(fixture["states"])
            transition_count += len(fixture["post_baseline_inputs"]["operations"])
        elif fixture_id == "physical_projection_derivations":
            replay_physical_projection(fixture)
            scope_count += len(fixture["states"])
            transition_count += len(fixture["post_baseline_inputs"]["operations"])
        elif fixture_id == "empty_and_nullary_projections":
            for case in fixture["cases"]:
                check_single_state(case, f"{fixture_id}/{case['label']}")
                same_rows(case["native"]["rows"], case["source"]["rows"],
                          f"{fixture_id}/{case['label']}/native from source")
                same_rows(case["S"]["rows"], case["native"]["rows"],
                          f"{fixture_id}/{case['label']}/S from native")
                scope_count += 1
        elif fixture_id == "binary_heavy_tie_and_decimal_equality":
            for state in fixture["states"]:
                check_common_state(state, f"{fixture_id}/{state['label']}")
                scope_count += 1
            binary = fixture["states"][0]
            binary_source = binary["source_tables"][0]["population"]
            binary_native = binary["native_populations"][0]["population"]
            binary_survivor = binary["survivor_populations"][0]["population"]
            check_native_from_source(binary_native, binary_source["rows"], binary_source["layout"],
                                     binary_source["layout"], "binary tie native rows")
            same_rows(binary_survivor["rows"], binary_native["rows"], "binary tie S from native")
            replay_decimal_noop(fixture)
            replay_weighting_control(fixture["index_event_weighting_control"])
            transition_count += len(fixture["states"][1]["post_baseline_inputs"]["operations"])
            transition_count += len(fixture["index_event_weighting_control"]["applied_child_key_event_trace"])
            scope_count += len(fixture["index_event_weighting_control"]["state_snapshots"])
        else:
            raise AssertionError(f"unrecognized fixture {fixture_id!r}")

    lower = packet["lower_only_capture"]
    require(lower["physical_input_denominator"] == "unavailable",
            "lower-only physical denominator must remain unavailable")
    require(lower["unavailable_must_not_be_encoded_as_zero"] is True,
            "lower-only unavailable state must not be represented as zero")
    return scope_count, transition_count


def main():
    packet = json.loads(PACKET.read_text(encoding="utf-8"))
    scopes, transitions = check_packet(packet)
    print(f"C01 literal fixture reference: PASS ({scopes} scopes, {transitions} replayed inputs)")


if __name__ == "__main__":
    main()
