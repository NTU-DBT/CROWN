# `include/crown/ir/program_span.hpp` — block usage map

[Source](../../../../../../include/crown/ir/program_span.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Expose borrowed spans into immutable native program storage.

Snapshot SHA-256: `2ba82fc7a68b200b5cc3ccb97c8dc378f0050609f85346b78e13f21ad60e6cd2`. 49 lines partitioned into 19 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_identity.md](../../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../../include/crown/ir/program_span.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Borrowed immutable range. Its backing metadata must outlive every view and · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../../include/crown/ir/program_span.hpp#L16) | Callable definition: Span(const T* data,std::size_t size) noexcept:data_(data,size) | calls data_ · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../../include/crown/ir/program_span.hpp#L17) | Callable definition: Span(std::span&lt;const T&gt; data) noexcept:data_(data) | calls data_ · [reviewed contract](#b0003) |
| [B0004 · 18–18](../../../../../../include/crown/ir/program_span.hpp#L18) | Callable definition: \[\[nodiscard\]\] const T* data() const noexcept | calls ; returns data_.data() · [reviewed contract](#b0004) |
| [B0005 · 19–19](../../../../../../include/crown/ir/program_span.hpp#L19) | Callable definition: \[\[nodiscard\]\] std::size_t size() const noexcept | calls ; returns data_.size() · [reviewed contract](#b0005) |
| [B0006 · 20–20](../../../../../../include/crown/ir/program_span.hpp#L20) | Callable definition: \[\[nodiscard\]\] bool empty() const noexcept | calls ; returns data_.empty() · [reviewed contract](#b0006) |
| [B0007 · 21–21](../../../../../../include/crown/ir/program_span.hpp#L21) | Callable definition: \[\[nodiscard\]\] iterator begin() const noexcept | calls ; returns data_.begin() · [reviewed contract](#b0007) |
| [B0008 · 22–22](../../../../../../include/crown/ir/program_span.hpp#L22) | Callable definition: \[\[nodiscard\]\] iterator end() const noexcept | calls ; returns data_.end() · [reviewed contract](#b0008) |
| [B0009 · 23–23](../../../../../../include/crown/ir/program_span.hpp#L23) | Callable definition: \[\[nodiscard\]\] auto rbegin() const noexcept | calls ; returns data_.rbegin() · [reviewed contract](#b0009) |
| [B0010 · 24–24](../../../../../../include/crown/ir/program_span.hpp#L24) | Callable definition: \[\[nodiscard\]\] auto rend() const noexcept | calls ; returns data_.rend() · [reviewed contract](#b0010) |
| [B0011 · 25–25](../../../../../../include/crown/ir/program_span.hpp#L25) | Explanatory comments or spacing. | source comment (unverified): // Subscript/front/back require valid indices; at() is the checked boundary. · [reviewed contract](#b0011) |
| [B0012 · 26–26](../../../../../../include/crown/ir/program_span.hpp#L26) | Callable definition: \[\[nodiscard\]\] const T& operator\[\](std::size_t i) const noexcept | returns data_\[i\]; source comment (unverified): // Subscript/front/back require valid indices; at() is the checked boundary. · [reviewed contract](#b0012) |
| [B0013 · 27–30](../../../../../../include/crown/ir/program_span.hpp#L27) | Callable definition: \[\[nodiscard\]\] const T& at(std::size_t i) const | calls size, storage::IndexFailure; returns data_\[i\] · [reviewed contract](#b0013) |
| [B0014 · 31–31](../../../../../../include/crown/ir/program_span.hpp#L31) | Callable definition: \[\[nodiscard\]\] const T& front() const noexcept | calls ; returns data_.front() · [reviewed contract](#b0014) |
| [B0015 · 32–32](../../../../../../include/crown/ir/program_span.hpp#L32) | Callable definition: \[\[nodiscard\]\] const T& back() const noexcept | calls ; returns data_.back() · [reviewed contract](#b0015) |
| [B0016 · 33–33](../../../../../../include/crown/ir/program_span.hpp#L33) | Callable definition: \[\[nodiscard\]\] operator std::span&lt;const T&gt;() const noexcept | returns data_ · [reviewed contract](#b0016) |
| [B0017 · 34–39](../../../../../../include/crown/ir/program_span.hpp#L34) | declares values/defaults or compile-time conditions. | source comment (unverified): // Builder/caller supplies sorted storage; this wrapper neither sorts nor · [reviewed contract](#b0017) |
| [B0018 · 40–48](../../../../../../include/crown/ir/program_span.hpp#L40) | Type/record definition: template&lt;class T&gt; class Set:public Span&lt;T&gt; | returns it!=this-&gt;end() && *it==value?it:this-&gt;end(); find(value)!=this-&gt;end(); source comment (unverified): // Builder/caller supplies sorted storage; this wrapper neither sorts nor · [reviewed contract](#b0018) |
| [B0019 · 49–49](../../../../../../include/crown/ir/program_span.hpp#L49) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::program · [reviewed contract](#b0019) |

## B0001

[Lines 1–15](../../../../../../include/crown/ir/program_span.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> class Span
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a lightweight immutable metadata range. |
| inputs / outputs | Wraps std::span&lt;const T&gt;; declares iterator/value aliases and checked/unchecked access. |
| invariants | Raw constructors require a valid range; the type alone does not prove factory admission. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | No eager range/lifetime validation; violating a standard span precondition is caller error. |
| cost | Fixed descriptor storage/copies; no element construction or traversal. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
using value_type=T;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the element type for generic metadata consumers. |
| inputs / outputs | value_type is T, iterator is std::span&lt;const T&gt;::iterator. |
| invariants | Access remains const even though the alias names T. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | Compile-time declarations only. |
| cost | No runtime operation. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
Span() noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty borrowed range. |
| inputs / outputs | Default dynamic-extent span has size0. |
| invariants | Empty access through front/back/subscript still requires the usual preconditions. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | No throwing operation. |
| cost | Fixed initialization, no element allocation. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0002

[Lines 16–16](../../../../../../include/crown/ir/program_span.hpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Span(const T* data,std::size_t size)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a caller-provided contiguous range. |
| inputs / outputs | Stores pointer/count through std::span. |
| invariants | Caller supplies a valid live range; no ownership or sortedness proof is created. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | Invalid range is a violated constructor precondition; no recovery layer. |
| cost | Fixed descriptor construction. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0003

[Lines 17–17](../../../../../../include/crown/ir/program_span.hpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Span(std::span<const T> data)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt an existing immutable span. |
| inputs / outputs | Copies its range descriptor. |
| invariants | Source span destruction is harmless only while the actual backing storage survives. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | No throwing operation. |
| cost | Constant descriptor copy. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0004

[Lines 18–18](../../../../../../include/crown/ir/program_span.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const T* data() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the range base pointer. |
| inputs / outputs | Returns data_.data(), including empty-range pointers. |
| invariants | The pointer carries no size or retention. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | No throwing operation. |
| cost | Constant pointer access. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0005

[Lines 19–19](../../../../../../include/crown/ir/program_span.hpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t size() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the range element count. |
| inputs / outputs | Returns data_.size(). |
| invariants | Count is not bytes or runtime work authority. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | No throwing operation. |
| cost | Constant count access. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0006

[Lines 20–20](../../../../../../include/crown/ir/program_span.hpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool empty() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether the range has elements. |
| inputs / outputs | Returns data_.empty(). |
| invariants | Empty does not describe ownership or query truth. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | No throwing operation. |
| cost | Constant count test. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0007

[Lines 21–21](../../../../../../include/crown/ir/program_span.hpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
iterator begin() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the forward start iterator. |
| inputs / outputs | Returns data_.begin(). |
| invariants | Iterator has the range backing lifetime and no retaining handle. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | No throwing operation. |
| cost | Constant iterator construction. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0008

[Lines 22–22](../../../../../../include/crown/ir/program_span.hpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
iterator end() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the forward sentinel iterator. |
| inputs / outputs | Returns data_.end(). |
| invariants | End is not dereferenceable. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | No throwing operation. |
| cost | Constant iterator construction. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0009

[Lines 23–23](../../../../../../include/crown/ir/program_span.hpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto rbegin() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the reverse start iterator. |
| inputs / outputs | Returns data_.rbegin(). |
| invariants | Empty ranges have no dereferenceable reverse start. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | No throwing operation. |
| cost | Constant reverse-iterator construction. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0010

[Lines 24–24](../../../../../../include/crown/ir/program_span.hpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto rend() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the reverse end iterator. |
| inputs / outputs | Returns data_.rend(). |
| invariants | Reverse end is not dereferenceable. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | No throwing operation. |
| cost | Constant reverse-iterator construction. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0011

[Lines 25–25](../../../../../../include/crown/ir/program_span.hpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L25:sha256:8cdbc6bafeb9c5efe57722ba40c33d4761f2342cade05a978922298d981ad1f1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Subscript/front/back require valid indices; at() is the checked boundary. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/ir/program_span.hpp lines 23-27; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [docs/code_specs/files/include/crown/ir/program_span.hpp.md](program_span.hpp.md), [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md) |

## B0012

[Lines 26–26](../../../../../../include/crown/ir/program_span.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const T& operator[](std::size_t i)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Access a prevalidated element without another explicit guard. |
| inputs / outputs | Returns data_\[i\] by reference. |
| invariants | Requires i&lt;size(); no bounds or lifetime check is performed here. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | Out-of-range use violates the access precondition. |
| cost | Constant address/reference access. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0013

[Lines 27–30](../../../../../../include/crown/ir/program_span.hpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const T& at(std::size_t i)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the metadata index before access. |
| inputs / outputs | Rejects i&gt;=size(), else returns data_\[i\]. |
| invariants | Check does not validate backing lifetime. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | Throws fixed-message IndexFailure(contract); no ordinary message construction. |
| cost | One bounds test and constant access; no successful-path allocation. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0014

[Lines 31–31](../../../../../../include/crown/ir/program_span.hpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const T& front() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the first prevalidated element. |
| inputs / outputs | Returns data_.front(). |
| invariants | Requires a nonempty live range. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | Empty access violates its precondition. |
| cost | Constant access without an explicit extra guard. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0015

[Lines 32–32](../../../../../../include/crown/ir/program_span.hpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const T& back() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the last prevalidated element. |
| inputs / outputs | Returns data_.back(). |
| invariants | Requires a nonempty live range. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | Empty access violates its precondition. |
| cost | Constant access without an explicit extra guard. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0016

[Lines 33–33](../../../../../../include/crown/ir/program_span.hpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
operator std::span<const T>() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pass metadata to APIs accepting an immutable standard span. |
| inputs / outputs | Returns the same range descriptor. |
| invariants | Conversion retains neither Program nor backing elements. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | No throwing operation. |
| cost | Constant descriptor copy. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0017

[Lines 34–39](../../../../../../include/crown/ir/program_span.hpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const T> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the sole range descriptor. |
| inputs / outputs | Holds base/count through standard span. |
| invariants | No hidden owner, allocation registry or liveness state exists. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | No field-side failure. |
| cost | Fixed storage, no destructor traversal. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0018

[Lines 40–48](../../../../../../include/crown/ir/program_span.hpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> class Set
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide ordered lookup over borrowed metadata. |
| inputs / outputs | Inherits Span constructors and adds find/contains. |
| invariants | Caller/builder must supply sorting consistent with &lt; and equality; this wrapper neither sorts nor enforces uniqueness. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | Invalid ordering violates lookup assumptions; comparator exceptions propagate. |
| cost | No new index/container; lookup costs are paid at each call. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
iterator find(const T& value) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find an exactly equal element in a sorted borrowed range. |
| inputs / outputs | lower_bound followed by end/equality check; absent returns end. |
| invariants | Sortedness and comparison consistency are construction preconditions. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | T comparisons may throw; no catch or mutation. |
| cost | Logarithmic ordered comparisons plus equality; arbitrary T comparisons may themselves allocate or have nonconstant cost. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
bool contains(const T& value) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report whether ordered lookup finds an equal element. |
| inputs / outputs | Compares find(value) with end(). |
| invariants | Same sortedness/lifetime requirements as find. |
| ownership | Descriptor/iterator/reference borrows immutable T storage. No owner or account is retained; backing objects must stay alive at stable addresses. Copies do not extend that lifetime. |
| failure | Comparator exceptions propagate. |
| cost | One find, no second scan or membership cache. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0019

[Lines 49–49](../../../../../../include/crown/ir/program_span.hpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L49:sha256:774e0e57e452387e8b836521923bfa4cdc6e11df831614d813437c520633a71a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::program at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [include/crown/ir/program_span.hpp](../../../../../../include/crown/ir/program_span.hpp), [docs/code_specs/files/include/crown/ir/program_span.hpp.md](program_span.hpp.md), [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md) |
