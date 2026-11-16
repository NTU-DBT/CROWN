#include "crown/io/input_options.hpp"
#include "crown/io/input_progress.hpp"

namespace crown::io {
AccountedInputOptions::Values::Values(const resource::MemoryAccount& account)
    :relation_tokens(resource::AccountedTextLess{},Tokens::allocator_type(
        account,resource::MemoryPurpose::immutable_metadata,input_detail::memory_owner)) {}
// Friend codec passes freshly prepared nested allocations under this same account.
AccountedInputOptions::AccountedInputOptions(const resource::MemoryAccount& account,Values&& input)
    :account_(account),values_(resource::make_accounted_shared<Values>(input_detail::memory_owner,account,
        resource::MemoryPurpose::immutable_metadata,std::move(input))) {}
AccountedInputOptions::Values::Values(const resource::MemoryAccount& account,const InputOptions& input)
    :format(input.format),limits(input.limits),table(input.table),delimiter(input.delimiter),header(input.header),
     csv_operation(input.csv_operation),relation_tokens(resource::AccountedTextLess{},Tokens::allocator_type(
         account,resource::MemoryPurpose::immutable_metadata,input_detail::memory_owner)),byte_offset(input.byte_offset) {
  for(const auto& [name,id]:input.relation_tokens)
    relation_tokens.emplace(resource::AccountedText::copy_of(account,name,input_detail::memory_owner),id);
  if(input.null_token)null_token=resource::AccountedText::copy_of(account,*input.null_token,input_detail::memory_owner);
  if(input.source)source=resource::AccountedText::copy_of(account,*input.source,input_detail::memory_owner);
}
AccountedInputOptions::AccountedInputOptions(const resource::MemoryAccount& account,const InputOptions& input)
    :account_(account),values_(resource::make_accounted_shared<Values>(input_detail::memory_owner,account,
        resource::MemoryPurpose::immutable_metadata,account,input)) {}
AccountedInputOptions::Values::Values(const resource::MemoryAccount& account,const Values& input)
    :format(input.format),limits(input.limits),table(input.table),delimiter(input.delimiter),header(input.header),
     csv_operation(input.csv_operation),relation_tokens(resource::AccountedTextLess{},Tokens::allocator_type(
         account,resource::MemoryPurpose::immutable_metadata,input_detail::memory_owner)),byte_offset(input.byte_offset) {
  for(const auto& [name,id]:input.relation_tokens)
    relation_tokens.emplace(resource::AccountedText::copy_of(account,name.view(),input_detail::memory_owner),id);
  if(input.null_token)null_token=resource::AccountedText::copy_of(account,input.null_token->view(),input_detail::memory_owner);
  if(input.source)source=resource::AccountedText::copy_of(account,input.source->view(),input_detail::memory_owner);
}
AccountedInputOptions::AccountedInputOptions(const resource::MemoryAccount& account,const AccountedInputOptions& input)
    :account_(account),values_(resource::make_accounted_shared<Values>(input_detail::memory_owner,account,
        resource::MemoryPurpose::immutable_metadata,account,input.get())) {}
const AccountedInputOptions::Values& AccountedInputOptions::get() const noexcept {
  static const Values empty;return values_?*values_:empty;
}
// Explicit ordinary DTO export; retained native map/text ownership stays separate.
InputOptions AccountedInputOptions::export_value() const {
  const auto& value=get();InputOptions result;
  result.format=value.format;result.limits=value.limits;result.table=value.table;result.delimiter=value.delimiter;
  result.header=value.header;result.csv_operation=value.csv_operation;result.byte_offset=value.byte_offset;
  for(const auto& [name,id]:value.relation_tokens)result.relation_tokens.emplace(std::string(name.view()),id);
  if(value.null_token)result.null_token=std::string(value.null_token->view());
  if(value.source)result.source=std::string(value.source->view());
  return result;
}
bool AccountedInputOptions::same_values(const AccountedInputOptions& other) const noexcept {
  const auto& a=get();const auto& b=other.get();
  return a.format==b.format && a.limits==b.limits && a.table==b.table && a.delimiter==b.delimiter && a.header==b.header &&
      a.csv_operation==b.csv_operation && a.relation_tokens==b.relation_tokens && a.null_token==b.null_token &&
      a.source==b.source && a.byte_offset==b.byte_offset;
}
} // namespace crown::io
