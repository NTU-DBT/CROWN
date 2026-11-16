# Root-only reproduction

**These commands are for the root agent. The author compiled and linked the probes but did not execute any binary.** Run from the repository root with compiler `c++` and preserve each output, error stream, exit status, sanitizer report, and environment in root-owned evidence. Do not convert the expected original-control termination into an assumed result.

The build below uses only `probe.cpp`, the selected single-header include root, the C++ standard library, and the compiler runtime. It does not link a CROWN archive. The original header is staged under `/tmp` so the native `third_party` tree remains untouched. Outputs use the author build root `/tmp/crown-c02-json-cleanup-tests-20261107-a`.

## Verify inputs and rebuild

```sh
sha256sum --check --strict docs/verification/c02-json-cleanup-tests-proposal/input-pins.sha256
mkdir -p /tmp/crown-c02-json-cleanup-tests-20261107-a/original/nlohmann
mkdir -p /tmp/crown-c02-json-cleanup-tests-20261107-a/objects
mkdir -p /tmp/crown-c02-json-cleanup-tests-20261107-a/bin
mkdir -p /tmp/crown-c02-json-cleanup-tests-20261107-a/logs
mkdir -p /tmp/crown-c02-json-cleanup-tests-20261107-a/results
cp docs/verification/c02-baseline-ranking-proposal/upstream/nlohmann-json-3.12.0.hpp /tmp/crown-c02-json-cleanup-tests-20261107-a/original/nlohmann/json.hpp
sha256sum /tmp/crown-c02-json-cleanup-tests-20261107-a/original/nlohmann/json.hpp
```

Strict compile flags for every object and link command are `-std=c++23 -O1 -g -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG`. `-O1` is chosen to keep sanitizer and ordinary probes coherent; this is not a performance build. The include-root order selects the desired header. The sanitizer object and link add the same ASan/UBSan options.

```sh
c++ -std=c++23 -O1 -g -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG -isystem /tmp/crown-c02-json-cleanup-tests-20261107-a/original -isystem third_party -c docs/verification/c02-json-cleanup-tests-proposal/probe.cpp -o /tmp/crown-c02-json-cleanup-tests-20261107-a/objects/original.o > /tmp/crown-c02-json-cleanup-tests-20261107-a/logs/original-compile.log 2>&1
c++ -std=c++23 -O1 -g -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG -isystem docs/verification/c02-baseline-ranking-proposal/overlay/third_party -isystem third_party -c docs/verification/c02-json-cleanup-tests-proposal/probe.cpp -o /tmp/crown-c02-json-cleanup-tests-20261107-a/objects/patched.o > /tmp/crown-c02-json-cleanup-tests-20261107-a/logs/patched-compile.log 2>&1
c++ -std=c++23 -O1 -g -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG -fsanitize=address,undefined -fno-omit-frame-pointer -isystem docs/verification/c02-baseline-ranking-proposal/overlay/third_party -isystem third_party -c docs/verification/c02-json-cleanup-tests-proposal/probe.cpp -o /tmp/crown-c02-json-cleanup-tests-20261107-a/objects/patched-san.o > /tmp/crown-c02-json-cleanup-tests-20261107-a/logs/patched-san-compile.log 2>&1
c++ -std=c++23 -O1 -g -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG /tmp/crown-c02-json-cleanup-tests-20261107-a/objects/original.o -o /tmp/crown-c02-json-cleanup-tests-20261107-a/bin/original > /tmp/crown-c02-json-cleanup-tests-20261107-a/logs/original-link.log 2>&1
c++ -std=c++23 -O1 -g -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG /tmp/crown-c02-json-cleanup-tests-20261107-a/objects/patched.o -o /tmp/crown-c02-json-cleanup-tests-20261107-a/bin/patched > /tmp/crown-c02-json-cleanup-tests-20261107-a/logs/patched-link.log 2>&1
c++ -std=c++23 -O1 -g -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG -fsanitize=address,undefined -fno-omit-frame-pointer /tmp/crown-c02-json-cleanup-tests-20261107-a/objects/patched-san.o -o /tmp/crown-c02-json-cleanup-tests-20261107-a/bin/patched-san > /tmp/crown-c02-json-cleanup-tests-20261107-a/logs/patched-san-link.log 2>&1
```

The three expected compiler invocations above succeeded for the final source. Exact object, executable, and empty-log hashes are in `compile-evidence.md`. A prior exploratory source used `std::deque` as the JSON array type and failed to compile because this implementation's `basic_json::push_back` accesses `array_t::capacity()`. That unsupported candidate was replaced with a custom `std::vector`-derived array plus a counting allocator; the old diagnostics are retained in the author's `/tmp` tree and are not part of the final package input set.

## Root-only runs

First compare normal output from the original and patched header. This checks the emitted `sizeof` values and serialized bytes for all listed serializable cases. It does not execute cleanup fault injection.

```sh
/tmp/crown-c02-json-cleanup-tests-20261107-a/bin/original --serialize > /tmp/crown-c02-json-cleanup-tests-20261107-a/results/original-serialize.txt 2> /tmp/crown-c02-json-cleanup-tests-20261107-a/results/original-serialize.stderr
/tmp/crown-c02-json-cleanup-tests-20261107-a/bin/patched --serialize > /tmp/crown-c02-json-cleanup-tests-20261107-a/results/patched-serialize.txt 2> /tmp/crown-c02-json-cleanup-tests-20261107-a/results/patched-serialize.stderr
cmp /tmp/crown-c02-json-cleanup-tests-20261107-a/results/original-serialize.txt /tmp/crown-c02-json-cleanup-tests-20261107-a/results/patched-serialize.txt
```

Then capture each cleanup run independently. The original is a historical control: because its destructor is `noexcept` while its cleanup stack can allocate, the injected `std::bad_alloc` may terminate the process. Root should retain the actual status and diagnostics rather than assuming a particular first failure point or signal. The patched ordinary run should complete all cases for the source-level assertions to pass. The sanitizer run adds leak and undefined-behavior checks; root must record actual results.

```sh
set +e
(ulimit -c 0; /tmp/crown-c02-json-cleanup-tests-20261107-a/bin/original --cleanup > /tmp/crown-c02-json-cleanup-tests-20261107-a/results/original-cleanup.stdout 2> /tmp/crown-c02-json-cleanup-tests-20261107-a/results/original-cleanup.stderr)
status=$?
printf 'exit=%s\n' "$status" > /tmp/crown-c02-json-cleanup-tests-20261107-a/results/original-cleanup.status
```

```sh
/tmp/crown-c02-json-cleanup-tests-20261107-a/bin/patched --cleanup > /tmp/crown-c02-json-cleanup-tests-20261107-a/results/patched-cleanup.stdout 2> /tmp/crown-c02-json-cleanup-tests-20261107-a/results/patched-cleanup.stderr
printf 'exit=%s\n' "$?" > /tmp/crown-c02-json-cleanup-tests-20261107-a/results/patched-cleanup.status
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 /tmp/crown-c02-json-cleanup-tests-20261107-a/bin/patched-san --cleanup > /tmp/crown-c02-json-cleanup-tests-20261107-a/results/patched-san-cleanup.stdout 2> /tmp/crown-c02-json-cleanup-tests-20261107-a/results/patched-san-cleanup.stderr
printf 'exit=%s\n' "$?" > /tmp/crown-c02-json-cleanup-tests-20261107-a/results/patched-san-cleanup.status
```

These are sequential root commands: preserve the status immediately after each run. The SAN process owns its own heap census; do not interpret the custom global `new` counters as a substitute for leak sanitizer. The deep chain covers a 4096-level iterative construction and teardown path, but does not test arbitrary depth or concurrent allocator activity. The probe does not establish project-wide allocator safety, durable reporting behavior, wire compatibility by itself, or any CROWN runtime/report integration.
