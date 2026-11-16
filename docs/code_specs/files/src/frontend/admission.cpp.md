# `src/frontend/admission.cpp` — block usage map

[Source](../../../../../src/frontend/admission.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics.

Snapshot SHA-256: `8c169d7e56dcb0f27d89c68b915da94139ebf1e355d2811259ad3cdd39b8c786`. 80 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../sql_support.md), [docs/sql_parser.md](../../../../sql_parser.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_admission.md](../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/frontend/admission.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–15](../../../../../src/frontend/admission.cpp#L8) | Callable definition: void rejection(AdmissionResult& result, BindingDiagnostic failure) | calls std::move, Error, starts_with · [reviewed contract](#b0002) |
| [B0003 · 16–17](../../../../../src/frontend/admission.cpp#L16) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0003) |
| [B0004 · 18–53](../../../../../src/frontend/admission.cpp#L18) | Callable definition: AdmissionResult admit_normalized(NormalizedSql program, planner::RecognitionLimits limits, NormalizeLimits grounding_limits) | calls normalize_sql, rejection, std::move, Error; returns result; result · [reviewed contract](#b0004) |
| [B0005 · 54–54](../../../../../src/frontend/admission.cpp#L54) | Explanatory comments or spacing. |  |
| [B0006 · 55–66](../../../../../src/frontend/admission.cpp#L55) | Callable definition: AdmissionResult admit_sql(std::string_view source, const Catalog& catalog, const AdmissionOptions& options) | calls bind_sql, rejection, std::move, normalize_sql; returns result; result · [reviewed contract](#b0006) |
| [B0007 · 67–67](../../../../../src/frontend/admission.cpp#L67) | Explanatory comments or spacing. |  |
| [B0008 · 68–79](../../../../../src/frontend/admission.cpp#L68) | Callable definition: std::string admission_status_name(AdmissionStatus status) | calls Error; returns @; @ · [reviewed contract](#b0008) |
| [B0009 · 80–80](../../../../../src/frontend/admission.cpp#L80) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::frontend · [reviewed contract](#b0009) |

## B0001

[Lines 1–7](../../../../../src/frontend/admission.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:941f396267bd38e36da8497ca244c59c01e3b9fb2f12729c5bd5966807ad6658
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports compile-time dependencies (crown/frontend/admission.hpp, crown/api/error.hpp, utility) and opens crown::frontend scope for the declarations or definitions that follow. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/frontend/admission.cpp](../../../../../src/frontend/admission.cpp), [docs/code_specs/files/src/frontend/admission.cpp.md](admission.cpp.md), [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0002

[Lines 8–15](../../../../../src/frontend/admission.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rejection(AdmissionResult& result, BindingDiagnostic failure)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map a binding/normalization/recognition diagnostic into admission phase and status. |
| inputs / outputs | Mutable result plus owned binding diagnostic in; result phase/status/diagnostic updated. |
| invariants | \`resource_limit\` has precedence; syntax phase maps to syntax error; \`unsupported_*\` maps to unsupported semantics; other declared diagnostics map to semantic error. \`invalid_ast\` denotes an internal invariant failure and is thrown as \`binding_contract\`. |
| ownership | Moves phase and diagnostic into result; reads code before moving the diagnostic. |
| failure | The \`invalid_ast\` exception path is required to avoid reporting malformed internal AST as a user semantic rejection. Other failure paths return a structured diagnostic. |
| cost | Constant classification and moves, plus error-string handling on the invariant path. No query or catalog scan. |
| Design | [docs/sql_admission.md](../../../../sql_admission.md), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp) |

## B0003

[Lines 16–17](../../../../../src/frontend/admission.cpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L17:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the anonymous namespace at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/admission.cpp](../../../../../src/frontend/admission.cpp), [docs/code_specs/files/src/frontend/admission.cpp.md](admission.cpp.md), [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0004

[Lines 18–53](../../../../../src/frontend/admission.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AdmissionResult admit_normalized(NormalizedSql program, planner::RecognitionLimits limits, NormalizeLimits grounding_limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ground legacy normalized v1 to v2 when needed, then report bounded structural admission. |
| inputs / outputs | \`NormalizedSql\` that callers must already have producer/reader validated, recognition limits, and optional host grounding limit in; owned status, program, witnesses, route, limits, and work out. |
| invariants | The API precondition is producer/reader-validated v1 or v2 input; implementation checks schema version and grounds v1 using stored parameters/limits plus the tighter explicit/stored work cap, but does not replay-validate v2 here. Recognition must complete before a class or route is returned. Contradictions retain actual structural classification and use \`constant_empty\`. |
| ownership | Program is passed by value and moved into the result; returned program and analysis own their data. |
| failure | Grounding diagnostics use \`rejection\`; invalid version/invariant throws \`admission_contract\`. Recognition exhaustion returns \`resource_limit\` without partial class. Completed cyclic/non-free-connex results retain diagnostics and their explicit statuses. |
| cost | Optional complete v1 grounding plus bounded GYO analysis; existing binding/normalization counts are reported, not rerun for v2. Recognition work is separately counted; no physical plan, runtime, allocator bytes, or SQL proof is produced. |
| Design | [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp) |

## B0006

[Lines 55–66](../../../../../src/frontend/admission.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AdmissionResult admit_sql(std::string_view source, const Catalog& catalog, const AdmissionOptions& options)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the SQL binding, normalization, and structural admission pipeline. |
| inputs / outputs | Borrowed SQL, catalog, parameters and stage limits in; owned \`AdmissionResult\` out. |
| invariants | First frontend failure stops the pipeline. Successful binding preserves requested SQL semantics; successful normalization supplies the core used for GYO admission. This does not execute SQL or lower a physical plan. |
| ownership | Copies/owns intermediate binding and normalized program via stage APIs; final result owns normalized program and witnesses. |
| failure | Binding and normalization diagnostics are mapped through \`rejection\`; their internal invariant exceptions propagate. Recognition and contract errors follow \`admit_normalized\`. |
| cost | Parse and source/catalog validation, binder, normalization, and recognition costs are composed; result counters are abstract per-stage work, not time/memory. Parsing, catalog-copy/validation overhead is not a separate \`AdmissionWork\` field. |
| Design | [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp) |

## B0008

[Lines 68–79](../../../../../src/frontend/admission.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string admission_status_name(AdmissionStatus status)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the stable text spelling for one admission status. |
| inputs / outputs | One \`AdmissionStatus\` enum value in; corresponding owned string out. |
| invariants | The switch covers all seven declared statuses. An out-of-range enum value is an internal contract error. |
| ownership | Returns string by value; no shared mutable storage. |
| failure | Unknown status throws \`admission_contract\`. |
| cost | Fixed case dispatch plus string result construction. |
| Design | [docs/sql_admission.md](../../../../sql_admission.md), [include/crown/frontend/admission.hpp](../../../../../include/crown/frontend/admission.hpp) |

## B0009

[Lines 80–80](../../../../../src/frontend/admission.cpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L80:sha256:2fc33ff8830b8cd06d6971e8e31b29a8803f152d87e09a3fc4092b3efecdac93
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::frontend at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/frontend/admission.cpp](../../../../../src/frontend/admission.cpp), [docs/code_specs/files/src/frontend/admission.cpp.md](admission.cpp.md), [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |
