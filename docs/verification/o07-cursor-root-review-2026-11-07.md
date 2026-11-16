# O07 cursor independent root review — 2026-11-07

Static scope: frozen [cursor proposal](o07-cursor-observation-proposal/README.md),
package `5dcd916bda78bbe1bef6047a65b4a1fa7ef6ad405ee54877c8033b818d3b8259`.
No current static blocker was found. The seven independent runtime groups are
being prepared; compiler/link success does not establish their result.

The result factory keeps a fixed scratch summary through allocation/construction,
copies mandatory startup work at existing charge sites, and removes its scratch
pointer before returning. Failed construction records startup plus unwind and
marks separate cleanup measurement unavailable. Existing invalid-view/readability
and reader-count admission guards precede cursor identity creation. The ordinary
mandatory counters and limits retain their original charge sites.

Successful next, exhausted next and active failure end their intervals before
cleanup begins. Close is idempotent, unlinks views, closes frames, releases leases
and runtime ownership, then completes timing using a separately owned observer.
Publication uses a weak runtime reference; copied observations retain no rows,
plan, layout, journal or runtime. Destruction, replacement, explicit cancel,
invalidation, exhaustion and next failure have distinct reasons. Closed-call
rejections are outside active-call timing and do not change saved measurements.

Current-cursor clocks use the raw testing/platform seam, while active delta
attempts separately count nested cursor reads. Timing descriptors explicitly state
that an internal cursor can be contained in a delta wall phase and is not additive.
Backward intervals become unavailable; duration/counter overflow saturates without
a semantic error. Off/counters avoid optional clocks, while saved mandatory work
and lease cleanup remain active. The new registry entry changes snapshot layout:
all runtime and app/test/report consumers require one matching ABI build.

Committed gauges use existing readable barriers, numeric vector reservation and
stored table cardinalities. Bases count physical tables once despite aliases;
visible counts exist only for C* E factors. Missing logical source authority,
full-result count, allocator bytes and recovery/checkpoint facts remain unavailable.
No tuple scan, join enumeration or implicit minimum-height/cost claim is added.

Independent tests still must exercise exact rows/work/phases, multiple/empty/
Boolean/projected/generalized products, failure and persistent allocation unwind,
owner destruction and moves, clock zero/regression/overflow, nested accounting,
state rollback and gauge scope, companion fields/limits and optional-off behavior.
No native source or task status changes for this review.
