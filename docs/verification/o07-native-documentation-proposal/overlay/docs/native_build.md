## Native EXPLAIN

Build the native `crown` target, then use the EXPLAIN dispatcher:

```sh
cmake --build --preset debug --target crown --parallel 2
build/debug/crown explain --help
```

The command forms are:

```text
crown explain {physical|runtime|session} PLAN.json [OPTIONS]
crown explain {query|progress} DOCUMENT.json [--work N] [--height-policy strict|best-found]
crown explain replay DOCUMENT.json --certificate FILE [--work N]
```

Reports support `--format text|json|dot|tree-json` and `--max-bytes N`. Runtime
and session reports accept `--observe off|counters|timed|trace`; the default is
`timed`. A work quantum passed to `progress`, `query`, or `replay` is an
explicit producer operation. Capturing or encoding the resulting report does
not advance that producer. See [observability.md](observability.md) for output
and accounting details.
