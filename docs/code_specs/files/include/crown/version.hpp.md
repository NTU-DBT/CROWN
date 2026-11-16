# `include/crown/version.hpp` — block usage map

[Source](../../../../../include/crown/version.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs.

Snapshot SHA-256: `6140a5c06929b463983729af9614a8d5767dd6941e7d899bf6a444e1fefa47bc`. 6 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_identity.md](../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../include/crown/version.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown · [reviewed contract](#b0001) |

## B0001

[Lines 1–6](../../../../../include/crown/version.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline constexpr std::string_view version="0.1.0";
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the compile-time software version and public API version labels. |
| inputs / outputs | \`version\` is the string view \`0.1.0\`; \`public_api_version\` is unsigned value \`1\`. |
| invariants | These constants do not negotiate or validate CQ, certificate, checkpoint, descriptor, or other independent wire versions. |
| ownership | The string view refers to a static string literal; the integer is a compile-time scalar. |
| failure | Reading these constants has no failure path; compatibility checks must use the relevant artifact/API-specific version contract. |
| cost | Compile-time constants with no dynamic allocation or runtime validation. |
| Design | [include/crown/version.hpp §version constants](../../../../../include/crown/version.hpp), [CMakeLists.txt §project version](../../../../../CMakeLists.txt), [docs/schema_evolution.md §artifact-specific schema versions](../../../../schema_evolution.md) |
