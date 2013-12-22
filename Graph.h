#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <list>

using namespace std;

class Graph
{
private:
	struct Edge; // Struct for each edge
	struct Vertex; // Struct for each vertex

	struct Edge {
		Vertex *destination; // Pointer to the destination vertex
		int distance; // The distance between the vertices

		Edge() : destination(NULL), distance(0) {}
		Edge(Vertex *d, int dis) : destination(d), distance(dis) {}
	};

	struct Vertex {
		int number; // The city's number
		string cityCode; // The city's code
		string cityName; // The city's name
		long population; // The city's population
		int elevation; // The city's elevation
		int minDistance; // The minimum distance to the previous vertex
		Vertex *previous; // Pointer to the vertex which has min distance
		vector<Edge> adjacencies; // The list of edges to the neighbor cities

		Vertex() : number(0), cityCode(""), cityName(""), 
			population(0), elevation(0), minDistance(INT_MAX), 
			previous(NULL), adjacencies(NULL){}
	};

	vector<Vertex> cities; // The vector of vertices
public:
	Graph(); // Default constructor
	Graph(string, string); // The parameters constructor
	Graph(const Graph&); // The copy constructor
	~Graph(); // The destructor

	// Function for program's operations
	void printCity(string);
	void computePath(Vertex&);
	list<Vertex> getShortest(Vertex&); 
	void printPath(string, string);
	Vertex* getCity(string);
	void insertPath(string, string, int);
	void removePath(string, string);
};

#endif