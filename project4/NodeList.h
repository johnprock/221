/* NodeList.h:
 * A C++ template which implements the List ADT.
 * Most of the code is excerpted from 
 * the code fragment 5.5, 5.6, 5.7 and 5.10 in
 * "Data Structures and Algorithms in C++"
 * by M. T. Goodrich et al.
 */
#ifndef NODELIST_H_
#define NODELIST_H_
#include <iostream>
#include "RuntimeException.h"
template <typename Object>
class NodeList {
protected: 
  struct Node {						// node in the NodeList
    Object  element;					// element
    Node*   prev;					// previous node
    Node*   next;					// next node
    Node(const Object& e = Object(), Node* p = NULL, Node* n = NULL)
        : element(e), prev(p), next(n) { }      	// constructor
  };
  typedef Node* NodePtr;				// pointer to a Node
public:
  class Position {					// position in NodeList
  private:
    NodePtr node;					// pointer to the node
  public:
    Position(NodePtr n = NULL)				// constructor
      { node = n; }
    Object& element() const 				// return element
         throw(InvalidPositionException) {
      if (node == NULL) throw InvalidPositionException("Null position");
      return node->element;
    }
    bool isNull() const 				// a null position?
      { return node == NULL; }
    friend class NodeList<Object>;			// allow access
    //overload << for outputing Position object
    friend std::ostream& operator<<(std::ostream& out, const Position& p) {
      if (p.isNull())
        out << "null";
      else
        out << p.element();
      return out;
    }
  };
protected:                          // utility to convert Position to node pointer
  NodePtr nodePtr(const Position& p) const throw(InvalidPositionException) {
    if (p.node == NULL)
      throw InvalidPositionException("Attempt to use null position");
    else return p.node;
  }
protected: 						// data members
  int       sz;        					// number of items
  NodePtr   header;					// head of list sentinel
  NodePtr   trailer;					// tail of list sentinel
public:
  NodeList() {						// default constructor
    sz = 0;
    header   = new Node;				// create sentinels
    trailer  = new Node;
    header->next   = trailer;				// head points to trailer
    trailer->prev  = header;				// trailer points to head
  }
  NodeList(const Object* a, int array_size) {          // additional constructor by array
    sz = 0;
    header   = new Node;				// create sentinels
    trailer  = new Node;
    header->next   = trailer;				// head points to trailer
    trailer->prev  = header;				// trailer points to head
    for (int i=0; i<array_size; i++)
      insertLast(a[i]);
  }  
  NodeList(const NodeList& l) {          // copy constructor
    sz = 0;
    header   = new Node;				// create sentinels
    trailer  = new Node;
    header->next   = trailer;				// head points to trailer
    trailer->prev  = header;				// trailer points to head
    NodePtr p=l.header->next;
    while (p!=l.trailer) {
      insertLast(p->element);
      p=p->next;
    }
  }
  NodeList& operator=(const NodeList& l)           // assignment operator
    {
      if (this != &l) { // avoid self copying (x = x)
        NodePtr p=header->next;
        while (p!=trailer) {
          delete p->prev;
          p=p->next;
        }
        delete trailer->prev;
        delete trailer;
        sz = 0;
        header   = new Node;				// create sentinels
        trailer  = new Node;
        header->next   = trailer;				// head points to trailer
        trailer->prev  = header;				// trailer points to head
        p=l.header->next;
        while (p!=l.trailer) {
          insertLast(p->element);
          p=p->next;
        }
      }
      return *this;
    }
  ~NodeList() {     // destructor
    NodePtr p=header->next;
    while (p!=trailer) {
      delete p->prev;
      p=p->next;
    }
    delete trailer->prev;
    delete trailer;
  }   
  
  //============= query functions =============
  
  int size() const 					// list size
    { return sz; }
  bool isEmpty() const 					// is the list empty?
    { return (sz == 0); }
  bool isFirst(const Position& p) const 		// is this the first?
      throw(InvalidPositionException) {
    NodePtr v = nodePtr(p);
    return v->prev == header;
  }
  bool isLast(const Position& p) const 			// is this the last?
      throw(InvalidPositionException) {
    NodePtr v = nodePtr(p);
    return v->next == trailer;
  }
  
  //============= accessor functions =============
  
  Position first() const 				// return first element
      throw(EmptyContainerException) {
    if (isEmpty()) throw EmptyContainerException("List is empty");
    return Position(header->next);
  }
  Position last() const 				// return last element
      throw(EmptyContainerException) {
    /* not in the text; complete this function */
    if (isEmpty()) throw EmptyContainerException("List is empty");
    return Position(trailer->prev);
  }  
  Position before(const Position& p) const 		// return item before p
      throw(BoundaryViolationException, InvalidPositionException) {
    NodePtr v = nodePtr(p);
    NodePtr prev = v->prev;
    if (prev == header)
      throw BoundaryViolationException("Advance past beginning of list");
    return Position(prev);
  }
  Position after(const Position& p) const     // return item after p
      throw(InvalidPositionException, BoundaryViolationException) {
    /* not in the text; complete this function */
    NodePtr v = nodePtr(p);
    NodePtr next = v->next;
    if (next == trailer)
      throw BoundaryViolationException("Advance past end of list");
    return Position(next);
  }
  
  //============= update functions =============
  
  Position insertBefore(const Position& p, const Object& element) 
    	throw(InvalidPositionException) { // insert before p
    /* not in the text; complete this function */
    NodePtr v = nodePtr(p);
    sz++;
    NodePtr newNode  = new Node(element, v->prev, v);
    v->prev->next    = newNode;				// link node into list
    v->prev	     = newNode;
    return Position(newNode);    
  }
  Position insertAfter(const Position& p, const Object& element)
      throw(InvalidPositionException) {			// insert after p
    NodePtr v = nodePtr(p);
    sz++;
    NodePtr newNode  = new Node(element, v, v->next);
    v->next->prev    = newNode;				// link node into list
    v->next	     = newNode;
    return Position(newNode);
  }
  Position insertFirst(const Object& element) {
    /* not in the text; complete this function */
    sz++;
    NodePtr newNode  = new Node(element, header, header->next);
    header->next->prev    = newNode;				// link node into list
    header->next	     = newNode;
    return Position(newNode);    
  }
  Position insertLast(const Object& element) {
    /* not in the text; complete this function */
    sz++;
    NodePtr newNode  = new Node(element, trailer->prev, trailer);
    trailer->prev->next    = newNode;				// link node into list
    trailer->prev	     = newNode;
    return Position(newNode); 
  }
  void remove(const Position& p)			// remove a given node
      throw(InvalidPositionException) {
    sz--;
    NodePtr v = nodePtr(p);
    v->prev->next    = v->next;				// unlink from the list
    v->next->prev    = v->prev;
    delete v;
  }
  void replaceElement(const Position& p, const Object& element)
      throw(InvalidPositionException) {			// replace element
    NodePtr v  = nodePtr(p);
    v->element = element;
  }
  void swapElements(const Position& a, const Position& b)
    	throw(InvalidPositionException) {
    /* not in the text; complete this function */
    NodePtr v = nodePtr(a);
    NodePtr u = nodePtr(b);
    Object  element=v->element;
    v->element=u->element;
    u->element=element;
  }
  //overload << for outputing NodeList object
  friend std::ostream& operator<<(std::ostream& out, const NodeList& l) {
    if (l.isEmpty())
      out << "empty";
    else {
      Position p=l.first();
      while (!l.isLast(p)) {
        out << p << " ";
        p = l.after(p);
      }
      out << p;
    }
    return out;
  }
};
#endif
