#include <stdlib.h>
#include <ctime>
#include "BinaryTree.h"
#include <iostream>
#include <deque>

int main(int argc, char* argv[]) {

  std::deque<BinaryTree<int>::NodePtr> traversal;
  BinaryTree<int> tree = BinaryTree<int>();
  clock_t start;
  clock_t end;

  // test insertLeft and insertRight
  start = clock();
  for(int i=0; i<atoi(argv[1]); i++) {
  }
  end = clock();
  cout << ((double)(end-start)/CLOCKS_PER_SEC) << ' ';

  // test preorder
  start = clock();
  for(int i=0; i<atoi(argv[1]); i++) {
    ;
  }
  end = clock();
  cout << ((double)(end-start)/CLOCKS_PER_SEC) << ' ';

  // test inorder
  start = clock();
  for(int i=0; i<atoi(argv[1]); i++) {
    ;
  }
  end = clock();
  cout << ((double)(end-start)/CLOCKS_PER_SEC) << ' ';
  
  // test simpleSearch
  start = clock();
  for(int i=0; i<atoi(argv[1]); i++) {
    ;
  }
  end = clock();
  cout << ((double)(end-start)/CLOCKS_PER_SEC) << '\n';
}
