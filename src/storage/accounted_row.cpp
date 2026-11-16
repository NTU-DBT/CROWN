#include "crown/storage/accounted_row.hpp"
#include "crown/storage/tuple_values.hpp"
#include "crown/api/error.hpp"

#include <algorithm>
#include <cstring>
#include <exception>
#include <limits>
#include <memory>
#include <type_traits>
#include <utility>

namespace crown::storage {
namespace {
using resource::MemoryFailure;
using resource::MemoryFault;
static_assert(std::is_trivially_destructible_v<ScalarView>);
static_assert(std::is_nothrow_move_constructible_v<ScalarView>);
static_assert(std::is_nothrow_copy_constructible_v<ScalarView>);

std::size_t checked_add(std::size_t left, std::size_t right) {
  if (right > std::numeric_limits<std::size_t>::max() - left)
    throw MemoryFailure(MemoryFault::overflow);
  return left + right;
}
ScalarView borrow(const Value& value) {
  if (const auto* cell = std::get_if<std::int64_t>(&value)) return *cell;
  if (const auto* cell = std::get_if<std::string>(&value)) return std::string_view(*cell);
  if (const auto* cell = std::get_if<bool>(&value)) return *cell;
  if (const auto* cell = std::get_if<Date>(&value)) return *cell;
  if (const auto* cell = std::get_if<Decimal>(&value)) return InlineDecimal::copy_of(*cell);
  throw MemoryFailure(MemoryFault::contract);
}
template<class Read> std::size_t cell_payload_bytes(std::size_t size,Read read) {
  if(size>std::numeric_limits<std::size_t>::max()/sizeof(ScalarView))throw MemoryFailure(MemoryFault::overflow);
  auto bytes=size*sizeof(ScalarView);
  for(std::size_t i=0;i<size;++i) {
    const auto cell=read(i);
    if(const auto* text=std::get_if<std::string_view>(&cell))bytes=checked_add(bytes,text->size());
  }
  return bytes;
}
template<class Read>
resource::MemoryBlock copy_cells(const resource::MemoryAccount& account, resource::MemoryAttribution attribution,
                                std::size_t size, Read read) {
  // One preflight calculation is shared with exact native queue admission.
  // Caller cells and string bytes stay alive and unchanged through both
  // preflight and copying; one funded block owns the returned payload bytes.
  const auto bytes=cell_payload_bytes(size,read);
  const auto descriptors=size*sizeof(ScalarView);
  auto block = account.allocate(bytes, alignof(ScalarView), resource::MemoryPurpose::tuple_values, attribution);
  auto* cells = static_cast<ScalarView*>(block.data());
  auto* tail = static_cast<char*>(block.data()) + descriptors;
  for (std::size_t i = 0; i < size; ++i) {
    auto cell = read(i);
    if (auto* text = std::get_if<std::string_view>(&cell)) {
      if (!text->empty()) std::memcpy(tail, text->data(), text->size());
      *text = std::string_view(tail, text->size());
      tail += text->size();
    }
    std::construct_at(cells + i, std::move(cell));
  }
  // ScalarView has a trivial destructor, including its inline Decimal. No
  // nested allocation or allocating cleanup exists after block admission.
  return block;
}

class Hasher {
 public:
  void byte(std::uint8_t value) noexcept { hash_ = (hash_ ^ value) * 1099511628211ULL; }
  void integer(std::uint64_t value) noexcept {
    for (unsigned i = 0; i < 8; ++i) { byte(static_cast<std::uint8_t>(value & 0xff)); value >>= 8; }
  }
  void text(std::string_view value) noexcept {
    integer(value.size());
    for (char character : value) byte(static_cast<std::uint8_t>(static_cast<unsigned char>(character)));
  }
  void value(const ScalarView& cell) noexcept {
    byte(static_cast<std::uint8_t>(cell.index()));
    if (const auto* number = std::get_if<std::int64_t>(&cell)) integer(static_cast<std::uint64_t>(*number));
    else if (const auto* string = std::get_if<std::string_view>(&cell)) text(*string);
    else if (const auto* boolean = std::get_if<bool>(&cell)) byte(*boolean ? 1 : 0);
    else if (const auto* date = std::get_if<Date>(&cell)) integer(static_cast<std::uint64_t>(date->epoch_days()));
    else if (const auto* decimal = std::get_if<InlineDecimal>(&cell)) {
      std::array<char, InlineDecimal::text_capacity> buffer{};
      const auto size = decimal->render(buffer);
      text(std::string_view(buffer.data(), size));
    } else std::terminate();  // No alternative can become valueless by throwing a move/copy.
  }
  [[nodiscard]] std::uint64_t get() const noexcept { return hash_; }
 private:
  std::uint64_t hash_ = 14695981039346656037ULL;
};
}  // namespace

InlineDecimal InlineDecimal::parse(std::string_view text) {
  if(text.empty())throw Error("invalid_scalar","decimal must contain digits");
  InlineDecimal result;std::size_t begin=0;
  if(text[0]=='+' || text[0]=='-'){result.negative_=text[0]=='-';begin=1;}
  const auto point=text.find('.',begin);
  const auto integer_end=point==std::string_view::npos?text.size():point;
  if(begin==integer_end || (point!=std::string_view::npos && point+1==text.size()))
    throw Error("invalid_scalar","decimal requires digits on both sides of a decimal point");
  for(std::size_t i=begin;i<text.size();++i)
    if(i!=point && (text[i]<'0' || text[i]>'9'))
      throw Error("invalid_scalar","decimal admits only an optional sign, digits and one decimal point");
  auto end=text.size();
  if(point!=std::string_view::npos)while(end>point+1 && text[end-1]=='0')--end;
  const auto scale=point==std::string_view::npos?0:end-point-1;
  std::size_t size=0;bool significant=false;
  for(std::size_t i=begin;i<end;++i) {
    if(i==point)continue;
    significant=significant || text[i]!='0';if(!significant)continue;
    if(size==result.digits_.size())throw Error("scalar_overflow","decimal coefficient exceeds 38 digits");
    result.digits_[size++]=text[i];
  }
  if(size==0)return InlineDecimal{};
  if(scale>38)throw Error("scalar_overflow","decimal scale exceeds 38");
  result.digits_size_=static_cast<std::uint8_t>(size);result.scale_=static_cast<std::uint8_t>(scale);return result;
}
InlineDecimal InlineDecimal::copy_of(const Decimal& value) noexcept {
  const auto parts = value.parts();
  InlineDecimal result;
  result.digits_size_ = static_cast<std::uint8_t>(parts.digits.size());
  result.scale_ = static_cast<std::uint8_t>(parts.scale);
  result.negative_ = parts.negative;
  std::copy(parts.digits.begin(), parts.digits.end(), result.digits_.begin());
  return result;
}
std::size_t InlineDecimal::render(std::span<char> output) const {
  const auto value = parts();
  const auto body = value.scale == 0 ? value.digits.size() :
      std::max(value.digits.size(), static_cast<std::size_t>(value.scale) + 1) + 1;
  const auto required = body + (value.negative ? 1U : 0U);
  if (output.size() < required) throw MemoryFailure(MemoryFault::contract);
  std::size_t position = 0;
  if (value.negative) output[position++] = '-';
  if (value.scale == 0) {
    for (char digit : value.digits) output[position++] = digit;
  } else if (value.digits.size() > value.scale) {
    const auto point = value.digits.size() - value.scale;
    for (std::size_t i = 0; i < value.digits.size(); ++i) {
      if (i == point) output[position++] = '.';
      output[position++] = value.digits[i];
    }
  } else {
    output[position++] = '0';output[position++] = '.';
    for (std::size_t i = value.digits.size(); i < value.scale; ++i) output[position++] = '0';
    for (char digit : value.digits) output[position++] = digit;
  }
  return position;
}
bool InlineDecimal::operator==(const InlineDecimal& other) const noexcept {
  const auto left = parts(), right = other.parts();
  return left.digits == right.digits && left.scale == right.scale && left.negative == right.negative;
}
std::strong_ordering InlineDecimal::operator<=>(const InlineDecimal& other) const noexcept {
  const auto left = parts(), right = other.parts();
  if (left.digits == "0" || right.digits == "0") {
    if (left.digits == right.digits) return std::strong_ordering::equal;
    if (left.digits == "0") return right.negative ? std::strong_ordering::greater : std::strong_ordering::less;
    return left.negative ? std::strong_ordering::less : std::strong_ordering::greater;
  }
  if (left.negative != right.negative) return left.negative ? std::strong_ordering::less : std::strong_ordering::greater;
  const auto exponent = static_cast<std::int64_t>(left.digits.size()) - static_cast<std::int64_t>(left.scale);
  const auto other_exponent = static_cast<std::int64_t>(right.digits.size()) - static_cast<std::int64_t>(right.scale);
  auto order = exponent <=> other_exponent;
  if (order == 0) {
    for (std::size_t i = 0; i < std::max(left.digits.size(), right.digits.size()); ++i) {
      const auto a = i < left.digits.size() ? left.digits[i] : '0';
      const auto b = i < right.digits.size() ? right.digits[i] : '0';
      order = a <=> b;
      if (order != 0) break;
    }
  }
  if (!left.negative || order == 0) return order;
  return order < 0 ? std::strong_ordering::greater : std::strong_ordering::less;
}

const ScalarView& RowView::at(std::size_t index) const {
  if (index >= size_) throw MemoryFailure(MemoryFault::contract);
  return data_[index];
}
std::uint64_t RowView::hash() const noexcept {
  Hasher hasher;
  hasher.integer(size_);
  for (const auto& value : cells()) hasher.value(value);
  return hasher.get();
}
bool RowView::operator==(RowView other) const noexcept {
  return size_ == other.size_ && (*this <=> other) == 0;
}
std::strong_ordering RowView::operator<=>(RowView other) const noexcept {
  for (std::size_t i = 0; i < std::min(size_, other.size_); ++i) {
    const auto order = data_[i] <=> other.data_[i];
    if (order != 0) return order;
  }
  return size_ <=> other.size_;
}

ScalarView borrow_scalar(const Value& value) { return borrow(value); }
ScalarType type_of(const ScalarView& value) {
  if(value.valueless_by_exception())throw resource::MemoryFailure(resource::MemoryFault::contract);
  return static_cast<ScalarType>(value.index());
}
bool operator==(const ScalarView& left,const Value& right){return left==borrow(right);}
std::strong_ordering operator<=>(const ScalarView& left,const Value& right){return left<=>borrow(right);}
std::strong_ordering operator<=>(RowView left,const Row& right) {
  for (std::size_t i=0;i<std::min(left.size(),right.size());++i) {
    const auto order=left[i]<=>borrow(right[i]);if(order!=0)return order;
  }
  return left.size()<=>right.size();
}
bool operator==(RowView left,const Row& right) { return left.size()==right.size() && (left<=>right)==0; }
Value export_scalar(const ScalarView& value) {
  return std::visit([](const auto& cell)->Value {
    using T=std::decay_t<decltype(cell)>;
    if constexpr(std::is_same_v<T,std::string_view>) return std::string(cell);
    else if constexpr(std::is_same_v<T,InlineDecimal>) {
      std::array<char,InlineDecimal::text_capacity> text{};const auto count=cell.render(text);
      return Decimal::parse(std::string_view(text.data(),count));
    } else return cell;
  },value);
}
Row export_row(RowView values) {
  Row result;result.reserve(values.size());
  for(const auto& value:values.cells()) result.push_back(export_scalar(value));
  return result;
}

AccountedRow::AccountedRow(AccountedRow&& other) noexcept
    : block_(std::move(other.block_)), size_(std::exchange(other.size_, 0)) {}
AccountedRow& AccountedRow::operator=(AccountedRow&& other) noexcept {
  if (this != &other) { block_ = std::move(other.block_);size_ = std::exchange(other.size_, 0); }
  return *this;
}
AccountedRow AccountedRow::copy_of(const resource::MemoryAccount& account, const Row& values,
                                 resource::MemoryAttribution attribution) {
  return AccountedRow(copy_cells(account, attribution, values.size(), [&](std::size_t i) { return borrow(values[i]); }), values.size());
}
AccountedRow AccountedRow::copy_of(const resource::MemoryAccount& account, RowView values,
                                 resource::MemoryAttribution attribution) {
  return AccountedRow(copy_cells(account, attribution, values.size(), [&](std::size_t i) { return values[i]; }), values.size());
}
resource::MemoryUsage AccountedRow::allocation_usage_for(const Row& values) {
  const auto bytes=cell_payload_bytes(values.size(),[&](std::size_t i){return borrow(values[i]);});
  return {1,resource::MemoryAccount::allocation_bytes(bytes,alignof(ScalarView)),bytes};
}
resource::MemoryUsage AccountedRow::allocation_usage_for(TupleValuesView values) {
  const auto bytes=cell_payload_bytes(values.size(),[&](std::size_t i){return values[i];});
  return {1,resource::MemoryAccount::allocation_bytes(bytes,alignof(ScalarView)),bytes};
}
AccountedRow AccountedRow::copy_view(const resource::MemoryAccount& account,TupleValuesView values,
                                  resource::MemoryAttribution attribution) {
  return AccountedRow(copy_cells(account,attribution,values.size(),[&](std::size_t i){return values[i];}),values.size());
}
AccountedRow AccountedRow::project(const resource::MemoryAccount& account, RowView values,
                                 std::span<const FieldId> fields, resource::MemoryAttribution attribution) {
  for (const auto field : fields)
    if (field.value >= values.size()) throw MemoryFailure(MemoryFault::contract);
  // Gather directly into one admitted descriptor/payload block. There is no
  // temporary Row/vector or borrowed string retained in the result.
  return AccountedRow(copy_cells(account, attribution, fields.size(),
      [&](std::size_t i) { return values[fields[i].value]; }), fields.size());
}
RowView AccountedRow::view() const & noexcept {
  return RowView(static_cast<const ScalarView*>(block_.data()), size_);
}

}  // namespace crown::storage
