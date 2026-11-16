# Source and evidence map

| Packet file | Origin and use |
| --- | --- |
| `source_audit_revision.py` | Copy of the executed predecessor repair plus exactly `revision.diff`; root invokes this excluded path directly. It has no native destination. |
| `revision.diff` | Exact unified source difference against the unchanged predecessor script, using stable labels. |
| `README.md`, `ROOT_REPRODUCTION.md`, `REVIEW_CASES.md` | New review, invocation and explicitly unexecuted case notes. |
| `input-paths.txt`, `INPUT_SHA256SUMS` | The 843 prior current FILE inputs plus 14 distinct predecessor-receipt/tool-alias inputs; 857 rows. Historical source manifests are FILE inputs only. |
| `source-files.sha256` | Every authored/recorded packet file except itself and the final package manifest. |
| `PACKAGE_SHA256SUMS` | Every packet file except itself. All paths are repository-relative. |

No native, frozen predecessor, root helper, root receipt, ledger or handoff file
is overwritten. The only generated temporary data is the unsorted input path
list under the assigned `/tmp/crown-c02-source-audit-compiler-scope-1/` prefix.
The packet is immutable after its final package hash is sent to root.
