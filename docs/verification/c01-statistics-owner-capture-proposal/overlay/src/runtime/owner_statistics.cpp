#include "owner_statistics_detail.hpp"
#include "crown/api/error.hpp"
#include <limits>
namespace crown::runtime::statistics {
Freshness compare_freshness(const OwnerStamp& old,const OwnerStamp& now,std::uint64_t lag) {
  if(old.owner!=now.owner)return Freshness::foreign_owner;
  if(old.layer!=now.layer)return Freshness::scope_mismatch;
  if(old.sequence>now.sequence)return Freshness::future_sequence;
  if(old.sequence==now.sequence)return Freshness::current;
  return now.sequence-old.sequence<=lag?Freshness::within_lag:Freshness::stale;
}
namespace detail {
namespace {
std::uint64_t product(std::size_t count,std::size_t width) {
  if(count>std::numeric_limits<std::size_t>::max()/width ||
      count>std::numeric_limits<std::uint64_t>::max()/width)throw Exhausted{};
  return static_cast<std::uint64_t>(count)*static_cast<std::uint64_t>(width);
}
}
OwnerBuilder::OwnerBuilder(OwnerStamp stamp,const PhysicalPlan& plan,const OwnerRequest& request,Limits limits,bool pending)
    :request_(request),budget_(limits),output_{stamp,plan,limits,request.selections.size()} {
  if(request.selections.size()>256)throw Error("invalid_statistics_request","at most 256 selections are allowed");
  for(const auto& s:request.selections)
    if(s.fields && s.fields->size()>limits.projection_width)throw Error("invalid_statistics_request","projection width exceeds request limit");
  if(pending){output_.availability_=Availability::pending_private_state;return;}
  try {
    budget_.work();budget_.bytes(sizeof(OwnerCapture));
    budget_.bytes(product(request.selections.size(),sizeof(Component)));
    output_.components_.reserve(request.selections.size());
  }catch(const Exhausted&){output_.availability_=Availability::budget_exhausted;}
}
bool OwnerBuilder::active() const noexcept {return output_.availability_==Availability::available;}
Component* OwnerBuilder::append(const Selection& selection) {
  if(!active())return nullptr;
  try {
    budget_.work();
    if(selection.fields){budget_.work(selection.fields->size());budget_.bytes(product(selection.fields->size(),sizeof(FieldId)));}
    output_.components_.push_back({selection,Availability::available,{},{},{},{},{}});
    return &output_.components_.back();
  }catch(const Exhausted&){output_.availability_=Availability::budget_exhausted;return nullptr;}
}
void OwnerBuilder::table(Component& component,const storage::ReferenceTable& table) {
  component.layout=table.layout();component.cardinality=table.size();
  component.storage_invalidation=Stamp{table.owner(),table.relation(),table.revision()};
  if(!component.selection.fields)return;
  try {
    component.distribution=detail::projected_fields(table,*component.selection.fields,budget_);
    if(component.distribution->completion!=Completion::exact)component.availability=Availability::budget_exhausted;
  }catch(const Exhausted&){component.availability=Availability::budget_exhausted;component.distribution=Distribution{};}
}
void OwnerBuilder::index(Component& component,const storage::ReferenceTable& table,IndexId id) {
  auto captured=statistics::index(table,id,budget_);component.layout=captured.projection->target();
  component.storage_invalidation=captured.stamp;
  component.cardinality=table.key_count(id);component.distribution=std::move(captured.distribution);
  if(component.distribution->completion!=Completion::exact)component.availability=Availability::budget_exhausted;
}
OwnerCapture OwnerBuilder::finish(){
  output_.usage_=budget_.usage();
  if(output_.availability_==Availability::available)
    for(const auto& component:output_.components_)
      if(component.availability==Availability::budget_exhausted){output_.availability_=Availability::budget_exhausted;break;}
  return std::move(output_);
}
}
}
