# `tests/reference/sql_scalar_driver.cpp` — block usage map

[Source](../../../../../tests/reference/sql_scalar_driver.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a00cf92c4d645c1fd83919c367d4808c24aebbeb5220b0a37efcdf352cd6834c`. 127 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../tests/reference/sql_scalar_driver.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 23–23](../../../../../tests/reference/sql_scalar_driver.cpp#L23) | Callable definition: void check(bool value, const char* message) | calls std::runtime_error; guard void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); } · [reviewed contract](#b0002) |
| [B0003 · 24–27](../../../../../tests/reference/sql_scalar_driver.cpp#L24) | Callable definition: Op operation(std::string_view name) | calls std::runtime_error; returns value; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 28–39](../../../../../tests/reference/sql_scalar_driver.cpp#L28) | Callable definition: scalar::Cell cell(const Json& value) | calls is_null, is_boolean, is_number_integer, is_string; returns {}; storage::ScalarView{value.get&lt;bool&gt;()} · [reviewed contract](#b0004) |
| [B0005 · 40–50](../../../../../tests/reference/sql_scalar_driver.cpp#L40) | Callable definition: Json encode(const scalar::Cell& value) | calls std::string, to_string, render, data; returns nullptr; *v · [reviewed contract](#b0005) |
| [B0006 · 51–76](../../../../../tests/reference/sql_scalar_driver.cpp#L51) | Callable definition: Json evaluate(const Json& request) | calls at, push_back, cell, contains; guard check(allocations == 0,"native SQL scalar computation allocated");; returns {{@ ,request.at(@ )}, {@ ,encode(result)}, {@ ,allocations},; growth push_back; 3 loop sites; source comment (unverified): // Only native computation is measured. Parsing, owning JSON output and · [reviewed contract](#b0006) |
| [B0007 · 77–77](../../../../../tests/reference/sql_scalar_driver.cpp#L77) | Explanatory comments or spacing. |  |
| [B0008 · 78–86](../../../../../tests/reference/sql_scalar_driver.cpp#L78) | Callable definition: template&lt;class Action&gt; void fault(Action action, storage::IndexFault expected) | calls deny, action, code, storage::IndexFailure; guard check(caught,"scalar contract/work failure changed its fixed fault family"); · [reviewed contract](#b0008) |
| [B0009 · 87–87](../../../../../tests/reference/sql_scalar_driver.cpp#L87) | Explanatory comments or spacing. | source comment (unverified): // Verify borrow and charge boundaries independently of SQL result comparisons. · [reviewed contract](#b0009) |
| [B0010 · 88–119](../../../../../tests/reference/sql_scalar_driver.cpp#L88) | Callable definition: void contracts() | calls text, std::string_view, deny, scalar::evaluate; guard check(std::get&lt;std::string_view&gt;(*result).data() == text.data(),"scalar return must borrow its stri…; source comment (unverified): // Verify borrow and charge boundaries independently of SQL result comparisons. · [reviewed contract](#b0010) |
| [B0011 · 120–120](../../../../../tests/reference/sql_scalar_driver.cpp#L120) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0011) |
| [B0012 · 121–127](../../../../../tests/reference/sql_scalar_driver.cpp#L121) | Callable definition: int main() | calls contracts, std::getline, evaluate, Json::parse; returns 0; 1; 1 loop sites · [reviewed contract](#b0012) |

## B0001

[Lines 1–22](../../../../../tests/reference/sql_scalar_driver.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr std::pair<std::string_view, Op> operations[] =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the single-translation-unit native scalar protocol and complete 21-opcode name table. |
| inputs / outputs | Private scalar API, one replacement-new hook, JSON support and static name/enum pairs feed the driver helpers. |
| invariants | The hook belongs only to this executable; operator mapping includes every current admitted SqlOperator alternative. |
| ownership | Static string views borrow literals; aliases and table create no query or runtime allocator. |
| failure | No scalar admission occurs in these declarations; unavailable headers fail compilation. |
| cost | Fixed compile-time table and constant aliases; mapping lookup and external I/O are outside denied-allocation intervals. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0002

[Lines 23–23](../../../../../tests/reference/sql_scalar_driver.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a driver contract assertion with a clear external diagnostic. |
| inputs / outputs | Boolean assertion and borrowed static message in; normal return if true. |
| invariants | A false assertion stops the driver through the outer error boundary. |
| ownership | The static message is borrowed until runtime_error copies it on failure. |
| failure | False throws runtime_error; its construction can allocate and is not native scalar computation. |
| cost | Fixed success branch; error formatting/exception cost belongs to failing test work. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0003

[Lines 24–27](../../../../../tests/reference/sql_scalar_driver.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Op operation(std::string_view name)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the authored JSON opcode name to the private scalar enum. |
| inputs / outputs | Borrowed operation string in; mapped SqlOperator out. |
| invariants | Only the explicit 21 names are accepted; the helper does not parse or bind SQL. |
| ownership | Name borrows request text for this call; no view is stored in the result. |
| failure | Unknown name throws runtime_error before the native no-new scope. |
| cost | Linear scan of a fixed 21-entry table with string comparisons, outside measured native computation. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0004

[Lines 28–39](../../../../../tests/reference/sql_scalar_driver.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L39:sha256:55e1befdc5aa8f82f47fb0bc99f1000f69faf0a17e20fce723acb09fea91242f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode the authored JSON scalar protocol into a nullable native cell while storing tagged payloads directly in their intended variant alternatives. |
| inputs / outputs | JSON null, boolean, signed integer, string, or tagged date/decimal object in; optional Cell out. String cells borrow the request JSON, while date and decimal cells own inline native values. |
| invariants | Boolean dispatch remains before integer decoding. Date and decimal payloads use their exact native parsers and are constructed directly as the corresponding ScalarView alternative inside Cell; no intermediate ScalarView-to-optional conversion is formed. |
| ownership | The input JSON outlives borrowed string views. Date/decimal parser results are stored in the Cell-owned variant alternative; temporary parser strings do not escape conversion. |
| failure | Invalid shape, absent tag data, or parse failure still propagates to the driver boundary; this helper adds no catch or recovery path and is not a public W05 input validator. |
| cost | Protocol inspection and parser work remain outside the no-new scalar evaluate region. Date/decimal construction initializes the optional variant in place and adds no heap policy or extra owner. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0005

[Lines 40–50](../../../../../tests/reference/sql_scalar_driver.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json encode(const scalar::Cell& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe a native scalar result without inspecting private numeric representation. |
| inputs / outputs | Borrowed Cell in; owning JSON null/bool/integer/string or tagged date/decimal value out. |
| invariants | NULL and false remain distinct. Exact canonical date/decimal spelling and variant kind are retained for the Python comparison. |
| ownership | Returned JSON owns copied output text; the input backing remains live during conversion. |
| failure | Owning JSON/string allocation or scalar rendering failure propagates outside the native evaluation interval. |
| cost | Output formatting/copying scales with text width and is not covered by the no-new scalar assertion. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0006

[Lines 51–76](../../../../../tests/reference/sql_scalar_driver.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json evaluate(const Json& request)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one public-value scalar observation with heap requests forbidden during native computation. |
| inputs / outputs | Request ID, opcode, authored values and optional positional arguments in; JSON result, replacement-new count and exact selected work out. |
| invariants | Build values/indices before Scope(0); use one nonrefilling fixed-diagnostic allowance; evaluate/assign only inside the denied interval. The JSON request outlives every borrowed string slot and encoding. |
| ownership | Vectors and output JSON are external test owners. Native spans borrow completed vectors; the returned Cell is copied before the scope ends and encoded while request backing remains live. |
| failure | Any replacement-new request throws, unexpected native/JSON/parse faults reach main, and nonzero observed count fails the assertion. No failure is treated as an oracle success. |
| cost | Only scalar evaluation is allocation-denied; parsing, vector growth, opcode lookup, JSON output and rendering remain external. Counter deltas measure selected work, not elapsed CPU. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0008

[Lines 78–86](../../../../../tests/reference/sql_scalar_driver.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void fault(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a fixed native contract/work failure under the same denied-new condition. |
| inputs / outputs | Test callback and expected public IndexFault code in; return after catching a matching IndexFailure. |
| invariants | The check uses the public code() API. Wrong fault code or no failure fails afterward; unrelated exception families escape instead of being accepted. |
| ownership | Callback borrows fixture state; no native error text is owned. C++ exception-runtime storage is not an operator-new measurement. |
| failure | Only IndexFailure is caught in the denied scope; final runtime_error on mismatch is outside it. |
| cost | One authored failing call plus code comparison; no production handler or query bookkeeping is added. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0009

[Lines 87–87](../../../../../tests/reference/sql_scalar_driver.cpp#L87); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Verify borrow and charge boundaries independently of SQL result comparisons.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate native borrow/work/diagnostic contract controls from mature SQL value comparisons. |
| inputs / outputs | The following contracts() fixture exercises private boundaries not represented by scalar SELECT queries. |
| invariants | USING left transfer and malformed slot/enum/type cases are native controls, not claimed SQL join/source-admission evidence. |
| ownership | Comment creates no data or owner. |
| failure | Assertions in the following fixture decide pass/fail; the prose installs no handling. |
| cost | No runtime cost; this is a test-scope qualification. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0010

[Lines 88–119](../../../../../tests/reference/sql_scalar_driver.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void contracts()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify scalar borrowing, ordered grants, short circuit and fixed contract failures. |
| inputs / outputs | Authored string/bool/integer slots and explicit allowances exercise native helper calls before JSON corpus processing. |
| invariants | Identity result aliases original string bytes; exact comparison uses two fields/512 bytes; one-under field cap preserves earlier left debit. NULL comparisons consume no scalar debit. False AND skips invalid later slot; USING reads left only. Accessed bad slots, nonbool truth, mismatched alternatives and invalid opcode fail as contracts. |
| ownership | String fixture remains live through all native views; arrays and allowances stay in scope. No result is treated as a retained payload owner. |
| failure | Each success scope denies replacement-new requests. fault() checks fixed failures; failed assertions or unexpected exceptions stop the process. |
| cost | Finite fixture work; deliberately failing calls, formatting and stderr output are test work. It proves observed hook/charge behavior, not a latency bound or full W05 integration. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |

## B0011

[Lines 120–120](../../../../../tests/reference/sql_scalar_driver.cpp#L120); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L120-L120:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_scalar_driver.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/reference/sql_scalar_driver.cpp](../../../../../tests/reference/sql_scalar_driver.cpp), [docs/scalars.md](../../../../scalars.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 121–127](../../../../../tests/reference/sql_scalar_driver.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute native boundary controls then stream one scalar response per input JSON line. |
| inputs / outputs | Newline JSON stdin in; newline result JSON stdout and diagnostic stderr/exit status out. |
| invariants | contracts() must pass before observations. Any exception ends with nonzero status so Python cannot silently accept truncated success. |
| ownership | Each parsed request temporary stays alive through evaluate/encoding; stream buffers and rendered output are caller/test-owned. |
| failure | One outer std::exception diagnostic boundary prints the failure and returns one; success returns zero. |
| cost | Linear input/output handling plus the explicitly measured computation inside each request; no production behavior is installed. |
| Design | [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/sql_normalization.md §NULLs, output mapping, and SQL row semantics](../../../../sql_normalization.md), [Refactor.md §W05 — Complete SQL NULL/type behavior and bag admission](../../../../../Refactor.md) |
