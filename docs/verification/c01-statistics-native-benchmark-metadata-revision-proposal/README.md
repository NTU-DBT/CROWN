# C01 native benchmark metadata and build-guard revision

This separate excluded revision preserves both the original native benchmark
package and the oracle correction package
`docs/verification/c01-statistics-native-benchmark-oracle-revision-proposal/`
(manifest SHA-256
`6c9f818a539a1f44f05169795620fd82147a661e6a861ec474af17328bbcd39b`). It
corrects one malformed storage object digest in the oracle revision's
`input-pins.sha256` and build script. The benchmark C++ source is byte-identical
to the oracle correction; no benchmark binary rebuild is needed or performed.

## Preserved preflight failure and correction

Root's metadata preflight attempt 2 stopped before executing any binary. The
preserved record is
`build/verification/c01-statistics-native-benchmark-input-preflight-attempt-2.json`,
SHA-256 `b6c8b4882b21ba13a12ec3c6f5a5667ec636e5a5b3b6a38a73705793b00696f6`.
It identifies a single malformed, 63-character expected hash for
`/tmp/crown-c01-native-benchmark-author/storage_reference.o`. The actual object
hash is the 64-character
`2827e2263ef2fdc124564dab2dec6dd50bf4813162896122707314d735a80f9e`, which
matches the original root attempt's object identity. Root records that the
native binary was not executed and attempt-2 raw output does not exist.

This revision replaces the malformed digest in both the copied input pins and
build script with the correct 64-character value. The build script uses
`sha256sum --check --strict --status` for its full input-pin manifest and its
object/archive guards. `--strict` makes malformed checksum records fatal,
including a short digest that a non-strict check could skip. Exact changes
against the frozen oracle revision are recorded in `metadata-correction.diff`.

The existing corrected benchmark binary remains at
`/tmp/crown-c01-native-benchmark-oracle-revision-final/crown_c01_native_benchmark`
with SHA-256
`ada8dae17e73c568fdec0886466d19a0352377fefb778b8ff6ef445a9b1549d8`. Its
source and 15 linked O3 runtime/collector/storage objects are pinned. Root owns
the strict preflight and subsequent execution of that binary.

## Build and execution boundary

This metadata-only revision does not compile or link C++ and does not execute
the binary. If a future rebuild is needed, the exact command is:

    CXX=c++ bash docs/verification/c01-statistics-native-benchmark-metadata-revision-proposal/build-only.sh \
      /tmp/crown-c01-native-benchmark-oracle-revision-rebuild \
      /tmp/crown-c01-native-benchmark-author

That script first strictly validates the input manifest, then verifies the 15
pinned O3 runtime/collector/storage objects and four Release archives. It
recompiles only the unchanged benchmark consumer and relinks it. Root's
preflight and run remain separate from this optional rebuild command.

The earlier root attempt 1 failed at the benchmark's first untimed S/P/E
oracle guard because child P had been compared with the global answer. That
independent oracle issue was corrected in the preserved oracle revision; the
first attempt emitted no benchmark JSON. The metadata preflight failure
recorded here is a separate issue and occurred before any revised binary run.
No native/runtime source, schema, report, CMake target, or C01 publication
status changes here. C01 remains `not_started` and excluded preparation.
