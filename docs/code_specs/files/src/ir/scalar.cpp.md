# `src/ir/scalar.cpp` — block usage map

[Source](../../../../../src/ir/scalar.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Parse, compare, hash and format exact scalar DTO values.

Snapshot SHA-256: `b68511f78d37fa4a2dd2d795d1f6ea543a8920064ec9b16ea3c36544074de273`. 119 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [values](../../../subsystem_contracts.md#values). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/scalars.md](../../../../scalars.md), [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/verification/s05-public-tuples-2026-11-09.md](../../../../verification/s05-public-tuples-2026-11-09.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/ir/scalar.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 11–11](../../../../../src/ir/scalar.cpp#L11) | Callable definition: bool digit(char value) | calls ; returns value &gt;= @ && value &lt;= @ · [reviewed contract](#b0002) |
| [B0003 · 12–14](../../../../../src/ir/scalar.cpp#L12) | Callable definition: \[\[noreturn\]\] void invalid_date() | calls Error · [reviewed contract](#b0003) |
| [B0004 · 15–16](../../../../../src/ir/scalar.cpp#L15) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 17–29](../../../../../src/ir/scalar.cpp#L17) | Callable definition: Date Date::parse(std::string_view text) | calls size, invalid_date, digit, ok; returns Date{static_cast&lt;std::int32_t&gt;(days)}; 1 loop sites; source comment (unverified): // The declared date range fits int32. · [reviewed contract](#b0005) |
| [B0006 · 30–30](../../../../../src/ir/scalar.cpp#L30) | Explanatory comments or spacing. |  |
| [B0007 · 31–46](../../../../../src/ir/scalar.cpp#L31) | Callable definition: std::string Date::to_string() const | calls year, month, day; returns result · [reviewed contract](#b0007) |
| [B0008 · 47–47](../../../../../src/ir/scalar.cpp#L47) | Explanatory comments or spacing. |  |
| [B0009 · 48–86](../../../../../src/ir/scalar.cpp#L48) | Callable definition: Decimal Decimal::parse(std::string_view text) | calls empty, Error, find, size; returns Decimal{}; result; growth push_back, reserve; 3 loop sites; source comment (unverified): // Strip insignificant zeros before the precision/scale checks. Exact aliases · [reviewed contract](#b0009) |
| [B0010 · 87–87](../../../../../src/ir/scalar.cpp#L87) | Explanatory comments or spacing. |  |
| [B0011 · 88–96](../../../../../src/ir/scalar.cpp#L88) | Callable definition: std::string Decimal::to_string() const | calls size, substr, std::string; returns result + digits_; result + digits_.substr(0, point) + @ + digits_.substr(point) · [reviewed contract](#b0011) |
| [B0012 · 97–97](../../../../../src/ir/scalar.cpp#L97) | Explanatory comments or spacing. |  |
| [B0013 · 98–118](../../../../../src/ir/scalar.cpp#L98) | Callable definition: std::strong_ordering Decimal::operator&lt;=&gt;(const Decimal& other) const | calls std::max; returns std::strong_ordering::equal; other.negative_ ? std::strong_ordering::greater : std::strong_ordering…; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 119–119](../../../../../src/ir/scalar.cpp#L119) | Closes surrounding scope/type. | source comment (unverified): // namespace crown · [reviewed contract](#b0014) |

## B0001

[Lines 1–10](../../../../../src/ir/scalar.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:84f1f444cf907d34b1de3092b8c43b9bdc08f7fc0e9d3b4fdb812b45e717c57f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/ir/scalar.hpp, crown/api/error.hpp, algorithm, chrono, cstddef, utility) and opens crown scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [docs/code_specs/files/src/ir/scalar.cpp.md](scalar.cpp.md), [docs/scalars.md](../../../../scalars.md), [docs/semantics.md](../../../../semantics.md) |

## B0002

[Lines 11–11](../../../../../src/ir/scalar.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool digit(char value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize only ASCII decimal digits. |
| inputs / outputs | One character returns true for 0..9. |
| invariants | No locale, sign or Unicode digit interpretation. |
| ownership | One scalar input, no retained state. |
| failure | Body uses nonthrowing scalar comparisons and no allocation. |
| cost | O(1). |
| Design | [docs/scalars.md](../../../../scalars.md), [docs/semantics.md](../../../../semantics.md) |

## B0003

[Lines 12–14](../../../../../src/ir/scalar.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void invalid_date()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present the public date-grammar/calendar diagnostic. |
| inputs / outputs | No return value; raises invalid_scalar with the finite Gregorian input contract. |
| invariants | All rejected date lexical/calendar cases use this same presentation. |
| ownership | The public Error owns its diagnostic; not a retained query value. |
| failure | Error construction can itself fail allocating; no state has been published. |
| cost | Failure-only exception/string costs; no success-path helper allocation. |
| Design | [docs/scalars.md](../../../../scalars.md), [docs/semantics.md](../../../../semantics.md) |

## B0004

[Lines 15–16](../../../../../src/ir/scalar.cpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L16:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [docs/code_specs/files/src/ir/scalar.cpp.md](scalar.cpp.md), [docs/scalars.md](../../../../scalars.md), [docs/semantics.md](../../../../semantics.md) |

## B0005

[Lines 17–29](../../../../../src/ir/scalar.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Date Date::parse(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse one finite canonical-format Gregorian day. |
| inputs / outputs | Exactly ten YYYY-MM-DD ASCII bytes produce int32 epoch days in 0001..9999. |
| invariants | Validate separators/digits, reject year zero, then use year_month_day::ok including leap-day rules; declared date range fits int32. |
| ownership | Borrows text during the call and returns an independent inline Date. |
| failure | Malformed or impossible date raises invalid_scalar before a result escapes. |
| cost | Fixed ten-byte/calendar work, no success-path allocation. |
| Design | [docs/scalars.md](../../../../scalars.md), [docs/semantics.md](../../../../semantics.md) |

## B0007

[Lines 31–46](../../../../../src/ir/scalar.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string Date::to_string() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render the admitted day as canonical YYYY-MM-DD. |
| inputs / outputs | An invariant-valid Date returns one owning ten-character standard string. |
| invariants | Only parse/default construction create Date values; no timezone/locale conversion or infinity sentinel. |
| ownership | Result owns ordinary string storage; Date remains unchanged. |
| failure | Standard string allocation failure propagates without changing Date. |
| cost | Fixed date conversion and ten writes; do not rely on an implementation-specific small-string allocation exemption. |
| Design | [docs/scalars.md](../../../../scalars.md), [docs/semantics.md](../../../../semantics.md) |

## B0009

[Lines 48–86](../../../../../src/ir/scalar.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Decimal Decimal::parse(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize a finite exact base-ten scalar without rounding. |
| inputs / outputs | Optional sign, integer digits and optional nonempty fractional digits yield canonical coefficient/sign/scale. |
| invariants | Only one point; strip leading coefficient zeros and trailing fractional zeros before bounds. Nonzero coefficient &lt;=38 digits, scale&lt;=38; every signed zero becomes positive zero/scale0. |
| ownership | Borrows input synchronously; returned coefficient owns at most38 standard-string digits. |
| failure | Malformed grammar raises invalid_scalar; canonical precision/scale overflow raises scalar_overflow. Allocation failure returns no partial Decimal. |
| cost | O(input bytes) scans with bounded coefficient storage; even a long all-zero input is scanned. Standard coefficient storage may allocate. |
| Design | [docs/scalars.md](../../../../scalars.md), [docs/semantics.md](../../../../semantics.md) |

## B0011

[Lines 88–96](../../../../../src/ir/scalar.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string Decimal::to_string() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render a canonical Decimal with sign and point in exact position. |
| inputs / outputs | Valid coefficient/scale produce owning canonical text, inserting fractional leading zeros as needed. |
| invariants | No exponent, plus sign, rounding or negative zero is introduced. |
| ownership | Owns ordinary output string/substring storage; source Decimal is borrowed. |
| failure | Standard allocation failure leaves the source unchanged. |
| cost | Bounded output at most41 bytes with possible ordinary string temporaries; not native zero-copy output. |
| Design | [docs/scalars.md](../../../../scalars.md), [docs/semantics.md](../../../../semantics.md) |

## B0013

[Lines 98–118](../../../../../src/ir/scalar.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::strong_ordering Decimal::operator<=>(const Decimal& other) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact Decimal numeric values without text-format allocation. |
| inputs / outputs | Two canonical values yield strong numeric ordering, including zero, negative and fractional cases. |
| invariants | Handle zero/sign, compare decimal exponents, then zero-pad coefficient comparisons; reverse magnitude order for negatives. |
| ownership | Borrows both canonical coefficients, no result storage beyond the ordering scalar. |
| failure | No allocation or arithmetic overflow for valid bounded coefficients/scales. |
| cost | At most38 coefficient comparisons after fixed sign/exponent work. |
| Design | [docs/scalars.md](../../../../scalars.md), [docs/semantics.md](../../../../semantics.md) |

## B0014

[Lines 119–119](../../../../../src/ir/scalar.cpp#L119); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L119-L119:sha256:250c3e1595f7269cedf50435b03d999ca6184ec33c6daa9baf0e4bd97c55f07a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [docs/code_specs/files/src/ir/scalar.cpp.md](scalar.cpp.md), [docs/scalars.md](../../../../scalars.md), [docs/semantics.md](../../../../semantics.md) |
