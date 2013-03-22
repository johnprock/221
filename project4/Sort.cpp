#include <iostream>
#include "Sort.h"
#include "Comparator.h"
#include "SortedSeqPriorityQueue.h" 

using namespace std;

int main() {

  
  InsertionSort<int, Comp> s;
  NodeSequence<int> n;
  n.insertFirst(0);
  n.insertFirst(1);
  n.insertFirst(-1);
  s.sort(n);

  cout << n;

  return 0;
}

