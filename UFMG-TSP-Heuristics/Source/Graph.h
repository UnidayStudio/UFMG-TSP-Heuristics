#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

struct City {
	// Stores how many times the Salesman visited the city.
	// For the TSP, it will never be more than 1.
	int visits;

	// Coordinates
	int x, y;
};

class Graph {
public:
	enum DistanceType {
		EUC_2D,
		ATT
	};

	Graph();
	Graph(const std::string& path, DistanceType dType);
	virtual ~Graph();

	/*======================================
	// Utils methods to manipulate the graph
	======================================*/

	int GetDistance(size_t cityA, size_t cityB);
	size_t GetCityCount();

	/*====================================
	// Travelling Salesman Problem Related
	====================================*/

	std::vector<size_t> GetTSPCities(int* walkDistance=nullptr);

	DistanceType distanceType;
protected:
	std::vector<City> m_cities;
};

#endif // !GRAPH_H