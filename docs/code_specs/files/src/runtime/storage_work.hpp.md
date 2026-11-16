# `src/runtime/storage_work.hpp` — block usage map

[Source](../../../../../src/runtime/storage_work.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Create a finite grant only for an outer indexed operation; retain/rebind it across nested and resumed work.

Snapshot SHA-256: `75a34c02d17ebb335c45efbed7d719917782555018d9b8a3ab6bf9918b017973`. 161 lines partitioned into 31 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../src/runtime/storage_work.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // A suspended update/view/cursor retains this same noncopyable allowance. · [reviewed contract](#b0001) |
| [B0002 · 14–23](../../../../../src/runtime/storage_work.hpp#L14) | Type/record definition: struct StorageWorkState | source comment (unverified): // A suspended update/view/cursor retains this same noncopyable allowance. · [reviewed contract](#b0002) |
| [B0003 · 24–25](../../../../../src/runtime/storage_work.hpp#L24) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 26–28](../../../../../src/runtime/storage_work.hpp#L26) | Callable definition: public: StorageWorkContext(const resource::MemoryAccount& memory,std::optional&lt;storage::IndexWork&gt; limit) :memory_(memory),limit_… | calls memory_, limit_ · [reviewed contract](#b0004) |
| [B0005 · 29–29](../../../../../src/runtime/storage_work.hpp#L29) | Callable definition: \[\[nodiscard\]\] const resource::MemoryAccount& memory() const noexcept | calls ; returns memory_ · [reviewed contract](#b0005) |
| [B0006 · 30–30](../../../../../src/runtime/storage_work.hpp#L30) | Callable definition: \[\[nodiscard\]\] bool indexed() const noexcept | calls has_value; returns limit_.has_value() · [reviewed contract](#b0006) |
| [B0007 · 31–31](../../../../../src/runtime/storage_work.hpp#L31) | Explanatory comments or spacing. | source comment (unverified): // Requires indexed(); this is the immutable five-domain ceiling, not remaining work. · [reviewed contract](#b0007) |
| [B0008 · 32–32](../../../../../src/runtime/storage_work.hpp#L32) | Callable definition: \[\[nodiscard\]\] const storage::IndexWork& limit() const noexcept | calls ; returns *limit_; source comment (unverified): // Requires indexed(); this is the immutable five-domain ceiling, not remaining work. · [reviewed contract](#b0008) |
| [B0009 · 33–33](../../../../../src/runtime/storage_work.hpp#L33) | Callable definition: \[\[nodiscard\]\] const StorageWorkLease& active() const noexcept | calls ; returns active_ · [reviewed contract](#b0009) |
| [B0010 · 34–34](../../../../../src/runtime/storage_work.hpp#L34) | controls preprocessing. |  · [reviewed contract](#b0010) |
| [B0011 · 35–41](../../../../../src/runtime/storage_work.hpp#L35) | Callable definition: \[\[nodiscard\]\] storage::IndexWork observed_work() const noexcept | calls get, remaining, limit; returns last_consumed_; {ceiling.structural_steps-left.structural_steps,ceiling.scalar_fields-left.scalar_f… · [reviewed contract](#b0011) |
| [B0012 · 42–42](../../../../../src/runtime/storage_work.hpp#L42) | Callable definition: \[\[nodiscard\]\] std::uint64_t fresh_operations() const noexcept | calls ; returns fresh_operations_ · [reviewed contract](#b0012) |
| [B0013 · 43–53](../../../../../src/runtime/storage_work.hpp#L43) | controls preprocessing; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 54–54](../../../../../src/runtime/storage_work.hpp#L54) | Callable definition: inline const resource::MemoryAccount& StorageWorkState::memory() const | calls memory; returns context-&gt;memory() · [reviewed contract](#b0014) |
| [B0015 · 55–68](../../../../../src/runtime/storage_work.hpp#L55) | Callable definition: template&lt;class Plan&gt; \[\[nodiscard\]\] inline std::shared_ptr&lt;StorageWorkContext&gt; storage_context(const Plan& plan, std::uint64_t lim… | calls constexpr, account, statistics, Error; returns plan.account(); existing ? existing : resource::MemoryAccount::create(limit_bytes); growth make_accounted_shared · [reviewed contract](#b0015) |
| [B0016 · 69–78](../../../../../src/runtime/storage_work.hpp#L69) | Callable definition: template&lt;class Plan&gt; inline void validate_storage_context(const Plan& plan,const std::shared_ptr&lt;StorageWorkContext&gt;& context, st… | calls options, indexed, has_value, limit · [reviewed contract](#b0016) |
| [B0017 · 79–81](../../../../../src/runtime/storage_work.hpp#L79) | Explanatory comments or spacing. | source comment (unverified): // Public creation from a compiler/cache artifact starts a new query. Native · [reviewed contract](#b0017) |
| [B0018 · 82–87](../../../../../src/runtime/storage_work.hpp#L82) | Callable definition: template&lt;class Plan&gt; \[\[nodiscard\]\] inline std::shared_ptr&lt;StorageWorkContext&gt; new_storage_context(const Plan& plan, std::uint64_t… | calls resource::MemoryAccount::create, options; returns resource::make_accounted_shared&lt;StorageWorkContext&gt;(account,resource::MemoryPurpose::support_metada…; growth make_accounted_shared; source comment (unverified): // Public creation from a compiler/cache artifact starts a new query. Native · [reviewed contract](#b0018) |
| [B0019 · 88–93](../../../../../src/runtime/storage_work.hpp#L88) | declares types or opens a type body. | source comment (unverified): // Single-writer internal composition. A fresh indexed operation funds a · [reviewed contract](#b0019) |
| [B0020 · 94–119](../../../../../src/runtime/storage_work.hpp#L94) | Callable definition: public: explicit StorageOperation(std::shared_ptr&lt;StorageWorkContext&gt; context,StorageWorkLease retained={}) :context_(std::move(c… | calls context_, std::move, indexed, Error; growth make_accounted_shared; source comment (unverified): // Admission precedes installing a newly minted operation. Rebinding a · [reviewed contract](#b0020) |
| [B0021 · 120–123](../../../../../src/runtime/storage_work.hpp#L120) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0021) |
| [B0022 · 124–132](../../../../../src/runtime/storage_work.hpp#L124) | Callable definition: ~StorageOperation() noexcept | calls std::terminate, observed_work, reset · [reviewed contract](#b0022) |
| [B0023 · 133–133](../../../../../src/runtime/storage_work.hpp#L133) | Callable definition: \[\[nodiscard\]\] const StorageWorkLease& lease() const noexcept | calls ; returns lease_ · [reviewed contract](#b0023) |
| [B0024 · 134–138](../../../../../src/runtime/storage_work.hpp#L134) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0024) |
| [B0025 · 139–143](../../../../../src/runtime/storage_work.hpp#L139) | Callable definition: \[\[nodiscard\]\] inline StorageWorkLease storage_lease(const std::shared_ptr&lt;StorageWorkContext&gt;& context) | calls indexed, active, Error; returns {}; context-&gt;active() · [reviewed contract](#b0025) |
| [B0026 · 144–146](../../../../../src/runtime/storage_work.hpp#L144) | Callable definition: \[\[nodiscard\]\] inline storage::IndexWorkAllowance* storage_work(const std::shared_ptr&lt;StorageWorkContext&gt;& context) | calls indexed, storage_lease; returns context && context-&gt;indexed() ? &storage_lease(context)-&gt;legacy : nullptr · [reviewed contract](#b0026) |
| [B0027 · 147–149](../../../../../src/runtime/storage_work.hpp#L147) | Callable definition: \[\[nodiscard\]\] inline storage::IndexWorkAllowance* compact_storage_work(const std::shared_ptr&lt;StorageWorkContext&gt;& context) | calls indexed, storage_lease, get; returns context && context-&gt;indexed() ? storage_lease(context)-&gt;allowance.get() : nullptr · [reviewed contract](#b0027) |
| [B0028 · 150–152](../../../../../src/runtime/storage_work.hpp#L150) | Callable definition: \[\[nodiscard\]\] inline storage::AccountedIndexWork owning_storage_work(const std::shared_ptr&lt;StorageWorkContext&gt;& context) | calls storage_lease; returns lease ? lease-&gt;allowance : storage::AccountedIndexWork{} · [reviewed contract](#b0028) |
| [B0029 · 153–153](../../../../../src/runtime/storage_work.hpp#L153) | Explanatory comments or spacing. | source comment (unverified): // Aliasing ownership retains the complete lease without another control or allowance. · [reviewed contract](#b0029) |
| [B0030 · 154–160](../../../../../src/runtime/storage_work.hpp#L154) | Callable definition: \[\[nodiscard\]\] inline std::shared_ptr&lt;storage::IndexWorkAllowance&gt; shared_storage_work( const std::shared_ptr&lt;StorageWorkContext&gt;&… | calls storage_lease, std::move; returns {}; {std::move(lease),allowance}; source comment (unverified): // Aliasing ownership retains the complete lease without another control or allowance. · [reviewed contract](#b0030) |
| [B0031 · 161–161](../../../../../src/runtime/storage_work.hpp#L161) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime::detail · [reviewed contract](#b0031) |

## B0001

[Lines 1–13](../../../../../src/runtime/storage_work.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:e269f59f2c1b436afa7f0e1e04e284b0000724b417cf935d926d75674342d976
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/storage_work.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/api/error.hpp"\`, \`"crown/ir/program.hpp"\`, \`"crown/storage/accounted_index_work.hpp"\`, \`"../storage/index_work_alias.hpp"\`, \`&lt;memory&gt;\`, \`&lt;utility&gt;\` for compilation; opens namespace \`crown::runtime::detail\`; forward-declares \`class StorageWorkContext\` without defining object layout. Source comment: A suspended update/view/cursor retains this same noncopyable allowance. The aliasing shared_ptr passed to storage journals owns the complete lease. |
| inputs / outputs | Compile-time consumers may name \`class StorageWorkContext\` while their definitions remain owned by the declaring headers/source files. |
| invariants | Forward declarations permit references to incomplete types; consumers that need layout or members include the defining header. The source note says: A suspended update/view/cursor retains this same noncopyable allowance. The aliasing shared_ptr passed to storage journals owns the complete lease. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: A suspended update/view/cursor retains this same noncopyable allowance. The aliasing shared_ptr passed to storage journals owns the complete lease. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 14–23](../../../../../src/runtime/storage_work.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StorageWorkState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one indexed native allowance across suspended runtime operations. |
| inputs / outputs | Original context and per-operation limit create one accounted allowance plus a legacy alias to that same allowance. |
| invariants | The alias does not create a second budget. Shared lease ownership is distinct from copying the noncopyable allowance. |
| ownership | Original account funds both control/allowance; journals may retain aliasing shared owners of this complete state. |
| failure | Funding failure installs no active operation. |
| cost | Fixed owner/allowance admission cost; resumption does not rerun it. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md) |

```text
  StorageWorkState(std::shared_ptr<StorageWorkContext> owner,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one funded indexed allowance and a legacy facade over that identical mutable balance. |
| inputs / outputs | Moves nonnull owning context, creates AccountedIndexWork(memory(),limit), initializes legacy through IndexWorkAlias::legacy(*allowance.get()). |
| invariants | Internal constructor callers provide matching context/limit and fund the outer lease separately. legacy is an alias, not a second work cap or copied balance. |
| ownership | State retains context and allowance control; legacy nonowningly aliases native balance within that retained allowance. |
| failure | Allowance funding/admission errors unwind local state before StorageOperation installs it as active. No broad handler or fallback grant. |
| cost | Actual funded allowance/control creation plus fixed owner/alias setup; not charged as tuple visits. Resumption skips this constructor. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 24–25](../../../../../src/runtime/storage_work.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using StorageWorkLease=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the complete grant state used to resume one suspended native operation. |
| inputs / outputs | Shared pointer retains StorageWorkState, its context, actual AccountedIndexWork and legacy alias. |
| invariants | Copying the lease shares one balance; it cannot copy/refill the noncopyable allowance. Owning only a raw facade pointer is insufficient to resume safely. |
| ownership | External cursor/journal/update may hold lease after lexical StorageOperation clears active slot. Last complete owner releases state/control. |
| failure | Shared handle copy/move adds no fresh-work admission or custom failure handling. |
| cost | Fixed ownership bookkeeping per copy; final destruction releases actual controls/owners and does not allocate a replacement. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
class StorageWorkContext {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain original native query allocation account, immutable backend work ceiling and current lexical grant binding. |
| inputs / outputs | memory_ is shared account; limit_ engaged selects indexed backend with fixed per-operation domains; active_ optionally retains the complete currently bound lease. Test counters expose last consumed work/fresh operations. |
| invariants | Single-writer synchronous composition only. Only StorageOperation changes active_; no nested/resumed refill is permitted. A context is not a lock or thread-local independent allowance. |
| ownership | Context owns account handle and optional active lease; StorageOperation must clear the active strong link at outer exit so retained suspended leases remain independent. |
| failure | Validation helpers reject wrong account/backend/limit; accessor preconditions are explicit and no context-level catch hides violations. |
| cost | Fixed metadata/owner state; new context/control is actually funded, while root indexed operation separately funds lease/allowance. Reference backend creates no indexed grant. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 26–28](../../../../../src/runtime/storage_work.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  StorageWorkContext(const resource::MemoryAccount& memory,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the immutable allocation account/backend cap for runtime work composition. |
| inputs / outputs | Copies existing account and optional five-domain IndexWork limit; active lease begins empty. |
| invariants | Internal callers supply valid account and admitted immutable plan limits; constructor does not validate/rehome a mismatched account by itself. |
| ownership | Retains account handle only; shared context allocation occurs at factory call sites, not in this constructor. |
| failure | No explicit throw or exception translation; later operation funding uses the same account. |
| cost | Fixed handle/optional copy without a row scan or work grant allocation. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 29–29](../../../../../src/runtime/storage_work.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const resource::MemoryAccount& memory() const noexcept { return memory_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose native work context metadata without creating an allowance. |
| inputs / outputs | Returns the existing query account by const reference. |
| invariants | Context must remain alive; caller must not interpret the reference as a fresh budget. |
| ownership | References borrow context; scalar result owns nothing. Active lease holds the complete original state, not a separate balance. |
| failure | Declared noexcept under accessor preconditions; no fallback grant, allocation or handler. |
| cost | Fixed field/optional access, no ledger/table scan. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 30–30](../../../../../src/runtime/storage_work.hpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] bool indexed()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose native work context metadata without creating an allowance. |
| inputs / outputs | Returns whether this context carries an indexed per-operation ceiling. |
| invariants | Backend choice is immutable plan metadata, not whether an operation is currently active. |
| ownership | References borrow context; scalar result owns nothing. Active lease holds the complete original state, not a separate balance. |
| failure | Declared noexcept under accessor preconditions; no fallback grant, allocation or handler. |
| cost | Fixed field/optional access, no ledger/table scan. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 31–31](../../../../../src/runtime/storage_work.hpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L31:sha256:3b07290477487b9793be0603454e98d7b6cdf2597038d652bdf45d73ba7800db
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`\[\[nodiscard\]\] const storage::IndexWork& limit() const noexcept\`: Requires indexed(); this is the immutable five-domain ceiling, not remaining work. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/storage_work.hpp:L32; use that declaration for the actual input/output shape. |
| invariants | The source note states: Requires indexed(); this is the immutable five-domain ceiling, not remaining work. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Requires indexed(); this is the immutable five-domain ceiling, not remaining work. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0008

[Lines 32–32](../../../../../src/runtime/storage_work.hpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const storage::IndexWork& limit()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose native work context metadata without creating an allowance. |
| inputs / outputs | Returns the configured five-domain per-operation ceiling by const reference. |
| invariants | Requires indexed()==true; this intentionally dereferences an engaged optional rather than guarding a caller invariant repeatedly. |
| ownership | References borrow context; scalar result owns nothing. Active lease holds the complete original state, not a separate balance. |
| failure | Declared noexcept under accessor preconditions; no fallback grant, allocation or handler. |
| cost | Fixed field/optional access, no ledger/table scan. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 33–33](../../../../../src/runtime/storage_work.hpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const StorageWorkLease& active()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose native work context metadata without creating an allowance. |
| inputs / outputs | Returns the lexical active complete lease, possibly empty, by const reference. |
| invariants | Reference is live state, not a retained resume owner; copy the lease while active if it must outlive the binding. |
| ownership | References borrow context; scalar result owns nothing. Active lease holds the complete original state, not a separate balance. |
| failure | Declared noexcept under accessor preconditions; no fallback grant, allocation or handler. |
| cost | Fixed field/optional access, no ledger/table scan. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 34–34](../../../../../src/runtime/storage_work.hpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L34:sha256:c4b9c3fab52d74ef772a80090ef4a35760b5a3b41ee88be876eed0db22a2fcbd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/storage_work.hpp: opens/branches compile-time guard \`#ifdef CROWN_RUNTIME_TESTING\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0011

[Lines 35–41](../../../../../src/runtime/storage_work.hpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] storage::IndexWork observed_work()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report exact consumed work domains for runtime boundary tests. |
| inputs / outputs | When active subtracts remaining allowance from original limit in all five domains; otherwise returns last_consumed_. |
| invariants | CROWN_RUNTIME_TESTING only. Active lease was created from the same context ceiling and charges never underflow. Values are native admission units, not CPU/time or logical tuple work. |
| ownership | Returns inline IndexWork; reads actual shared balance without cloning it. |
| failure | Noexcept arithmetic under matching-limit invariant; no recovery. |
| cost | Five fixed subtractions, no allocation or scan. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 42–42](../../../../../src/runtime/storage_work.hpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] std::uint64_t fresh_operations()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the testing count of newly admitted outer indexed grants. |
| inputs / outputs | Returns fresh_operations_, incremented only after successful fresh startup admission and saturating at UINT64_MAX. |
| invariants | Nested/resumed operations do not increment; reference operations create no grant. This test counter is not an execution/source stamp. |
| ownership | Inline value only, no ownership. |
| failure | Noexcept load; no diagnostic construction. |
| cost | Fixed load with test-build-only counter storage. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 43–53](../../../../../src/runtime/storage_work.hpp#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L53:sha256:50d8dfee1ec8ec5690b003bf6a852e75f51cd21b65965279763ba57593529e47
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish StorageWorkContext with StorageOperation friendship; retain memory_, limit_, active_, and the two test-only work counters, then close the class. |
| inputs / outputs | memory_ is the shared MemoryAccount value, limit_ the optional five-domain IndexWork ceiling, and active_ a StorageWorkLease. CROWN_RUNTIME_TESTING also declares last_consumed_ and fresh_operations_. Friendship grants StorageOperation private access. |
| invariants | The macro changes the class layout, so testing and production variants must use their coherent definitions. Line 50 is a value initializer, not a scope opener. The members do not by themselves validate or replenish a work allowance. |
| ownership | memory_ shares its account control; active_ is a shared_ptr&lt;StorageWorkState&gt; lease and retains that state/control while populated. limit_ and the guarded diagnostics are values. Actual operation/journal lifetime management belongs to StorageOperation and the existing lease API. |
| failure | Friend/member declarations add no handler or runtime rejection. Member initialization follows the constructor; the operation/allowance factories keep their own allocation and resource-failure contracts. |
| cost | Fixed member storage, optional ceiling and shared-lease handle; account/lease copies and release have their normal control costs when used. Test-only diagnostics add fields only to the testing class. Actual lease construction/operation work is outside this declaration span. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0014

[Lines 54–54](../../../../../src/runtime/storage_work.hpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const resource::MemoryAccount& StorageWorkState::memory()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the owning context account during original grant construction. |
| inputs / outputs | Returns context-&gt;memory(). |
| invariants | State constructor has already moved a valid nonnull context before calling this private helper; it never creates a substitute account. |
| ownership | Reference borrows state-retained context/account and must not outlive them. |
| failure | No new check/catch; nonnull owner is an internal construction precondition. |
| cost | Fixed pointer/reference access, no allocation or ledger scan. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 55–68](../../../../../src/runtime/storage_work.hpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Plan> [[nodiscard]] inline std::shared_ptr<StorageWorkContext> storage_context(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an internal runtime context using the native plan's existing account or an explicit rebuild account. |
| inputs / outputs | For account-bearing plan, rejects any different supplied account owner then uses plan.account(); otherwise uses existing when present or creates a new account(limit_bytes). Checks exact account ceiling and funds context with plan indexed limits. |
| invariants | Native/rebuild paths never silently rehome metadata onto a different query allowance. Equal byte ceilings alone do not establish account identity. This helper does not recompile/import a plan. |
| ownership | Returned context/control is funded as support_metadata on chosen account and retains it; existing immutable plan state is only borrowed during metadata reads. |
| failure | Mismatched owner throws storage_contract; wrong ceiling throws MemoryFailure(contract); allocation/account faults propagate without installing any active operation. |
| cost | Fixed option/account metadata checks plus actual shared context/control and, only for standalone no-existing path, account creation. No table scan or operation work grant yet. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 69–78](../../../../../src/runtime/storage_work.hpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Plan> inline void validate_storage_context(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an internal runtime context that differs from the immutable plan/account contract. |
| inputs / outputs | Checks nonnull, indexed engagement, exact per-operation IndexWork, exact memory ceiling, then native plan account owner identity when available. |
| invariants | All five work domains must match; this equality is not lexicographic limit admission. No context/account is replaced to repair a mismatch. |
| ownership | Borrows plan/context synchronously; retains nothing and mutates neither. |
| failure | Mismatch throws storage_contract with its precise backend/owner diagnostic. No broad catch or fallback. |
| cost | Fixed metadata comparisons/account statistics access, no table traversal or new allocation on successful validation. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 79–81](../../../../../src/runtime/storage_work.hpp#L79); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L81:sha256:c311dbb31bb3c9992d4b97415069fff8336c1cd5c1dcc3d8f53fab3037d75dd8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`template&lt;class Plan&gt; \[\[nodiscard\]\] inline std::shared_ptr&lt;StorageWorkContext&gt; new_storage_context(const Plan& plan, std::uint64_t limit_bytes)\`: Public creation from a compiler/cache artifact starts a new query. Native admission then consumes this same account and the one outer operation grant; internal rebuilds continue using storage_context's existing-account path. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/storage_work.hpp:L82; use that declaration for the actual input/output shape. |
| invariants | The source note states: Public creation from a compiler/cache artifact starts a new query. Native admission then consumes this same account and the one outer operation grant; internal rebuilds continue using storage_context's existing-account path. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Public creation from a compiler/cache artifact starts a new query. Native admission then consumes this same account and the one outer operation grant; internal rebuilds continue using storage_context's existing-account path. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0018

[Lines 82–87](../../../../../src/runtime/storage_work.hpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
new_storage_context(const Plan& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start a new runtime query account when importing a compiler/cache plan. |
| inputs / outputs | Plan backend limits and requested query byte cap produce one new context/account. |
| invariants | Public compiler ownership is not reused; later native compilation/storage/operations share this fresh account. Internal rebuild paths use the separate existing-account helper. |
| ownership | Original context owner retains the new account; no mutable table state is shared from the source plan. |
| failure | Account/context allocation failure returns no context. |
| cost | Fixed admission owner allocations and backend option access; plan import work happens separately. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md) |

## B0019

[Lines 88–93](../../../../../src/runtime/storage_work.hpp#L88); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class StorageOperation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Activate a fresh, nested or resumed native grant for one lexical scope. |
| inputs / outputs | Context and optional retained lease establish the allowance returned to nested storage calls until destruction. |
| invariants | Nested entries share the already active grant; resumption binds its exact original lease; conflicting owner/lease is rejected. Only a fresh outer indexed operation funds and debits admission. Single caller, not thread synchronization. |
| ownership | Outer scope temporarily installs its shared lease and clears that slot on destruction; external cursor/update owners may retain it after suspension. |
| failure | Failed admission never installs an active grant; destructor is nonallocating and terminates on impossible mismatched active ownership. |
| cost | Fresh operation has one funded allowance/control cost; nested/resumed scopes perform fixed owner checks with no budget refill. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md) |

## B0020

[Lines 94–119](../../../../../src/runtime/storage_work.hpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit StorageOperation(std::shared_ptr<StorageWorkContext> context,StorageWorkLease retained={})
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind one indexed operation to its original finite grant across nested calls and suspended owners. |
| inputs / outputs | Matching context plus optional retained lease in; active operation scope and retained lease access out. |
| invariants | Only an outer fresh operation creates a grant. Nested scopes reuse the current grant; resumed scopes restore the same lease without restoring its balance. |
| ownership | Lease retains context and AccountedIndexWork; the outer scope installs/removes context.active_. Reference operations retain memory but create no indexed grant. |
| failure | Reject foreign/conflicting leases. Allocate a fresh lease and admit startup before installing active_; destruction clears active_ without allocating. |
| cost | Fresh indexed admission funds shared lease/control and work-allowance control; nested/resumed entry uses shared-handle operations. This cost is separate from table visits. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0021

[Lines 120–123](../../../../../src/runtime/storage_work.hpp#L120); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  StorageOperation(const StorageOperation&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make lexical native grant activation immovable and uniquely paired with its outer teardown. |
| inputs / outputs | Deletes all copy/move constructors and assignments of StorageOperation. |
| invariants | Copying/moving an active lexical guard cannot duplicate the responsibility to clear context.active_; suspended ownership is explicitly StorageWorkLease instead. |
| ownership | Guard retains context/lease for its own lifetime; public resume owners retain the complete lease separately. |
| failure | Misuse fails at compile time; no runtime recovery branch. |
| cost | No executable work or state allocation. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 124–132](../../../../../src/runtime/storage_work.hpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ~StorageOperation() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clear the lexical active grant exactly once without destroying externally retained suspended ownership. |
| inputs / outputs | For outer_ only, verifies active_==lease_, records test work, then resets context.active_. Nested guards leave binding alone. |
| invariants | Mismatched active ownership means impossible internal nesting/owner corruption and terminates. Normal teardown never resets remaining allowance or creates another balance. |
| ownership | Own guard lease/context release after body; suspended external leases can keep original state/allowance alive. Clearing active breaks the context/state strong ownership cycle. |
| failure | Noexcept; terminate on violated exact binding is required invariant enforcement, not a removable user-input exception handler. |
| cost | Fixed owner check/reset and optional five-domain test subtraction; last-owner teardown may release funded state/control but allocates no replacement grant. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 133–133](../../../../../src/runtime/storage_work.hpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const StorageWorkLease& lease()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow this guard's complete grant owner for explicit suspension/journal composition. |
| inputs / outputs | Returns lease_, empty for reference/no-context path. |
| invariants | Borrowed reference alone does not extend guard lifetime; callers copy StorageWorkLease if it must survive outer exit. Same state preserves exact consumed balance. |
| ownership | Guard retains owner; copied shared lease may outlive active binding without relocating state. |
| failure | Declared noexcept; no allocation/validation/refill. |
| cost | Fixed reference return and caller-chosen shared-owner copy only. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 134–138](../../../../../src/runtime/storage_work.hpp#L134); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::shared_ptr<StorageWorkContext> context_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain guard context, exact lease and outer teardown responsibility. |
| inputs / outputs | context_ owns runtime context; lease_ owns active/resumed complete state; outer_ says this guard installed context.active_. |
| invariants | Nested guard shares lease with outer_=false; only installing guard clears binding. No mutable query row or per-entry recovery graph is stored. |
| ownership | Shared handles retain exact account/grant; lexical guard itself cannot move/copy. |
| failure | Constructor rejects foreign/conflicting leases before installation; destructor enforces matching active state. |
| cost | Two shared handles plus boolean per lexical scope; fresh underlying allocation costs occur only when original indexed grant is minted. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0025

[Lines 139–143](../../../../../src/runtime/storage_work.hpp#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline StorageWorkLease storage_lease(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain an owning handle to the currently active finite native grant. |
| inputs / outputs | Null/reference context returns empty; indexed context must have active lease and returns a shared copy of it. |
| invariants | This accessor never opens an operation or creates/refills a grant. Indexed primitive calls require the outer StorageOperation already active. |
| ownership | Returned handle retains complete state/context/allowance across suspension; scalar work remains shared. |
| failure | Absent active indexed operation throws storage_contract; no fallback unlimited allowance. |
| cost | Fixed branch/shared-handle copy; no success allocation, row scan or grant creation. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 144–146](../../../../../src/runtime/storage_work.hpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline storage::IndexWorkAllowance* storage_work(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the already active native allowance facade for synchronous storage calls. |
| inputs / outputs | Returns pointer to active lease's legacy alias or nullptr for null/reference context. |
| invariants | Never creates/resets allowance. Raw pointer must not outlive its actual retained owner; facade selection does not create a second grant. |
| ownership | Pointer borrows the active/retained complete lease; legacy aliases the same native balance. |
| failure | Indexed context with no active grant throws storage_contract via storage_lease; no catch/fallback. |
| cost | Fixed context check, temporary shared-owner copy and pointer access; no new allocation or balance copy. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0027

[Lines 147–149](../../../../../src/runtime/storage_work.hpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline storage::IndexWorkAllowance* compact_storage_work(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the already active native allowance facade for synchronous storage calls. |
| inputs / outputs | Returns active allowance.get() or nullptr for null/reference context. |
| invariants | Never creates/resets allowance. Raw pointer must not outlive its actual retained owner; facade selection does not create a second grant. |
| ownership | Pointer borrows actual AccountedIndexWork control; retain lease or owning allowance while using it. |
| failure | Indexed context with no active grant throws storage_contract via storage_lease; no catch/fallback. |
| cost | Fixed context check, temporary shared-owner copy and pointer access; no new allocation or balance copy. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0028

[Lines 150–152](../../../../../src/runtime/storage_work.hpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline storage::AccountedIndexWork owning_storage_work(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the actual native allowance control without copying its mutable work balance. |
| inputs / outputs | Copies active lease's AccountedIndexWork handle, or returns default empty for null/reference context. |
| invariants | This coowns the allowance, not the complete StorageWorkState resume lease/context. It does not by itself authorize rebinding a suspended runtime operation. |
| ownership | Returned handle keeps allowance control/account alive even after lexical active slot clears; balance is shared with legacy/native facades. |
| failure | Missing active indexed grant throws storage_contract; success adds no allocation/refill. |
| cost | Fixed shared-owner handle copies, no row scan or fresh native grant. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0029

[Lines 153–153](../../../../../src/runtime/storage_work.hpp#L153); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L153-L153:sha256:25e3e0b162889722389beb6b704d532217f0e84aaa0d7b94ab4f127bc2df7028
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`\[\[nodiscard\]\] inline std::shared_ptr&lt;storage::IndexWorkAllowance&gt; shared_storage_work( const std::shared_ptr&lt;StorageWorkContext&gt;& context)\`: Aliasing ownership retains the complete lease without another control or allowance. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/storage_work.hpp:L154; use that declaration for the actual input/output shape. |
| invariants | The source note states: Aliasing ownership retains the complete lease without another control or allowance. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Aliasing ownership retains the complete lease without another control or allowance. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0030

[Lines 154–160](../../../../../src/runtime/storage_work.hpp#L154); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] inline std::shared_ptr<storage::IndexWorkAllowance> shared_storage_work(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the complete lease while exposing its legacy alias to storage journals. |
| inputs / outputs | Obtains complete active lease, returns empty for reference path, otherwise constructs aliasing shared_ptr with get()=&lease-&gt;legacy and owner=the same moved lease. |
| invariants | Aliasing constructor creates no second control block or copied allowance. Journals share exact remaining budget and cannot refill it. |
| ownership | Returned pointer coowns complete state/context/native allowance through the original shared control; legacy pointer remains stable until last owner release. |
| failure | Absent active indexed grant throws storage_contract; no local catch or fallback. |
| cost | Fixed aliasing shared-owner operations without allocation; final owner release may destroy actual grant/control. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/accounted_index_work.hpp](../../../../../include/crown/storage/accounted_index_work.hpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0031

[Lines 161–161](../../../../../src/runtime/storage_work.hpp#L161); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L161-L161:sha256:8006176e29bd8d5a726886f993203bd32a406cbe36d48b563ff6209dd1f31eeb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::detail\` at its lexical source position in src/runtime/storage_work.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md), [docs/storage.md](../../../../storage.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
