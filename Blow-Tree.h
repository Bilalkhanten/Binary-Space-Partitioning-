#pragma once

// system
#include <iostream>
#include <type_traits>
// bsp
#include <smeeze/bsp/iterator.h>
#include <smeeze/bsp/node.h>
#include <smeeze/bsp/view.h>

namespace smeeze {
namespace bsp {
template <typename Node>
class tree {
public:
  typedef Node node_type;

  template<typename... Args>
  tree(Args&&... args) : _root_node(args...) { }

  template<typename Adapter>
  smeeze::bsp::view<Adapter> view(const typename Adapter::pivot_type & pivot) const {
    static_assert(std::is_same<typename Adapter::node_type, Node>::value, "adapter node type is not the same as tree node type");

    return smeeze::bsp::view<Adapter>(get_root(), pivot);
  }

  const Node * get_root() const { return & _root_node; }
private:
  Node _root_node;
};
}
}
