# Evidence-only source map

| File | Purpose |
| --- | --- |
| `tests/ranking_public_independent_test.cpp` | Public API and actual-owner semantic checks. Only public headers are included. |
| `tests/ranking_integer_independent_test.cpp` | Private UInt driver with separate decimal-digit expected-value algorithms. No proof/evidence factory is used. |
| `README.md` | Oracle independence, exact literal expectations and coverage limits. |
| `checkpoints/integer-1/` | Unchanged separately sealed historical arithmetic build. Root retained its old inputs before the active-time ABI revision. |
| `ROOT_REPRODUCTION.md` | Exact current strict binaries and matching fresh strict/sanitizer build and root run procedures. |
| `reproduce-build.sh` | Compile/link-only consumer recipe against an explicitly supplied coherently rebuilt dependency closure. |
| `SOURCE_REVIEW.md` | Independent JSON/payload review identities, two actual omissions and fixes, and remaining execution gates. |
| `BUILD_RESULTS.json` | Recorded zero strict compile/link exits, unchanged before/after inputs, historical evidence scope and pending execution. |
| `build/strict/` | Exact copied current consumer commands, logs, exits, dependency records and before/after input hashes. |
| `provenance/producer-compile-closure.sh` | Exact copy of the producer's coherent compile-only recipe, including both available runtime variants. Root reproduction uses only its production dependency stages for this packet. |
| `provenance/producer-STRICT_*` | Exact copies of the producer's held full implementation/archive inventories; their testing-runtime rows are contextual, not linked by these consumers. |
| `provenance/PRODUCTION_OBJECTS.tsv` | The 67 production source/variant/object rows selected from that inventory; the variant column is empty throughout. |
| `source-paths.txt`, `SOURCE_SHA256SUMS` | Current consumer/recipe plus producer implementation and public/private header identities. |
| `input-paths.txt`, `INPUT_SHA256SUMS` | Actual compiler dependency files, original source/fixture/contract/review inputs, tool and linked dependency identities. Historical manifests are pinned as files only. |
| `artifact-paths.txt`, `ARTIFACT_SHA256SUMS` | Current two binaries/objects and exact producer production objects/archives/command evidence used by the build. |
| `PACKAGE_SHA256SUMS` | All other files in this proposal, including preserved historical checkpoint files. It does not recursively validate their obsolete live-entry manifests. |

No file maps to a native destination. Root may execute these proposal consumers
against the matching producer overlay. Existing native and frozen files remain
inputs only. All linked CROWN C++ dependencies were coherently rebuilt against
the repaired JSON header; the unchanged parser C archive is the only reused
native archive. The proposal does not add a CMake target or change task status.
