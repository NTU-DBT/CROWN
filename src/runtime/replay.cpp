#include "crown/runtime/replay.hpp"

#include "crown/api/error.hpp"
#include <type_traits>
#include <utility>

namespace crown::runtime {
struct OrderedReplay::Data {
  io::EventReader reader;
  std::optional<SupportOwnerId> owner;
  explicit Data(io::EventReader input):reader(std::move(input)) {}
  // Bind on the first prepared event, before engine apply; rejection retries
  // that cached event on this same owner without acknowledging input progress.
  template<class Runtime> const io::InputEventView* prepare(Runtime& runtime) {
    if (owner && *owner!=runtime.owner())
      throw Error("invalid_replay_owner","an ordered source cannot switch runtime owners");
    if (!runtime.ready()) throw Error("runtime_busy","finish pending input/read/output ownership before replaying another event");
    if (reader.progress().sequence!=runtime.sequence())
      throw Error("invalid_sequence","source progress differs from the runtime's last committed sequence");
    if (!owner && !reader.matches_catalog(runtime.plan()))
      throw Error("catalog_mismatch","physical reader catalog differs from runtime source catalog");
    const auto* event=reader.peek();
    if (event) owner=runtime.owner();
    return event;
  }
};
OrderedReplay::OrderedReplay(io::EventReader reader) {
  const auto account=reader.account();
  data_=resource::make_accounted_unique<Data>(io::input_detail::memory_owner,account,
      resource::MemoryPurpose::support_metadata,std::move(reader));
}
OrderedReplay::~OrderedReplay()=default;
OrderedReplay::OrderedReplay(OrderedReplay&&) noexcept=default;
OrderedReplay& OrderedReplay::operator=(OrderedReplay&&) noexcept=default;
const io::InputEventView* OrderedReplay::peek() {
  if (!data_) throw Error("invalid_input_reader","moved-from ordered input replay");
  return data_->reader.peek();
}
const io::AccountedInputProgress& OrderedReplay::progress() const {
  if (!data_) throw Error("invalid_input_reader","moved-from ordered input replay");
  return data_->reader.progress();
}
bool OrderedReplay::failed() const noexcept { return data_ && data_->reader.failed(); }
std::optional<PhysicalEpoch> OrderedReplay::apply_next(PhysicalRuntime& runtime) {
  if (!data_) throw Error("invalid_input_reader","moved-from ordered input replay");
  const auto* event=data_->prepare(runtime); if (!event) return {};
  auto epoch=runtime.apply_view(event->update);
  // Sequence/source map changes were prepared by peek before engine work.
  // No throwing bookkeeping or user callbacks follows engine publication.
  data_->reader.acknowledge();
  static_assert(std::is_nothrow_move_constructible_v<PhysicalEpoch>);
  return std::optional<PhysicalEpoch>{std::move(epoch)};
}
std::optional<DeltaRuntime::Epoch> OrderedReplay::apply_next(DeltaRuntime& runtime) {
  if (!data_) throw Error("invalid_input_reader","moved-from ordered input replay");
  const auto* event=data_->prepare(runtime); if (!event) return {};
  auto epoch=runtime.apply_view(event->update); data_->reader.acknowledge();
  static_assert(std::is_nothrow_move_constructible_v<DeltaRuntime::Epoch>);
  return std::optional<DeltaRuntime::Epoch>{std::move(epoch)};
}
}  // namespace crown::runtime
