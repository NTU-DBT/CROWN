# Independent static review of the JSON and retained-payload repairs

2026-11-07. Root requested this read-only review while the coherent repaired
dependency closure was being prepared. This test author did not author the
producer implementation or edit its files. No binary, checker, CMake, CTest,
symbol tool or fault sweep was executed by this reviewer.

This review covers these exact draft source identities:

| Producer source | SHA-256 |
| --- | --- |
| `overlay/third_party/nlohmann/json.hpp` | `f763c58b102e65242d09275aec4b2f343268280ab4587b15587ad143b2e2a406` |
| `overlay/src/planner/ranking_payload.cpp` | `4d6311ac57bd8a88c0818089539821c46c9e01e939a74137623fa595b02d13d5` |
| `overlay/src/planner/ranking_payload.hpp` | `81086a751152af03b710148d39e02a9637ceb41036a0afbe23e57c44e4b5aa4b` |
| `overlay/src/planner/ranking.cpp` | `7dc006583f0e888e86d344336a610eb4585ae306de63ad67e0e93a0b114836c4` |

These paths are within `docs/verification/c02-baseline-ranking-proposal`.
A final package/closure pin remains necessary; this note does not silently
transfer its conclusion to later edits.

## Findings returned to the producer

Two actual owned payload components were missing from the first payload visitor:

1. `scalar()` handled string alternatives but skipped `Decimal`'s private
   coefficient string. `include/crown/ir/scalar.hpp` defines a heap-capable
   `digits_` string with up to 38 canonical digits. Copied query terms, normalized
   literals/constants/parameters and compiled input constants can retain this
   payload beyond the inline `Value` slot. The revised visitor charges a
   conservative 38 character bytes and 38 work units without allocating a
   formatted string. This covers logical coefficient content; capacity,
   terminators and allocator overhead remain outside the declared model.
2. `TupleLayout::Data` owns a vector of equality pairs in addition to its field
   vector. `src/storage/layout.cpp` populates a pair for each repeated variable,
   and `src/planner/lower.cpp` uses the ordered, potentially repeated output
   vector to construct its result layout. The revised visitor charges the
   equality-vector header and a conservative pair allowance per field. This
   linear bound covers repeated heads without an unbounded duplicate search.

Both corrections are present in the payload source hash above. They were
identified from the actual retained representations, not inferred from an
allocator-total claim or used to change any literal score expectation.

## JSON lifetime analysis

No static blocker was found for the project's default `json` and `ordered_json`
types with exceptions enabled.

The normal flattening loop remains. Its active value now lives outside the
`try` block, so a failed stack growth cannot trigger that value's destructor
before the catch can empty it. After partial moves, every descendant still has
one of three owners: the active value, the flattening stack, or the original
array/object. The catch prunes all three sets before normal teardown resumes.

The fallback walks to the last leaf using iterators, erases it, and restarts
from the retained root. It retains no allocating traversal stack and does not
recurse with input depth. An erased structured child is already empty, so its
ordinary destruction reserves zero flattening capacity. Removing the final
element also avoids `ordered_map::erase`'s const-key reconstruction/shift loop.
Primitive/string/binary clearing and destruction require no allocation in
these concrete container types.

Moving the active value by assignment and resetting it to null preserve the
normal per-iteration destruction point. The patch adds a static helper and
local variables, with no new stored field. It does not change serialized
values, container ordering, native scalar tags or object/union layout.

The slower fallback can revisit ancestors repeatedly. It is cleanup safety,
not a linear-time or hard-deadline promise. This review makes no separate claim
for arbitrary custom nlohmann object/allocator/base types or disabled-exception
configurations.

## Payload admission analysis and remaining gates

Each candidate admits its source/query/tree/program and identity component
model before calling the native lowerer. After lowering, the compiled plan's
layouts, relations, projections, inputs, nodes, edges, enumeration, guarantee
text and related metadata are charged before the plan is assigned into a
published score. Shared projection references may be charged repeatedly;
the declared accounting is conservative logical component payload. Native
blocking construction, allocator metadata/capacity and transient peak memory
are explicitly separate. No S05 total-byte or peak-bound conclusion follows.

The canonical-identity visitor is iterative and charges pending pointer entries
before inserting them. Fixed-width size multiplications use the common checked
budget helper. The revised Decimal allowance avoids an allocating formatting
call before admission; the equality bound uses the same checked vector charge.

Root still needs the complete consistently rebuilt CROWN closure with the
patched JSON header, ordinary and persistent-failure controls, sanitizer/leak
execution and all semantic regressions. Linking old archives that instantiate
the old JSON inline definitions would not establish this repaired closure.
The independent public tests retain the literal `195/105/190`, mirrored hot-table
scores, `24/32/32` slot totals and all prior assertions. Their exact/one-under
payload check validates the public transactional budget boundary; it does not
independently turn the component model into an allocator measurement.

The final independent strict link uses the held coherent producer closure at
`/tmp/crown-c02-baseline-coherent-strict-1`. Its exact recipe and source/variant
inventory are preserved under this packet's `provenance/` directory. All 67
production dependency units and the current consumers were compiled with the
patched header; the separately compiled testing runtime is not linked here.
Both independent consumers compile/link with empty logs and zero exits. This
closes the author-side dependency concern, while every execution/fault/sanitizer
gate above remains root-owned and unclaimed by this review.
