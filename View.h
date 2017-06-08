#pragma once

// bsp
#include <smeeze/bsp/Loop.h>

namespace smeeze {
namespace bsp {
template<typename Adapter>
class view {
public:
  view(const typename Adapter::node_type * node, const typename Adapter::pivot_type & pivot) : _adapter(node), _pivot(pivot) { }

  smeeze::bsp::iterator<Adapter> begin() const { return smeeze::bsp::iterator<Adapter>(_adapter, _pivot); }
  smeeze::bsp::iterator<Adapter> end() const { return smeeze::bsp::iterator<Adapter>(nullptr, _pivot); }
private:
  Adapter                      _adapter;
  typename Adapter::pivot_type _pivot;
};
}
}
