#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "XMLParser.hpp"
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> valid_xml = {
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
    "<note></note>",
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<note>\n\
<to>Tove</to>\n\
<from name=\"test\", joe=\"teddy\" >Jani</from>\n\
<heading>Reminder</heading>\n\
<note/>\n\
<body>Don't forget me this weekend!</body>\n\
</note>"
};

std::vector<std::vector<std::string>> valid_xml_tags = {
    {}, {
        "note"
    }, {
        "note",
        "to",
        "from",
        "heading",
        "body"
    }
};

std::vector<std::vector<size_t>> valid_xml_cnts = {
    {}, {
        1
    }, {
        2, 1, 1, 1, 1
    }
};

std::vector<std::vector<TokenStruct>> valid_xml_tokenstructs = {
    {
        {DECLARATION, "xml version=\"1.0\" encoding=\"UTF-8\""},
    }, {
        {START_TAG,   "note"},
        {END_TAG,     "note"}
    }, {
        {DECLARATION, "xml version=\"1.0\" encoding=\"UTF-8\""},
        {CONTENT,     "\n"},
        {START_TAG,   "note"},
        {CONTENT,     "\n"},
        {START_TAG,   "to"},
        {CONTENT,     "Tove"},
        {END_TAG,     "to"},
        {CONTENT,     "\n"},
        {START_TAG,   "from name=\"test\", joe=\"teddy\" "},
        {CONTENT,     "Jani"},
        {END_TAG,     "from"},
        {CONTENT,     "\n"},
        {START_TAG,   "heading"},
        {CONTENT,     "Reminder"},
        {END_TAG,     "heading"},
        {CONTENT,     "\n"},
        {EMPTY_TAG,   "note"},
        {CONTENT,     "\n"},
        {START_TAG,   "body"},
        {CONTENT,     "Don't forget me this weekend!"},
        {END_TAG,     "body"},
        {CONTENT,     "\n"},
        {END_TAG,     "note"},
    }
};


std::vector<TokenStruct> blank_tokenstruct = {};

std::vector<std::string> invalid_xml_tokens = {
    "", "</", "/>", "<?", "?>", "<", ">",
    "<note<",
    "</note/>",
    "<note?><note>",
    "<note><?note>",
    ">note><note>",
};

std::vector<std::string> invalid_xml = {
    "",
    "<note>",
    "< ></ >",
    "</note>",
    "<note></note><note/>",
    "<note/><note/>",
    "</note></note>"
    "<note><note>",
    "<note><note></note>",
    "<note></note></note>",
    "<note></note><potato>",
    "<note></note><potato></potato>",
    "<note></NOTE>",
    "<.note/>",
    "<-note/>",
    "<1note/>",
    "<.n}te/>",
    "fjfdjfdkh",
    "<note/>fflkflkfjkfdjlk",
    "dslkjdslkjdslkj<note/>",
    "<note></flag></note>",
    "<note></note><?xml?>",
    "<note><sthdis><qqq/>thshewrb</sthdis></note>",
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<note>\n\
<to>Tove</to>\n\
<from name=\"test\", joe=\"teddy\" >Jani</from>\n\
<heading>Reminder</heading>\n\
<note/></note>\n\
<body>Don't forget me this weekend!</body>\n\
</note>",
};

static std::string serialise_tokenType(StringTokenType type) {
    switch (type) {
        case START_TAG:     return "START_TAG";
        case END_TAG:       return "END_TAG";
        case EMPTY_TAG:     return "EMPTY_TAG";
        case CONTENT:       return "CONTENT";
        case DECLARATION:   return "DECLARATION";
    }
    return "ERROR";
}

static bool operator==(const TokenStruct& lhs, const TokenStruct& rhs) {
    return (lhs.tokenType == rhs.tokenType && lhs.tokenString == rhs.tokenString);
}

TEST_CASE("Basic Functionality", "[Stack]") {
    Stack<int> s;

    SECTION("Default Empty Stack") {
        REQUIRE(s.size() == 0);
        REQUIRE(s.isEmpty());
        REQUIRE_FALSE(s.pop());
        REQUIRE_THROWS(s.peek());
    }
    SECTION("With Contents") {
        for (size_t i = 1; i <= 10; i++) {
            REQUIRE(s.push(i));
            REQUIRE(s.size() == i);
        }

        SECTION("Unrolling Stack") {
            for (size_t i = 10; i > 0; i--) {
                REQUIRE_NOTHROW(s.peek());
                REQUIRE(s.peek() == i);
                REQUIRE(s.size() == i);
                REQUIRE(s.pop());
                REQUIRE(s.size() == i - 1);
            }
            REQUIRE_THROWS(s.peek());
        }
        SECTION("Clearing Stack") {
            s.clear();
            REQUIRE(s.size() == 0);
            REQUIRE(s.isEmpty());
        }
    }
}

TEST_CASE("Tokenise" "[XMLParser]") {
    XMLParser p;

    SECTION("Valid XML") {
        for (size_t i = 0; i < valid_xml.size(); i++) {
            INFO("String: " + valid_xml[i]);
            REQUIRE(p.tokenizeInputString(valid_xml[i]));
            std::vector<TokenStruct> v = p.returnTokenizedInput();
            std::string in = "";
            for (size_t j = 0; j < valid_xml_tokenstructs[i].size(); j++) {
                in += "L{";
                in += serialise_tokenType(v[j].tokenType);
                in += ", ";
                in += v[j].tokenString;
                in += "} : R{";
                in += serialise_tokenType(valid_xml_tokenstructs[i][j].tokenType);
                in += ", ";
                in += valid_xml_tokenstructs[i][j].tokenString;
                in += "}";
            }
            INFO(in);
            REQUIRE(v == valid_xml_tokenstructs[i]);
        }
    }
    SECTION("Invalid XML") {
        for (auto str : invalid_xml_tokens) {
            INFO("String: " + str);
            REQUIRE_FALSE(p.tokenizeInputString(str));
            REQUIRE(p.returnTokenizedInput() == blank_tokenstruct);
        }
    }
}

TEST_CASE("Parse", "[XMLParser]") {
    XMLParser p;

    SECTION("Valid XML") {
        for (size_t i = 0; i < valid_xml.size(); i++) {
            INFO("String: " + valid_xml[i]);
            REQUIRE(p.tokenizeInputString(valid_xml[i]));
            REQUIRE(p.parseTokenizedInput());
            for (size_t j = 0; j < valid_xml_tags[i].size(); j++) {
                REQUIRE(p.containsElementName(valid_xml_tags[i][j]));
                REQUIRE(p.frequencyElementName(valid_xml_tags[i][j]) == valid_xml_cnts[i][j]);
            }
        }
    }

    SECTION("Invalid XML") {
        for (const auto& str : invalid_xml) {
            INFO("String: " + str);
            p.tokenizeInputString(str);
            std::vector<TokenStruct> v = p.returnTokenizedInput();
            REQUIRE_FALSE(p.parseTokenizedInput());
            for (const auto& token : v) {
                REQUIRE_FALSE(p.containsElementName(token.tokenString));
                REQUIRE(p.frequencyElementName(token.tokenString) == 0);
            }
        }
    }
}
