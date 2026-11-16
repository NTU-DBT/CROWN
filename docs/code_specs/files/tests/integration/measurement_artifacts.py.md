# `tests/integration/measurement_artifacts.py` — block usage map

[Source](../../../../../tests/integration/measurement_artifacts.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `e9c3ebca37d15a2d26785592bb4cbd9ca3c8d46ca93821248360b77f2c4b6d79`. 295 lines partitioned into 13 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../../tests/integration/measurement_artifacts.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 19–21](../../../../../tests/integration/measurement_artifacts.py#L19) | Callable definition: def require(value, message): | calls RuntimeError; guard def require(value, message): · [reviewed contract](#b0002) |
| [B0003 · 22–23](../../../../../tests/integration/measurement_artifacts.py#L22) | Explanatory comments or spacing. |  |
| [B0004 · 24–25](../../../../../tests/integration/measurement_artifacts.py#L24) | Callable definition: def canonical(value): | calls dumps; returns json.dumps(value, sort_keys=True, separators=(',', ':'), ensure_ascii=False) · [reviewed contract](#b0004) |
| [B0005 · 26–27](../../../../../tests/integration/measurement_artifacts.py#L26) | Explanatory comments or spacing. |  |
| [B0006 · 28–43](../../../../../tests/integration/measurement_artifacts.py#L28) | Callable definition: def validators(root): | calls loads, read_text, in, glob; returns result; 3 loop sites · [reviewed contract](#b0006) |
| [B0007 · 44–45](../../../../../tests/integration/measurement_artifacts.py#L44) | Explanatory comments or spacing. |  |
| [B0008 · 46–68](../../../../../tests/integration/measurement_artifacts.py#L46) | Callable definition: def oracle(sql, events): | calls connect, execute, KEY, set; guard require(table in \['r0', 'r1'\], 'unexpected two-relation oracle table'); returns result; growth insert; 4 loop sites · [reviewed contract](#b0008) |
| [B0009 · 69–70](../../../../../tests/integration/measurement_artifacts.py#L69) | Explanatory comments or spacing. |  |
| [B0010 · 71–78](../../../../../tests/integration/measurement_artifacts.py#L71) | Callable definition: def chain(tree): | calls deepcopy, require, len, enumerate; guard require(len(nodes) == 2, 'fixture must retain exactly two native occurrences'); returns {'schema_version': 1, 'catalog_version': tree\['catalog_version'\], 'semantics': 'set',; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 79–80](../../../../../tests/integration/measurement_artifacts.py#L79) | Explanatory comments or spacing. |  |
| [B0012 · 81–287](../../../../../tests/integration/measurement_artifacts.py#L81) | Callable definition: def main(): | calls require, len, Path, resolve; guard require(len(sys.argv) in \[4, 5\], 'usage: measurement_artifacts.py CROWN COLLECTOR SOURCE \[ARTIFACT_…; returns path; result; growth insert; 17 loop sites · [reviewed contract](#b0012) |
| [B0013 · 288–295](../../../../../tests/integration/measurement_artifacts.py#L288) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |

## B0001

[Lines 1–18](../../../../../tests/integration/measurement_artifacts.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L18:sha256:07a3a5edea7bd15d9b8a58cacba4ffbf05481810763877ab6cd5ea22708b547f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the standalone cold artifact acceptance test and exact version tags. |
| inputs / outputs | Imports standard JSON/file/SQLite/process helpers and the existing jsonschema dependency; defines UPPER_TAG and MINIMUM_TAG. |
| invariants | No binary command or timing experiment runs on import; main executes only behind its module guard. |
| ownership | Module constants are immutable strings; no query owner or retained external process exists here. |
| failure | Missing required Python dependencies fail import; no optional dependency or fallback authority is introduced. |
| cost | Python import/setup only. Native commands, when root runs the test, occur later in explicit invoke calls. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [Refactor.md §5.4 and §14.1–14.4](../../../../../Refactor.md), [schemas/compiled-experimental-upper-v3.schema.json](../../../../../schemas/compiled-experimental-upper-v3.schema.json) |

## B0002

[Lines 19–21](../../../../../tests/integration/measurement_artifacts.py#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L21:sha256:8b14f7d5eb0d9a9cafc6d1aaa990a73bad9c261d2c3c97d6713ed7fa789c829b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a violated acceptance assertion with an active Release-independent Python check. |
| inputs / outputs | Receives a condition and concrete message; false raises RuntimeError. |
| invariants | Assertions are ordinary runtime branches and remain active independently of C++ build mode or Python assert optimization. |
| ownership | Borrows arguments; a raised exception owns its diagnostic according to Python. |
| failure | False reaches the one script-level failure handler and nonzero exit. |
| cost | One local branch; failure message/exception construction is test-host work. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [Refactor.md §5.4 and §14.1–14.4](../../../../../Refactor.md), [schemas/compiled-experimental-upper-v3.schema.json](../../../../../schemas/compiled-experimental-upper-v3.schema.json) |

## B0004

[Lines 24–25](../../../../../tests/integration/measurement_artifacts.py#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L25:sha256:119bfac72844a6d3a38f357b1cf2fe899e68ea3c3ee38905f72e24febc879cb3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize test JSON deterministically for catalog hashes, artifacts and comparison keys. |
| inputs / outputs | Receives a JSON-compatible value and returns sorted compact UTF-8-preserving JSON text. |
| invariants | This matches canonical catalog serialization for the controlled integer fixture; it does not establish semantic proof or binary provenance. |
| ownership | Returns a new Python string; source JSON remains caller-owned. |
| failure | Unsupported JSON values or host allocation failures propagate to the test boundary. |
| cost | Visits and serializes the value, with sorting per object; not a constant-time digest or native event operation. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [Refactor.md §5.4 and §14.1–14.4](../../../../../Refactor.md), [schemas/compiled-experimental-upper-v3.schema.json](../../../../../schemas/compiled-experimental-upper-v3.schema.json) |

## B0006

[Lines 28–43](../../../../../tests/integration/measurement_artifacts.py#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L43:sha256:df9b0dfedfb05a42f6ab9b41ff0cd6fcaffc72581035a870db5e26313d8015f1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the four artifact/report validators using the repository local schema corpus. |
| inputs / outputs | Reads schema JSON and returns Draft202012 validators for V1, V2, V3 and workload report V2. |
| invariants | Local file URIs and explicit schema IDs resolve through the supplied store. Shape validation supplements rather than replaces physical/source/certificate replay. |
| ownership | The returned validators/resolvers retain their parsed schema objects and store; no native plan is created. |
| failure | Missing/invalid schema, unresolved reference or validation errors abort the test. Existing repository RefResolver API avoids a new referencing-package requirement. |
| cost | Cold corpus read/parse plus four schema-definition checks; artifact validations traverse only their requested documents and refs. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [Refactor.md §5.4 and §14.1–14.4](../../../../../Refactor.md), [schemas/compiled-experimental-upper-v3.schema.json](../../../../../schemas/compiled-experimental-upper-v3.schema.json) |

## B0008

[Lines 46–68](../../../../../tests/integration/measurement_artifacts.py#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L68:sha256:6e0881deda79789743219392d73cf10aca7fde4383b6189bdb2969ae653e1f3e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently compute every full and signed-delta prefix for the fixed two-relation SQL fixture. |
| inputs / outputs | Receives fixture SQL and ordered physical insert/delete events; returns initial_rows and one current/signed frame per event. |
| invariants | SQLite evaluates the actual DISTINCT query on separate r0/r1 primary-key set tables. Delta is exact set difference between consecutive SQL results. Source operation/table domain is checked; all retained prefixes are also compared with B02 expected rows. |
| ownership | A private in-memory database, result sets and JSON arrays are owned locally; the database closes before return. |
| failure | Unsupported table/op, SQL error or allocation failure aborts. This function does not consume native output when deriving expected answers. |
| cost | Recomputes SQL and materializes finite sets at every test event, intentionally independent of CROWN incremental algorithms. This is correctness oracle cost, never benchmark timing. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [Refactor.md §5.4 and §14.1–14.4](../../../../../Refactor.md), [schemas/compiled-experimental-upper-v3.schema.json](../../../../../schemas/compiled-experimental-upper-v3.schema.json) |

## B0010

[Lines 71–78](../../../../../tests/integration/measurement_artifacts.py#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L71-L78:sha256:2098e7e8ee7deade89173c5e4e1e30c2584c635643395901eb9cfefcdb2e93f9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Propose an ordinary height-two chain from the genuine two-occurrence minimum fixture. |
| inputs / outputs | Copies its two native nodes, drops inherited separator claims, assigns one native child edge and returns an untrusted tree proposal with claimed height two. |
| invariants | The helper supplies no validity or height authority; the public lower-normalized command independently checks the entire returned tree before use. |
| ownership | Deep-copied node JSON is owned by the proposal; the original proof/witness is unchanged. |
| failure | Wrong occurrence count aborts setup. Invalid structure must be rejected by the actual lowerer. |
| cost | Copies two finite node records and scopes; no exhaustive family claim or fallback search is hidden here. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [Refactor.md §5.4 and §14.1–14.4](../../../../../Refactor.md), [schemas/compiled-experimental-upper-v3.schema.json](../../../../../schemas/compiled-experimental-upper-v3.schema.json) |

## B0012

[Lines 81–287](../../../../../tests/integration/measurement_artifacts.py#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L287:sha256:2a01419c464d77cee9267bef0ac9f266d9836d4c57975ea79759034e40273948
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise real minimum and taller-upper acceptance plus falsification controls through the built collector. |
| inputs / outputs | Receives CROWN COLLECTOR SOURCE and optional fresh artifact directory. Produces raw request/command/stdout/stderr evidence and a bounded result summary. |
| invariants | Original proof comes from genuine compile; ordinary and renamed-equal trees pass actual lower-normalized. Both storage backends and snapshot/delta modes compare every prefix against independently derived SQLite/B02 answers. V1 requires its original witness, V2 accepts equal checked alternatives, V3 admits equal/taller checked uppers without a minimum label. False lower/source/tree/declared-height/tag/type/field controls must fail without a report or sink; constant false remains V1/null only. |
| ownership | The test owns one fresh temporary/output directory, all input JSON and captured completed child output. Each process completes within its 120-second subprocess boundary before the next starts. |
| failure | Any unexpected exit, stderr, report, schema result, oracle disagreement or sink creation aborts. A supplied evidence directory must not exist; no completed packet or native binary is patched. Root owns builds and execution. |
| cost | Finite 20-event fixture, two backends and two observation modes, with no timing collection. Cold compilation/replay/lowering is test work. This is one structure-axis dependency, not the full ten-axis B04 gate. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [Refactor.md §5.4 and §14.1–14.4](../../../../../Refactor.md), [schemas/compiled-experimental-upper-v3.schema.json](../../../../../schemas/compiled-experimental-upper-v3.schema.json) |

## B0013

[Lines 288–295](../../../../../tests/integration/measurement_artifacts.py#L288); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L288-L295:sha256:c8741399534ddf50a5997d92c9ea3a7cc224150ed5a0b245616e28787f4949ea
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start the acceptance test as a script and expose a single conventional failure exit. |
| inputs / outputs | __main__ invokes main; an exception prints its message to stderr and exits one. |
| invariants | Importing this file does not launch subprocesses. Success is printed only after the complete acceptance matrix returns. |
| ownership | No query or process owner is retained by the guard; main owns its resources. |
| failure | The one boundary reports the original exception message; it performs no retry, success synthesis or baseline repair. |
| cost | One process boundary and error conversion; no native production overhead. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/physical_plans.md](../../../../physical_plans.md), [Refactor.md §5.4 and §14.1–14.4](../../../../../Refactor.md), [schemas/compiled-experimental-upper-v3.schema.json](../../../../../schemas/compiled-experimental-upper-v3.schema.json) |
