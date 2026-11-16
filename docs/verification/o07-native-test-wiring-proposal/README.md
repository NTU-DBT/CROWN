# O07 native test wiring proposal

This excluded root-owned proposal adds six native test executables and seven
CTest cases to the reviewed production/testing target graph. Original 92 cases
remain registered. Runtime consumers link only crown_explain_testing and its
matching runtime_testing; the query-only test links core/query/reference only.
The shared wrapper always creates a fresh corpus, runs every C++ group and the
complete checker, removes successful temporary files, and retains failed files.

Native placement requires the six accepted C++ sources, the query fixture
header, three independent checkers under tools/support, and the self-contained
native CLI runner/fixtures. The copied native query checker will resolve its
two schemas from the native repository rather than an excluded proposal.
CMake and the wrapper have not yet been exercised as native integration.
The native CLI fixture package remains pending, so this proposal is not ready
to apply or a substitute for the full native matrix. O07 remains not_started.
