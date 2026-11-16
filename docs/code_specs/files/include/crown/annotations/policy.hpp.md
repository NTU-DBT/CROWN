# `include/crown/annotations/policy.hpp` — block usage map

[Source](../../../../../../include/crown/annotations/policy.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit W01 annotation policies and implement exact bounded support/aggregate arithmetic.

Snapshot SHA-256: `4323850b1eef6e594dc8882653e967e79f66751e05d294860ea22a1f681aac81`. 134 lines partitioned into 26 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [annotations](../../../../subsystem_contracts.md#annotations). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/annotations.md](../../../../../annotations.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/annotations/policy.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Presence belongs to support, never to the sign or zero of a SUM payload. · [reviewed contract](#b0001) |
| [B0002 · 13–17](../../../../../../include/crown/annotations/policy.hpp#L13) | Type/record definition: struct Multiplicity | returns value != 0; source comment (unverified): // Presence belongs to support, never to the sign or zero of a SUM payload. · [reviewed contract](#b0002) |
| [B0003 · 18–21](../../../../../../include/crown/annotations/policy.hpp#L18) | Type/record definition: struct IntegerPayload |  · [reviewed contract](#b0003) |
| [B0004 · 22–25](../../../../../../include/crown/annotations/policy.hpp#L22) | Type/record definition: struct DecimalPayload |  · [reviewed contract](#b0004) |
| [B0005 · 26–26](../../../../../../include/crown/annotations/policy.hpp#L26) | Explanatory comments or spacing. |  |
| [B0006 · 27–38](../../../../../../include/crown/annotations/policy.hpp#L27) | Type/record definition: class MultiplicityPolicy |  · [reviewed contract](#b0006) |
| [B0007 · 39–39](../../../../../../include/crown/annotations/policy.hpp#L39) | Explanatory comments or spacing. |  |
| [B0008 · 40–48](../../../../../../include/crown/annotations/policy.hpp#L40) | Type/record definition: struct IntegerPolicy | source comment (unverified): // Checks the final exact total-old+next, even if an intermediate is outside int64. · [reviewed contract](#b0008) |
| [B0009 · 49–49](../../../../../../include/crown/annotations/policy.hpp#L49) | Explanatory comments or spacing. |  |
| [B0010 · 50–65](../../../../../../include/crown/annotations/policy.hpp#L50) | Type/record definition: class DecimalPolicy | returns specification_; source comment (unverified): // Every operand and result must fit DECIMAL(p,s). No rounding or rescaling loss. · [reviewed contract](#b0010) |
| [B0011 · 66–66](../../../../../../include/crown/annotations/policy.hpp#L66) | Explanatory comments or spacing. |  |
| [B0012 · 67–72](../../../../../../include/crown/annotations/policy.hpp#L67) | Type/record definition: template&lt;class Payload&gt; struct Annotation | returns support.present() · [reviewed contract](#b0012) |
| [B0013 · 73–73](../../../../../../include/crown/annotations/policy.hpp#L73) | Type/record definition: enum class MembershipChange |  · [reviewed contract](#b0013) |
| [B0014 · 74–82](../../../../../../include/crown/annotations/policy.hpp#L74) | Type/record definition: template&lt;class Payload&gt; struct ValueChange | returns MembershipChange::unchanged; after.present() ? MembershipChange::appeared : MembershipChange::disap… · [reviewed contract](#b0014) |
| [B0015 · 83–85](../../../../../../include/crown/annotations/policy.hpp#L83) | Explanatory comments or spacing. | source comment (unverified): // Pure preparation: callers publish the returned value only after every policy · [reviewed contract](#b0015) |
| [B0016 · 86–99](../../../../../../include/crown/annotations/policy.hpp#L86) | Callable definition: template&lt;class Payload, class Policy&gt; \[\[nodiscard\]\] Annotation&lt;Payload&gt; replace_contribution(const Annotation&lt;Payload&gt;& total, co… | calls present, Error, replace; returns {support, payload}; 1 loop sites; source comment (unverified): // Pure preparation: callers publish the returned value only after every policy · [reviewed contract](#b0016) |
| [B0017 · 100–100](../../../../../../include/crown/annotations/policy.hpp#L100) | Explanatory comments or spacing. |  |
| [B0018 · 101–102](../../../../../../include/crown/annotations/policy.hpp#L101) | Type/record definition: enum class Domain |  · [reviewed contract](#b0018) |
| [B0019 · 103–103](../../../../../../include/crown/annotations/policy.hpp#L103) | Type/record definition: enum class Deletion |  · [reviewed contract](#b0019) |
| [B0020 · 104–104](../../../../../../include/crown/annotations/policy.hpp#L104) | Type/record definition: enum class Backend |  · [reviewed contract](#b0020) |
| [B0021 · 105–105](../../../../../../include/crown/annotations/policy.hpp#L105) | Type/record definition: enum class Representation |  · [reviewed contract](#b0021) |
| [B0022 · 106–114](../../../../../../include/crown/annotations/policy.hpp#L106) | Type/record definition: struct Capabilities |  · [reviewed contract](#b0022) |
| [B0023 · 115–119](../../../../../../include/crown/annotations/policy.hpp#L115) | Type/record definition: struct Request |  · [reviewed contract](#b0023) |
| [B0024 · 120–121](../../../../../../include/crown/annotations/policy.hpp#L120) | Type/record definition: enum class AdmissionStatus |  · [reviewed contract](#b0024) |
| [B0025 · 122–127](../../../../../../include/crown/annotations/policy.hpp#L122) | Type/record definition: struct Admission | returns status == AdmissionStatus::admitted · [reviewed contract](#b0025) |
| [B0026 · 128–134](../../../../../../include/crown/annotations/policy.hpp#L128) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Closed registry: caller-provided algebra traits cannot confer backend authority. · [reviewed contract](#b0026) |

## B0001

[Lines 1–12](../../../../../../include/crown/annotations/policy.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the closed annotation value, arithmetic and capability interface. |
| inputs / outputs | Imports shared scalar/model/error types and standard integer/optional support; introduces crown::annotations. |
| invariants | Kernel availability is separate from SQL admission, runtime transaction ownership and paper update bounds. |
| ownership | Declarations create no query account, state registry or runtime object. |
| failure | No runtime failure at declaration; each callable has its own contract. |
| cost | Compile-time dependency boundary; no executable per-row instrumentation. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0002

[Lines 13–17](../../../../../../include/crown/annotations/policy.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Multiplicity {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a nonnegative logical weight and its presence boundary. |
| inputs / outputs | uint64 value defaults to zero; present() tests nonzero; default comparison orders the complete count. |
| invariants | Zero means absence. The carrier alone does not enforce a policy-specific positive maximum or authenticate a source contribution. |
| ownership | One inline integer, copied by value; no payload owner. |
| failure | Presence and built-in integer comparisons do not throw. |
| cost | Fixed scalar storage and operations; no allocation. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0003

[Lines 18–21](../../../../../../include/crown/annotations/policy.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IntegerPayload {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a signed SUM-like payload independently of support. |
| inputs / outputs | int64 value defaults to zero and compares by its complete signed value. |
| invariants | A zero or negative payload does not decide whether a group exists; use Multiplicity support. |
| ownership | Inline value with ordinary value copies. |
| failure | Carrier comparison does not throw; arithmetic policy separately checks results. |
| cost | Fixed scalar storage/comparison, no allocation. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0004

[Lines 22–25](../../../../../../include/crown/annotations/policy.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DecimalPayload {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an exact canonical decimal payload independently of support. |
| inputs / outputs | Decimal member defaults to zero; equality compares its canonical value representation. |
| invariants | Decimal has at most 38 coefficient digits and scale 0..38; a DecimalPolicy supplies any narrower fixed domain. |
| ownership | The Decimal owns ordinary string storage; this carrier is not account-funded native retained state. |
| failure | Decimal construction/copy can propagate allocation failure; equality does not construct an owning conversion. |
| cost | Copying can copy coefficient bytes; equality compares bounded canonical state and bytes. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0006

[Lines 27–38](../../../../../../include/crown/annotations/policy.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class MultiplicityPolicy {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose checked uint64 count arithmetic under one positive configured maximum. |
| inputs / outputs | Constructor selects a limit; add/multiply/remove/replace return new Multiplicity values. |
| invariants | Every supplied operand and stored result must fit the selected maximum; removal cannot exceed its current total. |
| ownership | The policy owns one inline limit; inputs remain caller-owned values. |
| failure | Invalid limit, overflow and underflow reject through Error; this supplies no owning transaction. |
| cost | Fixed-width arithmetic/checks; no successful-path row, container or account allocation. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0008

[Lines 40–48](../../../../../../include/crown/annotations/policy.hpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IntegerPolicy {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose exact signed int64 arithmetic with wider private intermediate values. |
| inputs / outputs | Signed add/product/remove/replace and signed-payload times full unsigned Multiplicity return IntegerPayload. |
| invariants | Final results must fit int64. Replacement checks total-old+next without requiring its intermediate to fit. |
| ownership | Stateless policy; immutable inputs and returned inline payload. |
| failure | Out-of-domain final value raises annotation_overflow; no input is modified. |
| cost | Bounded stack digit arithmetic and final conversion; no successful-result heap payload. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0010

[Lines 50–65](../../../../../../include/crown/annotations/policy.hpp#L50); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class DecimalPolicy {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose exact arithmetic constrained to DECIMAL(p,s). |
| inputs / outputs | Constructor validates DecimalSpec; specification() returns it; operations return canonical DecimalPayload. |
| invariants | 1 &lt;= p &lt;= 38 and s &lt;= p; operands and final value fit. Insignificant zeros may be removed, but rounding is not supplied. |
| ownership | Inline spec plus caller-owned Decimal operands; returned Decimal owns ordinary scalar text. |
| failure | Invalid spec or domain overflow rejects; result text/Decimal allocation can fail before return. |
| cost | Bounded stack arithmetic plus actual canonical-text construction/copy; not an allocation-free native update claim. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0012

[Lines 67–72](../../../../../../include/crown/annotations/policy.hpp#L67); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Payload> struct Annotation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair row/group support with an independently meaningful aggregate payload. |
| inputs / outputs | Multiplicity support and caller-selected Payload form a value; equality compares both. |
| invariants | Support alone determines presence; payload cancellation cannot erase a live group. |
| ownership | Owns its Payload by value; nested ownership/copy cost follows that type. |
| failure | Generic payload construction/equality may throw; the carrier adds no rollback. |
| cost | Fixed support work plus Payload storage, copy and equality costs. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

```text
[[nodiscard]] bool present() const noexcept { return support.present(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test annotation membership without inspecting numeric payload. |
| inputs / outputs | Returns whether this value has positive support. |
| invariants | A live zero-SUM annotation remains present; an absent nonzero payload is rejected by preparation, not silently accepted by this predicate. |
| ownership | Borrows the inline support only. |
| failure | Noexcept, no allocation or mutation. |
| cost | One uint64 nonzero comparison. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0013

[Lines 73–73](../../../../../../include/crown/annotations/policy.hpp#L73); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class MembershipChange {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the three zero-crossing outcomes of a value replacement. |
| inputs / outputs | unchanged, appeared or disappeared describes membership only. |
| invariants | Positive-to-positive count or payload changes can still be membership unchanged. |
| ownership | Plain enum value; no object lifetime authority. |
| failure | No runtime failure in the declaration. |
| cost | Fixed enum storage, no allocation. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0014

[Lines 74–82](../../../../../../include/crown/annotations/policy.hpp#L74); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Payload> struct ValueChange {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain complete before/after annotations for separate membership, count and payload observations. |
| inputs / outputs | Two owned Annotation&lt;Payload&gt; values feed three predicates. |
| invariants | No predicate coalesces a logical epoch or implies that an ancestor needs no numeric event. |
| ownership | Owns both payloads; callers fund their construction/copies. |
| failure | Payload construction/copy can fail before the carrier is prepared; no runtime rollback is provided. |
| cost | Two annotation values plus their real nested payload storage. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

```text
[[nodiscard]] MembershipChange membership() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify only the support zero crossing. |
| inputs / outputs | Before/after support presence yields unchanged, appeared or disappeared. |
| invariants | Two positive counts return unchanged even when their magnitude/payload differs. |
| ownership | Reads inline support; no payload borrow escapes. |
| failure | Noexcept and nonallocating. |
| cost | At most three fixed presence tests. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

```text
[[nodiscard]] bool support_changed() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe any count change, including positive-to-positive replacement. |
| inputs / outputs | Returns before.support != after.support. |
| invariants | This is distinct from membership(); it must not be replaced by a zero-crossing test in numeric propagation. |
| ownership | Borrows the two inline counts. |
| failure | Noexcept and nonallocating. |
| cost | One fixed-width comparison. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

```text
[[nodiscard]] bool payload_changed() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe payload changes independently of support. |
| inputs / outputs | Returns inequality of the before/after Payload values. |
| invariants | Generic Payload equality must represent the caller's intended exact payload equality. |
| ownership | Borrows payloads; no automatic numeric conversion or retained result. |
| failure | Payload equality can throw; this predicate deliberately has no blanket noexcept or catch. |
| cost | Actual Payload equality cost, including coefficient-byte comparison for Decimal. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0015

[Lines 83–85](../../../../../../include/crown/annotations/policy.hpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L85:sha256:302d27e9886e71de377a31ae3e916d0daa142bc30f8319a43f346c0a4099db27
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Pure preparation: callers publish the returned value only after every policy check succeeds. This supplies no runtime transaction or ancestor rollback. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/annotations/policy.hpp lines 81-87; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/annotations/policy.hpp](../../../../../../include/crown/annotations/policy.hpp), [docs/code_specs/files/include/crown/annotations/policy.hpp.md](policy.hpp.md), [docs/annotations.md](../../../../../annotations.md), [docs/invariant_memory.md](../../../../../invariant_memory.md) |

## B0016

[Lines 86–99](../../../../../../include/crown/annotations/policy.hpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Annotation<Payload> replace_contribution(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare replacement support and payload together before the caller publishes either. |
| inputs / outputs | Const total/old/next annotations and pure count/payload policies yield a new annotation. |
| invariants | Caller supplies pure arithmetic policies and a Payload for which Payload{} is their exact additive zero and equality implements the intended exact value/zero relation. Every absent input and absent result must have that zero payload; caller establishes old-contribution provenance. |
| ownership | Inputs remain owned by caller; returned Payload owns its result. No runtime, memory account or ancestor journal is created. |
| failure | Invalid absence encoding, policy arithmetic, default-payload construction/equality or allocation failures propagate before return; no partial result is published. |
| cost | Three input presence tests; only absent inputs construct/compare Payload{}. Count and payload replacements, one result-presence test and a conditional result-zero check follow. Returning {support,payload} copies the named payload lvalue, so generic/Decimal copying can allocate in addition to policy work. |
| Design | [docs/annotations.md](../../../../../annotations.md), [docs/weighted_messages.md](../../../../../weighted_messages.md), [Refactor.md §10.2 and W01](../../../../../../Refactor.md) |

## B0018

[Lines 101–102](../../../../../../include/crown/annotations/policy.hpp#L101); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Domain {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select a built-in arithmetic domain for explicit capability admission. |
| inputs / outputs | Boolean support, nonnegative counts, signed integer, fixed decimal, general semiring and approximate tags enter admit(). |
| invariants | An enum tag alone confers no implementation or runtime guarantee; unsupported/unknown domains reject. |
| ownership | Inline request metadata, no plugin registry. |
| failure | Declaration does not throw; admit returns a rejection status. |
| cost | Fixed dispatch tag. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0019

[Lines 103–103](../../../../../../include/crown/annotations/policy.hpp#L103); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Deletion {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish no deletion, algebraic exact retraction and replacement using retained witness information. |
| inputs / outputs | Request carries none, exact_retraction or replacement. |
| invariants | Boolean OR has no arithmetic inverse; its set backend can use replacement from separately maintained support. |
| ownership | Inline request metadata. |
| failure | Unsupported or unknown modes return unsupported_deletion where earlier domain checks admit. |
| cost | Fixed enum storage/checks. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0020

[Lines 104–104](../../../../../../include/crown/annotations/policy.hpp#L104); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Backend {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the closed arithmetic, set-tree and weighted-message implementations. |
| inputs / outputs | admit pairs backend selection with a domain rather than trusting caller-supplied algebra traits. |
| invariants | The set backend accepts Boolean support; weighted messages accept nonnegative multiplicity; payload kernels alone confer neither backend. |
| ownership | No dynamic backend registration or retained dispatch object. |
| failure | Unsupported backend/domain pairs return unsupported_backend. |
| cost | Fixed dispatch. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0021

[Lines 105–105](../../../../../../include/crown/annotations/policy.hpp#L105); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Representation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the implemented successful arithmetic representation. |
| inputs / outputs | fixed_word, bounded_decimal or unspecified accompanies capabilities. |
| invariants | This describes arithmetic storage, not a CPU-time, allocator or query-delay certificate. |
| ownership | Inline result metadata. |
| failure | No declaration-time failure. |
| cost | Fixed enum field. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0022

[Lines 106–114](../../../../../../include/crown/annotations/policy.hpp#L106); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Capabilities {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe audited algebra properties for admitted built-in domains. |
| inputs / outputs | Exactness, zero-sum freedom, no zero divisors, cancellation, retraction, replacement and representation are returned as value fields. |
| invariants | Properties concern exact underlying arithmetic on successful in-domain operations; bounded arithmetic is partial. Inspect Admission.status before using them as admission. |
| ownership | Fixed-size value, no proof token or caller extension point. |
| failure | No field access throws; incorrect caller inference is not validated here. |
| cost | Fixed field initialization/copy. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0023

[Lines 115–119](../../../../../../include/crown/annotations/policy.hpp#L115); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Request {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the requested built-in domain, deletion strategy and optional decimal specification. |
| inputs / outputs | Defaults request Boolean support with replacement and no DecimalSpec. |
| invariants | Fixed decimal requires a valid spec; other domains must not carry a decimal spec. |
| ownership | Owns only inline enum/optional spec metadata. |
| failure | Validation is deferred to admit(). |
| cost | Fixed storage/copy, no allocation. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0024

[Lines 120–121](../../../../../../include/crown/annotations/policy.hpp#L120); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class AdmissionStatus {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve explicit reasons that arithmetic/backend admission failed. |
| inputs / outputs | Status distinguishes admitted, unknown domain, unsupported algebra, invalid/unexpected decimal, unsupported deletion and unsupported backend. |
| invariants | No unsupported request silently defaults to Boolean or a different backend. |
| ownership | Inline diagnostic classification; no owning diagnostic string. |
| failure | No declaration-time failure. |
| cost | Fixed enum storage. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0025

[Lines 122–127](../../../../../../include/crown/annotations/policy.hpp#L122); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Admission {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return capability admission and the static policy name as a small value. |
| inputs / outputs | Status, capabilities and string_view policy accompany admitted() status comparison. |
| invariants | Non-admitted records may already contain domain capabilities/name; status remains the authority. |
| ownership | Policy names borrow static literals; no caller/request string is retained. |
| failure | admitted() is noexcept; no string allocation occurs in this carrier. |
| cost | Fixed value fields and one enum comparison. |
| Design | [docs/annotations.md](../../../../../annotations.md) |

## B0026

[Lines 128–134](../../../../../../include/crown/annotations/policy.hpp#L128); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Admission admit(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the closed no-throw capability selector and set-policy authority gate. |
| inputs / outputs | admit returns a status for a Request/Backend; require_set_backend_policy validates the actual set plan policy string. |
| invariants | User algebra traits cannot grant execution authority; arithmetic admission implies no maintenance or enumeration theorem. |
| ownership | Request/string inputs are borrowed during calls; returned policy view is static. |
| failure | admit is noexcept/status-based; set-policy rejection throws invalid_policy. |
| cost | Bounded enum/decimal checks and a short policy-name comparison; no successful-path allocation. |
| Design | [docs/annotations.md](../../../../../annotations.md), [docs/semantics.md](../../../../../semantics.md), [docs/weighted_messages.md](../../../../../weighted_messages.md) |
