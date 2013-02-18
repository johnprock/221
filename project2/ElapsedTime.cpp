// Patrick Rock
// CSCE 221H

#include<ctime>
#include<iostream>
#include"ListStack.h"

using namespace std;

int main() {
  
  ListStack<int> stack = ListStack<int>();
  clock_t start = clock();
  for(int i=0; i<10000000; i++) {
    stack.push(10);  
  }
  clock_t end = clock();

  /*
   * The number of ticks elapsed during the f() function call 
   * can be calculated by (end - start). The constant 
   * CLOCKS_PER_SEC specifies the relation between a clock tick
   * and a second (i.e. clock ticks per second). Therefore, dividing
   * (end - start) by CLOCKS_PER_SEC will give you the elapsed
   * time in seconds.
   */

  cout << "CPU elapsed time in seconds: "
    <<(double)(end - start)/CLOCKS_PER_SEC <<endl;
  cout << "Pop Stack: " << stack.pop() << '\n';
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

