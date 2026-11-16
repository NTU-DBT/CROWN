# Reviewed primitives and phase order

Use these cards to inspect the hot path before changing abstractions or deleting error handling. Each linked card has purpose, inputs/outputs, invariants, ownership/lifetime, failure boundary, costs and justified design references. Cards are scoped to named anchors; they do not prove all branches. Other source blocks remain explicitly structural maps.

| Phase | Owning state | What must finish before the next phase |
| --- | --- | --- |
| Admit | Original query account, immutable program, finite outer storage grant | Validate identity/types/options; reserve required work and ownership. |
| Prepare/private mutate | Source/table journals, metadata inverse records, queued causal events | Record inverse state before changing each structure; drain required propagation; prepare output. |
| Durable decision, if enabled | Journal/generation/sink file and lock owner | Decide/record authority; uncertain outcomes retain recovery-required state. |
| Publish | Pending runtime/session owner | Nonthrowing native commit, owner moves and sequence publication. |
| Retain/release | Epochs, cursors, output rows, undo pins and reports | Preserve borrowed lifetimes until the last lease; release without new allocation. |

## Memory account

Ordinary allocation/counter work and whole-ledger diagnostics are different primitives. Requested bytes include headers/alignment; they are not RSS. Standard-container allocators fund their own storage, not arbitrary nested members.

## Hash directory and live list

Prepare growth and inverse work before pointer publication. Hash lookup still performs exact equality under collisions. Prepaid link/unlink is O(1); live traversal follows live links, while diagnostics may scan capacity or repeatedly search collision chains.

## Boolean, physical and weighted propagation

Boolean P/E counters propagate membership zero crossings. Physical aliases maintain their own derivation counts and share one private input epoch. W02 numeric messages propagate every unequal value, including positive-to-positive changes; its default compact undo avoids full diagnostic record copies. W03 local factors exclude enumerated C* children; the result cursor multiplies those child factors once. FactorChange records are local inspection changes, not joined-answer deltas. Cursor scratch includes C* frames and the ordered output width, including repeated head fields. These are distinct usage contracts.

## Prepared source net batch

The [SQL source batch](../sql_rows_batches.md) authenticates complete-row weight
chains against the committed ledger, validates final touched constraint counters,
funds publication nodes, and stages decreases before increases through one native
epoch. Closing the token releases its temporary workspace immediately. Native
bag previews still require the genuine compiled output binding for SQL decoding.
Detached nodes remove allocation from publication; ordered comparisons and
teardown remain real work.

## Physical source images and cold construction

[Capture](../sql_source_images.md) reads complete original physical bags and
shares immutable row owners under one allowance. Cold reconstruction validates
genuine source/native binding, then copies admitted state into the receiver.
For C>0, one unpublished owner at C−1 consumes one complete seed at C. Source,
native, indexed and group build grants span their declared whole-image work;
all cold owners close before the normal context is installed. The existing
prepared tokens own rollback. There is no joined-row cache, live sequence setter,
extra update field or new catch. Capture/cold costs and durable-proof limits are
explicit in the guide; neither operation establishes a new paper bound.

## R2 transport primitives

The [R2 codec](../sql_aggregate_records.md) funds a pending physical command as
one frame plus flat cell/replacement arrays. It sorts full group keys with one
packed scratch buffer and index vector, then retains one canonical output frame.
Inspection and WAL transitions use fixed/borrowed data; failed feed publishes no
candidate state. These checks do not establish actual file durability or native
replay. The upper target adds no field or work to ordinary runtime updates.

## Genuine descriptor and selected bytes

[Descriptor admission](../sql_aggregate_descriptor.md) rebinds original SQL and
compares its exact binding plus actual native recipe before exposing C0. Finite
producer compiler caps within receiving caps need one lowering; other cases get
one additional bounded cold check. The opaque checkpoint/plan reader shares
regular-file, root, stamp, EOF and hash checks. Neither primitive acknowledges
sink output or establishes WAL replay or minimum-height authority.

## Complete physical checkpoint

The [checkpoint codec](../sql_aggregate_checkpoint.md) sorts complete nullable
physical row keys once, writes one frame and retains no runtime-state mirror.
Inspection borrows the frame without covered allocation. Restore checks complete
metadata before receiving allocation, materializes original physical rows, then
uses one genuine whole-image reconstruction at C. Temporary decoded/live rows
overlap during cold construction; their separate codec/build allowances remain
cumulative. Progress I and runtime C remain distinct. The delivery DTO records
data; actual W/I/C/D ownership is the durable coordinator's responsibility.

## Concrete R2 file owners

[WAL and sink files](../sql_aggregate_files.md) freeze genuine schema metadata into
the receiver and own actual regular-file descriptors and locks. WAL append stages
fixed spent cursor state, then publishes it only after sync and final stat. The
sink prepays offset-index capacity and chaining; duplicate delivery compares the
complete actual epoch in bounded chunks. Neither owner retains a second command
or output queue. A failure after I/O admission poisons getters and requires
reopening. Explicit incomplete-tail repair is a low-level primitive whose caller
must first finish the whole root/native replay/sink-coverage validation barrier.
Only a healthy untorn actual sink mints its receipt; DTOs remain data.

## Reviewed source cards

Each source page keeps every scoped anchor, seven-field usage/cost contract and reference. This compact index avoids duplicating those contracts; a listed source is not automatically fully reviewed.

| Source | Scoped contracts | Usage context |
| --- | ---: | --- |
| [CMakeLists.txt](files/CMakeLists.txt.md) | 1778 | Define native target boundaries, pinned dependencies, compilation options, installation and test registration. |
| [apps/crown/aggregate.cpp](files/apps/crown/aggregate.cpp.md) | 20 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [apps/crown/aggregate.hpp](files/apps/crown/aggregate.hpp.md) | 1 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [apps/crown/explain.cpp](files/apps/crown/explain.cpp.md) | 19 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [apps/crown/explain.hpp](files/apps/crown/explain.hpp.md) | 1 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [apps/crown/main.cpp](files/apps/crown/main.cpp.md) | 32 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [apps/crown/workflow.cpp](files/apps/crown/workflow.cpp.md) | 61 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [apps/crown/workflow.hpp](files/apps/crown/workflow.hpp.md) | 1 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [apps/crown/workflow_verify.cpp](files/apps/crown/workflow_verify.cpp.md) | 11 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [apps/crown/workflow_verify.hpp](files/apps/crown/workflow_verify.hpp.md) | 1 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [cmake/CrownConfig.cmake.in](files/cmake/CrownConfig.cmake.in.md) | 10 | Define native target boundaries, pinned dependencies, compilation options, installation and test registration. |
| [cmake/CrownInstall.cmake](files/cmake/CrownInstall.cmake.md) | 36 | Define native target boundaries, pinned dependencies, compilation options, installation and test registration. |
| [cmake/LibPgQuery.cmake](files/cmake/LibPgQuery.cmake.md) | 56 | Define native target boundaries, pinned dependencies, compilation options, installation and test registration. |
| [examples/component-planning/CMakeLists.txt](files/examples/component-planning/CMakeLists.txt.md) | 7 | Define native target boundaries, pinned dependencies, compilation options, installation and test registration. |
| [examples/component-planning/main.cpp](files/examples/component-planning/main.cpp.md) | 44 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/component-planning/reference.cpp](files/examples/component-planning/reference.cpp.md) | 17 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/component-runtime/CMakeLists.txt](files/examples/component-runtime/CMakeLists.txt.md) | 33 | Define native target boundaries, pinned dependencies, compilation options, installation and test registration. |
| [examples/component-runtime/aggregate.cpp](files/examples/component-runtime/aggregate.cpp.md) | 10 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/component-runtime/component_request.hpp](files/examples/component-runtime/component_request.hpp.md) | 17 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/component-runtime/legacy_cpp.cpp](files/examples/component-runtime/legacy_cpp.cpp.md) | 5 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/component-runtime/native_request.hpp](files/examples/component-runtime/native_request.hpp.md) | 14 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/component-runtime/native_rows.cpp](files/examples/component-runtime/native_rows.cpp.md) | 4 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/component-runtime/native_set.cpp](files/examples/component-runtime/native_set.cpp.md) | 6 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/component-runtime/session.cpp](files/examples/component-runtime/session.cpp.md) | 8 | Own input-to-output and durable lifecycle transitions for one creator-thread query session. |
| [examples/cost-calibration/CMakeLists.txt](files/examples/cost-calibration/CMakeLists.txt.md) | 8 | Define native target boundaries, pinned dependencies, compilation options, installation and test registration. |
| [examples/cost-calibration/main.cpp](files/examples/cost-calibration/main.cpp.md) | 23 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/independent-queries/CMakeLists.txt](files/examples/independent-queries/CMakeLists.txt.md) | 8 | Define native target boundaries, pinned dependencies, compilation options, installation and test registration. |
| [examples/independent-queries/main.cpp](files/examples/independent-queries/main.cpp.md) | 7 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/input-specialization/main.cpp](files/examples/input-specialization/main.cpp.md) | 12 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/meta-candidates/CMakeLists.txt](files/examples/meta-candidates/CMakeLists.txt.md) | 8 | Define native target boundaries, pinned dependencies, compilation options, installation and test registration. |
| [examples/meta-candidates/main.cpp](files/examples/meta-candidates/main.cpp.md) | 2 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/native-workflow/CMakeLists.txt](files/examples/native-workflow/CMakeLists.txt.md) | 8 | Define native target boundaries, pinned dependencies, compilation options, installation and test registration. |
| [examples/native-workflow/main.cpp](files/examples/native-workflow/main.cpp.md) | 15 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/ranking-evaluation/CMakeLists.txt](files/examples/ranking-evaluation/CMakeLists.txt.md) | 7 | Define native target boundaries, pinned dependencies, compilation options, installation and test registration. |
| [examples/ranking-evaluation/main.cpp](files/examples/ranking-evaluation/main.cpp.md) | 25 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/reoptimization/CMakeLists.txt](files/examples/reoptimization/CMakeLists.txt.md) | 8 | Define native target boundaries, pinned dependencies, compilation options, installation and test registration. |
| [examples/reoptimization/main.cpp](files/examples/reoptimization/main.cpp.md) | 19 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [examples/workload-measurement/CMakeLists.txt](files/examples/workload-measurement/CMakeLists.txt.md) | 7 | Define native target boundaries, pinned dependencies, compilation options, installation and test registration. |
| [examples/workload-measurement/main.cpp](files/examples/workload-measurement/main.cpp.md) | 63 | Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces. |
| [include/crown/annotations/policy.hpp](files/include/crown/annotations/policy.hpp.md) | 25 | Admit W01 annotation policies and implement exact bounded support/aggregate arithmetic. |
| [include/crown/api/error.hpp](files/include/crown/api/error.hpp.md) | 3 | Own a public diagnostic code/message using std::runtime_error; this header carries no planner/runtime validity guarantee. |
| [include/crown/catalog/catalog.hpp](files/include/crown/catalog/catalog.hpp.md) | 4 | Validate schema, table/column identity and declared integrity constraints before query or data admission. |
| [include/crown/frontend/adapter.hpp](files/include/crown/frontend/adapter.hpp.md) | 11 | Apply occurrence-local constants/repeated-variable tests and positional projection. |
| [include/crown/frontend/admission.hpp](files/include/crown/frontend/admission.hpp.md) | 8 | Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics. |
| [include/crown/frontend/aggregate.hpp](files/include/crown/frontend/aggregate.hpp.md) | 10 | Declare immutable aggregate input/group/measure/output descriptors and checked integer-column guards. |
| [include/crown/frontend/bind.hpp](files/include/crown/frontend/bind.hpp.md) | 21 | Resolve table/column aliases, expressions and exact typed literals against catalog metadata. |
| [include/crown/frontend/normalize.hpp](files/include/crown/frontend/normalize.hpp.md) | 12 | Normalize bound equality predicates, contradictions and SQL output semantics into a typed CQ. |
| [include/crown/frontend/parser.hpp](files/include/crown/frontend/parser.hpp.md) | 6 | Own the libpg_query parse result and expose the admitted parser representation. |
| [include/crown/frontend/sql_aggregate.hpp](files/include/crown/frontend/sql_aggregate.hpp.md) | 10 | Declare immutable original-SQL/source/kernel binding with physical-origin decoding; no executable plan or recovery authority. |
| [include/crown/frontend/sql_rows.hpp](files/include/crown/frontend/sql_rows.hpp.md) | 22 | Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics. |
| [include/crown/io/admission.hpp](files/include/crown/io/admission.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/batch.hpp](files/include/crown/io/batch.hpp.md) | 68 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/binding.hpp](files/include/crown/io/binding.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/candidates.hpp](files/include/crown/io/candidates.hpp.md) | 1 | Retain and enumerate checked minimum-height candidate alternatives under bounded content budgets. |
| [include/crown/io/catalog.hpp](files/include/crown/io/catalog.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/catalog_source.hpp](files/include/crown/io/catalog_source.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/checkpoint.hpp](files/include/crown/io/checkpoint.hpp.md) | 22 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/compiler_plan_artifact.hpp](files/include/crown/io/compiler_plan_artifact.hpp.md) | 22 | Read/write explicit compiler-owned plan artifacts at the native admission boundary. |
| [include/crown/io/cursor_observation.hpp](files/include/crown/io/cursor_observation.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/document.hpp](files/include/crown/io/document.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/explain.hpp](files/include/crown/io/explain.hpp.md) | 10 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/identity.hpp](files/include/crown/io/identity.hpp.md) | 21 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/ingest.hpp](files/include/crown/io/ingest.hpp.md) | 86 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/input_options.hpp](files/include/crown/io/input_options.hpp.md) | 28 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/input_progress.hpp](files/include/crown/io/input_progress.hpp.md) | 52 | Track exact resumable record/source position independently of runtime/output sequence. |
| [include/crown/io/input_view.hpp](files/include/crown/io/input_view.hpp.md) | 23 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/inspection.hpp](files/include/crown/io/inspection.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/layout.hpp](files/include/crown/io/layout.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/memory_report.hpp](files/include/crown/io/memory_report.hpp.md) | 1 | Declare explicit caller-owned memory-report JSON export; this header does not collect native memory. |
| [include/crown/io/normalization.hpp](files/include/crown/io/normalization.hpp.md) | 8 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/oracle.hpp](files/include/crown/io/oracle.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/physical.hpp](files/include/crown/io/physical.hpp.md) | 10 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/query_explain.hpp](files/include/crown/io/query_explain.hpp.md) | 6 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/recognition.hpp](files/include/crown/io/recognition.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/residual.hpp](files/include/crown/io/residual.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/run_context.hpp](files/include/crown/io/run_context.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/search.hpp](files/include/crown/io/search.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/sql.hpp](files/include/crown/io/sql.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/sql_aggregate_input.hpp](files/include/crown/io/sql_aggregate_input.hpp.md) | 7 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/statistics_explain.hpp](files/include/crown/io/statistics_explain.hpp.md) | 6 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/io/support.hpp](files/include/crown/io/support.hpp.md) | 10 | Declare logical-support diagnostic trace import and snapshot/epoch JSON export. |
| [include/crown/io/tree.hpp](files/include/crown/io/tree.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [include/crown/ir/digest.hpp](files/include/crown/ir/digest.hpp.md) | 1 | Compute and encode canonical SHA-256 digests used for artifact identity. |
| [include/crown/ir/ids.hpp](files/include/crown/ir/ids.hpp.md) | 20 | Give numeric IDs distinct types so owner/component domains are not interchanged accidentally. |
| [include/crown/ir/model.hpp](files/include/crown/ir/model.hpp.md) | 31 | Define/validate query variables, atom occurrences, scopes and output metadata. |
| [include/crown/ir/physical.hpp](files/include/crown/ir/physical.hpp.md) | 25 | Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs. |
| [include/crown/ir/program.hpp](files/include/crown/ir/program.hpp.md) | 56 | Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs. |
| [include/crown/ir/program_json.hpp](files/include/crown/ir/program_json.hpp.md) | 23 | Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs. |
| [include/crown/ir/program_model.hpp](files/include/crown/ir/program_model.hpp.md) | 47 | Define account-funded native equivalents of compiler metadata. |
| [include/crown/ir/program_span.hpp](files/include/crown/ir/program_span.hpp.md) | 23 | Expose borrowed spans into immutable native program storage. |
| [include/crown/ir/scalar.hpp](files/include/crown/ir/scalar.hpp.md) | 7 | Parse, compare, hash and format exact scalar DTO values. |
| [include/crown/ir/tree.hpp](files/include/crown/ir/tree.hpp.md) | 7 | Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs. |
| [include/crown/ir/update_pattern.hpp](files/include/crown/ir/update_pattern.hpp.md) | 15 | Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs. |
| [include/crown/observability/explain.hpp](files/include/crown/observability/explain.hpp.md) | 54 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [include/crown/observability/query_explain.hpp](files/include/crown/observability/query_explain.hpp.md) | 31 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [include/crown/observability/statistics_explain.hpp](files/include/crown/observability/statistics_explain.hpp.md) | 33 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [include/crown/planner/candidates.hpp](files/include/crown/planner/candidates.hpp.md) | 25 | Retain and enumerate checked minimum-height candidate alternatives under bounded content budgets. |
| [include/crown/planner/comparisons.hpp](files/include/crown/planner/comparisons.hpp.md) | 8 | Declare immutable opt-in exact comparison predicates and typed cold admission over genuine equality-CQ plans. |
| [include/crown/planner/difference.hpp](files/include/crown/planner/difference.hpp.md) | 8 | Declare explicit set/bag difference admission, immutable positive operands, actual structural profiles and advisory residual bounds. |
| [include/crown/planner/fallback.hpp](files/include/crown/planner/fallback.hpp.md) | 12 | Declare immutable explicit classical-CQ fallback admission, actual structural class, guarantee profile and advisory row estimates. |
| [include/crown/planner/keys.hpp](files/include/crown/planner/keys.hpp.md) | 12 | Declare immutable guarded key-specialization plans, source/reduced provenance, finite cold grants and safe borrowed metadata. |
| [include/crown/planner/lower.hpp](files/include/crown/planner/lower.hpp.md) | 2 | Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata. |
| [include/crown/planner/meta.hpp](files/include/crown/planner/meta.hpp.md) | 9 | Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata. |
| [include/crown/planner/meta_candidates.hpp](files/include/crown/planner/meta_candidates.hpp.md) | 9 | Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims. |
| [include/crown/planner/meta_join_trees.hpp](files/include/crown/planner/meta_join_trees.hpp.md) | 7 | Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata. |
| [include/crown/planner/oracle.hpp](files/include/crown/planner/oracle.hpp.md) | 16 | Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims. |
| [include/crown/planner/ranking.hpp](files/include/crown/planner/ranking.hpp.md) | 47 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [include/crown/planner/recognize.hpp](files/include/crown/planner/recognize.hpp.md) | 11 | Run GYO reduction for body and augmented-head hypergraphs; distinguish free-connex, acyclic non-free-connex and cyclic cases. |
| [include/crown/planner/residual.hpp](files/include/crown/planner/residual.hpp.md) | 32 | Generate and replay residual-reduction/reconstruction candidates as a structural aid to the exact planner. |
| [include/crown/planner/search.hpp](files/include/crown/planner/search.hpp.md) | 73 | Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims. |
| [include/crown/planner/selection.hpp](files/include/crown/planner/selection.hpp.md) | 79 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [include/crown/planner/star.hpp](files/include/crown/planner/star.hpp.md) | 9 | Declare cold opt-in literal star admission and original/source-only provenance without supplying a new minimum proof. |
| [include/crown/planner/update_pattern.hpp](files/include/crown/planner/update_pattern.hpp.md) | 12 | Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata. |
| [include/crown/planner/verify.hpp](files/include/crown/planner/verify.hpp.md) | 4 | Independently validate CROWN tree coverage, guard, connected-variable paths, connex output structure and height claims. |
| [include/crown/recovery/generation.hpp](files/include/crown/recovery/generation.hpp.md) | 24 | Read/publish durable generation roots with exact identity and selection outcome. |
| [include/crown/recovery/image.hpp](files/include/crown/recovery/image.hpp.md) | 26 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [include/crown/recovery/journal.hpp](files/include/crown/recovery/journal.hpp.md) | 44 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [include/crown/recovery/journal_file.hpp](files/include/crown/recovery/journal_file.hpp.md) | 43 | Own locked WAL descriptors, validate prefix state and poison uncertain append attempts. |
| [include/crown/recovery/local_sink.hpp](files/include/crown/recovery/local_sink.hpp.md) | 67 | Persist canonical complete epoch output and return authority-bearing delivery receipts. |
| [include/crown/recovery/plan_descriptor.hpp](files/include/crown/recovery/plan_descriptor.hpp.md) | 9 | Encode/decode exact selected-plan descriptor identity for generation recovery. |
| [include/crown/recovery/session_file.hpp](files/include/crown/recovery/session_file.hpp.md) | 15 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [include/crown/recovery/session_image.hpp](files/include/crown/recovery/session_image.hpp.md) | 8 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [include/crown/recovery/sql_aggregate_checkpoint.hpp](files/include/crown/recovery/sql_aggregate_checkpoint.hpp.md) | 10 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [include/crown/recovery/sql_aggregate_descriptor.hpp](files/include/crown/recovery/sql_aggregate_descriptor.hpp.md) | 11 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [include/crown/recovery/sql_aggregate_files.hpp](files/include/crown/recovery/sql_aggregate_files.hpp.md) | 35 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [include/crown/recovery/sql_aggregate_records.hpp](files/include/crown/recovery/sql_aggregate_records.hpp.md) | 30 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [include/crown/recovery/sql_aggregate_session.hpp](files/include/crown/recovery/sql_aggregate_session.hpp.md) | 12 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [include/crown/recovery/sql_rows_checkpoint.hpp](files/include/crown/recovery/sql_rows_checkpoint.hpp.md) | 8 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [include/crown/recovery/sql_rows_descriptor.hpp](files/include/crown/recovery/sql_rows_descriptor.hpp.md) | 10 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [include/crown/recovery/sql_rows_files.hpp](files/include/crown/recovery/sql_rows_files.hpp.md) | 5 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [include/crown/recovery/sql_rows_records.hpp](files/include/crown/recovery/sql_rows_records.hpp.md) | 16 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [include/crown/recovery/sql_rows_session.hpp](files/include/crown/recovery/sql_rows_session.hpp.md) | 12 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [include/crown/resource/allocator.hpp](files/include/crown/resource/allocator.hpp.md) | 20 | Fund native owners and nested storage from one finite requested-byte account. |
| [include/crown/resource/memory.hpp](files/include/crown/resource/memory.hpp.md) | 19 | Fund native owners and nested storage from one finite requested-byte account. |
| [include/crown/resource/owner_allocator.hpp](files/include/crown/resource/owner_allocator.hpp.md) | 3 | Fund native owners and nested storage from one finite requested-byte account. |
| [include/crown/resource/owner_text.hpp](files/include/crown/resource/owner_text.hpp.md) | 4 | Fund native owners and nested storage from one finite requested-byte account. |
| [include/crown/resource/ownership.hpp](files/include/crown/resource/ownership.hpp.md) | 9 | Fund native owners and nested storage from one finite requested-byte account. |
| [include/crown/resource/text.hpp](files/include/crown/resource/text.hpp.md) | 23 | Fund native owners and nested storage from one finite requested-byte account. |
| [include/crown/runtime/aggregate.hpp](files/include/crown/runtime/aggregate.hpp.md) | 25 | Declare nullable owning aggregate tuples, grouped state, atomic prepared batches and owning output. |
| [include/crown/runtime/combined_statistics.hpp](files/include/crown/runtime/combined_statistics.hpp.md) | 17 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [include/crown/runtime/comparisons.hpp](files/include/crown/runtime/comparisons.hpp.md) | 12 | Declare exact comparison binding, finite recomputation grants, owning snapshots and atomic endpoint set deltas. |
| [include/crown/runtime/delta.hpp](files/include/crown/runtime/delta.hpp.md) | 33 | Maintain live visible-factor indexes, canonical delta producers and retained delivery epochs. |
| [include/crown/runtime/difference.hpp](files/include/crown/runtime/difference.hpp.md) | 16 | Declare independent exact difference ownership, compressed checked counts and exact endpoint replacements distinct from aggregate payloads. |
| [include/crown/runtime/fallback.hpp](files/include/crown/runtime/fallback.hpp.md) | 12 | Declare finite independent exact fallback ownership, owning snapshots, atomic endpoint deltas and explicit materialization costs. |
| [include/crown/runtime/initialization.hpp](files/include/crown/runtime/initialization.hpp.md) | 19 | Compose one full physical source update across all its aliases into one atomic logical support epoch. |
| [include/crown/runtime/inspection.hpp](files/include/crown/runtime/inspection.hpp.md) | 44 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [include/crown/runtime/maintenance_cost.hpp](files/include/crown/runtime/maintenance_cost.hpp.md) | 59 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [include/crown/runtime/memory_report.hpp](files/include/crown/runtime/memory_report.hpp.md) | 35 | Capture/reconcile account allocation partitions with logical runtime ownership. |
| [include/crown/runtime/observation.hpp](files/include/crown/runtime/observation.hpp.md) | 98 | Collect optional counters/traces/clocks while preserving measured-zero versus unavailable fields. |
| [include/crown/runtime/owner_statistics.hpp](files/include/crown/runtime/owner_statistics.hpp.md) | 37 | Capture selected table/index distributions with owner/sequence stamps and partial-completion status. |
| [include/crown/runtime/physical.hpp](files/include/crown/runtime/physical.hpp.md) | 102 | Compose one full physical source update across all its aliases into one atomic logical support epoch. |
| [include/crown/runtime/program.hpp](files/include/crown/runtime/program.hpp.md) | 1 | Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs. |
| [include/crown/runtime/program_aliases.hpp](files/include/crown/runtime/program_aliases.hpp.md) | 1 | Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs. |
| [include/crown/runtime/program_json.hpp](files/include/crown/runtime/program_json.hpp.md) | 1 | Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs. |
| [include/crown/runtime/program_model.hpp](files/include/crown/runtime/program_model.hpp.md) | 1 | Define account-funded native equivalents of compiler metadata. |
| [include/crown/runtime/program_span.hpp](files/include/crown/runtime/program_span.hpp.md) | 1 | Expose borrowed spans into immutable native program storage. |
| [include/crown/runtime/queries.hpp](files/include/crown/runtime/queries.hpp.md) | 6 | Maintain Boolean CROWN record/survivor/projected-support state and enumerate current answers from factorized visible relations. |
| [include/crown/runtime/ranking_evidence.hpp](files/include/crown/runtime/ranking_evidence.hpp.md) | 34 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [include/crown/runtime/reoptimization.hpp](files/include/crown/runtime/reoptimization.hpp.md) | 52 | Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary. |
| [include/crown/runtime/replay.hpp](files/include/crown/runtime/replay.hpp.md) | 16 | Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary. |
| [include/crown/runtime/selection.hpp](files/include/crown/runtime/selection.hpp.md) | 29 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [include/crown/runtime/session.hpp](files/include/crown/runtime/session.hpp.md) | 169 | Own input-to-output and durable lifecycle transitions for one creator-thread query session. |
| [include/crown/runtime/session_checkpoint.hpp](files/include/crown/runtime/session_checkpoint.hpp.md) | 13 | Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary. |
| [include/crown/runtime/session_generation.hpp](files/include/crown/runtime/session_generation.hpp.md) | 5 | Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary. |
| [include/crown/runtime/session_journal.hpp](files/include/crown/runtime/session_journal.hpp.md) | 15 | Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary. |
| [include/crown/runtime/session_local_sink.hpp](files/include/crown/runtime/session_local_sink.hpp.md) | 6 | Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary. |
| [include/crown/runtime/session_reoptimization.hpp](files/include/crown/runtime/session_reoptimization.hpp.md) | 15 | Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary. |
| [include/crown/runtime/source_image.hpp](files/include/crown/runtime/source_image.hpp.md) | 5 | Declare deep accounted current or prepared physical source images with explicit row and work grants and no checkpoint authority. |
| [include/crown/runtime/sql_aggregate.hpp](files/include/crown/runtime/sql_aggregate.hpp.md) | 15 | Declare genuine physical-source aggregate ownership, prepared batches and owning output. |
| [include/crown/runtime/sql_rows.hpp](files/include/crown/runtime/sql_rows.hpp.md) | 27 | Maintain Boolean CROWN record/survivor/projected-support state and enumerate current answers from factorized visible relations. |
| [include/crown/runtime/star.hpp](files/include/crown/runtime/star.hpp.md) | 13 | Declare finite star ownership, atomic maintenance, exact snapshot cursors and honest work/degree/label gauges. |
| [include/crown/runtime/statistics.hpp](files/include/crown/runtime/statistics.hpp.md) | 60 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [include/crown/runtime/support.hpp](files/include/crown/runtime/support.hpp.md) | 57 | Maintain record/S/P/E support state and current/epoch cursor leases. |
| [include/crown/runtime/topk.hpp](files/include/crown/runtime/topk.hpp.md) | 12 | Declare exact snapshot rank keys, compressed result identity, finite grants and SQL runtime overloads. |
| [include/crown/runtime/update_pattern.hpp](files/include/crown/runtime/update_pattern.hpp.md) | 10 | Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary. |
| [include/crown/runtime/update_view.hpp](files/include/crown/runtime/update_view.hpp.md) | 8 | Compose one full physical source update across all its aliases into one atomic logical support epoch. |
| [include/crown/runtime/weighted.hpp](files/include/crown/runtime/weighted.hpp.md) | 52 | Execute weighted logical replacements and projected tuple/multiplicity enumeration with separate full messages, local visible factors and compact undo. |
| [include/crown/runtime/window.hpp](files/include/crown/runtime/window.hpp.md) | 68 | Maintain operational event-time/FIFO membership and prepared expiration transitions. |
| [include/crown/runtime/workload_statistics.hpp](files/include/crown/runtime/workload_statistics.hpp.md) | 55 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [include/crown/storage/accounted_arena.hpp](files/include/crown/storage/accounted_arena.hpp.md) | 9 | Keep stable tuple handles and retained deleted payloads for live readers and inverse operations. |
| [include/crown/storage/accounted_index_work.hpp](files/include/crown/storage/accounted_index_work.hpp.md) | 13 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [include/crown/storage/accounted_indexed.hpp](files/include/crown/storage/accounted_indexed.hpp.md) | 15 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [include/crown/storage/accounted_layout.hpp](files/include/crown/storage/accounted_layout.hpp.md) | 32 | Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries. |
| [include/crown/storage/accounted_plan.hpp](files/include/crown/storage/accounted_plan.hpp.md) | 19 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [include/crown/storage/accounted_projection.hpp](files/include/crown/storage/accounted_projection.hpp.md) | 13 | Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries. |
| [include/crown/storage/accounted_reference.hpp](files/include/crown/storage/accounted_reference.hpp.md) | 14 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [include/crown/storage/accounted_row.hpp](files/include/crown/storage/accounted_row.hpp.md) | 26 | Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries. |
| [include/crown/storage/accounted_table.hpp](files/include/crown/storage/accounted_table.hpp.md) | 12 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [include/crown/storage/arena.hpp](files/include/crown/storage/arena.hpp.md) | 5 | Keep stable tuple handles and retained deleted payloads for live readers and inverse operations. |
| [include/crown/storage/backend.hpp](files/include/crown/storage/backend.hpp.md) | 7 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [include/crown/storage/index_failure.hpp](files/include/crown/storage/index_failure.hpp.md) | 10 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [include/crown/storage/index_work.hpp](files/include/crown/storage/index_work.hpp.md) | 13 | Admit every work dimension atomically from one noncopyable operation balance. |
| [include/crown/storage/indexed.hpp](files/include/crown/storage/indexed.hpp.md) | 16 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [include/crown/storage/layout.hpp](files/include/crown/storage/layout.hpp.md) | 16 | Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries. |
| [include/crown/storage/physical.hpp](files/include/crown/storage/physical.hpp.md) | 3 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [include/crown/storage/plan.hpp](files/include/crown/storage/plan.hpp.md) | 3 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [include/crown/storage/reference.hpp](files/include/crown/storage/reference.hpp.md) | 13 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [include/crown/storage/table.hpp](files/include/crown/storage/table.hpp.md) | 13 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [include/crown/storage/table_types.hpp](files/include/crown/storage/table_types.hpp.md) | 3 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [include/crown/storage/tuple_values.hpp](files/include/crown/storage/tuple_values.hpp.md) | 18 | Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries. |
| [include/crown/version.hpp](files/include/crown/version.hpp.md) | 1 | Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs. |
| [src/annotations/policy.cpp](files/src/annotations/policy.cpp.md) | 37 | Admit W01 annotation policies and implement exact bounded support/aggregate arithmetic. |
| [src/catalog/catalog.cpp](files/src/catalog/catalog.cpp.md) | 25 | Validate schema, table/column identity and declared integrity constraints before query or data admission. |
| [src/frontend/adapter.cpp](files/src/frontend/adapter.cpp.md) | 6 | Apply occurrence-local constants/repeated-variable tests and positional projection. |
| [src/frontend/admission.cpp](files/src/frontend/admission.cpp.md) | 7 | Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics. |
| [src/frontend/aggregate.cpp](files/src/frontend/aggregate.cpp.md) | 45 | Bind admitted aggregate SQL into exact typed grouping, COUNT/SUM/AVG measures and immutable cast guards. |
| [src/frontend/bind.cpp](files/src/frontend/bind.cpp.md) | 45 | Resolve table/column aliases, expressions and exact typed literals against catalog metadata. |
| [src/frontend/normalize.cpp](files/src/frontend/normalize.cpp.md) | 32 | Normalize bound equality predicates, contradictions and SQL output semantics into a typed CQ. |
| [src/frontend/parser.cpp](files/src/frontend/parser.cpp.md) | 13 | Own the libpg_query parse result and expose the admitted parser representation. |
| [src/frontend/parser_detail.hpp](files/src/frontend/parser_detail.hpp.md) | 1 | Share one internal parser/deparser mutex across cold JSON/protobuf frontend calls. |
| [src/frontend/sql_aggregate.cpp](files/src/frontend/sql_aggregate.cpp.md) | 52 | Derive admitted source/kernel SQL through genuine binders, preserving physical grouping identity and checked foreign-AST lifetimes. |
| [src/frontend/sql_rows.cpp](files/src/frontend/sql_rows.cpp.md) | 57 | Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics. |
| [src/frontend/sql_rows_eval.hpp](files/src/frontend/sql_rows_eval.hpp.md) | 8 | Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics. |
| [src/frontend/sql_rows_value.hpp](files/src/frontend/sql_rows_value.hpp.md) | 8 | Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics. |
| [src/frontend/sql_scalar.hpp](files/src/frontend/sql_scalar.hpp.md) | 14 | Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics. |
| [src/io/admission.cpp](files/src/io/admission.cpp.md) | 8 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/batch.cpp](files/src/io/batch.cpp.md) | 53 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/batch_program.cpp](files/src/io/batch_program.cpp.md) | 5 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/binding.cpp](files/src/io/binding.cpp.md) | 12 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/candidates.cpp](files/src/io/candidates.cpp.md) | 19 | Retain and enumerate checked minimum-height candidate alternatives under bounded content budgets. |
| [src/io/catalog.cpp](files/src/io/catalog.cpp.md) | 12 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/catalog_source.hpp](files/src/io/catalog_source.hpp.md) | 3 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/checkpoint_detail.hpp](files/src/io/checkpoint_detail.hpp.md) | 15 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/compiler_plan_artifact.cpp](files/src/io/compiler_plan_artifact.cpp.md) | 10 | Read/write explicit compiler-owned plan artifacts at the native admission boundary. |
| [src/io/cursor_observation.cpp](files/src/io/cursor_observation.cpp.md) | 40 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/document.cpp](files/src/io/document.cpp.md) | 33 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/event_reader.cpp](files/src/io/event_reader.cpp.md) | 50 | Decode bounded stream records into funded native updates while retaining input progress. |
| [src/io/explain.cpp](files/src/io/explain.cpp.md) | 82 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/identity.cpp](files/src/io/identity.cpp.md) | 23 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/ingest.cpp](files/src/io/ingest.cpp.md) | 69 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/ingest_program.cpp](files/src/io/ingest_program.cpp.md) | 9 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/ingest_text.cpp](files/src/io/ingest_text.cpp.md) | 6 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/ingest_text.hpp](files/src/io/ingest_text.hpp.md) | 1 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/input_native.hpp](files/src/io/input_native.hpp.md) | 12 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/input_options.cpp](files/src/io/input_options.cpp.md) | 13 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/input_progress.cpp](files/src/io/input_progress.cpp.md) | 26 | Track exact resumable record/source position independently of runtime/output sequence. |
| [src/io/input_view.cpp](files/src/io/input_view.cpp.md) | 25 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/inspection.cpp](files/src/io/inspection.cpp.md) | 31 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/json.hpp](files/src/io/json.hpp.md) | 11 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/layout.cpp](files/src/io/layout.cpp.md) | 9 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/memory_report.cpp](files/src/io/memory_report.cpp.md) | 20 | Serialize a retained native memory report into ordinary JSON without rescanning live accounts/tables. |
| [src/io/native_decode.cpp](files/src/io/native_decode.cpp.md) | 38 | Parse exact scalar fields directly into compact native values. |
| [src/io/native_input.hpp](files/src/io/native_input.hpp.md) | 21 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/normalization.cpp](files/src/io/normalization.cpp.md) | 15 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/physical.cpp](files/src/io/physical.cpp.md) | 28 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/query_binding.hpp](files/src/io/query_binding.hpp.md) | 3 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/query_explain.cpp](files/src/io/query_explain.cpp.md) | 50 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/recognition.cpp](files/src/io/recognition.cpp.md) | 5 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/residual.cpp](files/src/io/residual.cpp.md) | 41 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/run_context.cpp](files/src/io/run_context.cpp.md) | 36 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/search.cpp](files/src/io/search.cpp.md) | 17 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/sql.cpp](files/src/io/sql.cpp.md) | 4 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/sql_aggregate_input.cpp](files/src/io/sql_aggregate_input.cpp.md) | 21 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/statistics_explain.cpp](files/src/io/statistics_explain.cpp.md) | 75 | Admit bounded external documents/records and serialize explicit public representations at the engine boundary. |
| [src/io/support.cpp](files/src/io/support.cpp.md) | 30 | Parse logical-support diagnostic Rows and serialize retained support state/journals without applying updates. |
| [src/ir/digest.cpp](files/src/ir/digest.cpp.md) | 6 | Compute and encode canonical SHA-256 digests used for artifact identity. |
| [src/ir/input_program.hpp](files/src/ir/input_program.hpp.md) | 16 | Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs. |
| [src/ir/model.cpp](files/src/ir/model.cpp.md) | 25 | Define/validate query variables, atom occurrences, scopes and output metadata. |
| [src/ir/program.cpp](files/src/ir/program.cpp.md) | 172 | Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs. |
| [src/ir/program_native_types.inc](files/src/ir/program_native_types.inc.md) | 41 | Import/export native compiler metadata using the receiving account. |
| [src/ir/program_replan.inc](files/src/ir/program_replan.inc.md) | 25 | Rebind and lower checked candidates into native metadata without retaining an ordinary DTO graph. |
| [src/ir/scalar.cpp](files/src/ir/scalar.cpp.md) | 10 | Parse, compare, hash and format exact scalar DTO values. |
| [src/ir/update_pattern.cpp](files/src/ir/update_pattern.cpp.md) | 25 | Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs. |
| [src/ir/update_pattern_detail.hpp](files/src/ir/update_pattern_detail.hpp.md) | 8 | Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs. |
| [src/observability/explain.cpp](files/src/observability/explain.cpp.md) | 58 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/observability/query_explain.cpp](files/src/observability/query_explain.cpp.md) | 29 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/observability/statistics_explain.cpp](files/src/observability/statistics_explain.cpp.md) | 21 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/planner/candidate_binding.hpp](files/src/planner/candidate_binding.hpp.md) | 38 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [src/planner/candidate_generator.cpp](files/src/planner/candidate_generator.cpp.md) | 39 | Enumerate candidate tree structures with an explicit generator frontier. |
| [src/planner/candidate_key.cpp](files/src/planner/candidate_key.cpp.md) | 29 | Compute canonical candidate identity through a bounded resumable key machine. |
| [src/planner/candidate_key.hpp](files/src/planner/candidate_key.hpp.md) | 7 | Compute canonical candidate identity through a bounded resumable key machine. |
| [src/planner/candidate_machine.hpp](files/src/planner/candidate_machine.hpp.md) | 13 | Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims. |
| [src/planner/candidates.cpp](files/src/planner/candidates.cpp.md) | 84 | Retain and enumerate checked minimum-height candidate alternatives under bounded content budgets. |
| [src/planner/certificate.cpp](files/src/planner/certificate.cpp.md) | 60 | Replay retained lower-bound evidence independently of search continuation state. |
| [src/planner/comparisons.cpp](files/src/planner/comparisons.cpp.md) | 12 | Check operator/variable/type and literal-byte admission while preserving the original equality query and plan authority. |
| [src/planner/compiled_source.cpp](files/src/planner/compiled_source.cpp.md) | 21 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [src/planner/compiled_source.hpp](files/src/planner/compiled_source.hpp.md) | 57 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [src/planner/continuation_budget.hpp](files/src/planner/continuation_budget.hpp.md) | 14 | Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims. |
| [src/planner/continuation_machine.hpp](files/src/planner/continuation_machine.hpp.md) | 21 | Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims. |
| [src/planner/difference.cpp](files/src/planner/difference.cpp.md) | 13 | Admit both original operands over the same catalog and check ordered output types without subtracting unrelated upper bounds. |
| [src/planner/exact.cpp](files/src/planner/exact.cpp.md) | 93 | Implement the local finite partition recurrence/search machine for exact native-height optimization. |
| [src/planner/fallback.cpp](files/src/planner/fallback.cpp.md) | 17 | Bound cold metadata work, recognize the original query and lower a full-catalog source-only coordinator without claiming a CROWN or GHD certificate. |
| [src/planner/fast_paths.cpp](files/src/planner/fast_paths.cpp.md) | 1 | Retain source-list compatibility while fast-path continuation implementation is owned by search_session.cpp. |
| [src/planner/fast_paths.hpp](files/src/planner/fast_paths.hpp.md) | 1 | Retain source-list compatibility while fast-path continuation implementation is owned by search_session.cpp. |
| [src/planner/keys.cpp](files/src/planner/keys.cpp.md) | 25 | Prove sequential enforced-FK parent elimination, compact query IDs and lower a separately certified reduced plan without changing the source constraint owner. |
| [src/planner/lower.cpp](files/src/planner/lower.cpp.md) | 71 | Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata. |
| [src/planner/meta.cpp](files/src/planner/meta.cpp.md) | 16 | Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata. |
| [src/planner/meta_candidates.cpp](files/src/planner/meta_candidates.cpp.md) | 38 | Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims. |
| [src/planner/meta_join_trees.cpp](files/src/planner/meta_join_trees.cpp.md) | 27 | Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata. |
| [src/planner/native_physical_binding.hpp](files/src/planner/native_physical_binding.hpp.md) | 18 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [src/planner/producer_cursor.hpp](files/src/planner/producer_cursor.hpp.md) | 20 | Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims. |
| [src/planner/ranking.cpp](files/src/planner/ranking.cpp.md) | 51 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [src/planner/ranking_detail.hpp](files/src/planner/ranking_detail.hpp.md) | 31 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [src/planner/ranking_integer.cpp](files/src/planner/ranking_integer.cpp.md) | 14 | Perform bounded exact integer score arithmetic without floating-point ordering changes. |
| [src/planner/ranking_payload.cpp](files/src/planner/ranking_payload.cpp.md) | 28 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [src/planner/ranking_payload.hpp](files/src/planner/ranking_payload.hpp.md) | 5 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [src/planner/recognize.cpp](files/src/planner/recognize.cpp.md) | 12 | Run GYO reduction for body and augmented-head hypergraphs; distinguish free-connex, acyclic non-free-connex and cyclic cases. |
| [src/planner/residual.cpp](files/src/planner/residual.cpp.md) | 55 | Generate and replay residual-reduction/reconstruction candidates as a structural aid to the exact planner. |
| [src/planner/residual_machine.hpp](files/src/planner/residual_machine.hpp.md) | 14 | Generate and replay residual-reduction/reconstruction candidates as a structural aid to the exact planner. |
| [src/planner/residual_reconstruct.cpp](files/src/planner/residual_reconstruct.cpp.md) | 34 | Reconstruct and check candidate trees, retaining the exact-repair boundary for counterexamples. |
| [src/planner/residual_reduce.cpp](files/src/planner/residual_reduce.cpp.md) | 17 | Build residual reduction traces from query scopes and output structure. |
| [src/planner/residual_trace.cpp](files/src/planner/residual_trace.cpp.md) | 23 | Replay and validate each claimed reduction step against the source query. |
| [src/planner/residual_view.cpp](files/src/planner/residual_view.cpp.md) | 12 | Generate and replay residual-reduction/reconstruction candidates as a structural aid to the exact planner. |
| [src/planner/search_budget.hpp](files/src/planner/search_budget.hpp.md) | 8 | Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims. |
| [src/planner/search_session.cpp](files/src/planner/search_session.cpp.md) | 141 | Advance a resumable exact/fast-path planner session under explicit transition/depth/time limits. |
| [src/planner/selection.cpp](files/src/planner/selection.cpp.md) | 58 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [src/planner/selection_binding.cpp](files/src/planner/selection_binding.cpp.md) | 60 | Require exact source/query/backend binding before admitting cached or candidate plan authority. |
| [src/planner/selection_budget.cpp](files/src/planner/selection_budget.cpp.md) | 39 | Account selection work/resources/timing and translate component stop reasons. |
| [src/planner/selection_cache.cpp](files/src/planner/selection_cache.cpp.md) | 20 | Manage bounded FIFO plan entries while retaining each entry's allocating account. |
| [src/planner/selection_detail.hpp](files/src/planner/selection_detail.hpp.md) | 47 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [src/planner/selection_payload.cpp](files/src/planner/selection_payload.cpp.md) | 25 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [src/planner/star.cpp](files/src/planner/star.cpp.md) | 16 | Check center/satellite/head structure and lower a full-catalog source coordinator with no generic occurrence routes. |
| [src/planner/update_pattern.cpp](files/src/planner/update_pattern.cpp.md) | 20 | Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata. |
| [src/planner/update_pattern_detail.hpp](files/src/planner/update_pattern_detail.hpp.md) | 3 | Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata. |
| [src/planner/verify.cpp](files/src/planner/verify.cpp.md) | 81 | Independently validate CROWN tree coverage, guard, connected-variable paths, connex output structure and height claims. |
| [src/recovery/binary_detail.hpp](files/src/recovery/binary_detail.hpp.md) | 19 | Encode/decode bounded fixed-width/versioned recovery fields and exact scalar payloads. |
| [src/recovery/generation.cpp](files/src/recovery/generation.cpp.md) | 41 | Read/publish durable generation roots with exact identity and selection outcome. |
| [src/recovery/generation_detail.hpp](files/src/recovery/generation_detail.hpp.md) | 30 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/generation_retirement.cpp](files/src/recovery/generation_retirement.cpp.md) | 22 | Retire only history authorized by durable root/delivery state. |
| [src/recovery/image.cpp](files/src/recovery/image.cpp.md) | 11 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/journal.cpp](files/src/recovery/journal.cpp.md) | 43 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/journal_file.cpp](files/src/recovery/journal_file.cpp.md) | 32 | Own locked WAL descriptors, validate prefix state and poison uncertain append attempts. |
| [src/recovery/local_sink.cpp](files/src/recovery/local_sink.cpp.md) | 42 | Persist canonical complete epoch output and return authority-bearing delivery receipts. |
| [src/recovery/local_sink_codec.cpp](files/src/recovery/local_sink_codec.cpp.md) | 27 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/local_sink_codec.hpp](files/src/recovery/local_sink_codec.hpp.md) | 8 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/plan_descriptor.cpp](files/src/recovery/plan_descriptor.cpp.md) | 24 | Encode/decode exact selected-plan descriptor identity for generation recovery. |
| [src/recovery/session_file.cpp](files/src/recovery/session_file.cpp.md) | 23 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/session_file_detail.hpp](files/src/recovery/session_file_detail.hpp.md) | 11 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/session_image.cpp](files/src/recovery/session_image.cpp.md) | 48 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/session_image_detail.hpp](files/src/recovery/session_image_detail.hpp.md) | 8 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/session_pattern_wire.hpp](files/src/recovery/session_pattern_wire.hpp.md) | 16 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_aggregate_cbor.hpp](files/src/recovery/sql_aggregate_cbor.hpp.md) | 8 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_aggregate_checkpoint.cpp](files/src/recovery/sql_aggregate_checkpoint.cpp.md) | 29 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_aggregate_descriptor.cpp](files/src/recovery/sql_aggregate_descriptor.cpp.md) | 30 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_aggregate_file_detail.cpp](files/src/recovery/sql_aggregate_file_detail.cpp.md) | 39 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_aggregate_file_detail.hpp](files/src/recovery/sql_aggregate_file_detail.hpp.md) | 12 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_aggregate_records.cpp](files/src/recovery/sql_aggregate_records.cpp.md) | 49 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_aggregate_session.cpp](files/src/recovery/sql_aggregate_session.cpp.md) | 37 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_aggregate_session_detail.hpp](files/src/recovery/sql_aggregate_session_detail.hpp.md) | 6 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_aggregate_session_replay.cpp](files/src/recovery/sql_aggregate_session_replay.cpp.md) | 5 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_aggregate_sink_file.cpp](files/src/recovery/sql_aggregate_sink_file.cpp.md) | 25 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_aggregate_wal.cpp](files/src/recovery/sql_aggregate_wal.cpp.md) | 3 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_aggregate_wal_file.cpp](files/src/recovery/sql_aggregate_wal_file.cpp.md) | 15 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_rows_cbor.hpp](files/src/recovery/sql_rows_cbor.hpp.md) | 1 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_rows_checkpoint.cpp](files/src/recovery/sql_rows_checkpoint.cpp.md) | 29 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_rows_descriptor.cpp](files/src/recovery/sql_rows_descriptor.cpp.md) | 31 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_rows_file_detail.hpp](files/src/recovery/sql_rows_file_detail.hpp.md) | 3 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_rows_records.cpp](files/src/recovery/sql_rows_records.cpp.md) | 51 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_rows_session.cpp](files/src/recovery/sql_rows_session.cpp.md) | 37 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_rows_session_detail.hpp](files/src/recovery/sql_rows_session_detail.hpp.md) | 6 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_rows_session_replay.cpp](files/src/recovery/sql_rows_session_replay.cpp.md) | 5 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_rows_sink_file.cpp](files/src/recovery/sql_rows_sink_file.cpp.md) | 25 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_rows_wal.cpp](files/src/recovery/sql_rows_wal.cpp.md) | 3 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/recovery/sql_rows_wal_file.cpp](files/src/recovery/sql_rows_wal_file.cpp.md) | 15 | Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority. |
| [src/resource/memory.cpp](files/src/resource/memory.cpp.md) | 50 | Fund native owners and nested storage from one finite requested-byte account. |
| [src/runtime/accounted_ordered_rows.hpp](files/src/runtime/accounted_ordered_rows.hpp.md) | 115 | Own ordered row-set/map nodes with exact allocation ownership and nonallocating extraction/reinsertion. |
| [src/runtime/aggregate.cpp](files/src/runtime/aggregate.cpp.md) | 68 | Maintain accounted logical input-row multiplicities and exact COUNT/SUM/AVG group proposals through one prepared aggregate batch. |
| [src/runtime/aggregate_detail.hpp](files/src/runtime/aggregate_detail.hpp.md) | 34 | Share exact aggregate validation, arithmetic and rendering between runtimes. |
| [src/runtime/aggregate_integer.hpp](files/src/runtime/aggregate_integer.hpp.md) | 25 | Provide fixed-width exact integer products, signed accumulators and decimal rounding for aggregate arithmetic. |
| [src/runtime/aggregate_tuple.cpp](files/src/runtime/aggregate_tuple.cpp.md) | 11 | Own nullable aggregate tuple cells and copied text with accounted payloads and borrowed read-only views. |
| [src/runtime/checkpoint_policy.hpp](files/src/runtime/checkpoint_policy.hpp.md) | 8 | Turn private physical/support prefixes into exact duplicate-free query answer additions/deletions with explicit producer and delivery policies. |
| [src/runtime/combined_statistics.cpp](files/src/runtime/combined_statistics.cpp.md) | 13 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/runtime/comparisons.cpp](files/src/runtime/comparisons.cpp.md) | 42 | Reuse ordinary propagation and full hidden-variable assignments, filter before projection, deduplicate and publish prepaid source/result state. |
| [src/runtime/constraint_validation.hpp](files/src/runtime/constraint_validation.hpp.md) | 9 | Validate complete native proposed source snapshots and enforced constraints under the query account. |
| [src/runtime/cq_recompute.hpp](files/src/runtime/cq_recompute.hpp.md) | 8 | Share original-account native query freezing and iterative witness traversal with borrowed callbacks and caller-selected consolidation. |
| [src/runtime/delta.cpp](files/src/runtime/delta.cpp.md) | 216 | Maintain live visible-factor indexes, canonical delta producers and retained delivery epochs. |
| [src/runtime/difference.cpp](files/src/runtime/difference.cpp.md) | 47 | Recompute both positive operands from one funded source image, consolidate set/bag residuals and publish prepared endpoint counts atomically. |
| [src/runtime/fallback.cpp](files/src/runtime/fallback.cpp.md) | 43 | Capture funded physical source images, enumerate complete assignments iteratively, project and deduplicate privately, then publish prepaid source/result state. |
| [src/runtime/inspection_detail.hpp](files/src/runtime/inspection_detail.hpp.md) | 15 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/runtime/maintenance_cost.cpp](files/src/runtime/maintenance_cost.cpp.md) | 63 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/runtime/memory_report.cpp](files/src/runtime/memory_report.cpp.md) | 30 | Capture/reconcile account allocation partitions with logical runtime ownership. |
| [src/runtime/memory_report_detail.hpp](files/src/runtime/memory_report_detail.hpp.md) | 19 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/runtime/native_statistics.cpp](files/src/runtime/native_statistics.cpp.md) | 26 | Build bounded native distributions using borrowed compact rows and shared storage work. |
| [src/runtime/observation.cpp](files/src/runtime/observation.cpp.md) | 34 | Collect optional counters/traces/clocks while preserving measured-zero versus unavailable fields. |
| [src/runtime/owner_statistics.cpp](files/src/runtime/owner_statistics.cpp.md) | 14 | Capture selected table/index distributions with owner/sequence stamps and partial-completion status. |
| [src/runtime/owner_statistics_detail.hpp](files/src/runtime/owner_statistics_detail.hpp.md) | 6 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/runtime/physical.cpp](files/src/runtime/physical.cpp.md) | 150 | Compose one full physical source update across all its aliases into one atomic logical support epoch. |
| [src/runtime/queries.cpp](files/src/runtime/queries.cpp.md) | 12 | Maintain Boolean CROWN record/survivor/projected-support state and enumerate current answers from factorized visible relations. |
| [src/runtime/ranking_evidence.cpp](files/src/runtime/ranking_evidence.cpp.md) | 49 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/runtime/ranking_evidence_detail.hpp](files/src/runtime/ranking_evidence_detail.hpp.md) | 3 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/runtime/reoptimization.cpp](files/src/runtime/reoptimization.cpp.md) | 32 | Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary. |
| [src/runtime/reoptimization_detail.hpp](files/src/runtime/reoptimization_detail.hpp.md) | 24 | Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary. |
| [src/runtime/replay.cpp](files/src/runtime/replay.cpp.md) | 14 | Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary. |
| [src/runtime/selection.cpp](files/src/runtime/selection.cpp.md) | 30 | Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies. |
| [src/runtime/session.cpp](files/src/runtime/session.cpp.md) | 207 | Own input-to-output and durable lifecycle transitions for one creator-thread query session. |
| [src/runtime/sql_aggregate.cpp](files/src/runtime/sql_aggregate.cpp.md) | 49 | Maintain touched group statistics from one private authentic source batch. |
| [src/runtime/sql_cold_rebuild.hpp](files/src/runtime/sql_cold_rebuild.hpp.md) | 3 | Declare the concrete private bridge for unpublished genuine SQL cold reconstruction. |
| [src/runtime/sql_rows.cpp](files/src/runtime/sql_rows.cpp.md) | 103 | Maintain Boolean CROWN record/survivor/projected-support state and enumerate current answers from factorized visible relations. |
| [src/runtime/star.cpp](files/src/runtime/star.cpp.md) | 35 | Maintain light-filtered groups, heavy predicates, exact degrees and sparse hysteretic migrations beside full original source validation. |
| [src/runtime/star_cursor.cpp](files/src/runtime/star_cursor.cpp.md) | 18 | Pace live-group projection candidates, deduplicate borrowed keys and return original-account owning outputs under a read lease. |
| [src/runtime/star_detail.hpp](files/src/runtime/star_detail.hpp.md) | 32 | Own accounted star records, sparse degree links, per-group projections and touched-record inverse journal primitives. |
| [src/runtime/star_hindex.hpp](files/src/runtime/star_hindex.hpp.md) | 38 | Track exact generalized H using occupied degree frequencies, two suffix counts and private allocation-free publication. |
| [src/runtime/statistics.cpp](files/src/runtime/statistics.cpp.md) | 31 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/runtime/statistics_collection.cpp](files/src/runtime/statistics_collection.cpp.md) | 32 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/runtime/statistics_collection.hpp](files/src/runtime/statistics_collection.hpp.md) | 41 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/runtime/storage_work.hpp](files/src/runtime/storage_work.hpp.md) | 33 | Create a finite grant only for an outer indexed operation; retain/rebind it across nested and resumed work. |
| [src/runtime/support.cpp](files/src/runtime/support.cpp.md) | 244 | Maintain record/S/P/E support state and current/epoch cursor leases. |
| [src/runtime/topk.cpp](files/src/runtime/topk.cpp.md) | 17 | Collect genuine SQL outputs, sort by explicit keys and identity, and return a compact exact prefix without query-update state. |
| [src/runtime/update_pattern_detail.hpp](files/src/runtime/update_pattern_detail.hpp.md) | 5 | Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary. |
| [src/runtime/validation_work.hpp](files/src/runtime/validation_work.hpp.md) | 6 | Compose one full physical source update across all its aliases into one atomic logical support epoch. |
| [src/runtime/weighted.cpp](files/src/runtime/weighted.cpp.md) | 107 | Execute weighted logical replacements and projected tuple/multiplicity enumeration with separate full messages, local visible factors and compact undo. |
| [src/runtime/weighted_cursor.cpp](files/src/runtime/weighted_cursor.cpp.md) | 31 | Maintain exact full-subtree messages and local visible factors, then enumerate projected core tuples with multiplicities. |
| [src/runtime/weighted_delta_detail.hpp](files/src/runtime/weighted_delta_detail.hpp.md) | 12 | Maintain exact full-subtree messages and local visible factors, then enumerate projected core tuples with multiplicities. |
| [src/runtime/weighted_detail.hpp](files/src/runtime/weighted_detail.hpp.md) | 7 | Maintain exact full-subtree messages and local visible factors, then enumerate projected core tuples with multiplicities. |
| [src/runtime/window.cpp](files/src/runtime/window.cpp.md) | 58 | Maintain operational event-time/FIFO membership and prepared expiration transitions. |
| [src/runtime/workload_statistics.cpp](files/src/runtime/workload_statistics.cpp.md) | 50 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/runtime/workload_statistics_detail.hpp](files/src/runtime/workload_statistics_detail.hpp.md) | 23 | Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact. |
| [src/storage/accounted_arena.cpp](files/src/storage/accounted_arena.cpp.md) | 53 | Keep stable tuple handles and retained deleted payloads for live readers and inverse operations. |
| [src/storage/accounted_index_scalar_work.hpp](files/src/storage/accounted_index_scalar_work.hpp.md) | 8 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/accounted_indexed.cpp](files/src/storage/accounted_indexed.cpp.md) | 89 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/accounted_indexed_journal.inc](files/src/storage/accounted_indexed_journal.inc.md) | 28 | Record/reverse native indexed mutations using the original account/work grant. |
| [src/storage/accounted_indexed_nodes.hpp](files/src/storage/accounted_indexed_nodes.hpp.md) | 20 | Own native indexed nodes using the exact allocator embedded before destruction. |
| [src/storage/accounted_indexed_testing.hpp](files/src/storage/accounted_indexed_testing.hpp.md) | 8 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/accounted_layout.cpp](files/src/storage/accounted_layout.cpp.md) | 42 | Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries. |
| [src/storage/accounted_plan.cpp](files/src/storage/accounted_plan.cpp.md) | 47 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/accounted_plan_testing.hpp](files/src/storage/accounted_plan_testing.hpp.md) | 4 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/accounted_pointer_array.hpp](files/src/storage/accounted_pointer_array.hpp.md) | 18 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/accounted_projection.cpp](files/src/storage/accounted_projection.cpp.md) | 18 | Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries. |
| [src/storage/accounted_reference.cpp](files/src/storage/accounted_reference.cpp.md) | 103 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/accounted_row.cpp](files/src/storage/accounted_row.cpp.md) | 39 | Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries. |
| [src/storage/accounted_table.cpp](files/src/storage/accounted_table.cpp.md) | 61 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/accounted_table_testing.hpp](files/src/storage/accounted_table_testing.hpp.md) | 4 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/arena.cpp](files/src/storage/arena.cpp.md) | 44 | Keep stable tuple handles and retained deleted payloads for live readers and inverse operations. |
| [src/storage/arena_owner.cpp](files/src/storage/arena_owner.cpp.md) | 3 | Keep stable tuple handles and retained deleted payloads for live readers and inverse operations. |
| [src/storage/arena_owner.hpp](files/src/storage/arena_owner.hpp.md) | 1 | Keep stable tuple handles and retained deleted payloads for live readers and inverse operations. |
| [src/storage/descriptor.hpp](files/src/storage/descriptor.hpp.md) | 6 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/hash_directory.hpp](files/src/storage/hash_directory.hpp.md) | 17 | Provide separately chained stable-node hash lookup and prepared bucket-array growth. |
| [src/storage/index_scalar_work.hpp](files/src/storage/index_scalar_work.hpp.md) | 10 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/index_work_alias.hpp](files/src/storage/index_work_alias.hpp.md) | 4 | Expose different diagnostic policies over the same canonical work balance. |
| [src/storage/indexed.cpp](files/src/storage/indexed.cpp.md) | 92 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/indexed_journal.inc](files/src/storage/indexed_journal.inc.md) | 28 | Record/reverse standalone indexed mutations using prepaid growth, pinned nodes and saved neighbors. |
| [src/storage/indexed_nodes.hpp](files/src/storage/indexed_nodes.hpp.md) | 28 | Define separately owned row/key/member nodes and their directory/live-list hooks. |
| [src/storage/indexed_testing.hpp](files/src/storage/indexed_testing.hpp.md) | 6 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/layout.cpp](files/src/storage/layout.cpp.md) | 44 | Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries. |
| [src/storage/live_list.hpp](files/src/storage/live_list.hpp.md) | 11 | Provide intrusive nonowning membership and O(1) prepaid link/unlink for live traversal. |
| [src/storage/owner.cpp](files/src/storage/owner.cpp.md) | 4 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/owner.hpp](files/src/storage/owner.hpp.md) | 1 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/physical.cpp](files/src/storage/physical.cpp.md) | 10 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/plan.cpp](files/src/storage/plan.cpp.md) | 16 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/reference.cpp](files/src/storage/reference.cpp.md) | 93 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/table.cpp](files/src/storage/table.cpp.md) | 60 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/table_testing.hpp](files/src/storage/table_testing.hpp.md) | 4 | Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations. |
| [src/storage/tuple_payload.hpp](files/src/storage/tuple_payload.hpp.md) | 3 | Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries. |
| [src/storage/tuple_values.cpp](files/src/storage/tuple_values.cpp.md) | 18 | Represent exact typed scalars, rows, layouts and projections at compiler/public/native boundaries. |
| [tests/examples/ranking_usage.cpp](files/tests/examples/ranking_usage.cpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/examples/selection_usage.cpp](files/tests/examples/selection_usage.cpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/admission.py](files/tests/integration/admission.py.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/adversarial_scalability.py](files/tests/integration/adversarial_scalability.py.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/aggregate_integer_oracle.py](files/tests/integration/aggregate_integer_oracle.py.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/aggregate_sql_oracle.py](files/tests/integration/aggregate_sql_oracle.py.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/annotation_arithmetic.py](files/tests/integration/annotation_arithmetic.py.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/baseline_evaluation.py](files/tests/integration/baseline_evaluation.py.md) | 4 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/binding.py](files/tests/integration/binding.py.md) | 33 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/catalog.py](files/tests/integration/catalog.py.md) | 44 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/clean_source_snapshot.py](files/tests/integration/clean_source_snapshot.py.md) | 4 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/cli_process_boundary.py](files/tests/integration/cli_process_boundary.py.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/comparisons_oracle.py](files/tests/integration/comparisons_oracle.py.md) | 16 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/component_analysis.py](files/tests/integration/component_analysis.py.md) | 29 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/component_planning.py](files/tests/integration/component_planning.py.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/component_runtime.py](files/tests/integration/component_runtime.py.md) | 7 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/component_workloads.py](files/tests/integration/component_workloads.py.md) | 14 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/composed_helper_defaults.py](files/tests/integration/composed_helper_defaults.py.md) | 4 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/cost_calibration.py](files/tests/integration/cost_calibration.py.md) | 7 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/difference_oracle.py](files/tests/integration/difference_oracle.py.md) | 25 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/example_output_failure.py](files/tests/integration/example_output_failure.py.md) | 7 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/experimental_report.py](files/tests/integration/experimental_report.py.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/fallback_oracle.py](files/tests/integration/fallback_oracle.py.md) | 18 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/fixtures.py](files/tests/integration/fixtures.py.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/ingest.py](files/tests/integration/ingest.py.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/input_specialization.py](files/tests/integration/input_specialization.py.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/installed_cost_calibration.py](files/tests/integration/installed_cost_calibration.py.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/installed_independent_queries.py](files/tests/integration/installed_independent_queries.py.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/installed_measurement.py](files/tests/integration/installed_measurement.py.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/installed_meta_candidates.py](files/tests/integration/installed_meta_candidates.py.md) | 3 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/installed_ranking_evaluation.py](files/tests/integration/installed_ranking_evaluation.py.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/installed_reoptimization.py](files/tests/integration/installed_reoptimization.py.md) | 4 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/installed_workflow.py](files/tests/integration/installed_workflow.py.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/key_specialization_oracle.py](files/tests/integration/key_specialization_oracle.py.md) | 27 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/legacy_replay_checker.py](files/tests/integration/legacy_replay_checker.py.md) | 4 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/measurement_artifacts.py](files/tests/integration/measurement_artifacts.py.md) | 8 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/measurement_build_provenance.py](files/tests/integration/measurement_build_provenance.py.md) | 4 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/measurement_harness.py](files/tests/integration/measurement_harness.py.md) | 4 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/normalization.py](files/tests/integration/normalization.py.md) | 22 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/operational_evaluation.py](files/tests/integration/operational_evaluation.py.md) | 4 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/parse_sql.py](files/tests/integration/parse_sql.py.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/physical.py](files/tests/integration/physical.py.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/ranking_evaluation.py](files/tests/integration/ranking_evaluation.py.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/release_package.py](files/tests/integration/release_package.py.md) | 19 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/scalars.py](files/tests/integration/scalars.py.md) | 31 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/schema.py](files/tests/integration/schema.py.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/search_evaluation.py](files/tests/integration/search_evaluation.py.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/sql_aggregate_checkpoint_wire.py](files/tests/integration/sql_aggregate_checkpoint_wire.py.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/sql_aggregate_cli.py](files/tests/integration/sql_aggregate_cli.py.md) | 12 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/sql_aggregate_runtime_oracle.py](files/tests/integration/sql_aggregate_runtime_oracle.py.md) | 34 | Compare physical aggregate epochs with independent mature SQL recomputation. |
| [tests/integration/sql_aggregate_transaction_crash.py](files/tests/integration/sql_aggregate_transaction_crash.py.md) | 7 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/sql_rows_oracle.py](files/tests/integration/sql_rows_oracle.py.md) | 25 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/sql_scalar_oracle.py](files/tests/integration/sql_scalar_oracle.py.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/star_oracle.py](files/tests/integration/star_oracle.py.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/support.py](files/tests/integration/support.py.md) | 7 | Exercise support CLI diagnostics against independent manual state and transition expectations. |
| [tests/integration/topk_oracle.py](files/tests/integration/topk_oracle.py.md) | 23 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/tree_oracle.py](files/tests/integration/tree_oracle.py.md) | 21 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/validate_plans.py](files/tests/integration/validate_plans.py.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/weighted_bag.py](files/tests/integration/weighted_bag.py.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/weighted_messages.py](files/tests/integration/weighted_messages.py.md) | 7 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/integration/workflow.py](files/tests/integration/workflow.py.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/observability/cli/native_cli_acceptance.py](files/tests/observability/cli/native_cli_acceptance.py.md) | 43 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/property/reference_fuzz_test.py](files/tests/property/reference_fuzz_test.py.md) | 3 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/recovery/generation/generator.py](files/tests/recovery/generation/generator.py.md) | 3 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/recovery/journal/fixture.py](files/tests/recovery/journal/fixture.py.md) | 21 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/recovery/journal/partial-metadata-fixture.py](files/tests/recovery/journal/partial-metadata-fixture.py.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/recovery/local_sink/generator.py](files/tests/recovery/local_sink/generator.py.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/recovery/reoptimization/generate.py](files/tests/recovery/reoptimization/generate.py.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/recovery/retirement/generator.py](files/tests/recovery/retirement/generator.py.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/recovery/retirement/root-delivery-generator.py](files/tests/recovery/retirement/root-delivery-generator.py.md) | 8 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/recovery/session_image_fixture.py](files/tests/recovery/session_image_fixture.py.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/aggregate_integer_driver.cpp](files/tests/reference/aggregate_integer_driver.cpp.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/aggregate_sql_driver.cpp](files/tests/reference/aggregate_sql_driver.cpp.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/candidate_set.cpp](files/tests/reference/candidate_set.cpp.md) | 28 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/candidate_set.hpp](files/tests/reference/candidate_set.hpp.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/comparisons_driver.cpp](files/tests/reference/comparisons_driver.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/delta_model.cpp](files/tests/reference/delta_model.cpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/delta_model.hpp](files/tests/reference/delta_model.hpp.md) | 8 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/difference_driver.cpp](files/tests/reference/difference_driver.cpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/evaluator.cpp](files/tests/reference/evaluator.cpp.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/evaluator.hpp](files/tests/reference/evaluator.hpp.md) | 3 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/fallback_driver.cpp](files/tests/reference/fallback_driver.cpp.md) | 12 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/key_specialization_driver.cpp](files/tests/reference/key_specialization_driver.cpp.md) | 7 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/native_input.hpp](files/tests/reference/native_input.hpp.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/residual_oracle.cpp](files/tests/reference/residual_oracle.cpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/residual_oracle.hpp](files/tests/reference/residual_oracle.hpp.md) | 1 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/sql_aggregate_runtime_driver.cpp](files/tests/reference/sql_aggregate_runtime_driver.cpp.md) | 14 | Drive authentic physical aggregate batches and export full keys and epochs. |
| [tests/reference/sql_rows_driver.cpp](files/tests/reference/sql_rows_driver.cpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/sql_scalar_driver.cpp](files/tests/reference/sql_scalar_driver.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/star_driver.cpp](files/tests/reference/star_driver.cpp.md) | 7 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/topk_driver.cpp](files/tests/reference/topk_driver.cpp.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/tree_oracle.cpp](files/tests/reference/tree_oracle.cpp.md) | 3 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/tree_oracle.hpp](files/tests/reference/tree_oracle.hpp.md) | 1 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/weighted_bag_oracle.py](files/tests/reference/weighted_bag_oracle.py.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/reference/weighted_oracle.py](files/tests/reference/weighted_oracle.py.md) | 12 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/checkpoint_file_probe.hpp](files/tests/support/checkpoint_file_probe.hpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/frozen_binding_v2.hpp](files/tests/support/frozen_binding_v2.hpp.md) | 22 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/generation_file_probe.hpp](files/tests/support/generation_file_probe.hpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/generation_fixture.hpp](files/tests/support/generation_fixture.hpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/history_retirement_fixture.hpp](files/tests/support/history_retirement_fixture.hpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/index_allocation.hpp](files/tests/support/index_allocation.hpp.md) | 27 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/indexed_runtime_fixture.hpp](files/tests/support/indexed_runtime_fixture.hpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/invariant_fixture.hpp](files/tests/support/invariant_fixture.hpp.md) | 18 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/journal_file_fixture.hpp](files/tests/support/journal_file_fixture.hpp.md) | 19 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/journal_file_probe.hpp](files/tests/support/journal_file_probe.hpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/local_sink_fixture.hpp](files/tests/support/local_sink_fixture.hpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/local_sink_probe.hpp](files/tests/support/local_sink_probe.hpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/planner_baseline_budget.hpp](files/tests/support/planner_baseline_budget.hpp.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/planner_exact_baseline.cpp](files/tests/support/planner_exact_baseline.cpp.md) | 33 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/planner_probe.hpp](files/tests/support/planner_probe.hpp.md) | 1 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/query_families.hpp](files/tests/support/query_families.hpp.md) | 8 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/ranking_exception_support.hpp](files/tests/support/ranking_exception_support.hpp.md) | 18 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/ranking_fixture.hpp](files/tests/support/ranking_fixture.hpp.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/runtime_probe.hpp](files/tests/support/runtime_probe.hpp.md) | 23 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/selection_exception_support.hpp](files/tests/support/selection_exception_support.hpp.md) | 47 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/selection_fixture.hpp](files/tests/support/selection_fixture.hpp.md) | 16 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/selection_independent_fixture.hpp](files/tests/support/selection_independent_fixture.hpp.md) | 36 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/session_checkpoint_test_fixture.hpp](files/tests/support/session_checkpoint_test_fixture.hpp.md) | 22 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/session_file_fixture.hpp](files/tests/support/session_file_fixture.hpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/session_journal_fixture.hpp](files/tests/support/session_journal_fixture.hpp.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/session_journal_stream_cases.hpp](files/tests/support/session_journal_stream_cases.hpp.md) | 16 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/sink_replay_fixture.hpp](files/tests/support/sink_replay_fixture.hpp.md) | 7 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/sql_aggregate_file_fixture.hpp](files/tests/support/sql_aggregate_file_fixture.hpp.md) | 18 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/sql_aggregate_file_probe.hpp](files/tests/support/sql_aggregate_file_probe.hpp.md) | 4 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/sql_aggregate_session_fixture.hpp](files/tests/support/sql_aggregate_session_fixture.hpp.md) | 12 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/sql_aggregate_session_probe.hpp](files/tests/support/sql_aggregate_session_probe.hpp.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/sql_rows_session_fixture.hpp](files/tests/support/sql_rows_session_fixture.hpp.md) | 29 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/statistics_acceptance.hpp](files/tests/support/statistics_acceptance.hpp.md) | 21 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/update_pattern_fixture.hpp](files/tests/support/update_pattern_fixture.hpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/weighted_bag_fixture.hpp](files/tests/support/weighted_bag_fixture.hpp.md) | 20 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/weighted_fixture.hpp](files/tests/support/weighted_fixture.hpp.md) | 34 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/window_checkpoint_test_fixture.hpp](files/tests/support/window_checkpoint_test_fixture.hpp.md) | 16 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/support/workload_replay.cpp](files/tests/support/workload_replay.cpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/accounted_ordered_rows_test.cpp](files/tests/unit/accounted_ordered_rows_test.cpp.md) | 16 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/admission_test.cpp](files/tests/unit/admission_test.cpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/aggregate_binding_test.cpp](files/tests/unit/aggregate_binding_test.cpp.md) | 14 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/aggregate_runtime_test.cpp](files/tests/unit/aggregate_runtime_test.cpp.md) | 37 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/annotation_admission_test.cpp](files/tests/unit/annotation_admission_test.cpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/annotation_oracle_driver.cpp](files/tests/unit/annotation_oracle_driver.cpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/annotation_policy_test.cpp](files/tests/unit/annotation_policy_test.cpp.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/arena_exception_test.cpp](files/tests/unit/arena_exception_test.cpp.md) | 25 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/arena_model_test.cpp](files/tests/unit/arena_model_test.cpp.md) | 32 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/arena_storage_test.cpp](files/tests/unit/arena_storage_test.cpp.md) | 12 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/batch_window_exception_test.cpp](files/tests/unit/batch_window_exception_test.cpp.md) | 63 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/binding_test.cpp](files/tests/unit/binding_test.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/candidate_proposals_test.cpp](files/tests/unit/candidate_proposals_test.cpp.md) | 32 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/candidates_exception_test.cpp](files/tests/unit/candidates_exception_test.cpp.md) | 88 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/candidates_io_test.cpp](files/tests/unit/candidates_io_test.cpp.md) | 20 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/candidates_test.cpp](files/tests/unit/candidates_test.cpp.md) | 37 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/catalog_test.cpp](files/tests/unit/catalog_test.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/checkpoint_image_test.cpp](files/tests/unit/checkpoint_image_test.cpp.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/combined_statistics_exception_test.cpp](files/tests/unit/combined_statistics_exception_test.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/combined_statistics_fixture.hpp](files/tests/unit/combined_statistics_fixture.hpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/combined_statistics_test.cpp](files/tests/unit/combined_statistics_test.cpp.md) | 2 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/comparisons_test.cpp](files/tests/unit/comparisons_test.cpp.md) | 25 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/compiler_plan_artifact_test.cpp](files/tests/unit/compiler_plan_artifact_test.cpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/composed_explain_test.cpp](files/tests/unit/composed_explain_test.cpp.md) | 59 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/constant_route_test.cpp](files/tests/unit/constant_route_test.cpp.md) | 24 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/constraint_memory_test.cpp](files/tests/unit/constraint_memory_test.cpp.md) | 16 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/cursor_observation_test.cpp](files/tests/unit/cursor_observation_test.cpp.md) | 73 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/delta_anchor_test.cpp](files/tests/unit/delta_anchor_test.cpp.md) | 41 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/delta_factor_test.cpp](files/tests/unit/delta_factor_test.cpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/delta_lifecycle_exception_test.cpp](files/tests/unit/delta_lifecycle_exception_test.cpp.md) | 46 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/delta_lifecycle_test.cpp](files/tests/unit/delta_lifecycle_test.cpp.md) | 57 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/delta_live_test.cpp](files/tests/unit/delta_live_test.cpp.md) | 46 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/delta_memory_test.cpp](files/tests/unit/delta_memory_test.cpp.md) | 20 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/delta_replay_scale_test.cpp](files/tests/unit/delta_replay_scale_test.cpp.md) | 29 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/delta_replay_test.cpp](files/tests/unit/delta_replay_test.cpp.md) | 43 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/delta_runtime_exception_test.cpp](files/tests/unit/delta_runtime_exception_test.cpp.md) | 51 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/delta_runtime_test.cpp](files/tests/unit/delta_runtime_test.cpp.md) | 53 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/delta_spec_test.cpp](files/tests/unit/delta_spec_test.cpp.md) | 32 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/difference_test.cpp](files/tests/unit/difference_test.cpp.md) | 30 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/durable_pipeline_test.cpp](files/tests/unit/durable_pipeline_test.cpp.md) | 27 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/epoch_index_test.cpp](files/tests/unit/epoch_index_test.cpp.md) | 14 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/epoch_memory_test.cpp](files/tests/unit/epoch_memory_test.cpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/epoch_view_exception_test.cpp](files/tests/unit/epoch_view_exception_test.cpp.md) | 65 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/epoch_view_test.cpp](files/tests/unit/epoch_view_test.cpp.md) | 27 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/exact_oracle_test.cpp](files/tests/unit/exact_oracle_test.cpp.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/fallback_test.cpp](files/tests/unit/fallback_test.cpp.md) | 22 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/file_cleanup_quota_test.cpp](files/tests/unit/file_cleanup_quota_test.cpp.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/fragment_cursor_exception_test.cpp](files/tests/unit/fragment_cursor_exception_test.cpp.md) | 43 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/fragment_cursor_test.cpp](files/tests/unit/fragment_cursor_test.cpp.md) | 33 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/generation_fault_test.cpp](files/tests/unit/generation_fault_test.cpp.md) | 22 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/generation_opaque_test.cpp](files/tests/unit/generation_opaque_test.cpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/generation_recovery_admission_test.cpp](files/tests/unit/generation_recovery_admission_test.cpp.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/generation_test.cpp](files/tests/unit/generation_test.cpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/history_retirement_fault_test.cpp](files/tests/unit/history_retirement_fault_test.cpp.md) | 18 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/history_retirement_test.cpp](files/tests/unit/history_retirement_test.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/independent_queries_test.cpp](files/tests/unit/independent_queries_test.cpp.md) | 21 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/index_directory_test.cpp](files/tests/unit/index_directory_test.cpp.md) | 17 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/index_live_list_test.cpp](files/tests/unit/index_live_list_test.cpp.md) | 12 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/index_node_lifetime_test.cpp](files/tests/unit/index_node_lifetime_test.cpp.md) | 14 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/index_scalar_work_test.cpp](files/tests/unit/index_scalar_work_test.cpp.md) | 7 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_collision_test.cpp](files/tests/unit/indexed_collision_test.cpp.md) | 7 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_copy_test.cpp](files/tests/unit/indexed_copy_test.cpp.md) | 8 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_cursor_test.cpp](files/tests/unit/indexed_cursor_test.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_delta_runtime_test.cpp](files/tests/unit/indexed_delta_runtime_test.cpp.md) | 53 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_fault_test.cpp](files/tests/unit/indexed_fault_test.cpp.md) | 18 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_initialization_test.cpp](files/tests/unit/indexed_initialization_test.cpp.md) | 42 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_journal_fault_test.cpp](files/tests/unit/indexed_journal_fault_test.cpp.md) | 22 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_journal_test.cpp](files/tests/unit/indexed_journal_test.cpp.md) | 20 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_owner_statistics_fixture.hpp](files/tests/unit/indexed_owner_statistics_fixture.hpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_owner_statistics_test.cpp](files/tests/unit/indexed_owner_statistics_test.cpp.md) | 3 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_physical_runtime_test.cpp](files/tests/unit/indexed_physical_runtime_test.cpp.md) | 30 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_runtime_budget_test.cpp](files/tests/unit/indexed_runtime_budget_test.cpp.md) | 20 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_session_test.cpp](files/tests/unit/indexed_session_test.cpp.md) | 54 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_support_model_test.cpp](files/tests/unit/indexed_support_model_test.cpp.md) | 28 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_table_model_test.cpp](files/tests/unit/indexed_table_model_test.cpp.md) | 31 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/indexed_table_test.cpp](files/tests/unit/indexed_table_test.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/ingest_exception_test.cpp](files/tests/unit/ingest_exception_test.cpp.md) | 57 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/ingest_test.cpp](files/tests/unit/ingest_test.cpp.md) | 37 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/initialization_exception_test.cpp](files/tests/unit/initialization_exception_test.cpp.md) | 76 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/initialization_scale_test.cpp](files/tests/unit/initialization_scale_test.cpp.md) | 14 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/initialization_test.cpp](files/tests/unit/initialization_test.cpp.md) | 42 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/input_specialization_cache_test.cpp](files/tests/unit/input_specialization_cache_test.cpp.md) | 14 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/input_specialization_test.cpp](files/tests/unit/input_specialization_test.cpp.md) | 17 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/instrumentation_memory_test.cpp](files/tests/unit/instrumentation_memory_test.cpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/invariant_memory_test.cpp](files/tests/unit/invariant_memory_test.cpp.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/journal_file_fault_test.cpp](files/tests/unit/journal_file_fault_test.cpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/journal_file_test.cpp](files/tests/unit/journal_file_test.cpp.md) | 7 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/journal_test.cpp](files/tests/unit/journal_test.cpp.md) | 17 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/json_cleanup_test.cpp](files/tests/unit/json_cleanup_test.cpp.md) | 47 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/key_specialization_test.cpp](files/tests/unit/key_specialization_test.cpp.md) | 28 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/layout_test.cpp](files/tests/unit/layout_test.cpp.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/local_sink_fault_test.cpp](files/tests/unit/local_sink_fault_test.cpp.md) | 17 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/local_sink_replay_fault_test.cpp](files/tests/unit/local_sink_replay_fault_test.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/local_sink_replay_test.cpp](files/tests/unit/local_sink_replay_test.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/local_sink_test.cpp](files/tests/unit/local_sink_test.cpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/maintenance_cost_fit_exception_test.cpp](files/tests/unit/maintenance_cost_fit_exception_test.cpp.md) | 28 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/maintenance_cost_fit_test.cpp](files/tests/unit/maintenance_cost_fit_test.cpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/maintenance_cost_owner_exception_test.cpp](files/tests/unit/maintenance_cost_owner_exception_test.cpp.md) | 65 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/maintenance_cost_statistics_test.cpp](files/tests/unit/maintenance_cost_statistics_test.cpp.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/maintenance_cost_test.cpp](files/tests/unit/maintenance_cost_test.cpp.md) | 7 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/memory_account_contract_test.cpp](files/tests/unit/memory_account_contract_test.cpp.md) | 118 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/meta_candidates_test.cpp](files/tests/unit/meta_candidates_test.cpp.md) | 16 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/meta_decomposition_test.cpp](files/tests/unit/meta_decomposition_test.cpp.md) | 26 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/meta_join_trees_test.cpp](files/tests/unit/meta_join_trees_test.cpp.md) | 47 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/native_program_test.cpp](files/tests/unit/native_program_test.cpp.md) | 12 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/native_replanning_test.cpp](files/tests/unit/native_replanning_test.cpp.md) | 27 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/native_replay_fault_test.cpp](files/tests/unit/native_replay_fault_test.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/native_replay_test.cpp](files/tests/unit/native_replay_test.cpp.md) | 18 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/normalization_test.cpp](files/tests/unit/normalization_test.cpp.md) | 20 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/observation_mode_binding_test.cpp](files/tests/unit/observation_mode_binding_test.cpp.md) | 50 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/observation_run_context_test.cpp](files/tests/unit/observation_run_context_test.cpp.md) | 73 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/operator_memory_report_test.cpp](files/tests/unit/operator_memory_report_test.cpp.md) | 22 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/owner_capture_memory_test.cpp](files/tests/unit/owner_capture_memory_test.cpp.md) | 18 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/owner_statistics_exception_test.cpp](files/tests/unit/owner_statistics_exception_test.cpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/owner_statistics_fixture.hpp](files/tests/unit/owner_statistics_fixture.hpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/owner_statistics_test.cpp](files/tests/unit/owner_statistics_test.cpp.md) | 2 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/parser_test.cpp](files/tests/unit/parser_test.cpp.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/physical_api_test.cpp](files/tests/unit/physical_api_test.cpp.md) | 22 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/physical_backend_options_test.cpp](files/tests/unit/physical_backend_options_test.cpp.md) | 18 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/physical_backend_plan_test.cpp](files/tests/unit/physical_backend_plan_test.cpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/physical_lowering_test.cpp](files/tests/unit/physical_lowering_test.cpp.md) | 17 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/physical_runtime_exception_test.cpp](files/tests/unit/physical_runtime_exception_test.cpp.md) | 56 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/physical_runtime_test.cpp](files/tests/unit/physical_runtime_test.cpp.md) | 30 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/planner_certificate_codec_test.cpp](files/tests/unit/planner_certificate_codec_test.cpp.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/planner_continuation_edge_test.cpp](files/tests/unit/planner_continuation_edge_test.cpp.md) | 26 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/planner_continuation_exception_test.cpp](files/tests/unit/planner_continuation_exception_test.cpp.md) | 54 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/planner_continuation_test.cpp](files/tests/unit/planner_continuation_test.cpp.md) | 23 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/planner_fast_paths_test.cpp](files/tests/unit/planner_fast_paths_test.cpp.md) | 33 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/planner_progress_test.cpp](files/tests/unit/planner_progress_test.cpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/planner_search_exception_test.cpp](files/tests/unit/planner_search_exception_test.cpp.md) | 46 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/prepared_epoch_exception_test.cpp](files/tests/unit/prepared_epoch_exception_test.cpp.md) | 59 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/prepared_epoch_test.cpp](files/tests/unit/prepared_epoch_test.cpp.md) | 24 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/public_tuple_memory_test.cpp](files/tests/unit/public_tuple_memory_test.cpp.md) | 20 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/query_explain_test.cpp](files/tests/unit/query_explain_test.cpp.md) | 50 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/ranking_binding_test.cpp](files/tests/unit/ranking_binding_test.cpp.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/ranking_census_test.cpp](files/tests/unit/ranking_census_test.cpp.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/ranking_contract_test.cpp](files/tests/unit/ranking_contract_test.cpp.md) | 2 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/ranking_empty_test.cpp](files/tests/unit/ranking_empty_test.cpp.md) | 2 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/ranking_evidence_memory_test.cpp](files/tests/unit/ranking_evidence_memory_test.cpp.md) | 26 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/ranking_exception_test.cpp](files/tests/unit/ranking_exception_test.cpp.md) | 18 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/ranking_integer_independent_test.cpp](files/tests/unit/ranking_integer_independent_test.cpp.md) | 21 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/ranking_normalized_exception_test.cpp](files/tests/unit/ranking_normalized_exception_test.cpp.md) | 2 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/ranking_payload_time_test.cpp](files/tests/unit/ranking_payload_time_test.cpp.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/ranking_public_independent_test.cpp](files/tests/unit/ranking_public_independent_test.cpp.md) | 33 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/ranking_pure_link_test.cpp](files/tests/unit/ranking_pure_link_test.cpp.md) | 2 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/ranking_result_memory_test.cpp](files/tests/unit/ranking_result_memory_test.cpp.md) | 24 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/recognition_test.cpp](files/tests/unit/recognition_test.cpp.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/reoptimization_churn_test.cpp](files/tests/unit/reoptimization_churn_test.cpp.md) | 8 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/reoptimization_clock_counter_test.cpp](files/tests/unit/reoptimization_clock_counter_test.cpp.md) | 8 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/reoptimization_descriptor_test.cpp](files/tests/unit/reoptimization_descriptor_test.cpp.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/reoptimization_fault_test.cpp](files/tests/unit/reoptimization_fault_test.cpp.md) | 17 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/reoptimization_generation_test.cpp](files/tests/unit/reoptimization_generation_test.cpp.md) | 20 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/reoptimization_install_fault_test.cpp](files/tests/unit/reoptimization_install_fault_test.cpp.md) | 21 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/reoptimization_install_test.cpp](files/tests/unit/reoptimization_install_test.cpp.md) | 19 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/reoptimization_policy_test.cpp](files/tests/unit/reoptimization_policy_test.cpp.md) | 4 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/reoptimization_promotion_fault_test.cpp](files/tests/unit/reoptimization_promotion_fault_test.cpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/reoptimization_rebuild_test.cpp](files/tests/unit/reoptimization_rebuild_test.cpp.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/reoptimization_recovery_admission_test.cpp](files/tests/unit/reoptimization_recovery_admission_test.cpp.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/reoptimization_recovery_budget_test.cpp](files/tests/unit/reoptimization_recovery_budget_test.cpp.md) | 12 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/reoptimization_selection_test.cpp](files/tests/unit/reoptimization_selection_test.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/reoptimization_session_test.cpp](files/tests/unit/reoptimization_session_test.cpp.md) | 20 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/report_capture_memory_test.cpp](files/tests/unit/report_capture_memory_test.cpp.md) | 31 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/report_memory_schema_test.cpp](files/tests/unit/report_memory_schema_test.cpp.md) | 4 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/residual_exception_test.cpp](files/tests/unit/residual_exception_test.cpp.md) | 50 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/residual_io_test.cpp](files/tests/unit/residual_io_test.cpp.md) | 14 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/residual_test.cpp](files/tests/unit/residual_test.cpp.md) | 47 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/result_cursor_exception_test.cpp](files/tests/unit/result_cursor_exception_test.cpp.md) | 53 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/result_cursor_test.cpp](files/tests/unit/result_cursor_test.cpp.md) | 31 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/runtime_checkpoint_test.cpp](files/tests/unit/runtime_checkpoint_test.cpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/runtime_inspection_test.cpp](files/tests/unit/runtime_inspection_test.cpp.md) | 18 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/runtime_memory_test.cpp](files/tests/unit/runtime_memory_test.cpp.md) | 25 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/runtime_observation_test.cpp](files/tests/unit/runtime_observation_test.cpp.md) | 71 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/runtime_storage_work_test.cpp](files/tests/unit/runtime_storage_work_test.cpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/scalar_statistics_test.cpp](files/tests/unit/scalar_statistics_test.cpp.md) | 45 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/scalar_test.cpp](files/tests/unit/scalar_test.cpp.md) | 9 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/schema_test.cpp](files/tests/unit/schema_test.cpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_backend_binding_test.cpp](files/tests/unit/selection_backend_binding_test.cpp.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_binding_independent_test.cpp](files/tests/unit/selection_binding_independent_test.cpp.md) | 19 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_binding_test.cpp](files/tests/unit/selection_binding_test.cpp.md) | 8 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_cache_independent_test.cpp](files/tests/unit/selection_cache_independent_test.cpp.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_cache_test.cpp](files/tests/unit/selection_cache_test.cpp.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_census_test.cpp](files/tests/unit/selection_census_test.cpp.md) | 2 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_contract_test.cpp](files/tests/unit/selection_contract_test.cpp.md) | 2 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_current_test.cpp](files/tests/unit/selection_current_test.cpp.md) | 2 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_exception_test.cpp](files/tests/unit/selection_exception_test.cpp.md) | 2 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_indexed_owner_test.cpp](files/tests/unit/selection_indexed_owner_test.cpp.md) | 8 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_normalized_exception_test.cpp](files/tests/unit/selection_normalized_exception_test.cpp.md) | 2 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_pattern_test.cpp](files/tests/unit/selection_pattern_test.cpp.md) | 8 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_public_independent_test.cpp](files/tests/unit/selection_public_independent_test.cpp.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_publication_fault_independent_test.cpp](files/tests/unit/selection_publication_fault_independent_test.cpp.md) | 36 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_pure_link_test.cpp](files/tests/unit/selection_pure_link_test.cpp.md) | 2 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_resources_independent_test.cpp](files/tests/unit/selection_resources_independent_test.cpp.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_resources_test.cpp](files/tests/unit/selection_resources_test.cpp.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_result_memory_test.cpp](files/tests/unit/selection_result_memory_test.cpp.md) | 27 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/selection_source_test.cpp](files/tests/unit/selection_source_test.cpp.md) | 2 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/semantics_test.cpp](files/tests/unit/semantics_test.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/session_checkpoint_test.cpp](files/tests/unit/session_checkpoint_test.cpp.md) | 8 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/session_checkpoint_window_test.cpp](files/tests/unit/session_checkpoint_window_test.cpp.md) | 7 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/session_exception_test.cpp](files/tests/unit/session_exception_test.cpp.md) | 53 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/session_file_fault_test.cpp](files/tests/unit/session_file_fault_test.cpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/session_file_test.cpp](files/tests/unit/session_file_test.cpp.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/session_image_test.cpp](files/tests/unit/session_image_test.cpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/session_journal_fault_test.cpp](files/tests/unit/session_journal_fault_test.cpp.md) | 12 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/session_journal_test.cpp](files/tests/unit/session_journal_test.cpp.md) | 10 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/session_memory_test.cpp](files/tests/unit/session_memory_test.cpp.md) | 19 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/session_test.cpp](files/tests/unit/session_test.cpp.md) | 54 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/source_checkpoint_test.cpp](files/tests/unit/source_checkpoint_test.cpp.md) | 12 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/source_image_test.cpp](files/tests/unit/source_image_test.cpp.md) | 14 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_aggregate_binding_test.cpp](files/tests/unit/sql_aggregate_binding_test.cpp.md) | 17 | Check genuine composed admission, origin/NULL decoding, identities, static-bootstrap metadata and explicit limits. |
| [tests/unit/sql_aggregate_checkpoint_test.cpp](files/tests/unit/sql_aggregate_checkpoint_test.cpp.md) | 20 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_aggregate_descriptor_test.cpp](files/tests/unit/sql_aggregate_descriptor_test.cpp.md) | 17 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_aggregate_files_fault_test.cpp](files/tests/unit/sql_aggregate_files_fault_test.cpp.md) | 20 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_aggregate_files_test.cpp](files/tests/unit/sql_aggregate_files_test.cpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_aggregate_input_test.cpp](files/tests/unit/sql_aggregate_input_test.cpp.md) | 16 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_aggregate_rebuild_test.cpp](files/tests/unit/sql_aggregate_rebuild_test.cpp.md) | 29 | Verify whole-image reconstruction, sequences, cumulative grants, constraints and retained ownership. |
| [tests/unit/sql_aggregate_records_test.cpp](files/tests/unit/sql_aggregate_records_test.cpp.md) | 24 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_aggregate_runtime_test.cpp](files/tests/unit/sql_aggregate_runtime_test.cpp.md) | 29 | Exercise original-SQL source/group atomicity, arithmetic, grants and lifetimes. |
| [tests/unit/sql_aggregate_session_fault_test.cpp](files/tests/unit/sql_aggregate_session_fault_test.cpp.md) | 22 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_aggregate_session_test.cpp](files/tests/unit/sql_aggregate_session_test.cpp.md) | 28 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_aggregate_transaction_crash_test.cpp](files/tests/unit/sql_aggregate_transaction_crash_test.cpp.md) | 35 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_rows_batch_test.cpp](files/tests/unit/sql_rows_batch_test.cpp.md) | 36 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_rows_binding_test.cpp](files/tests/unit/sql_rows_binding_test.cpp.md) | 12 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_rows_checkpoint_test.cpp](files/tests/unit/sql_rows_checkpoint_test.cpp.md) | 16 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_rows_descriptor_test.cpp](files/tests/unit/sql_rows_descriptor_test.cpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_rows_output_test.cpp](files/tests/unit/sql_rows_output_test.cpp.md) | 25 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_rows_records_test.cpp](files/tests/unit/sql_rows_records_test.cpp.md) | 21 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_rows_runtime_test.cpp](files/tests/unit/sql_rows_runtime_test.cpp.md) | 25 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_rows_session_fault_test.cpp](files/tests/unit/sql_rows_session_fault_test.cpp.md) | 17 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_rows_session_test.cpp](files/tests/unit/sql_rows_session_test.cpp.md) | 17 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/sql_source_snapshot_test.cpp](files/tests/unit/sql_source_snapshot_test.cpp.md) | 17 | Verify complete physical-source images, actual bindings, limits and retained ownership. |
| [tests/unit/star_test.cpp](files/tests/unit/star_test.cpp.md) | 29 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/statistics_capture_exception_test.cpp](files/tests/unit/statistics_capture_exception_test.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/statistics_capture_test.cpp](files/tests/unit/statistics_capture_test.cpp.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/statistics_collection_test.cpp](files/tests/unit/statistics_collection_test.cpp.md) | 21 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/statistics_explain_exception_test.cpp](files/tests/unit/statistics_explain_exception_test.cpp.md) | 12 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/statistics_explain_test.cpp](files/tests/unit/statistics_explain_test.cpp.md) | 5 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/statistics_report_fixture.hpp](files/tests/unit/statistics_report_fixture.hpp.md) | 8 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/statistics_runtime_only_test.cpp](files/tests/unit/statistics_runtime_only_test.cpp.md) | 2 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/storage_exception_test.cpp](files/tests/unit/storage_exception_test.cpp.md) | 22 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/storage_journal_exception_test.cpp](files/tests/unit/storage_journal_exception_test.cpp.md) | 34 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/storage_journal_test.cpp](files/tests/unit/storage_journal_test.cpp.md) | 34 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/storage_model_test.cpp](files/tests/unit/storage_model_test.cpp.md) | 23 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/storage_table_test.cpp](files/tests/unit/storage_table_test.cpp.md) | 16 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/stream_input_memory_test.cpp](files/tests/unit/stream_input_memory_test.cpp.md) | 22 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/support_api_test.cpp](files/tests/unit/support_api_test.cpp.md) | 32 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/support_exception_test.cpp](files/tests/unit/support_exception_test.cpp.md) | 36 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/support_journal_test.cpp](files/tests/unit/support_journal_test.cpp.md) | 41 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/support_model_test.cpp](files/tests/unit/support_model_test.cpp.md) | 28 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/topk_test.cpp](files/tests/unit/topk_test.cpp.md) | 28 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/transport_batch_test.cpp](files/tests/unit/transport_batch_test.cpp.md) | 28 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/tree_verifier_test.cpp](files/tests/unit/tree_verifier_test.cpp.md) | 14 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/typed_input_memory_test.cpp](files/tests/unit/typed_input_memory_test.cpp.md) | 17 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/update_pattern_profile_test.cpp](files/tests/unit/update_pattern_profile_test.cpp.md) | 24 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/update_pattern_runtime_test.cpp](files/tests/unit/update_pattern_runtime_test.cpp.md) | 40 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/update_pattern_test.cpp](files/tests/unit/update_pattern_test.cpp.md) | 15 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/update_pattern_transfer_test.cpp](files/tests/unit/update_pattern_transfer_test.cpp.md) | 19 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/weighted_bag_oracle_driver.cpp](files/tests/unit/weighted_bag_oracle_driver.cpp.md) | 7 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/weighted_bag_test.cpp](files/tests/unit/weighted_bag_test.cpp.md) | 11 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/weighted_cursor_limits_test.cpp](files/tests/unit/weighted_cursor_limits_test.cpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/weighted_delta_test.cpp](files/tests/unit/weighted_delta_test.cpp.md) | 35 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/weighted_limits_test.cpp](files/tests/unit/weighted_limits_test.cpp.md) | 22 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/weighted_messages_test.cpp](files/tests/unit/weighted_messages_test.cpp.md) | 20 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/weighted_oracle_driver.cpp](files/tests/unit/weighted_oracle_driver.cpp.md) | 6 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/weighted_support_test.cpp](files/tests/unit/weighted_support_test.cpp.md) | 24 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/window_checkpoint_test.cpp](files/tests/unit/window_checkpoint_test.cpp.md) | 21 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/window_memory_test.cpp](files/tests/unit/window_memory_test.cpp.md) | 21 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/window_sequence_test.cpp](files/tests/unit/window_sequence_test.cpp.md) | 8 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/window_test.cpp](files/tests/unit/window_test.cpp.md) | 51 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/workload_statistics_exception_test.cpp](files/tests/unit/workload_statistics_exception_test.cpp.md) | 17 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/workload_statistics_fixture.hpp](files/tests/unit/workload_statistics_fixture.hpp.md) | 13 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/unit/workload_statistics_test.cpp](files/tests/unit/workload_statistics_test.cpp.md) | 21 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tests/workflow/generate_fixtures.py](files/tests/workflow/generate_fixtures.py.md) | 18 | Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection. |
| [tools/analyze_adversarial_scalability.py](files/tools/analyze_adversarial_scalability.py.md) | 10 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/build_experimental_report.py](files/tools/build_experimental_report.py.md) | 33 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/check_code_specs.py](files/tools/check_code_specs.py.md) | 18 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/check_legacy_replay.py](files/tools/check_legacy_replay.py.md) | 13 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/code_specs_support.py](files/tools/code_specs_support.py.md) | 156 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/component_analysis.py](files/tools/component_analysis.py.md) | 5 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/component_workloads.py](files/tools/component_workloads.py.md) | 14 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/generate_adversarial_workloads.py](files/tools/generate_adversarial_workloads.py.md) | 10 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/generate_code_specs.py](files/tools/generate_code_specs.py.md) | 45 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/generate_ranking_evaluation.py](files/tools/generate_ranking_evaluation.py.md) | 13 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/generate_sql_aggregate_record_fixtures.py](files/tools/generate_sql_aggregate_record_fixtures.py.md) | 7 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/generate_workloads.py](files/tools/generate_workloads.py.md) | 19 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/package_release.py](files/tools/package_release.py.md) | 25 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/parser_spike/run.sh](files/tools/parser_spike/run.sh.md) | 2 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/parser_spike/smoke.c](files/tools/parser_spike/smoke.c.md) | 2 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/plot_adversarial_scalability.py](files/tools/plot_adversarial_scalability.py.md) | 12 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/plot_experimental_report.py](files/tools/plot_experimental_report.py.md) | 7 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/prepare_workflow_input.py](files/tools/prepare_workflow_input.py.md) | 3 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/ranking_analysis.py](files/tools/ranking_analysis.py.md) | 11 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/reference_fuzz.py](files/tools/reference_fuzz.py.md) | 53 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/run_adversarial_scalability.py](files/tools/run_adversarial_scalability.py.md) | 8 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/run_baseline_evaluation.py](files/tools/run_baseline_evaluation.py.md) | 6 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/run_component_planning.py](files/tools/run_component_planning.py.md) | 10 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/run_input_specialization.py](files/tools/run_input_specialization.py.md) | 10 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/run_legacy_baseline.py](files/tools/run_legacy_baseline.py.md) | 8 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/run_measurements.py](files/tools/run_measurements.py.md) | 19 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/run_operational_evaluation.py](files/tools/run_operational_evaluation.py.md) | 17 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/run_ranking_evaluation.py](files/tools/run_ranking_evaluation.py.md) | 13 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/run_search_evaluation.py](files/tools/run_search_evaluation.py.md) | 12 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/sqlite_component.py](files/tools/sqlite_component.py.md) | 3 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/support/ComponentReplay.scala](files/tools/support/ComponentReplay.scala.md) | 8 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/support/CrownReplay.scala](files/tools/support/CrownReplay.scala.md) | 2 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/support/check_composed_reports.py](files/tools/support/check_composed_reports.py.md) | 24 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/support/check_cursor_reports.py](files/tools/support/check_cursor_reports.py.md) | 19 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/support/check_query_reports.py](files/tools/support/check_query_reports.py.md) | 11 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/support/check_statistics_reports.py](files/tools/support/check_statistics_reports.py.md) | 15 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_candidate_reports.py](files/tools/verify_candidate_reports.py.md) | 13 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_clean_build.py](files/tools/verify_clean_build.py.md) | 17 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_imported_workloads.py](files/tools/verify_imported_workloads.py.md) | 12 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_invariant_wire.py](files/tools/verify_invariant_wire.py.md) | 1 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_json_cleanup.py](files/tools/verify_json_cleanup.py.md) | 6 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_memory_cli.py](files/tools/verify_memory_cli.py.md) | 3 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_memory_report.py](files/tools/verify_memory_report.py.md) | 3 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_observability_reports.py](files/tools/verify_observability_reports.py.md) | 1 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_report_memory_schema_v1.py](files/tools/verify_report_memory_schema_v1.py.md) | 12 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_report_memory_schema_v2.py](files/tools/verify_report_memory_schema_v2.py.md) | 13 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_residual_reports.py](files/tools/verify_residual_reports.py.md) | 7 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_schemas.py](files/tools/verify_schemas.py.md) | 5 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_search_progress.py](files/tools/verify_search_progress.py.md) | 7 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_statistics_reports.py](files/tools/verify_statistics_reports.py.md) | 3 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |
| [tools/verify_workloads.py](files/tools/verify_workloads.py.md) | 14 | Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments. |

See [error-handling dispositions](error_handling.md) and the [source index](README.md).
