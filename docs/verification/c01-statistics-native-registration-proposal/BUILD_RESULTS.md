# Publication-only compilation

Both direct strict builds completed with exit 0 on 2026-11-07. The writer and
the new guide example were compiled independently for production and
`CROWN_RUNTIME_TESTING`; the producer and report allocation-failure consumer
were then relinked against their matching frozen report objects. All eight
compiler/link logs are empty. No test, checker or CMake operation was run.

The flags are `-std=c++23 -O2 -g -UNDEBUG -Wall -Wextra -Wpedantic -Wconversion
-Wsign-conversion -Werror -pthread`, with `-DCROWN_RUNTIME_TESTING` only for the
testing build. Each link reuses 22 unchanged implementation objects and its
unchanged matching consumer object from the accepted report strict build,
replacing only `src_io_statistics_explain.cpp.o`. The five Release foundation
archives are separately pinned. No public/runtime layout changed here, and no
cached native library was rebuilt. This is not a fresh complete native closure.

The actual command files, input pins, empty logs and output manifests are in
`build-evidence/`. [build-publication-only.sh](build-publication-only.sh) reproduces
this narrow check using the original temporary report object directories.
Those temporary dependencies are author evidence only; registered native CMake
tests build from the checked-in sources and baselines.

| Variant | Executable | SHA-256 |
| --- | --- | --- |
| Production | `statistics_explain_test` | `5a235f82b5293190c4634995bf8fea952d9d00d11ec99e1d720166f31686f48f` |
| Testing | `statistics_explain_test` | `b24f983db535c5cc6d2897e2a2254c82806102fc450526755a04d8a715277e02` |
| Production | `statistics_explain_exception_test` | `c58859349c00fa68a0a259de2af7b302502d19c130797ba4ba4819be99e77928` |
| Testing | `statistics_explain_exception_test` | `f1feabaefdd6377b06337d9525f9b02d7dfd056c2151f3d4c6fd403a36b46cb2` |

Outputs are under `/tmp/crown-c01-native-registration-production` and
`/tmp/crown-c01-native-registration-testing`. The identical guide example
objects have SHA-256
`a6c8ad1e316a81e348b388b43857b8a45c9221352a316c0c9a36aaf91abd5156`.
The [example source](examples/statistics_report.cpp) is the new report example
in the public guide. Earlier owner/workload examples retain their accepted
guide compile-revision source; no new execution is inferred from compilation.

Remaining checks are explicit: root must execute these publication artifacts,
validate the copied schema/wrapper and gate rejection, configure the draft
CMake, compare actual CTest registration with all 131 expected names, build
separate native variants and runtime-only links, inspect testing-only symbols,
run the full native compiler/sanitizer/legacy/clean matrix, and accept its new
source seal. The parent report's full sanitizer continuation is now separately
accepted in root attempt 2; it does not execute this publication-only change.
No existing golden expectation was changed to obtain a pass.
