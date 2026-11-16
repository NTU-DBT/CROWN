# `src/recovery/generation_detail.hpp` — block usage map

[Source](../../../../../src/recovery/generation_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `167150ee75efa624bbeae1ea5ab6e62da0406ee112846d5463b0f244dc60aa85`. 97 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/recovery/generation_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 10–15](../../../../../src/recovery/generation_detail.hpp#L10) | Type/record definition: struct RetirementIntent |  · [reviewed contract](#b0002) |
| [B0003 · 16–17](../../../../../src/recovery/generation_detail.hpp#L16) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 18–23](../../../../../src/recovery/generation_detail.hpp#L18) | Type/record definition: struct RetirementBytes | returns bytes.data(); length · [reviewed contract](#b0004) |
| [B0005 · 24–37](../../../../../src/recovery/generation_detail.hpp#L24) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Internal single-root authority. Public metadata cannot construct/import it. · [reviewed contract](#b0005) |
| [B0006 · 38–38](../../../../../src/recovery/generation_detail.hpp#L38) | Callable definition: \[\[nodiscard\]\] const GenerationRoot& selected() const noexcept | calls ; returns selected_ · [reviewed contract](#b0006) |
| [B0007 · 39–39](../../../../../src/recovery/generation_detail.hpp#L39) | Callable definition: \[\[nodiscard\]\] bool has_selection() const noexcept | calls ; returns selected_.generation!=0 · [reviewed contract](#b0007) |
| [B0008 · 40–40](../../../../../src/recovery/generation_detail.hpp#L40) | Callable definition: \[\[nodiscard\]\] bool selection_attempted() const noexcept | calls ; returns attempted_ · [reviewed contract](#b0008) |
| [B0009 · 41–41](../../../../../src/recovery/generation_detail.hpp#L41) | Callable definition: \[\[nodiscard\]\] std::uint64_t operations() const noexcept | calls ; returns operations_ · [reviewed contract](#b0009) |
| [B0010 · 42–42](../../../../../src/recovery/generation_detail.hpp#L42) | Callable definition: \[\[nodiscard\]\] std::uint64_t validation_work() const noexcept | calls ; returns work_ · [reviewed contract](#b0010) |
| [B0011 · 43–43](../../../../../src/recovery/generation_detail.hpp#L43) | Callable definition: \[\[nodiscard\]\] const std::optional&lt;RetirementIntent&gt;& retirement() const noexcept | calls ; returns retirement_ · [reviewed contract](#b0011) |
| [B0012 · 44–79](../../../../../src/recovery/generation_detail.hpp#L44) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Opaque selected bytes only: native/SQL decoding remains in the caller. · [reviewed contract](#b0012) |
| [B0013 · 80–97](../../../../../src/recovery/generation_detail.hpp#L80) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::recovery::detail · [reviewed contract](#b0013) |

## B0001

[Lines 1–9](../../../../../src/recovery/generation_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:181323f3c70fe287add7851362438af1be8cfb1c2ea8c7e002f257d0a24d9e2d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define private root/retirement ownership beside public descriptive recovery records. |
| inputs / outputs | Generation DTOs, sink types and Linux descriptor owner definitions available internally. Forward-declare both concrete SQL Session classes for narrow private continuity friendship. |
| invariants | Only actual locked GenerationOwner and session barriers drive publication/deletion; public metadata alone is not authority. No new public authority or runtime operation is introduced. |
| ownership | No static owner or filesystem access is created by inclusion. The declarations own no state. |
| failure | No runtime admission occurs here. No runtime failure path. |
| cost | Compile-time dependency boundary; implementation costs are attached below. No executable work. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0002

[Lines 10–15](../../../../../src/recovery/generation_detail.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L10-L15:sha256:9d60135250ce4ce744a07d26bba5f248188b71c3c8d5aa9b823e281d4be3d039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record the exact historical cleanup interval and sink lineage for resumable retirement. |
| inputs / outputs | Before-root, immutable sink Header and acknowledged generation/sequence; fixed equality. |
| invariants | Wire v1/v2 omit before.delivery; runtime anchor comparison restores the actual selected delivery anchor. Equality compares stored fields and is not receipt validation. |
| ownership | Fixed-value record; owns no fd, lock, file bytes or account. |
| failure | Default/edited records are not validated. encode/inspect and GenerationOwner recheck the relevant invariants. |
| cost | Fixed-size copying/comparison; no dynamic allocation. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0003

[Lines 16–17](../../../../../src/recovery/generation_detail.hpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L17:sha256:5bb0dd755ae89407cfd552e9ef54e944fe82b4cceb6ba902cc515681ae654081
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fix legacy and plan-aware retirement frame lengths. |
| inputs / outputs | 724-byte v1 and 788-byte v2 constants. |
| invariants | v2 adds exactly a 64-byte selected-plan hash; version/flags/body/checksum checks select a matching size. |
| ownership | Constants own no resource. |
| failure | Malformed lengths reject in inspect_retirement_intent before fixed-offset reading. |
| cost | Constant-size wire envelopes; hashing still visits the actual chosen variant bytes. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0004

[Lines 18–23](../../../../../src/recovery/generation_detail.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L23:sha256:fc4d07b97f858b97eb9a9aa31f1005e28fc574c792364ac6892107b93293cb99
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the maximum-size retirement wire result on the stack. |
| inputs / outputs | Zero-filled 788-byte array, default length724, data/size borrowed accessors. |
| invariants | Only the leading length bytes are the frame; encoder chooses724/788. This mutable internal carrier does not validate arbitrary length edits. |
| ownership | Array owns bytes; data() borrows them for the carrier lifetime. |
| failure | Accessors are noexcept and do no checking; callers pass only encoded output to publish. |
| cost | Fixed788-byte storage and fixed-value copies; no account allocation. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0005

[Lines 24–37](../../../../../src/recovery/generation_detail.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] RetirementIntent inspect_retirement_intent(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare complete fixed-frame retirement validation. |
| inputs / outputs | Borrowed immutable bytes in; descriptive fixed RetirementIntent out. |
| invariants | Checks exact variant length, magic/version/flags/body/checksum and lineage fields; query/root/sink-owner selection is checked separately by GenerationOwner. |
| ownership | Output owns metadata only; no input borrow survives. |
| failure | GenerationFailure for framing/binding; policy validation can propagate ImageFailure. No filesystem mutation. |
| cost | O(724 or788) scan/hash, no successful-path heap graph. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
[[nodiscard]] RetirementBytes encode_retirement_intent(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare serialization of a checked cleanup intention. |
| inputs / outputs | RetirementIntent in; stack-owned exact v1/v2 bytes out. |
| invariants | Validates fixed binding/interval/policy; selected delivery is deliberately omitted from the wire intent. |
| ownership | Copies metadata into fixed storage; does not retain an actual sink receipt or root lock. |
| failure | Validation failure precedes publication; this codec performs no filesystem operation. |
| cost | Fixed-size encode plus SHA; caller separately consumes generation work. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
class GenerationOwner {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one anchored directory and advisory root lock through generation operations. |
| inputs / outputs | Path/query/create flag/GenerationLimits construct; move transfers live ownership; copy and move assignment are forbidden. |
| invariants | Constructor validates/open-locks/syncs/reads actual selected root and retirement. Move preserves counters/candidates/outcome and transfers both fds without another syscall; moved-from selected root is cleared and it is only discarded. The upper R2 Session is a private friend only to perform the existing fixed root continuity read; it gains no alternate DTO selection, retirement or mutable native authority. |
| ownership | FileDescriptor members retain directory and lock; stack preparation may be moved into an account-funded session holder. Destructor releases fds, not root/candidate files. |
| failure | Failed construction releases acquired fds. Selection uncertainty remains latched until destruction/reopen; creating a new report cannot reset it. |
| cost | Constructor has bounded filesystem validation; move copies fixed metadata and transfers fd integers; destruction uses best-effort raw closes. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0006

[Lines 38–38](../../../../../src/recovery/generation_detail.hpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L38:sha256:010fc07dfe41700505f0e5bc369f2deea27ab6691b5fd6568db25a8329d8c7ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the owner's last successfully adopted selection. |
| inputs / outputs | Const reference to selected_ out. |
| invariants | This snapshot changes only after successful internal adoption/publication; if selection_attempted is true it may differ from whichever on-disk root survived. |
| ownership | Borrowed member reference invalidated by owner destruction/move or later selection replacement. |
| failure | No validation, I/O or error; caller must also honor owner health and session state. |
| cost | O(1), no allocation. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0007

[Lines 39–39](../../../../../src/recovery/generation_detail.hpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L39:sha256:a41b8541a0412bf0d06a6705c8d6b3678abd394f1d3cde539cd6b7ce16032e80
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report whether this owner holds a nonzero selected generation. |
| inputs / outputs | Boolean derived from selected_.generation. |
| invariants | Presence alone does not imply health or successful last root attempt; moved-from selected_ is empty. |
| ownership | No ownership transfer. |
| failure | No failure or validation. |
| cost | O(1). |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0008

[Lines 40–40](../../../../../src/recovery/generation_detail.hpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L40:sha256:354b309cb38aeb809f3ca0fe81fa62e233cf6b835fcf202fcc3b69872feac7f5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the irreversible-selection uncertainty latch to session guards. |
| inputs / outputs | attempted_ Boolean out. |
| invariants | Set when root link/rename is dispatched, before injected syscall failure; cleared only after successful selected_ handoff. Quota rejection before dispatch does not set it. |
| ownership | Reads private owner state; external mutation is unavailable. |
| failure | No throw; true requires session recovery-required handling and retained lock rather than rollback/retry. |
| cost | O(1). |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0009

[Lines 41–41](../../../../../src/recovery/generation_detail.hpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L41:sha256:dfabc85d78b771351cba27c06086d5916155fd93e6b83c56cd5e691c7a811f6d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report cumulative admitted generation syscall attempts. |
| inputs / outputs | operations_ value out. |
| invariants | Retries and bounded temporary cleanup consume the same monotone counter; raw descriptor destruction and quota-rejected close cleanup are not counted here. |
| ownership | Copies a scalar counter; no new grant is created. |
| failure | No failure or I/O. |
| cost | O(1); counts attempts, not successful syscalls, bytes or elapsed time. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0010

[Lines 42–42](../../../../../src/recovery/generation_detail.hpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L42:sha256:4320c44da453faafbf9db792045b3e3ef32047e5e501c6095bd295741fedd36a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report cumulative generation validation debits. |
| inputs / outputs | work_ value out. |
| invariants | Units include payload hashing and actual fixed-root/retirement variant reads/encodes as charged by implementations; these are separate from syscall, codec and native build grants. |
| ownership | Scalar report is not mutable budget authority. |
| failure | No failure or charging. |
| cost | O(1), no scan. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0011

[Lines 43–43](../../../../../src/recovery/generation_detail.hpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L43:sha256:4b51ff37a9e016e263928aae73e536aa45402e25d872be97db07d30590e6810d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose whether an actual validated durable retirement intent needs continuation. |
| inputs / outputs | Const borrowed optional metadata out. |
| invariants | Presence is loaded/published under this lock; the session must supply validated sink lineage before replay/repair/resume. |
| ownership | Borrows owner member state; no new lock or receipt is produced. |
| failure | No throw; absence does not itself authorize arbitrary deletion. |
| cost | O(1). |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0012

[Lines 44–79](../../../../../src/recovery/generation_detail.hpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::array<char,4096> checkpoint_path(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the generation checkpoint pathname from the admitted root prefix. |
| inputs / outputs | Generation in; zero-terminated fixed4096-byte array out. |
| invariants | Constructor reserved suffix capacity; path formation itself accepts any generation and grants no selection/deletion authority. |
| ownership | Returned array owns path bytes independently of owner. |
| failure | No filesystem check or allocation; internal fixed-suffix bounds rely on constructor. |
| cost | O(root path length)+16 hex digits+fixed suffix; initializes the fixed array. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
[[nodiscard]] std::array<char,4096> journal_path(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the matching generation WAL pathname. |
| inputs / outputs | Generation in; fixed owning NUL-terminated path out. |
| invariants | Names use .g plus16 lowercase hex digits and .wal; a pathname is not a WAL owner and this class does not create the WAL. |
| ownership | Independent fixed array result. |
| failure | No I/O or admission; constructor path reserve is the bound. |
| cost | O(root path length) plus fixed array initialization/formatting. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
[[nodiscard]] std::array<char,4096> plan_path(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the selected/candidate descriptor pathname. |
| inputs / outputs | Generation in; fixed owning NUL-terminated path out. |
| invariants | Names use the same admitted root namespace and .plan suffix; actual plan content is checked by read_plan/publication callers. |
| ownership | Independent fixed array result. |
| failure | No I/O or plan validation. |
| cost | O(root path length) plus fixed array initialization/formatting. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
[[nodiscard]] ImageVector<char> read_plan(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load exactly the selected descriptor into the supplied receiving account. |
| inputs / outputs | MemoryAccount in; owning image byte vector out. |
| invariants | Requires healthy owner and selected plan hash; rereads root before/after, bounds regular file size, checks EOF/stamp and whole-file SHA. Compiler semantics remain a later boundary. |
| ownership | One receiving-account byte vector owns returned bytes; local file fd is released on every exit; root lock remains owned. |
| failure | Failures discard private bytes and close the fd; work/operations stay consumed. No repair or selection mutation is performed. |
| cost | O(plan bytes) read/hash and allocation plus two bounded root rereads; no second query account. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
void prepare_next(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove only the immediate unselected candidate set before retrying rotation. |
| inputs / outputs | Next generation in; its .ckpt/.wal/.plan names removed and directory synchronized. |
| invariants | Healthy existing selection, no retirement, exact successor and unchanged actual root required. Never used for initial creation or selected/older names. |
| ownership | Retains root lock; clears private candidate markers before guarded cleanup. |
| failure | Failure can leave some unselected names removed; selected history remains. Cumulative operation/work grants are not reset for retry. |
| cost | Three bounded-name unlink loops plus root check/directory sync; EINTR consumes attempts. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
void publish_checkpoint(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish and remember one complete candidate checkpoint under the root lock. |
| inputs / outputs | Generation and borrowed bytes in; private candidate generation/hash recorded after successful durable no-replace publication. |
| invariants | Bounds size and successor state; hashes bytes but does not inspect their session semantics. Session caller validates and creates the matching WAL separately. |
| ownership | Borrows stable input for hashing/writing; owns only fixed candidate identity afterward. |
| failure | Failure may leave an unselected candidate file; no root selection occurred. Do not infer absence from unchanged selection outcome; prepare_next can clean the exact successor. |
| cost | O(bytes) SHA/write plus private-file/directory fsync; fixed temporary naming. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
void publish_plan(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish and remember the complete candidate descriptor without selecting it. |
| inputs / outputs | Positive generation and nonempty borrowed descriptor bytes in. |
| invariants | Bounds plan bytes and successor; publication records SHA only on success. Descriptor/checked-compiler/equivalence validation belongs to session preparation. |
| ownership | Caller retains bytes through the synchronous write; owner stores fixed hash/generation. |
| failure | Failure leaves root unchanged but may leave unselected final file; no automatic rollback of that file. |
| cost | O(bytes) hash/write plus bounded temporary/open/link/unlink/fsync work. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
void publish_root(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the privately recorded durable checkpoint and optional descriptor. |
| inputs / outputs | Next GenerationRoot in; selected_ changes after root publication succeeds. |
| invariants | Query, candidate generation/hash, floor, monotone frontiers and plan continuity are checked. This owner does not verify/create the matching WAL or establish session quiescence; actual session callers do so before selection. |
| ownership | Retains directory/lock; copies fixed selected metadata only after durable link/rename+directory sync. |
| failure | Once root link/rename is admitted, attempted_ blocks further healthy operations until successful handoff; ambiguity is resolved by reopening, never rewriting the old root. |
| cost | Fixed root variant encode/SHA plus temporary publication. All account-funded native installation preparation belongs before this boundary. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
void validate_retirement(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a pending recorded retirement against an actual local sink owner. |
| inputs / outputs | const sink::File reference in; no return value. |
| invariants | Checks current File state, recorded root anchor, selected delivery prefix or base, exact immutable header and acknowledged frontiers. Mutable public reports alone do not substitute for File. |
| ownership | Borrows live file and private intent; does not acquire/delete files. |
| failure | Binding/state/prefix failure propagates without mutation. |
| cost | Fixed metadata comparisons plus indexed prefix/state queries; no historical rescan in this helper. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
void retire_history(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Continue only an authorized durable historical cleanup range. |
| inputs / outputs | Private sink Receipt, caller-read checkpoint bytes and receiving account in. |
| invariants | Session establishes quiescence and verified delivery; owner rechecks actual root/intent/receipt, rereads selected plan when present, confirms checkpoint hash/name, publishes intent, selects floor, then deletes only recorded older names. |
| ownership | Retains lock; receipt is opaque native evidence. Read-plan scratch uses existing receiving account. Caller checkpoint bytes remain immutable/live. |
| failure | Before root selection normal rejection retains selected history. Later failures can leave selected floor/partly deleted history/intent; resume recorded protocol. Root uncertainty latches attempted_; no rollback. |
| cost | O(checkpoint/plan bytes)+O(recorded generations) three-name unlink/fsync cleanup, each within operation/work limits. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
[[nodiscard]] std::array<char,4096> path(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep private path, root-read and retirement helpers behind the locked owner. |
| inputs / outputs | Fixed path/name builders; root reading, retirement reading/floor selection, checkpoint confirmation, private publication and bounded cleanup. |
| invariants | Builders rely on admitted suffix capacities; confirm_checkpoint rehashes supplied bytes and syncs the named inode/size without rereading checkpoint content. Trusted cooperating namespace/caller invariants are necessary. |
| ownership | Helpers use owner descriptors and fixed arrays; read_plan is the explicit dynamic byte owner. |
| failure | healthy rejects attempted selection; cleanup returns false rather than masking original failure. Private publication catches preserve outcomes and remove only temporary names. |
| cost | Fixed path/root metadata plus O(payload/history) work as applicable; no generic recovery or rollback layer. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
std::int64_t call(GenerationStage
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Centralize generation syscall counting, dispatch and safe retry policy. |
| inputs / outputs | Stage/count/fds/names/buffer/offset/stat parameters into call/checked/transfer. |
| invariants | Internal callers provide correctly typed valid pointers and bounded offsets. Ordinary admitted attempts consume limits; close/link/root-rename are not blindly retried on EINTR. Only the explicit emergency_cleanup flag from the eight-attempt failure helper bypasses the ordinary operation cap; normal post-link unlink/EINTR does not. |
| ownership | Dispatch borrows buffers/fds; named temporary cleanup and descriptor RAII remain separate owners. |
| failure | Closing still releases fd when ordinary quota is exhausted. Root dispatch latches attempted/unknown; transfer rejects zero progress. |
| cost | Every retry costs an attempt; transfer chunks add O(bytes/chunk) calls, cleanup&lt;=8 attempts outside ordinary quota but not counter-overflow. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [tests/unit/file_cleanup_quota_test.cpp](../../../../../tests/unit/file_cleanup_quota_test.cpp) |

```text
// Opaque selected bytes only: native/SQL decoding remains in the caller.
// Hash, bounded I/O, regular-file identity, EOF and root continuity precede
// return. Empty checkpoint payloads are allowed by this lower file boundary.
[[nodiscard]] ImageVector<char> read_checkpoint(const resource::MemoryAccount&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose selected checkpoint bytes to an internal caller without decoding or importing checkpoint state. |
| inputs / outputs | The internal GenerationOwner requires an already selected generation and a receiving MemoryAccount. |
| invariants | The new API promises byte/root/file validation only; SQL/native decoding, WAL validation, replay and durable R2 admission remain caller responsibilities. |
| ownership | Returned ImageVector uses the supplied account and is owned by the caller; the GenerationOwner lock remains live for the call. |
| failure | Invalid selection, file/root drift, limit/hash errors and account failures are reported by existing lower file failure types. |
| cost | Declaration only. Runtime work is shared with \`read_plan\` through \`read_selected\`. |
| Design | [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [docs/sql_aggregate_descriptor.md §Selected checkpoint bytes](../../../../sql_aggregate_descriptor.md) |

```text
[[nodiscard]] ImageVector<char> read_selected(const resource::MemoryAccount&,bool plan);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the private common reader used by read_plan and read_checkpoint. |
| inputs / outputs | The account funds the returned bytes; \`plan\` selects the existing plan path/cap/hash or checkpoint path/cap/hash. |
| invariants | Private helper preserves each file’s original acceptance conditions, including permitting empty checkpoint bytes but not empty plan bytes. |
| ownership | Only GenerationOwner calls it while holding its actual lock/state; returned storage belongs to the supplied account. |
| failure | Failure behavior is the existing GenerationFailure/account path of the selected read operation. |
| cost | Declaration only; implementation performs bounded I/O/hash validation. |
| Design | [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [docs/sql_aggregate_descriptor.md §Selected checkpoint bytes](../../../../sql_aggregate_descriptor.md) |

```text
friend class ::crown::recovery::sql_aggregate::Session;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Permit both concrete SQL aggregate and SQL rows receivers to perform the same private selected-root continuity read. |
| inputs / outputs | The friend calls private read_root(false,false) under its stable GenerationOwner lock and compares the exact selected value. The additional sql_rows::Session friend receives only this existing private continuity access, not a public mutable root/import API. |
| invariants | This changes C++ access only. R1 generation/retirement behavior, root wire formats and physical owner layout stay the same. Concrete single-root authority, locks, candidate identities, cumulative grants and retirement semantics are unchanged; plain rows does not acquire retirement from descriptive DTOs. |
| ownership | No alternate root/file/native owner or retained callback. Friendship creates no owner, FD, copied state, source graph or account. |
| failure | The existing read_root validation propagates; Session supplies the upper fail-stop latch. No new runtime failure/retry path is introduced by the declaration. |
| cost | No field, virtual dispatch, allocation or automatic runtime operation. Compile-time access change only; no per-operation or per-query runtime overhead. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0013

[Lines 80–97](../../../../../src/recovery/generation_detail.hpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GenerationLimits limits_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store fixed root authority and its observed persistent selection. |
| inputs / outputs | Limits, anchored directory/lock descriptors, root path/name, selected root and optional retirement. |
| invariants | Limits persist across operations; private selected/retirement state is changed only by validated implementations. Public copies do not mutate it. |
| ownership | Descriptors own OS resources; other fields own fixed metadata only. Root path arrays do not allocate. |
| failure | Destruction closes descriptors best-effort and does not unlink any named artifact. |
| cost | Fixed per-owner storage, including4096/256-byte path buffers. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

```text
std::array<char,32> query_id_{};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep cumulative grants, prepared candidate identities and selection outcome together. |
| inputs / outputs | Query id, operation/work counters, checkpoint/plan candidate generation+SHA, outcome/target and attempted flag. |
| invariants | Candidates are recorded only after their individual publish returns; target drives test stage/outcome classification. outcome describes selection, not absence of candidates. attempted guards reuse independently of descriptive selected_. |
| ownership | All values remain private; move carries them with actual fds. |
| failure | Failures retain consumed grants and may retain candidates; only documented prepare/select transitions reset candidate markers or attempted state. |
| cost | Fixed scalar/hash storage; no growing history/cache. |
| Design | [docs/generations.md](../../../../generations.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [src/recovery/generation.cpp](../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../src/recovery/generation_retirement.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |
