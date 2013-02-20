// Patrick Rock
// CSCE 221H

#include<ctime>
#include<iostream>
#include"ListStack.h"
#include"ArrayStack.h"
#include<math.h>
#include<iomanip>

using namespace std;

int main() {
 
  // initialize local variables
  int size; // size of stack is set at each loop iteration
  ListStack<int> stack1 = ListStack<int>();
  ArrayStack<int> stack2 = ArrayStack<int>();

  // set headers for data
  cout << "Size push pop size mySize pushDouble "
    << "mySize(Array)\n";

  for(int i=0; i<25; i++) { // measure ten powers of 2
  size = pow(2,i);

    //time push
    clock_t startPush = clock();
    for(int j=0; j<size; j++) {
      stack1.push(0); // time of push is independent of pushed element  
    }
    clock_t endPush = clock();

    //time size 
    clock_t startSize = clock();
      stack1.size();   
    clock_t endSize = clock();   

    //time mySize
    clock_t startMySize = clock();
      stack1.mySize();   
    clock_t endMySize = clock();

    //time pop
    clock_t startPop = clock();
    for(int j=0; j<size; j++) {
      stack1.pop();   
    }
    clock_t endPop = clock(); 

    //time array pushDouble
    clock_t startPushDouble = clock();
    for(int j=0; j<size; j++) {
      stack2.pushDouble(0);   
    }
    clock_t endPushDouble = clock();

    //time array mySize
    clock_t startMySizeA = clock();
      stack2.mySize();   
    clock_t endMySizeA = clock();

    //calculate actual run times
    double pushTime     = ( (double)(endPush - startPush)/CLOCKS_PER_SEC ); 
    double popTime      = ( (double)(endPop - startPop)/CLOCKS_PER_SEC );
    double sizeTime     = ( (double)(endSize - startSize)/CLOCKS_PER_SEC ); 
    double mySizeTime   = ( (double)(endMySize - startMySize)/CLOCKS_PER_SEC );
    double doubleTime   = ( (double)(endPushDouble - startPushDouble)/CLOCKS_PER_SEC );
    double mySizeATime  = ( (double)(endMySizeA - startMySizeA)/CLOCKS_PER_SEC );

    //output data
    cout << size << ' ' << pushTime << ' ' << popTime 
      << ' ' << sizeTime << ' '<< mySizeTime << ' ' << doubleTime
      << ' ' << mySizeATime << endl;
  }
  return 0;
}
