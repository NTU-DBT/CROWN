# CROWN Next: run a new SQL query

CROWN Next is a C++23 library and local-file CLI. A supported query needs SQL,
a typed catalog and update records. It does not need a query-specific C++ class.
The Scala/Flink instructions under `crown/` describe the original paper code.

Use Linux, GCC 13 with C++23, CMake 3.25 or newer and GNU Make. This source tree
contains the pinned parser archive and JSON header; the build needs no download.
Python 3.10 or newer is used below to bind the example input. Python and a database
server are not required to run the installed CLI. Project licensing and the full
release gates remain open; this is a local development installation.

## Build and install

Run from the repository root. A new temporary directory keeps prior state separate.

```sh
demo_dir="$(mktemp -d /tmp/crown-demo.XXXXXX)"
cmake -S . -B "$demo_dir/build" -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF "-DCMAKE_INSTALL_PREFIX=$demo_dir/prefix"
cmake --build "$demo_dir/build" --parallel 2
cmake --install "$demo_dir/build"
crown_cli="$demo_dir/prefix/bin/crown"
```

## Compile and inspect

The [route-labels fixture](examples/route-labels/query.sql) joins two occurrences
of `edge` with `labels`, filters one occurrence and projects terminal/label pairs.
It exercises shared support, duplicate inserts and absent deletes. Its
[catalog](examples/route-labels/catalog.json),
[18 update templates](examples/route-labels/events.template.jsonl) and
[SQLite expectations](examples/route-labels/expected.json) are data files.
The set CLI example requires the catalog's non-null columns. `expected.json`
records the independent SQLite expectations; `verify-trace` instead runs CROWN's
separate relational reference evaluator and does not read that file.

```sh
cp docs/examples/route-labels/query.sql "$demo_dir/query.sql"
cp docs/examples/route-labels/catalog.json "$demo_dir/catalog.json"
python3 "$demo_dir/prefix/share/crown/examples/native-workflow/prepare_workflow_input.py" "$crown_cli" "$demo_dir/catalog.json" docs/examples/route-labels/events.template.jsonl "$demo_dir/updates.jsonl"
"$crown_cli" compile "$demo_dir/query.sql" "$demo_dir/catalog.json" > "$demo_dir/compiled.json"
"$crown_cli" validate-plan compiled "$demo_dir/compiled.json"
"$crown_cli" explain compiled "$demo_dir/compiled.json" --format text
"$crown_cli" verify-trace "$demo_dir/compiled.json" "$demo_dir/updates.jsonl"
```

This query's tree must report `proven_minimum`. That describes structural height,
not CPU speed or a cost optimum. `verify-trace` compares a bounded trace with the
independent relational evaluator; it does not prove every query or trace correct.
See [model and guarantees](guarantees.md) for the full boundary.

## Run, read results and resume

```sh
"$crown_cli" run "$demo_dir/compiled.json" "$demo_dir/updates.jsonl" "$demo_dir/query.root" "$demo_dir/results.sink" --events 5
"$crown_cli" snapshot "$demo_dir/compiled.json" "$demo_dir/updates.jsonl" "$demo_dir/query.root" "$demo_dir/results.sink"
"$crown_cli" results "$demo_dir/compiled.json" "$demo_dir/updates.jsonl" "$demo_dir/query.root" "$demo_dir/results.sink" --epoch 3
"$crown_cli" checkpoint "$demo_dir/compiled.json" "$demo_dir/updates.jsonl" "$demo_dir/query.root" "$demo_dir/results.sink"
"$crown_cli" restore "$demo_dir/compiled.json" "$demo_dir/updates.jsonl" "$demo_dir/query.root" "$demo_dir/results.sink" --events 13
```

After event 5 the current set is `[[3,"blue"]]`. Event 3's delta inserts that row.
Deleting one of its two edge supports at event 5 does not delete the answer.
The final restore consumes the remaining 13 records and ends at sequence 18 with
an empty result. Source offset is 1800 for `route-labels-input`.

Use fresh root/sink names for a new run. Restore uses the same complete input
prefix and existing files. The sink holds durable output; stdout is a report,
not an acknowledgement. See [CLI contracts](cli.md), [troubleshooting](troubleshooting.md)
and [the supported interfaces](guarantees.md#choose-the-interface).

## Use the installed API

Copy `PREFIX/share/crown/examples/native-workflow` into a separate directory,
configure with `-DCMAKE_PREFIX_PATH=PREFIX`, and build `crown_native_workflow`.
It accepts `run|restore QUERY.sql CATALOG.json INPUT.jsonl ROOT SINK EVENTS`;
use fresh root/sink names for this separate execution. It uses public headers and
the same query-independent session code. [CLI/package details](cli.md#local-cmake-installation-and-consumer)
and a [complete result-cursor program](cursor_example.md) show the two API styles.

To contribute another supported query, follow [the query workflow](development.md).
