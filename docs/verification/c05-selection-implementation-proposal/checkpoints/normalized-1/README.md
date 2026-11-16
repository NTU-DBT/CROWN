# C05 normalized fixture checkpoint

Root's strict4 build/link and eight short producer consumers passed before this
revision. Root also closed the independent consumer build guard. The sole changed
overlay file is selection_normalized_exception_test.cpp: SQL now quotes physical
Catalog name R. PostgreSQL folds an unquoted R to r, while CROWN's catalog lookup
compares exact names; the old fixture would not reach normalization. This was
found by source inspection before executing that binary. No C05 implementation,
header, support helper, other consumer or numeric oracle changes.

Root targeted5 reuses the exact strict4 artifacts, which themselves preserve
strict3's eighteen unchanged TUs and the freshly corrected binding consumer.
Its explicit two-generation guards bind unchanged source/compiler/archive and
command metadata; only the quoted-SQL source is exempted and newly pinned.
It rebuilds/links only normalized_exception and executes no binary. All earlier
checkpoints and frozen independent packet bytes remain historical and unchanged.
