#pragma once
#include "continuation_machine.hpp"
#include <coroutine>
#include <exception>
#include <utility>

namespace crown::planner::continuation_detail::producer_private {
// Coroutines contain only nonthrowing control flow between suspension points.
// Every allocating operation is a saved closure in its owning coroutine frame,
// executed by Engine::step OUTSIDE resume(). A failed operation leaves the same
// closure pending. Coroutine creation is itself such an operation. No yielding
// comparator is used: map comparisons/allocators and scalar-width costs are
// excluded from the abstract transition count (not a hard CPU-time guarantee).
struct Engine;
struct Task {
  struct promise_type;
  using Handle = std::coroutine_handle<promise_type>;
  Handle handle{};
  Task() noexcept = default;
  explicit Task(Handle h) noexcept : handle(h) {}
  Task(Task&& t) noexcept : handle(std::exchange(t.handle, {})) {}
  Task& operator=(Task&& t) noexcept {
    if (this != &t) { if (handle) handle.destroy(); handle = std::exchange(t.handle, {}); }
    return *this;
  }
  ~Task() { if (handle) handle.destroy(); }
  bool await_ready() const noexcept { return false; }
  void await_suspend(Handle parent) noexcept;
  void await_resume() const noexcept {}
  struct promise_type {
    Engine* engine = nullptr;
    Handle parent{};
    Task* owner = nullptr;
    void* operation = nullptr;
    void (*execute)(void*) = nullptr;
    std::size_t requested_depth = 0;
    Task get_return_object() noexcept { return Task{Handle::from_promise(*this)}; }
    std::suspend_always initial_suspend() noexcept { return {}; }
    struct Finish {
      bool await_ready() const noexcept { return false; }
      void await_suspend(Handle h) const noexcept;
      void await_resume() const noexcept {}
    };
    Finish final_suspend() noexcept { return {}; }
    void return_void() noexcept {}
    // Throwing work must stay in Engine::step; an exception from resumed
    // coroutine control flow is fatal.
    void unhandled_exception() noexcept { std::terminate(); }
  };
};
struct Engine {
  Task::Handle active{};
  std::size_t depth = 0;
  bool administrative_only = false;
  void start(Task& task) noexcept {
    active = task.handle; active.promise().engine = this;
    active.promise().owner = &task; depth = 1;
  }
  // Cancellation is outside advance accounting. Tear down live frames from the
  // leaf upward and detach their owning Task first, avoiding recursive unwind.
  void cancel() noexcept {
    while (active) {
      const auto frame = active;
      active = frame.promise().parent;
      frame.promise().owner->handle = {};
      frame.destroy();
    }
    depth = 0;
  }
  UnitResult step(const UnitContext& context) {
    if (!active) return {};
    auto& p = active.promise();
    if (p.execute) {
      if (!administrative_only && !context.permits(p.requested_depth)) return {UnitEvent::depth_blocked, p.requested_depth};
      p.execute(p.operation); // failure leaves operation and suspension intact
      p.execute = nullptr;
      p.operation = nullptr;
    }
    active.resume(); // all intervening code is allocation-free
    return {};
  }
};
inline void Task::await_suspend(Handle parent) noexcept {
  auto& engine = *parent.promise().engine;
  handle.promise().engine = &engine;
  handle.promise().parent = parent;
  handle.promise().owner = this;
  engine.active = handle;
  ++engine.depth;
}
inline void Task::promise_type::Finish::await_suspend(Handle h) const noexcept {
  auto& engine = *h.promise().engine;
  engine.active = h.promise().parent;
  --engine.depth;
}
template<class F> struct Operation {
  F function;
  std::size_t requested_depth;
  bool await_ready() const noexcept { return false; }
  void await_suspend(Task::Handle h) noexcept {
    h.promise().operation = this;
    h.promise().execute = [](void* p) { static_cast<Operation*>(p)->function(); };
    h.promise().requested_depth = requested_depth;
  }
  void await_resume() const noexcept {}
};
template<class F> auto operation(F f, std::size_t depth = 0) noexcept {
  return Operation<F>{std::move(f), depth};
}
} // namespace crown::planner::continuation_detail::producer_private
