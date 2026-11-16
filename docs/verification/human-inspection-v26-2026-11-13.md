# Human inspection V26 — 2026-11-13

V26 adds [genuine R2 descriptor admission and selected checkpoint bytes](w06-r2-descriptor-2026-11-13.md)
and 217 scoped usage contracts. The full implementation goal remains active:
56 verified / 2 in progress / 20 not started, 78 total. W06 still requires its
physical checkpoint format, actual files/coordinator, genuine WAL replay, typed
input/CLI and varying-int32 admission. A02 licensing still blocks C04/B01 only.

The seal is `build/verification/human-inspection-v26-progress-v1.json`; frozen
source is `build/verification/human-inspection-v26-source-v1`. The root packet is
`build/verification/w06-r2-descriptor-implementation-v1`. V25 and its frozen source,
private builds, SDKs and evidence remain protected.

## Reviewed code and specifications

The [inspection map](../code_specs/README.md) covers 719 maintained code files and
13,753 scoped semantic contracts. All selected production scopes, examples and
tools have contracts; 2,342 selected existing-test scopes still need individual
review. Complete line/block partitioning remains a structural inspection aid,
not a claim that every line or all tests are semantically certified.

The additions are 136 existing catalog/binding/scalar/ingest test cards and 81
new or changed source/build scopes. The latter cover the descriptor header,
codec, bounded CBOR preflight, opaque reader and two tests, plus 16 CMake scopes.
The source review updates one library-source-list contract semantically and
1,405 source hashes after unchanged-command/body review. Existing keyed objects
and master order are preserved. The shared selected-file reader retains the
old plan-reader behavior while adding separately capped/hash-bound checkpoints.

One misleading SQLiteTrace docstring now names catalog metadata's types,
nullability, constraints and typed ordering. Exact original/current images and
non-docstring AST equality are preserved. A private catalog-review author refined
wording after its initial completion report, before this checkpoint; root checked
the final recursive seal and all adopted 136 objects again. The final packet
identity is pinned explicitly. No native source behavior follows from that prose
correction.

## Actual implementation and checks

Root implements the code and a normal-model reviewer checks actual API/ownership/
budget/domain semantics. Luna Max supplies scoped source and test contracts.
No Astra call is used. The implementation adds no production handler, ordinary
update field, row mirror, retry or second undo framework. Finite receiving caps
preserve original producer policies, including disabled compiler counters; a
redundant cold lowering pass is skipped where existing finite caps already bound
construction.

[Receiving evidence](w06-r2-descriptor-2026-11-13.md) passes final freshly linked
Debug 8/8 and full ASan/UBSan/leak 8/8, complete OFF Release and full descriptor
checks through a relocated 223-file public SDK. A separate installed consumer
checks NULL parameters, static 0/1, original owner release/input-byte destruction
and the next filtered/unused physical epoch. All 334 predecessor test commands/
properties remain except backtraces; 336 total are registered. Nineteen existing
archives and 28/29 runtime object files are byte-identical to V25. No CPU timing,
full 336/Clang execution or durable R2 recovery acceptance is claimed.

All 27 recorder jobs are terminal, 23 successful, with zero in-command input drift;
four original compiler/setup failures remain. Final native inputs are 1,163. The
final code-map checker verifies source hashes, structural partitions, scoped
anchors and generated links. A separate pinned 48-guide audit checks local links/
fragments, skipping external URLs. Frozen source/evidence and exact review seals
are enumerated in the V26 seal; the fresh postseal check validates them again.
The [handoff](../handoff.md) records actual next work and continuing limits.
