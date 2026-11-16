# C02 JSON cleanup fault-injection probe

This is an excluded, header-only regression probe for the proposed nlohmann JSON destructor cleanup change. It does not modify native `third_party`, link a CROWN archive, or exercise a CROWN report/runtime path. The root agent owns every probe execution and result record. This packet records compile/link evidence only; no runtime result is claimed here.

The patched header under test is the proposal overlay at [`../c02-baseline-ranking-proposal/overlay/third_party/nlohmann/json.hpp`](../c02-baseline-ranking-proposal/overlay/third_party/nlohmann/json.hpp), SHA-256 `f763c58b102e65242d09275aec4b2f343268280ab4587b15587ad143b2e2a406`. The original control is the preserved upstream header at [`../c02-baseline-ranking-proposal/upstream/nlohmann-json-3.12.0.hpp`](../c02-baseline-ranking-proposal/upstream/nlohmann-json-3.12.0.hpp), SHA-256 `aaf127c04cb31c406e5b04a63f1ae89369fccde6d8fa7cdda1ed4f32dfc5de63`; it matches the frozen native `third_party/nlohmann/json.hpp` byte-for-byte at the time pinned in `input-pins.sha256`.

The single source, [`probe.cpp`](probe.cpp), has two modes:

- `--serialize` constructs default `json`, `ordered_json`, and a custom vector-derived array using a counting allocator. It emits `sizeof` and normal serialized bytes for empty, scalar, string, binary, wide-array, long-key-object, growth-array, growth-object, and mixed-nested values. The 4096-level chain is built iteratively and intentionally omitted from serialization. Root can byte-compare original and patched output.
- `--cleanup` performs an ordinary teardown census and then reconstructs each value for persistent global-`new` failure at every observed cleanup allocation point. The injected failure remains active until the destructor returns, so a second allocation attempt is recorded and fails. It checks allocation/free balance, restored live-allocation counts, one injected failure at the selected point, and absence of a retry allocation. Growth shapes require more than two cleanup allocation points so the loop reaches stack growth.

Each tree is constructed and serialized before the cleanup accounting window. The deep-chain case skips serialization to avoid using the serializer as a second recursion-depth test. Formatting and output happen only after fault injection is disabled. The process is single-threaded by design.

The counter covers calls through the replaceable global C++ `new`/`delete` functions used by this probe. It is not a census of direct `malloc`, OS, sanitizer, or all possible custom allocator activity. The custom allocator delegates to `std::allocator`; sanitizer leak detection is the independent heap-leak check. A successful compile/link says nothing about runtime cleanup behavior. Root must run the original control, patched ordinary probe, and patched ASan/UBSan probe, retain their raw output/exit status, and record any sanitizer diagnostics before interpreting the result.

All compiler inputs, output identities, commands, and pending root-only executions are listed in [`compile-evidence.md`](compile-evidence.md), [`ROOT_REPRODUCTION.md`](ROOT_REPRODUCTION.md), and [`input-pins.sha256`](input-pins.sha256).
