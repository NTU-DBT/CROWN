# Static review cases, not executed by the author

1. The two frozen Clang aliases resolve to the same internal canonical FILE and
   hash. A raw map containing either or both consistent spellings satisfies the
   mandatory internal check; the external whitelist contains neither internal
   spelling. The receipt records all spellings actually observed.
2. Removing the internal Clang canonical identity from raw pins fails the
   mandatory raw-pin check even though the current compiler FILE still exists.
3. A changed current compiler FILE fails its raw and mandatory byte checks.
4. Contradictory mandatory aliases fail before assignment; contradictory raw
   aliases fail before assignment, for both internal and external paths.
5. A missing or overridden external compiler/helper/watcher fails the mandatory
   whitelist check, the mandatory raw-pin check, or both. Current bytes are also
   checked; a whitelist alone cannot satisfy the mandatory check.
6. An internal path listed as external is rejected. An unobserved external extra
   is rejected by exact whitelist equality. Unapproved external raw pins fail.
7. Existing explicit final mode, complete matrix, immutable authority and exact
   three status-document approvals remain necessary. Preliminary mode cannot
   accept final status even when tool checks pass.
8. Malformed or absent evidence still produces an unaccepted failure receipt;
   current read pins are rechecked before publication. No old source-manifest
   entries or project programs are executed by this helper.

These cases describe the source-reviewed contract. This packet contains no
executed test result for them and does not represent synthetic data as an
accepted matrix or root authority.
