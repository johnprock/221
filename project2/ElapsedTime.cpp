// Patrick Rock
// CSCE 221H

#include<ctime>
#include<iostream>
#include"ListStack.h"
#include<math.h>
#include<iomanip>

using namespace std;

int main() {
  int size; // size of stack is set at each loop iteration
  ListStack<int> stack1 = ListStack<int>();

  cout << "Size     push     pop      size     mySize\n";
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
    for(int j=0; j<size; j++) {
      stack1.size();   
    }
    clock_t endSize = clock();   

    //time mySize
    clock_t startMySize = clock();
    for(int j=0; j<size; j++) {
      stack1.mySize();   
    }
    clock_t endMySize = clock();

    //time pop
    clock_t startPop = clock();
    for(int j=0; j<size; j++) {
      stack1.pop();   
    }
    clock_t endPop = clock(); 

    //calculate average run times
    double pushTime     = ( (double)(endPush - startPush)/CLOCKS_PER_SEC ); 
    double popTime      = ( (double)(endPop - startPop)/CLOCKS_PER_SEC );
    double sizeTime     = ( (double)(endSize - startSize)/CLOCKS_PER_SEC ); 
    double mySizeTime   = ( (double)(endMySize - startMySize)/CLOCKS_PER_SEC );

    cout << size <<setw(10)<< pushTime <<setw(10)<< popTime 
      <<setw(10)<< sizeTime <<setw(10)<< mySizeTime << endl;
  }
  return 0;
}
/*/-------------------PUSH------------------//
  ListStack<int> stack1 = ListStack<int>();
  clock_t start1 = clock();
  for(int i=0; i<10000000; i++) {
    stack1.push(10);  
  }

  clock_t end1 = clock();
  cout << "Push clock, CPU elapsed time in seconds: "
    <<(double)(end1 - start1)/CLOCKS_PER_SEC <<endl;


//------------------POP-------------------//
  ListStack<int> stack2 = ListStack<int>();
  clock_t start2 = clock();
  for(int i=0; i<10000000; i++) {
    stack2.push(10);  
  }

  clock_t end2 = clock();
  cout << "Pop clock, CPU elapsed time in seconds: "
    <<(double)(end2 - start2)/CLOCKS_PER_SEC <<endl;
  cout << "Pop Stack: " << stack2.pop() << '\n';


//------------------SIZE------------------//  
  ListStack<int> stack3 = ListStack<int>();
  clock_t start3 = clock();
  for(int i=0; i<10000000; i++) {
    stack3.push(10);  
  }

  clock_t end3 = clock();
  cout << "Size clock, CPU elapsed time in seconds: "
    <<(double)(end3 - start3)/CLOCKS_PER_SEC <<endl;
  cout << "Pop Stack: " << stack3.pop() << '\n';

//----------------MY SIZE----------------//
  ListStack<int> stack4 = ListStack<int>();
  clock_t start4 = clock();
  for(int i=0; i<10000000; i++) {
    stack4.push(10);  
  }

  clock_t end4 = clock();
  cout << "mySize clock, CPU elapsed time in seconds: "
    <<(double)(end4 - start4)/CLOCKS_PER_SEC <<endl;
  cout << "Pop Stack: " << stack4.pop() << '\n';
  return 0;
}
*/

/* A way to improve the precision of measurement is to start
 * timing right after the clock ticks and also measure for many
 * times and get the average value.

// Wait for the clock to tick and record the start time
clock_t k = clock();
clock_t start;
do start = clock();
while (start == k);

// ---> call f() here <---

clock_t end=clock();

cout << "CPU elapsed time in seconds: "
<<(double)(end - start)/CLOCKS_PER_SEC <<endl;

 * Reference: 
 * A program described in	B. Stroustrup: Wrapping C++ Member Function Calls
 * "The C++ Report" June 2000
 * http://www.research.att.com/~bs/wrap_code.cpp
 */

