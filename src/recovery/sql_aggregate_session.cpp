#include "sql_aggregate_session_detail.hpp"
#include "binary_detail.hpp"
#include "crown/api/error.hpp"
#include "crown/ir/digest.hpp"
#include <algorithm>
#include <type_traits>

namespace crown::recovery::sql_aggregate {
namespace session_detail {
void require(bool condition,SessionFault fault) { if(!condition)throw SessionFailure(fault); }
std::optional<RejectReason> semantic(std::string_view code) noexcept {
  if(code=="sql_rows_weight_mismatch")return RejectReason::weight_mismatch;
  if(code=="sql_rows_overflow")return RejectReason::source_overflow;
  if(code=="unique_violation")return RejectReason::unique_violation;
  if(code=="foreign_key_violation")return RejectReason::foreign_key_violation;
  if(code=="aggregate_overflow")return RejectReason::aggregate_overflow;
  if(code=="annotation_overflow")return RejectReason::annotation_overflow;
  return {}; // Work/memory/contract/underflow errors never become semantic Reject.
}
GenerationDeliveryAnchor anchor(const SinkReceipt& receipt) {
  const auto& prefix=receipt.prefix();return {receipt.header().sink_id,prefix.physical_sequence,prefix.bytes,prefix.content_sha256};
}
} // namespace session_detail
using session_detail::require;
Session::Data::Data(const resource::MemoryAccount& memory,const SessionLimits& requested,
    ::crown::recovery::detail::GenerationOwner generation,Descriptor admitted,runtime::SqlAggregateRuntime runtime,
    io::AccountedInputProgress positions,std::optional<ReaderPosition> position)
    : account(memory),limits{requested.checkpoint,requested.capture,requested.wal,requested.sink,
          requested.history_generations,requested.replay_commands,requested.replay_codec_work},
      root(std::move(generation)),descriptor(std::move(admitted)),native(std::move(runtime)),
      progress(std::move(positions)),reader(position) {}
void Session::Data::ready() const {
  require(!poisoned && wal && sink && !wal->requires_reopen() && !sink->requires_reopen());
  require(native.ready() && root.has_selection());
}
Session::Data::Head Session::Data::own(DecodedInput input) {
  const auto view=input.view();
  require(progress.sequence<UINT64_MAX && view.command_sequence==progress.sequence+1,SessionFault::progress);
  io::InputPositions::Prepared position;
  if(view.source) {
    require(view.source->source.size()<=limits.checkpoint.source_bytes,SessionFault::limit);
    const auto old=progress.source_positions.find(view.source->source);
    if(old==progress.source_positions.end())require(progress.source_positions.size()<limits.checkpoint.sources,SessionFault::limit);
    else require(view.source->offset>old->second,SessionFault::progress);
    position=progress.source_positions.prepare(view.source->source,view.source->offset);
  }
  if(view.reader) {
    const auto old=reader.value_or(ReaderPosition{});
    require(old.records<UINT64_MAX && view.reader->records==old.records+1 &&
        view.reader->records<=view.command_sequence && view.reader->bytes>old.bytes,SessionFault::progress);
  }
  return {std::move(input),std::move(position)};
}
Session::Data::Prepared Session::Data::prepare() {
  require(head.has_value());const auto view=head->input.view();
  // The genuine source/native/group token is the only rollback mechanism.
  // Catch only its explicit semantic errors; all resource/contract errors escape
  // with the same owned logged head and unpublished progress still retained.
  try { return {native.prepare_batch({native.sequence()+1,view.replacements}),{}}; }
  catch(const Error& error) {
    const auto reason=session_detail::semantic(error.code());if(!reason)throw;
    return {{},reason};
  }
}
Limits Session::Data::codec_limits(bool output) const {
  auto result=output?limits.sink.scan.frame:limits.wal.scan.frame;
  require(replayed.codec_work<=limits.replay_codec_work,SessionFault::limit);
  result.record.work=std::min(result.record.work,limits.replay_codec_work-replayed.codec_work);return result;
}
void Session::Data::charge_codec(std::uint64_t amount) {
  require(replayed.codec_work<=limits.replay_codec_work && amount<=limits.replay_codec_work-replayed.codec_work,SessionFault::limit);
  replayed.codec_work+=amount;
}
Frame Session::Data::epoch(const runtime::sql_aggregate::Epoch& output,bool replaying) {
  require(head && output.captured,SessionFault::transition);
  const auto input=head->input.view();const auto& frame=head->input.frame();
  auto result=encode(account,descriptor.program(),output.sequence,
      GroupEpochView{root.selected().generation,input.command_sequence,output.sequence,frame.info().body_sha256,
          output.changed,output.group_changed,output.output},replaying?codec_limits(true):limits.sink.scan.frame);
  if(replaying)charge_codec(result.info().statistics.work);
  return result;
}
void Session::Data::publish(Prepared& prepared,std::optional<Frame> output) {
  const auto view=head->input.view();
  // All token/output/progress storage was funded before the durable decision.
  // The latch also covers an impossible invalid private-token publication.
  poisoned=true;
  if(prepared.token)static_cast<void>(prepared.token->commit());
  progress.source_positions.publish(head->position);progress.sequence=view.command_sequence;
  if(view.reader)reader=view.reader;
  spool=std::move(output);head.reset();poisoned=false;
}
void Session::Data::observe(const runtime::sql_aggregate::Epoch& output) {
  const auto add=[](std::uint64_t& total,std::uint64_t value) {require(value<=UINT64_MAX-total,SessionFault::limit);total+=value;};
  add(replayed.native_work,output.native.metrics.work);add(replayed.group_work,output.metrics.work);
  add(replayed.source_work.structural_steps,output.source_work.structural_steps);
  add(replayed.source_work.scalar_fields,output.source_work.scalar_fields);
  add(replayed.source_work.scalar_bytes,output.source_work.scalar_bytes);
  add(replayed.source_work.pointer_slots,output.source_work.pointer_slots);
  add(replayed.source_work.link_actions,output.source_work.link_actions);
}

Session::Session(resource::AccountedUnique<Data> value) noexcept : data_(std::move(value)) {}
Session::~Session()=default;
Session::Session(Session&&) noexcept=default;
Session::Data& Session::data() const { require(bool(data_));data_->ready();return *data_; }
bool Session::requires_reopen() const noexcept {
  return !data_ || data_->poisoned || !data_->wal || !data_->sink || data_->wal->requires_reopen() || data_->sink->requires_reopen();
}
SessionState Session::state() const {
  const auto& d=data();const auto w=d.wal->state().wal;
  return {w.logged_sequence,d.progress.sequence,d.native.sequence(),d.sink->state().prefix.physical_sequence,
      d.root.selected().generation,d.head.has_value(),d.spool.has_value()};
}
GenerationRoot Session::selected_root() const { return data().root.selected(); }
const Descriptor& Session::descriptor() const & { return data().descriptor; }
const io::AccountedInputProgress& Session::progress() const & { return data().progress; }
std::optional<ReaderPosition> Session::reader_position() const { return data().reader; }
std::optional<ReaderPosition> Session::logged_reader_position() const {
  const auto& d=data();if(d.head && d.head->input.view().reader)return d.head->input.view().reader;return d.reader;
}
std::optional<InputView> Session::pending_input() const & { const auto& d=data();return d.head?std::optional{d.head->input.view()}:std::nullopt; }
std::optional<std::string_view> Session::output() const & { const auto& d=data();return d.spool?std::optional{d.spool->bytes()}:std::nullopt; }
ReplayStatistics Session::replay_statistics() const { return data().replayed; }
runtime::sql_aggregate::Snapshot Session::snapshot(runtime::aggregate::SnapshotLimits limits) const { return data().native.snapshot(limits); }
std::uint64_t Session::source_weight(TableId table,std::span<const runtime::sql_rows::Cell> row) const { return data().native.source_weight(table,row); }

void Session::log(const InputView& input) & {
  auto& d=data();const auto state=d.wal->state().wal;const auto c=d.native.sequence();
  require(!d.head && !d.spool && state.logged_sequence==d.progress.sequence && state.command_sequence==d.progress.sequence &&
      state.physical_sequence==c && d.sink->state().prefix.physical_sequence==c);
  require(c<UINT64_MAX && d.progress.sequence<UINT64_MAX && input.command_sequence==d.progress.sequence+1,SessionFault::progress);
  auto head=d.own(encode_input(d.account,d.descriptor.program(),state.records,input,d.limits.wal.scan.frame));
  static_assert(std::is_nothrow_move_constructible_v<Data::Head>);
  d.wal->append(head.input.frame());d.head.emplace(std::move(head));
}
Decision Session::decide() & {
  auto& d=data();require(d.head && !d.spool);const auto state=d.wal->state().wal;
  require(state.pending && state.pending->ordinal==d.head->input.frame().info().ordinal,SessionFault::transition);
  auto prepared=d.prepare();const auto command=d.head->input.view().command_sequence;const auto& input=d.head->input.frame();
  if(prepared.rejected) {
    auto decision=encode(d.account,d.descriptor.program(),state.records,
        Reject{input.info().ordinal,input.info().body_sha256,command,d.native.sequence(),*prepared.rejected},d.limits.wal.scan.frame);
    d.wal->append(decision);d.publish(prepared,{});
  } else {
    auto output=d.epoch(prepared.token->preview(),false);
    auto decision=encode(d.account,d.descriptor.program(),state.records,
        Commit{input.info().ordinal,input.info().body_sha256,command,prepared.token->preview().sequence,
            output.bytes().size(),sha256_fixed(output.bytes())},d.limits.wal.scan.frame);
    d.wal->append(decision);d.publish(prepared,std::move(output));
  }
  return {command,d.native.sequence(),prepared.rejected};
}
bool Session::deliver() & {
  auto& d=data();if(!d.spool)return false;
  static_cast<void>(d.sink->append(*d.spool));
  // The external effect is confirmed. An unexpected private postcondition
  // failure must fail-stop, just like native publication after Commit sync.
  d.poisoned=true;const auto receipt=d.sink->receipt();
  require(receipt.prefix().physical_sequence==d.native.sequence(),SessionFault::binding);
  d.spool.reset();d.poisoned=false;return true;
}

Session Session::create_into(const resource::MemoryAccount& account,SessionPaths paths,SessionIdentity identity,
    frontend::SqlAggregateProgram program,const FreeConnexTree& tree,const PhysicalOptions& physical,
    runtime::sql_aggregate::Options options,const SessionLimits& limits) {
  require(limits.history_generations>0,SessionFault::limit);
  require(binary_detail::hex(identity.query_id) && binary_detail::hex(identity.sink_id),SessionFault::binding);
  auto admitted=admit_into(account,std::move(program),tree,physical,options,limits.admission);
  ::crown::recovery::detail::GenerationOwner root(paths.root,identity.query_id,true,limits.generation);
  require(!root.retirement(),SessionFault::binding);
  auto owner=resource::make_accounted_unique<Data>(image_owner,account,resource::MemoryPurpose::recovery_log,
      account,limits,std::move(root),std::move(admitted.descriptor),std::move(admitted.runtime),io::AccountedInputProgress(account),std::nullopt);
  owner->sink.emplace(SinkFile::create(account,paths.sink,owner->descriptor,
      SinkHeader{{identity.query_id,owner->descriptor.sha256()},identity.sink_id,0},limits.sink));
  static_cast<void>(select_checkpoint(*owner,true));return Session(std::move(owner));
}
GenerationRoot Session::select_checkpoint(Data& d,bool initial) {
  require(!d.head && !d.spool && d.native.ready());const auto c=d.native.sequence();
  const auto receipt=d.sink->receipt();require(receipt.prefix().physical_sequence==c,SessionFault::binding);
  const auto selected=d.root.selected();
  if(!initial) {
    const auto state=d.wal->state().wal;
    require(state.logged_sequence==d.progress.sequence && state.command_sequence==d.progress.sequence && state.physical_sequence==c);
    require(selected.first_generation==1 && selected.generation<d.limits.history_generations && selected.generation<UINT64_MAX,SessionFault::limit);
  }
  const auto generation=initial?1:selected.generation+1;
  const Binding binding{initial?receipt.header().binding.query_id:selected.query_id,d.descriptor.sha256()};
  const auto image=encode_checkpoint(d.account,d.descriptor,d.native.source_snapshot(d.limits.capture),
      CheckpointMetadata{binding,generation,c,d.progress.sequence,session_detail::anchor(receipt)},d.progress,d.reader,d.limits.checkpoint);
  if(!initial) {
    try { d.root.prepare_next(generation); }
    catch(const GenerationFailure& error) {
      // Failure while validating the selected root invalidates this owner.
      // Unselected-candidate unlink/sync failures do not change that selection.
      if(error.stage()!=GenerationStage::unlink_candidate && error.stage()!=GenerationStage::sync_directory)d.poisoned=true;
      throw;
    }
  }
  d.root.publish_plan(generation,d.descriptor.bytes());d.root.publish_checkpoint(generation,image.bytes());
  const auto path=d.root.journal_path(generation);
  auto wal=WalFile::create(d.account,path.data(),d.descriptor,
      WalHeader{binding,generation,image.info().sha256,c,d.progress.sequence},d.limits.wal);
  GenerationRoot next{binding.query_id,generation,1,image.info().sha256,c,d.progress.sequence,
      session_detail::anchor(receipt),d.descriptor.sha256()};
  if(initial)d.sink->validate();else validate_files(d);
  wal.validate();
  // Keep the actual root/locks on uncertainty. All allocating candidates and the
  // synced matching WAL exist before this single selection boundary.
  try { d.root.publish_root(next); }
  catch(...) { if(d.root.selection_attempted())d.poisoned=true;throw; }
  d.wal.emplace(std::move(wal));return next;
}
GenerationRoot Session::checkpoint() & { return select_checkpoint(data(),false); }
} // namespace crown::recovery::sql_aggregate
