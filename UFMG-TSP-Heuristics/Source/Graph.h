#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

struct City {
	bool visited;

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

	// Nearest Neighbor Algorithm
	std::vector<size_t> GetTSPCitiesNN(int* walkDistance=nullptr);

	// NN + 2-Opt
	std::vector<size_t> GetTSPCities2Opt(int* walkDistance = nullptr, int iterations = 5);

	// Simulated Annealing
	std::vector<size_t> GetTSPCitiesAnnealing(int* walkDistance = nullptr, int iterations = 1000);

	/*==========
	// TSP Utils
	==========*/

	// 2-OPT Swap
	static std::vector<size_t> Swap2Opt(const std::vector<size_t>& route, size_t i, size_t k);

	// To recalculate the distance:
	int GetWalkDistance(const std::vector<size_t>& route);

	DistanceType distanceType;

	struct {
		float temperature;

		float stopTemperature;
		float alpha;
	} anneal;
protected:
	std::vector<City> m_cities;
};

#endif // !GRAPH_H