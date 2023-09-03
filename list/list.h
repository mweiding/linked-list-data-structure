#ifndef LINKEDLIST_LIST_H
#define LINKEDLIST_LIST_H

#include <functional>
#include <iostream>
#include <string>
#include <tuple>

template <typename K, typename V>
class list {
 private:
  struct element {
    const K key;
    V value;
    element *next;

    element(const std::tuple<K, V>, element *);
  };

  element *head = nullptr;

  element *sortpart(std::function<bool(K, K)> lessThan, element *partlist);

 public:
  ~list();

  const V *search(const K) const;

  bool isEmpty() const;

  bool isSorted(std::function<bool(K, K)> lessThan) const;

  std::tuple<K, V> popHead();

  void sort(std::function<bool(K, K)> lessThan);

  list<K, V> &operator+=(const std::tuple<K, V>);

  list<K, V> &operator-=(const K);

  void printTo(std::ostream &ostr) const;
};
template <typename K, typename V>
list<K, V>::element::element(const std::tuple<K, V> tuple, list::element *after)
    : key(std::get<0>(tuple)) {
  this->value = std::get<1>(tuple);
  this->next = after;
}

template <typename K, typename V>
list<K, V>::~list() {
  element *current = head;
  while (current) {
    element *temp = current->next;
    delete current;
    current = temp;
  }
}

template <typename K, typename V>
bool list<K, V>::isEmpty() const {
  return head == nullptr;
}

template <typename K, typename V>
bool list<K, V>::isSorted(std::function<bool(K, K)> lessThan) const {
  element *current = head;
  if(current != nullptr) {
    while (current->next) {
      if (lessThan(current->next->key, current->key)) {  // check if sorting order is violated
        return false;
      }
      current = current->next;
    }
  }
  return true;
}

template <typename K, typename V>
std::tuple<K, V> list<K, V>::popHead() {
  if (head) {
    std::tuple<K, V> resultTuple(head->key, head->value);
    element *pTemp = head->next;
    delete head;
    head = pTemp;
    return resultTuple;
  } else {
    return std::tuple<K, V> ();
  }
}

template <typename K, typename V>
void list<K, V>::sort(std::function<bool(K, K)> lessThan) {
  if (isSorted(lessThan)) return;
  head = this->sortpart(lessThan, head);
}

template <typename K, typename V>
typename list<K, V>::element *list<K, V>::sortpart(
    std::function<bool(K, K)> lessThan, list::element *partlist) {
  // Pivot-element
  element *pivot = partlist;
  // Head of lower-list
  element *lower = nullptr;
  // Last element of lower-list
  element *lowerIndex = nullptr;
  // Head of higher-list
  element *higher = nullptr;
  // Last element of higher-list
  element *higherIndex = nullptr;

  if (partlist->next) {
    element *current = partlist->next;
    pivot->next = nullptr;

    while (current) {
      if (lessThan(current->key, pivot->key)) {
        if (lowerIndex) {
          lowerIndex->next = current; // add to end of lowerlist
        } else {
          lower = current; // add to head of lowerlist if empty
        }
        lowerIndex = current; // make lowerIndex point to the last element of lowerlist
      } else {
        if (higherIndex) {
          higherIndex->next = current;
        } else {
          higher = current;
        }
        higherIndex = current;
      }
      // disconnect remaining list
      element *temp = current->next;
      current->next = nullptr;
      current = temp;
    }

    if (higher) {
      pivot->next = this->sortpart(lessThan, higher);
    }

    if (lower) {
      element *newHead = this->sortpart(lessThan, lower);
      element *end = newHead;
      while (end->next) end = end->next;
      end->next = pivot;
      // Use pivot to return the new head of the list
      pivot = newHead;
    }
  }
  return pivot;
}

template <typename K, typename V>
const V *list<K, V>::search(const K searched_key) const {
  element *current = head;
  while (current != nullptr) {
    if (current->key == searched_key)
      return &current->value;
    else
      current = current->next;
  }
  return nullptr;
}

template <typename K, typename V>
list<K, V> &list<K, V>::operator+=(const std::tuple<K, V> addTuple) {
  if (head == nullptr) {
    head = new element(addTuple, nullptr);
  } else {
    element *current = head;
    K search_key = std::get<0>(addTuple);
    while (current != nullptr) {
      if (current->key == search_key) {
        current->value = std::get<1>(addTuple);
        break;
      } else if (current->next == nullptr) {
        current->next = new element(addTuple, nullptr);
        break;
      }
      current = current->next;
    }
  }
  return *this;
}

template <typename K, typename V>
list<K, V> &list<K, V>::operator-=(const K removeKey) {
  element *current = head;
  // check if list is empty
  if (head == nullptr) {
    return *this;
    // check if removeKey is the head
  } else if (current->key == removeKey) {
    head = head->next;
    delete current;
  } else {
    while (current->next != nullptr)
      if (current->next->key == removeKey) {
        element *temp = current->next;
        current->next = current->next->next; //connect the two dangling nodes
        delete temp;
        break;
      } else
        current = current->next;
  }
  return *this;
}

template <typename K, typename V>
void list<K, V>::printTo(std::ostream &ostr) const {
  element *current = head;
  while (current != nullptr) {
    ostr << current->key << "." << current->value << std::endl;
    current = current->next;
  }
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &ostr, const list<K, V> &list) {
  list.printTo(ostr);
  return ostr;
}

#endif  // LINKEDLIST_LIST_H
