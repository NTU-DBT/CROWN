# `src/io/search.cpp` — block usage map

[Source](../../../../../src/io/search.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `2e8554b5aeb471f81ec66e01751b3928e66eca36b18d36f5079ea3f01dacc964`. 111 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/io/search.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases. | returns #Value · [reviewed contract](#b0001) |
| [B0002 · 8–17](../../../../../src/io/search.cpp#L8) | Callable definition: const char* name(SearchPhase value) noexcept | calls P06_ENUM_CASE; returns @ · [reviewed contract](#b0002) |
| [B0003 · 18–28](../../../../../src/io/search.cpp#L18) | Callable definition: const char* name(ReplayPhase value) noexcept | calls P06_ENUM_CASE; returns @ · [reviewed contract](#b0003) |
| [B0004 · 29–39](../../../../../src/io/search.cpp#L29) | Callable definition: const char* name(StopReason value) noexcept | calls P06_ENUM_CASE; returns @ · [reviewed contract](#b0004) |
| [B0005 · 40–46](../../../../../src/io/search.cpp#L40) | Callable definition: const char* name(ResultKind value) noexcept | calls P06_ENUM_CASE; returns @ · [reviewed contract](#b0005) |
| [B0006 · 47–47](../../../../../src/io/search.cpp#L47) | Member/declaration region. |  · [reviewed contract](#b0006) |
| [B0007 · 48–52](../../../../../src/io/search.cpp#L48) | Callable definition: Json counters(const WorkCounters& value) | calls ; returns {{@ , value.attempted}, {@ , value.committed_transitions}, · [reviewed contract](#b0007) |
| [B0008 · 53–56](../../../../../src/io/search.cpp#L53) | Callable definition: Json phase_limit(const PhaseCeiling& value) | calls Json, count; returns {{@ , value.work ? Json(*value.work) : Json(nullptr)}, · [reviewed contract](#b0008) |
| [B0009 · 57–57](../../../../../src/io/search.cpp#L57) | Callable definition: Json depth_limit(const std::optional&lt;std::size_t&gt;& value) | calls Json; returns value ? Json(*value) : Json(nullptr) · [reviewed contract](#b0009) |
| [B0010 · 58–68](../../../../../src/io/search.cpp#L58) | Callable definition: Json checked_certificate(const HeightCertificate& proof, const SearchBinding& binding) | calls write_oracle, catalog, query, at; returns write_oracle(result, binding.catalog(), binding.query()).at(@ ); source comment (unverified): // Cold compatibility export copies proof payload and the returned certificate DOM. · [reviewed contract](#b0010) |
| [B0011 · 69–69](../../../../../src/io/search.cpp#L69) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0011) |
| [B0012 · 70–76](../../../../../src/io/search.cpp#L70) | Callable definition: Json write_validated_incumbent(const planner::ValidatedIncumbent& value) | calls binding, detail::query_binding, catalog, query; returns {{@ , 1}, {@ , @ }, · [reviewed contract](#b0012) |
| [B0013 · 77–79](../../../../../src/io/search.cpp#L77) | Callable definition: Json write_verified_optimum(const planner::VerifiedOptimum& value) | calls checked_certificate, certificate, binding; returns checked_certificate(value.certificate(), value.binding()) · [reviewed contract](#b0013) |
| [B0014 · 80–82](../../../../../src/io/search.cpp#L80) | Callable definition: Json write_verified_infeasible(const planner::VerifiedInfeasible& value) | calls checked_certificate, certificate, binding; returns checked_certificate(value.certificate(), value.binding()) · [reviewed contract](#b0014) |
| [B0015 · 83–98](../../../../../src/io/search.cpp#L83) | Callable definition: Json write_search_progress(const planner::ExactSearch& owner) | calls binding, progress, limits, incumbent; returns {{@ , 1}, {@ , @ }, {@ , @ }, · [reviewed contract](#b0015) |
| [B0016 · 99–110](../../../../../src/io/search.cpp#L99) | Callable definition: Json write_replay_progress(const planner::CertificateReplay& owner) | calls binding, progress, limits, detail::query_binding; returns {{@ , 1}, {@ , @ }, {@ , @ }, · [reviewed contract](#b0016) |
| [B0017 · 111–111](../../../../../src/io/search.cpp#L111) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0017) |

## B0001

[Lines 1–7](../../../../../src/io/search.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/io/search.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize live exact-search/replay observation and immutable checked artifacts outside controlled advance quanta. |
| inputs / outputs | Imports the declarations used by this translation unit/header; no runtime input or result. |
| invariants | Namespace/includes do not perform admission, validation, publication or IO. |
| ownership | Declarations give no ownership of caller records, source bytes or runtime accounts. |
| failure | Compile/link dependencies only; there is no executable failure boundary in these includes. |
| cost | Compile-time dependencies; later functions account for their own runtime work and storage. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–17](../../../../../src/io/search.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(SearchPhase value) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the observed SearchPhase without throwing for an unknown enum. |
| inputs / outputs | Enum in; const char* static spelling or unknown out. |
| invariants | Progress label is descriptive only; no proof/state transition derives from it. |
| ownership | Borrowed static storage, no account/runtime owner retained. |
| failure | noexcept; deliberate unknown fallback. |
| cost | O(1) finite switch, no allocation. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 18–28](../../../../../src/io/search.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ReplayPhase value) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the observed ReplayPhase without throwing for an unknown enum. |
| inputs / outputs | Enum in; const char* static spelling or unknown out. |
| invariants | Progress label is descriptive only; no proof/state transition derives from it. |
| ownership | Borrowed static storage, no account/runtime owner retained. |
| failure | noexcept; deliberate unknown fallback. |
| cost | O(1) finite switch, no allocation. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 29–39](../../../../../src/io/search.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(StopReason value) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the observed StopReason without throwing for an unknown enum. |
| inputs / outputs | Enum in; const char* static spelling or unknown out. |
| invariants | Progress label is descriptive only; no proof/state transition derives from it. |
| ownership | Borrowed static storage, no account/runtime owner retained. |
| failure | noexcept; deliberate unknown fallback. |
| cost | O(1) finite switch, no allocation. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 40–46](../../../../../src/io/search.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const char* name(ResultKind value) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the observed ResultKind without throwing for an unknown enum. |
| inputs / outputs | Enum in; const char* static spelling or unknown out. |
| invariants | Progress label is descriptive only; no proof/state transition derives from it. |
| ownership | Borrowed static storage, no account/runtime owner retained. |
| failure | noexcept; deliberate unknown fallback. |
| cost | O(1) finite switch, no allocation. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 47–47](../../../../../src/io/search.cpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L47:sha256:5882bf6f718f312f578ca235dbec677616757076a793bfe9e4ae3f953aa70d21
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ends the local preprocessor definition of P06_ENUM_CASE; subsequent translation-unit code cannot use that macro expansion. |
| inputs / outputs | No runtime values are exchanged; a preprocessor macro is removed for later source text in this translation unit. |
| invariants | The macro expansion is available only before this directive; later code must use ordinary declarations or a fresh definition. |
| ownership | No runtime state. |
| failure | No runtime error. Preprocessing/compilation can fail if later tokens depended on the removed macro. |
| cost | Preprocessing only. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [docs/code_specs/files/src/io/search.cpp.md](search.cpp.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/selection.md](../../../../selection.md) |

## B0007

[Lines 48–52](../../../../../src/io/search.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json counters(const WorkCounters& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export fixed controlled-work diagnostic counters. |
| inputs / outputs | WorkCounters in; attempted/committed/failures/active_nanoseconds/current_depth/peak_depth DOM out. |
| invariants | These are continuation_v1 attempted-transition and active-time observations, not byte, CPU instruction or lower-bound proof data. |
| ownership | Borrowed inline counters; ordinary object owns copied scalars. |
| failure | DOM allocation failure propagates. |
| cost | Fixed six-field DOM object; no search traversal or clock read. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 53–56](../../../../../src/io/search.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json phase_limit(const PhaseCeiling& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export optional work and active-time ceilings in their native units. |
| inputs / outputs | PhaseCeiling in; work and active_nanoseconds count or null out. |
| invariants | Null remains unbounded; serialization does not validate or raise ceilings or consume quantum work. |
| ownership | Inline optional values copied into ordinary DOM object. |
| failure | DOM allocation can fail; input unchanged. |
| cost | Fixed two-field construction, no clock sampling. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 57–57](../../../../../src/io/search.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json depth_limit(const std::optional<std::size_t>& value) { return value ? Json(*value) : Json(nullptr); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode optional logical depth as a number or null. |
| inputs / outputs | optional&lt;size_t&gt; in; Json scalar/null out. |
| invariants | No proof or resource admission is produced by a depth label. |
| ownership | Inline result only. |
| failure | No intentional failure branch. |
| cost | O(1), no container allocation. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 58–68](../../../../../src/io/search.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json checked_certificate(const HeightCertificate& proof, const SearchBinding& binding) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt an already checked immutable typed certificate to the established legacy certificate format. |
| inputs / outputs | Private helper receives HeightCertificate plus matching actual SearchBinding from typed serializers; returns only the certificate subtree of write_oracle. |
| invariants | Sets compatibility certificate_verified internally because typed token factory already checked proof; write_oracle does not replay it. This helper is not exposed for arbitrary edited proof/flag input. |
| ownership | OracleResult deep-copies tree/lower-bound vectors/algorithm from proof; legacy writer builds owning DOM, and .at("certificate") returns an lvalue so returning by value deep-copies that subtree before temporary destruction. |
| failure | Binding/accessor/legacy algorithm/tree/addressability/DOM/copy OOM errors propagate; no search/proof state mutation. |
| cost | Full proof graph copy+legacy query/tree/bounds serialization, extra legacy envelope and final certificate subtree deep copy; allocating cold IO, not advance work. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 69–69](../../../../../src/io/search.cpp#L69); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L69:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [docs/code_specs/files/src/io/search.cpp.md](search.cpp.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/selection.md](../../../../selection.md) |

## B0012

[Lines 70–76](../../../../../src/io/search.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_validated_incumbent(const planner::ValidatedIncumbent& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a checked valid upper tree without claiming minimum height. |
| inputs / outputs | ValidatedIncumbent handle in; version/accounting/query_binding/height_upper_bound/tree DOM out, certificate=null. |
| invariants | Actual private factory token binds verified upper tree to catalog/query; advertised labels are not sufficient to construct this type. |
| ownership | Local SearchBinding copy retains immutable binding owner; write_query/tree creates independent ordinary DOM. No full certificate graph copied here. |
| failure | Moved-from handle/binding or tree/document/DOM errors propagate; live owner is not advanced or changed. |
| cost | O(query/catalog/tree graph+names) serialization/validation and ordinary DOM storage; reference retention itself O(1). |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 77–79](../../../../../src/io/search.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_verified_optimum(const planner::VerifiedOptimum& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the independently checked optimum certificate through typed authority. |
| inputs / outputs | VerifiedOptimum in; canonical certificate-only DOM out via checked_certificate. |
| invariants | certificate() and binding() read actual immutable factory state; no caller-edited progress or Boolean accepted as proof. Serializer does not rerun lower-bound replay. |
| ownership | Handle retains underlying checked owner during call; private adapter/legacy DOM deep-copy owned proof structures as documented. |
| failure | Moved-from/accessor/legacy encoding/allocation failures propagate before return; checked artifact unchanged. |
| cost | O(full proof/query/tree graph+bytes) ordinary copies/serialization including final lvalue certificate subtree copy; not part of continuation counters. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 80–82](../../../../../src/io/search.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_verified_infeasible(const planner::VerifiedInfeasible& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the independently checked infeasibility certificate through typed authority. |
| inputs / outputs | VerifiedInfeasible in; canonical certificate-only DOM out via checked_certificate. |
| invariants | certificate() and binding() read actual immutable factory state; no caller-edited progress or Boolean accepted as proof. Serializer does not rerun lower-bound replay. |
| ownership | Handle retains underlying checked owner during call; private adapter/legacy DOM deep-copy owned proof structures as documented. |
| failure | Moved-from/accessor/legacy encoding/allocation failures propagate before return; checked artifact unchanged. |
| cost | O(full proof/query/tree graph+bytes) ordinary copies/serialization including final lvalue certificate subtree copy; not part of continuation counters. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 83–98](../../../../../src/io/search.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_search_progress(const planner::ExactSearch& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export live search progress, limits and any checked upper incumbent. |
| inputs / outputs | Const ExactSearch owner in; owning progress DOM with certificate=null out. |
| invariants | Reads binding first, then progress/limits/incumbent. A moved-from owner rejects binding even though progress() alone can report moved_from. Serialization does not advance, replay or mint a completed proof. |
| ownership | SearchBinding/incumbent copies retain actual immutable shared owners; scalar progress/limits copy inline; query/incumbent DOM deep-copies ordinary metadata. |
| failure | Binding/moved-from/serializer/DOM/OOM errors propagate; snapshots are sequential synchronous reads, with no added concurrent mutation synchronization. |
| cost | Scalar getters O(1), full query-binding export and optional incumbent-tree export may validate/copy/allocate; no clock read or quantum charge. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 99–110](../../../../../src/io/search.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_replay_progress(const planner::CertificateReplay& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export live independent certificate-replay progress without exporting unchecked proof authority. |
| inputs / outputs | Const CertificateReplay owner in; query binding, phase/stops/completion/validity/checked_claims/counters/limits DOM out, certificate=null. |
| invariants | Reads actual live owner; report valid flag alone is not a Verified* handle. Moved-from binding rejects before progress serialization. |
| ownership | Binding shared handle retained locally; scalar snapshot copied; ordinary DOM owns exported query/labels. |
| failure | Moved-from/binding/document/DOM allocation failures propagate, no replay advancement. |
| cost | O(query/catalog serialization+bytes)+fixed progress records; allocating IO outside controlled replay transitions. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [include/crown/io/search.hpp](../../../../../include/crown/io/search.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/io/query_binding.hpp](../../../../../src/io/query_binding.hpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 111–111](../../../../../src/io/search.cpp#L111); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L111:sha256:a992a30ac7c9748c33994a213cb5eed12f62a6204d01f8b49f69db451a145039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/search.cpp](../../../../../src/io/search.cpp), [docs/code_specs/files/src/io/search.cpp.md](search.cpp.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/selection.md](../../../../selection.md) |
