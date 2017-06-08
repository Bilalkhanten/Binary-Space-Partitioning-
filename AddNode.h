#pragma once

// system
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

namespace smeeze {
namespace bsp {
template <typename Item, typename Partition, typename Pivot>
class node {
public:
  typedef          node                           node_type;
  typedef          Item                           value_type;
  typedef typename std::vector<Item>              container_type;
  typedef typename container_type::const_iterator iterator_type;
  typedef          Pivot                          pivot_type;

  node() = delete;
  node(const node &) = delete;
  node & operator=(const node &) = delete;

  node(node && n) : _front(std::move(n._front)), _back(std::move(n._back)), _partition(std::move(n._partition)), _items(std::move(n._items)) { }

  template<typename Iterator>
  node(const Iterator & begin, const Iterator & end) : _front(nullptr), _back(nullptr) {
    // empty case
    if(begin == end) {
      throw(std::runtime_error("empty set"));
    }

    container_type front_set;
    container_type back_set;

    // partition must implement operator()(...)
    _partition(begin, end, _items, front_set, back_set);

    if(!front_set.empty()) { _front.reset(new node(front_set.begin(), front_set.end())); }
    if(!back_set.empty()) { _back.reset(new node(back_set.begin(), back_set.end())); }
  }

  iterator_type begin() const { return _items.begin(); }
  iterator_type end() const { return _items.end(); }

  const node * get_front() const { return _front.get(); }
  const node * get_back() const { return _back.get(); }

  const Partition & get_partition() const { return _partition; }
private:
  std::unique_ptr<node> _front;
  std::unique_ptr<node> _back;
  Partition             _partition;
  container_type        _items;
};
}
}
