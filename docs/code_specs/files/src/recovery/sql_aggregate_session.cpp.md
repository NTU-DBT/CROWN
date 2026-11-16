# `src/recovery/sql_aggregate_session.cpp` — block usage map

[Source](../../../../../src/recovery/sql_aggregate_session.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `7f40fa8f3ac500aee180a825e542eaba681d30a1f13dda5b7c8d81afb891dd93`. 215 lines partitioned into 39 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/recovery/sql_aggregate_session.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–10](../../../../../src/recovery/sql_aggregate_session.cpp#L10) | Callable definition: void require(bool condition,SessionFault fault) | calls SessionFailure; guard void require(bool condition,SessionFault fault) { if(!condition)throw SessionFailure(fault); } · [reviewed contract](#b0002) |
| [B0003 · 11–19](../../../../../src/recovery/sql_aggregate_session.cpp#L11) | Callable definition: std::optional&lt;RejectReason&gt; semantic(std::string_view code) noexcept | calls ; returns RejectReason::weight_mismatch; RejectReason::source_overflow; source comment (unverified): // Work/memory/contract/underflow errors never become semantic Reject. · [reviewed contract](#b0003) |
| [B0004 · 20–22](../../../../../src/recovery/sql_aggregate_session.cpp#L20) | Callable definition: GenerationDeliveryAnchor anchor(const SinkReceipt& receipt) | calls prefix, header; returns {receipt.header().sink_id,prefix.physical_sequence,prefix.bytes,prefix.content_sha256} · [reviewed contract](#b0004) |
| [B0005 · 23–24](../../../../../src/recovery/sql_aggregate_session.cpp#L23) | declares aliases. | source comment (unverified): // namespace session_detail · [reviewed contract](#b0005) |
| [B0006 · 25–31](../../../../../src/recovery/sql_aggregate_session.cpp#L25) | Callable definition: Session::Data::Data(const resource::MemoryAccount& memory,const SessionLimits& requested, ::crown::recovery::detail::GenerationOw… | calls account, root, std::move, descriptor · [reviewed contract](#b0006) |
| [B0007 · 32–35](../../../../../src/recovery/sql_aggregate_session.cpp#L32) | Callable definition: void Session::Data::ready() const | calls require, requires_reopen, ready, has_selection; guard require(!poisoned && wal && sink && !wal-&gt;requires_reopen() && !sink-&gt;requires_reopen()); · [reviewed contract](#b0007) |
| [B0008 · 36–53](../../../../../src/recovery/sql_aggregate_session.cpp#L36) | Callable definition: Session::Data::Head Session::Data::own(DecodedInput input) | calls view, require, size, find; guard require(progress.sequence&lt;UINT64_MAX && view.command_sequence==progress.sequence+1,SessionFault::pr…; returns {std::move(input),std::move(position)} · [reviewed contract](#b0008) |
| [B0009 · 54–64](../../../../../src/recovery/sql_aggregate_session.cpp#L54) | Callable definition: Session::Data::Prepared Session::Data::prepare() | calls require, has_value, view, prepare_batch; guard require(head.has_value());const auto view=head-&gt;input.view();; returns {native.prepare_batch({native.sequence()+1,view.replacements}),{}}; {{},reason}; source comment (unverified): // The genuine source/native/group token is the only rollback mechanism. · [reviewed contract](#b0009) |
| [B0010 · 65–69](../../../../../src/recovery/sql_aggregate_session.cpp#L65) | Callable definition: Limits Session::Data::codec_limits(bool output) const | calls require, std::min; guard require(replayed.codec_work&lt;=limits.replay_codec_work,SessionFault::limit);; returns result · [reviewed contract](#b0010) |
| [B0011 · 70–73](../../../../../src/recovery/sql_aggregate_session.cpp#L70) | Callable definition: void Session::Data::charge_codec(std::uint64_t amount) | calls require; guard require(replayed.codec_work&lt;=limits.replay_codec_work && amount&lt;=limits.replay_codec_work-replayed.… · [reviewed contract](#b0011) |
| [B0012 · 74–82](../../../../../src/recovery/sql_aggregate_session.cpp#L74) | Callable definition: Frame Session::Data::epoch(const runtime::sql_aggregate::Epoch& output,bool replaying) | calls require, view, frame, encode; guard require(head && output.captured,SessionFault::transition);; returns result · [reviewed contract](#b0012) |
| [B0013 · 83–92](../../../../../src/recovery/sql_aggregate_session.cpp#L83) | Callable definition: void Session::Data::publish(Prepared& prepared,std::optional&lt;Frame&gt; output) | calls view, commit, publish, std::move; source comment (unverified): // All token/output/progress storage was funded before the durable decision. · [reviewed contract](#b0013) |
| [B0014 · 93–101](../../../../../src/recovery/sql_aggregate_session.cpp#L93) | Callable definition: void Session::Data::observe(const runtime::sql_aggregate::Epoch& output) | calls require, add; guard const auto add=\[\](std::uint64_t& total,std::uint64_t value) {require(value&lt;=UINT64_MAX-total,Sessio… · [reviewed contract](#b0014) |
| [B0015 · 102–102](../../../../../src/recovery/sql_aggregate_session.cpp#L102) | Explanatory comments or spacing. |  |
| [B0016 · 103–103](../../../../../src/recovery/sql_aggregate_session.cpp#L103) | Callable definition: Session::Session(resource::AccountedUnique&lt;Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0016) |
| [B0017 · 104–105](../../../../../src/recovery/sql_aggregate_session.cpp#L104) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0017) |
| [B0018 · 106–106](../../../../../src/recovery/sql_aggregate_session.cpp#L106) | Callable definition: Session::Data& Session::data() const | calls require, bool, ready; guard Session::Data& Session::data() const { require(bool(data_));data_-&gt;ready();return *data_; }; returns *data_ · [reviewed contract](#b0018) |
| [B0019 · 107–109](../../../../../src/recovery/sql_aggregate_session.cpp#L107) | Callable definition: bool Session::requires_reopen() const noexcept | calls requires_reopen; returns !data_ \|\| data_-&gt;poisoned \|\| !data_-&gt;wal \|\| !data_-&gt;sink \|\| data_-&gt;wal-&gt;requires_reopen() \|\| data_-… · [reviewed contract](#b0019) |
| [B0020 · 110–114](../../../../../src/recovery/sql_aggregate_session.cpp#L110) | Callable definition: SessionState Session::state() const | calls data, state, sequence, selected; returns {w.logged_sequence,d.progress.sequence,d.native.sequence(),d.sink-&gt;state().prefix.physical_sequence, · [reviewed contract](#b0020) |
| [B0021 · 115–115](../../../../../src/recovery/sql_aggregate_session.cpp#L115) | Callable definition: GenerationRoot Session::selected_root() const | calls data, selected; returns data().root.selected() · [reviewed contract](#b0021) |
| [B0022 · 116–116](../../../../../src/recovery/sql_aggregate_session.cpp#L116) | Callable definition: const Descriptor& Session::descriptor() const & | calls data; returns data().descriptor · [reviewed contract](#b0022) |
| [B0023 · 117–117](../../../../../src/recovery/sql_aggregate_session.cpp#L117) | Callable definition: const io::AccountedInputProgress& Session::progress() const & | calls data; returns data().progress · [reviewed contract](#b0023) |
| [B0024 · 118–118](../../../../../src/recovery/sql_aggregate_session.cpp#L118) | Callable definition: std::optional&lt;ReaderPosition&gt; Session::reader_position() const | calls data; returns data().reader · [reviewed contract](#b0024) |
| [B0025 · 119–121](../../../../../src/recovery/sql_aggregate_session.cpp#L119) | Callable definition: std::optional&lt;ReaderPosition&gt; Session::logged_reader_position() const | calls data, view; returns d.head-&gt;input.view().reader; d.reader · [reviewed contract](#b0025) |
| [B0026 · 122–122](../../../../../src/recovery/sql_aggregate_session.cpp#L122) | Callable definition: std::optional&lt;InputView&gt; Session::pending_input() const & | calls data, view; returns d.head?std::optional{d.head-&gt;input.view()}:std::nullopt · [reviewed contract](#b0026) |
| [B0027 · 123–123](../../../../../src/recovery/sql_aggregate_session.cpp#L123) | Callable definition: std::optional&lt;std::string_view&gt; Session::output() const & | calls data, bytes; returns d.spool?std::optional{d.spool-&gt;bytes()}:std::nullopt · [reviewed contract](#b0027) |
| [B0028 · 124–124](../../../../../src/recovery/sql_aggregate_session.cpp#L124) | Callable definition: ReplayStatistics Session::replay_statistics() const | calls data; returns data().replayed · [reviewed contract](#b0028) |
| [B0029 · 125–125](../../../../../src/recovery/sql_aggregate_session.cpp#L125) | Callable definition: runtime::sql_aggregate::Snapshot Session::snapshot(runtime::aggregate::SnapshotLimits limits) const | calls data, snapshot; returns data().native.snapshot(limits) · [reviewed contract](#b0029) |
| [B0030 · 126–126](../../../../../src/recovery/sql_aggregate_session.cpp#L126) | Callable definition: std::uint64_t Session::source_weight(TableId table,std::span&lt;const runtime::sql_rows::Cell&gt; row) const | calls data, source_weight; returns data().native.source_weight(table,row) · [reviewed contract](#b0030) |
| [B0031 · 127–127](../../../../../src/recovery/sql_aggregate_session.cpp#L127) | Explanatory comments or spacing. |  |
| [B0032 · 128–136](../../../../../src/recovery/sql_aggregate_session.cpp#L128) | Callable definition: void Session::log(const InputView& input) & | calls data, state, sequence, require; guard require(!d.head && !d.spool && state.logged_sequence==d.progress.sequence && state.command_sequence…; growth emplace · [reviewed contract](#b0032) |
| [B0033 · 137–153](../../../../../src/recovery/sql_aggregate_session.cpp#L137) | Callable definition: Decision Session::decide() & | calls data, require, state, frame; guard auto& d=data();require(d.head && !d.spool);const auto state=d.wal-&gt;state().wal;; returns {command,d.native.sequence(),prepared.rejected} · [reviewed contract](#b0033) |
| [B0034 · 154–162](../../../../../src/recovery/sql_aggregate_session.cpp#L154) | Callable definition: bool Session::deliver() & | calls data, append, receipt, require; guard require(receipt.prefix().physical_sequence==d.native.sequence(),SessionFault::binding);; returns false; true; source comment (unverified): // The external effect is confirmed. An unexpected private postcondition · [reviewed contract](#b0034) |
| [B0035 · 163–163](../../../../../src/recovery/sql_aggregate_session.cpp#L163) | Explanatory comments or spacing. |  |
| [B0036 · 164–177](../../../../../src/recovery/sql_aggregate_session.cpp#L164) | Callable definition: Session Session::create_into(const resource::MemoryAccount& account,SessionPaths paths,SessionIdentity identity, frontend::SqlAgg… | calls require, binary_detail::hex, admit_into, std::move; guard require(limits.history_generations&gt;0,SessionFault::limit);; returns Session(std::move(owner)); growth emplace, make_accounted_unique · [reviewed contract](#b0036) |
| [B0037 · 178–213](../../../../../src/recovery/sql_aggregate_session.cpp#L178) | Callable definition: GenerationRoot Session::select_checkpoint(Data& d,bool initial) | calls require, ready, sequence, receipt; guard require(!d.head && !d.spool && d.native.ready());const auto c=d.native.sequence();; returns next; growth emplace; source comment (unverified): // Failure while validating the selected root invalidates this owner. · [reviewed contract](#b0037) |
| [B0038 · 214–214](../../../../../src/recovery/sql_aggregate_session.cpp#L214) | Callable definition: GenerationRoot Session::checkpoint() & | calls select_checkpoint, data; returns select_checkpoint(data(),false) · [reviewed contract](#b0038) |
| [B0039 · 215–215](../../../../../src/recovery/sql_aggregate_session.cpp#L215) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_aggregate · [reviewed contract](#b0039) |

## B0001

[Lines 1–9](../../../../../src/recovery/sql_aggregate_session.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "sql_aggregate_session_detail.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile the session coordinator against its private owner, bounded binary codec, native error type, and fixed digest primitives. |
| inputs / outputs | Implementation translation unit in; definitions for Session and session_detail out. |
| invariants | The coordinator reuses lower owners/codecs and does not introduce a second WAL, sink, digest, or native runtime implementation. |
| ownership | Includes and namespace declarations create no runtime ownership. |
| failure | Missing/incompatible dependencies fail at compile time; this region has no runtime catch or fallback. |
| cost | Compile-time only. |
| Design | [src/recovery/sql_aggregate_session_detail.hpp](../../../../../src/recovery/sql_aggregate_session_detail.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/ir/digest.hpp](../../../../../include/crown/ir/digest.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0002

[Lines 10–10](../../../../../src/recovery/sql_aggregate_session.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool condition,SessionFault fault)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a false coordinator invariant into the fixed typed SessionFailure category supplied by the caller. |
| inputs / outputs | Boolean condition and SessionFault in; normal return if true or SessionFailure(fault) if false. |
| invariants | The helper does no formatting and never maps a condition to a semantic RejectReason or lower-layer error category. |
| ownership | Consumes only scalar arguments; the exception stores the enum. |
| failure | A false condition throws; construction uses the fixed noexcept SessionFailure carrier. |
| cost | One branch and, on failure, fixed exception-object construction; no dynamic diagnostic formatting. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md) |

## B0003

[Lines 11–19](../../../../../src/recovery/sql_aggregate_session.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<RejectReason> semantic(std::string_view code) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate only the six named deterministic source/constraint/arithmetic errors into stable R2 Reject reasons. |
| inputs / outputs | Borrowed native Error code in; one of weight_mismatch, source_overflow, unique_violation, foreign_key_violation, aggregate_overflow, annotation_overflow, or empty out. |
| invariants | The mapping is an exact semantic allowlist. Memory/work/contract/underflow/internal-sequence failures and unlisted overflow names remain exceptions; no prefix or suffix rule broadens the set. |
| ownership | Borrows the error-code string_view and returns a fixed optional enum; it retains or allocates no message. |
| failure | Declared noexcept and has no fallback conversion. Adding a code requires proving that the native prepare rolled back and that recovery can reproduce the same deterministic decision. |
| cost | At most six short string comparisons; called only while translating a native preparation Error. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [build/verification/w06-r2-protocol-review-v1/protocol.md](../../../../../build/verification/w06-r2-protocol-review-v1/protocol.md), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md) |

## B0004

[Lines 20–22](../../../../../src/recovery/sql_aggregate_session.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GenerationDeliveryAnchor anchor(const SinkReceipt& receipt)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project the delivery identity from a receipt minted by the actual healthy R2 sink owner. |
| inputs / outputs | Borrowed SinkReceipt in; fixed sink ID, physical sequence, byte extent, and prefix fingerprint out. |
| invariants | The receipt is the authority for the copied fields; this helper does not accept an editable SinkPrefix or recompute/upgrade a digest into delivery proof. |
| ownership | Reads the receipt by reference and returns a fixed GenerationDeliveryAnchor value. |
| failure | No allocation or translation occurs; invalidity is rejected when the actual sink/receipt or root/checkpoint codec is validated. |
| cost | Fixed field copies. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md) |

## B0005

[Lines 23–24](../../../../../src/recovery/sql_aggregate_session.cpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using session_detail::require;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make the private typed invariant helper available to this implementation's coordinator methods. |
| inputs / outputs | Existing session_detail::require declaration in; one local namespace using-declaration out. |
| invariants | The using-declaration aliases the same helper; it does not define a second validation policy or alter SessionFault defaults. |
| ownership | No runtime state or object is created. |
| failure | Compile-time name lookup failure only. |
| cost | Compile-time only. |
| Design | [src/recovery/sql_aggregate_session_detail.hpp](../../../../../src/recovery/sql_aggregate_session_detail.hpp) |

## B0006

[Lines 25–31](../../../../../src/recovery/sql_aggregate_session.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Session::Data::Data(const resource::MemoryAccount& memory,const SessionLimits& requested,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize Data by retaining the receiver account and moving in the already admitted root, descriptor, runtime, and progress. |
| inputs / outputs | Receiving MemoryAccount, a synchronous borrowed SessionLimits reference, already owned generation/descriptor/runtime/progress and optional reader initialize Data. |
| invariants | C++ member declaration order remains the destruction policy: Head/spool and sink/WAL close before native/root teardown, with account last. This constructor does not create WAL/sink files or certify root selection. |
| ownership | Copies the account handle and the seven fixed checkpoint/capture/WAL/sink/history/replay groups memberwise; moves actual root/native/progress owners and copies reader scalars. No reference to requested or owning host binder payload is retained. |
| failure | Member construction failures propagate and already constructed members unwind in reverse declaration order. |
| cost | Fixed numeric/limit-group copies and existing owner moves only; no whole SessionLimits copy or extra database. LiveLimits is checked trivially copyable and its fields contain no host parameter vectors. |
| Design | [src/recovery/sql_aggregate_session_detail.hpp](../../../../../src/recovery/sql_aggregate_session_detail.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0007

[Lines 32–35](../../../../../src/recovery/sql_aggregate_session.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Session::Data::ready() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail closed before ordinary Session access when an owner, file, native runtime, or root is not ready. |
| inputs / outputs | Current Data state in; normal return only when unpoisoned, WAL/sink exist and are healthy, native runtime is ready, and root selection exists. |
| invariants | This is an O(1) readiness check over actual owners; it does not scan files or independently prove W/I/C/D equality. |
| ownership | Reads owner state without transferring or retaining members. |
| failure | Any failed predicate raises SessionFailure(state). |
| cost | Fixed boolean/owner-state checks with no allocation or file scan. |
| Design | [src/recovery/sql_aggregate_session_detail.hpp](../../../../../src/recovery/sql_aggregate_session_detail.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/generations.md](../../../../generations.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0008

[Lines 36–53](../../../../../src/recovery/sql_aggregate_session.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Session::Data::Head Session::Data::own(DecodedInput input)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate next-command/source/reader progress and fund its unpublished progress node while taking ownership of one input. |
| inputs / outputs | Owned DecodedInput whose command sequence should be I+1 in; Head with the same input and prepared source-position candidate out. |
| invariants | Source names/counts and offsets obey checkpoint limits and strict per-source monotonicity; reader records advance by one, do not exceed command sequence, and reader bytes increase. These checks do not publish I or any source/reader position. |
| ownership | Moves the complete DecodedInput into Head. InputPositions::Prepared is tied to this progress map; its unpublished node is released if Head construction fails. |
| failure | Progress/limit violations reject before WAL append. No catch converts them to Reject and no progress is visible until publish. |
| cost | One source-position lookup/preparation when present, fixed reader checks, and a move of already encoded/decoded input storage. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [build/verification/w06-r2-protocol-review-v1/actual-apis.md](../../../../../build/verification/w06-r2-protocol-review-v1/actual-apis.md) |

## B0009

[Lines 54–64](../../../../../src/recovery/sql_aggregate_session.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Session::Data::Prepared Session::Data::prepare()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the next physical epoch through the real atomic native token and recognize only allowlisted semantic rejection. |
| inputs / outputs | The one owned Head with command I+1 and current native epoch C in; active PreparedBatch preview authority or one RejectReason out. |
| invariants | The runtime batch uses C+1 for its physical sequence; Input command sequence is independent and can diverge after Reject. The native token owns all preparation rollback and remains private until the durable decision is appended. |
| ownership | Returned Prepared owns the actual move-only token. On an exception, native preparation RAII unwinds; the logged Head remains in Data. |
| failure | Only crown::api::Error with an exact code accepted by session_detail::semantic becomes Reject. All resource, work, contract, and other errors propagate with C/I/source progress unpublished. |
| cost | The original native/source/group grants and their actual batch work apply. This wrapper adds one token handoff and one short error-code lookup; it does not refill or replace native options. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [build/verification/w06-r2-protocol-review-v1/actual-apis.md](../../../../../build/verification/w06-r2-protocol-review-v1/actual-apis.md), [Refactor.md §11.9 W06](../../../../../Refactor.md) |

## B0010

[Lines 65–69](../../../../../src/recovery/sql_aggregate_session.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Limits Session::Data::codec_limits(bool output) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Give one replay Input decode or group-epoch encode the lesser of its file-record cap and remaining cumulative session codec budget. |
| inputs / outputs | Input/output selector and current replayed.codec_work in; copied Limits with record.work clipped to the remaining replay_codec_work. |
| invariants | Output selects sink frame limits; input selects WAL frame limits. The cumulative counter is never reset here. WAL's full file scan continues to use WalFile limits and is not charged as session codec_work. |
| ownership | Returns a copied Limits value and borrows Data's immutable configuration/counter. |
| failure | If accumulated work already exceeds the limit, throws SessionFailure(limit) before codec work starts. |
| cost | Fixed limit copy, comparison, and min operation. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md) |

## B0011

[Lines 70–73](../../../../../src/recovery/sql_aggregate_session.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Session::Data::charge_codec(std::uint64_t amount)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit one reported codec-work amount to the cumulative session replay counter with overflow-safe admission. |
| inputs / outputs | Nonnegative uint64 codec amount and current replayed.codec_work in; counter advanced by amount on success. |
| invariants | Check remaining capacity by subtraction before addition; failed admission leaves the counter unchanged. The unit is the codec's declared logical work, not CPU time. |
| ownership | Updates one scalar in Data; no work token or refillable shadow allowance is created. |
| failure | An amount exceeding replay_codec_work or arithmetic headroom throws SessionFailure(limit). |
| cost | Two bounded comparisons/subtraction checks and one scalar addition. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md) |

## B0012

[Lines 74–82](../../../../../src/recovery/sql_aggregate_session.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Frame Session::Data::epoch(const runtime::sql_aggregate::Epoch& output,bool replaying)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the full canonical group-value epoch bound to the selected generation, input command, physical C, and Input body identity. |
| inputs / outputs | Captured native Epoch and its current Head in; one owned encoded Frame containing changed/full-key group output out. |
| invariants | An uncaptured native preview is a transition error. Normal decision preparation uses the sink per-frame codec limit; replay additionally uses and charges the cumulative replay codec budget. Empty successful output still encodes a whole closing epoch. |
| ownership | The returned Frame owns its account-funded bytes; the Head and Epoch are borrowed only while encoding. |
| failure | Codec, work, output-cap, or allocation failure occurs before Commit append; the local PreparedBatch then rolls back and the logged Head remains pending. |
| cost | Codec work is linear in encoded data plus canonical complete-key ordering/comparisons; temporary key/index scratch and the retained Frame are bounded by codec/account limits. No CPU-time bound is implied. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md) |

## B0013

[Lines 83–92](../../../../../src/recovery/sql_aggregate_session.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Session::Data::publish(Prepared& prepared,std::optional<Frame> output)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish exactly the already durable Commit or Reject without constructing another rollback journal. |
| inputs / outputs | Private Prepared token/rejection, the Head's prepaid progress, and optional prebuilt output Frame in; native C when committed, I/source/reader progress, and optional spool updated by move/scalar operations. |
| invariants | The poison latch is set before native publication and cleared only after the token, prepared positions, progress, spool, and Head have been reconciled. Commit advances C and I; Reject advances I/source progress only. No new allocation is allowed after durable disposition. |
| ownership | The token is committed in place; Prepared position is published into its original progress map; the Frame moves into the sole spool and Head releases its input. |
| failure | An invalid private-token publication leaves poisoned set so normal accessors require recovery. Preparation/encoding failures occur earlier and do not call this block. |
| cost | Nonallocating publication reuses the actual native token. Native commit and staged undo/output/head teardown can scale with prepared entries. A new source name links its prepaid node through ordered-map comparisons (O(log S) comparisons with source-key byte costs); updating an existing offset is fixed. Scalar frontiers and owner moves are fixed; no full database clone or new undo journal is added. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [build/verification/w06-r2-protocol-review-v1/protocol.md](../../../../../build/verification/w06-r2-protocol-review-v1/protocol.md) |

## B0014

[Lines 93–101](../../../../../src/recovery/sql_aggregate_session.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Session::Data::observe(const runtime::sql_aggregate::Epoch& output)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate replay diagnostics for successful committed native epochs with checked fixed-width counters. |
| inputs / outputs | One native Epoch's work metrics in; cumulative replay native/group/source work counters updated in place. |
| invariants | Counter overflow is a replay limit failure. These totals report successful replay work; native_work, group_work, and source_work do not preempt or cap runtime work and do not alter the original operational options. |
| ownership | Reads borrowed fixed metric records and owns only scalar totals. |
| failure | Overflow throws SessionFailure(limit) before the replayed token is published; recovery does not expose partial statistics or state. |
| cost | A fixed number of checked additions per committed replay epoch, independent of source row count. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [build/verification/w06-r2-protocol-review-v1/actual-apis.md](../../../../../build/verification/w06-r2-protocol-review-v1/actual-apis.md) |

## B0016

[Lines 103–103](../../../../../src/recovery/sql_aggregate_session.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Session::Session(resource::AccountedUnique<Data> value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the one already funded private Data owner as the public Session handle. |
| inputs / outputs | Move-only AccountedUnique&lt;Data&gt; in; Session containing that owner out. |
| invariants | This constructor does not duplicate the account, native runtime, or file locks; readiness is checked by later access through data(). |
| ownership | Moves the AccountedUnique handle and its receiving-account lifetime into Session. |
| failure | Declared noexcept; no new allocation or validation exception is introduced here. |
| cost | One noexcept owner-handle move. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [src/recovery/sql_aggregate_session_detail.hpp](../../../../../src/recovery/sql_aggregate_session_detail.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 104–105](../../../../../src/recovery/sql_aggregate_session.cpp#L104); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Session::~Session()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use default destruction to release the complete owner through Data's declared reverse-member order. |
| inputs / outputs | Session destruction in; its AccountedUnique&lt;Data&gt; and owned members are destroyed out. |
| invariants | Data tears down Head/spool and sink/WAL before native/root, and retains the account through every member destructor. |
| ownership | The destructor relies on Data order to close Head/spool and file owners before native/root, retaining the account through teardown. |
| failure | The default destructor adds no translation/catch layer; lower owner destructors retain their own rules. |
| cost | Teardown follows the live member count and actual deallocation work; it is not a recovery scan. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [src/recovery/sql_aggregate_session_detail.hpp](../../../../../src/recovery/sql_aggregate_session_detail.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

```text
Session::Session(Session&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer the unique AccountedUnique&lt;Data&gt; handle from one Session into another without duplicating authority. |
| inputs / outputs | Move-constructible Session source in; destination owns the former source Data and file/root locks. |
| invariants | The source becomes empty and reports requires_reopen; the move is noexcept and does not create another runtime, reader, or file lock. Move assignment remains deleted. |
| ownership | The receiving Session becomes the sole AccountedUnique&lt;Data&gt; owner; existing borrows remain tied to that Data's lifetime, not to a copied Session. |
| failure | No throwing validation or allocation is performed by the defaulted move constructor. |
| cost | One noexcept owner-handle transfer. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [src/recovery/sql_aggregate_session_detail.hpp](../../../../../src/recovery/sql_aggregate_session_detail.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0018

[Lines 106–106](../../../../../src/recovery/sql_aggregate_session.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Session::Data& Session::data() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the private mutable owner only after checking that this Session handle exists and is ready. |
| inputs / outputs | Session handle in; borrowed Data reference out. |
| invariants | A moved-from/empty handle fails the first check; a present handle passes through Data::ready before any normal accessor/mutator uses it. |
| ownership | Returned reference is owned by AccountedUnique&lt;Data&gt; and is valid only while this Session retains that Data. |
| failure | Empty or unready owner raises the fixed SessionFailure category from require/ready. |
| cost | One owner-null check and the O(1) Data::ready predicate. |
| Design | [src/recovery/sql_aggregate_session_detail.hpp](../../../../../src/recovery/sql_aggregate_session_detail.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0019

[Lines 107–109](../../../../../src/recovery/sql_aggregate_session.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool Session::requires_reopen() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report whether this handle is empty, poisoned, missing an actual file owner, or backed by a WAL/sink owner that requires reopen. |
| inputs / outputs | Any Session handle in; noexcept boolean out. |
| invariants | This is a member-health predicate, not a cross-frontier validator or a root reread. Binding mismatches detected by callers must latch poison before relying on this result. |
| ownership | Reads the current unique Data and actual file owners; retains nothing. |
| failure | Never throws. A moved-from handle reports true. |
| cost | Fixed pointer/boolean checks; no file I/O or allocation. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0020

[Lines 110–114](../../../../../src/recovery/sql_aggregate_session.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionState Session::state() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read W/I/C/D and pending-owner flags from the current WAL, progress, native runtime, sink, and root. |
| inputs / outputs | Ready Session in; fixed SessionState value out. |
| invariants | logged comes from WalState.logged_sequence (W command sequence); disposed from progress.sequence (I); committed from native.sequence (C); delivered from actual SinkFile prefix (D). The method reports observed frontiers and does not repair or reconcile them. |
| ownership | The result owns scalars only; underlying owners are borrowed through the call. |
| failure | Requires Data::ready; typed owner/readiness failure propagates rather than being converted to a partial status. |
| cost | Fixed cached-state reads and value construction; no WAL/sink scan. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [build/verification/w06-r2-protocol-review-v1/protocol.md](../../../../../build/verification/w06-r2-protocol-review-v1/protocol.md) |

## B0021

[Lines 115–115](../../../../../src/recovery/sql_aggregate_session.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GenerationRoot Session::selected_root() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a value copy of the GenerationRoot currently held under the real root lock. |
| inputs / outputs | Ready Session in; fixed GenerationRoot metadata copy out. |
| invariants | The returned metadata is descriptive and editable by the caller; it is not the lock-owning GenerationOwner and cannot authorize file selection or retirement. |
| ownership | Copies root metadata; actual root and directory-lock ownership remain in Data. |
| failure | Readiness failure propagates; this accessor does not reread or independently validate the on-disk root. |
| cost | Fixed-size metadata/optional-field copy. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/generations.md](../../../../generations.md), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp) |

## B0022

[Lines 116–116](../../../../../src/recovery/sql_aggregate_session.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Descriptor& Session::descriptor() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the admitted immutable SQL/native descriptor by reference from a live lvalue Session. |
| inputs / outputs | Ready lvalue Session in; const Descriptor reference out. |
| invariants | The descriptor is the actual admitted binding used by the runtime and files, not an editable DTO. The rvalue overload is deleted so callers cannot retain a reference from a temporary. |
| ownership | Reference borrows Data::descriptor and expires with the owning Session. |
| failure | Readiness failure propagates; no descriptor copy or rebinding occurs here. |
| cost | One borrowed-reference return. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [docs/sql_aggregate_descriptor.md](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0023

[Lines 117–117](../../../../../src/recovery/sql_aggregate_session.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const io::AccountedInputProgress& Session::progress() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a const borrowed view of the account-owned I/source-position progress. |
| inputs / outputs | Ready lvalue Session in; const AccountedInputProgress reference out. |
| invariants | The returned progress.sequence is I and does not include a pending Head's unpublished source position. Rvalue access is deleted; callers cannot publish or edit through this const reference. |
| ownership | Reference borrows Data::progress under the Session/account lifetime. |
| failure | Readiness failure propagates; no progress export copy or file replay occurs. |
| cost | One borrowed-reference return. |
| Design | [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [src/io/input_progress.cpp](../../../../../src/io/input_progress.cpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [build/verification/w06-r2-protocol-review-v1/actual-apis.md](../../../../../build/verification/w06-r2-protocol-review-v1/actual-apis.md) |

## B0024

[Lines 118–118](../../../../../src/recovery/sql_aggregate_session.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<ReaderPosition> Session::reader_position() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the last durably disposed reader continuation position. |
| inputs / outputs | Ready Session in; optional ReaderPosition copy from committed Data::reader out. |
| invariants | A pending logged Input's reader position is not reported here; use logged_reader_position when the logged continuation is needed. |
| ownership | Returns a value copy and retains no pointer into Session. |
| failure | Readiness failure propagates; absent committed reader state returns empty. |
| cost | Fixed optional/value copy. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md) |

## B0025

[Lines 119–121](../../../../../src/recovery/sql_aggregate_session.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<ReaderPosition> Session::logged_reader_position() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the reader continuation associated with the logged head when one exists, otherwise the committed position. |
| inputs / outputs | Ready Session in; optional ReaderPosition value out. |
| invariants | A pending Head's reader can be ahead of I because it belongs to W=I+1; the committed reader remains unchanged until Commit/Reject publication. |
| ownership | Copies the small ReaderPosition value from the Head's owned frame view or committed Data field. |
| failure | Readiness or input-view failure propagates; no source position is published by observation. |
| cost | One optional/head check and fixed value copy. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md), [build/verification/w06-r2-protocol-review-v1/protocol.md](../../../../../build/verification/w06-r2-protocol-review-v1/protocol.md) |

## B0026

[Lines 122–122](../../../../../src/recovery/sql_aggregate_session.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<InputView> Session::pending_input() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a borrowed read-only view of the sole logged Head for inspection or same-head retry. |
| inputs / outputs | Ready lvalue Session in; optional InputView borrowing the owned DecodedInput, or empty if no Head. |
| invariants | The view does not own input rows and does not authorize another log append. It stays valid only while the same Head remains in Data; the rvalue overload is deleted. |
| ownership | Session::Data::Head owns the frame and flat row storage; returned view borrows it. |
| failure | Readiness/input-view failure propagates. A missing Head returns empty. |
| cost | One optional/value view construction with no row copy. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md) |

## B0027

[Lines 123–123](../../../../../src/recovery/sql_aggregate_session.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::string_view> Session::output() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the bytes of the sole canonical committed output spool without copying it. |
| inputs / outputs | Ready lvalue Session in; optional string_view over the retained Frame bytes, or empty if no spool. |
| invariants | The view is not a sink receipt and does not advance D. It remains valid only while the same spool Frame stays owned; the rvalue overload is deleted. |
| ownership | Frame in Data owns bytes; returned string_view borrows them. |
| failure | Readiness failure propagates. No spool returns empty. |
| cost | One optional view construction; no frame copy or re-encoding. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md) |

## B0028

[Lines 124–124](../../../../../src/recovery/sql_aggregate_session.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReplayStatistics Session::replay_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a value snapshot of cumulative counters accumulated by this recovery/replay owner. |
| inputs / outputs | Ready Session in; fixed ReplayStatistics copy out. |
| invariants | The copy is descriptive only; native/group/source totals are observations, not an allowance to spend or a preemptive budget. |
| ownership | Returns scalar counters and IndexWork by value; no runtime handle is retained. |
| failure | Readiness failure propagates; no additional scan or measurement is performed. |
| cost | Fixed-size copy. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md) |

## B0029

[Lines 125–125](../../../../../src/recovery/sql_aggregate_session.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
runtime::sql_aggregate::Snapshot Session::snapshot(runtime::aggregate::SnapshotLimits limits) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate snapshot capture to the committed genuine SqlAggregateRuntime. |
| inputs / outputs | Ready Session and native SnapshotLimits in; runtime Snapshot at current C out. |
| invariants | The snapshot reflects committed native state only; a logged Head or undelivered output spool does not publish additional native state. This is not a durable checkpoint/root rotation. |
| ownership | The returned Snapshot follows the runtime snapshot's account/ownership contract; Session retains its own runtime and root/file owners. |
| failure | Native snapshot validation, resource, or work failures propagate in their existing carriers. |
| cost | Exactly the native snapshot traversal/copy cost for the selected limits; this wrapper adds only readiness and delegation. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md) |

## B0030

[Lines 126–126](../../../../../src/recovery/sql_aggregate_session.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t Session::source_weight(TableId table,std::span<const runtime::sql_rows::Cell> row) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Query the actual runtime source weight, including zero for an absent complete physical row. |
| inputs / outputs | Ready Session, TableId, and borrowed row Cell span in; uint64 source weight out. |
| invariants | This delegates to genuine source state and does not modify a table, create a NetBatch, or publish an epoch. |
| ownership | The row span is borrowed for the call; returned weight is a scalar. |
| failure | Native table/row lookup and readiness failures propagate without session-level error remapping. |
| cost | The underlying source-index lookup cost; the wrapper adds no row copy or account allocation. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [build/verification/w06-r2-protocol-review-v1/actual-apis.md](../../../../../build/verification/w06-r2-protocol-review-v1/actual-apis.md) |

## B0032

[Lines 128–136](../../../../../src/recovery/sql_aggregate_session.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Session::log(const InputView& input) &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepay and own one physical Input, then establish W only after the actual WAL owner confirms its append. |
| inputs / outputs | Next InputView with command sequence I+1 in; one complete account-owned Head after successful WAL append. |
| invariants | Admit only when no Head/spool exists, W=I, WAL C matches runtime C, and actual sink D=C. encode_input receives WAL records as the frame ordinal; input.command_sequence is W and must not be conflated with that ordinal. Input ownership and source-position preparation precede file mutation; Head installation after append is statically required to be nothrow. |
| ownership | The local Head owns the encoded/decoded frame and prepared source progress until WAL append succeeds, then moves into Data. WalFile owns and locks the actual durable log. |
| failure | Pre-append validation/encoding/allocation leaves durable state unchanged. A failed/uncertain append poisons WalFile and requires reopen; no native state or source progress is published. |
| cost | One bounded input encode/hash and its account-owned input storage, followed by actual WAL append/fsync/stat work. No native batch preparation happens in this block. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [build/verification/w06-r2-protocol-review-v1/protocol.md](../../../../../build/verification/w06-r2-protocol-review-v1/protocol.md) |

## B0033

[Lines 137–153](../../../../../src/recovery/sql_aggregate_session.cpp#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Decision Session::decide() &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the sole logged Head with one atomic native token and append its durable Commit or semantic Reject before publication. |
| inputs / outputs | Owned pending Head with no spool in; Decision containing the original command sequence, resulting physical C, and optional allowlisted RejectReason out. |
| invariants | Commit output and decision identity/bytes/hash are fully encoded before WAL append; then the same token and prepaid I/source state publish and the spool is installed. Reject emits no sink epoch and advances I only. Successful empty/no-op input is still Commit, advances C, and produces an empty full epoch. W is unchanged by decide. |
| ownership | The native PreparedBatch is the sole private rollback token. The canonical Frame is owned before Commit; Reject has no output Frame. Data::publish runs only after actual WalFile append succeeds. |
| failure | Native resource/work/output preparation failure leaves the same logged Head pending with I/C unchanged. Only the explicit semantic allowlist writes Reject. Uncertain decision append requires reopen; poison protects post-append token publication. |
| cost | Original native/source/group preparation costs apply. Commit additionally encodes and hashes the canonical whole group frame; either disposition encodes/syncs one WAL decision. Post-sync token/map publication and teardown allocate no new C++ storage but can scale with prepared work and source-map comparisons. No CPU/preemptive replay budget is promised. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md) |

## B0034

[Lines 154–162](../../../../../src/recovery/sql_aggregate_session.cpp#L154); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool Session::deliver() &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deliver the sole committed epoch through the actual locked R2 SinkFile and release its spool only after a matching actual receipt. |
| inputs / outputs | Ready Session with zero or one canonical Frame spool in; false if absent, otherwise true after the sink prefix confirms the native physical C. |
| invariants | D is the actual SinkFile prefix, not a caller assertion. Sink append verifies full bytes for duplicates or syncs/checks a new epoch; only then may the spool be released. A failed sink append leaves the spool and the file owner requires reopen. |
| ownership | The spool remains owned by Data through append/receipt and is reset only after receipt binding succeeds; SinkFile owns the actual sink FD, index, and lock. |
| failure | If append itself fails, SinkFile retains its own reopen/uncertainty state and the spool remains. After append succeeds, Data::poisoned is set before receipt read and sequence validation; any unexpected postcondition failure remains fail-stop. The latch clears only after the spool is reset. |
| cost | One sink validation and actual file append/fsync/stat or bounded full-byte duplicate comparison; spool bytes are reused without another output queue. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [build/verification/w06-r2-protocol-review-v1/protocol.md](../../../../../build/verification/w06-r2-protocol-review-v1/protocol.md), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md) |

## B0036

[Lines 164–177](../../../../../src/recovery/sql_aggregate_session.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Session Session::create_into(const resource::MemoryAccount& account,SessionPaths paths,SessionIdentity identity,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a session from the genuine SQL program/tree/options, actual generation root, and actual sink, then publish its initial checkpoint selection. |
| inputs / outputs | Receiving account, borrowed path/configuration views, fixed identities, genuine program/tree/physical/normal options enter; one owning Session returns only after initial selection. |
| invariants | The factory validates IDs and nonzero generation history, calls the real admission path, rejects a selected R1 retirement intent, creates the real SinkFile, and selects generation 1. capture_changes must be explicitly enabled; runtime Options are passed through the admission path without a per-session grant refill or substitute replay policy. |
| ownership | The returned AccountedUnique&lt;Data&gt; retains the receiving account, genuine runtime/descriptor, root lock, sink lock, and progress state. Input path string_views are consumed synchronously and are not retained as authority. The const SessionLimits& lives only through the call; Data keeps its fixed live projection and the lower owners keep their established fixed limits. |
| failure | Admission/root/sink/checkpoint errors unwind the local owners. Failed initial creation can leave its newly created sink or unselected generation candidates; it never returns a partial Session. A root publication uncertainty is represented by the GenerationOwner selection latch. |
| cost | Cold SQL/native admission plus full initial source snapshot/checkpoint encoding, plan/checkpoint/WAL publication, validation, and sync work. This is not ordinary update cost. Populated unused host binder payloads cause no Session-level copies; the new-attempt differential regression compares against the empty-host factory. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_descriptor.md](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/generations.md](../../../../generations.md), [build/verification/w06-r2-protocol-review-v1/actual-apis.md](../../../../../build/verification/w06-r2-protocol-review-v1/actual-apis.md) |

## B0037

[Lines 178–213](../../../../../src/recovery/sql_aggregate_session.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GenerationRoot Session::select_checkpoint(Data& d,bool initial)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rotate the selected R2 checkpoint/WAL pair only from a quiescent, fully delivered native frontier. |
| inputs / outputs | Ready Data and initial/rotation mode in; next GenerationRoot after durable publication. |
| invariants | No Head or spool may exist; actual sink receipt D must equal native C. Rotation also requires W=I, WAL physical C agreement, and generation/history bounds. Checkpoint metadata binds C, I, descriptor hash, and the actual receipt anchor. Existing root owner prepares the plan, checkpoint, matching WAL, validates files, then publishes the root as the single selection boundary. |
| ownership | The actual GenerationOwner/root lock and candidate identities remain in Data. The receipt is minted by the actual SinkFile; no editable delivery DTO or forged R1 Receipt authorizes selection. |
| failure | Failures before root selection leave old selection authoritative; root publication uncertainty poisons Data when selection was attempted. Unselected next candidates may be retried under GenerationOwner rules. This block does not retire old history. |
| cost | Full physical source snapshot and checkpoint encoding, descriptor/checkpoint/WAL file writes and validation, root sync. Cost scales with saved image and configured file work, not with one update. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/generations.md](../../../../generations.md), [build/verification/w06-r2-protocol-review-v1/protocol.md](../../../../../build/verification/w06-r2-protocol-review-v1/protocol.md), [Refactor.md §11.7 O05](../../../../../Refactor.md) |

## B0038

[Lines 214–214](../../../../../src/recovery/sql_aggregate_session.cpp#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
GenerationRoot Session::checkpoint() &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the private checkpoint rotation protocol on a ready lvalue Session. |
| inputs / outputs | Ready lvalue Session in; newly selected GenerationRoot value out. |
| invariants | All quiescence, W=I,D=C, anchor, history, file-candidate, and root-selection checks are in select_checkpoint; this wrapper does not bypass them. |
| ownership | The returned root is metadata only; actual root/WAL ownership remains in Data. |
| failure | Readiness, snapshot/codec, generation, file, or root-selection failures propagate with the underlying retry/reopen/poison rules. |
| cost | Delegates the full source snapshot, checkpoint, plan/WAL publication, file validation, and root sync cost; not a constant-time update. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md), [docs/generations.md](../../../../generations.md), [Refactor.md §11.7 O05](../../../../../Refactor.md) |

## B0039

[Lines 215–215](../../../../../src/recovery/sql_aggregate_session.cpp#L215); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
} // namespace crown::recovery::sql_aggregate
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the implementation namespace after all coordinator definitions. |
| inputs / outputs | Open namespace scope in; translation-unit scope closed out. |
| invariants | This delimiter adds no function, state, error policy, or runtime behavior. |
| ownership | No object ownership. |
| failure | Malformed scope is a compile-time error only. |
| cost | Compile-time syntax only. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp) |
