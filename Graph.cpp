#include "Graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <deque>
#include <list>
#include <string>

using namespace std;

/**
	The constructor reads data from the text files
	and store it in the vector of vertices
	@param: cityFile The text file contains vertices' data
	@param: roadFile The text file contains edges' data
*/
Graph::Graph(string cityFile, string roadFile) {
	int index, number, elev, start, end, dis;
	long pop;
	string input, code;
	
	ifstream inputCity, inputRoad;
	inputCity.open(cityFile); // Open the cities' file
	if (!inputCity)  // Check whether the file is opened
		cout << "Invalid file name\n";
	else {
		index = 0;
		// Read until reaching the end of the file
		while(!inputCity.eof()) {
			// Add each vertex to the vector
			cities.push_back(Vertex());
			inputCity >> number; // Read city's number
			cities[index].number = number;
			inputCity >> code; // Rad city's code
			cities[index].cityCode = code;
			// Read the city's name
			while ((!isdigit(inputCity.peek())) || 
					(inputCity.peek() == ' ')) {
				if (inputCity.peek() == ' ')
					inputCity.ignore();
				else {
					inputCity >> input;
					cities[index].cityName += " " + input; 
				}
			}
			inputCity >> pop; // Read the city's population
			cities[index].population = pop;
			inputCity >> elev; // Read the city's elevation
			cities[index].elevation = elev;
			index++;
			
		}
	}
	inputCity.close(); // Close the cities' file

	inputRoad.open(roadFile); // Open the roads' file
	if (!inputRoad) // Check whether the file is opened
		cout << "Invalid file name\n";
	else {
		// Read until reaching the end of the file
		while(!inputRoad.eof()) {
			inputRoad >> start; // Read the start point
			inputRoad >> end; // Read the end point
			inputRoad >> dis; // Read the distance
			// Pointer to the associate vertex
			Vertex *node = &cities[end - 1];
			Edge newEdge(node, dis); // Create the new edge
			// Insert the new edge to the list of edges
			cities[start - 1].adjacencies.push_back(newEdge);
		}
	}
	inputRoad.close(); // Close the roads' file
}

/**
	The copy constructor 
*/
Graph::Graph(const Graph& g) {
	for (unsigned int i = 0; i < g.cities.size(); i++) {
		// Add each vertex to the vector
		cities.push_back(Vertex());
		// Read the cities' information
		cities[i].number = g.cities[i].number;
		cities[i].cityCode = g.cities[i].cityCode;
		cities[i].cityName = g.cities[i].cityName;
		cities[i].population = g.cities[i].population;
		cities[i].elevation = g.cities[i].elevation;
		// Copy the cities' list of neighbors 
		for (unsigned int j = 0; j < g.cities[i].adjacencies.size(); j++) {
			cities[i].adjacencies.push_back(g.cities[i].adjacencies[j]);
		}
		// Assign default values to minDistance and previous
		cities[i].minDistance = INT_MAX;
		cities[i].previous = NULL;
	}
}

/**
	The destructor
*/
Graph::~Graph() {
	cout << "Program closed! Thank you for using!";
	cin.ignore();
}

/**
	The printGraph function prints the information
	of all the cities
	@param: code The city's code
*/
void Graph::printCity(string code) {
	Vertex *v = getCity(code);
	if (v != NULL)
		cout << v->number << " " 
			<< v->cityCode << " "
			<< v->cityName << " "
			<< v->population << " "
			<< v->elevation << endl;
	else
		cout << "Error! Invalid city code\n";
}

/**
	The computePath function produces a shortest path
	tree for the graph
	@param: source Reference to the source vertex
*/
void Graph::computePath(Vertex &source) {
	// Initialiazation 
	for (unsigned int i = 0; i < cities.size(); i++) {
		cities[i].minDistance = INT_MAX;
		cities[i].previous = NULL;
	}

	// Set the source's minDistance to 0
	source.minDistance = 0;

	// The queue to hold all the vertices
	queue<Vertex*> vertexQueue;
	vertexQueue.push(&source);
	Vertex *u, *v;
	
	while (!vertexQueue.empty()) {
		u = vertexQueue.front();
		vertexQueue.pop(); // Remove u from queue
		if (u->minDistance == INT_MAX)
			break;
		for (unsigned int i = 0; i < u->adjacencies.size(); i++) {
			v = u->adjacencies[i].destination;
			int d = u->minDistance + u->adjacencies[i].distance;
			// Relaxation stage
			if (d < v->minDistance) {
				v->minDistance = d;
				v->previous = u;
				vertexQueue.push(v);
			}		
		}
	}
	v = NULL;
	u = NULL;
	
}

/**
	The getShortest function returns the list of 
	vertices which are the shortest path to the target
	@param: target Reference to the target vertex
*/
list<Graph::Vertex> Graph::getShortest(Vertex &target) {
	list<Vertex> path;
	for (Vertex* v = &target; v != NULL; v = v->previous)
		path.push_front(*v);
	return path;
}

/**
	The getCity function returns the pointer associates with
	the code input
	@param: code The city code input
	@return: current Reference to the vertex with the same city code
*/
Graph::Vertex* Graph::getCity(string code) {
	Vertex* current = NULL;
	// Search the vector of vertices
	for (unsigned int i = 0; i < cities.size(); i++) {
		// Found the code
		if (cities[i].cityCode == code) {
			current = &cities[i];
			break;
		}
	}
	return current;
}

/**
	The printPath function prints the shortest path between
	two cities
	@param: codeStart The city code of the starting point
		    codeEnd The city code of the destination
*/
void Graph::printPath(string codeStart, string codeEnd) {
	if (getCity(codeStart) == NULL || getCity(codeEnd) == NULL) 
		cout << "Error!! Invalid City Code...\n";
	else {
		computePath(*getCity(codeStart));
		list<Vertex> path = getShortest(*getCity(codeEnd));
		if (path.size() == 1) {
			cout << "You're already in the city\n";
		}
		else {
			cout << "The minimum distance between" 
				<< getCity(codeStart)->cityName << " and "
				<< getCity(codeEnd)->cityName << " is "
				<< path.back().minDistance  << " thourgh the route: ";
			while (!path.empty()) {
				if (path.size() == 1)
					cout << path.front().cityName << ".\n";
				else
					cout << path.front().cityName << " ,";
				path.pop_front();
			}
		}
	}
}

/**
	The insertPath function inserts a new edge between two
	vertices
	@param: codeStart The city code of the starting point
		    codeEnd The city code of the destination
			dis The distance between two cities
*/
void Graph::insertPath(string codeStart, string codeEnd, int dis) {
	if (getCity(codeStart) == NULL || getCity(codeEnd) == NULL) 
		cout << "Error!! Invalid City Code...\n";
	else {
		for (unsigned int i = 0; i < getCity(codeStart)->adjacencies.size(); i++) {
			if (getCity(codeEnd)->cityCode == getCity(codeStart)->adjacencies[i].destination->cityCode) {
				cout << "Path already exists\n";
				return;
			}
		}
		
		Edge *newEdge = new Edge(getCity(codeEnd), dis);
		getCity(codeStart)->adjacencies.push_back(*newEdge);
		cout << "Path has been inserted.\n";
		newEdge = NULL;
	}
}

/**
	The removePatht function remove an edge between
	two vertices
	@param: codeStart The city code of the starting point
		    codeEnd The city code of the destination
*/
void Graph::removePath(string codeStart, string codeEnd) {
	if (getCity(codeStart) == NULL || getCity(codeEnd) == NULL) 
		cout << "Error!! Invalid City Code...\n";
	else {
		for (unsigned int i = 0; i < getCity(codeStart)->adjacencies.size(); i++) {
			if (getCity(codeEnd)->cityCode == getCity(codeStart)->adjacencies[i].destination->cityCode) {
				getCity(codeStart)->adjacencies.erase(getCity(codeStart)->adjacencies.begin() + i);
				cout << "Path has been removed.\n";
				return;
			}
		}
		cout << "Path doesn't exist.\n";
	}

}