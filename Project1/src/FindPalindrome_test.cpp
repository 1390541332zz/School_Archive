#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include "FindPalindrome.hpp"
#include <array>

static bool ci_cmp(char l, char r) {
    return std::tolower(l) == std::tolower(r);
}

static bool ci_eq(const std::string & lhs, const std::string & rhs) {
    if (lhs.size() != rhs.size()) return false;
    return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), ci_cmp);
}

static const std::vector<std::string> invalid_string = {
    "",
    "0",
    "a1",
    "1a",
    " aaawrerf",
    "akedfoiw ",
    "aked foiw",
    "ldlkjfdlkjlkjd;lkleiejuoijklj"
};

static const std::vector<std::string> valid_string = {
    "aaa", "aba", "kayak", "Asa", "a",
    "k", "y", "aa"
};

static const std::vector<std::string> uc_string = {
    "AAA", "ABA", "kaYAk", "aSA", "A",
    "K", "Y", "AA"
};

static const std::vector<std::string> lc_string = {
    "aaa", "aba", "kayak", "asa", "a",
    "k", "y", "aak"
};

static const std::vector<std::string> pal_words1 = {
    "a", "AA", "AaA"
};
static const std::vector<std::string> pal_lc_words1 = {
    "a", "aa", "aaa"
};

static const std::vector<std::vector<std::string>> pal_list1 = {
    {"a", "AA", "AaA"},
    {"a", "AaA", "AA"},
    {"AA", "a", "AaA"},
    {"AA", "AaA", "a"},
    {"AaA", "a", "AA"},
    {"AaA", "AA", "a"}
};

static const std::vector<std::vector<std::vector<std::string>>> pal_split1 = {
    {{"a"}, {"AA", "AaA"}},
    {{"a", "AaA"}, {"AAAAAA"}},
    {{"AA"}, {"a", "AaA"}},
    {{"AA"}, {"AaA", "a"}},
    {{"AaA"}, {"a", "AA"}},
    {{"AaA"}, {"AA", "a"}},
    {{"aa", "a"}, {"a", "aaa", "aaaaaaaaaaaaa"}},
    {{"stab", "knows"}, {"kodok", "swonk", "bats"}},
    {
        {
            "morbid", "animal", "ogres", "lean", "stab", "rats", "amor", "trap"
        }, {
            "keep", "made", "Tacocat", "deep", "denned", "peed", "Tacocat", "Edam",
            "peek", "part", "Roma", "star", "bats", "nael", "Sergo", "lamina", "dibrom"
        }
    },
    {{"a"},{"a"}}
};

static const std::vector<std::vector<std::vector<std::string>>> invalid_pal_split1 = {
    {{"al"}, {"qAA", "AaA"}},
    {{"va", "AaA"}, {"AAAAAA"}},
    {{"AqA"}, {"Ba", "AaA"}},
    {{"AhA"}, {"AaA", "a"}},
    {{"AaAR"}, {"a", "AA"}},
    {{"AE"}, {"AA", "a"}},
    {{"aXa", "a"}, {"a", "aaa", "aaaaaaaaaaaaa"}},
    {{"alXXXXone"}, {"rye", "seres", "eyr", "Enola"}}
};

const std::vector<std::string> pal_words2 = {
    "alone", "rye", "seres", "eyr", "Enola"
};

static const std::vector<std::vector<std::string>> pal_list2 = {
    {"alone", "rye", "seres", "eyr", "Enola"},
    {"alone", "eyr", "seres", "rye", "Enola"},
    {"rye", "alone", "seres", "Enola", "eyr"},
    {"rye", "Enola", "seres", "alone", "eyr"},
    {"eyr", "alone", "seres", "Enola", "rye"},
    {"eyr", "Enola", "seres", "alone", "rye"},
    {"Enola", "rye", "seres", "eyr", "alone"},
    {"Enola", "eyr", "seres", "rye", "alone"}
};

static const std::vector<std::vector<std::vector<std::string>>> pal_lc_split1 = {
    {{"kayak"}, {"aa", "kayak"}},
    {{"a", "aaa"}, {"aaaaaaaa"}},
    {{"aa"}, {"a", "aaa"}},
    {{"aa"}, {"aaa", "a"}},
    {{"aaa"}, {"a", "aa"}},
    {{"aaa"}, {"aa", "a"}}
};

static const std::vector<std::vector<std::vector<std::string>>> pal_uc_split1 = {
    {{"kAyaK"}, {"aa", "kaYak"}},
    {{"a", "aaa"}, {"aaaAaAaa"}},
    {{"aa"}, {"a", "aaa"}},
    {{"Aa"}, {"Aaa", "a"}},
    {{"aaa"}, {"A", "aA"}},
    {{"aaA"}, {"Aa", "a"}}
};

const std::vector<std::vector<std::string>> pal_split2 = {
    {"alone", "rye"}, {"seres", "eyr", "Enola"}
};


TEST_CASE("Sanitised Data", "[FindPalindrome]") {
    FindPalindrome pal;
    SECTION("Restricted Characters", "[FindPalindrome]") {
        for (auto str : invalid_string) {
            REQUIRE_FALSE(pal.add(str));
        }
        REQUIRE_FALSE(pal.add(invalid_string));
    }
    SECTION("Nonduplicate Input", "[FindPalindrome]") {
        for (auto str : valid_string) {
            REQUIRE(pal.add(str));
            REQUIRE_FALSE(pal.add(str));
        }
        REQUIRE_FALSE(pal.add(valid_string[0]));
        pal.clear();
        REQUIRE(pal.add(valid_string));
        REQUIRE_FALSE(pal.add(valid_string));
    }
    SECTION("Nonduplicate Output", "[FindPalindrome]") {
        pal.add(valid_string);
        std::vector<std::vector<std::string>> vec = pal.toVector();
        std::sort(vec.begin(), vec.end());
        REQUIRE(std::unique(vec.begin(), vec.end()) == vec.end());
    }
}

TEST_CASE("Case Sensitivity", "[FindPalindrome]") {
    FindPalindrome pal_uc;
    FindPalindrome pal_lc;
    pal_uc.add(pal_words1);
    pal_lc.add(pal_lc_words1);
    SECTION("Helpers", "[FindPalindrome]") {
        REQUIRE(pal_uc.cutTest1(lc_string) == pal_uc.cutTest1(uc_string));
        for (size_t i = 0; i < pal_lc_split1.size(); i++) {
            REQUIRE(pal_uc.cutTest2(pal_lc_split1[i][0], pal_lc_split1[i][1])
                 == pal_uc.cutTest2(pal_uc_split1[i][0], pal_uc_split1[i][1]));
            REQUIRE(pal_uc.cutTest2(pal_lc_split1[i][0], pal_uc_split1[i][1])
                 == pal_uc.cutTest2(pal_uc_split1[i][0], pal_lc_split1[i][1]));

        }
    }
    SECTION("Accessors", "[FindPalindrome]") {
        std::vector<std::vector<std::string>> v_uc = pal_uc.toVector();
        std::vector<std::vector<std::string>> v_lc = pal_lc.toVector();
        REQUIRE(pal_uc.number() == pal_lc.number());
        REQUIRE(v_uc.size() == v_lc.size());
        for (size_t i = 0; i < v_uc.size(); i++) {
                REQUIRE(v_uc[i].size() == v_lc[i].size());
                REQUIRE_FALSE(v_uc[i] == v_lc[i]);
                REQUIRE(std::equal(v_uc[i].cbegin(),
                                   v_uc[i].cend(),
                                   v_lc[i].cbegin(),
                                   ci_eq));
        }
    }
}

TEST_CASE("Clear", "[FindPalindrome]") {
    FindPalindrome pal;
    const std::vector<std::vector<std::string>> v = {};
    pal.add(pal_words1);
    REQUIRE_FALSE(pal.toVector() == v);
    REQUIRE_FALSE(pal.number() == 0);
    pal.clear();
    REQUIRE(pal.toVector() == v);
    REQUIRE(pal.number() == 0);
}

TEST_CASE("Palindrome Detection", "[FindPalindrome]") {
    FindPalindrome pal;
    SECTION("Valid Palindromes", "[FindPalindrome]") {
        for (auto str : pal_list1) {
            REQUIRE(pal.cutTest1(str));
        }
        for (auto v : pal_split1) {
            REQUIRE(pal.cutTest2(v[0], v[1]));
        }
        pal.add(pal_words1);
        REQUIRE(pal.toVector() == pal_list1);
    }
    SECTION("Invalid Palindromes", "[FindPalindrome]") {
        for (size_t i = 0; i < pal_lc_split1.size(); i++) {
            REQUIRE_FALSE(pal.cutTest2(invalid_pal_split1[i][0],
                                       invalid_pal_split1[i][1]));
        }
    }
    SECTION("Single Palindrome", "[FindPalindrome]") {
        pal.add(pal_words2);

        REQUIRE(pal.cutTest1(pal_words2));
        REQUIRE(pal.cutTest2(pal_split2[0], pal_split2[1]));
        REQUIRE(pal.toVector() == pal_list2);
        REQUIRE(pal.number() == pal_list2.size());
    }
    SECTION("Single Word Palindrome" "[FindPalindrome]") {
        pal.add("kayak");
        const std::vector<std::vector<std::string>> v = {{"kayak"}};
        REQUIRE(pal.toVector() == v);
        REQUIRE(pal.number() == 1);
    }
}
