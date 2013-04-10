#include <iostream>
#include <map>
#include <queue>

#define ADJMATRIX
#ifndef ADJMATRIX
#include "Graph.h"
#else
#include "GraphWMatVer.h"
#endif

using namespace std;

// return a vector of vertices listed in the breadth-first search traversal order rooted at source
template<typename G>
vector<typename G::Vertex*>
BFS(G& g, typename G::Vertex* source)
{
   typedef typename G::Vertex* vertex_ptr_type;
   typedef std::vector<vertex_ptr_type> vector_type; 

   vector_type visitation;

   vector_type vertices = g.vertices();
   for (typename vector_type::iterator it = vertices.begin(); it != vertices.end(); ++it)
     (*it)->color = 0;

  std::queue<vertex_ptr_type> q;
  q.push(source);

  while (!q.empty())
  {
    vertex_ptr_type v = q.front();
    q.pop();
    if (v->color == 0)
    {
      visitation.push_back(v);
      v->color = 1;
      vector_type adj = g.adjacentVertices(v);

      for (typename vector_type::iterator u = adj.begin(); u != adj.end(); ++u)
        q.push(*u);
      
      v->color = 2;
    }
  }

   for (typename vector_type::iterator it = visitation.begin(); it != visitation.end(); ++it)
     std::cout << (*it)->element << " ";
   std::cout << std::endl;

  return visitation;
}

template<typename G>
void populate_complete(G& g, size_t n)
{
  // add vertices
  for (size_t i = 0; i < n; ++i)
    g.insertVertex('a'+i);

  typedef std::vector<typename G::Vertex*> vertices_type;
  vertices_type vert = g.vertices();

  // add edges
  for (typename vertices_type::iterator it = vert.begin(); it != vert.end(); ++it)
    for (typename vertices_type::iterator eit = vert.begin(); eit != vert.end(); ++eit)
      if (*it != *eit)
        g.insertEdge(*it, *eit, rand() % 100);
}


int main(int argc, char* argv[])
{
  typedef char vertex_property;
  typedef int edge_property;
  typedef Graph<vertex_property, edge_property> graph_type;

  const size_t n = 20;

#ifndef ADJMATRIX
   Graph<vertex_property, edge_property> g;
#else
   Graph<vertex_property, edge_property> g(n);
#endif

  // test adding vertices and edges
  populate_complete(g, n);
   
  cout << "calling BFS." << endl;
  BFS(g, g.vertices()[0]);
  cout << "done calling BFS!" << endl;

   return 0;
}

