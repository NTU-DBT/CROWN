# Root-only cache correction reproduction

Verify the final package/input/link FILE identities, then build exactly one
fresh consumer with the held production closure:

```sh
env LC_ALL=C bash docs/verification/c05-selection-independent-cache-correction-proposal/ROOT_BUILD.sh \
  /tmp/crown-c05-selection-independent-cache-correction-1
```

The recipe retains C++23, `-O3 -UNDEBUG`, all six strict warning flags and full
`-MD` dependencies. It links the held strict3 selection/ranking/runtime
production bridge and matching native Release plan/SQL/core/parser archives.
No testing-runtime or report archive is used. It records each command and
status, checks current inputs before/after, and never runs a binary.

After a successful build and retention of the actual dependency rows, root runs:

```sh
env LC_ALL=C /tmp/crown-c05-selection-independent-cache-correction-1/bin/selection_cache_independent \
  /home/userroot/Codex/CROWN
```

Retain stdout, stderr, exit status and before/after source/artifact guards. A
passing cache run must reach all five original groups, including the later
current-owner/reset/rebuild group that the original failure prevented. The
other independent consumers remain distinct evidence and must not be inferred
to have passed from this targeted run.

The new input projection reads current relevant sources/dependencies/archives.
Historical input manifests, including the original INPUT255, are pinned as
FILEs only; none of their old entries is checked against changed live files.
Existing dependency records describe their original compilations. Root must
record this new consumer's actual dependency set after compiling it.
