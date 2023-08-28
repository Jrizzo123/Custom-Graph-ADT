/*
* Name: Jacob Rizzo
* Final project
* Purpose: Implement a bidirectional weighted graph Abstract Data Type
*/

#include "graph.h"

Graph::Graph() {
	vertexCount = 0;
	edgeCount = 0;
}
Graph::~Graph() {
	clearGraph();
}

bool Graph::addVertex(int newVertex, int oldVertex, int weight) {
	bool result{ false };
	bool foundNew{ false };
	bool foundOld{ false };
	for (int i = 0; i < nodeList.size(); i++) { //seeing if vertices are in graph
		if (nodeList[i]->id == newVertex) {
			foundNew = true;
		}
		if (nodeList[i]->id == oldVertex) {
			foundOld = true;
		}
	}

	if (!foundNew && (foundOld || isEmpty()) && newVertex > 0) {
		if (isEmpty()) { //if empty, do not add edge
			Node* temp = new Node;
			temp->id = newVertex;
			nodeList.push_back(temp);
			vertexCount++;
			resize(nodeList.size());
			result = true;
		}
		else { //else, add edge
			Node* temp = new Node;
			temp->id = newVertex;
			nodeList.push_back(temp);
			vertexCount++;
			resize(nodeList.size());
			addEdge(newVertex, oldVertex, weight);
			result = true;
		}
	}



	return result;
}

bool Graph::removeVertex(int value) { //removing vertex
	bool result{ false };
	bool found{ false };
	int index;
	int row;
	int edgeCount1;

	if (!isEmpty()) { //making sure graph is not empty
		for (int i = 0; i < nodeList.size(); i++) { //making sure vertex is within graph 
			if (nodeList[i]->id == value) {
				found = true;
			}
		}

		if (found) {
			row = findIndex(value);
			for (int i = 0; i < adjMatrix.size(); i++) { //counting the number of edges for the two vertices
				if (adjMatrix[row][i] > 0) {
					edgeCount1++;
				}
			}
			if (edgeCount1 < 2) { //testing if edges must be added to maintain connection
				index = findIndex(value);
				for (auto& row : adjMatrix) {
					row.erase(row.begin() + index);
				}
				adjMatrix.erase(adjMatrix.begin() + index);
				nodeList.erase(nodeList.begin() + index);
				vertexCount--;
				edgeCount = edgeCount - edgeCount1;

				result = true;
			}
			else { // edges need to be created 
				index = findIndex(value);
				for (int i = 0; i < adjMatrix.size(); i++) { //counting the number of edges for the two vertices
					if (adjMatrix[index][i] > 0) {
						addEdge(nodeList[i]->id, nodeList[0]->id, 1);
					}
				}
				for (auto& row : adjMatrix) {
					row.erase(row.begin() + index);
				}
				adjMatrix.erase(adjMatrix.begin() + index);
				nodeList.erase(nodeList.begin() + index);
				vertexCount--;

				edgeCount = edgeCount - edgeCount1;
				result = true;
			}

		}
	}
	return result;
}

bool Graph::addEdge(int vertexOne, int vertexTwo, int weight) {
	bool result{ false };
	bool found1{ false };
	bool found2{ false };
	int row, column;


	if (!isEmpty()) {
		row = findIndex(vertexOne); //finding indexes of vertices within matrix
		column = findIndex(vertexTwo);
		if (adjMatrix[row][column] == 0 && row != column) {
			for (int i = 0; i < nodeList.size(); i++) { //seeing if the vertices are in the graph
				if (nodeList[i]->id == vertexOne) {
					found1 = true;
				}
				if (nodeList[i]->id == vertexTwo) {
					found2 = true;
				}
			}
			if (found1 && found2 & weight > 0) { //verifying data, edges, and that the vertices are not the same
				adjMatrix[row][column] = weight;
				adjMatrix[column][row] = weight;
				edgeCount++;
				result = true;
			}
		}
	}




	return result;
}

bool Graph::deleteEdge(int vertexOne, int vertexTwo) { //deleting edge between vertices
	bool result{ false };
	int row, column;
	int edgeCount1 = 0;
	int edgeCount2 = 0;

	if (isEmpty()) { 
		result = false;
	}
	else {
		row = findIndex(vertexOne);
		column = findIndex(vertexTwo);
		for (int i = 0; i < adjMatrix.size(); i++) { //counting the number of edges for the two vertices
			if (adjMatrix[row][i] > 0) {
				edgeCount1++;
			}
			if (adjMatrix[i][column] > 0) {
				edgeCount2++;
			}
		}

		if (!isEmpty() && edgeCount1 > 1 && edgeCount2 > 1) { //verifying there is an edge to delete
			adjMatrix[row][column] = 0;
			edgeCount--;
			result = true;
		}
	}


	return result;
}

int Graph::findIndex(int number) { //finding vertex position in nodeList, and also adjacency list
	int index;

	for (int i = 0; i < nodeList.size(); i++) {
		if (number == nodeList[i]->id) {
			index = i;
			i = nodeList.size() + 1;
		}
	}
	return index;
}

void Graph::resize(size_t newSize) { //resizing adjacency matrix to fit new node
	for (int i = 0; i < adjMatrix.size(); i++) {
		adjMatrix[i].push_back(0);
	}
	vector<int> row;
	for (int i = 0; i < nodeList.size(); i++) {
		row.push_back(0);
	}
	adjMatrix.push_back(row);

}

void Graph::printMatrix() { //printing adjacency matrix
	for (int i = 0; i < adjMatrix.size(); i++)
	{
		for (int j = 0; j < adjMatrix[i].size(); j++)
		{
			std::cout << std::left << std::setw(5) << adjMatrix[i][j] << "  ";
		}
		std::cout << std::endl;
	}

	
}

bool Graph::isEmpty() {
	bool result{ false };
	if (nodeList.size() == 0) {
		result = true;
	}
	return result;
}

bool Graph::isConnected(int vertexOne, int vertexTwo) { //testing if two vertices have an edge between them
	bool result{ false };
	int row, column;

	if (!isEmpty()) {
		row = findIndex(vertexOne);
		column = findIndex(vertexTwo);

		if (adjMatrix[row][column] > 0) {
			result = true;
		}
	}

	return result;
}

void Graph::clearGraph() {
	nodeList.clear();
	adjMatrix.clear();
	edgeCount = 0;
	vertexCount = 0;
}

int Graph::getVertexCount() {
	return vertexCount;
}
int Graph::getEdgeCount() {
	return edgeCount;
}

void Graph::breadthFirstSearch(int startingVertex) { //BFS algorithm to print graph

	std::queue<int> vQueue; 
	vector<int> visited;
	vQueue.push(startingVertex);
	int index;
	int id;
	bool found{ false };
	while (!vQueue.empty()) {
		int currentVertex = vQueue.front();
		vQueue.pop();


		if (!find(currentVertex, visited)) {
			cout << "Visited: " << currentVertex << endl;
		}

		visited.push_back(currentVertex);

		index = findIndex(currentVertex);
		for (int i = 0; i < nodeList.size(); i++) {
			id = nodeList[i]->id;
			if (adjMatrix[index][i] > 0) {
				if (!find(id, visited)) {
					id = nodeList[i]->id;
					vQueue.push(id);
				}
			}
		}
	}
}
void Graph::depthFirstSearch(int startingVertex) {
	vector<bool> visited(getVertexCount(), false);
	depthFirstSearch(startingVertex, visited);
}
void Graph::depthFirstSearch(int startingVertex, vector<bool>& visited) {
	cout << "visited: " << startingVertex << endl;
	int index;
	int indexId;
	index = findIndex(startingVertex);
	visited[index] = true;

	for (int i = 0; i < vertexCount; i++) {
		if (adjMatrix[index][i] > 0 && (!visited[i])) {
			indexId = nodeList[i]->id;
			depthFirstSearch(indexId, visited);
		}
	}
}

bool Graph::find(int id, vector<int> visited) { //private method to see if vertex has already been visited
	bool found{ false };

	for (int i = 0; i < visited.size(); i++) {
		if (visited[i] == id) {
			found = true;
		}
	}

	return found;
}
