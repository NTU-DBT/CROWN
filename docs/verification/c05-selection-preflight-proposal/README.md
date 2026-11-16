# C05 selection preflight — excluded design

This packet proposes the C05 baseline on the actual P06/P07/P08/C01/C02 APIs.
It contains design, public-interface sketches, an analytical cache argument and
an independent acceptance plan. It implements nothing and advances no card.
No native source, ledger, handoff, matrix helper or frozen evidence is changed.
No compiler, generated consumer, Python checker, CMake, CTest, symbol tool or
benchmark was run for this preflight. Root review precedes implementation.

The proposed default orders candidates by proved required height, committed
physical-input native-depth score, then the full structural key. Height-only
and tuple/index-slot policies remain explicit alternatives. C03 maintenance
cost is unavailable in this baseline. An optional slot-unit constraint is
enforced using complete C02 slot assessments; a requested allocator-byte
prediction fails explicitly. Slots are never compared to bytes.

Every call performs fresh complete ranking of its supplied retained candidate
set. The bounded cache stores only an immutable compiled P08 artifact, looked
up after that fresh decision. It never substitutes a cached proof, snapshot,
ranking result or evidence. Its full equality key includes exact source/tree
identity, original binding/height/context, the retained family, policies,
options, constraints and relevant evidence context. A cache hit cannot establish
freshness. Memory scoring already lowers the candidates in C02, so this design
does not claim that artifact caching avoids that work.

Pure calls are explicitly evidence-free or as-of. Runtime bridge calls always
capture new bounded evidence from the actual Physical/Delta/Session owner under
the existing exclusive-owner contract. They accept no caller-labelled current
record. Saved results remain owning history after later owner changes. Selection
does not install a plan, initialize another runtime, switch a session or perform
C06 reoptimization.

Read `CONTRACT.md` for the end-to-end decision, `API.md` for the proposed typed
surface, `CACHE_KEY.md` for exact binding and the cache proof, `RESOURCES.md`
for aggregate accounting/failure publication, `ACCEPTANCE.md` for concrete
independent fixtures, and `SOURCE_MAP.md` for existing and proposed layers.
`DECISIONS.md` records the source-grounded tradeoffs that need root review.

The frozen C02 native publication is pinned at package SHA-256
`2a4b0f76caec3c20bb512a642bba90e2c07ac4482c2c11462a539b35c3a17d78`.
It was subsequently applied by root and its native/execution sources frozen
in `build/verification/ranking-execution-freeze.json`, SHA-256
`1f97f84d7d2a09fb992668fcfa071d0065241b0a5de5395244a966216657d036`.
That boundary records 648 native inputs and 705 execution inputs; the expected
native registration is 143 tests/214 compile entries. The C02 matrix is a
separate root-owned task; this design makes no claim about its eventual result.
The already accepted scoped preparation aggregate is pinned independently.

`INPUT_SHA256SUMS` pins the exact files read; `source-files.sha256` selects the
actual code/API/fixture inputs grounding this design. `PACKAGE_SHA256SUMS`
pins this design packet itself. All paths in these manifests are relative to
the repository root, except any explicitly absolute temporary evidence path.
Only historical manifest FILE identities are pinned; their old source entries
are not rechecked against the later C02 tree.
