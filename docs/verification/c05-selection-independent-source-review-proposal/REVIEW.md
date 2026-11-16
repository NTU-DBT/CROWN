# Review of the held C05 source

No concrete implementation blocker was found in the nine reviewed C05
implementation/header files. This conclusion is limited to those held bytes,
their current native dependencies, and the contracts below. It does not accept
the card, certify every possible input, or close pending sanitizer/native gates.
The implementation inventory and exact hashes are in
[REVIEWED_SOURCE_SHA256SUMS](REVIEWED_SOURCE_SHA256SUMS).

## Authority, full-source binding and artifact admission

The public Selection and CurrentSelection handles expose const accessors and
private constructors. Their complete factories and mutable backing records are
in implementation/private source files. Public request/source declarations and
private byte-only diagnostic helpers cannot construct a checked proof, admitted
snapshot, observed Evidence, Selection, or cache entry. Selection retains the
current call's checked candidate and snapshot; reuse does not transfer a prior
call's proof or evidence into the result.

`selection_binding.cpp` compares complete framed source bytes before assessment
or cache lookup. A PhysicalBasis must match the original proof's Catalog/Query;
the explicit source must also match any supplied Evidence's actual plan source.
The PhysicalSource record contains the full core binding, original physical
catalog, optional owned normalized program, and all PhysicalOptions. It does
not require the evidence owner's old tree to be the newly selected tree. After
lowering or a cache hit, a separate compiled-input comparison requires the same
full source and the exact selected raw tree.

The current field inventory was checked against the native Catalog/Query,
BoundSql, NormalizedSql, PhysicalOptions, CandidateContext and Evidence
declarations. It includes ordered/repeated/empty sequences, optional presence,
all five native Value types, binary string bytes, canonical Decimal, Date,
bound expression alternatives, source locations, original SQL text, adapters,
physical routes, typed outputs, producer limits and recorded work. Nullable SQL
values remain optional SQL-boundary records, not an invented native scalar.
The nested core uses the existing bounded P07 v2 encoder; the outer encoder
charges its returned bytes again before copying them.

Native `lower_normalized` performs complete binding/normalization replay under
host limits. The replay restores stored producer limits and compares the full
serialized result with the input. Thus the C05 comparison does not depend on
silently replacing source work/limit metadata with the temporary host budget.
A new public field or format needs a corresponding binding/version review;
the current inventory does not promise compatibility with unreviewed extensions.

Artifact keys contain the complete original binding, required checked height,
context, family/exhaustion, every ordered retained member's key/height/raw tree,
explicit source/options, request/limits, effective decision/eligibility, origin,
and immutable evidence facts/configuration. Full byte equality is used, without
digest authority. Permuted raw trees can therefore remain distinct even when
their structural keys are equal. Owner/generation fields cannot alone authorize
a hit: the call has already made its own complete assessment and, for a current
call, obtained its own capture.

The deliberate exclusions are coherent with caching only a whole PhysicalPlan:
proof certificate/provenance, preparation Usage, elapsed measurements, actual
state-consumption counters, attempt/abort/unread details, cache-use mode,
retention capacities and addresses. Excluded metadata remains in the new
result/capture where applicable. The key is an artifact-reuse condition, not
freshness, proof, import, deployment or global optimizer authority.

## Whole-family choice, constraints and unsupported requests

Admission requires real snapshot/proof handles, a nonempty finite retained
family, supported enum values, and exhaustion when requested. C02 independently
checks every candidate's binding, required height, context and key uniqueness.
A retained prefix remains explicitly a prefix; neither success nor a failed
slot constraint proves a claim about unseen candidates.

Mandatory slot constraints obtain a complete Q assessment with
`require_evidence`, then mark every retained candidate eligible or ineligible.
Depth, when requested, is a second complete assessment of the same family.
C05 selects among the eligible candidates using the effective policy and
unsigned structural-key ties. It preserves the full C02 assessment, whose
unconstrained winner can differ from C05's constrained choice. An all-ineligible
family returns `constraint_unsatisfied`; it does not publish a partial winner
or a structural infeasibility proof. Height with a slot cap uses Q only for
eligibility, then the structural tie rule, without relabeling Q as height cost.

The default depth request can use only its explicitly configured statistical
fallback. Required evidence and mandatory constraints cannot be bypassed by
that fallback. Processing/bit/time/lowering/allocation failures do not choose a
different policy or try the next candidate. Uncomputed C02 score fields remain
placeholders selected by `effective_policy`, not computed cost facts.

Maintenance-cost and allocator-byte requests, and unsupported layout/index
values, are rejected during C05 admission before owner capture or cache lookup.
An already exhausted admission budget can stop first. Unsupported arithmetic
has a different boundary: native identity construction supports only
`exact-nonnull-v1` and rejects the changed DirectCQ arithmetic namespace during
lowering. C05 reports that failure and leaves the cache unchanged; it does not
promise an earlier arithmetic precheck. The corrected independent fixture now
tests five supported option variants plus this one explicit rejection/retry,
rather than claiming six supported namespaces.

## Current, historical and released owners

Pure selection treats optional Evidence as explicitly historical/as-of. It
does not claim that the evidence is current for an external runtime. The
current overloads always obtain a new bounded owner-driven capture, even for
height-only, and retain the owning RuntimeEvidence with the pure Selection.
No caller supplies a freshness flag or an arbitrary paired state/workload.

The bridge compares actual owner freshness at lag zero and checks physical
scope, committed sequence, state/workload/input owner agreement, pending state,
and the Physical-versus-Delta mode distinction. Session additionally reconciles
actual status, metadata, committed sequence, requested/resolved mode and
completion, live/view settings and workload options. Pending and released
boundaries fail before cache publication, including height-only. Source-capture
unavailability remains distinct from owner-boundary failure and from C05
processing exhaustion.

These checks operate under the public requirement that the caller preserve the
owner's exclusive synchronous-access contract for the complete call. C05 does
not acquire a new lock spanning capture through ranking/publication. Under that
contract there is no intervening writer; this review makes no concurrent-owner
guarantee. After return, a current result is an immutable historical record and
does not stay current across later updates, reset, configuration change or drop.

## Preparation-once work, payload and time

For preparation P, caller limits L, and current aggregate U, each complete
assessment receives `P + (L - U)` and contributes `returned - P`. The invariant
`P <= U <= L` makes this safe at the unsigned boundary. Current capture is added
once; a dual Q/depth call carries the same preparation without double charging
it. All eight additive dimensions, candidates, score bits and optional time
remain explicit. Borrowed binding/payload visitors use the current counters and
caps, copy their usage on either return path, and do not receive a fresh grant.

Key bytes, string bodies, vector items and retained records are admitted before
the corresponding copy/append. Multiplication guards precede `n * sizeof(T)`.
Known DirectCQ catalog/query/tree/options copies are admitted before lower;
the independent options copy is included. The new identity and compiled public
payload are charged after finite native lower, before retention. A basis uses
the native C02 source/identity visitor. Cache admission separately charges its
retained whole-plan component model and exact key copy. Shared components can
be conservatively counted more than once.

Native lower/identity/replay/normalization calls reserve remaining work and
refund to reported actual usage only on success. On exception, APIs without
partial counters retain the conservative reservation. Producer expression and
recursion limits remain additional bounds. Logical payload is not allocator
live bytes or peak: private native temporaries, allocation/control/node
overhead, spare capacities, prior proof/provider/capture construction, stack
records and destruction scratch have the documented exclusions. Q remains a
tuple/index slot proxy. There is no S05 or maintenance-cost inference.

Without an active-time limit, C05 takes no new clock readings. Historical
untimed preparation is marked unmeasured, not measured zero. With a limit,
outer and delegated wall intervals do not overlap in the aggregate; the final
check precedes publication. Native calls and cleanup are cooperative, so a
deadline can be crossed before the next check. Post-commit destruction cannot
revoke the published result. Native/component failures can have coarse
resource diagnostics (for example, a C02 byte limit does not identify which
private byte domain); retaining the component stop avoids inventing precision.

## Transactional cache publication and owning lifetimes

Lookup follows fresh whole-family decision. Hits retain the existing entire
PhysicalPlan but do not refresh FIFO order. Read-only misses lower a plan
without inserting; their successful miss statistics are still committed.
Capacity-zero caches are explicitly disabled. Retention caps are independent
from selection budgets; an entry that cannot fit fails rather than silently
disabling the requested cache.

All counters, insertions and FIFO evictions remain private in Prepared until
the result, late CurrentSelection wrapper and final budget check succeed.
`Prepared::commit` uses only list splices and scalar assignments. Evicted nodes
are moved to a private retired list, so a last plan reference and JSON teardown
are released after publication, not inside commit. Return-handle operations
following commit are nonthrowing. The active native JSON cleanup fallback is
an already accepted dependency, not a new C05 patch.

On failure, no cache statistics/order, runtime state, workload counters or old
result are intentionally modified. Cache creation, explicit clear and caller
request construction are separate operations. Selection/CurrentSelection own
immutable backing records; cached and returned plans use owning handles, not
runtime pins. Old results survive cache eviction/clear/move and owner drop.
Moved-from cache handles are rejected when cache use is requested. Thread-safe
shared cache access is not claimed; the cache also requires exclusive access.

## Limits of this review and execution evidence

The reviewer authored the independent literal fixtures before implementation
review and did not author the implementation. The original brace/noinline
compile corrections and unsupported-arithmetic fixture correction are preserved
as separate packages, with the original failures and diagnostic. The original
field checklist's six-option success wording is historical; the corrected
five-supported/one-rejected consumer and its receipt are authoritative for the
current fixture claim. No numerical expectation was changed.

Terminal strict evidence covers the selected five independent consumers and
all ten producer consumers. Their literal and failure-position totals are
listed in [EVIDENCE.md](EVIDENCE.md). Matching sanitizer compile/link evidence is
not runtime success. No pending sanitizer log is treated as a pass here.

The real exact/one-under two-assessment resource fixture is DirectCQ and skips
zero observed counters. Neutral Budget tests exercise all eight additive
domains, but manufacture no evidence. Producer normalized zero-cap tests and
complete persistent-failure sweeps exercise real replay/normalization; they do
not close the narrower real-normalized exact/one-under replay/normalization
boundary gap. Mutation inequalities are not a global injectivity proof. This
review does not add exhaustive generation saturation, every normalized field
combination, every compiler/policy, or measured overhead coverage.

The registration overlay is not sealed here. Final mapping/build graph review,
remaining root sanitizer evidence, native matrices and explicit repository
acceptance remain separate gates. Nothing in this packet advances C05 or the
full goal, expands C03/S05/deployment scope, or changes structural authority.
