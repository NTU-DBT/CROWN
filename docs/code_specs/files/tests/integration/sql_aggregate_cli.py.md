# `tests/integration/sql_aggregate_cli.py` — block usage map

[Source](../../../../../tests/integration/sql_aggregate_cli.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `2bc1fb5ecb306de58007c94051112848344fdc70c973b7bc1f5e0ff47bc9922b`. 291 lines partitioned into 21 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../tests/integration/sql_aggregate_cli.py#L1) | Imports dependencies; declares types or opens a type body. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 23–30](../../../../../tests/integration/sql_aggregate_cli.py#L23) | Callable definition: def invoke(binary, *arguments, code=0): | calls run, str, map, loads; returns json.loads(result.stderr); json.loads(result.stdout) · [reviewed contract](#b0002) |
| [B0003 · 31–32](../../../../../tests/integration/sql_aggregate_cli.py#L31) | Explanatory comments or spacing. |  |
| [B0004 · 33–35](../../../../../tests/integration/sql_aggregate_cli.py#L33) | Callable definition: def edit(values, before, after): | calls list; returns {"table": "r", "source_schema_version": 1, "values": list(values), · [reviewed contract](#b0004) |
| [B0005 · 36–37](../../../../../tests/integration/sql_aggregate_cli.py#L36) | Explanatory comments or spacing. |  |
| [B0006 · 38–40](../../../../../tests/integration/sql_aggregate_cli.py#L38) | Callable definition: def fingerprint(root, sink): | calls str, sha256, read_bytes, hexdigest; returns {str(path): hashlib.sha256(path.read_bytes()).hexdigest(); 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 41–42](../../../../../tests/integration/sql_aggregate_cli.py#L41) | Explanatory comments or spacing. |  |
| [B0008 · 43–54](../../../../../tests/integration/sql_aggregate_cli.py#L43) | Callable definition: def sql_groups(connection, state): | calls execute, items, range, executemany; returns result; 3 loop sites · [reviewed contract](#b0008) |
| [B0009 · 55–56](../../../../../tests/integration/sql_aggregate_cli.py#L55) | Explanatory comments or spacing. |  |
| [B0010 · 57–61](../../../../../tests/integration/sql_aggregate_cli.py#L57) | Callable definition: def snapshot(binary, root, sink, recovery, expected): | calls invoke, dumps; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 62–63](../../../../../tests/integration/sql_aggregate_cli.py#L62) | Explanatory comments or spacing. |  |
| [B0012 · 64–89](../../../../../tests/integration/sql_aggregate_cli.py#L64) | Callable definition: def sink_epochs(sink, expected, initial=None): | calls read_bytes, len, unpack_from, sha256; 3 loop sites · [reviewed contract](#b0012) |
| [B0013 · 90–91](../../../../../tests/integration/sql_aggregate_cli.py#L90) | Explanatory comments or spacing. |  |
| [B0014 · 92–104](../../../../../tests/integration/sql_aggregate_cli.py#L92) | Callable definition: def physical_options(): | calls dict, zip, in; returns {"schema_version": 2,; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 105–106](../../../../../tests/integration/sql_aggregate_cli.py#L105) | Explanatory comments or spacing. |  |
| [B0016 · 107–233](../../../../../tests/integration/sql_aggregate_cli.py#L107) | Callable definition: def profile(binary, helper, directory, indexed): | calls mkdir, in, write_text, dumps; returns {"indexed": indexed, "commands": len(commands), "commits": len(expected_commits),; 7 loop sites; source comment (unverified): # A failed report follows the durable decision. Retry must resume W, · [reviewed contract](#b0016) |
| [B0017 · 234–235](../../../../../tests/integration/sql_aggregate_cli.py#L234) | Explanatory comments or spacing. |  |
| [B0018 · 236–276](../../../../../tests/integration/sql_aggregate_cli.py#L236) | Callable definition: def sum_overflow(binary, directory, indexed, connection): | calls mkdir, in, write_text, COUNT; 4 loop sites; source comment (unverified): # A consumed unterminated final record is terminal for this CLI source. · [reviewed contract](#b0018) |
| [B0019 · 277–278](../../../../../tests/integration/sql_aggregate_cli.py#L277) | Explanatory comments or spacing. |  |
| [B0020 · 279–287](../../../../../tests/integration/sql_aggregate_cli.py#L279) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, TemporaryDirectory; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 288–291](../../../../../tests/integration/sql_aggregate_cli.py#L288) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0021) |

## B0001

[Lines 1–22](../../../../../tests/integration/sql_aggregate_cli.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L22:sha256:5cb2222b4219d2b16c4935497eeace79c4e7196aaf765b33171116789637691c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for sql_aggregate_cli.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/sql_aggregate_cli.py](../../../../../tests/integration/sql_aggregate_cli.py), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 23–30](../../../../../tests/integration/sql_aggregate_cli.py#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def invoke(binary, *arguments, code=0):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one public crown aggregate subprocess and parse its JSON success or error report. |
| inputs / outputs | Executes binary aggregate plus stringified arguments with a 180-second timeout; requires the requested return code. On expected nonzero status, requires empty stdout and a JSON stderr error code, then returns parsed JSON. |
| invariants | This checks process exit/report shape, not the truth of every reported field. Callers add operation-specific assertions; no subprocess exception is translated here. |
| ownership | Subprocess handle/output strings and decoded JSON belong to Python; files/account/native Session are owned by the child CLI. |
| failure | Timeout, launch error, wrong status, stdout on failure or malformed error JSON fails through Python exceptions/assertions. |
| cost | One process launch and captured stdout/stderr per invocation, capped only by the timeout here. |
| Design | [docs/sql_aggregate_input.md §Workflow](../../../../sql_aggregate_input.md), [apps/crown/aggregate.cpp §run reader/session loop, lines 167–190](../../../../../apps/crown/aggregate.cpp), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0004

[Lines 33–35](../../../../../tests/integration/sql_aggregate_cli.py#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def edit(values, before, after):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one physical table r replacement JSON object for the integration command fixture. |
| inputs / outputs | Copies row values to a Python list and adds schema version 1 with caller before/after weights. |
| invariants | It is a fixture constructor only; it does not validate row shape, sequence, source binding or weight semantics. |
| ownership | Returns a new Python dict/list independent of the caller’s iterable. |
| failure | No rejection behavior is implemented here. |
| cost | Copies the supplied row values once; fixture size is small except explicitly parameterized overflow weight, which is a scalar integer. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [schemas/sql-aggregate-input-v1.schema.json](../../../../../schemas/sql-aggregate-input-v1.schema.json) |

## B0006

[Lines 38–40](../../../../../tests/integration/sql_aggregate_cli.py#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def fingerprint(root, sink):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot hashes of the root’s matching durable files and the sink for no-mutation assertions. |
| inputs / outputs | Finds root-name sibling files plus the sink, sorts/deduplicates paths, and returns path-to-SHA256 for existing regular files. |
| invariants | The fingerprint deliberately excludes the JSONL source, SQL and catalog; callers compare durable root/sink state only. |
| ownership | Reads file bytes into Python-owned buffers; filesystem handles are scoped to read_bytes calls. |
| failure | Filesystem read errors propagate; an empty/missing file is omitted because only existing files are included. |
| cost | Reads each selected durable file fully and hashes all bytes; cost is O(total selected file bytes) and is test-only. |
| Design | [docs/sql_aggregate_input.md §Workflow](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md §Recovery and failure boundaries](../../../../sql_aggregate_session.md), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0008

[Lines 43–54](../../../../../tests/integration/sql_aggregate_cli.py#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sql_groups(connection, state):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute independent small-bag grouped COUNT/SUM/AVG snapshots with DuckDB for the main CLI profile. |
| inputs / outputs | Deletes all reference rows, expands each (row,weight) in the finite state Counter into ordinary rows, executes grouped SQL and formats SUM/AVG through exact numeric/Fraction helpers. |
| invariants | This expansion is only for small finite profile weights. The huge 2^62 overflow fixture is handled separately without row expansion; DuckDB floating AVG is not used. |
| ownership | DuckDB connection is borrowed; expanded row list and result map are Python/DB fixture state. |
| failure | DuckDB or numeric assertion/adapter failures propagate and fail the harness; it is not a native oracle proof for arbitrary workloads. |
| cost | Deletes/reinserts the full small fixture table each call and scans its rows; this deliberately simple reference cost is outside engine updates. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [tests/integration/aggregate_sql_oracle.py §numeric, lines 22–32](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0010

[Lines 57–61](../../../../../tests/integration/sql_aggregate_cli.py#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def snapshot(binary, root, sink, recovery, expected):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the public CLI snapshot’s output schema and grouped values with a supplied reference map. |
| inputs / outputs | Invokes snapshot with root/sink/recovery options, checks the five expected SQL kinds, and compares JSON-keyed groups/values exactly. |
| invariants | It validates only the fields explicitly asserted; snapshot state is read through the public CLI and is not itself a durable acknowledgement. |
| ownership | Inputs/options are borrowed Python values; invoke owns a fresh child process and returned JSON object. |
| failure | Any CLI error, wrong kind list or value mismatch fails an assertion. |
| cost | One CLI process plus linear comparison over returned groups. |
| Design | [docs/sql_aggregate_input.md §Workflow](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md §State and command usage](../../../../sql_aggregate_session.md), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0012

[Lines 64–89](../../../../../tests/integration/sql_aggregate_cli.py#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sink_epochs(sink, expected, initial=None):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode actual sink frames with the independent Python runtime oracle and replay each output delta against expected materialized state. |
| inputs / outputs | Reads all sink bytes, checks CROWNAG2 framing, fixed/payload lengths and body/prefix hashes; checks a SinkHeader followed by the expected number of epochs, sequence, exact before values, after/removal and complete state after every frame. initial seeds the global \[0,null\] aggregate when required. |
| invariants | Replay verifies the observed frame chain against this fixture’s expected states, including initial global state when supplied. It is a finite independent decoder/assertion path, not native proof or a general recovery implementation. |
| ownership | The sink is read-only here; Python frame buffers and decoded objects are temporary. session_epoch returns ordinary Python values and no native state or authority. |
| failure | Malformed/truncated frames, bad hashes, before mismatch or output-state mismatch fail assertions. The checker does not alter/repair the sink. |
| cost | Reads and retains the complete sink in memory, hashes each frame and decodes each expected epoch; test cost is O(sink bytes + output changes). |
| Design | [docs/sql_aggregate_records.md §Wire contract](../../../../sql_aggregate_records.md), [tests/integration/sql_aggregate_runtime_oracle.py §session_epoch, lines 386–444](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_input.md §Workflow](../../../../sql_aggregate_input.md), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0014

[Lines 92–104](../../../../../tests/integration/sql_aggregate_cli.py#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def physical_options():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply the fixed indexed-storage configuration used by the alternate CLI profile. |
| inputs / outputs | Returns schema version 2 policy, limits, indexed_chained_v1 algorithm and finite fixture work ceilings for each index work domain. |
| invariants | This object is test input, not a claim that limits are production defaults or a benchmarked allowance. The reference profile omits it. |
| ownership | Returns a fresh nested Python dict; callers serialize it into a temporary file. |
| failure | No validation occurs until the CLI admits the generated file. |
| cost | Constant-size fixture object construction; file serialization and native rebuild are separate test costs. |
| Design | [docs/sql_aggregate_input.md §Workflow](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md §State and command usage](../../../../sql_aggregate_session.md), [docs/sql_aggregate_session.md §Resource and performance scope](../../../../sql_aggregate_session.md) |

## B0016

[Lines 107–233](../../../../../tests/integration/sql_aggregate_cli.py#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def profile(binary, helper, directory, indexed):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise one finite end-to-end CLI profile over either reference or indexed source storage. |
| inputs / outputs | Creates catalog/query/input fixtures, starts a genuine aggregate session, then replays eleven fixed JSONL commands with mixed LF/CRLF, snapshots against small expanded DuckDB state, and checks actual sink epochs. Public API helper handoffs seed pending Input and Commit; the profile also exercises command limits, report failure/retry, semantic Rejects, checkpoints, malformed tails, status failures and torn-tail repair. |
| invariants | The helper’s two handoffs are real Session::log/decide calls followed by normal return, not process-crash/EIO cuts. Main sequence 5 is a weight mismatch; sequences 7 and 11 are aggregate_overflow under count-limit=5. This separate profile is distinct from sum_overflow()’s signed-bigint SUM case. Invalid transport tails must leave durable root/sink fingerprint stable; only source position is repaired by the fixture. |
| ownership | Temporary directory owns generated files; Python/DuckDB own reference state; each child CLI and helper process owns its Session/account/locks. Fresh CLI invocations perform recovery. |
| failure | Expected public command errors are checked by invoke plus exact codes where specified; any filesystem, subprocess, state, oracle or assertion mismatch fails the test. This does not simulate every power-loss/torn-write location. |
| cost | Eleven commands per profile, many child process starts, full durable-file fingerprints/sink parses and repeated small DuckDB table reconstruction; run twice, one per storage backend. Costs are harness-only. |
| Design | [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Ownership, failure and cost](../../../../sql_aggregate_input.md), [docs/sql_aggregate_input.md §Workflow](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md §State and command usage](../../../../sql_aggregate_session.md), [docs/sql_aggregate_session.md §Recovery and failure boundaries](../../../../sql_aggregate_session.md), [apps/crown/aggregate.cpp §run reader/session loop, lines 167–190](../../../../../apps/crown/aggregate.cpp), [src/recovery/sql_aggregate_session.cpp §Session log/decide implementation, lines 128–153](../../../../../src/recovery/sql_aggregate_session.cpp), [tests/integration/aggregate_sql_oracle.py §numeric, lines 22–32](../../../../../tests/integration/aggregate_sql_oracle.py), [tests/integration/sql_aggregate_runtime_oracle.py §session_epoch, lines 386–444](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md), [apps/crown/aggregate.cpp §seek continuation line-boundary guard, lines 141–155](../../../../../apps/crown/aggregate.cpp) |

## B0018

[Lines 236–276](../../../../../tests/integration/sql_aggregate_cli.py#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sum_overflow(binary, directory, indexed, connection):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise a compressed global INT SUM overflow and successful later retry without expanding its large weight. |
| inputs / outputs | Creates COUNT(*)/SUM(CAST(2 AS INT)) over one int64 source; sets weight 2^62, uses DuckDB DECIMAL multiplication to check count fits int64 while exact sum exceeds signed bigint, expects first command Reject aggregate_overflow with no commit/delivery, checkpoints, then applies weight 1 and checks \[1,2\] plus sink replay seeded from \[0,null\]. The second command is the final unterminated record; after it is consumed, appending LF plus a third valid command must fail at the CLI continuation guard without changing root/sink files. |
| invariants | This is a separate arithmetic overflow fixture, not the main profile’s count-limit=5 rejection. The large multiplicity is carried as one compressed command and is never expanded into rows; the succeeding sequence verifies W continuation after semantic Reject. Reader acceptance of an unterminated final line does not make its saved byte offset appendable: when the source later grows, the CLI requires the byte before the saved offset to be LF. |
| ownership | Fixture files live in the supplied temporary directory; the connection is borrowed; child CLI processes own session state and sink access. |
| failure | Wrong Reject/frontier/snapshot/sink state or oracle arithmetic fails assertions. The tested exact case is finite and does not establish all aggregate overflow paths. The appended-continuation check expects invalid_input_progress and an unchanged durable fingerprint. |
| cost | Two compressed commands and constant-size big-integer oracle multiplication; no repeated-row materialization for 2^62. |
| Design | [docs/aggregates.md §SQL and numeric contract](../../../../aggregates.md), [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md), [docs/sql_aggregate_input.md §One atomic JSONL command](../../../../sql_aggregate_input.md), [docs/sql_aggregate_session.md §State and command usage](../../../../sql_aggregate_session.md), [tests/integration/sql_aggregate_runtime_oracle.py §session_epoch, lines 386–444](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md), [apps/crown/aggregate.cpp §seek continuation line-boundary guard, lines 141–155](../../../../../apps/crown/aggregate.cpp) |

## B0020

[Lines 279–287](../../../../../tests/integration/sql_aggregate_cli.py#L279); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse binary/helper paths, run both storage profiles in a temporary directory and emit a machine-readable status summary. |
| inputs / outputs | Requires --binary and --helper paths, executes reference and indexed profiles, then prints JSON with status, DuckDB version and per-profile counts/flags. |
| invariants | A printed pass is meaningful only when this function actually runs and all nested assertions complete; source inspection alone does not claim that execution. The script requires installed DuckDB and has no fallback. |
| ownership | TemporaryDirectory owns generated fixtures; argparse, DuckDB and subprocess resources follow their respective Python/process lifetimes. |
| failure | Argument, import, subprocess, oracle or assertion failure exits nonzero through Python; no result JSON is printed after an earlier failure. |
| cost | Runs two full profiles and their separate overflow fixtures; process, file hashing, database and sink replay costs are explicit integration-test work. |
| Design | [docs/sql_aggregate_input.md §Workflow](../../../../sql_aggregate_input.md), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0021

[Lines 288–291](../../../../../tests/integration/sql_aggregate_cli.py#L288); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Parse binary/helper paths, run both storage profiles in a temporary directory and emit a machine-readable status summary. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | No presentation catch is added here: main/fixture failures and SystemExit propagate through the interpreter. This block supplies no extra retry or rollback. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. |
| Design | [tests/integration/sql_aggregate_cli.py](../../../../../tests/integration/sql_aggregate_cli.py), [docs/development.md](../../../../development.md), [docs/sql_aggregate_input.md §Workflow](../../../../sql_aggregate_input.md), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |
