# Proposed root-only checks

These cases have not been executed or syntax-checked by the author. Synthetic
failure cases must stay in isolated copies and must never masquerade as a
canonical matrix, root authority or completion record.

1. The actual freeze/native/execution digests match the root capture. Altered
   or unset digest constants produce an unaccepted failure. Preliminary mode
   with pending matrix, seal or status transition stays pending and cannot
   accept final completion. A supplied authority digest without its designated
   FILE fails, and final mode requires both explicit authority digests.
   In an isolated copy, create the designated matrix-authority FILE while
   omitting its CLI digest, with the canonical matrix first absent and then
   explicitly unaccepted: both cases must fail, not remain pending. With the
   exact digest supplied, a missing canonical receipt still fails; an unaccepted
   receipt is audited and fails its acceptance gate. An accepted matrix without
   any authority must still fail. Ordinary missing-matrix pending behavior is
   allowed only when no authority FILE or explicit identity is present.
2. Derive exactly 764 baseline paths from the captured integration, with 31
   additions and no removals. Omit, duplicate or change a mapped path and fail.
   Change an unmapped current file and fail against the captured baseline.
3. Confirm twelve historical seals and historical INPUT manifests are FILE-only
   reads. Passing an old seal through `--seal`, including through a symlink,
   must fail before any entry is parsed or checked.
4. A new seal must contain the exact sorted unique 795 ordinary paths. Reject
   exclusions, extra paths, aliases and changed current bytes. Final mode
   cannot accept a preliminary seal even when its bytes match.
5. Preserve C01/C02/C05 actual publication projection. An overlay link valid
   only at its native destination succeeds; an unrelated excluded document
   receives no invented projection. Broken native/local links, schema refs and
   outside-fence schema mentions fail. Every verification Markdown file is
   included in both opening and closing inventories.
6. Keep the patched JSON header and runtime14/report6 sets unchanged. Reject a
   pure selection runtime/report include, mixed runtime archive role, excluded
   native include path or missing public header. These anchors complement the
   actual compiler/link/symbol matrix; they are not standalone runtime proof.
7. Require exact 158 outcomes and 238 compilation/dependency identities. Omit
   an old test, new test, example object, ABI variant, link recipe, raw numeric
   row or sanitizer parser capture and fail. Derive row totals from actual
   outputs, including configurations where allocation counts differ. A running,
   failed or wrong-freeze summary/symbol receipt fails even if its rows appear
   complete. Reject a duplicated freeze test name or altered old143 prefix.
8. Require observed 24/214 incremental and 238/0 clean partitions, direct `.o.d`
   evidence and exact captured object/command/frozen-project equality. Historical
   generated/system-byte comparisons must remain explicitly unclaimed. An
   expected-count declaration cannot substitute for actual compile commands.
   Do not accept a missing clean row through the former C02 watcher sidecar.
9. Exercise consistent compiler aliases, missing mandatory tools, contradictory
   raw aliases, changed current bytes and exact external-whitelist equality.
   Repository-local Clang remains mandatory without being called external.
10. An unapproved new C05 allocation difference fails. The four old C02 Clang
    approvals cannot be broadened by test-name prefixes, percentage tolerance,
    unchanged-lowering speculation or a generic root-approved flag.
11. Parsed 39/3/36 baseline and 40/2/36 final rows must agree with explicit
    current ledger/handoff totals and active-card names. A stale footer fails;
    an explicitly historical handoff section does not alter current counts.
12. Final status-only changes require all three exact root-approved diffs and
    explicit approval FILE identity. Reject an unsupported fourth document,
    a no-op approval, a code/schema edit, wrong integration hash or altered
    diff. Final matrix authority must bind the exact canonical matrix hash.
13. Mutating any read file or changing either source/Markdown path inventory
    before receipt publication fails the closing guard. Preserve failed
    outputs and use a new invocation name; never overwrite prior evidence.

Root should first reconcile the proposed matrix field names with its final
reviewed producer. A schema mismatch is an explicit draft issue, not a reason
to weaken a required gate or silently accept a partial native matrix.
