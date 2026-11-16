#pragma once

#include "crown/resource/ownership.hpp"
#include "crown/storage/accounted_row.hpp"
#include <algorithm>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>

namespace crown::runtime::detail {

// Stable extracted nodes support ordered Delta/inspection state. Node/key
// allocations use the supplied account; Mapped must honor that ownership too.
// Exact owning pointers make node/key lifetime relabeling O(1), without an
// account-ledger search. Nested mapped-state relabeling has its own cost.
template<class Mapped>
class AccountedRowMap {
  struct Node;
  using Link=resource::AccountedUnique<Node>;
  struct Node {
    std::pair<const storage::AccountedRow,Mapped> entry;
    Link left,right;
    Node* parent=nullptr;
    unsigned height=1;
    Node(storage::AccountedRow key,Mapped value)
        :entry(std::piecewise_construct,std::forward_as_tuple(std::move(key)),std::forward_as_tuple(std::move(value))) {}
  };
 public:
  template<bool Constant> class Iterator {
   public:
    using value_type=std::pair<const storage::AccountedRow,Mapped>;
    using difference_type=std::ptrdiff_t;
    using iterator_category=std::forward_iterator_tag;
    using reference=std::conditional_t<Constant,const value_type&,value_type&>;
    using pointer=std::conditional_t<Constant,const value_type*,value_type*>;
    Iterator() noexcept=default;
    template<bool Other> requires(Constant && !Other)
    Iterator(const Iterator<Other>& other) noexcept:node_(other.node_) {}
    reference operator*() const noexcept{return node_->entry;}
    pointer operator->() const noexcept{return &node_->entry;}
    Iterator& operator++() noexcept {
      if(node_->right)node_=minimum(node_->right.get());
      else {auto* parent=node_->parent;while(parent && node_==parent->right.get()){node_=parent;parent=parent->parent;}node_=parent;}
      return *this;
    }
    Iterator operator++(int) noexcept {auto old=*this;++*this;return old;}
    bool operator==(const Iterator&) const noexcept=default;
   private:
    friend class AccountedRowMap;
    template<bool> friend class Iterator;
    explicit Iterator(Node* node) noexcept:node_(node) {}
    Node* node_=nullptr;
  };
  using iterator=Iterator<false>;
  using const_iterator=Iterator<true>;
  class node_type {
   public:
    node_type() noexcept=default;
    node_type(node_type&&) noexcept=default;
    node_type& operator=(node_type&&) noexcept=default;
    node_type(const node_type&)=delete;
    node_type& operator=(const node_type&)=delete;
    bool empty() const noexcept{return !node_;}
    explicit operator bool() const noexcept{return bool(node_);}
    const storage::AccountedRow& key() const noexcept{return node_->entry.first;}
    Mapped& mapped() const noexcept{return node_->entry.second;}
   private:
    friend class AccountedRowMap;
    explicit node_type(Link node) noexcept:node_(std::move(node)) {}
    Link node_;
  };
  struct insert_return_type {iterator position;bool inserted;node_type node;};

  AccountedRowMap(const resource::MemoryAccount& account,resource::MemoryPurpose purpose,
      resource::MemoryAttribution attribution,resource::AllocationLifetime lifetime=resource::AllocationLifetime::active)
      :account_(account),purpose_(purpose),attribution_(attribution),lifetime_(lifetime) {
    static_cast<void>(resource::MemoryAllocator<Node>(account,purpose,attribution));
  }
  AccountedRowMap(const AccountedRowMap&)=delete;
  AccountedRowMap& operator=(const AccountedRowMap&)=delete;
  AccountedRowMap(AccountedRowMap&& other) noexcept
      :account_(other.account_),purpose_(other.purpose_),attribution_(other.attribution_),lifetime_(other.lifetime_),
       root_(std::move(other.root_)),size_(std::exchange(other.size_,0)) {}
  AccountedRowMap& operator=(AccountedRowMap&&)=delete;
  ~AccountedRowMap(){clear();}
  const resource::MemoryAccount& account() const noexcept{return account_;}
  resource::MemoryPurpose purpose() const noexcept{return purpose_;}
  resource::MemoryAttribution attribution() const noexcept{return attribution_;}
  bool empty() const noexcept{return size_==0;}
  std::size_t size() const noexcept{return size_;}
  iterator begin() noexcept{return iterator(minimum(root_.get()));}
  iterator end() noexcept{return iterator{};}
  const_iterator begin() const noexcept{return const_iterator(minimum(root_.get()));}
  const_iterator end() const noexcept{return const_iterator{};}
  template<class Probe> iterator find(const Probe& probe) {return iterator(find_node(probe));}
  template<class Probe> const_iterator find(const Probe& probe) const {return const_iterator(find_node(probe));}
  template<class Probe> bool contains(const Probe& probe) const{return find(probe)!=end();}
  template<class Probe> Mapped& at(const Probe& probe) {
    const auto found=find(probe);if(found==end())throw std::out_of_range("native ordered row key");return found->second;
  }
  template<class Probe> const Mapped& at(const Probe& probe) const {
    const auto found=find(probe);if(found==end())throw std::out_of_range("native ordered row key");return found->second;
  }
  template<class Probe> iterator upper_bound(const Probe& probe) {return iterator(upper_node(probe));}
  template<class Probe> const_iterator upper_bound(const Probe& probe) const {return const_iterator(upper_node(probe));}
 private:
  template<class Probe> Node* find_node(const Probe& probe) const {
    auto* node=root_.get();
    while(node){const auto order=compare(node->entry.first,probe);if(order==0)return node;node=order<0?node->right.get():node->left.get();}
    return nullptr;
  }
  template<class Probe> Node* upper_node(const Probe& probe) const {
    auto* node=root_.get();Node* result=nullptr;
    while(node){if(compare(node->entry.first,probe)>0){result=node;node=node->left.get();}else node=node->right.get();}
    return result;
  }
 public:
  template<class Probe,class... Args> std::pair<iterator,bool> try_emplace(const Probe& probe,Args&&... args) {
    const auto found=find(probe);if(found!=end())return {found,false};
    if(size_==std::numeric_limits<std::size_t>::max())throw resource::MemoryFailure(resource::MemoryFault::overflow);
    auto key=storage::AccountedRow::copy_of(account_,borrow(probe),attribution_);
    auto node=resource::make_accounted_unique<Node>(attribution_,account_,purpose_,
        std::move(key),Mapped(std::forward<Args>(args)...));
    classify(node,lifetime_);
    return attach(std::move(node));
  }
  template<class Probe> Mapped& operator[](const Probe& probe) {
    const auto found=find(probe);if(found!=end())return found->second;
    return try_emplace(probe,account_,purpose_,attribution_,lifetime_).first->second;
  }
  template<class Probe,class Value> std::pair<iterator,bool> emplace(const Probe& probe,Value&& value) {
    return try_emplace(probe,std::forward<Value>(value));
  }
  insert_return_type insert(node_type handle) noexcept {
    if(!handle)return {end(),false,{}};
    const auto found=find(handle.key());if(found!=end())return {found,false,std::move(handle)};
    // Undo nodes return only to the original account/operator/container domain.
    const auto& deleter=handle.node_.get_deleter();
    if(deleter.account().statistics().owner!=account_.statistics().owner || deleter.purpose()!=purpose_ || deleter.attribution()!=attribution_)
      std::terminate();
    classify(handle.node_,lifetime_);
    auto result=attach(std::move(handle.node_));return {result.first,result.second,{}};
  }
  node_type extract(iterator position) noexcept {
    auto* target=position.node_;if(!target)return {};
    auto& location=link(target);auto victim=std::move(location);auto* parent=victim->parent;
    Node* rebalance_from=parent;
    if(!victim->left || !victim->right) {
      location=victim->left?std::move(victim->left):std::move(victim->right);
      if(location)location->parent=parent;
    }else if(!victim->right->left) {
      auto replacement=std::move(victim->right);
      replacement->left=std::move(victim->left);replacement->left->parent=replacement.get();
      replacement->parent=parent;location=std::move(replacement);rebalance_from=location.get();
    }else {
      auto* successor=minimum(victim->right.get());auto* successor_parent=successor->parent;
      auto replacement=std::move(successor_parent->left);
      successor_parent->left=std::move(replacement->right);
      if(successor_parent->left)successor_parent->left->parent=successor_parent;
      replacement->left=std::move(victim->left);replacement->left->parent=replacement.get();
      replacement->right=std::move(victim->right);replacement->right->parent=replacement.get();
      replacement->parent=parent;location=std::move(replacement);rebalance_from=successor_parent;
    }
    victim->parent=nullptr;victim->height=1;--size_;rebalance(rebalance_from);
    classify(victim,resource::AllocationLifetime::retained);return node_type(std::move(victim));
  }
  node_type extract(const_iterator position) noexcept{return extract(iterator(position.node_));}
  template<class Probe> node_type extract(const Probe& probe){return extract(find(probe));}
  void erase(iterator position) noexcept{auto old=extract(position);}
  void erase(const_iterator position) noexcept{auto old=extract(position);}
  template<class Probe> std::size_t erase(const Probe& probe) {
    const auto found=find(probe);if(found==end())return 0;erase(found);return 1;
  }
  void clear() noexcept {
    // Topology teardown uses a vine with bounded stack/no scratch. Nested
    // mapped payload destruction is additional work.
    while(root_){if(root_->left)rotate_right(root_);else {auto node=std::move(root_);root_=std::move(node->right);if(root_)root_->parent=nullptr;}}
    size_=0;
  }
  void set_lifetime(resource::AllocationLifetime lifetime) {
    lifetime_=lifetime;for(auto i=begin();i!=end();++i)classify(link(i.node_),lifetime);
  }
  unsigned height() const noexcept{return height(root_);}
  bool operator==(const AccountedRowMap& other) const {
    if(size()!=other.size())return false;
    auto a=begin(),b=other.begin();
    for(;a!=end();++a,++b)if(a->first.view()!=b->first.view() || !(a->second==b->second))return false;
    return true;
  }
  void check_invariants() const {
    std::size_t count=0;const storage::AccountedRow* previous=nullptr;
    for(auto i=begin();i!=end();++i) {
      const auto* node=i.node_;++count;
      if((node->left && node->left->parent!=node)||(node->right && node->right->parent!=node) ||
          node->height!=1+std::max(height(node->left),height(node->right)) ||
          (height(node->left)>height(node->right)?height(node->left)-height(node->right):height(node->right)-height(node->left))>1 ||
          (previous && !(previous->view()<node->entry.first.view())))
        throw resource::MemoryFailure(resource::MemoryFault::contract);
      previous=&node->entry.first;
    }
    if(count!=size_ || (root_ && root_->parent))throw resource::MemoryFailure(resource::MemoryFault::contract);
  }
 private:
  static const Row& borrow(const Row& row) noexcept{return row;}
  static storage::RowView borrow(storage::RowView row) noexcept{return row;}
  static storage::RowView borrow(const storage::AccountedRow& row) noexcept{return row.view();}
  static auto compare(const storage::AccountedRow& left,const Row& right){return left.view()<=>right;}
  static auto compare(const storage::AccountedRow& left,storage::RowView right) noexcept{return left.view()<=>right;}
  static auto compare(const storage::AccountedRow& left,const storage::AccountedRow& right) noexcept{return left.view()<=>right.view();}
  static Node* minimum(Node* node) noexcept {if(node)while(node->left)node=node->left.get();return node;}
  static unsigned height(const Link& node) noexcept{return node?node->height:0;}
  static void update(Node* node) noexcept{node->height=1+std::max(height(node->left),height(node->right));}
  // Own Node/key blocks have exact provenance. Mapped::set_lifetime may
  // visit a complete nested row set/map, including on extract/reinsert.
  static void classify(Link& node,resource::AllocationLifetime lifetime) {
    node.get_deleter().set_lifetime(node.get(),lifetime);node->entry.first.set_lifetime(lifetime);
    if constexpr(requires{node->entry.second.set_lifetime(lifetime);})node->entry.second.set_lifetime(lifetime);
  }
  Link& link(Node* node) noexcept {
    if(!node->parent)return root_;
    return node->parent->left.get()==node?node->parent->left:node->parent->right;
  }
  static void rotate_left(Link& location) noexcept {
    auto old=std::move(location);auto* parent=old->parent;auto top=std::move(old->right);
    old->right=std::move(top->left);if(old->right)old->right->parent=old.get();
    top->left=std::move(old);top->left->parent=top.get();top->parent=parent;
    update(top->left.get());update(top.get());location=std::move(top);
  }
  static void rotate_right(Link& location) noexcept {
    auto old=std::move(location);auto* parent=old->parent;auto top=std::move(old->left);
    old->left=std::move(top->right);if(old->left)old->left->parent=old.get();
    top->right=std::move(old);top->right->parent=top.get();top->parent=parent;
    update(top->right.get());update(top.get());location=std::move(top);
  }
  void rebalance(Node* node) noexcept {
    while(node) {
      update(node);auto& location=link(node);
      if(height(node->left)>height(node->right)+1) {
        if(height(node->left->right)>height(node->left->left))rotate_left(node->left);
        rotate_right(location);
      }else if(height(node->right)>height(node->left)+1) {
        if(height(node->right->left)>height(node->right->right))rotate_right(node->right);
        rotate_left(location);
      }
      node=location->parent;
    }
  }
  std::pair<iterator,bool> attach(Link node) noexcept {
    auto* parent=static_cast<Node*>(nullptr);auto* location=&root_;
    while(*location){parent=location->get();location=compare(parent->entry.first,node->entry.first)>0?&parent->left:&parent->right;}
    auto* inserted=node.get();node->parent=parent;*location=std::move(node);++size_;rebalance(parent);return {iterator(inserted),true};
  }
  resource::MemoryAccount account_;
  resource::MemoryPurpose purpose_;
  resource::MemoryAttribution attribution_;
  resource::AllocationLifetime lifetime_;
  Link root_;
  std::size_t size_=0;
};

class AccountedRowSet {
  using Map=AccountedRowMap<std::monostate>;
 public:
  class iterator {
   public:
    using value_type=storage::AccountedRow;
    using difference_type=std::ptrdiff_t;
    using iterator_category=std::forward_iterator_tag;
    using reference=const value_type&;
    using pointer=const value_type*;
    iterator() noexcept=default;
    reference operator*() const noexcept{return inner_->first;}
    pointer operator->() const noexcept{return &inner_->first;}
    iterator& operator++() noexcept{++inner_;return *this;}
    iterator operator++(int) noexcept{auto old=*this;++*this;return old;}
    bool operator==(const iterator&) const noexcept=default;
   private:
    friend class AccountedRowSet;
    explicit iterator(Map::const_iterator value) noexcept:inner_(value) {}
    Map::const_iterator inner_;
  };
  using const_iterator=iterator;
  class node_type {
   public:
    node_type() noexcept=default;
    node_type(node_type&&) noexcept=default;
    node_type& operator=(node_type&&) noexcept=default;
    explicit operator bool() const noexcept{return bool(inner_);}
    bool empty() const noexcept{return inner_.empty();}
    const storage::AccountedRow& value() const noexcept{return inner_.key();}
   private:
    friend class AccountedRowSet;
    explicit node_type(Map::node_type value) noexcept:inner_(std::move(value)) {}
    Map::node_type inner_;
  };
  struct insert_return_type {iterator position;bool inserted;node_type node;};
  AccountedRowSet(const resource::MemoryAccount& account,resource::MemoryPurpose purpose,resource::MemoryAttribution attribution,
      resource::AllocationLifetime lifetime=resource::AllocationLifetime::active):rows_(account,purpose,attribution,lifetime) {}
  AccountedRowSet(AccountedRowSet&&) noexcept=default;
  AccountedRowSet& operator=(AccountedRowSet&&)=delete;
  AccountedRowSet(const AccountedRowSet&)=delete;
  AccountedRowSet& operator=(const AccountedRowSet&)=delete;
  bool empty() const noexcept{return rows_.empty();}
  std::size_t size() const noexcept{return rows_.size();}
  iterator begin() const noexcept{return iterator(rows_.begin());}
  iterator end() const noexcept{return iterator(rows_.end());}
  template<class Probe> iterator find(const Probe& key) const{return iterator(rows_.find(key));}
  template<class Probe> bool contains(const Probe& key) const{return rows_.contains(key);}
  template<class Probe> iterator upper_bound(const Probe& key) const{return iterator(rows_.upper_bound(key));}
  template<class Probe> std::pair<iterator,bool> insert(const Probe& key){const auto result=rows_.try_emplace(key);return {iterator(result.first),result.second};}
  insert_return_type insert(node_type node) noexcept{auto result=rows_.insert(std::move(node.inner_));return {iterator(result.position),result.inserted,node_type(std::move(result.node))};}
  node_type extract(iterator position) noexcept{return node_type(rows_.extract(position.inner_));}
  template<class Probe> node_type extract(const Probe& key){return node_type(rows_.extract(key));}
  void erase(iterator position) noexcept{rows_.erase(position.inner_);}
  template<class Probe> std::size_t erase(const Probe& key){return rows_.erase(key);}
  void clear() noexcept{rows_.clear();}
  void set_lifetime(resource::AllocationLifetime lifetime){rows_.set_lifetime(lifetime);}
  void check_invariants() const{rows_.check_invariants();}
  unsigned height() const noexcept{return rows_.height();}
  Relation export_rows() const {Relation result;for(const auto& row:*this)result.insert(storage::export_row(row.view()));return result;}
  bool operator==(const AccountedRowSet& other) const noexcept {
    if(size()!=other.size())return false;
    auto a=begin(),b=other.begin();
    for(;a!=end();++a,++b)if(a->view()!=b->view())return false;
    return true;
  }
 private:
  Map rows_;
};
} // namespace crown::runtime::detail
