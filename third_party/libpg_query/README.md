# Vendored libpg_query source archive

This directory contains the unmodified libpg_query 18.1.0 source release
archive from the pinned upstream commit `c1546e7e97edc93fe8474d7a59881e91fbf48cfc`.
Its SHA-256 is
`2d3486cf6a9d3955b53e66235db39d62b54216c820cd392ab66dc842c5b1316d`.

The archive includes libpg_query's generated PostgreSQL 18.6 sources, so the
build extracts it under the CMake binary directory and invokes the upstream
Makefile's `build` target. This uses the configured C compiler and requires
GNU Make; it does not download PostgreSQL or run Bison, Ruby, or protobuf code
generation. The source archive is the build input; no pre-existing build
output is required.

The upstream archive preserves its original license and component notices.
Copies are also provided in `notices/` for convenient review:

- `LICENSE.libpg_query`: libpg_query's upstream license.
- `COPYRIGHT.postgresql`: PostgreSQL source copyright and license notice.
- `LICENSE.upb`: bundled upb notice.
- `LICENSE.utf8_range`: bundled utf8_range notice.
- `LICENSE.xxhash.hdr`: the xxHash BSD 2-Clause notice copied from the bundled
  `vendor/xxhash/xxhash.h` header.

These are upstream notices, not a new project-wide license selection.
