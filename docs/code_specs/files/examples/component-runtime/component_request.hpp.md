# `examples/component-runtime/component_request.hpp` — block usage map

[Source](../../../../../examples/component-runtime/component_request.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Demonstrate a concrete public workflow and executable invocation using installed/native CROWN interfaces.

Snapshot SHA-256: `89ff50e5e2d11519590ee6bf72e5df47bf3842ca0221e24bd9321bdb19cab0e0`. 137 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [examples](../../../subsystem_contracts.md#examples). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/cli.md](../../../../cli.md), [docs/native_build.md](../../../../native_build.md), [docs/measurement.md](../../../../measurement.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/reoptimization.md](../../../../reoptimization.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../examples/component-runtime/component_request.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Cold transport and observation helpers for the optional B04 applications. · [reviewed contract](#b0001) |
| [B0002 · 22–24](../../../../../examples/component-runtime/component_request.hpp#L22) | Callable definition: inline void require(bool condition, const char* message) | calls std::runtime_error; guard inline void require(bool condition, const char* message) { · [reviewed contract](#b0002) |
| [B0003 · 25–29](../../../../../examples/component-runtime/component_request.hpp#L25) | Callable definition: inline U64 elapsed(Clock::time_point first, Clock::time_point last) | calls count, require; guard require(value &gt;= 0, "component clock regressed");; returns static_cast&lt;U64&gt;(value) · [reviewed contract](#b0003) |
| [B0004 · 30–36](../../../../../examples/component-runtime/component_request.hpp#L30) | Callable definition: inline U64 number(const Json& value, U64 maximum = UINT64_MAX) | calls require, is_number_integer, is_number_unsigned; guard require(value.is_number_integer() && (value.is_number_unsigned() \|\| value.get&lt;std::int64_t&gt;() &gt;= 0),; returns result · [reviewed contract](#b0004) |
| [B0005 · 37–40](../../../../../examples/component-runtime/component_request.hpp#L37) | Type/record definition: struct Event |  · [reviewed contract](#b0005) |
| [B0006 · 41–47](../../../../../examples/component-runtime/component_request.hpp#L41) | Type/record definition: struct Request |  · [reviewed contract](#b0006) |
| [B0007 · 48–50](../../../../../examples/component-runtime/component_request.hpp#L48) | Explanatory comments or spacing. | source comment (unverified): // Admit the complete unit-weight trace once, before query/API timing. This · [reviewed contract](#b0007) |
| [B0008 · 51–101](../../../../../examples/component-runtime/component_request.hpp#L51) | Callable definition: inline Request read_request(int argc, char** argv) | calls require, input, bool, read; guard require(argc == 2, "usage: component_driver REQUEST.json");; returns result; growth insert, push_back, reserve; 3 loop sites; source comment (unverified): // Admit the complete unit-weight trace once, before query/API timing. This · [reviewed contract](#b0008) |
| [B0009 · 102–104](../../../../../examples/component-runtime/component_request.hpp#L102) | Callable definition: inline Json time_value(const Request& request, U64 value) | calls Json; returns request.verify ? Json(nullptr) : Json(value) · [reviewed contract](#b0009) |
| [B0010 · 105–108](../../../../../examples/component-runtime/component_request.hpp#L105) | Callable definition: inline void add_records(U64& total, U64 amount, U64 maximum) | calls require; guard require(amount &lt;= maximum-total, "component output-record limit exceeded"); · [reviewed contract](#b0010) |
| [B0011 · 109–118](../../../../../examples/component-runtime/component_request.hpp#L109) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Legacy formatting writes into this bounded sink inside its genuine API call. · [reviewed contract](#b0011) |
| [B0012 · 119–119](../../../../../examples/component-runtime/component_request.hpp#L119) | Callable definition: TextSink(bool capture, U64 maximum) : capture_(capture), maximum_(maximum) | calls capture_, maximum_ · [reviewed contract](#b0012) |
| [B0013 · 120–120](../../../../../examples/component-runtime/component_request.hpp#L120) | Callable definition: void next_frame() | calls clear · [reviewed contract](#b0013) |
| [B0014 · 121–121](../../../../../examples/component-runtime/component_request.hpp#L121) | Callable definition: \[\[nodiscard\]\] const std::string& frame() const | calls ; returns frame_ · [reviewed contract](#b0014) |
| [B0015 · 122–130](../../../../../examples/component-runtime/component_request.hpp#L122) | Callable definition: protected: std::streamsize xsputn(const char* text, std::streamsize length) override | calls require, append; guard require(length &gt;= 0, "negative component stream write");; returns length; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 131–135](../../../../../examples/component-runtime/component_request.hpp#L131) | Callable definition: int_type overflow(int_type value) override | calls traits_type::eq_int_type, traits_type::eof, traits_type::not_eof, traits_type::to_char_type; returns traits_type::not_eof(value); value · [reviewed contract](#b0016) |
| [B0017 · 136–137](../../../../../examples/component-runtime/component_request.hpp#L136) | Closes surrounding scope/type. | source comment (unverified): // namespace component · [reviewed contract](#b0017) |

## B0001

[Lines 1–21](../../../../../examples/component-runtime/component_request.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:11608e47e1d00dc609d86ef81c71c0ecdb6f738511143bbe6aca1a1d7d1eff86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Introduce the cold JSON transport, monotonic clock and scalar aliases shared by the optional C++ component observers. |
| inputs / outputs | Includes JSON, array/container, file, exception and stream-buffer APIs; opens component and aliases Json, Clock and U64. |
| invariants | This is application observation scaffolding, not a native operator, account grant or paper cost interface. |
| ownership | Declarations retain no query rows or result state; later Request and sink instances own their explicit application data. |
| failure | Missing headers or incompatible standard/library configuration fail compilation; this region installs no runtime handler. |
| cost | Compilation and type declarations only; clock and container work occurs in the following functions. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/legacy_baselines.md](../../../../legacy_baselines.md), [Refactor.md §11.11 B04 and §14.3–14.4](../../../../../Refactor.md) |

## B0002

[Lines 22–24](../../../../../examples/component-runtime/component_request.hpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L24:sha256:c18d23199c28eee4913e655e0b1f39f9ff660e14a4a5be6ecd8e7a519470f993
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop a component application when an explicit transport/observation precondition fails. |
| inputs / outputs | Takes a condition and fixed message; returns on true and throws std::runtime_error on false. |
| invariants | A successful check supplies only its named local precondition; it never certifies query correctness or build provenance. |
| ownership | The condition/message are borrowed for the call; a thrown standard exception owns its message according to the library. |
| failure | False propagates to the application's single CLI catch; no runtime rollback or retry is introduced. |
| cost | One branch on success; exception/message allocation is failure-path work outside native grants. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/legacy_baselines.md](../../../../legacy_baselines.md) |

## B0003

[Lines 25–29](../../../../../examples/component-runtime/component_request.hpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L29:sha256:078552349c9b3f0f827ef9446f76734009a99ea79ee71f257244f5137951143f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one completed steady-clock interval to a nonnegative integer nanosecond observation. |
| inputs / outputs | Receives two Clock time points and returns their duration; a negative interval is rejected. |
| invariants | Both endpoints must describe the same monotonic clock and selected phase; the value is not CPU time or a complexity bound. |
| ownership | Time points and returned scalar are values; no runtime owner is retained. |
| failure | Clock regression or an invalid negative interval raises the local application error. |
| cost | Constant scalar duration conversion/check; the clock sampling cost belongs to surrounding observation work. |
| Design | [docs/measurement.md](../../../../measurement.md) |

## B0004

[Lines 30–36](../../../../../examples/component-runtime/component_request.hpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L36:sha256:9241c5cd40f6057cbcdb419f49633a5a2b9f2fd8b204358af318926869b96551
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an exact nonnegative JSON integer under a caller-selected maximum. |
| inputs / outputs | Accepts a JSON number and optional uint64 maximum; returns U64 after signedness/range checks. |
| invariants | Booleans, floating values and negative signed integers are rejected; unsigned values do not pass through a narrowing signed conversion. |
| ownership | Borrows the JSON node; returns an owning scalar without retaining the input tree. |
| failure | Wrong type/sign/range raises a local application error before the selected driver proceeds. |
| cost | Selected JSON type/access operations and scalar checks; no integer spelling, allocator or whole-request CPU guarantee follows. |
| Design | [docs/measurement.md](../../../../measurement.md), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json) |

## B0005

[Lines 37–40](../../../../../examples/component-runtime/component_request.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L40:sha256:4002cffefcca0c5df8263890eed627de81e7399743995e3d545bcebeb5288eaf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one normalized integer-pair transport command and its declared workload phase. |
| inputs / outputs | Event stores operation/table/phase strings and two signed int64 values. |
| invariants | Operation and unit-set legality are established by read_request; this DTO alone supplies no physical TableId or compiler authority. |
| ownership | The strings and pair are application-owned copies, independent of JSON nodes and native borrowed cells. |
| failure | Ordinary string/vector allocation can fail while preparing the request; the type performs no publication. |
| cost | Fixed scalar fields plus variable string backing per event; the input vector is caller/tool memory outside the query account. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/physical_runtime.md](../../../../physical_runtime.md) |

## B0006

[Lines 41–47](../../../../../examples/component-runtime/component_request.hpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L47:sha256:d618d5db67390ef7cbffed01209a90e190da045fae3e272c8c003a5d519226e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the parsed invocation, admitted trace and observation caps alive across fresh-owner passes. |
| inputs / outputs | Request owns original JSON, Event vector, verify flag, warmup/repetition counts and record/byte caps. |
| invariants | The original document remains metadata/input; verify mode requests observations rather than establishing a correctness verdict. |
| ownership | All fields are application-owned; native runtime account/owner handles are created separately by each driver. |
| failure | Construction/admission failures propagate before owner creation; this DTO has no rollback machinery. |
| cost | Storage scales with request bytes and event count; warmup/report ownership is separate from funded operator memory. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 48–50](../../../../../examples/component-runtime/component_request.hpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L50:sha256:b21bf7bc69e99abaa66f69c04ada485918b73deee3a1857163040644911f7a4b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the phase and lifetime boundary of complete-trace unit-set admission. |
| inputs / outputs | The comment introduces read_request and its temporary validation set. |
| invariants | It asserts a cold prepass, not an update-path membership mirror; operational engines still perform their own admission/maintenance. |
| ownership | The validation set is local to read_request and is destroyed before that function returns its owned Request. |
| failure | The note implements no check itself; actual rejection lives in the following function. |
| cost | No executable work in this region; the following prepass pays set comparisons and request allocations. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/legacy_baselines.md](../../../../legacy_baselines.md) |

## B0008

[Lines 51–101](../../../../../examples/component-runtime/component_request.hpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L101:sha256:dc2f7660cd35b6b4bb6be2cd1434117f8d00c65492789320c335dac5922a4875
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a bounded request and admit a complete valid unit-set trace before any query/API timing. |
| inputs / outputs | Reads the sole pathname, parses schema/version/command/caps/pass counts, copies integer pairs, validates +/− chains by table/pair, and returns Request. |
| invariants | At most 64MiB content, one million admitted events and 100 passes of each kind; measured passes must be positive. Every insert is absent and every delete present in the cold trace model. This is transport admission, not SQL/tree/provenance authority. |
| ownership | The file stream closes by RAII; text/JSON/events are caller-owned. The local ordered validation set is discarded on return; no additional live row ledger enters measurement. |
| failure | Bad reads/JSON/missing fields/type/range/caps/duplicate or absent edits throw before an owner exists. Extra metadata fields are not interpreted as authority. Allocation errors propagate to the single CLI boundary. |
| cost | O(request bytes) reading/parsing plus ordered-set work over the trace, strings and scalar copies. The content cap is checked before appending each chunk; ordinary parser/report allocations are not native-account allocations or a total CPU cap. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/legacy_baselines.md](../../../../legacy_baselines.md), [examples/component-runtime/aggregate.cpp](../../../../../examples/component-runtime/aggregate.cpp), [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp) |

## B0009

[Lines 102–104](../../../../../examples/component-runtime/component_request.hpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L102-L104:sha256:4a2f9a4298e816f52d72bd419910db739113c0fa255f5c10a9daa819389312b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish unmeasured verification timings from real measured nanoseconds. |
| inputs / outputs | Returns JSON null in verify mode, otherwise the supplied U64 timing scalar. |
| invariants | Null means unavailable/unmeasured; it is not a measured zero. The function does not sample a clock. |
| ownership | The returned JSON value is application/report-owned and borrows no runtime state. |
| failure | Ordinary JSON construction may throw; no engine state is changed. |
| cost | Constant selected dispatch/scalar construction, with ordinary JSON implementation costs. |
| Design | [docs/measurement.md](../../../../measurement.md) |

## B0010

[Lines 105–108](../../../../../examples/component-runtime/component_request.hpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L108:sha256:46fa9a9a9d3557047dfaf6017e6a97c4fea05d654b6787e5004b6acb5991b7c7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a cumulative per-pass emitted-record allowance without unsigned wrap. |
| inputs / outputs | Checks an amount against remaining maximum and increments the caller's total. |
| invariants | Caller maintains total&lt;=maximum from an initial zero; acceptance preserves that invariant. It counts observations, not expanded bag multiplicity. |
| ownership | Borrows/mutates one caller-owned counter; retains no tuples or keys. |
| failure | An excess rejects the run after the actual driver stage; no rollback of a completed baseline/native event is promised. |
| cost | Constant checked counter work per counted record/batch. |
| Design | [docs/measurement.md](../../../../measurement.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md) |

## B0011

[Lines 109–118](../../../../../examples/component-runtime/component_request.hpp#L109); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L109-L118:sha256:f93278b74729e69a076d7024eeef76d2188f7dea6777667a6f5fc4b419cb1b2c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the bounded legacy text observer and its application-owned byte/newline counters. |
| inputs / outputs | Opens TextSink with capture/max fields, current-frame string and cumulative byte/record scalars. |
| invariants | Measure mode will count/discard formatted text; verify mode additionally owns one raw event frame. Neither mode replaces the published formatter. |
| ownership | TextSink owns frame capacity and counters; the associated ostream borrows the sink and must die first. |
| failure | This declaration has no handler or live write; writes and capacity failures are defined below. |
| cost | One small stream-buffer object and optional retained maximum-frame capacity, not a query-state row graph. |
| Design | [docs/legacy_baselines.md](../../../../legacy_baselines.md), [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp) |

## B0012

[Lines 119–119](../../../../../examples/component-runtime/component_request.hpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L119-L119:sha256:5399bbe7cc35c8e60e00bbfa9591049e6cc0b7e8f5b550c230a6a86e13d5fb55
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure capture policy and the intrinsic-text byte allowance for one pass. |
| inputs / outputs | Initializes TextSink from a verify/capture flag and maximum bytes. |
| invariants | Counters start at zero; maximum is a cumulative pass cap, not a native grant. |
| ownership | The sink owns its empty string/control state; no output stream or baseline owner is created here. |
| failure | Normal member construction may fail through the standard library; no baseline has been mutated. |
| cost | Constant scalar initialization and empty-string construction. |
| Design | [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp), [docs/legacy_baselines.md](../../../../legacy_baselines.md) |

## B0013

[Lines 120–120](../../../../../examples/component-runtime/component_request.hpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L120-L120:sha256:ca31850eeb07378e6bb162f043f842b4695ca521a29b24aa3655664127687390
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retire the previous raw event frame before observing the next event. |
| inputs / outputs | Clears the owned frame string while preserving pass-wide byte/newline totals. |
| invariants | Previously exported JSON frames already own copies; this operation does not reset the output allowance. |
| ownership | The string may retain its capacity until sink destruction; any prior frame() borrow is invalidated. |
| failure | String clear is a local nonpublication operation; no retry or source-state change occurs. |
| cost | Clear/destruction cost follows the string implementation; allocated maximum-frame capacity can remain retained. |
| Design | [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp) |

## B0014

[Lines 121–121](../../../../../examples/component-runtime/component_request.hpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L121-L121:sha256:3063b0cee2eb1e11e3bd8fdc0562c38c75eec970778dc899e57dc21b03aa7450
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the current captured raw text for immediate report copying. |
| inputs / outputs | Returns const std::string& containing the current event's writes. |
| invariants | The text is exact observed legacy formatting; it is not parsed/group-folded or a correctness flag. |
| ownership | Borrow lasts only until a write, next_frame or sink destruction. Json construction at the caller copies it before the next event. |
| failure | No validation or exception conversion occurs in this accessor. |
| cost | Constant reference access; report copying/escaping is caller work. |
| Design | [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp), [docs/legacy_baselines.md](../../../../legacy_baselines.md) |

## B0015

[Lines 122–130](../../../../../examples/component-runtime/component_request.hpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L122-L130:sha256:82133b0e219d9076a0bbe22ffc9a4fd47d7d6e3ffd2c2843e322636c51b3b509
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count and optionally retain a genuine bulk legacy formatting write. |
| inputs / outputs | Accepts a character slice/streamsize, rejects negative/excess length, appends only in capture mode, counts newlines, and returns accepted length. |
| invariants | bytes never exceeds maximum; records counts actual newline bytes and is bounded by emitted bytes. Data is not normalized or deduplicated. |
| ownership | Input borrows end on return; verify mode copies bytes into the owned frame. Measure mode retains no payload text. |
| failure | A cap/allocation failure propagates through the caller's ostream exception mask; the underlying process may already have changed state. No output transaction or rollback is supplied. |
| cost | Linear scan in emitted characters plus capture copying/allocation when enabled. This sink work remains inside the measured published API/formatting phase. |
| Design | [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp), [docs/measurement.md](../../../../measurement.md), [docs/legacy_baselines.md](../../../../legacy_baselines.md) |

## B0016

[Lines 131–135](../../../../../examples/component-runtime/component_request.hpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L131-L135:sha256:1bb6bae06340cca3725250659aafa12ec67b85a80eff508b7a95e11bdc44a849
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Honor the streambuf single-character/EOF contract through the same byte cap. |
| inputs / outputs | EOF is acknowledged without writing; a real character delegates one byte to xsputn and returns that character. |
| invariants | Single-byte and bulk writes share counters/capture rules; EOF creates no output record. |
| ownership | A local character is synchronously borrowed by xsputn; only the sink may retain its copied value. |
| failure | Delegated capacity/allocation failures propagate; no baseline repair is attempted. |
| cost | Constant local work plus the one-byte sink operation. |
| Design | [examples/component-runtime/legacy_cpp.cpp](../../../../../examples/component-runtime/legacy_cpp.cpp) |

## B0017

[Lines 136–137](../../../../../examples/component-runtime/component_request.hpp#L136); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L136-L137:sha256:fb2e5fdb17c005793177f691878b2737a35ebedf336c13138df631a4c2989b07
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the TextSink type and component helper namespace. |
| inputs / outputs | Terminates declarations introduced above; exports no further callable. |
| invariants | Structural braces preserve scope only and supply no independent runtime guarantee. |
| ownership | No instance is created or destroyed merely by these declaration boundaries. |
| failure | Syntax/scope mistakes fail compilation; there is no failure handler here. |
| cost | No runtime work. |
| Design | [examples/component-runtime/component_request.hpp](../../../../../examples/component-runtime/component_request.hpp) |
