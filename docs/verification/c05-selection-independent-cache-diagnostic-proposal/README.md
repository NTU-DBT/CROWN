# C05 independent cache rejection diagnostic

The original root strict run passed the seven public groups, then the cache
consumer exited 1 with `C05 did not publish a complete pure result`. The three
later consumers did not run. The immutable receipt is
`build/verification/c05-independent-strict-root-attempt-1.json`, FILE
`8a7955ed460232db3b826df1da743092330afa0440cc66bb355cfa38bd6892d3`.
Its source guards remained stable. This packet diagnoses that preserved failure;
it is not a corrected acceptance suite.

The source is an exact copy of the original cache consumer plus diagnostic
output. `diagnostic-only.diff` shows every change. All original API operations,
numeric expectations, predicates, success requirements and failure behavior
remain intact. Messages are emitted before or after selection API calls, outside
their accounting/timing interval. The added `std::source_location` reports the
call site without constructing a string. This is not an allocation-count probe.

Each call reports scenario, sequential call number, loop field, caller line,
stop/stage/resource, optional component stop (`-1` means absent), reason bits,
whether a result was published and additive usage. Enum values are the exact
zero-based declarations in the pinned public headers. In particular,
`Stop::lowering_failure` is 13, `Stage::lowering` is 8 and `Resource::none` is 0.
`Stop::complete` is 0 and `Stage::publication` is 10. The physical-options loop
prints an explicit namespace marker before its six fields.

Source inspection provides a hypothesis, not an execution conclusion. The
original physical-options field 0 appends `-namespace` to the arithmetic policy
and still requires a complete result. Native `src/io/identity.cpp` accepts only
`exact-nonnull-v1`, while native lowering calls that identity path. C05 catches
the resulting native error as a lowering failure. The diagnostic preserves the
old success requirement so root can identify the actual first rejected call.
No assertion is relaxed and no implementation change is proposed by this packet.

The root recipe compiles one fresh consumer with C++23, `-O3 -UNDEBUG`, all six
strict warning flags and `-MD`, then links the same held production strict3
selection archives and native Release archives. It adds no testing macro,
testing-runtime archive or report dependency. The original source packet,
strict correction packet, unsealed sanitizer metadata and all native sources
remain untouched. The author has not compiled, linked or executed the probe.
