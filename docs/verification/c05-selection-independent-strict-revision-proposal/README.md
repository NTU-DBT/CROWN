# Independent C05 strict compile revision

This new packet corrects exactly two source-level compile defects reported by
root's closed strict-1 build, session5162. The original independent package
`50e80347560e4fb18a85d9229b252fd181ca2bfb44a16510af812045c9cf5c0b`, its
authoring-1 lineage and every strict-1 output remain unchanged. No runtime result
was inferred from that failed build.

The byte fixture was missing one closing initializer brace in its diagnostic
NormalizedSql adapter record. The revised copy adds that brace. The focused
allocation fixture's sized delete was inlined to `std::free`, triggering GNU's
optimized mismatched-new-delete diagnostic. The revised copy routes all twelve
delete forms through one non-inlined, nonallocating `release` function and marks
all replacement new/delete boundaries non-inline. Allocation counters, measured
intervals, persistent failure positions, scalar values, byte expectations and
every assertion are unchanged. No warning is disabled; `-O3` and all six strict
warning flags remain mandatory. Exact source differences are preserved here.

Only these two consumers are recompiled/relinked. Root's successful public,
cache and resource consumers retain their original source/object/dependency/
binary identities. The same five pure implementation objects and production
bridge from root strict-3 are reused, with the same native Release libraries.
No C05 implementation, API, native file, producer test or old evidence is edited.

The old 255-row input manifest is now historical because the producer's unused
normalized-exception fixture received an authorized SQL quoting correction.
This packet pins that old manifest FILE, never checks its historical rows, and
uses a new relevant input inventory. It excludes producer test sources and
mutable native status guides. Current native execution freeze/API/implementation/
compiler/archive inputs, all five actual independent source inputs, the failed
diagnostic FILEs and reused artifacts are explicitly pinned instead.

The author only read, hashed and authored files. No compiler, linker, checker,
Python, project executable, build system or symbol command was run by the author.
Root must build the two corrected consumers, then execute all five using the
mixed-source but single-ABI source map in `ROOT_REPRODUCTION.md`. This is source
readiness only. Sanitizer, full sweeps, native C05 integration and broader card
acceptance remain separate gates; literal scores/caps and authority rules are
not weakened by this revision.
