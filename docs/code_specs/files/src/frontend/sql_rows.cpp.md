# `src/frontend/sql_rows.cpp` — block usage map

[Source](../../../../../src/frontend/sql_rows.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics.

Snapshot SHA-256: `dcc77581923153bb22f2c06056836b8974d3feb7463efbe3a4741b5ab04421b4`. 584 lines partitioned into 55 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../sql_support.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../src/frontend/sql_rows.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 18–21](../../../../../src/frontend/sql_rows.cpp#L18) | Callable definition: template&lt;class T&gt; auto allocator(const resource::MemoryAccount& account) | calls ; returns resource::MemoryAllocator&lt;T&gt;(account, resource::MemoryPurpose::immutable_metadata, · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../src/frontend/sql_rows.cpp#L22) | Callable definition: \[\[noreturn\]\] void fail(std::string code, std::string message) | calls Error, std::move · [reviewed contract](#b0003) |
| [B0004 · 23–24](../../../../../src/frontend/sql_rows.cpp#L23) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 25–29](../../../../../src/frontend/sql_rows.cpp#L25) | Callable definition: std::size_t merge_owner(std::size_t left, std::size_t right) | calls ; returns right; left · [reviewed contract](#b0005) |
| [B0006 · 30–34](../../../../../src/frontend/sql_rows.cpp#L30) | Callable definition: template&lt;class T&gt; std::span&lt;const T&gt; append(Items&lt;T&gt;& target, const std::vector&lt;T&gt;& values) | calls empty, size, insert, end; returns {}; {target.data() + begin, values.size()}; growth insert · [reviewed contract](#b0006) |
| [B0007 · 35–39](../../../../../src/frontend/sql_rows.cpp#L35) | Callable definition: template&lt;class T&gt; std::span&lt;const T&gt; rebase(std::span&lt;const T&gt; old, const Items&lt;T&gt;& source, const Items&lt;T&gt;& target) | calls empty, data, size; returns {}; {target.data() + (old.data() - source.data()), old.size()} · [reviewed contract](#b0007) |
| [B0008 · 40–71](../../../../../src/frontend/sql_rows.cpp#L40) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace · [reviewed contract](#b0008) |
| [B0009 · 72–82](../../../../../src/frontend/sql_rows.cpp#L72) | Callable definition: explicit Data(const resource::MemoryAccount& owner) : account(owner), names(allocator&lt;resource::AccountedText&gt;(owner)), sources(a… | calls account, names, sources, columns · [reviewed contract](#b0009) |
| [B0010 · 83–88](../../../../../src/frontend/sql_rows.cpp#L83) | Callable definition: std::string_view name(std::string_view text) | calls rows_detail::text_fits, fail, push_back, resource::AccountedText::copy_of; returns names.back().view(); growth copy_of, push_back · [reviewed contract](#b0010) |
| [B0011 · 89–99](../../../../../src/frontend/sql_rows.cpp#L89) | Callable definition: void freeze_values(std::span&lt;const SqlRowCell&gt; values) | calls push_back, empty, storage::AccountedRow::copy_of, storage::RowView::borrow; growth copy_of, push_back, reserve; 2 loop sites; source comment (unverified): // One actual row owns every present constant, including string bytes. · [reviewed contract](#b0011) |
| [B0012 · 100–103](../../../../../src/frontend/sql_rows.cpp#L100) | declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0012) |
| [B0013 · 104–111](../../../../../src/frontend/sql_rows.cpp#L104) | Type/record definition: struct DraftOccurrence |  · [reviewed contract](#b0013) |
| [B0014 · 112–112](../../../../../src/frontend/sql_rows.cpp#L112) | Type/record definition: struct Pair |  · [reviewed contract](#b0014) |
| [B0015 · 113–128](../../../../../src/frontend/sql_rows.cpp#L113) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |
| [B0016 · 129–133](../../../../../src/frontend/sql_rows.cpp#L129) | Callable definition: void charge(std::uint64_t amount = 1) | calls fail · [reviewed contract](#b0016) |
| [B0017 · 134–139](../../../../../src/frontend/sql_rows.cpp#L134) | Callable definition: std::size_t root(std::size_t value) | calls charge; returns top; 2 loop sites · [reviewed contract](#b0017) |
| [B0018 · 140–145](../../../../../src/frontend/sql_rows.cpp#L140) | Callable definition: void unite(std::size_t left, std::size_t right) | calls root, std::swap · [reviewed contract](#b0018) |
| [B0019 · 146–146](../../../../../src/frontend/sql_rows.cpp#L146) | Callable definition: const BoundExpression& expression(ExpressionId id) const | calls at; returns bound_.expressions.at(id.value) · [reviewed contract](#b0019) |
| [B0020 · 147–149](../../../../../src/frontend/sql_rows.cpp#L147) | Callable definition: std::size_t effective_arguments(const BoundOperation& node) const | calls size; returns node.operation == SqlOperator::using_value ? 1 : node.arguments.size() · [reviewed contract](#b0020) |
| [B0021 · 150–179](../../../../../src/frontend/sql_rows.cpp#L150) | Callable definition: void analyze() | calls size, resize, charge, storage::borrow_scalar; growth resize; 2 loop sites · [reviewed contract](#b0021) |
| [B0022 · 180–239](../../../../../src/frontend/sql_rows.cpp#L180) | Callable definition: void predicates() | calls pending, rbegin, rend, empty; growth emplace_back, push_back; 5 loop sites; source comment (unverified): // Local equality is already a guard. Only cross-occurrence classes · [reviewed contract](#b0022) |
| [B0023 · 240–263](../../../../../src/frontend/sql_rows.cpp#L240) | Callable definition: void fold_grounded() | calls size, charge, root, effective_arguments; growth push_back; 3 loop sites · [reviewed contract](#b0023) |
| [B0024 · 264–269](../../../../../src/frontend/sql_rows.cpp#L264) | Callable definition: Pair new_pair(SqlType type, bool nullable) | calls size, push_back, rows_detail::scalar; returns result; growth push_back · [reviewed contract](#b0024) |
| [B0025 · 270–274](../../../../../src/frontend/sql_rows.cpp#L270) | Callable definition: std::size_t head(VariableId variable) | calls find, end, size, push_back; returns found-&gt;second; position; growth emplace, push_back · [reviewed contract](#b0025) |
| [B0026 · 275–279](../../../../../src/frontend/sql_rows.cpp#L275) | Callable definition: void project(DraftOccurrence& occurrence, Pair pair, ExpressionId expression, SqlType type) | calls push_back, rows_detail::scalar; growth push_back · [reviewed contract](#b0026) |
| [B0027 · 280–351](../../../../../src/frontend/sql_rows.cpp#L280) | Callable definition: void core() | calls size, root, contains, emplace; returns a.variable &lt; b.variable; growth emplace, insert, push_back; 8 loop sites; source comment (unverified): // First keep structural join classes. Output-only nullable classes add a · [reviewed contract](#b0027) |
| [B0028 · 352–399](../../../../../src/frontend/sql_rows.cpp#L352) | Callable definition: void schemas() | calls size, std::visit, reserve, local; growth push_back, reserve, resize; 12 loop sites · [reviewed contract](#b0028) |
| [B0029 · 400–422](../../../../../src/frontend/sql_rows.cpp#L400) | Callable definition: void freeze_programs() | calls size, expression, reserve, push_back; growth push_back, reserve; 4 loop sites · [reviewed contract](#b0029) |
| [B0030 · 423–434](../../../../../src/frontend/sql_rows.cpp#L423) | Callable definition: void retain_constants() | calls needed, size, reset; 6 loop sites; source comment (unverified): // Only executable reads need initial constants. This cold pass drops dead · [reviewed contract](#b0030) |
| [B0031 · 435–438](../../../../../src/frontend/sql_rows.cpp#L435) | Callable definition: public: SqlRowsCompiler(const resource::MemoryAccount& account, const BoundSql& bound, const SqlRowsBindOptions& options) : bound… | calls bound_, options_, result_; growth make_accounted_shared · [reviewed contract](#b0031) |
| [B0032 · 439–484](../../../../../src/frontend/sql_rows.cpp#L439) | Callable definition: SqlRowsProgram run() | calls resource::AccountedText::copy_of, size, fail, storage::borrow_scalar; returns result; growth copy_of, push_back, resize; 5 loop sites; source comment (unverified): // Binary framing also preserves opaque catalog hint/untrusted-name bytes; · [reviewed contract](#b0032) |
| [B0033 · 485–487](../../../../../src/frontend/sql_rows.cpp#L485) | Closes surrounding scope/type. | source comment (unverified): // namespace detail · [reviewed contract](#b0033) |
| [B0034 · 488–491](../../../../../src/frontend/sql_rows.cpp#L488) | Callable definition: const SqlRowsProgram::Data& SqlRowsProgram::data() const | calls fail; returns *data_ · [reviewed contract](#b0034) |
| [B0035 · 492–492](../../../../../src/frontend/sql_rows.cpp#L492) | Callable definition: const resource::MemoryAccount& SqlRowsProgram::account() const & | calls data; returns data().account · [reviewed contract](#b0035) |
| [B0036 · 493–493](../../../../../src/frontend/sql_rows.cpp#L493) | Callable definition: std::string_view SqlRowsProgram::source() const & | calls data, view; returns data().source.view() · [reviewed contract](#b0036) |
| [B0037 · 494–494](../../../../../src/frontend/sql_rows.cpp#L494) | Callable definition: std::string_view SqlRowsProgram::binding_image() const & | calls data, view; returns data().binding.view() · [reviewed contract](#b0037) |
| [B0038 · 495–495](../../../../../src/frontend/sql_rows.cpp#L495) | Callable definition: std::string_view SqlRowsProgram::source_sha256() const & | calls data, size; returns {d.key.data(), d.key.size()} · [reviewed contract](#b0038) |
| [B0039 · 496–496](../../../../../src/frontend/sql_rows.cpp#L496) | Callable definition: SqlSemantics SqlRowsProgram::semantics() const | calls data; returns data().semantics · [reviewed contract](#b0039) |
| [B0040 · 497–497](../../../../../src/frontend/sql_rows.cpp#L497) | Callable definition: SqlWrapper SqlRowsProgram::wrapper() const | calls data; returns data().wrapper · [reviewed contract](#b0040) |
| [B0041 · 498–498](../../../../../src/frontend/sql_rows.cpp#L498) | Callable definition: bool SqlRowsProgram::contradiction() const | calls data; returns data().contradiction · [reviewed contract](#b0041) |
| [B0042 · 499–499](../../../../../src/frontend/sql_rows.cpp#L499) | Callable definition: std::uint64_t SqlRowsProgram::work() const | calls data; returns data().work · [reviewed contract](#b0042) |
| [B0043 · 500–500](../../../../../src/frontend/sql_rows.cpp#L500) | Callable definition: std::span&lt;const SqlRowsSource&gt; SqlRowsProgram::sources() const & | calls data; returns data().sources · [reviewed contract](#b0043) |
| [B0044 · 501–501](../../../../../src/frontend/sql_rows.cpp#L501) | Callable definition: std::span&lt;const SqlRowsConstraint&gt; SqlRowsProgram::constraints() const & | calls data; returns data().constraints · [reviewed contract](#b0044) |
| [B0045 · 502–502](../../../../../src/frontend/sql_rows.cpp#L502) | Callable definition: std::span&lt;const SqlRowsOccurrence&gt; SqlRowsProgram::occurrences() const & | calls data; returns data().occurrences · [reviewed contract](#b0045) |
| [B0046 · 503–503](../../../../../src/frontend/sql_rows.cpp#L503) | Callable definition: std::span&lt;const SqlRowsOutput&gt; SqlRowsProgram::outputs() const & | calls data; returns data().outputs · [reviewed contract](#b0046) |
| [B0047 · 504–504](../../../../../src/frontend/sql_rows.cpp#L504) | Callable definition: std::span&lt;const SqlRowCell&gt; SqlRowsProgram::initial_values() const & | calls data; returns data().initial · [reviewed contract](#b0047) |
| [B0048 · 505–505](../../../../../src/frontend/sql_rows.cpp#L505) | Explanatory comments or spacing. |  |
| [B0049 · 506–520](../../../../../src/frontend/sql_rows.cpp#L506) | Callable definition: SqlRowsCore SqlRowsProgram::export_core() const | calls data, size, push_back, std::to_string; returns result; growth emplace_back, push_back; 4 loop sites · [reviewed contract](#b0049) |
| [B0050 · 521–521](../../../../../src/frontend/sql_rows.cpp#L521) | Explanatory comments or spacing. |  |
| [B0051 · 522–568](../../../../../src/frontend/sql_rows.cpp#L522) | Callable definition: SqlRowsProgram SqlRowsProgram::freeze(const resource::MemoryAccount& account, const SqlRowsProgram& source) | calls resource::MemoryFailure, data, statistics, resource::AccountedText::copy_of; returns source; SqlRowsProgram(std::move(out)); growth copy_of, make_accounted_shared; 6 loop sites · [reviewed contract](#b0051) |
| [B0052 · 569–569](../../../../../src/frontend/sql_rows.cpp#L569) | Explanatory comments or spacing. |  |
| [B0053 · 570–580](../../../../../src/frontend/sql_rows.cpp#L570) | Callable definition: SqlRowsBindResult bind_sql_rows_into(const resource::MemoryAccount& account, std::string_view source, const Catalog& catalog, con… | calls resource::MemoryFailure, bind_sql, detail::SqlRowsCompiler, run; returns *diagnostic; detail::SqlRowsCompiler(account, std::get&lt;BoundSql&gt;(bound), options).run() · [reviewed contract](#b0053) |
| [B0054 · 581–583](../../../../../src/frontend/sql_rows.cpp#L581) | Callable definition: SqlRowsBindResult bind_sql_rows(std::string_view source, const Catalog& catalog, const SqlRowsBindOptions& options) | calls bind_sql_rows_into, resource::MemoryAccount::create; returns bind_sql_rows_into(resource::MemoryAccount::create(options.memory_limit_bytes), source, catalog, op… · [reviewed contract](#b0054) |
| [B0055 · 584–584](../../../../../src/frontend/sql_rows.cpp#L584) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::frontend · [reviewed contract](#b0055) |

## B0001

[Lines 1–17](../../../../../src/frontend/sql_rows.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:8825a4acccb32b5a2a76b94608ca2ed2ac94901105e59234d109f261f6502f38
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide funded arrays, owner lattice, append and clone rebasing. |
| inputs / outputs | append returns a span into reserved target; rebase transfers same offsets to cloned arrays. |
| invariants | Append callers reserve final total before publishing; nonempty old spans belong to source; sentinel owner states never index occurrences. |
| ownership | MemoryAllocator charges immutable metadata; views do not own. |
| failure | Allocation during append propagates; helper preconditions are trusted. |
| cost | Append linear in appended count; rebase O(1); merge_owner O(1). |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/include/crown/resource/ownership.hpp](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/include/crown/resource/ownership.hpp), [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows.cpp §L352-354,398-400,501-531](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows.cpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0002

[Lines 18–21](../../../../../src/frontend/sql_rows.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L21:sha256:9b1fe2b73a1e82b6e3b57b7c011237d56ea828297e9abdea37e3e716933ef061
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the compiler metadata allocator. |
| inputs / outputs | Existing account to typed allocator. |
| invariants | Uses immutable_metadata purpose/owner; never creates a replacement account. |
| ownership | Allocator retains the same account. |
| failure | Invalid allocator authority propagates MemoryFailure. |
| cost | Fixed descriptor construction; no payload allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0003

[Lines 22–22](../../../../../src/frontend/sql_rows.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:72265e34d5f86feeccff0eddc3a393d9fd4119d8db0624f2f970432ee128e16a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise one cold compiler diagnostic. |
| inputs / outputs | Owned code/message to Error. |
| invariants | The outer compiler boundary translates Error once. |
| ownership | Exception owns its strings. |
| failure | Always throws; string/exception allocation may fail. |
| cost | Diagnostic string ownership and exception cost only on rejection. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0004

[Lines 23–24](../../../../../src/frontend/sql_rows.cpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L24:sha256:bc1b3f1f9b4283358e7e04248d88a5b49218a3865877e607452813aabfb58032
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Defines compile-time constant(s) no_owner, several_owners; no dynamic initialization is introduced by these constants. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [docs/code_specs/files/src/frontend/sql_rows.cpp.md](sql_rows.cpp.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0005

[Lines 25–29](../../../../../src/frontend/sql_rows.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L29:sha256:f69bc300f7a148609e82b6e731688b747110e6b7e68719e98963756688bc73a3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Join effective expression ownership. |
| inputs / outputs | Two owner IDs to no/single/several owner. |
| invariants | Constants have no owner; equal single owners remain local; distinct owners become several. |
| ownership | Scalar values only. |
| failure | No throwing operation. |
| cost | Constant comparisons, no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0006

[Lines 30–34](../../../../../src/frontend/sql_rows.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L34:sha256:41cc9599b6018badffa1f54219b410878d8b2aa18dba8d0127a42497bc7a672b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one reserved immutable metadata slice. |
| inputs / outputs | Backing vector and cold values to borrowed span. |
| invariants | Callers reserve total capacity before publishing any nonempty span; empty slices need no pointer arithmetic. |
| ownership | Copies descriptors into the account-backed vector; span borrows it. |
| failure | Insertion failures unwind private construction. |
| cost | Linear in appended descriptors; no growth when the declared reserve holds. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0007

[Lines 35–39](../../../../../src/frontend/sql_rows.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L39:sha256:34bfec8cc265873e7da49272b8103e803453378990276df8bce76d0d89ed136a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move one cloned span to its new backing array. |
| inputs / outputs | Old span and corresponding arrays to receiver span. |
| invariants | Factory spans are slices of the stated old array; clone preserves array order and size. |
| ownership | Result borrows the new backing; old owner is not retained. |
| failure | Private valid-metadata precondition; no allocation or error translation. |
| cost | Constant offset/length arithmetic. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0008

[Lines 40–71](../../../../../src/frontend/sql_rows.cpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L71:sha256:18e2f3c9f311d38dd50dc07c09fc7477eacbeaac4533f610be67de39af9f0a5f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare immutable SQL program backing arrays, source/binding text and initial private defaults. |
| inputs / outputs | Data retains account, AccountedText source/binding, key, catalog/work/semantics/wrapper/contradiction, flat metadata arrays, literal_backing and initial nullable values. |
| invariants | The layout stores factory-produced metadata; declaration alone does not establish valid spans, compile SQL or compute a binding/hash. |
| ownership | Text and flat arrays use the retained account when constructed/populated; borrowed published spans later point into reserved immutable storage. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/docs/query_memory.md](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/docs/query_memory.md), [build/verification/w05-sql-rows-human-review-v1/sources/include/crown/storage/accounted_row.hpp §L78-124](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/include/crown/storage/accounted_row.hpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0009

[Lines 72–82](../../../../../src/frontend/sql_rows.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L72-L82:sha256:7eec4a0ef07d825688c30328070de05ca2f8cdb6d60dd7b3212d2b3c9f871db9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize one receiver-owned metadata container. |
| inputs / outputs | Existing account to empty arrays. |
| invariants | Every retained vector uses this account and immutable metadata attribution. |
| ownership | Data retains account and empty owning vectors. |
| failure | Partial member construction unwinds through RAII. |
| cost | Fixed number of allocator/empty-vector descriptors; later reserves pay their own sizes. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0010

[Lines 83–88](../../../../../src/frontend/sql_rows.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L88:sha256:bd8f29d57bac6fee9433bbd2682d401b4c8b1a572a6e369be7b49bee76383735
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one validated metadata name. |
| inputs / outputs | UTF8 text without NUL becomes an AccountedText and stable string_view. |
| invariants | Moving AccountedText descriptors does not move character blocks. |
| ownership | Data.names owns each character allocation. |
| failure | Unsupported text throws Error; allocation propagates. |
| cost | O(text bytes), one nonempty text block; vector may grow. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/include/crown/resource/text.hpp §L21-46](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/include/crown/resource/text.hpp), [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows_value.hpp §L10-26](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows_value.hpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0011

[Lines 89–99](../../../../../src/frontend/sql_rows.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L99:sha256:0d61aa3c2dab255d89862dc2e04b47720dae7fab2b1c48e84f0f0164903b7a0b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze present constant slots and preserve NULL placeholders. |
| inputs / outputs | Borrowed slots become initial views into one AccountedRow. |
| invariants | Present retained slot order maps to owned row cells. The compiler first removes unread folded slots and canonicalizes grounded outputs; NULL/dynamic/unused placeholders remain disengaged. Distinct still-live constant slots can still copy duplicate bytes. |
| ownership | Temporary present vector is cold standard memory; retained row and initial are funded. |
| failure | Allocation/account failure aborts unpublished Data. |
| cost | O(slot count + summed present string lengths), including duplicates. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/storage/accounted_row.cpp §L34-65](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/storage/accounted_row.cpp), [build/verification/w05-sql-rows-human-review-v1/README.md §cost item 3](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0012

[Lines 100–103](../../../../../src/frontend/sql_rows.cpp#L100); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L100-L103:sha256:6a9beddbf12653762ba41418d217a96a4b3f62f898365ff6bb517924ef686ea4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the prior private program-data declaration, opens the internal detail namespace, and begins SqlRowsCompiler, which converts a bound nullable SQL query into the immutable SQL rows program. |
| inputs / outputs | This span declares a helper type and its member layout; it does not call its operations. Member signatures and constructors in the enclosing file define the actual input/output boundary. |
| invariants | The type is an implementation detail at this scope; callers must use its neighboring validated factory/owner path rather than treat the declaration as a proof. |
| ownership | Construction initializes declared members according to their types; ownership follows each member type, with no extra owner introduced by the class declaration. |
| failure | The declaration itself does not translate runtime errors; construction and member operations may fail according to their definitions and allocation sources. |
| cost | No per-call cost is incurred by the declaration. Object construction/member operations may allocate or traverse according to their concrete member types and definitions. |
| Design | [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [docs/code_specs/files/src/frontend/sql_rows.cpp.md](sql_rows.cpp.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0013

[Lines 104–111](../../../../../src/frontend/sql_rows.cpp#L104); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L104-L111:sha256:f84add18a6c1e913ec6ebcf5df60960401e8d736b2180e739a1c94b436a146d6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track compiler-only equivalence/ownership/output state. |
| inputs / outputs | BoundSql and options are borrowed while draft vectors/maps accumulate the program. |
| invariants | Physical column offsets distinguish aliases of the same source; known_ separates NULL constants from dynamic placeholders. |
| ownership | Scratch is cold standard storage and is destroyed after publication. |
| failure | Allocation may propagate. |
| cost | O(expressions + physical columns + draft metadata) scratch. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/include/crown/frontend/bind.hpp §L52-65](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/include/crown/frontend/bind.hpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0014

[Lines 112–112](../../../../../src/frontend/sql_rows.cpp#L112); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L112-L112:sha256:7be04a7bf7dd6ddd9ba35d85547d5c9ff6ddc3a8563760b462449e2928b43d7f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Associate selected payload and optional presence variables. |
| inputs / outputs | One payload ID and optional flag ID. |
| invariants | Non-null classes omit presence; nullable selected classes carry both fields. |
| ownership | Inline compiler workspace only. |
| failure | No executable validation. |
| cost | Fixed-size value, no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0015

[Lines 113–128](../../../../../src/frontend/sql_rows.cpp#L113); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L113-L128:sha256:9d660b5dba54f3e89b1103fa057e251b2fa85297b8304dcd2adccbc108a54eef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declares SqlRowsCompiler’s borrowed BoundSql/options inputs, result handle, normalization vectors/maps, per-occurrence drafts, residual expressions, nullable slot, and work count. These are compiler scratch and retained result handles, not runtime row-update state. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [docs/code_specs/files/src/frontend/sql_rows.cpp.md](sql_rows.cpp.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0016

[Lines 129–133](../../../../../src/frontend/sql_rows.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L129-L133:sha256:5d0b18c91522735db2b2d29accf9e27ffe8841e08e4f44506b931c61804af8d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge explicit work and maintain disjoint equality classes. |
| inputs / outputs | charge updates monotone visits; root path-compresses; unite uses rank. |
| invariants | Successful work stays within optional limit and uint64; parents remain a forest. |
| ownership | Compiler-local arrays only. |
| failure | Exhaustion throws normalization resource_limit before counter addition; no refund. |
| cost | Union-find amortized inverse-Ackermann, with explicit root/edge debits; not all other compile work is metered. |
| Design | [build/verification/w05-sql-rows-human-review-v1/README.md §cost item 2](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0017

[Lines 134–139](../../../../../src/frontend/sql_rows.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L134-L139:sha256:470352069d58f83af306345ae548627c8dc79a0c65faa431611e9b272ad3309d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find and compress an equality class. |
| inputs / outputs | Admitted physical index to representative. |
| invariants | Parent links form a union-by-rank forest; path compression preserves equivalence. |
| ownership | Mutates only cold compiler parent workspace. |
| failure | Private indices are established from trusted binder columns. |
| cost | Iterative path traversal/compression; amortized union-find cost. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0018

[Lines 140–145](../../../../../src/frontend/sql_rows.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L140-L145:sha256:a6bb8271de2257111b76e7ec1852bac4c445230b342880488010c125d9290525
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Merge two unconditional equality classes. |
| inputs / outputs | Two physical indices. |
| invariants | Union by rank changes only representatives; flags/constants are reconciled in the following pass. |
| ownership | Cold parent/rank workspace only. |
| failure | Private valid indices; no account mutation. |
| cost | Two representative finds and constant union work. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0019

[Lines 146–146](../../../../../src/frontend/sql_rows.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L146-L146:sha256:2e33634fbd7fc9edc25c71a50f895092b3cb3c42733e78822b697190cb8f0e2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a freshly bound expression. |
| inputs / outputs | Validated ID to borrowed expression. |
| invariants | The compiler accepts a fresh BoundSql internally, not a caller-mutated DTO. |
| ownership | Borrows compiler-call binder state. |
| failure | Private admitted index precondition. |
| cost | Constant indexed read. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0020

[Lines 147–149](../../../../../src/frontend/sql_rows.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L147-L149:sha256:1e698f3ca989e91badcd93f94760ff29d12b1c48d9d6955cfecc04311e467e3e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict USING ownership and dependencies to its transfer operand. |
| inputs / outputs | Bound opcode to effective argument count. |
| invariants | USING transfers the left operand; its separately bound equality remains mandatory. |
| ownership | Reads immutable bound arguments. |
| failure | Private checked opcode arity. |
| cost | Constant opcode test; no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0021

[Lines 150–179](../../../../../src/frontend/sql_rows.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L150-L179:sha256:d797d8a93cb15a2308f0fa23cde26a3ebc03e3d8c27d0c63e05e5a1d67f68240
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Analyze trusted topological expressions once. |
| inputs / outputs | Assign effective occurrence owner, physical-column alias, known value; fold constants. |
| invariants | USING reads only its left value after separate mandatory equality. Cast aliasing is safe only for binder-admitted representation-preserving nodes. Every physical source column has a bound leaf. |
| ownership | Folded string values borrow BoundSql/options until freeze. |
| failure | Non-topological effective arguments give rows_contract; scalar contract faults propagate. |
| cost | O(expressions + effective argument visits + actual constant comparisons). |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/bind.cpp §L207-241,398-400,433-442](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/bind.cpp), [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_scalar.hpp §L38-86](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_scalar.hpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0022

[Lines 180–239](../../../../../src/frontend/sql_rows.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L180-L239:sha256:da8a648d46b1a0dbb24df85a9460639b3cbb24f6af647d5978ec2aa0c914ee47
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract unconditional AND/equality guards. |
| inputs / outputs | Flatten conjunctions; union direct columns; collect known present column constants; ordinary equality to NULL marks contradiction. |
| invariants | Only unconditional equalities may merge classes; no OR-derived merge. Snapshot marks local equalities live too; F1 proposes live flags only across owners. Local-only equality is enforced by guards without a hidden native join field; cross-occurrence equalities retain their shared class. |
| ownership | Pending/constants vectors are cold scratch. |
| failure | Work/allocation failures abort compilation. |
| cost | O(conjunct visits + union work); scalar byte comparisons occur later. |
| Design | [build/verification/w05-sql-rows-human-review-v1/README.md §F1](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_scalar.hpp §L68-80](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_scalar.hpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

```text
if (operation && (operation->operation == SqlOperator::is_null || operation->operation == SqlOperator::is_not_null)) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract NULL guards and reconcile representative constraints. |
| inputs / outputs | IS NOT NULL sets non-null; IS NULL attaches one dedicated NULL slot; representative flags and constants are merged. |
| invariants | Dedicated NULL slot never aliases the Boolean IS NULL result; incompatible constants or NULL/non-null force contradiction. |
| ownership | NULL slot extends scratch arrays; fixed ids later reference retained initial values. |
| failure | Only resource/contract failures throw; contradictions are retained semantics. |
| cost | O(physical columns + constant assignments) union/find visits, plus comparison widths. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/tests/unit/sql_rows_binding_test.cpp §L68-75](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/tests/unit/sql_rows_binding_test.cpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0023

[Lines 240–263](../../../../../src/frontend/sql_rows.cpp#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L240-L263:sha256:cc46b25aa6cec6d1ee8af74d98b0501d0fd7b206dd4ca3d89532e8ccf3a98654
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Propagate grounding and localize remaining predicates. |
| inputs / outputs | Replace fixed physical aliases; fold now-constant expressions; retain unresolved predicates per effective owner. |
| invariants | Only TRUE constant filters pass; ungrounded multi-occurrence predicates reject. A nonknown expression must have a real owner. |
| ownership | Borrowed constant values remain valid through freezing. |
| failure | Unsupported cross-relation predicate is a diagnostic; resource/scalar faults follow boundary. |
| cost | O(expressions + effective arguments + residual predicates), plus scalar work. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/bind.cpp §L135-155](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/bind.cpp), [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_scalar.hpp §L22-86](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_scalar.hpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0024

[Lines 264–269](../../../../../src/frontend/sql_rows.cpp#L264); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L264-L269:sha256:b1f768d4ccfaa6de7910597fa244b5c770f459c3d53d2ba49a6b262d86333df6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate scalar/presence variables and stable head positions. |
| inputs / outputs | new_pair adds payload and optional Boolean; head deduplicates VariableId; project records encoding fields. |
| invariants | A nullable selected pair contributes both fields; repeated references reuse head positions. |
| ownership | Funded variables/head; draft projection remains cold. |
| failure | Allocation and unsupported type/contract failures propagate to factory boundary. |
| cost | O(1) vector append amortized; head map lookup O(log head size). |
| Design | [build/verification/w05-sql-rows-human-review-v1/README.md §encoding argument](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0025

[Lines 270–274](../../../../../src/frontend/sql_rows.cpp#L270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L270-L274:sha256:75f936384cb75ef1b42c38e4fd262d5da5a740c2e3194bd1b4dac86fbf922c7d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reuse or append a free-head position. |
| inputs / outputs | Core variable ID to stable head position. |
| invariants | Each varying field appears once in the head even when SQL outputs repeat it. |
| ownership | Cold scan and optional retained metadata append. |
| failure | Allocation failure unwinds the private program. |
| cost | Linear search in current head width; repeated calls can be quadratic in output width, construction only. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0026

[Lines 275–279](../../../../../src/frontend/sql_rows.cpp#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L275-L279:sha256:f2a8997bfa481b620a35a7cb8c2b938e1f374e402607937f88c3d460e76dcb4a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append canonical encoded native fields. |
| inputs / outputs | Pair/expression/type to draft projection entries. |
| invariants | Presence uses Boolean; nullable payload has a canonical missing value; all fields are sorted later. |
| ownership | Copies IDs into cold occurrence workspace. |
| failure | Ordinary workspace growth may throw. |
| cost | One or two descriptor appends, amortized constant plus allocator growth. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0027

[Lines 280–351](../../../../../src/frontend/sql_rows.cpp#L280); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L280-L351:sha256:16baff9dfc7ecf69bd928d0f0321dd4d0383c894a1cee7f30ca1aa39ae2ec488
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build join/output variable and decoder mapping. |
| inputs / outputs | Keep unfixed live classes, then ordered constants/class values/local computed outputs or EXISTS. |
| invariants | Cross-occurrence unfixed equality classes retain join fields; local-only equality needs guards only. Nullable private output pairs enter the full head. Grounded outputs reuse their class fixed slot while preserving each output name/SqlType. |
| ownership | Outputs/names/head are funded; class maps are cold. |
| failure | Cross-relation output rejects; allocation/type faults abort. |
| cost | Cold physical/output traversal, union-find/ordered maps and needed-expression closure; head deduplication can scan quadratically in output width. No runtime constant lookup table is added. |
| Design | [build/verification/w05-sql-rows-human-review-v1/README.md §F1 and encoding argument](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [build/verification/w05-sql-rows-human-review-v1/sources/build/verification/w05-start-v1/design-notes-v1.md §L43-71](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/build/verification/w05-start-v1/design-notes-v1.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

```text
for (std::size_t o = 0; o < occurrences_.size(); ++o) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile source guards, projections, and necessary instruction closure. |
| inputs / outputs | For each occurrence create constant/non-null/local equality guards, sorted variables, and topological dynamic reads/opcodes. |
| invariants | One projection per class per occurrence; same-source aliases stay distinct. Known slots never appear as dynamic targets. Sorting ExpressionIds follows binder topology. |
| ownership | Cold draft metadata becomes retained only in freeze_programs. |
| failure | Nonlocal dependency gives rows_contract; resource/allocation faults abort. |
| cost | O(physical columns + projected-field sort + reached dependency edges/set lookups). |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/bind.cpp §L110-119,381-405](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/bind.cpp), [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows_eval.hpp §L19-62](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows_eval.hpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0028

[Lines 352–399](../../../../../src/frontend/sql_rows.cpp#L352); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L352-L399:sha256:8d057b3e2d72773be5a6349b54d0f37c4d19823cd3b7c932ec43f184e0d3a862
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve complete schema backing and canonicalize enforced UNIQUE keys. |
| inputs / outputs | Count all tables/columns/enforced constraints and publish sorted unique-key columns first. |
| invariants | Untrusted keys are omitted from enforcement descriptors; full source schemas/routes include unused tables. Totals cover later FK appends. |
| ownership | Accounted backing arrays reserved before spans; temporary grouping vectors cold. |
| failure | Allocation/account failure aborts unpublished metadata. |
| cost | O(catalog shape + key sorting); not charged to normalization work. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/catalog/catalog.cpp §L52-110](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/catalog/catalog.cpp), [build/verification/w05-sql-rows-human-review-v1/sources/docs/catalog.md §L106-125](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/docs/catalog.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

```text
const auto* key = std::get_if<ForeignKeyConstraint>(&constraint);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve FK parents and publish source dependency spans. |
| inputs / outputs | Choose enforced parent by source/sorted column set, reorder FK columns positionally, build reverse references, then full schemas/routes. |
| invariants | Matching parent exists after binder catalog validation; reordering follows parent key order; empty keys retain meaning. |
| ownership | All published spans point into previously reserved Data backing; names have separate stable blocks. |
| failure | Missing validated parent yields rows_contract; allocation failure aborts. |
| cost | Parent scan O(F*U*key comparisons); per-FK reorder O(key width squared); remaining publication linear. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/catalog/catalog.cpp §L89-110](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/catalog/catalog.cpp), [build/verification/w05-sql-rows-human-review-v1/README.md §constraint item 1](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0029

[Lines 400–422](../../../../../src/frontend/sql_rows.cpp#L400); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L400-L422:sha256:17307669244cc46485b12ea4123270e3c2c7c5cfba4c8322076d50a67f2e58c0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze draft occurrence instruction lists. |
| inputs / outputs | Precount/reserve all flat arrays, append arguments and instruction spans, then occurrences. |
| invariants | Spans remain stable; instruction order is ascending topological ExpressionId; projection order is VariableId order. |
| ownership | Receiving account owns arrays; temporary drafts do not escape. |
| failure | Allocation failure unwinds unpublished Data. |
| cost | O(total instruction, argument, guard and projection count). |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows.cpp §L328-340](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows.cpp), [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows_eval.hpp §L44-60](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows_eval.hpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0030

[Lines 423–434](../../../../../src/frontend/sql_rows.cpp#L423); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L423-L434:sha256:ea8b8edd43c5d5cc47a910def0975c3d996a3263ee501c9b32f3dacd25df2cf7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drop unread folded constant values before owning their bytes. |
| inputs / outputs | Published immutable instruction/decoder IDs mark needed initial slots. |
| invariants | Every guard constant, operation argument, predicate, projected expression and constant output remains; original expression indices do not change. Validation already checked all strings. |
| ownership | One cold bit mask; it is not retained in the program. Removed views own no bytes. freeze_values funds only the remaining present constants. |
| failure | Mask allocation failure unwinds private compilation; valid factory IDs stay within values_. No new catch or partial publication. |
| cost | Linear in expression slots plus metadata references, using one bit per slot; no runtime scan/cache/interning work. These cold visits are separate from selected work_ charges. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-constant-retention-probe-v1/README.md](../../../../../build/verification/w05-rows-constant-retention-probe-v1/README.md) |

## B0031

[Lines 435–438](../../../../../src/frontend/sql_rows.cpp#L435); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L435-L438:sha256:ac4f30c2744d899a4e5bb62fc0a3e3e51cb1b3bcba70dda7563450b9affb95b7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain immutable compiler inputs and allocate private funded Data. |
| inputs / outputs | Account, freshly bound SQL and binding options. |
| invariants | Input references outlive synchronous run; output publication follows complete construction. |
| ownership | References cold inputs; owns one accounted Data control. |
| failure | Partial construction releases funded metadata through RAII. |
| cost | Fixed constructor work and one Data/control allocation; run owns traversal/copy costs. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0032

[Lines 439–484](../../../../../src/frontend/sql_rows.cpp#L439); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L439-L484:sha256:d5555c9ee1661e41c9f964f1f48fe3c1e760dd2dc6220cccfc68ff8dd976164a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile and freeze genuine row SQL, compute the unchanged canonical source key, and optionally retain its exact CBOR. |
| inputs / outputs | Bound SQL, receiving result account and SqlRowsBindOptions -&gt; genuine SqlRowsProgram. |
| invariants | Validates typed parameters, normalizes occurrence/predicate/core metadata, checks retained text and exports validated core. Source SHA always hashes the same canonical SQL/catalog/typed-value signature; only true retain_binding_image copies that image. Selected compiler work remains unchanged. |
| ownership | Result metadata/constants/source and optional image use the receiving account; ordinary signature DOM/CBOR and compiler arrays are temporary cold workspace. |
| failure | Existing normalization/parameter/resource/allocation failures propagate through factory ownership; no catch or fallback is added by the conditional copy. |
| cost | Actual cold normalization/schema/freeze/export plus canonical DOM/CBOR/hash; opted-in storage adds O(image bytes) accounted copy, default adds no image allocation. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows_value.hpp §L50-64](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows_value.hpp), [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/bind.cpp §L550-567](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/bind.cpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

```text
io::Json signature{{"family", "CROWN-SQL-ROWS;1"}, {"source", bound_.source}, {"catalog", io::write_catalog_payload(bound_.catalog)}};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind exact source identity and validate cold core shape. |
| inputs / outputs | Encode family, exact SQL, complete catalog and typed parameter values as CBOR; SHA-256; export/validate core. |
| invariants | CBOR preserves opaque byte strings; key is conservative source identity, not semantic canonicalization. Validation does not recognize free-connexity. |
| ownership | JSON/encoded bytes/export are cold temporary allocations; fixed digest retained. |
| failure | Serialization/export/allocation failures abort unpublished result. |
| cost | O(serialized input bytes + core validation), outside work_ charges. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/io/catalog.cpp §L122-153](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/io/catalog.cpp), [build/verification/w05-sql-rows-human-review-v1/sources/src/ir/model.cpp §L75-113](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/ir/model.cpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0033

[Lines 485–487](../../../../../src/frontend/sql_rows.cpp#L485); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L485-L487:sha256:c4992b56c86bac4eff299a3f71382697416f38beddb6139a217c634c53eba93e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ends the private SqlRowsCompiler definition and detail namespace; public handle accessors and bind factory functions follow. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [docs/code_specs/files/src/frontend/sql_rows.cpp.md](sql_rows.cpp.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0034

[Lines 488–491](../../../../../src/frontend/sql_rows.cpp#L488); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L488-L491:sha256:8c8c461ea711d78b0dbd68c93f6025023e416ce3f24cc59c71d85d039ba2b4c1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Access immutable Data without exporting ownership. |
| inputs / outputs | Validate nonempty handle; return scalar properties and borrowed spans/text/account. |
| invariants | Caller keeps a program owner live for every borrowed access. |
| ownership | No allocation on successful accessor. |
| failure | Empty program throws invalid_sql_rows_program. |
| cost | O(1). |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/include/crown/frontend/sql_rows.hpp §L85-119](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/include/crown/frontend/sql_rows.hpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0035

[Lines 492–492](../../../../../src/frontend/sql_rows.cpp#L492); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L492-L492:sha256:69d13f5f41a3f24be1b05d3e527910452874a13500c99371d23ea8a16401db98
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the allocation authority. |
| inputs / outputs | Borrowed existing account. |
| invariants | Reads actual immutable program state without exporting a DTO or recomputing validation. |
| ownership | Reference borrows the program. |
| failure | Empty handle rejects through data(); borrowed getters are lvalue-only. |
| cost | Constant descriptor/scalar read, no allocation or traversal. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0036

[Lines 493–493](../../../../../src/frontend/sql_rows.cpp#L493); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L493-L493:sha256:9234cc368c9a938bda0b74ecffb6cccf70894d5b3aef953f3e0d909ba7037721
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect exact admitted SQL bytes. |
| inputs / outputs | Borrowed source text. |
| invariants | Reads actual immutable program state without exporting a DTO or recomputing validation. |
| ownership | Text belongs to retained AccountedText. |
| failure | Empty handle rejects through data(); borrowed getters are lvalue-only. |
| cost | Constant descriptor/scalar read, no allocation or traversal. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0037

[Lines 494–494](../../../../../src/frontend/sql_rows.cpp#L494); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L494-L494:sha256:b1dd384385936c2210ee8dc96859f2cc85eb48c7260bdaa54b3c11bbce4cd619
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained exact source/catalog/typed-parameter CBOR image. |
| inputs / outputs | This nonempty SqlRowsProgram const lvalue -&gt; data().binding.view() as string_view; empty when binding did not opt into retention. |
| invariants | Returns the named retained value; this accessor performs no preparation, publication or revalidation. |
| ownership | The view borrows immutable AccountedText bytes; keep its backing program alive and do not move away the sole owning handle. |
| failure | data() rejects an empty handle with the existing program contract Error; this getter allocates, binds and copies nothing. |
| cost | O(1) checked pointer/length access; no byte traversal, hash, receiving allocation or compiler/freeze work. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0038

[Lines 495–495](../../../../../src/frontend/sql_rows.cpp#L495); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L495-L495:sha256:1c490c9566d2d474b8f5babf9d4f548f26b8cabdb8a711a5577bbdbadd69bff8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect conservative source identity. |
| inputs / outputs | Borrowed 64-byte hexadecimal key. |
| invariants | Reads actual immutable program state without exporting a DTO or recomputing validation. |
| ownership | Array belongs to immutable Data; view is not null-terminated. |
| failure | Empty handle rejects through data(); borrowed getters are lvalue-only. |
| cost | Constant descriptor/scalar read, no allocation or traversal. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0039

[Lines 496–496](../../../../../src/frontend/sql_rows.cpp#L496); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L496-L496:sha256:f5ad753a26b051dac0dc24d4219d2cea175bec1eef630cd239a94aeb3fc5cc48
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect bag versus DISTINCT output semantics. |
| inputs / outputs | SqlSemantics value. |
| invariants | Reads actual immutable program state without exporting a DTO or recomputing validation. |
| ownership | Scalar copy only. |
| failure | Empty handle rejects through data(); borrowed getters are lvalue-only. |
| cost | Constant descriptor/scalar read, no allocation or traversal. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0040

[Lines 497–497](../../../../../src/frontend/sql_rows.cpp#L497); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L497-L497:sha256:e6a4eb314d4053b7e6340e1e5ada74c915c5b4492beaa3d161e018efe60c9cff
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect ordinary rows versus whole-result EXISTS. |
| inputs / outputs | SqlWrapper value. |
| invariants | Reads actual immutable program state without exporting a DTO or recomputing validation. |
| ownership | Scalar copy only. |
| failure | Empty handle rejects through data(); borrowed getters are lvalue-only. |
| cost | Constant descriptor/scalar read, no allocation or traversal. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0041

[Lines 498–498](../../../../../src/frontend/sql_rows.cpp#L498); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L498-L498:sha256:f3533c8027f3a00641d05a973fa5f0eeecce2f886fb03a27577939920d97cde5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect a proved constant-false route. |
| inputs / outputs | Boolean value. |
| invariants | Reads actual immutable program state without exporting a DTO or recomputing validation. |
| ownership | Scalar copy only. |
| failure | Empty handle rejects through data(); borrowed getters are lvalue-only. |
| cost | Constant descriptor/scalar read, no allocation or traversal. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0042

[Lines 499–499](../../../../../src/frontend/sql_rows.cpp#L499); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L499-L499:sha256:60583fa7a6f265cdb268536c4e7d072cb75523802a1d28a5d6c1f5feb24a38ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report counted compiler visits. |
| inputs / outputs | Accumulated logical work. |
| invariants | Reads actual immutable program state without exporting a DTO or recomputing validation. |
| ownership | Scalar copy only; not total CPU/byte cost. |
| failure | Empty handle rejects through data(); borrowed getters are lvalue-only. |
| cost | Constant descriptor/scalar read, no allocation or traversal. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0043

[Lines 500–500](../../../../../src/frontend/sql_rows.cpp#L500); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L500-L500:sha256:c1d0b0d8f5bb5e2c469bf6f83f7a3966341a974f1d000e59f61e29ba21bd8800
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow full physical source metadata. |
| inputs / outputs | Immutable source span. |
| invariants | Reads actual immutable program state without exporting a DTO or recomputing validation. |
| ownership | Span borrows Data. |
| failure | Empty handle rejects through data(); borrowed getters are lvalue-only. |
| cost | Constant descriptor/scalar read, no allocation or traversal. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0044

[Lines 501–501](../../../../../src/frontend/sql_rows.cpp#L501); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L501-L501:sha256:66467b385260833427a12dbd53d5fa413ed4d989402e9efda54ca7f1d8851a0f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow enforced constraint metadata. |
| inputs / outputs | Immutable constraint span. |
| invariants | Reads actual immutable program state without exporting a DTO or recomputing validation. |
| ownership | Span/nested spans borrow Data. |
| failure | Empty handle rejects through data(); borrowed getters are lvalue-only. |
| cost | Constant descriptor/scalar read, no allocation or traversal. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0045

[Lines 502–502](../../../../../src/frontend/sql_rows.cpp#L502); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L502-L502:sha256:3cb7cbf3a2cfb1c896a5add7b337117c867b5581062cabeead7d08c787623016
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow alias-local executable metadata. |
| inputs / outputs | Immutable occurrence span. |
| invariants | Reads actual immutable program state without exporting a DTO or recomputing validation. |
| ownership | Span/instructions borrow Data. |
| failure | Empty handle rejects through data(); borrowed getters are lvalue-only. |
| cost | Constant descriptor/scalar read, no allocation or traversal. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0046

[Lines 503–503](../../../../../src/frontend/sql_rows.cpp#L503); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L503-L503:sha256:48538d72699d5ef534d8b186f3653483c41feb38ff7c8b1063610956feafa820
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow ordered SQL output schema/decoders. |
| inputs / outputs | Immutable output span. |
| invariants | Reads actual immutable program state without exporting a DTO or recomputing validation. |
| ownership | Names/spans/constants borrow Data. |
| failure | Empty handle rejects through data(); borrowed getters are lvalue-only. |
| cost | Constant descriptor/scalar read, no allocation or traversal. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0047

[Lines 504–504](../../../../../src/frontend/sql_rows.cpp#L504); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L504-L504:sha256:e885d8a452b25b7eff4be501897fdfc1007bb78fa7a1c86c58ee8aa33ffecd00
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow constant slots and dynamic placeholders. |
| inputs / outputs | Immutable optional scalar cells. |
| invariants | Reads actual immutable program state without exporting a DTO or recomputing validation. |
| ownership | Present text bytes belong to literal backing; dynamic placeholders are NULL. |
| failure | Empty handle rejects through data(); borrowed getters are lvalue-only. |
| cost | Constant descriptor/scalar read, no allocation or traversal. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0049

[Lines 506–520](../../../../../src/frontend/sql_rows.cpp#L506); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L506-L520:sha256:c4ab233abcb484ef17cf5c24ea3f2268eb6c900560c3cf37ddbb8b88f390dc52
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export actual derived schema and query for planner choice. |
| inputs / outputs | One generated table/atom per occurrence, non-null typed columns in projection order, ordered head and contradiction. |
| invariants | No source constraint/statistic is promoted into core authority; nullable SQL is already encoded. Query validation checks shape only. Each derived variable term is constructed directly in variant alternative 0, without a temporary nested variant. |
| ownership | Fresh standard Catalog/Query belongs to caller. |
| failure | Allocation or validate errors propagate. |
| cost | O(exported shape) allocations and validation; explicitly cold. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/ir/model.cpp §L75-113](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/ir/model.cpp), [build/verification/w05-sql-rows-human-review-v1/README.md §encoding argument](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0051

[Lines 522–568](../../../../../src/frontend/sql_rows.cpp#L522); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L522-L568:sha256:98504fe0ba4106cec489eead59e80f57800c2dcbd91e61e9db35f40874dcc335
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share same-account immutable metadata or copy and rebase it into a genuine receiving account. |
| inputs / outputs | Valid MemoryAccount and genuine source SqlRowsProgram -&gt; frozen program retaining source key/work/semantics and metadata. |
| invariants | Same account aliases; cross-account copies all backing arrays/text/constants and rebases spans/names. An empty binding image stays empty without image allocation; retained bytes copy exactly. No new source hash is computed. |
| ownership | Source stays unchanged; returned Data/backing uses receiver. Same-account return shares the existing immutable owner. |
| failure | Invalid account raises MemoryFailure(contract); empty source/getter and allocation failures propagate with local RAII cleanup. |
| cost | O(1) same-account share; cross-account linear metadata/name/constant and opted-in image copies with actual receiving allocations; no SQL rebind or native execution. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/docs/query_memory.md](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/docs/query_memory.md), [build/verification/w05-sql-rows-human-review-v1/sources/include/crown/storage/accounted_row.hpp §L78-108](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/include/crown/storage/accounted_row.hpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

```text
for (auto& column : out->columns) column.name = out->name(column.name);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebase clone names and every nested span before publication. |
| inputs / outputs | Copy names into destination text blocks; rebase source, constraint, operation and occurrence views; return immutable handle. |
| invariants | All nonempty old spans have matching copied backing; offsets/counts preserved; initial strings were separately frozen. |
| ownership | No destination view borrows source after successful return. |
| failure | Name-copy allocation failure destroys unpublished clone. |
| cost | O(names + descriptors + name bytes); pointer rebasing O(1) per span. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/include/crown/resource/text.hpp §L21-46](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/include/crown/resource/text.hpp), [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows.cpp §L35-39](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/sql_rows.cpp), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0053

[Lines 570–580](../../../../../src/frontend/sql_rows.cpp#L570); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L570-L580:sha256:e137d925a308344e43a33745b1a1e6c2bf47792fc64a730881cc4db9c5a8fbf9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve binder boundary and translate compiler Error once. |
| inputs / outputs | bind_sql produces diagnostic or owned BoundSql; compiler Error becomes parameters/normalization diagnostic; default factory creates cap. |
| invariants | Invalid account rejects before binding; no broad catch/retry/rollback framework. Existing binder has different allocation diagnostics. |
| ownership | BoundSql and failed compiler state release before return/propagation. |
| failure | MemoryFailure/bad_alloc outside binder translation and IndexFailure are not caught here. |
| cost | Cold factory only; diagnostics can allocate. |
| Design | [build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/bind.cpp §L550-567](../../../../../build/verification/w05-sql-rows-human-review-v1/sources/src/frontend/bind.cpp), [build/verification/w05-sql-rows-human-review-v1/README.md §F2](../../../../../build/verification/w05-sql-rows-human-review-v1/README.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md) |

## B0054

[Lines 581–583](../../../../../src/frontend/sql_rows.cpp#L581); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L581-L583:sha256:8e6a331f009d46bcf4b83c28c9f5a6169c767f5d5dd8e17c3c566d2737349855
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one explicit standalone compiler account. |
| inputs / outputs | Source/catalog/options to program or binding diagnostic. |
| invariants | This standalone entry creates the requested finite cap once; _into preserves supplied authority. |
| ownership | Successful program retains its compiler account. |
| failure | Account/compilation failure propagates; binder and compiler diagnostic boundaries remain explicit. |
| cost | One account construction plus the complete cold bind/compile operation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0055

[Lines 584–584](../../../../../src/frontend/sql_rows.cpp#L584); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L584-L584:sha256:2fc33ff8830b8cd06d6971e8e31b29a8803f152d87e09a3fc4092b3efecdac93
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::frontend at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [docs/code_specs/files/src/frontend/sql_rows.cpp.md](sql_rows.cpp.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |
