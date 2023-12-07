#include <iostream>
#include "Graph/Graph.h"

void SetupGraph(Graph& graph)
{
	std::vector<int> vertex0{ 1, 3 };
	std::vector<int> vertex1{ 0, 2, 3, 4 };
	std::vector<int> vertex2{ 1 };
	std::vector<int> vertex3{ 0, 1, 4 };
	std::vector<int> vertex4{ 1, 3 };
	std::vector<int> vertex5{ 6 };
	std::vector<int> vertex6{ 5 };

	graph.AddVertex(vertex0);
	graph.AddVertex(vertex1);
	graph.AddVertex(vertex2);
	graph.AddVertex(vertex3);
	graph.AddVertex(vertex4);
	graph.AddVertex(vertex5);
	graph.AddVertex(vertex6);
}

///////////////////////////////

int main()
{
	Graph graph;
	SetupGraph(graph);

	graph.PrintDepthFirst(0);
	graph.PrintBreadthFirst(0);

	graph.PrintDepthFirst(4);
	graph.PrintBreadthFirst(3);

	// values for testing
	int source = 1;
	int goal = 6;
	std::cout << "Has path (true or false) from " << source << " to " << goal << " - " << graph.HasPath(source, goal) << '\n';

	source = 0;
	goal = 4;
	std::cout << "Has path (true or false) from " << source << " to " << goal << " - " << graph.HasPath(source, goal) << '\n';

	std::cout << "Connected components count = " << graph.CountConnectedComponents() << '\n';
	std::cout << "Largest connected component = " << graph.GetLargestComponentSize() << '\n';

	int vertexAIndex = 0;
	int vertexBIndex = 4;
	std::cout << "Shortest path from " << vertexAIndex << " to " << vertexBIndex << " = " << graph.GetShortestPathLength(vertexAIndex, vertexBIndex) << '\n';

	return 0;
}