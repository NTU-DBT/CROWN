# Sanitizer source and provenance scope

The logical five-consumer suite uses these immutable files:

| Consumer | Source packet |
| --- | --- |
| selection_public_independent | Original frozen independent packet |
| selection_cache_independent | Frozen cache-correction packet |
| selection_resources_independent | Original frozen independent packet |
| selection_binding_independent | Frozen independent strict-revision packet |
| selection_publication_fault_independent | Frozen independent strict-revision packet |

The shared `selection_independent_fixture.hpp` stays in the original packet.
Every sanitizer consumer is compiled anew. Ordinary objects/binaries are
historical evidence only and cannot enter the sanitizer link. No testing-runtime
macro or archive is used. The byte consumer links no runtime/report archive;
the other four link the production selection/ranking/runtime bridge closure.

The frozen current input identities cover:

- Those six actual source/header files, all three package/source manifest FILEs,
  literal/checklist/lineage documentation, the separate correction diffs, and root's
  terminal independent strict build/test receipts.
- The held two C05 public headers, private selection_detail/ranking declarations,
  five pure implementation units, production runtime bridge, and exact matching
  root-created sanitizer archive/object/command/dependency/source receipt.
- Native current include/src inputs, the native execution-freeze FILE and relevant
  provenance, active patched JSON, the matching native sanitizer C++/parser
  archives, and exact compiler/frontend/linker identities.
- The immutable design/API/normalized-fixture checkpoint FILEs. The normalized
  producer test is not compiled or linked by this independent suite, so its source
  file is not a new current input merely because it appeared in an old manifest.

Historical input manifests are checked only as FILE bytes. No old manifest's
entries are replayed after approved producer or status-document changes. Native
README/ranking/native_build status prose is not a compilation dependency and
does not enter the new current source scope. This exclusion never permits a
changed code/header/archive byte to pass without a new matched closure.

Root must retain full `-MD` dependency rows and hash every actual project/system
dependency before accepting sanitizer execution. A fresh include path or source
listing is not represented as an unseen compiler dependency record. The packet
is frozen against the terminal matching closure and corrected strict results;
the independent sanitizer build/run and its fresh dependency rows remain pending.
