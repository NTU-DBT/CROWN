# `tests/unit/sql_rows_descriptor_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_rows_descriptor_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `b0a8a69c2d33911b34c8109a845b4d5a253c1d6415a039e369f99780d68bffd8`. 137 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 17–21](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L17) | Callable definition: Catalog schema() | calls push_back, std::string; returns value; growth push_back · [reviewed contract](#b0002) |
| [B0003 · 22–28](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L22) | Callable definition: frontend::SqlRowsProgram bind(bool retain=true) | calls std::string, frontend::bind_sql_rows, schema, assert; guard assert(std::holds_alternative&lt;frontend::SqlRowsProgram&gt;(result));return std::get&lt;frontend::SqlRowsP…; returns std::get&lt;frontend::SqlRowsProgram&gt;(std::move(result)) · [reviewed contract](#b0003) |
| [B0004 · 29–32](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L29) | Callable definition: FreeConnexTree tree(const frontend::SqlRowsProgram& program) | calls export_core, planner::minimum_tree, assert; guard assert(chosen.tree && chosen.certificate_verified);return *chosen.tree;; returns *chosen.tree · [reviewed contract](#b0004) |
| [B0005 · 33–33](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L33) | Callable definition: void integer(std::string& out,std::uint64_t value) | calls push_back; growth push_back; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 34–34](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L34) | Callable definition: std::string bytes(const std::vector&lt;std::uint8_t&gt;& value) | calls data, size; returns {reinterpret_cast&lt;const char*&gt;(value.data()),value.size()} · [reviewed contract](#b0006) |
| [B0007 · 35–35](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L35) | Explanatory comments or spacing. | source comment (unverified): // Independent protected framing supports checksum-valid semantic/CBOR forgeries. · [reviewed contract](#b0007) |
| [B0008 · 36–41](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L36) | Callable definition: std::string envelope(std::string_view binding,std::string_view recipe) | calls integer, size, result, sha256_fixed; returns result+body; source comment (unverified): // Independent protected framing supports checksum-valid semantic/CBOR forgeries. · [reviewed contract](#b0008) |
| [B0009 · 42–44](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L42) | Callable definition: template&lt;class Action&gt; void rejected(Action action) | calls action, assert; guard bool failed=false;try{action();}catch(const recovery::ImageFailure&){failed=true;}assert(failed); · [reviewed contract](#b0009) |
| [B0010 · 45–61](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L45) | Callable definition: void cbor_and_frame() | calls envelope, std::string_view, deny, rr::inspect_descriptor; guard {s04_alloc::Scope deny(0);inspected=rr::inspect_descriptor(valid);assert(s04_alloc::calls==0);}; 3 loop sites · [reviewed contract](#b0010) |
| [B0011 · 62–109](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L62) | Callable definition: void genuine_round_trip(bool indexed) | calls bind, s04_runtime::options, reset, resource::MemoryAccount::create; guard assert(restored.descriptor.bytes()==original.descriptor.bytes());; 1 loop sites; source comment (unverified): // Output policy is part of descriptor identity without changing native shape. · [reviewed contract](#b0011) |
| [B0012 · 110–119](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L110) | Callable definition: void binding_opt_in() | calls bind, tree, assert, binding_image; guard assert(ordinary.binding_image().empty() && !retained.binding_image().empty()); · [reviewed contract](#b0012) |
| [B0013 · 120–131](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L120) | Callable definition: void receiving_caps() | calls bind, tree, resource::MemoryAccount::create, rr::admit_into; guard assert(account.statistics().current.allocations==1);; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 132–132](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L132) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0014) |
| [B0015 · 133–137](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L133) | Callable definition: int main() | calls cbor_and_frame, genuine_round_trip, binding_opt_in, receiving_caps; returns 1; 1 loop sites · [reviewed contract](#b0015) |

## B0001

[Lines 1–16](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:07fbee14b514f4d1ccc0af298ecd106192d40bef8ce23f809c7b185b796dfb56
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare finite descriptor-test dependencies, aliases and memory cap. |
| inputs / outputs | Include descriptor/hash/planner and test storage/allocation/assertion helpers; define local Json/Cell/rr aliases and 64MiB fixture cap. |
| invariants | Declarations are test setup only; no assertion receipt or runtime action is produced. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp) |

## B0002

[Lines 17–21](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L21:sha256:12f3c64a217eb4cc7738f09d7fc9723db58790d8b33802c651f425a4fc9a5728
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the concrete typed physical schema used by this independent finite assertion family. |
| inputs / outputs | No arguments; returns the concrete Catalog tables/columns/constraints/hints written in this fixture. |
| invariants | Returned metadata is editable; no catalog validator is called here. |
| ownership | The returned ordinary vectors/strings own fixture metadata; no receiving account is used. |
| failure | Ordinary fixture allocation failures propagate. |
| cost | Construct the listed finite metadata and name/hint bytes; ordinary allocations occur. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp) |

## B0003

[Lines 22–28](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L28:sha256:9c3e2ea91c73b3b82dd017062d03e410eeffb3034402edc6c411d71b15a28b05
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require genuine original nonaggregate SQL factory admission for the test query. |
| inputs / outputs | Retain flag (default true) -&gt; actual two-parameter fixture SqlRowsProgram; options set retain_binding_image=retain before bind_sql_rows. |
| invariants | Asserts admitted fixture SQL/catalog/typed parameter values. Both retention choices use the same inputs and source_sha256; equality is checked separately by binding_opt_in. |
| ownership | Factory program owns immutable metadata through its account; fixture strings/catalog are ordinary caller values. |
| failure | A diagnostic fails assert; parser/allocation exceptions propagate to main. |
| cost | Actual cold SQL parsing/binding/normalization and metadata allocation. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp) |

## B0004

[Lines 29–32](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L32:sha256:2bfed7109f8862b1d4945612d95ff593d450a93e74285016de0e89a9b8a5bb91
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ask the exact planner for this fixture and assert a returned certificate-verified tree. |
| inputs / outputs | A genuine fixture program exports its core; planner::minimum_tree supplies the returned FreeConnexTree. |
| invariants | Asserts the tree/status or certificate flag explicitly present in this body; this helper does not independently replay a certificate. |
| ownership | Core/tree DTOs own ordinary metadata; the immutable program is borrowed. |
| failure | Failed fixture assertions or planner/resource exceptions stop the test. |
| cost | Cold core export and actual finite exact search; may allocate and is not a per-update operation. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0005

[Lines 33–33](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L33:sha256:b2fb41aa83f9f95785071d90881c94c12730fcd2a85c2d920768428bf42c447d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently append exact little-endian words for expected wire bytes. |
| inputs / outputs | Append one uint64_t argument to the supplied ordinary string as exactly8 little-endian bytes. |
| invariants | No width parameter or input validation exists in this helper. |
| ownership | Mutates caller string; actual growth uses ordinary allocation. |
| failure | String allocation failures propagate. |
| cost | Fixed8-byte loop and possible ordinary string growth; no receiving/native work. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp) |

## B0006

[Lines 34–34](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L34:sha256:03c83636dbc5085e07724f494ebaa628cb910c9f5e0f4a22e7115d117d85b0e1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy cold CBOR bytes into an ordinary test string. |
| inputs / outputs | A const uint8 vector becomes a same-length std::string copy. |
| invariants | No parsing, wire validation or native admission occurs. |
| ownership | The returned string owns its copied bytes. |
| failure | Ordinary string allocation failures propagate. |
| cost | O(vector bytes) copy with an ordinary allocation. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp) |

## B0007

[Lines 35–35](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L35:sha256:3ff1a9c3f701798847c36c5256bc97018ca6821f0f283f8cc175fad2a13a7259
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent block boundary. |
| inputs / outputs | Comment/spacing only. |
| invariants | Text is not an executed check or proof. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp) |

## B0008

[Lines 36–41](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L36-L41:sha256:6a38307d2e0c3b91e0b115c02fa1100fcc8717452bb081cd3f0200c88865fea9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently construct protected family framing and both checksums for goldens/hostile complete frames. |
| inputs / outputs | Borrowed binding and recipe string_views -&gt; complete ordinary CROWNRD2 hostile/expected frame string. |
| invariants | Independent layout writes both section extents and protected length/body/prefix fields; section content semantics are not validated. SHA primitive is the existing shared implementation. |
| ownership | Input views stay live through call; local body and returned complete frame own their copies. |
| failure | Ordinary string allocations propagate. |
| cost | Copy/append both CBOR sections and framing, hash body/prefix; no program/binder/runtime/native call. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp) |

## B0009

[Lines 42–44](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L44:sha256:7363eaa4615067276b5902688ffd70f74c98eb1d6bc241cc5a34a2a20fd9ca0a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the fixed image rejection carrier for this deliberate invalid input. |
| inputs / outputs | Invoke the supplied Action; assert that it throws ImageFailure. |
| invariants | Only the asserted exception occurrence is established; the action’s semantic state is checked by its caller. |
| ownership | The helper owns no runtime/output data. |
| failure | A missing expected exception fails assert; exceptions outside the caught type propagate. |
| cost | One action call and fixed exception/assert logic, plus the action’s own costs. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp) |

## B0010

[Lines 45–61](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L61:sha256:3803c825293a4773729705a0f573659cca4d62fb6cc18d5ec24387784a922174
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the independently framed minimal CBOR maps; assert allocation-free inspection, truncation/bit corruption, listed complete hostile CBOR and exact/one-under limits. |
| inputs / outputs | No arguments -&gt; void after protected CBOR/frame and exact-limit assertion loops. |
| invariants | This is a finite test helper/assertion body, not an execution receipt or proof for other inputs. |
| ownership | Fixture DTOs/expected bytes/maps use ordinary test storage; actual programs/runtimes/codecs use the explicitly created accounts and local owners. |
| failure | The exact catches/assertions in this body check expected refusals; all unhandled failures reach main. No production catch or recovery action is introduced. |
| cost | Construct finite ordinary expected/hostile CBOR frame strings, inspect under allocation denial, all truncation/bit controls, seven complete hostile CBORs and exact/one-under caps. No SQL bind, native factory/update or cursor. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp) |

## B0011

[Lines 62–109](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L109:sha256:c8096fb175317bb6ae6e3f96d83ffbc5c9354ea581b7ef2159b675ab946641f5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert actual two-parameter/opaque-hint rebind, normal/output/native/provenance equality, changed-policy identity, exact/zero cold-work behavior and checksum-valid provenance/native forgeries. |
| inputs / outputs | Indexed backend flag -&gt; void after genuine typed-parameter descriptor round-trip/policy/provenance assertions. |
| invariants | This is a finite test helper/assertion body, not an execution receipt or proof for other inputs. |
| ownership | Fixture DTOs/expected bytes/maps use ordinary test storage; actual programs/runtimes/codecs use the explicitly created accounts and local owners. |
| failure | The exact catches/assertions in this body check expected refusals; all unhandled failures reach main. No production catch or recovery action is introduced. |
| cost | Cold fixture compile/exact trees, two genuine admissions, repeated successful/refused rebinds and two prepared-output updates/commits; ordinary CBOR/DOM forgeries plus real receiver metadata/runtime/frame storage. No result cursor or full result snapshot. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp) |

## B0012

[Lines 110–119](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L110-L119:sha256:8794d6336de906967f6e8d963dc7934c7c6a594bb814bb9253a4ab6ecb3452b8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove Descriptor admission requires optional retained metadata without changing the SQL source identity. |
| inputs / outputs | No arguments. Bind the same typed-parameter SQL/catalog fixture with retention false/true; attempt genuine Descriptor admission with unretained program. |
| invariants | Asserts empty/retained image distinction, equal source_sha256, ImageFailure(binding) and unchanged receiving current statistics. Lower tree is chosen before the denial measurement. |
| ownership | Both genuine compiler handles and chosen tree stay live; account starts with its controller and owns no returned Descriptor/runtime after refusal. |
| failure | Local catch accepts only ImageFailure(binding); missing/different refusal fails assert or reaches main. No production error framework. |
| cost | Two finite cold compiles, exact fixture tree search and one early admission denial; no runtime/descriptor receiving allocation from the denied call. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp), [include/crown/frontend/sql_rows.hpp](../../../../../include/crown/frontend/sql_rows.hpp), [src/recovery/sql_rows_descriptor.cpp](../../../../../src/recovery/sql_rows_descriptor.cpp) |

## B0013

[Lines 120–131](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L120-L131:sha256:ea65649bf1300b09c4d31877a50f6d9fc69d3b5368b21024b5ae90df8b1ef728
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure this constructor’s receiving peak and assert exact-byte pass/one-byte-under refusal with current allocations returned to the receiver controller. |
| inputs / outputs | No arguments -&gt; void after measured receiving-peak exact/one-byte-under assertions. |
| invariants | This is a finite test helper/assertion body, not an execution receipt or proof for other inputs. |
| ownership | Fixture DTOs/expected bytes/maps use ordinary test storage; actual programs/runtimes/codecs use the explicitly created accounts and local owners. |
| failure | The exact catches/assertions in this body check expected refusals; all unhandled failures reach main. No production catch or recovery action is introduced. |
| cost | Cold fixture compile/tree, one peak-measuring admission, then exact-byte success and one-byte-under refused admission. Account checks/controller cleanup included; no update/output decode/result cursor. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp) |

## B0014

[Lines 132–132](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L132); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L132-L132:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the stated namespace/type scope. |
| inputs / outputs | No runtime input or output. |
| invariants | No new checks or state transitions. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp) |

## B0015

[Lines 133–137](../../../../../tests/unit/sql_rows_descriptor_test.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L137:sha256:ca1d30d50e7453be26bff0ff11fdfdab874de7fd930870f6f9ba7aba3ce80ebd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run CBOR, two-backend descriptor round-trip, opt-in and receiving-cap assertion families. |
| inputs / outputs | No arguments; invokes exactly the assertion families listed here and returns0, or1 for an unexpected std::exception. |
| invariants | Passing this body establishes only those finite assertions when run with asserts enabled. |
| ownership | Local test fixtures unwind normally; the harness owns stdout/stderr. |
| failure | Expected helper catches are local; main prints unexpected exceptions and returns failure. |
| cost | Sum of called finite tests and report output; not a benchmark or production operation. |
| Design | [tests/unit/sql_rows_descriptor_test.cpp](../../../../../tests/unit/sql_rows_descriptor_test.cpp) |
