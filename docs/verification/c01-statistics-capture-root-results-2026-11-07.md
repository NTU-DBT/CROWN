# C01 bounded state capture — root preparation results, 2026-11-07

**Excluded preparation only. C01 remains not_started; native O07 inputs remain frozen.**
The [storage capture proposal](c01-statistics-proposal/README.md) passes root execution.
Its PACKAGE_SHA256SUMS identity is
`bcb41e25ab0e6287210fc694f5f84398c9fd86b7c258d0344747de5f4bf475fc`.

Root independently rebuilt all ten translation units per configuration using
C++23 and the complete project warning policy: `-Wall -Wextra -Wpedantic
-Wconversion -Wsign-conversion -Werror`. Both ordinary and exception executables
pass in optimized strict mode and ASan+UBSan with leak checking enabled.

| Configuration | Ordinary groups | Allocation sweeps | Injected failures |
| --- | ---: | ---: | ---: |
| GCC strict, O2 | 14 | 2 | 34 |
| GCC ASan+UBSan+leaks, O1 | 14 | 2 | 34 |

The failure positions are the same two explicit-capture sweeps exercised in each
configuration, not 68 distinct integrated-engine fault positions. Each failure
preserves the same table owner, revision, rows, previous owning report and fresh
recovery capture. Ordinary cases cover exact literal/reference counts,
NDV/degree/top-K, nullary projections, incomplete results, shared budgets,
byte strings/Decimal equality, cursor invalidation and owning report lifetime.

All 646 pinned proposal/native/execution inputs match before and after. The
[raw root summary](../../build/verification/c01-statistics-capture-root-attempt-1.json)
records exact compile/link/test commands, log hashes, binary hashes and pins.
Raw logs use the same `c01-statistics-capture-root-attempt-1-*` prefix.
Root driver: `/tmp/crown-c01-capture-root.py`; isolated build:
`/tmp/crown-c01-capture-root-attempt-1/`. No native CMake/test/source file changed.

The primitive remains storage-scoped. Its revision is an invalidation stamp,
not a committed runtime epoch. Accounted bytes are explicitly modeled component
payload, with actual observed capacity maxima and stated exclusions; they are
not total allocator bytes. Owner/P/E/derivation wiring, transactional collection,
reset/freshness/report integration, measured overhead and the native matrix are
still required before C01 acceptance. O07 sealing must precede native C01 edits.
