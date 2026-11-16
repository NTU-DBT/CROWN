# `include/crown/planner/ranking.hpp` — block usage map

[Source](../../../../../../include/crown/planner/ranking.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `4ee4320541170a6657761be8a70dd62160e366ef78caf95eb8860dad765e6032`. 166 lines partitioned into 33 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../../ranking.md), [docs/selection.md](../../../../../selection.md), [docs/selection_binding.md](../../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../../include/crown/planner/ranking.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../../include/crown/planner/ranking.hpp#L16) | Type/record definition: enum class Policy |  · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../../include/crown/planner/ranking.hpp#L17) | Type/record definition: enum class Fallback |  · [reviewed contract](#b0003) |
| [B0004 · 18–20](../../../../../../include/crown/planner/ranking.hpp#L18) | Type/record definition: enum class Stop |  · [reviewed contract](#b0004) |
| [B0005 · 21–28](../../../../../../include/crown/planner/ranking.hpp#L21) | Type/record definition: enum class Reason : std::uint64_t |  · [reviewed contract](#b0005) |
| [B0006 · 29–29](../../../../../../include/crown/planner/ranking.hpp#L29) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 30–30](../../../../../../include/crown/planner/ranking.hpp#L30) | Callable definition: constexpr Reasons reason(Reason value) noexcept | calls ; returns static_cast&lt;Reasons&gt;(value) · [reviewed contract](#b0007) |
| [B0008 · 31–38](../../../../../../include/crown/planner/ranking.hpp#L31) | Type/record definition: struct Limits |  · [reviewed contract](#b0008) |
| [B0009 · 39–44](../../../../../../include/crown/planner/ranking.hpp#L39) | Type/record definition: struct Usage |  · [reviewed contract](#b0009) |
| [B0010 · 45–45](../../../../../../include/crown/planner/ranking.hpp#L45) | Type/record definition: struct Request |  · [reviewed contract](#b0010) |
| [B0011 · 46–46](../../../../../../include/crown/planner/ranking.hpp#L46) | Type/record definition: struct InputWeight |  · [reviewed contract](#b0011) |
| [B0012 · 47–47](../../../../../../include/crown/planner/ranking.hpp#L47) | Type/record definition: struct SourceCardinality |  · [reviewed contract](#b0012) |
| [B0013 · 48–48](../../../../../../include/crown/planner/ranking.hpp#L48) | Type/record definition: enum class CaptureState |  · [reviewed contract](#b0013) |
| [B0014 · 49–49](../../../../../../include/crown/planner/ranking.hpp#L49) | Type/record definition: struct SourceObservation |  · [reviewed contract](#b0014) |
| [B0015 · 50–53](../../../../../../include/crown/planner/ranking.hpp#L50) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |
| [B0016 · 54–58](../../../../../../include/crown/planner/ranking.hpp#L54) | Type/record definition: struct ModeIdentity |  · [reviewed contract](#b0016) |
| [B0017 · 59–64](../../../../../../include/crown/planner/ranking.hpp#L59) | Type/record definition: struct EvidenceIdentity |  · [reviewed contract](#b0017) |
| [B0018 · 65–74](../../../../../../include/crown/planner/ranking.hpp#L65) | Type/record definition: struct CaptureAccounting |  · [reviewed contract](#b0018) |
| [B0019 · 75–78](../../../../../../include/crown/planner/ranking.hpp#L75) | Explanatory comments or spacing. | source comment (unverified): // Factory-produced score input, separate from the structural proof. Always an · [reviewed contract](#b0019) |
| [B0020 · 79–99](../../../../../../include/crown/planner/ranking.hpp#L79) | Type/record definition: class Evidence | returns *this; source comment (unverified): // Factory-produced score input, separate from the structural proof. Always an · [reviewed contract](#b0020) |
| [B0021 · 100–100](../../../../../../include/crown/planner/ranking.hpp#L100) | Type/record definition: struct OccurrenceDepth |  · [reviewed contract](#b0021) |
| [B0022 · 101–104](../../../../../../include/crown/planner/ranking.hpp#L101) | Type/record definition: struct TableDepth |  · [reviewed contract](#b0022) |
| [B0023 · 105–108](../../../../../../include/crown/planner/ranking.hpp#L105) | Type/record definition: struct PopulationBound |  · [reviewed contract](#b0023) |
| [B0024 · 109–112](../../../../../../include/crown/planner/ranking.hpp#L109) | Type/record definition: struct SlotTerm |  · [reviewed contract](#b0024) |
| [B0025 · 113–124](../../../../../../include/crown/planner/ranking.hpp#L113) | Type/record definition: struct CandidateScore |  · [reviewed contract](#b0025) |
| [B0026 · 125–130](../../../../../../include/crown/planner/ranking.hpp#L125) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Complete ranking of this retained prefix only; no provider advance or plan · [reviewed contract](#b0026) |
| [B0027 · 131–131](../../../../../../include/crown/planner/ranking.hpp#L131) | Callable definition: Result(Result&& x) noexcept:data_(x.data_) | calls data_ · [reviewed contract](#b0027) |
| [B0028 · 132–132](../../../../../../include/crown/planner/ranking.hpp#L132) | Callable definition: Result& operator=(Result&& x) noexcept | returns *this · [reviewed contract](#b0028) |
| [B0029 · 133–147](../../../../../../include/crown/planner/ranking.hpp#L133) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0029) |
| [B0030 · 148–148](../../../../../../include/crown/planner/ranking.hpp#L148) | Callable definition: explicit Result(std::shared_ptr&lt;const detail::ResultData&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0030) |
| [B0031 · 149–150](../../../../../../include/crown/planner/ranking.hpp#L149) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0031) |
| [B0032 · 151–157](../../../../../../include/crown/planner/ranking.hpp#L151) | Type/record definition: struct Attempt |  · [reviewed contract](#b0032) |
| [B0033 · 158–166](../../../../../../include/crown/planner/ranking.hpp#L158) | declares values/defaults or compile-time conditions. | source comment (unverified): // All retained members are evaluated or no Result is published. No provider · [reviewed contract](#b0033) |

## B0001

[Lines 1–15](../../../../../../include/crown/planner/ranking.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:df7b8fb60d717ef8b7ebec850ed763f3532b0e65184a615b0846bbc1d2774e10
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use #pragma once to suppress repeated header processing within a translation unit. Make #include "crown/ir/program.hpp", #include "crown/resource/owner_allocator.hpp", #include "crown/resource/owner_text.hpp", #include "crown/planner/candidates.hpp", #include "crown/ir/physical.hpp", #include &lt;chrono&gt;, #include &lt;memory&gt;, #include &lt;optional&gt;, #include &lt;string&gt;, #include &lt;vector&gt; available to include/crown/planner/ranking.hpp; open crown::planner::ranking and detail; forward-declare Factory, EvidenceData, ResultData. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [include/crown/planner/ranking.hpp](../../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../../ranking.md), [docs/selection_accounting.md](../../../../../selection_accounting.md) |

## B0002

[Lines 16–16](../../../../../../include/crown/planner/ranking.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Policy {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the candidate ordering model. |
| inputs / outputs | height_only, committed_input_native_depth or tuple_index_slots. |
| invariants | Every policy ranks only retained candidates at the original certified height; scores are neither runtime duration nor new lower proofs. |
| ownership | Copied scalar policy. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed enum transfer. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0003

[Lines 17–17](../../../../../../include/crown/planner/ranking.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Fallback {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the response to unavailable score evidence. |
| inputs / outputs | require_evidence stops; height_only orders the same whole snapshot by key. |
| invariants | Resource or arithmetic failures do not trigger evidence fallback. |
| ownership | Copied scalar choice. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed enum transfer. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0004

[Lines 18–20](../../../../../../include/crown/planner/ranking.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Stop {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify complete ranking or a bounded no-result outcome. |
| inputs / outputs | Captures empty inputs, evidence/binding failures, resource stops and internal faults. |
| invariants | Only complete with a Result supplies selection; a resource stop does not prove no better candidate exists. |
| ownership | Copied enum in Attempt. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed status storage. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0005

[Lines 21–28](../../../../../../include/crown/planner/ranking.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Reason :
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name reasons recorded for unavailable as-of evidence. |
| inputs / outputs | Independent bit values for source/capture/interval/owner/mode conditions. |
| invariants | Reasons describe input usability and freshness checks, never structural proof authority. |
| ownership | Bit values retained in evidence/attempt/result. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed word flags. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0006

[Lines 29–29](../../../../../../include/crown/planner/ranking.hpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Reasons=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store combined evidence reason bits. |
| inputs / outputs | uint64 mask for fixed Reason values. |
| invariants | Combining flags does not establish freshness or proof authority. |
| ownership | Inline scalar. |
| failure | Type/version definitions do not validate caller content or allocate payload. |
| cost | Fixed word operations. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0007

[Lines 30–30](../../../../../../include/crown/planner/ranking.hpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr Reasons reason(Reason value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one reason flag to the stored mask. |
| inputs / outputs | Returns the underlying uint64 value. |
| invariants | No enum validation or reason combination occurs. |
| ownership | Scalar copy. |
| failure | Nonthrowing cast. |
| cost | Fixed operation. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0008

[Lines 31–38](../../../../../../include/crown/planner/ranking.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Limits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set logical ranking and delegated compiler ceilings. |
| inputs / outputs | Work/cells/key/payload bytes, candidate count, 1..512 score bits, delegated allowances and optional active time. |
| invariants | Logical payload/cells differ from actual memory-account capacity; time checks are cooperative. |
| ownership | Owns scalar limits. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed-size options; does not preallocate candidates. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0009

[Lines 39–44](../../../../../../include/crown/planner/ranking.hpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Usage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report carried preparation and attempted ranking debits. |
| inputs / outputs | Separate work/cells/key/payload/delegation counts and active nanoseconds. |
| invariants | Usage can remain spent after private work fails; it is not retained bytes or total CPU instructions. |
| ownership | Owns numeric snapshot. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed-size copying/comparison. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
bool operator==(const Usage&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all usage counters. |
| inputs / outputs | Memberwise Boolean equality. |
| invariants | Equal values do not compare owners or establish freshness. |
| ownership | Borrows two snapshots. |
| failure | No validation. |
| cost | Fixed numeric comparisons. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0010

[Lines 45–45](../../../../../../include/crown/planner/ranking.hpp#L45); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Request {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind a ranking policy, fallback and ceilings to one call. |
| inputs / outputs | Defaults to height-only with evidence-required fallback. |
| invariants | Request cannot enlarge the candidate snapshot or rewrite its original proof. |
| ownership | Owns scalar request. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed option copying. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0011

[Lines 46–46](../../../../../../include/crown/planner/ranking.hpp#L46); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InputWeight {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record committed physical table input frequencies. |
| inputs / outputs | Table ID and insert/erase/changed/noop counters. |
| invariants | Depth weighting uses inserts+erases; changed/noop remain observations, not separate score factors. |
| ownership | Inline captured values. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed storage. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0012

[Lines 47–47](../../../../../../include/crown/planner/ranking.hpp#L47); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourceCardinality {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one exact captured physical source size. |
| inputs / outputs | Physical TableId plus uint64 row count. |
| invariants | Missing source evidence is not zero; the factory/eligibility boundary supplies completeness. |
| ownership | Inline captured values. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed storage. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0013

[Lines 48–48](../../../../../../include/crown/planner/ranking.hpp#L48); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CaptureState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish available source facts from missing or private data. |
| inputs / outputs | Includes not_requested, available, budget_exhausted, pending_private_state, unavailable and released. |
| invariants | Unavailable facts do not become fabricated zero-cardinality evidence. |
| ownership | Scalar capture tag. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed storage. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0014

[Lines 49–49](../../../../../../include/crown/planner/ranking.hpp#L49); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourceObservation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose per-source capture disposition. |
| inputs / outputs | Table ID, capture tag and optional count. |
| invariants | Public aggregate construction does not independently establish a healthy current source census. |
| ownership | Owns optional numeric value. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed-size value. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0015

[Lines 50–53](../../../../../../include/crown/planner/ranking.hpp#L50); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> using EvidenceVector=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store retained evidence rows in their original owner account. |
| inputs / outputs | std::vector with OwnerAllocator&lt;T&gt;. |
| invariants | Allocator identity/capacity follow the native account; logical rank payload does not replace actual accounting. |
| ownership | Vector owns elements/account-aware capacity; references need surviving EvidenceData. |
| failure | Type/version definitions do not validate caller content or allocate payload. |
| cost | Vector traversal/copy/growth and final teardown depend on element count/capacity. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
using EvidenceText=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store complete retained exact binding bytes. |
| inputs / outputs | basic_string with OwnerAllocator&lt;char&gt;. |
| invariants | No digest-only binding; length includes arbitrary byte content. |
| ownership | Owns account-backed bytes and allocator account. |
| failure | Type/version definitions do not validate caller content or allocate payload. |
| cost | String copy/compare/growth costs depend on byte length/capacity. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
template<class T> using ScoreVector=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store receiving-account score explanation arrays. |
| inputs / outputs | std::vector with OwnerAllocator&lt;T&gt;. |
| invariants | Existing candidate/evidence owners are not retagged by using this alias. |
| ownership | Owns newly allocated score storage and nested values. |
| failure | Type/version definitions do not validate caller content or allocate payload. |
| cost | Vector allocation/copy/cleanup costs follow count, capacity and nested owners. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
using ScoreText=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store exact score text using OwnerText. |
| inputs / outputs | Account-aware owned text, including decimal score strings and full structural key. |
| invariants | Score strings are representation, not time/byte/performance certificates. |
| ownership | Owns bytes and original score allocator. |
| failure | Type/version definitions do not validate caller content or allocate payload. |
| cost | Byte-sized copy/compare/cleanup costs; decimal output bounded155digits, structural keys can be larger. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0016

[Lines 54–58](../../../../../../include/crown/planner/ranking.hpp#L54); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ModeIdentity {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record the modes associated with captured evidence. |
| inputs / outputs | Owner layer and requested/resolved maintenance/completion/view choices. |
| invariants | Equal mode records do not establish current owner freshness. |
| ownership | Inline snapshot copied with evidence. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed numeric comparison. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
bool operator==(const ModeIdentity&) const=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all mode fields. |
| inputs / outputs | Memberwise Boolean equality. |
| invariants | Equal values do not compare owners or establish freshness. |
| ownership | Borrows two snapshots. |
| failure | No validation. |
| cost | Fixed numeric comparisons. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0017

[Lines 59–64](../../../../../../include/crown/planner/ranking.hpp#L59); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EvidenceIdentity {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain an as-of owner/epoch/interval/configuration stamp. |
| inputs / outputs | Owner, epoch, reset/config/segment/format, collection limits/mode and saturation flags. |
| invariants | Pure ranking cannot revalidate a live owner using this stored stamp alone. |
| ownership | Inline captured identity; no live owner pointer. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed-size snapshot. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0018

[Lines 65–74](../../../../../../include/crown/planner/ranking.hpp#L65); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CaptureAccounting {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain which processing and source-state capture limits were used. |
| inputs / outputs | Processing limits, request/return counts, selected state bounds, consumed work/rows/keys/bytes and descriptor counts. |
| invariants | Capture completeness is explicit; limits/counts do not create structural or future-freshness authority. |
| ownership | Owns numeric/options report. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed-size metadata. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0019

[Lines 75–78](../../../../../../include/crown/planner/ranking.hpp#L75); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L78:sha256:c3bec36ac10feb7ce3bd34212b405fcee10212a27693ac6fce66800a028833fe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Evidence: Factory-produced score input, separate from the structural proof. Always an as-of record: this pure layer cannot assert that an owner is still current. Moves deliberately retain the source shared owner, so noexcept getters can borrow directly. Assignments may destroy a large old destination payload. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Evidence; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Evidence come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [include/crown/planner/ranking.hpp](../../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../../ranking.md), [docs/selection_accounting.md](../../../../../selection_accounting.md) |

## B0020

[Lines 79–99](../../../../../../include/crown/planner/ranking.hpp#L79); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Evidence {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain immutable factory-produced as-of ranking input. |
| inputs / outputs | Borrow compiled plan, physical input/source facts, identity, eligibility reasons and preparation usage. |
| invariants | No public default/import constructor; copy-like moves keep both source and destination valid for noexcept borrows. Pure ranking cannot assert currentness. |
| ownership | Shares const EvidenceData, its CompiledProgram and original accounted metadata; assignments can destroy old final-owned payload. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Construction has fixed shared-owner work; assignment/destruction can tear down old data, vectors and final-owned plan payload. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
Evidence(const Evidence&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the Evidence shared owner. |
| inputs / outputs | Source and destination retain the same immutable EvidenceData. |
| invariants | Move deliberately copies the shared_ptr: source stays nonnull and public noexcept borrows remain valid; self-assignment is safe. |
| ownership | Adds a shared owner without deep payload copy. |
| failure | Noexcept shared-pointer operation; no validation/worker work. |
| cost | Fixed refcount/handle work without payload allocation. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
Evidence& operator=(const Evidence&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the Evidence shared owner. |
| inputs / outputs | Source and destination retain the same immutable EvidenceData. |
| invariants | Move deliberately copies the shared_ptr: source stays nonnull and public noexcept borrows remain valid; self-assignment is safe. |
| ownership | Shared ownership; replacing a destination can release its previous final owner. |
| failure | Noexcept shared-pointer operation; no validation/worker work. |
| cost | Fixed refcount/handle work plus potentially full old-payload teardown. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
Evidence(Evidence&& x) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain during move the Evidence shared owner. |
| inputs / outputs | Source and destination retain the same immutable EvidenceData. |
| invariants | Move deliberately copies the shared_ptr: source stays nonnull and public noexcept borrows remain valid; self-assignment is safe. |
| ownership | Adds a shared owner without deep payload copy. |
| failure | Noexcept shared-pointer operation; no validation/worker work. |
| cost | Fixed refcount/handle work without payload allocation. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
Evidence& operator=(Evidence&& x) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain during move the Evidence shared owner. |
| inputs / outputs | Source and destination retain the same immutable EvidenceData. |
| invariants | Move deliberately copies the shared_ptr: source stays nonnull and public noexcept borrows remain valid; self-assignment is safe. |
| ownership | Shared ownership; replacing a destination can release its previous final owner. |
| failure | Noexcept shared-pointer operation; no validation/worker work. |
| cost | Fixed refcount/handle work plus potentially full old-payload teardown. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
explicit Evidence(std::shared_ptr<const detail::EvidenceData> data) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install a prepared private Evidence payload. |
| inputs / outputs | Transfers a factory-supplied shared pointer into the public handle. |
| invariants | Factory must supply nonnull complete data; no caller-controlled public empty constructor exists. |
| ownership | Transfers one shared owner; moved-from local parameter can be empty. |
| failure | Noexcept; internal factory precondition is not rechecked here. |
| cost | Fixed pointer transfer. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0021

[Lines 100–100](../../../../../../include/crown/planner/ranking.hpp#L100); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OccurrenceDepth {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report one native occurrence contribution depth. |
| inputs / outputs | Occurrence, original physical table and native-only root-to-node depth. |
| invariants | Native root depth is one; generalized nodes add zero. |
| ownership | Inline score detail. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed-size record. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0022

[Lines 101–104](../../../../../../include/crown/planner/ranking.hpp#L101); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TableDepth {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain a physical table depth contribution. |
| inputs / outputs | Committed insert/erase counts plus decimal depth_sum and weighted contribution. |
| invariants | Counts are physical inputs, not derivations or observed maintenance work. |
| ownership | ScoreText owns allocator-aware text. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Copy/retention follows owned text lengths; handle movement can release prior text. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0023

[Lines 105–108](../../../../../../include/crown/planner/ranking.hpp#L105); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PopulationBound {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain candidate-local relation population bounds. |
| inputs / outputs | Node plus record/survivor/parent-support decimal bounds and optional visible bound. |
| invariants | These are conservative derived populations, not observed bytes or exact join sizes. |
| ownership | Owns accounted text/optional value. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Proportional to retained decimal strings, each bounded by score bits. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0024

[Lines 109–112](../../../../../../include/crown/planner/ranking.hpp#L109); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SlotTerm {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain one tuple or index membership slot term. |
| inputs / outputs | Relation, optional unique index, width, population and contribution. |
| invariants | Width+1 counts abstract slots; no allocator/object/peak-memory byte bound follows. |
| ownership | Owns scalar metadata and accounted decimal text. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed fields plus bounded text ownership. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0025

[Lines 113–124](../../../../../../include/crown/planner/ranking.hpp#L113); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateScore {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one fully admitted alternative and its model explanation. |
| inputs / outputs | Candidate handle/key/height, decimal score fields, detailed vectors and optional newly modeled compiled plan. |
| invariants | Original candidate proof remains unchanged; modeled plan is score input, not runtime installation. |
| ownership | Candidate shares prior immutable owners; new text/vectors use receiving score account and modeled plan uses replan_into. |
| failure | Constructor candidate access and allocator/account/allocation failures can throw; copying nested text/vectors can allocate. Public record mutation creates no checked candidate or proof authority; the ranker populates only private drafts before publication. |
| cost | Copying nested payload can allocate/scan; destruction can free final plan/data; no constant whole-record-copy claim. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0026

[Lines 125–130](../../../../../../include/crown/planner/ranking.hpp#L125); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Result {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a complete deterministic ranking of a fixed prefix. |
| inputs / outputs | Expose selected candidate/index, full scores, snapshot, request, effective policy, fallback and spent usage. |
| invariants | Best means only among this retained snapshot; no provider advancement, plan install or future-freshness promise. |
| ownership | Shares immutable ResultData/account and old snapshot/evidence owners; getters borrow from a live retained owner. |
| failure | Factory creates only complete nonempty rankings; public copy-like moves keep source usable. |
| cost | Fixed handle construction; final-owned scores/model plans may have size-dependent teardown. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
Result(const Result&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the Result shared owner. |
| inputs / outputs | Source and destination retain the same immutable ResultData. |
| invariants | Move deliberately copies the shared_ptr: source stays nonnull and public noexcept borrows remain valid; self-assignment is safe. |
| ownership | Adds a shared owner without deep payload copy. |
| failure | Noexcept shared-pointer operation; no validation/worker work. |
| cost | Fixed refcount/handle work without payload allocation. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
Result& operator=(const Result&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the Result shared owner. |
| inputs / outputs | Source and destination retain the same immutable ResultData. |
| invariants | Move deliberately copies the shared_ptr: source stays nonnull and public noexcept borrows remain valid; self-assignment is safe. |
| ownership | Shared ownership; replacing a destination can release its previous final owner. |
| failure | Noexcept shared-pointer operation; no validation/worker work. |
| cost | Fixed refcount/handle work plus potentially full old-payload teardown. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0027

[Lines 131–131](../../../../../../include/crown/planner/ranking.hpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Result(Result&& x) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain during move the Result shared owner. |
| inputs / outputs | Source and destination retain the same immutable ResultData. |
| invariants | Move deliberately copies the shared_ptr: source stays nonnull and public noexcept borrows remain valid; self-assignment is safe. |
| ownership | Adds a shared owner without deep payload copy. |
| failure | Noexcept shared-pointer operation; no validation/worker work. |
| cost | Fixed refcount/handle work without payload allocation. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0028

[Lines 132–132](../../../../../../include/crown/planner/ranking.hpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Result& operator=(Result&& x) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain during move the Result shared owner. |
| inputs / outputs | Source and destination retain the same immutable ResultData. |
| invariants | Move deliberately copies the shared_ptr: source stays nonnull and public noexcept borrows remain valid; self-assignment is safe. |
| ownership | Shared ownership; replacing a destination can release its previous final owner. |
| failure | Noexcept shared-pointer operation; no validation/worker work. |
| cost | Fixed refcount/handle work plus potentially full old-payload teardown. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0029

[Lines 133–147](../../../../../../include/crown/planner/ranking.hpp#L133); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static constexpr unsigned format_version=1;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the published ranking result format. |
| inputs / outputs | Version1 compile-time constant. |
| invariants | A format tag does not admit arbitrary imported evidence/results. |
| ownership | Inline constant. |
| failure | Type/version definitions do not validate caller content or allocate payload. |
| cost | No runtime allocation or traversal. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
static constexpr unsigned arithmetic_version=1;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name fixed-capacity exact score arithmetic semantics. |
| inputs / outputs | Version1 compile-time constant. |
| invariants | Version remains distinct from proof algorithm, candidate family and allocator backend. |
| ownership | Inline constant. |
| failure | Type/version definitions do not validate caller content or allocate payload. |
| cost | No runtime allocation or traversal. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0030

[Lines 148–148](../../../../../../include/crown/planner/ranking.hpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Result(std::shared_ptr<const detail::ResultData> data) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install a prepared private Result payload. |
| inputs / outputs | Transfers a factory-supplied shared pointer into the public handle. |
| invariants | Factory must supply nonnull complete data; no caller-controlled public empty constructor exists. |
| ownership | Transfers one shared owner; moved-from local parameter can be empty. |
| failure | Noexcept; internal factory precondition is not rechecked here. |
| cost | Fixed pointer transfer. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0031

[Lines 149–150](../../../../../../include/crown/planner/ranking.hpp#L149); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const detail::ResultData> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one immutable ranking result and its selected candidate, evidence, request, scores, and account. |
| inputs / outputs | Result accessors return const references to the retained snapshot, selected candidate, score vector, account, evidence, request, and usage; selected() returns scores\[selected_index\].candidate, while index/policy/reason accessors return values. |
| invariants | ResultData is const after publication, and Result has no public arbitrary-data constructor. |
| ownership | Copies share the ResultData owner and keep its account-backed payload alive. |
| failure | The member declaration has no failure path; public Result handles come from the factory. |
| cost | The field declaration does no work. Last-owner release can destroy vectors, text, evidence, and candidate payloads, so cleanup is not assumed constant. |
| Design | [src/planner/ranking_detail.hpp §ResultData](../../../../../../src/planner/ranking_detail.hpp), [src/planner/ranking.cpp §Result accessors](../../../../../../src/planner/ranking.cpp), [docs/ranking.md §Runtime evidence allocation ownership](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0032

[Lines 151–157](../../../../../../include/crown/planner/ranking.hpp#L151); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Attempt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the complete result or an explicit partial processing outcome. |
| inputs / outputs | Stop, optional immutable Result, usage, evaluated count and evidence reasons. |
| invariants | No Result is published for partial scoring/resource/internal failure; evaluated counts completed model values only. |
| ownership | Owns optional shared result plus numeric diagnostics. |
| failure | These public value carriers do not validate or mint proof/freshness authority; consumers/factories enforce the closed protocols. |
| cost | Fixed report work plus shared-owner release if overwritten. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0033

[Lines 158–166](../../../../../../include/crown/planner/ranking.hpp#L158); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Attempt rank(const CandidateSnapshot&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rank a fixed retained snapshot using a derived score account. |
| inputs / outputs | Request/evidence go to the synchronous all-or-nothing ranker. |
| invariants | No provider advancement, owner mutation, new structural proof, cache use or runtime installation. |
| ownership | Result retains snapshot/evidence; new allocations use selected/supplied account, existing owners remain separately retained. |
| failure | Returns Attempt status from one noexcept exception boundary. |
| cost | Variable whole-binding, candidate, score, lowering and cleanup costs within logical/cooperative ceilings. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |

```text
[[nodiscard]] Attempt rank_with_account(const resource::MemoryAccount&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rank using the explicitly supplied receiving account. |
| inputs / outputs | Request/evidence go to the synchronous all-or-nothing ranker. |
| invariants | No provider advancement, owner mutation, new structural proof, cache use or runtime installation. |
| ownership | Result retains snapshot/evidence; new allocations use selected/supplied account, existing owners remain separately retained. |
| failure | Returns Attempt status from one noexcept exception boundary. |
| cost | Variable whole-binding, candidate, score, lowering and cleanup costs within logical/cooperative ceilings. |
| Design | [docs/ranking.md](../../../../../ranking.md), [docs/query_memory.md](../../../../../query_memory.md) |
