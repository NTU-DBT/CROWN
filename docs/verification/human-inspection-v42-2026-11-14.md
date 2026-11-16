# V42 — public declaration usage specifications

V42 adds **39 scoped declaration/alias cards in 20 public headers**, covering
305 previously structural source lines. The [source index](../code_specs/README.md)
now has **16,648 contracts in 14,232 blocks**, across 751 files /172,040 lines /
19,412 blocks. Selected callable/type/inline-cluster gaps remain zero. The exact
structural remainder is **5,180 blocks in 691
files /15,798 lines**; it is checked as the previous remainder minus these 39 IDs.
Card scope follows its anchor, not blanket certification of neighboring comments.

| Source | New cards |
| --- | ---: |
| [ranking.hpp](../code_specs/files/include/crown/planner/ranking.hpp.md) | 1 |
| [recognize.hpp](../code_specs/files/include/crown/planner/recognize.hpp.md) | 2 |
| [selection.hpp](../code_specs/files/include/crown/planner/selection.hpp.md) | 1 |
| [verify.hpp](../code_specs/files/include/crown/planner/verify.hpp.md) | 1 |
| [aggregate.hpp](../code_specs/files/include/crown/runtime/aggregate.hpp.md) | 1 |
| [program_aliases.hpp](../code_specs/files/include/crown/runtime/program_aliases.hpp.md) | 1 |
| [sql_rows.hpp](../code_specs/files/include/crown/runtime/sql_rows.hpp.md) | 3 |
| [accounted_index_work.hpp](../code_specs/files/include/crown/storage/accounted_index_work.hpp.md) | 4 |
| [accounted_indexed.hpp](../code_specs/files/include/crown/storage/accounted_indexed.hpp.md) | 1 |
| [accounted_layout.hpp](../code_specs/files/include/crown/storage/accounted_layout.hpp.md) | 4 |
| [accounted_projection.hpp](../code_specs/files/include/crown/storage/accounted_projection.hpp.md) | 2 |
| [accounted_reference.hpp](../code_specs/files/include/crown/storage/accounted_reference.hpp.md) | 3 |
| [accounted_row.hpp](../code_specs/files/include/crown/storage/accounted_row.hpp.md) | 3 |
| [arena.hpp](../code_specs/files/include/crown/storage/arena.hpp.md) | 2 |
| [index_failure.hpp](../code_specs/files/include/crown/storage/index_failure.hpp.md) | 1 |
| [index_work.hpp](../code_specs/files/include/crown/storage/index_work.hpp.md) | 3 |
| [indexed.hpp](../code_specs/files/include/crown/storage/indexed.hpp.md) | 1 |
| [layout.hpp](../code_specs/files/include/crown/storage/layout.hpp.md) | 2 |
| [reference.hpp](../code_specs/files/include/crown/storage/reference.hpp.md) | 2 |
| [table.hpp](../code_specs/files/include/crown/storage/table.hpp.md) | 1 |

## Source and design findings

Declarations select names, types, access, storage and allowed expressions; they
do not execute an operation merely by appearing in a header. Cards distinguish
those effects from the validation, allocation, iteration and cleanup of actual
calls. [Paper/design context](../code_review.md) remains separate from engineering
lifetime and failure rules. A namespace alias, public DTO or success report
cannot supply a minimum-proof, fresh-owner or durable-publication guarantee.

The work-grant union stores either its canonical balance or a borrowed root
pointer. Diagnostic aliases do not copy/refill a grant; alias-of-alias is rejected
by the existing terminating invariant check. Accounted handles share the same
mutable allowance and provide no synchronization. The fixed IndexFailure carrier
owns an enum rather than dynamic diagnostic text; throwing can still use exception
runtime storage. No guard is removed merely to reduce the count of error paths.

Deleted rvalue overloads reject direct temporary-owner borrows on the accounted
APIs. Legacy arena/table layout getters are unqualified and still require caller
lifetime discipline. Shared and unique data members retain their actual payload
owners; final release can perform cleanup. Vector aliases preserve allocator
semantics rather than creating a fresh budget. Snapshot/rebuild/diagnostic walks
and the private prepare/commit lifetime remain explicit in the relevant cards.

## Review and verification scope

One Luna Max author and a separate Luna Max peer review all seven fields. Root
reads every selected range (305 lines) with adjacent context, targeted backing
implementations and the final fields; root does not claim rereading all complete
20 headers. Exact replay checks 39 peer amendments plus
3 root amendments. Source geometry, unique anchors, the
original missing set and all 16,609 older registry entries are preserved.
Thirty-five author declaration labels are separately reconciled to the exact
frozen block-signature metadata; all seven semantic fields stay unchanged by
that normalization, and the sealed author payload is preserved.

All **1,196 native inputs and 355 production paths equal V41 byte for byte**.
There is no native build, CTest, SDK, benchmark or release run in V42, and no
runtime handler, wrapper, allocation, branch or checkpoint is added. V41's actual
strict affected Debug/SAN backend-binding results retain their dated attribution.
Completed map and current-guide checks validate local references, with external
URLs explicitly skipped. The [receiving packet](../../build/verification/inspection-public-declarations-v42-v1/README.md)
pins both immutable reviews and the final exact structural remainder.

Latest seal: build/verification/human-inspection-v42-progress-v1.json; frozen
source: build/verification/human-inspection-v42-source-v1. Exact prior handoff:
[V41 history](../handoff-history-v41-2026-11-14.md). The full goal remains active:
**57 verified /1 in progress A02 /20 not started**. W06 retains its bounded profile;
A02/C04/B01, R2 retirement, V04 and release gates remain open.
