# `include/crown/resource/owner_text.hpp` — block usage map

[Source](../../../../../../include/crown/resource/owner_text.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Fund native owners and nested storage from one finite requested-byte account.

Snapshot SHA-256: `6374d6f8afcad532495766c8168416b4c2da9b66e8154dfc6a45c1afbd8263a0`. 24 lines partitioned into 4 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [memory](../../../../subsystem_contracts.md#memory). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/memory_reports.md](../../../../../memory_reports.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../../include/crown/resource/owner_text.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Reading native result text beside a caller string never needs an owning · [reviewed contract](#b0001) |
| [B0002 · 14–18](../../../../../../include/crown/resource/owner_text.hpp#L14) | Callable definition: template&lt;class Traits,class Allocator&gt; requires (!std::same_as&lt;Allocator,OwnerAllocator&lt;char&gt;&gt;) \[\[nodiscard\]\] bool operator==(con… | calls size; returns std::basic_string_view&lt;char,Traits&gt;(left.data(),left.size())==std::basic_string_view&lt;char,Traits&gt;(r…; source comment (unverified): // Reading native result text beside a caller string never needs an owning · [reviewed contract](#b0002) |
| [B0003 · 19–23](../../../../../../include/crown/resource/owner_text.hpp#L19) | Callable definition: template&lt;class Traits,class Allocator&gt; requires (!std::same_as&lt;Allocator,OwnerAllocator&lt;char&gt;&gt;) \[\[nodiscard\]\] auto operator&lt;=&gt;(co… | calls size; returns std::basic_string_view&lt;char,Traits&gt;(left.data(),left.size())&lt;=&gt;std::basic_string_view&lt;char,Traits&gt;(… · [reviewed contract](#b0003) |
| [B0004 · 24–24](../../../../../../include/crown/resource/owner_text.hpp#L24) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::resource · [reviewed contract](#b0004) |

## B0001

[Lines 1–13](../../../../../../include/crown/resource/owner_text.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using OwnerText=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name a native result string whose account follows transferable container ownership. |
| inputs / outputs | OwnerText is basic_string&lt;char, char_traits&lt;char&gt;, OwnerAllocator&lt;char&gt;&gt;. |
| invariants | String backing allocation is charged when requested; allocator rebinding/propagation preserves the original account/purpose/attribution. Library small-string storage may avoid an allocation. |
| ownership | The string owns characters and an account-retaining allocator; a borrowed view must not outlive that string. |
| failure | Allocation/growth uses inherited resource failure behavior; comparison overloads below do not materialize an ordinary owning string. |
| cost | Copies/growth have ordinary string character/allocation costs; the alias adds no conversion wrapper or per-read allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

## B0002

[Lines 14–18](../../../../../../include/crown/resource/owner_text.hpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool operator==(const std::basic_string<char,Traits,OwnerAllocator<char>>& left,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare native result text with a same-traits caller string without exporting ownership. |
| inputs / outputs | OwnerAllocator-backed left string and another-allocator right string produce equality through two string_views. |
| invariants | The requires clause excludes an identical OwnerAllocator type; both byte ranges remain alive during comparison and retain their original allocators. |
| ownership | Views borrow string data only; no caller string, account or character storage is copied. |
| failure | The overload is noexcept; it provides no diagnostic/recovery wrapper. |
| cost | Length comparison plus at most the compared character span; no allocation by the adapter. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

## B0003

[Lines 19–23](../../../../../../include/crown/resource/owner_text.hpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] auto operator<=>(const std::basic_string<char,Traits,OwnerAllocator<char>>& left,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order native and caller strings through borrowed same-traits character ranges. |
| inputs / outputs | OwnerAllocator-backed left string and another-allocator right string return the string_view three-way comparison result. |
| invariants | No allocator conversion affects ordering. The comparison is lexicographic under the supplied Traits and includes explicit lengths. |
| ownership | Both data ranges remain borrowed from their live strings; no retained view escapes. |
| failure | The overload is noexcept; it does not allocate or translate failures. |
| cost | O(min(left length,right length)) worst-case character work plus length handling, with no owning conversion. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/owner_allocator.hpp](../../../../../../include/crown/resource/owner_allocator.hpp) |

## B0004

[Lines 24–24](../../../../../../include/crown/resource/owner_text.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:7567672dab57c42722d3b39b4b45d2fe8c5a88eb6ef0a643a7b5488aa659ec31
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::resource\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::resource\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::resource\` at its lexical source position in include/crown/resource/owner_text.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::resource\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
