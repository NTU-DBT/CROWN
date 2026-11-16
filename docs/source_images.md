# Accounted physical source images

The [V71 acceptance](verification/general-query-fallback-v71-2026-11-16.md)
records source review and actual Release/ASan/UBSan checks for this bridge and
the explicit fallback owner.

`PhysicalRuntime::source_image()` returns native owning full-source data.
`PendingUpdate::source_image()` returns the private after-state after all alias
routes drain, using that token's existing indexed operation lease. Rows include
unused tables, in catalog table order; row order follows the storage backend.
Each table vector, tuple and string payload retains the original query account.
The image survives source rollback and runtime teardown. Its public program is
source-schema metadata, not an original-query answer or checkpoint authority.

One `SourceImageLimits` balance bounds table/row/field and payload-byte visits;
the row limit counts all physical rows. Pointer capacity and tuple copies also
spend the original indexed operation's five-domain allowance. Repeated captures
inside one pending token never replenish that indexed lease. The changed table
uses its journal cursor; unchanged tables use ordinary live cursors. Payload work
is admitted before each deep clone. No ordinary Database/string export or sort
is hidden in this operation.

A failed capture leaves an active pending token available for rollback. All
cursors and private partial images retire before failure escapes. Native index
and memory failures retain their resource categories. Calls on the owner must
be externally serialized, as with its other source operations. The fallback
wrapper additionally guards its own source/result publication and retirement.
