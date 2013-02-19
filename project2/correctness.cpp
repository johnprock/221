#include "ListStack.h"

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int main(){
  //need to test correctness over all ListStack functions
  ListStack<int> l1;
  vector<int> v;

  //test correctness of pushing onto an empty list
  try{
    for(size_t i = 0; i<10000; ++i){
      int r = rand();
      l1.push(r);
      //save order of elements in an external vector to check pop order later on
      v.push_back(r);
      //checking if push and top are implemented correctly
      if(l1.size() != i+1){
        cerr << "Error::incorrect push" << endl;
        exit(1);
      }
      if(l1.top() != r){
        cerr << "Error::incorrect top/push" << endl;
        exit(1);
      }
      //checking if mySize is implemented correctly
      if(l1.mySize() != l1.size()){
        cerr << "Error::incorrect mySize()" << endl;
        exit(1);
      }
      if(l1.top() != r){
        cerr << "Error::mySize() destroyed the order" << endl;
        exit(1);
      }
    }
  }
  catch(...){
    cerr << "Error::stackEmptyException, something is amiss!" << endl;
    exit(1);
  }

  //test correctness of assignment, copy, and pop
  ListStack<int> l2;
//  l2 = l1;
  ListStack<int> l3(l2);
/*  
  //double check the order on being popped against ordering in v
  try{
    for(size_t i = 10000; i>0; --i){
      int r1 = l2.pop();
      if(l2.size() != i-1){
        cerr << "Error::pop incorrect" << endl;
        exit(1);
      }
      int r2 = l3.pop();
      if(r1 != v[i-1]){
        cerr << "Error::assignment/mySize did not preserve order or pop not correct" << endl;
        exit(1);
      }
      if(r2 != v[i-1]){
        cerr << "Error::copy constructor/mySize did not preserve order or pop not correct" << endl;
        exit(1);
      }
    }
  }
  catch(...){
    cerr << "Error::stackEmptyException, something is amiss!" << endl;
    exit(1);
  }*/
}
