# Human inspection V32: checked varying integer aggregates

The full Refactor.md goal remains active: **56 verified / 2 in progress
(A02/W06) / 20 not started**, 78 total. A02 still blocks C04/B01. This checkpoint
implements varying integer aggregate arguments and continues individual source
inspection; it does not close the full W06 or release decision.

The implementation packet is
[w06-varying-int32-implementation-v1](../../build/verification/w06-varying-int32-implementation-v1/next-implementation.md).
The previous exact handoff is [V31 history](../handoff-history-v31-2026-11-13.md).
The seal and source snapshot are `build/verification/human-inspection-v32-progress-v1.json`
and `build/verification/human-inspection-v32-source-v1`.

## Direct implementation and authority

Only three of 355 production paths change; 352 remain byte-identical to V31.
The [aggregate interface](../../include/crown/frontend/aggregate.hpp),
[compiler](../../src/frontend/aggregate.cpp) and
[shared projection](../../src/runtime/aggregate_detail.hpp) add one sorted,
deduplicated immutable column-guard vector and its borrowed accessor. There is
no new mutable row/group/operator field, catch, rollback journal or native scalar
alternative. The two actual mutable runtime owner files remain byte-identical.

Physical input and raw grouping types remain bigint. Genuine source projection
selects raw ColumnRef leaves and leaves casts in kernel SQL. The ordinary
narrowing admission boundary was AggregateCompiler::argument, rather than the
composition physical_type(int32) switch identified in the previous handoff.
The compiler records an inner integer narrowing before final argument type or
measure deduplication, preserving COUNT and narrow-then-widen behavior.

Projection checks contributing non-NULL values against the inclusive int32
bounds before group changes. NULL passes. Filtered, unmatched and consolidated
net-zero changes produce no contributing fact and need no aggregate evaluation.
Existing owner cleanup unwinds both source/native and group preparation on a
cast refusal. SUM(integer) retains its final bigint bound; SUM(bigint) retains
NUMERIC(38,0); AVG(integer) keeps its wide numerator. Foreign freeze copies the
guards; descriptor rebind reconstructs them from authentic original SQL/catalog.
There is no new serialized guard DTO or format field.

These unconditional column/constant/cast arguments permit one guard per original
column. Future conditional expressions or aggregate FILTER need a fresh scope
review. This is local engineering, without a new CROWN paper complexity claim.
See [binding](../sql_aggregate_binding.md), [runtime](../sql_aggregate_runtime.md),
[batch](../aggregate_batches.md) and [error handling](../code_specs/error_handling.md).

## Exact receiving evidence

[Receiving acceptance](../../build/verification/w06-varying-int32-implementation-v1/receiving-acceptance-v1.json)
records passing evidence for all **21 affected test names** in Debug and
ASan/UBSan with leak checks. The initial 21-test commands each passed 17 tests
and rejected four oracle modes at one unsupported join fixture. After adding
its required hidden id separator, only those four Python modes were rerun.
Final C++ is identical across these gates; the later native-input change is
that one Python fixture. Initial command exits and failures remain recorded.

| Profile | Initial 21-test command | Corrected four oracle modes |
| --- | --- | --- |
| Debug | 17 pass, four fixture failures; 129.13s | 4/4 pass; 1,074.57s |
| ASan/UBSan/leaks | 17 pass, four fixture failures; 369.22s | 4/4 pass; 1,768.39s |

Each final DuckDB 1.5.4 mode checks 123 original-SQL cases on both backends:
246 native cases, 3,952 snapshots and 3,706 atomic epochs. The 24 new varying
integer cases include all nineteen AVG scales, raw/narrow/widened arguments,
NULL, boundaries, raw grouping, filters, joins and self-joins. Mature SQL runs
the actual casts and recomputes values; exact Fraction rounding supplies the
documented local AVG scale and expected metadata follows the local type policy.
Direct, whole-physical rebuild, checkpoint and durable Session modes all pass.
Each Session profile additionally verifies 14,824 cold reopens and 3,952 actual
checkpoints, with independently decoded sink epochs.

Focused C++ tests cover opposite signed contributions whose individual sums
exceed bigint but whose consolidated final sum fits, uncaptured/captured paths,
final overflow rollback, inclusive cast bounds, nested COUNT, a wide AVG-only
numerator, sorted two-column guards, exact/one-under work and foreign-freeze
allocation cuts. Actual Session tests cover pending cast Reject, I/reader
progress without C/D, complete filtered source preservation and a checksum-valid
false Reject rejected before torn WAL/sink repair. Existing Session fault,
descriptor, checkpoint, record, input and actual CLI controls also pass.

Complete production OFF Release builds. The relocated 229-file SDK passes
8/8 in 4.21s: standalone/current public header, six full public unit consumers
and installed CLI. Its original prefix is absent. Nineteen of 21 archives are
byte-identical to V31, including recovery and the parser; only aggregate and
composed aggregate runtime archives change. Only aggregate.hpp changes among
installed headers. There are 25 checked strict flag records. All 347 test names,
properties and previously resolved commands are preserved; OFF registers zero.
Earlier broad builds resolve 59/40 formerly unbuilt commands in Debug/SAN;
this is compilation availability, not test execution.

## Costs and retained corrections

The actual old/current installed Release comparison uses the same client source
over four legacy grouped/global and captured/uncaptured profiles. Sixteen
updates preserve receiving allocation counts, covered apply new attempts,
selected work and exact binding images, with explicit COUNT/SUM/empty snapshot
checks. Immutable program storage adds **56 accounted payload/requested bytes**,
including foreign freeze. Program/Epoch/Metrics remain 16/160/72 bytes in that
build. Nonempty guard backing is additional cold retained storage. U guarded
columns add U selected checkpoints per projected row/fact, including NULL; a
warmed two-column update asserts two extra checkpoints and zero covered new
calls. Legacy programs still pay the accessor/empty-loop check. This establishes
no CPU timing, malloc/RSS or portable ABI guarantee.

There are 27 recorder jobs: 21 successful exits and six retained failures
(two deliberately interrupted overly broad builds, two test-only compile
failures and two initial oracle-fixture commands). The six interrupted target
outputs were rebuilt afterward. Three exact input cohorts cover the unchanged
1,193-path native set; nine paths change versus V31. Every recorded command has
zero in-command input drift. Root documentation-checker corrections are also
retained: recursive seal shape/order, actual unused-map key and old unbuilt
command resolution. They are separate from native implementation failures.
See [cohorts](../../build/verification/w06-varying-int32-implementation-v1/input-cohorts-v1.json)
and [registration amendment](../../build/verification/w06-varying-int32-implementation-v1/registration-comparison-v2.json).

## Human inspection and remaining work

The [source map](../code_specs/README.md) covers 748 files, 171,588 lines and
19,357 blocks, with 15,338 contracts in 12,927 blocks. V32 adds 132 cards:
eight root implementation/test cards, 63 existing API-test cards and 61 existing
cursor/initialization-test cards. Separate independent amendments correct six
and ten author cards; original author evidence remains immutable. Those two
documentation lanes execute no native tests. Root also rechecks the 215 old
cards attached to changed sources, updates type/guard/caller semantics, rekeys
two signatures and normalizes/deduplicates references. The exact delta records
355 changed predecessor objects, including reference-only edits.

All selected non-test semantic regions have cards; **1,223 existing-test regions
still need individual cards**. All anchors, source hashes and 115,783 generated
local links pass. Structural maps, comments and card presence are not semantic
proofs or a blanket certification of every retained comment.

Root designed, implemented and verified; Luna Max authored two bounded test-card
packets; one inherited-model lane independently reviewed source/design and both
card sets. No Astra invocation was needed. No full 347-test, current Clang, CPU
benchmark, complete W06 or release claim is made. Next is the complete original
W06 requirement audit and continued test-card work. R2 history retirement remains
separate; concurrent B01/B05 drafts remain unaccepted with prior provenance.
