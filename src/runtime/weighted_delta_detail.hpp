#pragma once
#include "weighted_detail.hpp"
#include <algorithm>
#include <type_traits>

namespace crown::runtime::weighted {
// Mutable only inside one pending token; the index borrows stable owned row
// payloads, not vector element addresses. Commit drops it before publishing.
struct BagDeltas::Data {
  struct Less {
    Data* owner;
    bool operator()(storage::RowView a, storage::RowView b) const { return owner->compare(a,b)<0; }
  };
  using Entries=weighted_detail::Vector<BagDelta>;
  using Index=std::map<storage::RowView,std::size_t,Less,
      resource::MemoryAllocator<std::pair<const storage::RowView,std::size_t>>>;
  annotations::MultiplicityPolicy policy;
  std::uint64_t* epoch_work;
  std::optional<std::uint64_t> limit;
  BagDeltaMetrics metrics;
  Entries rows; // Declared first: borrowed index keys die before owned payloads.
  Index index;
  Data(const resource::MemoryAccount& account, annotations::MultiplicityPolicy counts,
      std::uint64_t& work, std::optional<std::uint64_t> ceiling)
      :policy(counts),epoch_work(&work),limit(ceiling),
       rows(resource::MemoryAllocator<BagDelta>(account,resource::MemoryPurpose::output_buffer)),
       index(Less{this},Index::allocator_type(account,resource::MemoryPurpose::delta_state)) {}
  void charge(std::uint64_t amount=1, std::uint64_t* counter=nullptr) {
    weighted_detail::require(epoch_work && amount<=UINT64_MAX-*epoch_work &&
        (!limit || (*epoch_work<=*limit && amount<=*limit-*epoch_work)),
        "resource_limit","weighted bag delta work exhausted");
    *epoch_work+=amount;metrics.work+=amount;if(counter)*counter+=amount;
  }
  void bytes(const storage::ScalarView& cell) {
    if (const auto* text=std::get_if<std::string_view>(&cell))
      charge(static_cast<std::uint64_t>(text->size()),&metrics.scalar_bytes);
  }
  int cell(const storage::ScalarView& a, const storage::ScalarView& b) {
    charge(1,&metrics.fields);
    if (a.index()!=b.index()) return a.index()<b.index()?-1:1;
    if (const auto* left=std::get_if<std::string_view>(&a)) {
      const auto right=std::get<std::string_view>(b);
      const auto size=std::min(left->size(),right.size());
      for (std::size_t i=0;i<size;++i) {
        charge(1,&metrics.scalar_bytes);
        const auto x=static_cast<unsigned char>((*left)[i]),y=static_cast<unsigned char>(right[i]);
        if(x!=y)return x<y?-1:1;
      }
      return left->size()<right.size()?-1:left->size()!=right.size()?1:0;
    }
    const auto order=a<=>b;return order<0?-1:order>0?1:0;
  }
  int compare(storage::RowView a, storage::RowView b) {
    charge(1,&metrics.comparisons);
    for(std::size_t i=0;i<std::min(a.size(),b.size());++i)
      if(const auto order=cell(a[i],b[i]);order)return order;
    return a.size()<b.size()?-1:a.size()!=b.size()?1:0;
  }
  SignedMagnitude merge(SignedMagnitude a, SignedMagnitude b) {
    charge();
    if(a.negative==b.negative)return {a.negative,policy.add(a.magnitude,b.magnitude)};
    if(a.magnitude>=b.magnitude)return {a.negative,{a.magnitude.value-b.magnitude.value}};
    return {b.negative,{b.magnitude.value-a.magnitude.value}};
  }
  void add(const storage::AccountedLayout& layout, storage::RowView row, SignedMagnitude term) {
    charge(1,&metrics.terms);
    const auto found=index.find(row); // Probe borrowed projection before any owning copy.
    if(found!=index.end()) {
      const auto slot=found->second;const auto next=merge(rows[slot].change,term);
      charge(1,&metrics.mutations);
      if(next.magnitude.present()) {rows[slot].change=next;return;}
      const auto last=rows.size()-1;
      const auto moved=slot==last?index.end():index.find(rows[last].tuple.values());
      if(slot!=last) {
        weighted_detail::require(moved!=index.end(),"weighted_contract","delta index lost its owned row");
        moved->second=slot;
      }
      index.erase(found);
      if(slot!=last)rows[slot]=std::move(rows[last]);
      rows.pop_back();return;
    }
    static_assert(std::is_nothrow_move_constructible_v<BagDelta> && std::is_nothrow_move_assignable_v<BagDelta>);
    if(rows.size()==rows.capacity()) {
      charge(static_cast<std::uint64_t>(rows.size())); // Actual relocated handles.
      const auto capacity=rows.capacity();
      weighted_detail::require(capacity<=rows.max_size()/2,"resource_limit","delta capacity exhausted");
      rows.reserve(capacity?capacity*2:1);
    }
    // Only a new net key freezes scalar descriptors and string bytes.
    for(const auto& value:row.cells()) {charge(1,&metrics.fields);bytes(value);}
    auto tuple=layout.tuple(row,{resource::MemoryOwnerKind::output,0});
    charge(2,&metrics.mutations); // Insert plus its one eventual index-node release.
    index.emplace(tuple.values(),rows.size());
    rows.push_back({std::move(tuple),term}); // Reserved capacity; only no-throw moves.
  }
  void publish() noexcept {
    index.clear(); // Each node's release was funded at insertion; compares no keys.
    epoch_work=nullptr;
  }
};
} // namespace crown::runtime::weighted
