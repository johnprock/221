#ifndef ARRAYVECTOR_H_
#define ARRAYVECTOR_H_
#include <iostream>
#include <algorithm>
template <typename Object>
class ArrayVector {
protected:
  int           capacity;			// length of array
  int           sz;				// number of elements in vector
  Object*	a;				// array storing the elements
  void overflow();				// handle overflow by resizing
public:
  ArrayVector(int initCap = 100000) {		// constructor
    capacity    = initCap;
    sz          = 0;
    a           = new Object[capacity];
  }
  ArrayVector(const Object* b, int array_size, int initCap = 100000) {
    capacity    = std::max(array_size,initCap);
    sz          = 0;
    a           = new Object[capacity];
    for (int i=0; i<array_size; i++)
      a[i]=b[i];
    sz+=array_size;
  }
  ArrayVector(const ArrayVector& l) {                    // copy operator
    capacity = l.capacity;
    sz = l.sz;
    a = new Object[capacity];
    for (int i=0; i<sz; i++)
      a[i]=l.a[i];
  }
  ArrayVector& operator=(const ArrayVector& l) {          // assignment operator
    if (this != &l) {
      capacity = l.capacity;
      sz = l .sz;
      delete[] a;
      a = new Object[capacity];
      for (int i=0; i<sz; i++)
        a[i]=l.a[i];
    }
    return *this;
  }
  ~ArrayVector() {
    delete[] a;
  }
  int size() const  				// number of elements
    { return sz; }
  bool isEmpty() const  			// is vector empty?
    { return size() == 0; }
  Object& elemAtRank(int r) const  			// access element at rank r
    { return a[r]; }
  void replaceAtRank(int r, const Object& e)  	// replace element at given rank
    { a[r] = e; }
  void removeAtRank(int r);			// remove element at given rank
  void insertAtRank(int r, const Object& e);	// insert element at given rank
  //overload << for outputing NodeList object
  friend std::ostream& operator<<(std::ostream& out, const ArrayVector& v) {
    if (v.isEmpty())
      out << "empty";
    else
      for (int i=0; i<v.sz; i++)
        out << v.a[i] << " ";
    return out;
  }  
};

template <typename Object>
void ArrayVector<Object>::
removeAtRank(int r) {				// remove element at given rank
  for (int i = r; i < sz-1; i++)
    a[i] = a[i+1];				// shift elements down
  sz--;
}

template <typename Object>
void ArrayVector<Object>::
insertAtRank(int r, const Object& e) {		// insert element at given rank
  if (sz == capacity) overflow();		// handle overflow
  for (int i = sz-1; i >= r; i--)
    a[i+1] = a[i];				// shift elements up
  a[r] = e;
  sz++;
}

template <typename Object>
void ArrayVector<Object>::
overflow() {					// handle overflow by resizing
  capacity *= 2;				// double capacity
  Object* b = new Object[capacity];
  for (int i = 0; i < sz; i++) {		// copy contents to new array
    b[i] = a[i];
  }
  delete [] a;					// discard old array
  a = b;					// make b the new array
}
#endif
