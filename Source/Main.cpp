#include <iostream>
#include "Graph/Graph.h"
#include "Graph/Vertex.h"

//////////

void PrintIDs(const std::vector<int>& IDs)
{
	for (const int& ID : IDs)
	{
		if (ID <= 0)
		{
			break;
		}
		else
		{
			std::cout << ID << ", ";
		}
	}
	std::cout << '\n';
}

void ResetVector(std::vector<int>& IDs)
{
	for (int& ID : IDs)
	{
		if (ID <= 0)
		{
			break;
		}
		else
		{
			ID = 0;
		}
	}
}

void Run(Graph& graph, const int size)
{
	{
		std::vector<int> resultIDs(size);
		const int sourceID = 33;

		std::cout << "Depth first printing starting from " << sourceID << " : ";
		graph.TraverseDepthFirst(sourceID, resultIDs);
		PrintIDs(resultIDs);
		ResetVector(resultIDs);

		std::cout << "Breadth first printing starting from " << sourceID << " : ";
		graph.TraverseBreadthFirst(sourceID, resultIDs);
		PrintIDs(resultIDs);
		ResetVector(resultIDs);
	}

	const int startID = 53;
	const int endID = 65;
	std::cout << "Has path from " << startID << " to " << endID << " - " << (graph.HasPath(startID, endID) ? "true" : "false") << '\n';

	const int startID2 = 13;
	const int endID2 = 33;
	std::cout << "Has path from " << startID2 << " to " << endID2 << " - " << (graph.HasPath(startID2, endID2) ? "true" : "false") << '\n';

	std::cout << "Connected components count = " << graph.CountConnectedComponents() << '\n';
	std::cout << "Largest connected component = " << graph.GetLargestComponentSize() << '\n';

	const int vertexAID = 13;
	const int vertexBID = 33;
	std::cout << "Shortest path from " << vertexAID << " to " << vertexBID << " = " << graph.GetShortestPathLength(vertexAID, vertexBID) << '\n';
}

void Setup(std::vector<Vertex>& vertices)
{
	static const std::vector<int> IDs = { 13, 53, 26, 77, 33, 42, 65 };
	std::vector<Person> persons;
	persons.reserve(IDs.size());
	persons.emplace_back(IDs[0], "A", 25);
	persons.emplace_back(IDs[1], "B", 28);
	persons.emplace_back(IDs[2], "C", 22);
	persons.emplace_back(IDs[3], "D", 26);
	persons.emplace_back(IDs[4], "E", 25);
	persons.emplace_back(IDs[5], "F", 25);
	persons.emplace_back(IDs[6], "G", 23);

	vertices.reserve(IDs.size());
	vertices.emplace_back(std::move(persons[0]), std::initializer_list({ IDs[1], IDs[3] }));
	vertices.emplace_back(std::move(persons[1]), std::initializer_list({ IDs[0], IDs[2], IDs[3], IDs[4] }));
	vertices.emplace_back(std::move(persons[2]), std::initializer_list({ IDs[1] }));
	vertices.emplace_back(std::move(persons[3]), std::initializer_list({ IDs[0], IDs[1], IDs[4] }));
	vertices.emplace_back(std::move(persons[4]), std::initializer_list({ IDs[1], IDs[3] }));
	vertices.emplace_back(std::move(persons[5]), std::initializer_list({ IDs[6] }));
	vertices.emplace_back(std::move(persons[6]), std::initializer_list({ IDs[5] }));
}

//////////

int main()
{
	std::vector<Vertex> vertices;
	Setup(vertices);

	Graph graph(vertices);
	Run(graph, static_cast<int>(vertices.size()));
	
	return 0;
}