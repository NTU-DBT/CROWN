# Exact test preservation and new coverage

The accepted native Release `CTestTestfile.cmake` has 131 registrations. Its
bytes are retained under `build-evidence/` and its source file is pinned as an
input. `prior-ctests-ordered.txt` is the extracted registration order;
`prior-ctest-commands.cmake` replaces only this workspace's source and binary
prefixes with `${SOURCE_DIR}` and `${BINARY_DIR}` for comparison. Python paths,
arguments, test names and their order are otherwise unchanged.

The CMake overlay changes the JSON hash guard, adds the pure and production
bridge libraries outside BUILD_TESTING, and appends the new testing block just
before the existing final sanitizer environment block. It edits no preceding
test declaration, target/source list, timeout, macro or command. The original
131 tests remain the prefix; the 12 additions are the suffix. The C01 14-unit
runtime and six-unit report lists and their matching variants are unchanged.

| New CTest | Distinct evidence |
| --- | --- |
| `ranking_binding` | Frozen P07 full binding bytes and prefix allocation behavior; bounded output admission |
| `ranking_pure_link` | Actual typed ranking consumer with no runtime/report library |
| `ranking_contract` | Required-height candidates, hot-relation reversal, literal scores, freshness, fallback and complete evaluation |
| `ranking_empty` | Constant/nullary/unary/empty source bounds; exact zero versus unknown; capture versus processing budgets |
| `ranking_payload_time` | Repeated owned SQL/program payload, Decimal/repeated outputs, exact/one-under caps and carried active time |
| `ranking_census` | Isolated uint64/root/denominator/protocol boundaries plus an actual testing Delta owner; private injection is not public evidence import |
| `ranking_exceptions` | Persistent allocation failures across capture and all three policies; complete owner/workload/result preservation and retry |
| `ranking_normalized_exceptions` | Same obligations through real normalized binding, replay, identity and lowering |
| `ranking_public_independent` | Eight public groups with literal tree geometry, real alias/source mapping, semantics, terms, freshness and unchanged proof authority |
| `ranking_integer_independent` | Independent decimal-digit arithmetic oracle, 54 operands/2,916 ordered pairs and all 16 limb boundaries in accepted predecessor execution |
| `json_cleanup` | Header-only patched normal/persistent-failure cleanup; json, ordered_json and custom vector-derived array/allocator; depth 4,096 |
| `json_patch_compatibility` | Isolated original/patched sizeof and full serialization bytes, plus actual original SIGABRT/bad_alloc control |

The independent public consumer takes the repository root and reads existing
small P07 Boolean query/tree fixtures. All other ranking consumers take no
arguments. The JSON cleanup consumer takes `--cleanup`; the wrapper receives
two target-file paths. `new-ctest-commands.tsv` gives the exact arguments and
timeouts. Every new test has `C02` label, assertions enabled and all project
warning flags. The two persistent C02 fault tests allow 3,600 seconds; JSON
tests allow 300 seconds with 120-second child limits. Sanitizer options come
from the inherited final CMake block, including leak detection.

The two documented-function object targets are compile checks, not extra
CTest executions. The upstream JSON control is not registered directly with
WILL_FAIL: arbitrary crashes are not accepted. The wrapper requires SIGABRT
and bad_alloc diagnostics and rejects unrelated sanitizer diagnostics; normal
serialization must succeed without stderr and compare byte-for-byte. Failure
artifacts are retained in a printed temporary directory. Success cleans it.

The old P07 candidates, candidate-exception and candidate-report tests are not
duplicated. Their accepted bytes, proof/binding authority and report formats
remain obligations of the full native matrix. No new acceptance/status field
is added to a user report or schema. Header-only cleanup probes do not by
themselves validate every CROWN JSON use or custom allocator profile; the
coherent native rebuild and complete legacy matrix remain required.
