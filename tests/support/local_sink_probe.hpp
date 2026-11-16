#pragma once
#include "crown/recovery/local_sink.hpp"
#include <limits>
namespace crown::recovery::sink::testing {
// Private syscall observations; after-hook decisions are ignored.
struct Event {Stage stage;bool after;std::uint64_t ordinal;std::size_t requested;std::int64_t result;int native_error;};
struct Decision {int error_before=0,error_after=0;std::size_t maximum_transfer=std::numeric_limits<std::size_t>::max();bool zero_entropy=false;};
// Borrowed thread-local context; caller clears the hook before destroying it.
using Hook=Decision(*)(const Event&,void*) noexcept;
void set_hook(Hook,void*) noexcept;
} // namespace crown::recovery::sink::testing
