#pragma once

#include "crown/io/ingest.hpp"
#include "crown/resource/ownership.hpp"
#include "crown/resource/text.hpp"

namespace crown::recovery::detail {struct SessionImageAccess;}

namespace crown::io {
// Native option descriptors share original-account Values on ordinary copy.
// Direct Values copies clone map/text; explicit imports use the receiving account.
// Public InputOptions remains the ordinary caller-owned DTO.
class AccountedInputOptions {
 public:
  struct Values {
    using Tokens=std::map<resource::AccountedText,TableId,resource::AccountedTextLess,
        resource::MemoryAllocator<std::pair<const resource::AccountedText,TableId>>>;
    InputFormat format=InputFormat::jsonl;
    InputLimits limits;
    std::optional<TableId> table;
    char delimiter=',';
    bool header=true;
    SetOperation csv_operation=SetOperation::insert;
    Tokens relation_tokens;
    std::optional<resource::AccountedText> null_token,source;
    std::uint64_t byte_offset=0;
    Values()=default;
    explicit Values(const resource::MemoryAccount&);
    Values(const resource::MemoryAccount&,const InputOptions&);
    Values(const resource::MemoryAccount&,const Values&);
  };
  AccountedInputOptions() noexcept=default;
  AccountedInputOptions(const resource::MemoryAccount&,const InputOptions&);
  AccountedInputOptions(const resource::MemoryAccount&,const AccountedInputOptions&);
  [[nodiscard]] const Values& get() const noexcept;
  [[nodiscard]] const resource::MemoryAccount& account() const noexcept {return account_;}
  [[nodiscard]] InputOptions export_value() const;
  [[nodiscard]] bool same_values(const AccountedInputOptions&) const noexcept;
 private:
  friend struct recovery::detail::SessionImageAccess;
  AccountedInputOptions(const resource::MemoryAccount&,Values&&);
  resource::MemoryAccount account_;
  std::shared_ptr<const Values> values_;
};
} // namespace crown::io
