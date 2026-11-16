## Native EXPLAIN

The native CLI can report validated physical plans, runtime and session state,
and exact-search or certificate-replay progress with `crown explain`. These are
read-only diagnostic reports: capture does not advance a runtime or search,
and it does not add cost-ranking authority. See the
[observability guide](docs/observability.md) for modes, report scope, and
examples.
