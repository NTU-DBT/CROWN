# Inspectable tools, test support and package configuration

The source maps contain **9,669 scoped contracts in 7,318 blocks**, across
693 maintained files / 159,435 lines / 17,883 mapped blocks. Every maintained
line in that inventory has a structural map. Start with the
[source index](../code_specs/README.md), [primitive cards](../code_specs/primitives.md)
and [review guide](../code_review.md). Each scoped contract records usage,
inputs/outputs, invariants, ownership, failures, costs and source/design references.

All 5,468 selected production scopes retain contracts. The 326 files under
include/src/apps remain byte-identical to [v15](human-inspection-v15-2026-11-12.md).
This checkpoint adds no production state, allocation, handler or update-path work.
Remaining nonproduction review is explicit: 4,549 test scopes and 1,147 root
CMake commands. Structural coverage is not complete semantic or execution proof.

## Review the actual offline and test boundaries

The checkpoint adds 697 contracts: 303 remaining-tool, 239 remaining-support,
81 CMake-module, 64 workflow/CLI and ten SDK-template cards. Tools, examples and
cmake modules now have no selected gaps. The root CMake review is sealed in a
separate unmerged packet and is not included in this source checkpoint.

Twenty support files gain 39 comment updates. Twenty-two Python tools gain
25 comment edits, adding 22 lines. Their comment variants preserve complete
C++ token/literal streams or Python ASTs/tokens/literal spellings. The two
self-hashing workload generators retain their exact bytes: changing comments
there would change their corpus manifests. Their individual specs are updated
without regenerating corpus data.

The [support review](../../build/verification/remaining-test-support-human-review-v1/README.md)
distinguishes ordinary oracle copies, borrowed frames/images, original-account
data, lexical guards, C++ new denial and syscall-fault seams. Historical frozen
JSON teardown comments are qualified against the actual patched vendor cleanup.
The [tool review](../../build/verification/remaining-tools-human-review-v1/README.md)
documents actual subprocess/time/output limits, retained failure artifacts,
process versus native memory/timing and the scope of independent oracles.

The [workflow/CLI review](../../build/verification/integration-cli-human-review-v1/README.md)
and [independent corrections](../../build/verification/integration-cli-independent-acceptance-v1/README.md)
cover 56 actual Python function/class nodes and 49 selected gaps. The EXPLAIN
campaign uses its frozen schema copies, not the separately evolving root schema
files. Schema validation, lexical DOT checks and semantic tree/proof checks have
different roles. Paths are not open directory handles, and retained Python
references are not native borrowed-memory lifetimes.

## Correct two confirmed acceptance defects

The EXPLAIN harness executed four named runtime-configuration calls but reported
three. Its summary now reports four. Whole AST comparison identifies exactly
that integer change. The readiness self-file hash and closed package digest are
updated together; the other 65 payload hashes remain unchanged. The original
sealed review and execution packages remain intact.

Both real campaigns pass: 2,749 checks and 175 CLI invocations per profile.
The emitted count reconciles to the four named successful configuration calls;
the complete campaign has 21 runtime-form calls including byte/negative cases.
All 889 evidence files per profile are preserved. Console test totals are
56.49 seconds Debug and 223.94 seconds ASan/UBSan/leaks.

The offline statistics oracle could equate True, int64(1) and Decimal(1) through
Python tuple equality. It now checks exact scalar classes at each key position
after checking ranked values. The per-cell comparison streams through constant
auxiliary iterator state; the existing ranked and decoded key collections remain.
No decoder, expected Counter construction or native implementation changes. A receiving-source fixture passes 32 cases:
all supported scalar kinds, different values, nullary/mixed keys, ranking and
zero top-K, including ten cross-kind counterexamples rejected by the new check.
This is a narrowly demonstrated checker defect; no full-report forgery or
current-native-corpus failure is inferred.

The actual producer/wrapper/checker pipelines also pass in both profiles:
31 production reports and 32 testing reports, with two legacy byte comparisons
per variant and 15/17 rejected mutations. The two statistics CTests take
8.11 seconds Debug and 9.98 seconds ASan/UBSan/leaks. Their existing wrapper
cleans successful temporary corpora; terminal logs and source/binary pins remain.

An inaccurate schema-audit dependency docstring is corrected separately. This
intentionally changes a documentation string literal; it is not included in
comment-token equality. All executable function bodies in that script remain.

## Include the previously omitted SDK template

Both mapping inventories now recognize .cmake.in, and lexical dispatch treats it
as CMake. The unchanged twelve-line
[CrownConfig template](../../cmake/CrownConfig.cmake.in) has ten individual cards
covering initialization, dependency discovery, imported parser ownership,
archive existence checking, relocation, exported targets and required components.
Placeholders remain template text; the mapper does not configure or execute them.

[Actual isolated tools](../../build/verification/cmake-template-functional-validation-v1/README.md)
pass eight recorded outcomes: LF/CRLF raw hashes, complete partitions, an attached
card and UTF8 comment evidence; old silent omission; current omission/staleness
rejection. [Independent review](../../build/verification/cmake-template-independent-acceptance-v1/README.md)
confirms four recognition-predicate changes and the ten cards. The 63 old mapper
records change only three invariants plus source hashes; 8,909 other predecessor
records remain identical. The new 697 records preserve all unrelated work.

## Evidence and remaining work

The first tool-review manifest omitted eight nested files named manifest.json
from its direct list, although dependency pins already bound them. Its original
bytes are preserved. The authoritative
[complete sibling seal](../../build/verification/remaining-tools-human-review-v1-complete-seal-v2.json)
checks exact directory membership and directly hashes all 219 files, including
the original and nested manifests. Integration occurred only after this check.

Each recorded command has fixed inputs and no in-command drift. Earlier CLI
campaign maps precede later support comments and offline changes; the exact
production executable/source and 66-payload campaign closure remain current.
Later native statistics and documentation gates use the final input cohort.
These distinct scopes are recorded explicitly instead of claiming identical
whole-repository input maps across both phases.

All 325 test registrations remain byte-identical. Strict C++23 builds and both
selected native campaigns pass; no full 325-test, Release/Clang or latency claim
is made. Main build directories remain active/reusable after preservation.

Root evidence: `build/verification/inspection-nonproduction-contracts-v1`.
Seal: `build/verification/human-inspection-v16-progress-v1.json`; frozen source:
`build/verification/human-inspection-v16-source-v1`. Full Refactor/W06/release
work remains active; the [W06 assessment](../../build/verification/w06-contract-assessment-v1/assessment.md)
is a requirements/design assessment, not implemented recovery evidence.
