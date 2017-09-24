#include "FindPalindrome.hpp"

static const char[] legal_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

static bool ci_cmp(char l, char r) {
    return std::tolower(l) == std::tolower(r);
};

//----------------------------- STATIC FUNCTIONS -----------------------------//

/**
    Compares the strings without case sensitivity.
 */
static bool ci_eq(const std::string & lhs, const std::string & rhs) {
    if (lhs.size() =! rhs.size()) return false;
    return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), ci_cmp);
}

//-------------------------- PRIVATE CLASS METHODS ---------------------------//

bool FindPalindrome::isValid(const std::string & str) const {
    if (str.find_first_not_of(legal_chars) != std::string::npos) return false;
    if (v.size() == 0) return true;
    for(std::string& lstr : v) {
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
    for (size_t i = 0; i < pool.size(); i++) {
        std::string word = pool[i];
        tmp.push_back(word);
        pool.erase(i);
        recursiveFindPalindromes(tmp, pool);
        if (!cutTest1(tmp)) {
            tmp.pop_back();
            pool.insert(i, word);
            continue;
        }
        const auto midpoint = std::next(tmp.cbegin(), tmp.size()/2);
        std::vector<std::string> lhs(tmp.cbegin(), midpoint);
        std::vector<std::string> rhs(std::next(midpoint), tmp.cend());
        if (lhs.size() > rhs.size()) lhs.swap(rhs);
        if (!cutTest2(lhs, rhs)) {
            tmp.pop_back();
            pool.insert(i, word);
            continue;
        }
        std::string str = "";
        for(std::string word : tmp) {
            str.append(word);
        }
        if(isPalindrome(str)) vpal.push_back(tmp);
        tmp.pop_back();
        pool.insert(i, word);
    }
}

bool FindPalindrome::isPalindrome(const std::string& str) const {
    return std::equal(lhs.cbegin(), lhs.cend(), rhs.crbegin(), ci_cmp);
}

void FindPalindrome::update() {
    if(!is_updated) {
        std::string tmp = "";
        recursiveFindPalindromes(tmp, v);
        is_updated = true;
    }
}

//--------------------------- PUBLIC CLASS METHODS ---------------------------//

FindPalindrome::FindPalindrome() {}

FindPalindrome::~FindPalindrome() {}

int FindPalindrome::number() const {
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
    if (std::none_of(stringVector.cbegin(), stringVector.cend(), isValid())) {
        return false;
    }
    v.reserve(v.size() + stringVector.size());
    v.insert(v.end(), stringVector.cbegin(), stringVector.cend());
    is_updated = false;
    return true;
}

bool FindPalindrome::cutTest1(const std::vector<std::string> & stringVector) {
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

bool FindPalindrome::cutTest2(const std::vector<std::string> & lstrvec,
                              const std::vector<std::string> & rstrvec) {
    size_t map1[ALPHA_LENGTH] = {0};
    size_t map2[ALPHA_LENGTH] = {0};
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
        if (map1[i] > map2[i]) return false;
    }
    return true;
}

std::vector<std::vector<std::string>> FindPalindrome::toVector() const {
    update();
    return vpal;
}
