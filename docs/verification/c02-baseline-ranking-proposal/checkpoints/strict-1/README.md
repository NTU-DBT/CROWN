# Strict-only execution checkpoint 1

This checkpoint freezes the completed strict implementation, ten consumer links
and their actual inputs while the separate sanitizer build and package prose
finish. It is not a complete-package, sanitizer, native-matrix or card-completion
verdict. The author has not executed a consumer or checker.

From repository root, `INPUT_SHA256SUMS` pins actual full compiler dependencies,
the compiler/backend, original/patched header provenance, explicit compile
recipe, parser C archive/configuration, unchanged inherited P07 fixtures/schema
inputs and checker. Relative paths resolve from repository root; absolute paths
are actual system compiler inputs or isolated artifacts. `ARTIFACT_SHA256SUMS`
pins 92 objects, seven rebuilt C++ archives and ten executable links.
`COMMAND_EVIDENCE_SHA256SUMS` pins exact commands, full dependencies, compiler
logs/exits, source/header before-after records and archive member lists.

Root should check all three manifests before and after running every argv from
`root-commands.json`, retaining terminal exit/stdout/stderr/time and guard
results. No inherited IO output directory is required: the existing Python
checker calls its producer with `--emit` and reads captured stdout. The other
inherited semantic consumer needs the exact `tests/candidates` directory.

All CROWN C++ objects use the same patched header. Only the matching Release
parser C archive is reused; no cached native C++ archive or report library is
linked. Runtime consumers use exactly one production/testing variant, and the
pure consumer has no runtime/report link.

Source/header/strict artifact bytes covered by these guards are held unchanged
until root reports completion of the before/after guard. Later implementation
changes require a new revision/checkpoint and matching sanitizer rebuild, not a
silent alteration of this historical checkpoint.
