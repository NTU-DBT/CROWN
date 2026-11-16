# V52: update-pattern runtime and human inspection

This is a bounded continuation of [V51](update-pattern-contracts-v51-2026-11-14.md),
not full X01 or Refactor acceptance. The ledger stays 60 verified, two in
progress (A02, X01), and 16 not started. Licensing/provenance still limits C04/B01
acceptance. Existing B05, V01/V02 and bounded W06 evidence retains its stated scope.

## Result and usage

QuerySession now admits source-bound declarations into its original account and
rejects violating commands before journal/native preparation. Plain typed and
stream input rejects every insertion-only erase command, including a set no-op.
Window input checks actual final-reference lifetime endings and explicit positive
joint FIFO scopes. Whole watermarks validate before any expiration effect.
Unrestricted window policy appends value 4; earlier values retain their meanings.

The implementation reuses existing counts/birth IDs, the Session semantic-error
latch and the existing catch/abort boundary. It adds no retained row mirror,
scope index, retry framework or runtime dependency on ranking. Declared watermark
simulation uses one query-funded integer vector. A flag collected during its
existing fill pass skips sorting unless the per-table baseline or live positive
scopes require grouping outside global physical order. Scoped explicit withdrawal
can still scan live counts; that actual cost is documented rather than called
constant time.

Committed diagnostics retain the exact declaration and actual current physical
program identity, separate command/physical origins and through-counters, insertion
policy and a scalar first violation. Immutable run context holds requested rules.
Current runtime selection requires an actual matching Session monitor; bare
runtime opt-in calls refuse. Measured plan replacement retains the declaration
and enforcement state while the reported tree identity changes.

Undeclared checkpoints retain state version 1 and its exact layout. Declared
version 2 adds bounded source/rule/origin/violation bytes. Inspection allocates no
rule scratch; receiving decode/import/copy uses original-account storage under
separate finite grants. Restored status explicitly assumes a trusted checkpoint;
checksums and a mutable checkpoint DTO do not prove historical enforcement.
See [usage and per-primitive costs](../update_patterns.md),
[checkpoint layout](../checkpoints.md) and [selection binding](../selection.md).

## Executed controls

Final exact-input Debug tests pass 15/15: monitor integration, native replay,
journal, session image, window/session checkpoints, run context, session
reoptimization, durable installation, measured selection, and five current
selection/cache/binding/resource controls. Final ASan/UBSan with leak detection
passes seven groups. The production Release build passes with BUILD_TESTING=OFF.
The final commands and all intermediate successes/failures are retained under
`build/verification/x01-runtime-monitor-*-v52-*.{json,log}`; receipt hashes distinguish
earlier source versions from final evidence.

The new test runs 560 seeded proposals against a separately implemented
lifetime-list model across reference/indexed backends and unrestricted/per-table
physical policies: 472 accepted and 88 rejected. It checks exact results,
progress and unchanged rejected prefixes. Duplicate lifetimes, independent scope
IDs, maximum raw scope ID, whole-watermark rejection, typed/stream no-op erases,
native/binary restore and actual current-selection rule binding have controls.

Healthy metadata-only watermark preparation has three measured C++ new denial
cuts; semantic rejection/error construction has five. Denial stays active through
cleanup. Every cut leaves committed window storage/account bytes unchanged and
does not latch a semantic violation; retry succeeds or produces the intended
semantic rejection. This seam does not intercept all libc/exception-runtime
allocation. The exact abstract watermark grant is 61; 60 refuses before effects.
Two 15-row grouped/interleaved unrestricted histories have equal counted work.
These are logical-work controls, not timing benchmarks.

Actual file/log reconstruction preserves a committed declaration and an input
without a durable decision. That input retries through the ordinary guard, and
a later forbidden lifetime termination changes neither log nor window prefix.
A real measured choice publishes a different tree through the existing durable
generation protocol; subsequent image restore still rejects its forbidden erase
and reports the installed physical identity. These are finite scenarios, not all
crash cuts or full migration/recovery acceptance.

Three owner-bound JSON examples (enforced, rejected, restored-rejected) pass the
complete Draft 2020-12 report schema. Native assertions additionally verify field
separation and omission for undeclared Sessions. The existing session-image test
retains its version-1 golden fixture.

## Review and block contracts

One Astra Max agent performed a bounded semantic review over pinned monitor,
window, binding and recovery sources, with zero open actionable findings. Its
full include/src context snapshot is not a review of every copied file. Root
separately received three later native successors: the allocation-free inspector
fix, source comments, and the no-FIFO sort skip. The first native test exposed
the inspector bug: constructing an allocator from the inspection-only empty
account failed even before vector allocation. Binding the allocator only for
materialization fixes that path; persistent zero-allocation inspection now passes.

Luna Max agents supplied the wire codec, 31 header usage cards and 40 test cards.
Root supplied 16 integration/API cards, amended 40 existing semantic contracts
and five shared documentation/routing contracts, and received each source-bound
successor explicitly. Header option cards distinguish value-copy cost from
actual admission; report-test cards distinguish selected native assertions from
separate full schema validation. No completed peer packet was rewritten.

The [block index](../code_specs/README.md) and
[primitive contracts](../code_specs/primitives.md) contain the final coverage.
Generation/checking validates every mapped source line, exact source/span hash,
contract attachment and generated local link. Comments and scope delimiters
have usage cards; whitespace-only regions keep structural descriptions. These
complete binding checks are distinct from scoped semantic reviews and finite
native tests.

## Limits and continuation

The [P4 source/proof audit](../update_patterns.md#paper-and-planner-boundary)
remains the source of lifetime/FIFO premises and the conservative transfer
argument. V51's constant/all-insertion/height-one/height-two sufficient fragment
is unchanged. Taller mixed-case characterization, broader SQL/alias/projection
transfer and full X01 acceptance remain open. Original P02/P07 evidence remains
the structural authority; no Trim/MixDetect result supplies a height certificate.
No new CPU maintenance, public delay, benchmark, full 352-test suite, Clang or
moved-SDK result is claimed.

The completed component packet is
`build/verification/update-pattern-runtime-v52-v1`. Entry, peer review, contract
receiving, schema, native receipts, coverage/link audit, source/evidence seal and
postcheck retain separate scopes. The [handoff](../handoff.md) identifies the
continuation boundary. The full goal and release gates remain open.
