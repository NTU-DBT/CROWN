# `include/crown/runtime/sql_rows.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/sql_rows.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain Boolean CROWN record/survivor/projected-support state and enumerate current answers from factorized visible relations.

Snapshot SHA-256: `a755e055714a65155c95e07cc4b29c1160d93ac7d090090c42b65eba534bb7a4`. 199 lines partitioned into 23 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../../support_invariants.md), [docs/runtime_support.md](../../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../../result_cursors.md), [docs/epoch_views.md](../../../../../epoch_views.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../../include/crown/runtime/sql_rows.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 10–17](../../../../../../include/crown/runtime/sql_rows.hpp#L10) | Type/record definition: struct Options | source comment (unverified): // One source allowance per replacement, shared by validation, constraints · [reviewed contract](#b0002) |
| [B0003 · 18–23](../../../../../../include/crown/runtime/sql_rows.hpp#L18) | Type/record definition: struct Update | source comment (unverified): // Complete physical row; borrowed until return. · [reviewed contract](#b0003) |
| [B0004 · 24–24](../../../../../../include/crown/runtime/sql_rows.hpp#L24) | Explanatory comments or spacing. | source comment (unverified): // Distinct atomic net command; this is not an ordered transport batch. · [reviewed contract](#b0004) |
| [B0005 · 25–29](../../../../../../include/crown/runtime/sql_rows.hpp#L25) | Type/record definition: struct SourceReplacement | source comment (unverified): // Distinct atomic net command; this is not an ordered transport batch. · [reviewed contract](#b0005) |
| [B0006 · 30–30](../../../../../../include/crown/runtime/sql_rows.hpp#L30) | Type/record definition: struct NetBatch |  · [reviewed contract](#b0006) |
| [B0007 · 31–35](../../../../../../include/crown/runtime/sql_rows.hpp#L31) | Type/record definition: struct Epoch | source comment (unverified): // Full source weight changed, even if every alias filters it. · [reviewed contract](#b0007) |
| [B0008 · 36–37](../../../../../../include/crown/runtime/sql_rows.hpp#L36) | Explanatory comments or spacing. | source comment (unverified): // SQL-presented changes borrow one caller scratch row and the active token. · [reviewed contract](#b0008) |
| [B0009 · 38–42](../../../../../../include/crown/runtime/sql_rows.hpp#L38) | Type/record definition: struct OutputLimits | source comment (unverified): // SQL-presented changes borrow one caller scratch row and the active token. · [reviewed contract](#b0009) |
| [B0010 · 43–46](../../../../../../include/crown/runtime/sql_rows.hpp#L43) | Type/record definition: struct OutputChangeView |  · [reviewed contract](#b0010) |
| [B0011 · 47–52](../../../../../../include/crown/runtime/sql_rows.hpp#L47) | Type/record definition: struct Result | source comment (unverified): // Sharing immutable metadata preserves SQL names/types after owner teardown. · [reviewed contract](#b0011) |
| [B0012 · 53–54](../../../../../../include/crown/runtime/sql_rows.hpp#L53) | Explanatory comments or spacing. | source comment (unverified): // An explicit physical-source image shares immutable complete row storage. · [reviewed contract](#b0012) |
| [B0013 · 55–55](../../../../../../include/crown/runtime/sql_rows.hpp#L55) | Type/record definition: struct SourceEntry | source comment (unverified): // An explicit physical-source image shares immutable complete row storage. · [reviewed contract](#b0013) |
| [B0014 · 56–60](../../../../../../include/crown/runtime/sql_rows.hpp#L56) | Type/record definition: struct SourceSnapshotLimits | source comment (unverified): // Fields and retained string extents are admitted without UTF8 rescanning. · [reviewed contract](#b0014) |
| [B0015 · 61–62](../../../../../../include/crown/runtime/sql_rows.hpp#L61) | Explanatory comments or spacing. | source comment (unverified): // Whole-image load has distinct finite build admissions. Operational · [reviewed contract](#b0015) |
| [B0016 · 63–69](../../../../../../include/crown/runtime/sql_rows.hpp#L63) | Type/record definition: struct RebuildLimits | source comment (unverified): // Whole-image load has distinct finite build admissions. Operational · [reviewed contract](#b0016) |
| [B0017 · 70–73](../../../../../../include/crown/runtime/sql_rows.hpp#L70) | Type/record definition: struct RebuildMetrics |  · [reviewed contract](#b0017) |
| [B0018 · 74–83](../../../../../../include/crown/runtime/sql_rows.hpp#L74) | Type/record definition: struct SourceSnapshot |  · [reviewed contract](#b0018) |
| [B0019 · 84–119](../../../../../../include/crown/runtime/sql_rows.hpp#L84) | declares namespace scope; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime::sql_rows · [reviewed contract](#b0019) |
| [B0020 · 120–131](../../../../../../include/crown/runtime/sql_rows.hpp#L120) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0020) |
| [B0021 · 132–154](../../../../../../include/crown/runtime/sql_rows.hpp#L132) | Type/record definition: class ResultCursor | source comment (unverified): // One owning nullable SQL row per distinct output; DISTINCT emits weight 1. · [reviewed contract](#b0021) |
| [B0022 · 155–190](../../../../../../include/crown/runtime/sql_rows.hpp#L155) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Untrusted physical rows are revalidated through the genuine source and · [reviewed contract](#b0022) |
| [B0023 · 191–199](../../../../../../include/crown/runtime/sql_rows.hpp#L191) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Quiescent, eager and owning: no reader lease or update-path row mirror. · [reviewed contract](#b0023) |

## B0001

[Lines 1–9](../../../../../../include/crown/runtime/sql_rows.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:a5c75dbecd9cbeb0b404f4fbf9dcc65060a35a0f991f1f8c4d52141424ece92c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the frontend nullable SQL cell and aggregate tuple types in runtime::sql_rows. |
| inputs / outputs | Cell is frontend::SqlRowCell; Tuple is aggregate::Tuple. |
| invariants | The aliases denote the original types. A default Tuple is an empty invalid handle, distinct from a valid factory-produced zero-cell Tuple; borrowed cell views require a retained Tuple owner. |
| ownership | Aliasing adds no owner. Every factory-created Tuple retains its account-backed Data; zero-cell tuples skip the separate cell-payload allocation. A default handle owns no Data. |
| failure | Alias declarations have no runtime failure path. |
| cost | Compile-time names only; constructing/copying the aliased values has their normal costs. |
| Design | [include/crown/frontend/sql_rows.hpp §SqlRowCell](../../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/runtime/aggregate.hpp §aggregate::Tuple](../../../../../../include/crown/runtime/aggregate.hpp), [docs/sql_rows_runtime.md §Representation and SQL semantics](../../../../../sql_rows_runtime.md), [src/runtime/aggregate_tuple.cpp §Tuple::copy_of and Tuple::data](../../../../../../src/runtime/aggregate_tuple.cpp) |

## B0002

[Lines 10–17](../../../../../../include/crown/runtime/sql_rows.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L10-L17:sha256:20f04a01bb846f49ffc11c150d965f067ab9a83cc59bfd637ff264d2ad8691a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native policy and source admission limits explicit for both single-row apply and net-batch preparation. |
| inputs / outputs | Native weighted options plus the selected five-domain source-work limit. |
| invariants | One source allowance is used per apply call; one source allowance is shared by every edit, key check and alias in a NetBatch. This allowance is selected logical admissions, not a map-comparison or time bound. The native epoch retains its separate existing grant; exact native uint64 limits apply before DISTINCT/EXISTS. |
| ownership | Value configuration; creates no account/grant itself. |
| failure | The record does not validate; public constructors/methods enforce source/native options. |
| cost | Fixed descriptor/scalar copies. Each invocation constructs its one source allowance; map comparisons, allocator bytes and CPU time are real costs outside selected admissions. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md), include/crown/runtime/sql_rows.hpp:10-17, include/crown/runtime/weighted.hpp:15-34, include/crown/storage/index_work.hpp:10-45, Refactor.md:874-878 |

## B0003

[Lines 18–23](../../../../../../include/crown/runtime/sql_rows.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L23:sha256:c092c82ff00688a2db9a53959134403a32ab0f60fa86e7fe5c0f701a0db179d6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request one complete physical-row weight replacement. |
| inputs / outputs | Contiguous sequence, source ID, borrowed full row and before/after weights. |
| invariants | Before authenticates committed full-row identity; contents do not change inside one replacement. |
| ownership | Cells/text must remain live until synchronous apply returns. |
| failure | Records perform no validation; public methods enforce their contracts. |
| cost | Fixed descriptor/scalar copies; copying owning handles changes reference counts without payload allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0004

[Lines 24–24](../../../../../../include/crown/runtime/sql_rows.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:8761628971e5ec98d198ddd8fad68239f8afb3c5e308e652ae3e527a631abf06
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct SourceReplacement\`: Distinct atomic net command; this is not an ordered transport batch. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/sql_rows.hpp:L25; use that declaration for the actual input/output shape. |
| invariants | The source note states: Distinct atomic net command; this is not an ordered transport batch. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0005

[Lines 25–29](../../../../../../include/crown/runtime/sql_rows.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L29:sha256:6834b8dddb381fa34478a3dce6db82fa70eed420fc2080b8eb5d42b2e6c46c06
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one expected-weight link for a complete physical source row inside a net batch. |
| inputs / outputs | Source table ID, borrowed complete nullable row, and before/after uint64 weights; repeated equal source/full-row identities are ordered links. |
| invariants | The first before must equal the committed ledger; each later before must equal the prior proposed after. The span carries no schema, constraint, native-source, or proof authority. |
| ownership | The row and its text borrow only through synchronous prepare_batch return. The value type retains no input storage. |
| failure | The record does not validate. prepare_batch rejects bad source IDs, arity/domain, chain mismatches, resource limits, constraints, or native staging before returning a token. |
| cost | Fixed descriptors; copying a span does not copy its row/text bytes. Runtime validation and any new tuple freezing have separate actual costs. |
| Design | include/crown/runtime/sql_rows.hpp:25, [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), Refactor.md:874-878 |

## B0006

[Lines 30–30](../../../../../../include/crown/runtime/sql_rows.hpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L30:sha256:f900401bd50bbfabc9a4fd53ef46e9c82bab203c14d1644dc2da89b23c9bc615
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request one atomic source net transaction at one logical sequence. |
| inputs / outputs | One sequence plus a borrowed contiguous span of SourceReplacement entries; prepare_batch returns one move-only PreparedBatch. |
| invariants | This is not an ordered transport batch of observable events. Input order is used only to authenticate exact per-row expected-weight chains; only each row’s final weight participates in constraint/native preparation and no intermediate result is published. |
| ownership | The replacement span and every nested row span are borrowed until prepare_batch returns. No batch/input span is retained. |
| failure | A noncontiguous sequence or invalid replacement rejects the whole preparation. Commit advances one sequence; failure/rollback leaves committed sequence and source/key state unchanged. |
| cost | O(number of edits and validated row widths) input work plus touched-state, constraint, alias, and native preparation. One source allowance and one native epoch/grant cover the whole batch. |
| Design | include/crown/runtime/sql_rows.hpp:30, include/crown/runtime/weighted.hpp:286-287, src/runtime/weighted.cpp:663-674, Refactor.md:874-878 |

## B0007

[Lines 31–35](../../../../../../include/crown/runtime/sql_rows.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L35:sha256:c180127f1e725f12f80f0aecbf666bf98bce248bc2bdf3dd7e87cdaef09a9bc1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report one committed single-row update or committed net-batch source/native effects. |
| inputs / outputs | Source changed flag, cumulative source admissions for that invocation, and the native weighted Epoch. |
| invariants | For apply, changed compares one source before/after; for a batch it compares each consolidated final row against committed state. A filtered source change may have no native change. Successful empty/no-op batches still commit one sequence. |
| ownership | Moves native Epoch and optional owning journal/capture handles; does not capture a full source/result snapshot. |
| failure | Record itself is passive; apply/PreparedBatch public operations enforce sequence and preparation/commit contracts. |
| cost | Fixed descriptors/counters plus moves of returned native ownership; source_work reports one invocation’s selected admissions, not each edit as a separate grant. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md), include/crown/runtime/sql_rows.hpp:31-37, src/runtime/sql_rows.cpp:409-415, include/crown/runtime/weighted.hpp:228-249 |

## B0008

[Lines 36–37](../../../../../../include/crown/runtime/sql_rows.hpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L37:sha256:ceecc82a24f963538ec28da2a4069f967ad953922521714622baa28e1c3fbe74
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document borrowed SQL output and the single token-wide decode allowance. |
| inputs / outputs | Human-readable comment only; no runtime arguments or result. |
| invariants | The comment describes the adjacent code; it performs no check or state transition. |
| ownership | No runtime storage, borrow or owner is created. |
| failure | No executable failure or handler. |
| cost | No executable cost. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../../Refactor.md) |

## B0009

[Lines 38–42](../../../../../../include/crown/runtime/sql_rows.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L42:sha256:cfbbb01e3d5f771fc93496203b74aea44a1b3f85de9af77fd9baa006672eb093
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the two fixed prepared-output admission limits and value equality. |
| inputs / outputs | OutputLimits stores uint64 rows=65536 and work=1000000; default equality compares these fields. |
| invariants | The DTO itself neither validates an override nor spends a grant; work denotes selected row/field reads, with serialized bytes charged separately. |
| ownership | Owns two scalar values; construction/copy/equality require no heap storage. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../../Refactor.md) |

## B0010

[Lines 43–46](../../../../../../include/crown/runtime/sql_rows.hpp#L43); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L46:sha256:64d32ea4d3c44b4f72c8674d291b0a8894931db1f4b37547fe42ee9dd0cb5d0f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define a borrowed nullable SQL row change with an exact signed unsigned magnitude. |
| inputs / outputs | OutputChangeView carries span&lt;const Cell&gt; values and weighted::SignedMagnitude change. |
| invariants | The carrier does not validate width, nonzero magnitude or presentation mode. |
| ownership | The span borrows caller scratch and token-backed payloads; the sign/magnitude is a copied value. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../../Refactor.md) |

## B0011

[Lines 47–52](../../../../../../include/crown/runtime/sql_rows.hpp#L47); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L52:sha256:52df37c7a0b5a7e8f5fd3e8c2a205862f64f01a3016e6b6fdd24f99f88620dfe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a complete owning SQL result. |
| inputs / outputs | Nullable tuple, multiplicity and immutable schema handle. |
| invariants | DISTINCT weight is one; EXISTS emits exactly one Boolean row; schema retains names/types after teardown. |
| ownership | Tuple owns bytes; schema shares the admitted program without deep copy. |
| failure | Records perform no validation; public methods enforce their contracts. |
| cost | Fixed descriptor/scalar copies; copying owning handles changes reference counts without payload allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../../sql_rows.md), [Refactor.md §W05](../../../../../../Refactor.md) |

## B0012

[Lines 53–54](../../../../../../include/crown/runtime/sql_rows.hpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L54:sha256:08d6e5e28ec22a64fee52e6d6ffab17ce4499cb1faa014ce8096fde16e9e07a3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct SourceEntry\`: An explicit physical-source image shares immutable complete row storage. It includes filtered/unused tables and retains the real source/native schema. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/sql_rows.hpp:L44; use that declaration for the actual input/output shape. |
| invariants | The source note states: An explicit physical-source image shares immutable complete row storage. It includes filtered/unused tables and retains the real source/native schema. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: An explicit physical-source image shares immutable complete row storage. It includes filtered/unused tables and retains the real source/native schema. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0013

[Lines 55–55](../../../../../../include/crown/runtime/sql_rows.hpp#L55); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L55:sha256:5a488b0abffc6354517bc5a1828b63db9f1c1b6a4df11847bfb28099b06d383c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one distinct complete physical source row and its current multiplicity. |
| inputs / outputs | TableId, immutable nullable Tuple handle and uint64 physical weight form one row entry; output order is source TableId then the source map’s exact tuple order. |
| invariants | One entry represents one currently present physical row regardless of weight. Filtered rows and tables unused by the bound SQL remain represented; weights are not expanded into copies. |
| ownership | The Tuple handle shares its already-owned immutable row payload. A returned image vector can retain the row independently of the runtime and input buffers. |
| failure | This public value record does not validate direct caller construction. The runtime snapshot method emits entries from its previously validated source maps. |
| cost | One vector record and a shared Tuple handle per distinct row; row string payload bytes are not cloned per entry. |
| Design | [include/crown/runtime/sql_rows.hpp](../../../../../../include/crown/runtime/sql_rows.hpp), [include/crown/runtime/aggregate.hpp](../../../../../../include/crown/runtime/aggregate.hpp), [src/runtime/sql_rows.cpp](../../../../../../src/runtime/sql_rows.cpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md) |

## B0014

[Lines 56–60](../../../../../../include/crown/runtime/sql_rows.hpp#L56); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L60:sha256:37fd7926d9433ecd43e49aed877edcdb1564583d9df4a2fae49c277f2370cc16
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound an explicit physical-source image by distinct row count and selected scan work. |
| inputs / outputs | rows limits distinct table/row entries; work_limit supplies cumulative structural-step, scalar-field and scalar-byte admissions. |
| invariants | Scalar fields include nullable cells. scalar_bytes admits retained string extents by size only; it does not rescan UTF8 or represent CPU, payload-copy bytes, pointer slots or link actions. |
| ownership | Caller supplies scalar limits; the snapshot call keeps no reference to the limits object. |
| failure | Exceeding rows reports sql_rows_source_limit; exhausting a selected IndexWork dimension propagates storage::IndexFailure with storage_work_limit before an image is returned. |
| cost | The row cap limits output entries, not summed multiplicity. Work charges table/row/field traversal and string extent; it does not claim an allocator or CPU bound. |
| Design | [include/crown/storage/index_work.hpp](../../../../../../include/crown/storage/index_work.hpp), [include/crown/runtime/sql_rows.hpp](../../../../../../include/crown/runtime/sql_rows.hpp), [src/runtime/sql_rows.cpp](../../../../../../src/runtime/sql_rows.cpp), [tests/unit/sql_source_snapshot_test.cpp](../../../../../../tests/unit/sql_source_snapshot_test.cpp) |

## B0015

[Lines 61–62](../../../../../../include/crown/runtime/sql_rows.hpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L62:sha256:4d5b15b86cd6dd98ad2625e5aa714e4ebe20334f617d52a3ad22883505103105
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document that source rebuild limits are cold-build-only admissions. |
| inputs / outputs | The comment separates row/source/native/indexed/lowering limits from normal \`sql_rows::Options\` and preserves source table/arithmetic domains. |
| invariants | These caps are selected finite-work controls, not map-comparison, CPU, or global allocation bounds. |
| ownership | Documentation adjacent to value limits; no owner. |
| failure | No failure behavior added by the comment. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/sql_rows.hpp](../../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_aggregate_runtime.md §Account and work costs](../../../../../sql_aggregate_runtime.md) |

## B0016

[Lines 63–69](../../../../../../include/crown/runtime/sql_rows.hpp#L63); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L69:sha256:2ea95b0d58dcd8db5349c61124971d60ed6939012637f78ffa301dfed4e54b21
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound the physical seed and its genuine compiler/native construction. |
| inputs / outputs | Limits cover distinct physical entry count, one source-work root, native-work ceiling, optional indexed-work ceiling and finite lowering limits. |
| invariants | indexed_work is required iff the captured native plan is indexed; C=0 image cannot carry rows; operational multiplicity/per-table domains stay bound. |
| ownership | Value-only limits are supplied by the caller; rebuilt storage/account state is separately owned by receiver. |
| failure | Bad option/domain or exhausted work fails before publication. |
| cost | Rows count entries, not expanded bag multiplicity; source work is selected logical admission, indexed work one fixed context, lowering host limits remain distinct. |
| Design | [include/crown/runtime/sql_rows.hpp](../../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_source_images.md §Limits and measured work](../../../../../sql_source_images.md), build/verification/w06-sql-aggregate-cold-rebuild-design-v1/cost-and-lifetime.md:18 |

## B0017

[Lines 70–73](../../../../../../include/crown/runtime/sql_rows.hpp#L70); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L73:sha256:3c6f2fcccc4c6b62947d5b42aff94631961cf199a8546cfb3fc84fbe5ba7d2e3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report selected physical/native/indexed/lowering work for a source rebuild. |
| inputs / outputs | Reports source IndexWork, indexed IndexWork, native logical work and lowerer work. |
| invariants | Zero indexed work on ordered storage does not imply no native work; lowering report excludes compiler DTO/identity/JSON and other existing scopes. |
| ownership | Copied counter values only. |
| failure | Report is assigned after the cold source owner is fully ready. |
| cost | Fixed metric object; fields are not CPU, malloc, or map-comparison counts. |
| Design | [include/crown/runtime/sql_rows.hpp](../../../../../../include/crown/runtime/sql_rows.hpp), [src/runtime/sql_rows.cpp](../../../../../../src/runtime/sql_rows.cpp), [docs/sql_source_images.md §Limits and measured work](../../../../../sql_source_images.md) |

## B0018

[Lines 74–83](../../../../../../include/crown/runtime/sql_rows.hpp#L74); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L83:sha256:7feea997176f22c35571353a622ae4a0c8c1bddeb450f221f6dfd149cf5339d0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an in-memory image of a quiescent SQL physical source owner and its actual native binding inputs. |
| inputs / outputs | Stores committed source sequence, genuine SqlRowsProgram, native CompiledProgram, actual weighted::Binding, selected capture work and complete ordered SourceEntry vector. |
| invariants | The method-produced value includes filtered/unused physical entries and exact row weights. It is observational source data; no import, restore, checkpoint or descriptor-admission API is supplied here. |
| ownership | Program and compiled-program handles share immutable owners; the binding is fixed scalar metadata. The row vector uses the receiving MemoryAccount and row Tuple handles share immutable payload owners. No cursor/read lease is retained. |
| failure | The record type itself performs no input validation and can be modified by its caller. Validity claims apply to values returned by SqlRowsRuntime::source_snapshot. |
| cost | O(R) vector descriptors plus shared row/program handles; physical payload strings are shared rather than copied. The snapshot can keep its memory account alive until its owned handles are released. |
| Design | [include/crown/runtime/sql_rows.hpp](../../../../../../include/crown/runtime/sql_rows.hpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [include/crown/runtime/weighted.hpp](../../../../../../include/crown/runtime/weighted.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp), [src/runtime/sql_rows.cpp](../../../../../../src/runtime/sql_rows.cpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md) |

## B0019

[Lines 84–119](../../../../../../include/crown/runtime/sql_rows.hpp#L84); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L84-L119:sha256:bda52fc76d53614a1c265214a404b7fbc4df6fa1e15d64852ceed2351384ecb5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the SQL runtime and the first part of its move-only prepared-batch API. |
| inputs / outputs | Declare PreparedBatch ownership/active/sequence/source/native preview methods and opt-in output_size/output_change signatures. |
| invariants | Deleted copy and rvalue borrow overloads constrain use; bodies elsewhere enforce active-token state and presentation rules. |
| ownership | PreparedBatch declares an account-owned private handle; returned references/views require the live token, and output cells additionally require caller scratch. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md), [src/runtime/sql_rows.cpp](../../../../../../src/runtime/sql_rows.cpp), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../../Refactor.md) |

```text
[[nodiscard]] bool changed() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the prepared source batch’s normalized physical-weight-change flag. |
| inputs / outputs | Active PreparedBatch returns one bool stored from whether any touched complete source-row key has before != final after. |
| invariants | Includes physical changes even when filtered/unused from every SQL occurrence; a no-op/finally-cancelled net reports false. It says nothing about native output or SQL aggregate group changes. |
| ownership | Scalar read borrows token only for the call; it retains no rows or source owner. |
| failure | Closed/moved token reports invalid_sql_rows_batch before returning. |
| cost | O(1) bool read, no allocation or budget/work charge. |
| Design | [include/crown/runtime/sql_rows.hpp](../../../../../../include/crown/runtime/sql_rows.hpp), [src/runtime/sql_rows.cpp](../../../../../../src/runtime/sql_rows.cpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_aggregate_runtime.md](../../../../../sql_aggregate_runtime.md) |

```text
} // namespace crown::runtime::sql_rows namespace crown::runtime {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep both the source factory and cold implementation bridge at controlled access points. |
| inputs / outputs | The class region places \`rebuild_into\` on the public source runtime and grants the source-private \`detail::SqlColdRebuild\` access to opaque Data. |
| invariants | No public sequence setter, logical bag-fact port, source-map alias or generic mode flag is added. |
| ownership | The runtime handle shares private Data; the internal friend is source-local. |
| failure | Invalid/moved facade and rebuild errors follow existing runtime error boundaries. |
| cost | One static API declaration and one friend; no hot fields. |
| Design | [include/crown/runtime/sql_rows.hpp](../../../../../../include/crown/runtime/sql_rows.hpp), [src/runtime/sql_cold_rebuild.hpp](../../../../../../src/runtime/sql_cold_rebuild.hpp), [docs/sql_source_images.md §Recovery boundary](../../../../../sql_source_images.md) |

## B0020

[Lines 120–131](../../../../../../include/crown/runtime/sql_rows.hpp#L120); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L120-L131:sha256:58fc7e0d4f5cd1e028713ea5ce26096548df2298f94b0844bcfb9fc2048c31aa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete the prepared-batch output, commit, rollback and private-storage declarations. |
| inputs / outputs | Delete rvalue output_change; declare output_work, commit, rollback, private friends/constructor/data() and AccountedUnique&lt;Data&gt;. |
| invariants | These declarations do not decode a row, spend the allowance or publish an epoch. |
| ownership | The private handle owns the token data; borrowed output access is restricted to const lvalues. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [src/runtime/sql_rows.cpp §PreparedBatch::Data](../../../../../../src/runtime/sql_rows.cpp), [src/runtime/sql_rows.cpp §SqlRowsRuntime::prepare_batch](../../../../../../src/runtime/sql_rows.cpp), [docs/sql_rows_batches.md §Usage and visibility](../../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [Refactor.md §8.1, W05-W06](../../../../../../Refactor.md) |

## B0021

[Lines 132–154](../../../../../../include/crown/runtime/sql_rows.hpp#L132); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L132-L154:sha256:4960322590c043ffba16f8233a8b47a8a03d205e6166de5beed0b49e76078b6e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one move-only SQL result reader and its native writer-excluding lease. |
| inputs / outputs | results() creates the cursor; next() returns an optional owning nullable Result with bag multiplicity, DISTINCT weight one, or the one EXISTS Boolean result. state/active/sequence inspect its lifecycle. |
| invariants | Updates remain excluded until terminal next(), cancel() or destruction. A prepared source batch prevents acquiring a new reader. Returned rows are complete SQL presentation values, distinct from native encoded bag-delta previews. |
| ownership | Accounted cursor Data retains the immutable SQL program and native cursor/reader lease. Each yielded Tuple owns its receiving-account payload independently; it survives cursor/runtime teardown. Moving transfers the cursor; cancel/destruction release its lease. |
| failure | Construction failure releases an acquired native lease through RAII. Closed/moved state follows the documented cursor guards; an output-copy failure fails/closes the native cursor. cancel is nonthrowing and idempotent. |
| cost | Fixed facade moves/status reads; acquisition funds Data and output-width scratch plus native cursor setup. next performs actual native traversal, nullable decoding and owning row/string copy under the original receiving account/grant. No complete output history is kept. |
| Design | [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), src/runtime/sql_rows.cpp:417-461 |

## B0022

[Lines 155–190](../../../../../../include/crown/runtime/sql_rows.hpp#L155); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L155-L190:sha256:f532594109d5b2c6a6d9984208dddb4395d6053fb64001edaf107ee4818d101e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare SQL runtime creation, rebuild, mutation, results and source lookup interfaces. |
| inputs / outputs | Declare constructor/create_into/rebuild_into, move-only lifecycle, metadata/scalar getters, apply, prepare_batch, prepare_output_batch, results and source_weight. |
| invariants | Old prepare_batch defaults capture disabled; the opt-in output factory has separate OutputLimits. Source/result/rebuild rules are implemented in their named bodies. |
| ownership | Runtime owns shared private Data; program/native borrows need the retained owner, and prepared tokens retain their SQL owner separately. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | include/crown/runtime/sql_rows.hpp:122, src/runtime/sql_rows.cpp:499-503, src/runtime/weighted.cpp:663-674, include/crown/resource/ownership.hpp:40-74, [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../../Refactor.md) |

```text
explicit SqlRowsRuntime(frontend::SqlRowsProgram, const FreeConnexTree&, const PhysicalOptions& = {}, sql_rows::Options = {});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose whole physical-source reconstruction while keeping all validation in the existing source transaction. |
| inputs / outputs | A real receiver, SourceSnapshot, normal source options, cold rebuild limits and optional work report produce a ready SqlRowsRuntime. |
| invariants | Rows are revalidated as complete physical records through genuine source validation/constraints and one pending native epoch at image.sequence; no live sequence mutator. |
| ownership | The returned owner funds row/key/native state in the receiver. The input snapshot remains caller-owned; its row spans are synchronous during seed preparation only. |
| failure | Failure publishes neither owner nor metrics; pending native epoch rollback is existing RAII. |
| cost | One source grant, one native grant/epoch, one optional fixed indexed lease plus separate lowerer costs; no generic all-work theorem. |
| Design | [include/crown/runtime/sql_rows.hpp](../../../../../../include/crown/runtime/sql_rows.hpp), [src/runtime/sql_rows.cpp](../../../../../../src/runtime/sql_rows.cpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../../sql_rows_batches.md), [docs/sql_source_images.md §Closed cold reconstruction](../../../../../sql_source_images.md), [docs/sql_source_images.md §Recovery boundary](../../../../../sql_source_images.md) |

## B0023

[Lines 191–199](../../../../../../include/crown/runtime/sql_rows.hpp#L191); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L191-L199:sha256:449d91c98364f63ed4badc8ffeaf533576851060b8c4ed8dba1f7f0757a41102
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare explicit source-image export and the runtime private handle boundary. |
| inputs / outputs | Declare source_snapshot(SourceSnapshotLimits={}), SqlColdRebuild friendship, private shared-pointer constructor, data() and data_. |
| invariants | Only explicit source_snapshot performs eager source export; declaring the method does not create an update-path snapshot. |
| ownership | The member is shared_ptr&lt;Data&gt;; actual owning SourceSnapshot is returned only by a later explicit call. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/runtime/sql_rows.hpp](../../../../../../include/crown/runtime/sql_rows.hpp), [src/runtime/sql_rows.cpp](../../../../../../src/runtime/sql_rows.cpp), [include/crown/runtime/weighted.hpp](../../../../../../include/crown/runtime/weighted.hpp), [tests/unit/sql_source_snapshot_test.cpp](../../../../../../tests/unit/sql_source_snapshot_test.cpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/weighted_enumeration.md](../../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../../Refactor.md) |

```text
std::shared_ptr<Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain SqlRowsRuntime's shared implementation state behind the move-only facade. |
| inputs / outputs | create_into supplies account-backed Data; runtime methods operate through data_. |
| invariants | Runtime methods resolve through data_; PreparedBatch::Data can retain the same shared owner after facade movement or destruction. |
| ownership | The shared pointer owns the SQL program/native runtime/source state until final release. |
| failure | data() rejects an empty moved-from facade with invalid_sql_rows_runtime. |
| cost | The field declaration allocates nothing; final release destroys native state and maps with data-dependent cleanup. |
| Design | [src/runtime/sql_rows.cpp §SqlRowsRuntime::create_into](../../../../../../src/runtime/sql_rows.cpp), [src/runtime/sql_rows.cpp §SqlRowsRuntime::PreparedBatch::Data](../../../../../../src/runtime/sql_rows.cpp), [docs/sql_rows_runtime.md §Start at the two public boundaries](../../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md §Usage and visibility](../../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../../query_memory.md) |
