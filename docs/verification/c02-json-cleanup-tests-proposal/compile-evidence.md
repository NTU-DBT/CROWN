# Compile/link evidence

**Status: compiled and linked, not executed.** No benchmark, probe mode, checker, Python checker, CMake, CTest, or symbol-inspection tool was run by the author. Root owns all runtime validation and must not treat these build results as cleanup acceptance.

## Compiler and flags

Compiler command: `c++` resolves to `/usr/bin/c++` in the author environment. Version output:

```text
c++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
Copyright (C) 2023 Free Software Foundation, Inc.
```

All object builds used C++23, `-O1 -g`, `-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror`, and `-UNDEBUG`. The patched sanitizer object and executable additionally used `-fsanitize=address,undefined -fno-omit-frame-pointer`. No CROWN object, project archive, generated code, or native library was linked. The sanitizer build covers this entire standalone probe translation unit and the selected JSON header.

## Final-source compile and link outcomes

Every listed compile and link command exited 0. Each corresponding stdout/stderr log is empty (SHA-256 `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855`). The exact command lines are in [`ROOT_REPRODUCTION.md`](ROOT_REPRODUCTION.md).

| Variant | Header selected | Object SHA-256 | Linked executable SHA-256 |
|---|---|---|---|
| Original ordinary control | Preserved upstream 3.12.0 header, staged at `/tmp/crown-c02-json-cleanup-tests-20261107-a/original/nlohmann/json.hpp` | `629be23326e10806b70478f37e7a84ba92761b496d0ce0ee1fc55ec01184d34f` | `fac0768993d9d168fa086c26bfc750b359e6a61e6b6f7f96b37a323ce9180c7d` |
| Patched ordinary | Proposal overlay header | `b35dab14d5362a6a4506935e47ba395c46fa5f9c2e72362690025425bc4800a7` | `c3cd8d9c51151ab9ebdb073692268bf9cb7ad38fc7f747cc6befead9e75ea747` |
| Patched ASan/UBSan | Proposal overlay header | `7be2272fb5b69c2c8404445c68c4dfb2df6f2982e39b267aae205ee8206eb351` | `bbbefbb8778b18245ae83eee4bae6f3aaf8a54d1f1812f4692962d1e3b89fa92` |

The source SHA-256 is `532774214c13b5dfaac2cee798db37c7824e98db91a3eec91ab424eaa7797a79`. The overlay header SHA-256 is `f763c58b102e65242d09275aec4b2f343268280ab4587b15587ad143b2e2a406`. The preserved upstream header and native `third_party/nlohmann/json.hpp` both hash to `aaf127c04cb31c406e5b04a63f1ae89369fccde6d8fa7cdda1ed4f32dfc5de63`. These source and header pins are also recorded in [`input-pins.sha256`](input-pins.sha256).

Compile object/log files are under `/tmp/crown-c02-json-cleanup-tests-20261107-a/objects` and `/tmp/crown-c02-json-cleanup-tests-20261107-a/logs`; linked binaries are under the corresponding `bin` directory. Their hashes identify the exact outputs handed to root, but no execution result exists yet.

## Superseded compile preflight

An earlier candidate used `std::deque` for the custom JSON array. Its source hash was `880493d0f06261bafd03eea4542aa21bb0c111529c93cfbf19a1bfcda32f0c87`. The three strict compile attempts failed because the pinned nlohmann `basic_json::push_back` implementation accesses `array_t::capacity()`, which `std::deque` does not provide. This was a source/container compatibility error, not a cleanup finding. The final source uses a custom `std::vector`-derived array and custom allocator; all final variants compiled and linked as above. The preflight logs are retained under `/tmp/crown-c02-json-cleanup-tests-20261107-a/logs/preflight-deque-*` with hashes:

- Original control: `65971fba8ab492f54ab5b95e5e124414760ce2fc2a00c259d7a6dfab7d6ea915`
- Patched ordinary and patched sanitizer: `b3470d4dd734f96f5ab694444012bd2152c922fb8deaeb104a24ec2dc693c192`

The failed preflight candidate is historical only and is not part of the final input manifest. The root execution packet should use only the final source and binaries above.
