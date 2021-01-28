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

			int id, x, y;

			if (iss >> id >> x >> y) {
				m_cities.push_back({ 0, x, y });
			}
			else {
				break;
			}
		}
		else {
			if (line == "NODE_COORD_SECTION") {
				readingCoords = true;
			}
		}

	}

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

	if (m_cities.size() > 0) {
		for (auto& city : m_cities) {
			std::cout << city.x << ", " << city.y << "\n";
		}
	}

	if (walkDistance) { *walkDistance = distance; }
	return out;
}

