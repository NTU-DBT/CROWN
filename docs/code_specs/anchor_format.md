# Binding a usage spec to source

Each entry in `reviewed_contracts.json` has a source path, an anchor, a reviewed
whole-file SHA-256, and seven usage fields: purpose, inputs/outputs, invariants,
ownership, failure, cost, and references. The authored spec describes its own
scope. A comment or declaration spec does not replace the called primitive's
contract or prove every sentence in a source comment.

The [generator](../../tools/generate_code_specs.py) accepts two anchor forms:

- A unique source-text fragment. It first tries exact matching, then the existing
  whitespace-flexible matching. Ambiguous or absent matches are not selected.
- An exact source span, useful for repeated `}` delimiters or repeated notes:
  `@source-span:L<first>-L<last>:sha256:<lowercase-64-digit-digest>`.

Span lines are one-based and inclusive. The digest covers the UTF-8 bytes of
those complete lines, including their actual line endings and any final newline.
The whole-file hash remains required. Range, syntax or checksum mismatch leaves
the anchor unmatched; impossible numeric widths are rejected before conversion.
There is no fallback from a malformed reserved span to a literal-text match.
The locator establishes content/location identity, not AST or proof authority.

The receiving process checks that each new span equals its intended mapped
block, that keys are unique, and that all seven fields and references are
present. The source index supplies clickable line boundaries. Static assertions,
module imports, field initialization and pure comments have different costs;
their cards must state the actual boundary rather than call all scaffolding free.

After a source edit, inspect the affected spec and its callers before rebinding
its whole-file hash. If lines or span contents move, review and update the span
as well. Regenerate with `PYTHONDONTWRITEBYTECODE=1 python3 tools/generate_code_specs.py`,
then run `PYTHONDONTWRITEBYTECODE=1 python3 tools/check_code_specs.py`.
The checker consumes saved maps, so canonical card edits require regeneration.

These tools run offline. They add no native owner, guard, callback, allocation
account, exception layer or work to an engine update.
