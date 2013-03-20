#ifndef NODESEQUENCE_H_
#define NODESEQUENCE_H_
#include <iostream>
#include "NodeList.h"
#include "RuntimeException.h"
template <typename Object>
class NodeSequence : public NodeList<Object> {
protected: 						// utilities
  void checkRank(int rank) const 			// check for valid rank
      throw(BoundaryViolationException) {
    if (rank < 0 || rank >= NodeList<Object>::sz)
      throw BoundaryViolationException("Invalid rank");
  }
public:
  typedef typename NodeList<Object>::Position Position;
  typedef typename NodeList<Object>::NodePtr NodePtr;
  NodeSequence() : NodeList<Object>() {} // default constructor
  NodeSequence(const Object* a, int array_size) 
    : NodeList<Object>(a,array_size) {}          // additional constructor by array
  Position atRank(int rank) const 			// position of rank
      throw(BoundaryViolationException);
  int rankOf(const Position& p) const 			// get rank of element
      throw(InvalidPositionException);
  Object elemAtRank (int rank) const 			// element at this rank
      throw(BoundaryViolationException) {
    checkRank(rank);
    return atRank(rank).element();
  }
  void insertAtRank (int rank, const Object& element)	// insert at given rank
      throw(BoundaryViolationException) {
    if (rank == NodeList<Object>::size())					// no checkRank if last
      insertLast(element);
    else {
      checkRank(rank);
      insertBefore( atRank(rank), element );
    }
  }
  void removeAtRank (int rank)				// remove from rank
      throw(BoundaryViolationException) {
    checkRank(rank);
    Position p = atRank(rank);				// position to remove
    remove(p);
  }
  void replaceAtRank (int rank, const Object& element)	// replace at rank
      throw(BoundaryViolationException) {
    checkRank(rank);
    replaceElement( atRank(rank), element );
  }
};

template <typename Object>
typename NodeSequence<Object>::Position NodeSequence<Object>::
atRank(int rank) const 					// position of rank
    throw(BoundaryViolationException) {
  NodePtr v;
  checkRank(rank);
  if (rank <= NodeList<Object>::size()/2) {				// scan forward from head
    v = NodeList<Object>::header->next;
    for (int i = 0; i < rank; i++)
      v = v->next;
  }
  else {						// scan back from tail
    v = NodeList<Object>::trailer->prev;
    for (int i = 1; i < NodeList<Object>::size()-rank; i++)
      v = v->prev;
  }
  return Position(v);
}

template <typename Object>
int NodeSequence<Object>::
rankOf(const Position &p) const 			// get rank of position
    throw(InvalidPositionException) {
  NodePtr v = nodePtr(NodeList<Object>::first());
  int i = 0;
  while (v != NodeList<Object>::trailer) {				// search for p.node
    if (p.node == v) return i;				// found it here
    v = v->next;					// else advance
    i++;
  }							// did not find it?
  throw InvalidPositionException("Position not found");
}
#endif
