# Scalar/constraint proposal build evidence

2026-11-07. **Compile/link only; root execution pending.** No project binary, benchmark, Python checker, CMake, CTest, `nm`, network or git operation was executed by the author.

Both final builds use the same [test source](scalar_statistics_test.cpp), SHA-256 `3df1df308c36acd0d0d3f44e374c7bf207610e19b0abad190f9408ceb9d8b905`, with no `CROWN_RUNTIME_TESTING` definition. Flags include `-std=c++23 -O2 -g -UNDEBUG -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread`. Sanitizer compilation and linkage additionally use `-O1 -fsanitize=address,undefined -fno-omit-frame-pointer`. No warning is suppressed. Final compile and link logs are empty.

| Final consumer | Result | Binary SHA-256 |
| --- | --- | --- |
| `/tmp/crown-c01-scalar-production-strict-final/scalar_statistics_test` | Compile/link exit 0; not executed | `92338c4ec53baf9e81456cab1472801416c8fa3c33827f28084f46701d2d7a67` |
| `/tmp/crown-c01-scalar-production-sanitized-final/scalar_statistics_test` | Compile/link exit 0; not executed | `942386d18ee73e1927d040007e8938a144255fa67ed50d5f59340e634b11b456` |

The strict consumer links 15 accepted production implementation/consumer objects from `/tmp/crown-c01-combined-production` and the five accepted Release archives. The sanitized consumer links the corresponding 15 objects from `/tmp/crown-c01-combined-root-production-sanitized-attempt-1` and the five accepted sanitizer archives. This task compiled the new test translation unit in each configuration; it did not rebuild those already accepted implementations. Their exact bytes, dependency files and originating compiler-command files are pinned. No production/testing object mixture is introduced.

Actual expanded commands are retained in [strict-commands.sh](build-evidence/strict-commands.sh) and [sanitized-commands.sh](build-evidence/sanitized-commands.sh). Each final output directory's seven files—test object, executable, dependency file, compile/link logs, command file and link-input manifest—are pinned by the corresponding artifact manifest. [build-only.sh](build-only.sh) reproduces compilation/linkage without executing the consumer.

The initial strict attempt rejected errors confined to this new test source: an unqualified `size` helper conflicted with `std::size`, a tree scope used a vector instead of `VariableSet`, one optional root needed explicit `NodeId`, an unused helper remained, and one loop/return layout triggered a strict indentation warning. Those were corrected without relaxing flags. Its [diagnostic log](build-evidence/strict-initial-compile.log) and command file are preserved. A subsequent strict attempt compiled and linked; final builds followed the addition of independent source-regrouping checks. [prior-build-artifacts.sha256](build-evidence/prior-build-artifacts.sha256) preserves both earlier output directories as historical build evidence; their binaries are not execution candidates for this final source.

Compiler version evidence is retained from the accepted closure in [compiler-version.txt](build-evidence/compiler-version.txt): GCC 13.3.0. The actual `/usr/bin/c++` file was also hashed: `1353e9bdd29a7295c7226bf6c63abccce056d8cac31f112e5cdbecc3f28c2769`. System standard-library headers are not exhaustively hashed.

[INPUT_SHA256SUMS](INPUT_SHA256SUMS) has 119 entries and SHA-256 `ca39e80a2b0a5b9d72d62b92910961f69e502f2a48fdf15a9cd134881ae9bbe1`. It pins the predecessor package/root results, existing scalar/constraint/layout fixture inputs, every non-system header named by the consumer dependencies, the actual strict/sanitized link objects/archives, their dependency files/commands, compiler identity and O07 authority files. [source-files.sha256](source-files.sha256) pins the two authored implementation files, test and build script, with manifest SHA-256 `a8b4220eff3a81545a41ee8334f05f27dd898180f47f1ef19fa163fa0797e1cb`.

The frozen combined manifest remains `cb0ecb64935f80bf4915aa069de1bf01bcf1ea2f22a591f6f7408d405fcf4cfe`. Current O07's 691-entry source seal remains `f4acf6ea043859d350aa0dd2d56c86afca24535d7288eb5774f94b26ab0ea21e`. `PACKAGE_SHA256SUMS` seals all files in this new package except itself. Native integration, root's policy/replay/window work and the new report/benchmark packages remain separate.
