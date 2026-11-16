# `include/crown/runtime/workload_statistics.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/workload_statistics.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `a884dafd3ccf1a4f17b7cc352e138e321df6f4633a9d8e94125a7e8da64ddaa9`. 136 lines partitioned into 27 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../../statistics.md), [docs/observability.md](../../../../../observability.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../../include/crown/runtime/workload_statistics.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 11–11](../../../../../../include/crown/runtime/workload_statistics.hpp#L11) | Type/record definition: enum class Kind |  · [reviewed contract](#b0002) |
| [B0003 · 12–12](../../../../../../include/crown/runtime/workload_statistics.hpp#L12) | Type/record definition: enum class Operation | growth insert · [reviewed contract](#b0003) |
| [B0004 · 13–13](../../../../../../include/crown/runtime/workload_statistics.hpp#L13) | Explanatory comments or spacing. | source comment (unverified): // Timed collection is deliberately not implemented. These modes read no clocks. · [reviewed contract](#b0004) |
| [B0005 · 14–14](../../../../../../include/crown/runtime/workload_statistics.hpp#L14) | Type/record definition: enum class Mode | source comment (unverified): // Timed collection is deliberately not implemented. These modes read no clocks. · [reviewed contract](#b0005) |
| [B0006 · 15–15](../../../../../../include/crown/runtime/workload_statistics.hpp#L15) | Type/record definition: enum class InputScope |  · [reviewed contract](#b0006) |
| [B0007 · 16–17](../../../../../../include/crown/runtime/workload_statistics.hpp#L16) | Type/record definition: enum class Role |  · [reviewed contract](#b0007) |
| [B0008 · 18–33](../../../../../../include/crown/runtime/workload_statistics.hpp#L18) | Type/record definition: struct Descriptor | returns input_scope==InputScope::physical_table?std::optional&lt;TableId&gt;{{table}}:std::nullopt · [reviewed contract](#b0008) |
| [B0009 · 34–39](../../../../../../include/crown/runtime/workload_statistics.hpp#L34) | Type/record definition: struct Options |  · [reviewed contract](#b0009) |
| [B0010 · 40–42](../../../../../../include/crown/runtime/workload_statistics.hpp#L40) | Explanatory comments or spacing. | source comment (unverified): // Numeric payload; snapshots expose only const spans. Histogram population is · [reviewed contract](#b0010) |
| [B0011 · 43–55](../../../../../../include/crown/runtime/workload_statistics.hpp#L43) | Type/record definition: struct Cell | source comment (unverified): // Numeric payload; snapshots expose only const spans. Histogram population is · [reviewed contract](#b0011) |
| [B0012 · 56–61](../../../../../../include/crown/runtime/workload_statistics.hpp#L56) | Type/record definition: struct Metadata |  · [reviewed contract](#b0012) |
| [B0013 · 62–65](../../../../../../include/crown/runtime/workload_statistics.hpp#L62) | Type/record definition: struct Memory |  · [reviewed contract](#b0013) |
| [B0014 · 66–73](../../../../../../include/crown/runtime/workload_statistics.hpp#L66) | Type/record definition: struct ModeFacts |  · [reviewed contract](#b0014) |
| [B0015 · 74–79](../../../../../../include/crown/runtime/workload_statistics.hpp#L74) | Type/record definition: struct Stamp |  · [reviewed contract](#b0015) |
| [B0016 · 80–80](../../../../../../include/crown/runtime/workload_statistics.hpp#L80) | Type/record definition: enum class Availability |  · [reviewed contract](#b0016) |
| [B0017 · 81–83](../../../../../../include/crown/runtime/workload_statistics.hpp#L81) | Type/record definition: enum class DenominatorScope |  · [reviewed contract](#b0017) |
| [B0018 · 84–88](../../../../../../include/crown/runtime/workload_statistics.hpp#L84) | Type/record definition: struct Fraction |  · [reviewed contract](#b0018) |
| [B0019 · 89–97](../../../../../../include/crown/runtime/workload_statistics.hpp#L89) | declares namespace scope; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Factory-produced owning handle. The private immutable payload contains only · [reviewed contract](#b0019) |
| [B0020 · 98–98](../../../../../../include/crown/runtime/workload_statistics.hpp#L98) | Callable definition: Snapshot(Snapshot&& value) noexcept :data_(value.data_) | calls data_; source comment (unverified): // Copy-like moves keep both factory-produced handles readable. · [reviewed contract](#b0020) |
| [B0021 · 99–99](../../../../../../include/crown/runtime/workload_statistics.hpp#L99) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0021) |
| [B0022 · 100–100](../../../../../../include/crown/runtime/workload_statistics.hpp#L100) | Callable definition: Snapshot& operator=(Snapshot&& value) noexcept | returns *this · [reviewed contract](#b0022) |
| [B0023 · 101–126](../../../../../../include/crown/runtime/workload_statistics.hpp#L101) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // input_share uses ALL committed physical inputs. Detail event means use · [reviewed contract](#b0023) |
| [B0024 · 127–127](../../../../../../include/crown/runtime/workload_statistics.hpp#L127) | Callable definition: \[\[nodiscard\]\] Availability arrival_per_second() const noexcept | calls ; returns Availability::unavailable · [reviewed contract](#b0024) |
| [B0025 · 128–132](../../../../../../include/crown/runtime/workload_statistics.hpp#L128) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0025) |
| [B0026 · 133–133](../../../../../../include/crown/runtime/workload_statistics.hpp#L133) | Callable definition: explicit Snapshot(std::shared_ptr&lt;const Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0026) |
| [B0027 · 134–136](../../../../../../include/crown/runtime/workload_statistics.hpp#L134) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime::workload · [reviewed contract](#b0027) |

## B0001

[Lines 1–10](../../../../../../include/crown/runtime/workload_statistics.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose workload statistics without conflating optional observation clocks. |
| inputs / outputs | Includes delta types and fixed/span/vector support; forwards QuerySession and defines U64. |
| invariants | C01 hooks use numeric counters and read no clocks; independent O07 may still be timed. |
| ownership | No live collector or report owner created by inclusion. |
| failure | Compile-time declarations only. |
| cost | No runtime work at inclusion; report factories allocate explicitly. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 11–11](../../../../../../include/crown/runtime/workload_statistics.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Kind { physical, occurrence, support, degree, logical };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify workload population kind. |
| inputs / outputs | physical/occurrence/support/degree/logical selects root or event population. |
| invariants | Kinds do not make counts from distinct populations interchangeable. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 12–12](../../../../../../include/crown/runtime/workload_statistics.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Operation { insert, erase };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify initiating set operation. |
| inputs / outputs | insert/erase label an actual physical or logical input stratum. |
| invariants | Event transition direction may differ and uses event_operation separately. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 13–13](../../../../../../include/crown/runtime/workload_statistics.hpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L13:sha256:64e99942351dcdf329f877cb55315075a81def0be1ebaeaea1b3ec38315978a8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`enum class Mode\`: Timed collection is deliberately not implemented. These modes read no clocks. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/workload_statistics.hpp:L14; use that declaration for the actual input/output shape. |
| invariants | The source note states: Timed collection is deliberately not implemented. These modes read no clocks. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Timed collection is deliberately not implemented. These modes read no clocks. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/statistics.md](../../../../../statistics.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0005

[Lines 14–14](../../../../../../include/crown/runtime/workload_statistics.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Mode { off, counters };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select optional C01 counter collection. |
| inputs / outputs | off or counters; default off. |
| invariants | Neither mode reads clocks; timed collection is deliberately absent. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 15–15](../../../../../../include/crown/runtime/workload_statistics.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class InputScope { physical_table, logical_epoch };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish physical input and logical epoch scope. |
| inputs / outputs | physical_table permits actual initiating TableId; logical_epoch has none. |
| invariants | Logical-only observations cannot supply physical-input denominators. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 16–17](../../../../../../include/crown/runtime/workload_statistics.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Role { input, adapter, derivation, survivor, parent_support, visible_support,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the actual instrumented workload role. |
| inputs / outputs | input/adapter/derivation/survivor/parent/visible/native_touched_degree/generalized_probe roles. |
| invariants | Bucket degree observes one actual child event; generalized probe is a separate 0/1 presence observation, not a reverse-index degree. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 18–33](../../../../../../include/crown/runtime/workload_statistics.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Descriptor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one plan-derived workload stratum. |
| inputs / outputs | Fixed Kind/table/scope/operation/InputScope/Role and optional native node/occurrence/edge/index/event-operation IDs; default equality compares all. |
| invariants | Runtime State validates dense actual IDs/routes. Publicly editable Descriptor fields alone cannot mint immutable Snapshot authority. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::optional<TableId> initiating_table() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a physical initiating table only for physical scope. |
| inputs / outputs | Returns TableId{table} when input_scope==physical_table, otherwise nullopt. |
| invariants | Does not validate that this numeric table belongs to a catalog; factory routes establish that. |
| ownership | Only the named inline values are read/copied/mutated; no input backing is retained. State receivers keep their already admitted metadata/account unchanged. |
| failure | No throwing operation or exception translation. Guards, when present, have exactly the behavior described above. |
| cost | O(1) optional scalar construction, no allocation/clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const Descriptor&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every descriptor identity field. |
| inputs / outputs | Default equality compares tags, table/scope and all optional IDs. |
| invariants | Structural equality is not a current-owner/freshness check. |
| ownership | Only the named inline values are read/copied/mutated; no input backing is retained. State receivers keep their already admitted metadata/account unchanged. |
| failure | No throwing operation or exception translation. Guards, when present, have exactly the behavior described above. |
| cost | Bounded fixed field comparison, no allocation/clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0009

[Lines 34–39](../../../../../../include/crown/runtime/workload_statistics.hpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Options {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry finite C01 route/detail admission settings. |
| inputs / outputs | mode off; max_cells 4096; period 1, offset 0, detail_budget 65536; equality compares all. |
| invariants | Configure validates mode/period/offset and admits complete strata at a quiescent barrier; attempts use zero-based ordinal modulo, including retries/aborts/no-ops. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const Options&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare full collection options. |
| inputs / outputs | Default equality compares mode/max_cells/period/offset/detail_budget. |
| invariants | Equal options do not imply equal reset/configuration/segment generations or observed intervals. |
| ownership | Only the named inline values are read/copied/mutated; no input backing is retained. State receivers keep their already admitted metadata/account unchanged. |
| failure | No throwing operation or exception translation. Guards, when present, have exactly the behavior described above. |
| cost | Bounded scalar comparison, no allocation/clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0010

[Lines 40–42](../../../../../../include/crown/runtime/workload_statistics.hpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L42:sha256:c7b639cad5281256615483ff0425a4afa36c4009ade5040f8569f13aaa44e7b6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct Cell\`: Numeric payload; snapshots expose only const spans. Histogram population is event after-values (support) or one actual child-event degree (degree). Bin 0 is zero; bins 1..64 are \[2^(b-1),2^b-1\]. Empty extrema are unavailable. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/workload_statistics.hpp:L43; use that declaration for the actual input/output shape. |
| invariants | The source note states: Numeric payload; snapshots expose only const spans. Histogram population is event after-values (support) or one actual child-event degree (degree). Bin 0 is zero; bins 1..64 are \[2^(b-1),2^b-1\]. Empty extrema are unavailable. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/statistics.md](../../../../../statistics.md), [docs/memory_reports.md](../../../../../memory_reports.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0011

[Lines 43–55](../../../../../../include/crown/runtime/workload_statistics.hpp#L43); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Cell {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one fixed numeric workload population cell. |
| inputs / outputs | Root input/change/no-op/sample counts; detail route/support crossings; 65 log2 bins, count/sum/min/max and saturation. |
| invariants | Root complete_detail_inputs includes committed selected untruncated no-ops. Support histogram counts event after-values including zero, not current-key census; empty extrema are unavailable. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed 65-bin storage/copy/equality; observe O(1) fixed-width bin computation, merge/equality visit all 65 bins. No heap allocation/clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void observe(U64) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe one event value in a capped numeric histogram. |
| inputs / outputs | Value increments selected bin/count/sum, initializes or updates min/max and saturates overflowing numeric fields. |
| invariants | Bin0 is zero; bin b in 1..64 covers \[2^(b-1),2^b-1\]. Repeated event values count repeatedly. |
| ownership | Mutates this inline Cell only. |
| failure | noexcept; overflow is visible saturation rather than exception. |
| cost | O(1) word-width bit computation and fixed scalar updates; no allocation/clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void merge(const Cell&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Merge a completed numeric sample into committed/history cell. |
| inputs / outputs | Adds every scalar/bin with saturation; combines extrema only when other.count is nonzero. |
| invariants | Saturation propagates, including from the other cell; no partial sample publication is implied by calling this low-level primitive alone. |
| ownership | Mutates this Cell, reads other synchronously; retains no reference. |
| failure | noexcept; capped arithmetic records lower bounds. |
| cost | 65-bin loop plus fixed counters/extrema, independent of row count; no allocation/clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const Cell&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare complete numeric Cell payloads. |
| inputs / outputs | Default equality compares all counters, bins, extrema and saturation. |
| invariants | Equal values do not establish equal collection intervals or owner identity. |
| ownership | Only the named inline values are read/copied/mutated; no input backing is retained. State receivers keep their already admitted metadata/account unchanged. |
| failure | No throwing operation or exception translation. Guards, when present, have exactly the behavior described above. |
| cost | Fixed 65-bin comparison and scalar fields; no allocation/clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0012

[Lines 56–61](../../../../../../include/crown/runtime/workload_statistics.hpp#L56); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Metadata {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe workload attempt and collector-quality metadata. |
| inputs / outputs | Attempts/commits/aborts/selection/complete/truncation, guard/detail/clear/merge actions and four degradation flags. |
| invariants | Complete counts only committed selected untruncated attempts; aborted detail never merges. Invalid descriptor/protocol/ordinal flags can degrade ratios despite visible numeric counters. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0013

[Lines 62–65](../../../../../../include/crown/runtime/workload_statistics.hpp#L62); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Memory {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe component capacity payload, separate from total account memory. |
| inputs / outputs | object/descriptors/committed/attempt/previous/retained/routes byte counters report collector capacity payload. |
| invariants | Excludes caller-retained report arrays, allocator framing/rounding, engine storage and temporary old/new overlap. Never use it as total requested bytes or RSS evidence. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0014

[Lines 66–73](../../../../../../include/crown/runtime/workload_statistics.hpp#L66); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ModeFacts {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain requested/resolved execution-mode facts for an interval. |
| inputs / outputs | delta_owner, requested/resolved DeltaMode/Completion, live policy and view; equality compares all. |
| invariants | Mode rotation keeps prior interval separate. Matching mode fields alone do not establish owner/epoch/interval binding. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
bool operator==(const ModeFacts&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all workload mode facts. |
| inputs / outputs | Default equality compares delta-owner, requested/resolved modes and completion, live policy and view. |
| invariants | Comparison is used as model compatibility metadata; it does not prove calibrated timing validity. |
| ownership | Only the named inline values are read/copied/mutated; no input backing is retained. State receivers keep their already admitted metadata/account unchanged. |
| failure | No throwing operation or exception translation. Guards, when present, have exactly the behavior described above. |
| cost | Bounded fixed-field comparison; no allocation/clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0015

[Lines 74–79](../../../../../../include/crown/runtime/workload_statistics.hpp#L74); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Stamp {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify a captured workload interval with capped-generation markers. |
| inputs / outputs | Actual SupportOwnerId, committed/start epochs, reset/configuration generation, segment, format version and three saturation flags. |
| invariants | Use the complete unsaturated tuple; segment restarts across configure/reset. This stamp is not a durable sequence or an automatic live freshness check. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0016

[Lines 80–80](../../../../../../include/crown/runtime/workload_statistics.hpp#L80); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Availability { disabled, unavailable, exact, sampled, incomplete, lower_bound };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Qualify workload detail observations. |
| inputs / outputs | disabled/unavailable/exact/sampled/incomplete/lower_bound describes the current captured counts. |
| invariants | Sampled is deterministic observed data, not random-sample confidence; lower-bound raw counts cannot form meaningful capped ratios. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0017

[Lines 81–83](../../../../../../include/crown/runtime/workload_statistics.hpp#L81); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class DenominatorScope { unavailable, all_committed_physical_inputs,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify the actual denominator population of a ratio. |
| inputs / outputs | Unavailable, all committed physical, matching stratum/complete-detail-sample stratum, observed support changes or visited routes. |
| invariants | Denominators from different scopes are not interchangeable with global query result cardinality. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Constant-size tag; no runtime allocation, work scan or clock. Invalid casts are not automatically checked by this declaration. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0018

[Lines 84–88](../../../../../../include/crown/runtime/workload_statistics.hpp#L84); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fraction {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry an unreduced observed count fraction and its scope. |
| inputs / outputs | Raw numerator/denominator plus Availability and DenominatorScope; defaults unavailable/zero. |
| invariants | Inspect availability/scope; zero denominators and capped participating counts yield unavailable, never divide blindly or infer a future rate. |
| ownership | The caller owns all inline scalar/enum/optional/fixed-array members; this record alone retains no backing storage or runtime. |
| failure | This value declaration performs no validation or failure translation. Admission/consumer checks run separately before facts are accepted. |
| cost | Fixed-size value construction/copy/comparison; no dynamic allocation, clocks, scans or retained heap owner. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0019

[Lines 89–97](../../../../../../include/crown/runtime/workload_statistics.hpp#L89); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Snapshot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a factory-produced immutable workload snapshot. |
| inputs / outputs | State/QuerySession factories provide private Data containing plan metadata, numeric arrays and interval facts; accessors/ratios expose const reads. |
| invariants | No rows, runtime pointer or pins; later configure/reset/updates cannot rewrite an earlier immutable Data object. Factory construction, not public DTO labels, establishes authority. |
| ownership | Shared_ptr retains Data, its actual plan/account and copied descriptor/current/prior arrays. Ordinary copies and explicit copy-like moves share payload; views borrow this ownership. |
| failure | Factory allocation can throw before return. Once factory-created, copies/moves/accessors are noexcept; last release can free arrays/control/plan metadata. |
| cost | Factory snapshot allocates/copies O(D) cells/descriptors; handle copies refcount only. Detail/ratio functions have their separate O(D) scans. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/workload_statistics_detail.hpp](../../../../../../src/runtime/workload_statistics_detail.hpp) |

```text
Snapshot(const Snapshot&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy-share immutable workload snapshot Data. |
| inputs / outputs | Default noexcept copy constructor retains the same Data. |
| invariants | Both handles read identical immutable interval facts. |
| ownership | Retains existing Data/account/plan; no array deep copy or runtime ownership. |
| failure | noexcept. |
| cost | O(1) shared refcount, no fresh payload; final release deallocates trivial descriptor/cell arrays and may release a last plan graph. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0020

[Lines 98–98](../../../../../../include/crown/runtime/workload_statistics.hpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Snapshot(Snapshot&& value) noexcept :data_(value.data_) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move-share a workload snapshot without invalidating the source. |
| inputs / outputs | Constructor copies value.data_ rather than moving it. |
| invariants | Both factory-produced handles remain readable after this explicit copy-like move. |
| ownership | Shared Data/account ownership is retained in both. |
| failure | noexcept. |
| cost | O(1) refcount; no array allocation/copy. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0021

[Lines 99–99](../../../../../../include/crown/runtime/workload_statistics.hpp#L99); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Snapshot& operator=(const Snapshot&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy-assign shared immutable workload snapshot Data. |
| inputs / outputs | Destination adopts the source shared_ptr. |
| invariants | Source remains readable; destination views into old Data require another retaining handle to remain valid. |
| ownership | Shares new Data and releases old Data, possibly its last arrays/control/plan owner. |
| failure | noexcept. |
| cost | O(1) refcount assignment plus deallocation of old trivial arrays/control and possible last plan-graph teardown; no new payload or mandatory cell scan. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0022

[Lines 100–100](../../../../../../include/crown/runtime/workload_statistics.hpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Snapshot& operator=(Snapshot&& value) noexcept { data_=value.data_; return *this; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move-assign a workload snapshot while keeping both handles readable. |
| inputs / outputs | Copies value.data_ into destination and returns *this. |
| invariants | Explicit copy-like move differs from standard moved-from-null shared-handle classes. |
| ownership | New Data shared; old last Data can be destroyed. |
| failure | noexcept. |
| cost | O(1) refcount plus actual old-owner release; no deep copy/allocation. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0023

[Lines 101–126](../../../../../../include/crown/runtime/workload_statistics.hpp#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const CompiledProgram& plan() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow workload snapshot admitted plan. |
| inputs / outputs | Returns const CompiledProgram& from immutable Data. |
| invariants | Plan metadata owns actual source/catalog/layout identity; not a runtime pointer. |
| ownership | Caller retains a Snapshot sharing this Data; a returned reference/span does not retain Data by itself. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const Stamp& stamp() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow workload snapshot interval stamp. |
| inputs / outputs | Returns const Stamp& from immutable Data. |
| invariants | Compare complete stamp and saturation before treating interval labels as unique. |
| ownership | Caller retains a Snapshot sharing this Data; a returned reference/span does not retain Data by itself. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const Options& options() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow workload snapshot collection settings. |
| inputs / outputs | Returns const Options& from immutable Data. |
| invariants | Settings describe this captured interval, not later reconfiguration. |
| ownership | Caller retains a Snapshot sharing this Data; a returned reference/span does not retain Data by itself. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const ModeFacts& modes() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow workload snapshot current interval modes. |
| inputs / outputs | Returns const ModeFacts& from immutable Data. |
| invariants | Mode facts belong to the current stored interval. |
| ownership | Caller retains a Snapshot sharing this Data; a returned reference/span does not retain Data by itself. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const ModeFacts& previous_modes() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow workload snapshot previous interval modes. |
| inputs / outputs | Returns const ModeFacts& from immutable Data. |
| invariants | Interpret together with has_previous and previous interval endpoints. |
| ownership | Caller retains a Snapshot sharing this Data; a returned reference/span does not retain Data by itself. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::span<const Descriptor> descriptors() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow workload snapshot descriptor list. |
| inputs / outputs | Returns span&lt;const Descriptor&gt; from immutable Data. |
| invariants | Descriptors align positionally with current/previous cells. |
| ownership | Caller retains a Snapshot sharing this Data; a returned reference/span does not retain Data by itself. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::span<const Cell> cells() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow workload snapshot committed current cells. |
| inputs / outputs | Returns span&lt;const Cell&gt; from immutable Data. |
| invariants | Pending runtime work never exposes staged cells here. |
| ownership | Caller retains a Snapshot sharing this Data; a returned reference/span does not retain Data by itself. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::span<const Cell> previous_cells() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow workload snapshot previous interval cells. |
| inputs / outputs | Returns span&lt;const Cell&gt; from immutable Data. |
| invariants | Check has_previous before interpreting prior interval content. |
| ownership | Caller retains a Snapshot sharing this Data; a returned reference/span does not retain Data by itself. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const Metadata& metadata() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow workload snapshot current metadata. |
| inputs / outputs | Returns const Metadata& from immutable Data. |
| invariants | Attempt diagnostics and committed count populations remain distinct. |
| ownership | Caller retains a Snapshot sharing this Data; a returned reference/span does not retain Data by itself. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const Metadata& previous_metadata() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow workload snapshot previous metadata. |
| inputs / outputs | Returns const Metadata& from immutable Data. |
| invariants | Metadata belongs to prior segment, not current counts. |
| ownership | Caller retains a Snapshot sharing this Data; a returned reference/span does not retain Data by itself. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] const Memory& memory() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow workload snapshot collector payload accounting. |
| inputs / outputs | Returns const Memory& from immutable Data. |
| invariants | This excludes the snapshot own copied arrays/control and total account framing. |
| ownership | Caller retains a Snapshot sharing this Data; a returned reference/span does not retain Data by itself. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] bool pending() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read workload snapshot pending. |
| inputs / outputs | Returns the stored boolean/epoch by value. |
| invariants | True means runtime/session has private state; returned counters are still committed-only. |
| ownership | Independent scalar; Snapshot retains backing Data during the call. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] bool has_previous() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read workload snapshot has_previous. |
| inputs / outputs | Returns the stored boolean/epoch by value. |
| invariants | Indicates whether a prior mode interval is stored. |
| ownership | Independent scalar; Snapshot retains backing Data during the call. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] bool replaced_history() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read workload snapshot replaced_history. |
| inputs / outputs | Returns the stored boolean/epoch by value. |
| invariants | Indicates that a newer rotation replaced older retained interval history. |
| ownership | Independent scalar; Snapshot retains backing Data during the call. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] U64 previous_interval_start_epoch() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read workload snapshot previous_interval_start_epoch. |
| inputs / outputs | Returns the stored boolean/epoch by value. |
| invariants | Prior interval beginning; use only together with has_previous and full stamp. |
| ownership | Independent scalar; Snapshot retains backing Data during the call. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] U64 previous_interval_end_epoch() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read workload snapshot previous_interval_end_epoch. |
| inputs / outputs | Returns the stored boolean/epoch by value. |
| invariants | Prior interval end; not an independent durable timestamp. |
| ownership | Independent scalar; Snapshot retains backing Data during the call. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Availability detail_availability() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assess current detail completeness without inventing a rate. |
| inputs / outputs | Mode off→disabled; metadata/cell saturation→lower_bound; committed truncation/degradation→incomplete; period1 exact else sampled. |
| invariants | Does not itself reject pending or saturated interval-generation stamps; consumers such as cost::features add those authority checks. |
| ownership | Reads immutable current arrays; no allocations or live runtime access. |
| failure | noexcept; all factory array sizes are valid. |
| cost | O(D) cell saturation scan worst case; no allocation/clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Fraction input_share(std::size_t descriptor) const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute one physical stratum share of all committed physical inputs. |
| inputs / outputs | Valid physical descriptor returns its inputs over the sum of every physical descriptor inputs; invalid/nonphysical returns unavailable. |
| invariants | Includes changed and no-op committed inputs; zero denominator or saturated participating cells disables ratio. Metadata route degradation marks incomplete. |
| ownership | Reads immutable arrays; returns independent raw Fraction. |
| failure | noexcept; checked descriptor bounds and capped denominator arithmetic. |
| cost | O(D) denominator scan each call; no allocation or clock. Repeated all-root calls can cost O(D²). |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Fraction events_per_physical_input(std::size_t descriptor) const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute observed events per matching physical input stratum. |
| inputs / outputs | Select numerator by kind; locate matching physical table/op root; physical uses base.inputs, detail uses base.complete_detail_inputs. |
| invariants | Detail mean excludes aborted/truncated attempts but includes selected no-ops. Logical-only scope, absent root, zero/capped counts make it unavailable; no population expansion. |
| ownership | Reads borrowed arrays; returns fixed Fraction. |
| failure | noexcept; checks ID/scope and root presence. |
| cost | O(D) root search plus O(D) detail availability for nonphysical kinds; no allocation/clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Fraction crossing_fraction(std::size_t descriptor) const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute observed support presence-crossing fraction. |
| inputs / outputs | Support descriptor: (zero_to_positive+positive_to_zero)/changes; other IDs/kinds unavailable. |
| invariants | Caps/zero denominator disable ratio; detail availability qualifies uncapped counts. Population is observed changed support events, not live keys. |
| ownership | Reads immutable data; fixed result. |
| failure | noexcept, checked ID/kind and overflow. |
| cost | O(D) detail availability scan when usable; otherwise O(1). No allocation/clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] Fraction adapter_selectivity(std::size_t descriptor) const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute adapter acceptance over observed visited routes. |
| inputs / outputs | Occurrence descriptor returns accepted/visited and observed_visited_routes scope. |
| invariants | Zero/capped counts unavailable; deterministic sampled detail does not establish future selectivity. |
| ownership | Reads immutable arrays; fixed result. |
| failure | noexcept, checked ID/kind. |
| cost | O(D) detail availability when usable; otherwise O(1), no allocation/clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0024

[Lines 127–127](../../../../../../include/crown/runtime/workload_statistics.hpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Availability arrival_per_second() const noexcept { return Availability::unavailable; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decline a wall-clock arrival-rate claim. |
| inputs / outputs | Always returns Availability::unavailable. |
| invariants | C01 has no clock or active-time interval. |
| ownership | Returns independent enum, retains nothing. |
| failure | For the stated live/readable object this noexcept accessor cannot fail. Borrowed references/views do not extend backing lifetime. |
| cost | O(1) member lookup/view construction; no allocation or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0025

[Lines 128–132](../../../../../../include/crown/runtime/workload_statistics.hpp#L128); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Snapshot with_pending() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a workload snapshot with a private-state marker. |
| inputs / outputs | Only State/QuerySession friends can call; allocate copied Data on data_-&gt;plan.account(), set pending=true and return new handle. |
| invariants | Original immutable snapshot remains unchanged. This is a deep-copy operation despite changing only one flag. |
| ownership | Copies descriptor/current/previous arrays and retains plan; receiving native account is the same original account, capture/1. |
| failure | Allocation failure frees unpublished copy; source/live committed collector unchanged. |
| cost | O(D) arrays allocation/copy plus old/new report overlap; no row scan or clock. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp) |

## B0026

[Lines 133–133](../../../../../../include/crown/runtime/workload_statistics.hpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Snapshot(std::shared_ptr<const Data> value) noexcept : data_(std::move(value)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt private factory workload Data ownership. |
| inputs / outputs | Friend supplies shared_ptr&lt;const Data&gt;; private constructor moves it into data_. |
| invariants | No public null/default factory exists; callers require factory-produced readable handles. |
| ownership | Owns shared Data only, not a runtime; retains its actual arrays/plan/account. |
| failure | noexcept pointer move. |
| cost | O(1) ownership transfer; Data construction costs occur earlier. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |

## B0027

[Lines 134–136](../../../../../../include/crown/runtime/workload_statistics.hpp#L134); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the immutable workload payload owner. |
| inputs / outputs | data_ is the only Snapshot member; its incomplete Data is defined in workload_statistics.cpp. |
| invariants | Payload arrays remain fixed after publication. Borrowed spans do not themselves retain it. |
| ownership | Last shared_ptr releases copied arrays/control and plan metadata/account; no rows/pins. |
| failure | Destruction is not an update hook and does not allocate a replacement. |
| cost | Handle storage O(1); final release deallocates three trivial-element arrays/control and any last plan graph. There is no explicit cell scan at release. |
| Design | [include/crown/runtime/workload_statistics.hpp](../../../../../../include/crown/runtime/workload_statistics.hpp), [src/runtime/workload_statistics.cpp](../../../../../../src/runtime/workload_statistics.cpp), [src/runtime/statistics_collection.cpp](../../../../../../src/runtime/statistics_collection.cpp), [docs/statistics.md](../../../../../statistics.md), [docs/code_review.md](../../../../../code_review.md) |
