#include "stdafx.h"
#include "../header/GameStorage.h"

void CsvReader::readCsv(
	std::vector<std::pair<int, int>> *animationRanges,
	std::vector<int> *animationDelays,
	int *animationFlipBias,
	std::vector<std::string> *paths,
	std::string character
) {
	std::vector<std::vector<std::string>> csv = readCSV("resources/csv/character.csv");
	std::pair<int, int> range;

	for (size_t i = 1; i < csv.size(); i++) {
		if (csv[i][0] != character)
			continue;

		int delay = std::stoi(csv[i][3]);
		std::string prefix = csv[i][2];
		range = { std::stoi(csv[i][1].substr(0, csv[i][1].find('~'))), std::stoi(csv[i][1].substr(csv[i][1].find('~') + 1)) };

		for (int i = 0; i < range.second - range.first; i++) {
			paths->push_back(prefix + std::to_string(i) + ".bmp");
		}

		animationRanges->push_back(range);
		animationDelays->push_back(delay);
	}

	*animationFlipBias = range.second;

	// filp
	for (size_t i = 1; i < csv.size(); i++) {
		if (csv[i][0] != character)
			continue;

		int delay = std::stoi(csv[i][3]);
		std::string prefix = csv[i][2];
		range = { std::stoi(csv[i][1].substr(0, csv[i][1].find('~'))), std::stoi(csv[i][1].substr(csv[i][1].find('~') + 1)) };

		for (int i = 0; i < range.second - range.first; i++) {
			paths->push_back(prefix + "flip_" + std::to_string(i) + ".bmp");
		}

		animationRanges->push_back(range);
		animationDelays->push_back(delay);
	}
}
