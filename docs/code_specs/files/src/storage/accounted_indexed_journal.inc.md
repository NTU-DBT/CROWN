# `src/storage/accounted_indexed_journal.inc` — block usage map

[Source](../../../../../src/storage/accounted_indexed_journal.inc) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Record/reverse native indexed mutations using the original account/work grant.

Snapshot SHA-256: `6af4489f0bd4128e743f25998fd98f63248bcc0546e8751b49d616456201c349`. 225 lines partitioned into 28 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–3](../../../../../src/storage/accounted_indexed_journal.inc#L1) | declares types or opens a type body. | source comment (unverified): // Included after AccountedIndexedTable::State. All inverse node/link actions · [reviewed contract](#b0001) |
| [B0002 · 4–11](../../../../../src/storage/accounted_indexed_journal.inc#L4) | Type/record definition: struct Key |  · [reviewed contract](#b0002) |
| [B0003 · 12–25](../../../../../src/storage/accounted_indexed_journal.inc#L12) | Type/record definition: struct Undo |  · [reviewed contract](#b0003) |
| [B0004 · 26–26](../../../../../src/storage/accounted_indexed_journal.inc#L26) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 27–34](../../../../../src/storage/accounted_indexed_journal.inc#L27) | Type/record definition: struct Prepared | returns record.get(); bool(record) · [reviewed contract](#b0005) |
| [B0006 · 35–40](../../../../../src/storage/accounted_indexed_journal.inc#L35) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 41–43](../../../../../src/storage/accounted_indexed_journal.inc#L41) | Callable definition: Data(std::shared_ptr&lt;State&gt; state, std::shared_ptr&lt;AccountedIndexedJournalReader&gt; authority) : owner(std::move(state)), report_ow… | calls owner, std::move, report_owner, reader · [reviewed contract](#b0007) |
| [B0008 · 44–50](../../../../../src/storage/accounted_indexed_journal.inc#L44) | Callable definition: ~Data() | calls rollback, lock, size, std::terminate · [reviewed contract](#b0008) |
| [B0009 · 51–56](../../../../../src/storage/accounted_indexed_journal.inc#L51) | Callable definition: State& active() const | calls IndexFailure; returns *owner · [reviewed contract](#b0009) |
| [B0010 · 57–73](../../../../../src/storage/accounted_indexed_journal.inc#L57) | Callable definition: Prepared prepare(bool inserted) | calls active, room, size, max_size; returns result; growth make_accounted_unique · [reviewed contract](#b0010) |
| [B0011 · 74–82](../../../../../src/storage/accounted_indexed_journal.inc#L74) | Callable definition: void publish(Prepared preparation) noexcept | calls capacity, push_back, std::move, swap; growth push_back; 2 loop sites · [reviewed contract](#b0011) |
| [B0012 · 83–93](../../../../../src/storage/accounted_indexed_journal.inc#L83) | Callable definition: void release_keys(Undo& undo) noexcept | calls std::terminate, size, destroy_indexed_node; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 94–107](../../../../../src/storage/accounted_indexed_journal.inc#L94) | Callable definition: void undo_insert(Undo& undo) noexcept | calls unlink_prepaid, first, erase_prepaid, destroy_indexed_node; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 108–124](../../../../../src/storage/accounted_indexed_journal.inc#L108) | Callable definition: void undo_erase(Undo& undo) noexcept | calls revive, classify_indexed_node, link_between_prepaid, size; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 125–127](../../../../../src/storage/accounted_indexed_journal.inc#L125) | Callable definition: void close() noexcept | calls reset · [reviewed contract](#b0015) |
| [B0016 · 128–136](../../../../../src/storage/accounted_indexed_journal.inc#L128) | Callable definition: void rollback() noexcept | calls rbegin, rend, undo_insert, undo_erase; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 137–157](../../../../../src/storage/accounted_indexed_journal.inc#L137) | Callable definition: void commit() noexcept | calls size, destroy_indexed_node, release_keys, get_deleter; 1 loop sites; source comment (unverified): // The shared reader remains active authority for valid committed cursors; · [reviewed contract](#b0017) |
| [B0018 · 158–159](../../../../../src/storage/accounted_indexed_journal.inc#L158) | Closes surrounding scope/type. |  · [reviewed contract](#b0018) |
| [B0019 · 160–160](../../../../../src/storage/accounted_indexed_journal.inc#L160) | Callable definition: AccountedIndexedTable::Journal::Journal(resource::AccountedUnique&lt;Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0019) |
| [B0020 · 161–163](../../../../../src/storage/accounted_indexed_journal.inc#L161) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0020) |
| [B0021 · 164–164](../../../../../src/storage/accounted_indexed_journal.inc#L164) | Callable definition: bool AccountedIndexedTable::Journal::active() const noexcept | calls ; returns data_ && data_-&gt;owner · [reviewed contract](#b0021) |
| [B0022 · 165–165](../../../../../src/storage/accounted_indexed_journal.inc#L165) | Callable definition: std::size_t AccountedIndexedTable::Journal::size() const noexcept | calls size; returns data_ ? data_-&gt;entries.size() : 0 · [reviewed contract](#b0022) |
| [B0023 · 166–169](../../../../../src/storage/accounted_indexed_journal.inc#L166) | Callable definition: AccountedIndexedTable::ChangeView AccountedIndexedTable::Journal::change(std::size_t index) const & | calls size, IndexFailure, get; returns {entry.inserted, entry.handle, entry.pin-&gt;get()} · [reviewed contract](#b0023) |
| [B0024 · 170–170](../../../../../src/storage/accounted_indexed_journal.inc#L170) | Callable definition: void AccountedIndexedTable::Journal::rollback() noexcept | calls rollback · [reviewed contract](#b0024) |
| [B0025 · 171–174](../../../../../src/storage/accounted_indexed_journal.inc#L171) | Callable definition: void AccountedIndexedTable::Journal::commit() noexcept | calls active, commit, get_deleter, set_lifetime · [reviewed contract](#b0025) |
| [B0026 · 175–178](../../../../../src/storage/accounted_indexed_journal.inc#L175) | Callable definition: InsertResult AccountedIndexedTable::Journal::insert(const AccountedTuple& tuple) | calls IndexFailure, active, AccountedIndexedTable::insert_impl, get; returns AccountedIndexedTable::insert_impl(data_-&gt;owner, tuple, *data_-&gt;reader-&gt;work, data_.get()); growth insert · [reviewed contract](#b0026) |
| [B0027 · 179–215](../../../../../src/storage/accounted_indexed_journal.inc#L179) | Callable definition: bool AccountedIndexedTable::Journal::erase(TupleHandle handle) | calls IndexFailure, active, start, row; returns false; true; growth emplace, push_back; 2 loop sites · [reviewed contract](#b0027) |
| [B0028 · 216–225](../../../../../src/storage/accounted_indexed_journal.inc#L216) | Callable definition: AccountedIndexedTable::Journal AccountedIndexedTable::journal(AccountedIndexWork work) | calls IndexFailure, state, unlocked, same_account; returns Journal(std::move(data)); growth make_accounted_shared, make_accounted_unique · [reviewed contract](#b0028) |

## B0001

[Lines 1–3](../../../../../src/storage/accounted_indexed_journal.inc#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AccountedIndexedTable::Journal::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own prepared inverse records and the one exclusive indexed table authority. |
| inputs / outputs | Shared State and reader create empty original-account undo owners and active phase state. |
| invariants | Only one active journal per State; detached rows/members/empty keys stay retained until exact reverse undo or commit. Committed inverse raw pointers are not traversed again. |
| ownership | Strong owner exists only while active; committed change views retain pins/undo buffers and weak reporting ownership without retaining the whole table. |
| failure | Abandoned active Data rolls back through its destructor; no replacement snapshot is needed. |
| cost | One Data/control plus per-change Undo and O(index count) key/neighbor vector; retained history capacity is explicit native memory. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0002

[Lines 4–11](../../../../../src/storage/accounted_indexed_journal.inc#L4); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  struct Key {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture secondary membership and live-key neighbors needed by an inverse. |
| inputs / outputs | Raw key/member pointers and their old bucket/live-list neighbors identify the exact reinsertion positions. |
| invariants | Journal key reference counts protect empty keys while active; reverse undo restores neighbors in valid order. |
| ownership | Inline nonowning pointers inside an account-owned Undo vector; row pin retains tuple payload separately. |
| failure | No independent recovery path; callers finish funding before mutation. |
| cost | Fixed pointer record per secondary index; no tuple/key payload copy. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0003

[Lines 12–25](../../../../../src/storage/accounted_indexed_journal.inc#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  struct Undo {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one insert/delete inverse with stable row identity and pins. |
| inputs / outputs | Direction, handle, previous high-water, row/list pointers, optional arena pin and key records reverse one published change. |
| invariants | Insert rollback restores last_tuple; erase rollback revives the original row allocation/links. Revision is deliberately not restored. |
| ownership | Original-account unique Undo owns its key vector and payload pin; raw node ownership stays with State or detached journal authority. |
| failure | Unpublished preparation releases safely; published entry requires commit/rollback before owner release. |
| cost | Fixed metadata plus O(indices) pointer vector/pin; no full table or child-state mirror. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0004

[Lines 26–26](../../../../../src/storage/accounted_indexed_journal.inc#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L26:sha256:63cea856f2db575126a96d295d32fa8aee5b9a0a97707a90ca6305a2afc09658
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed_journal.inc: imports or aliases \`Owner = resource::AccountedUnique&lt;Undo&gt;\`. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | AccountedUnique retains one owned object and its account-aware deleter. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 27–34](../../../../../src/storage/accounted_indexed_journal.inc#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  struct Prepared {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund an unpublished Undo and optional replacement undo-owner vector. |
| inputs / outputs | Temporary token owns a fresh inverse object and any required entries capacity growth. |
| invariants | Existing entries move only during publish after all funding; token destruction never publishes a change. |
| ownership | Private unique Undo and original-account replacement vector. |
| failure | Preparation failure releases these owners and leaves the old journal vector intact. |
| cost | Fixed token and actual new vector capacity/Undo allocations; no row/key deep copy. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0006

[Lines 35–40](../../../../../src/storage/accounted_indexed_journal.inc#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L40:sha256:0569767575e51708889a1d2d22737c9f16003ab5a2d71a081d6ae8276fc2e61d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed_journal.inc: this range contains member/state declarations Member/state declarations in this range include \`std::shared_ptr&lt;State&gt; owner\`; \`std::weak_ptr&lt;State&gt; report_owner\`; \`std::shared_ptr&lt;AccountedIndexedJournalReader&gt; reader\`; \`bool committed = false\`. |
| inputs / outputs | This span declares/carries these members or local values: \`std::shared_ptr&lt;State&gt; owner\`; \`std::weak_ptr&lt;State&gt; report_owner\`; \`std::shared_ptr&lt;AccountedIndexedJournalReader&gt; reader\`; \`bool committed = false\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | shared_ptr members retain shared state for the handle lifetime. weak_ptr members observe state without retaining it. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0007

[Lines 41–43](../../../../../src/storage/accounted_indexed_journal.inc#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(std::shared_ptr<State> state,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an inactive-to-callers journal implementation with exact authority. |
| inputs / outputs | Strong State plus shared reader initializes weak report owner and empty entries vector. |
| invariants | Table flags are installed only after this complete construction succeeds. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. |
| failure | Funding/construction failure publishes no active table journal. |
| cost | Fixed ownership/empty-container setup. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0008

[Lines 44–50](../../../../../src/storage/accounted_indexed_journal.inc#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ~Data() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rollback abandonment and retire retained-history accounting on final destruction. |
| inputs / outputs | Active Data reverses state; committed Data decrements weakly reachable State retained_history by its entry count. |
| invariants | After close there is no strong table owner. Expired report owner is valid; pins/control buffers release independently. |
| ownership | Destroys native inverses/pins and their original-account buffers. |
| failure | Nonallocating destruction; retained-count underflow is an internal terminate condition. |
| cost | Actual inverse/entry/key/pin destruction, potentially final arena/control release; no new grant. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0009

[Lines 51–56](../../../../../src/storage/accounted_indexed_journal.inc#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  State& active() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate this exact active journal authority before table access. |
| inputs / outputs | Owner, journal_active, active_journal pointer and reader phase must all agree. |
| invariants | A stale/committed/rolled-back token cannot mutate or open new tentative cursors. |
| ownership | Returns borrowed State under the journal strong owner. |
| failure | Raises IndexFailure(invalid_journal). |
| cost | O(1) authority checks; no allocation on success. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0010

[Lines 57–73](../../../../../src/storage/accounted_indexed_journal.inc#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Prepared prepare(bool inserted) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare one inverse record and possible geometric undo-owner capacity growth. |
| inputs / outputs | Insert/delete direction reserves journal/population capacity, retained-history room, work words, Undo object and keys for all indices. |
| invariants | Checks all size/counter limits before mutation. Existing undo entries are not moved until nonthrowing publish. |
| ownership | Original layout account funds native state, nodes, directory capacity, deep values and output owners; there is no replacement query account. The returned token owns every newly allocated preparation. |
| failure | Failure before publication releases prepared owners and preserves logical table state; already spent work is not refunded. |
| cost | Fixed inverse and O(indices) key capacity; occasional O(existing entries) owner-vector growth/move is admitted up front. No hidden result materialization. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0011

[Lines 74–82](../../../../../src/storage/accounted_indexed_journal.inc#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void publish(Prepared preparation) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish an already funded inverse with no allocation. |
| inputs / outputs | Complete preparation with a tuple pin optionally swaps grown owner capacity, increments key journal references and appends the Undo. |
| invariants | Every key reference increment and append capacity was admitted; table mutation and inverse become paired under active journal authority. |
| ownership | Unique Undo ownership transfers into entries; existing tuple pin remains inside it. |
| failure | Noexcept; missing capacity/pin or invalid prepared state terminates. |
| cost | O(indices) key reference increments and possibly O(old entries) pointer-owner moves; no deep tuple copy or new work admission. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0012

[Lines 83–93](../../../../../src/storage/accounted_indexed_journal.inc#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void release_keys(Undo& undo) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drop one active inverse key-retention reference set. |
| inputs / outputs | Each recorded key loses one journal reference; empty unreferenced nonlive keys are destroyed. |
| invariants | References cannot underflow; an empty key scheduled for destruction must already be absent from live-key traversal. |
| ownership | Releases retained key ownership through its embedded allocator; no allocation. |
| failure | Internal impossible reference/list state terminates. |
| cost | O(indices) fixed pointer/count operations plus final key/deep-payload release; cached hooks avoid lookup. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0013

[Lines 94–107](../../../../../src/storage/accounted_indexed_journal.inc#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void undo_insert(Undo& undo) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reverse a published tentative insertion using saved row identity. |
| inputs / outputs | Unlink row/ID, destroy member nodes, retire newly empty keys, erase arena liveness and restore previous last_tuple. |
| invariants | Key references keep required empty nodes until release_keys; reverse order preserves later inverse dependencies. |
| ownership | Tuple pin protects erased payload until entry release; no replacement row allocation. |
| failure | Noexcept prepaid inverse; impossible arena/link state terminates. |
| cost | O(row memberships) direct hook operations and payload releases; no hash/projection/admission or high-water scan. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0014

[Lines 108–124](../../../../../src/storage/accounted_indexed_journal.inc#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void undo_erase(Undo& undo) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore the original deleted row and secondary positions. |
| inputs / outputs | Revive pinned arena allocation, reactivate row/member/key storage and relink saved resident/bucket/live-key neighbors. |
| invariants | Original logical ID, arena allocation and tuple address survive; mutation revision remains invalidating. |
| ownership | Moves detached membership authority back to State using existing allocations. |
| failure | Noexcept under saved-neighbor/reverse-order invariants; internal mismatch terminates. |
| cost | O(indices) direct classifications/list links; no key comparison, payload clone, fresh work or allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0015

[Lines 125–127](../../../../../src/storage/accounted_indexed_journal.inc#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void close() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release exact table journal authority after commit or rollback work. |
| inputs / outputs | Reset active_reader/active_journal/journal_active then release the strong State owner. |
| invariants | All inverse/publication work must have finished before close; retained reader/pins remain separate owners. |
| ownership | Strong table authority is released, not transferred to a history registry. |
| failure | Noexcept valid active-owner contract. |
| cost | Fixed authority resets plus possible final State destruction; final owner release is not merely O(1) cleanup. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0016

[Lines 128–136](../../../../../src/storage/accounted_indexed_journal.inc#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void rollback() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Abort reader authority before reversing every published mutation. |
| inputs / outputs | Active Data marks reader aborted, undoes entries in reverse, releases key references and closes. |
| invariants | Closed Data is a no-op. Logical state/IDs/pins restore while physical directory capacity may remain grown. |
| ownership | Prepared inverse owners fund all recovery; entries are cleared after reversal. |
| failure | Noexcept/prepaid; impossible internal state terminates rather than allocating fallback recovery. |
| cost | O(entries and their memberships/key references), plus native release; no new grant, rehash, payload reconstruction or whole-state copy. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0017

[Lines 137–157](../../../../../src/storage/accounted_indexed_journal.inc#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void commit() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep tentative membership and finalize native inverse retention. |
| inputs / outputs | Publish pending action counts, destroy erased row/member metadata, release key references, classify inverse buffers retained and close. |
| invariants | Mutations already admitted counter sums. Committed inverse raw pointers are never used for rollback again; only retained pins support change views. |
| ownership | History retains Undo/key buffers and tuple pins while strong table authority ends; shared reader still authorizes valid committed cursors. |
| failure | Noexcept/prepaid; no new work grant or allocation. |
| cost | O(entries and their index/key/member release), direct allocation-header classifications and possible final State destruction; no row payload recopy. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0018

[Lines 158–159](../../../../../src/storage/accounted_indexed_journal.inc#L158); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L158-L159:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct AccountedIndexedTable::Journal::Data\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct AccountedIndexedTable::Journal::Data\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct AccountedIndexedTable::Journal::Data\` at its lexical source position in src/storage/accounted_indexed_journal.inc; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct AccountedIndexedTable::Journal::Data\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0019

[Lines 160–160](../../../../../src/storage/accounted_indexed_journal.inc#L160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable::Journal::Journal(resource::
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a completely prepared journal implementation. |
| inputs / outputs | Accounted unique Data moves into the public journal token. |
| invariants | Factory already installed table authority after successful Data construction. |
| ownership | Transfers the sole Data owner without copying inverses. |
| failure | Noexcept. |
| cost | O(1), no allocation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0020

[Lines 161–163](../../../../../src/storage/accounted_indexed_journal.inc#L161); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L161-L163:sha256:02ae7fb00ead63422db4529825d45f06e6938e30e7d5c08c99a2dad5597e2000
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/accounted_indexed_journal.inc; the range contains the state/helper statements shown at its exact source span. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0021

[Lines 164–164](../../../../../src/storage/accounted_indexed_journal.inc#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedIndexedTable::Journal::active() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect whether this token still owns active table authority. |
| inputs / outputs | Returns false for moved-from/closed tokens. |
| invariants | Commit/rollback clear owner; retained change entries can still exist after commit. |
| ownership | Inline token/owner checks only. |
| failure | Noexcept. |
| cost | O(1). |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0022

[Lines 165–165](../../../../../src/storage/accounted_indexed_journal.inc#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t AccountedIndexedTable::Journal::size() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the number of recorded changes. |
| inputs / outputs | Returns entries.size or zero for a moved-from token. |
| invariants | Commit retains records; rollback clears them. |
| ownership | Copies count without exporting a history vector. |
| failure | Noexcept. |
| cost | O(1), unlike reference journal indexed list traversal for change(i). |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0023

[Lines 166–169](../../../../../src/storage/accounted_indexed_journal.inc#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable::ChangeView AccountedIndexedTable::Journal::change(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one retained change record/payload. |
| inputs / outputs | Valid zero-based index returns direction, handle and tuple reference backed by that entry pin. |
| invariants | Change view is local storage history, not a joined-answer delta. Tentative IDs must not be externally published before commit. |
| ownership | Borrowed tuple reference requires journal/pin lifetime; no new retaining copy. |
| failure | Moved token/out-of-range entry raises invalid_journal. |
| cost | O(1) vector indexing and pin access; no payload copy or native work debit. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0024

[Lines 170–170](../../../../../src/storage/accounted_indexed_journal.inc#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedIndexedTable::Journal::rollback() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly close a journal through its prepared inverse protocol. |
| inputs / outputs | Open token rolls back; moved/closed token does nothing. |
| invariants | Same idempotent path as abandoned Data destruction. |
| ownership | Releases active State ownership after exact reverse undo. |
| failure | Noexcept. |
| cost | Actual Data rollback/cleanup costs; wrapper adds only presence check. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0025

[Lines 171–174](../../../../../src/storage/accounted_indexed_journal.inc#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void AccountedIndexedTable::Journal::commit() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finalize an open journal and retain its inspectable change pins. |
| inputs / outputs | Open token commits Data then marks the Data allocation retained; moved/closed token is a no-op. |
| invariants | Change records remain readable until token destruction; this is volatile native commit, not durable storage. |
| ownership | Original account retains history buffers/pins, not whole table authority. |
| failure | Noexcept/nonallocating. |
| cost | Underlying entry/member cleanup plus fixed Data-header classification. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0026

[Lines 175–178](../../../../../src/storage/accounted_indexed_journal.inc#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult AccountedIndexedTable::Journal::insert(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert under this exact active journal and original grant. |
| inputs / outputs | Typed tuple delegates to insert_impl with retained State/allowance/Data authority. |
| invariants | Closed token rejects; duplicate remains a no-op and records no inverse. |
| ownership | Journal owns inverse pin/metadata only after complete insertion preparation. |
| failure | Failure before publication releases prepared owners and preserves logical table state; already spent work is not refunded. |
| cost | Underlying per-index preparation/publication costs; no independent allowance or second insertion implementation. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0027

[Lines 179–215](../../../../../src/storage/accounted_indexed_journal.inc#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool AccountedIndexedTable::Journal::erase(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain and detach one existing row for exact later undo. |
| inputs / outputs | Owner-checked handle uses the reader grant; stale ID returns false, live row produces one retained Undo. |
| invariants | All counters, pin room, vector capacity, key references, link inverses and retirement allowances finish before detach. Original row/member nodes are retained rather than replaced. |
| ownership | Pin holds original tuple; Undo saves raw row/key/member neighbors under key journal references. |
| failure | Failure before publication releases prepared owners and preserves logical table state; already spent work is not refunded. |
| cost | ID lookup plus O(indices and scalar-field admission). Deep payload copy amounts are conservative work allowances; the row/key payloads are retained, not deep-copied. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0028

[Lines 216–225](../../../../../src/storage/accounted_indexed_journal.inc#L216); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedIndexedTable::Journal AccountedIndexedTable::journal(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire one exclusive native table journal with an account-matching owning grant. |
| inputs / outputs | Nonempty AccountedIndexWork funds reader/Data, then installs exact active authority. |
| invariants | No active journal already; work account matches layout account and fixed diagnostics. Composed callers must share this same allowance across all tables. |
| ownership | Original-account reader/Data; State strongly retained only while active. |
| failure | Empty/foreign/busy/work/allocation failure installs no journal flags or active pointer. |
| cost | One fixed start/control-word admission and actual reader/Data allocations, no table/row snapshot. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |
