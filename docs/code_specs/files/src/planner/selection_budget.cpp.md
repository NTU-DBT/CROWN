# `src/planner/selection_budget.cpp` — block usage map

[Source](../../../../../src/planner/selection_budget.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Account selection work/resources/timing and translate component stop reasons.

Snapshot SHA-256: `02d2fdb5d15269909f3d8de96131f45a9159590bd84e551e83c3228d368e3aa1`. 198 lines partitioned into 39 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/planner/selection_budget.cpp#L1) | Imports dependencies; declares namespace scope. | source comment (unverified): // Pair each additive usage counter with its cap and diagnostic label. See · [reviewed contract](#b0001) |
| [B0002 · 9–13](../../../../../src/planner/selection_budget.cpp#L9) | Type/record definition: struct Dimension | source comment (unverified): // Pair each additive usage counter with its cap and diagnostic label. See · [reviewed contract](#b0002) |
| [B0003 · 14–25](../../../../../src/planner/selection_budget.cpp#L14) | declares values/defaults or compile-time conditions. | source comment (unverified): // Define shared order for cumulative checks and delegated merges. See · [reviewed contract](#b0003) |
| [B0004 · 26–32](../../../../../src/planner/selection_budget.cpp#L26) | Callable definition: void elapsed(rank::Usage& usage, std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end) noexcept | calls count; source comment (unverified): // Accumulate sampled active nanoseconds without wrapping. See docs/selection_accounting.md. · [reviewed contract](#b0004) |
| [B0005 · 33–33](../../../../../src/planner/selection_budget.cpp#L33) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |
| [B0006 · 34–34](../../../../../src/planner/selection_budget.cpp#L34) | Callable definition: void require(bool value, Stop stop) | calls ; guard void require(bool value, Stop stop) { if (!value) throw Failure{stop, Resource::none, {}, 0}; } · [reviewed contract](#b0006) |
| [B0007 · 35–37](../../../../../src/planner/selection_budget.cpp#L35) | Explanatory comments or spacing. | source comment (unverified): // Translate component status without exception-runtime work for diagnostics. · [reviewed contract](#b0007) |
| [B0008 · 38–59](../../../../../src/planner/selection_budget.cpp#L38) | Callable definition: Failure component_diagnostic(rank::Stop value, rank::Reasons reasons) noexcept | calls ; returns Failure{stop, resource, value, reasons}; source comment (unverified): // Translate component status without exception-runtime work for diagnostics. · [reviewed contract](#b0008) |
| [B0009 · 60–61](../../../../../src/planner/selection_budget.cpp#L60) | Explanatory comments or spacing. | source comment (unverified): // Unwind an unsuccessful delegated assessment using the same diagnostic mapping. See · [reviewed contract](#b0009) |
| [B0010 · 62–64](../../../../../src/planner/selection_budget.cpp#L62) | Callable definition: \[\[noreturn\]\] void component_failure(rank::Stop value, rank::Reasons reasons) | calls component_diagnostic; source comment (unverified): // Unwind an unsuccessful delegated assessment using the same diagnostic mapping. See · [reviewed contract](#b0010) |
| [B0011 · 65–66](../../../../../src/planner/selection_budget.cpp#L65) | Explanatory comments or spacing. | source comment (unverified): // Admit finite score/time limits and carried preparation usage. See · [reviewed contract](#b0011) |
| [B0012 · 67–73](../../../../../src/planner/selection_budget.cpp#L67) | Callable definition: Budget::Budget(const rank::Limits& value, rank::Usage initial,const resource::MemoryAccount& account) : limits(value), usage(init… | calls limits, usage, memory, require; guard require(limits.score_bits != 0 && limits.score_bits &lt;= 512 &&; source comment (unverified): // Admit finite score/time limits and carried preparation usage. See · [reviewed contract](#b0012) |
| [B0013 · 74–75](../../../../../src/planner/selection_budget.cpp#L74) | Explanatory comments or spacing. | source comment (unverified): // Reject consumed additive or active-time limits without modifying them. See · [reviewed contract](#b0013) |
| [B0014 · 76–82](../../../../../src/planner/selection_budget.cpp#L76) | Callable definition: void Budget::check() const | calls count; guard void Budget::check() const {; 1 loop sites; source comment (unverified): // Reject consumed additive or active-time limits without modifying them. See · [reviewed contract](#b0014) |
| [B0015 · 83–84](../../../../../src/planner/selection_budget.cpp#L83) | Explanatory comments or spacing. | source comment (unverified): // Sample a running outer interval without stopping the timer or checking limits. See · [reviewed contract](#b0015) |
| [B0016 · 85–91](../../../../../src/planner/selection_budget.cpp#L85) | Callable definition: void Budget::finish() noexcept | calls std::chrono::steady_clock::now, elapsed; source comment (unverified): // Sample a running outer interval without stopping the timer or checking limits. See · [reviewed contract](#b0016) |
| [B0017 · 92–92](../../../../../src/planner/selection_budget.cpp#L92) | Callable definition: void Budget::sample() | calls finish, check; guard void Budget::sample() { finish(); check(); } · [reviewed contract](#b0017) |
| [B0018 · 93–94](../../../../../src/planner/selection_budget.cpp#L93) | Explanatory comments or spacing. | source comment (unverified): // Reject a disallowed scalar debit before mutating that counter. See · [reviewed contract](#b0018) |
| [B0019 · 95–98](../../../../../src/planner/selection_budget.cpp#L95) | Callable definition: void Budget::add(std::uint64_t& current, std::uint64_t amount, std::uint64_t cap, Resource resource) | calls ; source comment (unverified): // Reject a disallowed scalar debit before mutating that counter. See · [reviewed contract](#b0019) |
| [B0020 · 99–99](../../../../../src/planner/selection_budget.cpp#L99) | Callable definition: void Budget::work(std::uint64_t n) | calls sample, add · [reviewed contract](#b0020) |
| [B0021 · 100–100](../../../../../src/planner/selection_budget.cpp#L100) | Callable definition: void Budget::cells(std::uint64_t n) | calls add · [reviewed contract](#b0021) |
| [B0022 · 101–101](../../../../../src/planner/selection_budget.cpp#L101) | Callable definition: void Budget::bytes(std::uint64_t n) | calls add · [reviewed contract](#b0022) |
| [B0023 · 102–102](../../../../../src/planner/selection_budget.cpp#L102) | Explanatory comments or spacing. | source comment (unverified): // Charge the keys processing dimension. See docs/selection_accounting.md. · [reviewed contract](#b0023) |
| [B0024 · 103–103](../../../../../src/planner/selection_budget.cpp#L103) | Callable definition: void Budget::keys(std::uint64_t n) | calls work, add; source comment (unverified): // Charge the keys processing dimension. See docs/selection_accounting.md. · [reviewed contract](#b0024) |
| [B0025 · 104–105](../../../../../src/planner/selection_budget.cpp#L104) | Explanatory comments or spacing. | source comment (unverified): // Derive a component grant that carries shared preparation exactly once. See · [reviewed contract](#b0025) |
| [B0026 · 106–120](../../../../../src/planner/selection_budget.cpp#L106) | Callable definition: rank::Limits Budget::begin_delegate(const rank::Usage& preparation) | calls sample, require, std::chrono::nanoseconds, count; guard require(preparation.*d.usage &lt;= usage.*d.usage);; returns out; 1 loop sites; source comment (unverified): // Derive a component grant that carries shared preparation exactly once. See · [reviewed contract](#b0026) |
| [B0027 · 121–122](../../../../../src/planner/selection_budget.cpp#L121) | Explanatory comments or spacing. | source comment (unverified): // Merge component work delta and measure delegated wall phase once. See · [reviewed contract](#b0027) |
| [B0028 · 123–142](../../../../../src/planner/selection_budget.cpp#L123) | Callable definition: void Budget::end_delegate(const rank::Usage& returned, const rank::Usage& preparation) | calls std::chrono::steady_clock::now, elapsed, require, add; guard require(returned.*d.usage &gt;= preparation.*d.usage);; 1 loop sites; source comment (unverified): // Merge component work delta and measure delegated wall phase once. See · [reviewed contract](#b0028) |
| [B0029 · 143–144](../../../../../src/planner/selection_budget.cpp#L143) | Explanatory comments or spacing. | source comment (unverified): // Classify historical evidence timing without inventing a clock measurement. See · [reviewed contract](#b0029) |
| [B0030 · 145–149](../../../../../src/planner/selection_budget.cpp#L145) | Callable definition: PreparationTiming preparation_timing(const std::optional&lt;rank::Evidence&gt;& evidence) noexcept | calls capture_accounting; returns PreparationTiming::absent; evidence-&gt;capture_accounting().processing_limits.active_time ?; source comment (unverified): // Classify historical evidence timing without inventing a clock measurement. See · [reviewed contract](#b0030) |
| [B0031 · 150–151](../../../../../src/planner/selection_budget.cpp#L150) | Explanatory comments or spacing. | source comment (unverified): // Compare admitted canonical nonnegative decimal score strings. See · [reviewed contract](#b0031) |
| [B0032 · 152–160](../../../../../src/planner/selection_budget.cpp#L152) | Callable definition: int decimal_compare(std::string_view a, std::string_view b, Budget& budget) | calls work, size, keys; returns a.size() &lt; b.size() ? -1 : 1; a\[i\] &lt; b\[i\] ? -1 : 1; 1 loop sites; source comment (unverified): // Compare admitted canonical nonnegative decimal score strings. See · [reviewed contract](#b0032) |
| [B0033 · 161–161](../../../../../src/planner/selection_budget.cpp#L161) | Explanatory comments or spacing. | source comment (unverified): // Order complete structural keys by unsigned bytes. See docs/selection_accounting.md. · [reviewed contract](#b0033) |
| [B0034 · 162–172](../../../../../src/planner/selection_budget.cpp#L162) | Callable definition: bool key_less(std::string_view a, std::string_view b, Budget& budget) | calls work, std::min, size, keys; returns x &lt; y; a.size() &lt; b.size(); 1 loop sites; source comment (unverified): // Order complete structural keys by unsigned bytes. See docs/selection_accounting.md. · [reviewed contract](#b0034) |
| [B0035 · 173–174](../../../../../src/planner/selection_budget.cpp#L173) | Explanatory comments or spacing. | source comment (unverified): // Check full exact byte equality with optional cache comparison accounting. See · [reviewed contract](#b0035) |
| [B0036 · 175–184](../../../../../src/planner/selection_budget.cpp#L175) | Callable definition: bool equal_bytes(std::string_view a, std::string_view b, Budget& budget, std::uint64_t* compared) | calls work, size, keys, Budget::add; returns false; false; 1 loop sites; source comment (unverified): // Check full exact byte equality with optional cache comparison accounting. See · [reviewed contract](#b0036) |
| [B0037 · 185–185](../../../../../src/planner/selection_budget.cpp#L185) | Explanatory comments or spacing. | source comment (unverified): // Admit canonical decimal caps through 2^512-1. See docs/selection_accounting.md. · [reviewed contract](#b0037) |
| [B0038 · 186–197](../../../../../src/planner/selection_budget.cpp#L186) | Callable definition: void validate_slot_limit(std::string_view text, Budget& budget) | calls require, empty, size, front; guard require(!text.empty() && text.size() &lt;= 155 && (text.size() == 1 \|\| text.front() != '0'), Stop::inv…; 2 loop sites; source comment (unverified): // Admit canonical decimal caps through 2^512-1. See docs/selection_accounting.md. · [reviewed contract](#b0038) |
| [B0039 · 198–198](../../../../../src/planner/selection_budget.cpp#L198) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::selection::detail · [reviewed contract](#b0039) |

## B0001

[Lines 1–8](../../../../../src/planner/selection_budget.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:e11b6ee9b3d8db5712e147f2ea13dafe649114171854e824da9c309e70b3057b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | make #include "selection_detail.hpp", #include &lt;algorithm&gt;, #include &lt;array&gt; available to src/planner/selection_budget.cpp; open crown::planner::selection::detail and anonymous helper namespace. Attached note: Pair each additive usage counter with its cap and diagnostic label. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0002

[Lines 9–13](../../../../../src/planner/selection_budget.cpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Dimension {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair each additive usage counter with its cap and diagnostic label. |
| inputs / outputs | Pointers-to-members in Usage/Limits plus Resource. |
| invariants | Covers eight additive dimensions, not candidate count/score bits/time. |
| ownership | Static value descriptors. |
| failure | No runtime validation. |
| cost | Fixed descriptor. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0003

[Lines 14–25](../../../../../src/planner/selection_budget.cpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr std::array dimensions{
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define shared order for cumulative checks and delegated merges. |
| inputs / outputs | Eight work/cell/key/payload/lower/identity/replay/normalization mappings. |
| invariants | Order determines first failure and partial accepted merge diagnostics. |
| ownership | Immutable static table. |
| failure | No allocation. |
| cost | Fixed eight entries. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0004

[Lines 26–32](../../../../../src/planner/selection_budget.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void elapsed(rank::Usage& usage,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate sampled active nanoseconds without wrapping. |
| inputs / outputs | Adds positive interval; negative interval or arithmetic overflow saturates to UINT64_MAX. |
| invariants | Diagnostic elapsed is not arrival rate or CPU instructions. |
| ownership | Mutates caller Usage. |
| failure | Noexcept; does not enforce the time ceiling. |
| cost | Fixed clock-duration arithmetic. |
| Design | [docs/selection_accounting.md §Optional active time](../../../../selection_accounting.md) |

## B0005

[Lines 33–33](../../../../../src/planner/selection_budget.cpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L33:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the lexical scope identified by the source span. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0006

[Lines 34–34](../../../../../src/planner/selection_budget.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value, Stop stop)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Throw a fixed selection failure when a required condition is false. |
| inputs / outputs | True returns; false throws Failure with Resource::none. |
| invariants | No mutable cache operation is performed here. |
| ownership | Value-only exception. |
| failure | Caller selects stop; default is internal_error. |
| cost | Fixed test plus exception-runtime cost only on failure. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md) |

## B0007

[Lines 35–37](../../../../../src/planner/selection_budget.cpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L37:sha256:72e4f21d30d8dc2886406e9ebba8025b1248a8643fe6488e4420784417b5788d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for component_diagnostic: Translate component status without exception-runtime work for diagnostics. Map ranking outcomes into stable selection diagnostics without throwing. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies component_diagnostic; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for component_diagnostic come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0008

[Lines 38–59](../../../../../src/planner/selection_budget.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Failure component_diagnostic(rank::Stop value, rank::Reasons reasons) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map ranking outcomes into stable selection diagnostics without throwing. |
| inputs / outputs | Returns Failure carrying original component stop/reasons. |
| invariants | complete maps internal_error; byte_limit remains resource_limit with Resource::none. |
| ownership | Owns only scalar values. |
| failure | Noexcept; unknown/internal cases conservatively stay internal_error. |
| cost | Fixed switch; no allocation or exception detour. |
| Design | [docs/selection.md](../../../../selection.md) |

## B0009

[Lines 60–61](../../../../../src/planner/selection_budget.cpp#L60); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L61:sha256:45d420ccae9cf1b2308bc62a6eb1e268fce8d55049c8378fc5ddb26f2c1b8d6b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for component_failure: Unwind an unsuccessful delegated assessment using the same diagnostic mapping. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies component_failure; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for component_failure come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0010

[Lines 62–64](../../../../../src/planner/selection_budget.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[noreturn]] void component_failure(rank::Stop value, rank::Reasons reasons)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Unwind an unsuccessful delegated assessment using the same diagnostic mapping. |
| inputs / outputs | Throws component_diagnostic(value,reasons). |
| invariants | Only callers needing transaction unwind use this boundary; note(rank::Stop) uses direct mapping. |
| ownership | Value-only Failure. |
| failure | Always throws; cache remains private. |
| cost | Fixed mapping plus exception-runtime overhead. |
| Design | [docs/selection_accounting.md §Atomic publication](../../../../selection_accounting.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0011

[Lines 65–66](../../../../../src/planner/selection_budget.cpp#L65); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L65-L66:sha256:78b068cdaf8c1ec0675bc3926199bd6d2dbc7ab783353bd4a775da37f04c7064
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Budget: Admit finite score/time limits and carried preparation usage. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Budget; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Budget come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0012

[Lines 67–73](../../../../../src/planner/selection_budget.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Budget::Budget(const rank::Limits& value, rank::Usage initial,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit finite score/time limits and carried preparation usage. |
| inputs / outputs | Copies limits/initial Usage/account; checks bits 1..512 and nonnegative time, then starts clock only if enabled. |
| invariants | Initial additive usage may equal caps; time at/above its cap rejects before work. |
| ownership | Shares account and owns counters/timer. |
| failure | Fixed Failure may abort Operation construction. |
| cost | Eight-counter checks; optional clock sample, no payload traversal. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/selection_accounting.md §Optional active time](../../../../selection_accounting.md) |

## B0013

[Lines 74–75](../../../../../src/planner/selection_budget.cpp#L74); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L75:sha256:2b98e96505107bc9700a98600081c5119ffa7eb7239fa2b508876958ed521275
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Budget: Reject consumed additive or active-time limits without modifying them. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Budget; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Budget come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0014

[Lines 76–82](../../../../../src/planner/selection_budget.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Budget::check() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject consumed additive or active-time limits without modifying them. |
| inputs / outputs | Counter greater-than cap fails; active time greater-or-equal fails. |
| invariants | Additive equality leaves zero remaining allowance; timing equality already stops. |
| ownership | Borrows Budget values. |
| failure | Throws first dimension Failure in table order. |
| cost | Fixed eight checks and optional duration comparison. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/selection_accounting.md §Optional active time](../../../../selection_accounting.md) |

## B0015

[Lines 83–84](../../../../../src/planner/selection_budget.cpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L84:sha256:8719234d8f41d926cad831aa051a46539bef001352b07abf933a7f1978da9b3b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Budget: Sample a running outer interval without stopping the timer or checking limits. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Budget; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Budget come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0016

[Lines 85–91](../../../../../src/planner/selection_budget.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Budget::finish() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sample a running outer interval without stopping the timer or checking limits. |
| inputs / outputs | Adds elapsed and advances started when running. |
| invariants | running remains true; finalize explicitly clears it after commit. Untimed calls sample no clock. |
| ownership | Updates Usage/time scalars. |
| failure | Noexcept, elapsed saturates. |
| cost | Optional one clock sample; no traversal. |
| Design | [docs/selection_accounting.md §Optional active time](../../../../selection_accounting.md) |

## B0017

[Lines 92–92](../../../../../src/planner/selection_budget.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Budget::sample() { finish(); check(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sample then enforce the current processing grant. |
| inputs / outputs | Calls finish followed by check. |
| invariants | Elapsed accounting precedes any resource exception. |
| ownership | Mutates owned budget scalars. |
| failure | Failure retains newly sampled diagnostic time. |
| cost | Fixed checks plus optional clock sample. |
| Design | [docs/selection_accounting.md §Optional active time](../../../../selection_accounting.md) |

## B0018

[Lines 93–94](../../../../../src/planner/selection_budget.cpp#L93); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L93-L94:sha256:0a5e0d1c02d733a054d3cc9890a079c53287dddb22f3e4e80fdf36f21108bc0f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Budget: Reject a disallowed scalar debit before mutating that counter. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Budget; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Budget come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0019

[Lines 95–98](../../../../../src/planner/selection_budget.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Budget::add(std::uint64_t& current,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a disallowed scalar debit before mutating that counter. |
| inputs / outputs | Checks current&gt;cap or amount&gt;cap-current, then adds. |
| invariants | Subtraction protects overflow; previously accepted other dimensions remain. |
| ownership | Borrows one counter. |
| failure | Throws resource_limit with supplied Resource. |
| cost | Constant arithmetic. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0020

[Lines 99–99](../../../../../src/planner/selection_budget.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Budget::work(std::uint64_t n)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge the work processing dimension. |
| inputs / outputs | Samples/checks, then debits usage.work. |
| invariants | Time/previous dimensions are checked before work addition. |
| ownership | Mutates Budget Usage only. |
| failure | Cap/overflow rejects before this counter increment; earlier debits stay diagnostic. |
| cost | Optional clock plus fixed addition. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0021

[Lines 100–100](../../../../../src/planner/selection_budget.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Budget::cells(std::uint64_t n)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge the cells processing dimension. |
| inputs / outputs | Debits usage.cells. |
| invariants | No clock sampling by this primitive. |
| ownership | Mutates Budget Usage only. |
| failure | Cap/overflow rejects before this counter increment; earlier debits stay diagnostic. |
| cost | Fixed addition. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0022

[Lines 101–101](../../../../../src/planner/selection_budget.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Budget::bytes(std::uint64_t n)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge the bytes processing dimension. |
| inputs / outputs | Debits modeled usage.payload_bytes. |
| invariants | Modeled payload differs from actual requested/account bytes. |
| ownership | Mutates Budget Usage only. |
| failure | Cap/overflow rejects before this counter increment; earlier debits stay diagnostic. |
| cost | Fixed addition. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0023

[Lines 102–102](../../../../../src/planner/selection_budget.cpp#L102); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L102-L102:sha256:89bf64d4be78f1ff6fe816f9583bdf533dd4d91048fe3468ada1b6fe12498e5c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for add: Charge the keys processing dimension. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies add; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for add come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0024

[Lines 103–103](../../../../../src/planner/selection_budget.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Budget::keys(std::uint64_t n)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge the keys processing dimension. |
| inputs / outputs | Charges work(n), then binding_key_bytes. |
| invariants | Key rejection can retain the successful work debit. |
| ownership | Mutates Budget Usage only. |
| failure | Cap/overflow rejects before this counter increment; earlier debits stay diagnostic. |
| cost | Optional clock plus two scalar debit checks. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0025

[Lines 104–105](../../../../../src/planner/selection_budget.cpp#L104); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L104-L105:sha256:45689fb21ffd08004469c840c9b810aed9714118e66d274487dc32b568536271
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Budget: Derive a component grant that carries shared preparation exactly once. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Budget; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Budget come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0026

[Lines 106–120](../../../../../src/planner/selection_budget.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
rank::Limits Budget::begin_delegate(const rank::Usage& preparation)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive a component grant that carries shared preparation exactly once. |
| inputs / outputs | After sample, returns D=P+(L-U) in each additive dimension and analogous remaining active time. |
| invariants | Requires P&lt;=U&lt;=L; sum cannot exceed L. With timing, pauses running flag while outer started remains delegate wall origin. |
| ownership | Returns scalar limits; retains outer account/counters. |
| failure | Invariant or time failure precedes delegation. |
| cost | Fixed dimension arithmetic plus optional clock sample. |
| Design | [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/selection_accounting.md §Optional active time](../../../../selection_accounting.md) |

## B0027

[Lines 121–122](../../../../../src/planner/selection_budget.cpp#L121); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L121-L122:sha256:e0036296d91f92414463c9dd0565ab18eda9ae619e7a12bed4a7aaa1bd489a0d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for Budget: Merge component work delta and measure delegated wall phase once. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies Budget; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for Budget come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0028

[Lines 123–142](../../../../../src/planner/selection_budget.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Budget::end_delegate(const rank::Usage& returned,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Merge component work delta and measure delegated wall phase once. |
| inputs / outputs | Adds V-P dimension deltas after sampling complete delegated wall interval; restarts outer running timer. |
| invariants | Does not add overlapping component elapsed again. Untimed return must not add a new elapsed delta. Earlier accepted dimensions can remain if a later merge fails. |
| ownership | Mutates outer Usage; component result remains independently retained. |
| failure | Failure occurs after wall sampling and in dimension order, preserving actual returned counters as far as admitted. |
| cost | Fixed merge checks plus clock sample; delegated cost is external. |
| Design | [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md), [docs/selection_accounting.md §Optional active time](../../../../selection_accounting.md) |

## B0029

[Lines 143–144](../../../../../src/planner/selection_budget.cpp#L143); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L143-L144:sha256:c6e07d8045cf4b7a61f01bb6427341137e0eaa4c0368c2ce5b80e84d91a5449d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for preparation_timing: Classify historical evidence timing without inventing a clock measurement. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies preparation_timing; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for preparation_timing come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0030

[Lines 145–149](../../../../../src/planner/selection_budget.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PreparationTiming preparation_timing(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify historical evidence timing without inventing a clock measurement. |
| inputs / outputs | Absent evidence -&gt; absent; capture active_time present -&gt; measured, otherwise unmeasured. |
| invariants | This reads capture configuration, not current owner freshness. |
| ownership | Borrows immutable Evidence. |
| failure | Noexcept. |
| cost | Fixed handle/configuration read. |
| Design | [docs/selection_accounting.md §Optional active time](../../../../selection_accounting.md) |

## B0031

[Lines 150–151](../../../../../src/planner/selection_budget.cpp#L150); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L150-L151:sha256:11769fddf0be46b4affad6e3ecf792758b724ac0537d6af114afdbc56c6cd7e5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for decimal_compare: Compare admitted canonical nonnegative decimal score strings. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies decimal_compare; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for decimal_compare come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0032

[Lines 152–160](../../../../../src/planner/selection_budget.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int decimal_compare(std::string_view a,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare admitted canonical nonnegative decimal score strings. |
| inputs / outputs | Length order, then digit order; returns -1/0/1. |
| invariants | Inputs must already be canonical; this function does not parse/validate them. |
| ownership | Borrows byte spans. |
| failure | Work/key cap may abort during examined pairs. |
| cost | One base work plus two work/key bytes per equal-length examined pair. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0033

[Lines 161–161](../../../../../src/planner/selection_budget.cpp#L161); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L161-L161:sha256:95e0c03052c553241868c81a67915b70d6237d6bb3001c98f2a9d67d6d8f83e6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for key_less: Order complete structural keys by unsigned bytes. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies key_less; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for key_less come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0034

[Lines 162–172](../../../../../src/planner/selection_budget.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool key_less(std::string_view a,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order complete structural keys by unsigned bytes. |
| inputs / outputs | Lexicographic byte comparison then length. |
| invariants | No hash or prefix-only equality authorizes artifact reuse. |
| ownership | Borrows stable key spans. |
| failure | Budget stops abort transaction. |
| cost | Base work plus two charged bytes per examined pair; linear common prefix. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0035

[Lines 173–174](../../../../../src/planner/selection_budget.cpp#L173); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L173-L174:sha256:dc6aa43d73454c53286f7133c6f32f8e1d253751e3b6eab47c445ffc02ea8786
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for equal_bytes: Check full exact byte equality with optional cache comparison accounting. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies equal_bytes; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for equal_bytes come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0036

[Lines 175–184](../../../../../src/planner/selection_budget.cpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool equal_bytes(std::string_view a,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check full exact byte equality with optional cache comparison accounting. |
| inputs / outputs | Length mismatch returns false; matching bytes update optional compared count. |
| invariants | Counters charge both bytes before comparison; overflow can follow admitted key traffic. |
| ownership | Borrows spans and optional scalar counter. |
| failure | Resource/counter stop leaves private work diagnostics, no cache mutation. |
| cost | Linear examined bytes with selected charge; no allocation. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md), [docs/selection_binding.md §Physical source and artifact frames](../../../../selection_binding.md) |

## B0037

[Lines 185–185](../../../../../src/planner/selection_budget.cpp#L185); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L185:sha256:1c9aa10630019ee89ed9c95259e6098ed966bc094b7f42cbf2264ea48cf8a43c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for validate_slot_limit: Admit canonical decimal caps through 2^512-1. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies validate_slot_limit; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for validate_slot_limit come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |

## B0038

[Lines 186–197](../../../../../src/planner/selection_budget.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_slot_limit(std::string_view text,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit canonical decimal caps through 2^512-1. |
| inputs / outputs | Checks nonempty &lt;=155 digits, leading zero, digits and maximal 155-digit bound. |
| invariants | Zero is valid; the cap is unitless slots. |
| ownership | Borrows caller text. |
| failure | Invalid input or work/key limit throws before publication. |
| cost | Charges each visited digit/pair; bounded input width does not imply allocator-byte prediction. |
| Design | [docs/selection_accounting.md §Exact charge primitives](../../../../selection_accounting.md) |

## B0039

[Lines 198–198](../../../../../src/planner/selection_budget.cpp#L198); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L198-L198:sha256:41848aefb30bbb259c959e13f974e1f553bad9051ef8e1ee6f1df63b5ac2ac7c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::selection::detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/selection_budget.cpp](../../../../../src/planner/selection_budget.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/selection_binding.md](../../../../selection_binding.md) |
