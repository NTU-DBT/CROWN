# Independent C02 sanitizer execution preparation

This is a separate excluded build packet for the same two frozen independent
consumers in [the strict proposal](../c02-ranking-independent-tests-proposal/).
The original 47-file package remains unchanged at manifest SHA-256
`858177262891c22718b12254a9b6da9b8ae31910235ad89f1e280ac2f2fc53b8`.
No test source, implementation, API, native source or task ledger is changed.
C02 remains preparation-only; the root task owns native acceptance.

Root accepted the current strict consumers in
`build/verification/c02-independent-strict-root-attempt-2.json`: 54 integer
operands, 2,916 ordered pairs, three arithmetic groups and 16 boundaries, plus
all eight public groups. The literal `13/24/32/32/195/105/190` expectations remain
unchanged. That execution checked 1,205 lexical pins. The old integer-only
checkpoint is still historical; none of its obsolete live-entry manifests is
revalidated by this packet.

The author compiled and linked the frozen tests with C++23, assertions enabled,
all six warning flags, ASan, UBSan and frame pointers against the complete
matching sanitized production closure. There are 67 producer archive units:
31 core, 10 SQL, 3 plan, 3 ranking, 15 production runtime and 5 reference units.
The integer driver links only the matching sanitized integer object. The public
driver links the six sanitized production archives and the sanitized parser C
archive. No cached native C++ archive, strict object, testing-runtime archive,
report archive or newly added producer test is linked.

The producer's 67 unique implementation source hashes are byte-identical between
strict and sanitizer configurations. All 67 actual production compile commands
carry the full warning set, the patched JSON include root and ASan/UBSan flags;
none contains the testing macro or a strict/Release dependency path. The actual
compiler tools, API/private ABI headers, JSON patch, source/header dependencies,
linked objects and archives are pinned before and after the final compile.
The recorded command vectors retain the producer's `-O2` followed by `-O1`,
so the effective sanitizer optimization is `-O1`.

The earlier [independent source review](../c02-ranking-independent-tests-proposal/SOURCE_REVIEW.md)
and [coverage limits](../c02-ranking-independent-tests-proposal/README.md) remain
applicable. Decimal coefficient and repeated-layout equality payload accounting
are included in the held implementation. The JSON fallback is nonrecursive and
allocation-free for the reviewed concrete types, but can revisit ancestors;
it is not a linear-time or hard-deadline guarantee. Logical payload accounting
does not claim allocator totals or transient peak memory. Raw private arithmetic
does not turn clipped runtime observations into exact facts.

Root separately accepted the producer's ten strict consumers and 8,112 injected
OOM positions in `build/verification/c02-producer-strict-root-attempt-2.json`.
The separate JSON cleanup/control packet passed 30 cases and 96 fault positions
in both ordinary and sanitizer probes, with the original failure control
observed, in `build/verification/c02-json-cleanup-root-attempt-2.json`. Those
scoped results do not replace execution of these two full sanitizer consumers.

This packet contains no author-side test, checker, CMake, CTest, symbol-tool or
benchmark execution. Root must run both binaries with leak detection, preserve
stdout/stderr/exit records, and recheck the file pins. Native C02 registration,
matrix and final source gates, and any remaining native C01 gates, stay with
the root task. No performance, allocator-total or global-cost-optimality claim
is made.

Use [ROOT_REPRODUCTION.md](ROOT_REPRODUCTION.md) for exact root commands and
[BUILD_RESULTS.json](BUILD_RESULTS.json) for compile-only outcomes. The package
is frozen only when its final manifest is reported to root.
