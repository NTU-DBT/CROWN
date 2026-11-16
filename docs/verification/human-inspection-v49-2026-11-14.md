# V49: complete scoped usage-card coverage

The maintained index covers 755 files, 172,812 lines and 19,462 lexical/AST/CMake
blocks. Its 18,992 authored usage contracts cover all 16,561 nonblank blocks.
The remaining 2,901 blocks contain blank spacing and keep structural descriptions.
No nonblank block is left with structural facts alone. Each line belongs to a
mapped block; usage fields describe the block's scope, rather than repeat prose
on every line. See the [index](../code_specs/README.md) and
[examination guide](../code_review.md).

## What was received

V49 adds 2,148 cards for the final nonblank frontier: 386 planner,
369 runtime/storage/resource, 368 other native boundaries and 1,025 test/build/tool
blocks. These comprise 853 declaration regions, 616 comment regions and 679
scope-close regions. Every card supplies purpose, inputs/outputs, invariants,
ownership, failure, cost and references, plus its reviewed source hash.
Exact source-span anchors disambiguate repeated braces and notes; the
[anchor specification](../code_specs/anchor_format.md) defines their binding.

Complete mechanical checks cover every new card and the resulting 18,992-record
registry: exact source binding, source hashes, unique keys, required fields,
local references and replay of existing-record changes. Regeneration and the
map checker verify full source coverage, zero stale/unused cards and valid
generated local links. Remaining blank-block contents match V48.

Author source review and independent cross-review are recorded separately.
The planner review read all 66 declaration and 61 closing regions and checked
the non-certifying language in its 259 comment cards. Runtime/boundary review
used targeted compound declarations and adjacent ownership definitions; it did
not re-prove all 737 behavior/cost claims. Root reviewed the factored material
for its 1,025 cards and 109 distinct non-namespace closing contexts. Independent
root review checked all bindings and selected semantic cases, followed by a
bounded check of 684 wording/reference corrections. The final planner/runtime
postimage reviews check their 31/9 corrected records. These review scopes do
not establish a general proof of every retained source comment.

Concrete corrections distinguish owning blocks from numeric identities, borrowed
Choice pointers from their retained arena, shared immutable artifact owners,
inline `make_shared` construction costs, namespace transitions and compile-only
prototype failures. The Task span ends at its default constructor; the adjacent
Handle-taking constructor is outside that span. A runtime draft's parent label
named the V47 ancestor embedded in V48; receiving corrects the label to the
actual V48 seal without modifying the completed draft. All its source pins match
V48. P2 references remain limited to the frozen-ear reduction recipe.

## Direct code and cost boundary

All 355 `apps/include/src` paths are byte-identical to V48. All C++ executable
tokens and literals, and all CMake command bodies, are unchanged. Five stale
comment lines in CMake and indexed-table tests were corrected. The only changed
tool behavior is the offline anchor locator: strict syntax, in-range endpoints
and an exact SHA-256 check return a location or no match. A numeric-width guard
rejects impossible endpoints before integer conversion, including 5,000-digit
inputs, without a new catch or arbitrary cutoff. Literal anchors retain their
existing uniqueness behavior. Twenty-six pure locator controls and independent
AST/source checks pass; the other 21 tool functions are unchanged.

The specs distinguish preprocessing, constant/member initialization, Python
module work, construction, native calls and cleanup. A declaration is not a
blanket promise that its initializers or referenced types allocate nothing.
The registry and locator run offline and add no engine checks, instrumentation,
owner, allocation, dependency, error layer or per-update work. Existing handler
dispositions remain in [error handling](../code_specs/error_handling.md):
rollback, reader cleanup and uncertain-I/O latching retain their owning boundary.
No production handler was added or removed in V49.

The existing registry receives 1,532 source-hash-only updates with original
authors preserved, and one semantic amendment for `contract_line`. The remaining
old records are unchanged. The raw registry and exact before/after receipts are
preserved for human examination.

## Evidence and limits

The evidence packet is
`build/verification/inspection-structural-completion-v49-v1`. It retains the V48
entry audit, original/corrected drafts, source-review materials, independent
review receipts, exact registry replay, generator/checker logs, coverage audit,
current-guide link audit and final source/evidence manifest. Review packets, including the independently authored source and correction
reviews, are the `build/verification/v49-*-review-*` directories named in receiving.
Root owns final exact registry replay and receiving. An additional reviewer
status note is limited to counts, terminal logs and prose boundaries.
The checkpoint and postcheck are
`build/verification/human-inspection-v49-progress-v1.json` and
`build/verification/human-inspection-v49-postseal-check-v1.json`.

No native build, CTest suite, benchmark, installed SDK or plotting job was run
for V49. The entry audit checked 4,618 current/frozen V48 source paths and 59,157
protected artifacts. Prior B05 results remain attached to their exact frozen
V48 experiment cohort, including its separately recorded generator docstring
successor. Documentation coverage supplies inspection scope, not a new native
correctness, complexity, timing, allocator or paper-proof claim.

The [ledger](../task_ledger.md) remains 60 verified, one in progress (A02),
17 not started, 78 total. V01/V02 and the bounded V33 W06 contract retain their
documented acceptance. A02-dependent work, remaining experimental/extensions,
R2 retirement and release gates remain open. The full Refactor goal is active.
Use the [handoff](../handoff.md) to continue.
