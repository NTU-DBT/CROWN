# Native operator memory reports

`runtime::memory::capture(owner)` accepts a SupportRuntime, PhysicalRuntime,
DeltaRuntime or QuerySession. A successful attempt holds an immutable native
report with the original query account, epoch and physical-plan hash. Capture
does not advance execution. Its control, arrays and temporary work use that
same account; retaining a report therefore consumes the configured query budget.
Copies share the captured value. A report remains readable after its runtime
closes and releases its storage without allocating.

The report joins three views of the same captured instant:

- `owners()` partitions every resident allocation by its actual attribution.
  The partition includes older held generations, reports, cursors and output.
- `tables()` identifies each current support or physical-source table and its
  actual table and tuple-arena owners. It records live, retained and free slots,
  values, index entries, directories and undo/history counters.
- `operators()` records support records, survivors, parent and visible keys,
  physical derivation keys, and materialized Delta factor rows and index
  memberships. Each entry identifies the owner that funds its metadata.

Owner, purpose and lifetime totals reconcile exactly with the captured account.
Table and arena owners join the same partition. Multiple bindings may reference
one owner; sum `owners()` once instead of adding repeated table/operator joins.
Logical record counts describe the current runtime; account totals can also
include retained older state. Counts alone do not imply a fixed byte size.

Requested bytes include allocator overhead; payload bytes describe the requested
payload. Active, retained and free-pool lifetimes distinguish current use from
reserved reusable storage. Allocation/free history and peak requested bytes are
historical counters, not additional resident bytes. The snapshot includes its
own resident report storage; diagnostic scratch is released before the final
account instant. Later activity does not change the captured numbers.

Private execution returns `pending` with the account partition and no committed
table/operator counts. A dropped session returns `released` with its remaining
account partition. A stopped session can still report committed runtime state.
A hidden visible factor or unmaterialized Delta image is explicitly unavailable
rather than reported as zero. The Delta coordinator uses `delta_node:UINT64_MAX`;
factor owners retain their node IDs.

Capture has finite work, owner, table and operator limits. Allocation failure,
exhaustion, overflow or inconsistent counts return a fixed stop and no partial
report. Failed capture preserves the runtime, prior reports and current resident
usage; historical allocation counters can still record attempted work. Diagnostic
work charges cover scans and sorting and are separate from execution allowances.

## CLI and explicit export

```sh
crown explain runtime plan.json --format memory-json
crown explain session plan.json --format memory-json --input events.jsonl --events 10
crown explain runtime plan.json --format memory-json --memory-limit-bytes 67108864
```

The format is `crown-query-memory`, version 1, validated by
[the schema](../schemas/memory-report-v1.schema.json). The library's explicit
`io::write_memory_report(report)` export and CLI JSON encoding use caller-owned
storage outside the query account. `--max-bytes` limits the completed encoded
output, before stdout publication; it does not cap temporary JSON encoding memory.
`--memory-limit-bytes` limits native query storage, including report capture.
The memory format applies to runtime/session commands. Proof and benchmark-label
options do not apply. Existing EXPLAIN formats retain their own schemas.

The [scoped verification record](verification/s05-operator-memory-native-2026-11-09.md)
preserves those tested cases. S05 native query-account acceptance is recorded in
[the final acceptance audit](verification/s05-native-acceptance-2026-11-09.md); the
[query memory contract](query_memory.md) documents the runtime cap and the
caller-owned JSON export boundary.
