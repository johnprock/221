#include <iostream>
#include "Graph.h"
#include "mst.h"
#include <ctime>
//#include "GraphWMatVer.h"

using namespace std;

int main(int argc, char* argv[]) {

  typedef char vertex_property;
  typedef int edge_property;
  typedef Graph<vertex_property, edge_property> graph_type;
  graph_type G;

  // read graph from a file
  if(argc == 2) {
    string file_name = argv[1];
    G.read_file(file_name);
  }

  // generate graph
  if(argc == 3) {
    const size_t n = atoi(argv[1]); //size of graph
    const int graph_shape = atoi(argv[2]); // dense or sparse
  }

  G.print();



}
