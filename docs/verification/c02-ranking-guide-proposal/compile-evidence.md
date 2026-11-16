# Compile evidence

The usage snippets were compiled against the header bytes the API owner marked
stable for this guide; they are pinned in `input-pins.sha256`. The wider C02
proposal is not frozen or accepted. Any later public-header change requires a
new pin and compile. Compiler: `c++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0`.

Both compile commands exited 0 and produced empty diagnostic logs. They used
`-std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror`,
the C02 overlay include directory before native `include`, and
`-isystem third_party`. `-c` produced object files only; no link or execution
occurred. No `NDEBUG` was defined. The active-time API revision was included in
both compiles. One standalone translation unit combines the three displayed
function bodies with shared includes and namespace aliases; those bodies are
unchanged.

```sh
c++ --version > /tmp/crown-c02-guide-final-20261107/compiler-version.txt 2>&1

c++ -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror \
  -I docs/verification/c02-baseline-ranking-proposal/overlay/include \
  -I include -isystem third_party \
  -MMD -MF /tmp/crown-c02-guide-final-20261107/ranking-guide-production.d \
  -c /tmp/crown-c02-guide-final-20261107/ranking-guide.cpp \
  -o /tmp/crown-c02-guide-final-20261107/ranking-guide-production.o \
  > /tmp/crown-c02-guide-final-20261107/ranking-guide-production.log 2>&1

c++ -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror \
  -DCROWN_RUNTIME_TESTING \
  -I docs/verification/c02-baseline-ranking-proposal/overlay/include \
  -I include -isystem third_party \
  -MMD -MF /tmp/crown-c02-guide-final-20261107/ranking-guide-testing.d \
  -c /tmp/crown-c02-guide-final-20261107/ranking-guide.cpp \
  -o /tmp/crown-c02-guide-final-20261107/ranking-guide-testing.o \
  > /tmp/crown-c02-guide-final-20261107/ranking-guide-testing.log 2>&1
```

| Artifact | SHA-256 |
| --- | --- |
| Snippet source | `3c7f715a6df2a34060a2259ac4e5d44739cf9a53985d19702acc58c5c6365f3c` |
| Compiler version record | `88b7c4b67564a146863224148116065fee418539f0a408f3636a68f3bde51805` |
| Production object | `926f0585a7ec5860a4ee403f8539f5d4680349c74c0e6c354fa945abb2bd00ae` |
| Production diagnostics (empty) | `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855` |
| Production dependency map | `82ab40901ca60b3b08fc3658cd021b8f746a984e1bc11cb12ef89c01233e0f0b` |
| Testing-macro object | `926f0585a7ec5860a4ee403f8539f5d4680349c74c0e6c354fa945abb2bd00ae` |
| Testing-macro diagnostics (empty) | `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855` |
| Testing-macro dependency map | `58e35e1154d39f463a5cbaa7fa7834730676e022e32e01a49b05f813537b31c0` |

The dependency-map hashes record the compiler's project-local include closure
for both variants. Input pins record all project headers in that closure. The
active system C++ library and system headers are not individually hash-pinned;
the compiler identity/version and invocation are recorded. `third_party` was
passed as a system include directory and produced no local entry in the
dependency maps.
