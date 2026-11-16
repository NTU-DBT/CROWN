# Independent C05 sanitizer preparation

This is a frozen metadata/recipe packet. It references two unchanged consumer
sources and the shared fixture in
`docs/verification/c05-selection-independent-tests-proposal/`, plus two corrected
consumer copies in the separately frozen strict revision and the separately
corrected cache consumer. It neither copies nor edits them. The original frozen package FILE is
`50e80347560e4fb18a85d9229b252fd181ca2bfb44a16510af812045c9cf5c0b`.
Its authoring-1 lineage and literal expectations remain unchanged. The strict
revision package FILE is
`fab25305c707509657be11f9b389602c5983d96df50a7e3eb7833b6e79421c23`.
That revision adds one missing diagnostic initializer brace and non-inline
allocation/deallocation boundaries; it changes no value or assertion.
The cache correction package FILE is
`0c9a484df64c82a5a4dbb5fd0bdd32479ccdbfb832814d4d00ec347403165c2a`.
It preserves the unsupported arithmetic mutation as a rejection/atomicity
check, checks all retained entries and a supported retry, and keeps five
supported option variants' distinct-key assertions. Root confirmed the native
arithmetic contract before accepting that separate correction.

The original 255-row input manifest is historical. It includes an unused producer
normalized-exception test that root has approved for a quote-only correction.
This packet treats the old manifest as a FILE identity only and never checks its
old rows against live files. It does not invoke the old ROOT_BUILD recipe, whose
historical input check would be inappropriate after that correction.

The new input scope binds the actual selected independent sources, current
public/private APIs and implementation units, native execution freeze and needed
native headers/sources, active patched JSON, compiler/toolchain identities and
root's matching complete sanitizer archive receipt. Unused producer test sources
and mutable native status guides are deliberately outside that compilation scope.
Their approved publication transitions do not authorize changes to code or ABI.

Root's three strict execution receipts together pass all five selected
consumers and 22 groups. The original cache failure and confirming diagnostic
are preserved. Root's matching sanitizer implementation receipt records 19
fresh TUs, three archives and ten successful links with stable inputs. This
packet selects only its two production C05 archives and matching native
sanitizer dependencies. Independent sanitizer compilation/execution remains
pending; no result is inferred from ordinary success or producer compilation.

[Source scope](SOURCE_SCOPE.md), [preserved coverage and limits](COVERAGE.md),
[root reproduction](ROOT_REPRODUCTION.md), [provenance](PROVENANCE.md) and
[remaining gates](PENDING.md) describe the frozen scope.
`CONSUMER_SOURCE_SHA256SUMS` identifies the six selected immutable consumer/header
files. `INPUT_SHA256SUMS` and `LINK_INPUT_SHA256SUMS` bind the matching closure.

All compilation, linking, checking and execution remains root-owned. The author
only reads, hashes and authors source/metadata. Strict independent findings must
be resolved in a separately preserved source correction, never by mutating the
frozen consumer packets or silently weakening their literal/authority assertions.
