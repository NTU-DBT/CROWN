# C05 API checkpoint 2

The public/private interface and implementation bytes are unchanged from API
checkpoint 1. Root strict3 compiled eighteen of nineteen TUs and all three
archives/nine available consumers. Only selection_binding_test.cpp failed:
optimized nested variant move assignment drew maybe-uninitialized diagnostics
from GCC13. The retained diagnostics are in the immutable strict3 output.

The single changed overlay file now constructs the nested Value's string
alternative in place, then assigns the same three bytes `a NUL b`. This avoids
moving an intermediate union while preserving the exact field-mutation oracle.
No warning/optimization option or assertion is removed. Root can reuse the
eighteen unchanged TUs, three archives and nine binaries, rebuilding/linking
only the corrected consumer with build-checkpoint-4.sh. Its guards bind the
exact prior source/compiler/archive artifacts and exempt only this documented
changed source. It executes no consumer.

The source manifest pins the complete twenty-two overlay files and new recipe.
The predecessor manifest binds API checkpoint 1 and the terminal strict3
provenance files. This checkpoint is not execution acceptance or final freeze.
