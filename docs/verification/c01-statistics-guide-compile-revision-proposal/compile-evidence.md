# Snippet compile evidence

Four strict translation-unit compiles succeeded with exit code 0 on the frozen combined API overlay, manifest SHA-256 `cb0ecb64935f80bf4915aa069de1bf01bcf1ea2f22a591f6f7408d405fcf4cfe`. The owner-state snippet and the combined Delta snippet were each compiled once without `CROWN_RUNTIME_TESTING` and once with `CROWN_RUNTIME_TESTING=1`. Each command uses `-c`; none linked or ran an executable.

Compiler: `c++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0`.

The exact shared flags and include order are `-std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG -O3 -I docs/verification/c01-statistics-combined-proposal/overlay/include -I include -isystem third_party`. `-MD` emits the recorded dependency files, including the system JSON header and the project headers used through the actual public API.

## Exact commands

Owner-state snippet, production preprocessing:

```sh
c++ -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG -O3 -I docs/verification/c01-statistics-combined-proposal/overlay/include -I include -isystem third_party -MD -MF /tmp/crown-c01-guide-revision-owner-production.d -c /tmp/crown-c01-guide-revision-owner.cpp -o /tmp/crown-c01-guide-revision-owner-production.o > /tmp/crown-c01-guide-revision-owner-production.log 2>&1
```

Owner-state snippet, testing preprocessing:

```sh
c++ -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG -O3 -DCROWN_RUNTIME_TESTING=1 -I docs/verification/c01-statistics-combined-proposal/overlay/include -I include -isystem third_party -MD -MF /tmp/crown-c01-guide-revision-owner-testing.d -c /tmp/crown-c01-guide-revision-owner.cpp -o /tmp/crown-c01-guide-revision-owner-testing.o > /tmp/crown-c01-guide-revision-owner-testing.log 2>&1
```

Combined state/workload snippet, production preprocessing:

```sh
c++ -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG -O3 -I docs/verification/c01-statistics-combined-proposal/overlay/include -I include -isystem third_party -MD -MF /tmp/crown-c01-guide-revision-combined-production.d -c /tmp/crown-c01-guide-revision-combined.cpp -o /tmp/crown-c01-guide-revision-combined-production.o > /tmp/crown-c01-guide-revision-combined-production.log 2>&1
```

Combined state/workload snippet, testing preprocessing:

```sh
c++ -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -UNDEBUG -O3 -DCROWN_RUNTIME_TESTING=1 -I docs/verification/c01-statistics-combined-proposal/overlay/include -I include -isystem third_party -MD -MF /tmp/crown-c01-guide-revision-combined-testing.d -c /tmp/crown-c01-guide-revision-combined.cpp -o /tmp/crown-c01-guide-revision-combined-testing.o > /tmp/crown-c01-guide-revision-combined-testing.log 2>&1
```

## Artifact identities

| Translation unit | Source SHA-256 | Exit | Log SHA-256 | Object SHA-256 | Dependency-list SHA-256 |
| --- | --- | ---: | --- | --- | --- |
| Owner production | `dbfc27e227587ad8b87f9ac79af2f9786d0a558a4a8157234b7281c5c4f025b5` | 0 | `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855` | `074bf1838d241a5b1e17be6769fd50800c457543604b39226a4a4804b39ea871` | `987b51f0216dd37e7d296a73e4657c79edc3fc61c5baf7490ca9a192418e54f0` |
| Owner testing | `dbfc27e227587ad8b87f9ac79af2f9786d0a558a4a8157234b7281c5c4f025b5` | 0 | `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855` | `074bf1838d241a5b1e17be6769fd50800c457543604b39226a4a4804b39ea871` | `d798edd5e7399453826c66cf8ed4b4e7e9aeee33ac26c72fc2b25d97a13c1b0e` |
| Combined production | `cf0d8df00e96d922e8f94e40caa6bcef163d95aa3d2ee447f1c0427f740d7eb0` | 0 | `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855` | `9f1d077a2858e0f0391cb391b0cd72543f508ea6de70a2335a455b3be6c16e85` | `21bde779a4f13f25524f68f8c1ce84a862c2b8034f9d1d0258a11ac5e072236c` |
| Combined testing | `cf0d8df00e96d922e8f94e40caa6bcef163d95aa3d2ee447f1c0427f740d7eb0` | 0 | `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855` | `9f1d077a2858e0f0391cb391b0cd72543f508ea6de70a2335a455b3be6c16e85` | `dc61af8e696522f0514e955b0307a36a914fde8e634bb7bf3d9368380f160975` |

The source files are byte-for-byte extractions of the two C++ fences in `overlay/docs/statistics.md`. The empty log hash means the successful compile emitted no diagnostic text. `input-pins.sha256` pins the combined package and public headers plus the native headers and third-party JSON header in the generated dependency lists.

The original frozen guide recorded a missing-header failure because its include list omitted `-isystem third_party`; that failure preceded API parsing and is retained in the old package. Its raw compiler log was not retained there, so no old failure log hash is claimed. This new revision adds the include path and records the four successful compile-only attempts above.
