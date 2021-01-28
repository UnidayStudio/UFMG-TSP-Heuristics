#include "Graph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>


Graph::Graph() {

}

Graph::Graph(const std::string & path, DistanceType dType){
	distanceType = dType;

	std::ifstream file(path);

	std::string line;
	bool readingCoords = false;
	int dimension = 0;
	while (std::getline(file, line)) {
		if (line == "EOF") { break; }

		if (readingCoords) {
			std::istringstream iss(line);

			int id;
			double x, y;

			if (iss >> id >> x >> y) {
				m_cities.push_back({ false, int(x), int(y) });
			}
			else {
				throw std::exception("Invalid format!");
				break;
			}
		}
		else {
			if (line == "NODE_COORD_SECTION") {
				readingCoords = true;
			}
		}

	}

	file.close();
}

Graph::~Graph() {

}

int Graph::GetDistance(size_t cityA, size_t cityB){
	City& i = m_cities[cityA];
	City& j = m_cities[cityB];

	if (distanceType == DistanceType::EUC_2D) {
		auto xd = i.x - j.x;
		auto yd = i.y - j.y;
		return round(sqrt(xd * xd + yd * yd));
	}
	else if (distanceType == DistanceType::ATT) {
		auto xd = i.x - j.x;
		auto yd = i.y - j.y;
		int rij = sqrt((xd * xd + yd * yd) / 10.0);
		return round(rij);
	}
	throw std::exception("Invalid Distance Type!");
	return 0;
}

size_t Graph::GetCityCount(){
	return m_cities.size();
}

std::vector<size_t> Graph::GetTSPCities(int* walkDistance){
	std::vector<size_t> out;
	int distance = 0;

	// Reset all cities first
	for (auto& city : m_cities) {
		city.visited = false;
	}

	// To make sure that we get deterministic results, we'll
	// always start with the first city in the list.
	size_t current = 0;
	size_t firstCity = current;
	size_t remaining = m_cities.size() - 1;
	
	while (remaining > 0 && m_cities.size() > 0) {
		m_cities[current].visited = true;

		// First step: Find the nearest unvisited city.
		int nearest = -1;
		int nDistance = INT_MAX;
		for (size_t i = 0; i < m_cities.size(); i++) {
			if (m_cities[i].visited) {				
				continue;
			}
			int d = GetDistance(current, i);
			if (d < nDistance) {
				nearest = i;
				nDistance = d;
			}
		}
		if (nearest == -1) {
			throw std::exception("No city left!");
			break;
		}

		// Saving the results:
		out.push_back(current);
		current = nearest;
		distance += nDistance;
		
		remaining--;
	}
	// Now the Salesman needs to go back to the first
	// city he visited.
	out.push_back(firstCity);
	distance += GetDistance(current, firstCity);

	if (walkDistance) { *walkDistance = distance; }
	return out;
}

