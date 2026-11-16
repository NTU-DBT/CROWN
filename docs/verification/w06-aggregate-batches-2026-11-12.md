# Prepared aggregate groups: receiving checks

The [logical batch contract](../aggregate_batches.md) specifies the real
standalone row-ledger authority, touched group proposals, final arithmetic,
ownership, publication and costs. This component does not supply the genuine
source/native/group/session/recovery coordinator required by W06.

| Final source profile | Checks | Result |
| --- | --- | --- |
| Strict GCC C++23 Debug | aggregate_integer_oracle, aggregate_binding, aggregate_runtime, aggregate_sql_oracle | 4/4 pass, 3.60 s |
| Strict GCC C++23 ASan/UBSan with leak checking | Same four checks | 4/4 pass, 12.39 s |
| Test-disabled production Release | Complete default build | Pass |
| Relocated installed Release SDK | Strict public CROWN::aggregate batch consumer | Pass; 216 installed files |

The extended aggregate_runtime test runs four new batch groups before its
unchanged W04 controls. It checks multi-group replacement/deletion, NULL/global
semantics, identical projected values with distinct group keys, rounded-equal
AVG, final count/SUM rejection and retry, duplicate/zero/underflow admission,
work/account limits, covered C++ new failure cuts, allocation-free commit,
abandonment and retained input/program/output ownership. The independent old
integer and SQL oracles continue to exercise the exact arithmetic kernel and
single-row paths; they are not a new randomized physical-source batch oracle.

Root's exact private receiving trial passes before maintained adoption. The
maintained Debug/sanitizer gates then compile and execute the adopted bytes.
Original private proposals remain unchanged. Root isolates four batch-only
counters in BatchMetrics, preserving legacy Metrics/Epoch sizes at 72/160 bytes.
An actual v19 installed-library comparison confirms the same constructor and
five-case allocation counts, selected work and output expectations. Shared
ownership/busy metadata adds 56 fixed accounted bytes; facade size is 40→16.
No CPU speedup, global-heap bound or portable ABI guarantee is claimed.

Independent static review finds no runtime correctness defect in the local
proposal and corrects two descriptions: unhinted destination node insertion
still performs logarithmic typed-key comparisons; an int64 sum needs at most
38 coefficient digits. Root's calling/cost contract and receiving cards carry
those corrections. The single-row SUM policy is retained at compile time;
only batch finalization defers the declared result-range check.

The current public catalog cannot express varying int32 input columns, and W04
rejects their narrowing casts. Constant SUM(integer) and private exact wide
arithmetic controls do not close that end-to-end mixed-sign case. Genuine
source composition, closed group-only contribution authority, static bootstrap,
durable outcomes, checkpoint/recovery and the operational CLI stay open.

Root recipes, source cohorts, archived terminal CTest logs, native and relocated
SDK hashes live in build/verification/w06-aggregate-batch-implementation-v1. Its
12 recorder jobs pass with no in-command source drift; final gates pin 1,132
maintained inputs. The tests retain active assertions. Execution of all 327 tests and a
Clang gate remain open. The separate source-batch v19 checkpoint stays immutable;
the [handoff](../handoff.md) records subsequent work.
