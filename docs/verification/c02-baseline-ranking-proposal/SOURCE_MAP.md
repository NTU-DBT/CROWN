# Overlay and linkage map

All destination paths below are relative to the repository root. This is an
excluded proposal, not an instruction to apply files while native C01 is frozen.
`source-files.sha256` pins the actual overlay bytes when this packet is frozen.

| Destination | Change | Responsibility |
| --- | --- | --- |
| `include/crown/planner/ranking.hpp` | New | Typed pure request, immutable Evidence/Result and exact score terms |
| `include/crown/runtime/ranking_evidence.hpp` | New | Actual-owner capture, per-policy revalidation and synchronous convenience API |
| `src/planner/candidate_binding.hpp` | New | Shared private full binding-format-v2 encoder, optional bounded sink |
| `src/planner/candidates.cpp` | Existing file overlay | Only moves the old encoder behind the helper; P07 authority/context/format unchanged |
| `src/planner/ranking_detail.hpp` | New | Private budgets, fixed limbs and immutable factories |
| `src/planner/ranking_integer.cpp` | New | Portable exact arithmetic and canonical integer text |
| `src/planner/ranking.cpp` | New | Complete admission, scoring, explicit fallback and deterministic selection |
| `src/planner/ranking_payload.hpp` | New | Private component accounting interface |
| `src/planner/ranking_payload.cpp` | New | Per-candidate owned source and compiled-plan payload admission |
| `src/runtime/ranking_evidence_detail.hpp` | New | Private census classifier seam for isolated numeric boundary tests |
| `src/runtime/ranking_evidence.cpp` | New | Native joint capture and actual-owner checks, no report dependency |
| `third_party/nlohmann/json.hpp` | Existing file overlay | Allocation-safe exceptional JSON cleanup, exact local diff/provenance preserved |

The two existing destinations have exact native predecessors pinned in the
input manifest. The ten new destinations do not overwrite native APIs. Public
factory constructors remain private; only tests explicitly including private
implementation headers can exercise isolated injected boundary records. Such
fixtures are not an evidence import mechanism.

The compile-only closure uses seven archives, all newly compiled with the same
patched Json header. The source lists in `compile-closure.sh` are explicit and
the generated `.members` and `STRICT_IMPLEMENTATION_OBJECTS.tsv` name every
actual source/definition/object. Core has 31 TUs (with the overlay candidates
implementation), SQL 10, plan 3, ranking 3, reference 5, production runtime 15,
and testing runtime 15: 82 implementation/reference TUs per configuration.
The testing runtime and its evidence adapter are compiled with
`CROWN_RUNTIME_TESTING`; production is compiled without it. They are never
linked together. All other project C++ dependencies are common, rebuilt inputs.

The pure link consumer has ranking/core/SQL/plan dependencies and no runtime or
report archive. Runtime consumers select exactly one runtime variant. Neither
link contains crown_explain, crown_query_explain, report IO or a cached native
project C++ archive. The unchanged parser C dependency is reused only with its
matching Release or sanitizer configuration and is separately pinned.

## Later native integration obligations

This packet does not edit CMake. A later reviewed registration must add the
pure/runtimes sources to appropriately directed targets, update the native
vendored-Json checksum to the accepted patch, retain all C01/P07 tests, and
register relevant new consumers plus independent cleanup/semantic tests. The
native matrix must recompile every Json-using C++ unit consistently; simply
overriding one inline instantiation or linking a patched object into old C++
archives is not sufficient. No new report schema or serialization authority is
part of this overlay.
