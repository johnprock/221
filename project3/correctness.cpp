/* This program tests the BinaryTree implmentation */

#include "BinaryTree.h"
#include <iostream>
#include <cassert>


BinaryTree<int> generateLinkedList(int n)
{
  BinaryTree<int> T(0);
  BinaryTree<int>::Node* p = T.getRoot();
  for(int i = 0; i < n - 1; i++){
    BinaryTree<int>::Node* c = T.insertRight(p,i+1);
    p = c;
  }
  return T;
}

BinaryTree<int> generateCompleteTree(int n)
{
  BinaryTree<int> T(0);
  int I = 0;
  deque<BinaryTree<int>::NodePtr> leaves;
  deque<BinaryTree<int>::NodePtr> tmpleaves;
  leaves.push_back(T.getRoot());
  while(I < n){
    int size = leaves.size();
    tmpleaves.clear();
    for(int i=0;i<size&&I<n;i++){
      BinaryTree<int>::Node* l = T.insertLeft(leaves[i],++I);
      tmpleaves.push_back(l);
      BinaryTree<int>::Node* r = T.insertRight(leaves[i],++I);
      tmpleaves.push_back(r);      
    }
    leaves.clear();
    leaves = tmpleaves;
  }
  return T;
}


int main()
{
  BinaryTree<int> empty;
  BinaryTree<int> complete = generateCompleteTree(30);
  BinaryTree<int> list = generateLinkedList(100);

  // empty tree is empty
  assert(empty.isEmpty());

  // size of complete tree
  assert(complete.getSize() == 31);

  // size of list
  assert(list.getSize() == 100);


  // depth of complete tree
  assert(complete.getDepth() == 4);

  // depth of list
  assert(list.getDepth() == 99);


  typedef BinaryTree<int>::NodeDeque traversal_type;

  // root is at the front of a preorder traversal
  traversal_type pre;
  complete.preorder(pre, complete.getRoot());
  assert(pre.front() == complete.getRoot());

  // root is at the end of a postorder traversal
  traversal_type post;
  complete.postorder(post, complete.getRoot());
  assert(post.back() == complete.getRoot());

  // root is in the middle of an inorder traversal
  traversal_type in;
  complete.inorder(in, complete.getRoot());
  assert(in.at(in.size()/2) == complete.getRoot());


  // traversals should contain all nodes of the tree
  assert(pre.size() == complete.getSize());
  assert(post.size() == complete.getSize());
  assert(in.size() == complete.getSize());

  typedef BinaryTree<int>::NodePtr iterator;
  const int query_value = 22;

  // 22 should be in the list and complete tree
  iterator complete_query = complete.simpleSearch(query_value);
  iterator list_query = list.simpleSearch(query_value);
  iterator empty_query = empty.simpleSearch(query_value);

  assert(complete_query != NULL);
  assert(list_query != NULL);
  assert(empty_query == NULL);
  

  // test copy ctor and assignment operator
  BinaryTree<int> copied(complete);
  BinaryTree<int> assigned;
  assigned = complete;

  // should have same size
  assert(copied.getSize() == complete.getSize());
  assert(assigned.getSize() == complete.getSize());

  // should still have 22
  iterator copy_query = copied.simpleSearch(query_value);
  iterator assign_query = assigned.simpleSearch(query_value);

  assert(copy_query != NULL);
  assert(assign_query != NULL);

  std::cout << "Passed!" << std::endl;

  return 0;
}

