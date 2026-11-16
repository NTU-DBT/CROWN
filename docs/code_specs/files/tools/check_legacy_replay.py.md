# `tools/check_legacy_replay.py` — block usage map

[Source](../../../../tools/check_legacy_replay.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `c7b22ab0cb4db88bb10b1bfefa4e22c00d4f64f4b4960b648ad43f3c36a4a304`. 226 lines partitioned into 23 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../tools/check_legacy_replay.py#L1) | Imports dependencies. | growth insert; 3 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 20–23](../../../../tools/check_legacy_replay.py#L20) | Callable definition: def check(condition, message): | calls ValueError; guard def check(condition, message): · [reviewed contract](#b0002) |
| [B0003 · 24–25](../../../../tools/check_legacy_replay.py#L24) | Explanatory comments or spacing. |  |
| [B0004 · 26–30](../../../../tools/check_legacy_replay.py#L26) | Callable definition: def join3(relations): | calls G1, G2, G3; returns {(a, b, c, d) for a, b in relations\['G1'\]; 3 loop sites · [reviewed contract](#b0004) |
| [B0005 · 31–32](../../../../tools/check_legacy_replay.py#L31) | Explanatory comments or spacing. |  |
| [B0006 · 33–47](../../../../tools/check_legacy_replay.py#L33) | Callable definition: def scala_rows(stdout): | calls splitlines, startswith, loads, check; guard check(set(row) == {'event', 'delta_base64', 'rows'}, 'unexpected Scala record fields'); returns result; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 48–49](../../../../tools/check_legacy_replay.py#L48) | Explanatory comments or spacing. |  |
| [B0008 · 50–65](../../../../tools/check_legacy_replay.py#L50) | Callable definition: def signed_rows(encoded): | calls Counter, b64decode, decode, splitlines; guard check(match is not None, 'unexpected signed Scala output line'); returns result; 4 loop sites; source comment (unverified): # JoinedAttributes prints named pairs, unlike the stale published test · [reviewed contract](#b0008) |
| [B0009 · 66–67](../../../../tools/check_legacy_replay.py#L66) | Explanatory comments or spacing. |  |
| [B0010 · 68–100](../../../../tools/check_legacy_replay.py#L68) | Callable definition: def verify_scala(trace, stdout): | calls splitlines, scala_rows, check, len; guard check(lines and len(actual) == len(lines), 'missing or extra Scala event records'); returns dict(events=len(lines), signed_records=emitted, snapshots=snapshots); growth insert; 8 loop sites · [reviewed contract](#b0010) |
| [B0011 · 101–102](../../../../tools/check_legacy_replay.py#L101) | Explanatory comments or spacing. |  |
| [B0012 · 103–108](../../../../tools/check_legacy_replay.py#L103) | Callable definition: def five_edge_paths(edges): | calls list, range; returns paths; 3 loop sites · [reviewed contract](#b0012) |
| [B0013 · 109–110](../../../../tools/check_legacy_replay.py#L109) | Explanatory comments or spacing. |  |
| [B0014 · 111–132](../../../../tools/check_legacy_replay.py#L111) | Callable definition: def graph_milestones(trace, deletions): | calls set, enumerate, splitlines, len; guard check(len(fields) == 3 and fields\[0\] in allowed and all(re.fullmatch(r'\[1-9\]\[0-9\]*', v) for v in fi…; growth insert; 3 loop sites · [reviewed contract](#b0014) |
| [B0015 · 133–134](../../../../tools/check_legacy_replay.py#L133) | Explanatory comments or spacing. |  |
| [B0016 · 135–155](../../../../tools/check_legacy_replay.py#L135) | Callable definition: def cpp_frames(stdout, query): | calls splitlines, pop, check, len; guard check(lines\[:2\] == \[f'Query: {query}', 'Algorithm: Crown'\], 'unexpected C++ query or algorithm head…; returns frames; 1 loop sites; source comment (unverified): # Published main emits one final blank line. · [reviewed contract](#b0016) |
| [B0017 · 156–157](../../../../tools/check_legacy_replay.py#L156) | Explanatory comments or spacing. |  |
| [B0018 · 158–166](../../../../tools/check_legacy_replay.py#L158) | Callable definition: def verify_cpp(trace, stdout): | calls dict, len, graph_milestones, cpp_frames; guard check(milestones and len(frames) == len(milestones), 'missing or extra C++ milestone output'); returns dict(milestones=milestones); growth insert; 3 loop sites · [reviewed contract](#b0018) |
| [B0019 · 167–168](../../../../tools/check_legacy_replay.py#L167) | Explanatory comments or spacing. |  |
| [B0020 · 169–197](../../../../tools/check_legacy_replay.py#L169) | Callable definition: def verify_grouped(trace, stdout, replacements): | calls Counter, graph_milestones, cpp_frames, check; guard check(wanted and len(frames) == len(wanted), 'missing or extra line5gc milestones'); returns dict(milestones=totals, output_records=records, zero_replacements=removals,; growth new; 5 loop sites; source comment (unverified): # A record carries the new absolute count, including zero for · [reviewed contract](#b0020) |
| [B0021 · 198–199](../../../../tools/check_legacy_replay.py#L198) | Explanatory comments or spacing. |  |
| [B0022 · 200–222](../../../../tools/check_legacy_replay.py#L200) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, check; guard check(not args.output.exists(), 'refusing to overwrite an existing evidence report'); 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 223–226](../../../../tools/check_legacy_replay.py#L223) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0023) |

## B0001

[Lines 1–19](../../../../tools/check_legacy_replay.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:2cdbf6e6f7313999195212f5aa832918e264f1de5ca26a04704e13912a70bf28
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define a tiny offline verifier for captured Scala/Flink and C++ CROWN output, with no external-baseline launch or timing role. |
| inputs / outputs | Imports and module documentation state the four admitted modes: Scala L3, C++ line5cd insert-only, line5gc full groups, and line5gc absolute replacements. |
| invariants | Each mode is a narrow fixture contract documented in docs/legacy_baselines.md; build/run provenance comes from separate receipts, not this checker. |
| ownership | Module-level imports and constants retain no process, filesystem, or baseline state. |
| failure | Import or syntax failures stop execution before a pass report exists. |
| cost | Python module initialization only; no baseline process is launched. |
| Design | [docs/legacy_baselines.md](../../../legacy_baselines.md), [Refactor.md §11.11 B01 and §14.3–14.4](../../../../Refactor.md), [tools/run_legacy_baseline.py](../../../../tools/run_legacy_baseline.py) |

## B0002

[Lines 20–23](../../../../tools/check_legacy_replay.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L23:sha256:6ce732caa6f94390a8925d42eb4cc8b0b188500be03b6f6c7f44ce5070d96e57
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a non-optimizable verification failure when a replay condition is false. |
| inputs / outputs | Accepts a condition object and message; evaluates Python truthiness once, returns on a true condition and raises ValueError otherwise. |
| invariants | Uses an explicit condition rather than assert, so checker guards remain active under Python -O. |
| ownership | Borrows its predicate/message and retains nothing. |
| failure | A false condition raises ValueError before report publication. |
| cost | One branch per validation; exception construction occurs only on failure. |
| Design | [tools/check_legacy_replay.py](../../../../tools/check_legacy_replay.py), [tests/integration/legacy_replay_checker.py](../../../../tests/integration/legacy_replay_checker.py) |

## B0004

[Lines 26–30](../../../../tools/check_legacy_replay.py#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L30:sha256:94c4ddca040623c19e68a2bec3b79865b377b230b0ee26611cb1dbfd831c96b9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the literal set result of G1(A,B) join G2(B,C) join G3(C,D) for one small snapshot. |
| inputs / outputs | Reads relation sets keyed G1/G2/G3 and returns a set of four-integer rows that agree on the shared B and C coordinates. |
| invariants | Set semantics suppress duplicate derivations in the result; input event signs and relation updates are handled by verify_scala. |
| ownership | The returned Python set owns its row tuples; the input mapping is borrowed. |
| failure | Missing relation keys or malformed rows propagate as ordinary Python exceptions. |
| cost | Direct triple nested relation iteration has cubic worst-case work O(\|G1\|\|G2\|\|G3\|) per call, plus result storage; this oracle is for tiny fixtures. |
| Design | [docs/legacy_baselines.md](../../../legacy_baselines.md), [Refactor.md §11.11 B01](../../../../Refactor.md), [tools/check_legacy_replay.py](../../../../tools/check_legacy_replay.py) |

## B0006

[Lines 33–47](../../../../tools/check_legacy_replay.py#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L47:sha256:d0ff9572a67ed8b4783a5ae34a2cc514b6e7455581de562decbf5bade7283c5b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse captured Scala stdout into per-event JSON envelopes and exactly one close diagnostic. |
| inputs / outputs | Returns JSON rows with exactly event/delta_base64/rows fields; non-JSON lines must match the legacy Process Function close-footer grammar. |
| invariants | Exactly one footer is required; unrecognized lines, missing/extra fields, or duplicate/missing footer fail before semantic comparison. |
| ownership | Returns an owning list of parsed JSON objects; input stdout is borrowed. |
| failure | Malformed JSON, envelope shape, footer text, or footer count raises through check/json parsing. |
| cost | Linear in captured stdout bytes and number of envelopes, plus parsed object storage. |
| Design | [docs/legacy_baselines.md](../../../legacy_baselines.md), [tests/legacy_baselines/captures.json](../../../../tests/legacy_baselines/captures.json), [tests/legacy_baselines/scala-l3.stdout.jsonl](../../../../tests/legacy_baselines/scala-l3.stdout.jsonl) |

## B0008

[Lines 50–65](../../../../tools/check_legacy_replay.py#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L65:sha256:5c78bfe47391ccbce50cad3f9276190e71f136d8d7e289d99b447a208cfb0740
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode a captured Base64 signed-delta payload into a multiplicity-preserving named tuple counter. |
| inputs / outputs | Validates Base64, decodes UTF-8 signed lines, validates four named A–D integer pairs, and returns a Counter keyed by sign and A/B/C/D value order. |
| invariants | Raw signed multiplicity is retained; each accepted output row has four names exactly covering A through D, and output order is normalized by field name. |
| ownership | The returned Counter owns its keys/counts; the encoded string is borrowed. |
| failure | Invalid Base64/UTF-8, sign-line grammar, pair spelling, or schema raises a check/decode error. |
| cost | Linear in decoded capture size and number of emitted pairs, plus Counter storage. |
| Design | [docs/legacy_baselines.md](../../../legacy_baselines.md), [tools/support/CrownReplay.scala](../../../../tools/support/CrownReplay.scala), [tests/legacy_baselines/scala-l3.stdout.jsonl](../../../../tests/legacy_baselines/scala-l3.stdout.jsonl) |

## B0010

[Lines 68–100](../../../../tools/check_legacy_replay.py#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L100:sha256:125458c07e82b06ef9d9da9e1dca895b2299004b329e1d14aaed84db9c8afeac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the Scala L3 event stream, every raw signed delta, and every genuine current-result snapshot against a direct tiny join. |
| inputs / outputs | Consumes comma-separated +/- G1/G2/G3 two-value events and the captured per-event envelopes; updates three relation sets, recomputes join3, checks exact event sequence, strict ASCII signed-decimal int32 tokens, and compares Counters for signed changes plus snapshot rows. |
| invariants | Only unique inserts and present deletes are admitted; int32 bounds and Scala decimal token spelling are checked; every input event must have one matching output record; multiplicities and snapshots are compared without deduplicating captured rows. |
| ownership | The helper owns its relation sets, current row set, output summaries and counters; trace/stdout strings are borrowed. |
| failure | Bad schema/sign/domain, duplicate insert, absent delete, event order, delta multiplicity, or snapshot mismatch raises before a pass report. |
| cost | Recomputes the literal triple join after every event, retaining parsed captures and per-event summaries plus current result sets. Cost includes relation/output sizes and scalar/integer widths; there is no general CPU or memory cap. |
| Design | [docs/legacy_baselines.md](../../../legacy_baselines.md), [Refactor.md §11.11 B01](../../../../Refactor.md), [tools/support/CrownReplay.scala](../../../../tools/support/CrownReplay.scala), [benchmarks/legacy/replay/scala-l3-mixed.txt](../../../../benchmarks/legacy/replay/scala-l3-mixed.txt), [tests/legacy_baselines/scala-l3.stdout.jsonl](../../../../tests/legacy_baselines/scala-l3.stdout.jsonl) |

## B0012

[Lines 103–108](../../../../tools/check_legacy_replay.py#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L108:sha256:61194afd211e0d3a2149e6f48fa8a6c85a39add5cc25b3f39683cb3133b0dec9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize all five-copy directed-edge join paths for a small graph snapshot. |
| inputs / outputs | Starts with each edge and extends matching endpoints four times, returning each six-vertex/five-edge path as a list entry. |
| invariants | Uses a list rather than a set so endpoint witnesses and repeated paths remain available for bag-path and grouped-count checks. |
| ownership | Returns an owning list of path tuples; the input edge set is borrowed. |
| failure | Invalid edge tuple contents fail through ordinary indexing/comparison errors. |
| cost | The direct five-copy self-join has O(E^5) worst-case work and materialized-path memory, including intermediate lists; it is limited to tiny benchmark fixtures. |
| Design | [docs/legacy_baselines.md](../../../legacy_baselines.md), [Refactor.md §11.11 B01](../../../../Refactor.md), [tools/check_legacy_replay.py](../../../../tools/check_legacy_replay.py) |

## B0014

[Lines 111–132](../../../../tools/check_legacy_replay.py#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L132:sha256:0d9bb18ca6a3d548d9beae0bacca6bc1d0a5a05433dcc295e30cae7a0012f2e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a graph update trace and yield direct five-edge path snapshots only at explicit milestone markers. |
| inputs / outputs | Reads positive integer edge endpoints, admitting only inserts or +/- according to deletions; each '*' yields its line number, edge count, and materialized five_edge_paths result. |
| invariants | Insertions must be unique, deletions must name present edges, IDs must fit uint32, and the stream must end at an observed milestone with no unobserved update tail. |
| ownership | The helper owns the mutable edge set and yields each milestone's newly materialized path list to its consumer. |
| failure | Malformed signs/IDs, duplicate or absent operations, unqualified events, or a final update without a trailing '*' raises through check. |
| cost | Scans trace lines and recomputes/materializes the fifth-power path join per milestone; the accepted traces are deliberately tiny. |
| Design | [docs/legacy_baselines.md](../../../legacy_baselines.md), [benchmarks/legacy/replay/line5cd-insert-only.txt](../../../../benchmarks/legacy/replay/line5cd-insert-only.txt), [benchmarks/legacy/replay/line5gc-mixed.txt](../../../../benchmarks/legacy/replay/line5gc-mixed.txt) |

## B0016

[Lines 135–155](../../../../tools/check_legacy_replay.py#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L155:sha256:c0b66fcb214efcd1fde9e207107c699b26abdd9624b2d59ec0c1900f40f34a07
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Split captured C++ query output into complete milestone frames while validating diagnostic envelopes. |
| inputs / outputs | Requires the query and algorithm headers, then frames output records at Running Time lines paired with Memory Usage lines. |
| invariants | Timing and memory values are syntax-checked diagnostics only; every result frame must terminate with the expected pair and no dangling records. |
| ownership | Returns an owning list of frame-line lists; stdout string is borrowed. |
| failure | Wrong query/algorithm, malformed time/memory diagnostic, missing pair, or unterminated frame raises through check. |
| cost | Linear in captured stdout bytes and frame count, with stored frame strings. |
| Design | [docs/legacy_baselines.md](../../../legacy_baselines.md), [tests/legacy_baselines/captures.json](../../../../tests/legacy_baselines/captures.json), [tests/legacy_baselines/line5cd.stdout.txt](../../../../tests/legacy_baselines/line5cd.stdout.txt), [tests/legacy_baselines/line5gc-full.stdout.txt](../../../../tests/legacy_baselines/line5gc-full.stdout.txt) |

## B0018

[Lines 158–166](../../../../tools/check_legacy_replay.py#L158); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L158-L166:sha256:00f1355e6c90bf4bc514fcecc44ce94d91f2b2cf93e29eb1860cd797be42db3f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check insert-only line5cd output at every observed milestone against distinct internal quadruples from five-edge paths. |
| inputs / outputs | Computes direct graph milestones, counts distinct path coordinates p\[1:5\] separately from total path witnesses, parses line5cd frames, and compares the printed result for every milestone. |
| invariants | Requires at least one milestone and an exact frame count; line5cd accepts only the insert-only contract, not deletion or delta-mode semantics. |
| ownership | Returns milestone evidence values; path lists and frames are local to verification. |
| failure | Unsupported graph operation, missing frame, or any count mismatch raises before report creation. |
| cost | Materializes O(E^5) path lists per milestone, then computes set counts; it is suitable only for tiny traces and makes no timing claim. |
| Design | [docs/legacy_baselines.md](../../../legacy_baselines.md), [benchmarks/legacy/replay/line5cd-insert-only.txt](../../../../benchmarks/legacy/replay/line5cd-insert-only.txt), [tests/legacy_baselines/line5cd.stdout.txt](../../../../tests/legacy_baselines/line5cd.stdout.txt) |

## B0020

[Lines 169–197](../../../../tools/check_legacy_replay.py#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L169-L197:sha256:8d940279f8db50185e2aa3a3a41bc07158e803c7ab8f1e7f5f649a8ba153b77a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check line5gc full grouped outputs or absolute-count replacement outputs at every observed milestone. |
| inputs / outputs | Builds expected Counters from five-edge paths grouped by middle edge; full mode resets to each complete nonzero group map, while replacement mode folds absolute counts and treats zero records as removals. |
| invariants | The final modeled state must equal the expected group Counter at every milestone; replacement records are absolute counts, not signed aggregate deltas; insertion/deletion qualification and final milestone checks come from graph_milestones. |
| ownership | Expected maps, folded state, and summaries are local owning values. |
| failure | Malformed group lines, duplicate/zero full groups, or state mismatch fails before publishing a pass. |
| cost | Direct path enumeration is O(E^5) in time/materialized paths; grouped maps and all milestone summaries are retained for tiny traces. |
| Design | [docs/legacy_baselines.md](../../../legacy_baselines.md), [benchmarks/legacy/replay/line5gc-mixed.txt](../../../../benchmarks/legacy/replay/line5gc-mixed.txt), [tests/legacy_baselines/line5gc-full.stdout.txt](../../../../tests/legacy_baselines/line5gc-full.stdout.txt), [tests/legacy_baselines/line5gc-replacements.stdout.txt](../../../../tests/legacy_baselines/line5gc-replacements.stdout.txt) |

## B0022

[Lines 200–222](../../../../tools/check_legacy_replay.py#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L200-L222:sha256:63aaa84290077ce91b0afe2f52a8cb37298827e840f2e736d705e6e9788c96f1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select an admitted replay mode, verify exact trace/capture bytes, and publish an offline report only after successful comparison. |
| inputs / outputs | Requires baseline/trace/stdout/output CLI paths; reads both inputs as bytes, dispatches to the chosen verifier, records their hashes plus the checker hash, and creates a JSON report with baseline_launched=false and timing_eligible=false. |
| invariants | Only the four named modes are accepted; output must not already exist; no external baseline is launched, timing is ineligible, and pass publication occurs after verifier success. |
| ownership | Trace/stdout byte strings and report values are local; output path is caller-selected; no baseline or capture is mutated. |
| failure | Missing/unreadable inputs, UTF-8/JSON/verification errors, existing output, or exclusive-create failure exits without an intentional pass report. |
| cost | Reads and hashes full captures in memory and performs cubic/fifth-power tiny-oracle work; exclusive mode x prevents overwrite but is not atomic content publication and may leave a partial file on I/O failure. |
| Design | [docs/legacy_baselines.md](../../../legacy_baselines.md), [Refactor.md §11.11 B01](../../../../Refactor.md), [tools/run_legacy_baseline.py](../../../../tools/run_legacy_baseline.py), [tests/legacy_baselines/captures.json](../../../../tests/legacy_baselines/captures.json) |

## B0023

[Lines 223–226](../../../../tools/check_legacy_replay.py#L223); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L223-L226:sha256:239f34ccf0a25c3afeefe82507f70b0ffbbcbf03dd6930292ca35d6b41937a29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke main only when this module is executed directly. |
| inputs / outputs | The standard Python main guard invokes main when run as a script. |
| invariants | Importing the module does not launch a baseline; direct execution runs only the offline checker selected by its CLI. |
| ownership | No retained state beyond the process. |
| failure | Exceptions/nonzero errors propagate to the process exit. |
| cost | One condition and call; the interpreter supplies normal-return or uncaught-failure process status. |
| Design | [tools/check_legacy_replay.py](../../../../tools/check_legacy_replay.py), [docs/legacy_baselines.md](../../../legacy_baselines.md) |
