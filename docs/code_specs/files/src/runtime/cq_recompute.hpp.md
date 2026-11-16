# `src/runtime/cq_recompute.hpp` — block usage map

[Source](../../../../../src/runtime/cq_recompute.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Share original-account native query freezing and iterative witness traversal with borrowed callbacks and caller-selected consolidation.

Snapshot SHA-256: `57d39d4e3646100deaa74533659db434e17213d7d5284d1f0f99512bfc0560aa`. 167 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [cq_recompute](../../../subsystem_contracts.md#cq_recompute). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/fallback.md](../../../../fallback.md), [docs/difference.md](../../../../difference.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md](../../../../../Refactor.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/runtime/cq_recompute.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 11–14](../../../../../src/runtime/cq_recompute.hpp#L11) | Callable definition: template&lt;class T&gt; auto allocator(const resource::MemoryAccount& account, resource::MemoryPurpose purpose = resource::MemoryPurpos… | calls ; returns resource::MemoryAllocator&lt;T&gt;(account, purpose, memory) · [reviewed contract](#b0002) |
| [B0003 · 15–18](../../../../../src/runtime/cq_recompute.hpp#L15) | Callable definition: inline LayoutId output_id(const CompiledProgram& source, const char* code) | calls layouts, size, Error; returns LayoutId{source.layouts().size() + 1} · [reviewed contract](#b0003) |
| [B0004 · 19–32](../../../../../src/runtime/cq_recompute.hpp#L19) | declares types or opens a type body. | source comment (unverified): // Native immutable original-query storage shared by the conservative engines. · [reviewed contract](#b0004) |
| [B0005 · 33–105](../../../../../src/runtime/cq_recompute.hpp#L33) | Callable definition: template&lt;class Budget&gt; FrozenQuery(const CompiledProgram& source, const ::crown::Query& original, std::optional&lt;LayoutId&gt; output,… | calls text, account, variables, constants; returns std::string_view{}; std::string_view(text.data() + offset, value.size()); growth copy_of, insert, push_back, reserve, resize; 8 loop sites · [reviewed contract](#b0005) |
| [B0006 · 106–114](../../../../../src/runtime/cq_recompute.hpp#L106) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // One callback for EVERY complete physical-row choice, before DISTINCT/count · [reviewed contract](#b0006) |
| [B0007 · 115–166](../../../../../src/runtime/cq_recompute.hpp#L115) | Callable definition: template&lt;class Budget, class Emit&gt; void visit(const program::Query& query, const physical::SourceImage& image, const resource::Me… | calls take, size, assignment, trail; returns emit(storage::RowView::borrow(projected)); growth push_back, reserve; 4 loop sites; source comment (unverified): // One callback for EVERY complete physical-row choice, before DISTINCT/count · [reviewed contract](#b0007) |
| [B0008 · 167–167](../../../../../src/runtime/cq_recompute.hpp#L167) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::cq_recompute · [reviewed contract](#b0008) |

## B0001

[Lines 1–10](../../../../../src/runtime/cq_recompute.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:bc5f22de2f0b6d34f6c8f34d2fd21756382978b396e1d22f44ebb2138a529734
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare a narrow private common CQ metadata/traversal implementation. |
| inputs / outputs | Includes charged SourceImage/Error definitions and defines original-account Vector/attribution aliases. |
| invariants | This is an internal positive-CQ primitive; callers choose DISTINCT or witness counting and own publication. |
| ownership | No source runtime, ordinary catalog mirror or callback wrapper is owned by the aliases. |
| failure | No executable evaluation/admission occurs at inclusion. |
| cost | Compile-time dependencies only; future container capacities are actually funded. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp) |

## B0002

[Lines 11–14](../../../../../src/runtime/cq_recompute.hpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L14:sha256:1397841814c21e90a3e38d5fe8863de615cb35416d00238072f90b8d7bba43c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an account-bound typed allocator for common scratch or immutable metadata. |
| inputs / outputs | MemoryAccount and selected MemoryPurpose produce MemoryAllocator&lt;T&gt;. |
| invariants | Attribution remains support_node/0 on the original source account. |
| ownership | Returned allocator shares account authority without allocating an element or minting budget. |
| failure | Invalid memory contract rejects through existing resource APIs. |
| cost | Fixed allocator-handle bookkeeping; allocations/deallocations retain actual allocator costs. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp) |

## B0003

[Lines 15–18](../../../../../src/runtime/cq_recompute.hpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L18:sha256:3047c4633ecc20887a5d68132de994a87068edd56ca4124a85cf34511537ec91
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the next private headed output layout identity without wrapping. |
| inputs / outputs | CompiledProgram and caller-specific diagnostic code produce LayoutId{layouts.size()+1}. |
| invariants | A caller creates at most its own requested layout; difference RHS requests no layout. |
| ownership | Returned scalar ID retains no layout, payload or account owner. |
| failure | SIZE_MAX layouts throws caller overflow code before integer addition. |
| cost | Fixed size/check/add work; no catalog scan or layout allocation. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp) |

## B0004

[Lines 19–32](../../../../../src/runtime/cq_recompute.hpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L32:sha256:300367d00aad87996e191afcf55bd9257eed78159b37c90ab31aa96c57293574
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a stable native immutable copy of actual original query semantics. |
| inputs / outputs | FrozenQuery owns text, variable, literal, flat term/atom/head arrays, their Query views and optional output layout. |
| invariants | Fixed reserves keep spans/string views/literal views stable; unrequested layouts remain empty; no source owner is created here. |
| ownership | Every vector/literal/layout is original-account funded; Query views borrow only member-owned storage. |
| failure | Member declarations perform no query validation; callers pass an already validated query/source catalog. |
| cost | Linear metadata/literal storage plus optional headed layout; final owner destruction visits each real allocation. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

## B0005

[Lines 33–105](../../../../../src/runtime/cq_recompute.hpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L105:sha256:063856c3ecfc62213e37954ad780e3a8fa064ae6de50bbc7befc33358003b4dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze all original CQ terms and optionally create its ordered headed native layout. |
| inputs / outputs | Validated original Query/source program, optional fresh output ID, binding label and one caller Budget produce member-owned native metadata. |
| invariants | Checked extent counts precede fixed reserves; constants are copied as exact scalar cells; ignored/repeated terms and output repetition are retained; first variable occurrence chooses DecimalSpec only when making a layout. |
| ownership | Text/spans are stable inside pre-reserved account vectors; literal AccountedRows own payloads; temporary decimal/seen/field arrays retire locally; RHS-only metadata retains no duplicate output ID. |
| failure | Extent/layout overflow uses caller code; work or allocation/domain refusal unwinds all partially constructed metadata before any Runtime publication. |
| cost | Visits all names/terms/head entries and copies actual literal/string/decimal bytes, plus optional O(V+H) layout scratch, native layout checks, actual allocator and cleanup costs; one shared Budget is never refilled per primitive. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp) |

## B0006

[Lines 106–114](../../../../../src/runtime/cq_recompute.hpp#L106); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L114:sha256:c149f2805425946306618252b8c42268f2295e5a8fe6d98cc9c93c52c3788e2a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prevent metadata relocation that would invalidate its internal borrowed views. |
| inputs / outputs | Deleted copying accompanies the following complete-witness callback contract. |
| invariants | FrozenQuery is directly constructed inside immutable Binding Data; callers must not copy its Query spans into an unrelated owner. |
| ownership | A live Binding Data owns metadata throughout traversal; callback RowView is temporary and may not escape without an accounted copy. |
| failure | Copy attempts fail compilation; callback false is permitted only when caller semantics allow early stop. |
| cost | No callback type erasure or per-assignment dispatch allocation; declaration/comments add no runtime work. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp) |

## B0007

[Lines 115–166](../../../../../src/runtime/cq_recompute.hpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L115-L166:sha256:6f637190ca493ffbddded1956d0a8d1542edcce8792307d09cb86da324a81d2d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Traverse every matching complete physical-row choice with iterative atom frames. |
| inputs / outputs | Native query, one owned source image, original account, Budget/metrics and templated emit(RowView)-&gt;bool; emits projected ordered head for each complete witness. |
| invariants | Frame marks restore exactly new variable bindings; trail has at most V entries; all repeated/constant terms compare exactly before projection; each alias chooses an actual full row, including differences in ignored columns; contradictory query emits none and empty body emits once. |
| ownership | Assignment ScalarViews borrow source image/frozen literals; O(V+A+H) funded arrays own only binding/index/projection scratch; emit must retain values before returning; no extra source journal, recursion, Row DTO or std::function. |
| failure | Caller Budget/scalar/emit/account failures unwind local arrays while image and Binding remain alive; callback false stops traversal, suitable for Boolean SET support but not BAG multiplicity. |
| cost | All visited nested-loop prefixes, trail restores, term/equality scalar bytes, full-witness head projection and caller emission costs are real; prefix work can be huge with zero answers; ordered dedup/counting belongs to caller, not an O(1) claim. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [src/runtime/fallback.cpp](../../../../../src/runtime/fallback.cpp), [src/runtime/difference.cpp](../../../../../src/runtime/difference.cpp) |

## B0008

[Lines 167–167](../../../../../src/runtime/cq_recompute.hpp#L167); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L167-L167:sha256:61c0ef0e9702d40d294111a5b84a4b6e21cbcdc438e4a2561615f75fca6d3c08
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private common evaluator namespace. |
| inputs / outputs | Ends native query storage/traversal declarations. |
| invariants | No public runtime profile or theorem is introduced by the private helper. |
| ownership | No owner is retained by the delimiter. |
| failure | No executable failure. |
| cost | No runtime work. |
| Design | [Refactor.md](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/cq_recompute.hpp](../../../../../src/runtime/cq_recompute.hpp) |
