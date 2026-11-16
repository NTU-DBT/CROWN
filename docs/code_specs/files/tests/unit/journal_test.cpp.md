# `tests/unit/journal_test.cpp` — block usage map

[Source](../../../../../tests/unit/journal_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c6d4ec4441f037ee7eff4c300b31b8c4df8f3b61c5260c6e6d26a341a8989139`. 303 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/unit/journal_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 14–14](../../../../../tests/unit/journal_test.cpp#L14) | Callable definition: template&lt;class T&gt; concept HasRvalueInputView=requires(const T&& value) | calls input_view · [reviewed contract](#b0002) |
| [B0003 · 15–18](../../../../../tests/unit/journal_test.cpp#L15) | declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!HasRvalueInputView&lt;jp::Decoded&gt;); · [reviewed contract](#b0003) |
| [B0004 · 19–19](../../../../../tests/unit/journal_test.cpp#L19) | Callable definition: void check(bool condition,const char* message) | calls std::runtime_error; guard void check(bool condition,const char* message){if(!condition)throw std::runtime_error(message);} · [reviewed contract](#b0004) |
| [B0005 · 20–20](../../../../../tests/unit/journal_test.cpp#L20) | Callable definition: std::string_view bytes(const jp::Encoded& value) | calls data, size; returns {value.bytes.data(),value.bytes.size()} · [reviewed contract](#b0005) |
| [B0006 · 21–24](../../../../../tests/unit/journal_test.cpp#L21) | Callable definition: template&lt;class Action&gt; void rejected(Action action) | calls deny, action, check; guard bool failed=false;{s04_alloc::Scope deny(0);try{action();}catch(const jp::Failure&){failed=true;}ch… · [reviewed contract](#b0006) |
| [B0007 · 25–28](../../../../../tests/unit/journal_test.cpp#L25) | Callable definition: void reseal(jp::Encoded& value) | calls sha256_fixed, bytes, substr, std::copy · [reviewed contract](#b0007) |
| [B0008 · 29–35](../../../../../tests/unit/journal_test.cpp#L29) | Callable definition: jp::Header header() | calls std::copy, begin, end, fill; returns result · [reviewed contract](#b0008) |
| [B0009 · 36–42](../../../../../tests/unit/journal_test.cpp#L36) | Callable definition: void golden(const std::string& directory,const char* name,const jp::Encoded& encoded) | calls file, check, size; guard std::ifstream file(directory+"/"+name+".hex");std::string text;file&gt;&gt;text;check(text.size()==2*enco…; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 43–116](../../../../../tests/unit/journal_test.cpp#L43) | Callable definition: jp::Encoded roundtrip(const std::string& directory,const char* name,std::uint64_t ordinal,const jp::PayloadView& payload, const r… | calls statistics, jp::encode, check, golden; guard check(captures==account.statistics().successful_allocations-before.successful_allocations,"journal …; returns item.source_position; std::move(*image); 4 loop sites · [reviewed contract](#b0010) |
| [B0011 · 117–136](../../../../../tests/unit/journal_test.cpp#L117) | Callable definition: void invalid_frames(const resource::MemoryAccount& account,const jp::Encoded& input) | calls reseal, rejected, jp::inspect, bytes; 2 loop sites; source comment (unverified): // Independently derived offsets in the rich physical-input fixture. · [reviewed contract](#b0011) |
| [B0012 · 137–168](../../../../../tests/unit/journal_test.cpp#L137) | Callable definition: void metadata_prefix_cases(const resource::MemoryAccount& account,const std::string& directory) | calls header, jp::encode, jp::inspect, bytes; guard check(state.records==step+1 && state.consumed==ends\[step\] && state.physical_sequence==(step==3?3U:2…; 7 loop sites · [reviewed contract](#b0012) |
| [B0013 · 169–241](../../../../../tests/unit/journal_test.cpp#L169) | Callable definition: void prefix_cases(const resource::MemoryAccount& account) | calls header, jp::encode, jp::inspect, bytes; guard check(result.physical_sequence==physical\[completed\] && result.command_sequence==commands\[completed\]…; 5 loop sites; source comment (unverified): // A corrupted length in a complete final commit must never silently erase · [reviewed contract](#b0013) |
| [B0014 · 242–254](../../../../../tests/unit/journal_test.cpp#L242) | Callable definition: void failure_contract(const resource::MemoryAccount& account) | calls jp::encode, header, deny, jp::inspect; guard check(s04_alloc::calls==0,"journal failure diagnostic allocated");} · [reviewed contract](#b0014) |
| [B0015 · 255–273](../../../../../tests/unit/journal_test.cpp#L255) | Callable definition: void source_work_admission(const resource::MemoryAccount& account) | calls name, back, storage::TupleValuesView::borrow, size; guard check(failed,"journal encoder traversed source text before work admission");; growth insert; source comment (unverified): // Source text is followed only by offset u64 and the absent-reader byte. · [reviewed contract](#b0015) |
| [B0016 · 274–274](../../../../../tests/unit/journal_test.cpp#L274) | Closes surrounding scope/type. |  · [reviewed contract](#b0016) |
| [B0017 · 275–303](../../../../../tests/unit/journal_test.cpp#L275) | Callable definition: int main(int argc,char** argv) | calls check, resource::MemoryAccount::create, roundtrip, header; guard check(argc==2,"fixture directory required");const std::string directory=argv\[1\];const auto account=…; returns 1; growth insert · [reviewed contract](#b0017) |

## B0001

[Lines 1–13](../../../../../tests/unit/journal_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:8f10c50f2560ec8bb568564cc3ba9c15f5597b048d000f84d300248771a1a257
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare journal_test.cpp: include "crown/recovery/journal.hpp", "crown/ir/digest.hpp", "index_allocation.hpp", &lt;algorithm&gt;, &lt;fstream&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–14](../../../../../tests/unit/journal_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> concept HasRvalueInputView=requires(const T&& value){std::move(value).input_view();};

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile-time guard that forbids making a borrowed InputView from a temporary Decoded owner. |
| inputs / outputs | Concept tests the const-rvalue expression std::move(value).input_view(); static_assert requires it to be unavailable for jp::Decoded. |
| invariants | The lvalue adapter is owner-bound, and the rvalue overload is deleted so a borrowed view cannot escape a dying owner. |
| ownership | Compile-time only; no runtime object or view is produced. |
| failure | An API that permits the expression fails compilation. |
| cost | One requires-expression and static assertion; no runtime allocation. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md](../../../../journal.md) |

## B0003

[Lines 15–18](../../../../../tests/unit/journal_test.cpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L18:sha256:f8d08d0c454453b3653ac4cc4c59466778caa7b254ef3a4fe3f8215b84bc64bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare journal_test.cpp: require 3 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 19–19](../../../../../tests/unit/journal_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition,const char* message){if(!condition)throw std::runtime_error(message);}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fixed C-string assertion helper for journal checks. |
| inputs / outputs | Accepts a condition and borrowed C string; returns on true, otherwise throws std::runtime_error(message). |
| invariants | The helper performs no account or codec work. The C-string expression is already supplied by the caller. |
| ownership | Borrows message only for the call; a thrown exception owns its diagnostic representation. |
| failure | False throws std::runtime_error; exception construction can itself fail. No exception is caught. |
| cost | One branch on condition. The helper has no success-path string or container construction; failure may allocate the exception message. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp) |

## B0005

[Lines 20–20](../../../../../tests/unit/journal_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view bytes(const jp::Encoded& value){return {value.bytes.data(),value.bytes.size()};}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an encoded frame as a string_view. |
| inputs / outputs | Returns a string_view spanning value.bytes.data() through value.bytes.size() for one Encoded frame. |
| invariants | The returned view covers exactly the encoded vector contents and does not append a terminator or copy bytes. |
| ownership | Borrows the Encoded vector; the view becomes invalid when that storage is destroyed or reallocated. |
| failure | No validation or exception handling is added here; any lifetime misuse is a caller error. |
| cost | Constructs a pointer/length view in constant operations; no byte traversal or owned buffer is created. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp) |

## B0006

[Lines 21–24](../../../../../tests/unit/journal_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void rejected(Action action) {
  bool failed=false;{s04_alloc::Scope deny(0);try{action();}catch(const jp::Failure&){failed=true;}check(s04_alloc::calls==0,"journal rejection allocated");}
  check(failed,"journal accepted malformed input");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a malformed-input action to throw journal Failure without covered C++ new calls. |
| inputs / outputs | Takes Action by value; invokes under s04_alloc::Scope(0), catches only jp::Failure, then checks zero hook calls. |
| invariants | Other exception types escape; the wrapper accepts only the journal rejection category. |
| ownership | Action closure is copied or moved; captures remain borrowed. |
| failure | Missing jp::Failure fails the check; bad_alloc or unrelated failures propagate. |
| cost | One action invocation. Zero counted C++ new attempts says nothing about libc calls, CPU, or account bytes. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal.md](../../../../journal.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0007

[Lines 25–28](../../../../../tests/unit/journal_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reseal(jp::Encoded& value) {
  const auto hash=sha256_fixed(bytes(value).substr(jp::frame_header_size));std::copy(hash.begin(),hash.end(),value.bytes.begin()+20);
  const auto prefix=sha256_fixed(bytes(value).substr(0,jp::frame_prefix_size));std::copy(prefix.begin(),prefix.end(),value.bytes.begin()+jp::frame_prefix_size);
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reseal a mutated test frame by recomputing body and prefix hashes. |
| inputs / outputs | Takes a mutable Encoded and rewrites the body digest at byte offset 20, then the frame-prefix digest at frame_prefix_size. |
| invariants | Hashes bytes after frame_header_size first, then hashes the prefix preceding frame_prefix_size after the body digest has been installed. |
| ownership | Mutates the supplied Encoded in place; temporary digest arrays are fixed-size values. |
| failure | No journal Failure is caught or checked. Invalid offsets or malformed body structure are not repaired; this fixture helper assumes its frame shape. |
| cost | Two fixed-digest passes over frame bytes plus two fixed-size copies. Test-fixture hashing work is proportional to frame length; it is not a codec cost measurement. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal.md](../../../../journal.md) |

## B0008

[Lines 29–35](../../../../../tests/unit/journal_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
jp::Header header() {
  jp::Header result;constexpr std::string_view id="0123456789abcdef0123456789abcdef";
  std::copy(id.begin(),id.end(),result.query_id.begin());result.binding.physical_sha256.fill('a');result.binding.source_sha256.fill('b');
  result.binding.catalog_version=7;result.checkpoint_sha256.fill('c');result.input_kind=jp::InputKind::stream;
  result.binding.policy={1,1000000,UINT64_MAX,0,0,2,256,1,0,1,0,1,1000000,UINT64_MAX,1,1,0,0,1,1000000,1,1000000,1,1000000,65536,67108864};
  return result;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the deterministic valid stream header used by fixtures. |
| inputs / outputs | Returns a Header value with fixed query ID, binding digests/version, stream kind, and literal policy limits. |
| invariants | All fields are initialized deterministically; query ID is copied from a 32-character literal and digest arrays are filled with fixed letters. |
| ownership | Returns a value object; no runtime, account, or input view is retained. |
| failure | No failure path is asserted for these fixed scalar/array assignments. |
| cost | Fixed-size field and array assignments with no row loop or account operation; later encoding is separate work. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md](../../../../journal.md) |

## B0009

[Lines 36–42](../../../../../tests/unit/journal_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void golden(const std::string& directory,const char* name,const jp::Encoded& encoded) {
  std::ifstream file(directory+"/"+name+".hex");std::string text;file>>text;check(text.size()==2*encoded.bytes.size(),"independent journal fixture length differs");
  constexpr std::string_view hex="0123456789abcdef";
  for(std::size_t i=0;i<encoded.bytes.size();++i) {
    const auto value=static_cast<unsigned char>(encoded.bytes[i]);check(text[2*i]==hex[value>>4] && text[2*i+1]==hex[value&15],"independent journal fixture bytes differ");
  }
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare encoded bytes with an independent lowercase hexadecimal fixture. |
| inputs / outputs | Builds directory/name.hex, reads one whitespace-delimited hex token, and compares it with encoded.bytes as lowercase byte pairs. |
| invariants | The token must have exactly twice the encoded byte count; each high/low nibble is compared against the fixed lowercase alphabet. |
| ownership | Borrows directory, name, and Encoded for the call; ifstream and token string are local owners. |
| failure | check throws std::runtime_error on length or byte mismatch; file-open/extraction failure is detected through the empty or wrong-sized token. I/O exceptions are not translated here. |
| cost | Reads one fixture token and checks every encoded byte once. Path concatenation and token storage may allocate; this is independent golden-file test work, not codec allocation evidence. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md](../../../../journal.md) |

## B0010

[Lines 43–116](../../../../../tests/unit/journal_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise encode, inspect, decode, input-view adaptation, quota boundaries, and fault positions for one payload. |
| inputs / outputs | Borrows PayloadView, optional expected Row, directory and account; returns owning Encoded. |
| invariants | Checks kind/ordinal/payload bindings, golden bytes, InputView adaptation only while Decoded lives, every truncation and bit flip, exact/one-under codec limits, and receiving-account requested-byte boundary. |
| ownership | Encoded/Decoded buffers are account-owned. Adapted InputView borrows Decoded. Source/CSV/frame views borrow their backing objects. |
| failure | Expects jp::Failure for malformed/under-limit cases, bad_alloc at every observed encode/decode hook index, and MemoryFailure::limit at one-under account cap. |
| cost | Encode/inspect/decode plus repeated inspect; sweeps each observed allocation call; checks every truncation and bit-flip copy. The explicit std::move of the Encoded held in the optional extracts that value; it is not a no-copy or allocator-cost proof. Account bytes and C++ new calls are distinct; loops revisit whole frames and imply no CPU/RSS bound. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal.md](../../../../journal.md), [docs/decisions/0013-support-journals.md](../../../../decisions/0013-support-journals.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0011

[Lines 117–136](../../../../../tests/unit/journal_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject resealed malformed tags, scalar fields, permutations, policies, and commit contexts. |
| inputs / outputs | Copies the rich physical-input frame, corrupts selected source/reader fields, reseals checksums, then calls inspect; it also encodes invalid headers/commits and scans a forbidden metadata stream. |
| invariants | The listed offsets target UTF-8 tags, scalar values, reader positions/CSV mapping, header generation/policy/sequences, and commit kind/context; resealing keeps checksum validity from masking semantic validation. |
| ownership | Borrows account and input frame; each malformed Encoded and assembled stream is a local fixture owner. No Decoded view escapes. |
| failure | Each negative action is required by rejected() to throw jp::Failure with zero counted C++ new calls in the action scope. Fixture construction/check failures propagate as test exceptions. |
| cost | Per-position copies, hash reseals, and inspect/encode/scan calls revisit whole frames; stream concatenation can allocate before the deny scope. The test fixes a finite list of malformed offsets and does not measure CPU or general malformed-input cost. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal.md](../../../../journal.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0012

[Lines 137–168](../../../../../tests/unit/journal_test.cpp#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check every byte cut of a partial window watermark metadata sequence and its cursor parity. |
| inputs / outputs | Builds header, watermark input, partial metadata marker and completion; scans all cuts, feeds a Cursor, and tests counter/substep/record quota variants. |
| invariants | Pending input identity/substep and physical/command boundaries match the four-record fixture; whole scan and cursor agree. |
| ownership | Log owns frame bytes. PendingView borrows log; Cursor owns continuation but retains a borrowed pending-frame view. |
| failure | Malformed markers and one-under bytes/work/record limits reject with jp::Failure. |
| cost | One scan per byte cut repeatedly revalidates prefixes; Cursor feeds complete records. Abstract byte-work and C++ new checks do not measure CPU/RSS. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal.md](../../../../journal.md), [docs/storage_journal.md](../../../../storage_journal.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0013

[Lines 169–241](../../../../../tests/unit/journal_test.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check every byte cut and incremental continuation of a six-record window prefix, including failure state and moves. |
| inputs / outputs | Builds six records; checks every cut, whole scan, six incremental feeds, malformed feeds, tail replacement, quota tampering, cursor move and one-under limits. |
| invariants | Failed feed leaves prior stored state/work intact; returned snapshots cannot mint quota. Pending bytes borrow the log. |
| ownership | Cursor is move-only and owns private continuation; pending frame view borrows log. Moved-from cursor is rejected. |
| failure | Malformed/under-quota cases expect jp::Failure; complete corrupt record length rejects instead of becoming torn tail. |
| cost | Every prefix cut triggers another full scan, plus separate six-record feeds. This finite repeated work does not bound production CPU or repair cost. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal.md](../../../../journal.md), [docs/storage_journal.md](../../../../storage_journal.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0014

[Lines 242–254](../../../../../tests/unit/journal_test.cpp#L242); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve fixed journal diagnostics and an account contract failure category. |
| inputs / outputs | Encodes a valid header, changes the version byte, and inspects it under the allocation hook; separately encodes with an absent MemoryAccount. |
| invariants | The version case must expose Fault::version and the fixed what() text; the missing-account case must preserve MemoryFault::contract. |
| ownership | The local Encoded owns account-backed bytes; the absent account is a non-owning empty handle. |
| failure | The malformed frame must throw jp::Failure without covered C++ new calls. The empty-account call must throw MemoryFailure::contract; neither category is converted into the other. |
| cost | One small encode and two isolated negative calls. The hook covers selected C++ new overloads only; no CPU or total allocator claim is made. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal.md](../../../../journal.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0015

[Lines 255–273](../../../../../tests/unit/journal_test.cpp#L255); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Show source-name work is admitted before UTF-8 traversal in selected encode and inspect paths. |
| inputs / outputs | Creates a 4096-byte source name with invalid final UTF-8, encodes under source_bytes=4096/work=512, then encodes valid text, corrupts its last source byte, reseals, and inspects with a derived exact work limit. |
| invariants | The first case expects work rejection before UTF-8 traversal. The second grants prefix/body hash work plus body bytes through source text but leaves no work for the later UTF-8 validation visit. |
| ownership | The source name and payload borrow caller-local string/row storage; Encoded owns its bytes in the supplied MemoryAccount. |
| failure | Both selected actions must throw jp::Failure::work while Scope(0) observes no counted C++ new calls. This does not enumerate all source lengths or all validation paths. |
| cost | One 4096-byte source setup, one early-rejected encode, then one encode/reseal and inspect over the complete frame with a calculated finite work budget. Abstract journal work is not elapsed CPU. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [src/recovery/journal.cpp](../../../../../src/recovery/journal.cpp), [docs/journal.md](../../../../journal.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0016

[Lines 274–274](../../../../../tests/unit/journal_test.cpp#L274); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L274-L274:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in journal_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 275–303](../../../../../tests/unit/journal_test.cpp#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the seven payload roundtrips and focused negative, lifetime, prefix, and source-work cases. |
| inputs / outputs | Requires one fixture-directory argument, creates a 32 MiB account, runs seven payload roundtrips, then malformed-frame, decoded-owner, prefix, metadata, diagnostic, and source-work cases. |
| invariants | The seven roundtrips cover header, physical input/commit, checkpoint, and three window commands; the rich input uses a two-column permutation and input lifetime check. Failure exits through the std::exception catch. |
| ownership | Main owns directory string and account for the test run. Encoded/Decoded results and temporary views are scoped inside helpers; it prints only after the full sequence succeeds. |
| failure | Missing argv or any check/codec/resource exception reaches the outer std::exception handler and returns 1; success returns 0. This is test orchestration, not persistence/replay. |
| cost | Runs the finite fixture loops in roundtrip and prefix helpers, including every byte cut and every encoded byte flip for each selected payload. No test execution or runtime cost claim is inferred from this source review. |
| Design | [tests/unit/journal_test.cpp](../../../../../tests/unit/journal_test.cpp), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp), [docs/journal.md](../../../../journal.md), [docs/decisions/0013-support-journals.md](../../../../decisions/0013-support-journals.md) |
