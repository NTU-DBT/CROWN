# Independent C02 publication review packet

This packet contains a read-only static review of the excluded C02 native
publication and its separately root-owned integration/execution recipes.
It is not a native build, test run, source acceptance or card-completion record.
The reviewer performed file reads, comparisons and hashes only; no compiler,
checker, executable, CMake, CTest, symbol tool, benchmark, network or git action
was used. All authored files are inside this packet or the assigned scratch
prefix. Native and all predecessor frozen packages are unchanged by this work.

`REVIEW.md` contains the publication findings and limits. `NEW_TESTS.tsv` is
an independently enumerated ordered inventory of the twelve additions.
`ROOT_DRIVER_APPENDIX.md`, `ROOT_INTEGRATION_APPENDIX.md` and
`ROOT_FREEZE_APPENDIX.md` review the exact root recipes as separate scopes.
The initial freeze gap is retained alongside the narrowed accepted static
revision; do not use the old draft. `baseline/` retains the prior CMake/CTest
and generated-compile evidence, current manifest FILE identities, and terminal
preparation aggregation. `root-drivers/` retains the exact examined recipes.

The final `review-result.json` binds the immutable author package and source/
input identities and distinguishes static acceptance from pending native gates.
`INPUT_SHA256SUMS` pins the external FILEs examined; it is an as-of pre-integration
record. `SOURCE_SHA256SUMS` pins the authored review sources and retained
copies. `PACKAGE_SHA256SUMS` covers this packet except itself. All relative
manifest paths use the repository root, and `/tmp` paths are explicit absolutes.

To validate this packet's own frozen bytes from the repository root, root can
use `sha256sum -c docs/verification/c02-native-registration-independent-review-proposal/PACKAGE_SHA256SUMS`.
The final parent message supplies that manifest FILE identity. Before application,
root separately verifies the author source/input/pre-edit pins with its reviewed
guarded integrator. After integration, do not revalidate an as-of pre-edit or
historical live-entry manifest against changed native paths; retain FILE
identities and copied baseline evidence. No test or build is authorized merely
by a partial review manifest check.

The native matrix must still establish the actual 143 ordered tests, 214 compile
entries, preserved legacy commands/numeric results, warning/sanitizer/compiler
contracts, variant/archive boundaries, coherent JSON rebuild and clean-source
behavior before final source/metadata acceptance. No allocation-count change
has a blanket waiver. C03, S05, deployment, cost calibration and the remaining
cards are outside this packet.
