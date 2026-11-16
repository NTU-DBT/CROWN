#pragma once
#include "crown/recovery/generation.hpp"
#include "session_file_detail.hpp"
#include "crown/recovery/local_sink.hpp"
#include <optional>

namespace crown::recovery::sql_aggregate { class Session; }
namespace crown::recovery::sql_rows { class Session; }
namespace crown::recovery::detail {
struct RetirementIntent {
  GenerationRoot before;
  sink::Header sink;
  std::uint64_t acknowledged_generation=0,acknowledged_sequence=0;
  bool operator==(const RetirementIntent&) const=default;
};
inline constexpr std::size_t retirement_intent_size=724;
inline constexpr std::size_t retirement_plan_intent_size=788;
struct RetirementBytes {
  std::array<char,retirement_plan_intent_size> bytes{};
  std::size_t length=retirement_intent_size;
  [[nodiscard]] const char* data() const noexcept {return bytes.data();}
  [[nodiscard]] std::size_t size() const noexcept {return length;}
};
[[nodiscard]] RetirementIntent inspect_retirement_intent(std::string_view);
[[nodiscard]] RetirementBytes encode_retirement_intent(const RetirementIntent&);
// Internal single-root authority. Public metadata cannot construct/import it.
// Fixed path/codec state can be built on the stack before query admission, then
// moved into that receiving account without another filesystem operation.
class GenerationOwner {
 public:
  // Session callers prepare the matching WAL and native state before selection.
  // This owner retains the actual root lock and candidate file identities.
  GenerationOwner(std::string_view,const std::array<char,32>&,bool create,GenerationLimits);
  ~GenerationOwner()=default;
  GenerationOwner(const GenerationOwner&)=delete;GenerationOwner& operator=(const GenerationOwner&)=delete;
  GenerationOwner(GenerationOwner&&) noexcept;
  GenerationOwner& operator=(GenerationOwner&&)=delete;
  [[nodiscard]] const GenerationRoot& selected() const noexcept {return selected_;}
  [[nodiscard]] bool has_selection() const noexcept {return selected_.generation!=0;}
  [[nodiscard]] bool selection_attempted() const noexcept {return attempted_;}
  [[nodiscard]] std::uint64_t operations() const noexcept {return operations_;}
  [[nodiscard]] std::uint64_t validation_work() const noexcept {return work_;}
  [[nodiscard]] const std::optional<RetirementIntent>& retirement() const noexcept {return retirement_;}
  [[nodiscard]] std::array<char,4096> checkpoint_path(std::uint64_t) const;
  [[nodiscard]] std::array<char,4096> journal_path(std::uint64_t) const;
  [[nodiscard]] std::array<char,4096> plan_path(std::uint64_t) const;
  [[nodiscard]] ImageVector<char> read_plan(const resource::MemoryAccount&);
  // Opaque selected bytes only: native/SQL decoding remains in the caller.
  // Hash, bounded I/O, regular-file identity, EOF and root continuity precede
  // return. Empty checkpoint payloads are allowed by this lower file boundary.
  [[nodiscard]] ImageVector<char> read_checkpoint(const resource::MemoryAccount&);
  // Before a rotation, remove only the next unselected candidate. Never called
  // for initial creation or selected/older generations. Root lock stays held.
  void prepare_next(std::uint64_t);
  void publish_checkpoint(std::uint64_t,std::string_view);
  void publish_plan(std::uint64_t,std::string_view);
  void publish_root(const GenerationRoot&);
  // Resume only the recorded range, with the actual validated local owner.
  void validate_retirement(const sink::File&) const;
  void retire_history(const sink::Receipt&,std::string_view checkpoint_bytes,const resource::MemoryAccount&);
 private:
  friend class ::crown::recovery::sql_aggregate::Session; // Final fixed root continuity check.
  friend class ::crown::recovery::sql_rows::Session; // Same opaque root check for row recovery.
  [[nodiscard]] std::array<char,4096> path(std::uint64_t,std::string_view) const;
  [[nodiscard]] std::array<char,256> name(std::uint64_t,std::string_view) const;
  [[nodiscard]] GenerationRoot read_root(bool missing_ok,bool adopt);
  [[nodiscard]] ImageVector<char> read_selected(const resource::MemoryAccount&,bool plan);
  void read_retirement();
  void select_retirement_floor();
  void confirm_checkpoint(std::string_view);
  [[nodiscard]] std::array<char,256> retirement_name() const;
  void publish(std::string_view,const char*,bool replace,bool selection);
  void consume_work(std::uint64_t);
  void healthy() const;
  bool cleanup_temporary(const char*) noexcept;
  std::int64_t call(GenerationStage,std::size_t=0,int=-1,const char* =nullptr,
      const char* =nullptr,void* =nullptr,std::uint64_t=0,struct stat* =nullptr,bool emergency_cleanup=false);
  std::int64_t checked(GenerationStage,std::size_t=0,int=-1,const char* =nullptr,
      const char* =nullptr,void* =nullptr,std::uint64_t=0,struct stat* =nullptr);
  void transfer(bool,int,char*,std::size_t,std::uint64_t=0);
  GenerationLimits limits_;
  FileDescriptor directory_,lock_;
  std::array<char,4096> root_path_{};
  std::array<char,256> root_name_{};
  GenerationRoot selected_;
  std::optional<RetirementIntent> retirement_;
  std::array<char,32> query_id_{};
  std::uint64_t operations_=0,work_=0;
  std::uint64_t candidate_generation_=0;
  std::array<char,64> candidate_sha256_{};
  std::uint64_t candidate_plan_generation_=0;
  std::array<char,64> candidate_plan_sha256_{};
  GenerationOutcome outcome_=GenerationOutcome::unchanged;
  GenerationTarget target_=GenerationTarget::root;
  bool attempted_=false;
};
} // namespace crown::recovery::detail
