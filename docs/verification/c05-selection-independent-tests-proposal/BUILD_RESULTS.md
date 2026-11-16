# Actual build/execution status at packet freeze

| Scope | Actual result |
| --- | --- |
| Five independent consumers | Authored and statically inspected; not compiled or linked by this author |
| Independent ordinary executions | Not run; root must produce separate exit/output/guard receipts |
| Independent sanitizer executions | Not run; require matching complete sanitized implementation and native archives |
| Root strict-3 implementation closure | Root reports all implementation units and three archives built; 18 of19 total TUs and9 of10 producer links passed, with one producer binding-fixture warning |
| Root strict-4 producer correction | Root reports targeted binding consumer compile/link success and unchanged implementation/archive source lineage; not an independent consumer result |
| Compiler/system dependencies | Root recipe records full `-MD` files; actual dependencies must be retained and hashed by root before independent execution |

Before freeze, an initial input-hash inventory guessed the compiler frontend at
an absent `/usr/lib/gcc/` path. The partial 254-row output was not accepted and
is retained under the assigned temporary authoring prefix. Read-only discovery
located the actual `/usr/libexec/gcc/x86_64-linux-gnu/13/cc1plus`; the regenerated
manifest has all 255 requested FILE rows. Every final per-file hash loop now
stops immediately on failure. No compiler was invoked during that correction.

`INPUT_SHA256SUMS` pins the exact source/header/contract/compiler/native-archive
FILE inputs and root-confirmed strict implementation archive/object metadata
available at freeze. It does not claim that a source checksum proves compilation,
that archive naming proves ABI, or that unrelated historical input-manifest rows
are current. The held root strict checkpoint receipt and its manifests are FILE
provenance inputs; old live-entry inventories are not silently replayed.

All five independent consumers use production runtime ABI where runtime is
needed. The byte-only consumer is pure and links no runtime/report archive.
Focused OOM lives in its own binary. No testing seam or fabricated immutable
handle is used. Strict and sanitizer variants must have separate objects and
matching dependencies; ordinary C++ archives may not enter a sanitizer closure.

Unfinished coverage is explicit in `FIELD_MUTATIONS.md`. The focused OOM test is
not a replacement for complete producer sweeps. Timed tests classify carried
measurement and limits; they make no performance guarantee. No C05 native matrix,
CLI/publication/registration, measured engine overhead, C03 or S05 claim follows
from this preparation.
