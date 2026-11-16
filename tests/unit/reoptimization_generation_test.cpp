#include "history_retirement_fixture.hpp"
#include "generation_file_probe.hpp"
#include <cerrno>
#include <sys/wait.h>

namespace {
using namespace crown;
using namespace crown::recovery;
using generation_test::put;
using session_file_test::contents;
using session_file_test::Directory;
using session_file_test::descriptors;
using session_checkpoint_test::check;
using detail::GenerationOwner;
constexpr std::string_view first_plan="self-contained plan descriptor one";
constexpr std::string_view next_plan="self-contained plan descriptor two";
constexpr std::string_view first_checkpoint="checkpoint one";
constexpr std::string_view next_checkpoint="checkpoint two";
enum class Action {plan,select,read};
template<class Function> GenerationFailure rejected(Function&& function) {
  try{function();}catch(const GenerationFailure& failure){return failure;}
  throw std::runtime_error("generation descriptor accepted an invalid boundary");
}
struct Files {
  Directory directory;
  resource::MemoryAccount account=resource::MemoryAccount::create(8*1024*1024);
  std::string root=directory.file("query.root");
  std::array<char,32> query=generation_test::options().journal.query_id;
  GenerationLimits limits;
  std::optional<GenerationOwner> owner;
  explicit Files(bool delivery=false) {
    owner.emplace(root,query,true,limits);owner->publish_checkpoint(1,first_checkpoint);owner->publish_plan(1,first_plan);
    auto initial=selection(1);
    if(delivery)initial.delivery=GenerationDeliveryAnchor{local_sink_test::options().sink_id,0,148,sha256_fixed("prefix")};
    owner->publish_root(initial);
  }
  GenerationRoot selection(std::uint64_t generation) const {
    GenerationRoot result{query,generation,1,sha256_fixed(generation==1?first_checkpoint:next_checkpoint),0,0};
    result.plan_sha256=sha256_fixed(generation==1?first_plan:next_plan);return result;
  }
  std::string path(std::uint64_t generation,std::string_view suffix) const {return generation_test::path(root,generation,suffix);}
  void prepare(Action action) {
    if(action==Action::read)return;
    owner->prepare_next(2);owner->publish_checkpoint(2,next_checkpoint);
    if(action==Action::select)owner->publish_plan(2,next_plan);
  }
  void perform(Action action) {
    if(action==Action::plan)owner->publish_plan(2,next_plan);
    else if(action==Action::select)owner->publish_root(selection(2));
    else static_cast<void>(owner->read_plan(account));
  }
  void recover() {
    owner.reset();owner.emplace(root,query,false,limits);const auto generation=owner->selected().generation;
    check(generation==1 || generation==2,"uncertain root selected an unknown generation");
    const auto bytes=owner->read_plan(account);check(std::string_view(bytes.data(),bytes.size())==(generation==1?first_plan:next_plan),"root recovery chose another descriptor");
    check(contents(path(1,".plan"))==first_plan && contents(path(1,".ckpt"))==first_checkpoint,"candidate operation changed original files");
  }
};
void codec_and_binding() {
  for(const bool delivery:{false,true}) {
    Files f(delivery);const auto bytes=contents(f.root);const auto selected=f.owner->selected();
    check(bytes.size()==(delivery?generation_root_plan_delivery_size:generation_root_plan_size) &&
        static_cast<unsigned char>(bytes[8])==3 && static_cast<unsigned char>(bytes[10])==(delivery?1:0) && inspect_generation_root(bytes)==selected,"v3 root shape/selection differs");
    for(std::size_t cut=0;cut<bytes.size();++cut)static_cast<void>(rejected([&]{static_cast<void>(inspect_generation_root(std::string_view(bytes).substr(0,cut)));}));
    for(std::size_t i=0;i<bytes.size();++i) {
      auto changed=bytes;changed[i]^=1;static_cast<void>(rejected([&]{static_cast<void>(inspect_generation_root(changed));}));
    }
    f.prepare(Action::plan);auto next=f.selection(2);next.delivery=selected.delivery;
    check(rejected([&]{f.owner->publish_root(next);}).fault()==GenerationFault::binding,"root selected an unpublished descriptor");
    f.owner->publish_plan(2,next_plan);auto wrong=next;wrong.plan_sha256=sha256_fixed("other");
    check(rejected([&]{f.owner->publish_root(wrong);}).fault()==GenerationFault::binding,"root selected the wrong descriptor hash");
    wrong=next;wrong.plan_sha256.reset();check(rejected([&]{f.owner->publish_root(wrong);}).fault()==GenerationFault::binding,"rotation stripped selected plan lineage");
    {s04_alloc::Scope deny(0);f.owner->publish_root(next);}
    const auto current=contents(f.root);check(inspect_generation_root(current)==next,"nonallocating root selection changed metadata");f.recover();
  }
}
void resource_and_corruption() {
  Files f;const auto before=f.account.statistics().current.requested_bytes;
  f.owner.reset();const auto compiler=CompiledProgram::standalone(window_checkpoint_test::plan(false));
  const auto denied=rejected([&]{static_cast<void>(runtime::QuerySession::restore_generation(compiler,f.root,generation_test::recovery_options()));});
  check(denied.fault()==GenerationFault::binding && denied.stage()==GenerationStage::state,"caller-selected plan bypassed descriptor-aware recovery");
  f.owner.emplace(f.root,f.query,false,f.limits);
  {
    const auto bytes=f.owner->read_plan(f.account);
    check(bytes.get_allocator().account().statistics().owner==f.account.statistics().owner &&
        f.account.statistics().current.requested_bytes>before,"descriptor read bypassed receiving account");
  }
  check(f.account.statistics().current.requested_bytes==before,"descriptor read retained a buffer");
  put(f.path(1,".plan"),"tampered descriptor");check(rejected([&]{static_cast<void>(f.owner->read_plan(f.account));}).fault()==GenerationFault::binding,"descriptor hash mismatch was accepted");
  check(contents(f.path(1,".plan"))=="tampered descriptor","failed descriptor read repaired bytes");put(f.path(1,".plan"),first_plan);
  f.owner.reset();f.limits.plan_bytes=first_plan.size()-1;f.owner.emplace(f.root,f.query,false,f.limits);
  check(rejected([&]{static_cast<void>(f.owner->read_plan(f.account));}).fault()==GenerationFault::limit,"descriptor byte grant was ignored");
  f.owner.reset();f.limits.plan_bytes=first_plan.size();f.owner.emplace(f.root,f.query,false,f.limits);static_cast<void>(f.owner->read_plan(f.account));
  f.owner->prepare_next(2);put(f.path(2,".plan"),"orphan descriptor");put(f.path(2,".ckpt"),"orphan checkpoint");put(f.path(2,".wal"),"orphan WAL");
  f.owner->prepare_next(2);check(!std::filesystem::exists(f.path(2,".plan")) && !std::filesystem::exists(f.path(2,".ckpt")) && !std::filesystem::exists(f.path(2,".wal")),"candidate cleanup left orphan descriptor/pair");
  check(contents(f.path(1,".plan"))==first_plan,"candidate cleanup removed selected descriptor");
}
struct Hook {
  std::uint64_t calls=0,fail=0,crash=0;
  bool after=false;
  static testing::GenerationDecision visit(const testing::GenerationEvent& event,void* context) noexcept {
    auto& self=*static_cast<Hook*>(context);if(!event.after)++self.calls;
    if(self.crash==self.calls && event.after==self.after)::_exit(77);
    testing::GenerationDecision result;
    if(!event.after && self.fail==self.calls){if(self.after)result.error_after=EIO;else result.error_before=EIO;}
    return result;
  }
};
struct Installed {
  explicit Installed(Hook& hook){testing::set_generation_hook(Hook::visit,&hook);}
  ~Installed(){testing::set_generation_hook(nullptr,nullptr);}
};
std::uint64_t call_count(Action action) {Files f;f.prepare(action);Hook hook;{Installed scope(hook);f.perform(action);}return hook.calls;}
void faults_and_crashes(bool crash) {
  std::uint64_t cuts=0;
  for(const auto action:{Action::plan,Action::select,Action::read}) {
    const auto count=call_count(action);
    for(std::uint64_t point=1;point<=count;++point)for(const bool after:{false,true}) {
      Files f;f.prepare(action);const auto original=contents(f.root);const auto opened=descriptors();Hook hook;hook.after=after;
      if(crash) {
        const auto pid=::fork();check(pid>=0,"descriptor crash fork failed");
        if(pid==0){hook.crash=point;Installed scope(hook);try{f.perform(action);}catch(...){::_exit(3);}::_exit(4);}
        int status=0;check(::waitpid(pid,&status,0)==pid && WIFEXITED(status) && WEXITSTATUS(status)==77,"descriptor syscall crash cut missed");
      }else {
        hook.fail=point;{Installed scope(hook);static_cast<void>(rejected([&]{f.perform(action);}));}
        if(f.owner->selection_attempted()) {
          const auto denied=rejected([&]{f.owner->prepare_next(2);});check(denied.fault()==GenerationFault::state && denied.outcome()==GenerationOutcome::unknown,"uncertain selection owner was reused");
          static_cast<void>(rejected([&]{f.owner->publish_checkpoint(2,next_checkpoint);}));
          static_cast<void>(rejected([&]{f.owner->publish_plan(2,next_plan);}));
          static_cast<void>(rejected([&]{f.owner->publish_root(f.selection(2));}));
          static_cast<void>(rejected([&]{static_cast<void>(f.owner->read_plan(f.account));}));
        }
      }
      if(action!=Action::select)check(contents(f.root)==original,"descriptor-only failure changed selected root");
      f.recover();check(descriptors()==opened,"descriptor fault/crash leaked file descriptors");++cuts;
    }
  }
  std::cout<<"C06 generation descriptor "<<(crash?"process crash":"I/O failure")<<" cuts PASS: "<<cuts<<" before/after real plan-publication/root-selection/locked-read calls; surviving root/descriptor and uncertainty latch.\n";
}
void retirement() {
  Files f;f.prepare(Action::select);f.owner->publish_root(f.selection(2));
  auto plan=window_checkpoint_test::plan(false);runtime::DeltaRuntime runtime(plan);
  const auto image=runtime.checkpoint_image();const std::array schema{ScalarType::int64};
  sink::Header header{f.query,local_sink_test::options().sink_id,image.manifest.binding,1,0,1,sink::schema_sha256(f.account,schema)};
  auto output=sink::File::create(f.account,f.directory.file("output.sink"),header,schema);
  const detail::RetirementIntent intent{f.owner->selected(),header,1,0};const auto encoded=detail::encode_retirement_intent(intent);
  check(encoded.size()==detail::retirement_plan_intent_size && static_cast<unsigned char>(encoded.data()[8])==2,"v2 retirement intent shape differs");
  const auto decoded=detail::inspect_retirement_intent({encoded.data(),encoded.size()});
  check(decoded.before.plan_sha256==f.owner->selected().plan_sha256,"retirement intent lost selected plan hash");
  auto changed=std::string(encoded.data(),encoded.size());changed[changed.size()-65]='g';history_retirement_test::checksum(changed);
  static_cast<void>(rejected([&]{static_cast<void>(detail::inspect_retirement_intent(changed));}));
  auto other=intent;other.before.plan_sha256=sha256_fixed("foreign descriptor");const auto foreign=detail::encode_retirement_intent(other);
  put(f.root+".retire",{foreign.data(),foreign.size()});
  check(rejected([&]{f.owner->retire_history(output.receipt(),next_checkpoint,f.account);}).fault()==GenerationFault::binding && std::filesystem::exists(f.path(1,".plan")),"foreign plan retirement intent deleted history");
  std::filesystem::remove(f.root+".retire");put(f.path(2,".plan"),"tampered selected descriptor");
  check(rejected([&]{f.owner->retire_history(output.receipt(),next_checkpoint,f.account);}).fault()==GenerationFault::binding &&
      std::filesystem::exists(f.path(1,".plan")),"retirement deleted recovery history with a damaged selected descriptor");
  put(f.path(2,".plan"),next_plan);f.owner->retire_history(output.receipt(),next_checkpoint,f.account);
  check(f.owner->selected().first_generation==2 && f.owner->selected().plan_sha256==intent.before.plan_sha256 &&
      !std::filesystem::exists(f.path(1,".plan")) && !std::filesystem::exists(f.path(1,".ckpt")) && !std::filesystem::exists(f.path(1,".wal")) &&
      contents(f.path(2,".plan"))==next_plan,"retirement removed current descriptor or lost lineage");
  f.owner.reset();f.owner.emplace(f.root,f.query,false,f.limits);const auto bytes=f.owner->read_plan(f.account);
  check(std::string_view(bytes.data(),bytes.size())==next_plan && f.owner->selected().first_generation==2,"retired selection could not recover its self-contained descriptor");
}
} // namespace
int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: reoptimization_generation faults|crash");
    if(std::string_view(argv[1])=="crash")faults_and_crashes(true);
    else {codec_and_binding();resource_and_corruption();retirement();faults_and_crashes(false);}
    return 0;
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
