# C01 online owner integration boundaries — 2026-11-07

**Read-only native inspection; no hook integration or native execution claim.**
The accepted isolated collector needs the following owner adaptation before
it can represent actual runtime transactions. Preserve its frozen packages.

1. Delta outer admission precedes the physical changed/no-op fact. In
   `src/runtime/delta.cpp`, PendingEpoch::Data opens its outer context before
   `physical.begin_staged(update)`. In `src/runtime/physical.cpp`, Data::prepare
   discovers changed/no-op from the already validated source membership test.
   The collector's current `begin(descriptor, changed)` cannot receive an
   invented fact at the earlier delta boundary. A later revision can separate
   root admission from one nonallocating actual physical-fact staging hook,
   retaining the existing overload for standalone physical owners.
2. Physical and support commit are nested. Only final outer delta success may
   publish committed workload totals. Physical abort, late delta stage/spool/
   live failure and caller cancellation must discard the same scratch sample.
   A nested success cannot close the root ticket. Nonthrowing public commit
   must remain nonthrowing with the collector enabled and an allocator that
   rejects every request.
3. Lower-only SupportRuntime has native input epochs, not physical base-table
   inputs. Its initiating scope needs a logical-only root identity; source
   cardinality and physical denominators stay unavailable. Do not manufacture a
   catalog table/op descriptor solely to fit the current isolated API.
4. Optional O07 observation can be off. C01 descriptor ownership, epoch/reset
   stamps and successful semantic-mode segmentation cannot depend on an O07
   observer existing or on allocating transition capture. Failed/no-op mode
   switches preserve the workload segment; successful switches rotate it once.
5. Native support counter hooks use actual before/after values in the existing
   counter mutation path. Positive-to-positive support changes count even
   without P/E membership transitions. Child touched degrees use the actual
   already-computed matching bucket length once per applied child-key event;
   multiple events remain multiple observations. Generalized probes have their
   own scope and cannot be called native reverse-index degrees.
6. Data freshness uses actual owner, owning plan and committed epoch, not the
   storage cursor revision. Rollback can advance revision without committing.
   Bootstrap/rebuild work starts a new owner/stream interval, and ordinary
   stream hooks must remain suppressed during unpublished initialization.

Committed event fractions have an explicit physical-input denominator. They do
not supply arrival events per second. Per-second rates remain unavailable
without an explicit measured interval; no processing or sink callback latency
can stand in for upstream arrival time. Counters/off collection reads no clocks.

Required future tests include real nested rollback after nonzero scratch,
failed/no-op/successful mode switches with O07 disabled, lower-only scope,
bootstrap suppression, no-op inputs, same-owner allocation-failure recovery,
pending/committed unread output, move/drop, historical owning report lifetime,
and semantic parity with all instrumentation off. The component microbenchmark
is not evidence for engine-wide update overhead or rollback correctness.
