# `apps/crown/main.cpp` — block usage map

[Source](../../../../../apps/crown/main.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `4169bfa74f65d11e7e21eaffc33409a23df82dea8c510f9594b57ce300dbe117`. 354 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–32](../../../../../apps/crown/main.cpp#L1) | Imports dependencies; declares namespace scope. | growth new · [reviewed contract](#b0001) |
| [B0002 · 33–43](../../../../../apps/crown/main.cpp#L33) | Callable definition: crown::planner::SearchLimits search_limits(const char* value) | calls reset, std::from_chars, data, size; returns limits; limits · [reviewed contract](#b0002) |
| [B0003 · 44–60](../../../../../apps/crown/main.cpp#L44) | Callable definition: std::string read_text(const char* path, std::optional&lt;std::size_t&gt; byte_limit = std::nullopt) | calls input, crown::Error, resize, read; returns text; growth resize; source comment (unverified): // Read at most limit+1; the parser or caller reports its normal limit error. · [reviewed contract](#b0003) |
| [B0004 · 61–62](../../../../../apps/crown/main.cpp#L61) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 63–335](../../../../../apps/crown/main.cpp#L63) | Callable definition: static int command_main(int argc, char** argv) | calls std::string, command, crown::cli::aggregate_main, std::string_view; returns 0; 0; growth push_back; 3 loop sites; source comment (unverified): // Syntax, binding, normalization and structural admission remain separate. · [reviewed contract](#b0005) |
| [B0006 · 336–337](../../../../../apps/crown/main.cpp#L336) | Explanatory comments or spacing. | source comment (unverified): // Keep diagnostic failures inside the process boundary and flush once at exit. · [reviewed contract](#b0006) |
| [B0007 · 338–354](../../../../../apps/crown/main.cpp#L338) | Callable definition: int main(int argc, char** argv) | calls command_main, flush; returns 2; status; source comment (unverified): // Keep diagnostic failures inside the process boundary and flush once at exit. · [reviewed contract](#b0007) |

## B0001

[Lines 1–32](../../../../../apps/crown/main.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L32:sha256:cb4fc9ce51f9cb9a192647a53f18a98066c393e6b42ca48dcf7c373e92eb455e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare main.cpp: include "crown/api/error.hpp", "crown/version.hpp", "crown/io/document.hpp", "crown/io/tree.hpp", "crown/io/oracle.hpp", "crown/io/sql.hpp", "crown/io/catalog.hpp", "crown/io/binding.hpp", "crown/io/normalization.hpp", "crown/io/identity.hpp", "crown/io/admission.hpp", "crown/io/recognition.hpp", "crown/io/physical.hpp", "crown/io/support.hpp", "crown/io/ingest.hpp", "crown/catalog/catalog.hpp", "crown/planner/recognize.hpp", "evaluator.hpp", "explain.hpp", "workflow.hpp", "aggregate.hpp", &lt;exception&gt;, &lt;new&gt;, &lt;charconv&gt;, &lt;fstream&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;optional&gt;, &lt;string&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [apps/crown/main.cpp](../../../../../apps/crown/main.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 33–43](../../../../../apps/crown/main.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
crown::planner::SearchLimits search_limits(const char* value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse legacy structural search budget or explicit unlimited mode. |
| inputs / outputs | Missing arg leaves default SearchLimits; unlimited clears work limit; decimal uint64 sets it. |
| invariants | Only compatibility structural commands use this selector; no time/query-memory/cost-optimum authority. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | usage on malformed integer/unlimited spelling. |
| cost | Ordinary option string copy and O(bytes) parse. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

## B0003

[Lines 44–60](../../../../../apps/crown/main.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string read_text(const char* path, std::optional<std::size_t> byte_limit = std::nullopt)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read legacy command input with optional early byte-limit detection. |
| inputs / outputs | Bounded private callers read at most limit+1; other callers buffer entire stream before parsing. |
| invariants | Current private bounded values are finite parse/catalog limits below size/stream maxima. Legacy uncapped JSON/certificate paths have no whole-file byte cap in this helper. |
| ownership | Returned owning text outlives local ifstream. |
| failure | Open/bad read/allocation failures propagate; caller/parser diagnoses limit+1. |
| cost | O(read bytes) ordinary string resize/copy and synchronous file I/O; not native account. |
| Design | [docs/cli.md](../../../../cli.md) |

## B0004

[Lines 61–62](../../../../../apps/crown/main.cpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L62:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in main.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [apps/crown/main.cpp](../../../../../apps/crown/main.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 63–335](../../../../../apps/crown/main.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static int command_main(int argc, char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch each CLI command once, including the separate original-SQL aggregate family. |
| inputs / outputs | Routes file workflows and shifted EXPLAIN before older SQL/catalog/CQ/reference commands; each branch sets its own result status. The aggregate command delegates argc/argv to aggregate_main; --help advertises its five operations. |
| invariants | CLI remains existing admitted set family. Parser/binder/normalizer/schema validity, structural validity, minimum proof, native execution and durable delivery are distinct authorities. The original set dispatcher and final process flush boundary retain their statements; the three-line integration adds a header, help line and command branch. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | Local narrow catches map expected component failures; legacy Error returns input2 or contract3 and stdexception internal3. A diagnostic exception propagates to the final main boundary, which emits a fixed fallback; main also checks the final stdout flush. |
| cost | Command-specific compile/scan/proof/native or I/O costs; ordinary DOM/dump diagnostics outside query grant. One extra command-name comparison per invocation; native epoch loops are unchanged. |
| Design | [docs/cli.md](../../../../cli.md), [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_support.md](../../../../sql_support.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md), [apps/crown/aggregate.cpp](../../../../../apps/crown/aggregate.cpp), [docs/sql_aggregate_input.md](../../../../sql_aggregate_input.md) |

```text
if (argc == 2 && std::string(argv[1]) == "--version") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Print build/API version. |
| inputs / outputs | Writes version/C++/set/API declaration and returns0. |
| invariants | Build metadata is not per-query proof or feature admission. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Fixed literal/version formatting and stdout I/O. |
| Design | [docs/cli.md](../../../../cli.md) |

```text
if (argc == 2 && std::string(argv[1]) == "--help") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Print top-level command families. |
| inputs / outputs | Writes usage and delegates detail help navigation. |
| invariants | Lists current commands only; no W05 bag/NULL CLI claim. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Fixed literal stdout I/O. |
| Design | [docs/cli.md](../../../../cli.md) |

```text
return crown::cli::workflow_main(argc,argv);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route known durable file and compiled-artifact commands. |
| inputs / outputs | Forwards original argv to private workflow dispatcher. |
| invariants | Only the explicit command list and compiled explain/validate form route here. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Fixed command spelling checks plus delegated work. |
| Design | [docs/cli.md §Durable results and benchmark reports](../../../../cli.md) |

```text
return crown::cli::explain_main(argc-1,argv+1);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route other EXPLAIN forms with shifted argv. |
| inputs / outputs | explain_main sees explain as argv0. |
| invariants | Its own resource/encoding/status presentation remains distinct. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Fixed shift plus delegated capture/explicit work. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/io/explain.hpp](../../../../../include/crown/io/explain.hpp) |

```text
if (argc >= 2 && std::string(argv[1]) == "validate-input") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a complete physical stream without an engine. |
| inputs / outputs | Admits supported JSONL/binary/CSV/selected legacy format and exact table; bounded catalog, reader peek/ack through EOF, summary. |
| invariants | Only source/domain/order validity; no maintained result/durable output. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Full stream decode/source-map plus DTO progress/JSON output. |
| Design | [docs/cli.md](../../../../cli.md), [docs/ingestion.md](../../../../ingestion.md) |

```text
if (argc >= 2 && std::string(argv[1]) == "parse-sql") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export syntax-only SQL parser result. |
| inputs / outputs | Bounded SQL read; syntax result0 or diagnostic1 on stdout. |
| invariants | No binding, structural/native admission or execution. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Parser limit+1 read/tokenization/DTO dump. |
| Design | [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_support.md](../../../../sql_support.md) |

```text
if (argc >= 2 && std::string(argv[1]) == "bind-sql") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve SQL names/types against supplied catalog. |
| inputs / outputs | Reads catalog/options, binds bounded SQL, emits typed binding or diagnostic0/1. |
| invariants | BoundSql alone is not structural/native/SQL-row-family runtime admission. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Catalog/options DOM and binder work/output. |
| Design | [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_support.md](../../../../sql_support.md) |

```text
if (argc >= 2 && std::string(argv[1]) == "normalize-sql") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export executable set-family SQL normalization or binding diagnostic. |
| inputs / outputs | Reads optional typed parameters/values, bind then normalize; emits result0/1. |
| invariants | Normalization replay identity is separate from supported structural/native admission. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | DOM/file copies + binder/normalizer/parameter specialization. |
| Design | [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_support.md](../../../../sql_support.md) |

```text
if (argc >= 2 && std::string(argv[1]) == "admit-sql") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform integrated existing SQL/structural admission. |
| inputs / outputs | Catalog/options plus bounded SQL yield AdmissionResult and status0/1. |
| invariants | Admission execution_status remains not_lowered; not W05 bag/runtime support. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Parser/binder/normalization/recognition and JSON report. |
| Design | [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_support.md](../../../../sql_support.md) |

```text
if (argc >= 2 && std::string(argv[1]) == "admit-normalized") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a strictly reconstructed normalization artifact. |
| inputs / outputs | Optional recognition work limit; resource Error becomes artifact-phase AdmissionResult. |
| invariants | Only narrow resource rejection is converted; contract/corruption faults propagate. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Full legacy read/reconstruction and metered recognition. |
| Design | [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_support.md](../../../../sql_support.md) |

```text
if (argc >= 2 && (std::string(argv[1]) == "validate-normalized"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate or canonicalize normalization without claiming structural admission. |
| inputs / outputs | Reader reconstructs artifact; emits canonical program or program_valid/not_checked. |
| invariants | Not_checked is explicit; JSON reader replay validation is distinct from backend support. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Whole artifact DOM/replay/canonical output. |
| Design | [docs/sql_admission.md](../../../../sql_admission.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/sql_support.md](../../../../sql_support.md) |

```text
if (argc >= 2 && (std::string(argv[1]) == "upgrade-cq"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform explicit upward CQ/normalization migration. |
| inputs / outputs | Parses target uint64 and invokes version-aware upgrade before writing. |
| invariants | Writers otherwise preserve version; unsupported migration rejects. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Full read/copy/validation/migration/output. |
| Design | [docs/schema_evolution.md](../../../../schema_evolution.md) |

```text
if (argc >= 2 && (std::string(argv[1]) == "fingerprint-cq"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute bounded canonical query identity. |
| inputs / outputs | Selects CQ/normalization identity profile and optional work limit; resource status emits identity_valid=false. |
| invariants | No partial hash on stop; digests navigate and do not authorize proof/native import. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Exact colored canonicalization work plus artifact/output copies. |
| Design | [docs/query_identity.md](../../../../query_identity.md) |

```text
if (argc >= 2 && (std::string(argv[1]) == "lower-plan"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a supplied exact set/query tree to physical plan. |
| inputs / outputs | Reads query/normalization/tree/options, explicitly upgrades normalizationv1→v2, emits plan or invalid_plan/resource result. |
| invariants | Checks structure/source semantics, not minimum-height or cheapest runtime. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Full artifact parse/validation/layout/index lowering/output. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

```text
if (argc >= 2 && std::string(argv[1]) == "support-trace") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run diagnostic logical native support epochs. |
| inputs / outputs | Reads actual physical plan/logical trace, applies updates, checks invariants and exports full snapshots; resource/support overflow stops at rejected sequence. |
| invariants | Logical native set event route, not physical SQL input or durable workflow. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Per epoch native work plus expensive invariant/full-state snapshot DOM retention. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md) |

```text
if (argc >= 2 && (std::string(argv[1]) == "validate-physical"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate/canonicalize the physical artifact representation. |
| inputs / outputs | Strict reader reconstructs physical plan, emits canonical form or valid/execution/hash metadata. |
| invariants | Hash/report flag does not manufacture plan/minimum/runtime authority. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Whole parse/replay/lowering validation and output. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

```text
if (argc >= 2 && (std::string(argv[1]) == "validate-catalog"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate/canonicalize standalone full catalog. |
| inputs / outputs | Strict reader admits catalog; emits canonical metadata or valid/version. |
| invariants | No database/FK data enforcement or query structural classification. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Catalog-wide validation/DOM/output. |
| Design | [docs/catalog.md](../../../../catalog.md) |

```text
const std::string command = argv[1];
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit legacy typed CQ structural/reference command arguments. |
| inputs / outputs | Restricts command/arity, reads full Document before branch. |
| invariants | Legacy read may be unbounded in bytes; document validity is not structural support/minimum. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Whole document read/parse/domain validation. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

```text
if (command == "canonicalize") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize a typed CQ document. |
| inputs / outputs | Writes validated document preserving declared version. |
| invariants | No structural/native backend admission inferred. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Full metadata/data/update serialization. |
| Design | [docs/cli.md](../../../../cli.md) |

```text
} else if (command == "validate-cq") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report typed CQ validity only. |
| inputs / outputs | Emits cq_valid and structural_admission:not_checked. |
| invariants | Classical set semantics; separate recognizer/tree/native steps remain required. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Fixed report after document validation. |
| Design | [docs/cli.md](../../../../cli.md) |

```text
} else if (command == "tree-oracle") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact structural minimum through compatibility search. |
| inputs / outputs | minimum_tree under optional default/unlimited work yields oracle report;0 only proved minimum. |
| invariants | Not an update evaluator, cost optimum or general physical operator shortcut. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Finite family exact search+proof and DOM output. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

```text
} else if (command == "verify-height") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently check original-query height certificate. |
| inputs / outputs | Reads bound certificate and replays verifier under chosen work; binding mismatch becomes invalid report. |
| invariants | Raw fields never authorize optimum; report.valid controls status0/1. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Certificate parse/binding and independent verification. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

```text
} else if (command == "validate-plan") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check original-query tree structural validity. |
| inputs / outputs | Reads named tree, validate_tree and writes violations/report status0/1. |
| invariants | Valid upper/tree height is separate from minimum proof and runtime cost. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Catalog/query/tree scans and verifier/output. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

```text
} else if (command == "classify") {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export structural recognition analysis. |
| inputs / outputs | analyze computes class/witness/failure-core fields. |
| invariants | Classification alone is not a supplied optimal tree or executable program. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Recognition scans and diagnostic encoding. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/planner_proofs.md §P06 retained execution and authority](../../../../planner_proofs.md) |

```text
crown::reference::Session session(document.catalog, document.query, document.initial);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the explicit reference recompute oracle. |
| inputs / outputs | Initial typed DB plus ordered logical set updates produce initial/current epoch output. |
| invariants | Reference backend is distinct from native maintained runtime and SQL nullable/bag APIs. |
| ownership | Private command/tool storage owns its ordinary strings/DOMs/handles; source/native owners retain their documented authority. No caller-visible native result is created merely by parsing a flag or diagnostic field. |
| failure | This branch returns its existing status. The final process boundary flushes/checks stdout and contains diagnostic exceptions; report failure never rolls back completed command effects. |
| cost | Complete relational recomputation per update and retained full JSON epoch report. |
| Design | [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/semantics.md](../../../../semantics.md) |

## B0006

[Lines 336–337](../../../../../apps/crown/main.cpp#L336); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L336-L337:sha256:f5fb7dc87eae38f010e6d225e952702918c47b7b728d0c079e1681018ff3ef4e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Keep diagnostic failures inside the process boundary and flush once at exit. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [apps/crown/main.cpp](../../../../../apps/crown/main.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 338–354](../../../../../apps/crown/main.cpp#L338); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc, char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish one CLI invocation with checked stdout and a final diagnostic exception boundary. |
| inputs / outputs | Borrows process argc/argv, invokes command_main once, flushes stdout, preserves its nonzero status; a failed flush after status0 returns2/io_error. Escaping bad_alloc returns3/resource_limit; other stdexception returns3/internal_error. |
| invariants | Existing command parsing, component diagnostics and typed durable outcomes remain in command_main. No command retry, source reapplication or durable rollback. A failed report does not establish whether earlier native/file work committed. |
| ownership | Only stack status plus fixed string literals; borrowed process standard streams outlive this call. No new query owner, observer, account, heap buffer or per-update state. |
| failure | The try includes command dispatch and flush. Diagnostic exceptions from inner catch bodies reach these last catches. Fixed fallback JSON avoids Json/owning-string construction. Standard stderr uses default nonthrowing iostream settings; an unwritable stderr may lose the diagnostic while the nonzero status remains. |
| cost | One dispatch and one explicit stdout flush per process, independent of query row/update count. Existing output/diagnostic formatting costs remain; no hot-path work or allocations are added to native execution. |
| Design | [docs/cli.md](../../../../cli.md), [apps/crown/workflow.cpp](../../../../../apps/crown/workflow.cpp), [apps/crown/explain.cpp](../../../../../apps/crown/explain.cpp), [tests/integration/cli_process_boundary.py](../../../../../tests/integration/cli_process_boundary.py), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |
