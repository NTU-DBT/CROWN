# Full source review continuation and C04 foundations — V55

The [V54 full review](full-scope-review-v54-2026-11-15.md) remains the baseline.
This continuation receives every changed source against its exact frozen bytes:
all 366 maintained production paths and all 419 primary production/build/tool/
example paths are fully read, with zero unread primary paths. Seven existing
primary files changed and two are new; byte-identical source retains its V54
review. Supporting tests/schemas have separate scoped inspections. This does
not claim a fresh full read of every test file or a universal correctness proof.

## Implemented and corrected

[Meta construction](../meta_decompositions.md) implements P3v2 Definition 4.3 /
Algorithm 1 metadata, selected work/node/scope-cell limits and independent checks.
It preserves occurrence identity, including aliases/equal scopes, and explicitly
qualifies empty/nullary and disconnected inputs. The [finite proposal bridge](../candidate_alternatives.md#supplied-finite-proposals)
retains the original proof/P02/height/key/publication gates. Family identity
survives ranking, selection and reports; the original CandidateCache rejects
finite batches. EXPLAIN rejects candidate/family mismatches.

| Finding | Correction and regression |
| --- | --- |
| Nullary checker-domain inconsistency | Both APIs explicitly stop outside their admitted empty/nonempty-edge domain. |
| Artificial minor hides a cyclic body | Require each minor's whole scope to fit one original physical scope, a stronger Algorithm 1 invariant. Coverage/RIP then permit contraction to an ordinary join tree. The literal triangle union-bag is rejected. |
| Disconnected root depends on creation order | Prefer the canonical empty-scope minor over a later terminal component minor. An isolated occurrence plus a four-edge component preserves the correct root. |
| New overlap group has no terminal root | Repeat equal-overlap grouping to a fixed point before freezing ears. The independent GYO corpus exposed R(x),S(x,y),T(x,y); its literal five-node regression preserves both minor identities. |
| EXPLAIN partial constraints violate the structural schema gate | Partial family/source conditions now inherit the closed outer records, with explicit non-null family guards. Existing nullable fields and default output remain supported. The actual composed corpus and real finite/native documents validate. |

The nested-group native failure and initial 44/45 Debug run are retained as
failures. The earlier primary construction pseudocode remains sealed historical
evidence; the corrected operational interpretation is explained in the source,
independent review and usage guide. Paper asymptotic/delay claims are not imported.

## Native evidence

There are358 current registrations. V54 validated its 356 checks across full runs
and qualified corrective reruns. V55 validates45 affected registrations in Debug
and ASan/UBSan/leak profiles; it does not claim two new full 358-test suites.
Debug has 44 initial passes, the schema correction, all 5 affected current-schema
passes and 2 current source-closure passes. Sanitizers pass43 affected checks and
2 separately run current source-closure checks. Final Debug, sanitizer and
production Release/tests-OFF build refreshes pass and compile no additional C++.
Production code is identical across the pre/post schema correction.

Each profile passes 11 literal meta structures, malformed metadata/domain controls,
selected exact/one-short/zero grants, and 7,750 independent GYO comparisons over
3,875 scope multisets in forward/reverse order:7,114 acyclic and 636 cyclic.
GYO is independent of the meta APIs, but is another maintained production
algorithm. Neither this finite corpus nor structural checks prove every input.

Real schema fixtures include35 legacy reports,5 additional finite/EXPLAIN reports,
54 existing and 14 new rejected mutations. Two additional parent/member family
controls per profile use individually schema-valid children to isolate the
snapshot fence. Proposal tests also cover first-owner allocation denial/retry,
budget/capacity continuation, lifetimes, original proof retention, cache-family
separation and C02/C05 selection. Existing allocation-failure sweeps and both
storage-backend selection controls pass in the affected matrix.

## Human inspection and costs

The block index maps 776 files /177,669 lines /19,879 blocks. All 16,947 nonblank
blocks have 19,382 authored contracts;2,932 regions are blank spacing. V55 adds 98
contracts, amends 37 semantic/attachment cards and rebinds 45 CMake references.
Source hashes, attachments, fields and local links are checked separately.
The [inspection guide](../code_review.md) links code, exact paper sections and
independent controls for a human reviewer.

These changes add cold planning work and no runtime update hook, retained row
index or runtime error framework. Recomputed metadata checks and input admission
retain explicit costs; counters are selected operations/cells, not heap bytes or
total CPU. Owning EXPLAIN provenance can copy an allocating residual trace.

C04 remains in progress: bounded meta join-tree enumeration, CROWN/head/
generalized mapping, independent family coverage comparisons and integration
remain required. Ordinary-tree metadata cannot establish global generalized
minimum height or global maintenance-cost optimality. The full Refactor goal
and release gates remain open. Ledger: 61 verified / 2 in progress / 15 not started.
Rights/notices and immutable predecessor evidence are preserved.

Evidence packet: `build/verification/meta-candidate-adapter-v55-v1`.
Current source seal: `build/verification/human-inspection-v55-progress-v1.json`.
The [handoff](../handoff.md) identifies the next required implementation work.
