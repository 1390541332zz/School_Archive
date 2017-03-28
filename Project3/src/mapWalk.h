#ifndef PROJECT3_MAPWALK_H
#define PROJECT3_MAPWALK_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include <climits>
#include <cmath>

enum command {MAXUP, MAXDOWN, MINDIFF};

#define ROW 15
#define COL 20

#define MAPW 5
#define PATHW 3
#define NSIDES 5
#define ILLEGALVAL(val) ((val == MAXUP) ? -INT_MAX : INT_MAX)
#define MAXDIM(fixedArr, dynArr) ((dynArr < fixedArr) ? dynArr : fixedArr)

int mapWalk(std::string inputFile, std::string outputFile);
int minMaxElement(int adj[NSIDES], bool isMax);
void fillRegion(int map[ROW][COL], int i1, int i2, int j1, int j2, int val);
void loadMap(std::string inputFile, int map[ROW][COL], int dims[2]);
void printMap(std::ofstream& os, int map[ROW][COL], int dims[2], bool isMap);
void traverseMap(std::ofstream& os, int map[ROW][COL], int dims[2], int startPos, command cmd);
void assignAdjacent(int adj[NSIDES], int map[ROW][COL], int dims[2], command& cmd, int& adjPos, int& i, int& j);

#endif /* PROJECT3_MAPWALK_H */