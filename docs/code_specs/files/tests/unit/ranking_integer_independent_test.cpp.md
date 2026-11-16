# `tests/unit/ranking_integer_independent_test.cpp` — block usage map

[Source](../../../../../tests/unit/ranking_integer_independent_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `16acab19c9096db452abb5df8cabdafb7f5951b77e77fc19a75adc643263260f`. 320 lines partitioned into 36 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../tests/unit/ranking_integer_independent_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 22–24](../../../../../tests/unit/ranking_integer_independent_test.cpp#L22) | Callable definition: void require(bool condition, const std::string& message) | calls std::runtime_error; guard void require(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 25–28](../../../../../tests/unit/ranking_integer_independent_test.cpp#L25) | Explanatory comments or spacing. | source comment (unverified): // Independent oracle: big-endian base-10 ASCII digits. Multiplication uses · [reviewed contract](#b0003) |
| [B0004 · 29–32](../../../../../tests/unit/ranking_integer_independent_test.cpp#L29) | Callable definition: std::string canonical(std::string value) | calls find_first_not_of, substr; returns first == std::string::npos ? @ : value.substr(first); source comment (unverified): // Independent oracle: big-endian base-10 ASCII digits. Multiplication uses · [reviewed contract](#b0004) |
| [B0005 · 33–33](../../../../../tests/unit/ranking_integer_independent_test.cpp#L33) | Explanatory comments or spacing. |  |
| [B0006 · 34–48](../../../../../tests/unit/ranking_integer_independent_test.cpp#L34) | Callable definition: std::string plus(const std::string& a, const std::string& b) | calls size, push_back, std::reverse, begin; returns canonical(result); growth push_back; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 49–49](../../../../../tests/unit/ranking_integer_independent_test.cpp#L49) | Explanatory comments or spacing. |  |
| [B0008 · 50–59](../../../../../tests/unit/ranking_integer_independent_test.cpp#L50) | Callable definition: std::string times(const std::string& a, const std::string& b) | calls canonical, plus; returns result; 2 loop sites · [reviewed contract](#b0008) |
| [B0009 · 60–60](../../../../../tests/unit/ranking_integer_independent_test.cpp#L60) | Explanatory comments or spacing. |  |
| [B0010 · 61–71](../../../../../tests/unit/ranking_integer_independent_test.cpp#L61) | Callable definition: std::string predecessor(std::string value) | calls require, size, canonical, std::runtime_error; guard require(value != "0", "decimal predecessor of zero");; returns canonical(value); 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 72–72](../../../../../tests/unit/ranking_integer_independent_test.cpp#L72) | Explanatory comments or spacing. |  |
| [B0012 · 73–87](../../../../../tests/unit/ranking_integer_independent_test.cpp#L73) | Callable definition: unsigned bit_length(std::string value) | calls push_back, canonical; returns count; growth push_back; 2 loop sites · [reviewed contract](#b0012) |
| [B0013 · 88–88](../../../../../tests/unit/ranking_integer_independent_test.cpp#L88) | Explanatory comments or spacing. |  |
| [B0014 · 89–92](../../../../../tests/unit/ranking_integer_independent_test.cpp#L89) | Callable definition: int ordering(const std::string& a, const std::string& b) | calls size; returns a.size() &lt; b.size() ? -1 : 1; a == b ? 0 : a &lt; b ? -1 : 1 · [reviewed contract](#b0014) |
| [B0015 · 93–93](../../../../../tests/unit/ranking_integer_independent_test.cpp#L93) | Explanatory comments or spacing. |  |
| [B0016 · 94–97](../../../../../tests/unit/ranking_integer_independent_test.cpp#L94) | Callable definition: std::string decimal(const UInt& value) | calls ; returns value.decimal(budget) · [reviewed contract](#b0016) |
| [B0017 · 98–98](../../../../../tests/unit/ranking_integer_independent_test.cpp#L98) | Explanatory comments or spacing. |  |
| [B0018 · 99–106](../../../../../tests/unit/ranking_integer_independent_test.cpp#L99) | Callable definition: void value_is(const UInt& actual, const std::string& expected) | calls decimal, require, bits, bit_length; guard require(rendered == expected, "decimal mismatch: expected " + expected + ", got " + rendered); · [reviewed contract](#b0018) |
| [B0019 · 107–107](../../../../../tests/unit/ranking_integer_independent_test.cpp#L107) | Explanatory comments or spacing. |  |
| [B0020 · 108–120](../../../../../tests/unit/ranking_integer_independent_test.cpp#L108) | Callable definition: UInt parse_for_driver(const std::string& value) | calls UInt::from, UInt::add, UInt::multiply, value_is; returns actual; 1 loop sites; source comment (unverified): // Only this private unit driver constructs wide values. Each constructed · [reviewed contract](#b0020) |
| [B0021 · 121–121](../../../../../tests/unit/ranking_integer_independent_test.cpp#L121) | Explanatory comments or spacing. |  |
| [B0022 · 122–131](../../../../../tests/unit/ranking_integer_independent_test.cpp#L122) | Callable definition: template&lt;class Function&gt; void fails(rank::Stop expected, Function&& operation) | calls operation, require, std::runtime_error; guard require(failure.stop == expected, "wrong arithmetic failure category"); · [reviewed contract](#b0022) |
| [B0023 · 132–132](../../../../../tests/unit/ranking_integer_independent_test.cpp#L132) | Explanatory comments or spacing. |  |
| [B0024 · 133–147](../../../../../tests/unit/ranking_integer_independent_test.cpp#L133) | Callable definition: template&lt;class Operation&gt; void exact_work(Operation operation) | calls operation, require, fails; guard require(measured.usage.work != 0, "operation has no charged work"); · [reviewed contract](#b0024) |
| [B0025 · 148–148](../../../../../tests/unit/ranking_integer_independent_test.cpp#L148) | Explanatory comments or spacing. |  |
| [B0026 · 149–172](../../../../../tests/unit/ranking_integer_independent_test.cpp#L149) | Callable definition: void binary_value(const UInt& a, const UInt& b, const std::string& expected, bool multiply) | calls bit_length, fails, UInt::multiply, UInt::add · [reviewed contract](#b0026) |
| [B0027 · 173–173](../../../../../tests/unit/ranking_integer_independent_test.cpp#L173) | Explanatory comments or spacing. |  |
| [B0028 · 174–199](../../../../../tests/unit/ranking_integer_independent_test.cpp#L174) | Callable definition: void primitive_inputs() | calls max, value_is, UInt::from, std::to_string; 2 loop sites · [reviewed contract](#b0028) |
| [B0029 · 200–200](../../../../../tests/unit/ranking_integer_independent_test.cpp#L200) | Explanatory comments or spacing. |  |
| [B0030 · 201–219](../../../../../tests/unit/ranking_integer_independent_test.cpp#L201) | Callable definition: std::vector&lt;std::string&gt; boundary_values() | calls plus, insert, predecessor, begin; returns {values.begin(), values.end()}; growth insert; 1 loop sites; source comment (unverified): // Alternating and sparse decimal operands give unequal low limbs and carry · [reviewed contract](#b0030) |
| [B0031 · 220–220](../../../../../tests/unit/ranking_integer_independent_test.cpp#L220) | Explanatory comments or spacing. |  |
| [B0032 · 221–240](../../../../../tests/unit/ranking_integer_independent_test.cpp#L221) | Callable definition: void cross_boundary_arithmetic() | calls boundary_values, push_back, parse_for_driver, size; guard require(UInt::compare(values\[i\], values\[j\], compare) == ordering(expected\[i\], expected\[j\]),; growth push_back; 3 loop sites · [reviewed contract](#b0032) |
| [B0033 · 241–241](../../../../../tests/unit/ranking_integer_independent_test.cpp#L241) | Explanatory comments or spacing. |  |
| [B0034 · 242–303](../../../../../tests/unit/ranking_integer_independent_test.cpp#L242) | Callable definition: void budgets_and_aliases() | calls parse_for_driver, exact_work, UInt::add, UInt::multiply; guard require(value.decimal(exact) == text, "exact decimal byte cap failed");; 2 loop sites · [reviewed contract](#b0034) |
| [B0035 · 304–305](../../../../../tests/unit/ranking_integer_independent_test.cpp#L304) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0035) |
| [B0036 · 306–320](../../../../../tests/unit/ranking_integer_independent_test.cpp#L306) | Callable definition: int main() | calls primitive_inputs, cross_boundary_arithmetic, budgets_and_aliases, what; returns 0; 1 · [reviewed contract](#b0036) |

## B0001

[Lines 1–21](../../../../../tests/unit/ranking_integer_independent_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:7a8654b40df5627509e625f381e95172e3259891396b0af9a0af5c3c507a28ff
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_integer_independent_test.cpp: include "ranking_detail.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 22–24](../../../../../tests/unit/ranking_integer_independent_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed private-driver assertion into a runtime_error. |
| inputs / outputs | A Boolean and const std::string diagnostic enter; success returns and false throws runtime_error(message). |
| invariants | The diagnostic is materialized at the call site before the branch; concatenated expected/got messages may allocate on successful checks too. |
| ownership | Borrows the diagnostic during the call; the thrown exception owns its copied text. |
| failure | False throws, and diagnostic/exception construction can fail; the helper does not translate arithmetic Failure categories. |
| cost | One conditional branch; eager std::string conversion/concatenation cost depends on message length, separate from Budget logical work. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0003

[Lines 25–28](../../../../../tests/unit/ranking_integer_independent_test.cpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L28:sha256:80152b2cba103734b154a225040a993878c65e1a55d1f91d874a591841e98fc8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Independent oracle: big-endian base-10 ASCII digits. Multiplication uses repeated decimal addition and decimal shifts; bit length uses long division by two. No production limb access, native-wide product, or rank helper. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 29–32](../../../../../tests/unit/ranking_integer_independent_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string canonical(std::string value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize a private oracle decimal string by removing leading zeroes. |
| inputs / outputs | Takes an owning decimal string by value; returns "0" when every character is zero, otherwise returns the suffix beginning at the first nonzero digit. |
| invariants | Assumes decimal digit input and canonicalizes zero; it does not validate signs or nondigit characters. |
| ownership | Parameter and returned substring own standard-library storage; input caller retains its own copy when passing an lvalue. |
| failure | String search/substr allocation failures propagate; there is no oracle error status. |
| cost | Scans to the first nonzero digit and may copy the remaining suffix, so work and allocation follow decimal string length. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp) |

## B0006

[Lines 34–48](../../../../../tests/unit/ranking_integer_independent_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string plus(const std::string& a, const std::string& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute decimal addition in the test oracle without reading production limbs. |
| inputs / outputs | Two borrowed canonical decimal strings produce an owning sum string through right-to-left digit addition, carry, reversal, and canonicalization. |
| invariants | This is independent base-10 test arithmetic and assumes digit strings; it is not a production score calculation or proof for all values. |
| ownership | Inputs are borrowed; result and temporary digit buffer are ordinary std::string owners. |
| failure | Allocation failures propagate; invalid characters are not separately rejected. |
| cost | Loops over the longer operand plus carry, then reverses and canonicalizes; string growth/copy cost depends on result digits. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0008

[Lines 50–59](../../../../../tests/unit/ranking_integer_independent_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string times(const std::string& a, const std::string& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute decimal multiplication for the independent expected-value oracle. |
| inputs / outputs | Two borrowed digit strings yield a decimal product by shifting an accumulated result once per digit of b and repeatedly adding a up to that digit's numeric value. |
| invariants | The oracle uses only decimal-string operations; it does not use production UInt limbs, native-wide products, or rank helpers. Inputs are expected to be canonical nonnegative digit strings. |
| ownership | Inputs are borrowed and each intermediate/result string owns its own standard storage. |
| failure | String allocation failures propagate; invalid digit input has no explicit validation path. |
| cost | Nested loops vary with operand digit lengths and each decimal digit (up to nine repeated plus calls); there is no fixed per-product CPU cost. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0010

[Lines 61–71](../../../../../tests/unit/ranking_integer_independent_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string predecessor(std::string value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the independent decimal string immediately below a positive value. |
| inputs / outputs | Takes a value string by copy, rejects "0", scans right-to-left borrowing across zeroes, decrements the first nonzero digit, and canonicalizes the returned string. |
| invariants | The test calls it with canonical positive powers of two; the helper is not a general decimal parser and does not check each character. |
| ownership | Owns its by-value working copy and returned string. |
| failure | Zero or an all-zero borrow path throws runtime_error; string allocation/search failures propagate. |
| cost | One reverse scan until a nonzero digit, followed by canonicalization; cost follows number of digits and borrow length. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0012

[Lines 73–87](../../../../../tests/unit/ranking_integer_independent_test.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
unsigned bit_length(std::string value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute an independent binary bit length by repeated decimal division by two. |
| inputs / outputs | Takes an owning decimal string and returns the number of divide-by-two rounds until it equals "0". |
| invariants | Inputs in these tests are canonical nonnegative decimals; the procedure is deliberately independent of UInt::bits and production limb representation. |
| ownership | Owns the working decimal value and a new quotient string each round; caller input is unaffected. |
| failure | Allocation failures propagate. Malformed or noncanonical inputs are outside the oracle's stated test domain. |
| cost | Each round scans every current decimal digit, builds a quotient, canonicalizes it, and repeats for the bit length; work grows across both digits and rounds. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp) |

## B0014

[Lines 89–92](../../../../../tests/unit/ranking_integer_independent_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int ordering(const std::string& a, const std::string& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the independent expected ordering for canonical nonnegative decimal strings. |
| inputs / outputs | Two borrowed strings return -1, 0, or 1 by digit-count comparison and then lexicographic comparison when lengths match. |
| invariants | Canonical equal-length decimal strings have the same lexical and numeric order; the helper assumes that input form. |
| ownership | Borrows both strings and returns a scalar. |
| failure | No explicit failure path; standard string comparison does not mutate inputs. |
| cost | Length mismatch is constant scalar work; equal lengths may compare through the first differing digit or all digits. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0016

[Lines 94–97](../../../../../tests/unit/ranking_integer_independent_test.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string decimal(const UInt& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render one private production UInt through its public-to-this-test decimal method under default ranking limits. |
| inputs / outputs | A borrowed UInt is passed with a fresh Budget constructed from default rank::Limits; an owning std::string is returned. |
| invariants | The helper does not inspect private limbs. Budget work/payload are production logical counters, not CPU time or whole allocator bytes. |
| ownership | UInt is borrowed; returned text is a separate std::string and Budget is local. |
| failure | Budget validation, logical limits, and std::string allocation failures propagate. |
| cost | UInt conversion charges 16 initial work units, 17 per generated decimal digit, and one per emitted digit, and admits output bytes through Budget; actual host string allocation is separate from that logical measure. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0018

[Lines 99–106](../../../../../tests/unit/ranking_integer_independent_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void value_is(const UInt& actual, const std::string& expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one actual UInt's exported decimal, bits, zero status, and canonical digit form to an independent oracle string. |
| inputs / outputs | A borrowed UInt and expected decimal string are checked through decimal(), bit_length(), zero(), canonical(), and digit search. |
| invariants | Assertions are bounded by supplied test values; oracle bit_length is independent repeated decimal division, not a second production implementation. |
| ownership | Borrows actual and expected; decimal/canonical temporaries are local owning strings. |
| failure | Any mismatch throws runtime_error; expected/got string concatenation for the first diagnostic is eager and can allocate even when values match. |
| cost | Formats once, computes independent bit length, and scans/canonicalizes digits with string work proportional to the value's decimal length; each Budget counter remains logical. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0020

[Lines 108–120](../../../../../tests/unit/ranking_integer_independent_test.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
UInt parse_for_driver(const std::string& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct test UInt operands from decimal text without private limb access and cross-check each parsed value. |
| inputs / outputs | A borrowed digit string is processed left-to-right using UInt::from(0), UInt::from(10), per-character digit conversion, multiply, and add under a fresh default Budget; the resulting UInt is returned by value. |
| invariants | Every constructed operand is immediately checked against value_is. Construction uses production UInt::from/multiply/add; independence comes from the decimal-string expected arithmetic/bit-length oracle, not from this parser. Test inputs are canonical nonnegative ASCII digit strings. |
| ownership | Returns a fixed-array UInt value; Budget and intermediate UInt values are local and the input text remains caller-owned. |
| failure | Budget work/bit failures, the immediate value_is assertion, or standard allocation failures abort the parse; no partially constructed UInt is returned. Character-to-digit conversion assumes ASCII 0..9 and is not a syntax validator, so malformed input is outside the helper contract. |
| cost | One loop per input digit charges UInt::from(18), multiply(304), and add(33) logical work units, followed by decimal/oracle checks; the loop is linear in text length but those Budget units do not measure host CPU time. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0022

[Lines 122–131](../../../../../tests/unit/ranking_integer_independent_test.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Function>
void fails(rank::Stop expected, Function&& operation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one operation to throw a ranking arithmetic Failure with the specified Stop category. |
| inputs / outputs | A Stop and callable are supplied; the callable is invoked once and normal return is treated as a test failure. |
| invariants | Only rank::detail::Failure is caught and its category is compared; unrelated exceptions propagate to main. |
| ownership | The forwarded operation is borrowed for this synchronous invocation; no arithmetic value is retained by this helper. |
| failure | Wrong Failure category or unexpected success throws runtime_error; the helper does not catch other exception types. |
| cost | One operation call plus the exception branch; the wrapped UInt work and eager diagnostic string construction are separate costs. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp) |

## B0024

[Lines 133–147](../../../../../tests/unit/ranking_integer_independent_test.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Operation>
void exact_work(Operation operation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a deterministic arithmetic operation succeeds at its measured logical work cap and fails one unit below it. |
| inputs / outputs | A callable is copied/moved by value; it runs with a default Budget to measure work, with a second Budget capped to that usage, and once more with work reduced by one. |
| invariants | Measured work must be nonzero and exactly reproducible at the cap; underflow call must report work_limit and stay within its cap. This compares Budget units, not elapsed CPU work. |
| ownership | Owns the callable copy and three local Budget values; operation-created arithmetic outputs are temporary. |
| failure | Any operation failure at the measured/exact runs, non-reproducible count, wrong Stop, or counter overshoot throws. |
| cost | Invokes the supplied operation three times; each invocation's loops/limb conversion determine logical work and actual CPU/allocation separately. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0026

[Lines 149–172](../../../../../tests/unit/ranking_integer_independent_test.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void binary_value(const UInt& a, const UInt& b, const std::string& expected, bool multiply) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one production add or multiply result to a decimal oracle and exercise the corresponding score-bit boundary. |
| inputs / outputs | Borrows two UInt operands, expected decimal result, and operation selector. If oracle bit length exceeds 512 it expects bit_limit under default rank::Limits; otherwise it checks a default-limit result (including the default 512-bit score ceiling), an exact max(1,bits) score cap, and, when cap exceeds one, a one-bit-lower failure. |
| invariants | The helper's edge case at one-bit results intentionally skips a zero-bit cap because zero is invalid_limits; these fixture pairs do not establish behavior for arbitrary operands. |
| ownership | Borrows operands/oracle; result values, Budgets, and error-path strings are local. |
| failure | Mismatched decimal/bits or stop throws. Allocation or oracle construction failures propagate. |
| cost | For results above 512 bits it attempts one operation under default limits and expects bit_limit. Otherwise it runs the default-limit operation, an exact score-bit-cap repeat, and a one-under failure when output bits exceed one. Each production add/multiply invocation charges 33/304 logical work units before calculation/bit rejection; successful value checks also format and independently inspect the result. These units are not host CPU costs. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0028

[Lines 174–199](../../../../../tests/unit/ranking_integer_independent_test.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void primitive_inputs() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check UInt conversion at twelve hand-selected uint64 boundaries and reject invalid score-bit limits. |
| inputs / outputs | Iterates zero, small values, 32-bit transitions, 64-bit high-bit values, and UINT64_MAX boundaries; each is checked as decimal, under exact work, and under an exact bit ceiling with one-under rejection when the ceiling exceeds one. Limits 0 and 513 must be invalid. |
| invariants | This is a finite hand-selected boundary set, not exhaustive uint64 coverage or a general performance bound. |
| ownership | The fixed array and each UInt/Budget are local; output and assertion strings use ordinary test allocations. |
| failure | Value mismatches throw runtime_error. exact_work separately expects work_limit for a one-under work cap; each value whose exact score-bit ceiling exceeds one also expects bit_limit for a one-under bit cap; score_bits 0 and 513 expect invalid_limits. |
| cost | Twelve values each trigger repeated UInt::from calls (18 logical work units apiece), formatting and exact-work runs plus two invalid-limit constructions; loops over the fixed array and decimal digit length. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0030

[Lines 201–219](../../../../../tests/unit/ranking_integer_independent_test.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::string> boundary_values() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the sorted unique decimal operands used for cross-boundary arithmetic comparisons. |
| inputs / outputs | Starts with six zero/small/uint64 values, doubles a decimal power through bit 512, inserts predecessor and selected power/power-plus-one boundaries at every 32 bits, adds three alternating/sparse patterns, then returns the ordered set as a vector. |
| invariants | The returned std::set&lt;std::string&gt; iteration order is lexical, not numeric; it contains 54 unique strings and reaches 155 decimal digits at the 512-bit boundary. The finite fixture is not exhaustive arithmetic verification or a universal operand/CPU bound. |
| ownership | The function owns its set, strings, power accumulator, and returned vector. |
| failure | Decimal string operations and set/vector allocation failures propagate. |
| cost | Runs 512 decimal-string doubling steps. At each of 16 multiples of 32 it inserts the predecessor; at the 15 checkpoints below 512 it also inserts the power and power-plus-one. Three sparse strings are added to six initial values; one generated predecessor duplicates an initial value, leaving 54 unique strings. Ordered-set order is lexical; comparison/storage and string sizes grow with digits. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0032

[Lines 221–240](../../../../../tests/unit/ranking_integer_independent_test.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cross_boundary_arithmetic() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare production add, multiply, and compare against the independent decimal oracle over every ordered pair in the generated boundary set. |
| inputs / outputs | Builds expected decimal strings and parsed UInt values, then nests over all value pairs; each pair tests addition, multiplication, ordering, and that both operands retain their prior decimal output. |
| invariants | The set and pair counts are derived from this source's deduplicated finite strings. The oracle does not read production limbs; exceeding 512 result bits is expected to fail with bit_limit. |
| ownership | The vector owns parsed UInts and strings; pair temporaries and Budgets live within the loop. Each UInt is a value, not a shared mutable operand. |
| failure | Any mismatch, wrong cap behavior, operand mutation, or arithmetic/allocation exception aborts the group. |
| cost | Performs 54²=2,916 ordered pairs. Each computes decimal-string oracle add/multiply; invokes binary_value for add and multiply (default attempt, exact bit-cap repeat and conditional one-under attempt for in-range outputs; a default-limit bit failure for outputs above 512); charges compare once (16 units); and formats operands before/after. Each production add/multiply invocation charges 33/304; successful decimal export charges 16 initial +17 per generated digit + one per emitted digit, plus payload bytes. Actual CPU and string-allocation costs are not measured. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0034

[Lines 242–303](../../../../../tests/unit/ranking_integer_independent_test.cpp#L242); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void budgets_and_aliases() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise exact work and payload ceilings, decimal export transactionality, alias-safe arithmetic failure, and the 512-bit boundary. |
| inputs / outputs | Builds four operands plus a maximum 512-bit value, tests exact work for add/multiply/compare and decimal output, exact/one-under output-byte limits, self-assignment add/multiply failures at zero work, successful alias multiply, low-bit add failure, and max-value carry/product overflow. |
| invariants | Failed assignment expressions leave the previous UInt/string intact; maximum value has 512 bits and 155 decimal digits. Each claim is limited to these explicit operands and Budget categories. |
| ownership | UInt values use fixed inline arrays; decimal outputs and oracle values are owning strings. Each Budget is local and no runtime account is involved. |
| failure | Expected stops are work_limit, byte_limit, or bit_limit at specified caps; any stop mismatch, operand/output mutation, or unexpected successful overflow throws. |
| cost | Runs multiple independent operation/cap scenarios, including repeated 155-digit formatting and big-integer oracle operations. Logical Budget accounting is distinct from standard string allocation and host CPU time. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |

## B0035

[Lines 304–305](../../../../../tests/unit/ranking_integer_independent_test.cpp#L304); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L304-L305:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ranking_integer_independent_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0036

[Lines 306–320](../../../../../tests/unit/ranking_integer_independent_test.cpp#L306); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Schedule the three private integer-driver groups and report a failure exit if any oracle or Budget assertion throws. |
| inputs / outputs | Calls primitive_inputs, cross_boundary_arithmetic, and budgets_and_aliases; returns zero after the group summary. |
| invariants | The driver is a finite selected boundary corpus, not a proof for all 512-bit values. Its printed boundaries=16 label counts the sixteen multiples-of-32 checkpoints, not the 54 unique operand strings or 2,916 ordered pairs; assertions are source evidence only in this packet. |
| ownership | Main owns only each group's local vectors, UInts, Budgets, and strings; no ranking runtime or query owner is constructed. |
| failure | std::exception failures print a diagnostic and return 1; an unexpected production Failure prints its stop and returns 2. This packet does not execute main. |
| cost | Schedules three groups; cross_boundary_arithmetic dominates with N-squared ordered pairs, and each pair uses string-oracle plus budgeted arithmetic work. |
| Design | [tests/unit/ranking_integer_independent_test.cpp](../../../../../tests/unit/ranking_integer_independent_test.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/planner/ranking_integer.cpp](../../../../../src/planner/ranking_integer.cpp), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |
