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
#include <cstdlib>
#include <ctime>
#include <array>

TEST(MinMaxElement, Max) {
    std::srand(std::time(0));
    std::array<int, NSIDES> arr = {0};
    for (size_t i = 0; i < NSIDES; i++) {
        arr[i] = (std::rand() & 1) ? std::rand() : -std::rand();
    }
    ASSERT_EQ(*std::max_element(arr.begin(), arr.end()), \
              arr[minMaxElement(arr.data(), true)]);
}

TEST(MinMaxElement, Min) {
    std::srand(std::time(0));
    std::array<int, NSIDES> arr = {0};
    for (size_t i = 0; i < NSIDES; i++) {
        arr[i] = (std::rand() & 1) ? std::rand() : -std::rand();
    }
    ASSERT_EQ(*std::min_element(arr.begin(), arr.end()), \
              arr[minMaxElement(arr.data(), false)]);
}

TEST(FillRegion, Fill) {
    int fillVal = std::rand();
    int arr[ROW][COL] = {0};
    fillRegion(arr, 0, ROW-1, 0, COL-1, fillVal);
    for (size_t i = 0; i < ROW; i++) {
        for (size_t j = 0; j < COL; j++) {
            ASSERT_EQ(arr[i][j], fillVal);
        }
    }
}

TEST(assignAdjacent, Boundary) {
    std::srand(std::time(0));
    int adj[NSIDES] = {0};
    int map[ROW][COL] = {0};
    int dims[2] = {std::rand()%(ROW*2), std::rand()%(COL*2)};
    int adjPos = -1;
    command cmd = static_cast<command>(std::rand()%3);
    
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            for (int k = 0; k < NSIDES; k++) {
                if (adjPos == k) ASSERT_EQ(ILLEGALVAL(cmd), adj[adjPos]); 
            }
            assignAdjacent(adj, map, dims, cmd, adjPos, i, j);
            if (i <= 1) {
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

TEST(LoadMap, Load) {
    std::string mapFile = "test/generated/loadmap.test";
    std::ofstream os(mapFile);
    int dimTest[2] = {std::rand()%(ROW*2), std::rand()%(COL*2)};
    int mapTest[ROW][COL] = {0};
    int dims[2] = {0};
    int map[ROW][COL] = {0};
    int randInt = 0;
    
    os << std::left << std::setw(13) << "ncols"     << dimTest[1]  << std::endl;
    os << std::left << std::setw(13) << "nrows"     << dimTest[0]  << std::endl;
    os << std::left << std::setw(13) << "xllcorner" << std::rand() << std::endl;
    os << std::left << std::setw(13) << "yllcorner" << std::rand() << std::endl;
    os << std::left << std::setw(13) << "cellsize"  << std::rand() << std::endl;
    for (int i = 0; i < dimTest[0]; i++) {
        os << ' ';
        for (int j = 0; j < dimTest[1]; j++) {
            randInt = std::rand()%65536;
            os << randInt << ' ';
            if (i < ROW && j < COL) mapTest[i][j] = randInt;
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
            ASSERT_EQ(map[i][j], mapTest[i][j]);
        }
    }
}