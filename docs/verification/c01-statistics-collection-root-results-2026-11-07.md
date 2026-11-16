# C01 transactional numeric collection — root preparation results, 2026-11-07

**Excluded component preparation only; C01 remains not_started.** Root accepts
the [warning-only revision](c01-statistics-collection-warning-proposal/README.md),
package manifest SHA-256
`0ad7771da11e2bb545ece48ef1f2ff5b93b62856b58279ed926b3ed50cecd5fd`.
The original [frozen package](c01-statistics-collection-proposal/README.md) remains
unchanged, manifest `613b1ee2759a068d34c4077e29681225bc280e64013c0fd71beac78d7fa732ff`.

Root attempt 1 failed the full warning policy before execution: the signed
`std::bit_width` result indexed a size_t array. The revision's sole code change
is an explicit size_t conversion of its proved 0..64 result. Header and all
assertions are byte-identical. No numerical behavior or acceptance expectation
was changed; the original failed summary/build log remain preserved.

Attempt 2 independently rebuilds both translation units with C++23,
`-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror`, then passes
the assertion-enabled suite at O2 and O1 ASan+UBSan with leak checking. Its seven
function groups cover nested/root publication and aborts, stale sibling tickets,
physical no-ops, deterministic attempt sampling, complete detail truncation,
zero crossings versus positive-to-positive changes, touched event multiplicity,
all 65 bin boundaries, saturation, reset/rotation, actual vector-capacity
accounting, four configuration allocation-failure positions and a globally
rejecting allocator on hot lifecycle paths. Empty min/max remain unknown;
binned histograms are not exact quantiles or positive-key state populations.

All 655 proposal/native/execution pins match before and after.
[Root summary](../../build/verification/c01-statistics-collection-root-attempt-2.json)
contains exact commands, binary/log hashes and pins. Raw logs use the same
`c01-statistics-collection-root-attempt-2-*` prefix. Root driver:
`/tmp/crown-c01-collection-root-revision.py`; isolated build:
`/tmp/crown-c01-collection-root-attempt-2/`.

These tests establish a standalone numeric component. Native owner hooks,
initialization suppression, rollback wiring, mode/session forwarding, owning
historical reports, committed-epoch freshness, clocks, measured overhead and
native integration remain unverified. Memory is capacity-derived component
payload with stated exclusions, not S05 total allocator bytes. No native O07
execution input was modified; its original sanitizer matrix remains active.
