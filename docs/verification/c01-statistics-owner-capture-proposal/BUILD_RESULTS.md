# Author build evidence — 2026-11-07

**Compile/link only. No test executable, Python checker, CMake or CTest was run. C01 remains `not_started`.**

The final owner-capture overlay compiles and links with Ubuntu GCC 13.3.0 (`13.3.0-6ubuntu2~24.04.1`), C++23, `-O2 -g -pthread`, and all six required warning switches: `-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror`. All compiler/linker commands exited zero, and their saved diagnostic logs are empty.

| Build item | Result |
| --- | --- |
| Seven overlay implementation translation units: reference, statistics, owner statistics, support, physical, delta, session | Compiled |
| Five native runtime/IO consumers: IO support/inspection, replay, window, observation | Recompiled with overlay public headers |
| Four standalone test translation units | Compiled |
| Four test executables | Linked against pinned Release archives |
| Ordinary/exception executable execution | **Not run; root required** |
| ASan/UBSan/leak execution | **Not run; root required** |

The complete initial build compiled all twelve implementation/consumer units and four tests. Final checked-multiplication and incomplete-visit changes recompiled `statistics.cpp`, `owner_statistics.cpp` and `support.cpp`, then relinked all four executables. The added nonvirtual internal `WeightedBuilder::stop()` declaration changed no class layout. Final independent fixture changes recompiled both owner test units and relinked their executables. No object with an incompatible public layout was reused; all owner/report fields were already present before the full initial compile. Cached native dependency libraries were neither rebuilt nor modified.

Exact expanded commands are retained in [author-compile-commands.sh](build-evidence/author-compile-commands.sh). The complete direct rebuild recipe is [compile.sh](compile.sh). Build output is `/tmp/crown-c01-owner-max-strict/`; [BUILD_ARTIFACT_SHA256SUMS](build-evidence/BUILD_ARTIFACT_SHA256SUMS) records 50 final object, diagnostic-log, command and binary artifacts there. [DEPENDENCY_SHA256SUMS](build-evidence/DEPENDENCY_SHA256SUMS) pins all five linked archives. The native `reference.cpp` archive member is overridden by the proposal object passed earlier on the link command.

| Final binary | SHA-256 |
| --- | --- |
| `owner_statistics_test` | `c040f6efb275685feb0ecd03e66a0ca74902ef2205cfcaba63f525e2a5b17fe3` |
| `owner_statistics_exception_test` | `ae0726821fddcacf9254ee7f5faafba5806b7834422c5e8cd41cd0fb1e81f2f8` |
| `statistics_capture_test` | `1ef40944f907ff6ef8d965ac82f6d28fb24747bd28cd5423209e214192d5655e` |
| `statistics_capture_exception_test` | `b2736331ef684bd8cb19eda074cd4a95b6222ddc329a477c5aaea5ca5e4dd9b2` |

These binaries propose 18 owner ordinary groups, 14 storage ordinary groups, two owner capture allocation sweeps, one report-copy allocation sweep and two storage allocation sweeps. Compilation does not establish those assertions or predict the number of injected failure positions. Root reproduction and remaining coverage are specified in [README.md](README.md).

`INPUT_SHA256SUMS` records 100 source/header/design/archive inputs, including a conservative native-header superset. The accepted storage cursor header/source copies match their prior package byte for byte. The two previously accepted proposal packages were not changed. No native integration or CMake source/target edit is included.
