# C02 native publication and registration proposal

This is an excluded publication overlay. Native files, the ledger, handoff,
Refactor.md, accepted C01/C02 packets and historical manifests are unchanged.
C02 remains preparation-only here. Root owns the guarded native application,
CMake configuration, execution, complete five-configuration matrix and final
source acceptance; this author executes no consumers or checkers.

The current C01 checkpoint is verified: all five configurations passed 131
tests. Its 733-entry source-seal **file** is
`docs/verification/statistics-sources.sha256`, SHA-256
`95eda9c8b4b6e631a9b85bc0d1c84315c1577aa0dbcb84801d570c9217ce070e`.
The accepted matrix and final source audit file hashes are respectively
`327cb135d48394a15cc0fd151d7f8f32c749d14bde70f4cb3f5372b36028fc8e`
and `78f668b6a3af08b9bddfc2b995a73009a1be23b12d255eb341b7821e534f25a3`.
This proposal pins those files; it does not recheck historical manifest entries.

Root has also accepted the complete scoped C02 preparation execution in
`build/verification/c02-preparation-execution-completion.json`, SHA-256
`4c39ded5d7d09d2802181e476f236c403f8f7533d8606e6fe3f3a53fa58e2d60`.
That aggregate reconciles producer strict/full sanitizer, independent
strict/sanitizer, original/patched JSON controls, and normalized replay fault
sweeps. It does not accept this new native registration.

## Publication contents

`source-map.tsv` uses the preceding publication's four-column format:
`overlay_file`, `native_destination`, `origin`, `change`. It maps all 38 files.
`source-provenance.tsv` adds exact predecessor/source/proposal hashes.
`overwritten-paths.txt` lists seven existing destinations; `pre-edit.sha256`
pins their current native bytes. `new-paths.txt` lists 31 new destinations.
`source-files.sha256` pins every actual overlay file. All manifest paths use
the repository root as their base, except explicit absolute compiler/artifact
paths. Root must preserve the accepted C01 seal and back up old destination
bytes before its separately authorized application.

The 12 implementation files are exact copies of the frozen C02 implementation,
including the shared binding encoder and patched JSON header. All ten ranking
consumer sources and three fixture/helper headers are exact copies. The public
example source is the exact compiled guide translation unit. No proof type,
binding namespace, score rule, evidence factory, default limit or runtime mode
is changed by publication.

The header-only JSON probe changes two output labels from misleading
`deque_json` to `custom_vector_json`, and marks its replacement scalar/aligned
new and scalar delete functions `noinline`. GCC 13 optimized compilation
otherwise diagnosed inlined delete/free as a mismatched allocation pair.
The retained failed compiler log and complete `json-probe-publication.patch`
show the adjustment. No shape, allocator counter, failure condition, assertion
or numeric expectation changed; no warning flag was disabled.

The new wrapper performs isolated original/patched sizeof/serialization
comparison and the specific original bad_alloc abort control. The separate
patched cleanup test must succeed. It records finite child timeouts and retains
failure evidence. The active header, exact original, patch, lock and vendor
notice are distinct and offline. The upstream MIT copyright/license is
unchanged; A02's project distribution license remains unresolved.

## Build direction and test inventory

`crown_ranking` owns three pure units and links plan/SQL/core only.
`crown_ranking_runtime` and `crown_ranking_runtime_testing` each own one bridge
unit and link the pure ranker plus exactly their matching runtime variant.
Opt-in means an explicit client link; the existing runtime and report targets
do not acquire a reverse dependency. Their source lists stay at 14 runtime
and six report units per variant. The testing definition reaches only the
matching bridge, census probe and testing example. No ranker target needs a
report library, and no CROWN target uses the upstream control header.

The proposal retains the entire existing registration text and appends 12
CTest names after the old 131, before the inherited sanitizer environment
assignment. It expects 143 tests and 214 compile-command entries:
195 prior entries plus three pure units, two bridges, ten ranking consumers,
two example variants and two isolated JSON probes. Native CMake has not been
run for this proposal; root must verify these exact counts and commands.

`prior-ctests-ordered.txt`, `prior-ctest-commands.cmake` and the retained Release
CTest file record the actual accepted order/arguments. `expected-ctests-ordered.txt`
and `expected-ctests.txt` give the complete ordered and sorted inventories.
`new-ctest-commands.tsv` and `target-inventory.tsv` specify each new command,
timeout, source, macro, include and link choice. Existing P07 cases remain
registered once. The new semantic and decimal arithmetic tests are independent
oracles; producer boundary/fault tests add complementary private and lifecycle
coverage. Native tests have no verification-package or author `/tmp` dependency.

## Public contract

The proposed `docs/ranking.md` and `docs/ranking_accounting.md` describe typed
minimum-height admission, complete retained-prefix evaluation, exact wide
scores and every term, deterministic ties, current-only committed-attempt
weights including no-ops, physical source cardinalities, per-policy
freshness/availability, explicit statistical fallback and transactional resource
stops. Uncomputed score fields are placeholders interpreted by effective policy.
The public API adds no proof/import authority, CLI, report schema or plan
deployment. It does not supply C03 calibration, arrival Hz, S05 allocator/peak
bytes or global runtime optimality. The README's stale C01-pending sentence
is corrected only in this proposed copy; C02 native verification stays pending.

The author records direct compile/link checks in `BUILD_RESULTS.md` and
`build-evidence/`; `REPRODUCTION.md` separates those from root-only execution
and native matrix obligations. Package freeze pins are reported to root only
after all source/doc/maps and final compile evidence are coherent.
