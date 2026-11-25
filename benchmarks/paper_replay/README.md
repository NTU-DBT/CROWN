# Paper replay benchmarks (native vs. original Flink)

Small, self-contained tooling used to diagnose and fix native performance on the
paper workloads (November 2026). It reuses the campaign bindings and inputs under
`build/experiments/paper-serial-comparison-20261116-v1` and
`build/experiments/paper-completion-audit-20261116-v1`.

- `build.sh BUILD_DIR OUT_DIR` builds the four replay harnesses (`paper_native_routed`,
  `_snb`, `_fallback`, `_aggregate`) against the static libraries of a CMake build
  directory (e.g. a RelWithDebInfo build with `-O3 -g -fno-omit-frame-pointer`).
  The harness sources are copies of the campaign's `native_replay_*.cpp`; the routed
  and SNB harnesses also honour `CROWN_OBS_OFF=1` (observation mode off).
- `run.py --bin OUT_DIR --out RUNS --timeout S --jobs N --filter=SUBSTR ...` builds each
  case's request from the campaign binding exactly like `run_native_stream_v3.py`,
  runs it and writes `RUNS/<case>/result.json` plus `RUNS/summary.json`.
- `flink_medians.json`: original Flink p=1 accumulate/wall medians per case.
- `sampler.cpp` + `prof_report.py`: an in-process SIGPROF frame-pointer sampler (perf and
  ptrace are unavailable on this host). Run a harness with `CROWN_PROF=out.txt`, then
  `python3 prof_report.py BINARY out.txt 40` for self/inclusive profiles.
- `CROWN_GC=blocking` (default) runs the keyed core single-threaded, collecting
  garbage when its retired-memory pool is full; `CROWN_GC=background` adds one
  collector thread. `CROWN_GC_POOL` sets the blocking-mode pool size (bytes,
  with an optional `K`/`M`/`G`/`T` suffix; default `64M`); `unlimited` turns
  collection off unless the engine memory budget would be exceeded. Reports
  carry `gc_mode`, `threads` (the process thread count at the end of the
  replay loop: 1 or 2) and `gc` (pool size and process-wide collections,
  retired, freed and pending bytes at the end of the loop).
- The aggregate harness runs fused keyed batches (`sql_aggregate::Options::fused`,
  docs/keyed_core.md); `CROWN_AGGREGATE_FUSED=0` keeps the layered
  SqlRows/Weighted path. Reports carry `fused`.
- The fallback harness reports `cyclic_algorithm` (`ghd` when the query
  decomposes, else `support`; `CROWN_CYCLIC_ENGINE=support` forces the
  support-count engine). Outside delta mode it maintains without per-epoch
  answer changes (`fallback::Options::answer_changes`). Snapshots stream
  (`fallback::Runtime::visit`): each row is a result tuple, unsorted.
- Per-phase timers (`decode_ns`, `apply_ns`, `output_ns`, ...) read the TSC
  (`tick_clock.hpp`, calibrated against steady_clock at start). End-to-end time
  is measured outside, by GNU time.
- Timing runs use `--jobs 1` with nothing else running on the host: concurrent
  processes share memory bandwidth and caches and distort wall times.
- Verify mode: set `"command":"verify"` and a new `"capture_file"` in a request to
  capture every delta/snapshot row; compare captures byte-for-byte across builds.

## Flat executors (`CROWN_ENGINE=flat`)

All four harnesses run the lean executors of `docs/flat_runtime.md` when the
environment has `CROWN_ENGINE=flat`:

- `FlatRuntime` for the routed and SNB set queries;
- `FlatCyclicRuntime` for the dumbbell fallback;
- `FlatCountRuntime` for star `COUNT(*)`.

The report says `"engine":"flat"`. `flat_driver.hpp` holds the shared glue.

- `CROWN_ENGINE=flat python3 run.py --bin OUT_DIR ...` times the flat engines.
- `verify_flat.py --bin OUT_DIR --out DIR [--lines N] [--window W] [--filter=...]`
  replays one stream prefix through both engines in verify mode. It then compares
  the captures block by block, with rows sorted per relation update and per
  snapshot.
  - `--window W` rewrites the prefix into a sliding window of W inserts, so
    deletions start early.
  - SNB prefixes are `--snb-scale` (default 10) times longer.
