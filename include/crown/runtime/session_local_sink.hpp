#pragma once
#include "crown/runtime/session_journal.hpp"
#include "crown/recovery/local_sink.hpp"
namespace crown::runtime {
struct SessionLocalSinkOptions {
  std::array<char,32> sink_id{};
  recovery::sink::Limits file;
  std::uint64_t delivery_work=512*1024*1024;
  bool repair_torn_tail=true;
};
struct SessionLocalSinkState {
  bool enabled=false,recovery_required=false,replaying=false;
  std::uint64_t verified_sequence=0;
  std::uint64_t delivery_work=0;
  std::uint64_t blocked_inputs=0;
  recovery::sink::State persisted;
  // Describes an authenticated checkpoint-prefix basis. Current delivery,
  // health and quiescence still gate retirement; this report grants no authority.
  bool retirement_verified=false;
};
enum class LocalDeliveryKind :std::uint8_t {idle,published,duplicate};
struct LocalDelivery {
  LocalDeliveryKind kind=LocalDeliveryKind::idle;
  std::uint64_t generation=0,sequence=0;
  std::size_t rows=0;
};
} // namespace crown::runtime
