#include "accounted_ordered_rows.hpp"
#include "index_allocation.hpp"

#include <array>
#include <bit>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <ranges>
#include <stdexcept>

using namespace crown;
using namespace crown::runtime::detail;
namespace {
using resource::AllocationLifetime;
using resource::MemoryAccount;
using resource::MemoryAttribution;
using resource::MemoryPurpose;
constexpr MemoryAttribution owner{resource::MemoryOwnerKind::delta_node,7};
void check(bool value,std::string_view message) {
  if(!value)throw std::runtime_error(std::string(message));
}
MemoryAccount account() {return MemoryAccount::create(std::numeric_limits<std::uint64_t>::max());}
Row key(std::int64_t value) {return {value};}
void reconcile(const MemoryAccount& memory) {
  memory.check_invariants();
  const auto state=memory.statistics();resource::MemoryUsage purposes{},lifetimes{};
  const auto add=[](auto& a,const auto& b) {
    a.allocations+=b.allocations;a.requested_bytes+=b.requested_bytes;a.payload_bytes+=b.payload_bytes;
  };
  for(const auto& value:state.by_purpose)add(purposes,value);
  for(const auto& value:state.by_lifetime)add(lifetimes,value);
  check(purposes==state.current && lifetimes==state.current,"actual ordered-row allocations do not reconcile");
  check(state.peak_requested_bytes<=state.limit_bytes,"ordered rows exceeded the account limit");
}
void controller_only(const MemoryAccount& memory) {
  reconcile(memory);
  const auto state=memory.statistics();
  check(state.current.allocations==1 && state.current.requested_bytes==MemoryAccount::control_bytes(),
      "ordered rows retained memory after all owners were released");
}
void equivalent(const AccountedRowSet& rows,const Relation& expected) {
  rows.check_invariants();
  check(rows.export_rows()==expected,"native ordering/membership differs from independent std::set");
  if(!rows.empty())check(rows.height()<=2U*static_cast<unsigned>(std::bit_width(rows.size())),"ordered lookup height is not logarithmic");
  for(std::int64_t i=-1;i<=8;++i) {
    const auto probe=key(i);const auto a=rows.find(probe),b=rows.upper_bound(probe);
    const auto x=expected.find(probe),y=expected.upper_bound(probe);
    check((a==rows.end())==(x==expected.end()),"heterogeneous find differs from std::set");
    check((b==rows.end())==(y==expected.end()),"heterogeneous upper_bound differs from std::set");
    if(b!=rows.end())check(b->view()==*y,"upper_bound selected a different lexical row");
  }
}
void exhaustive_ordering() {
  auto memory=account();
  std::array<std::int64_t,6> order{0,1,2,3,4,5};
  do {
    AccountedRowSet rows(memory,MemoryPurpose::delta_state,owner);Relation expected;
    for(const auto value:order) {
      check(rows.insert(key(value)).second==expected.insert(key(value)).second,"insertion result mismatch");
      equivalent(rows,expected);
    }
    // This reverses construction order for every permutation, exercising each
    // possible deletion order as well as both immediate/deep successor cases.
    for(const auto value:std::views::reverse(order)) {
      const auto probe=key(value);
      auto removed=rows.extract(probe);check(bool(removed),"extraction missed an existing row");
      expected.erase(probe);equivalent(rows,expected);
      {
        s04_alloc::Scope no_allocation(0);
        check(rows.insert(std::move(removed)).inserted,"allocation-free reinsertion failed");
        check(rows.erase(probe)==1,"allocation-free erasure failed");
        check(s04_alloc::calls==0,"extract/reinsert/erase allocated");
      }
      equivalent(rows,expected);
    }
    reconcile(memory);
  }while(std::next_permutation(order.begin(),order.end()));
  controller_only(memory);
}
void random_differential() {
  auto memory=account();
  {
    AccountedRowSet rows(memory,MemoryPurpose::delta_state,owner);Relation expected;
    std::mt19937 random(0x41a7);
    for(std::size_t i=0;i<6000;++i) {
      const auto probe=key(static_cast<std::int64_t>(random()%384));
      if(random()%3==0)check(rows.erase(probe)==expected.erase(probe),"random erase result differs");
      else check(rows.insert(probe).second==expected.insert(probe).second,"random insert result differs");
      if(i%29==0)equivalent(rows,expected);
    }
    equivalent(rows,expected);
    s04_alloc::Scope no_allocation(0);rows.clear();rows.clear();
    check(s04_alloc::calls==0,"iterative tree destruction allocated");
  }
  controller_only(memory);
}
void stable_addresses() {
  auto memory=account();
  {
    AccountedRowMap<std::uint64_t> rows(memory,MemoryPurpose::delta_state,owner);
    std::map<std::int64_t,std::pair<const storage::AccountedRow*,std::uint64_t*>> addresses;
    for(const auto value:std::array<std::int64_t,12>{4,2,9,1,3,6,11,5,7,10,12,8}) {
      const auto i=rows.try_emplace(key(value),static_cast<std::uint64_t>(value)).first;
      addresses.emplace(value,std::pair{&i->first,&i->second});
    }
    for(const auto value:std::array<std::int64_t,12>{4,6,9,2,11,5,1,8,3,12,10,7}) {
      auto handle=rows.extract(key(value));check(bool(handle),"stable-address extraction failed");
      const auto [row,mapped]=addresses.at(value);
      check(&handle.key()==row && &handle.mapped()==mapped,"extraction moved an existing entry");
      for(const auto& [other,address]:addresses)if(other!=value) {
        const auto found=rows.find(key(other));
        check(found!=rows.end() && &found->first==address.first && &found->second==address.second,
            "successor replacement or rotation moved a surviving entry");
      }
      rows.check_invariants();
      {
        s04_alloc::Scope no_allocation(0);
        const auto returned=rows.insert(std::move(handle));
        check(returned.inserted && &returned.position->first==row && &returned.position->second==mapped,
            "reinsertion replaced an undo row's identity");
        check(s04_alloc::calls==0,"stable-address reinsertion allocated");
      }
      rows.erase(key(value));addresses.erase(value);rows.check_invariants();
    }
  }
  controller_only(memory);
}
void scalar_ownership_and_lifetimes() {
  auto memory=account();
  {
    AccountedRowSet rows(memory,MemoryPurpose::delta_state,owner);
    Relation expected;
    {
      const Row original{std::int64_t{-4},std::string("left\0right",10)+std::string(4096,'q'),true,
          Date::parse("2026-11-09"),Decimal::parse("-12345678901234567890123456789012345678")};
      expected.insert(original);check(rows.insert(original).second,"mixed-scalar row insertion failed");
    }
    check(rows.export_rows()==expected,"native row did not own its binary string/decimal bytes");
    const auto original=memory.statistics().current;
    auto handle=rows.extract(rows.begin());
    auto state=memory.statistics();
    check(state.current==original,"extraction changed the actual allocated byte count");
    check(state.by_lifetime[static_cast<std::size_t>(AllocationLifetime::retained)].allocations==2,
        "extracted node and scalar payload were not both classified retained");
    {
      s04_alloc::Scope no_allocation(0);
      check(rows.insert(std::move(handle)).inserted,"native mixed-scalar reinsertion failed");
      check(!rows.insert(*expected.begin()).second,"duplicate row insertion was accepted");
      check(s04_alloc::calls==0,"native reinsertion or duplicate lookup allocated");
    }
    state=memory.statistics();
    check(state.by_lifetime[static_cast<std::size_t>(AllocationLifetime::retained)].allocations==0,
        "reinserted scalar allocation remained classified retained");
    rows.set_lifetime(AllocationLifetime::retained);reconcile(memory);
    check(memory.statistics().by_lifetime[static_cast<std::size_t>(AllocationLifetime::retained)].allocations==2,
        "whole-set lifetime classification missed an actual allocation");
    rows.set_lifetime(AllocationLifetime::active);
  }
  controller_only(memory);
}
void exact_cap_and_faults() {
  std::uint64_t peak=0;
  const Row first{std::string(2048,'x')},second{std::string(4096,'y')};
  {
    auto memory=account();AccountedRowSet rows(memory,MemoryPurpose::delta_state,owner);
    rows.insert(first);rows.insert(second);peak=memory.statistics().peak_requested_bytes;
  }
  {
    auto memory=MemoryAccount::create(peak);
    {AccountedRowSet rows(memory,MemoryPurpose::delta_state,owner);rows.insert(first);rows.insert(second);
      check(memory.statistics().peak_requested_bytes==peak,"exact native node/payload cap was not admitted");}
    controller_only(memory);
  }
  {
    auto memory=MemoryAccount::create(peak-1);
    {
      AccountedRowSet rows(memory,MemoryPurpose::delta_state,owner);rows.insert(first);
      const auto before=memory.statistics().current;
      bool denied=false;
      try{rows.insert(second);}catch(const resource::MemoryFailure& error){denied=error.fault()==resource::MemoryFault::limit;}
      check(denied && memory.statistics().current==before && rows.export_rows()==Relation{first},
          "one-byte denial changed native membership or leaked an allocation");
    }
    controller_only(memory);
  }
  std::size_t failures=0;bool finished=false;
  for(std::ptrdiff_t fail=0;fail<16;++fail) {
    auto memory=account();
    {
      AccountedRowSet rows(memory,MemoryPurpose::delta_state,owner);rows.insert(first);
      const auto before=memory.statistics().current;bool failed=false;
      {
        s04_alloc::Scope fault(fail);
        try{rows.insert(second);}catch(const std::bad_alloc&){failed=true;}
      }
      if(failed) {
        ++failures;check(rows.export_rows()==Relation{first} && memory.statistics().current==before,
            "persistent allocation failure changed the map or leaked scalar/node storage");
        rows.insert(second);check(rows.size()==2,"native insertion could not retry after allocation failure");
      }else finished=true;
      rows.check_invariants();reconcile(memory);
    }
    controller_only(memory);if(finished)break;
  }
  check(finished && failures>=2,"native payload and node allocation failures were not exercised");
}
struct Bucket {
  std::uint64_t value=0;
  AccountedRowSet rows;
  Bucket(const MemoryAccount& memory,MemoryPurpose purpose,MemoryAttribution attribution,AllocationLifetime lifetime)
      :rows(memory,purpose,attribution,lifetime) {}
  Bucket(const MemoryAccount& memory,const Row& initial)
      :rows(memory,MemoryPurpose::delta_state,owner) {rows.insert(initial);value=1;}
  void set_lifetime(AllocationLifetime lifetime){rows.set_lifetime(lifetime);}
};
void nested_ownership() {
  auto memory=account();
  {
    AccountedRowMap<Bucket> rows(memory,MemoryPurpose::delta_state,owner);
    const Row separator=key(42),payload{std::string(3072,'n')};
    rows[separator].rows.insert(payload);rows.find(separator)->second.value=1;
    const auto before=memory.statistics().current;
    auto removed=rows.extract(separator);
    check(memory.statistics().current==before &&
        memory.statistics().by_lifetime[static_cast<std::size_t>(AllocationLifetime::retained)].allocations==4,
        "nested extraction missed the actual outer/inner nodes or scalar payloads");
    {
      s04_alloc::Scope no_allocation(0);check(rows.insert(std::move(removed)).inserted,"nested undo reinsertion failed");
      check(s04_alloc::calls==0,"nested undo reinsertion allocated");
    }
    check(rows.find(separator)->second.rows.export_rows()==Relation{payload},"nested ownership lost its row");
  }
  controller_only(memory);
  bool finished=false;std::size_t failures=0;
  for(std::ptrdiff_t fail=0;fail<16;++fail) {
    {
      AccountedRowMap<Bucket> rows(memory,MemoryPurpose::delta_state,owner);
      const Row separator=key(42),payload{std::string(3072,'n')};const auto before=memory.statistics().current;
      bool failed=false;
      {s04_alloc::Scope fault(fail);try{rows.try_emplace(separator,memory,payload);}catch(const std::bad_alloc&){failed=true;}}
      if(failed) {
        ++failures;check(rows.empty() && memory.statistics().current==before,"nested construction was not failure atomic");
        rows.try_emplace(separator,memory,payload);
      }else finished=true;
      rows.check_invariants();reconcile(memory);
    }
    controller_only(memory);if(finished)break;
  }
  check(finished && failures>=4,"nested allocation failure coverage did not reach every owned allocation");
}
} // namespace
int main() {
  try {
    exhaustive_ordering();random_differential();stable_addresses();scalar_ownership_and_lifetimes();
    exact_cap_and_faults();nested_ownership();
    std::cout<<"native ordered rows: exhaustive/random differential, stable handles, exact caps, persistent faults, lifetimes and cleanup passed\n";
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
