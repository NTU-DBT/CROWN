# Remaining execution gates

Root supplied the normalized SQL quote-only checkpoint. Its manifest FILE is
`d3c8a81bda48d506023a38a6f720f1c41c31aaa4b5a46eb188b511e7b87bb871`;
its current-source manifest FILE is
`93e1318bfd55a1447990710b4da40667aeb0dc6413996e40a03746697bf9b8c8`.
The terminal targeted strict compile/link receipt is
`build/verification/c05-selection-strict-root-checkpoint-5.json`, FILE
`07037eb654cc09e22f4782f2bd0385e6f8b98893b339bd97baabcde141d0213c`.
It records exit 0 and stable sources. The producer fixture itself is not an
independent consumer dependency; its correction is provenance, not permission
to replay an old input manifest against changed live files.

The matching sanitizer implementation closure has compiled and linked
successfully, and all five corrected independent consumers have passed in
strict mode. Their exact receipts and selected source lineage are recorded in
`PROVENANCE.md`. The final source/input/link/package manifests are sealed for
root's independent sanitizer build.

Still required:

1. Root compilation/linking of all five selected consumers with the frozen
   sanitizer recipe and matching production libraries, retaining actual fresh
   full `-MD` records and all dependency/source/artifact guards.
2. Root ASan/UBSan/leak execution of all five consumers with the recorded
   environment. Group counts, focused failure positions and any completed
   failure positions must come from those runs rather than the strict results.
3. Separate completion of producer sanitizer execution, accepted publication,
   native integration and the full native matrix. These are not implied by the
   prepared independent recipe or by the matching library build receipt.

The precise real-normalized exact/one-under replay/normalization gap remains in
`COVERAGE.md`. No independent checker, compiler or binary has run by this author.
