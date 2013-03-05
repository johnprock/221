// Patrick Rock
// CSCE 221H

/* BinaryTree.h:
 * A C++ template which implements a binary tree ADT.
 */
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <deque>
#include <stack>
#include "EulerTour.h"

// let the compiler know about these
template<typename Object>
class RecursiveInorder;

template<typename Object>
class RecursivePreorder;

template<typename Object>
class RecursivePostorder;

using namespace std;

template<typename Object>
class BinaryTree {


public:
  class Node {						// node in the BinaryTree
    private:
      Object element;					// element
      Node*  parent;					// parent
      Node*  leftchild;					// left child
      Node*  rightchild;				// right child
      int    depth;					// depth of node

    public:
      Node(const Object& e = Object(), Node* p = NULL, Node* l = NULL, Node* r = NULL) : element(e), parent(p), leftchild(l), rightchild(r) { 	// constructor for Node
	if(p!=NULL)
	  depth=p->depth+1;
	else depth = 0; 
      }

      Node(const Node* n) { // copy constructor
        element = n->getElement();
        depth = n->getDepth();
        parent = n->getParent();
        if(n->getLeftChild() == NULL){
          leftchild = NULL;
        }
        else {
          leftchild = new Node(n->getLeftChild());
        }
        if(n->getRightChild() == NULL){
          rightchild = NULL;
        }
        else {
          rightchild = new Node(n->getRightChild());
        }

      }

      ~Node(){	// destructor for Node
	  delete rightchild;
	  rightchild = NULL;
	  delete leftchild;
	  leftchild = NULL;
      }	
      
      //accessor functions:
      Object getElement()const{return element;}
      Node* getParent()const{return parent;}
      Node* getLeftChild()const{return leftchild;}
      Node* getRightChild()const{return rightchild;}
      int getDepth()const{return depth;}
      bool isExternal()const{return leftchild == NULL && rightchild == NULL;}

      //modifier functions
      void setElement(const Object& e){element = e;}
      void setParent(Node* p){parent = p;}
      void setLeftChild(Node* l){leftchild = l;}
      void setRightChild(Node* r){rightchild = r;}
      
  };

  typedef Node* NodePtr;				// pointer to the node
  typedef deque<NodePtr> NodeDeque;

private:
  NodePtr root;						// root of binary tree
  int size;						// number of nodes
  int depth;						// depth of tree  

public:
  BinaryTree():root(new Node()),size(0),depth(0){ }	// default constructor for BinaryTree
  BinaryTree(const Object& e):root(new Node(e)),size(1),depth(0){ }  // creates a BinaryTree and initializes the root
  ~BinaryTree(){					// destructor for BinaryTree
      delete root;
      root = NULL;
  }
  BinaryTree(const BinaryTree<Object>& b){              // copy constructor
    size =  b.getSize();
    depth = b.getDepth();
    NodePtr n = b.getRoot();
    root = new Node(n);
  }
  int getSize() const{					// return size of BinaryTree
    return size;
  }
  int getDepth() const{					// return the depth of the BinaryTree
    return depth;
  }
  bool isEmpty(){					// is the BinaryTree empty?
    return size == 0;
  }
  NodePtr getRoot() const{				// returns the root of the BinaryTree
    return root;
  }
  friend ostream &operator<<( ostream &out, BinaryTree<Object> &T ){   // prints out the tree
    deque<NodePtr> in;
    in.clear();
    T.inorder(in,T.getRoot());
    for (int i=0; i < in.size(); i++) {
      for (int j=0; j < in[i]->getDepth(); j++)
        out << "  ";
      out << in[i]->getElement() << endl;
    }
  }
  NodePtr insertLeft(NodePtr p, const Object& e);	// inserts a Node with element e to the left of p
  NodePtr insertRight(NodePtr p, const Object& e);	// inserts a Node with element e to the right of p
  void preorder(deque<NodePtr> &v,NodePtr r);		// gives a deque that contains the preorder traversal of the BinaryTree
  void inorder(deque<NodePtr> &v,NodePtr r);		// gives a deque that contains the inorder traversal of the BinaryTree
  void postorder(deque<NodePtr> &v,NodePtr r);		// gives a deque that contains the postorder traversal of the BinaryTree
  NodePtr simpleSearch(const Object& e);		// searches the BinaryTree for the element e

};

// inserts a Node with element e to the left of p
// returns NULL if element already has a left child
template <typename Object>        
typename BinaryTree<Object>::NodePtr
BinaryTree<Object>::insertLeft(NodePtr p, const Object& e) {
  
  if(p->getLeftChild() != NULL) {
    return NULL; // node already has a left child
  }
  
  Node* n = new Node(e, p);
  p->setLeftChild(n);

  // update tree internal state
  size = size+1;
  if(n->getDepth() > depth) {
    depth = n->getDepth();
  }

  return n; // return the inserted node
}

// inserts a Node with element e to the right of p
// returns NULL if element already has a right child
template <typename Object>
typename BinaryTree<Object>::NodePtr
BinaryTree<Object>::insertRight(NodePtr p, const Object& e) {
  if(p->getRightChild() != NULL) {
    return NULL;
  }

  Node* n = new Node(e, p);
  p->setRightChild(n);
 
  // update tree internal state
  size = size+1;
  if(n->getDepth() > depth) {
    depth = n->getDepth();
  }

  return n;
}

// gives a deque that contains the preorder traversal of the BinaryTree
template <typename Object>
void
BinaryTree<Object>::preorder(deque<NodePtr> &v, NodePtr r) { // recursive
  RecursivePreorder<Object> tour = RecursivePreorder<Object>(v);
  tour.eulerTour(r);
}

// gives a deque that contains the inorder traversal of the BinaryTree
template <typename Object>
void
BinaryTree<Object>::inorder(deque<NodePtr> &v, NodePtr r) { // iterative
  stack<NodePtr> in = stack<NodePtr>();
  NodePtr current = r;   //push the root on the stack

  bool c = false;
  while(!c) {
    if(current != NULL) // go to furthest left child
    {
      in.push(current);
      current = current->getLeftChild();
    }
    else {
      if(!in.empty()) { 
        current = in.top(); 
        in.pop();
        v.push_back(current);
        current = current->getRightChild(); 
      }
      else // if stack is empty we are done
        c = true;
    }
  }
}

// gives a deque that contains the postorder traversal of the BinaryTree
template <typename Object>
void
BinaryTree<Object>::postorder(deque<NodePtr> &v, NodePtr r) { // recursive
 RecursivePostorder<Object> tour = RecursivePostorder<Object>(v);
 tour.eulerTour(r);
}

// searches the BinaryTree for the element e
template <typename Object>
typename BinaryTree<Object>::NodePtr
BinaryTree<Object>::simpleSearch(const Object& e) { // generates traversal and
  deque<NodePtr> d;                                 // then searchs it
  RecursivePostorder<Object> tour = RecursivePostorder<Object>(d);
  tour.eulerTour(root);
  for(int i=0; i<d.size(); i++) {
    if(d[i]->getElement() == e)
      return d[i];
  }
  return NULL;
}

#endif

