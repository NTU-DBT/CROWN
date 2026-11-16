#include "compiled_source.hpp"
#include <algorithm>
#include <memory>

namespace crown::planner::compiler_source_detail {
namespace {
// Caller DTO conversion only. Ordinary payload is materialized; accounted
// layout/projection leaves share original metadata and native callbacks.
class Copy {
 public:
  std::string copy(std::string_view value) {return std::string(value);}
  io::Json copy(program::JsonView value) {
    switch(value.kind()) {
      case program::JsonKind::null:return nullptr;
      case program::JsonKind::boolean:return value.boolean();
      case program::JsonKind::integer:return value.integer();
      case program::JsonKind::unsigned_integer:return value.unsigned_integer();
      case program::JsonKind::number:return value.number();
      case program::JsonKind::string:return std::string(value.text());
      case program::JsonKind::array: {
        auto result=io::Json::array();
        for(std::size_t i=0;i<value.size();++i)result.push_back(copy(value.at(i)));
        return result;
      }
      case program::JsonKind::object: {
        auto result=io::Json::object();
        for(std::size_t i=0;i<value.size();++i)
          result[std::string(value.key(i))]=copy(value.member(i));
        return result;
      }
    }
    throw storage::IndexFailure(storage::IndexFault::contract);
  }
  Value copy(const storage::ScalarView& value) {return storage::export_scalar(value);}
  Decimal copy(const storage::InlineDecimal& value) {return std::get<Decimal>(storage::export_scalar(storage::ScalarView{value}));}
  storage::TupleLayout copy(const storage::AccountedLayout& value) {return value.descriptor();}
  storage::Projection copy(const storage::AccountedProjection& value) {return value.descriptor();}
  template<class T> OwnedType<program::Span<T>> copy(program::Span<T> value) {
    OwnedType<program::Span<T>> result;result.reserve(value.size());
    for(const auto& item:value)result.push_back(copy(item));
    return result;
  }
  template<class T> OwnedType<program::Set<T>> copy(program::Set<T> value) {
    OwnedType<program::Set<T>> result;for(const auto& item:value)result.insert(copy(item));return result;
  }
  template<class T> OwnedType<std::optional<T>> copy(const std::optional<T>& value) {
    if(!value)return {};
    return OwnedType<std::optional<T>>(std::in_place,copy(*value));
  }
  template<std::size_t I=0,class... T> OwnedType<std::variant<T...>> variant(const std::variant<T...>& value) {
    if constexpr(I<sizeof...(T)) {
      if(value.index()==I)return OwnedType<std::variant<T...>>(std::in_place_index<I>,copy(std::get<I>(value)));
      return variant<I+1>(value);
    } else throw storage::IndexFailure(storage::IndexFault::contract);
  }
  template<class... T> OwnedType<std::variant<T...>> copy(const std::variant<T...>& value) {return variant(value);}
  template<class T> OwnedType<T> copy(const T& value) {
    using R=OwnedType<T>;constexpr auto fields=Owned<T>::fields;
    if constexpr(fields==0) {static_assert(std::is_same_v<T,R> && std::is_trivially_copyable_v<T>,"missing owning compiler input mapping");return value;}
    else if constexpr(fields==1) {const auto& [f0]=value;return R{copy(f0)};}
    else if constexpr(fields==2) {const auto& [f0,f1]=value;return R{copy(f0),copy(f1)};}
    else if constexpr(fields==3) {const auto& [f0,f1,f2]=value;return R{copy(f0),copy(f1),copy(f2)};}
    else if constexpr(fields==4) {const auto& [f0,f1,f2,f3]=value;return R{copy(f0),copy(f1),copy(f2),copy(f3)};}
    else if constexpr(fields==5) {const auto& [f0,f1,f2,f3,f4]=value;return R{copy(f0),copy(f1),copy(f2),copy(f3),copy(f4)};}
    else if constexpr(fields==6) {const auto& [f0,f1,f2,f3,f4,f5]=value;return R{copy(f0),copy(f1),copy(f2),copy(f3),copy(f4),copy(f5)};}
    else if constexpr(fields==7) {const auto& [f0,f1,f2,f3,f4,f5,f6]=value;return R{copy(f0),copy(f1),copy(f2),copy(f3),copy(f4),copy(f5),copy(f6)};}
    else if constexpr(fields==8) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7]=value;return R{copy(f0),copy(f1),copy(f2),copy(f3),copy(f4),copy(f5),copy(f6),copy(f7)};}
    else if constexpr(fields==9) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7,f8]=value;return R{copy(f0),copy(f1),copy(f2),copy(f3),copy(f4),copy(f5),copy(f6),copy(f7),copy(f8)};}
    else if constexpr(fields==10) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7,f8,f9]=value;return R{copy(f0),copy(f1),copy(f2),copy(f3),copy(f4),copy(f5),copy(f6),copy(f7),copy(f8),copy(f9)};}
    else if constexpr(fields==11) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10]=value;return R{copy(f0),copy(f1),copy(f2),copy(f3),copy(f4),copy(f5),copy(f6),copy(f7),copy(f8),copy(f9),copy(f10)};}
    else if constexpr(fields==12) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11]=value;return R{copy(f0),copy(f1),copy(f2),copy(f3),copy(f4),copy(f5),copy(f6),copy(f7),copy(f8),copy(f9),copy(f10),copy(f11)};}
    else if constexpr(fields==13) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12]=value;return R{copy(f0),copy(f1),copy(f2),copy(f3),copy(f4),copy(f5),copy(f6),copy(f7),copy(f8),copy(f9),copy(f10),copy(f11),copy(f12)};}
    else if constexpr(fields==14) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13]=value;return R{copy(f0),copy(f1),copy(f2),copy(f3),copy(f4),copy(f5),copy(f6),copy(f7),copy(f8),copy(f9),copy(f10),copy(f11),copy(f12),copy(f13)};}
    else if constexpr(fields==15) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14]=value;return R{copy(f0),copy(f1),copy(f2),copy(f3),copy(f4),copy(f5),copy(f6),copy(f7),copy(f8),copy(f9),copy(f10),copy(f11),copy(f12),copy(f13),copy(f14)};}
    else static_assert(Owned<T>::fields==0,"unsupported compiler input arity");
  }
};
} // namespace
Catalog catalog(const program::Catalog& value) {return Copy{}.copy(value);}
Query query(const program::Query& value) {return Copy{}.copy(value);}
frontend::NormalizedSql normalized(const program::NormalizedSql& value) {return Copy{}.copy(value);}
PhysicalOptions options(const program::PhysicalOptions& value) {return Copy{}.copy(value);}
FreeConnexTree tree(const program::FreeConnexTree& value) {return Copy{}.copy(value);}
ProgramExport export_program(const CompiledProgram& value) {
  Copy copy;
  ProgramExport result;
  result.route=value.route();
  result.catalog=copy.copy(value.catalog());
  result.query=copy.copy(value.query());
  result.tree=copy.copy(value.tree());
  result.normalized=copy.copy(value.normalized());
  result.validation=copy.copy(value.validation());
  result.identity=copy.copy(value.identity());
  result.physical_sha256=copy.copy(value.physical_sha256());
  // Preserve the prepared digest bytes after a width check; this export path
  // does not recompute or independently validate the digest contents.
  const auto source_digest=value.physical_source_sha256();
  if(source_digest.size()!=result.physical_source_sha256.size())
    throw storage::IndexFailure(storage::IndexFault::contract);
  std::copy(source_digest.begin(),source_digest.end(),result.physical_source_sha256.begin());
  result.options=copy.copy(value.options());
  result.guarantee=copy.copy(value.guarantee());
  result.layouts=copy.copy(value.layouts());
  result.relations=copy.copy(value.relations());
  result.indexes=copy.copy(value.indexes());
  result.inputs=copy.copy(value.inputs());
  result.base_routes=copy.copy(value.base_routes());
  result.nodes=copy.copy(value.nodes());
  result.edges=copy.copy(value.edges());
  result.enumeration=copy.copy(value.enumeration());
  result.result_layout=value.result_layout().descriptor();
  result.work=value.work();
  return result;
}
} // namespace crown::planner::compiler_source_detail
