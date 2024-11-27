#pragma once
#include <unordered_map>
#include "Vertex.h"

struct PairIndexDistance
{
	int index;
	int distance;
};

class Graph
{
public:
	Graph() = delete;

	Graph(std::vector<Vertex>& vertices);

	void AddVertex(const Vertex& vertex);

	// print the graph using DFS starting from the source
	void TraverseDepthFirst(const int sourceID, std::vector<int>& result);

	// print the graph using BFS starting from the source
	void TraverseBreadthFirst(const int sourceID, std::vector<int>& result);

	// uses BFS to check if a path exists from the source to the goal
	bool HasPath(const int sourceID, const int goalID);

	// uses DFS to traverse through each component and returns their count
	int CountConnectedComponents();

	// uses DFS to traverse through each component and returns the largest size
	int GetLargestComponentSize();

	// uses BFS to return the shortest length from vertexA to vertexB
	int GetShortestPathLength(const int vertexAID, const int vertexBID);

private:
	void ResetSearchData();

	// DFS utility for counting connected components
	void DFSUtil(const int vertexID);

	// DFS utility for counting component's size
	int DFSUtilWithSizeCount(const int vertexID);

	//////////

	std::unordered_map<int, Vertex> m_Vertices;
	std::unordered_map<int, bool> m_VisitedVertices;
};

