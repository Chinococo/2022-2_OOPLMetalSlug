#pragma once
#include <vector>

class CsvReader {
public:
	static void readCsv(
		std::vector<std::pair<int, int>> *animationRanges,
		std::vector<int> *animationDelays,
		int *animationFlipBias,
		std::vector<std::string> *paths,
		std::string character
	);
};
