# Decision 0007: replay-validated programs and separate identity domains

F05 freezes the existing normalized SQL v1 producer and adds a strict reader.
The format contains its full source binding, so reconstruct it by bounded
binding/normalization replay and require complete canonical serialization
agreement. This avoids trusting attacker-controlled or corrupted IDs, local
program wiring, output mappings or occurrence routes. JSON Schema defines
shape; replay validates the complete executable artifact. Diagnostic
envelopes are never executable programs.

Keep CQ format 1/2/3 writers version-preserving. Provide explicit upward
migration with before/after validation and reject all downgrades or unknown
versions. Existing tree/certificate-v1 contracts and exact proof bindings
remain intact. Future producer changes must preserve the v1 reader or provide
an explicit version/migration, including changes to recorded work counters.

Separate semantic query identity, output labels/types, cost inputs and the
composed plan-cache policy key. Canonicalize variable/alias names and
occurrence order by complete colored-occurrence labeling. Preserve every
mutable input and return no identity if the operational budget is exhausted.
Return canonical-to-original ID maps for future safe cache use. This is a
defined equivalence profile, not a general SQL equivalence solver.

SHA-256 uses a domain/version-framed deterministic JSON encoding. Exact
source schema/version, local adapter and parameter semantics enter the
semantic payload; statistics/hints enter cost invalidation. The detailed
contracts are in [schema_evolution.md](../schema_evolution.md) and
[query_identity.md](../query_identity.md). Physical-plan lowering and runtime
cache installation remain P08/P07 work. The
[verification packet](../verification/schema-2026-11-05.md) records the completed
F05 matrix and finite acceptance evidence.
