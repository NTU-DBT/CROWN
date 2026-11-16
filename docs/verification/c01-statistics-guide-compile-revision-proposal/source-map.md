# Source map

| Proposal file | Purpose | Future destination or treatment |
| --- | --- | --- |
| `overlay/docs/statistics.md` | C01 guide revised to the current combined proposal API and compile-checked examples | Candidate for `docs/statistics.md` only after root review and C01 publication approval; no native file is created here |
| `README.md` | Status, reconciliation, current versus historical pins, and compile summary | Proposal record only |
| `input-pins.sha256` | Current combined headers, native transitive headers, accepted evidence and current documentation | Active inputs for this revision |
| `historical-input-pins.sha256` | Original frozen guide proposal pins copied without edits | Historical inputs only; superseded where current O07 documentation hashes changed |
| `compile-evidence.md` | Exact compile-only commands and artifact/log/source/header hashes | Compile evidence; no linked or executed program |
| `source-map.md` | Proposed documentation placement and exclusion boundary | Proposal record only |
| `package.sha256` | File-level hash manifest for this revision, excluding itself | Proposal identity |

The package contains documentation and evidence only. It does not edit the frozen base guide, the combined proposal, native files, O07 report/schema/tool/CMake inputs, or tests.
