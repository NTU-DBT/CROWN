# Native invariant diagnostic memory

SupportRuntime, PhysicalRuntime and DeltaRuntime keep their existing
`inspect_invariants(options)` and `check_invariants()` behavior. Their independent
expected-state checks now use the original query account for owning sets, maps,
database snapshots, projected keys and live-factor regrouping. The physical
checker reads native record rows instead of exporting a full support snapshot.
The Delta inspector still derives expected live factors independently of the
bootstrap algorithm.

`InvariantReport::issues` uses an OwnerAllocator under the original account.
`InvariantIssue::key` is an InvariantKey with compact native values:

- `key.view()` borrows its typed values while the key remains alive.
- `key == caller_row` compares without exporting or allocating.
- Copying a key/report funds its new storage from the original account.
- Moving and releasing reports allocate nothing. Retained reports stay readable
  after the runtime changes or closes.

The new expected-state collections and issue values use attribution capture:15.
Native cursors, snapshots and projection helpers retain their existing allocation
attributions within the same query account. Empty reports retain their allocator
binding without retaining expected-state scratch. Temporary work closes before
inspection returns. `InvariantReport(account)` explicitly binds a caller-created
report; default construction does not create an allowance.

Inspection retains its logical work units and issue limits. Exhaustion returns
`complete=false`, so a partial report cannot be valid. Out-of-memory still
propagates as `std::bad_alloc` (including fixed MemoryFailure diagnostics), with
current runtime storage and older reports preserved. The existing account cap
also bounds diagnostic scratch and retained reports; retrying does not increase
that cap. Explicit diagnostic storage operations use the existing canonical
grant without refilling an execution operation.

`io::write_invariant_report` remains an explicit caller-owned export. Its version1
JSON format, work counts, issue order and partial prefixes are unchanged. Its
encoded-byte budget constrains the output string, not all caller scalar-export
temporaries. Canonical state and snapshot DTOs remain explicit caller exports;
the invariant checks no longer use those ordinary owning graphs internally.

See [verification](verification/s05-invariant-diagnostics-native-2026-11-09.md)
for actual allocation faults, query caps and independent predecessor comparisons.
This scoped migration does not by itself verify the entire S05 card.
