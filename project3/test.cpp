# include "BinaryTree.h"
#include <iostream>
#include <deque>

int main() {
  
  BinaryTree<int> tree = BinaryTree<int>(0);
  tree.insertLeft(tree.getRoot(), 1);
  tree.insertRight(tree.getRoot(), 2);

  deque<BinaryTree<int>::Node*> in;
  in.clear();
  tree.inorder(in,tree.getRoot());
  
}
