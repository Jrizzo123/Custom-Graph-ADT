#ifndef CLASSES_GRAPH_H
#define CLASSES_GRAPH_H

#include "data.h"
#include <iostream>
#include <iomanip>
#include <queue>
using std::cout;
using std::endl;

class Graph {
public:
	Graph();
	~Graph();

	bool addVertex(int, int, int);
	bool addEdge(int, int, int);
	bool deleteEdge(int, int);
	bool removeVertex(int);
	void printMatrix();
	bool isEmpty();
	int getEdgeCount();
	int getVertexCount();
	bool isConnected(int, int);
	void clearGraph();
	void breadthFirstSearch(int);
	void depthFirstSearch(int);

private:
	vector<Node*> nodeList;
	vector<vector<int>> adjMatrix;
	int edgeCount, vertexCount;
	int findIndex(int);
	void resize(size_t);
	bool find(int, vector<int>);
	void depthFirstSearch(int, vector<bool>&);
};



#endif
