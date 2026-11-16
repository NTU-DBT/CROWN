# Pinned legacy comparison environments

B01 builds the original Scala/Flink CROWN and DynaGox's C++ CROWN baseline in
separate directories, without changing their source, tests or build definitions.
Independent tiny replays pass; [B01 technical acceptance](verification/legacy-baselines-v57-2026-11-15.md)
is received within the named scope. The overall Refactor goal remains active.

These are reproductions of the pinned source under explicitly recorded local
toolchains. They are not reproductions of the paper's complete experiments or
historical machine/software stack. No baseline timing or speedup is claimed.
The new plan-driven engine imports none of these baseline implementation files.

## Source and toolchain identity

| Input | Immutable identity | Received scope |
| --- | --- | --- |
| Scala/Flink CROWN | NTU-DBT/CROWN `e369a623517723b3be3ea3e9806779f3c591e7f9` | All 64 staged files Git-blob match; unmodified POM compiles 47 main sources and packages the original/shaded JARs. |
| C++ CROWN baseline | hkustDB/DynaGox `c6811db68a34ab3b32722968c4e1e821f730c5ac` | All 144 staged files Git-blob match the pinned tree; only the exact CROWN executable target is built. |
| Java | [Temurin `jdk8u472-b08`](https://github.com/adoptium/temurin8-binaries/releases/tag/jdk8u472-b08), Linux x64 HotSpot | Archive SHA256 `5becaa4ac660e844c5a39e2ebc39ff5ac824c37ff1b625af8c8b111dc13c3592`, checked against the official release asset digest. |
| Scala stack | Maven 3.8.7; Scala 2.12.7; Flink 1.13.5 | POM versions unchanged; private Maven repository, 94 resolved test/runtime JARs pinned. |
| C++ stack | GNU 13.3.0; CMake 3.28.3; Release | Actual compiler, linker, flags, libraries and executable are hashed; no source portability patch. |
| fmt | 11.1.2, commit `8303d140a1a11f19b982a9f664bbe59a1ccda3f4` | Exact preselected source, using the baseline's declared version. |
| Catch2 | v3.7.1, commit `fa43b77429ba76c462b1898d6cd2f2d7a9416b14` | Required by the baseline's unconditional test configuration even when building only `crown_exec`. |
| Formatter | Ubuntu clang-format 18.1.3 | Genuine privately extracted binary; configure finds it, and no formatting target is run. |

The [earlier source record](source_baselines.md) describes its dated inspection,
not these new build results. Java 8 is selected explicitly; the host `java` and
`javac` resolve to different modern versions. Source archives, dependency
metadata and command receipts live in `build/verification/legacy-baselines-v57-v1`
and the separate Scala/C++ receiving packets. Build/cache outputs stay under
`build/legacy-baselines-v57-v1`. Completed packets and accepted prefixes are
immutable; reproduce into a new directory.

## What is actually checked

| Baseline path | Query and admitted inputs | Actual independent comparison |
| --- | --- | --- |
| Scala `L3ProcessFunctions(2)` through Flink's keyed test harness | Full `G1(A,B) ⋈ G2(B,C) ⋈ G3(C,D)`; three independently labelled set inputs; valid inserts/deletes of int32 pairs | 22 events, all 22 current snapshots and all 18 raw signed output records. Includes branching, last-witness deletion, empty results, negative values and reinsertion. |
| C++ `line5cd`, milestone full mode | Five copies of one directed edge set; distinct internal quadruples `(v1,v2,v3,v4)` of length-five walks; unique positive insertions | All 10 milestone counts: `0,0,0,0,0,1,1,1,1,2`. Endpoint witnesses change full walk counts to `1,2,4,4,8` without falsely changing distinct output. |
| C++ `line5gc`, full mode | Same five-copy join, grouped by middle edge `(v2,v3)`, with valid positive-edge inserts/deletes/reinserts | All 22 milestone states; 22 printed group records. |
| C++ `line5gc`, CLI delta mode | Same grouped query | All 22 milestone states after folding 24 absolute current-count replacements, including 8 zero removals. These records are not signed aggregate differences. |

The Scala [verification adapter](../tools/support/CrownReplay.scala) is new,
separate verification code. It feeds the unchanged published process function,
captures raw named-pair delta text, and immediately reads the genuine full-result
iterator into owning integer rows. It does not replace propagation or install a
new output algorithm. Sorting snapshots preserves duplicates. Full drains after every event are part
of this verified schedule: the original enumerator can update global-alive
markers. This is not a delta-only or maintenance-only execution qualification.
The first nine
inputs follow the published test fixture; later inputs extend its coverage.
This harness does not qualify the graph Job's physical-to-alias routing, a
MiniCluster deployment, windows, aggregates, distributed execution or other
Scala process functions.

The [offline checker](../tools/check_legacy_replay.py) performs a literal
three-relation join for Scala and a direct five-copy self-join for C++.
It checks signed multiplicities and snapshots without deduplicating captured
rows, validates complete C++ query/milestone envelopes and interprets replacement
zeros as removals. Trace admission requires a final observed graph milestone and ASCII signed
decimal Scala int32 tokens. It rejects duplicate inserts, absent deletes,
unqualified signs and out-of-domain values. It reads each captured input once,
hashes those exact bytes, refuses to overwrite reports and publishes a pass
only after every check completes. It launches no baseline and certifies no
execution provenance by itself; the separate source/build/run receipts provide
that binding. Its work can be cubic or fifth-power in tiny relation size, with
materialized join paths and captured outputs; it is a correctness tool.

The [maintained traces](../benchmarks/legacy/replay/scala-l3-mixed.txt),
[distinct-count trace](../benchmarks/legacy/replay/line5cd-insert-only.txt) and
[grouped-count trace](../benchmarks/legacy/replay/line5gc-mixed.txt) retain exact
inputs. [Capture provenance](../tests/legacy_baselines/captures.json) binds exact
copies of actual stdout to the external execution receipts. The
[offline regression](../tests/integration/legacy_replay_checker.py) uses those
captures and corruption/unsupported-input controls, including optimized Python
guards and immutable existing output. Its CTest needs no JDK, Maven, formatter
or downloaded baseline source.

## Build and replay

Stage source from the immutable commits into a fresh private directory. For
Scala, use `git archive <pin> crown`, not the successor worktree or its existing
`crown/target`. For C++, the official archive is
`https://codeload.github.com/hkustDB/DynaGox/tar.gz/c6811db68a34ab3b32722968c4e1e821f730c5ac`;
its received SHA256 is `600698807d7116acef36d87c4e4d42859ba773aa133490ef1d3cf63e2e36cf2e`.
Verify extracted files against the pinned Git tree. Preserve all original
notices. The checked-in legacy `compile_all.sh` removes an in-source build;
invoke CMake explicitly against the isolated tree instead.

With `task_cpp`, `task_build`, `task_fmt`, `task_catch` and `task_formatter`
pointing to the staged source, fresh build and pinned dependencies:

```sh
cmake -S "$task_cpp" -B "$task_build" -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_COMPILER=/usr/bin/c++ \
  -DFETCHCONTENT_SOURCE_DIR_FMT="$task_fmt" \
  -DFETCHCONTENT_SOURCE_DIR_CATCH2="$task_catch" \
  -DCLANG-FORMAT_PATH:FILEPATH="$task_formatter" \
  -DFETCHCONTENT_FULLY_DISCONNECTED=ON
cmake --build "$task_build" --target crown_exec --parallel 2
"$task_build/experiments/crown_exec" --query line5cd --mode full --print-result \
  --input benchmarks/legacy/replay/line5cd-insert-only.txt
```

For Scala, select the private Java 8 `JAVA_HOME`/`PATH` and private Maven
`-Dmaven.repo.local` explicitly. The accepted POM commands are `compile`,
`-Dsuites=OutputResultTest -DskipTests=false test`, and
`-DskipTests=true package`. The middle command fails as described below; the
others pass. The package command deliberately skips tests and is not test
acceptance. The JAR has no `Main-Class`; use an explicit classpath/entrypoint.
The complete dependency-classpath export and Scala 2.12.7 helper compile/run
commands are retained in the Scala packet. The separate helper classes precede
the unchanged main classes and resolved test dependencies; the helper receives
`benchmarks/legacy/replay/scala-l3-mixed.txt` as its sole argument. All 375 main
class bytes match before/after packaging and inside both JARs, including the
classes used by the accepted replay. Generated `dependency-reduced-pom.xml` is
packaging metadata, not a source edit.

Check a captured output without rerunning an external baseline:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 tools/check_legacy_replay.py \
  --baseline scala-l3 --trace benchmarks/legacy/replay/scala-l3-mixed.txt \
  --stdout tests/legacy_baselines/scala-l3.stdout.jsonl \
  --output build/new-scala-capture-check.json
PYTHONDONTWRITEBYTECODE=1 python3 tests/integration/legacy_replay_checker.py .
```

The other checker modes are `cpp-line5cd`, `cpp-line5gc-full` and
`cpp-line5gc-replacements`; use the corresponding trace/captured output. Choose
a new output pathname. The old `run_legacy_baseline.py --try-build` is a dated
build diagnostic, not this replay verifier; it must never target the maintained
worktree or an accepted frozen source, and its output must be a new evidence file.

## Retained failures and comparison limits

The previous host-Java build failure (`/packages cannot be represented as URI`)
remains evidence. Java 8 removes that build failure without changing the POM.
The published `OutputResultTest` then fails with `NumberFormatException` for
`(D`: its `reorder` expects four values followed by four names, while current
`JoinedAttributes.toString` emits named pairs. That test and failure remain
unchanged. The separate adapter/checker handles the actual format and supplies
independent output evidence; no published test-suite pass is claimed. Upstream
Scala minor-version and shading duplicate-class warnings remain in the logs.

`line5cd.process` discards the operation field and always inserts. Its CLI
`--mode` is not forwarded to that specialization. Deletions and a delta protocol
are excluded for `line5cd`; they are qualified separately for `line5gc` above.
Other dispatch queries/modes are unqualified, not silently assumed supported.
The baselines use floating-point annotations/epsilon rules; these tiny integer
results do not establish exact large-count or general scalar semantics. The new
engine's arithmetic and admission contract stays separate.

The C++ memory diagnostic reads `/proc/self/status` **VmPeak**, not RSS, and its
helper fails to close that file at milestones. Exclude it as target-RSS evidence
and exclude unreviewed long-milestone timing/memory comparisons. The Scala close
footer and C++ timing lines are captured diagnostics, not benchmark samples.
Correctness qualification here is limited to the named queries and inputs.
Future B04/B06 comparisons must additionally bind equal semantics/output modes,
new-trace correctness, setup costs, compiler/dependency/environment identity and
controlled measurement scopes. Approximation and parallel/distributed engine
execution remain deferred. Licensing checks remain deferred under the user's
instruction; rights and notices are preserved.
