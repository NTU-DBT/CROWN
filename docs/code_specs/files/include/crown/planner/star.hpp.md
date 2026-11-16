# `include/crown/planner/star.hpp` — block usage map

[Source](../../../../../../include/crown/planner/star.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare cold opt-in literal star admission and original/source-only provenance without supplying a new minimum proof.

Snapshot SHA-256: `fa394ba78ee4e7f336f2551358134576c65990388ea9ec8387396cda9f303a08`. 78 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [star](../../../../subsystem_contracts.md#star). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/star.md](../../../../../star.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../../include/crown/planner/star.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 12–15](../../../../../../include/crown/planner/star.hpp#L12) | Type/record definition: struct Limits | source comment (unverified): // One selected admission/mapping balance. · [reviewed contract](#b0002) |
| [B0003 · 16–18](../../../../../../include/crown/planner/star.hpp#L16) | Type/record definition: struct Usage |  · [reviewed contract](#b0003) |
| [B0004 · 19–29](../../../../../../include/crown/planner/star.hpp#L19) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Cold opt-in metadata for the exact set family in P2 v1 Definition 4.5, · [reviewed contract](#b0004) |
| [B0005 · 30–30](../../../../../../include/crown/planner/star.hpp#L30) | Callable definition: Plan(Plan&& other) noexcept : data_(other.data_) | calls data_ · [reviewed contract](#b0005) |
| [B0006 · 31–31](../../../../../../include/crown/planner/star.hpp#L31) | Callable definition: Plan& operator=(Plan&& other) noexcept | returns *this · [reviewed contract](#b0006) |
| [B0007 · 32–53](../../../../../../include/crown/planner/star.hpp#L32) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Private source coordinator: the complete original catalog/options with an · [reviewed contract](#b0007) |
| [B0008 · 54–54](../../../../../../include/crown/planner/star.hpp#L54) | Callable definition: explicit Plan(std::shared_ptr&lt;const Data&gt; data) : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0008) |
| [B0009 · 55–78](../../../../../../include/crown/planner/star.hpp#L55) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Requires a genuine direct-CQ tree plan, non-null exact set semantics and · [reviewed contract](#b0009) |

## B0001

[Lines 1–11](../../../../../../include/crown/planner/star.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:a04a696db8acdcd6eb24f552276845b75b83379ac8e9735094cd43b19caf619c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import cold physical-plan admission and standard ownership/view types for the opt-in star plan API. |
| inputs / outputs | Header guard/includes and planner::star namespace opening; no query or source event input. |
| invariants | The API depends on genuine PhysicalPlan/lowerer metadata; inclusion itself supplies no structural or theorem authority. |
| ownership | Declarations own no mutable runtime state or query account. |
| failure | Dependency/type errors fail compilation; no runtime handler. |
| cost | Compile-time inclusion only. |
| Design | [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [include/crown/planner/lower.hpp](../../../../../../include/crown/planner/lower.hpp) |

## B0002

[Lines 12–15](../../../../../../include/crown/planner/star.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L15:sha256:62c7528469d12da005ab5718a83a276c788884602001ae7fbd164b77ca618413
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare independent selected-work and existing cold-lowering admission limits. |
| inputs / outputs | Limits.work defaults to1000000 and optional PhysicalLimits lowering may be supplied to admit(). |
| invariants | Selected shape/mapping work is one finite balance; optional lowering limits keep the existing separate lowerer/identity/validation cost contract. |
| ownership | Small caller-owned option values; constructing them does not allocate a query allowance. |
| failure | No check here; admit()/lower_tree enforce their respective grants. |
| cost | Constant-sized value initialization; not all physical CPU or allocation work. |
| Design | [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [src/planner/star.cpp](../../../../../../src/planner/star.cpp), [docs/star.md](../../../../../star.md) |

## B0003

[Lines 16–18](../../../../../../include/crown/planner/star.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L18:sha256:05e242e7309d6d19c9f1c2cf98fa45155bcaa2692b14cf52771f995778a70356
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose actual selected admission and source-only lowering work separately. |
| inputs / outputs | Usage contains work and lowering_work counters initialized tozero; Plan::usage() returns the completed values. |
| invariants | Counters describe executed cold admission work, not exact height, runtime update/delay, or total allocation/CPU usage. |
| ownership | Inline scalar metadata retained by immutable Plan::Data. |
| failure | No executable failure branch in this declaration. |
| cost | Fixed scalar storage/access. |
| Design | [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [src/planner/star.cpp](../../../../../../src/planner/star.cpp), [docs/star.md](../../../../../star.md) |

## B0004

[Lines 19–29](../../../../../../include/crown/planner/star.hpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L29:sha256:cc29832aaf98992fc34c71f276082e516434ec0e10ca8cec0285b4b4dde76500
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define immutable cold opt-in plan ownership and distinguish its family guard from minimum-height authority. |
| inputs / outputs | Plan declaration, surviving default copy operations and explanatory P2 Def4.5 family/receiving-account boundary. |
| invariants | Explicit center selection requires one all-variable center and distinct unary satellites. Admission does not search a new tree or upgrade the general checked upper to an optimum. |
| ownership | Copies share immutable ordinary compiler storage; actual native runtime admission must fund retained metadata under its receiving original account. |
| failure | Declarations/comments introduce no handler. Compiler allocations occur in the admitted factory, not in copy handles. |
| cost | Shared-handle copies are bounded; final owner release may destroy full compiler graphs. |
| Design | [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [src/planner/star.cpp](../../../../../../src/planner/star.cpp), [docs/star.md](../../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt](../../../../../../build/verification/v68-star-proof-v1/audit.txt) |

## B0005

[Lines 30–30](../../../../../../include/crown/planner/star.hpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L30:sha256:f8c2020b9061d5c7c5f57329c678a51c2097149b23c9584670e9b5f53064fcb2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move a Plan handle while deliberately retaining the source immutable owner. |
| inputs / outputs | Existing named Plan rvalue in; new Plan sharing the same nonnull Data out. |
| invariants | Move is copy-like, so both source and destination retain valid borrowing accessors; no arbitrary external Data enters. |
| ownership | Shares an existing immutable shared_ptr, creates no metadata copy or account. |
| failure | No allocation/throw; declared noexcept. |
| cost | One shared-owner reference increment. |
| Design | [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [src/planner/star.cpp](../../../../../../src/planner/star.cpp) |

## B0006

[Lines 31–31](../../../../../../include/crown/planner/star.hpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L31:sha256:2d0b27e62f918ab627b414815b74bd71f2200b29736177e6bdd95ae131478f2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assign a surviving Plan owner from an rvalue without emptying its source. |
| inputs / outputs | Destination and source Plan handles in; destination aliases source Data and source remains valid. |
| invariants | No deep clone or authority upgrade; replacing destination may release its former last owner. |
| ownership | Shared immutable ownership transfers by copying the handle; old destination graph can be destroyed. |
| failure | No allocating publication; declared noexcept. |
| cost | Bounded handle assignment plus possibly graph-sized destruction of the old final owner. |
| Design | [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [src/planner/star.cpp](../../../../../../src/planner/star.cpp) |

## B0007

[Lines 32–53](../../../../../../include/crown/planner/star.hpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L53:sha256:f81df405a00b407df7dd283085720db24baff7ee4c1e5ae81e36c22bc882be22
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare exact original/source-only plan, coordinate/head mapping and usage borrows. |
| inputs / outputs | Named Plan lvalue in; references/spans/IDs/scalars for general/source_only/center/table/d/j/satellites/ordered head/usage out; rvalue borrows are deleted. |
| invariants | Source-only plan retains complete catalog/options/constraints but has empty constant-true query/routes and is not the answer program or original proof. d is center arity; j counts distinct head variables while ordered repetitions survive. Missing satellites are conceptual truth. |
| ownership | Views borrow retained immutable Data and require a surviving Plan handle; scalar IDs/counts are copied. |
| failure | Valid private construction keeps Data nonnull; no status conversion or dynamic validation in getters. |
| cost | Bounded field/span/reference access; final owner release remains separate. |
| Design | [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [src/planner/star.cpp](../../../../../../src/planner/star.cpp), [include/crown/runtime/star.hpp](../../../../../../include/crown/runtime/star.hpp), [docs/star.md](../../../../../star.md) |

## B0008

[Lines 54–54](../../../../../../include/crown/planner/star.hpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L54:sha256:f4b25bc173383cb1cf8f6ce915a6b76453968424f051e5f2ec3b3670d5037f85
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Privately wrap a completely prepared immutable star admission payload. |
| inputs / outputs | Factory-owned shared_ptr&lt;const Data&gt; in; Plan handle out. |
| invariants | Only friend admit() can manufacture this payload owner; public DTO edits cannot create admission authority. |
| ownership | Moves existing shared ownership into the handle; no payload allocation here. |
| failure | No new fallible work after factory payload allocation. |
| cost | One shared-pointer move. |
| Design | [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [src/planner/star.cpp](../../../../../../src/planner/star.cpp) |

## B0009

[Lines 55–78](../../../../../../include/crown/planner/star.hpp#L55); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L78:sha256:56cf2c4a7ce25db4083b7888ee450a6f315e4cb765c4b6e5077cdad32b80b232
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Specify the exact cold admission/refusal/cost boundary and retain private Plan ownership. |
| inputs / outputs | Friend/data declarations plus public admit(general,center,limits) signature and full family/guarantee comments. |
| invariants | Direct non-null set tree, distinct physical tables, distinct variable-only center fields, distinct unary satellite coordinates and a satellite for every hidden coordinate are required. Full/repeated/permuted heads survive and no64-coordinate limit is imposed. Admission supplies no P2 delay/update or structural-dimension theorem. |
| ownership | Private Data owner survives copies/moves; compiler wrapper/vectors are ordinary storage. Runtime receiving-account import is a later boundary. |
| failure | Unsupported shapes: star_admission; selected work: star_work_limit; lowerer keeps its independent categories. Private failure preserves supplied general handle. |
| cost | Selected guard/mapping work excludes plan copies, allocations, scalar widths, ordered-set and source-only lower/identity/validation work. |
| Design | [include/crown/planner/star.hpp](../../../../../../include/crown/planner/star.hpp), [src/planner/star.cpp](../../../../../../src/planner/star.cpp), [docs/star.md](../../../../../star.md), [build/verification/v68-star-proof-v1/audit.txt](../../../../../../build/verification/v68-star-proof-v1/audit.txt), [Refactor.md](../../../../../../Refactor.md) |
