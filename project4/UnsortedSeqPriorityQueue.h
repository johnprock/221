#ifndef UNSORTEDSEQPRIORITYQUEUE_H_
#define UNSORTEDSEQPRIORITYQUEUE_H_
#include "RuntimeException.h"
#include "Item.h"
#include "NodeSequence.h"
template <typename Key, typename Element, typename Comp>
class UnsortedSeqPriorityQueue { 
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
  UnsortedSeqPriorityQueue() : S(), comp() { }		// default constructor
  int size() const      				// number of items
    { return S.size(); }
  bool isEmpty() const  				// is the queue empty?
    { return S.isEmpty(); }
  void insertItem(const Key& k, const Element& e) {	// insert into queue
    S.insertLast(ItemPair(k,e));		// insert at end
  }
  Element& minElement()					// element with min key
      throw(EmptyContainerException) {
    if (S.isEmpty())
      throw EmptyContainerException("Minimum element of empty queue");

    Position curr = S.first();			// start search
    Key k = curr.element().key();
    while (!S.isLast(curr))
    {
      if (comp(k, key(curr)) > 0)
        k = curr.element().key();
        
      curr = S.after(curr);
    }

    return curr.element().element();
  }
  const Key& minKey() const     			// returns minimum key
      throw(EmptyContainerException) {
    if (S.isEmpty())
      throw EmptyContainerException("Minimum key of empty queue");

    Position curr = S.first();			// start search
    Key k = curr.element().key();
    while (!S.isLast(curr))
    {
      if (comp(k, key(curr)) > 0)
        k = curr.element().key();
        
      curr = S.after(curr);
    }

    return curr.element().key();
  }
  void removeMin()					// remove minimum
      throw(EmptyContainerException) {
    if (S.isEmpty())
      throw EmptyContainerException("Removal from empty queue");

    Position curr = S.first();			// start search
    Key k = curr.element().key();
    while (!S.isLast(curr))
    {
      if (comp(k, key(curr)) > 0)
        k = curr.element().key();
        
      curr = S.after(curr);
    }

    S.remove(curr);
  }
};
#endif
