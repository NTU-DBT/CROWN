# CLI process boundary and observation/recovery/query contracts

This continuation adds 518 contracts after v10: 505 from four scoped reviews
and 13 root contracts for the process boundary, regression and registration.
The map reaches 6,153 contracts in 5,384 blocks across 692 maintained files /
159,262 lines / 17,813 blocks. Another 882 selected production blocks need
individual cards (378 include, 504 src, zero apps); test/tool/example gaps
remain separate. Structural maps do not establish semantic correctness.

Start with the [block index](../code_specs/README.md) and
[primitive contracts](../code_specs/primitives.md). Contracts specify usage,
inputs/outputs, ownership/lifetime, invariants, failures and actual cost.
Paper provenance stays in [the review guide](../code_review.md); CLI transport,
C++ ownership, accounting and file protocols are local engineering contracts.

## Two reproduced process failures and a small boundary

The pinned pre-fix CLI returned success for `--version` with stdout directed
to `/dev/full`. A POSIX argument containing byte ff caused strict JSON
diagnostic encoding to throw from a catch body and abort the process. These
failures are retained in the root packet with core dumps disabled.

The original dispatcher is now private `command_main`. Its complete code and
literal stream is preserved apart from that signature and comments. Final
`main` invokes it once, flushes stdout inside its try and changes a successful
status to 2/`io_error` if flushing failed. An existing nonzero status stays
nonzero. Standard exceptions escaping diagnostic bodies receive fixed JSON:
3/`resource_limit` for C++ bad_alloc, 3/`internal_error` otherwise.

The two final catches are necessary process presentation boundaries. All 21
existing component handlers retain their distinct input, proof, resource,
native and durable outcome roles. There is no new query state, retry, observer,
account or per-update wrapper. The added explicit flush happens once per
process. A failed report never undoes native/file effects; stderr failure can
still lose a diagnostic. See the [CLI description](../cli.md) and
[handler dispositions](../code_specs/error_handling.md).

The [maintained process regression](../../tests/integration/cli_process_boundary.py)
launches the real executable: ordinary version/help succeed, both fail with
checked io_error on `/dev/full`, and invalid argument bytes produce valid JSON
and a controlled nonzero exit. A separate private harness compiles the actual
main entry under a renamed symbol and links the real remaining app objects and
libraries. Fixed stack stream buffers are prepared before persistent C++ new
failure is armed. The old entry leaks bad_alloc; the fixed entry returns 3 and
a fixed resource_limit diagnostic while allocation denial remains armed.
This covers C++ allocation failure in that path, not general system/malloc OOM.

## Reviewed boundaries and costs

| Scope | Human inspection result |
| --- | --- |
| All seven CLI files, 113 cards | Existing set-family command admission and independently replayed compiled proof remain separate from diagnostic flags. Tool DOMs, formatting buffers, native owners and durable sinks have distinct lifetimes and limits. |
| Four observation/cost headers, 244 cards | Owning/deep-copy vectors differ from borrowed views and shared handles. Ratio fields are unchecked data; forecasts are not demand admission. Optional observation does not replace mandatory native budgets. |
| Journal/sink-codec/retirement, 70 cards | Full validation/checksum/parse passes and overlapping account buffers are explicit. Checkpoint confirmation hashes validated caller bytes and checks the inode, without rereading it. Retirement removes only the recorded older ckpt/wal/plan files under the durable intent protocol. |
| Query EXPLAIN/context/document, 78 cards | Immutable typed evidence differs from descriptive DTO flags. Capture shares retained proof/model handles but allocates its own report envelope; DOM validation, scalar conversion and format-3 catalog work have real costs. |

The original reviews remain pinned:
[CLI](../../build/verification/cli-entrypoints-human-review-v1/report.md),
[observation/cost headers](../../build/verification/runtime-observation-cost-headers-human-review-v1/report.md),
[recovery codec](../../build/verification/recovery-codec-retirement-human-review-v1/report.md),
[query/context/document](../../build/verification/query-context-document-human-review-v1/report.md).
Historical CLI findings in that draft are superseded by the root fix/probes;
31 affected failure contracts now describe the final process boundary.

Root proves whole-file C++/literal token equality for all comment variants and
complete callable/type block equality. Comment-only scaffolding can split
structural map ranges without changing code. The dispatcher restoration proof
separately excludes only its explicit signature rename and appended wrapper.
No other functional change is introduced by these reviews.

Root also corrects two earlier scalar CMake guard cards whose end-of-file
anchors had followed later appended test groups. They now point to the actual
scalar closing guards before SQL rows declarations. All 101 previously reviewed
CMake commands are byte-identical; this is a semantic anchor correction.

## Verification and preservation

Both strict 22-target builds pass. The selected 26 tests pass in Debug
(111.08 seconds) and ASan/UBSan with leak detection (313.69 seconds), on matching
1,129 maintained input pins with no drift. They cover CLI/workflow/EXPLAIN and
observation/cost/recovery controls. Private final process and persistent-C++-OOM
probes pass in both profiles; allocation denial records two attempts, no escaped
exception, exit 3 and a 66-byte fixed diagnostic. No full 325-test, Release/Clang
or latency claim is made.

Raw terminal LastTest logs are archived. Native inventories record each
profile's actual 40-target link closure, 41 artifacts, 181 C++ objects and 162
metadata files. Main build artifacts remain reusable observed bytes; private
probe binaries and their source/compile/link receipts are preserved evidence.

The [registration audit](../../build/verification/inspection-cli-registration-v1/README.md)
checks that both profiles preserve all 324 prior raw command/property/backtrace
pairs and append only cli_process_boundary. The new test has an O08 label,
120-second timeout and explicit sanitizer environment.

Root evidence and recipes: `build/verification/inspection-cli-v1`.
Seal: `build/verification/human-inspection-v11-progress-v1.json`;
frozen source: `build/verification/human-inspection-v11-source-v1`.
Earlier seals remain immutable; active build directories may be reused after
checkpoint evidence is preserved. Repository-wide human review, W06 work and
full release acceptance remain open.
