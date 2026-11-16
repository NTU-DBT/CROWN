# Root-only targeted diagnostic

After verifying the advertised package/input/link FILE identities, root runs:

```sh
env LC_ALL=C bash docs/verification/c05-selection-independent-cache-diagnostic-proposal/ROOT_BUILD.sh \
  /tmp/crown-c05-selection-independent-cache-diagnostic-1
```

The exact compiler/link argv are recorded by that recipe. Retain the new full
dependency record and actual input hashes before running:

```sh
env LC_ALL=C /tmp/crown-c05-selection-independent-cache-diagnostic-1/bin/selection_cache_independent_diagnostic \
  /home/userroot/Codex/CROWN
```

Retain stdout, stderr and exit status separately, and repeat the current guards
afterward. A diagnostic exit 1 at the unchanged failed assertion is expected if
the original rejection reproduces; it is not a passing acceptance test. Read
the final marked API call and its status before deciding whether the cause is
an invalid fixture request or an implementation defect. Do not continue by
weakening literals or silently treating the rejection as a cache miss.

Historical input manifests are pinned as FILEs only. This packet never checks
the original 255-entry manifest against changed live files. Its current input
scope is independently projected from the actual original cache dependency
record, relevant held implementation/public headers, literal fixture files,
matching archives/compiler and terminal root receipts. Root must add the actual
new diagnostic dependency rows; an old record does not claim a new compilation.
