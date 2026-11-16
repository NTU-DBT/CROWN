# `tools/verify_memory_report.py` — block usage map

[Source](../../../../tools/verify_memory_report.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `d79d893919ee35bd16b2273951afff4088b6fa027bc4a0737f53fd5673a3f3c7`. 53 lines partitioned into 3 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–18](../../../../tools/verify_memory_report.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 19–20](../../../../tools/verify_memory_report.py#L19) | Callable definition: def usage_sum(values): | calls sum; returns {k:sum(v\[k\] for v in values) for k in \['allocations','requested_bytes','payload_bytes'\]}; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 21–53](../../../../tools/verify_memory_report.py#L21) | declares callable signatures; declares values/defaults or compile-time conditions. | 8 loop sites · [reviewed contract](#b0003) |

## B0001

[Lines 1–18](../../../../tools/verify_memory_report.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run native operator-memory export/schema/account identity checks at module import. |
| inputs / outputs | argparse --executable, reads/checks memory schema, then temporary native --export-directory and eight-report loop. |
| invariants | No __main__ guard; importing launches native producer. Normal assertions required. Exact ledger sums are finite evidence, not process RSS or full allocator overhead accounting. |
| ownership | Owns schema/validator/parsed reports/maps; TemporaryDirectory owns exported files, child native memory separate. |
| failure | Usage/import/schema/subprocess/assert failures propagate; temporary context cleans exported directory. |
| cost | Whole schema/read/export and eight full reports; no local subprocess timeout, check=True enforces exit. |
| Design | [tools/verify_memory_report.py](../../../../tools/verify_memory_report.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/memory-report-v1.schema.json](../../../../schemas/memory-report-v1.schema.json), [tests/unit/operator_memory_report_test.cpp](../../../../tests/unit/operator_memory_report_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0002

[Lines 19–20](../../../../tools/verify_memory_report.py#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def usage_sum(values):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sum three independent usage fields across ledger entries. |
| inputs / outputs | Reiterable values collection in; allocations/requested_bytes/payload_bytes sum dict out. |
| invariants | Iterates values separately per field; actual callers pass lists or dict_values, not one-shot iterators. Counts/bytes remain distinct dimensions. |
| ownership | Borrows entries, owns three-field dict and integer sums. |
| failure | Missing/type/arithmetic/OOM errors propagate. |
| cost | Three O(entries) passes, big-integer sum costs; no native ledger traversal. |
| Design | [tools/verify_memory_report.py](../../../../tools/verify_memory_report.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/memory-report-v1.schema.json](../../../../schemas/memory-report-v1.schema.json), [tests/unit/operator_memory_report_test.cpp](../../../../tests/unit/operator_memory_report_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |

## B0003

[Lines 21–53](../../../../tools/verify_memory_report.py#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
with tempfile.TemporaryDirectory(prefix='crown-operator-memory-') as temporary:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate eight native memory exports against schema and independently summed owner/purpose/lifetime/arena identities. |
| inputs / outputs | Native exporter path in; eight JSON files under temporary directory out then read/validated. |
| invariants | Checks unique attribution, current≤peak≤limit, allocations-frees, delta coordinator sentinel not factor attribution, table/arena slot partitions and noncommitted empty exports. |
| ownership | TemporaryDirectory removes output on failure/success; owns current parsed report/owner maps/sum lists, no retained persistent pack. |
| failure | Subprocess check=True or schema/assert/IO errors escape; no timeout/byte cap here. |
| cost | One native export process then full report/table/owner/arena scans and repeated sums; files+DOM ordinary process resources. |
| Design | [tools/verify_memory_report.py](../../../../tools/verify_memory_report.py), [docs/memory_reports.md](../../../memory_reports.md), [schemas/memory-report-v1.schema.json](../../../../schemas/memory-report-v1.schema.json), [tests/unit/operator_memory_report_test.cpp](../../../../tests/unit/operator_memory_report_test.cpp), [CMakeLists.txt](../../../../CMakeLists.txt), [docs/code_review.md](../../../code_review.md) |
