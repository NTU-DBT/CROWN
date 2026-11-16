# Metadata/build-guard revision evidence

## Root preflight attempt 2

Root's preflight record is
`build/verification/c01-statistics-native-benchmark-input-preflight-attempt-2.json`
(SHA-256
`b6c8b4882b21ba13a12ec3c6f5a5667ec636e5a5b3b6a38a73705793b00696f6`). It
reports one issue before execution: the frozen oracle revision's pin for
`storage_reference.o` contained a 63-character digest. The preserved report
records the expected malformed string, the actual correct 64-character hash,
and explicitly says `native_binary_executed: false` and
`raw_attempt_2_exists: false`.

The corrected hash is
`2827e2263ef2fdc124564dab2dec6dd50bf4813162896122707314d735a80f9e`. It is
used in this revision's `input-pins.sha256` and the explicit object check in
`build-only.sh`. The build script also applies GNU `sha256sum --check --strict
--status` to the complete input manifest and its object/archive records. This
prevents a malformed checksum line from being silently ignored. The original
preflight artifact and frozen oracle revision are unchanged.

## Existing corrected binary and build provenance

The corrected benchmark source was already compiled and linked in the prior
oracle revision using C++23, `-O3 -DNDEBUG`, and the full six warning flags as
errors. This metadata revision does not recompile or relink it. The existing
binary SHA-256 is
`ada8dae17e73c568fdec0886466d19a0352377fefb778b8ff6ef445a9b1549d8`; its
source SHA-256 is
`7f2ce2e8b9a86088b0e181263351dc246aac9ad4ca544c8acb5fbbb127b842a6`. Its 15
O3 runtime/collector/storage object hashes and four Release archive hashes
remain in `input-pins.sha256`. No CROWN_RUNTIME_TESTING define was used for
that production build.

The build-guard revision itself was not built and its script was not run by the
author. No benchmark, diagnostic program, test, checker, CMake, CTest, or `nm`
command was run. Root owns strict input preflight and benchmark execution.
There is no measurement or benchmark acceptance result in this package.
C01 remains `not_started` and excluded preparation.

## Metadata revision identities

| Artifact | SHA-256 |
| --- | --- |
| metadata `build-only.sh` with strict hash checks | `d45b9db8bbb4efaa01ac53ab71a4aaabf2c8264c9a7d1110475de25d8c78a402` |
| corrected `input-pins.sha256` | `9c82b9071ee41aa0384ff65f4ccd1ee70094ae69f005c9094493b697594f6692` |
| unchanged corrected consumer source | `7f2ce2e8b9a86088b0e181263351dc246aac9ad4ca544c8acb5fbbb127b842a6` |
| exact metadata/build-guard diff | `5b9b6fc56d56b22acef2972ff60c695a7a5de6a93270326fc10cb358e6976330` |
| existing corrected binary, not rebuilt or run | `ada8dae17e73c568fdec0886466d19a0352377fefb778b8ff6ef445a9b1549d8` |
| root's no-execution preflight attempt 2 | `b6c8b4882b21ba13a12ec3c6f5a5667ec636e5a5b3b6a38a73705793b00696f6` |
