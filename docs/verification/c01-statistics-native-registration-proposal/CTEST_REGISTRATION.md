# Independent CTest registration inventory

The authored expected native count is **131 = 99 retained + 32 added**. This
document and the two name lists were prepared from the preserved original
registration and explicit intended new cases, not by configuring the draft.
Root must compare actual `ctest --show-only=json-v1` output after configuration.
The complete command/source/variant inventory is [registered-ctests.tsv](registered-ctests.tsv).

| Added CTest names | Count | Link boundary and purpose |
| --- | ---: | --- |
| `statistics_capture`, `statistics_capture_exceptions` | 2 | Production runtime; bounded storage distributions and allocation recovery. |
| `statistics_owner`, `statistics_owner_exceptions` | 2 | Production runtime; actual owner scopes and allocation recovery. Only ordinary owner assertions additionally link the independent reference evaluator. |
| `statistics_collection` | 1 | Testing runtime plus private runtime headers; collector numeric/protocol/saturation regressions. |
| `statistics_workload`, `statistics_workload_exceptions` | 2 | Testing runtime; integrated hooks and configure/update/mode failure sweeps. |
| `statistics_combined_production`, `statistics_combined_testing` | 2 | Matching runtime only; nine groups of joint state/workload capture. |
| `statistics_combined_exceptions_production`, `statistics_combined_exceptions_testing` | 2 | Matching runtime only; same-owner joint allocation recovery. |
| `statistics_reports_production`, `statistics_reports_testing` | 2 | Matching report library; one temp-corpus producer plus independent schema/semantic/legacy/mutation checker and publication-field rejection. Testing adds actual collector saturation fixture. |
| `statistics_report_exceptions_production`, `statistics_report_exceptions_testing` | 2 | Matching report library; four distinct allocation sweeps. |
| `statistics_runtime_only_production`, `statistics_runtime_only_testing` | 2 | Matching runtime only, without reference or any report/query-explain library. |
| `statistics_scalars` | 1 | Production runtime; seven typed scalar/constraint groups. |
| `statistics_delta_fifo`, `statistics_delta_fifo_eager`, `statistics_delta_fifo_incremental`, `statistics_delta_fifo_root_first`, `statistics_delta_fifo_anchored` | 5 | One production delta consumer with census enabled, FIFO; unchanged independent A04/prefix assertions. |
| `statistics_replay_fifo`, `statistics_window_fifo` | 2 | Production enabled replay and independent window list-oracle consumers, FIFO. |
| `statistics_delta_lifo`, `statistics_delta_lifo_eager`, `statistics_delta_lifo_incremental`, `statistics_delta_lifo_root_first`, `statistics_delta_lifo_anchored` | 5 | One production delta consumer with census enabled, LIFO. |
| `statistics_replay_lifo`, `statistics_window_lifo` | 2 | Production enabled replay and window consumers, LIFO. |

The six policy executables link `crown_runtime` and `crown_reference`; none links
the testing runtime. `CROWN_STATISTICS_ACCEPTANCE` is consumer-local, and only
the three LIFO consumers define `CROWN_STATISTICS_LIFO`. Existing tests
`delta_runtime*`, `delta_replay`, and `window` preserve their macro-absent behavior
and original commands. There are no redundant new registrations of those off
cases. The historical generalized diagnostic and baseline generator remain
excluded, since their facts are already asserted by registered tests and their
actual v2 bytes are checked in.

All new consumers use `-UNDEBUG` to keep the numeric collector's assertions
active in optimized builds. Probe definitions flow from the existing testing
runtime's public compile definition, not a project-wide macro. Fault consumers
are separate CTests from report generation/schema checking. Each new CTest has
`LABELS C01` and `TIMEOUT 900`; the existing final sanitizer environment loop
still applies to the entire registered suite.
