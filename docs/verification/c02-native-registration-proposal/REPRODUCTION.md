# Reproduction and root-owned native gates

Run manifest checks relative to the repository root. `PACKAGE_SHA256SUMS`
contains this packet's files; `source-files.sha256` contains its 38 overlay
files; `INPUT_SHA256SUMS` contains exact source/header/compiler/artifact inputs.
Absolute artifact/compiler paths are intentional. The old C01 seal is pinned
as a **file** only in this packet. Do not recheck old historical source-entry
manifests against a later native tree.

## Direct compilation, no execution

The author used the final compile-only recipe with a new output directory:

```sh
bash docs/verification/c02-native-registration-proposal/compile-publication.sh \
  /home/userroot/Codex/CROWN /tmp/crown-c02-native-registration-release-1 all 3
```

The fourth argument chooses optimization 0..3; 3 was the final full check.
For a new reproduction choose an unused `/tmp/crown-c02-native-registration-*`
directory. The recipe refuses to append newly named pure-ranking members to
an existing copied archive. Stages `archives`, `pure`, `bridges`, `consumers`,
`json` and `link` are available for inspection; the complete ordered `all`
recipe is authoritative. It compiles/archives/links only and never launches
an artifact. The pinned accepted coherent strict objects and matching parser
C archive must still exist, with exact identities given in the input and
reused-artifact records. This direct recipe is host-specific preparation,
not a native build dependency or a clean-source reproduction.

Every direct command has a `.command`, `.log` and `.exit` file. Every compile
has a complete `.d` dependency file and object. Every archive has a member
list. `build-evidence/ARTIFACT_SHA256SUMS` binds the final 19 objects, eight C++
archives and 12 executables. `build-evidence/COMMAND_SHA256SUMS` binds the exact
commands, logs, statuses, dependency and member files. Retained earlier
optimized diagnostics and probe checks have separate pins. No compiler output
or passed isolated test is a native CMake/CTest acceptance claim.

## Optional root-only publication execution

`root-commands.json` records the exact 12 new-test equivalents using the final
direct binaries, including the new wrapper and checked-in fixture root. These
commands were not run by the author. The wrapper uses the final original and
patched header-only probes; it is not enough to run only the patched cleanup
binary. Running these direct commands can validate the new probe/wrapper
publication, but cannot validate native target registration or replace the
complete matrix. Preserve stdout/stderr/exit status and before/after guards.

## Native application and verification

Only root may apply this reviewed mapping. Immediately before that batch it
validates the current 733 C01 seal entries once, checks all overwritten
pre-edit bytes and new-path absence, and backs up every overwritten native
file. It preserves the C01 seal as historical and all accepted predecessor
package/manifests and original Refactor.md. This proposal does not modify
ledger/handoff/status evidence; root manages that transaction separately.

Copy only the exact mapped overlay files. Then perform fresh native configure
and rebuild so every CROWN C++ unit sees the same active f763c58b patched JSON
header; do not mix old native project C++ archives. Existing parser source and
configuration remain unchanged. The original header is isolated to its control
executable. CMake checksum failures are genuine input failures and must not be
waived by substituting the upstream hash for locally patched bytes.

Root checks the actual generated test order/commands against the original
131-prefix and the complete expected 143-name list, not only a set count.
Expected compile entries are 214. Verify three pure units, one production
bridge, one testing bridge, unchanged 14/6 runtime/report lists, macro
propagation, clean linkage directions and all private include requirements.
Pure links have no runtime/report; each bridge links only its matching runtime.
The two example objects must compile and the upstream control must have no
active-header include root or CROWN archive dependency.

The full matrix remains GCC Debug, GCC Release, ASan+UBSan with leaks, Clang
Debug and fresh source-only Release. Native compiler/warning/parser policies
remain inherited; no new warnings or sanitizer diagnostics are waived. The
clean source copy already includes every new code, fixture, example, wrapper
and vendor-control path. Existing P07, report/serialization, statistics and
legacy tests must all remain present and pass. Finish with independent raw
evidence/source review and the root-owned current native source seal/status
transaction. C03, C05 deployment, S05 bytes and the remaining cards are not
accepted by these C02 gates.
