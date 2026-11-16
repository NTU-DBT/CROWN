# D03 projected delta proof and reference model, 2026-11-06

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`. **D03 is verified for its
specification, conditional proof, executable model and independent internal
review.** The [D02 packet](fragment-cursors-2026-11-06.md) and its 463-input
manifest describe the previous checkpoint. The full 78-card goal remains
active: 24 verified, four in progress and 50 not started.

Specification: [delta transitions](../delta_transition_spec.md).
Executable model: [interface](../../tests/reference/delta_model.hpp),
[implementation](../../tests/reference/delta_model.cpp),
[independent oracle cases](../../tests/unit/delta_spec_test.cpp).

## Requirement audit

| D03 artifact / acceptance | Evidence |
| --- | --- |
| Insertion/deletion transition specification | One fully drained logical occurrence route at a time; actual E zero crossings, after/live-after insertion context, before/live-before deletion context, full E-key bindings, per-route draining and one unpublished physical epoch. |
| Witness partition proof | Each target assignment belongs to its least changed factor. Soundness, completeness, disjointness and the same-sign alias telescoping argument are explicit. Rejected candidates are still true difference rows; no cross-fragment output deduplication dictionary is used. |
| Liveness state machine | Exact global L definition and top-down bootstrap proof with downward-totality/running-intersection preconditions. Ready, propagating, live-build, pending, paused, draining, prepared and committed-output states; mode bootstrap/invalidation, rollback and publication obligations. |
| Complexity ledger | Journal scans, E/L scans/copies, temporary separator indexes, dead-key checks, actual cursor scans, rank membership checks, output width, spool/delivery and retained images are charged separately. H,T≤mD bounds duplication only; no D05 delay claim. |
| Paper and model counterexamples | Projection collision, simultaneous two-survivor projection activation, full root key with empty parent separator, ancestor/child deletion ownership, unchanged-root/below-root output change, unlive keys, unchanged E with new L, and new–new self-join prefix combinations. |
| Independent review | A fresh read-only Luna Max reviewer traced every worked output and checked proof/model correspondence; a separate source audit checked runtime prefix/rollback/publication gaps. Findings and disposition are below. |

The model is linked to `crown_reference`/`crown_core`, not the maintained
runtime. It independently materializes native subtree joins to derive E,
bootstraps L through top-down semijoins, and appends accepted rows to a raw
vector. It neither obtains delta output from an answer difference nor
deduplicates across fragments. The checker uses the independent A04 evaluator
for before/after answers, computes their difference, and compares both the
set and raw vector cardinality. It also checks every L set against the
corresponding exact global-answer projection.

## Finite coverage

The exhaustive domain is `{0,1}` for small integer relations:

| Family | Initial states × possible membership toggles | Checked transitions |
| --- | --- | ---: |
| Q(x):R(x,z) | 16 × 4 | 64 |
| Q(x):R(x),S(x,y) | (4 × 16) × 6 | 384 |
| Q(x):R(x,z),S(z,y) | (16 × 16) × 8 | 2,048 |
| Boolean unary relation | 4 × 2 | 8 |
| Total | Both directions occur across the exhaustive states | 2,504 |

Additional fixtures cover full/reordered/repeated heads, empty/nullary and
constant true/false routes, constant-filtered rows, ignored physical payload
projection counts, generalized 3/8-child products (4/128 added outputs),
same-scope aliases and a two-alias loop-edge insertion/deletion.

Alias-prefix tests give each occurrence an independent logical table, apply
one route at a time, and compare each stage to A04. The concatenated raw stage
vectors must be duplicate-free and equal the original same-base-table CQ's
physical endpoint difference. Different constant predicates on two aliases
also exercise route output counts `[0,1]` on insertion, `[0,0]` on a 2→1
derivation deletion, and `[1,0]` on last-derivation deletion.

Every checked stage verifies `H≤mD`, `T≤mD`, accepted/rejected accounting and
no duplicate vector output. An empty exact answer delta requires unchanged L
memberships. Invalid factor geometry/totality, row types and mixed factor
polarity are rejected. The model does not validate an arbitrary physical
input history or implement a mixed-batch API.

## Independent review and disposition

The root derived the proof and model. Luna Max supplied the separate fixture
suite. A fresh-context read-only reviewer (`delta_spec_review`) audited the
specification/model and independently derived the owner traces. A separate
read-only audit (`delta_stage_audit`) checked the actual pending-epoch and
physical-route implementation against the proposed lifecycle.

| Finding | Disposition |
| --- | --- |
| Low: "the key is determined by the parent E row" could mean the whole child key. | Clarified that only the separator key is determined; additional child E-key fields remain part of the explicit witness binding. |
| Coverage boundary: model executes core CQ deltas, not SQL mapped records. | The spec explicitly labels DISTINCT/EXISTS mapping as analytical obligations. D04 must add a SQL-output delta oracle, including both replacement signs for EXISTS. |
| Existing `view(before)` is epoch-start, not immediately preceding alias prefix. | Required D04 checkpoint/record interval/prefix identity hook is documented. The stage patch interval must retain the cumulative journal for active table writers and pins. |
| No existing L cache, per-route delta callback, spool/output participant or session drain API. | Documented as D04/D06/O06 implementation requirements, not facilities certified by this model. Current support/count/source rollback and prefix leases are preserved prerequisites. |

After the wording/scope corrections, the proof reviewer reported no remaining
D03 specification/research-review blocker under the stated assumptions. The
review traced: root-owned ancestor/child erasure once; below-root S ownership;
dead-key omission; and self-join route-1 left ownership followed by route-2
right ownership, including the new–new loop term. The review did not run tests.
This is an independent internal review; external G2/V02 and release gates
remain unsigned/open. G5 still needs D04/D05 actual maintained-output evidence.

## Matrix and continuation

All 49 earlier tests remain alongside `delta_spec`. All five configurations
pass, with native warnings kept as errors:

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 50/50 pass | 63.22 s |
| GCC 13.3 Release | 50/50 pass | 8.43 s |
| ASan/UBSan including parser C | 50/50 pass | 312.20 s |
| Clang 18.1.3 C/C++ Debug | 50/50 pass | 48.48 s |
| Fresh source-only Release | 50/50 pass | 8.43 s |

Every final matrix process is terminal and successful. The four in-place
runs share one unchanged before/after source fingerprint. The clean configure,
build and test took 256.76 s and removed its temporary source/build tree.
Sanitizers include parser C with leak detection and halt on ASan/UBSan errors.

Frozen physical-plan v1, support-trace v1 and support-report v2 formats are
unchanged. The support CLI passes 25 checks/34 manual states under Python
`-O`. The optional schema audit passes 18 schema meta-checks, 26 normalized
artifacts, 19 identity artifacts, 59 admission artifacts, two layout/projection
artifacts, 31 physical artifacts, three support traces/reports and two rejected
update reports. These are existing CLI/schema compatibility checks, not an
implemented delta stream.

The [467-input source manifest](delta-spec-sources.sha256) covers the ordinary
contracts, new spec/model/cases and all prior source/build/test/dependency
inputs; all fingerprints pass. Verification packets/manifests and mutable
handoff/ledger files remain excluded. Logs and per-configuration summaries
are ignored `build/verification/delta-spec-*` files. The model's CTest log
retains the owner trace and exhaustive-step count.

```sh
cmake --preset debug
cmake --build --preset debug --parallel 2
ctest --preset debug --output-on-failure
cmake --preset release
cmake --build --preset release --parallel 2
ctest --preset release --output-on-failure
cmake --preset sanitize
cmake --build --preset sanitize --parallel 2
ctest --preset sanitize --output-on-failure
cmake -S . -B build/clang-debug
cmake --build build/clang-debug --parallel 2
ctest --test-dir build/clang-debug --output-on-failure
python3 -O tests/integration/support.py build/release/crown .
python3 tools/verify_schemas.py build/release/crown
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/delta-spec-clean-source.log
sha256sum -c docs/verification/delta-spec-sources.sha256
```

D04 must implement stage-local journal-range views, owner-only E-factor reads,
private eager-live maintenance, canonical E witnesses/completions, prepared
bounded output and atomic alias-epoch integration. D06/O06 supply operational
draining/delivery/recovery. The mathematical model and lifecycle table do not
claim a production delta API, SQL delta stream, durable sink or D05 delay bound.
