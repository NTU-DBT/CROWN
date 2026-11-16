# Input boundaries

REVIEWED_SOURCE_SHA256SUMS identifies the nine C05 public/private implementation
files reviewed completely: two public headers, one private header, five pure
selection translation units, and one runtime bridge translation unit.

INPUT_SHA256SUMS contains 108 fresh direct FILE hashes for the reviewed files,
supporting current native contracts/implementations, the held C05 binding and
accounting specifications, frozen oracle/fixture lineage, and designated root
terminal evidence. Input paths are explicit in input-paths.txt. The before and
after fresh manifests must match exactly. This is source-review provenance,
not a complete compiler dependency or archive closure claim.

Historical package/checkpoint/source manifests included in that list are FILE
identities only. In particular, the original independent INPUT_SHA256SUMS with
255 entries is not opened as an authority for current file bytes, and none of
its entries is revalidated. Fresh selected source pins are independently listed
because those are actual reviewed inputs. The old cache fixture and failed
brace/noinline sources remain preserved; only the accepted selected source
lineage is described as passing.

No historical C01/C02 source seal entries are reopened. Current native files
read for delegated contracts are pinned directly in this new review. The
ranking execution freeze is a FILE input, not permission to rerun old audits.
Status-only README/native_build/ranking prose is excluded. No mutable root
progress file, live output, compiler executable, temporary archive, or new
registration-draft file is required by this source-only review.

Package and source manifests use repository-relative paths. The package
manifest omits only itself; source-files.sha256 omits itself and the package
manifest. ROOT_REVIEW.md is a root-only integrity recipe and does not build or
execute a project program.
