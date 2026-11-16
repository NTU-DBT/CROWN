# `tests/unit/planner_certificate_codec_test.cpp` — block usage map

[Source](../../../../../tests/unit/planner_certificate_codec_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `18d08373aa4bb45063a2fdb6bcf6a81cc95658651d57095cc4afb351f6d02c38`. 65 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../tests/unit/planner_certificate_codec_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 9–9](../../../../../tests/unit/planner_certificate_codec_test.cpp#L9) | Callable definition: void check(bool yes,const char* message) | calls std::runtime_error; guard void check(bool yes,const char* message) { if (!yes) throw std::runtime_error(message); } · [reviewed contract](#b0002) |
| [B0003 · 10–14](../../../../../tests/unit/planner_certificate_codec_test.cpp#L10) | Callable definition: template&lt;class F&gt; void rejects(F action,std::string_view code) | calls action, check, code, std::runtime_error; guard catch (const Error& error) { check(error.code()==code,"unexpected certificate codec error"); return… · [reviewed contract](#b0003) |
| [B0004 · 15–60](../../../../../tests/unit/planner_certificate_codec_test.cpp#L15) | Callable definition: void run() | calls planner::minimum_tree, planner::testing::minimum_tree_baseline, check, io::write_oracle; guard check(optimized.certificate_verified && baseline.certificate_verified &&; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 61–61](../../../../../tests/unit/planner_certificate_codec_test.cpp#L61) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |
| [B0006 · 62–65](../../../../../tests/unit/planner_certificate_codec_test.cpp#L62) | Callable definition: int main() | calls run, what; returns 1 · [reviewed contract](#b0006) |

## B0001

[Lines 1–8](../../../../../tests/unit/planner_certificate_codec_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:0684535ef47671f3bf6f6dc52451c80179a84c5a59cbc348b2b976e1e57bba4a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_certificate_codec_test.cpp: include "crown/api/error.hpp", "crown/io/oracle.hpp", "planner_probe.hpp", &lt;iostream&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/planner_certificate_codec_test.cpp](../../../../../tests/unit/planner_certificate_codec_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 9–9](../../../../../tests/unit/planner_certificate_codec_test.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool yes,const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a certificate-codec assertion with a diagnostic. |
| inputs / outputs | Accepts a Boolean and borrowed C string. |
| invariants | False is the only failure condition. |
| ownership | Message is borrowed. |
| failure | Throws std::runtime_error on false. |
| cost | One condition branch; a failed assertion constructs std::runtime_error and copies the C-string message. |
| Design | [tests/unit/planner_certificate_codec_test.cpp](../../../../../tests/unit/planner_certificate_codec_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0003

[Lines 10–14](../../../../../tests/unit/planner_certificate_codec_test.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F> void rejects(F action,std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert a codec action returns the expected planner Error code. |
| inputs / outputs | Accepts F by value and expected code; invokes named action() as an lvalue. |
| invariants | Only crown::Error is matched; the helper does not normalize arbitrary exceptions. |
| ownership | Callable is owned for the call; string_view is borrowed. |
| failure | Wrong error fails through check; no Error throws runtime_error; other exceptions propagate. |
| cost | One action invocation. |
| Design | [tests/unit/planner_certificate_codec_test.cpp](../../../../../tests/unit/planner_certificate_codec_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0004

[Lines 15–60](../../../../../tests/unit/planner_certificate_codec_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Round-trip optimized and baseline height certificates and reject malformed proof cases. |
| inputs / outputs | Constructs a two-atom query; writes/reads valid certificates, checks lower-bound replay, schema/tamper/unknown-algorithm cases, and resource-limited null certificates. |
| invariants | A readable unknown legacy algorithm is not a valid proof: verification rejects it. Resource limitation is not infeasibility. |
| ownership | All JSON, query, proof, and verification results are local. |
| failure | Expected codec errors are checked by rejects; any missing rejection or invalid verification throws runtime_error. |
| cost | Finite codec cases over one two-atom query and its bounded certificates. |
| Design | [tests/unit/planner_certificate_codec_test.cpp](../../../../../tests/unit/planner_certificate_codec_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0005

[Lines 61–61](../../../../../tests/unit/planner_certificate_codec_test.cpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L61:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in planner_certificate_codec_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/planner_certificate_codec_test.cpp](../../../../../tests/unit/planner_certificate_codec_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 62–65](../../../../../tests/unit/planner_certificate_codec_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the certificate-codec cases and report failure. |
| inputs / outputs | Calls run once; returns zero on success. |
| invariants | The success message follows the complete codec group. |
| ownership | No persistent state. |
| failure | Catches std::exception, writes the message, and returns 1. |
| cost | One fixed group. |
| Design | [tests/unit/planner_certificate_codec_test.cpp](../../../../../tests/unit/planner_certificate_codec_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
