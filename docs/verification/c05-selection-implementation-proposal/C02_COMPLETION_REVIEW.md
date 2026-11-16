# Independent source review of the C02 completion transaction

Reviewed on 2026-11-07 at root's explicit request while the C05 implementation
overlay was held. This record does not execute or modify the helper, mark C02
verified, approve a live matrix, or alter any native/ledger/handoff file.

The reviewed helper is `/tmp/crown-c02-completion-transaction-v1.py`, SHA-256
`d942dd5c877aaf36d6323f50e71a3451a3b3c735c13364403bb09e9e8998b713`.
The final native matrix was still pending at review time. Findings were sent
promptly to root; any corrected v2 requires its own identity/recheck.

## Findings

1. **P2: one current guide opening remains falsely pending after success.**
   `update_guides()` updates the C02 section of `docs/native_build.md`, but does
   not replace its opening at lines9–11, which says the API is prepared for
   integration and the143-test matrix remains pending. The same resulting file
   then says the registration is verified and all143 tests pass. Add an exact
   replacement for this opening within the existing three-guide status-only
   scope. The source auditor binds approved diffs; it explicitly does not infer
   the prose semantics and therefore cannot discover this contradiction.

2. **P2: created-artifact tracking starts after the write succeeds.**
   `new_text()` writes directly to a new final path, while its caller appends
   that path to `created` only after return. A partial write/interrupt can thus
   leave an untracked canonical approval, seal, packet or guide-diff file when
   the exception branch restores the five metadata files. This does not affect
   the normal rejected-audit path, but violates the advertised complete
   rollback/failed-artifact retention for that I/O failure boundary. Register
   intended-new paths before writing, or stage and atomically rename while
   tracking both paths. Preserve existing-artifact refusal semantics.

3. **P3: timeout diagnostics lose partial subprocess output.**
   `subprocess.run(..., capture_output=True, timeout=600)` can raise
   TimeoutExpired before the normal stdout/stderr files are written. The
   exception receipt records `repr(exc)` but not the captured partial streams.
   Canonical audit files are moved if present, yet useful timeout evidence can
   disappear. Retain the exception's output/stderr in the attempt, with explicit
   text/bytes handling. No timeout occurred in this review; this is a direct
   exception-path inspection finding.

The handoff also names strict3 as the current C05 checkpoint although root has
now completed targeted4. Use checkpoint-neutral wording and retain the actual
jobs record as authority. This is a minor metadata correction, not a native
source or matrix issue.

## Sound inspected boundaries

Preflight requires the exact current C02 freeze FILE, unchanged native and
execution per-file maps, immutable historical manifest FILE identities and
integration receipt. It requires a final accepted canonical matrix with no
errors/pending entries, the exact reviewed auditor/package/authority boundary,
the narrow allocation approval and all five terminal143-test summaries with
matching before/after native/execution fingerprints. No pending SAN summary
can satisfy these checks.

The source seal uses764 unique sorted safe path names. The final source auditor
independently recomputes the ordinary inventory as the prior733 path names plus
the31 reviewed new native destinations, rejects removals, checks every current
seal hash and exact native/execution path sets, and verifies mapped/unmapped
ownership. Old historical manifest entries are used only for path inventory,
not checked against changed native contents. The preliminary inventory is not
treated as the final source-content authority.

The helper changes exactly three guides plus ledger/handoff metadata. The
guide replacements are exact-count guarded. Native C++/headers, CMake, tests,
schemas, tools, vendor header and Refactor remain in the held freeze. For normal
exceptions after staging, original guide/control bytes are restored before
canonical failed artifacts are moved into the preserved attempt directory.
Source audits are invoked only after provisional metadata and the official seal
exist; accepted final audit precedes the completion checkpoint. Existing final
artifact and attempt paths are refused instead of overwritten.

Ledger parsing requires78 distinct cards, starting38verified/3in_progress/
37not_started and C02in_progress/C05not_started. The staged result changes only
C02 to verified, resulting39/2/37 with C05 still not_started. The original full
goal and open A02/O06/C03/S05/release boundaries remain explicit.

There is no circular completion hash: guide status text links to the packet;
the764 seal hashes ordinary sources, excluding controls and new verification
artifacts; the packet quotes that seal; the final auditor hashes source,
approval, packet and controls without reading the completion checkpoint; only
after acceptance does the checkpoint pin the audit and final metadata. The
receipt then pins the checkpoint. The audit's read-pin and path-inventory
closing guards reject changes observed during its run.

## Exact inspected inputs and limits

| File | SHA-256 |
| --- | --- |
| source_audit_revision.py in c02-source-audit-compiler-scope-revision-proposal | 24ba9bd723ead31073eb7287b94a25990e7fcf271baff9a353171d9e0b9895b3 |
| ranking-source-auditor-compiler-scope-authority.json | 6985134aa431feaab42f46d88152a88be0f50b85beb87851fd267796296c0392 |
| ranking-preliminary-sources.sha256 | 932835122475e5de1c93bb5b950c12c896245b8e9e7fc2328610ddb2a2e02476 |
| ranking-allocation-review-clang-guarantee-v1.json | 612f174cf314ab5a64629d91f35049bd0ccc6440b60da7ab483c3211a9aee175 |
| README.md before transition | e3aa4a39e3640980e9c58366212dc0cf46aa1b6afdb236fde9daacd949884a69 |
| docs/native_build.md before transition | 6d76582ede1eb5283d181c48d1f336cf64c2bb0932e73a4e6befdaf6b507b296 |
| docs/ranking.md before transition | de202a55c6351fe6759078b33a528c3bfbaa77dfc7a31646734032989eb1279e |
| docs/task_ledger.md before transition | c59306f6d33140831d3173eba1de0890a9f26c3841c3aa42161db195cb10fc30 |
| docs/handoff.md before transition | 1cc83ee6d53a092944e995bf596f92336eb87bbefa400129d6bac0c1a9ff7356 |

Inspection read/hash operations only. No helper, auditor, compiler, test,
Python checker, CMake/CTest/nm or root-job polling was performed. I did not
independently execute rollback faults, validate terminal SAN outcomes, or claim
all dynamic prerequisites already hold. The source review requires correction
of the current-guide contradiction and the documented exception-path gaps
before treating v1 as the final completion transaction.
