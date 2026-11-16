# C01 actual-owner state capture — root preparation results, 2026-11-07

**Excluded explicit-state slice only. C01 remains not_started.** Root accepts
the [generalized-fixture revision](c01-statistics-owner-generalized-revision-proposal/README.md),
manifest SHA-256 `dc7276b9c6427784f67372a95efa0365de3859203a0c1706fe2fe494ef02869e`.
The [first owner package](c01-statistics-owner-capture-proposal/README.md) and
failed root attempt 1 remain preserved. Production source/header bytes are
identical across those two packages; the repair changes only the generalized
fixture/helper/diagnostic and its recorded expectations.

| Configuration | Owner ordinary groups | Storage ordinary groups | Owner/copy sweeps and injected positions | Storage sweeps and injected positions |
| --- | ---: | ---: | --- | --- |
| Strict C++23, O2 | 18 | 14 | 3 sweeps / 100 positions | 2 sweeps / 34 positions |
| ASan+UBSan+leaks, O1 | 18 | 14 | 3 sweeps / 100 positions | 2 sweeps / 34 positions |

Root verified strict author commands/object/binary/archive pins before running
the four suites. Root independently compiled the complete sanitized closure:
12 implementation and five test/diagnostic translation units, linked matching
instrumented dependencies, and executed all four principal suites. The extra
diagnostic was built under sanitizers; its strict execution is separately
recorded. All builds use the six project warning flags with Werror. This owner
slice uses the production runtime variant; it is separate from online tests
that use CROWN_RUNTIME_TESTING. The same 134 allocation-failure positions are
exercised in each configuration, not 268 distinct locations.

Actual captures match independent literal full-row/source projections, native
derivations, records, S, P/E positive counts and existing-index degree maps.
Tests cover direct/replay/rebuild, source/no-op freshness, actual owner/plan/
committed epoch, rollback revision advancing without a committed epoch,
private/unread/session/drop states, immutable owning reports, shared exhaustion,
ordered/repeated/empty projections and strong report-copy failure recovery.
No optional trace or production collector is used as the independent row/map
oracle. Accounted bytes remain a declared component payload model, not S05.

Attempt 1 failed the assumption that hidden x puts R(x,y) outside C* under
G(y)->R(x,y),S(y), head y. Actual maximal C* crosses each output-only separator
{y}, so all three nodes have E factors. Root independently checked verifier/
lowerer code and ran the diagnostic: generalized candidate keys remain {7,8},
S remains {7}, and actual captured distributions agree with canonical native
state. The revision retains these counts, checks all three present E maps,
and adds T(x) under R with hidden separator {x}; T then has real nonempty
records/S/P and not_applicable E. No collector behavior or unrelated assertion
was weakened to make the test pass.

[Root summary](../../build/verification/c01-statistics-owner-root-attempt-2.json)
and [geometry diagnostic](../../build/verification/c01-statistics-owner-generalized-diagnostic-attempt-1.json)
retain exact commands, hashes and 729 distinct unchanged input/artifact files.
Raw logs share the root-attempt prefix. Root sanitized build is
`/tmp/crown-c01-owner-max-root-sanitized-attempt-2/`.

Merge with online hooks, joint state/workload composition, production/testing
closure checks, native integration, EXPLAIN/versioned schema exports, measured
engine overhead and full C01/native acceptance remain unfinished. No native
O07 source/header/test/tool/schema/CMake input changed; the original O07
sanitizer matrix remains independent.
