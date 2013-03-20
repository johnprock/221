#include "Sort.h"
#include "Comparator.h"

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

bool IsSorted(NodeSequence<int>& n){
  for(int i = 0; i<n.size()-1; i++){
    if(n.elemAtRank(i) > n.elemAtRank(i+1))
        return false;
  }
  return true;
}

template<template<typename, typename> class Sort>
bool TestSort(string name){
  
  NodeSequence<int> rnd, ord, rord;
  
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
  if(!TestSort<InsertionSort>("InsertionSort"))
    passed = false;
  if(!TestSort<SelectionSort>("SelectionSort"))
    passed = false;
  if(!TestSort<QuickSortMedium>("QuickSortMedium"))
    passed = false;
  if(!TestSort<QuickSortRandom>("QuickSortRandom"))
    passed = false;
  
  if(passed)
    cout << "All tests passed." << endl;
  else
    cout << "Tests failed." << endl;

  return 0;
}
