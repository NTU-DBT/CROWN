# Root-only invocation

Root reported source inspection, successful parsing and verification of all five held driver bodies before authorizing this source freeze. Copy exactly those bytes to the same filenames under `/tmp/`. The package author has not executed or syntax-checked these sources. Run from `/home/userroot/Codex/CROWN`; preserve every output from a failed preflight or execution. A corrected attempt requires new evidence/helper names or a separately reviewed revision; these helpers do not overwrite existing terminal evidence.

```text
python3 /tmp/crown-selection-execution-freeze.py
```

After root records the resulting freeze FILE hash, substitute its exact hexadecimal value for `FREEZE_SHA` in these argv. Do not supply the text placeholder to a real command.

```text
python3 /tmp/crown-selection-matrix.py debug --freeze-sha256 FREEZE_SHA
python3 /tmp/crown-selection-matrix.py release --freeze-sha256 FREEZE_SHA
python3 /tmp/crown-selection-matrix.py clang --freeze-sha256 FREEZE_SHA
python3 /tmp/crown-selection-clean-matrix.py --freeze-sha256 FREEZE_SHA
```

Root chooses concurrency for those four legs. After all four are terminal and other expensive activity has stopped, root writes the immutable quiescence receipt described in [SCHEMA.md](SCHEMA.md), records its FILE hash, and launches the full SAN leg alone:

```text
python3 /tmp/crown-selection-matrix.py sanitize --freeze-sha256 FREEZE_SHA --quiescence-sha256 QUIESCENCE_SHA
```

The per-test timeouts are preserved. The clean adapter is invoked by the clean matrix wrapper, with Release and parallel2. It retains direct dependencies before tests and calls the symbol collector before cleanup. Do not separately recollect clean symbols under the same names.

For the four persistent build trees, root collects symbols after successful compilation; this may precede terminal test outcomes and never accepts them:

```text
python3 /tmp/crown-selection-symbols.py build/debug debug --freeze-sha256 FREEZE_SHA
python3 /tmp/crown-selection-symbols.py build/release release --freeze-sha256 FREEZE_SHA
python3 /tmp/crown-selection-symbols.py build/clang-debug clang --freeze-sha256 FREEZE_SHA
python3 /tmp/crown-selection-symbols.py build/sanitize sanitize --freeze-sha256 FREEZE_SHA --parser-undefined
```

No helper changes native code, test properties, the old evidence, or the registry. CMake/CTest execute with their existing inherited environment and frozen presets/cache compiler choices. The later independent matrix auditor must verify the actual flags, all158 ordered commands/outcomes, all238 entries, observed24/214 versus238fresh build partitions, predecessor provenance, warnings/vendor recipes, exact numeric rows, allocation decisions and symbols. Full acceptance is possible only after all five terminal legs and those independent checks pass.
