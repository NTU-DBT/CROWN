# C05 exact logical charges and timing

This is the implementation's component accounting contract. It does not count
allocator live bytes, capacities, peak bytes, elapsed arrival rates, or measured
update costs. A tuple/index slot is unitless. `AllocatorByteLimit` is rejected;
no numeric slot/byte comparison is performed.

The implementation uses the existing C02 `ranking::Limits` and `Usage` domains.
The eight additive dimensions are work, cells, binding-key bytes, modeled
payload bytes, lower work, identity work, binding-replay work, and normalization
work. All additions check the remaining allowance before mutation. Candidate
count and score-bit width are independent finite admissions. Zero score bits,
more than 512 score bits, and negative optional time are invalid requests.

## Exact charge primitives

The following table specifies operations, not CPU instructions. `n` means the
exact number of visited elements or bytes; `sizeof(T)` uses the actual compiled
ABI. The pinned compiler/variant therefore forms part of a reproduced charge.
Charges are cumulative logical admission: scratch/key payload is not refunded
when a temporary dies. Repeated conservative allowances are intentional.

| Operation | Work | Cells | Key traffic | Modeled payload |
| --- | ---: | ---: | ---: | ---: |
| C05 `work(n)` | n | 0 | 0 | 0 |
| C05 `vector<T>(n)` | 0 | n | 0 | n × sizeof(T) |
| Fixed payload walker object T | 1 | 0 | 0 | sizeof(T) |
| Payload walker sequence of T | n | n | 0 | n × sizeof(T) |
| Payload walker string | byte length | 0 | 0 | byte length |
| Payload walker set of variable IDs | cardinality | cardinality | 0 | cardinality × sizeof(VariableId) |
| Scalar payload visit | 1 | 0 | 0 | string bytes as above; Decimal adds 38 work and 38 bytes |
| Encoded byte append, including domain/tag/length | 1 | 0 | 1 | 1 |
| Encoded raw string body | byte length | 0 | byte length | byte length |
| Decimal binding formatter | 41 | 0 | 0 | 41, before calling the public formatter; encoded canonical bytes are additional |
| Full byte equality | 1 plus 2 per examined byte pair | 0 | 2 per examined pair | 0 |
| Structural-key order | 1 plus 2 per examined byte pair | 0 | 2 per examined pair | 0 |
| Decimal score comparison | 1; if equal length, 2 per examined digit pair | 0 | same examined digit-pair charge | 0 |
| Slot-cap validation | 1 per cap digit; for a 155-digit cap, 2 per examined maximum-bound pair | 0 | same | 0 |
| Retained candidate eligibility visit | 1 per candidate | 0 | comparisons above | 0 |
| Retained winner visit | 1 per candidate, including excluded candidates | 0 | comparisons above | 0 |
| Cache lookup entry | 1 plus full equality charges | 0 | comparisons above | 0 |
| Prepared cache Entry | 0 | 1 | key length for copy | sizeof(Entry) plus key length |
| Planned FIFO eviction | 1 per entry | 0 | 0 | 0 |
| Actual-owner boundary check | 13, plus 12 for QuerySession | 0 | 0 | 0 |
| Late CurrentSelection backing record | 1 | 0 | 0 | sizeof(runtime selection Data) |

All encoding appends charge before string growth. The nested Catalog/Query
record delegates to the unchanged bounded P07 v2 encoder through C02's helper.
That helper admits both remaining key and remaining payload allowances before
allocating; its exact returned Usage is carried, then copying its bytes into
the outer tagged record is charged again. P07's native unbudgeted bytes and
prefix allocation shape are not changed by this overlay.

The Catalog walker covers table/column names, ordered constraints and their
column vectors, statistics vectors, key-hint vectors and strings. The Query
walker covers variables, atoms/terms, scalar strings/Decimals and ordered head
aliases. The raw-tree walker covers nodes, IDs, scopes, children, claimed
separators and optional claimed connex vectors. Fixed scalar/enum/optional
members are in their containing object's logical storage.

Selection's own backing object is charged once as `sizeof(SelectionData)`.
The copied DirectCQ policy strings and optional slot-cap string are admitted
before that copy. The fixed number of assessment handles and the entire
retained-set decision vector are reserved only after exact vector admission.
CandidateSnapshot, checked candidate, proof, pre-existing PhysicalBasis and
Evidence handles share immutable backing; sharing does not repeat their
already prepared component construction charge.

## Lowered and cached plan components

Before a first DirectCQ lower, the known Catalog, Query, exact candidate tree,
PhysicalOptions and their owned strings/vectors are pre-admitted. There is no
invented identity DOM to inspect. The new identity and compiled public payload
are traversed and charged after finite native lower succeeds, before result or
cache retention. The options pre-admission is conservative in addition to the
compiled walker describing those same public options. A real PhysicalBasis
uses C02's existing source/identity walker before lowering.

The identity DOM visitor is iterative. It charges its vector control object,
one pointer item for the root and each queued child, a JSON cell and
`sizeof(Json)` for every node, an additional pointer allowance per structured
node, string values, and object-key string controls/bytes. Identity hashes and
occurrence/variable order vectors are also included. Pointer capacity and map
node allocator overhead are excluded.

Compiled public payload uses the unchanged C02 walker. This includes options,
guarantee strings/vectors, validation vectors, physical digest, layouts,
relations, inputs/constants, routes, node/edge projections and enumeration
descriptors. It includes the conservative private Decimal coefficient allowance
and up to one repeated-field equality pair per layout field. It can count
shared projection/layout components more than once; it does not deduplicate
by allocation address.

A read-write cache miss separately traverses the complete chosen plan's source
and compiled public components. The resulting delta of modeled payload is the
entry's cache-retention charge and also consumes this selection's aggregate
payload. This intentionally charges an already shared plan again for admission
to the independent cache-retention domain. The key copy and Entry are additional
selection charges; independent cache caps retain exact key lengths and plan
component charges, not allocator bytes. A hit retains the existing whole
PhysicalPlan and does not pretend that a new plan was allocated.

Native P08 lower, normalization, replay and identity construction can allocate
private temporaries before their final public size can be inspected. Finite
native work caps apply, but this logical payload cap is not a bound on that
temporary allocation peak. C01 raw owner snapshots remain bounded by their own
admitted options/max_cells and state-capture limits; their retained storage is
not relabeled as C05 payload. Existing proof/provider storage, reference-count
control blocks, allocator headers, set/list/map node overhead, spare capacity,
native private maps, call-stack/control records and destruction scratch are
explicit exclusions. No S05 claim follows.

## Delegated budget equation

Let P be the same Evidence's preparation Usage, L the caller ceilings, and U
the current selection total. An as-of call starts with U=P; a current call
starts at zero and adds its fresh capture once. A complete assessment receives
`D = P + (L - U)` for each additive dimension. Its returned Usage V contributes
`V - P`, never V again. Because `P <= U <= L`, this construction cannot overflow
even at UINT64_MAX. A dual assessment performs complete Q first, then complete
depth using the remaining total; both retain their exact delegated Requests,
Usages and per-candidate reproduction terms.

Borrowed C02 binding/payload visitors receive the existing Usage and remaining
caps, with their internal timer disabled. Their returned counters replace that
same Usage, including on exception, while the outer interval measures the work.
No fresh component grant is silently substituted.

Native blocking lower/identity/replay/normalization calls reserve all remaining
relevant native work before entering. Success replaces the reservation with
reported actual work; an exception retains the conservative reservation because
those APIs expose no partial work counter. Producer work limits remain
additional bounds. The normalized basis's finite expression/recursion limits
are copied, not replaced by unlimited values.

## Optional active time

Without `active_time`, this overlay takes no new clock readings. Untimed
preparation remains explicitly `PreparationTiming::unmeasured`; its absent
elapsed measurement is not claimed as measured zero. No-evidence pure calls
report `absent`. Actual timed capture reports `measured`.

With a time ceiling, C05 partitions the synchronous call into nonoverlapping
outer and delegated phases. It samples the outer interval before delegation,
passes the derived remaining duration, then measures the entire delegated
wall phase once. It does not also add the component's overlapping timer delta.
The complete component Usage still retains that delta for inspection. The
aggregate therefore includes any wrapper overhead outside the component's own
sampled interval, instead of dropping it or counting the interval twice.
Historical P is carried exactly once and idle time between calls is excluded.

A timed as-of call made from untimed Evidence reports unmeasured historical
preparation explicitly: the ceiling covers measured current work plus whatever
preparation timing was actually recorded. It cannot retrospectively include an
unknown prior duration. A zero or already consumed deadline stops before new
work. The final deadline check precedes publication. This is cooperative, not
preemptive; a native call or cleanup can cross the deadline before the next
check. After the no-throw commit, destruction cannot revoke a published result.

## Atomic publication

All statistics, entry insertion and eviction counts are local to Prepared until
the complete result and any CurrentSelection wrapper exist. `commit()` performs
only list splices and scalar assignments. Evicted nodes are moved to a private
retired list; dropping a last plan reference and JSON cleanup happens after
publication, so the commit itself does not allocate a cleanup stack. The active
native JSON header already supplies the independently accepted persistent-OOM
cleanup fallback. C05 does not patch or mix that header.

Failure returns only fixed scalar diagnostics and an empty optional result.
Cache contents/order/counters, owner state, workload snapshots, provider/proof
handles and prior selections remain unchanged. Cache creation, caller request
construction and an explicit cache clear are separate caller operations.
Root must execute exact/one-under and persistent-failure consumers before any
of these authored checks become execution evidence.
