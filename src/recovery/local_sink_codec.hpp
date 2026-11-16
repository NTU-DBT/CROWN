#pragma once
#include "crown/recovery/local_sink.hpp"
namespace crown::recovery::sink::detail {
struct Encoded {ImageVector<char> bytes;std::uint64_t work=0;};
struct Inspected {bool header=false;Header binding;std::uint64_t ordinal=0,generation=0,sequence=0,rows=0,work=0;};
[[nodiscard]] Encoded encode_header(const resource::MemoryAccount&,const Header&,std::span<const ScalarType>,ImageLimits);
[[nodiscard]] Encoded encode_epoch(const resource::MemoryAccount&,std::uint64_t ordinal,std::uint64_t generation,std::uint64_t sequence,std::span<const RowView>,std::span<const ScalarType>,ImageLimits);
[[nodiscard]] Inspected inspect(std::string_view,std::span<const ScalarType>,ImageLimits);
[[nodiscard]] Epoch decode(const resource::MemoryAccount&,std::string_view,std::span<const ScalarType>,ImageLimits);
// Validates protected length without requiring the body. File::open decides
// torn-tail status and rejects an incomplete initial frame.
[[nodiscard]] std::uint64_t frame_size(std::string_view,ImageLimits,std::uint64_t& work);
} // namespace crown::recovery::sink::detail
