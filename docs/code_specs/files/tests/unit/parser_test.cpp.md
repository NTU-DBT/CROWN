# `tests/unit/parser_test.cpp` — block usage map

[Source](../../../../../tests/unit/parser_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `aba1188ffb2623214a2904999474f26e75e399fc86c33fc7bee551ddef4d702e`. 113 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/unit/parser_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 14–16](../../../../../tests/unit/parser_test.cpp#L14) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 17–20](../../../../../tests/unit/parser_test.cpp#L17) | Callable definition: const SqlSyntax& syntax(const SqlParseResult& result) | calls std::runtime_error; returns *parsed · [reviewed contract](#b0003) |
| [B0004 · 21–26](../../../../../tests/unit/parser_test.cpp#L21) | Callable definition: const SqlDiagnostic& failure(const SqlParseResult& result, std::string_view code) | calls check, std::string; guard check(std::holds_alternative&lt;SqlDiagnostic&gt;(result), "expected failure: " + std::string(code));; returns diagnostic · [reviewed contract](#b0004) |
| [B0005 · 27–60](../../../../../tests/unit/parser_test.cpp#L27) | Callable definition: void ownership_and_boundaries() | calls parse_sql, std::string, crown::io::write_sql_parse, dump; guard check(syntax(owned).source.ends_with("-- tail"), "source text retained after temporary input dies");; 4 loop sites; source comment (unverified): // This throws inside JSON conversion after ParseOwner was constructed. · [reviewed contract](#b0005) |
| [B0006 · 61–83](../../../../../tests/unit/parser_test.cpp#L61) | Callable definition: void encoding_and_locations() | calls parse_sql, failure, check, find; guard check(diagnostic.byte_offset == text.find("FROM"), "Unicode cursor maps to byte offset");; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 84–99](../../../../../tests/unit/parser_test.cpp#L84) | Callable definition: void concurrent_callers() | calls errors, size, emplace_back, syntax; growth emplace_back; 4 loop sites · [reviewed contract](#b0007) |
| [B0008 · 100–101](../../../../../tests/unit/parser_test.cpp#L100) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0008) |
| [B0009 · 102–113](../../../../../tests/unit/parser_test.cpp#L102) | Callable definition: int main() | calls ownership_and_boundaries, encoding_and_locations, concurrent_callers, what; returns 0; 1 · [reviewed contract](#b0009) |

## B0001

[Lines 1–13](../../../../../tests/unit/parser_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:42a6f2a4bc8dbbf847f08c176328b53214134a46be42ba2bda512e932409ac83
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare parser_test.cpp: include "crown/frontend/parser.hpp", "crown/io/sql.hpp", &lt;exception&gt;, &lt;iostream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;thread&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/parser_test.cpp](../../../../../tests/unit/parser_test.cpp), [docs/sql_parser.md](../../../../sql_parser.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–16](../../../../../tests/unit/parser_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raises a parser-test exception on false. |
| inputs / outputs | Accepts bool and message reference. |
| invariants | Only the predicate result controls this helper; caller string expressions can allocate before entry. |
| ownership | Message remains borrowed for the call. |
| failure | False throws std::runtime_error. |
| cost | Branch-only assertion. |
| Design | [tests/unit/parser_test.cpp](../../../../../tests/unit/parser_test.cpp) |

## B0003

[Lines 17–20](../../../../../tests/unit/parser_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SqlSyntax& syntax(const SqlParseResult& result)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Returns the parsed SqlSyntax alternative from a parse-result variant. |
| inputs / outputs | Returns const SqlSyntax reference when the result holds syntax. |
| invariants | A syntax alternative is required; success is checked at the variant boundary. |
| ownership | Reference is borrowed from SqlParseResult and cannot outlive it. |
| failure | A diagnostic alternative throws std::runtime_error with the diagnostic message; the SqlParseResult continues to own that diagnostic. |
| cost | Variant test only; copies diagnostic text only on failure. |
| Design | [tests/unit/parser_test.cpp](../../../../../tests/unit/parser_test.cpp), [include/crown/frontend/parser.hpp](../../../../../include/crown/frontend/parser.hpp) |

## B0004

[Lines 21–26](../../../../../tests/unit/parser_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SqlDiagnostic& failure(const SqlParseResult& result, std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extracts a parser diagnostic and verifies its code. |
| inputs / outputs | Returns const SqlDiagnostic reference from the input result when its alternative and code match. |
| invariants | The result object must remain alive for the returned reference. |
| ownership | No diagnostic copy on successful extraction; the result owns the diagnostic. |
| failure | Wrong alternative throws std::runtime_error with the requested-code text; a wrong code reports the actual and expected code. Neither failure message includes SqlDiagnostic.message. |
| cost | Variant/code comparison only. |
| Design | [tests/unit/parser_test.cpp](../../../../../tests/unit/parser_test.cpp), [include/crown/frontend/parser.hpp](../../../../../include/crown/frontend/parser.hpp) |

## B0005

[Lines 27–60](../../../../../tests/unit/parser_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ownership_and_boundaries()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks parser input ownership, fixed iteration boundaries, empty SQL, and classification edges. |
| inputs / outputs | Parses successful/error/multiple-statement samples 500 times each, checks a parse-then-JSON resource case, five empty forms, five quoting/comment forms, and four syntax-valid-but-unsupported statements. |
| invariants | Raw source ranges and AST version are asserted; parse owners survive later calls and copy/move; parse-limit failure occurs during JSON export; syntax errors can supersede multi-statement classification. |
| ownership | SqlParseResult owns source/AST needed after the input temporary; copied/moved results are checked after original calls. |
| failure | Expected empty, syntax, limit, and not_checked outcomes are inspected in their result variants. |
| cost | 2,000 loop parses across four cases (success, syntax error, multiple statements, and conversion-limit error), plus the fixed boundary samples; ordinary AST/JSON allocations are not account measurements. |
| Design | [tests/unit/parser_test.cpp](../../../../../tests/unit/parser_test.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [include/crown/frontend/parser.hpp](../../../../../include/crown/frontend/parser.hpp), [docs/sql_parser.md](../../../../sql_parser.md) |

## B0006

[Lines 61–83](../../../../../tests/unit/parser_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void encoding_and_locations()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Checks byte offsets, Unicode coordinates, malformed UTF-8 diagnostics, and byte limit edges. |
| inputs / outputs | Parses one mixed Unicode/newline input, EOF/NUL inputs, six malformed UTF-8 strings, four valid strings, and byte-limit 7/8 variants. |
| invariants | Byte offsets are distinct from character/line/column fields; malformed bytes assert byte offset without fabricated Unicode position; the eight-byte boundary succeeds under configured AST cap. |
| ownership | Parser results own input bytes and diagnostics. |
| failure | Syntax and encoding errors are expected result alternatives; wrong location or boundary classification fails. |
| cost | Fifteen fixed parses: 13 encoding/location samples plus the two byte-limit boundary cases; no input-size scaling measurement. |
| Design | [tests/unit/parser_test.cpp](../../../../../tests/unit/parser_test.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [include/crown/frontend/parser.hpp](../../../../../include/crown/frontend/parser.hpp), [docs/sql_parser.md](../../../../sql_parser.md) |

## B0007

[Lines 84–99](../../../../../tests/unit/parser_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void concurrent_callers()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invokes independent parser calls concurrently and checks every result. |
| inputs / outputs | Starts four std::thread workers, each doing 25 successful parses and 25 syntax-error parses, joins all workers, then rethrows captured exceptions. |
| invariants | It tests concurrent caller correctness for these samples; it does not assert parallel parser execution or throughput. |
| ownership | Each thread owns its parse results; exception_ptr transports a failure to main thread after join. |
| failure | Worker exceptions are captured and rethrown after all joins, failing the test. |
| cost | Four workers ×25 iterations ×2 parses =200 parse calls, plus thread setup/join; no timing result. |
| Design | [tests/unit/parser_test.cpp](../../../../../tests/unit/parser_test.cpp), [src/frontend/parser.cpp](../../../../../src/frontend/parser.cpp), [include/crown/frontend/parser.hpp](../../../../../include/crown/frontend/parser.hpp), [docs/sql_parser.md](../../../../sql_parser.md) |

## B0008

[Lines 100–101](../../../../../tests/unit/parser_test.cpp#L100); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L100-L101:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in parser_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/parser_test.cpp](../../../../../tests/unit/parser_test.cpp), [docs/sql_parser.md](../../../../sql_parser.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 102–113](../../../../../tests/unit/parser_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Runs parser ownership, location, and concurrent-caller groups. |
| inputs / outputs | No arguments; invokes the three parser test functions and catches std::exception. |
| invariants | Success output requires each helper to return. |
| ownership | Helpers keep parser results and threads local. |
| failure | Caught exception is printed and returns nonzero. |
| cost | Three finite groups; no test execution claim is part of this source contract. |
| Design | [tests/unit/parser_test.cpp](../../../../../tests/unit/parser_test.cpp), [docs/sql_parser.md](../../../../sql_parser.md) |
