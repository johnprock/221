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

	const static int N = 1; //constant used to increment array size using pushN

    // constructor given max capacity
    ArrayStack(int cap = CAPACITY);

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
  void pushBad(const Object& elem) throw(StackFullException);
	void pushConstant(const Object& elem);
	void pushDouble(const Object& elem);

    // pop the stack
    Object pop() throw(StackEmptyException);

  private:
    // member data
    int       capacity; // actual length of stack array
    Object*   S; // the stack array
    int       t; // index of the top of the stack
};

// constructor given max capacity
template <typename Object>
ArrayStack<Object>::ArrayStack(int cap) {
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
  ArrayStack<Object> S;
  int count = 0; 
  while (!this->isEmpty())
  {
	  count++;
	  S.pushDouble(this->top());
    this->pop();
  }

  while (!S.isEmpty())
  {
	  this->pushDouble(S.top());
    S.pop();
  }

  return count;
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
ArrayStack<Object>::pushBad(const Object& elem) throw(StackFullException) {
  if (size() == capacity)
    throw StackFullException();
  S[++t] = elem;
}
template <typename Object>
void ArrayStack<Object>::pushConstant(const Object& elem) {
	if (size() == capacity)
	{
		capacity += N;
		Object* T = new Object[capacity];

		for (int i = 0; i < t; ++i)
			T[i] = S[i];

		delete S;

		S = T;
	}
	S[++t] = elem;
}
template <typename Object>
void ArrayStack<Object>::pushDouble(const Object& elem) {
	if (size() == capacity)
	{
		capacity *= 2;
		Object* T = new Object[capacity];

		for (int i = 0; i < t; ++i)
			T[i] = S[i];

		delete S;

		S = T;
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
