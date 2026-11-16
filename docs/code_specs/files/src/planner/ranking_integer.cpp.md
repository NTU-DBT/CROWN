# `src/planner/ranking_integer.cpp` — block usage map

[Source](../../../../../src/planner/ranking_integer.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Perform bounded exact integer score arithmetic without floating-point ordering changes.

Snapshot SHA-256: `2de329924c6e08b453b8b925bfb54e0929bc56a153006d190357aafd657afa64`. 51 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../src/planner/ranking_integer.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–9](../../../../../src/planner/ranking_integer.cpp#L6) | Callable definition: unsigned UInt::bits() const noexcept | calls size, std::bit_width; returns static_cast&lt;unsigned&gt;((i-1)*32)+static_cast&lt;unsigned&gt;(std::bit_width(limbs_\[i-1\])); 0; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 10–10](../../../../../src/planner/ranking_integer.cpp#L10) | Callable definition: bool UInt::zero() const noexcept | calls bits; returns bits()==0 · [reviewed contract](#b0003) |
| [B0004 · 11–11](../../../../../src/planner/ranking_integer.cpp#L11) | Callable definition: void UInt::check(const Budget& b) const | calls bits; guard void UInt::check(const Budget& b) const {if(bits()&gt;b.limits.score_bits)throw Failure{Stop::bit_limi… · [reviewed contract](#b0004) |
| [B0005 · 12–14](../../../../../src/planner/ranking_integer.cpp#L12) | Callable definition: UInt UInt::from(std::uint64_t value,Budget& b) | calls work, check; guard b.work(18);UInt out;out.limbs_\[0\]=static_cast&lt;std::uint32_t&gt;(value);out.limbs_\[1\]=static_cast&lt;std::…; returns out · [reviewed contract](#b0005) |
| [B0006 · 15–20](../../../../../src/planner/ranking_integer.cpp#L15) | Callable definition: UInt UInt::add(const UInt& x,const UInt& y,Budget& b) | calls work, check; guard out.check(b);return out;; returns out; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 21–22](../../../../../src/planner/ranking_integer.cpp#L21) | Explanatory comments or spacing. | source comment (unverified): // Fixed 16x16 limb work with 32 inline scratch limbs; reject high limbs or · [reviewed contract](#b0007) |
| [B0008 · 23–31](../../../../../src/planner/ranking_integer.cpp#L23) | Callable definition: UInt UInt::multiply(const UInt& x,const UInt& y,Budget& b) | calls work, std::copy_n, begin, check; guard UInt out;std::copy_n(scratch.begin(),16,out.limbs_.begin());out.check(b);return out;; returns out; 3 loop sites; source comment (unverified): // Fixed 16x16 limb work with 32 inline scratch limbs; reject high limbs or · [reviewed contract](#b0008) |
| [B0009 · 32–34](../../../../../src/planner/ranking_integer.cpp#L32) | Callable definition: int UInt::compare(const UInt& x,const UInt& y,Budget& b) | calls work; returns -1; 1; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 35–36](../../../../../src/planner/ranking_integer.cpp#L35) | Explanatory comments or spacing. | source comment (unverified): // At most 155 decimal digits for 512 bits. Render into bounded stack scratch · [reviewed contract](#b0010) |
| [B0011 · 37–44](../../../../../src/planner/ranking_integer.cpp#L37) | Callable definition: UInt::Digits UInt::digits(Budget& b) const | calls work, std::any_of, begin, end; returns v!=0; output; 3 loop sites; source comment (unverified): // At most 155 decimal digits for 512 bits. Render into bounded stack scratch · [reviewed contract](#b0011) |
| [B0012 · 45–47](../../../../../src/planner/ranking_integer.cpp#L45) | Callable definition: std::string UInt::decimal(Budget& b) const | calls digits, std::string, rend; returns std::string(value.bytes.rend()-static_cast&lt;std::ptrdiff_t&gt;(value.count),value.bytes.rend()) · [reviewed contract](#b0012) |
| [B0013 · 48–50](../../../../../src/planner/ranking_integer.cpp#L48) | Callable definition: ScoreText UInt::decimal(Budget& b,const resource::MemoryAccount& account) const | calls digits, ScoreText, rend; returns ScoreText(value.bytes.rend()-static_cast&lt;std::ptrdiff_t&gt;(value.count),value.bytes.rend(),score_allo… · [reviewed contract](#b0013) |
| [B0014 · 51–51](../../../../../src/planner/ranking_integer.cpp#L51) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::ranking::detail · [reviewed contract](#b0014) |

## B0001

[Lines 1–5](../../../../../src/planner/ranking_integer.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:aadf3641e004549451b7a660b605a95a16312175a5825817e76141612767b026
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | make #include "ranking_detail.hpp", #include &lt;algorithm&gt;, #include &lt;bit&gt; available to src/planner/ranking_integer.cpp; open crown::planner::ranking::detail. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0002

[Lines 6–9](../../../../../src/planner/ranking_integer.cpp#L6); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
unsigned UInt::bits()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the significant score width. |
| inputs / outputs | Scans limbs from highest and returns bit_width(highest)+offset, or zero. |
| invariants | Does not mutate or truncate limbs. |
| ownership | Reads only this value's sixteen inline limbs and returns an unsigned scalar; no Budget is supplied or retained. |
| failure | Noexcept; no counter/time check, Failure throw, heap allocation or text construction. |
| cost | At most16limbs, no allocation or budget debit. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 10–10](../../../../../src/planner/ranking_integer.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool UInt::zero()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test exact numeric zero. |
| inputs / outputs | Returns bits()==0. |
| invariants | Zero test includes every limb. |
| ownership | Reads only this value's inline limbs through bits() and returns bool; no Budget is supplied or retained. |
| failure | Noexcept; no counter/time check, Failure throw, heap allocation or text construction. |
| cost | At most16limbs, no explicit budget debit. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 11–11](../../../../../src/planner/ranking_integer.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void UInt::check(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce the caller admitted score width. |
| inputs / outputs | Throws when actual bits exceed score_bits. |
| invariants | Budget constructor already established1..512 limit. |
| ownership | Borrows this UInt and const Budget only to read score_bits; returns no value or retained owner. |
| failure | Throws Failure{bit_limit} only when significant width exceeds score_bits. Performs no work/time/payload debit or text allocation. |
| cost | At most16limbs, no allocation on success. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 12–14](../../../../../src/planner/ranking_integer.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UInt UInt::from(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a full uint64 score operand. |
| inputs / outputs | Debits18work, sets low2limbs and checks configured width. |
| invariants | No narrowing/truncation beyond known low/high32 split. |
| ownership | Mutates the borrowed Budget and returns a new inline UInt; no operand storage or heap owner escapes. |
| failure | Budget work/clock Failure or requested-width bit_limit propagates; no text or dynamic integer allocation occurs. |
| cost | Fixed16-limb initialization and width scan. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 15–20](../../../../../src/planner/ranking_integer.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UInt UInt::add(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add two exact nonnegative scores. |
| inputs / outputs | Debits33work, adds16limbs with carry then enforces configured width. |
| invariants | Any final carry or excess requested width is bit_limit rather than wrap. |
| ownership | Borrows immutable operands, mutates Budget and returns a new inline UInt; source limbs remain unchanged. |
| failure | Budget work/clock Failure or final carry/requested-width bit_limit propagates; no text or dynamic integer allocation occurs. |
| cost | Fixed16-limb sum plus width scan. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 21–22](../../../../../src/planner/ranking_integer.cpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L22:sha256:8d544f0215c063f1e16127795f29b2eeb488fca34422aecc95e1d392e25d10bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for UInt: Fixed 16x16 limb work with 32 inline scratch limbs; reject high limbs or the requested bit ceiling instead of truncating the exact product. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies UInt; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for UInt come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0008

[Lines 23–31](../../../../../src/planner/ranking_integer.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UInt UInt::multiply(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Multiply exact scores using bounded schoolbook arithmetic. |
| inputs / outputs | Debits304work, uses32scratch limbs, rejects nonzero upper16 and requested-width overflow. |
| invariants | Each uint64 term is one32x32product+32-bit accumulated limb+carry; fixed bounds fit uint64. |
| ownership | Borrows immutable operands, mutates Budget and returns a new inline UInt; all thirty-two product scratch limbs are local inline storage. |
| failure | Budget work/clock Failure or high-limb/requested-width bit_limit propagates; no text or dynamic integer allocation occurs. |
| cost | 256limb products plus fixed carry/high-limb/width scans; inline scratch only. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 32–34](../../../../../src/planner/ranking_integer.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int UInt::compare(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order two exact bounded integers. |
| inputs / outputs | Debits16work, compares high limbs downward, returns -1/0/1. |
| invariants | Numeric comparison precedes stable key tie-break. |
| ownership | Borrows immutable UInt operands and mutable Budget, returning only int; no ownership transfer or allocation. |
| failure | Budget work/clock Failure can propagate. compare does not recheck score_bits or allocate text. |
| cost | At most16limb comparisons. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 35–36](../../../../../src/planner/ranking_integer.cpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L36:sha256:dac1cec05526e312df7f72eeec6af812fac767b4e8ee6140d9a77acf80fa2960
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for UInt: At most 155 decimal digits for 512 bits. Render into bounded stack scratch first; a later budget/output-allocation failure cannot alter the source UInt. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies UInt; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for UInt come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

## B0011

[Lines 37–44](../../../../../src/planner/ranking_integer.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UInt::Digits UInt::digits(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render exact reverse decimal digits in bounded scratch. |
| inputs / outputs | Copies limbs, repeatedly divides by10, then debits emitted bytes/work. |
| invariants | Zero emits one digit; at most155digits. A later budget rejection leaves prior work spent but original UInt unchanged. |
| ownership | Borrows source limbs, mutates Budget, copies limbs into fixed scratch and returns inline reverse Digits; no heap text is created. |
| failure | Budget work/clock/payload-byte Failure can follow accepted prior debits. digits does not recheck score_bits or allocate output text. |
| cost | At most155passes of16limbs, fixed scratch and logical debits; no output allocation here. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 45–47](../../../../../src/planner/ranking_integer.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string UInt::decimal(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the exact integer to ordinary decimal text. |
| inputs / outputs | Reverses bounded rendered digits into std::string. |
| invariants | No leading sign, floating approximation or rounding. |
| ownership | Borrows the UInt and mutable Budget; returned std::string owns copied decimal characters independently. |
| failure | digits budget work/clock/payload failures propagate; final ordinary string allocation may throw. This overload performs no new bit-width check. |
| cost | Bounded render plus O(digits) ordinary string allocation/copy. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 48–50](../../../../../src/planner/ranking_integer.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScoreText UInt::decimal(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the exact integer to receiving-account decimal text. |
| inputs / outputs | Reverses digits into ScoreText with score_allocator(account). |
| invariants | Same exact textual value; ownership path differs from ordinary overload. |
| ownership | Borrows UInt/Budget and supplied receiving account; returned ScoreText owns copied characters with score_allocator account/purpose/attribution. |
| failure | digits budget work/clock/payload failures and account/allocator/allocation failures propagate. No new bit-width check or partial published text. |
| cost | Bounded render plus O(digits) account-aware allocation/copy. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 51–51](../../../../../src/planner/ranking_integer.cpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L51:sha256:8bf65c99ea9806935a6f88212f8f7cd998531829b15fe2d7e82f4bf3d015cd76
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::ranking::detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking.md](../../../../ranking.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |
