# `src/runtime/combined_statistics.cpp` — block usage map

[Source](../../../../../src/runtime/combined_statistics.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Capture bounded distributions, workload counters, owner memory and explain observations without mislabeling partial information as exact.

Snapshot SHA-256: `a935d095391905d22a7b759c78a483b461dd59ee629392a96fd248855246f86d`. 46 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [statistics](../../../subsystem_contracts.md#statistics). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../src/runtime/combined_statistics.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–9](../../../../../src/runtime/combined_statistics.cpp#L6) | Type/record definition: struct CombinedCapture::Data |  · [reviewed contract](#b0002) |
| [B0003 · 10–20](../../../../../src/runtime/combined_statistics.cpp#L10) | Callable definition: CombinedCapture::CombinedCapture(OwnerCapture state,::crown::runtime::workload::Snapshot events) | calls stamp, plan, physical_sha256, availability; growth make_accounted_shared; source comment (unverified): // Factory inputs have private construction authority; this also catches a · [reviewed contract](#b0003) |
| [B0004 · 21–21](../../../../../src/runtime/combined_statistics.cpp#L21) | Callable definition: const OwnerCapture& CombinedCapture::state() const noexcept | calls ; returns data_-&gt;state · [reviewed contract](#b0004) |
| [B0005 · 22–22](../../../../../src/runtime/combined_statistics.cpp#L22) | Callable definition: const ::crown::runtime::workload::Snapshot& CombinedCapture::workload() const noexcept | calls ; returns data_-&gt;workload · [reviewed contract](#b0005) |
| [B0006 · 23–24](../../../../../src/runtime/combined_statistics.cpp#L23) | declares namespace scope. |  · [reviewed contract](#b0006) |
| [B0007 · 25–27](../../../../../src/runtime/combined_statistics.cpp#L25) | Callable definition: statistics::CombinedCapture SupportRuntime::capture_combined_statistics(const statistics::OwnerRequest& request,statistics::Limit… | calls capture_combined_statistics_view; returns capture_combined_statistics_view(request,limits) · [reviewed contract](#b0007) |
| [B0008 · 28–31](../../../../../src/runtime/combined_statistics.cpp#L28) | Callable definition: statistics::CombinedCapture SupportRuntime::capture_combined_statistics_view(statistics::OwnerRequestView request,statistics::Lim… | calls capture_statistics_view, workload_statistics, statistics::CombinedCapture, std::move; returns statistics::CombinedCapture(std::move(state),std::move(events)) · [reviewed contract](#b0008) |
| [B0009 · 32–34](../../../../../src/runtime/combined_statistics.cpp#L32) | Callable definition: statistics::CombinedCapture PhysicalRuntime::capture_combined_statistics(const statistics::OwnerRequest& request,statistics::Limi… | calls capture_combined_statistics_view; returns capture_combined_statistics_view(request,limits) · [reviewed contract](#b0009) |
| [B0010 · 35–38](../../../../../src/runtime/combined_statistics.cpp#L35) | Callable definition: statistics::CombinedCapture PhysicalRuntime::capture_combined_statistics_view(statistics::OwnerRequestView request,statistics::Li… | calls capture_statistics_view, workload_statistics, statistics::CombinedCapture, std::move; returns statistics::CombinedCapture(std::move(state),std::move(events)) · [reviewed contract](#b0010) |
| [B0011 · 39–41](../../../../../src/runtime/combined_statistics.cpp#L39) | Callable definition: statistics::CombinedCapture DeltaRuntime::capture_combined_statistics(const statistics::OwnerRequest& request,statistics::Limits … | calls capture_combined_statistics_view; returns capture_combined_statistics_view(request,limits) · [reviewed contract](#b0011) |
| [B0012 · 42–45](../../../../../src/runtime/combined_statistics.cpp#L42) | Callable definition: statistics::CombinedCapture DeltaRuntime::capture_combined_statistics_view(statistics::OwnerRequestView request,statistics::Limit… | calls capture_statistics_view, workload_statistics, statistics::CombinedCapture, std::move; returns statistics::CombinedCapture(std::move(state),std::move(events)) · [reviewed contract](#b0012) |
| [B0013 · 46–46](../../../../../src/runtime/combined_statistics.cpp#L46) | Closes surrounding scope/type. |  · [reviewed contract](#b0013) |

## B0001

[Lines 1–5](../../../../../src/runtime/combined_statistics.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:16c5f9f5041da73113092f0a1680f0f78ef2bcf909c43bfded071b4313aa8ba7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/combined_statistics.cpp: imports \`"crown/runtime/combined_statistics.hpp"\`, \`"crown/api/error.hpp"\`, \`"crown/resource/ownership.hpp"\` for compilation; opens namespace \`crown::runtime::statistics\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 6–9](../../../../../src/runtime/combined_statistics.cpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CombinedCapture::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a state population capture and a workload snapshot for one checked owner boundary. |
| inputs / outputs | state owns OwnerCapture metadata/components/copied keys; workload owns a shared detached numeric Snapshot graph. |
| invariants | Both members describe matching actual owner, committed sequence, physical plan hash and pending state, checked by private CombinedCapture construction. Neither retains live source rows or mutable owner pointers; state can own copied row keys. |
| ownership | Shared Data/control uses original account capture:5. State keeps funded copied selections/keys; workload shares its funded descriptor/cell snapshot. Wrapper copies share Data. |
| failure | Private construction rejects mismatched pairing before publication; account/actual member-copy allocation failure propagates. |
| cost | One actual wrapper/control allocation plus moves from factory-produced values. Lvalue OwnerCapture by-value copying can separately deep-copy arrays/keys; do not call all combined construction allocation-free. |
| Design | [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/combined_statistics_test.cpp](../../../../../tests/unit/combined_statistics_test.cpp), [tests/unit/combined_statistics_exception_test.cpp](../../../../../tests/unit/combined_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 10–20](../../../../../src/runtime/combined_statistics.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CombinedCapture::CombinedCapture(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject incompatible capture pairs before constructing an owning combined handle. |
| inputs / outputs | Checks state.owner==workload.owner, state.sequence==committed_epoch, exact physical SHA equality and pending equivalence, then funds Data/control on state.plan().account() and moves both inputs. |
| invariants | Only private factory-created typed captures enter this constructor; checks catch future owner-forwarding regressions. It does not merge availability/completion/interval semantics or make an incomplete state distribution exact. |
| ownership | By-value inputs become owned members; factory moves avoid deep recopy. A caller lvalue copy before private entry can allocate on original account. No live runtime pointer/row/cursor is retained. |
| failure | Mismatch throws statistics_binding before Data publication. Account/allocation failure unwinds local captures; source owners are unchanged and no broad handler is added. |
| cost | Fixed stamp/pending and 64-byte plan-hash comparison plus one actual funded shared Data/control request; original state/workload capture costs are paid separately. |
| Design | [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/combined_statistics_test.cpp](../../../../../tests/unit/combined_statistics_test.cpp), [tests/unit/combined_statistics_exception_test.cpp](../../../../../tests/unit/combined_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 21–21](../../../../../src/runtime/combined_statistics.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const OwnerCapture& CombinedCapture::state()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the combined handle's owning selected state population capture. |
| inputs / outputs | Returns data_-&gt;state by const reference. |
| invariants | Access does not recapture/revalidate the owner or merge independent availability/interval meanings. Private factory-produced handle remains immutable history. |
| ownership | Reference borrows shared Data; retain a CombinedCapture owner while using it. Underlying native values remain independently retained by that Data. |
| failure | Declared noexcept under valid handle invariant, no fallback allocation or catch. |
| cost | Fixed reference return, no deep copy, row scan or clock. |
| Design | [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/combined_statistics_test.cpp](../../../../../tests/unit/combined_statistics_test.cpp), [tests/unit/combined_statistics_exception_test.cpp](../../../../../tests/unit/combined_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 22–22](../../../../../src/runtime/combined_statistics.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ::crown::runtime::workload::Snapshot& CombinedCapture::workload()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the combined handle's owning detached numeric workload snapshot. |
| inputs / outputs | Returns data_-&gt;workload by const reference. |
| invariants | Access does not recapture/revalidate the owner or merge independent availability/interval meanings. Private factory-produced handle remains immutable history. |
| ownership | Reference borrows shared Data; retain a CombinedCapture owner while using it. Underlying native values remain independently retained by that Data. |
| failure | Declared noexcept under valid handle invariant, no fallback allocation or catch. |
| cost | Fixed reference return, no deep copy, row scan or clock. |
| Design | [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/combined_statistics_test.cpp](../../../../../tests/unit/combined_statistics_test.cpp), [tests/unit/combined_statistics_exception_test.cpp](../../../../../tests/unit/combined_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 23–24](../../../../../src/runtime/combined_statistics.cpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L24:sha256:7593126ad97c01c05cae6e22e200314dca507a3787ec4812ff54e14892a1bf5d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/combined_statistics.cpp: opens namespace \`crown::runtime\`; closes \`namespace crown::runtime::statistics\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0007

[Lines 25–27](../../../../../src/runtime/combined_statistics.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::CombinedCapture SupportRuntime::capture_combined_statistics(const statistics::OwnerRequest& request,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt an owning state request to the synchronous combined capture view for SupportRuntime. |
| inputs / outputs | Forwards request and limits to capture_combined_statistics_view without copying selection vectors. |
| invariants | Caller request remains stable through this synchronous call; requested state scopes retain actual owner/layer semantics. Wrapper does not advance engine input/output or reset observations. |
| ownership | No request graph is retained; successful combined result owns copied selected facts and detached numeric snapshots. |
| failure | Delegated shape/capture/account/binding failures propagate; no additional catch/retry. |
| cost | Fixed request-view/limits forwarding plus actual delegated state scan, workload snapshot allocations and combined control funding. |
| Design | [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/combined_statistics_test.cpp](../../../../../tests/unit/combined_statistics_test.cpp), [tests/unit/combined_statistics_exception_test.cpp](../../../../../tests/unit/combined_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 28–31](../../../../../src/runtime/combined_statistics.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::CombinedCapture SupportRuntime::capture_combined_statistics_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture state and committed workload observations from the same actual SupportRuntime boundary. |
| inputs / outputs | Synchronously obtains capture_statistics_view(request,limits) then workload_statistics(), moves both into checked CombinedCapture. |
| invariants | Caller holds exclusive synchronous owner access across both reads. Private pending state remains metadata-only; completed captures preserve separate availability/interval semantics and do not mutate runtime. |
| ownership | State owns funded component/projection/key copies; workload owns detached funded numeric arrays; combined control retains both on the original account. Caller request span/source runtime need not survive result. |
| failure | State/workload allocation or typed request errors propagate; mismatched boundaries reject statistics_binding before combined publication. Existing exact capture work-limit translations stay in their component boundary. |
| cost | Selected native population scan/copy/sort/histogram work plus O(descriptor+Cell counts) numeric snapshot clone and one combined Data/control allocation. Even an empty state request can require workload array/control allocation. |
| Design | [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/combined_statistics_test.cpp](../../../../../tests/unit/combined_statistics_test.cpp), [tests/unit/combined_statistics_exception_test.cpp](../../../../../tests/unit/combined_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 32–34](../../../../../src/runtime/combined_statistics.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::CombinedCapture PhysicalRuntime::capture_combined_statistics(const statistics::OwnerRequest& request,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt an owning state request to the synchronous combined capture view for PhysicalRuntime. |
| inputs / outputs | Forwards request and limits to capture_combined_statistics_view without copying selection vectors. |
| invariants | Caller request remains stable through this synchronous call; requested state scopes retain actual owner/layer semantics. Wrapper does not advance engine input/output or reset observations. |
| ownership | No request graph is retained; successful combined result owns copied selected facts and detached numeric snapshots. |
| failure | Delegated shape/capture/account/binding failures propagate; no additional catch/retry. |
| cost | Fixed request-view/limits forwarding plus actual delegated state scan, workload snapshot allocations and combined control funding. |
| Design | [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/combined_statistics_test.cpp](../../../../../tests/unit/combined_statistics_test.cpp), [tests/unit/combined_statistics_exception_test.cpp](../../../../../tests/unit/combined_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 35–38](../../../../../src/runtime/combined_statistics.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::CombinedCapture PhysicalRuntime::capture_combined_statistics_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture state and committed workload observations from the same actual PhysicalRuntime boundary. |
| inputs / outputs | Synchronously obtains capture_statistics_view(request,limits) then workload_statistics(), moves both into checked CombinedCapture. |
| invariants | Caller holds exclusive synchronous owner access across both reads. Private pending state remains metadata-only; completed captures preserve separate availability/interval semantics and do not mutate runtime. |
| ownership | State owns funded component/projection/key copies; workload owns detached funded numeric arrays; combined control retains both on the original account. Caller request span/source runtime need not survive result. |
| failure | State/workload allocation or typed request errors propagate; mismatched boundaries reject statistics_binding before combined publication. Existing exact capture work-limit translations stay in their component boundary. |
| cost | Selected native population scan/copy/sort/histogram work plus O(descriptor+Cell counts) numeric snapshot clone and one combined Data/control allocation. Even an empty state request can require workload array/control allocation. |
| Design | [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/combined_statistics_test.cpp](../../../../../tests/unit/combined_statistics_test.cpp), [tests/unit/combined_statistics_exception_test.cpp](../../../../../tests/unit/combined_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 39–41](../../../../../src/runtime/combined_statistics.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::CombinedCapture DeltaRuntime::capture_combined_statistics(const statistics::OwnerRequest& request,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt an owning state request to the synchronous combined capture view for DeltaRuntime. |
| inputs / outputs | Forwards request and limits to capture_combined_statistics_view without copying selection vectors. |
| invariants | Caller request remains stable through this synchronous call; requested state scopes retain actual owner/layer semantics. Wrapper does not advance engine input/output or reset observations. |
| ownership | No request graph is retained; successful combined result owns copied selected facts and detached numeric snapshots. |
| failure | Delegated shape/capture/account/binding failures propagate; no additional catch/retry. |
| cost | Fixed request-view/limits forwarding plus actual delegated state scan, workload snapshot allocations and combined control funding. |
| Design | [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/combined_statistics_test.cpp](../../../../../tests/unit/combined_statistics_test.cpp), [tests/unit/combined_statistics_exception_test.cpp](../../../../../tests/unit/combined_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 42–45](../../../../../src/runtime/combined_statistics.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::CombinedCapture DeltaRuntime::capture_combined_statistics_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture state and committed workload observations from the same actual DeltaRuntime boundary. |
| inputs / outputs | Synchronously obtains capture_statistics_view(request,limits) then workload_statistics(), moves both into checked CombinedCapture. |
| invariants | Caller holds exclusive synchronous owner access across both reads. Private pending state remains metadata-only; completed captures preserve separate availability/interval semantics and do not mutate runtime. |
| ownership | State owns funded component/projection/key copies; workload owns detached funded numeric arrays; combined control retains both on the original account. Caller request span/source runtime need not survive result. |
| failure | State/workload allocation or typed request errors propagate; mismatched boundaries reject statistics_binding before combined publication. Existing exact capture work-limit translations stay in their component boundary. |
| cost | Selected native population scan/copy/sort/histogram work plus O(descriptor+Cell counts) numeric snapshot clone and one combined Data/control allocation. Even an empty state request can require workload array/control allocation. |
| Design | [src/runtime/combined_statistics.cpp](../../../../../src/runtime/combined_statistics.cpp), [include/crown/runtime/combined_statistics.hpp](../../../../../include/crown/runtime/combined_statistics.hpp), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp), [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md), [tests/unit/combined_statistics_test.cpp](../../../../../tests/unit/combined_statistics_test.cpp), [tests/unit/combined_statistics_exception_test.cpp](../../../../../tests/unit/combined_statistics_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 46–46](../../../../../src/runtime/combined_statistics.cpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L46:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in src/runtime/combined_statistics.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
