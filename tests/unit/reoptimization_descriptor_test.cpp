#include "crown/recovery/plan_descriptor.hpp"
#include "history_retirement_fixture.hpp"

namespace {
using namespace crown;
using namespace crown::recovery;
using session_checkpoint_test::check;
constexpr std::string_view artifact="{\"compiler_input\":\"golden-test-only\"}";
std::string unhex(std::string_view text) {
  std::string out;int high=-1;
  for(const char c:text) {
    if(c=='\n' || c=='\r' || c==' ' || c=='\t')continue;
    const int digit=c>='0' && c<='9'?c-'0':c>='a' && c<='f'?c-'a'+10:-1;check(digit>=0,"descriptor golden contains nonhex bytes");
    if(high<0)high=digit;else{out.push_back(static_cast<char>(16*high+digit));high=-1;}
  }
  check(high<0,"descriptor golden has a half byte");return out;
}
template<class Function> void rejected(Function&& function,std::optional<ImageFault> expected={}) {
  try{function();}catch(const ImageFailure& failure){check(!expected || failure.fault()==*expected,"descriptor rejected with wrong fault");return;}
  throw std::runtime_error("descriptor accepted invalid framing/grant/binding");
}
PlanSelection selection(const detail::RetirementIntent& seed,bool sink=true,bool parent_plan=true,bool delivery=false) {
  PlanSelection out;out.predecessor=seed.before;out.source=seed.sink.binding;out.target=out.source;
  out.target.physical_sha256=sha256_fixed("selected physical plan");out.generation=8;out.physical_sequence=11;out.command_sequence=14;
  if(parent_plan)out.predecessor.plan_sha256=sha256_fixed("predecessor descriptor");
  if(sink)out.sink_origin=seed.sink;
  if(delivery)out.predecessor.delivery=GenerationDeliveryAnchor{seed.sink.sink_id,out.predecessor.physical_sequence,1234,sha256_fixed("prefix")};
  return out;
}
void golden(const detail::RetirementIntent& seed,std::string_view bytes) {
  const auto account=resource::MemoryAccount::create(4*1024*1024);const auto expected=selection(seed);
  const auto encoded=encode_plan_descriptor(account,expected,artifact);
  check(bytes.size()==1529 && std::string_view(encoded.bytes.data(),encoded.bytes.size())==bytes,"native descriptor differs from independent Python packet");
  const auto inspected=inspect_plan_descriptor(bytes);
  check(inspected.selection==expected && inspected.compiler_artifact==artifact,"independent descriptor decoded metadata/bytes differ");
  check(inspected.statistics.bytes==bytes.size() && inspected.statistics.work==bytes.size()*4,"descriptor work units differ");
}
void variants(const detail::RetirementIntent& seed) {
  const auto account=resource::MemoryAccount::create(4*1024*1024);const auto before=account.statistics().current;
  for(const bool sink:{false,true})for(const bool plan:{false,true})for(const bool delivery:{false,true})for(const bool switched:{false,true}) {
    if(delivery && !sink)continue;
    auto input=selection(seed,sink,plan,delivery);if(switched)input.last_switch_epoch=0;
    const auto encoded=encode_plan_descriptor(account,input,artifact);
    InspectedPlanDescriptor decoded;
    {s04_alloc::Scope deny(0);decoded=inspect_plan_descriptor({encoded.bytes.data(),encoded.bytes.size()});}
    check(decoded.selection==input && decoded.compiler_artifact==artifact && encoded.bytes.get_allocator().account().statistics().owner==account.statistics().owner,
        "descriptor optional fields/zero-allocation inspection/original account differ");
    check(account.statistics().current.requested_bytes>before.requested_bytes,"descriptor bytes were not funded");
    PlanDescriptorLimits limits;limits.bytes=encoded.bytes.size();limits.artifact_bytes=artifact.size();limits.work=encoded.statistics.work;
    const auto exact=encode_plan_descriptor(account,input,artifact,limits);static_cast<void>(inspect_plan_descriptor({exact.bytes.data(),exact.bytes.size()},limits));
    --limits.bytes;rejected([&]{static_cast<void>(encode_plan_descriptor(account,input,artifact,limits));},ImageFault::limit);++limits.bytes;
    --limits.work;rejected([&]{static_cast<void>(encode_plan_descriptor(account,input,artifact,limits));},ImageFault::work);++limits.work;
    --limits.artifact_bytes;rejected([&]{static_cast<void>(inspect_plan_descriptor({exact.bytes.data(),exact.bytes.size()},limits));},ImageFault::limit);
  }
  check(account.statistics().current==before,"descriptor ownership release leaked original account memory");
}
void corruption(std::string_view packet) {
  for(std::size_t cut=0;cut<packet.size();++cut)rejected([&]{static_cast<void>(inspect_plan_descriptor(packet.substr(0,cut)));});
  for(std::size_t i=0;i<packet.size();++i) {
    auto changed=std::string(packet);changed[i]^=1;rejected([&]{static_cast<void>(inspect_plan_descriptor(changed));});
  }
  for(const std::size_t offset:{std::size_t{8},std::size_t{10},std::size_t{12},std::size_t{20},std::size_t{52},std::size_t{20+128+64+344+64}}) {
    auto changed=std::string(packet);changed[offset]^=1;history_retirement_test::checksum(changed);
    rejected([&]{static_cast<void>(inspect_plan_descriptor(changed));});
  }
}
void bindings_and_allocation(const detail::RetirementIntent& seed) {
  const auto account=resource::MemoryAccount::create(4*1024*1024);const auto input=selection(seed);const auto before=account.statistics().current;
  auto changed=input;changed.target.source_sha256=sha256_fixed("foreign source");
  rejected([&]{static_cast<void>(encode_plan_descriptor(account,changed,artifact));},ImageFault::binding);
  changed=input;++changed.target.catalog_version;rejected([&]{static_cast<void>(encode_plan_descriptor(account,changed,artifact));},ImageFault::binding);
  changed=input;changed.target.policy[0]=changed.target.policy[0]?0:1;rejected([&]{static_cast<void>(encode_plan_descriptor(account,changed,artifact));});
  changed=input;++changed.generation;rejected([&]{static_cast<void>(encode_plan_descriptor(account,changed,artifact));},ImageFault::binding);
  changed=input;changed.sink_origin->binding.source_sha256=sha256_fixed("foreign sink source");rejected([&]{static_cast<void>(encode_plan_descriptor(account,changed,artifact));},ImageFault::binding);
  changed=selection(seed,true,true,true);changed.sink_origin.reset();rejected([&]{static_cast<void>(encode_plan_descriptor(account,changed,artifact));},ImageFault::binding);
  changed=input;changed.last_switch_epoch=changed.physical_sequence+1;rejected([&]{static_cast<void>(encode_plan_descriptor(account,changed,artifact));},ImageFault::binding);
  PlanDescriptorLimits limits;limits.fields=0;rejected([&]{static_cast<void>(encode_plan_descriptor(account,input,artifact,limits));},ImageFault::limit);
  bool failed=false;
  {s04_alloc::Scope deny(0);try{static_cast<void>(encode_plan_descriptor(account,input,artifact));}catch(const std::bad_alloc&){failed=true;}}
  check(failed && account.statistics().current==before,"descriptor allocation failure changed receiving account");
  const auto retry=encode_plan_descriptor(account,input,artifact);check(inspect_plan_descriptor({retry.bytes.data(),retry.bytes.size()}).selection==input,"descriptor failure cannot retry");
}
} // namespace
int main(int argc,char** argv) {
  try {
    check(argc==3,"usage: reoptimization_descriptor RETIREMENT_GOLDEN DESCRIPTOR_GOLDEN");
    const auto seed=detail::inspect_retirement_intent(unhex(session_file_test::contents(argv[1])));
    const auto packet=unhex(session_file_test::contents(argv[2]));golden(seed,packet);variants(seed);corruption(packet);bindings_and_allocation(seed);
    std::cout<<"C06 plan descriptor PASS: independent1529-byte golden, twelve optional-field combinations, all truncations/bit flips, exact work/byte/artifact grants, logical/sink binding, native funding/failure/retry. Compiler semantic admission remains separate.\n";
    return 0;
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
