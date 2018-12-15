#include <cstdlib>
#include <string>
#include <vector>
#include <mutex>
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

using TSStrV = TSGeneric<std::vector<std::string>>;

void search_str(std::string const & s, std::string & file, std::ifstream & is, TSStrV & v)
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
            ss << file << ':' << line;
            v([&](std::vector<std::string> & vec){
                vec.push_back(ss.str());
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
    std::vector<std::string> filenames(argv[2], argv[argc + 1]);
    std::vector<std::ifstream> files(argv[2], argv[argc + 1]);
    if(std::any_of(files.cbegin(), files.cend(), &std::ifstream::is_open)) {
        return EXIT_FAILURE;
    }
    std::vector<std::thread> threads;
    TSStrV v;

    for (int i = 0; i < files.size(); ++i) {
        std::thread t(search_str, std::ref(str), std::ref(filenames[i]), std::ref(files[i]), std::ref(v));
        threads.push_back(std::move(t));
    }

    for (auto t : threads) {
        t.join();
    }
    
    while (true) {
        std::cout << v([](std::vector<std::string> & v){
            auto x = v.front();
            x.pop_front();
            return x;
        }) << std::endl;
    }
    return EXIT_SUCCESS;
}
