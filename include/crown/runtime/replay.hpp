#pragma once

#include "crown/io/ingest.hpp"
#include "crown/runtime/delta.hpp"

namespace crown::runtime {
// One ordered source reader binds to one runtime owner on first application.
// Progress advances only after atomic engine commit, with no throwing input
// bookkeeping after publication. Output retry is separate from input retry.
class OrderedReplay {
 public:
  explicit OrderedReplay(io::EventReader reader);
  ~OrderedReplay();
  OrderedReplay(const OrderedReplay&)=delete;
  OrderedReplay& operator=(const OrderedReplay&)=delete;
  OrderedReplay(OrderedReplay&&) noexcept;
  OrderedReplay& operator=(OrderedReplay&&) noexcept;
  [[nodiscard]] const io::InputEventView* peek();
  [[nodiscard]] const io::AccountedInputProgress& progress() const;
  [[nodiscard]] bool failed() const noexcept;
  [[nodiscard]] std::optional<PhysicalEpoch> apply_next(PhysicalRuntime& runtime);
  [[nodiscard]] std::optional<DeltaRuntime::Epoch> apply_next(DeltaRuntime& runtime);
 private:
  struct Data;
  resource::AccountedUnique<Data> data_;
};
}  // namespace crown::runtime
