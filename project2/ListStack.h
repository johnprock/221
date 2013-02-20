// Patrick Rock
// CSCE 221H
// 2/19/2013

//ListStack.h -- a list-based implementation of the stack
//Refer to ArrayStack.h (Stack implemenation) 
//for array based implemenation.


#ifndef LISTSTACK_H_
#define LISTSTACK_H_

#include "RuntimeException.h"

using namespace std;

template <typename Object>
class ListStack {
  public:
    class StackEmptyException : public RuntimeException {
      public:
        StackEmptyException() : RuntimeException("Access to empty stack") {}
    };

    //constructor - simply set top element to NULL and size to 0
    ListStack();

    // copy constructor
    ListStack(const ListStack& st); 

    // destructor
    ~ListStack();

    // assignment operator
    ListStack& operator=(const ListStack& st); 

    // is the stack empty?
    bool isEmpty() const {return m_size == 0;} 

    // number of elements in the stack
    size_t size() const {return m_size;}; 

    // number of elements in the stack
    size_t mySize();

    // return the top of the stack
    Object& top() throw(StackEmptyException);

    // push object onto the stack
    void push(const Object& elem); 

    // pop the stack
    Object pop() throw(StackEmptyException); 

  protected:

    // node in the NodeList
    struct Node {						
      Object  m_element; //element
      Node*   m_next;    // next node

      // constructor
      Node(const Object& e = Object(), Node* n = NULL) : m_element(e), m_next(n) {}
    };
    
    typedef Node* NodePtr; // pointer to a Node

  private:
    // member data
    size_t  m_size; // current length of stack 
    NodePtr m_head; //top of the stack
};

//constructor - simply set top element to NULL and size to 0
template <typename Object>
ListStack<Object>::ListStack() : m_head(NULL), m_size(0) {}

//copy constructor
template <typename Object>
ListStack<Object>::ListStack(const ListStack& st) {
	m_head = NULL; // initialize with default values
	m_size = 0;
	NodePtr temp;
	temp = st.m_head;
	while (temp != NULL) // same as assignment
	{
		push(temp->m_element); 
		temp = temp->m_next;
	}
}    


//destructor
template <typename Object>
ListStack<Object>::~ListStack() { 
  while(!isEmpty())
    pop(); // popped nodes are deleted
}

//assignment operator
template <typename Object>
ListStack<Object>&
ListStack<Object>::operator=(const ListStack& st) {
	NodePtr temp;
	temp = st.m_head;
	while(temp != NULL) // end of the stack is NULL
	{
		push(temp->m_element); 
		temp = temp->m_next; // step through the stack
	}
	delete temp;
}
// number of elements in the stack
// bad implementation
template <typename Object>
size_t
ListStack<Object>::mySize() {
  ListStack<Object>* temp = new ListStack<Object>();
  int c = 0;
  while(!isEmpty()) { // this reverses the order
    temp->push(pop());
    c++;
  } 
  while(!temp->isEmpty()) { // put elements back in order
    push(temp->pop());
  }
  return c;
}

// return the top of the stack
template <typename Object>
Object&
ListStack<Object>::top() throw(StackEmptyException) {
  if (isEmpty())
    throw StackEmptyException();
  return m_head->m_element;
}

// push object onto the stack
template <typename Object>
void
ListStack<Object>::push(const Object& elem) {
  Node* new_node =  new Node(elem, m_head);
  m_head = new_node; //head slides down into new node
  m_size++;
}

// pop the stack
template <typename Object>
Object
ListStack<Object>::pop() throw(StackEmptyException) {
  if (isEmpty())
    throw StackEmptyException();
	
  Object obj = m_head->m_element; //keep track of data since node is deleted
  NodePtr temp = m_head;
  m_head = m_head->m_next;
  delete temp;
  m_size--;
  return obj;
}

#endif
