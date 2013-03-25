/** 
 * HeapPriorityQueue.h:
 * A priority-queue template class realized with a heap. It uses a data structure
 * called "heap tree", which is uniquely defined in the text and is stored in VectorHeapTree.h.
 * A "heap tree" stores (Key, Element) in each internal node, but does NOT have the
 * "heap-order property"; thus, it's not a heap. The priority-queue
 * template maintains the "heap-order property" for the heap tree and provides 
 * standard operations for a priority-queue. The heap order
 * property states that the parent's value/key is always less than or equal
 * to children's values. The section 7.3 describes how to implement a 
 * priority-queue using a "heap" and a "heap tree". The latter structure 
 * is a unique design of the text.
 *
 * This template uses Item class to store (Key, Element) pair. It also 
 * uses Comp class to compare two keys.
 *
 * Most of the code is excerpted from the code fragment 7.8, 7.9 in
 * "Data Structures and Algorithms in C++" by M. T. Goodrich et al.
 */
#ifndef HEAPPRIORITYQUEUE_H_
#define HEAPPRIORITYQUEUE_H_
#include "RuntimeException.h"
#include "Item.h"
#include <algorithm>
#include <vector>

template<typename T>
struct CompWrapper
{
  template<typename U>
  bool operator()(const U& x, const U& y)
  {
    return T()(x, y) == 1;
  }
};

template <typename Key, typename Element, typename Comp>
class HeapPriorityQueue { 
public: 						// typename shortcuts
  typedef Item<Key, Element>	    ItemPair; 		// (key, element) pair
private: 						// member data
  Comp	      comp;					// comparator
  std::vector<Element> v;
public:  
  HeapPriorityQueue()			// constructor
    : v(), comp() { }
  int size() const 					// number of elements
    { return v.size(); }
  bool isEmpty() const  				// is the queue empty?
    { return size() == 0; }
    
  void insertItem(const Key& k, const Element& e);	// insert (key, element)

  const Element& minElement()					// return min element
  {
    return v.front();
  }
  void removeMin() throw(EmptyContainerException);	// remove minimum
  
};

template <typename Key, typename Element, typename Comp>
void HeapPriorityQueue<Key, Element, Comp>::
insertItem(const Key& k, const Element& e) {		// insert key-element
  v.push_back(e);
  std::push_heap(v.begin(), v.end(), CompWrapper<Comp>());
}

template <typename Key, typename Element, typename Comp>
void HeapPriorityQueue<Key, Element, Comp>::
removeMin()						// remove minimum
    throw(EmptyContainerException) {
  
  if (isEmpty())
    throw EmptyContainerException("Removal from empty queue");

  std::pop_heap(v.begin(), v.end(), CompWrapper<Comp>());
  v.pop_back();
}
#endif
