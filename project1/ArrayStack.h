// ArrayStack.h
// This class provides a template stack. Internally
// the stack is stored as an array.

#ifndef ARRAYSTACK_H_
#define ARRAYSTACK_H_

#include "RuntimeException.h"

#define CAPACITY 1000 //default capacity of the stack

template <typename Object>
class ArrayStack {
  public:
    //exception classes thrown by various functions
    class StackEmptyException : public RuntimeException {
      public:
        StackEmptyException() : RuntimeException("Access to empty stack") {}
    };

    class StackFullException : public RuntimeException {
      public:
        StackFullException() : RuntimeException("Stack overflow") {}
    };

    // constructor given max capacity
    ArrayStack(size_t cap = CAPACITY);

    // copy constructor
    ArrayStack(const ArrayStack& st); 
    
    // destructor
    ~ArrayStack() { delete [] S; } 

    // assignment operator
    ArrayStack& operator=(const ArrayStack& st); 
    
    // is the stack empty?
    bool isEmpty() const {return t < 0;} 

    // number of elements in the stack
    int size() const {return t+1;}; 

    // number of elements in the stack
    int mySize();

    // return the top of the stack
    Object& top() throw(StackEmptyException);

    // push object onto the stack
    void push(const Object& elem) throw(StackFullException);

    // pop the stack
    Object pop() throw(StackEmptyException);

  private:
    // member data
    size_t       capacity; // actual length of stack array
    Object*   S; // the stack array
    int       t; // index of the top of the stack
};

// constructor given max capacity
template <typename Object>
ArrayStack<Object>::ArrayStack(size_t cap) {
  capacity  = cap;
  S         = new Object[capacity];
  t         = -1;
}

// copy constructor
template <typename Object>
ArrayStack<Object>::ArrayStack(const ArrayStack& st) {
  //initialize internal variables
  capacity  = st.capacity;
  t         = st.t;
  S         = new Object[capacity];

  // copy contents
  for (int i = 0; i <= t; i++) {
    S[i] = st.S[i];
  }
}

// assignment operator
template <typename Object>
ArrayStack<Object>&
ArrayStack<Object>::operator=(const ArrayStack& st) {
  // avoid self copy (x = x)
  if(this != &st) {
    
    // delete old contents
    delete [] S;
    
    //initialize internal variables
    capacity  = st.capacity;
    t         = st.t;
    S         = new Object[capacity];
    
    // copy contents
    for(int i = 0; i <= t; i++) {
      S[i] = st.S[i];
    }
  }
  return *this;
}

// number of elements in the stack
template <typename Object>
int
ArrayStack<Object>::mySize() {
  /**************************************************************
   *  Complete this function using only public methods
   *  such as StackArray constructor, push(), pop() and isEmpty()
   *  (but not size()) 
   **************************************************************
   */

  ArrayStack<Object> S = ArrayStack<int>(size());
  int c = 0;
  while( !isEmpty() ) {
    S.push(pop());
    c++;
  }
  while( !S.isEmpty() ) {
    push(S.pop());
  }
  return c;
}

// return the top of the stack
template <typename Object>
Object&
ArrayStack<Object>::top() throw(StackEmptyException) {
  if (isEmpty())
    throw StackEmptyException();
  return S[t];
}

// push object onto the stack
template <typename Object>
void
ArrayStack<Object>::push(const Object& elem) throw(StackFullException) {
  if (size() == capacity) {
    throw StackFullException();
  }

  S[++t] = elem;
}

// pop the stack
template <typename Object>
Object
ArrayStack<Object>::pop() throw(StackEmptyException) {
  if (isEmpty())
    throw StackEmptyException();
  return S[t--];
}

#endif
