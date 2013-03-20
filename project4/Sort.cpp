#include <iostream>
#include "Sort.h"
#include "Comparator.h"
#include "SortedSeqPriorityQueue.h" 

int main() {

  SortedSeqPriorityQueue<int,int,Comp> s();
  s.insertItem(1,1);

  return 0;

}

