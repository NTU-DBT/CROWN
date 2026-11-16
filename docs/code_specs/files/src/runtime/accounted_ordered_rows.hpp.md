# `src/runtime/accounted_ordered_rows.hpp` — block usage map

[Source](../../../../../src/runtime/accounted_ordered_rows.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Own ordered row-set/map nodes with exact allocation ownership and nonallocating extraction/reinsertion.

Snapshot SHA-256: `f8e3249dc146d14f559662d0176c6ebb8840499ec0d015601f755bfe89b5fd93`. 334 lines partitioned into 95 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [delta](../../../subsystem_contracts.md#delta). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/delta_transition_spec.md](../../../../delta_transition_spec.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/anchored_delta.md](../../../../anchored_delta.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../src/runtime/accounted_ordered_rows.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Stable extracted nodes support ordered Delta/inspection state. Node/key · [reviewed contract](#b0001) |
| [B0002 · 24–31](../../../../../src/runtime/accounted_ordered_rows.hpp#L24) | Type/record definition: struct Node |  · [reviewed contract](#b0002) |
| [B0003 · 32–40](../../../../../src/runtime/accounted_ordered_rows.hpp#L32) | declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 41–42](../../../../../src/runtime/accounted_ordered_rows.hpp#L41) | Callable definition: template&lt;bool Other&gt; requires(Constant && !Other) Iterator(const Iterator&lt;Other&gt;& other) noexcept:node_(other.node_) | calls node_ · [reviewed contract](#b0004) |
| [B0005 · 43–43](../../../../../src/runtime/accounted_ordered_rows.hpp#L43) | Callable definition: reference operator*() const noexcept | returns node_-&gt;entry · [reviewed contract](#b0005) |
| [B0006 · 44–44](../../../../../src/runtime/accounted_ordered_rows.hpp#L44) | Callable definition: pointer operator-&gt;() const noexcept | returns &node_-&gt;entry · [reviewed contract](#b0006) |
| [B0007 · 45–49](../../../../../src/runtime/accounted_ordered_rows.hpp#L45) | Callable definition: Iterator& operator++() noexcept | calls get; returns *this; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 50–50](../../../../../src/runtime/accounted_ordered_rows.hpp#L50) | Callable definition: Iterator operator++(int) noexcept | returns old · [reviewed contract](#b0008) |
| [B0009 · 51–54](../../../../../src/runtime/accounted_ordered_rows.hpp#L51) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |
| [B0010 · 55–55](../../../../../src/runtime/accounted_ordered_rows.hpp#L55) | Callable definition: explicit Iterator(Node* node) noexcept:node_(node) | calls node_ · [reviewed contract](#b0010) |
| [B0011 · 56–59](../../../../../src/runtime/accounted_ordered_rows.hpp#L56) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |
| [B0012 · 60–75](../../../../../src/runtime/accounted_ordered_rows.hpp#L60) | Type/record definition: class node_type | returns !node_; bool(node_) · [reviewed contract](#b0012) |
| [B0013 · 76–76](../../../../../src/runtime/accounted_ordered_rows.hpp#L76) | Type/record definition: struct insert_return_type |  · [reviewed contract](#b0013) |
| [B0014 · 77–77](../../../../../src/runtime/accounted_ordered_rows.hpp#L77) | Explanatory comments or spacing. |  |
| [B0015 · 78–82](../../../../../src/runtime/accounted_ordered_rows.hpp#L78) | Callable definition: AccountedRowMap(const resource::MemoryAccount& account,resource::MemoryPurpose purpose, resource::MemoryAttribution attribution,r… | calls account_, purpose_, attribution_, lifetime_ · [reviewed contract](#b0015) |
| [B0016 · 83–84](../../../../../src/runtime/accounted_ordered_rows.hpp#L83) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0016) |
| [B0017 · 85–87](../../../../../src/runtime/accounted_ordered_rows.hpp#L85) | Callable definition: AccountedRowMap(AccountedRowMap&& other) noexcept :account_(other.account_),purpose_(other.purpose_),attribution_(other.attributi… | calls account_, purpose_, attribution_, lifetime_ · [reviewed contract](#b0017) |
| [B0018 · 88–88](../../../../../src/runtime/accounted_ordered_rows.hpp#L88) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0018) |
| [B0019 · 89–89](../../../../../src/runtime/accounted_ordered_rows.hpp#L89) | Callable definition: ~AccountedRowMap() | calls clear · [reviewed contract](#b0019) |
| [B0020 · 90–90](../../../../../src/runtime/accounted_ordered_rows.hpp#L90) | Callable definition: const resource::MemoryAccount& account() const noexcept | calls ; returns account_ · [reviewed contract](#b0020) |
| [B0021 · 91–91](../../../../../src/runtime/accounted_ordered_rows.hpp#L91) | Callable definition: resource::MemoryPurpose purpose() const noexcept | calls ; returns purpose_ · [reviewed contract](#b0021) |
| [B0022 · 92–92](../../../../../src/runtime/accounted_ordered_rows.hpp#L92) | Callable definition: resource::MemoryAttribution attribution() const noexcept | calls ; returns attribution_ · [reviewed contract](#b0022) |
| [B0023 · 93–93](../../../../../src/runtime/accounted_ordered_rows.hpp#L93) | Callable definition: bool empty() const noexcept | calls ; returns size_==0 · [reviewed contract](#b0023) |
| [B0024 · 94–94](../../../../../src/runtime/accounted_ordered_rows.hpp#L94) | Callable definition: std::size_t size() const noexcept | calls ; returns size_ · [reviewed contract](#b0024) |
| [B0025 · 95–95](../../../../../src/runtime/accounted_ordered_rows.hpp#L95) | Callable definition: iterator begin() noexcept | calls iterator, minimum, get; returns iterator(minimum(root_.get())) · [reviewed contract](#b0025) |
| [B0026 · 96–96](../../../../../src/runtime/accounted_ordered_rows.hpp#L96) | Callable definition: iterator end() noexcept | calls ; returns iterator{} · [reviewed contract](#b0026) |
| [B0027 · 97–97](../../../../../src/runtime/accounted_ordered_rows.hpp#L97) | Callable definition: const_iterator begin() const noexcept | calls const_iterator, minimum, get; returns const_iterator(minimum(root_.get())) · [reviewed contract](#b0027) |
| [B0028 · 98–98](../../../../../src/runtime/accounted_ordered_rows.hpp#L98) | Callable definition: const_iterator end() const noexcept | calls ; returns const_iterator{} · [reviewed contract](#b0028) |
| [B0029 · 99–99](../../../../../src/runtime/accounted_ordered_rows.hpp#L99) | Callable definition: template&lt;class Probe&gt; iterator find(const Probe& probe) | calls iterator, find_node; returns iterator(find_node(probe)) · [reviewed contract](#b0029) |
| [B0030 · 100–100](../../../../../src/runtime/accounted_ordered_rows.hpp#L100) | Callable definition: template&lt;class Probe&gt; const_iterator find(const Probe& probe) const | calls const_iterator, find_node; returns const_iterator(find_node(probe)) · [reviewed contract](#b0030) |
| [B0031 · 101–101](../../../../../src/runtime/accounted_ordered_rows.hpp#L101) | Callable definition: template&lt;class Probe&gt; bool contains(const Probe& probe) const | calls find, end; returns find(probe)!=end() · [reviewed contract](#b0031) |
| [B0032 · 102–104](../../../../../src/runtime/accounted_ordered_rows.hpp#L102) | Callable definition: template&lt;class Probe&gt; Mapped& at(const Probe& probe) | calls find, end, std::out_of_range; returns found-&gt;second · [reviewed contract](#b0032) |
| [B0033 · 105–107](../../../../../src/runtime/accounted_ordered_rows.hpp#L105) | Callable definition: template&lt;class Probe&gt; const Mapped& at(const Probe& probe) const | calls find, end, std::out_of_range; returns found-&gt;second · [reviewed contract](#b0033) |
| [B0034 · 108–108](../../../../../src/runtime/accounted_ordered_rows.hpp#L108) | Callable definition: template&lt;class Probe&gt; iterator upper_bound(const Probe& probe) | calls iterator, upper_node; returns iterator(upper_node(probe)) · [reviewed contract](#b0034) |
| [B0035 · 109–109](../../../../../src/runtime/accounted_ordered_rows.hpp#L109) | Callable definition: template&lt;class Probe&gt; const_iterator upper_bound(const Probe& probe) const | calls const_iterator, upper_node; returns const_iterator(upper_node(probe)) · [reviewed contract](#b0035) |
| [B0036 · 110–115](../../../../../src/runtime/accounted_ordered_rows.hpp#L110) | Callable definition: private: template&lt;class Probe&gt; Node* find_node(const Probe& probe) const | calls get, compare; returns node; nullptr; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 116–120](../../../../../src/runtime/accounted_ordered_rows.hpp#L116) | Callable definition: template&lt;class Probe&gt; Node* upper_node(const Probe& probe) const | calls get, compare; returns result; 1 loop sites · [reviewed contract](#b0037) |
| [B0038 · 121–130](../../../../../src/runtime/accounted_ordered_rows.hpp#L121) | Callable definition: public: template&lt;class Probe,class... Args&gt; std::pair&lt;iterator,bool&gt; try_emplace(const Probe& probe,Args&&... args) | calls find, end, max, resource::MemoryFailure; returns {found,false}; attach(std::move(node)); growth copy_of, make_accounted_unique · [reviewed contract](#b0038) |
| [B0039 · 131–134](../../../../../src/runtime/accounted_ordered_rows.hpp#L131) | Callable definition: template&lt;class Probe&gt; Mapped& operator\[\](const Probe& probe) | calls end, try_emplace; returns found-&gt;second; try_emplace(probe,account_,purpose_,attribution_,lifetime_).first-&gt;second · [reviewed contract](#b0039) |
| [B0040 · 135–137](../../../../../src/runtime/accounted_ordered_rows.hpp#L135) | Callable definition: template&lt;class Probe,class Value&gt; std::pair&lt;iterator,bool&gt; emplace(const Probe& probe,Value&& value) | calls try_emplace; returns try_emplace(probe,std::forward&lt;Value&gt;(value)); growth emplace · [reviewed contract](#b0040) |
| [B0041 · 138–147](../../../../../src/runtime/accounted_ordered_rows.hpp#L138) | Callable definition: insert_return_type insert(node_type handle) noexcept | calls end, find, key, std::move; returns {end(),false,{}}; {found,false,std::move(handle)}; growth insert; source comment (unverified): // Undo nodes return only to the original account/operator/container domain. · [reviewed contract](#b0041) |
| [B0042 · 148–170](../../../../../src/runtime/accounted_ordered_rows.hpp#L148) | Callable definition: node_type extract(iterator position) noexcept | calls link, std::move, get, minimum; returns {}; node_type(std::move(victim)) · [reviewed contract](#b0042) |
| [B0043 · 171–171](../../../../../src/runtime/accounted_ordered_rows.hpp#L171) | Callable definition: node_type extract(const_iterator position) noexcept | calls iterator; returns extract(iterator(position.node_)) · [reviewed contract](#b0043) |
| [B0044 · 172–172](../../../../../src/runtime/accounted_ordered_rows.hpp#L172) | Callable definition: template&lt;class Probe&gt; node_type extract(const Probe& probe) | calls find; returns extract(find(probe)) · [reviewed contract](#b0044) |
| [B0045 · 173–173](../../../../../src/runtime/accounted_ordered_rows.hpp#L173) | Callable definition: void erase(iterator position) noexcept | calls extract · [reviewed contract](#b0045) |
| [B0046 · 174–174](../../../../../src/runtime/accounted_ordered_rows.hpp#L174) | Callable definition: void erase(const_iterator position) noexcept | calls extract · [reviewed contract](#b0046) |
| [B0047 · 175–177](../../../../../src/runtime/accounted_ordered_rows.hpp#L175) | Callable definition: template&lt;class Probe&gt; std::size_t erase(const Probe& probe) | calls find, end; returns 0; 1 · [reviewed contract](#b0047) |
| [B0048 · 178–183](../../../../../src/runtime/accounted_ordered_rows.hpp#L178) | Callable definition: void clear() noexcept | calls rotate_right, std::move; 1 loop sites; source comment (unverified): // Topology teardown uses a vine with bounded stack/no scratch. Nested · [reviewed contract](#b0048) |
| [B0049 · 184–186](../../../../../src/runtime/accounted_ordered_rows.hpp#L184) | Callable definition: void set_lifetime(resource::AllocationLifetime lifetime) | calls begin, end, classify, link; 1 loop sites · [reviewed contract](#b0049) |
| [B0050 · 187–187](../../../../../src/runtime/accounted_ordered_rows.hpp#L187) | Callable definition: unsigned height() const noexcept | calls ; returns height(root_) · [reviewed contract](#b0050) |
| [B0051 · 188–193](../../../../../src/runtime/accounted_ordered_rows.hpp#L188) | Callable definition: bool operator==(const AccountedRowMap& other) const | calls begin, end, view; returns false; false; 1 loop sites · [reviewed contract](#b0051) |
| [B0052 · 194–206](../../../../../src/runtime/accounted_ordered_rows.hpp#L194) | Callable definition: void check_invariants() const | calls begin, end, std::max, height; 1 loop sites · [reviewed contract](#b0052) |
| [B0053 · 207–208](../../../../../src/runtime/accounted_ordered_rows.hpp#L207) | Callable definition: private: static const Row& borrow(const Row& row) noexcept | calls ; returns row · [reviewed contract](#b0053) |
| [B0054 · 209–209](../../../../../src/runtime/accounted_ordered_rows.hpp#L209) | Callable definition: static storage::RowView borrow(storage::RowView row) noexcept | calls ; returns row · [reviewed contract](#b0054) |
| [B0055 · 210–210](../../../../../src/runtime/accounted_ordered_rows.hpp#L210) | Callable definition: static storage::RowView borrow(const storage::AccountedRow& row) noexcept | calls view; returns row.view() · [reviewed contract](#b0055) |
| [B0056 · 211–211](../../../../../src/runtime/accounted_ordered_rows.hpp#L211) | Callable definition: static auto compare(const storage::AccountedRow& left,const Row& right) | calls view; returns left.view()&lt;=&gt;right · [reviewed contract](#b0056) |
| [B0057 · 212–212](../../../../../src/runtime/accounted_ordered_rows.hpp#L212) | Callable definition: static auto compare(const storage::AccountedRow& left,storage::RowView right) noexcept | calls view; returns left.view()&lt;=&gt;right · [reviewed contract](#b0057) |
| [B0058 · 213–213](../../../../../src/runtime/accounted_ordered_rows.hpp#L213) | Callable definition: static auto compare(const storage::AccountedRow& left,const storage::AccountedRow& right) noexcept | calls view; returns left.view()&lt;=&gt;right.view() · [reviewed contract](#b0058) |
| [B0059 · 214–214](../../../../../src/runtime/accounted_ordered_rows.hpp#L214) | Callable definition: static Node* minimum(Node* node) noexcept | calls get; returns node; 1 loop sites · [reviewed contract](#b0059) |
| [B0060 · 215–215](../../../../../src/runtime/accounted_ordered_rows.hpp#L215) | Callable definition: static unsigned height(const Link& node) noexcept | calls ; returns node?node-&gt;height:0 · [reviewed contract](#b0060) |
| [B0061 · 216–216](../../../../../src/runtime/accounted_ordered_rows.hpp#L216) | Callable definition: static void update(Node* node) noexcept | calls std::max, height · [reviewed contract](#b0061) |
| [B0062 · 217–218](../../../../../src/runtime/accounted_ordered_rows.hpp#L217) | Explanatory comments or spacing. | source comment (unverified): // Own Node/key blocks have exact provenance. Mapped::set_lifetime may · [reviewed contract](#b0062) |
| [B0063 · 219–222](../../../../../src/runtime/accounted_ordered_rows.hpp#L219) | Callable definition: static void classify(Link& node,resource::AllocationLifetime lifetime) | calls get_deleter, set_lifetime, get, constexpr; source comment (unverified): // Own Node/key blocks have exact provenance. Mapped::set_lifetime may · [reviewed contract](#b0063) |
| [B0064 · 223–226](../../../../../src/runtime/accounted_ordered_rows.hpp#L223) | Callable definition: Link& link(Node* node) noexcept | calls get; returns root_; node-&gt;parent-&gt;left.get()==node?node-&gt;parent-&gt;left:node-&gt;parent-&gt;right · [reviewed contract](#b0064) |
| [B0065 · 227–232](../../../../../src/runtime/accounted_ordered_rows.hpp#L227) | Callable definition: static void rotate_left(Link& location) noexcept | calls std::move, get, update · [reviewed contract](#b0065) |
| [B0066 · 233–238](../../../../../src/runtime/accounted_ordered_rows.hpp#L233) | Callable definition: static void rotate_right(Link& location) noexcept | calls std::move, get, update · [reviewed contract](#b0066) |
| [B0067 · 239–251](../../../../../src/runtime/accounted_ordered_rows.hpp#L239) | Callable definition: void rebalance(Node* node) noexcept | calls update, link, height, rotate_left; 1 loop sites · [reviewed contract](#b0067) |
| [B0068 · 252–256](../../../../../src/runtime/accounted_ordered_rows.hpp#L252) | Callable definition: std::pair&lt;iterator,bool&gt; attach(Link node) noexcept | calls get, compare, std::move, rebalance; returns {iterator(inserted),true}; 1 loop sites · [reviewed contract](#b0068) |
| [B0069 · 257–266](../../../../../src/runtime/accounted_ordered_rows.hpp#L257) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0069) |
| [B0070 · 267–285](../../../../../src/runtime/accounted_ordered_rows.hpp#L267) | Type/record definition: public: class iterator | returns inner_-&gt;first; &inner_-&gt;first · [reviewed contract](#b0070) |
| [B0071 · 286–286](../../../../../src/runtime/accounted_ordered_rows.hpp#L286) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0071) |
| [B0072 · 287–299](../../../../../src/runtime/accounted_ordered_rows.hpp#L287) | Type/record definition: class node_type | returns bool(inner_); inner_.empty() · [reviewed contract](#b0072) |
| [B0073 · 300–300](../../../../../src/runtime/accounted_ordered_rows.hpp#L300) | Type/record definition: struct insert_return_type |  · [reviewed contract](#b0073) |
| [B0074 · 301–302](../../../../../src/runtime/accounted_ordered_rows.hpp#L301) | Callable definition: AccountedRowSet(const resource::MemoryAccount& account,resource::MemoryPurpose purpose,resource::MemoryAttribution attribution, r… | calls rows_ · [reviewed contract](#b0074) |
| [B0075 · 303–306](../../../../../src/runtime/accounted_ordered_rows.hpp#L303) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0075) |
| [B0076 · 307–307](../../../../../src/runtime/accounted_ordered_rows.hpp#L307) | Callable definition: bool empty() const noexcept | calls ; returns rows_.empty() · [reviewed contract](#b0076) |
| [B0077 · 308–308](../../../../../src/runtime/accounted_ordered_rows.hpp#L308) | Callable definition: std::size_t size() const noexcept | calls ; returns rows_.size() · [reviewed contract](#b0077) |
| [B0078 · 309–309](../../../../../src/runtime/accounted_ordered_rows.hpp#L309) | Callable definition: iterator begin() const noexcept | calls iterator; returns iterator(rows_.begin()) · [reviewed contract](#b0078) |
| [B0079 · 310–310](../../../../../src/runtime/accounted_ordered_rows.hpp#L310) | Callable definition: iterator end() const noexcept | calls iterator; returns iterator(rows_.end()) · [reviewed contract](#b0079) |
| [B0080 · 311–311](../../../../../src/runtime/accounted_ordered_rows.hpp#L311) | Callable definition: template&lt;class Probe&gt; iterator find(const Probe& key) const | calls iterator; returns iterator(rows_.find(key)) · [reviewed contract](#b0080) |
| [B0081 · 312–312](../../../../../src/runtime/accounted_ordered_rows.hpp#L312) | Callable definition: template&lt;class Probe&gt; bool contains(const Probe& key) const | calls ; returns rows_.contains(key) · [reviewed contract](#b0081) |
| [B0082 · 313–313](../../../../../src/runtime/accounted_ordered_rows.hpp#L313) | Callable definition: template&lt;class Probe&gt; iterator upper_bound(const Probe& key) const | calls iterator; returns iterator(rows_.upper_bound(key)) · [reviewed contract](#b0082) |
| [B0083 · 314–314](../../../../../src/runtime/accounted_ordered_rows.hpp#L314) | Callable definition: template&lt;class Probe&gt; std::pair&lt;iterator,bool&gt; insert(const Probe& key) | calls try_emplace, iterator; returns {iterator(result.first),result.second}; growth insert · [reviewed contract](#b0083) |
| [B0084 · 315–315](../../../../../src/runtime/accounted_ordered_rows.hpp#L315) | Callable definition: insert_return_type insert(node_type node) noexcept | calls std::move, iterator, node_type; returns {iterator(result.position),result.inserted,node_type(std::move(result.node))}; growth insert · [reviewed contract](#b0084) |
| [B0085 · 316–316](../../../../../src/runtime/accounted_ordered_rows.hpp#L316) | Callable definition: node_type extract(iterator position) noexcept | calls node_type; returns node_type(rows_.extract(position.inner_)) · [reviewed contract](#b0085) |
| [B0086 · 317–317](../../../../../src/runtime/accounted_ordered_rows.hpp#L317) | Callable definition: template&lt;class Probe&gt; node_type extract(const Probe& key) | calls node_type; returns node_type(rows_.extract(key)) · [reviewed contract](#b0086) |
| [B0087 · 318–318](../../../../../src/runtime/accounted_ordered_rows.hpp#L318) | Callable definition: void erase(iterator position) noexcept | calls  · [reviewed contract](#b0087) |
| [B0088 · 319–319](../../../../../src/runtime/accounted_ordered_rows.hpp#L319) | Callable definition: template&lt;class Probe&gt; std::size_t erase(const Probe& key) | calls ; returns rows_.erase(key) · [reviewed contract](#b0088) |
| [B0089 · 320–320](../../../../../src/runtime/accounted_ordered_rows.hpp#L320) | Callable definition: void clear() noexcept | calls  · [reviewed contract](#b0089) |
| [B0090 · 321–321](../../../../../src/runtime/accounted_ordered_rows.hpp#L321) | Callable definition: void set_lifetime(resource::AllocationLifetime lifetime) | calls  · [reviewed contract](#b0090) |
| [B0091 · 322–322](../../../../../src/runtime/accounted_ordered_rows.hpp#L322) | Callable definition: void check_invariants() const | calls  · [reviewed contract](#b0091) |
| [B0092 · 323–323](../../../../../src/runtime/accounted_ordered_rows.hpp#L323) | Callable definition: unsigned height() const noexcept | calls ; returns rows_.height() · [reviewed contract](#b0092) |
| [B0093 · 324–324](../../../../../src/runtime/accounted_ordered_rows.hpp#L324) | Callable definition: Relation export_rows() const | calls insert, storage::export_row, view; returns result; growth insert; 1 loop sites · [reviewed contract](#b0093) |
| [B0094 · 325–330](../../../../../src/runtime/accounted_ordered_rows.hpp#L325) | Callable definition: bool operator==(const AccountedRowSet& other) const noexcept | calls begin, end, view; returns false; false; 1 loop sites · [reviewed contract](#b0094) |
| [B0095 · 331–334](../../../../../src/runtime/accounted_ordered_rows.hpp#L331) | Member/declaration region. | source comment (unverified): // namespace crown::runtime::detail · [reviewed contract](#b0095) |

## B0001

[Lines 1–23](../../../../../src/runtime/accounted_ordered_rows.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AccountedRowMap {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an AVL-ordered native row map with stable extractable nodes and exact account provenance. |
| inputs / outputs | Mapped type, receiving account/purpose/attribution/lifetime configure copied row keys and separately funded Node allocations. |
| invariants | Keys are immutable, unique and lexically ordered; parent links/heights maintain AVL balance. Mapped must honor the supplied account/ownership protocol and be nothrow destructible. This is not a general allocator injector or paper-derived bound. |
| ownership | Map owns account and unique node tree; each key owns its compact scalar block. Iterators borrow nodes; extracted handles own detached nodes. Nested Mapped ownership is supplied explicitly by construction/callers. |
| failure | Allocating insertion may throw before attachment; fixed ownership/domain violations can throw or terminate at documented noexcept restoration boundaries. |
| cost | O(log N) lexical node comparisons per balanced lookup/mutation, weighted by examined row/string widths, plus mapped work. No logical work grant is accepted; actual node/key capacity uses MemoryAccount. Clear/classification may traverse nested mapped payloads. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
  using Link=resource::AccountedUnique<Node>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one exact native tree node allocation with its allocator/deleter provenance. |
| inputs / outputs | AccountedUnique&lt;Node&gt; links own root/children or an extracted node. |
| invariants | Deleter knows exact Node pointer/count/account/purpose/tag; node lifetime classification needs no account-ledger scan. |
| ownership | Unique ownership transfers during rotations/extraction; raw parent links do not own. |
| failure | Node destruction must be noexcept; invalid deallocation provenance terminates. |
| cost | Fixed owner transfer/classification for the node itself; owned Mapped destruction is separate. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0002

[Lines 24–31](../../../../../src/runtime/accounted_ordered_rows.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  struct Node {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one immutable row key/mapped value, owned children, parent borrow and AVL height. |
| inputs / outputs | entry plus left/right unique links, parent=null and height=1. |
| invariants | Attached children point back to this node. Detached node handles have no children/parent and height one. |
| ownership | Node owns key, mapped value and children. Parent is nonowning; owning Link funds actual Node/control-free allocation. |
| failure | Construction/member failures unwind private state; nothrow destructor is statically required by accounted ownership. |
| cost | Fixed node shell plus row bytes/mapped payload. Ordinary recursive child destruction is avoided by map clear and childless extraction. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    Node(storage::AccountedRow key,Mapped value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one prepared key/value node without attaching it. |
| inputs / outputs | Move key/value into pair&lt;const AccountedRow,Mapped&gt; through piecewise construction. |
| invariants | Const key cannot be replaced in place; Node defaults initialize detached link/height state. |
| ownership | Adopts key/mapped ownership; does not clone or retag nested allocations. |
| failure | Mapped construction/move can throw; caller unique-allocation factory destroys/deallocates partial node. |
| cost | Fixed owner movement plus Mapped move cost; key payload is not copied here. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0003

[Lines 32–40](../../../../../src/runtime/accounted_ordered_rows.hpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<bool Constant> class Iterator {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one stable map node with mutable or const mapped access. |
| inputs / outputs | Pointer-only forward iterator; Constant chooses const pair reference/pointer, while key is always const. |
| invariants | Dereference/increment require a live attached non-end node. Extraction/erase invalidates that node iterator; rotations preserve other node addresses. Iterators do not pin the map or key. |
| ownership | Raw Node pointer only; owner/map or extracted payload must remain alive for any referenced value. |
| failure | No runtime end/foreign-domain guards; violating iterator preconditions is invalid usage. |
| cost | Fixed iterator storage/copy; increment may walk AVL height, complete traversal amortizes link walks across nodes. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    Iterator() noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the null map end iterator. |
| inputs / outputs | node_ defaults null. |
| invariants | Null supports end comparison only, not dereference/increment. |
| ownership | No owner retained. |
| failure | Noexcept, no allocation. |
| cost | Fixed pointer initialization. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0004

[Lines 41–42](../../../../../src/runtime/accounted_ordered_rows.hpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
    Iterator(const Iterator<Other>& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert mutable map iterator to const iterator. |
| inputs / outputs | Enabled only for Constant && !Other; copies node pointer. |
| invariants | Does not extend lifetime or permit reverse const removal. |
| ownership | Borrowed pointer transfer only. |
| failure | Noexcept; no validation or allocation. |
| cost | Fixed pointer copy. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0005

[Lines 43–43](../../../../../src/runtime/accounted_ordered_rows.hpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
    reference operator*() const noexcept{return node_->entry;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the pointed map pair. |
| inputs / outputs | Returns mutable/const entry according to Constant. |
| invariants | Requires live non-end node; key remains const. |
| ownership | Reference borrows node/key/mapped owners. |
| failure | Noexcept unchecked dereference under iterator precondition. |
| cost | Constant access. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0006

[Lines 44–44](../../../../../src/runtime/accounted_ordered_rows.hpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
    pointer operator->() const noexcept{return &node_->entry;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a pointer to the pointed map pair. |
| inputs / outputs | Returns address of live entry. |
| invariants | Requires non-end iterator; does not validate owner/domain. |
| ownership | Borrow only; no lease or shared owner. |
| failure | Noexcept unchecked access. |
| cost | Constant address calculation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0007

[Lines 45–49](../../../../../src/runtime/accounted_ordered_rows.hpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
    Iterator& operator++() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance to the next key in sorted node order. |
| inputs / outputs | Descend to right-subtree minimum or climb parents until leaving a left edge; null denotes end. |
| invariants | Requires live attached non-end node with valid parent links. Keys and node addresses are unchanged. |
| ownership | Mutates only iterator pointer; owns no traversal stack. |
| failure | Noexcept, no allocation/comparison or new guard. |
| cost | O(tree height) worst increment; O(N) total link work for a full valid traversal. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0008

[Lines 50–50](../../../../../src/runtime/accounted_ordered_rows.hpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
    Iterator operator++(int) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return old iterator and advance this iterator. |
| inputs / outputs | Pointer copy followed by prefix increment. |
| invariants | Same live non-end precondition as prefix increment. |
| ownership | Both iterators borrow nodes. |
| failure | Noexcept; no allocation. |
| cost | Fixed copy plus prefix traversal cost. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0009

[Lines 51–54](../../../../../src/runtime/accounted_ordered_rows.hpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
    bool operator==(const Iterator&) const noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare map iterator node identities. |
| inputs / outputs | Default equality compares stored Node pointer. |
| invariants | Does not compare rows, owner domains or establish lifetime; null ends compare equal. |
| ownership | Borrows pointer values only. |
| failure | Noexcept. |
| cost | Constant pointer comparison. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0010

[Lines 55–55](../../../../../src/runtime/accounted_ordered_rows.hpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
    explicit Iterator(Node* node) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an internal map iterator over a found node or end. |
| inputs / outputs | Store pointer without ownership transfer. |
| invariants | Only map/friend iterator constructs this representation. |
| ownership | Nonowning raw pointer. |
| failure | Noexcept; caller establishes validity. |
| cost | Constant initialization. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0011

[Lines 56–59](../../../../../src/runtime/accounted_ordered_rows.hpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  using iterator=Iterator<false>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose mutable and const map iterator aliases. |
| inputs / outputs | iterator=Iterator&lt;false&gt;, const_iterator=Iterator&lt;true&gt;. |
| invariants | Only mapped value mutability changes; keys remain immutable. |
| ownership | Aliases add no ownership. |
| failure | Compile-time names only. |
| cost | No runtime cost. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    Node* node_=nullptr;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the borrowed current map iterator node or null end. |
| inputs / outputs | Raw Node pointer defaults null and changes only through internal construction/increment. |
| invariants | No account/map identity or lifetime lease is stored; user must respect iterator invalidation and live-owner preconditions. |
| ownership | Nonowning pointer; node memory remains owned by map or detached handle. |
| failure | No validation/allocation in the field. |
| cost | Fixed pointer storage. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0012

[Lines 60–75](../../../../../src/runtime/accounted_ordered_rows.hpp#L60); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  class node_type {
   public:
    node_type() noexcept=default;
    node_type(node_type&&) noexcept=default;
    node_type& operator=(node_type&&) noexcept=default;
    node_type(const node_type&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a detached map node for allocation-free undo reinsertion. |
| inputs / outputs | Default empty and move-only handle exposes key/mapped and owns one childless Link. |
| invariants | Extraction removes topology links; insertion can reject duplicate and return ownership intact. Valid reinsertion must use original account/purpose/attribution domain. |
| ownership | Unique node/key/mapped ownership; move assignment can destroy the previous detached payload. |
| failure | Noexcept owner moves; invalid empty key/mapped access is a caller precondition violation. |
| cost | Move construction constant; overwritten/final mapped payload cleanup may be size dependent. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    bool empty() const noexcept{return !node_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether detached map node ownership is absent. |
| inputs / outputs | Returns !node_. |
| invariants | Empty handle permits only ownership/emptiness operations. |
| ownership | Scalar observation. |
| failure | Noexcept. |
| cost | Constant null test. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    explicit operator bool() const noexcept{return bool(node_);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test nonempty map node handle. |
| inputs / outputs | Returns bool(node_). |
| invariants | Does not validate provenance against a target map. |
| ownership | No retained result. |
| failure | Noexcept. |
| cost | Constant null test. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    const storage::AccountedRow& key() const noexcept{return node_->entry.first;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow detached immutable map key. |
| inputs / outputs | Returns key reference from nonempty handle. |
| invariants | Requires node ownership; cannot mutate/rebind key. |
| ownership | Reference expires when node is destroyed; reinsertion preserves node address. |
| failure | Noexcept unchecked nonempty precondition. |
| cost | Constant access. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    Mapped& mapped() const noexcept{return node_->entry.second;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow mutable value from a nonempty detached map node. |
| inputs / outputs | Returns Mapped& even through const node handle. |
| invariants | Const handle preserves key ownership, not mapped immutability; used for exact undo state. |
| ownership | Borrow into uniquely owned detached node. |
| failure | Noexcept unchecked nonempty precondition. |
| cost | Constant access. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    explicit node_type(Link node) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a detached map node Link. |
| inputs / outputs | Move unique allocation owner into node_. |
| invariants | Internal extraction supplies childless detached node. |
| ownership | Unique ownership transfer. |
| failure | Noexcept. |
| cost | Constant transfer. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0013

[Lines 76–76](../../../../../src/runtime/accounted_ordered_rows.hpp#L76); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  struct insert_return_type {iterator position;bool inserted;node_type node;};

  AccountedRowMap(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report map node-handle insertion without discarding a rejected node. |
| inputs / outputs | Position/inserted flag plus returned handle when duplicate found. |
| invariants | Successful insert empties returned handle; empty input yields end,false,empty. |
| ownership | Returned node retains rejected ownership; position only borrows. |
| failure | Carrier performs no validation; handle moves are noexcept. |
| cost | Fixed fields; final returned-handle destruction may free mapped payload. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0015

[Lines 78–82](../../../../../src/runtime/accounted_ordered_rows.hpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  AccountedRowMap(const resource::MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind an empty row map to one existing account/purpose/tag/lifetime. |
| inputs / outputs | Copy allocator provenance and validate it through MemoryAllocator&lt;Node&gt;. |
| invariants | Creates no new account or memory grant; root empty and size zero. |
| ownership | Retains existing account handle; no node/key allocation. |
| failure | Invalid allocator parameters throw MemoryFailure(contract). |
| cost | Fixed handle/contract setup. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0016

[Lines 83–84](../../../../../src/runtime/accounted_ordered_rows.hpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  AccountedRowMap(const AccountedRowMap&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disallow implicit map copying and its hidden nested allocations. |
| inputs / outputs | Copy constructor/assignment are deleted; move assignment is also deleted below. |
| invariants | Ownership must be transferred explicitly or populated under the correct existing account. |
| ownership | No copy operation exists. |
| failure | Invalid use is a compile error. |
| cost | No runtime work. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0017

[Lines 85–87](../../../../../src/runtime/accounted_ordered_rows.hpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  AccountedRowMap(AccountedRowMap&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move the entire tree without moving any node/key address. |
| inputs / outputs | Copy account/provenance/lifetime, move root, exchange source size to zero. |
| invariants | Source is empty but retains valid allocator provenance; root parent stays null and existing node pointers remain stable. |
| ownership | Transfers all node owners to destination; account copy does not mint capacity. |
| failure | Noexcept; no allocation or element move. |
| cost | Constant owner/scalar work. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0018

[Lines 88–88](../../../../../src/runtime/accounted_ordered_rows.hpp#L88); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  AccountedRowMap& operator=(AccountedRowMap&&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disallow replacing an existing map account/tree through move assignment. |
| inputs / outputs | Move construction remains available; assignment is a compile-time error. |
| invariants | Avoids implicit destination teardown/account rebinding semantics in maintained nested state. |
| ownership | No runtime transfer. |
| failure | Compile-time rejection. |
| cost | No runtime work. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0019

[Lines 89–89](../../../../../src/runtime/accounted_ordered_rows.hpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ~AccountedRowMap(){clear();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release the entire map through its iterative clear path. |
| inputs / outputs | Call clear before remaining account/deleter member teardown. |
| invariants | Every Node is detached from children before deletion; Mapped must be nothrow destructible. |
| ownership | Releases node/key/mapped allocations under their original accounts. |
| failure | Implicit noexcept; no scratch allocation for topology teardown. |
| cost | Linear node/link teardown plus mapped payload destruction; no recursive tree-height stack. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0020

[Lines 90–90](../../../../../src/runtime/accounted_ordered_rows.hpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  const resource::MemoryAccount& account() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow bound account. |
| inputs / outputs | Existing account reference; caller keeps map owned. |
| invariants | Reads valid map metadata/topology only; no new admission or allocation. |
| ownership | Retains no new owner; borrow requires live map. |
| failure | Noexcept; requires map remains alive. |
| cost | Constant access. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0021

[Lines 91–91](../../../../../src/runtime/accounted_ordered_rows.hpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  resource::MemoryPurpose purpose() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read bound node purpose. |
| inputs / outputs | Scalar MemoryPurpose. |
| invariants | Reads valid map metadata/topology only; no new admission or allocation. |
| ownership | Scalar copy only. |
| failure | Noexcept; requires map remains alive. |
| cost | Constant access. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0022

[Lines 92–92](../../../../../src/runtime/accounted_ordered_rows.hpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  resource::MemoryAttribution attribution() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read bound node/key attribution. |
| inputs / outputs | Scalar owner tag. |
| invariants | Reads valid map metadata/topology only; no new admission or allocation. |
| ownership | Scalar copy only. |
| failure | Noexcept; requires map remains alive. |
| cost | Constant access. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0023

[Lines 93–93](../../../../../src/runtime/accounted_ordered_rows.hpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  bool empty() const noexcept{return size_==0;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test attached map population. |
| inputs / outputs | True exactly when size_ zero under map invariant. |
| invariants | Reads valid map metadata/topology only; no new admission or allocation. |
| ownership | Scalar observation only. |
| failure | Noexcept; requires map remains alive. |
| cost | Constant count test. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0024

[Lines 94–94](../../../../../src/runtime/accounted_ordered_rows.hpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::size_t size() const noexcept{return size_;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read attached map node count. |
| inputs / outputs | size_ excludes extracted node handles. |
| invariants | Reads valid map metadata/topology only; no new admission or allocation. |
| ownership | Scalar copy only. |
| failure | Noexcept; requires map remains alive. |
| cost | Constant access. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0025

[Lines 95–95](../../../../../src/runtime/accounted_ordered_rows.hpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  iterator begin() noexcept{return iterator(minimum(root_.get()));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow first mutable map iterator. |
| inputs / outputs | Minimum node or end; key immutable. |
| invariants | Reads valid map metadata/topology only; no new admission or allocation. |
| ownership | No node ownership retained. |
| failure | Noexcept; requires map remains alive. |
| cost | O(height) left-link walk, no row comparisons. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0026

[Lines 96–96](../../../../../src/runtime/accounted_ordered_rows.hpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  iterator end() noexcept{return iterator{};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create mutable map end. |
| inputs / outputs | Null iterator sentinel. |
| invariants | Reads valid map metadata/topology only; no new admission or allocation. |
| ownership | No ownership retained. |
| failure | Noexcept; requires map remains alive. |
| cost | Constant initialization. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0027

[Lines 97–97](../../../../../src/runtime/accounted_ordered_rows.hpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  const_iterator begin() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow first const map iterator. |
| inputs / outputs | Minimum node or end; entry const. |
| invariants | Reads valid map metadata/topology only; no new admission or allocation. |
| ownership | No node ownership retained. |
| failure | Noexcept; requires map remains alive. |
| cost | O(height) left-link walk. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0028

[Lines 98–98](../../../../../src/runtime/accounted_ordered_rows.hpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  const_iterator end() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create const map end. |
| inputs / outputs | Null iterator sentinel. |
| invariants | Reads valid map metadata/topology only; no new admission or allocation. |
| ownership | No ownership retained. |
| failure | Noexcept; requires map remains alive. |
| cost | Constant initialization. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0029

[Lines 99–99](../../../../../src/runtime/accounted_ordered_rows.hpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> iterator find(const Probe& probe)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow matching mutable map iterator. |
| inputs / outputs | Delegates find_node(probe); returns end when absent. |
| invariants | Probe may be Row, RowView or AccountedRow with compatible scalar semantics; lookup does not construct a copied key. |
| ownership | Probe borrowed for call; returned iterators borrow live attached nodes. |
| failure | Probe comparison errors can propagate; no explicit allocation or mutation on valid lookup. |
| cost | O(log N) AVL comparisons, each weighted by examined row/string/decimal payload; no logical grant debit. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0030

[Lines 100–100](../../../../../src/runtime/accounted_ordered_rows.hpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> const_iterator find(const Probe& probe) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow matching const map iterator. |
| inputs / outputs | Delegates find_node(probe); returns end when absent. |
| invariants | Probe may be Row, RowView or AccountedRow with compatible scalar semantics; lookup does not construct a copied key. |
| ownership | Probe borrowed for call; returned iterators borrow live attached nodes. |
| failure | Probe comparison errors can propagate; no explicit allocation or mutation on valid lookup. |
| cost | O(log N) AVL comparisons, each weighted by examined row/string/decimal payload; no logical grant debit. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0031

[Lines 101–101](../../../../../src/runtime/accounted_ordered_rows.hpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> bool contains(const Probe& probe) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test exact row-key membership. |
| inputs / outputs | Returns find(probe)!=end(). |
| invariants | Probe may be Row, RowView or AccountedRow with compatible scalar semantics; lookup does not construct a copied key. |
| ownership | Probe borrowed for call; returned iterators borrow live attached nodes. |
| failure | Probe comparison errors can propagate; no explicit allocation or mutation on valid lookup. |
| cost | O(log N) AVL comparisons, each weighted by examined row/string/decimal payload; no logical grant debit. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0032

[Lines 102–104](../../../../../src/runtime/accounted_ordered_rows.hpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> Mapped& at(const Probe& probe)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow mutable mapped value for an existing exact key. |
| inputs / outputs | Find key and return mapped reference; absent key throws out_of_range. |
| invariants | Does not insert a default value. |
| ownership | Borrow requires node/map lifetime; probe borrowed for lookup only. |
| failure | Comparison errors or std::out_of_range on absence; formatted exception path may allocate. |
| cost | O(log N) variable-width lexical lookup; successful access allocates nothing. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0033

[Lines 105–107](../../../../../src/runtime/accounted_ordered_rows.hpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> const Mapped& at(const Probe& probe) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow const mapped value for an existing exact key. |
| inputs / outputs | Find key and return mapped reference; absent key throws out_of_range. |
| invariants | Does not insert a default value. |
| ownership | Borrow requires node/map lifetime; probe borrowed for lookup only. |
| failure | Comparison errors or std::out_of_range on absence; formatted exception path may allocate. |
| cost | O(log N) variable-width lexical lookup; successful access allocates nothing. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0034

[Lines 108–108](../../../../../src/runtime/accounted_ordered_rows.hpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> iterator upper_bound(const Probe& probe)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow first mutable map key strictly above probe. |
| inputs / outputs | Delegates upper_node(probe). |
| invariants | Probe may be Row, RowView or AccountedRow with compatible scalar semantics; lookup does not construct a copied key. |
| ownership | Probe borrowed for call; returned iterators borrow live attached nodes. |
| failure | Probe comparison errors can propagate; no explicit allocation or mutation on valid lookup. |
| cost | O(log N) AVL comparisons, each weighted by examined row/string/decimal payload; no logical grant debit. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0035

[Lines 109–109](../../../../../src/runtime/accounted_ordered_rows.hpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> const_iterator upper_bound(const Probe& probe) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow first const map key strictly above probe. |
| inputs / outputs | Delegates upper_node(probe). |
| invariants | Probe may be Row, RowView or AccountedRow with compatible scalar semantics; lookup does not construct a copied key. |
| ownership | Probe borrowed for call; returned iterators borrow live attached nodes. |
| failure | Probe comparison errors can propagate; no explicit allocation or mutation on valid lookup. |
| cost | O(log N) AVL comparisons, each weighted by examined row/string/decimal payload; no logical grant debit. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0036

[Lines 110–115](../../../../../src/runtime/accounted_ordered_rows.hpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> Node* find_node(const Probe& probe) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Walk the AVL tree for lexical equality. |
| inputs / outputs | Compare each stored key to borrowed probe and follow left/right until equal or null. |
| invariants | Relies on unique sorted keys and valid AVL links; does not scan the account ledger. |
| ownership | Returns nonowning Node pointer. |
| failure | Probe-specific comparison failure propagates; no mutation/allocation. |
| cost | O(height) row comparisons; height O(log N) when invariants hold. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0037

[Lines 116–120](../../../../../src/runtime/accounted_ordered_rows.hpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> Node* upper_node(const Probe& probe) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find strict lexical successor by maintaining a best upper node. |
| inputs / outputs | On stored key &gt; probe save node and go left; otherwise go right. |
| invariants | Strict successor excludes equal key; topology remains unchanged. |
| ownership | Probe and candidate pointers are borrows. |
| failure | Comparison failure propagates; no allocation. |
| cost | O(log N) variable-width row comparisons under AVL invariant. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0038

[Lines 121–130](../../../../../src/runtime/accounted_ordered_rows.hpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe,class... Args> std::pair<iterator,bool> try_emplace(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare funded key/value/node completely before tree attachment. |
| inputs / outputs | Return existing iterator without evaluating Mapped constructor; otherwise check count overflow, copy key, construct Mapped and Node, classify, attach. |
| invariants | Search precedes construction; caller supplies correct nested Mapped account/provenance. Second attachment search uses nonthrowing native row comparison and no allocation. |
| ownership | New key/native Node owned privately until successful attach; input probe borrowed only while copied. |
| failure | Lookup, size overflow, key/Mapped/node allocation/construction/classification can throw before map mutation; private RAII releases prepared storage. |
| cost | Two logarithmic lexical walks on miss plus deep key copy, Node allocation, Mapped construction/classification and logarithmic rebalance. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0039

[Lines 131–134](../../../../../src/runtime/accounted_ordered_rows.hpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> Mapped& operator[](const Probe& probe) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find or construct account-aware mapped state for one row key. |
| inputs / outputs | Return hit; miss forwards this map account/purpose/tag/lifetime into Mapped constructor via try_emplace. |
| invariants | Instantiated only when Mapped supports this constructor; does not silently inject allocators into arbitrary members. |
| ownership | Returns mapped borrow; missing key/value become map-owned. |
| failure | Lookup or insertion/construction failures propagate before attachment. |
| cost | Hit is lexical lookup; miss repeats lookup and pays complete try_emplace/mapped costs. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0040

[Lines 135–137](../../../../../src/runtime/accounted_ordered_rows.hpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe,class Value> std::pair<iterator,bool> emplace(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate one explicit mapped value to guarded insertion. |
| inputs / outputs | Forward Value to try_emplace; existing key retains current mapped value. |
| invariants | Value construction may already have occurred at caller; this wrapper does not rebind nested account ownership. |
| ownership | Adopts forwarded value only on successful missing-key insertion. |
| failure | Underlying comparison/construction/allocation failures propagate. |
| cost | Fixed delegation plus try_emplace and supplied Value move/construction costs. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0041

[Lines 138–147](../../../../../src/runtime/accounted_ordered_rows.hpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  insert_return_type insert(node_type handle) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reinsert a retained childless native node without allocating a replacement. |
| inputs / outputs | Empty input returns end/false; duplicate returns found/false plus intact handle; otherwise verify exact node account/purpose/tag, classify active and attach. |
| invariants | Only original allocation domain may attach. Native row comparisons, ownership transfers and valid lifetime reclassification must not throw; no key/value copy. |
| ownership | Consumes handle on success, returns it on duplicate; detached node/key/mapped ownership is preserved. |
| failure | Noexcept; foreign domain or unexpected classification/comparison failure terminates rather than allocating rollback machinery. |
| cost | Two logarithmic native-row walks and rebalance, O(1) own-node/key classification plus possible traversal of nested Mapped state. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0042

[Lines 148–170](../../../../../src/runtime/accounted_ordered_rows.hpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  node_type extract(iterator position) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach the exact node allocation while preserving all remaining node addresses. |
| inputs / outputs | End returns empty. Replace zero/one-child node or transplant successor for two children; repair parent links, rebalance, decrement size and classify detached payload retained. |
| invariants | Position must belong to this map. Extracted node is childless, parent-null, height one; no entry/key swap or reallocation. Other iterators stay stable. |
| ownership | Returned handle owns exact node/key/mapped; iterator to extracted node no longer participates in map traversal. |
| failure | Noexcept under valid topology/provenance and nonthrowing nested classification; misuse/internal violation may terminate. |
| cost | O(log N) successor/rebalance links with no row comparisons; own classification O(1), nested Mapped classification may be linear in its payload. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0043

[Lines 171–171](../../../../../src/runtime/accounted_ordered_rows.hpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  node_type extract(const_iterator position) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach through a const iterator without copying the immutable key. |
| inputs / outputs | Internally wrap same Node pointer as mutable iterator and call extract. |
| invariants | Same-container/live-or-end position precondition; structural const iterator does not forbid map mutation through this map method. |
| ownership | Transfers detached ownership to result. |
| failure | Noexcept with extract preconditions. |
| cost | Fixed conversion plus extract/classification cost. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0044

[Lines 172–172](../../../../../src/runtime/accounted_ordered_rows.hpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> node_type extract(const Probe& probe)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract by borrowed row probe. |
| inputs / outputs | find followed by iterator extract; absence returns empty. |
| invariants | Lookup has probe-specific exception semantics, extraction preserves original allocation. |
| ownership | Probe borrowed; result uniquely owns detached payload. |
| failure | Comparison can throw before mutation; extract itself is noexcept under its invariants. |
| cost | O(log N) variable-width lookup plus logarithmic detach and nested classification. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0045

[Lines 173–173](../../../../../src/runtime/accounted_ordered_rows.hpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void erase(iterator position) noexcept{auto old=extract(position);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase by mutable iterator. |
| inputs / outputs | Extract into local handle, then destroy that detached payload. |
| invariants | Same-map valid iterator or end; remaining node addresses unchanged. |
| ownership | Local node owner releases exact key/mapped storage. |
| failure | Noexcept; Mapped destruction/provenance must honor native contracts. |
| cost | Extract/rebalance/classification plus size-dependent mapped/key destruction. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0046

[Lines 174–174](../../../../../src/runtime/accounted_ordered_rows.hpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void erase(const_iterator position) noexcept{auto old=extract(position);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase by const iterator. |
| inputs / outputs | Extract into local handle, then destroy that detached payload. |
| invariants | Same-map valid iterator or end; remaining node addresses unchanged. |
| ownership | Local node owner releases exact key/mapped storage. |
| failure | Noexcept; Mapped destruction/provenance must honor native contracts. |
| cost | Extract/rebalance/classification plus size-dependent mapped/key destruction. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0047

[Lines 175–177](../../../../../src/runtime/accounted_ordered_rows.hpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> std::size_t erase(const Probe& probe)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase an exact key if present and report zero/one. |
| inputs / outputs | Find; absent returns0, otherwise iterator erase then1. |
| invariants | Unique keys permit at most one removal. |
| ownership | Probe borrowed; erased payload ownership is destroyed. |
| failure | Comparison failure before mutation; valid erase/destruction is nonthrowing. |
| cost | Logarithmic variable-width lookup plus detach/classification/mapped cleanup. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0048

[Lines 178–183](../../../../../src/runtime/accounted_ordered_rows.hpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void clear() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy map topology iteratively without an allocating traversal stack. |
| inputs / outputs | Rotate left subtrees into a vine; detach each root with no left child, move its right link out, delete childless node, finally set size zero. |
| invariants | No recursive left/right chain destruction. Intermediate topology need not remain AVL or externally readable; do not reenter map from destruction. |
| ownership | Releases every Node/key/mapped owner; invalidates all iterators/borrows into destroyed entries. |
| failure | Noexcept; Mapped must be nothrow destructible. No scratch allocation for topology walk. |
| cost | O(N) link/rotation/deletion operations plus all nested mapped/scalar deallocation; nested mapped destructors can have their own traversals. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0049

[Lines 184–186](../../../../../src/runtime/accounted_ordered_rows.hpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void set_lifetime(resource::AllocationLifetime lifetime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reclassify all attached map/node/key/mapped allocations. |
| inputs / outputs | Store default lifetime and traverse in order, invoking classify on each exact owning Link. |
| invariants | Changes diagnostics only, not key order/contents; nested Mapped.set_lifetime is invoked when available. |
| ownership | Existing accounts/allocations retained; no account or grant created. |
| failure | Lifetime/provenance contract failures can propagate after partial diagnostic relabeling; valid classification allocates nothing. |
| cost | O(N) outer traversal with O(1) own node/key relabel per node, plus full nested mapped classification costs. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0050

[Lines 187–187](../../../../../src/runtime/accounted_ordered_rows.hpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  unsigned height() const noexcept{return height(root_);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read cached outer AVL height. |
| inputs / outputs | Empty returns0; otherwise root height. |
| invariants | Not a query/tree native-height metric or nested mapped height. |
| ownership | Scalar result only. |
| failure | Noexcept. |
| cost | Constant cached access. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0051

[Lines 188–193](../../../../../src/runtime/accounted_ordered_rows.hpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  bool operator==(const AccountedRowMap& other) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare ordered row keys and mapped values semantically. |
| inputs / outputs | Fast size mismatch; paired in-order key RowView and Mapped equality until mismatch/end. |
| invariants | Ignores node shape/account/lifetime labels; requires valid maps and compatible mapped equality. |
| ownership | Borrows both maps; no copied rows or ownership. |
| failure | Mapped equality/comparison exceptions can propagate; no explicit allocation in outer comparison. |
| cost | Linear paired iterator traversal plus variable-width key and Mapped comparison; nested mapped equality may scan large state. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0052

[Lines 194–206](../../../../../src/runtime/accounted_ordered_rows.hpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void check_invariants() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check reachable map ordering, parent links, cached AVL heights/balance and size. |
| inputs / outputs | In-order traversal compares previous key, children/parent links and height difference; final size/root-parent check. |
| invariants | Assumes accessible valid node memory/basic traversability; not a memory-corruption-safe cycle detector or account validator. Does not validate nested Mapped semantics. |
| ownership | Borrows nodes/key views; no scratch set or owner retained. |
| failure | Mismatch throws fixed MemoryFailure(contract); malformed pointer/cycle state is outside safe checker preconditions. |
| cost | O(N) iterator/height checks plus adjacent variable-width row comparison; no allocation on valid check. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0053

[Lines 207–208](../../../../../src/runtime/accounted_ordered_rows.hpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static const Row& borrow(const Row& row) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an ordinary row probe. |
| inputs / outputs | Return const Row& unchanged. |
| invariants | Backing row/scalars must remain alive for synchronous use. |
| ownership | Nonowning borrow; no row export/copy. |
| failure | Noexcept. |
| cost | Constant handle/reference work. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0054

[Lines 209–209](../../../../../src/runtime/accounted_ordered_rows.hpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static storage::RowView borrow(storage::RowView row) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve a native row probe view. |
| inputs / outputs | Return RowView value unchanged. |
| invariants | Backing row/scalars must remain alive for synchronous use. |
| ownership | Nonowning borrow; no row export/copy. |
| failure | Noexcept. |
| cost | Constant handle/reference work. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0055

[Lines 210–210](../../../../../src/runtime/accounted_ordered_rows.hpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static storage::RowView borrow(const storage::AccountedRow& row) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an accounted key payload. |
| inputs / outputs | Return row.view(). |
| invariants | Backing row/scalars must remain alive for synchronous use. |
| ownership | Nonowning borrow; no row export/copy. |
| failure | Noexcept. |
| cost | Constant handle/reference work. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0056

[Lines 211–211](../../../../../src/runtime/accounted_ordered_rows.hpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static auto compare(const storage::AccountedRow& left,const Row& right)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare stored key with ordinary row values. |
| inputs / outputs | Delegate lexical RowView three-way comparison. |
| invariants | Compares scalar variants and values/byte strings, not addresses or digests. |
| ownership | Borrows both rows for call only. |
| failure | Ordinary scalar borrowing errors can propagate; no owning export is used. |
| cost | Examined row-field/string prefix cost; decimals are bounded inline, no whole Row allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0057

[Lines 212–212](../../../../../src/runtime/accounted_ordered_rows.hpp#L212); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static auto compare(const storage::AccountedRow& left,storage::RowView right) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare stored key with native row view. |
| inputs / outputs | Delegate lexical RowView three-way comparison. |
| invariants | Compares scalar variants and values/byte strings, not addresses or digests. |
| ownership | Borrows both rows for call only. |
| failure | Noexcept under valid native scalar views. |
| cost | Examined row-field/string prefix cost; decimals are bounded inline, no whole Row allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0058

[Lines 213–213](../../../../../src/runtime/accounted_ordered_rows.hpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static auto compare(const storage::AccountedRow& left,const storage::AccountedRow& right) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two stored compact keys. |
| inputs / outputs | Delegate lexical RowView three-way comparison. |
| invariants | Compares scalar variants and values/byte strings, not addresses or digests. |
| ownership | Borrows both rows for call only. |
| failure | Noexcept under valid native scalar views. |
| cost | Examined row-field/string prefix cost; decimals are bounded inline, no whole Row allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0059

[Lines 214–214](../../../../../src/runtime/accounted_ordered_rows.hpp#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static Node* minimum(Node* node) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find leftmost node or preserve null end. |
| inputs / outputs | Follow left links from supplied subtree root. |
| invariants | Requires valid acyclic subtree. |
| ownership | Borrowed Node pointer result. |
| failure | Noexcept; no comparisons/allocation. |
| cost | O(subtree height) link walk. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0060

[Lines 215–215](../../../../../src/runtime/accounted_ordered_rows.hpp#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static unsigned height(const Link& node) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read subtree height with null equal to zero. |
| inputs / outputs | Return node-&gt;height or0. |
| invariants | Cached metadata is trusted, not recomputed. |
| ownership | Borrowed Link; scalar result. |
| failure | Noexcept. |
| cost | Constant access. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0061

[Lines 216–216](../../../../../src/runtime/accounted_ordered_rows.hpp#L216); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static void update(Node* node) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Refresh one node cached height from its children. |
| inputs / outputs | Set 1+max(left,right) heights. |
| invariants | Non-null node and bounded valid AVL heights required; does not rebalance by itself. |
| ownership | Mutates scalar metadata only. |
| failure | Noexcept. |
| cost | Constant reads/arithmetic. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0062

[Lines 217–218](../../../../../src/runtime/accounted_ordered_rows.hpp#L217); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L217-L218:sha256:0cac7393a26fe1e4d3322c5a3617f926a63e1353ff69342c6486f5ff3febc57f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`static void classify(Link& node,resource::AllocationLifetime lifetime)\`: Own Node/key blocks have exact provenance. Mapped::set_lifetime may visit a complete nested row set/map, including on extract/reinsert. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/accounted_ordered_rows.hpp:L219; use that declaration for the actual input/output shape. |
| invariants | The source note states: Own Node/key blocks have exact provenance. Mapped::set_lifetime may visit a complete nested row set/map, including on extract/reinsert. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment creates or retains no runtime owner. Its prose documents Node/key block provenance and possible nested Mapped::set_lifetime traversal; that lifetime rule must be checked in the adjacent implementation, not inferred from the comment alone. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Own Node/key blocks have exact provenance. Mapped::set_lifetime may visit a complete nested row set/map, including on extract/reinsert. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0063

[Lines 219–222](../../../../../src/runtime/accounted_ordered_rows.hpp#L219); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static void classify(Link& node,resource::AllocationLifetime lifetime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Relabel exact node allocation, row key block and optional nested mapped state. |
| inputs / outputs | Use owning deleter.set_lifetime(pointer), AccountedRow.set_lifetime, and Mapped.set_lifetime when supported. |
| invariants | No account-ledger search for own Node/key. Nested Mapped method can traverse its rows; O(1) own provenance is not an O(1) whole-subtree claim. |
| ownership | Preserves original owner/account/payload; only allocation diagnostic lifetime changes. |
| failure | Nonempty valid owner/lifetime required; contract or nested classification errors propagate; noexcept callers rely on established validity. |
| cost | O(1) Node/key classification plus actual Mapped classification, with no new allocation/grant on valid paths. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0064

[Lines 223–226](../../../../../src/runtime/accounted_ordered_rows.hpp#L223); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Link& link(Node* node) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the unique owner slot of an attached node. |
| inputs / outputs | Root if parent null, otherwise matching parent left/right Link. |
| invariants | Node belongs to this map; parent-child invariants identify slot without search. |
| ownership | Mutable borrow of owning Link; no ownership transfer yet. |
| failure | Noexcept unchecked internal topology precondition. |
| cost | Constant pointer checks. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0065

[Lines 227–232](../../../../../src/runtime/accounted_ordered_rows.hpp#L227); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static void rotate_left(Link& location) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rotate one owned subtree left without replacing node allocations. |
| inputs / outputs | Move root/pivot/inner child Links, repair all affected parent pointers, update both heights and restore owning location. |
| invariants | Required pivot child must exist. Node/key addresses and sorted order remain stable; old parent link is retained. |
| ownership | Moves existing unique ownership only; no mapped/key copy. |
| failure | Noexcept under valid links and noexcept deleter transfers. |
| cost | Constant Link/pointer/height work; no row comparison or allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0066

[Lines 233–238](../../../../../src/runtime/accounted_ordered_rows.hpp#L233); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static void rotate_right(Link& location) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rotate one owned subtree right without replacing node allocations. |
| inputs / outputs | Move root/pivot/inner child Links, repair all affected parent pointers, update both heights and restore owning location. |
| invariants | Required pivot child must exist. Node/key addresses and sorted order remain stable; old parent link is retained. |
| ownership | Moves existing unique ownership only; no mapped/key copy. |
| failure | Noexcept under valid links and noexcept deleter transfers. |
| cost | Constant Link/pointer/height work; no row comparison or allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0067

[Lines 239–251](../../../../../src/runtime/accounted_ordered_rows.hpp#L239); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void rebalance(Node* node) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore AVL heights/balance along the ancestor path after mutation. |
| inputs / outputs | Update each ancestor, select single/double rotations from child heights, continue from replacement root parent. |
| invariants | Input path belongs to this map; rotations preserve sorted immutable key/node identity. |
| ownership | Mutates links/scalar metadata only. |
| failure | Noexcept; no allocation/comparison under valid topology. |
| cost | O(log N) ancestors/constant rotations per ancestor for valid AVL state. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0068

[Lines 252–256](../../../../../src/runtime/accounted_ordered_rows.hpp#L252); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::pair<iterator,bool> attach(Link node) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach one unique prepared childless node and rebalance. |
| inputs / outputs | Native-key descent chooses empty Link, installs parent, increments size, rebalances and returns iterator,true. |
| invariants | Caller established unique key, room/provenance/classification; attach does not independently reject duplicates or check size overflow. |
| ownership | Consumes prepared Link into map; no new allocation or element movement. |
| failure | Noexcept; native comparisons/topology preconditions must hold. |
| cost | O(log N) variable-width native comparisons plus AVL link maintenance. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0069

[Lines 257–266](../../../../../src/runtime/accounted_ordered_rows.hpp#L257); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  resource::MemoryAccount account_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain row-map allocation domain and outer tree metadata. |
| inputs / outputs | Account/purpose/tag/lifetime, unique root and attached size. |
| invariants | Account identity persists in moved-from empty map; raw iterator nodes do not retain this owner. |
| ownership | Owns account/root; size/lifetime are local diagnostics, not allocated bytes. |
| failure | Field setup does not add generic validation; constructors/mutations enforce contracts. |
| cost | Fixed metadata plus transitively owned tree/mapped payload. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
class AccountedRowSet {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose native ordered row-set semantics over AccountedRowMap&lt;monostate&gt;. |
| inputs / outputs | Keys only; forwarding insertion/extraction, lifetime, diagnostics and explicit ordinary export. |
| invariants | No duplicate key/mapped payload; underlying AVL/provenance/iterator contracts apply unchanged. |
| ownership | Owns one Map, unique compact keys/nodes; iterators are nonowning const-key views. |
| failure | Forwarded operations preserve map failures/noexcept rules; no new recovery layer. |
| cost | Same logarithmic variable-width lookup/mutation and linear cleanup; explicit export allocates a separate ordinary Relation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0070

[Lines 267–285](../../../../../src/runtime/accounted_ordered_rows.hpp#L267); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  class iterator {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a const key from the underlying monostate map. |
| inputs / outputs | Pointer-sized Map::const_iterator wrapper; dereference exposes AccountedRow only. |
| invariants | Live non-end requirements and invalidation rules come from Map; no key mutation or set pinning. |
| ownership | Inner iterator borrows node. |
| failure | Unchecked noexcept iterator operations require valid lifetime. |
| cost | Fixed wrapper operations plus underlying increment link walk. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    iterator() noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct empty set iterator. |
| inputs / outputs | Default inner map end. |
| invariants | Does not extend map/node lifetime; dereference/increment require a live non-end position. |
| ownership | No row ownership retained. |
| failure | Noexcept under iterator preconditions. |
| cost | Constant pointer initialization. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    reference operator*() const noexcept{return inner_->first;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow set key by reference. |
| inputs / outputs | Const AccountedRow& for live non-end inner node. |
| invariants | Does not extend map/node lifetime; dereference/increment require a live non-end position. |
| ownership | No row ownership retained. |
| failure | Noexcept under iterator preconditions. |
| cost | Constant access. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    pointer operator->() const noexcept{return &inner_->first;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow set key by pointer. |
| inputs / outputs | Const AccountedRow* for live non-end inner node. |
| invariants | Does not extend map/node lifetime; dereference/increment require a live non-end position. |
| ownership | No row ownership retained. |
| failure | Noexcept under iterator preconditions. |
| cost | Constant access. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    iterator& operator++() noexcept{++inner_;return *this;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance set iterator. |
| inputs / outputs | Prefix inner map increment. |
| invariants | Does not extend map/node lifetime; dereference/increment require a live non-end position. |
| ownership | No row ownership retained. |
| failure | Noexcept under iterator preconditions. |
| cost | O(height) worst link walk; full traversal linear. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    iterator operator++(int) noexcept{auto old=*this;++*this;return old;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return old set iterator and advance. |
| inputs / outputs | Copy wrapper then prefix increment. |
| invariants | Does not extend map/node lifetime; dereference/increment require a live non-end position. |
| ownership | No row ownership retained. |
| failure | Noexcept under iterator preconditions. |
| cost | Fixed copy plus increment. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    bool operator==(const iterator&) const noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare set iterator positions. |
| inputs / outputs | Compare inner node pointer. |
| invariants | Does not extend map/node lifetime; dereference/increment require a live non-end position. |
| ownership | No row ownership retained. |
| failure | Noexcept under iterator preconditions. |
| cost | Constant pointer comparison. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    explicit iterator(Map::const_iterator value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap internal map const iterator. |
| inputs / outputs | Copy/move pointer wrapper into inner_. |
| invariants | Does not extend map/node lifetime; dereference/increment require a live non-end position. |
| ownership | No row ownership retained. |
| failure | Noexcept under iterator preconditions. |
| cost | Constant pointer transfer. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0071

[Lines 286–286](../../../../../src/runtime/accounted_ordered_rows.hpp#L286); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  using const_iterator=iterator;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the same const-key iterator for const set traversal. |
| inputs / outputs | Set iterator never exposes mapped mutation. |
| invariants | Set keys remain immutable. |
| ownership | Alias adds no owner. |
| failure | Compile-time only. |
| cost | No runtime work. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0072

[Lines 287–299](../../../../../src/runtime/accounted_ordered_rows.hpp#L287); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  class node_type {
   public:
    node_type() noexcept=default;
    node_type(node_type&&) noexcept=default;
    node_type& operator=(node_type&&) noexcept=default;
    explicit operator bool() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a move-only extracted set node through the underlying map handle. |
| inputs / outputs | Default empty; moves transfer inner map node; exposes const row value. |
| invariants | Same original-domain reinsertion requirement; implicit copies unavailable. Move assignment can release old extracted row allocation. |
| ownership | Unique detached node/key owner; no mapped payload beyond monostate. |
| failure | Noexcept moves; empty value access is invalid usage. |
| cost | Constant movement plus possible old row/node deallocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    explicit operator bool() const noexcept{return bool(inner_);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test extracted set node ownership. |
| inputs / outputs | Return inner map handle Boolean. |
| invariants | No provenance validation. |
| ownership | Scalar result. |
| failure | Noexcept. |
| cost | Constant null test. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    bool empty() const noexcept{return inner_.empty();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test empty extracted set node. |
| inputs / outputs | Delegate inner emptiness. |
| invariants | Empty cannot be dereferenced. |
| ownership | Scalar result. |
| failure | Noexcept. |
| cost | Constant null test. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    const storage::AccountedRow& value() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable row from nonempty extracted set node. |
| inputs / outputs | Return inner_.key(). |
| invariants | Requires nonempty live handle; no key mutation/export. |
| ownership | Borrow into detached owner. |
| failure | Noexcept unchecked precondition. |
| cost | Constant access. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

```text
    explicit node_type(Map::node_type value) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt an extracted map node as set node. |
| inputs / outputs | Move inner unique owner. |
| invariants | Only set friends build this representation. |
| ownership | Unique owner transfer. |
| failure | Noexcept. |
| cost | Constant movement. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0073

[Lines 300–300](../../../../../src/runtime/accounted_ordered_rows.hpp#L300); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  struct insert_return_type {iterator position;bool inserted;node_type node;};
  AccountedRowSet(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return set node insertion position/status and any rejected owner. |
| inputs / outputs | Wrap map insertion result with key-only iterator/node. |
| invariants | Duplicate retains input node in result; success consumes it. |
| ownership | Position borrows; returned node owns rejected key. |
| failure | Carrier adds no validation. |
| cost | Fixed fields plus eventual node cleanup. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0074

[Lines 301–302](../../../../../src/runtime/accounted_ordered_rows.hpp#L301); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  AccountedRowSet(const resource::MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind an empty set to the existing allocation domain. |
| inputs / outputs | Forward account/purpose/tag/lifetime to underlying map. |
| invariants | No separate grant, implicit key copy or metadata mirror. |
| ownership | Map retains account; no keys allocated yet. |
| failure | Map allocator-contract failures propagate. |
| cost | Constant setup. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0075

[Lines 303–306](../../../../../src/runtime/accounted_ordered_rows.hpp#L303); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  AccountedRowSet(AccountedRowSet&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Permit set move construction while forbidding copy/replacement assignment. |
| inputs / outputs | Map move transfers topology and empties source; assignments/copies below are deleted. |
| invariants | Transferred node addresses remain stable and source retains its allocator domain. |
| ownership | Unique tree ownership transfer. |
| failure | Noexcept construction; unsupported assignment/copy is compile error. |
| cost | Constant owner/scalar move; implicit final destruction uses map clear. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0076

[Lines 307–307](../../../../../src/runtime/accounted_ordered_rows.hpp#L307); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  bool empty() const noexcept{return rows_.empty();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read set emptiness. |
| inputs / outputs | Underlying map empty flag. |
| invariants | No validation, row scan or allocation is performed. |
| ownership | Scalar/iterator borrow only; set must survive iterators. |
| failure | Noexcept. |
| cost | Constant count read. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0077

[Lines 308–308](../../../../../src/runtime/accounted_ordered_rows.hpp#L308); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::size_t size() const noexcept{return rows_.size();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read attached set key count. |
| inputs / outputs | Underlying map node count. |
| invariants | No validation, row scan or allocation is performed. |
| ownership | Scalar/iterator borrow only; set must survive iterators. |
| failure | Noexcept. |
| cost | Constant count read. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0078

[Lines 309–309](../../../../../src/runtime/accounted_ordered_rows.hpp#L309); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  iterator begin() const noexcept{return iterator(rows_.begin());}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow first set key position. |
| inputs / outputs | Underlying const map minimum or end. |
| invariants | No validation, row scan or allocation is performed. |
| ownership | Scalar/iterator borrow only; set must survive iterators. |
| failure | Noexcept. |
| cost | O(height) link walk. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0079

[Lines 310–310](../../../../../src/runtime/accounted_ordered_rows.hpp#L310); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  iterator end() const noexcept{return iterator(rows_.end());}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct set end position. |
| inputs / outputs | Null map iterator wrapper. |
| invariants | No validation, row scan or allocation is performed. |
| ownership | Scalar/iterator borrow only; set must survive iterators. |
| failure | Noexcept. |
| cost | Constant pointer work. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0080

[Lines 311–311](../../../../../src/runtime/accounted_ordered_rows.hpp#L311); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> iterator find(const Probe& key) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find set key without owning conversion. |
| inputs / outputs | Wrap rows_.find(key). |
| invariants | Map lexical/probe semantics apply; no new validation or key copy. |
| ownership | Probe borrowed; iterator result borrows set node. |
| failure | Probe comparison failures propagate. |
| cost | O(log N) examined row/string-prefix comparisons. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0081

[Lines 312–312](../../../../../src/runtime/accounted_ordered_rows.hpp#L312); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> bool contains(const Probe& key) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test exact set membership. |
| inputs / outputs | Delegate rows_.contains(key). |
| invariants | Map lexical/probe semantics apply; no new validation or key copy. |
| ownership | Probe borrowed; iterator result borrows set node. |
| failure | Probe comparison failures propagate. |
| cost | O(log N) examined row/string-prefix comparisons. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0082

[Lines 313–313](../../../../../src/runtime/accounted_ordered_rows.hpp#L313); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> iterator upper_bound(const Probe& key) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find first set key strictly above probe. |
| inputs / outputs | Wrap rows_.upper_bound(key). |
| invariants | Map lexical/probe semantics apply; no new validation or key copy. |
| ownership | Probe borrowed; iterator result borrows set node. |
| failure | Probe comparison failures propagate. |
| cost | O(log N) examined row/string-prefix comparisons. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0083

[Lines 314–314](../../../../../src/runtime/accounted_ordered_rows.hpp#L314); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> std::pair<iterator,bool> insert(const Probe& key)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert a copied compact key if absent. |
| inputs / outputs | Underlying try_emplace with monostate value; wrap position and inserted flag. |
| invariants | Duplicate allocates no replacement key/node. |
| ownership | New key/node funded by set account; returned iterator borrows. |
| failure | Map lookup/allocation/overflow failures propagate before attachment. |
| cost | Map insertion cost: logarithmic comparisons/rebalance plus deep key and Node allocation on miss. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0084

[Lines 315–315](../../../../../src/runtime/accounted_ordered_rows.hpp#L315); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  insert_return_type insert(node_type node) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reinsert a retained set node without allocating a new key. |
| inputs / outputs | Move inner handle through map insertion; wrap result/rejected owner. |
| invariants | Original account/purpose/tag and childless-node preconditions apply. |
| ownership | Success consumes, duplicate returns unique owner. |
| failure | Noexcept; invalid original-domain assumptions terminate in map. |
| cost | Logarithmic native key comparison/rebalance with fixed key/node classification; no mapped subtree beyond monostate. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0085

[Lines 316–316](../../../../../src/runtime/accounted_ordered_rows.hpp#L316); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  node_type extract(iterator position) noexcept{return node_type(rows_.extract(position.inner_));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach one exact set node by iterator. |
| inputs / outputs | Wrap map extraction. |
| invariants | Iterator belongs to this set or is end; other key addresses remain stable. |
| ownership | Returned handle owns detached key/node. |
| failure | Noexcept under map topology/provenance preconditions. |
| cost | Logarithmic pointer rebalance plus fixed classification. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0086

[Lines 317–317](../../../../../src/runtime/accounted_ordered_rows.hpp#L317); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> node_type extract(const Probe& key)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach set node by borrowed exact key. |
| inputs / outputs | Lookup/extract underlying map; absence empty. |
| invariants | No key export/copy. |
| ownership | Result uniquely owns node/key. |
| failure | Probe comparison errors propagate before mutation. |
| cost | Logarithmic variable-width lookup plus detach/rebalance. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0087

[Lines 318–318](../../../../../src/runtime/accounted_ordered_rows.hpp#L318); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void erase(iterator position) noexcept{rows_.erase(position.inner_);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase set node by iterator. |
| inputs / outputs | Delegate map erase. |
| invariants | Same-set position/end precondition. |
| ownership | Releases exact node/key allocation. |
| failure | Noexcept under native map contracts. |
| cost | Detach/rebalance and key/node deallocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0088

[Lines 319–319](../../../../../src/runtime/accounted_ordered_rows.hpp#L319); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Probe> std::size_t erase(const Probe& key)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Erase set key and report zero/one. |
| inputs / outputs | Delegate map erase(key). |
| invariants | Unique key semantics. |
| ownership | Probe borrowed; removed owner destroyed. |
| failure | Probe comparison errors can propagate. |
| cost | Logarithmic comparisons plus detach/deallocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0089

[Lines 320–320](../../../../../src/runtime/accounted_ordered_rows.hpp#L320); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void clear() noexcept{rows_.clear();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release all set keys through iterative map clear. |
| inputs / outputs | Delegate rows_.clear(). |
| invariants | Invalidates all set iterators; no recursive AVL topology destructor. |
| ownership | Releases node/compact-key blocks under original account. |
| failure | Noexcept with no scratch allocation. |
| cost | Linear key/node teardown plus scalar deallocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0090

[Lines 321–321](../../../../../src/runtime/accounted_ordered_rows.hpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void set_lifetime(resource::AllocationLifetime lifetime){rows_.set_lifetime(lifetime);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Relabel every set node and compact row block. |
| inputs / outputs | Delegate map traversal with monostate values. |
| invariants | No key/order change or fresh allocation/grant. |
| ownership | Retains original account/provenance. |
| failure | Invalid lifetime/provenance contract failure can propagate; valid path allocates nothing. |
| cost | O(N) traversal, O(1) own node/key relabel per row. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0091

[Lines 322–322](../../../../../src/runtime/accounted_ordered_rows.hpp#L322); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void check_invariants() const{rows_.check_invariants();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check set AVL ordering/link/height/count invariants. |
| inputs / outputs | Delegate map checker. |
| invariants | Not a safe arbitrary pointer/cycle corruption detector or database truth checker. |
| ownership | Read-only row/node borrows. |
| failure | Fixed MemoryFailure(contract) on detected mismatch. |
| cost | Linear traversal plus adjacent lexical row comparison; no valid-path allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0092

[Lines 323–323](../../../../../src/runtime/accounted_ordered_rows.hpp#L323); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  unsigned height() const noexcept{return rows_.height();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read cached set AVL height. |
| inputs / outputs | Underlying map root height or0. |
| invariants | No validation, row scan or allocation is performed. |
| ownership | Scalar/iterator borrow only; set must survive iterators. |
| failure | Noexcept. |
| cost | Constant cached read. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0093

[Lines 324–324](../../../../../src/runtime/accounted_ordered_rows.hpp#L324); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Relation export_rows() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly export the complete native set to an ordinary owning Relation. |
| inputs / outputs | For each key export owning Row/scalars and insert into ordered std::set. |
| invariants | External/diagnostic conversion, not internal funded native retention or a new checked artifact. |
| ownership | Result owns ordinary Row/string/Decimal and set-node allocations independent of source account. |
| failure | Scalar/export/allocation/comparison failures propagate; partial local result is discarded without source mutation. |
| cost | Copies every row/deep byte and performs O(N log N) ordered insert comparisons despite sorted input; explicit extra storage. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0094

[Lines 325–330](../../../../../src/runtime/accounted_ordered_rows.hpp#L325); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  bool operator==(const AccountedRowSet& other) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two ordered compact key sets semantically. |
| inputs / outputs | Fast size check then paired RowView equality until mismatch/end. |
| invariants | Ignores topology/account/lifetime; valid native ScalarViews support nonthrowing comparison. |
| ownership | Borrows both sets; no export or new ownership. |
| failure | Noexcept under native row contracts. |
| cost | Linear paired iterator traversal plus examined row/string prefixes; no allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0095

[Lines 331–334](../../../../../src/runtime/accounted_ordered_rows.hpp#L331); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Map rows_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the set's sole accounted monostate map. |
| inputs / outputs | All set key nodes, compact rows, AVL metadata and account provenance live in rows_. |
| invariants | No mirrored ordinary Relation or secondary container is retained; explicit export_rows creates a caller-owned copy. |
| ownership | Exclusive underlying map owner; destruction uses its iterative clear. |
| failure | Construction/operations follow underlying map contracts; field itself adds no guard. |
| cost | Fixed map handle/state plus all key/node storage; last release has linear teardown cost. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/support_invariants.md](../../../../support_invariants.md), [include/crown/resource/ownership.hpp](../../../../../include/crown/resource/ownership.hpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |
