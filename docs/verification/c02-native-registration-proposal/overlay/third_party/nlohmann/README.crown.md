# nlohmann/json 3.12.0 with the CROWN cleanup repair

The active `json.hpp` is a locally patched copy, SHA-256
`f763c58b102e65242d09275aec4b2f343268280ab4587b15587ad143b2e2a406`.
The exact original upstream single header is preserved at
`upstream/nlohmann/json.hpp`, SHA-256
`aaf127c04cb31c406e5b04a63f1ae89369fccde6d8fa7cdda1ed4f32dfc5de63`.
Its source is the unchanged nlohmann/json v3.12.0 release single header.
All upstream copyright text remains in both headers; `LICENSE.MIT` remains
unchanged. The project distribution license is a separate unresolved A02 matter.

The complete local difference is `patches/crown-cleanup-oom.patch`, SHA-256
`65acb363a5b9787022eb3eb058641a0533a6cf6b642db5605a7c5848d681c9a9`.
The patch's two file labels identify the upstream and CROWN versions. It changes
only `json_value` cleanup: normal destruction keeps the iterative flattening
stack. If reserve or growth throws `std::bad_alloc`, an allocation-free,
nonrecursive fallback prunes last leaves from the current item, stack and
partially moved original containers. Keeping the active item outside the try
scope prevents premature throwing destruction during unwinding. Erasing the
last object member avoids ordered-map key-shift copies.

The slower fallback can revisit ancestors and be quadratic in depth. It is
exceptional cleanup, not a hard deadline or linear-time guarantee. No stored
field, type layout, wire format, hash input, canonical ordering or normal value
semantics is changed. The supported scope is CROWN's exceptions-enabled default
`json`, `ordered_json`, and the vector-derived array/counting allocator used by
the probe. `JSON_NOEXCEPTION`, `-fno-exceptions` and throwing destructors or
deallocators are not additional supported profiles.

All CROWN C++ objects must be rebuilt coherently with the active header. The
original header has its own isolated include root and header-only control
executable; it must never enter a CROWN target or be linked to CROWN archives.
CMake checks the active header, original header and patch identities offline.
`dependencies.lock.json` distinguishes active and original bytes explicitly.

The native registration proposes `json_cleanup` and
`json_patch_compatibility`. The first exercises ordinary and persistent-fault
teardown; the second compares complete serialization/sizeof output from the
two isolated executables and requires the original bad_alloc abort control.
The custom type label is `custom_vector_json`; it is not `std::deque`.
The 4,096-level case tests cleanup only, not recursive serialization.

The excluded predecessor probes passed ordinary and ASan/UBSan/leak checking
at root: 30 cases and 96 fault positions in each patched run, with the upstream
abort reproduced. This local publication and its full native matrix remain
pending; the probe does not establish arbitrary custom-container safety,
project-wide allocation bounds or C02 performance.
