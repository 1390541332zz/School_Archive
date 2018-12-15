#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <deque>
#include <mutex>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <thread>

// Concept courtesy of Herb Sutter's talk
// C++ and Beyond 2012: Herb Sutter - C++ Concurrency
template<typename T>
class TSGeneric {
private:
    T x_;
    mutable std::mutex m;
public:
    TSGeneric() {}
    TSGeneric(T x) : x_(x) {}
    template <typename F>
    auto operator()(F fun) -> decltype(fun(x_))
    {
        std::lock_guard<std::mutex> lock(m);
        return fun(x_);
    }
};

using SearchResult  = std::pair<void const *, std::string>;
using SearchResults = std::deque<SearchResult>;

void search_str(std::string const & s, std::ifstream & is, TSGeneric<SearchResults> & d)
{
    std::size_t line = 1;
    while (is.good()) {
        bool found = false;
        for (auto c : s) {
            if (is.peek() == '\n') {
                ++line;
            }
            if (is.get() != c) {
                break;
            }
        }
        if (found) {
            std::stringstream ss;
            ss << line;
            d([&](SearchResults & deq){
                deq.push_back({&is,ss.str()});
            });
        }
    }
}

int main(int argc, char ** argv)
{
    if (argc < 3) {
        return EXIT_FAILURE;
    }
    std::string str(argv[1]);
    std::vector<std::ifstream> files(argv + 2, argv + argc);
    if(std::any_of(files.cbegin(), files.cend(), [](std::ifstream const & s) {
        return !s.is_open();
    })) {
        return EXIT_FAILURE;
    }
    std::vector<std::thread> threads;
    std::vector<std::thread::id> ids;
    threads.reserve(files.size()); 
    ids.reserve(files.size()); 
    TSGeneric<SearchResults> d;

    for (auto & file : files) {
        std::thread t(search_str, std::ref(str), std::ref(file), std::ref(d));
        ids.push_back(t.get_id());
        threads.push_back(std::move(t));
    }
    std::map<void const *, std::string> m;
    std::transform(files.cbegin(), files.cend(), argv + 2, std::inserter(m, m.end()), 
        [](std::ifstream const & is, std::string s)
    {
        return std::make_pair(&is, s);
    });
    for (auto & t : threads) {
        t.join();
    }
    d([&m](SearchResults const & d) { 
        std::for_each(d.cbegin(), d.cend(), [&m](SearchResult const & x) {
            std::cout << m[x.first] << ':' << x.second << std::endl;
        });
    });
    return EXIT_SUCCESS;
}
