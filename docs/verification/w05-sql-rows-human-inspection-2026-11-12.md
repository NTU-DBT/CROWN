# W05 nullable SQL rows and human inspection

W05 is verified for the explicitly admitted SQL families. The new
[nullable-row library](../sql_rows_runtime.md) supplies physical source rows,
plain SELECT bags, NULL-sensitive equality joins, DISTINCT, constants and EXISTS.
[W04](w04-aggregates-human-inspection-2026-11-12.md) separately supplies admitted
nullable GROUP BY and integer COUNT/SUM/AVG. Bare GROUP BY without an aggregate
rejects. These are separate APIs; joined aggregates, coordinated batches and
checkpoint/recovery integration remain W06 work.

The independent [acceptance review](../../build/verification/w05-rows-acceptance-scope-review-v1/README.md)
checks Refactor.md's unchanged W05 criteria against source and actual receipts.
The final seal is `build/verification/w05-rows-progress-v1.json`; acceptance is
`build/verification/w05-rows-acceptance-v1.json`. Frozen project source is
`build/verification/w05-rows-source-v1`. The older W04 and W05 foundation seals
remain immutable. W05 build directories remain reusable; recorded binary hashes
identify the bytes observed at the checkpoint, not immutable future build paths.

## Implementation and cost boundary

Start with [the compiler header](../../include/crown/frontend/sql_rows.hpp),
[runtime header](../../include/crown/runtime/sql_rows.hpp), then the
[implementation guide](../sql_rows_runtime.md) and source-linked block cards.
The factory binds actual SQL into immutable, account-owned source/schema/opcode
metadata. NULL is encoded by a canonical payload and a presence Boolean when
needed. Ordinary equality rejects missing operands; ordered output fields recover
every varying head field, keeping output decoding injective. Computed expression
slots retain their own fields; repeated column classes can share fields.

One full nullable-row count map per physical table authenticates the exact prior
row and weight. Enforced UNIQUE/FK indexes use SQL NULLS DISTINCT / MATCH SIMPLE
rules, including self-reference and empty keys. All aliases of one source share
one replacement epoch. New source and key nodes are prepared privately; native
commit precedes publication of funded handles and nonthrowing count edits. There
is no whole-state clone, second native count map or new source rollback framework.

One source allowance covers selected validation, key and alias work. The native
epoch keeps its separate original indexed allowance. Neither is a total CPU
meter: map comparisons, compiler workspace and cursor decode/copy costs remain
explicit. Owning results add a nullable output freeze and retain an immutable
program handle, including its metadata/constants, until released. Reader leases
exclude writers until terminal next/cancel/destruction. All calls are serialized.

All query forms use checked uint64 weighted intermediates. A product can overflow
before DISTINCT or EXISTS reduces the visible result. No Boolean-update bound,
saturating count rule, allocation-free cursor or latency speedup is claimed.

Cold constant liveness retains only constants read by frozen guards, operations,
predicates, projections or outputs, preserving slot IDs. In the pinned four-alias
query with a 1 MiB string parameter, retained payload falls from sixteen copies
to one and requested bytes from 16,784,756 to 1,055,052. The same query admits
under 3 MiB; a native regression checks the one-slot contract. These are retained
memory observations, not total compiler-workspace or timing measurements. The
change adds no update-path constant cache or lookup.

SQL NULL encoding, allocator/lifetime rules, constraint maintenance and failure
publication are local contracts. Paper provenance and exact versions are in the
[review guide](../code_review.md); weighted recurrence links are in
[weighted enumeration](../weighted_enumeration.md). These implementation choices
are not presented as paper theorems.

## Executed checks and freshness

| Gate | Observed result and scope |
| --- | --- |
| Strict GCC Debug selected cohort | 54/54, 207.41 s, before the final constant-liveness fix, its binding regression, oracle-helper changes and weighted-header comment clarification. Four current input hashes differ; historical full-cohort evidence. |
| Current Debug SQL family | 3/3, 52.04 s, with all current 1,127 maintained input pins. |
| Current ASan/UBSan/leak selected cohort | 54/54, 720.41 s, with the same current 1,127 pins; address/undefined instrumentation, leak checking and halt-on-error enabled. |
| DuckDB 1.5.4 row SQL | 55 SQL cases / 110 backend cases / 3,410 snapshots, both ordered and indexed native backends. |
| PostgreSQL 16.15 row SQL | 61 SQL cases / 122 backend cases / 3,782 snapshots, including unconstrained mixed-scale NUMERIC and untyped NULL inference. |
| Scalar SQL primitive | 3,439 matching-type DuckDB cases across 20 scalar opcodes; retained in the sanitizer cohort. |
| Existing set/grouped aggregate paths | Binding, normalization, admission and fixture gates pass; four W04 aggregate gates rerun in the 54-test cohort. |
| Installed SDK | Consumer links only installed CROWN::sql_rows; receiver cap/resident allocation, nullable DISTINCT and detached tuple/schema lifetime checks pass. |
| Registration | All 319 W04 command/property/backtrace records remain byte-identical after profile build-directory substitution; four appended tests make 323. Frozen scalar CMake prefix remains identical. |

Receipts are `build/verification/w05-rows-final-test-debug-v1.json`,
`w05-rows-final-sql-debug-v2.json`, `w05-rows-final-test-sanitizer-v2.json`,
`w05-rows-postgres-debug-v4.json` and `w05-rows-{install-debug,sdk-configure,sdk-build,sdk-run}-v1.json`.
All commands are terminal; raw LastTest logs and every earlier failed command's
receipt/preimage remain preserved. Current receipts have no input drift. The
earlier full Debug run is not labelled current-source full-cohort verification.

The row oracle executes original SQL in each engine, reconstructing only small
physical source bags in Python. Full PostgreSQL result arity and kind/decimal
typmods come from independent description, not a native-derived prefix. Typed
JSON identities distinguish false from zero. Binary/C collation, UTF8 and string
settings are checked explicitly. A private negative control drops one trailing
NULL output and its type; the current oracle rejects it. PostgreSQL runs use
private Unix sockets, are always stopped and leave no live child service. There
is no engine fallback, installation or skip in the registered oracle.

Native controls cover source identity, NULL versus present zero/false/empty,
hidden-row projection collisions, self-alias weights, filtered/no-op replacements,
UNIQUE/FK restrictions, generic NUMERIC/date/text domains and arithmetic overflow.
Input allocation cuts cover 53/70/54/71 positions for ordered/indexed with and
without capture; every failed epoch retries at the same sequence. Cursor failure
cuts cover five positions per backend; construction cuts cover five ordered and
seven indexed positions. Exact/one-under receiver and source-work limits,
borrowed-slot cleanup, retained schema/results and detached cursor leases pass.
These are per-fixture positions, not globally unique failure counts.

No full 323-test execution, R0/R1 release, Release/Clang matrix, W06 recovery or
new elapsed-performance experiment is claimed.

## Human examination and remaining review

The index has 4,097 source-pinned semantic contracts in 3,544 mapped blocks;
690 maintained files / 158,834 lines / 17,723 blocks have structural maps. Every
substantive new SQL-row scope has an individual contract. Accounted-plan and
Boolean support drafts were checked against callers and integrated; comment-only
changes preserve complete executable/literal tokens. One redundant inner support
catch is removed after tracing all four callers to their existing abort or RAII
rollback owner. Required outer boundaries remain. Documentation adds no runtime
instrumentation or checks.

Individual semantic review remains open for 2,554 selected production blocks
(564 include, 1,933 src, 57 apps). Structural mapping does not certify those
blocks. Delta/session drafts are queued separately and excluded from these
counts. Do not refresh a reviewed-source hash without checking the affected
contract and executable block. The full Refactor goal and release reviews remain
active.
