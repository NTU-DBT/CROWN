#pragma once

#include "crown/ir/program.hpp"
#include "crown/resource/owner_allocator.hpp"
#include "crown/storage/accounted_layout.hpp"
#include <vector>

namespace crown::runtime::physical {
struct SourceImageLimits {
  std::uint64_t rows = 65536; // Total full physical rows, including unused tables.
  std::uint64_t work = 1'000'000; // One image's table/row/field/payload-byte allowance.
};

// Explicit owning compact source data, in catalog table order. Per-table row
// order follows the storage backend and is not an ordering guarantee. Every
// descriptor, row and string allocation retains the original runtime account.
// program supplies genuine source schemas/constraints; this editable image is
// not a query answer, authenticated checkpoint or authority to restore state.
struct SourceImage {
  using Rows = std::vector<storage::AccountedTuple, resource::OwnerAllocator<storage::AccountedTuple>>;
  std::uint64_t sequence, work = 0;
  CompiledProgram program;
  std::vector<Rows, resource::OwnerAllocator<Rows>> tables;
  SourceImage(const resource::MemoryAccount&, std::uint64_t, const CompiledProgram&);
  SourceImage(const SourceImage&) = delete;
  SourceImage& operator=(const SourceImage&) = delete;
  SourceImage(SourceImage&&) noexcept = default;
  SourceImage& operator=(SourceImage&&) noexcept = default;
};
} // namespace crown::runtime::physical
