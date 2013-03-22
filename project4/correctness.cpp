#include "Sort.h"
#include "Comparator.h"

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

template<template<typename> class Seq>
bool IsSorted(Seq<int>& n){
  for(int i = 0; i<n.size()-1; i++){
    if(n.elemAtRank(i) > n.elemAtRank(i+1))
        return false;
  }
  return true;
}

template<template<typename, typename> class Sort, template<typename> class Seq>
bool TestSort(string name){
  
  Seq<int> rnd, ord, rord;
  
  for(size_t i = 0; i<100; i++){
    int r = rand();
    rnd.insertLast(r);
    ord.insertLast(i);
    rord.insertLast(100-i);
  }

  Sort<int, Comp> s;
  s.sort(rnd);
  s.sort(ord);
  s.sort(rord);

  bool passed = true;
  if(!IsSorted(rnd)){
    cerr << "Error: " << name << " is incorrect for random input." << endl;
    passed = false;
  }
  if(!IsSorted(ord)){
    cerr << "Error: " << name << " is incorrect for ordered input." << endl;
    passed = false;
  }
  if(!IsSorted(rord)){
    cerr << "Error: " << name << " is incorrect for reverse ordered input." << endl;
    passed = false;
  }

  return passed;
}

int main(){

  bool passed = true;
  if(!TestSort<InsertionSort, NodeSequence>("InsertionSort"))
    passed = false;
  if(!TestSort<SelectionSort, NodeSequence>("SelectionSort"))
    passed = false;
  if(!TestSort<QuickSortMedian, VectorSequence>("QuickSortMedium"))
    passed = false;
  if(!TestSort<QuickSortRandom, VectorSequence>("QuickSortRandom"))
    passed = false;
  
  if(passed)
    cout << "All tests passed." << endl;
  else
    cout << "Tests failed." << endl;

  return 0;
}
