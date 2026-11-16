# Frozen native publication proposal

Frozen on 2026-11-07 after the complete direct optimized check. The packet
contains 38 mapped native destinations: seven overwrites with exact pre-edit
hashes and 31 new paths. Native sources, original Refactor.md, task status,
handoff and all predecessor packets remain untouched.

The complete overlay source manifest has SHA-256
`c86f38f21540fde74d0004d3ff55af4c1ef5aea054a62c5edcb6a068bb4915ba`.
The 633-entry input manifest has SHA-256
`08a92c0dca224107b35aafbede9f80d35e24c061bacecd6270e8c233c1ed09a3`.
The four-column source map has SHA-256
`e3fd7f876c08ab39594ff89caf071b78cdad0810ddf56aefd362375ce96fa060`.
The sorted 143-test inventory has SHA-256
`5afdb9379b4adfc66684530d26f066cd73ea80f790d36763c9df4441d10734b1`;
the ordered inventory has SHA-256
`3160e499257bc742462fc8e809c795e2c12e4f30a1edd43d951a2e0e0e5793e9`.
Expected native compile entries are 214, pending actual root CMake verification.

The final direct artifacts contain 19 compiled new TUs, eight C++ archives and
12 executable links. All final compiles/archive constructions/links exit zero
with empty diagnostic logs. Their 39-entry artifact manifest has SHA-256
`7d9e9f81d88de5fe47a06d5a5ef887e5fb53acec92d846ee14a9c8179d673896`.
No artifact/checker was executed by the author. The new wrapper/probe copy and
native 143-test matrix await root execution. Accepted predecessor strict/SAN
results are attributed separately in BUILD_RESULTS.md.

All 12 implementation files remain byte-identical to the accepted frozen C02
baseline. The only test-source publication delta is the accurately named custom
vector probe and its three noinline annotations/comment; every numeric and
fault assertion is preserved. No pending native gate is converted to an
acceptance field in a user-facing API, CLI, report or schema.

PACKAGE_SHA256SUMS pins every packet file other than itself, with paths relative
to the repository root. Its final file hash is sent separately to root and the
independent reviewer to avoid a self-referential digest. Keep this packet and
all named artifacts immutable through guarded review/execution/application.
