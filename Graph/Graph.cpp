#include "Graph.h"
#include <iostream>
#include <stack>
#include <queue>

void Graph::AddVertex(const std::vector<int>& vertices)
{
	adjacencyList.push_back(vertices);
}

void Graph::PrintDepthFirst(int sourceIndex)
{
	std::cout << "Depth first printing starting from " << sourceIndex << " : ";

	int currentVertex = 0;
	std::vector<bool> visitedVertices(adjacencyList.size());
	std::stack<int> verticesStack;
	verticesStack.push(sourceIndex);

	while (verticesStack.size() > 0)
	{
		if (!visitedVertices[verticesStack.top()])
		{
			currentVertex = verticesStack.top();
			visitedVertices[currentVertex] = true;
			std::cout << currentVertex << " ";
		}
		verticesStack.pop();

		for (int neighbor : adjacencyList[currentVertex])
		{
			if (!visitedVertices[neighbor])
			{
				verticesStack.push(neighbor);
			}
		}
	}

	std::cout << '\n';
}

void Graph::PrintBreadthFirst(int sourceIndex)
{
	std::cout << "Breadth first printing starting from " << sourceIndex << " : ";

	int currentVertex = 0;
	std::vector<bool> visitedVertices(adjacencyList.size());
	std::queue<int> verticesQueue;
	verticesQueue.push(sourceIndex);

	while (verticesQueue.size() > 0)
	{
		if (!visitedVertices[verticesQueue.front()])
		{
			currentVertex = verticesQueue.front();
			visitedVertices[currentVertex] = true;
			std::cout << currentVertex << " ";
		}
		verticesQueue.pop();

		for (int neighbor : adjacencyList[currentVertex])
		{
			if (!visitedVertices[neighbor])
			{
				verticesQueue.push(neighbor);
			}
		}
	}

	std::cout << '\n';
}

bool Graph::HasPath(int sourceIndex, int goalIndex)
{
	bool hasPath = false;
	int currentVertex = 0;
	std::vector<bool> visitedVertices(adjacencyList.size());
	std::queue<int> verticesQueue;
	verticesQueue.push(sourceIndex);

	while (verticesQueue.size() > 0)
	{
		if (!visitedVertices[verticesQueue.front()])
		{
			currentVertex = verticesQueue.front();
			if (currentVertex == goalIndex)
			{
				hasPath = true;
				break;
			}

			visitedVertices[currentVertex] = true;
		}
		verticesQueue.pop();

		for (int neighbor : adjacencyList[currentVertex])
		{
			if (!visitedVertices[neighbor])
			{
				verticesQueue.push(neighbor);
			}
		}
	}

	return hasPath;
}

void Graph::DFSUtil(int vertexindex, std::vector<bool>& visitedVertices)
{
	visitedVertices.at(vertexindex) = true;
	for (int neighbor : adjacencyList[vertexindex])
	{
		if (!visitedVertices.at(neighbor))
		{
			DFSUtil(neighbor, visitedVertices);
		}
	}
}

int Graph::CountConnectedComponents()
{
	int count = 0;
	std::vector<bool> visitedVertices(adjacencyList.size());

	for (int i = 0; i < adjacencyList.size(); i++)
	{
		if (!visitedVertices[i])
		{
			DFSUtil(i, visitedVertices);
			count++;
		}
	}

	return count;
}

int Graph::DFSUtilWithSizeCount(int vertexindex, std::vector<bool>& visitedVertices)
{
	int size = 0;
	if (!visitedVertices.at(vertexindex))
	{
		visitedVertices.at(vertexindex) = true;
		size = 1;

		for (int neighbor : adjacencyList[vertexindex])
		{
			size += DFSUtilWithSizeCount(neighbor, visitedVertices);
		}
	}

	return size;
}

int Graph::GetLargestComponentSize()
{
	int size = 0;
	int largestSize = 0;
	std::vector<bool> visitedVertices(adjacencyList.size());

	for (int i = 0; i < adjacencyList.size(); i++)
	{
		if (!visitedVertices[i])
		{
			size = DFSUtilWithSizeCount(i, visitedVertices);
			if (size > largestSize)
			{
				largestSize = size;
			}
		}
	}

	return largestSize;
}

int Graph::GetShortestPathLength(int vertexAIndex, int vertexBIndex)
{
	int shortestLength = 0;
	std::vector<bool> visitedVertices(adjacencyList.size());

	PairIndexDistance current{0, 0};
	std::queue<PairIndexDistance> verticesQueue;
	verticesQueue.push({ vertexAIndex, 0 });

	while (verticesQueue.size() > 0)
	{
		if (!visitedVertices[verticesQueue.front().index])
		{
			current = verticesQueue.front();
			if (current.index == vertexBIndex)
			{
				shortestLength = current.distance;
				break;
			}

			visitedVertices[current.index] = true;
		}
		verticesQueue.pop();

		for (int neighbor : adjacencyList[current.index])
		{
			if (!visitedVertices[neighbor])
			{
				verticesQueue.push({ neighbor, current.distance + 1 });
			}
		}
	}

	return shortestLength;
}