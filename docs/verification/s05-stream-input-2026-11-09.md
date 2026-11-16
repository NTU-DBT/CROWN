# S05 native streaming input ownership — 9 November 2026

Status: **in progress**. Ledger41 verified /3 in progress /34 not started and the
full78-card Refactor.md goal remain active. Root implemented this cohort; one
Luna Max agent performed read-only caller and remaining-owner census. No Astra
was used. Continue with root for most work and reserve Astra Max sparingly.
Artifacts: `build/verification/s05-stream-input-*`.

## Real retained ownership

QuerySession constructs EventReader from its admitted CompiledProgram. The plan
bridge supplies the program's existing finite account and immutable catalog
alias without a core-to-plan link. Actual reader control, immutable option
control/map nodes/key/source/null bytes, funded catalog fingerprint serialization,
framing capacity, JSON tokens/metadata/column scratch, binary/delimited fields,
CSV header permutations, compact cached rows and source text all consume that
grant. AccountedInputOptions is shared with the funded SessionRunContext, whose
copy retains that storage without allocating. No ordinary operational Row/JSON
DOM/string/map shadow or fresh execution allowance is retained.

Native JSON uses the bounded event schema, UTF-8/escape/surrogate handling and
exact integer token rules; decimal coefficients parse inline. SHA-256 has a fixed
output path; its existing public string wrapper uses the same compression.
Canonical catalog output uses real funded capacity. Table lookup borrows the
already admitted immutable catalog, avoiding ordinary revalidation scratch.
The public owning DTO/SAX and binary codecs remain compatibility references;
canonical writer/SHA mechanics are shared. Malformed native JSON syntax uses
stable invalid_document text instead of third-party exception internals. Schema,
row/domain/binding/option/limit/source codes and ordering retain their contracts.

EventReader/OrderedReplay peek returns a stable InputEventView. Only explicit
acknowledgement publishes prepared source nodes/scalars and advances sequence.
Reader parse/order/allocation failures remain sticky; correction requires explicit
recreation. Engine rejection retains the cached event. Ack, commit, native
close and session stop allocate nothing. Value progress snapshots clone under
the original grant and native stopped progress survives reader/runtime destruction.
Public session progress/snapshot DTOs and AccountedInputOptions.export_value are
explicit caller exports. Native option fields are accessed through get().
OrderedReplay shell uses the reader account and applies native physical/delta
views, with a funded catalog-binding fingerprint. Standalone CatalogSource reader
construction is an explicit compiler/external adapter with its own account;
actual sessions use genuine CompiledProgram authority.

## Verification scope and source history

Prepared source1–3 syntax receipts precede the source move; source4 integrates
native API/session/replay/options. Source5 adapts one native string-view test
accessor and passes8 existing checks in0.96s. Source6 adds the actual memory test;
it detects real ordinary catalog-validation scratch during table lookup. Source7
fixes that ownership leak and passes the new check in3.34s. Source8 changes only
one existing composed-report test caller and freezes946 paths. Its full Debug
run passes213/214, exposing CLI native-map serialization as an array instead of
the required object. Source9 changes ONLY apps/crown/main.cpp to export native
accepted progress as a caller DTO at serialization. Every native library/test/
verifier/fixture file remains byte-identical to source8. Final source10 changes
documentation only, for947 paths.

| Configuration | Completed exact source scopes |
| --- | --- |
| GCC Debug |Source9 full214/214, 892.96s; CLI16/16, 49.73s |
| GCC Release |Source8 native40/40, 16.31s; source9 CLI16/16, 8.26s |
| Clang18 Debug |Source8 native40/40, 99.21s; source9 CLI16/16, 36.41s |
| ASan+UBSan/leaks |Source8 native40/40, 550.31s; source9 CLI16/16, 199.29s |

Source8 builds all Debug targets and the other modes' selected40. Source9
rebuilds the CLI in all four modes; final Debug reruns the complete suite, and
all16 CLI-dependent checks pass separately in every mode. No native library or
test code changes after source8.
Accepted final builds have zero compiler diagnostics. Detailed stdout is saved
before any subsequent CTest registration/run, without enumeration overlap.
All39 recorded jobs are closed. Progress-v2 binds sources/raw
attempts/current native executables/scope audit/handoff. These are scoped results;
full native compiler/sanitizer/fresh-source acceptance remains separately open.

The actual stream_input_memory test covers both backends and all8 profiles with
five scalar types,38-digit decimals, long binary/UTF-8 strings, source IDs,
relation/null tokens, CSV header permutation and quoted embedded newlines. Caller
DTOs/streams are prepared outside the measured operation. Constructor, decode,
source preparation and progress-copy upstream calls reconcile with successful
original-account requests. Cached peek, commit/ack/close/stop and option copies
pass persistent allocation prohibition. Exact/one-under original query caps,
caller-visible accepted prefix, smaller same-sequence explicit recreation,
constructor/peek persistent failures, retained native options/progress and final
controller-only release pass. Fixture values below are Debug source7 measurements,
not universal peaks; constructor/peek fault counts are the same for both backends.

| Format | Query peak reference / indexed bytes | Constructor / peek fault positions per backend |
| --- | --- | --- |
| jsonl | 817523 / 817887 | 10 / 33 |
| binary | 423971 / 424335 | 10 / 13 |
| csv | 423777 / 424141 | 12 / 38 |
| legacy_signed | 423604 / 423968 | 12 / 25 |
| legacy_relations | 424067 / 424431 | 14 / 26 |
| legacy_insert_only | 423642 / 424006 | 12 / 24 |
| legacy_flags | 423604 / 423968 | 12 / 25 |
| legacy_timestamp_flags | 423596 / 423960 | 12 / 26 |

Nineteen directed JSON cases per backend compare native/public values or error
codes, including arbitrary field order, BOM, Unicode escapes/surrogates, binary
string bytes, exact scalar limits and malformed schema. An independent Debug
harness compares12007 deterministic documents/byte mutations with the public SAX
codec:308 accepted and11699 rejected, zero code/value differences and zero native
storage drift after every case. It does not prove all possible documents or
third-party syntax-message identity.

The CLI fixture schema/verifier stays unchanged: source9 explicitly exports
progress as a DTO and preserves the required object-shaped source_positions.
All source8 non-CLI binaries stay byte-identical after the CLI-only rebuild.
Five old tests contain only8 boundary type/export adapters. Whole-file
reconstruction preserves every other byte, assertion and independent expected
algorithm. Raw include/header/style/private-access/native-caller compile failures,
the actual catalog-scratch memory failure, source8 CLI object/array fixture failure
and all source preimages remain
immutable. No flag, timeout, schema, frozen CLI/report verifier or old receipt is
weakened. Automatic review rejected an initial intermediate removal before the
replacement was complete; the complete replacement then passed strict syntax,
and the old reader was preserved before the verified source move.

## Remaining whole-goal work

Operational ObservationState shared control/trace capacity and workload State/
Collector route/descriptor/committed/attempt/previous/configure arrays remain
ordinary. Retained cursor/configuration/summary state is fixed data or funded
aliases; it must not be mislabeled as owning strings. The capture shell is funded,
but retained trace/combined/owner/workload/report/evidence payloads require their
own ownership disposition and funding. Explicit caller diagnostic DTOs are a
separate boundary. Asynchronous/invariant/diagnostic scratch, authentic operator
record/byte reconciliation and complete overflow/no-op/churn/compiler/sanitizer/
fresh-source native matrices remain open. The focused next-owner census is not
exhaustive acceptance. S05 and whole-query memory acceptance remain **false**.
See [handoff](../handoff.md), [ingestion](../ingestion.md),
[memory contract](../memory_accounts.md) and [ledger](../task_ledger.md).
