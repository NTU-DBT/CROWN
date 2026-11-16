#include "invariant_fixture.hpp"
#include "index_allocation.hpp"
#include <iostream>
#include <optional>

using namespace crown;
using namespace crown::runtime;
using namespace s05_inspection;
namespace {
void check(bool value,std::string_view message){if(!value)throw std::runtime_error(std::string(message));}
void verify(const InvariantReport& report,const resource::MemoryAccount& account) {
  const auto id=account.statistics().owner;
  check(report.issues.get_allocator().account().statistics().owner==id,"invariant report issues lost the original account");
  for(const auto& issue:report.issues)check(issue.key.account().statistics().owner==id,"invariant issue key lost its original account");
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto now=account.statistics().current;
  check(now.allocations==1 && now.requested_bytes==resource::MemoryAccount::control_bytes(),"invariant report retained closed runtime storage");
}
template<class Make> void lifetime(Make make) {
  std::optional<Owner> owner(make(allowance));const auto memory=account(*owner);
  {
    const auto before=memory.statistics();std::optional<InvariantReport> healthy;std::size_t calls=0;
    {s04_alloc::Scope count;healthy=inspect(*owner);calls=s04_alloc::calls;}
    check(healthy->valid() && calls>0 && calls==memory.statistics().successful_allocations-before.successful_allocations,"healthy inspection made unfunded requests");
    verify(*healthy,memory);healthy.reset();check(memory.statistics().current==before.current,"healthy inspection retained expected-state scratch");
    const auto start=memory.statistics();{s04_alloc::Scope count;check_invariants(*owner);calls=s04_alloc::calls;}
    check(calls>0 && calls==memory.statistics().successful_allocations-start.successful_allocations && memory.statistics().current==start.current,"check_invariants made unfunded requests or retained scratch");
  }
  const auto corruption=corrupt(*owner);const auto before=memory.statistics();std::optional<InvariantReport> held;std::size_t calls=0;
  {s04_alloc::Scope count;held=inspect(*owner);calls=s04_alloc::calls;}
  check(held->complete && !held->valid() && held->issues.size()==1 && held->issues[0].key==corruption.key,"funded inspection lost exact localized corruption");
  check(calls==memory.statistics().successful_allocations-before.successful_allocations,"corrupt inspection made unfunded requests");verify(*held,memory);
  const auto encoded=io::write_invariant_report(*held);std::optional<InvariantReport> copied;const auto copy_start=memory.statistics();
  {s04_alloc::Scope count;copied=*held;calls=s04_alloc::calls;}
  check(calls>0 && calls==memory.statistics().successful_allocations-copy_start.successful_allocations,"report copy made unfunded requests");verify(*copied,memory);
  restore(*owner,corruption);check(inspect(*owner).valid(),"inspection modified or failed to restore current state");
  {s04_alloc::Scope none(0);owner.reset();verify(*held,memory);verify(*copied,memory);}
  check(io::write_invariant_report(*held)==encoded && io::write_invariant_report(*copied)==encoded,"retained report changed after restoration/owner close");
  {s04_alloc::Scope none(0);std::optional<InvariantReport> moved(std::move(*copied));copied.reset();held.reset();moved.reset();}
  controller_only(memory);
}
template<class Make> std::size_t faults(Make make) {
  auto owner=make(allowance);const auto corruption=corrupt(owner);const auto memory=account(owner);const auto held=inspect(owner);const auto encoded=io::write_invariant_report(held);std::size_t expected=0;
  {s04_alloc::Scope count;const auto value=inspect(owner);expected=s04_alloc::calls;}
  check(expected>0 && expected<8192,"invariant allocation calibration exceeds finite fixture bound");
  for(std::size_t point=0;point<=expected;++point) {
    const auto before=memory.statistics().current;std::optional<InvariantReport> value;bool failed=false;std::size_t calls=0;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{value=inspect(owner);}catch(const std::bad_alloc&){failed=true;}calls=s04_alloc::calls;}
    if(point<expected)check(failed && !value && calls==point+1,"invariant inspection missed a persistent allocation failure");
    else check(!failed && value && calls==expected && value->complete,"invariant final allocation probe did not succeed");
    value.reset();check(memory.statistics().current==before,"invariant allocation failure leaked private scratch or issues");verify(held,memory);
    check(io::write_invariant_report(inspect(owner))==encoded && io::write_invariant_report(held)==encoded,"failed invariant inspection changed current state or an old report");
  }
  std::size_t copies=0;{s04_alloc::Scope count;const auto copy=held;copies=s04_alloc::calls;}
  check(copies>0,"invariant copy allocation calibration was empty");
  for(std::size_t point=0;point<copies;++point) {
    const auto before=memory.statistics().current;bool failed=false;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{const auto copy=held;}catch(const std::bad_alloc&){failed=true;}}
    check(failed && memory.statistics().current==before && io::write_invariant_report(held)==encoded,"failed invariant report copy damaged its source or leaked storage");
  }
  restore(owner,corruption);check(inspect(owner).valid(),"allocation sweep changed restored state");return expected;
}
template<class Make> void limits(Make make,bool byte_caps) {
  auto owner=make(allowance);const auto corruption=corrupt(owner);const auto full=inspect(owner);const auto memory=account(owner);
  for(const bool exact:{true,false}) {
    InspectionOptions options;options.work_limit=full.work-(exact?0:1);const auto result=inspect(owner,options);
    check(result.complete==exact && !result.valid(),"invariant exact/one-under work limit changed completeness");verify(result,memory);
    options=InspectionOptions{};options.issue_limit=full.issues.size()-(exact?0:1);const auto issues=inspect(owner,options);
    check(issues.complete==exact && !issues.valid() && issues.issues.size()==(exact?full.issues.size():0),"invariant exact/one-under issue limit changed localized output");verify(issues,memory);
  }
  restore(owner,corruption);if(!byte_caps)return;
  std::uint64_t peak=0;std::size_t pins=0;
  {auto value=make(allowance);static_cast<void>(corrupt(value));const auto budget=account(value);std::vector<InvariantReport> held;held.reserve(2048);
    for(std::size_t i=0;i<2048;++i){const auto before=budget.statistics().peak_requested_bytes;auto report=inspect(value);const auto after=budget.statistics().peak_requested_bytes;
      if(i>0 && after>before){peak=after;pins=i;break;}held.push_back(std::move(report));}
  }
  check(peak>0 && pins>0,"invariant hoarding did not cross the genuine setup peak");
  for(const bool exact:{true,false}) {
    auto value=make(exact?peak:peak-1);static_cast<void>(corrupt(value));const auto budget=account(value);std::vector<InvariantReport> held;held.reserve(pins);
    for(std::size_t i=0;i<pins;++i)held.push_back(inspect(value));
    const auto before=budget.statistics().current;bool failed=false;
    try{const auto report=inspect(value);verify(report,budget);}catch(const std::bad_alloc&){failed=true;}
    check(failed!=exact && budget.statistics().current==before,"invariant query-byte boundary changed or leaked current state");verify(held.front(),budget);
    if(!exact){held.pop_back();verify(inspect(value),budget);check(budget.statistics().limit_bytes==peak-1,"invariant retry minted another allowance");}
  }
}
}
int main(int argc,char** argv) {
  try {
    if(argc==3 && std::string_view(argv[1])=="--export-directory"){export_reports(argv[2]);return 0;}
    check(argc==1,"unknown invariant memory test argument");std::size_t cases=0;
    each([&](unsigned flavor,bool indexed,std::size_t shape,Kind kind,const PhysicalPlan& plan,const Database& database) {
      std::cout<<"invariants flavor="<<flavor<<" indexed="<<indexed<<" shape="<<shape<<" kind="<<static_cast<unsigned>(kind)<<std::endl;
      const auto create=[&](std::uint64_t cap){return make(plan,database,kind,cap);};lifetime(create);const auto positions=faults(create);limits(create,shape==0);
      std::cout<<"persistent allocation positions="<<positions<<'\n';++cases;
    });
    check(cases==42,"invariant memory fixture matrix changed");std::cout<<"42 authentic invariant allocation/limit/lifetime cases passed\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
