# `tools/code_specs_support.py` — block usage map

[Source](../../../../tools/code_specs_support.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `dc109dc447fb5c122a7985db07c48db7bd80e8e9da9ba8a5e6bfc7b9c23a00d3`. 468 lines partitioned into 14 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–36](../../../../tools/code_specs_support.py#L1) | declares callable signatures; declares values/defaults or compile-time conditions. | 1 loop sites · [reviewed contract](#b0001) |
| [B0002 · 37–72](../../../../tools/code_specs_support.py#L37) | declares callable signatures. | growth allocate, clone; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 73–108](../../../../tools/code_specs_support.py#L73) | declares aliases. | growth allocate, new; 5 loop sites · [reviewed contract](#b0003) |
| [B0004 · 109–144](../../../../tools/code_specs_support.py#L109) | Module statements. | growth allocate; 2 loop sites · [reviewed contract](#b0004) |
| [B0005 · 145–180](../../../../tools/code_specs_support.py#L145) | declares aliases. | returns no partial specialization and preserve the caller\'s original plan. Normalized SQL, constant operat…; growth allocate, new; 4 loop sites · [reviewed contract](#b0005) |
| [B0006 · 181–216](../../../../tools/code_specs_support.py#L181) | declares callable signatures. | growth allocate, insert, new; 4 loop sites · [reviewed contract](#b0006) |
| [B0007 · 217–252](../../../../tools/code_specs_support.py#L217) | declares aliases; declares callable signatures. | growth allocate; 6 loop sites · [reviewed contract](#b0007) |
| [B0008 · 253–288](../../../../tools/code_specs_support.py#L253) | declares aliases; declares types or opens a type body. | growth allocate, new; 3 loop sites · [reviewed contract](#b0008) |
| [B0009 · 289–305](../../../../tools/code_specs_support.py#L289) | declares aliases. |  · [reviewed contract](#b0009) |
| [B0010 · 306–341](../../../../tools/code_specs_support.py#L306) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | returns original-account owning outputs under a read lease.',; a compact exact prefix without query-update …; growth new; 2 loop sites; source comment (unverified): # File-stem display labels are context, not proof that every matching path has this role. · [reviewed contract](#b0010) |
| [B0011 · 342–377](../../../../tools/code_specs_support.py#L342) | declares aliases. | 6 loop sites · [reviewed contract](#b0011) |
| [B0012 · 378–413](../../../../tools/code_specs_support.py#L378) | declares aliases; declares callable signatures. | returns authority-bearing delivery receipts.',; 6 loop sites · [reviewed contract](#b0012) |
| [B0013 · 414–418](../../../../tools/code_specs_support.py#L414) | Module statements. | 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 419–468](../../../../tools/code_specs_support.py#L419) | Callable definition: def family(path): | calls endswith, startswith, rsplit, any; returns 'build'; 'tests'; 5 loop sites; source comment (unverified): # Ordered path/name heuristics select context; they do not certify file behavior. · [reviewed contract](#b0014) |

## B0001

[Lines 1–36](../../../../tools/code_specs_support.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
"""Reviewed subsystem and primitive contracts used by generate_code_specs.py.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide authored shared subsystem context and display role classification to the generator. |
| inputs / outputs | Module load materializes CONTRACTS/ROLES and defines family(); no filesystem, import of generator, or generation call. |
| invariants | Context and file labels are not per-block semantic certification or paper proof. main explicitly attaches them separately from authored scoped cards. |
| ownership | Mutable Python dict/list graphs own text/reference arrays; strings are immutable objects, module does not expose a frozen mapping. |
| failure | Syntax/data construction/OOM errors can prevent import; no handlers. |
| cost | Fixed current context/role text graph allocation at import; no native update overhead. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
CONTRACTS = {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store seven-field module-boundary documentation context for the current 33 families. |
| inputs / outputs | Family keys map to purpose, input/output, invariants, ownership, failure, cost and references. Difference and shared positive-CQ recomputation receive separate contexts. |
| invariants | Mutable ordinary offline metadata remains separate from block-specific source review and supplies no executable authority or paper bound. Set/bag difference and callback traversal are separate meanings. |
| ownership | Owns nested dicts/reference lists and immutable strings; dict(CONTRACTS\[group\]) is shallow and later references list is replaced locally. |
| failure | Unknown family/key/data-shape errors are uncaught in consumer; ordinary import allocation may fail. |
| cost | Constant current data-size storage/import; generation traverses/context-renders text and checks reference paths. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
@source-span:L34-L42:sha256:abf5c1bc0e8998ebb044d6d689bb8caf716a0f9752b6d293a3cee462fd1814d9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define shared context for the explicit comparison family. |
| inputs / outputs | The seven-field dictionary describes typed public IR, complete-assignment filtering, endpoint set deltas and ordinary recomputation. |
| invariants | Context is not per-block proof. Equality provenance, original account, one wrapper balance, separate cumulative producer work and real materialization/cleanup costs remain explicit; no P9 bound is claimed. |
| ownership | Ordinary Python dictionary/string/reference metadata, outside native query state. |
| failure | Existing import/render/type/allocation errors propagate through offline tools. |
| cost | Fixed literal import and offline text rendering; no native update or cursor overhead. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/comparisons.md](../../../comparisons.md), [Refactor.md](../../../../Refactor.md) |

```text
@source-span:L25-L33:sha256:8084f69a586b08203545d6490f57aa2e99d5fc13fdf1c25ba35bb4b6e9aff909
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the explicit conservative fallback family for human inspection. |
| inputs / outputs | Seven shared fields describe original public IR, actual structural class, full-source capture, exact recomputation and endpoint deltas. |
| invariants | This context is not per-block proof or a GHD/CROWN certificate. One original account, cumulative grants and real prefix/materialization/cleanup costs remain explicit. |
| ownership | Ordinary Python strings, lists and dictionary metadata, outside native state. |
| failure | Offline import/render/allocation errors propagate without a new handler. |
| cost | Fixed metadata import and offline rendering only. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/fallback.md](../../../fallback.md), [Refactor.md](../../../../Refactor.md) |

```text
@source-span:L7-L15:sha256:0684aae34f4ba220f7b7951d87cfa304ded7c77a4f53b1525acdc52e760effb8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define shared difference inspection context. |
| inputs / outputs | Seven fields describe the actual set/bag pair semantics, original account, one source image, count replacements and conservative costs. |
| invariants | Shared context is not block-specific proof or executable authority. Local engineering and finite grants do not imply CROWN/P11 bounds. |
| ownership | Ordinary offline Python metadata, outside native state. |
| failure | Offline import/render/allocation errors propagate. |
| cost | Fixed metadata import and offline rendering; no native hot-path work. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/difference.md](../../../difference.md), [docs/fallback.md](../../../fallback.md), [Refactor.md](../../../../Refactor.md) |

```text
@source-span:L16-L24:sha256:9089a8a1a056a7b33e9be9d13da7831fe16051269196c846e32fa5243552c3fe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define shared cq_recompute inspection context. |
| inputs / outputs | Seven fields describe the actual positive-query freezer/visitor, borrowed complete-witness callback and caller-selected consolidation. |
| invariants | Shared context is not block-specific proof or executable authority. Local engineering and finite grants do not imply CROWN/P11 bounds. |
| ownership | Ordinary offline Python metadata, outside native state. |
| failure | Offline import/render/allocation errors propagate. |
| cost | Fixed metadata import and offline rendering; no native hot-path work. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/difference.md](../../../difference.md), [docs/fallback.md](../../../fallback.md), [Refactor.md](../../../../Refactor.md) |

## B0002

[Lines 37–72](../../../../tools/code_specs_support.py#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
'weighted': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared weighted context: weighted logical messages/local factors and compressed multiplicity enumeration, with distinct weighted admission. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute weighted code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'api': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared api context: public owning Error diagnostics, with no query or rollback authority. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute api code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'memory': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared memory context: actual requested-byte accounting/allocator ownership distinct from RSS. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute memory code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
@source-span:L43-L51:sha256:b7d31849e9c7374499ce44d0329de5821c50fcaf4ccf6e86c024801c2bce4440
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define shared documentation context for exact literal star maintenance. |
| inputs / outputs | The star dictionary supplies the existing seven-field module context to the offline source-map generator. |
| invariants | Context distinguishes light fact visits, heavy group predicates, counted projections, sparse H/reset work and local cursor repair. It explicitly excludes a blanket P2/native delay claim and is not per-block certification. |
| ownership | Ordinary imported Python dictionary, immutable strings and a reference list; no native account or runtime state. |
| failure | Ordinary import/render/type/allocation errors propagate through the existing documentation tools. |
| cost | Fixed literal import and offline text/reference rendering; no query-update or cursor overhead. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/star.md](../../../star.md), [docs/code_review.md](../../../code_review.md) |

## B0003

[Lines 73–108](../../../../tools/code_specs_support.py#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
'values': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared values context: exact scalar/row/layout/projection conversions and borrowed/native ownership boundaries. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | Subsystem usage context does not execute values code or create authority. The dated S05 tuple guide is historical ownership evidence; current acceptance comes from current source and verification checkpoints. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing reference paths are filtered by the generator; the values references now name existing files. Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'arena': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared arena context: owner/slot/generation handles, pins and retained deleted payload lifetime. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute arena code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'storage': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared storage context: exact rows/primary-secondary membership, rollback and backend work assumptions. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute storage code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'ir': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared ir context: ordinary compiler DTOs versus immutable admitted native metadata. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute ir code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0004

[Lines 109–144](../../../../tools/code_specs_support.py#L109); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
'frontend': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared frontend context: parser/binder/normalizer boundaries and unsupported-language diagnostic phases. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute frontend code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'catalog': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared catalog context: schema/full-source data/constraint validation and full-scan reference costs. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute catalog code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'planner': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared planner context: structural recognition/tree verification/lowering separate from exact height proof. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute planner code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'search': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared search context: finite exact-height producer/replay and checked evidence under limits. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute search code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0005

[Lines 145–180](../../../../tools/code_specs_support.py#L145); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
'residual': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared residual context: residual construction/replay and independently checked exact repair. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute residual code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'ranking': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared ranking context: bound feasible-candidate modeled scores/selection separate from height proof or measured speed. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute ranking code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
@source-span:L178-L186:sha256:ed86460c6b727d74614c4aa88973b0a0343aca33eba141e18fe384f69f405de7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the shared exact snapshot-sort documentation context. |
| inputs / outputs | Offline generator imports this literal context/role for source inspection pages; no query input is evaluated. |
| invariants | Top-k is separate from Boolean support and planner candidate ranking. Context preserves rendered SQL value order, group identity, compressed multiplicity and separate producer/sort budgets. A display label is not semantic certification. |
| ownership | Ordinary Python dictionary/string metadata is shared by the offline generator, outside all native query accounts. |
| failure | Import or rendering errors use the existing documentation-tool boundary; this literal installs no runtime error handling. |
| cost | One offline literal import plus generated text/reference copies; no query execution or update-path work. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/topk.md](../../../topk.md), [Refactor.md](../../../../Refactor.md) |

```text
@source-span:L169-L177:sha256:953f619bc635112758dd7aa7f1a4bc6bcd5e1b0ca73d480a54f5bdfd203d4b7a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define exact guarded-key context. |
| inputs / outputs | Offline generator imports literal usage context/role labels; no query or database is evaluated. |
| invariants | Enforced authority, live witnesses, private-variable guards, full source enforcement and reduced-only proof scope remain explicit. Labels are not correctness authority or automatic selection. |
| ownership | Ordinary Python dictionary/string metadata outside native query accounts; retained generated text is offline output. |
| failure | Existing import/render failures propagate at the documentation tool boundary; no runtime error handling is added. |
| cost | One cold literal import plus output copies/references; no runtime or ordinary update work. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/key_specialization.md](../../../key_specialization.md), [Refactor.md](../../../../Refactor.md) |

## B0006

[Lines 181–216](../../../../tools/code_specs_support.py#L181); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
'support': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared support context: Boolean S/P/E membership and factorized current/epoch cursor leases. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute support code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'physical': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared physical context: full source aliases/exact derivations/atomic logical epoch and source-constraint scratch. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute physical code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'delta': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared delta context: private telescoping prefixes/live factors and retained signed result delivery. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute delta code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'session': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared session context: creator-thread source-to-output preparation/publication and uncertain durable recovery. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute session code or create checked authority. V52 context distinguishes admitted requests, enforced live prefix, trusted restored history and versioned recovery; real scoped work/storage is documented without a paper CPU/delay claim. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md), [docs/update_patterns.md](../../../update_patterns.md) |

## B0007

[Lines 217–252](../../../../tools/code_specs_support.py#L217); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
'window': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared window context: operational membership/expiration and borrowed Prepared lifetime without claiming paper FIFO. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute window code or create checked authority. V52 context distinguishes admitted requests, enforced live prefix, trusted restored history and versioned recovery; real scoped work/storage is documented without a paper CPU/delay claim. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md), [docs/update_patterns.md](../../../update_patterns.md) |

```text
'statistics': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared statistics context: stamped availability/unknown-versus-zero and explicit diagnostic collection/export costs. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute statistics code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'recovery': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared recovery context: length/identity/prefix/locks/checksums/durable selection and uncertain IO phases. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute recovery code or create checked authority. V52 context distinguishes admitted requests, enforced live prefix, trusted restored history and versioned recovery; real scoped work/storage is documented without a paper CPU/delay claim. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md), [docs/update_patterns.md](../../../update_patterns.md) |

```text
'io': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared io context: versioned external representation/native record boundaries and explicit temporary parsing storage. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute io code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0008

[Lines 253–288](../../../../tools/code_specs_support.py#L253); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
'annotations': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared annotations context: bounded exact arithmetic policy, distinct from weighted runtime/SQL support. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute annotations code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'tools': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared tools context: offline evidence/CLI/file/hash/process workflows, whose actual main/argument behavior must be inspected. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute tools code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'tests': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared tests context: finite fixture/oracle/fault evidence and actual execution distinct from source inventory. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute tests code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'build': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared build context: target/dependency/configure/build/install rules distinct from verification of runtime correctness. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute build code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0009

[Lines 289–305](../../../../tools/code_specs_support.py#L289); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
'examples': {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide shared examples context: demonstration ownership/measurement interval and workflow semantics without release/performance certification. |
| inputs / outputs | Authored seven-field dictionary consumed by family-selected module context and subsystem page, not copied as a contract onto every block. |
| invariants | This entry states subsystem intended usage; source-specific assumptions/failure/cost behavior still require anchor/caller review. It does not execute examples code or create checked authority. |
| ownership | Owning Python nested dict with six immutable text values and a mutable reference list; normal main use reads it and shallow-copies the family dict. |
| failure | Missing key/type/OOM problems propagate in consumers; importing prose does not validate a subsystem. |
| cost | O(entry text/reference size) fixed import storage; rendering copies Markdown strings and performs per-reference filesystem existence tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
@source-span:L298-L305:sha256:68dd811f0f1ae3c356de72312d5fa7b3fa48f4c1ecbc8c2bd59b20bce5233e91
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete the unchanged examples-context tail after the dictionary scaffolding boundary shifts. |
| inputs / outputs | Offline examples invariant/ownership/failure/cost/reference literals and the CONTRACTS dictionary closure; no example or native query runs here. |
| invariants | The display context distinguishes setup, measurement and engine semantics. This new span supplies structural coverage of unchanged text; it does not add a behavior or certify every example. |
| ownership | Shared ordinary Python literal metadata is imported by the offline generator, outside all native query accounts. |
| failure | Existing documentation import/render failures propagate; dictionary closure adds no error handler or runtime effect. |
| cost | Cold literal import and generated text copies only, with no ordinary query-update cost. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_review.md](../../../code_review.md) |

## B0010

[Lines 306–341](../../../../tools/code_specs_support.py#L306); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ROLES = {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide display labels for exact source paths and fallback stems in inspection maps. |
| inputs / outputs | Exact source paths and fallback stems map to display labels; five new roles identify difference admission/runtime and the shared private CQ freezer/visitor. |
| invariants | Role strings provide offline inspection context only; all preexisting entries remain exact. Added labels select no algorithm, guarantee or recovery authority. |
| ownership | The imported Python module owns ordinary mutable dictionary/string values. |
| failure | Malformed data/import allocation can still fail at import; no new handler or runtime path exists. |
| cost | Four new fixed dictionary entries in an offline module; generator exact-path/fallback-stem lookup and native operation costs are unchanged. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/README.md](../../README.md) |

```text
'include/crown/frontend/aggregate.hpp':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label include/crown/frontend/aggregate.hpp by its actual aggregate responsibility. |
| inputs / outputs | Exact source path -&gt; Declare immutable aggregate input/group/measure/output descriptors and checked integer-column guards. |
| invariants | This entry supplies display text only; it neither certifies every block nor grants a paper/runtime bound. |
| ownership | Ordinary dictionary/string data owned by the offline Python module. |
| failure | Import/allocation errors propagate through the existing tool boundary; no handler is added. |
| cost | One fixed key/value pair is held in the imported module dictionary. For each discovered source entry, the generator evaluates the exact-path lookup and the fallback-stem lookup; this is offline map generation with no product operation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [include/crown/frontend/aggregate.hpp](../../../../include/crown/frontend/aggregate.hpp), [docs/aggregates.md](../../../aggregates.md), [docs/code_specs/README.md](../../README.md) |

```text
'include/crown/runtime/aggregate.hpp':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label include/crown/runtime/aggregate.hpp by its actual aggregate responsibility. |
| inputs / outputs | Exact source path -&gt; Declare nullable owning aggregate tuples, grouped state, atomic prepared batches and owning output. |
| invariants | This entry supplies display text only; it neither certifies every block nor grants a paper/runtime bound. |
| ownership | Ordinary dictionary/string data owned by the offline Python module. |
| failure | Import/allocation errors propagate through the existing tool boundary; no handler is added. |
| cost | One fixed key/value pair is held in the imported module dictionary. For each discovered source entry, the generator evaluates the exact-path lookup and the fallback-stem lookup; this is offline map generation with no product operation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [include/crown/runtime/aggregate.hpp](../../../../include/crown/runtime/aggregate.hpp), [docs/aggregates.md](../../../aggregates.md), [docs/code_specs/README.md](../../README.md) |

```text
'src/frontend/aggregate.cpp':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label src/frontend/aggregate.cpp by its actual aggregate responsibility. |
| inputs / outputs | Exact source path -&gt; Bind admitted aggregate SQL into exact typed grouping, COUNT/SUM/AVG measures and immutable cast guards. |
| invariants | This entry supplies display text only; it neither certifies every block nor grants a paper/runtime bound. |
| ownership | Ordinary dictionary/string data owned by the offline Python module. |
| failure | Import/allocation errors propagate through the existing tool boundary; no handler is added. |
| cost | One fixed key/value pair is held in the imported module dictionary. For each discovered source entry, the generator evaluates the exact-path lookup and the fallback-stem lookup; this is offline map generation with no product operation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [src/frontend/aggregate.cpp](../../../../src/frontend/aggregate.cpp), [docs/aggregates.md](../../../aggregates.md), [docs/code_specs/README.md](../../README.md) |

```text
'src/runtime/aggregate.cpp':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label src/runtime/aggregate.cpp by its actual aggregate responsibility. |
| inputs / outputs | Exact source path -&gt; Maintain accounted logical input-row multiplicities and exact COUNT/SUM/AVG group proposals through one prepared aggregate batch. |
| invariants | This entry supplies display text only; it neither certifies every block nor grants a paper/runtime bound. |
| ownership | Ordinary dictionary/string data owned by the offline Python module. |
| failure | Import/allocation errors propagate through the existing tool boundary; no handler is added. |
| cost | One fixed key/value pair is held in the imported module dictionary. For each discovered source entry, the generator evaluates the exact-path lookup and the fallback-stem lookup; this is offline map generation with no product operation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [src/runtime/aggregate.cpp](../../../../src/runtime/aggregate.cpp), [docs/aggregates.md](../../../aggregates.md), [docs/code_specs/README.md](../../README.md) |

```text
'src/runtime/aggregate_integer.hpp':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label src/runtime/aggregate_integer.hpp by its actual aggregate responsibility. |
| inputs / outputs | Exact source path -&gt; Provide fixed-width exact integer products, signed accumulators and decimal rounding for aggregate arithmetic. |
| invariants | This entry supplies display text only; it neither certifies every block nor grants a paper/runtime bound. |
| ownership | Ordinary dictionary/string data owned by the offline Python module. |
| failure | Import/allocation errors propagate through the existing tool boundary; no handler is added. |
| cost | One fixed key/value pair is held in the imported module dictionary. For each discovered source entry, the generator evaluates the exact-path lookup and the fallback-stem lookup; this is offline map generation with no product operation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [src/runtime/aggregate_integer.hpp](../../../../src/runtime/aggregate_integer.hpp), [docs/aggregates.md](../../../aggregates.md), [docs/code_specs/README.md](../../README.md) |

```text
'src/runtime/aggregate_tuple.cpp':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label src/runtime/aggregate_tuple.cpp by its actual aggregate responsibility. |
| inputs / outputs | Exact source path -&gt; Own nullable aggregate tuple cells and copied text with accounted payloads and borrowed read-only views. |
| invariants | This entry supplies display text only; it neither certifies every block nor grants a paper/runtime bound. |
| ownership | Ordinary dictionary/string data owned by the offline Python module. |
| failure | Import/allocation errors propagate through the existing tool boundary; no handler is added. |
| cost | One fixed key/value pair is held in the imported module dictionary. For each discovered source entry, the generator evaluates the exact-path lookup and the fallback-stem lookup; this is offline map generation with no product operation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [src/runtime/aggregate_tuple.cpp](../../../../src/runtime/aggregate_tuple.cpp), [docs/aggregates.md](../../../aggregates.md), [docs/code_specs/README.md](../../README.md) |

```text
@source-span:L329-L329:sha256:98e1a4110c01b0b3f44210d07b051928d0ababb0dc33b82baaeb8b2b3ca274cc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label include/crown/runtime/topk.hpp by its actual optional snapshot top-k role. |
| inputs / outputs | Offline generator imports this literal context/role for source inspection pages; no query input is evaluated. |
| invariants | Top-k is separate from Boolean support and planner candidate ranking. Context preserves rendered SQL value order, group identity, compressed multiplicity and separate producer/sort budgets. A display label is not semantic certification. |
| ownership | Ordinary Python dictionary/string metadata is shared by the offline generator, outside all native query accounts. |
| failure | Import or rendering errors use the existing documentation-tool boundary; this literal installs no runtime error handling. |
| cost | One offline literal import plus generated text/reference copies; no query execution or update-path work. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/topk.md](../../../topk.md), [Refactor.md](../../../../Refactor.md) |

```text
@source-span:L330-L330:sha256:9ac2b819b25ce2a3f9753759b1953dabb25834efe010b58f7eeac42ce4f97e48
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label src/runtime/topk.cpp by its actual optional snapshot top-k role. |
| inputs / outputs | Offline generator imports this literal context/role for source inspection pages; no query input is evaluated. |
| invariants | Top-k is separate from Boolean support and planner candidate ranking. Context preserves rendered SQL value order, group identity, compressed multiplicity and separate producer/sort budgets. A display label is not semantic certification. |
| ownership | Ordinary Python dictionary/string metadata is shared by the offline generator, outside all native query accounts. |
| failure | Import or rendering errors use the existing documentation-tool boundary; this literal installs no runtime error handling. |
| cost | One offline literal import plus generated text/reference copies; no query execution or update-path work. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/topk.md](../../../topk.md), [Refactor.md](../../../../Refactor.md) |

```text
@source-span:L331-L331:sha256:c5af04b9ac4881e45bbc0eb034cb7be5f6611058ee5936f1c115042e09ac695e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label the actual cold guarded-key source role. |
| inputs / outputs | Offline generator imports literal usage context/role labels; no query or database is evaluated. |
| invariants | Enforced authority, live witnesses, private-variable guards, full source enforcement and reduced-only proof scope remain explicit. Labels are not correctness authority or automatic selection. |
| ownership | Ordinary Python dictionary/string metadata outside native query accounts; retained generated text is offline output. |
| failure | Existing import/render failures propagate at the documentation tool boundary; no runtime error handling is added. |
| cost | One cold literal import plus output copies/references; no runtime or ordinary update work. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/key_specialization.md](../../../key_specialization.md), [Refactor.md](../../../../Refactor.md) |

```text
@source-span:L332-L332:sha256:eab4a179bd1ebe9c697efa3d1e4a3bc447f1bc421089d00ca6009c88b6fa39ca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label the actual cold guarded-key source role. |
| inputs / outputs | Offline generator imports literal usage context/role labels; no query or database is evaluated. |
| invariants | Enforced authority, live witnesses, private-variable guards, full source enforcement and reduced-only proof scope remain explicit. Labels are not correctness authority or automatic selection. |
| ownership | Ordinary Python dictionary/string metadata outside native query accounts; retained generated text is offline output. |
| failure | Existing import/render failures propagate at the documentation tool boundary; no runtime error handling is added. |
| cost | One cold literal import plus output copies/references; no runtime or ordinary update work. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/key_specialization.md](../../../key_specialization.md), [Refactor.md](../../../../Refactor.md) |

```text
@source-span:L322-L322:sha256:896130cb9f79e711da5cb2d19ee491753fe5d0296844764a501f8a8db95b0990
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare immutable cold literal-family admission and original/source-only provenance. |
| inputs / outputs | Exact path include/crown/planner/star.hpp maps to its source responsibility display label. |
| invariants | A role string supplies offline inspection context and proves neither every block nor a runtime/paper bound. |
| ownership | One ordinary Python dictionary key/string value, outside all native query accounts. |
| failure | Existing import/render failures propagate; this literal adds no error-handling mechanism. |
| cost | One fixed offline entry and dictionary lookup during generation; no product operation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [include/crown/planner/star.hpp](../../../../include/crown/planner/star.hpp), [docs/star.md](../../../star.md) |

```text
@source-span:L323-L323:sha256:006ad350f5612d8bba3f5522cbe421b7ed2fe9886f5a76aea6f507a03aee385c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe actual cold center/satellite/head checks and empty occurrence-route lowering. |
| inputs / outputs | Exact path src/planner/star.cpp maps to its source responsibility display label. |
| invariants | A role string supplies offline inspection context and proves neither every block nor a runtime/paper bound. |
| ownership | One ordinary Python dictionary key/string value, outside all native query accounts. |
| failure | Existing import/render failures propagate; this literal adds no error-handling mechanism. |
| cost | One fixed offline entry and dictionary lookup during generation; no product operation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [src/planner/star.cpp](../../../../src/planner/star.cpp), [docs/star.md](../../../star.md) |

```text
@source-span:L324-L324:sha256:1670061fe4e933a64f29698ba970505e02ae477bc6f88bf78c4acd2b1f599503
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the public finite-account atomic owner, exact cursor and work/degree/label gauges. |
| inputs / outputs | Exact path include/crown/runtime/star.hpp maps to its source responsibility display label. |
| invariants | A role string supplies offline inspection context and proves neither every block nor a runtime/paper bound. |
| ownership | One ordinary Python dictionary key/string value, outside all native query accounts. |
| failure | Existing import/render failures propagate; this literal adds no error-handling mechanism. |
| cost | One fixed offline entry and dictionary lookup during generation; no product operation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [include/crown/runtime/star.hpp](../../../../include/crown/runtime/star.hpp), [docs/star.md](../../../star.md) |

```text
@source-span:L325-L325:sha256:1718de75899efca6652b8d5e56571cb42814d5a6985282b1589c4dd9c906b2de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe accounted records, intrusive degree links, counted projections and compact inverse journal. |
| inputs / outputs | Exact path src/runtime/star_detail.hpp maps to its source responsibility display label. |
| invariants | A role string supplies offline inspection context and proves neither every block nor a runtime/paper bound. |
| ownership | One ordinary Python dictionary key/string value, outside all native query accounts. |
| failure | Existing import/render failures propagate; this literal adds no error-handling mechanism. |
| cost | One fixed offline entry and dictionary lookup during generation; no product operation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [src/runtime/star_detail.hpp](../../../../src/runtime/star_detail.hpp), [docs/star.md](../../../star.md) |

```text
@source-span:L326-L326:sha256:67f06c7797afcbcf6ffb7971ceadcb2099e43dc5bddc7e69124e9228371263e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe exact generalized H with occupied degree buckets and private prepaid publication. |
| inputs / outputs | Exact path src/runtime/star_hindex.hpp maps to its source responsibility display label. |
| invariants | A role string supplies offline inspection context and proves neither every block nor a runtime/paper bound. |
| ownership | One ordinary Python dictionary key/string value, outside all native query accounts. |
| failure | Existing import/render failures propagate; this literal adds no error-handling mechanism. |
| cost | One fixed offline entry and dictionary lookup during generation; no product operation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [src/runtime/star_hindex.hpp](../../../../src/runtime/star_hindex.hpp), [docs/star.md](../../../star.md) |

```text
@source-span:L327-L327:sha256:84ced0362968f9c0d2d4afe60fa2b9d7d3376c2c4d039a8f746cf4dc1b8e6c10
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe actual light groups, heavy predicates, sparse migrations and full-source validation. |
| inputs / outputs | Exact path src/runtime/star.cpp maps to its source responsibility display label. |
| invariants | A role string supplies offline inspection context and proves neither every block nor a runtime/paper bound. |
| ownership | One ordinary Python dictionary key/string value, outside all native query accounts. |
| failure | Existing import/render failures propagate; this literal adds no error-handling mechanism. |
| cost | One fixed offline entry and dictionary lookup during generation; no product operation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [src/runtime/star.cpp](../../../../src/runtime/star.cpp), [docs/star.md](../../../star.md) |

```text
@source-span:L328-L328:sha256:651f9ef5cbad097b27db756f5adcaece7420e6a05f773abf121861b7a67df603
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe candidate pacing, borrowed-key deduplication and owning outputs under a read lease. |
| inputs / outputs | Exact path src/runtime/star_cursor.cpp maps to its source responsibility display label. |
| invariants | A role string supplies offline inspection context and proves neither every block nor a runtime/paper bound. |
| ownership | One ordinary Python dictionary key/string value, outside all native query accounts. |
| failure | Existing import/render failures propagate; this literal adds no error-handling mechanism. |
| cost | One fixed offline entry and dictionary lookup during generation; no product operation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [src/runtime/star_cursor.cpp](../../../../src/runtime/star_cursor.cpp), [docs/star.md](../../../star.md) |

```text
@source-span:L318-L318:sha256:47ce52a20e596d75c1e7215c1408e722c47f73fbc6170de19088dbc927737bf1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the actual responsibility of include/crown/planner/comparisons.hpp. |
| inputs / outputs | 'include/crown/planner/comparisons.hpp': 'Declare immutable opt-in exact comparison predicates and typed cold admission over genuine equality-CQ plans.', |
| invariants | The exact-path role is offline display text, not semantic certification, optimizer selection or paper authority. |
| ownership | One ordinary Python dictionary key/string value; no native owner. |
| failure | Existing import/render failures propagate; no runtime handler. |
| cost | One fixed metadata entry and an offline dictionary lookup. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [include/crown/planner/comparisons.hpp](../../../../include/crown/planner/comparisons.hpp), [docs/comparisons.md](../../../comparisons.md), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py) |

```text
@source-span:L319-L319:sha256:91bac734be9770ffdb678d75b1235484c6d4b9cb145c5ec963e413a60dd48ce3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the actual responsibility of src/planner/comparisons.cpp. |
| inputs / outputs | 'src/planner/comparisons.cpp': 'Check operator/variable/type and literal-byte admission while preserving the original equality query and plan authority.', |
| invariants | The exact-path role is offline display text, not semantic certification, optimizer selection or paper authority. |
| ownership | One ordinary Python dictionary key/string value; no native owner. |
| failure | Existing import/render failures propagate; no runtime handler. |
| cost | One fixed metadata entry and an offline dictionary lookup. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [src/planner/comparisons.cpp](../../../../src/planner/comparisons.cpp), [docs/comparisons.md](../../../comparisons.md), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py) |

```text
@source-span:L320-L320:sha256:01e8a05f1d3213835c54df85e8e7794095289d8ac5f0e885053a57684a490acb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the actual responsibility of include/crown/runtime/comparisons.hpp. |
| inputs / outputs | 'include/crown/runtime/comparisons.hpp': 'Declare exact comparison binding, finite recomputation grants, owning snapshots and atomic endpoint set deltas.', |
| invariants | The exact-path role is offline display text, not semantic certification, optimizer selection or paper authority. |
| ownership | One ordinary Python dictionary key/string value; no native owner. |
| failure | Existing import/render failures propagate; no runtime handler. |
| cost | One fixed metadata entry and an offline dictionary lookup. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [include/crown/runtime/comparisons.hpp](../../../../include/crown/runtime/comparisons.hpp), [docs/comparisons.md](../../../comparisons.md), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py) |

```text
@source-span:L321-L321:sha256:b8b2c8cc60fcae8f5bd3912bc80780bbffb39fc562341178d24488375cc0312f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the actual responsibility of src/runtime/comparisons.cpp. |
| inputs / outputs | 'src/runtime/comparisons.cpp': 'Reuse ordinary propagation and full hidden-variable assignments, filter before projection, deduplicate and publish prepaid source/result state.', |
| invariants | The exact-path role is offline display text, not semantic certification, optimizer selection or paper authority. |
| ownership | One ordinary Python dictionary key/string value; no native owner. |
| failure | Existing import/render failures propagate; no runtime handler. |
| cost | One fixed metadata entry and an offline dictionary lookup. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [src/runtime/comparisons.cpp](../../../../src/runtime/comparisons.cpp), [docs/comparisons.md](../../../comparisons.md), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py) |

```text
@source-span:L313-L313:sha256:d575d186fc13624aecf6518290fb4eb2096d218d44ccced4177e616659b17dad
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label the actual responsibility of include/crown/planner/fallback.hpp. |
| inputs / outputs | 'include/crown/planner/fallback.hpp': 'Declare immutable explicit classical-CQ fallback admission, actual structural class, guarantee profile and advisory row estimates.', |
| invariants | Exact-path role text is display context only; it grants no runtime authority or performance bound. |
| ownership | One ordinary dictionary key and string value. |
| failure | Offline import/render failures propagate. |
| cost | One metadata entry and offline lookup. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [include/crown/planner/fallback.hpp](../../../../include/crown/planner/fallback.hpp), [docs/fallback.md](../../../fallback.md), [docs/source_images.md](../../../source_images.md) |

```text
@source-span:L314-L314:sha256:54c51a1fb3e1c023b3eed32b7d82e029bb965fe108932a0bd8bba0151116f78b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label the actual responsibility of src/planner/fallback.cpp. |
| inputs / outputs | 'src/planner/fallback.cpp': 'Bound cold metadata work, recognize the original query and lower a full-catalog source-only coordinator without claiming a CROWN or GHD certificate.', |
| invariants | Exact-path role text is display context only; it grants no runtime authority or performance bound. |
| ownership | One ordinary dictionary key and string value. |
| failure | Offline import/render failures propagate. |
| cost | One metadata entry and offline lookup. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [src/planner/fallback.cpp](../../../../src/planner/fallback.cpp), [docs/fallback.md](../../../fallback.md), [docs/source_images.md](../../../source_images.md) |

```text
@source-span:L315-L315:sha256:1999d2ccbecec7ef15babfdae1716c364ea194bfc64f4ea0575f062588e18129
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label the actual responsibility of include/crown/runtime/fallback.hpp. |
| inputs / outputs | 'include/crown/runtime/fallback.hpp': 'Declare finite independent exact fallback ownership, owning snapshots, atomic endpoint deltas and explicit materialization costs.', |
| invariants | Exact-path role text is display context only; it grants no runtime authority or performance bound. |
| ownership | One ordinary dictionary key and string value. |
| failure | Offline import/render failures propagate. |
| cost | One metadata entry and offline lookup. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [include/crown/runtime/fallback.hpp](../../../../include/crown/runtime/fallback.hpp), [docs/fallback.md](../../../fallback.md), [docs/source_images.md](../../../source_images.md) |

```text
@source-span:L316-L316:sha256:dbcb3bf34b25e59ce6f1fd4e4cc3f1ff7644232336284153b24a5c98588e418c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label the actual responsibility of src/runtime/fallback.cpp. |
| inputs / outputs | 'src/runtime/fallback.cpp': 'Capture funded physical source images, enumerate complete assignments iteratively, project and deduplicate privately, then publish prepaid source/result state.', |
| invariants | Exact-path role text is display context only; it grants no runtime authority or performance bound. |
| ownership | One ordinary dictionary key and string value. |
| failure | Offline import/render failures propagate. |
| cost | One metadata entry and offline lookup. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [src/runtime/fallback.cpp](../../../../src/runtime/fallback.cpp), [docs/fallback.md](../../../fallback.md), [docs/source_images.md](../../../source_images.md) |

```text
@source-span:L317-L317:sha256:2823f4a45a230160b35993d9f339f8a8996249ffb128e33ba6db0d747944a246
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label the actual responsibility of include/crown/runtime/source_image.hpp. |
| inputs / outputs | 'include/crown/runtime/source_image.hpp': 'Declare deep accounted current or prepared physical source images with explicit row and work grants and no checkpoint authority.', |
| invariants | Exact-path role text is display context only; it grants no runtime authority or performance bound. |
| ownership | One ordinary dictionary key and string value. |
| failure | Offline import/render failures propagate. |
| cost | One metadata entry and offline lookup. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [include/crown/runtime/source_image.hpp](../../../../include/crown/runtime/source_image.hpp), [docs/fallback.md](../../../fallback.md), [docs/source_images.md](../../../source_images.md) |

```text
@source-span:L308-L308:sha256:9c85a72385a6812ac97c7fbdee83e4735509a6ca4d6b782306bc0fc48d964fcd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the actual responsibility of include/crown/planner/difference.hpp. |
| inputs / outputs | 'include/crown/planner/difference.hpp': 'Declare explicit set/bag difference admission, immutable positive operands, actual structural profiles and advisory residual bounds.', |
| invariants | Exact-path display text grants no algorithm, proof, optimizer or recovery authority. |
| ownership | One ordinary metadata key/string value. |
| failure | Offline import/render failures propagate. |
| cost | One offline dictionary entry and lookup. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [include/crown/planner/difference.hpp](../../../../include/crown/planner/difference.hpp), [docs/difference.md](../../../difference.md) |

```text
@source-span:L309-L309:sha256:bad9c69edf903c9c3b980783ff806f14a7e3ce92f4ee92c9f5d25cb7bb339bd1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the actual responsibility of src/planner/difference.cpp. |
| inputs / outputs | 'src/planner/difference.cpp': 'Admit both original operands over the same catalog and check ordered output types without subtracting unrelated upper bounds.', |
| invariants | Exact-path display text grants no algorithm, proof, optimizer or recovery authority. |
| ownership | One ordinary metadata key/string value. |
| failure | Offline import/render failures propagate. |
| cost | One offline dictionary entry and lookup. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [src/planner/difference.cpp](../../../../src/planner/difference.cpp), [docs/difference.md](../../../difference.md) |

```text
@source-span:L310-L310:sha256:3429e94beb91279ffce1648d712e457877d0f5f19a6b7908942b3ed96233340d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the actual responsibility of include/crown/runtime/difference.hpp. |
| inputs / outputs | 'include/crown/runtime/difference.hpp': 'Declare independent exact difference ownership, compressed checked counts and exact endpoint replacements distinct from aggregate payloads.', |
| invariants | Exact-path display text grants no algorithm, proof, optimizer or recovery authority. |
| ownership | One ordinary metadata key/string value. |
| failure | Offline import/render failures propagate. |
| cost | One offline dictionary entry and lookup. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [include/crown/runtime/difference.hpp](../../../../include/crown/runtime/difference.hpp), [docs/difference.md](../../../difference.md) |

```text
@source-span:L311-L311:sha256:1cdb43776c520d9e6f33da476ff4a724b05f02821c2820e06a4edf201c928f06
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the actual responsibility of src/runtime/difference.cpp. |
| inputs / outputs | 'src/runtime/difference.cpp': 'Recompute both positive operands from one funded source image, consolidate set/bag residuals and publish prepared endpoint counts atomically.', |
| invariants | Exact-path display text grants no algorithm, proof, optimizer or recovery authority. |
| ownership | One ordinary metadata key/string value. |
| failure | Offline import/render failures propagate. |
| cost | One offline dictionary entry and lookup. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [src/runtime/difference.cpp](../../../../src/runtime/difference.cpp), [docs/difference.md](../../../difference.md) |

```text
@source-span:L312-L312:sha256:db1c4f8033f6746a4d6560808c0175e894586cfcbab603251f97f7fe822fd22c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the actual responsibility of src/runtime/cq_recompute.hpp. |
| inputs / outputs | 'src/runtime/cq_recompute.hpp': 'Share original-account native query freezing and iterative witness traversal with borrowed callbacks and caller-selected consolidation.', |
| invariants | Exact-path display text grants no algorithm, proof, optimizer or recovery authority. |
| ownership | One ordinary metadata key/string value. |
| failure | Offline import/render failures propagate. |
| cost | One offline dictionary entry and lookup. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [src/runtime/cq_recompute.hpp](../../../../src/runtime/cq_recompute.hpp), [docs/difference.md](../../../difference.md) |

## B0011

[Lines 342–377](../../../../tools/code_specs_support.py#L342); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
'error': 'Own a public diagnostic code/message using std::runtime_error; this header carries no planner/runtime validity guarantee.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem error: Own a public diagnostic code/message using std::runtime_error; this header carries no planner/runtime validity guarantee. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing error still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'weighted': 'Execute weighted logical replacements and projected tuple/multiplicity enumeration with separate full messages, local visible factors and compact undo.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem weighted: Execute weighted logical replacements and projected tuple/multiplicity enumeration with separate full messages, local visible factors and compact undo. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing weighted still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'digest': 'Compute and encode canonical SHA-256 digests used for artifact identity.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem digest: Compute and encode canonical SHA-256 digests used for artifact identity. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing digest still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'scalar': 'Parse, compare, hash and format exact scalar DTO values.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem scalar: Parse, compare, hash and format exact scalar DTO values. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing scalar still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'model': 'Define/validate query variables, atom occurrences, scopes and output metadata.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem model: Define/validate query variables, atom occurrences, scopes and output metadata. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing model still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'ids': 'Give numeric IDs distinct types so owner/component domains are not interchanged accidentally.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem ids: Give numeric IDs distinct types so owner/component domains are not interchanged accidentally. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing ids still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'program_span': 'Expose borrowed spans into immutable native program storage.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem program_span: Expose borrowed spans into immutable native program storage. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing program_span still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'program_model': 'Define account-funded native equivalents of compiler metadata.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem program_model: Define account-funded native equivalents of compiler metadata. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing program_model still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'program_native_types': 'Import/export native compiler metadata using the receiving account.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem program_native_types: Import/export native compiler metadata using the receiving account. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing program_native_types still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'program_replan': 'Rebind and lower checked candidates into native metadata without retaining an ordinary DTO graph.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem program_replan: Rebind and lower checked candidates into native metadata without retaining an ordinary DTO graph. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing program_replan still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'parser': 'Own the libpg_query parse result and expose the admitted parser representation.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem parser: Own the libpg_query parse result and expose the admitted parser representation. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing parser still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'bind': 'Resolve table/column aliases, expressions and exact typed literals against catalog metadata.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem bind: Resolve table/column aliases, expressions and exact typed literals against catalog metadata. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing bind still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'normalize': 'Normalize bound equality predicates, contradictions and SQL output semantics into a typed CQ.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem normalize: Normalize bound equality predicates, contradictions and SQL output semantics into a typed CQ. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing normalize still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'adapter': 'Apply occurrence-local constants/repeated-variable tests and positional projection.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem adapter: Apply occurrence-local constants/repeated-variable tests and positional projection. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing adapter still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'recognize': 'Run GYO reduction for body and augmented-head hypergraphs; distinguish free-connex, acyclic non-free-connex and cyclic cases.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem recognize: Run GYO reduction for body and augmented-head hypergraphs; distinguish free-connex, acyclic non-free-connex and cyclic cases. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing recognize still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'verify': 'Independently validate CROWN tree coverage, guard, connected-variable paths, connex output structure and height claims.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem verify: Independently validate CROWN tree coverage, guard, connected-variable paths, connex output structure and height claims. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing verify still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'exact': 'Implement the local finite partition recurrence/search machine for exact native-height optimization.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem exact: Implement the local finite partition recurrence/search machine for exact native-height optimization. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing exact still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'certificate': 'Replay retained lower-bound evidence independently of search continuation state.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem certificate: Replay retained lower-bound evidence independently of search continuation state. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing certificate still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'fast_paths': 'Retain source-list compatibility while fast-path continuation implementation is owned by search_session.cpp.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem fast_paths: Retain source-list compatibility while fast-path continuation implementation is owned by search_session.cpp. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing fast_paths still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'search_session': 'Advance a resumable exact/fast-path planner session under explicit transition/depth/time limits.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem search_session: Advance a resumable exact/fast-path planner session under explicit transition/depth/time limits. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing search_session still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'candidate_generator': 'Enumerate candidate tree structures with an explicit generator frontier.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem candidate_generator: Enumerate candidate tree structures with an explicit generator frontier. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing candidate_generator still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'candidate_key': 'Compute canonical candidate identity through a bounded resumable key machine.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem candidate_key: Compute canonical candidate identity through a bounded resumable key machine. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing candidate_key still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'candidates': 'Retain and enumerate checked minimum-height candidate alternatives under bounded content budgets.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem candidates: Retain and enumerate checked minimum-height candidate alternatives under bounded content budgets. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 4 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing candidates still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'residual_reduce': 'Build residual reduction traces from query scopes and output structure.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem residual_reduce: Build residual reduction traces from query scopes and output structure. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing residual_reduce still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'residual_trace': 'Replay and validate each claimed reduction step against the source query.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem residual_trace: Replay and validate each claimed reduction step against the source query. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing residual_trace still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'residual_reconstruct': 'Reconstruct and check candidate trees, retaining the exact-repair boundary for counterexamples.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem residual_reconstruct: Reconstruct and check candidate trees, retaining the exact-repair boundary for counterexamples. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing residual_reconstruct still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'ranking_integer': 'Perform bounded exact integer score arithmetic without floating-point ordering changes.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem ranking_integer: Perform bounded exact integer score arithmetic without floating-point ordering changes. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing ranking_integer still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'selection_budget': 'Account selection work/resources/timing and translate component stop reasons.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem selection_budget: Account selection work/resources/timing and translate component stop reasons. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing selection_budget still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'selection_cache': 'Manage bounded FIFO plan entries while retaining each entry\'s allocating account.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem selection_cache: Manage bounded FIFO plan entries while retaining each entry's allocating account. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing selection_cache still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'selection_binding': 'Require exact source/query/backend binding before admitting cached or candidate plan authority.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem selection_binding: Require exact source/query/backend binding before admitting cached or candidate plan authority. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing selection_binding still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'include/crown/io/memory_report.hpp': 
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare explicit caller-owned memory-report JSON export; this header does not collect native memory. |
| inputs / outputs | Exact maintained source path selects this display label before stem fallback. |
| invariants | This labels a source map; it supplies no checked runtime/planner authority. Consult the linked source for its executable contract. |
| ownership | Module-owned dictionary key/value strings; lookup borrows immutable strings. |
| failure | Import/allocation errors propagate; the display role introduces no runtime error handler. |
| cost | Fixed offline dictionary/string storage and average constant-time role lookup; no native runtime work. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [include/crown/io/memory_report.hpp](../../../../include/crown/io/memory_report.hpp), [docs/code_specs/README.md](../../README.md) |

```text
'src/io/memory_report.cpp': 
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a retained native memory report into ordinary JSON without rescanning live accounts/tables. |
| inputs / outputs | Exact maintained source path selects this display label before stem fallback. |
| invariants | This labels a source map; it supplies no checked runtime/planner authority. Consult the linked source for its executable contract. |
| ownership | Module-owned dictionary key/value strings; lookup borrows immutable strings. |
| failure | Import/allocation errors propagate; the display role introduces no runtime error handler. |
| cost | Fixed offline dictionary/string storage and average constant-time role lookup; no native runtime work. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [src/io/memory_report.cpp](../../../../src/io/memory_report.cpp), [docs/code_specs/README.md](../../README.md) |

```text
'include/crown/io/support.hpp': 
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare logical-support diagnostic trace import and snapshot/epoch JSON export. |
| inputs / outputs | Exact maintained source path selects this display label before stem fallback. |
| invariants | This labels a source map; it supplies no checked runtime/planner authority. Consult the linked source for its executable contract. |
| ownership | Module-owned dictionary key/value strings; lookup borrows immutable strings. |
| failure | Import/allocation errors propagate; the display role introduces no runtime error handler. |
| cost | Fixed offline dictionary/string storage and average constant-time role lookup; no native runtime work. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [include/crown/io/support.hpp](../../../../include/crown/io/support.hpp), [docs/code_specs/README.md](../../README.md) |

```text
'src/io/support.cpp': 
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse logical-support diagnostic Rows and serialize retained support state/journals without applying updates. |
| inputs / outputs | Exact maintained source path selects this display label before stem fallback. |
| invariants | This labels a source map; it supplies no checked runtime/planner authority. Consult the linked source for its executable contract. |
| ownership | Module-owned dictionary key/value strings; lookup borrows immutable strings. |
| failure | Import/allocation errors propagate; the display role introduces no runtime error handler. |
| cost | Fixed offline dictionary/string storage and average constant-time role lookup; no native runtime work. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [src/io/support.cpp](../../../../src/io/support.cpp), [docs/code_specs/README.md](../../README.md) |

```text
'tests/integration/support.py': 
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise support CLI diagnostics against independent manual state and transition expectations. |
| inputs / outputs | Exact maintained source path selects this display label before stem fallback. |
| invariants | This labels a source map; it supplies no checked runtime/planner authority. Consult the linked source for its executable contract. |
| ownership | Module-owned dictionary key/value strings; lookup borrows immutable strings. |
| failure | Import/allocation errors propagate; the display role introduces no runtime error handler. |
| cost | Fixed offline dictionary/string storage and average constant-time role lookup; no native runtime work. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [tests/integration/support.py](../../../../tests/integration/support.py), [docs/code_specs/README.md](../../README.md) |

## B0012

[Lines 378–413](../../../../tools/code_specs_support.py#L378); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
'hash_directory': 'Provide separately chained stable-node hash lookup and prepared bucket-array growth.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem hash_directory: Provide separately chained stable-node hash lookup and prepared bucket-array growth. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing hash_directory still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'live_list': 'Provide intrusive nonowning membership and O(1) prepaid link/unlink for live traversal.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem live_list: Provide intrusive nonowning membership and O(1) prepaid link/unlink for live traversal. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing live_list still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'indexed_nodes': 'Define separately owned row/key/member nodes and their directory/live-list hooks.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem indexed_nodes: Define separately owned row/key/member nodes and their directory/live-list hooks. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing indexed_nodes still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'accounted_indexed_nodes': 'Own native indexed nodes using the exact allocator embedded before destruction.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem accounted_indexed_nodes: Own native indexed nodes using the exact allocator embedded before destruction. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing accounted_indexed_nodes still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'indexed_journal': 'Record/reverse standalone indexed mutations using prepaid growth, pinned nodes and saved neighbors.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem indexed_journal: Record/reverse standalone indexed mutations using prepaid growth, pinned nodes and saved neighbors. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing indexed_journal still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'accounted_indexed_journal': 'Record/reverse native indexed mutations using the original account/work grant.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem accounted_indexed_journal: Record/reverse native indexed mutations using the original account/work grant. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing accounted_indexed_journal still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'index_work': 'Admit every work dimension atomically from one noncopyable operation balance.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem index_work: Admit every work dimension atomically from one noncopyable operation balance. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing index_work still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'index_work_alias': 'Expose different diagnostic policies over the same canonical work balance.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem index_work_alias: Expose different diagnostic policies over the same canonical work balance. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing index_work_alias still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'accounted_ordered_rows': 'Own ordered row-set/map nodes with exact allocation ownership and nonallocating extraction/reinsertion.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem accounted_ordered_rows: Own ordered row-set/map nodes with exact allocation ownership and nonallocating extraction/reinsertion. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing accounted_ordered_rows still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'storage_work': 'Create a finite grant only for an outer indexed operation; retain/rebind it across nested and resumed work.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem storage_work: Create a finite grant only for an outer indexed operation; retain/rebind it across nested and resumed work. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing storage_work still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'constraint_validation': 'Validate complete native proposed source snapshots and enforced constraints under the query account.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem constraint_validation: Validate complete native proposed source snapshots and enforced constraints under the query account. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing constraint_validation still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'support': 'Maintain record/S/P/E support state and current/epoch cursor leases.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem support: Maintain record/S/P/E support state and current/epoch cursor leases. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 5 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing support still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'delta': 'Maintain live visible-factor indexes, canonical delta producers and retained delivery epochs.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem delta: Maintain live visible-factor indexes, canonical delta producers and retained delivery epochs. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing delta still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'session': 'Own input-to-output and durable lifecycle transitions for one creator-thread query session.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem session: Own input-to-output and durable lifecycle transitions for one creator-thread query session. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing session still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'window': 'Maintain operational event-time/FIFO membership and prepared expiration transitions.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem window: Maintain operational event-time/FIFO membership and prepared expiration transitions. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing window still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'native_statistics': 'Build bounded native distributions using borrowed compact rows and shared storage work.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem native_statistics: Build bounded native distributions using borrowed compact rows and shared storage work. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing native_statistics still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'owner_statistics': 'Capture selected table/index distributions with owner/sequence stamps and partial-completion status.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem owner_statistics: Capture selected table/index distributions with owner/sequence stamps and partial-completion status. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing owner_statistics still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'memory_report': 'Capture/reconcile account allocation partitions with logical runtime ownership.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem memory_report: Capture/reconcile account allocation partitions with logical runtime ownership. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 4 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing memory_report still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'observation': 'Collect optional counters/traces/clocks while preserving measured-zero versus unavailable fields.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem observation: Collect optional counters/traces/clocks while preserving measured-zero versus unavailable fields. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing observation still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'event_reader': 'Decode bounded stream records into funded native updates while retaining input progress.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem event_reader: Decode bounded stream records into funded native updates while retaining input progress. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing event_reader still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'native_decode': 'Parse exact scalar fields directly into compact native values.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem native_decode: Parse exact scalar fields directly into compact native values. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing native_decode still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'input_progress': 'Track exact resumable record/source position independently of runtime/output sequence.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem input_progress: Track exact resumable record/source position independently of runtime/output sequence. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing input_progress still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'compiler_plan_artifact': 'Read/write explicit compiler-owned plan artifacts at the native admission boundary.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem compiler_plan_artifact: Read/write explicit compiler-owned plan artifacts at the native admission boundary. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing compiler_plan_artifact still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'binary_detail': 'Encode/decode bounded fixed-width/versioned recovery fields and exact scalar payloads.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem binary_detail: Encode/decode bounded fixed-width/versioned recovery fields and exact scalar payloads. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing binary_detail still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'journal_file': 'Own locked WAL descriptors, validate prefix state and poison uncertain append attempts.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem journal_file: Own locked WAL descriptors, validate prefix state and poison uncertain append attempts. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing journal_file still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'generation': 'Read/publish durable generation roots with exact identity and selection outcome.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem generation: Read/publish durable generation roots with exact identity and selection outcome. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing generation still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'generation_retirement': 'Retire only history authorized by durable root/delivery state.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem generation_retirement: Retire only history authorized by durable root/delivery state. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 1 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing generation_retirement still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'local_sink': 'Persist canonical complete epoch output and return authority-bearing delivery receipts.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem local_sink: Persist canonical complete epoch output and return authority-bearing delivery receipts. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing local_sink still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'plan_descriptor': 'Encode/decode exact selected-plan descriptor identity for generation recovery.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem plan_descriptor: Encode/decode exact selected-plan descriptor identity for generation recovery. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing plan_descriptor still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
'policy': 'Admit W01 annotation policies and implement exact bounded support/aggregate arithmetic.',
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the current display label for stem policy: Admit W01 annotation policies and implement exact bounded support/aggregate arithmetic. |
| inputs / outputs | Exact stem match in any inventoried family selects this string; current saved inventory has 2 matching paths. |
| invariants | Label is presentation data, not a scoped behavior/ownership proof. Different directories sharing policy still collide under current lookup; inspect actual path and contracts. |
| ownership | Immutable Python string owned by ROLES dict/module; returned file_role shares that object until JSON/Markdown copy. |
| failure | No per-entry validation/catch; fallback happens only if key absent. No native operation is invoked. |
| cost | Fixed label text storage at import and average O(1) dict lookup per matching file; output copies label bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

## B0013

[Lines 414–418](../../../../tools/code_specs_support.py#L414); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L414-L418:sha256:44fb36d8f50772c14b86ad6164bff5440e5a4a1cac507917e63c9f61c63fba61
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete the unchanged tail of exact-path display roles after literal chunk boundaries shift. |
| inputs / outputs | Three existing entries label the SQL source-image unit, unpublished SQL cold-rebuild bridge and whole-image rebuild unit, then close ROLES. |
| invariants | All three strings retain exact prior bytes. They are offline display context, not semantic certification or runtime reconstruction authority. |
| ownership | Three ordinary dictionary key/string pairs and a lexical dictionary boundary. |
| failure | Existing offline import/render failures propagate; no native handler. |
| cost | Fixed metadata construction and offline lookup only. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tests/unit/sql_source_snapshot_test.cpp](../../../../tests/unit/sql_source_snapshot_test.cpp), [src/runtime/sql_cold_rebuild.hpp](../../../../src/runtime/sql_cold_rebuild.hpp), [tests/unit/sql_aggregate_rebuild_test.cpp](../../../../tests/unit/sql_aggregate_rebuild_test.cpp), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py) |

## B0014

[Lines 419–468](../../../../tools/code_specs_support.py#L419); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def family(path):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose subsystem context by ordered path/stem heuristics. |
| inputs / outputs | A repository-relative POSIX path string returns its first matching documentation family. |
| invariants | Earlier build/tests/tools/examples/domain priorities remain exact. New exact difference and runtime cq_recompute rules precede old stem rules; every old rule retains relative order. Documentation routing supplies no executable or proof authority. |
| ownership | Borrows path, owns extracted stem string and returns shared static family label. |
| failure | Nonstring malformed input may throw; unknown ordinary path intentionally falls back ir. |
| cost | Fixed ordered substring/prefix tests O(path/stem bytes), no filesystem or code execution. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
if path.endswith('CMakeLists.txt') or '/cmake/' in '/' + path or path.endswith('.cmake'): return 'build'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route build paths with the exact context priority. |
| inputs / outputs | CMakeLists.txt/.cmake/cmake directory takes precedence even inside tests; returns matching context key or continues later domain tests. |
| invariants | Only string routing; no proof a file implements every described behavior. Ordering is observable when names overlap. |
| ownership | Uses input string/extracted stem and shared literal key; no source/backing owner. |
| failure | No catch or native effect; malformed types may propagate string-method errors. |
| cost | Fixed substring/prefix comparisons and small any() loops; proportional to path/stem bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
if path.startswith('tests/'): return 'tests'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route tests paths with the exact context priority. |
| inputs / outputs | tests root takes precedence over remaining runtime-like stems; returns matching context key or continues later domain tests. |
| invariants | Only string routing; no proof a file implements every described behavior. Ordering is observable when names overlap. |
| ownership | Uses input string/extracted stem and shared literal key; no source/backing owner. |
| failure | No catch or native effect; malformed types may propagate string-method errors. |
| cost | Fixed substring/prefix comparisons and small any() loops; proportional to path/stem bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
if path.startswith('tools/'): return 'tools'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route tools paths with the exact context priority. |
| inputs / outputs | tool sources use tools context; returns matching context key or continues later domain tests. |
| invariants | Only string routing; no proof a file implements every described behavior. Ordering is observable when names overlap. |
| ownership | Uses input string/extracted stem and shared literal key; no source/backing owner. |
| failure | No catch or native effect; malformed types may propagate string-method errors. |
| cost | Fixed substring/prefix comparisons and small any() loops; proportional to path/stem bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
if path.startswith('examples/'): return 'examples'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route examples paths with the exact context priority. |
| inputs / outputs | examples map to demonstration context; returns matching context key or continues later domain tests. |
| invariants | Only string routing; no proof a file implements every described behavior. Ordering is observable when names overlap. |
| ownership | Uses input string/extracted stem and shared literal key; no source/backing owner. |
| failure | No catch or native effect; malformed types may propagate string-method errors. |
| cost | Fixed substring/prefix comparisons and small any() loops; proportional to path/stem bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
if path.startswith('apps/'): return 'examples'
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route apps paths with the exact context priority. |
| inputs / outputs | apps share examples context; returns matching context key or continues later domain tests. |
| invariants | Only string routing; no proof a file implements every described behavior. Ordering is observable when names overlap. |
| ownership | Uses input string/extracted stem and shared literal key; no source/backing owner. |
| failure | No catch or native effect; malformed types may propagate string-method errors. |
| cost | Fixed substring/prefix comparisons and small any() loops; proportional to path/stem bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
if '/planner/' in path:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route planner paths with the exact context priority. |
| inputs / outputs | Planner exact difference precedes fallback and all preexisting planner rules. |
| invariants | Earlier build/tests/tools/examples/domain priorities remain exact. New exact difference and runtime cq_recompute rules precede old stem rules; every old rule retains relative order. Documentation routing supplies no executable or proof authority. |
| ownership | Uses input string/extracted stem and shared literal key; no source/backing owner. |
| failure | No catch or native effect; malformed types may propagate string-method errors. |
| cost | Fixed substring/prefix comparisons and small any() loops; proportional to path/stem bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
if '/storage/' in path:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route storage paths with the exact context priority. |
| inputs / outputs | arena first, layout/row/tuple/projection values, else storage; returns matching context key or continues later domain tests. |
| invariants | Only string routing; no proof a file implements every described behavior. Ordering is observable when names overlap. |
| ownership | Uses input string/extracted stem and shared literal key; no source/backing owner. |
| failure | No catch or native effect; malformed types may propagate string-method errors. |
| cost | Fixed substring/prefix comparisons and small any() loops; proportional to path/stem bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
if '/ir/' in path:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ir paths with the exact context priority. |
| inputs / outputs | scalar values versus other ir; returns matching context key or continues later domain tests. |
| invariants | Only string routing; no proof a file implements every described behavior. Ordering is observable when names overlap. |
| ownership | Uses input string/extracted stem and shared literal key; no source/backing owner. |
| failure | No catch or native effect; malformed types may propagate string-method errors. |
| cost | Fixed substring/prefix comparisons and small any() loops; proportional to path/stem bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
if '/runtime/' in path:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route runtime paths with the exact context priority. |
| inputs / outputs | Runtime exact difference and cq_recompute precede fallback/source_image and all preexisting runtime rules. |
| invariants | Earlier build/tests/tools/examples/domain priorities remain exact. New exact difference and runtime cq_recompute rules precede old stem rules; every old rule retains relative order. Documentation routing supplies no executable or proof authority. |
| ownership | Uses input string/extracted stem and shared literal key; no source/backing owner. |
| failure | No catch or native effect; malformed types may propagate string-method errors. |
| cost | Fixed substring/prefix comparisons and small any() loops; proportional to path/stem bytes. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/code_specs/subsystem_contracts.md](../../subsystem_contracts.md), [docs/code_specs/README.md](../../README.md), [docs/code_review.md](../../../code_review.md) |

```text
@source-span:L458-L458:sha256:af9b9f8e8ee2bc6ce29cb359947304510b0f982d67b5eabfa7cbe0ca26a79ac1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the exact runtime topk stem to snapshot-sort documentation before generic runtime context. |
| inputs / outputs | Borrowed runtime stem topk, after comparisons and star, returns the existing topk documentation context. |
| invariants | Earlier path/domain rules and the new exact difference rule (plus cq_recompute in runtime) precede this old stem rule. Every preexisting stem rule retains relative order. The result selects inspection context only. |
| ownership | Borrows the local stem and returns a shared literal string; no source or native owner. |
| failure | Ordinary malformed path/type behavior remains in family(); this branch adds no catch or native effect. |
| cost | One bounded stem equality after prior path tests; offline only. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/topk.md](../../../topk.md) |

```text
@source-span:L440-L440:sha256:76e109d91ec56189ecbd793e1b1f8b8c1987f0cefa02662b0c4e65450f8a18aa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the exact planner keys stem before the existing generic planner contexts. |
| inputs / outputs | Borrowed planner stem keys, after comparisons and star, returns the existing keys documentation context. |
| invariants | Earlier path/domain rules and the new exact difference rule (plus cq_recompute in runtime) precede this old stem rule. Every preexisting stem rule retains relative order. The result selects inspection context only. |
| ownership | Borrows local stem and returns a shared string literal; no native source owner or account. |
| failure | No catch or native effect; existing malformed path/type behavior remains in family(). |
| cost | One bounded equality after prior path tests, only during offline generation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/key_specialization.md](../../../key_specialization.md) |

```text
@source-span:L439-L439:sha256:8ec26308cee1da78efbdc8ac83280f242866306beae2369b21041b33af5cf4d3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the exact planner star stem to the literal-family admission context. |
| inputs / outputs | The extracted planner stem star returns the shared star family label. |
| invariants | Earlier path/domain rules and the new exact difference rule (plus cq_recompute in runtime) precede this old stem rule. Every preexisting stem rule retains relative order. The result selects inspection context only. |
| ownership | Borrows the local stem and returns a shared string literal; no native ownership. |
| failure | Existing malformed path/type failures propagate; no handler is added. |
| cost | One offline stem equality after earlier path tests. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/star.md](../../../star.md) |

```text
@source-span:L457-L457:sha256:b1fd0cface478043904702c283b41f020a972bff4d46da9aa26d04efe60695de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route runtime star and star_ private helper stems to their actual context. |
| inputs / outputs | The exact runtime stem star or prefix star_ returns the shared star family label. |
| invariants | Earlier path/domain rules and the new exact difference rule (plus cq_recompute in runtime) precede this old stem rule. Every preexisting stem rule retains relative order. The result selects inspection context only. |
| ownership | Borrows the local stem and returns a shared literal; no query owner. |
| failure | Existing malformed path/type failures propagate; no handler is added. |
| cost | One equality and at most one fixed-prefix test during offline generation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/star.md](../../../star.md) |

```text
@source-span:L438-L438:sha256:accfde69de10347600c6b98127fa3e4f61636661a7a68ac9ab14d5669643abae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the exact comparison stem before generic planner context. |
| inputs / outputs | The extracted exact stem comparisons returns the shared comparisons context. |
| invariants | Earlier path/domain rules and the new exact difference rule (plus cq_recompute in runtime) precede this old stem rule. Every preexisting stem rule retains relative order. The result selects inspection context only. |
| ownership | Borrows a local string and returns a shared literal; no source/native ownership. |
| failure | Existing malformed path/type failures propagate; no new catch. |
| cost | One stem equality during offline generation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/comparisons.md](../../../comparisons.md) |

```text
@source-span:L456-L456:sha256:accfde69de10347600c6b98127fa3e4f61636661a7a68ac9ab14d5669643abae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the exact comparison stem before generic runtime context. |
| inputs / outputs | The extracted exact stem comparisons returns the shared comparisons context. |
| invariants | Earlier path/domain rules and the new exact difference rule (plus cq_recompute in runtime) precede this old stem rule. Every preexisting stem rule retains relative order. The result selects inspection context only. |
| ownership | Borrows a local string and returns a shared literal; no source/native ownership. |
| failure | Existing malformed path/type failures propagate; no new catch. |
| cost | One stem equality during offline generation. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/comparisons.md](../../../comparisons.md) |

```text
@source-span:L437-L437:sha256:e4f4732e054c7e002518270f483ff7d806fd0bc0d56e11fe48fa499d5edf7328
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route this exact planner stem to fallback inspection context. |
| inputs / outputs | if stem=='fallback':return 'fallback' |
| invariants | Earlier path/domain rules and the new exact difference rule (plus cq_recompute in runtime) precede this old stem rule. Every preexisting stem rule retains relative order. The result selects inspection context only. |
| ownership | Borrow a path-derived string and return a shared family literal. |
| failure | Existing malformed path/type errors propagate; no catch is added. |
| cost | One offline string equality. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/fallback.md](../../../fallback.md), [docs/source_images.md](../../../source_images.md) |

```text
@source-span:L454-L454:sha256:e4f4732e054c7e002518270f483ff7d806fd0bc0d56e11fe48fa499d5edf7328
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route this exact runtime stem to fallback inspection context. |
| inputs / outputs | if stem=='fallback':return 'fallback' |
| invariants | Earlier path/domain rules and the new exact difference rule (plus cq_recompute in runtime) precede this old stem rule. Every preexisting stem rule retains relative order. The result selects inspection context only. |
| ownership | Borrow a path-derived string and return a shared family literal. |
| failure | Existing malformed path/type errors propagate; no catch is added. |
| cost | One offline string equality. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/fallback.md](../../../fallback.md), [docs/source_images.md](../../../source_images.md) |

```text
@source-span:L455-L455:sha256:b75cf8c10ca16774ab76a49516c2bbb4df472b3bf3b49f345f319ab4c697a9da
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route this exact runtime stem to physical inspection context. |
| inputs / outputs | if stem=='source_image':return 'physical' |
| invariants | Earlier path/domain rules and the new exact difference rule (plus cq_recompute in runtime) precede this old stem rule. Every preexisting stem rule retains relative order. The result selects inspection context only. |
| ownership | Borrow a path-derived string and return a shared family literal. |
| failure | Existing malformed path/type errors propagate; no catch is added. |
| cost | One offline string equality. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/fallback.md](../../../fallback.md), [docs/source_images.md](../../../source_images.md) |

```text
@source-span:L436-L436:sha256:c777da24d865ac639bff945a40226f95d79a61a67965c62c84edd9d809903892
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the exact new stem to difference inspection context. |
| inputs / outputs | if stem=='difference':return 'difference' |
| invariants | Earlier domain/path rules retain priority; all old stem rules retain relative order. This selects documentation only. |
| ownership | Borrow a path-derived string and return a shared literal. |
| failure | Existing malformed path/type failures propagate; no handler added. |
| cost | One offline string equality. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/difference.md](../../../difference.md) |

```text
@source-span:L452-L452:sha256:c777da24d865ac639bff945a40226f95d79a61a67965c62c84edd9d809903892
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the exact new stem to difference inspection context. |
| inputs / outputs | if stem=='difference':return 'difference' |
| invariants | Earlier domain/path rules retain priority; all old stem rules retain relative order. This selects documentation only. |
| ownership | Borrow a path-derived string and return a shared literal. |
| failure | Existing malformed path/type failures propagate; no handler added. |
| cost | One offline string equality. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/difference.md](../../../difference.md) |

```text
@source-span:L453-L453:sha256:5db46c277e28d3e09fcc5a75237b4c38872283c94f5385c1072c4b54bc4da4aa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the exact new stem to cq_recompute inspection context. |
| inputs / outputs | if stem=='cq_recompute':return 'cq_recompute' |
| invariants | Earlier domain/path rules retain priority; all old stem rules retain relative order. This selects documentation only. |
| ownership | Borrow a path-derived string and return a shared literal. |
| failure | Existing malformed path/type failures propagate; no handler added. |
| cost | One offline string equality. |
| Design | [tools/code_specs_support.py](../../../../tools/code_specs_support.py), [tools/generate_code_specs.py](../../../../tools/generate_code_specs.py), [docs/difference.md](../../../difference.md) |
