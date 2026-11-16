# `src/io/compiler_plan_artifact.cpp` — block usage map

[Source](../../../../../src/io/compiler_plan_artifact.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Read/write explicit compiler-owned plan artifacts at the native admission boundary.

Snapshot SHA-256: `ccdcb96d964bf00a1103e86f495398a4ca32dfd8bf4f4c58deff8e06c5a8e8fa`. 55 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/io/compiler_plan_artifact.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Prepare already serialized ordinary DTO scratch; this caps retained wire bytes, · [reviewed contract](#b0001) |
| [B0002 · 10–12](../../../../../src/io/compiler_plan_artifact.cpp#L10) | Callable definition: void size(std::string_view bytes,const CompilerArtifactLimits& limits) | calls empty, Error; source comment (unverified): // Prepare already serialized ordinary DTO scratch; this caps retained wire bytes, · [reviewed contract](#b0002) |
| [B0003 · 13–13](../../../../../src/io/compiler_plan_artifact.cpp#L13) | Explanatory comments or spacing. | source comment (unverified): // Snapshot the whole supplied compiler account, including other retained owners. · [reviewed contract](#b0003) |
| [B0004 · 14–18](../../../../../src/io/compiler_plan_artifact.cpp#L14) | Callable definition: CompilerArtifactStatistics capture_statistics(const resource::MemoryAccount& account,std::size_t bytes,Clock::time_point started) | calls Clock::now, Error, count, statistics; returns {bytes,static_cast&lt;std::uint64_t&gt;(std::chrono::duration_cast&lt;std::chrono::nanoseconds&gt;(ended-starte…; source comment (unverified): // Snapshot the whole supplied compiler account, including other retained owners. · [reviewed contract](#b0004) |
| [B0005 · 19–21](../../../../../src/io/compiler_plan_artifact.cpp#L19) | Callable definition: resource::AccountedText retain(const resource::MemoryAccount& account,std::string_view bytes) | calls resource::AccountedText::copy_of; returns resource::AccountedText::copy_of(account,bytes,{resource::MemoryOwnerKind::immutable_metadata,0},re…; growth copy_of · [reviewed contract](#b0005) |
| [B0006 · 22–22](../../../../../src/io/compiler_plan_artifact.cpp#L22) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0006) |
| [B0007 · 23–31](../../../../../src/io/compiler_plan_artifact.cpp#L23) | Callable definition: CompilerPlanArtifact CompilerPlanArtifact::prepare(const resource::MemoryAccount& account,const PhysicalPlan& plan,CompilerArtifa… | calls Clock::now, write_physical, dump, size; returns CompilerPlanArtifact(std::move(program),std::move(bytes),measured) · [reviewed contract](#b0007) |
| [B0008 · 32–39](../../../../../src/io/compiler_plan_artifact.cpp#L32) | Callable definition: CompilerPlanArtifact CompilerPlanArtifact::replay(const resource::MemoryAccount& account,std::string_view serialized,CompilerArti… | calls Clock::now, size, read_physical, CompiledProgram::compile; returns CompilerPlanArtifact(std::move(program),std::move(bytes),capture_statistics(account,serialized.size… · [reviewed contract](#b0008) |
| [B0009 · 40–54](../../../../../src/io/compiler_plan_artifact.cpp#L40) | Callable definition: CompilerPlanArtifact CompilerPlanArtifact::prepare(const resource::MemoryAccount& account,const CompiledProgram& source,CompilerA… | calls Clock::now, Error, PhysicalPlan::from_compiled, normalized; returns CompilerPlanArtifact(std::move(program),std::move(bytes),measured) · [reviewed contract](#b0009) |
| [B0010 · 55–55](../../../../../src/io/compiler_plan_artifact.cpp#L55) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0010) |

## B0001

[Lines 1–9](../../../../../src/io/compiler_plan_artifact.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:c861ab2c150fd3eaef24f2d56f36243e2d3f7b2f2b1b2cc8c5df032ef935ce0f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/io/compiler_plan_artifact.hpp, crown/api/error.hpp, chrono) and opens crown::io scope for the declarations or definitions that follow. Embedded source note records intended usage: Prepare already serialized ordinary DTO scratch; this caps retained wire bytes, not total compiler allocation. Replay applies it before parsing caller bytes. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/code_specs/files/src/io/compiler_plan_artifact.cpp.md](compiler_plan_artifact.cpp.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 10–12](../../../../../src/io/compiler_plan_artifact.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void size(std::string_view bytes,const CompilerArtifactLimits& limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check retained artifact wire length at the compiler boundary. |
| inputs / outputs | Rejects empty bytes or byte length greater than CompilerArtifactLimits.bytes. |
| invariants | Prepare has already materialized its ordinary serialized string before this check; replay checks caller wire bytes before parsing. This does not cap temporary DOM/compiler allocation. |
| ownership | Borrows bytes/limits for one scalar check; reserves no memory. |
| failure | Rejects with public compiler_artifact_limit, without clamping or returning truncated text. |
| cost | Fixed empty/length comparisons; no parse/hash/byte scan or successful allocation. |
| Design | [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [tests/unit/compiler_plan_artifact_test.cpp](../../../../../tests/unit/compiler_plan_artifact_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 13–13](../../../../../src/io/compiler_plan_artifact.cpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L13:sha256:b9511b48ab3b127cc84126d7eac70f118864b3ab72d5b367ca102bbe6f377d30
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Snapshot the whole supplied compiler account, including other retained owners. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at src/io/compiler_plan_artifact.cpp lines 11-15; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/code_specs/files/src/io/compiler_plan_artifact.cpp.md](compiler_plan_artifact.cpp.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 14–18](../../../../../src/io/compiler_plan_artifact.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompilerArtifactStatistics capture_statistics(const resource::MemoryAccount& account,std::size_t bytes,Clock::time_point started) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture boundary timing and whole compiler-account statistics. |
| inputs / outputs | Reads ending steady clock, rejects regression and returns retained bytes, elapsed ns, its two explicit boundary clock reads and account.statistics(). |
| invariants | compiler_memory includes the entire supplied account's current/history/peak, including other retained owners. It is neither exclusive artifact usage nor a total process/DTO or phase-local peak. |
| ownership | Only fixed statistics values escape; account/program ownership is held by the artifact separately. |
| failure | Clock regression or invalid account access rejects; no fabricated zero timing or retry. |
| cost | One ending clock read and fixed statistics copy. Nested compiler components may have their own costs/clocks; clock_reads=2 counts this wrapper's explicit pair. |
| Design | [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [tests/unit/compiler_plan_artifact_test.cpp](../../../../../tests/unit/compiler_plan_artifact_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 19–21](../../../../../src/io/compiler_plan_artifact.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::AccountedText retain(const resource::MemoryAccount& account,std::string_view bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain exact compiler artifact bytes as a real funded text allocation. |
| inputs / outputs | Copies bytes under immutable_metadata owner/purpose into AccountedText with its terminator and real account framing. |
| invariants | The same supplied compiler account funds this text; it is not an accounting ticket or a native execution grant. |
| ownership | Result owns copied bytes independently of serialized temporary/caller input. |
| failure | Size overflow, account cap or allocator failure propagates before a retained value is returned. |
| cost | O(serialized bytes) deep copy plus actual character request/framing; empty text is rejected earlier by size(). |
| Design | [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [tests/unit/compiler_plan_artifact_test.cpp](../../../../../tests/unit/compiler_plan_artifact_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 22–22](../../../../../src/io/compiler_plan_artifact.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/code_specs/files/src/io/compiler_plan_artifact.cpp.md](compiler_plan_artifact.cpp.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 23–31](../../../../../src/io/compiler_plan_artifact.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompilerPlanArtifact CompilerPlanArtifact::prepare(const resource::MemoryAccount& account,const PhysicalPlan& plan,CompilerArtifactLimits limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a compiler artifact from an already checked physical plan. |
| inputs / outputs | Times write_physical/dump, byte check, CompiledProgram::compile under compiler account and retained byte copy; destroys serialized temporary before sampling statistics. |
| invariants | PhysicalPlan authority precedes this call. No query/session mutation occurs; native execution must later freeze/import into its original receiving account/grant. |
| ownership | Returned artifact owns funded executable metadata and exact bytes. Temporary ordinary JSON/string/PhysicalPlan compiler storage is outside the retained compiler account. |
| failure | Serialization/byte/domain/compile/account/allocation failure returns no artifact and releases private partial owners through RAII. |
| cost | Complete physical serialization and native metadata compile/copy plus teardown and two explicit clock reads. Byte acceptance is checked after serialization; no global compiler memory/CPU cap is implied. |
| Design | [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [tests/unit/compiler_plan_artifact_test.cpp](../../../../../tests/unit/compiler_plan_artifact_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 32–39](../../../../../src/io/compiler_plan_artifact.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompilerPlanArtifact CompilerPlanArtifact::replay(const resource::MemoryAccount& account,std::string_view serialized,CompilerArtifactLimits limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay complete physical artifact semantics before constructing executable metadata. |
| inputs / outputs | Checks input byte grant, read_physical replays source/catalog/tree/options under replay limits, compiles into supplied account, then retains the original input bytes and captures cost. |
| invariants | Serialized digests/flags alone have no execution authority; checked PhysicalPlan replay and CompiledProgram construction establish it. Exact supplied wire bytes, including formatting, are retained. |
| ownership | Input string_view is borrowed only during replay/copy; result owns program metadata and retained text under compiler account. Ordinary parse/lowering DTOs are temporary outside native accounting. |
| failure | Wire/binding/replay/resource/account/allocation errors propagate with no partial fallback program; constructed intermediates are released. |
| cost | Full input parse, canonical lowering/binding comparison, native compilation and byte copy. Temporary plan teardown is included before final measured account snapshot. |
| Design | [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [tests/unit/compiler_plan_artifact_test.cpp](../../../../../tests/unit/compiler_plan_artifact_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 40–54](../../../../../src/io/compiler_plan_artifact.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompilerPlanArtifact CompilerPlanArtifact::prepare(const resource::MemoryAccount& account,const CompiledProgram& source,CompilerArtifactLimits limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export and reconstruct a checked compiled source at an explicit cold compiler boundary. |
| inputs / outputs | Requires nonempty source; exports PhysicalPlan, re-lowers normalized or direct CQ with replay caps, compares complete physical/source identities, serializes, compiles and retains bytes under compiler account. |
| invariants | Typed source authority and canonical reconstruction precede digest equality. This boundary is never implicit native update/publication work and does not select an arbitrary new physical plan. |
| ownership | Source is borrowed; compiler DTO export/lowering is temporary ordinary ownership. New executable/text belongs to supplied compiler account and must be imported into receiving native account separately. |
| failure | Empty source, reconstruction identity mismatch, cap/byte/domain/account/allocation failure returns no artifact; no source/session mutation. |
| cost | Full metadata export, canonical validation/lowering, two identity comparisons, serialization, compile, copied bytes and temporary teardown. Payback includes this existing compiler cost; no constant-time clone or global memory guarantee. |
| Design | [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [tests/unit/compiler_plan_artifact_test.cpp](../../../../../tests/unit/compiler_plan_artifact_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 55–55](../../../../../src/io/compiler_plan_artifact.cpp#L55); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L55:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/code_specs/files/src/io/compiler_plan_artifact.cpp.md](compiler_plan_artifact.cpp.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/query_memory.md](../../../../query_memory.md) |
