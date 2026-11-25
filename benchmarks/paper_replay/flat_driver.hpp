#pragma once
// Shared glue for running the paper harnesses on runtime::FlatRuntime
// (CROWN_ENGINE=flat). Rows are counted in a C callback; verify mode decodes
// and captures them exactly like the reference path.
#include "crown/runtime/flat.hpp"
#include "crown/runtime/flat_cyclic.hpp"
#include <crown/io/document.hpp>
#include "crown/storage/keyed.hpp"
#include <cstdlib>
#include <fstream>
#include <functional>
#include <limits>
#include <stdexcept>
#include <optional>
#include <string>
#include <vector>

namespace {
// CROWN_GC=background: the keyed core frees garbage on one collector thread
// (two threads in all); otherwise blocking: single-threaded, collecting when
// the retired-memory pool is full or the engine budget would be exceeded.
// CROWN_GC_POOL sets the blocking-mode retired-memory pool: bytes with an
// optional K/M/G/T suffix (powers of 1024), or "unlimited" (collect only when
// the engine budget would be exceeded). Default 64M.
inline crown::storage::keyed::GcOptions paper_gc_options() {
  crown::storage::keyed::GcOptions options;
  const char* mode = std::getenv("CROWN_GC");
  if (mode && std::string(mode) == "background") options.mode = crown::storage::keyed::GcMode::background;
  else if (mode && std::string(mode) != "blocking") throw std::runtime_error("CROWN_GC must be blocking or background");
  if (const char* pool = std::getenv("CROWN_GC_POOL")) {
    const std::string text(pool);
    if (text == "unlimited") {
      options.retired_bytes = std::numeric_limits<std::size_t>::max();
    } else {
      std::size_t used = 0;
      const auto value = std::stoull(text, &used);
      const std::string unit = text.substr(used);
      const int shift = unit.empty() ? 0 : unit == "K" ? 10 : unit == "M" ? 20 : unit == "G" ? 30 : unit == "T" ? 40 : -1;
      if (shift < 0 || value > (std::numeric_limits<std::size_t>::max() >> shift))
        throw std::runtime_error("CROWN_GC_POOL must be a size like 64M, 4G or unlimited");
      options.retired_bytes = static_cast<std::size_t>(value) << shift;
    }
  }
  return options;
}
// GC report fields: options and process-wide totals at the end of the loop.
inline crown::io::Json paper_gc_report(const crown::storage::keyed::GcOptions& options) {
  const auto s = crown::storage::keyed::process_gc_statistics();
  return {{"mode", crown::storage::keyed::gc_mode_name(options.mode)}, {"pool_bytes", options.retired_bytes},
          {"collections", s.collections}, {"retired_bytes", s.retired_bytes}, {"freed_bytes", s.freed_bytes},
          {"pending_bytes", s.pending_bytes}};
}
// Threads of this process now (from /proc/self/status).
inline std::int64_t process_threads() {
  std::ifstream status("/proc/self/status");
  std::string line;
  while (std::getline(status, line))
    if (line.rfind("Threads:", 0) == 0) return std::stoll(line.substr(8));
  return -1;
}
inline bool flat_engine_requested() {
  const char* engine = std::getenv("CROWN_ENGINE");
  return engine && std::string(engine) == "flat";
}
struct FlatCounter {
  const crown::runtime::FlatRuntime* owner = nullptr;
  const crown::runtime::FlatCyclicRuntime* cyclic = nullptr;
  std::uint64_t rows = 0, candidates = 0;
  std::optional<std::pair<std::size_t, std::size_t>> not_equal;  // SNB full-head filter
  std::function<void(crown::SetOperation, crown::io::Json)> capture;  // verify mode only
  static void row(void* context, crown::SetOperation operation, const std::int64_t* values, std::size_t size) {
    auto& self = *static_cast<FlatCounter*>(context);
    ++self.candidates;
    if (self.not_equal && values[self.not_equal->first] == values[self.not_equal->second]) return;
    ++self.rows;
    if (self.capture) {
      auto cells = crown::io::Json::array();
      for (std::size_t i = 0; i < size; ++i)
        cells.push_back(crown::io::write_scalar(self.owner ? self.owner->decode(i, values[i]) : self.cyclic->decode(i, values[i])));
      self.capture(operation, std::move(cells));
    }
  }
  crown::runtime::FlatSink sink() { return {this, &FlatCounter::row}; }
};
inline crown::runtime::FlatSink flat_sink(const crown::runtime::FlatCyclicRuntime& owner, FlatCounter& counter) {
  counter.cyclic = &owner;
  return counter.sink();
}
inline void flat_snapshot(const crown::runtime::FlatCyclicRuntime& owner, FlatCounter& counter) {
  owner.snapshot(flat_sink(owner, counter));
}
}  // namespace
