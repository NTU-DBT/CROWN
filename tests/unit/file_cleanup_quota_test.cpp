#include "journal_file_fixture.hpp"
#include "journal_file_probe.hpp"
#include "local_sink_probe.hpp"
#include "generation_file_probe.hpp"
#include "generation_detail.hpp"
#include <cassert>
#include <cerrno>

namespace {
using namespace crown;
namespace jp=recovery::journal;
namespace sk=recovery::sink;
using crown::journal_file_test::Directory;
using crown::journal_file_test::contents;
// Repeat EINTR at ordinary post-link unlink and its emergency cleanup. Record
// every admitted attempt so the operation cap plus eight cleanup attempts is
// independently asserted; no allocator or simulated filesystem is substituted.
struct Interrupt {
  std::uint64_t last=0,unlinks=0;
  template<class Event,class Decision> Decision visit(const Event& event,bool unlink) noexcept {
    last=event.ordinal;Decision result;
    if(!event.after && unlink) {++unlinks;result.error_before=EINTR;}
    return result;
  }
  static jp::testing::FileDecision journal(const jp::testing::FileEvent& event,void* context) noexcept {
    return static_cast<Interrupt*>(context)->visit<jp::testing::FileEvent,jp::testing::FileDecision>(event,event.stage==jp::FileStage::unlink_temporary);
  }
  static sk::testing::Decision sink(const sk::testing::Event& event,void* context) noexcept {
    return static_cast<Interrupt*>(context)->visit<sk::testing::Event,sk::testing::Decision>(event,event.stage==sk::Stage::unlink_temporary);
  }
  static recovery::testing::GenerationDecision generation(const recovery::testing::GenerationEvent& event,void* context) noexcept {
    return static_cast<Interrupt*>(context)->visit<recovery::testing::GenerationEvent,recovery::testing::GenerationDecision>(event,event.stage==recovery::GenerationStage::unlink_temporary);
  }
};
// All three owners must fail at the configured quota, report the bounded
// cleanup failure, release their actual locks/FDs, and preserve linked bytes.
void legacy_owners(const jp::Header& header) {
  constexpr std::uint64_t cap=32;Directory dir;const auto account=resource::MemoryAccount::create(8ULL*1024*1024);
  const auto before=crown::journal_file_test::descriptors();
  {
    Interrupt hook;auto limits=jp::FileLimits{};limits.operations=cap;bool failed=false;
    jp::testing::set_file_hook(Interrupt::journal,&hook);
    try {auto file=jp::File::create(account,dir.file("wal"),header,limits);}
    catch(const jp::FileFailure& error) {failed=error.fault()==jp::FileFault::limit && error.temporary_cleanup_failed();}
    jp::testing::set_file_hook(nullptr,nullptr);assert(failed && hook.last==cap+8 && hook.unlinks>8);
    auto file=jp::File::open(account,dir.file("wal"),header);assert(file.state().records==1);
  }
  {
    sk::Header binding;binding.query_id=header.query_id;binding.sink_id.fill('a');binding.binding=header.binding;
    const std::array<ScalarType,0> schema{};binding.schema_sha256=sk::schema_sha256(account,schema);
    Interrupt hook;auto limits=sk::Limits{};limits.operations=cap;bool failed=false;
    sk::testing::set_hook(Interrupt::sink,&hook);
    try {auto file=sk::File::create(account,dir.file("sink"),binding,schema,limits);}
    catch(const sk::Failure& error) {failed=error.fault()==sk::Fault::limit && error.temporary_cleanup_failed();}
    sk::testing::set_hook(nullptr,nullptr);assert(failed && hook.last==cap+8 && hook.unlinks>8);
    auto file=sk::File::open(account,dir.file("sink"),binding,schema);assert(file.receipt().sequence()==0);
  }
  {
    Interrupt hook;auto limits=recovery::GenerationLimits{};limits.operations=cap;bool failed=false;
    const auto root=dir.file("query.root");std::string candidate;
    {
      recovery::detail::GenerationOwner owner(root,header.query_id,true,limits);candidate=owner.checkpoint_path(1).data();
      recovery::testing::set_generation_hook(Interrupt::generation,&hook);
      try {owner.publish_checkpoint(1,"opaque-candidate");}
      catch(const recovery::GenerationFailure& error) {failed=error.fault()==recovery::GenerationFault::limit && error.temporary_cleanup_failed();}
      recovery::testing::set_generation_hook(nullptr,nullptr);assert(failed && hook.last==cap+8 && hook.unlinks>8);
    }
    assert(contents(candidate)=="opaque-candidate" && !std::filesystem::exists(root));
    recovery::detail::GenerationOwner reopened(root,header.query_id,true,{});assert(!reopened.has_selection());
  }
  assert(crown::journal_file_test::descriptors()==before && account.statistics().current.allocations==1);
}
} // namespace
int main(int argc,char** argv) {
  assert(argc==2);const crown::journal_file_test::Frames frames(argv[1]);legacy_owners(frames.binding);
}
