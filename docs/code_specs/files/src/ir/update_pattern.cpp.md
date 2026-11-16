# `src/ir/update_pattern.cpp` — block usage map

[Source](../../../../../src/ir/update_pattern.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs.

Snapshot SHA-256: `3b1fbacbda590baa21515eacd06bfcc51c7e07da9f19ca43309677f7ea2578a6`. 144 lines partitioned into 26 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_identity.md](../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/ir/update_pattern.cpp#L1) | Imports dependencies; declares namespace scope. | source comment (unverified): // Charge deterministic construction work and payload before allocating. All · [reviewed contract](#b0001) |
| [B0002 · 8–18](../../../../../src/ir/update_pattern.cpp#L8) | Type/record definition: struct Budget | source comment (unverified): // Charge deterministic construction work and payload before allocating. All · [reviewed contract](#b0002) |
| [B0003 · 19–24](../../../../../src/ir/update_pattern.cpp#L19) | Callable definition: template&lt;class T&gt; void reserve(detail::Vector&lt;T&gt;& values, std::size_t count, Budget& budget) | calls Failure, cells, bytes; growth reserve · [reviewed contract](#b0003) |
| [B0004 · 25–29](../../../../../src/ir/update_pattern.cpp#L25) | Closes surrounding scope/type. | source comment (unverified): // Canonicalize R rules in O(R log R) comparisons and O(R) retained cells. · [reviewed contract](#b0004) |
| [B0005 · 30–58](../../../../../src/ir/update_pattern.cpp#L30) | Callable definition: Declaration detail::Factory::make(const resource::MemoryAccount& account, std::array&lt;char, 64&gt; source, std::uint64_t tables, std:… | calls require, size, work, std::all_of; guard require(rules.size() &lt;= tables);; returns (c &gt;= @ && c &lt;= @ ) \|\| (c &gt;= @ && c &lt;= @ ); a.table &lt; b.table; growth make_accounted_shared, push_back, reserve; 2 loop sites; source comment (unverified): // Canonicalize R rules in O(R log R) comparisons and O(R) retained cells. · [reviewed contract](#b0005) |
| [B0006 · 59–60](../../../../../src/ir/update_pattern.cpp#L59) | Explanatory comments or spacing. | source comment (unverified): // Read the existing immutable source digest; do not hash or clone the program. · [reviewed contract](#b0006) |
| [B0007 · 61–69](../../../../../src/ir/update_pattern.cpp#L61) | Callable definition: Declaration Declaration::capture(const resource::MemoryAccount& account, const CompiledProgram& source, std::span&lt;const TableRule… | calls detail::require, bool, physical_source_sha256, size; guard detail::require(bool(source));; returns detail::Factory::make(account, hash, source.source_catalog().tables.size(), rules, limits); source comment (unverified): // Read the existing immutable source digest; do not hash or clone the program. · [reviewed contract](#b0007) |
| [B0008 · 70–72](../../../../../src/ir/update_pattern.cpp#L70) | Callable definition: Declaration Declaration::import(const resource::MemoryAccount& account, const Record& record, const Limits& limits) | calls detail::Factory::make; returns detail::Factory::make(account, record.source_sha256, record.source_tables, record.rules, limits) · [reviewed contract](#b0008) |
| [B0009 · 73–76](../../../../../src/ir/update_pattern.cpp#L73) | Callable definition: Declaration Declaration::import(const resource::MemoryAccount& account, std::array&lt;char, 64&gt; hash, std::uint64_t tables, std::spa… | calls detail::Factory::make; returns detail::Factory::make(account, hash, tables, rules, limits) · [reviewed contract](#b0009) |
| [B0010 · 77–82](../../../../../src/ir/update_pattern.cpp#L77) | Callable definition: Usage Declaration::copy_usage() const noexcept | calls size; returns {}; {64 + count, count, sizeof(detail::Data) + count * sizeof(TableRule)}; source comment (unverified): // Construction already bounded this sum and count by uint64 payload/cell caps. · [reviewed contract](#b0010) |
| [B0011 · 83–85](../../../../../src/ir/update_pattern.cpp#L83) | Explanatory comments or spacing. | source comment (unverified): // Transfer validated metadata to a receiving account in O(R), without sorting · [reviewed contract](#b0011) |
| [B0012 · 86–96](../../../../../src/ir/update_pattern.cpp#L86) | Callable definition: Declaration detail::Factory::copy(const resource::MemoryAccount& account, const Declaration& source) | calls require, bool, copy_usage, reserve; guard require(bool(source));; returns Declaration(std::move(data)); growth insert, make_accounted_shared, reserve; source comment (unverified): // Transfer validated metadata to a receiving account in O(R), without sorting · [reviewed contract](#b0012) |
| [B0013 · 97–99](../../../../../src/ir/update_pattern.cpp#L97) | Callable definition: Declaration Declaration::copy_of(const resource::MemoryAccount& account, const Declaration& source) | calls detail::Factory::copy; returns detail::Factory::copy(account, source); growth copy_of · [reviewed contract](#b0013) |
| [B0014 · 100–100](../../../../../src/ir/update_pattern.cpp#L100) | Explanatory comments or spacing. |  |
| [B0015 · 101–109](../../../../../src/ir/update_pattern.cpp#L101) | Callable definition: Declaration Declaration::copy_of(const resource::MemoryAccount& account, const Declaration& source, const Limits& limits) | calls copy_usage, work, cells, bytes; returns detail::Factory::copy(account, source); growth copy_of · [reviewed contract](#b0015) |
| [B0016 · 110–111](../../../../../src/ir/update_pattern.cpp#L110) | Explanatory comments or spacing. | source comment (unverified): // Explicit external export: ordinary caller-owned allocation may throw. · [reviewed contract](#b0016) |
| [B0017 · 112–118](../../../../../src/ir/update_pattern.cpp#L112) | Callable definition: Record Declaration::export_record() const | calls detail::require, bool, reserve, size; guard detail::require(bool(data_));; returns result; growth push_back, reserve; 1 loop sites; source comment (unverified): // Explicit external export: ordinary caller-owned allocation may throw. · [reviewed contract](#b0017) |
| [B0018 · 119–124](../../../../../src/ir/update_pattern.cpp#L119) | Callable definition: bool Declaration::matches(const CompiledProgram& source) const noexcept | calls physical_source_sha256, size, std::equal, begin; returns false; hash.size() == data_-&gt;source.size() && std::equal(hash.begin(), hash.end(), data_-&gt;source.be… · [reviewed contract](#b0018) |
| [B0019 · 125–125](../../../../../src/ir/update_pattern.cpp#L125) | Callable definition: bool Declaration::constrained() const noexcept | calls ; returns data_ && data_-&gt;constrained · [reviewed contract](#b0019) |
| [B0020 · 126–126](../../../../../src/ir/update_pattern.cpp#L126) | Callable definition: std::uint64_t Declaration::source_tables() const noexcept | calls ; returns data_ ? data_-&gt;tables : 0 · [reviewed contract](#b0020) |
| [B0021 · 127–127](../../../../../src/ir/update_pattern.cpp#L127) | Callable definition: Usage Declaration::captured_usage() const noexcept | calls ; returns data_ ? data_-&gt;usage : Usage{} · [reviewed contract](#b0021) |
| [B0022 · 128–131](../../../../../src/ir/update_pattern.cpp#L128) | Callable definition: std::span&lt;const TableRule&gt; Declaration::rules() const & noexcept | calls data, size; returns data_ ? std::span&lt;const TableRule&gt;{data_-&gt;rules.data(), data_-&gt;rules.size()} : · [reviewed contract](#b0022) |
| [B0023 · 132–133](../../../../../src/ir/update_pattern.cpp#L132) | Explanatory comments or spacing. | source comment (unverified): // Logarithmic lookup, with no allocation. A processing visitor must charge its · [reviewed contract](#b0023) |
| [B0024 · 134–139](../../../../../src/ir/update_pattern.cpp#L134) | Callable definition: const TableRule* Declaration::find(TableId table) const & noexcept | calls std::lower_bound, begin, end; returns nullptr; rule.table &lt; id; source comment (unverified): // Logarithmic lookup, with no allocation. A processing visitor must charge its · [reviewed contract](#b0024) |
| [B0025 · 140–143](../../../../../src/ir/update_pattern.cpp#L140) | Callable definition: const std::array&lt;char, 64&gt;& Declaration::source_sha256() const & | calls detail::require, bool; guard detail::require(bool(data_));; returns data_-&gt;source · [reviewed contract](#b0025) |
| [B0026 · 144–144](../../../../../src/ir/update_pattern.cpp#L144) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::patterns · [reviewed contract](#b0026) |

## B0001

[Lines 1–7](../../../../../src/ir/update_pattern.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:df1576eb4f99a7fc48682607ff27276d65554faff162ff0de8989c3b532dfd48
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include the private declaration builder and compiled source metadata, then establish implementation scope. |
| inputs / outputs | Uses detail declarations and CompiledProgram physical source/catalog access. |
| invariants | Source binding is read from the existing compiler artifact; this translation unit does not hash or clone query bodies. |
| ownership | No ownership in include/namespace setup. |
| failure | No runtime failure path. |
| cost | Compile-time setup only. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 8–18](../../../../../src/ir/update_pattern.cpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L18:sha256:d1bf9c3b4326f342777b9d27c8b8f0fa0d454ffbf806ec3b5c9a4da2adb7a3d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track independent logical work, cell, and payload caps during declaration construction. |
| inputs / outputs | Budget owns Limits and Usage; add checks overflow/cap before increment; work/cells/bytes route to their respective Fault values. |
| invariants | The subtraction check avoids unsigned overflow and rejects before charging; counters model declared checkpoints/payload, not allocator framing. |
| ownership | Stack-local value; no account or heap owner. |
| failure | Throws Failure with the dimension’s fault before the corresponding state update. |
| cost | O(1) per charge; no allocation. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0003

[Lines 19–24](../../../../../src/ir/update_pattern.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L24:sha256:b464234b54c6e2b4506d7ad07231ee5fbc9425e415ac75bcd5dfe9d7dfb2db49
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve a declaration vector only after charging its logical cells and payload. |
| inputs / outputs | T-vector, requested count, Budget enter; checks count*sizeof(T), charges cells/bytes, then calls reserve. |
| invariants | Overflow or logical caps fail before reserve; the MemoryAccount remains an independent actual-allocation cap. |
| ownership | Container memory is funded by its bound OwnerAllocator account. |
| failure | Failure propagates as declaration limit; reserve may propagate account failure or std::bad_alloc. |
| cost | O(1) charging plus allocator reserve cost; charges count cells and count*sizeof(T) payload. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 25–29](../../../../../src/ir/update_pattern.cpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L29:sha256:99abce1f274164abdaae6581521623110efba43f2dc63d33bb5a4f6c67350584
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the canonical construction shape and failure boundary for Factory::make. |
| inputs / outputs | R rules are canonicalized by table ID; explicit IDs are compared directly with no group scratch directory. |
| invariants | Retain only O(R) rule cells; publish no Declaration until complete; local account owners unwind on failure without catch/retry. |
| ownership | Partial Data remains local to the supplied account and is released when construction exits unsuccessfully. |
| failure | Invalid declarations, logical caps, and account denial remain distinct existing failure paths. |
| cost | O(R log R) comparisons; O(R) retained cells; no FIFO group allocation. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0005

[Lines 30–58](../../../../../src/ir/update_pattern.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L58:sha256:f92e146ad269fd2eb178a65663ddb627ecbaa1e2bef432fdd3fda04647c7244b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate, canonicalize, and publish one immutable declaration. |
| inputs / outputs | Checks rule count against source tables, a 64-character lowercase hex digest, each table bound, and duplicate table IDs; receives span/rules and Limits. |
| invariants | Charges fixed digest work, per-rule work, vector cells/payload, and sort comparisons; constrained is true only for insertion-only or nonzero FIFO IDs. Sorting creates canonical table order while preserving raw IDs. |
| ownership | Creates account-funded Data and publishes a Declaration only after all checks, sort, and duplicate scan complete. |
| failure | Malformed shape throws invalid_declaration; budget limits throw the corresponding Failure; allocator failures propagate. No partially built handle escapes. |
| cost | O(R log R) comparisons, O(R) vector cells; no CapturedRule/groups/index or group scratch. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0006

[Lines 59–60](../../../../../src/ir/update_pattern.cpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L60:sha256:97c07d9c5169938e78f2299a883391b65f66dacfdd7db5651f362fd057d2f504
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clarify that capture reads the compiler’s existing source digest rather than rehashing or cloning the program. |
| inputs / outputs | The following capture method reads \`physical_source_sha256()\` and source catalog table count. |
| invariants | A declaration binds to the exact compiled artifact source identity; this is not row-history capture. |
| ownership | Program remains borrowed; declaration Data is funded by the supplied account. |
| failure | Empty source or malformed digest length is rejected by fixed declaration failure. |
| cost | One digest copy of 64 bytes and source table-count read, plus Factory costs. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0007

[Lines 61–69](../../../../../src/ir/update_pattern.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L69:sha256:d4d9abe06789219bf5c3e39e4ff67450dafe9d826869c619ac6fdffcd6f312cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture requested table rules against an actual CompiledProgram. |
| inputs / outputs | Requires a truthy source, copies its existing physical SHA-256 into a fixed array, checks its length, then calls Factory::make with source table count. |
| invariants | The method does not hash/recompile/clone the program; rules are declarations, not proof of an enforcement origin. |
| ownership | Returns account-owned immutable Declaration metadata. |
| failure | Invalid source/digest/shape, logical budget, or account allocation may fail before publication. |
| cost | Fixed 64-byte digest copy plus O(R log R) canonical construction. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0008

[Lines 70–72](../../../../../src/ir/update_pattern.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L72:sha256:e54f3985122ddd142fb55735be41dfdba30faae9a752fc52117d5ae961780bec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import an ordinary Record by applying the same canonical shape validation as capture. |
| inputs / outputs | Passes record digest, table count, and caller vector rules to Factory::make under the specified account/limits. |
| invariants | A shape-valid imported hash gains no source authority until \`matches(source)\` succeeds. |
| ownership | Imported immutable rule values are newly allocated in the supplied account; Record stays caller-owned. |
| failure | Invalid digest/table/rule or limits/account failure propagate through the existing builder path. |
| cost | O(R log R) for canonical sort and duplicate validation. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0009

[Lines 73–76](../../../../../src/ir/update_pattern.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L76:sha256:3377b0f7ac069f805a868e9df93253198aafc4242e70c3edfec719fd3fc97b99
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import canonicalizable declaration metadata directly from funded decoder scratch. |
| inputs / outputs | Borrow a hash value, source table count and rule span; return the existing Factory::make result under explicit limits/account. |
| invariants | Same shape/hash/table/duplicate/sort admission as Record import. No source-program or historical-compliance authority is inferred. |
| ownership | Input span is synchronous; returned immutable data owns its receiving-account copy. No ordinary Record vector is constructed. |
| failure | Existing Failure covers invalid declaration/logical caps; receiving allocation failures propagate with local cleanup. |
| cost | O(R log R) canonicalization and O(R) retained rule storage plus existing fixed source validation; allocator/framing costs are additional. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 77–82](../../../../../src/ir/update_pattern.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L82:sha256:0ad5727c87a1acbfd81d76ca9d90dbe713a7a082bd64269931eaf47f0c657d3e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the logical grant needed to copy an existing declaration. |
| inputs / outputs | Empty handle returns zero Usage; otherwise returns fixed 64+R work, R cells, and sizeof(Data)+R*sizeof(TableRule) payload. |
| invariants | The sum/count fit because successful construction already bounded them by uint64 payload/cell limits; this is a pre-admission description, not allocation. |
| ownership | Reads immutable original Data; returned Usage owns no memory. |
| failure | Noexcept; empty handles are supported. |
| cost | O(1) aside from reading R count; no allocation. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0011

[Lines 83–85](../../../../../src/ir/update_pattern.cpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L85:sha256:68c88deb445ea6c39072408fa26be51090cc5654369d129e875b5da5517f97e6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document copy as a receiving-account O(R) transfer that skips sorting and requires prior logical admission. |
| inputs / outputs | Factory::copy duplicates validated metadata and sorted rules into a different account. |
| invariants | Caller must pre-admit copy_usage; receiving allocator independently caps real bytes; raw scope IDs and order are preserved. |
| ownership | Source handle keeps original Data owner; new Data belongs to receiving account. |
| failure | Account allocation failure propagates; no catch/retry or partial new handle. |
| cost | O(R) copy, no O(R log R) re-sort and no group index. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0012

[Lines 86–96](../../../../../src/ir/update_pattern.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L86-L96:sha256:b6a18b3b41a7be9d68906cae591ad838f3d18f65c6db250fbd1516fc40a9c7e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy validated immutable declaration metadata into a receiving account. |
| inputs / outputs | Requires valid source; creates Data in receiving account, copies constrained/usage and inserts existing sorted rules. |
| invariants | Source is not mutated; source order is already canonical; copy usage reports the logical grant. |
| ownership | Returned Declaration shares only the new receiving-account Data; old handle still retains original owner. |
| failure | Invalid source throws Failure; reserve/insert may fail from account or ordinary allocator limits before publication. |
| cost | O(R) vector copy and O(1) fixed data; no sort/group scratch. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0013

[Lines 97–99](../../../../../src/ir/update_pattern.cpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L97-L99:sha256:e369aa3c8d4d0dadb895bd5ad170a13127409e2c5ef206046289e526cb471181
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the explicit receiving-account copy operation. |
| inputs / outputs | Delegates copy_of(account, source) directly to Factory::copy. |
| invariants | Does not share source Data; creates a separate immutable allocation funded by the requested account. |
| ownership | Returned handle owns the copied Data through shared_ptr. |
| failure | Propagates Factory validation/account failures. |
| cost | O(R), no re-sort. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0015

[Lines 101–109](../../../../../src/ir/update_pattern.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L109:sha256:53a154e4d158d01d4115511e4412048c01795d3648c01b473a48e83611851e76
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a validated declaration copy against finite receiving metadata limits. |
| inputs / outputs | Read copy_usage; debit work/cells/payload in a stack Budget, then delegate to Factory::copy. |
| invariants | Logical admission happens before new allocation. Invalid handles still fail factory validation; an allocator cap is separate from the logical payload grant. |
| ownership | Borrow the source; returned Data/rule vector are funded by the supplied receiving account. |
| failure | Existing Failure for limits/invalid handle and ordinary native allocation failures; no partial declaration or catch layer. |
| cost | Fixed admission checks plus O(R) copy and O(R) receiving storage; no re-sort or group scratch. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 110–111](../../../../../src/ir/update_pattern.cpp#L110); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L110-L111:sha256:1e48d4b395c239c18b60aa9d23674084e613f2014402ce153d6741052f69132b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clarify that external export allocates ordinary caller-owned storage and may throw. |
| inputs / outputs | The adjacent export_record builds a standard Record vector from immutable metadata. |
| invariants | Export is intentionally outside query-account admission and is not a bounded runtime snapshot/checkpoint token. |
| ownership | Result vector is owned by the caller and uses ordinary allocator. |
| failure | std::bad_alloc may propagate; invalid empty declaration uses Failure. |
| cost | O(R) copy work and caller-owned cells. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0017

[Lines 112–118](../../../../../src/ir/update_pattern.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L112-L118:sha256:a86e7b3dcf71d215ddd9a3abecd99ec7876db6f7290abad531fe87a843eb4fc5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export immutable declaration metadata to the ordinary Record DTO. |
| inputs / outputs | Requires nonempty Data; copies hash/table count, reserves rule count, then pushes every TableRule. |
| invariants | Export preserves canonical table order and raw scope IDs; it does not export a group index or enforcement history. |
| ownership | Returned vector belongs to the caller, not the query account. |
| failure | Invalid empty handle throws Failure; reserve/push may propagate std::bad_alloc. |
| cost | O(R) cells and copy work. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0018

[Lines 119–124](../../../../../src/ir/update_pattern.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L119-L124:sha256:c531ab2cbefa5095cd370126fe6a04c9c1bab83d19eddb72ff4bc6fb65e84715
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a Declaration’s source digest and source table count against a compiled program. |
| inputs / outputs | Returns false for empty handle/source; compares the existing physical digest length/bytes and catalog table count. |
| invariants | Both digest and table count must match; this is source binding only, not runtime compliance. |
| ownership | Borrows the program and immutable Data; no new owner. |
| failure | noexcept and allocation-free. |
| cost | O(64) digest comparison plus constant table-count comparison. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0019

[Lines 125–125](../../../../../src/ir/update_pattern.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L125-L125:sha256:cde8cbee594bf92cd79f64075746f56a9c89d595ba5617337bd42c5b4523b8c1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report whether a valid declaration handle requests any insertion-only or FIFO condition; an invalid handle returns false. |
| inputs / outputs | Returns data_ && data_-&gt;constrained. |
| invariants | Empty declaration is false; scope IDs are preserved without grouping or scope remapping. |
| ownership | Reads immutable Data only. |
| failure | noexcept. |
| cost | O(1), no allocation. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 126–126](../../../../../src/ir/update_pattern.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L126-L126:sha256:600f900e54b32578f63d469557afb53727eb84fd20e940008156811517e423c3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the declared source-table count or zero for an empty handle. |
| inputs / outputs | Returns data_-&gt;tables when present, otherwise zero. |
| invariants | The count is source catalog metadata, not number of constrained rules. |
| ownership | Reads immutable Data only. |
| failure | noexcept. |
| cost | O(1). |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0021

[Lines 127–127](../../../../../src/ir/update_pattern.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L127-L127:sha256:d5167df1ab01756f7c4d278e327fa519f4265485657416176ddb7cc9e56c8cab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return successful capture usage or zero for an empty handle. |
| inputs / outputs | Returns stored Data::usage or default Usage. |
| invariants | Reports declaration construction charges, not future analysis, copy, or allocator framing. |
| ownership | Reads immutable Data only. |
| failure | noexcept. |
| cost | O(1). |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0022

[Lines 128–131](../../../../../src/ir/update_pattern.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L128-L131:sha256:5d5fa0dbd47291a1c18cf7672dd8ab3a50c2b6c3989b3469e55dcc36d3c32568
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return an lvalue-borrowed span over the canonical TableRule vector. |
| inputs / outputs | Returns the immutable rule vector span or an empty span when Data is absent. |
| invariants | Rules are sorted by table and preserve exact raw FIFO IDs; caller may not outlive/destroy the Declaration handle while using the view. |
| ownership | Span borrows Data held by the original account through this handle. |
| failure | noexcept; rvalue view overload is deleted in the public header. |
| cost | O(1), no allocation. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0023

[Lines 132–133](../../../../../src/ir/update_pattern.cpp#L132); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L132-L133:sha256:9b44f6278da0eab643398dd0f91cb5e78868a071a914455fe9028aca62e1e3ce
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document logarithmic, allocation-free table lookup and the need for consumers to charge their own comparisons. |
| inputs / outputs | The following find method performs lower_bound on the canonical vector. |
| invariants | IR find does not consume planner Budget; planner’s own visitor charges each comparator. |
| ownership | Borrowed result points into Declaration-owned immutable Data. |
| failure | No allocation/failure path for lookup. |
| cost | O(log R) comparisons, no scratch index. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0024

[Lines 134–139](../../../../../src/ir/update_pattern.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L134-L139:sha256:241f5823e8767af4e5ed2fb2ccb06e2eedf0037da5850cac7f130b9991a0e313
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find one rule by TableId in the sorted canonical rules. |
| inputs / outputs | Returns pointer to matching TableRule or nullptr; empty declaration returns nullptr. |
| invariants | Correctness relies on Factory’s sort and unique-table validation; the pointer borrows the Declaration. |
| ownership | Pointer lifetime is bounded by the lvalue Declaration handle; rvalue overload is deleted. |
| failure | noexcept and allocation-free. |
| cost | O(log R), no derived index. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0025

[Lines 140–143](../../../../../src/ir/update_pattern.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L140-L143:sha256:e657fe2ae1b1e937517fd2030858ca7dfa6aa7f6515c8ad350c3dec032095f74
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a borrowed reference to the source digest for a valid lvalue handle. |
| inputs / outputs | Requires Data; returns const array&lt;char,64&gt;&. |
| invariants | Digest lifetime is tied to Declaration; temporary-handle overload is deleted. |
| ownership | Reference borrows the account-funded immutable Data. |
| failure | Empty handle throws fixed invalid_declaration Failure. |
| cost | O(1), no allocation. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0026

[Lines 144–144](../../../../../src/ir/update_pattern.cpp#L144); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L144-L144:sha256:e91c78741d2badb3befbf1c91d734c67e3539a976f33bd77eb7e4f93fb088066
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the implementation namespace after declaration definitions. |
| inputs / outputs | No values enter or leave. |
| invariants | Namespace close carries no API or runtime claim. |
| ownership | No ownership effect. |
| failure | No failure path. |
| cost | No runtime cost. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |
