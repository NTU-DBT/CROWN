# `src/runtime/star_hindex.hpp` — block usage map

[Source](../../../../../src/runtime/star_hindex.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Track exact generalized H using occupied degree frequencies, two suffix counts and private allocation-free publication.

Snapshot SHA-256: `0a454fa1ac80379757c574d283d4e1164ad72d45cc9f701841d174c4fd824a46`. 249 lines partitioned into 40 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [star](../../../subsystem_contracts.md#star). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../src/runtime/star_hindex.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Exact center-coordinate generalized H, not maximum degree or graph H for · [reviewed contract](#b0001) |
| [B0002 · 23–23](../../../../../src/runtime/star_hindex.hpp#L23) | Type/record definition: struct State |  · [reviewed contract](#b0002) |
| [B0003 · 24–24](../../../../../src/runtime/star_hindex.hpp#L24) | Explanatory comments or spacing. |  |
| [B0004 · 25–45](../../../../../src/runtime/star_hindex.hpp#L25) | Callable definition: public: // nullopt means a mathematical power above UINT64_MAX. The exponent-zero // convention is 1, including 0^0, because d=1 … | calls ; returns Count{1}; Count{0}; 1 loop sites; source comment (unverified): // nullopt means a mathematical power above UINT64_MAX. The exponent-zero · [reviewed contract](#b0004) |
| [B0005 · 46–54](../../../../../src/runtime/star_hindex.hpp#L46) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // A preparation borrows one stable index; the index must outlive it and · [reviewed contract](#b0005) |
| [B0006 · 55–59](../../../../../src/runtime/star_hindex.hpp#L55) | Callable definition: Prepared(Prepared&& other) noexcept : owner_(std::exchange(other.owner_, nullptr)), old_(other.old_), destination_(other.destinat… | calls owner_, std::exchange, old_, destination_ · [reviewed contract](#b0006) |
| [B0007 · 60–71](../../../../../src/runtime/star_hindex.hpp#L60) | Callable definition: Prepared& operator=(Prepared&& other) noexcept | calls emplace, std::move, std::exchange; returns *this; growth emplace; source comment (unverified): // Reconstruct the optional node handle: tokens from unequal query · [reviewed contract](#b0007) |
| [B0008 · 72–72](../../../../../src/runtime/star_hindex.hpp#L72) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0008) |
| [B0009 · 73–73](../../../../../src/runtime/star_hindex.hpp#L73) | Callable definition: \[\[nodiscard\]\] Count next_h() const noexcept | calls ; returns next_.h · [reviewed contract](#b0009) |
| [B0010 · 74–74](../../../../../src/runtime/star_hindex.hpp#L74) | Callable definition: \[\[nodiscard\]\] Count next_keys() const noexcept | calls ; returns next_.keys · [reviewed contract](#b0010) |
| [B0011 · 75–75](../../../../../src/runtime/star_hindex.hpp#L75) | Callable definition: \[\[nodiscard\]\] Count next_a() const noexcept | calls ; returns next_.a · [reviewed contract](#b0011) |
| [B0012 · 76–76](../../../../../src/runtime/star_hindex.hpp#L76) | Callable definition: \[\[nodiscard\]\] Count next_b() const noexcept | calls ; returns next_.b · [reviewed contract](#b0012) |
| [B0013 · 77–81](../../../../../src/runtime/star_hindex.hpp#L77) | Explanatory comments or spacing. | source comment (unverified): // Valid publication uses equal-allocator detached insertion and integer · [reviewed contract](#b0013) |
| [B0014 · 82–93](../../../../../src/runtime/star_hindex.hpp#L82) | Callable definition: void commit() noexcept | calls insert, std::move, end, erase; growth insert; source comment (unverified): // Valid publication uses equal-allocator detached insertion and integer · [reviewed contract](#b0014) |
| [B0015 · 94–96](../../../../../src/runtime/star_hindex.hpp#L94) | declares types or opens a type body. |  · [reviewed contract](#b0015) |
| [B0016 · 97–100](../../../../../src/runtime/star_hindex.hpp#L97) | Callable definition: Prepared(HIndex& owner, Histogram::iterator old, Histogram::iterator destination, std::optional&lt;Histogram::node_type&gt; node, State… | calls owner_, old_, destination_, node_ · [reviewed contract](#b0016) |
| [B0017 · 101–106](../../../../../src/runtime/star_hindex.hpp#L101) | Member/declaration region. |  · [reviewed contract](#b0017) |
| [B0018 · 107–112](../../../../../src/runtime/star_hindex.hpp#L107) | Callable definition: explicit HIndex(const resource::MemoryAccount& account, std::size_t dimension, resource::MemoryAttribution attribution = {resourc… | calls dimension_, histogram_, Histogram::allocator_type, require; guard require(dimension != 0, "center arity must be positive"); · [reviewed contract](#b0018) |
| [B0019 · 113–118](../../../../../src/runtime/star_hindex.hpp#L113) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Move only between operations, with no live Prepared. A moved-from index · [reviewed contract](#b0019) |
| [B0020 · 119–119](../../../../../src/runtime/star_hindex.hpp#L119) | Callable definition: \[\[nodiscard\]\] std::size_t dimension() const noexcept | calls ; returns dimension_ · [reviewed contract](#b0020) |
| [B0021 · 120–120](../../../../../src/runtime/star_hindex.hpp#L120) | Callable definition: \[\[nodiscard\]\] Count h() const noexcept | calls ; returns state_.h · [reviewed contract](#b0021) |
| [B0022 · 121–121](../../../../../src/runtime/star_hindex.hpp#L121) | Callable definition: \[\[nodiscard\]\] Count keys() const noexcept | calls ; returns state_.keys · [reviewed contract](#b0022) |
| [B0023 · 122–122](../../../../../src/runtime/star_hindex.hpp#L122) | Callable definition: \[\[nodiscard\]\] Count a() const noexcept | calls ; returns state_.a · [reviewed contract](#b0023) |
| [B0024 · 123–123](../../../../../src/runtime/star_hindex.hpp#L123) | Callable definition: \[\[nodiscard\]\] Count b() const noexcept | calls ; returns state_.b · [reviewed contract](#b0024) |
| [B0025 · 124–124](../../../../../src/runtime/star_hindex.hpp#L124) | Callable definition: \[\[nodiscard\]\] std::size_t histogram_buckets() const noexcept | calls size; returns histogram_.size() · [reviewed contract](#b0025) |
| [B0026 · 125–127](../../../../../src/runtime/star_hindex.hpp#L125) | Callable definition: \[\[nodiscard\]\] std::optional&lt;Count&gt; threshold(Count base) const noexcept | calls power; returns power(base, dimension_ - 1) · [reviewed contract](#b0026) |
| [B0027 · 128–132](../../../../../src/runtime/star_hindex.hpp#L128) | Explanatory comments or spacing. | source comment (unverified): // One actual center-row change changes this coordinate's one key degree by · [reviewed contract](#b0027) |
| [B0028 · 133–181](../../../../../src/runtime/star_hindex.hpp#L133) | Callable definition: template&lt;class Charge&gt; \[\[nodiscard\]\] Prepared prepare(Count old_degree, Count new_degree, Charge&& charge) | calls charge, require, add, subtract; guard require(insertion ? old_degree != UINT64_MAX && new_degree == old_degree + 1 :; returns Prepared(*this, old, destination, std::move(node), next); growth emplace; source comment (unverified): // One actual center-row change changes this coordinate's one key degree by · [reviewed contract](#b0028) |
| [B0029 · 182–184](../../../../../src/runtime/star_hindex.hpp#L182) | Explanatory comments or spacing. | source comment (unverified): // Explicit diagnostic scan, not an update primitive or complexity witness. · [reviewed contract](#b0029) |
| [B0030 · 185–198](../../../../../src/runtime/star_hindex.hpp#L185) | Callable definition: void check_invariants() const | calls threshold, following_threshold, require, add; guard require(degree && frequency, "histogram contains a zero bucket");; 1 loop sites; source comment (unverified): // Explicit diagnostic scan, not an update primitive or complexity witness. · [reviewed contract](#b0030) |
| [B0031 · 199–199](../../../../../src/runtime/star_hindex.hpp#L199) | Explanatory comments or spacing. |  |
| [B0032 · 200–203](../../../../../src/runtime/star_hindex.hpp#L200) | Callable definition: private: static void require(bool condition, const char* message) | calls Error; guard static void require(bool condition, const char* message) { · [reviewed contract](#b0032) |
| [B0033 · 204–206](../../../../../src/runtime/star_hindex.hpp#L204) | Callable definition: static Count add(Count value, Count amount) | calls require; guard require(amount &lt;= UINT64_MAX - value, "histogram count overflow"); return value + amount;; returns value + amount · [reviewed contract](#b0033) |
| [B0034 · 207–209](../../../../../src/runtime/star_hindex.hpp#L207) | Callable definition: static Count subtract(Count value, Count amount) | calls require; guard require(amount &lt;= value, "histogram count underflow"); return value - amount;; returns value - amount · [reviewed contract](#b0034) |
| [B0035 · 210–213](../../../../../src/runtime/star_hindex.hpp#L210) | Callable definition: \[\[nodiscard\]\] std::optional&lt;Count&gt; following_threshold(Count h) const noexcept | calls threshold; returns Count{1}; h == UINT64_MAX ? std::optional&lt;Count&gt;{} : threshold(h + 1) · [reviewed contract](#b0035) |
| [B0036 · 214–216](../../../../../src/runtime/star_hindex.hpp#L214) | Callable definition: static bool at_least(Count degree, std::optional&lt;Count&gt; bound) noexcept | calls ; returns degree && bound && degree &gt;= *bound · [reviewed contract](#b0036) |
| [B0037 · 217–221](../../../../../src/runtime/star_hindex.hpp#L217) | Callable definition: static Count adjusted(Count value, std::optional&lt;Count&gt; bound, Count old_degree, Count new_degree) | calls at_least, subtract, add; returns value · [reviewed contract](#b0037) |
| [B0038 · 222–224](../../../../../src/runtime/star_hindex.hpp#L222) | Callable definition: static bool inside(Count degree, std::optional&lt;Count&gt; low, std::optional&lt;Count&gt; high) noexcept | calls at_least; returns at_least(degree, low) && (!high \|\| degree &lt; *high) · [reviewed contract](#b0038) |
| [B0039 · 225–238](../../../../../src/runtime/star_hindex.hpp#L225) | Callable definition: template&lt;class Charge&gt; Count interval(std::optional&lt;Count&gt; low, std::optional&lt;Count&gt; high, Count old_degree, Count new_degree, Ch… | calls charge, lower_bound, end, add; returns 0; count; 1 loop sites · [reviewed contract](#b0039) |
| [B0040 · 239–249](../../../../../src/runtime/star_hindex.hpp#L239) | Member/declaration region. | source comment (unverified): // Only occupied degree buckets are traversed in a threshold interval. For · [reviewed contract](#b0040) |

## B0001

[Lines 1–22](../../../../../src/runtime/star_hindex.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L22:sha256:2540dc79afb96f7d044b05d8e9495e0f0221e1ab87c427517b6d9f709a066b10
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the exact generalized H tracker and its accounted degree-frequency representation. |
| inputs / outputs | Count, Histogram and HIndex declarations establish the private center-coordinate primitive. |
| invariants | H counts positive-degree keys above r^(d-1); P2 defines the quantity, while the suffix tracker is a local repair. |
| ownership | Histogram nodes use the supplied original account; this private class creates no query allowance. |
| failure | Public prepare and constructor validation own the failure boundary; declarations add no runtime handler. |
| cost | Sparse occupied degrees only; map nodes, scalar powers and account bookkeeping have actual costs. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0002

[Lines 23–23](../../../../../src/runtime/star_hindex.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L23:sha256:7586f6a6ac48fe26828692427905e88a7d44ddf8712af293a1ec2345dd0a59f5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the four exact scalar summaries of a committed histogram. |
| inputs / outputs | State defaults h, positive key total, A and B to zero. |
| invariants | A counts degree &gt;=h^(d-1); B counts degree &gt;=(h+1)^(d-1), with d1 exponent-zero semantics. |
| ownership | Inline state owns no heap payload or source-key identity. |
| failure | State assignments are private after validated preparation. |
| cost | Four fixed-width words. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0004

[Lines 25–45](../../../../../src/runtime/star_hindex.hpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L45:sha256:57efc1b7f155c8fe9ed7aff44bbc7be70900ce7b6b4c028f90b1ac4ce4d86b65
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute an integer threshold power without overflow or floating point. |
| inputs / outputs | Nonnegative base and size_t exponent return the exact uint64 power or nullopt for mathematical infinity. |
| invariants | Exponent zero gives one, including 0^0; zero/one bases shortcut before large-exponent overflow classification. |
| ownership | Only inline arithmetic is used; no histogram or memory owner is accessed. |
| failure | Overflow returns an explicit absent threshold instead of throwing or wrapping. |
| cost | Bounded uint64 exponentiation-by-squaring work; no source-key or degree-bucket scan. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0005

[Lines 46–54](../../../../../src/runtime/star_hindex.hpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L54:sha256:40a02ad047680483d63b09761d94c713529d64a256f4c75cd491eed36e2b86aa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare an exclusive noncopyable prospective H transition. |
| inputs / outputs | Prepared borrows a stable HIndex until commitment or abandonment. |
| invariants | The owner histogram must remain unchanged and alive; only one token per owner may be operationally outstanding. |
| ownership | Only a possible detached destination bucket is owned; no live histogram edits are made by preparation. |
| failure | Dropping an uncommitted token frees private node storage and preserves all committed summaries. |
| cost | Fixed token fields and at most one accounted node. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0006

[Lines 55–59](../../../../../src/runtime/star_hindex.hpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L59:sha256:ebca265397a3932daaa1f63d922b076a667b26859f426ac60f80e5e95db61614
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer one prepared H transition through move construction. |
| inputs / outputs | Transfer owner, active iterators, optional node and next summary, then clear moved-from owner and iterator dependencies. |
| invariants | A moved-from token cannot publish or later copy iterators that a committed destination may invalidate. |
| ownership | Detached node allocator ownership transfers without rebinding the query account. |
| failure | The move is noexcept and performs no histogram mutation. |
| cost | Fixed ownership/iterator/state movement and iterator reset; no allocation or histogram mutation. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0007

[Lines 60–71](../../../../../src/runtime/star_hindex.hpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L71:sha256:f0ea596cee6c1529a412fdba8480c2d6ee7267b85c483ea111fbeb033f3e7258
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a preparation safely across potentially different query allocators. |
| inputs / outputs | Move assignment abandons the destination token, reconstructs its optional node and transfers source authority. |
| invariants | Nonpropagating node-handle move assignment is avoided; source owner and iterators are cleared after transfer, so later moves of inactive/moved-from tokens have no retired iterator dependencies. |
| ownership | Any abandoned detached destination node is freed through its original allocator. |
| failure | Noexcept replacement cannot mutate either owner histogram before a later explicit commit. |
| cost | Fixed moves/iterator resets plus actual deallocation of an abandoned optional node. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0008

[Lines 72–72](../../../../../src/runtime/star_hindex.hpp#L72); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L72-L72:sha256:2b25c0c25d7183068d8ac5aae0008bb45b252065c0cd809366e451b70c2eec16
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release an abandoned prepared histogram node by normal destruction. |
| inputs / outputs | The default destructor destroys only owned optional node state. |
| invariants | No rollback action is required because prepare did not edit the owner. |
| ownership | The detached node retains the account necessary for its deallocation. |
| failure | Destruction publishes nothing and is nonthrowing under allocator contracts. |
| cost | At most one node release; no histogram walk. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0009

[Lines 73–73](../../../../../src/runtime/star_hindex.hpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L73:sha256:5cd84e135cc1e230b7d4188520f070840da47e9f26ad7087fe03fbfa06f98e1e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the prospective generalized H for private view rebalancing. |
| inputs / outputs | next_h returns next_.h, computed against the virtual degree change. |
| invariants | It is a proposal until the same source/view barrier commits the token. |
| ownership | Returns a copied word, with no additional owner. |
| failure | No failure on a valid token. |
| cost | O(1) scalar access. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0010

[Lines 74–74](../../../../../src/runtime/star_hindex.hpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L74:sha256:aea2b6f1101036cdcdaa854f9e63adeaa3fc1a09555f1469416e844db083a85d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the prospective number of positive-degree keys. |
| inputs / outputs | next_keys returns next_.keys after zero-presence crossing adjustment. |
| invariants | Degree zero is not counted as a positive key. |
| ownership | Returns an independent uint64 value. |
| failure | No failure on a valid token. |
| cost | O(1) scalar access. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0011

[Lines 75–75](../../../../../src/runtime/star_hindex.hpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L75:sha256:08d2382a1a60292a9ecd275f13205940245677ce74f781d1e0f727546c492460
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the prospective lower suffix count. |
| inputs / outputs | next_a returns the count at next_h^(d-1). |
| invariants | The suffix reflects the virtual old/new update, not premature histogram publication. |
| ownership | A copied count retains no key or bucket. |
| failure | No failure on a valid token. |
| cost | O(1) scalar access. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0012

[Lines 76–76](../../../../../src/runtime/star_hindex.hpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L76-L76:sha256:2f5966a45be89b19a6daedecc85d8afb67123b90d256f9c6e74800af0571d469
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the prospective upper suffix count. |
| inputs / outputs | next_b returns the count at (next_h+1)^(d-1). |
| invariants | The upper suffix witnesses maximality when the transition commits. |
| ownership | A copied count retains no key or bucket. |
| failure | No failure on a valid token. |
| cost | O(1) scalar access. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0013

[Lines 77–81](../../../../../src/runtime/star_hindex.hpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L81:sha256:b59990d45a664b16b989b04fb78f1413a3e4e4b917fae54d7eb5845eed978a4b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the H token no-allocation publication ordering. |
| inputs / outputs | Comment identifies equal-allocator node insertion, old-bucket erasure and scalar assignment. |
| invariants | Insertion precedes erasure because the saved lower_bound hint may be the old bucket. |
| ownership | Existing prepared storage supplies all publication memory. |
| failure | Only a valid serialized token is eligible for noexcept commitment. |
| cost | Integer comparison, map erasure/deallocation and account costs are retained. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0014

[Lines 82–93](../../../../../src/runtime/star_hindex.hpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L93:sha256:76d5864c20e26035a7e2ddd2b259db9bf1959b40314e5094a3e6c6225539c4c2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit one validated private degree-frequency transition. |
| inputs / outputs | Publish the destination frequency, decrement/prune old degree, assign next State, then clear owner and both saved iterators. |
| invariants | Histogram is unchanged since prepare. Insert before erasing an old hint, and clear the retired iterator after its last use so moving the inactive token remains valid. |
| ownership | An inserted node joins the owner map with the same allocator; token authority is cleared after publication. |
| failure | Valid commit is noexcept and allocation-free; an ownerless token is inert. Clearing retired references avoids copying an invalid erased iterator later. |
| cost | Ordered node insertion/erase, fixed summary assignment and iterator retirement; no refill or key census. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0015

[Lines 94–96](../../../../../src/runtime/star_hindex.hpp#L94); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L96:sha256:e7eb9e8c4b96bb86581519f455c723906bd0700cb64354be3982315633f3b376
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Limit prepared-token creation to the HIndex owner. |
| inputs / outputs | Private access and friend declaration precede its validated constructor. |
| invariants | A caller cannot fabricate the saved iterators/prospective summary through a public constructor. |
| ownership | No additional ownership exists in these declarations. |
| failure | Compilation enforces the private boundary. |
| cost | No runtime work. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0016

[Lines 97–100](../../../../../src/runtime/star_hindex.hpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L97-L100:sha256:ab05845aa3c5743ffcc12fdfca2f3b552bf1ea02ce29f6fe3f9a13553c6fc092
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Package a completed private H proposal. |
| inputs / outputs | Owner reference, old/destination iterators, optional node and next summary initialize Prepared. |
| invariants | Every fallible validation/allocation is already complete before this noexcept constructor. |
| ownership | The token borrows the stable index and owns its detached node only. |
| failure | Construction is noexcept and changes no histogram. |
| cost | Fixed field/node-handle move. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0017

[Lines 101–106](../../../../../src/runtime/star_hindex.hpp#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L106:sha256:6438979c02f189b47799744200f6dbb16a6fe84fb61736438c94bcd6c586b600
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the prepared H publication inputs and close the nested type. |
| inputs / outputs | Raw owner, stable current iterators, optional detached node and next State are retained. |
| invariants | An active token borrows a stable serialized owner; moved-from and committed tokens have cleared owner/iterator dependencies. |
| ownership | Only a detached node is owned. Active iterators borrow resident histogram storage and are retired on commit or ownership transfer. |
| failure | No cleanup beyond normal member destruction is declared here. |
| cost | Fixed-size preparation metadata. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0018

[Lines 107–112](../../../../../src/runtime/star_hindex.hpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L112:sha256:45a924b93e3542aac937df63cf9119be1a45e218edc3f8f29efe4e548a32fab4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an empty histogram on the existing query account. |
| inputs / outputs | Original account, positive center arity and attribution initialize an empty ordered histogram and zero summaries. |
| invariants | The account is supplied by the owner; no hidden budget or unrelated allocator is created. |
| ownership | The map allocator retains account, support_metadata purpose and immutable attribution. |
| failure | Invalid account/configuration or zero dimension refuses private construction. |
| cost | Fixed initial state; actual node allocation occurs only when a degree bucket is prepared. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0019

[Lines 113–118](../../../../../src/runtime/star_hindex.hpp#L113); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L113-L118:sha256:5774387477cb615151fba90ad8722b8e8b47c2078d01d9a6ccf4fc8d9807a5d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict copying/moving of an operational H owner. |
| inputs / outputs | Copy/assignment are deleted; move construction is allowed only between operations without live tokens. |
| invariants | A moved-from index is for destruction, since its copied summary no longer describes transferred nodes. |
| ownership | Map ownership moves with its existing allocator; no key payload is copied. |
| failure | These declarations enforce type restrictions; callers must preserve the documented token-lifetime precondition. |
| cost | Move construction transfers container state; later final destruction visits retained buckets. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0020

[Lines 119–119](../../../../../src/runtime/star_hindex.hpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L119-L119:sha256:fededb45a883130655b831d353a25b7e3f22a1d0bf6d63939a85249a4825acf4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report center arity used by this H definition. |
| inputs / outputs | dimension returns the immutable positive dimension_. |
| invariants | It means center arity, not independently certified structural dimension. |
| ownership | Returns a size value, not borrowed storage. |
| failure | No failure on a live index. |
| cost | O(1) access. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0021

[Lines 120–120](../../../../../src/runtime/star_hindex.hpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L120-L120:sha256:7c5d6a64a91b34cea9a4d6f1cd67344b326b34a4f31d2addf4418840f9cdfaad
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the committed exact generalized H. |
| inputs / outputs | h returns state_.h. |
| invariants | Prepared next_h is not exposed through this committed getter before publication. |
| ownership | Returns a copied count without owning a histogram. |
| failure | No failure on a live index. |
| cost | O(1) access. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0022

[Lines 121–121](../../../../../src/runtime/star_hindex.hpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L121-L121:sha256:e8f6aaed8c75c576afd8455641d0952ae831cb55299ae50a5d66f7241b603041
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report committed positive-degree key population. |
| inputs / outputs | keys returns state_.keys. |
| invariants | Satellite-only degree-zero records are excluded. |
| ownership | Returns a copied count. |
| failure | No failure on a live index. |
| cost | O(1) access. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0023

[Lines 122–122](../../../../../src/runtime/star_hindex.hpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L122-L122:sha256:d6171a49903fa56c5162933c0bbaa889286d98e03eafc42b80a3da5fbb319bec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the committed suffix at the current H threshold. |
| inputs / outputs | a returns state_.a. |
| invariants | The histogram invariant defines it using positive degrees and h^(d-1). |
| ownership | Returns a copied count. |
| failure | No failure on a live index. |
| cost | O(1) access. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0024

[Lines 123–123](../../../../../src/runtime/star_hindex.hpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L123-L123:sha256:857fe1c98de24dd2925c281712a27c0855d18bf41f4047e18fab3a9b7bed72cd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the committed suffix above the next candidate H. |
| inputs / outputs | b returns state_.b. |
| invariants | It counts positive keys at (h+1)^(d-1), including the exponent-zero d1 convention. |
| ownership | Returns a copied count. |
| failure | No failure on a live index. |
| cost | O(1) access. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0025

[Lines 124–124](../../../../../src/runtime/star_hindex.hpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L124-L124:sha256:e568f6b5d803ddf9813c951f823617d41ca78fcec187807c17864ca693b24d00
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report occupied degree-bucket count for bounded diagnostics. |
| inputs / outputs | histogram_buckets returns ordered map size. |
| invariants | Only occupied positive degrees are represented. |
| ownership | Returns a scalar size without exposing container iterators. |
| failure | No failure on a live index. |
| cost | O(1) map-size access; inspecting those buckets is separate work. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0026

[Lines 125–127](../../../../../src/runtime/star_hindex.hpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L125-L127:sha256:235b14d12eb88e38adf0533192194008f47179668415b2ac23185237dd7b58bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind a threshold base to this center arity. |
| inputs / outputs | threshold(base) computes power(base, dimension_-1). |
| invariants | Construction established dimension&gt;0; nullopt retains mathematical infinity. |
| ownership | No storage ownership changes. |
| failure | Overflow is represented, not thrown. |
| cost | Bounded fixed-word power calculation. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0027

[Lines 128–132](../../../../../src/runtime/star_hindex.hpp#L128); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L128-L132:sha256:ddae2c2096a3d719b4a663a2fe5bf179d506d3dddc6fac3a53f30a5eeb75c2b9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the one-incidence, absent-zero and shared-budget H preparation contract. |
| inputs / outputs | The following prepare accepts exactly one center-key degree increment/decrement. |
| invariants | No-op source events and satellite changes must bypass this primitive; the caller shares one charge balance. |
| ownership | All destination-node storage is private until later source/view publication. |
| failure | Any refusal leaves the owner histogram and its summaries unchanged. |
| cost | Threshold intervals, lookup, arithmetic and allocation remain explicit costs. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0028

[Lines 133–181](../../../../../src/runtime/star_hindex.hpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L181:sha256:607bacbf6a0f352f75c216bb74f745df01313637e73fd9d8a648995d072acf74
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare exact H/A/B after one center-coordinate degree change. |
| inputs / outputs | Validate old/new +/-1, derive positive key total and virtual suffix counts, adjust H by at most one and fund a missing destination bucket. |
| invariants | Current A/B satisfy exact H; interval adjustment includes the virtual old/new degrees. d1 sets h=A=B=positive keys. |
| ownership | The histogram remains untouched; returned Prepared owns at most one original-account detached node and borrows saved map iterators. |
| failure | Invalid transition/counter inconsistency, shared charge refusal or allocation failure publishes no change. |
| cost | A constant number of ordered lookups plus occupied buckets in the changed threshold interval; width O_d((h+1)^(d-2)) for d&gt;=2, with map/allocation costs additional. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0029

[Lines 182–184](../../../../../src/runtime/star_hindex.hpp#L182); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L182-L184:sha256:c0bd43b8a376e3d99cad94eed51b90f40fb0ee0c4774311803a4f6a61f2f6866
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mark the following histogram audit as cold diagnostic work. |
| inputs / outputs | Comment describes positive buckets, key total, two suffixes and maximality checks. |
| invariants | The diagnostic scan must not replace update-time threshold tracking. |
| ownership | It borrows the existing histogram without building another source-key structure. |
| failure | Invariant failure is diagnostic refusal, not a recovery or mutation path. |
| cost | Full occupied-bucket scan, explicitly outside the update primitive. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0030

[Lines 185–198](../../../../../src/runtime/star_hindex.hpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L198:sha256:afe523dfd15567ae9c4babffa3b1e05fa2ac64c2e606387d14082e4b0fdc5df4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check internal histogram totals and exact-H threshold conditions. |
| inputs / outputs | Recompute positive-key/A/B sums over every stored degree and compare committed summaries and maximality. |
| invariants | All bucket degrees/frequencies are positive; A&gt;=h and B&lt;h+1, with uint64-max boundary handled explicitly. |
| ownership | Read-only inline scratch borrows the map; no payload or account is acquired. |
| failure | Malformed counts/overflow or disagreement raises star_hindex_contract without mutation. |
| cost | O(number of occupied degree buckets), plus bounded threshold arithmetic; not source-answer verification. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0032

[Lines 200–203](../../../../../src/runtime/star_hindex.hpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L200-L203:sha256:d5c0ca49f651a42f5d9fb026f4f53501ed907d59d00e62befa477b28e5c8bacc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report a violated private H precondition with a scoped code. |
| inputs / outputs | A false condition throws Error(star_hindex_contract, message). |
| invariants | Normal valid updates do not build diagnostic text. |
| ownership | The exception owns its external message; no histogram state is changed. |
| failure | The Error propagates to the owning source/view rollback boundary. |
| cost | Constant check; exception formatting/allocation is failure-only cost. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0033

[Lines 204–206](../../../../../src/runtime/star_hindex.hpp#L204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L204-L206:sha256:5d989368ff065d6c87089536ef92a2371fae597d14025f1866992d078ef3042c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add exact H/histogram counts without wraparound. |
| inputs / outputs | value and amount return value+amount after checking uint64 headroom. |
| invariants | A successful sum is representable exactly. |
| ownership | Only inline numeric values are involved. |
| failure | Overflow raises the private H contract error before the caller assigns state. |
| cost | Fixed unsigned arithmetic and comparison. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0034

[Lines 207–209](../../../../../src/runtime/star_hindex.hpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L207-L209:sha256:6800b767af7134e8319c00a48c50eb597b220309115e9dfe445f9794a90279cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Subtract exact H/histogram counts without underflow. |
| inputs / outputs | value and amount return their checked difference. |
| invariants | The subtrahend cannot exceed the existing count. |
| ownership | Only inline numeric values are involved. |
| failure | Underflow raises the private H contract error before publication. |
| cost | Fixed unsigned arithmetic and comparison. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0035

[Lines 210–213](../../../../../src/runtime/star_hindex.hpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L210-L213:sha256:ace3022b5b8037e8083ee5b5016af40a8d5e61419287ea2ace5bcb4684765087
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the next-H threshold across the uint64 boundary. |
| inputs / outputs | following_threshold(h) returns one for d1, infinity if h+1 cannot be represented, otherwise threshold(h+1). |
| invariants | The exponent-zero rule takes priority over base overflow. |
| ownership | No histogram or scalar payload is owned. |
| failure | No exception; mathematical overflow is explicit nullopt. |
| cost | Fixed boundary check plus bounded power calculation. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0036

[Lines 214–216](../../../../../src/runtime/star_hindex.hpp#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L214-L216:sha256:62da118c33f01a7297c6347cd4e8355cfc0b043c756981ac9169fbdf70f56c5e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test positive degree membership in a finite suffix. |
| inputs / outputs | degree and optional bound return true only for a present positive degree at/above a finite threshold. |
| invariants | Absent degree zero and infinite thresholds contribute no key. |
| ownership | No ownership or mutation. |
| failure | Noexcept comparison. |
| cost | Fixed word tests. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0037

[Lines 217–221](../../../../../src/runtime/star_hindex.hpp#L217); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L217-L221:sha256:5c814cc70b838366265d644fc8b78cab7d3a6401a2a6c6ea4282b963e30ad4be
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one virtual key replacement to a suffix count. |
| inputs / outputs | Subtract old positive-degree membership then add new membership against one threshold. |
| invariants | The owner histogram is not edited while its prospective summary is computed. |
| ownership | Inputs/output are inline counts and threshold values. |
| failure | Counter inconsistency is rejected through checked add/subtract. |
| cost | Two membership tests and checked word updates. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0038

[Lines 222–224](../../../../../src/runtime/star_hindex.hpp#L222); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L222-L224:sha256:5f9bbf49ba188e9944ae8868272ce01a3ddd9edeeba2833584155605b5d9e8c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test membership in a finite or overflow-capped threshold interval. |
| inputs / outputs | A positive degree belongs when low&lt;=degree and it is below a finite high, or high is mathematical infinity. |
| invariants | An infinite lower threshold yields no representable members; degree zero remains absent. |
| ownership | No payload or iterator ownership. |
| failure | Noexcept comparisons. |
| cost | Fixed word tests. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0039

[Lines 225–238](../../../../../src/runtime/star_hindex.hpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L225-L238:sha256:99b7712e9b1332e989bd9fc1d45b45b8b7d0a54be6b1072da7842f9f80c19471
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count only occupied buckets in the changed threshold interval. |
| inputs / outputs | Find low, sum frequencies before high/end, then apply the virtual old/new incidence adjustment. |
| invariants | This is the mathematical threshold band, capped by the word domain; it is not a scan of all source keys. |
| ownership | Borrowed iterators require unchanged histogram ownership throughout preparation. |
| failure | Shared work refusal or checked count inconsistency propagates before any H mutation. |
| cost | One ordered lower_bound plus visited occupied buckets and constant adjustment; logarithmic comparisons and interval width are explicit. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0040

[Lines 239–249](../../../../../src/runtime/star_hindex.hpp#L239); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L239-L249:sha256:668e22a5898d2e87d8bd411c40281ec4762e1990e6b565851295e18fec5e1623
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare H state and qualify the threshold-span update cost. |
| inputs / outputs | Dimension, accounted Histogram and State close the exact H implementation. |
| invariants | d&gt;=2 interval width O_d((h+1)^(d-2)) is not universally O(1); infinity preserves the actual finite word domain. |
| ownership | The histogram owns its sparse bucket nodes under the original account. |
| failure | Ordinary member destruction releases buckets; it is not a query update or another work grant. |
| cost | Retained space is occupied degree buckets; ordered/scalar/account and teardown costs remain additional. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 5.1 (PDF p16)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §6](../../../../../build/verification/v68-star-proof-v1/audit.txt) |
