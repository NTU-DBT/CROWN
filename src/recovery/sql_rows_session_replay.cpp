#include "sql_rows_session_detail.hpp"
#include "crown/ir/digest.hpp"

namespace crown::recovery::sql_rows {
using session_detail::require;
void Session::replay(std::string_view bytes,const Inspected& info,const WalState& after,void* context) {
  auto& d=*static_cast<Data*>(context);const auto delivered=d.sink->state().prefix.physical_sequence;
  if(info.kind==Kind::wal_header)return;
  if(info.kind==Kind::input) {
    // Logging a later Input proves the previous C was already acknowledged.
    // Reject inconsistent history immediately rather than collecting a queue.
    require(!d.head && !d.spool && d.native.sequence()<=delivered,SessionFault::binding);
    require(d.replayed.commands<d.limits.replay_commands,SessionFault::limit);++d.replayed.commands;
    auto input=decode_input(d.account,d.descriptor.program(),bytes,d.codec_limits(false));
    d.charge_codec(input.frame().info().statistics.work);d.head.emplace(d.own(std::move(input)));return;
  }
  require(d.head.has_value(),SessionFault::transition);auto prepared=d.prepare();
  if(info.kind==Kind::reject) {
    const auto& expected=std::get<Reject>(info.payload);
    require(prepared.rejected && *prepared.rejected==expected.reason,SessionFault::binding);
    d.publish(prepared,{});
  } else {
    require(info.kind==Kind::commit && prepared.token && !prepared.rejected,SessionFault::binding);
    const auto& expected=std::get<Commit>(info.payload);const auto& preview=*prepared.token;
    auto output=d.epoch(preview,true);d.observe(preview);d.charge_codec(output.bytes().size());
    require(expected.output_bytes==output.bytes().size() && expected.output_sha256==sha256_fixed(output.bytes()),SessionFault::binding);
    if(preview.sequence()<=delivered) {d.sink->verify(output);d.publish(prepared,{});}
    else {
      require(delivered<UINT64_MAX && preview.sequence()==delivered+1 && !d.spool,SessionFault::binding);
      d.publish(prepared,std::move(output));
    }
  }
  require(d.native.sequence()==after.physical_sequence && d.progress.sequence==after.command_sequence,SessionFault::binding);
}
void Session::validate_files(Data& d) {
  const bool previous=d.poisoned;d.poisoned=true;
  d.sink->validate();d.wal->validate();
  require(d.root.read_root(false,false)==d.root.selected(),SessionFault::binding);
  d.poisoned=previous;
}
Session Session::recover_into(const resource::MemoryAccount& account,SessionPaths paths,const Id& query_id,const SessionLimits& limits) {
  require(limits.history_generations>0,SessionFault::limit);
  ::crown::recovery::detail::GenerationOwner root(paths.root,query_id,false,limits.generation);const auto selected=root.selected();
  require(selected.plan_sha256 && selected.delivery && selected.physical_sequence<=selected.command_sequence &&
      selected.first_generation==1 && selected.generation<=limits.history_generations && !root.retirement(),SessionFault::binding);
  // Rebinding's empty/static C0 runtime dies before the actual checkpoint owner
  // is built. Retain genuine descriptor metadata, never a second live database.
  auto descriptor=[&] {
    const auto bytes=root.read_plan(account);auto admitted=rebind_into(account,{bytes.data(),bytes.size()},limits.admission);
    return std::move(admitted.descriptor);
  }();
  require(descriptor.sha256()==*selected.plan_sha256,SessionFault::binding);
  auto restored=[&] {
    const auto bytes=root.read_checkpoint(account);
    return restore_checkpoint_into(account,descriptor,{bytes.data(),bytes.size()},
        CheckpointMetadata{{query_id,descriptor.sha256()},selected.generation,selected.physical_sequence,selected.command_sequence,*selected.delivery},
        limits.rebuild,limits.checkpoint);
  }();
  auto owner=resource::make_accounted_unique<Data>(image_owner,account,resource::MemoryPurpose::recovery_log,
      account,limits,std::move(root),std::move(descriptor),std::move(restored.runtime),std::move(restored.progress),restored.reader);
  owner->sink.emplace(SinkFile::open(account,paths.sink,owner->descriptor,
      SinkHeader{{query_id,owner->descriptor.sha256()},selected.delivery->sink_id,0},limits.sink));
  const auto baseline=owner->sink->prefix(selected.physical_sequence);
  require(baseline.bytes==selected.delivery->bytes && baseline.content_sha256==selected.delivery->content_sha256 &&
      owner->sink->state().prefix.generation<=selected.generation,SessionFault::binding);
  const auto path=owner->root.journal_path(selected.generation);
  owner->wal.emplace(WalFile::open_replay(account,path.data(),owner->descriptor,
      WalHeader{{query_id,owner->descriptor.sha256()},selected.generation,selected.checkpoint_sha256,selected.physical_sequence,selected.command_sequence},
      limits.wal,Session::replay,owner.get()));
  const auto state=owner->wal->state();const auto delivered=owner->sink->state().prefix.physical_sequence;
  require(state.wal.sink_floor<=delivered && delivered<=owner->native.sequence() &&
      owner->progress.sequence==state.wal.command_sequence && owner->native.sequence()==state.wal.physical_sequence &&
      owner->head.has_value()==state.wal.pending.has_value(),SessionFault::binding);
  if(owner->head)require(delivered==owner->native.sequence() && !owner->spool,SessionFault::binding);
  const bool torn=state.torn_tail || owner->sink->state().torn_tail;
  require(!torn || limits.repair_torn_tail,SessionFault::tail);
  validate_files(*owner); // Entire root/native/output/coverage barrier before any truncate.
  owner->wal->repair_tail();owner->sink->repair_tail();
  validate_files(*owner);return Session(std::move(owner));
}
} // namespace crown::recovery::sql_rows
