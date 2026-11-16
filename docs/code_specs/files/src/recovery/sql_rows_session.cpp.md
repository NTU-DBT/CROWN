# `src/recovery/sql_rows_session.cpp` — block usage map

[Source](../../../../../src/recovery/sql_rows_session.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `0df01044458825c98b04f53b99565ea8d0e807c6dc08365b9dab80868f331456`. 210 lines partitioned into 40 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/recovery/sql_rows_session.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–10](../../../../../src/recovery/sql_rows_session.cpp#L10) | Callable definition: void require(bool condition,SessionFault fault) | calls SessionFailure; guard void require(bool condition,SessionFault fault) { if(!condition)throw SessionFailure(fault); } · [reviewed contract](#b0002) |
| [B0003 · 11–18](../../../../../src/recovery/sql_rows_session.cpp#L11) | Callable definition: std::optional&lt;RejectReason&gt; semantic(std::string_view code) noexcept | calls ; returns RejectReason::weight_mismatch; RejectReason::source_overflow; source comment (unverified): // Work/memory/contract/underflow errors never become semantic Reject. · [reviewed contract](#b0003) |
| [B0004 · 19–21](../../../../../src/recovery/sql_rows_session.cpp#L19) | Callable definition: GenerationDeliveryAnchor anchor(const SinkReceipt& receipt) | calls prefix, header; returns {receipt.header().sink_id,prefix.physical_sequence,prefix.bytes,prefix.content_sha256} · [reviewed contract](#b0004) |
| [B0005 · 22–23](../../../../../src/recovery/sql_rows_session.cpp#L22) | declares aliases. | source comment (unverified): // namespace session_detail · [reviewed contract](#b0005) |
| [B0006 · 24–30](../../../../../src/recovery/sql_rows_session.cpp#L24) | Callable definition: Session::Data::Data(const resource::MemoryAccount& memory,const SessionLimits& requested, ::crown::recovery::detail::GenerationOw… | calls account, root, std::move, descriptor · [reviewed contract](#b0006) |
| [B0007 · 31–34](../../../../../src/recovery/sql_rows_session.cpp#L31) | Callable definition: void Session::Data::ready() const | calls require, requires_reopen, ready, has_selection; guard require(!poisoned && wal && sink && !wal-&gt;requires_reopen() && !sink-&gt;requires_reopen()); · [reviewed contract](#b0007) |
| [B0008 · 35–52](../../../../../src/recovery/sql_rows_session.cpp#L35) | Callable definition: Session::Data::Head Session::Data::own(DecodedInput input) | calls view, require, size, find; guard require(progress.sequence&lt;UINT64_MAX && view.command_sequence==progress.sequence+1,SessionFault::pr…; returns {std::move(input),std::move(position)} · [reviewed contract](#b0008) |
| [B0009 · 53–63](../../../../../src/recovery/sql_rows_session.cpp#L53) | Callable definition: Session::Data::Prepared Session::Data::prepare() | calls require, has_value, view, prepare_output_batch; guard require(head.has_value());const auto view=head-&gt;input.view();; returns {native.prepare_output_batch({native.sequence()+1,view.replacements},descriptor.output_limits()),{}…; source comment (unverified): // The genuine source/native token is the only rollback mechanism. · [reviewed contract](#b0009) |
| [B0010 · 64–68](../../../../../src/recovery/sql_rows_session.cpp#L64) | Callable definition: Limits Session::Data::codec_limits(bool output) const | calls require, std::min; guard require(replayed.codec_work&lt;=limits.replay_codec_work,SessionFault::limit);; returns result · [reviewed contract](#b0010) |
| [B0011 · 69–72](../../../../../src/recovery/sql_rows_session.cpp#L69) | Callable definition: void Session::Data::charge_codec(std::uint64_t amount) | calls require; guard require(replayed.codec_work&lt;=limits.replay_codec_work && amount&lt;=limits.replay_codec_work-replayed.… · [reviewed contract](#b0011) |
| [B0012 · 73–81](../../../../../src/recovery/sql_rows_session.cpp#L73) | Callable definition: Frame Session::Data::epoch(const runtime::SqlRowsRuntime::PreparedBatch& output,bool replaying) | calls require, output_size, has_value, view; guard require(head && output.output_size().has_value(),SessionFault::transition);; returns result · [reviewed contract](#b0012) |
| [B0013 · 82–91](../../../../../src/recovery/sql_rows_session.cpp#L82) | Callable definition: void Session::Data::publish(Prepared& prepared,std::optional&lt;Frame&gt; output) | calls view, commit, publish, std::move; source comment (unverified): // All token/output/progress storage was funded before the durable decision. · [reviewed contract](#b0013) |
| [B0014 · 92–101](../../../../../src/recovery/sql_rows_session.cpp#L92) | Callable definition: void Session::Data::observe(const runtime::SqlRowsRuntime::PreparedBatch& output) | calls require, add, native_preview, output_work; guard const auto add=\[\](std::uint64_t& total,std::uint64_t value) {require(value&lt;=UINT64_MAX-total,Sessio… · [reviewed contract](#b0014) |
| [B0015 · 102–102](../../../../../src/recovery/sql_rows_session.cpp#L102) | Explanatory comments or spacing. |  |
| [B0016 · 103–103](../../../../../src/recovery/sql_rows_session.cpp#L103) | Callable definition: Session::Session(resource::AccountedUnique&lt;Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0016) |
| [B0017 · 104–105](../../../../../src/recovery/sql_rows_session.cpp#L104) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0017) |
| [B0018 · 106–106](../../../../../src/recovery/sql_rows_session.cpp#L106) | Callable definition: Session::Data& Session::data() const | calls require, bool, ready; guard Session::Data& Session::data() const { require(bool(data_));data_-&gt;ready();return *data_; }; returns *data_ · [reviewed contract](#b0018) |
| [B0019 · 107–109](../../../../../src/recovery/sql_rows_session.cpp#L107) | Callable definition: bool Session::requires_reopen() const noexcept | calls requires_reopen; returns !data_ \|\| data_-&gt;poisoned \|\| !data_-&gt;wal \|\| !data_-&gt;sink \|\| data_-&gt;wal-&gt;requires_reopen() \|\| data_-… · [reviewed contract](#b0019) |
| [B0020 · 110–114](../../../../../src/recovery/sql_rows_session.cpp#L110) | Callable definition: SessionState Session::state() const | calls data, state, sequence, selected; returns {w.logged_sequence,d.progress.sequence,d.native.sequence(),d.sink-&gt;state().prefix.physical_sequence, · [reviewed contract](#b0020) |
| [B0021 · 115–115](../../../../../src/recovery/sql_rows_session.cpp#L115) | Callable definition: GenerationRoot Session::selected_root() const | calls data, selected; returns data().root.selected() · [reviewed contract](#b0021) |
| [B0022 · 116–116](../../../../../src/recovery/sql_rows_session.cpp#L116) | Callable definition: const Descriptor& Session::descriptor() const & | calls data; returns data().descriptor · [reviewed contract](#b0022) |
| [B0023 · 117–117](../../../../../src/recovery/sql_rows_session.cpp#L117) | Callable definition: const io::AccountedInputProgress& Session::progress() const & | calls data; returns data().progress · [reviewed contract](#b0023) |
| [B0024 · 118–118](../../../../../src/recovery/sql_rows_session.cpp#L118) | Callable definition: std::optional&lt;ReaderPosition&gt; Session::reader_position() const | calls data; returns data().reader · [reviewed contract](#b0024) |
| [B0025 · 119–121](../../../../../src/recovery/sql_rows_session.cpp#L119) | Callable definition: std::optional&lt;ReaderPosition&gt; Session::logged_reader_position() const | calls data, view; returns d.head-&gt;input.view().reader; d.reader · [reviewed contract](#b0025) |
| [B0026 · 122–122](../../../../../src/recovery/sql_rows_session.cpp#L122) | Callable definition: std::optional&lt;InputView&gt; Session::pending_input() const & | calls data, view; returns d.head?std::optional{d.head-&gt;input.view()}:std::nullopt · [reviewed contract](#b0026) |
| [B0027 · 123–123](../../../../../src/recovery/sql_rows_session.cpp#L123) | Callable definition: std::optional&lt;std::string_view&gt; Session::output() const & | calls data, bytes; returns d.spool?std::optional{d.spool-&gt;bytes()}:std::nullopt · [reviewed contract](#b0027) |
| [B0028 · 124–124](../../../../../src/recovery/sql_rows_session.cpp#L124) | Callable definition: ReplayStatistics Session::replay_statistics() const | calls data; returns data().replayed · [reviewed contract](#b0028) |
| [B0029 · 125–125](../../../../../src/recovery/sql_rows_session.cpp#L125) | Callable definition: runtime::SqlRowsRuntime::ResultCursor Session::results(runtime::weighted::CursorOptions options) const | calls data, results; returns data().native.results(options) · [reviewed contract](#b0029) |
| [B0030 · 126–126](../../../../../src/recovery/sql_rows_session.cpp#L126) | Callable definition: runtime::weighted::Multiplicity Session::root_weight() const | calls data, root_weight; returns data().native.root_weight() · [reviewed contract](#b0030) |
| [B0031 · 127–127](../../../../../src/recovery/sql_rows_session.cpp#L127) | Callable definition: std::uint64_t Session::source_weight(TableId table,std::span&lt;const runtime::sql_rows::Cell&gt; row) const | calls data, source_weight; returns data().native.source_weight(table,row) · [reviewed contract](#b0031) |
| [B0032 · 128–128](../../../../../src/recovery/sql_rows_session.cpp#L128) | Explanatory comments or spacing. |  |
| [B0033 · 129–137](../../../../../src/recovery/sql_rows_session.cpp#L129) | Callable definition: void Session::log(const InputView& input) & | calls data, state, sequence, require; guard require(!d.head && !d.spool && state.logged_sequence==d.progress.sequence && state.command_sequence…; growth emplace · [reviewed contract](#b0033) |
| [B0034 · 138–154](../../../../../src/recovery/sql_rows_session.cpp#L138) | Callable definition: Decision Session::decide() & | calls data, require, state, frame; guard auto& d=data();require(d.head && !d.spool);const auto state=d.wal-&gt;state().wal;; returns {command,d.native.sequence(),prepared.rejected} · [reviewed contract](#b0034) |
| [B0035 · 155–163](../../../../../src/recovery/sql_rows_session.cpp#L155) | Callable definition: bool Session::deliver() & | calls data, append, receipt, require; guard require(receipt.prefix().physical_sequence==d.native.sequence(),SessionFault::binding);; returns false; true; source comment (unverified): // The external effect is confirmed. An unexpected private postcondition · [reviewed contract](#b0035) |
| [B0036 · 164–164](../../../../../src/recovery/sql_rows_session.cpp#L164) | Explanatory comments or spacing. |  |
| [B0037 · 165–178](../../../../../src/recovery/sql_rows_session.cpp#L165) | Callable definition: Session Session::create_into(const resource::MemoryAccount& account,SessionPaths paths,SessionIdentity identity, frontend::SqlRow… | calls require, binary_detail::hex, admit_into, std::move; guard require(limits.history_generations&gt;0,SessionFault::limit);; returns Session(std::move(owner)); growth emplace, make_accounted_unique · [reviewed contract](#b0037) |
| [B0038 · 179–208](../../../../../src/recovery/sql_rows_session.cpp#L179) | Callable definition: GenerationRoot Session::select_checkpoint(Data& d,bool initial) | calls require, ready, sequence, receipt; guard require(!d.head && !d.spool && d.native.ready());const auto c=d.native.sequence();; returns next; growth emplace; source comment (unverified): // Once file mutation starts, any uncertainty requires reopening. Keeping one · [reviewed contract](#b0038) |
| [B0039 · 209–209](../../../../../src/recovery/sql_rows_session.cpp#L209) | Callable definition: GenerationRoot Session::checkpoint() & | calls select_checkpoint, data; returns select_checkpoint(data(),false) · [reviewed contract](#b0039) |
| [B0040 · 210–210](../../../../../src/recovery/sql_rows_session.cpp#L210) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_rows · [reviewed contract](#b0040) |

## B0001

[Lines 1–9](../../../../../src/recovery/sql_rows_session.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:e077a4930fca023589c9436ef9ec85d395675019824c63a8b241d4be809eedc1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include Session/binary/error/digest helpers and open local implementation scopes. |
| inputs / outputs | Expose dependencies for the concrete Session method bodies. |
| invariants | No runtime state, validation or I/O is created by these includes/scopes. |
| ownership | No runtime owner or backing allocation is created by these declarations. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0002

[Lines 10–10](../../../../../src/recovery/sql_rows_session.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L10-L10:sha256:20a7449de8c2481164756c0f53dfb37c1a26f1ef5db82f16b3c3cb0e351abecc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce one explicit Session predicate with its fixed fault category. |
| inputs / outputs | bool condition and SessionFault fault -&gt; void when true, SessionFailure(fault) when false. |
| invariants | Only the supplied predicate is tested; this helper infers no other Session invariant. |
| ownership | Scalar inputs; retains no state. |
| failure | Throws SessionFailure only for false condition; no catch or translation. |
| cost | O(1) branch; no explicit allocation on success. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0003

[Lines 11–18](../../../../../src/recovery/sql_rows_session.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L18:sha256:497cc219d6ad6b6c3998b6b541cc0b9a20eb64f4ed4d56d0f1bec733a5c4a40e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify only the five native/source Error codes allowed to become semantic Reject. |
| inputs / outputs | Borrowed error-code string_view -&gt; matching RejectReason or nullopt. |
| invariants | Exact code matches only: weight mismatch, source overflow, UNIQUE, FK, annotation overflow. Resource/contract/underflow codes remain unclassified. |
| ownership | Returns an optional scalar and retains no borrowed bytes. |
| failure | noexcept; does not throw or catch the Error being classified. |
| cost | At most five bounded literal comparisons; no allocation, native work or file access. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0004

[Lines 19–21](../../../../../src/recovery/sql_rows_session.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L21:sha256:e0ea802d2b40a962c5469ace00aac0eae5e522bcf99ad6d565f7fa1f28edc4fd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one actual sink receipt observation into a generation delivery-anchor DTO. |
| inputs / outputs | Const SinkReceipt -&gt; GenerationDeliveryAnchor{sink_id,C,bytes,content_sha256}. |
| invariants | Reads receipt.header()/prefix() only; does not verify a current file or acquire its lock. |
| ownership | Copies fixed arrays/scalars; returned anchor retains no receipt or FD. |
| failure | No explicit failing check; fixed receipt accessors are noexcept. |
| cost | O(1) fixed-width copies; no hash, I/O or allocation. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0005

[Lines 22–23](../../../../../src/recovery/sql_rows_session.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L23:sha256:a8d5186a21c29e435ff081e9157210c4a4c97a68650e5865d940b88d832bf1bc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close local helper scope and import its require name. |
| inputs / outputs | Close session_detail and declare using session_detail::require. |
| invariants | No call or state transition executes. |
| ownership | No runtime owner or backing allocation is created by these declarations. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0006

[Lines 24–30](../../../../../src/recovery/sql_rows_session.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L30:sha256:79850d0e429e9cbd95eae0a3e6af275cdd7b7b5002dde44b8994792680fa982b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble the one receiving-account Session owner from genuine locked root, descriptor and native state. |
| inputs / outputs | Selected authority/runtime/progress plus finite live limits in; private Data out. |
| invariants | LiveLimits copies only fixed operational bounds, not caller-owned cold parameter DTOs. One head/spool and one owner remain the model. |
| ownership | Member order retains the account through native/files/temporary teardown; cold configuration is borrowed only by factories. |
| failure | Construction unwinds owned members normally; no replacement account or additional undo framework. |
| cost | Fixed owner/limit moves plus the genuine existing member storage; no source/result scan. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0007

[Lines 31–34](../../../../../src/recovery/sql_rows_session.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L34:sha256:677e2ca9b62341d5405cae9a5f56149ac6b212bdbec7356285490dd3edb033a0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a usable selected Session with idle native state. |
| inputs / outputs | This Data -&gt; normal return only when not poisoned, wal/sink exist and require no reopen, native.ready() and root.has_selection(). |
| invariants | Guard reads current owner flags/readiness only; it neither validates inode/EOF nor repairs state. |
| ownership | Borrows retained members without changing ownership. |
| failure | Failed predicate throws SessionFailure(state); member readiness checks retain their own contract. |
| cost | Fixed owner/readiness flag checks; no native/source scan, allocation or syscall. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0008

[Lines 35–52](../../../../../src/recovery/sql_rows_session.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L52:sha256:e3be8e9daabadb1bc0e3f3895021d146234bd3eff19430cb1007f830639ad088
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one decoded physical command and pre-fund its strict source/reader progress proposal before input I/O. |
| inputs / outputs | DecodedInput in; Head with immutable input and prepared source-position node out. |
| invariants | Command I is next; source offsets strictly advance and reader bytes/records move consistently even when C will not advance on Reject. |
| ownership | Head owns the frame/cell/replacement arrays and prepared progress; no source-row mirror is retained. |
| failure | Progress/name/resource validation failure publishes no progress/native/input append. |
| cost | Actual source-position lookup/preparation and fixed progress checks are bounded/charged; no whole-source scan. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0009

[Lines 53–63](../../../../../src/recovery/sql_rows_session.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L63:sha256:4d2f5881b4e2664959619c73b60f04df144a650e6ff59cad4920b29286ced1b3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the one logged physical command through the genuine SQL-presented batch factory. |
| inputs / outputs | Existing pending head and descriptor's original output policy in; real move-only native/source token or supported Reject reason out. |
| invariants | Normal source/native/SQL output limits are unchanged; all aliases/weights/constraints prepare atomically. Only the stable semantic allowlist is translated. |
| ownership | The genuine token is the only rollback owner; the logged head remains owned for resource/contract failure. |
| failure | The one explicit Error catch maps supported semantic codes, otherwise rethrows the original failure with committed source/progress unchanged. |
| cost | Actual native/source preparation and opt-in numeric/support output capture; no snapshots/result graph/retry loop. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0010

[Lines 64–68](../../../../../src/recovery/sql_rows_session.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L68:sha256:781886e0036b484dd5b285a9f6daab20e49597428b8dd629ffdedcde14cdf395
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict replay codec work to the remaining one-lifetime budget. |
| inputs / outputs | output flag -&gt; copy of sink or WAL frame Limits whose record.work is min(original cap,remaining replay_codec_work). |
| invariants | Requires spent codec_work&lt;=total cap; computes a view of remaining credit without spending or refilling it. |
| ownership | Returns fixed copied limits; retains no buffer. |
| failure | SessionFailure(limit) for an invalid spent counter. |
| cost | O(1) arithmetic/copies; no codec traversal or allocation. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0011

[Lines 69–72](../../../../../src/recovery/sql_rows_session.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L72:sha256:1a92cc2007277ff434e862e979c51a88233b6f600612f48afb586bb73b5b22f6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit one successful replay codec operation from its retained cumulative allowance. |
| inputs / outputs | uint64 amount -&gt; replayed.codec_work increment after bounded subtraction checks. |
| invariants | Checks existing spent&lt;=cap and amount&lt;=remaining before mutation, preventing wrap/refill. |
| ownership | Mutates one retained scalar only. |
| failure | SessionFailure(limit) leaves the counter unchanged when admission fails. |
| cost | O(1) checked arithmetic; no allocation or codec work is executed by this debit. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0012

[Lines 73–81](../../../../../src/recovery/sql_rows_session.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L81:sha256:d6811b5e36c876643b915a85c1db3f271b05a009f3cad82fb2be21efcd4c6330
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode and fund one canonical genuine SQL-presented output frame before durable Commit. |
| inputs / outputs | Active prepared SQL token, pending input identity and selected generation in; owned complete RowEpoch frame out. |
| invariants | Physical C/input I/hash/source-changed identity is tied to this real token. Empty/no-op output still gets a complete epoch; row signed magnitude is never narrowed. |
| ownership | Encoder uses receiving-account scratch/packed keys/final bytes; one future spool owns the final frame. No second owning SQL delta graph is introduced. |
| failure | Any output/codec/resource failure leaves the caller's token to roll back and the same logged head pending; no Commit is appended. |
| cost | Explicit native capture decode, canonical ordering, hashing/serialization and selected replay charges; byte visits use codec limits and token reads share one decode allowance. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0013

[Lines 82–91](../../../../../src/recovery/sql_rows_session.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L91:sha256:d484c399517faec0f05789075680fe66d92d9351ee9e5d5a53dc3cb0a38337eb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the already-funded native/source/progress decision and at most one canonical output spool after decision fsync. |
| inputs / outputs | Prepared token or semantic Reject and optional complete output Frame in; committed C/I/progress/spool out. |
| invariants | The fail-stop latch starts before native publication. Reject consumes I without C; successful empty decisions still advance C and require delivery. No throwing preparation remains after durable decision. |
| ownership | Move existing token/progress nodes/frame; clear the one head; preserve one source/native owner and original account. |
| failure | Unexpected publication contract failure keeps poisoned/reopen required; no broad catch, secondary journal or retry framework is added. |
| cost | Funded nonallocating commit/progress moves/cleanup, no output re-encoding or source scan. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0014

[Lines 92–101](../../../../../src/recovery/sql_rows_session.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L101:sha256:66d15cd3f5406aa2b812b7709b8324df776a4deb753e7259f6ad0f8baa95d6da
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate actual successful replay native/source/SQL-output counters. |
| inputs / outputs | Genuine prepared token after codec output reads in; checked replay diagnostics out. |
| invariants | Counts report selected work only, not elapsed CPU; original normal per-command limits remain unchanged. |
| ownership | Only fixed existing counters are copied/added. |
| failure | Counter overflow rejects the private receiving construction rather than wrap diagnostics. |
| cost | Fixed number of checked additions. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0016

[Lines 103–103](../../../../../src/recovery/sql_rows_session.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L103:sha256:9346a5e366b5c40732dd999ed49e2e48df38d3956d58832d5959ee9033a13cc1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the already funded private Session owner. |
| inputs / outputs | AccountedUnique&lt;Data&gt; value -&gt; moved data_ member. |
| invariants | Constructor itself performs no admission, file operation or readiness validation. |
| ownership | Transfers the one unique Data/account lifetime without copying it. |
| failure | Declared noexcept. |
| cost | O(1) owning-handle move; no allocation. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0017

[Lines 104–105](../../../../../src/recovery/sql_rows_session.cpp#L104); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L104-L105:sha256:e65a5a0d5fd3bfcd9dd981dfa80893905404d8a78c6be06339d0a06395165df7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Default Session destruction and noexcept move construction. |
| inputs / outputs | Declare default destructor and default move constructor. |
| invariants | Move transfers data_; destruction uses existing reverse Data/member teardown and performs no new recovery protocol. |
| ownership | Data/member RAII releases current resources at destruction; move creates no copy of source/native/file state. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0018

[Lines 106–106](../../../../../src/recovery/sql_rows_session.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L106:sha256:937af13190cfb59e27da6d9ebde0c87093e6ca815b8b0741f2ca419cced8d169
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return Session Data after handle-presence and readiness checks. |
| inputs / outputs | This Session -&gt; mutable Data& after require(bool(data_)) and data_-&gt;ready(). |
| invariants | Checks only owner/readiness predicates; no physical-file validation or replay occurs. |
| ownership | Returns a reference borrowing this unique owner. |
| failure | Empty/unready Session throws the existing SessionFailure from the guards. |
| cost | O(1) pointer and fixed readiness checks; no allocation or I/O. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0019

[Lines 107–109](../../../../../src/recovery/sql_rows_session.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L109:sha256:de05321df36f82f50e603899e79628d9bdf17aaceb1c1d430473b06fc42aa5c2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report whether this facade requires fresh recovery without throwing. |
| inputs / outputs | This Session -&gt; true for absent Data,poisoned,missing wal/sink or either file requires_reopen(). |
| invariants | Does not call ready(), inspect native state or validate actual files; result is an owner-health flag observation. |
| ownership | Reads pointers/flags only and retains no new owner. |
| failure | noexcept; missing owners return true. |
| cost | O(1) fixed pointer/flag reads; no allocation or syscall. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0020

[Lines 110–114](../../../../../src/recovery/sql_rows_session.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L110-L114:sha256:4d3c8659bd6e20dd796bec7018ac5cd8b22e0e1a6075a4b54c3ed0360e7eecce
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the current W/I/C/D, selected generation and pending-head/spool flags. |
| inputs / outputs | Ready Session -&gt; SessionState from WAL.logged_sequence,progress.sequence,native.sequence,sink.prefix.C,selected generation and optional flags. |
| invariants | Observes retained state; no frontier is advanced and no inode/EOF is reread. |
| ownership | Returns fixed-value metadata only. |
| failure | Session/file readiness guards propagate; no repair or error conversion. |
| cost | O(1) getter/copy work; no source scan, hash, allocation or I/O. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0021

[Lines 115–115](../../../../../src/recovery/sql_rows_session.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L115-L115:sha256:510e943bf3f1eb910155eaa4f7f093bbd944282ae1d48351517b6cb3efde6702
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the selected generation-root descriptor. |
| inputs / outputs | data().root.selected() -&gt; GenerationRoot fixed value. |
| invariants | Returns the named retained value; this accessor performs no preparation, publication or revalidation. |
| ownership | Return owns fixed root DTO fields; it retains no FD, lock or selection authority. |
| failure | data() applies the existing Session presence/readiness guard; delegated getter guards propagate. |
| cost | O(1) readiness/field access and fixed copy or reference return; no scan, binding, hash, allocation or I/O. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0022

[Lines 116–116](../../../../../src/recovery/sql_rows_session.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L116-L116:sha256:6a6b39c71484afd67a74977b1b35f57bc0d4cfe82165e3c58dd02f961e542b5f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained genuine row descriptor. |
| inputs / outputs | data().descriptor -&gt; const Descriptor&. |
| invariants | Returns the named retained value; this accessor performs no preparation, publication or revalidation. |
| ownership | Reference borrows this Session Data; keep the serialized Session owner alive. No descriptor copy/rebind occurs. |
| failure | data() applies the existing Session presence/readiness guard; delegated getter guards propagate. |
| cost | O(1) readiness/field access and fixed copy or reference return; no scan, binding, hash, allocation or I/O. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0023

[Lines 117–117](../../../../../src/recovery/sql_rows_session.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L117-L117:sha256:1f9a31c5c38d19e69bd5105623df618ee0bd4328ae587b361267cc36fe5ae6ec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow committed input-progress metadata. |
| inputs / outputs | data().progress -&gt; const AccountedInputProgress&. |
| invariants | Returns the named retained value; this accessor performs no preparation, publication or revalidation. |
| ownership | Reference borrows the live serialized Data and its account-backed positions; subsequent mutation can change it. |
| failure | data() applies the existing Session presence/readiness guard; delegated getter guards propagate. |
| cost | O(1) readiness/field access and fixed copy or reference return; no scan, binding, hash, allocation or I/O. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0024

[Lines 118–118](../../../../../src/recovery/sql_rows_session.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L118:sha256:3a1f5fa56f27d5107a130a5601e2253e027921b394a17f4094e817dec54af71d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the committed optional reader position. |
| inputs / outputs | data().reader -&gt; optional&lt;ReaderPosition&gt;. |
| invariants | Returns the named retained value; this accessor performs no preparation, publication or revalidation. |
| ownership | Fixed scalar optional is returned by value; no progress backing is retained. |
| failure | data() applies the existing Session presence/readiness guard; delegated getter guards propagate. |
| cost | O(1) readiness/field access and fixed copy or reference return; no scan, binding, hash, allocation or I/O. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0025

[Lines 119–121](../../../../../src/recovery/sql_rows_session.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L119-L121:sha256:55aaa25dd279718041620b31e0ceccebb0a18419f3149ab5f0dabaafec60ad8f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a pending head reader position when present, otherwise the committed reader position. |
| inputs / outputs | Ready Session -&gt; head.input.view().reader if engaged, else data.reader. |
| invariants | The head view is fixed stored metadata; no Input bytes are reparsed and no progress is published. |
| ownership | Returns optional ReaderPosition by value; retains no frame borrow. |
| failure | Session readiness/private input-view invariants apply; no new handler. |
| cost | O(1) optional/view reads; no allocation or I/O. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0026

[Lines 122–122](../../../../../src/recovery/sql_rows_session.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L122-L122:sha256:7f698654a7958bc2ebac8909b018a698bf8fa4176ce974f8394adb285db86a44
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the currently logged undecided input if one exists. |
| inputs / outputs | Ready Session -&gt; optional InputView from owned head.input.view(), or nullopt. |
| invariants | Returns the named retained value; this accessor performs no preparation, publication or revalidation. |
| ownership | Cell/replacement/source views borrow the owned head and expire when that head is resolved/reset or owner is destroyed. |
| failure | Session readiness and private DecodedInput view invariant apply. |
| cost | O(1) optional/view construction; no wire inspection, row copy, allocation or I/O. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0027

[Lines 123–123](../../../../../src/recovery/sql_rows_session.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L123-L123:sha256:5dcf550e8894500b0e6979ab5599013c2300f9f1c9687dae99cb19a020e0a2c4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the canonical committed output spool if delivery remains pending. |
| inputs / outputs | Ready Session -&gt; optional string_view over spool.bytes(), or nullopt. |
| invariants | Returns the named retained value; this accessor performs no preparation, publication or revalidation. |
| ownership | Bytes borrow the owned spool; delivery/reset/owner destruction invalidates them. Reading does not acknowledge delivery. |
| failure | Session readiness guard applies. |
| cost | O(1) optional/pointer-length access; no encoding, hashing, allocation or I/O. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0028

[Lines 124–124](../../../../../src/recovery/sql_rows_session.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L124-L124:sha256:16d8d1020911ce51c939c673b34390d12916916a390b0db0e05fb237c28c4823
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the accumulated replay statistics. |
| inputs / outputs | data().replayed -&gt; ReplayStatistics value. |
| invariants | Returns the named retained value; this accessor performs no preparation, publication or revalidation. |
| ownership | Fixed counters are copied; returned value owns no runtime/frame/file storage. |
| failure | data() applies the existing Session presence/readiness guard; delegated getter guards propagate. |
| cost | O(1) readiness/field access and fixed copy or reference return; no scan, binding, hash, allocation or I/O. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0029

[Lines 125–125](../../../../../src/recovery/sql_rows_session.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L125-L125:sha256:baf918822c20bd6c345be9338055b3d66da329a6b80a71dfb3a53efd43387fa4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open a committed SQL result cursor through the genuine native runtime. |
| inputs / outputs | CursorOptions and ready Session -&gt; data().native.results(options). |
| invariants | This call opens a cursor; rows are enumerated later. The runtime lease blocks mutations until terminal/cancel/destruction. |
| ownership | Returned move-only cursor retains its runtime and receiving-account cursor state. |
| failure | Session readiness plus runtime cursor admission/account failures propagate. |
| cost | Fixed delegation plus actual runtime cursor setup/allocation; no eager full result enumeration or snapshot. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0030

[Lines 126–126](../../../../../src/recovery/sql_rows_session.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L126-L126:sha256:a9814caed943343d577aede6f2648a0bf71acaafc3090dd61956e6bfd6f316ba
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read committed native full-root weight before SQL presentation. |
| inputs / outputs | data().native.root_weight() -&gt; weighted::Multiplicity. |
| invariants | Returns the named retained value; this accessor performs no preparation, publication or revalidation. |
| ownership | Returns a scalar; this is neither presented row count nor an exported result bag. |
| failure | data() applies the existing Session presence/readiness guard; delegated getter guards propagate. |
| cost | O(1) readiness/field access and fixed copy or reference return; no scan, binding, hash, allocation or I/O. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0031

[Lines 127–127](../../../../../src/recovery/sql_rows_session.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L127-L127:sha256:bd7d00a9c5ae72ed10ccff4742b13ba28e613a5e271933533ce15a1e5f16040c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Look up one complete physical source-row weight through the genuine runtime. |
| inputs / outputs | TableId and span&lt;const nullable Cell&gt; -&gt; data().native.source_weight(table,row), zero when absent. |
| invariants | Runtime validates actual full row/table/type domain before lookup; Session adds only readiness. |
| ownership | Input row/text is borrowed for the call; no owning row or result graph is created. |
| failure | Session/runtime shape,type,UTF8 and state failures propagate; no semantic Reject conversion. |
| cost | Actual complete-row validation plus ordered source-map comparisons, including string bytes; no allocation or full source scan. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0033

[Lines 129–137](../../../../../src/recovery/sql_rows_session.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L129-L137:sha256:727d19fdabf2d1faace8da2888eccee645734d661190846e2f51016c0bb55157
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pre-fund one next physical Input and append/sync it only after prior committed output is delivered. |
| inputs / outputs | Next InputView at exact I+1 in; one owned durable pending head out. |
| invariants | No existing head/spool; WAL I/C/native C/sink D frontiers agree. Input ordinal and logical command sequence remain distinct. |
| ownership | Head owns input/progress before I/O; fixed noexcept move publishes it only after the actual WAL append confirms durability. |
| failure | Funding/type/progress failure publishes no head/native change; uncertain append poisons the file and requires reopen. |
| cost | Explicit bounded transport/source-position preparation and actual append/fsync; no native commit or output yet. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0034

[Lines 138–154](../../../../../src/recovery/sql_rows_session.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L138-L154:sha256:ef51c61a2b2f7c851580fcdb109e8717bbbd75931a6ae880be70ac61147145ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve the one logged head with genuine atomic source changes and exact pre-encoded SQL output or a supported Reject. |
| inputs / outputs | Pending owned Input plus consistent WAL head in; Decision{I,C,reason} out. |
| invariants | Encode/fund output and Commit length/hash before fsync; only then publish. Reject has unchanged C and no output; resource/contract failures remain pending and untagged. |
| ownership | One genuine prepared token plus at most one final frame; publication moves already-owned state. |
| failure | Existing RAII unwinds preparation before durable decision; append uncertainty requires reopen, with no inferred commit outcome or extra catch. |
| cost | Actual selected source/native/capture/codec/append work; no full result snapshot or unrelated feature path. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0035

[Lines 155–163](../../../../../src/recovery/sql_rows_session.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L155-L163:sha256:bf7394c64d07885a294ed71977476efe50c2fc3aa9060551f0c34b17083c6747
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Confirm actual canonical sink bytes/receipt before acknowledging the one committed spool. |
| inputs / outputs | Optional pending output in; false for none or true after exact append/retry confirmation. |
| invariants | Native C must equal the actual receipt prefix C. A complete empty-output frame is still acknowledged; stdout/snapshot is not delivery. |
| ownership | Sink retains bounded offset metadata, not a payload queue; successful receipt check releases the one spool. |
| failure | I/O uncertainty is latched by file owner; unexpected post-append private mismatch poisons Session before dropping output. |
| cost | Bounded actual write/sync or complete-byte retry comparison plus fixed receipt check; funded post-I/O state changes allocate nothing. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0037

[Lines 165–178](../../../../../src/recovery/sql_rows_session.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L165-L178:sha256:46d357310bdcc9ee34370bea81ad42ecbbd2dd34ffacf9dd202d8a88916eb12b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one durable Session from genuine SQL/checked tree and original normal/output policies. |
| inputs / outputs | Receiving account/new paths/IDs/program/tree/physical options/finite grants in; locked initial selected Session out. |
| invariants | No editable native DTO enters. Require finite history and valid labels; descriptor/source admission is genuine and initial C/I are zero. |
| ownership | Move real descriptor/runtime into one account-owned Data, create actual sink and initial checkpoint/WAL/root; cold parameter options are not retained in live limits. |
| failure | Normal factory RAII closes abandoned owners; actual durable candidate/file outcomes are governed by existing file/generation contracts, never guessed or silently overwritten. |
| cost | Explicit cold compilation/lowering/metadata retention, initial physical image and bounded file publication; no per-update source snapshot. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0038

[Lines 179–208](../../../../../src/recovery/sql_rows_session.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L179-L208:sha256:14b50a4a540902d4ef6493c7b245711c5138633b41db9b55debf61499cd59718
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a complete physical checkpoint with descriptor/WAL before selecting one new root generation. |
| inputs / outputs | Quiescent headless/spoolless owner at W=I,D=C in; actual selected GenerationRoot out. |
| invariants | Cold image preparation precedes the poison latch; every file mutation afterward requires reopen on failure. Preserve prior latch through validation, publish root last, and retain the generation-1 nonrefillable history bound. |
| ownership | Real sink receipt binds checkpoint anchor; root lock and actual candidate identities remain owned until selection; allocate/fund candidates before root publication. |
| failure | Before mutation errors preserve ready owner; after latch, any uncertainty requires reopen. No retirement, per-stage retry or catch framework is introduced. |
| cost | Explicit cold O(physical source rows/bytes) image/encode and finite durable plan/checkpoint/WAL/root operations; no update-path row mirror. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0039

[Lines 209–209](../../../../../src/recovery/sql_rows_session.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L209-L209:sha256:936409ad2dbf37c3c514e723fdadaf1b1b432114209eb16ab65a3bfa4f34736a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate explicit Session checkpoint selection for an established generation. |
| inputs / outputs | Ready lvalue Session -&gt; select_checkpoint(data(),false) GenerationRoot. |
| invariants | Wrapper adds readiness only; full W=I,D=C/head/spool/history/durable checks are in select_checkpoint. |
| ownership | Delegated selection retains the same owner/account/locks. |
| failure | Propagates readiness/selection failure and fail-stop latch; no catch/retry. |
| cost | Fixed delegation plus actual explicit snapshot/image/file/root publication costs of select_checkpoint; no automatic per-update checkpoint. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0040

[Lines 210–210](../../../../../src/recovery/sql_rows_session.cpp#L210); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L210-L210:sha256:5a88989d646de8c904ac4cbcd84db92dc85500003eb77614a29dedc10d8206dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the surrounding namespace/type at this exact lexical boundary. |
| inputs / outputs | No runtime arguments, results or state transition. |
| invariants | A scope delimiter carries no admission, replay, invariant or rollback authority. |
| ownership | Namespace/type closure does not destroy objects merely by being declared here. |
| failure | No runtime failure or handler exists in this delimiter. |
| cost | No executable or per-query cost. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |
