# `src/io/admission.cpp` — block usage map

[Source](../../../../../src/io/admission.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `72eb4f9a6b15fb960ee88077c86fd13978f43871092c33a2a580b33cc1401747`. 70 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/io/admission.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 11–11](../../../../../src/io/admission.cpp#L11) | Callable definition: Json optional_integer(std::optional&lt;std::uint64_t&gt; value) | calls Json; returns value ? Json(*value) : Json(nullptr) · [reviewed contract](#b0002) |
| [B0003 · 12–13](../../../../../src/io/admission.cpp#L12) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0003) |
| [B0004 · 14–32](../../../../../src/io/admission.cpp#L14) | Callable definition: Json write_admission(const frontend::AdmissionResult& result) | calls frontend::admission_status_name, optional_integer, write_sql_binding, at; returns output; source comment (unverified): // Diagnostic compiler DTO: frontend/structure status never lowers or starts execution. · [reviewed contract](#b0004) |
| [B0005 · 33–33](../../../../../src/io/admission.cpp#L33) | Explanatory comments or spacing. |  |
| [B0006 · 34–69](../../../../../src/io/admission.cpp#L34) | Callable definition: frontend::AdmissionOptions read_admission_options(std::string_view text) | calls detail::parse_json, detail::fields, detail::version, at; returns options; options · [reviewed contract](#b0006) |
| [B0007 · 70–70](../../../../../src/io/admission.cpp#L70) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0007) |

## B0001

[Lines 1–10](../../../../../src/io/admission.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:cd6b402bd675389fb21954a4a3c75d35a7f741071618cdf4842deb16378efeaf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/io/admission.hpp, crown/io/binding.hpp, crown/io/normalization.hpp, crown/io/recognition.hpp, json.hpp, limits) and opens crown::io scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/admission.cpp](../../../../../src/io/admission.cpp), [docs/code_specs/files/src/io/admission.cpp.md](admission.cpp.md), [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_parser.md](../../../../sql_parser.md) |

## B0002

[Lines 11–11](../../../../../src/io/admission.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json optional_integer(std::optional<std::uint64_t> value) { return value ? Json(*value) : Json(nullptr); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an optional phase work quantity without inventing a measurement. |
| inputs / outputs | Returns an exact uint64 JSON number when present and JSON null when absent. |
| invariants | Absent means unavailable/not run rather than zero or unlimited execution work. |
| ownership | Owns only the returned JSON scalar. |
| failure | JSON scalar construction failures propagate; no phase is executed. |
| cost | Fixed scalar/null construction; no source/program traversal. |
| Design | [src/io/admission.cpp](../../../../../src/io/admission.cpp), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp), [src/frontend/admission.cpp](../../../../../src/frontend/admission.cpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [tests/integration/admission.py](../../../../../tests/integration/admission.py), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 12–13](../../../../../src/io/admission.cpp#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L13:sha256:1a2b20dc2c40fa9e343f416cea603f20773bf78cc451665cd619e35d574510f7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. Trailing source note states: Diagnostic compiler DTO: frontend/structure status never lowers or starts execution. It remains prose guidance, not a certified executable claim. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. Any trailing comment in this block is guidance only and adds no runtime invariant. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/admission.cpp](../../../../../src/io/admission.cpp), [docs/code_specs/files/src/io/admission.cpp.md](admission.cpp.md), [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_parser.md](../../../../sql_parser.md) |

## B0004

[Lines 14–32](../../../../../src/io/admission.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Json write_admission(const frontend::AdmissionResult& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export frontend/structure admission results while keeping execution explicitly unlowered. |
| inputs / outputs | Builds schema-v1 status/phase/route/diagnostic/work/limits; serializes optional normalized program and structural analysis when the corresponding inputs exist. |
| invariants | admission_scope remains frontend_and_structure and execution_status remains not_lowered. No physical lowering, minimum-height verification or runtime construction occurs. |
| ownership | The returned ordinary owning JSON tree copies its exposed strings/arrays/objects; it retains no live runtime, grant or typed proof capability. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Ordinary DOM construction and deep program/catalog/structure exports; diagnostic conversion constructs a binding-diagnostic envelope. Cost scales with supplied payloads, not merely fixed status fields. |
| Design | [src/io/admission.cpp](../../../../../src/io/admission.cpp), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp), [src/frontend/admission.cpp](../../../../../src/frontend/admission.cpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [tests/integration/admission.py](../../../../../tests/integration/admission.py), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 34–69](../../../../../src/io/admission.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
frontend::AdmissionOptions read_admission_options(std::string_view text) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read explicit parameter specialization and per-phase operational admission limits. |
| inputs / outputs | Parses strict versioned fields; optional type/value arrays are wrapped and delegated to existing readers, and binding/normalization/recognition limits overwrite defaults only when present. |
| invariants | Null work_limit means unbounded for that phase, zero remains an explicit zero grant. Expression/recursion limits must fit host size_t. This only constructs options, not an admitted program. |
| ownership | Returned options own parameter metadata/values; input JSON and synthesized wrapper strings are temporary ordinary compiler DTOs. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Full JSON parse plus wrapper DOM/dump/reparse for parameter types/values, scalar checks and deep parameter/catalog copies. No native memory account or global byte/CPU cap is installed. |
| Design | [src/io/admission.cpp](../../../../../src/io/admission.cpp), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp), [src/frontend/admission.cpp](../../../../../src/frontend/admission.cpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [tests/integration/admission.py](../../../../../tests/integration/admission.py), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

```text
  const auto work = [](const Json& node, std::optional<std::uint64_t>& target) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply an explicitly present phase work limit without conflating null and zero. |
| inputs / outputs | Missing work_limit leaves target unchanged; null clears the optional; otherwise reads exact nonnegative uint64. |
| invariants | The same operation configures each phase option, not a shared runtime allowance or consumed counter. |
| ownership | Mutates the local options scalar only; captures no retained input. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Fixed field/presence/type lookup and scalar assignment; no phase traversal. |
| Design | [src/io/admission.cpp](../../../../../src/io/admission.cpp), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp), [src/frontend/admission.cpp](../../../../../src/frontend/admission.cpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [tests/integration/admission.py](../../../../../tests/integration/admission.py), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

```text
    const auto size = [](const Json& node,const char* name,std::size_t& target) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound host-sized binding limits before narrowing conversion. |
| inputs / outputs | Missing field preserves its default; present exact unsigned value above SIZE_MAX rejects before static_cast. |
| invariants | Limit parsing performs no expression allocation/admission and does not silently clamp or treat zero as absent. |
| ownership | Updates only local options metadata; diagnostic paths are borrowed synchronously. |
| failure | Shape/type/version, parser/serialization or ordinary allocation failures propagate; this boundary adds no catch, fallback or retry. |
| cost | Fixed range check and cast on success; public diagnostic construction can allocate on rejection. |
| Design | [src/io/admission.cpp](../../../../../src/io/admission.cpp), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp), [src/frontend/admission.cpp](../../../../../src/frontend/admission.cpp), [src/io/binding.cpp](../../../../../src/io/binding.cpp), [tests/unit/admission_test.cpp](../../../../../tests/unit/admission_test.cpp), [tests/integration/admission.py](../../../../../tests/integration/admission.py), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 70–70](../../../../../src/io/admission.cpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L70:sha256:a992a30ac7c9748c33994a213cb5eed12f62a6204d01f8b49f69db451a145039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/admission.cpp](../../../../../src/io/admission.cpp), [docs/code_specs/files/src/io/admission.cpp.md](admission.cpp.md), [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_parser.md](../../../../sql_parser.md) |
