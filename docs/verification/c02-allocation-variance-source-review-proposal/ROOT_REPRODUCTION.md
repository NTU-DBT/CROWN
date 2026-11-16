# Root-only continuation

All paths in checksum manifests are repository-relative or absolute as written;
run checksum checks from `/home/userroot/Codex/CROWN`. Verify the package FILE
identity first, then `PACKAGE_SHA256SUMS`, `PRECOMPILE_INPUT_SHA256SUMS`,
`GNU_ACTUAL_DEPENDENCIES_SHA256SUMS` and `GNU_ARTIFACT_SHA256SUMS`.

`commands.json` contains eight exact argv arrays with repository cwd and no
additional environment overrides. The GNU default compile command already
completed, so reuse its pinned object and do not overwrite its command/log/exit
record. Root may run the remaining seven compiler/link arrays. For a repeat of
the completed GNU compile, choose a new temporary output prefix and retain both
results. All existing paths use `/tmp/crown-c02-allocation-variance-1/`.

No testing-runtime, cached proposal C++ archive or ordinary/sanitized mixture is
used. The header-level probe links no CROWN archive. The real lower probe links
the native production plan, SQL, parser and core archives from the same compiler's
Debug tree. Both compilers use the native Debug option pattern, C++23 and all
six warning/error flags. The JSON header is the current patched native header.

Root should capture each remaining compile/link exit and complete log, retain the
compiler-generated dependency files, and pin all actual source/system headers,
compiler binaries, linked archives, objects and executables. The GNU dependency
pins in this packet are observations from its completed compile; they are not a
substitute for Clang's or the lower consumer's actual dependency records.

Once linked, the exact run argv are the following one-element arrays, with cwd
`/home/userroot/Codex/CROWN` and no environment overrides:

```json
[
  ["/tmp/crown-c02-allocation-variance-1/gcc-default"],
  ["/tmp/crown-c02-allocation-variance-1/clang-default"],
  ["/tmp/crown-c02-allocation-variance-1/gcc-lower"],
  ["/tmp/crown-c02-allocation-variance-1/clang-lower"]
]
```

Keep stdout/stderr and exit codes separately. The default probe must report all
22 forms and exact descriptor checks; the lower probe must report all three
actual candidate calls. Compare counts, requested-size populations and temporary
frees per form/candidate, not merely their final sums. No failure loop runs in
either probe, and no particular compiler difference is asserted by the producer.
Root's native persistent-failure evidence remains the authority for every tested
failure position and unchanged state/results. Any allocation-only review record
must cite both that evidence and the new causal observations explicitly.
