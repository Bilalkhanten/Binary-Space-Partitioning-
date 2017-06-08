#pragma once

// system
#include <cstdint>
#include <algorithm>
// bsp
#include <smeeze/bsp/AddNode.h>

namespace smeeze {
namespace bsp {
class statistics {
public:
  // calculate the size of the tree(number of items)
  template<typename Node>
  static uint32_t size(const Node * node) {
    return (std::distance(node->begin(), node->end())) + (node->get_front() == nullptr ? 0 : size(node->get_front())) + (node->get_back() == nullptr ? 0 : size(node->get_back()));
  }
  // count the number of nodes
  template<typename Node>
  static uint32_t count(const Node * node) {
    return 1 + (node->get_front() == nullptr ? 0 : size(node->get_front())) + (node->get_back() == nullptr ? 0 : size(node->get_back()));
  }
  // how deep is the tree
  template<typename Node>
  static uint32_t depth(const Node * node) {
    uint32_t l(node->get_front() == nullptr ? 0 : depth(node->get_front())); 
    uint32_t r(node->get_back() == nullptr ? 0 : depth(node->get_back())); 
    return 1 + std::max(l, r);
  }
};
}
}
