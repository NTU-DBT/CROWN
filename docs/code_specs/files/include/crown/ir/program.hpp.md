# `include/crown/ir/program.hpp` — block usage map

[Source](../../../../../../include/crown/ir/program.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs.

Snapshot SHA-256: `fc55f3ca55753d435c04a438afb934e5680905749c1e6023df5dfb2fb93eb1a8`. 148 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_identity.md](../../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/ir/program.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../../include/crown/ir/program.hpp#L13) | Type/record definition: enum class InputExecution |  · [reviewed contract](#b0002) |
| [B0003 · 14–17](../../../../../../include/crown/ir/program.hpp#L14) | Type/record definition: struct InputPreparationLimits |  · [reviewed contract](#b0003) |
| [B0004 · 18–25](../../../../../../include/crown/ir/program.hpp#L18) | Type/record definition: struct InputPreparationUsage | source comment (unverified): // Only allocated instruction/range table capacity; excludes Data/control · [reviewed contract](#b0004) |
| [B0005 · 26–30](../../../../../../include/crown/ir/program.hpp#L26) | Type/record definition: struct ReplanLimits |  · [reviewed contract](#b0005) |
| [B0006 · 31–31](../../../../../../include/crown/ir/program.hpp#L31) | Type/record definition: enum class ReplanFault |  · [reviewed contract](#b0006) |
| [B0007 · 32–38](../../../../../../include/crown/ir/program.hpp#L32) | Type/record definition: class ReplanFailure final:public std::exception | returns value_; @ · [reviewed contract](#b0007) |
| [B0008 · 39–74](../../../../../../include/crown/ir/program.hpp#L39) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Immutable executable metadata: admission owns copied payload and tokens. · [reviewed contract](#b0008) |
| [B0009 · 75–78](../../../../../../include/crown/ir/program.hpp#L75) | declares values/defaults or compile-time conditions. | source comment (unverified): // An explicitly supplied compiler basis is immutable input. New graph and · [reviewed contract](#b0009) |
| [B0010 · 79–79](../../../../../../include/crown/ir/program.hpp#L79) | Callable definition: \[\[nodiscard\]\] explicit operator bool() const noexcept | calls ; returns bool(data_) · [reviewed contract](#b0010) |
| [B0011 · 80–115](../../../../../../include/crown/ir/program.hpp#L80) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Aliases the existing accounted program control; creates no mirror/control. · [reviewed contract](#b0011) |
| [B0012 · 116–143](../../../../../../include/crown/ir/program.hpp#L116) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0012) |
| [B0013 · 144–144](../../../../../../include/crown/ir/program.hpp#L144) | Callable definition: explicit CompiledProgram(std::shared_ptr&lt;const Data&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0013) |
| [B0014 · 145–148](../../../../../../include/crown/ir/program.hpp#L145) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown · [reviewed contract](#b0014) |

## B0001

[Lines 1–12](../../../../../../include/crown/ir/program.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once #include "crown/ir/program_model.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the private bridge name before granting it access to CompiledProgram. |
| inputs / outputs | A forward declaration in \`crown::runtime::detail\` makes the narrow source-only friend name available. |
| invariants | This adds no public factory or source descriptor; ordinary public freeze keeps its existing signature. |
| ownership | The bridge type has no ownership by this declaration. |
| failure | Name/namespace errors fail compilation. |
| cost | No runtime cost. |
| Design | [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [src/runtime/sql_cold_rebuild.hpp](../../../../../../src/runtime/sql_cold_rebuild.hpp) |

```text
@source-span:L1-L12:sha256:3773f3501c98a280837583df6242fa4b12803334094a9d29e5754e5edbcb2681
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the public admitted-program and finite input-preparation dependencies. |
| inputs / outputs | Header guards, program model, receiving storage binding, IndexWork types and private native-lowering forward declarations. |
| invariants | Including this header does not opt a query into threaded execution or change physical/source identity. |
| ownership | Declarations own no runtime state; concrete program handles retain immutable Data. |
| failure | No runtime failure at inclusion; type/link errors remain compiler diagnostics. |
| cost | Compile-time dependencies only; interpreted Data adds one nullable prepared owner. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../../include/crown/storage/index_work.hpp) |

## B0002

[Lines 13–13](../../../../../../include/crown/ir/program.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L13:sha256:c9e8b48c01561ea0d4568ea2698ab21c887e38bf0e54d2a0f4f6dda22f733b78
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the two versioned input-expression execution policies. |
| inputs / outputs | interpreted_v1 or threaded_v1; getters expose the actual admitted policy. |
| invariants | This policy is separate from a physical-tree/source hash and is not a caller instruction format. |
| ownership | Small value enum; prepared instruction ownership lives in private program Data. |
| failure | The enum grants no admission authority or allocation. |
| cost | Constant-size value copying. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/sql_support.md](../../../../../sql_support.md), [docs/scalars.md](../../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../../src/frontend/sql_scalar.hpp) |

## B0003

[Lines 14–17](../../../../../../include/crown/ir/program.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L17:sha256:e80800929a69689b1fd8951c64edafec677df77055c02215896e67934d1535b6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound one cold preparation of normalized SQL occurrence adapters. |
| inputs / outputs | Logical work cap and total executable instruction cap; defaults are one million and one hundred thousand. |
| invariants | Zero denies nonempty preparation; limits do not replenish a native receiving allowance or bound wall time. |
| ownership | Caller-owned value copied into the immutable prepared owner for later freeze/replan reconstruction. |
| failure | Preparation reports storage_work_limit or storage_capacity when the named checkpoint/cap is exhausted. |
| cost | Fixed-size limits; bounded work checks precede each logical checkpoint and instruction-count increment. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../../include/crown/storage/index_work.hpp) |

## B0004

[Lines 18–25](../../../../../../include/crown/ir/program.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L25:sha256:c9a605765a66a4bc17c4b68e6e97beb64d79fc5237e3e6d3c022cdc9e5182471
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report preparation checkpoints and extra table capacity with distinct base-copy cost. |
| inputs / outputs | work, executable instruction count, allocated instruction/range capacity bytes and five-domain base_freeze_work. |
| invariants | metadata_bytes excludes Data/control blocks and base copied metadata; all real allocations still use the account. Work is logical, not nanoseconds. Replan has no base copy and reports zero base_freeze_work. |
| ownership | Returned usage is a value snapshot; it lends no access to mutable instruction buffers. |
| failure | The record itself cannot fail; an absent prepared owner yields zero usage. |
| cost | Constant-size reporting; full query-account statistics supply the broader allocation scope. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../../include/crown/storage/index_work.hpp) |

## B0005

[Lines 26–30](../../../../../../include/crown/ir/program.hpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReplanLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound fresh native lowering and inherited compiler credits independently. |
| inputs / outputs | PhysicalLimits plus optional binding-replay and normalization work caps; the latter default to one million. |
| invariants | Absent caps mean unbounded in that dimension; physical lowering and identity caps are intersected with producer options, while existing binding/normalization counters are compared directly. |
| ownership | Value-owned scalar/options configuration; no account or proof ownership. |
| failure | Exceeded dimensions become distinct ReplanFailure faults; the stored numbers do not themselves validate source or candidate. |
| cost | Fixed-size option copying; caps are logical units rather than a bound on every byte scan or elapsed time. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../../selection_accounting.md) |

## B0006

[Lines 31–31](../../../../../../include/crown/ir/program.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ReplanFault {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish native candidate/source mismatch from each delegated logical limit. |
| inputs / outputs | binding, lowering_work, identity_work, binding_replay_work, normalization_work tags. |
| invariants | These tags do not subsume storage contract/overflow/work faults or MemoryFailure propagated from funded construction. |
| ownership | Plain enum value owned by the exception. |
| failure | No operation or allocation in the enum definition. |
| cost | Fixed tag representation. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../../selection_accounting.md) |

## B0007

[Lines 32–38](../../../../../../include/crown/ir/program.hpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ReplanFailure final:public std::exception {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a fixed native replan rejection without building diagnostic text. |
| inputs / outputs | One ReplanFault; fault() exposes its specific reason and what() exposes a shared literal. |
| invariants | The exception reports construction failure, not a partial executable program or a failure of the candidate proof. |
| ownership | Stores only its tag; what() does not own or retain a source/candidate. |
| failure | Its declared operations are noexcept; the C++ exception runtime is outside query allocation accounting. |
| cost | Fixed member work for construction/access; throwing still entails exception-runtime work. |
| Design | [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
explicit ReplanFailure(ReplanFault value) noexcept:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture the exact native lowering rejection tag. |
| inputs / outputs | Input fault value becomes value_; no normalization or formatting. |
| invariants | All declared fault tags are preserved. |
| ownership | Owns the copied enum only. |
| failure | Noexcept. |
| cost | Fixed scalar assignment. |
| Design | [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] ReplanFault fault() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the retained native lowering fault. |
| inputs / outputs | Returns the stored ReplanFault by value. |
| invariants | Reading the fault does not retry or consume any work. |
| ownership | Does not expose a borrowed program. |
| failure | Noexcept. |
| cost | Fixed scalar read. |
| Design | [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const char* what() const noexcept override
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide stable generic presentation for native replan failure. |
| inputs / outputs | Returns the literal native candidate lowering failed. |
| invariants | Detailed cause remains in fault(), not generated text. |
| ownership | Pointer has static lifetime. |
| failure | Noexcept. |
| cost | Fixed pointer return; no formatting. |
| Design | [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0008

[Lines 39–74](../../../../../../include/crown/ir/program.hpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class CompiledProgram {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own immutable executable metadata and retain the source backing any borrowed native views. |
| inputs / outputs | Empty default handle or shared const Data; explicit factories admit or construct a complete program. |
| invariants | Freeze copies retained payload/tokens into the receiver. Replan retains canonical admitted source fields and constructs fresh executable metadata; for nonempty contradiction its tree/report describe the empty operator, while the original candidate/proof remains unchanged. Validation reports and guarantee labels do not confer independently replayed optimality. |
| ownership | Implicit copy shares the accounted control; implicit move transfers it and empties the source. Assignment can release the old destination; last release destroys the arena and possibly the canonical source. Borrowed getters require a surviving owner. |
| failure | Default/moved-from handles admit bool() but checked getters throw invalid_storage. Factories publish only completed Data; storage/memory and logical faults propagate. |
| cost | Copy/move construction is shared-handle work; assignment/destruction can release all old graph allocations. No universal constant-time destructor or graph deep-copy cost. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
CompiledProgram() noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty compiled-program handle for later publication. |
| inputs / outputs | No arguments; data_ is an empty shared_ptr. |
| invariants | Presence is false; getters requiring Data are invalid until assigned. |
| ownership | No program/control ownership is established. |
| failure | Noexcept. |
| cost | Fixed empty shared_ptr initialization. |
| Design | [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] static CompiledProgram freeze(const resource::MemoryAccount&,
      const PhysicalPlan&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a compiler DTO program into the receiving query account and shared execution work grant. |
| inputs / outputs | PhysicalPlan and account are borrowed for the synchronous call; returns an independent native graph. |
| invariants | Execution admission enforces indexed operation-grant requirements; compiler identity/validation are copied, not replayed. |
| ownership | All retained text, arrays and canonical layout/projection metadata belong to the receiver; no DTO owner is retained. |
| failure | Memory, storage-work, contract and overflow faults propagate without publishing a result. |
| cost | Traverses all retained model/identity/instruction payload and descriptor metadata; projection memo scans and source-table searches can be quadratic. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../../selection_accounting.md) |

```text
[[nodiscard]] static CompiledProgram freeze(const resource::MemoryAccount&,
      const CompiledProgram&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-admit an existing native compiler/cache program into the receiving runtime account. |
| inputs / outputs | Borrowed native source and optional shared execution work grant; returns a new native graph. |
| invariants | Clones binding tokens into the receiver and remaps nested descriptors; no legacy DTO export or fresh proof validation. |
| ownership | Source may close after success; new graph owns copied source/JSON/SQL metadata and receiving-account tokens. |
| failure | Empty source, memory/overflow, descriptor contract or work failures abort construction. |
| cost | Copies retained bytes and arrays; binding/projection alias recovery can scan earlier indexes quadratically. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../../selection_accounting.md) |

```text
[[nodiscard]] static CompiledProgram standalone(const PhysicalPlan&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an initial compiler artifact with its own maximum-capacity component account. |
| inputs / outputs | Borrowed PhysicalPlan; returns native immutable program. |
| invariants | This compiler boundary precedes runtime admission; later execution still requires freeze into the query account. |
| ownership | Artifact retains its new account and all compiler payload. |
| failure | Account/control or metadata construction may fail; no execution instance is created. |
| cost | Full compile/admission work; UINT64_MAX is a byte cap, not a constant resource or time promise. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../../selection_accounting.md) |

```text
[[nodiscard]] static CompiledProgram compile(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile an already lowered compiler plan into supplied-account native metadata. |
| inputs / outputs | Account and PhysicalPlan; complete immutable artifact is returned. |
| invariants | Uses compiler metadata counters instead of execution operation cap; it does not rerun tree checking or establish an optimum. |
| ownership | Fresh graph and canonical descriptors are funded in the supplied component account. |
| failure | Storage/memory/overflow failures propagate; failed partial graph remains private and is released. |
| cost | Full model/identity/metadata copying and token remapping with container/descriptor allocation costs. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../../selection_accounting.md) |

```text
[[nodiscard]] static CompiledProgram replan(const CompiledProgram&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a typed checked candidate under the basis program account. |
| inputs / outputs | Borrowed basis and MinimumHeightCandidate plus optional limits; returns a fresh program. |
| invariants | Exact catalog/query binding and typed candidate valid/native-height consistency are checked before source-credit admission and operator construction. Nonempty contradiction uses the canonical empty operator tree and valid zero-height/depth report, preserving original candidate/proof; ordinary and empty-body inputs retain candidate tree/report. No independent optimum replay occurs. |
| ownership | Keeps canonical admitted source alive and allocates fresh graph/scratch in basis.account(). |
| failure | Binding/logical limits, storage faults or memory failure propagate without replacing the caller basis. |
| cost | Full binding encodes, metadata freezes, tree/instruction construction and physical digest scans; reused producer credits do not imply zero fresh work. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md), [docs/selection_accounting.md §Delegated budget equation](../../../../../selection_accounting.md) |

```text
@source-span:L60-L69:sha256:39891ebb56d395acdd6892f2dd036336c2010dd184fb9babadb88b64f163d7e1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose opt-in, automatic SQL input preparation and actual execution diagnostics. |
| inputs / outputs | Genuine CompiledProgram, receiving account, finite logical limits and optional borrowed IndexWork allowance in; independently owned prepared CompiledProgram out. |
| invariants | Source must be normalized SQL. No caller code/instructions are accepted. Physical/source hashes remain unchanged. Indexed admission requires the original fixed capped allowance before any consumption. Actual mode and stable key describe the admitted program. |
| ownership | The new program owns copied normalized payload and prepared argument views in its receiving account; source and caller allowance remain borrowed. |
| failure | Invalid source/SQL requirement, allowance contract, logical cap, account limit, overflow and allocation failures propagate; unpublished metadata is released, consumed work/peak are not refunded. |
| cost | Cold base metadata copy plus adapter analysis/table construction; interpreter default needs no instruction vectors. No global cache or per-query machine code. |
| Design | [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/sql_support.md](../../../../../sql_support.md), [docs/scalars.md](../../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../../include/crown/storage/index_work.hpp) |

```text
@source-span:L70-L70:sha256:922e6b22f26d46c5bf6a8fd82423a5548b542a1ada8cbde785d1471677741e57
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the retained input preparation resource policy for cold exact cache/source binding. |
| inputs / outputs | Valid immutable program in; optional copied InputPreparationLimits out, absent for interpreter. |
| invariants | Returns actual stored finite limits rather than observed usage/base-freeze counters. This lets cache/admission consumers distinguish execution policy while preserving ordinary physical/source hashes and interpreted encoding. |
| ownership | Returns plain value fields; no instruction view, mutable diagnostics handle or allocation escapes. |
| failure | Empty compiled handle raises existing invalid_storage; otherwise no allocation or denial. |
| cost | Constant-time optional scalar copy in cold consumers; no runtime update hook. |
| Design | [docs/selection_binding.md](../../../../../selection_binding.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0009

[Lines 75–78](../../../../../../include/crown/ir/program.hpp#L75); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] static CompiledProgram replan_into(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a candidate graph in an explicitly supplied receiving account. |
| inputs / outputs | Receiver account, immutable basis, checked candidate and limits; returns a new program. |
| invariants | Exact catalog/query binding and typed candidate valid/native-height consistency are checked before source-credit admission and operator construction. Nonempty contradiction uses the canonical empty operator tree and valid zero-height/depth report, preserving original candidate/proof; ordinary and empty-body inputs retain candidate tree/report. No independent optimum replay occurs. |
| ownership | Receiver funds new graph, descriptors and construction scratch; retained canonical source keeps its original funded owner. |
| failure | Invalid account/basis/candidate or binding/limit/memory/storage failure prevents publication. |
| cost | Same synchronous metadata and byte scans as replan; no cancellation, depth or elapsed-time continuation is provided. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md), [docs/selection_accounting.md §Delegated budget equation](../../../../../selection_accounting.md) |

## B0010

[Lines 79–79](../../../../../../include/crown/ir/program.hpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] explicit operator bool() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether a compiled-program handle currently owns Data. |
| inputs / outputs | Returns bool(data_). |
| invariants | True means presence, not a fresh proof or runtime initialization. |
| ownership | Does not extend Data lifetime or traverse it. |
| failure | Noexcept, including empty or moved-from handles. |
| cost | Fixed shared-pointer observation. |
| Design | [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0011

[Lines 80–115](../../../../../../include/crown/ir/program.hpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const resource::MemoryAccount& account() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed account view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the receiver account for this program’s fresh allocations; corresponding rvalue reference accessor is deleted. |
| invariants | Does not imply a retained supplied canonical source used this same account. |
| ownership | The returned account reference borrows Data. Explicitly copying MemoryAccount retains its controller/cap, not the program metadata or source-view lifetime. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const program::Catalog& catalog() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed catalog view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the core catalog consumed by physical instructions; corresponding rvalue reference accessor is deleted. |
| invariants | Normalized original physical catalog is exposed by source_catalog(), separately. |
| ownership | Catalog/table/name/constraint/statistics views borrow Data or its retained canonical basis. Copying program::Catalog copies those views and does not acquire an owner. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const program::Query& query() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed query view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the retained original core occurrence/head model including contradiction metadata; corresponding rvalue reference accessor is deleted. |
| invariants | Does not canonicalize a contradictory nonempty body to an empty structural query. |
| ownership | Variable/atom/term/head arrays and string constants borrow Data or retained basis. A copied program::Query header does not retain them. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const program::FreeConnexTree& tree() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the executable operator tree while retaining original structural authority separately. |
| inputs / outputs | Lvalue accessor returns the executable tree by const reference; the rvalue reference overload is deleted. |
| invariants | For nonempty contradiction replans this is the canonical empty executable operator tree, while query() retains original atoms/head and the supplied candidate keeps its original structural tree/proof. Ordinary and empty-body replans preserve the candidate raw tree, including optional claims. The view alone establishes no independently replayed optimum. |
| ownership | Node/ID/scope/child/claim views borrow Data; its empty constant operator has no node payload. A copied tree header is not an owner of a nonempty tree. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const std::optional<program::NormalizedSql>& normalized() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed normalized view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the optional admitted SQL binding, constants and compiled adapter metadata; corresponding rvalue reference accessor is deleted. |
| invariants | Absence distinguishes direct CQ input; access does not rerun parsing or normalization. |
| ownership | All nested SQL source/catalog/expression/adapter/output views borrow Data or retained basis. Copying this optional native program does not retain those backing owners. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const program::ValidationReport& validation() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained validation report for executable operator metadata. |
| inputs / outputs | Lvalue accessor returns the executable validation report; the rvalue reference overload is deleted. |
| invariants | Nonempty contradiction replans expose a fresh valid operator report with native height and edge depth zero and empty connex/separator/violation arrays; this does not replace the original candidate validation or proof. Other routes retain the admitted compiler/candidate report. Observing a report creates no checked capability. |
| ownership | Diagnostic text, connex and separator views borrow Data; scalar validity/heights are values. Copying the native report does not retain its arrays or establish proof authority. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const program::QueryIdentity& identity() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed identity view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the retained semantic/output/cost/cache identity and permutations; corresponding rvalue reference accessor is deleted. |
| invariants | Producer work is retained credit; reading it does not regenerate canonical JSON or hashes. |
| ownership | Canonical JsonView, digests and ID-order spans borrow Data or retained basis. Neither copied identity header nor JsonView acquires a source owner. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const program::PhysicalOptions& options() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed options view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the retained policy, producer limits and indexed-backend configuration; corresponding rvalue reference accessor is deleted. |
| invariants | Replan host-limit intersections are local construction state and do not rewrite these producer options. |
| ownership | Policy label views borrow Data or retained basis; limits/backend spec are inline values. Copying native options does not own the policy text. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../../selection_accounting.md) |

```text
[[nodiscard]] const program::GuaranteeProfile& guarantee() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed guarantee view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the stored execution/height/backend/accounting profile labels; corresponding rvalue reference accessor is deleted. |
| invariants | Labels do not grant independently checked optimum, completed runtime initialization or measured performance. |
| ownership | Profile labels and string inventories borrow Data or retained basis. Copying the native profile does not retain the backing label bytes. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../../selection_accounting.md) |

```text
[[nodiscard]] const program::Span<storage::AccountedLayout>& layouts() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed layouts view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the primary canonical layout inventory for the storage binding; corresponding rvalue reference accessor is deleted. |
| invariants | Auxiliary SQL-result/unused-source descriptors are exposed through their dedicated accessors. |
| ownership | The inventory span borrows Data/binding ownership. Each explicitly copied AccountedLayout retains only its own descriptor control and can outlive the inventory. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const program::Span<program::PhysicalRelation>& relations() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed relations view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the active physical-base and internal relation instructions; corresponding rvalue reference accessor is deleted. |
| invariants | These immutable bindings do not contain mutable runtime table contents. |
| ownership | The relation array borrows Data. Copied PhysicalRelation values retain their layout controls and inline coordinates, not the array owner. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const program::Span<program::IndexRequirement>& indexes() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed indexes view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the shared canonical projection requirements and use labels; corresponding rvalue reference accessor is deleted. |
| invariants | Requirements are not registrations of mutable runtime indexes. |
| ownership | Requirement/use arrays borrow Data. Copying an AccountedProjection retains its endpoints/control, while a copied requirement still borrows its uses span. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const program::Span<program::PhysicalInput>& inputs() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed inputs view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the occurrence routes, layout/projection tokens and core guard instructions; corresponding rvalue reference accessor is deleted. |
| invariants | Adapt_input() executes these separately; reading does not validate any row. Constant routes expose an empty instruction collection even when query().atoms is nonempty. |
| ownership | The input array and guard spans/text borrow Data or retained basis. Copied layout/projection handles retain descriptor controls, not the guard arrays. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const program::Span<program::Span<OccurrenceId>>& base_routes() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed base_routes view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the source-table to occurrence fanout arrays; corresponding rvalue reference accessor is deleted. |
| invariants | On tree routes these arrays map each physical source table to its routed logical occurrences. Constant routes retain empty route entries even when the original contradiction-marked Query has atoms; this is not a live subscription list. |
| ownership | Both the outer route array and inner occurrence spans borrow Data. Copying either span/header acquires no program/source ownership. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] PhysicalRoute route() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read executable route without borrowing a field reference. |
| inputs / outputs | Returns tree, constant_true or constant_false. |
| invariants | Route is execution metadata; it does not establish original structural minimum height. |
| ownership | Returned enum is independent of program lifetime. |
| failure | Empty handle throws invalid_storage. |
| cost | Checked scalar lookup. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const program::Catalog& source_catalog() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the complete physical source catalog from an lvalue program. |
| inputs / outputs | Normalized input exposes original binding.catalog; direct CQ exposes core catalog. Rvalue reference overload is deleted. |
| invariants | Source table IDs are the base-event namespace, not necessarily normalized core table IDs. |
| ownership | Caller must keep a program owner; source_catalog_owner() is the explicit owning alternative. |
| failure | Empty lvalue throws invalid_storage; temporary reference access fails compilation. |
| cost | Checked branch/member lookup; no table or column scan. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] std::shared_ptr<const program::Catalog> source_catalog_owner() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep physical source catalog views alive through an alias of the existing program owner. |
| inputs / outputs | Returns shared_ptr&lt;const Catalog&gt; into this Data or its retained canonical basis. |
| invariants | Ownership shares existing accounted Data, not a deep catalog copy or a new control block. |
| ownership | Returned alias can outlive the calling handle and retains the complete source lifetime it needs. |
| failure | Empty handle throws invalid_storage. |
| cost | Shared-control aliasing is fixed work; final owner release can pay complete graph teardown. |
| Design | [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] std::string_view physical_sha256() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the physical artifact identity for the selected executable operator. |
| inputs / outputs | Lvalue returns the physical artifact digest view; the temporary view accessor is deleted. |
| invariants | Native replan hashes the selected operator tree with source digest, plan-cache identity and ID-order maps; indexed v2 also includes full physical options. Reference v1 does not directly hash every finite physical option, so full source/options equality is a separate binding check. Hash equality itself grants no proof authority. |
| ownership | Requires a surviving program owner; copied string_view is not an owner. |
| failure | Empty lvalue throws invalid_storage; temporary borrowed access fails compilation. |
| cost | Checked view lookup, independent of hashed source size. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] std::string_view physical_source_sha256() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the original compiler physical-source digest as a borrowed digest view. |
| inputs / outputs | Lvalue returns string_view; rvalue view accessor is deleted. |
| invariants | Replan preserves the canonical admitted source digest while building a fresh candidate physical digest. No hash validation is performed on read. |
| ownership | Requires a surviving program owner; copied string_view is not an owner. |
| failure | Empty lvalue throws invalid_storage; temporary borrowed access fails compilation. |
| cost | Checked view lookup, independent of hashed source size. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0012

[Lines 116–143](../../../../../../include/crown/ir/program.hpp#L116); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const program::EnumerationProgram& enumeration() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed enumeration view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the immutable assignment steps, output slots, equalities and recorded depth; corresponding rvalue reference accessor is deleted. |
| invariants | This is instruction metadata, not a started cursor or materialized answer set. |
| ownership | Step/output/equality arrays borrow Data. A copied parent-key projection can retain its descriptor controls, but not the containing instruction/assignment arrays. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Enumeration and result assembly](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const storage::AccountedLayout& result_layout() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed result_layout view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the core ordered-head result descriptor; corresponding rvalue reference accessor is deleted. |
| invariants | Duplicate output variables keep their tuple equality constraints; SQL wrapper/output layout may differ. |
| ownership | The returned reference needs Data; explicitly copying AccountedLayout retains its own funded descriptor/control and context/fields independently of this program. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Enumeration and result assembly](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const storage::AccountedLayout& sql_result_layout() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed sql_result_layout view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the SQL-visible result descriptor or core result descriptor for direct CQ; corresponding rvalue reference accessor is deleted. |
| invariants | EXISTS uses a single boolean field and normalized outputs preserve their SQL domains. |
| ownership | The reference borrows Data; copying AccountedLayout retains the SQL/core descriptor’s existing funded control, so that descriptor can outlive the program. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const program::Span<program::SourceTable>& sources() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed sources view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the complete source-table relation coordinates and layouts including unused tables; corresponding rvalue reference accessor is deleted. |
| invariants | Auxiliary unused-table coordinates need not be entries in the active storage binding. |
| ownership | The SourceTable array borrows Data. Copying one SourceTable value retains its AccountedLayout control and relation value independently of the containing array. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const program::Span<program::PhysicalNode>& nodes() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed nodes view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the physical node scope, topology, layout/projection and relation-role instructions; corresponding rvalue reference accessor is deleted. |
| invariants | Fields borrow the program arena or retained canonical source; no operator state is materialized. Constant routes expose an empty instruction collection even when query().atoms is nonempty. |
| ownership | Node and child/scope/visible arrays borrow Data or retained basis. Copied descriptors retain their controls, but copying PhysicalNode does not own its nested spans. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] const program::Span<program::PhysicalEdge>& edges() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a stable borrowed edges view from a surviving compiled program. |
| inputs / outputs | Lvalue accessor returns the child-slot and parent-key/reverse-index instructions; corresponding rvalue reference accessor is deleted. |
| invariants | Child slots preserve arbitrary fanout ordering and are not binary-tree positions. Constant routes expose an empty instruction collection even when query().atoms is nonempty. |
| ownership | The edge array borrows Data. A copied PhysicalEdge owns its projection control plus scalar coordinates and can outlive that array. |
| failure | Empty lvalue handle throws invalid_storage; direct temporary reference access is rejected at compile time. |
| cost | The accessor is a checked member lookup without payload copying; subsequent scans/release are separate costs. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] storage::AccountedLayout scope_layout(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request a receiver-funded descriptor for caller-selected ordered variables and binding suffix. |
| inputs / outputs | LayoutId, variable span, suffix and optional allowance produce an owning AccountedLayout. |
| invariants | Does not register the caller ID in the immutable program; ordered/repeated variable positions are retained. |
| ownership | Result descriptor owns its accounted metadata and can outlive this program. |
| failure | Bad/empty input, memory, overflow, work or descriptor-contract failures propagate. |
| cost | Variable scan plus field and binding-byte construction; not an existing-token lookup. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] std::uint64_t work() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose this program’s physical-lowering counter for delegated accounting. |
| inputs / outputs | Returns retained or freshly counted uint64 work. |
| invariants | Does not add identity/binding/normalization credits or claim every byte/comparison was counted. |
| ownership | Value return needs no retained view. |
| failure | Empty handle throws invalid_storage. |
| cost | Checked scalar lookup. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../../selection_accounting.md) |

```text
[[nodiscard]] storage::AccountedPlanStorage make_storage(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a new mutable storage instance from this program’s canonical binding. |
| inputs / outputs | Optional shared execution allowance; returns empty relation tables with required indexes. |
| invariants | Metadata sharing does not create a new allowance or populated execution epoch. |
| ownership | Mutable tables use program account; immutable descriptors retain the existing funded controls. |
| failure | Empty program, indexed admission contract, work/memory/owner failures propagate. |
| cost | Relation/index construction and registration costs plus funded arrays, not constant-time binding access. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
[[nodiscard]] std::optional<storage::AccountedTuple> adapt_input(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt one physical event row using this program’s compiled occurrence instructions. |
| inputs / outputs | Borrowed source row, occurrence and optional shared allowance; yields owning AccountedTuple or filtered nullopt. |
| invariants | Executes normalized SQL guards/program before core guards and native projection; it does not traverse a SQL AST or publish a runtime update. A constant route has no executable input occurrences; direct calls with retained original occurrence IDs therefore reject instead of adapting a row. |
| ownership | Scratch and tuple payload are funded; successful tuple retains its own copied payload and descriptor controls. |
| failure | Layout/type/ID, work, memory and metadata faults propagate; filter mismatch is ordinary nullopt. |
| cost | Row width, expression/argument/guard visits and compared/copied byte widths determine work and allocations. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
const program::Span<program::Span<OccurrenceId>>& base_routes() const &&=delete; [[nodiscard]] const program::Span<program::PhysicalNode>& nodes() const &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the cold metadata-mode helper private to CompiledProgram and its closed bridge. |
| inputs / outputs | \`freeze_impl\` takes a real PhysicalPlan, caller grant and explicit MetadataWork mode; the friend is SqlColdRebuild only. |
| invariants | Public \`freeze\` remains the execution-mode path; the private helper cannot import fabricated descriptors or alter plan identity. |
| ownership | Returned CompiledProgram owns receiver-accounted metadata through the existing builder. |
| failure | Freeze/binding/work/allocation errors unwind the unpublished CompiledProgram. |
| cost | Compiler metadata admission and builder costs remain the existing measured work; no hot record is added. |
| Design | [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
@source-span:L139-L141:sha256:ac321fe270cb6b3c9c66e6f6f969207acec9118074fb050ed0d2be53308d3340
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep receiving-copy and optional prepared-program construction behind one private boundary. |
| inputs / outputs | Receiving account, immutable source, borrowed work pointer, optional preparation limits; private result is published only on success. |
| invariants | A missing limits value preserves interpreter behavior; existing prepared source limits are passed explicitly by freeze. This declaration does not bypass clone_binding cap validation. |
| ownership | Factory allocates new Data/control/arrays in receiver; prepared views point into that new Data. |
| failure | Direct existing storage/resource exceptions; no retry/refill or partial program publication. |
| cost | Cold copy/build path; no event-loop or scalar timestamp hook. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../../include/crown/storage/index_work.hpp) |

## B0013

[Lines 144–144](../../../../../../include/crown/ir/program.hpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit CompiledProgram(std::shared_ptr<const Data> data) noexcept:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish an already completed immutable program control. |
| inputs / outputs | Consumes the shared_ptr parameter into data_; used by trusted Builder/NativeLowering friends. |
| invariants | This constructor performs no validation; callers must finish graph construction before returning it publicly. |
| ownership | Transfers one strong owner without copying graph bytes; parameter acquisition may already have copied a caller handle. |
| failure | Noexcept. |
| cost | Fixed pointer transfer; no release of an existing destination object. |
| Design | [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

## B0014

[Lines 145–148](../../../../../../include/crown/ir/program.hpp#L145); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] const Data& data() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Centralize checked access to the immutable control behind public getters. |
| inputs / outputs | Returns a Data reference or rejects an empty handle. |
| invariants | All nonpresence getters use this guard directly or through another checked accessor. |
| ownership | Reference borrows data_; shared_ptr field retains the graph until the last owner. |
| failure | IndexFailure invalid_storage for default or moved-from handles. |
| cost | One presence test and pointer dereference. |
| Design | [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |

```text
std::shared_ptr<const Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the accounted immutable arena and any canonical source used by its views. |
| inputs / outputs | Single const-Data shared owner; empty denotes no program. |
| invariants | No mutable runtime tables or candidate-proof capability are stored in this public handle. |
| ownership | Copy aliases the native accounted Data control; last-owner release invokes Data destruction and descriptor/member release. |
| failure | Shared-owner lifecycle is nonthrowing; construction errors happen before publication. |
| cost | Handle copies do not clone metadata; final release scales with constructed arena elements and retained source/descriptors. |
| Design | [docs/query_memory.md §Boundaries](../../../../../query_memory.md) |
