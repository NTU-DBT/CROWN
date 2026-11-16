# C02 source-auditor independent review

The executed root draft is preserved byte-for-byte as `reviewed-root-draft.py`,
SHA-256 `bb8c62824c1c678c0f75532aae203db594fd9983ca5b208d866721f64534aeb5`.
Its preliminary receipt remains unchanged at
`build/verification/ranking-source-preliminary-audit-attempt-1.json`, SHA-256
`1a47f1095c3b7c33ef4f00a0b2c0c0ed689612077ee3959f0adaf31dcd8ceefd`.
That receipt reports 764 ordinary files, zero errors and two pending final gates.
This reviewer did not execute either helper, a syntax checker, a project program,
compiler, CMake, CTest, symbol command, process poll, network or git command.

Static review found two concrete final-acceptance gaps: the fresh integration
ownership record was consumed without binding its FILE hash to the freeze, and
the final acceptance expression did not require `--final`. The latter could
skip final packet/handoff/three-guide checks once the matrix, official seal and
verified ledger existed. The original draft is not approved for final use.

Additional checks were incomplete: status-change entries were validated only
when bytes differed; final metadata depended on a mutable completion checkpoint;
the external whitelist could be enlarged/overridden without exact observed-set
reconciliation; the matrix consumer checked compile counts but not the complete
214 source/dependency identity sets and their required raw bindings; and inline
documented schema paths were not scanned. A utility hash failure also recorded
an error but continued to import that utility. Malformed/missing evidence could
exit without a failure receipt. None of these findings changes the preserved
preliminary result or implies that its then-current source bytes were wrong.

`source_audit_revision.py` and `revision.diff` propose a separate repair. It:

- Requires the C02 integration FILE hash from the immutable current freeze,
  checks 38 distinct destinations with 31 additions, and binds the C01 publication
  namespace record to its preserved FILE identity. It compares all 705 current
  execution hashes, all 648 native hashes and their aggregates. The ordinary
  inventory remains exactly 733 prior pathnames plus 31 additions, with no removal.
  Unmapped bytes use the fresh captured integration baseline; mapped bytes use
  publication ownership and only the three explicit root-approved status changes.
- Requires explicit final mode, an official current seal, all 78 original ledger
  IDs, phase counts of 38/3/37 before completion or 39/2/37 after completion, and
  the existing C01/O07/C05 boundaries. Final evidence citations and the active
  full-goal handoff remain required. It changes no ledger or handoff.
- Retains FILE-only checks for all eleven historical seals. Reading the C01 seal
  for its 733 pathnames never evaluates its old checksum entries against changed
  native files. The current C02 seal is the only source seal whose entries are
  checked as current content.
- Restores C01's documented schema-path scan outside fences, including inline
  code and explicitly declared package-relative bases. Both C01 and C02 published
  Markdown copies resolve links/mentions in their native publication namespace.
  The existing local-link checks, 29 actual schemas, local reference resolution
  and five closed report schemas remain in place.
- Binds the exact reviewed matrix auditor/package, current freeze, closing source
  guard, five terminal configurations, all 143 ordered outcomes/commands, observed
  numeric-row populations, exact 214 target/source and dependency identities,
  generated links, actual fresh/cached compiler populations, all nine symbol roles
  and sanitizer parser capture to their raw FILE pins. It does not rerun the
  matrix's compiler/parser/numeric algorithms or invent a numeric-row total.
- Requires the authority's canonical external whitelist to equal the observed
  external raw-pin map exactly. Frozen helper/compiler/watcher values cannot be
  overridden. A root-reviewed allowance remains a literal FILE identity, never
  permission to import or execute that file.
- Reads an immutable `ranking-completion-metadata-approval.json`, validates all
  three guide entries with explicit root decisions and exact before/after bytes,
  and optionally binds an actual canonical diff. It never reads the later mutable
  completion checkpoint. Root classifies prose as status-only; the helper checks
  that classification's precise byte scope rather than guessing prose semantics.
- Stops before importing a changed utility, rejects duplicate JSON keys, retains
  read pins and checks them again before publication, and writes an unaccepted
  failure receipt for malformed/missing evidence. Output files are created
  exclusively. Default/preliminary mode cannot return final acceptance.

The proposed revision has been reviewed statically against the frozen matrix
schema, including the separate dependency-alias revision. Root must review and
execute it before treating any result as accepted. The matrix's allocation-only
differences remain separate explicit root decisions; this packet approves none.
The sanitizer/final matrix and final metadata gates are not closed by this review.

This reviewer wrote the earlier independent eight public/three integer fixtures
and the matrix auditor, but did not write the ranking implementation or the root
source-auditor draft. The changes here are authored repairs, not a claim of a
second independent implementation review. Root reproduction and the two authority
record contracts are in `ROOT_REPRODUCTION.md`. No native or prior frozen file
was changed; only this new review packet and its distinct temporary hash logs were
written.
