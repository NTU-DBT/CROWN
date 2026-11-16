#include "crown/recovery/sql_aggregate_records.hpp"
#include "binary_detail.hpp"
#include <algorithm>

namespace crown::recovery::sql_aggregate {
Inspected WalCursor::feed(const frontend::SqlAggregateProgram& program,std::string_view frame) {
  using binary_detail::require;
  // Admit cumulative transport bytes/work before parsing; no per-frame refill.
  require(state_.records<limits_.records,ImageFault::limit);
  require(state_.bytes<=limits_.bytes && frame.size()<=limits_.bytes-state_.bytes,ImageFault::limit);
  require(state_.work<=limits_.work,ImageFault::work);
  auto limits=limits_.frame;limits.record.work=std::min(limits.record.work,limits_.work-state_.work);
  auto info=inspect(program,frame,limits);require(info.ordinal==state_.records);
  auto next=state_; // Fixed-size candidate; failed validation publishes nothing.
  if(next.records==0) {
    require(info.kind==Kind::wal_header);next.header=std::get<WalHeader>(info.payload);
    next.logged_sequence=next.command_sequence=next.header.command_sequence;
    next.physical_sequence=next.sink_floor=next.header.physical_sequence;
  } else if(info.kind==Kind::input) {
    const auto& input=std::get<InputInfo>(info.payload);
    require(!next.pending && next.command_sequence<UINT64_MAX && next.physical_sequence<UINT64_MAX);
    require(input.command_sequence==next.command_sequence+1);
    next.pending=PendingInput{info.ordinal,input.command_sequence,info.body_sha256};
    next.logged_sequence=input.command_sequence;
    // A writer may log a new Input only after actual D=C. This lower bound
    // permits recovery with one final missing output epoch, never a queue.
    next.sink_floor=next.physical_sequence;
  } else if(info.kind==Kind::commit || info.kind==Kind::reject) {
    require(next.pending.has_value());const auto& pending=*next.pending;
    if(info.kind==Kind::commit) {
      const auto& value=std::get<Commit>(info.payload);
      require(value.input_ordinal==pending.ordinal && value.input_sha256==pending.body_sha256,ImageFault::binding);
      require(value.command_sequence==pending.command_sequence && next.physical_sequence<UINT64_MAX &&
          value.physical_sequence==next.physical_sequence+1);
      require(value.output_bytes<=limits_.frame.record.bytes,ImageFault::limit);
      next.physical_sequence=value.physical_sequence;
    } else {
      const auto& value=std::get<Reject>(info.payload);
      require(value.input_ordinal==pending.ordinal && value.input_sha256==pending.body_sha256,ImageFault::binding);
      require(value.command_sequence==pending.command_sequence && value.physical_sequence==next.physical_sequence);
    }
    next.command_sequence=pending.command_sequence;next.pending.reset();
  } else require(false);
  ++next.records;next.bytes+=frame.size();next.work+=info.statistics.work;state_=next;
  return info;
}
} // namespace crown::recovery::sql_aggregate
