# Generalized revision build and diagnostic evidence

**C01 remains `not_started`. The author compiled and linked only. Full ordinary/allocation/sanitizer execution of this revision remains with root.**

The compiler is Ubuntu GCC 13.3.0 (`13.3.0-6ubuntu2~24.04.1`). The refreshed owner ordinary test, owner allocation test and new generalized diagnostic compiled with C++23, `-O2 -g -pthread`, and `-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror`. All commands exited zero; their diagnostic logs are empty. The two unchanged storage tests were relinked without recompilation.

All fifteen production source/internal-header/public-header files are byte-identical to frozen owner package `b2599d31f8f982bf764e1c65b0f8001357f299363c39b847647d7e53d73ce89d`. The twelve previously compiled runtime/storage/IO objects were therefore reused unchanged from `/tmp/crown-c01-owner-max-strict/`, together with the two unchanged storage test objects and pinned Release archives. No public layout, numerical implementation or native input changed. `build-evidence/REUSED_INPUT_SHA256SUMS` records their identities; the complete fresh-build recipe remains available in `compile.sh`.

| Revision binary under `/tmp/crown-c01-owner-max-generalized-strict/` | SHA-256 |
| --- | --- |
| `owner_statistics_generalized_diagnostic` | `c9268b22e318dc12b03bc64c99be7e581f35c72e82bd0df3175f457bad11b189` |
| `owner_statistics_test` | `7cb6aed9524414c482824cab8c36c61255768427a64e69336bff49de398b6482` |
| `owner_statistics_exception_test` | `abb5284ba0a1c271c1799ffb63358c7edc8815d48da6dad2331d3bd8ef10fcc0` |
| `statistics_capture_test` | `1ef40944f907ff6ef8d965ac82f6d28fb24747bd28cd5423209e214192d5655e` |
| `statistics_capture_exception_test` | `b2736331ef684bd8cb19eda074cd4a95b6222ddc329a477c5aaea5ca5e4dd9b2` |

Root subsequently executed only the diagnostic, recording `build/verification/c01-statistics-owner-generalized-diagnostic-attempt-1.{json,log}`. Root reported PASS, the diagnostic binary hash unchanged, and all 635 frozen inputs stable. Its output confirms:

- Original geometry: maximal C* = `{0,1,2}`, all three E factors present, G records `{7,8}`, G S `{7}`, E(G) `{7:1}`, E(R) `{7:2,8:1}`, E(S) `{7:1}`.
- Separate hidden-separator geometry: T/node 3 is outside C*, its E is `not_applicable`, and G's records/S counts remain 2/1.

That printed diagnostic validates the concrete geometry diagnosis and repair; it does not replace the complete ordinary or allocation test suites. The original failed root attempt 1 and frozen package are preserved. Test group 9 is the sole changed existing assertion block, with new hidden-separator helpers added to the common fixture. All exception and storage test sources are byte-identical to their originals. Coverage inventory remains 18 owner ordinary groups, 14 storage ordinary groups, and five allocation sweeps, now with stronger generalized/E coverage inside group 9.

`build-evidence/author-compile-commands.sh` records the exact compiler/linker commands. `BUILD_ARTIFACT_SHA256SUMS` pins the final new build artifacts; `test-group9.patch` isolates the ordinary-test repair. No binary was executed by the author, no sanitizer build was performed by the author, and no cached native library or frozen package was modified.
