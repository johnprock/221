#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <cmath>
#include <map>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Adjacency Matrix Version
// This version can be used for comparison purposes.
// Many of the functions may not be as efficient as the adjacency list version.
// In this graph, we're not taking into account removeVertex (assume the graph
// will only be built up) or removeEdge
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template<typename Object,typename Weight>
class Graph  {
   public:
      
      class Vertex;

      class Edge{
	 public:
	    Edge(Vertex* v,Vertex* w,Weight setweight){
	       start = v;
	       end = w;
	       v->edge.push_back(this);
	       w->inedge.push_back(this);
	       weight = setweight;
	       explored = false;
	    }
	    Edge(){
	       explored = false;
	    }
	    Weight weight;
	    Vertex* start;
	    Vertex* end;
	    bool explored;
      };

      class Vertex{
	 public:
	    Vertex(Object setelement){
	       level = 0;
	       connectedcomponent = 0;
	       element = setelement;
	       back = NULL;
	       explored = false;
	       index = -1;
         color = 0;
	    }
	    Vertex(){
	       level = 0;
	       connectedcomponent = 0;
	       back = NULL;
	       explored = false;
	       index = -1;
         color = 0;
	    }
	    void setIndex(int _ind) { index = _ind; }
	    Object element;
	    vector<Edge*> edge;
	    vector<Edge*> inedge;
	    double value;
	    unsigned int starttime, finishtime;
	    unsigned int level;
	    unsigned int connectedcomponent;
	    float rank;
	    Vertex* back;
	    bool explored;
	    //needs to be added for graph matrix representation
	    int index;
      int color;
      };	


   /////////////////////////////////////////////////////////////////////////
   private:

      vector<Edge*> edge;
      vector<Vertex*> vertex;
      unsigned int counter;
      vector<vector<Edge*> > edge_mat;
      unsigned int n;  //actual size of matrix (nxn)

   /////////////////////////////////////////////////////////////////////////
   public:
      Graph(int N);

      Graph(Graph& G);

      Graph& operator=(Graph const& G);

      ~Graph();
      void initMatrix( int N );

      void reset();
      void resetBack();
      void resetValues();
      void resetLevels();
      void resetExplored();
      void resetConnectedComponents();

      vector<Vertex*> incidentVertices(Vertex* v);
      vector<Edge*> incidentEdges(Vertex* v);
      vector<Edge*> outgoingEdges(Vertex* v);
      vector<Vertex*> adjacentVertices(Vertex* v);
      unsigned int indegree(Vertex* v);
      unsigned int outdegree(Vertex* v);
      unsigned int degree(Vertex* v);
      Vertex* startVertex(Edge* e);
      Vertex* endVertex(Edge* e);
      // is there an edge from v to w ?
      bool isAdjacent(Vertex* v,Vertex* w);

      Vertex* insertVertex(Object o);
      void insertEdge(Vertex* v,Vertex* w,Weight t);
      void insertUndirectedEdge(Vertex* v,Vertex* w,Weight t);
/*
      void removeVertex(Vertex* v);
      void removeEdge(Edge* e);
*/

      unsigned int numVertices();
      unsigned int numEdges();
      vector<Vertex*> vertices();
      vector<Edge*> edges();

      void print();
      /////////////////////////////////////////////////////////////////////////

      typedef Object object_type;
      typedef Weight weight_type;
};



template<typename Object,typename Weight>
Graph<Object,Weight>::Graph(int N){

   // Set up sizes. (nx n) -- doesn't expand beyond what is initially created
   n=N;
   initMatrix(n);
}

template<typename Object, typename Weight>
void Graph<Object,Weight>::initMatrix(int N) {
   edge_mat.resize(n);
   for (int i = 0; i < n; ++i)
      edge_mat[i].resize(n);

   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
	 edge_mat[i][j]=NULL; //setall to null
}

template<typename Object,typename Weight>
Graph<Object,Weight>::Graph(Graph<Object,Weight>& G) : n(G.n)
{
   std::map<typename Graph<Object,Weight>::Vertex*, typename Graph<Object,Weight>::Vertex*> vertex_mapping;

   size_t index = 0;
   for (typename vector<typename Graph<Object,Weight>::Vertex*>::iterator it = G.vertex.begin(); it != G.vertex.end(); ++it, ++index)
   {
      Vertex* v = new Vertex(**it);
      vertex_mapping[*it] = v;
      v->setIndex(index);
      vertex.push_back(v);
   }

   initMatrix(n);

   for (typename vector<typename Graph<Object,Weight>::Edge*>::iterator it = G.edge.begin(); it != G.edge.end(); ++it)
     insertEdge(vertex_mapping[(*it)->start], vertex_mapping[(*it)->end], (*it)->weight);
}

template<typename Object,typename Weight>
Graph<Object,Weight>::~Graph(){
  for (typename vector<typename Graph<Object,Weight>::Edge*>::iterator it = this->edge.begin(); it != this->edge.end(); ++it)
    delete *it;

  for (typename vector<typename Graph<Object,Weight>::Vertex*>::iterator it = this->vertex.begin(); it != this->vertex.end(); ++it)
    delete *it;
}

template<typename Object,typename Weight>
Graph<Object,Weight>& Graph<Object,Weight>::operator=(Graph<Object,Weight> const& other){
  if (this == &other)
    return *this;

  for (typename vector<typename Graph<Object,Weight>::Edge*>::iterator it = this->edge.begin(); it != this->edge.end(); ++it)
    delete *it;

  for (typename vector<typename Graph<Object,Weight>::Vertex*>::iterator it = this->vertex.begin(); it != this->vertex.end(); ++it)
    delete *it;

  n = other.n;

  std::map<typename Graph<Object,Weight>::Vertex*, typename Graph<Object,Weight>::Vertex*> vertex_mapping;

  size_t index = 0;
  for (typename vector<typename Graph<Object,Weight>::Vertex*>::iterator it = other.vertex.begin(); it != other.vertex.end(); ++it, ++index)
  {
    Vertex* v = new Vertex(**it);
    vertex_mapping[*it] = v;
    v->setIndex(index);
    vertex.push_back(v);
  }

  initMatrix(n);

  for (typename vector<typename Graph<Object,Weight>::Edge*>::iterator it = other.edge.begin(); it != other.edge.end(); ++it)
    insertEdge(vertex_mapping[(*it)->start], vertex_mapping[(*it)->end], (*it)->weight);

}

template<typename Object,typename Weight> 
void Graph<Object,Weight>::reset(){
   counter = 0;
   resetBack();
   resetValues();
   resetLevels();
   resetExplored();
   resetConnectedComponents();
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::resetBack(){
   for(unsigned int i=0;i<vertex.size();i++)
      vertex[i]->back = NULL;
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::resetValues(){
   for(unsigned int i=0;i<vertex.size();i++)
      vertex[i]->value = INT_MAX;
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::resetLevels(){
   for(unsigned int i=0;i<vertex.size();i++)
      vertex[i]->level = 0;
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::resetExplored(){
   for(unsigned int i=0;i<vertex.size();i++)
      vertex[i]->explored = false;
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::resetConnectedComponents(){
   for(unsigned int i=0;i<vertex.size();i++)
      vertex[i]->connectedcomponent = 0;
}

template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Vertex*> Graph<Object,Weight>::incidentVertices(Vertex* v){
   vector<Vertex*> result;
   //run through column in matrix to see if edge exists that comes into v
   //and if does add to incoming edges' start (cause end should be v)
   int v_index = v->index;
   for(unsigned int i=0;i<n;i++) {
      if( edge_mat[i][v_index] != NULL ) {
	 Edge* e = edge_mat[i][v_index];
	 result.push_back(e->start);
      }
   }
   return result;
}
template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Edge*> Graph<Object,Weight>::incidentEdges(Vertex* v){
   vector<Edge*> in_edges;
   //run through column in matrix to see if edge exists
   //and if does add to incoming edges
   int v_index = v->index;
   for(unsigned int i=0;i<n;i++) {
      if( edge_mat[i][v_index] != NULL ) {
	 Edge* e = edge_mat[i][v_index];
	 in_edges.push_back(e);
      }
   }
   return in_edges;
}



template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Edge*> Graph<Object,Weight>::outgoingEdges(Vertex* v){
   vector<Edge*> out_edges;
   //run through row in matrix to see if edge exists
   //and if does add to outgoing edges
   int v_index = v->index;
   for(unsigned int i=0;i<n;i++) {
      if( edge_mat[v_index][i] != NULL ) {
	 Edge* e = edge_mat[v_index][i];
	 out_edges.push_back(e);
      }
   }
   return out_edges;
}

template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Vertex*> Graph<Object,Weight>::adjacentVertices(Vertex* v){
   vector<Vertex*> result;
   //run through row in matrix to see if edge exists
   //and if does add to adjacent vertices (the end vertex)
   int v_index = v->index;
   for(unsigned int i=0;i<n;i++) {
      if( edge_mat[v_index][i] != NULL ) {
	 Edge* e = edge_mat[v_index][i];
	 result.push_back(e->end);
      }
   }
   return result;
}


template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::outdegree(Vertex* v){
   vector<Edge*> out_edges = outgoingEdges(v);
   return out_edges.size();
}

template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::indegree(Vertex* v){
   vector<Edge*> in_edges = incidentEdges(v);
   return in_edges.size();
}

template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::degree(Vertex* v){
   return indegree(v) + outdegree(v);
}

template<typename Object,typename Weight>
typename Graph<Object,Weight>::Vertex* Graph<Object,Weight>::startVertex(Edge* e){
   return e->start;
}

template<typename Object,typename Weight>
typename Graph<Object,Weight>::Vertex* Graph<Object,Weight>::endVertex(Edge* e){
   return e->end;
}

// is there an edge from v to w ?
template<typename Object,typename Weight>
bool Graph<Object,Weight>::isAdjacent(Vertex* v,Vertex* w){
   unsigned int v_index = v->index;
   unsigned int w_index = w->index;
   if(edge_mat[v_index][w_index] != NULL)
      return true;
   else
      return false;
}

template<typename Object,typename Weight>
typename Graph<Object,Weight>::Vertex* Graph<Object,Weight>::insertVertex(Object o){
   int cursize = vertex.size();
   Vertex* vert = new Vertex(o);
   vert->setIndex(cursize);
   vertex.push_back(vert);
   return vert;
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::insertEdge(Vertex* v,Vertex* w,Weight t){
   Edge* e = new Edge(v,w,t);
   edge.push_back(e);
   int v_index = v->index;
   int w_index = w->index;
   edge_mat[v_index][w_index] = e;
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::insertUndirectedEdge(Vertex* v,Vertex* w,Weight t){
   insertEdge(v,w,t);
   insertEdge(w,v,t);
}

/*
template<typename Object,typename Weight>
void Graph<Object,Weight>::removeEdge(Edge* e){
   for(unsigned int i=0;i<e->start->edge.size();i++)
      if(e == e->start->edge[i]){
	 e->start->edge.erase(e->start->edge.begin()+i);
	 break;
      }
   for(unsigned int i=0;i<e->end->inedge.size();i++)
      if(e == e->end->inedge[i]){
	 e->end->inedge.erase(e->end->inedge.begin()+i);
	 break;
      }
   for(unsigned int i=0;i<edge.size();i++)
      if(e == edge[i]){
	 edge(edge.begin()+i);
	 break;
      }
}


template<typename Object,typename Weight>
void Graph<Object,Weight>::removeVertex(Vertex* v){
}
*/

template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::numVertices(){
   return vertex.size();
}

template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::numEdges(){
   return edge.size();
}

template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Vertex* > Graph<Object,Weight>::vertices(){
   return vertex;
}

template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Edge* > Graph<Object,Weight>::edges(){
   return edge;
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::print(){
   cout << "vertices:" << endl;
   for(unsigned int i=0;i<vertex.size();i++)
      cout << vertex[i]->element << endl;
   cout << "edges:" << endl;
   for(unsigned int i=0;i<edge.size();i++)
      cout << "(" << edge[i]->start->element << "," << edge[i]->end->element << " wt: " << edge[i]->weight<< ")" << endl;

   bool showMat=true;
   if(showMat)
   for(unsigned int i=0; i<n; i++) {
      cout << "| "<<flush;
      for(unsigned int j=0; j<n; j++) {
	 if( edge_mat[i][j] != NULL ) {
	    Edge* e = edge_mat[i][j];
	    cout.width(6);
	    cout << left << e->weight << " "<<flush;
	 }
	 else {
	    cout.width(6);
	    cout << left << "-"<<flush;
	 }
      }
      cout << "\t|" << endl;
   }
}



/*template<typename Object, typename Weight>
void Graph<Object,Weight>::read_file(std::string filename) {
  string data;

  ifstream infile;
  infile.open(filename.c_str());
  
  infile >> data;
  vcounter = atoi(data.c_str());
  
  for(int i=0; i<vcounter; i++) {
    insertVertex(Object());
  }

  while(!infile.eof()) {
    int v;
    int w;
    int weight;
    infile >> data;
    v = atoi(data.c_str());
    infile >> data;
    w = atoi(data.c_str());
    infile >> data;
    weight = atoi(data.c_str());

    insertEdge(vertex[v],vertex[w],weight);
  }

  infile.close();
}*/

#endif




