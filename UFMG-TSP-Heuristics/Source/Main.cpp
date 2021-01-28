#include <iostream>
#include <string>

#include <experimental/filesystem>

#include "Graph.h"
#include "Timer.h"

namespace fs = std::experimental::filesystem;


int main(int argc, char** argv) {
	Timer timer;
	{
		Graph att("./Data/att48.tsp", Graph::ATT);

		int distance;
		
		timer.Reset();
		auto res = att.GetTSPCities(&distance);
		double duration = timer.Get();

		std::string fName = "att48.tsp";
		std::cout << fName << ", " << distance;
		std::cout << ", " << duration << "\n";
	}

	for (auto& entry : fs::directory_iterator("./Data/EUC_2D/")) {
		std::string fName = entry.path().string();

		Graph euc(fName, Graph::EUC_2D);

		int distance;

		timer.Reset();
		auto res = euc.GetTSPCities(&distance);
		double duration = timer.Get();

		fName = fs::path(fName).filename().string();
		std::cout << fName << ", " << distance;
		std::cout << ", " << duration << "\n";
	}

	system("pause");
	return 0;
}