// Patrick Rock
// CSCE 221H

/* BinaryTree.h:
 * A C++ template which implements a binary tree ADT.
 */
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <deque>
#include "EulerTour.h"

template<typename Object>
class RecursiveInorder;

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

      ~Node(){	// destructor for Node
	  delete rightchild;
	  rightchild = NULL;
	  delete leftchild;
	  leftchild = NULL;
      }	
      
      //accessor functions:
      Object getElement(){return element;}
      Node* getParent(){return parent;}
      Node* getLeftChild(){return leftchild;}
      Node* getRightChild(){return rightchild;}
      int getDepth(){return depth;}
      bool isExternal(){return leftchild == NULL && rightchild == NULL;}

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
  int getSize() const{					// return size of BinaryTree
    return size;
  }
  int getDepth() const{					// return the depth of the BinaryTree
    return depth;
  }
  bool isEmpty(){					// is the BinaryTree empty?
    return size == 0;
  }
  NodePtr getRoot(){					// returns the root of the BinaryTree
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
  
  Node* n = new Node(e);
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

  Node* n = new Node(e);
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
BinaryTree<Object>::preorder(deque<NodePtr> &v, NodePtr r) {
}

// gives a deque that contains the inorder traversal of the BinaryTree
template <typename Object>
void
BinaryTree<Object>::inorder(deque<NodePtr> &v, NodePtr r) { 
  RecursiveInorder<Object> tour = RecursiveInorder<Object>(v);
  tour.eulerTour(r);
}

// gives a deque that contains the postorder traversal of the BinaryTree
template <typename Object>
void
BinaryTree<Object>::postorder(deque<NodePtr> &v, NodePtr r) {
 return NULL;
}

// searches the BinaryTree for the element e
template <typename Object>
typename BinaryTree<Object>::NodePtr
BinaryTree<Object>::simpleSearch(const Object& e) {
  return NULL;
}

#endif

