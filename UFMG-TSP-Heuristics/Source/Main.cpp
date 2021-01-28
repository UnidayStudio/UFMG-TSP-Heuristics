#include <iostream>
#include <string>

#include <experimental/filesystem>

#include "Graph.h"
#include "Timer.h"

namespace fs = std::experimental::filesystem;

#define TEST_COUNT 1000

void Run(const std::string& path, Graph::DistanceType dType) {
	Graph att(path, dType);
	Timer timer;

	std::string fName = fs::path(path).stem().string();

	double avgDuration = 0.0;
	int distance;

	for (int i = 0; i < TEST_COUNT; i++) {
		timer.Reset();
		auto res = att.GetTSPCities(&distance);
		avgDuration += timer.Get();
	}

	avgDuration /= TEST_COUNT;

	std::cout << fName << ", " << distance << ", ";
	std::cout << std::fixed << avgDuration << "\n";
}

int main(int argc, char** argv) {
	Run("./Data/att48.tsp", Graph::ATT);
	
	for (auto& entry : fs::directory_iterator("./Data/EUC_2D/")) {
		std::string fName = entry.path().string();

		Run(fName, Graph::EUC_2D);
	}

	system("pause");
	return 0;
}