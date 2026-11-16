# Physical SQL source images: receiving verification

The [source image API](../sql_source_images.md) captures all original physical
tables and their complete nullable rows, actual source/native recipes and binding,
and the committed sequence. It retains filtered/unused rows that native or grouped
output cannot reconstruct. This is an owning in-memory value; whole-image cold
rebuild and durable W06 recovery remain open.

## Executed checks

Strict maintained C++23 Debug and full ASan/UBSan/leak builds each pass all seven
focused tests: source snapshot, SQL rows runtime/batch/binding, composed aggregate
runtime/binding, and the existing aggregate runtime. Debug takes 3.62 seconds;
sanitizers take 15.60 seconds. Complete test-disabled Release builds successfully.
A relocated 220-file SDK builds and runs a strict public consumer using only the
installed composed-runtime target.

Both test profiles register 331 tests. All 330 predecessor commands and execution
properties remain, excluding source-line backtraces; only `sql_source_snapshot`
is added. The OFF configuration includes the production runtime and excludes the
new test. These results do not establish execution of all 331 tests.

The new test runs ordered and indexed storage. It checks complete nullable rows,
filtered/unused tables, original table/tuple ordering, real binding/program
identity, retained string lifetime after erase, and image survival after caller
text and runtime facade destruction. Constant-zero/one native routes retain unused
physical rows while their root remains unchanged. Moves under covered C++ new
denial and controller-only final teardown pass.

Exact capture work `{12,11,262,0,0}` is checked for the bounded fixture, including a
256-byte string and an unused string. Distinct-row and each used work dimension
reject one below the required limit without advancing state or retaining partial
image memory. The measured capture path has one covered C++ new failure point per
backend; denial at each point permits retry on the same owner. This observed seam
does not establish every allocator, syscall or account-denial fault position.
Pending epochs and active source readers reject capture.

## Design and cost boundaries

The production patch adds public source-image records/limits and read-only capture
methods without changing existing update bodies or persistent runtime fields.
Capture uses the original source maps, one receiving-account entry vector, shared
immutable row/program owners and one cumulative work allowance. It visits the
table list twice and each retained row/field once. String `size()` contributes an
admitted retained extent; the implementation does not rescan or clone payloads,
expand multiplicities, sort rows, or maintain an update-path row mirror.

There is no new catch, retry framework or undo system. Ordinary owning values
release incomplete capture on failure. Retained shared rows keep their original
allocation account/purpose until the last owner closes. Reference counting,
vector allocation and retention are real costs; the work fields are neither CPU
instructions nor all allocator bytes. No paper complexity or speedup claim is
assigned to this local capture contract.

## Evidence and later wording changes

Root evidence is `build/verification/w06-source-image-implementation-v1`:
receiving acceptance, final source pins, test logs, relocated SDK pins,
registration parity and input cohorts. All 25 recorder jobs are terminal, with
24 successes and one preserved private test-compilation failure. That fixture
used `fault.triggered` instead of the actual `s04_alloc::triggered`; the test was
corrected before all final private/maintained gates. Production source needed no
repair. Private sanitizer runs instrument only the modified runtime/test units;
the full maintained sanitizer result above includes their dependencies.

Each job has an unchanged in-command input map. After the final gates, an
independent ingest-test review changes comments and 18 diagnostic literal tokens;
its non-literal tokens/assertions/calls/control flow are unchanged. One offline
generator prose literal distinguishes comment-only edits from diagnostic edits.
Exact source phases and proofs remain recorded; no wording-only native rerun is
claimed. The [inspection map](../code_specs/README.md) and
[handoff](../handoff.md) retain the remaining review and implementation scope.
