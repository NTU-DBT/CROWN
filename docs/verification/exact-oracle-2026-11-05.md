# P03 exact-oracle verification packet, 2026-11-05

Input revision: uncommitted worktree on `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`. This checkpoint's build/contracts/fixtures
are fingerprinted in [exact-oracle-sources.sha256](exact-oracle-sources.sha256).
This is the historical P03 audit. Foundation and P02 packets describe their
earlier source snapshots and retain their historical checksums. The later
frontend changes are recorded in [frontend-2026-11-05.md](frontend-2026-11-05.md).

## Disposition

P03's complete-family oracle acceptance is verified. The literal reference
enumerator, normal-form proof, complete memoized search, analytic minima and
honest resource statuses are implemented. The public oracle also requires
independent upper-tree and lower-bound certificate replay. Broader P04 and
P06 tasks are **in progress**: dedicated q-hierarchical fast paths, resumable
search and an explicit best-found policy are still missing. Cost ranking,
physical lowering, SQL binding and the incremental runtime remain unfinished.
G0/G1–G11 remain open; no R0/R1 release is claimed.

## Artifacts and algorithm evidence

- `tests/reference/tree_oracle.cpp`: the frozen literal Refactor.md §5.4
  search over labelled root/parent topologies, 0…m−1 generalized nodes and
  the complete union of native power sets, including empty. It calls P02 on
  candidates and searches native-height bounds in order. Operational limits
  never convert unfinished enumeration into infeasibility.
- `src/planner/exact.cpp`: equivalent exhaustive root/child partitions with
  memoized occurrence subsets and native-ancestor/output-reachability flags.
  It retains every occurrence and computes forced generalized scopes from
  child native unions. It uses no residual-ear-round height shortcut.
- `src/planner/certificate.cpp`: independent inside/outside sets, an
  independently written partition enumerator and increasing-size lower-bound
  replay. It checks P02 upper witnesses and rejects unproved claims.
- `src/planner/search_budget.hpp`: work, tracked recursion and optional
  best-effort time limits. Search and replay get separate budgets. Counts
  describe charge boundaries, not all CPU instructions or parser/serializer
  work. The literal reference alone materializes the power-set universe and
  applies its explicit scope cap.
- [planner_proofs.md](../planner_proofs.md): unary generalized contraction,
  m−1 node bound, boundary/separator equality, forced generalized scopes,
  blocked exclusive-head criterion, recurrence completeness and certificate
  induction. These are engineering arguments under the specified tree family;
  no new polynomial planner or residual reconstruction theorem is claimed.
- `include/crown/io/oracle.hpp`, `src/io/document.cpp`,
  [height-certificate-v1.schema.json](../../schemas/height-certificate-v1.schema.json):
  strict query-bound certificate I/O and type-sensitive canonical binding.
- `apps/crown/main.cpp` / [tree_oracle.md](../tree_oracle.md): `tree-oracle`
  and `verify-height`, exact/resource/unsupported statuses and certificate use.

The literal implementation was first built and tested in its own initial
configuration and remains a separate baseline. Producer and verifier share
resource/model machinery and the P02 upper-tree checker, but not partition
or boundary helpers. The certificate
contains the upper witness, full catalog/query binding with no physical data,
and a finite table of lower bounds. It does not rely on a producer-supplied
Boolean optimum claim.

## Actual build/test matrix

| Configuration | Outcome |
| --- | --- |
| GCC 13.3 Debug | 9/9 CTest tests passed |
| GCC 13.3 Release | 9/9 passed |
| GCC 13.3 Debug, ASan + UBSan | 9/9 passed; no sanitizer findings |
| Clang 18.1.3 Debug, libstdc++ 13 | 9/9 passed |
| Final clean source snapshot under `/tmp` | Configure/build and 9/9 passed |
| Oracle CLI runner under Python `-O -B` | All 21 cases, replay/corruption/boundary checks passed |
| JSON Schema audit | Certificate schema valid; actual nine-atom certificate validates with local CQ/tree refs |

The nine tests are `semantics`, `recognition`, `tree_verifier`, `exact_oracle`,
`cli_smoke`, `fixtures`, `reference_fuzz`, `plan_fixtures`, and
`tree_oracle_fixtures`. Prior reference/semantic/structural regressions remain
enabled. Raw local outputs are in `build/verification/p03-release.log`,
`p03-sanitize.log`, `p03-clang.log`, `p03-clean-source.log` and each build's
CTest `Testing/Temporary/LastTest.log`. The clean copy included declared
native sources, tests, tools, schemas and vendored dependencies only, and was
removed after success. It was not a committed checkout. Compiler/dependency
versions and the sandbox workaround are unchanged from the foundation packet.

Commands used to reproduce the final configuration:

```sh
cmake --preset debug
cmake --build --preset debug --parallel 2
ctest --preset debug
cmake --preset release
cmake --build --preset release --parallel 2
ctest --preset release
cmake --preset sanitize
cmake --build --preset sanitize --parallel 2
ctest --preset sanitize
cmake -S . -B build/clang-debug -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_COMPILER="$PWD/build/toolchains/clang18/root/usr/bin/clang++-18"
cmake --build build/clang-debug --parallel 2
ctest --test-dir build/clang-debug --output-on-failure
python3 -O -B tests/integration/tree_oracle.py build/release/crown
sha256sum -c docs/verification/exact-oracle-sources.sha256
```

## Finite coverage and proof checks

`exact_oracle` compares all **371** ordered 0–2-atom CQs over three variables
and every body-bound head against literal labelled-topology/full-power-set
enumeration. Seven additional three-atom shapes cover cyclic failure,
disconnected/Boolean/nested/equal scopes and a height-one query requiring both
generalized nodes. It checks independent proof replay and rejects changed
minimum/upper scope, false root bounds, missing/duplicate states, unsupported
algorithms, and a weakened hidden-head infeasibility proof. Zero work, zero
recursion, zero deadline, and literal scope exhaustion have explicit resource
outcomes. A search that finishes but cannot finish its proof replay still
publishes no minimum. A 70-variable composite generalized key verifies without
materializing its native power sets.

The **21** analytic CLI fixtures cover empty-body zero, nonempty/nullary
height one, projection/Boolean, full two-edge minimum one versus proper-head
minimum two, four-edge full path minimum two, equal scopes, disconnected
heads, three/eight-child stars, a 65-variable singleton, both seven-/nine-atom
residual minimums **three**, and renaming/permutation. Non-free-connex endpoint
and triangle queries produce completed empty-family proofs. Every selected
tree passes standalone `validate-plan`; each emitted certificate is replayed
by a separate `verify-height` process. Height/scope/claim corruptions fail, and
zero work never yields a minimum or a completed infeasibility result.

The nine-atom run selected height three with 321 states and 75,537 partition
visits; its recorded search/replay work was 311,520 / 1,766,742. These are
defined compile-work counters for that run, not throughput or maintenance
measurements. The actual result/certificate are in local ignored
`build/verification/p03-nine-result.json` and `p03-nine-certificate.json`.

Luna Max independently prepared analytic fixtures/schema/docs and performed
a focused read-only code/contract review. No false-bound acceptance gap was
found; false root/child infeasibility mutations were rejected. Review found
two wording issues and a malformed-binding diagnostic mismatch. Those were
fixed: malformed nested binding data is a strict input error, while a different
well-formed binding is an invalid certificate. Unit and real CLI checks now
enforce that distinction. The final build matrix includes the fixes. No
external human mathematical or full G2/V02 signoff is asserted; finite cases
do not replace the recorded completeness arguments or remaining release review.

## Enabled next dependencies

Continue Stage 1 with F01 scalar/catalog completion and F02's pinned owned
parser wrapper, then binding/normalization/full schema identity (F03–F05).
The direct-IR reference evaluator, classifier, tree checker and exact small
minimum workflow are now executable. P08/S/runtime work can use their verified
interfaces when its remaining dependencies are ready. Keep P04/P06 unfinished
features explicit; do not enable a residual candidate as an optimum without
its separate P05 proof. The complete 78-card goal remains active.
