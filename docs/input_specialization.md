# Prepared SQL input programs

`CompiledProgram::prepare_inputs` prebinds admitted SQL occurrence expressions
to column-copy and fixed-operation workers. Execution stays serial. The
`threaded_v1` name describes instruction dispatch through function pointers.
The ordinary interpreter remains the default. This implements the compiled-input
program option in [Refactor X09 and the component ablation](../Refactor.md).

The compiler derives every instruction from the existing normalized program;
callers supply no instructions, callbacks or query registrations. Both modes use
the unchanged [scalar evaluator](../src/frontend/sql_scalar.hpp), storage,
change propagation, journal and output paths. Preparation changes neither the
versioned physical descriptor nor its physical/source hashes.

```cpp
auto account = crown::resource::MemoryAccount::create(64U * 1024U * 1024U);
std::optional<crown::storage::IndexWorkAllowance> cold_work;
if (const auto& indexed = source.options().indexed_storage)
  cold_work.emplace(indexed->per_operation, true);
auto prepared = crown::CompiledProgram::prepare_inputs(
    account, source, {}, cold_work ? &*cold_work : nullptr);
```

Here `source` is a genuine compiled SQL program and the caller starts one cold
preparation operation. Code already inside an admitted operation must borrow its
existing allowance. Indexed preparation checks the original grant against the
physical per-operation cap before consuming any work. Plain CQ programs without
normalized SQL reject preparation. A normalized constant-result program may have
zero executable ports and zero instructions.

| API value | Meaning |
| --- | --- |
| `input_execution()` / `input_execution_key()` | Actual interpreter or prepared dispatch and its versioned implementation key. |
| `input_preparation_limits()` | Retained finite work/instruction policy; absent for the interpreter. |
| `input_preparation().work` | Logical preparation checkpoints, separate from base receiving-copy work. |
| `instructions` | Prepared occurrence instruction count. |
| `metadata_bytes` | Actual instruction/range vector capacity bytes; excludes fixed owner/Data/control overhead. |
| `base_freeze_work` | Five IndexWork domains consumed by the receiving base copy. |

The receiving MemoryAccount funds all metadata, including the fixed overhead
excluded from `metadata_bytes`. A denied preparation leaves the source unchanged
and releases its unpublished receiving allocations. Attempted cold work and peak
memory still count. The factory reuses normal storage admission and RAII cleanup.

A CompiledProgram receiving freeze rebuilds prepared views in the new account.
Native replanning preserves the actual basis's execution policy and finite
preparation limits. Physical descriptor export/reconstruction carries no execution
policy and starts interpreted; prepare the reconstructed program explicitly to
opt back in. Image restoration with an expected prepared CompiledProgram retains
its selected mode. Each new runtime owner funds its own admitted metadata.

The existing C05 artifact cache separates prepared and interpreted programs and
different preparation limits. Its versioned suffix leaves interpreter binding
bytes unchanged. See the exact [cache frames](selection_binding.md) and
[logical payload charges](selection_accounting.md). There is no global prepared
program cache. Repeated updates on one runtime reuse its admitted program.

Preparation replaces expression-variant lookup with prebound workers. Each
worker passes a fixed operator to the shared evaluator, allowing an optimizing
compiler to fold its opcode dispatch. Each normalized input still allocates/copies the
existing value vector over all bound expressions; scalar work and result
semantics remain identical. This is a concrete dispatch specialization, with
extra cold copy/preparation and table memory. It does not compile the whole
executor or generate per-query machine code.

`crown_input_specialization` and [the study runner](../tools/run_input_specialization.py)
compare the same SQL, actual tree, backend, trace, native work and output demand.
Both commands drain signed deltas and the full snapshot after each physical
input; initialization includes the initial snapshot. Verification records exact
SQLite-checked captures with null clocks. Measurement records finite nonnegative
phase clocks and null captures. The preparation timer includes the receiving base
copy, and each fresh owner admits its own copy. Shared executable bytes, extra
table bytes, cold preparation and owner/loop costs remain separate.

The generated trace corpus contains join-only controls, local predicates, casts,
repeated projections, NULL logic, self aliases, EXISTS and constant false. Exact
prefixes must pass on both modes/backends before any controlled timing. Finite
results, variability and slower outcomes are retained without a predetermined
speedup. The [experimental report guide](experimental_report.md) describes raw
links and cross-machine methodology.

Build and run the methodology from a fresh source/build/output prefix. Select
`task_cpu` from the machine's permitted affinity. The resulting build identities
and timing observations are new; exact result checks use the same corpus.

```sh
cmake -S "$task_source" -B "$task_build" -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_COMPILER="$task_cxx" -DBUILD_TESTING=OFF
cmake --build "$task_build" --parallel 2 --target \
  crown crown_measure_workload crown_input_specialization
PYTHONDONTWRITEBYTECODE=1 python3 "$task_source/tools/run_input_specialization.py" \
  --source "$task_source" --build-dir "$task_build" \
  --crown "$task_build/crown" --collector "$task_build/crown_measure_workload" \
  --client "$task_build/crown_input_specialization" --output "$task_new_study" \
  --cpu "$task_cpu" --width 2 --width 8 --width 32 --warmups 1 --repetitions 3 \
  --schedule-seed 20261115 --max-total-bytes 2147483648
```

For correctness-only receiving, add `--preflight-only`; no measurement child is
then launched. Each normal run completes all declared variant gates before
starting its first excluded warmup or measured owner. Exact commands, raw
resources, source/build/launcher pins and end-of-run closure stay in the new
study.
