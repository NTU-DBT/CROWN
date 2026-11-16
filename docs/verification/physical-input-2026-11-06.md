# O01 physical input and ordered replay, 2026-11-06

Input: uncommitted `master` based on
`e369a623517723b3be3ea3e9806779f3c591e7f9`.
O01 is implemented and verified. Independent Astra source review and all
69 tests pass the final five-configuration matrix for frozen sources.
The complete 78-card goal remains active: 29 verified, four in progress
(A02/P04/P06/O06), 45 not started. No session, recovery or release gate is
inferred from input-codec acceptance.

Contract: [physical input and replay](../ingestion.md),
[F01 catalog/scalars](../catalog.md), [physical runtime](../physical_runtime.md)
and [D06 output lifecycle](../delta_lifecycle.md).
Sources: [input API](../../include/crown/io/ingest.hpp),
[wire/reader implementation](../../src/io/ingest.cpp),
[text parser](../../src/io/ingest_text.cpp),
[replay API](../../include/crown/runtime/replay.hpp) and
[replay implementation](../../src/runtime/replay.cpp).
The [D06 packet](delta-lifecycle-2026-11-06.md) and its 484-input manifest
remain historical and have not been resealed.

## O01 requirement audit

| Obligation | Evidence and scope |
| --- | --- |
| JSONL and binary update codecs | Strict independently versioned full-row physical events bind catalog version, source-schema version and complete canonical catalog SHA-256. Exact int64/string/bool/date/decimal domains, literal insert/delete, table case and optional source positions are preserved. Binary wire tags and little-endian framing are explicit, without ABI/pointer serialization. |
| Schema-aware CSV | Exact complete source-column headers may be permuted; headerless input uses schema order. Explicit delimiter, sign/operation and NULL-marker policy; quoted separators/newlines, doubled quotes, CRLF and final EOF records are handled. Missing/extra columns, invalid syntax/types and unsupported NULL fail. Unused query columns remain part of physical row identity. |
| Explicit legacy adapters | Signed, relation-token, insert-only, flag-first and timestamp/flag profiles have separate configuration. Relation tokens require exact mappings. Timestamp/flag input requires a source ID and retains the unsigned timestamp as its offset. Literal flags/signs are preserved, and `*` control records fail explicitly. The known TwoComb converter sign bug is documented rather than repaired by guessing. |
| Sequence and source-position validation | Stream sequences are contiguous after accepted progress. Per-source offsets strictly increase; zero, gaps and interleaving sources are supported. Duplicate/backward positions, gaps/repeated engine sequences and uint64 exhaustion fail. Initial progress is caller-supplied, not a checkpoint importer. |
| Malformed rows cannot partially mutate state | Reader parsing/order checks and source-map node preparation precede engine work. Parse/allocation failure is sticky without accepted-progress changes. Engine rejection retains the cached event/progress for same-sequence retry. Existing physical/source/count/kernel/live transactions roll back atomically. A valid acknowledgement allocates nothing and throws nothing after engine commit. |
| Deterministic ordered replay | `OrderedReplay` binds one runtime owner and exact catalog, requires readiness and matching progress, then applies one event and acknowledges commitment. Physical no-ops still commit the sequence/position. Repeated ordered input has the same epoch sequence; native delta replay matches independent A04 before/after differences without duplicate raw emissions. |
| Bounded ownership and diagnostics | One raw/decoded record plus bounded field/source metadata is retained. Record, field, source, source-count, column, record-count and optional total-byte limits are explicit. JSON SAX/direct encoding avoid allocating DOM teardown under persistent OOM. The CLI validates to EOF and emits one successful summary only after the whole stream passes. |

The envelope's full catalog fingerprint deliberately includes constraints,
statistics and hints. It is stricter than semantic query identity. Codec
progress records accepted input, while byte/decoded-record counters can include
lookahead or an unacknowledged record. Those counters do not define a durable
resume point or retain CSV header/decoder state.

## Independent fixtures and failure evidence

[Semantic cases](../../tests/unit/ingest_test.cpp) independently construct JSON
and binary bytes, check rich canonical catalog hashing against the F01 writer,
and exercise all scalar domains, UTF-8/NUL, int64/uint64 boundaries and framing
budgets. Negative cases cover duplicate/unknown JSON keys, null/floating tokens,
wrong versions/bindings/types/arity, binary tags/flags/truncation/trailing data,
source order, scoped configuration and all text profiles.

The eight-event full-row self-join fixture keeps different unused payloads
distinct while their projected alias derivation counts rise/fall independently.
It checks physical endpoints, set no-ops, invariant inspection and contiguous
epochs. Delta replay checks each raw signed output against A04 before/after
evaluation, including projection-count-only empty deltas. Owner/catalog/busy
barriers and later malformed records preserve the already committed prefix.

[Failure cases](../../tests/unit/ingest_exception_test.cpp) keep allocation
failure armed through rollback and teardown. Final Debug positions:

| Operation | Persistent allocation failures before success |
| --- | --- |
| Reader construction, JSONL / binary / CSV | 18 / 18 / 18 |
| Reader peek, JSONL / binary / CSV | 33 / 15 / 10 |
| Cached physical replay application | 79 |
| Cached delta replay application | 122 |

Additional sweeps cover canonical catalog hashing and both stateless readers/
writers. No-allocation checks cover acknowledgement of new/existing sources,
cached reader moves/destruction and replay teardown. Source pins, persistent
parse failures, late binary truncation, output-busy rejection and later-alias
quota rollback preserve state/progress and permit the documented retry.

A sparse replay fixture seeds 900 rows away from an arena capacity boundary
and checks that one input does not allocate a database-sized row copy. It does
not prove a uniform per-update allocation bound: arena high-water metadata
may grow geometrically, and constraint validation has its own state scans.
Record bounds also exclude catalog/configuration ownership, allocator slack,
external stream buffers and caller output. JSON lexer scratch may reach the
record cap before a narrower string-field acceptance check.

[CLI fixtures](../../tests/integration/ingest.py) pass 23 valid-format and
rejection checks, computing the canonical catalog SHA independently in Python.
The optimized-Python invocation also passes all 23 checks. The final Release
schema audit passes 19 meta, 26 normalized, 19 identity, 59 admission, two
layout/projection, 31 physical, three support, two rejected-report and two
physical-input artifacts.

Luna Max authored semantic/oracle cases, persistent-failure cases, text parsing,
CLI fixtures/integration and entry documentation in separate assignments.
Root integrated the wire/reader/replay implementation and acceptance evidence.
Astra architecture review prompted strict rejection of unrelated format options
and symmetric LF/CRLF JSON object budgets; both are covered by tests. A fresh
read-only Astra review found no O01 blocker in the actual source/tests. Its
nonblocking table-name field-limit clarification is in the contract. Neither
reviewer ran builds or claimed an external audit or downstream O-card signoff.

## Matrix and source identity

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3 Debug | 69/69 pass | 115.26 s |
| GCC 13.3 Release | 69/69 pass | 13.98 s |
| ASan/UBSan, including parser C | 69/69 pass | 518.37 s |
| Clang 18.1.3 C/C++ Debug | 69/69 pass | 86.63 s |
| Fresh source-only Release | 69/69 pass | 13.60 s |

Frozen native/test fingerprint:
`020f68924794d46873572b378f9bf139c92adc049e8576c9c93720546073ea9b`
(412 inputs). It uses the prior sorted-path/NUL/content/NUL definition over
CMake files and include/src/apps/tests/cmake, excluding Python caches. No
native source changed during the final matrix. The
[495-input manifest](physical-input-sources.sha256) adds nine native/test files,
one schema and the input contract to D06's 484 inputs. Verification
packets/manifests, handoff and ledger are excluded.
Manifest SHA-256:
`394ea5788f1d2dd41a465f8cc591c6e8d535fdff421c8887f1ca14255119fb6d`.

Raw CTest output, configure/build/test logs and per-configuration summaries
are retained under ignored `build/verification/physical-input-*`. Clean
verification took 309.87 s overall and removed
`/tmp/crown-clean-source-eua6979l`. All final processes are terminal/successful.
All four in-place runs record identical before/after source fingerprints. Each retains
five D04 oracle invocations: 2,712 updates, 1,408 raw records and 2,504 exhaustive
toggles per policy/strategy. D05 N=2/64 maxima remain insert 69/63/10 and erase
62/77/10, with explicit growing preparation/finalization costs.

Refactor.md remains byte-identical, SHA-256
`bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce`.
D06's historical 484-input manifest retains SHA-256
`3300aa4d412930322bbbeb74fe88b0ec3be78586794616cc226d1d67545e1665`.

Independent `sha256sum -c` passes all 495 inputs; all 147 checked local
Markdown destinations exist. The provenance review found stale ledger footer
counts/next-task prose; those now match its 78-row table and this packet.
The aggregate and full hash-check output are retained under
`build/verification/physical-input-*`.

```sh
cmake --preset debug
cmake --build --preset debug --parallel 2
ctest --preset debug --output-on-failure
cmake --preset release
cmake --build --preset release --parallel 2
ctest --preset release --output-on-failure
cmake --preset sanitize
cmake --build --preset sanitize --parallel 2
ctest --preset sanitize --output-on-failure
cmake -S . -B build/clang-debug
cmake --build build/clang-debug --parallel 2
ctest --test-dir build/clang-debug --output-on-failure
python3 -O tests/integration/ingest.py build/release/crown .
python3 tools/verify_schemas.py build/release/crown
python3 tools/verify_clean_build.py --configuration Release --parallel 2 --log build/verification/physical-input-clean-source.log
sha256sum -c docs/verification/physical-input-sources.sha256
```

O02 session ownership is the next enabled dependency. R06/S05 remain necessary
for O04 checkpoints, and O05/O06 must establish WAL/recovery/delivery semantics.
The O01 diagnostic is not O08's session/streaming CLI. No all-or-nothing file
batch, durable/exactly-once sink or recovery guarantee is claimed. The entire
78-card implementation goal remains active.
