#ifndef SORTEDSEQPRIORITYQUEUE_H_
#define SORTEDSEQPRIORITYQUEUE_H_
#include "RuntimeException.h"
#include "Item.h"
#include "NodeSequence.h"
template <typename Key, typename Element, typename Comp>
class SortedSeqPriorityQueue { 
public:
  typedef Item<Key, Element>	    ItemPair;		// (key, element) pair
  typedef typename NodeSequence<ItemPair>::Position 	    Position;		// position in sequence
protected:      					// local utilities
  const Key& key(const Position& p) const 		// position's key
    { return p.element().key(); }
  Element& element(const Position& p)			// position's element
    { Position t = p; return t.element().element(); }
private:        					// member data
  NodeSequence<ItemPair>  S;						// sorted sequence
  Comp	    comp;					// comparator
public:
  SortedSeqPriorityQueue() : S(), comp() { }		// default constructor
  int size() const      				// number of items
    { return S.size(); }
  bool isEmpty() const  				// is the queue empty?
    { return S.isEmpty(); }
  void insertItem(const Key& k, const Element& e) {	// insert into queue
    if (S.isEmpty())
      S.insertFirst(ItemPair(k, e));			// if empty insert first

    else if (comp(k, key(S.last())) > 0)		// greater than last?
      S.insertAfter(S.last(), ItemPair(k,e));		// insert at end

    else {
      Position curr = S.first();			// start search
      while (!S.isLast(curr) && comp(k, key(curr)) > 0)			// skip over small keys
        curr = S.after(curr);
      S.insertBefore(curr, ItemPair(k,e));			// insert here
    }
  }
  Element& minElement()					// element with min key
      throw(EmptyContainerException) {
    if (S.isEmpty())
      throw EmptyContainerException("Minimum element of empty queue");
    else
      return element(S.first());
  }
  const Key& minKey() const     			// returns minimum key
      throw(EmptyContainerException) {
    if (S.isEmpty())
      throw EmptyContainerException("Minimum key of empty queue");
    else
      return key(S.first());
  }
  void removeMin()					// remove minimum
      throw(EmptyContainerException) {
    if (S.isEmpty())
      throw EmptyContainerException("Removal from empty queue");
    S.remove(S.first());
  }
};
#endif
