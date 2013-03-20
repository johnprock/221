/** 
 * Item.h:
 * A C++ class template that stores a (Key, Element) pair, 
 * which is used in priority queue class template.
 * This code is excerpted from the code fragment 7.2 in
 * "Data Structures and Algorithms in C++" by M. T. Goodrich et al.
 */
#ifndef ITEM_H_
#define ITEM_H_
#include <iostream>
template <typename Key, typename Element>
class Item {					// a (key, element) pair
private:
  Key	    _key;				// key value
  Element   _elem;				// element
public:
  typedef Key key_type;
  typedef Element element_type;

  Item(const Key& k = Key(), const Element& e = Element())
    : _key(k), _elem(e) { }			// constructor
  const Key& key() const 			// gets the key (read only)
    { return _key; }
  Element& element()				// gets the element
    { return _elem; }
  const Element& element() const 		// gets the element (read only)
    { return _elem; }
  void setKey(const Key& k)			// sets the key value
    { _key = k; }
  void setElement(const Element& e)		// sets the element
    { _elem = e; }
  //overload << for printing Item object
  friend std::ostream& operator<<(std::ostream& out, const Item& item) {
    out << "(" << item._key << "," << item._elem << ")";
    return out;
  }    
};
#endif
