#include "Graph.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
	// Create a graph object
	Graph myGraph("city.dat", "road.dat"); 
	char choice = ' '; // The user's command
	string start = "", end = "";
	stringstream ss;
	int dis = 0;
	do {
		cout << "Command? ";
		cin >> choice;
		cin.ignore();
		switch (choice) {
		case ('Q'): 
			cout << "City code: ";
			getline(cin, start);
			myGraph.printCity(start);
			break;
		case ('D'):
			cout << "City code of starting point: ";
			getline(cin, start);
			cout << "City code of starting point: ";
			getline(cin, end);
			myGraph.printPath(start, end);
			break;
		case ('I'):
			cout << "City code of starting point: ";
			getline(cin, start);
			cout << "City code of starting point: ";
			getline(cin, end);
			cout << "Distance: ";
			cin >> dis;
			myGraph.insertPath(start, end, dis);
			break;
		case ('R'):
			cout << "City code of starting point: ";
			getline(cin, start);
			cout << "City code of starting point: ";
			getline(cin, end);
			myGraph.removePath(start, end);
			break;
		case ('H'):
			cout << "Q \tQuery the city information by entering the city code.\n"
				<< "D \tFind the minimum distance between two cities.\n"
				<< "I \tInsert a road by entering two city codes and distance.\n"
				<< "R \tRemove an existing road by entering two city codes.\n"
				<< "H \tDisplay this message.\n"
				<< "E \tExit.\n";
			break;
		case ('E'): break;
		default:
			cout << "Error!! Invalid option.";
		} 
	} while (choice != 'E');
	
	return 0;
}