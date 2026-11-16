# Integer-only root execution checkpoint

This checkpoint is frozen independently of the unfinished public/runtime test
package. The producer confirmed its arithmetic API/source stable for this build.
The author compiled and linked, but did not execute the binary or a checker.

The executable contains only the independent decimal-digit driver and the
producer's matching UInt object. It links no project archive, runtime, report
library or testing probe. There is no `CROWN_RUNTIME_TESTING` or sanitizer macro
in this ordinary production build. This checkpoint is not public-runtime,
sanitizer, C02-native or matrix acceptance.

The driver, public/private arithmetic headers, UInt source and native freeze
were hashed before compilation. A strict checksum check of that saved list
passed after linking. `INPUT_SHA256SUMS` adds the compiler-recorded project
dependency closure and actual `/usr/bin/c++` executable. `ARTIFACT_SHA256SUMS`
records the executable, consumer object, copied UInt object and exact producer
object origin; the latter two hashes must agree. Manifests use repository-relative
paths except explicit absolute compiler/build-artifact paths.

Root, from `/home/userroot/Codex/CROWN`, may run:

```sh
c02_integer_checkpoint=docs/verification/c02-ranking-independent-tests-proposal/checkpoints/integer-1
sha256sum --check --strict "$c02_integer_checkpoint/CHECKPOINT_SHA256SUMS"
sha256sum --check --strict "$c02_integer_checkpoint/INPUT_SHA256SUMS"
sha256sum --check --strict "$c02_integer_checkpoint/ARTIFACT_SHA256SUMS"
/tmp/crown-c02-independent-integer-checkpoint-1/ranking_integer_independent_test
```

The driver prints the actual decimal operand/pair population and three completed
groups only after its assertions pass. Root must retain its own output and exit
status. A successful result does not authorize the remaining public API tests or
claim any runtime facts beyond exact private integer arithmetic.
