# Root-only sanitizer reproduction

This frozen recipe binds the terminal matched sanitizer closure and corrected
strict source lineage. It is not a completed independent sanitizer result.
The build script requires the input/link/package manifests and exact recorded
closure path. All five consumers compile anew; no ordinary independent object
or binary enters these links.

From the repository root, the proposed exact build argv is:

```sh
env LC_ALL=C bash docs/verification/c05-selection-independent-sanitize-proposal/ROOT_BUILD.sh \
  /tmp/crown-c05-selection-independent-sanitize-1
```

The compiler recipe matches the producer sanitizer variant: C++23, `-g
-UNDEBUG`, all six strict warning flags, ASan plus UBSan, frame pointers and full
`-MD` dependencies. The pure byte consumer links no runtime/report archive. The
other four consumers use production selection/ranking/runtime bridges; no
testing-runtime macro or archive is admitted. All native C++ archives come from
the matching sanitizer build, with the active patched JSON header.

Before execution, root must retain the actual five dependency records and pin
their complete project/system inputs, compiler commands, objects, binaries,
matching archives and root-held source/closure receipts. No unseen dependency
record is implied by the include arguments alone. Compiler or link failure is a
terminal failed attempt and retains all logs; it does not authorize changing a
test expectation.

After successful build and provenance checks, the five proposed execution argv
use the same leak/error environment as native sanitizer CTest:

```sh
env LC_ALL=C ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
  /tmp/crown-c05-selection-independent-sanitize-1/bin/selection_public_independent /home/userroot/Codex/CROWN
env LC_ALL=C ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
  /tmp/crown-c05-selection-independent-sanitize-1/bin/selection_cache_independent /home/userroot/Codex/CROWN
env LC_ALL=C ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
  /tmp/crown-c05-selection-independent-sanitize-1/bin/selection_resources_independent /home/userroot/Codex/CROWN
env LC_ALL=C ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
  /tmp/crown-c05-selection-independent-sanitize-1/bin/selection_binding_independent
env LC_ALL=C ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
  /tmp/crown-c05-selection-independent-sanitize-1/bin/selection_publication_fault_independent /home/userroot/Codex/CROWN
```

Root records every exit status and full output, repeats the final current
source/artifact guards and retains failures as separate attempts. Ordinary
success counts do not establish sanitizer success. The focused OOM driver
derives its measured positions from that variant's own successful operation;
positions and recovered-publication counts must be reported as observed, never
copied from the ordinary run or silently waived.

Neither compilation nor these five consumers establish native registration,
the full native configuration matrix, measured overhead, deployment readiness,
S05 allocator accounting, C03 optimization or structural proof authority.
