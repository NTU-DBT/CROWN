#pragma once

#include "crown/io/batch.hpp"
#include "crown/runtime/window.hpp"
#include "crown/runtime/delta.hpp"

namespace crown::runtime {
enum class SessionBegin { pending, would_block, end };
enum class SessionState { created, running, paused, stopped, dropped };
enum class SessionPhase { ready, pending, paused_pending, draining, prepared, output };
struct SessionStatus {
  SessionState state;
  SessionPhase phase;
  std::uint64_t committed_sequence;
  bool input_failed;
  bool end_of_input;
  std::optional<std::uint64_t> pending_sequence;
  std::uint64_t pending_work;
  std::size_t output_remaining;
  std::optional<io::QueueStats> queue;
  std::optional<WindowProgress> window;
  std::optional<std::uint64_t> pending_command_sequence;
};
struct SnapshotLimits {
  std::size_t rows=65536;
  // Retained vector slots, row Value capacity, string capacity+1 and a
  // 64-byte Decimal coefficient allowance. Query/layout/progress metadata,
  // allocator overhead, one cursor-produced row and transient old/new vector
  // allocations during growth are additional costs. This is not a peak cap.
  std::size_t bytes=64*1024*1024;
  ResultCursorOptions cursor;
};
struct SessionOptions {
  io::InputOptions input;
  DeltaOptions delta;
  SnapshotLimits snapshot;
  std::shared_ptr<const DeclaredBenchmarkContext> declared_benchmark;
};
enum class SessionInputKind { owned_stream, typed_physical, typed_window };
// Constructed once during session admission, never copied by observation hooks.
// Exact native bytes remain native bytes; strict text encoding is an export duty.
struct SessionRunContext {
  SessionInputKind input_kind;
  io::InputOptions input;
  std::optional<io::QueueLimits> queue;
  std::optional<WindowOptions> window;
  SnapshotLimits snapshot;
  InitializationContext initialization;
  DeltaOptions requested_delta;
  DeltaMode resolved_mode;
  DeltaCompletion resolved_completion;
};
struct SessionSnapshot {
  std::uint64_t sequence;
  io::InputProgress progress;
  storage::TupleLayout layout;
  std::vector<storage::Tuple> rows;
  std::size_t accounted_bytes=0;
  std::optional<WindowProgress> window;
};

// Synchronous, creator-thread writer ownership. Owns the input stream and all
// runtime/pending/output resources. Never exposes an internal token or lease.
// Accepted sequence starts at zero; initialization overloads preserve supplied rows.
// Destruction requires exclusive ownership, as for its owned input stream.
class QuerySession {
 public:
  [[nodiscard]] static std::unique_ptr<QuerySession> create(PhysicalPlan plan,
      std::unique_ptr<std::istream> input,SessionOptions options={});
  [[nodiscard]] static std::unique_ptr<QuerySession> create(PhysicalPlan plan,const Database& initial,
      std::unique_ptr<std::istream> input,SessionOptions options={},BuildOptions build={});
  [[nodiscard]] static std::unique_ptr<QuerySession> create_typed(PhysicalPlan plan,
      io::QueueLimits limits={},SessionOptions options={});
  [[nodiscard]] static std::unique_ptr<QuerySession> create_typed(PhysicalPlan plan,const Database& initial,
      io::QueueLimits limits={},SessionOptions options={},BuildOptions build={});
  [[nodiscard]] static std::unique_ptr<QuerySession> create_windowed(PhysicalPlan plan,WindowOptions window,
      io::QueueLimits limits={},SessionOptions options={});
  [[nodiscard]] static std::unique_ptr<QuerySession> create_windowed(PhysicalPlan plan,const Database& initial,
      WindowOptions window,io::QueueLimits limits={},SessionOptions options={},BuildOptions build={});
  ~QuerySession();
  QuerySession(const QuerySession&)=delete;
  QuerySession& operator=(const QuerySession&)=delete;
  QuerySession(QuerySession&&)=delete;
  QuerySession& operator=(QuerySession&&)=delete;
  [[nodiscard]] SessionStatus status() const;
  [[nodiscard]] std::shared_ptr<const SessionRunContext> run_context() const;
  [[nodiscard]] ObservationSnapshot observations() const;
  [[nodiscard]] std::optional<CursorObservation> last_cursor_observation() const;
  [[nodiscard]] ObservationTrace observation_trace() const;
  [[nodiscard]] io::InputProgress progress() const;
  void start();
  void pause();
  // Admission is allowed before start, but not while paused or terminal.
  [[nodiscard]] io::Admission enqueue(io::TransportBatch& batch);
  void finish_input();
  [[nodiscard]] SessionBegin begin_next_result();
  // False means validated EOF; open-empty typed input throws input_would_block.
  // Window metadata-only work uses an explicit private preparation barrier.
  [[nodiscard]] bool begin_next();
  [[nodiscard]] DeltaStep step();
  // Prepared only. All work after engine publication is nonthrowing.
  void commit();
  void start_drain();
  // Complete/discard only the current input/output; never reads another event.
  // May finish a paused epoch while leaving admission paused.
  void drain();
  [[nodiscard]] std::optional<SignedResult> next_output();
  // Actual committed results, including epoch-zero Boolean/nullary results.
  // Allowed with committed unread output; rejected with private pending work.
  [[nodiscard]] SessionSnapshot snapshot(std::optional<SnapshotLimits> limits=std::nullopt) const;
  [[nodiscard]] std::optional<WindowCanonicalState> window_state() const;
  // Stop is terminal; abort unpublished work, release source/output buffers,
  // retain committed runtime for snapshots. Drop releases runtime state too.
  // Public guards can report thread/reentrancy errors; cleanup never allocates.
  void stop();
  void drop();
 private:
#ifdef CROWN_RUNTIME_TESTING
  friend class RuntimeTestProbe;
#endif
  struct Impl;
  explicit QuerySession(std::unique_ptr<Impl> data) noexcept;
  std::unique_ptr<Impl> data_;
};
}  // namespace crown::runtime
