# `include/crown/runtime/delta.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/delta.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain live visible-factor indexes, canonical delta producers and retained delivery epochs.

Snapshot SHA-256: `4e74853831e1c40dd9488bafa6c8e02dd0c84639d0afaf5af665008ca1680463`. 298 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [delta](../../../../subsystem_contracts.md#delta). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/delta_transition_spec.md](../../../../../delta_transition_spec.md), [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/delta_lifecycle.md](../../../../../delta_lifecycle.md), [docs/anchored_delta.md](../../../../../anchored_delta.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../../include/crown/runtime/delta.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 11–11](../../../../../../include/crown/runtime/delta.hpp#L11) | Type/record definition: enum class DeltaMode |  · [reviewed contract](#b0002) |
| [B0003 · 12–12](../../../../../../include/crown/runtime/delta.hpp#L12) | Type/record definition: enum class LiveMaintenance |  · [reviewed contract](#b0003) |
| [B0004 · 13–13](../../../../../../include/crown/runtime/delta.hpp#L13) | Type/record definition: enum class DeltaCompletion |  · [reviewed contract](#b0004) |
| [B0005 · 14–14](../../../../../../include/crown/runtime/delta.hpp#L14) | Type/record definition: enum class DeltaBound |  · [reviewed contract](#b0005) |
| [B0006 · 15–15](../../../../../../include/crown/runtime/delta.hpp#L15) | Type/record definition: enum class DeltaPublication |  · [reviewed contract](#b0006) |
| [B0007 · 16–16](../../../../../../include/crown/runtime/delta.hpp#L16) | Type/record definition: enum class DeltaState |  · [reviewed contract](#b0007) |
| [B0008 · 17–17](../../../../../../include/crown/runtime/delta.hpp#L17) | Type/record definition: enum class DeltaStep |  · [reviewed contract](#b0008) |
| [B0009 · 18–24](../../../../../../include/crown/runtime/delta.hpp#L18) | Type/record definition: struct DeltaTimings | source comment (unverified): // Disjoint wall-clock phases, excluding user pause time. Sink time includes · [reviewed contract](#b0009) |
| [B0010 · 25–46](../../../../../../include/crown/runtime/delta.hpp#L25) | Type/record definition: struct DeltaRuntimeProfile | source comment (unverified): // All text refers to static storage; this value may outlive its facade. · [reviewed contract](#b0010) |
| [B0011 · 47–63](../../../../../../include/crown/runtime/delta.hpp#L47) | Type/record definition: struct DeltaOptions | source comment (unverified): // Automatic selects replay for row-coupled live maintenance and anchored · [reviewed contract](#b0011) |
| [B0012 · 64–97](../../../../../../include/crown/runtime/delta.hpp#L64) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0012) |
| [B0013 · 98–102](../../../../../../include/crown/runtime/delta.hpp#L98) | Type/record definition: struct SignedResult |  · [reviewed contract](#b0013) |
| [B0014 · 103–113](../../../../../../include/crown/runtime/delta.hpp#L103) | Type/record definition: struct DeltaStage | source comment (unverified): // One-based position in the physical table's full route list, including · [reviewed contract](#b0014) |
| [B0015 · 114–118](../../../../../../include/crown/runtime/delta.hpp#L114) | Type/record definition: struct LiveSnapshot | source comment (unverified): // Parent-before-child plan.enumeration().steps order, full E keys. · [reviewed contract](#b0015) |
| [B0016 · 119–154](../../../../../../include/crown/runtime/delta.hpp#L119) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Exact set deltas with ordered replay and canonical comparison strategies. · [reviewed contract](#b0016) |
| [B0017 · 155–190](../../../../../../include/crown/runtime/delta.hpp#L155) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Stages at most one accepted core row. This is private progress, not a · [reviewed contract](#b0017) |
| [B0018 · 191–226](../../../../../../include/crown/runtime/delta.hpp#L191) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Bootstrap a checked alternative at this exact committed epoch, under the · [reviewed contract](#b0018) |
| [B0019 · 227–262](../../../../../../include/crown/runtime/delta.hpp#L227) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Account-wide native requests; public exports and caller allocations are separate. · [reviewed contract](#b0019) |
| [B0020 · 263–298](../../../../../../include/crown/runtime/delta.hpp#L263) | controls preprocessing; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Native adapters borrow row values only for this call; pending storage owns · [reviewed contract](#b0020) |

## B0001

[Lines 1–10](../../../../../../include/crown/runtime/delta.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:c925c756710fbfeff434121ace2f5a05ff596f56f9a89e86b64ff07d6ea5513f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/runtime/delta.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/runtime/physical.hpp"\`, \`&lt;string_view&gt;\` for compilation; opens namespace \`crown::observability\`; opens namespace \`crown::runtime\`; opens namespace \`ranking::detail\`; opens namespace \`reoptimization::detail\`; forward-declares \`class ModeDescriptor\`, \`class QuerySession\`, \`struct OwnerAccess\`, \`class Budget\`, \`struct Access\` without defining object layout; closes \`namespace crown::observability\`, \`namespace ranking::detail\`, \`namespace reoptimization::detail\` Member/state declarations in this range include \`} namespace reoptimization::detail {class Budget\`. |
| inputs / outputs | This span declares/carries these members or local values: \`} namespace reoptimization::detail {class Budget\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | Forward declarations permit references to incomplete types; consumers that need layout or members include the defining header. Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 11–11](../../../../../../include/crown/runtime/delta.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class DeltaMode
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select maintenance-only versus exact set-delta production. |
| inputs / outputs | Options or set_mode choose the active mode; profile reports the effective choice. |
| invariants | Maintenance changes physical/support state without building L or output; changing to delta requires successful live-state bootstrap. |
| ownership | Scalar policy, no retained owner. |
| failure | The enum cannot fail; runtime mode transitions enforce readiness and budgets. |
| cost | No allocation for the tag; enabling delta can scan all native state. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0003

[Lines 12–12](../../../../../../include/crown/runtime/delta.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class LiveMaintenance
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select when global live factors are maintained. |
| inputs / outputs | on_output couples live edits to accepted core rows; incremental drains affected buckets; eager rebuilds full images. |
| invariants | Each policy must preserve the same exact committed L; equal outputs do not imply equal work. |
| ownership | Scalar policy borrowed through options/profile. |
| failure | Policy compatibility is checked by runtime construction, not by this enum. |
| cost | Tag storage is fixed; affected bucket scans or complete old/new image costs remain policy dependent. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0004

[Lines 13–13](../../../../../../include/crown/runtime/delta.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class DeltaCompletion
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose replay or a qualified comparison completion strategy. |
| inputs / outputs | automatic resolves from live maintenance; ordered_replay, anchored and root_first choose their admitted algorithms. |
| invariants | Only replay claims bounded accepted transitions after preparation; candidate bounds do not bound rejected runs. |
| ownership | Scalar policy. |
| failure | Incompatible replay/comparison choices reject at runtime admission. |
| cost | Fixed tag; actual preparation/enumeration/finalization are separate work phases. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0005

[Lines 14–14](../../../../../../include/crown/runtime/delta.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class DeltaBound
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label the specific transition bound actually established. |
| inputs / outputs | unclaimed or bounded_indexed_actions appears in a returned profile. |
| invariants | A label is descriptive, not proof authority or a constant public-startup claim. |
| ownership | Scalar descriptor. |
| failure | No allocation or failure. |
| cost | Fixed storage and copy. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0006

[Lines 15–15](../../../../../../include/crown/runtime/delta.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class DeltaPublication
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe whether committed delta records are published. |
| inputs / outputs | no_delta_output for maintenance; eager_atomic_spool for delta mode. |
| invariants | The eager spool becomes public only after the complete physical epoch commits. |
| ownership | Scalar descriptor. |
| failure | No failure in the enum; spool limits can reject epoch preparation. |
| cost | Fixed storage; full eager output preparation has real row/byte costs. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0007

[Lines 16–16](../../../../../../include/crown/runtime/delta.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class DeltaState
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the private/committed Delta lifecycle. |
| inputs / outputs | Runtime and pending token state accessors return readiness/progress/output/terminal states. |
| invariants | Paused/prepared work remains unpublished; committed output does not roll back input on discard. |
| ownership | Scalar snapshot; does not retain or unlock an epoch. |
| failure | The enum itself cannot fail; valid-owner rules apply to accessors. |
| cost | Fixed descriptor; no traversal. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0008

[Lines 17–17](../../../../../../include/crown/runtime/delta.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class DeltaStep
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report one pending preparation step. |
| inputs / outputs | step returns progress, core_result or prepared. |
| invariants | core_result is private progress, not a published SignedResult. |
| ownership | Scalar status. |
| failure | Stepping can throw before publication and abort the pending epoch. |
| cost | Fixed status; step still includes the documented preparation/production work. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0009

[Lines 18–24](../../../../../../include/crown/runtime/delta.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaTimings
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep disjoint observed wall-clock phase durations. |
| inputs / outputs | Propagation, internal delta, mapping, serialization and callback wait durations are uint64 nanoseconds. |
| invariants | Pause time is excluded; sink time includes callback CPU/wait; saturating diagnostics do not authorize deterministic work. |
| ownership | Inline counters copied with an owning epoch/profile observation. |
| failure | Value construction cannot allocate; clock/callback failure handling belongs to the driver. |
| cost | Fixed counter storage, optional clock observations during executed phases; no timing-based correctness claim. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0010

[Lines 25–46](../../../../../../include/crown/runtime/delta.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaRuntimeProfile
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the effective runtime strategy, backend, quotas and qualified costs. |
| inputs / outputs | profile returns value fields and static string_views for the actual admitted runtime. |
| invariants | Backend follows immutable plan options in every mode. Candidate/accepted bounds apply only to the stated phase; public eager startup includes complete epoch preparation. Spool accounting includes native node/value/payload requests and account framing. output_accounting preserves historical v2 text byte for byte; its old wording is not the current spool quota specification. DeltaOptions comments and docs/delta_runtime.md state the actual framed-byte accounting. |
| ownership | Text refers to static literals, so a detached profile outlives the facade. The profile does not retain the runtime. |
| failure | Plain value construction is nonallocating; profile on a moved facade rejects at its owner boundary. |
| cost | Fixed metadata selection; the stated state/scans/allocator/width costs are not performed by reading the descriptor. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0011

[Lines 47–63](../../../../../../include/crown/runtime/delta.hpp#L47); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaOptions
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound and select exact set-delta execution. |
| inputs / outputs | Physical options, mode/view/live/completion policies, delta work, cursor/view limits and finite spool limits are admitted together. |
| invariants | Automatic completion is resolved; exceeding a spool limit aborts before publication. Spool bytes include node and native tuple requests with account framing; query descriptors/scratch/journals are additional. |
| ownership | Options are copied into the runtime; they do not own pending rows or results. |
| failure | Invalid combinations reject at construction; resource/work failures propagate during actual admission/preparation. |
| cost | Fixed policy copy; finite caps do not remove the cost of producing and retaining the whole eager spool. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0012

[Lines 64–97](../../../../../../include/crown/runtime/delta.hpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaMetrics
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record actual delta work and retained-state/output peaks. |
| inputs / outputs | Work/category counts, live/index/queue gauges, maxima and spool sizes describe an attempt/epoch. |
| invariants | Counts distinguish preparation, candidates, accepted/rejected rows and finalization. Diagnostic maxima and rows are not an asymptotic proof or a CPU meter. |
| ownership | Inline counters; accessor references borrow their pending/committed owner. |
| failure | Constructing the value is nonallocating; work/counter admission occurs in producer helpers before their mutations. |
| cost | Fixed-size state and selected hook increments; snapshots/export and the measured operations retain separate costs. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0013

[Lines 98–102](../../../../../../include/crown/runtime/delta.hpp#L98); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SignedResult
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer one committed owning set-delta record. |
| inputs / outputs | Ordinal, insert/erase sign and a native owning Tuple describe one output. |
| invariants | Ordinal identifies order within the prepared epoch; it is not a durable exactly-once acknowledgement. |
| ownership | Tuple retains its funded payload/account after epoch/runtime destruction. |
| failure | Moving a prepared record is nonallocating; later explicit conversion/encoding may allocate. |
| cost | Fixed handle move; deep row construction occurred during spool preparation, and final payload destruction has width/allocator cost. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0014

[Lines 103–113](../../../../../../include/crown/runtime/delta.hpp#L103); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaStage
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one physical alias prefix and its committed output interval. |
| inputs / outputs | Occurrence/prefix, before/after existence, work counts and spool begin/count describe a selected route. |
| invariants | Prefix is one-based in the full route list and may have gaps; spool interval is zero-based. Scalar EXISTS replacement is prepared at epoch end outside these ranges. |
| ownership | Inline summary; span access borrows its epoch. |
| failure | Value copying does not allocate; construction follows route preparation and can report only reached work. |
| cost | Fixed-size summary; does not scan or regenerate output. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0015

[Lines 114–118](../../../../../../include/crown/runtime/delta.hpp#L114); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LiveSnapshot
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export complete global live factors at one committed sequence. |
| inputs / outputs | Vector of public Relations follows parent-before-child enumeration-step order and contains full E keys. |
| invariants | This is a diagnostic image of global L, distinct from local E membership or support counts. |
| ownership | Owns copied relation rows; survives the facade. |
| failure | Snapshot materialization can allocate and fail; it does not publish a new epoch. |
| cost | Full factor/row/scalar-width scan and copy with ordinary public DTO allocations. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/delta_transition_spec.md](../../../../../delta_transition_spec.md) |

## B0016

[Lines 119–154](../../../../../../include/crown/runtime/delta.hpp#L119); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Epoch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a lease over committed prepared output. |
| inputs / outputs | Move-only Epoch exposes committed physical input, metrics/timings/stages/layout and output delivery. |
| invariants | Private records become readable only after successful native commit. Finishing/discarding output permits the next input and does not undo committed state. |
| ownership | Shared Data retains the runtime/account and FIFO. Borrowed metadata spans/references require this owner to remain valid. |
| failure | Invalid handles reject. Delivery callback failure preserves the current row; output owner teardown releases unread rows. |
| cost | Prepared next is a nonallocating owning move; callback/serialization and unread/final-owner teardown costs remain explicit. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
[[nodiscard]] bool deliver_one(const std::function<void(const SignedResult&)>& sink);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acknowledge a committed row only after callback success. |
| inputs / outputs | Sink receives a borrowed SignedResult; false means no remaining record. The two-callback overload measures serialization separately. |
| invariants | A sink that accepts then throws can observe a duplicate on retry; callback completion, not ordinal, advances acknowledgement. |
| ownership | Epoch retains the row throughout callback even if a facade is moved/closed; callback must copy payload to retain it independently. |
| failure | Original callback exception propagates with current row retained unless deferred discard is completed safely after callback. |
| cost | One callback per retained row plus optional serialization; arbitrary callback CPU/I/O is additional, with no durable delivery guarantee. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0017

[Lines 155–190](../../../../../../include/crown/runtime/delta.hpp#L155); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class PendingEpoch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own unpublished physical and live-state preparation. |
| inputs / outputs | Move-only token exposes state, sequence, metrics, route summaries and stepping/control/publication. |
| invariants | Only prepared tokens can commit. Destruction or rollback aborts unpublished input; paused/draining rows are still private. |
| ownership | Unique accounted Data owns native pending state, journals, views, candidate producers and private FIFO. |
| failure | Stage/preparation failures abort the token through existing rollback; required outer error boundaries preserve original failures. |
| cost | Affected preparation/undo/spool storage; cleanup can traverse affected keys, rows and retained owners even without allocations. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
[[nodiscard]] DeltaStep step();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare at most one accepted core row while retaining all required aliases. |
| inputs / outputs | Progress status, private core-result status or prepared status; not a public SignedResult. |
| invariants | Propagation/preparation and terminal finalization can perform data-dependent work; one core row is not a constant public startup promise. |
| ownership | Borrows/mutates the token and its funded producer/queue state. |
| failure | Work/allocation/arithmetic or internal failures abort unpublished state; prior debits remain spent. |
| cost | Qualified replay core actions plus separate route preparation/finalization, row widths, exact-key comparisons and allocator work. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
void start_drain();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable output retention while still completing semantic maintenance. |
| inputs / outputs | Pending token enters draining mode; later step/drain executes all required rows/aliases. |
| invariants | Dropping output retention does not skip live-state transitions and is distinct from rollback. |
| ownership | Releases/prevents retained FIFO records under the existing token owner. |
| failure | Invalid token/state rejects; subsequent preparation can still fail and abort. |
| cost | May destroy already retained rows and continues all required native work; no output-history copy. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
[[nodiscard]] Epoch commit();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a completely prepared delta epoch. |
| inputs / outputs | Prepared token transfers a committed owning Epoch. |
| invariants | Native state, all ordered aliases and output are published together; no partial alias visibility. |
| ownership | Prepared Data becomes the committed output owner; token becomes inactive. |
| failure | No allocation/throwing preparation belongs after the publication point; invalid state rejects before commit. |
| cost | Nonallocating publication with affected cleanup/lifecycle work; no constant total finalization claim. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0018

[Lines 191–226](../../../../../../include/crown/runtime/delta.hpp#L191); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Epoch discard();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish a private epoch without retaining delta records. |
| inputs / outputs | Drains required maintenance, then returns the committed empty/output-discarded epoch. |
| invariants | Input and live-state semantics still commit; this is distinct from aborting the token. |
| ownership | Existing token owns all private state until publication. |
| failure | Drain can fail and abort; no partial committed record escapes. |
| cost | All required maintenance/production and retained-row destruction remain real work. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
[[nodiscard]] DeltaRuntime rebuilt_for(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a checked alternative from this exact committed source state. |
| inputs / outputs | MinimumHeightCandidate, build limits and replan limits produce a separate DeltaRuntime at the same sequence. |
| invariants | Uses the complete immutable source and original account; does not publish a session switch or perform catch-up. |
| ownership | Old runtime remains intact while a funded candidate, native snapshot and replacement live state coexist. |
| failure | Admission, source binding, work or allocation failure destroys the private candidate without changing the current owner. |
| cost | Compiler/lowering, full snapshot/rebuild and temporary dual-state memory are explicit. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/reoptimization.md](../../../../../reoptimization.md) |

```text
[[nodiscard]] recovery::EncodedImage checkpoint_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode native runtime state at a writer-ready barrier. |
| inputs / outputs | Image limits in; owning encoded native image out. |
| invariants | No private epoch, result cursor or unread output. Runtime-only image does not itself encode session source/window positions or publish durable files. |
| ownership | Encoded result retains its own funded bytes; input runtime remains unchanged. |
| failure | Binding/barrier/resource/encoding failure propagates before external publication. |
| cost | Explicit source/image traversal and encoding allocations; not an update-path primitive. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/native-replay.md](../../../../../native-replay.md) |

```text
[[nodiscard]] static DeltaRuntime restore_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore matching native state into a receiving program/account. |
| inputs / outputs | Immutable program, image bytes, semantic/runtime/build/image limits produce a rebuilt committed owner. |
| invariants | Image source/binding/options must match; receiver memory cap may differ; diagnostic history resets. |
| ownership | New owner imports source rows and rebuilds support/index/live state; input bytes are borrowed during restore. |
| failure | Validation/rebuild/work/allocation failure prevents publishing a returned runtime. |
| cost | Full decode/rebuild and retained receiving storage; durable session/root repair remains separate. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/native-replay.md](../../../../../native-replay.md) |

## B0019

[Lines 227–262](../../../../../../include/crown/runtime/delta.hpp#L227); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] resource::MemoryStatistics accounted_memory_statistics() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report actual allocations routed through the native query account. |
| inputs / outputs | Returns the account-wide requested-byte counters for this owner/account. |
| invariants | These counters are not RSS and do not certify all external/public DTO or caller allocations. Shared-account residents remain included. |
| ownership | Value snapshot; account ownership remains with retained runtime/program/results. |
| failure | Moved facade rejects; valid account statistics are nonallocating. |
| cost | Fixed account-counter snapshot; attribution scans and full memory captures are separate APIs. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
[[nodiscard]] statistics::CombinedCapture capture_combined_statistics(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture declared native and workload statistics explicitly. |
| inputs / outputs | Owner request/limits produce owning captures; view overload borrows request data only for the call. |
| invariants | Unknown/incomplete/freshness statuses remain visible; no sampling result authorizes structural proof or hidden exactness. |
| ownership | Capture owns funded result payload and retains its originating account/metadata as defined by the statistics API. |
| failure | Expected work/allocation exhaustion produces declared statuses; internal contract faults retain their public boundary behavior. |
| cost | Selected/full scans, sorting, sampling and result allocation are explicit diagnostic work. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/statistics.md](../../../../../statistics.md) |

```text
void declare_benchmark_context(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach preconstructed immutable observation labels. |
| inputs / outputs | Shared const DeclaredBenchmarkContext affects future attempt bindings. |
| invariants | Changes no query semantics or deterministic work grant and does not parse text or read clocks at mutation. |
| ownership | Runtime retains the shared immutable labels; prior attempt records retain their own bindings. |
| failure | Writable-owner/state validation precedes assignment; callers fund/construct labels before mutation. |
| cost | Shared-handle/lifecycle update; label destruction may release retained metadata. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
[[nodiscard]] DeltaMetrics set_mode(DeltaMode mode);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Switch maintenance/output mode only at a quiescent barrier. |
| inputs / outputs | Requested mode in; bootstrap metrics out. |
| invariants | Failed enabling bootstrap preserves old mode/cache. Maintenance updates never consume a stale live image. |
| ownership | Current owner retains source state; private replacement live image is adopted only after success. |
| failure | Reader/pending/output conflicts reject; work/allocation/bootstrap failures preserve committed state. |
| cost | Enabling delta scans/builds global live factors; disabling releases retained live state; neither is a constant total operation. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0020

[Lines 263–298](../../../../../../include/crown/runtime/delta.hpp#L263); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] PendingEpoch begin_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begin an exact physical full-row set event using borrowed input. |
| inputs / outputs | PhysicalUpdateView carries sequence/table/sign/borrowed scalar row; returned token owns preparation. |
| invariants | All physical aliases remain inside one publication epoch; source identity, types and constraints are checked. |
| ownership | Borrowed values are imported/pinned before begin returns; caller need not export an owning public Row. |
| failure | Invalid update/source/domain/work/allocation failure rejects or aborts before publication. |
| cost | Required physical/source routing and private state preparation, with actual row/width/index costs; no added row-export copy. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
[[nodiscard]] Epoch apply_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare and commit one borrowed physical update synchronously. |
| inputs / outputs | PhysicalUpdateView produces a committed eager output Epoch. |
| invariants | Equivalent retention semantics to begin/drain/commit; does not silently disable output. |
| ownership | Private local token owns rollback until commit; returned Epoch owns prepared output. |
| failure | Any preparation failure unwinds its private owner and preserves committed input state; durable delivery is outside this boundary. |
| cost | Complete physical/alias/preparation/mapping/spool/finalization work occurs before return. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
[[nodiscard]] SupportRuntime::ResultCursor core_results(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read committed native core results under an existing runtime lease. |
| inputs / outputs | Cursor options produce a retaining lazy SupportRuntime cursor; results() selects the SQL-facing projection. |
| invariants | Result readers exclude mutation; set output does not imply weighted/nullable SQL-row admission. |
| ownership | Cursor retains native owner and borrowed entries; each emitted Tuple owns its funded payload. |
| failure | Construction publishes a reader only after preparation; next failure terminates/relinquishes its lease. |
| cost | Native cursor startup/traversal/output costs plus explicit result ownership, not a full result snapshot. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
[[nodiscard]] CanonicalDeltaState canonical_state() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export exact state for independent diagnostic comparison. |
| inputs / outputs | Returns owning canonical source/support/live state for the current owner. |
| invariants | Canonical equality is evidence for the inspected state, not a replacement for source admission or minimum-height proof. |
| ownership | Exported public structures own their copied rows; do not borrow a transient native row. |
| failure | Readiness/validation/allocation failure propagates without modifying committed state. |
| cost | Full traversal, sorting/copying and scalar-width allocation; never hidden per-event maintenance. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../../ordered_delta.md), [docs/query_memory.md](../../../../../query_memory.md) |
