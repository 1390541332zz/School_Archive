#ifndef PROJECT2_COUNTRYINFO_H
#define PROJECT2_COUNTRYINFO_H

#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <limits>
#include <climits>
#include <cstdint>
#include <cctype>

int countryInfo(std::string commandFile, std::string outputFile);

int loadData(std::string inputFile, int state,             std::string& cCode,     \
             std::string& iso,      std::string& iso3,     std::string& isoNum,    \
             std::string& fips,     std::string& country,  std::string& capital,   \
             double& area,          long& pop,             std::string& continent, \
             std::string& tld,      std::string& curCode,  std::string& curName,   \
             std::string& phone,    std::string& postal,   std::string& regex,     \
             std::string& lang,     std::string& geoId,    std::string& neighbors, \
             std::string& altFips);

int returnInfo(std::ofstream& os,      std::string& iso,     std::string& iso3,    \
               std::string& isoNum,    std::string& fips,    std::string& country, \
               std::string& capital,   double& area,         long& pop,            \
               std::string& continent, std::string& tld,     std::string& curCode, \
               std::string& curName,   std::string& phone,   std::string& postal,  \
               std::string& regex,     std::string& lang,    std::string& geoId,   \
               std::string& neighbors,  std::string& altFips);

int seekCountry(std::ofstream& os, std::string& inputFile, std::string& cCode);
int seekNeighbors(std::ofstream& os, std::string& inputFile, std::string& cCode);
int size(std::ofstream& os, std::string& inputFile, std::string& sizeType);

//Print Without trailing whitespace
#define NOTRAILW(os, title, tab, str) do { \
    if(std::iscntrl(str.front())) { \
        str.clear(); \
    } \
    if(str.back() == ' ') { \
        str.pop_back();\
    } \
    if (!str.empty()) { \
        os << title << tab << str << std::endl; \
    } else { \
        os << title << std::endl; \
    } \
} while (0)

#endif /* PROJECT2_COUNTRYINFO_H */
