# Future root authority records

These are required field contracts, not issued approval records. Root creates
the actual records after reviewing their exact evidence. This package does not
write an authority, alter metadata or choose a future approval digest. Both
designated authority files are immutable once used and are closing-hashed by
the source audit. Their actual SHA-256 identities are invocation arguments.

## Matrix authority

The designated path is
`build/verification/selection-matrix-audit-authority.json`.

| Field | Required meaning |
| --- | --- |
| `card`, `reviewer`, `decision` | `C05`, `root`, `accepted_evidence_only_auditor` |
| `native`, `execution` | Exact count/digest objects from the actual C05 freeze |
| `canonical_matrix` | `{path,sha256}` for `build/verification/selection-matrix-evidence-audit.json`, bound to the reviewed final receipt |
| `auditor` | `{path,sha256}` for the exact independent auditor source inside its reviewed verification package; matches the matrix receipt |
| `package_manifest` | `{path,sha256}` for that auditor's complete package manifest; membership is exact and includes `auditor` |
| `allowed_external_file_pins` | Exact canonical absolute external-path-to-digest map observed in the final matrix's raw inputs, including mandatory external tools and current clean system inputs |

The matrix receipt is written before this root authority. The independent
matrix auditor must not read this later source-audit authority as an input to
the receipt whose hash it approves. Its own reviewed allocation decisions are
separate prior inputs. Root approves exact new C05 differences individually;
the old four C02 Clang approvals retain their original scope.

Package members are current immutable auditor files. Historical INPUT manifest
files within that package are hashed as FILEs only; this source auditor does
not interpret their rows as current native source claims. The matrix's own
explicit raw-evidence/input map is a separate current evidence contract.

## Completion metadata approval

The designated path is
`build/verification/selection-completion-metadata-approval.json`.

| Field | Required meaning |
| --- | --- |
| `card`, `reviewer`, `decision` | `C05`, `root`, `accepted_verification_status_only` |
| `native`, `execution` | Exact unchanged count/digest objects from the actual C05 freeze |
| `integration_record_sha256` | Exact accepted C05 integration FILE identity |
| `status_document_changes` | Exactly `README.md`, `docs/native_build.md`, and `docs/selection.md`, with the row fields below |

Each status-document row has `reviewer:root`,
`decision:accepted_verification_status_only`, `change_kind:verification_status_only`,
`before` equal to the published mapping's applied hash, `after` equal to the
current file hash, and `diff_evidence:{path,sha256}`. The before and after hashes
must differ. The retained diff must exactly equal Python `difflib.unified_diff`
of the frozen publication source and current native guide, preserving line
endings, with labels `<native-path>:published` and `<native-path>:verified`.
The evidence path stays within `build/verification/`. Semantic classification
as status-only is root's explicit review, not a prose heuristic in the auditor.

Ledger, current handoff, the evolving verification packet and live native jobs
registry are read and closing-hashed at final invocation. Their required final
state is C05 verified, 40 verified/2 in progress/36 not started, with A02/O06
still in progress and the full goal active. They are not immutable INPUT rows
in this package. The final transaction must coordinate their hold with all
verification Markdown until the source audit publishes its result.

## Order and failure behavior

1. Complete the exact five native configurations and independent matrix audit.
2. Root reviews and writes the SHA-bound matrix authority.
3. Root prepares the three concrete status-only edits and their exact approval,
   performs its reversible metadata transition, and writes the new795 source
   seal. The freeze's native/execution bytes remain unchanged.
4. Invoke this frozen source auditor with `--final` and both explicit authority
   digests. Any malformed, missing, stale or mismatched authority fails.
5. Only after a passed final source audit does root write a completion checkpoint
   citing it. That checkpoint is deliberately absent from all prerequisites.

Preliminary mode can observe missing future gates as pending. An explicit
authority digest without its designated file is an error. Existing metadata
approval is never silently ignored; an accepted canonical matrix always needs
its explicit reviewed authority. No pending receipt advances card status.
