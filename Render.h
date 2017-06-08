#pragma once

// system
#include <iostream>
// bsp
#include <smeeze/bsp/AddNode.h>

namespace smeeze {
namespace bsp {
class render {
private:
  // helper
  template<typename Node>
  static std::string _note_to_string(const Node & node) {
    std::string result("[");
    for(auto i = node->begin(); i != node->end() ; ++i) {
      result += " " + std::to_string(*i);
    }
    result += " ]";
    return result;
  }
public:
  //
  // left to right
  //
  template<typename Node>
  static void left_to_right(const Node * node) {
    if(node->get_front() != nullptr) { _left_to_right(node->get_front(), "", true); }

    std::cerr << "\u253c" << _note_to_string(node) << std::endl;

    if(node->get_back() != nullptr) { _left_to_right(node->get_back(), "", false); }
  }
private:
  template<typename Node>
  static void _left_to_right(const Node * node, const std::string & indent, bool is_front, size_t depth = 0) {
    static const char * box_horizontal          = "\u2500";
    static const char * box_vertical            = "\u2502";
    static const char * box_down_right          = "\u256d";
    static const char * box_down_horizontal     = "\u252c";
    static const char * box_up_right            = "\u2570";
    static const char * box_up_horizontal       = "\u2534";
    static const char * box_vertical_horizontal = "\u253c";

    if(node->get_front() != nullptr) { _left_to_right(node->get_front(), indent + (is_front ? " " : box_vertical) + "   " , true, depth + 1); }

    if(is_front) {
      std::cerr << indent << box_down_right << box_horizontal << box_horizontal << box_horizontal;
    } else {
      std::cerr << indent << box_up_right << box_horizontal << box_horizontal << box_horizontal;
    }
    switch(_node_joint_type(node)) {
      case 0: std::cerr << box_horizontal; break;
      case 1: std::cerr << box_up_horizontal; break;
      case 2: std::cerr << box_down_horizontal; break;
      case 3: std::cerr << box_vertical_horizontal; break;
    }
    std::cerr << _note_to_string(node) << std::endl;

    if(node->get_back() != nullptr) { _left_to_right(node->get_back(), indent + (is_front ? box_vertical : " ") + "   " , false, depth + 1); }
  }
  template<typename Node>
  static uint32_t _node_joint_type(const Node * node) {
    uint32_t result(0);
    if(node->get_front() != nullptr) { result |= 1; }
    if(node->get_back() != nullptr) { result |= 2; }
    return result;
  }
};
}
}
