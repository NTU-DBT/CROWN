# Troubleshoot a local workflow

Start with the command's structured diagnostic and preserve the SQL, catalog,
input prefix, options and source/build versions needed to reproduce it. Stdout
reports and process exit alone do not establish a durable commit. See
[CLI diagnostics](cli.md#durable-results-and-benchmark-reports).

| Symptom | Meaning and next action |
| --- | --- |
| `unsupported_semantics`, `cyclic_body`, `non_free_connex` | Inspect the admission diagnostic; `admit-sql` can report frontend/structure status without a compiled artifact. EXPLAIN needs a successfully compiled artifact. Use the [supported interface](guarantees.md#choose-the-interface). An acyclic body can still have a non-free-connex projection; a full head does not make a cyclic body acyclic. |
| `resource_limit` during compile or proof replay | Identify the stage and its grant: admission/physical options, search, proof replay or report export have separate limits. Increasing search work alone may not address the failure. Preserve the incomplete status; do not call an incumbent a minimum. |
| Invalid catalog binding, sequence, source position or row type | Check the exact catalog and physical column order, canonical digest, contiguous sequence and increasing per-source offsets. Recreate bound input from the intended template; do not rewrite accepted recovery history. See [ingestion](ingestion.md). |
| `input_failed` on another read | A previous consuming preparation failed. Recreate the reader explicitly after correcting the input. A complete cached event rejected by the engine is the separate retryable case. |
| Update rejected while a result cursor is open | Drain the terminal null or call `cancel()`. Returning the last row alone leaves the read lease open. Do not add a retry loop around an active lease. |
| New session cannot use existing root/sink paths | Choose new names for a new execution. Use `restore` and the original input prefix when resuming an existing execution. |
| I/O outcome is `unknown`, or stdout failed after publication | Preserve the files and recover before retrying. Read durable sink receipts; a missing report is not evidence that no commit happened. |
| Query account exhausted despite a small output | Inspect metadata, retained payload, spool and current owners. Output size is not the account/RSS bound. See [query memory](query_memory.md). |
| An installed consumer cannot find `Crown` | Pass the installation prefix to `CMAKE_PREFIX_PATH`, or its package directory to `Crown_DIR`. Copy an installed example and keep source/build include paths out of that consumer. See [installation](cli.md#local-cmake-installation-and-consumer). |
| Generated source cards are stale | Review the changed source and affected contract, then regenerate and check. Do not suppress the hash check. See [development](development.md#write-code-for-human-inspection). |

The set, nullable-row and aggregate interfaces have different command/input
formats. The [aggregate CLI](sql_aggregate_input.md) additionally requires its
session binding and uses weight replacements, not set insert/delete records.
Use its documented pending-Input, output-delivery and repair rules.

Historical verification packets report their original source and configurations.
Consult the [current handoff](handoff.md) and [task ledger](task_ledger.md) for later
changes and open gates. A local fix or passing finite trace does not certify a
whole release or remove a documented qualification.
