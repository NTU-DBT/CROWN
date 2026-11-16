# C02 ranking usage guide — excluded proposal

This guide documents the current draft API in the neighboring C02 baseline
ranking proposal. **C02 remains `not_started`; these headers are not accepted
native APIs.** The examples consume an already-owned, typed P07
`CandidateSnapshot` and an already-initialized actual owner. They do not build
proofs, search for candidates, import evidence, alter P07 context, or deploy a
runtime.

See [the usage guide](usage-guide.md), [source map](source-map.md), and
[compile evidence](compile-evidence.md). `input-pins.sha256` records the API and
native type headers used; `PACKAGE_SHA256SUMS` seals this excluded packet.

The API owner marked the public headers stable enough for this guide's pins and
compile pass. The snippets compile with the repository's six strict warning
flags in production and `CROWN_RUNTIME_TESTING` macro variants. The wider C02
proposal remains unaccepted and is not frozen; any later public-header change
requires refreshing this guide's pins and compile evidence. No linking or
execution was performed. Root owns all validation of the future implementation.
