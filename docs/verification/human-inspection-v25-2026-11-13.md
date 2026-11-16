# Human inspection V25 — 2026-11-13

V25 adds a tested [R2 transport foundation](w06-r2-records-2026-11-13.md) and
261 source-pinned usage contracts. The full Refactor goal remains active:
56 verified / 2 in progress / 20 not started, 78 total. W06 still requires actual
durable descriptor/checkpoint/files/coordinator/replay/CLI and varying-int32
admission. A02 licensing still blocks C04/B01 only.

The seal is `build/verification/human-inspection-v25-progress-v1.json`; frozen
source is `build/verification/human-inspection-v25-source-v1`. The root packet is
`build/verification/w06-r2-coordinator-implementation-v1`. V24 remains protected,
including its frozen source, evidence, private builds and SDK.

## Human contracts

The [inspection map](../code_specs/README.md) partitions 714 maintained code files,
166,049 lines and 18,681 blocks. It contains 13,536 scoped semantic contracts in
11,159 blocks. All 5,749 selected production scopes, examples and tools have
contracts; 2,478 selected existing-test scopes remain. Structural coverage is not
individual semantic certification of every line or all tests.

The additions are 163 existing observation/explain/JSON-cleanup/support-journal
test cards, 83 complete selected scopes across the new header/codec/WAL/test/
fixture generator, and 15 build cards. The build review updates one target-list
contract semantically and refreshes 1,359 unchanged-source-command hashes after
checking exact projections. Existing keyed objects and master order are retained.
No maintained source comment/diagnostic correction was required in these packets.
New code keeps usage/ownership comments beside the primitives and detailed
seven-field cards in the source pages, avoiding line-by-line comment duplication.

The final checker passes current source hashes, complete structural partitions,
anchors and 105,942 generated local links. The compact primitive index retains
every detailed contract in its linked source page. Current-guide local links and
fragments have a separate pinned audit; external URLs are skipped.

## Implementation and independent review

The new upper codec validates nullable complete physical rows and full grouping
keys, preserves absent tuple versus NULL cells, canonicalizes whole group epochs,
and checks W/I/C grammar with one pending identity and derived sink floor. It
owns one input frame plus flat arrays and one output frame. It adds no production
catch, retry/undo framework, native hot field or ordinary update-path work.

Root implements the code; Luna Max authors the scoped cards and build review.
A separate normal-model reviewer checks the actual protocol/APIs and stable
codec. Three local correctness findings are fixed before acceptance. All packet
payloads, source pre/postimages, seven fields, anchors and references are checked
independently before adoption. Advisory whole-registry drift from unrelated card
merges is recorded; target source/projection checks remain exact. No Astra call
is used in this continuation.

## Actual gates and limits

[Receiving evidence](w06-r2-records-2026-11-13.md) passes 10/10 selected strict
Debug tests and 10/10 full ASan/UBSan/leak tests, complete OFF Release, and the
entire copied codec test against the relocated 222-file SDK. Seven independent
Python byte goldens reproduce exactly. All 333 predecessor test commands and
properties remain except backtraces; 334 total are registered. All 20 existing
SDK archives are byte-identical to V24. No CPU timing, full334/Clang execution or
durable recovery acceptance is claimed.

All 23 recorder jobs are terminal, 19 successful, with zero in-command input drift;
four original setup/test failures are preserved. There are 1,157 final native
inputs: only two existing build files change, plus five new code files and seven
hex fixtures. Existing production source bytes remain unchanged.

The complete source/evidence hashes and separate packet-seal identities are in
the V25 seal and root `review-seal-pins-v1.json`. The [handoff](../handoff.md)
records the next actual APIs and protocol obligations. It preserves the distinction
between codec data, native admission and real file publication authority.
