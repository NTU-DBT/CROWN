# Schema evolution and executable artifact validation

F05 adds complete normalized-program schemas, bounded replay readers,
explicit CQ upgrades and [canonical identities](query_identity.md). The
[verification packet](verification/schema-2026-11-05.md) records all 21 tests
passing across the compiler/sanitizer/clean-build matrix.

The native readers implement the semantic contract; JSON Schema checks the
document shape. For example, an integer expression ID can satisfy a schema
and still refer to no expression. Passing a schema is not permission to
execute a plan.

| Artifact | Supported versions | Read / write rule |
| --- | --- | --- |
| Direct CQ document | 1, 2, 3 | Read with strict fields and exact scalar/reference checks. Default writer preserves the document version. |
| Standalone catalog | 1 | Validate complete typed metadata; unknown fields and versions reject. |
| SQL binding | 1 | `read_sql_binding` rebinds the owned source/catalog/signature and compares every field with the serialized artifact. |
| Normalized SQL program | 1, 2 | Version-specific complete replay; new producers emit v2 with grounded constant classes. V1 remains frozen. |
| Structural tree / height certificate | Tree 1; certificate 1, 2 | Structural trees retain their strict v1 codec. Height certificates use exact v1 replay or v2 symmetry/component replay, with strict schema/algorithm version matching. Canonical hashes do not replace proof replay. |
| Query identity | 1 | Deterministic inspection/cache-key output; recompute it from validated query/program input. It is not an executable plan reader. |
| Tuple layout / key projection | 1 | Immutable descriptors and explicit caller-token projection rebinding; [storage contract](storage.md). |
| Physical plan / lowering options | 1 | Full source/tree/program replay and exact typed artifact comparison; [physical contract](physical_plans.md). |
| Logical support trace / diagnostic report | Input 1, report 2 | Read strict native scoped-row traces as v1; emit journal-backed v2 reports. The v1 report definition remains historical; neither report is a checkpoint/import path; [support contract](runtime_support.md). |

Physical plan sources contain a generated CQ-v3 compile document with empty
physical data/events, or a replayed grounded normalized-v2 program. Lowering
does not mutate an input CQ document's version. Legacy normalized v1 is
explicitly grounded before physical tree validation, so stale geometry cannot
be reused. Physical replay has independent host lowering/identity and program
caps; stored unlimited cannot raise them. Producer limits remain intact on
successful replay. A change to the physical v1 producer's slots, work counts,
profile or serialization requires compatibility handling or a new version.

The height-certificate schema version is independent of the direct CQ document
version and of the exact `query_binding` document embedded in a certificate.
Direct CQ remains formats 1, 2 and 3; the binding still selects its canonical
CQ format from catalog metadata. P04 changes proof encoding and replay rules
only, without changing parser, CQ, or query-binding version contracts. See
[tree oracle and certificate versions](tree_oracle.md) and the
[P04 verification record](verification/planner-fast-paths-2026-11-06.md).

## Normalized program format 1

[sql-normalization-v1.schema.json](../schemas/sql-normalization-v1.schema.json)
defines success programs and diagnostic envelopes. Successful programs retain
the complete typed binding, specialized parameter values, core CQ version 3,
all occurrence adapters, ordered base routes and SQL output mapping. Adapter
expressions, columns, variables and occurrences use integer IDs; the core
uses its existing versioned names. There are no process addresses or parser
pointers. The core's initial relations and updates are empty because this is
a program, not a checkpoint of `AdapterState`.

The native executable reader accepts only successful artifacts. It reconstructs
owned state by source/catalog replay instead of trusting serialized indices or
operator wiring. It checks the full normalized result, including local
predicates, projections, repeated-column checks, routing, constants, types,
source locations, work counters, limits and the SQL EXISTS/output wrapper.
Any nested field that disagrees with replay fails instead of silently defaulting.
Duplicate JSON keys, incompatible versions and noncanonical typed scalar
spellings fail as well. JSON whitespace, object-key order and equivalent JSON
string escaping do not affect reading. Floating-point tokens cannot stand in
for integer counters or IDs.

The host `ProgramReadLimits` independently caps binding work, expression count,
recursion and normalization work. Serialized `unlimited` limits cannot disable
those host caps. On successful replay the stored limits remain intact; limits
are resource policy, not query semantics. A resource stop returns no executable
program. The CLI's default caps match the frontend defaults. This is not a
global wall-time or memory budget.

V1 replay semantics are tied to the pinned syntax parser, binding/normalization
rules and complete producer format. A change that renumbers instructions,
changes emitted work counters or alters canonical program fields must preserve
the v1 replay path or introduce an explicit new artifact version and migration.
The frozen [normalized-v1.json](../tests/frontend/schema/normalized-v1.json)
and [normalized-v1-fixed-head.json](../tests/frontend/schema/normalized-v1-fixed-head.json)
fixtures guard that boundary. Unsupported future versions are rejected.

```sh
crown normalize-sql INPUT.sql CATALOG.json > PROGRAM.json
crown validate-normalized PROGRAM.json
crown canonicalize-normalized PROGRAM.json
```

These commands never grant structural admission. Read/configuration/replay
rejection uses stderr and exit 2. Normalization itself retains its existing
stdout diagnostic/exit-1 contract. Internal invariant failures use exit 3.

## Normalized program format 2

F06 exposed a completeness gap in v1's structural geometry: a column fixed by
equality to a constant could remain in the free head and falsely make a path
projection non-free-connex. Format 2 propagates final equality-class constants
to `adapter.constant_columns`, with a typed value guard for every physical
column in that class. It removes fixed variables from core scopes/projections
and maps fixed output positions to constants. Every mutable atom remains,
including nullary projections with support counts over full physical rows.
OR/NOT do not create unconditional equality facts.

[sql-normalization-v2.schema.json](../schemas/sql-normalization-v2.schema.json)
defines this new success format. Failure diagnostics retain their format-1
envelope. Native import selects the replay rules by version; it never applies
v2 normalization while interpreting a v1 artifact.

```sh
crown upgrade-normalized PROGRAM.v1.json 2
```

The upgrader validates v1 replay, renormalizes with the same source/catalog/
specialization under host caps and emits v2. Same-version migration validates
and copies; downgrades reject. SQL answers and physical update semantics stay
the same, while core geometry/variable IDs and plan/certificate bindings can
change. Regenerate and validate plans for the new core. `admit-normalized`
performs grounded v2 admission for validated legacy inputs.

## Explicit direct-CQ migration

```sh
crown upgrade-cq INPUT.json TARGET_VERSION
```

`upgrade_document` supports 1→2, 1→3 and 2→3, plus a same-version validated copy.
It validates both the original and upgraded document, preserves all typed
values, query/head/occurrence semantics, initial physical rows and update
sequence, and changes embedded update encoding versions together with the
root version. Version 3 writes catalog defaults explicitly. No new keys,
NULL values or constraints are inferred.

Every downgrade rejects, even when a particular input might fit the older
format. Unknown target versions reject. The ordinary `write_document` still
preserves format 1/2/3 and rejects metadata or scalar information that cannot
be represented by the requested original format. The structural-tree and
certificate-v1 formats stay unchanged, including the original exact
query-binding bytes and validation semantics; height-certificate v2 is a
separate versioned proof format and v1 remains readable and replayable.

Physical-plan serialization, plan-cache installation, source-schema barriers
and online migration belong to later lowering/runtime tasks. A version or
digest alone does not make those execution boundaries available.
