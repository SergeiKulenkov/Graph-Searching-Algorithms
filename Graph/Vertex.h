#pragma once
#include <vector>
#include <string>

class Person
{
public:
	Person() : m_Id(-1), m_Name(""), m_Age(0)
	{ }

	Person(const int ID, const std::string& name, const int age) : 
			m_Id(ID), m_Name(name), m_Age(age)
	{ }

	Person(const Person& person) : 
			m_Id(person.m_Id), m_Name(person.m_Name), m_Age(person.m_Age)
	{ }

	Person(Person&& person) : 
			m_Id(person.m_Id), m_Name(person.m_Name), m_Age(person.m_Age)
	{ }

	int GetID() const { return m_Id; }

	std::string GetName() const { return m_Name; }

	int GetAge() const { return m_Age; }

private:
	int m_Id;
	std::string m_Name;
	int m_Age;
};

///////////////////////////////

class Vertex
{
public:
	Vertex() { }

	Vertex(const Vertex& vertex) : 
			m_Data(vertex.m_Data), m_AdjacentIDs(vertex.m_AdjacentIDs)
	{ }

	Vertex(Vertex&& vertex) : 
			m_Data(std::move(vertex.m_Data)), m_AdjacentIDs(vertex.m_AdjacentIDs)
	{ }

	Vertex(const Person& data) : m_Data(data)
	{ }

	Vertex(Person&& data) : m_Data(std::move(data))
	{ }

	Vertex(const Person& data, const std::vector<int>& adjacent) : 
			m_Data(data), m_AdjacentIDs(adjacent)
	{ }

	Vertex(Person&& data, std::vector<int>& adjacent) : 
			m_Data(std::move(data)), m_AdjacentIDs(adjacent)
	{ }

	int GetID() const { return m_Data.GetID(); }

	const std::vector<int>& GetAdjacentIDs() const { return m_AdjacentIDs; }

private:
	Person m_Data;
	std::vector<int> m_AdjacentIDs;
};