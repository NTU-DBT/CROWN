# Decision 0013: affected-record support journals and undo

Status: R04 verified, 2026-11-05; the [verification audit](../verification/runtime-journal-2026-11-05.md)
records the complete 39-test compiler/sanitizer/clean-source matrix.

## Decision

Keep the validated `PhysicalPlan`, the single logical `NativeSetUpdate` input,
the support propagation rules, and the public support-handle identity from
[decision 0011](0011-reference-support.md). Replace full-state staging for a
real update with a lazy set of relation-local storage journals and a prepared
metadata undo stack. The runtime remains single-writer and in-memory.

The first mutation to a reference relation opens its `ReferenceTable::Journal`.
Each table journal records inverse row/index membership changes. Metadata
changes are represented by undo entries prepared before mutation: inserts are
removed during rollback, in-place changes retain the old record or counter,
and erases extract existing map nodes for allocation-free reinsertion. The
runtime records each affected state change in the public journal as propagation
proceeds. A record stores its local ordinal, causal event ID, support handle,
logical tuple, and before/after membership, child state, or projection count.
Every record pins its tuple payload, including for deleted memberships.

On failure, metadata undo entries run in reverse order before the opened table
journals roll back. Both paths restore the previously visible rows, indexes,
logical tuple IDs, metadata, answer, sequence, and public handles without
allocating. Arena high-water slots, table revisions, and private arena
generations may still advance. A no-op has no journal and consumes its valid
sequence with zero work and zero metrics.

All throw-capable journal, undo, queue, and result-artifact preparation
finishes before the commit barrier. Commit is a no-throw operation: commit the
opened table journals, destroy their private scopes and the metadata undo
nodes, then advance the runtime sequence. The public journal keeps affected
record pins and owned before/after values. It does not retain old table state
or metadata maps. The engine does not retain successful journals; their
lifetime and retained-value cost belong to callers.

Transition capture remains optional. When `capture_transitions` is enabled,
the journal also holds propagation events and the epoch holds owning local
membership transitions. Native event 1 has cause 0. Child-key events receive
IDs when enqueued and refer to the event that caused them; application ordinals
record actual FIFO or LIFO order. Event IDs, causes, and accounting are created
even when the event vector is disabled. Every real update accounts for the
native update plus its child-key events; no-ops report zero.

## Consequences and limits

Public journals survive subsequent updates and can outlive the runtime while
their caller retains the `SupportEpoch` or its shared journal. A journal is a
per-update diagnostic record, not a frozen before/after query snapshot, an
outside-context object, an answer-delta stream, or a D01/D02 cursor/liveness
protocol. The runtime keeps no journal history. Captured transition keys and
diagnostic snapshots own additional values, so caller retention and report
serialization costs are outside the kernel's update metrics.

The 20 metric counters include four historical copy counters that remain zero.
`saved_child_flags` counts only flags copied into metadata undo entries; it
does not count public journal before/after copies, allocations, bytes, strings,
or CPU time. `work_limit` is an exact abstract-work limit, not a memory-byte,
allocator, or time quota. Arena statistics aggregate record and slot counts
across reference tables and are not byte accounting.

The trace reader continues to accept v1 logical native input. The CLI emits
v2 reports using `reference_incremental_journal`; the v1 report definition is
historical and remains frozen. Neither report is an import format, checkpoint,
recovery log, or physical update protocol.

R05 physical adapters remain open: this runtime does not route a physical row
to SQL aliases, consolidate multiple physical derivations, or apply a
multi-alias physical epoch. The implementation establishes no general CROWN
update bound or output-sensitive complexity guarantee. External G2/V02 proof
review remains outstanding.

## Validation status

All 39 tests pass GCC Debug/Release, ASan/UBSan, Clang18 and a fresh source-only
Release build. Independent subtree/oracle checks and journal replay cover
manual and generated updates under both queue orders; allocation-failure,
retained-value and versioned diagnostic checks are included in the audit.
