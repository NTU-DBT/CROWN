# `include/crown/planner/meta.hpp` — block usage map

[Source](../../../../../../include/crown/planner/meta.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata.

Snapshot SHA-256: `1dccb3e7c43f177dd91487e11299444065a17e872b9ec6bb3669bc9ad0cde46b`. 53 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [planner](../../../../subsystem_contracts.md#planner). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/tree_plans.md](../../../../../tree_plans.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/planner/meta.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // P3 arXiv:2603.15465v2, Definition 4.3 and Algorithm 1 (PDF pp.10–12). · [reviewed contract](#b0001) |
| [B0002 · 13–18](../../../../../../include/crown/planner/meta.hpp#L13) | Type/record definition: struct Node | source comment (unverified): // P3 arXiv:2603.15465v2, Definition 4.3 and Algorithm 1 (PDF pp.10–12). · [reviewed contract](#b0002) |
| [B0003 · 19–22](../../../../../../include/crown/planner/meta.hpp#L19) | Type/record definition: struct Decomposition |  · [reviewed contract](#b0003) |
| [B0004 · 23–27](../../../../../../include/crown/planner/meta.hpp#L23) | Type/record definition: struct Limits |  · [reviewed contract](#b0004) |
| [B0005 · 28–31](../../../../../../include/crown/planner/meta.hpp#L28) | Type/record definition: struct Usage |  · [reviewed contract](#b0005) |
| [B0006 · 32–35](../../../../../../include/crown/planner/meta.hpp#L32) | Type/record definition: enum class Stop |  · [reviewed contract](#b0006) |
| [B0007 · 36–40](../../../../../../include/crown/planner/meta.hpp#L36) | Type/record definition: struct Build |  · [reviewed contract](#b0007) |
| [B0008 · 41–41](../../../../../../include/crown/planner/meta.hpp#L41) | Type/record definition: struct Check |  · [reviewed contract](#b0008) |
| [B0009 · 42–53](../../../../../../include/crown/planner/meta.hpp#L42) | declares values/defaults or compile-time conditions. | guard \[\[nodiscard\]\] Check check(const Catalog&, const Query&, const Decomposition&, Limits = {});; source comment (unverified): // Validation of Catalog/Query is existing allocating admission outside these · [reviewed contract](#b0009) |

## B0001

[Lines 1–12](../../../../../../include/crown/planner/meta.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:2c68e7da345fc12a8a0aa95aa608516c93ac703ef214c05d65b981c32043f951
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the cold-planning metadata namespace and the standard/recognizer types needed by its declarations. |
| inputs / outputs | Including this header makes Scope, optional indices, vector storage and meta declarations available to a C++ translation unit. |
| invariants | The include guard prevents repeated declarations. The introductory comments distinguish metadata from an executable CROWN tree and preserve occurrence identity. |
| ownership | These directives and namespace opening create no metadata owner or runtime allocation; ownership starts with the declared value types. |
| failure | Missing or incompatible dependent declarations are compile-time failures; this region has no runtime error path. |
| cost | Header parsing and dependent includes are build costs. This region performs no planner work and adds no per-update hook. |
| Design | [docs/meta_decompositions.md](../../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1) |

## B0002

[Lines 13–18](../../../../../../include/crown/planner/meta.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L18:sha256:58f418ebb622c8862f4d6e925d2c9caecb3796f729030165f60e58d62925365b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one physical occurrence or canonical minor with its scope, interface and optional parent. |
| inputs / outputs | occurrence is an original atom index when present, including index zero; scope is chi, interface is kappa, and parent indexes the same decomposition. |
| invariants | An admitted physical chi equals that occurrence scope; an absent occurrence denotes a minor even if its chi equals a physical scope. Raw values are unchecked until check succeeds. |
| ownership | Each Node owns its two ordered Scope sets. Optional indices are scalar values, not pointers or retaining capabilities. |
| failure | Aggregate construction can encode invalid indices or scopes intentionally; Scope allocation/copy failure propagates. Merely constructing Node does not validate it. |
| cost | Index access is fixed-size; copying/destroying scopes visits their members and can allocate/free set nodes. Node is metadata used during planning. |
| Design | [docs/meta_decompositions.md](../../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3) |

## B0003

[Lines 19–22](../../../../../../include/crown/planner/meta.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L22:sha256:4771b75a7d6bc04609aca77934c134bd57b8b286f2fa14386b0d01fab15cef0b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the full proposed metadata graph and identify its root by node index. |
| inputs / outputs | nodes stores Node values and root selects one element for a nonempty admitted decomposition. |
| invariants | A raw Decomposition is not a checked tree: one root, acyclic connected parent links, coverage and interfaces are established by check, not by the default root value. |
| ownership | The vector owns all nodes and their scopes. Copying duplicates their containers; moving transfers them; destruction releases the complete metadata graph. |
| failure | Default construction yields an empty proposal rather than a valid root. Container allocation/copy failure propagates; topology errors become checker rejection. |
| cost | Vector/index declarations are cheap; copying and last destruction scale with stored nodes and scope members. There is no runtime row state here. |
| Design | [docs/meta_decompositions.md](../../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3) |

## B0004

[Lines 23–27](../../../../../../include/crown/planner/meta.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L27:sha256:66063d6d241651195ddce16d5e67c81e2db759fa7d19cd4f067a49240dbcf943
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply finite grants for selected metadata work, resident decomposition nodes and cumulative explicit scope cells. |
| inputs / outputs | work and scope_cells are uint64 grants; nodes is a size_t grant. The listed defaults apply when the caller omits Limits. |
| invariants | Zero grants are real limits, not unlimited sentinels. These grants exclude allocating catalog/query admission and do not bound allocator bytes or total CPU. |
| ownership | Limits is a copyable scalar value; each API call copies it into its private Budget rather than sharing or refilling a global grant. |
| failure | Exhaustion is reported through the corresponding work_limit, node_limit or cell_limit stop; this type itself performs no admission. |
| cost | Fixed-size construction/copy. The grants limit only the charge sites described in the implementation, not all transitive work. |
| Design | [docs/meta_decompositions.md](../../../../../meta_decompositions.md) |

## B0005

[Lines 28–31](../../../../../../include/crown/planner/meta.hpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L31:sha256:c1d090d776361edfd7e2f5dad2b7c8e316de624b277abf64a41befb141a8f0aa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the work/cell charges consumed and the peak metadata-node count reached by one call. |
| inputs / outputs | work and scope_cells start at zero and accumulate; nodes starts at zero and records the largest admitted decomposition size. |
| invariants | Returned usage stays within that call's Limits. Counts describe selected metadata operations and explicit copies/inserts, not elapsed time, RSS or all allocations. |
| ownership | Usage owns three scalar counters and can outlive construction scratch without retaining query, decomposition or allocator state. |
| failure | A stopped call still returns its consumed charges; allocation/admission exceptions do not fabricate a completed Usage result. |
| cost | Reading/copying these counters is fixed-size. Node usage is a peak count while scope_cells is cumulative, so the two must not be interpreted interchangeably. |
| Design | [docs/meta_decompositions.md](../../../../../meta_decompositions.md) |

## B0006

[Lines 32–35](../../../../../../include/crown/planner/meta.hpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L35:sha256:41b76a901ab6a6f66a256435bf1d724c360c52e800ac9d41b84d85c3f53fffbc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name successful completion, unsupported body domains, reduction failure, invalid metadata and individual grant exhaustion. |
| inputs / outputs | Build and Check carry one Stop value; callers discriminate it before using a decomposition or treating valid as true. |
| invariants | Only complete may publish a Build decomposition or a true Check.valid. empty_body/nullary_occurrence are provider domain stops, not general engine rejection. |
| ownership | Stop is a scalar enum with no owned diagnostic string or graph state. |
| failure | invalid_decomposition denotes a failed proposed/generated structure; limit stops make no acyclicity or minimum-height claim. Admission/OOM exceptions remain separate. |
| cost | Fixed-size branching on the enum. Enumerators themselves introduce no additional checks, scans or exception machinery. |
| Design | [docs/meta_decompositions.md](../../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS1), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1) |

## B0007

[Lines 36–40](../../../../../../include/crown/planner/meta.hpp#L36); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L40:sha256:92eb23cea8780bdbdedc18660e7042bfb3646fdcf3db1fceae3ac0a10b6fef71
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return construction status, consumed grants and an optional owning complete decomposition. |
| inputs / outputs | construct produces Build; the caller must inspect stop and may use decomposition only when stop is complete. |
| invariants | No partial decomposition is published on a budget, domain, cyclic or structural stop. A completed graph is planning metadata, not a native-height capability. |
| ownership | Build owns any returned Decomposition and its containers. Stopped calls retain only status and Usage, after private construction scratch is discarded. |
| failure | Noncomplete results have an absent decomposition. Catalog/query validation and allocation exceptions propagate instead of being converted into an invented Stop. |
| cost | Returning/moving an engaged decomposition transfers its owning vector; copying it may allocate and visit all stored scope members. |
| Design | [docs/meta_decompositions.md](../../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1) |

## B0008

[Lines 41–41](../../../../../../include/crown/planner/meta.hpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L41:sha256:c7d9f74ddff8b4de0f37a20623782834e549ce959eefb75cf4d1df91788ffe5f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a bounded independent structural check result without retaining the checked proposal. |
| inputs / outputs | check returns stop, Usage and valid; valid is true only with complete after all implemented metadata properties pass. |
| invariants | The boolean is a property report for the current input bytes; it grants no CROWN admission, join-tree enumeration completeness or height authority. |
| ownership | Check contains only scalar status/counters/boolean values; it borrows no lifetime from the input graph after the call. |
| failure | Invalid proposals and domain/limit stops have valid=false. Input-admission or allocation exceptions can propagate before a Check exists. |
| cost | Copying the result is fixed-size; the underlying checking scans and scratch storage are accounted separately. |
| Design | [docs/meta_decompositions.md](../../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS4) |

## B0009

[Lines 42–53](../../../../../../include/crown/planner/meta.hpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L53:sha256:02c1996bada765fbaedb626f65e4167c0ae3ce01245ac224d8e0186dd760c07b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the public construction/checking entry points and document their costs, domain and authority boundary. |
| inputs / outputs | Both functions borrow Catalog and Query plus optional Limits; check additionally borrows Decomposition, while construct can return a new owned graph. |
| invariants | Empty/nullary stops are explicit, duplicate occurrences retain identity, and every checked minor fits one original scope. Metadata is not automatically a valid CROWN candidate. |
| ownership | Inputs remain caller-owned. Successful Build owns its graph; Check retains nothing. The namespace closure changes lookup scope, not resource lifetime. |
| failure | crown::validate admission and allocator exceptions propagate; internal metadata limits become result stops without publishing partial construction. |
| cost | Cold planning only. The header explicitly excludes admission allocations, allocator bytes and total CPU; no incremental runtime cost theorem follows from these counters. |
| Design | [docs/meta_decompositions.md](../../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS1), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3) |
