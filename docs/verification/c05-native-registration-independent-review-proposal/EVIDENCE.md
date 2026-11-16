# Evidence and acceptance boundary

Root's immutable preparation aggregate is
`build/verification/c05-preparation-execution-completion.json`, FILE SHA-256
`43b420248cb77e1c6c9ba72fe6f29e3de80498740d19d53b0cafbad935d5f0c9`.
It accepts the excluded execution scopes and the prior independent source
review, while retaining native C05 as not started at that checkpoint.

The final producer sanitizer receipt is
`build/verification/c05-producer-sanitize-root-attempt-1.json`, SHA-256
`b4751d01a1d5d867a7c415fc656052dcbb97e6099baa8e81264a0bba6f20f4af`.
The independent sanitizer receipt is
`build/verification/c05-independent-sanitize-root-attempt-1.json`, SHA-256
`1352225d850e10cbffcca9f654b81acde7edb825ac1fd7063d43d28011b4b3f8`.
Their producing sessions are terminal. No live log or build-only receipt is
used as a runtime pass.

Both ordinary and matching sanitizer generations pass all ten producer
consumers and the selected five independent consumers / 22 groups. The latter
retain depth 195/105/190, slots 24/32/32, caps 23/24/31/32, alias/unused source
10/7, Decimal/repeated head 13 and zero 0. Producer direct and normalized
persistent sweeps observe 32,966 and 20,420 positions respectively, with zero
cleanup recoveries. Independent focused publication probes observe 22 selected
positions, two late publication failures and zero completed fault positions.
Those different populations are not combined into a new exhaustive claim.

The earlier source-review package is FILE-pinned as
`6590cecabeff424ea347c3dcf78295443431f7e9a81ee080443e8aee049e00d8`.
Its as-of sanitizer-pending statement remains historically correct. The newer
terminal receipts extend execution evidence without rewriting that package or
its 14/13/108 provenance. The real-normalized positive-boundary coverage limit
still applies after those sanitizer successes.

The verified native predecessor is C02. The current 764-file seal FILE hash is
`3ab4ca48b70203e5cf4e85f4883a6c2279bc01d164ad7ad054adace94dc62a41`.
It is not expanded or entry-checked by this reviewer. Root's retained generated
evidence receipt is `build/verification/c05-c02-predecessor-build-evidence.json`,
FILE SHA-256 `b21d69747ea69f0a7d7d86ffd9c372dc47eee5020ee4f0e386a5b45cc1616561`.
The retained Release compile database and CTest registration provide the old
214-entry / 143-test metadata baseline independently of mutable build paths.

Final publication copies and preparation receipts do not establish native
CMake execution, a complete 158-test five-configuration matrix, all 238 actual
compile entries/closures, incremental cache reuse, or clean-source portability.
Those remain root-owned gates. This packet does not advance C05, another card,
the ledger, handoff, or the full goal.
