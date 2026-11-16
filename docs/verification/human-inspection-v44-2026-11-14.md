# V44 — test instrumentation and fixture usage specifications

V44 adds **23 scoped cards in four test sources**, covering **268 previously
structural source lines**. The [source index](../code_specs/README.md) now has
**16,717 contracts in 14,301 blocks**, across 751 files /172,040 lines /19,412
blocks. Selected callable/type/inline-cluster gaps remain zero, including all
5,461 selected test regions. Another **5,111 structural blocks in
670 files /15,137 lines** still need appropriate
human disposition. These counts do not certify every existing comment.

| Source | New cards |
| --- | ---: |
| [maintenance_cost_owner_exception_test.cpp](../code_specs/files/tests/unit/maintenance_cost_owner_exception_test.cpp.md) | 4 |
| [memory_account_contract_test.cpp](../code_specs/files/tests/unit/memory_account_contract_test.cpp.md) | 10 |
| [runtime_observation_test.cpp](../code_specs/files/tests/unit/runtime_observation_test.cpp.md) | 7 |
| [workload_statistics_test.cpp](../code_specs/files/tests/unit/workload_statistics_test.cpp.md) | 2 |

## Source and performance findings

Allocation probes describe exactly which replacement allocation forms they
intercept. Attempts can include failures; requested bytes differ in coverage from
account charges and do not measure RSS. The fixed 2,048-record trace uses bounded
linear searches, has enabled and overflow cases, and can remove a tracked address
after tracing stops. No general constant-time or whole-heap claim follows.
These probes are test-executable machinery; this batch changes no production path.

Ref-qualified accessors reject direct borrows from temporary expressions. Their
static assertions do not keep a saved pointer from a named owner alive. Snapshot
type assertions check API shape, while runtime capture can separately allocate and
throw. Defaulted out-of-line destruction instantiates the accounted deleter with
a complete, nothrow-destructible payload; a fixture's closing brace executes no
cleanup. Synthetic clock ticks are not CPU measurements.

The self-join fixture ignores payload when binding query variables, while full
physical row identity still includes that payload. Distinct physical rows can
support one projected answer. [Semantic contract](../semantics.md) and
[paper/design context](../code_review.md) distinguish those guarantees from test
setup and engineering instrumentation. Cards link to their material callers and
implementations. Existing cleanup catches remain where they restore a test flag
or release acquired storage; no new handler or inspection abstraction is added.

## Review and corrected audit

A Luna Max author and a separate Luna Max peer reviewed all seven fields. Root
read all 268 selected lines, the nine lines excluded from the initial scope,
adjacent context and targeted material callers/implementations, then all 161
original fields, 18 peer amendments and 2
root amendments. This is not a fresh read of all 6,151 lines in the four files.
Exact field replay preserves all **16,694 older cards** and source geometry.
The original 28-region proposal is retained; five pure fixture-closing regions
remain in the global structural goal, with separate concise dispositions.

An independent structural audit pinned the pre-adoption remainder: 5,134 blocks,
670 files /15,405 lines, exact key digest
`53da69e093e7b931d1628649e353de589fe04e71b44bae8fba8b2cdfdbfdb40d`.
Root caught its initial lexer treating C++ numeric separators as quotes. The
original sealed packet is preserved with an explicit classification limitation.
A separate amendment aligns its lexer with the established source-map lexer,
tests separators, character/string forms and literal boundaries, and recomputes
the categories. Root independently checks that amendment and subtracts exactly
the 23 adopted IDs. Categories guide review; they are not semantic acceptance.
The maintained mapping/checker tools are unchanged.

All **1,196 native inputs and 355 production paths equal V43 byte for byte**.
V44 has **no native build, CTest, SDK, benchmark or release execution** and adds
no runtime allocation, wrapper, branch or checkpoint. Completed generated-map and
current-guide checks validate local references; external URLs are skipped.
V41's affected strict Debug and ASan/UBSan/leak results retain their dated scope.
The [receiving packet](../../build/verification/inspection-structural-review-v44-v1/README.md)
pins both semantic reviews, both audit packets and the exact final remainder.

Latest seal: build/verification/human-inspection-v44-progress-v1.json; frozen
source: build/verification/human-inspection-v44-source-v1. Exact previous handoff:
[V43 history](../handoff-history-v43-2026-11-14.md). Full Refactor work stays active:
**57 verified /1 in progress A02 /20 not started**. W06 retains its bounded
profile; A02/C04/B01, R2 retirement, V04 and release gates remain open.
