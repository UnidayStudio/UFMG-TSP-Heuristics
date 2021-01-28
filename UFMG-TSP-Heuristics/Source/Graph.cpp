#include "Graph.h"

#include <fstream>
#include <cmath>
#include <thread>

Graph::Graph() {

}

Graph::Graph(const std::string & path, DistanceType dType){
	distanceType = dType;
}

Graph::~Graph() {

}

int Graph::GetDistance(size_t cityA, size_t cityB){
	City& i = m_cities[cityA];
	City& j = m_cities[cityB];

	if (distanceType == DistanceType::EUC_2D) {
		int xd = i.x - j.x;
		int yd = i.y - j.y;
		return round(sqrt(xd * xd + yd * yd));
	}
	else if (distanceType == DistanceType::ATT) {
		int xd = i.x - j.x;
		int yd = i.y - j.y;
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

	using namespace std::chrono_literals;
	std::this_thread::sleep_for(10ms);

	if (walkDistance) {
		*walkDistance = distance;
	}
	return out;
}

