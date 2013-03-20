#ifndef VECTORSEQUENCE_H_
#define VECTORSEQUENCE_H_
#include <iostream>
#include "ArrayVector.h"
#include "RuntimeException.h"
template <typename Object>
class VectorSequence : public ArrayVector<Object> {
public:
  class Position {					// position in ArrayVector
  private:
    int i;				// index of a object
    const VectorSequence<Object>* v;    
  public:
    Position(int i = -1, const VectorSequence<Object>* v=NULL)				// constructor
      { this->i = i; this->v = v;}
    int index() const
      { return i; }
    Object& element() const 				// return element
         throw(InvalidPositionException) {
      if (i == -1) throw InvalidPositionException("Null position");
      return v->elemAtRank(i);
    }
    bool isNull() const 				// a null position?
      { return i == -1 || v==NULL; }
    //overload << for outputing Position object
    friend std::ostream& operator<<(std::ostream& out, const Position& p) {
      if (p.isNull())
        out << "null";
      else
        out << p.element();
      return out;
    }
  };  
protected: 						// utilities
  void checkRank(int rank) const 			// check for valid rank
      throw(BoundaryViolationException) {
    if (rank < 0 || rank >= ArrayVector<Object>::sz)
      throw BoundaryViolationException("Invalid rank");
  }
public:
  VectorSequence() : ArrayVector<Object>() {} // default constructor
  VectorSequence(const Object* a, int array_size) 
    : ArrayVector<Object>(a,array_size) {}          // additional constructor by array
  Position atRank(int rank) const 			// position of rank
      throw(BoundaryViolationException);
  int rankOf(const Position& p) const 			// get rank of element
      throw(InvalidPositionException);

  //============= query functions =============
  
  bool isFirst(const Position& p) const 		// is this the first?
      throw(InvalidPositionException) {
    if (p.isNull())
      throw InvalidPositionException("Null Position");
    else
      return p.index()==0;
  }
  bool isLast(const Position& p) const 			// is this the last?
      throw(InvalidPositionException) {
    if (p.isNull())
      throw InvalidPositionException("Null Position");
    else
      return p.index()==ArrayVector<Object>::sz-1;
  }
  
  //============= accessor functions =============
  
  Position first() const 				// return first element
      throw(EmptyContainerException) {
    if (ArrayVector<Object>::isEmpty()) throw EmptyContainerException("Sequence is empty");
    return Position(0,this);
  }
  Position last() const 				// return last element
      throw(EmptyContainerException) {
    if (ArrayVector<Object>::isEmpty()) throw EmptyContainerException("Sequence is empty");
    return Position(ArrayVector<Object>::sz-1,this);
  }  
  Position before(const Position& p) const 		// return item before p
      throw(BoundaryViolationException, InvalidPositionException) {
    if (p.isNull())
      throw InvalidPositionException("Null Position");
    checkRank(p.index());
    return Position(p.index()-1,this);
  }
  Position after(const Position& p) const     // return item after p
      throw(InvalidPositionException, BoundaryViolationException) {
    if (p.isNull())
      throw InvalidPositionException("Null Position");
    checkRank(p.index());
    return Position(p.index()+1,this);
  }
  
  //============= update functions =============
  
  Position insertBefore(const Position& p, const Object& element) 
    	throw(InvalidPositionException) { // insert before p
    if (p.isNull())
      throw InvalidPositionException("Null Position");
    int index;
    checkRank(index=p.index());
    ArrayVector<Object>::insertAtRank(index,element);
    return Position(index,this);
  }
  Position insertAfter(const Position& p, const Object& element)
      throw(InvalidPositionException) {			// insert after p
    if (p.isNull())
      throw InvalidPositionException("Null Position");
    int index;
    checkRank(index=p.index());
    if (++index==ArrayVector<Object>::sz)
      return insertLast(element);
    ArrayVector<Object>::insertAtRank(index,element);
    return Position(index,this);
  }
  Position insertFirst(const Object& element) {
    ArrayVector<Object>::insertAtRank(0,element);
    return Position(0,this);    
  }
  Position insertLast(const Object& element) {
    int index;
    ArrayVector<Object>::insertAtRank(index=ArrayVector<Object>::sz,element);
    return Position(index,this); 
  }
  void remove(const Position& p)			// remove a given node
      throw(InvalidPositionException) {
    if (p.isNull())
      throw InvalidPositionException("Null Position");
    int index;
    checkRank(index=p.index());
    ArrayVector<Object>::removeAtRank(index);
  }
  void replaceElement(const Position& p, const Object& element)
      throw(InvalidPositionException) {			// replace element
    if (p.isNull())
      throw InvalidPositionException("Null Position");
    int index;
    checkRank(index=p.index());
    ArrayVector<Object>::replaceAtRank(index,element);
  }
  void swapElements(const Position& a, const Position& b)
    	throw(InvalidPositionException) {
    if (a.isNull() || b.isNull())
      throw InvalidPositionException("Null Position");
    checkRank(a.index());
    checkRank(b.index());
    Object o = a.element();
    ArrayVector<Object>::replaceAtRank(a.index(),b.element());
    ArrayVector<Object>::replaceAtRank(b.index(),o);
  }
};

template <typename Object>
typename VectorSequence<Object>::Position VectorSequence<Object>::
atRank(int rank) const 					// position of rank
    throw(BoundaryViolationException) {
  checkRank(rank);
  return Position(rank,this);
}

template <typename Object>
int VectorSequence<Object>::
rankOf(const Position &p) const 			// get rank of position
    throw(InvalidPositionException) {
  checkRank(p.index());
  return p.index();
}
#endif
