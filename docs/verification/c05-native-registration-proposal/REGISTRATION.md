# Target and test contract

`crown_selection` owns five translation units: selection, selection_budget,
selection_binding, selection_payload and selection_cache. It publishes the
pure selection header and links `crown_ranking`. The existing ranker supplies
the unchanged bounded arithmetic, binding and public payload helpers.

`crown_selection_runtime` owns one source and links `crown_selection` plus
`crown_ranking_runtime`. Under `BUILD_TESTING`,
`crown_selection_runtime_testing` compiles that source separately and links
`crown_ranking_runtime_testing`. Its transitive `CROWN_RUNTIME_TESTING` applies
to its consumers only. No producer/testing runtime object or archive is mixed.
Neither bridge links observability or report IO.

Every new test compiles with `-UNDEBUG` and the existing six strict warning
options through `crown_options`. Existing configuration, sanitizer flags,
thread/parser dependencies and JSON checks remain inherited. The pure-link
producer and independent byte oracle link only `crown_selection`; all other
new tests link the production bridge except the census consumer, which links
only the testing bridge. Two object-only example targets compile the same
`tests/examples/selection_usage.cpp` through each bridge.

The ten producer tests preserve the held implementation consumers without
rewriting expectations. The independent public, cache, resources and fault
tests receive the repository source directory and read the existing Boolean
candidate fixture files. The independent byte oracle takes no argument. The
three persistent-fault consumers have a 7200-second timeout; the remaining
new tests have 900 seconds. All are labeled `C05`.

All 15 declarations precede the existing sanitizer block's directory-wide
test enumeration. They therefore receive the same leak checking, immediate
ASan failure and UBSan stack-trace environment as the retained 143 tests.
No prior test timeout, label, environment, command, wrapper or registration
order is changed.

The source-derived counts are 143 + 15 = 158 tests and 214 + 24 = 238 compile
entries. Root must check the actual generated ordered test commands and compile
database after integration. Source inspection alone does not prove those
generated counts, clean-source portability, linking or execution.
