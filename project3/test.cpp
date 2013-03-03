# include "BinaryTree.h"
#include <iostream>

int main() {
  BinaryTree<int> tree = BinaryTree<int>();
  tree.insertLeft(tree.getRoot(), 1);
  tree.insertRight(tree.getRoot(), 2);
}
