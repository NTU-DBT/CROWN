# Workload schema usage contracts

These declarative JSON-pointer contracts complement the [source block map](README.md).
They describe validation shape and usage, not evidence that runtime observations are true.
B05 is local measurement engineering under [Refactor.md](../../Refactor.md); its
[methodology](../adversarial_scalability.md) and [measurement boundaries](../measurement.md)
define the runtime interpretation. The v1 raw-report schema remains unchanged.

## schemas/workload-manifest-v1.schema.json `/properties/generator/properties/path`

Source: [schemas/workload-manifest-v1.schema.json](../../schemas/workload-manifest-v1.schema.json)

Reviewed SHA-256: `4bb629c4dd71c9a30330107077c8a736d5159aab4d0a4c707a77bfdd5a10443e`

**Purpose:** Allow exactly the reviewed B02 and B05 generator paths in a workload-v1 manifest.

**Inputs outputs:** Generator path string is constrained to tools/generate_workloads.py or tools/generate_adversarial_workloads.py.

**Invariants:** Manifest schema version remains 1; generator SHA, seed, scale, query IDs and ordering fields remain required and independently verified.

**Ownership:** Declarative schema only; no runtime owner.

**Failure:** Other path values fail JSON Schema validation.

**Cost:** One enum validation for the selected field.

**References:** [schemas/workload-manifest-v1.schema.json](../../schemas/workload-manifest-v1.schema.json), [tools/verify_workloads.py](../../tools/verify_workloads.py), [tools/generate_adversarial_workloads.py](../../tools/generate_adversarial_workloads.py)

## schemas/workload-measurement-v2.schema.json `/properties/schema_version`

Source: [schemas/workload-measurement-v2.schema.json](../../schemas/workload-measurement-v2.schema.json)

Reviewed SHA-256: `8f0a7fa60da843173fc6a148bc4684b459ef5cb8bfc1cbdc110a7228de69e95f`

**Purpose:** Define the raw workload-measurement report envelope at schema version 2.

**Inputs outputs:** Raw verify or measure report JSON in; constrains root version to integer 2 and command-specific members.

**Invariants:** Embedded request remains schema version 1. Version 1 report schema remains a separate unchanged compatibility contract.

**Ownership:** Declarative validation only.

**Failure:** Wrong version, missing required fields or additional disallowed fields fail validation.

**Cost:** Schema validation scales with supplied report document and schema branches.

**References:** [schemas/workload-measurement-v2.schema.json](../../schemas/workload-measurement-v2.schema.json), [examples/workload-measurement/main.cpp](../../examples/workload-measurement/main.cpp), [tools/run_measurements.py](../../tools/run_measurements.py), [tests/integration/measurement_harness.py](../../tests/integration/measurement_harness.py)

## schemas/workload-measurement-v2.schema.json `/$defs/epoch/properties/storage`

Source: [schemas/workload-measurement-v2.schema.json](../../schemas/workload-measurement-v2.schema.json)

Reviewed SHA-256: `8f0a7fa60da843173fc6a148bc4684b459ef5cb8bfc1cbdc110a7228de69e95f`

**Purpose:** Require separate source/support arena counts and derivation-key count on each measured epoch.

**Inputs outputs:** Storage object references the storage definition; source and support use the arena definition.

**Invariants:** Arena counters are unsigned populations with a closed property set. Schema validity does not prove runtime values came from the claimed sampling boundary.

**Ownership:** Declarative schema only.

**Failure:** Missing fields, negative/out-of-range values or unknown nested keys fail validation.

**Cost:** Validates the fixed count fields per epoch.

**References:** [schemas/workload-measurement-v2.schema.json](../../schemas/workload-measurement-v2.schema.json), [examples/workload-measurement/main.cpp](../../examples/workload-measurement/main.cpp), [tools/analyze_adversarial_scalability.py](../../tools/analyze_adversarial_scalability.py)

## schemas/workload-measurement-v2.schema.json `/$defs/arena`

Source: [schemas/workload-measurement-v2.schema.json](../../schemas/workload-measurement-v2.schema.json)

Reviewed SHA-256: `8f0a7fa60da843173fc6a148bc4684b459ef5cb8bfc1cbdc110a7228de69e95f`

**Purpose:** Define the six numeric arena population counters used by each storage sample.

**Inputs outputs:** Requires slots, live_records, retained_records, pins, free_slots and exhausted_slots as unsigned 64-bit values.

**Invariants:** Field shape only; the analyzer separately checks the slot partition on its selected B05 records.

**Ownership:** Declarative schema only.

**Failure:** Unknown/missing properties or invalid unsigned values fail schema validation.

**Cost:** Six scalar checks per source/support arena object.

**References:** [schemas/workload-measurement-v2.schema.json](../../schemas/workload-measurement-v2.schema.json), [tools/analyze_adversarial_scalability.py](../../tools/analyze_adversarial_scalability.py)

## Candidate and EXPLAIN family constraints

Sources: [candidate report](../../schemas/candidate-report-v1.schema.json)
`/$defs/candidate`, `/$defs/snapshot`, `/$defs/progress`, and
[EXPLAIN report](../../schemas/explain-report-v2.schema.json)
`/$defs/physical_report`.

**Purpose:** Preserve the distinction between original seed/normal-form
exhaustion and consumption of caller-supplied finite proposals.

**Inputs outputs:** The family controls permitted provenance source and precise
exhaustion label. Snapshot members must have their parent family's label;
EXPLAIN's selected source must agree with its optional reported family.

**Invariants:** Existing default output labels stay unchanged. Finite batches
use `finite-proposals-v1`, `supplied_proposal` and
`supplied_finite_proposals_v1_only`. Nullable EXPLAIN fields remain nullable.
Partial conditional constraints inherit the closed outer object declarations;
they do not declare a second open record shape. Schema validity establishes
neither proof authority nor actual exhaustion.

**Ownership:** Declarative schemas create no engine owner, callback or update
hook. Native writers retain their existing typed ownership boundaries.

**Failure:** Unknown/mismatched labels and cross-family members fail schema
validation. A typed candidate paired with a different family snapshot rejects
with `explain_family` before report publication.

**Cost:** Offline validation scales with the supplied document and schema
branches. Typed EXPLAIN admission uses an owning provenance getter that can copy
residual traces; this is separate from runtime update cost.

**References:** [candidate usage](../candidate_alternatives.md),
[meta work](../meta_decompositions.md),
[native fixtures](../../tests/unit/candidate_proposals_test.cpp),
[strict verifier](../../tools/verify_candidate_reports.py).

Reviewed candidate SHA-256: `28026b2a6a2bd1a11e14b48db17da21d3edb20d4f716e781d1ab8e807af67e80`; EXPLAIN SHA-256: `655f0bb6232968f613edfe33b008538014a720b12114bc5ba1d1d2e8848d893f`.

## Component Session synthetic consumer wait

Source: [component runtime request](../../schemas/component-runtime-request-v1.schema.json)
`/properties/session/properties/consumer_delay_us`.

Reviewed SHA-256: `d91b16d5943f2f1590ceb5539e288a525e7e8312cdf39445bf2378a69901576d`.

**Purpose:** Admit the explicit experimental wait at a committed Session output
service boundary, as described in the [component guide](../component_evaluation.md).

**Inputs outputs:** Optional integer microseconds in0..100000; omission selects
zero in the native reader. It changes an experimental client's service schedule.

**Invariants:** Native admission rejects nonzero wait with maintenance-only output.
The actual wait retains the committed epoch and appears inside output/loop time;
its separate counter is nested. Schema shape alone establishes no runtime or
queue-saturation observation. Existing per-physical-event commitment is preserved.

**Ownership:** Declarative schema owns no runtime state. The client retains the
actual epoch until its ordinary output action completes.

**Failure:** Out-of-range or wrong-type values reject at schema/native boundaries;
the native reader additionally enforces action compatibility and integer encoding.
It selects no approximate, parallel or fallback operation.

**Cost:** Schema validation is offline. Zero wait adds no sleep-clock reads; nonzero
wait performs an actual sleep and two clock reads in the experimental client.

**References:** [Session source](../../examples/component-runtime/session.cpp),
[exact source contract](files/examples/component-runtime/session.cpp.md),
[actual receiving](../../build/verification/component-evaluation-v60-v1/runtime-fields-receiving-v1.json).
