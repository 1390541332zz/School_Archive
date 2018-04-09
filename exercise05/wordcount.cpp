// Exercise 05: Wordcounts
// Author: Jacob Abel
//
// Objectives
// 1) Counts number of times each word appears in a text file.
// 2) Sorts the words from most to least frequently used.
// 3) Writes the top 10 most used words to std::cout.

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <iostream>

int main() 
{
    typedef std::pair<std::string, std::size_t> wordpair;
    auto cmp = [](wordpair const& lhs, wordpair const& rhs) {
                     return (lhs.second < rhs.second);
                 };            

    std::ifstream is("prose.txt");
    std::map<std::string, std::size_t> word_map;
    std::string word;

    while (is >> word) {
        word_map[word]++;
    }

    std::priority_queue<wordpair, std::vector<wordpair>, decltype(cmp)>
        word_heap(word_map.cbegin(), word_map.cend(), cmp);

    for (std::size_t i = 0; i < 10; ++i) {
        std::cout << word_heap.top().first << ' ';
        word_heap.pop();
    }
    std::cout << std::endl;

    return 0;
}
