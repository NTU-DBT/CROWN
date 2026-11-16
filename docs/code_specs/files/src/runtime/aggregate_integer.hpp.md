# `src/runtime/aggregate_integer.hpp` — block usage map

[Source](../../../../../src/runtime/aggregate_integer.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Provide fixed-width exact integer products, signed accumulators and decimal rounding for aggregate arithmetic.

Snapshot SHA-256: `d2c0686fb56e19bc5c8af81669daed227a7db562fff6c4ea1d66901b92c2afda`. 154 lines partitioned into 24 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../src/runtime/aggregate_integer.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Private W04 arithmetic. Admitted groups have at most INT64_MAX rows of · [reviewed contract](#b0001) |
| [B0002 · 16–20](../../../../../src/runtime/aggregate_integer.hpp#L16) | Type/record definition: struct Magnitude | returns high == 0 && low == 0 · [reviewed contract](#b0002) |
| [B0003 · 21–23](../../../../../src/runtime/aggregate_integer.hpp#L21) | Explanatory comments or spacing. | source comment (unverified): // Four 32-bit partial products form the exact 64-by-64 product without a · [reviewed contract](#b0003) |
| [B0004 · 24–32](../../../../../src/runtime/aggregate_integer.hpp#L24) | Callable definition: \[\[nodiscard\]\] inline Magnitude multiply(std::uint64_t left, std::uint64_t right) noexcept | calls ; returns {b * d + (second &gt;&gt; 32) + (third &gt;&gt; 32), (third &lt;&lt; 32) \| (first & mask)}; source comment (unverified): // Four 32-bit partial products form the exact 64-by-64 product without a · [reviewed contract](#b0004) |
| [B0005 · 33–35](../../../../../src/runtime/aggregate_integer.hpp#L33) | Explanatory comments or spacing. | source comment (unverified): // Callers have already admitted the group row bound; signed-sum intermediates · [reviewed contract](#b0005) |
| [B0006 · 36–39](../../../../../src/runtime/aggregate_integer.hpp#L36) | Callable definition: \[\[nodiscard\]\] inline Magnitude add(Magnitude left, Magnitude right) noexcept | calls ; returns {left.high + right.high + static_cast&lt;std::uint64_t&gt;(low &lt; left.low), low}; source comment (unverified): // Callers have already admitted the group row bound; signed-sum intermediates · [reviewed contract](#b0006) |
| [B0007 · 40–41](../../../../../src/runtime/aggregate_integer.hpp#L40) | Explanatory comments or spacing. | source comment (unverified): // Precondition left &gt;= right is established by the signed caller's comparison. · [reviewed contract](#b0007) |
| [B0008 · 42–44](../../../../../src/runtime/aggregate_integer.hpp#L42) | Callable definition: \[\[nodiscard\]\] inline Magnitude subtract(Magnitude left, Magnitude right) noexcept | calls ; returns {left.high - right.high - static_cast&lt;std::uint64_t&gt;(left.low &lt; right.low), left.low - right.low}; source comment (unverified): // Precondition left &gt;= right is established by the signed caller's comparison. · [reviewed contract](#b0008) |
| [B0009 · 45–45](../../../../../src/runtime/aggregate_integer.hpp#L45) | Explanatory comments or spacing. |  |
| [B0010 · 46–46](../../../../../src/runtime/aggregate_integer.hpp#L46) | Type/record definition: struct Quotient |  · [reviewed contract](#b0010) |
| [B0011 · 47–49](../../../../../src/runtime/aggregate_integer.hpp#L47) | Explanatory comments or spacing. | source comment (unverified): // Divisor is a positive admitted SQL count (at most INT64_MAX). The remainder · [reviewed contract](#b0011) |
| [B0012 · 50–64](../../../../../src/runtime/aggregate_integer.hpp#L50) | Callable definition: \[\[nodiscard\]\] inline Quotient divide(Magnitude numerator, std::uint64_t divisor) noexcept | calls assert; guard assert(divisor &gt; 0 && divisor &lt;= static_cast&lt;std::uint64_t&gt;(INT64_MAX));; returns out; 1 loop sites; source comment (unverified): // Divisor is a positive admitted SQL count (at most INT64_MAX). The remainder · [reviewed contract](#b0012) |
| [B0013 · 65–67](../../../../../src/runtime/aggregate_integer.hpp#L65) | Explanatory comments or spacing. | source comment (unverified): // Decimal rendering divides four base-2^32 words by ten. This fixed stack · [reviewed contract](#b0013) |
| [B0014 · 68–81](../../../../../src/runtime/aggregate_integer.hpp#L68) | Callable definition: \[\[nodiscard\]\] inline std::uint32_t decimal_digit(Magnitude& value) noexcept | calls ; returns static_cast&lt;std::uint32_t&gt;(remainder); 1 loop sites; source comment (unverified): // Decimal rendering divides four base-2^32 words by ten. This fixed stack · [reviewed contract](#b0014) |
| [B0015 · 82–84](../../../../../src/runtime/aggregate_integer.hpp#L82) | Explanatory comments or spacing. | source comment (unverified): // Coefficient has at most 38 digits and scale is 0..18. InlineDecimal owns · [reviewed contract](#b0015) |
| [B0016 · 85–107](../../../../../src/runtime/aggregate_integer.hpp#L85) | Callable definition: \[\[nodiscard\]\] inline storage::InlineDecimal decimal(Magnitude coefficient, bool negative, std::uint8_t scale) | calls zero, assert, size, decimal_digit; guard assert(count &lt; digits.size());; returns storage::InlineDecimal::parse(std::string_view(text.data(), length)); 4 loop sites; source comment (unverified): // Coefficient has at most 38 digits and scale is 0..18. InlineDecimal owns · [reviewed contract](#b0016) |
| [B0017 · 108–111](../../../../../src/runtime/aggregate_integer.hpp#L108) | declares types or opens a type body. | source comment (unverified): // One trivially copied sufficient statistic. Group existence and non-null · [reviewed contract](#b0017) |
| [B0018 · 112–124](../../../../../src/runtime/aggregate_integer.hpp#L112) | Callable definition: public: // Add or retract value*multiplicity after the caller checks row-count bounds. // INT64_MIN is converted without signed n… | calls multiply, add, subtract, zero; source comment (unverified): // Add or retract value*multiplicity after the caller checks row-count bounds. · [reviewed contract](#b0018) |
| [B0019 · 125–128](../../../../../src/runtime/aggregate_integer.hpp#L125) | Callable definition: \[\[nodiscard\]\] bool fits_int64() const noexcept | calls ; returns magnitude_.high == 0 && magnitude_.low &lt;= limit · [reviewed contract](#b0019) |
| [B0020 · 129–134](../../../../../src/runtime/aggregate_integer.hpp#L129) | Callable definition: \[\[nodiscard\]\] std::int64_t int64_value() const noexcept | calls assert, fits_int64; guard assert(fits_int64());; returns INT64_MIN; negative_ ? -value : value · [reviewed contract](#b0020) |
| [B0021 · 135–135](../../../../../src/runtime/aggregate_integer.hpp#L135) | Callable definition: \[\[nodiscard\]\] storage::InlineDecimal value() const | calls decimal; returns decimal(magnitude_, negative_, 0) · [reviewed contract](#b0021) |
| [B0022 · 136–138](../../../../../src/runtime/aggregate_integer.hpp#L136) | Explanatory comments or spacing. | source comment (unverified): // Count matches this sum's exact non-NULL multiplicity (1..INT64_MAX). · [reviewed contract](#b0022) |
| [B0023 · 139–149](../../../../../src/runtime/aggregate_integer.hpp#L139) | Callable definition: \[\[nodiscard\]\] storage::InlineDecimal average(std::uint64_t count, std::uint8_t scale) const | calls assert, divide, multiply, add; guard assert(scale &lt;= 18);; returns decimal(coefficient, negative_, scale); 1 loop sites; source comment (unverified): // Count matches this sum's exact non-NULL multiplicity (1..INT64_MAX). · [reviewed contract](#b0023) |
| [B0024 · 150–154](../../../../../src/runtime/aggregate_integer.hpp#L150) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime::aggregate::detail · [reviewed contract](#b0024) |

## B0001

[Lines 1–15](../../../../../src/runtime/aggregate_integer.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Private W04 arithmetic. Admitted groups have at most INT64_MAX rows of
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the private group-count/value domain that makes bounded sufficient statistics safe. |
| inputs / outputs | Caller supplies coherent int64 contributions with total group/non-NULL multiplicity at most INT64_MAX; this header returns only numeric state/results. |
| invariants | \|sum\| &lt;= C*2^63 &lt; 2^126 for a legal group, hence at most38 coefficient digits; add/retract temporaries bounded below2^127 fit two unsigned words. Group existence, NULL exclusion and count admission remain external. |
| ownership | All primitive state is inline; this comment supplies no group, account, transaction or SQL binding owner. |
| failure | These are caller preconditions, not repeated runtime admission checks. Violating them can wrap unsigned state or invalidate later asserted rendering/conversion bounds. |
| cost | No runtime work from the protocol comment; row-count size does not cause repeated-row expansion. This local argument is no SQL/transaction acceptance or paper update-time theorem. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0002

[Lines 16–20](../../../../../src/runtime/aggregate_integer.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Magnitude {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one unsigned128 magnitude in high/low uint64 words. |
| inputs / outputs | Defaults both words to zero; comparison and zero() support signed-magnitude arithmetic. |
| invariants | Value is high*2^64+low; declaration order makes default comparison lexicographic by high then low. Magnitude itself has no sign or overflow admission. |
| ownership | Owns two inline words, with ordinary value-copy lifetime. |
| failure | Construct/copy and unsigned comparison do not allocate or reject values; helpers impose their own bounds. |
| cost | Fixed two-word storage/copy; no heap or magnitude-dependent container. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

```text
auto operator<=>(const Magnitude&) const = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order unsigned128 magnitudes by their high word and then low word. |
| inputs / outputs | Returns defaulted strong ordering between two inline Magnitude values. |
| invariants | Unsigned word ordering agrees with high*2^64+low and supplies subtract’s left&gt;=right gate. |
| ownership | Borrows the other value for comparison; result owns no storage. |
| failure | Valid inline comparison has no checked failure or allocation. |
| cost | At most two unsigned word comparisons, with fixed stack/value state. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

```text
[[nodiscard]] bool zero() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize canonical numeric zero independently of signed state. |
| inputs / outputs | Returns high==0 && low==0. |
| invariants | No inference about group existence or non-NULL count follows from zero magnitude. |
| ownership | Inline reads and value bool result. |
| failure | Noexcept; no allocation. |
| cost | Two word tests at most. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0003

[Lines 21–23](../../../../../src/runtime/aggregate_integer.hpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Four 32-bit partial products form the exact 64-by-64 product without a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Justify exact partial-product carries without extended integer or dynamic bigint storage. |
| inputs / outputs | Let B=2^32 and split both uint64 operands into digits a,b,c,d below B. |
| invariants | b*c+floor(a*c/B) &lt;= B^2-B-1, and a*d+(second mod B) &lt;= B^2-B; both fit uint64. Final high-word sum is at most B^2-1, and shifted low bits are explicitly separated from carried bits. |
| ownership | Only inline split words/carries are needed. |
| failure | The product is exact for every uint64 pair; no group-bound restriction is needed for multiply itself. |
| cost | Four32x32 products plus fixed word additions/shifts; no heap request or input-magnitude loop. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0004

[Lines 24–32](../../../../../src/runtime/aggregate_integer.hpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline Magnitude multiply(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the full unsigned64-by64 product as an exact128 result. |
| inputs / outputs | Two uint64 values yield high and low words. |
| invariants | The two cross-term carries fit their uint64 temporaries. third&lt;&lt;32 intentionally retains its low32 bits in the low result; its high bits are included separately in high. |
| ownership | Inputs/results and temporaries are inline values. |
| failure | Noexcept for all uint64 operands; no overflow exception or heap path. |
| cost | Fixed four partial multiplications, bounded carry arithmetic and two-word output; independent of represented multiplicity. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0005

[Lines 33–35](../../../../../src/runtime/aggregate_integer.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Callers have already admitted the group row bound; signed-sum intermediates
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the bounded-intermediate precondition for unchecked magnitude addition. |
| inputs / outputs | Caller proves the mathematical addition fits128 bits; legal admitted signed-sum use stays below2^127. |
| invariants | The low-word carry cannot overflow the high result within this domain. The wider temporary bound does not by itself authorize a38-digit final SUM output. |
| ownership | No owner or arithmetic state is introduced by the comment. |
| failure | No general overflow detection/refund is added; callers must admit group/count state before using add. |
| cost | No runtime overhead beyond the following two-word helper. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0006

[Lines 36–39](../../../../../src/runtime/aggregate_integer.hpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline Magnitude add(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add two bounded unsigned magnitudes with one low-word carry. |
| inputs / outputs | Returns left+right as two words when its mathematical sum fits128 bits. |
| invariants | low&lt;left.low detects unsigned low wrap exactly; caller’s admitted signed-sum/AVG coefficient bounds prove the high addition does not wrap. |
| ownership | Copies inline operands and returns an inline result. |
| failure | Noexcept and no overflow report; out-of-domain inputs can silently wrap modulo2^128. |
| cost | Fixed word adds/comparison and constant inline state; no heap or logical allowance. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0007

[Lines 40–41](../../../../../src/runtime/aggregate_integer.hpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Precondition left >= right is established by the signed caller
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a nonnegative mathematical difference before unsigned subtraction. |
| inputs / outputs | Signed-magnitude replace compares operands before selecting subtract order. |
| invariants | left&gt;=right proves enough high-word value exists when the low-word subtraction borrows. |
| ownership | No retained state. |
| failure | This is a precondition, not an extra dynamic check in subtract. |
| cost | The preceding two-word comparison and following fixed subtraction avoid a generic exception path. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0008

[Lines 42–44](../../../../../src/runtime/aggregate_integer.hpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline Magnitude subtract(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Subtract ordered magnitudes using the low-word borrow. |
| inputs / outputs | Requires left&gt;=right and returns exact left-right. |
| invariants | left.low&lt;right.low subtracts one from the high difference; unsigned low wrap is the intended limb result. |
| ownership | Two-word value inputs/result; no alias or owner escapes. |
| failure | Noexcept with no order check; reversed input gives a modular result outside this helper’s contract. |
| cost | Fixed two-word arithmetic with no allocation. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0010

[Lines 46–46](../../../../../src/runtime/aggregate_integer.hpp#L46); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Quotient {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return full128 quotient and one bounded remainder together. |
| inputs / outputs | divide initializes value to zero and remainder to zero, then fills both. |
| invariants | Successful divide guarantees numerator=value*divisor+remainder and 0&lt;=remainder&lt;divisor. Raw default construction alone does not initialize this aggregate’s plain remainder member. |
| ownership | Inline Magnitude plus one uint64 value; no borrowed storage. |
| failure | No allocation or validation by the record itself; divisor constraints belong to divide. |
| cost | Fixed result storage/copy. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0011

[Lines 47–49](../../../../../src/runtime/aggregate_integer.hpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Divisor is a positive admitted SQL count
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove the long-division remainder shift remains exact in uint64. |
| inputs / outputs | Admitted divisor D satisfies1&lt;=D&lt;=INT64_MAX. |
| invariants | At each bit, R&lt;D, so 2R+incoming &lt;=2D-1&lt;=2^64-3; the shift loses no bit. Either subtraction restores R&lt;D or it was already below D. |
| ownership | Only a one-word remainder and inline quotient are needed. |
| failure | Zero/too-large divisor is a private contract violation; debug assertion is not public admission. |
| cost | One fixed128-bit scan, without an allocating wider intermediate. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0012

[Lines 50–64](../../../../../src/runtime/aggregate_integer.hpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline Quotient divide(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform exact binary long division of any128 numerator by an admitted positive count. |
| inputs / outputs | Magnitude numerator and divisor1..INT64_MAX yield full quotient and remainder. |
| invariants | Processes positions127..0 once. Conditional branches select shifts only in0..63 for numerator/quotient words; remainder invariant prevents uint64 shift overflow. |
| ownership | Owns only inline result/local words; numerator copied by value. |
| failure | Noexcept; debug asserts divisor range. Release callers must establish it; no general division error object is built. |
| cost | Exactly128 iterations with fixed word work and constant stack space; no heap/requested logical budget. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0013

[Lines 65–67](../../../../../src/runtime/aggregate_integer.hpp#L65); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Decimal rendering divides four base-2^32 words by ten.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Limit decimal conversion to fixed-word scratch on requested numeric output. |
| inputs / outputs | decimal_digit views one128 magnitude as four high-to-low base2^32 words. |
| invariants | Remainder before each word is below10; current=R*2^32+word&lt;10*2^32 fits uint64, and current/10 fits uint32. |
| ownership | Four-word scratch is local; the magnitude is updated in place. |
| failure | No dynamic bigint or output-state owner is introduced. |
| cost | Four divide-by-ten word operations per emitted digit, outside state replace(). |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0014

[Lines 68–81](../../../../../src/runtime/aggregate_integer.hpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline std::uint32_t decimal_digit(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract one exact decimal digit while replacing magnitude with floor(value/10). |
| inputs / outputs | Mutable128 magnitude; returns remainder0..9. |
| invariants | Words are processed high to low and recombined without sign conversion; every intermediate division fits its declared word widths. |
| ownership | Mutates only supplied inline magnitude; four uint32 scratch words are local. |
| failure | Noexcept for all128 values; no allocation or formatting exception. |
| cost | Exactly four word divisions/remainders and fixed shifts/copies. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0015

[Lines 82–84](../../../../../src/runtime/aggregate_integer.hpp#L82); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Coefficient has at most 38 digits and scale is 0..18.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State output digit/scale bounds and prevent a stack-backed view escape. |
| inputs / outputs | Coefficient&lt;10^38, sign bool and scale0..18 are required by decimal(). |
| invariants | At most38 digit extractions. Signed decimal text uses at most40 bytes with a point, or39 without, within InlineDecimal::text_capacity41. Zero suppresses a minus sign. |
| ownership | InlineDecimal::parse copies coefficient digits into its inline object before scratch dies. |
| failure | Coefficient/scale bounds are private preconditions; the digit assertion is not a release-mode bounds validator. |
| cost | Bounded38-byte digit and41-byte text arrays plus four-word conversion scratch; no accepted-path heap. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp) |

## B0016

[Lines 85–107](../../../../../src/runtime/aggregate_integer.hpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline storage::InlineDecimal decimal(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render a bounded signed coefficient and scale into an independently owned InlineDecimal. |
| inputs / outputs | Magnitude&lt;10^38, bool sign and scale0..18 produce an exact canonical decimal value. |
| invariants | Digits are collected least-significant first and emitted in reverse with leading fractional zeros/point as needed. Negative zero is suppressed. InlineDecimal canonicalizes trailing fractional zeros, so value text need not retain declared padding/scale. |
| ownership | Both scratch arrays are stack-owned; returned InlineDecimal owns its coefficient and retains no string_view into them. |
| failure | Within bounds generated spelling is valid and parse has no failure/heap path. Invalid private bounds can trip assert or overrun scratch with assertions disabled; no general public formatter admission is provided. |
| cost | At most38 four-word digit passes plus at most40 emitted bytes and a bounded parse scan; fixed stack storage, no allocating formatter. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp) |

## B0017

[Lines 108–111](../../../../../src/runtime/aggregate_integer.hpp#L108); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class IntegerSum {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Maintain an exact bounded signed sum separately from count and group existence. |
| inputs / outputs | Inline zero state; replace adds/retracts compressed int64 contributions; accessors expose range and decimal/average results. |
| invariants | Caller supplies legal contribution history and admits row/non-NULL count bounds. Final legal \|S\|&lt;2^126; negative_ is false whenever magnitude is zero. AVG count must match the represented non-NULL multiplicity. Zero sum does not mean no group. |
| ownership | Two-word magnitude plus sign are value-owned/trivially copied; no account, heap, row identity or count is retained. |
| failure | Private unchecked word operations rely on those bounds. Rendering/conversion assertions do not implement input/SQL/group/publication admission. |
| cost | Fixed per-replacement word arithmetic, independent of multiplicity. Requested decimal/AVG output uses bounded additional stack/conversion work; group/key/transaction costs are outside this type. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0018

[Lines 112–124](../../../../../src/runtime/aggregate_integer.hpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void replace(std::int64_t value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add or retract value times multiplicity without expanding repeated rows. |
| inputs / outputs | Int64 value, uint64 multiplicity and erase flag mutate only signed sufficient statistic. |
| invariants | Caller admits coherent count/old-weight bounds and valid retract history; state/intermediate sums stay within stated bounds. MIN uses -(value+1) then unsigned+1, avoiding signed MIN negation. Equal signs add; unequal signs subtract ordered magnitudes and choose the larger sign; exact cancellation canonicalizes sign. |
| ownership | Inline state and product temporaries; count/group membership remains external. |
| failure | Noexcept and no dynamic bound checks here; illegal caller arithmetic history can produce modular state. Zero value or multiplicity returns without mutation. |
| cost | One bounded64x64 product, one sign/word comparison and one add/subtract at most; fixed stack/no heap, no multiplicity-length loop. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0019

[Lines 125–128](../../../../../src/runtime/aggregate_integer.hpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool fits_int64() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test exact signed64 output representability without narrowing. |
| inputs / outputs | Requires high==0 and low&lt;=MAX for nonnegative or&lt;=2^63 for negative state. |
| invariants | Negative MIN is included; positive2^63 is excluded. This is output range checking, not group/count validation. |
| ownership | Only inline reads and bool return. |
| failure | Noexcept; no allocation. |
| cost | Fixed sign selection and two word/range tests. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0020

[Lines 129–134](../../../../../src/runtime/aggregate_integer.hpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::int64_t int64_value() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract a checked signed64 sum including INT64_MIN safely. |
| inputs / outputs | Caller must establish fits_int64(); debug assertion repeats that precondition. |
| invariants | Negative magnitude2^63 returns MIN directly. All other narrowed magnitudes are&lt;=MAX, so the cast and optional signed negation stay representable. |
| ownership | Returns scalar value with no borrowed owner. |
| failure | Noexcept; out-of-range use is a private contract violation, not a checked publication error in this method. |
| cost | Fixed range/sign/word work; no heap or decimal conversion. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0021

[Lines 135–135](../../../../../src/runtime/aggregate_integer.hpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] storage::InlineDecimal value() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a legal bounded signed SUM as exact canonical decimal. |
| inputs / outputs | Returns decimal(magnitude_,negative_,0). |
| invariants | Final represented legal group sum has at most38 digits; the weaker temporary bound below2^127 alone is not a decimal-output admission rule. No NULL/empty-group decision is made. |
| ownership | Returned InlineDecimal owns inline coefficient independent of IntegerSum. |
| failure | Valid bounded state has no formatting failure/heap request; invalid state can violate decimal’s private bounds. |
| cost | Bounded decimal output work only when requested, with38-digit/41-byte stack scratch and inline result. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp) |

## B0022

[Lines 136–138](../../../../../src/runtime/aggregate_integer.hpp#L136); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// output type; ties round away from zero without floating-point conversion.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Tie AVG’s scale/rounding proof to the sum’s matching non-NULL count. |
| inputs / outputs | Count is the exact positive represented non-NULL multiplicity, at mostINT64_MAX; scale0..18 follows bound output type. |
| invariants | \|S\|/count&lt;=2^63 proves whole quotient high==0. Scaling quotient and remainder separately keeps products below2^63*10^18&lt;2^123; final rounded coefficient fits37 digits. A merely positive unrelated count is insufficient. |
| ownership | Count is supplied separately and never inferred from sum/group existence. |
| failure | Caller establishes count consistency; current assertions check positivity/range/scale and quotient high, not that semantic relation. |
| cost | No full-sum-by10^s wide product, floating point or dynamic bigint is needed. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |

## B0023

[Lines 139–149](../../../../../src/runtime/aggregate_integer.hpp#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] storage::InlineDecimal average(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact fixed-scale AVG with half ties rounded away from zero. |
| inputs / outputs | Matching count1..INT64_MAX and scale0..18 yield an InlineDecimal rounded at that scale. |
| invariants | Divides \|S\|=q*C+r, then divides r*10^s by C; coefficient=q*10^s+floor(r*10^s/C). remainder&gt;=C-remainder tests twice-remainder&gt;=C without overflow; increment magnitude before restoring sign. Rounded zero stays unsigned. Declared scale is separate from canonical trailing-zero trimming. |
| ownership | Sum remains unchanged; only fixed inline words/stack output and independently owned InlineDecimal are used. |
| failure | Debug asserts scale, positive count range and zero quotient high. Caller must also establish count/sum coherence; no input/group/SQL error wrapper is introduced. |
| cost | At most18 factor multiplies, two128-step divisions, two64x64 products, bounded word adds and38-digit conversion. Constant bounded stack/no valid-path heap; no group-size loop. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp) |

## B0024

[Lines 150–154](../../../../../src/runtime/aggregate_integer.hpp#L150); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Magnitude magnitude_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep signed zero canonical without storing count or group lifetime. |
| inputs / outputs | Private magnitude and negative_=false; implicit default/copy/move/destruction use member value semantics. |
| invariants | replace normalizes sign when magnitude becomes zero. Independent row/non-NULL counts must survive cancellation outside this state. |
| ownership | Inline values only; copied states share no dynamic owner and need no cleanup graph. |
| failure | No allocation or destruction failure; numerical preconditions remain with callers. |
| cost | Fixed object state/copy/teardown, distinct from requested output conversion work. |
| Design | [docs/aggregates.md §Bounded integer sufficient statistics](../../../../aggregates.md) |
