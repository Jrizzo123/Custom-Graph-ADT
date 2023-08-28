/*
* Name: Jacob Rizzo
* Final project
* Purpose: Automated testing for graph ADT
*/

#include "main.h"

int main() {

	/*
	* IMPORTANT:
	* when main uses a for loop to perform an operation, some of them will say failed... this does not mean the method failed 
	* Some of the data being entered in some of the for loops are duplicates, but there are enough iterations to create a solid testing ground
	*/



	srand(time(NULL));

	int ids1[TESTDATA1] = { 60, 20, 10, 70, 30, 40, 50, 100, 90, 80 };
	int ids2[TESTDATA1] = { 62, 26, 13, 79, 34, 48, 52, 101, 93, 84 };
	int weights1[TESTDATA2] = { 15, 35, 25, 55, 45, 75, 65, 95, 85 };
	vector<int> addedVertices;

	Graph graph;


	//testing operations on empty graph
	cout << "Testing graph..." << endl;
	cout << "===============================" << endl << endl;

	cout << "Testing operations on empty graph..." << endl << endl;

	if (graph.isEmpty()) {
		cout << "Graph is empty" << endl;
	}
	else {
		cout << "Graph is not empty" << endl;
	}

	cout << "Number of vertices: " << graph.getVertexCount() << endl;
	cout << "Number of edges: " << graph.getEdgeCount() << endl;

	int testIndex = rand() % TESTDATA1 - 1;
	int testIndex2;
	int testWeight;

	cout << "Trying to remove edge on empty graph...";
	if (graph.deleteEdge(ids1[testIndex], ids1[testIndex + 1])) {
		cout << "Removed edge between " << ids1[testIndex] << " and " << ids1[testIndex + 1] << endl;
	}
	else {
		cout << "Failed to remove edge" << endl;
	}

	cout << endl << "Testing if connection exists between two nonexistent vertices.." << endl;
	if (graph.isConnected(ids1[testIndex], ids1[testIndex + 1])) {
		cout << "Vertices " << ids1[testIndex] << " and " << ids1[testIndex + 1] << " have edge between them" << endl;
	}
	else {
		cout << "No edge between vertices" << endl;
	}

	//randomely filling graph
	cout << endl << endl << "Filling graph" << endl;
	cout << "======================================" << endl << endl;
	addedVertices.push_back(10); //initializing addedVertices, will remove after for loop

	for (int i = 0; i < TESTDATA1; i++) { //automatically filling graph with data
		//some data will not add because it is a duplicate, but it will average ~5-6 total vertices
		testIndex = rand() % TESTDATA1 - 1;
		testIndex2 = rand() % addedVertices.size();
		testWeight = rand() % TESTDATA2 - 1;
		if (graph.addVertex(ids1[testIndex], addedVertices[testIndex2], weights1[testWeight])) {
			cout << "Added vertex " << ids1[testIndex] << endl;
			addedVertices.push_back(ids1[testIndex]);
		}
		else {
			cout << "Failed to add vertex" << endl;
		}
	}

	if (!addedVertices.empty()) { //erasing placeholder element
		addedVertices.erase(addedVertices.begin());
	}

	//testing adding bad data
	cout << "Adding known duplicate...";
	testIndex = addedVertices[0];
	testIndex2 = addedVertices[1];
	if (graph.addVertex(addedVertices[testIndex], addedVertices[testIndex2], weights1[testWeight])) {
		cout << "Successfully added vertex" << endl;
	}
	else {
		cout << "Failed" << endl;
	}

	cout << "Adding vertex connected to nonexistent vertex...";
	testIndex = rand() % TESTDATA1 - 1;
	testIndex2 = rand() % TESTDATA1 - 1;
	testIndex2 = addedVertices[1];
	if (graph.addVertex(ids2[testIndex], ids2[testIndex2], weights1[testWeight])) {
		cout << "Successfully added vertex" << endl;
	}
	else {
		cout << "Failed" << endl;
	}

	cout << "Adding vertex with invalid data...";
	testIndex = rand() % TESTDATA1 - 1;
	if (graph.addVertex(-1, addedVertices[testIndex], weights1[testWeight])) {
		cout << "Successfully added vertex" << endl;
	}
	else {
		cout << "Failed" << endl;
	}


	//testing operations on filled graph
	cout << endl << "Number of vertices: " << graph.getVertexCount() << endl;
	cout << "Number of edges: " << graph.getEdgeCount() << endl;


	//Testing addEdge
	cout << endl << "Testing adding edges between vertices..." << endl;
	cout << "=============================================" << endl;
	for (int i = 0; i < TESTEDGE; i++) {
		testIndex = rand() % addedVertices.size();
		testIndex2 = rand() % addedVertices.size();
		testWeight = rand() % TESTDATA2 - 1;
		if (graph.addEdge(addedVertices[testIndex], addedVertices[testIndex2], weights1[testWeight])) {
			cout << "Added edge between " << addedVertices[testIndex] << " and " << addedVertices[testIndex2] << " with weight " << weights1[testWeight] << endl;
		}
		else {
			cout << "Failed to add edge" << endl;
		}
	}
	//testing invalid data
	cout << "Adding between non existent vertices...";
	testIndex = rand() % TESTDATA2;
	testIndex2 = rand() % TESTDATA2;
	if (graph.addEdge(ids2[testIndex], ids2[testIndex2], weights1[testWeight])) {
		cout << "Succefsully added edge" << endl;
	}
	else {
		cout << "failed" << endl;
	}
	cout << "Adding edge with invalid data...";
	testIndex = rand() % addedVertices.size();
	testIndex2 = rand() % addedVertices.size();
	if (graph.addEdge(addedVertices[testIndex], addedVertices[testIndex2], -1)) {
		cout << "Succefsully added edge" << endl;
	}
	else {
		cout << "failed" << endl;
	}
	cout << endl;

	cout << "Vertex count: " << graph.getVertexCount() << endl;
	cout << "Edge count: " << graph.getEdgeCount() << endl;

	if (graph.isEmpty()) {
		cout << "Graph is empty" << endl;
	}
	else {
		cout << "Graph is not empty" << endl;
	}
	cout << endl;
	

	cout << "Testing for edges between vertices..." << endl;
	cout << "===========================================" << endl << endl;
	for (int i = 0; i < TESTDATA1; i++) {
		testIndex = rand() % addedVertices.size();
		testIndex2 = rand() % addedVertices.size();
		if (graph.isConnected(addedVertices[testIndex], addedVertices[testIndex2])) {
			cout << "An edge exists between " << addedVertices[testIndex] << " and " << addedVertices[testIndex2] << endl;
		}
		else {
			cout << "No edge between " << addedVertices[testIndex] << " and " << addedVertices[testIndex2] << endl;
		}
	}
	cout << endl;


	//testing breadth first search algorithm
	cout << endl << "BFS print: " << endl << endl;

	graph.breadthFirstSearch(addedVertices[testIndex]);

	//printing adjacency matrix
	cout << endl << "Adjacency matrix: " << endl;
	graph.printMatrix();
	cout << endl << endl;


	//testing removeVertex method
	for (int i = 0; i < graph.getVertexCount(); i++) {
		testIndex = rand() % addedVertices.size();
		if (graph.removeVertex(addedVertices[testIndex])) {
			cout << "Deleted vertex " << addedVertices[testIndex] << endl;
			addedVertices.erase(addedVertices.begin() + testIndex);
		}
		else {
			cout << "Failed to delete vertex " << addedVertices[testIndex] << endl;
		}
	}

	//testing depth first search by printing remaining vertices
	cout << endl << "Printing graph with depth first search..." << endl;
	testIndex = rand() % addedVertices.size();
	graph.depthFirstSearch(addedVertices[testIndex]);

	//printing remaining matrix
	cout << endl << "Adjacency matrix: " << endl;
	graph.printMatrix();
	cout << endl << endl;

	//clearing entire graph
	cout << "Clearing graph..." << endl;
	graph.clearGraph();

	if (graph.isEmpty()) {
		cout << "Graph is empty" << endl;
	}
	else {
		cout << "Graph is not empty" << endl;
	}





	/*Second round testing*/




	cout << "Creating a large graph" << endl;
	cout << "===============================" << endl;


	int ids3[TESTDATA3];
	int ids4[TESTDATA1] = { 62, 26, 13, 79, 34, 48, 52, 101, 93, 84 };
	int weights2[TESTDATA3];
	int data;

	for (int i = 0; i < TESTDATA3; i++) { //filling test data arrays
		data = rand() % TESTRANGE;
		ids3[i] = data;
		data = rand() % TESTRANGE;
		weights2[i] = data;
	}

	//testing operations on empty graph
	cout << "Testing graph..." << endl;
	cout << "===============================" << endl << endl;

	cout << "Testing operations on empty graph..." << endl << endl;

	if (graph.isEmpty()) {
		cout << "Graph is empty" << endl;
	}
	else {
		cout << "Graph is not empty" << endl;
	}

	cout << "Number of vertices: " << graph.getVertexCount() << endl;
	cout << "Number of edges: " << graph.getEdgeCount() << endl;

	testIndex = rand() % TESTDATA3 - 1;
	testIndex2;
	testWeight;

	cout << "Trying to remove edge on empty graph...";
	if (graph.deleteEdge(ids3[testIndex], ids3[testIndex + 1])) {
		cout << "Removed edge between " << ids3[testIndex] << " and " << ids3[testIndex + 1] << endl;
	}
	else {
		cout << "Failed to remove edge" << endl;
	}

	cout << endl << "Testing if connection exists between two nonexistent vertices.." << endl;
	if (graph.isConnected(ids3[testIndex], ids3[testIndex + 1])) {
		cout << "Vertices " << ids3[testIndex] << " and " << ids3[testIndex + 1] << " have edge between them" << endl;
	}
	else {
		cout << "No edge between vertices" << endl;
	}

	//filling graph with automated for loop
	cout << endl << endl << "Filling graph" << endl;
	cout << "======================================" << endl << endl;
	addedVertices.push_back(10); //initializing addedVertices

	for (int i = 0; i < TESTDATA3; i++) {
		testIndex = rand() % TESTDATA3 - 1;
		testIndex2 = rand() % addedVertices.size();
		testWeight = rand() % TESTDATA2 - 1;
		if (graph.addVertex(ids3[testIndex], addedVertices[testIndex2], weights2[testWeight])) {
			cout << "Added vertex " << ids3[testIndex] << endl;
			addedVertices.push_back(ids3[testIndex]);
		}
		else {
			cout << "Failed to add vertex" << endl;
		}
	}

	if (!addedVertices.empty()) { //removing placeholder
		addedVertices.erase(addedVertices.begin());
	}

	//attempting to add bad data
	cout << "Adding known duplicate...";
	testIndex = addedVertices[0];
	testIndex2 = addedVertices[1];
	if (graph.addVertex(addedVertices[testIndex], addedVertices[testIndex2], weights2[testWeight])) {
		cout << "Successfully added vertex" << endl;
	}
	else {
		cout << "Failed" << endl;
	}

	cout << "Adding vertex connected to nonexistent vertex...";
	testIndex = rand() % TESTDATA3 - 1;
	testIndex2 = rand() % TESTDATA3 - 1;
	testIndex2 = addedVertices[1];
	if (graph.addVertex(ids3[testIndex], ids3[testIndex2], weights2[testWeight])) {
		cout << "Successfully added vertex" << endl;
	}
	else {
		cout << "Failed" << endl;
	}

	cout << "Adding vertex with invalid data...";
	testIndex = rand() % TESTDATA3 - 1;
	if (graph.addVertex(-1, addedVertices[testIndex], weights2[testWeight])) {
		cout << "Successfully added vertex" << endl;
	}
	else {
		cout << "Failed" << endl;
	}

	//testing operations on filled graph
	cout << endl << "Number of vertices: " << graph.getVertexCount() << endl;
	cout << "Number of edges: " << graph.getEdgeCount() << endl;


	//Testing addEdge
	cout << endl << "Testing adding edges between vertices..." << endl;
	cout << "=============================================" << endl;
	for (int i = 0; i < TESTEDGE2; i++) {
		testIndex = rand() % addedVertices.size();
		testIndex2 = rand() % addedVertices.size();
		testWeight = rand() % TESTDATA3 - 1;
		if (graph.addEdge(addedVertices[testIndex], addedVertices[testIndex2], weights2[testWeight])) {
			cout << "Added edge between " << addedVertices[testIndex] << " and " << addedVertices[testIndex2] << " with weight " << weights2[testWeight] << endl;
		}
		else {
			cout << "Failed to add edge" << endl;
		}
	}
	cout << "Adding between non existent vertices...";
	testIndex = rand() % TESTDATA3;
	testIndex2 = rand() % TESTDATA3;
	if (graph.addEdge(ids3[testIndex], ids3[testIndex2], weights2[testWeight])) {
		cout << "Succefsully added edge" << endl;
	}
	else {
		cout << "failed" << endl;
	}
	cout << "Adding edge with invalid data...";
	testIndex = rand() % addedVertices.size();
	testIndex2 = rand() % addedVertices.size();
	if (graph.addEdge(addedVertices[testIndex], addedVertices[testIndex2], -1)) {
		cout << "Succefsully added edge" << endl;
	}
	else {
		cout << "failed" << endl;
	}
	cout << endl;

	cout << "Vertex count: " << graph.getVertexCount() << endl;
	cout << "Edge count: " << graph.getEdgeCount() << endl;

	if (graph.isEmpty()) {
		cout << "Graph is empty" << endl;
	}
	else {
		cout << "Graph is not empty" << endl;
	}
	cout << endl;


	cout << "Testing for edges between vertices..." << endl;
	cout << "===========================================" << endl << endl;
	for (int i = 0; i < TESTDATA3; i++) {
		testIndex = rand() % addedVertices.size();
		testIndex2 = rand() % addedVertices.size();
		if (graph.isConnected(addedVertices[testIndex], addedVertices[testIndex2])) {
			cout << "An edge exists between " << addedVertices[testIndex] << " and " << addedVertices[testIndex2] << endl;
		}
		else {
			cout << "No edge between " << addedVertices[testIndex] << " and " << addedVertices[testIndex2] << endl;
		}
	}
	cout << endl;

	cout << endl << "BFS print: " << endl << endl;

	//testing bfs algorithm
	graph.breadthFirstSearch(addedVertices[testIndex]);


	for (int i = 0; i < graph.getVertexCount(); i++) {
		testIndex = rand() % addedVertices.size();
		if (graph.removeVertex(addedVertices[testIndex])) {
			cout << "Deleted vertex " << addedVertices[testIndex] << endl;
			addedVertices.erase(addedVertices.begin() + testIndex);
		}
		else {
			cout << "Failed to delete vertex " << addedVertices[testIndex] << endl;
		}
	}

	//testing dfs algorithm
	cout << endl << "Printing graph with depth first search..." << endl;
	testIndex = rand() % addedVertices.size();
	graph.depthFirstSearch(addedVertices[testIndex]);


	cout << "Clearing graph..." << endl;
	graph.clearGraph(); //clearing graph

	if (graph.isEmpty()) {
		cout << "Graph is empty" << endl;
	}
	else {
		cout << "Graph is not empty" << endl;
	}
}
