# `src/runtime/difference.cpp` — block usage map

[Source](../../../../../src/runtime/difference.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Recompute both positive operands from one funded source image, consolidate set/bag residuals and publish prepared endpoint counts atomically.

Snapshot SHA-256: `7c2200d3f158985a26328118be7827cdeef95a9f336aa806937fc5347346ceb8`. 274 lines partitioned into 47 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [difference](../../../subsystem_contracts.md#difference). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/difference.md](../../../../difference.md), [docs/source_images.md](../../../../source_images.md), [docs/annotations.md](../../../../annotations.md), [Refactor.md](../../../../../Refactor.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/runtime/difference.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 11–14](../../../../../src/runtime/difference.cpp#L11) | Callable definition: template&lt;class T&gt; auto allocator(const resource::MemoryAccount& account, resource::MemoryPurpose purpose = resource::MemoryPurpos… | calls ; returns cq_recompute::allocator&lt;T&gt;(account, purpose) · [reviewed contract](#b0002) |
| [B0003 · 15–17](../../../../../src/runtime/difference.cpp#L15) | Callable definition: template&lt;class T&gt; OutputVector&lt;T&gt; output(const resource::MemoryAccount& account) | calls ; returns OutputVector&lt;T&gt;(resource::OwnerAllocator&lt;T&gt;(account, resource::MemoryPurpose::output_buffer, memory… · [reviewed contract](#b0003) |
| [B0004 · 18–20](../../../../../src/runtime/difference.cpp#L18) | Callable definition: void require(bool condition, const char* message) | calls Error; guard void require(bool condition, const char* message) { · [reviewed contract](#b0004) |
| [B0005 · 21–23](../../../../../src/runtime/difference.cpp#L21) | declares types or opens a type body. |  · [reviewed contract](#b0005) |
| [B0006 · 24–27](../../../../../src/runtime/difference.cpp#L24) | Callable definition: void take(std::uint64_t amount = 1) | calls Error · [reviewed contract](#b0006) |
| [B0007 · 28–28](../../../../../src/runtime/difference.cpp#L28) | Callable definition: \[\[nodiscard\]\] std::uint64_t remaining() const noexcept | calls ; returns limit - metrics.work · [reviewed contract](#b0007) |
| [B0008 · 29–34](../../../../../src/runtime/difference.cpp#L29) | Callable definition: void scalar(const storage::ScalarView& value) | calls take, size, parts · [reviewed contract](#b0008) |
| [B0009 · 35–35](../../../../../src/runtime/difference.cpp#L35) | Callable definition: void payload(storage::RowView row) | calls cells, scalar; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 36–38](../../../../../src/runtime/difference.cpp#L36) | Callable definition: std::strong_ordering compare(const storage::ScalarView& a, const storage::ScalarView& b) | calls scalar; returns a &lt;=&gt; b · [reviewed contract](#b0010) |
| [B0011 · 39–44](../../../../../src/runtime/difference.cpp#L39) | Callable definition: std::strong_ordering compare(storage::RowView a, storage::RowView b) | calls take, std::min, size; returns order; a.size() &lt;=&gt; b.size(); 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 45–49](../../../../../src/runtime/difference.cpp#L45) | Callable definition: std::strong_ordering compare(const storage::Tuple& a, const storage::Tuple& b) | calls values, native_view, require, has_value; guard require(left.has_value() && right.has_value(), "difference result lost native ownership");; returns compare(*left, *right) · [reviewed contract](#b0012) |
| [B0013 · 50–50](../../../../../src/runtime/difference.cpp#L50) | Closes surrounding scope/type. |  · [reviewed contract](#b0013) |
| [B0014 · 51–57](../../../../../src/runtime/difference.cpp#L51) | Type/record definition: struct RowLess | returns budget-&gt;compare(a.view(), b.view()) &lt; 0; budget-&gt;compare(a.view(), b) &lt; 0 · [reviewed contract](#b0014) |
| [B0015 · 58–62](../../../../../src/runtime/difference.cpp#L58) | Type/record definition: struct Writing |  · [reviewed contract](#b0015) |
| [B0016 · 63–67](../../../../../src/runtime/difference.cpp#L63) | Callable definition: Multiplicity residual(Mode mode, Multiplicity left, Multiplicity right, const annotations::MultiplicityPolicy& policy) | calls present, remove; returns {left.present() && !right.present() ? 1U : 0U}; left &gt; right ? policy.remove(left, right) : Multipl… · [reviewed contract](#b0016) |
| [B0017 · 68–71](../../../../../src/runtime/difference.cpp#L68) | Explanatory comments or spacing. | source comment (unverified): // One union-key scratch map retains both complete operand counts. A key can · [reviewed contract](#b0017) |
| [B0018 · 72–113](../../../../../src/runtime/difference.cpp#L72) | Callable definition: Vector&lt;Entry&gt; recompute(const Binding& binding, const physical::SourceImage& image, Limits limits, Budget& budget) | calls account, profile, policy, multiplicity_limit; returns mode == Mode::bag_except_all \|\| !query.head.empty(); result; growth copy_of, emplace, push_back; 1 loop sites; source comment (unverified): // One union-key scratch map retains both complete operand counts. A key can · [reviewed contract](#b0018) |
| [B0019 · 114–132](../../../../../src/runtime/difference.cpp#L114) | Callable definition: void replacements(const Vector&lt;Entry&gt;& before, const Vector&lt;Entry&gt;& after, OutputVector&lt;Change&gt;& changes, Budget& budget) | calls take, push_back, present, size; growth push_back; 3 loop sites · [reviewed contract](#b0019) |
| [B0020 · 133–143](../../../../../src/runtime/difference.cpp#L133) | Callable definition: std::pair&lt;std::optional&lt;std::uint64_t&gt;, std::optional&lt;std::uint64_t&gt;&gt; products( const program::Query& query, std::span&lt;const std:… | calls reset; returns {product, prefix}; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 144–145](../../../../../src/runtime/difference.cpp#L144) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0021) |
| [B0022 · 146–158](../../../../../src/runtime/difference.cpp#L146) | Type/record definition: struct Binding::Data |  · [reviewed contract](#b0022) |
| [B0023 · 159–162](../../../../../src/runtime/difference.cpp#L159) | Callable definition: const Binding::Data& Binding::data() const | calls Error; returns *data_ · [reviewed contract](#b0023) |
| [B0024 · 163–163](../../../../../src/runtime/difference.cpp#L163) | Callable definition: const program::Query& Binding::left() const & | calls data; returns data().left.query · [reviewed contract](#b0024) |
| [B0025 · 164–164](../../../../../src/runtime/difference.cpp#L164) | Callable definition: const program::Query& Binding::right() const & | calls data; returns data().right.query · [reviewed contract](#b0025) |
| [B0026 · 165–165](../../../../../src/runtime/difference.cpp#L165) | Callable definition: const Profile& Binding::profile() const & | calls data; returns data().profile · [reviewed contract](#b0026) |
| [B0027 · 166–166](../../../../../src/runtime/difference.cpp#L166) | Callable definition: const CompiledProgram& Binding::sources() const & | calls data; returns data().sources · [reviewed contract](#b0027) |
| [B0028 · 167–167](../../../../../src/runtime/difference.cpp#L167) | Callable definition: const storage::AccountedLayout& Binding::result_layout() const & | calls data; returns data().left.layout · [reviewed contract](#b0028) |
| [B0029 · 168–168](../../../../../src/runtime/difference.cpp#L168) | Callable definition: const resource::MemoryAccount& Binding::account() const & | calls data; returns data().account · [reviewed contract](#b0029) |
| [B0030 · 169–169](../../../../../src/runtime/difference.cpp#L169) | Callable definition: std::uint64_t Binding::multiplicity_limit() const | calls data; returns data().limit · [reviewed contract](#b0030) |
| [B0031 · 170–179](../../../../../src/runtime/difference.cpp#L170) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0031) |
| [B0032 · 180–191](../../../../../src/runtime/difference.cpp#L180) | Callable definition: Data(PhysicalRuntime source, const planner::difference::Plan& plan, const Options& options, Budget& budget) : account(source.plan… | calls account, plan, sources, std::move; growth make_accounted_shared; 2 loop sites · [reviewed contract](#b0032) |
| [B0033 · 192–194](../../../../../src/runtime/difference.cpp#L192) | Callable definition: void readable() const | calls ready, Error · [reviewed contract](#b0033) |
| [B0034 · 195–195](../../../../../src/runtime/difference.cpp#L195) | Closes surrounding scope/type. |  · [reviewed contract](#b0034) |
| [B0035 · 196–213](../../../../../src/runtime/difference.cpp#L196) | Callable definition: Runtime::Runtime(const planner::difference::Plan& plan, Options options) | calls policy, take, sources, source_only; returns {!query.contradiction && query.atoms.empty() ? 1U : 0U}; growth make_accounted_unique, push_back · [reviewed contract](#b0035) |
| [B0036 · 214–216](../../../../../src/runtime/difference.cpp#L214) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0036) |
| [B0037 · 217–220](../../../../../src/runtime/difference.cpp#L217) | Callable definition: Runtime::Data& Runtime::data() const | calls Error; returns *data_ · [reviewed contract](#b0037) |
| [B0038 · 221–221](../../../../../src/runtime/difference.cpp#L221) | Callable definition: const Binding& Runtime::binding() const & | calls data; returns data().binding · [reviewed contract](#b0038) |
| [B0039 · 222–222](../../../../../src/runtime/difference.cpp#L222) | Callable definition: const resource::MemoryAccount& Runtime::account() const & | calls data; returns data().account · [reviewed contract](#b0039) |
| [B0040 · 223–223](../../../../../src/runtime/difference.cpp#L223) | Callable definition: bool Runtime::ready() const | calls data, ready; returns !d.busy && d.sources.ready() · [reviewed contract](#b0040) |
| [B0041 · 224–224](../../../../../src/runtime/difference.cpp#L224) | Callable definition: std::uint64_t Runtime::sequence() const | calls data, readable, sequence; returns d.sources.sequence() · [reviewed contract](#b0041) |
| [B0042 · 225–225](../../../../../src/runtime/difference.cpp#L225) | Callable definition: bool Runtime::has_answer() const | calls data, readable, empty; returns !d.rows.empty() · [reviewed contract](#b0042) |
| [B0043 · 226–250](../../../../../src/runtime/difference.cpp#L226) | Callable definition: Epoch Runtime::apply(const PhysicalSetUpdate& update) | calls data, readable, writing, take; guard } else { require(count != 0, "difference table cardinality underflow"); --count; }; returns {std::move(input), d.binding, std::move(changes), metrics}; growth insert; 1 loop sites; source comment (unverified): // The one image, all visitors/maps and every fallible replacement allocation · [reviewed contract](#b0043) |
| [B0044 · 251–257](../../../../../src/runtime/difference.cpp#L251) | Callable definition: Snapshot Runtime::snapshot(Limits limits) const | calls data, readable, writing, take; returns {d.sources.sequence(), d.binding, std::move(rows), metrics}; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0044) |
| [B0045 · 258–268](../../../../../src/runtime/difference.cpp#L258) | Callable definition: Explain Runtime::explain() const | calls data, readable, writing, tables; returns {d.binding.profile(), std::move(tables), static_cast&lt;std::uint64_t&gt;(d.rows.size()), d.binding.multi…; 1 loop sites · [reviewed contract](#b0045) |
| [B0046 · 269–271](../../../../../src/runtime/difference.cpp#L269) | Callable definition: Database Runtime::source_snapshot() const | calls data, readable, writing, snapshot; returns d.sources.snapshot().physical · [reviewed contract](#b0046) |
| [B0047 · 272–274](../../../../../src/runtime/difference.cpp#L272) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;Epoch&gt;);; source comment (unverified): // namespace crown::runtime::difference · [reviewed contract](#b0047) |

## B0001

[Lines 1–10](../../../../../src/runtime/difference.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:1b42855b47c3c1bde6b8e5560c241fd281dc20069f4cbc58a3340c9e29ce13f0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up private exact difference computation with the shared CQ visitor. |
| inputs / outputs | Includes public difference, common frozen-query/traversal support and ordered map/type traits; aliases common Vector. |
| invariants | Only this translation unit implements residual counts and endpoint replacement semantics; helper does not own publication. |
| ownership | Original support_node attribution is used for retained state, scratch and output payloads. |
| failure | Includes/aliases add no executable retry or failure translation. |
| cost | Compile-time setup; concrete container allocation/cleanup costs occur at use. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp) |

## B0002

[Lines 11–14](../../../../../src/runtime/difference.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L14:sha256:281eba130a329f55bd39411820fc487480a9aead0799382e109f67c593ebc4ed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the common original-account allocator for a selected memory purpose. |
| inputs / outputs | MemoryAccount and optional purpose yield typed MemoryAllocator. |
| invariants | No replacement account or budget refill is created for either operand. |
| ownership | Returned allocator shares original source authority and allocates no payload yet. |
| failure | Existing resource contract handles invalid allocation authority. |
| cost | Fixed allocator-handle work; subsequent vector/map capacities are actually funded. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp) |

## B0003

[Lines 15–17](../../../../../src/runtime/difference.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L17:sha256:d623ad2e3158e4e007135a70b7217f92bcb93901a9591d658e420658c0367d1a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty transferable funded output array. |
| inputs / outputs | Original account produces OutputVector&lt;T&gt; with output_buffer OwnerAllocator. |
| invariants | Array element ownership can outlive Runtime without introducing another source owner. |
| ownership | Capacity uses original account; Tuple/Binding elements share immutable existing native owners. |
| failure | Future growth may refuse through original finite allocation authority. |
| cost | Fixed empty-vector setup, followed by actual amortized growth, element and cleanup costs. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0004

[Lines 18–20](../../../../../src/runtime/difference.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L20:sha256:3cc09a5b5e9111ffa24787e74165dfaeddd006e6c6f9df75f3fb53cf94e4c7f4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject impossible retained-result/cardinality states with a direct diagnostic. |
| inputs / outputs | Boolean premise and static message return normally or throw difference_invariant. |
| invariants | This is a local contract check, not a rollback/retry framework. |
| ownership | Arguments borrow caller state; no successful owner transfer. |
| failure | False throws before the caller continues. |
| cost | One branch on success; exceptional diagnostic cost is not a primitive performance guarantee. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0005

[Lines 21–23](../../../../../src/runtime/difference.cpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L23:sha256:5995e1bcb07e5444f7d7c80fd1d3b8e93ef00eb8e6157ef620ceafc6a8e529b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold one cumulative exact-operation work balance and diagnostics. |
| inputs / outputs | Budget borrows Metrics and stores the caller limit. |
| invariants | metrics.work begins at zero and never exceeds limit; both metadata imports or both update queries share it. |
| ownership | Only local ordered scratch comparators borrow this stack Budget; persistent state is a sorted vector. |
| failure | Exhaustion unwinds private work and existing source pending token; no replenishment occurs. |
| cost | Fixed state; selected units conservatively track fields/bytes rather than elapsed time. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0006

[Lines 24–27](../../../../../src/runtime/difference.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L27:sha256:86b07876a03fe59cc3ce3072ab4563f29819e2478c313620282df8a998752e69
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit selected work before adding to the cumulative balance. |
| inputs / outputs | Amount defaults to one; checks remaining and increments metrics.work. |
| invariants | Maintained work&lt;=limit makes subtraction and addition nonwrapping. |
| ownership | Only private operation diagnostics mutate. |
| failure | Insufficient remaining work throws difference_work_limit before increment. |
| cost | Fixed integer check/add independent of amount. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0007

[Lines 28–28](../../../../../src/runtime/difference.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L28:sha256:b03189754ae9512b96e66ce82e6f2711fece2488455bf96a0b1892f548d35e77
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose unconsumed work for the one source image admission. |
| inputs / outputs | Returns limit-work without creating or consuming a new grant. |
| invariants | Successful capture actual image.work is charged once to this same Budget. |
| ownership | Scalar return holds no source lease or account owner. |
| failure | Noexcept under maintained balance invariant. |
| cost | One subtraction. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0008

[Lines 29–34](../../../../../src/runtime/difference.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L34:sha256:8cd12815780f3c35569882bf387122b49940cfb865cb504ee741f44353626dd2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a native scalar field and its conservative string/decimal extent. |
| inputs / outputs | ScalarView increases total work, scalar_fields and scalar_bytes. |
| invariants | Admission precedes scalar comparison or payload retention; Decimal remains exact native representation. |
| ownership | Borrowed values remain owned by image/frozen constants/accounted keys/tuples during the call. |
| failure | Extent refusal can follow field admission; units already consumed are not refunded inside the failed operation. |
| cost | Fixed tag/length inspection plus admitted bytes; actual comparison/copy and allocator costs remain real. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0009

[Lines 35–35](../../../../../src/runtime/difference.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L35:sha256:980e3b7a6d22104439239ad410c3da3356191861dddb917e49aa6a334c6e6fca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit all projected row payload fields before owning retention. |
| inputs / outputs | Borrowed RowView delegates each field to scalar(). |
| invariants | One shared balance covers the entire row and both operands. |
| ownership | No payload is copied or retained by this admission pass itself. |
| failure | Work refusal stops before following AccountedRow/Tuple retention. |
| cost | O(fields+admitted string/decimal extents). |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0010

[Lines 36–38](../../../../../src/runtime/difference.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L38:sha256:6ca20360bec320fc77bff3189a1b18f9276033f8dd90ed7f17afc6cf02febcd6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two exact native scalar values after field/byte admission. |
| inputs / outputs | Two ScalarViews produce strong ordering. |
| invariants | Cold positional ScalarType compatibility establishes the comparable domain, without decimal coercion or floating point. |
| ownership | Borrowed operands remain under live native owners. |
| failure | Work refusal precedes actual ordering; no committed answer changes. |
| cost | Two scalar admissions plus actual native string-prefix/bounded numeric comparison. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp) |

## B0011

[Lines 39–44](../../../../../src/runtime/difference.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L44:sha256:19b65f5371b2d3f66539a26034dce0bca25de3fffe647c50058e1f6880ba3d27
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order projected rows lexicographically with explicit examined-field costs. |
| inputs / outputs | RowViews return first nonzero scalar order, otherwise arity order. |
| invariants | One row unit and every examined scalar prefix are admitted; equal full rows compare all head positions including repetition. |
| ownership | No layout coercion, ordinary Row export or payload copy occurs. |
| failure | Work refusal may stop local map or endpoint merge before publication. |
| cost | O(examined fields/bytes) per comparison, multiplied by real ordered-map or merge comparison count. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0012

[Lines 45–49](../../../../../src/runtime/difference.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L49:sha256:4f83b6ff26b63b62895468ef76aecaab3c21393ab96f9b1f9961dfc9d1ad320b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare committed/private result Tuple payloads through native views. |
| inputs / outputs | Two Tuple handles extract native RowViews and delegate exact row ordering. |
| invariants | All result tuples came from the LEFT native result layout. |
| ownership | Tuple handles keep payloads alive beyond temporary adapter objects. |
| failure | Missing native backing throws difference_invariant; delegated work can refuse. |
| cost | Fixed view extraction plus actual scalar-prefix/byte comparison; no legacy DTO export. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0013

[Lines 50–50](../../../../../src/runtime/difference.cpp#L50); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L50:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the local Budget definition. |
| inputs / outputs | Completes cumulative work/comparison helper methods. |
| invariants | Its stack lifetime encloses every local comparator that borrows it. |
| ownership | No persistent container stores the Budget pointer. |
| failure | No executable operation at the delimiter. |
| cost | No runtime work. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0014

[Lines 51–57](../../../../../src/runtime/difference.cpp#L51); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L57:sha256:e5597056ebfc7e1459c61215509a059a6c8907974a18581aeea418316f9e39fc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide transparent budgeted ordering for owned union keys and borrowed probes. |
| inputs / outputs | RowLess compares AccountedRow/RowView combinations through one Budget pointer. |
| invariants | It exists only in recompute local map; ordering is exact same-type scalar lexicographic order. |
| ownership | Map/keys use original account; borrowed Budget outlives all map comparisons and map retirement. |
| failure | Comparison work refusal relies on ordinary private map exception safety and caller pending-token rollback. |
| cost | O(log union keys) ordered comparisons per probe/insertion, each with real scalar-prefix bytes; map allocation/destruction separately applies. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0015

[Lines 58–62](../../../../../src/runtime/difference.cpp#L58); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L62:sha256:d28848b678dbf3f53e1ebaedce6131ea6e70001879e9afe87fa69246093fb7e1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard the whole wrapper read/publication and retirement interval. |
| inputs / outputs | Writing sets borrowed Data.busy on construction and clears at scope exit. |
| invariants | Caller checks readability first; guard is declared before source token/image/new/old result temporaries, so callbacks see busy throughout. |
| ownership | No mutex, new owner, extra journal or source copy is created. |
| failure | Entry/exit flag writes are noexcept; failed operations unwind while guarded. |
| cost | Two scalar writes; calls on a single owner still require serialization. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0016

[Lines 63–67](../../../../../src/runtime/difference.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L67:sha256:cd4f5d4bb29a9e233336c71d36bacada766d19f672a1c5a3240b32817b050daf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact residual support or clipped bag multiplicity. |
| inputs / outputs | Explicit Mode, nonnegative left/right counts and W01 policy return one nonnegative count. |
| invariants | SET gives one iff left present and right absent; BAG gives left-right only when left&gt;right, otherwise zero. |
| ownership | POD input/output counts retain no tuple or annotation payload. |
| failure | Valid admitted Mode/counts avoid underflow; W01 remove preserves bounded domain. |
| cost | Fixed count comparisons/subtraction; no expanded bag rows or signed narrowing. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp) |

## B0017

[Lines 68–71](../../../../../src/runtime/difference.cpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L71:sha256:9f66f274b7ffd27da7aeb96ea79b0a6ee3bd972f9075626e8c58dab6e9b75fc4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the two-operand union-key scratch representation. |
| inputs / outputs | One accounted ordered key map stores independent left/right counts. |
| invariants | Each side has its own rows cap; union may have twice the cap; raw RHS values are compared without LEFT layout conversion. |
| ownership | All keys/counts are local until both operand traversals and residual materialization finish. |
| failure | This comment introduces no separate failure mechanism. |
| cost | Storage is O(left distinct+right distinct) keys plus payloads, before residual tuples coexist. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0018

[Lines 72–113](../../../../../src/runtime/difference.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L72-L113:sha256:f973e427d15f2c4222dd448ccfa55740c508a8ead06d1aed60cf0acdde86735d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute both complete operand counts and materialize positive compressed residuals. |
| inputs / outputs | Actual Binding, one full-source image, limits/shared Budget yield sorted native Entry state. |
| invariants | Shared visitor emits complete physical witnesses before reduction; SET saturates at one and may stop Boolean after first match; BAG counts all witnesses with W01 add; each operand row cap and count overflow applies even when subtraction later cancels; only positive residuals become LEFT-schema tuples. |
| ownership | One original-account union map owns raw projected keys and both counts; RHS-only Decimal keys need no LEFT-schema cast; map and residual payloads coexist temporarily; persistent result vector holds no Budget pointer. |
| failure | Work/key/W01/account/allocation refusal destroys all private map/result state; no source or committed residual changes before caller publication. |
| cost | Both full prefix traversals/terms/bytes, O(log union keys) probes and insert comparisons, O(union keys) residual scan, actual output payload/capacity growth and full cleanup; no count expansion or constant-time ordered operation claim. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp) |

## B0019

[Lines 114–132](../../../../../src/runtime/difference.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L114-L132:sha256:715d39248956673ab0aac348eefa2b601ea4dd8baf4b9dfd5daff3f8bd1f36ce
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact endpoint multiplicity replacements with a sorted merge. |
| inputs / outputs | Sorted before/after Entry vectors append owning Change records and update add/remove/change metrics. |
| invariants | Equal keys emit only when counts differ; removed/added keys have zero after/before; existing-key count changes are neither membership add nor removal. |
| ownership | Change Tuple handles retain old/new payload owners, including deleted keys, with same original account; no payload expansion. |
| failure | Comparison/work/output-capacity refusal happens before source commit and discards partial changes. |
| cost | O(before distinct+after distinct) visits/comparisons with actual head-prefix byte costs plus O(changed keys) funded handle/count capacity. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0020

[Lines 133–143](../../../../../src/runtime/difference.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L143:sha256:a3b2e7f5d69bb8b6dbc0d2ba956f9351b519473b88db5fa303e894982eaed89a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute safe advisory per-operand full-product and prefix-product sums. |
| inputs / outputs | Original query and committed per-table counts return optional uint64 full product and cumulative prefix sum. |
| invariants | Every alias contributes its table factor; overflow yields nullopt; later zero restores exact final zero but cannot recover an earlier overflowing prefix sum. |
| ownership | Only scalar optional accumulators borrow immutable metadata/counts. |
| failure | No arithmetic wrap or allocation; valid metadata guarantees table indexes. |
| cost | O(atom occurrences) scalar arithmetic; selectivity, constants, scalar widths, actual join pruning and emitted keys are not modeled. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0021

[Lines 144–145](../../../../../src/runtime/difference.cpp#L144); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L144-L145:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | End the private difference primitive scope. |
| inputs / outputs | Closes helpers before immutable Binding storage definition. |
| invariants | Local Budget/comparator/map types do not escape as maintained answer state. |
| ownership | No owner transfer at this delimiter. |
| failure | No executable failure. |
| cost | No runtime work. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0022

[Lines 146–158](../../../../../src/runtime/difference.cpp#L146); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L146-L158:sha256:8fddd88cba0c7a85ba27c3a24dbb01aac245a26c5ef51e08ed3175f9c2fd5974
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own both actual original CQs and their semantic execution binding. |
| inputs / outputs | Data stores account, genuine source-only CompiledProgram, actual Profile, W01 limit and two FrozenQuery members. |
| invariants | LEFT alone gets a fresh output ID/layout; RIGHT retains actual terms/head for comparable raw projection without duplicate layout identity or decimal narrowing. |
| ownership | One shared account-funded immutable Data owns all query arrays/text/literals/layout; no ordinary retained pair Query/Catalog or second source runtime. |
| failure | Both metadata imports consume the same constructor Budget; metadata/layout overflow or account/allocation refusal unwinds Data. |
| cost | Sum of two actual metadata/literal imports plus one LEFT layout and temporary metadata scratch, including native allocator/cleanup costs. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp), [include/crown/planner/difference.hpp](../../../../../include/crown/planner/difference.hpp) |

## B0023

[Lines 159–162](../../../../../src/runtime/difference.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L159-L162:sha256:5a9a366c46d8dad4589b374f464a6afb37e6ed905f55dbd18f2bc6e8562b6aba
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a Binding owns immutable pair-query metadata. |
| inputs / outputs | Returns referenced Data or rejects an empty Binding. |
| invariants | Every successful getter borrows the same source/account/pair semantics. |
| ownership | No new Data, row or source lease is created. |
| failure | Empty handle throws difference_state. |
| cost | Fixed shared-pointer presence test/reference return. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0024

[Lines 163–163](../../../../../src/runtime/difference.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L163-L163:sha256:3c088058f18aef2d4856326cca1dc35e40201efd4245e381219927e61a23053a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual frozen LEFT original query. |
| inputs / outputs | Returns Data.left.query by const reference. |
| invariants | Contains original variables/atoms/terms/head/contradiction, not source-only Query{}. |
| ownership | Lvalue Binding keeps all referenced frozen storage alive. |
| failure | Empty Binding throws difference_state. |
| cost | Fixed checked reference access; no query copy. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp) |

## B0025

[Lines 164–164](../../../../../src/runtime/difference.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L164-L164:sha256:04b1d2fabc77c3de0a737d0d8eb1522df14e418a908c655193ba6a0a5b990e89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual frozen RIGHT original query. |
| inputs / outputs | Returns Data.right.query by const reference. |
| invariants | RIGHT terms/head are retained even though only LEFT has an output layout. |
| ownership | Lvalue Binding keeps exact RHS text/literals/arrays alive. |
| failure | Empty Binding throws difference_state. |
| cost | Fixed checked reference access; no metadata copy. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp) |

## B0026

[Lines 165–165](../../../../../src/runtime/difference.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L165-L165:sha256:3822eaceed3298d5156ac03943e71ef0d4b7a3a9e2c5e430f2cfc1a24a442524
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the actual difference mode/arithmetic/profile labels. |
| inputs / outputs | Returns immutable Data.profile. |
| invariants | Class/reason reflect both admitted original operands; no source-only query theorem is substituted. |
| ownership | Binding owns Profile POD/static string labels. |
| failure | Empty Binding throws difference_state. |
| cost | Fixed reference access. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0027

[Lines 166–166](../../../../../src/runtime/difference.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L166-L166:sha256:7ab5c4ea903771eef27ee26b2c217a9dbda88c2f3c29cbff5387a43bb05e0536
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow genuine full-catalog source coordination provenance. |
| inputs / outputs | Returns stored source-only CompiledProgram. |
| invariants | Its own empty CQ supports sources/constraints and is not a combined difference-query certificate. |
| ownership | Binding retains the genuine program and its original account metadata. |
| failure | Empty Binding throws difference_state. |
| cost | Fixed handle reference; no compilation or source snapshot. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0028

[Lines 167–167](../../../../../src/runtime/difference.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L167-L167:sha256:2c16ca2fb92416edc2aca6b7e5f3ff7bf3bcd718e17f47ce265d21c3e5733913
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the LEFT ordered headed native output layout. |
| inputs / outputs | Returns Data.left.layout. |
| invariants | Residual positive keys originate LEFT; RHS-only raw keys are never forced into this schema. |
| ownership | Layout lifetime follows immutable Binding/account ownership. |
| failure | Empty Binding throws difference_state. |
| cost | Fixed reference access; tuple payload checks/copy occur separately. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0029

[Lines 168–168](../../../../../src/runtime/difference.cpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L168-L168:sha256:ed08cb0bb9d2c8102a2c3baa819d09c19c9a978a065c1ad41c77bb8d53f41d02
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the original source memory authority retained by Binding. |
| inputs / outputs | Returns Data.account by const reference. |
| invariants | It is the same account used by both metadata imports, source image, state and outputs. |
| ownership | Caller retains Binding while borrowing account reference. |
| failure | Empty Binding throws difference_state. |
| cost | Fixed reference access; no new grant/account. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0030

[Lines 169–169](../../../../../src/runtime/difference.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L169-L169:sha256:6212afbe7e579a9169141e12e8b882593d4ed99ce17fefa30070b2264cbcafa6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the immutable W01 per-key multiplicity ceiling. |
| inputs / outputs | Returns Data.limit by value. |
| invariants | The positive ceiling applies to each operand count before clipped subtraction. |
| ownership | Scalar return holds no native owner. |
| failure | Empty Binding throws difference_state. |
| cost | Fixed checked scalar access. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0031

[Lines 170–179](../../../../../src/runtime/difference.cpp#L170); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L170-L179:sha256:7b944c7ccf3120e535301100cc2b6ae9ca30648f245a125377a6e93d4cad9825
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the one-source maintained difference state. |
| inputs / outputs | Data retains original account, one PhysicalRuntime, immutable Binding/limits, sorted Entry vector, full table counts, table-use mask and busy flag. |
| invariants | Rows contain only positive compressed residuals; no persistent operand maps, second source copy, ordinary mirror or comparator Budget pointer. |
| ownership | Persistent vectors and source program use the same original account; snapshots/epochs share independent immutable payload ownership. |
| failure | Declarations perform no mutation; constructors establish invariants before facade becomes usable. |
| cost | O(full catalog counts/mask+residual distinct payloads+two query metadata) retained state, plus inherited source state. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0032

[Lines 180–191](../../../../../src/runtime/difference.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L180-L191:sha256:e0ad29cd93ccf111058b381881fbe3529c6bbe4a4bc00a412f616fa5cf5a3e22
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize shared native pair semantics, count tracking and relevant source mask. |
| inputs / outputs | Moves one genuine source runtime; imports both queries with options and shared Budget; initializes full-catalog cardinalities to zero. |
| invariants | used marks union of table occurrences only in noncontradictory operands, so irrelevant or impossible operand changes skip recomputation while still committing source events. |
| ownership | Data/shared Binding/vectors are original-account funded; constructor temporary source move transfers sole source ownership. |
| failure | Budget/account/metadata allocation refusal unwinds all partially built state; no exposed owner advances. |
| cost | Both metadata imports plus O(catalog tables+noncontradictory atom occurrences) selected/scalar writes and allocator costs. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp) |

## B0033

[Lines 192–194](../../../../../src/runtime/difference.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L192-L194:sha256:5f449ed77710959eeffa60b4e117c87800f8050ae3682635430829043189c90c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject observations/reentry during wrapper or native source publication. |
| inputs / outputs | readable() returns only if !busy and sources.ready(). |
| invariants | Reader never sees a source endpoint paired with stale residual/count state. |
| ownership | No source image/read lease/output owner is acquired. |
| failure | Busy/native-pending state throws difference_busy. |
| cost | Fixed flag/readiness checks; this is not thread synchronization. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0034

[Lines 195–195](../../../../../src/runtime/difference.cpp#L195); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L195-L195:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete the maintained Data definition. |
| inputs / outputs | Closes the source/result owner and its direct guard methods. |
| invariants | Only preceding funded members hold persistent state. |
| ownership | No new owner at closure. |
| failure | No executable failure. |
| cost | No runtime work. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0035

[Lines 196–213](../../../../../src/runtime/difference.cpp#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L196-L213:sha256:4b14af4fe007cd9582618620313724996b823ed1a7d9a273483e5a28f53ca6b5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the exact initial residual over one initially empty physical catalog. |
| inputs / outputs | Admitted pair Plan/Options produce one native source owner, frozen actual queries and initial compressed result. |
| invariants | One shared wrapper Budget covers both imports and initial result; noncontradictory empty body has one complete witness, any nonempty body initially has none; per-operand rows cap is checked even if two initial truths cancel; positive W01 limit validated first. |
| ownership | Data/source/Binding/result use original account; Writing spans initial answer allocation and retirement; no source image is needed for known empty tables. |
| failure | Invalid annotation limit, metadata/work/key/layout/account/allocation refusal prevents construction; no partial Runtime is returned. |
| cost | Inherited native source construction, two metadata imports, full-catalog support vectors and at most one nullary residual tuple; no full source scan or two evaluator runtimes. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp) |

## B0036

[Lines 214–216](../../../../../src/runtime/difference.cpp#L214); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L214-L216:sha256:d1c5047f2b9543cf3d82b13faa99266df419fa743ad54b0a7d9addc0e3f60d23
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Default move-only facade lifetime to its accounted Data owner. |
| inputs / outputs | Destructor and noexcept move construction/assignment transfer/release Data. |
| invariants | No copy of sources, queries, count vectors or result payloads is introduced. |
| ownership | Existing shared Binding/tuple/output owners can outlive facade; old Data retirement releases actual source/metadata/state allocations. |
| failure | Moves are noexcept; a moved-from facade is rejected by data(). |
| cost | Handle transfer plus potentially substantial old/final Data destruction; not constant total retirement cost. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0037

[Lines 217–220](../../../../../src/runtime/difference.cpp#L217); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L217-L220:sha256:5008a7a1faad664bcbc9783e878168f68fa9679a11c5b52f1c5644216dc1ddcd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a Runtime still owns its maintained Data. |
| inputs / outputs | Returns mutable internal Data reference for public methods. |
| invariants | A moved-from facade cannot access old state. |
| ownership | No new account/grant/source image is acquired. |
| failure | Missing Data throws difference_state. |
| cost | Fixed unique-owner presence check/reference return. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0038

[Lines 221–221](../../../../../src/runtime/difference.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L221-L221:sha256:e11944276c5c1d1a06faae08d0f1b90872be5309b6298d2bde61708440e03c81
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable actual pair semantics from the live facade. |
| inputs / outputs | Returns maintained Binding reference after data() check. |
| invariants | Binding semantics remain immutable independent of current answer sequence. |
| ownership | Copy Binding if it must survive Runtime teardown; reference alone borrows facade. |
| failure | Moved-from Runtime throws difference_state. |
| cost | Fixed checked reference access. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0039

[Lines 222–222](../../../../../src/runtime/difference.cpp#L222); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L222-L222:sha256:37c4f8acd35c7d8ddcaa7d160f3861eaec3a86e914e16b0700d36317093af787
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the original difference/source memory account. |
| inputs / outputs | Returns Data.account reference. |
| invariants | No per-operand or per-query independent source account is minted. |
| ownership | Reference requires live facade or separately retained account/Binding handle. |
| failure | Moved-from Runtime throws difference_state. |
| cost | Fixed reference access. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0040

[Lines 223–223](../../../../../src/runtime/difference.cpp#L223); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L223-L223:sha256:e8631935f49cb376508303223bc98ae80f2afa29b5a95725d45022e8566804a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report whether wrapper and sole source owner are quiescent. |
| inputs / outputs | Returns !busy && sources.ready(). |
| invariants | False spans source commit, residual/count publication and old-state/token retirement. |
| ownership | No row/metadata copy or read lease. |
| failure | Moved-from Runtime throws difference_state. |
| cost | Fixed flag/native ready checks. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0041

[Lines 224–224](../../../../../src/runtime/difference.cpp#L224); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L224-L224:sha256:a62a92827b854bc9f3e97726737beb3898412feffdaf76d269e627338b4846ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the committed full-source/result endpoint sequence. |
| inputs / outputs | After readable(), returns sources.sequence(). |
| invariants | Source and residual state share the same publication boundary. |
| ownership | Scalar result holds no borrow/lease. |
| failure | Moved-from/busy state rejects. |
| cost | Fixed state checks and sequence read. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0042

[Lines 225–225](../../../../../src/runtime/difference.cpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L225-L225:sha256:db55a809358f6e2536ab1cd511ebd68c429de41f98162ff4150ba1a485cc9c36
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read residual nonemptiness from committed compressed state. |
| inputs / outputs | After readable(), returns !rows.empty(). |
| invariants | Counts are positive, so nonempty vector is exact positive residual support. |
| ownership | No tuple copy or eager recomputation occurs. |
| failure | Moved-from/busy state rejects. |
| cost | Fixed vector emptiness test. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0043

[Lines 226–250](../../../../../src/runtime/difference.cpp#L226); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L226-L250:sha256:aad8ee71c0bf1ba597a17a1d4bd7e900800c023c099d6e6443b8ba6aa151ede2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Atomically publish one full-source event and exact difference count replacements. |
| inputs / outputs | PhysicalSetUpdate returns genuine PhysicalEpoch, actual Binding, owning endpoint Change array and Metrics. |
| invariants | One source.prepare precedes all fallible work; trigger is physical_changed and noncontradictory operand table-use union; duplicate/absent/irrelevant events skip recompute; one after-source image and one remaining wrapper balance serve both queries; only valid source.commit precedes nonthrowing count assignment/result vector swap. |
| ownership | Source pending token supplies existing rollback; image/maps/visitors retire before commit; original-account output handles retain old/new tuples; Writing outlives source token/new-old state retirement. |
| failure | Source/constraint/capture/work/key/W01/account/allocation failure rolls back source and leaves sequence/cardinalities/residuals unchanged; no new journal/recovery layer. |
| cost | Inherited full-source validation/copy, one image capture, both visited prefix traversals and ordered count maps, residual materialization, linear endpoint merge, actual allocator and retirement costs; one grant is never reset per operand. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp) |

## B0044

[Lines 251–257](../../../../../src/runtime/difference.cpp#L251); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L251-L257:sha256:6a86f469791433c842a9e4cce2e8204787671b21815eea0273b698f3ec04137f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy committed compressed answers into a transferable owning snapshot. |
| inputs / outputs | Caller Limits bounds work/distinct output keys; returns sequence, Binding, Entry array and copy Metrics. |
| invariants | Copies handles/counts only; no bag expansion, source image, query traversal or per-key multiplicity recomputation. |
| ownership | Original-account OwnerAllocator capacity plus immutable Tuple/Binding owners survive facade teardown and require no source read lease. |
| failure | Busy/work/row/account/allocation refusal leaves committed source/count/result state intact. |
| cost | O(residual distinct keys) funded vector capacity and handle/count copies; final-owner payload/metadata cleanup remains actual cost. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0045

[Lines 258–268](../../../../../src/runtime/difference.cpp#L258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L258-L268:sha256:6c2d4a55196155eceb88b89ecd9c83c4677cc567a467aff6a3ac00534a8644ad
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build owning cold diagnostics from actual committed source/result counts. |
| inputs / outputs | Returns actual pair Profile, full table_rows, result distinct count, W01 ceiling, optional total multiplicity and per-query product/prefix estimates, memory stats. |
| invariants | Total count may overflow while individual keys remain valid; every overflow becomes nullopt; later zero recovers only full product; estimates are advisory upper products, not CROWN/GHD certificates or measured join work. |
| ownership | Funded transferable cardinality array shares original authority; Profile uses immutable POD/static labels; busy guard covers allocation callbacks. |
| failure | Busy/account/allocation refusal cannot mutate source or result endpoints. |
| cost | O(catalog tables+left atoms+right atoms+residual distinct keys), no scalar payload copying or bag expansion; ordinary diagnostic allocation/cleanup costs apply. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0046

[Lines 269–271](../../../../../src/runtime/difference.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L269-L271:sha256:cf54f2f57ecbb937042a444cbc96fa5f8b49ff5cdd987187fab01087b2de6938
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export genuine full physical sources at an explicit external diagnostic boundary. |
| inputs / outputs | After readability/busy protection, returns sources.snapshot().physical Database. |
| invariants | Difference evaluation never uses this ordinary DTO as a retained mirror or update input. |
| ownership | Ordinary exported Database/Row/string allocations belong to caller; internal native source rules/account are inherited. |
| failure | Inherited snapshot/export failures unwind without endpoint mutation. |
| cost | Eager full-source/support snapshot/export costs; this is not an internal constant-cost operation. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0047

[Lines 272–274](../../../../../src/runtime/difference.cpp#L272); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L272-L274:sha256:3ef3a25f065e039f9d0d356a21adfee1efc10e772e38c215bf702dd16cf4c9f7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the nonthrowing prepared-result return movement premise. |
| inputs / outputs | Static assertions require Epoch/Snapshot noexcept move construction and close namespace. |
| invariants | Already prepared aggregate return cannot introduce an allocation/failure after valid source commit. |
| ownership | Moves transfer existing original-account output/Binding/native source epoch owners. |
| failure | Future member changes violating premise fail compilation. |
| cost | Compile-time checks; runtime handle moves and actual eventual cleanup remain separate costs. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |
