# `src/runtime/sql_aggregate.cpp` — block usage map

[Source](../../../../../src/runtime/sql_aggregate.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain touched group statistics from one private authentic source batch.

Snapshot SHA-256: `0084907c3e292d06738d7e01a4993311356a216d2f9785c84d122a486495b306`. 379 lines partitioned into 49 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–26](../../../../../src/runtime/sql_aggregate.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace · [reviewed contract](#b0001) |
| [B0002 · 27–38](../../../../../src/runtime/sql_aggregate.cpp#L27) | Callable definition: Data(const resource::MemoryAccount& receiver, frontend::SqlAggregateProgram original, const FreeConnexTree& tree, const PhysicalO… | calls account, program, frontend::SqlAggregateProgram::freeze, options · [reviewed contract](#b0002) |
| [B0003 · 39–50](../../../../../src/runtime/sql_aggregate.cpp#L39) | Callable definition: Data(const resource::MemoryAccount& receiver,frontend::SqlAggregateProgram original,SqlRowsRuntime child, sql_aggregate::Options … | calls account, program, frontend::SqlAggregateProgram::freeze, options · [reviewed contract](#b0003) |
| [B0004 · 51–51](../../../../../src/runtime/sql_aggregate.cpp#L51) | Callable definition: bool global() const noexcept | calls empty; returns key.empty() · [reviewed contract](#b0004) |
| [B0005 · 52–54](../../../../../src/runtime/sql_aggregate.cpp#L52) | Callable definition: void require_idle() const | calls fail · [reviewed contract](#b0005) |
| [B0006 · 55–60](../../../../../src/runtime/sql_aggregate.cpp#L55) | Callable definition: Budget open(std::uint64_t next) const | calls require_idle, fail, take; returns budget · [reviewed contract](#b0006) |
| [B0007 · 61–63](../../../../../src/runtime/sql_aggregate.cpp#L61) | Explanatory comments or spacing. | source comment (unverified): // The opaque compiler checked complete-head coverage, exact SqlTypes and · [reviewed contract](#b0007) |
| [B0008 · 64–82](../../../../../src/runtime/sql_aggregate.cpp#L64) | Callable definition: void decode(storage::RowView native, Budget& budget) | calls size, native_fields, fail, inputs; 1 loop sites; source comment (unverified): // The opaque compiler checked complete-head coverage, exact SqlTypes and · [reviewed contract](#b0008) |
| [B0009 · 83–109](../../../../../src/runtime/sql_aggregate.cpp#L83) | Callable definition: void initialize(Budget& budget) | calls kernel_program, has_input, input_types, size; growth copy_of, emplace; source comment (unverified): // Weighted constant routes already have their authentic 0/1 root at epoch · [reviewed contract](#b0009) |
| [B0010 · 110–112](../../../../../src/runtime/sql_aggregate.cpp#L110) | declares types or opens a type body. |  · [reviewed contract](#b0010) |
| [B0011 · 113–117](../../../../../src/runtime/sql_aggregate.cpp#L113) | Type/record definition: struct Proposal |  · [reviewed contract](#b0011) |
| [B0012 · 118–128](../../../../../src/runtime/sql_aggregate.cpp#L118) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Owner is first and dies last, including failed construction. Child rollback · [reviewed contract](#b0012) |
| [B0013 · 129–143](../../../../../src/runtime/sql_aggregate.cpp#L129) | Callable definition: Data(std::shared_ptr&lt;SqlAggregateRuntime::Data&gt; target, SqlRowsRuntime::PreparedBatch child, Budget allowance) : owner(std::move(… | calls owner, std::move, source, budget; growth reserve; 1 loop sites; source comment (unverified): // Caller sets owner-&gt;busy after this constructor returns. · [reviewed contract](#b0013) |
| [B0014 · 144–148](../../../../../src/runtime/sql_aggregate.cpp#L144) | Callable definition: ~Data() | calls clear, rollback · [reviewed contract](#b0014) |
| [B0015 · 149–156](../../../../../src/runtime/sql_aggregate.cpp#L149) | Callable definition: void charge_copy(std::span&lt;const Cell&gt; cells) | calls take, size; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 157–174](../../../../../src/runtime/sql_aggregate.cpp#L157) | Callable definition: Proposal& touch() | calls aggregate::detail::project, kernel_program, take, find; returns queued-&gt;second; groups.emplace(std::move(owned), Proposal{current, std::move(after), {}}).first-&gt;se…; growth copy_of, emplace · [reviewed contract](#b0016) |
| [B0017 · 175–196](../../../../../src/runtime/sql_aggregate.cpp#L175) | Callable definition: void contribute(std::span&lt;const weighted::BagDelta&gt; facts, bool erasing) | calls take, fail, decode, values; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 197–201](../../../../../src/runtime/sql_aggregate.cpp#L197) | Callable definition: Tuple render(const Tuple& key, const Group& group) | calls aggregate::detail::render, kernel_program, view, charge_copy; returns tuple · [reviewed contract](#b0018) |
| [B0019 · 202–218](../../../../../src/runtime/sql_aggregate.cpp#L202) | Callable definition: void finalize(const Tuple& key, Proposal& proposal) | calls take, check_sums, kernel_program, global; growth push_back · [reviewed contract](#b0019) |
| [B0020 · 219–244](../../../../../src/runtime/sql_aggregate.cpp#L219) | Callable definition: sql_aggregate::Epoch commit() noexcept | calls assert, active, std::move, empty; guard assert(live && owner-&gt;busy && source.active());; returns std::move(result); growth insert; 1 loop sites; source comment (unverified): // Child is closed to every other caller. Its active checks are established · [reviewed contract](#b0020) |
| [B0021 · 245–246](../../../../../src/runtime/sql_aggregate.cpp#L245) | Closes surrounding scope/type. |  · [reviewed contract](#b0021) |
| [B0022 · 247–250](../../../../../src/runtime/sql_aggregate.cpp#L247) | Callable definition: sql_aggregate::Epoch::Epoch(const resource::MemoryAccount& account, std::uint64_t next, frontend::SqlAggregateProgram source, boo… | calls sequence, captured, program, std::move · [reviewed contract](#b0022) |
| [B0023 · 251–254](../../../../../src/runtime/sql_aggregate.cpp#L251) | Callable definition: sql_aggregate::Snapshot::Snapshot(const resource::MemoryAccount& account, std::uint64_t next, frontend::SqlAggregateProgram sourc… | calls sequence, program, std::move, groups · [reviewed contract](#b0023) |
| [B0024 · 255–257](../../../../../src/runtime/sql_aggregate.cpp#L255) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;sql_aggregate::Epoch&gt;); · [reviewed contract](#b0024) |
| [B0025 · 258–258](../../../../../src/runtime/sql_aggregate.cpp#L258) | Callable definition: SqlAggregateRuntime::SqlAggregateRuntime(std::shared_ptr&lt;Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0025) |
| [B0026 · 259–268](../../../../../src/runtime/sql_aggregate.cpp#L259) | Callable definition: SqlAggregateRuntime SqlAggregateRuntime::create_into(const resource::MemoryAccount& account, frontend::SqlAggregateProgram progra… | calls resource::MemoryFailure, fail, SqlAggregateRuntime, std::move; returns SqlAggregateRuntime(resource::make_accounted_shared&lt;Data&gt;(account, resource::MemoryPurpose::table_s…; growth make_accounted_shared · [reviewed contract](#b0026) |
| [B0027 · 269–318](../../../../../src/runtime/sql_aggregate.cpp#L269) | Callable definition: SqlAggregateRuntime SqlAggregateRuntime::rebuild_into(const resource::MemoryAccount& account, const sql_aggregate::SourceSnapshot… | calls source_program, source_sha256, fail, source_work; returns SqlAggregateRuntime(std::move(owner)); rebuilt; growth make_accounted_shared, make_accounted_unique; source comment (unverified): // Import actual compiler metadata once; child freeze is then a same-account · [reviewed contract](#b0027) |
| [B0028 · 319–319](../../../../../src/runtime/sql_aggregate.cpp#L319) | Explanatory comments or spacing. |  |
| [B0029 · 320–323](../../../../../src/runtime/sql_aggregate.cpp#L320) | Callable definition: SqlAggregateRuntime::SqlAggregateRuntime(frontend::SqlAggregateProgram program, const FreeConnexTree& tree, const PhysicalOptions… | calls SqlAggregateRuntime, create_into, resource::MemoryAccount::create, std::move · [reviewed contract](#b0029) |
| [B0030 · 324–326](../../../../../src/runtime/sql_aggregate.cpp#L324) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0030) |
| [B0031 · 327–330](../../../../../src/runtime/sql_aggregate.cpp#L327) | Callable definition: SqlAggregateRuntime::Data& SqlAggregateRuntime::data() const | calls fail; returns *data_ · [reviewed contract](#b0031) |
| [B0032 · 331–331](../../../../../src/runtime/sql_aggregate.cpp#L331) | Callable definition: const frontend::SqlAggregateProgram& SqlAggregateRuntime::program() const & | calls data; returns data().program · [reviewed contract](#b0032) |
| [B0033 · 332–332](../../../../../src/runtime/sql_aggregate.cpp#L332) | Callable definition: const resource::MemoryAccount& SqlAggregateRuntime::account() const & | calls data; returns data().account · [reviewed contract](#b0033) |
| [B0034 · 333–333](../../../../../src/runtime/sql_aggregate.cpp#L333) | Callable definition: std::uint64_t SqlAggregateRuntime::sequence() const | calls data; returns data().sequence · [reviewed contract](#b0034) |
| [B0035 · 334–334](../../../../../src/runtime/sql_aggregate.cpp#L334) | Callable definition: bool SqlAggregateRuntime::ready() const noexcept | calls ready; returns data_ && !data_-&gt;busy && data_-&gt;source.ready() · [reviewed contract](#b0035) |
| [B0036 · 335–337](../../../../../src/runtime/sql_aggregate.cpp#L335) | Callable definition: weighted::Multiplicity SqlAggregateRuntime::root_weight() const | calls data, require_idle, root_weight; returns value.source.root_weight() · [reviewed contract](#b0036) |
| [B0037 · 338–338](../../../../../src/runtime/sql_aggregate.cpp#L338) | Callable definition: resource::MemoryStatistics SqlAggregateRuntime::accounted_memory_statistics() const | calls data, statistics; returns data().account.statistics() · [reviewed contract](#b0037) |
| [B0038 · 339–341](../../../../../src/runtime/sql_aggregate.cpp#L339) | Callable definition: std::uint64_t SqlAggregateRuntime::source_weight(TableId id, std::span&lt;const sql_rows::Cell&gt; cells) const | calls data, require_idle, source_weight; returns value.source.source_weight(id, cells) · [reviewed contract](#b0038) |
| [B0039 · 342–348](../../../../../src/runtime/sql_aggregate.cpp#L342) | Callable definition: SqlAggregateRuntime::PreparedBatch SqlAggregateRuntime::prepare_batch(const sql_rows::NetBatch& batch) | calls data, open, prepare_batch, std::move; returns PreparedBatch(std::move(prepared)); growth make_accounted_unique · [reviewed contract](#b0039) |
| [B0040 · 349–349](../../../../../src/runtime/sql_aggregate.cpp#L349) | Callable definition: SqlAggregateRuntime::PreparedBatch::PreparedBatch(resource::AccountedUnique&lt;Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0040) |
| [B0041 · 350–352](../../../../../src/runtime/sql_aggregate.cpp#L350) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0041) |
| [B0042 · 353–356](../../../../../src/runtime/sql_aggregate.cpp#L353) | Callable definition: SqlAggregateRuntime::PreparedBatch::Data& SqlAggregateRuntime::PreparedBatch::data() const | calls fail; returns *data_ · [reviewed contract](#b0042) |
| [B0043 · 357–357](../../../../../src/runtime/sql_aggregate.cpp#L357) | Callable definition: bool SqlAggregateRuntime::PreparedBatch::active() const noexcept | calls ; returns data_ && data_-&gt;live · [reviewed contract](#b0043) |
| [B0044 · 358–358](../../../../../src/runtime/sql_aggregate.cpp#L358) | Callable definition: const sql_aggregate::Epoch& SqlAggregateRuntime::PreparedBatch::preview() const & | calls data; returns data().result · [reviewed contract](#b0044) |
| [B0045 · 359–361](../../../../../src/runtime/sql_aggregate.cpp#L359) | Callable definition: sql_aggregate::Epoch SqlAggregateRuntime::PreparedBatch::commit() | calls data, commit, reset; returns result · [reviewed contract](#b0045) |
| [B0046 · 362–362](../../../../../src/runtime/sql_aggregate.cpp#L362) | Callable definition: void SqlAggregateRuntime::PreparedBatch::rollback() noexcept | calls reset · [reviewed contract](#b0046) |
| [B0047 · 363–372](../../../../../src/runtime/sql_aggregate.cpp#L363) | Callable definition: sql_aggregate::Snapshot SqlAggregateRuntime::snapshot(aggregate::SnapshotLimits limits) const | calls data, require_idle, take, size; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0047) |
| [B0048 · 373–378](../../../../../src/runtime/sql_aggregate.cpp#L373) | Callable definition: sql_aggregate::SourceSnapshot SqlAggregateRuntime::source_snapshot(sql_rows::SourceSnapshotLimits limits) const | calls data, require_idle, source_snapshot, assert; guard assert(source.sequence == value.sequence);; returns {value.program, std::move(source)} · [reviewed contract](#b0048) |
| [B0049 · 379–379](../../../../../src/runtime/sql_aggregate.cpp#L379) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0049) |

## B0001

[Lines 1–26](../../../../../src/runtime/sql_aggregate.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/runtime/sql_aggregate.hpp" #include "aggregate_detail.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep composed runtime and aggregate helper includes together with the source-private closed rebuild bridge. |
| inputs / outputs | The implementation includes its public facade, aggregate kernel helpers and private SqlColdRebuild definitions. |
| invariants | The internal bridge stays under \`src/runtime\`; this does not expose it through an installed public header. |
| ownership | Includes create no runtime owner or grant. |
| failure | Missing implementation declarations fail compilation. |
| cost | Compile-time dependency only; no runtime cost. |
| Design | [src/runtime/sql_aggregate.cpp](../../../../../src/runtime/sql_aggregate.cpp), [src/runtime/sql_cold_rebuild.hpp](../../../../../src/runtime/sql_cold_rebuild.hpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp) |

## B0002

[Lines 27–38](../../../../../src/runtime/sql_aggregate.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(const resource::MemoryAccount& receiver, frontend::SqlAggregateProgram original, const FreeConnexTree& tree, const PhysicalOptions& physical, sql_aggregate::Options requested
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep normal aggregate construction on its original option budget while routing shared bootstrap through a caller-owned Budget. |
| inputs / outputs | The normal constructor still creates one \`Budget{options.group_work_limit,{}}\` and passes it to \`initialize\`; the cold constructor can pass the same unrefilled Budget through static bootstrap and one seed. |
| invariants | Normal execution still initializes one authentic global-empty/static state before publication. The cold path uses the matching C=0 or C−1 base only in an unpublished owner. |
| ownership | The ordinary receiver, source child, scratch vectors and group map remain owned by unpublished Data; the Budget is stack-scoped. |
| failure | Existing kernel/count/work/account/allocation errors abort construction before facade publication. |
| cost | One stack Budget and helper call during construction; no extra hot record or per-operation cost. |
| Design | [src/runtime/sql_aggregate.cpp](../../../../../src/runtime/sql_aggregate.cpp), [docs/aggregates.md §Logical input and publication](../../../../aggregates.md), [docs/sql_source_images.md §Closed cold reconstruction](../../../../sql_source_images.md) |

## B0003

[Lines 39–50](../../../../../src/runtime/sql_aggregate.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(const resource::MemoryAccount& receiver,frontend::SqlAggregateProgram original,SqlRowsRuntime child,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an unpublished aggregate owner around the already rebuilt source at its private base frontier. |
| inputs / outputs | Receiver, genuine aggregate program, rebuilt source child, original options and sequence base initialize the common Data fields. |
| invariants | The caller initializes static/group state using the shared Budget; C is 0 at epoch zero or C−1 before the single seed. This constructor alone does not publish the runtime. |
| ownership | Outer Data owns frozen program, child source, funded scratch and groups; child and outer use the same receiver. |
| failure | Member construction failures unwind before a public facade exists. |
| cost | Cold owner-sized scratch/group allocation only; no per-row input table or added hot fields. |
| Design | [src/runtime/sql_aggregate.cpp](../../../../../src/runtime/sql_aggregate.cpp), [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0004

[Lines 51–51](../../../../../src/runtime/sql_aggregate.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool global() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish global from grouped state using immutable group-key width. |
| inputs / outputs | Outer Data -&gt; whether group-key scratch is empty. |
| invariants | Kernel group width is immutable and scratch has that exact width. |
| ownership | Borrows existing Data only. |
| failure | No throw or mutation. |
| cost | O(1), no allocation/admission. |
| Design | src/runtime/aggregate.cpp:106, src/runtime/sql_aggregate.cpp:38, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 52–54](../../../../../src/runtime/sql_aggregate.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require_idle() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep pending composition private to one serialized owner. |
| inputs / outputs | Outer Data busy flag -&gt; success or sql_aggregate_busy. |
| invariants | Only one composed token can be prepared; const snapshots/probes do not observe child tentative native state. |
| ownership | Reads outer scalar, retains nothing. |
| failure | Error on busy before another operational action. |
| cost | O(1); no allocation on success, standard Error construction on rejection. |
| Design | src/runtime/sql_rows.cpp:99, src/runtime/weighted.cpp:99, [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), src/runtime/sql_aggregate.cpp:39, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 55–60](../../../../../src/runtime/sql_aggregate.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Budget open(std::uint64_t next) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one next contiguous epoch and open one cumulative group allowance. |
| inputs / outputs | Requested sequence -&gt; one Budget initialized with options.group_work_limit and its opening debit. |
| invariants | UINT64_MAX cannot wrap; requires next==committed+1; busy fails first; empty batches use the same admission. |
| ownership | Returns local Budget, never per-fact refills. |
| failure | Busy/invalid_sequence/work denial leaves source/native/groups untouched. |
| cost | O(1), one take; no allocation on success. |
| Design | src/runtime/aggregate.cpp:110, src/runtime/weighted.cpp:665, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:42, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 61–63](../../../../../src/runtime/sql_aggregate.cpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// The opaque compiler checked complete-head coverage, exact SqlTypes and // nullable/default encoding. These fields come only from this owner's child
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record why decoder fields are safe to read only from this owner’s authenticated child token. |
| inputs / outputs | No executable input/output; comment describes compile-time complete-head coverage, exact SQL types, nullable/default encoding, and private compiler-owned descriptors. |
| invariants | Only genuine source-produced native facts enter decode; public rows/DTOs cannot select arbitrary field indexes or bypass source admission. |
| ownership | Comment documents child token authority; no data retained by the comment. |
| failure | No runtime failure in comment; decode enforces internal width consistency. |
| cost | No executable cost; each actual field/presence/string charge is in decode. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md), src/runtime/sql_aggregate.cpp:48, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 64–82](../../../../../src/runtime/sql_aggregate.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void decode(storage::RowView native, Budget& budget)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode authentic native head facts into the exact canonical nullable kernel input. |
| inputs / outputs | One private child-owned RowView -&gt; reusable input cells via genuine field/presence/constant descriptors. |
| invariants | Opaque V2 complete-head coverage plus deterministic NULL payload establishes injectivity; bound origin/full type is distinct from normalized descriptor; test presence before payload. |
| ownership | Input string views borrow native fact only through preparation; source Program owns constant views; enclosing Borrows clears scratch before child teardown. |
| failure | Width mismatch reports internal contract failure; allocation/work denial unwinds outer preparation. Scalar/variant correctness is established by real factories, not arbitrary caller rows. |
| cost | K field admissions plus tested presence flags and observed string bytes; no DTO/scalar copy allocation, parser, second ledger or duplicate scalar validation. |
| Design | src/frontend/sql_aggregate.cpp:340, src/frontend/sql_aggregate.cpp:375, [src/frontend/sql_rows_eval.hpp](../../../../../src/frontend/sql_rows_eval.hpp), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), src/runtime/sql_aggregate.cpp:51, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 83–109](../../../../../src/runtime/sql_aggregate.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void initialize(Budget& budget)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the existing static/global bootstrap against the caller’s cumulative group-work budget. |
| inputs / outputs | A fresh actual aggregate kernel and source state plus \`Budget&\` produce the same authenticated static 0/1 or global-empty group state. |
| invariants | Normal construction supplies a new budget at the configured group cap; cold C&gt;0 reconstruction reuses one unrefilled budget for bootstrap and the C−1→C seed. No synthetic operational epoch is exposed. |
| ownership | Initial group/key state is receiver-owned; the referenced Budget remains with the factory stack. |
| failure | Kernel contract, static root-weight, arithmetic, group-work or allocation errors abort the unpublished owner. |
| cost | The original initialization body is retained after extracting its local Budget declaration; only the cold factory adds cumulative use. |
| Design | [src/runtime/sql_aggregate.cpp](../../../../../src/runtime/sql_aggregate.cpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md), [docs/sql_source_images.md §Closed cold reconstruction](../../../../sql_source_images.md) |

## B0010

[Lines 110–112](../../../../../src/runtime/sql_aggregate.cpp#L110); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
}; struct SqlAggregateRuntime::PreparedBatch::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the outer Data type and begin the private PreparedBatch backing type. |
| inputs / outputs | The following type owns proposals, child source token, result and busy state. |
| invariants | Declares the outer owner before child/proposal members so reverse member destruction keeps it alive through rollback/teardown. |
| ownership | C++ member-order declaration controls lifetime. |
| failure | No operation body; construction/destruction contracts follow. |
| cost | No executable work from the closing/opening syntax itself. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md), src/runtime/sql_aggregate.cpp:98, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 113–117](../../../../../src/runtime/sql_aggregate.cpp#L113); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Proposal
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe exactly one touched group proposal for joint publication. |
| inputs / outputs | Full group key -&gt; committed iterator, proposed rows/States and optional detached new group node. |
| invariants | Iterator stays valid until serialized commit; no untouched State copied; proposed vector allocator exactly matches persistent support_metadata. |
| ownership | Touched map owns key handle/Group/node; outer owner declared before child/proposals. |
| failure | No implicit publication; partial/map allocation failure discards private entry. |
| cost | O(M) State storage per first-touched group plus actual new-key bytes; no row-count ledger. |
| Design | src/runtime/aggregate.cpp:284, include/crown/resource/allocator.hpp:10, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:101, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 118–128](../../../../../src/runtime/sql_aggregate.cpp#L118); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Touched = std::map<Tuple, Proposal, Less, resource::MemoryAllocator<std::pair<const Tuple, Proposal>>>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one Proposal per distinct touched full group in the receiver-funded ordered map. |
| inputs / outputs | Tuple key and private Proposal value are inserted/looked up during contribution; comparator uses shared nullable Tuple ordering. |
| invariants | No complete joined-row ledger or untouched groups are stored. One key entry exists for each distinct touched group; committed map iterator remains stable while busy excludes mutation. |
| ownership | The map node/key/proposal use receiver MemoryPurpose::scratch. Key payload is copied or shared from the existing owner; Proposal holds a non-owning committed iterator and receiver-funded after State/node. |
| failure | Map node/key allocation failure unwinds private preparation before outer busy latch/publication; comparator is nonthrowing. |
| cost | One ordered-map lookup/insert per first touch with logarithmic key comparisons and actual string comparisons; node allocation and payload bytes are separate receiver costs. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md), src/runtime/sql_aggregate.cpp:106, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 129–143](../../../../../src/runtime/sql_aggregate.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(std::shared_ptr<SqlAggregateRuntime::Data> target, SqlRowsRuntime::PreparedBatch child, Budget allowance) : owner(std::move(target)), source(std::move(child)), budget(std::mo
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seal complete source/native/group/output proposal under one retained outer owner. |
| inputs / outputs | Outer shared Data, already prepared genuine child, one allowance -&gt; active private composed prepared Data and immutable preview. |
| invariants | Requires capture from this child; records genuine changed flag; scans removals before additions, finalizes every touched group once and finishes last debit before live latch. |
| ownership | Owner is declared first/dies last. Child source token holds native pending state and mandatory D facts; Borrow guards clear input/key scratch after construction; result owns metadata and receiver output. The constructor does not latch outer busy until it returns and the factory sets it. |
| failure | Every group/decoder/output/work/allocation failure unwinds child native rollback; outer busy is latched only after successful construction. |
| cost | One group Budget covers two D scans and selected decode/projection/touch/final work. Captured results reserve capacity for groups.size() before finalize, even if equality suppression leaves no emitted changes; D buffer, map comparisons, allocator work and teardown are real separate costs. |
| Design | src/runtime/sql_rows.cpp:276, src/runtime/sql_rows.cpp:392, src/runtime/weighted.cpp:710, src/runtime/aggregate.cpp:311, [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:117, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 144–148](../../../../../src/runtime/sql_aggregate.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Data()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close unpublished composition through existing child rollback and private proposal release. |
| inputs / outputs | Live prepared Data destruction -&gt; original source/native/groups/frontier and cleared busy; committed Data requires no rollback. |
| invariants | Never publishes on destruction, no second undo; child/proposals finish before owner dies; no native borrows remain. |
| ownership | When live, clears touched proposals and rolls back child while the shared outer owner still exists; failed construction uses member unwinding because live was never set. |
| failure | No throw; failed-constructor member unwinding supplies equivalent cleanup without destructor body/live latch. |
| cost | Visited touched nodes/state/output plus real child native undo/capture teardown; no extra allocation or new inverse log. |
| Design | src/runtime/sql_rows.cpp:416, src/runtime/weighted.cpp:290, include/crown/resource/ownership.hpp:17, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:132, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 149–156](../../../../../src/runtime/sql_aggregate.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void charge_copy(std::span<const Cell> cells)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit actual retained Tuple-copy fields and string bytes under the same group allowance. |
| inputs / outputs | Cell span -&gt; metrics copied_fields/copied_bytes and cumulative work. |
| invariants | Every counter increment follows sufficient take, establishing uint64 room; data/lengths already authentic. |
| ownership | Borrows cells only; tuple ownership is handled by caller. |
| failure | Work denial aborts preparation and releases private allocations. |
| cost | One visit per actual copied field plus actual string bytes; separate from decode/project/measure work. |
| Design | src/runtime/aggregate.cpp:339, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:137, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0016

[Lines 157–174](../../../../../src/runtime/sql_aggregate.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Proposal& touch()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve/create one touched full group proposal, copying only its current State vector. |
| inputs / outputs | Decoded input/key scratch -&gt; stable Touched::Proposal reference. |
| invariants | Uses actual kernel group columns and NULL/full-key comparator. Existing group key shares; new key copies once. Persistent and proposed State allocators exactly equal. |
| ownership | Touched map retains owned key and proposed state; committed iterator pinned by outer/child ownership and serialization. |
| failure | Projection/probe/copy/state/map work or allocation failure leaves committed maps unchanged. |
| cost | One map proposal per distinct touched full group: actual logarithmic ordered-map comparisons and string compares, projection charges, one first-touch M-State copy/init, one new key copy if absent. No untouched group traversal. |
| Design | src/runtime/aggregate.cpp:351, src/runtime/aggregate.cpp:38, include/crown/resource/allocator.hpp:84, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:145, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 175–196](../../../../../src/runtime/sql_aggregate.cpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void contribute(std::span<const weighted::BagDelta> facts, bool erasing)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply genuine net retractions before additions using exact shared sufficient-statistic math. |
| inputs / outputs | Internal unique nonzero BagDelta span plus selected sign -&gt; touched group rows/count/sum proposals. |
| invariants | Reads only genuine encoded source-child BagDelta facts before SQL DISTINCT/EXISTS presentation; the compiled decoder reconstructs bound origin and exact value. Facts are not expanded by multiplicity. All decreases precede increases, and final aggregate SUM checks are deferred to touched-group finalize. |
| ownership | Borrows child facts and reusable input scratch only; retains no complete logical-row key/index. |
| failure | Internal zero/retraction-count contract error or count/work denial unwinds entire source/native proposal; shared adjust assertions follow genuine subbag proof. |
| cost | Two D-entry scans plus per-fact decoded fields/presence/string-byte work and M measure updates; first touch adds projection/map/key/state costs. Group Budget is selected logical work, not CPU or all comparison/allocation work. |
| Design | src/runtime/weighted.cpp:710, src/runtime/weighted_delta_detail.hpp:9, src/runtime/aggregate.cpp:396, src/runtime/aggregate_integer.hpp:112, [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), src/runtime/sql_aggregate.cpp:163, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0018

[Lines 197–201](../../../../../src/runtime/sql_aggregate.cpp#L197); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple render(const Tuple& key, const Group& group)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an owning nullable SQL tuple from one committed/proposed group with shared W04 formatting. |
| inputs / outputs | Owned full key plus group rows/States -&gt; owning receiver output_buffer Tuple. |
| invariants | Final sums checked before rendering; actual immutable output kinds/types/AVG scale drive values; charge copy fields/bytes before tuple escapes. |
| ownership | Common render clears output borrows; returned tuple owns every retained string and inline decimal. |
| failure | Output arithmetic/copy/allocation/work failure remains before publication and destroys proposal; no partially emitted result. |
| cost | O(O+actual copied bytes), one real Tuple payload/control copy per requested before/after tuple. |
| Design | src/runtime/aggregate.cpp:175, src/runtime/aggregate.cpp:410, [src/runtime/aggregate_tuple.cpp](../../../../../src/runtime/aggregate_tuple.cpp), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:185, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 202–218](../../../../../src/runtime/sql_aggregate.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finalize(const Tuple& key, Proposal& proposal)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seal one final touched group, requested before/final output and detached node. |
| inputs / outputs | Full group key/Proposal -&gt; final-only SUM validation, optional full-key GroupChange, optional prepared persistent group node. |
| invariants | Global group persists at zero; grouped last deletion disappears. Absent differs from NULL tuple. Equal rendered values suppress events without losing logical group identity. |
| ownership | Old state remains immutable; new node uses destination allocator; output owns keys/tuples; move of after into node occurs only for new surviving group. |
| failure | Every SUM/render/reserve/push/node/work failure unwinds before joint commit. |
| cost | For each touched group, one final M-measure check and optional old/final renders; one detached node if a group is newly present. When capture is enabled, result.output reserves groups.size() once before finalize even if equal/absent output suppression leaves size zero; that retained vector capacity is a real receiver allocation until Epoch release. |
| Design | src/runtime/aggregate.cpp:417, src/runtime/aggregate.cpp:59, docs/aggregates.md:55, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:190, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 219–244](../../../../../src/runtime/sql_aggregate.cpp#L219); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_aggregate::Epoch commit() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish genuine source/native and prepared group state as one serialized committed frontier. |
| inputs / outputs | Known live internal child/outer proposal -&gt; moved complete Epoch, closed child, committed groups and outer sequence. |
| invariants | The child source transaction publishes source constraints/native journal first while serialized. Then prepared group node insertions/erasures/scalar updates and equal-allocator State swaps publish one sequence; no other observer can interleave. Internal D facts are cleared before return. No D-to-G scan/expansion happens at commit. |
| ownership | Child/result/proposals remain backed by outer owner through publication; groups.clear releases private entries before busy false/live false. Public commit then resets PreparedBatch::Data. Returned Epoch owns requested output, not proposal storage. |
| failure | No normal fallible work is reachable on a genuine live token; invalid/closed token is rejected before this barrier. No catch/undo replacement. |
| cost | O(G) proposal traversal plus unhinted destination std::map node insertion comparisons for each newly inserted group, iterator erase/scalar assignment/equal-allocator vector swap, D-capture release and state/proposal teardown. No new allocation, numeric validation, formatting or group Budget admission. |
| Design | src/runtime/sql_rows.cpp:404, src/runtime/weighted.cpp:727, src/runtime/weighted_delta_detail.hpp:96, include/crown/resource/allocator.hpp:84, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:207, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
return std::move(result); // Account/program/output moves are nonallocating.
  }
};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private PreparedBatch::Data definition after its complete preparation, cleanup and commit operations. |
| inputs / outputs | Type scope close; no input/output. |
| invariants | No additional method, catch or publication state follows inside this type. |
| ownership | No ownership operation at the brace. |
| failure | Compile-time scope closure only. |
| cost | Zero runtime work. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md), src/runtime/sql_aggregate.cpp:233, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0021

[Lines 245–246](../../../../../src/runtime/sql_aggregate.cpp#L245); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L245-L246:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct SqlAggregateRuntime::PreparedBatch::Data\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct SqlAggregateRuntime::PreparedBatch::Data\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct SqlAggregateRuntime::PreparedBatch::Data\` at its lexical source position in src/runtime/sql_aggregate.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct SqlAggregateRuntime::PreparedBatch::Data\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/aggregates.md](../../../../aggregates.md), [docs/aggregate_batches.md](../../../../aggregate_batches.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0022

[Lines 247–250](../../../../../src/runtime/sql_aggregate.cpp#L247); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_aggregate::Epoch::Epoch(const resource::MemoryAccount& account, std::uint64_t next, frontend::SqlAggregateProgram source, bool capture) : sequence(next), captured(capture), na
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create receiver-owned aggregate epoch output retaining original composed schema identity. |
| inputs / outputs | Account/next/genuine Program/capture choice -&gt; initialized Epoch with empty native bag/output and zero metrics. |
| invariants | Native summary starts at requested sequence; source result fills actual metrics/root on preparation/commit. No native D output is retained publicly. |
| ownership | Program shares receiver metadata; output uses OwnerAllocator output_buffer. |
| failure | Allocator construction may reject invalid account before publication; scalar/handle initialization has no body throws. |
| cost | O(1) fixed record/control refs, no output element allocation until reserve during prepare. |
| Design | [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), include/crown/runtime/sql_aggregate.hpp:17, src/runtime/sql_aggregate.cpp:235, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0023

[Lines 251–254](../../../../../src/runtime/sql_aggregate.cpp#L251); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_aggregate::Snapshot::Snapshot(const resource::MemoryAccount& account, std::uint64_t next, frontend::SqlAggregateProgram source) : sequence(next), program(std::move(source)), g
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an eager receiver-owned full-group snapshot with original composed metadata. |
| inputs / outputs | Account/sequence/genuine Program -&gt; empty owning Snapshot vector. |
| invariants | No reader lease or caller-fed logical authority; full keys distinguish equal projected outputs. |
| ownership | Program shares receiver metadata; vector uses output_buffer allocator. |
| failure | Only allocator/account contract construction can fail before result escape. |
| cost | O(1) constructor; requested group payload copying is explicit snapshot work. |
| Design | src/runtime/aggregate_tuple.cpp:74-77, include/crown/runtime/sql_aggregate.hpp:31, src/runtime/sql_aggregate.cpp:239, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0024

[Lines 255–257](../../../../../src/runtime/sql_aggregate.cpp#L255); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static_assert(std::is_nothrow_move_constructible_v<sql_aggregate::Epoch>); static_assert(std::is_nothrow_move_assignable_v<weighted::Epoch>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the public Epoch and child weighted Epoch to move without throwing across the publication barrier. |
| inputs / outputs | Compile-time traits of Epoch and weighted::Epoch. |
| invariants | The commit path relies on transferring the already prepared owning result after all throwing work has finished. |
| ownership | No runtime owner; static assertion only. |
| failure | A future type-layout/allocator change that loses noexcept move fails compilation. |
| cost | Compile-time check only. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md), src/runtime/sql_aggregate.cpp:243, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0025

[Lines 258–258](../../../../../src/runtime/sql_aggregate.cpp#L258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateRuntime::SqlAggregateRuntime(std::shared_ptr<Data> value) noexcept : data_(std::move(value))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move fully constructed shared outer owner into facade. |
| inputs / outputs | shared_ptr&lt;Data&gt; -&gt; SqlAggregateRuntime. |
| invariants | No state publication or grant creation. |
| ownership | Transfers shared ownership; active token may independently retain owner. |
| failure | noexcept. |
| cost | O(1), no allocation. |
| Design | include/crown/resource/ownership.hpp:75, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:246, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0026

[Lines 259–268](../../../../../src/runtime/sql_aggregate.cpp#L259); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateRuntime SqlAggregateRuntime::create_into(const resource::MemoryAccount& account, frontend::SqlAggregateProgram program, const FreeConnexTree& tree, const PhysicalOptio
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build composition in one supplied receiving grant from genuine factory metadata/tree. |
| inputs / outputs | Account, opaque Program, genuine-source tree/physical options/runtime options -&gt; ready epoch0 SqlAggregateRuntime. |
| invariants | Receiver grant authoritative; count_limit&lt;=INT64_MAX; metadata freeze imports once without granting new proof; source factory owns plan validation. |
| ownership | Accounted shared outer Data/control holds nested receiver-owned state; empty/foreign account handling follows normal import. |
| failure | Empty receiver/program, invalid options, compiler import/native/plan/bootstrap/work/memory failure aborts construction. |
| cost | Real accounted fixed control plus cold import/source creation/query-sized scratch and initial global group; no row clone. |
| Design | src/runtime/sql_rows.cpp:471, src/runtime/aggregate.cpp:349-357, [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:247, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0027

[Lines 269–318](../../../../../src/runtime/sql_aggregate.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateRuntime SqlAggregateRuntime::rebuild_into(const resource::MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct the original aggregate binding and complete physical source image before returning a normal ready runtime. |
| inputs / outputs | Composite image, receiver, normal options and cold limits -&gt; rebuilt groups/frontier and optional selected counters. |
| invariants | Require genuine matching aggregate/source source-SHA; re-lower captured actual tree/options through original compiler; compare both physical digests and full weighted binding; C=0 initializes authentic static state, C&gt;0 performs one C−1→C source/native epoch with the same group budget. No fabricated descriptors or durable authority. |
| ownership | New program/source/group/native state belongs to receiver; image handles remain caller-owned. Cold tokens, D capture, journals and indexed operation close before a normal context is installed. |
| failure | Any compiler/source/native/group/cap/allocation failure destroys only unpublished state; metrics assign only on success; no broad catch or second undo layer. |
| cost | Distinct finite lowering/source/native/indexed/group admissions. Required native D-fact capture is transient and charged; no joined-row ledger or caller-visible aggregate change output is retained. Map/DTO/compiler costs are not claimed as fully bounded by the selected counters. |
| Design | [src/runtime/sql_aggregate.cpp](../../../../../src/runtime/sql_aggregate.cpp), [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [docs/sql_source_images.md §Recovery boundary](../../../../sql_source_images.md), build/verification/w06-sql-aggregate-cold-rebuild-design-v1/cost-and-lifetime.md:18 |

## B0029

[Lines 320–323](../../../../../src/runtime/sql_aggregate.cpp#L320); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateRuntime::SqlAggregateRuntime(frontend::SqlAggregateProgram program, const FreeConnexTree& tree, const PhysicalOptions& physical, sql_aggregate::Options options) : SqlA
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an explicit runtime-sized account then use the same genuine receiving factory. |
| inputs / outputs | Opaque Program/tree/physical/options -&gt; standalone runtime with options.memory_limit_bytes grant. |
| invariants | Compiler default32MiB never becomes runtime allowance; receiver import copies genuine foreign metadata. |
| ownership | Created account is owned by outer Data and all retained nested allocations. |
| failure | Account/factory failure leaves no partially published owner. |
| cost | One actual account creation plus ordinary factory cost; no hidden nested cap. |
| Design | src/runtime/sql_rows.cpp:467, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:257, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0030

[Lines 324–326](../../../../../src/runtime/sql_aggregate.cpp#L324); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateRuntime::SqlAggregateRuntime(SqlAggregateRuntime&&) noexcept = default; SqlAggregateRuntime& SqlAggregateRuntime::operator=(SqlAggregateRuntime&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Default the facade move operations and destructor for shared outer Data ownership. |
| inputs / outputs | Move transfers one shared_ptr; destruction/assignment drops a reference. |
| invariants | An active PreparedBatch has its own shared reference and can preserve busy state after facade movement/destruction. |
| ownership | Shared reference moves/releases; no unique exclusive owner claim. |
| failure | Move operations are noexcept; last-reference Data teardown is ordinary release. |
| cost | O(1) handle transfer/drop, or actual last-owner group/source teardown. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md), src/runtime/sql_aggregate.cpp:261, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0031

[Lines 327–330](../../../../../src/runtime/sql_aggregate.cpp#L327); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateRuntime::Data& SqlAggregateRuntime::data() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate facade/token handle before accessing private owner state. |
| inputs / outputs | Facade or token -&gt; private Data&. |
| invariants | No null/closed dereference; token requires live, facade requires retained shared owner. |
| ownership | Borrows existing private storage only. |
| failure | Empty/moved/closed Error before operational access. |
| cost | O(1), no allocation on valid access. |
| Design | include/crown/resource/ownership.hpp:17, [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), src/runtime/sql_aggregate.cpp:264, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0032

[Lines 331–331](../../../../../src/runtime/sql_aggregate.cpp#L331); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const frontend::SqlAggregateProgram& SqlAggregateRuntime::program() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow actual original composed immutable compiler binding. |
| inputs / outputs | Const lvalue runtime -&gt; SqlAggregateProgram const&. |
| invariants | Metadata never becomes caller-editable source/proof authority; valid during active preparation. |
| ownership | Reference borrows retained facade; explicit handle copy owns metadata independently. |
| failure | Empty/moved facade Error. |
| cost | O(1), no allocation. |
| Design | src/frontend/sql_aggregate.cpp:112, [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), src/runtime/sql_aggregate.cpp:268, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0033

[Lines 332–332](../../../../../src/runtime/sql_aggregate.cpp#L332); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& SqlAggregateRuntime::account() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the actual retained receiving grant/statistics without minting another account. |
| inputs / outputs | Const lvalue facade -&gt; receiving account reference or statistics value. |
| invariants | All retained nested composition state has this owner; diagnostics are serialized but allowed while prepared. |
| ownership | Account reference borrows facade, explicit copies retain control; statistics own only counters. |
| failure | Empty/moved facade Error. |
| cost | O(1), no allocation. |
| Design | include/crown/resource/memory.hpp:106, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:269, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0034

[Lines 333–333](../../../../../src/runtime/sql_aggregate.cpp#L333); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t SqlAggregateRuntime::sequence() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe outer committed frontier while preparation remains private. |
| inputs / outputs | Runtime -&gt; committed uint64 sequence. |
| invariants | Prepared preview sequence is separate; scalar advances only after genuine joint publication. |
| ownership | Reads outer Data only. |
| failure | Moved/empty facade Error. |
| cost | O(1), no allocation on success. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), src/runtime/weighted.cpp:727, src/runtime/sql_aggregate.cpp:270, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0035

[Lines 334–334](../../../../../src/runtime/sql_aggregate.cpp#L334); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SqlAggregateRuntime::ready() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe facade/token availability without exposing private tentative state. |
| inputs / outputs | Facade/token -&gt; bool. |
| invariants | Empty/moved returns false; outer readiness also requires !busy and real source ready. |
| ownership | Reads retained scalar/handle only. |
| failure | No throw on valid internal source; no mutation. |
| cost | O(1), no allocation. |
| Design | include/crown/runtime/sql_aggregate.hpp:46, [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), src/runtime/sql_aggregate.cpp:271, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0036

[Lines 335–337](../../../../../src/runtime/sql_aggregate.cpp#L335); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
weighted::Multiplicity SqlAggregateRuntime::root_weight() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe genuine committed native full-root multiplicity. |
| inputs / outputs | Idle runtime -&gt; weighted::Multiplicity. |
| invariants | Outer busy check prevents tentative source/native visibility; not an aggregate/group count. |
| ownership | Borrows private source facade temporarily. |
| failure | Busy/moved facade Error. |
| cost | O(1) root summary read, no allocation. |
| Design | src/runtime/weighted.cpp:660, [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), src/runtime/sql_aggregate.cpp:272, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0037

[Lines 338–338](../../../../../src/runtime/sql_aggregate.cpp#L338); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryStatistics SqlAggregateRuntime::accounted_memory_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the actual retained receiving grant/statistics without minting another account. |
| inputs / outputs | Const lvalue facade -&gt; receiving account reference or statistics value. |
| invariants | All retained nested composition state has this owner; diagnostics are serialized but allowed while prepared. |
| ownership | Account reference borrows facade, explicit copies retain control; statistics own only counters. |
| failure | Empty/moved facade Error. |
| cost | O(1), no allocation. |
| Design | include/crown/resource/memory.hpp:106, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:275, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0038

[Lines 339–341](../../../../../src/runtime/sql_aggregate.cpp#L339); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t SqlAggregateRuntime::source_weight(TableId id, std::span<const sql_rows::Cell> cells) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe an authenticated committed complete physical source row weight. |
| inputs / outputs | Source id + borrowed complete physical cells -&gt; actual source weight. |
| invariants | Requires outer idle, then delegates real source validation/index lookup; no logical row API. |
| ownership | Retains neither input views nor mutable source handles. |
| failure | Busy/source id/type Error leaves state unchanged. |
| cost | Actual source row validation and map lookup, no allocation. |
| Design | src/runtime/sql_rows.cpp:489, [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), src/runtime/sql_aggregate.cpp:276, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0039

[Lines 342–348](../../../../../src/runtime/sql_aggregate.cpp#L342); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateRuntime::PreparedBatch SqlAggregateRuntime::prepare_batch(const sql_rows::NetBatch& batch)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare exactly one authentic physical-source/native/group transaction. |
| inputs / outputs | Physical sql_rows::NetBatch -&gt; opaque active composed token with complete output preview. |
| invariants | Open contiguous group Budget once, call private actual source.prepare_batch with required capture exactly once, latch busy only after all throws complete. |
| ownership | Accounted unique backing stores shared outer owner and internal child token; no separate source token or logical input API escapes. |
| failure | Sequence/source constraints/native/group/work/allocation/output failures unwind child rollback; facade remains ready at old sequence. |
| cost | One retained group allowance, source allowance and native allowance for whole command; O(touched work), no per-row exception wrapper. |
| Design | src/runtime/sql_rows.cpp:498, src/runtime/weighted.cpp:665, include/crown/resource/ownership.hpp:44, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:279, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0040

[Lines 349–349](../../../../../src/runtime/sql_aggregate.cpp#L349); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateRuntime::PreparedBatch::PreparedBatch(resource::AccountedUnique<Data> value) noexcept : data_(std::move(value))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move prepared backing into opaque public token without an allocation. |
| inputs / outputs | AccountedUnique&lt;Data&gt; -&gt; PreparedBatch ownership. |
| invariants | Only outer runtime constructs token; internal genuine source remains inaccessible. |
| ownership | Transfers single unique backing; shared outer owner retained inside. |
| failure | noexcept. |
| cost | O(1) ownership transfer, no allocation. |
| Design | include/crown/resource/ownership.hpp:41, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:286, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0041

[Lines 350–352](../../../../../src/runtime/sql_aggregate.cpp#L350); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateRuntime::PreparedBatch::PreparedBatch(PreparedBatch&&) noexcept = default; SqlAggregateRuntime::PreparedBatch& SqlAggregateRuntime::PreparedBatch::operator=(PreparedBa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Default token move and destruction so unique PreparedBatch::Data controls RAII rollback. |
| inputs / outputs | Move transfers the unique Data; overwritten/destroyed active token drops its old Data. |
| invariants | Moved-from token is invalid; last active Data destructor rolls back child and releases owner; move is not a commit. |
| ownership | Unique proposal workspace moves without copying; backing owner lifetime follows token. |
| failure | Noexcept move/destruction; rollback body is noexcept. |
| cost | O(1) transfer; replacing/destroying active token pays real proposal and child undo teardown. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md), src/runtime/sql_aggregate.cpp:287, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0042

[Lines 353–356](../../../../../src/runtime/sql_aggregate.cpp#L353); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SqlAggregateRuntime::PreparedBatch::Data& SqlAggregateRuntime::PreparedBatch::data() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate facade/token handle before accessing private owner state. |
| inputs / outputs | Facade or token -&gt; private Data&. |
| invariants | No null/closed dereference; token requires live, facade requires retained shared owner. |
| ownership | Borrows existing private storage only. |
| failure | Empty/moved/closed Error before operational access. |
| cost | O(1), no allocation on valid access. |
| Design | include/crown/resource/ownership.hpp:17, [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), src/runtime/sql_aggregate.cpp:290, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0043

[Lines 357–357](../../../../../src/runtime/sql_aggregate.cpp#L357); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SqlAggregateRuntime::PreparedBatch::active() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe facade/token availability without exposing private tentative state. |
| inputs / outputs | Facade/token -&gt; bool. |
| invariants | Empty/moved returns false; outer readiness also requires !busy and real source ready. |
| ownership | Reads retained scalar/handle only. |
| failure | No throw on valid internal source; no mutation. |
| cost | O(1), no allocation. |
| Design | include/crown/runtime/sql_aggregate.hpp:46, [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), src/runtime/sql_aggregate.cpp:294, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0044

[Lines 358–358](../../../../../src/runtime/sql_aggregate.cpp#L358); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const sql_aggregate::Epoch& SqlAggregateRuntime::PreparedBatch::preview() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow sealed epoch/output metadata from an active composed token. |
| inputs / outputs | Active const lvalue token -&gt; const Epoch&; rvalue access deleted. |
| invariants | No child mutation/token escape; preview is invalidated by move/close/death, native D handle empty. |
| ownership | Caller may explicitly copy Tuple/Program handles for ownership; reference itself borrows token. |
| failure | Closed/moved token rejected before reference return. |
| cost | O(1), no allocation on valid access. |
| Design | include/crown/runtime/sql_aggregate.hpp:46, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:295, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0045

[Lines 359–361](../../../../../src/runtime/sql_aggregate.cpp#L359); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_aggregate::Epoch SqlAggregateRuntime::PreparedBatch::commit()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close public live token after its nonallocating private joint commit. |
| inputs / outputs | Active token -&gt; owning Epoch; closed/moved token rejected. |
| invariants | Move/save result, reset backing Data before return; native D already dropped; output survives facade death. |
| ownership | Unique backing releases child/proposals before retained outer owner; empty deleter may keep account control only. |
| failure | Invalid token Error before internal barrier; genuine commit has no allocation or normal error. |
| cost | O(joint publish/teardown); no new allocation. |
| Design | src/runtime/weighted.cpp:727, src/runtime/sql_rows.cpp:523, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:296, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0046

[Lines 362–362](../../../../../src/runtime/sql_aggregate.cpp#L362); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SqlAggregateRuntime::PreparedBatch::rollback() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly close an unpublished token and free its backing workspace promptly. |
| inputs / outputs | Any token -&gt; closed; empty/moved is harmless. |
| invariants | Unique reset invokes private destructor/real child rollback; frontier unchanged. |
| ownership | Child/proposals die while outer owner retained; only empty deleter account ref remains. |
| failure | noexcept, no broad catch. |
| cost | Prefunded rollback/release only; no allocation. |
| Design | src/runtime/sql_rows.cpp:526, src/runtime/weighted.cpp:685, [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:299, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0047

[Lines 363–372](../../../../../src/runtime/sql_aggregate.cpp#L363); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_aggregate::Snapshot SqlAggregateRuntime::snapshot(aggregate::SnapshotLimits limits) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return eager owning full-key SQL aggregate results from committed groups. |
| inputs / outputs | Committed owner and SnapshotLimits -&gt; Snapshot retaining original Program, sequence and full GroupResult tuples. |
| invariants | Busy rejected; group cap checked before reserve; rendering uses actual kernel descriptors and shared math. No native join scan or output-key dedup. |
| ownership | Keys share owned group tuples, output values copied receiver-owned; Data output scratch cleared by common render. |
| failure | Busy/group/work/render/memory error destroys incomplete result only. |
| cost | Explicit all-group operation: one cap/reserve plus each O output fields/copy; distinct work Budget per requested snapshot, not an epoch refill. |
| Design | src/runtime/aggregate.cpp:407-414, [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), src/runtime/sql_aggregate.cpp:300, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0048

[Lines 373–378](../../../../../src/runtime/sql_aggregate.cpp#L373); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sql_aggregate::SourceSnapshot SqlAggregateRuntime::source_snapshot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture the composed owner’s original aggregate binding together with its child’s current physical image. |
| inputs / outputs | Requires outer idle state, delegates limits to SqlRowsRuntime::source_snapshot, checks the child sequence against the aggregate sequence, and returns the aggregate program handle paired with the moved child image. |
| invariants | No aggregate result/group snapshot is substituted for physical rows. The child check enforces one committed epoch; the assert documents the internal atomic-sequence invariant, not a release-mode external validation gate. |
| ownership | Copies a shared immutable aggregate-program handle and transfers the child image. No active token, child runtime facade or lease escapes. |
| failure | Outer busy error precedes delegation; child quiescence/row/work/allocation errors propagate. No catch or source/group state mutation occurs. |
| cost | One child image scan/reserve; pairing adds only handle copy and child move. No second source copy, group rendering or cold rebuild. |
| Design | [src/runtime/sql_aggregate.cpp](../../../../../src/runtime/sql_aggregate.cpp), [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0049

[Lines 379–379](../../../../../src/runtime/sql_aggregate.cpp#L379); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
} // namespace crown::runtime
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the runtime namespace after the public composed-runtime definitions. |
| inputs / outputs | Scope close only. |
| invariants | No API or state is introduced at this brace. |
| ownership | No ownership effect. |
| failure | Compile-time scope validation. |
| cost | Zero runtime work. |
| Design | [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/cost-and-lifetime.md), [build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/reference-plan.md), src/runtime/sql_aggregate.cpp:310, [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/aggregates.md](../../../../aggregates.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md) |
