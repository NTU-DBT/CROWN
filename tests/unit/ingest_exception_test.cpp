#include "crown/api/error.hpp"
#include "crown/io/catalog.hpp"
#include "crown/io/ingest.hpp"
#include "crown/io/support.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/runtime/replay.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

// This standalone executable replaces the ordinary throwing scalar and
// array global operator new forms directly; fail-after injects before the
// shim backing malloc call. No dedicated aligned/nothrow replacements are
// present, and indirect library delegation is not asserted coverage. Direct
// malloc/realloc/system failures and MemoryAccount admission denials are not
// injected by this shim.
namespace {
thread_local std::ptrdiff_t fail_after = -1;
thread_local std::size_t largest_allocation = 0;
thread_local std::size_t allocation_count = 0;
thread_local std::size_t total_allocation_bytes = 0;

[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
  largest_allocation = std::max(largest_allocation, bytes);
  ++allocation_count;
  total_allocation_bytes += bytes;
  if (fail_after >= 0) {
    if (fail_after == 0) throw std::bad_alloc{};
    --fail_after;
  }
  if (auto* result = std::malloc(bytes == 0 ? 1 : bytes)) return result;
  throw std::bad_alloc{};
}

struct FaultScope {
  explicit FaultScope(std::ptrdiff_t step = -1) noexcept { fail_after = step; }
  ~FaultScope() { fail_after = -1; }
  FaultScope(const FaultScope&) = delete;
  FaultScope& operator=(const FaultScope&) = delete;
  void forbid_allocations() noexcept { fail_after = 0; }
};
}  // namespace

void* operator new(std::size_t bytes) { return malloc_new(bytes); }
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
void operator delete(void* pointer) noexcept { std::free(pointer); }
void operator delete[](void* pointer) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }

namespace {
using namespace crown;
using namespace crown::runtime;
using io::InputEvent;
using io::InputFormat;
using io::InputOptions;
using io::InputProgress;

static_assert(std::is_nothrow_move_constructible_v<io::EventReader>);
static_assert(std::is_nothrow_move_assignable_v<io::EventReader>);
static_assert(std::is_nothrow_move_constructible_v<OrderedReplay>);
static_assert(std::is_nothrow_move_assignable_v<OrderedReplay>);

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    std::forward<Action>(action)();
  } catch (const Error& failure) {
    check(failure.code() == code,
          "expected " + std::string(code) + ", got " + failure.code());
    return;
  }
  throw std::runtime_error("expected error code " + std::string(code));
}

Catalog make_catalog() {
  return {53, {{"R", {{"x", ScalarType::int64}, {"label", ScalarType::string}}, 4}}};
}

Row row(std::int64_t x, std::string label) {
  return {x, std::move(label)};
}

InputEvent event(std::uint64_t sequence, std::int64_t x, std::string label,
                 std::optional<io::SourcePosition> position = std::nullopt) {
  return {{sequence, TableId{0}, SetOperation::insert, row(x, std::move(label))},
          std::move(position)};
}

bool same_event(const auto& left, const InputEvent& right) {
  return left.update.sequence == right.update.sequence &&
         left.update.table == right.update.table &&
         left.update.operation == right.update.operation &&
         left.update.values == right.update.values &&
         left.source_position == right.source_position;
}

struct Fixture {
  Catalog catalog = make_catalog();
  InputEvent input = event(1, 7, "payload-long-enough-for-several-allocations",
                           io::SourcePosition{"source-A", 100});
  std::string json = io::write_input_json(input, catalog);
  std::string binary = io::write_input_binary(input, catalog);
  std::string csv = "x|label\n7|payload-long-enough-for-several-allocations\n";
  InputProgress initial;
  InputOptions json_options;
  InputOptions binary_options;
  InputOptions csv_options;

  Fixture() {
    initial.sequence = 0;
    initial.source_positions.emplace("old-source", 3);
    binary_options.format = InputFormat::binary;
    csv_options.format = InputFormat::csv;
    csv_options.table = TableId{0};
    csv_options.delimiter = '|';
    csv_options.source = "source-A";
    csv_options.byte_offset = 100;
  }

  std::string_view bytes(InputFormat format) const {
    if (format == InputFormat::jsonl) return json;
    if (format == InputFormat::binary) return binary;
    return csv;
  }

  InputOptions options(InputFormat format) const {
    if (format == InputFormat::jsonl) return json_options;
    if (format == InputFormat::binary) return binary_options;
    return csv_options;
  }

  InputEvent expected(InputFormat format) const {
    if (format != InputFormat::csv) return input;
    return event(1, 7, "payload-long-enough-for-several-allocations",
                 io::SourcePosition{"source-A", 100 + std::string("x|label\n").size()});
  }

  std::uint64_t expected_bytes_read(InputFormat format) const {
    if (format == InputFormat::jsonl) return json.size();
    if (format == InputFormat::binary) return binary.size();
    return csv.size();
  }
};

std::unique_ptr<io::EventReader> make_reader(const Fixture& fixture,
                                             InputFormat format,
                                             std::istringstream& stream,
                                             InputProgress progress) {
  return std::make_unique<io::EventReader>(stream, fixture.catalog,
                                           fixture.options(format),
                                           std::move(progress));
}

void check_fresh_recreated_event(const Fixture& fixture, InputFormat format) {
  std::istringstream replacement{std::string(fixture.bytes(format))};
  auto reader = make_reader(fixture, format, replacement, fixture.initial);
  const auto* decoded = reader->peek();
  check(decoded && same_event(*decoded, fixture.expected(format)),
        "recreated reader did not decode the original event");
  check(reader->progress() == fixture.initial,
        "recreated reader changed accepted progress before acknowledgement");
  reader->acknowledge();
  check(reader->progress().sequence == 1 &&
            reader->progress().source_positions.at("source-A") ==
                fixture.expected(format).source_position->offset,
        "recreated reader could not explicitly accept the same input");
}

std::string edge_line(const Catalog& catalog, std::uint64_t sequence,
                      std::int64_t x, std::int64_t z,
                      std::optional<io::SourcePosition> position = std::nullopt) {
  InputEvent input{{sequence, TableId{0}, SetOperation::insert, {x, z}},
                   std::move(position)};
  return io::write_input_json(input, catalog) + "\n";
}

std::size_t sweep_reader_construction(const Fixture& fixture, InputFormat format) {
  constexpr std::ptrdiff_t max_points = 2048;
  std::size_t failures = 0;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    std::istringstream stream{std::string(fixture.bytes(format))};
    auto schema = fixture.catalog;
    auto config = fixture.options(format);
    auto progress = fixture.initial;
    std::optional<io::EventReader> reader;
    bool failed = false;
    {
      FaultScope fault(point);
      try {
        reader.emplace(stream, std::move(schema), std::move(config),
                       std::move(progress));
      } catch (const std::bad_alloc&) {
        failed = true;
      }
    }
    if (failed) {
      ++failures;
      // Construction does not consume the borrowed stream. A fresh reader on
      // the same bytes and progress is the explicit recovery operation.
      check_fresh_recreated_event(fixture, format);
      continue;
    }
    check(failures > 0, "reader construction sweep observed no injected ordinary-new failure point");
    const auto* decoded = reader->peek();
    check(decoded && same_event(*decoded, fixture.expected(format)),
          "reader construction sweep changed the decoded event");
    check(reader->progress() == fixture.initial,
          "reader construction sweep changed accepted progress");
    return failures;
  }
  throw std::runtime_error("EventReader construction sweep exceeded 2048 points");
}

std::size_t sweep_reader_peek(const Fixture& fixture, InputFormat format) {
  constexpr std::ptrdiff_t max_points = 4096;
  std::size_t failures = 0;
  bool saw_completed_record_before_failure = false;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    std::istringstream stream{std::string(fixture.bytes(format))};
    auto reader = make_reader(fixture, format, stream, fixture.initial);
    bool failed = false;
    const io::InputEventView* decoded = nullptr;
    {
      FaultScope fault(point);
      try {
        decoded = reader->peek();
      } catch (const std::bad_alloc&) {
        failed = true;
      }
    }
    if (failed) {
      ++failures;
      check(reader->failed(), "parser/progress-preparation OOM was not sticky");
      check(reader->progress() == fixture.initial && reader->records_read() == 0,
            "failed peek advanced accepted source progress or record count");
      saw_completed_record_before_failure |=
          reader->bytes_read() == fixture.expected_bytes_read(format);
      expect_error([&] { static_cast<void>(reader->peek()); }, "input_failed");
      check_fresh_recreated_event(fixture, format);
      continue;
    }

    check(failures > 0, "reader peek sweep observed no injected ordinary-new failure point");
    check(saw_completed_record_before_failure,
          "peek sweep missed OOM after bytes were consumed, including progress-node preparation");
    check(decoded && same_event(*decoded, fixture.expected(format)) &&
              reader->peek() == decoded && !reader->failed() &&
              reader->progress() == fixture.initial && reader->records_read() == 1,
          "successful peek sweep changed its cached event or progress");
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      reader->acknowledge();
    }
    check(reader->progress().sequence == 1 &&
              reader->progress().source_positions.at("source-A") ==
                  fixture.expected(format).source_position->offset,
          "acknowledgement did not commit the prepared source position");
    return failures;
  }
  throw std::runtime_error("EventReader peek sweep exceeded 4096 points");
}

void acknowledgement_and_lifetime_are_noalloc(const Fixture& fixture) {
  for (const auto format : {InputFormat::jsonl, InputFormat::binary, InputFormat::csv}) {
    // A fresh source takes the prepared map-node path.
    {
      std::istringstream stream{std::string(fixture.bytes(format))};
      auto reader = make_reader(fixture, format, stream, fixture.initial);
      check(reader->peek() != nullptr, "new-source acknowledgement fixture did not decode");
      {
        FaultScope no_allocations;
        no_allocations.forbid_allocations();
        reader->acknowledge();
      }
      check(reader->progress().sequence == 1 &&
                reader->progress().source_positions.contains("source-A"),
            "new-source acknowledgement requested intercepted ordinary new under persistent fail-after");
    }

    // Existing-source acknowledgement uses a saved iterator and must not request
    // an intercepted ordinary-new form.
    auto existing_progress = fixture.initial;
    existing_progress.source_positions.emplace("source-A", 1);
    {
      std::istringstream stream{std::string(fixture.bytes(format))};
      auto reader = make_reader(fixture, format, stream, existing_progress);
      check(reader->peek() != nullptr, "existing-source acknowledgement fixture did not decode");
      {
        FaultScope no_allocations;
        no_allocations.forbid_allocations();
        reader->acknowledge();
      }
      check(reader->progress().sequence == 1 &&
                reader->progress().source_positions.at("source-A") ==
                    fixture.expected(format).source_position->offset,
            "existing-source acknowledgement requested intercepted ordinary new under persistent fail-after");
    }
  }

  std::istringstream first_stream{fixture.json};
  auto first = make_reader(fixture, InputFormat::jsonl, first_stream, fixture.initial);
  check(first->peek() != nullptr, "move/destruction fixture did not decode");
  std::istringstream second_stream{fixture.json};
  auto second = make_reader(fixture, InputFormat::jsonl, second_stream, fixture.initial);
  check(second->peek() != nullptr, "move assignment target did not decode");
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    io::EventReader moved(std::move(*first));
    *second = std::move(moved);  // Destroys the old target Data while OOM stays armed.
  }
  check(second->peek() && second->progress() == fixture.initial,
        "EventReader moves requested intercepted ordinary new or lost cached input/progress");
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    second.reset();  // Reader destruction must not request intercepted ordinary new.
  }
}

void sweep_catalog_digest_and_codecs(const Fixture& fixture) {
  constexpr std::ptrdiff_t max_points = 2048;
  std::size_t digest_failures = 0;
  bool digest_succeeded = false;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    bool failed = false;
    std::string digest;
    {
      FaultScope fault(point);
      try {
        digest = io::input_catalog_sha256(fixture.catalog);
      } catch (const std::bad_alloc&) {
        failed = true;
      }
    }
    if (failed) {
      ++digest_failures;
      continue;
    }
    check(digest_failures > 0,
          "catalog digest sweep observed no injected ordinary-new failure point");
    check(digest == io::input_catalog_sha256(fixture.catalog),
          "catalog digest changed across failed attempts");
    digest_succeeded = true;
    break;
  }
  check(digest_succeeded, "catalog digest sweep exceeded 2048 points");

  const auto exercise_writer = [&](auto&& writer, std::string_view clean,
                                   std::string_view label) {
    bool persistent_oom_returned = false;
    {
      FaultScope persistent;
      persistent.forbid_allocations();
      try {
        const auto ignored = writer();
        static_cast<void>(ignored);
      } catch (const std::bad_alloc&) {
        persistent_oom_returned = true;
      }
    }
    check(persistent_oom_returned,
          std::string(label) + " did not return cleanly from persistent OOM");

    std::size_t failures = 0;
    for (std::ptrdiff_t point = 0; point < max_points; ++point) {
      bool failed = false;
      std::string encoded;
      {
        FaultScope fault(point);
        try {
          encoded = writer();
        } catch (const std::bad_alloc&) {
          failed = true;
        }
      }
      if (failed) {
        ++failures;
        continue;
      }
      check(failures > 0, std::string(label) + " sweep observed no injected ordinary-new failure point");
      check(encoded == clean, std::string(label) + " changed bytes after an injected ordinary-new failure and retry");
      return;
    }
    throw std::runtime_error(std::string(label) + " sweep exceeded 2048 points");
  };

  exercise_writer([&] { return io::write_input_json(fixture.input, fixture.catalog); },
                  fixture.json, "JSON input writer");
  exercise_writer([&] { return io::write_input_binary(fixture.input, fixture.catalog); },
                  fixture.binary, "binary input writer");

  const auto large = event(1, 8, std::string(32 * 1024, 'x'));
  io::InputLimits tight;
  tight.record_bytes = 128;
  const auto check_tight_budget = [&](auto&& writer, std::string_view label) {
    largest_allocation = 0;
    allocation_count = 0;
    expect_error([&] { static_cast<void>(writer()); }, "resource_limit");
    check(largest_allocation < 4096,
          std::string(label) + " requested a payload-sized intercepted ordinary-new block before rejecting the short budget");
  };
  check_tight_budget([&] { return io::write_input_json(large, fixture.catalog, tight); },
                     "JSON writer");
  check_tight_budget([&] { return io::write_input_binary(large, fixture.catalog, tight); },
                     "binary writer");
}

PhysicalPlan make_root_plan() {
  constexpr VariableId x{0}, label{1};
  const Catalog catalog{53, {{"R", {{"x", ScalarType::int64},
                                       {"label", ScalarType::string}}, 4}}};
  const Query query{{{"x", ScalarType::int64}, {"label", ScalarType::string}},
                    {{"r", TableId{0}, {x, label}}},
                    {{x, "x"}, {label, "label"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"root", NodeKind::native, {x, label}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan make_self_join_plan() {
  constexpr VariableId x{0}, z{1}, y{2};
  const Catalog catalog{53, {{"E", {{"x", ScalarType::int64},
                                       {"z", ScalarType::int64}}, 4}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64},
                     {"y", ScalarType::int64}},
                    {{"left", TableId{0}, {x, z}}, {"right", TableId{0}, {z, y}}},
                    {{x, "x"}, {z, "z"}, {y, "y"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"join-key", NodeKind::generalized, {z}, {NodeId{1}, NodeId{2}}, {}, {}},
      {"left", NodeKind::native, {x, z}, {}, 0, {}},
      {"right", NodeKind::native, {z, y}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

io::Json normalized_owners(io::Json value) {
  const auto normalize = [&](const auto& self, io::Json& item) -> void {
    if (item.is_object()) {
      if (item.contains("owner")) item["owner"] = 0;
      for (auto& member : item.items()) self(self, member.value());
    } else if (item.is_array()) {
      for (auto& member : item) self(self, member);
    }
  };
  normalize(normalize, value);
  return value;
}

struct RuntimeImage {
  std::uint64_t sequence = 0;
  bool answer = false;
  std::vector<Relation> physical;
  io::Json support;
  bool operator==(const RuntimeImage&) const = default;
};

RuntimeImage image(const PhysicalRuntime& runtime) {
  const auto snapshot = runtime.snapshot();
  RuntimeImage result;
  result.sequence = snapshot.sequence;
  result.answer = runtime.has_answer();
  result.physical = snapshot.physical.tables;
  result.support = normalized_owners(io::write_support_snapshot(snapshot.support,
                                                                  runtime.plan()));
  return result;
}

RuntimeImage image(const DeltaRuntime& runtime) {
  const auto snapshot = runtime.snapshot();
  RuntimeImage result;
  result.sequence = snapshot.sequence;
  result.answer = runtime.has_answer();
  result.physical = snapshot.physical.tables;
  result.support = normalized_owners(io::write_support_snapshot(snapshot.support,
                                                                  runtime.plan()));
  return result;
}

io::InputProgress progress_at(std::uint64_t sequence) {
  io::InputProgress progress;
  progress.sequence = sequence;
  return progress;
}

std::string line(const Catalog& catalog, std::uint64_t sequence, std::int64_t x,
                 std::string label,
                 std::optional<io::SourcePosition> position = std::nullopt) {
  return io::write_input_json(event(sequence, x, std::move(label), std::move(position)),
                             catalog) + "\n";
}

std::string root_line(const PhysicalPlan& plan, std::uint64_t sequence,
                      std::int64_t x, std::string label, std::uint64_t offset) {
  return line(plan.catalog(), sequence, x, std::move(label),
              io::SourcePosition{"replay-source", offset});
}

struct HeldSourcePin {
  PhysicalEpoch epoch;
  TupleHandle handle{};
  ArenaHandle retained_handle{};
  Row values;
  io::Json support_journal;

  explicit HeldSourcePin(PhysicalEpoch committed) : epoch(std::move(committed)) {
    check(epoch.input.source.has_value(), "committed seed did not retain its source row");
    handle = epoch.input.source->handle;
    retained_handle = epoch.input.source->retained.handle();
    values = storage::export_row(epoch.input.source->tuple().values());
    support_journal = normalized_owners(io::write_support_epoch(epoch.support));
  }

  void check_unchanged() const {
    check(epoch.input.source && epoch.input.source->handle == handle &&
              epoch.input.source->retained.handle() == retained_handle &&
              epoch.input.source->tuple().values() == values,
          "injected ordinary-new failure changed a committed source-row pin");
    check(normalized_owners(io::write_support_epoch(epoch.support)) == support_journal,
          "injected ordinary-new failure changed an older support journal");
  }
};

std::size_t sweep_ordered_physical_apply(const PhysicalPlan& plan) {
  constexpr std::ptrdiff_t max_points = 8192;
  const auto catalog = plan.catalog();
  const auto second = root_line(plan, 2, 2, "second", 20);

  PhysicalRuntime clean(plan);
  auto clean_seed = clean.apply({1, TableId{0}, SetOperation::insert, row(1, "seed")});
  auto clean_next = clean.apply({2, TableId{0}, SetOperation::insert, row(2, "second")});
  const auto expected = image(clean);
  check(expected.sequence == 2 && expected.physical[0].size() == 2,
        "physical replay clean fixture did not commit two full source rows");
  static_cast<void>(clean_seed);
  static_cast<void>(clean_next);

  std::size_t failures = 0;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    PhysicalRuntime runtime(plan);
    HeldSourcePin held(runtime.apply({1, TableId{0}, SetOperation::insert,
                                      row(1, "seed")}));
    const auto before = image(runtime);
    const auto old_sequence = runtime.sequence();
    std::istringstream stream(second);
    io::EventReader reader(stream, catalog, {}, progress_at(1));
    OrderedReplay replay(std::move(reader));
    const auto* cached = replay.peek();
    check(cached && cached->update.sequence == 2,
          "physical replay sweep did not prepare its cached source event");

    bool failed = false;
    std::optional<PhysicalEpoch> output;
    {
      FaultScope fault(point);
      try {
        auto accepted = replay.apply_next(runtime);
        if (accepted) output.emplace(std::move(*accepted));
      } catch (const std::bad_alloc&) {
        failed = true;
      }
    }
    held.check_unchanged();
    if (failed) {
      ++failures;
      check(runtime.sequence() == old_sequence && replay.progress() == progress_at(1) &&
                !replay.failed() && replay.peek() == cached,
            "physical engine OOM changed committed progress or lost the cached event");
      check(image(runtime) == before,
            "physical engine OOM changed the previous committed runtime state");
      runtime.check_invariants();
      const auto retry = replay.apply_next(runtime);
      check(retry && runtime.sequence() == 2 && replay.progress().sequence == 2,
            "physical replay could not retry the same event after engine OOM");
      check(replay.progress().source_positions.at("replay-source") == 20,
            "physical replay retry did not accept its prepared source offset");
      check(image(runtime) == expected,
            "physical retry differed from the clean execution after owner normalization");
      held.check_unchanged();
      continue;
    }

    check(failures > 0, "physical replay sweep observed no injected ordinary-new failure point");
    check(output && runtime.sequence() == 2 && replay.progress().sequence == 2 &&
              replay.progress().source_positions.at("replay-source") == 20 &&
              !replay.failed(),
          "physical replay accepted sequence and source progress did not advance together");
    check(image(runtime) == expected,
          "successful physical replay differed from clean execution");
    held.check_unchanged();
    runtime.check_invariants();
    return failures;
  }
  throw std::runtime_error("OrderedReplay physical sweep exceeded 8192 points");
}

void sparse_replay_does_not_copy_the_existing_database(const PhysicalPlan& plan) {
  // Stay below the arena's geometric slot-capacity boundary so the check
  // measures intercepted ordinary-new request bytes without that expansion.
  constexpr std::int64_t seeded_rows = 900;
  PhysicalRuntime runtime(plan);
  for (std::int64_t value = 0; value < seeded_rows; ++value) {
    auto committed = runtime.apply(
        {runtime.sequence() + 1, TableId{0}, SetOperation::insert,
         row(value, "existing-row")});
    static_cast<void>(committed);
  }
  const auto encoded = root_line(plan, runtime.sequence() + 1, seeded_rows,
                                 "one-new-row", 9000);
  std::istringstream stream(encoded);
  OrderedReplay replay(io::EventReader(stream, plan.catalog(), {},
                                       progress_at(runtime.sequence())));
  check(replay.peek() != nullptr, "sparse replay fixture did not decode its event");

  allocation_count = 0;
  largest_allocation = 0;
  total_allocation_bytes = 0;
  const auto output = replay.apply_next(runtime);
  const auto replay_allocation_bytes = total_allocation_bytes;
  const auto replay_allocation_count = allocation_count;
  const auto replay_largest_allocation = largest_allocation;
  check(output && runtime.sequence() == seeded_rows + 1 &&
            replay.progress().sequence == seeded_rows + 1,
        "sparse replay did not accept one update over the existing database");
  check(replay_allocation_bytes <
            static_cast<std::size_t>(seeded_rows) * sizeof(Row),
        "single-row replay requested " + std::to_string(replay_allocation_bytes) +
            " bytes through intercepted ordinary new; bound was " +
            std::to_string(static_cast<std::size_t>(seeded_rows) * sizeof(Row)) +
            ", ordinary-new request count=" + std::to_string(replay_allocation_count) +
            ", largest ordinary-new request=" + std::to_string(replay_largest_allocation));
  check(runtime.snapshot().physical.tables[0].size() ==
            static_cast<std::size_t>(seeded_rows + 1),
        "sparse replay lost existing physical rows");
  runtime.check_invariants();
}

DeltaOptions ordered_delta_options(std::size_t spool_rows = 65536,
                                   std::size_t spool_bytes = 64 * 1024 * 1024) {
  DeltaOptions options;
  options.mode = DeltaMode::maintenance;
  options.completion = DeltaCompletion::ordered_replay;
  options.live_maintenance = LiveMaintenance::on_output;
  options.spool_row_limit = spool_rows;
  options.spool_byte_limit = spool_bytes;
  return options;
}

std::vector<std::tuple<std::uint64_t, SetOperation, Row>> drain_delta(
    DeltaRuntime::Epoch& epoch) {
  std::vector<std::tuple<std::uint64_t, SetOperation, Row>> result;
  while (auto record = epoch.next())
    result.emplace_back(record->ordinal, record->operation, crown::storage::export_row(record->tuple.values()));
  return result;
}

struct DeltaCleanImage {
  RuntimeImage runtime;
  std::vector<std::tuple<std::uint64_t, SetOperation, Row>> output;
};

DeltaCleanImage clean_delta_single_event(const PhysicalPlan& plan,
                                         const std::string& encoded,
                                         std::uint64_t starting_sequence) {
  DeltaRuntime runtime(plan, ordered_delta_options());
  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  std::istringstream stream(encoded);
  OrderedReplay replay(io::EventReader(stream, plan.catalog(), {},
                                       progress_at(starting_sequence)));
  auto output = replay.apply_next(runtime);
  check(output.has_value(), "clean delta replay did not return an epoch");
  DeltaCleanImage result;
  result.output = drain_delta(*output);
  result.runtime = image(runtime);
  return result;
}

std::size_t sweep_ordered_delta_apply(const PhysicalPlan& plan) {
  constexpr std::ptrdiff_t max_points = 16384;
  const auto catalog = plan.catalog();
  const auto encoded = root_line(plan, 1, 1, "first", 11);
  const auto expected = clean_delta_single_event(plan, encoded, 0);
  check(expected.runtime.sequence == 1 && expected.runtime.physical[0].size() == 1,
        "delta replay clean fixture did not commit its event");

  std::size_t failures = 0;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    DeltaRuntime runtime(plan, ordered_delta_options());
    static_cast<void>(runtime.set_mode(DeltaMode::delta));
    const auto before = image(runtime);
    std::istringstream stream(encoded);
    OrderedReplay replay(io::EventReader(stream, catalog, {}, progress_at(0)));
    const auto* cached = replay.peek();
    check(cached != nullptr, "delta replay sweep did not prepare its cached event");

    bool failed = false;
    std::optional<DeltaRuntime::Epoch> output;
    {
      FaultScope fault(point);
      try {
        auto accepted = replay.apply_next(runtime);
        if (accepted) output.emplace(std::move(*accepted));
      } catch (const std::bad_alloc&) {
        failed = true;
      }
    }
    if (failed) {
      ++failures;
      check(runtime.sequence() == 0 && replay.progress() == progress_at(0) &&
                !replay.failed() && replay.peek() == cached,
            "delta engine OOM changed committed progress or lost the cached event");
      check(image(runtime) == before,
            "delta engine OOM changed the previous committed physical/support state");
      runtime.check_invariants();
      auto retry = replay.apply_next(runtime);
      check(retry && runtime.sequence() == 1 && replay.progress().sequence == 1,
            "delta replay could not retry the same event after engine OOM");
      check(replay.progress().source_positions.at("replay-source") == 11,
            "delta replay retry did not accept its prepared source offset");
      const auto actual_output = drain_delta(*retry);
      check(actual_output == expected.output && image(runtime) == expected.runtime,
            "delta retry output or runtime state differed from clean execution");
      runtime.check_invariants();
      continue;
    }

    check(failures > 0, "delta replay sweep observed no injected ordinary-new failure point");
    check(output && runtime.sequence() == 1 && replay.progress().sequence == 1 &&
              replay.progress().source_positions.at("replay-source") == 11 &&
              !replay.failed(),
          "delta replay accepted sequence and source progress did not advance together");
    check(drain_delta(*output) == expected.output && image(runtime) == expected.runtime,
          "successful delta replay differed from clean output/state after owner normalization");
    runtime.check_invariants();
    return failures;
  }
  throw std::runtime_error("OrderedReplay delta sweep exceeded 16384 points");
}

void parser_oom_precedes_engine_and_late_truncation_is_sticky() {
  const auto plan = make_root_plan();
  const auto catalog = plan.catalog();
  const auto valid = root_line(plan, 1, 1, "accepted", 10);
  const auto next = root_line(plan, 2, 2, "needs-reader-recreation", 20);
  const auto input = valid + next;
  constexpr std::ptrdiff_t max_points = 4096;
  std::size_t parser_failures = 0;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    PhysicalRuntime runtime(plan);
    std::istringstream stream(input);
    io::EventReader reader(stream, catalog);
    OrderedReplay replay(std::move(reader));
    const auto first = replay.apply_next(runtime);
    check(first && runtime.sequence() == 1 && replay.progress().sequence == 1,
          "parser OOM fixture did not commit its first record");
    auto accepted_progress = progress_at(1);
    accepted_progress.source_positions.emplace("replay-source", 10);

    bool failed = false;
    {
      FaultScope fault(point);
      try {
        static_cast<void>(replay.apply_next(runtime));
      } catch (const std::bad_alloc&) {
        failed = true;
      }
    }
    if (failed) {
      if (replay.failed()) {
        ++parser_failures;
        check(replay.progress() == accepted_progress && runtime.sequence() == 1,
              "parse OOM advanced accepted source progress or began an engine commit");
        check(runtime.snapshot().physical.tables[0] == Relation{row(1, "accepted")},
              "parse OOM altered the previously accepted engine row");
        expect_error([&] { static_cast<void>(replay.peek()); }, "input_failed");

        // The reader consumed some or all of record two. Recovery is explicit:
        // a new stream starts at the unaccepted record with sequence 1 progress.
        std::istringstream replacement(next);
        OrderedReplay restored(io::EventReader(replacement, catalog, {},
                                                 accepted_progress));
        const auto* retry = restored.peek();
        check(retry && retry->update.sequence == 2 &&
                  retry->update.values == row(2, "needs-reader-recreation"),
              "explicitly recreated reader did not recover the unaccepted event");
        check(restored.progress() == accepted_progress,
              "recreated reader advanced progress while preparing its retry");
      } else {
        // Parsing succeeded and an injected ordinary-new request failed in engine
        // apply. The decoded record remains cached for retry on the same reader.
        check(replay.progress() == accepted_progress && runtime.sequence() == 1,
              "engine OOM advanced source progress before commit");
        const auto* cached = replay.peek();
        check(cached && cached->update.sequence == 2 && !replay.failed(),
              "engine OOM failed the reader or discarded its decoded event");
        const auto retry = replay.apply_next(runtime);
        check(retry && runtime.sequence() == 2 && replay.progress().sequence == 2,
              "reader could not retry the decoded event after engine OOM");
        check(replay.progress().source_positions.at("replay-source") == 20,
              "decoded event retry did not commit its source position");
      }
      continue;
    }

    check(parser_failures > 0,
          "ordered parser sweep injected no failure before the engine transition");
    check(runtime.sequence() == 2 && replay.progress().sequence == 2 &&
              replay.progress().source_positions.at("replay-source") == 20,
          "successful parser sweep did not commit sequence and source progress together");
    return;
  }
  throw std::runtime_error("OrderedReplay parser sweep exceeded 4096 points");
}

void late_truncated_binary_and_output_busy_keep_progress() {
  const auto plan = make_root_plan();
  const auto catalog = plan.catalog();
  const auto first = io::write_input_binary(event(1, 1, "first"), catalog);
  const auto second = io::write_input_binary(event(2, 2, "second"), catalog);
  std::istringstream truncated(first + second.substr(0, second.size() - 1));
  InputOptions binary;
  binary.format = InputFormat::binary;
  OrderedReplay broken(io::EventReader(truncated, catalog, binary));
  PhysicalRuntime physical(plan);
  const auto committed = broken.apply_next(physical);
  check(committed && physical.sequence() == 1 && broken.progress().sequence == 1,
        "late binary truncation fixture did not commit its valid prefix");
  expect_error([&] { static_cast<void>(broken.apply_next(physical)); }, "invalid_document");
  check(broken.failed() && broken.progress().sequence == 1 && physical.sequence() == 1 &&
            physical.snapshot().physical.tables[0] == Relation{row(1, "first")},
        "truncated later binary frame changed accepted runtime/progress");

  const auto self_join = make_self_join_plan();
  const auto self_catalog = self_join.catalog();
  const auto contents = edge_line(self_catalog, 1, 1, 2,
                                  io::SourcePosition{"edge-feed", 10}) +
      edge_line(self_catalog, 2, 2, 1, io::SourcePosition{"edge-feed", 20}) +
      edge_line(self_catalog, 3, 1, 1, io::SourcePosition{"edge-feed", 30});
  std::istringstream stream(contents);
  OrderedReplay replay(io::EventReader(stream, self_catalog));
  auto options = ordered_delta_options();
  DeltaRuntime delta(self_join, options);
  static_cast<void>(delta.set_mode(DeltaMode::delta));
  {
    auto output = replay.apply_next(delta);
    check(output.has_value(), "output-busy fixture omitted its first epoch");
    static_cast<void>(drain_delta(*output));
  }
  auto held_output = replay.apply_next(delta);
  check(held_output && held_output->remaining() > 0,
        "output-busy fixture did not retain a visible delta epoch");
  const auto* cached = replay.peek();
  check(cached && cached->update.sequence == 3,
        "output-busy fixture did not cache the following event");
  expect_error([&] { static_cast<void>(replay.apply_next(delta)); }, "runtime_busy");
    check(replay.peek() == cached && replay.progress().sequence == 2 &&
            replay.progress().source_positions.at("edge-feed") == 20 &&
            delta.sequence() == 2 && !replay.failed(),
        "output busy rejection skipped or failed the cached source record");
  static_cast<void>(drain_delta(*held_output));
  auto retried = replay.apply_next(delta);
  check(retried && replay.progress().sequence == 3 && delta.sequence() == 3,
        "the same output-blocked event did not apply after output was drained");
  check(replay.progress().source_positions.at("edge-feed") == 30,
        "retried output-blocked event did not accept its source offset");
  static_cast<void>(drain_delta(*retried));
}

void alias_fanout_quota_rollback_retains_cached_input() {
  const auto plan = make_self_join_plan();
  const auto catalog = plan.catalog();
  auto options = ordered_delta_options(0);
  DeltaRuntime runtime(plan, options);
  // Seed both aliases in maintenance mode, then start ordered output mode.
  auto first = runtime.apply({1, TableId{0}, SetOperation::insert,
                              {std::int64_t{1}, std::int64_t{2}}});
  first.discard();
  auto second = runtime.apply({2, TableId{0}, SetOperation::insert,
                               {std::int64_t{2}, std::int64_t{1}}});
  second.discard();
  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  const auto before = image(runtime);

  const auto source_event = io::write_input_json(
      {{3, TableId{0}, SetOperation::insert, {std::int64_t{1}, std::int64_t{1}}},
       io::SourcePosition{"fanout-source", 31}}, catalog) + "\n";
  std::istringstream stream(source_event);
  OrderedReplay replay(io::EventReader(stream, catalog, {}, progress_at(2)));
  const auto* cached = replay.peek();
  check(cached && cached->update.sequence == 3,
        "alias quota fixture did not prepare the next source event");
  expect_error([&] { static_cast<void>(replay.apply_next(runtime)); }, "resource_limit");
  check(replay.peek() == cached && replay.progress() == progress_at(2) &&
            runtime.sequence() == 2 && runtime.ready() && !replay.failed(),
        "alias-fanout quota rollback lost the cached event or advanced progress");
  check(image(runtime) == before,
        "alias-fanout quota rollback changed the previous engine state");
  runtime.check_invariants();
}

}  // namespace

int main() {
  try {
    const Fixture fixture;
    const auto json_construction = sweep_reader_construction(fixture, InputFormat::jsonl);
    const auto binary_construction = sweep_reader_construction(fixture, InputFormat::binary);
    const auto csv_construction = sweep_reader_construction(fixture, InputFormat::csv);
    const auto json_peek = sweep_reader_peek(fixture, InputFormat::jsonl);
    const auto binary_peek = sweep_reader_peek(fixture, InputFormat::binary);
    const auto csv_peek = sweep_reader_peek(fixture, InputFormat::csv);
    acknowledgement_and_lifetime_are_noalloc(fixture);
    sweep_catalog_digest_and_codecs(fixture);

    const auto root = make_root_plan();
    const auto physical_failures = sweep_ordered_physical_apply(root);
    sparse_replay_does_not_copy_the_existing_database(root);
    const auto delta_failures = sweep_ordered_delta_apply(root);
    parser_oom_precedes_engine_and_late_truncation_is_sticky();
    late_truncated_binary_and_output_busy_keep_progress();
    alias_fanout_quota_rollback_retains_cached_input();

    std::cout << "Ingestion ordinary-new fault points: constructor json/binary/csv="
              << json_construction << '/' << binary_construction << '/' << csv_construction
              << ", peek=" << json_peek << '/' << binary_peek << '/' << csv_peek
              << ", physical replay=" << physical_failures
              << ", delta replay=" << delta_failures << '\n';
  } catch (const std::exception& error) {
    std::cerr << "ingestion exception test failed: " << error.what() << '\n';
    return 1;
  }
}
