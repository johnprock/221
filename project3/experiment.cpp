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

  clock_t start1;
  clock_t end1;
  clock_t start2;
  clock_t end2;
  clock_t start3;
  clock_t end3;
  clock_t start4;
  clock_t end4;


  // print test size
  cout << atoi(argv[1]) << ' ';

  // test postorder
  start1 = clock();
  for(int i=0; i<100; i++) {
    std::deque<BinaryTree<int>::NodePtr> traversal;
    tree.postorder(traversal, tree.getRoot());
  }
  end1 = clock();
  cout << ((double)(end1-start1)/(100*CLOCKS_PER_SEC)) << ' ';

  // test preorder
  start2 = clock();
  for(int i=0; i<100; i++) {
    std::deque<BinaryTree<int>::NodePtr> traversal;
    tree.preorder(traversal, tree.getRoot());
  }
  end2 = clock();
  cout << ((double)(end2-start2)/(100*CLOCKS_PER_SEC)) << ' ';

  // test inorder
  start3 = clock();
  for(int i=0; i<100; i++) {
    std::deque<BinaryTree<int>::NodePtr> traversal;
    tree.inorder(traversal, tree.getRoot());
  }
  end3 = clock();
  cout << ((double)(end3-start3)/(100*CLOCKS_PER_SEC)) << ' ';
  
  // test simpleSearch
  start4 = clock();
  for(int i=0; i<100; i++) {
    tree.simpleSearch(i);
  }
  end4 = clock();
  cout << ((double)(end4-start4)/(100*CLOCKS_PER_SEC)) << '\n';
}
