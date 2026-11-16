#include "crown/recovery/journal.hpp"
#include "crown/ir/digest.hpp"
#include "index_allocation.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

using namespace crown;
using namespace crown::recovery;
namespace jp=crown::recovery::journal;
template<class T> concept HasRvalueInputView=requires(const T&& value){std::move(value).input_view();};
static_assert(!HasRvalueInputView<jp::Decoded>);
static_assert(!std::is_copy_constructible_v<jp::Cursor> && !std::is_copy_assignable_v<jp::Cursor>);
static_assert(!std::is_constructible_v<jp::Cursor,jp::Scanned>);
namespace {
void check(bool condition,const char* message){if(!condition)throw std::runtime_error(message);}
std::string_view bytes(const jp::Encoded& value){return {value.bytes.data(),value.bytes.size()};}
template<class Action> void rejected(Action action) {
  bool failed=false;{s04_alloc::Scope deny(0);try{action();}catch(const jp::Failure&){failed=true;}check(s04_alloc::calls==0,"journal rejection allocated");}
  check(failed,"journal accepted malformed input");
}
void reseal(jp::Encoded& value) {
  const auto hash=sha256_fixed(bytes(value).substr(jp::frame_header_size));std::copy(hash.begin(),hash.end(),value.bytes.begin()+20);
  const auto prefix=sha256_fixed(bytes(value).substr(0,jp::frame_prefix_size));std::copy(prefix.begin(),prefix.end(),value.bytes.begin()+jp::frame_prefix_size);
}
jp::Header header() {
  jp::Header result;constexpr std::string_view id="0123456789abcdef0123456789abcdef";
  std::copy(id.begin(),id.end(),result.query_id.begin());result.binding.physical_sha256.fill('a');result.binding.source_sha256.fill('b');
  result.binding.catalog_version=7;result.checkpoint_sha256.fill('c');result.input_kind=jp::InputKind::stream;
  result.binding.policy={1,1000000,UINT64_MAX,0,0,2,256,1,0,1,0,1,1000000,UINT64_MAX,1,1,0,0,1,1000000,1,1000000,1,1000000,65536,67108864};
  return result;
}
void golden(const std::string& directory,const char* name,const jp::Encoded& encoded) {
  std::ifstream file(directory+"/"+name+".hex");std::string text;file>>text;check(text.size()==2*encoded.bytes.size(),"independent journal fixture length differs");
  constexpr std::string_view hex="0123456789abcdef";
  for(std::size_t i=0;i<encoded.bytes.size();++i) {
    const auto value=static_cast<unsigned char>(encoded.bytes[i]);check(text[2*i]==hex[value>>4] && text[2*i+1]==hex[value&15],"independent journal fixture bytes differ");
  }
}
jp::Encoded roundtrip(const std::string& directory,const char* name,std::uint64_t ordinal,const jp::PayloadView& payload,
    const resource::MemoryAccount& account,const Row* expected=nullptr) {
  const auto before=account.statistics();std::optional<jp::Encoded> image;std::size_t captures=0,restores=0;
  {s04_alloc::Scope count;image=jp::encode(account,ordinal,payload);captures=s04_alloc::calls;}
  check(captures==account.statistics().successful_allocations-before.successful_allocations,"journal encoder escaped account");
  golden(directory,name,*image);const auto info=jp::inspect(bytes(*image));
  {s04_alloc::Scope deny(0);static_cast<void>(jp::inspect(bytes(*image)));check(s04_alloc::calls==0,"journal inspection allocated");}
  const auto pre=account.statistics();std::optional<jp::Decoded> decoded;
  {s04_alloc::Scope count;decoded=jp::decode(account,bytes(*image));restores=s04_alloc::calls;}
  check(restores==account.statistics().successful_allocations-pre.successful_allocations,"journal decoder escaped account");
  check(decoded->info.kind==static_cast<jp::Kind>(payload.index()) && decoded->info.ordinal==ordinal,"journal kind/ordinal lost");
  if(expected)check(decoded->row.view()==*expected,"journal native scalar row differs");
  if(const auto* value=std::get_if<jp::Header>(&payload))check(decoded->info.header==*value,"journal header binding differs");
  if(const auto* value=std::get_if<jp::Commit>(&payload))check(decoded->info.commit==*value,"journal commit binding differs");
  if(const auto* value=std::get_if<jp::Checkpoint>(&payload))check(decoded->info.checkpoint==*value,"journal checkpoint binding differs");
  if(const auto* value=std::get_if<jp::InputView>(&payload)) {
    std::optional<jp::InputView> adapted;
    {s04_alloc::Scope deny(0);adapted=decoded->input_view();check(s04_alloc::calls==0,"native journal input adapter allocated");}
    check(adapted->item.index()==value->item.index(),"native journal input adapter changed source kind");
    std::visit([&](const auto& original) {
      using T=std::remove_cvref_t<decltype(original)>;const auto& actual=std::get<T>(adapted->item);
      check(actual.source_position==original.source_position,"native journal adapter lost source position");
      if constexpr(std::is_same_v<T,io::InputEventView>)check(actual.update.sequence==original.update.sequence && actual.update.table==original.update.table &&
          actual.update.operation==original.update.operation && actual.update.values==original.update.values,"native journal physical view differs");
      else {
        check(actual.sequence==original.sequence && actual.command.index()==original.command.index(),"native journal window view differs");
        std::visit([&](const auto& expected) {
          using C=std::remove_cvref_t<decltype(expected)>;
          if constexpr(std::is_same_v<C,io::WindowInsertView>) {
            const auto& restored=std::get<C>(actual.command);check(restored.label==expected.label && restored.table==expected.table &&
                restored.timestamp==expected.timestamp && restored.values==expected.values,"native journal insertion view differs");
          }else if constexpr(std::is_same_v<C,io::WindowWithdraw>)check(std::get<C>(actual.command).label==expected.label,"native journal withdrawal view differs");
          else if constexpr(std::is_same_v<C,io::AdvanceWatermark>)check(std::get<C>(actual.command).watermark==expected.watermark,"native journal watermark view differs");
        },original.command);
      }
    },value->item);
    const auto source=std::visit([](const auto& item){return item.source_position;},value->item);
    check(decoded->info.input.source_present==source.has_value(),"journal optional source differs");
    if(source)check(decoded->source_name()==source->source && decoded->info.input.source_offset==source->offset,"journal source identity differs");
    if(value->reader)check(decoded->info.input.reader_records==value->reader->records && decoded->info.input.reader_bytes==value->reader->bytes &&
        decoded->info.input.header_read==value->reader->header_read && std::equal(decoded->csv_fields.begin(),decoded->csv_fields.end(),value->reader->csv_fields.begin(),value->reader->csv_fields.end()),"journal reader state differs");
  }
  else rejected([&]{static_cast<void>(decoded->input_view());});
  decoded.reset();const auto resident=account.statistics().current;
  for(std::size_t point=0;point<captures;++point) {
    bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{auto value=jp::encode(account,ordinal,payload);}catch(const std::bad_alloc&){failed=true;}}
    check(failed && account.statistics().current==resident,"journal encode fault leaked or accepted");
  }
  for(std::size_t point=0;point<restores;++point) {
    bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{auto value=jp::decode(account,bytes(*image));}catch(const std::bad_alloc&){failed=true;}}
    check(failed && account.statistics().current==resident,"journal decode fault leaked or accepted");
  }
  for(std::size_t size=0;size<image->bytes.size();++size)rejected([&]{static_cast<void>(jp::inspect(bytes(*image).substr(0,size)));});
  for(std::size_t position=0;position<image->bytes.size();++position) {
    auto changed=*image;changed.bytes[position]^=1;rejected([&]{static_cast<void>(jp::inspect(bytes(changed)));});
  }
  jp::Limits limits;limits.record.bytes=image->bytes.size();static_cast<void>(jp::inspect(bytes(*image),limits));
  --limits.record.bytes;rejected([&]{static_cast<void>(jp::inspect(bytes(*image),limits));});
  limits={};limits.record.work=info.statistics.work;static_cast<void>(jp::inspect(bytes(*image),limits));
  --limits.record.work;rejected([&]{static_cast<void>(jp::inspect(bytes(*image),limits));});
  limits={};limits.record.work=image->statistics.work;{auto exact=jp::encode(account,ordinal,payload,limits);check(exact.bytes==image->bytes,"exact encode work changed bytes");}
  --limits.record.work;rejected([&]{auto value=jp::encode(account,ordinal,payload,limits);});
  if(restores>0) {
    std::uint64_t peak=0;
    {auto receiving=resource::MemoryAccount::create(16*1024*1024);auto value=jp::decode(receiving,bytes(*image));peak=receiving.statistics().peak_requested_bytes;}
    {auto receiving=resource::MemoryAccount::create(peak);auto value=jp::decode(receiving,bytes(*image));check(receiving.statistics().peak_requested_bytes==peak,"exact journal receiving cap differs");}
    bool failed=false;
    try{auto receiving=resource::MemoryAccount::create(peak-1);auto value=jp::decode(receiving,bytes(*image));}
    catch(const resource::MemoryFailure& error){failed=error.fault()==resource::MemoryFault::limit;}
    check(failed,"one-under journal receiving cap accepted");
  }
  std::cout<<name<<" bytes="<<image->bytes.size()<<" capture/restore="<<captures<<'/'<<restores<<" golden/truncations/flips/faults/caps passed\n";
  return std::move(*image);
}
void invalid_frames(const resource::MemoryAccount& account,const jp::Encoded& input) {
  // Independently derived offsets in the rich physical-input fixture.
  for(const auto position:{84U,93U,110U,119U,141U,156U,165U,178U,195U}) {
    auto bad=input;bad.bytes[position+64]=static_cast<char>(0xff);reseal(bad);rejected([&]{static_cast<void>(jp::inspect(bytes(bad)));});
  }
  for(const auto position:{94U,187U}) {
    auto bad=input;std::fill_n(bad.bytes.begin()+position+64,8,'\0');reseal(bad);rejected([&]{static_cast<void>(jp::inspect(bytes(bad)));});
  }
  {auto bad=input;bad.bytes[212+64]=1;reseal(bad);rejected([&]{static_cast<void>(jp::inspect(bytes(bad)));});}
  {auto bad=input;std::fill_n(bad.bytes.begin()+157+64,8,static_cast<char>(0xff));reseal(bad);rejected([&]{static_cast<void>(jp::inspect(bytes(bad)));});}
  {auto invalid=header();invalid.generation=0;rejected([&]{auto value=jp::encode(account,0,jp::PayloadView{invalid});});}
  {auto invalid=header();invalid.binding.policy[0]=2;rejected([&]{auto value=jp::encode(account,0,jp::PayloadView{invalid});});}
  {auto invalid=header();invalid.physical_sequence=1;rejected([&]{auto value=jp::encode(account,0,jp::PayloadView{invalid});});}
  {jp::Commit invalid;invalid.input_ordinal=1;invalid.input_sha256=jp::inspect(bytes(input)).body_sha256;invalid.kind=jp::CommitKind::metadata;invalid.completes_input=false;
    auto first=jp::encode(account,0,jp::PayloadView{header()});auto mark=jp::encode(account,2,jp::PayloadView{invalid});
    std::string stream(bytes(first));stream.append(bytes(input));stream.append(bytes(mark));
    rejected([&]{static_cast<void>(jp::scan(stream));}); // Metadata is forbidden for a physical/stream source.
    invalid.kind=static_cast<jp::CommitKind>(2);rejected([&]{auto value=jp::encode(account,2,jp::PayloadView{invalid});});}
  std::cout<<"checksum-valid malformed tags/scalars/reader positions/CSV permutation/header policy rejected before allocation\n";
}
void metadata_prefix_cases(const resource::MemoryAccount& account,const std::string& directory) {
  auto base=header();base.input_kind=jp::InputKind::window;base.physical_sequence=2;base.command_sequence=5;
  auto first=jp::encode(account,0,jp::PayloadView{base});const io::WindowCommandView watermark{6,io::AdvanceWatermark{30},{}};
  auto input=jp::encode(account,1,jp::PayloadView{jp::InputView{watermark,{}}});
  jp::Commit partial;partial.input_ordinal=1;partial.input_sha256=jp::inspect(bytes(input)).body_sha256;partial.kind=jp::CommitKind::metadata;
  partial.physical_sequence=2;partial.command_sequence=5;partial.completes_input=false;auto middle=jp::encode(account,2,jp::PayloadView{partial});
  auto last=partial;last.kind=jp::CommitKind::physical;last.physical_sequence=3;last.command_sequence=6;last.substep=1;last.completes_input=true;
  auto final=jp::encode(account,3,jp::PayloadView{last});std::string log;std::array<std::size_t,4> ends{};std::size_t n=0;
  for(const auto* frame:{&first,&input,&middle,&final}){log.append(bytes(*frame));ends[n++]=log.size();}
  jp::Encoded combined{ImageVector<char>(image_allocator<char>(account)),{}};combined.bytes.assign(log.begin(),log.end());golden(directory,"window-partial-metadata-prefix",combined);
  for(std::size_t cut=0;cut<first.bytes.size();++cut)rejected([&]{static_cast<void>(jp::scan(std::string_view(log).substr(0,cut)));});
  for(std::size_t cut=first.bytes.size();cut<=log.size();++cut) {
    std::size_t step=0;while(step+1<ends.size() && ends[step+1]<=cut)++step;
    s04_alloc::Scope deny(0);const auto state=jp::scan(std::string_view(log).substr(0,cut));
    check(state.records==step+1 && state.consumed==ends[step] && state.physical_sequence==(step==3?3U:2U) && state.command_sequence==(step==3?6U:5U) &&
        state.torn_tail==(cut!=ends[step]) && state.pending.has_value()==(step==1 || step==2) && s04_alloc::calls==0,"metadata prefix boundary differs");
    if(state.pending)check(state.pending->next_substep==(step==2?1U:0U) && state.pending->frame==bytes(input),"metadata prefix lost pending input/substep");
  }
  const auto whole=jp::scan(log);jp::ScanLimits limits;limits.bytes=log.size();limits.work=whole.work;limits.records=4;
  jp::Cursor cursor(limits,&base);for(const auto* frame:{&first,&input,&middle,&final})static_cast<void>(cursor.feed(bytes(*frame)));
  check(cursor.state().work==whole.work && cursor.state().command_sequence==6,"metadata incremental parity differs");
  for(unsigned which=0;which<3;++which){auto low=limits;if(which==0)--low.bytes;else if(which==1)--low.work;else --low.records;rejected([&]{static_cast<void>(jp::scan(log,low));});}
  for(unsigned which=0;which<3;++which) {
    auto invalid=partial;if(which==0)++invalid.physical_sequence;else if(which==1)++invalid.command_sequence;else ++invalid.substep;
    auto mark=jp::encode(account,2,jp::PayloadView{invalid});std::string bad(bytes(first));bad.append(bytes(input));bad.append(bytes(mark));rejected([&]{static_cast<void>(jp::scan(bad));});
  }
  const Row empty;const io::WindowCommandView insertion{6,io::WindowInsertView{9,TableId{0},storage::TupleValuesView::borrow(empty),100},{}};
  auto nonwatermark=jp::encode(account,1,jp::PayloadView{jp::InputView{insertion,{}}});partial.input_sha256=jp::inspect(bytes(nonwatermark)).body_sha256;
  auto invalid=jp::encode(account,2,jp::PayloadView{partial});std::string bad(bytes(first));bad.append(bytes(nonwatermark));bad.append(bytes(invalid));
  rejected([&]{static_cast<void>(jp::scan(bad));});
  std::cout<<"independent partial-metadata prefix bytes="<<log.size()<<" every cut, exact quotas, incremental parity and strict window/counter context passed\n";
}
void prefix_cases(const resource::MemoryAccount& account) {
  auto base=header();base.input_kind=jp::InputKind::window;base.physical_sequence=2;base.command_sequence=5;
  auto first=jp::encode(account,0,jp::PayloadView{base});
  const io::WindowCommandView watermark{6,io::AdvanceWatermark{30},{}};
  auto input=jp::encode(account,1,jp::PayloadView{jp::InputView{watermark,{}}});
  jp::Commit step;step.input_ordinal=1;step.input_sha256=jp::inspect(bytes(input)).body_sha256;step.physical_sequence=3;step.command_sequence=5;step.completes_input=false;
  auto a=jp::encode(account,2,jp::PayloadView{step});step.physical_sequence=4;step.substep=1;auto b=jp::encode(account,3,jp::PayloadView{step});
  step.kind=jp::CommitKind::metadata;step.substep=2;step.command_sequence=6;step.completes_input=true;auto c=jp::encode(account,4,jp::PayloadView{step});
  jp::Checkpoint mark{4,6,{}};mark.checkpoint_sha256.fill('d');auto checkpoint=jp::encode(account,5,jp::PayloadView{mark});
  std::string log;std::array<std::size_t,6> ends{};std::size_t index=0;
  for(const auto* frame:{&first,&input,&a,&b,&c,&checkpoint}){log.append(bytes(*frame));ends[index++]=log.size();}
  const std::array<std::uint64_t,6> physical{2,2,3,4,4,4},commands{5,5,5,5,6,6};
  for(std::size_t cut=0;cut<ends[0];++cut)rejected([&]{static_cast<void>(jp::scan(std::string_view(log).substr(0,cut)));});
  for(std::size_t cut=ends[0];cut<=log.size();++cut) {
    std::size_t completed=0;while(completed+1<ends.size() && ends[completed+1]<=cut)++completed;
    s04_alloc::Scope deny(0);const auto result=jp::scan(std::string_view(log).substr(0,cut));
    check(result.physical_sequence==physical[completed] && result.command_sequence==commands[completed] && result.records==completed+1 &&
        result.consumed==ends[completed] && result.torn_tail==(cut!=ends[completed]) && s04_alloc::calls==0,"journal truncated-prefix boundary differs");
    check(result.pending.has_value()==(completed>=1 && completed<=3),"journal lost partial watermark input");
    if(result.pending)check(result.pending->ordinal==1 && result.pending->next_substep==completed-1 && result.pending->frame==bytes(input),"journal pending watermark replay identity differs");
  }
  const auto whole=jp::scan(log);jp::ScanLimits exact;exact.work=whole.work;exact.bytes=log.size();exact.records=6;
  {
    jp::Cursor validator(exact,&base);std::size_t previous=0;
    for(std::size_t k=0;k<ends.size();++k) {
      s04_alloc::Scope deny(0);const auto& cursor=validator.feed(std::string_view(log).substr(previous,ends[k]-previous));previous=ends[k];
      check(cursor.physical_sequence==physical[k] && cursor.command_sequence==commands[k] && cursor.records==k+1 && s04_alloc::calls==0,
          "incremental journal state differs or allocates");
    }
    const auto& cursor=validator.state();
    check(cursor.consumed==whole.consumed && cursor.work==whole.work && cursor.last_command_end==whole.last_command_end &&
        cursor.last_checkpoint_end==whole.last_checkpoint_end && !cursor.pending && !cursor.torn_tail,"incremental journal scan differs from whole prefix");
  }
  {
    jp::Cursor validator;static_cast<void>(validator.feed(bytes(first)));const auto before=validator.state();
    rejected([&]{static_cast<void>(validator.feed(bytes(a)));});
    rejected([&]{static_cast<void>(validator.feed(std::string_view(log).substr(ends[0])));});
    rejected([&]{static_cast<void>(validator.feed(bytes(input).substr(0,bytes(input).size()-1)));});
    check(before.records==1 && before.consumed==ends[0] && !before.pending && before.physical_sequence==2 && before.command_sequence==5,
        "failed incremental validation changed its prior state");
    check(validator.state().records==before.records && validator.state().work==before.work && !validator.state().pending,"failed cursor operation changed private continuation");
    static_cast<void>(validator.finish_tail(bytes(input).substr(0,12)));
    {s04_alloc::Scope deny(0);const auto& repaired=validator.feed(bytes(input));check(!repaired.torn_tail && repaired.pending && repaired.records==2,"complete replacement record retained torn flag");}
    jp::ScanLimits tight;tight.work=before.work;jp::Cursor restricted(tight,&base);static_cast<void>(restricted.feed(bytes(first)));
    auto forged=restricted.state();forged.work=0;forged.records=0;
    check(forged.work==0 && restricted.state().work==tight.work && restricted.state().records==1,"diagnostic snapshot changed cursor quota");
    rejected([&]{static_cast<void>(restricted.feed(bytes(input)));});
    check(restricted.state().records==1 && restricted.state().work==tight.work,"failed quota check reset cursor allowance");
    jp::Cursor moved(std::move(validator));
    rejected([&]{static_cast<void>(validator.feed(bytes(a)));});
    {s04_alloc::Scope deny(0);check(moved.feed(bytes(a)).physical_sequence==3 && s04_alloc::calls==0,"cursor move lost its continuation");}
  }
  {s04_alloc::Scope deny(0);static_cast<void>(jp::scan(log,exact,&base));check(s04_alloc::calls==0,"prefix inspection allocated");}
  {auto under=exact;--under.work;rejected([&]{static_cast<void>(jp::scan(log,under));});}
  {auto under=exact;--under.bytes;rejected([&]{static_cast<void>(jp::scan(log,under));});}
  {auto under=exact;--under.records;rejected([&]{static_cast<void>(jp::scan(log,under));});}
  {auto wrong=base;++wrong.generation;rejected([&]{static_cast<void>(jp::scan(log,{},&wrong));});}
  {auto bad=log;bad.back()^=1;rejected([&]{static_cast<void>(jp::scan(bad));});}
  {auto wrong=step;wrong.input_sha256[0]=wrong.input_sha256[0]=='0'?'1':'0';auto encoded=jp::encode(account,4,jp::PayloadView{wrong});
    const auto bad=log.substr(0,ends[3])+std::string(bytes(encoded));rejected([&]{static_cast<void>(jp::scan(bad));});}
  {auto wrong=step;wrong.substep=3;auto encoded=jp::encode(account,4,jp::PayloadView{wrong});
    const auto bad=log.substr(0,ends[3])+std::string(bytes(encoded));rejected([&]{static_cast<void>(jp::scan(bad));});}
  {const auto bad=std::string(bytes(first))+std::string(bytes(a));rejected([&]{static_cast<void>(jp::scan(bad));});}
  {
    // A corrupted length in a complete final commit must never silently erase
    // a committed command by looking like an interrupted append.
    auto bad=log.substr(0,ends[4]);const auto position=ends[3]+12;
    bad[position]=static_cast<char>(static_cast<unsigned char>(bad[position])+1);
    bool failed=false;{s04_alloc::Scope deny(0);try{static_cast<void>(jp::scan(bad));}catch(const jp::Failure&){failed=true;}}
    check(failed,"complete record length corruption was treated as a torn tail");
  }
  std::cout<<"all journal prefix cuts, incremental parity/rollback, partial watermark commits, sequencing/binding and exact global limits passed\n";
}
void failure_contract(const resource::MemoryAccount& account) {
  auto image=jp::encode(account,0,jp::PayloadView{header()});
  image.bytes[8]=2;
  bool translated=false;{s04_alloc::Scope deny(0);try{static_cast<void>(jp::inspect(bytes(image)));}
    catch(const jp::Failure& error){translated=error.fault()==jp::Fault::version && std::string_view(error.what())=="journal record rejected";}
    check(s04_alloc::calls==0,"journal failure diagnostic allocated");}
  check(translated,"journal version failure was not translated to its public fixed diagnostic");
  bool resource=false;
  {s04_alloc::Scope deny(0);try{const resource::MemoryAccount absent;auto value=jp::encode(absent,0,jp::PayloadView{header()});}
    catch(const resource::MemoryFailure& error){resource=error.fault()==resource::MemoryFault::contract;}}
  check(resource,"journal codec hid or bypassed a real account contract failure");
  std::cout<<"fixed journal diagnostics and unchanged resource failure categories passed\n";
}
void source_work_admission(const resource::MemoryAccount& account) {
  std::string name(4096,'a');name.back()=static_cast<char>(0xff);const Row row;
  const io::InputEventView event{{1,TableId{0},SetOperation::insert,storage::TupleValuesView::borrow(row)},io::SourcePositionView{name,0}};
  const jp::PayloadView payload{jp::InputView{event,{}}};jp::Limits limits;limits.source_bytes=name.size();limits.record.work=512;
  bool failed=false;
  {s04_alloc::Scope deny(0);try{auto value=jp::encode(account,1,payload,limits);}
    catch(const jp::Failure& error){failed=error.fault()==jp::Fault::work;}}
  check(failed,"journal encoder traversed source text before work admission");
  name.back()='a';limits.record.work=64*1024*1024;auto image=jp::encode(account,1,payload,limits);
  // Source text is followed only by offset u64 and the absent-reader byte.
  image.bytes[image.bytes.size()-10]=static_cast<char>(0xff);reseal(image);
  // Prefix read/hash, body hash, then body bytes through the source text.
  // No work remains for its separate UTF8-validation visit.
  limits.record.work=jp::frame_header_size+jp::frame_prefix_size+2*(image.bytes.size()-jp::frame_header_size)-9;failed=false;
  {s04_alloc::Scope deny(0);try{static_cast<void>(jp::inspect(bytes(image),limits));}
    catch(const jp::Failure& error){failed=error.fault()==jp::Fault::work;}}
  check(failed,"journal decoder traversed source text before work admission");
  std::cout<<"source-name work admitted before encode/decode UTF8 traversal passed\n";
}
}
int main(int argc,char** argv) {
  try {
    check(argc==2,"fixture directory required");const std::string directory=argv[1];const auto account=resource::MemoryAccount::create(32*1024*1024);
    auto h=roundtrip(directory,"header",0,jp::PayloadView{header()},account);
    const Row rich{INT64_MIN,std::string("A\0\xff",3),true,Date::parse("1970-01-01"),Decimal::parse("-123.45")};
    const std::array<std::uint64_t,2> permutation{1,0};
    const io::InputEventView physical{{1,TableId{0},SetOperation::insert,storage::TupleValuesView::borrow(rich)},io::SourcePositionView{"alpha",0}};
    const jp::InputView input{physical,jp::ReaderAdvanceView{123,1,true,permutation}};
    auto p=roundtrip(directory,"physical-input",1,jp::PayloadView{input},account,&rich);
    jp::Commit commit;commit.input_ordinal=1;commit.input_sha256=jp::inspect(bytes(p)).body_sha256;commit.physical_sequence=1;commit.command_sequence=1;
    auto c=roundtrip(directory,"physical-commit",2,jp::PayloadView{commit},account);
    jp::Checkpoint checkpoint{1,1,{}};checkpoint.checkpoint_sha256.fill('d');auto cp=roundtrip(directory,"checkpoint",3,jp::PayloadView{checkpoint},account);
    const Row empty;
    const io::WindowCommandView insertion{2,io::WindowInsertView{9,TableId{0},storage::TupleValuesView::borrow(empty),100},{}};
    auto i=roundtrip(directory,"window-insert-input",4,jp::PayloadView{jp::InputView{insertion,{}}},account,&empty);
    const io::WindowCommandView withdrawal{3,io::WindowWithdraw{9},{}};auto w=roundtrip(directory,"window-withdraw-input",5,jp::PayloadView{jp::InputView{withdrawal,{}}},account);
    const io::WindowCommandView watermark{4,io::AdvanceWatermark{120},{}};auto m=roundtrip(directory,"window-watermark-input",6,jp::PayloadView{jp::InputView{watermark,{}}},account);
    invalid_frames(account,p);
    std::optional<jp::Decoded> owning;
    {auto encoded=jp::encode(account,1,jp::PayloadView{input});owning=jp::decode(account,bytes(encoded));}
    check(owning->row.view()==rich && owning->source_name()=="alpha" && owning->csv_fields.size()==2,"journal decoded values borrowed destroyed bytes");
    {s04_alloc::Scope deny(0);owning.reset();}
    prefix_cases(account);
    metadata_prefix_cases(account,directory);
    failure_contract(account);
    source_work_admission(account);
    std::cout<<"Maintained journal codec/prefix corpus passed; persistence/replay integration pending\n";
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
