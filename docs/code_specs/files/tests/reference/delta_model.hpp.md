# `tests/reference/delta_model.hpp` — block usage map

[Source](../../../../../tests/reference/delta_model.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `26b13633da8be5000d33c4f6876bd8be11150227c43f2754a25a206fb0795bf2`. 57 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../tests/reference/delta_model.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Test-only, materializing executable specification. It never reads the · [reviewed contract](#b0001) |
| [B0002 · 11–16](../../../../../tests/reference/delta_model.hpp#L11) | Type/record definition: struct Factor | source comment (unverified): // Sorted visible variable IDs. · [reviewed contract](#b0002) |
| [B0003 · 17–21](../../../../../tests/reference/delta_model.hpp#L17) | Type/record definition: struct Snapshot | source comment (unverified): // Original order, including repeated fields. · [reviewed contract](#b0003) |
| [B0004 · 22–34](../../../../../tests/reference/delta_model.hpp#L22) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Native rows have complete ascending-variable-ID node scopes, after local · [reviewed contract](#b0004) |
| [B0005 · 35–39](../../../../../tests/reference/delta_model.hpp#L35) | Type/record definition: struct Fragment |  · [reviewed contract](#b0005) |
| [B0006 · 40–43](../../../../../tests/reference/delta_model.hpp#L40) | Type/record definition: struct Metrics |  · [reviewed contract](#b0006) |
| [B0007 · 44–50](../../../../../tests/reference/delta_model.hpp#L44) | Type/record definition: struct Transition | source comment (unverified): // Append only: no deduplication across fragments. · [reviewed contract](#b0007) |
| [B0008 · 51–57](../../../../../tests/reference/delta_model.hpp#L51) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // One fully drained same-sign logical occurrence step. Select changed E · [reviewed contract](#b0008) |

## B0001

[Lines 1–10](../../../../../tests/reference/delta_model.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:770c6c34bd033127e81f6d0c60ad3574e70f856c647719dff54105bfeb8f05c2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_model.hpp: include "crown/ir/model.hpp", "crown/ir/tree.hpp", &lt;map&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp) |

## B0002

[Lines 11–16](../../../../../tests/reference/delta_model.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Factor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one visible materialized E factor for the independent logical delta model. |
| inputs / outputs | Stores native/tree node ID, optional parent factor index, sorted visible-variable scope and an exact set of owning rows. |
| invariants | Validated snapshots require unique node IDs, parent-before-child order, sorted unique scope, exact row width and consistent scalar types. Rows represent visible projections of complete subtree joins. |
| ownership | Ordinary vectors/sets own scope and Value rows; no runtime node, journal, reader or account capability is retained. |
| failure | The struct itself validates nothing; model entrypoints reject malformed supplied snapshots. |
| cost | Storage scales with full materialized rows and scalar payload, intentionally separate from compact production factors. |
| Design | [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/result_cursors.md](../../../../result_cursors.md) |

## B0003

[Lines 17–21](../../../../../tests/reference/delta_model.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Snapshot {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe an owning visible-factor snapshot and its original ordered output head. |
| inputs / outputs | Contains head positions including repeats, root-first factors and a Boolean constant-route answer. |
| invariants | Empty factors encode a constant route; a true constant requires an empty head. Nonconstant factors form one connected parent-before-child tree and cover all unique head variables with running intersection. |
| ownership | Owns all ordinary reference containers; public fields remain editable data and provide no native-state or proof authority. |
| failure | Public model operations call validate_snapshot before relying on its shape; allocation errors are ordinary reference failures. |
| cost | Full factor storage plus head positions; not a checkpoint or live-state mirror in ordinary runtime updates. |
| Design | [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [docs/delta_runtime.md](../../../../delta_runtime.md) |

## B0004

[Lines 22–34](../../../../../tests/reference/delta_model.hpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L34:sha256:bc67d23302e261f962df20289afeb3b95c7d4e178b3132f18962996a0e18fd21
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_model.hpp: declare helper function signatures without invoking them. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. Function prototypes declare the shown reference/helper API; invocation and any default-argument evaluation occur at the caller. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp) |

## B0005

[Lines 35–39](../../../../../tests/reference/delta_model.hpp#L35); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fragment {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one changed-factor witness and its independently enumerated completion partition. |
| inputs / outputs | Stores factor index, owning witness Row and candidate/accepted/rejected output vectors. |
| invariants | partition fills a fragment only for a live changed witness; every candidate is accepted only if this is its earliest changed factor, otherwise recorded rejected. |
| ownership | Owns copied complete rows in ordinary vectors for human/test inspection; no borrowed cursor lease. |
| failure | Construction/allocation failure aborts the reference result before return. |
| cost | Can retain candidates and their accepted/rejected copies simultaneously; this diagnostic oracle intentionally materializes them. |
| Design | [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [docs/delta_runtime.md §Views and prefix identity](../../../../delta_runtime.md) |

## B0006

[Lines 40–43](../../../../../tests/reference/delta_model.hpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Metrics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count selected witness/candidate/earlier-factor events in a completed reference transition. |
| inputs / outputs | Plain uint64 counts for changed keys, live/dead witnesses, candidates, accepted/rejected rows and earlier probes. |
| invariants | Counts are selected logical events, not bytes, elapsed CPU, resource grants or native work counters. The test corpus must keep these ordinary unchecked counters in range. |
| ownership | Fixed values returned with the owning Transition; caller edits cannot refill any production allowance. |
| failure | No independent overflow or resource status is implemented by this struct. |
| cost | Fixed counter storage; updates accompany actual reference traversal. |
| Design | [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [docs/delta_runtime.md §Work and space accounting](../../../../delta_runtime.md) |

## B0007

[Lines 44–50](../../../../../tests/reference/delta_model.hpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Transition {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the full independently materialized result of one drained same-sign logical occurrence step. |
| inputs / outputs | Contains polarity, changed memberships, before/after live sets, fragments, append-only raw accepted rows and selected Metrics. |
| invariants | Compatible query/factor schemas and monotone same-sign memberships are checked. Raw rows are appended across fragments without a final global dedup pass, so duplicate ownership mistakes remain observable. |
| ownership | All rows/sets/fragments are ordinary owning containers, independent of runtime journals/live caches/cursors. |
| failure | Invalid model or transition shape throws its named reference Error; partial result remains local and unwinds. |
| cost | Retains multiple full live/change/candidate/output representations for bounded verification, never on the production update path. |
| Design | [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [docs/delta_runtime.md §Views and prefix identity](../../../../delta_runtime.md) |

## B0008

[Lines 51–57](../../../../../tests/reference/delta_model.hpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L57:sha256:de70a696e68468e8bfbab416cfd8b7e4cc769930a906ff592b82ee9eba8821b1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_model.hpp: declare helper function signatures without invoking them. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. Function prototypes declare the shown reference/helper API; invocation and any default-argument evaluation occur at the caller. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/reference/delta_model.hpp](../../../../../tests/reference/delta_model.hpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md), [tests/reference/delta_model.cpp](../../../../../tests/reference/delta_model.cpp) |
