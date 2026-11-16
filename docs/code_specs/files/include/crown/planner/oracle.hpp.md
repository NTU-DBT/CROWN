# `include/crown/planner/oracle.hpp` — block usage map

[Source](../../../../../../include/crown/planner/oracle.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims.

Snapshot SHA-256: `bec4b84f5924e33654266841058e837570ecc6458ae7e9d8e3fccc656c231d18`. 87 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../../include/crown/planner/oracle.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Compatibility ceilings apply independently to producer and replay. literal_scope_limit · [reviewed contract](#b0001) |
| [B0002 · 10–18](../../../../../../include/crown/planner/oracle.hpp#L10) | Type/record definition: struct SearchLimits | source comment (unverified): // Compatibility ceilings apply independently to producer and replay. literal_scope_limit · [reviewed contract](#b0002) |
| [B0003 · 19–20](../../../../../../include/crown/planner/oracle.hpp#L19) | Explanatory comments or spacing. | source comment (unverified): // Counters identify executed routes and attempted work; proof authority comes from complete · [reviewed contract](#b0003) |
| [B0004 · 21–31](../../../../../../include/crown/planner/oracle.hpp#L21) | Type/record definition: struct SearchStatistics | source comment (unverified): // Counters identify executed routes and attempted work; proof authority comes from complete · [reviewed contract](#b0004) |
| [B0005 · 32–33](../../../../../../include/crown/planner/oracle.hpp#L32) | Explanatory comments or spacing. | source comment (unverified): // Claim a contextual lower bound, with null for infinity; it becomes usable only after · [reviewed contract](#b0005) |
| [B0006 · 34–40](../../../../../../include/crown/planner/oracle.hpp#L34) | Type/record definition: struct LowerBoundEntry | source comment (unverified): // Claim a contextual lower bound, with null for infinity; it becomes usable only after · [reviewed contract](#b0006) |
| [B0007 · 41–43](../../../../../../include/crown/planner/oracle.hpp#L41) | Explanatory comments or spacing. | source comment (unverified): // This aggregate is an unverified claim: pair a matching upper with complete lower replay · [reviewed contract](#b0007) |
| [B0008 · 44–49](../../../../../../include/crown/planner/oracle.hpp#L44) | Type/record definition: struct HeightCertificate | source comment (unverified): // This aggregate is an unverified claim: pair a matching upper with complete lower replay · [reviewed contract](#b0008) |
| [B0009 · 50–51](../../../../../../include/crown/planner/oracle.hpp#L50) | Explanatory comments or spacing. | source comment (unverified): // Strict results separate a checked minimum, a checked empty tree family and an incomplete · [reviewed contract](#b0009) |
| [B0010 · 52–52](../../../../../../include/crown/planner/oracle.hpp#L52) | Type/record definition: enum class OracleStatus | source comment (unverified): // Strict results separate a checked minimum, a checked empty tree family and an incomplete · [reviewed contract](#b0010) |
| [B0011 · 53–54](../../../../../../include/crown/planner/oracle.hpp#L53) | Explanatory comments or spacing. | source comment (unverified): // Own strict adapter evidence; a resource stop returns no partial minimum/tree/certificate. · [reviewed contract](#b0011) |
| [B0012 · 55–65](../../../../../../include/crown/planner/oracle.hpp#L55) | Type/record definition: struct OracleResult | source comment (unverified): // Own strict adapter evidence; a resource stop returns no partial minimum/tree/certificate. · [reviewed contract](#b0012) |
| [B0013 · 66–67](../../../../../../include/crown/planner/oracle.hpp#L66) | Explanatory comments or spacing. | source comment (unverified): // Report completed checking separately from replay resource exhaustion; the report is a · [reviewed contract](#b0013) |
| [B0014 · 68–73](../../../../../../include/crown/planner/oracle.hpp#L68) | Type/record definition: struct CertificateReport | source comment (unverified): // Report completed checking separately from replay resource exhaustion; the report is a · [reviewed contract](#b0014) |
| [B0015 · 74–87](../../../../../../include/crown/planner/oracle.hpp#L74) | declares values/defaults or compile-time conditions. | source comment (unverified): // Complete normal-form search with memoization. A completed public result has · [reviewed contract](#b0015) |

## B0001

[Lines 1–9](../../../../../../include/crown/planner/oracle.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:6800e17c48e5dd99508f57d9dfd78415b25b8dfa317532e0743044bd92438e9b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use #pragma once to suppress repeated header processing within a translation unit. Make #include "crown/ir/tree.hpp", #include &lt;chrono&gt; available to include/crown/planner/oracle.hpp; open crown::planner. Attached note: Compatibility ceilings apply independently to producer and replay. literal_scope_limit affects the literal oracle, not partition search. resource accounting. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [include/crown/planner/oracle.hpp](../../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0002

[Lines 10–18](../../../../../../include/crown/planner/oracle.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SearchLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure the blocking exact-search and replay compatibility limits. |
| inputs / outputs | Optional work, recursion and time ceilings map to separate producer/replay phase ledgers; literal_scope_limit belongs to the literal test oracle. |
| invariants | Null ceilings are unbounded. Production partition search does not generate the native-scope power set and ignores literal_scope_limit. |
| ownership | Owns scalar configuration; callers may copy it without retaining an active search. |
| failure | Negative or unrepresentable time values reject during adapter admission; exhausted operational limits do not prove infeasibility. |
| cost | Limits meter controlled transitions/depth/cooperative active time, excluding admission and ordinary allocator/comparison/width costs; they are not byte caps. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../../planner_proofs.md), [src/planner/search_session.cpp](../../../../../../src/planner/search_session.cpp) |

## B0003

[Lines 19–20](../../../../../../include/crown/planner/oracle.hpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L20:sha256:a521ca362b2d181aa2b5a9ffd15007fd973974a69fde2d7e3d7ee7a24adeaace
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for SearchStatistics: Counters identify executed routes and attempted work; proof authority comes from complete independent replay. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies SearchStatistics; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for SearchStatistics come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/oracle.hpp](../../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0004

[Lines 21–31](../../../../../../include/crown/planner/oracle.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SearchStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report work and structural route counters from exact planning. |
| inputs / outputs | Counters expose states, partitions, candidates, cache hits, hierarchy/singleton/empty routes, component splits, symmetry skips and bound prunes. |
| invariants | Work aliases follow continuation_v1 attempted accounting; structural counters do not establish completeness or elapsed-time complexity. |
| ownership | Owns scalar diagnostics; result/progress objects carry copies. |
| failure | Counter overflow handling belongs to the facade ledger; a statistics snapshot is never proof authority. |
| cost | Fixed-size snapshot storage; underlying counted transitions may have variable container and comparison costs. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../../planner_continuations.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../../planner_proofs.md) |

## B0005

[Lines 32–33](../../../../../../include/crown/planner/oracle.hpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L33:sha256:6509c9455349431e23786b834be0fe1d2013f1fb54fc3520fe40e94a376d2633
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for LowerBoundEntry: Claim a contextual lower bound, with null for infinity; it becomes usable only after independent proof. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies LowerBoundEntry; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for LowerBoundEntry come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/oracle.hpp](../../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0006

[Lines 34–40](../../../../../../include/crown/planner/oracle.hpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LowerBoundEntry {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State a lower-bound claim for one native subset and structural context. |
| inputs / outputs | occurrences is a nonempty sorted unique in-range sequence; flags specify generalized permission and connex reachability; null bound means infinity. |
| invariants | A finite bound lies between one and member count. Producer values are exact memo optima, but replay accepts any independently established safe lower bound; v2 canonicalizes equal-scope orbits. |
| ownership | Owns the member vector and scalar claim; it carries no authority before checking. |
| failure | Replay rejects malformed members, duplicate orbit keys or unjustified claims; omitted child claims supply only universal one. |
| cost | Claim storage and comparison scale with member count; proving a claim can enumerate exponentially many partitions. |
| Design | [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../../planner_proofs.md), [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md) |

## B0007

[Lines 41–43](../../../../../../include/crown/planner/oracle.hpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L43:sha256:242249bbe8a0550bd38b5a686c62ad8ee4741254468b7eb5ea0cf8a2d2a0dab1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for HeightCertificate: This aggregate is an unverified claim: pair a matching upper with complete lower replay before granting optimum or infeasibility authority. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies HeightCertificate; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for HeightCertificate come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/oracle.hpp](../../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0008

[Lines 44–49](../../../../../../include/crown/planner/oracle.hpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct HeightCertificate {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an algorithm-tagged upper witness and finite table of lower-bound claims. |
| inputs / outputs | Finite minimum_height requires a tree of matching checked height; absent minimum/tree represents claimed infeasibility. The owned replay binding supplies the exact catalog/query. |
| invariants | Empty body uses a checked empty height-zero tree and no states. v1/v2 tags choose replay rules; this mutable aggregate itself confers no checked authority. |
| ownership | Owns tree and claims by value; replay admission retains an independent immutable copy/move of the complete input. |
| failure | Unknown algorithms, mismatched upper/tree presence and failed lower replay reject; resource stops leave the claim unverified. |
| cost | Storage scales with tree and claim payloads; copying/serialization can allocate and is separate from handle-copy costs. |
| Design | [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../../planner_proofs.md), [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md) |

## B0009

[Lines 50–51](../../../../../../include/crown/planner/oracle.hpp#L50); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L51:sha256:368263a26d613c7c640521a54869c6dcbe88d109d0a9cbd70a62a8fb641acead
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for OracleStatus: Strict results separate a checked minimum, a checked empty tree family and an incomplete resource stop. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies OracleStatus; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for OracleStatus come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/oracle.hpp](../../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0010

[Lines 52–52](../../../../../../include/crown/planner/oracle.hpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class OracleStatus { proven_minimum, unsupported, resource_limit };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish strict optimum, completed no-tree result and incomplete operational search. |
| inputs / outputs | Blocking minimum_tree returns proven_minimum for matching upper/lower proof, unsupported for checked empty admissible family, and resource_limit otherwise. |
| invariants | Resource exhaustion never means infeasibility; unsupported in this adapter is not a timeout or heuristic failure. |
| ownership | Scalar result tag owns no certificate or witness. |
| failure | The enum can be edited in a mutable result; authority derives from the checked computation rather than the tag alone. |
| cost | Fixed-size storage and comparisons; proof effort resides in the producer/checker. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../../src/planner/search_session.cpp) |

## B0011

[Lines 53–54](../../../../../../include/crown/planner/oracle.hpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L54:sha256:5bd02bcfcc05b5d34ce395425373e78f990fbf76cb289594bd4cb43f0321017c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for OracleResult: Own strict adapter evidence; a resource stop returns no partial minimum/tree/certificate. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies OracleResult; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for OracleResult come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/oracle.hpp](../../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0012

[Lines 55–65](../../../../../../include/crown/planner/oracle.hpp#L55); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OracleResult {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the blocking adapter result with owning evidence and diagnostics. |
| inputs / outputs | Carries status, optional minimum/tree, lower claims, statistics, algorithm, reason, verification flag and the limits used. |
| invariants | Resource-limit results contain no minimum, tree or partial certificate. Completed unsupported results have checked infinite root evidence without an upper. |
| ownership | Owns result payloads; allocating compatibility conversion occurs privately before return. |
| failure | Copy/conversion allocation can throw instead of returning a partially certified result; editing fields does not create typed authority. |
| cost | Return construction copies complete tree/claim payloads and strings; size can grow with an exponential proof table. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../../planner_proofs.md), [src/planner/search_session.cpp](../../../../../../src/planner/search_session.cpp) |

## B0013

[Lines 66–67](../../../../../../include/crown/planner/oracle.hpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L67:sha256:d253f0809ed4c84f91f5c34bbc57d349274ed1d65a9261f73e5db51cced22ee3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CertificateReport: Report completed checking separately from replay resource exhaustion; the report is a summary, not an owning optimum handle. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CertificateReport; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CertificateReport come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/oracle.hpp](../../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../../planner_proofs.md) |

## B0014

[Lines 68–73](../../../../../../include/crown/planner/oracle.hpp#L68); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CertificateReport {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Summarize blocking independent certificate replay without exposing a partial proof owner. |
| inputs / outputs | valid reports completed checking; resource_limit distinguishes exhausted work/time/depth/allocation/counter resources; work counts attempts. |
| invariants | An invalid claim differs from an incomplete replay. The mutable summary alone cannot be promoted into VerifiedOptimum. |
| ownership | Owns its message and scalar snapshot; it does not retain the checked tree or input binding. |
| failure | Message/result conversion may allocate and throw; report.valid remains false without completed checker authority. |
| cost | Fixed scalar report plus variable message storage; replay effort is measured separately. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [src/planner/search_session.cpp](../../../../../../src/planner/search_session.cpp) |

## B0015

[Lines 74–87](../../../../../../include/crown/planner/oracle.hpp#L74); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] OracleResult minimum_tree(const Catalog& catalog, const Query& query, const SearchLimits& limits = {});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the strict blocking adapter over owned exact-search continuations. |
| inputs / outputs | Admits/copies catalog and query, advances until completion or a cumulative stop, and returns owning minimum/infeasibility evidence or a resource status. |
| invariants | A valid upper is returned as a minimum only after matching whole-root independent replay; strict resource stops withhold incumbents and partial certificates. |
| ownership | Borrows arguments only during admission/call; the active owner then uses its own immutable binding. |
| failure | Input/limit errors, internal proof failures and allocating result conversion can throw; ordinary resource stops return resource_limit. |
| cost | Can execute exponential search and replay plus result copying; limits are transition/depth/cooperative-time ceilings, not full CPU or byte bounds. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../../planner_proofs.md), [Refactor.md §5.5](../../../../../../Refactor.md), [Refactor.md §11.3 P06](../../../../../../Refactor.md), [src/planner/search_session.cpp](../../../../../../src/planner/search_session.cpp) |

```text
[[nodiscard]] CertificateReport verify_height_certificate(const Catalog& catalog, const Query& query,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently replay a caller-supplied v1/v2 height claim for an admitted binding. |
| inputs / outputs | Admits immutable catalog/query/certificate ownership, validates the upper if present, proves all supplied lower claims and matches the full root. |
| invariants | The checker reconstructs scopes/ports/components/orbits independently of producer state. Incomplete replay cannot establish either optimum or infeasibility. |
| ownership | Owns admitted inputs during the call and returns only an allocating summary. |
| failure | Malformed proof returns invalid after checker rejection; resource exhaustion has its own flag; admission/result allocation and invalid limit values may throw. |
| cost | Worst-case replay independently enumerates branch partitions and stores supplied/verified claims and derived port caches. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../../planner_proofs.md), [Refactor.md §5.4](../../../../../../Refactor.md), [Refactor.md §11.3 P06](../../../../../../Refactor.md), [src/planner/search_session.cpp](../../../../../../src/planner/search_session.cpp) |
