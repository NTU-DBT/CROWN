#pragma once

#include "crown/runtime/sql_aggregate.hpp"

namespace crown::runtime::topk {
enum class Direction { ascending, descending };
enum class NullOrder { first, last };
// Zero-based SQL output field. NULL placement is independent of direction.
// Empty order means identity order; repeated keys are allowed.
struct Key {
  std::size_t field;
  Direction direction = Direction::ascending;
  NullOrder nulls = NullOrder::last;
};
struct Limits {
  std::uint64_t candidates = 65536; // Compressed output tuples or aggregate groups.
  std::uint64_t work = 1000000; // Validation, selection and comparison/field/byte units.
  std::uint64_t producer_work = 1000000; // One separate native scan or group-render grant.
};
// Rows use the full nullable output tuple as identity. Aggregates keep the full
// group key, including keys omitted from the output. Identity is query-scoped.
// Multiplicity compresses selected copies [0,m); no duplicate expansion occurs.
struct Entry {
  aggregate::Tuple identity, values;
  std::uint64_t multiplicity;
};
struct Metrics {
  std::uint64_t work = 0, candidates = 0, comparisons = 0, fields = 0, scalar_bytes = 0;
};
using Program = std::variant<frontend::SqlRowsProgram, frontend::SqlAggregateProgram>;
// Owning compact output and genuine immutable schema retain the original query
// account after runtime teardown. Public edits confer no native/recovery authority.
struct Snapshot {
  std::uint64_t sequence, requested_k, selected_rows = 0;
  Program program;
  aggregate::OutputVector<Entry> entries;
  Metrics metrics;
  Snapshot(const resource::MemoryAccount&, std::uint64_t, std::uint64_t, Program);
};
} // namespace crown::runtime::topk

namespace crown::runtime {
// Explicit exact snapshot recomputation: collect N compressed tuples/groups,
// sort by requested fields then identity ASC NULLS FIRST, and take k logical
// copies. Scratch is O(N); retained entry storage is O(M) selected identities.
// No update hook, cached ranking, expanded bag, P10 bound or SQL clause is added.
// Serialize calls with the owner. Require ready() even for k=0; order validation
// precedes producer creation. k=0 allocates no candidate/result storage.
// Candidate, tuple and result storage uses the original account; ordinary
// diagnostics/exception-runtime storage is separate. Failure releases private
// state and reader leases; committed query state/sequence stay unchanged.
// Observation and cumulative/peak allocation counters need not be restored.
// No partial result escapes.
[[nodiscard]] topk::Snapshot snapshot_topk(const SqlRowsRuntime&, std::span<const topk::Key>,
    std::uint64_t k, topk::Limits = {});
[[nodiscard]] topk::Snapshot snapshot_topk(const SqlAggregateRuntime&, std::span<const topk::Key>,
    std::uint64_t k, topk::Limits = {});
} // namespace crown::runtime
