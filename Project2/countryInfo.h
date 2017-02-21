#ifndef PROJECT2_COUNTRYINFO_H
#define PROJECT2_COUNTRYINFO_H

int countryInfo(std::string inputFile, std::string outputFile);
int returnInfo(std::ofstream& output, std::string inputFile, std::string cmd, std::string country);
std::string returnCountry(std::string inputFile, std::string country);
std::string returnNeighbours(std::string inputFile, std::string country);
std::string size(std::string inputFile, std::string sizeType);

#endif /* PROJECT2_COUNTRYINFO_H */
