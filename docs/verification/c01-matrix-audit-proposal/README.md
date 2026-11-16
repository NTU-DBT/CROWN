# C01 evidence-only matrix auditor

2026-11-07. **Excluded audit preparation. C01 is in progress; this package does
not advance C01, the ledger, or the full goal.** The author read and hashed
evidence and wrote this auditor, but did not execute Python, tests, CMake, CTest,
project binaries, symbol tools or benchmarks. Root owns the first execution and
all acceptance. Native sources, root matrix/capture scripts, accepted packages
and historical O07 evidence are unchanged.

[audit.py](audit.py) consumes the designated C01 freeze and terminal matrix
records, their raw logs, actual generated registration/compile/link metadata,
retained clean-build artifacts and new statistics symbol dumps. It uses only
Python's standard library and makes no subprocess, project import, network,
process-status or binary-execution call. It refuses to overwrite an existing
output JSON or sibling log. [ROOT_REPRODUCTION.md](ROOT_REPRODUCTION.md) gives the
exact root invocation and review procedure.

## Frozen identity and partial results

The designated freeze is `build/verification/statistics-execution-freeze.json`,
SHA-256 `c00d2188033aed5a9a12da1cff4d62c57a5888ce520f864a91141d8513d3e671`.
Native scope is 623 files / `25f7143860cf28f6c7ba0e89a5b40708d3fb71fec979408bf1135f0fa45b1ef0`;
execution scope is 676 files / `70916b45f3105b21d281f49c12c0455c9de8f3b2d76daa74bf252f2bb2144f4d`.
The auditor recomputes those current scopes and per-file maps. It checks all ten
historical native manifest **file** hashes, including the preserved O07 seal;
it never rechecks their old entries against the new native sources.

Only `statistics-{debug,release,sanitize,clang,clean-source}-summary.json`
terminal records qualify. An absent, partially published or nonterminal record
remains pending. Its live build/test logs are not inspected as passing evidence.
The six-role statistics symbol record is required for each configuration;
sanitizer additionally requires the parser's undefined-symbol dump. Missing
symbol collection remains pending even if that matrix's tests have finished.

`accepted: true` and `audit_state: accepted_final_matrix` are emitted only when
all five terminal configurations, cross-configuration comparisons, symbol
checks, input pins and any explicit allocation reviews pass. Otherwise accepted
is false. Partial or review-required evidence grants no project acceptance.
The output includes the auditor/freeze hashes, every read evidence hash, each
actual registered name, ordered LastTest outcome and executed command.

## Test and numeric evidence

The 131 names in the new freeze are sorted, not execution order. The auditor
parses each actual `CTestTestfile.cmake`, requires 131 unique registered names,
then compares all ordered LastTest records, their exact argv and working
directories with that registration. It also reconciles the 131 verbose passed
records and aggregate summary. Relative registration order of the 99 legacy
tests is preserved. New tests must retain label C01 and timeout 900; sanitizer
environment settings must apply to every test.

The accepted O07 release LastTest log supplies all 99 historical commands and
numeric rows. Known source/build directory prefixes are normalized for command
comparison. All output rows containing a digit or a boolean assignment are
retained, including group counts, JSON numeric facts, query-family progress,
allocation counts and signed traces. There is no invented expected row total,
blanket timing exclusion, omitted trace population or automatic allocation
waiver. Row totals in the result are observed counts only.

Two narrow normalizations are explicit and retained alongside original rows:
the CLI's named artifact `run_dir` has a volatile timestamp/process suffix, and
D04's printed signed-result sequence is compared as a sorted multiset because
the existing independent fixture asserts signed-key sets rather than enumeration
order. Signs, tuple field order, values, sequences and duplicate multiplicities
remain exact. Unrecognized trace syntax fails instead of being dropped. The
normalization does not excuse changed numeric work, budgets or semantics.

Every observed test's commands/numeric rows are compared across configurations
against the fixed native Release baseline. The 32 added tests also retain their
actual-source contracts and accepted preparation markers: state 14 groups,
owner 18, joint 9 per variant, online 10, scalar/constraint 7; report corpora
31/32 with 15/17 semantic/schema rejections, two legacy byte comparisons and one
native publication-field rejection. Silent collector/runtime-only consumers
must remain silent and pass their actual assertions. Exact selected policy
input/derivation/source/metadata counts are checked for FIFO and LIFO. Accepted
preparation allocation counts are compared as evidence, not silently assumed
immutable across compilers or layout changes.

Any observed allocation-only difference is retained with both complete rows,
test, configuration, baseline, position and a content-derived ID. It blocks
acceptance until root provides an exact, explained approval record. Only named
allocation/fault-count fields may differ; changed row counts, labels, semantic
values, limits or work are not approvable through that mechanism. Unused/stale
approvals fail a complete raw matrix. Nothing in this package approves a future
allocation change. See the [invalid-by-design template](allocation-review.example.json).

## Compiler, parser and archive boundaries

The auditor derives the expected 195 unique target/source entries from the
historical 157-entry clean O07 database plus 14 added library compilations and
24 added consumers. Actual C01 entries must match that exact set. Both runtime
variants have 14 units; both report variants have six. It checks all six strict
warning/error flags, C++23, actual compiler identity/version, optimization/debug
mode, sanitizer/frame-pointer flags and consumer-local assertion enablement.
No excluded proposal path, warning suppression, sanitizer suppression, mixed
runtime/report ABI variant or leaked acceptance/order macro is permitted.

Every target's generated link recipe is read. Production CLI linkage, all
consumer compile/link macro bindings, both runtime-only consumers, the separate
query-only test, and report/runtime separation remain explicit. Archive output
names are distinguished from dependencies. Numeric testing probes must be
absent from production and report archives; testing runtime must define the
exact 12 RuntimeTestProbe methods, including the C01 saturation seam, plus the
two existing observation hooks. Planner baseline isolation and sanitizer parser
runtime references are independently checked from the new symbol dumps.

The pinned vendor archive/Makefile recipe independently derives 96 C units,
outside the raw CMake database. Generated parser compiler/configuration/recipe
evidence is checked for ordinary builds. The clean adapter retains its upstream
Makefile, cache and verbose log, but not its generated parser config file; the
auditor therefore checks the clean actual make invocation and compiler identity
from those retained artifacts. Exactly 96 clean `compiling ...c` labels must
match the archive inventory. Upstream hides expanded per-file C argv; the result
does not pretend those argv were retained.

Fresh clean diagnostics must equal the three precise historical O07 diagnostics:
GNU Make's jobserver fallback and the two upstream upb maybe-uninitialized
warnings. They are preserved limitations, not called safe, fixed or false
positives. No additional/changed vendor or project warning is accepted. Ordinary
configure/build/test logs must have no warning diagnostics.

## Scope and remaining work

[PINNED_INPUTS.json](PINNED_INPUTS.json) binds 92 immutable designated inputs,
including source contracts, accepted preparation logs and the historical audit
pattern. Native matrix results are intentionally not frozen as completed by this
proposal; root's audit run pins whichever terminal evidence actually exists.
The source/input/package manifests seal this authoring work. No execution,
syntax-check or audit-pass claim follows from their existence.

Root must inspect the first result, resolve any real evidence/schema issue,
review legitimate allocation changes separately, and retain successive outputs.
The independent final source audit and ledger/handoff acceptance are separate
root gates even after this script accepts the complete matrix evidence.
