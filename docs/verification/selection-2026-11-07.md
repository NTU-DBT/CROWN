# C05 physical selection verification

C05 is verified. All 158 tests pass each of the five native configurations.
The complete 78-card goal remains active: 40 verified, two in progress (A02/O06),
36 not started, 78 total. Work is uncommitted on master at baseline
e369a623517723b3be3ea3e9806779f3c591e7f9.

[Selection policies](../selection.md), [artifact binding and cache](../selection_binding.md)
and [aggregate budget accounting](../selection_accounting.md) define the scope.
Selection returns an owning PhysicalPlan after fresh admission and assessment;
it does not install a plan or migrate live state. VerifiedOptimum authority and
exact query/context/source binding remain prerequisites. C03 calibration,
allocator-byte prediction and automatic reoptimization remain unsupported.

## Native evidence

| Configuration | Tests | CTest seconds | Closed session |
| --- | --- | --- | --- |
| GCC Debug | 158/158 | 3019.76 | 12967 |
| GCC Release | 158/158 | 471.7 | 12116 |
| ASan + UBSan + leaks | 158/158 | 13904.36 | 39384 |
| Clang Debug | 158/158 | 2368.35 | 31556 |
| Clean source-only Release | 158/158 | 481.67 | 42506 |

Every configuration preserves the complete 143-test prefix, its commands,
properties and ordering, then runs all 15 C05 consumers. The matrix verifies
1,116 numeric rows per configuration and the 238 target/source compilation
entries. Incremental builds actually compile 24 entries and retain 214 accepted
predecessor entries; the source-only Release build freshly compiles all 238.
Runtime/report compositions remain 14/six units per production/testing variant;
selection adds five pure units and one bridge per variant, 15 consumer units
and two example objects. Actual commands, dependencies, compiler identities,
flags, definitions, archives and executable links are audited.

The clean leg retains all 238 dependency records and 716 unique actual include
inputs, including generated-header copies, with post-test source/input guards
before temporary-tree cleanup. Cached object/argv/project-source history is
separate from current system/generated-header observations; historical bytes
for those external/generated inputs were not retained. Twelve symbol roles
are checked per configuration; the sanitizer capture also checks both parser
sanitizer references. ASan/UBSan and leak checking pass in a recorded quiet
window. Existing 3,600-second and new 7,200-second fault-test limits were kept.

The canonical records are `build/verification/selection-matrix-evidence-audit.json`
and `build/verification/selection-source-evidence-audit.json`. The explicit root
matrix authority is `build/verification/selection-matrix-audit-authority.json`.
The completion checkpoint is written only after accepted final source evidence.

Execution freeze FILE SHA256:
`affcb8fa29b193e57f9501c5a88054eaba9467b7040273f36f28c507f3146711`.
Native676 digest: `d963498ffa4d0ebcfa650f2a958258c2bf18a352022c264549dc3cbbab79b733`.
Execution733 digest: `fc12d2bd82756946a3a5bcdec910df400481b7af1bc4199254040e59730c2445`.
Official795-source seal: `docs/verification/selection-sources.sha256`, SHA256
`0250c5e467fce543d500617442c9bd3551a4b4aa82f01c8d2056d0ab1eaa5653`.
The preliminary seal remains retained separately. All twelve predecessor source
manifests are historical FILE identities; their entries are never checked
against later source. The three status-only guide changes and exact diffs are
bound by `selection-completion-metadata-approval.json`.

## Allocation review and retained preparation

Root independently traced the 26 exact Clang allocation comparisons in
[the source review](c05-allocation-variance-source-review-proposal/ROOT_REVIEW.md).
One default GuaranteeProfile per physical lowering explains the retained
measured five-string allocation effect. Direct multiplicities [1,1,3,3,0,1,3]
give increases [5,5,15,15,0,5,15]; normalized multiplicities [1,1,1] give [5,5,5].
The immutable root decision is
`build/verification/selection-allocation-review-clang-guarantee-v1.json`, SHA256
`cab46951a9604c7e97a97d7fc4b79c39a91d3cb297bc68e86f84760005a43019`.
All 26 exact IDs are applied with no unapproved or unused entries. This decision
does not waive semantic, cleanup, byte/peak, timeout or future-row changes.

Producer GNU sweeps cover 32,966 direct and 20,420 normalized fault positions;
Clang covers 33,026 and 20,435 respectively, with zero cleanup recoveries.
The independent focused consumer retains 22 positions, two late publication
failures and zero completed fault positions. Excluded strict and matching
sanitizer preparation passed ten producer and five independent consumers.
The preparation aggregate43b42024..., native integration9f8824f1... and staged
24-compile/15-test receipt38ce409e... remain preserved as preparation evidence.
All earlier failed attempts and both preliminary matrix receipts remain intact.
The revised matrix auditor accepts exactly the two reviewed ASCII/typographic
vendor warning-line equivalents; no other diagnostic is normalized away.

## Coverage limits

Real normalized positive exact/one-under replay and normalization thresholds
have not been established. DirectCQ boundaries, neutral eight-domain budget
algebra, real normalized zero-cap cases and complete persistent-fault sweeps
cover distinct scopes. Logical component payload and slot proxies are not
allocator or peak-memory accounting. Current-owner selection and shared-cache
access require caller-preserved exclusive access; owning results may outlive
owners and cache entries. Timing limits are soft; measurement-disabled paths
do not read clocks. S04/S05 storage, O04-O06 recovery/delivery, A02 licensing
and release gates remain separate unfinished work. No R0/R1 release is claimed.
