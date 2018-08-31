#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

typedef std::pair<std::string, std::size_t> map_pair;

void wordcount(std::ifstream & is, std::ostream & os)
{
    std::map<std::string, std::size_t> words;
    std::string word;
    while(is >> word) {
        auto it = words.find(word);
        if (it == words.end()) {
            words.emplace(word, 1);
        } else {
            it->second++;
        }
    }
    std::vector<map_pair> v;
    std::move(words.begin(), words.end(), std::back_inserter(v));
    std::partial_sort(v.begin(), v.begin() + 10, v.end(), 
             [] (map_pair const & x, map_pair const & y) {
                 return (std::get<1>(x) > std::get<1>(y));
             });
    for (std::size_t i = 0; i < 10; ++i) {
        os << std::get<0>(v[i]) << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::string wordfile = "./prose.txt";
    std::ifstream is(wordfile);
    wordcount(is, std::cout);
}
