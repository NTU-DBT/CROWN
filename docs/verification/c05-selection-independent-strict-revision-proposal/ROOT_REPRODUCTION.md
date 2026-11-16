# Root-only corrected strict closure

Verify the advertised package FILE identity, its entries and the new input/reused
artifact manifests. Do not run the historical 255-entry input check. Root then
compiles and links only the two changed consumers:

```sh
bash docs/verification/c05-selection-independent-strict-revision-proposal/ROOT_BUILD.sh \
  /tmp/crown-c05-selection-independent-strict-revision-1
```

The recipe preserves C++23, `-O3 -UNDEBUG`, all six strict warning flags and full
`-MD` dependencies. The original shared fixture is included read-only; no testing
macro is defined. The byte consumer remains pure (no runtime/report archive).
The focused OOM consumer uses the production selection/ranking/runtime bridge
and the same matched native Release plan/SQL/core/parser archives as the three
reused consumers. Root must retain/hash actual new dependency rows before tests.

All five exact execution argv, with `LC_ALL=C`, are:

```sh
/tmp/crown-c05-selection-independent-strict-1/bin/selection_public_independent /home/userroot/Codex/CROWN
/tmp/crown-c05-selection-independent-strict-1/bin/selection_cache_independent /home/userroot/Codex/CROWN
/tmp/crown-c05-selection-independent-strict-1/bin/selection_resources_independent /home/userroot/Codex/CROWN
/tmp/crown-c05-selection-independent-strict-revision-1/bin/selection_binding_independent
/tmp/crown-c05-selection-independent-strict-revision-1/bin/selection_publication_fault_independent /home/userroot/Codex/CROWN
```

These are proposed root invocations, not executed author results. Keep outputs,
exit statuses and source/artifact guards separately. Any test failure retains
its exact original oracle; it is not permission to relax a literal or failure
atomicity condition. The pending sanitizer metadata packet must later bind this
two-source revision plus the three unchanged original sources, using matching
sanitized implementation/native archives and freshly compiled consumers.
