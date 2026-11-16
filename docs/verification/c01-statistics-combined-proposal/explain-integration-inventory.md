# Remaining EXPLAIN and schema integration

This is an inventory and proposed compatibility contract. No report header/source, schema, CLI or CMake file is changed. The existing schema is [EXPLAIN v2](../../../schemas/explain-report-v2.schema.json); no replacement schema has been created.

## Current closed contract

The v2 schema closes `cost` and the physical report with `additionalProperties: false`. Its `cost.statistics` value is the constant `unavailable`; selection and estimated-state capabilities also remain unavailable. [The current writer](../../../src/io/explain.cpp) emits schema version 2, those constants and `C01_statistics` in `open_gates` (lines 355, 413 and 426). Human output likewise says statistics are unavailable. Appending C01 fields to a v2 object would violate that contract.

[PlanExplanation](../../../include/crown/observability/explain.hpp) is an immutable factory-produced handle. Its runtime/session factories in [the report implementation](../../../src/observability/explain.cpp) already bind actual owner configuration, observations, cursor metadata and committed gauges. They have no retained C01 handle or state-capture request. O07 observations report O07 mode/options; they cannot identify an independently configured C01 collector. Caller-declared benchmark labels remain declarations, not measured instrumentation configuration.

## Proposed opt-in representation

Keep default v2 capture/serialization byte-compatible. Introduce a separately versioned, explicitly requested physical/runtime/session report format for C01. Its new closed schema should have a top-level `statistics` object and an independently identified instrumentation object; do not silently add keys to v2 or replace catalog estimates with runtime observations. Query/search forms without a runtime should explicitly report no owner and no collected runtime facts.

The proposed statistics transport has separate state and workload sections:

| Section | Required meanings |
| --- | --- |
| Binding | Format version, actual support owner, owner layer, committed sequence and owning physical-plan identity; process-local IDs do not become checkpoint identities |
| State capture | Requested selection count, actual limits/usage, pending/budget/unavailable/not-applicable status, exact cardinalities where known, and individual component completion |
| State distributions | Typed population scope/layout and ordered projection fields; exact NDV and positive-key histograms/top-K only when complete; incomplete NDV/top-K are null, with completed visits labeled as progress |
| Workload interval | Actual options, configuration/reset generations, segment, interval start/current epoch, previous-segment boundaries and modes, pending flag, saturation flags |
| Workload observations | Census physical input/no-op counts, admitted/aborted/selected/truncated coverage, per-stratum descriptors, exact binned observations for complete samples, and explicit rational denominator scopes |
| Freshness | A comparison against an actual current owner and an explicit allowed event lag; data epoch freshness does not stand in for reset/sample/segment equality |
| Memory/work | State cumulative accounted-component payload and workload retained vector-capacity components remain distinct models, with their exclusions; neither is S05 total/peak allocation accounting |

Support and degree event histograms describe touched events/after-values; state histograms describe current positive keys. These populations must have separate names and denominators. Deterministic sampling does not imply unbiased extrapolation. Arrival rate and timed C01 collection remain unavailable. A current stamp does not make a pending, budget-exhausted or sampled component exact.

Typed keys need a deliberate transport representation that preserves exact native bytes, Date/Decimal values, ordered/repeated fields and empty keys. Invalid UTF-8 and embedded NUL must not be normalized, silently replaced or used to infer NULL. A new typed byte-string encoding is preferable to fabricating a Unicode key; its schema/round-trip/order tests are still work to implement. Export formatting needs its own finite byte/item limits and must preserve completion semantics when refusing an export. Capture work limits do not cover arbitrary formatting or caller retention.

## Owner-driven capture and benchmark identification

Extend the future report capture options with an explicit state request and limits. The actual runtime/session factory obtains `CombinedCapture`; it does not accept arbitrary `Component`, `Stamp`, exactness flags or an independently paired workload snapshot. The joint handle already enforces same owner/committed epoch/plan/pending agreement. Report construction must also compare this boundary to its actual mode/session metadata. Preserve existing native Catalog/Query admission; matching JSON or a hash alone is not new authority. Session capture must use one session guard or an internal combined report seam, without recursively re-entering public guarded methods.

A report usable alone for benchmarks must expose **both** O07 and C01 instrumentation settings, even when one is off. C01 fields must include off/counters mode, deterministic period/offset, detailed-action cap, admitted cells/payload, actual reset/segment stamps and whether an explicit state scan was requested. O07 trace/timing options remain separately named. “O07 off” must never imply “all instrumentation off.” Current C01 reads no clocks and has no timed mode; any future timing must be declared independently. Historical reports must retain their original options and mode facts after reset, reconfiguration, mode switch and drop.

Keep the default v2 writer for existing consumers. The benchmark path should require the new report version whenever it enables C01, so it cannot produce an apparently self-contained v2 benchmark report that omits an active collector. No such CLI option, serializer or enforcement is implemented by this package.

Observed state/workload facts do not implement cost ranking. The proposed version must keep cost selection, estimated-state predictions, global cost optimality and structural proof authority separate. Keep the C01 project gate open until integration, required native matrices and measured overhead are accepted; availability of an isolated fact is not project completion. C02 remains open regardless of exact histogram availability.

## Concrete remaining changes and checks

1. Add immutable C01 ownership to the report data/factories and explicit capture/export options; retain compile-only/pending/released distinctions and strong allocation-failure behavior.
2. Add the new closed schema and version dispatch, typed scalar/key export, bounded JSON/human rendering and schema fixtures. Leave v2 fixtures and defaults unchanged. No replacement file is created by this inventory.
3. Add independent instrumentation identification to the versioned runtime/session report and the benchmark capture path. Actual modes/options must come from owners, not declared labels.
4. Add schema/semantic checks for pending state with current stamps, exact earlier components followed by exhaustion, foreign/rebuilt owners, reset without data change, mode segmentation without data change, deterministic sampled denominators, saturation, empty/non-applicable E and invalid byte strings. Check that serialization itself cannot promote unknown facts into exact ones.
5. Recompile/report-test both runtime variants after implementation, then run the required combined live-maintenance/completion/order/mode policy matrix and scalar/constraint/Boolean/disconnected/window coverage. Measure native-engine overhead and component memory separately from explicit scan/export costs, using identical outputs, workload/seed/build/hardware, repeated runs and dispersion. No measured overhead or S05 total-allocator claim is supplied here.
