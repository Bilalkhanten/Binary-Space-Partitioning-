#pragma once

// system
#include <cassert>
#include <iterator>
#include <stack>
#include <queue>
// bsp
#include <smeeze/bsp/node.h>

namespace smeeze {
namespace bsp {
template<typename Adapter>
class iterator : public std::iterator<std::forward_iterator_tag, typename Adapter::value_type> {
public:
  iterator() = delete;
  iterator(const Adapter & a, const typename Adapter::pivot_type & pivot) : _pivot(pivot) {
    // push end state
    _stack.push(frame(nullptr));
    // push adapter
    if(a.get_node() != nullptr) {
      _stack.push(frame(a));
      _advance();
    }
  }

  bool                                 operator!=(const iterator & rhs) { return _stack.top() != rhs._stack.top(); }
  iterator                           & operator++() { _advance(); return *this; }
  const typename Adapter::value_type & operator*() const { return *iter; }
private:
  //
  // 'stack' frame
  //
  class frame {
  public:
    enum class mode { init, push_first, iterate_init, iterate_handle, push_second, fini };

    frame(const frame &f) : _adapter(f._adapter), _modes(f._modes), _modes_iterator(std::next(_modes.begin(), std::distance(f._modes.begin(), f._modes_iterator))) { }

    frame(const Adapter & adapter) : _adapter(adapter), _modes({mode::init,
                                                                mode::push_first,
                                                                mode::iterate_init, mode::iterate_handle,
                                                                mode::push_second,
                                                                mode::fini}), _modes_iterator(_modes.begin()) { }

    bool operator!=(const frame & rhs) { return _adapter.get_node() != rhs._adapter.get_node(); }

    const Adapter & get_adapter() const { return _adapter; }
          Adapter & get_adapter()       { return _adapter; }
    const mode    & get_mode() const { return *_modes_iterator; }

    void advance() {
      ++_modes_iterator;
    }
  private:
             Adapter                             _adapter;
             std::array<mode, 6>                 _modes;
    typename std::array<mode, 6>::const_iterator _modes_iterator;
  };
  typename Adapter::pivot_type _pivot;
  std::stack<frame>            _stack;
private:
  //
  // private members
  //
  void _advance() {
    while(_stack.size() > 1) {
      switch(_frame_mode()) {
        case frame::mode::init:
          _frame_advance();
          _get_adapter().pivot(_pivot);
          break;
        case frame::mode::push_first:
          _frame_advance();
          {
            auto first(_get_adapter().get_first());
            if(first != nullptr) { _stack.push(frame(first)); }
          }
          break;
        case frame::mode::iterate_init:
          _frame_advance();
          iter = _get_adapter().begin();
          end = _get_adapter().end();
          if(iter == end) {
            _frame_advance();
          } else {
            return;                                                   // yield
          }
          break;
        case frame::mode::iterate_handle:
          ++iter;
          if(iter == end) {
            _frame_advance();
          } else {
            return;                                                   // yield
          }
          break;
        case frame::mode::push_second:
          _frame_advance();
          {
            auto second(_get_adapter().get_second());
            if(second != nullptr) { _stack.push(frame(second)); }
          }
          break;
        case frame::mode::fini:
          _frame_advance();
          _stack.pop();
          break;
      }
    }
  }

  const frame & _get_frame() const { assert(!_stack.empty()); return _stack.top(); }
        frame & _get_frame()       { assert(!_stack.empty()); return _stack.top(); }

  const Adapter & _get_adapter() const { return _get_frame().get_adapter(); }
        Adapter & _get_adapter()       { return _get_frame().get_adapter(); }

  const typename frame::mode & _frame_mode() const { return _get_frame().get_mode(); }
  void                         _frame_advance() { _get_frame().advance(); }

  typename Adapter::iterator_type iter;
  typename Adapter::iterator_type end;
};
}
}
