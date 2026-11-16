#pragma once

#include <nlohmann/json.hpp>
#include <array>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <limits>
#include <set>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <utility>
#include <vector>

// Cold transport and observation helpers for the optional B04 applications.
// None of these objects belongs to native query state or a paper cost model.
namespace component {
using Json = nlohmann::json;
using Clock = std::chrono::steady_clock;
using U64 = std::uint64_t;
inline void require(bool condition, const char* message) {
  if (!condition) throw std::runtime_error(message);
}
inline U64 elapsed(Clock::time_point first, Clock::time_point last) {
  const auto value = std::chrono::duration_cast<std::chrono::nanoseconds>(last-first).count();
  require(value >= 0, "component clock regressed");
  return static_cast<U64>(value);
}
inline U64 number(const Json& value, U64 maximum = UINT64_MAX) {
  require(value.is_number_integer() && (value.is_number_unsigned() || value.get<std::int64_t>() >= 0),
      "expected a nonnegative integer");
  const auto result = value.get<U64>();
  require(result <= maximum, "component request integer exceeds limit");
  return result;
}
struct Event {
  std::string operation, table, phase;
  std::array<std::int64_t, 2> values;
};
struct Request {
  Json document;
  std::vector<Event> events;
  bool verify;
  std::size_t warmups, repetitions;
  U64 max_records, max_bytes;
};

// Admit the complete unit-weight trace once, before query/API timing. This
// temporary set is discarded on return; no measurement-side row ledger remains.
inline Request read_request(int argc, char** argv) {
  require(argc == 2, "usage: component_driver REQUEST.json");
  std::ifstream input(argv[1], std::ios::binary);
  require(bool(input), "cannot open component request");
  std::string text; char buffer[4096];
  while (input) {
    input.read(buffer, sizeof(buffer));
    const auto count = static_cast<std::size_t>(input.gcount());
    require(count <= 64U*1024U*1024U-text.size(), "component request exceeds 64MiB");
    text.append(buffer, count);
  }
  require(!input.bad(), "component request read failed");
  auto data = Json::parse(text);
  require(data.at("schema_version").is_number_integer() && data.at("schema_version") == 1,
      "unknown component request version");
  const auto command = data.at("command").get<std::string>();
  require(command == "verify" || command == "measure", "unknown component command");
  const auto& limits = data.at("limits");
  const auto maximum = number(limits.at("input_events"), 1000000);
  const auto records = number(limits.at("output_records"));
  const auto bytes = number(limits.at("output_bytes"));
  Request result{std::move(data), {}, command == "verify", 0, 0,
      records, bytes};
  result.warmups = number(result.document.at("warmup_passes"), 100);
  result.repetitions = number(result.document.at("measured_passes"), 100);
  require(result.repetitions > 0, "component request needs a measured pass");
  const auto& events = result.document.at("events");
  require(events.is_array() && events.size() <= maximum, "component event limit exceeded");
  result.events.reserve(events.size());
  std::set<std::pair<std::string, std::array<std::int64_t, 2>>> live;
  for (const auto& row : events) {
    Event event{row.at("operation").get<std::string>(), row.at("table").get<std::string>(),
        row.value("phase", "updates"), {}};
    const auto& values = row.at("values");
    require(values.is_array() && values.size() == 2, "component inputs are integer pairs");
    for (std::size_t i=0; i<2; ++i) {
      require(values[i].is_number_integer(), "component input is not an integer");
      if (values[i].is_number_unsigned())
        require(values[i].get<U64>() <= INT64_MAX, "component input exceeds int64");
      event.values[i] = values[i].get<std::int64_t>();
    }
    const auto key = std::make_pair(event.table, event.values);
    if (event.operation == "+") require(live.insert(key).second, "duplicate component insertion");
    else {
      require(event.operation == "-", "component operation must be + or -");
      require(live.erase(key) == 1, "absent component deletion");
    }
    result.events.push_back(std::move(event));
  }
  return result;
}
inline Json time_value(const Request& request, U64 value) {
  return request.verify ? Json(nullptr) : Json(value);
}
inline void add_records(U64& total, U64 amount, U64 maximum) {
  require(amount <= maximum-total, "component output-record limit exceeded");
  total += amount;
}

// Legacy formatting writes into this bounded sink inside its genuine API call.
// Measurement counts bytes/newlines without retaining text. Verification owns
// only the current event's raw frame, exported after the call has completed.
class TextSink : public std::streambuf {
  bool capture_;
  U64 maximum_;
  std::string frame_;
 public:
  U64 bytes = 0, records = 0;
  TextSink(bool capture, U64 maximum) : capture_(capture), maximum_(maximum) {}
  void next_frame() { frame_.clear(); }
  [[nodiscard]] const std::string& frame() const { return frame_; }
 protected:
  std::streamsize xsputn(const char* text, std::streamsize length) override {
    require(length >= 0, "negative component stream write");
    const auto count = static_cast<U64>(length);
    require(count <= maximum_-bytes, "component output-byte limit exceeded");
    if (capture_) frame_.append(text, static_cast<std::size_t>(count));
    for (std::streamsize i=0; i<length; ++i) if (text[i] == '\n') ++records;
    bytes += count; return length;
  }
  int_type overflow(int_type value) override {
    if (traits_type::eq_int_type(value, traits_type::eof())) return traits_type::not_eof(value);
    const char character = traits_type::to_char_type(value);
    xsputn(&character, 1); return value;
  }
};
}  // namespace component
