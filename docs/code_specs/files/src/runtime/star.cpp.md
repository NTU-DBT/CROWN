# `src/runtime/star.cpp` — block usage map

[Source](../../../../../src/runtime/star.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain light-filtered groups, heavy predicates, exact degrees and sparse hysteretic migrations beside full original source validation.

Snapshot SHA-256: `a30817d3e7b5a2d8f7fcc98ea78585a7a43e3d2b18d563c5002e2e509454c224`. 438 lines partitioned into 38 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [star](../../../subsystem_contracts.md#star). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/runtime/star.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 8–10](../../../../../src/runtime/star.cpp#L8) | Callable definition: storage::RowView scalar_key(const storage::ScalarView& value) noexcept | calls storage::RowView::borrow; returns storage::RowView::borrow(std::span&lt;const storage::ScalarView&gt;(&value, 1)) · [reviewed contract](#b0002) |
| [B0003 · 11–13](../../../../../src/runtime/star.cpp#L11) | Callable definition: bool above_twice(std::uint64_t value, std::uint64_t threshold) noexcept | calls ; returns value &gt; threshold && value - threshold &gt; threshold · [reviewed contract](#b0003) |
| [B0004 · 14–18](../../../../../src/runtime/star.cpp#L14) | Callable definition: std::optional&lt;std::uint64_t&gt; epoch_threshold(std::uint64_t scale, std::size_t d) noexcept | calls sd::HIndex::power; returns 1; {} · [reviewed contract](#b0004) |
| [B0005 · 19–31](../../../../../src/runtime/star.cpp#L19) | Callable definition: CompiledProgram import_program(const resource::MemoryAccount& account, const PhysicalPlan& plan, storage::IndexWork limit) | calls options, std::min, storage::AccountedIndexWork::create, CompiledProgram::freeze; returns CompiledProgram::freeze(account, plan, work.get()) · [reviewed contract](#b0005) |
| [B0006 · 32–33](../../../../../src/runtime/star.cpp#L32) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0006) |
| [B0007 · 34–54](../../../../../src/runtime/star.cpp#L34) | Callable definition: Runtime::Data::Data(PhysicalRuntime source, const planner::star::Plan& plan, std::uint64_t limit, storage::IndexWork metadata_wor… | calls account, plan, program, import_program; growth emplace_back, push_back, reserve; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 55–57](../../../../../src/runtime/star.cpp#L55) | Callable definition: void Runtime::Data::readable() const | calls ready, Error · [reviewed contract](#b0008) |
| [B0009 · 58–62](../../../../../src/runtime/star.cpp#L58) | Callable definition: storage::RowView Runtime::Data::head_key(const sd::Fact& fact, sd::Scratch& scratch) const | calls clear, push_back, view, storage::RowView::borrow; returns storage::RowView::borrow(scratch.head); growth push_back; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 63–75](../../../../../src/runtime/star.cpp#L63) | Callable definition: storage::RowView Runtime::Data::group_key(const sd::Fact& fact, sd::Scratch& scratch) const | calls clear, emplace_back, push_back, view; returns storage::RowView::borrow(scratch.group); growth emplace_back, push_back; 1 loop sites; source comment (unverified): // A Boolean flag plus one value per coordinate encodes the full dynamic mask. · [reviewed contract](#b0010) |
| [B0011 · 76–78](../../../../../src/runtime/star.cpp#L76) | Explanatory comments or spacing. | source comment (unverified): // VS stores every light-eligible center row once. A group keeps counted DISTINCT · [reviewed contract](#b0011) |
| [B0012 · 79–103](../../../../../src/runtime/star.cpp#L79) | Callable definition: void Runtime::Data::attach(sd::Fact& fact, sd::Journal& journal, sd::Budget& budget, sd::Scratch& scratch) | calls sd::require, take, group_key, find; guard sd::require(fact.missing == 0 && !fact.group, "invalid light-filter attachment");; growth copy_of, emplace; 1 loop sites; source comment (unverified): // VS stores every light-eligible center row once. A group keeps counted DISTINCT · [reviewed contract](#b0012) |
| [B0013 · 104–118](../../../../../src/runtime/star.cpp#L104) | Callable definition: void Runtime::Data::detach(sd::Fact& fact, sd::Journal& journal, sd::Budget& budget, sd::Scratch& scratch) | calls take, find, head_key, sd::require; guard sd::require(projected != group.projections.end() && group.supports != 0, "missing projected support…; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 119–121](../../../../../src/runtime/star.cpp#L119) | Explanatory comments or spacing. | source comment (unverified): // Degree-directory edits move one intrusive key between occupied-degree buckets. · [reviewed contract](#b0014) |
| [B0015 · 122–144](../../../../../src/runtime/star.cpp#L122) | Callable definition: void Runtime::Data::degree(sd::Dimension& dimension, sd::Key& key, std::uint64_t next, sd::Journal& journal, sd::Budget& budget) | calls take, find, sd::require, end; guard sd::require(old != dimension.buckets.end() && old-&gt;second.count, "missing degree bucket");; growth emplace; source comment (unverified): // Degree-directory edits move one intrusive key between occupied-degree buckets. · [reviewed contract](#b0015) |
| [B0016 · 145–148](../../../../../src/runtime/star.cpp#L145) | Explanatory comments or spacing. | source comment (unverified): // A relabel changes roles without changing real sources, degrees or H. Detach · [reviewed contract](#b0016) |
| [B0017 · 149–167](../../../../../src/runtime/star.cpp#L149) | Callable definition: void Runtime::Data::relabel(sd::Dimension& dimension, sd::Key& key, bool heavy, sd::Journal& journal, sd::Budget& budget, sd::Scr… | calls take, detach, assign, emplace; growth emplace; 3 loop sites; source comment (unverified): // A relabel changes roles without changing real sources, degrees or H. Detach · [reviewed contract](#b0017) |
| [B0018 · 168–201](../../../../../src/runtime/star.cpp#L168) | Callable definition: void Runtime::Data::rebalance(sd::Dimension& dimension, sd::Key& changed, std::uint64_t h, sd::Journal& journal, sd::Budget& budg… | calls take, relabel, above_twice, size; growth push_back, reserve; 4 loop sites; source comment (unverified): // Only old LIGHT keys in \[new_tau,2*old_tau\] can become heavy. Sparse · [reviewed contract](#b0018) |
| [B0019 · 202–202](../../../../../src/runtime/star.cpp#L202) | Explanatory comments or spacing. |  |
| [B0020 · 203–244](../../../../../src/runtime/star.cpp#L203) | Callable definition: void Runtime::Data::satellite(std::size_t coordinate, storage::RowView row, bool insertion, sd::Journal& journal, sd::Budget& bud… | calls find, end, sd::require, emplace; guard sd::require(insertion, "missing satellite source key");; growth copy_of, emplace; 2 loop sites; source comment (unverified): // No center row, head projection or result union is visited here. · [reviewed contract](#b0020) |
| [B0021 · 245–245](../../../../../src/runtime/star.cpp#L245) | Explanatory comments or spacing. |  |
| [B0022 · 246–301](../../../../../src/runtime/star.cpp#L246) | Callable definition: void Runtime::Data::center_change(storage::RowView row, bool insertion, sd::Journal& journal, sd::Budget& budget, sd::Scratch& sc… | calls take, find, sd::require, end; guard sd::require(insertion == (found == facts.end()), "center source membership disagrees");; growth copy_of, emplace, push_back, reserve; 4 loop sites; source comment (unverified): // Histogram tokens remain private until the same final source/view barrier. · [reviewed contract](#b0022) |
| [B0023 · 302–302](../../../../../src/runtime/star.cpp#L302) | Explanatory comments or spacing. |  |
| [B0024 · 303–308](../../../../../src/runtime/star.cpp#L303) | Callable definition: Runtime::Runtime(const planner::star::Plan& plan, Options options) | calls sources, source_only, plan, account; growth make_accounted_shared · [reviewed contract](#b0024) |
| [B0025 · 309–311](../../../../../src/runtime/star.cpp#L309) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0025) |
| [B0026 · 312–315](../../../../../src/runtime/star.cpp#L312) | Callable definition: Runtime::Data& Runtime::data() const | calls Error; returns *data_ · [reviewed contract](#b0026) |
| [B0027 · 316–316](../../../../../src/runtime/star.cpp#L316) | Callable definition: const CompiledProgram& Runtime::program() const & | calls data; returns data().program · [reviewed contract](#b0027) |
| [B0028 · 317–317](../../../../../src/runtime/star.cpp#L317) | Callable definition: const resource::MemoryAccount& Runtime::account() const & | calls data; returns data().account · [reviewed contract](#b0028) |
| [B0029 · 318–318](../../../../../src/runtime/star.cpp#L318) | Callable definition: std::uint64_t Runtime::sequence() const | calls data, readable, sequence; returns d.sources.sequence() · [reviewed contract](#b0029) |
| [B0030 · 319–319](../../../../../src/runtime/star.cpp#L319) | Callable definition: bool Runtime::ready() const | calls data, ready; returns !d.updating && !d.readers && d.sources.ready() · [reviewed contract](#b0030) |
| [B0031 · 320–320](../../../../../src/runtime/star.cpp#L320) | Callable definition: bool Runtime::has_answer() const | calls data, readable, empty; returns !d.live.empty() · [reviewed contract](#b0031) |
| [B0032 · 321–352](../../../../../src/runtime/star.cpp#L321) | Callable definition: Epoch Runtime::apply(const PhysicalSetUpdate& update) | calls data, readable, Error, Writing; guard sd::require(preview.source.has_value(), "changed source has no pinned row");; returns result; growth insert; 1 loop sites; source comment (unverified): // Covers source publication, histogram commit and private journal retirement · [reviewed contract](#b0032) |
| [B0033 · 353–363](../../../../../src/runtime/star.cpp#L353) | Callable definition: State Runtime::state() const | calls data, readable, sequence, size; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0033) |
| [B0034 · 364–370](../../../../../src/runtime/star.cpp#L364) | Callable definition: std::optional&lt;KeyState&gt; Runtime::key(std::size_t coordinate, storage::ScalarView value) const | calls data, readable, size, Error; returns {}; KeyState{found-&gt;second.degree, found-&gt;second.heavy, found-&gt;second.present} · [reviewed contract](#b0034) |
| [B0035 · 371–371](../../../../../src/runtime/star.cpp#L371) | Callable definition: Database Runtime::source_snapshot() const | calls data, readable, snapshot; returns d.sources.snapshot().physical · [reviewed contract](#b0035) |
| [B0036 · 372–375](../../../../../src/runtime/star.cpp#L372) | Explanatory comments or spacing. | source comment (unverified): // Cold O(d*N + maintained index entries) inspection, with funded scratch and · [reviewed contract](#b0036) |
| [B0037 · 376–437](../../../../../src/runtime/star.cpp#L376) | Callable definition: void Runtime::check_invariants(std::uint64_t work) const | calls data, readable, scratch, size; guard budget.take(); sd::require(fact.values == &values && fact.keys.size() == d.dimensions.size(), "inva…; 10 loop sites; source comment (unverified): // Cold O(d*N + maintained index entries) inspection, with funded scratch and · [reviewed contract](#b0037) |
| [B0038 · 438–438](../../../../../src/runtime/star.cpp#L438) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::star · [reviewed contract](#b0038) |

## B0001

[Lines 1–7](../../../../../src/runtime/star.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:33e4175deb911e5c82fae9099ae2ebbb08ebea810549f032e8da6f2573a80dd8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open the star implementation over its private state/journal helpers. |
| inputs / outputs | The file includes star_detail.hpp and algorithm utilities, then declares its detail namespace alias. |
| invariants | No runtime owner or source mutation is created by file-level declarations. |
| ownership | Following functions operate on the explicit original-account Data owner. |
| failure | Compile/include failures are separate from runtime admission. |
| cost | Translation/declaration work only. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 8–10](../../../../../src/runtime/star.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L10:sha256:0ae3aa70d208f5c20ce2a2807b8661e93e4f57da04b4de00405b9c86b416fc23
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one typed scalar as a coordinate-key lookup row. |
| inputs / outputs | scalar_key(value) returns a one-element RowView over that caller scalar. |
| invariants | The view is used only while the scalar remains alive; it is not retained as map ownership. |
| ownership | No bytes are copied and no account is acquired; insertion explicitly imports an AccountedRow later. |
| failure | Noexcept view construction. |
| cost | Fixed span/view creation, excluding later scalar comparison. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 11–13](../../../../../src/runtime/star.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L13:sha256:180caccd5d8cdb11e8c649bb45cf9ae25a53362b04ee760acdff689ebf5be6c4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test the strict promotion/reset inequality without doubling overflow. |
| inputs / outputs | above_twice(value, threshold) returns whether mathematical value&gt;2*threshold. |
| invariants | Subtraction is evaluated only after value&gt;threshold, so it cannot underflow. |
| ownership | Inline integers only. |
| failure | Noexcept comparison; no saturation changes the predicate. |
| cost | Fixed word arithmetic. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0004

[Lines 14–18](../../../../../src/runtime/star.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L18:sha256:b850f4faf0111db51c11b8df9a5ce2fd840c5656aeb2ec4e021bd5e19a5fb31c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute a coordinate epoch threshold from its scale and center arity. |
| inputs / outputs | epoch_threshold(scale,d) returns one for d1, infinity for overflowing scale+1, or exact (scale+1)^(d-1). |
| invariants | The exponent-zero case precedes base-overflow handling; positive arity is an admitted-plan premise. |
| ownership | No source/key owner is accessed. |
| failure | Noexcept; infinity is represented explicitly. |
| cost | Fixed boundary tests and bounded HIndex integer-power work. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0005

[Lines 19–31](../../../../../src/runtime/star.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L31:sha256:10b5b3cbf1915f167c5c5aaec8e8a86d0bf192af719f51adbf76186c664b124c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import the original comparison/schema program through an explicit original-account cold grant. |
| inputs / outputs | import_program takes account, genuine PhysicalPlan and IndexWork; it independently caps all five fields against indexed per_operation policy and freezes the original program. |
| invariants | Structural steps, scalar fields/bytes, pointer slots and link actions each retain their ceiling. This grant is not recreated by updates and supplies no star execution guarantee. |
| ownership | AccountedIndexWork object/control and all frozen program metadata use the coordinator account; the temporary work owner expires after cold freeze. |
| failure | Metadata-domain or memory refusal unwinds private construction before a Runtime is returned; no hidden unmetered original-program import remains. |
| cost | Cold program traversal/copy, finite selected index-work domains and actual allocation/scalar costs; no per-epoch work. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0006

[Lines 32–33](../../../../../src/runtime/star.cpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L33:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the file-local helper namespace before owner definitions. |
| inputs / outputs | Namespace scaffolding separates helpers from Runtime::Data member definitions. |
| invariants | It changes lookup scope only, with no new proof or execution mode. |
| ownership | No storage ownership. |
| failure | No runtime failure. |
| cost | No runtime work. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 34–54](../../../../../src/runtime/star.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L54:sha256:7d41e943cabbbc7d4d41f93dcb2872537ee40f516137ebfac28e933060f91a63
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the empty native star state on the source coordinator account. |
| inputs / outputs | Data imports the genuine comparison/schema program with metadata_work, moves the source-only owner, and copies coordinate/routes/head/free mappings. |
| invariants | The source account funds all imports/indexes. The cold import uses one five-domain grant capped by genuine indexed policy; general program guarantees are not reused as the star profile. |
| ownership | Shared Data owns sources, program and accounted containers. Admitted compiler-vector spans are copied, not borrowed. |
| failure | Cold work-domain, freeze/vector/account refusal unwinds private construction; the caller Plan remains valid. |
| cost | Cold metadata freeze and O(catalog+d+head width) setup/capacity; no original generic join-maintenance runtime is initialized. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 55–57](../../../../../src/runtime/star.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L57:sha256:ffee6f0b75aef6cfd8db6785aa456d1371ec1ccfaa9938c26e0c43833b154726
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a readable committed source/view boundary. |
| inputs / outputs | Data::readable rejects updating or a nonready source coordinator. |
| invariants | The whole private write includes source commit, H commit and journal retirement; no mutable view/source read escapes between those stages. |
| ownership | No ownership change. |
| failure | A busy source raises star_busy. |
| cost | Constant writing-flag and source-readiness checks. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 58–62](../../../../../src/runtime/star.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L62:sha256:33266a93879ea8edcdb46d0412d37d57ab2c99e03138eec9c1cfdc68cf1b7e12
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a borrowed full-head projection in reusable scratch. |
| inputs / outputs | head_key reads the fact center fields in the original ordered/repeated head mapping. |
| invariants | Every distinct output variable is retained in its declared position; aliases/types remain in program result metadata. |
| ownership | Scratch owns cell capacity; ScalarViews borrow immutable fact bytes until copied into a retained projection. |
| failure | Admitted field IDs and reserved scratch capacity are preconditions; owning key construction is separate and fallible. |
| cost | O(head width) scalar copies; string bytes are not duplicated for the probe. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 63–75](../../../../../src/runtime/star.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L75:sha256:3744c4087ec569914086b71d1aee9a90fb769efc72b0a43f3b2a03faf4721747
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the complete dynamic heavy partition and heavy-coordinate identity. |
| inputs / outputs | group_key emits one heavy flag and one actual/sentinel value per coordinate, plus the ordered heavy Key pointer list. |
| invariants | Light positions always use integer zero after a false flag; true heavy slots retain their typed value. No machine-word mask truncation. |
| ownership | Borrowed scratch views/pointers require resident fact/key storage; retained group keys later import their own native row. |
| failure | Scratch was reserved for 2*d cells and d pointers before processing rows. |
| cost | O(d) temporary cell/pointer work plus later retained-key copies and ordered comparison. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 76–78](../../../../../src/runtime/star.cpp#L76); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L76-L78:sha256:24a66ab81c034b061acbadc4927a7ffeb7fae3777d9e0f08911e59bba1e80ada
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the light-filtered/grouped-set support invariant. |
| inputs / outputs | Comment identifies VS center-row contribution, per-group counted full-head projection and VC live-group set. |
| invariants | The maintained VC is not an eager globally distinct result union. |
| ownership | Facts/groups/projections own their described rows and reverse memberships. |
| failure | attach/detach below enforce this invariant through the shared inverse journal. |
| cost | Projection/group support changes are paid on actual touched rows; result deduplication is deferred to cursors. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 79–103](../../../../../src/runtime/star.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L103:sha256:ccb48848a0b855d75358567f5756d258ca065c1bd17984f97e38aa3f0366ee11
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach one light-eligible center row to its counted heavy group. |
| inputs / outputs | Find/create the group, publish reverse heavy-key memberships, find/create/increment head support, and link the fact; activate a first supported group with no missing heavy predicate. |
| invariants | The fact has missing==0 and no existing group. Projected collisions increment support instead of duplicating a set answer. |
| ownership | New group/projection rows and containers use the original account; raw reverse pointers refer to resident map records. |
| failure | Every fallible allocation/edit has its inverse funded first. Overflow/invariant/work/memory refusal rolls back the whole private view prefix. |
| cost | O(d+head width) row/probe work and ordered group/projection/reverse-set operations; no global answer-union maintenance. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 104–118](../../../../../src/runtime/star.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L104-L118:sha256:906c5dc92b7f478bf932058623301d914100ffb6e9bfa6679c1a48d8838af458
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove one fact contribution and reclaim its last supported view records. |
| inputs / outputs | detach decrements/removes its head count, group support and fact link, then removes live/reverse/group records when support reaches zero. |
| invariants | A null group is an already noneligible row and is inert. A retained group has positive support and nonempty projected counts. |
| ownership | Extracted projection/group nodes remain owned by inverse entries until restoration or committed retirement. |
| failure | Missing support is an invariant error; work/allocation refusal before later edits triggers inverse rollback. |
| cost | One head probe and support update, plus O(number of heavy coordinates) index removals at the last support. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 119–121](../../../../../src/runtime/star.cpp#L119); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L119-L121:sha256:8bd27fb83b7d1538201657a147fd288dfb728f8b6fc176800a7b7b7a801a404a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the sparse intrusive degree-directory update ordering. |
| inputs / outputs | Comment identifies one key move between occupied positive-degree buckets. |
| invariants | Each changed pointer/count has a funded inverse; empty buckets disappear. |
| ownership | Key records own links and the degree map owns bucket heads/counts. |
| failure | The following private operation remains enclosed by source/view rollback. |
| cost | Only affected buckets/neighbor links are edited, not all degree keys. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0015

[Lines 122–144](../../../../../src/runtime/star.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L122-L144:sha256:2e0c264bb013fc9c0b230b47b1701b7ac2847c834556f934306dc35c044e5f0c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move one coordinate key between its old/new degree buckets. |
| inputs / outputs | Unlink the key from the old bucket, decrement/prune it, assign degree, and prepend the key to a found/funded new bucket. |
| invariants | Positive old degree has a valid occupied bucket; zero next degree has no directory membership. |
| ownership | All scalar links/counters and map extraction/insertion belong to the same journal; targets remain resident or retained for reverse undo. |
| failure | Work/node/capacity refusal preserves the prior epoch through rollback; a missing old bucket is an invariant failure. |
| cost | A constant number of ordered bucket operations and intrusive neighbor edits, with actual inverse/capacity costs. |
| Design | [docs/star.md](../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0016

[Lines 145–148](../../../../../src/runtime/star.cpp#L145); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L145-L148:sha256:7d0b48943d1f9de510e75ca90637ba3b5492903db30aabd089d3c5337573ce1a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain output-preserving private label migration. |
| inputs / outputs | Comment distinguishes old VS detach, label change and reattachment under new light/heavy roles. |
| invariants | Migration does not fake source updates, alter real degree/H or rebuild unrelated heavy row buckets. |
| ownership | Existing source/fact/key identities are retained across internal role changes. |
| failure | The inverse journal protects every private change until the common barrier. |
| cost | Cost is incident-row migration and associated projection/index edits. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 149–167](../../../../../src/runtime/star.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L149-L167:sha256:9f5c612c54b162856ae34164d5b75913f7262ba79874198ac2c025f4f2d1fef1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Migrate only one key whose heavy/light label changes. |
| inputs / outputs | relabel detaches all incident fact contributions, changes key label/heavy-set membership, recomputes light-missing counts and reattaches eligible rows. |
| invariants | An unchanged label returns immediately. Fact incidence and real satellite presence stay unchanged; groups may be rebuilt only for touched contributions. |
| ownership | The key fact set is borrowed and not edited by this traversal; extracted view nodes remain journal-owned for rollback. |
| failure | Any work/allocation/invariant failure reverses label, links and support changes before source publication. |
| cost | O(incident rows*(d+head/index work)); center_visits counts both detach/reattach passes and migrated_rows counts each row once for this key relabel. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0018

[Lines 168–201](../../../../../src/runtime/star.cpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L168-L201:sha256:14371876bcae63d9e01a972dde6e9f7128ae40c9cec6931a23f31f6de407e854
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply hysteresis and affected-key-only scale resets. |
| inputs / outputs | rebalance promotes above2*tau, demotes belowtau/2, and resets when heavy count&gt;2*scale or exact prospective H&lt;scale/2. |
| invariants | Reset candidates are old heavy keys plus old light keys in the relevant degree band. Only changed labels migrate; arbitrarily huge unchanged heavy buckets are skipped. |
| ownership | Candidate pointer scratch is original-account private storage; the directory/heavy set own referenced resident keys. |
| failure | Scratch/work/migration refusal is journal-atomic. Threshold and scale assignments occur only after all candidate processing. |
| cost | Local crossing cost follows incident rows; reset degree-band enumeration/migrations obey the local audit argument, with std::map, d, scalar and allocator factors additional. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 203–244](../../../../../src/runtime/star.cpp#L203); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L203-L244:sha256:3a925ac8e14bd946512e5d9b00de301ae76004ef3c141ade9c0bca0dce4591bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Maintain a real unary satellite by its current key role. |
| inputs / outputs | Create/find its key, toggle real presence, then update heavy-group missing counts or light-fact missing counts and zero crossings. |
| invariants | Heavy branch walks key.groups only, never center rows or head projections. Light branch walks key.facts; a degree-zero absent key is reclaimed. |
| ownership | The source token pins the typed input; all imported key rows and reverse nodes use the original account and inverse journal. |
| failure | Source/key membership disagreement is an invariant failure. Work/memory/refusal unwinds source and view together. |
| cost | Group_visits for a heavy key, center_visits for a light key, plus actual ordered zero-crossing edits and separate source validation. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 246–301](../../../../../src/runtime/star.cpp#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L246-L301:sha256:a8aeb1c681290af95326ad7c88baa6d30926582b9ae1982246d651ca47eca51c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Maintain one actual center membership change and prepare every coordinate H. |
| inputs / outputs | Create/find the fact and coordinate keys, prepare H tokens, edit incidence/degree links, update VS support, rebalance from next_h, and prune zero-degree keys/final fact. |
| invariants | Each coordinate changes one degree by exactly +/-1. H remains uncommitted while view edits occur; deleting facts stay resident until their coordinate-vector last use. |
| ownership | Fact/key/group edits use one journal; H destination nodes are private tokens. Key nodes are retained if a real satellite is still present. |
| failure | Any degree/work/memory/invariant refusal rolls back all earlier coordinates and source preparation, without a full view clone. |
| cost | O(d) base memberships/H transitions plus actual threshold intervals and affected migrations; initial fact payload/head/group/index work remains real. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0024

[Lines 303–308](../../../../../src/runtime/star.cpp#L303); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L303-L308:sha256:8a0836ed022622a57d92451ce866c31e65c79826782bf55099d4d6a8b05d108c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the source-only coordinator and funded shared star owner. |
| inputs / outputs | Runtime creates the source-only coordinator from Options::sources, then funds shared Data and passes both per-epoch work and cold metadata_work. |
| invariants | The original program is schema/comparison metadata, while the private coordinator has empty routes/full constraints. No hidden per-update metadata work grant is created. |
| ownership | The shared Data object/control and all nested containers retain the same original account. |
| failure | Source, object, five-domain metadata or memory admission failure leaves no public Runtime and preserves Plan. |
| cost | Cold source/metadata admission and fixed-query index setup; no per-event comparison runtime or hidden memory grant. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0025

[Lines 309–311](../../../../../src/runtime/star.cpp#L309); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L309-L311:sha256:d1c5047f2b9543cf3d82b13faa99266df419fa743ad54b0a7d9addc0e3f60d23
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use ordinary destruction and move transfer for the runtime handle. |
| inputs / outputs | Default destructor/move operations release or transfer shared Data. |
| invariants | Cursor shared ownership can retain Data after the public Runtime handle is gone. |
| ownership | Last owner destroys source/view state through existing account allocators. |
| failure | Move is noexcept; moved-from public access is checked by data(). |
| cost | Handle movement is fixed-size; final release can scale with retained source/view metadata and rows. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0026

[Lines 312–315](../../../../../src/runtime/star.cpp#L312); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L312-L315:sha256:fa42d3443c8efc0aeabd407037c303e074776fda09003c47ffd4603cb18f4db8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a live runtime owner before accessing Data. |
| inputs / outputs | data() returns the shared private Data reference or raises star_state for a moved-from handle. |
| invariants | It checks handle presence, not source readiness or reader exclusion; callers add the appropriate boundary check. |
| ownership | Returned reference borrows the Runtime/cursor-retained Data owner. |
| failure | Moved-from access fails before dereferencing private state. |
| cost | Constant pointer check and reference return. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0027

[Lines 316–316](../../../../../src/runtime/star.cpp#L316); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L316-L316:sha256:e8747cd11f6b67bd4cb564b9850bc857935a8e303440c7a179771dc97c98465e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the genuine original compiled answer program. |
| inputs / outputs | program() returns Data::program as a const lvalue reference. |
| invariants | The returned original query/schema program carries its GENERAL execution profile. It is neither the source-only program nor the star pacing/cleanup guarantee. |
| ownership | Caller must retain Runtime or copy the genuine CompiledProgram handle before releasing its owner. |
| failure | Moved-from Runtime is rejected by data(); direct temporary borrowing is deleted in the header. |
| cost | Constant handle/reference access. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0028

[Lines 317–317](../../../../../src/runtime/star.cpp#L317); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L317-L317:sha256:37c4f8acd35c7d8ddcaa7d160f3861eaec3a86e914e16b0700d36317093af787
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the original finite account used by source and star state. |
| inputs / outputs | account() returns Data::account as a const lvalue reference. |
| invariants | The reference is not a replacement budget and does not refill native admission. |
| ownership | Caller must retain the Runtime or copy the account handle for independent lifetime. |
| failure | Moved-from Runtime is rejected; direct temporary borrowing is deleted. |
| cost | Constant reference access; account observations have their separately documented costs. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0029

[Lines 318–318](../../../../../src/runtime/star.cpp#L318); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L318-L318:sha256:a62a92827b854bc9f3e97726737beb3898412feffdaf76d269e627338b4846ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the committed original physical sequence. |
| inputs / outputs | sequence checks Data/readability then returns sources.sequence(). |
| invariants | A private source update is never presented as a committed star sequence. |
| ownership | Returns a copied uint64 value. |
| failure | Moved/busy owner access raises its scoped state error. |
| cost | Constant readiness/sequence access. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0030

[Lines 319–319](../../../../../src/runtime/star.cpp#L319); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L319-L319:sha256:9ba97dc2f2202fab294afe401458ae01724f7ef0408ce7e7d361f122d4ae235e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report whether updates can start at the current boundary. |
| inputs / outputs | ready returns true only when no private writing interval, no star readers and a ready source coordinator. |
| invariants | It cannot report write readiness in the source-committed/H-pending or journal-retirement interval. |
| ownership | No owner or lease is acquired by the boolean report. |
| failure | A moved-from Runtime fails through data(). |
| cost | Constant scalar/source readiness checks. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0031

[Lines 320–320](../../../../../src/runtime/star.cpp#L320); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L320-L320:sha256:f8f375bc7e9bafaea59c95ff4a93b834bfe066ee0a1a89a7bc00e57f335f1482
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test current answer existence from maintained live groups. |
| inputs / outputs | has_answer returns whether the readable live-group set is nonempty. |
| invariants | Any live group has positive support/projections and all heavy predicates present. |
| ownership | No cursor, result payload or source snapshot is allocated. |
| failure | Moved/busy owner access is rejected. |
| cost | Constant live-set emptiness test, unlike result materialization or cursor cleanup. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0032

[Lines 321–352](../../../../../src/runtime/star.cpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L321-L352:sha256:6344c847a2a1710f9c2b54105dd7aeb09a818263111d88b14184a0667990f655
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit one physical input and star view through the common source/H/journal barrier. |
| inputs / outputs | apply validates read/write exclusion, prepares full source state, dispatches real center/satellite changes, then commits source, H tokens and journal and returns Epoch. |
| invariants | A local Writing guard covers source preparation, all view edits, source/H commit and journal retirement, including allocation callbacks. Duplicate/absent/unrouted events preserve view/H; readers exclude writes. |
| ownership | One original-account journal/H/scratch set encloses touched edits; source preview pins its typed row. The writing flag outlives all private token/journal destruction. |
| failure | All fallible edits precede valid no-allocation commitment. Any earlier refusal reverses view/H storage and source preparation before Writing resets, preserving the prior epoch. |
| cost | Actual affected heavy/light maintenance and selected metrics plus complete separate source/constraint/storage work; no full answer delta is emitted. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0033

[Lines 353–363](../../../../../src/runtime/star.cpp#L353); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L353-L363:sha256:393dc3d88f090638b6b65eaaae4496e74b6cd8f81fe11f0e8fd1708cb8f498d8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture committed gauges without exporting internal pointers. |
| inputs / outputs | state returns sequence, fact/group/live sizes and one DimensionState per coordinate. |
| invariants | H, scale, positive/heavy key counts and optional threshold describe one readable serial view. |
| ownership | OwnerAllocator funds and retains the diagnostic vector on the original account; copied values can outlive Runtime. |
| failure | Busy/moved access or capture allocation refusal changes no maintained state. |
| cost | O(d) values and vector capacity allocation. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0034

[Lines 364–370](../../../../../src/runtime/star.cpp#L364); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L364-L370:sha256:0bfd549edb07622de395d0d84754c5bd292dad94486d5224df44d02e428aba17
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probe a typed coordinate value for its retained degree/label/presence. |
| inputs / outputs | key validates coordinate range and performs a transparent one-cell row lookup, returning optional KeyState. |
| invariants | No key means no tracked center/satellite record; a present real satellite can legitimately return degree zero. |
| ownership | The scalar probe is borrowed only for the call; the result contains copied scalars. |
| failure | Out-of-range coordinate raises star_coordinate; busy/moved access is rejected. |
| cost | One ordered row lookup with actual typed/scalar-byte comparisons; no retained probe allocation. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0035

[Lines 371–371](../../../../../src/runtime/star.cpp#L371); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L371-L371:sha256:902c15d416c51d73e0b945390120a7269b1ab7416430cecc2179cd34604a4e1c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a full owning ordinary source database for examination. |
| inputs / outputs | source_snapshot returns the private source owner physical snapshot Database. |
| invariants | It includes all original catalog tables, not just center or satellites. |
| ownership | The returned caller DTO owns ordinary rows/strings; it is outside native retained account payload boundaries. |
| failure | Moved/busy access and diagnostic/export allocation failure propagate without mutation. |
| cost | Full source scan/copy cost, explicitly not a hot maintenance or H primitive. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0036

[Lines 372–375](../../../../../src/runtime/star.cpp#L372); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L372-L375:sha256:565c2888cfe7c8e671b54a25e0972f62272514ec6c35e30500dace754f4fa9b5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scope the internal star consistency inspector. |
| inputs / outputs | Comment describes a cold shared-grant check over maintained records/links. |
| invariants | It checks internal view consistency; original-CQ answer/source agreement is an independent A04 obligation. |
| ownership | Inspection scratch is funded on the original account. |
| failure | The following method may refuse its grant or allocation without changing sources/view. |
| cost | O(d*N+maintained index entries) visits plus ordered/scalar/account costs. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0037

[Lines 376–437](../../../../../src/runtime/star.cpp#L376); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L376-L437:sha256:2ac191d499482b235c1bc151158bb0da896f1adb33385b863701d0609b9bc60e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Audit committed fact/group/projection/coordinate/H invariants with a bounded cold grant. |
| inputs / outputs | Check fact coordinate reverses/light eligibility, group identity/support/liveness, exact projection counts, H suffixes, key census/heavy band and intrusive degree lists. |
| invariants | Counts must agree across actual maintained structures; source answer equivalence is not inferred solely from these local checks. |
| ownership | Temporary expected-support map and scalar/pointer buffers use original-account scratch; retained records are borrowed read-only. |
| failure | Budget, memory or invariant refusal leaves maintained state unchanged and identifies no independently proved arbitrary-memory corruption safety. |
| cost | Whole maintained-state inspection with O(d*N+index entries) selected visits; ordered lookup, row widths, scratch allocations and H scans are actual additional work. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0038

[Lines 438–438](../../../../../src/runtime/star.cpp#L438); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L438-L438:sha256:e898273caf1be38528f5e43eb29805db329a1e942171a5ddef8c4d4c074bbfe3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the star runtime implementation namespace. |
| inputs / outputs | Namespace closure ends definitions in crown::runtime::star. |
| invariants | It introduces no implicit flush, publication or owner. |
| ownership | No storage ownership. |
| failure | No runtime failure. |
| cost | No runtime work. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md) |
