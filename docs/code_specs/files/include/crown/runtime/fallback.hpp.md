# `include/crown/runtime/fallback.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/fallback.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare finite independent exact fallback ownership, owning snapshots, atomic endpoint deltas and explicit materialization costs.

Snapshot SHA-256: `f336c451f58e0404b8ef0acc08dfce564375cf7b1197f6cfeeb3cbb9e5f858bf`. 106 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [fallback](../../../../subsystem_contracts.md#fallback). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/fallback.md](../../../../../fallback.md), [docs/source_images.md](../../../../../source_images.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md](../../../../../../Refactor.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../../include/crown/runtime/fallback.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–16](../../../../../../include/crown/runtime/fallback.hpp#L12) | Type/record definition: struct Limits | source comment (unverified): // Shared metadata/capture/join/dedup/difference admissions. · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../../include/crown/runtime/fallback.hpp#L17) | Type/record definition: struct Options |  · [reviewed contract](#b0003) |
| [B0004 · 18–24](../../../../../../include/crown/runtime/fallback.hpp#L18) | Type/record definition: struct Metrics |  · [reviewed contract](#b0004) |
| [B0005 · 25–30](../../../../../../include/crown/runtime/fallback.hpp#L25) | declares types or opens a type body. | source comment (unverified): // The actual arbitrary original CQ is frozen separately from the genuine · [reviewed contract](#b0005) |
| [B0006 · 31–51](../../../../../../include/crown/runtime/fallback.hpp#L31) | Type/record definition: class Binding | returns bool(data_); source comment (unverified): // The actual arbitrary original CQ is frozen separately from the genuine · [reviewed contract](#b0006) |
| [B0007 · 52–53](../../../../../../include/crown/runtime/fallback.hpp#L52) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 54–54](../../../../../../include/crown/runtime/fallback.hpp#L54) | Type/record definition: struct Snapshot |  · [reviewed contract](#b0008) |
| [B0009 · 55–60](../../../../../../include/crown/runtime/fallback.hpp#L55) | Type/record definition: struct Epoch | source comment (unverified): // Full-source epoch; local support events are not answer deltas. · [reviewed contract](#b0009) |
| [B0010 · 61–68](../../../../../../include/crown/runtime/fallback.hpp#L61) | Type/record definition: struct Explain | source comment (unverified): // Actual committed original physical cardinalities. · [reviewed contract](#b0010) |
| [B0011 · 69–104](../../../../../../include/crown/runtime/fallback.hpp#L69) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Explicit conservative exact-set fallback. One genuine source-only physical · [reviewed contract](#b0011) |
| [B0012 · 105–106](../../../../../../include/crown/runtime/fallback.hpp#L105) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::fallback · [reviewed contract](#b0012) |

## B0001

[Lines 1–11](../../../../../../include/crown/runtime/fallback.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:b2086aa1ffbc16fb4fcc011e12fa16efdf1cb3f39a19c15894913fd01f1dd8b7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the native conservative exact-set fallback using genuine source coordination. |
| inputs / outputs | Includes admitted fallback plan, physical runtime and transferable allocator APIs; aliases the planner Profile. |
| invariants | Original arbitrary CQ metadata is distinct from the empty source-coordinator query. |
| ownership | Inclusion/aliases create no account or owning source rows. |
| failure | No admission or native work is executed by declarations. |
| cost | Compile-time dependencies only; implementation costs remain explicit. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp) |

## B0002

[Lines 12–16](../../../../../../include/crown/runtime/fallback.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L16:sha256:cd0a10a918d9e31a26f6318cec64f9118af385275e22bd5a0e16c72a176f95d2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound a whole wrapper operation, full-source capture and distinct retained result count. |
| inputs / outputs | work defaults to one million; source_rows and rows each default to 65536. |
| invariants | Constructor import/initial answer share one budget; each update shares capture/evaluation/dedup/difference work. |
| ownership | Plain limit values confer neither a new memory owner nor an implicit native indexed grant. |
| failure | Insufficient admissions refuse before publication; source-image errors remain inherited capture errors. |
| cost | Scalar checks only; work units do not bound elapsed time, payload allocation framing or cleanup. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp) |

## B0003

[Lines 17–17](../../../../../../include/crown/runtime/fallback.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:e677cbe379781719c84752c555cbcaeaf78f9efae1761928351f8939e428c174
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine genuine full-source policy with explicit fallback limits. |
| inputs / outputs | Options holds PhysicalRuntimeOptions sources and fallback recompute Limits. |
| invariants | Original catalog/backend/constraint/account ceilings stay bound to the one source owner. |
| ownership | Configuration copies retain no query/result payload. |
| failure | Native constructor policy rejection remains distinct from fallback evaluation refusal. |
| cost | Configuration value copy; source admission and recomputation retain their actual separate work. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp) |

## B0004

[Lines 18–24](../../../../../../include/crown/runtime/fallback.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L24:sha256:990ceae4f0c0148239c94ead158ee3987e69adc59d4fce43f246af41e44e9fd1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the performed capture, prefix matching, projection and endpoint work. |
| inputs / outputs | Metrics distinguishes actual image work/rows, row/term/equality visits, assignments, duplicates and deltas. |
| invariants | Scalar bytes are conservative extents; complete assignments and distinct outputs are separate counts. |
| ownership | Plain diagnostic values own no source image, cursor or borrowed scalar. |
| failure | Failed private operations return no committed Metrics; counters are not refunded inside an operation. |
| cost | Counter work is selected/admitted; comparison bytes, allocator costs and cleanup remain real. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp) |

## B0005

[Lines 25–30](../../../../../../include/crown/runtime/fallback.hpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L30:sha256:e7766320ebaf54188b335af64f8c62d69089ec48d3e7fcb8f7bab5a90bd5296d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the actual-query versus source-only provenance boundary. |
| inputs / outputs | Forward declaration plus Binding lifetime/identity documentation. |
| invariants | The genuine Query{} coordinator profile must not be interpreted as the arbitrary original query guarantee. |
| ownership | Binding retains actual terms/text/schema/profile through immutable account-backed storage. |
| failure | Documentation introduces no executable behavior. |
| cost | No runtime cost or new theorem follows from this declaration region. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp) |

## B0006

[Lines 31–51](../../../../../../include/crown/runtime/fallback.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L51:sha256:02702ec8b74e267a389af488393850e924bccadc928e9c19e888a716c4b09318
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose owning frozen arbitrary-query semantics and original-head schema. |
| inputs / outputs | Binding getters borrow program::Query, Profile, source-only CompiledProgram, AccountedLayout and account. |
| invariants | All runtime query views refer to native frozen arrays/text/literal blocks; no ordinary retained Query/Catalog mirror. |
| ownership | Copies share the funded immutable Data; lvalue-only getters prevent borrowing a temporary handle. |
| failure | Empty Binding getters throw fallback_state; no new grant is created by copying a live handle. |
| cost | Fixed shared-owner/getter work; final-owner destruction traverses actual metadata allocations. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp) |

## B0007

[Lines 52–53](../../../../../../include/crown/runtime/fallback.hpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L53:sha256:b74db564fa2eb61de5a41231d3d4a6f9d54e4a8ea4db0a7ac96d843bb1546762
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define transferable funded arrays for native answer handles and diagnostic cardinalities. |
| inputs / outputs | TupleVector stores Tuple handles; Cardinalities stores uint64 values with OwnerAllocator. |
| invariants | Returned arrays adopt their original account; internal maintained arrays use nonpropagating allocators. |
| ownership | Capacity and native tuple owners survive facade destruction under the same original account. |
| failure | Array growth may refuse from the original finite allocation authority. |
| cost | O(array capacity) storage; native Tuple copies share immutable payload rather than copying strings. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp) |

## B0008

[Lines 54–54](../../../../../../include/crown/runtime/fallback.hpp#L54); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L54:sha256:16c31dba75f6705e367363a10d6ed3be9e9ce1d07e0c371264cd9493c56dc9a9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a self-contained eager committed result snapshot. |
| inputs / outputs | Sequence, actual Binding, sorted distinct headed rows and copy Metrics. |
| invariants | Rows preserve ordered/repeated head fields; Boolean truth is one nullary row, false is no row. |
| ownership | Funded array/Binding/native payloads outlive Runtime and hold no source read lease. |
| failure | Snapshot refusal returns no partial value and changes no committed state. |
| cost | O(result count) handle copy/capacity work; last-owner payload and metadata cleanup remain actual costs. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp) |

## B0009

[Lines 55–60](../../../../../../include/crown/runtime/fallback.hpp#L55); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L60:sha256:e40eaa5fce68b8b3f31ccfb62c44781dc513cc3a60d30ad01c12784e32754d37
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return full-source publication and exact answer endpoint differences. |
| inputs / outputs | PhysicalEpoch input, actual semantic Binding and owning added/removed set rows with Metrics. |
| invariants | Only added/removed are original-query answer deltas; source/support events are separate local facts. |
| ownership | Native row handles preserve removed values after deletion/owner teardown in their original account. |
| failure | No result Epoch is returned until all fallible capture/answer/delta work precedes valid source commit. |
| cost | Source work plus conservative evaluation/dedup/merge and O(delta) funded handle arrays. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp) |

## B0010

[Lines 61–68](../../../../../../include/crown/runtime/fallback.hpp#L61); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L68:sha256:d7bd0baafcc7985835d6dd2f68b9028e8cfceeaad32cdc0e3d07a36a56554754
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose an owning cold execution profile and advisory cardinality estimates. |
| inputs / outputs | Explain contains actual per-table counts, optional Cartesian/prefix products, result count and account statistics. |
| invariants | Overflow yields nullopt; final product zero does not erase an earlier overflowing prefix sum. |
| ownership | Cardinalities array is funded/transferrable; Profile uses immutable static labels and enums. |
| failure | Diagnostic allocation can refuse without changing committed state. |
| cost | O(catalog tables plus original atom occurrences); estimates ignore filters/byte widths and are not runtime bounds. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp) |

## B0011

[Lines 69–104](../../../../../../include/crown/runtime/fallback.hpp#L69); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L104:sha256:7fafccea088bf766d491efe6c4afa8a1b74d2b64db5b344ca046524a37ecfbce
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare a serial exact evaluator for cyclic and acyclic non-free-connex CQs. |
| inputs / outputs | Admitted Plan/Options construct initially empty sources; apply/snapshot/explain expose committed state. |
| invariants | One genuine source-only owner enforces full constraints; iterative original-term evaluation filters before DISTINCT projection. |
| ownership | Native metadata, source image, scratch, results and outputs all use the original account; no second source journal or overlay. |
| failure | Private source-token RAII rolls back refusal; busy guard spans source/result publication and temporary retirement. |
| cost | Explicit image/prefix/product/scalar/byte/dedup/materialization/cleanup costs; no constant-delay CROWN/GHD/bag/recovery claim. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp) |

## B0012

[Lines 105–106](../../../../../../include/crown/runtime/fallback.hpp#L105); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L106:sha256:065afca96ff52ad9437386e799e876038e1516fbce18d7ab8e0ede03a6995f9a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the move-only facade and its namespace. |
| inputs / outputs | Completes Runtime after the unique account-funded Data member declaration. |
| invariants | Executable state remains owned solely by the preceding AccountedUnique; metadata outputs have their own immutable owners. |
| ownership | No raw ordinary query/database owner is added at closure. |
| failure | Closing delimiters execute no operation. |
| cost | No runtime work; facade/Data retirement follows the declared member ownership. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/query_memory.md](../../../../../query_memory.md), [include/crown/runtime/fallback.hpp](../../../../../../include/crown/runtime/fallback.hpp) |
