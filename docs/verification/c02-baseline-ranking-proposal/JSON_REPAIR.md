# Allocation-safe JSON cleanup for C02's native lowering dependency

The source baseline is vendored nlohmann/json 3.12.0, SHA-256
`aaf127c04cb31c406e5b04a63f1ae89369fccde6d8fa7cdda1ed4f32dfc5de63`.
`upstream/nlohmann-json-3.12.0.hpp` is the exact preserved original and
`upstream/LICENSE.MIT` preserves its license. `json-cleanup.patch` is the full
local difference. The excluded patched header has SHA-256
`f763c58b102e65242d09275aec4b2f343268280ab4587b15587ad143b2e2a406`.

The original `json_value::destroy` allocates a vector to flatten nested values.
Native PhysicalPlan protects its retained canonical identity during final
destruction, but temporary DOMs in identity generation, physical binding and
normalized replay are not covered by that guard. A persistent allocation fault
in those temporary destructors can terminate instead of reaching C02's outer
bad_alloc catch. This is a concrete dependency of memory ranking.

The patch preserves the normal iterative flattening algorithm. Its active
`current_item` lives outside a try scope, rather than being destroyed while an
allocation exception travels to the handler. If stack reservation/growth throws
bad_alloc, current_item, stack elements and original container values may each
own distinct partially moved descendants. The handler clears all three owners
without allocating. It iteratively descends to a last leaf, erases that leaf,
and repeats, never keeping a depth-dependent recursion or heap stack.

Last-member erase matters for ordered_json: erasing an earlier entry could
shift/copy const string keys and allocate. Every structured child erased by the
fallback is already empty. Its normal destructor therefore needs no flattening
allocation. Normal cleanup keeps its fast iterative path; the slower repeated
descent is used only after allocation failure. Fallback cost is finite but may
be quadratic in nesting depth. It is exceptional cleanup, not a scored cost or
hard deadline guarantee.

No stored field, Json type, wire encoding, hash input, canonical order or normal
value semantics is changed. The intended native scope is CROWN's existing
exceptions-enabled default json, ordered_json and supported container/allocator
instantiations exercised by the independent probes. CROWN does not support or
enable JSON_NOEXCEPTION/-fno-exceptions; this packet does not expand that profile.
Custom allocators whose deallocation/destructors throw are not an added contract.

Every linked project C++ unit is rebuilt with the same patched include root.
Mixing cached native C++ archives would mix inline Json definitions and is not
an accepted reproduction. Only the parser's pinned C archive is reused, from
Release for strict and from the sanitizer configuration for ASan/UBSan. The
native header and archives remain untouched. A later native integration must
update the existing CMake vendored-checksum guard and run its full matrix.

Independent inspection found no static ownership/last-erase blocker in the
exceptions-enabled default/ordered paths. Root subsequently reproduced the
original abort and passed ordinary and ASan/UBSan/leak cleanup probes: 30 cases
and 96 fault points in each patched run, including 4,096-level cleanup. The
custom probe type is a std::vector-derived array with ProbeAllocator (its label
`deque_json` does not mean std::deque was tested). Deep-chain serialization is
not claimed. The serialized compatibility output was 254,074 bytes with equal
original/patched SHA-256
`3affc55d1305636b4d6e7ad77c7a89cec58f1649ad40f74b1ca68a967fb5fdb0`.
`BUILD_RESULTS.md` pins the root receipt and preserves its limited scope.
