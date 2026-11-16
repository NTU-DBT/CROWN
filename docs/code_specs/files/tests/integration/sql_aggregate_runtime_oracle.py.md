# `tests/integration/sql_aggregate_runtime_oracle.py` — block usage map

[Source](../../../../../tests/integration/sql_aggregate_runtime_oracle.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Compare physical aggregate epochs with independent mature SQL recomputation.

Snapshot SHA-256: `df59f46f7aeeb0b3a89061dd71e6918660eeb38dafa9f3d1eaa3ce0aee01e1c5`. 606 lines partitioned into 64 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–25](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L1) | Imports dependencies; declares types or opens a type body. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 26–41](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L26) | declares values/defaults or compile-time conditions. | 2 loop sites; source comment (unverified): # Explicit fixture spellings, independent of the native cast/compiler metadata. · [reviewed contract](#b0002) |
| [B0003 · 42–45](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L42) | Callable definition: def catalog(): | calls column, in; returns {"version": 1, "tables": \[{"name": name, "columns": columns} for name in ("r", "t")\]}; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 46–47](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L46) | Explanatory comments or spacing. |  |
| [B0005 · 48–49](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L48) | Callable definition: def edit(table, values, before, after): | calls list; returns {"table": table, "values": list(values), "before": before, "after": after} · [reviewed contract](#b0005) |
| [B0006 · 50–51](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L50) | Explanatory comments or spacing. |  |
| [B0007 · 52–53](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L52) | Callable definition: def batch(*edits): | calls list; returns {"edits": list(edits)} · [reviewed contract](#b0007) |
| [B0008 · 54–55](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L54) | Explanatory comments or spacing. |  |
| [B0009 · 56–57](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L56) | Callable definition: def expression(kind, argument): | calls COUNT, upper; returns argument if kind == "group" else "COUNT(*)" if kind == "all" else f"{kind.upper()}({argument})" · [reviewed contract](#b0009) |
| [B0010 · 58–59](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L58) | Explanatory comments or spacing. |  |
| [B0011 · 60–74](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L60) | Callable definition: def sql(case, reference=False): | calls list, enumerate, extend, SUM; returns result; 2 loop sites · [reviewed contract](#b0011) |
| [B0012 · 75–76](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L75) | Explanatory comments or spacing. |  |
| [B0013 · 77–85](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L77) | Callable definition: def logical_references(case): | calls get, fullmatch, append; returns result; 2 loop sites; source comment (unverified): # Fixture original columns, independently of native descriptors. Different · [reviewed contract](#b0013) |
| [B0014 · 86–87](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L86) | Explanatory comments or spacing. |  |
| [B0015 · 88–90](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L88) | Callable definition: def logical_sql(case): | calls join, logical_references; returns "SELECT " + ",".join(logical_references(case) or \["1"\]) + case\["tail"\]; 1 loop sites; source comment (unverified): # Constant1 represents the nullary row only for the cold SQL Counter. · [reviewed contract](#b0015) |
| [B0016 · 91–92](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L91) | Explanatory comments or spacing. |  |
| [B0017 · 93–100](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L93) | Callable definition: def argument_kind(argument): | calls fullmatch; returns CAST_ARGUMENTS\[argument\]\[1\]; COLUMN_KIND\[matched\[1\]\] · [reviewed contract](#b0017) |
| [B0018 · 101–102](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L101) | Explanatory comments or spacing. |  |
| [B0019 · 103–104](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L103) | Callable definition: def scalar_type(kind, nullable=True, scale=None): | calls ; returns {"kind": kind, "nullable": nullable, "decimal": \[38, scale\] if scale is not None else None} · [reviewed contract](#b0019) |
| [B0020 · 105–106](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L105) | Explanatory comments or spacing. |  |
| [B0021 · 107–121](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L107) | Callable definition: def expected_metadata(case): | calls enumerate, append, scalar_type, argument_kind; returns types, \[scalar_type(argument_kind(value)) for value in case\["groups"\]\], names; 2 loop sites · [reviewed contract](#b0021) |
| [B0022 · 122–123](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L122) | Explanatory comments or spacing. |  |
| [B0023 · 124–128](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L124) | Callable definition: def make_case(name, outputs, tail, groups=(), batches=(), scale=18, **options): | calls catalog, list, sql; returns result · [reviewed contract](#b0023) |
| [B0024 · 129–130](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L129) | Explanatory comments or spacing. |  |
| [B0025 · 131–198](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L131) | Callable definition: def fixed_cases(): | calls make_case, batch, edit, in; growth new; 1 loop sites · [reviewed contract](#b0025) |
| [B0026 · 199–200](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L199) | Explanatory comments or spacing. |  |
| [B0027 · 201–223](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L201) | Callable definition: def integer_cases(): | calls batch, edit, CAST, make_case · [reviewed contract](#b0027) |
| [B0028 · 224–225](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L224) | Explanatory comments or spacing. |  |
| [B0029 · 226–242](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L226) | Callable definition: def scale_cases(): | calls batch, edit, range, make_case; 1 loop sites · [reviewed contract](#b0029) |
| [B0030 · 243–244](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L243) | Explanatory comments or spacing. |  |
| [B0031 · 245–267](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L245) | Callable definition: def random_cases(): | calls Random, range, randrange, choice; 3 loop sites · [reviewed contract](#b0031) |
| [B0032 · 268–269](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L268) | Explanatory comments or spacing. |  |
| [B0033 · 270–288](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L270) | Callable definition: def states(case): | calls enumerate, dict, len, type; 10 loop sites · [reviewed contract](#b0033) |
| [B0034 · 289–290](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L289) | Explanatory comments or spacing. |  |
| [B0035 · 291–295](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L291) | Callable definition: def integer(value): | calls type, in, Decimal, str; returns result · [reviewed contract](#b0035) |
| [B0036 · 296–297](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L296) | Explanatory comments or spacing. |  |
| [B0037 · 298–299](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L298) | Callable definition: def scalar(value, kind, postgres): | calls pg_value, canonical; returns rows.pg_value(value, kind) if postgres else rows.canonical(value) · [reviewed contract](#b0037) |
| [B0038 · 300–301](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L300) | Explanatory comments or spacing. |  |
| [B0039 · 302–325](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L302) | Callable definition: def decode_groups(case, records, postgres): | calls len, sum, scalar, argument_kind; returns result; 4 loop sites · [reviewed contract](#b0039) |
| [B0040 · 326–327](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L326) | Explanatory comments or spacing. |  |
| [B0041 · 328–335](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L328) | Callable definition: def reference_snapshot(case, sequence, expanded, physical_changed, group_records, logical_records, postgres): | calls argument_kind, logical_references, Counter, len; returns {"sequence": sequence, "groups": decode_groups(case, group_records, postgres),; 4 loop sites · [reviewed contract](#b0041) |
| [B0042 · 336–337](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L336) | Explanatory comments or spacing. |  |
| [B0043 · 338–364](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L338) | Callable definition: def duckdb_reference(case): | calls connect, execute, current_setting, fetchone; returns trace; 9 loop sites; source comment (unverified): # Required; no skip/install/fallback. · [reviewed contract](#b0043) |
| [B0044 · 365–366](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L365) | Explanatory comments or spacing. |  |
| [B0045 · 367–370](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L367) | Callable definition: def substitute_parameters(text, case): | calls get, sub, literal, int; returns re.sub(r"\$(\d+)", lambda match: rows.literal(parameters\[int(match\[1\]) - 1\]), text); source comment (unverified): # Fixture placeholders occur only as predicate expressions, never in quotes. · [reviewed contract](#b0045) |
| [B0046 · 371–372](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L371) | Explanatory comments or spacing. |  |
| [B0047 · 373–377](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L373) | Callable definition: def json_rows(query, arity): | calls range, q, join, COALESCE; returns f"COALESCE((SELECT json_agg(json_build_array({fields})) FROM {source}),'\[\]'::json)"; 2 loop sites · [reviewed contract](#b0047) |
| [B0048 · 378–379](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L378) | Explanatory comments or spacing. |  |
| [B0049 · 380–403](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L380) | Callable definition: def postgres_reference(case, postgres): | calls join, sql, ddl, substitute_parameters; returns \[reference_snapshot(case, sequence, expanded, changed, result\["groups"\], result\["logical"\], True); 10 loop sites · [reviewed contract](#b0049) |
| [B0050 · 404–405](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L404) | Explanatory comments or spacing. |  |
| [B0051 · 406–412](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L406) | Callable definition: def group_map(groups): | calls set, type, key; returns result; 1 loop sites · [reviewed contract](#b0051) |
| [B0052 · 413–414](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L413) | Explanatory comments or spacing. |  |
| [B0053 · 415–423](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L415) | Callable definition: def output_diff(before, after): | calls keys, get; returns result; 1 loop sites · [reviewed contract](#b0053) |
| [B0054 · 424–425](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L424) | Explanatory comments or spacing. |  |
| [B0055 · 426–484](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L426) | Callable definition: def session_epoch(encoded): | calls fromhex, len, unpack_from, sha256; returns value; int.from_bytes(take(8), "little"); 2 loop sites · [reviewed contract](#b0055) |
| [B0056 · 485–486](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L485) | Explanatory comments or spacing. |  |
| [B0057 · 487–515](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L487) | Callable definition: def compare(case, observed, expected): | calls fullmatch, key, expected_metadata, len; 2 loop sites · [reviewed contract](#b0057) |
| [B0058 · 516–517](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L516) | Explanatory comments or spacing. |  |
| [B0059 · 518–531](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L518) | Callable definition: def native_request(case, backend, rebuild=False, checkpoint=False, session=False): | calls in, update; returns result; 2 loop sites; source comment (unverified): # Reference groups/outputs/tail never enter native binding as descriptors. · [reviewed contract](#b0059) |
| [B0060 · 532–533](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L532) | Explanatory comments or spacing. |  |
| [B0061 · 534–542](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L534) | Callable definition: def reference_contract(): | calls key, output_diff, in, len; 1 loop sites; source comment (unverified): # This checks oracle representation only, never native or SQL evaluation. · [reviewed contract](#b0061) |
| [B0062 · 543–544](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L543) | Explanatory comments or spacing. |  |
| [B0063 · 545–602](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L545) | Callable definition: def main(): | calls RuntimeError, reference_contract, ArgumentParser, add_argument; 15 loop sites; source comment (unverified): # Check chains/bounds before native or mature SQL runs. · [reviewed contract](#b0063) |
| [B0064 · 603–606](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L603) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0064) |

## B0001

[Lines 1–25](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3 """SQL recomputation of genuine composed physical NetBatch epochs.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the independent SQL oracle's standard-library wire decoder imports, deterministic bounded cohort settings and original-schema fixture types. |
| inputs / outputs | Module import defines helpers/constants; session spool support adds stdlib hash/struct/date decoding while preserving the existing seed, weight/source-copy caps and input column-kind mapping. |
| invariants | Import starts no database or native driver. SQL engines execute relational semantics; the independent GroupEpoch reader checks a known fixture frame but owns no native/durable authority. |
| ownership | Python module owns constants and import references only. |
| failure | Missing helper import fails module loading; the selected SQL engine has no automatic fallback. |
| cost | Small module initialization/import work; no query-account charge. |
| Design | [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md) |

## B0002

[Lines 26–41](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L41:sha256:64c4edb7d6981d273d073fd14296455762f55cb9ba6d78f930396e1fbdda499d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for sql_aggregate_runtime_oracle.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 42–45](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def catalog():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the actual two-table nullable physical schema used by original SQL factories. |
| inputs / outputs | No arguments -&gt; real catalog JSON with r/t(id,g,x,flag). |
| invariants | Calls existing W05 column helper; every column nullable, no fabricated normalized program or new admission. |
| ownership | Ordinary finite test metadata; io catalog parser validates native input. |
| failure | Helper/schema errors fail fixture generation. |
| cost | Eight scalar column descriptors shared by two fixed tables; no SQL/native run here. |
| Design | tests/integration/sql_rows_oracle.py:55, include/crown/io/catalog.hpp:9, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0005

[Lines 48–49](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def edit(table, values, before, after):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one complete physical expected-weight replacement fixture. |
| inputs / outputs | Table,row,before,after -&gt; command entry JSON. |
| invariants | Values remain complete physical identity, never aggregate logical facts. |
| ownership | Copies row list into test-owned command. |
| failure | Bounds/authentication checked before execution by states and actual source. |
| cost | O(physical arity), ordinary harness allocation. |
| Design | include/crown/runtime/sql_aggregate.hpp:79, include/crown/runtime/sql_rows.hpp:25, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0007

[Lines 52–53](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def batch(*edits):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group physical replacements into one true atomic command boundary. |
| inputs / outputs | Finite edit arguments -&gt; {edits:\[...\]}. |
| invariants | No sequential runtime apply calls or transport-event semantics; empty allowed. |
| ownership | Owns finite ordinary test list. |
| failure | Invalid entries fail states/real source admission. |
| cost | O(number of edits), no runtime grant refill. |
| Design | include/crown/runtime/sql_aggregate.hpp:79, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0009

[Lines 56–57](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def expression(kind, argument):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spell a known fixed-family original target expression. |
| inputs / outputs | Fixture kind/argument -&gt; group/COUNT(*)/COUNT/SUM/AVG text. |
| invariants | Reference fixture builder only; not an arbitrary SQL parser or admission allowlist. |
| ownership | Returns ordinary owned SQL text. |
| failure | Invalid fixture kind/argument rejected by later construction/actual factory. |
| cost | O(expression bytes), cold test work. |
| Design | docs/aggregates.md:23, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0011

[Lines 60–74](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sql(case, reference=False):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct complete original/reference SQL from one explicit fixture definition. |
| inputs / outputs | Case + reference bool -&gt; actual original or hidden-key/SUM-COUNT reference SELECT. |
| invariants | Same FROM/JOIN/WHERE/GROUP BY; only reference targets add keys/decompose AVG. Actual original alone enters native binder; no arbitrary SQL substring surgery. |
| ownership | Case-owned clause/target strings yield ordinary cold SQL text. |
| failure | Unknown/invalid fixture fails real binder/SQL; no fabricated successful shape. |
| cost | O(target/clause bytes), bounded query family; no native metadata derived from this function. |
| Design | tests/integration/aggregate_sql_oracle.py:76, include/crown/runtime/sql_aggregate.hpp:69, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0013

[Lines 77–85](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def logical_references(case):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose original group/argument column expressions for independent logical-bag change comparison. |
| inputs / outputs | Case -&gt; finite raw original-column list; the explicit cast-spelling table unwraps fixture casts before deduplication. |
| invariants | Raw origins come only from fixture SQL metadata, never native descriptors/equality classes. Cast result types do not change logical source-fact identity; distinct origins remain distinct. |
| ownership | Ordinary test strings; withheld from native_request. |
| failure | Unsupported fixture spelling is not native admission authority; real factories remain decisive. |
| cost | O(fixed target/group count squared list membership), small cold query metadata. |
| Design | include/crown/frontend/bind.hpp:16, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0015

[Lines 88–90](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def logical_sql(case):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct independent plain bag SELECT for group_changed reference. |
| inputs / outputs | Case -&gt; required original columns over identical original FROM/JOIN/WHERE. |
| invariants | No GROUP BY; nullary row represented by constant1 only in cold reference Counter; no logical tuple enters runtime. |
| ownership | Ordinary owned reference SQL string. |
| failure | SQL failure fails oracle, no fallback. |
| cost | O(reference/SQL bytes); actual join enumeration is mature SQL work. |
| Design | tests/integration/sql_rows_oracle.py:173, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0017

[Lines 93–100](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def argument_kind(argument):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record documented input types for this explicit reference fixture family. |
| inputs / outputs | Known raw reference/literal or explicit fixture cast spelling -&gt; expected final SqlKind code. |
| invariants | Physical references remain bigint; the finite cast table labels integer/narrow-then-widen results independently of native metadata. Mature SQL evaluates casts; this lookup only predicts output representation. |
| ownership | Value-only cold metadata. |
| failure | Unknown fixture raises KeyError; no silent widening/narrowing. |
| cost | O(expression length), fixed literal lookup. |
| Design | include/crown/frontend/bind.hpp:9, docs/aggregates.md:35, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0019

[Lines 103–104](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def scalar_type(kind, nullable=True, scale=None):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode expected documented SQL result type metadata for assertions. |
| inputs / outputs | Kind/nullability/optional scale -&gt; comparison-only JSON. |
| invariants | NUMERIC uses precision38; local AVG scale preserved. This object is never native program input. |
| ownership | Ordinary scalar/dictionary expectation. |
| failure | Invalid fixture metadata fails comparison. |
| cost | O(1) bounded JSON metadata. |
| Design | docs/aggregates.md:35, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0021

[Lines 107–121](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def expected_metadata(case):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently state ordered output/key types and original names for each known query. |
| inputs / outputs | Case -&gt; output types, full key types, names. |
| invariants | COUNT nonnull bigint; SUM(int32) bigint; SUM(bigint) numeric38,0; AVG numeric38,s. Group types from actual fixture catalog; aliases/default names preserved. |
| ownership | Ordinary comparison-only arrays; never passed to driver as descriptors. |
| failure | Unsupported literal/kind/shape or actual mismatch fails oracle. |
| cost | O(targets+groups), no SQL/native calls. |
| Design | docs/aggregates.md:35, include/crown/frontend/bind.hpp:9, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0023

[Lines 124–128](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def make_case(name, outputs, tail, groups=(), batches=(), scale=18, **options):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep one original SQL fixture, independent reference description and physical trace together. |
| inputs / outputs | Name,outputs,tail,groups,batches,scale/options -&gt; case with actual original SQL. |
| invariants | Builder does not widen factories; native_request strips all reference-only fields. |
| ownership | Finite test-owned dictionaries/lists/text. |
| failure | Construction/real binding/SQL errors fail test. |
| cost | O(fixture text and small list copies). |
| Design | [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0025

[Lines 131–198](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def fixed_cases():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate sixteen deterministic original-SQL/physical-boundary controls, including hidden join separator and final-weight chains. |
| inputs / outputs | Generator -&gt; original SQL/catalog/physical NetBatch cases. |
| invariants | Cases carry only original SQL/catalog and complete physical edits. They include aliases, original-origin grouping, NULL, static sources, parameters, filter/no-op and bounded final-only source chains; expected groups remain reference-side. |
| ownership | Ordinary finite rows/cases; complete physical borrows owned later by driver. |
| failure | Every chain/bound checked before engine/runtime; real admission still must run. |
| cost | 16 finite traces, each small; final expansions &lt;=24 and each weight&lt;=8. Intermediate0→8→1 is never expanded. |
| Design | [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0027

[Lines 201–223](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def integer_cases():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate five mature-SQL recomputation cases for genuine varying integer casts. |
| inputs / outputs | Boundary/NULL/filtered global and raw grouping, nested COUNT, two-table join and self-join physical command traces. |
| invariants | Both ::integer and CAST syntax execute in the SQL engine; narrow SUM, raw/widened SUM and AVG have independent expected representations. Raw origins drive logical change detection. Two-sided join retains hidden a.id in GROUP BY to admit its actual CROWN source tree. |
| ownership | Python owns bounded physical fixtures; no native metadata/state is supplied. |
| failure | Malformed chains are refused by states(); SQL/native/metadata disagreement fails comparison. |
| cost | Five bounded expanded-bag traces; nineteen additional integer AVG scale traces come from scale_cases(). |
| Design | [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md) |

## B0029

[Lines 226–242](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L226); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def scale_cases():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate raw-bigint and checked-integer AVG cases at every admitted output scale 0 through 18. |
| inputs / outputs | For each scale, two genuine original-SQL traces with positive/negative halves, thirds, zero, NULL and disappearance. |
| invariants | The mature SQL query returns exact SUM and COUNT; the Python reference applies the shared Fraction rounding helper. Runtime requests the declared scale normally. |
| ownership | Finite shared physical fixture rows/commands, no runtime owner retained. |
| failure | Chain/type/scale or engine/runtime mismatch fails. |
| cost | 38 traces of six atomic commands; bounded expanded weights stay at most two. |
| Design | tests/integration/aggregate_sql_oracle.py:26, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0031

[Lines 245–267](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L245); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def random_cases():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate 64 reproducible short physical command traces from a fixed seed. |
| inputs / outputs | Fixed seed -&gt; joined-separator, self-join and filtered-global cases. |
| invariants | Each trace has 24 commands, complete before/final physical row weights and a bounded expanded source bag; seeded generation does not use native output as reference. |
| ownership | Ordinary test dictionaries/rows; no native maintained state mirror used as authority. |
| failure | Bound/authentication failure aborts before actual execution. |
| cost | 64*24 bounded commands; &lt;=3 edits/command; six-row pool and weights0..3. |
| Design | [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0033

[Lines 270–288](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def states(case):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Authenticate fixture physical chains and expand only atomic final states under hard small-bag guards. |
| inputs / outputs | Case -&gt; epoch0 and each contiguous final expanded physical state + normalized changed. |
| invariants | Each complete-row expected weight exact; zero entries removed; intermediate edits never expanded. Per-row&lt;=8 and total copies&lt;=24 checked before expansion. |
| ownership | External ordinary source dictionaries only; never feeds decoded joined facts. |
| failure | Assertion before engine/runtime for invalid chain/arity/bounds. |
| cost | O(finite edits+bounded source state copies); at most24 physical copies/table per reference boundary. |
| Design | tests/integration/sql_rows_oracle.py:162, include/crown/runtime/sql_rows.hpp:25, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0035

[Lines 291–295](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L291); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def integer(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read exact SQL integer sufficient statistics without floating coercion. |
| inputs / outputs | Non-NULL int/Decimal/text -&gt; exact Python int. |
| invariants | Bool/float rejected; Decimal construction is exact and equality rejects fractional text. |
| ownership | Temporary scalar only. |
| failure | Assertion/value conversion failure fails oracle. |
| cost | Bounded small scalar parsing; no native math implementation. |
| Design | tests/integration/aggregate_sql_oracle.py:99, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0037

[Lines 298–299](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L298); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def scalar(value, kind, postgres):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reuse existing SQL-engine scalar canonicalization at typed field boundaries. |
| inputs / outputs | Raw engine value, known kind, engine choice -&gt; canonical JSON-compatible scalar. |
| invariants | Postgres textual bool/int/null conversion from existing helper; DuckDB native types canonicalized; no equality normalization by value classes. |
| ownership | Returns ordinary expected scalar. |
| failure | Existing conversion failure propagates. |
| cost | One field plus its actual text/decimal byte work. |
| Design | tests/integration/sql_rows_oracle.py:32, tests/integration/sql_rows_oracle.py:208, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0039

[Lines 302–325](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L302); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def decode_groups(case, records, postgres):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode mature SQL group keys and original outputs, deriving only AVG from SQL SUM/COUNT. |
| inputs / outputs | Complete reference result records -&gt; unique full-key group map. |
| invariants | Reference arity exact; absent group differs from NULL-valued row; counts/sums read exactly; AVG denominator/non-NULL numerator consistency checked. Native local numeric result rules applied explicitly, not engine floating AVG. |
| ownership | Owns ordinary expected key/value JSON; no runtime states touched. |
| failure | Duplicate keys/shape/nonexact integers/negative counts/invalid NULL sum-count relation fail. |
| cost | O(reference groups*target fields), exact Fraction helper per AVG; SQL already computed join/group/statistics. |
| Design | tests/integration/aggregate_sql_oracle.py:76, tests/integration/aggregate_sql_oracle.py:99, tests/integration/sql_rows_oracle.py:208, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0041

[Lines 328–335](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L328); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def reference_snapshot(case, sequence, expanded, physical_changed, group_records, logical_records, postgres):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture one independent committed SQL boundary and full logical-bag identity. |
| inputs / outputs | Sequence,expanded physical sources, SQL aggregate/logical records -&gt; reference frame. |
| invariants | Logical Counter from SQL rows, not Python joins; includes complete original required columns or unit representation; changed from normalized physical state. |
| ownership | Ordinary eager reference maps/Counters, no native ownership. |
| failure | Shape/conversion/group errors fail. |
| cost | At most576 two-occurrence assignments in this bounded cohort, plus group/field conversion. |
| Design | tests/integration/sql_rows_oracle.py:162, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0043

[Lines 338–364](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L338); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def duckdb_reference(case):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute each bounded final physical state in required in-memory DuckDB and fetch independent aggregate plus logical-source SQL results. |
| inputs / outputs | Case -&gt; full mature SQL reference trace. |
| invariants | Default binary collation checked; real DDL/inserts; same original source clauses; target arity/key engine types checked; exact SUM/COUNT only. No skip/install/fallback. |
| ownership | Private in-memory connection closed in finally; standard test DTOs outside query account. |
| failure | Missing DuckDB, unsupported SQL, schema mismatch or assertion fails the oracle. It neither installs nor falls back to another engine. |
| cost | Bounded table rebuilds and two SQL queries per boundary; cold reference cost distinct from native runtime grants. |
| Design | tests/integration/sql_rows_oracle.py:173, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0045

[Lines 367–370](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L367); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def substitute_parameters(text, case):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reuse existing safe literal writer for the known predicate-only placeholder fixture. |
| inputs / outputs | Reference SQL + actual typed source parameter values -&gt; complete PG reference SQL. |
| invariants | Placeholders only in fixture predicate expressions, never quoted text; not a general arbitrary SQL rewriter. Native parameter admission remains genuine factory. |
| ownership | Returns ordinary SQL text; literals escaped by pinned W05 helper. |
| failure | Missing/invalid parameter fails before SQL. |
| cost | O(fixture SQL/parameter bytes). |
| Design | tests/integration/sql_rows_oracle.py:195, tests/integration/sql_rows_oracle.py:260, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0047

[Lines 373–377](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L373); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def json_rows(query, arity):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap a known complete reference query for exact nullable PostgreSQL row transport. |
| inputs / outputs | Query + complete expected arity -&gt; json_agg array of text fields with NULL preserved. |
| invariants | Aliases cover every field, no native-output arity drives SQL description; empty result is \[\]. |
| ownership | Owned SQL wrapper text only. |
| failure | SQL/shape failures surface in caller; no dropped-field fallback. |
| cost | O(arity+SQL bytes); engine aggregates bounded reference rows. |
| Design | tests/integration/sql_rows_oracle.py:269, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0049

[Lines 380–403](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L380); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def postgres_reference(case, postgres):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute bounded final states in the explicitly selected private PostgreSQL helper and collect independent aggregate and logical SQL results. |
| inputs / outputs | Case + existing started PG helper -&gt; reference trace. |
| invariants | Drops/recreates only fixture tables in private cluster; independent gdesc arity/full-key types; final-only TRUNCATE/INSERT states; both aggregate and logical SQL; exact sequence coverage. |
| ownership | Existing caller owns PG lifecycle; ordinary scripts/results are reference work. |
| failure | PostgreSQL setup, SQL, description, JSON or shutdown failure propagates; no automatic engine switch. |
| cost | Bounded generated SQL per trace, two result queries per boundary; uses pinned shared helper subprocess/timeouts. |
| Design | tests/integration/sql_rows_oracle.py:223, tests/integration/sql_rows_oracle.py:260, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0051

[Lines 406–412](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L406); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def group_map(groups):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate native snapshot shape/uniqueness by full hidden group key. |
| inputs / outputs | List of {key,values} -&gt; exact keyed records. |
| invariants | Key/value must be arrays; canonical key retains NULL/bool/int identity; equal projected rows do not collapse. |
| ownership | Owns ordinary parsed response index, no native tuple/fact authority. |
| failure | Malformed/duplicate group key assertion fails. |
| cost | O(groups*key serialization), external comparison work. |
| Design | [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0053

[Lines 415–423](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L415); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def output_diff(before, after):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive exact full-key before/final aggregate output events from independent SQL snapshots. |
| inputs / outputs | Two reference group maps -&gt; unique key/before/after events. |
| invariants | Absent uses null; present NULL tuple remains array; same rendered values suppress; equal outputs from distinct keys retained separately. |
| ownership | Owns expected ordinary event dictionaries. |
| failure | Invalid map semantics fail earlier decode checks. |
| cost | O(union of reference group keys+value comparisons), outside native grants. |
| Design | [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0055

[Lines 426–484](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L426); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def session_epoch(encoded):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently decode the test driver's actual GroupEpoch spool bytes before semantic comparison with mature SQL output. |
| inputs / outputs | Lowercase frame hex in; validated known-version frame metadata and key/before/after nullable tuples out. |
| invariants | Python stdlib checks frame size/header, body length, payload and prefix hashes, tag, bounded row/cell counts, legal presence flags, typed scalar encodings and exact EOF. Missing tuple is distinct from a present tuple containing SQL NULL. This is a bounded fixture decoder, not a general codec, descriptor/type-binding validator or durability authority. |
| ownership | Owns ordinary decoded Python bytes/lists/dicts only; native state and sink files remain in the C++ driver. |
| failure | Malformed/truncated/unsupported fixture output aborts via assertions or Python hex/UTF8/date/struct parsing errors; the enclosing oracle reports the failed comparison/run. |
| cost | O(hex/frame bytes plus decoded cells/events) Python work/storage for the native bounded fixture output. The 128 MiB check occurs after bytes.fromhex; this is not preallocation admission for arbitrary external hex input. Event and row loops check 100,000 events and 1,000 cells per row. |
| Design | [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0057

[Lines 487–515](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L487); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def compare(case, observed, expected):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare native snapshots and atomic aggregate events with independently recomputed typed SQL traces, including decoded Session spool output when selected. |
| inputs / outputs | Original case, C++ response and DuckDB or explicitly selected PostgreSQL reference trace in; assertion success out. |
| invariants | Full group keys remain unique; metadata/types, scalar identity, C sequence, changed flags and before/after event diffs match SQL. Session frame hex is decoded before its output is compared. This function checks output/native sequence, not the full W/I/C/D frontier tuple; unit Session tests cover those frontiers. |
| ownership | Borrows parsed response/reference maps; \`frame_hex\` is removed from that local response epoch after decoding and replaced with ordinary decoded output. |
| failure | Malformed or mismatched values fail assertions with case/sequence context; Python assertions must remain enabled. |
| cost | O(finite snapshots/events/typed serialized bytes), including one independent spool decode for each Session epoch; no native or SQL mutation. |
| Design | [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0059

[Lines 518–531](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L518); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def native_request(case, backend, rebuild=False, checkpoint=False, session=False):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one restricted native-driver request for a known SQL case/backend and one selected reconstruction mode. |
| inputs / outputs | Case/backend and mutually exclusive rebuild/checkpoint/session flags in; fresh request dictionary containing original catalog/SQL/AVG/batches plus permitted parameters and limits out. |
| invariants | Reference groups, expected SQL outputs and oracle descriptions never enter native binding as descriptors. Nested case objects remain shared; main's mutually exclusive test-script flags select at most one reconstruction mode. |
| ownership | Returns a fresh outer dict; nested catalog/batches/parameters remain owned by the case and are not deep-copied. |
| failure | Malformed fixture values fail in surrounding validation/native execution; this adapter does no error translation. |
| cost | Fixed field assignments and backend-qualified ID construction; nested serialization happens in the subprocess caller. |
| Design | [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0061

[Lines 534–542](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L534); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def reference_contract():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check oracle representation edge cases before native or SQL execution. |
| inputs / outputs | No input -&gt; typed JSON, NULL/absence, equal-output distinct-key and exact ±half assertions. |
| invariants | Exercises comparison contract only; no native/SQL/mature-engine evidence is implied. |
| ownership | Finite local expected maps/Fractions. |
| failure | Any helper/representation mismatch aborts test. |
| cost | Fixed tiny pure-Python work. |
| Design | tests/integration/aggregate_sql_oracle.py:26, [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |

## B0063

[Lines 545–602](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L545); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the bounded SQL oracle in direct, physical-rebuild, checkpoint or durable Session-reopen verification mode. |
| inputs / outputs | Select one native/direct-rebuild/checkpoint/Session mode and explicit mature engine. Run 123 cases on both backends, including 24 varying-integer cases; compare independent SQL snapshots and actual group output frames. |
| invariants | \`--session-every-epoch\` is an oracle-script option, not a product CLI. In this mode the driver reopens after log, decision, delivery and checkpoint for each committed command; the oracle checks four reopens per epoch, initial plus per-epoch durable checkpoints, and independently decoded output against SQL. It does not claim host power-loss survival, history retirement, timing bounds or full W/I/C/D comparison here. |
| ownership | Python owns case/request/report data; the driver owns actual native Session/files; optional private PostgreSQL lifecycle is closed in the existing finally block. |
| failure | Driver exit, SQL failure, configured subprocess timeout, malformed frame, output mismatch or counter mismatch aborts the script; Session-mode driver timeout is 3600 seconds and other modes use 600 seconds. PostgreSQL mode requires its explicit binary and has no engine fallback. |
| cost | 246 bounded native cases. Session mode performs four genuine recoveries and one checkpoint per committed command; harness timeouts remain limits, not CPU/delay claims. |
| Design | [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp), [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), Refactor.md:1325, [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0064

[Lines 603–606](../../../../../tests/integration/sql_aggregate_runtime_oracle.py#L603); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__": main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke main only when the Python oracle is executed as a script. |
| inputs / outputs | Script invocation dispatches main; importing module defines fixture/reference helpers without starting native or SQL work. |
| invariants | Required engine/no-fallback and assertion controls remain enforced inside main. |
| ownership | No driver/runtime owner at import or guard. |
| failure | Invocation propagates main failures to process exit. |
| cost | One guard check. |
| Design | [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [tests/integration/aggregate_sql_oracle.py](../../../../../tests/integration/aggregate_sql_oracle.py), [tests/integration/sql_aggregate_runtime_oracle.py](../../../../../tests/integration/sql_aggregate_runtime_oracle.py), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/reference/sql_rows_driver.cpp](../../../../../tests/reference/sql_rows_driver.cpp), [docs/sql_aggregate_binding.md](../../../../sql_aggregate_binding.md), [tests/reference/sql_aggregate_runtime_driver.cpp](../../../../../tests/reference/sql_aggregate_runtime_driver.cpp) |
