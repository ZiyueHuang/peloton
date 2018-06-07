//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// skiplist.h
//
// Identification: src/include/index/skiplist.h
//
// Copyright (c) 2015-17, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <vector>
#include <algorithm>

namespace peloton {
namespace index {

/*
 * SKIPLIST_TEMPLATE_ARGUMENTS - Save some key strokes
 */
#define SKIPLIST_TEMPLATE_ARGUMENTS                                       \
  template <typename KeyType, typename ValueType, typename KeyComparator, \
            typename KeyEqualityChecker, typename ValueEqualityChecker>

template <typename KeyType, typename ValueType, typename KeyComparator,
          typename KeyEqualityChecker, typename ValueEqualityChecker>
class SkipList {
  // TODO: Add your declarations here
 public:

  constexpr static size_t MAX_LEVEL = 16;

  struct Node {
    KeyType key;
    ValueType value;
    Node * forwards[MAX_LEVEL];
    Node(KeyType k, ValueType v): key(k), value(v) {
      for (size_t i = 0; i <= MAX_LEVEL; i++) {
        forwards[i] = nullptr;
      }
    }
  };

  SkipList(KeyComparator p_key_cmp_obj = KeyComparator{},
           KeyEqualityChecker p_key_eq_obj = KeyEqualityChecker{},
           ValueEqualityChecker p_value_eq_obj = ValueEqualityChecker{})
    :
      key_cmp_obj{p_key_cmp_obj},
      key_eq_obj{p_key_eq_obj},
      value_eq_obj{p_value_eq_obj} {
    return;
  }

  ~SkipList() {
  	return;
  }

  bool Insert(const KeyType &key, const ValueType &value) {
    nodes.push_back(Node(key, value));
    return true;
  }

  bool Delete(const KeyType &key, const ValueType &value) {
  	bool ret = false;
    auto dit = nodes.begin();
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
      const Node& n = *it;
      if (key_eq_obj(key, n.key) && value_eq_obj(value, n.value)) {
      	dit = it;
      	ret = true;
      	break;
      }
    }
    if (ret) nodes.erase(dit);
    return ret;
  }

  void GetValue(const KeyType &search_key, std::vector<ValueType> &value_list) {
    for (auto n : nodes) {
      if (key_eq_obj(search_key, n.key)) value_list.push_back(n.value);
    }
  }

  KeyComparator key_cmp_obj;

  KeyEqualityChecker key_eq_obj;

  ValueEqualityChecker value_eq_obj;

  std::vector<Node> nodes;
};

}  // namespace index
}  // namespace peloton
