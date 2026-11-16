# P07 typed report proposal

Preparation only, 2026-11-07. P07 remains `not_started`. This directory is
excluded from native sources, schemas, targets, tools and CTest. Nothing here
establishes integration, P07 acceptance, or completion of the frozen P05 run.

`report.hpp` and `report.cpp` propose three allocating writers in
`crown::io::alternatives_proposal`:

- `write_candidate_progress(const CandidateProvider&)` samples the live owner's
  diagnostic progress, counters, limits and family status. It intentionally
  does not accept an editable `CandidateProgress` aggregate.
- `write_minimum_height_candidate(const MinimumHeightCandidate&)` exports the
  checked alternative upper, structural key and original generation provenance.
- `write_candidate_snapshot(const CandidateSnapshot&)` exports the immutable
  prefix and its actual family-exhaustion flag. A partial or cancelled prefix
  retains the supplied proof of original minimum height.

There is no reader, proof constructor, proof replay implementation, API-draft
change or new native integration. Serialization is explicit allocating IO
outside advance quanta; it does not advance or resume the provider. Invalid or
moved artifacts are rejected. The report schema accepts only supported exact
context versions and the declared exact-seed/residual-seed/normal-form family.

## Proof and exhaustion scopes

Every report contains exact `query_binding`, context and `original_proof` with
scope `original_query`. The original certificate is exported exclusively using
native `write_verified_optimum`, retaining its own original witness and lower
claims. Native `query_binding` selects CQ v1, typed date/decimal v2 or catalog
metadata v3, with all original binding information preserved.

The candidate's alternative tree appears only in `checked_upper`, labeled
`checked_upper_only`. Its checked height equals the separately supplied original
minimum. The writer checks that height and exact binding agree before export.
It never replaces the original certificate's witness with the alternative tree.
A structural key supplies identity within its binding/context, not proof.

`family_exhausted` covers admitted seeds plus the specified normal form, not all
possible tree shapes or globally cheapest plans. `optimization_scope` is fixed
to `structural_height_only`. Original minimum-height proof is present before any
candidate and is independent of enumeration completeness or cancellation. The
snapshot includes no cursor-resumption claim. Sequence numbers retain their
original generation meaning and are not globally unique cache-reuse IDs. The
current API does not expose the internal reuse ledger, so this report cannot
export it. Optional residual provenance embeds the existing native residual
trace report, whose audit scope remains the frozen trace only.

The conservative standalone format embeds the complete original certificate
**including its original witness**. Merely exporting h*, a proof flag or a
structural key would lose the self-contained evidence needed for later exact
binding checks and independent replay. Snapshot entries are full candidate
reports and repeat the certificate/binding for independent extraction. This
trades larger output and allocating serialization work for simple ownership and
self-contained provenance. A later referenced-proof bundle could remove this
repetition, but would need an explicit external reference and binding protocol;
this proposal does not invent one.

## Strict schema boundary

`candidate-report-v1.schema.json` uses Draft 2020-12, strict named objects with
`additionalProperties: false`, required fields and constrained artifact,
context, family, proof-scope and status values. It references existing strict CQ,
tree, certificate and residual-trace schemas by repository-relative paths;
those native schemas remain unchanged. Original certificates must contain a
non-null minimum and original witness. Phase/exhaustion and residual-provenance
relationships receive additional structural constraints.

Schema validation checks document shape, not proof validity. Standard JSON
Schema cannot compare separate binding/height fields, prefix length with a count,
or deduplicate computed structural keys. Those are typed producer invariants;
a future reader must independently check them and replay proof/upper validity.
A schema-valid manually edited document cannot manufacture a checked handle.
The report envelope is rejected by the existing height-certificate reader.

## Supplemental validation

Strict direct `-O0` and `-O3` builds and runs passed with the existing release
core archive, without configuring/building any CMake target or invoking CTest.
At each optimization level, `report-probe.cpp` emitted **23 actual reports**
using real P06 proofs across CQ v1, date v2 and metadata v3. It independently
replayed every embedded original certificate, checked equality with native
original export, and exported an alternative upper different from that original
witness. It also checked P02 validity, immutable partial snapshots, admitted and
cancelled progress, no progress advancement during IO, rejected moved artifacts,
and compile-time exclusion of untyped progress/upper-only inputs.

`validate-probe.py` accepted all 23 documents and rejected **48 meaningful
mutations** per build, including extra properties at multiple nesting levels,
null original proof evidence, wrong proof scope/context/family, promoted upper
status, invalid counters/limits, forged exhaustion and malformed provenance.
These are supplemental release-linked report checks, not sanitizer evidence or
an exhaustive binding/provenance corpus. Residual-source export is implemented
using the existing typed trace writer but this small fixture corpus does not
publish a distinct residual-source candidate; that path needs a later fixture.

Reproduce from the repository root, replacing `-O0` with `-O3` for the second
configuration:

```sh
g++ -std=c++23 -O0 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -Iinclude -Isrc/planner -isystem third_party docs/verification/p07-report-proposal/report-probe.cpp docs/verification/p07-report-proposal/report.cpp docs/verification/p07-facade-proposal/facade.cpp docs/verification/p07-generator-proposal/generator.cpp docs/verification/p07-key-proposal/key.cpp build/release/libcrown_core.a -o /tmp/p07-report-O0
/tmp/p07-report-O0 > /tmp/p07-reports-O0.json
python3 docs/verification/p07-report-proposal/validate-probe.py /tmp/p07-reports-O0.json
```

Artifacts, runtime/schema logs and source/archive fingerprints are saved under
`build/verification/p07-report-proposal-2026-11-07/`. The public API draft and all
other proposal directories remain unchanged by this report task.
