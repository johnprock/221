#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

//#define ADJMATRIX
#ifndef ADJMATRIX
#include "Graph.h"
#else
#include "GraphWMatVer.h"
#endif

using namespace std;




template<typename G>
class Tree {

  public:

  class Node {
    
    public:
      G val;
      vector<Node*> children;
      Node* parent;
  
      Node(G x) {
        val = x;
        parent = NULL;
      }
      
      void setParent(Node* n) {
        parent = n;
      }
  };

  Node* root;

  Tree(G x) {
    root = new Node(x);
  }
};


// Disjoint Set Data Structure
template<typename G>
class Dset {

  typedef typename Tree<G>::Node node;   

  private: 
    set<Tree<G> > trees;

  public:
    void makeSet(G x) {
      Tree<G> tree(x);
      tree.root->setParent(new typename Tree<G>::Node(x));
      trees.insert(tree);
    }

    G find(typename Tree<G>::Node* x) {
      if(x->parent->val == x->val) {
        return x->val;
      }
      else {
        return find(x->parent);
      }

    }

    void unon(typename Tree<G>::Node* x, typename Tree<G>::Node* y) {
      node* xRoot = new node(find(x));
      node* yRoot = new node(find(y));
      xRoot->setParent(yRoot);
    }
};


      
      // return a vector of edges that comprise the MST
template<typename G>
vector<typename G::Edge*>
minimum_spanning_tree(G& g)
{
  typedef typename G::Edge* edge_ptr_type;
  typedef std::vector<edge_ptr_type> vector_type; 

  vector_type mst;

  // compute MST here
  // Kruskal's Algorithm 
    


  return mst;
}

template<typename G>
void populate_mesh(G& g, size_t n)
{
  // add vertices
  for (size_t i = 0; i < n*n; ++i)
    g.insertVertex('a'+i);

  typedef std::vector<typename G::Vertex*> vertices_type;
  vertices_type vert = g.vertices();
  
  // add edges
  for (size_t i = 0; i < n*n; i++)
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

  const size_t n = 3;

#ifndef ADJMATRIX
   Graph<vertex_property, edge_property> g;
#else
   Graph<vertex_property, edge_property> g(n*n);
#endif

  // add vertices and edges
  populate_mesh(g, n);
   
  // print out graph
  std::cout << "Graph:" << std::endl;
  print_edges(g.edges());

  // compute MST
  std::vector<graph_type::Edge*> mst = minimum_spanning_tree(g);

  // print out MST
  std::cout << "\nMST:" << std::endl;
  print_edges(mst);

  return 0;
}

