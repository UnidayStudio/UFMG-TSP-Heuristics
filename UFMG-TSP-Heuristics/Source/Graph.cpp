#include "Graph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

// For the code to compile using MingW...
#ifndef INT_MAX
#define INT_MAX 2147483647
#endif 


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
#ifdef _MSC_VER
				throw std::exception("Invalid format!");
#endif
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
#ifdef _MSC_VER
	throw std::exception("Invalid Distance Type!");
#endif
	return 0;
}

size_t Graph::GetCityCount(){
	return m_cities.size();
}

std::vector<size_t> Graph::GetTSPCitiesNN(int* walkDistance){
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
#ifdef _MSC_VER
			throw std::exception("No city left!");
#endif
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

std::vector<size_t> Graph::GetTSPCities2Opt(int * walkDistance, int iterations){
	// Start with the NN solution:
	int currentDistance;
	auto current = GetTSPCitiesNN(&currentDistance);
	currentDistance = GetWalkDistance(current);
	
	// Needs at least 5 cities for this to make sense. If it's less than 3,
	// then there is no circle and the path doesn't make sense (invalid).
	// If it's 4, the circle is a triangle (first and last cities are the same)
	// and a triangle already have the best path.
	if (current.size() < 5) {
		*walkDistance = currentDistance;
		return current;
	}

	// Just to compare it in the end
	int startDistance = currentDistance;
	auto startPath = current;

	int routeSize = current.size();

	for (int attempt = 0; attempt < iterations; attempt++) {
		// Note: The first and the last city can't be included
		// here since they MUST be the same.
		for (int i = 1; i < routeSize - 3; i++) {
			bool breakThis = false;

			for (int k = i + 1; k < routeSize - 2; k++) {
				auto newRoute = Swap2Opt(current, i, k);				
				int newDistance = GetWalkDistance(newRoute);

				if (newDistance < currentDistance) {
					currentDistance = newDistance;
					current = newRoute;

					breakThis = true;
					break;
				}
			}
			if (breakThis) {
				break;
			}
		}
	}

	//std::cout << " - Start: " << startDistance << ", end: " << currentDistance;
	//std::cout << ". Reduction: " << 1.f - float(currentDistance) / float(startDistance);
	//std::cout << "\n";

	*walkDistance = currentDistance;
	return current;
}

std::vector<size_t> Graph::Swap2Opt(const std::vector<size_t>& route, size_t i, size_t k){
	std::vector<size_t> out;

	// Step 1: Add route[0] to route[i-1] into the output
	for (int x = 0; x < i - 1; x++) {
		out.push_back(route[x]);
	}

	// Step 2: Add route[i] to route[k] bu reversed into the output
	for (int x = k; x >= i ; x--) {
		out.push_back(route[x]);
	}

	// Step 3: Add route[k+1] to end into the output
	for (int x = k; x < route.size(); x++) {
		out.push_back(route[x]);
	}

	return out;
}

int Graph::GetWalkDistance(const std::vector<size_t>& route){
	if (route.size() <= 1) {
		return 0;
	}
	int out = GetDistance(route[route.size() - 1], route[0]);

	for (int i = 0; i < route.size() - 1; i++) {
		out += GetDistance(route[i], route[i + 1]);
	}

	return out;
}

