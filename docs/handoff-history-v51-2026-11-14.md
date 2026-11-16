# CROWN continuation handoff — V51

Continue the full Refactor implementation goal; it remains active. The ledger is
60 verified /2 in progress (A02/X01) /16 not started, 78 total. No release or full
X01 acceptance is claimed. The exact prior handoff is preserved in
[V50 history](handoff-history-v50-2026-11-14.md).

The V51 checkpoint is `build/verification/human-inspection-v51-progress-v1.json`,
with frozen source `build/verification/human-inspection-v51-source-v1` and
postcheck `build/verification/human-inspection-v51-postseal-check-v1.json`.
Read and verify that seal/postcheck before editing. The receiving packet is
`build/verification/update-pattern-contracts-v51-v1`; the
[V51 verification record](verification/update-pattern-contracts-v51-2026-11-14.md)
explains implementation, native checks, source/spec receiving and review limits.
The accepted parent is V50 seal SHA
`11ecaf63d63e2a93f737778a71903d4dd443d62e3d65ca4efde79ef2134207f2`.

## Completed in V51

IR declarations bind canonical TableRule values to the actual compiler source
SHA-256 and table count. They preserve explicit raw joint FIFO IDs and own no
row history or unused group index. Planner analysis retains genuine candidate
and source-bound declaration handles, rejects unsupported transfer cases and
recognizes constant/all-insertion/height-one/conservative height-two sufficient
cases. Raw reports are not_checked, constants not_required, and typed transfer
is marked checked only after the gates. Taller mixed cases remain unknown.

Pure selection optionally uses those analyses to exclude unproved cases at the
original certified minimum height, retains each analysis and binds all source/
rule fields into a versioned artifact key. No eligible candidate returns before
unnecessary primary ranking; invoked C02 assessments still cover the full retained
family. Default requests skip new analysis/copy work and keep prior request bytes;
empty optional/vector fields add fixed storage. Base runtime still does not link
ranking. No input-update hook, retained row mirror, monitor catch or recovery
wire extension was added. The public analysis boundary translates errors once.

Final exact-source ASan/UBSan/leak checks pass ten targeted groups. Debug coverage
combines nine passed groups in v3 and the corrected final selection_pattern run.
The latter passes 332 persistent covered C++ allocation denials, including nine
in pattern_analysis, and an actual original-account cap refusal. Raw malloc and
exception-runtime storage are outside the seam. The production Release build
passes with BUILD_TESTING=OFF. Earlier failed/older-source runs are preserved;
there is no new whole 351-case suite, benchmark, Clang or moved-SDK claim.

Specifications cover 763 maintained files /174,044 lines /19,573 mapped blocks.
19,102 contracts cover all 16,671 nonblank blocks; the remaining 2,902 blocks are
blank. V51 adds 98 cards and reviews/amends 22 changed existing blocks; 1,623
hash-only and 71 exact-body anchor updates preserve their original authors.
The source/map/reference checker passes 139,502 generated local links. Root's
receiving records distinguish full binding checks from scoped semantic review.

Completed Luna Max packets are continuation-v51-entry-v1,
v51-declaration-usage-review-v1, v51-new-usage-cards-v1 and
v51-final-pattern-code-review-v1. The final review has zero open findings over
13 effective native source pins, preserving original and successor copies.
Its sanitizer note was pending at review time; root separately receives final
SAN v2. Root authored the native implementation, six integration/test cards,
22 amendments, and the explicit corrections/rebases to peer drafts. No Astra
was used in V51. The V50 paper proof packet remains independent source/proof
context, not successor implementation acceptance.

## Next implementation

Finish X01's actual insertion-only/mixed admission monitors before asserting a
pattern-dependent runtime profile. Establish and charge the origin/loading
prefix, distinguish no-op erases and metadata-only label removal from physical
lifetime termination, and reject violations before publication through existing
Session/window ownership. Prefer the existing window birth-count owner for FIFO;
nonwindow FIFO needs genuine origin/history, not sampled C01 counters.

Bind committed monitoring/profile facts to source/query/tree/schema and preserve
them through checkpoint/journal restore and reoptimization. A requested
Declaration and a plain Analysis are not observed compliance or proof authority.
Keep the conservative accepted-row transfer argument and taller-case limitation;
never promote Trim/MixDetect into height or pattern-bound authority. The
[usage guide](update_patterns.md) and immutable V50 requirements/design/proof
packet spell out the remaining acceptance obligations.

A02's project license disposition still blocks C04/B01 acceptance, not independent
implementation. Other open tasks are C04; X01–X11; B01/B04/B06; V03/V04. B05 stays
its finite V48 cohort; V01/V02 and bounded V33 W06 retain their stated premises.

## Workspace rules

Completed packets, snapshots, private SDK/builds and dependency prefixes remain
immutable. `.git` is read-only at e369a623517723b3be3ea3e9806779f3c591e7f9; do not
stage, reset or commit. No applicable AGENTS.md was found at entry. Use
PYTHONDONTWRITEBYTECODE=1 for repository/helper imports. exec_command requires
require_escalated because the default launcher is broken; no approval rejection
occurred. Reusable builds are w05-debug, w05-sanitizer and
inspection-build-scope-off-v1 (Release/tests OFF). Do not edit native inputs while
recorder-wrapped jobs run. There are no live native jobs at this checkpoint.
