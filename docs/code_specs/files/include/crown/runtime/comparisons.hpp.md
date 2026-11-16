# `include/crown/runtime/comparisons.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/comparisons.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare exact comparison binding, finite recomputation grants, owning snapshots and atomic endpoint set deltas.

Snapshot SHA-256: `eabecb43893ed8d0358c6420c6f403aefdc683ea79071beab1c9a71cd97f82b0`. 102 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [comparisons](../../../../subsystem_contracts.md#comparisons). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/comparisons.md](../../../../../comparisons.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/runtime/comparisons.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../../include/crown/runtime/comparisons.hpp#L13) | Type/record definition: struct Predicate |  · [reviewed contract](#b0002) |
| [B0003 · 14–18](../../../../../../include/crown/runtime/comparisons.hpp#L14) | Type/record definition: struct Limits | source comment (unverified): // One shared wrapper grant, including row/scalar/byte work. · [reviewed contract](#b0003) |
| [B0004 · 19–19](../../../../../../include/crown/runtime/comparisons.hpp#L19) | Type/record definition: struct Options |  · [reviewed contract](#b0004) |
| [B0005 · 20–26](../../../../../../include/crown/runtime/comparisons.hpp#L20) | Type/record definition: struct Metrics |  · [reviewed contract](#b0005) |
| [B0006 · 27–33](../../../../../../include/crown/runtime/comparisons.hpp#L27) | declares types or opens a type body. | source comment (unverified): // Genuine equality-program provenance plus the ACTUAL comparison conjunction. · [reviewed contract](#b0006) |
| [B0007 · 34–50](../../../../../../include/crown/runtime/comparisons.hpp#L34) | Type/record definition: class Binding | returns bool(data_); source comment (unverified): // Genuine equality-program provenance plus the ACTUAL comparison conjunction. · [reviewed contract](#b0007) |
| [B0008 · 51–51](../../../../../../include/crown/runtime/comparisons.hpp#L51) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0008) |
| [B0009 · 52–57](../../../../../../include/crown/runtime/comparisons.hpp#L52) | Type/record definition: struct Snapshot | source comment (unverified): // Sorted distinct full-head rows; immutable native payloads are shared. · [reviewed contract](#b0009) |
| [B0010 · 58–63](../../../../../../include/crown/runtime/comparisons.hpp#L58) | Type/record definition: struct Epoch | source comment (unverified): // Original source/support epoch, NOT comparison answer deltas. · [reviewed contract](#b0010) |
| [B0011 · 64–99](../../../../../../include/crown/runtime/comparisons.hpp#L64) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Exact comparison wrapper over one genuine PhysicalRuntime. Updates use its · [reviewed contract](#b0011) |
| [B0012 · 100–102](../../../../../../include/crown/runtime/comparisons.hpp#L100) | Member/declaration region. | source comment (unverified): // namespace crown::runtime::comparisons · [reviewed contract](#b0012) |

## B0001

[Lines 1–12](../../../../../../include/crown/runtime/comparisons.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:be8f2bc834631a74840996039b21b53945285d0160fecf0f752c43895ee81c31
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the opt-in exact comparison runtime over genuine planner admission and native storage types. |
| inputs / outputs | Imports planner/physical/owner APIs; defines Operator and borrowed native-scalar Operand aliases. |
| invariants | Variable operands use original VariableId; literal operands are exact ScalarView values without SQL NULL. |
| ownership | Aliases allocate nothing; scalar string views require their immutable Binding owner. |
| failure | Declarations perform no admission or execution. |
| cost | Compile-time inclusion/aliases only; runtime costs belong to the implementations. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/comparisons.md](../../../../../comparisons.md), [include/crown/runtime/comparisons.hpp](../../../../../../include/crown/runtime/comparisons.hpp) |

## B0002

[Lines 13–13](../../../../../../include/crown/runtime/comparisons.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L13:sha256:59a99d65d8124e8a771b12c8254aef8bd067d6559fb1b45c675b0c91bd8798b2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one admitted comparison conjunct in frozen native metadata. |
| inputs / outputs | Left/right variable-or-scalar operands and one six-relation planner operator. |
| invariants | Both operand kinds have the same ScalarType established by genuine planner admission. |
| ownership | Operand views borrow Binding-owned literal blocks; they do not own string bytes themselves. |
| failure | A raw Predicate DTO is not an executable admission token. |
| cost | Fixed-size variant metadata; actual scalar comparison may inspect strings/decimal digits. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/comparisons.md](../../../../../comparisons.md), [include/crown/runtime/comparisons.hpp](../../../../../../include/crown/runtime/comparisons.hpp) |

## B0003

[Lines 14–18](../../../../../../include/crown/runtime/comparisons.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L18:sha256:cea85e3d2f80eb5cf949ed117e4e296dc0dfdd7dd39fcb56765e5a90e958af42
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound wrapper work, cumulative witness production and distinct materialization independently. |
| inputs / outputs | Three uint64 limits default to one million wrapper/producer units and 65536 distinct rows. |
| invariants | Wrapper work is shared across constructor freeze/initial build or across one update/recompute/difference. |
| ownership | Plain copied scalar limits confer no memory account and do not extend payload lifetimes. |
| failure | Insufficient limits refuse privately; producer exhaustion uses the inherited cursor boundary. |
| cost | Limit reads are scalar work; selected units do not imply a wall-time bound. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/comparisons.md](../../../../../comparisons.md), [include/crown/runtime/comparisons.hpp](../../../../../../include/crown/runtime/comparisons.hpp) |

## B0004

[Lines 19–19](../../../../../../include/crown/runtime/comparisons.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L19:sha256:e677cbe379781719c84752c555cbcaeaf78f9efae1761928351f8939e428c174
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine unchanged physical-source policy with comparison recomputation admissions. |
| inputs / outputs | PhysicalRuntimeOptions sources plus wrapper Limits recompute. |
| invariants | The genuine source policy and original indexed/account ceilings remain authoritative. |
| ownership | Options are configuration values; execution constructs exactly one genuine physical owner. |
| failure | Invalid source options can fail through the existing physical constructor. |
| cost | Configuration copy only; constructor/source/recomputation costs are separate. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/comparisons.md](../../../../../comparisons.md), [include/crown/runtime/comparisons.hpp](../../../../../../include/crown/runtime/comparisons.hpp) |

## B0005

[Lines 20–26](../../../../../../include/crown/runtime/comparisons.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L26:sha256:ff6ea27edd401fbac38b6d482c4d2577ab320cc568dc9cafcb247c654fb8d3a0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the selected work and exact set-maintenance path actually executed. |
| inputs / outputs | Counters distinguish wrapper/view/producer work, witnesses, predicates, projection, duplicates and endpoint sizes. |
| invariants | Scalar bytes are admitted extents; recomputed is false when every native membership is unchanged. |
| ownership | Returned Metrics are value diagnostics and retain no source/view/allocator borrow. |
| failure | Counters on a refused private operation are not published as a committed epoch. |
| cost | Counter increments are included in selected admissions; allocator and cleanup costs remain real. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/comparisons.md](../../../../../comparisons.md), [include/crown/runtime/comparisons.hpp](../../../../../../include/crown/runtime/comparisons.hpp) |

## B0006

[Lines 27–33](../../../../../../include/crown/runtime/comparisons.hpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L33:sha256:faed940bd292ec73b92e3d0ad9ec2b42cdb53ec9dde43df99c10284e62eff618
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the frozen Binding provenance and lifetime boundary before its declaration. |
| inputs / outputs | Documents actual predicates plus original equality metadata, without a new comparison identity. |
| invariants | The inherited equality guarantee is never relabeled as a comparison execution theorem. |
| ownership | Keeping Binding retains constants and schema independently of the mutable runtime. |
| failure | Comment/forward declaration performs no executable action. |
| cost | No runtime operation; it constrains interpretation of the following public API. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/comparisons.md](../../../../../comparisons.md), [include/crown/runtime/comparisons.hpp](../../../../../../include/crown/runtime/comparisons.hpp) |

## B0007

[Lines 34–50](../../../../../../include/crown/runtime/comparisons.hpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L50:sha256:bae47ff6333d44f2ca035ad10546489e8a77cc6d4abb923408363e63e6f0304e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own immutable original-account comparison semantics and expose borrowed metadata getters. |
| inputs / outputs | Default empty Binding or runtime-created shared owner; getters expose program, predicates and account. |
| invariants | Only Runtime constructs nonempty bindings; const-lvalue getters cannot borrow a temporary handle. |
| ownership | Shared Data owns copied literal blocks and native predicate arrays; CompiledProgram aliases genuine frozen metadata. |
| failure | Empty binding getters throw comparison_state; copying a live binding creates no new allowance. |
| cost | Shared-owner handle copies/getters are scalar bookkeeping; final-owner destruction visits retained metadata. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/comparisons.md](../../../../../comparisons.md), [include/crown/runtime/comparisons.hpp](../../../../../../include/crown/runtime/comparisons.hpp) |

## B0008

[Lines 51–51](../../../../../../include/crown/runtime/comparisons.hpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L51:sha256:9c1e0386a1b884468545a19c08523613f48aea8db727eff8ab61016bd1b1cc0d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Give transferable snapshot and delta arrays the original query allocator. |
| inputs / outputs | TupleVector is a vector of native-backed Tuple handles with OwnerAllocator. |
| invariants | Transferred arrays adopt their source account; internal maintained state instead uses MemoryAllocator. |
| ownership | Vector capacity and native tuple owners remain charged after facade teardown. |
| failure | Array growth can refuse from the original account. |
| cost | O(array capacity) storage; native tuple-handle copies share immutable payload rather than copying strings. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/comparisons.md](../../../../../comparisons.md), [include/crown/runtime/comparisons.hpp](../../../../../../include/crown/runtime/comparisons.hpp) |

## B0009

[Lines 52–57](../../../../../../include/crown/runtime/comparisons.hpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L57:sha256:54a4dd7f5580bde787f9ba2dd41a4500d0ea9383832c91c9e90de4d649ba6e42
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a self-contained eager current comparison result. |
| inputs / outputs | Committed sequence, semantic Binding, sorted distinct original-head rows and copy metrics. |
| invariants | Rows preserve ordered/repeated head fields and exact set semantics. |
| ownership | Funded vector and native tuple owners outlive Runtime; no source read lease is retained. |
| failure | Failed snapshot creation returns no partially constructed Snapshot. |
| cost | Eager O(result count) funded handle copies; later teardown releases vector/last-owner payload costs. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/comparisons.md](../../../../../comparisons.md), [include/crown/runtime/comparisons.hpp](../../../../../../include/crown/runtime/comparisons.hpp) |

## B0010

[Lines 58–63](../../../../../../include/crown/runtime/comparisons.hpp#L58); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L63:sha256:076fdd53b1ea4db218df62afa6a01bfeed3bd6d7af22cf4820651c82ba59a950
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return source publication together with exact comparison endpoint changes. |
| inputs / outputs | PhysicalEpoch input, semantic Binding, added/removed native Tuple arrays and maintenance metrics. |
| invariants | Physical support transitions are local native events; only added/removed are comparison answer deltas. |
| ownership | Every delta row owns/shares its original-account payload, including removed rows after source deletion. |
| failure | No Epoch is returned before all fallible view/difference work and valid source publication complete. |
| cost | O(delta size) handle arrays plus the explicitly reported source/recomputation/merge work. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/comparisons.md](../../../../../comparisons.md), [include/crown/runtime/comparisons.hpp](../../../../../../include/crown/runtime/comparisons.hpp) |

## B0011

[Lines 64–99](../../../../../../include/crown/runtime/comparisons.hpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L99:sha256:bba60207bd5442683336622fbab656da2c72eae5369afad706cf96c0a024505e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the serial exact comparison owner and its source/result publication contract. |
| inputs / outputs | Admitted Plan/Options construct empty sources plus initial answer; apply, snapshot and diagnostic accessors expose committed state. |
| invariants | Filter complete assignments before original-head projection; one genuine source owner; no second undo journal or source clone. |
| ownership | Data retains the account, physical owner, frozen binding and sorted native result handles; outputs retain independent ownership. |
| failure | Private source-token rollback handles refusal; synchronous callbacks cannot observe the partial publication window. |
| cost | Recomputation/materialization may visit all witnesses and ordered rows; no CQC update bound or lazy delay guarantee. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/comparisons.md](../../../../../comparisons.md), [include/crown/runtime/comparisons.hpp](../../../../../../include/crown/runtime/comparisons.hpp) |

## B0012

[Lines 100–102](../../../../../../include/crown/runtime/comparisons.hpp#L100); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L100-L102:sha256:c9e7a4e0917d7070c27f3391c1561e73d3ee9d410fedbe6865fb1e819364411f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the facade’s account-funded unique implementation owner and close its declaration. |
| inputs / outputs | data_ holds Runtime::Data; the private data() accessor validates moved-from use. |
| invariants | Only one facade owns this mutable Data; moving transfers that owner without minting an account. |
| ownership | AccountedUnique funds object/deleter storage and destroys retained physical/result state on last ownership. |
| failure | Default/moved-from ownership cannot execute getters through data(). |
| cost | Pointer transfer is scalar; retiring old Data traverses its actual source/result metadata and allocations. |
| Design | [Refactor.md](../../../../../../Refactor.md), [docs/comparisons.md](../../../../../comparisons.md), [include/crown/runtime/comparisons.hpp](../../../../../../include/crown/runtime/comparisons.hpp) |
