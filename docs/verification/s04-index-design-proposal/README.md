# S04 optimized-index design draft

This is design only, authored alongside the C05 verification work.
It adds no implementation, dependency, native file, build, benchmark, input
freeze or acceptance claim. S04 remains not started. Root's C05 corrections
and publication freeze take priority over this draft.

The recommended primitive is a new, independently implemented stable-node hash
table with primary equality lookup, logical-ID lookup and projected secondary
buckets. Live row/key/member links provide traversal over current membership,
independent of hash-array capacity and arena high-water slots. Existing
ReferenceTable remains unchanged as the standard-container oracle and default
backend. Hash collisions always resolve by exact typed equality.

The current code does not have an interchangeable storage interface. Runtime
owners, journals and C01 capture use concrete reference-table types; physical
artifact v1 fixes its backend string to reference_ordered_v1. Consequently a
new primitive is not a drop-in production backend. This draft identifies a
separate, explicit facade/profile/artifact integration gate before runtime
exposure. It does not silently relabel an optimized owner as reference storage
or change existing output/binding bytes.

The accompanying draft files are `CONTRACT.md`, `WORK_MODEL.md`,
`INTEGRATION.md`, `ACCEPTANCE.md`, `MEASUREMENT.md`, `DECISIONS.md` and
`SOURCE_MAP.md`. They use existing paths as code references; proposed paths
are labeled explicitly and do not become build inputs.

Refactor.md S04 depends on S03 and A02. The proposed implementation copies no
legacy index code and adds no external dependency. The existing A02 provenance
and distribution-license disposition remain unresolved as recorded in
`docs/source_baselines.md`; this proposal makes no new licensing decision or
claim of an audited DynaGox adaptation.
