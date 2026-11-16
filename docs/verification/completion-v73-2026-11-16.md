# V73 original-scope review and integrated verification

Publication update: the code is now available on the
[GitHub review branch](https://github.com/NTU-DBT/CROWN/tree/review/native-v73-f4732bac).
The [current handoff](../handoff.md) records delivery. The V73 review below retains
its original pre-publication state and evidence vintage.

The original-scope requirement review and current integrated verification are
received. Release and Debug ASan/UBSan each pass all 396 current registered tests,
with zero failures or skips. GitHub publication is prepared and awaits
authentication. The Refactor goal remains active until delivery and final receiving.

## Requirement and source review

Three parallel review agents checked the original task requirements, associated
invariants, mandatory examples and release evidence. Their received matrices cover
all 78 task IDs, 777 requirement rows and all 44 Q01–Q20/U01–U24 cases. Of those
rows, 770 are complete and seven retain explicit deferred clauses. The root also
checked 18 cross-cutting and user-scope rows. The joined evidence identifies 403
distinct file/hash pairs. No outstanding requirement within the agreed scope was
identified by these reviews.

The matrices and their evidence pins are inspectable in the
[joined requirements](../../build/verification/v73-completion-root-v1/joined-requirements.json),
[received evidence](../../build/verification/v73-completion-root-v1/received-evidence-pins.json)
and [cross-cutting review](../../build/verification/v73-completion-root-v1/global-requirements.json).
The three audit packets preserve the individual arguments:
[frontend/planner](../../build/verification/v73-completion-frontend-planner-v1/receiving.json),
[runtime/extensions](../../build/verification/v73-completion-runtime-extensions-v1/receiving.json)
and [benchmarks/documentation/releases](../../build/verification/v73-completion-evidence-release-v1/receiving.json).

This increment changes no native code or configuration. The 902 current paths
remain exact V72, including 414 production paths. Entry receiving checked all
4,994 inherited live files and their explicit immutable providers. The review
uses current requirement-to-source arguments and exact-source inheritance of
earlier detailed inspection; it is not a fresh independent proof of every old
line. Earlier release, SDK and benchmark artifacts keep their original source
vintages and scope.

## Human inspection and implementation boundaries

The [inspection guide](../code_review.md) and [primitive guide](../code_specs/primitives.md)
describe the maintained source structure. Maps cover 900 files, 202,375 lines and
22,533 regions. All 19,205 nonblank regions have seven-field source-bound usage,
invariant, cost and reference contracts; 3,328 blank regions retain structural
facts. The registry contains 21,731 records. These contracts support inspection;
coverage alone is not a correctness proof.

The [error-handling review](../code_specs/error_handling.md) explains the retained
ownership and publication boundaries. Ordinary comparisons, top-k and difference
use the documented propagation or exact recomputation approaches. Their materialization,
scalar, allocation and cleanup costs remain explicit. No specialized paper bound
is claimed for those conservative implementations. Exact requests retain exact
semantics, and query owners retain independent mutable state.

The task ledger remains 75 verified, one in progress and two not started out of
78. A02 project licensing disposition is user-deferred; existing rights and notices
remain preserved. X07 approximation and X11 parallel/distributed execution are
user-deferred. Shared-query optimization is also deferred under the independent
X10 interface. Conditional unsupported C05 cost policies and source-classified
external workloads retain their explicit admission/evidence limits. These are
recorded scope decisions, not newly claimed implementations.

## Current integrated execution

Both complete native builds pass. Each profile executes all 396 registered
commands without a selection regex: 396 pass, zero fail and zero skip. Actual
JUnit, command, registration definitions, source-before/source-after and build
metadata are preserved for the
[Release suite](../../build/verification/v73-full-regression-v1/release-suite-v1/receiving.json)
and [sanitizer suite](../../build/verification/v73-full-regression-v1/sanitizer-suite-v1/receiving.json).
The complete 902-path source inventory and captured metadata remain unchanged
across both builds and suites. These actual current cohorts extend V72's
five-command integration scope. Earlier full suites and V72's targeted checks
retain their own source vintages. No rerun, timeout extension or test exclusion
was used to manufacture these results.

The fresh inspection checker also passes all 900 mapped files and 158,448 local
links with the same 902 source/configuration hashes. Complete tests and map
coverage support the scoped review; they do not replace the invariant arguments.

Finite tests and review arguments do not establish universal correctness or a
performance improvement. Historical benchmark evidence supports the documented
same-host replay methodology; it does not demonstrate a second physical machine.
No new release archive is accepted by this review.

## GitHub delivery

Another agent prepared an isolated source repository on branch `main`, with
initial commit `2390b679880712ff5d1e38c3555d5f410c8177f5` and a documentation-only
successor `4a09f56f35c15c51a634f925eca12947de08dd3c`. All 902 native inputs match
the accepted implementation. Offline configure discovers 396 tests; the export
itself has not executed them. Git integrity and credential-signature checks pass
within the limits recorded in the
[publication receipt](../../build/verification/v73-github-publication-v1/receiving.json).
The export includes maintained source, inspection documentation and required
pinned dependency inputs. Large historical evidence archives and build products
are omitted with an explicit publication README.

The intended destination is private `wqc0712/CROWN-native`. The first device-login
flow expired, so no repository has been created and nothing has been pushed.
Publishing needs a fresh authenticated session, verification of the API owner and
repository availability, then remote commit/private-visibility verification.
The original repository's Git metadata remains unchanged. Later documentation
updates require an explicit successor commit in the isolated export.
