# Separate static review of root's C02 matrix drivers

These are root-owned execution recipes, reviewed without executing/importing
Python, CMake, CTest, `nm`, a compiler or a binary. Exact copies are retained under
`root-drivers/`. The examined original identities are:

| Root driver | SHA-256 |
| --- | --- |
| `/tmp/crown-ranking-matrix.py` | `e8a068ceaf27922a433b0e73c16929eea95ff956cd228f080c0d8bf016176fa7` |
| `/tmp/crown-ranking-symbols.py` | `876a727a431ec05234c723359afe8f124a10ebb8f36fcd7352be796837f035bb` |
| `/tmp/crown-ranking-clean-evidence.py` | `83fe42168d49a2bf980a1fc0e66bb9a619c4b1ae548c5e168ba52271db199c98` |
| `/tmp/crown-ranking-clean-matrix.py` | `fe9b62bda41849cd23f9fdcf7bf431ed4b7206105ffd4ab2ef0ef2fe428dfe18` |

The differences from the preserved `crown-statistics-*` recipes are limited to
the new `ranking-*` evidence/freeze paths, verbose ordinary builds, exclusive
ordinary phase logs, the future freeze's expected CTest count, three new ranking
archive roles, and the clean adapter's 3,600-second per-command ceiling. The
repository's clean-build helper remains unchanged.

The ordinary driver fingerprints native and complete execution inputs before
and after its configure/build/test sequence and compares the initial identities
with the new freeze. It fails on a nonzero subprocess result, an unexpected
final test count or source drift. Its verbose test output and retained successful
LastTest output are evidence for a later independent row/command audit, not a
replacement for that audit. A failed test's verbose phase log is preserved;
the dedicated LastTest copy occurs on the successful-test branch.

The symbol collector captures nine archives: plan, pure ranker, production and
testing ranker bridges, planner testing, production/testing runtime and
production/testing report. The sanitizer caller can request the parser's
undefined symbols as a tenth role. Each archive is hashed before/after capture;
stdout/stderr are preserved and hashed. Production runtime test-seam absence and
testing-runtime seed presence are checked. These defined-symbol dumps do not by
themselves establish every dependency boundary; final link commands, macro
variants, actual compile entries and pure/runtime-only links remain necessary.
Its recorded status correctly says independent semantic audit is pending.

The clean adapter loads the unchanged repository helper and wraps its snapshot
and command functions in memory. It checks both the original and copied source
identities, retains compile commands, CMake cache, test registration, LastTest,
flags/link records and the vendor Makefile before the helper removes the
temporary tree, and captures the same archive roles. Completion requires the
helper's success, stable source identities and actual temporary-tree removal.
The outer clean matrix additionally checks the freeze's expected test count.
The longer ceiling changes execution allowance, not test selection or math.

One current execution assumption is explicit: the Clang configure command
reuses `build/clang-debug` without supplying compiler or build-type flags.
The inspected cache selects the held clang-18/clang++-18 paths and Debug; the
relevant original lines are retained under `baseline/clang-cache-fields.txt`.
This is suitable for that held cache. If the directory is replaced or rebuilt
from scratch, root must select those compilers/Debug explicitly and verify the
actual cache and compile flags before accepting the Clang leg. No empty-cache
Clang reproducibility claim follows from the driver alone.

No blocking defect was found for the stated frozen-input/current-cache run.
The recipes fail closed rather than authorizing partial native acceptance.
Root must still inspect every terminal result, all 143 registered names and
commands, numeric rows, actual warning/sanitizer/compiler settings and any
legitimate allocation-only changes before advancing C02. This appendix does
not approve hypothetical future driver edits or execute the supplied recipes.

The additional post-integration freeze is reviewed separately in
`ROOT_FREEZE_APPENDIX.md`. Its accepted static revision binds the author FILEs
and every unmapped execution byte to the freshly captured integration baseline,
and records the retained predecessor toolchain/compiler identities. This makes
the Clang-cache assumption explicit in the future freeze; the native matrix
must still verify the actual configured compiler and flags.
