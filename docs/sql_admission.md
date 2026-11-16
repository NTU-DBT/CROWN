# SQL frontend and structural admission (F06)

`admit-sql` connects typed binding, grounded equality normalization and GYO
recognition. It reports whether the normalized query fits the frontend/core
contract. `admit-sql` itself returns no physical plan or height certificate. Separate
`lower-normalized` and `verify-height` workflows are documented in
[physical plans](physical_plans.md) and [height certificates](tree_oracle.md);
execution and session behavior remain separate contracts and are not implied
by admission. Every result explicitly records
`admission_scope:frontend_and_structure` and `execution_status:not_lowered`.
The [verification packet](verification/admission-2026-11-05.md) records all 23
tests passing across Debug/Release/sanitizers, Clang and a source-only build.

```sh
crown admit-sql INPUT.sql CATALOG.json [OPTIONS.json]
crown admit-normalized PROGRAM.json [WORK_LIMIT]
```

Source SQL uses the flat version-1 catalog and the bounded expression/type
contracts from [binding](sql_binding.md) and [normalization](sql_normalization.md).
Artifact input first passes complete bounded replay. Admission grounds a
legacy normalized-v1 program to v2 before recognition. It keeps every mutable
occurrence and evaluates both the body H and H plus the free-variable set F.
The extra F edge is a recognition device; it creates no table/runtime node.

## Statuses and precedence

| `admission_status` | Meaning / evidence |
| --- | --- |
| `admitted` | Supported frontend semantics and a completed structural decision. `route:free_connex` has acyclic H and H+F; `route:constant_empty` has a proven normalization contradiction and retains the actual shape classification. |
| `syntax_error` | Encoding, empty/multiple-statement or SQL syntax failure. Original parser code and coordinates are retained. |
| `semantic_error` | Names, ambiguity, type mismatch, invalid literal/catalog or missing/incompatible parameter values. The originating phase and diagnostic survive. |
| `unsupported_semantics` | A parsed construct requires an unavailable SQL feature, cast/type, row bag, nullable source policy, cross-occurrence predicate or output. The precise frontend diagnostic code is retained. |
| `cyclic_body` | Completed GYO leaves a cyclic residual in H. A full head does not change this result. |
| `non_free_connex` | H is acyclic but H+F has a cyclic residual, such as a projected path's two endpoints. |
| `resource_limit` | A parser/binder/normalizer/import/recognition limit stopped the request. No partial query class or admission route is returned. |

Configuration files and I/O are checked before compilation by the CLI. Valid
requests then run parsing, binding, normalization and recognition in that
order; the first frontend failure is reported. Unsupported clauses remain
unsupported even when another predicate would make the result empty.
Codes beginning `unsupported_` map to unsupported semantics; remaining
declared binding/normalization errors map to semantic errors. Parser errors
remain syntax errors, and `resource_limit` takes precedence over those groups.
Internal parser/IR invariant failures use the separate internal-error channel.

Only after the supported frontend finishes does the compiler consider a
constant-empty route. It still completes recognition and records the actual
body/head shape. A contradictory cyclic query can therefore report `admitted`,
`route:constant_empty`, `structure.query_class:cyclic`. This never presents
cyclic maintenance as part of the free-connex route.

Admitted source queries return exit 0. All admission rejections/resource stops
return JSON on stdout and exit 1. Malformed options/catalogs/artifacts and
file/usage failures return JSON on stderr and exit 2; invariant failures use
exit 3. A malformed executable artifact is an input error. A resource stop
while replaying/importing it is an admission resource result in phase
`artifact`.

## Options, parameters and limits

```json
{
  "schema_version": 1,
  "parameter_types": [{"type":"int64","nullable":true}],
  "parameter_values": [1],
  "limits": {
    "binding": {"work_limit":1000000,"expression_limit":100000,"recursion_limit":128},
    "normalization": {"work_limit":1000000},
    "recognition": {"work_limit":1000000}
  }
}
```

All fields except `schema_version` are optional. Parameter declarations use
the existing F03 format; values use exact typed scalar/NULL encodings.
Changing parameter values requires new normalization and admission. Missing
values or mismatched types are semantic parameter errors, while malformed
JSON/declaration documents are configuration errors. Unknown fields/versions
and floating-point integer limits reject.

Work limits accept unsigned integers or JSON null for unlimited. Binding also
has expression/depth caps. The source parser retains its fixed default 1 MiB
and AST-nesting limits. Recognition shares one budget across scope building,
body GYO and augmented GYO. Exhaustion discards partial analysis rather than
calling an unfinished residual cyclic. There is no fixed column/occurrence
mask and no global wall-time/memory guarantee.

The normalized-artifact CLI's optional work limit applies to recognition.
Import replay has the F05 host caps; additional v1→v2 grounding also has a
default one-million-work host cap, independent of serialized limits. The
C++ `admit_normalized` API permits an explicit grounding cap as its third
argument. The effective grounding limit is the tighter host/stored limit.

`work.binding` and `work.normalization` contain completed producer counts;
unfinished stages are null. Artifact replay costs are separate from those
stored producer counts. `work.recognition` records this recognition attempt,
including consumed work on a resource stop. These are abstract operation
counts, not benchmark timings.

## Evidence, outputs and examples

Every completed structural result contains body and augmented reduction
witnesses, failed cores, the synthetic-head index and `height_status:not_checked`.
Global structural diagnostics have null source coordinates; use residual edge
indices with `program.binding.occurrences` and their source locations. Name/
type/parser diagnostics preserve the original byte and Unicode coordinates.

The report includes the complete grounded normalized-v2 program once that
stage completes. Its nested `admission_status:not_checked` remains the frozen
normalization-component marker. The enclosing report records the subsequent
admission decision. Extracting a component program does not carry a trusted
physical plan or certificate.

```sh
# Admitted full path; executable lowering remains unavailable.
crown admit-sql tests/frontend/admission/cases/full_path.sql tests/frontend/admission/catalog.json
# Rejected projected endpoints, with H+F failed core.
crown admit-sql tests/frontend/admission/cases/endpoint_path.sql tests/frontend/admission/catalog.json
# Grounded constant head is admitted after format-2 normalization.
crown admit-sql tests/frontend/admission/cases/fixed_output.sql tests/frontend/admission/catalog.json
```

The machine-readable [support corpus](../tests/frontend/admission/manifest.json)
covers each declared SQL feature group, expected class/reason and applicable
manual/SQLite outputs. It includes aliases, composite equality, USING/NATURAL,
disconnected/nullary/Boolean queries, fixed heads/join keys, self-joins,
repeated scopes/outputs, local NULL logic, exact types/parameters, unsupported
SQL and every admission category. An independent literal join-tree enumerator
checks generated structural families without calling production GYO.
