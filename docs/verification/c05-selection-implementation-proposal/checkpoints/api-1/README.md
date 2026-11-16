# C05 API checkpoint 1

This is a stable interface/source checkpoint for root and the independent test
author, not the final implementation freeze or execution acceptance.

The public interfaces are `planner::selection::select` and three matched
`runtime::selection::select_current` overloads, with immutable Selection and
CurrentSelection handles and the move-only PlanCache. Their headers are copied
under this checkpoint's overlay paths. The private diagnostic record APIs in
the copied selection_detail.hpp return bytes only and confer no authority.
`BINDING.source.txt` preserves the original documentation bytes specifying
their field tags/order independently of control flow. Copied documentation has
a source-text suffix so original relative links retain their documented origin.

The original GNU six-unit compile checkpoint remains as-of evidence. Root's
full strict checkpoint 2 compiled 18 of 19 TUs and linked 9 of 10 consumers;
the binding consumer had a preprocessor comma in one macro argument. That
source-only fixture defect is now parenthesized. No binary ran in checkpoint 2.
The separate DirectCQ options pre-admission correction and additional typed
wide-comparison/full-capture retention assertions are in checkpoint 3 inputs.
All checkpoint-2 artifacts/logs remain untouched.

The next exact root command is recorded in `BUILD.md` at the proposal root.
The independently pinned current source manifest includes the public headers,
all implementation/consumer sources and that new recipe. No further public API
change is anticipated. A future correction must be explicitly reported and
repinned; this checkpoint must remain historical rather than overwritten.
