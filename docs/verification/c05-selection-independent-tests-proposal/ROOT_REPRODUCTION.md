# Root-only independent build and execution

The author has not run a compiler, linker, source checker, Python, CMake, CTest,
symbol command or produced binary. `ROOT_BUILD.sh` is an authored recipe, not a
build result. Before invocation root must verify this packet's advertised FILE
hash, its entries, the implementation API checkpoint, and the successful matching
implementation archive receipt. A failed producer test compile does not invalidate
unchanged successful implementation archives; their exact source/variant/object
lineage still must be retained. No testing-runtime archive is used here.

The ordinary command uses the five unchanged strict-3 pure implementation objects
and its production bridge archive, plus the current matching native Release C02,
runtime, plan, SQL, parser C and core archives. Root's strict-3 implementation
archive provenance must be bound before running:

```sh
bash docs/verification/c05-selection-independent-tests-proposal/ROOT_BUILD.sh \
  /tmp/crown-c05-selection-implementation-strict-3 \
  /tmp/crown-c05-selection-independent-strict-1 strict
```

The five compile argv all use C++23, `-O3 -UNDEBUG`, the six strict warning flags,
the current overlay public headers first, the independent test include directory,
private planner declarations and the sole active native `third_party` root.
Every consumer has `-MD` dependencies, no CROWN_RUNTIME_TESTING or planner-test
macro. Four consumers use the production runtime bridge; the diagnostic byte
consumer links only pure selection/ranking and plan/SQL/core/parser dependencies.
No report archive or excluded old JSON header is linked. The fault executable
is separate, so its replacement allocation functions cannot affect ordinary
consumers. Build logs, actual commands, statuses, dependencies, artifacts and
before/after link/source identities are retained under the new output.

Root must retain and hash every actual `.d` dependency, including system headers,
before accepting execution. This packet's source inputs do not claim unseen
compiler dependency rows. Exact held implementation archive hashes are recorded
by the recipe before/after link and bound to root's implementation build receipt;
archive names alone are not proof of matching ABI or flags.

Each executable writes only stdout/stderr and takes the following exact argv:

```sh
/tmp/crown-c05-selection-independent-strict-1/bin/selection_public_independent /home/userroot/Codex/CROWN
/tmp/crown-c05-selection-independent-strict-1/bin/selection_cache_independent /home/userroot/Codex/CROWN
/tmp/crown-c05-selection-independent-strict-1/bin/selection_resources_independent /home/userroot/Codex/CROWN
/tmp/crown-c05-selection-independent-strict-1/bin/selection_binding_independent
/tmp/crown-c05-selection-independent-strict-1/bin/selection_publication_fault_independent /home/userroot/Codex/CROWN
```

Use `LC_ALL=C`. No event timing expectation depends on a performance threshold.
The active-time tests grant 60 seconds except deliberate invalid/exhausted caps;
they assert accounting classification, not speed. Preserve each output and exit
status independently; a successful compile is not a passing test result.

For sanitizer closure, root first builds the matching implementation production
archives using the producer's held sanitizer recipe and native sanitizer archives.
Then invoke this recipe with that exact closure directory, a fresh independent
output such as `/tmp/crown-c05-selection-independent-sanitize-1`, and `sanitize`.
This selects `-g -UNDEBUG -fsanitize=address,undefined -fno-omit-frame-pointer`,
matching sanitizer link flags and only `build/sanitize` C++/parser archives.
Do not substitute ordinary or testing-runtime objects. Execution uses the same
five argument patterns and root's explicit ASan/UBSan environment, including
`ASAN_OPTIONS=detect_leaks=1:halt_on_error=1` and
`UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1`. No sanitizer success is claimed
until those exact binaries and dependency/guard records are accepted by root.

The original authoring checkpoint is immutable. A compile/API/test correction
must preserve it and be recorded with its reason, exact diff and new pins.
Numeric expectations, proof authority and failure atomicity may not be weakened
to accommodate an unexplained failure. The full C05/native matrix, deployment,
C03 and allocator/S05 claims remain outside this excluded preparation.
