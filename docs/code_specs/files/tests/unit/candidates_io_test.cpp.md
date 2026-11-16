# `tests/unit/candidates_io_test.cpp` — block usage map

[Source](../../../../../tests/unit/candidates_io_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `1c6c8933c384c9fb0603eb2f8fe5c4205f8e1f7407f2be673646870d9b36c548`. 217 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/unit/candidates_io_test.cpp#L1) | Imports dependencies; declares namespace scope. | growth new · [reviewed contract](#b0001) |
| [B0002 · 12–12](../../../../../tests/unit/candidates_io_test.cpp#L12) | Type/record definition: enum class Mode |  · [reviewed contract](#b0002) |
| [B0003 · 13–13](../../../../../tests/unit/candidates_io_test.cpp#L13) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 14–16](../../../../../tests/unit/candidates_io_test.cpp#L14) | Type/record definition: struct Unexpected final : std::exception | returns @ · [reviewed contract](#b0004) |
| [B0005 · 17–24](../../../../../tests/unit/candidates_io_test.cpp#L17) | Callable definition: void* allocate(std::size_t bytes) | calls std::malloc; returns value; growth allocate, malloc · [reviewed contract](#b0005) |
| [B0006 · 25–25](../../../../../tests/unit/candidates_io_test.cpp#L25) | Closes surrounding scope/type. |  · [reviewed contract](#b0006) |
| [B0007 · 26–26](../../../../../tests/unit/candidates_io_test.cpp#L26) | Callable definition: void* operator new(std::size_t bytes) | calls allocation_probe::allocate; returns allocation_probe::allocate(bytes); growth allocate, new · [reviewed contract](#b0007) |
| [B0008 · 27–27](../../../../../tests/unit/candidates_io_test.cpp#L27) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns allocation_probe::allocate(bytes); growth allocate, new · [reviewed contract](#b0008) |
| [B0009 · 28–28](../../../../../tests/unit/candidates_io_test.cpp#L28) | Callable definition: void operator delete(void* value) noexcept | calls std::free · [reviewed contract](#b0009) |
| [B0010 · 29–29](../../../../../tests/unit/candidates_io_test.cpp#L29) | Callable definition: void operator delete\[\](void* value) noexcept | calls  · [reviewed contract](#b0010) |
| [B0011 · 30–30](../../../../../tests/unit/candidates_io_test.cpp#L30) | Callable definition: void operator delete(void* value, std::size_t) noexcept | calls std::free · [reviewed contract](#b0011) |
| [B0012 · 31–31](../../../../../tests/unit/candidates_io_test.cpp#L31) | Callable definition: void operator delete\[\](void* value, std::size_t) noexcept | calls  · [reviewed contract](#b0012) |
| [B0013 · 32–36](../../../../../tests/unit/candidates_io_test.cpp#L32) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 37–37](../../../../../tests/unit/candidates_io_test.cpp#L37) | Callable definition: void check(bool ok, const char* message) | calls std::runtime_error; guard void check(bool ok, const char* message) { if (!ok) throw std::runtime_error(message); } · [reviewed contract](#b0014) |
| [B0015 · 38–38](../../../../../tests/unit/candidates_io_test.cpp#L38) | Type/record definition: struct Fixture |  · [reviewed contract](#b0015) |
| [B0016 · 39–56](../../../../../tests/unit/candidates_io_test.cpp#L39) | Callable definition: Fixture fixture(int version) | calls push_back, Date::parse, Decimal::parse; returns f; growth push_back · [reviewed contract](#b0016) |
| [B0017 · 57–62](../../../../../tests/unit/candidates_io_test.cpp#L57) | Callable definition: VerifiedOptimum prove(const Fixture& f) | calls ExactSearch::create, check, advance, optimum; guard check(owner.advance({10'000'000, {}}).progress.result == ResultKind::verified_optimum,; returns *owner.optimum() · [reviewed contract](#b0017) |
| [B0018 · 63–71](../../../../../tests/unit/candidates_io_test.cpp#L63) | Callable definition: void exhaust(CandidateProvider& p) | calls advance, check; guard check(r.stopped_for == CandidateStop::candidate_ready \|\| r.stopped_for == CandidateStop::quantum_wo…; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 72–74](../../../../../tests/unit/candidates_io_test.cpp#L72) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_invocable_v&lt;decltype(&report::write_candidate_progress), const CandidateProg… · [reviewed contract](#b0019) |
| [B0020 · 75–217](../../../../../tests/unit/candidates_io_test.cpp#L75) | Callable definition: int main(int argc, char** argv) | calls check, std::string_view, io::Json::array, fixture; guard check(argc == 2 && std::string_view(argv\[1\]) == "--emit", "usage: candidates_io_test --emit");; returns 1; growth push_back; 2 loop sites · [reviewed contract](#b0020) |

## B0001

[Lines 1–11](../../../../../tests/unit/candidates_io_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:8177cf5ed4d2095ef5ec0552681325cdf64c79b585d1721bd731a47a564f3b95
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare candidates_io_test.cpp: include "crown/io/candidates.hpp", "crown/api/error.hpp", "crown/planner/verify.hpp", &lt;iostream&gt;, &lt;stdexcept&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;cstdlib&gt;, &lt;new&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–12](../../../../../tests/unit/candidates_io_test.cpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Mode { normal, allocation_failure, unexpected_failure };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Names the probe mode consumed by the next replaced ordinary allocation. |
| inputs / outputs | One global state chooses normal allocation, bad_alloc or unexpected exception. |
| invariants | allocate resets it before acting; a mode affects at most one ordinary new/new\[\] call. |
| ownership | Translation-unit global, not synchronized or a production allocator. |
| failure | Unknown enum state falls through normal path. |
| cost | Fixed enum access; allocation cost is performed by allocate. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0003

[Lines 13–13](../../../../../tests/unit/candidates_io_test.cpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L13:sha256:c8deed9e7e26aba77aa3b981eecab8dccf351a282a8937de5e72290e992cbfc0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare candidates_io_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 14–16](../../../../../tests/unit/candidates_io_test.cpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Unexpected final : std::exception {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Defines a stateless exception distinct from std::bad_alloc for provider failure classification. |
| inputs / outputs | No payload; what() returns a literal. |
| invariants | Used only by the unexpected_failure probe branch. |
| ownership | Exception object owns no dynamic message. |
| failure | No catch/classification here. |
| cost | Fixed-size construction and throw path. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0005

[Lines 17–24](../../../../../tests/unit/candidates_io_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* allocate(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implements one-shot probe allocation using malloc or one injected exception. |
| inputs / outputs | Size in; malloc-backed pointer or std::bad_alloc/Unexpected. |
| invariants | Copies and resets global mode before branch; size zero requests one byte; malloc failure throws bad_alloc. |
| ownership | Matching global delete overloads release returned storage. |
| failure | An armed mode throws bad_alloc or Unexpected, and malloc failure throws bad_alloc. This translation unit defines ordinary unaligned throwing new/new\[\] replacements, with no aligned or nothrow overload definitions. Default library nothrow forms can delegate to throwing replacements, so missing nothrow definitions do not prove bypass of this hook. |
| cost | Copies and resets one global mode, then either throws the injected exception or calls malloc once for max(bytes,1). This function never calls free; matching delete bodies do. No allocation census or RSS measurement is performed. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [exact paper reference](https://eel.is/c++draft/new.delete.single) |

## B0006

[Lines 25–25](../../../../../tests/unit/candidates_io_test.cpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L25:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in candidates_io_test.cpp: namespace allocation_probe. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 26–26](../../../../../tests/unit/candidates_io_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return allocation_probe::allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Routes ordinary scalar operator new through the injected allocator. |
| inputs / outputs | Byte count in; pointer/exception out. |
| invariants | Delegates directly to allocate. |
| ownership | Returned storage is malloc-backed and freed by matching global delete replacements defined in this test translation unit. Those replacements apply to ordinary allocations in the linked test executable, not only calls from this function. |
| failure | Probe exceptions propagate without wrapper. |
| cost | Same single allocation path; not total allocation measurement. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0008

[Lines 27–27](../../../../../tests/unit/candidates_io_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return allocation_probe::allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Routes ordinary array operator new\[\] through the injected allocator. |
| inputs / outputs | Array byte count in; pointer/exception out. |
| invariants | Shares the global one-shot mode with scalar new. This definition is the ordinary unaligned throwing array overload; no aligned or nothrow overload is defined here. That is a definition-scope statement, not proof that indirect nothrow requests cannot reach a throwing replacement. |
| ownership | Returned pointer is malloc-backed. |
| failure | Probe exceptions propagate. |
| cost | One malloc path or injected throw; no heap census. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0009

[Lines 28–28](../../../../../tests/unit/candidates_io_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* value) noexcept { std::free(value); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Matches scalar unsized delete with free for replacement allocations. |
| inputs / outputs | Pointer in; no return. |
| invariants | Uses std::free and noexcept. |
| ownership | Releases malloc storage. |
| failure | No free error reporting. |
| cost | One free call. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0010

[Lines 29–29](../../../../../tests/unit/candidates_io_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* value) noexcept { std::free(value); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Matches array unsized delete with free for replacement allocations. |
| inputs / outputs | Pointer in; no return. |
| invariants | Uses std::free and noexcept; no element destructor behavior is implemented here. |
| ownership | Releases malloc storage. |
| failure | No free error reporting. |
| cost | One free call. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0011

[Lines 30–30](../../../../../tests/unit/candidates_io_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* value, std::size_t) noexcept { std::free(value); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Matches scalar sized delete with free for replacement allocations. |
| inputs / outputs | Pointer and compiler size in; no return; size ignored. |
| invariants | Uses std::free and noexcept. |
| ownership | Releases malloc storage. |
| failure | No size validation or error reporting. |
| cost | One free call; size is not accounting. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0012

[Lines 31–31](../../../../../tests/unit/candidates_io_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* value, std::size_t) noexcept { std::free(value); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Matches array sized delete with free for replacement allocations. |
| inputs / outputs | Pointer and compiler size in; no return; size ignored. |
| invariants | Uses std::free and noexcept. |
| ownership | Releases malloc storage. |
| failure | No size validation; other allocation forms are not covered. |
| cost | One free call. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0013

[Lines 32–36](../../../../../tests/unit/candidates_io_test.cpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L36:sha256:b23d88b01eb39e982a73d4096c569d5a6a982b698329a4a349028f13a3f15b1c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare candidates_io_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 37–37](../../../../../tests/unit/candidates_io_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool ok, const char* message) { if (!ok) throw std::runtime_error(message); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Throws a test runtime_error when a local assertion is false. |
| inputs / outputs | Boolean plus const char* message in; returns or throws. |
| invariants | No provider or JSON inspection beyond condition passed by caller. |
| ownership | Borrows message until a failure exception is built. |
| failure | False condition throws runtime_error; main catches standard exceptions. |
| cost | Branch only; error construction may allocate. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0015

[Lines 38–38](../../../../../tests/unit/candidates_io_test.cpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture { Catalog catalog; Query query; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pairs the catalog and query for report fixtures. |
| inputs / outputs | Owns Catalog and Query values. |
| invariants | Their IDs and indices are established by fixture(). |
| ownership | Value vectors/strings owned by record. |
| failure | No validation here; proof factory validates downstream. |
| cost | Small fixture copies/moves. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0016

[Lines 39–56](../../../../../tests/unit/candidates_io_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture fixture(int version) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Builds one of the three report CQs used by main. |
| inputs / outputs | Version 1 creates R(x), S(x,y), T(y); versions 2/3 create D with date/decimal constants and ignored string; 3 sets source schema version 2. |
| invariants | Main calls only 1,2,3; each result binds the exact catalog/query pair. |
| ownership | Returns an owning Fixture by value. |
| failure | Other version integers fall into the single-table branch; scalar parse errors propagate. |
| cost | Small fixed vectors and scalar parses, not a workload benchmark. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0017

[Lines 57–62](../../../../../tests/unit/candidates_io_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VerifiedOptimum prove(const Fixture& f) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtains the original P06 optimum consumed by candidate and IO reports. |
| inputs / outputs | Fixture const reference in; a copy of owner.optimum() out. |
| invariants | One ExactSearch advance with 10,000,000 grant must report verified_optimum before dereference. |
| ownership | The local search owns its continuation. The returned VerifiedOptimum copies a shared immutable authority handle retaining the admitted binding, upper and proof after facade teardown; it does not deep-copy the certificate payload. |
| failure | If the single advance does not verify optimum, assertion throws; there is no retry. |
| cost | Admits the input and makes one advance with a 10,000,000-work grant. Returning the authority handle copies shared ownership, not all proof data. Search/proof construction has its own allocations; the grant is not measured CPU/bytes. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0018

[Lines 63–71](../../../../../tests/unit/candidates_io_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exhaust(CandidateProvider& p) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drains one provider until its exact provider-family exhaustion result. |
| inputs / outputs | Mutable CandidateProvider ref in; mutates it through at most 100 advances. |
| invariants | Each quantum grants 1,000,000 work; only candidate_ready/quantum_work continue and exhausted returns. |
| ownership | Caller owns provider; no retained handle. |
| failure | Unexpected stop or guard exhaustion throws runtime_error. |
| cost | Up to 100 advances, each with specified work grant; generation and allocation are not benchmarked. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0019

[Lines 72–74](../../../../../tests/unit/candidates_io_test.cpp#L72); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L72-L74:sha256:912ed1689eabe1a1205c67b9f89ff94288e6e1087ba0ed897e1c5ae1f6ea32a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare candidates_io_test.cpp: require 2 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/candidates_io_test.cpp](../../../../../tests/unit/candidates_io_test.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 75–217](../../../../../tests/unit/candidates_io_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc, char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produces native --emit examples for a separate candidate-report schema driver, covering progress/snapshot/candidate writers, proof replay, resource/fault stops and residual-cache provenance. |
| inputs / outputs | Requires --emit; builds three fixture proofs/providers, appends JSON reports; success prints JSON and returns zero. |
| invariants | The native producer checks report binding and original-proof replay; the admitted-progress writer leaves provider work and candidate_count unchanged; a copied partial snapshot serializes identically after the live owner exhausts; exported candidates are independently P02-valid at h*; the ordinary certificate reader rejects the report envelope; record_limit is observed; one injected bad_alloc yields allocation_failure and the same owner later returns candidate_ready; an injected non-bad_alloc exception yields terminal internal_failure; moved-from candidate writing is rejected; residual-seed and cached provenance retain frozen_residual_trace_only scope. Separately, the Python CTest driver validates emitted documents against candidate-report-v1 JSON Schema and rejects its finite schema/authority mutations. |
| ownership | Owns local proofs/providers/snapshots/candidates and allocating JSON DOM/output; reports repeat exported proof/binding/tree data. |
| failure | Main catches std::exception, resets probe and returns 1; expected Error rejections are caught locally; invalid CLI arguments fail. |
| cost | Four ExactSearch setup advances (one for each of the three report versions and one residual fixture, each with a 10,000,000 grant); provider advances use 1,000,000 grants and drain guard 100; residual search uses a 50,000,000 grant. Proof replay and JSON/tree serialization allocate outside candidate work accounting; grants are ceilings, not measured consumption/time. |
| Design | [include/crown/io/candidates.hpp](../../../../../include/crown/io/candidates.hpp), [src/io/candidates.cpp](../../../../../src/io/candidates.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [tools/verify_candidate_reports.py](../../../../../tools/verify_candidate_reports.py), [schemas/candidate-report-v1.schema.json](../../../../../schemas/candidate-report-v1.schema.json), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md) |
