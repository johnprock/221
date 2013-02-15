///////////////////////////////////////////////////////////////////////
//
//  CSCE 221H - Example experimental setup
//
//  Runs STL's accumulate over a set of random doubles in a vector.
//
//  created:  2009.01.26
//  modified: 2010.01.24
//
//////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>   //for setprecision
#include <vector>
#include <algorithm> //for generate
#include <numeric>   //for accumulate
#include <ctime>     //for clock

using namespace std;

// Runs the accumulation test on _size input.  Averages the running time 
// over _num_itr iterations, and returns the average time.
double RunTest(size_t _size, int _num_itr);

int main(int argc, char** argv) {
  size_t lower = 2;
  size_t upper = 200000000;

  if (argc >= 3) {
     lower = atoi(argv[1]);
	 upper = atoi(argv[2]);
  }
  
  cout << setprecision(10);
  cout << "Sum, Size, Time(sec)" << endl;

  size_t size = lower;
  while( size <= upper) {
    cout << size << ", " << RunTest(size,10+int(10000000/size)) << endl;
    size *=2;
  }

  return 0;
}


double RunTest(size_t _size, int _num_itr) {

  //create vector, allocating _size elements
  vector<double> random_vector(_size);

  //randomly generate input data
  generate(random_vector.begin(), random_vector.end(), rand);

  //begin timing
  clock_t k=clock();
  clock_t start;
  do start = clock();  //begin at new tick
  while (start == k);


  //Run accumulate _num_itr times
  double sum(0.0);
  for(int i=0; i<_num_itr; ++i) {
    sum += accumulate(random_vector.begin(), random_vector.end(), double(0.0));
  }

  //end timing
  clock_t end = clock();

  cout << sum << ", ";

  double elapsed_time = double(end - start) / double(CLOCKS_PER_SEC);
  return elapsed_time / double(_num_itr);

}
