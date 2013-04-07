#include <iostream>
#include "Sort.h"
#include "Comparator.h"
#include <ctime>

using namespace std;



NodeSequence<int> gen_random_node(int size) {
  NodeSequence<int> ns;
  for(int i=0; i<size; i++) {
    ns.insertLast(rand());
  }
  return ns;
}

VectorSequence<int> gen_random_vect(int size) {
  VectorSequence<int> vs;
  for(int i=0; i<size; i++) {
    vs.insertLast(rand());
  }
  return vs;
}

NodeSequence<int> gen_reverse_node(int size) {
  NodeSequence<int> ns;
  for(int i=0; i<size; i++) {
    ns.insertFirst(i);
  }
  return ns;
}

VectorSequence<int> gen_reverse_vect(int size) {
  VectorSequence<int> vs;
  for(int i=0; i<size; i++) {
    vs.insertFirst(i);
  }
  return vs;
}

NodeSequence<int> gen_sorted_node(int size) {
  NodeSequence<int> ns;
  for(int i=0; i<size; i++) {
    ns.insertLast(i);
  }
  return ns;
}

VectorSequence<int> gen_sorted_vect(int size) {
  VectorSequence<int> vs;
  for(int i=0; i<size; i++) {
    vs.insertLast(i);
  }
  return vs;
}

clock_t test(int sort, int inp, int size) { // times a given sort and input

  InsertionSort<int, Comp>    ins;
  HeapSort<int, Comp>         heap;
  SelectionSort<int, Comp>    selec;
  MergeSort<int, Comp>        merge;
  QuickSortLast<int, Comp>    qlast;
  QuickSortMedian<int, Comp>  qmed;
  QuickSortRandom<int, Comp>  qrand;
  RadixSort<int, Comp>        radix;

  NodeSequence<int> ns;
  VectorSequence<int> vs;
  clock_t start;
  clock_t stop;

  switch(inp) {
    case 1: 
      ns = gen_random_node(size);
      vs = gen_random_vect(size);
      break;
    case 2:
      ns = gen_reverse_node(size);
      vs = gen_reverse_vect(size);
      break;
    case 3:
      ns = gen_sorted_node(size);
      vs = gen_sorted_vect(size);
      break;
  }

  start = clock();
  switch(sort) {
    case 1: ins.sort(ns);     break;
    case 2: heap.sort(ns);    break;
    case 3: selec.sort(ns);   break;
    case 4: merge.sort(ns);   break;
    case 5: qlast.sort(vs);   break;
    case 6: qmed.sort(vs);    break;
    case 7: qrand.sort(vs);   break;
    case 8: radix.sort(vs);   break;
  }
  stop = clock();
  
  cout << ((double)(stop-start)/(CLOCKS_PER_SEC));

}



int main(int argc, char* argv[]) {

  int size = atoi(argv[1]);
  int sort = atoi(argv[2]);
  int type = atoi(argv[3]);

  for(int i=100; i<size; i+=100) {
    cout << i << ";";
    test(sort,type,i);
    cout << endl;
  }
    cout << endl;
  
  
}







