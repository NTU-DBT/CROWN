# `tools/run_input_specialization.py` — block usage map

[Source](../../../../tools/run_input_specialization.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `b7e674c84bc7997c7bc13c2f49e86cf7a0734e7e7918cb9e3cb8b2d3575fd6e7`. 301 lines partitioned into 17 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../tools/run_input_specialization.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 24–25](../../../../tools/run_input_specialization.py#L24) | Callable definition: def save(path, value, exclusive=False): | calls open, write, dumps · [reviewed contract](#b0002) |
| [B0003 · 26–27](../../../../tools/run_input_specialization.py#L26) | Explanatory comments or spacing. |  |
| [B0004 · 28–64](../../../../tools/run_input_specialization.py#L28) | Callable definition: def cases(widths): | calls add, edit, append, range; returns result; growth insert; 10 loop sites · [reviewed contract](#b0004) |
| [B0005 · 65–66](../../../../tools/run_input_specialization.py#L65) | Explanatory comments or spacing. |  |
| [B0006 · 67–92](../../../../tools/run_input_specialization.py#L67) | Callable definition: def oracle(case): | calls connect, quote, replace, join; returns '"' + value.replace('"', '""') + '"'; {tuple(bool(cell) if kind == 'boolean' else cell for cell, ki…; growth insert; 13 loop sites · [reviewed contract](#b0006) |
| [B0007 · 93–94](../../../../tools/run_input_specialization.py#L93) | Explanatory comments or spacing. |  |
| [B0008 · 95–96](../../../../tools/run_input_specialization.py#L95) | Callable definition: def timing(value, verify): | calls require, type; guard require(value is None if verify else type(value) is int and value &gt;= 0, 'invalid verify/measure pha… · [reviewed contract](#b0008) |
| [B0009 · 97–98](../../../../tools/run_input_specialization.py#L97) | Explanatory comments or spacing. |  |
| [B0010 · 99–102](../../../../tools/run_input_specialization.py#L99) | Callable definition: def unordered(value): | calls canonical, require, len, set; guard require(len(keys) == len(set(keys)), 'duplicate native output record'); returns sorted(keys); 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 103–104](../../../../tools/run_input_specialization.py#L103) | Explanatory comments or spacing. |  |
| [B0012 · 105–149](../../../../tools/run_input_specialization.py#L105) | Callable definition: def inspect(case, ask, report, expected, paths, reference=None): | calls require, digest, startswith, all; guard require(report\['kind'\] == 'b04_input_specialization_report_v1' and report\['schema_version'\] == 1 and; returns {'identity': identity, 'counts': counts\[-1\]}; 10 loop sites · [reviewed contract](#b0012) |
| [B0013 · 150–151](../../../../tools/run_input_specialization.py#L150) | Explanatory comments or spacing. |  |
| [B0014 · 152–287](../../../../tools/run_input_specialization.py#L152) | Callable definition: def run(args): | calls require, sched_getaffinity, len, set; guard require(args.preflight_only or args.cpu is not None, 'controlled specialization timing requires exp…; returns experiment.invoke(label, argv); None, None; 30 loop sites · [reviewed contract](#b0014) |
| [B0015 · 288–289](../../../../tools/run_input_specialization.py#L288) | Explanatory comments or spacing. |  |
| [B0016 · 290–296](../../../../tools/run_input_specialization.py#L290) | Callable definition: def main(): | calls ArgumentParser, add_argument, run, parse_args; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 297–301](../../../../tools/run_input_specialization.py#L297) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0017) |

## B0001

[Lines 1–23](../../../../tools/run_input_specialization.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L23:sha256:c95f01fe5e4b203bd9ae3e6f5ec82546c68a89b2ada7d6dde528d4d5e3c999fc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the cold study dependencies and exact execution/output identities. |
| inputs / outputs | Existing Experiment/build provenance/canonical JSON/exact ratio/SQLite helpers; fixed mode-key map and output protocol. |
| invariants | No wrapper claims compiled source equivalence from mode labels alone; later captures bind actual native hashes/mode/work. |
| ownership | Module owns immutable conventions; no native process starts on import. |
| failure | Import/dependency errors stop script before study creation. |
| cost | Cold Python imports; no native per-input hook. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0002

[Lines 24–25](../../../../tools/run_input_specialization.py#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L25:sha256:cc64daad1ce952f1a0c80b5ae4db2b7e426e9f3c501a669047e2f788e3b2e090
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write reviewable JSON, optionally refusing an existing destination. |
| inputs / outputs | Path/value/exclusive flag; pretty sorted JSON plus newline. |
| invariants | Frozen source/request/oracle/manifest writes use exclusive mode; only live experiment checkpoints use replacement. |
| ownership | File context owns output handle; caller owns JSON. |
| failure | Filesystem/encoding failures propagate; no fallback destination. |
| cost | Linear serialized bytes; outside measured native phase. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0004

[Lines 28–64](../../../../tools/run_input_specialization.py#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L64:sha256:4f298d51fd026d4f7b8d60238728ab8c87ec41154f8fd874bca124c76a27c78b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate bounded SQL-only matched cohorts rather than handwritten executable registrations. |
| inputs / outputs | Distinct finite widths; seven SQL shapes with source schemas, real phased set events and output types. Catalog wire columns use bool, while oracle output_types retain the explicit boolean conversion tag. |
| invariants | Same per-case SQL and physical trace feed both input modes and both backends. Duplicate insert/absent erase remain real no-op obligations. Join-only, predicates, casts/repeats/constants, NULL logic, aliases, EXISTS and constant false are retained. |
| ownership | Ordinary Python dictionaries/lists own cohort data; no program callbacks or native instructions are supplied. |
| failure | Caller validates width/count grants before generation; allocations may fail normally. |
| cost | O(width) facts/events per shape; independent oracle/output costs can grow with results. |
| Design | [docs/sql_normalization.md](../../../sql_normalization.md), [docs/sql_support.md](../../../sql_support.md), [docs/scalars.md](../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../src/frontend/sql_scalar.hpp), [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0006

[Lines 67–92](../../../../tools/run_input_specialization.py#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L92:sha256:186a016bbe5ff6d54404a6c2ea87e1fcfe892b1c50916c8d600a0d70590db85f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute every prefix and signed set difference using independent SQLite. |
| inputs / outputs | Case SQL/catalog/events; initial result rows and each physical-prefix snapshot/deletion/insertion record. |
| invariants | Physical relations enforce UNIQUE full nonnull row set semantics. INSERT OR IGNORE and exact-row deletes implement noops. Query rows become sets, and declared boolean outputs are converted from SQLite integers. Expected deltas derive solely from before/after SQL sets. |
| ownership | In-memory SQLite connection is local and always closed; returned ordinary JSON owns expected values. |
| failure | SQLite/schema/type/allocation failures fail preflight; no native answer is substituted as oracle. |
| cost | Full SQL recomputation per prefix intentionally charged as correctness setup, never measured execution timing. |
| Design | [docs/sql_normalization.md](../../../sql_normalization.md), [docs/sql_support.md](../../../sql_support.md), [docs/scalars.md](../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../src/frontend/sql_scalar.hpp), [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0008

[Lines 95–96](../../../../tools/run_input_specialization.py#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L95-L96:sha256:eaa5481ea839be91e95eba4ee54b0a6239b2a28f0632a4cfe357934d3df82c32
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject malformed phase clocks before a native report enters study summaries. |
| inputs / outputs | One reported clock scalar and verify-mode flag; accepts only null for verify or an exact nonnegative Python integer for measure. |
| invariants | Booleans, floats, negative integers and measured nulls are rejected. This cold receiver guard does not validate clock accuracy, quiescence or turn a correctness run into performance evidence. |
| ownership | Borrows one JSON scalar; owns no native state or timing source. |
| failure | ValueError stops receiving; caller retains actual raw report and failed/unverified experiment row. |
| cost | Constant cold scalar/type check per setup/pass/epoch clock; no engine hook. |
| Design | [docs/measurement.md](../../../measurement.md), [Refactor.md §14.1–14.4](../../../../Refactor.md) |

## B0010

[Lines 99–102](../../../../tools/run_input_specialization.py#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L99-L102:sha256:64a08cf76b31321bf8b122b3986f690e80c20b6ff70cc515ff2b29a30b5d94d0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare unordered output records without losing multiplicity errors. |
| inputs / outputs | JSON record sequence; sorted canonical JSON keys. |
| invariants | Duplicate native records reject before set-like ordering; canonical booleans remain distinct from integers. |
| ownership | Owns canonical key list; input remains borrowed. |
| failure | Duplicate/schema/encoding errors stop receiving. |
| cost | O(records log records plus encoded bytes) in cold correctness checking. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0012

[Lines 105–149](../../../../tools/run_input_specialization.py#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L149:sha256:9c68c0b5f970fe9b416d34de4e9fd403b9edb0d650d4b28718fc5756a4b2be13
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Receive native reports only after source/mode/tree/output/work obligations match. |
| inputs / outputs | Case, exact request/report, independent SQLite expected prefix frames, bound file paths/catalog digest and optional prior mode reference. |
| invariants | Requires actual kind/request/mode/protocol, SQL/input/catalog digests and constant route. Interpreter must have no extra tables; fresh owners preserve actual instruction counts/table bytes. All verify clocks null. Every prefix coordinates/phase/signed rows/snapshot/counts match oracle; paired native work and physical/source/tree/backend identity stay equal. Initial and per-input full drains are explicit. Every setup/pass/epoch clock must be null in verify or an exact nonnegative integer in measure; measured initial/per-input captures must be null. Native work must be an exact nonnegative integer. |
| ownership | Borrows input JSON/files; returns small owned identity/count reference for later repetitions. |
| failure | Any mismatch raises ValueError; caller retains raw command and unverified row, preventing eligible timing. |
| cost | Cold hash/canonical/sort/traversal work per captured report; not charged as native maintenance. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0014

[Lines 152–287](../../../../tools/run_input_specialization.py#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L152-L287:sha256:921741dedbd3c64b9a257b83006f20eb4eedf32a2e96155d0863a3edc335cefd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all matched correctness gates before a deterministic balanced measured schedule. |
| inputs / outputs | Explicit source/build/binaries, finite widths/backends/process/raw grants, CPU, warmups/repetitions and exclusive new output directory. |
| invariants | Controlled timing requires allowed explicit CPU. Pins real build files/units/dependencies/compiler/harness and launchers. Declares all case/backend/mode variants; every prefix verified before any measure. Source/catalog/trace/oracle/requests/manifest hash freeze precedes timing and rechecks before each native call. Failed/stopped children remain explicit and block timing when preflight fails; semantic failure leaves retained unverified row and failed study. Each repetition has one child per retained variant; slower outcomes are not removed. |
| ownership | New task directory owns raw stdout/stderr/resource/commands/experiment and frozen inputs; exclusive creation protects prior studies. Existing SDK/source trees are read-only. Native owners live only in children. |
| failure | Native failures/timeouts/raw limits are retained; mismatch/closure/IO failures checkpoint failed status and propagate. No retry, silent candidate removal or unavailable=zero score. |
| cost | Whole-child GNU-time RSS/wall includes compiler/warmups/serialization; native phase clocks are distinct. Summaries retain base-inclusive preparation/work/table and real account scopes, shared executable size; exact ratios use matched physical-input counts. End rehashes build files, units, dependencies, compiler, harness, launchers and frozen inputs. This finite input-execution ablation does not itself close all B04 axes. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json), [docs/query_memory.md](../../../query_memory.md), [docs/memory_accounts.md](../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../include/crown/storage/index_work.hpp) |

## B0016

[Lines 290–296](../../../../tools/run_input_specialization.py#L290); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L290-L296:sha256:636737988e85b81e3d07dfd08d38775d47a970de458cbc8e4359a2b954841835
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a bounded direct matched-study CLI. |
| inputs / outputs | Required source/build/Crown/collector/client/output; optional widths/backends/CPU/warmups/reps/process/raw caps/seed/preflight-only. |
| invariants | Argparse backend names are closed; run validates finite grants and CPU before build inspection. Preflight-only performs correctness, not eligible measurements. |
| ownership | Argument paths are values; run owns new artifacts. |
| failure | Argument/validation failures produce nonzero outer exit. |
| cost | Cold parsing only. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |

## B0017

[Lines 297–301](../../../../tools/run_input_specialization.py#L297); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L297-L301:sha256:af15d3992bff6e82d675e308c99fb1111187aa57cbcdc5145e69ae95685057ec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use one final diagnostic boundary for the cold experiment script. |
| inputs / outputs | __main__ executes CLI; exceptions print a concise failure and exit one. |
| invariants | No failed process is relabelled complete; run checkpoint/raw files remain reviewable. |
| ownership | OS/Python release open handles; native processes are reaped by Experiment. |
| failure | Exception boundary emits stderr and nonzero status. |
| cost | Constant outer handling; no retry framework. |
| Design | [Refactor.md §14.1–14.4](../../../../Refactor.md), [docs/measurement.md](../../../measurement.md), [build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json](../../../../build/verification/v61-b04-completion-audit-v1/requirement-matrix-v1.json) |
