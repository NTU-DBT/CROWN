# `include/crown/frontend/admission.hpp` — block usage map

[Source](../../../../../../include/crown/frontend/admission.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Convert the admitted SQL fragment into an exact typed equality CQ and explicit SQL output semantics.

Snapshot SHA-256: `3b8b61c8f4998a5e4cdf160145530fbd8a630f8d149014c7fa3ba23307bf29f7`. 41 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [frontend](../../../../subsystem_contracts.md#frontend). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/sql_support.md](../../../../../sql_support.md), [docs/sql_parser.md](../../../../../sql_parser.md), [docs/sql_binding.md](../../../../../sql_binding.md), [docs/sql_normalization.md](../../../../../sql_normalization.md), [docs/sql_admission.md](../../../../../sql_admission.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../../include/crown/frontend/admission.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–7](../../../../../../include/crown/frontend/admission.hpp#L7) | Type/record definition: enum class AdmissionStatus |  · [reviewed contract](#b0002) |
| [B0003 · 8–8](../../../../../../include/crown/frontend/admission.hpp#L8) | Type/record definition: enum class AdmissionRoute |  · [reviewed contract](#b0003) |
| [B0004 · 9–14](../../../../../../include/crown/frontend/admission.hpp#L9) | Type/record definition: struct AdmissionOptions |  · [reviewed contract](#b0004) |
| [B0005 · 15–19](../../../../../../include/crown/frontend/admission.hpp#L15) | Type/record definition: struct AdmissionLimits |  · [reviewed contract](#b0005) |
| [B0006 · 20–24](../../../../../../include/crown/frontend/admission.hpp#L20) | Type/record definition: struct AdmissionWork |  · [reviewed contract](#b0006) |
| [B0007 · 25–34](../../../../../../include/crown/frontend/admission.hpp#L25) | Type/record definition: struct AdmissionResult |  · [reviewed contract](#b0007) |
| [B0008 · 35–41](../../../../../../include/crown/frontend/admission.hpp#L35) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Frontend + structural admission only: this does not lower a physical plan, · [reviewed contract](#b0008) |

## B0001

[Lines 1–6](../../../../../../include/crown/frontend/admission.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:8db61e5b5b98b6c54d7bf8a0a6bd43fa1443fd75029e6e7db9c022b6c45a709d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Header guard and frontend normalization/planner-recognition dependencies, followed by the crown::frontend namespace opening for admission result and option declarations. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The header guard prevents repeat inclusion in a translation unit; imported declarations determine compile-time names. The note/type comments in this span are guidance and do not add runtime validation or a capability. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path is introduced by the guard/imports; incompatible or missing declarations fail during compilation or linking. |
| cost | Preprocessor/compiler work only for these lines; the guard adds no per-operation runtime work. |
| Design | [include/crown/frontend/admission.hpp](../../../../../../include/crown/frontend/admission.hpp), [docs/code_specs/files/include/crown/frontend/admission.hpp.md](admission.hpp.md), [docs/sql_admission.md](../../../../../sql_admission.md), [docs/sql_normalization.md](../../../../../sql_normalization.md) |

## B0002

[Lines 7–7](../../../../../../include/crown/frontend/admission.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class AdmissionStatus
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the seven complete admission outcomes. |
| inputs / outputs | Values: admitted, syntax/semantic/unsupported rejection, cyclic/non-free-connex shape, and resource limit. |
| invariants | A status is a frontend/structural result only; it does not mean a physical plan or maintained runtime exists. |
| ownership | Scoped enum scalar. |
| failure | No enum validation in the type. APIs reject an unknown cast value when converted to text. |
| cost | Fixed-size value. |
| Design | [docs/sql_admission.md](../../../../../sql_admission.md) |

## B0003

[Lines 8–8](../../../../../../include/crown/frontend/admission.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class AdmissionRoute
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish a structurally free-connex route from a proven constant-empty route. |
| inputs / outputs | \`free_connex\` or \`constant_empty\`. |
| invariants | Constant-empty still retains actual shape analysis; routes are only set on admitted results. |
| ownership | Scoped enum scalar. |
| failure | No enum validation in the type. |
| cost | Fixed-size value. |
| Design | [docs/sql_admission.md](../../../../../sql_admission.md) |

## B0004

[Lines 9–14](../../../../../../include/crown/frontend/admission.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AdmissionOptions
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle inputs and limits for source SQL admission. |
| inputs / outputs | Binding options, owned specialized SQL values, normalization limits, and planner recognition limits. |
| invariants | Binding parameter declarations and normalization values are distinct; stage limits are applied by their respective stages. |
| ownership | Owns the parameter vector and option values; APIs receive the record by const reference. |
| failure | No aggregate-level validation; each stage validates its own inputs. |
| cost | Fixed-size limit records plus parameter vector/value storage; work follows selected pipeline. |
| Design | [docs/sql_admission.md](../../../../../sql_admission.md), [docs/sql_binding.md](../../../../../sql_binding.md), [docs/sql_normalization.md](../../../../../sql_normalization.md) |

## B0005

[Lines 15–19](../../../../../../include/crown/frontend/admission.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AdmissionLimits
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report effective binding, normalization, and recognition limits. |
| inputs / outputs | Three limit structs in/out with the result. |
| invariants | The field names retain stage boundaries; a grounding host cap may tighten stored normalization limits for legacy v1. |
| ownership | Owns only scalar/optional limit values. |
| failure | No aggregate validation. |
| cost | Fixed-size value. |
| Design | [docs/sql_admission.md](../../../../../sql_admission.md) |

## B0006

[Lines 20–24](../../../../../../include/crown/frontend/admission.hpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AdmissionWork
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report completed/attempted abstract work by stage. |
| inputs / outputs | Optional uint64 binding, normalization, and recognition counts. |
| invariants | Incomplete stages may remain absent; recognition includes consumed work on resource stop. Counts are not elapsed time or bytes. |
| ownership | Owns optional scalar counters. |
| failure | No arithmetic or validation occurs in the record. |
| cost | Fixed-size value. |
| Design | [docs/sql_admission.md](../../../../../sql_admission.md) |

## B0007

[Lines 25–34](../../../../../../include/crown/frontend/admission.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AdmissionResult
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one admission status, diagnostics, normalized program, structural witness, route, limits, and work. |
| inputs / outputs | Status defaults to semantic_error; phase, diagnostic, program, structure, and route are optional; limits/work are reported. |
| invariants | A rejected/incomplete request must not be presented as having a completed structural class/route; a successful result remains frontend/structure only. |
| ownership | Owns strings, normalized program, diagnostics, and structural analysis. |
| failure | The record does not enforce field correlations; \`admit_sql\`/\`admit_normalized\` establish them. Internal contract errors may escape rather than populate a result. |
| cost | Moves/copies potentially large normalized AST/CQ and GYO witness data; costs belong to the producing stages. |
| Design | [docs/sql_admission.md](../../../../../sql_admission.md), [docs/sql_normalization.md](../../../../../sql_normalization.md) |

## B0008

[Lines 35–41](../../../../../../include/crown/frontend/admission.hpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] AdmissionResult admit_sql(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare SQL and normalized-artifact admission APIs and status serialization. |
| inputs / outputs | \`admit_sql\` accepts source/catalog/options; \`admit_normalized\` accepts an owned v1/v2 normalized program plus recognition/grounding caps; name conversion accepts an enum. |
| invariants | The API boundary documents frontend plus structural admission only. Normalized input must already be producer/reader validated; legacy v1 is grounded before classification. |
| ownership | Results and input artifact are value-owning; no parser-owned pointer crosses the API. |
| failure | Each function’s declared diagnostics/errors are defined by its implementation; declarations themselves do no validation. |
| cost | Calls can parse, copy, normalize, and recognize a complete query; resource cost is bounded by stage limits except no global memory/wall-time guarantee. |
| Design | [docs/sql_admission.md](../../../../../sql_admission.md), [src/frontend/admission.cpp](../../../../../../src/frontend/admission.cpp) |
