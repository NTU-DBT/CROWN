#pragma once

#include "crown/io/ingest.hpp"
#include "crown/io/input_view.hpp"
#include "crown/io/input_progress.hpp"
#include <list>

namespace crown {class CompiledProgram;}
namespace crown::runtime {class QuerySession;}
namespace crown::io {
struct QueueCheckpoint;
struct SourceStateLimits;
// Event time is an adapter uint64 domain, independent of SQL scalar types and
// source offsets. Insertion labels increase strictly for the session lifetime.
struct WindowInsert {
  std::uint64_t label;
  TableId table;
  Row values;
  std::uint64_t timestamp;
};
struct WindowCommand {
  std::uint64_t sequence;
  std::variant<WindowInsert,WindowWithdraw,AdvanceWatermark> command;
  std::optional<SourcePosition> source_position;
};
using InputItem=std::variant<InputEvent,WindowCommand>;
struct BatchLimits {
  std::size_t events=65536;
  std::size_t bytes=64*1024*1024;
};
struct QueueLimits {
  std::size_t batches=64;
  std::size_t events=65536;
  std::size_t bytes=64*1024*1024;
  bool operator==(const QueueLimits&) const=default;
};
enum class Admission { accepted, full };
enum class QueueMode { physical, window };
// Counts cover the retained queued graph; schema/options, accepted positions
// and account control have separate original-account ownership.
struct QueueStats {
  std::size_t batches=0,events=0,accounted_bytes=0;
  bool closed=false,failed=false;
  bool operator==(const QueueStats&) const = default;
};

// A transport batch preserves every event barrier. No cancellation/coalescing.
// Bounds owned list nodes, Value slots, string capacities and Decimal allowance;
// allocator metadata, constructor input, and temporary allocations are separate.
class TransportBatch {
 public:
  explicit TransportBatch(std::vector<InputItem> items,BatchLimits limits={});
  ~TransportBatch();
  TransportBatch(const TransportBatch&)=delete;
  TransportBatch& operator=(const TransportBatch&)=delete;
  TransportBatch(TransportBatch&&) noexcept;
  TransportBatch& operator=(TransportBatch&&) noexcept;
  [[nodiscard]] bool empty() const noexcept;
  [[nodiscard]] std::size_t size() const noexcept;
  [[nodiscard]] std::size_t accounted_bytes() const noexcept;
 private:
  struct Data;
  std::unique_ptr<Data> data_;
  friend class TypedQueue;
};

// Closed implementation-owned source for QuerySession. The head remains owned
// and counted through pending work/whole watermark expansion. Head semantic
// errors are sticky; allocation failure and engine rejection permit retry.
class TypedQueue {
 public:
  TypedQueue(CatalogSource catalog,QueueMode mode,QueueLimits limits={},InputLimits input_limits={});
  // Execution admission derives both metadata and memory authority from the
  // already admitted program. No nested queue allowance is created.
  TypedQueue(const CompiledProgram&,QueueMode,QueueLimits limits={},InputLimits input_limits={});
  TypedQueue(const CompiledProgram&,const QueueCheckpoint&);
  TypedQueue(const CompiledProgram&,const QueueCheckpoint&,const SourceStateLimits&);
  [[nodiscard]] QueueCheckpoint checkpoint_state() const;
  [[nodiscard]] QueueCheckpoint checkpoint_state(const SourceStateLimits&) const;
  ~TypedQueue();
  TypedQueue(const TypedQueue&)=delete;
  TypedQueue& operator=(const TypedQueue&)=delete;
  TypedQueue(TypedQueue&&) noexcept;
  TypedQueue& operator=(TypedQueue&&) noexcept;
  // Only success imports ownership. Full/failure preserves offered data,
  // membership and accepted progress; account preparation history may advance.
  [[nodiscard]] Admission enqueue(TransportBatch& batch);
  void finish() noexcept;
  [[nodiscard]] const InputItemView* peek();
  void acknowledge() noexcept;
  [[nodiscard]] const AccountedInputProgress& progress() const;
  [[nodiscard]] bool failed() const noexcept;
  [[nodiscard]] bool closed() const noexcept;
  [[nodiscard]] bool empty() const noexcept;
  [[nodiscard]] QueueStats stats() const noexcept;
  [[nodiscard]] AccountedInputProgress close() noexcept;
 private:
  friend class runtime::QuerySession;
  [[nodiscard]] std::uint64_t stage_replay(const InputItemView&,const SourceStateLimits&);
  TypedQueue(const resource::MemoryAccount&,CatalogSource,QueueMode,QueueLimits,InputLimits,bool admitted);
  TypedQueue(const resource::MemoryAccount&,CatalogSource,const QueueCheckpoint&,const SourceStateLimits&,bool admitted);
  struct Data;
  resource::AccountedUnique<Data> data_;
};
}  // namespace crown::io
