# `tests/unit/checkpoint_image_test.cpp` — block usage map

[Source](../../../../../tests/unit/checkpoint_image_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `e8f517286bb11ab00f21633ee90592b7b4a1bb15f7bee657270466d83b1c4ea7`. 145 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/unit/checkpoint_image_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../tests/unit/checkpoint_image_test.cpp#L13) | Callable definition: void check(bool value,const char* message) | calls std::runtime_error; guard void check(bool value,const char* message) {if(!value)throw std::runtime_error(message);} · [reviewed contract](#b0002) |
| [B0003 · 14–14](../../../../../tests/unit/checkpoint_image_test.cpp#L14) | Callable definition: std::string_view view(const EncodedImage& image) | calls data, size; returns {image.bytes.data(),image.bytes.size()} · [reviewed contract](#b0003) |
| [B0004 · 15–18](../../../../../tests/unit/checkpoint_image_test.cpp#L15) | Callable definition: template&lt;class Action&gt; void rejected(Action action,ImageFault fault) | calls action, check, fault, std::runtime_error; guard try{action();}catch(const ImageFailure& error){check(error.fault()==fault,"wrong image rejection");… · [reviewed contract](#b0004) |
| [B0005 · 19–23](../../../../../tests/unit/checkpoint_image_test.cpp#L19) | Callable definition: void reseal(EncodedImage& image) | calls size, sha256_fixed, view, substr; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 24–27](../../../../../tests/unit/checkpoint_image_test.cpp#L24) | Callable definition: void verify(const DecodedImage& image,const ImageManifest& manifest,const std::vector&lt;Row&gt;& expected) | calls check, size, empty, values; guard check(image.manifest==manifest && image.tables.size()==2 && image.tables\[0\].size()==2 && image.tabl…; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 28–31](../../../../../tests/unit/checkpoint_image_test.cpp#L28) | Callable definition: unsigned hex(char value) | calls check; guard check(value&gt;='a' && value&lt;='f',"invalid independent golden hex");return static_cast&lt;unsigned&gt;(value…; returns static_cast&lt;unsigned&gt;(value-@ ); static_cast&lt;unsigned&gt;(value-@ +10) · [reviewed contract](#b0007) |
| [B0008 · 32–32](../../../../../tests/unit/checkpoint_image_test.cpp#L32) | Closes surrounding scope/type. |  · [reviewed contract](#b0008) |
| [B0009 · 33–145](../../../../../tests/unit/checkpoint_image_test.cpp#L33) | Callable definition: int main(int argc,char** argv) | calls check, fill, size, min; guard check(argc==2,"golden fixture path missing");; returns 1; growth copy_of, push_back; 12 loop sites; source comment (unverified): // Checksum-valid malformed payloads must also fail before allocating. · [reviewed contract](#b0009) |

## B0001

[Lines 1–12](../../../../../tests/unit/checkpoint_image_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:4cf2a6a27cf279ffe80485932ff86ce151640bed4a2a1a709f6d47bda38d4399
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare checkpoint_image_test.cpp: include "crown/recovery/image.hpp", "crown/ir/digest.hpp", "index_allocation.hpp", &lt;fstream&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;tuple&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/checkpoint_image_test.cpp](../../../../../tests/unit/checkpoint_image_test.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–13](../../../../../tests/unit/checkpoint_image_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed local predicate into one readable test failure. |
| inputs / outputs | Receives a boolean and a borrowed diagnostic; returns on true, otherwise throws std::runtime_error. |
| invariants | The helper checks the assertion predicate only; it does not normalize CROWN recovery or memory errors. |
| ownership | The message remains owned by the caller; the exception owns its copied diagnostic after construction. |
| failure | False is the only intentional branch that raises the supplied diagnostic. |
| cost | One predicate branch; exception/string construction allocates only on failure. |
| Design | [tests/unit/checkpoint_image_test.cpp](../../../../../tests/unit/checkpoint_image_test.cpp), [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [tests/recovery/runtime-image-v1.hex](../../../../../tests/recovery/runtime-image-v1.hex), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0003

[Lines 14–14](../../../../../tests/unit/checkpoint_image_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view view(const EncodedImage& image)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the encoded image payload as a non-owning byte view for hashing and decoding. |
| inputs / outputs | Maps EncodedImage.bytes data and length to std::string_view; no bytes are returned by value. |
| invariants | The view is valid only while the same image storage remains alive and unmodified. |
| ownership | EncodedImage retains the vector; the caller borrows it for this synchronous test operation. |
| failure | An empty/moved-from image may provide an empty view; later codec validation determines rejection. |
| cost | Constant-time descriptor construction; no payload copy or native account allocation. |
| Design | [tests/unit/checkpoint_image_test.cpp](../../../../../tests/unit/checkpoint_image_test.cpp), [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [tests/recovery/runtime-image-v1.hex](../../../../../tests/recovery/runtime-image-v1.hex), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0004

[Lines 15–18](../../../../../tests/unit/checkpoint_image_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void rejected(Action action,ImageFault fault)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that a decoder call rejects with one specified ImageFault. |
| inputs / outputs | Invokes a supplied action and expected fault; accepts ImageFailure only when its fault matches. |
| invariants | Only the designated codec error is accepted; another fault or normal return fails the test. |
| ownership | The action captures its fixture by reference for the call; no decoded state is retained. |
| failure | Wrong-fault ImageFailure, unrelated exceptions, and acceptance all fail the assertion. |
| cost | One action invocation plus exception-path checks; action cost is supplied by each bounded test case. |
| Design | [tests/unit/checkpoint_image_test.cpp](../../../../../tests/unit/checkpoint_image_test.cpp), [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [tests/recovery/runtime-image-v1.hex](../../../../../tests/recovery/runtime-image-v1.hex), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0005

[Lines 19–23](../../../../../tests/unit/checkpoint_image_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reseal(EncodedImage& image)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute the CROWNRI1 payload length and checksum after deliberate payload mutation. |
| inputs / outputs | Mutates the image header length and digest from the current byte vector after edits to bytes beyond the header. |
| invariants | It reseals only the outer length and payload SHA256; it does not repair semantic fields or binding metadata. |
| ownership | The caller continues to own the same EncodedImage vector; the hash uses a borrowed view of it. |
| failure | An image shorter than the fixed header would underflow the test helper's size calculation; fixtures always start from a valid encoder result. |
| cost | One fixed 8-byte header rewrite and one linear payload hash; no new image buffer or receiving query allocation. |
| Design | [tests/unit/checkpoint_image_test.cpp](../../../../../tests/unit/checkpoint_image_test.cpp), [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [tests/recovery/runtime-image-v1.hex](../../../../../tests/recovery/runtime-image-v1.hex), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0006

[Lines 24–27](../../../../../tests/unit/checkpoint_image_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(const DecodedImage& image,const ImageManifest& manifest,const std::vector<Row>& expected)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a decoded image's manifest, table shape, and selected scalar rows against the independent expected values. |
| inputs / outputs | Takes decoded state, expected manifest, and ordinary expected Rows by const reference; returns only if both tables and expected row values agree. |
| invariants | The fixture requires two tables, two rows in table 0, an empty table 1, and exact scalar equality in insertion order. |
| ownership | Decoded rows remain owned by the decoder result/account; expected Rows are ordinary caller-owned test values. |
| failure | Any manifest, shape, or scalar mismatch throws the test diagnostic. |
| cost | Scans the small fixed fixture and compares scalars; expected rows are not counted as native query allocations. |
| Design | [tests/unit/checkpoint_image_test.cpp](../../../../../tests/unit/checkpoint_image_test.cpp), [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [tests/recovery/runtime-image-v1.hex](../../../../../tests/recovery/runtime-image-v1.hex), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0007

[Lines 28–31](../../../../../tests/unit/checkpoint_image_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
unsigned hex(char value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse one lowercase hexadecimal nibble from the independent golden image file. |
| inputs / outputs | Accepts a character; returns its numeric value for 0-9 or a-f. |
| invariants | Uppercase and non-hex characters are intentionally rejected by the test's own check helper. |
| ownership | No state is retained; the input character is copied by value. |
| failure | Invalid golden-file text fails the test rather than being silently normalized. |
| cost | Constant-time branch/arithmetic per nibble; the caller's golden string copy and stream storage use ordinary test memory. |
| Design | [tests/unit/checkpoint_image_test.cpp](../../../../../tests/unit/checkpoint_image_test.cpp), [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [tests/recovery/runtime-image-v1.hex](../../../../../tests/recovery/runtime-image-v1.hex), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0008

[Lines 32–32](../../../../../tests/unit/checkpoint_image_test.cpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L32:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in checkpoint_image_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/checkpoint_image_test.cpp](../../../../../tests/unit/checkpoint_image_test.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 33–145](../../../../../tests/unit/checkpoint_image_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise CROWNRI1 encoding, decoding, malformed-input preflight, fault rollback, and held-image lifetime. |
| inputs / outputs | Requires a path to the independent Python golden hex fixture; builds a fixed binding and rows, then runs encode/decode and mutation/cap probes. |
| invariants | The assertions cover exact golden bytes, binary NUL/0xff and extrema, checksum-valid malformed values, all truncations/one-bit flips before allocation, exact/under limits, and source-account release; they do not establish a CPU-time/RSS bound or runtime schema rebuild semantics. |
| ownership | The original MemoryAccount owns native rows and encoded/decoded payloads; target accounts own independent cap probes; expected Rows, mutated image copies, and golden text use ordinary test allocations. |
| failure | Codec ImageFailure faults, actual query-account MemoryFailure, and injected test C++ replacement-new bad_alloc are distinguished; held decoded state survives encoded-image release and vice versa. |
| cost | Finite byte/row mutation loops scale with this fixture image; each injected replacement-new cut retries a codec call. Actual native allocations are the account-funded image buffers/decoded rows; test-side image copies, vectors, and oracle values are separate. |
| Design | [tests/unit/checkpoint_image_test.cpp](../../../../../tests/unit/checkpoint_image_test.cpp), [docs/checkpoints.md § Runtime image format 1](../../../../checkpoints.md), [docs/checkpoints.md § Resource and validation contract](../../../../checkpoints.md), [src/recovery/image.cpp](../../../../../src/recovery/image.cpp), [tests/recovery/runtime-image-v1.hex](../../../../../tests/recovery/runtime-image-v1.hex), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |
