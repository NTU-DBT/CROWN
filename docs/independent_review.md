# Independent source-to-invariant review

V02 is verified for the documented conditional source arguments. Separate
reviewers inspected the relevant implementation scopes; root received their
arguments, source pins, counterexamples and actual producer/consumer joins.
The [V46 report](verification/v02-independent-review-2026-11-14.md) records the
selected native checks. The [V47 receiving report](verification/v02-public-guarantees-2026-11-14.md)
records catalogue closure, usage cards and the two reviewed tool input changes.
Engine code is unchanged. Existing
[bounded W06 acceptance](verification/human-inspection-v33-2026-11-13.md) remains
verified. The full Refactor goal, experiments and release gates remain open.

Start with a public claim below, follow its implementation and usage contract,
then inspect the corresponding proof packet. Every packet identifies the frozen
bytes and the ranges actually read. A whole-file digest does not mean every
branch was reviewed. Finite models and native fault sweeps supplement the
arguments; neither proves completeness or every possible failure point.

| Claim | Implementation and usage specification | Checked argument and counter boundary |
| --- | --- | --- |
| G01: admitted SQL and NULL semantics | [Binding](../src/frontend/bind.cpp), [normalization](../src/frontend/normalize.cpp), [nullable SQL](sql_rows_runtime.md) | [SQL review](../build/verification/v02-sql-aggregate-proof-review-v1/report.txt): whitelist/type/three-valued-logic induction and canonical presence/payload encoding. Selected binder/source work is not total compiler CPU. The only subquery form is a whole-result EXISTS wrapper without outer FROM/WHERE; correlation rejects. |
| G02: complete physical identity and independent aliases | [Physical state](../src/runtime/physical.cpp), [physical contract](physical_runtime.md) | [Support/physical review](../build/verification/v02-support-physical-proof-review-v1/review.md): each occurrence count equals the number of admitted complete source rows mapping to its key; only zero crossings change native membership. Alias, derivation and crossing counters measure different operations. |
| G03: minimum native height | [Exact search](../src/planner/exact.cpp), [certificate replay](../src/planner/certificate.cpp), [planner proof](planner_proofs.md) | [Independent planner review](../build/verification/v02-planner-proof-review-v1/report.txt): native-anchor finite normal form, partition recurrence and independent lower-bound checking. Only completed search plus replay proves optimality. Resource stops retain their own status and cumulative grants. |
| G04: exact ordered projected set delta | [Anchor/live primitives](../src/runtime/delta.cpp#L306), [usage cards](code_specs/files/src/runtime/delta.cpp.md), [specification](delta_transition_spec.md), [ordered contract](ordered_delta.md) | [Delta review](../build/verification/v02-delta-proof-review-v1/review.md): earliest changed factor partitions answers once; same-sign stage prefixes preserve downward totality; fresh descendant witnesses justify live deletion. Journal/view, probe, queue and output counters refer to their actual phases. |
| G05: bounded internal indexed producer steps | [Delta runtime](../src/runtime/delta.cpp), [ordered contract](ordered_delta.md) | The delta review separates route preparation from first/next/last productive transitions and finalization. The accepted bound counts selected indexed actions after preparation for a fixed query. Scalar width, allocator work and complete public atomic startup are additional costs. |
| G06: atomic preparation, inverse and publication | [Support](../src/runtime/support.cpp), [physical state](../src/runtime/physical.cpp), [delta runtime](../src/runtime/delta.cpp), [lifecycle](physical_runtime.md) | Support/physical and delta reviews trace owned inverses, saved nodes, view closure and commit ordering. [Storage receiving](../build/verification/v02-storage-leaf-review-v1/report.txt) checks exact lookup, saved-node inverse and nonallocating publication; the account argument supplies allocation/release assumptions. No in-memory token establishes external delivery or crash durability. |
| G07: one finite receiving query account | [Memory account](../src/resource/memory.cpp), [query memory contract](query_memory.md) | [Root arguments with independent corrections](../build/verification/v02-independent-review-v1/root-system-arguments-v2.md): allocation-list induction proves requested-byte admission and ownership. [Native owner chains](../build/verification/v02-funded-runtime-review-v1/review.md) and [ranking/selection/reoptimization owners](../build/verification/v02-planner-funding-review-v1/review.md) have separate field/caller arguments; the [closure appendix](../build/verification/v02-closure-audit-v1/leaf-arguments.md) supplies remaining actual caller joins. A new outer operation's finite work grant does not refill the query byte cap. |
| G08: exact bounded weighted messages | [Weighted maintenance](../src/runtime/weighted.cpp), [message contract](weighted_messages.md) | [Weighted review](../build/verification/v02-weighted-proof-review-v1/review.md): full child products, separator sums and causal FIFO replacement; generalized candidates intersect complete scopes before projection. Numeric events, slot visits and products are distinct from membership crossings. |
| G09: projected bag factorization and cursor | [Weighted cursor](../src/runtime/weighted_cursor.cpp), [lowering](../src/planner/lower.cpp), [enumeration contract](weighted_enumeration.md) | Weighted review: cut C* edges, sum independent hidden choices inside each component, then multiply local visible factors once. Visible keys merge hidden root witnesses before enumeration. Cursor counters describe selected startup/advance/termination/cleanup work. |
| G10: genuine original-SQL aggregate NetBatch | [SQL source](../src/runtime/sql_rows.cpp), [group coordinator](../src/runtime/sql_aggregate.cpp), [composition contract](sql_aggregate_runtime.md) | SQL review: authenticated final source state, decreases-first alias staging, mutation-time delta telescope, complete group identity and final-only batch SUM checks. Genuine nonzero facts, touched group widths, decoded fields and output bytes have separate counters. |
| G11: SQL aggregate WAL/decision/sink frontiers | [Session](../src/recovery/sql_aggregate_session.cpp), [replay](../src/recovery/sql_aggregate_session_replay.cpp), [contract](sql_aggregate_session.md) | Root arguments: delivered ≤ committed ≤ disposed ≤ logged, with at most one unresolved Input. Commit sync precedes publication of the same prepared token; resource denial is not a semantic Reject. [File arguments](../build/verification/v02-independent-review-v1/root-file-arguments-v2.md), [codec review](../build/verification/v02-recovery-codec-review-v1/review.md) and [checkpoint reconstruction](../build/verification/v02-aggregate-checkpoint-review-v1/review.md) receive those local leaves; the [closure audit](../build/verification/v02-closure-audit-v1/review.md) reconciles their actual composition. |
| G12: performance qualification | [Guarantees](guarantees.md), [ranking model](ranking.md) | Minimum height and proxy rankings do not prove global CPU/memory optimum or a universal speedup. Counters and finite observations retain their own units. |
| G13: crash evidence scope | [Session contract](sql_aggregate_session.md), [file contract](sql_aggregate_files.md) | Finite interruption profiles cover their named native/syscall seams. Trusted local-filesystem sync assumptions are explicit; no every-instruction or arbitrary hardware power-loss theorem is claimed. |
| G14: capability profiles and counters | [Physical profile](../include/crown/ir/physical.hpp), [runtime profile](../src/runtime/delta.cpp), [guarantees](guarantees.md) | Immutable compile-time capability metadata differs from effective runtime strategy/state. Selected abstract work is not a complete CPU, RSS or instruction meter. Legacy frozen EXPLAIN labels are versioned historical fields; see [observability](observability.md). [Export receiving](../build/verification/v02-public-export-review-v1/review.md) and [L02](../build/verification/v02-closure-audit-v1/leaf-arguments.md) trace actual field/version/availability encoders. |
| G15: set Session local delivery and recovery | [QuerySession](../src/runtime/session.cpp), [journal contract](session-journal.md), [local sink](local-sink.md) | [File-protocol review](../build/verification/v02-file-protocol-review-v1/review.md): durable decision before acknowledgment, complete-byte duplicate comparison and candidate sync before selected-root publication. Combined restore validates before sequential WAL/sink repair; plain sink reopen compares post-checkpoint contents during delivery. |
| G16: recognized free-connex class has an admitted tree | [Recognition](../src/planner/recognize.cpp), [tree rules](planner_proofs.md#free-connex-class-and-tree-existence) | [Class bridge](../build/verification/v02-freeconnex-class-bridge-review-v1/report.txt): augmented join-tree branches construct a native-only witness; anchored contraction and connex rewiring give the converse. Generalized nodes can improve height. Finite models supplement the proof; finite machine/resource stops are not infeasibility. |
| G17: source, queue and window progress | [Reader](../src/io/event_reader.cpp), [window](../src/runtime/window.cpp), [input contract](ingestion.md) | [Source recovery](../build/verification/v02-source-recovery-review-v1/report.txt): retained complete input, acknowledgment, source/window restoration and replay validation are separate transitions. Optional seek can precede final sink checks; all checks precede repair. [L03](../build/verification/v02-closure-audit-v1/leaf-arguments.md) supplies options, TransportBatch and actual OrderedReplay joins; external consumed prefix bytes remain a caller obligation. |
| G18: reoptimization preserves future behavior and durable selection | [Candidate replay](../src/runtime/reoptimization.cpp), [Session](../src/runtime/session.cpp), [switch contract](reoptimization.md) | [C06 argument](../build/verification/v02-reoptimization-semantic-review-v1/review.md): committed backlog is an exact contiguous prefix; pending heads survive until commit, target failures preserve old progress, and exact source/options plus same-boundary source/configured-view comparison precede publication. Matching one current row set alone does not imply future equivalence. |
| G19: selected state populations and transactional workload facts | [Statistics](statistics.md), [collector](../src/runtime/statistics_collection.cpp), [observations](observability.md) | [Observation argument](../build/verification/v02-observation-grant-review-v1/review.md): completed distributions scan their declared populations; incomplete scans publish no prefix as exact. Workload cells contain committed facts; live Metadata can include pending attempts. C01 samples admitted attempt ordinals; O07 trace selection uses physical sequence. |
| G20: deterministic retained-family ranking and constrained selection | [Ranking](ranking.md), [selection](selection.md), [integer primitive](../src/planner/ranking_integer.cpp) | [Selection argument](../build/verification/v02-selection-semantic-review-v1/report.md): exact limb arithmetic, common-denominator depth order, candidate-local slots and full-key ties. Mandatory caps precede fallback. Every valid C05 select_current requires the fresh owner boundary; C02 height-only rank_current does not capture currentness. Slots are not allocator bytes. |
| G21: composed indexed-work grants | [IndexWork](../include/crown/storage/index_work.hpp), [retained operation lease](../src/runtime/storage_work.hpp), [indexed contract](indexed_storage.md) | The observation argument proves all-domain denial nonmutation and exact same-context lease forwarding through update, cursor, capture and rebuild callers. A resumed operation spends its retained balance. Independent outer operations have fresh finite work grants on the original byte account; work units are not CPU time. |
| G22: verified set-session history retirement | [Retirement](../src/recovery/generation_retirement.cpp), [usage and formats](history-retirement.md) | [Retirement argument](../build/verification/v02-retirement-proof-review-v1/report.txt): genuine sink-prefix authority, durable intent before floor, exact old-name whitelist and synced deletion before intent removal. Merely queued input is permitted; active/logged input is not. Trusted namespace and genuine-intent assumptions remain. R2 aggregate retirement is open. |
| G23: conditional cost forecasts and declared calibration | [C03 API](../include/crown/runtime/maintenance_cost.hpp), [model](maintenance_cost.md) | [Positive C03 argument](../build/verification/v02-cost-model-review-v1/report.md): admitted reduced 64-bit rational forecasts, explicit unknown terms, actual candidate profiles and owned publication. Fitting is approximate and labeled; accuracy, causal attribution and future memory remain unproved. C05 still rejects maintenance_cost. |
| G24: controlled finite measurement reporting | [Runner](../tools/run_measurements.py), [collector](../examples/workload-measurement/main.cpp), [measurement usage](measurement.md) | [B03 argument](../build/verification/v02-measurement-review-v1/review.md): independent native gates precede trials; clock partitions, empirical summaries and process/account memory retain their actual units. JSONL file content has a stronger measured check than discard/none. Failed-packet recording has a protected-loop/save boundary. |
| G25: standalone storage primitives | [Storage](storage.md), [arenas](tuple_arenas.md), [indexes](indexed_storage.md), [journals](storage_journal.md) | [Ordinary storage receiving](../build/verification/v02-standalone-storage-review-v1/review.md) proves actual table/arena/index/journal/PlanStorage composition separately from native accounted storage. Ordinary containers remain outside S05. [L04](../build/verification/v02-closure-audit-v1/leaf-arguments.md) proves actual D01/D02 hidden/visible enumeration; hidden witness scans retain their real costs. |
| G26: scalar, catalog and caller codec contracts | [Scalars](scalars.md), [catalog](catalog.md), [CQ reader](../src/io/document.cpp) | [Scalar/catalog receiving](../build/verification/v02-scalar-catalog-codec-review-v1/report.md), [export/identity/native-pack receiving](../build/verification/v02-public-export-review-v1/review.md) and [L01/L02](../build/verification/v02-closure-audit-v1/leaf-arguments.md) trace actual formats, versions, initial native packing and canonical identity. UTF8 serialization is narrower than arbitrary native binary strings. DTOs and hashes alone confer no authority. |
| G27: local CLI/package identity and workflows | [CLI](cli.md), [installed workflow](native_build.md), [version](../include/crown/version.hpp) | [CLI/package receiving](../build/verification/v02-cli-package-review-v1/report.md) and [L05/L06](../build/verification/v02-closure-audit-v1/leaf-arguments.md) supply positive dispatch, error-layer, output, install and example contracts. Historical [O08](verification/o08-workflow-acceptance-2026-11-10.md) and [V01](verification/v01-documentation-2026-11-14.md) retain their bounded scope; no published release is claimed. |

The [support review](../build/verification/v02-support-physical-proof-review-v1/review.md)
also supplies the upstream factor argument: native S rows require every child
separator; generalized S is the complete-scope intersection; P/E count distinct
local survivors. Running intersection and output-only C* cuts then establish
downward totality and equality of the E join with projected answers. Direct and
replay initialization reach the same uniquely determined recursive state.

The [R1 source/window receiving review](../build/verification/v02-source-recovery-review-v1/report.txt)
checks native reconstruction and source acknowledgment. Ordinary restore does not
seek/read a continuation. Optional journal-recovery seek follows native/source
replay validation but precedes final sink/tail checks; all those checks precede
repair. The [descriptor review](../build/verification/v02-descriptor-admission-review-v1/review.md)
separates bounded structural preflight from genuine compiler/runtime rebind.
Its item cap is shared across binding and recipe in each structural pass; the
original report's “per image” phrase is qualified by the receiving receipt.

## Coverage and dependency closure

The [public-header census](../build/verification/v02-public-header-census-v1/report.md)
accounts for all 139 headers as a breadth inventory. Its exact full-header pins
and declarations route inspection; they do not certify all implementations.
The earlier [22-row catalogue](../build/verification/v02-public-claim-catalogue-v1/report.md)
is supplemented here by C03, B03, standalone storage, scalar/codec and CLI/package
contracts. Historical verified component status does not discharge a missing
source argument. The [closure audit](../build/verification/v02-closure-audit-v1/review.md)
and [six actual leaf arguments](../build/verification/v02-closure-audit-v1/leaf-arguments.md)
reconcile the remaining producer/consumer joins. Root's
[dependency dispositions](../build/verification/v02-public-guarantee-closure-v1/dependency-dispositions-v1.json)
record acceptance with explicit external premises and counter units.

[C07 receiving](../build/verification/v02-baseline-evaluation-review-v1/report.md)
adds the concrete finite baseline-evaluation algorithms: training-only selection,
preflight, frozen calibration, eligibility, exact affine-fit decisions and regret.
It does not establish C03 event-forecast accuracy or future generalization.

The [SHA-256 receiving argument](../build/verification/v02-digest-leaf-review-v1/root-argument-v2.md)
compares the constants and recurrence with NIST FIPS 180-4 and binds word arithmetic
to the recorded native ABI. Release-SDK and sanitizer probes check finite vectors;
they do not prove behavior on every C++ integer-promotion model.

## Counterexamples and dispositions

| Tempting simplification | Why it fails | Current disposition |
| --- | --- | --- |
| Use residual rounds as minimum height | The inspected seven/nine-atom families have a height-three witness and no height-two tree despite the smaller residual recipe. | Exact search and certificate replay retain authority; [residual candidates](residual_candidates.md) are proposals. |
| Project signed witness differences | Old and new hidden witnesses can cancel at the same visible answer. Projecting their signed witness deltas emits spurious set changes. | Compare projected endpoints and use earliest-factor ownership. |
| Multiply the full subtree annotation at every cursor node | Parent annotations already contain inside-child weights, so multiplying them again double counts. | Local visible factors include outside-C* children only, followed by hidden sums. |
| Check SUM(integer) after each contribution in a batch | Large opposite contributions may temporarily exceed bigint while the final group sum fits. | Keep the bounded wide numerator and check final touched groups; standalone single-row behavior remains immediate. |
| Treat resource failure as SQL rejection or an empty answer | Work/account denial says nothing about semantic validity. | Preserve the typed resource error and the committed state. |
| Treat a complete prefix digest as proof of identical output | Metadata can agree without comparing the producer's real bytes. | Duplicate delivery compares the entire canonical frame. |

The original weighted finite model included one tree outside Above admission.
Its packet remains unchanged and is labeled algebraic over-approximation here.
The [support packet](../build/verification/v02-support-physical-proof-review-v1/valid-weighted-results.json)
adds a valid nested generalized replacement shape: 59,049 states and 118,098
before/after checks. Those counts are finite evidence, not the factorization proof.

The localized inspector's lack of a separate configured-cap comparison was also
investigated. It compares exact source-derived counts; no admitted route to a
coherent over-cap state or failure of the documented corruption probes was found.
The difference from the legacy policy audit is optional diagnostic coverage,
not a demonstrated defect requiring another runtime guard.

## Paper and implementation authority

Use the [exact paper versions and source map](code_review.md#exact-paper-versions).
P1 v2 Definition 3.2 supplies Guard/Above/Connex in addition to Definition 3.1's
Cover/Connect notation; Definition 3.1 alone is insufficient. P2 v1 §2.1.1 gives
the native-anchor generalized-scope convention and §2.1.3 the full tree rules.
Classical GYO recognition, the local exact-height recurrence and the repair of
the inspected residual recipe have their own arguments. C++ ownership, SQL
admission, account caps and durable files are local engineering contracts.

No production catch, defensive framework, persistent state or update-path
instrumentation was added for this review. Costs in the usage cards remain
the costs of the actual primitive, including preparation and teardown.
