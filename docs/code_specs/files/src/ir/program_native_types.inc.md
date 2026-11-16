# `src/ir/program_native_types.inc` — block usage map

[Source](../../../../../src/ir/program_native_types.inc) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Import/export native compiler metadata using the receiving account.

Snapshot SHA-256: `952dbdb3a9f2a1c59a3f326b714acead27b7c9f981905e13fd1c67252ceed486`. 43 lines partitioned into 4 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_identity.md](../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–36](../../../../../src/ir/program_native_types.inc#L1) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Native-to-native copies use the same checked aggregate field mapping. · [reviewed contract](#b0001) |
| [B0002 · 37–41](../../../../../src/ir/program_native_types.inc#L37) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0002) |
| [B0003 · 42–42](../../../../../src/ir/program_native_types.inc#L42) | Type/record definition: template&lt;class T&gt; struct Type&lt;Span&lt;T&gt;&gt; |  · [reviewed contract](#b0003) |
| [B0004 · 43–43](../../../../../src/ir/program_native_types.inc#L43) | Type/record definition: template&lt;class T&gt; struct Type&lt;Set&lt;T&gt;&gt; |  · [reviewed contract](#b0004) |

## B0001

[Lines 1–36](../../../../../src/ir/program_native_types.inc#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<> struct Type<::crown::program::Column>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native Column as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::Column and aggregate arity 5; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::UniqueConstraint>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native UniqueConstraint as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::UniqueConstraint and aggregate arity 3; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::ForeignKeyConstraint>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native ForeignKeyConstraint as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::ForeignKeyConstraint and aggregate arity 5; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::DistinctEstimate>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native DistinctEstimate as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::DistinctEstimate and aggregate arity 2; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::TableStatistics>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native TableStatistics as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::TableStatistics and aggregate arity 2; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::KeyHint>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native KeyHint as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::KeyHint and aggregate arity 2; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::Table>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native Table as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::Table and aggregate arity 6; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::Catalog>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native Catalog as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::Catalog and aggregate arity 2; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::Variable>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native Variable as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::Variable and aggregate arity 2; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::Atom>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native Atom as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::Atom and aggregate arity 3; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::Output>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native Output as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::Output and aggregate arity 2; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::Query>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native Query as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::Query and aggregate arity 4; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::TreeNode>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native TreeNode as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::TreeNode and aggregate arity 6; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::FreeConnexTree>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native FreeConnexTree as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::FreeConnexTree and aggregate arity 4; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::PlanViolation>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native PlanViolation as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::PlanViolation and aggregate arity 6; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::ValidationReport>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native ValidationReport as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::ValidationReport and aggregate arity 6; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::BoundLiteral>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native BoundLiteral as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::BoundLiteral and aggregate arity 1; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::BoundOperation>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native BoundOperation as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::BoundOperation and aggregate arity 2; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::BoundExpression>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native BoundExpression as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::BoundExpression and aggregate arity 3; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::BoundOccurrence>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native BoundOccurrence as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::BoundOccurrence and aggregate arity 5; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::BoundOutput>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native BoundOutput as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::BoundOutput and aggregate arity 2; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::BoundSql>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native BoundSql as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::BoundSql and aggregate arity 13; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::ColumnConstant>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native ColumnConstant as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::ColumnConstant and aggregate arity 2; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::OccurrenceAdapter>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native OccurrenceAdapter as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::OccurrenceAdapter and aggregate arity 9; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::ConstantOutput>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native ConstantOutput as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::ConstantOutput and aggregate arity 1; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::NormalizedOutput>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native NormalizedOutput as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::NormalizedOutput and aggregate arity 3; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::NormalizedSql>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native NormalizedSql as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::NormalizedSql and aggregate arity 11; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::CachePolicy>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native CachePolicy as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::CachePolicy and aggregate arity 4; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::PhysicalOptions>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native PhysicalOptions as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::PhysicalOptions and aggregate arity 3; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::GuaranteeProfile>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native GuaranteeProfile as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::GuaranteeProfile and aggregate arity 15; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::QueryIdentity>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native QueryIdentity as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::QueryIdentity and aggregate arity 8; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::PhysicalRelation>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native PhysicalRelation as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::PhysicalRelation and aggregate arity 5; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::IndexRequirement>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native IndexRequirement as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::IndexRequirement and aggregate arity 4; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::InputConstant>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native InputConstant as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::InputConstant and aggregate arity 2; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

## B0002

[Lines 37–41](../../../../../src/ir/program_native_types.inc#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<> struct Type<::crown::program::PhysicalInput>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native PhysicalInput as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::PhysicalInput and aggregate arity 8; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::PhysicalNode>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native PhysicalNode as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::PhysicalNode and aggregate arity 15; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::PhysicalEdge>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native PhysicalEdge as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::PhysicalEdge and aggregate arity 5; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::EnumerationStep>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native EnumerationStep as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::EnumerationStep and aggregate arity 6; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

```text
template<> struct Type<::crown::program::EnumerationProgram>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep native EnumerationProgram as its result type during checked metadata refreezing. |
| inputs / outputs | Declares Result=::crown::program::EnumerationProgram and aggregate arity 4; Builder uses this mapping when freezing fields. |
| invariants | Arity must match the actual aggregate definition. This trait alone performs no source/schema/proof admission. |
| ownership | Compile-time type/count only; actual Builder owns new native arena storage and any retained layout tokens. |
| failure | Incorrect aggregate arity/type use fails compilation; allocation and native validation failures belong to Builder calls. |
| cost | No runtime action or allocation at specialization; field visits, text/span copies and layout imports are separate Builder work. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

## B0003

[Lines 42–42](../../../../../src/ir/program_native_types.inc#L42); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> struct Type<Span<T>>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve the native Span wrapper while recursively mapping its element type. |
| inputs / outputs | Result is Span&lt;typename Type&lt;T&gt;::Result&gt;. |
| invariants | Mapping does not retain backing or validate sorting/uniqueness; Set invariants remain caller/Builder responsibilities. |
| ownership | Compile-time alias; actual returned descriptors borrow the owning metadata arena. |
| failure | Invalid element mapping fails instantiation; no runtime handler. |
| cost | No runtime traversal or allocation in this declaration. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |

## B0004

[Lines 43–43](../../../../../src/ir/program_native_types.inc#L43); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> struct Type<Set<T>>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve the native Set wrapper while recursively mapping its element type. |
| inputs / outputs | Result is Set&lt;typename Type&lt;T&gt;::Result&gt;. |
| invariants | Mapping does not retain backing or validate sorting/uniqueness; Set invariants remain caller/Builder responsibilities. |
| ownership | Compile-time alias; actual returned descriptors borrow the owning metadata arena. |
| failure | Invalid element mapping fails instantiation; no runtime handler. |
| cost | No runtime traversal or allocation in this declaration. |
| Design | [src/ir/program_native_types.inc](../../../../../src/ir/program_native_types.inc), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program_model.hpp](../../../../../include/crown/ir/program_model.hpp), [tests/unit/native_program_test.cpp](../../../../../tests/unit/native_program_test.cpp) |
