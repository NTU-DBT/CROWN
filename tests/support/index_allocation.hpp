#pragma once

// Single-TU test-executable replacement new/delete, following the native C05
// convention. Never include in a storage library or in multiple linked TUs.
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <new>

namespace s04_alloc {
// Counts covered C++ new attempts only; libc malloc calls and byte/account totals
// are separate. Zero remaining persists until the nonnested Scope is destroyed.
inline thread_local bool enabled = false;
inline thread_local std::ptrdiff_t remaining = -1;
inline thread_local std::size_t calls = 0;
inline thread_local bool triggered = false;
inline void position() {
  if (!enabled) return;
  if (calls == std::numeric_limits<std::size_t>::max()) throw std::bad_alloc{};
  ++calls;
  if (remaining == 0) { triggered = true;throw std::bad_alloc{}; }
  if (remaining > 0) --remaining;
}
[[gnu::noinline]] inline void* allocate(std::size_t size) {
  position();if (auto* value = std::malloc(size ? size : 1)) return value;
  throw std::bad_alloc{};
}
[[gnu::noinline]] inline void* aligned(std::size_t size, std::size_t alignment) {
  position();
  if (size > std::numeric_limits<std::size_t>::max() - (alignment - 1)) throw std::bad_alloc{};
  const auto rounded = ((size ? size : 1) + alignment - 1) / alignment * alignment;
  if (auto* value = std::aligned_alloc(alignment, rounded)) return value;
  throw std::bad_alloc{};
}
[[gnu::noinline]] inline void release(void* value) noexcept { std::free(value); }
class Scope {
 public:
  explicit Scope(std::ptrdiff_t fail_after = -1) noexcept {
    if (enabled) std::terminate();
    remaining = fail_after;calls = 0;triggered = false;enabled = true;
  }
  Scope(const Scope&) = delete;
  Scope& operator=(const Scope&) = delete;
  ~Scope() { enabled = false;remaining = -1; }
};
} // namespace s04_alloc

// No-inline allocation/deallocation seams keep optimized compilers from
// diagnosing the intentional replacement-new malloc/free implementation.
[[gnu::noinline]] void* operator new(std::size_t n) { return s04_alloc::allocate(n); }
[[gnu::noinline]] void* operator new[](std::size_t n) { return s04_alloc::allocate(n); }
[[gnu::noinline]] void* operator new(std::size_t n, const std::nothrow_t&) noexcept { try { return s04_alloc::allocate(n); } catch (...) { return nullptr; } }
[[gnu::noinline]] void* operator new[](std::size_t n, const std::nothrow_t&) noexcept { try { return s04_alloc::allocate(n); } catch (...) { return nullptr; } }
[[gnu::noinline]] void* operator new(std::size_t n, std::align_val_t alignment) { return s04_alloc::aligned(n, static_cast<std::size_t>(alignment)); }
[[gnu::noinline]] void* operator new[](std::size_t n, std::align_val_t alignment) { return s04_alloc::aligned(n, static_cast<std::size_t>(alignment)); }
[[gnu::noinline]] void* operator new(std::size_t n, std::align_val_t alignment, const std::nothrow_t&) noexcept { try { return s04_alloc::aligned(n, static_cast<std::size_t>(alignment)); } catch (...) { return nullptr; } }
[[gnu::noinline]] void* operator new[](std::size_t n, std::align_val_t alignment, const std::nothrow_t&) noexcept { try { return s04_alloc::aligned(n, static_cast<std::size_t>(alignment)); } catch (...) { return nullptr; } }
[[gnu::noinline]] void operator delete(void* p) noexcept { s04_alloc::release(p); }
[[gnu::noinline]] void operator delete[](void* p) noexcept { s04_alloc::release(p); }
[[gnu::noinline]] void operator delete(void* p, std::size_t) noexcept { s04_alloc::release(p); }
[[gnu::noinline]] void operator delete[](void* p, std::size_t) noexcept { s04_alloc::release(p); }
[[gnu::noinline]] void operator delete(void* p, const std::nothrow_t&) noexcept { s04_alloc::release(p); }
[[gnu::noinline]] void operator delete[](void* p, const std::nothrow_t&) noexcept { s04_alloc::release(p); }
[[gnu::noinline]] void operator delete(void* p, std::align_val_t) noexcept { s04_alloc::release(p); }
[[gnu::noinline]] void operator delete[](void* p, std::align_val_t) noexcept { s04_alloc::release(p); }
[[gnu::noinline]] void operator delete(void* p, std::size_t, std::align_val_t) noexcept { s04_alloc::release(p); }
[[gnu::noinline]] void operator delete[](void* p, std::size_t, std::align_val_t) noexcept { s04_alloc::release(p); }
[[gnu::noinline]] void operator delete(void* p, std::align_val_t, const std::nothrow_t&) noexcept { s04_alloc::release(p); }
[[gnu::noinline]] void operator delete[](void* p, std::align_val_t, const std::nothrow_t&) noexcept { s04_alloc::release(p); }
