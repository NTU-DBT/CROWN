# S04 indexed storage and runtime verification

S04 is verified on the complete published native integration. All 199 tests
pass each of five configurations on identical staged source bytes. Each fresh
build actually compiles 281 C++ commands from 231 distinct sources. Root audits
accept flags, assertions, link/ABI population, one storage-owner allocator,
production/test authority isolation and actual parser ASan/UBSan symbols.

| Configuration | Tests | Actual C++ commands | CTest seconds |
| --- | --- | --- | --- |
| GCC Debug | 199/199 | 281 | 3024.96 |
| GCC Release | 199/199 | 281 | 498.13 |
| ASan + UBSan + leaks | 199/199 | 281 | 14152.98 |
| Clang Debug | 199/199 | 281 | 2431.23 |
| Clean source-only Release | 199/199 | 281 | 498.70 |

The execution freeze is `build/verification/s04-native-matrix-execution-freeze-attempt-1.json`.
The accepted complete matrix is `build/verification/s04-complete-native-matrix-audit-v1.json` (SHA256
`7ddfb6d4e27ab51c38f7d14365520d2e436a03d49359a2ebc6069224f6fec624`), and the precompletion source binding is
`build/verification/s04-current-native-source-audit-v1.json` (SHA256`47c5d133df971be8333c11c4fe031cc527dc5dee2589ffa4070c3001c38921b6`).
Final metadata/source-seal authority is recorded separately in
`build/verification/s04-final-native-source-audit-v1.json` and
`build/verification/s04-completion-checkpoint.json`.

## Runtime and index coverage

Indexed Support/Physical/Delta/Session, initialization, C01 capture and C02/C05
direct/normalized live-owner selection are integrated. Independent oracles
cover 14 structural families/1064 support updates, 450 physical epochs, 2712
delta updates in each of five modes and 18 owner-capture groups. Six original
reference regressions pass. Seven derived oracle files retain exact expected
states/assertions with only backend selector/include transformations.

Actual aggregate runtime work is`{1695,588,23982,2631,4410}`. Five independent
one-under cases preserve complete previous membership, handles, metadata,
counts and pins and permit a smaller valid retry. All 167 persistent allocation
failure positions recover without another allocation attempt. Commit allocates
nothing; cursors/delta continuations/captures and target rebuild keep one grant.
Integer annotations above2^53 remain exact; exact membership uses no epsilon.

Debug/Clang generate 32 byte-identical artifacts and each passes 42 exact
numeric schema boundaries and 140 rejected mutations. All 31 schema documents
and 1251 offline references are checked. Publication receipts retain all 74
applied paths and native preimages. Current source controls bind 847 native
inputs and 849 staged files, including the independent clean source snapshot.

## Qualified measurements

The production `StorageTable` comparison retains 80 raw samples/40 paired
runs and 136 timing groups: populations 16/256/4096/16384, payloads 2/258 bytes,
fixed secondary-key degree 16 and five alternating repetitions. Complete-row
oracles and paired checksums match. Input materialization, construction, load,
replacement, trim and destruction remain visible in the raw records.

Ratios below are indexed/reference median time across the eight population/
payload cases. The finite fixture shows both improvements and regressions.

| Operation | Indexed/reference ratio | Observation |
| --- | --- | --- |
| Secondary-bucket walk | 0.340–0.818 | Faster |
| Primary hit/miss probes | 1.378–7.647 | Slower |
| Eight-live walk after history | 1.310–1.408 | Slower |

Eight-live traversal admits exactly `{10240,0,0,8192,0}` for all tested histories
and payloads. This includes 1024 cursor startups, eight advances and end per
cursor, plus eight pointer words of startup metadata per cursor. Pointer-word
admission is separate from allocator bytes and CPU time. These observations
establish no universal or whole-runtime speedup. Profiling/calibration and
B03/B05/C03 remain open; all slow cases stay in the evidence packet.

Raw measurements: `build/verification/s04-storage-comparison-attempt-1/`.
Timing summary: `build/verification/s04-storage-comparison-summary-attempt-1.json`.
Results review: `build/verification/s04-storage-comparison-root-results-review-v1.json`.

## Preserved development evidence and open gates

Prepublication source12 passed 19 strict Debug and 19 ASan/UBSan/leak tests.
Failed source10 strict-test compilation and source11 allowance assertions,
debugger/rebuild probes and all executed helper versions remain preserved.
They are historical preparation; current acceptance uses the full matrix above.
Historical manifest FILE identities remain intact. Their old source/INPUT
entries are never evaluated against successor code.

This backend is an independent original implementation. Refactor.md explicitly
allows independent implementation while A02 is open. No Scala/DynaGox legacy
source was copied for this backend; the project license/distribution choice is
still pending. S05 whole-query allocator bytes/peaks, recovery/durable delivery,
whole-runtime performance and release/full 78-card completion remain open.
