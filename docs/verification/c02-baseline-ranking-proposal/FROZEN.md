# Excluded implementation freeze — 2026-11-07

This is the first full C02 baseline implementation packet. It preserves the
accepted frozen preflight and all native/C01/independent packages. No ledger or
handoff change is included; C02 remains `not_started`.

- Twelve overlay paths are pinned by source-files.sha256:
  `50e919ce4384ce7e7d4ca550ed09d5ae74b3579549441b6ba4be0c401aa56bf6`.
- The 641-row full input manifest is
  `b3d99557190b7ac1d6109f054ebafdb5a47a3aa298e9f45820a6e2a780a11587`.
- The immutable strict checkpoint is
  `0e58e774ca6a7ab2305a5f1fb0bfd4991feeb5f87b22d008f2c858f7b5062ac8`.
- The matching sanitizer/supplemental checkpoint is
  `a350d6cd7780440ef9aa06712613e41d57cc3daf7ed17688c1201500af9214b6`.

Each configuration has 82 implementation/reference and 11 consumer translation
units compiled directly, seven coherent C++ archives and eleven executable
links, with exact strict/sanitized flags and macro variants. The author ran no
produced binary or checker. Root has passed the initial ten strict gates,
independent current strict semantics/arithmetic, and ordinary/sanitized JSON
cleanup probes; full matching sanitizer and supplemental normalized-replay
execution are separate pending root gates at this cutoff. BUILD_RESULTS.md
records the exact terminal receipts and limitations.

The strict checkpoint remains byte-for-byte historical. Its ten-command set
does not silently gain the later normalized-replay consumer. That consumer is
separately pinned in both configurations and appears explicitly in the matching
sanitizer checkpoint. All source/header/archive inputs remain held for root's
active guards and the separate independent sanitizer packet.

PACKAGE_SHA256SUMS, generated after this note, covers the complete publication
except itself, with paths relative to this directory. Checkpoints use their own
directory as package-manifest base. Input/compiled-artifact/evidence manifests
use repository-root or explicit absolute paths. Later root receipts can refer
to this immutable preparation without rewriting its cutoff evidence. A future
implementation change requires a new revision and matching build/verification;
it must preserve this packet and both checkpoint histories.
