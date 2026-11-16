# Inspectable original SQL aggregate binding

The source maps contain **11,947 source-pinned contracts in 9,590 blocks** across
700 maintained code files / 162,631 lines / 18,241 mapped blocks. Every inventoried
line belongs to an inspection block. All 5,605 selected production scopes and
all selected example/tool scopes have authored contracts. Remaining selected
manual gaps are **3,698 test scopes**; structural coverage alone is not a usage
specification or correctness proof. Start with the [source index](../code_specs/README.md)
and [primitive cards](../code_specs/primitives.md).

This adds 445 contracts after [v20](human-inspection-v20-2026-11-12.md): 350 for
observation, epoch/prepared-epoch and physical/window failure tests, plus 95 for
the original SQL compiler. The compiler review reconciles 1,409 existing records
against their exact original cards and current source. One misleading epoch-view
failure string now states the successful same-journal insertion actually checked;
it no longer attributes registration release to a default cursor destructor.
Assertions and control flow are unchanged. The 350 test-review cards add no
execution claims of their own.

The [compiler contract](../sql_aggregate_binding.md) explains genuine binders,
original column identity, nullable decoding, full native-head coverage, cold AST
ownership and separate versioned digests. The receiving [verification](w06-sql-aggregate-binding-2026-11-12.md)
records strict Debug/SAN 15/15, full test-disabled Release, relocated installed
SDK and targeted first-arena failure/retry controls. All 327 predecessor test
commands/properties remain, plus one compiler test. No full-suite result is inferred.

The source/account/work and error boundaries are explicit in the block cards.
Two checked decodes replace the unsafe proposed clone API. One common existing
parser gate protects native C parsing/deparsing; the public compiler translates
ordinary admission errors at one boundary and propagates allocation and parser
contract failures. There is no runtime retry or undo framework in this compiler,
and the documentation tools add no application overhead. The paper mapping in
[code review](../code_review.md) remains authoritative; local SQL, ownership and
durability contracts do not acquire paper bounds from a citation.

Seal: `build/verification/human-inspection-v21-progress-v1.json`; frozen source:
`build/verification/human-inspection-v21-source-v1`. Root evidence is the compiler
implementation packet, including all failed setups and later corrections. V20
and its frozen source/evidence remain immutable. Main native builds remain active;
the protected private compiler builds and relocated SDKs must not be rebuilt.

W06 stays in progress. A separate private group-only runtime proposal has strict
receiving tests after two fixture repairs; it is not maintained or sanitizer/
independent-SQL accepted here. Queue/session/WAL, durable rejection and uncertain
outcomes, separate input/committed/output frontiers, checkpoint/rebuild and CLI
remain open, as does varying-int32 column SUM admission. The full ledger stays
56 verified / two in progress / 20 not started. Continue from the [handoff](../handoff.md).
