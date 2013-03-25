#include "UnsortedSeqPriorityQueue.h"
#include "Comparator.h"
#include <iostream>

using namespace std;

int main(){

  UnsortedSeqPriorityQueue<int, int, Comp> uspq;
  uspq.insertItem(1, 1);
  uspq.insertItem(2, 2);
  uspq.insertItem(3, 3);

  int i = uspq.minElement();
  uspq.removeMin();
  int j = uspq.minElement();

  cout << "First::" << i << endl;
  cout << "Second::" << j << endl;
}
