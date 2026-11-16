# `include/crown/runtime/star.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/star.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare finite star ownership, atomic maintenance, exact snapshot cursors and honest work/degree/label gauges.

Snapshot SHA-256: `98f1abc1aae86f5278c3c002a0d1ba0b82897f3daea033a2d3eab220de282653`. 117 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [star](../../../../subsystem_contracts.md#star). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/star.md](../../../../../star.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/runtime/star.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–15](../../../../../../include/crown/runtime/star.hpp#L9) | Type/record definition: struct Options | source comment (unverified): // Original full-source validation/storage grant. · [reviewed contract](#b0002) |
| [B0003 · 16–22](../../../../../../include/crown/runtime/star.hpp#L16) | Type/record definition: struct Metrics | source comment (unverified): // center_visits counts both migration passes; group_visits counts heavy · [reviewed contract](#b0003) |
| [B0004 · 23–28](../../../../../../include/crown/runtime/star.hpp#L23) | Type/record definition: struct Epoch |  · [reviewed contract](#b0004) |
| [B0005 · 29–32](../../../../../../include/crown/runtime/star.hpp#L29) | Type/record definition: struct DimensionState | source comment (unverified): // nullopt: mathematical power exceeds uint64. · [reviewed contract](#b0005) |
| [B0006 · 33–36](../../../../../../include/crown/runtime/star.hpp#L33) | Type/record definition: struct KeyState | source comment (unverified): // present is the real satellite, or true if none exists. · [reviewed contract](#b0006) |
| [B0007 · 37–40](../../../../../../include/crown/runtime/star.hpp#L37) | Type/record definition: struct State |  · [reviewed contract](#b0007) |
| [B0008 · 41–43](../../../../../../include/crown/runtime/star.hpp#L41) | Type/record definition: struct CursorOptions | source comment (unverified): // Shared across this cursor's complete lifetime. · [reviewed contract](#b0008) |
| [B0009 · 44–47](../../../../../../include/crown/runtime/star.hpp#L44) | Type/record definition: struct CursorMetrics |  · [reviewed contract](#b0009) |
| [B0010 · 48–61](../../../../../../include/crown/runtime/star.hpp#L48) | declares types or opens a type body. | source comment (unverified): // Opt-in, initially empty, serial exact-set star owner. It maintains the real · [reviewed contract](#b0010) |
| [B0011 · 62–79](../../../../../../include/crown/runtime/star.hpp#L62) | Type/record definition: public: class Cursor |  · [reviewed contract](#b0011) |
| [B0012 · 80–107](../../../../../../include/crown/runtime/star.hpp#L80) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Original query/schema/comparison authority. Its general execution profile · [reviewed contract](#b0012) |
| [B0013 · 108–117](../../../../../../include/crown/runtime/star.hpp#L108) | Closes surrounding scope/type. | source comment (unverified): // A cursor deduplicates counted per-group head projections. Its quantum is · [reviewed contract](#b0013) |

## B0001

[Lines 1–8](../../../../../../include/crown/runtime/star.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:ceafda441e7f590102d07f9b90f4d9786b3fe293407cae1b4f5d94ad3573afc4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Introduce the public star runtime interface and namespace. |
| inputs / outputs | Planner admission, physical-source and owner-allocator declarations are included for the following API. |
| invariants | This header declares an opt-in backend; including it changes no planner default or query execution. |
| ownership | Declarations acquire no query state; retained owners are created by implementation factories. |
| failure | Normal C++ include/type errors occur at compilation; no runtime handler is introduced. |
| cost | Header parsing and dependent interface instantiation only. |
| Design | [docs/star.md](../../../../../star.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [docs/result_cursors.md](../../../../../result_cursors.md) |

## B0002

[Lines 9–15](../../../../../../include/crown/runtime/star.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L15:sha256:925e1ce60565799c2aaa60a3903697708ebc900a310ba83200e1b0f7029cdff7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate full-source, per-epoch view and one cold metadata-import allowance. |
| inputs / outputs | Options contains PhysicalRuntimeOptions sources, uint64 heavy/light work and five-domain IndexWork metadata_work. |
| invariants | Source and star grants are separate. The original comparison/schema import is capped by genuine indexed plan policy once at construction, never recreated during updates. |
| ownership | Caller options are copied; source creation supplies the original account and the cold work object uses that account. |
| failure | Source, metadata-domain and epoch-work limits retain their actual separate refusal boundaries. |
| cost | Options are fixed data. Source admission, original metadata freeze and actual per-input view work remain separately bounded/measured. |
| Design | [docs/star.md](../../../../../star.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [docs/result_cursors.md](../../../../../result_cursors.md) |

## B0003

[Lines 16–22](../../../../../../include/crown/runtime/star.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L22:sha256:1906dac04550245d2d420eef5a9511ad31f44218bab568bed9f57e22ce2f49e6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe selected star maintenance work by operation branch. |
| inputs / outputs | Metrics exports selected work, real changes, center/group visits, projection changes, relabeled keys/rows and resets. |
| invariants | center_visits includes both migration passes; migrated_rows counts one row per relabeled key; group_visits counts only heavy-satellite reverse-index entries. These are not total CPU/source cost. |
| ownership | A value is accumulated privately for one apply attempt and copied into a successful Epoch. |
| failure | The owning Budget refuses work exhaustion; metrics are not authority to commit a source epoch. |
| cost | Fixed counter storage; each reported visit follows its charged action and distinct counter definition. |
| Design | [docs/star.md](../../../../../star.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [docs/result_cursors.md](../../../../../result_cursors.md) |

## B0004

[Lines 23–28](../../../../../../include/crown/runtime/star.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L28:sha256:51108f97c9bf082c283e4ebbd2c94cd15e76e4046c9b4640aa358c23ddefe2cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report a committed original source epoch and its star maintenance observations. |
| inputs / outputs | Epoch contains input sequence, physical membership change, PhysicalMetrics and Metrics. |
| invariants | A valid no-op still advances source sequence; this object contains no signed query-answer delta. |
| ownership | All fields are copied scalar/metric values and retain no live source row or runtime lease. |
| failure | Only apply after its source/view publication barrier returns an Epoch. |
| cost | Fixed-size result construction; producing the state and metrics is charged elsewhere. |
| Design | [docs/star.md](../../../../../star.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [docs/result_cursors.md](../../../../../result_cursors.md) |

## B0005

[Lines 29–32](../../../../../../include/crown/runtime/star.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L32:sha256:6f12722fe82ea1ae547744b3e12642b82bb4180f36782d23b198268728b418df
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one coordinate H/scale/key census for examination. |
| inputs / outputs | DimensionState reports exact h, epoch scale, positive-degree key count, heavy count and optional threshold. |
| invariants | A missing threshold denotes a mathematical power beyond uint64; it never means wrapped zero. |
| ownership | Fields are standalone scalar copies inside an original-account State vector. |
| failure | Creation follows readable committed-state checks; this report does not revalidate H. |
| cost | Fixed data per coordinate; collecting all coordinates is linear in arity. |
| Design | [docs/star.md](../../../../../star.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [docs/result_cursors.md](../../../../../result_cursors.md) |

## B0006

[Lines 33–36](../../../../../../include/crown/runtime/star.hpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L36:sha256:49ef7088c0607a5bc14315aa3ce27489fb87e9c5f29e068362d3910887a2a2e7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the tracked state of one typed coordinate key. |
| inputs / outputs | KeyState returns degree, heavy label and real/conceptual satellite presence. |
| invariants | A present real satellite may have degree zero; an absent satellite is conceptually true on live center keys. |
| ownership | The result is an optional copied value, not a borrowed key-map address. |
| failure | Runtime::key rejects an out-of-range coordinate; a missing key returns no value. |
| cost | Fixed output after the actual ordered key lookup and scalar comparison. |
| Design | [docs/star.md](../../../../../star.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [docs/result_cursors.md](../../../../../result_cursors.md) |

## B0007

[Lines 37–40](../../../../../../include/crown/runtime/star.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L40:sha256:54cc67ba2bd80e77d9eb1a7af96b42bf3e4edc35d158135f7a31ea6193443182
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a committed star census and its coordinate diagnostics. |
| inputs / outputs | State contains sequence, center/group/live counts and an OwnerAllocator dimension vector. |
| invariants | The scalar census and H/label values belong to the same readable serial boundary. |
| ownership | The vector retains its original query account and may outlive Runtime; no raw key/fact pointer is exported. |
| failure | Capture allocation can fail without changing sources or the maintained view. |
| cost | O(d) copied dimension values and accounted capacity; not a result enumeration. |
| Design | [docs/star.md](../../../../../star.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [docs/result_cursors.md](../../../../../result_cursors.md) |

## B0008

[Lines 41–43](../../../../../../include/crown/runtime/star.hpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L43:sha256:f8a196a87032b57d03890daf161ccc248675ed5e1b62d2f49b1a94dfaa684553
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set one cumulative allowance for a projection cursor. |
| inputs / outputs | CursorOptions carries the uint64 work grant used from construction through active next calls. |
| invariants | The allowance is not reset per output or candidate quantum. |
| ownership | It is a copied caller value retained in private cursor Data. |
| failure | Cursor exhaustion raises star_cursor_work_limit and closes the reader lease. |
| cost | Fixed option storage; cleanup and scalar/container costs remain additional. |
| Design | [docs/star.md](../../../../../star.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [docs/result_cursors.md](../../../../../result_cursors.md) |

## B0009

[Lines 44–47](../../../../../../include/crown/runtime/star.hpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L47:sha256:369aa196710e8a1435bb3b59889358c362aba286f182d7d8de520131f2888a96
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose candidate production and explicit cursor cleanup observations. |
| inputs / outputs | CursorMetrics records work/candidates/duplicates/outputs/group advances, cleanup items and quantum. |
| invariants | The quantum counts candidates; cleanup_items is a separate teardown measure, not a constant-delay claim. |
| ownership | The value is copied out and retained after cursor cancellation without holding the query. |
| failure | The private cursor charges selected work before its counters advance. |
| cost | Fixed-size counters; their populations and underlying traversal costs remain real. |
| Design | [docs/star.md](../../../../../star.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [docs/result_cursors.md](../../../../../result_cursors.md) |

## B0010

[Lines 48–61](../../../../../../include/crown/runtime/star.hpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L61:sha256:415e1b41f562d6a2f50161f378aede7bff270ee91275745be1b42ec8287e142b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the initially-empty exact-set prototype and inherited source/account boundary. |
| inputs / outputs | Class contract describes genuine heavy/light group maintenance and opt-in serial snapshot execution. |
| invariants | No generic join runtime is maintained behind the star view; P2 definitions and local repairs are distinguished. |
| ownership | All native state, journal, cursor and outputs use the original coordinator account. |
| failure | Atomic rollback belongs to the private source/view preparation; the note adds no catch or fallback. |
| cost | Source constraints, compilation, maps and scalar widths retain costs beyond selected star actions. |
| Design | [docs/star.md](../../../../../star.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [docs/result_cursors.md](../../../../../result_cursors.md) |

## B0011

[Lines 62–79](../../../../../../include/crown/runtime/star.hpp#L62); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L79:sha256:81199162c9b6752a4923917273163f1ee68426d347ab85986c59146d2705933c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare a move-only owning result cursor with explicit closure. |
| inputs / outputs | Cursor offers next, cancel and metrics; a private AccountedUnique Data token retains its runtime owner. |
| invariants | A live read lease prevents updates; each distinct output is returned once in unspecified order. |
| ownership | Owning returned tuples survive the cursor/runtime. Moving transfers private state; cancel releases its lease. |
| failure | Construction/next failure discards private scratch and closes the lease; moved/closed next returns null. |
| cost | Quantum production, original-account allocation and linear scratch/last-owner cleanup have separate costs. |
| Design | [docs/star.md](../../../../../star.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [docs/result_cursors.md](../../../../../result_cursors.md) |

## B0012

[Lines 80–107](../../../../../../include/crown/runtime/star.hpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L107:sha256:d2ec6fbe3e970d8e61a540a193ebde9958ce5a90ab55e3d3f889d0d0001deb04
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare star construction, serial updates and immutable/diagnostic read boundaries. |
| inputs / outputs | Runtime constructs from Plan/Options, exposes original program/account references, readiness/existence/sequence, apply/results and diagnostic exports. |
| invariants | program() supplies original query/schema/comparison authority with its GENERAL profile, not a star guarantee. The owner is initially empty and independently serial. |
| ownership | Shared Data owns all native state; cursors may retain it. Borrowed program/account references reject direct temporary access; source_snapshot is a caller DTO. |
| failure | Moved/private/busy update boundaries reject as implemented; native admission/refusal cannot expose partial source/view state. |
| cost | Handle/read operations and actual constructor/maintenance/diagnostic work are distinct; declarations provide no constant wall-clock claim. |
| Design | [docs/star.md](../../../../../star.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [docs/result_cursors.md](../../../../../result_cursors.md) |

## B0013

[Lines 108–117](../../../../../../include/crown/runtime/star.hpp#L108); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L108-L117:sha256:8f05a724b97bc8faa35557e69f34fc47c04ffa8e0351dca9bdc1292b05c71b30
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Qualify the star candidate production and cleanup profile. |
| inputs / outputs | Comment states K=min(center_rows, product_hidden(1+heavy keys)) with empty quantum one and distinct head count j. |
| invariants | Per-group deduplication and heavy-label bounds give O_d((h+1)^(d-j)) selected candidates; full heads use one, not a transferred general runtime profile. |
| ownership | Reader leases retain borrowed projection keys; owning outputs retain independent original-account rows/layouts. |
| failure | Failure closes the cursor; terminal null or cancel releases its lease before updates resume. |
| cost | Ordered comparisons, scalar widths, tuple allocation/copy and O(cursor scratch)/last-owner cleanup are actual additional costs. |
| Design | [docs/star.md](../../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §7](../../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/result_cursors.md](../../../../../result_cursors.md), [docs/query_memory.md](../../../../../query_memory.md) |
