# V43 — wire and IR declaration usage specifications

V43 adds **46 scoped wire/IR declaration cards in 31 public headers**, covering
393 previously structural source lines. The [source index](../code_specs/README.md)
now has **16,694 contracts in 14,278 blocks**, across 751 files /172,040 lines /
19,412 blocks. Selected callable/type/inline-cluster gaps remain zero. The exact
structural remainder is **5,134 blocks in 670
files /15,405 lines**; it is checked as the previous remainder minus these 46 IDs.
Card scope follows its anchor, not blanket certification of neighboring comments.

| Source | New cards |
| --- | ---: |
| [adapter.hpp](../code_specs/files/include/crown/frontend/adapter.hpp.md) | 1 |
| [bind.hpp](../code_specs/files/include/crown/frontend/bind.hpp.md) | 3 |
| [normalize.hpp](../code_specs/files/include/crown/frontend/normalize.hpp.md) | 2 |
| [sql_rows.hpp](../code_specs/files/include/crown/frontend/sql_rows.hpp.md) | 1 |
| [admission.hpp](../code_specs/files/include/crown/io/admission.hpp.md) | 1 |
| [binding.hpp](../code_specs/files/include/crown/io/binding.hpp.md) | 1 |
| [candidates.hpp](../code_specs/files/include/crown/io/candidates.hpp.md) | 1 |
| [catalog.hpp](../code_specs/files/include/crown/io/catalog.hpp.md) | 1 |
| [catalog_source.hpp](../code_specs/files/include/crown/io/catalog_source.hpp.md) | 1 |
| [cursor_observation.hpp](../code_specs/files/include/crown/io/cursor_observation.hpp.md) | 1 |
| [document.hpp](../code_specs/files/include/crown/io/document.hpp.md) | 1 |
| [inspection.hpp](../code_specs/files/include/crown/io/inspection.hpp.md) | 1 |
| [layout.hpp](../code_specs/files/include/crown/io/layout.hpp.md) | 1 |
| [memory_report.hpp](../code_specs/files/include/crown/io/memory_report.hpp.md) | 1 |
| [oracle.hpp](../code_specs/files/include/crown/io/oracle.hpp.md) | 1 |
| [recognition.hpp](../code_specs/files/include/crown/io/recognition.hpp.md) | 1 |
| [residual.hpp](../code_specs/files/include/crown/io/residual.hpp.md) | 1 |
| [run_context.hpp](../code_specs/files/include/crown/io/run_context.hpp.md) | 1 |
| [search.hpp](../code_specs/files/include/crown/io/search.hpp.md) | 1 |
| [sql.hpp](../code_specs/files/include/crown/io/sql.hpp.md) | 1 |
| [tree.hpp](../code_specs/files/include/crown/io/tree.hpp.md) | 1 |
| [digest.hpp](../code_specs/files/include/crown/ir/digest.hpp.md) | 1 |
| [model.hpp](../code_specs/files/include/crown/ir/model.hpp.md) | 6 |
| [physical.hpp](../code_specs/files/include/crown/ir/physical.hpp.md) | 1 |
| [program_json.hpp](../code_specs/files/include/crown/ir/program_json.hpp.md) | 1 |
| [program_model.hpp](../code_specs/files/include/crown/ir/program_model.hpp.md) | 5 |
| [tree.hpp](../code_specs/files/include/crown/ir/tree.hpp.md) | 1 |
| [sql_aggregate_checkpoint.hpp](../code_specs/files/include/crown/recovery/sql_aggregate_checkpoint.hpp.md) | 1 |
| [sql_aggregate_descriptor.hpp](../code_specs/files/include/crown/recovery/sql_aggregate_descriptor.hpp.md) | 1 |
| [sql_aggregate_records.hpp](../code_specs/files/include/crown/recovery/sql_aggregate_records.hpp.md) | 4 |
| [version.hpp](../code_specs/files/include/crown/version.hpp.md) | 1 |

## Source and design findings

Aliases and forward declarations choose names and shapes; they do not run the
compiler, parser, validation or codec. Owned reference values differ from native
spans and scalar views. Strings can borrow native backing; inline numeric/date/
Decimal values retain their own bounded representation. Retain actual shared
layout/program owners where views need them. [Paper/design context](../code_review.md)
distinguishes mathematical query structure from these engineering contracts.

JSON import/export is separate from typed checked authority. Binding artifacts
require bounded compiler replay; a parsed tree or HeightCertificate DTO is not
minimum-proof acceptance. Live progress export does not advance a continuation.
Output-byte caps do not cap caller data, string capacity, scratch or elapsed time.
SHA-256 byte digests and FNV bucket hashes have different uses; neither an alias
nor a hash alone authenticates a query or execution claim.

R2 transport works on genuine program types and fixed/borrowed metadata. Frame
owns encoded bytes plus inspection info; DecodedInput adds flat cells/replacements
whose spans borrow retained storage. Successful inspection and bounded codec work
do not establish file durability, selected generations, sink receipts or native
replay. Interface and version constants do not negotiate unrelated wire formats.

## Review and verification scope

One Luna Max author and a separate Luna Max peer review all seven fields. Root
reads every selected range (393 lines) with adjacent context, targeted backing
implementations and the final fields; root does not claim rereading all complete
31 headers. Exact replay checks 52 peer amendments plus
1 root amendments. Source geometry, unique anchors, the
original missing set and all 16,648 older registry entries are preserved.
The author expected-file source pins expanded from 31 selected headers to all
47 selected/excluded header files before cards. The exact 46-region scope stayed
fixed; its old/new pin is recorded separately. Canonical block-signature metadata
already matches the frozen inventory. Formal receiving advances the disjoint
V41-based draft to V42 without changing its native headers.

All **1,196 native inputs and 355 production paths equal V42 byte for byte**.
There is no native build, CTest, SDK, benchmark or release run in V43, and no
runtime handler, wrapper, allocation, branch or checkpoint is added. V41's actual
strict affected Debug/SAN backend-binding results retain their dated attribution.
Completed map and current-guide checks validate local references, with external
URLs explicitly skipped. The [receiving packet](../../build/verification/inspection-wire-declarations-v43-v1/README.md)
pins both immutable reviews and the final exact structural remainder.

Latest seal: build/verification/human-inspection-v43-progress-v1.json; frozen
source: build/verification/human-inspection-v43-source-v1. Exact prior handoff:
[V42 history](../handoff-history-v42-2026-11-14.md). The full goal remains active:
**57 verified /1 in progress A02 /20 not started**. W06 retains its bounded profile;
A02/C04/B01, R2 retirement, V04 and release gates remain open.
