# `src/runtime/weighted_delta_detail.hpp` — block usage map

[Source](../../../../../src/runtime/weighted_delta_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact full-subtree messages and local visible factors, then enumerate projected core tuples with multiplicities.

Snapshot SHA-256: `fce8c212e5f78f46a944c282325ed022a174adbb5e15be8dd6abd191d79770b6`. 101 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [weighted](../../../subsystem_contracts.md#weighted). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/annotations.md](../../../../annotations.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/runtime/weighted_delta_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Mutable only inside one pending token; the index borrows stable owned row · [reviewed contract](#b0001) |
| [B0002 · 10–13](../../../../../src/runtime/weighted_delta_detail.hpp#L10) | Type/record definition: struct Less | returns owner-&gt;compare(a,b)&lt;0 · [reviewed contract](#b0002) |
| [B0003 · 14–22](../../../../../src/runtime/weighted_delta_detail.hpp#L14) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Declared first: borrowed index keys die before owned payloads. · [reviewed contract](#b0003) |
| [B0004 · 23–27](../../../../../src/runtime/weighted_delta_detail.hpp#L23) | Callable definition: Data(const resource::MemoryAccount& account, annotations::MultiplicityPolicy counts, std::uint64_t& work, std::optional&lt;std::uint… | calls policy, epoch_work, limit, rows · [reviewed contract](#b0004) |
| [B0005 · 28–33](../../../../../src/runtime/weighted_delta_detail.hpp#L28) | Callable definition: void charge(std::uint64_t amount=1, std::uint64_t* counter=nullptr) | calls weighted_detail::require; guard weighted_detail::require(epoch_work && amount&lt;=UINT64_MAX-*epoch_work && · [reviewed contract](#b0005) |
| [B0006 · 34–37](../../../../../src/runtime/weighted_delta_detail.hpp#L34) | Callable definition: void bytes(const storage::ScalarView& cell) | calls charge, size · [reviewed contract](#b0006) |
| [B0007 · 38–52](../../../../../src/runtime/weighted_delta_detail.hpp#L38) | Callable definition: int cell(const storage::ScalarView& a, const storage::ScalarView& b) | calls charge, index, std::min, size; returns a.index()&lt;b.index()?-1:1; x&lt;y?-1:1; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 53–58](../../../../../src/runtime/weighted_delta_detail.hpp#L53) | Callable definition: int compare(storage::RowView a, storage::RowView b) | calls charge, std::min, size, cell; returns order; a.size()&lt;b.size()?-1:a.size()!=b.size()?1:0; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 59–64](../../../../../src/runtime/weighted_delta_detail.hpp#L59) | Callable definition: SignedMagnitude merge(SignedMagnitude a, SignedMagnitude b) | calls charge, add; returns {a.negative,policy.add(a.magnitude,b.magnitude)}; {a.negative,{a.magnitude.value-b.magnitude.value}} · [reviewed contract](#b0009) |
| [B0010 · 65–95](../../../../../src/runtime/weighted_delta_detail.hpp#L65) | Callable definition: void add(const storage::AccountedLayout& layout, storage::RowView row, SignedMagnitude term) | calls charge, find, end, merge; guard weighted_detail::require(moved!=index.end(),"weighted_contract","delta index lost its owned row");; growth emplace, push_back, reserve; 1 loop sites; source comment (unverified): // Probe borrowed projection before any owning copy. · [reviewed contract](#b0010) |
| [B0011 · 96–99](../../../../../src/runtime/weighted_delta_detail.hpp#L96) | Callable definition: void publish() noexcept | calls clear; source comment (unverified): // Each node's release was funded at insertion; compares no keys. · [reviewed contract](#b0011) |
| [B0012 · 100–101](../../../../../src/runtime/weighted_delta_detail.hpp#L100) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::weighted · [reviewed contract](#b0012) |

## B0001

[Lines 1–9](../../../../../src/runtime/weighted_delta_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BagDeltas::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep mutable consolidation private until the funded publication barrier. |
| inputs / outputs | Native policy/work pointer, account-backed facts and borrowed-key lookup. |
| invariants | Data never moves; index is declared after rows so it dies first; publish detaches the epoch-work pointer. |
| ownership | One funded shared control retains fact capacity/payloads; index owns only key views and slot numbers. |
| failure | Preparation exceptions cannot expose a partial committed result. |
| cost | Current net payloads plus peak vector capacity and one lookup node per current net key. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0002

[Lines 10–13](../../../../../src/runtime/weighted_delta_detail.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  struct Less {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order borrowed output probes while charging actual comparison work. |
| inputs / outputs | Two RowViews use the owning Data scalar comparator. |
| invariants | Data address remains stable; comparator may throw before map mutation. |
| ownership | Raw self pointer borrows its enclosing nonmoving shared owner. |
| failure | Work exhaustion propagates to the existing stage abort. |
| cost | Actual compared fields/string prefixes; no owning temporary key. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0003

[Lines 14–22](../../../../../src/runtime/weighted_delta_detail.hpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L22:sha256:557405e6799398fc41fb8040fcb9594d4b52d351452c176846b70d3cdb89c0e1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/weighted_delta_detail.hpp: imports or aliases \`Entries=weighted_detail::Vector&lt;BagDelta&gt;\`, \`Index=std::map&lt;storage::RowView,std::size_t,Less, resource::MemoryAllocator&lt;std::pair&lt;const storage::RowView,std::size_t&gt;&gt;&gt;\`. Source comment: Declared first: borrowed index keys die before owned payloads Member/state declarations in this range include \`std::uint64_t* epoch_work\`; \`std::optional&lt;std::uint64_t&gt; limit\`; \`Index index\`. |
| inputs / outputs | This span declares/carries these members or local values: \`std::uint64_t* epoch_work\`; \`std::optional&lt;std::uint64_t&gt; limit\`; \`Index index\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | The source note says: Declared first: borrowed index keys die before owned payloads. Prose alone does not enforce the rule. |
| ownership | Allocator-backed storage uses the explicit account/purpose/attribution shown in the declaration or constructor. Vector is the runtime account-backed vector alias; the enclosing constructor selects the account and purpose. Span/view members borrow their source; retain the source owner for the full use window. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 23–27](../../../../../src/runtime/weighted_delta_detail.hpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Data(const resource::MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the optional consolidation owner under the original account. |
| inputs / outputs | Exact policy, epoch work reference/ceiling and receiving allocator; empty containers. |
| invariants | No new account/allowance; self comparator points to this stable object. |
| ownership | Vector and map allocators retain the same account; work pointer borrows the active token. |
| failure | Control allocation can fail before token publication. |
| cost | Fixed empty controls; later insertions fund actual storage. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0005

[Lines 28–33](../../../../../src/runtime/weighted_delta_detail.hpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void charge(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit capture work before its covered operation. |
| inputs / outputs | Amount and optional category counter; advance epoch total and capture subset. |
| invariants | Check uint64/ceiling before increment; each category is bounded by total admitted capture work. |
| ownership | Borrow active epoch work until publish clears that pointer. |
| failure | Exhaustion raises resource_limit without adding an exception layer. |
| cost | Fixed unsigned checks/increments. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0006

[Lines 34–37](../../../../../src/runtime/weighted_delta_detail.hpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void bytes(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit bytes only where a string payload will be copied. |
| inputs / outputs | ScalarView; string length charged to scalar_bytes, other alternatives add none here. |
| invariants | Fixed-size descriptor work is charged by the caller separately. |
| ownership | Borrows input; copies no string. |
| failure | Work exhaustion propagates before copy. |
| cost | Fixed tag/length read plus debit. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0007

[Lines 38–52](../../../../../src/runtime/weighted_delta_detail.hpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  int cell(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact typed scalar values with byte-level work admission. |
| inputs / outputs | ScalarViews produce -1/0/1; alternative index first, unsigned binary string prefix next. |
| invariants | Order agrees with native typed order; numeric/date/inline-decimal operations retain their bounded primitive costs. |
| ownership | Borrows both cells; no owned string conversion. |
| failure | A charge may exhaust the cumulative work allowance. |
| cost | Actual compared fields/string-prefix bytes; fixed-word or bounded-digit nonstring comparison. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0008

[Lines 53–58](../../../../../src/runtime/weighted_delta_detail.hpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  int compare(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order full borrowed output rows for consolidation. |
| inputs / outputs | Lexicographic scalar comparison, then arity. |
| invariants | Equality uses every relevant typed cell, never Python-like cross-kind numeric coercion. |
| ownership | Borrowed probes and stable owned key payloads. |
| failure | Comparison admission errors leave map search/insertion at the existing rollback boundary. |
| cost | Visited fields/bytes; ordered map invokes this O(log current keys) times per ordinary lookup. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0009

[Lines 59–64](../../../../../src/runtime/weighted_delta_detail.hpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  SignedMagnitude merge(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine two signed unsigned-magnitude contributions. |
| inputs / outputs | Same signs use checked policy.add; opposite signs subtract smaller from larger. |
| invariants | No signed narrowing; a zero result is removed by add. |
| ownership | Inline values only. |
| failure | Same-sign policy overflow rejects before changing stored fact. |
| cost | Fixed checked arithmetic. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0010

[Lines 65–95](../../../../../src/runtime/weighted_delta_detail.hpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void add(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consolidate a projected term before allocating an owning output key. |
| inputs / outputs | Compiled result layout, borrowed row and nonzero term; update/insert/cancel its unique fact. |
| invariants | Probe first; on cancel repair moved-last slot and erase old key before payload destruction; reserved insertion uses only no-throw moves after membership publication. |
| ownership | Index borrows stable fact payloads; new keys alone freeze original-account tuple/string bytes. |
| failure | Comparison, capacity, tuple or node allocation failures abort the existing epoch; no local catch. |
| cost | Ordered lookup, actual compared/copy bytes and handle relocations. Existing-key merge/cancel creates no new owning output tuple. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0011

[Lines 96–99](../../../../../src/runtime/weighted_delta_detail.hpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void publish() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Discard mutable lookup state before sharing committed facts. |
| inputs / outputs | Clear index and null the borrowed epoch-work pointer. |
| invariants | Every release was prefunded at insertion; clearing compares no keys and allocates nothing. |
| ownership | Only immutable rows/metrics and their original-account allocator controls remain. |
| failure | Nonthrowing cleanup under existing allocator contract. |
| cost | Linear in remaining lookup nodes plus deallocation bookkeeping; no sort, seal copy or compaction. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0012

[Lines 100–101](../../../../../src/runtime/weighted_delta_detail.hpp#L100); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L100-L101:sha256:67394b29ad8392be1e577e4ac05a33458a3ffc1b2556266dcb65dacaeadbe2aa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/weighted_delta_detail.hpp: closes \`struct BagDeltas::Data\`, \`namespace crown::runtime::weighted\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace crown::runtime::weighted Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
