# `src/runtime/star_detail.hpp` — block usage map

[Source](../../../../../src/runtime/star_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Own accounted star records, sparse degree links, per-group projections and touched-record inverse journal primitives.

Snapshot SHA-256: `e5b752e00a03e44f2f8797519c5a3bdb581d0509bcfa998766e0fe4093c93d4c`. 229 lines partitioned into 32 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [star](../../../subsystem_contracts.md#star). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../src/runtime/star_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 16–19](../../../../../src/runtime/star_detail.hpp#L16) | Callable definition: template&lt;class T&gt; auto allocator(const resource::MemoryAccount& account, resource::MemoryPurpose purpose = resource::MemoryPurpos… | calls ; returns resource::MemoryAllocator&lt;T&gt;(account, purpose, memory) · [reviewed contract](#b0002) |
| [B0003 · 20–22](../../../../../src/runtime/star_detail.hpp#L20) | Callable definition: inline void require(bool value, const char* message) | calls Error; guard inline void require(bool value, const char* message) { · [reviewed contract](#b0003) |
| [B0004 · 23–30](../../../../../src/runtime/star_detail.hpp#L23) | Type/record definition: struct Budget |  · [reviewed contract](#b0004) |
| [B0005 · 31–36](../../../../../src/runtime/star_detail.hpp#L31) | Type/record definition: struct RowLess | returns a.view() &lt; b.view(); a.view() &lt; b · [reviewed contract](#b0005) |
| [B0006 · 37–37](../../../../../src/runtime/star_detail.hpp#L37) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 38–40](../../../../../src/runtime/star_detail.hpp#L38) | Callable definition: template&lt;class T&gt; Set&lt;T&gt; set(const resource::MemoryAccount& account) | calls ; returns Set&lt;T&gt;(std::less&lt;T*&gt;{}, allocator&lt;T*&gt;(account)) · [reviewed contract](#b0007) |
| [B0008 · 41–42](../../../../../src/runtime/star_detail.hpp#L41) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0008) |
| [B0009 · 43–45](../../../../../src/runtime/star_detail.hpp#L43) | Callable definition: template&lt;class V&gt; Rows&lt;V&gt; rows(const resource::MemoryAccount& account) | calls ; returns Rows&lt;V&gt;(RowLess{}, allocator&lt;std::pair&lt;const storage::AccountedRow, V&gt;&gt;(account)) · [reviewed contract](#b0009) |
| [B0010 · 46–52](../../../../../src/runtime/star_detail.hpp#L46) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 53–60](../../../../../src/runtime/star_detail.hpp#L53) | Type/record definition: struct Fact | source comment (unverified): // Own map key, stable until journal retirement. · [reviewed contract](#b0011) |
| [B0012 · 61–71](../../../../../src/runtime/star_detail.hpp#L61) | Type/record definition: struct Key | source comment (unverified): // One typed cell in the owning key map. · [reviewed contract](#b0012) |
| [B0013 · 72–82](../../../../../src/runtime/star_detail.hpp#L72) | Type/record definition: struct Group | 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 83–85](../../../../../src/runtime/star_detail.hpp#L83) | Explanatory comments or spacing. | source comment (unverified): // The degree directory owns only one head/count per OCCUPIED positive degree. · [reviewed contract](#b0014) |
| [B0015 · 86–86](../../../../../src/runtime/star_detail.hpp#L86) | Type/record definition: struct Bucket | source comment (unverified): // The degree directory owns only one head/count per OCCUPIED positive degree. · [reviewed contract](#b0015) |
| [B0016 · 87–88](../../../../../src/runtime/star_detail.hpp#L87) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0016) |
| [B0017 · 89–103](../../../../../src/runtime/star_detail.hpp#L89) | Type/record definition: struct Dimension |  · [reviewed contract](#b0017) |
| [B0018 · 104–109](../../../../../src/runtime/star_detail.hpp#L104) | Explanatory comments or spacing. | source comment (unverified): // One inverse journal covers only touched view records. Detached map nodes keep · [reviewed contract](#b0018) |
| [B0019 · 110–115](../../../../../src/runtime/star_detail.hpp#L110) | Type/record definition: struct ScalarUndo | source comment (unverified): // One inverse journal covers only touched view records. Detached map nodes keep · [reviewed contract](#b0019) |
| [B0020 · 116–130](../../../../../src/runtime/star_detail.hpp#L116) | Type/record definition: template&lt;class C&gt; struct EditUndo | growth insert; source comment (unverified): // Later extraction undo has restored this exact node. Its pointers are · [reviewed contract](#b0020) |
| [B0021 · 131–134](../../../../../src/runtime/star_detail.hpp#L131) | declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;Undo&gt;); · [reviewed contract](#b0021) |
| [B0022 · 135–137](../../../../../src/runtime/star_detail.hpp#L135) | Callable definition: public: Journal(const resource::MemoryAccount& account, Budget& budget) : entries_(allocator&lt;Undo&gt;(account, resource::MemoryPurpo… | calls entries_, budget_ · [reviewed contract](#b0022) |
| [B0023 · 138–141](../../../../../src/runtime/star_detail.hpp#L138) | Callable definition: ~Journal() | calls rbegin, rend, std::visit, rollback; 1 loop sites · [reviewed contract](#b0023) |
| [B0024 · 142–143](../../../../../src/runtime/star_detail.hpp#L142) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0024) |
| [B0025 · 144–144](../../../../../src/runtime/star_detail.hpp#L144) | Callable definition: void commit() noexcept | calls  · [reviewed contract](#b0025) |
| [B0026 · 145–153](../../../../../src/runtime/star_detail.hpp#L145) | Callable definition: template&lt;class T&gt; void assign(T& target, T value) | calls static_assert, prepare, std::memcpy, data; guard static_assert(std::is_trivially_copyable_v&lt;T&gt; && sizeof(T) &lt;= 16);; growth emplace_back · [reviewed contract](#b0026) |
| [B0027 · 154–164](../../../../../src/runtime/star_detail.hpp#L154) | Callable definition: template&lt;class C, class... Args&gt; typename C::iterator emplace(C& container, Args&&... args) | calls pending, key_comp, get_allocator, extract; guard require(inserted.inserted, "duplicate private index insertion");; returns inserted.position; growth emplace, emplace_back, insert; source comment (unverified): // Prepare both node and journal capacity before the no-fail insertion. · [reviewed contract](#b0027) |
| [B0028 · 165–170](../../../../../src/runtime/star_detail.hpp#L165) | Callable definition: template&lt;class C&gt; void erase(C& container, typename C::iterator position) | calls require, end, prepare, extract; guard require(position != container.end(), "missing private index removal");; growth emplace_back · [reviewed contract](#b0028) |
| [B0029 · 171–179](../../../../../src/runtime/star_detail.hpp#L171) | Callable definition: private: void prepare() | calls take, size, capacity, Error; growth reserve · [reviewed contract](#b0029) |
| [B0030 · 180–186](../../../../../src/runtime/star_detail.hpp#L180) | declares values/defaults or compile-time conditions. | source comment (unverified): // Borrowed scalar/pointer buffers are reused across all rows of one input. · [reviewed contract](#b0030) |
| [B0031 · 187–197](../../../../../src/runtime/star_detail.hpp#L187) | Type/record definition: struct Scratch | growth reserve; source comment (unverified): // Borrowed scalar/pointer buffers are reused across all rows of one input. · [reviewed contract](#b0031) |
| [B0032 · 198–229](../../../../../src/runtime/star_detail.hpp#L198) | declares namespace scope; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime::star::detail · [reviewed contract](#b0032) |

## B0001

[Lines 1–15](../../../../../src/runtime/star_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:a19edc55b57d76bfe529daafb15b22a7f13cabe9a94de087576a0c66f22fb1b4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind private star records and helpers to the public API and one attribution. |
| inputs / outputs | The header includes runtime/H definitions, defines support_node:0 attribution and an accounted Vector alias. |
| invariants | It is private implementation metadata; no alternate query account or public plan authority is constructed. |
| ownership | Each later allocator explicitly receives the original account. |
| failure | Normal declaration/include errors are compile-time; native construction owns its later refusal boundary. |
| cost | Header/type setup only; actual container allocations are charged where constructed. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0002

[Lines 16–19](../../../../../src/runtime/star_detail.hpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L19:sha256:3fa38d24c65ca11170761bd881339962ac6fc39c0ef9fd62b67be5ecffd0b3b1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a typed star allocator on the original account. |
| inputs / outputs | Account and purpose return MemoryAllocator&lt;T&gt; with the private star attribution. |
| invariants | Rebinding preserves account/purpose/attribution rather than borrowing an unaccounted default allocator. |
| ownership | The allocator shares the supplied account control. |
| failure | Invalid account/purpose fails through the existing allocator contract. |
| cost | Fixed allocator construction; allocation/account cost occurs at container growth. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0003

[Lines 20–22](../../../../../src/runtime/star_detail.hpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L22:sha256:1231d0179f8a9e66bb561ff67e9b7aa5a86dc022e498247779a31b6e1bd05054
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report a failed internal star invariant. |
| inputs / outputs | A false predicate throws Error(star_invariant, message). |
| invariants | Diagnostics occur before the owning operation publishes its epoch. |
| ownership | The exception message is external diagnostic ownership, not retained view payload. |
| failure | The error propagates to existing private journal/source rollback. |
| cost | Constant success check; failure text/exception allocation remains additional. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0004

[Lines 23–30](../../../../../src/runtime/star_detail.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L30:sha256:f889de7ca161e9f83d60332b72d7b42ef0bd92db9e7e56affedfe0d621d3afa3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spend one balance across all heavy/light edits in an input. |
| inputs / outputs | Budget borrows the operation Metrics and immutable work limit; take increments selected work. |
| invariants | Metrics starts at zero and each take checks equality before increment, including UINT64_MAX limit. |
| ownership | No counter/limit account is minted; all nested helpers share this Budget reference. |
| failure | Exhaustion raises star_work_limit before the next selected mutation is prepared. |
| cost | One comparison/increment per selected action; dictionary/scalar/allocation work is not a CPU bound. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0005

[Lines 31–36](../../../../../src/runtime/star_detail.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L36:sha256:b45dc51f032bbdf7f90eb842085b119e767fd354a3f77fc43da7400c9b0688b6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare owned star map keys with borrowed row probes. |
| inputs / outputs | RowLess overloads compare AccountedRow/RowView value sequences transparently. |
| invariants | Stored keys are immutable canonical native cells; layout ownership/address does not determine row equality. |
| ownership | Lookup borrows keys/views without copying strings or allocating a probe row. |
| failure | The native-view comparisons are noexcept for admitted cells. |
| cost | Lexicographic typed/scalar/string comparison cost and ordered-map factors remain real. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0006

[Lines 37–37](../../../../../src/runtime/star_detail.hpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L37:sha256:aefd426c1d2d8f602a5ab1923a49546e0cf96074341e5b38609f8169c7bb8055
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare accounted nonowning reverse pointer sets. |
| inputs / outputs | Set&lt;T&gt; maps stable T pointers through std::less&lt;T*&gt;. |
| invariants | Targets are owned by fact/key/group maps and stay resident when dereferenced. |
| ownership | Set nodes own pointer values, not the pointed-to records. |
| failure | Container allocation fails through its supplied allocator when an insertion is prepared. |
| cost | Ordered pointer comparisons plus one accounted node per membership. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0007

[Lines 38–40](../../../../../src/runtime/star_detail.hpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L40:sha256:a22e4dacb54431d27da019e739a91d34434501d24ffc35a3247430fc02c0d046
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an empty reverse-pointer index on the original account. |
| inputs / outputs | set&lt;T&gt;(account) returns the correct comparator and allocated-node policy. |
| invariants | It never substitutes a default unaccounted pointer set. |
| ownership | The returned set retains only its allocator until memberships are inserted. |
| failure | Invalid allocator admission propagates before publication. |
| cost | Fixed container construction; later membership edits pay map/tree costs. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0008

[Lines 41–42](../../../../../src/runtime/star_detail.hpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L42:sha256:4e3aa6dd253f06ecae59255488eefab8e3e166aa15eeccd68085f5615e580125
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare owning compact-row dictionaries with transparent lookup. |
| inputs / outputs | Rows&lt;V&gt; is an accounted map from AccountedRow to the private value type V. |
| invariants | Value-based RowLess permits borrowed probes; stored row bytes remain immutable. |
| ownership | Each key owns its native scalar payload; map nodes share the original account. |
| failure | Node/key allocation may refuse during private insertion. |
| cost | Ordered-map structure and retained payload width are actual space/time costs. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0009

[Lines 43–45](../../../../../src/runtime/star_detail.hpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L45:sha256:91656b5feebc7b3319adf380784c3dd02a806531e9a0c0354046f0f3aa5ab23a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty compact-row dictionary with the native allocator. |
| inputs / outputs | rows&lt;V&gt;(account) returns a map using RowLess and support-metadata attribution. |
| invariants | Nested V members still require their own explicit account constructors. |
| ownership | Only allocator/control state is retained before first insertion. |
| failure | Allocator contract errors propagate without changing the view. |
| cost | Fixed setup; no source or result scan. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0010

[Lines 46–52](../../../../../src/runtime/star_detail.hpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L52:sha256:a26eac2f2a3658064b49cad1d9b821d5a7e24b6f208a930a458aaf9b6b6810da
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the independent fact/key/group/projection map types. |
| inputs / outputs | Forward declarations and aliases associate owned rows with Fact, Key, Group or support counts. |
| invariants | A projected count is center-row support for set output, not general bag execution. |
| ownership | Aliases themselves acquire no storage or authority. |
| failure | Type/declaration errors remain compile-time. |
| cost | No runtime work. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0011

[Lines 53–60](../../../../../src/runtime/star_detail.hpp#L53); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L60:sha256:cca358a9f814ea9e6089774cf4435398e45dc1cc441725d81deec129c82f2597
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one center fact and its current light-filter/group membership. |
| inputs / outputs | Fact stores its owning map-key address, per-coordinate Key pointers, missing-light count and optional Group pointer. |
| invariants | A fact contributes to a group exactly when no light predicate is missing; pointers are used only while records are resident. |
| ownership | Its coordinate vector is funded on the original account; map ownership supplies immutable center row bytes. |
| failure | Vector construction may refuse before the new fact node joins maintained state. |
| cost | O(d) pointer storage per center row; group/projection ownership is separate. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 61–71](../../../../../src/runtime/star_detail.hpp#L61); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L71:sha256:8473d9a5da956c7e1b4b1e13a201b5a5268eb2281a563246584ffeb24c79db19
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Maintain one coordinate key, real/conceptual presence and reverse memberships. |
| inputs / outputs | Key stores degree, label, presence, intrusive degree links, incident facts and referenced heavy groups. |
| invariants | Positive degree equals incident fact count. The heavy flag and Dimension::heavy mirror each other at committed boundaries. |
| ownership | The key map owns its one-cell row; pointer sets and links borrow stable resident fact/group/key records. |
| failure | Accounted reverse-set insertion can fail inside the shared journal boundary. |
| cost | Fixed key metadata plus actual incident memberships; string payloads are copied only by the owning key row. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 72–82](../../../../../src/runtime/star_detail.hpp#L72); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L72-L82:sha256:8f9265b5743a2c7cfeedee7c11eaa97565629aad1fb1b391706b9e4f52d0479e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one light-filtered heavy-coordinate group and counted head projections. |
| inputs / outputs | Group owns a heavy-key vector, projected support dictionary, total support and missing-heavy count. |
| invariants | All rows in the group share heavy coordinates; missing-heavy state decides liveness, independently of projection support counts. |
| ownership | Heavy pointers borrow dimension keys; vector and projected row/count nodes use the original account. |
| failure | Private constructor allocations can fail before journal insertion; existing state is unchanged. |
| cost | O(number of heavy coordinates) setup and retained distinct projections; no eager global answer union. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 83–85](../../../../../src/runtime/star_detail.hpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L85:sha256:b8105a377fecb5bcea2aef4b174515516576e5301cf8a643bd0c2c25ae883d3c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the sparse positive-degree directory. |
| inputs / outputs | The following Bucket and Buckets organize coordinate keys by occupied degree. |
| invariants | A reset may enumerate its relevant degree interval without visiting unrelated low keys or unchanged heavy row buckets. |
| ownership | Intrusive Key links supply membership without an extra list allocation per link. |
| failure | Actual directory edits remain journaled and fallible during preparation. |
| cost | Space follows occupied degrees plus existing key links, not a dense maximum-degree array. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 86–86](../../../../../src/runtime/star_detail.hpp#L86); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L86-L86:sha256:174a43d70a6cf394b2a896deb2f7ef9b219e87eda64df24583e408264612ffaa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one occupied degree bucket by a linked-list head and count. |
| inputs / outputs | Bucket contains a resident Key head pointer and membership count. |
| invariants | A committed bucket has positive degree/count and correctly linked keys. |
| ownership | The directory owns this descriptor; Key maps own the records it links. |
| failure | No allocation occurs in the inline value itself. |
| cost | Two scalar fields; enumeration pays one visit per selected key. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0016

[Lines 87–88](../../../../../src/runtime/star_detail.hpp#L87); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L87-L88:sha256:8f0d93654ee8dc74fb25d6c09f6709857bf481972689cc4fbf0d5d3515c750c8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the accounted ordered degree-bucket directory. |
| inputs / outputs | Buckets maps a positive uint64 degree to its Bucket descriptor. |
| invariants | Zero-degree entries are omitted and empty buckets are reclaimed. |
| ownership | Directory nodes retain the supplied original account. |
| failure | Growth/removal is staged through the inverse journal. |
| cost | Logarithmic degree lookup and occupied-node space. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 89–103](../../../../../src/runtime/star_detail.hpp#L89); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L103:sha256:e1649bb10d65928e0ea63904880c3b4186e97096cbcf80221813958805123643
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one complete coordinate degree/label state. |
| inputs / outputs | Dimension owns key map, degree buckets, heavy pointer set, exact H tracker, scale, threshold and real-satellite flag. |
| invariants | Initial scale is one and threshold is 2^(d-1), using explicit infinity on overflow; H starts empty. |
| ownership | All containers/H nodes share the original account. The type can move only between operations without live H tokens. |
| failure | Container/H construction refusal unwinds private members; no coordinate state is published. |
| cost | Fixed initial descriptors and O(keys+degrees+memberships) retained state; the d1 threshold uses exponent zero. |
| Design | [docs/star.md](../../../../star.md), [P2 arXiv:2603.14754v1 Definition 4.5 and section 5.2 (PDF pp14,16–18)](https://arxiv.org/pdf/2603.14754v1), [build/verification/v68-star-proof-v1/audit.txt §5–7](../../../../../build/verification/v68-star-proof-v1/audit.txt), [docs/query_memory.md](../../../../query_memory.md) |

## B0018

[Lines 104–109](../../../../../src/runtime/star_detail.hpp#L104); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L104-L109:sha256:b583d4f8755d8db20f09a15c3fa42a94cf792f4ce4f7ef66ea2afa5d14f3cb35
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain stable-value insertion undo and touched-state rollback. |
| inputs / outputs | Comment separates detached erased nodes, stable inserted value/key pointers and trivially copied scalar inverses. |
| invariants | Later extraction undo restores a node before insertion undo obtains a fresh lookup; stale iterators are not reused. |
| ownership | Undo entries live in one accounted vector; target-node allocations remain their actual separate cost. |
| failure | Reverse rollback requires validated same-allocator containers and nonthrowing native comparisons/deallocation. |
| cost | No full view copy or per-record virtual undo object; vector capacity, comparisons and target nodes still cost work/bytes. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0019

[Lines 110–115](../../../../../src/runtime/star_detail.hpp#L110); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L110-L115:sha256:cd9571c5cf6cd4176879b4e4cc73fe0b557cea70f8cff2554ed1309800c45f1f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Save and restore one small scalar/link object representation. |
| inputs / outputs | ScalarUndo holds a target, up to16 saved bytes and exact copy width; rollback memcpy restores those bytes. |
| invariants | Journal::assign admits only trivially copyable types no larger than the buffer, while reverse ordering preserves target residency. |
| ownership | The record borrows its target; journal/node handles retain any enclosing erased payload until restoration. |
| failure | Valid rollback is noexcept and allocates nothing. |
| cost | Fixed bounded memcpy; no source scan or auxiliary allocation. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0020

[Lines 116–130](../../../../../src/runtime/star_detail.hpp#L116); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L116-L130:sha256:ac5338f1c5fd6bea66792dbae3c1dbd8bed1b194f93ac8bd4f54ab509b51b9e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Undo one container insertion or extraction using correct node lifetime. |
| inputs / outputs | EditUndo retains container plus stable inserted value pointer or an extracted node; rollback erases a fresh lookup or reinserts the node. |
| invariants | Reverse later extraction first restores an inserted node. Its old iterators remain invalid, so lookup uses restored immutable key/value. |
| ownership | Erased payload is owned by node handle with its original allocator; insertion undo borrows the restored resident value. |
| failure | Valid native comparator/equal-allocator rollback is noexcept and needs no allocation; it is not a general arbitrary-container undo API. |
| cost | One ordered find/erase for insertion inverse or node reinsertion for extraction inverse, plus real scalar comparisons/deallocation. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0021

[Lines 131–134](../../../../../src/runtime/star_detail.hpp#L131); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L131-L134:sha256:96f0659dc9cccf942f1e3a490fa5570269a5cbab93cc1615c307d4efe6377cff
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate the concrete journal inverse variants. |
| inputs / outputs | Undo covers ScalarUndo and fact/key/group/projection/degree/pointer-set EditUndo records. |
| invariants | The static assertion requires nonthrowing variant move, enabling funded vector publication without another failure point. |
| ownership | Each alternative owns only its described detached node or borrowed target metadata. |
| failure | An added alternative that could throw on move must fail the compile-time boundary. |
| cost | Fixed variant slot per prepared inverse; no virtual dispatch or standalone per-inverse heap object. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0022

[Lines 135–137](../../../../../src/runtime/star_detail.hpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L137:sha256:57153b6effeafc74c45ba71387da9c7acd40080e10f8b27c5f78ed2fb1bcefda
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a private touched-view journal sharing the operation budget. |
| inputs / outputs | Original account and Budget reference construct the inverse vector with journal_undo purpose. |
| invariants | The journal starts active and is neither copied nor independently budgeted. |
| ownership | Vector capacity is accounted; the borrowed Budget must outlive journal destruction. |
| failure | Allocator admission can fail before any journaled mutation. |
| cost | Fixed setup; later inverse capacity grows geometrically. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0023

[Lines 138–141](../../../../../src/runtime/star_detail.hpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L138-L141:sha256:5d5b14c1f1bccc1e3638473e2cd9de65bc3a0ee257715e4465fb969e1b14355e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rollback all unpublished view edits in reverse order on scope exit. |
| inputs / outputs | An active Journal visits inverse entries from newest to oldest. |
| invariants | Later node extraction inverses restore residency before earlier value/scalar inverses use those addresses. |
| ownership | Detached nodes and private vector storage remain owned until member destruction after rollback. |
| failure | Valid inverse operations are noexcept and allocate nothing; no catch/retry layer is used. |
| cost | O(number of inverse entries) dispatch plus each inverse map lookup/reinsertion and release cost. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0024

[Lines 142–143](../../../../../src/runtime/star_detail.hpp#L142); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L142-L143:sha256:f8d83942b82a256fba4d03832f600c33833fc24faa287c44b1da90d770285779
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent duplicate ownership of one undo transaction. |
| inputs / outputs | Journal copy constructor and copy assignment are deleted. |
| invariants | Only one active journal owns and executes a given inverse sequence. |
| ownership | Vector storage and borrowed Budget remain with their original journal object. |
| failure | Invalid copying fails compilation. |
| cost | No runtime work. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0025

[Lines 144–144](../../../../../src/runtime/star_detail.hpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L144-L144:sha256:c78ca09aa8c101d0bc5461cdc1f7434fcb36856c4dfe69863cc63ee36d93691f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the completed view edits by disarming rollback. |
| inputs / outputs | commit changes active_ to false after the source/H publication boundary. |
| invariants | All fallible view work has already completed; commit itself does not rebuild or replay changes. |
| ownership | Removed nodes retire when inverse entries are later destroyed through their original allocators. |
| failure | Noexcept scalar flag update. |
| cost | O(1) disarming; journal/node destruction still pays actual cleanup afterward. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0026

[Lines 145–153](../../../../../src/runtime/star_detail.hpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L145-L153:sha256:feb386cb6359ac8d4f61b34a6837a2885e2534fca7956ea22052c4bb222ffa1a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund and append a scalar inverse before changing its target. |
| inputs / outputs | assign skips an equal value, otherwise saves exact old bytes and writes the new value. |
| invariants | Trivially-copyable size&lt;=16 is enforced statically; vector capacity and selected work precede mutation. |
| ownership | The inverse borrows a resident target or a target retained/restored by node ownership ordering. |
| failure | Budget/capacity refusal happens before target assignment; older edits are reversed by journal destruction. |
| cost | Fixed comparison/copy plus amortized accounted vector growth; nested pointer/counter costs remain visible. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0027

[Lines 154–164](../../../../../src/runtime/star_detail.hpp#L154); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L154-L164:sha256:2b0fef778d88b3d37d4c9beb10095298b5548672d2a6ab1d9a465bf00e4358a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage one container node and its insertion inverse before publication. |
| inputs / outputs | emplace builds a detached node using the destination allocator, funds journal capacity, inserts it and records its stable value address. |
| invariants | The call expects a genuinely absent key; inverse variant insertion cannot throw after capacity is funded. |
| ownership | A private temporary owns the new node until successful insertion; the map then owns its key/payload. |
| failure | Node/allocation/work refusal preserves the previous edit prefix for rollback; duplicate private insertion is an invariant error. |
| cost | A target-node allocation, ordered insertion, and one inverse record; no view-wide copying. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0028

[Lines 165–170](../../../../../src/runtime/star_detail.hpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L165-L170:sha256:41d1357b0404dc1328b071b915d60dab5d9612bd75bd5859149c0afaf7325c7e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract one resident node while retaining its reinsertion inverse. |
| inputs / outputs | erase validates an iterator, funds journal capacity and appends the owned extracted node. |
| invariants | The node value is not dereferenced through earlier pointers while extracted; reverse undo restores it before earlier inverses run. |
| ownership | The journal node handle retains erased native payload and allocator until rollback/release. |
| failure | Work/capacity refusal precedes extraction. Valid extraction and nonthrowing record movement need no allocation. |
| cost | Ordered node extraction plus inverse storage; final node cleanup is real work. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0029

[Lines 171–179](../../../../../src/runtime/star_detail.hpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L171-L179:sha256:157babfbc840985c3f98c4b2ce5a951344cf484cb353f2bf7495642e850d2897
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one journal edit and reserve geometric inverse capacity. |
| inputs / outputs | prepare spends the shared Budget and doubles vector capacity from an initial16 slots when needed. |
| invariants | Capacity overflow is checked before doubling; no record/mutation is appended by this helper. |
| ownership | The vector grows on the original account with journal_undo purpose. |
| failure | Work, capacity-overflow or memory refusal leaves existing inverse entries intact for rollback. |
| cost | Selected charge plus actual amortized vector allocation/moves; memory growth is not free. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0030

[Lines 180–186](../../../../../src/runtime/star_detail.hpp#L180); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L180-L186:sha256:901d147260678f729be843c1393a19e26f35b2529151e7c4ba1c8eaa421606b7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one active inverse sequence and its operation balance. |
| inputs / outputs | Journal fields hold the inverse vector, borrowed Budget and active flag; the next comment introduces shared scratch. |
| invariants | Journal lifetime encloses all private edits and precedes source-token rollback on failure. |
| ownership | The vector owns records/node handles; the budget is borrowed and not another allowance. |
| failure | Member destruction releases inverse storage after active rollback or committed retirement. |
| cost | Space is proportional to touched edits/capacity, not a full maintained-state clone. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0031

[Lines 187–197](../../../../../src/runtime/star_detail.hpp#L187); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L187-L197:sha256:88a8b433335a339a8cfb5face0a41a2eadbe68ec673b02232587b47fa7e4c7fb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve reusable group/head/pointer scratch for one input operation. |
| inputs / outputs | Scratch allocates original-account ScalarView group/head vectors and heavy-Key pointers for d coordinates/output width. |
| invariants | Group capacity is 2*d after an overflow check; probes borrow cells and each retained map key later imports its own row. |
| ownership | Only vector capacity is owned; scalar strings and Key pointers borrow source/map payload during the private call. |
| failure | Arity overflow or reserve failure occurs within the source/journal rollback boundary. |
| cost | O(d+head width) scratch setup, reused across touched rows instead of per-row ordinary Row mirrors. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |

## B0032

[Lines 198–229](../../../../../src/runtime/star_detail.hpp#L198); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L198-L229:sha256:ec2bc0346ffc5256bbcb530fad4e96af8ca92d9263886f703e69eb784fa8d62f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the original-account runtime owner and its private maintenance operations. |
| inputs / outputs | Data owns original account/program, full-source coordinator, view work limit, coordinate/routes/head metadata, fact/group/live indexes, reader count and updating guard flag. |
| invariants | The updating guard spans source/H commitment and journal retirement. Imported comparison/schema metadata has a separate bounded cold IndexWork allowance; reader and source-ready checks protect mutable view reads. |
| ownership | Shared Data owns all nested original-account state and immutable imported mappings; its methods use borrowed private journals/tokens during one serial operation. |
| failure | Mutable source/view read access rejects the complete private writing interval; fallible construction/import and edits expose no partially published owner/epoch. |
| cost | O(d/catalog/head) fixed-query metadata plus actual maintained indexes and selected touched-state work. |
| Design | [docs/star.md](../../../../star.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../include/crown/resource/allocator.hpp) |
