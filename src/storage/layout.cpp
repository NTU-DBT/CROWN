#include "crown/storage/layout.hpp"
#include "crown/storage/accounted_layout.hpp"
#include "crown/storage/accounted_projection.hpp"
#include "descriptor.hpp"
#include "tuple_payload.hpp"
#include "crown/resource/ownership.hpp"
#include <algorithm>

#include "crown/api/error.hpp"
#include "crown/catalog/catalog.hpp"
#include <map>
#include <utility>

namespace crown::storage {
struct TupleLayout::Data:detail::LayoutDescriptor {
  std::vector<Field> owned_fields;
  LayoutContext owned_context;
  std::vector<detail::DescriptorEquality> owned_equalities;
  Data(LayoutId id,std::vector<Field> fields,LayoutContext context,std::optional<LayoutOrigin> origin,
      std::vector<detail::DescriptorEquality> equalities)
      :owned_fields(std::move(fields)),owned_context(std::move(context)),owned_equalities(std::move(equalities)) {
    layout_id=id;field_view=owned_fields;context_view={owned_context.catalog_version,owned_context.binding};
    origin_value=origin;equality_view=owned_equalities;
  }
};
struct Projection::Data:detail::ProjectionDescriptor {
  std::vector<FieldId> owned_fields;
  Data(TupleLayout from,TupleLayout to,std::vector<FieldId> fields)
      :detail::ProjectionDescriptor(std::move(from),std::move(to)),owned_fields(std::move(fields)) {field_view=owned_fields;}
};

namespace {
struct LegacyTuplePayload:detail::TuplePayload {
  Row owned;
  explicit LegacyTuplePayload(Row row) noexcept:owned(std::move(row)){legacy=&owned;}
};
struct NativeTuplePayload:detail::TuplePayload {
  AccountedTuple owned;
  NativeTuplePayload(const resource::MemoryAccount& memory,AccountedTuple row) noexcept:owned(std::move(row)) {
    account=memory;native=owned.values();
  }
};
void require(bool value,std::string_view code,std::string_view message) { if (!value) throw Error(std::string(code),std::string(message)); }
// Inclusion of exact decimal domains; no conversion/rounding is performed.
bool fits_domain(const Field& source,const Field& target) {
  if (source.type != target.type) return false;
  if (!target.decimal) return true;
  return source.decimal && source.decimal->scale <= target.decimal->scale &&
      source.decimal->precision-source.decimal->scale <= target.decimal->precision-target.decimal->scale;
}
}  // namespace

TupleLayout::TupleLayout(LayoutId id,std::vector<Field> fields,LayoutContext context,std::optional<LayoutOrigin> origin) {
  require(context.catalog_version>0,"invalid_layout","layout catalog version must be positive");
  require(!origin || origin->source_schema_version>0,"invalid_layout","layout source version must be positive");
  std::map<VariableId,FieldId> first;
  std::vector<detail::DescriptorEquality> equalities;
  for (std::size_t i=0;i<fields.size();++i) {
    const auto& field=fields[i]; static_cast<void>(type_name(field.type));
    require(!field.decimal || (field.type==ScalarType::decimal && field.decimal->precision>=1 && field.decimal->precision<=38 && field.decimal->scale<=field.decimal->precision),
        "invalid_layout","invalid fixed-decimal field specification");
    if (field.variable) {
      const auto [entry,inserted]=first.emplace(*field.variable,FieldId{i});
      if (!inserted) {
        require(fields[entry->second.value].type==field.type,"invalid_layout","one layout variable has incompatible scalar types");
        equalities.push_back({entry->second,FieldId{i}});
      }
    }
  }
  data_=std::make_shared<Data>(id,std::move(fields),std::move(context),origin,std::move(equalities));
}
LayoutId TupleLayout::id() const { require(bool(data_),"invalid_layout","moved-from tuple layout"); return data_->layout_id; }
const std::span<const Field>& TupleLayout::fields() const { static_cast<void>(id()); return data_->field_view; }
const LayoutContextView& TupleLayout::context() const { static_cast<void>(id()); return data_->context_view; }
const std::optional<LayoutOrigin>& TupleLayout::origin() const { static_cast<void>(id()); return data_->origin_value; }
bool TupleLayout::same_token(const TupleLayout& other) const noexcept { return data_ && data_==other.data_; }
bool TupleLayout::same_token(const AccountedLayout& other) const noexcept {return other.same_token(*this);}
bool TupleLayout::same_descriptor(const TupleLayout& other) const {
  return id()==other.id() && std::ranges::equal(fields(),other.fields()) && context()==other.context() && origin()==other.origin();
}
void TupleLayout::validate(const Row& values) const {
  const auto& schema=fields();
  require(values.size()==schema.size(),"invalid_tuple","tuple arity differs from compiled layout");
  for (std::size_t i=0;i<schema.size();++i) {
    if (type_of(values[i])!=schema[i].type) throw Error("invalid_tuple","tuple scalar kind differs at field "+std::to_string(i));
    if (schema[i].decimal) require(catalog::decimal_fits(std::get<Decimal>(values[i]),*schema[i].decimal),"scalar_overflow","tuple decimal exceeds the exact field domain");
  }
  for (const auto& [left,right] : data_->equality_view) require(values[left.value]==values[right.value],"invalid_tuple","repeated layout variable has unequal values");
}
void TupleLayout::validate_view(TupleValuesView values) const {
  if(const auto* legacy=values.legacy_row()){validate(*legacy);return;}
  const auto& schema=fields();
  require(values.size()==schema.size(),"invalid_tuple","tuple arity differs from compiled layout");
  for(std::size_t i=0;i<schema.size();++i) {
    const auto value=values[i];
    if(value.index()!=static_cast<std::size_t>(schema[i].type))throw Error("invalid_tuple","tuple scalar kind differs at field "+std::to_string(i));
    if(schema[i].decimal) {
      const auto parts=std::get<InlineDecimal>(value).parts();
      const auto integer_digits=parts.digits=="0" || parts.digits.size()<=parts.scale?std::size_t{0}:parts.digits.size()-parts.scale;
      require(parts.scale<=schema[i].decimal->scale && integer_digits+schema[i].decimal->scale<=schema[i].decimal->precision,
          "scalar_overflow","tuple decimal exceeds the exact field domain");
    }
  }
  for(const auto& [left,right]:data_->equality_view)require(values[left.value]==values[right.value],"invalid_tuple","repeated layout variable has unequal values");
}
// Public validation preserves formatted Error diagnostics. Native descriptor
// factories also validate while constructing funded payloads; this path currently
// pays both passes. Direct AccountedLayout callers use its one native boundary.
Tuple TupleLayout::tuple(const Row& values) const {
  validate(values);
  if(data_->make_native_tuple)return data_->make_native_tuple(*this,TupleValuesView::borrow(values));
  return Tuple(*this,std::make_shared<LegacyTuplePayload>(values));
}
Tuple TupleLayout::tuple(Row&& values) const {
  validate(values);
  if(data_->make_native_tuple)return data_->make_native_tuple(*this,TupleValuesView::borrow(values));
  return Tuple(*this,std::make_shared<LegacyTuplePayload>(std::move(values)));
}
Tuple TupleLayout::tuple_view(TupleValuesView values) const {
  validate_view(values);
  if(data_->make_native_tuple)return data_->make_native_tuple(*this,std::move(values));
  // Explicit standalone compiler/tool owning output. Runtime descriptors always
  // retain the native factory and its original query account.
  return Tuple(*this,std::make_shared<LegacyTuplePayload>(export_row(std::move(values))));
}
Tuple::Tuple(TupleLayout layout,std::shared_ptr<const detail::TuplePayload> values) noexcept
    :layout_(std::move(layout)),payload_(std::move(values)) {}
// Standalone rows deep-copy their values; admitted native payloads share their
// immutable owner. Copy cost therefore depends on the payload representation.
Tuple::Tuple(const Tuple& other):layout_(other.layout_) {
  if(other.payload_ && other.payload_->legacy)payload_=std::make_shared<LegacyTuplePayload>(*other.payload_->legacy);
  else payload_=other.payload_;
}
Tuple Tuple::from_accounted(AccountedTuple row) {
  const auto account=row.layout().query_account();const auto attribution=row.attribution();
  const auto before=account.statistics().current;
  auto owner=resource::make_accounted_shared<NativeTuplePayload>(attribution,account,resource::MemoryPurpose::output_buffer,account,std::move(row));
  const auto after=account.statistics().current;
  // The constructor only moves an admitted tuple and copies account handles.
  // Therefore this exact difference is the shared object's real allocation(s),
  // including rebound control-block storage and all account framing. It is not
  // a reserved accounting ticket or a scan of the allocation ledger.
  const auto values=owner->owned.memory_usage();
  owner->usage={after.allocations-before.allocations+values.allocations,
      after.requested_bytes-before.requested_bytes+values.requested_bytes,
      after.payload_bytes-before.payload_bytes+values.payload_bytes};
  auto layout=owner->owned.layout().descriptor();return Tuple(std::move(layout),std::move(owner));
}
bool Tuple::is_accounted() const noexcept{return payload_ && bool(payload_->account);}
resource::MemoryUsage Tuple::memory_usage() const noexcept{return payload_?payload_->usage:resource::MemoryUsage{};}
resource::MemoryStatistics Tuple::account_statistics() const {
  if(!is_accounted())throw resource::MemoryFailure(resource::MemoryFault::contract);
  return payload_->account.statistics();
}
Tuple& Tuple::operator=(const Tuple& other) {
  if (this!=&other) {
    Tuple next(other);
    std::swap(layout_,next.layout_); payload_.swap(next.payload_);
  }
  return *this;
}
Tuple& Tuple::operator=(Tuple&& other) noexcept {
  if (this!=&other) {
    layout_=std::move(other.layout_); payload_=std::move(other.payload_);
  }
  return *this;
}

Projection::Projection(TupleLayout source,TupleLayout target,std::vector<FieldId> fields) {
  require(source.context()==target.context(),"invalid_projection","projection layouts belong to different catalog/query contexts");
  require(fields.size()==target.fields().size(),"invalid_projection","projection arity differs from target layout");
  std::map<VariableId,FieldId> first;
  for (std::size_t i=0;i<fields.size();++i) {
    require(fields[i].value<source.fields().size(),"invalid_projection","projection source field is out of range");
    const auto& input=source.fields()[fields[i].value]; const auto& output=target.fields()[i];
    require(fits_domain(input,output),"invalid_projection","projection changes scalar kind or narrows an exact decimal domain");
    require(!input.variable || !output.variable || input.variable==output.variable,"invalid_projection","projection changes a bound variable identity");
    if (output.variable) {
      const auto [entry,inserted]=first.emplace(*output.variable,fields[i]);
      if (!inserted) {
        const auto& previous=source.fields()[entry->second.value];
        require(entry->second==fields[i] || (previous.variable && previous.variable==input.variable),"invalid_projection","repeated target variable is not justified by the source layout");
      }
    }
  }
  data_=std::make_shared<Data>(std::move(source),std::move(target),std::move(fields));
}
const TupleLayout& Projection::source() const { require(bool(data_),"invalid_projection","moved-from projection"); return data_->source; }
const TupleLayout& Projection::target() const { static_cast<void>(source()); return data_->target; }
const std::span<const FieldId>& Projection::fields() const { static_cast<void>(source()); return data_->field_view; }
bool Projection::same_token(const Projection& other) const noexcept { return data_ && data_==other.data_; }
bool Projection::same_token(const AccountedProjection& other) const noexcept {return other && same_token(other.descriptor());}
Tuple Projection::apply(const Tuple& tuple) const {
  require(source().same_token(tuple.layout()),"layout_mismatch","projection input has a different immutable layout token");
  if(data_->apply_native_tuple)return data_->apply_native_tuple(*this,tuple);
  Row result; result.reserve(fields().size());
  for (const auto field : fields()) result.push_back(export_scalar(tuple.values()[field.value]));
  return target().tuple(std::move(result));
}
TupleLayout table_layout(LayoutId id,const Catalog& schema,TableId table,std::string binding) {
  catalog::validate_catalog(schema);
  require(table.value<schema.tables.size(),"invalid_layout","table layout source is out of range");
  const auto& input=schema.tables[table.value]; std::vector<Field> fields;
  for (const auto& column : input.columns) {
    require(!column.nullable,"unsupported_nullability","classical tuple layouts require non-null fields");
    fields.push_back({column.type,column.decimal,{}});
  }
  return {id,std::move(fields),{schema.version,std::move(binding)},LayoutOrigin{table,input.source_schema_version}};
}
TupleLayout scope_layout(LayoutId id,const Query& query,std::span<const VariableId> variables,LayoutContext context) {
  std::vector<Field> fields;
  for (const auto variable : variables) {
    require(variable.value<query.variables.size(),"invalid_layout","scope variable is out of range");
    fields.push_back({query.variables[variable.value].type,{},variable});
  }
  return {id,std::move(fields),std::move(context)};
}
TupleLayout projected_layout(LayoutId id,const TupleLayout& source,std::span<const FieldId> fields) {
  std::vector<Field> selected;
  for (const auto field : fields) {
    require(field.value<source.fields().size(),"invalid_projection","projection source field is out of range");
    selected.push_back(source.fields()[field.value]);
  }
  return {id,std::move(selected),{source.context().catalog_version,std::string(source.context().binding)}};
}
}  // namespace crown::storage
