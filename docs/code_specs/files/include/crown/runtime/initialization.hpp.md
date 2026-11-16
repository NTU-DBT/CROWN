# `include/crown/runtime/initialization.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/initialization.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Compose one full physical source update across all its aliases into one atomic logical support epoch.

Snapshot SHA-256: `7da9fc268db375fbcba6e92d63f3a7e128ee2f0ae3e9a6578fb3482447080e66`. 42 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [physical](../../../../subsystem_contracts.md#physical). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [docs/support_invariants.md](../../../../../support_invariants.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/runtime/initialization.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–9](../../../../../../include/crown/runtime/initialization.hpp#L9) | Type/record definition: enum class BuildMethod |  · [reviewed contract](#b0002) |
| [B0003 · 10–13](../../../../../../include/crown/runtime/initialization.hpp#L10) | Type/record definition: struct BuildOptions |  · [reviewed contract](#b0003) |
| [B0004 · 14–22](../../../../../../include/crown/runtime/initialization.hpp#L14) | Type/record definition: struct BuildMetrics |  · [reviewed contract](#b0004) |
| [B0005 · 23–24](../../../../../../include/crown/runtime/initialization.hpp#L23) | declares namespace scope. | source comment (unverified): // Shared cumulative build accounting; distinct from ordinary per-event caps. · [reviewed contract](#b0005) |
| [B0006 · 25–31](../../../../../../include/crown/runtime/initialization.hpp#L25) | Callable definition: inline void build_charge(BuildMetrics& metrics,const BuildOptions& options,std::uint64_t amount=1) | calls max, Error; source comment (unverified): // Shared cumulative build accounting; distinct from ordinary per-event caps. · [reviewed contract](#b0006) |
| [B0007 · 32–33](../../../../../../include/crown/runtime/initialization.hpp#L32) | Explanatory comments or spacing. | source comment (unverified): // Use a category distinct from metrics.work. Its overflow can occur after · [reviewed contract](#b0007) |
| [B0008 · 34–39](../../../../../../include/crown/runtime/initialization.hpp#L34) | Callable definition: inline void build_metric(BuildMetrics& metrics,const BuildOptions& options,std::uint64_t& counter,std::uint64_t amount=1) | calls build_charge, max, Error; source comment (unverified): // Use a category distinct from metrics.work. Its overflow can occur after · [reviewed contract](#b0008) |
| [B0009 · 40–40](../../../../../../include/crown/runtime/initialization.hpp#L40) | Type/record definition: struct NativeSeed |  · [reviewed contract](#b0009) |
| [B0010 · 41–42](../../../../../../include/crown/runtime/initialization.hpp#L41) | Closes surrounding scope/type. | source comment (unverified): // namespace detail · [reviewed contract](#b0010) |

## B0001

[Lines 1–8](../../../../../../include/crown/runtime/initialization.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the runtime initialization public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

## B0002

[Lines 9–9](../../../../../../include/crown/runtime/initialization.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class BuildMethod {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose explicit snapshot construction versus diagnostic insertion replay. |
| inputs / outputs | direct and insertion_replay are separate initialization implementations, not ordinary input modes. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

## B0003

[Lines 10–13](../../../../../../include/crown/runtime/initialization.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BuildOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure cumulative runtime initialization work. |
| inputs / outputs | Construction method and optional cumulative build work cap, separate from per-event work limits. |
| invariants | Public value/configuration only; changing fields does not perform admission, execute an input or create proof authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

```text
BuildMethod method=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The explicit direct/replay build method. |
| inputs / outputs | Stores/exposes the explicit direct/replay build method. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

```text
std::optional<std::uint64_t> work_limit=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The optional selected initialization work allowance. |
| inputs / outputs | Stores/exposes the optional selected initialization work allowance. |
| invariants | This field is descriptive/configuration data, not an independent admission or publication capability. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

## B0004

[Lines 14–22](../../../../../../include/crown/runtime/initialization.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct BuildMetrics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe concrete initialization work and populations. |
| inputs / outputs | Fixed counters record source/constraint/adapter/support/index/replay/bootstrap work; no measurement is an elapsed-time or allocator-byte promise. |
| invariants | Counters are reported data. Managed helper calls use a category counter distinct from metrics.work; no mutable metric grants publication authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Declaration/field initialization performs no semantic validation. Consumers validate the actual values at their own boundary. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

```text
std::uint64_t work=0, source_rows=0, constraint_rows=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The cumulative selected work and source/constraint rows visited. |
| inputs / outputs | Stores/exposes the cumulative selected work and source/constraint rows visited. |
| invariants | Counters are reported data. Managed helper calls use a category counter distinct from metrics.work; no mutable metric grants publication authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

```text
std::uint64_t adapter_visits=0, adapter_rejections=0, derivation_changes=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The adapter attempts/rejections and admitted derivation changes during build. |
| inputs / outputs | Stores/exposes the adapter attempts/rejections and admitted derivation changes during build. |
| invariants | Counters are reported data. Managed helper calls use a category counter distinct from metrics.work; no mutable metric grants publication authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

```text
std::uint64_t native_keys=0, generalized_candidates=0, child_probes=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The native key, generalized candidate and child-probe build counts. |
| inputs / outputs | Stores/exposes the native key, generalized candidate and child-probe build counts. |
| invariants | Counters are reported data. Managed helper calls use a category counter distinct from metrics.work; no mutable metric grants publication authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

```text
std::uint64_t survivors=0, parent_keys=0, visible_keys=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The constructed survivor, parent-support and visible populations. |
| inputs / outputs | Stores/exposes the constructed survivor, parent-support and visible populations. |
| invariants | Counters are reported data. Managed helper calls use a category counter distinct from metrics.work; no mutable metric grants publication authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

```text
std::uint64_t storage_records=0, index_memberships=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The retained storage record/index membership counts. |
| inputs / outputs | Stores/exposes the retained storage record/index membership counts. |
| invariants | Counters are reported data. Managed helper calls use a category counter distinct from metrics.work; no mutable metric grants publication authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

```text
std::uint64_t replay_inputs=0, replay_events=0, replay_work=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The diagnostic insertion-replay inputs/events/work, distinct from direct construction. |
| inputs / outputs | Stores/exposes the diagnostic insertion-replay inputs/events/work, distinct from direct construction. |
| invariants | Counters are reported data. Managed helper calls use a category counter distinct from metrics.work; no mutable metric grants publication authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

```text
std::uint64_t live_bootstrap_work=0, live_rows=0, live_parent_rows=0, live_child_rows=0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | The live-provenance bootstrap work and row/parent/child populations. |
| inputs / outputs | Stores/exposes the live-provenance bootstrap work and row/parent/child populations. |
| invariants | Counters are reported data. Managed helper calls use a category counter distinct from metrics.work; no mutable metric grants publication authority. |
| ownership | Inline fixed fields only; copying these values allocates no container or text. No source/native owner is retained. |
| failure | Assignment adds no validation; aggregate construction/copy has the ownership costs stated here. |
| cost | Fixed-size initialization/copy/comparison; declaration itself performs no runtime scan or I/O. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

## B0005

[Lines 23–24](../../../../../../include/crown/runtime/initialization.hpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L24:sha256:034f49ecc21ca37f954f6499395e0efa3a9fba609e54d3d4a3892b801d9818fd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/runtime/initialization.hpp: opens namespace \`detail\`. Source comment: Shared cumulative build accounting; distinct from ordinary per-event caps. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Shared cumulative build accounting; distinct from ordinary per-event caps. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Shared cumulative build accounting; distinct from ordinary per-event caps. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0006

[Lines 25–31](../../../../../../include/crown/runtime/initialization.hpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void build_charge(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume cumulative initialization work before build action. |
| inputs / outputs | Checks uint64 overflow and remaining optional work cap, then increments metrics.work. |
| invariants | No subtraction underflow when prior work exceeds the cap; build work is separate from ordinary event grants. |
| ownership | Borrows mutable metrics and fixed options; no owner allocation. |
| failure | resource_limit before increment on cumulative overflow/cap failure; ordinary Error diagnostic allocation can itself fail. |
| cost | Fixed arithmetic/branches; no clock, per-category container or successful-path allocation. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

## B0007

[Lines 32–33](../../../../../../include/crown/runtime/initialization.hpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L33:sha256:7c318a3309a7cf02eff3044b0cd2fd84089d90e3d889354e159897e85867201c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`inline void build_metric(BuildMetrics& metrics,const BuildOptions& options,std::uint64_t& counter,std::uint64_t amount=1)\`: Use a category distinct from metrics.work. Its overflow can occur after cumulative charging; spent work is not refunded by that later failure. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/initialization.hpp:L34; use that declaration for the actual input/output shape. |
| invariants | The source note states: Use a category distinct from metrics.work. Its overflow can occur after cumulative charging; spent work is not refunded by that later failure. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | The note describes a failure or stop boundary: Use a category distinct from metrics.work. Its overflow can occur after cumulative charging; spent work is not refunded by that later failure. The comment adds no handler; the surrounding code determines the outcome. |
| cost | The note states a local cost boundary: Use a category distinct from metrics.work. Its overflow can occur after cumulative charging; spent work is not refunded by that later failure. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0008

[Lines 34–39](../../../../../../include/crown/runtime/initialization.hpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void build_metric(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge total build work then increment a category counter safely. |
| inputs / outputs | Calls build_charge first, checks independent counter overflow, then increments the passed category. |
| invariants | Use a managed category distinct from metrics.work. If independent counter overflow fails after charge, spent cumulative work remains charged; no budget refund. |
| ownership | Borrows metrics/options/category reference; callers preserve category invariants. |
| failure | Cumulative resource_limit can precede category work; counter overflow can follow the cumulative charge. Error allocation failures propagate. |
| cost | Fixed cumulative checks and one extra category overflow check; no success allocation or timing. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md) |

## B0009

[Lines 40–40](../../../../../../include/crown/runtime/initialization.hpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NativeSeed {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a native node seed with retained immutable tuple payload. |
| inputs / outputs | NodeId and AccountedTuple used by direct construction/rebuild. |
| invariants | Seed values alone are not a checked source/plan or publication token; the builder validates actual node/source use. |
| ownership | Inline NodeId plus move-only AccountedTuple, which retains shared AccountedLayout metadata and uniquely owns its compact AccountedRow block. |
| failure | Implicit NativeSeed copying is deleted because AccountedTuple is noncopyable. Member moves are noexcept; explicit tuple clone, when requested separately by a caller, can allocate and fail. |
| cost | Moves transfer layout/unique row ownership without materializing an ordinary Row. NativeSeed cannot be copied; an explicit tuple clone allocates/copies native payload. Final release retains actual native metadata/row cleanup cost. |
| Design | [include/crown/runtime/initialization.hpp](../../../../../../include/crown/runtime/initialization.hpp), [src/runtime/physical.cpp](../../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../../src/runtime/support.cpp), [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [include/crown/storage/accounted_layout.hpp](../../../../../../include/crown/storage/accounted_layout.hpp) |

## B0010

[Lines 41–42](../../../../../../include/crown/runtime/initialization.hpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L42:sha256:364de4e97229f1a80745fc7f7931c6bbd674acfe02841a34605d3dd74fea07ca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/runtime/initialization.hpp: closes \`namespace detail\`, \`namespace crown::runtime\`. Source comment: namespace detail namespace crown::runtime |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace detail namespace crown::runtime Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/runtime_initialization.md](../../../../../runtime_initialization.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
