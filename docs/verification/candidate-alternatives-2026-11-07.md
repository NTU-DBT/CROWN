# P07 minimum-height alternative plans

Status: implemented and verified, 2026-11-07 (Asia/Shanghai). All 92 tests pass
the five-configuration matrix on one frozen revision. The full 78-card goal
remains active: 36 verified, two in progress (A02/O06), 40 not started.

The native [contract](../candidate_alternatives.md) and
[proof notes](../planner_proofs.md) define the public CandidateProvider,
minimum-height candidate, immutable snapshot and exact-binding FIFO cache.
Only an unchanged original P06 VerifiedOptimum supplies the minimum. Every
seed/generated tree passes original-binding P02 and the exact proved-height
gate. An alternative never replaces the certificate's original witness.
Exhaustion covers admitted seeds plus the finite normal form, including
separately retained unary-generalized witnesses; it does not establish global
cost optimization across all tree shapes.

The full 92-test matrix is the native acceptance evidence. Earlier isolated
prototypes and their checks are design/preparation evidence, not native
acceptance or a substitute for this matrix.

## Independent acceptance

- The public provider's complete families match a separate Prüfer collector
  across all 225 three-atom/two-variable valid-head queries. Frozen P03 and
  owned P06 minima agree. Independent signatures and production structural
  keys are bijective; Boolean R/S/T has three plans and the equal-scope
  three-occurrence self-join has four.
- Native P02/height/binding checks, empty/nullary/projected/disconnected inputs,
  permutations, generalized scopes/grouping and original occurrence identity,
  unit/varied slicing, zero grants, resource raises, cancellation/moves and
  retained handles pass. Public P06 replay preserves a non-normal-form unary
  witness and its unchanged proof. Mandatory seven-/nine-atom original
  minimum-three seeds and bounded 70-variable/70-occurrence work pass.
- The genuine N(), R(x,y), S(x), output-y fixture publishes two distinct
  height-two trees: P06's generalized empty root over N and R→S, then P05's
  native R-root with S,N children. Residual provenance and its trace-only
  authority survive cached reuse under the new provider's supplied proof.
- Exact catalog/query/context fences cover versions, types, constraints,
  metadata, constants/ignored terms, head order/repetition/aliases,
  contradiction and unsupported profiles. Raw bytes, non-UTF-8 strings and
  embedded NULs remain exact in native admission/cache identity. Strict JSON
  text encoding remains a separately documented transport boundary.
- Generator/key/fresh-provider advance sweeps cover every observed
  613/17/2369 allocation position with persistent failure, two retries and
  same-owner recovery to ordered output/statistics/content/committed work.
  Separate uncapped factory, snapshot, cache-node and residual/cached-prefix
  admission sweeps pass with deep copied value baselines. Their counts are
  discovered in the loops; no unprinted admission counts are invented.
- Thirty-five actual typed reports and 54 rejected schema mutations cover
  CQ v1/v2/v3, date/decimal/metadata, original proof vs separate checked upper,
  immutable prefixes, real residual/cached provenance, resource/allocation
  stops and terminal failure. Original certificates are independently replayed.
  Reports do not accept editable progress flags or create proof authority.

Fresh [Astra source/proof review](p07-native-review-2026-11-07.md) is clear.
The final direct typed Catalog/Query v2 encoder covers every native field,
using type/length/record framing, ordered counts, presence bits and raw bytes.
Dates use exact day values and decimals canonical exact text. The final repair removes JSON construction from admission entirely. It constructs
no JSON during admission, so failed allocation unwinds ordinary native
containers without allocating another destruction stack. Logical limits and
variable-width costs/exclusions remain explicit; S05 bytes/hard deadlines
and durable recovery/delivery remain separate.

Native source, schema, tool and fixture inputs remain frozen for this acceptance; do NOT change execution inputs.

## Full matrix

| Configuration | Tests | CTest seconds |
| --- | --- | ---: |
| GCC Debug | 92/92 | 1340.75 |
| GCC Release | 92/92 | 234.44 |
| Clang Debug | 92/92 | 1113.50 |
| Fresh source-only Release | 92/92 | 218.24 |
| ASan + UBSan + leak checking (sanitizer) | 92/92 | 5718.82 |

All jobs are terminal and closed. Clean-source helper time is 656.95 seconds
(657.06 including its wrapper), configure/build/test 0.98/437.51/218.25 seconds;
`/tmp/crown-clean-source-rvhwtkti` is removed. Final focused Debug/Release
three-target acceptance took 100.93/16.01 seconds before the full matrix.

Every configuration preserves the same 495 native-input fingerprint
`975cc69ab2c66dcd0fa1f967877208ef0d78d6f2169d518037a5c14b7c56f2f3`
and 537 complete execution-input fingerprint
`4ed6d7ba9b91a79a6283dc61a73c2d5ab70aabc6a338b987c7c1ea506ebcf43f`.
The freeze record is `build/verification/candidate-alternatives-execution-freeze.json`;
full raw logs/summaries use `candidate-alternatives-{configuration}-*`.
The independent matrix audit accepts 165 matching structured rows in all four
in-place configurations: the preserved P05 162 plus three P07 rows. It also
checks all prior mandatory failure/semantic profiles, parser-C ASan/UBSan,
project warnings, proof-export scopes and clean-source completion/removal.
JSON/log: `build/verification/candidate-alternatives-matrix-evidence-audit.*`.

Two targeted failed/interim attempts remain archived and unaccepted:
`candidate-alternatives-targeted-attempt-1-pre-byte-fix/` and
`candidate-alternatives-targeted-attempt-2-dom-unwind/`. The first implementation
used strict textual binding dumping and rejected valid native byte strings.
An interim DOM encoding then exposed nlohmann's allocating nonthrowing
destructor during persistent factory OOM; a debugger traceback confirmed it.
Direct native v2 encoding repairs both. No fault positions, assertions,
warning policies or memory checks were weakened. P07 uses one final revision;
the earlier P05 watchdog-only A/B history is not a P07 acceptance bridge.

## Source seal and next work

The [592-input ordinary source seal](candidate-alternatives-sources.sha256)
has SHA-256 `7128bca952d896f768afcc8ac7daa0630de43ad98bcfc95a7fb2105342216dcb`: P05's 563 plus 29 new paths, none removed.
All eight prior manifest FILE hashes and the original Refactor.md hash are
preserved. The independent final source audit passes with zero failures and zero pending checks; JSON/log: `build/verification/candidate-alternatives-source-seal-audit.*`.

The excluded [O07 preflight](o07-design-preflight-2026-11-07.md) and observed
[hand-trace baseline](o07-baseline-probe/README.md) are preparation only.
O07 remains not started until native integration. Continue that free branch,
respect S04/S05's dependency/license chain, and keep all remaining recovery,
optimizer, extension, experiment, external-review and release gates open.
