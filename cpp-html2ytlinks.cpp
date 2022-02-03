#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include <filesystem>
#include <vector>
#include <regex>

std::vector<std::string> searchResults;

void searchF(std::string fileName, std::string searchTerm) {
	std::ifstream fileHandle(fileName);
	std::string searchBuffer;
	while (std::getline(fileHandle, searchBuffer)) {
		size_t where = 0;
		while (true) {
			std::string toSearch = searchBuffer.substr(where);
			size_t  location = toSearch.find(searchTerm);
			if (location != std::string::npos) {
				std::string match;
				match = toSearch.substr(location);
				std::string notyet;
				size_t pog = match.find('\"');
				if (pog != std::string::npos)
				{
					notyet = match.substr(0, pog);
					location = location + notyet.size();
				}
				searchResults.push_back(notyet);
				where = where + location;
			}
			else break;
		}
	}
	return;
}

int main(int argc, char** argv) {
	std::cout << "cpp-html2ytlinks, compiled at " << __DATE__ << ' ' << __TIME__ << ".\n\n";
	std::string pathInput;
	if (argc >= 2) {
		pathInput = argv[1];
		searchF(pathInput, "watch?v=");
	}
	else {
		std::cout << "html document to scan for youtube links: ";
		std::getline(std::cin, pathInput);
		searchF(pathInput, "watch?v=");
	}
	if ((std::adjacent_find(searchResults.begin(), searchResults.end()) != searchResults.end()) == true) {
		std::ofstream resultsFileHandle("results.txt");
		for (int i = 0; i < searchResults.size(); i++)
		{
			i++;
			std::cout << searchResults[i] << '\n';
			resultsFileHandle << searchResults[i] << '\n';
		}
		resultsFileHandle.close();
	}
	else {
		std::ofstream resultsFileHandle("results.txt");
		for (int i = 0; i < searchResults.size(); i++)
		{
			std::cout << searchResults[i] << '\n';
			resultsFileHandle << searchResults[i] << '\n';
		}
		resultsFileHandle.close();
	}
	return 0;
}
