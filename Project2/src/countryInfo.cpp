/*
 * Purpose for program: This program parses a file containing country info and
 * returns information about a countries, size, neighbors, and
 * general information.
 *
 * Programmer: Jacob Abel
 * Date: Febuary 27, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "countryInfo.h"

int countryInfo(std::string commandFile, std::string outputFile) {
    std::ifstream commands(commandFile);
    std::ofstream os(outputFile);
    std::string countryFile;
    std::string cmd;
    std::string arg;

    std::getline(commands, countryFile, ':');
    commands.ignore(1, '\n');

    if (countryFile == "Data File") {
        commands >> countryFile;
        os << "Data file: " << countryFile << std::endl;
    } else {
        std::cerr << countryFile << std::endl;
        std::cerr << "ERROR: Missing Data File!" << std::endl;
        commands.close();
        return -1;
    }

    while (commands >> cmd >> arg) {
        os << "Command: " << cmd << " " << arg << std::endl;
        if (cmd == "size") {
            size(os, countryFile, arg);
        } else if (cmd == "country") {
            seekCountry(os, countryFile, arg);
        } else if (cmd == "neighbors") {
            seekNeighbors(os, countryFile, arg);
        } else {
            std::cerr << "ERROR: Invalid Command" << std::endl;
        }

    }

    commands.close();
    os.close();
    return 0;
}

int loadData(std::string inputFile, int state,             std::string& cCode,     \
             std::string& iso,      std::string& iso3,     std::string& isoNum,    \
             std::string& fips,     std::string& country,  std::string& capital,   \
             double& area,          long& pop,             std::string& continent, \
             std::string& tld,      std::string& curCode,  std::string& curName,   \
             std::string& phone,    std::string& postal,   std::string& regex,     \
             std::string& lang,     std::string& geoId,    std::string& neighbors, \
             std::string& altFips) {

    std::ifstream is(inputFile);
    std::string nList;
    std::string areaString;
    std::string popString;
    double size = -1;
    long cCount = 0;

    while (!is.fail() && (state == 0 ? cCode != iso : true)) {
        if (is.peek() == '#') {
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::getline(is, iso,        '\t');
            std::getline(is, iso3,       '\t');
            std::getline(is, isoNum,     '\t');
            std::getline(is, fips,       '\t');
            std::getline(is, country,    '\t');
            std::getline(is, capital,    '\t');
            std::getline(is, areaString, '\t');
            std::getline(is, popString,  '\t');
            std::getline(is, continent,  '\t');
            std::getline(is, tld,        '\t');
            std::getline(is, curCode,    '\t');
            std::getline(is, curName,    '\t');
            std::getline(is, phone,      '\t');
            std::getline(is, postal,     '\t');
            std::getline(is, regex,      '\t');
            std::getline(is, lang,       '\t');
            std::getline(is, geoId,      '\t');
            std::getline(is, neighbors,  '\t');
            std::getline(is, altFips,    '\n');
            area = std::stod(areaString);
            pop  = std::stol(popString);

            if (is.fail()) break;
            
            switch (state) {
                case 0:
                    break;
                case 1: //Average
                    if (size == -1) size = 0;
                    cCode = "";
                    cCount++;
                    size += area;
                    
                    std::cout << cCount << iso << '|' << area << '|' << size << std::endl;
                    break;
                case 2: //Max
                    if (area > size) {
                        size = area;
                        cCode = iso;
                    }
                    break;
                case 3: //Min
                    if (size == -1) size = LONG_MAX;
                    if (area < size) {
                        size = area;
                        cCode = iso;
                    }
                    break;
                case 4: //Neighbor Search
                    if (neighbors.find(cCode) != std::string::npos) {
                        nList.append(iso);
                        nList.push_back(',');
                    }
                    break;
                default:
                    std::cerr << "ERROR: Invalid Size Type!" << std::endl;
                    return -1;
            }
        }
    }
    
    if (cCode != iso || state == 4) {
        iso       = "";    iso3      = "";    isoNum  = "";    fips    = "";
        country   = "";    capital   = "";    area    =  0;    pop     =  0;
        continent = "";    tld       = "";    curCode = "";    curName = "";
        phone     = "";    postal    = "";    regex   = "";    lang    = "";
        geoId     = "";    neighbors = "";    altFips = "";
    }

    switch (state) {
        case 0:
            break;
        case 1: //Average
            pop  = cCount;
            area = size;
            iso  = "__AVERAGE";
            break;
        case 2: //Max
            loadData(inputFile, 0, cCode, iso, iso3, isoNum, fips, country,    \
                     capital, area, pop, continent, tld, curCode, curName,     \
                     phone, postal, regex, lang, geoId, neighbors, altFips);
            break;
        case 3: //Min
            loadData(inputFile, 0, cCode, iso, iso3, isoNum, fips, country,    \
                     capital, area, pop, continent, tld, curCode, curName,     \
                     phone, postal, regex, lang, geoId, neighbors, altFips);
            break;
        case 4:
            neighbors = nList;
            iso = "__NEIGHBORS";
    }

    is.close();
    return 0;
}

int returnInfo(std::ofstream& os,      std::string& iso,     std::string& iso3,    \
               std::string& isoNum,    std::string& fips,    std::string& country, \
               std::string& capital,   double& area,         long& pop,            \
               std::string& continent, std::string& tld,     std::string& curCode, \
               std::string& curName,   std::string& phone,   std::string& postal,  \
               std::string& regex,     std::string& lang,    std::string& geoId,   \
               std::string& neighbors,  std::string& altFips) {
    os << std::left << std::fixed << std::setprecision(2);
    NOTRAILW(os, "\tISO:",              "\t\t\t", iso);
    NOTRAILW(os, "\tISO3:",             "\t\t\t", iso3);
    NOTRAILW(os, "\tISO Numeric:",        "\t\t", isoNum);
    NOTRAILW(os, "\tFIPS:",             "\t\t\t", fips);
    NOTRAILW(os, "\tCountry:",            "\t\t", country);
    NOTRAILW(os, "\tCapital:",            "\t\t", capital);
    os        << "\tArea:"           << "\t\t\t" << area << std::endl;
    os        << "\tPopulation:"       << "\t\t" << pop  << std::endl;
    NOTRAILW(os, "\tContinent:",          "\t\t", continent);
    NOTRAILW(os, "\tTLD:",              "\t\t\t", tld);
    NOTRAILW(os, "\tCurrency Code:",      "\t\t", curCode);
    NOTRAILW(os, "\tCurrency Name:",      "\t\t", curName);
    NOTRAILW(os, "\tPhone:",            "\t\t\t", phone);
    NOTRAILW(os, "\tPostal Code:",        "\t\t", postal);
    NOTRAILW(os, "\tPostal Code Regex:",    "\t", regex);
    NOTRAILW(os, "\tLanguages:",          "\t\t", lang);
    NOTRAILW(os, "\tGeonameid:",          "\t\t", geoId);
    NOTRAILW(os, "\tNeighbors:",          "\t\t", neighbors);
    NOTRAILW(os, "\tEquiv FIPS Code:",      "\t", altFips);
    return 0;
}


int seekCountry(std::ofstream& os, std::string& inputFile, std::string& cCode) {
    double area = 0;
    long pop = 0;
    std::string iso, iso3, isoNum, fips, country, capital, continent, tld,     \
    curCode, curName, phone, postal, regex, lang, geoId, neighbors, altFips;

    loadData(inputFile, 0, cCode, iso, iso3, isoNum, fips, country, capital,   \
             area, pop, continent, tld, curCode, curName, phone, postal,       \
             regex, lang, geoId, neighbors, altFips);
    if (cCode == iso) {
        returnInfo(os, iso, iso3, isoNum, fips, country, capital, area, pop,   \
                   continent, tld, curCode, curName, phone, postal, regex,     \
                   lang, geoId, neighbors, altFips);
    } else {
        os << "\tCountry " << cCode << " not found." << std::endl;
    }
    return 0;
}

int seekNeighbors(std::ofstream& os, std::string& inputFile, std::string& cCode) {
    double area = 0;
    long pop = 0;
    std::string iso, iso3, isoNum, fips, country, capital, continent, tld,     \
    curCode, curName, phone, postal, regex, lang, geoId, neighbors, altFips;

    loadData(inputFile, 4, cCode, iso, iso3, isoNum, fips, country, capital,   \
             area, pop, continent, tld, curCode, curName, phone, postal,       \
             regex, lang, geoId, neighbors, altFips);
    
    
    
    if(neighbors.length() >= 2) {
        std::string nList = neighbors;
        size_t i = 1;
        for (size_t j = 0; j < nList.length(); j += 3) {
            std::string nCode = nList.substr(j, 2);
            std::cout << nList << j << i << std::endl;
            os << "Neighbor " << i++ << std::endl;
            loadData(inputFile, 0, nCode, iso, iso3, isoNum, fips, country,    \
                     capital, area, pop, continent, tld, curCode, curName,     \
                     phone, postal, regex, lang, geoId, neighbors, altFips);
            returnInfo(os, iso, iso3, isoNum, fips, country, capital, area,    \
                       pop, continent, tld, curCode, curName, phone, postal,   \
                       regex, lang, geoId, neighbors, altFips);
            std::cout << "survival" << std::endl;
        }
    } else {
        os << "\tCountry " << cCode << " has no neighbors." << std::endl;
    }
    return 0;
}

int size(std::ofstream& os, std::string& inputFile, std::string& sizeType) {
    double area = 0;
    long pop = 0;
    std::string cCode, iso, iso3, isoNum, fips, country, capital, continent,   \
    tld, curCode, curName, phone, postal, regex, lang, geoId, neighbors,       \
    altFips;
    
    if (sizeType == "average") {
        loadData(inputFile, 1, cCode, iso, iso3, isoNum, fips, country,        \
                 capital, area, pop, continent, tld, curCode, curName, phone,  \
                 postal, regex, lang, geoId, neighbors, altFips);
        double avg = area /  pop;
        os << std::fixed << std::setprecision(2);
        os << '\t' << "Sum: "           << area << std::endl;
        os << '\t' << "Country count: " << pop  << std::endl;
        os << '\t' << "Average Size: "  << avg  << std::endl;

    } else if (sizeType == "largest") {
        loadData(inputFile, 2, cCode, iso, iso3, isoNum, fips, country,        \
                 capital, area, pop, continent, tld, curCode, curName, phone,  \
                 postal, regex, lang, geoId, neighbors, altFips);
        returnInfo(os, iso, iso3, isoNum, fips, country, capital, area, pop,   \
                   continent, tld, curCode, curName, phone, postal, regex,     \
                   lang, geoId, neighbors, altFips);
    } else if (sizeType == "smallest") {
        loadData(inputFile, 3, cCode, iso, iso3, isoNum, fips, country,        \
                 capital, area, pop, continent, tld, curCode, curName, phone,  \
                 postal, regex, lang, geoId, neighbors, altFips);
        returnInfo(os, iso, iso3, isoNum, fips, country, capital, area, pop,   \
                   continent, tld, curCode, curName, phone, postal, regex,     \
                   lang, geoId, neighbors, altFips);
    } else {
        std::cerr << "ERROR: Invalid Size Type!" << std::endl;
        return -1;
    }

    return 0;
}
