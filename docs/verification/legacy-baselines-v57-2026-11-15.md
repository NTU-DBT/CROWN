# B01 legacy baseline acceptance and full review continuation — V57

B01 is technically verified for the named isolated builds and tiny output
replays. The [usage and reproduction guide](../legacy_baselines.md) states source,
toolchain, query, input, output and cost boundaries. The original Refactor goal
and release gates remain open.

## Requirement receiving

| Refactor B01 requirement | Authoritative received evidence |
| --- | --- |
| Isolated pinned Scala and C++ baseline builds | All 64 Scala and 144 C++ files Git-blob match their immutable commits. Private source/build/dependency directories preserve the worktree and original inputs. Unmodified Scala compile/package and C++ Release CROWN target builds pass. |
| Small supported replays independently verified before timing | Actual Scala 22 snapshots/18 signed records, C++ line5cd 10 milestones and line5gc 22 full +22 replacement milestones match independent direct relational evaluation. No baseline timing is used. |
| Build-failure records | The prior host-JDK JRT failure and current published Scala parser-test failure are preserved separately from successful compilation/package and independent replay. |
| Published reproduction distinguished from local modifications | Source/POM/tests remain unchanged. The new Scala verification adapter is separate, with its exact source/classes pinned. Toolchains differ from the historical paper environment; neither published-binary identity nor complete experiment reproduction is claimed. |
| Unsupported operations excluded | line5cd ignores signs and has no qualified delta protocol; only unique positive inserts/full milestones are admitted. line5gc full and absolute-replacement modes have their own valid mixed trace. Other dispatch queries, large-count arithmetic and unqualified Scala paths remain outside this qualification. |

A02 remains in progress. The user's instruction defers licensing checks while
preserving rights/notices, so it is not a technical blocker to these B01 results.
No baseline implementation is copied into the new engine.

## Actual builds and outputs

Scala uses explicit Temurin 8u472 / Maven 3.8.7 and the unmodified Scala 2.12.7 /
Flink 1.13.5 POM. All 47 main source files compile. Packaging passes with
`-DskipTests=true`, yielding a 112,551,945-byte shaded JAR plus the original JAR.
All 375 main class bytes match before/after packaging and inside both JARs,
including the classes used by the accepted replay. There is no Main-Class
manifest or shaded-runtime replay claim. Generated dependency-reduced-pom.xml
is separately identified as build output. The private 94-JAR test/runtime
classpath, Java libraries, compiled adapter classes and commands are pinned.

The published OutputResultTest executes one test and fails: its reorder parser
expects numeric CSV followed by names, while JoinedAttributes emits named pairs
such as `(D,4)`. That test remains unchanged. A separate verification-only keyed
Flink harness feeds the actual original L3 process function and captures raw
signed text plus real current-result iterator rows. All 22 events agree with a
literal G1/G2/G3 join, including branching, last witnesses, empty results,
negative integers and reinsertion. No captured duplicates are erased.

Full drains after every input are part of the verified Scala schedule; the
original iterator can change global-alive markers. This does not qualify a
delta-only or maintenance-only run, graph Job routing, MiniCluster deployment,
windows or other process functions. Compiler minor-version and shading
warnings remain visible in the original logs.

C++ uses GNU 13.3 / CMake 3.28.3 Release, exact fmt 11.1.2 and Catch2 v3.7.1 sources,
and a genuine private clang-format 18 binary. All 144 published inputs remain
unchanged. Only crown_exec and its CROWN dependencies are built; no approximate
algorithm is selected. Complete actual flags, source/dependency/toolchain,
archive/library and executable hashes are retained.

line5cd matches all 10 milestone distinct counts. Added endpoint witnesses change
full path counts without inflating internal distinct quadruples. line5gc matches
all 22 milestones in each mode:22 full group records and 24 absolute replacements,
including 8 zero removals. Source inspection and per-milestone state folding
establish the replacement interpretation; they are not signed aggregate deltas.
The same unchanged executable supplies all three qualified C++ runs.

The original C++ diagnostic reads VmPeak rather than RSS and leaks its /proc
file handle at milestones. It supplies no target-RSS evidence or qualified
long-milestone timing. Floating-point/epsilon baseline arithmetic is qualified
only by these tiny integer cases, separately from the new engine's semantics.

## Findings, review and regression

| Finding | Received correction or disposition |
| --- | --- |
| Host Java cannot compile the pinned Scala stack | Select a separately pinned genuine Java8 environment; original source/POM remain unchanged. |
| Published test parser disagrees with current tuple formatting | Preserve its failure; new independent adapter/checker consumes actual named pairs and direct iterator rows. |
| Offline C++ checker accepted updates after the last observed milestone | Reject a pending update tail; three separate mode controls isolate the missing final observation. |
| Python int admitted a spelling rejected by Scala | Require ASCII signed-decimal int32 tokens. The 0_1 control keeps mathematical results unchanged and isolates admission. |
| Documentation checker had a separate suffix inventory | Add the same exact Scala-helper path to its independent inventory. The original failed check is preserved; the broad Scala suffix remains excluded. |
| Proposed usage cards attached costs/negative controls to the wrong region | Root receives exact4positive+8negative and16negative region scopes, setup/finally phases, output exclusive-create semantics and actual inventory traversal costs. |

Parallel workhorse source/actual-output reviews and a separate final semantic
review received the two checker fixes. Luna supplied 24 seven-field usage cards
and 1,560 exact source rebindings. Root individually received the code/callers,
corrected 12 proposed field descriptions, fixed one exact section reference and
amended the inventory contract.
Root also received 18 checker source bindings and two inventory semantic amendments
when the final documentation check exposed its separate inventory mismatch.
The Scala helper's two generic structural chunks are not method/Scala-AST
boundaries. No new Astra invocation was used in V57.

The final offline regression passes all 4 actual-capture cases and 24 negative
controls, including signed duplicates, zero-removal loss, wrong snapshots,
booleans, sequence/Base64, unsupported operations, unobserved tails, optimized
Python guards and existing-report preservation. The checker validates retained
capture bytes; source/build/run receipts separately establish actual execution.
It does not launch or time a baseline or atomically publish file contents.

The current Debug and sanitizer configurations each pass 2 scoped CTests:
legacy_replay_checker and clean_source_snapshot. A separate real clean source
copy configures and runs the new offline CTest without an external JDK/Maven/
baseline build. Production tests-OFF configuration passes. There are 362 current
registrations; no new full 362-test matrix or sanitizer run of the legacy C++
executable is claimed.

## Source and human-inspection scope

All 370 maintained production paths remain byte-identical to V56. Full-source
receiving covers all 427 primary production/build/tool/example paths: retain 425
prior full reads, receive 3 changed files (CMake/generator/checker) and 2 new tools.
The new integration script, actual captures and traces have scoped inspection.
This is not a fresh full read of every inherited test file or a universal
correctness proof.

The index maps 788 files /179,848 lines /20,105 blocks. All 17,144 nonblank blocks
have 19,579 authored seven-field contracts; 2,961 regions are blank spacing.
V57 adds 24 cards, rebinds 1,578 pre-existing CMake/generator/checker attachments
and amends three prior inventory semantic cards. Appending the CTest leaves all 45
existing numeric CMake references unchanged. Generated maps, independent
source/registry checks and guide links have separate evidence.

The only new implementation is optional offline verification and its CTest.
There is no engine update hook, retained row/index graph, shared-query state,
production error framework or new execution dependency. Direct tiny oracles can
have cubic/fifth-power work and materialized outputs; these costs are stated
rather than assigned to engine maintenance or benchmarking.

Evidence root: `build/verification/legacy-baselines-v57-v1`.
Independent packets: `v57-b01-scala-recon-v1`, `v57-b01-cpp-recon-v1`,
`v57-b01-independent-review-v1` and `v57-b01-spec-proposal-v1`, under
`build/verification`. Source seal:
`build/verification/human-inspection-v57-progress-v1.json`.
The [handoff](../handoff.md) records the next work and preservation rules.
Ledger: 63 verified /1 in progress (A02) /14 not started =78.
