#pragma once

#include "crown/resource/owner_allocator.hpp"
#include "crown/storage/accounted_row.hpp"
#include <exception>
#include <span>
#include <vector>

namespace crown::recovery {
inline constexpr resource::MemoryAttribution image_owner{resource::MemoryOwnerKind::recovery,0};
template<class T> using ImageVector=std::vector<T,resource::OwnerAllocator<T>>;
template<class T> [[nodiscard]] auto image_allocator(const resource::MemoryAccount& account) {
  return resource::OwnerAllocator<T>(account,resource::MemoryPurpose::recovery_log,image_owner);
}
enum class ImageFault { limit, work, corrupt, version, binding, scalar };
class ImageFailure final:public std::exception {
 public:
  explicit ImageFailure(ImageFault fault) noexcept:fault_(fault) {}
  [[nodiscard]] ImageFault fault() const noexcept {return fault_;}
  [[nodiscard]] const char* what() const noexcept override {return "runtime checkpoint image rejected";}
 private:
  ImageFault fault_;
};
struct ImageLimits {
  std::uint64_t bytes=64*1024*1024,work=256*1024*1024;
  std::uint64_t tables=4096,rows=1'000'000,fields=1024,scalar_bytes=1024*1024;
};
// Runtime image component v1. A complete session envelope additionally needs
// input positions, options and window state. This is not a durable file API.
struct ImageBinding {
  std::array<char,64> physical_sha256{},source_sha256{};
  std::uint64_t catalog_version=0;
  std::array<std::uint64_t,26> policy{};
  bool operator==(const ImageBinding&) const=default;
};
struct ImageManifest {
  ImageBinding binding;
  std::uint64_t epoch=0;
  bool operator==(const ImageManifest&) const=default;
};
struct ImageStatistics {
  std::uint64_t bytes=0,work=0,rows=0;
};
struct InspectedImage {
  ImageManifest manifest;
  ImageStatistics statistics;
};
struct EncodedImage {
  // Copying the byte vector can allocate; moves transfer its actual account.
  // Manifest/statistics fields do not make these bytes a durable/native owner.
  ImageVector<char> bytes;
  ImageStatistics statistics;
  ImageManifest manifest;
};
struct ImageTableView {std::span<const storage::RowView> rows;};
struct ImageRow {
  storage::AccountedRow row;
  [[nodiscard]] storage::RowView values() const noexcept {return row.view();}
};
struct DecodedImage {
  // Native row entries are move-only; decoding explicitly funds their copies.
  // Table arrays and compact row bytes outlive the input image independently.
  using Rows=ImageVector<ImageRow>;
  ImageManifest manifest;
  ImageVector<Rows> tables;
  ImageStatistics statistics;
};
// Little endian, exact scalar tags, fixed arithmetic identity, complete-body
// SHA256. Encode preflights before allocation. Decode validates the entire
// checksummed structure before allocating, then owns every returned byte.
// Work counts serialized byte visits in preflight/materialization/checksum;
// scalar comparisons and runtime storage/rebuild grants have separate units.
[[nodiscard]] EncodedImage encode_image(const resource::MemoryAccount&,const ImageManifest&,
    std::span<const ImageTableView>,ImageLimits={});
[[nodiscard]] DecodedImage decode_image(const resource::MemoryAccount&,std::string_view,
    const ImageBinding&,ImageLimits={});
// Validates the complete runtime component without allocating or materializing
// rows. The returned manifest is fixed-size metadata, not admission authority.
[[nodiscard]] InspectedImage inspect_image(std::string_view,ImageLimits={});
inline constexpr std::size_t image_header_size=84;
} // namespace crown::recovery
