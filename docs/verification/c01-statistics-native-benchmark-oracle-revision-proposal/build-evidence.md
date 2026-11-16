# Oracle revision compile/link evidence

## Preserved root attempt and diagnosis

The first root attempt used the frozen original package with manifest SHA-256
`a281668f3abf1a978d43fafb914fe8a6851b8876181581d755adb8cf21f53887`. Root's
preserved attempt record has SHA-256
`b9de8c5725c90be3bb9db252bb545f57ef169f3e60909a2ebd37479c61632eed`; stderr
is `829f4706dd628ad326fd10c109e92a58835eec35298e8ab3005ba8a74f3e721c`; raw
JSON is empty (`e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855`).
The process exited 1 at the first untimed S/P/E population guard. It emitted no
timed benchmark records.

The error was in the independent oracle: it derived the S child P map from the
global query answer. The native contract derives P for each node by projecting
that node's survivors. The admitted child scope and separator are both `{y}`,
so child P must group the literal current S survivor set by y. The root P and
root E expectations still come from the global answer. The exact one-file
source correction is in `oracle-correction.diff`; all event generation,
numeric parameters, output checksums, native implementation, and collector
code are unchanged.

This conclusion is grounded in the current, pinned `src/runtime/support.cpp`,
`src/planner/lower.cpp`, and the independent expectations in
`tests/unit/physical_runtime_test.cpp` and `tests/unit/support_model_test.cpp`.
Their SHA-256 values and the original/combined proposal identities are in
`input-pins.sha256`. The root's preserved attempt 1 and original frozen package
remain unchanged.

## Revised compile/link

The changed consumer compiled and linked successfully with exit code 0. The
author command was:

    CXX=c++ bash docs/verification/c01-statistics-native-benchmark-oracle-revision-proposal/build-only.sh \
      /tmp/crown-c01-native-benchmark-oracle-revision-final \
      /tmp/crown-c01-native-benchmark-author

Compiler: `c++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0`.

The revised consumer was compiled with:

    -std=c++23 -O3 -DNDEBUG -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread

Its include paths were the pinned combined API overlay include and private
runtime directories, the native public/private include directories, and
`-isystem third_party`. It was compiled as a single source with `-MMD -MF` and
`-c`; there is no `CROWN_RUNTIME_TESTING` define. The binary was relinked with
the same C++23/O3/DNDEBUG/full-warning/-Werror/pthread flags and the 15 pinned
O3 production runtime/collector/storage objects listed in `input-pins.sha256`.
The script verifies all 15 object hashes and the four cached Release archive
hashes before compile/link. No runtime source/object was rebuilt for this
correction.

| Revised output | SHA-256 |
| --- | --- |
| `native_benchmark.cpp` | `7f2ce2e8b9a86088b0e181263351dc246aac9ad4ca544c8acb5fbbb127b842a6` |
| `oracle-correction.diff` | `7b97648c8a58ee6c3d686add6909053783dad6697c4d361a1431244c58e52a60` |
| `build-only.sh` | `30a335159a8e084316b6eb541abb0d260ee3dd213ca82b8f34d7f9f0fedb1c01` |
| compiled `native_benchmark.o` | `f0268c2a7d30737c687211aaf6905dcc828b54a101b23814e652dff8c7ea7a07` |
| generated `native_benchmark.d` | `23c0855234d0c7bc9c6908ec838f68061780a8c34d8fe05bc5d30647d6a6f97c` |
| consumer compile log (empty) | `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855` |
| link log (empty) | `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855` |
| linked binary, not executed | `ada8dae17e73c568fdec0886466d19a0352377fefb778b8ff6ef445a9b1549d8` |

The benchmark binary was not executed by the author. No test, checker, CMake,
CTest, `nm`, diagnostic binary, or benchmark run was invoked. Root owns the
next corrected benchmark execution and its result record. This compile/link
does not establish runtime guard success or supply native overhead numbers.
C01 remains `not_started` and excluded preparation.
