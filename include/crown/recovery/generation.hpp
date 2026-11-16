#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <string_view>
#include <optional>

namespace crown::recovery {
enum class GenerationStage : std::uint8_t {
  path,open_directory,open_lock,stat_file,lock_file,open_root,read_data,
  entropy,create_temporary,write_data,sync_file,close_file,link_file,
  rename_root,unlink_temporary,unlink_candidate,sync_directory,state,
  open_retirement,unlink_history,unlink_retirement
};
enum class GenerationTarget : std::uint8_t {lock,root,checkpoint,journal,retirement,plan};
enum class GenerationFault : std::uint8_t {io,limit,path,not_regular,busy,changed,truncated,corrupt,binding,state};
// Concerns root selection, not unselected candidate/temporary creation. Unknown
// requires releasing the old owner and reopening the authoritative root.
enum class GenerationOutcome : std::uint8_t {unchanged,unknown,durable};
class GenerationFailure final:public std::exception {
 public:
  GenerationFailure(GenerationFault fault,GenerationStage stage,GenerationOutcome outcome,
      int error=0,bool cleanup=false) noexcept:fault_(fault),stage_(stage),outcome_(outcome),error_(error),cleanup_(cleanup) {}
  [[nodiscard]] GenerationFault fault() const noexcept {return fault_;}
  [[nodiscard]] GenerationStage stage() const noexcept {return stage_;}
  [[nodiscard]] GenerationOutcome outcome() const noexcept {return outcome_;}
  [[nodiscard]] int native_error() const noexcept {return error_;}
  [[nodiscard]] bool temporary_cleanup_failed() const noexcept {return cleanup_;}
  [[nodiscard]] const char* what() const noexcept override {return "generation operation failed";}
 private:
  GenerationFault fault_;GenerationStage stage_;GenerationOutcome outcome_;int error_;bool cleanup_;
};
struct GenerationLimits {
  std::size_t path_bytes=4095,chunk_bytes=1024*1024;
  std::uint64_t operations=1'000'000,checkpoint_bytes=128*1024*1024,validation_work=1024*1024*1024;
  std::uint64_t plan_bytes=64*1024*1024;
};
struct GenerationDeliveryAnchor {
  std::array<char,32> sink_id{};
  std::uint64_t sequence=0,bytes=0;
  std::array<char,64> content_sha256{};
  bool operator==(const GenerationDeliveryAnchor&) const=default;
};
struct GenerationRoot {
  std::array<char,32> query_id{};
  std::uint64_t generation=0,first_generation=0;
  std::array<char,64> checkpoint_sha256{};
  std::uint64_t physical_sequence=0,command_sequence=0;
  std::optional<GenerationDeliveryAnchor> delivery=std::nullopt;
  // v3 binds a self-contained descriptor at this generation's own .plan path.
  // Rotation retains a self-contained descriptor; retirement needs no older .plan.
  std::optional<std::array<char,64>> plan_sha256=std::nullopt;
  bool operator==(const GenerationRoot&) const=default;
};
// Checksummed CROWNGR1: v1 is the 212-byte native selection; v2 adds the durable
// checkpoint delivery anchor (324 bytes). v3 adds a required descriptor hash,
// with optional delivery anchor (276/388 bytes). Inspection grants no mutation or
// retirement authority. Rotation retains older pairs until verified retirement.
[[nodiscard]] GenerationRoot inspect_generation_root(std::string_view);
inline constexpr std::size_t generation_root_size=212;
inline constexpr std::size_t generation_root_delivery_size=324;
inline constexpr std::size_t generation_root_plan_size=276;
inline constexpr std::size_t generation_root_plan_delivery_size=388;
} // namespace crown::recovery
