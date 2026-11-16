# Source baselines and provenance

Status: **A02 in progress; acceptance remains open.** This record reflects the
workspace inspected on 2026-11-05. It separates source inspection from build
and experiment evidence. Commands below are documented recipes, not claims
that they were run.

## Pinned sources

| Source | Pin and verification | Availability here |
| --- | --- | --- |
| NTU-DBT/CROWN (R1) | `master` at `e369a623517723b3be3ea3e9806779f3c591e7f9`. `git rev-parse HEAD` returned this commit. The relevant local files listed below have Git blob IDs matching `HEAD:path`. | Legacy Scala/Flink source is present. The source files listed below match the pinned commit; successor work is also in the worktree. The root `README.md` is being updated for the successor and is excluded from the local fingerprint table. |
| hkustDB/DynaGox (R2) | `main` at `c6811db68a34ab3b32722968c4e1e821f730c5ac`, as recorded in `Refactor.md` §§1.2 and 18.2. The [official GitHub API](https://api.github.com/repos/hkustDB/DynaGox/commits/c6811db68a34ab3b32722968c4e1e821f730c5ac) confirms the commit exists (committer date 2025-10-06 UTC; message “Update Readme.md”); it is unsigned (`verified: false`). Its tree is `26b9d6dffc35eee1336f48471279447e3f40fc25`; the recursive tree response was not truncated. | Relevant files were fetched from official raw URLs at this immutable commit and fingerprinted below. No local DynaGox checkout or build was made. |

The CROWN paper pin is P1 in `Refactor.md` §18.1: Qichen Wang, Xiao Hu,
Binyang Dai, and Ke Yi, “Change Propagation Without Joins,” PVLDB 16(5),
2023; corrected full version `arXiv:2301.04003v2` (2023-12-02). The plan says
the arXiv v2 corrects errors in the original version.

The DynaGox `Readme.md` identifies the repository as code and resources for
“Approximate Query Processing under Updates,” matching P12 in `Refactor.md`
§18.1: Binyang Dai and Ke Yi, PACMMOD 3(6), article 295 (2025) / SIGMOD 2026.
The plan records publisher metadata and repository/abstract-level evidence;
the full publisher paper was not accessible during that review. The repository
pin does not imply independent verification of the paper's full results.

The planner/runtime research pins below are taken from Refactor.md's source
register; no fresh full-paper review is claimed by this implementation run.

| Source | Immutable version from the plan | Current implementation use |
| --- | --- | --- |
| P1, Change Propagation Without Joins | arXiv `2301.04003v2`, 2023-12-02 | Target contract; no legacy propagation copied |
| P2, Towards Parameterized Hardness on Maintaining Conjunctive Queries | arXiv `2603.14754v1`, 2026 | Planner requirements/counterexamples retained; no residual height certificate implemented |
| P3, Succinct Structure Representations for Efficient Query Optimization | arXiv `2603.15465v2`, 2026-08-18 | Future candidate/search interface; no meta-decomposition implementation yet |
| P4, Towards Update-Dependent Analysis of Query Maintenance | PODS/PACMMOD 2025, article 117, as identified in the plan | Future update-contract review; no FIFO guarantee implemented |

## Inspected CROWN files and local fingerprints

These files are relevant to the source inventory in `Refactor.md` §18.2. The
SHA-256 values fingerprint the local bytes. For the CROWN files in this table,
the local Git blob ID also matched the corresponding path at the pinned HEAD.

| Local path | Role | SHA-256 |
| --- | --- | --- |
| `crown/README.md` | Query workflow, inputs, modes, and prerequisites | `f44450e23e633d11642a4dfe6c4a2e9903936bbaa95212b0fe0b019272419c9e` |
| `crown/pom.xml` | Scala/Flink dependency and packaging versions | `134439a5f1415d8b9bd6dedbf6ffc6410c6319ef2f8b871205c490f68f18d3d6` |
| `crown/src/main/scala/RelationType/Relation.scala` | Relation state and enumeration behavior (R4) | `1e2da8959fd872b4ca15f065878b376744287895c7e9755c5bc2e5b143ec3cab` |
| `crown/src/main/scala/RelationType/Attributes.scala` | Tuple representation and annotations (R5) | `d482429d6a792df5d64510d6a138967b797e908f2909071b28a164c4272f3a5b` |
| `crown/src/test/scala/OutputResultTest.scala` | Existing asserted result traces (R12) | `6ee3e8fa1a272f855baf7705ccedcc55a5e190dce0e09476fe89299999674aa1` |
| `experiments/README.md` | Experiment setup, modes, commands, and result paths | `fac16aa7ab2d51607a544ae589f008ca2d9ca1d0a02725997e069fb54aa6303a` |
| `experiments/build_all.sh` | Legacy experiment build orchestration | `6028059915cebae32959983179de1e5d31505592ffb3cfaa4c48a01348dce93e` |

`Refactor.md` §18.2's DynaGox paths map to `dynagox_cpp/implement/...` in the
pinned tree. These remote SHA-256 values were computed from the raw bytes
returned by `raw.githubusercontent.com/hkustDB/DynaGox/c6811db68a34ab3b32722968c4e1e821f730c5ac/`;
they fingerprint remote source, not files checked out locally.
For example, the README fingerprint can be recomputed with:

```sh
curl -fsSL https://raw.githubusercontent.com/hkustDB/DynaGox/c6811db68a34ab3b32722968c4e1e821f730c5ac/Readme.md | sha256sum
```

| Pinned remote path | Role | SHA-256 |
| --- | --- | --- |
| `Readme.md` | Repository contents, paper, build/reproduction instructions | `9021b12aba40dd37356e5b6ff853862f568acc2c51c1c091f462de8499f47f93` |
| `dynagox_cpp/implement/CMakeLists.txt` | DynaGox C++ build root | `73e236b9117a9c75dffaca586eab37e5fa1f98171e8169134b57d9f21aa4e536` |
| `dynagox_cpp/implement/experiments/CMakeLists.txt` | Fixed DynaGox/CROWN executables and query libraries | `f9e77d0ac48dfc6169acf6805fb35446ab9a34e8312e12e6164e872f7c24834b` |
| `dynagox_cpp/experiments/scripts/compile_all.sh` | Release configure/build script | `01a2a42de9f1e9eada14bd05d5625ced255227d06affa990321ce0eba194cf1f` |
| `dynagox_cpp/implement/experiments/src/crown/main.cpp` | Fixed query dispatch and CLI modes (R7) | `19b6d527b69a895559c591b73178ab88b8611ca7bbec8795ed0eaf131ac61d15` |
| `dynagox_cpp/implement/experiments/src/crown/crown_line5cd.cpp` | One inspected CROWN specialization (R9) | `431014059d0b5d5deea1ff410d995de5710c78fe5608165cc17f7953bc241b31` |
| `dynagox_cpp/implement/cmake/fmt.cmake` | Pinned fmt dependency | `39b8cf57ee754a391bbb505e580f38f0c34104751eba359adf39ee1320874c77` |
| `dynagox_cpp/implement/cmake/ClangFormat.cmake` | Configure-time formatter requirement | `85ee94792262fc8984766c09dfb20adbce0c5bd80d42438adae96b7c917cbe32` |
| `dynagox_cpp/experiments/scripts/common.sh` | Resolves the CMake source/build paths | `47b95f5f8809f9724bd5359ea49a1bcc5101a36159f92f04e3df6f577afb0827` |
| `FIVM/LICENSE` | Nested F-IVM license file, inspected separately | `1754ecf960563026ff2c867d5539ed34c287f2b8ce95c07059619122dab00abb` |

The plan describes complete source trees and says key runtime, index, build,
entry-point, test files, and representative query implementations were
inspected; it did not claim an exhaustive review of every specialization or
vendored compiler file. This remote inspection likewise covers only the files
listed above and the complete tree's notice-path inventory.

## Legacy commands and modes

The CROWN README documents this package command from `crown/`:

```sh
mvn clean package -DskipTests=true
```

It then describes MiniCluster execution with
`java -cp target/CROWN-1.0-SNAPSHOT.jar {job_name} --path {base_path} --graph {file_name}`,
or Flink standalone submission with `flink run -d -c {job_name}` and that
JAR. The query is selected by a handwritten job/process-function class: the
documented workflow rewrites SQL to a natural join, chooses a generalized
join tree, and implements the process function. Its graph input example uses
`+` for insertions, `-` for deletions, and `*` for full enumeration. The SNB
example repeats `+|R|...` for its deletion line, so that input notation is
ambiguous in the README. Full and delta enumeration controls are exposed;
documented parallelism values are `{1, 2, 4, 8, 16, 32}`, and COUNT is the
documented supported aggregation.

For paper experiments, `experiments/README.md` documents setup followed by
`cd experiments && bash build_all.sh` and `bash run_all.sh`; the latter runs
the Figure 7–10 suite. This workflow expects external data, DBToaster, HDFS,
and other configured dependencies. Result files are documented under
`experiments/log/result/`. The README lists Java 1.8.0_321, Scala 2.12.15,
Maven 3.8.4, sbt 1.4.3, g++ 11.2.0, .NET 5.0.403, OCaml 5.0.0, Hadoop 2.7.0,
and PostgreSQL 10.23 among its requirements.

The `crown/README.md` prerequisite list instead says Java 1.8.0_60 and Scala
2.12.12. Its POM pins Java 8, Scala 2.12.7, and Flink 1.13.5. These recorded
versions differ; treat the files as historical instructions rather than a
reconciled toolchain lock.

### DynaGox C++ baseline

At the pinned DynaGox commit, `dynagox_cpp/implement/CMakeLists.txt` requires
CMake 3.23 and sets C++23. It pins `fmt` 11.1.2 with CMake FetchContent and
requires a `clang-format` executable at configure time; no compiler or
`clang-format` version is pinned in the inspected files. FetchContent may
need network access for fmt.

The DynaGox `Readme.md` says to run
`bash dynagox_cpp/experiments/compile_all.sh`, but that path does not exist in
the pinned tree. The tree contains
`dynagox_cpp/experiments/scripts/compile_all.sh`. From the repository root,
the checked-in build script can be invoked as:

```sh
bash dynagox_cpp/experiments/scripts/compile_all.sh
```

The script removes `dynagox_cpp/implement/build`, then runs
`cmake -DCMAKE_BUILD_TYPE=Release ..` and `cmake --build .` from that build
directory. This command is recorded as source evidence only; it was not run.

`dynagox_cpp/implement/experiments/src/crown/main.cpp` dispatches among fixed
query classes rather than compiling arbitrary SQL. Its parser handles `--input`,
`--query`, `--mode full|delta`, and `--print-result`; an input line beginning
with `*` triggers a milestone. The hard-coded query names are `line5c`,
`line5s`, `line5m`, `line5cd`, `line5gc`, `line5sd`, `dumbbell`, `lsqb6`,
`job8`, `job8s`, `job8m1`, `job8m2`, `job16`, `job19`, `ceb1`–`ceb4`,
`tpch3`, `tpch5`, `tpch8`, `tpch9`, `tpch10`, `tpcds15`, and `tpcds19`.
The CLI's full/delta flag is passed only to some specializations, so it does
not establish support for every operation in every query.
`crown_line5cd.cpp` discards the first input field and calls only insert
operations for its five relations. The README also lists data-conversion
variants for graph, TPC-H, and TPC-DS inputs; those are input-preparation modes,
not a guarantee of runtime operation support.

## Evidence status

| Baseline | Source inspection | Successful legacy build | Reproduced experiment |
| --- | --- | --- | --- |
| CROWN | Plan records inspection of key source areas in the complete tree; relevant local files and hashes above were checked. | **No successful build evidence recorded.** The documented Maven commands were not run for this record. | **Not reproduced.** No result or timing evidence recorded. |
| DynaGox | Selected files inspected remotely through official GitHub API/raw URLs at the pinned commit; no local checkout. | **Not built.** The pinned build recipe is recorded above. | **Not reproduced.** |

These fields are independent. Source inspection does not imply that a build or
experiment succeeded. No baseline timing or performance comparison is claimed.

## Successor implementation and licensing

The new C++23 core under `include/`, `src/`, `apps/`, and `tests/reference/`
is an independent implementation. No copied CROWN or DynaGox source file was
observed in those paths. The reuse policy in `Refactor.md` §1.4 keeps legacy
artifacts separate, uses CROWN state transitions as a behavioral reference,
and treats DynaGox index designs as candidates for adaptation only after an
ownership and arithmetic audit. Any later source or design reuse needs an
entry in this record. The first vendored dependency is
nlohmann/json 3.12.0. The exact original single header is now preserved at
`third_party/nlohmann/upstream/nlohmann/json.hpp`, SHA-256
`aaf127c04cb31c406e5b04a63f1ae89369fccde6d8fa7cdda1ed4f32dfc5de63`. The active
`third_party/nlohmann/json.hpp` includes the CROWN exceptional-cleanup repair
and has SHA-256
`f763c58b102e65242d09275aec4b2f343268280ab4587b15587ad143b2e2a406`.
`third_party/nlohmann/patches/crown-cleanup-oom.patch` preserves the complete
local difference (SHA-256
`65acb363a5b9787022eb3eb058641a0533a6cf6b642db5605a7c5848d681c9a9`);
`third_party/nlohmann/README.crown.md` records its origin, limits and isolated
original-header control. This 2026-11-07 local vendor update changes cleanup
after `std::bad_alloc`, retaining normal flattening, type layout and serialization.
It is not an upstream release change or an additional project license decision.
All original copyright text is retained, and
`third_party/nlohmann/LICENSE.MIT` is present (SHA-256
`46a65cffd1ea955132d95a8dd921640714a8d6b537d2e4e482d31145ae95b603`). The
CMake configuration checks the active header, original header and local patch
hashes. All project C++ units use the same active header; the upstream control
links no project archive. The C02 native publication and matrix remain pending.

The SQL syntax wrapper now uses libpg_query 18.1.0 at commit
`c1546e7e97edc93fe8474d7a59881e91fbf48cfc`, archive SHA-256
`2d3486cf6a9d3955b53e66235db39d62b54216c820cd392ab66dc842c5b1316d`.
The original source archive is vendored unchanged at
`third_party/libpg_query/libpg_query-18.1.0.tar.gz` and checked at configuration
and before extraction. The native build compiles the bundled generated
PostgreSQL 18.6 sources in the binary directory, using the upstream `make build`
target with no download or regeneration. All original notices remain inside
the archive, with copies for libpg_query, PostgreSQL, upb, utf8_range, and
xxHash under `third_party/libpg_query/notices/`. The dependency lock and
[wrapper contract](sql_parser.md) record its BSD/PostgreSQL/component notices
and owned syntax interface. The earlier optional spike remains historical.

The F03 binder is independent implementation code. Its SQL scope/output
contract was checked against PostgreSQL 18's
[table-expression documentation](https://www.postgresql.org/docs/18/queries-table-expressions.html)
and [EXISTS documentation](https://www.postgresql.org/docs/18/functions-subquery.html).
Default output-label behavior was inspected in the PostgreSQL
[`parse_target.c` reference](https://github.com/postgres/postgres/blob/REL_18_STABLE/src/backend/parser/parse_target.c)
on 2026-11-05. That moving-branch URL is a reference inspection, not a build
input or release dependency; no source code from it was copied. The native
build continues to use only the pinned archive above. Binder contracts and
independent fixtures are fingerprinted in its verification packet.

The F04 normalizer and support-counted adapters are independent implementations
of the occurrence/equality/identity contract in Refactor.md. Their local SQL
truth tables were checked against PostgreSQL 18's
[logical operators](https://www.postgresql.org/docs/18/functions-logical.html)
and [comparison predicates](https://www.postgresql.org/docs/18/functions-comparison.html)
on 2026-11-05. No external normalizer or adapter implementation was copied.

F05's digest and canonical-identity code is independent implementation code.
SHA-256 follows the algorithm and fixed constants in the primary
[NIST FIPS 180-4 standard](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf),
inspected on 2026-11-05. Known empty/abc/multi-block/million-a vectors and
independent Python `hashlib` checks verify the implementation; no external
hash implementation was copied or added as a native dependency.

F06's bounded recognition/admission and format-2 constant grounding are
independent implementations extending the existing native frontend and GYO.
The fixed-head correction follows equality substitution in Refactor.md's CQ
model; its concrete legacy/new geometry, preserved v1 replay and independent
SQL/CQ checks are recorded in decision 0008 and the admission verification
packet. No external admission/normalizer implementation was copied.

The exact-tree components are independent code. The literal oracle follows
the complete normal-form family in Refactor.md §5.4. The memoized branch
partitions and independently replayed lower-bound states are justified in
[planner_proofs.md](planner_proofs.md); they do not copy external planner
source or depend on the residual-height recipe. Their algorithm/version and
current source fingerprints are recorded in the oracle verification packet.

No root project `LICENSE`, `NOTICE`, or `COPYING` file was found, and no new
project license decision is recorded in the workspace. The vendored
dependency notices apply to their respective components only. This record makes
no license choice for the project or legacy sources.

At the pinned DynaGox commit, the root tree contains no `LICENSE`, `NOTICE`,
or `COPYING`, and the complete non-truncated recursive tree contains no
repository-root file with those names. The recursive tree does contain nested
files for included components:
`FIVM/LICENSE`, `FIVM/backend/dbtoaster/LICENSE`,
`dbtoaster_cpp/dbtoaster-backend/LICENSE` and `NOTICE`, and
`dbtoaster_cpp/dbtoaster-frontend/LICENSE`. The DynaGox README says its
MultiHashMap is inspired by F-IVM and describes F-IVM as Apache 2.0; the
inspected `FIVM/LICENSE` is Apache 2.0 (remote SHA-256
`1754ecf960563026ff2c867d5539ed34c287f2b8ce95c07059619122dab00abb`). These
nested notices do not establish a repository-wide DynaGox license. This is a
notice-path inventory, not a legal conclusion about the DynaGox source.

## A02 acceptance still open

This record verifies the DynaGox commit exists and fingerprints selected
remote source files, while keeping remote inspection distinct from a local
checkout, build, or experiment. The DynaGox environment record has no pinned
compiler or formatter version; the CROWN documentation retains its conflicting
historical Java/Scala versions. A02 remains in progress; any actual legacy
source or design reuse must be added with its exact source provenance. No
DynaGox source was copied here. No project license is selected in this record;
that remains an owner decision before any legacy source is copied into a
distributable release, and does not block independent new-code work. Build and
experiment statuses are recorded separately; the absence of those runs alone
is not an A02 acceptance failure.
