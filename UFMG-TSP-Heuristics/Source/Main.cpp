#include <iostream>
#include <string>

#include "Graph.h"
#include "Timer.h"

#ifdef _MSC_VER
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
// If you're not using Visual Studio (MSVC), please use
// C++17 and check if your compiler have the filesystem lib!
#include <filesystem>
namespace fs = std::filesystem;
#endif

#define TEST_COUNT 10

void Run(const std::string& path, Graph::DistanceType dType) {
	Graph att(path, dType);
	Timer timer;

	std::string fName = fs::path(path).stem().string();

	double avgDuration = 0.0;
	int distance;

	for (int i = 0; i < TEST_COUNT; i++) {
		timer.Reset();
		//auto res = att.GetTSPCitiesNN(&distance);
		//auto res = att.GetTSPCities2Opt(&distance, 100);
		auto res = att.GetTSPCitiesAnnealing(&distance, 1000);
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