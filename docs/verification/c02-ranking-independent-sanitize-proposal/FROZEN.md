# Frozen root-ready sanitizer packet

Frozen on 2026-11-07. Both unchanged independent consumers compile and link with
ASan/UBSan, frame pointers, assertions and all six warning flags. All four final
compiler/linker exits are zero and all four logs are empty. No test executable
or semantic checker was run by this author.

The final integer binary is
`/tmp/crown-c02-independent-sanitize-current-2/ranking_integer_independent_test`,
SHA-256 `2884dc76c31f84963eb027689c228f11a84cc2d607bf7e1e97f9c259c40dae96`.
The final public binary is
`/tmp/crown-c02-independent-sanitize-current-2/ranking_public_independent_test`,
SHA-256 `374c6a2b682c715694890669c7fb15f9d03b881af97a6da81c900156c364b717`.
Use the exact argv/environment in [commands.json](commands.json) and the checks
in [ROOT_REPRODUCTION.md](ROOT_REPRODUCTION.md).

The 16-entry source manifest remains byte-identical to the strict source
manifest, SHA-256
`de2cbc0603eb34a6e787c7430d28d8b17a0f4444ad79164f4d91eda59f0f1357`.
The 590-entry current input manifest is
`0ba034a60ca52e40a374b31933b88ae7e5f907897804513209581419c510d78f`.
The 77-entry binary/object/archive artifact manifest is
`2c0790c9d36d7116ce6e26ce9695976c39e54edf0bf4490429e14b7122307292`.
The 505-entry command/log/dependency/exit manifest is
`8803488a7bdd7265c6c4384cf4cd8eb3f0a5fa793a914288ee5fc3faf409eba9`.

All 590 current input hashes agree before and after the final compile, including
the actual compiler tools, patch/API/ABI headers, sources and linked archives.
The original 47-file strict packet validates unchanged. The actual 67 production
source hashes match between strict and sanitizer configurations. No ordinary,
old-JSON or testing-runtime C++ input is used by these consumers.

The enclosing package manifest hashes every other file in this new packet; its
identity is supplied to root separately. Preserve this packet after root starts
execution. A repair must use a new sibling packet and retain failed evidence.
The accepted strict and scoped JSON controls remain separate from the pending
full independent sanitizer execution. No native C01/C02 gate or task ledger is
advanced by this preparation.
