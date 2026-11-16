# `include/crown/runtime/update_pattern.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/update_pattern.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary.

Snapshot SHA-256: `59fbc33fcf3bd9fac03219e12073bf1b88774aabaed3ef01730ff808c31cfa9a`. 36 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [session](../../../../subsystem_contracts.md#session). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/native-replay.md](../../../../../native-replay.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/runtime/update_pattern.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Admission copies requested rules into the original query account under this · [reviewed contract](#b0001) |
| [B0002 · 9–12](../../../../../../include/crown/runtime/update_pattern.hpp#L9) | Type/record definition: struct UpdatePatternOptions | source comment (unverified): // Admission copies requested rules into the original query account under this · [reviewed contract](#b0002) |
| [B0003 · 13–13](../../../../../../include/crown/runtime/update_pattern.hpp#L13) | Type/record definition: enum class PatternViolationKind |  · [reviewed contract](#b0003) |
| [B0004 · 14–14](../../../../../../include/crown/runtime/update_pattern.hpp#L14) | Explanatory comments or spacing. | source comment (unverified): // Fixed diagnostic, filled before throwing a semantic error. It owns no row. · [reviewed contract](#b0004) |
| [B0005 · 15–20](../../../../../../include/crown/runtime/update_pattern.hpp#L15) | Type/record definition: struct PatternViolation | source comment (unverified): // Fixed diagnostic, filled before throwing a semantic error. It owns no row. · [reviewed contract](#b0005) |
| [B0006 · 21–21](../../../../../../include/crown/runtime/update_pattern.hpp#L21) | Type/record definition: enum class PatternHistory |  · [reviewed contract](#b0006) |
| [B0007 · 22–22](../../../../../../include/crown/runtime/update_pattern.hpp#L22) | Type/record definition: enum class PatternInsertionPolicy |  · [reviewed contract](#b0007) |
| [B0008 · 23–26](../../../../../../include/crown/runtime/update_pattern.hpp#L23) | Explanatory comments or spacing. | source comment (unverified): // Ordinary committed diagnostic, not structural proof or a CPU/delay theorem. · [reviewed contract](#b0008) |
| [B0009 · 27–35](../../../../../../include/crown/runtime/update_pattern.hpp#L27) | Type/record definition: struct UpdatePatternStatus | source comment (unverified): // Ordinary committed diagnostic, not structural proof or a CPU/delay theorem. · [reviewed contract](#b0009) |
| [B0010 · 36–36](../../../../../../include/crown/runtime/update_pattern.hpp#L36) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0010) |

## B0001

[Lines 1–8](../../../../../../include/crown/runtime/update_pattern.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:e55531cf38ce64614672734e9c5e8213db818020cebea2e2f3d3376e7c7110b9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide dependencies and namespace scope for the runtime pattern value types. |
| inputs / outputs | No callable input or output; the include supplies the source-bound IR declaration and optional support. |
| invariants | This block only enables later declarations; the P4 update-lifetime model does not become a runtime proof through inclusion. |
| ownership | Includes, namespace scope and comments create no runtime owner. |
| failure | No runtime failure path; ordinary compilation requires the declared IR API. |
| cost | No runtime work; compile-time dependency processing only. |
| Design | [include/crown/ir/update_pattern.hpp](../../../../../../include/crown/ir/update_pattern.hpp), [docs/update_patterns.md](../../../../../update_patterns.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 9–12](../../../../../../include/crown/runtime/update_pattern.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L12:sha256:debc643b0845a89283a5bff569f5fdce14876a86691259f88ca5bcfa8cdc332c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry an opt-in source-bound declaration and its finite capture limits into session creation. |
| inputs / outputs | SessionOptions.update_patterns supplies this value to QuerySession::Impl::capture_patterns; that caller matches the compiled source, checks FIFO tables, and returns a declaration copy for the run context. |
| invariants | The declaration is a requested assumption, not observed compliance. FIFO scopes are accepted only for supported window-managed tables with known origins; P4 premises do not follow from construction. |
| ownership | The handle retains its immutable declaration owner; session capture copies the declaration into the compiled program account under the remaining limits. |
| failure | Declaring or copying this option value validates nothing and allocates no rule vector. Session admission can reject invalid/foreign/unsupported declarations, metadata limits or receiving allocation. |
| cost | Fixed option/immutable-handle copy. Actual admission separately performs O(R) source/rule validation and receiving copy under finite limits; this value type scans no history. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [include/crown/ir/update_pattern.hpp](../../../../../../include/crown/ir/update_pattern.hpp), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0003

[Lines 13–13](../../../../../../include/crown/runtime/update_pattern.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L13:sha256:3ff2bb38c7b27b27adb118e7bada532f29ad24974c3a4e06177a80461b30362a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the three fixed kinds of rejected update-pattern transitions. |
| inputs / outputs | Session and window monitors produce erase_command, physical_erase, or fifo_scope; the version-2 checkpoint codec writes the kind as one byte. |
| invariants | Current declaration order gives wire values 0, 1, and 2. Kind selects local diagnostic context only; it carries no P4 proof authority. |
| ownership | An enum value has no dynamic owner. |
| failure | No runtime failure path; invalid wire values are rejected by the codec. |
| cost | No runtime work beyond reading or writing one enum byte at the codec boundary. |
| Design | [src/runtime/update_pattern_detail.hpp](../../../../../../src/runtime/update_pattern_detail.hpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [src/recovery/session_pattern_wire.hpp](../../../../../../src/recovery/session_pattern_wire.hpp), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0004

[Lines 14–14](../../../../../../include/crown/runtime/update_pattern.hpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L14:sha256:0118d0aa7c3e60fef972931a68e97f6e72a75bf913fa0705f6467d0f104e761c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the fixed-field diagnostic contract for PatternViolation. |
| inputs / outputs | No runtime input or output; this comment describes the following value type. |
| invariants | The comment is documentation only. It does not establish P4 premises or change the caller error path. |
| ownership | A comment owns no runtime data; the following type stores fixed metadata only. |
| failure | No runtime failure path; executable error behavior is specified by PatternViolation and its callers. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/update_pattern.hpp](../../../../../../include/crown/runtime/update_pattern.hpp), [src/runtime/update_pattern_detail.hpp](../../../../../../src/runtime/update_pattern_detail.hpp), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0005

[Lines 15–20](../../../../../../include/crown/runtime/update_pattern.hpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L20:sha256:a934c8c7f1626ef8b17f16a92be825470a1e5ae5619fb33667f9d0dea4b8506f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the fixed diagnostic for one rejected pattern transition. |
| inputs / outputs | The caller records kind, table, command sequence, and label before raising the semantic update-pattern error. |
| invariants | A stream erase uses label zero; window physical-erase and FIFO diagnostics use a positive label. A violation describes the rejected next transition, not proof that earlier history obeyed P4. |
| ownership | Fields are fixed scalars with no row payload or container owner. |
| failure | Assigning the record does not throw; the higher-level Error owns text and its construction may allocate. |
| cost | Fixed field assignment and equality comparison; no rule scan is performed by the type. |
| Design | [src/runtime/update_pattern_detail.hpp](../../../../../../src/runtime/update_pattern_detail.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../../src/runtime/window.cpp), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0006

[Lines 21–21](../../../../../../include/crown/runtime/update_pattern.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L21:sha256:fd4a9ac35414b46a73498b9dffaf3a376632392d85fe045947419e7a4561d34e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Label whether status came from this session or a restored checkpoint. |
| inputs / outputs | Session status construction selects current_session or restored_checkpoint. |
| invariants | Restored history explicitly relies on trusted checkpoint provenance; this tag does not turn the old prefix into newly monitored P4 compliance. |
| ownership | The enum is a value tag with no dynamic owner. |
| failure | No runtime failure path. |
| cost | No runtime work beyond storing or copying one tag. |
| Design | [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0007

[Lines 22–22](../../../../../../include/crown/runtime/update_pattern.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:74114db38169cbf1fae06f1d787dae9d9d5c7d1d6665b6ef9e3c6585233a0de7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the insertion policy reported with a pattern status. |
| inputs / outputs | Session status reports reject_erase_commands for non-window input and reject_lifetime_termination for window input. |
| invariants | This status label describes the active monitor mode; it is not a separate guarantee profile or P4 theorem. |
| ownership | The enum is a value tag with no dynamic owner. |
| failure | No runtime failure path. |
| cost | No runtime work beyond storing or copying one tag. |
| Design | [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0008

[Lines 23–26](../../../../../../include/crown/runtime/update_pattern.hpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L26:sha256:ce13f56ad0fe7a7a813af59ffaebff917179d5f752d8383f2eb954b21126c98e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scope UpdatePatternStatus as a committed diagnostic rather than proof authority. |
| inputs / outputs | No runtime input or output; the comment describes the status fields that follow. |
| invariants | The restored-prefix assumption is explicit. P4 is paper context for the modeled property, not evidence supplied by this comment. |
| ownership | The comment owns no data. |
| failure | No runtime failure path; failures come from status construction or session admission. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/update_pattern.hpp](../../../../../../include/crown/runtime/update_pattern.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0009

[Lines 27–35](../../../../../../include/crown/runtime/update_pattern.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L35:sha256:3c36f7fe56f314ffb0dd6589eb1fcdbaa179ab3e7ccdf295f3ab50354ac94202
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the current declaration, its origin, monitored progress, source identity, and optional violation. |
| inputs / outputs | QuerySession::update_pattern_status returns this value; SessionStatus may include it when a declaration is active. |
| invariants | monitored_sequence and completed_command_sequence describe the reported session boundary. history distinguishes a new run from restored history; neither status nor declaration certifies unmonitored prefix history or a public delay bound. |
| ownership | Declaration copies retain the existing immutable funded owner; counters, hash, enums, and optional violation are fixed metadata, with no row graph. |
| failure | The value itself has no formatted error path; session creation/restore performs binding and may fail before a status is returned. |
| cost | Fixed field copying, a 64-byte digest copy, and declaration-handle ownership work; it does not scan runtime rows. Last-owner release can destroy O(R) declaration metadata. |
| Design | [include/crown/runtime/session.hpp](../../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [include/crown/ir/update_pattern.hpp](../../../../../../include/crown/ir/update_pattern.hpp), [docs/update_patterns.md](../../../../../update_patterns.md), [docs/checkpoints.md](../../../../../checkpoints.md) |

## B0010

[Lines 36–36](../../../../../../include/crown/runtime/update_pattern.hpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L36:sha256:024a31d07f0690bcfeef2cd00cf111a56223bd48741eae7b548b6bc9143d9111
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the runtime namespace after the value declarations. |
| inputs / outputs | No runtime input or output. |
| invariants | This delimiter changes scope only; it makes no paper, monitor, or persistence claim. |
| ownership | No object ownership is introduced. |
| failure | No explicit runtime failure path. |
| cost | No algorithmic runtime cost. |
| Design | [include/crown/runtime/update_pattern.hpp](../../../../../../include/crown/runtime/update_pattern.hpp), [docs/update_patterns.md](../../../../../update_patterns.md) |
