#pragma once
#include <vector>

struct PairIndexDistance
{
	int index;
	int distance;
};

class Graph
{
public:
	void AddVertex(const std::vector<int>& vertices);

	// print the graph using DFS starting from the source
	void PrintDepthFirst(int sourceIndex);

	// print the graph using BFS starting from the source
	void PrintBreadthFirst(int sourceIndex);

	// uses BFS to check if a path exists from the source to the goal
	bool HasPath(int sourceIndex, int goalIndex);

	// uses DFS to traverse through each component and returns their count
	int CountConnectedComponents();

	// uses DFS to traverse through each component and returns the largest size
	int GetLargestComponentSize();

	// uses BFS to return the shortest length from vertexA to vertexB
	int GetShortestPathLength(int vertexAIndex, int vertexBIndex);

private:
	// DFS utility for counting connected components
	void DFSUtil(int vertexIndex, std::vector<bool>& visitedVertices);

	// DFS utility for counting a component's size
	int DFSUtilWithSizeCount(int vertexIndex, std::vector<bool>& visitedVertices);

	//////////

	std::vector<std::vector<int>> adjacencyList;
};

