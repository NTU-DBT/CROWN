#pragma once

#include "crown/io/checkpoint.hpp"
#include "ingest_text.hpp"
#include <algorithm>
#include <bit>

namespace crown::io::checkpoint_detail {
inline void require(bool value,recovery::ImageFault fault=recovery::ImageFault::corrupt) {
  if(!value)throw recovery::ImageFailure(fault);
}
struct Budget {
  SourceStateLimits limits;
  std::uint64_t used=0;
  void charge(std::uint64_t value) {
    require(used<=limits.work && value<=limits.work-used,recovery::ImageFault::work);used+=value;
  }
  void positions(const AccountedInputProgress& progress,const InputLimits& input) {
    require(progress.source_positions.size()<=limits.positions && progress.source_positions.size()<=input.sources,
        recovery::ImageFault::limit);
    charge(1);
    for(const auto& [name,offset]:progress.source_positions) {
      static_cast<void>(offset);charge(1);charge(name.size());
      require(!name.empty() && name.size()<=input.source_bytes && name.view().find('\0')==std::string_view::npos);
      ingest_detail::require_utf8(name.view());
    }
  }
  void options(const AccountedInputOptions::Values& options) {
    charge(1);charge(options.relation_tokens.size());
    for(const auto& [name,table]:options.relation_tokens){static_cast<void>(table);charge(name.size());}
    if(options.source)charge(options.source->size());
    if(options.null_token)charge(options.null_token->size());
  }
};
// Conservative replay source-validation units, charged before scalar text,
// identifier validation/copy and bounded red-black source-directory searches.
// Accepted progress was validated at checkpoint admission; never rescan its
// complete map for every replayed row.
inline void replay_input(Budget& budget,const InputItemView& item,const InputLimits& limits,const InputPositions& positions) {
  // Precharge incremental checks; callers still validate the row and source acceptance order.
  require(positions.size()<=budget.limits.positions && positions.size()<=limits.sources,recovery::ImageFault::limit);budget.charge(1);
  storage::TupleValuesView values;bool row=false;
  if(const auto* event=std::get_if<InputEventView>(&item)){values=event->update.values;row=true;}
  else if(const auto* insert=std::get_if<WindowInsertView>(&std::get<WindowCommandView>(item).command)){values=insert->values;row=true;}
  const auto multiple=[&](std::uint64_t count,std::uint64_t width){require(width==0 || count<=UINT64_MAX/width,recovery::ImageFault::work);budget.charge(count*width);};
  if(row) {
    require(values.size()<=limits.columns,recovery::ImageFault::limit);
    for(std::size_t i=0;i<values.size();++i){budget.charge(8);const auto scalar=values[i];
      if(const auto* text=std::get_if<std::string_view>(&scalar))multiple(text->size(),4);
      else if(std::holds_alternative<storage::InlineDecimal>(scalar))budget.charge(82);
    }
  }
  const auto position=std::visit([](const auto& value){return value.source_position;},item);
  if(position) {
    require(position->source.size()<=limits.source_bytes,recovery::ImageFault::limit);
    const auto depth=static_cast<std::uint64_t>(std::bit_width(static_cast<std::uint64_t>(positions.size())));multiple(position->source.size(),12+8*depth);
    if(positions.size()==budget.limits.positions)require(positions.contains(position->source),recovery::ImageFault::limit);
  }
}
inline std::array<char,64> hash(std::string_view value) {
  require(value.size()==64,recovery::ImageFault::binding);std::array<char,64> result{};
  std::copy(value.begin(),value.end(),result.begin());return result;
}
} // namespace crown::io::checkpoint_detail
