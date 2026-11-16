# `src/ir/input_program.hpp` — block usage map

[Source](../../../../../src/ir/input_program.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs.

Snapshot SHA-256: `2356d5755cd6c23043e6556bde3f3b05602ba28a67584c26a7360c8b1d93d93c`. 154 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_identity.md](../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/ir/input_program.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 11–17](../../../../../src/ir/input_program.hpp#L11) | Type/record definition: struct InputInstruction |  · [reviewed contract](#b0002) |
| [B0003 · 18–18](../../../../../src/ir/input_program.hpp#L18) | Type/record definition: struct InputRange |  · [reviewed contract](#b0003) |
| [B0004 · 19–19](../../../../../src/ir/input_program.hpp#L19) | Explanatory comments or spacing. |  |
| [B0005 · 20–24](../../../../../src/ir/input_program.hpp#L20) | Callable definition: inline void input_column(const InputInstruction& instruction,storage::RowView row, InputCells values,storage::IndexWorkAllowance*) | calls size, storage::IndexFailure, at · [reviewed contract](#b0005) |
| [B0006 · 25–30](../../../../../src/ir/input_program.hpp#L25) | Callable definition: template&lt;frontend::SqlOperator Operation&gt; void input_operation(const InputInstruction& instruction,storage::RowView, InputCells v… | calls size, storage::IndexFailure, frontend::sql_detail::evaluate · [reviewed contract](#b0006) |
| [B0007 · 31–48](../../../../../src/ir/input_program.hpp#L31) | Callable definition: inline InputInstruction::Execute input_executor(frontend::SqlOperator operation) | calls CROWN_INPUT_OPERATION, storage::IndexFailure; returns &input_operation&lt;name&gt; · [reviewed contract](#b0007) |
| [B0008 · 49–51](../../../../../src/ir/input_program.hpp#L49) | Explanatory comments or spacing. | source comment (unverified): // Logical preparation checkpoints are separate from base-copy IndexWork. No · [reviewed contract](#b0008) |
| [B0009 · 52–69](../../../../../src/ir/input_program.hpp#L52) | Type/record definition: class InputBudget | source comment (unverified): // Logical preparation checkpoints are separate from base-copy IndexWork. No · [reviewed contract](#b0009) |
| [B0010 · 70–77](../../../../../src/ir/input_program.hpp#L70) | declares types or opens a type body. | source comment (unverified): // A prepared owner exists only in the opted-in mode. Its argument views refer · [reviewed contract](#b0010) |
| [B0011 · 78–82](../../../../../src/ir/input_program.hpp#L78) | Callable definition: PreparedInputs(const resource::MemoryAccount& account,resource::MemoryAttribution owner, InputPreparationLimits value,InputPrepar… | calls limits, usage, instructions, ranges · [reviewed contract](#b0011) |
| [B0012 · 83–83](../../../../../src/ir/input_program.hpp#L83) | Explanatory comments or spacing. |  |
| [B0013 · 84–109](../../../../../src/ir/input_program.hpp#L84) | Callable definition: static InputPreparationUsage analyze(const std::optional&lt;NormalizedSql&gt;& sql,std::size_t ports, const InputPreparationLimits& lim… | calls budget, step, size, storage::IndexFailure; returns usage; usage; 3 loop sites; source comment (unverified): // A constant executable has no ports even when its admitted SQL source · [reviewed contract](#b0013) |
| [B0014 · 110–141](../../../../../src/ir/input_program.hpp#L110) | Callable definition: static std::shared_ptr&lt;const PreparedInputs&gt; build(const resource::MemoryAccount& account, resource::MemoryAttribution owner,cons… | calls allocation, budget, reserve, step; returns result; growth make_accounted_shared, push_back, reserve; 2 loop sites · [reviewed contract](#b0014) |
| [B0015 · 142–148](../../../../../src/ir/input_program.hpp#L142) | Callable definition: void execute(OccurrenceId port,storage::RowView row,InputCells values,storage::IndexWorkAllowance* work) const | calls at, admit; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 149–149](../../../../../src/ir/input_program.hpp#L149) | Closes surrounding scope/type. |  · [reviewed contract](#b0016) |
| [B0017 · 150–153](../../../../../src/ir/input_program.hpp#L150) | Callable definition: inline storage::IndexWork input_work_difference(storage::IndexWork before,storage::IndexWork after) | calls ; returns {before.structural_steps-after.structural_steps,before.scalar_fields-after.scalar_fields, · [reviewed contract](#b0017) |
| [B0018 · 154–154](../../../../../src/ir/input_program.hpp#L154) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::program::detail · [reviewed contract](#b0018) |

## B0001

[Lines 1–10](../../../../../src/ir/input_program.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:ebdf80954164b204f853afb67185b4a2fb380e3d01564b59134114856113762f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define private account-aware storage and scalar-view aliases for prepared SQL adapters. |
| inputs / outputs | Program model, ownership allocator and unchanged sql_scalar helper; InputVector and mutable optional-value span aliases. |
| invariants | Private implementation accepts no serialized caller bytecode; optional cells retain SQL NULL representation. |
| ownership | Vectors use supplied MemoryAllocator; spans borrow scratch values. |
| failure | No runtime allocation in includes/aliases. |
| cost | Compile-time only; worker templates share existing scalar implementation. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0002

[Lines 11–17](../../../../../src/ir/input_program.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L17:sha256:4c457fd59d6b5fe751322b5dd6c6fbdfcd7509d31fab989fe334e76e61705c14
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one prebound expression worker and its validated operands. |
| inputs / outputs | Expression target, optional column, borrowed argument IDs and fixed internal Execute function pointer. |
| invariants | Only analyze/build create instructions from admitted normalized expressions. Column and operation workers are selected internally; no caller callback is installed. |
| ownership | Instruction value owns scalar IDs/pointer; arguments borrow immutable resulting normalized storage. |
| failure | Record construction alone cannot fail; builder validates variants and executor domain before publication. |
| cost | Fixed-size instruction; metadata capacity is explicitly accounted/reported. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0003

[Lines 18–18](../../../../../src/ir/input_program.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L18:sha256:44dcf85cf9aab5f9a9944f9074608e5117977a6034fcd7de922e3aecbddbfcca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe a port-contiguous segment in the flat instruction table. |
| inputs / outputs | begin offset and count, initially zero. |
| invariants | Each range is built from one actual executable adapter in port order; offset/count stay inside the completed instruction vector. |
| ownership | Plain values; PreparedInputs owns range/instruction tables. |
| failure | No allocation/failure in record definition. |
| cost | Constant-size port descriptor; avoids one vector/control per port. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0005

[Lines 20–24](../../../../../src/ir/input_program.hpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L24:sha256:ff597e4f934c562883efafd64635239317594866aaa7bab77678124069d2358e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute a prebound physical-column read. |
| inputs / outputs | Validated instruction, borrowed physical row and mutable optional SQL values; writes the target cell. |
| invariants | Target bound is checked; row.at enforces column bound. Required per-expression step and physical scalar checks occur in caller, matching interpreter order. |
| ownership | Writes only scratch cells; copied ScalarView borrows validated physical value until adaptation completes. |
| failure | Out-of-range target/column raises contract; no tuple has been published. |
| cost | One indexed column read/write; no variant/operator decoding or allocation. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0006

[Lines 25–30](../../../../../src/ir/input_program.hpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L30:sha256:3ffd935143ba2ff2bf032ed38e470723ab5d1d856c118d290b0f9ff7cbb533ff
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute one prebound SQL operator using the unchanged scalar evaluator. |
| inputs / outputs | Compile-time SqlOperator, argument IDs, scratch values and borrowed work allowance; writes target optional value. |
| invariants | Target bound and shared evaluate enforce the same argument/NULL/domain/scalar-work contract as interpreter; no alternate arithmetic implementation. |
| ownership | Argument span borrows program; values are scratch; result views follow shared evaluator lifetime rules. |
| failure | Existing contract/scalar/work errors propagate without tuple publication. |
| cost | Shared operator cost plus one static worker call; no per-query machine-code generation. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0007

[Lines 31–48](../../../../../src/ir/input_program.hpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L48:sha256:86c654e83802f6e44ae8bf12cb2590f83cf64ac9b26776a3b0f78b7dce6cd9e4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the closed admitted SQL operator set to internal fixed workers. |
| inputs / outputs | SqlOperator enum in; internal InputInstruction::Execute pointer out. |
| invariants | All current evaluator operation tags have a case. This cold switch runs during preparation; user pointers/code cannot enter this table. |
| ownership | Returned pointer refers to shared static template code, not query-owned executable memory. |
| failure | Unknown enum raises existing contract failure. |
| cost | Cold fixed-size switch; one shared executable contains workers for all queries. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0008

[Lines 49–51](../../../../../src/ir/input_program.hpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L51:sha256:fced1663edf0d2e5ed8095bc4da761bc3cb2579190c5548e8b6441efc84eff99
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document distinct logical preparation and borrowed native grant scopes. |
| inputs / outputs | Comment only; no new allowance object or runtime behavior. |
| invariants | Preparation never refills a receiving owner grant. |
| ownership | No owned storage. |
| failure | No execution or failure. |
| cost | No runtime cost. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0009

[Lines 52–69](../../../../../src/ir/input_program.hpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L69:sha256:f78da9ceb066befbf83c635879848b8a17bddb6bf61058331dd41620004f68ea
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preadmit finite logical checkpoints and selected native metadata pointer slots. |
| inputs / outputs | Borrowed limits, mutable usage record and optional receiving IndexWork pointer; step increments work, table&lt;T&gt; charges representable capacity bytes as pointer slots. |
| invariants | Logical cap is checked before step withdrawal/increment. Native allowance remains caller-owned and unreplenished. Byte multiplication is checked; pointer-slot rounding avoids overflow. table admission is a logical checkpoint, not an exact allocator CPU/control-block bound. |
| ownership | InputBudget borrows all three authorities and retains no allocation. |
| failure | Work exhaustion, native denial and multiplication overflow propagate before the admitted allocation/write; prior consumed work is not refunded. |
| cost | Constant arithmetic per step/table; subsequent allocations still use finite MemoryAccount. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0010

[Lines 70–77](../../../../../src/ir/input_program.hpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L77:sha256:ef86915402a887b5ddbe90ad53f26595f6861831d185f34b411cfa1ee6894198
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep extra instruction/range tables only in opted-in immutable programs. |
| inputs / outputs | PreparedInputs retains finite limits, usage and two account-backed vectors. |
| invariants | Argument spans borrow enclosing result normalized metadata; no separate expression graph copy or global cache exists. |
| ownership | Prepared owner and table capacities use receiver attribution. Data outlives instruction execution; table destruction never dereferences argument spans. |
| failure | Construction/growth failures unwind private owner; no partial publication. |
| cost | One owner plus flat capacities proportional to executable ports/instructions. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0011

[Lines 78–82](../../../../../src/ir/input_program.hpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L82:sha256:08097eb4803e5c4983d9b2c02ffa984806ac7d1af2e619d56dedc92f7daaac00
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize empty prepared tables using the receiving immutable-metadata allocator. |
| inputs / outputs | Account/attribution, retained limits and analyzed usage in; private empty tables with correct allocator identity. |
| invariants | No vector capacity is retained in default interpreted Data; this constructor is reached only in explicit/reconstructed prepared mode. |
| ownership | Vectors retain account/attribution; object/control allocation is separately receiver-funded. |
| failure | Allocator/control admission failures unwind through make_accounted_shared. |
| cost | Fixed initialization; capacity growth occurs in build. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0013

[Lines 84–109](../../../../../src/ir/input_program.hpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L84-L109:sha256:13764f4b4614e9ed921c291353d5bbeed1793e3f1f70d931255b68194ccc6675
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count and validate the finite executable adapter instructions before allocating tables. |
| inputs / outputs | Optional normalized metadata, actual executable port count, limits and borrowed grant; returns analyzed usage. |
| invariants | Visits actual ports only: constant SQL may retain dormant source adapters while executable ports are zero. Nonzero ports must match adapters. Every instruction checks capacity before increment; column occurrence and operation/argument bounds are validated. Argument visits and named reads consume logical work. |
| ownership | Borrows immutable source; owns only a local scalar usage record. |
| failure | Logical/native work, instruction capacity, expression bounds/variant and operation contract errors propagate; no prepared vector is allocated by analyze. |
| cost | Linear in visited ports/instructions/argument IDs; finite work can stop early. The caller may already own an unpublished base copy. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0014

[Lines 110–141](../../../../../src/ir/input_program.hpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L110-L141:sha256:721e5ed6f5ff3f0775dc1f5c5db272fb2da049abc385f5a437509211616cd89f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct and publish a flat receiver-owned prepared input data program. |
| inputs / outputs | Receiver account/tag, completed normalized result, actual port count, finite limits, analyzed usage and borrowed native grant. |
| invariants | Fixed PreparedInputs object slots and table sizes are preadmitted. reserve uses analyzed counts; actual port/program writes consume logical steps. Operation spans bind to result metadata. Capacity-byte products/sum are checked; metadata_bytes reports actual table capacities, excluding owner/control/base copy. |
| ownership | Accounted owner owns two vectors; source argument spans remain valid through enclosing immutable Data. Result pointer becomes const at publication. |
| failure | Work/cap/overflow/resource/allocation/variant failures unwind unreturned owner and tables; no hidden grant refill or instruction callback enters. |
| cost | One control/object, two reserves and linear port/instruction writes; no per-expression heap node or JIT. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0015

[Lines 142–148](../../../../../src/ir/input_program.hpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L142-L148:sha256:3f600a9a7ab7976b2166917f7d1700f1266a8a1dce388861b1cac014f32aa40e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute one contiguous prepared adapter with interpreter-equivalent step admission. |
| inputs / outputs | Occurrence port, borrowed physical row, scratch optional-value span and borrowed native allowance. |
| invariants | Port range is bounds checked. Each instruction admits one structural step before invoking its fixed worker; worker bounds/scalar behavior match interpreter. Ranges are immutable trusted build output. |
| ownership | Only scratch cells change; program/instructions/arguments remain immutable. |
| failure | Work/contract/scalar failure stops before publishing adapted tuple, with normal consumed-work semantics. |
| cost | Linear instruction visits; one function pointer call each, no expression variant lookup or timing hook. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0016

[Lines 149–149](../../../../../src/ir/input_program.hpp#L149); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L149-L149:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private prepared owner definition. |
| inputs / outputs | Type-scope closing syntax only. |
| invariants | Does not add an executable branch or authority. |
| ownership | Member destructors release accounted capacities when last owner dies. |
| failure | No standalone failure. |
| cost | No independent runtime operation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0017

[Lines 150–153](../../../../../src/ir/input_program.hpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L150-L153:sha256:efcb78140653521ded5afe6e53a1a7c1beadca7cb307dd9b6cc89ca288534fc9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the cold base-copy work usage from a monotone borrowed grant. |
| inputs / outputs | Before/after IndexWork values in; five coordinate-wise consumed amounts out. |
| invariants | Caller captures one unrefilled allowance before and after base clone; after never exceeds before. This helper does not validate arbitrary caller counters. |
| ownership | Returns plain values; no allowance ownership or mutation. |
| failure | No allocation or checked exception; monotonicity is an internal precondition. |
| cost | Five unsigned subtractions, constant time. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0018

[Lines 154–154](../../../../../src/ir/input_program.hpp#L154); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L154-L154:sha256:3478c5a7c7f151f90c7b373a71777f82ab7320e1bd4a4cb36cfa14052c00b57c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private helper namespace. |
| inputs / outputs | Scope syntax only. |
| invariants | No exported bytecode/callback format is introduced. |
| ownership | No storage owned. |
| failure | No failure. |
| cost | No runtime work. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |
