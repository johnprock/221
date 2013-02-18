// Patrick Rock
// CSCE 221H

#include<ctime>
#include<iostream>
#include"ListStack.h"

using namespace std;

int main() {
  
//-------------------PUSH------------------//
  ListStack<int> stack1 = ListStack<int>();
  clock_t start1 = clock();
  for(int i=0; i<10000000; i++) {
    stack1.push(10);  
  }

  clock_t end1 = clock();
  cout << "CPU elapsed time in seconds: "
    <<(double)(end1 - start1)/CLOCKS_PER_SEC <<endl;
  cout << "Pop Stack: " << stack1.pop() << '\n';


//------------------POP-------------------//
  ListStack<int> stack2 = ListStack<int>();
  clock_t start2 = clock();
  for(int i=0; i<10000000; i++) {
    stack2.push(10);  
  }

  clock_t end2 = clock();
  cout << "CPU elapsed time in seconds: "
    <<(double)(end2 - start2)/CLOCKS_PER_SEC <<endl;
  cout << "Pop Stack: " << stack2.pop() << '\n';


//------------------SIZE------------------//  
  ListStack<int> stack3 = ListStack<int>();
  clock_t start3 = clock();
  for(int i=0; i<10000000; i++) {
    stack3.push(10);  
  }

  clock_t end3 = clock();
  cout << "CPU elapsed time in seconds: "
    <<(double)(end3 - start3)/CLOCKS_PER_SEC <<endl;
  cout << "Pop Stack: " << stack3.pop() << '\n';

//----------------MY SIZE----------------//
  ListStack<int> stack4 = ListStack<int>();
  clock_t start4 = clock();
  for(int i=0; i<10000000; i++) {
    stack4.push(10);  
  }

  clock_t end4 = clock();
  cout << "CPU elapsed time in seconds: "
    <<(double)(end4 - start4)/CLOCKS_PER_SEC <<endl;
  cout << "Pop Stack: " << stack4.pop() << '\n';
  return 0;
}


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

