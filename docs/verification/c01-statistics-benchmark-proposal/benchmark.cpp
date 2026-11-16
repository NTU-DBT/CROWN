#include "statistics_collection.hpp"

#include <algorithm>
#include <array>
#include <charconv>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string_view>
#include <system_error>
#include <vector>

namespace collection = crown::runtime::statistics_collection;
using U64 = std::uint64_t;

namespace {
constexpr std::size_t row_count = 96;
constexpr std::size_t group_count = 8;
constexpr std::size_t maximum_aliases = 4;
constexpr std::size_t maximum_parents = 4;
constexpr std::size_t default_event_count = 50000;
constexpr std::size_t default_warmups = 2;
constexpr std::size_t default_repetitions = 9;
constexpr U64 default_seed = 2026110701ULL;
constexpr U64 fnv_offset = 14695981039346656037ULL;
constexpr U64 fnv_prime = 1099511628211ULL;
constexpr std::string_view build_flags =
    "-std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG -O3";

enum class Profile { no_calls, off_calls, census, sampled };
enum class Reason { changed, duplicate_insert, absent_erase };

struct Event {
  std::uint8_t row{};
  bool insert{};
  std::uint8_t group{};
  std::uint8_t alias_count{};
  std::array<std::uint8_t, maximum_aliases> alias_offsets{};
  std::uint8_t parent_count{};
  std::array<std::uint8_t, maximum_parents> parent_degrees{};
};

struct Row {
  bool present{};
  std::uint8_t group{};
};

struct LogicalResult {
  U64 inputs{};
  U64 changed{};
  U64 noops{};
  U64 duplicate_inserts{};
  U64 absent_erases{};
  U64 occurrence_visits{};
  U64 occurrence_accepted{};
  U64 occurrence_rejected{};
  std::array<U64, group_count> final_group_rows{};
  U64 state_checksum{};
  U64 trace_checksum{};
  bool operator==(const LogicalResult&) const = default;
};

struct ProfileReport {
  std::string_view name{};
  std::string_view collector_mode{"none"};
  U64 sample_period{};
  U64 sample_offset{};
  U64 detail_budget{};
  std::size_t max_cells{};
  std::size_t descriptor_count{};
  std::vector<U64> raw_nanoseconds{};
  LogicalResult logical{};
  collection::Metadata metadata{};
  collection::Memory memory{};
};

U64 next_random(U64& state) noexcept {
  state += 0x9E3779B97F4A7C15ULL;
  U64 value = state;
  value = (value ^ (value >> 30U)) * 0xBF58476D1CE4E5B9ULL;
  value = (value ^ (value >> 27U)) * 0x94D049BB133111EBULL;
  return value ^ (value >> 31U);
}

void hash_word(U64& hash, U64 value) noexcept {
  for (unsigned int byte_index = 0; byte_index < 8U; ++byte_index) {
    hash ^= (value >> (byte_index * 8U)) & 0xFFULL;
    hash *= fnv_prime;
  }
}

std::vector<Event> make_workload(std::size_t event_count, U64 seed) {
  std::vector<Event> events(event_count);
  U64 random_state = seed;
  const U64 groups = static_cast<U64>(group_count);
  for (std::size_t index = 0; index < event_count; ++index) {
    Event& event = events[index];
    const U64 first = next_random(random_state);
    event.row = static_cast<std::uint8_t>(first % static_cast<U64>(row_count));
    event.insert = ((first >> 8U) & 1ULL) == 0ULL;
    event.group = static_cast<std::uint8_t>((first >> 16U) % groups);

    const U64 shape = next_random(random_state);
    event.alias_count = static_cast<std::uint8_t>(2ULL + (shape % 3ULL));
    event.parent_count = static_cast<std::uint8_t>(3ULL + ((shape >> 8U) % 2ULL));
    const auto base_degree = static_cast<std::uint8_t>(1ULL + ((shape >> 16U) % 8ULL));
    for (std::size_t slot = 0; slot < maximum_aliases; ++slot) {
      const U64 alias_bits = next_random(random_state);
      event.alias_offsets[slot] = static_cast<std::uint8_t>(alias_bits % groups);
    }
    for (std::size_t slot = 0; slot < maximum_parents; ++slot) {
      // Every changed event touches at least three parent records. Alternating
      // degrees make repetitions observable without collapsing equal values.
      event.parent_degrees[slot] = static_cast<std::uint8_t>(
          static_cast<unsigned int>(base_degree) + static_cast<unsigned int>(slot % 2U));
    }
  }
  return events;
}

std::size_t physical_descriptor(bool insert) noexcept {
  return insert ? 0U : 4U;
}

std::size_t occurrence_descriptor(bool insert) noexcept {
  return insert ? 1U : 5U;
}

std::size_t support_descriptor(bool insert) noexcept {
  return insert ? 2U : 6U;
}

std::size_t degree_descriptor(bool insert) noexcept {
  return insert ? 3U : 7U;
}

template <Profile profile>
LogicalResult execute(const std::vector<Event>& events, collection::Collector* collector) {
  static_cast<void>(collector);
  std::array<Row, row_count> rows{};
  std::array<U64, group_count> group_rows{};
  LogicalResult result{};
  result.trace_checksum = fnv_offset;

  for (std::size_t index = 0; index < events.size(); ++index) {
    const Event& event = events[index];
    Row& row = rows[static_cast<std::size_t>(event.row)];
    Reason reason = Reason::changed;
    const bool changed = event.insert ? !row.present : row.present;
    if (event.insert && row.present) {
      reason = Reason::duplicate_insert;
    } else if (!event.insert && !row.present) {
      reason = Reason::absent_erase;
    }
    const std::uint8_t affected_group = event.insert ? event.group : row.group;

    ++result.inputs;
    if (changed) {
      ++result.changed;
    } else {
      ++result.noops;
      if (reason == Reason::duplicate_insert) {
        ++result.duplicate_inserts;
      } else {
        ++result.absent_erases;
      }
    }

    collection::Ticket outer{};
    collection::Ticket child{};
    if constexpr (profile != Profile::no_calls) {
      outer = collector->begin(physical_descriptor(event.insert), changed);
      if (changed) {
        child = collector->nest(outer);
      }
    }

    U64 support_before = 0;
    U64 support_after = 0;
    if (changed) {
      const std::size_t group = static_cast<std::size_t>(affected_group);
      support_before = group_rows[group];
      if (event.insert) {
        row.present = true;
        row.group = event.group;
        ++group_rows[group];
      } else {
        row.present = false;
        --group_rows[group];
      }
      support_after = group_rows[group];
    }

    hash_word(result.trace_checksum, static_cast<U64>(index));
    hash_word(result.trace_checksum, event.insert ? 1ULL : 0ULL);
    hash_word(result.trace_checksum, static_cast<U64>(event.row));
    hash_word(result.trace_checksum, static_cast<U64>(event.group));
    hash_word(result.trace_checksum, changed ? 1ULL : 0ULL);
    hash_word(result.trace_checksum, static_cast<U64>(reason));
    if (changed) {
      hash_word(result.trace_checksum, static_cast<U64>(affected_group));
      hash_word(result.trace_checksum, support_before);
      hash_word(result.trace_checksum, support_after);
      hash_word(result.trace_checksum, static_cast<U64>(event.alias_count));
      for (std::size_t alias = 0; alias < static_cast<std::size_t>(event.alias_count); ++alias) {
        const std::uint8_t candidate_group = static_cast<std::uint8_t>(
            (static_cast<U64>(affected_group) + static_cast<U64>(event.alias_offsets[alias])) %
            static_cast<U64>(group_count));
        const bool local_predicate =
            ((static_cast<std::size_t>(event.row) + alias + static_cast<std::size_t>(candidate_group)) % 4U) != 0U;
        const bool accepted = candidate_group == affected_group && local_predicate;
        ++result.occurrence_visits;
        if (accepted) {
          ++result.occurrence_accepted;
        } else {
          ++result.occurrence_rejected;
        }
        hash_word(result.trace_checksum, static_cast<U64>(candidate_group));
        hash_word(result.trace_checksum, local_predicate ? 1ULL : 0ULL);
        hash_word(result.trace_checksum, accepted ? 1ULL : 0ULL);
        if constexpr (profile != Profile::no_calls) {
          collector->occurrence(occurrence_descriptor(event.insert), accepted);
        }
      }
      if constexpr (profile != Profile::no_calls) {
        collector->support(support_descriptor(event.insert), support_before, support_after);
      }
      hash_word(result.trace_checksum, static_cast<U64>(event.parent_count));
      for (std::size_t parent = 0; parent < static_cast<std::size_t>(event.parent_count); ++parent) {
        hash_word(result.trace_checksum, static_cast<U64>(event.parent_degrees[parent]));
        if constexpr (profile != Profile::no_calls) {
          collector->degree(degree_descriptor(event.insert),
                            static_cast<U64>(event.parent_degrees[parent]));
        }
      }
      if constexpr (profile != Profile::no_calls) {
        static_cast<void>(collector->finish(child, true));
      }
    }
    if constexpr (profile != Profile::no_calls) {
      static_cast<void>(collector->finish(outer, true));
    }
  }

  result.final_group_rows = group_rows;
  U64 state_hash = fnv_offset;
  for (std::size_t slot = 0; slot < rows.size(); ++slot) {
    hash_word(state_hash, static_cast<U64>(slot));
    hash_word(state_hash, rows[slot].present ? 1ULL : 0ULL);
    hash_word(state_hash, static_cast<U64>(rows[slot].group));
  }
  for (std::size_t group = 0; group < group_rows.size(); ++group) {
    hash_word(state_hash, static_cast<U64>(group));
    hash_word(state_hash, group_rows[group]);
  }
  result.state_checksum = state_hash;
  return result;
}

std::array<collection::Descriptor, 8> make_descriptors() {
  using collection::Descriptor;
  using collection::Kind;
  using collection::Operation;
  return {{
      Descriptor{Kind::physical, 1U, 0U, Operation::insert},
      Descriptor{Kind::occurrence, 1U, 0U, Operation::insert},
      Descriptor{Kind::support, 1U, 0U, Operation::insert},
      Descriptor{Kind::degree, 1U, 0U, Operation::insert},
      Descriptor{Kind::physical, 1U, 0U, Operation::erase},
      Descriptor{Kind::occurrence, 1U, 0U, Operation::erase},
      Descriptor{Kind::support, 1U, 0U, Operation::erase},
      Descriptor{Kind::degree, 1U, 0U, Operation::erase},
  }};
}

collection::Options make_options(Profile profile, std::size_t event_count) {
  collection::Options options{};
  options.max_cells = 8U;
  options.period = profile == Profile::sampled ? 64U : 1U;
  options.offset = 0U;
  options.detail_budget = profile == Profile::off_calls ? 0U : static_cast<U64>(event_count) * 9ULL;
  options.mode = profile == Profile::off_calls ? collection::Mode::off : collection::Mode::counters;
  return options;
}

bool parse_size(const char* text, std::size_t& result) noexcept {
  const char* const end = text + std::string_view{text}.size();
  std::size_t value = 0;
  const auto parsed = std::from_chars(text, end, value);
  if (parsed.ec != std::errc{} || parsed.ptr != end) {
    return false;
  }
  result = value;
  return true;
}

bool parse_seed(const char* text, U64& result) noexcept {
  const char* const end = text + std::string_view{text}.size();
  U64 value = 0;
  const auto parsed = std::from_chars(text, end, value);
  if (parsed.ec != std::errc{} || parsed.ptr != end) {
    return false;
  }
  result = value;
  return true;
}

bool verify_clean_metadata(const collection::Metadata& metadata) noexcept {
  return !metadata.invalid_descriptor && !metadata.protocol_error &&
         !metadata.ordinal_exhausted && !metadata.saturated && metadata.aborted == 0U &&
         metadata.truncated == 0U && metadata.committed_truncated == 0U;
}

template <Profile profile>
ProfileReport measure_profile(std::string_view name, const std::vector<Event>& events,
                              std::size_t warmups, std::size_t repetitions,
                              const LogicalResult& expected, collection::Collector& collector,
                              const std::array<collection::Descriptor, 8>& descriptors) {
  static_cast<void>(collector);
  ProfileReport report{};
  report.name = name;
  report.raw_nanoseconds.resize(repetitions);

  if constexpr (profile != Profile::no_calls) {
    const collection::Options options = make_options(profile, events.size());
    if (profile == Profile::off_calls) {
      collector.configure(options, {});
    } else {
      collector.configure(options, descriptors);
    }
    report.collector_mode = options.mode == collection::Mode::off ? "off" : "counters";
    report.sample_period = options.period;
    report.sample_offset = options.offset;
    report.detail_budget = options.detail_budget;
    report.max_cells = options.max_cells;
    report.descriptor_count = collector.descriptors().size();
    report.memory = collector.memory();
  }

  for (std::size_t index = 0; index < warmups + repetitions; ++index) {
    if constexpr (profile != Profile::no_calls) {
      if (!collector.reset()) {
        throw std::runtime_error("collector reset rejected outside a transaction");
      }
    }
    const bool measured = index >= warmups;
    const auto start = measured ? std::chrono::steady_clock::now()
                                : std::chrono::steady_clock::time_point{};
    LogicalResult actual{};
    if constexpr (profile == Profile::no_calls) {
      actual = execute<profile>(events, nullptr);
    } else {
      actual = execute<profile>(events, &collector);
    }
    const auto stop = measured ? std::chrono::steady_clock::now()
                               : std::chrono::steady_clock::time_point{};
    if (!(actual == expected)) {
      throw std::runtime_error("profile logical result differs from no-calls reference");
    }
    if (measured) {
      const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
      if (elapsed <= 0) {
        throw std::runtime_error("steady clock reported a nonpositive timed interval");
      }
      report.raw_nanoseconds[index - warmups] = static_cast<U64>(elapsed);
      if constexpr (profile != Profile::no_calls) {
        report.metadata = collector.metadata();
        if (!verify_clean_metadata(report.metadata)) {
          throw std::runtime_error("collector reported degraded, aborted, or truncated coverage");
        }
      }
      report.logical = actual;
    }
  }
  return report;
}

U64 median(std::vector<U64> values) {
  std::sort(values.begin(), values.end());
  const std::size_t middle = values.size() / 2U;
  if ((values.size() % 2U) != 0U) {
    return values[middle];
  }
  return values[middle - 1U] + ((values[middle] - values[middle - 1U]) / 2ULL);
}

void print_hex(std::ostream& stream, U64 value) {
  constexpr std::array<char, 16> digits{{'0', '1', '2', '3', '4', '5', '6', '7',
                                         '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'}};
  std::array<char, 16> buffer{};
  for (std::size_t index = buffer.size(); index > 0U; --index) {
    const std::size_t digit = static_cast<std::size_t>(value & 0xFULL);
    buffer[index - 1U] = digits[digit];
    value >>= 4U;
  }
  stream << "\"0x" << std::string_view(buffer.data(), buffer.size()) << '\"';
}

void print_logical(std::ostream& stream, const LogicalResult& result) {
  stream << "{\"inputs\":" << result.inputs << ",\"changed\":" << result.changed
         << ",\"noops\":" << result.noops << ",\"duplicate_inserts\":"
         << result.duplicate_inserts << ",\"absent_erases\":" << result.absent_erases
         << ",\"occurrence_visits\":" << result.occurrence_visits
         << ",\"occurrence_accepted\":" << result.occurrence_accepted
         << ",\"occurrence_rejected\":" << result.occurrence_rejected
         << ",\"final_group_rows\":[";
  for (std::size_t index = 0; index < result.final_group_rows.size(); ++index) {
    if (index != 0U) {
      stream << ',';
    }
    stream << result.final_group_rows[index];
  }
  stream << "],\"state_checksum\":";
  print_hex(stream, result.state_checksum);
  stream << ",\"trace_checksum\":";
  print_hex(stream, result.trace_checksum);
  stream << '}';
}

void print_metadata(std::ostream& stream, const collection::Metadata& metadata) {
  stream << "{\"attempts\":" << metadata.attempts << ",\"committed\":" << metadata.committed
         << ",\"aborted\":" << metadata.aborted << ",\"selected\":" << metadata.selected
         << ",\"complete\":" << metadata.complete << ",\"aborted_selected\":"
         << metadata.aborted_selected << ",\"truncated\":" << metadata.truncated
         << ",\"committed_truncated\":" << metadata.committed_truncated
         << ",\"guards\":" << metadata.guards << ",\"detail_actions\":"
         << metadata.detail_actions << ",\"cleared_cells\":" << metadata.cleared_cells
         << ",\"merged_cells\":" << metadata.merged_cells
         << ",\"saturated\":" << (metadata.saturated ? "true" : "false")
         << ",\"invalid_descriptor\":" << (metadata.invalid_descriptor ? "true" : "false")
         << ",\"protocol_error\":" << (metadata.protocol_error ? "true" : "false")
         << ",\"ordinal_exhausted\":" << (metadata.ordinal_exhausted ? "true" : "false") << '}';
}

void print_memory(std::ostream& stream, const collection::Memory& memory, bool collector_present) {
  stream << "{\"collector_present\":" << (collector_present ? "true" : "false")
         << ",\"object_bytes\":" << memory.object_bytes
         << ",\"descriptors_bytes\":" << memory.descriptors_bytes
         << ",\"committed_bytes\":" << memory.committed_bytes
         << ",\"attempt_bytes\":" << memory.attempt_bytes
         << ",\"previous_bytes\":" << memory.previous_bytes
         << ",\"retained_payload_bytes\":" << memory.retained_payload_bytes
         << ",\"object_plus_payload_bytes\":"
         << (memory.object_bytes + memory.retained_payload_bytes) << '}';
}

void print_report(std::ostream& stream, const ProfileReport& report, std::size_t event_count,
                  bool collector_present) {
  const U64 low = *std::min_element(report.raw_nanoseconds.begin(), report.raw_nanoseconds.end());
  const U64 high = *std::max_element(report.raw_nanoseconds.begin(), report.raw_nanoseconds.end());
  const U64 middle = median(report.raw_nanoseconds);
  const long double throughput =
      (static_cast<long double>(event_count) * 1000000000.0L) / static_cast<long double>(middle);
  stream << "{\"name\":\"" << report.name << "\",\"raw_nanoseconds\":[";
  for (std::size_t index = 0; index < report.raw_nanoseconds.size(); ++index) {
    if (index != 0U) {
      stream << ',';
    }
    stream << report.raw_nanoseconds[index];
  }
  stream << "],\"median_nanoseconds\":" << middle << ",\"min_nanoseconds\":" << low
         << ",\"max_nanoseconds\":" << high << ",\"median_workload_events_per_second\":"
         << std::fixed << std::setprecision(2) << static_cast<double>(throughput) << std::defaultfloat
         << ",\"same_as_reference\":true,\"collector_config\":{\"mode\":\""
         << report.collector_mode << "\",\"period\":" << report.sample_period
         << ",\"offset\":" << report.sample_offset << ",\"detail_budget\":"
         << report.detail_budget << ",\"max_cells\":" << report.max_cells
         << ",\"descriptor_count\":" << report.descriptor_count
         << "},\"logical\":";
  print_logical(stream, report.logical);
  stream << ",\"collector_metadata\":";
  print_metadata(stream, report.metadata);
  stream << ",\"memory\":";
  print_memory(stream, report.memory, collector_present);
  stream << '}';
}

} // namespace

int main(int argc, char** argv) {
  std::size_t event_count = default_event_count;
  std::size_t warmups = default_warmups;
  std::size_t repetitions = default_repetitions;
  U64 seed = default_seed;
  if (argc > 5) {
    std::cerr << "usage: crown-c01-benchmark [events [warmups [repetitions [seed]]]]\n";
    return 2;
  }
  if ((argc > 1 && !parse_size(argv[1], event_count)) ||
      (argc > 2 && !parse_size(argv[2], warmups)) ||
      (argc > 3 && !parse_size(argv[3], repetitions)) ||
      (argc > 4 && !parse_seed(argv[4], seed)) || event_count == 0U || repetitions == 0U ||
      warmups > std::numeric_limits<std::size_t>::max() - repetitions ||
      event_count > static_cast<std::size_t>(std::numeric_limits<U64>::max() / 9ULL)) {
    std::cerr << "invalid configuration; events and repetitions must be positive and events <= UINT64_MAX/9\n";
    return 2;
  }

  try {
    const std::vector<Event> events = make_workload(event_count, seed);
    const LogicalResult expected = execute<Profile::no_calls>(events, nullptr);
    const auto descriptors = make_descriptors();
    collection::Collector collector;

    const ProfileReport no_calls = measure_profile<Profile::no_calls>(
        "no_instrumentation_calls", events, warmups, repetitions, expected,
        collector, descriptors);
    const ProfileReport off_calls = measure_profile<Profile::off_calls>(
        "off_collector_calls", events, warmups, repetitions, expected,
        collector, descriptors);
    const ProfileReport census = measure_profile<Profile::census>(
        "census_counters_period_1", events, warmups, repetitions, expected,
        collector, descriptors);
    const ProfileReport sampled = measure_profile<Profile::sampled>(
        "sampled_counters_period_64_offset_0", events, warmups, repetitions, expected,
        collector, descriptors);

    std::cout << "{\"schema\":\"crown-c01-collector-overhead-benchmark-v1\","
              << "\"scope\":\"component_microbenchmark_only_not_engine_throughput_or_runtime_parity\","
              << "\"seed\":" << seed << ",\"events\":" << event_count
              << ",\"rows\":" << row_count << ",\"groups\":" << group_count
              << ",\"warmups\":" << warmups << ",\"repetitions\":" << repetitions
              << ",\"build_flags\":\"" << build_flags << "\","
              << "\"clock\":\"steady_clock around complete workload runs; collector has no clocks\","
              << "\"expected_logical\":";
    print_logical(std::cout, expected);
    std::cout << ",\"profiles\":[";
    print_report(std::cout, no_calls, event_count, false);
    std::cout << ',';
    print_report(std::cout, off_calls, event_count, true);
    std::cout << ',';
    print_report(std::cout, census, event_count, true);
    std::cout << ',';
    print_report(std::cout, sampled, event_count, true);
    std::cout << "]}\n";
  } catch (const std::exception& error) {
    std::cerr << "benchmark setup or verification failed: " << error.what() << '\n';
    return 1;
  }
  return 0;
}
