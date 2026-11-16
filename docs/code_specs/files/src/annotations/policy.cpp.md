# `src/annotations/policy.cpp` — block usage map

[Source](../../../../../src/annotations/policy.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit W01 annotation policies and implement exact bounded support/aggregate arithmetic.

Snapshot SHA-256: `e16b2f00f59f76893c92aed73fcf308bec6dfb6f05a166caf861ecaa639dc7fa`. 257 lines partitioned into 40 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [annotations](../../../subsystem_contracts.md#annotations). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/annotations.md](../../../../annotations.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/annotations/policy.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–12](../../../../../src/annotations/policy.cpp#L10) | Callable definition: \[\[noreturn\]\] void overflow() | calls Error · [reviewed contract](#b0002) |
| [B0003 · 13–15](../../../../../src/annotations/policy.cpp#L13) | Callable definition: bool valid_spec(DecimalSpec spec) noexcept | calls ; returns spec.precision &gt;= 1 && spec.precision &lt;= 38 && spec.scale &lt;= spec.precision · [reviewed contract](#b0003) |
| [B0004 · 16–17](../../../../../src/annotations/policy.cpp#L16) | Explanatory comments or spacing. | source comment (unverified): // At most 76 aligned/product digits, plus a carry for a three-term replacement. · [reviewed contract](#b0004) |
| [B0005 · 18–22](../../../../../src/annotations/policy.cpp#L18) | Type/record definition: struct Coefficient | source comment (unverified): // At most 76 aligned/product digits, plus a carry for a three-term replacement. · [reviewed contract](#b0005) |
| [B0006 · 23–26](../../../../../src/annotations/policy.cpp#L23) | Callable definition: void normalize(Coefficient& value) | calls ; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 27–35](../../../../../src/annotations/policy.cpp#L27) | Callable definition: Coefficient coefficient(std::uint64_t value) | calls ; returns result; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 36–42](../../../../../src/annotations/policy.cpp#L36) | Callable definition: Coefficient coefficient(IntegerPayload value) | calls ; returns result · [reviewed contract](#b0008) |
| [B0009 · 43–53](../../../../../src/annotations/policy.cpp#L43) | Callable definition: Coefficient coefficient(const DecimalPayload& value, std::uint32_t scale) | calls parts, size, normalize; returns result; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 54–59](../../../../../src/annotations/policy.cpp#L54) | Callable definition: int compare(const Coefficient& a, const Coefficient& b) | calls ; returns a.size &lt; b.size ? -1 : 1; a.digits\[i - 1\] &lt; b.digits\[i - 1\] ? -1 : 1; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 60–64](../../../../../src/annotations/policy.cpp#L60) | Callable definition: Coefficient negate(Coefficient value) | calls normalize; returns value · [reviewed contract](#b0011) |
| [B0012 · 65–92](../../../../../src/annotations/policy.cpp#L65) | Callable definition: Coefficient add(const Coefficient& a, const Coefficient& b) | calls std::max, compare, normalize; returns result; 2 loop sites · [reviewed contract](#b0012) |
| [B0013 · 93–109](../../../../../src/annotations/policy.cpp#L93) | Callable definition: Coefficient multiply(const Coefficient& a, const Coefficient& b) | calls normalize; returns result; 3 loop sites · [reviewed contract](#b0013) |
| [B0014 · 110–122](../../../../../src/annotations/policy.cpp#L110) | Callable definition: IntegerPayload integer(const Coefficient& value) | calls max, overflow, min; returns {std::numeric_limits&lt;std::int64_t&gt;::min()}; {value.negative ? -result : result}; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 123–141](../../../../../src/annotations/policy.cpp#L123) | Callable definition: DecimalPayload decimal(Coefficient value, std::uint32_t scale, DecimalSpec spec) | calls std::move, begin, overflow, push_back; returns {}; {Decimal::parse(text)}; growth push_back; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 142–143](../../../../../src/annotations/policy.cpp#L142) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0016) |
| [B0017 · 144–146](../../../../../src/annotations/policy.cpp#L144) | Callable definition: MultiplicityPolicy::MultiplicityPolicy(std::uint64_t limit) : limit_(limit) | calls limit_, Error · [reviewed contract](#b0017) |
| [B0018 · 147–149](../../../../../src/annotations/policy.cpp#L147) | Callable definition: void MultiplicityPolicy::validate(Multiplicity value) const | calls overflow · [reviewed contract](#b0018) |
| [B0019 · 150–154](../../../../../src/annotations/policy.cpp#L150) | Callable definition: Multiplicity MultiplicityPolicy::add(Multiplicity a, Multiplicity b) const | calls validate, overflow; returns {a.value + b.value} · [reviewed contract](#b0019) |
| [B0020 · 155–159](../../../../../src/annotations/policy.cpp#L155) | Callable definition: Multiplicity MultiplicityPolicy::multiply(Multiplicity a, Multiplicity b) const | calls validate, overflow; returns {a.value * b.value} · [reviewed contract](#b0020) |
| [B0021 · 160–164](../../../../../src/annotations/policy.cpp#L160) | Callable definition: Multiplicity MultiplicityPolicy::remove(Multiplicity total, Multiplicity old) const | calls validate, Error; returns {total.value - old.value} · [reviewed contract](#b0021) |
| [B0022 · 165–167](../../../../../src/annotations/policy.cpp#L165) | Callable definition: Multiplicity MultiplicityPolicy::replace(Multiplicity total, Multiplicity old, Multiplicity next) const | calls add, remove; returns add(remove(total, old), next) · [reviewed contract](#b0022) |
| [B0023 · 168–168](../../../../../src/annotations/policy.cpp#L168) | Explanatory comments or spacing. |  |
| [B0024 · 169–171](../../../../../src/annotations/policy.cpp#L169) | Callable definition: IntegerPayload IntegerPolicy::add(IntegerPayload a, IntegerPayload b) | calls integer, annotations::add, coefficient; returns integer(annotations::add(coefficient(a), coefficient(b))) · [reviewed contract](#b0024) |
| [B0025 · 172–174](../../../../../src/annotations/policy.cpp#L172) | Callable definition: IntegerPayload IntegerPolicy::multiply(IntegerPayload a, IntegerPayload b) | calls integer, annotations::multiply, coefficient; returns integer(annotations::multiply(coefficient(a), coefficient(b))) · [reviewed contract](#b0025) |
| [B0026 · 175–177](../../../../../src/annotations/policy.cpp#L175) | Callable definition: IntegerPayload IntegerPolicy::multiply(IntegerPayload a, Multiplicity b) | calls integer, annotations::multiply, coefficient; returns integer(annotations::multiply(coefficient(a), coefficient(b.value))) · [reviewed contract](#b0026) |
| [B0027 · 178–180](../../../../../src/annotations/policy.cpp#L178) | Callable definition: IntegerPayload IntegerPolicy::remove(IntegerPayload total, IntegerPayload old) | calls integer, annotations::add, coefficient, negate; returns integer(annotations::add(coefficient(total), negate(coefficient(old)))) · [reviewed contract](#b0027) |
| [B0028 · 181–183](../../../../../src/annotations/policy.cpp#L181) | Callable definition: IntegerPayload IntegerPolicy::replace(IntegerPayload total, IntegerPayload old, IntegerPayload next) | calls integer, annotations::add, coefficient, negate; returns integer(annotations::add(annotations::add(coefficient(total), negate(coefficient(old))), coefficien… · [reviewed contract](#b0028) |
| [B0029 · 184–184](../../../../../src/annotations/policy.cpp#L184) | Explanatory comments or spacing. |  |
| [B0030 · 185–187](../../../../../src/annotations/policy.cpp#L185) | Callable definition: DecimalPolicy::DecimalPolicy(DecimalSpec spec) : specification_(spec) | calls specification_, valid_spec, Error · [reviewed contract](#b0030) |
| [B0031 · 188–192](../../../../../src/annotations/policy.cpp#L188) | Callable definition: void DecimalPolicy::validate(const DecimalPayload& value) const | calls parts, size, overflow · [reviewed contract](#b0031) |
| [B0032 · 193–197](../../../../../src/annotations/policy.cpp#L193) | Callable definition: DecimalPayload DecimalPolicy::add(const DecimalPayload& a, const DecimalPayload& b) const | calls validate, std::max, parts, decimal; returns decimal(annotations::add(coefficient(a, scale), coefficient(b, scale)), scale, specification_) · [reviewed contract](#b0032) |
| [B0033 · 198–203](../../../../../src/annotations/policy.cpp#L198) | Callable definition: DecimalPayload DecimalPolicy::multiply(const DecimalPayload& a, const DecimalPayload& b) const | calls validate, parts, decimal, annotations::multiply; returns decimal(annotations::multiply(coefficient(a, left_scale), coefficient(b, right_scale)), · [reviewed contract](#b0033) |
| [B0034 · 204–208](../../../../../src/annotations/policy.cpp#L204) | Callable definition: DecimalPayload DecimalPolicy::multiply(const DecimalPayload& a, Multiplicity b) const | calls validate, parts, decimal, annotations::multiply; returns decimal(annotations::multiply(coefficient(a, scale), coefficient(b.value)), scale, specification_) · [reviewed contract](#b0034) |
| [B0035 · 209–211](../../../../../src/annotations/policy.cpp#L209) | Callable definition: DecimalPayload DecimalPolicy::remove(const DecimalPayload& total, const DecimalPayload& old) const | calls replace; returns replace(total, old, {}) · [reviewed contract](#b0035) |
| [B0036 · 212–217](../../../../../src/annotations/policy.cpp#L212) | Callable definition: DecimalPayload DecimalPolicy::replace(const DecimalPayload& total, const DecimalPayload& old, const DecimalPayload& next) const | calls validate, std::max, parts, decimal; returns decimal(annotations::add(annotations::add(coefficient(total, scale), negate(coefficient(old, scale)… · [reviewed contract](#b0036) |
| [B0037 · 218–218](../../../../../src/annotations/policy.cpp#L218) | Explanatory comments or spacing. |  |
| [B0038 · 219–251](../../../../../src/annotations/policy.cpp#L219) | Callable definition: Admission admit(const Request& request, Backend backend) noexcept | calls valid_spec; returns result; result · [reviewed contract](#b0038) |
| [B0039 · 252–256](../../../../../src/annotations/policy.cpp#L252) | Callable definition: void require_set_backend_policy(std::string_view policy) | calls admit, admitted, Error · [reviewed contract](#b0039) |
| [B0040 · 257–257](../../../../../src/annotations/policy.cpp#L257) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::annotations · [reviewed contract](#b0040) |

## B0001

[Lines 1–9](../../../../../src/annotations/policy.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/annotations/policy.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the closed policies with local bounded decimal scratch. |
| inputs / outputs | Imports the public policy, fixed arrays, algorithms and ordinary text for final Decimal construction. |
| invariants | Private helpers are arithmetic implementation details and confer no SQL or runtime transaction admission. |
| ownership | No global mutable state or per-query helper registry. |
| failure | Declaration region does not execute arithmetic or allocate. |
| cost | Compile-time dependency boundary only. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0002

[Lines 10–12](../../../../../src/annotations/policy.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void overflow()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report a domain overflow consistently across exact arithmetic kernels. |
| inputs / outputs | No value result; throws Error(annotation_overflow) with a fixed explanatory message. |
| invariants | Callers invoke this before returning an out-of-domain result; input values are const/by-value. |
| ownership | Error owns its presentation strings; no arithmetic scratch or runtime state is published. |
| failure | Error/string construction can itself encounter allocation failure; this is not a fixed nonallocating exception type. |
| cost | Error path only; successful arithmetic does not call it. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0003

[Lines 13–15](../../../../../src/annotations/policy.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool valid_spec(DecimalSpec spec) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the supported fixed-decimal precision/scale pair. |
| inputs / outputs | Returns 1 &lt;= precision &lt;= 38 and scale &lt;= precision. |
| invariants | Scale is unsigned; the lower bound zero is inherent in its type. |
| ownership | Borrows/copies two scalar fields only. |
| failure | Noexcept, returns false rather than formatting an error. |
| cost | Three bounded integer comparisons. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0004

[Lines 16–17](../../../../../src/annotations/policy.cpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L17:sha256:28c109bfad72844ce2cfdb4df6e3dcf896ffc27701c99b6bc143ba17bb3fd195
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: At most 76 aligned/product digits, plus a carry for a three-term replacement. All scratch arithmetic stays on the stack; only the final Decimal owns text. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/annotations/policy.cpp lines 14-19; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/annotations/policy.cpp](../../../../../src/annotations/policy.cpp), [docs/code_specs/files/src/annotations/policy.cpp.md](policy.cpp.md), [docs/annotations.md](../../../../annotations.md), [docs/invariant_memory.md](../../../../invariant_memory.md) |

## B0005

[Lines 18–22](../../../../../src/annotations/policy.cpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Coefficient {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold exact signed-magnitude base-ten scratch for wider intermediates. |
| inputs / outputs | 80 zeroed least-significant-first digit slots, live size and sign form a temporary coefficient. |
| invariants | Private callers keep 1 &lt;= size &lt;= 80, digits in 0..9 and canonical high end; aligned sums/products use at most 77 live digits. |
| ownership | All scratch storage is inline/stack, including whole-value copies. |
| failure | There are no dynamic capacity checks: the public operand/spec bounds and helper call graph establish capacity. |
| cost | Fixed 80-slot storage/initialization; no heap allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0006

[Lines 23–26](../../../../../src/annotations/policy.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void normalize(Coefficient& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove high insignificant magnitude zeros and clear negative zero. |
| inputs / outputs | Mutates a private valid Coefficient in place. |
| invariants | Keeps at least one digit; normalization does not remove fractional low zeros or change the represented number. |
| ownership | Borrowed private stack scratch only. |
| failure | No throwing operation; relies on valid size/digits established by callers. |
| cost | At most the bounded digit width; no allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0007

[Lines 27–35](../../../../../src/annotations/policy.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Coefficient coefficient(std::uint64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expand a full unsigned count into private decimal digits. |
| inputs / outputs | uint64 input produces a positive canonical Coefficient, including one digit for zero. |
| invariants | At most 20 digits are needed and fit the 80-slot array. |
| ownership | Returns inline stack scratch by value. |
| failure | No dynamic storage or arithmetic overflow in repeated division/remainder by ten. |
| cost | At most 20 digit iterations. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0008

[Lines 36–42](../../../../../src/annotations/policy.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Coefficient coefficient(IntegerPayload value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract signed int64 magnitude without negating INT64_MIN. |
| inputs / outputs | IntegerPayload becomes unsigned magnitude digits plus its sign. |
| invariants | Unsigned zero-minus-converted-negative handles the minimum signed value exactly. |
| ownership | Inline temporary/result only. |
| failure | No throwing operation for a valid int64 carrier. |
| cost | One sign/magnitude conversion plus at most 19 magnitude digit iterations. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0009

[Lines 43–53](../../../../../src/annotations/policy.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Coefficient coefficient(const DecimalPayload& value, std::uint32_t scale)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Align a canonical decimal coefficient to a caller-selected common scale. |
| inputs / outputs | Validated DecimalPayload and scale &gt;= operand scale produce shifted least-significant-first digits. |
| invariants | Callers choose scale from validated operand scales for addition/replacement; multiplication passes each operand's own scale. Alignment fits the private array. |
| ownership | Borrows DecimalParts during the call; output owns inline digits and retains no string view. |
| failure | Relies on validated canonical Decimal/spec and nonnegative scale difference; no public arbitrary-scale entry point or heap allocation. |
| cost | Zeroed 80-slot scratch plus one pass over at most 38 original coefficient digits, followed by normalize(). For an aligned zero operand, normalization can scan the bounded aligned width (at most 76 positions); no heap allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0010

[Lines 54–59](../../../../../src/annotations/policy.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int compare(const Coefficient& a, const Coefficient& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare canonical magnitudes for signed addition/subtraction. |
| inputs / outputs | Two private coefficients yield -1, 0 or 1; their sign bits are deliberately ignored. |
| invariants | Live size/top-digit normalization makes size comparison a valid magnitude comparison. |
| ownership | Borrows both stack arrays. |
| failure | No dynamic work can throw; callers provide valid sizes/digits. |
| cost | Size check followed by at most the bounded live digit width. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0011

[Lines 60–64](../../../../../src/annotations/policy.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Coefficient negate(Coefficient value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce the opposite signed scratch magnitude for subtraction. |
| inputs / outputs | A by-value coefficient has its sign toggled and negative zero normalized. |
| invariants | The caller's operand is unchanged and zero remains positive. |
| ownership | Inline coefficient copy/result. |
| failure | No allocation or external state change. |
| cost | Fixed-array copy plus bounded normalization. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0012

[Lines 65–92](../../../../../src/annotations/policy.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Coefficient add(const Coefficient& a, const Coefficient& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add signed magnitudes exactly beyond public result ranges. |
| inputs / outputs | Same signs use digit carry; opposite signs subtract smaller magnitude from larger with borrow. |
| invariants | Zeroed unused tails and caller-proven capacity make indexed digit reads/writes valid; normalize clears high zeros/negative zero. |
| ownership | Borrows operands; result and carry/borrow live on the stack. |
| failure | No public-domain check or exception here; final integer()/decimal() checks the result. |
| cost | Bounded O(max live digit width), plus magnitude comparison when signs differ; no allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0013

[Lines 93–109](../../../../../src/annotations/policy.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Coefficient multiply(const Coefficient& a, const Coefficient& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute an exact wide signed product by schoolbook decimal convolution. |
| inputs / outputs | Validated private coefficients produce a normalized product with XOR sign. |
| invariants | Only public integer/count or original decimal coefficient widths reach multiplication; a.size+b.size fits 80 and each unsigned convolution slot stays small. |
| ownership | 80 unsigned product slots and the returned digit array are stack scratch. |
| failure | No final domain admission here; wider product is checked by the caller conversion. |
| cost | O(a.size*b.size) digit products plus carry pass, bounded by supported public widths; no heap allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0014

[Lines 110–122](../../../../../src/annotations/policy.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IntegerPayload integer(const Coefficient& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a wide exact signed coefficient into int64. |
| inputs / outputs | Canonical scratch digits yield IntegerPayload or annotation_overflow. |
| invariants | Every multiply/add is prechecked against sign-dependent magnitude limit; INT64_MIN is constructed through its explicit special case. |
| ownership | Returns inline value and borrows scratch only during conversion. |
| failure | Overflow is reported before a bad native integer operation; error presentation can allocate. |
| cost | One bounded most-significant-first digit pass; no successful-result allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0015

[Lines 123–141](../../../../../src/annotations/policy.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DecimalPayload decimal(Coefficient value, std::uint32_t scale, DecimalSpec spec)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize exact wide decimal scratch and admit the final fixed-domain value. |
| inputs / outputs | Signed coefficient, arithmetic scale and valid spec yield canonical DecimalPayload. |
| invariants | Only insignificant fractional zeros are removed. Nonzero result must fit 38 coefficient digits, declared scale and integer-digit capacity; zero returns canonical zero. |
| ownership | Scratch is copied inline; final ordinary std::string/Decimal owns its bytes outside any native query account. |
| failure | Domain overflow rejects before a nonconforming result; text construction and Decimal::parse can propagate allocation/errors. Inputs remain unchanged. |
| cost | Bounded repeated digit shifts (quadratic in &lt;= 80 scratch digits), then canonical text emission/parsing and real string allocation/copy. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0016

[Lines 142–143](../../../../../src/annotations/policy.cpp#L142); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L142-L143:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/annotations/policy.cpp](../../../../../src/annotations/policy.cpp), [docs/code_specs/files/src/annotations/policy.cpp.md](policy.cpp.md), [docs/annotations.md](../../../../annotations.md), [docs/invariant_memory.md](../../../../invariant_memory.md) |

## B0017

[Lines 144–146](../../../../../src/annotations/policy.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
MultiplicityPolicy::MultiplicityPolicy(std::uint64_t limit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Establish a positive maximum for every count operation. |
| inputs / outputs | Stores the supplied uint64 limit, including UINT64_MAX. |
| invariants | Zero maximum is invalid; this is an arithmetic ceiling, not a memory/work grant. |
| ownership | One inline member, no account ownership. |
| failure | Zero limit throws invalid_annotation; no completed policy is returned. |
| cost | Fixed check/store; diagnostic allocation only on error. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0018

[Lines 147–149](../../../../../src/annotations/policy.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void MultiplicityPolicy::validate(Multiplicity value) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a count operand above this policy's configured maximum. |
| inputs / outputs | Multiplicity value is checked without changing it. |
| invariants | Every public count operation invokes validation on its supplied operands, even for a mathematical zero/no-op result. |
| ownership | Reads inline policy/count values. |
| failure | Excess raises annotation_overflow. |
| cost | One comparison on success. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0019

[Lines 150–154](../../../../../src/annotations/policy.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Multiplicity MultiplicityPolicy::add(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add two valid nonnegative counts without wraparound. |
| inputs / outputs | Returns a+b only when both operands and the sum fit the configured limit. |
| invariants | Validate a before computing limit-a; compare b to remaining capacity before addition. |
| ownership | Immutable by-value inputs and inline result. |
| failure | Invalid operand/result raises annotation_overflow before return; no state mutation. |
| cost | Fixed validation/subtraction/comparison/addition; no successful allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0020

[Lines 155–159](../../../../../src/annotations/policy.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Multiplicity MultiplicityPolicy::multiply(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Multiply two valid nonnegative counts without wraparound. |
| inputs / outputs | Returns a*b, with a zero divisor avoiding division. |
| invariants | Both operands are validated even if one is zero; a &lt;= limit/b is established before a nonzero product. |
| ownership | By-value operands/result, no retained scratch. |
| failure | Invalid operand/product raises annotation_overflow. |
| cost | Fixed checks and at most one integer division/product; no successful allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0021

[Lines 160–164](../../../../../src/annotations/policy.cpp#L160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Multiplicity MultiplicityPolicy::remove(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retract a nonnegative share from a count total. |
| inputs / outputs | Validated total and old yield total-old. |
| invariants | old &lt;= total; caller separately establishes ownership/provenance of that old share. |
| ownership | Inline inputs/result; no source-row map is consulted. |
| failure | Operand domain overflow or annotation_underflow rejects before subtraction. |
| cost | Fixed checks/subtraction, no successful allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0022

[Lines 165–167](../../../../../src/annotations/policy.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Multiplicity MultiplicityPolicy::replace(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a count share using exact retract-then-add arithmetic. |
| inputs / outputs | Returns total-old+next by remove followed by add. |
| invariants | Old share cannot exceed total and all operands/final total fit the same policy maximum; no signed delta is formed. |
| ownership | Only inline temporaries, no independent transaction or aggregate-count mirror. |
| failure | Overflow/underflow propagates from the two public checked primitives, without changing caller state. |
| cost | Fixed checked remove/add calls; some operand validation repeats by composition, no successful allocation. |
| Design | [docs/annotations.md](../../../../annotations.md), [docs/weighted_messages.md](../../../../weighted_messages.md) |

## B0024

[Lines 169–171](../../../../../src/annotations/policy.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IntegerPayload IntegerPolicy::add(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact signed addition and check the final int64 range. |
| inputs / outputs | Two IntegerPayload values become wide signed digits, add exactly, then convert. |
| invariants | No overflowing signed native add is evaluated. |
| ownership | Bounded stack operands/result scratch and inline public result. |
| failure | Final range overflow throws annotation_overflow; inputs are unchanged. |
| cost | Bounded digit expansion/addition/conversion, no successful heap allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0025

[Lines 172–174](../../../../../src/annotations/policy.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IntegerPayload IntegerPolicy::multiply(IntegerPayload a, IntegerPayload b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact signed-by-signed product with final int64 admission. |
| inputs / outputs | Two int64 payloads yield their product or overflow. |
| invariants | INT64_MIN magnitude/sign handling stays in unsigned/digit arithmetic, including multiplication by -1. |
| ownership | Only inline/stack scratch and result. |
| failure | Out-of-range final product throws annotation_overflow. |
| cost | Bounded schoolbook digit product and checked conversion; no successful allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0026

[Lines 175–177](../../../../../src/annotations/policy.cpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IntegerPayload IntegerPolicy::multiply(IntegerPayload a, Multiplicity b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scale a signed payload by a full unsigned logical weight. |
| inputs / outputs | IntegerPayload times uint64 Multiplicity returns a checked signed result. |
| invariants | The unsigned weight is never narrowed to int64. No independent MultiplicityPolicy limit is accepted here. |
| ownership | By-value inputs and bounded stack digits. |
| failure | Final int64 overflow throws; a zero payload may correctly multiply a large valid uint64 count to zero. |
| cost | At most 19-by-20 decimal digit products plus conversion, no successful allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0027

[Lines 178–180](../../../../../src/annotations/policy.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IntegerPayload IntegerPolicy::remove(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Subtract a signed old payload using wider exact scratch. |
| inputs / outputs | Returns total-old after negating old's private coefficient. |
| invariants | Payload subtraction is independent of nonnegative support/provenance; int64 minimum is not directly negated. |
| ownership | Inline operands and stack scratch. |
| failure | Final int64 range error raises annotation_overflow. |
| cost | Bounded expansion, sign change, add and conversion; no successful allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0028

[Lines 181–183](../../../../../src/annotations/policy.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IntegerPayload IntegerPolicy::replace(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check only the final exact signed total-old+next. |
| inputs / outputs | Three int64 inputs are combined in wider scratch before one final conversion. |
| invariants | A valid cancellation/no-op remains valid even if the intermediate subtraction is outside int64. |
| ownership | Inputs are immutable values; all intermediates stay on the stack. |
| failure | Only a nonrepresentable final int64 result raises overflow; no partially published value. |
| cost | Three bounded expansions, two signed additions and one final conversion, no successful allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0030

[Lines 185–187](../../../../../src/annotations/policy.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DecimalPolicy::DecimalPolicy(DecimalSpec spec)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a fixed exact decimal arithmetic policy. |
| inputs / outputs | Stores valid precision/scale metadata. |
| invariants | Requires 1 &lt;= p &lt;= 38 and s &lt;= p before any operation uses p-s. |
| ownership | Owns only the inline specification. |
| failure | Invalid specification throws invalid_annotation. |
| cost | Fixed scalar validation/store; no successful allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0031

[Lines 188–192](../../../../../src/annotations/policy.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void DecimalPolicy::validate(const DecimalPayload& value) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify that a canonical Decimal operand fits this fixed domain. |
| inputs / outputs | Borrowed DecimalParts supply canonical scale and significant integer-digit count. |
| invariants | Canonical zero needs zero integer digits, including DECIMAL(p,p). Decimal itself already enforces &lt;= 38 coefficient digits. |
| ownership | Reads existing coefficient bytes through a temporary borrowed parts view. |
| failure | Excess fractional/integer width raises annotation_overflow; no rounding or operand rewrite. |
| cost | Fixed canonical metadata checks and zero-coefficient comparison; no new owning text. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0032

[Lines 193–197](../../../../../src/annotations/policy.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DecimalPayload DecimalPolicy::add(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add fixed-domain decimals at their exact common scale. |
| inputs / outputs | Valid operands are aligned to max(scale_a,scale_b), added, then normalized/admitted. |
| invariants | Alignment introduces only exact low zeros; no precision is silently discarded. |
| ownership | Operands are borrowed; scratch is bounded stack and returned Decimal owns its text. |
| failure | Operand/final-domain overflow and result-string allocation propagate without modifying operands. |
| cost | Bounded alignment/addition plus final normalization/render/parse and possible ordinary allocation. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0033

[Lines 198–203](../../../../../src/annotations/policy.cpp#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DecimalPayload DecimalPolicy::multiply(const DecimalPayload& a, const DecimalPayload& b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Multiply exact fixed-domain decimal payloads. |
| inputs / outputs | Original coefficient product uses scale_a+scale_b before removing insignificant fractional zeros. |
| invariants | Operand scales are valid and &lt;= 38; at most 76 coefficient digits/scale are needed in scratch. Final result must fit the original spec. |
| ownership | Borrowed inputs, bounded stack product, owning final Decimal. |
| failure | No rounding fallback; nonconforming result throws annotation_overflow and allocation failures propagate. |
| cost | Bounded O(d_a*d_b) digit product plus final zero normalization/text construction. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0034

[Lines 204–208](../../../../../src/annotations/policy.cpp#L204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DecimalPayload DecimalPolicy::multiply(const DecimalPayload& a, Multiplicity b)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scale an exact decimal payload by a full uint64 count. |
| inputs / outputs | Validated payload coefficient times unsigned count preserves its arithmetic scale before normalization. |
| invariants | Count is not narrowed to signed; any count-policy ceiling is a separate caller obligation. |
| ownership | Borrowed Decimal and by-value count; stack scratch; result owns ordinary decimal text. |
| failure | Payload/final-domain overflow and final allocation failures propagate. |
| cost | At most 38-by-20 digit products plus normalization/render/parse; no retained runtime state. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0035

[Lines 209–211](../../../../../src/annotations/policy.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DecimalPayload DecimalPolicy::remove(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retract one exact decimal payload through checked replacement with zero. |
| inputs / outputs | Returns replace(total,old,zero). |
| invariants | Signed numeric retraction is separate from source/group support validation. |
| ownership | Inputs are borrowed; result owns the returned Decimal. |
| failure | Replacement domain/allocation failures propagate before return. |
| cost | Replacement's bounded scratch and final text costs; constructing the zero Decimal follows ordinary scalar semantics. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0036

[Lines 212–217](../../../../../src/annotations/policy.cpp#L212); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DecimalPayload DecimalPolicy::replace(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute total-old+next with one final fixed-decimal admission. |
| inputs / outputs | Three validated operands align to their maximum scale and combine in wider signed scratch. |
| invariants | Final-range checking allows valid cancellations across an out-of-domain intermediate; no rounding or binary floating point. |
| ownership | Borrowed input text, bounded stack digits, one returned owning Decimal. |
| failure | Invalid operands/final result and result allocation failures propagate; no mutable aggregate state is changed. |
| cost | Three alignments/two additions within &lt;= 77 digits, bounded normalization and final text allocation/copy. |
| Design | [docs/annotations.md](../../../../annotations.md) |

## B0038

[Lines 219–251](../../../../../src/annotations/policy.cpp#L219); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Admission admit(const Request& request, Backend backend) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve supported built-in algebra and backend capabilities without allocating diagnostics. |
| inputs / outputs | Request/domain/deletion/spec and backend produce an Admission value with static policy-name view. |
| invariants | Rejects unsupported/unknown domains first, then decimal misuse, deletion misuse and unsupported backend pairs. Status is authoritative even if earlier capability fields were filled. |
| ownership | Borrows request during the call; result stores only scalar metadata and static string literals. |
| failure | Noexcept status return: no exception translation or fallback backend. Caller-provided traits cannot register support. |
| cost | Bounded enum branches and fixed spec checks; no container, account, text or payload allocation. |
| Design | [docs/annotations.md](../../../../annotations.md), [docs/semantics.md](../../../../semantics.md), [docs/weighted_messages.md](../../../../weighted_messages.md) |

## B0039

[Lines 252–256](../../../../../src/annotations/policy.cpp#L252); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require_set_backend_policy(std::string_view policy)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the closed Boolean annotation policy to real set-plan admission. |
| inputs / outputs | Requested policy name must equal the registry's admitted certified-set-tree policy. |
| invariants | Weighted/payload kernel names cannot silently select the existing set runtime or change its identity semantics. |
| ownership | Borrows supplied name; registry result borrows a static name. |
| failure | Mismatch or nonadmission throws invalid_policy; no catch switches to a different policy. |
| cost | Fixed registry checks plus actual short string comparison; allocation only for rejection presentation. |
| Design | [docs/annotations.md](../../../../annotations.md), [docs/query_identity.md](../../../../query_identity.md), [docs/weighted_messages.md](../../../../weighted_messages.md) |

## B0040

[Lines 257–257](../../../../../src/annotations/policy.cpp#L257); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L257-L257:sha256:f81132fa3e8b8fabe1be8bc8d2c0934f98c3528a31900ca2ae86fa522a677737
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::annotations at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/annotations/policy.cpp](../../../../../src/annotations/policy.cpp), [docs/code_specs/files/src/annotations/policy.cpp.md](policy.cpp.md), [docs/annotations.md](../../../../annotations.md), [docs/invariant_memory.md](../../../../invariant_memory.md) |
