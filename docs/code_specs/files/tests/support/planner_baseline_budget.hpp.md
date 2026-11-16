# `tests/support/planner_baseline_budget.hpp` — block usage map

[Source](../../../../../tests/support/planner_baseline_budget.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `3aea508f97e9f25b26acb77ffeb91987526c1dd7872dc075b44ea07c52750c82`. 64 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/support/planner_baseline_budget.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Legacy baseline stop owns ordinary message text and may allocate on rejection. · [reviewed contract](#b0001) |
| [B0002 · 12–16](../../../../../tests/support/planner_baseline_budget.hpp#L12) | Type/record definition: struct SearchStopped : std::exception | returns reason.c_str(); source comment (unverified): // Legacy baseline stop owns ordinary message text and may allocate on rejection. · [reviewed contract](#b0002) |
| [B0003 · 17–18](../../../../../tests/support/planner_baseline_budget.hpp#L17) | declares types or opens a type body. |  · [reviewed contract](#b0003) |
| [B0004 · 19–24](../../../../../tests/support/planner_baseline_budget.hpp#L19) | Callable definition: public: explicit WorkBudget(const SearchLimits& limits) : limits_(limits), start_(std::chrono::steady_clock::now()) | calls limits_, start_, std::chrono::steady_clock::now, count · [reviewed contract](#b0004) |
| [B0005 · 25–25](../../../../../tests/support/planner_baseline_budget.hpp#L25) | Explanatory comments or spacing. |  |
| [B0006 · 26–36](../../../../../tests/support/planner_baseline_budget.hpp#L26) | Callable definition: void charge() | calls SearchStopped, std::chrono::steady_clock::now, max · [reviewed contract](#b0006) |
| [B0007 · 37–38](../../../../../tests/support/planner_baseline_budget.hpp#L37) | Explanatory comments or spacing. | source comment (unverified): // Charge precedes depth denial; a refused entry consumes work but not depth. · [reviewed contract](#b0007) |
| [B0008 · 39–54](../../../../../tests/support/planner_baseline_budget.hpp#L39) | Type/record definition: class Frame | source comment (unverified): // Charge precedes depth denial; a refused entry consumes work but not depth. · [reviewed contract](#b0008) |
| [B0009 · 55–55](../../../../../tests/support/planner_baseline_budget.hpp#L55) | Explanatory comments or spacing. |  |
| [B0010 · 56–56](../../../../../tests/support/planner_baseline_budget.hpp#L56) | Callable definition: \[\[nodiscard\]\] Frame frame() | calls Frame; returns Frame(*this) · [reviewed contract](#b0010) |
| [B0011 · 57–64](../../../../../tests/support/planner_baseline_budget.hpp#L57) | declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::planner::baseline_detail · [reviewed contract](#b0011) |

## B0001

[Lines 1–11](../../../../../tests/support/planner_baseline_budget.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:57c0b8da0d25891a0a38c5d1aa7a4a8d9c9eac4aa619bd344870445d00440d76
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_baseline_budget.hpp: include "crown/api/error.hpp", "crown/planner/oracle.hpp", &lt;exception&gt;, &lt;limits&gt;, &lt;string&gt;, &lt;utility&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–16](../../../../../tests/support/planner_baseline_budget.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SearchStopped : std::exception {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry an owning reason for the legacy partition baseline's resource stop. |
| inputs / outputs | Moves a by-value std::string into reason; what() returns reason.c_str(). |
| invariants | This is a baseline control exception, not a checked proof/infeasibility artifact. It is not the fixed no-message native MemoryFailure diagnostic. |
| ownership | Exception owns reason bytes. what() borrows until exception destruction/change; implicit copies can allocate string payload, user constructor does not delete copy/move. |
| failure | Reason/message construction can itself throw bad_alloc; baseline caller separately catches bad_alloc as resource_limit without accepting partial proof. |
| cost | Possible string allocation/copy plus exception propagation; what() is fixed nonthrowing reference access. |
| Design | [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
  const char* what() const noexcept override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the baseline stop's stored diagnostic bytes. |
| inputs / outputs | Returns reason.c_str(). |
| invariants | Message does not certify proof completion or change work limits. |
| ownership | Pointer borrows the SearchStopped string; copy its bytes if retaining beyond catch/exception lifetime. |
| failure | Declared noexcept, no recovery or allocation. |
| cost | Fixed pointer return without formatting/copy. |
| Design | [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 17–18](../../../../../tests/support/planner_baseline_budget.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class WorkBudget {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose explicit baseline producer work/time/host-stack limits for the legacy comparison solver. |
| inputs / outputs | Owns SearchLimits, start steady-clock time, public SearchStatistics and private current recursion depth. charge/frame mutate one actual instance referenced by PartitionSearch. |
| invariants | No explicitly deleted WorkBudget copy/move: copying would duplicate limits/start/depth/counters, not share a grant. Actual baseline keeps one instance and passes reference. This is host-recursive baseline support, distinct from production logical continuation depth/accounting. |
| ownership | Inline limits/time/counters only; no row, native account or typed proof owner. |
| failure | Negative time throws invalid_search_limits; resource guards throw owning SearchStopped; baseline adapter clears partial outputs on those/actual bad_alloc. |
| cost | charge performs named abstract work steps and optional clock check, not total CPU/bytes/allocator accounting. Frame uses actual host scope depth; baseline algorithms perform substantial separate container/proof work. |
| Design | [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 19–24](../../../../../tests/support/planner_baseline_budget.hpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  explicit WorkBudget(const SearchLimits& limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize one baseline allowance and its wall-clock origin. |
| inputs / outputs | Copies limits, always samples steady_clock::now into start_, rejects negative present millisecond time limit. |
| invariants | Zero time remains explicit immediate exhaustion at first charge; absent time skips later charge clock checks but constructor still samples one clock. |
| ownership | Owns copied fixed limits/time; caller SearchLimits need not survive. |
| failure | Negative limit throws Error(invalid_search_limits); diagnostic construction may allocate. No fallback/unlimited substitution. |
| cost | Fixed limits copy plus one steady clock sample, not native memory admission. |
| Design | [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 26–36](../../../../../tests/support/planner_baseline_budget.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void charge()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one legacy baseline abstract work unit after work/time/overflow checks. |
| inputs / outputs | Rejects used&gt;=present work cap, then elapsed floored milliseconds&gt;=present time cap, then uint64 work maximum; only on success increments statistics.work. |
| invariants | Previous admitted units remain spent. Zero work denies before time sampling; resource-stop message is ordinary owning text. This does not bound every branch/container allocation or microsecond of solver work. |
| ownership | Mutates this budget's inline counters; no shared native allowance/account. |
| failure | Throws SearchStopped with exact work/time/counter reason; message allocation can fail independently. No catch/refund/retry. |
| cost | Fixed checks/increment plus Clock::now/duration only when time cap present; represented work still executes separately in caller. |
| Design | [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 37–38](../../../../../tests/support/planner_baseline_budget.hpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L38:sha256:1f9adbbb990f232fad26196e608168fb2d5dc2ad547792b69ddcf9f32e1b4c76
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Charge precedes depth denial; a refused entry consumes work but not depth. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 39–54](../../../../../tests/support/planner_baseline_budget.hpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  class Frame {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair one admitted baseline recursion entry with unconditional depth cleanup. |
| inputs / outputs | Constructor charges work first, checks depth&gt;=optional recursion cap, then increments depth; destructor decrements on successful construction. It holds WorkBudget&. |
| invariants | Depth refusal can consume the already admitted work unit but leaves depth unchanged. Copy/assignment are deleted; user destructor suppresses implicit move. frame() uses guaranteed prvalue copy elision, not duplicated depth guards. |
| ownership | Borrows exact budget, which must outlive the lexical frame; no heap/account or proof data owned. |
| failure | Charge/recursion denial throws before depth increment; constructed frame unwinds depth without throwing/allocating. |
| cost | Fixed entry/exit arithmetic plus charge's optional clock; tracks actual host recursion scopes rather than allocating a continuation stack. |
| Design | [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 56–56](../../../../../tests/support/planner_baseline_budget.hpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] Frame frame()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open a noncopyable baseline recursion frame through direct prvalue return. |
| inputs / outputs | Returns Frame(*this); language-guaranteed copy elision constructs the returned guard directly. |
| invariants | Caller keeps automatic guard alive for the recursive scope. It is not a heap stack or new work budget. |
| ownership | Guard borrows this WorkBudget; must not outlive it. |
| failure | Frame constructor charge/depth errors propagate before a live guard escapes. |
| cost | Fixed object construction plus charge clock/check cost, no Frame allocation or copy. |
| Design | [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 57–64](../../../../../tests/support/planner_baseline_budget.hpp#L57); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  SearchStatistics statistics;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose baseline counters separately from private limit/time/depth state. |
| inputs / outputs | statistics holds work and solver-updated route counts; limits_/start_/depth_ preserve current admission state. |
| invariants | Counters alone do not establish optimum/certificate validity; independent complete replay remains authority. Default WorkBudget copies duplicate this state, so actual callers retain one referenced instance. |
| ownership | All fields inline; no scalar key/string/row owner. |
| failure | Exact charge guards work overflow; other baseline route statistics follow their caller limits, not a universal saturating counter protocol. |
| cost | Fixed storage, no instrumentation in production runtime or source rows. |
| Design | [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |
