# Evidence-only source map

No file maps to a native source, tool, test, schema, CMake or public documentation
destination. Execute the sealed proposal auditor directly; do not replace any
O07 or root-owned script.

| Proposal file | Role |
| --- | --- |
| `audit.py` | New standalone evidence-only C01 auditor. |
| `PINNED_INPUTS.json` | 92 fixed input identities checked by that auditor. |
| `allocation-review.example.json` | Intentionally invalid shape example, never an approval. |
| `README.md` | Audit contract, retained limits and unexecuted author status. |
| `ROOT_REPRODUCTION.md` | Exact root invocation and review/output contract. |
| `source-files.sha256` | Hashes of the auditor and its two data/example files. |
| `INPUT_SHA256SUMS` | Standard checksum form of the 92 pinned inputs. |
| `PACKAGE_SHA256SUMS` | Whole proposal seal, excluding itself. |

The root-owned matrix, clean-adapter and symbol scripts are inputs only. The
historical O07 auditor is read as a design pattern and pinned; it is neither
imported, modified nor run. New matrix outputs are read only after designated
terminal records qualify. All audit outputs must use a new designated
`build/verification/statistics-matrix-*audit*.json` path or the dedicated
`/tmp/crown-c01-audit-` prefix and are created only when root invokes the script.
