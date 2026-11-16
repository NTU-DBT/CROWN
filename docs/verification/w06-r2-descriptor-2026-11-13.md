# W06 genuine descriptor and opaque checkpoint reads — 2026-11-13

The [genuine descriptor factories](../sql_aggregate_descriptor.md) and selected
opaque checkpoint read port now have scoped receiving evidence. Durable R2
physical checkpoint format, actual WAL/sink owners, coordinator, genuine WAL
replay/crash recovery, nullable JSONL/CLI and varying-int32 admission remain open.
W06 and the full implementation goal stay in progress.

## Implemented behavior

CROWNAD2 version1 retains exact factory binding CBOR and a regenerated actual
native recipe, including original SQL/catalog/typed parameters/AVG, nullable
decode identity, parser/compiler identity, native tree/options/full weighted
binding and original operational policies. A bounded allocation-free structural
pass precedes both cold DOMs. Rebinding uses the actual SQL factory, compares
exact binding bytes, constructs a genuine C0 runtime, then compares the entire
regenerated frame. Edited DTOs or stored proof claims are not import authority.
Opaque catalog metadata bytes survive without escaping or replacement.

Both lowering/identity host counters are finite. A pair of finite producer caps
already within them bounds actual construction directly; otherwise one extra
finite host lowering pass checks the same input before original-policy runtime
construction. No policy is silently clamped, disabled producer limits remain
bound, and no altered-policy graph is retained. Codec work spans all wire passes
and comparisons. Ordinary compiler/DOM workspace has its separate limits.

GenerationOwner::read_plan and new read_checkpoint share one direct selected
reader. It retains actual root lock ownership, separate file caps/hash/path,
root-before/after, nofollow/regular-file, bounded allocation, EOF/stamp/hash and
checked-close protections. Lower opaque checkpoint bytes may be empty; a later
image decoder is responsible for image validity. The adapter still must enforce
R2 v3 descriptor/actual D=C anchor and C≤I semantics.

There is no new production catch, native hot field, row mirror or retry/undo
framework. Immutable descriptor/control/bytes and actual metadata use the
receiving account. Native admission and file publication remain separate.

## Actual gates

| Receiving gate | Result |
| --- | --- |
| Strict GCC C++23 Debug | Final selected 8/8; 23.00s |
| Full ASan/UBSan/leak profile | Final same 8/8; 54.33s |
| Complete OFF Release | Pass after explicit optional construction repair |
| Relocated 223-file SDK | Full copied descriptor test passes under strict Release |
| Additional installed public consumer | NULL parameter, static0/1, original owner released, input bytes destroyed, next filtered/unused physical epoch pass |
| Registration continuity | All previous 334 commands/properties exact except backtraces; 336 total |
| Existing archives/object code | 19 archives unchanged; runtime archive changes only generation.cpp.o, other 28 objects unchanged |

The selected tests are generation, reoptimization generation/descriptor, SQL
aggregate runtime/rebuild/records and the two new tests. Their selected binaries
were freshly linked against current libraries before regression execution.
The descriptor test covers both backends, actual nullable next output, exact
binding/native/options, opaque hint bytes, original disabled producer counters,
exact/one-under codec/receiving caps, hostile/checksum-valid metadata, all cuts/
bit flips of an independent 166-byte framing golden, and malformed/deep/huge CBOR.
The framing golden contains empty maps and is not semantic admission evidence;
actual program reconstruction is tested separately through genuine factories.

The opaque read test covers complete binary/empty payloads, actual plan/checkpoint
binding, receiving caps and cumulative I/O/work boundaries, all observed read
syscall positions with both error sides, short transfers, changed/appended/root
bytes, malformed selected payloads, nofollow symlink and nonregular-file rejection.
Failed reads release their funded payload/FDs and do not repair selected files.
The C++ new hook does not observe libc or exception-ABI allocation. No all-336,
Clang, CPU timing or durable R2 recovery acceptance is claimed.

## Evidence

The root packet is `build/verification/w06-r2-descriptor-implementation-v1`.
It contains receiving acceptance, final input cohorts, registration comparison,
SDK/archive comparison, source scope, original failure logs, and exact comment
correction proof. All 27 recorder jobs are terminal, 23 successful, with zero
in-command input drift. Four compiler/setup failures are preserved: a new loop's
misleading indentation, an unnecessary heavy test fixture include, a test guard's
indentation, and GCC13's optimized conditional-optional warning. Direct branches
and the existing lightweight fixture resolve them without suppression/handlers.

Final native input count is 1,163. Existing changes are CMake, the two private
generation files and one catalog-test docstring. Five new code files and one hex
golden are added. The docstring now names metadata's types/nullability/constraints/
ordering use; non-docstring AST is identical. The main code and actual ordinary
update object bytes remain unchanged. The archive comparison is not a CPU result.

Independent static review is sealed at
`build/verification/w06-r2-descriptor-review-v1`, manifest SHA256
`b60befbc3bf1187c12a4b6832342622890756accf716500363bc0555bbff61fe`.
Its preserved source predates the final compiler/fast-path refinement; the
3-file amendment is `w06-r2-descriptor-review-v1-amendment1`, manifest SHA256
`9f368a38cbd3dbe203923fcd544c892fc6fb51d9f9b5263fd8fd78ff7ef4d12e`.
No outstanding scoped finding remains. The reviewer did not execute native tests.
P1 §7.3 is weighted context only; see [the corrected source map](../code_review.md).
