#include "native_input.hpp"
#include "input_native.hpp"
#include "catalog_source.hpp"
#include "ingest_text.hpp"
#include "crown/api/error.hpp"
#include "crown/catalog/catalog.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <charconv>
#include <limits>

namespace crown::io::input_detail {
namespace {
void require(bool ok,std::string_view code,std::string_view message) {
  if(!ok)throw Error(std::string(code),std::string(message));
}
void bounded(std::size_t size,std::size_t limit,std::string_view message) {
  require(size<=limit,"resource_limit",message);
}
struct Cell {
  resource::AccountedText text;
  storage::ScalarView value{std::int64_t{0}};
};
// Cell/text views stay backed until the compact row owns every payload.
// Full row/domain validation follows this freeze and can still reject it.
struct Builder {
  const resource::MemoryAccount& account;
  Vector<Cell> cells;
  Decoded decoded;
  explicit Builder(const resource::MemoryAccount& memory):account(memory),cells(allocator<Cell>(account)) {}
  void value(storage::ScalarView value) {cells.push_back({{},value});}
  void text(std::string_view text) {
    auto owned=resource::AccountedText::copy_of(account,text,memory_owner);
    auto view=owned.view();cells.push_back({std::move(owned),view});
  }
  void source(std::string_view name,std::uint64_t offset) {
    decoded.source=resource::AccountedText::copy_of(account,name,memory_owner);
    decoded.event.source_position=SourcePositionView{decoded.source.view(),offset};
  }
  Decoded finish(const auto& catalog,const InputLimits& limits) {
    Vector<storage::ScalarView> values(allocator<storage::ScalarView>(account));values.reserve(cells.size());
    for(const auto& cell:cells)values.push_back(cell.value);
    decoded.row=storage::AccountedRow::copy_of(account,storage::RowView::borrow(values),memory_owner);
    decoded.event.update.values=storage::TupleValuesView::borrow(decoded.row.view());
    validate(decoded.event,catalog,limits,row_issue(catalog,decoded.event.update.table,decoded.event.update.values));
    return std::move(decoded);
  }
};
TableId native_table(const auto& catalog,std::string_view name) {
  // The reader validated a standalone catalog once, or retained an admitted
  // immutable program. Public find_table() revalidates with ordinary scratch.
  for(std::size_t i=0;i<catalog.tables.size();++i)
    if(catalog.tables[i].name==name)return TableId{i};
  throw Error("unknown_table","unknown table: "+std::string(name));
}
void binding(std::uint64_t version,std::uint64_t source,std::string_view hash,TableId id,const auto& catalog,std::string_view expected) {
  require(version==catalog.version && source==catalog.tables[id.value].source_schema_version && hash==expected,
      "catalog_mismatch","input catalog or source schema binding differs from the supplied catalog");
}
// The event schema bounds nesting to root/source/tagged scalar/values.
// Successful token/cell storage uses the supplied account, with no JSON DOM
// or general nesting stack. Errors retain the public diagnostic construction.
class JsonReader {
  struct Integer {std::uint64_t magnitude;bool negative;};
  const resource::MemoryAccount& account_;
  std::string_view input_;
  const InputLimits& limits_;
  std::size_t at_=0;
  Buffer token_;
  Builder builder_;
  resource::AccountedText hash_,table_;
  std::uint64_t version_=0,catalog_version_=0,source_version_=0;
  unsigned seen_=0;
  [[noreturn]] static void invalid() {throw Error("invalid_document","input JSON token does not match the physical event schema");}
  [[noreturn]] static void syntax() {throw Error("invalid_document","invalid physical event JSON");}
  void space() {while(at_<input_.size() && (input_[at_]==' ' || input_[at_]=='\t' || input_[at_]=='\r' || input_[at_]=='\n'))++at_;}
  bool accept(char ch) {space();if(at_==input_.size() || input_[at_]!=ch)return false;++at_;return true;}
  void expect(char ch) {if(!accept(ch))syntax();}
  char take() {if(at_==input_.size())syntax();return input_[at_++];}
  static unsigned digit(char ch) {
    if(ch>='0' && ch<='9')return static_cast<unsigned>(ch-'0');
    if(ch>='a' && ch<='f')return static_cast<unsigned>(ch-'a'+10);
    if(ch>='A' && ch<='F')return static_cast<unsigned>(ch-'A'+10);
    syntax();
  }
  std::uint32_t hex() {std::uint32_t result=0;for(unsigned i=0;i<4;++i)result=(result<<4U)|digit(take());return result;}
  void utf8(std::uint32_t code) {
    if(code<=0x7fU)token_.push_back(static_cast<char>(code));
    else if(code<=0x7ffU) {
      token_.push_back(static_cast<char>(0xc0U|(code>>6U)));token_.push_back(static_cast<char>(0x80U|(code&0x3fU)));
    }else if(code<=0xffffU) {
      token_.push_back(static_cast<char>(0xe0U|(code>>12U)));token_.push_back(static_cast<char>(0x80U|((code>>6U)&0x3fU)));token_.push_back(static_cast<char>(0x80U|(code&0x3fU)));
    }else {
      token_.push_back(static_cast<char>(0xf0U|(code>>18U)));token_.push_back(static_cast<char>(0x80U|((code>>12U)&0x3fU)));
      token_.push_back(static_cast<char>(0x80U|((code>>6U)&0x3fU)));token_.push_back(static_cast<char>(0x80U|(code&0x3fU)));
    }
  }
  // Borrowed result expires on the next string token; field acceptance is later,
  // so token scratch can approach record_bytes before field_bytes rejects it.
  std::string_view string() {
    space();if(at_==input_.size() || input_[at_]!='"')invalid();++at_;token_.clear();
    for(;;) {
      const auto ch=take();if(ch=='"')break;
      if(static_cast<unsigned char>(ch)<32U)syntax();
      if(ch!='\\'){token_.push_back(ch);continue;}
      switch(take()) {
        case '"':token_.push_back('"');break;
        case '\\':token_.push_back('\\');break;
        case '/':token_.push_back('/');break;
        case 'b':token_.push_back('\b');break;
        case 'f':token_.push_back('\f');break;
        case 'n':token_.push_back('\n');break;
        case 'r':token_.push_back('\r');break;
        case 't':token_.push_back('\t');break;
        case 'u': {
          auto code=hex();
          if(code>=0xd800U && code<=0xdbffU) {
            if(take()!='\\' || take()!='u')syntax();
            const auto low=hex();if(low<0xdc00U || low>0xdfffU)syntax();
            code=0x10000U+((code-0xd800U)<<10U)+(low-0xdc00U);
          }else if(code>=0xdc00U && code<=0xdfffU)syntax();
          utf8(code);break;
        }
        default:syntax();
      }
    }
    ingest_detail::require_utf8(token_.view());return token_.view();
  }
  Integer integer() {
    space();const bool negative=at_<input_.size() && input_[at_]=='-';if(negative)++at_;
    if(at_==input_.size() || input_[at_]<'0' || input_[at_]>'9')invalid();
    const auto digits=at_;
    if(input_[at_]=='0')++at_;
    else while(at_<input_.size() && input_[at_]>='0' && input_[at_]<='9')++at_;
    if(at_<input_.size() && (input_[at_]=='.' || input_[at_]=='e' || input_[at_]=='E'))invalid();
    std::uint64_t magnitude=0;const auto parsed=std::from_chars(input_.data()+digits,input_.data()+at_,magnitude);
    if(parsed.ec!=std::errc{} || (negative && magnitude>std::uint64_t{1}<<63U))invalid();
    return {magnitude,negative};
  }
  std::uint64_t unsigned_integer() {
    const auto value=integer();if(value.negative && value.magnitude)invalid();return value.magnitude;
  }
  // Callbacks classify/copy each borrowed key before parsing another string.
  template<class Fn> void members(Fn member) {
    if(!accept('{'))invalid();
    if(accept('}'))return;
    for(;;) {const auto key=string();expect(':');member(key);if(accept('}'))return;expect(',');}
  }
  void position() {
    unsigned seen=0;resource::AccountedText source;std::uint64_t offset=0;
    members([&](std::string_view key) {
      const auto field=key=="source"?1U:key=="offset"?2U:0U;
      require(field!=0 && !(seen&field),"invalid_document","unknown or duplicate source-position field");seen|=field;
      if(field==2){offset=unsigned_integer();return;}
      const auto name=string();bounded(name.size(),limits_.source_bytes,"input source identifier exceeds its byte limit");
      require(!name.empty() && name.find('\0')==std::string_view::npos,"invalid_source_position","source identifier must be nonempty and contain no NUL");
      source=resource::AccountedText::copy_of(account_,name,memory_owner);
    });
    require(seen==3,"invalid_document","source_position requires source and offset");
    builder_.decoded.source=std::move(source);builder_.decoded.event.source_position=SourcePositionView{builder_.decoded.source.view(),offset};
  }
  void scalar() {
    space();if(at_==input_.size())syntax();
    bounded(builder_.cells.size()+1,limits_.columns,"physical input column limit exceeded");
    if(input_[at_]=='"') {
      const auto value=string();bounded(value.size(),limits_.field_bytes,"input string field exceeds its byte limit");builder_.text(value);return;
    }
    if(input_[at_]=='{') {
      bool seen=false;std::optional<storage::ScalarView> value;
      members([&](std::string_view key) {
        require(!seen && (key=="date" || key=="decimal"),"invalid_document","tagged input scalar needs exactly one date/decimal field");
        const bool date=key=="date";seen=true;const auto text=string();bounded(text.size(),limits_.field_bytes,"tagged input field exceeds its byte limit");
        if(date)value=Date::parse(text);else value=storage::InlineDecimal::parse(text);
      });
      require(value.has_value(),"invalid_document","empty tagged input scalar");builder_.value(*value);return;
    }
    if(input_.substr(at_,4)=="true"){at_+=4;builder_.value(true);return;}
    if(input_.substr(at_,5)=="false"){at_+=5;builder_.value(false);return;}
    const auto value=integer();
    if(!value.negative)require(value.magnitude<=static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max()),"invalid_document","input integer exceeds int64 range");
    const auto signed_value=value.negative?(value.magnitude==(std::uint64_t{1}<<63U)?std::numeric_limits<std::int64_t>::min():-static_cast<std::int64_t>(value.magnitude)):static_cast<std::int64_t>(value.magnitude);
    builder_.value(signed_value);
  }
  void values() {
    if(!accept('['))invalid();
    if(accept(']'))return;
    for(;;){scalar();if(accept(']'))return;expect(',');}
  }
 public:
  JsonReader(const resource::MemoryAccount& account,std::string_view text,const InputLimits& limits)
      :account_(account),input_(text),limits_(limits),token_(account),builder_(account) {}
  Decoded decode(const auto& catalog,std::string_view fingerprint) {
    bounded(input_.size(),limits_.record_bytes,"JSON input record exceeds its byte limit");
    if(input_.starts_with("\xef\xbb\xbf"))at_=3;
    members([&](std::string_view key) {
      constexpr std::array<std::string_view,9> names={"catalog_sha256","catalog_version","operation","schema_version","sequence","source_position","source_schema_version","table","values"};
      const auto found=std::find(names.begin(),names.end(),key);if(found==names.end())invalid();
      const auto field=static_cast<unsigned>(found-names.begin());require(!(seen_&(1U<<field)),"invalid_document","duplicate input JSON field");seen_|=1U<<field;
      switch(field) {
        case 0:{const auto text=string();require(text.size()==64,"catalog_mismatch","input catalog fingerprint must have 64 hexadecimal characters");hash_=resource::AccountedText::copy_of(account_,text,memory_owner);break;}
        case 1:catalog_version_=unsigned_integer();break;
        case 2:{const auto text=string();require(text=="insert" || text=="delete","unsupported_input_operation","physical input operation must be insert or delete");builder_.decoded.event.update.operation=text=="insert"?SetOperation::insert:SetOperation::erase;break;}
        case 3:version_=unsigned_integer();break;
        case 4:builder_.decoded.event.update.sequence=unsigned_integer();break;
        case 5:position();break;
        case 6:source_version_=unsigned_integer();break;
        case 7:{const auto text=string();bounded(text.size(),limits_.field_bytes,"physical table name exceeds its byte limit");table_=resource::AccountedText::copy_of(account_,text,memory_owner);break;}
        case 8:values();break;
        default:std::terminate();
      }
    });
    constexpr auto required=((1U<<9U)-1U)&~(1U<<5U);
    require((seen_&required)==required,"invalid_document","physical input JSON is missing required fields");space();if(at_!=input_.size())syntax();
    require(version_==1,"unsupported_version","unsupported physical input schema version");builder_.decoded.event.update.table=native_table(catalog,table_.view());
    binding(catalog_version_,source_version_,hash_.view(),builder_.decoded.event.update.table,catalog,fingerprint);
    return builder_.finish(catalog,limits_);
  }
};
struct BinaryReader {
  std::string_view input;
  std::size_t position=0;
  std::string_view take(std::size_t count) {
    require(count<=input.size()-position,"invalid_document","truncated binary input record");const auto result=input.substr(position,count);position+=count;return result;
  }
  std::uint64_t integer(std::size_t bytes) {
    const auto value=take(bytes);std::uint64_t result=0;
    for(std::size_t i=0;i<bytes;++i)result|=static_cast<std::uint64_t>(static_cast<unsigned char>(value[i]))<<(i*8U);
    return result;
  }
  std::string_view string(std::size_t limit) {
    const auto count=integer(4);require(count<=limit,"resource_limit","binary field exceeds its byte limit");
    const auto result=take(static_cast<std::size_t>(count));ingest_detail::require_utf8(result);return result;
  }
};
Decoded binary(const resource::MemoryAccount& account,std::string_view bytes,const auto& catalog,const InputLimits& limits,std::string_view fingerprint) {
  bounded(bytes.size(),limits.record_bytes,"binary input record exceeds its byte limit");BinaryReader input{bytes};
  require(input.take(8)=="CROWNUPD","invalid_document","invalid binary input magic");require(input.integer(2)==1,"unsupported_version","unsupported binary input schema version");
  const auto length=input.integer(4);require(length==bytes.size()-input.position,"invalid_document","binary frame length differs from the complete record");
  const auto version=input.integer(8),source_version=input.integer(8);const auto hash=input.take(64);const auto sequence=input.integer(8);
  const auto table=native_table(catalog,input.string(limits.field_bytes));binding(version,source_version,hash,table,catalog,fingerprint);
  const auto operation=input.integer(1);require(operation==1 || operation==2,"unsupported_input_operation","unknown binary input operation");
  Builder builder(account);builder.decoded.event.update={sequence,table,operation==1?SetOperation::insert:SetOperation::erase,{}};
  const auto positioned=input.integer(1);require(positioned<=1,"invalid_document","invalid binary source-position flag");
  if(positioned){const auto source=input.string(limits.source_bytes);const auto offset=input.integer(8);builder.source(source,offset);}
  const auto fields=input.integer(4);require(fields<=limits.columns,"resource_limit","binary input column limit exceeded");
  require(fields==catalog.tables[table.value].columns.size(),"invalid_update","binary row arity differs from physical schema");
  require(fields<=(bytes.size()-input.position)/2,"invalid_document","binary field count exceeds its remaining payload");builder.cells.reserve(static_cast<std::size_t>(fields));
  for(std::uint64_t i=0;i<fields;++i) {
    switch(input.integer(1)) {
      case 0:builder.value(std::bit_cast<std::int64_t>(input.integer(8)));break;
      case 1:builder.text(input.string(limits.field_bytes));break;
      case 2:{const auto value=input.integer(1);require(value<=1,"invalid_document","binary Boolean must be zero or one");builder.value(value!=0);break;}
      case 3:bounded(10,limits.field_bytes,"date field exceeds its byte limit");builder.value(Date::parse(input.take(10)));break;
      case 4:{const auto text=input.string(limits.field_bytes);const auto value=storage::InlineDecimal::parse(text);std::array<char,storage::InlineDecimal::text_capacity> encoded{};const auto size=value.render(encoded);require(std::string_view(encoded.data(),size)==text,"invalid_document","binary decimal text must be canonical");builder.value(value);break;}
      default:throw Error("invalid_document","unsupported binary scalar tag");
    }
  }
  require(input.position==bytes.size(),"invalid_document","binary input record has trailing bytes");return builder.finish(catalog,limits);
}
} // namespace
Decoded decode_json(const resource::MemoryAccount& account,std::string_view text,const CatalogSource& catalog,const InputLimits& limits,std::string_view fingerprint) {
  return catalog_source_detail::read(catalog,[&](const auto& schema){return JsonReader(account,text,limits).decode(schema,fingerprint);});
}
Decoded decode_binary(const resource::MemoryAccount& account,std::string_view text,const CatalogSource& catalog,const InputLimits& limits,std::string_view fingerprint) {
  return catalog_source_detail::read(catalog,[&](const auto& schema){return binary(account,text,schema,limits,fingerprint);});
}
} // namespace crown::io::input_detail
