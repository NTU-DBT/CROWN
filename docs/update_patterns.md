# Update patterns: declarations, enforcement and conditional planning

X01 is verified within the [qualified support-action profile](verification/update-pattern-profile-v54-2026-11-15.md).
V50 supplies physical-row lifetime FIFO, V51 source-bound declarations/conditional
selection, and V52 Session enforcement, committed-prefix diagnostics and
checkpoint/journal/reoptimization continuity. V53 proves source-event transfer
for monotone sources and arbitrary height-one cores, plus a taller subtree
condition. V54 pairs the selected proved case with its exact source/tree and,
when requested through current selection, actual captured Session premises.
A declaration remains a requested assumption. Broader mixed/SQL lifetime
characterization and release acceptance retain their separate scope. The bound
counts successful logical Boolean support actions; CPU and public delay are
separate costs.

## Select the actual ordering contract

```cpp
WindowOptions options;
options.managed_tables = {TableId{0}, TableId{1}};
options.fifo = WindowFifoPolicy::physical_global;
auto session = QuerySession::create_windowed(program, options);
```

The managed tables start empty. Initial rows in unmanaged tables remain outside
this monitor. All comparisons use complete physical rows, including columns
that the query does not output. See [window admission](batches_windows.md).

| Policy | Ordered objects | Scope |
| --- | --- | --- |
| `global` (0) | Live insertion labels | Union of managed tables |
| `per_relation` (1) | Live insertion labels | Each managed table separately |
| `physical_global` (2) | Live distinct full-row lifetimes | Union of managed tables |
| `physical_per_relation` (3) | Live distinct full-row lifetimes | Each managed table separately |
| `unrestricted` (4) | No baseline FIFO restriction | Explicit declaration scopes still apply |

A lifetime starts at reference count zero-to-one and ends at one-to-zero.
Its identity is the first insertion label's count ID, which survives removal of
that original label. A later reinserted row gets a new, larger birth ID. The
existing ordered count map already represents this order; no second row store,
persistent lifetime index or per-update profile allocation is added.

For labels `1:A, 2:B, 3:A`, removing label 1 retains physical row A. Removing
label 2 next is legal label FIFO, but removes B while A's older lifetime is live.
The physical policies reject that final B removal within the relevant scope.
They allow removing label 3 first while A has another reference: that operation
has no physical erase. Per-table ordering allows independent tables to progress
separately; it does not establish a jointly FIFO trace for two tables.

## Validate before publication

Explicit final-reference withdrawal checks the oldest live count globally or
within the target table. Metadata-only removal needs no physical front check.
Publication still uses the original prepared token after native commitment.

Watermarks visit `(deadline,label)` order. Their entire proposed expiration
sequence is checked before its first effect. With width 10 and insertion
timestamps 0,1,2 for `1:A,2:B,3:A`, watermark 11 would first remove A's label 1,
then physically erase B while A remains. The command rejects before either
effect. It does not skip an expiration or reorder the command to make it pass.

The simulation copies integer lifetime counters into one original-account
scratch vector, ordered by `(scope,birth ID)`. Global count order is already
sorted; per-table mode sorts it. Each proposed label removal decrements its
counter. A final decrement is allowed only at the group's first entry or after
an already-zero predecessor. Initially there are no zeros, and this rule keeps
zeros a prefix of each group. It therefore accepts exactly the oldest live
lifetime removal. Live counts, rows and indexes remain untouched during this
check. The vector is destroyed before the prepared command is published.

The existing rejection path reports `window_fifo_violation` on the first failed
session begin. Later begins report the existing sticky `input_failed` status.
The committed epoch, labels, source acknowledgement, results and watermark stay
at their previous boundary. Resource denial/allocation failure retains its
existing retry behavior. Once a valid multi-step watermark starts, previous
committed steps remain visible if later native preparation needs a retry.
No new catch, retry or rollback layer is introduced.

## Actual costs and persistence

Let D be live distinct full rows and E be expiring labels. Physical watermark
preflight uses O(D) integer scratch in one allocation, O(D) initialization,
O(E log D) counter lookup and existing label lookups; per-table mode adds
O(D log D) sorting. Build/comparison/step work is charged before any effect.
Allocator framing and actual capacity consume the original query account.
`max_accounted_bytes` bounds retained window/component storage; transient
scratch additionally consumes the query cap. Active expiration IDs and later
native row preparation have their existing separate costs and limits.

An explicit global final removal uses the first count; per-table final removal
may scan D count entries, with charged visits. Existing row insertion still
scans distinct full rows and compares scalar bytes. These monitors do not give
the complete session a constant-time update bound. Label modes allocate no new
lifetime simulation; a watermark without expirations does not build it.

The existing policy byte keeps values 0/1 and their interpretation. Values 2/3
extend the admitted range without changing field positions or enum storage.
Older readers reject the new values. Checkpoint restore preserves original
birth/count IDs, including IDs whose original labels have disappeared. Run
context and human EXPLAIN use the exact policy names; the v2 report schema admits
the new names. Stored options identify the managed scope; they do not prove an
unmonitored trace before initialization.

## Paper and planner boundary

P4 is Hu and Wang, *Towards Update-Dependent Analysis of Query Maintenance*,
PACMMOD 3(2), article 117, 2025. The [author PDF](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf)
was inspected at SHA-256
`ef37776d0496a5562c7f3e20342d4eeccba90e53ab84117447b11238b372c538`.
Its set-CQ/self-join/update-lifetime/RAM premises, charged initialization and
amortized maintenance results require separate implementation transfer.

Physical FIFO can be lost under non-injective occurrence projection:
`+(a,u1), +(b,u2), +(a,u3), -(a,u1), -(b,u2), -(a,u3)` is full-row FIFO, while
projection to the first column emits `+a,+b,-b,-a`. Alias fanout also needs its
own argument. A C01 sample with no observed deletion is not an insertion-only
declaration or an exact lifetime monitor.

The [Refactor §5.3 audit](../Refactor.md) also obstructs the literal P4 Lemma 3.7
Trim reconstruction. Successful Trim/MixDetect reduction cannot supply a height
or pattern-bound certificate. Actual trees require the independent verifier
and height evidence. The source/proof packet
`build/verification/v50-pattern-proof-audit-v1` retains exact author sources,
counterexamples, the prefix proof, conservative height-two sufficient conditions
and the remaining mixed-pattern obligations. This window component enables no
new paper-derived maintenance, delay or optimality guarantee.

## Declare a requested source contract

[`patterns::Declaration`](../include/crown/ir/update_pattern.hpp) is a small
immutable value below ranking and runtime. `capture(account, program, rules)`
binds rules to the actual `CompiledProgram` source SHA-256 and source table count.
`import` validates the shape of an ordinary `Record`; `matches(program)` still
has to succeed before that imported request can be used. Neither operation
replays history, establishes a monitor origin or creates proof authority.

A `TableRule` names one source table. `insertion_only=true` means no effective
physical full-row lifetime ends after an enforcement origin. An absent-row erase
or removal of one of several window labels does not end such a lifetime. The
Session policies below state their origin and any stronger command restriction.
This metadata API itself supplies no
such admission policy or historical compliance claim. Any loading prefix needed
for a paper bound still has to be charged.

`fifo_scope=0` makes no FIFO request. Equal positive IDs explicitly name one
joint FIFO scope over its member tables; distinct IDs are unrelated. One rule per
table means the declarations form disjoint scopes, with no inferred union of
overlapping clauses. IDs are preserved exactly, including `UINT64_MAX`. A table
may be both insertion-only and a scope member. Missing tables have no restriction.
An empty declaration is valid and unconstrained; passing it as a selection
condition still requests a proved sufficient case.

Construction sorts R rules by table ID and rejects duplicate or unknown tables,
invalid lowercase 64-digit source hashes and insufficient logical grants. Work is
O(R log R), retained cells O(R); the sort has its ordinary call-stack cost. There
is no derived group index, scope remapping, group scratch vector or row history.
`find(table)` is O(log R) and allocates nothing. Views and pointers borrow the
handle; temporary-handle view overloads are deleted.

`Limits` cap logical work checkpoints, vector cells and element/control payload
bytes. They do not count CPU instructions or allocator framing. The original
receiving `MemoryAccount` separately funds every actual allocation and enforces
its immutable byte cap. `captured_usage()` reports the successful construction;
`copy_usage()` describes an O(R) copy into a different account. A caller using
two-argument `copy_of` must pre-admit that logical copy; its three-argument
overload admits `copy_usage()` against explicit limits before allocation. The
allocator cap always applies. The span-based `import` accepts funded decoder
scratch directly and uses the same shape/canonicalization admission as `Record`.
An ordinary handle copy shares the original immutable owner.
The public raw `selection::CapturedRequest(account, request)` constructor likewise
requires external logical pre-admission of the declaration copy and copied text;
its stored limits are metadata. The bounded `select()` entry point performs
those admissions under the aggregate grant before invoking that constructor. Failed construction
publishes no declaration and relies on local ownership cleanup, without a new
catch/retry layer.

`export_record()` deliberately allocates an ordinary caller-owned vector outside
the query account. It takes O(R) copy work and may propagate `std::bad_alloc`.
That external DTO is suitable for explicit presentation/serialization; it is not
an implicitly bounded runtime snapshot or a checkpoint monitor token.

## Inspect a conditional candidate analysis

[`planner::patterns::analyse`](../include/crown/planner/update_pattern.hpp)
accepts a genuine `MinimumHeightCandidate`, a native program and a declaration.
It checks the declaration/source digest and compares the complete typed
catalog/query binding using the existing C02 encoder. It retains the exact
candidate and declaration handles in its ordinary `Analysis`, so the checked
CQ/tree, height, source digest and rules remain inspectable after the call.
Those existing owners retain their own allocation/lifetime contracts. Newly
allocated table scratch and edge storage consume the supplied receiving account.
The report is diagnostic data, not an independently importable proof handle.
Direct report construction leaves transfer `not_checked` and allocates no edge
storage. A constant route reports `not_required`; `checked_typed_cq` is assigned
only after the direct typed-CQ transfer gates pass.

The analysis uses the actual admitted source event mapping first. A compiled
occurrence adapter deterministically returns zero or one tuple for a physical
row. The native coordinator increments/decrements that occurrence's support
count and stages membership only at 0→1/1→0. Each physical row event therefore
causes at most one logical event per affected occurrence. Alias prefixes are
staged atomically under one pending owner; they add a fixed-query fanout factor.
Physical no-ops bypass routing. Adapter evaluation, byte operations, constraints,
allocation and output retain separate costs.

Two cases need no physical-to-logical FIFO transfer:

- If every participating actual `PhysicalInput::base` is insertion-only, every
  occurrence support count is nondecreasing. Filtering, projection collisions and
  repeated physical aliases preserve logical insertion-only. Unused physical
  tables remain unrestricted. The report is `insertion_only` with transfer
  `checked_monotone_source`, independently of height.
- At native height at most one, every native is a leaf by P02 Above. Each logical
  membership change propagates at most one key along its generalized ancestors.
  Arbitrary source updates, aliases and projection collisions can use this case.
  The report is `height_one` with transfer `checked_event_mapping`.

These transfer names describe conditional logical events, not historical trace
compliance or injective/FIFO transfer. Public output mapping can have its own
behavior: an EXISTS wrapper may replace its synthetic false row with true even
when every native occurrence event is an insertion.

For other mixed trees, the stronger lifetime gate still requires a direct,
non-nullable, self-join-free typed set CQ with no ignored source columns. The
existing compiler rejects nullable direct CQ columns. Normalized SQL above
height one remains `unknown` unless all participating physical sources satisfy
the earlier insertion-only case. Passing the stronger gate reports
`checked_typed_cq`; it does not itself prove all tree premises.

The accepted-row map is injective under that gate: each source column is a query
variable (possibly repeated) or a fixed constant. Equal variable images determine
every source column of an accepted row. Repeated variables impose equality;
constants fix positions. Rejected rows have no occurrence presence. Restriction
of a joint FIFO trace to those accepted rows preserves relative lifetime order.
Ignored columns can destroy this argument, as the projection counterexample
shows. The source-event cases above never rename physical FIFO as logical FIFO.

A constant-result route still reports `constant_result` / `not_required`.
For a mixed maintained tree that passed the stronger gate, every native edge
`parent -> child` must satisfy one of these premises:

1. **The entire child subtree is insertion-only.** Every native descendant,
   including the child itself, needs the declaration. Native survivor relations
   and their key projections then only grow, by bottom-up induction. Each child
   key can appear at most once during any fixed parent tuple lifetime.
2. **The child is a native leaf jointly FIFO with its parent.** Their rules need
   the same positive raw scope ID. Old matching child rows can only disappear;
   new matching rows must survive until the older parent lifetime ends. The key
   presence bit can change at most twice during that parent lifetime.

At height two, all native children are leaves, so this is the existing
`height_two_edges` case with `child_insertion_only` or `joint_fifo_scope` bases.
Taller accepted trees report `subtree_edges`; a nonleaf monotone child uses
`subtree_insertion_only`. All examined native edges remain in the report,
including unproved edges. One failed premise leaves the overall case `unknown`;
that is not hardness or a proof that no alternative tree is compatible.

Checking only an internal child's insertion-only flag is unsound. Its raw row
can remain present while a mutable descendant repeatedly removes its survivor
support. Even one global FIFO scope over every raw input fails to prevent this.
The seven-atom minimum-height-three fixture admits `3n+2m+3` full source updates
(including loading) with exactly `2mn` survivor transitions at its amplified
parent. This refutes naive edge/pair tests for that maintained tree, not every
possible query plan. The [V53 verification](verification/update-pattern-transfer-v53-2026-11-14.md)
records the independent proof/counterexample and actual native controls.

The new argument bounds actual child-bit changes and reverse-index visits,
then generalized propagation, for a fixed verified tree and charged input
lifetimes. It does not assume P4's unfiltered enclosureness is constant. The
original P02/P07 tree/height evidence remains the structural authority; neither
Trim nor MixDetect supplies a replacement certificate. An optional broader
parent-conditioned component theorem in the proof packet remains unimplemented.

For Q atoms, C column/term positions, R rules and T tree nodes, the worst higher
mixed analysis adds O(C + Q log Q + Q log(R+1) + T) charged visitor work beyond
full source binding, and O(Q+T) scratch/edge cells. All-source insertion lookup
stops at its first missing premise. Taller analysis uses one NodeId order vector
and one byte flag vector: parent-before-child traversal followed in reverse,
without recursion or a visited set because the candidate is already checked.
Their logical payload is `(sizeof(NodeId)+1)*T` plus allocator/capacity costs.
The order vector dies before the edge analysis begins; only the original
candidate/declaration handles and edge report are retained. Height at most two
allocates no subtree vectors, and leaf parents need no rule lookup.

Rule, sort and traversal visits debit the operation grant; vector cells and
payload are admitted before allocation. Publication follows all checks.
Source binding, scalar bytes, encoder/allocator work and last-owner teardown
retain their own costs. This explicit planning analysis never runs per input
update. The existing public `noexcept` attempt boundary translates failures once;
private helpers add no catch layer and failed calls return no partial report.

## Use the condition in pure selection

Set `selection::Request::update_patterns` to request conditional admissibility.
The current path requires `PhysicalBasis` with an actual `CompiledProgram`;
`DirectCQ` and ordinary `PhysicalPlan` inputs return `unsupported_model` for this
opt-in request. This is an API admission boundary, not a query impossibility.

Selection checks its full snapshot/source binding and declaration once, copies
the rules into the receiving selection account under the aggregate grant, then
analyses each retained candidate. The private visitor reuses the checked binding;
it does not serialize the full source again per candidate. Result
`pattern_analyses()` has one item per retained candidate in the same order.
`CandidateDecision::eligibility=pattern_unproved` excludes an otherwise slot
eligible candidate. A slot-cap failure takes precedence in that enum; the
separate analysis still records the pattern result. No eligible candidate yields
`constraint_unsatisfied`, without a partial result or cache publication.

After optional slot assessment, no eligible candidate returns before primary
ranking. When a candidate remains eligible, required C02 assessments cover the
full retained family, including excluded candidates. Selection chooses only among
eligible candidates at the original certified minimum height. It neither manufactures a filtered proof family nor calls an
unproved case impossible. The compiled source remains unchanged. Artifact keys
include a versioned pattern domain, complete source digest/table count and every
canonical table/insertion/scope field. Distinct raw scope IDs cannot alias even
if they happen to yield equal compatibility. Requests without a declaration
retain their previous request-byte encoding and skip all new analysis/copy work.
The empty optional/vector fields do add fixed result/request storage; there is
no new per-update scan, index, row mirror, catch or monitor allocation.

The native `update_pattern` and `selection_pattern` tests exercise real P02/P07
handles, source/candidate refusal, joint versus per-table premises, actual winner
change, exact cache binding, grant refusal and allocation cleanup. The [V51 verification record](verification/update-pattern-contracts-v51-2026-11-14.md)
states the tested sources and limits. Runtime enforcement is the separate V52
boundary described below; conditional selection alone still establishes no
observed history or engine complexity bound.

## Enforce a declaration through QuerySession

```cpp
const std::array rules{
    patterns::TableRule{TableId{0}, false, 7},
    patterns::TableRule{TableId{1}, false, 7},
    patterns::TableRule{TableId{2}, true, 0}};
SessionOptions settings;
settings.update_patterns = UpdatePatternOptions{
    patterns::Declaration::capture(program.account(), program, rules), {}};
WindowOptions windows;
windows.managed_tables = {TableId{0}, TableId{1}, TableId{2}};
windows.fifo = WindowFifoPolicy::unrestricted;
auto session = QuerySession::create_windowed(program, windows, {}, settings);
```

Admission checks the actual program source, the finite metadata grant and the
original query account. Every table with a positive FIFO scope must be managed
by the window, whose managed base tables start empty. A nonwindow Session
refuses FIFO rules: it has no equivalent lifetime history. No declaration can
be attached retroactively to a live Session. Initial native loading retains its
existing charged construction; unmanaged initial rows remain outside window
lifetime monitoring. That initialization is not a free prefix in a paper bound.

The implemented policy always rejects a violating command. An owned stream or
typed physical Session rejects every erase command on an insertion-only table,
including an absent-row no-op. A window Session rejects only a proposed final
reference removal for that table; duplicate-label withdrawals and expirations
remain legal while the physical row survives. Equal positive scope IDs order
full physical lifetimes jointly across those tables. Different IDs never imply
a union. The baseline physical-global policy is stronger than each scoped FIFO
restriction; physical-per-relation plus explicit scopes enforces both.

Guards run before journaling the command or preparing native row changes.
Whole-watermark simulation checks insertion-only and FIFO conditions before
any expiration effect, including effects on unrelated tables. It reuses the
existing ordered counts and one integer scratch vector; it stores no row mirror.
After a valid command begins, active removals reuse the prepaid preflight and
the existing per-step publication protocol. A later resource failure can be
retried without rolling back previously committed substeps.

A completed semantic error is `update_pattern_violation`, followed by sticky
`input_failed`. A fixed violation names the kind, table, command and label,
without retaining row values. Resource refusal, including failure to allocate
the error object itself, leaves the committed prefix unchanged and retryable.
The existing Session catch/abort boundary handles both paths; no additional
catch, rollback or fallback layer was added.

## Read the committed prefix and bind current selection

`session.update_pattern_status()` and `SessionStatus::update_patterns` expose
the declaration, the actual current physical program hash, physical/command
origins, committed physical sequence, completed command sequence, insertion
policy and first violation. Metadata-only commands advance command progress
without advancing the physical sequence. Private preparation never appears as
a completed command. Fresh Session origins are zero, with managed tables empty;
the initial native loading context remains separate and charged.

Run-context JSON records the immutable requested rules. Session-status JSON
records `enforced_prefix` or `rejected`, with `maintenance_bound=not_asserted`.
The optional fields are omitted for undeclared Sessions. These diagnostics are
ordinary data, not structural certificates or independently observed history.

Runtime `select_current`/`select_for_reoptimization` accepts a pattern request
only from a real QuerySession capture with an available, unrejected monitor,
matching committed physical sequence, source hash/table count and exact
canonical rules. Bare PhysicalRuntime and DeltaRuntime opt-in calls refuse
`unsupported_model`. Existing owner, mode, pending and source checks still apply.
A measured reoptimization choice revalidates the real Session before starting.
Replacement retains the same source-bound declaration and monitor state while
the reported physical hash changes to the installed tree. Structural minimum
height authority remains P02/P07; the V51 sufficient-case analysis stays conditional.

## Support-action guarantee profile

`planner::selection::Selection::pattern_guarantee()` returns an optional
`planner::selection::PatternGuarantee`. A present profile reports the positive
bound `O_Q(I + U)` for the selected plan's successful logical Boolean native support
process. Q denotes the fixed compiled query and tree, including occurrence
fanout. I counts physical source rows at a charged initialization; U counts
physical source events, including no-ops. Initialization, reconstruction and
plan replacement must each account for their own starting state. The profile
does not estimate I, U or an elapsed duration from a sequence counter.

The counted actions are native input/child-key probes, matching reverse-index
visits and child-bit changes, survivor events and generalized upward
propagation. The [source-event and subtree argument](#inspect-a-conditional-candidate-analysis)
explains the physical-to-occurrence transfer. Its subtree proof bounds every
matching reverse visit, including changes that leave a parent's conjunction
unchanged. It does not count only successful survivor transitions.
The exact proof/counterexample scope is retained in the
[V53 record](verification/update-pattern-transfer-v53-2026-11-14.md).

This is an amortized abstract support-action bound. Storage lookups, scans and
comparisons, variable-width scalar work, source adaptation, allocation,
monitoring, journaling, rollback/retry, output work and total CPU/delay remain
separate costs. Native reference buckets use their maintained index; this bound
does not make storage operations or source-constraint validation constant time.
One event can still cause many support actions. Failed or retried
attempts do not become free because they leave the committed sequence unchanged.

The pure profile's `analysis()` returns the selected candidate's exact retained
case, source transfer, declaration and edge bases. Its `plan()` returns the
selected compiled physical program. The candidate keeps its original P02/P07
tree/height authority. `bound`, `units`, `input_accounting`, `excluded_costs` and
`proof_reference` state the claim's model. The enum `name()` helpers provide
readable case, transfer and edge-basis labels. No profile is produced for an
absent pattern request or an unproved selected case. Unsupported cases still
remain unknown and cannot silently acquire the positive bound.

A contradictory nonempty body retains its genuine original candidate and
checked structural height. Its executable plan uses the canonical empty tree
and `constant_false` route. The profile preserves both descriptions; a constant
operator does not replace or lower the original candidate's height proof. The
`constant_result` case has no native support-tree work.

For actual Session premises, use
`runtime::selection::CurrentSelection::pattern_guarantee()`. For example, with
an admitted family, compiled program, active Session and source-bound request:

```cpp
namespace ps = crown::planner::selection;
namespace pp = crown::planner::patterns;
namespace rs = crown::runtime::selection;
auto choice = rs::select_current(family, ps::PhysicalBasis{program}, *session, request);
if (choice.selection) {
  auto profile = choice.selection->pattern_guarantee();
  if (profile) {
    auto selected = profile->selected();
    std::cout << ps::PatternGuarantee::bound
              << " case=" << pp::name(selected.analysis().sufficient)
              << " owner=" << profile->stamp().owner.value
              << " through=" << profile->enforcement().monitored_sequence
              << " selected_plan_matches_capture="
              << profile->selected_plan_matches_capture() << '\n';
  }
}
```

The runtime profile retains these distinct facts:

| Accessor | Meaning |
| --- | --- |
| `selected()` | The selected plan's conditional positive profile and exact source/tree premises |
| `enforcement()` | The captured Session declaration, physical/command origins and through-counters, insertion policy, history and actual physical-program hash |
| `stamp()` | The captured physical owner's identity, committed physical sequence and layer |
| `selected_plan_matches_capture()` | Equality of the selected and observed complete physical-program hashes at capture |

The selected plan can differ from the installed plan. A false match flag leaves
a useful qualified claim for the selected plan under the captured source
premises; it does not attribute that plan's bound to the observed executor.
A true flag identifies the same physical program at that boundary. It does not
prove that the entire earlier prefix used that program, and it does not promise
future freshness. Reoptimization requires a charged initialization/rebuild of
its target; this profile makes no retrospective work claim across earlier plan
segments. Recapture after owner progress, restore or replacement when a new
boundary is needed.

Runtime publication requires both a proved selected case and the actual,
unrejected Session premises already checked by current selection. The ordinary
Session status can continue to say `maintenance_bound=not_asserted`: that status
alone lacks a selected proof case. The qualified profile adds that separate
case rather than turning the Session diagnostic into a whole-engine bound.
Metadata-only commands retain their separate command progress; `stamp()` uses
physical progress. Restored `enforcement().history` still assumes a trusted
checkpoint and does not authenticate or reconstruct historical enforcement.

Both profile handles share existing immutable selection/capture owners. Reading
the profile adds fixed reference-count work and no allocation, row copy, index
or per-update analysis. Accessors borrow retained data while the profile lives.
Physical-hash comparison visits the fixed 64-byte digest. Holding a profile can
keep its already funded plan, analysis and capture alive; releasing a final owner
or overwriting it can destroy that larger retained state. Explicit export or
printing has its own work and output storage. Profiles are reports, not new
proof/import capabilities.

## Restore the declared contract

Undeclared Session checkpoints keep state version 1 and its exact wire layout.
Declared checkpoints use state version 2. After the optional window and before
the runtime image length, the extension stores the source hash/table count,
sorted rules, physical/command origins and optional fixed violation. Its size
is `97 + 17*R + (violation ? 25 : 0)` bytes, without row history. Existing FIFO
values 0–3 keep their meaning; value 4 appends unrestricted behavior.

Inspection validates structure and caps without allocating. Decoding funds rule
scratch and retained declaration data from the receiving query account, with
separate finite parse/import grants. Native restore additionally checks actual
program source, window admission, origins and violation context, then copies the
declaration under receiving limits. File/log restore and durable plan replacement
use this same versioned checkpoint. A logged undecided input is retried through
the ordinary guard after recovery.

Restored status explicitly says `trusted_restored_checkpoint`. Public mutable
checkpoint metadata can be authored by its caller; shape checks and checksums
do not authenticate past enforcement. Recovery and subsequent current selection
assume the existing trusted local-checkpoint boundary. They do not reconstruct
historical compliance from a declaration or checksum. The monitor enforces all
new admitted commands after restore.

## Account for opt-in costs

Let R be declared tables, D live distinct full-row lifetimes and E proposed
expiring labels. The following additions are separate from existing native
maintenance, row copies, label/index lookup, scalar byte comparison, allocator
framing, initialization, output and recovery costs. Empty/singleton lookups
retain their fixed cost; logarithmic counts below include that constant term.

| Operation | Additional work/storage |
| --- | --- |
| Admission/receiving copy | O(R) work and retained rule cells after source binding; actual allocation uses the query cap |
| Plain insertion-only erase check | O(log R) borrowed table lookup; no row copy or extra retained index |
| Scoped explicit final withdrawal | Up to O(D log R) visits through existing birth-ordered counts; no scratch vector |
| Declared watermark with expirations | One O(D) integer vector, O(D log R) rule binding, O(D log D) sort only for physical-per-relation or live positive scopes outside physical-global, and O(E(log R + log D)) counter work |
| Current selection binding | O(R) canonical rule comparison under the existing aggregate work grant |
| Status copy | Fixed inline metadata plus an immutable declaration handle; no per-status rule-vector allocation |

Under the current 64-bit layout, the declared watermark counter has 32 bytes
per live lifetime before allocator/capacity costs; this is not an ABI promise.
An insertion-only watermark without baseline ordering or live FIFO scopes keeps
the existing birth order and skips sorting.
Combining legacy label policies retains their existing cursor-map/traversal
costs. A watermark without expirations creates no new counter vector. Undeclared
Sessions retain their original scans and allocations, plus fixed optional-field
checks/storage. These costs establish no constant CPU update bound.

See the [V52 verification record](verification/update-pattern-runtime-v52-2026-11-14.md)
for the monitor/continuity controls and the [V54 record](verification/update-pattern-profile-v54-2026-11-15.md)
for the accepted qualified profile and current validation.
