// Patrick Rock
// CSCE 221H
// 3/19/2013  

#include <stdlib.h>
#include <ctime>
#include "BinaryTree.h"
#include <iostream>
#include <deque>





BinaryTree<int> generateCompleteTree(int n) // code taken from correctness.cpp
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


int main(int argc, char* argv[]) {

  if(argc < 2){
    cout << "Incorrect arguments\n";
  }

  BinaryTree<int> tree = generateCompleteTree(atoi(argv[1]));

  // test preorder
  std::deque<BinaryTree<int>::NodePtr> traversal;
  tree.preorder(traversal, tree.getRoot());

}
