# Sanitizer evidence-only source map

| Path | Purpose |
| --- | --- |
| `README.md` | Scope, source/variant identity, accepted strict context and remaining gates. |
| `ROOT_REPRODUCTION.md` | Exact root argv/environment, pin checks and fresh coherent reproduction recipes. |
| `commands.json` | Structured final compile invocation and two root-only execution commands. |
| `BUILD_RESULTS.json` | Actual compile/link exits and hashes; no test-execution claim. |
| `FROZEN.md` | Final immutable packet identities and readiness. |
| `provenance/consumer-reproduce-build.sh` | Exact copy of the frozen independent compile-only recipe; it reads the original unchanged tests. |
| `provenance/producer-compile-closure.sh` | Exact copy of the producer's coherent source/variant/flag recipe. |
| `provenance/producer-SANITIZED_*` | Exact held producer implementation/archive inventories, including contextual testing-runtime rows not linked here. |
| `provenance/PRODUCTION_OBJECTS.tsv` | The 67 actual production archive source/object rows. |
| `build/sanitize/` | Copied final consumer compile/link commands, exits, logs, dependency and before/after source/archive records. |
| `build/preparation/` | Preserved initial successful compile/link metadata, superseded by a final build with complete precompile input pins. |
| `build/preflight/` | Source/configuration comparison, compiler provenance, and complete before/after input checks. |
| `source-paths.txt`, `SOURCE_SHA256SUMS` | The same frozen consumer and producer sources/recipes, without source edits. |
| `input-paths.txt`, `INPUT_SHA256SUMS` | Actual compiler/header/ABI/patch/archive dependencies and terminal historical evidence files. |
| `artifact-paths.txt`, `ARTIFACT_SHA256SUMS` | Final two binaries/objects and the complete matching production object/archive inputs. |
| `command-paths.txt`, `COMMAND_EVIDENCE_SHA256SUMS` | Exact producer and consumer command/log/dependency/exit/archive-membership evidence. |
| `PACKAGE_SHA256SUMS` | Every other file in this new packet. |

No path maps to a native destination. The original test files and all 47 files
of the strict package are read-only inputs. All author writes are confined to
this new packet and `/tmp/crown-c02-independent-sanitize-*`. No schema, CLI,
CMake, test registration, source ledger or handoff is changed.
