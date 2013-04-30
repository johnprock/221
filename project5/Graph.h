#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>

using namespace std;

template<typename Object,typename Weight>
class Graph{
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
	    }
	    Vertex(){
	       level = 0;
	       connectedcomponent = 0;
	       back = NULL;
	       explored = false;
	    }
	    Object element;
	    vector<Edge*> edge;
	    vector<Edge*> inedge;
	    double value;
	    unsigned int starttime, finishtime;
	    unsigned int level;
	    unsigned int connectedcomponent;
	    float rank;
	    Vertex* back;
      int color;
	    bool explored;
      };	

      /////////////////////////////////////////////////////////////////////////
   private:

      vector<Edge*> edge;

      vector<Vertex*> vertex;

      unsigned int vcounter; //tracks number of verticies
      unsigned int ecounter; //tracks number of edges

   public:
      /////////////////////////////////////////////////////////////////////////
      Graph();

      Graph(Graph& G);

      ~Graph();

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
      void removeVertex(Vertex* v);
      void removeEdge(Edge* e);

      unsigned int numVertices();
      unsigned int numEdges();
      vector<Vertex*> vertices();
      vector<Edge*> edges();

      void print();
      void read_file(std::string filename);
      /////////////////////////////////////////////////////////////////////////

};



template<typename Object,typename Weight>
Graph<Object,Weight>::Graph(){
  edge = vector<Edge*>();
  vertex = vector<Vertex*>();
  vcounter = 0;
  ecounter = 0;
}


template<typename Object,typename Weight>
Graph<Object,Weight>::Graph(Graph<Object,Weight>& G){
 
  std::map<typename Graph<Object,Weight>::Vertex*, typename
    Graph<Object, Weight>::Vertex*> vertex_mapping;

  
  // copy verticies
  for(typename vector<typename Graph<Object,Weight>::Vertex*>::iterator it =
      G.vertex.begin(); it != G.vertex.end(); ++it) {
    Vertex* v = new Vertex(**it);
    vertex_mapping[*it] = v;
    vertex.push_back(v);

  }

  // copy edges
  for(typename vector<typename Graph<Object,Weight>::Edge*>::iterator it =
      G.edge.begin(); it != G.edge.end(); ++it)
    insertEdge(vertex_mapping[(*it)->start], vertex_mapping[(*it)->end],
        (*it)->weight);


  vcounter = G.vcounter;
  ecounter = G.ecounter;
}

template<typename Object,typename Weight>
Graph<Object,Weight>::~Graph(){
  
  for(int i=0; i<ecounter; i++) {
    delete edge[i];
  }
  for(int i=0; i<vcounter; i++) {
    delete vertex[i];
  }
}

template<typename Object,typename Weight> 
void Graph<Object,Weight>::reset(){
   vcounter = 0;
   ecounter = 0;
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
vector<typename Graph<Object,Weight>::Edge*> Graph<Object,Weight>::incidentEdges(Vertex* v){
  return v->inedge;   
}

template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Edge*> Graph<Object,Weight>::outgoingEdges(Vertex* v){
  return v->edge;
}

template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Vertex*> Graph<Object,Weight>::incidentVertices(Vertex* v){
   vector<Vertex*> result;
   //fill result
   for(int i=0; i<v->edge.size(); i++) {
     result.push_back(v->inedge[i]->start);
   }
   return result;
}

template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Vertex*> Graph<Object,Weight>::adjacentVertices(Vertex* v){
   vector<Vertex*> result;
   //fill result
   for(int i=0; i<v->edge.size(); i++) {
    result.push_back(v->edge[i]->end);
   }
   return result;
}

template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::outdegree(Vertex* v){
  return v->edge.size(); 
}

template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::indegree(Vertex* v){
  return v->inedge.size();   
}

template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::degree(Vertex* v){
  return v->edge.size() + v->inedge.size ();  
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
  for(int i=0; i< v->edge.size(); i++) {
    if(v->edge[i]->end == w)
      return true;
  }
  return false;
}

template<typename Object,typename Weight>
typename Graph<Object,Weight>::Vertex* Graph<Object,Weight>::insertVertex(Object o){
  Vertex* v = new Vertex(o);
  vertex.push_back(v);
  vcounter++;
  return v;
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::insertEdge(Vertex* v,Vertex* w,Weight t){
  Edge* e = new Edge(v,w,t);
  edge.push_back(e);
  ecounter++;
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::removeEdge(Edge* e){
  // find and erase e
  for(int i=0; i<edge.size(); i++) {
    if(edge[i] == e) {
      edge.erase(i);
      ecounter--;
    }
  }
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::insertUndirectedEdge(Vertex* v,Vertex* w,Weight t){
  Edge* e1 = new Edge(v,w,t);
  Edge* e2 = new Edge(w,v,t);
  edge.push_back(e1);
  edge.push_back(e2);
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::removeVertex(Vertex* v){
  for(int i=0; i<vertex.size(); i++) {
    if(vertex[i] == v) {
      vertex.erase(i);
      vcounter--;
    }
  }
}

template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::numVertices(){
  return vcounter;
}

template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::numEdges(){
  return ecounter;
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
      cout << "(" << edge[i]->start->element << "," << edge[i]->end->element << ")" << endl;
}

template<typename Object, typename Weight>
void Graph<Object,Weight>::read_file(std::string filename) {
  string data;

  ifstream infile;
  infile.open(filename.c_str());
  
  infile >> data;
  int vnum = atoi(data.c_str());

  for(int i=0; i<vnum; i++) {
    insertVertex(Object());
  }

  while(!infile.eof()) {
    int v;
    int w;
    int weight;
    infile >> v >> w >> weight;
    insertEdge(vertex[v],vertex[w],weight);
  }

  infile.close();
}


#endif




