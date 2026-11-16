# C02 allocation-variance source investigation

This excluded packet prepares a causal diagnostic for the fifteen additional
Clang allocation positions. It changes no native code, descriptor, assertion,
golden expectation, held library or allocation-review decision. Root alone runs
the probes and decides whether any observed difference is allocation-only.

The already completed root success profile is
`build/verification/c02-clang-success-allocation-profile-attempt-2.json`, SHA-256
`77042813b621307a0ec3b3310cf236a1dddd33857c39e6415e83ce58d2a06805`.
Its direct GNU counts are height 34, depth 55, memory 7,994 and capture 29; Clang
has 8,009 for memory and the same other counts. The normalized memory counts are
38,645 and 38,660. These are observed successful-call totals, separate from the
native persistent-failure sweeps and their unchanged semantic assertions.

Source inspection shows a shared place to investigate. Only the tuple/index-slot
policy calls `memory_score`, which lowers every retained candidate. The fixture
has three real P06/P07 candidates. Both direct and normalized lowering reach
`Lowering::run`; each `Lowering` constructs one `PhysicalPlan::Data` with
`std::make_shared`. Its default members include `PhysicalOptions` and
`GuaranteeProfile`. The normalized path has extra replay work, but the same
default Data construction. This explains why a fixed per-candidate construction
effect could appear in both traces; it does not establish which constructor caused it.

`GuaranteeProfile` contains twelve scalar strings and three vector-of-string
default member initializers. Five vector entries exceed the 15-character local
capacity in the held libstdc++13 `basic_string` source: one operation mode, two
assumptions and two output-accounting strings. GNU13.3 and Clang18.1.3 both use
that header family in the held native builds. An initializer-list vector copies
from const backing-array elements, so temporary string storage is a meaningful
control to inspect. No particular compiler's allocation elision, temporary
construction, defect or standard conformance is inferred from that source alone.

`default_initialization_probe.cpp` measures 22 constructions: native profile and
options defaults, value initialization, shared construction, profile construction
from an explicit value, a nested options/profile control, the actual cache-policy
defaults, scalar-only controls, and each exact vector initializer as a member
and a direct local vector. Every literal is preserved and checked after the
measured interval. No raw plan, proof or runtime evidence is manufactured.

`native_lower_probe.cpp` obtains the three actual typed candidates using the
unchanged fixture. Search and options preparation happen before the counter starts.
It measures one real `lower_tree` call for each candidate, linked to the matching
native production plan/SQL/core/parser archives, and prints the real structural
key, physical identity and work afterward. It checks the descriptor strings and
the expected fixture shape; it is not a new independent runtime-semantics oracle.

The fixed counter records successful C++ scalar/array/aligned allocations, frees
observed during construction, requested bytes and allocation-size histograms.
It uses fixed thread-local arrays and performs no tracing allocation or output
inside an interval. Validation/output and final object destruction are outside
each interval. Temporary destruction before the constructor returns remains
inside, so its frees are visible. Event/histogram capacity overflow fails explicitly.
Direct C allocation, allocator metadata, peak/live bytes, and later destruction
are outside this counter's coverage; requested-byte totals are not S05 memory bounds.

The causal contrast to evaluate is more specific than equal totals. If the vector
default-initialization boundary is responsible, the compiler difference should
localize to the exact vector controls, with a 1/2/2 pattern, appear in the relevant
native profile/nested/shared form, and account for five extra calls in each real
candidate lower. Allocation sizes and temporary frees should identify the same
string populations. Scalar/options/cache controls and direct-vector/value forms
help distinguish alternatives. A different pattern falsifies or narrows this
hypothesis. No allocation count is hardcoded as a success assertion.

Only the GNU default-probe object compiled: strict C++23, all six warning/error
flags, Debug `-g`, no suppression, exit 0 and empty log. It was not linked or run.
Automatic approval review rejected the Clang compile before launch, interpreting
compilation as root-only work. The exact action/reason is retained in
`automatic-review-rejection.json`. Root instructed the author not to retry and
will perform the remaining compilation, links and execution. No binary, checker,
Python, CMake, CTest, symbol tool or benchmark was run by this author.

`PRECOMPILE_INPUT_SHA256SUMS` pins the known native headers, source path, two
compiler binaries and both matching archive sets before the GNU compilation;
all 94 rows still match afterward. `GNU_ACTUAL_DEPENDENCIES_SHA256SUMS` pins all
365 files in that compiler's actual `-MD` dependency closure. Other probes have
not compiled, so their future dependency closures are not claimed. Root must
retain and pin those after its builds. The exact eight build argv and root run
argv are in `commands.json` and `ROOT_REPRODUCTION.md`.

This source investigation can support a narrowly explained root decision only
after its causal controls are observed and reconciled with the existing full
persistent-OOM evidence. It grants no semantic equivalence from counts alone,
compiler-bug finding, numeric waiver, native acceptance, C03 calibration, C05
selection authority, S05 bound or full-goal completion.
