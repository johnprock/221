#ifndef EULERTOUR_H
#define EULERTOUR_H
#include "BinaryTree.h"

template<typename E>
class BinaryTree;

template <typename E>
class EulerTour
{ 

protected:
  typedef BinaryTree<E> Tree; 
  typedef typename Tree::NodePtr NodePtr; // a position in the tree

public:
 void eulerTour(NodePtr r);
protected:
 virtual void visitExternal(NodePtr p) {} 
 virtual void visitLeft(NodePtr p) {} 
 virtual void visitBelow(NodePtr p) {} 
 virtual void visitRight(NodePtr p) {} 
};

template <typename E> // do the tour 
void EulerTour<E>::eulerTour(NodePtr p) {
  if (p == NULL)
    return;

  if (p->isExternal()) { 
    visitExternal(p);

  } else { 
    visitLeft(p); 
    eulerTour(p->getLeftChild()); 
    visitBelow(p); 
    eulerTour(p->getRightChild()); 
    visitRight(p);
  }
}

template<typename E>
class RecursiveInorder : public EulerTour<E>
{
  std::deque<typename EulerTour<E>::NodePtr>& d;

public:
  RecursiveInorder(std::deque<typename EulerTour<E>::NodePtr>& de)
    : d(de) 
  {};

  virtual void visitExternal(typename EulerTour<E>::NodePtr p)
  {
    d.push_back(p);
  }

  virtual void visitBelow(typename EulerTour<E>::NodePtr p)
  {
    d.push_back(p);
  }
};


template<typename E>
class RecursivePreorder : public EulerTour<E>
{
  std::deque<typename EulerTour<E>::NodePtr>& d;

public:
  RecursivePreorder(std::deque<typename EulerTour<E>::NodePtr>& de)
    : d(de)
    {};

  virtual void visitExternal(typename EulerTour<E>::NodePtr p)
  {
    d.push_back(p);
  }

  virtual void visitRight(typename EulerTour<E>::NodePtr p)
  {
    d.push_back(p);
  }
};


#endif
