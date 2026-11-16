# `include/crown/ir/program_json.hpp` — block usage map

[Source](../../../../../../include/crown/ir/program_json.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs.

Snapshot SHA-256: `c3e56960300c886d2f0abb32805c6ac45b75d118bafc2a7c3f9f7258e9071db5`. 36 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/physical_runtime.md](../../../../../physical_runtime.md), [docs/query_identity.md](../../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/ir/program_json.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 9–9](../../../../../../include/crown/ir/program_json.hpp#L9) | Type/record definition: enum class JsonKind |  · [reviewed contract](#b0002) |
| [B0003 · 10–12](../../../../../../include/crown/ir/program_json.hpp#L10) | Explanatory comments or spacing. | source comment (unverified): // Flat child ranges are owned by Program's native metadata arena. · [reviewed contract](#b0003) |
| [B0004 · 13–35](../../../../../../include/crown/ir/program_json.hpp#L13) | Type/record definition: class JsonView | returns kind()==JsonKind::null; kind()==JsonKind::array; source comment (unverified): // Flat child ranges are owned by Program's native metadata arena. · [reviewed contract](#b0004) |
| [B0005 · 36–36](../../../../../../include/crown/ir/program_json.hpp#L36) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::program · [reviewed contract](#b0005) |

## B0001

[Lines 1–8](../../../../../../include/crown/ir/program_json.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
namespace detail { struct JsonNode; class Builder; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native JSON node and builder implementation types incomplete while allowing \`JsonView\` and its friend builder to refer to them. |
| inputs / outputs | The declarations name \`detail::JsonNode\` and \`detail::Builder\`; the view stores a pointer to a node and exposes read-only accessors. |
| invariants | These private incomplete types are not a public parser/import API. A view is valid only while the native metadata owning its node remains alive. |
| ownership | This declaration does not retain an owner; \`CompiledProgram\` owns the flat metadata arena backing node and string views. |
| failure | No operation occurs here; actual \`JsonView\` accessors require the requested kind and valid array/object index. |
| cost | No runtime cost for the declarations. View access returns borrowed scalar/range values; builder allocation occurs during native program construction. |
| Design | [include/crown/ir/program_json.hpp §detail declarations and JsonView](../../../../../../include/crown/ir/program_json.hpp), [include/crown/ir/program.hpp §CompiledProgram ownership](../../../../../../include/crown/ir/program.hpp), [src/ir/program.cpp §JsonView accessors](../../../../../../src/ir/program.cpp) |

## B0002

[Lines 9–9](../../../../../../include/crown/ir/program_json.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class JsonKind
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the exact stored native JSON alternatives. |
| inputs / outputs | Ordered tags null/bool/signed/unsigned/double/text/array/object match JsonNode variant indices. |
| invariants | Tag layout is a private native representation, not an editable proof/source token. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | No runtime failure at declaration/default/fixed metadata access; actual backing lifetime remains a caller precondition. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0003

[Lines 10–12](../../../../../../include/crown/ir/program_json.hpp#L10); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L10-L12:sha256:2eab629fbee2b6c53daa40add13c75e54ff6d0bd10a6739897650876c080a1e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Flat child ranges are owned by Program's native metadata arena. Views borrow that arena and never retain the original nlohmann JSON graph. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/ir/program_json.hpp lines 8-14; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [docs/code_specs/files/include/crown/ir/program_json.hpp.md](program_json.hpp.md), [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md) |

## B0004

[Lines 13–35](../../../../../../include/crown/ir/program_json.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class JsonView
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect a previously frozen native metadata JSON tree. |
| inputs / outputs | Exposes typed scalar and indexed array/object access over JsonNode. |
| invariants | No mutation or construction from an arbitrary public JsonNode pointer. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | No runtime failure at declaration/default/fixed metadata access; actual backing lifetime remains a caller precondition. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
JsonView() noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the empty/null native JSON view. |
| inputs / outputs | node_ remains nullptr; kind is null and size is0. |
| invariants | Default null is data, not a checked query operator or proof. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | No runtime failure at declaration/default/fixed metadata access; actual backing lifetime remains a caller precondition. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
JsonKind kind() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the exact stored kind. |
| inputs / outputs | Null pointer maps to null; live node maps its variant index. |
| invariants | No numeric type coercion or DOM traversal. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | No runtime failure at declaration/default/fixed metadata access; actual backing lifetime remains a caller precondition. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
bool is_null() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test the null alternative. |
| inputs / outputs | Compares kind with null. |
| invariants | A null view has no dereferenceable node. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | No runtime failure at declaration/default/fixed metadata access; actual backing lifetime remains a caller precondition. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
bool is_array() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test the array alternative. |
| inputs / outputs | Compares kind with array. |
| invariants | Does not enumerate children. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | No runtime failure at declaration/default/fixed metadata access; actual backing lifetime remains a caller precondition. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
bool is_object() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test the object alternative. |
| inputs / outputs | Compares kind with object. |
| invariants | Does not look up object keys. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | No runtime failure at declaration/default/fixed metadata access; actual backing lifetime remains a caller precondition. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
bool is_structured() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether indexed children are available. |
| inputs / outputs | Returns is_array() \|\| is_object(). |
| invariants | Null and scalars are unstructured. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | No runtime failure at declaration/default/fixed metadata access; actual backing lifetime remains a caller precondition. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
std::size_t size() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read immediate child count or scalar cardinality. |
| inputs / outputs | Arrays/objects return flat-range size; null0; other scalar1. |
| invariants | Not a recursive byte/node count. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | No runtime failure at declaration/default/fixed metadata access; actual backing lifetime remains a caller precondition. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
JsonView at(std::size_t) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an array child at a checked index. |
| inputs / outputs | Requires array kind then checks the flat child span index. |
| invariants | Object access uses member/key instead; no cross-kind coercion. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | Wrong kind or out-of-range child index throws fixed IndexFailure(contract) in the implementation. No parsing, publication, recovery or ordinary diagnostic string construction. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
std::string_view key(std::size_t) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an object member name. |
| inputs / outputs | Requires object kind and checked member index. |
| invariants | Positional access; no name lookup or text copy. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | Wrong kind or out-of-range child index throws fixed IndexFailure(contract) in the implementation. No parsing, publication, recovery or ordinary diagnostic string construction. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
JsonView member(std::size_t) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an object member value. |
| inputs / outputs | Requires object kind and checked member index. |
| invariants | Returned child shares arena lifetime, independently of this view descriptor. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | Wrong kind or out-of-range child index throws fixed IndexFailure(contract) in the implementation. No parsing, publication, recovery or ordinary diagnostic string construction. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
bool boolean() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an exactly Boolean native scalar. |
| inputs / outputs | Requires boolean kind, returns stored bool. |
| invariants | No truthiness conversion. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | Wrong kind or out-of-range child index throws fixed IndexFailure(contract) in the implementation. No parsing, publication, recovery or ordinary diagnostic string construction. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
std::int64_t integer() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an exactly signed native integer. |
| inputs / outputs | Requires integer kind, returns stored int64. |
| invariants | Unsigned/double alternatives are rejected rather than coerced. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | Wrong kind or out-of-range child index throws fixed IndexFailure(contract) in the implementation. No parsing, publication, recovery or ordinary diagnostic string construction. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
std::uint64_t unsigned_integer() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an exactly unsigned native integer. |
| inputs / outputs | Requires unsigned_integer kind, returns stored uint64. |
| invariants | Signed/double alternatives are rejected rather than coerced. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | Wrong kind or out-of-range child index throws fixed IndexFailure(contract) in the implementation. No parsing, publication, recovery or ordinary diagnostic string construction. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
double number() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the stored floating-number alternative. |
| inputs / outputs | Requires number kind, returns stored double. |
| invariants | This does not convert signed or unsigned integer alternatives. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | Wrong kind or out-of-range child index throws fixed IndexFailure(contract) in the implementation. No parsing, publication, recovery or ordinary diagnostic string construction. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
std::string_view text() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow frozen native JSON text. |
| inputs / outputs | Requires string kind, returns stored string_view. |
| invariants | No owning export or UTF8 revalidation at this accessor. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | Wrong kind or out-of-range child index throws fixed IndexFailure(contract) in the implementation. No parsing, publication, recovery or ordinary diagnostic string construction. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
friend class detail::Builder;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict node-pointer construction to the native builder. |
| inputs / outputs | Builder can invoke the private JsonNode pointer constructor. |
| invariants | Public callers can create null but cannot supply a node pointer through this API. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | No runtime failure at declaration/default/fixed metadata access; actual backing lifetime remains a caller precondition. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
explicit JsonView(const detail::JsonNode* node)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a builder-selected native node. |
| inputs / outputs | Stores the pointer without copying its graph. |
| invariants | Builder owns validity; pointer construction adds no retention. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | No runtime failure at declaration/default/fixed metadata access; actual backing lifetime remains a caller precondition. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

```text
const detail::JsonNode* node_=nullptr;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the optional borrowed node pointer. |
| inputs / outputs | Null sentinel represents null view. |
| invariants | Destroying this descriptor never destroys the arena or DOM. |
| ownership | Bare pointer/view borrows Program native metadata; child/text/key views retain no owner and require that arena to survive. The original nlohmann DOM is not retained. |
| failure | No runtime failure at declaration/default/fixed metadata access; actual backing lifetime remains a caller precondition. |
| cost | Constant descriptor/tag/count/index access with no successful-path allocation or recursive traversal; returned string bytes remain borrowed. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [src/ir/program.cpp](../../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../../include/crown/ir/program.hpp), [tests/unit/native_program_test.cpp](../../../../../../tests/unit/native_program_test.cpp) |

## B0005

[Lines 36–36](../../../../../../include/crown/ir/program_json.hpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L36:sha256:774e0e57e452387e8b836521923bfa4cdc6e11df831614d813437c520633a71a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::program at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [include/crown/ir/program_json.hpp](../../../../../../include/crown/ir/program_json.hpp), [docs/code_specs/files/include/crown/ir/program_json.hpp.md](program_json.hpp.md), [docs/semantics.md](../../../../../semantics.md), [docs/physical_plans.md](../../../../../physical_plans.md) |
