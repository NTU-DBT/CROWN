#include "crown/runtime/queries.hpp"
#include "crown/api/error.hpp"
#include <limits>
#include <type_traits>

namespace crown::runtime {
static_assert(std::is_nothrow_move_assignable_v<QuerySession::Owner::deleter_type>);
namespace {
// Both const inspection and mutable dispatch perform one ordered lookup.
auto find_entry(auto& entries,std::uint64_t directory,QueryId id) {
  if (id.directory != directory)
    throw Error("query_id","query ID belongs to another directory");
  const auto position = entries.find(id.value);
  if (position == entries.end())
    throw Error("query_id","query ID is absent or has been removed");
  return position;
}
} // namespace

IndependentQueries::IndependentQueries(QueryDirectoryLimits limits)
    : account_(resource::MemoryAccount::create(limits.memory_bytes)),
      entries_(std::less<std::uint64_t>{},resource::MemoryAllocator<Entry>(
          account_,resource::MemoryPurpose::directory)),
      limits_(limits),directory_(account_.statistics().owner) {}

QueryId IndependentQueries::admit(QuerySession::Owner& session) & {
  if (!session) throw Error("query_owner","query admission needs an owning Session");
  if (entries_.size() >= limits_.queries)
    throw Error("query_limit","live query count limit reached");
  if (next_ == std::numeric_limits<std::uint64_t>::max())
    throw Error("query_id_overflow","query ID history is exhausted");
  // Only this node allocation can fail. Numeric comparison and the subsequent
  // unique-owner move do not allocate or invoke a caller callback.
  const auto position = entries_.try_emplace(next_).first;
  position->second = std::move(session);
  return {directory_,next_++};
}

bool IndependentQueries::contains(QueryId id) const noexcept {
  return id.directory == directory_ && entries_.find(id.value) != entries_.end();
}
resource::MemoryStatistics IndependentQueries::directory_memory() const {
  return account_.statistics();
}
QuerySession& IndependentQueries::at(QueryId id) & {
  return *find_entry(entries_,directory_,id)->second;
}
const QuerySession& IndependentQueries::at(QueryId id) const & {
  return *find_entry(entries_,directory_,id)->second;
}
QuerySession::Owner IndependentQueries::release(QueryId id) & {
  const auto position = find_entry(entries_,directory_,id);
  auto result = std::move(position->second);
  entries_.erase(position);
  return result;
}
void IndependentQueries::erase(QueryId id) & {
  entries_.erase(find_entry(entries_,directory_,id));
}
} // namespace crown::runtime
