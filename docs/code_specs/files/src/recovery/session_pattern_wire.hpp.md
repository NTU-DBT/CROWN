# `src/recovery/session_pattern_wire.hpp` — block usage map

[Source](../../../../../src/recovery/session_pattern_wire.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `91837a585c539da15fc56dfce9e4dd27e02f701553046ca5f5efe2cb0655ec45`. 240 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../src/recovery/session_pattern_wire.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Usage: version 2 callers place this section immediately after the optional · [reviewed contract](#b0001) |
| [B0002 · 22–24](../../../../../src/recovery/session_pattern_wire.hpp#L22) | Callable definition: inline void require(bool value, ImageFault fault = ImageFault::binding) | calls binary_detail::require; guard inline void require(bool value, ImageFault fault = ImageFault::binding) { · [reviewed contract](#b0002) |
| [B0003 · 25–32](../../../../../src/recovery/session_pattern_wire.hpp#L25) | Callable definition: inline std::uint64_t section_size(std::uint64_t rules, bool has_violation) | calls require, max; guard require(rules &lt;= (std::numeric_limits&lt;std::uint64_t&gt;::max() - fixed - extra) / rule_bytes,; returns fixed + rules * rule_bytes + extra; source comment (unverified): // hash, counts, origins and presence byte · [reviewed contract](#b0003) |
| [B0004 · 33–38](../../../../../src/recovery/session_pattern_wire.hpp#L33) | Callable definition: inline std::uint64_t scratch_size(std::uint64_t rules) | calls require, max; guard require(rules &lt;= std::numeric_limits&lt;std::uint64_t&gt;::max() / cell_bytes &&; returns rules * cell_bytes · [reviewed contract](#b0004) |
| [B0005 · 39–47](../../../../../src/recovery/session_pattern_wire.hpp#L39) | Callable definition: inline std::uint64_t parse_work(std::uint64_t rules, bool has_violation) | calls require, max; guard require(rules &lt;= (std::numeric_limits&lt;std::uint64_t&gt;::max() - fixed) / passes,; returns fixed + rules * passes; source comment (unverified): // Hash validation, fixed metadata, one rule pass, plus at most one bounded · [reviewed contract](#b0005) |
| [B0006 · 48–53](../../../../../src/recovery/session_pattern_wire.hpp#L48) | Callable definition: inline std::uint64_t parse_payload(std::uint64_t rules, bool has_violation) | calls section_size, scratch_size, require, max; guard require(scratch &lt;= std::numeric_limits&lt;std::uint64_t&gt;::max() - wire, ImageFault::limit);; returns wire + scratch · [reviewed contract](#b0006) |
| [B0007 · 54–59](../../../../../src/recovery/session_pattern_wire.hpp#L54) | Callable definition: inline void check_parse_caps(const patterns::Limits& limits, std::uint64_t rules, bool has_violation) | calls require, parse_work, parse_payload; guard require(rules &lt;= limits.cells, ImageFault::limit); · [reviewed contract](#b0007) |
| [B0008 · 60–74](../../../../../src/recovery/session_pattern_wire.hpp#L60) | Callable definition: template&lt;class Input&gt; inline std::optional&lt;patterns::TableRule&gt; wire_rule(Input& in, std::size_t start, std::size_t count, std::u… | calls at; returns patterns::TableRule{TableId{id}, insertion != 0, fifo}; std::nullopt; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 75–80](../../../../../src/recovery/session_pattern_wire.hpp#L75) | Callable definition: inline const patterns::TableRule* find_rule(std::span&lt;const patterns::TableRule&gt; rules, std::uint64_t table) noexcept | calls std::lower_bound, begin, end; returns rule.table.value &lt; id; found != rules.end() && found-&gt;table.value == table ? &*found : nullptr · [reviewed contract](#b0009) |
| [B0010 · 81–105](../../../../../src/recovery/session_pattern_wire.hpp#L81) | Callable definition: inline void check_violation_context(runtime::SessionInputKind input_kind, bool input_failed, std::uint64_t accepted, const std::o… | calls require, max; guard require(input_failed); · [reviewed contract](#b0010) |
| [B0011 · 106–113](../../../../../src/recovery/session_pattern_wire.hpp#L106) | Callable definition: inline std::uint64_t accepted_command_sequence(const runtime::SessionCheckpoint& state) | calls std::visit, constexpr; returns state.window-&gt;progress.completed_command_sequence; std::visit(\[\](const auto& source) -&gt; std::uint64… · [reviewed contract](#b0011) |
| [B0012 · 114–117](../../../../../src/recovery/session_pattern_wire.hpp#L114) | Closes surrounding scope/type. | source comment (unverified): // namespace pattern_wire_detail · [reviewed contract](#b0012) |
| [B0013 · 118–157](../../../../../src/recovery/session_pattern_wire.hpp#L118) | Callable definition: template&lt;class Output&gt; void write_pattern_extension(Output& out, const runtime::SessionCheckpoint& state) | calls require, has_value, rules, source_tables; guard require(state.version == runtime::SessionCheckpoint::current_version, ImageFault::version);; 1 loop sites; source comment (unverified): // Version 2 only. Writes canonical declaration rules followed by checkpoint · [reviewed contract](#b0013) |
| [B0014 · 158–161](../../../../../src/recovery/session_pattern_wire.hpp#L158) | Explanatory comments or spacing. | source comment (unverified): // Version 2 only. Inspection validates structure without allocating; decode · [reviewed contract](#b0014) |
| [B0015 · 162–239](../../../../../src/recovery/session_pattern_wire.hpp#L162) | Callable definition: template&lt;class Input&gt; void read_pattern_extension(Input& in, const SessionImageManifest& manifest) | calls require, hash, size, max; guard require(manifest.state_version == runtime::SessionCheckpoint::current_version, ImageFault::version);; growth emplace, push_back, reserve; 1 loop sites; source comment (unverified): // Version 2 only. Inspection validates structure without allocating; decode · [reviewed contract](#b0015) |
| [B0016 · 240–240](../../../../../src/recovery/session_pattern_wire.hpp#L240) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::detail · [reviewed contract](#b0016) |

## B0001

[Lines 1–21](../../../../../src/recovery/session_pattern_wire.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:dc3da2ffa23582d5242a32777f5a0ca820ccb19c05e1cbb551fdcbe5afd30db6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the private version-2 pattern section codec and its bound dependencies. |
| inputs / outputs | No runtime input or output; the block includes binary/session types and opens private recovery namespaces. |
| invariants | The comment fixes placement after window state and before runtime-image length; version 1 does not call the codec. Pattern checks record assumptions and do not establish P4 truth or CPU/delay bounds. |
| ownership | Includes and namespace declarations create no runtime owner. |
| failure | No runtime failure path; compilation requires the binary and session codec types. |
| cost | No runtime work; compile-time dependencies only. |
| Design | [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0002

[Lines 22–24](../../../../../src/recovery/session_pattern_wire.hpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L24:sha256:9538263595a7f9f8a63936d694d1e6a3648958fca03fe9f260cff77bc842af81
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route a false codec condition through the existing fixed image failure. |
| inputs / outputs | Private codec helpers pass a boolean and optional ImageFault to binary_detail::require. |
| invariants | A passing check has no effect; a failed check does not establish or translate runtime policy. |
| ownership | No owner or DTO is retained. |
| failure | Throws ImageFailure with the selected fixed fault; no message formatting or catch is added. |
| cost | Constant condition and branch work. |
| Design | [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0003

[Lines 25–32](../../../../../src/recovery/session_pattern_wire.hpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L32:sha256:d6450748fd7bef4a7d73cc389b16c74c5b56c643a3f17bff00c879eb9c20c7ae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the encoded section length with overflow checks. |
| inputs / outputs | Rule count and violation presence produce 97 fixed bytes, 17 bytes per rule, and 25 optional violation bytes. |
| invariants | Length arithmetic matches the version-2 layout; it does not validate source identity or prove historical compliance. |
| ownership | Only scalar arithmetic is retained. |
| failure | Rejects overflowing counts with ImageFailure(limit). |
| cost | Constant-time checked arithmetic. |
| Design | [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0004

[Lines 33–38](../../../../../src/recovery/session_pattern_wire.hpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L38:sha256:98a19e49d5ff6e0ecdb5dee6c97212d621fbaf20a477bf3424acd075d2530188
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute decoder scratch bytes for the rule count. |
| inputs / outputs | A rule count is multiplied by sizeof(TableRule) after uint64 and native-size overflow checks. |
| invariants | The estimate bounds only funded scratch capacity; it says nothing about RSS or P4 cost. |
| ownership | No allocation occurs during estimation. |
| failure | Rejects impossible products with ImageFailure(limit). |
| cost | Constant-time checked arithmetic. |
| Design | [src/recovery/session_pattern_wire.hpp](../../../../../src/recovery/session_pattern_wire.hpp), [include/crown/ir/update_pattern.hpp](../../../../../include/crown/ir/update_pattern.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0005

[Lines 39–47](../../../../../src/recovery/session_pattern_wire.hpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L47:sha256:1de01b7427167cc3f8d2e5aa3db5571a693a1ee5ddd62a2b182ced3f0f5d37bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Estimate finite envelope traversal work for fixed fields and one or two rule passes. |
| inputs / outputs | Rule count and violation presence produce 72 fixed units plus one unit per rule pass. |
| invariants | This is a codec work-cap estimate, separate from Declaration::import work and not a wall-clock or public-delay theorem. |
| ownership | Only scalar arithmetic is retained. |
| failure | Rejects an overflowing estimate with ImageFailure(work). |
| cost | Constant-time checked arithmetic. |
| Design | [src/recovery/session_pattern_wire.hpp](../../../../../src/recovery/session_pattern_wire.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0006

[Lines 48–53](../../../../../src/recovery/session_pattern_wire.hpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L53:sha256:74c5b516429e6e033fda285b1516566c5add83355a566474dbddb1bdb5c1244c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine wire payload and possible rule scratch into one checked parse payload estimate. |
| inputs / outputs | Rule count and violation presence determine serialized bytes plus sizeof(TableRule) scratch bytes. |
| invariants | The estimate is a finite parser/scratch cap, independent from the immutable declaration import grant and the account’s simultaneous physical limit. |
| ownership | No buffer or vector is created. |
| failure | Rejects arithmetic overflow with ImageFailure(limit). |
| cost | Constant-time checked arithmetic. |
| Design | [src/recovery/session_pattern_wire.hpp](../../../../../src/recovery/session_pattern_wire.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0007

[Lines 54–59](../../../../../src/recovery/session_pattern_wire.hpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L59:sha256:7d8923f5575197e851d8181beea06a65d502ac4447809023e2fb38d1cb0a2d09
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply rule-cell, parser-work, and parser-payload caps before serialization or scratch allocation. |
| inputs / outputs | patterns::Limits and the rule/violation counts yield ImageFailure if any parse grant is exceeded. |
| invariants | The same envelope caps constrain writer and reader; Declaration::import applies its own construction limits later. These checks do not confer paper proof authority. |
| ownership | No allocation occurs in the cap check. |
| failure | Uses ImageFailure(limit/work) for codec limits. |
| cost | Constant-time comparisons after checked estimates. |
| Design | [src/recovery/session_pattern_wire.hpp](../../../../../src/recovery/session_pattern_wire.hpp), [include/crown/ir/update_pattern.hpp](../../../../../include/crown/ir/update_pattern.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0008

[Lines 60–74](../../../../../src/recovery/session_pattern_wire.hpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L60-L74:sha256:add482809c91cf68e4be6f62325db074f005831d4c2633b01d0be84054fa36f9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the diagnostic table in already-validated sorted wire rules. |
| inputs / outputs | The input adapter, rule-section offset/count, and table ID yield an optional fixed TableRule. |
| invariants | Canonical increasing IDs permit early stop. Input::at charges eight-byte reads; the bool byte was validated during the first pass. This checks local diagnostic context only. |
| ownership | Uses borrowed input bytes and a stack optional; it creates no vector. |
| failure | Input::at can raise ImageFailure for work or malformed bounds; the helper catches nothing. |
| cost | O(R) worst-case table reads for R rules, with each u64 read charged through Input. |
| Design | [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0009

[Lines 75–80](../../../../../src/recovery/session_pattern_wire.hpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L80:sha256:064b689d126f9cede6f01a255d8e2bb6a8292af1109e0626e2224b7a3b60df61
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find a violation table in a live immutable declaration. |
| inputs / outputs | A sorted rule span and table ID return a borrowed pointer or null for writer-side context validation. |
| invariants | Declaration construction guarantees canonical rules; finding a rule does not validate the live program binding or P4 history. |
| ownership | The pointer borrows the declaration span; no ownership is added. |
| failure | No explicit failure path for a valid span. |
| cost | O(log R) comparisons; no allocation. |
| Design | [include/crown/ir/update_pattern.hpp](../../../../../include/crown/ir/update_pattern.hpp), [src/recovery/session_pattern_wire.hpp](../../../../../src/recovery/session_pattern_wire.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0010

[Lines 81–105](../../../../../src/recovery/session_pattern_wire.hpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L105:sha256:f1735af08998f68205796b1bcf3a0d8a16e41612a75deeb9489ca8f7d90abed4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a serialized violation is consistent with the failed input boundary and its declaration rule. |
| inputs / outputs | Writer/reader supply input kind, input_failed, accepted command, optional violation, and matching rule. |
| invariants | A violation requires input_failed and accepted+1 without overflow; erase_command is non-window/insertion-only/label-zero; window physical_erase is insertion-only/positive-label; window fifo_scope has a positive scope/positive label. This validates codec context, not P4 proof premises. |
| ownership | Uses a borrowed rule pointer and fixed optional diagnostic. |
| failure | Rejects inconsistent context with ImageFailure(binding). |
| cost | Constant checks after the bounded rule lookup. |
| Design | [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0011

[Lines 106–113](../../../../../src/recovery/session_pattern_wire.hpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L113:sha256:893e77a155820b4ac0b03962724421353be9c954045678c3d35348cf5953443e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the accepted command sequence used to validate checkpoint origins. |
| inputs / outputs | Window checkpoints use completed_command_sequence; other source variants use their accepted progress sequence. |
| invariants | The helper selects saved sequence metadata only; restore separately validates source/window consistency and program binding. |
| ownership | Borrows the checkpoint variant during dispatch and returns one scalar. |
| failure | Valid checkpoint variants require no handler or translation here. |
| cost | Constant variant dispatch. |
| Design | [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0012

[Lines 114–117](../../../../../src/recovery/session_pattern_wire.hpp#L114); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L114-L117:sha256:273a37ddf0de7d0b891eb2a0b71435b35b05dc08fb99da42b13b7d064906817f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private helper namespace and state the writer’s version-2 scope. |
| inputs / outputs | No runtime input or output; the following template is the version-2 writer. |
| invariants | The comment describes the format boundary, not an independent runtime guarantee or P4 proof. |
| ownership | No runtime owner is introduced. |
| failure | No runtime failure path. |
| cost | No runtime cost. |
| Design | [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0013

[Lines 118–157](../../../../../src/recovery/session_pattern_wire.hpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L118-L157:sha256:065ebd0f0948d28c7cbc3c0d00744e68b2417e765d253be9af0d90ea39f672d6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a declared session pattern into the version-2 extension. |
| inputs / outputs | The session-image writer supplies an Output adapter and SessionCheckpoint after optional window bytes and before runtime-image length. |
| invariants | Requires version 2 and one declaration; admits count/work/payload caps before content lookups; checks origin bounds and violation rule/context; writes hash, table count, canonical rules, origins, and optional fixed violation. Program/source binding remains restore admission. |
| ownership | Reads an immutable Declaration handle and fixed checkpoint metadata; Output owns the encoded bytes on materialization. |
| failure | Malformed state/limits use ImageFailure; Output may fail under its existing account/budget. No new catch layer is added. |
| cost | O(R) rule serialization plus O(log R) violation rule lookup when present. The parent session writer reserves the exact funded output capacity after sizing; this helper writes into that storage without a separate section vector. |
| Design | [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0014

[Lines 158–161](../../../../../src/recovery/session_pattern_wire.hpp#L158); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L158-L161:sha256:97a88c636334930c347ef305bd3d7d0f226f99004d423b54e83ea38c63f2f737
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the reader’s version-2 inspection and materialization distinction. |
| inputs / outputs | No runtime input or output; the comment scopes the following template. |
| invariants | Inspection validates without heap allocation; decode binds funded scratch only when a result exists. The text grants no CPU-time or P4 guarantee. |
| ownership | The comment creates no owner. |
| failure | No runtime failure path in this comment block. |
| cost | No runtime cost. |
| Design | [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0015

[Lines 162–239](../../../../../src/recovery/session_pattern_wire.hpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L162-L239:sha256:c175a8746aafd86a5a10e639db053cd145b5fb552fd838b5fd3307a89629c726
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect or materialize the version-2 pattern section against a validated session manifest. |
| inputs / outputs | Reader and manifest provide version, input kind, failure state, accepted/committed sequences, pattern limits, account, and nullable decode result. |
| invariants | Validates lowerhex source hash, native/cap-safe counts, exact section bounds, sorted unique table IDs below source_tables, origins within committed/accepted progress, and violation kind/rule/next-command context. Inspection has no result and allocates no scratch. Decode binds an ImageVector allocator only with a result, then imports the declaration; source-to-program binding remains restore admission and checkpoint history remains trusted provenance. |
| ownership | Inspection borrows input only. Decode scratch and imported immutable declaration use the receiving MemoryAccount simultaneously; no ordinary Record/vector mirror is built. |
| failure | Malformed wire and parser limits use ImageFailure. Declaration::import may propagate its fixed patterns::Failure only during materialization; account allocation failures retain their own type. No catch/retry layer is added. |
| cost | O(R) validation plus a bounded violation-rule scan; decode then performs declaration canonicalization/import under its separate finite grant. The caps do not promise CPU time, RSS, or end-to-end update delay. |
| Design | [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [include/crown/ir/update_pattern.hpp](../../../../../include/crown/ir/update_pattern.hpp), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0016

[Lines 240–240](../../../../../src/recovery/session_pattern_wire.hpp#L240); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L240-L240:sha256:acdf1b5fc75d5c18b842bb7fb52e994294982fe0260b6a9937115ce51c7d9072
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recovery detail namespace after the extension templates. |
| inputs / outputs | No runtime input or output. |
| invariants | This delimiter adds no version rule, provenance, or paper claim. |
| ownership | No object ownership is introduced. |
| failure | No explicit runtime failure path. |
| cost | No algorithmic runtime cost. |
| Design | [src/recovery/session_pattern_wire.hpp](../../../../../src/recovery/session_pattern_wire.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |
