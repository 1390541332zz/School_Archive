/*
 * Purpose for program: Google Unit Tests for mapWalk.cpp
 *
 * Programmer: Jacob Abel
 * Date: March 23, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "mapWalk.h"
#include <gtest/gtest.h>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <array>

//Helper Functions
void initAdjArr(std::array<int, NSIDES> arr) {
    std::srand(std::time(0));
    for (size_t i = 0; i < NSIDES; i++) {
        arr[i] = (std::rand() & 1) ? std::rand() : -std::rand();
    }
}

void initDimsArr(int dims[2]) {
    std::srand(std::time(0));
    dims[0] = std::rand()%(ROW*2)+1;
    dims[1] = std::rand()%(COL*2)+1;
}

void initMapArr(int map[ROW][COL], int dims[2]) {
    std::srand(std::time(0));
    for (int i = 0; i < dims[0]; i++) {
        for (int j = 0; j < dims[1]; j++) {
            if (i < ROW && j < COL) map[i][j] = std::rand()%65536;
        }
    }
}

void initPos(int dims[2], int& i, int& j) {
    std::srand(std::time(0));
    i = std::rand()%MAXDIM(ROW, dims[0]);
    j = std::rand()%MAXDIM(COL, dims[1]);
}

command randCmd() {
    std::srand(std::time(0));
    return static_cast<command>(std::rand()%3);
}

int absFun(int i) {
    return std::abs(i);
}

//Unit Tests
TEST(MinMaxElement, Max) {
    std::array<int, NSIDES> arr = {0};
    initAdjArr(arr);
    ASSERT_EQ(*std::max_element(arr.begin(), arr.end()), \
              arr[minMaxElement(arr.data(), true)]);
}

TEST(MinMaxElement, Min) {
    std::array<int, NSIDES> arr = {0};
    initAdjArr(arr);
    ASSERT_EQ(*std::min_element(arr.begin(), arr.end()), \
              arr[minMaxElement(arr.data(), false)]);
}

TEST(FillRegion, Fill) {
    std::srand(std::time(0));
    int fillVal = std::rand();
    int arr[ROW][COL] = {0};
    fillRegion(arr, 0, ROW-1, 0, COL-1, fillVal);
    for (size_t i = 0; i < ROW; i++) {
        for (size_t j = 0; j < COL; j++) {
            ASSERT_EQ(arr[i][j], fillVal);
        }
    }
}

TEST(AssignAdjacent, Boundary) {
    int adj[NSIDES] = {0};
    int map[ROW][COL] = {0};
    int dims[2] = {0};
    int adjPos = -1;
    command cmd = randCmd();
    initDimsArr(dims);
    initMapArr(map, dims);

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            assignAdjacent(adj, map, dims, cmd, adjPos, i, j);
            for (int k = 0; k < NSIDES; k++) {
                if (adjPos == k) ASSERT_EQ(ILLEGALVAL(cmd), adj[adjPos]);
                if ((k == 0 && i > 0) || \
                    (k == 1 && i > 0                      && j < MAXDIM(COL, dims[1])-1) || \
                    (k == 2                               && j < MAXDIM(COL, dims[1])-1) || \
                    (k == 3 && i < MAXDIM(ROW, dims[0])-1 && j < MAXDIM(COL, dims[1])-1) || \
                    (k == 4 && i < MAXDIM(ROW, dims[0])-1)) {
                    ASSERT_NE(adj[k], ILLEGALVAL(cmd)) << dims[0] << ' '<< dims[1] << " k " << k << " i " << i << " j " << j;
                }
            }
            if (i < 1) {
                ASSERT_EQ(ILLEGALVAL(cmd), adj[0]);
                ASSERT_EQ(ILLEGALVAL(cmd), adj[1]);
            }
            if (i >= MAXDIM(ROW, dims[0])-1) {
                ASSERT_EQ(ILLEGALVAL(cmd), adj[3]);
                ASSERT_EQ(ILLEGALVAL(cmd), adj[4]);
            }
            if (j >= MAXDIM(COL, dims[1])-1) {
                ASSERT_EQ(ILLEGALVAL(cmd), adj[1]);
                ASSERT_EQ(ILLEGALVAL(cmd), adj[2]);
                ASSERT_EQ(ILLEGALVAL(cmd), adj[3]);
            }
        }
    }
}

TEST(AssignAdjacent, Selection) {
    int adj[NSIDES] = {0};
    int map[ROW][COL] = {0};
    int dims[2] = {0};
    int adjPos = -1;
    int i = 0;
    int j = 0;
    command cmd = randCmd();
    initDimsArr(dims);
    initMapArr(map, dims);
    initPos(dims, i, j);
    assignAdjacent(adj, map, dims, cmd, adjPos, i, j);
    
    for (int i = 1; i < MAXDIM(ROW, dims[0])-1; i++) {
        for (int j = 1; j < MAXDIM(COL, dims[1])-1; j++) {
            for (int k = 0; k < NSIDES; k++) {
                if (adjPos == k) ASSERT_EQ(ILLEGALVAL(cmd), adj[adjPos]); 
            }
            assignAdjacent(adj, map, dims, cmd, adjPos, i, j);
            if (adjPos != 0) ASSERT_EQ(adj[0], map[i-1][ j ] - map[i][j]);
            if (adjPos != 1) ASSERT_EQ(adj[1], map[i-1][j+1] - map[i][j]);
            if (adjPos != 2) ASSERT_EQ(adj[2], map[ i ][j+1] - map[i][j]);
            if (adjPos != 3) ASSERT_EQ(adj[3], map[i+1][j+1] - map[i][j]);
            if (adjPos != 4) ASSERT_EQ(adj[4], map[i+1][ j ] - map[i][j]);
        }
    }
}

TEST(LoadMap, Load) {
    std::srand(std::time(0));
    std::string mapFile = "test/generated/loadmap.test";
    std::ofstream os(mapFile);
    int dimTest[2] = {0};
    int mapTest[ROW][COL] = {0};
    int dims[2] = {0};
    int map[ROW][COL] = {0};
    
    initDimsArr(dimTest);
    initMapArr(mapTest, dimTest);
    
    os << std::left << std::setw(13) << "ncols"     << dimTest[1]  << std::endl;
    os << std::left << std::setw(13) << "nrows"     << dimTest[0]  << std::endl;
    os << std::left << std::setw(13) << "xllcorner" << std::rand() << std::endl;
    os << std::left << std::setw(13) << "yllcorner" << std::rand() << std::endl;
    os << std::left << std::setw(13) << "cellsize"  << std::rand() << std::endl;
    for (int i = 0; i < MAXDIM(ROW, dimTest[0]); i++) {
        for (int j = 0; j < MAXDIM(COL, dimTest[1]); j++) {
            os << ' ' << mapTest[i][j];
        }
        os << std::endl;
    }
    if(os.fail()) return;
    os.close();
    
    loadMap(mapFile, map, dims);
    
    ASSERT_EQ(dims[0], dimTest[0]);
    ASSERT_EQ(dims[1], dimTest[1]);
    
    for (int i = 0; i < MAXDIM(ROW, dims[0]); i++) {
        for (int j = 0; j < MAXDIM(COL, dims[1]); j++) {
            ASSERT_EQ(map[i][j], mapTest[i][j]) << "i: " << i << " j: " << j;
        }
    }
}

TEST(MovePos, Navigate) {
    std::array<int, NSIDES> adj = {0};
    int map[ROW][COL] = {0};
    int dims[2] = {0};
    int adjPos = -1;
    int steps = 0;
    int sum = 0;
    int sumTest = 0;
    int stepTest = 0;
    command cmd = randCmd();
    int path[ROW][COL];
    fillRegion(path, 0, ROW - 1, 0, COL - 1, '-');
    initDimsArr(dims);
    initMapArr(map, dims);
    
    for (int i = 0; i < MAXDIM(ROW, dims[0]); i++) {
        for (int j = 0; j < MAXDIM(COL, dims[1]); j++) {
            int iVar = i;
            int jVar = j;
            assignAdjacent(adj.data(), map, dims, cmd, adjPos, iVar, jVar);
            movePos(path, adj.data(), dims, adjPos, iVar, jVar, steps, sum, cmd);
            if(adjPos != -1) sumTest += adj[adjPos];
            stepTest++;
            ASSERT_EQ(sum, sumTest);
            ASSERT_EQ(steps, stepTest);
            if (j == jVar + 1) {
                ASSERT_GT(adjPos, 0);
                ASSERT_LT(adjPos, 4);
            }
            if (iVar == i - 1) ASSERT_LT(adjPos, 2);
            if (iVar == i + 1) ASSERT_GT(adjPos, 2);
            if (path[iVar][jVar] == 'X') ASSERT_GE(jVar, MAXDIM(COL, dims[1])-1);
            
        }
    }
}