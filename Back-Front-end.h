#pragma once

// system
#include <cassert>

namespace smeeze {
namespace bsp {
namespace adapters {
template<typename Node>
class front_to_back {
private:
  typedef          const Node          * node_pointer;
public:
  typedef          Node                  node_type;
  typedef typename Node::value_type      value_type;
  typedef typename Node::iterator_type   iterator_type;
  typedef typename Node::pivot_type      pivot_type;

  front_to_back(node_pointer n) : _node(n), _first(nullptr), _second(nullptr) {
  }

  void pivot(const pivot_type & p) {
    assert(_node != nullptr);
    _first = _node->get_front();
    _second = _node->get_back();
  }

  iterator_type begin() const { return _node->begin(); }
  iterator_type end() const { return _node->end(); }

  node_pointer get_node() const { return _node; }
  node_pointer get_first() const { return _first; }
  node_pointer get_second() const { return _second; }
private:
  node_pointer _node;
  node_pointer _first;
  node_pointer _second;
};
}
}
}
