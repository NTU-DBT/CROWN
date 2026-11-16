# Excluded O07 runtime overlay review

Status: independent static review of the first excluded runtime slice,
2026-11-07. O07 remains `not_started`. Frozen native P07 inputs were not
changed. This reviewer ran no build, CTest, runtime probe or binary. The
baseline hand-trace observations concern the old runtime; compiler-only
checks and forthcoming overlay tests do not establish native acceptance.

Reviewed the O07 preflight and baseline README, all ten overlay header/source
files, unified patch, baseline/overlay hash inventories, ABI include audit and
patch/build/audit scripts. Source references below are relative to
`o07-runtime-proposal/overlay/` and describe the inspected revision.

## Findings requiring disposition

1. **Partial nested work cannot be detected by total magnitude.**
   `src/runtime/physical.cpp:112–125` considers physical work inclusive and
   derives exclusive work whenever `metrics.work >= support_work`. But
   `route():204–209` performs a support stage before charging its work to the
   physical coordinator. That charge can fail, or the support stage can fail
   after accumulating partial work. If physical-only work already exceeds
   support work, for example because enforced-constraint validation scanned
   many source rows (`:164–174`), the inequality still holds. The available
   inclusive total then omits support, and the advertised exclusive difference
   subtracts work that was never incorporated. The earlier 4-versus-40 check
   catches only the case where the raw number is smaller. Track successfully
   incorporated support work or an explicit incomplete-charge state instead.
   Required coverage includes a constraint-heavy failure with raw physical
   work greater than support, plus failure inside the support stage. Reported
   immediately to root, the overlay author and independent test author.
2. **Dropped-trace counter loses overflow status.**
   `src/runtime/observation.cpp:151–152` saturates `trace_dropped` but discards
   the saturation flag through a local `ignored` variable. `trace_truncated`
   already means capacity truncation and does not distinguish an exact maximum
   count from overflow. Preserve/reset a dropped-counter saturation flag or
   explicitly define maximum as a capped lower bound, consistent with other
   metric/lifetime overflow diagnostics. This must remain nonthrowing and must
   not alter mandatory runtime budgets. Reported to root and the overlay author.

## Supported static conclusions

- Off mode returns no collector or trace buffer. Optional hooks guard on the
  collector; `PhaseTimer` checks clock enablement before any clock expression.
  Existing mandatory counters, cap checks, event IDs, journals, routing and
  result operations remain in place. Legacy full transition capture is an
  explicitly rejected conflict with off. Optional observation does not charge
  mandatory work. Default timed preserves legacy phase timing availability.
- Registry fields retain layer/accounting/unit metadata. Support work is a
  component of physical work, while delta view/cursor work is a separate
  domain; phase subsets and prepared spool gauges are documented. Unentered
  layers remain unavailable, disabled timings are distinguished from zero,
  optional counters saturate nonthrowingly, and attempts differ from committed
  state changes. The physical partial-charge exception is finding 1 above.
- One shared observation state has fixed-size summaries and a trace vector
  resized only at admission. Mutation, commit, rollback and release hooks use
  scalar/POD operations and preallocated record writes. Explicit trace export
  allocates an owned copy; its vector contains only numeric records. No JSON,
  UTF-8 conversion, rows, pins, borrowed strings or observer callbacks enter
  collection or unwind.
- The outer admitted attempt owns its ticket. Nested support/physical begin
  calls expose layer availability without independently committing/aborting
  the outer delta summary. Rollback preserves existing cursor/physical/live
  cleanup order. Changed timer scopes finish before aggregate summary copies.
  Epoch output retains shared observation state after runtime release without
  introducing a back-reference ownership cycle.
- Codec and sink attempts/returns/failures are distinct from transfer and
  acknowledgement. The local shared Epoch data keeps callback-borrowed rows
  alive; deferred discard does not remove the row before callback accounting.
  Output leases block a new update while late output metrics update the prior
  summary. These rules require callback/move/destruction runtime checks.
- Direct and replay initialization temporarily suppress support collection
  through a move-restored shared pointer. Initialization and mode-change live
  bootstrap retain their existing separate counters and do not manufacture
  sequence-zero update attempts. Current-result cursor telemetry beyond the
  existing mandatory accounting remains a declared later slice.
- Sampling depends on sequence and configured period/offset, independently of
  data and timing. New attempts clear the logical trace prefix; unsampled,
  pending, committed, aborted, truncated and released states are distinct.
  Lifetime attempt saturation prevents sampled records from claiming newly
  unique attempt IDs. A capacity-truncated prefix is not a complete causal
  proof, even if its disposition says committed.
- Session reporting retains its existing creator-thread/reentrancy guard.
  Before empty/last/discarded output release, stop and drop, it captures bounded
  summary metadata. Drop releases the runtime and trace payload, retaining a
  scalar snapshot marked released; independently copied traces remain owned by
  the caller. No epoch is retained solely for these summaries.

## ABI/build preparation and required acceptance

The build helper uses overlay headers first, recompiles all eight existing
runtime translation units plus observation.cpp, and recreates a replacement
archive. It must not be mixed with the old runtime archive. The pinned
43-source baseline and quoted-include audit cover the recorded 49 non-runtime
translation units, including the batch/window/replay distinction. This is a
bounded source audit, not a general ABI guarantee. Tests/apps also need overlay
headers and a consistent `CROWN_RUNTIME_TESTING` definition. Patch generation
checks original hashes and never applies the patch. The audit script writes
new baseline files, so it must not be rerun to silently bless changed inputs.
Runtime evidence must identify the final overlay hash set after fixes.

Required first-slice runtime coverage remains: independent literal 40/44,
21/25 and duplicate-zero ledgers; exact rows/canonical states/mandatory limits
across off/counters/timed/trace; zero optional clock calls in off/counters and
untimed trace; nested support failure and both shapes of rejected support
charge; direct/replay initialization suppression; sampled retries and period
boundaries; capacities zero/one/exact/full; callback failures and deferred
release; pause/drain/abort/commit and standalone-owner lifetimes; session last
summary after empty output/stop/drop; persistent OOM at every added admission
allocation and throughout cleanup. Metric availability and saturation must be
checked independently of nanosecond magnitudes. Mandatory journal IDs and
causes should match the literal baseline where those events are admitted.

Full O07 additionally requires authority-aware human/JSON EXPLAIN, tree
JSON/DOT export, schema/mutation checks, resolved execution and benchmark mode
identity, broader cursor/build/input/window/queue phases and explicit unknown
memory/checkpoint/recovery fields. Neither this first slice nor the baseline
probe closes those gates, C01/C02, S05 or native P07 acceptance.

## Narrow correction review

Both findings above are corrected in the inspected excluded source; runtime
acceptance remains pending. No additional static blocker was found.

For finding 1, `physical.cpp:103–108,117–132,211–224` now records the support
work actually incorporated by successful coordinator charges. It marks the
accounting incomplete before entering the support stage and restores completion
only after the stage and charge succeed. Any exception closes this pending
update through rollback with that flag still false; a later route cannot erase
the failure. Both physical totals then remain unavailable regardless of numeric
magnitude. On success, exclusive work subtracts only the incorporated subset.
That subset cannot overflow independently because every addition is already
contained in the checked monotone coordinator total. A failure later in an
observer/view step leaves the already successful partition valid. All new
bookkeeping remains guarded by enabled observation and changes no mandatory
charge, limit or rollback ordering.

For finding 2, `observation.hpp:139–142` now retains
`trace_dropped_saturated`; `observation.cpp:108` resets it for each new outer
attempt and line 152 passes it directly to the nonthrowing saturating increment.
Nested begins preserve it, and ordinary snapshot/session/trace copying carries
it automatically. Capacity truncation and dropped-count overflow are now
separate facts. This public snapshot layout requires consistent recompilation
of the overlay runtime and all consumers, as specified by the existing ABI rule.

The unified patch includes both changes and the README explains the revised
semantics. Root reports a complete nine-unit overlay rebuild and matching
43-file original baseline; those are root/author compile reports, not runs by
this reviewer. The planned constraint-heavy ledger (raw physical work 107,
full inclusive work 147, cap 130), the ordinary 4/40 failure shape, and failure
inside support remain required independent runtime regressions. Raw output,
mandatory accounting, optional off clocks, trace capacities/lifetimes and
persistent-OOM sweeps still need actual overlay acceptance. Native P07 remains
untouched and O07 remains `not_started`.
