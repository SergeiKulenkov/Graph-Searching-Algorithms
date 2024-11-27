#include "Graph.h"
#include <stack>
#include <queue>

Graph::Graph(std::vector<Vertex>& vertices)
{
	for (Vertex& vertex : vertices)
	{
		m_Vertices.emplace(vertex.GetID(), std::move(vertex));
	}
}

void Graph::ResetSearchData()
{
	for (const auto& [key, value] : m_Vertices)
	{
		m_VisitedVertices[key] = false;
	}
}

void Graph::AddVertex(const Vertex& vertex)
{
	m_Vertices.emplace(vertex.GetID(), vertex);
}

void Graph::TraverseDepthFirst(const int sourceID, std::vector<int>& result)
{
	ResetSearchData();
	int currentVertexID = 0;
	int vertexIndex = 0;
	std::stack<int> verticesStack;
	verticesStack.push(sourceID);

	while (verticesStack.size() > 0)
	{
		if (!m_VisitedVertices[verticesStack.top()])
		{
			currentVertexID = verticesStack.top();
			m_VisitedVertices[currentVertexID] = true;
			result[vertexIndex] = currentVertexID;
			vertexIndex++;
		}
		verticesStack.pop();

		for (const int neighborID : m_Vertices[currentVertexID].GetAdjacentIDs())
		{
			if (!m_VisitedVertices[neighborID])
			{
				verticesStack.push(neighborID);
			}
		}
	}
}

void Graph::TraverseBreadthFirst(const int sourceID, std::vector<int>& result)
{
	ResetSearchData();
	int currentVertexID = 0;
	int vertexIndex = 0;
	std::queue<int> verticesQueue;
	verticesQueue.push(sourceID);

	while (verticesQueue.size() > 0)
	{
		if (!m_VisitedVertices[verticesQueue.front()])
		{
			currentVertexID = verticesQueue.front();
			m_VisitedVertices[currentVertexID] = true;
			result[vertexIndex] = currentVertexID;
			vertexIndex++;
		}
		verticesQueue.pop();

		for (const int neighborID : m_Vertices[currentVertexID].GetAdjacentIDs())
		{
			if (!m_VisitedVertices[neighborID])
			{
				verticesQueue.push(neighborID);
			}
		}
	}
}

bool Graph::HasPath(const int sourceID, const int goalID)
{
	ResetSearchData();
	bool hasPath = false;
	int currentVertexID = 0;
	std::queue<int> verticesQueue;
	verticesQueue.push(sourceID);

	while (verticesQueue.size() > 0)
	{
		if (!m_VisitedVertices[verticesQueue.front()])
		{
			currentVertexID = verticesQueue.front();
			if (currentVertexID == goalID)
			{
				hasPath = true;
				break;
			}

			m_VisitedVertices[currentVertexID] = true;
		}
		verticesQueue.pop();

		for (const int neighborID : m_Vertices[currentVertexID].GetAdjacentIDs())
		{
			if (!m_VisitedVertices[neighborID])
			{
				verticesQueue.push(neighborID);
			}
		}
	}

	return hasPath;
}

void Graph::DFSUtil(const int vertexID)
{
	m_VisitedVertices[vertexID] = true;
	for (const int neighborID : m_Vertices[vertexID].GetAdjacentIDs())
	{
		if (!m_VisitedVertices[neighborID])
		{
			DFSUtil(neighborID);
		}
	}
}

int Graph::CountConnectedComponents()
{
	ResetSearchData();
	int count = 0;

	for (const auto& [key, value] : m_Vertices)
	{
		if (!m_VisitedVertices[key])
		{
			DFSUtil(key);
			count++;
		}
	}

	return count;
}

int Graph::DFSUtilWithSizeCount(const int vertexID)
{
	int size = 0;
	if (!m_VisitedVertices[vertexID])
	{
		m_VisitedVertices[vertexID] = true;
		size = 1;

		for (const int neighborID : m_Vertices[vertexID].GetAdjacentIDs())
		{
			size += DFSUtilWithSizeCount(neighborID);
		}
	}

	return size;
}

int Graph::GetLargestComponentSize()
{
	ResetSearchData();
	int size = 0;
	int largestSize = 0;

	for (const auto& [key, value] : m_Vertices)
	{
		if (!m_VisitedVertices[key])
		{
			size = DFSUtilWithSizeCount(key);
			if (size > largestSize)
			{
				largestSize = size;
			}
		}
	}

	return largestSize;
}

int Graph::GetShortestPathLength(const int vertexAID, const int vertexBID)
{
	ResetSearchData();
	int shortestLength = 0;

	PairIndexDistance current{0, 0};
	std::queue<PairIndexDistance> verticesQueue;
	verticesQueue.push({ vertexAID, 0 });

	while (verticesQueue.size() > 0)
	{
		if (!m_VisitedVertices[verticesQueue.front().index])
		{
			current = verticesQueue.front();
			if (current.index == vertexBID)
			{
				shortestLength = current.distance;
				break;
			}

			m_VisitedVertices[current.index] = true;
		}
		verticesQueue.pop();

		for (const int neighborID : m_Vertices[current.index].GetAdjacentIDs())
		{
			if (!m_VisitedVertices[neighborID])
			{
				verticesQueue.push({ neighborID, current.distance + 1 });
			}
		}
	}

	return shortestLength;
}