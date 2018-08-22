/*
 * Purpose for program: This program evaluates a map file and determines a 
 * route based on change in elevation program.
 *
 * Programmer: Jacob Abel
 * Date: March 23, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "mapWalk.h"

int mapWalk(std::string inputFile, std::string outputFile) {
    std::ifstream cmds(inputFile);
    std::ofstream os(outputFile);
    std::string mapFile, cmd, strA, strB;
    int map[ROW][COL] = {0};
    int dims[2] = {0};
    int startPos = 0;
    
    if (cmds >> strA && strA == "File:") {
        cmds >> mapFile;
        os << std::left << "Loading: " << mapFile << std::endl;
        loadMap(mapFile, map, dims);
        printMap(os, map, dims, true);
    } else {
        std::cerr << "ERROR: Missing Data File!" << std::endl;
        cmds.close();
        os.close();
        return -1;
    }
    while (cmds >> strA >> strB >> startPos) {
        cmd = strA + " " + strB; 
        os << std::left << "Command: " << cmd << std::endl;
        if (cmd == "Greatest Inclination") {
            traverseMap(os, map, dims, startPos, MAXUP);
        } else if (cmd == "Greatest Declination") {
            traverseMap(os, map, dims, startPos, MAXDOWN);
        } else if (cmd == "Least Elevation") {
            traverseMap(os, map, dims, startPos, MINDIFF);
        } else {
            std::cerr << "ERROR: Invalid Command" << std::endl;
        }
    }
    cmds.close();
    os.close();
    return 0;
}

//Takes a range of rows(i1 to i2) and columns(j1 to j2) and fills with val
void fillRegion(int map[ROW][COL], int i1, int i2, int j1, int j2, int val) {
    for (int i = i1; i <= i2; i++) {
        for (int j = j1; j <= j2; j++) {
            map[i][j] = val;
        }
    }
}

//Finds the minimum or maximum element
int minMaxElement(int adj[NSIDES], bool isMax) {
    int max = 0;
    int cur = 0;
    while (cur < NSIDES) {
        if (isMax ? (adj[max] < adj[cur]) : (adj[max] > adj[cur])) max = cur;
        cur++;
    }
    return max;
}

// Loads the elevation map into an array.
void loadMap(std::string inputFile, int map[ROW][COL], int dims[2]) {
    std::ifstream is(inputFile);
    std::string tmp;

    is >> tmp >> dims[1];
    is >> tmp >> dims[0];
    for (int i = 3; i <= 6; i++) {
        if (!is.fail()) is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (i < dims[0] && j < dims[1] && !is.fail()) {
                is >> map[i][j];
            } else if (!is.fail()) {
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (j >= dims[1]) j = COL;
                if (i >= dims[0]) {
                    i = ROW;
                    j = COL;
                }
            } else if (is.fail()) {
                std::cerr << "ERROR: Unexpected File Error!" << std::endl;
                return;
            }
            if (is.peek() != '\n' && j >= COL-1 && dims[1] > COL) {
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    is.close();
}

// Prints an ASCII Map of the elevations or a path.
void printMap(std::ofstream& os, int map[ROW][COL], int dims[2], bool isMap) {
    os << std::left;
    os << "Number of rows: "    << MAXDIM(ROW, dims[0]) << std::endl;
    os << "Number of columns: " << MAXDIM(COL, dims[1]) << std::endl;
    os << '\t' << std::setw(isMap ? MAPW : PATHW) << ' ' << std::right;
    for (int i = 0; i < MAXDIM(COL, dims[1]); i++) {
        os << std::setw(isMap ? MAPW : PATHW) << i;
    }
    os << std::endl;
    for (int i = 0; i < MAXDIM(ROW, dims[0]); i++) {
        os << '\t' << std::setw(isMap ? MAPW : PATHW-1) << i;
        if (!isMap) os << ' ';
        for (int j = 0; j < MAXDIM(COL, dims[1]); j++) {
            if (isMap) {
                os << std::setw(MAPW) << map[i][j];
            } else {
                os << std::setw(PATHW) << static_cast<char>(map[i][j]);
            }
        }
        os << std::endl;
    }
    os << '\t' << std::endl;
}

// Navigates the map and generates a path.
void traverseMap(std::ofstream& os, int map[ROW][COL], int dims[2], int startPos, command cmd) {    
    int adj[NSIDES] = {0};
    int steps = 0;
    int sum = 0;
    int adjPos = -1;
    int i = startPos;
    int j = 0;
    
    int path[ROW][COL];
    fillRegion(path, 0, ROW - 1, 0, COL - 1, '-');

    if (startPos >= MAXDIM(ROW, dims[0]) || startPos < 0) {
        os << std::left << "Bad starting row: " << startPos << std::endl;
        return;
    }
    while (j < MAXDIM(COL, dims[1])-1) {
        assignAdjacent(adj, map, dims, cmd, adjPos, i, j);
        movePos(path, adj, dims, adjPos, i, j, steps, sum, cmd);
    }
    os << std::left;
    os << '\t' << std::setw(16) << "Height change: "  << sum   << std::endl;
    os << '\t' << std::setw(16) << "Steps: "          << steps << std::endl;
    os << '\t' << std::setw(16) << "Average change: " \
       << static_cast<double>(sum) / static_cast<double>(steps) << std::endl;
    os << '\t' << std::setw(16) << "Starting row: "   << startPos << std::endl;
    printMap(os, path, dims, false);
}

void movePos(int path[ROW][COL], int adj[NSIDES], int dims[2], int& adjPos, int& i, int& j, int& steps, int& sum, command cmd) {
    // Up, Upper Right, Right, Lower Right, Down
    const char pos[NSIDES] = {'^', '/', '>', '\\', 'v'};
    switch (cmd) {
        case MAXUP:
            adjPos = minMaxElement(adj, true);
            break;
        case MAXDOWN:
            adjPos = minMaxElement(adj, false);
            break;
        case MINDIFF:
            int adjAbs[NSIDES] = {0};
            for (int i = 0; i < NSIDES; i++) {
                adjAbs[i] = std::abs(adj[i]);
            }
            adjPos = minMaxElement(adjAbs, false);
            break;
    }
    path[i][j] = pos[adjPos];
    if (adjPos > 0 && adjPos < 4) j++;  // Moving Forward
    if (adjPos < 2) i--;                // Moving Up
    if (adjPos > 2) i++;                // Moving Down
    if (j >= MAXDIM(COL, dims[1]) - 1) path[i][j] = 'X';
    sum += adj[adjPos];
    steps++;
}

void assignAdjacent(int adj[NSIDES], int map[ROW][COL], int dims[2], command& cmd, int& adjPos, int& i, int& j) {
    adj[0] = (i > 0)                                                     ? (map[i-1][ j ] - map[i][j]) : ILLEGALVAL(cmd);
    adj[1] = (i > 0                       && j < MAXDIM(COL, dims[1])-1) ? (map[i-1][j+1] - map[i][j]) : ILLEGALVAL(cmd);
    adj[2] =                                (j < MAXDIM(COL, dims[1])-1) ? (map[ i ][j+1] - map[i][j]) : ILLEGALVAL(cmd);
    adj[3] = (i < MAXDIM(ROW, dims[0])-1  && j < MAXDIM(COL, dims[1])-1) ? (map[i+1][j+1] - map[i][j]) : ILLEGALVAL(cmd);
    adj[4] = (i < MAXDIM(ROW, dims[0])-1)                                ? (map[i+1][ j ] - map[i][j]) : ILLEGALVAL(cmd);
    if(adjPos == 0 || adjPos == 4) adj[NSIDES - 1 - adjPos] = ILLEGALVAL(cmd);
}