#include "FindPalindrome.hpp"
static const char legal_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";


//----------------------------- STATIC FUNCTIONS -----------------------------//

/**
    Compares characters without case sensitivity.
 */
static bool ci_cmp(char l, char r) {
    return std::tolower(l) == std::tolower(r);
}

/**
    Compares the strings without case sensitivity.
 */
static bool ci_eq(const std::string & lhs, const std::string & rhs) {
    if (lhs.size() != rhs.size()) return false;
    return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), ci_cmp);
}

/**
    Returns the total number of chars in a vector of strings.
 */
static size_t vstr_charcnt(const std::vector<std::string>& v) {
    size_t i = 0;
    for (const std::string& str : v) {
        i += str.size();
    }
    return i;
}


//-------------------------- PRIVATE CLASS METHODS ---------------------------//

bool FindPalindrome::isValid(const std::string & str) const {
    if (str.empty()) return false;
    if (str.find_first_not_of(legal_chars) != std::string::npos) return false;
    if (v.size() == 0) return true;
    for(const std::string& lstr : v) {
        if (ci_eq(lstr, str)) return false;
    }
    return true;
}

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(
        std::vector<std::string> candidateStringVector,
        std::vector<std::string> currentStringVector) {

    std::vector<std::string>& tmp = candidateStringVector;
    std::vector<std::string>& pool = currentStringVector;

    if (pool.empty()) return;
    if (!cutTest1(v)) return;
    if(!cutTest2(tmp, pool)) {
        return;
    }

    for (size_t i = 0; i < pool.size(); i++) {
        auto it = std::next(pool.begin(), i);
        tmp.push_back(*it);
        pool.erase(it);
        recursiveFindPalindromes(tmp, pool);
        if (pool.empty()) {
            std::string str = "";
            for(std::string& word : tmp) {
                str.append(word);
            }
            if (isPalindrome(str)) vpal.push_back(tmp);
        }
        pool.insert(it, tmp.back());
        tmp.pop_back();
    }
}

bool FindPalindrome::isPalindrome(const std::string& str) const {
    return std::equal(str.cbegin(), str.cend(), str.crbegin(), ci_cmp);
}

void FindPalindrome::update() {
    if(!is_updated) {
        std::vector<std::string> tmp = {};
        vpal.clear();
        recursiveFindPalindromes(tmp, v);
        is_updated = true;
    }
}

//--------------------------- PUBLIC CLASS METHODS ---------------------------//

FindPalindrome::FindPalindrome() {}

FindPalindrome::~FindPalindrome() {}

int FindPalindrome::number() {
    update();
    return vpal.size();
}

void FindPalindrome::clear() {
    v.clear();
    vpal.clear();
    is_updated = true;
}

bool FindPalindrome::add(const std::string & value) {
    if(!isValid(value)) return false;
    v.push_back(value);
    is_updated = false;
    return true;
}

bool FindPalindrome::add(const std::vector<std::string> & stringVector) {
    for (const std::string& str : stringVector) {
        if (!isValid(str)) return false;
    }
    v.reserve(v.size() + stringVector.size());
    v.insert(v.end(), stringVector.cbegin(), stringVector.cend());
    is_updated = false;
    return true;
}

bool FindPalindrome::cutTest1(const std::vector<std::string> & stringVector) {
    if(stringVector.size() == 0) return true;
    size_t map[ALPHA_LENGTH] = {0};
    bool lone_char = false;
    for (const std::string& str : stringVector) {
        for (const char c : str) {
            map[std::tolower(c) - 'a']++;
        }
    }
    for (size_t i = 0; i < ALPHA_LENGTH; i++) {
        bool even_char = (map[i] % 2 != 1);
        if (!even_char && lone_char) return false;
        if (!even_char) lone_char = true;
    }
    return true;
}

bool FindPalindrome::cutTest2(const std::vector<std::string> & stringVector1,
                              const std::vector<std::string> & stringVector2) {
    size_t map1[ALPHA_LENGTH] = {0};
    size_t map2[ALPHA_LENGTH] = {0};
    bool direction = vstr_charcnt(stringVector1) > vstr_charcnt(stringVector2);
    if (direction) {
        if(stringVector2.empty()) return true;
    } else {
        if(stringVector1.empty()) return true;
    }

    for (const std::string& str : stringVector1) {
        for (const char c : str) {
            map1[std::tolower(c) - 'a']++;
        }
    }
    for (const std::string& str : stringVector2) {
        for (const char c : str) {
            map2[std::tolower(c) - 'a']++;
        }
    }
    for (size_t i = 0; i < ALPHA_LENGTH; i++) {
        if (direction) {
            if (map2[i] > map1[i]) return false;
        } else {
            if (map1[i] > map2[i]) return false;
        }
    }

    return true;
}

std::vector<std::vector<std::string>> FindPalindrome::toVector() {
    update();
    return vpal;
}
