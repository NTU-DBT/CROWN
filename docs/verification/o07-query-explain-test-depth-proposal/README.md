# Independent query EXPLAIN acceptance proposal — excluded, O07 NS

This directory alone is the test author's writable proposal. No native file,
report source package, other overlay, CMake file or historical seal was edited.
The test author compiled and linked only; **no C++ test executable or Python
schema checker was executed**. Root owns acceptance runs and dispositions.

The frozen subject is `../o07-query-explain-proposal/readiness.json`, package
`1ee51f89955602fc2ff2a0aecce1c1728a4ba10d0981f0a4fb4b66ea58049802`.
The test links its O0 archive, frozen Release Reference and Core only. There is
no runtime overlay/archive or foreign Runtime ABI in this closure. O0/O3 below
refer to the independent test TU, not rebuilt native libraries.

## What the executable requires

`query_explain_test.cpp` is self-contained and includes no other test CPP. It
has four selectable groups; `all` runs every group:

- `states`: genuine strict/best-found search admitted/preprocess/search/upper/
  producer-complete-before-proof/final states; work, active-time and depth stops;
  positive time quanta, zero and negative quanta with unchanged stored progress;
  monotone limit changes/rejection; cancellation both before and after upper;
  replay admitted/partial/checked-claims-before-root/resource/cancelled/valid and
  corrupt algorithm/height/root/claim paths. The explicit additional lifecycle
  fixture S(y,z), R(x,y), T(z,w), with full ordered head x,y,z,w, is first run
  one transition at a time to measure the depth at its first actual checked
  upper. Fresh owners use that ceiling and must stop later in producer search
  with the checked upper retained, then raise/resume to the independently
  literal-oracle-checked optimum. Failure to observe the state is a **failure**,
  never a skip. This extra fixture does not replace any of the 437 inputs. Both strict
  and best-found states must preserve proof authority. All six factory sources
  are emitted, including typed upper, optimum, negative and checked certificate.
- `metadata`: exact input binding identity and retained values, versions, FK
  target/columns/status, enforced and untrusted constraints, maximum unsigned
  statistics, hints, decimal spec, binary collation, ordered duplicate aliases,
  ignored terms, signed integer minimum, bool, Gregorian date and exact Decimal;
  NUL/quote/backslash/newline bytes; malformed UTF-8 in values and identifiers.
  Native non-UTF8 capture succeeds; the affected text exports reject separately.
  Nullable=true is outside native admission, so admitted column nullability is
  checked as false; this test does not invent an admitted nullable binding.
- `faults`: process-local replacement allocators fail persistently at every
  successive allocation index until the entire operation succeeds, without a
  fixed sweep cap. Faults remain armed during exception unwinding/destruction.
  Capture, typed checked capture, all four exports, capture-cap rejection and
  invalid-UTF8 rejection are swept. Existing reports, deep copied progress and
  owning producer remain unchanged; the same operation/owner succeeds after
  each failure is disarmed. Real search/replay bad_alloc stops recover on the
  same owner. An injected non-bad_alloc allocation exception creates actual
  terminal internal_failure states, without editable progress or proof flags.
- `family`: **all 426 systematic inputs plus all 11 anchors**, each under both
  policies, compared against `reference::exhaustive_minimum_tree` from the
  separately frozen native Reference archive. The oracle enumerates literal
  labelled topologies/native power sets, not report/provider classifications.
  Search and genuine replay use bounded quanta and read-only captures throughout.
  Expected final height and negative outcome come from the independent oracle.
  Reference work/depth/scope/time ceilings are explicitly unbounded for this
  finite domain. Any reference resource outcome or unexpected continuation stop
  is a **failure**, never a success or skipped input. The contradiction-marked
  nonempty triangle must remain structurally negative, while empty-body cases
  retain their own structural outcomes; no P08 constant_false shortcut is used.

Report snapshots are copied before advance/limit change/move/cancel/drop. Tests
compare all progress counters/statistics by value, preserve native immutable
binding identity, reject moved-from report/producer/all typed-handle variants,
and check that hidden strict uppers never export a tree. Compile-time negative
construction checks reject mutable progress/OracleResult/certificates/trees/
boolean flags. Report admission performs no JSON, recognition or advance; the
source equality checks catch any producer/statistics mutation during capture.

All four text transports have exact encoded-byte boundary, one-byte-under and
zero-cap tests. Their native failures leave the checked owner/report untouched.
Each emitted report has an independently written `.expected` numeric/hex sidecar
from native accessors. It contains exact root/node IDs/scopes/children/occurrences/
separator/connex/height claims, all certificate lower-bound entries and counters.
It does not use the report serializer or a JSON DOM.

## Offline schema and semantic acceptance

`check_corpus.py` requires already-installed `jsonschema`, does no networking or
subprocess work, and accepts no external authority. It checks the two local
closed Draft 2020-12 schemas, rejects duplicate JSON keys/nonfinite numbers,
compares report fields with the independent native sidecars, and checks:

- all six source and five height-status families; independent proof/publication
  conditions, bounds and witness/certificate agreement;
- original binding and claims preserved between owning report/tree exports;
- node/root/occurrence IDs, complete reachability, unique native occurrences,
  independent native height computation and running intersection;
- DOT generated numeric nodes/edges matching the original native tree;
- human status, counter aliases/inequalities/time-cap interpretation;
- exact scalar/metadata/control-byte round trips and uncollected recognition;
- undeclared authority-field/unknown-status minimum-flag negative schema cases.

`--require-all` rejects missing state/source/resource/fault/metadata groups and
requires exactly **872 family search and 872 family replay JSON reports**. Both
policies run all 437 native inputs; only the raw-byte anchor cannot produce JSON,
so 436 × 2 exports per producer type is the expected transport count. This is
not a skip of the raw native search/replay/oracle comparison.

These semantics do not replace native P02/proof replay, and schema validity is
never authority. Native counter overflow is not injected: there is no public
seam to reach UINT64_MAX counters, and the suite does not forge progress. Clock
quantum tests require the existing steady clock to advance at nanosecond-scale
measurement; root must diagnose any platform-specific timing failure honestly.
Root observed the separate depth diagnostic before this revision; this revised
suite and its additional literal comparison still require root execution. There is no claimed coverage
of arbitrary query completeness, O07 CLI integration, runtime metrics, durable
state, P08 physical lowering or the final native build matrix.

## Root-only run instructions

Build commands only (used by this author, no binary execution):

```sh
python3 docs/verification/o07-query-explain-test-depth-proposal/build_test.py /tmp/crown-o07-query-explain-depth-tests-o0 --opt 0
python3 docs/verification/o07-query-explain-test-depth-proposal/build_test.py /tmp/crown-o07-query-explain-depth-tests-o3 --opt 3
```

Root may run the four groups into separate **fresh** directories, so partial
attempts cannot contaminate a final corpus. These commands have **not** been run
by the test author:

```sh
/tmp/crown-o07-query-explain-depth-tests-o0/query-explain-test /tmp/crown-query-depth-acceptance/states states
/tmp/crown-o07-query-explain-depth-tests-o0/query-explain-test /tmp/crown-query-depth-acceptance/metadata metadata
/tmp/crown-o07-query-explain-depth-tests-o0/query-explain-test /tmp/crown-query-depth-acceptance/faults faults
/tmp/crown-o07-query-explain-depth-tests-o0/query-explain-test /tmp/crown-query-depth-acceptance/family family
python3 docs/verification/o07-query-explain-test-depth-proposal/check_corpus.py /tmp/crown-query-depth-acceptance --require-all
```

External process timeout/OOM is an incomplete/failed acceptance run, never an
accepted resource skip. The family prints every completed input for auditability.
A run can be expensive; no smaller smoke family is substituted for final
acceptance. An optimized test executable is also available for root reruns.
`compile-evidence-o0.json`, `compile-evidence-o3.json` and `readiness.json` record
all source/compiler dependency/archive/binary hashes and the no-execution scope.

## Revision provenance and depth diagnosis

The original package `../o07-query-explain-test-proposal/` remains byte-identical
(package SHA `8fb33b288b4abd58fd0955a8a7e8319de875e4b59cd19e77684fae6f4f4ac98d`).
Root attempt 1 passed metadata, persistent faults and all 437 inputs under both
policies; states failed the test author's overly restrictive depth discovery.
That discovery required replay peak > final producer peak, excluding a valid
post-upper stop during further **producer** exploration. No subject bug or
proof-rule relaxation follows from that test selection error.

Native `exact.cpp:165` publishes a candidate before later native/generalized
root/partition exploration (`206–272`). `search_session.cpp:245–252` publishes
the checked incumbent and returns to producer search. The revised explicit
fixture exercises this route. Root's separate diagnostic exit 0 observed first
upper depth 11, final producer peak 14 and replay peak 8; strict and best-found
ceiling 11 stopped in search with upper 2 and resumed after raising the ceiling.
Evidence: `build/verification/o07-query-depth-diagnostic-attempt-1.{json,log}`.
The independent author did not execute that probe. The revision measures the
first-upper depth from genuine progress instead of hardcoding diagnostic
counters, requires the actual stop under both policies, checks immutable stopped
reports after resume, and independently checks the extra fixture's final height
with the same frozen literal oracle.
