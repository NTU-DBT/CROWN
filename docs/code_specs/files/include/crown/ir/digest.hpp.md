# `include/crown/ir/digest.hpp` — block usage map

[Source](../../../../../../include/crown/ir/digest.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Compute and encode canonical SHA-256 digests used for artifact identity.

Snapshot SHA-256: `9ed5125628296ac8c9681898e013c69524533ccb7e1ff4924db814b4981a0515`. 12 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_identity.md](../../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/ir/digest.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures. | source comment (unverified): // SHA-256 of arbitrary bytes, lowercase hexadecimal, per FIPS 180-4. · [reviewed contract](#b0001) |

## B0001

[Lines 1–12](../../../../../../include/crown/ir/digest.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::string sha256(std::string_view bytes);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose SHA-256 helpers for arbitrary byte strings in owning and fixed-width forms. |
| inputs / outputs | Both consume \`string_view\`; \`sha256\` returns 64 lowercase hex characters in \`std::string\`, while \`sha256_fixed\` returns the same bytes in \`array&lt;char,64&gt;\`. |
| invariants | Digest input is byte-preserving, with no typed/document interpretation. This helper alone is not a query identity, proof, or authenticity check. |
| ownership | The view is borrowed for the call; fixed result owns inline bytes and string result owns its allocation. |
| failure | Inputs outside the implementation’s 64-bit bit-length domain throw \`resource_limit\`; allocation for the string result can also fail. |
| cost | Processes input bytes in SHA-256 blocks with fixed local scratch; time scales with input length. The \`std::string\` result may allocate; fixed result does not need a dynamic result buffer. |
| Design | [include/crown/ir/digest.hpp §public API](../../../../../../include/crown/ir/digest.hpp), [src/ir/digest.cpp §SHA-256 implementation](../../../../../../src/ir/digest.cpp), [docs/query_identity.md §identity digests](../../../../../query_identity.md), [docs/scalars.md §noncryptographic value hashes](../../../../../scalars.md) |
