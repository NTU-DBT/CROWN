# Exact as-of provenance

The root-created matching sanitizer closure is
`/tmp/crown-c05-selection-implementation-sanitize-1`. Its terminal receipt is
`build/verification/c05-selection-sanitize-root-checkpoint-1.json`, FILE
`8c8e0ef0066795be37ba057c6278874aacf04d945ff84fc96abde0f2ee6a087e`.
It records 19 fresh TUs, three archives, ten links, exit 0 and 203 stable input
entries. Its before/after input manifest FILEs are both
`eec6b2c1bda8275e6e9553b44545da938ee3c0845676acab42048c27de2731a9`;
its artifact manifest FILE is
`178b3eb72351080ef6a26d1767b5ae2e142b3a51e362e23f23b57743236a8e41`.
Only the five-unit pure archive and one-unit production bridge are linked here.

The independent strict evidence is a preserved sequence, not a replacement of
the original failure:

| Root receipt | Outcome used here |
| --- | --- |
| c05-independent-strict-root-attempt-1.json | Public seven groups passed; original cache failed; later consumers not run |
| c05-independent-cache-diagnostic-root-attempt-1.json | Confirmed original call 33 rejected unsupported arithmetic; original assertion still exited 1 |
| c05-independent-cache-corrected-strict-root-attempt-1.json | Corrected cache five groups passed, supported options 5 and rejected arithmetic 1 |
| c05-independent-strict-root-remaining-attempt-1.json | Resources 3, byte framing 5 and focused publication failure 2 groups passed |

The corresponding FILE identities, in table order, are
`8a7955ed460232db3b826df1da743092330afa0440cc66bb355cfa38bd6892d3`,
`9cad99e6147feb3eb30126c7627c1e96ac2695b223b70cd8b13fa2de06ad3bb0`,
`3126baa70103947a236e3befae252bdb89e352be44864d8b487d56082359ffec`
and `796121ad5c2df62777b2ae8d6acd2183c08ccccf79e7b1c04b72595e40a39f17`.
Together the accepted strict paths cover five selected consumers and 22 groups.
The focused ordinary OOM run observed 22 positions, two publication failures and
zero completed fault positions. The byte run observed five scalar types, 17
tree mutations, 38 core mutations and 79 normalized-record mutations. These
ordinary observations do not predict sanitizer allocation positions or results.

The public/private C05 ABI remains at the held API checkpoint:

| Header | FILE identity |
| --- | --- |
| planner/selection.hpp | aa8d8613d9ffb3b3c3e2a59ff8767d540edd7db82a98c10c05298b167104cc1b |
| runtime/selection.hpp | 713469fb08752227ba12af2fb85ae0717aae37b938d0938c8744ffd380d10ff1 |
| selection_detail.hpp | 310c2659433a04bf9f4d6f4975d636eb33720f74671d6d516381937e3da3edab |

The final input manifest binds the current actual headers, six implementation
sources/objects, historical API copies, compiler commands, archive recipes and
dependency records. The compiler is `/usr/bin/c++`, resolving to GNU 13; the
frontend, link driver, assembler/linker and sanitizer/C++ runtime library FILEs
are also pinned. The C05 compile flags are C++23, `-g -UNDEBUG`, all six strict
warnings, `-fsanitize=address,undefined -fno-omit-frame-pointer` and full `-MD`.
Native library flags come from their retained generated files; the Debug
sanitizer build does not define `NDEBUG`. Testing-runtime definitions occur only
in the producer's separate testing variant and are absent from this link graph.

The nine exact linked archives and compiler FILE are listed in
`LINK_INPUT_SHA256SUMS`. There is no ordinary C++ library substitution and no
testing/report archive. The native execution-freeze FILE remains
`1f97f84d7d2a09fb992668fcfa071d0065241b0a5de5395244a966216657d036`,
describing the held native 648/execution 705 C02 source scope. This packet pins
its FILE identity and current relevant compilation inputs; it does not reopen
historical source-seal entries or claim C05 native verification.

The producer's distinct strict receipts report eight ordinary consumers plus
two complete failure consumers, 32,966 direct and 20,420 normalized persistent
positions with no cleanup recoveries. Those receipts are pinned as separate
evidence only. Producer sanitizer execution was still pending when root
authorized this independent sanitizer freeze. No live progress record is used
as passing evidence.
