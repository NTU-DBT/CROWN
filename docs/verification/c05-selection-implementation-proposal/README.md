# C05 selection — frozen excluded implementation

This new overlay implements the accepted C05 preflight. The immutable design
package is `492e5a3f4804acb357a5177f3eed92487a7538ae747e6abfc258fbf08f45ee54`;
root's implementation authorization is
`build/verification/c05-selection-design-root-review-2026-11-07.json`, SHA-256
`58a955dd341f0b2bb642be0ec272e34f3b0fb749d8d5ef69df58762c6ebd839b`.

Only this proposal and its distinct `/tmp/crown-c05-selection-implementation-*`
outputs are authored here. Native sources, all C01/C02 packages and artifacts,
the ledger and AntiGravity handoff remain unchanged. Root owns all execution
and acceptance. Direct compilation/linking, when recorded, is not test execution.

The API and implementation are frozen after root's accepted excluded execution
and independent source review. Diagnostic
`Resource` fields distinguish C05 limits, and CacheObservation records actual
cache-use/capacity configuration in addition to the designed disposition. These
do not change policy, proof, cache equality or selection semantics.

No C03 model, allocator-byte prediction, automatic deployment, native acceptance
or card-status claim is made. All such unsupported requests remain explicit.

The packet contains the pure selection layer, separate matched runtime bridge,
complete constraint/primary assessment retention, exact framed source/family/
context binding and a transactional bounded FIFO artifact cache. The source
map names future native destinations only; no destination is copied here and
no native registration is included.

- [Public usage and limitations](GUIDE.md)
- [Exact byte framing and field-order contract](BINDING.md)
- [Logical charge table, aggregate equation and timing](ACCOUNTING.md)
- [Authored consumer inventory and required execution gates](TESTS.md)
- [Root-only direct build recipe and variant inventory](BUILD.md)
- [Exact root consumer invocations and provenance](ROOT_REPRODUCTION.md)
- [Recorded root outcomes and remaining gates](EVIDENCE.md)

The current full checkpoint is nineteen compile entries and ten links. The
historical first checkpoint compiled six implementation units cleanly; later
source changes mean those old objects are not a current complete closure.
Root passed all ten producer consumers and all five independent consumers in
both ordinary and matching ASan/UBSan/leak-checking variants. Each variant
completed the producer's 32,966 direct and 20,420 normalized persistent-failure
positions, with zero cleanup recoveries. Independent coverage remains its
separate 22 groups and focused positions. The exact receipts, preserved
corrections and limits are recorded in `EVIDENCE.md`; root's accepted aggregate
is `build/verification/c05-preparation-execution-completion.json`, SHA-256
`43b420248cb77e1c6c9ba72fe6f29e3de80498740d19d53b0cafbad935d5f0c9`.

`FROZEN.md` defines the source, artifact and historical-checkpoint manifest
scope. Native publication, independent registration review, guarded application,
the complete native matrix and final source acceptance remain separate gates.
