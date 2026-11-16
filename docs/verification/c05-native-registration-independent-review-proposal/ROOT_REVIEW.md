# Root-only integrity and later validation

The reviewer did not execute these commands or any project checker. From the
repository root, root can verify this review's fresh FILE scope:

```sh
sha256sum --check docs/verification/c05-native-registration-independent-review-proposal/PACKAGE_SHA256SUMS
sha256sum --check docs/verification/c05-native-registration-independent-review-proposal/source-files.sha256
sha256sum --check docs/verification/c05-native-registration-independent-review-proposal/INPUT_SHA256SUMS
cmp docs/verification/c05-native-registration-independent-review-proposal/INPUT_BEFORE_SHA256SUMS docs/verification/c05-native-registration-independent-review-proposal/INPUT_AFTER_SHA256SUMS
```

The listed historical checksum manifests are FILE inputs only. Do not recurse
through them or call historical source-audit entry points. Root's separate
application guard owns the current 764-entry seal check, exact destination/new
path validation, backup and application transaction.

After application, root must obtain actual generated ordered commands/settings
for all 158 tests, the 238-entry target/source inventory, compiler/flags/macros,
link closure and symbol evidence, observed fresh/cached partition, dependency
provenance, and all native matrix outcomes. The complete clean-source leg must
use the copied native files and establish its own fresh build. No proposed
count, static review, excluded receipt or new-tests-only run replaces those gates.

Any change to the frozen publication requires a separate reviewed revision.
Later native execution and acceptance records may cite this unchanged packet.
