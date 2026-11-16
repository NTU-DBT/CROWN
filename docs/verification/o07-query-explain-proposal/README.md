# O07 query/search explanation — excluded proposal, O07 NS

This unapplied package adds owning query/search reports without a PhysicalPlan.
It changes no native inputs, tests, CMake, prior ready proposals or historical
seals. O07 remains **not_started**. Validation here compiles and links new units
and a consumer against a pinned existing library; no binary/search/replay/test
is executed. Root owns independent runtime acceptance.

## Authority and immutable API

`observability::QueryExplanation::capture(const ExactSearch&)` and
`capture(const CertificateReplay&)` read actual producer accessors. The overloads
`from(ValidatedIncumbent)`, `from(VerifiedOptimum)`, `from(VerifiedInfeasible)` and
`from(CheckedCertificate)` accept only the existing immutable checked handles.
There is no constructor accepting SearchProgress, ReplayProgress, OracleResult,
HeightCertificate, a tree, JSON, a status string or caller-edited flags.

The artifact owns an immutable SearchBinding and copied typed evidence handles.
It copies producer progress, current limits, policy and limit revision under the
producer's existing exclusive-caller discipline. Capture performs no advance,
certificate replay, recognition, tree verification, binding serialization or
JSON construction. It is an explicit allocating read, outside producer quanta.
One owning Data allocation and constant-time size checks do not charge or alter
producer counters. QueryExplainLimits independently bounds retained witness-node
and certificate-entry counts; failure leaves the producer untouched.

The binding remains the **exact original native Catalog/Query** from the owner
or evidence handle: table and variable names, occurrence order, IDs, constants,
ignored columns, ordered aliases, contradiction, source schema versions,
column nullability/collation/decimal metadata, constraints/status/references,
statistics and key hints. No alpha-equivalence, projected query substitution,
JSON equality or binding digest is used. Native raw byte strings remain native
strings until explicitly exported. SearchBinding does not own normalized SQL
source/parameters; this report does not manufacture them.

Copies survive producer movement, cancellation, limit raises, later advances
and destruction. A later report can have different progress; an older report
never changes. Passing a moved-from producer/typed handle rejects through its
existing accessor contract. A moved-from QueryExplanation rejects through
`invalid_query_explanation`. Capture is not concurrency-safe against advancing
or destroying its producer; callers already owe exclusive ownership.

## Bounds, proof and replay states

Height status is derived from genuine typed handles first:

| Status | Meaning and authority |
| --- | --- |
| `verified_optimum` | A VerifiedOptimum supplies the original checked upper and independently checked minimum proof. |
| `verified_infeasible` | A VerifiedInfeasible proves the admissible structural-tree family empty; no physical plan or witness is created. |
| `checked_upper` | A published ValidatedIncumbent establishes only an upper bound; no optimum is claimed. |
| `owner_checked_upper_unpublished` | Actual ExactSearch progress records a checked numeric upper, but strict policy has not exposed a typed witness. |
| `unknown` | No upper/proof handle or observed upper exists; search/replay can be admitted, unfinished, interrupted, invalid or cancelled. |

The last distinction follows `ExactSearch::progress()` and `incumbent()`:
progress retains the internal checked upper under strict policy, while incumbent
returns a handle only under best-found. The report preserves that numeric owner
observation but cannot export its hidden tree or select it for runtime use.
Best-found does not silently replace strict. An unfinished producer with an
incumbent remains a checked upper, regardless of how small its gap looks.

The proof domain is the original CQ atom/head structural-tree family. A nonempty
contradiction-marked query still has the P06 universal lower 1 and retains its
original structural feasibility outcome (including a cyclic triangle negative).
This is distinct from P08 lowering a contradiction to an executable constant_false
operator with height 0. Structural infeasibility never says that no executable
backend/shortcut can answer the contradictory query. JSON and human reports
state this domain explicitly; no recognizer or lower-rule change is introduced.

The lower bound is the same P06 universal empty/nonempty-body bound (0/1) until
a typed optimum or infeasibility proof exists. Infeasibility alone has no lower
or upper. Raw observed SearchProgress flags/interval are separately reported as
producer diagnostics; they never mint a report proof handle. CheckedCertificate
is retained and supplies its genuine optimum/infeasibility handle. Certificate
content is exported only from typed checked evidence, bound to the same original
input; null lower-bound entries retain the native infinity/no-completion meaning.

Replay reports preserve actual phase, recorded stop, complete/valid, checked
claim count, consumed counters, limit revision and current limits. Completing an
invalid replay can mean `complete=true, valid=false`; that is not an infeasibility
proof. Partial checked claims or a finished producer are not a checked root or
published certificate. The replay owner intentionally does not expose its input
claim or partially validated upper as checked authority, so these remain absent
until `checked()` publishes. No report call finishes replay on the caller's behalf.

WorkCounters preserve attempted work, committed transitions, allocation failures,
active nanoseconds and current/peak logical frame depth. Active time excludes
caller pause. Native active nanoseconds saturate without a separate overflow bit;
`active_nanoseconds_at_cap` therefore means exact UINT64_MAX **or capped**, not
proof of an exact duration. Other counters retain native finite-counter semantics.
`structural.work` aliases producer attempted work and `structural.certificate_work`
aliases replay attempted work; these must not be added again. Committed transitions
are a different count, not additional attempted work. The two producer/replay
phases are separately scoped in JSON. SearchStatistics are observed producer counters, not newly collected statistics
or a classifier result. Hierarchy hits can concern subproblems; they never label
the whole input q-hierarchical.

`recorded_last_stop` is exactly the owner's stored last_stop. A zero-work/zero-time
advance returns a quantum stop without changing that stored field; capture cannot
recover the most recent returned stop and explicitly says so. It does not accept
an arbitrary SearchAdvance to overwrite history. Invalid-quantum, allocation,
depth/work/time exhaustion, cancelled, failed and completed phases retain their
actual independent fields instead of being collapsed into one “unsupported”.

## Compatibility with existing exactness states

| Existing state | Query report interpretation |
| --- | --- |
| Refactor §5.5 `proven_minimum`; OracleStatus::proven_minimum | Only `verified_optimum`, with real typed proof and original witness. |
| `valid_upper_bound` | `checked_upper`; or explicitly owner-observed/unpublished upper under strict, without a selectable/exportable tree. |
| `resource_limit` | A resource stop (total work/time, depth, allocation, counter exhaustion) remains in producer state; any independently checked incumbent remains an upper, never an optimum/infeasibility proof. |
| OracleStatus::unsupported from completed exact negative proof | `verified_infeasible`, meaning no admissible tree for this exact binding, not broad SQL/frontend/backend unsupported. |
| Quantum work/time stop | Resumable/incomplete producer state; not total budget exhaustion or infeasibility. |
| Cancelled | Frozen cancelled phase, retained checked upper if published; no newly claimed proof. |
| Invalid certificate / failed replay | Complete/valid/stop reflect actual replay; no checked certificate or negative proof is synthesized. |
| Admitted / unfinished without incumbent | `unknown` with universal lower and absent upper; no fake empty tree. |
| Mutable OracleResult flags or imported JSON | No admission path; native typed replay must produce authority independently. |

Cost selection is separate: cost search is `not_run`, estimates and candidate
family exhaustion are null, fresh statistics are `not_collected`. Original
catalog estimates are retained as input metadata only. Neither structural
minimum height nor a completed height proof establishes cost optimality,
minimum-candidate-family enumeration completeness, runtime speed, state bytes,
indices, arithmetic/runtime mode, cursor guarantees or durability.

## Read-only structure and text boundaries

`recognized_class` is explicitly `not_collected`, with zero recognizer diagnostic
work because none runs. This package does not silently run a structural analysis,
charge producer work, reinterpret structural counters or reclassify proof
scope. A future optional recognized-class pass needs its own bounded diagnostic
budget and provenance; it must not mutate producer authority.

Tree export exists only when `witness()` holds a genuine ValidatedIncumbent:
`io::write_query_explain_tree_json()` preserves exact original tree claims and
binding; `write_query_explain_dot()` uses generated numeric DOT IDs and escaped
original labels. A missing witness throws `query_explain_no_witness`, including
infeasible, incomplete replay, strict-withheld upper and unknown reports. An
empty-body **checked** witness can legitimately have zero nodes; this is distinct
from fabricating an empty tree for a missing witness. Export does not rerun P02,
derive missing separators/C*, invoke Graphviz, execute commands or generate SVG.
Original claimed separators/connex/height remain labeled claims from the checked
witness. The existing physical-plan EXPLAIN remains the source of full compiled
separator/index/runtime metadata.

`write_query_explain_json()` and `write_query_explain_text()` emit complete owning
strings under an encoded-byte cap. Every native text field actually emitted is
strictly checked for UTF-8 and controls/NUL/quotes/backslashes are escaped. An
oversized string is rejected before scanning it; output appends remain capped.
No JSON DOM is used, and no JSON/text operation runs during report admission or
producer unwind. Native invalid-byte bindings can be captured normally and fail
only a text export containing those bytes. DOT need not emit a raw-byte constant
that appears only in the query binding; it validates the labels it does emit.
Transport failure leaves both report and producer intact. Exported JSON/schema
is a diagnostic representation, never a checked-handle deserializer.

`schemas/query-explain-v1.schema.json` and `query-witness-v1.schema.json` are closed
Draft 2020-12 shape contracts. They preserve scalar tags (including `bool`, exact
date/decimal strings), binding metadata, statuses, nullable unavailable values,
and source/proof-family conditions. Equality of numeric lower/upper/witness
heights, certificate binding, node references and producer invariants still need
independent semantic checks; schema validation cannot grant proof authority.

## Finite fixtures and required independent tests

`fixtures/query_families.hpp` supplies native typed inputs only. Anchor families
include empty body, nullary relation, unary/single-atom projection, full-head
path, non-free-connex endpoint projection, disconnected product, cyclic triangle,
empty/nonempty contradiction metadata and a raw native byte-string constant. Expected admissibility
labels are test expectations, never report inputs. The separate systematic
family contains **426** inputs: choose 1..3 distinct nonempty scopes from the
seven scopes over three variables and every head subset of their union. It is a
finite fixture scope, not an arbitrary-query completeness claim. Compare its
outcomes/heights with the independent literal labelled-topology/native-power-set
`reference::exhaustive_minimum_tree`, not with the report's own status logic.
No fixture is executed by this package's author.

Required status/lifetime families:

1. Actual strict and best-found producers: admitted, preprocessing/search,
   work/time/depth-limited before/after a checked upper, producer finished before
   proof publication, quantum stops, zero quantum with unchanged owner progress,
   limit raise/rejection, cancellation and terminal optimum/infeasibility.
2. Genuine replay: admitted/partial, interrupted/cancelled, valid optimum and
   infeasible proof; corrupted claims/tree/root/algorithm and invalid replay.
   No partial flags or copied edited progress can enter a report factory.
3. Capture before owner advance/move/drop and verify copied binding, counters,
   options, limits, original tree/certificate and previous report never change.
   Typed upper, optimum, negative and checked-certificate constructors preserve
   authority. Moved-from producers/handles/reports reject; captures never advance.
4. Strict hidden-upper state cannot export a tree; best-found genuine upper can;
   infeasible/invalid/pending replay cannot fabricate a tree. Verify original
   bindings, duplicate aliases, constraints/status/FKs, decimal/date metadata,
   untrusted catalog statistics, key hints and native byte constants exactly.
5. Independent JSON/schema and semantic checks for every status/source family,
   human status consistency, checked DOT/tree reference integrity, bounded text
   exact boundary and UTF-8/control/NUL behavior. Resource failures are export/
   report failures only; owner progress and proof artifacts remain unchanged.
6. The systematic 426-query family under deliberately interrupted search and
   replay, with independent finite oracle agreement on final height/negative
   outcomes. Independent allocation-failure tests must retain producer state and
   prohibit partial report publication.

## Build, dependencies and remaining integration

Only four new library files are proposed. `query-explain.patch` also adds the two
schemas; it is never applied. `baseline-sha256.json`, `proposal-sha256.json`,
compiler dependency hashes and readiness manifest pin inputs/artifacts.

The owning unit depends on unchanged planner/search and core IR; IO depends on
that owning unit and core scalar formatting. Both new units and a link-only
consumer build with strict C++23 conversion warnings and `-Werror` at O0 and O3,
linking **only the pinned native libcrown_core.a**. Native core already owns the
exact-search/replay implementation. No runtime overlay, physical-plan archive,
SQL/PG archive or changed native ABI is needed. The fixture header is parsed by
the consumer compiler but never executed.

Acyclic future target arrangement: a new `crown_query_explain` target can contain
both units and link publicly to `crown_core`; the eventual observability/CLI
facade links to this target and existing physical/runtime report targets. Do not
place the new IO source into crown_core while making core depend back on the new
owning target. No CMake change is made here.

```sh
python3 docs/verification/o07-query-explain-proposal/build_proposal.py /tmp/crown-o07-query-explain-o0 --opt 0
python3 docs/verification/o07-query-explain-proposal/build_proposal.py /tmp/crown-o07-query-explain-o3 --opt 3
```

The frozen library is reused at its recorded build/hash; O0/O3 here describe the
new units/consumer, not a new native library build. Compile/link success is not
runtime verification. Native query/physical/runtime human+JSON/schema/CLI wiring,
run-context/cursor companion integration, independent report and instrumentation
acceptance, remaining registry gaps and the native matrix remain next steps.
O07, S05 whole-memory and durable/checkpoint/recovery gates remain open.
