# Separate static review of root's C02 integration driver

Reviewed original: `/tmp/crown-c02-native-integrate.py`, SHA-256
`2b23eacd64b6d63725d619d6b6481cd74cabf9ea745778ec926f379a8a5f43d0`.
An exact copy is retained under `root-drivers/`. This reviewer did not execute
it or any of the gated precursor programs.

The driver requires the author and independent-review package manifest FILE
identities as explicit arguments and validates their entries before copying.
It separately checks the author's input, 38-source and seven-pre-edit manifests.
Its four-column source-map schema matches the publication map:
`overlay_file`, `native_destination`, `origin`, `change`.
It requires a one-to-one map covering every overlay file, exactly 38 destinations,
seven existing files and 31 new files. The expected existing file contents are
checked before a write; source paths must resolve inside the frozen overlay,
destination paths must be canonical and remain in the allowed repository roots.
Verification packages, repository control directories, Refactor and the named
ledger/handoff paths cannot be copied through this map.

Five specific root execution summaries must report `passed`, stable sources and
no errors. Both C01 matrix/source gates must be accepted, and the coherent C02
strict command audit must have passed. The script preserves the original
Refactor FILE identity and all eleven historical source-manifest FILE identities;
it does not recheck historical manifests' old live entries. Its single complete
current-source check is the accepted C01 733-entry seal, after the other gates
and immediately before backups and application.

Seven overwritten files are copied to a dedicated backup and checked. The
accepted C01 seal FILE is copied as history. The integration record retains
source/input/package/review/baseline pins, all mappings, before/after identities
and the driver identity. Each copied destination is checked against its expected
source hash. Historical manifest FILE and Refactor identities are checked again.
On an ordinary caught copy/hash exception, changed destinations are restored
from backup or removed if new, and failure is recorded.

This is a guarded reversible file batch, not a filesystem transaction. It assumes
exclusive application to these paths. It does not promise recovery from process
kill, power loss, a failing backup/record device or an exception during rollback;
newly created empty directories may remain after rollback. These limits do not
change the stated root workflow or authorize concurrent edits. No application
has been performed by this reviewer.

The terminal preparation aggregation, retained under `baseline/`, is FILE
`build/verification/c02-preparation-execution-completion.json`, SHA-256
`4c39ded5d7d09d2802181e476f236c403f8f7533d8606e6fe3f3a53fa58e2d60`.
It resolves the producer sanitizer driver's old hardcoded pending-closure text
from all twelve terminal stages, without rewriting raw evidence. Both normalized
strict/sanitizer sweeps report 38,763 persistent-failure positions and zero
recovered-cleanup positions. This is scoped preparation evidence; it does not
accept the forthcoming native registration or matrix.

No blocking defect was found for the exact frozen-map/exclusive-root use above.
The final author manifest base/shape and source identities must match this review
before invocation. Any changed driver or publication requires renewed review.
