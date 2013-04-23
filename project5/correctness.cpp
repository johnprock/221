#include <iostream>
#include <cassert>
#include <fstream>

//#include "GraphWMatVer.h"
#include "Graph.h"

void print(Graph<double,double>::Vertex* v)
{
  std::cout << v->element << ", " << v->level << ", " << v->starttime << ", " << v->finishtime << std::endl;
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


template<typename Graph>
struct edge_equal
{
  Graph* m_g;
  typename Graph::Vertex* m_v;
  bool m_end;

  edge_equal(Graph* g, typename Graph::Vertex* v, bool end)
   : m_g(g), m_v(v), m_end(end)
  { }

  bool operator()(typename Graph::Edge* const& e)
  {
    return (m_end ? m_g->endVertex(e) : m_g->startVertex(e)) == m_v;
  }
};



int main(int argc, char* argv[])
{
  typedef char vertex_property;
  typedef int edge_property;
  typedef Graph<vertex_property, edge_property> graph_type;

  const size_t n = 20;
  graph_type g;

  // test adding vertices and edges
  populate_complete(g, n);

  // test number of vertices
  assert(("Size of graph is incorrect", g.numVertices() == n));

  // test number of edges
  assert(("Number of edges is incorrect", g.numEdges() == n*n-n));

  // get vertices
  typedef std::vector<graph_type::Vertex*> vertices_type;
  vertices_type vert = g.vertices();

  bool passed = true;

  // test adjacency of every vertex
  for (vertices_type::iterator it = vert.begin(); it != vert.end(); ++it)
    for (vertices_type::iterator eit = vert.begin(); eit != vert.end(); ++eit)
      if (*it != *eit)
        passed &= g.isAdjacent(*it, *eit);
      else
        passed &= !g.isAdjacent(*it, *eit);

  assert(("Adjacency information incorrect", passed));


  // grab random vertex v
  graph_type::Vertex* v = vert.front();

  // test degrees of v
  assert(("In-degree incorrect", g.indegree(v) == n-1));
  assert(("Out-degree incorrect", g.outdegree(v) == n-1));
  assert(("Degree incorrect", g.degree(v) == 2*(n-1)));


  // test incident vertices of v
  vertices_type incident = g.incidentVertices(v);
  passed = true;

  // make sure every vertex (except v) appears exactly once in list of incident vertices
  for (vertices_type::iterator it = vert.begin(); it != vert.end(); ++it)
    if (*it != v)
      passed &= std::count(incident.begin(), incident.end(), *it) == 1;

  assert(("Incident vertices incorrect", passed));


  // test adjacent vertices of v
  vertices_type adjacent = g.adjacentVertices(v);
  passed = true;

  // make sure every vertex (except v) appears exactly once in list of adjacent vertices
  for (vertices_type::iterator it = vert.begin(); it != vert.end(); ++it)
    if (*it != v)
      passed &= std::count(adjacent.begin(), adjacent.end(), *it) == 1;

  assert(("Adjacent vertices incorrect", passed));


  // get outgoing edges of v
  typedef std::vector<graph_type::Edge*> edges_type;
  edges_type out_edges = g.outgoingEdges(v);
  passed = true;

  // make sure every vertex (except v) appears exactly once as the target of an outgoing edge of v
  for (vertices_type::iterator it = vert.begin(); it != vert.end(); ++it)
    if (*it != v)
      passed &= std::count_if(out_edges.begin(), out_edges.end(), edge_equal<graph_type>(&g, *it, true)) == 1;

  assert(("Outgoing edges or endVertex incorrect", passed));

  // make sure the source of all outgoing edges is v
  passed = std::count_if(out_edges.begin(), out_edges.end(), edge_equal<graph_type>(&g, v, false)) == out_edges.size();

  assert(("Outgoing edges or startVertex incorrect", passed));


  // get incident edges of v
  typedef std::vector<graph_type::Edge*> edges_type;
  edges_type in_edges = g.incidentEdges(v);
  passed = true;

  // make sure every vertex (except v) appears exactly once as the source of an incident edge of v
  for (vertices_type::iterator it = vert.begin(); it != vert.end(); ++it)
    if (*it != v)
      passed &= std::count_if(in_edges.begin(), in_edges.end(), edge_equal<graph_type>(&g, *it, false)) == 1;

  assert(("Incident edges or startVertex incorrect", passed));

  // make sure the target of all incident edges is v
  passed = std::count_if(in_edges.begin(), in_edges.end(), edge_equal<graph_type>(&g, v, true)) == in_edges.size();

  assert(("Incident edges or endVertex incorrect", passed));


  // create copy of graph
  graph_type copy(g);

  assert(("Size of copy incorrect", g.numVertices() == copy.numVertices() && g.numEdges() == copy.numEdges()));


  // test reading in from a file
  
  cout << "Testing file read.\n";
  graph_type g_file;
  cout << "Graph constructed\n";
  std::string filename = "power.g";
  
  cout << "Reading in graph...\n";
  g_file.read_file(filename);
  cout << " done.\n";

  ifstream stream;
  stream.open(filename.c_str());
  int num_vertices;
  stream >> num_vertices;

  assert(("Size of graph from file incorrect", num_vertices == g_file.numVertices()));

  std::cout << "All tests passed!" << std::endl;

  return 0;
}

