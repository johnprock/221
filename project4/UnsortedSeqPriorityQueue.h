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

    Position curr = S.first(), minp = curr;			// start search
    while (!S.isLast(curr))
    {
      if (comp(key(minp), key(curr)) > 0)
        minp = curr;
        
      curr = S.after(curr);
    }

    return (comp(key(minp), key(curr)) > 0 ? curr : minp).element().element();
  }
  const Key& minKey() const     			// returns minimum key
      throw(EmptyContainerException) {
    if (S.isEmpty())
      throw EmptyContainerException("Minimum key of empty queue");

    Position curr = S.first(), minp;			// start search
    while (!S.isLast(curr))
    {
      if (comp(key(minp), key(curr)) > 0)
        minp = curr;
        
      curr = S.after(curr);
    }

    return (comp(key(minp), key(curr)) > 0 ? curr : minp).element().key();
  }
  void removeMin()					// remove minimum
      throw(EmptyContainerException) {
    if (S.isEmpty())
      throw EmptyContainerException("Removal from empty queue");

    Position curr = S.first(), minp = curr;			// start search
    while (!S.isLast(curr))
    {
      if (comp(key(minp), key(curr)) > 0)
        minp = curr;
        
      curr = S.after(curr);
    }

    S.remove(comp(key(minp), key(curr)) > 0 ? curr : minp);
  }
};
#endif
