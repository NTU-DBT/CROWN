#pragma once

#include "crown/io/batch.hpp"
#include "crown/runtime/update_view.hpp"
#include "crown/runtime/update_pattern.hpp"
#include "crown/resource/ownership.hpp"
#include "crown/recovery/image.hpp"
#include <algorithm>
#include <span>
#include <memory>

namespace crown::resource {class MemoryAccount;}
namespace crown::program {struct Catalog;}
namespace crown::recovery::detail {struct SessionImageAccess;}

namespace crown::runtime {
// The original modes order labels. Physical modes order live full-row lifetimes,
// whose birth IDs survive removing the first of several labels for one row.
enum class WindowFifoPolicy { global=0, per_relation=1, physical_global=2, physical_per_relation=3, unrestricted=4 };
[[nodiscard]] constexpr const char* window_fifo_name(WindowFifoPolicy value) noexcept {
  switch(value) {
    case WindowFifoPolicy::global:return "global";
    case WindowFifoPolicy::per_relation:return "per_relation";
    case WindowFifoPolicy::physical_global:return "physical_global";
    case WindowFifoPolicy::physical_per_relation:return "physical_per_relation";
    case WindowFifoPolicy::unrestricted:return "unrestricted";
  }
  return "unknown";
}
struct WindowOptions {
  std::vector<TableId> managed_tables;
  std::uint64_t width=1;
  WindowFifoPolicy fifo=WindowFifoPolicy::global;
  std::size_t max_labels=65536;
  // Native retained payload/index descriptors and active watermark storage.
  // The query account additionally funds real links, framing and preparation.
  std::size_t max_accounted_bytes=64*1024*1024;
  // Abstract index visits/row-column comparisons, not CPU instructions;
  // tree search cost, scalar byte comparisons and allocations are additional.
  std::uint64_t command_work_limit=1000000;
};
// Immutable options collection. Copies share actual original-account control
// and capacity storage, including after the controller/session is destroyed.
class WindowTables {
  struct Data;
 public:
  using const_iterator=std::span<const TableId>::iterator;
  WindowTables() noexcept=default;
  [[nodiscard]] static WindowTables copy_of(const resource::MemoryAccount&,const std::vector<TableId>&);
  [[nodiscard]] static WindowTables copy_of(const resource::MemoryAccount&,std::span<const TableId>,std::size_t capacity);
  [[nodiscard]] std::size_t size() const noexcept;
  [[nodiscard]] std::size_t capacity() const noexcept;
  [[nodiscard]] const TableId* data() const noexcept;
  [[nodiscard]] bool empty() const noexcept {return size()==0;}
  [[nodiscard]] const TableId& operator[](std::size_t i) const noexcept {return data()[i];}
  [[nodiscard]] const_iterator begin() const noexcept {return std::span<const TableId>(data(),size()).begin();}
  [[nodiscard]] const_iterator end() const noexcept {return std::span<const TableId>(data(),size()).end();}
  [[nodiscard]] bool operator==(const WindowTables& other) const noexcept {
    return std::equal(begin(),end(),other.begin(),other.end());
  }
  template<class Allocator> [[nodiscard]] bool operator==(const std::vector<TableId,Allocator>& other) const noexcept {
    return std::equal(begin(),end(),other.begin(),other.end());
  }
 private:
  explicit WindowTables(std::shared_ptr<const Data> data) noexcept:data_(std::move(data)) {}
  std::shared_ptr<const Data> data_;
};
struct AccountedWindowOptions {
  // Ordinary copies share managed IDs; explicit account imports copy capacity.
  // These settings still require controller/catalog admission checks.
  WindowTables managed_tables;
  std::uint64_t width;
  WindowFifoPolicy fifo;
  std::size_t max_labels,max_accounted_bytes;
  std::uint64_t command_work_limit;
  AccountedWindowOptions(const resource::MemoryAccount&,const WindowOptions&);
  AccountedWindowOptions(const resource::MemoryAccount&,const AccountedWindowOptions&);
 private:
  friend struct recovery::detail::SessionImageAccess;
  AccountedWindowOptions()=default;
};
// Canonical state is an explicit external DTO. Operational state owns compact
// native rows, accounted nodes and a separate native active command internally.
struct WindowLabel {
  std::uint64_t label;
  TableId table;
  Row values;
  std::uint64_t timestamp,deadline,count_id;
  bool operator==(const WindowLabel&) const = default;
};
struct WindowCount {
  std::uint64_t id;
  TableId table;
  Row values;
  std::uint64_t count;
  bool operator==(const WindowCount&) const = default;
};
struct WindowActiveCommand {
  std::uint64_t sequence,watermark;
  std::vector<std::uint64_t> expiration_labels;
  std::size_t completed_steps=0,total_steps=0;
  std::uint64_t accounted_work=0;
  bool operator==(const WindowActiveCommand&) const = default;
};
struct WindowMetrics {
  std::size_t live_labels=0,distinct_rows=0,accounted_bytes=0;
  std::uint64_t last_command_work=0;
  bool operator==(const WindowMetrics&) const = default;
};
struct WindowProgress {
  std::uint64_t completed_command_sequence=0,physical_sequence=0,completed_watermark=0,last_label=0;
  std::optional<std::uint64_t> active_command_sequence;
  std::size_t completed_steps=0,total_steps=0;
  bool operator==(const WindowProgress&) const = default;
};
struct WindowCanonicalState {
  std::vector<WindowLabel> labels;
  std::vector<WindowCount> counts;
  std::vector<std::pair<std::uint64_t,std::uint64_t>> expiration_index;
  std::vector<std::uint64_t> global_fifo;
  std::vector<std::pair<TableId,std::vector<std::uint64_t>>> relation_fifo;
  std::uint64_t completed_command_sequence=0,physical_sequence=0,completed_watermark=0,last_label=0;
  std::optional<WindowActiveCommand> active_command;
  WindowMetrics metrics;
  bool operator==(const WindowCanonicalState&) const = default;
};
struct WindowStateLimits {
  std::uint64_t work=16*1024*1024;
  std::size_t labels=65536,counts=65536;
};
struct WindowCheckpointLabel {
  std::uint64_t label;
  TableId table;
  storage::AccountedRow values;
  std::uint64_t timestamp,deadline,count_id;
};
struct WindowCheckpointCount {
  std::uint64_t id;
  TableId table;
  storage::AccountedRow values;
  std::uint64_t count;
};
// Native quiescent window state for the session envelope. FIFO/expiration
// directories are derived from validated labels on restore. Count identity,
// including IDs whose original label expired, and all progress are retained.
struct WindowCheckpoint {
  // Native row entries are move-only; checkpoint_state() explicitly clones them.
  // Mutable fields are not source/base matching or durable publication authority.
  AccountedWindowOptions options;
  WindowProgress progress;
  recovery::ImageVector<WindowCheckpointLabel> labels;
  recovery::ImageVector<WindowCheckpointCount> counts;
  std::array<char,64> catalog_sha256{};
  std::uint64_t last_command_work=0,work=0;
  bool stopped=false;
  WindowCheckpoint(const resource::MemoryAccount& account,AccountedWindowOptions value)
      :options(std::move(value)),labels(recovery::image_allocator<WindowCheckpointLabel>(account)),
       counts(recovery::image_allocator<WindowCheckpointCount>(account)) {}
};
// Window policy selects label FIFO, full-row lifetime FIFO or unrestricted order.
// Labels for the same row share set presence; managed tables start empty (checked by session).
class WindowController {
  struct Impl;
 public:
  class Prepared {
    // Owns staged rows/nodes but borrows the controller through a raw pointer.
    // Moving transfers that preparation; it does not retain controller lifetime.
   public:
    ~Prepared();
    Prepared(Prepared&&) noexcept;
    Prepared& operator=(Prepared&&) noexcept;
    Prepared(const Prepared&)=delete;
    Prepared& operator=(const Prepared&)=delete;
    [[nodiscard]] const std::optional<PhysicalUpdateView>& update() const noexcept;
    [[nodiscard]] bool completes_command() const noexcept;
    // Must follow successful engine commit, or the explicit metadata barrier.
    // The controller must outlive Prepared; only one Prepared may be live.
    // Destroy Prepared before stopping the controller.
    void publish() noexcept;
   private:
    struct Data;
    explicit Prepared(resource::AccountedUnique<Data>) noexcept;
    resource::AccountedUnique<Data> data_;
    friend class WindowController;
  };
  WindowController(Catalog catalog,WindowOptions options);
  WindowController(const resource::MemoryAccount&,const program::Catalog&,const WindowOptions&);
  WindowController(const resource::MemoryAccount&,const program::Catalog&,const WindowCheckpoint&,WindowStateLimits={});
  [[nodiscard]] WindowCheckpoint checkpoint_state(WindowStateLimits={}) const;
  ~WindowController();
  WindowController(const WindowController&)=delete;
  WindowController& operator=(const WindowController&)=delete;
  [[nodiscard]] Prepared prepare(const io::WindowCommand&,std::uint64_t next_physical_sequence);
  [[nodiscard]] Prepared prepare_view(const io::WindowCommandView&,std::uint64_t next_physical_sequence);
  [[nodiscard]] WindowCanonicalState canonical_state() const;
  [[nodiscard]] WindowMetrics metrics() const noexcept;
  [[nodiscard]] WindowProgress progress() const noexcept;
  // Terminal: release expansion storage but retain committed prefix scalars.
  void stop() noexcept;
  [[nodiscard]] const AccountedWindowOptions& options() const noexcept;
 private:
  friend class QuerySession;
  [[nodiscard]] bool manages(TableId) const noexcept;
  [[nodiscard]] Prepared prepare_pattern_view(const io::WindowCommandView&,std::uint64_t,
      const patterns::Declaration*,PatternViolation*);
#ifdef CROWN_RUNTIME_TESTING
  friend class RuntimeTestProbe;
#endif
  std::shared_ptr<Impl> data_;
};
}  // namespace crown::runtime
