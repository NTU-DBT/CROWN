# Genuine R2 descriptor admission

The [descriptor factories](../include/crown/recovery/sql_aggregate_descriptor.hpp)
retain original SQL binding, the actual native recipe, and original runtime
policies. `admit_into` constructs a genuine C0 aggregate runtime from a genuine
program and supplied tree/options. `rebind_into` reconstructs the program through
the real binder and creates a fresh C0 owner, then requires complete descriptor
byte equality. Neither factory selects a file root, imports physical rows, replays
a WAL, acknowledges output or establishes a minimum-height proof.

The [implementation](../src/recovery/sql_aggregate_descriptor.cpp) is a cold upper
component. It adds no field or ordinary update work to the existing source,
native or group runtime. The weighted aggregation context is P1 §7.3 in the
[corrected source map](code_review.md). Encoding, ownership, budgets and durability
boundaries are local engineering contracts, not paper theorems.

## What is authenticated

The actual compiler's immutable binding image already contains original SQL,
catalog, typed parameter declarations/values, source SQL/key, kernel/AVG scale,
nullable decode mapping, parser archive/version and static source weight. It is
retained exactly, rather than exporting an editable BoundSql/program DTO.

A second canonical CBOR object records format/arithmetic/output-policy versions,
the actual native tree and PhysicalOptions, full physical/source/weighted hashes
and multiplicity domain, and all original runtime options. Those options include
count/multiplicity limits, source/native/group work, capture flags and standalone
memory-option values. `_into` always uses its receiving account; stored standalone
memory values do not mint a new grant. Group change capture must be enabled.

On recovery, the factory reads original SQL/catalog/parameters/AVG from the binding
image and invokes `bind_sql_aggregate_into` under finite receiving compiler caps.
It requires exact factory binding-image equality before lowering. It then decodes
the stored recipe, admits lowering under finite receiving caps, constructs the actual
runtime with original options, regenerates the recipe from its real source
snapshot, and compares the whole frame. Claimed hashes, trees, decoder metadata,
policies and versions are data to check, not native import authority. A changed
parser/compiler binding must reproduce the exact bytes or fail admission.

## Wire and bounded parsing

`CROWNAD2` is separate from R1 descriptors and R2 row records. Its version1
envelope uses the [148-byte protected prefix/body layout](sql_aggregate_records.md#wire-contract).
The body is binding length8/binding bytes, then recipe length8/recipe bytes.
Lengths are unsigned little endian; hashes are lowercase ASCII SHA256. The
descriptor's root identity is the hash of the complete frame. Exact frames reject
trailing bytes.

Before either DOM is allocated, [the CBOR preflight](../src/recovery/sql_aggregate_cbor.hpp)
admits only definite minimal-width uint64/int64, string, array, map, Boolean and
NULL forms. It rejects indefinite values, byte strings, tags, floats, invalid
simple values, duplicate/unsorted map keys, bad key UTF8 and excessive sizes,
items, nesting or work. The maximum configured depth is256. Map order is the
factory's strict string-byte order, not an RFC length-first ordering.

String **values** remain bounded opaque bytes. Genuine factories retain opaque
catalog hint/untrusted-name bytes, so a blanket UTF8 check would narrow their
existing domain. Original SQL/TEXT/catalog use is instead revalidated by the real
factories; no escaping or replacement changes the stored image. Map keys are
fixed schema names in genuine images. Unknown/edited fields cannot survive exact
factory re-encoding and binding comparison.

Byte/work/scalar caps apply to the envelope and both CBOR components. Item counts
are shared across both components in each structural pass. Codec work is shared
through initial inspection, comparison, encoding, hashing and final comparison;
there is no per-phase refill. Schema caps bound original table/column counts and
group/output widths. No physical source rows are stored in a descriptor, so its
row statistic is zero. Compiler/DOM and tree workspace use the existing ordinary
compiler conventions; retained program/native metadata, descriptor bytes and
runtime state use the receiving account. Codec counters do not measure compiler
CPU or all allocator work.

## Ownership, failure and cost

`Descriptor` shares immutable account-owned metadata and exact bytes; borrowed
views require a surviving handle. Its native program and weighted binding come
from the actual newly created runtime. A caller cannot construct it from an
edited descriptor DTO. `Admitted` returns that descriptor, the move-only runtime
and codec statistics. Output ownership survives source byte/program-owner death.

Inspection uses fixed/borrowed storage and no covered C++ allocation. Malformed
wire and limits use fixed ImageFailure. Cold JSON/compiler/schema exceptions and
account failures propagate; there is no added production catch or retry/undo
framework. Owning values release incomplete admission on failure. No native
owner is exposed until exact binding/recipe checks finish.

A finite receiving binder grant can refuse valid descriptor bytes. Its
`resource_limit` diagnostic becomes `ImageFailure(ImageFault::work)`; semantic
binding diagnostics become `ImageFailure(ImageFault::binding)`. The receiving
account returns to its prior retained state on either failure.

Host lowering/identity grants are finite and distinct from original producer
PhysicalOptions, which may have disabled compiler counters. If both original
compiler caps are finite and within the receiving caps, actual construction is
already bounded and there is one lowering pass. Otherwise the factory performs
one finite host lowering pass and discards it, then the existing runtime lowers
the same deterministic input using unchanged original options. This adds a cold
validation pass only when required; there is no per-row check or altered-policy
graph cache. Original policies remain intact. Binder source/AST/expression/
recursion/work limits remain separate and finite at this boundary.

Wire operations are linear in admitted bytes/items plus map-key comparison
extents, with stack depth bounded by the configured maximum. Cold binding/tree/
runtime construction has its actual separate compiler costs; this guide claims
no constant admission cost or portable CPU bound. A valid supplied tree provides
an upper height bound. Strict minimum claims require genuine planner evidence.

## Selected checkpoint bytes

The private [GenerationOwner](../src/recovery/generation_detail.hpp) now exposes
`read_checkpoint(account)` alongside `read_plan(account)`. Both delegate to one
direct selected-file reader: root-before check, own nofollow file open, regular
type/size admission, cumulative work before receiving allocation, complete read,
EOF/stamp/hash validation, checked close, root-after check. Checkpoint and plan
use their own caps/hashes/paths. The lower publisher permits empty opaque
checkpoint payloads, so the reader preserves that domain; actual image decoding
must separately reject an invalid/empty image.

This port retains the actual root lock and returns funded opaque bytes. It does
not authorize SQL/source reconstruction or impose R2 root semantics. The upper
[R2 Session](sql_aggregate_session.md) requires a v3 descriptor hash, C≤I, actual
D=C checkpoint delivery coverage and no R1 retirement intent, then validates the
selected checkpoint/WAL/sink and genuine replay before any tail repair.
See [cold source reconstruction](sql_source_images.md)
and [R2 records](sql_aggregate_records.md) for the adjoining contracts.

The [descriptor test](../tests/unit/sql_aggregate_descriptor_test.cpp) and
[opaque read test](../tests/unit/generation_opaque_test.cpp) specify focused checks.
Their execution evidence is maintained separately; existence alone is not a
durable recovery or full release claim.
