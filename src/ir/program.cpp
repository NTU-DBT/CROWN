#include "crown/ir/program.hpp"
#include "input_program.hpp"
#include "../runtime/sql_cold_rebuild.hpp"

#include "crown/resource/ownership.hpp"
#include "../frontend/sql_scalar.hpp"
#include "../storage/owner.hpp"
#include "../planner/native_physical_binding.hpp"
#include "../planner/candidate_binding.hpp"
#include "crown/planner/candidates.hpp"
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <type_traits>
#include <utility>

namespace crown::program::detail {
template<class T> using Vector=std::vector<T,resource::MemoryAllocator<T>>;
struct Allocation {
  resource::MemoryBlock block;
  std::size_t constructed=0;
  void (*destroy)(void*,std::size_t) noexcept=nullptr;
};
struct JsonMember;
struct JsonNode {
  std::variant<std::monostate,bool,std::int64_t,std::uint64_t,double,std::string_view,
      Span<JsonNode>,Span<JsonMember>> value;
};
struct JsonMember {std::string_view key;JsonNode value;};
template<class T> struct Type {using Result=T;static constexpr std::size_t fields=0;};
template<> struct Type<::crown::Column> {using Result=::crown::program::Column;static constexpr std::size_t fields=5;};
template<> struct Type<::crown::UniqueConstraint> {using Result=::crown::program::UniqueConstraint;static constexpr std::size_t fields=3;};
template<> struct Type<::crown::ForeignKeyConstraint> {using Result=::crown::program::ForeignKeyConstraint;static constexpr std::size_t fields=5;};
template<> struct Type<::crown::DistinctEstimate> {using Result=::crown::program::DistinctEstimate;static constexpr std::size_t fields=2;};
template<> struct Type<::crown::TableStatistics> {using Result=::crown::program::TableStatistics;static constexpr std::size_t fields=2;};
template<> struct Type<::crown::KeyHint> {using Result=::crown::program::KeyHint;static constexpr std::size_t fields=2;};
template<> struct Type<::crown::Table> {using Result=::crown::program::Table;static constexpr std::size_t fields=6;};
template<> struct Type<::crown::Catalog> {using Result=::crown::program::Catalog;static constexpr std::size_t fields=2;};
template<> struct Type<::crown::Variable> {using Result=::crown::program::Variable;static constexpr std::size_t fields=2;};
template<> struct Type<::crown::Atom> {using Result=::crown::program::Atom;static constexpr std::size_t fields=3;};
template<> struct Type<::crown::Output> {using Result=::crown::program::Output;static constexpr std::size_t fields=2;};
template<> struct Type<::crown::Query> {using Result=::crown::program::Query;static constexpr std::size_t fields=4;};
template<> struct Type<::crown::TreeNode> {using Result=::crown::program::TreeNode;static constexpr std::size_t fields=6;};
template<> struct Type<::crown::FreeConnexTree> {using Result=::crown::program::FreeConnexTree;static constexpr std::size_t fields=4;};
template<> struct Type<::crown::planner::PlanViolation> {using Result=::crown::program::PlanViolation;static constexpr std::size_t fields=6;};
template<> struct Type<::crown::planner::ValidationReport> {using Result=::crown::program::ValidationReport;static constexpr std::size_t fields=6;};
template<> struct Type<::crown::frontend::BoundLiteral> {using Result=::crown::program::BoundLiteral;static constexpr std::size_t fields=1;};
template<> struct Type<::crown::frontend::BoundOperation> {using Result=::crown::program::BoundOperation;static constexpr std::size_t fields=2;};
template<> struct Type<::crown::frontend::BoundExpression> {using Result=::crown::program::BoundExpression;static constexpr std::size_t fields=3;};
template<> struct Type<::crown::frontend::BoundOccurrence> {using Result=::crown::program::BoundOccurrence;static constexpr std::size_t fields=5;};
template<> struct Type<::crown::frontend::BoundOutput> {using Result=::crown::program::BoundOutput;static constexpr std::size_t fields=2;};
template<> struct Type<::crown::frontend::BoundSql> {using Result=::crown::program::BoundSql;static constexpr std::size_t fields=13;};
template<> struct Type<::crown::frontend::ColumnConstant> {using Result=::crown::program::ColumnConstant;static constexpr std::size_t fields=2;};
template<> struct Type<::crown::frontend::OccurrenceAdapter> {using Result=::crown::program::OccurrenceAdapter;static constexpr std::size_t fields=9;};
template<> struct Type<::crown::frontend::ConstantOutput> {using Result=::crown::program::ConstantOutput;static constexpr std::size_t fields=1;};
template<> struct Type<::crown::frontend::NormalizedOutput> {using Result=::crown::program::NormalizedOutput;static constexpr std::size_t fields=3;};
template<> struct Type<::crown::frontend::NormalizedSql> {using Result=::crown::program::NormalizedSql;static constexpr std::size_t fields=11;};
template<> struct Type<::crown::io::CachePolicy> {using Result=::crown::program::CachePolicy;static constexpr std::size_t fields=4;};
template<> struct Type<::crown::PhysicalOptions> {using Result=::crown::program::PhysicalOptions;static constexpr std::size_t fields=3;};
template<> struct Type<::crown::GuaranteeProfile> {using Result=::crown::program::GuaranteeProfile;static constexpr std::size_t fields=15;};
template<> struct Type<::crown::io::QueryIdentity> {using Result=::crown::program::QueryIdentity;static constexpr std::size_t fields=8;};
template<> struct Type<::crown::PhysicalRelation> {using Result=::crown::program::PhysicalRelation;static constexpr std::size_t fields=5;};
template<> struct Type<::crown::IndexRequirement> {using Result=::crown::program::IndexRequirement;static constexpr std::size_t fields=4;};
template<> struct Type<::crown::InputConstant> {using Result=::crown::program::InputConstant;static constexpr std::size_t fields=2;};
template<> struct Type<::crown::PhysicalInput> {using Result=::crown::program::PhysicalInput;static constexpr std::size_t fields=8;};
template<> struct Type<::crown::PhysicalNode> {using Result=::crown::program::PhysicalNode;static constexpr std::size_t fields=15;};
template<> struct Type<::crown::PhysicalEdge> {using Result=::crown::program::PhysicalEdge;static constexpr std::size_t fields=5;};
template<> struct Type<::crown::EnumerationStep> {using Result=::crown::program::EnumerationStep;static constexpr std::size_t fields=6;};
template<> struct Type<::crown::EnumerationProgram> {using Result=::crown::program::EnumerationProgram;static constexpr std::size_t fields=4;};
template<> struct Type<std::string> {using Result=std::string_view;};
template<> struct Type<Decimal> {using Result=storage::InlineDecimal;};
template<> struct Type<storage::TupleLayout> {using Result=storage::AccountedLayout;};
template<> struct Type<storage::Projection> {using Result=storage::AccountedProjection;};
template<> struct Type<io::Json> {using Result=JsonView;};
template<class T,class A> struct Type<std::vector<T,A>> {using Result=Span<typename Type<T>::Result>;};
template<class T,class L,class A> struct Type<std::set<T,L,A>> {using Result=Set<typename Type<T>::Result>;};
template<class T> struct Type<std::optional<T>> {using Result=std::optional<typename Type<T>::Result>;};
template<class... T> struct Type<std::variant<T...>> {using Result=std::variant<typename Type<T>::Result...>;};
#include "program_native_types.inc"
template<class T> using Frozen=typename Type<T>::Result;
void require(bool value) {if(!value)throw storage::IndexFailure(storage::IndexFault::contract);}
void step(storage::IndexWorkAllowance* work,std::uint64_t amount=1) {
  if(work)work->admit(storage::IndexWork{.structural_steps=amount});
}
template<class T> void words(storage::IndexWorkAllowance* work,std::size_t count) {
  if(!work)return;
  constexpr auto per=static_cast<std::uint64_t>((sizeof(T)+sizeof(void*)-1)/sizeof(void*));
  if(count>UINT64_MAX/per)throw storage::IndexFailure(storage::IndexFault::overflow);
  work->admit(storage::IndexWork{.pointer_slots=static_cast<std::uint64_t>(count)*per});
}
storage::AccountedLayout make_layout(const resource::MemoryAccount& account,resource::MemoryAttribution owner,
    LayoutId id,std::span<const storage::Field> fields,std::uint64_t version,std::string_view identity,
    std::string_view suffix,std::optional<storage::LayoutOrigin> origin,storage::IndexWorkAllowance* work) {
  if(suffix.size()>SIZE_MAX-identity.size())throw storage::IndexFailure(storage::IndexFault::overflow);
  words<storage::Field>(work,fields.size());words<char>(work,identity.size()+suffix.size());
  if(work)work->admit(storage::IndexWork{.scalar_fields=static_cast<std::uint64_t>(fields.size()),
      .scalar_bytes=static_cast<std::uint64_t>(identity.size()+suffix.size())});
  Vector<char> binding(resource::MemoryAllocator<char>(account,resource::MemoryPurpose::scratch,owner));
  binding.reserve(identity.size()+suffix.size());binding.insert(binding.end(),identity.begin(),identity.end());
  binding.insert(binding.end(),suffix.begin(),suffix.end());
  return storage::AccountedLayout::make(account,id,fields,{version,{binding.data(),binding.size()}},origin,owner);
}
ScalarType sql_scalar(frontend::SqlKind kind) {
  switch(kind) {
    case frontend::SqlKind::int32:case frontend::SqlKind::int64:return ScalarType::int64;
    case frontend::SqlKind::string:return ScalarType::string;
    case frontend::SqlKind::boolean:return ScalarType::boolean;
    case frontend::SqlKind::date:return ScalarType::date;
    case frontend::SqlKind::decimal:return ScalarType::decimal;
    case frontend::SqlKind::unknown:break;
  }
  throw storage::IndexFailure(storage::IndexFault::contract);
}
} // namespace crown::program::detail

namespace crown {
struct CompiledProgram::Data {
  resource::MemoryAccount account;
  // Replanned programs retain the canonical admitted source only, never a
  // growing chain of prior physical candidate graphs.
  CompiledProgram basis;
  storage::AccountedPlanStorage::Binding binding;
  resource::MemoryAttribution attribution;
  program::detail::Vector<program::detail::Allocation> allocations;
  program::Span<storage::AccountedLayout> layouts;
  PhysicalRoute route=PhysicalRoute::constant_false;
  program::Catalog catalog{};
  program::Query query{};
  program::FreeConnexTree tree{};
  std::optional<program::NormalizedSql> normalized;
  program::ValidationReport validation{};
  program::QueryIdentity identity{};
  std::string_view physical_sha256;
  std::array<char,64> physical_source_digest{},native_physical_digest{};
  program::PhysicalOptions options{};
  program::GuaranteeProfile guarantee{};
  program::Span<program::PhysicalRelation> relations;
  program::Span<program::IndexRequirement> indexes;
  program::Span<program::PhysicalInput> inputs;
  program::Span<program::Span<OccurrenceId>> base_routes;
  program::Span<program::PhysicalNode> nodes;
  program::Span<program::PhysicalEdge> edges;
  program::EnumerationProgram enumeration{};
  storage::AccountedLayout result_layout,sql_result_layout;
  program::Span<program::SourceTable> sources;
  std::uint64_t work=0;
  std::shared_ptr<const program::detail::PreparedInputs> prepared_inputs;
  Data(storage::AccountedPlanStorage::Binding value,resource::MemoryAttribution owner)
      :account(value.account()),binding(std::move(value)),attribution(owner),allocations(resource::MemoryAllocator<program::detail::Allocation>(
          binding.account(),resource::MemoryPurpose::immutable_metadata,owner)),layouts(binding.layouts()) {}
  Data(const resource::MemoryAccount& value,resource::MemoryAttribution owner,CompiledProgram source)
      :account(value),basis(std::move(source)),attribution(owner),
       allocations(resource::MemoryAllocator<program::detail::Allocation>(value,resource::MemoryPurpose::immutable_metadata,owner)) {}
  ~Data() {
    // Destroy completed arena prefixes before member/block release. Flat
    // JSON/SQL views own no child graph; member release can still destroy
    // descriptor controls and the last retained canonical source.
    for(auto it=allocations.rbegin();it!=allocations.rend();++it)
      it->destroy(it->block.data(),it->constructed);
  }
};
} // namespace crown

namespace crown::program::detail {
class Builder {
  CompiledProgram::Data& data_;
  const PhysicalPlan* source_;
  const CompiledProgram* native_source_=nullptr;
  storage::IndexWorkAllowance* work_;
  struct Memo {const storage::Projection* source;storage::AccountedProjection projection;};
  struct NativeMemo {const storage::AccountedProjection* source;storage::AccountedProjection projection;};
  Vector<Memo> projections_;
  Vector<NativeMemo> native_projections_;
 public:
  Builder(CompiledProgram::Data& data,const PhysicalPlan& source,storage::IndexWorkAllowance* work)
      :data_(data),source_(&source),work_(work),projections_(resource::MemoryAllocator<Memo>(
          data.binding.account(),resource::MemoryPurpose::scratch,data.attribution)),
       native_projections_(resource::MemoryAllocator<NativeMemo>(data.account,resource::MemoryPurpose::scratch,data.attribution)) {
    std::size_t capacity=source.indexes().size();
    const auto add=[&](std::size_t n) {if(n>SIZE_MAX-capacity)throw storage::IndexFailure(storage::IndexFault::overflow);capacity+=n;};
    add(source.nodes().size());add(source.nodes().size());add(source.edges().size());
    add(source.inputs().size());add(source.enumeration().steps.size());
    words<Memo>(work_,capacity);projections_.reserve(capacity);
    for(const auto& index:source.indexes()) {
      step(work_);projections_.push_back({&index.projection,data.binding.projection(index.id)});
    }
  }
  Builder(CompiledProgram::Data& data,storage::IndexWorkAllowance* work)
      :data_(data),source_(nullptr),work_(work),projections_(resource::MemoryAllocator<Memo>(
          data.account,resource::MemoryPurpose::scratch,data.attribution)),
       native_projections_(resource::MemoryAllocator<NativeMemo>(data.account,resource::MemoryPurpose::scratch,data.attribution)) {}
  Builder(CompiledProgram::Data& data,const CompiledProgram& source,storage::IndexWorkAllowance* work)
      :data_(data),source_(nullptr),native_source_(&source),work_(work),
       projections_(resource::MemoryAllocator<Memo>(data.account,resource::MemoryPurpose::scratch,data.attribution)),
       native_projections_(resource::MemoryAllocator<NativeMemo>(data.account,resource::MemoryPurpose::scratch,data.attribution)) {
    std::size_t capacity=source.indexes().size();
    const auto add=[&](std::size_t n){if(n>SIZE_MAX-capacity)throw storage::IndexFailure(storage::IndexFault::overflow);capacity+=n;};
    add(source.nodes().size());add(source.nodes().size());add(source.edges().size());add(source.inputs().size());add(source.enumeration().steps.size());
    words<NativeMemo>(work_,capacity);native_projections_.reserve(capacity);
    for(const auto& index:source.indexes()){step(work_);native_projections_.push_back({&index.projection,data.binding.projection(index.id)});}
  }
  template<class T> std::pair<T*,std::size_t> allocate(std::size_t n) {
    static_assert(std::is_nothrow_destructible_v<T>);
    if(n>SIZE_MAX/sizeof(T))throw storage::IndexFailure(storage::IndexFault::overflow);
    words<T>(work_,n);
    auto block=data_.account.allocate(n*sizeof(T),alignof(T),resource::MemoryPurpose::immutable_metadata,data_.attribution);
    auto* pointer=static_cast<T*>(block.data());
    if(data_.allocations.size()==data_.allocations.capacity()) {
      const auto old=data_.allocations.capacity();
      if(old>SIZE_MAX/2)throw storage::IndexFailure(storage::IndexFault::overflow);
      const auto next=old?old*2:8;words<Allocation>(work_,next);data_.allocations.reserve(next);
    }
    const auto index=data_.allocations.size();
    data_.allocations.push_back({std::move(block),0,[](void* p,std::size_t count) noexcept {
      std::destroy_n(static_cast<T*>(p),count);
    }});
    return {pointer,index};
  }
  template<class T> void constructed(std::size_t index,std::size_t count) {
    static_cast<void>(sizeof(T));data_.allocations[index].constructed=count;
  }
  template<class T> T* defaults(std::size_t n) {
    if(!n)return nullptr;
    const auto [pointer,index]=allocate<T>(n);
    for(std::size_t i=0;i<n;++i) {std::construct_at(pointer+i);constructed<T>(index,i+1);}
    return pointer;
  }
  std::string_view freeze(std::string_view value) {
    if(work_)work_->admit(storage::IndexWork{.scalar_bytes=static_cast<std::uint64_t>(value.size())});
    if(value.empty())return {};
    const auto [pointer,index]=allocate<char>(value.size());
    std::uninitialized_copy(value.begin(),value.end(),pointer);constructed<char>(index,value.size());
    return {pointer,value.size()};
  }
  std::string_view freeze(const std::string& value) {return freeze(std::string_view(value));}
  storage::InlineDecimal freeze(const Decimal& value) {return storage::InlineDecimal::copy_of(value);}
  storage::AccountedLayout freeze(const storage::TupleLayout& source) {
    step(work_);const auto id=source.id();
    require(id.value<source_->layouts().size() && source.same_token(source_->layouts()[id.value]));
    return data_.binding.layout(id);
  }
  storage::AccountedProjection freeze(const storage::Projection& source) {
    for(const auto& old:projections_) {step(work_);if(source.same_token(*old.source))return old.projection;}
    const auto from=freeze(source.source()),to=freeze(source.target());
    if(work_)work_->admit(storage::IndexWork{.scalar_fields=static_cast<std::uint64_t>(source.fields().size())});
    words<FieldId>(work_,source.fields().size());
    auto result=storage::AccountedProjection::freeze(from,to,source.fields(),data_.attribution);
    projections_.push_back({&source,result});return result;
  }
  // Native construction already owns every nested span/token through this
  // program or its canonical basis. These copies retain existing funded handles;
  // the generic owning-field mapping below remains strict for all other types.
  storage::AccountedLayout freeze(const storage::AccountedLayout& value) {
    if(!native_source_)return value;
    step(work_);const auto id=value.id();require(id.value<native_source_->layouts().size() && value.same_token(native_source_->layouts()[id.value]));
    return data_.binding.layout(id);
  }
  storage::AccountedProjection freeze(const storage::AccountedProjection& value) {
    if(!native_source_)return value;
    for(const auto& old:native_projections_){step(work_);if(value.same_token(*old.source))return old.projection;}
    words<FieldId>(work_,value.fields().size());
    if(work_)work_->admit(storage::IndexWork{.scalar_fields=static_cast<std::uint64_t>(value.fields().size())});
    auto result=storage::AccountedProjection::freeze(freeze(value.source()),freeze(value.target()),value.fields(),data_.attribution);
    native_projections_.push_back({&value,result});return result;
  }
  program::PhysicalRelation freeze(const program::PhysicalRelation& value) {return native_source_?aggregate(value):value;}
  program::PhysicalInput freeze(const program::PhysicalInput& value) {return native_source_?aggregate(value):value;}
  program::PhysicalNode freeze(const program::PhysicalNode& value) {return native_source_?aggregate(value):value;}
  program::PhysicalEdge freeze(const program::PhysicalEdge& value) {return native_source_?aggregate(value):value;}
  program::EnumerationStep freeze(const program::EnumerationStep& value) {return native_source_?aggregate(value):value;}
  template<class T,class A> Frozen<std::vector<T,A>> freeze(const std::vector<T,A>& source) {
    using E=Frozen<T>;if(source.empty())return {};
    const auto [pointer,index]=allocate<E>(source.size());std::size_t i=0;
    for(const auto& value:source) {std::construct_at(pointer+i,freeze(value));constructed<E>(index,++i);}
    return {pointer,source.size()};
  }
  template<class T,class L,class A> Frozen<std::set<T,L,A>> freeze(const std::set<T,L,A>& source) {
    using E=Frozen<T>;if(source.empty())return {};
    const auto [pointer,index]=allocate<E>(source.size());std::size_t i=0;
    for(const auto& value:source) {std::construct_at(pointer+i,freeze(value));constructed<E>(index,++i);}
    return {pointer,source.size()};
  }
  template<class T> Span<Frozen<T>> freeze(Span<T> source) {
    using E=Frozen<T>;if(source.empty())return {};
    const auto [pointer,index]=allocate<E>(source.size());std::size_t i=0;
    for(const auto& value:source){std::construct_at(pointer+i,freeze(value));constructed<E>(index,++i);}return {pointer,source.size()};
  }
  template<class T> Set<Frozen<T>> freeze(Set<T> source) {const auto value=freeze(Span<T>(source));return {value.data(),value.size()};}
  template<class T> Frozen<std::optional<T>> freeze(const std::optional<T>& source) {
    if(!source)return {};
    return Frozen<std::optional<T>>(std::in_place,freeze(*source));
  }
  template<std::size_t I=0,class... T> Frozen<std::variant<T...>> freeze_variant(const std::variant<T...>& source) {
    if constexpr(I<sizeof...(T)) {
      if(source.index()==I)return Frozen<std::variant<T...>>(std::in_place_index<I>,freeze(std::get<I>(source)));
      return freeze_variant<I+1>(source);
    } else throw storage::IndexFailure(storage::IndexFault::contract);
  }
  template<class... T> Frozen<std::variant<T...>> freeze(const std::variant<T...>& source) {return freeze_variant(source);}
  JsonView freeze(const io::Json& source) {
    struct Pending {const io::Json* source;JsonNode* target;};
    Vector<Pending> pending(resource::MemoryAllocator<Pending>(data_.account,resource::MemoryPurpose::scratch,data_.attribution));
    const auto enqueue=[&](const io::Json* input,JsonNode* target) {
      if(pending.size()==pending.capacity()) {
        const auto old=pending.capacity();if(old>SIZE_MAX/2)throw storage::IndexFailure(storage::IndexFault::overflow);
        const auto capacity=old?old*2:8;words<Pending>(work_,capacity);pending.reserve(capacity);
      }
      pending.push_back({input,target});
    };
    auto* root=defaults<JsonNode>(1);enqueue(&source,root);
    for(std::size_t i=0;i<pending.size();++i) {
      step(work_);const auto [input,output]=pending[i];
      if(input->is_object()) {
        auto* members=defaults<JsonMember>(input->size());output->value=Span<JsonMember>{members,input->size()};std::size_t j=0;
        for(auto it=input->begin();it!=input->end();++it,++j) {
          members[j].key=freeze(it.key());enqueue(&it.value(),&members[j].value);
        }
      } else if(input->is_array()) {
        auto* nodes=defaults<JsonNode>(input->size());output->value=Span<JsonNode>{nodes,input->size()};std::size_t j=0;
        for(const auto& value:*input)enqueue(&value,nodes+j++);
      } else if(input->is_string())output->value=freeze(input->get_ref<const io::Json::string_t&>());
      else if(input->is_boolean())output->value=input->get<bool>();
      else if(input->is_number_unsigned())output->value=input->get<std::uint64_t>();
      else if(input->is_number_integer())output->value=input->get<std::int64_t>();
      else if(input->is_number_float())output->value=input->get<double>();
      else require(input->is_null());
    }
    return JsonView(root);
  }
  JsonView freeze(JsonView source) {
    struct Pending {JsonView input;JsonNode* output;};
    Vector<Pending> pending(resource::MemoryAllocator<Pending>(data_.account,resource::MemoryPurpose::scratch,data_.attribution));
    const auto enqueue=[&](JsonView input,JsonNode* output){
      if(pending.size()==pending.capacity()) {
        const auto old=pending.capacity();if(old>SIZE_MAX/2)throw storage::IndexFailure(storage::IndexFault::overflow);
        const auto capacity=old?old*2:8;words<Pending>(work_,capacity);pending.reserve(capacity);
      }
      pending.push_back({input,output});
    };
    auto* root=defaults<JsonNode>(1);enqueue(source,root);
    for(std::size_t i=0;i<pending.size();++i) {
      step(work_);const auto [input,output]=pending[i];
      switch(input.kind()) {
        case JsonKind::null:break;
        case JsonKind::boolean:output->value=input.boolean();break;
        case JsonKind::integer:output->value=input.integer();break;
        case JsonKind::unsigned_integer:output->value=input.unsigned_integer();break;
        case JsonKind::number:output->value=input.number();break;
        case JsonKind::string:output->value=freeze(input.text());break;
        case JsonKind::array: {
          auto* values=defaults<JsonNode>(input.size());output->value=Span<JsonNode>{values,input.size()};
          for(std::size_t j=0;j<input.size();++j){enqueue(input.at(j),values+j);}break;
        }
        case JsonKind::object: {
          auto* values=defaults<JsonMember>(input.size());output->value=Span<JsonMember>{values,input.size()};
          for(std::size_t j=0;j<input.size();++j){values[j].key=freeze(input.key(j));enqueue(input.member(j),&values[j].value);}break;
        }
      }
    }
    return JsonView(root);
  }
  template<class T> Frozen<T> aggregate(const T& source) {
    using R=Frozen<T>;constexpr auto fields=Type<T>::fields;
    if constexpr(fields==0) {
      // A new trivial view still needs a reviewed backing owner; trivial copy
      // alone does not turn borrowed pointers/spans into owned metadata.
      static_assert(std::is_same_v<T,R> && std::is_trivially_copyable_v<T>,"a retained owning field needs an explicit native mapping");return source;
    } else {
      step(work_);
      if constexpr(fields==1) {const auto& [f0]=source;return R{freeze(f0)};}
      else if constexpr(fields==2) {const auto& [f0,f1]=source;return R{freeze(f0),freeze(f1)};}
      else if constexpr(fields==3) {const auto& [f0,f1,f2]=source;return R{freeze(f0),freeze(f1),freeze(f2)};}
      else if constexpr(fields==4) {const auto& [f0,f1,f2,f3]=source;return R{freeze(f0),freeze(f1),freeze(f2),freeze(f3)};}
      else if constexpr(fields==5) {const auto& [f0,f1,f2,f3,f4]=source;return R{freeze(f0),freeze(f1),freeze(f2),freeze(f3),freeze(f4)};}
      else if constexpr(fields==6) {const auto& [f0,f1,f2,f3,f4,f5]=source;return R{freeze(f0),freeze(f1),freeze(f2),freeze(f3),freeze(f4),freeze(f5)};}
      else if constexpr(fields==7) {const auto& [f0,f1,f2,f3,f4,f5,f6]=source;return R{freeze(f0),freeze(f1),freeze(f2),freeze(f3),freeze(f4),freeze(f5),freeze(f6)};}
      else if constexpr(fields==8) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7]=source;return R{freeze(f0),freeze(f1),freeze(f2),freeze(f3),freeze(f4),freeze(f5),freeze(f6),freeze(f7)};}
      else if constexpr(fields==9) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7,f8]=source;return R{freeze(f0),freeze(f1),freeze(f2),freeze(f3),freeze(f4),freeze(f5),freeze(f6),freeze(f7),freeze(f8)};}
      else if constexpr(fields==10) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7,f8,f9]=source;return R{freeze(f0),freeze(f1),freeze(f2),freeze(f3),freeze(f4),freeze(f5),freeze(f6),freeze(f7),freeze(f8),freeze(f9)};}
      else if constexpr(fields==11) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10]=source;return R{freeze(f0),freeze(f1),freeze(f2),freeze(f3),freeze(f4),freeze(f5),freeze(f6),freeze(f7),freeze(f8),freeze(f9),freeze(f10)};}
      else if constexpr(fields==12) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11]=source;return R{freeze(f0),freeze(f1),freeze(f2),freeze(f3),freeze(f4),freeze(f5),freeze(f6),freeze(f7),freeze(f8),freeze(f9),freeze(f10),freeze(f11)};}
      else if constexpr(fields==13) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12]=source;return R{freeze(f0),freeze(f1),freeze(f2),freeze(f3),freeze(f4),freeze(f5),freeze(f6),freeze(f7),freeze(f8),freeze(f9),freeze(f10),freeze(f11),freeze(f12)};}
      else if constexpr(fields==14) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13]=source;return R{freeze(f0),freeze(f1),freeze(f2),freeze(f3),freeze(f4),freeze(f5),freeze(f6),freeze(f7),freeze(f8),freeze(f9),freeze(f10),freeze(f11),freeze(f12),freeze(f13)};}
      else if constexpr(fields==15) {const auto& [f0,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14]=source;return R{freeze(f0),freeze(f1),freeze(f2),freeze(f3),freeze(f4),freeze(f5),freeze(f6),freeze(f7),freeze(f8),freeze(f9),freeze(f10),freeze(f11),freeze(f12),freeze(f13),freeze(f14)};}
      else static_assert(Type<T>::fields!=0,"missing aggregate native mapping");
    }
  }
  template<class T> Frozen<T> freeze(const T& source) {return aggregate(source);}
  void run() {
    if(native_source_)run_source(*native_source_);else {require(source_!=nullptr);run_source(*source_);}
  }
  template<class Source> void run_source(const Source& source) {
    data_.route=source.route();data_.catalog=freeze(source.catalog());data_.query=freeze(source.query());
    data_.tree=freeze(source.tree());data_.normalized=freeze(source.normalized());data_.validation=freeze(source.validation());
    data_.identity=freeze(source.identity());data_.physical_sha256=freeze(source.physical_sha256());
    data_.options=freeze(source.options());data_.guarantee=freeze(source.guarantee());
    data_.relations=freeze(source.relations());data_.indexes=freeze(source.indexes());data_.inputs=freeze(source.inputs());
    data_.base_routes=freeze(source.base_routes());data_.nodes=freeze(source.nodes());data_.edges=freeze(source.edges());
    data_.enumeration=freeze(source.enumeration());data_.result_layout=freeze(source.result_layout());data_.work=source.work();
    const auto source_digest=source.physical_source_sha256();
    std::copy(source_digest.begin(),source_digest.end(),data_.physical_source_digest.begin());
    finish_native_auxiliary();
  }
  void finish_native_auxiliary() {
    const auto& catalog=data_.normalized?data_.normalized->binding.catalog:data_.catalog;
    Vector<storage::Field> fields(resource::MemoryAllocator<storage::Field>(data_.account,resource::MemoryPurpose::scratch,data_.attribution));
    data_.sql_result_layout=data_.result_layout;
    if(data_.normalized) {
      const auto& sql=*data_.normalized;
      const auto count=sql.binding.wrapper==frontend::SqlWrapper::exists?std::size_t{1}:sql.outputs.size();
      words<storage::Field>(work_,count);fields.reserve(count);
      if(sql.binding.wrapper==frontend::SqlWrapper::exists)fields.push_back({ScalarType::boolean});
      else for(const auto& output:sql.outputs)fields.push_back({sql_scalar(output.type.kind),output.type.decimal});
      data_.sql_result_layout=make_layout(data_.account,data_.attribution,LayoutId{data_.layouts.size()},
          fields,catalog.version,data_.physical_sha256,":sql-result",{},work_);
    }
    if(!catalog.tables.empty()) {
      require(catalog.tables.size()<=SIZE_MAX-data_.layouts.size() && catalog.tables.size()<=SIZE_MAX-data_.relations.size());
      const auto [sources,index]=allocate<program::SourceTable>(catalog.tables.size());
      for(std::size_t i=0;i<catalog.tables.size();++i) {
        const auto found=std::find_if(data_.relations.begin(),data_.relations.end(),[&](const auto& relation) {
          step(work_);return relation.role==RelationRole::physical_base && relation.base==TableId{i};
        });
        if(found!=data_.relations.end())std::construct_at(sources+i,program::SourceTable{found->id,found->layout});
        else {
          fields.clear();const auto& table=catalog.tables[i];words<storage::Field>(work_,table.columns.size());
          fields.reserve(table.columns.size());for(const auto& column:table.columns)fields.push_back({column.type,column.decimal,{}});
          auto layout=make_layout(data_.account,data_.attribution,LayoutId{data_.layouts.size()+i},fields,
              catalog.version,data_.physical_sha256,":source",storage::LayoutOrigin{TableId{i},table.source_schema_version},work_);
          std::construct_at(sources+i,program::SourceTable{RelationId{data_.relations.size()+i},std::move(layout)});
        }
        constructed<program::SourceTable>(index,i+1);
      }
      data_.sources={sources,catalog.tables.size()};
    }
  }
};
} // namespace crown::program::detail

#include "program_replan.inc"

namespace crown {
CompiledProgram CompiledProgram::standalone(const PhysicalPlan& source) {
  auto account=resource::MemoryAccount::create(UINT64_MAX);
  return compile(account,source);
}
CompiledProgram CompiledProgram::compile(const resource::MemoryAccount& account,const PhysicalPlan& source) {
  storage::IndexWorkAllowance compiler_work({UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX},true);
  auto binding=storage::AccountedPlanStorage::freeze_binding(account,source,&compiler_work,storage::MetadataWork::compiler);
  const auto owner=storage::detail::try_new_storage_owner();if(!owner)throw storage::IndexFailure(storage::IndexFault::overflow);
  const resource::MemoryAttribution tag{resource::MemoryOwnerKind::immutable_metadata,owner->value};
  program::detail::words<Data>(&compiler_work,1);
  auto result=resource::make_accounted_shared<Data>(tag,account,resource::MemoryPurpose::immutable_metadata,std::move(binding),tag);
  program::detail::Builder builder(*result,source,&compiler_work);builder.run();return CompiledProgram(std::move(result));
}
CompiledProgram CompiledProgram::freeze(const resource::MemoryAccount& account,const PhysicalPlan& source,storage::IndexWorkAllowance* work) {
  return freeze_impl(account,source,work,storage::MetadataWork::execution);
}
CompiledProgram CompiledProgram::freeze_impl(const resource::MemoryAccount& account,const PhysicalPlan& source,
    storage::IndexWorkAllowance* work,storage::MetadataWork mode) {
  auto binding=storage::AccountedPlanStorage::freeze_binding(account,source,work,mode);
  const auto owner=storage::detail::try_new_storage_owner();
  if(!owner)throw storage::IndexFailure(storage::IndexFault::overflow);
  const resource::MemoryAttribution attribution{resource::MemoryOwnerKind::immutable_metadata,owner->value};
  program::detail::words<Data>(work,1);
  auto result=resource::make_accounted_shared<Data>(attribution,account,resource::MemoryPurpose::immutable_metadata,std::move(binding),attribution);
  program::detail::Builder builder(*result,source,work);builder.run();return CompiledProgram(std::move(result));
}
CompiledProgram CompiledProgram::freeze(const resource::MemoryAccount& account,const CompiledProgram& source,storage::IndexWorkAllowance* work) {
  return freeze_program(account,source,work,source.data().prepared_inputs?
      std::optional{source.data().prepared_inputs->limits}:std::nullopt);
}
CompiledProgram CompiledProgram::prepare_inputs(const resource::MemoryAccount& account,const CompiledProgram& source,
    const program::InputPreparationLimits& limits,storage::IndexWorkAllowance* work) {
  program::detail::require(source.normalized().has_value());
  return freeze_program(account,source,work,limits);
}
CompiledProgram CompiledProgram::freeze_program(const resource::MemoryAccount& account,const CompiledProgram& source,
    storage::IndexWorkAllowance* work,const std::optional<program::InputPreparationLimits>& preparation) {
  storage::IndexWorkAllowance local({UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX},true);
  // Indexed admission still requires the caller's existing capped allowance.
  // The reference backend has no such allowance; a local counter records its
  // selected cold checkpoints without creating indexed execution authority.
  auto* receiving=work?work:(preparation && !source.options().indexed_storage?&local:nullptr);
  const auto before=receiving?receiving->remaining():storage::IndexWork{};
  // Validate the original indexed allowance before preparation can consume it.
  // A later preparation denial releases this unpublished base copy by RAII.
  auto binding=storage::AccountedPlanStorage::clone_binding(account,source.data().binding,receiving);
  const auto owner=storage::detail::try_new_storage_owner();if(!owner)throw storage::IndexFailure(storage::IndexFault::overflow);
  const resource::MemoryAttribution tag{resource::MemoryOwnerKind::immutable_metadata,owner->value};
  program::detail::words<Data>(receiving,1);
  auto result=resource::make_accounted_shared<Data>(tag,account,resource::MemoryPurpose::immutable_metadata,std::move(binding),tag);
  program::detail::Builder builder(*result,source,receiving);builder.run();
  if(preparation) {
    const auto base_freeze=receiving?program::detail::input_work_difference(before,receiving->remaining()):storage::IndexWork{};
    auto usage=program::detail::PreparedInputs::analyze(result->normalized,result->inputs.size(),*preparation,receiving);
    usage.base_freeze_work=base_freeze;
    result->prepared_inputs=program::detail::PreparedInputs::build(account,tag,result->normalized,result->inputs.size(),*preparation,usage,receiving);
  }
  return CompiledProgram(std::move(result));
}
program::InputExecution CompiledProgram::input_execution() const {
  return data().prepared_inputs?program::InputExecution::threaded_v1:program::InputExecution::interpreted_v1;
}
std::string_view CompiledProgram::input_execution_key() const {
  return data().prepared_inputs?"crown-input-threaded-v1":"crown-input-interpreted-v1";
}
program::InputPreparationUsage CompiledProgram::input_preparation() const {
  const auto& d=data();return d.prepared_inputs?d.prepared_inputs->usage:program::InputPreparationUsage{};
}
std::optional<program::InputPreparationLimits> CompiledProgram::input_preparation_limits() const {
  const auto& d=data();return d.prepared_inputs?std::optional{d.prepared_inputs->limits}:std::nullopt;
}
CompiledProgram CompiledProgram::replan(const CompiledProgram& basis,const planner::MinimumHeightCandidate& candidate,
    const program::ReplanLimits& limits) {
  if(!basis)throw program::ReplanFailure(program::ReplanFault::binding);
  return program::detail::NativeLowering::run(basis.account(),basis,candidate,limits);
}
CompiledProgram CompiledProgram::replan_into(const resource::MemoryAccount& account,const CompiledProgram& basis,
    const planner::MinimumHeightCandidate& candidate,const program::ReplanLimits& limits) {
  return program::detail::NativeLowering::run(account,basis,candidate,limits);
}
const CompiledProgram::Data& CompiledProgram::data() const {
  if(!data_)throw storage::IndexFailure(storage::IndexFault::invalid_storage);
  return *data_;
}
const resource::MemoryAccount& CompiledProgram::account() const & {return data().account;}
PhysicalRoute CompiledProgram::route() const {return data().route;}
const program::Catalog& CompiledProgram::catalog() const & {return data().catalog;}
const program::Query& CompiledProgram::query() const & {return data().query;}
const program::FreeConnexTree& CompiledProgram::tree() const & {return data().tree;}
const std::optional<program::NormalizedSql>& CompiledProgram::normalized() const & {return data().normalized;}
const program::ValidationReport& CompiledProgram::validation() const & {return data().validation;}
const program::QueryIdentity& CompiledProgram::identity() const & {return data().identity;}
const program::PhysicalOptions& CompiledProgram::options() const & {return data().options;}
const program::GuaranteeProfile& CompiledProgram::guarantee() const & {return data().guarantee;}
const program::EnumerationProgram& CompiledProgram::enumeration() const & {return data().enumeration;}
const storage::AccountedLayout& CompiledProgram::result_layout() const & {return data().result_layout;}
const storage::AccountedLayout& CompiledProgram::sql_result_layout() const & {return data().sql_result_layout;}
const program::Span<program::SourceTable>& CompiledProgram::sources() const & {return data().sources;}
storage::AccountedLayout CompiledProgram::scope_layout(LayoutId id,std::span<const VariableId> variables,
    std::string_view suffix,storage::IndexWorkAllowance* work) const {
  const auto& d=data();program::detail::words<storage::Field>(work,variables.size());
  program::detail::Vector<storage::Field> fields(resource::MemoryAllocator<storage::Field>(account(),resource::MemoryPurpose::scratch,d.attribution));
  fields.reserve(variables.size());
  for(const auto variable:variables) {
    program::detail::require(variable.value<d.query.variables.size());fields.push_back({d.query.variables[variable.value].type,{},variable});
  }
  return program::detail::make_layout(account(),d.attribution,id,fields,d.catalog.version,d.physical_sha256,suffix,{},work);
}
const program::Catalog& CompiledProgram::source_catalog() const & {const auto& d=data();return d.normalized?d.normalized->binding.catalog:d.catalog;}
std::shared_ptr<const program::Catalog> CompiledProgram::source_catalog_owner() const {return {data_,&source_catalog()};}
std::string_view CompiledProgram::physical_sha256() const & {return data().physical_sha256;}
std::string_view CompiledProgram::physical_source_sha256() const & {const auto& value=data().physical_source_digest;return {value.data(),value.size()};}
const program::Span<storage::AccountedLayout>& CompiledProgram::layouts() const & {return data().layouts;}
const program::Span<program::PhysicalRelation>& CompiledProgram::relations() const & {return data().relations;}
const program::Span<program::IndexRequirement>& CompiledProgram::indexes() const & {return data().indexes;}
const program::Span<program::PhysicalInput>& CompiledProgram::inputs() const & {return data().inputs;}
const program::Span<program::PhysicalNode>& CompiledProgram::nodes() const & {return data().nodes;}
const program::Span<program::PhysicalEdge>& CompiledProgram::edges() const & {return data().edges;}
const program::Span<program::Span<OccurrenceId>>& CompiledProgram::base_routes() const & {return data().base_routes;}
std::uint64_t CompiledProgram::work() const {return data().work;}
storage::AccountedPlanStorage CompiledProgram::make_storage(storage::IndexWorkAllowance* work) const {return storage::AccountedPlanStorage(data().binding,work);}
CompiledProgram runtime::detail::SqlColdRebuild::freeze(const resource::MemoryAccount& account,
    const PhysicalPlan& source,storage::IndexWorkAllowance* work) {
  // The real lowering result remains the only input. Existing compiler binding
  // import accepts a separate fixed metadata grant; no descriptor is fabricated.
  return CompiledProgram::freeze_impl(account,source,work,
      source.options().indexed_storage?storage::MetadataWork::compiler:storage::MetadataWork::execution);
}
storage::AccountedPlanStorage runtime::detail::SqlColdRebuild::storage(const CompiledProgram& source,
    storage::IndexWorkAllowance* work) {
  return storage::AccountedPlanStorage(source.data().binding,work,
      storage::AccountedPlanStorage::ColdRebuild{});
}
namespace {
using NativeSqlValue=program::SqlValue;
using frontend::sql_detail::admit_value;
using frontend::sql_detail::truth;
} // namespace

std::optional<storage::AccountedTuple> CompiledProgram::adapt_input(OccurrenceId occurrence,
    storage::RowView physical,storage::IndexWorkAllowance* work) const {
  const auto& d=data();const auto& input=d.inputs.at(occurrence.value);
  const auto issue=input.physical_layout.validation_issue(physical);
  if(!issue.ok())throw storage::TupleValidationFailure(issue);
  for(const auto& value:physical.cells())admit_value(work,value);
  program::detail::Vector<storage::ScalarView> logical(resource::MemoryAllocator<storage::ScalarView>(account(),resource::MemoryPurpose::scratch));
  storage::RowView source=physical;
  if(d.normalized) {
    const auto& sql=*d.normalized;const auto& adapter=sql.adapters.at(occurrence.value);
    for(const auto& fixed:adapter.constant_columns) {
      program::detail::step(work);admit_value(work,fixed.value);admit_value(work,physical.at(fixed.column.value));
      if(physical.at(fixed.column.value)!=fixed.value)return {};
    }
    for(const auto& equality:adapter.equal_columns) {
      program::detail::step(work);admit_value(work,physical.at(equality.left.value));admit_value(work,physical.at(equality.right.value));
      if(physical.at(equality.left.value)!=physical.at(equality.right.value))return {};
    }
    program::detail::words<NativeSqlValue>(work,sql.constants.size());
    program::detail::Vector<NativeSqlValue> values(sql.constants.begin(),sql.constants.end(),
        resource::MemoryAllocator<NativeSqlValue>(account(),resource::MemoryPurpose::scratch));
    if(d.prepared_inputs)d.prepared_inputs->execute(occurrence,physical,values,work);
    else for(const auto id:adapter.program) {
        program::detail::step(work);const auto& expression=sql.binding.expressions.at(id.value).node;
        if(const auto* column=std::get_if<program::BoundColumn>(&expression)) {
          program::detail::require(column->occurrence==occurrence);values.at(id.value)=physical.at(column->column.value);
        } else if(const auto* operation=std::get_if<program::BoundOperation>(&expression))values.at(id.value)=frontend::sql_detail::evaluate(operation->operation,operation->arguments,values,work);
        else throw storage::IndexFailure(storage::IndexFault::contract);
      }
    for(const auto id:adapter.predicates) {program::detail::step(work);if(truth(values.at(id.value))!=std::optional<bool>{true})return {};}
    program::detail::words<storage::ScalarView>(work,adapter.projection.size());logical.reserve(adapter.projection.size());
    for(const auto& field:adapter.projection) {
      const auto& value=values.at(field.expression.value);program::detail::require(value.has_value());logical.push_back(*value);
    }
    source=storage::RowView::borrow(logical);
  }
  for(const auto& equality:input.equalities) {
    program::detail::step(work);admit_value(work,source.at(equality.left.value));admit_value(work,source.at(equality.right.value));
    if(source.at(equality.left.value)!=source.at(equality.right.value))return {};
  }
  for(const auto& fixed:input.constants) {
    program::detail::step(work);admit_value(work,source.at(fixed.field.value));admit_value(work,fixed.value);
    if(source.at(fixed.field.value)!=fixed.value)return {};
  }
  for(const auto field:input.projection.fields())admit_value(work,source.at(field.value));
  return input.projection.apply(source);
}
} // namespace crown

namespace crown::program {
JsonKind JsonView::kind() const noexcept {return node_?static_cast<JsonKind>(node_->value.index()):JsonKind::null;}
std::size_t JsonView::size() const noexcept {
  if(is_array())return std::get<Span<detail::JsonNode>>(node_->value).size();
  if(is_object())return std::get<Span<detail::JsonMember>>(node_->value).size();
  return is_null()?0:1;
}
JsonView JsonView::at(std::size_t i) const {detail::require(is_array());return JsonView(&std::get<Span<detail::JsonNode>>(node_->value).at(i));}
std::string_view JsonView::key(std::size_t i) const {detail::require(is_object());return std::get<Span<detail::JsonMember>>(node_->value).at(i).key;}
JsonView JsonView::member(std::size_t i) const {detail::require(is_object());return JsonView(&std::get<Span<detail::JsonMember>>(node_->value).at(i).value);}
bool JsonView::boolean() const {detail::require(kind()==JsonKind::boolean);return std::get<bool>(node_->value);}
std::int64_t JsonView::integer() const {detail::require(kind()==JsonKind::integer);return std::get<std::int64_t>(node_->value);}
std::uint64_t JsonView::unsigned_integer() const {detail::require(kind()==JsonKind::unsigned_integer);return std::get<std::uint64_t>(node_->value);}
double JsonView::number() const {detail::require(kind()==JsonKind::number);return std::get<double>(node_->value);}
std::string_view JsonView::text() const {detail::require(kind()==JsonKind::string);return std::get<std::string_view>(node_->value);}
} // namespace crown::program
