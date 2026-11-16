# C02 operational accounting, version 1

Limits are finite unsigned counters, except the optional nonnegative soft time
ceiling. Defaults are 128 candidates, 1,000,000 C02 work units, 1,000,000 cells,
8 MiB binding/key bytes, 16 MiB logical payload, and 1,000,000 units each of
lowering, identity, binding replay and normalization work. Score bits are
1..512. Zero work/time and insufficient carried usage return resource stops.

Work covers traversal, copied/examined bytes, key comparisons, integer limb
operations and decimal output. Conversion charges 18 units, addition 33,
multiplication 304, comparison 16, and decimal conversion 16 plus 17 per digit
and one per emitted digit. Operations return a new fixed-array value; failures
leave operands and prior results unchanged. Integer arrays and multiplication
scratch are fixed at 16 and 32 uint32 limbs respectively.

`cells` counts admitted vector/set elements and logical DOM nodes, including
charged scratch inventories. `payload_bytes` is cumulative modeled allocation
admission: fixed public object sizes, vector element counts times sizeof,
copied text lengths, exact decimal score digits, and the conservative private
components below. Released temporaries are not refunded. It is intentionally
more conservative than a live retained-byte sum and is build/ABI-specific.
The score and canonical score text do not depend on sizeof or this accounting.

## Candidate-plan payload

Before **each** blocking lower call, `plan_source_payload` admits the candidate's
Catalog, Query and tree and the basis's owned normalized binding/program, when
present. This includes every table/column/name/constraint/hint/statistic vector,
term, variable, ordered/repeated head, tree scope/claim/child list, source SQL
text, alias, expression arguments and literal, parameter, output and adapter
vector. Normalized core catalog/query copies are counted separately from the
PhysicalPlan's direct core copies. A long source string retained by N candidate
plans is charged N times.

It also admits the same-binding semantic identity content before construction:
the four fixed-length hash strings, ID orders and complete canonical DOM. The
DOM model counts Json cells and object key string headers/bytes, not allocator
map-node overhead. Its iterative scratch pointer inventory and the retained
identity-cleanup pointer inventory are charged separately. The native identity
does not depend on tree choice under the checked original binding, actual
normalized program and options; post-lowering hash equality is only an internal
consistency check, never admission/import authority.

After lowering returns, before retaining the plan in a CandidateScore,
`plan_compiled_payload` admits options, guarantees, validation, layouts, layout
fields/context, relations, projections, index uses, inputs/constants/equalities,
base routes, nodes, edges and enumeration. The full source pre-admission precedes
the native call; exact derived structure is only available after it. A failed
post-call admission destroys the local plan and returns no Result. Therefore
the cap bounds admitted modeled publication, not peak temporary construction
inside an indivisible native lower call.

Each Decimal alternative reserves 38 coefficient bytes without calling its
allocating formatter: the domain's canonical coefficient is at most 38 digits.
Each TupleLayout includes its private equality-vector header and a conservative
allowance of one FieldId pair per field; this covers repeated output variables
without an unbounded duplicate scan. Shared projection component payload may
be charged repeatedly by separate published references. Every layout's shared
fields/context payload is charged from the plan's owned layout inventory.

Excluded from this model are shared_ptr control blocks, allocator headers and
container node overhead/capacity slack, internal padding beyond the expressly
counted public types, fixed private plan fields, retained external caller-owned
proof/snapshot/plan payload behind shared handles, native temporary JSON/text/
parser structures, and allocator high-water/peak totals. The exact binding
encoder also uses Decimal's bounded formatting temporary (at most 41 characters
including sign, leading zero and decimal point), outside its admitted output
string. Fixed limb/scratch arrays are separately bounded stack storage. No S05
claim follows.

## Native capture and lowering boundaries

One finite native C01 Limits object covers the complete source request.
`CaptureAccounting` preserves all six native limits, actual work/row/key/byte
usage, state status, component counts, and workload descriptor/cell counts.
`SourceObservation` preserves per-component availability and optional returned
cardinality. A native source-budget stop is evidence unavailability, distinct
from exhausted C02 processing. Its explicit height fallback does not invent
source facts or reuse previous detail.

Workload snapshot creation copies native configured slabs before C02 can inspect
them. That admitted allocation is governed by the actual owner's collector
configuration (`max_cells`, stored descriptors/current/previous slabs), not the
later C02 payload cap. C01 `Memory` remains its own modeled component measure.
The runtime evidence retains the actual joint capture/session context so this
cost is not mislabeled as a ranker-owned byte total.

Each candidate gets only the remaining aggregate native work/identity and,
when normalized, replay/normalization allowances. Those four work allowances
are finite uint64 values even if the owner's producer options were unlimited.
The finite size_t expression/recursion limits of the actual owned binding are
copied; no optional unlimited work value is imported. On success the native
work counters are added. On native failure those APIs expose no partial work
count, so the complete remaining allowances are conservatively retained as
charged reservations. They are not falsely reported as measured CPU work.

All C02 resource failures are transactional. `rank` retains no partial winner;
`capture` retains no partial Evidence after a C02 processing/allocation failure.
Native C01 can publish an explicitly partial/unavailable bounded capture, whose
statuses are retained as evidence. Existing native resource diagnostics can
collapse a replay's allocation failure into a native resource diagnostic; C02
preserves `lowering_limit` for a native `resource_limit` and never treats it as
statistical unavailability.

## Time

Timing uses steady_clock only when requested. `Usage.active_nanoseconds`
contains previously measured preparation plus current measured active work,
excluding idle time between separate calls. The final publication check runs
after capture/result preparation. It is a soft ceiling checked between charged
processing batches and around full binding encodes/native calls; it cannot
preempt a parser, allocator, encoder or lowerer. A byte/limb batch is admitted as
one charged operation rather than reading a clock for every character.
Elapsed-time diagnostic addition may cap at UINT64_MAX solely to reject a
time ceiling; score arithmetic never caps. A cap at or below already carried
time stops before further ranking and retains that usage. With no ceiling,
no new timing is collected. Pure as-of replay may use a different finite budget
without changing the score inputs; its original capture limits stay recorded.
