#pragma once

// Fixed, test-only observers shared by the baseline and mixed-transaction
// persistence matrices. Production objects and default paths have no hook field.
#include "sql_aggregate_session_fixture.hpp"
#include "sql_aggregate_file_probe.hpp"
#include "generation_file_probe.hpp"
#include "index_allocation.hpp"
#include <cerrno>

namespace crown::sql_aggregate_session_test {
namespace gt = recovery::testing;
// Fixed test observations join the two existing file seams without changing
// production layouts. A point is one actual syscall attempt, before/after.
struct Event {
  std::uint64_t point;bool generation,after;
  ar::FileStage file;recovery::GenerationStage root;recovery::GenerationTarget target;
  std::int64_t result;
};
struct Hook {
  std::array<Event,4096> events{};std::size_t size=0;
  std::uint64_t point=0,fail=0,crash=0,deny=0;
  bool after=false,armed=false;
  void observe(bool generation,bool done,ar::FileStage file,recovery::GenerationStage root,
      recovery::GenerationTarget target,std::int64_t result) noexcept {
    if(!done)++point;
    assert(size<events.size());events[size++]={point,generation,done,file,root,target,result};
    if(point==crash && done==after)::_exit(77);
    if(point==deny && done) {s04_alloc::remaining=0;s04_alloc::calls=0;s04_alloc::triggered=false;armed=true;}
  }
  static ar::testing::FileDecision file(const ar::testing::FileEvent& event,void* context) noexcept {
    auto& h=*static_cast<Hook*>(context);h.observe(false,event.after,event.stage,recovery::GenerationStage::state,recovery::GenerationTarget::root,event.result);
    ar::testing::FileDecision result;
    if(!event.after && h.point==h.fail) {if(h.after)result.error_after=EIO;else result.error_before=EIO;}
    return result;
  }
  static gt::GenerationDecision root(const gt::GenerationEvent& event,void* context) noexcept {
    auto& h=*static_cast<Hook*>(context);h.observe(true,event.after,ar::FileStage::state,event.stage,event.target,event.result);
    gt::GenerationDecision result;
    if(!event.after && h.point==h.fail) {if(h.after)result.error_after=EIO;else result.error_before=EIO;}
    return result;
  }
};
struct Installed {
  explicit Installed(Hook& hook) {ar::testing::set_file_hook(Hook::file,&hook);gt::set_generation_hook(Hook::root,&hook);}
  ~Installed() {ar::testing::set_file_hook(nullptr,nullptr);gt::set_generation_hook(nullptr,nullptr);}
};
inline bool durability(const Event& event) {
  if(!event.generation)return event.file==ar::FileStage::write_data || event.file==ar::FileStage::sync_file ||
      event.file==ar::FileStage::sync_directory || event.file==ar::FileStage::link_file || event.file==ar::FileStage::truncate_tail;
  return event.root==recovery::GenerationStage::write_data || event.root==recovery::GenerationStage::sync_file ||
      event.root==recovery::GenerationStage::sync_directory || event.root==recovery::GenerationStage::link_file || event.root==recovery::GenerationStage::rename_root;
}
} // namespace crown::sql_aggregate_session_test
