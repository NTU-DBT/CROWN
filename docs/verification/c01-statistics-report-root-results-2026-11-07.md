# C01 versioned statistics reports — root results, 2026-11-07

**Accepted excluded preparation; C01 remains `not_started`.** The frozen
[report proposal](c01-statistics-report-proposal/README.md), package manifest
`730a7488e53a749b024b307dab27c09d58a324ae7603bccc8831364af289f947`,
passes both strict C++23 O2 variants and both complete ASan+UBSan/leak variants.
Its [independent Astra review](c01-statistics-report-independent-review-2026-11-07.md)
has no unresolved blocker and records the source/evidence inspection limits.

| Check per applicable configuration | Production | Testing |
| --- | ---: | ---: |
| Versioned v3 JSON/human report cases | 31 | 32 |
| Rejected schema/semantic mutations | 15 | 17 |
| Same-owner allocation sweeps | 4 | 4 |
| Injected allocation positions across those sweeps | 99 | 99 |
| Runtime-only consumer | passed | passed |
| Inherited joint groups | 9 passed | 9 passed |
| Inherited online groups | not applicable | 10 passed |

The four report sweeps reach 61 actual-owner capture, 14 JSON, 11 human, and 13
guarded private-session positions. Counts repeat for the same scenarios across
variants/builds; they are not additional independent datasets. Root validates
schema and exact literal facts separately from producer checks and fault sweeps.
The installed validator is jsonschema 4.10.3.

Root executes the pinned author strict binaries and independently recompiles all
23 implementation/report translation units for each sanitizer variant, plus five
production and six testing consumers. Each executable uses one complete matching
variant. The runtime-only consumers link the 15 runtime/IO-support objects and
foundation archives, with no report or observability object. The session context
therefore preserves the one-guard owner boundary and native archive direction.

The new immutable v3 report retains actual owner/mode/O07/C01 context, separates
state populations from workload events and reset/configuration/segment domains,
and exports typed native bytes without UTF-8 normalization. Absent requests do
not scan state. Pending, stopped, released, stale, sampled, truncated, saturated,
non-applicable and budget-exhausted facts remain distinct. Generalized 0/1
pre-probe presence is labelled separately from native touched degrees. Exact,
one-under and zero encoded byte/item limits and historical lifetime checks pass.
No partial text is returned when export fails.

An independently linked frozen-combined/original-report producer supplies two
C01-off v2 baselines. Every strict/sanitizer production/testing corpus matches
both baseline files byte-for-byte and validates the unchanged closed v2 schema.
Legacy full capture explicitly rejects enabled C01 so instrumentation is not
silently omitted. These are targeted runtime/session comparisons; broader old
CLI and project matrices are still native integration work.

[Strict attempt 1](../../build/verification/c01-statistics-report-root-attempt-1.json)
is explicitly `strict_only` and initially leaves sanitizer work pending. The
[complete sanitizer continuation](../../build/verification/c01-statistics-report-root-attempt-2.json)
pins and reuses those successful strict results, then builds/runs the complete
matching sanitizer variants without repeating unchanged strict execution.
Root sessions 1299 and 12748 are terminal and closed. Full compiler commands,
binary/dependency/artifact/log hashes, fixture files and comparisons are retained.

Two source issues were resolved before the proposal freeze: the first session
report seam introduced a runtime-to-observability dependency, and a generic
degree-kind label misnamed generalized presence probes. The accepted immutable
runtime-only context and role-specific label correct those issues. No failing
root report fixture was discarded or rewritten. Frozen ancestors and native
sources remain unchanged.

Native publication still requires the explicit CMake/test/documentation overlay,
portable checked-in v2 baselines and removal of the preparation-only repository
acceptance field from runtime capabilities. The final native matrix and source
audit remain open. Timing evidence is in the separate accepted actual-engine
benchmark packet; neither this report nor component byte fields establish S05
total/peak allocator memory, cost ranking, arrival Hz, or new proof authority.
