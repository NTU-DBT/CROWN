# C05 recorded evidence and remaining gates

This file records completed root outcomes only. The excluded implementation is
frozen as excluded preparation and is not registered natively. Root owns compilation after the initial
six-unit author checkpoint, all consumer execution and later acceptance. The
implementation and executed build recipes remain immutable. All preparation
guards are closed. Nothing in this packet advances C05's native card status.

## Completed strict checkpoints

| Checkpoint | Observed outcome | Boundary |
| --- | --- | --- |
| Historical strict1 | Six implementation translation units compiled under GNU C++23 and all six warning flags | Historical source only; no linked or executed consumers |
| Root strict2 | Eighteen of nineteen translation units, three archives and nine of ten links passed | Binding test macro comma failed; original diagnostics retained |
| Root strict3 | Eighteen of nineteen translation units, three archives and nine of ten links passed; 203 input entries unchanged | Optimized nested variant construction in the binding consumer still failed; no implementation failure was reported |
| Root targeted strict4 | Corrected binding consumer compiled and linked; eighteen earlier translation units, three archives and nine binaries reused with exact provenance | In-place construction retained the same literal bytes and all warnings/oracles |
| Root strict smoke | Eight of eight short consumers exited zero, with empty stderr and guarded source inputs unchanged | The two complete allocation-failure consumers were not included |
| Root targeted strict5 and strict faults | The corrected normalized consumer joined the exact strict3/strict4 closure; both complete persistent-failure consumers exited zero with empty stderr and stable guards | Ordinary execution only; the sweeps cover their actual reached allocation positions |

The smoke consumers were `pure_link`, `contract`, `cache`, `source`, `current`,
`binding`, `resources` and `census`. The executed binding case reported 143
record/key mutations. That is an observed producer check count, not a proof of
all possible source or cache inputs. The testing-macro `census` consumer used
the matching testing runtime; the others used production or pure closures.

The exact terminal root receipts are:

| Receipt file | SHA-256 |
| --- | --- |
| `build/verification/c05-selection-strict-root-checkpoint-4.json` | `ce940f0c35500e4c69f026bb4fc091a8a04202edced79c9a6d37b99fd3861ac4` |
| `build/verification/c05-producer-strict-root-attempt-1-smoke.json` | `af6eccdd50b1ec917de1c13f8f59bc6793b5543de0fd96cc341228f6b5003acc` |
| `build/verification/c05-producer-strict-root-attempt-1-smoke-dependencies.json` | `63be01603329e1166e571046ac6ba312689a8e3672ed661f27de1d306cbb7b8b` |
| `build/verification/c05-producer-strict-root-attempt-1-faults.json` | `2fd27f52b246ff36b0ef73ef39bcb8467fd7203321140a026b9592218fe04ffa` |

The smoke receipt pins all eight executable files, argv, environment, source
and compiler dependencies, stdout/stderr, exit statuses and durations. The
separate dependency receipt retains the reused/fresh object chain. The first
root smoke preflight stopped before any consumer because the guard expected
only overlay paths while the complete source manifest also contained recipe4.
Root preserved that failed preflight and used a corrected inventory guard;
no implementation or assertion change was required.

The two later strict fault consumers completed 32,966 DirectCQ positions and
20,420 normalized-source positions. Both reported zero cleanup recoveries and
preservation of the complete prior owner/workload/cache/owning-result state.
The DirectCQ sweep recorded two late publication failures. These are observed
totals for those exact fixtures and binaries, not a universal allocation bound
or a reason to combine independent focused positions into an exhaustive count.
Together with the eight smoke consumers, all ten producer ordinary consumers
passed.

## Independent cache diagnosis

The independent ordinary public consumer passed its seven groups, including
the literal depth, slot, constrained-winner, alias and Decimal cases. The cache
consumer subsequently failed its generic successful-selection assertion. Root
preserved that result and executed a separate diagnostic with the same success
expectations and added call/field markers.

The diagnostic confirmed that calls 1 through 32 succeeded. Call 33, physical
options field 0, changed the arithmetic policy from `exact-nonnull-v1` to an
unsupported value. Native `src/io/identity.cpp` requires that exact arithmetic
policy; native lower preserves it. C05 returned `lowering_failure` at `lowering`,
with no resource/component classification and no selection. This matches the
existing public contract in `docs/query_identity.md`; it does not justify
adding an unsupported arithmetic backend or changing C05's implementation.

The terminal diagnostic receipt is
`build/verification/c05-independent-cache-diagnostic-root-attempt-1.json`,
SHA-256 `9cad99e6147feb3eb30126c7627c1e96ac2695b223b70cd8b13fa2de06ad3bb0`.
It records exit 1, unchanged source guards and the status
`confirmed_unsupported_arithmetic_rejection`. This expected diagnostic failure
is not counted as a passing independent cache consumer.

Root authorized the independent author to retain that case as a rejection with
cache preservation and supported retry, while keeping all five supported
option variants' distinct-key assertions. The original test, failure and
diagnostic packages remain unchanged. The corrected cache consumer now passes
root's ordinary execution. Its receipt,
`build/verification/c05-independent-cache-corrected-strict-root-attempt-1.json`,
has SHA-256 `3126baa70103947a236e3befae252bdb89e352be44864d8b487d56082359ffec`.
All five independent ordinary consumers and 22 groups pass across the preserved
source lineage. The matching independent sanitizer outcome is recorded below.

## Matching sanitizer builds, execution and source review

Root completed the matching producer sanitizer build: 19 fresh translation
units, three archives and ten links, with 203 inputs unchanged. Its terminal
receipt is `build/verification/c05-selection-sanitize-root-checkpoint-1.json`,
SHA-256 `8c8e0ef0066795be37ba057c6278874aacf04d945ff84fc96abde0f2ee6a087e`.
The flags are C++23, `-g`, assertions enabled, all six strict warnings,
ASan/UBSan and frame pointers, with full `-MD` dependency capture. This is build
evidence; the later runtime receipt below establishes sanitizer execution.

Root also completed all five fresh matching independent sanitizer compiles and
links. Its terminal build receipt is
`build/verification/c05-independent-sanitize-build-root-attempt-1.json`,
SHA-256 `9266571c1c8db29071f6c5627c1342210698ab92a72a8b68f3642661d07096c3`.
That build receipt records 801 stable source inputs and stable link inputs;
its then-pending runtime acceptance was subsequently completed in the separate
receipt below. No live sanitizer log is treated as a pass.

All ten producer sanitizer consumers passed with ASan, UBSan and leak checking,
empty stderr and stable source guards. The direct and normalized sweeps
repeated 32,966 and 20,420 persistent-failure positions, respectively, with
zero cleanup recoveries. Their recorded durations were 2874.7283645209973 and
1312.169021232985 seconds; these are fixture/profile measurements, not a runtime
cost prediction. All five selected independent sanitizer consumers also passed
their 22 groups, with the same literal expectations and preserved corrected
lineage as the ordinary variant. The independent focused test's 22 positions,
two publication failures and zero completed fault positions remain distinct
from the producer's complete sweeps.

| Final terminal record | SHA-256 |
| --- | --- |
| `build/verification/c05-producer-sanitize-root-attempt-1.json` | `b4751d01a1d5d867a7c415fc656052dcbb97e6099baa8e81264a0bba6f20f4af` |
| `build/verification/c05-independent-sanitize-root-attempt-1.json` | `1352225d850e10cbffcca9f654b81acde7edb825ac1fd7063d43d28011b4b3f8` |
| `build/verification/c05-preparation-execution-completion.json` | `43b420248cb77e1c6c9ba72fe6f29e3de80498740d19d53b0cafbad935d5f0c9` |

The aggregate accepts excluded preparation execution and the scoped independent
source review. It explicitly retains native publication/matrix/source gates,
the real-normalized positive replay/normalization boundary limit, the
non-byte/non-C03 meaning of slots and logical payload, and exclusive owner/cache
access. It does not advance the native ledger or the whole goal.

The independent source review reports no concrete blocker in the held nine
implementation/header files. Its immutable package is
`docs/verification/c05-selection-independent-source-review-proposal/PACKAGE_SHA256SUMS`,
SHA-256 `6590cecabeff424ea347c3dcf78295443431f7e9a81ee080443e8aee049e00d8`.
The review distinguishes full artifact binding, fresh decisions on cache hits,
exclusive actual-owner access, preparation-once budgets and delayed cache
commit. It retains the narrow real-normalized positive replay/normalization
boundary coverage limit recorded in `TESTS.md`. It does not replace runtime
evidence or review the later publication mapping.

## Preserved correction and remaining gates

Source inspection found that the normalized fault fixture declared catalog
table `R` but used an unquoted SQL identifier, which PostgreSQL folds to `r`.
After the previous producer and independent build guards closed, root
authorized the single-source correction to `FROM "R"`. The fixture now resolves
the intended real binding. No implementation, interface, support helper,
numeric oracle or other consumer changed. Checkpoint `normalized-1` and
`build-checkpoint-5.sh` pin that correction and the strict4/strict3 artifact
lineage. The later completed strict fault receipt and matching sanitizer build
receipt above bind that corrected generation.

The full matching producer and independent sanitizer executions are complete.
Later native publication, registration review, guarded integration, the native
matrix and final source acceptance remain additional gates. This packet freezes
the accepted excluded implementation without asserting native completion.
