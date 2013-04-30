#include <iostream>
#include <map>
#include <vector>
#include <ctime>

#define ADJMATRIX
#ifndef ADJMATRIX
#include "Graph.h"
#else
#include "GraphWMatVer.h"
#endif

using namespace std;

//comparator used to sort edges
template<typename G>
class Comp {
  typedef typename G::Edge edge;
  public:
  bool operator() (edge* a, edge* b) {
    return (a->weight < b->weight);
  }

};


// Disjoint Set Data Structure
template<typename G>
class Dset {

  typedef typename G::Vertex vertex;

  private: 
    vector<vertex*> clouds;  
    map<vertex*, vertex*> cloudMap;

  public:
    void makeSet(vertex* x) {
      cloudMap[x] = x;
      clouds.push_back(x); 
    }

    void unon(vertex* x, vertex* y) {
      if(cloudMap[x] == cloudMap[y])
        return;
      else {
        for(int i=0; i<clouds.size(); i++) {
          if(cloudMap[clouds[i]] == cloudMap[y]) 
            cloudMap[clouds[i]] = cloudMap[x];
        }
      } 
    }

    vertex* find(vertex* x) {
      return cloudMap[x];    
    }

};


      
      // return a vector of edges that comprise the MST
template<typename G>
vector<typename G::Edge*>
minimum_spanning_tree(G& g)
{
  typedef typename G::Vertex vertex;
  typedef typename G::Edge* edge_ptr_type;
  typedef std::vector<edge_ptr_type> vector_type; 

  vector_type mst;
  Dset<G> clouds;
  Comp<G> comp;

  // compute MST here
  // Kruskal's Algorithm
  
  // make a cloud 
  vector<vertex*> vert = g.vertices();
  vector<edge_ptr_type> edge = g.edges();
  sort(edge.begin(), edge.end(), comp);

  for(int i=0; i<vert.size(); i++) {
    clouds.makeSet(vert[i]);
  }

  for(int i=0; i<edge.size(); i++) {
    vertex* u = edge[i]->start;
    vertex* v = edge[i]->end;
    if(clouds.find(u) != clouds.find(v)) {
      mst.push_back(edge[i]);
      clouds.unon(u,v); 
    }
  }


  return mst;
}

template<typename G>
void populate_mesh(G& g, size_t n, int density)
{
  // add vertices
  for (size_t i = 0; i < n*n; ++i)
    g.insertVertex('a'+i);

  typedef std::vector<typename G::Vertex*> vertices_type;
  vertices_type vert = g.vertices();
  
  // add edges
  for (size_t i = 0; i < (n*n/density); i++)
  {
    size_t row_start = (i/n)*n;
    size_t x = (i - row_start + 1) + row_start;
    size_t y = i+n;
      
    if (x < row_start+n)
      g.insertUndirectedEdge(vert[i], vert[x], i+x);

    if (y < n*n)
      g.insertUndirectedEdge(vert[i], vert[y], i+y);
  }
}

template<typename Vector>
void print_edges(Vector const& v)
{
  for (typename Vector::const_iterator it = v.begin(); it != v.end(); ++it)
    std::cout << "(" << (*it)->start->element << ", "
                     << (*it)->end->element << ") weight = "
                     << (*it)->weight << std::endl;
}


int main(int argc, char* argv[])
{
  typedef char vertex_property;
  typedef int edge_property;
  typedef Graph<vertex_property, edge_property> graph_type;

  const size_t n = atoi(argv[1]);
  clock_t start;
  clock_t stop;


#ifndef ADJMATRIX
   Graph<vertex_property, edge_property> g;
#else
   Graph<vertex_property, edge_property> g(n*n);
#endif

  // add vertices and edges
  populate_mesh(g, n, 1);
   
  start = clock();
  // compute MST
  std::vector<graph_type::Edge*> mst = minimum_spanning_tree(g);
  stop = clock();

  //print out time
  cout << "Time taken for computation: " <<
    ((double)(stop-start)/(CLOCKS_PER_SEC)) << endl; 

  return 0;
}

