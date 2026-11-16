# `tools/parser_spike/run.sh` — block usage map

[Source](../../../../../tools/parser_spike/run.sh) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `0eb630a2e1bb045de63c6485e88c7a8720469e343cc6c0f00efcf70dd0ebd429`. 57 lines partitioned into 2 blocks using `script_regions`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/workloads.md](../../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–31](../../../../../tools/parser_spike/run.sh#L1) | declares values/defaults or compile-time conditions. | source comment (unverified): #!/bin/sh · [reviewed contract](#b0001) |
| [B0002 · 32–57](../../../../../tools/parser_spike/run.sh#L32) | declares values/defaults or compile-time conditions. | source comment (unverified): # Always build from a fresh extraction of the verified archive. · [reviewed contract](#b0002) |

## B0001

[Lines 1–31](../../../../../tools/parser_spike/run.sh#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
echo "parser spike requires make" >&2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the parser-spike repository/build paths and check required host tools before changing files. |
| inputs / outputs | Uses set -eu; derives script_dir/repo_root; fixes build/work/download/archive/source paths; selects CC or cc; checks curl, sha256sum, compiler and make availability. |
| invariants | All later paths derive from the script directory beneath repository build/parser-spike; caller cwd and positional argv do not choose outputs. CC may select the compiler. This block performs prerequisite checks but does not download, delete or compile. |
| ownership | The shell process owns path variables and selected tool names; no files are opened in this block. |
| failure | Missing tools print a diagnostic to stderr and exit nonzero; set -e propagates a failing command. |
| cost | Path resolution and four command lookups only. |
| Design | [tools/parser_spike/run.sh](../../../../../tools/parser_spike/run.sh), docs/decisions/0002-parser-spike.md:58-69, tools/parser_spike/run.sh:1-31 |

## B0002

[Lines 32–57](../../../../../tools/parser_spike/run.sh#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
-o "$build_dir/parser-smoke"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fetch/verify the pinned libpg_query archive if needed, recreate its build-local source tree, build it, compile the smoke executable and run it. |
| inputs / outputs | Creates download/work dirs; conditionally curls the pinned archive to a temporary file, verifies SHA256 and moves it into the cache; always rechecks the cached archive; rm -rf’s only build/parser-spike/work/libpg_query-18.1.0; extracts, runs upstream make build, compiles parser-smoke, then executes it. |
| invariants | Network access occurs only if the pinned archive is absent; digest checks precede extraction. The deletion target is fixed below ignored build/parser-spike; no user-selected arbitrary path is removed. |
| ownership | The script owns temporary download path via trap and build-local output files; it does not clean successful archive/build artifacts, and a failed later build can leave partial outputs. |
| failure | set -e stops on failed download/hash/extraction/build/compile/smoke. The trap removes only an in-progress download temp; later build failures do not roll back cached archive or build outputs. |
| cost | One optional network download plus archive hash/extract/upstream build, one C compilation/link, and one smoke process; time/disk are host/upstream dependent and not bounded here. |
| Design | [tools/parser_spike/run.sh](../../../../../tools/parser_spike/run.sh), [tools/parser_spike/smoke.c](../../../../../tools/parser_spike/smoke.c), docs/decisions/0002-parser-spike.md:50-80, tools/parser_spike/run.sh:32-57 |
