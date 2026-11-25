#include "crown/io/input_progress.hpp"
#include "crown/io/ingest.hpp"
#include <exception>
#include <stdexcept>

namespace crown::io {
struct InputPositions::Data {
  resource::MemoryAccount account;
  Map values;
  explicit Data(const resource::MemoryAccount& memory)
      :account(memory),values(resource::AccountedTextLess{},Map::allocator_type(
          account,resource::MemoryPurpose::support_metadata,input_detail::memory_owner)) {}
  Data(const Data& source):account(source.account),values(source.values) {}
};
InputPositions::InputPositions() noexcept=default;
InputPositions::InputPositions(const resource::MemoryAccount& account)
    :data_(resource::make_accounted_unique<Data>(input_detail::memory_owner,account,
        resource::MemoryPurpose::support_metadata,account)) {}
InputPositions::~InputPositions()=default;
InputPositions::InputPositions(InputPositions&&) noexcept=default;
InputPositions& InputPositions::operator=(InputPositions&&) noexcept=default;
InputPositions::InputPositions(const InputPositions& source) {
  if(source.data_)data_=resource::make_accounted_unique<Data>(input_detail::memory_owner,source.data_->account,
      resource::MemoryPurpose::support_metadata,*source.data_);
}
InputPositions& InputPositions::operator=(const InputPositions& source) {
  if(this!=&source){InputPositions copy(source);*this=std::move(copy);}return *this;
}
std::size_t InputPositions::size() const noexcept {return data_?data_->values.size():0;}
InputPositions::const_iterator InputPositions::begin() const noexcept {
  if(data_)return data_->values.begin();
  static const Map empty;
  return empty.begin();
}
InputPositions::const_iterator InputPositions::end() const noexcept {
  if(data_)return data_->values.end();
  // Use the same empty range sentinel as begin(), without allocating a node.
  return begin();
}
InputPositions::const_iterator InputPositions::find(std::string_view name) const {
  return data_?data_->values.find(name):end();
}
const std::uint64_t& InputPositions::at(std::string_view name) const {
  const auto found=find(name);if(found==end())throw std::out_of_range("input source position is absent");return found->second;
}
InputPositions::Prepared InputPositions::prepare(std::string_view name,std::uint64_t offset) {
  // The source owner checks ordering/counts first; only detached storage is prepared here.
  if(!data_)throw resource::MemoryFailure(resource::MemoryFault::contract);
  Prepared prepared;prepared.offset_=offset;
  const auto found=data_->values.find(name);
  if(found!=data_->values.end()) {prepared.existing_=found;prepared.existing=true;return prepared;}
  Map nodes(data_->values.key_comp(),data_->values.get_allocator());
  const auto node=nodes.emplace(resource::AccountedText::copy_of(data_->account,name,input_detail::memory_owner),offset);
  prepared.node_=nodes.extract(node.first);return prepared;
}
void InputPositions::publish(Prepared& prepared) noexcept {
  // Link funded storage after commit; new-name insertion still performs tree comparisons.
  if(!data_)std::terminate();
  if(prepared.node_) {
    if(!data_->values.insert(std::move(prepared.node_)).inserted)std::terminate();
  }else if(prepared.existing)prepared.existing_->second=prepared.offset_;
}
bool InputPositions::operator==(const std::map<std::string,std::uint64_t>& other) const {
  if(size()!=other.size())return false;
  auto expected=other.begin();
  for(const auto& [name,offset]:*this) {
    if(name.view()!=expected->first || offset!=expected->second)return false;
    ++expected;
  }
  return true;
}
AccountedInputProgress::AccountedInputProgress(const resource::MemoryAccount& account,const InputProgress& source)
    :sequence(source.sequence),source_positions(account) {
  for(const auto& [name,offset]:source.source_positions) {
    auto prepared=source_positions.prepare(name,offset);source_positions.publish(prepared);
  }
}
bool AccountedInputProgress::operator==(const InputProgress& other) const {
  return sequence==other.sequence && source_positions==other.source_positions;
}
AccountedInputProgress::AccountedInputProgress(const resource::MemoryAccount& account,const AccountedInputProgress& source)
    :sequence(source.sequence),source_positions(account) {
  for(const auto& [name,offset]:source.source_positions) {
    auto prepared=source_positions.prepare(name.view(),offset);source_positions.publish(prepared);
  }
}
InputProgress AccountedInputProgress::export_value() const {
  InputProgress result;result.sequence=sequence;
  for(const auto& [name,offset]:source_positions)result.source_positions.emplace(std::string(name.view()),offset);
  return result;
}
} // namespace crown::io
