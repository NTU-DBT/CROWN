# `tools/prepare_workflow_input.py` — block usage map

[Source](../../../../tools/prepare_workflow_input.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `9860368c32f938828d5841741e1871269e1857f1dda956d1e400e0c852bd3fba`. 27 lines partitioned into 3 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../tools/prepare_workflow_input.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 7–24](../../../../tools/prepare_workflow_input.py#L7) | Callable definition: def main(): | calls len, ValueError, Path, read_bytes; returns 0; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 25–27](../../../../tools/prepare_workflow_input.py#L25) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |

## B0001

[Lines 1–6](../../../../tools/prepare_workflow_input.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the installed helper for binding a small JSONL template to the actual canonical catalog digest. |
| inputs / outputs | Imports Path/hashlib/json/subprocess/sys and guarded main; no native command at import. |
| invariants | Catalog normalization authority comes from crown canonicalize-catalog; adding a digest is not full event/source/sequence validation. |
| ownership | Owns imports; later bytes/DOMs/serialized lines/captures are ordinary Python process memory. |
| failure | Import errors propagate before CLI handler. |
| cost | Fixed import setup; file/native work is only in main. |
| Design | [tools/prepare_workflow_input.py](../../../../tools/prepare_workflow_input.py), [docs/cli.md](../../../cli.md), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [schemas/physical-update-v1.schema.json](../../../../schemas/physical-update-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 7–24](../../../../tools/prepare_workflow_input.py#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind all template events to a native-canonical catalog SHA before exclusively writing a bounded output. |
| inputs / outputs | Exactly CROWN/CATALOG/TEMPLATE/OUTPUT args; reads full template, invokes native canonicalize-catalog, adds/compares catalog_sha256, writes new JSONL and prints count. |
| invariants | Checks template≤8MiB after full read and output≤16MiB after full encode. Requires each nonblank-as-coded line parse to object and existing digest absent/equal; no full semantic update/sequence check. |
| ownership | Owns complete template bytes, captured canonical catalog, all parsed records/serialized lines and final joined UTF8 output; output handle closes via context. |
| failure | Wrong args/size/digest/object raise; native check=True captures no timeout/output-byte cap. Exclusive output open follows all transform checks; IO failure can retain partial new file. |
| cost | Full input read/decode/JSON parse, one native subprocess, complete canonical hash and per-record reserialization; several full-output temporaries before byte limit is enforced. |
| Design | [tools/prepare_workflow_input.py](../../../../tools/prepare_workflow_input.py), [docs/cli.md](../../../cli.md), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [schemas/physical-update-v1.schema.json](../../../../schemas/physical-update-v1.schema.json), [docs/code_review.md](../../../code_review.md) |

## B0003

[Lines 25–27](../../../../tools/prepare_workflow_input.py#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__=='__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter the input-binding helper only when executed as a script. |
| inputs / outputs | __name__ guard invokes the actual entry point; arguments/results follow that entry point. |
| invariants | This guarded block is inactive on normal import; it grants no schema/proof/native authority beyond completed checks. |
| ownership | Entry point owns its argument/packet/process temporaries; this wrapper does not create a separate native account. |
| failure | Catches Exception, prints text and exits1; main SystemExit result is not swallowed. No input mutation/cleanup of partial new output. |
| cost | Main conversion/one native subprocess plus fixed error presentation. |
| Design | [tools/prepare_workflow_input.py](../../../../tools/prepare_workflow_input.py), [docs/cli.md](../../../cli.md), [cmake/CrownInstall.cmake](../../../../cmake/CrownInstall.cmake), [schemas/physical-update-v1.schema.json](../../../../schemas/physical-update-v1.schema.json), [docs/code_review.md](../../../code_review.md) |
