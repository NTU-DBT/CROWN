# `include/crown/io/admission.hpp` — block usage map

[Source](../../../../../../include/crown/io/admission.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `1a609222e631877a9e4a99c1ab2c912a1a09a2cc1beeb13eb77f331c76b9da3a`. 10 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../../include/crown/io/admission.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Strict v1 options with optional parameter_types, parameter_values and limits. · [reviewed contract](#b0001) |

## B0001

[Lines 1–10](../../../../../../include/crown/io/admission.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Json write_admission(const frontend::AdmissionResult& result);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare JSON export for frontend admission results and import of admission options. |
| inputs / outputs | The writer accepts an \`AdmissionResult\`; the reader accepts option JSON with optional parameter declarations, values, and binding/normalization/recognition limits. |
| invariants | The emitted scope is frontend and structure, with execution marked not lowered. Missing options retain C++ defaults; imported fields are strict and versioned. |
| ownership | The writer returns an owning JSON DOM. The options reader returns ordinary option/value vectors independent of its input string. |
| failure | Unknown fields, wrong schema versions, malformed option types, or invalid parameter documents raise document errors; writer formatting can reject invalid supplied enums through delegated serializers. |
| cost | Both operations use ordinary JSON/option allocations. Work limits are passed onward as selected compiler counters and do not cap parse/DOM or all allocation costs. |
| Design | [include/crown/io/admission.hpp §public declarations](../../../../../../include/crown/io/admission.hpp), [src/io/admission.cpp §write_admission/read_admission_options](../../../../../../src/io/admission.cpp), [src/frontend/admission.cpp §admission scope](../../../../../../src/frontend/admission.cpp), [docs/sql_admission.md §frontend admission](../../../../../sql_admission.md) |
